//------------------------------------------------------------------------------
// Source code generated by wxDesigner from file: vtui.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "vtui_wdr.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "vtui_wdr.h"

const int ID_TEXT = 10000;

#include <wx/intl.h>

// Euro sign hack of the year
#if wxUSE_UNICODE
    #define __WDR_EURO__ wxT("\u20ac")
#else
    #if defined(__WXMAC__)
        #define __WDR_EURO__ wxT("\xdb")
    #elif defined(__WXMSW__)
        #define __WDR_EURO__ wxT("\x80")
    #else
        #define __WDR_EURO__ wxT("\xa4")
    #endif
#endif

// Implement window functions

wxSizer *BuildingDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );

    wxBoxSizer *item2 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item3 = new wxStaticText( parent, ID_TEXT, _("Building Levels"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs4 = (wxString*) NULL;
    wxListBox *item4 = new wxListBox( parent, ID_LEVEL, wxDefaultPosition, wxSize(60,100), 0, strs4, wxLB_SINGLE );
    item2->Add( item4, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxFlexGridSizer *item5 = new wxFlexGridSizer( 2, 0, 0 );

    wxButton *item6 = new wxButton( parent, ID_LEVEL_COPY, _("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
    item6->Enable( false );
    item5->Add( item6, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item7 = new wxButton( parent, ID_LEVEL_DEL, _("Del"), wxDefaultPosition, wxDefaultSize, 0 );
    item7->Enable( false );
    item5->Add( item7, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item8 = new wxButton( parent, ID_LEVEL_UP, _("Up"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, ID_LEVEL_DOWN, _("Down"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    item2->Add( item5, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT, 5 );

    wxStaticLine *item10 = new wxStaticLine( parent, ID_LINE1, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item2->Add( item10, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxBoxSizer *item11 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item12 = new wxButton( parent, ID_EDITHEIGHTS, _("Baseline Editor"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item13 = new wxButton( parent, ID_SET_ROOF_TYPE, _("Set Roof Type"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

    item2->Add( item11, 0, wxALIGN_CENTER, 5 );

    item1->Add( item2, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxStaticBox *item15 = new wxStaticBox( parent, -1, _("Level Properties") );
    wxStaticBoxSizer *item14 = new wxStaticBoxSizer( item15, wxVERTICAL );

    wxBoxSizer *item16 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item17 = new wxStaticText( parent, ID_TEXT, _("Stories:"), wxDefaultPosition, wxDefaultSize, 0 );
    item16->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSpinCtrl *item18 = new wxSpinCtrl( parent, ID_STORIES, wxT("0"), wxDefaultPosition, wxSize(60,-1), 0, 0, 100, 0 );
    item16->Add( item18, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item14->Add( item16, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item19 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item20 = new wxStaticText( parent, ID_TEXT, _("Story Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item21 = new wxTextCtrl( parent, ID_STORY_HEIGHT, wxT(""), wxDefaultPosition, wxSize(60,-1), 0 );
    item19->Add( item21, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxStaticText *item22 = new wxStaticText( parent, ID_TEXT, _("meters"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item22, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item14->Add( item19, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item23 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item24 = new wxStaticText( parent, ID_TEXT, _("Material:"), wxDefaultPosition, wxDefaultSize, 0 );
    item23->Add( item24, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item25 = new wxTextCtrl( parent, ID_MATERIAL1, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item23->Add( item25, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item26 = new wxButton( parent, ID_SET_MATERIAL, _("Set"), wxDefaultPosition, wxDefaultSize, 0 );
    item23->Add( item26, 0, wxALIGN_CENTER|wxALL, 5 );

    item14->Add( item23, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item27 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item28 = new wxStaticText( parent, ID_TEXT, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
    item27->Add( item28, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticBitmap *item29 = new wxStaticBitmap( parent, ID_COLOR1, vtuiBitmapsFunc( 0 ), wxDefaultPosition, wxSize(32,18) );
    item27->Add( item29, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item30 = new wxButton( parent, ID_SET_COLOR, _("Set"), wxDefaultPosition, wxDefaultSize, 0 );
    item27->Add( item30, 0, wxALIGN_CENTER|wxALL, 5 );

    item14->Add( item27, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item31 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item32 = new wxStaticText( parent, ID_TEXT, _("Edge Slopes:"), wxDefaultPosition, wxDefaultSize, 0 );
    item31->Add( item32, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item33 = new wxTextCtrl( parent, ID_EDGE_SLOPES, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item31->Add( item33, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item34 = new wxButton( parent, ID_SET_EDGE_SLOPES, _("Set"), wxDefaultPosition, wxDefaultSize, 0 );
    item31->Add( item34, 0, wxALIGN_CENTER|wxALL, 5 );

    item14->Add( item31, 0, wxALIGN_CENTER, 5 );

    item1->Add( item14, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    item0->Add( item1, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxBoxSizer *item35 = new wxBoxSizer( wxHORIZONTAL );

    item35->Add( 80, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item36 = new wxButton( parent, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item35->Add( item36, 0, wxALIGN_CENTER|wxALL, 5 );

    item35->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item37 = new wxButton( parent, ID_EDGES, _("Edges >>"), wxDefaultPosition, wxDefaultSize, 0 );
    item35->Add( item37, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item35, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

wxSizer *g_pTopGroup;
wxSizer *g_pEdgeGroup;
wxSizer *BuildingEdgesDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );
    g_pTopGroup = item1;

    wxBoxSizer *item2 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item3 = new wxStaticText( parent, ID_TEXT, _("Building Levels"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs4 = (wxString*) NULL;
    wxListBox *item4 = new wxListBox( parent, ID_LEVEL, wxDefaultPosition, wxSize(60,100), 0, strs4, wxLB_SINGLE );
    item2->Add( item4, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxFlexGridSizer *item5 = new wxFlexGridSizer( 2, 0, 0 );

    wxButton *item6 = new wxButton( parent, ID_LEVEL_COPY, _("Copy"), wxDefaultPosition, wxDefaultSize, 0 );
    item6->Enable( false );
    item5->Add( item6, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item7 = new wxButton( parent, ID_LEVEL_DEL, _("Del"), wxDefaultPosition, wxDefaultSize, 0 );
    item7->Enable( false );
    item5->Add( item7, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item8 = new wxButton( parent, ID_LEVEL_UP, _("Up"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, ID_LEVEL_DOWN, _("Down"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    item2->Add( item5, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT, 5 );

    wxStaticLine *item10 = new wxStaticLine( parent, ID_LINE1, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item2->Add( item10, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxBoxSizer *item11 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item12 = new wxButton( parent, ID_EDITHEIGHTS, _("Baseline Editor"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item13 = new wxButton( parent, ID_SET_ROOF_TYPE, _("Set Roof Type"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

    item2->Add( item11, 0, wxALIGN_CENTER, 5 );

    item1->Add( item2, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxStaticBox *item15 = new wxStaticBox( parent, -1, _("Level Properties") );
    wxStaticBoxSizer *item14 = new wxStaticBoxSizer( item15, wxVERTICAL );

    wxBoxSizer *item16 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item17 = new wxStaticText( parent, ID_TEXT, _("Stories:"), wxDefaultPosition, wxDefaultSize, 0 );
    item16->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSpinCtrl *item18 = new wxSpinCtrl( parent, ID_STORIES, wxT("0"), wxDefaultPosition, wxSize(60,-1), 0, 0, 100, 0 );
    item16->Add( item18, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item14->Add( item16, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item19 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item20 = new wxStaticText( parent, ID_TEXT, _("Story Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item21 = new wxTextCtrl( parent, ID_STORY_HEIGHT, wxT(""), wxDefaultPosition, wxSize(60,-1), 0 );
    item19->Add( item21, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxStaticText *item22 = new wxStaticText( parent, ID_TEXT, _("meters"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item22, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item14->Add( item19, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxStaticText *item23 = new wxStaticText( parent, ID_TEXT, _("Edges:"), wxDefaultPosition, wxDefaultSize, 0 );
    item14->Add( item23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxString *strs24 = (wxString*) NULL;
    wxListBox *item24 = new wxListBox( parent, ID_EDGE, wxDefaultPosition, wxSize(60,-1), 0, strs24, wxLB_SINGLE );
    item14->Add( item24, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5 );

    item1->Add( item14, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxStaticBox *item26 = new wxStaticBox( parent, -1, _("Edge Properties") );
    wxStaticBoxSizer *item25 = new wxStaticBoxSizer( item26, wxVERTICAL );
    g_pEdgeGroup = item25;

    wxBoxSizer *item27 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item28 = new wxStaticText( parent, ID_TEXT, _("Material:"), wxDefaultPosition, wxDefaultSize, 0 );
    item27->Add( item28, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxTextCtrl *item29 = new wxTextCtrl( parent, ID_MATERIAL2, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item27->Add( item29, 1, wxALIGN_CENTER|wxRIGHT|wxTOP, 5 );

    wxButton *item30 = new wxButton( parent, ID_SET_MATERIAL, _("Set"), wxDefaultPosition, wxDefaultSize, 0 );
    item27->Add( item30, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    item25->Add( item27, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item31 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item32 = new wxButton( parent, ID_MODIFY_FACADE, _("Facade"), wxDefaultPosition, wxDefaultSize, 0 );
    item31->Add( item32, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item33 = new wxTextCtrl( parent, ID_FACADE, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_PROCESS_ENTER );
    item31->Add( item33, 1, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    item25->Add( item31, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item34 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item35 = new wxStaticText( parent, ID_TEXT, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
    item34->Add( item35, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticBitmap *item36 = new wxStaticBitmap( parent, ID_COLOR2, vtuiBitmapsFunc( 0 ), wxDefaultPosition, wxSize(32,18) );
    item34->Add( item36, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item37 = new wxButton( parent, ID_SET_COLOR, _("Set"), wxDefaultPosition, wxDefaultSize, 0 );
    item34->Add( item37, 0, wxALIGN_CENTER|wxALL, 5 );

    item25->Add( item34, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item38 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item39 = new wxStaticText( parent, ID_TEXT, _("Slope:"), wxDefaultPosition, wxDefaultSize, 0 );
    item38->Add( item39, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item40 = new wxTextCtrl( parent, ID_EDGE_SLOPE, wxT(""), wxDefaultPosition, wxSize(60,-1), 0 );
    item38->Add( item40, 0, wxALIGN_CENTER|wxRIGHT|wxBOTTOM, 5 );

    item25->Add( item38, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxTextCtrl *item41 = new wxTextCtrl( parent, ID_FEATURES, wxT(""), wxDefaultPosition, wxSize(-1,55), wxTE_MULTILINE );
    item25->Add( item41, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

    wxBoxSizer *item42 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item43 = new wxButton( parent, ID_FEAT_CLEAR, _("Clear"), wxDefaultPosition, wxSize(70,-1), 0 );
    item42->Add( item43, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item44 = new wxButton( parent, ID_FEAT_WALL, _("Wall"), wxDefaultPosition, wxSize(70,-1), 0 );
    item42->Add( item44, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item45 = new wxButton( parent, ID_FEAT_WINDOW, _("Window"), wxDefaultPosition, wxSize(70,-1), 0 );
    item42->Add( item45, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item46 = new wxButton( parent, ID_FEAT_DOOR, _("Door"), wxDefaultPosition, wxSize(70,-1), 0 );
    item42->Add( item46, 0, wxALIGN_CENTER|wxALL, 5 );

    item25->Add( item42, 0, wxALIGN_CENTER, 5 );

    item1->Add( item25, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    item0->Add( item1, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxBoxSizer *item47 = new wxBoxSizer( wxHORIZONTAL );

    item47->Add( 80, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item48 = new wxButton( parent, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item47->Add( item48, 0, wxALIGN_CENTER|wxALL, 5 );

    item47->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item49 = new wxButton( parent, ID_EDGES, _("Edges <<"), wxDefaultPosition, wxDefaultSize, 0 );
    item47->Add( item49, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item47, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

wxSizer *LinearStructDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item2 = new wxStaticText( parent, ID_TEXT, _("Defined Style:"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs3 = (wxString*) NULL;
    wxChoice *item3 = new wxChoice( parent, ID_LINEAR_STRUCTURE_STYLE, wxDefaultPosition, wxSize(160,-1), 0, strs3, 0 );
    item1->Add( item3, 1, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxStaticBox *item5 = new wxStaticBox( parent, -1, _("Posts") );
    wxStaticBoxSizer *item4 = new wxStaticBoxSizer( item5, wxVERTICAL );

    wxBoxSizer *item6 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item7 = new wxStaticText( parent, ID_TEXT, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
    item6->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs8 = (wxString*) NULL;
    wxChoice *item8 = new wxChoice( parent, ID_POST_TYPE, wxDefaultPosition, wxSize(100,-1), 0, strs8, 0 );
    item6->Add( item8, 1, wxALIGN_CENTER|wxALL, 5 );

    item4->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item9 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, _("Spacing:"), wxDefaultPosition, wxDefaultSize, 0 );
    item9->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_POST_SPACING_EDIT, wxT(""), wxDefaultPosition, wxSize(50,-1), 0 );
    item9->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSlider *item12 = new wxSlider( parent, ID_POST_SPACING_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item9->Add( item12, 0, wxALIGN_CENTER|wxALL, 0 );

    item4->Add( item9, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item13 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item14 = new wxStaticText( parent, ID_TEXT, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item13->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item15 = new wxTextCtrl( parent, ID_POST_HEIGHT_EDIT, wxT(""), wxDefaultPosition, wxSize(50,-1), 0 );
    item13->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSlider *item16 = new wxSlider( parent, ID_POST_HEIGHT_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item13->Add( item16, 0, wxALIGN_CENTER|wxALL, 0 );

    item4->Add( item13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item17 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item18 = new wxStaticText( parent, ID_TEXT, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
    item17->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item19 = new wxTextCtrl( parent, ID_POST_SIZE_EDIT, wxT(""), wxDefaultPosition, wxSize(50,-1), 0 );
    item17->Add( item19, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSlider *item20 = new wxSlider( parent, ID_POST_SIZE_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item17->Add( item20, 0, wxALIGN_CENTER|wxALL, 0 );

    item4->Add( item17, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    item0->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticBox *item22 = new wxStaticBox( parent, -1, _("Connection") );
    wxStaticBoxSizer *item21 = new wxStaticBoxSizer( item22, wxVERTICAL );

    wxBoxSizer *item23 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item24 = new wxStaticText( parent, ID_TEXT, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
    item23->Add( item24, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs25 = (wxString*) NULL;
    wxChoice *item25 = new wxChoice( parent, ID_CONN_TYPE, wxDefaultPosition, wxSize(100,-1), 0, strs25, 0 );
    item23->Add( item25, 1, wxALIGN_CENTER|wxALL, 5 );

    item21->Add( item23, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item26 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item27 = new wxStaticText( parent, ID_TEXT, _("Top Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item26->Add( item27, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item28 = new wxTextCtrl( parent, ID_CONN_TOP_EDIT, wxT(""), wxDefaultPosition, wxSize(50,-1), 0 );
    item26->Add( item28, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSlider *item29 = new wxSlider( parent, ID_CONN_TOP_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item26->Add( item29, 0, wxALIGN_CENTER|wxALL, 0 );

    item21->Add( item26, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item30 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item31 = new wxStaticText( parent, ID_TEXT, _("Bottom Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item30->Add( item31, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item32 = new wxTextCtrl( parent, ID_CONN_BOTTOM_EDIT, wxT(""), wxDefaultPosition, wxSize(50,-1), 0 );
    item30->Add( item32, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSlider *item33 = new wxSlider( parent, ID_CONN_BOTTOM_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item30->Add( item33, 0, wxALIGN_CENTER|wxALL, 0 );

    item21->Add( item30, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item34 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item35 = new wxStaticText( parent, ID_TEXT, _("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
    item34->Add( item35, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item36 = new wxTextCtrl( parent, ID_CONN_WIDTH_EDIT, wxT(""), wxDefaultPosition, wxSize(50,-1), 0 );
    item34->Add( item36, 0, wxALIGN_CENTER|wxALL, 5 );

    wxSlider *item37 = new wxSlider( parent, ID_CONN_WIDTH_SLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item34->Add( item37, 0, wxALIGN_CENTER|wxALL, 0 );

    item21->Add( item34, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    item0->Add( item21, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

wxSizer *InstanceDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxRadioButton *item1 = new wxRadioButton( parent, ID_RADIO_CONTENT, _("Instance from Content File"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    item0->Add( item1, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxBoxSizer *item2 = new wxBoxSizer( wxHORIZONTAL );

    item2->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item3 = new wxStaticText( parent, ID_TEXT, _("File:"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs4 = (wxString*) NULL;
    wxChoice *item4 = new wxChoice( parent, ID_CHOICE_FILE, wxDefaultPosition, wxSize(200,-1), 0, strs4, 0 );
    item2->Add( item4, 1, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item5 = new wxBoxSizer( wxHORIZONTAL );

    item5->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item6 = new wxStaticText( parent, ID_TEXT, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
    item5->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs7 = (wxString*) NULL;
    wxChoice *item7 = new wxChoice( parent, ID_CHOICE_TYPE, wxDefaultPosition, wxSize(200,-1), 0, strs7, 0 );
    item5->Add( item7, 1, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item8 = new wxBoxSizer( wxHORIZONTAL );

    item8->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item9 = new wxStaticText( parent, ID_TEXT, _("Item:"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs10 = (wxString*) NULL;
    wxChoice *item10 = new wxChoice( parent, ID_CHOICE_ITEM, wxDefaultPosition, wxSize(220,-1), 0, strs10, 0 );
    item8->Add( item10, 1, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item8, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxRadioButton *item11 = new wxRadioButton( parent, ID_RADIO_MODEL, _("Instance from 3D Model File"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item11, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxBoxSizer *item12 = new wxBoxSizer( wxHORIZONTAL );

    item12->Add( 20, 20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item13 = new wxTextCtrl( parent, ID_MODEL_FILE, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item12->Add( item13, 1, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item14 = new wxButton( parent, ID_BROWSE_MODEL_FILE, _("..."), wxDefaultPosition, wxSize(30,-1), 0 );
    item14->SetFont( wxFont( 12, wxROMAN, wxNORMAL, wxNORMAL ) );
    item12->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item12, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item15 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item16 = new wxStaticText( parent, ID_TEXT, _("Location:"), wxDefaultPosition, wxDefaultSize, 0 );
    item15->Add( item16, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item17 = new wxTextCtrl( parent, ID_LOCATION, wxT(""), wxDefaultPosition, wxSize(200,-1), 0 );
    item15->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

wxSizer *DistanceDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxFlexGridSizer *item0 = new wxFlexGridSizer( 3, 0, 0 );

    wxStaticText *item1 = new wxStaticText( parent, ID_TEXT, _("Map Offset"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item1, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item2 = new wxTextCtrl( parent, ID_MAP_OFFSET, wxT(""), wxDefaultPosition, wxSize(180,-1), 0 );
    item0->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxString *strs3 = (wxString*) NULL;
    wxChoice *item3 = new wxChoice( parent, ID_UNITS1, wxDefaultPosition, wxSize(100,-1), 0, strs3, 0 );
    item0->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item4 = new wxStaticText( parent, ID_TEXT, _("Map Distance"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxTextCtrl *item5 = new wxTextCtrl( parent, ID_MAP_DIST, wxT(""), wxDefaultPosition, wxSize(180,-1), 0 );
    item0->Add( item5, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxString *strs6 = (wxString*) NULL;
    wxChoice *item6 = new wxChoice( parent, ID_UNITS2, wxDefaultPosition, wxSize(100,-1), 0, strs6, 0 );
    item0->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item7 = new wxStaticText( parent, ID_TEXT, _("Geodesic Distance"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item8 = new wxTextCtrl( parent, ID_GEOD_DIST, wxT(""), wxDefaultPosition, wxSize(180,-1), 0 );
    item0->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs9 = (wxString*) NULL;
    wxChoice *item9 = new wxChoice( parent, ID_UNITS3, wxDefaultPosition, wxSize(100,-1), 0, strs9, 0 );
    item0->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item10 = new wxStaticText( parent, ID_TEXT, _("Approximate Ground"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item11 = new wxTextCtrl( parent, ID_GROUND_DIST, wxT(""), wxDefaultPosition, wxSize(180,-1), 0 );
    item0->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs12 = (wxString*) NULL;
    wxChoice *item12 = new wxChoice( parent, ID_UNITS4, wxDefaultPosition, wxSize(100,-1), 0, strs12, 0 );
    item0->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticText *item13 = new wxStaticText( parent, ID_TEXT, _("Vertical Difference"), wxDefaultPosition, wxDefaultSize, 0 );
    item0->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item14 = new wxTextCtrl( parent, ID_VERTICAL, wxT(""), wxDefaultPosition, wxSize(180,-1), 0 );
    item0->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );

    wxString *strs15 = (wxString*) NULL;
    wxChoice *item15 = new wxChoice( parent, ID_UNITS5, wxDefaultPosition, wxSize(100,-1), 0, strs15, 0 );
    item0->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

wxSizer *ColorMapDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item2 = new wxStaticText( parent, ID_TEXT, _("File:"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item3 = new wxTextCtrl( parent, ID_CMAP_FILE, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item1->Add( item3, 1, wxALIGN_CENTER|wxALL, 5 );

    item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxBoxSizer *item4 = new wxBoxSizer( wxHORIZONTAL );

    wxCheckBox *item5 = new wxCheckBox( parent, ID_RELATIVE, _("Scale relative to elevation range"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );

    wxCheckBox *item6 = new wxCheckBox( parent, ID_BLEND, _("Blend colors smoothly"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item0->Add( item4, 0, wxALIGN_CENTER, 5 );

    wxBoxSizer *item7 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticBox *item9 = new wxStaticBox( parent, -1, _("Colors") );
    wxStaticBoxSizer *item8 = new wxStaticBoxSizer( item9, wxVERTICAL );

    wxListCtrl *item10 = new wxListCtrl( parent, ID_COLORLIST, wxDefaultPosition, wxSize(-1,120), wxLC_REPORT|wxLC_NO_HEADER|wxSUNKEN_BORDER );
    item8->Add( item10, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxBoxSizer *item11 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item12 = new wxButton( parent, ID_CHANGE_COLOR, _("Change Color..."), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item13 = new wxButton( parent, ID_DELETE_ELEVATION, _("Delete Color"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

    item8->Add( item11, 0, wxALIGN_CENTER, 5 );

    wxStaticBox *item15 = new wxStaticBox( parent, -1, _("New Color") );
    wxStaticBoxSizer *item14 = new wxStaticBoxSizer( item15, wxHORIZONTAL );

    wxStaticText *item16 = new wxStaticText( parent, ID_TEXT, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item14->Add( item16, 0, wxALIGN_CENTER|wxALL, 5 );

    wxTextCtrl *item17 = new wxTextCtrl( parent, ID_HEIGHT_TO_ADD, wxT(""), wxDefaultPosition, wxSize(80,-1), 0 );
    item14->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item18 = new wxButton( parent, ID_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
    item14->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );

    item8->Add( item14, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item7->Add( item8, 1, wxGROW|wxALL, 5 );

    wxBoxSizer *item19 = new wxBoxSizer( wxVERTICAL );

    wxButton *item20 = new wxButton( parent, ID_SAVE_CMAP, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item20, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item21 = new wxButton( parent, ID_SAVE_AS_CMAP, _("Save As..."), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item21, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item22 = new wxButton( parent, ID_LOAD_CMAP, _("Load"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item22, 0, wxALIGN_CENTER|wxALL, 5 );

    wxStaticLine *item23 = new wxStaticLine( parent, ID_LINE1, wxDefaultPosition, wxSize(20,-1), wxLI_HORIZONTAL );
    item19->Add( item23, 0, wxALIGN_CENTER|wxALL, 5 );

    wxButton *item24 = new wxButton( parent, wxID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item24, 0, wxALIGN_CENTER|wxALL, 5 );

    item7->Add( item19, 0, wxALIGN_CENTER|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item0->Add( item7, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    if (set_sizer)
    {
        parent->SetSizer( item0 );
        if (call_fit)
            item0->SetSizeHints( parent );
    }
    
    return item0;
}

// Implement menubar functions

// Implement toolbar functions

// Implement bitmap functions

wxBitmap vtuiBitmapsFunc( size_t index )
{
    if (index == 0)
    {
        /* XPM */
        static const char *xpm_data[] = {
        /* columns rows colors chars-per-pixel */
        "32 18 5 1",
        "a c Black",
        "b c #FFFFFF",
        "c c #FF0000",
        "d c #0000FF",
        "e c #00FF00",
        /* pixels */
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaabaaaaaabaaaaaaaabaabaaaaaaaa",
        "aaaabaaaaabaaaaaaaaabaabaaaaaaaa",
        "aaaabaaaaabaaaaaaaaabaabaaaaaaaa",
        "aaaabaaabbbbaaaaaaaababbbaaaaaaa",
        "aaaabaaaaabaaaaaaaaabaabaaaaaaaa",
        "aaabbaabbabaabbabababaabaaaabaaa",
        "aababababababababababaabaaabbbaa",
        "aababababababababababaabaabbbbba",
        "aabababbaababababababaabaaabbbaa",
        "aabababaaababababababaabaaaabaaa",
        "aaabbaabbabaabababaabaabaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaccccccccaaeeeeeeeeaadddddddaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        };
        wxBitmap bitmap( xpm_data );
        return bitmap;
    }
    return wxNullBitmap;
}


// End of generated file
