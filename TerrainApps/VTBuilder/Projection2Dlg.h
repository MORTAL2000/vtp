/////////////////////////////////////////////////////////////////////////////
// Name:        Projection2Dlg.h
// Author:      XX
// Created:     XX/XX/XX
// Copyright:   XX
/////////////////////////////////////////////////////////////////////////////

#ifndef __Projection2Dlg_H__
#define __Projection2Dlg_H__

#ifdef __GNUG__
    #pragma interface "Projection2Dlg.cpp"
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "VTBuilder_wdr.h"
#include "AutoDialog.h"
#include "vtdata/Projections.h"

#ifndef __ProjectionDlg_H__
enum ProjType
{
    PT_GEO,
    PT_UTM,
    PT_ALBERS,
    PT_LAMBERT
};
#endif

// WDR: class declarations

//----------------------------------------------------------------------------
// Projection2Dlg
//----------------------------------------------------------------------------

class Projection2Dlg: public AutoDialog
{
public:
    // constructors and destructors
    Projection2Dlg( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );
    
    // WDR: method declarations for Projection2Dlg
    wxListCtrl* GetProjparam()  { return (wxListCtrl*) FindWindow( ID_PROJPARAM ); }
    wxChoice* GetHorizchoice()  { return (wxChoice*) FindWindow( ID_HORUNITS ); }
    wxChoice* GetZonechoice()  { return (wxChoice*) FindWindow( ID_ZONE ); }
    wxChoice* GetDatumchoice()  { return (wxChoice*) FindWindow( ID_DATUM ); }
    wxChoice* GetProjchoice()  { return (wxChoice*) FindWindow( ID_PROJ ); }
    void SetProjection(vtProjection &proj);
    void GetProjection(vtProjection &proj);
    void SetUIFromProjection();
    void SetProjectionUI(ProjType type);
    void UpdateControlStatus();
    void DisplayProjectionSpecificParams();
    void AskStatePlane();

    int         m_iDatum;
    int         m_iZone;
    vtProjection    m_proj;

private:
    // WDR: member variable declarations for Projection2Dlg
    ProjType    m_eProj;
    int         m_iProj;
    int         m_iUnits;
    wxListCtrl  *m_pParamCtrl;
    wxChoice    *m_pZoneCtrl;
    wxChoice    *m_pHorizCtrl;
    wxChoice    *m_pDatumCtrl;
    wxChoice    *m_pProjCtrl;

    bool m_bInitializedUI;

private:
    // WDR: handler declarations for Projection2Dlg
    void OnDatum( wxCommandEvent &event );
    void OnItemRightClick( wxListEvent &event );
    void OnHorizUnits( wxCommandEvent &event );
    void OnZone( wxCommandEvent &event );
    void OnSetStatePlane( wxCommandEvent &event );
    void OnProjChoice( wxCommandEvent &event );
    void OnInitDialog(wxInitDialogEvent& event);

private:
    DECLARE_EVENT_TABLE()
};


#endif

