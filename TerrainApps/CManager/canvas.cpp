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
#include "vtlib/core/NavEngines.h"
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

vtGLCanvas::vtGLCanvas(wxWindow *parent, wxWindowID id,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name, int* gl_attrib):
  wxGLCanvas(parent, id, pos, size, style, name, gl_attrib)
{
	parent->Show(TRUE);
	SetCurrent();

	m_bPainting = false;
	m_bRunning = true;
}


vtGLCanvas::~vtGLCanvas(void)
{
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

void vtGLCanvas::UpdateStatusText()
{
	vtFrame *frame = GetMainFrame();
	if (!frame || !frame->GetStatusBar()) return;

	vtScene *scene = vtGetScene();
	if (!scene) return;

	// get framerate
	float fps = scene->GetFrameRate();

	// get camera distance
	float dist = wxGetApp().m_pTrackball->GetRadius();

	vtString str;
	str.Format("fps %.3g, camera distance %.2f meters", fps, dist);

	frame->SetStatusText((const char *)str);
}

void vtGLCanvas::OnPaint( wxPaintEvent& event )
{
	// place the dc inside a scope, to delete it before the end of function
	if (1)
	{
		// This is a dummy, to avoid an endless succession of paint messages.
		// OnPaint handlers must always create a wxPaintDC.
		wxPaintDC dc(this);
#ifndef __WXMOTIF__
		if (!GetContext()) return;
#endif

		if (m_bPainting) return;

		m_bPainting = true;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the SSG scene
		vtGetScene()->DoUpdate();

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
			UpdateStatusText();
		}

		m_bPainting = false;
	}

	// Must allow some idle processing to occur - or the toolbars will not
	// update, and the close box will not respond!
	wxGetApp().ProcessIdle();
}

static void Reshape(int width, int height)
{
	glViewport(0, 0, (GLint)width, (GLint)height);
}


void vtGLCanvas::OnClose(wxCloseEvent& event)
{
	m_bRunning = false;
}

void vtGLCanvas::OnSize(wxSizeEvent& event)
{
#ifndef __WXMOTIF__
	if (!GetContext()) return;
#endif

	SetCurrent();
	int width, height;
	GetClientSize(& width, & height);
	Reshape(width, height);

	vtGetScene()->SetWindowSize(width, height);
}

void vtGLCanvas::OnChar(wxKeyEvent& event)
{
	long key = event.KeyCode();

	// pass the char to the frame for it to do "accelerator" shortcuts
	vtFrame *frame = (vtFrame*) GetParent();
	frame->OnChar(event);

	// pass the char to the vtlib Scene
	vtGetScene()->OnKey(key, 0);
}

void vtGLCanvas::OnMouseEvent(wxMouseEvent& event1)
{
	// turn WX mouse event into a VT mouse event
	vtMouseEvent event;
	wxEventType  ev = event1.GetEventType();
	switch (ev)
	{
	case wxEVT_LEFT_DOWN:
		event.type = VT_DOWN;
		event.button = VT_LEFT;
		break;
	case wxEVT_LEFT_UP:
		event.type = VT_UP;
		event.button = VT_LEFT;
		break;
	case wxEVT_MIDDLE_DOWN:
		event.type = VT_DOWN;
		event.button = VT_MIDDLE;
		break;
	case wxEVT_MIDDLE_UP:
		event.type = VT_UP;
		event.button = VT_MIDDLE;
		break;
	case wxEVT_RIGHT_DOWN:
		event.type = VT_DOWN;
		event.button = VT_RIGHT;
		break;
	case wxEVT_RIGHT_UP:
		event.type = VT_UP;
		event.button = VT_RIGHT;
		break;
	case wxEVT_MOTION:
		event.type = VT_MOVE;
		event.button = VT_NONE;
		break;
	default:
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

	vtGetScene()->OnMouse(event);
}

void vtGLCanvas::OnEraseBackground(wxEraseEvent& event)
{
	// Do nothing, to avoid flashing.
}

