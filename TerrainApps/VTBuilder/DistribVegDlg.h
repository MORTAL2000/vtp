/////////////////////////////////////////////////////////////////////////////
// Name:        DistribVegDlg.h
// Author:      XX
// Created:     XX/XX/XX
// Copyright:   XX
/////////////////////////////////////////////////////////////////////////////

#ifndef __DistribVegDlg_H__
#define __DistribVegDlg_H__

#ifdef __GNUG__
    #pragma interface "DistribVegDlg.cpp"
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "VTBuilder_wdr.h"
#include "AutoDialog.h"

// WDR: class declarations

//----------------------------------------------------------------------------
// DistribVegDlg
//----------------------------------------------------------------------------

class DistribVegDlg: public AutoDialog
{
public:
    // constructors and destructors
    DistribVegDlg( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );

	float m_fSampling, m_fScarcity;

    // WDR: method declarations for DistribVegDlg
    
private:
    // WDR: member variable declarations for DistribVegDlg
    
private:
    // WDR: handler declarations for DistribVegDlg
	void OnInitDialog(wxInitDialogEvent& event);

private:
    DECLARE_EVENT_TABLE()
};




#endif
