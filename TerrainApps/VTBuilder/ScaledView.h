//
// ScaledView.h
//
// Copyright (c) 2001-2013 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef SCALEDVIEWH
#define SCALEDVIEWH

#include "vtdata/MathTypes.h"
#include "ogr_geometry.h"

class vtScaledView : public wxScrolledWindow
{
public:
	vtScaledView(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL, const wxString& name = _T(""));

	void SetScale(double scale);
	double GetScale();

	void ZoomToPoint(const DPoint2 &p);
	void ZoomToRect(const DRECT &geo_rect, float margin);
	void ZoomOutToRect(const DRECT &geo_rect);

	wxRect WorldToCanvas(const DRECT &r);
	DRECT WorldToCanvasD(const DRECT &r);
	wxRect WorldToWindow(const DRECT &r);
	DRECT CanvasToWorld(const wxRect &r);

	void GetCanvasPosition(const wxMouseEvent &event, wxPoint &pos);
	DRECT GetWorldRect();
	wxRect PointsToRect(const wxPoint &p1, const wxPoint &p2);

	// transform object space -> screen space
	int	sx(double x) { return (int)(x*m_dScale - m_limits.left); }
	int	sy(double y) { return (int)(-y*m_dScale - m_limits.top); }
	double	sxD(double x) { return x*m_dScale - m_limits.left; }
	double	syD(double y) { return -y*m_dScale - m_limits.top; }
	void screen(const DPoint2 &p, wxPoint &sp) const
	{
		sp.x = (int)(p.x*m_dScale - m_limits.left);
		sp.y = (int)(-p.y*m_dScale - m_limits.top);
	}
	void screen(const OGRPoint *p, wxPoint &sp) const
	{
		sp.x = (int)(p->getX()*m_dScale - m_limits.left);
		sp.y = (int)(-(p->getY())*m_dScale - m_limits.top);
	}
	// transform object space -> screen space (relative delta)
	int	sdx(double x) { return (int)(x*m_dScale); }
	int	sdy(double y) { return (int)(-y*m_dScale); }

	wxPoint screen_delta(const DPoint2 &p) const
	{
		wxPoint sp;
		sp.x = (int)(p.x*m_dScale);
		sp.y = (int)(-p.y*m_dScale);
		return sp;
	}

	// transform screen space -> object space
	double ox(int x) { return (x + m_limits.left) / m_dScale; }
	double oy(int y) { return -(y + m_limits.top) / m_dScale; }
	void object(const wxPoint &sp, DPoint2 &p) const
	{
		p.x = (sp.x + m_limits.left) / m_dScale;
		p.y = -(sp.y + m_limits.top) / m_dScale;
	}

	// transform screen space -> object space (relative delta)
	double odx(int x) { return x/m_dScale; }
	double ody(int y) { return -y/m_dScale; }

	int ProjectPolyline(wxDC *pDC, const DLine2 &dline, bool bClose);
	void DrawLine(wxDC *pDC, const DPoint2 &p0, const DPoint2 &p1);
	void DrawPolyLine(wxDC *pDC, const DLine2 &line, bool bClose);
	void DrawDoubleLine(wxDC *pDC, const DLine2 &line, const DLine2 &width);
	void DrawPolygon(wxDC *pDC, const DPolygon2 &poly, bool bFill);

	void DrawOGRLinearRing(wxDC *pDC, const OGRLinearRing *line, bool bCircles);
	void DrawOGRPolygon(wxDC *pDC, const OGRPolygon &poly, bool bFill, bool bCircles);
	void DrawDPolygon2(wxDC *pDC, const DPolygon2 &poly, bool bFill, bool bCircles);

protected:
	void UpdateRanges();

	double	m_dScale;	// pixels per UTM meter/pixel per degree
	DRECT	m_limits;	// allowed range of m_offset
};

#define SCREENBUF_SIZE 32000
extern wxPoint g_screenbuf[SCREENBUF_SIZE];

#endif
