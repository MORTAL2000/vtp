//
// Name:	 canvas.cpp
// Purpose:	 Implements the canvas class for the wxWindows application.
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "vtlib/vtlib.h"
#include "vtlib/core/TimeEngines.h"
#include "../TerrainSceneWP.h"	// for GetTerrainScene
#include "../Enviro.h"			// for g_App
#include "canvas.h"
#include "frame.h"
#include "app.h"

DECLARE_APP(vtApp)

/*
 * vtGLCanvas implementation
 */
BEGIN_EVENT_TABLE(vtGLCanvas, wxGLCanvas)
	EVT_CLOSE(vtGLCanvas::OnClose)
	EVT_SIZE(vtGLCanvas::OnSize)
	EVT_PAINT(vtGLCanvas::OnPaint)
	EVT_CHAR(vtGLCanvas::OnChar)
	EVT_MOUSE_EVENTS(vtGLCanvas::OnMouseEvent)
	EVT_ERASE_BACKGROUND(vtGLCanvas::OnEraseBackground)
END_EVENT_TABLE()

static vtGLCanvas *s_canvas = NULL;


vtGLCanvas::vtGLCanvas(wxWindow *parent, wxWindowID id,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name, int* gl_attrib):
  wxGLCanvas(parent, id, pos, size, style, name, gl_attrib)
{
	parent->Show(TRUE);
	SetCurrent();

	m_StatusTimer.SetFrame((wxFrame *)parent);
	m_StatusTimer.Start(1000);

	m_bPainting = false;
	m_bRunning = true;
	m_bShowFrameRateChart = true;

	s_canvas = this;
}


vtGLCanvas::~vtGLCanvas(void)
{
}

void EnableContinuousRendering(bool bTrue)
{
	if (s_canvas)
		s_canvas->m_bRunning = bTrue;
}

void vtGLCanvas::QueueRefresh(bool eraseBackground)
	// A Refresh routine we can call from inside OnPaint.
	//   (queues the events rather than dispatching them immediately).
{
	// With wxGTK, you can't do a Refresh() in OnPaint because it doesn't
	//   queue (post) a Refresh event for later.  Rather it dispatches
	//   (processes) the underlying events immediately via ProcessEvent
	//   (read, recursive call).  See the wxPostEvent docs and Refresh code
	//   for more details.
	if ( eraseBackground ) 
	{
		wxEraseEvent eevent( GetId() );
		eevent.SetEventObject( this );
		wxPostEvent( GetEventHandler(), eevent );
	}

	wxPaintEvent event( GetId() );
	event.SetEventObject( this );
	wxPostEvent( GetEventHandler(), event );
}

void StatusTimer::Notify()
{
	if (!m_pFrame || !m_pFrame->GetStatusBar()) return;

	vtScene *scene = vtGetScene();
	if (!scene) return;

	// get framerate
	float fps = scene->GetFrameRate();

	// get time of day
	int hr, min, sec;
	GetTerrainScene().m_pTime->GetTime(hr, min, sec);

	vtString str, str2;
	str.Format("fps %3.1f, time %02d:%02d:%02d, ", fps, hr, min, sec);

	g_App.DescribeCoordinates(str2);
	str += str2;

	// get CLOD triangle counts, if appropriate
	g_App.DescribeCLOD(str2);
	str += str2;

	str += g_App.m_strMessage;

	m_pFrame->SetStatusText((const char *)str);
}


void vtGLCanvas::OnPaint( wxPaintEvent& event )
{
	// place the dc inside a scope, to delete it before the end of function
	if (1)
	{
		// This is a dummy, to avoid an endless succession of paint messages.
		// OnPaint handlers must always create a wxPaintDC.
		wxPaintDC dc(this);
#ifdef __WXMSW__
		if (!GetContext()) return;
#endif

		if (m_bPainting || !m_bRunning) return;

		m_bPainting = true;

		// Render the Scene Graph
		vtGetScene()->DoUpdate();

		if (m_bShowFrameRateChart)
			vtGetScene()->DrawFrameRateChart();

		SwapBuffers();

#ifdef WIN32
		// Call Refresh again for continuous rendering,
		if (m_bRunning)
			Refresh(FALSE);
#else
		// Queue another refresh for continuous rendering.
		//   (Yield first so we don't starve out keyboard & mouse events.)
		//
		// FIXME: We may want to use a frame timer instead of immediate-
		//   redraw so we don't eat so much CPU on machines that can
		//   easily handle the frame rate.
		wxYield();
		QueueRefresh(FALSE);
#endif

		// update the status bar every 1/10 of a second
		static float last_stat = 0.0f;
		float cur = vtGetTime();
		if (cur - last_stat > 0.1f)
		{
			last_stat = cur;
			m_StatusTimer.Notify();
		}

		m_bPainting = false;
	}

	// Must allow some idle processing to occur - or the toolbars will not
	// update, and the close box will not respond!
	wxGetApp().ProcessIdle();
}

void vtGLCanvas::OnClose(wxCloseEvent& event)
{
	m_bRunning = false;
}

void vtGLCanvas::OnSize(wxSizeEvent& event)
{
  // Presumably this is a wxMSWism.  
  // For wxGTK & wxMotif, all canvas resize events occur before the context
  //   is set.  So ignore this context check and grab the window width/height
  //   when we get it so it (and derived values such as aspect ratio and
  //   viewport parms) are computed correctly.
#ifdef __WXMSW__
	if (!GetContext()) return;
#endif

	SetCurrent();
	int width, height;
	GetClientSize(& width, & height);

	vtGetScene()->SetWindowSize(width, height);

	wxGLCanvas::OnSize(event);
}

void vtGLCanvas::OnChar(wxKeyEvent& event)
{
	long key = event.KeyCode();

	// pass the char to the frame for it to do "accelerator" shortcuts
	vtFrame *frame = (vtFrame*) GetParent();
	frame->OnChar(event);

	int flags = 0;

	if (event.ControlDown())
		flags |= VT_CONTROL;

	if (event.ShiftDown())
		flags |= VT_SHIFT;

	if (event.AltDown())
		flags |= VT_ALT;

	// pass the char to the vtlib Scene
	vtGetScene()->OnKey(key, flags);
}

void vtGLCanvas::OnMouseEvent(wxMouseEvent& event1)
{
	// turn WX mouse event into a VT mouse event
	vtMouseEvent event;
	wxEventType  ev = event1.GetEventType();
	if (ev == wxEVT_LEFT_DOWN) {
		event.type = VT_DOWN;
		event.button = VT_LEFT;
	} else if (ev == wxEVT_LEFT_UP) {
		event.type = VT_UP;
		event.button = VT_LEFT;
	} else if (ev == wxEVT_MIDDLE_DOWN) {
		event.type = VT_DOWN;
		event.button = VT_MIDDLE;
	} else if (ev == wxEVT_MIDDLE_UP) {
		event.type = VT_UP;
		event.button = VT_MIDDLE;
	} else if (ev == wxEVT_RIGHT_DOWN) {
		event.type = VT_DOWN;
		event.button = VT_RIGHT;
	} else if (ev == wxEVT_RIGHT_UP) {
		event.type = VT_UP;
		event.button = VT_RIGHT;
	} else if (ev == wxEVT_MOTION) {
		event.type = VT_MOVE;
		event.button = VT_NONE;
	} else {
		// ignored mouse events, such as wxEVT_LEAVE_WINDOW
		return;
	}

	if (ev == wxEVT_LEFT_DOWN || ev == wxEVT_MIDDLE_DOWN || ev == wxEVT_RIGHT_DOWN)
		CaptureMouse();
	if (ev == wxEVT_LEFT_UP || ev == wxEVT_MIDDLE_UP || ev == wxEVT_RIGHT_UP)
		ReleaseMouse();

	event.flags = 0;
	wxCoord xpos, ypos;
    event1.GetPosition(&xpos, &ypos);
	event.pos.Set(xpos, ypos);

	if (event1.ControlDown())
		event.flags |= VT_CONTROL;

	if (event1.ShiftDown())
		event.flags |= VT_SHIFT;

	if (event1.AltDown())
		event.flags |= VT_ALT;

	// inform Enviro app
	g_App.OnMouse(event);

	vtGetScene()->OnMouse(event);
}

void vtGLCanvas::OnEraseBackground(wxEraseEvent& event)
{
	// Do nothing, to avoid flashing.
}

