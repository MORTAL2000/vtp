//
// UtilityLayer.cpp
//
// Copyright (c) 2001-2008 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Builder.h"
#include "UtilityLayer.h"
#include "ScaledView.h"

wxPen greenPen;
wxPen bluePen;
static bool g_bInitializedPens = false;

//////////////////////////////////////////////////////////////////////////

vtUtilityLayer::vtUtilityLayer() : vtLayer(LT_UTILITY)
{
	SetLayerFilename(_T("Untitled.osm"));

	if (!g_bInitializedPens)
	{
		g_bInitializedPens = true;
		greenPen.SetColour(25,128,0);
		bluePen.SetColour(25,25,200);
	}
}

bool vtUtilityLayer::GetExtent(DRECT &rect)
{
	if (m_Poles.empty())
		return false;

	GetPoleExtents(rect);

	return true;
}

void vtUtilityLayer::DrawLayer(wxDC *pDC, vtScaledView *pView)
{
	uint i;
	uint npoles = m_Poles.size();
	uint nlines = m_Lines.size();

	if (!npoles)
		return;

	pDC->SetPen(greenPen);
	pDC->SetBrush(*wxTRANSPARENT_BRUSH);

	if (m_proj.IsGeographic())
		m_size = pView->sdx(2E-4);	// ~20 meters, in degrees.
	else
		m_size = pView->sdx(20);	// 20 meters
	if (m_size > 5) m_size = 5;
	if (m_size < 1) m_size = 1;

	pDC->SetPen(bluePen);
	for (i = 0; i < npoles; i++)
	{
		// draw each Pole
		vtPole *pole = m_Poles[i];

/*		if (pole->IsSelected())
		{
			if (!bSel)
			{
				pDC->SetPen(bluePen);
				bSel = true;
			}
		}
		else
		{
			if (bSel)
			{
				pDC->SetPen(greenPen);
				bSel = false;
			}
		} */
		DrawPole(pDC, pView, pole);
	}
	pDC->SetPen(greenPen);
	DLine2 polyline;
	for (i = 0; i < nlines; i++)
	{
		vtLine *line = m_Lines[i];
		line->MakePolyline(polyline);
		pView->DrawPolyLine(pDC, polyline, false);
	}
}

void vtUtilityLayer::DrawPole(wxDC *pDC, vtScaledView *pView, vtPole *pole)
{
	wxPoint center;
	pView->screen(pole->m_p, center);

	pDC->DrawLine(center.x-m_size, center.y, center.x+m_size+1, center.y);
	pDC->DrawLine(center.x, center.y-m_size, center.x, center.y+m_size+1);
}

bool vtUtilityLayer::OnSave(bool progress_callback(int))
{
	return WriteOSM(GetLayerFilename().mb_str(wxConvUTF8));
}

bool vtUtilityLayer::OnLoad()
{
	wxString strExt = GetLayerFilename().AfterLast('.');

//	if (!strExt.CmpNoCase("utl"))
//		return ReadUTL(m_strFilename);
	return false;
}

void vtUtilityLayer::GetProjection(vtProjection &proj)
{
	proj = m_proj;
}

void vtUtilityLayer::SetProjection(const vtProjection &proj)
{
	vtUtilityMap::SetProjection(proj);
}

bool vtUtilityLayer::TransformCoords(vtProjection &proj)
{
	if (proj == m_proj)
		return true;

	return vtUtilityMap::TransformTo(proj);
}

bool vtUtilityLayer::AppendDataFrom(vtLayer *pL)
{
	// safety check
	if (pL->GetType() != LT_UTILITY)
		return false;

//	vtUtilityLayer *pFrom = (vtUtilityLayer *)pL;
	// TODO
	return true;
}

void vtUtilityLayer::Offset(const DPoint2 &delta)
{
	vtUtilityMap::Offset(delta);
}

void vtUtilityLayer::GetPropertyText(wxString &strIn)
{
	wxString str;
	str.Printf(_("Nodes (poles/towers): %d\n"), m_Poles.size());
	strIn += str;

	str.Printf(_("Lines: %d\n"), m_Lines.size());
	strIn += str;
}

void vtUtilityLayer::DeselectAll()
{
}

void vtUtilityLayer::InvertSelection()
{
}


