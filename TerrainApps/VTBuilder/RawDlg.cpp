//
// Name: RawDlg.cpp
//
// Copyright (c) 2001-2004 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifdef __GNUG__
	#pragma implementation "RawDlg.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "RawDlg.h"
#include "Projection2Dlg.h"
#include "ExtentDlg.h"

// WDR: class implementations

//----------------------------------------------------------------------------
// RawDlg
//----------------------------------------------------------------------------

// WDR: event table for RawDlg

BEGIN_EVENT_TABLE(RawDlg,AutoDialog)
	EVT_RADIOBUTTON( ID_EXT_SPACING, RawDlg::OnRadio )
	EVT_RADIOBUTTON( ID_EXT_EXACT, RawDlg::OnRadio )
	EVT_RADIOBUTTON( ID_CRS_SIMPLE, RawDlg::OnRadio )
	EVT_RADIOBUTTON( ID_CRS_CURRENT, RawDlg::OnRadio )
	EVT_RADIOBUTTON( ID_CRS_EXACT, RawDlg::OnRadio )
	EVT_BUTTON( ID_EXTENTS, RawDlg::OnExtents )
	EVT_BUTTON( ID_CRS, RawDlg::OnCRS )
END_EVENT_TABLE()

RawDlg::RawDlg( wxWindow *parent, wxWindowID id, const wxString &title,
		const wxPoint& pos, const wxSize& size, long style ) :
	AutoDialog(parent, id, title, pos, size, style)
{
	m_bExtSpacing = true;
	m_bExtExact = false;

	m_bCrsSimple = true;
	m_bCrsCurrent = false;
	m_bCrsExact = false;

	RawDialogFunc( this, TRUE );
}

// WDR: handler implementations for RawDlg

void RawDlg::OnExtents( wxCommandEvent &event )
{
	ExtentDlg dlg(NULL, -1, _T("Elevation Grid Extents"));
	dlg.SetArea(m_extents, (m_proj.IsGeographic() != 0));
	if (dlg.ShowModal() == wxID_OK)
		m_extents = dlg.m_area;
}

void RawDlg::OnCRS( wxCommandEvent &event )
{
	Projection2Dlg dlg(NULL, -1, _T("Please indicate CRS"));
	dlg.SetProjection(m_proj);

	if (dlg.ShowModal() == wxID_OK)
		dlg.GetProjection(m_proj);
}

void RawDlg::OnRadio( wxCommandEvent &event )
{
	TransferDataFromWindow();
	UpdateEnabling();
	UpdateExtents();
	UpdateProjection();
}

void RawDlg::OnInitDialog(wxInitDialogEvent& event)
{
	AddNumValidator(ID_BYTES, &m_iBytes);
	AddNumValidator(ID_WIDTH, &m_iWidth);
	AddNumValidator(ID_HEIGHT, &m_iHeight);
	AddNumValidator(ID_VUNITS, &m_fVUnits);
	AddNumValidator(ID_SPACING, &m_fSpacing);
	AddValidator(ID_BIG_ENDIAN, &m_bBigEndian);

	AddValidator(ID_EXT_SPACING, &m_bExtSpacing);
	AddValidator(ID_EXT_EXACT, &m_bExtExact);

	AddValidator(ID_CRS_SIMPLE, &m_bCrsSimple);
	AddValidator(ID_CRS_CURRENT, &m_bCrsCurrent);
	AddValidator(ID_CRS_EXACT, &m_bCrsExact);

	UpdateEnabling();
	UpdateExtents();
	UpdateProjection();

	wxDialog::OnInitDialog(event);  // calls TransferDataToWindow()
}

void RawDlg::UpdateEnabling()
{
	GetSpacing()->Enable(m_bExtSpacing);
	GetExtents()->Enable(m_bExtExact);

	GetCrs()->Enable(m_bCrsExact);
}

void RawDlg::UpdateExtents()
{
	if (m_bExtSpacing)
	{
		m_extents.left = 0;
		m_extents.bottom = 0;
		m_extents.right = m_iWidth * m_fSpacing;
		m_extents.top = m_iHeight * m_fSpacing;
	}
}

void RawDlg::UpdateProjection()
{
	if (m_bCrsSimple)
		m_proj.SetProjectionSimple(true, 1, EPSG_DATUM_WGS84);
	if (m_bCrsCurrent)
		m_proj = m_original;
}


