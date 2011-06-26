//
// Name:	 canvas.cpp
// Purpose:	 Implements the canvas class for the wxWindows application.
//
// Copyright (c) 2001-2011 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "vtlib/vtlib.h"
#include "vtlib/core/Event.h"
#include "vtui/GraphicsWindowWX.h"
#include "vtdata/vtLog.h"

#include "canvas.h"
#include "frame.h"
#include "app.h"

DECLARE_APP(vtApp)

// Support for the SpaceNavigator
#include "vtlib/core/SpaceNav.h"
vtSpaceNav g_SpaceNav;

#define LOG_MOUSE_CAPTURE	0
#if LOG_MOUSE_CAPTURE
#define VTLOGCAP VTLOG
#else
#define VTLOGCAP
#endif

/*
 * vtGLCanvas implementation
 */
BEGIN_EVENT_TABLE(vtGLCanvas, wxGLCanvas)
	EVT_CLOSE(vtGLCanvas::OnClose)
	EVT_SIZE(vtGLCanvas::OnSize)
#ifndef __WXMAC__
	EVT_PAINT(vtGLCanvas::OnPaint)
#endif
	EVT_CHAR(vtGLCanvas::OnChar)
	EVT_KEY_DOWN(vtGLCanvas::OnKeyDown)
	EVT_KEY_UP(vtGLCanvas::OnKeyUp)
	EVT_MOUSE_EVENTS(vtGLCanvas::OnMouseEvent)
	EVT_ERASE_BACKGROUND(vtGLCanvas::OnEraseBackground)
	EVT_MOUSE_CAPTURE_LOST(vtGLCanvas::OnMouseCaptureLost)
	EVT_IDLE(vtGLCanvas::OnIdle)
END_EVENT_TABLE()

static vtGLCanvas *s_canvas = NULL;

vtGLCanvas::vtGLCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
	const wxSize& size, long style, const wxString& name, int* gl_attrib) :
#ifdef __WXMAC__
		wxGLCanvas(parent, id, pos, size, style, name, gl_attrib)
#else
		wxGLCanvas(parent, id, gl_attrib, pos, size, style, name)
#endif
{
	VTLOG("vtGLCanvas constructor\n");

#ifdef __WXMAC__
	const GLint Value = 1;
	aglSetInteger(GetContext()->m_glContext, AGL_SWAP_INTERVAL, &Value); // Force VSYNC on
#else
	m_bFirstPaint = true;
	m_bPainting = false;
#endif
	m_bRunning = true;
	m_bCapture = false;

	VTLOG1("vtGLCanvas: calling Show on parent\n");
	parent->Show(true);

	for (int i = 0; i < 512; i++)
		m_pbKeyState[i] = false;
	vtGetScene()->SetKeyStates(m_pbKeyState);
	m_iConsecutiveMousemoves = 0;

	// On RTL (right-to-left) system, the canvas should still be always LTR
	SetLayoutDirection(wxLayout_LeftToRight);

	// Initialize spacenavigator, if there is one present
	g_SpaceNav.Init();
	g_SpaceNav.SetTarget(vtGetScene()->GetCamera());

	s_canvas = this;
#ifdef NVIDIA_PERFORMANCE_MONITORING
	CPerformanceMonitorDialog::NVPM_init();
#endif
	VTLOG1("vtGLCanvas, leaving constructor\n");
}

vtGLCanvas::~vtGLCanvas(void)
{
	VTLOG(" destructing Canvas\n");
#ifdef NVIDIA_PERFORMANCE_MONITORING
	CPerformanceMonitorDialog::NVPM_shutdown();
#endif
	((GraphicsWindowWX*)vtGetScene()->GetGraphicsContext())->CloseOsgContext();
}

void vtGLCanvas::SetSpaceNavSpeed(float f)
{
	g_SpaceNav.SetSpeed(f);
}

void vtGLCanvas::SetSpaceNavAllowRoll(bool b)
{
	g_SpaceNav.SetAllowRoll(b);
}

#if WIN32
WXLRESULT vtGLCanvas::MSWDefWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam)
{
	// Catch SpaceNavigator messages; all others pass through
	if (nMsg == WM_INPUT)
		g_SpaceNav.ProcessWM_INPUTEvent(lParam);
	return wxWindowMSW::MSWDefWindowProc(nMsg, wParam, lParam);
}
#endif

void EnableContinuousRendering(bool bTrue)
{
	VTLOG("EnableContinuousRendering %d\n", bTrue);
	if (!s_canvas)
		return;

#ifdef __WXMAC__
	s_canvas->m_bRunning = bTrue;
#else
	bool bNeedRefresh = (s_canvas->m_bRunning == false && bTrue == true);
	s_canvas->m_bRunning = bTrue;
	if (bNeedRefresh)
		s_canvas->Refresh(FALSE);
#endif

	vtGetScene()->TimerRunning(bTrue);
}

#ifndef __WXMAC__
void vtGLCanvas::OnPaint( wxPaintEvent& event )
{
	if (m_bFirstPaint) VTLOG1("vtGLCanvas: first OnPaint\n");

	// Prevent this function from ever being called nested, it is not re-entrant
	static bool bInside = false;
	if (bInside)
		return;
	bInside = true;

	// place the dc inside a scope, to delete it before the end of function
	if (1)
	{
		// This is a dummy, to avoid an endless succession of paint messages.
		// OnPaint handlers must always create a wxPaintDC.
		if (m_bFirstPaint) VTLOG1("vtGLCanvas: creating a wxPaintDC on the stack\n");
		wxPaintDC dc(this);
	}

	// Avoid reentrance
	if (m_bPainting || !m_bRunning)
	{
		bInside = false;
		return;
	}
	m_bPainting = true;

	// Render the scene
	if (m_bFirstPaint)
		VTLOG1("vtGLCanvas: DoUpdate\n");

	vtGetScene()->DoUpdate();

	if (1)
	{
		// update the status bar every 1/10 of a second
		static float last_stat = 0.0f;
		float cur = vtGetTime();
		if (cur - last_stat > 0.1f)
		{
			last_stat = cur;
			vtFrame *frame = GetMainFrame();
			frame->UpdateStatusText();
		}
	}

	m_bPainting = false;

	// Reset the number of mousemoves we've gotten since last redraw
	m_iConsecutiveMousemoves = 0;

	if (m_bFirstPaint)
		m_bFirstPaint = false;

#ifdef NVIDIA_PERFORMANCE_MONITORING
	CPerformanceMonitorDialog::NVPM_frame();
#endif

	// Must allow some idle processing to occur - or the toolbars will not
	// update, and the close box will not respond!
//	wxGetApp().ProcessIdle();

	bInside = false;
}
#endif	// not __WXMAC__

void vtGLCanvas::OnClose(wxCloseEvent& event)
{
	VTLOG("Canvas OnClose\n");
	m_bRunning = false;
}

void vtGLCanvas::OnSize(wxSizeEvent& event)
{
	static int count = 0;
	if (count < 3)
	{
		VTLOG("Canvas  OnSize: %d %d\n", event.GetSize().x, event.GetSize().y);
		count++;
	}
	SetCurrent();
	wxSize size = GetClientSize();
	vtGetScene()->SetWindowSize(size.x, size.y);
	wxGLCanvas::OnSize(event);
}

void vtGLCanvas::OnChar(wxKeyEvent& event)
{
#ifdef USE_OSG_STATS
	GraphicsWindowWX* pGW = (GraphicsWindowWX*)vtGetScene()->GetGraphicsContext();
	if ((NULL != pGW) && pGW->valid())
		pGW->getEventQueue()->keyPress(event.GetKeyCode());
#endif
	long key = event.GetKeyCode();

	int flags = 0;

	if (event.ControlDown())
		flags |= VT_CONTROL;

	if (event.ShiftDown())
		flags |= VT_SHIFT;

	if (event.AltDown())
		flags |= VT_ALT;

	// pass the char to the vtlib Scene
	vtGetScene()->OnKey(key, flags);

	// Allow wxWindows to pass the event along to other code
	event.Skip();
}

void vtGLCanvas::OnKeyDown(wxKeyEvent& event)
{
	m_pbKeyState[event.m_keyCode] = true;
	event.Skip();
}

void vtGLCanvas::OnKeyUp(wxKeyEvent& event)
{
	m_pbKeyState[event.m_keyCode] = false;
	event.Skip();
}

void vtGLCanvas::OnMouseEvent(wxMouseEvent& event1)
{
	// Ensure that the default handler is called - this improves focus handling
    event1.Skip();

	// turn WX mouse event into a VT mouse event
	vtMouseEvent mevent;
	wxEventType type = event1.GetEventType();

	if ( type == wxEVT_LEFT_DOWN )
	{
		mevent.type = VT_DOWN;
		mevent.button = VT_LEFT;
	}
	else if ( type == wxEVT_LEFT_UP )
	{
		mevent.type = VT_UP;
		mevent.button = VT_LEFT;
	}
	else if ( type == wxEVT_MIDDLE_DOWN )
	{
		mevent.type = VT_DOWN;
		mevent.button = VT_MIDDLE;
	}
	else if ( type == wxEVT_MIDDLE_UP )
	{
		mevent.type = VT_UP;
		mevent.button = VT_MIDDLE;
	}
	else if ( type == wxEVT_RIGHT_DOWN )
	{
		mevent.type = VT_DOWN;
		mevent.button = VT_RIGHT;
	}
	else if ( type == wxEVT_RIGHT_UP )
	{
		mevent.type = VT_UP;
		mevent.button = VT_RIGHT;
	}
	else if ( type == wxEVT_MOTION )
	{
		mevent.type = VT_MOVE;
		mevent.button = VT_NONE;
		m_iConsecutiveMousemoves++;		// Increment
	}
	else if ( type == wxEVT_MOUSEWHEEL )
	{
		mevent.type = VT_WHEEL;
		mevent.button = event1.GetWheelRotation() / event1.GetWheelDelta();
	}
#ifdef __WXGTK__
    // wxGTK does not automatically set keyboard focus on to an OpenGL canvas window
	else if (type == wxEVT_ENTER_WINDOW)
	{
	    SetFocus();
	}
#endif
	else
	{
		// ignore other mouse events, such as wxEVT_LEAVE_WINDOW
		return;
	}

	if (type == wxEVT_LEFT_DOWN || type == wxEVT_MIDDLE_DOWN || type == wxEVT_RIGHT_DOWN)
	{
		VTLOGCAP("DOWN: capture %d", m_bCapture);
		if (!m_bCapture)
		{
			CaptureMouse();
			m_bCapture = true;
			VTLOGCAP(" -> true");
		}
		VTLOGCAP("\n");
	}
	if (type == wxEVT_LEFT_UP || type == wxEVT_MIDDLE_UP || type == wxEVT_RIGHT_UP)
	{
		VTLOGCAP("  UP: capture %d, isdown %d %d %d", m_bCapture,
			event1.LeftIsDown(), event1.MiddleIsDown(), event1.RightIsDown());

		if (m_bCapture && !event1.LeftIsDown() && !event1.MiddleIsDown() && !event1.RightIsDown())
		{
			ReleaseMouse();
			m_bCapture = false;
			VTLOGCAP(" -> false");
		}
		VTLOGCAP("\n");
	}

	// Because of the way the event pump works, if it takes too long to
	//  handle a MouseMove event, then we might get the next MouseMove
	//  event without ever seeing a Redraw or Idle.  That's because the
	//  MouseMove events are considered higher priority in the queue.
	// So, to keep response smooth, we effectively ignore all but one
	//  MouseMove event per Draw event.
	if (type == wxEVT_MOTION && m_iConsecutiveMousemoves > 1)
		return;

	mevent.flags = 0;
	wxCoord xpos, ypos;
	event1.GetPosition(&xpos, &ypos);
	mevent.pos.Set(xpos, ypos);

	if (event1.ControlDown())
		mevent.flags |= VT_CONTROL;

	if (event1.ShiftDown())
		mevent.flags |= VT_SHIFT;

	if (event1.AltDown())
		mevent.flags |= VT_ALT;

	// inform vtlib scene, which informs the engines
	vtGetScene()->OnMouse(mevent);
}

void vtGLCanvas::OnEraseBackground(wxEraseEvent& event)
{
	// Do nothing, to avoid flashing.
}

void vtGLCanvas::OnMouseCaptureLost(wxMouseCaptureLostEvent& event1)
{
	VTLOGCAP("MouseCaptureLost, capture -> false\n");
	m_bCapture = false;

	// When capture is lost, we won't get mouse events anymore.
	// That means we won't know when a mouse button goes up or down, so
	//  Enviro might think that a button is still down even when the focus
	//  comes back, when the button isn't down.
	// If we get this event, should we let the app know that any mouse
	//  buttons which were down are no longer down?  Not necessarily.
	//  They might in fact still be down. There is not a clear good solution.
}

void vtGLCanvas::OnIdle(wxIdleEvent &event)
{
	// standard continuous rendering
	if (m_bRunning)
#ifdef __WXMAC__
	{
		// Make sure the Graphics context of this thread is this window
		SetCurrent();

		// Render the Scene Graph
		vtGetScene()->DoUpdate();

		// Reset the number of mousemoves we've gotten since last redraw
		m_iConsecutiveMousemoves = 0;

		event.RequestMore();
	}
#else
		Refresh(false);
#endif
}

