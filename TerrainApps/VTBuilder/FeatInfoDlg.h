//
// Name:		FeatInfoDlg.h
//
// Copyright (c) 2002 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef __FeatInfoDlg_H__
#define __FeatInfoDlg_H__

#ifdef __GNUG__
	#pragma interface "FeatInfoDlg.cpp"
#endif

#include "VTBuilder_wdr.h"
#include "AutoDialog.h"

class vtFeatures;

// WDR: class declarations

//----------------------------------------------------------------------------
// FeatInfoDlg
//----------------------------------------------------------------------------

class FeatInfoDlg: public AutoDialog
{
public:
	// constructors and destructors
	FeatInfoDlg( wxWindow *parent, wxWindowID id, const wxString &title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE );

	void SetFeatureSet(vtFeatures *pFeatures);
	void Clear();
	void ShowSelected();
	void ShowPicked();
	void ShowAll();
	void ShowFeature(int iFeat);

	// WDR: method declarations for FeatInfoDlg
	wxStaticText* GetTextVertical()  { return (wxStaticText*) FindWindow( ID_TEXT_VERTICAL ); }
	wxButton* GetDelHigh()  { return (wxButton*) FindWindow( ID_DEL_HIGH ); }
	wxChoice* GetChoiceVertical()  { return (wxChoice*) FindWindow( ID_CHOICE_VERTICAL ); }
	wxChoice* GetChoiceShow()  { return (wxChoice*) FindWindow( ID_CHOICE_SHOW ); }
	wxListCtrl* GetList()  { return (wxListCtrl*) FindWindow( ID_LIST ); }
	
private:
	// WDR: member variable declarations for FeatInfoDlg
	vtFeatures *m_pFeatures;
	int	 m_iShow;
	int	 m_iVUnits;

private:
	// WDR: handler declarations for FeatInfoDlg
	void OnDeleteHighlighted( wxCommandEvent &event );
	void OnChoiceVertical( wxCommandEvent &event );
	void OnChoiceShow( wxCommandEvent &event );
	void OnListRightClick( wxListEvent &event );
	void OnItemSelected( wxListEvent &event );
	void OnInitDialog(wxInitDialogEvent& event);

private:
	DECLARE_EVENT_TABLE()
};




#endif
