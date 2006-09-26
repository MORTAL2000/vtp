//
// Name: LinearStructDlg.cpp
//
// Copyright (c) 2001-2006 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "LinearStructDlg.h"

#define VALUE_MIN  0.2f
#define VALUE_MAX  10.2f
#define SIZE_MIN  0.05f
#define SIZE_MAX  2.55f
#define BOTTOM_MIN  -4.0f
#define BOTTOM_MAX  9.0f
#define WIDTH_MIN   0.0f
#define WIDTH_MAX   10.0f
#define SLOPE_MIN   15
#define SLOPE_MAX   90

// WDR: class implementations

//----------------------------------------------------------------------------
// LinearStructureDlg
//----------------------------------------------------------------------------

// WDR: event table for LinearStructureDlg

BEGIN_EVENT_TABLE(LinearStructureDlg, AutoDialog)
	EVT_INIT_DIALOG (LinearStructureDlg::OnInitDialog)
	EVT_CHOICE( ID_LINEAR_STRUCTURE_STYLE, LinearStructureDlg::OnStyle )
	EVT_TEXT( ID_POST_HEIGHT_EDIT, LinearStructureDlg::OnTextEdit )
	EVT_TEXT( ID_POST_SPACING_EDIT, LinearStructureDlg::OnTextEdit )
	EVT_TEXT( ID_POST_SIZE_EDIT, LinearStructureDlg::OnTextEdit )
	EVT_TEXT( ID_CONN_WIDTH_EDIT, LinearStructureDlg::OnTextEdit )
	EVT_TEXT( ID_CONN_TOP_EDIT, LinearStructureDlg::OnTextEdit )
	EVT_TEXT( ID_CONN_BOTTOM_EDIT, LinearStructureDlg::OnTextEdit )
	EVT_SLIDER( ID_POST_HEIGHT_SLIDER, LinearStructureDlg::OnSlider )
	EVT_SLIDER( ID_POST_SPACING_SLIDER, LinearStructureDlg::OnSlider )
	EVT_SLIDER( ID_POST_SIZE_SLIDER, LinearStructureDlg::OnSlider )
	EVT_SLIDER( ID_CONN_WIDTH_SLIDER, LinearStructureDlg::OnSlider )
	EVT_SLIDER( ID_CONN_TOP_SLIDER, LinearStructureDlg::OnSlider )
	EVT_SLIDER( ID_CONN_BOTTOM_SLIDER, LinearStructureDlg::OnSlider )
	EVT_CHOICE( ID_POST_TYPE, LinearStructureDlg::OnPostType )
	EVT_CHOICE( ID_CONN_TYPE, LinearStructureDlg::OnConnType )
	EVT_CHOICE( ID_CHOICE_EXTENSION, LinearStructureDlg::OnExtension )
	EVT_TEXT( ID_SLOPE, LinearStructureDlg::OnTextEdit )
	EVT_SLIDER( ID_SLOPE_SLIDER, LinearStructureDlg::OnSlider )
	EVT_CHECKBOX( ID_CONSTANT_TOP, LinearStructureDlg::OnConstantTop )
END_EVENT_TABLE()

LinearStructureDlg::LinearStructureDlg( wxWindow *parent, wxWindowID id, const wxString &title,
	const wxPoint &position, const wxSize& size, long style ) :
	AutoDialog( parent, id, title, position, size, style )
{
	LinearStructDialogFunc( this, TRUE );
	m_bSetting = false;

	m_iStyle = 0;
	m_param.Defaults();

	AddValidator(ID_LINEAR_STRUCTURE_STYLE, &m_iStyle);

	AddValidator(ID_POST_HEIGHT_SLIDER, &m_iPostHeight);
	AddValidator(ID_POST_SPACING_SLIDER, &m_iPostSpacing);
	AddValidator(ID_POST_SIZE_SLIDER, &m_iPostSize);
	AddValidator(ID_CONN_WIDTH_SLIDER, &m_iConnWidth);
	AddValidator(ID_CONN_TOP_SLIDER, &m_iConnTop);
	AddValidator(ID_CONN_BOTTOM_SLIDER, &m_iConnBottom);
	AddValidator(ID_SLOPE_SLIDER, &m_iSlope);
	AddValidator(ID_CONSTANT_TOP, &m_param.m_bConstantTop);

	AddNumValidator(ID_POST_HEIGHT_EDIT, &m_param.m_fPostHeight, 2);
	AddNumValidator(ID_POST_SPACING_EDIT, &m_param.m_fPostSpacing, 2);
	AddNumValidator(ID_POST_SIZE_EDIT, &m_param.m_fPostWidth, 2);
	AddNumValidator(ID_CONN_WIDTH_EDIT, &m_param.m_fConnectWidth, 2);
	AddNumValidator(ID_CONN_TOP_EDIT, &m_param.m_fConnectTop, 2);
	AddNumValidator(ID_CONN_BOTTOM_EDIT, &m_param.m_fConnectBottom, 2);
	AddNumValidator(ID_SLOPE, &m_param.m_iConnectSlope);

	// NB -- these must match the FS_ enum in order
	GetStyle()->Clear();
	GetStyle()->Append(_("Wooden posts, wire"));
	GetStyle()->Append(_("Metal posts, wire"));
	GetStyle()->Append(_("Metal poles, chain-link"));
	GetStyle()->Append(_("Security fence"));
	GetStyle()->Append(_("Dry-stone wall"));
	GetStyle()->Append(_("Stone wall"));
	GetStyle()->Append(_("Privet hedge"));
	GetStyle()->Append(_("Berm"));
	GetStyle()->Append(_("Railing (Pipe)"));
	GetStyle()->Append(_("Railing (Wire)"));
	GetStyle()->Append(_("Railing (EU)"));
	GetStyle()->Append(_("(custom)"));

	GetPostType()->Clear();
	GetPostType()->Append(_("none"));
	GetPostType()->Append(_("wood"));
	GetPostType()->Append(_("steel"));

	GetConnType()->Clear();
	GetConnType()->Append(_("none"));
	GetConnType()->Append(_("wire"));
	GetConnType()->Append(_("chain-link"));
	GetConnType()->Append(_("drystone"));
	GetConnType()->Append(_("stone"));
	GetConnType()->Append(_("privet"));
	GetConnType()->Append(_("grass"));
	GetConnType()->Append(_("railing_wire"));
	GetConnType()->Append(_("railing_eu"));
	GetConnType()->Append(_("railing_pipe"));
}

void LinearStructureDlg::SetOptions(const vtLinearParams &param)
{
	m_param = param;

	ValuesToSliders();
	UpdateTypes();
	m_bSetting = true;
	TransferDataToWindow();
	m_bSetting = false;
	UpdateEnabling();

	OnSetOptions(m_param);
}

void LinearStructureDlg::UpdateTypes()
{
	wxString ws(m_param.m_PostType, wxConvUTF8);
	GetPostType()->SetStringSelection(ws);

	ws = wxString(m_param.m_ConnectType, wxConvUTF8);
	GetConnType()->SetStringSelection(ws);

	vtString str = m_param.m_PostExtension;
	if (str == "none")
		GetExtension()->SetSelection(0);
	if (str == "left")
		GetExtension()->SetSelection(1);
	if (str == "right")
		GetExtension()->SetSelection(2);
	if (str == "double")
		GetExtension()->SetSelection(3);
}

void LinearStructureDlg::UpdateEnabling()
{
	bool bHasPosts = (m_param.m_PostType != "none");
	bool bHasConn = (m_param.m_ConnectType != "none");

	GetPostSpacingEdit()->Enable(bHasPosts);
	GetPostSpacingSlider()->Enable(bHasPosts);
	GetPostHeightEdit()->Enable(bHasPosts);
	GetPostHeightSlider()->Enable(bHasPosts);
	GetPostSizeEdit()->Enable(bHasPosts);
	GetPostSizeSlider()->Enable(bHasPosts);

	GetConnWidthEdit()->Enable(bHasConn);
	GetConnWidthSlider()->Enable(bHasConn);
	GetConnTopEdit()->Enable(bHasConn);
	GetConnTopSlider()->Enable(bHasConn);
	GetConnBottomEdit()->Enable(bHasConn);
	GetConnBottomSlider()->Enable(bHasConn);
	GetSlope()->Enable(bHasConn);
	GetSlopeSlider()->Enable(bHasConn);
	GetConstantTop()->Enable(bHasConn);
}

void LinearStructureDlg::GuessStyle()
{
	// Go through the known styles and see if any match the current params
	vtLinearParams p;
	for (int i = 0; i < FS_TOTAL; i++)
	{
		p.ApplyStyle((vtLinearStyle) i);
		if (m_param == p)
		{
			m_iStyle = i;
			return;
		}
	}
	m_iStyle = FS_TOTAL;	// Custom
}

// WDR: handler implementations for LinearStructureDlg

void LinearStructureDlg::OnConstantTop( wxCommandEvent &event )
{
	TransferDataFromWindow();
	OnSetOptions(m_param);
}

void LinearStructureDlg::OnInitDialog(wxInitDialogEvent& event)
{
	ValuesToSliders();
	GuessStyle();
	UpdateTypes();
	m_bSetting = true;
	TransferDataToWindow();
	m_bSetting = false;
	UpdateEnabling();
}

void LinearStructureDlg::OnConnType( wxCommandEvent &event )
{
	if (m_bSetting) return;

	wxString ws = GetConnType()->GetStringSelection();
	m_param.m_ConnectType = ws.mb_str(wxConvUTF8);
	UpdateEnabling();

	GuessStyle();
	m_bSetting = true;
	TransferDataToWindow();
	m_bSetting = false;
	OnSetOptions(m_param);
}

void LinearStructureDlg::OnPostType( wxCommandEvent &event )
{
	if (m_bSetting) return;

	wxString ws = GetPostType()->GetStringSelection();
	m_param.m_PostType = ws.mb_str(wxConvUTF8);
	UpdateEnabling();

	GuessStyle();
	m_bSetting = true;
	TransferDataToWindow();
	m_bSetting = false;
	OnSetOptions(m_param);
}

void LinearStructureDlg::OnExtension( wxCommandEvent &event )
{
	if (m_bSetting) return;

	int val = GetExtension()->GetSelection();
	if (val == 0)
		m_param.m_PostExtension = "none";
	if (val == 1)
		m_param.m_PostExtension = "left";
	if (val == 2)
		m_param.m_PostExtension = "right";
	if (val == 3)
		m_param.m_PostExtension = "double";

	GuessStyle();
	m_bSetting = true;
	TransferDataToWindow();
	m_bSetting = false;
	OnSetOptions(m_param);
}

void LinearStructureDlg::OnStyle( wxCommandEvent &event )
{
	if (m_bSetting) return;

	TransferDataFromWindow();
	vtLinearStyle style = (vtLinearStyle) m_iStyle;
	if (style != FS_TOTAL)
	{
		m_param.ApplyStyle(style);
		UpdateTypes();
		ValuesToSliders();
		m_bSetting = true;
		TransferDataToWindow();
		m_bSetting = false;
		OnSetOptions(m_param);
		UpdateEnabling();
	}
}

void LinearStructureDlg::OnSlider( wxCommandEvent &event )
{
	if (m_bSetting) return;

	TransferDataFromWindow();
	int id = event.GetId();
	SlidersToValues(id);
	GuessStyle();
	m_bSetting = true;
	TransferDataToWindow();
	m_bSetting = false;
	OnSetOptions(m_param);
}

void LinearStructureDlg::OnTextEdit( wxCommandEvent &event )
{
	if (m_bSetting) return;

	TransferDataFromWindow();
	m_param.m_fPostDepth = m_param.m_fPostWidth;
	ValuesToSliders();
	GuessStyle();
	m_bSetting = true;
	TransferDataToWindow();
	m_bSetting = false;
	OnSetOptions(m_param);
}

void LinearStructureDlg::SlidersToValues(int which)
{
	switch (which)
	{
	case ID_POST_SPACING_SLIDER:
		m_param.m_fPostSpacing   = VALUE_MIN + m_iPostSpacing * (VALUE_MAX - VALUE_MIN) / 100.0f;
		break;
	case ID_POST_HEIGHT_SLIDER:
		m_param.m_fPostHeight	= VALUE_MIN + m_iPostHeight *  (VALUE_MAX - VALUE_MIN) / 100.0f;
		break;
	case ID_POST_SIZE_SLIDER:
		m_param.m_fPostWidth	 = VALUE_MIN + m_iPostSize *	(VALUE_MAX - VALUE_MIN) / 100.0f;
		m_param.m_fPostDepth	 = VALUE_MIN + m_iPostSize *	(VALUE_MAX - VALUE_MIN) / 100.0f;
		break;
	case ID_CONN_TOP_SLIDER:
		m_param.m_fConnectTop	= VALUE_MIN + m_iConnTop *	 (VALUE_MAX - VALUE_MIN) / 100.0f;
		break;
	case ID_CONN_BOTTOM_SLIDER:
		m_param.m_fConnectBottom = BOTTOM_MIN + m_iConnBottom * (BOTTOM_MAX - BOTTOM_MIN) / 100.0f;
		break;
	case ID_CONN_WIDTH_SLIDER:
		m_param.m_fConnectWidth  = WIDTH_MIN + m_iConnWidth *   (WIDTH_MAX - WIDTH_MIN) / 100.0f;
		break;
	case ID_SLOPE_SLIDER:
		m_param.m_iConnectSlope  = SLOPE_MIN + m_iSlope *   (SLOPE_MAX - SLOPE_MIN) / 100.0f;
		break;
	}
}

void LinearStructureDlg::ValuesToSliders()
{
	m_iPostHeight =  (int) ((m_param.m_fPostHeight - VALUE_MIN) /	(VALUE_MAX - VALUE_MIN) * 100.0f);
	m_iPostSpacing = (int) ((m_param.m_fPostSpacing - VALUE_MIN) /   (VALUE_MAX - VALUE_MIN) * 100.0f);
	m_iPostSize =	 (int) ((m_param.m_fPostWidth - VALUE_MIN) /	 (VALUE_MAX - VALUE_MIN) * 100.0f);
	m_iConnTop =	 (int) ((m_param.m_fConnectTop - VALUE_MIN) /	(VALUE_MAX - VALUE_MIN) * 100.0f);
	m_iConnBottom =  (int) ((m_param.m_fConnectBottom - BOTTOM_MIN) / (BOTTOM_MAX - BOTTOM_MIN) * 100.0f);
	m_iConnWidth =   (int) ((m_param.m_fConnectWidth - WIDTH_MIN) /  (WIDTH_MAX - WIDTH_MIN) * 100.0f);
	m_iSlope =		 (int) ((m_param.m_iConnectSlope - SLOPE_MIN) /  (float)(SLOPE_MAX - SLOPE_MIN) * 100.0f);
}

