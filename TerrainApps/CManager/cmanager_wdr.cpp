//------------------------------------------------------------------------------
// Source code generated by wxDesigner from file: cmanager.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "cmanager_wdr.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "cmanager_wdr.h"

#include <wx/intl.h>

// Implement window functions

wxSizer *SceneGraphFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxTreeCtrl *item1 = new wxTreeCtrl( parent, ID_SCENETREE, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxSUNKEN_BORDER );
    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxBoxSizer *item2 = new wxBoxSizer( wxHORIZONTAL );

    wxCheckBox *item3 = new wxCheckBox( parent, ID_ENABLED, _("Enabled"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item4 = new wxButton( parent, ID_ZOOMTO, _("Zoom To"), wxDefaultPosition, wxSize(60,-1), 0 );
    item2->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item5 = new wxButton( parent, ID_REFRESH, _("Refresh"), wxDefaultPosition, wxSize(55,-1), 0 );
    item2->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item2, 0, wxALIGN_CENTER|wxALL, 0 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *PropDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxStaticBox *item2 = new wxStaticBox( parent, -1, _("Item") );
    wxStaticBoxSizer *item1 = new wxStaticBoxSizer( item2, wxVERTICAL );

    wxBoxSizer *item3 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item4 = new wxStaticText( parent, ID_TEXT, _("Item Name:"), wxDefaultPosition, wxSize(60,-1), 0 );
    item3->Add( item4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item5 = new wxTextCtrl( parent, ID_ITEM, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item5, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item6 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item7 = new wxStaticText( parent, ID_TEXT, _("Type:"), wxDefaultPosition, wxSize(60,-1), 0 );
    item6->Add( item7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxString *strs8 = (wxString*) NULL;
    wxChoice *item8 = new wxChoice( parent, ID_TYPECHOICE, wxDefaultPosition, wxSize(100,-1), 0, strs8, 0 );
    item6->Add( item8, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item1->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item9 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, _("Tags:"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item11 = new wxButton( parent, ID_ADDTAG, _("&Add"), wxDefaultPosition, wxSize(38,-1), 0 );
    item9->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item12 = new wxButton( parent, ID_REMOVETAG, _("&Remove"), wxDefaultPosition, wxSize(62,-1), 0 );
    item9->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item13 = new wxButton( parent, ID_EDITTAG, _("&Edit"), wxDefaultPosition, wxSize(42,-1), 0 );
    item9->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

    item1->Add( item9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxListCtrl *item14 = new wxListCtrl( parent, ID_TAGLIST, wxDefaultPosition, wxSize(160,120), wxLC_REPORT|wxSUNKEN_BORDER );
    item1->Add( item14, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item1, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *ModelDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxStaticBox *item2 = new wxStaticBox( parent, -1, _("Model") );
    wxStaticBoxSizer *item1 = new wxStaticBoxSizer( item2, wxVERTICAL );

    wxBoxSizer *item3 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item4 = new wxStaticText( parent, ID_TEXT, _("Filename:"), wxDefaultPosition, wxDefaultSize, 0 );
    item3->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item5 = new wxTextCtrl( parent, ID_FILENAME, wxT(""), wxDefaultPosition, wxSize(160,-1), 0 );
    item3->Add( item5, 1, wxALIGN_CENTER|wxALL, 5 );

    item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item6 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item7 = new wxStaticText( parent, ID_TEXT, _("Visible at distance:"), wxDefaultPosition, wxDefaultSize, 0 );
    item6->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item8 = new wxTextCtrl( parent, ID_DISTANCE, wxT(""), wxDefaultPosition, wxSize(60,-1), wxTE_PROCESS_ENTER );
    item6->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    item1->Add( item6, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item9 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, _("Scale:"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_SCALE, wxT(""), wxDefaultPosition, wxSize(60,-1), wxTE_PROCESS_ENTER );
    item9->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item12 = new wxStaticText( parent, ID_TEXT, _("(meters/unit)"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );

    item1->Add( item9, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item13 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item14 = new wxStaticText( parent, ID_TEXT, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
    item13->Add( item14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxTextCtrl *item15 = new wxTextCtrl( parent, ID_STATUS, wxT(""), wxDefaultPosition, wxSize(80,40), wxTE_MULTILINE );
    item13->Add( item15, 1, wxALIGN_CENTER, 5 );

    item1->Add( item13, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

wxSizer *TagDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item2 = new wxStaticText( parent, ID_TEXT, _("Tag Name"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs3 = (wxString*) NULL;
    wxChoice *item3 = new wxChoice( parent, ID_TAGNAME, wxDefaultPosition, wxSize(100,-1), 0, strs3, 0 );
    item1->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxBoxSizer *item4 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item5 = new wxStaticText( parent, ID_TEXT, _("Tag Value"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item6 = new wxTextCtrl( parent, ID_TAGTEXT, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item4->Add( item6, 1, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

    wxBoxSizer *item7 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item8 = new wxButton( parent, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->SetDefault();
    item7->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    item7->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item7, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxBOTTOM, 5 );

    if (set_sizer)
    {
        parent->SetAutoLayout( TRUE );
        parent->SetSizer( item0 );
        if (call_fit)
        {
            item0->Fit( parent );
            item0->SetSizeHints( parent );
        }
    }
    
    return item0;
}

// Implement menubar functions

// Implement toolbar functions

// Implement bitmap functions


// End of generated file
