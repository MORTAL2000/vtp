//------------------------------------------------------------------------------
// Source code generated by wxDesigner from file: vtui.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "vtui_wdr.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private header
#include "vtui_wdr.h"

#include <wx/intl.h>

// Implement window functions

wxSizer *BuildingDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );

    wxBoxSizer *item2 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item3 = new wxStaticText( parent, ID_TEXT, _("Building Levels"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxString *strs4 = (wxString*) NULL;
    wxListBox *item4 = new wxListBox( parent, ID_LEVEL, wxDefaultPosition, wxSize(60,100), 0, strs4, wxLB_SINGLE );
    item2->Add( item4, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxFlexGridSizer *item5 = new wxFlexGridSizer( 2, 0, 0 );

    wxButton *item6 = new wxButton( parent, ID_LEVEL_COPY, _("Copy"), wxDefaultPosition, wxSize(40,-1), 0 );
    item6->Enable( FALSE );
    item5->Add( item6, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item7 = new wxButton( parent, ID_LEVEL_DEL, _("Del"), wxDefaultPosition, wxSize(40,-1), 0 );
    item7->Enable( FALSE );
    item5->Add( item7, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item8 = new wxButton( parent, ID_LEVEL_UP, _("Up"), wxDefaultPosition, wxSize(40,-1), 0 );
    item5->Add( item8, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, ID_LEVEL_DOWN, _("Down"), wxDefaultPosition, wxSize(40,-1), 0 );
    item5->Add( item9, 0, wxALIGN_CENTRE|wxALL, 5 );

    item2->Add( item5, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT, 5 );

    item1->Add( item2, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxStaticBox *item11 = new wxStaticBox( parent, -1, _("Level Properties") );
    wxStaticBoxSizer *item10 = new wxStaticBoxSizer( item11, wxVERTICAL );

    wxBoxSizer *item12 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item13 = new wxStaticText( parent, ID_TEXT, _("Stories:"), wxDefaultPosition, wxDefaultSize, 0 );
    item12->Add( item13, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxSpinCtrl *item14 = new wxSpinCtrl( parent, ID_STORIES, wxT("0"), wxDefaultPosition, wxSize(60,-1), 0, 0, 100, 0 );
    item12->Add( item14, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item10->Add( item12, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item15 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item16 = new wxStaticText( parent, ID_TEXT, _("Story Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item15->Add( item16, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item17 = new wxTextCtrl( parent, ID_STORY_HEIGHT, wxT(""), wxDefaultPosition, wxSize(60,-1), 0 );
    item15->Add( item17, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxStaticText *item18 = new wxStaticText( parent, ID_TEXT, _("meters"), wxDefaultPosition, wxDefaultSize, 0 );
    item15->Add( item18, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item10->Add( item15, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item19 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item20 = new wxStaticText( parent, ID_TEXT, _("Material:"), wxDefaultPosition, wxDefaultSize, 0 );
    item19->Add( item20, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item21 = new wxTextCtrl( parent, ID_MATERIAL1, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item19->Add( item21, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item22 = new wxButton( parent, ID_SET_MATERIAL, _("Set"), wxDefaultPosition, wxSize(40,-1), 0 );
    item19->Add( item22, 0, wxALIGN_CENTRE|wxALL, 5 );

    item10->Add( item19, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item23 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item24 = new wxStaticText( parent, ID_TEXT, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
    item23->Add( item24, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxStaticBitmap *item25 = new wxStaticBitmap( parent, ID_COLOR1, vtuiBitmapsFunc( 0 ), wxDefaultPosition, wxSize(32,18) );
    item23->Add( item25, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item26 = new wxButton( parent, ID_SET_COLOR, _("Set"), wxDefaultPosition, wxSize(40,-1), 0 );
    item23->Add( item26, 0, wxALIGN_CENTRE|wxALL, 5 );

    item10->Add( item23, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item27 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item28 = new wxStaticText( parent, ID_TEXT, _("Edge Slopes:"), wxDefaultPosition, wxDefaultSize, 0 );
    item27->Add( item28, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item29 = new wxTextCtrl( parent, ID_EDGE_SLOPES, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item27->Add( item29, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item30 = new wxButton( parent, ID_SET_EDGE_SLOPES, _("Set"), wxDefaultPosition, wxSize(40,-1), 0 );
    item27->Add( item30, 0, wxALIGN_CENTRE|wxALL, 5 );

    item10->Add( item27, 0, wxALIGN_CENTRE, 5 );

    item1->Add( item10, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    item0->Add( item1, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxBoxSizer *item31 = new wxBoxSizer( wxHORIZONTAL );

    item31->Add( 80, 20, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxButton *item32 = new wxButton( parent, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item31->Add( item32, 0, wxALIGN_CENTRE|wxALL, 5 );

    item31->Add( 20, 20, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxButton *item33 = new wxButton( parent, ID_EDGES, _("Edges >>"), wxDefaultPosition, wxDefaultSize, 0 );
    item31->Add( item33, 0, wxALIGN_CENTRE|wxALL, 5 );

    item0->Add( item31, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

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

wxSizer *g_pTopGroup;
wxSizer *g_pEdgeGroup;
wxSizer *BuildingEdgesDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );
    g_pTopGroup = item1;

    wxBoxSizer *item2 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item3 = new wxStaticText( parent, ID_TEXT, _("Building Levels"), wxDefaultPosition, wxDefaultSize, 0 );
    item2->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxString *strs4 = (wxString*) NULL;
    wxListBox *item4 = new wxListBox( parent, ID_LEVEL, wxDefaultPosition, wxSize(60,100), 0, strs4, wxLB_SINGLE );
    item2->Add( item4, 1, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );

    wxFlexGridSizer *item5 = new wxFlexGridSizer( 2, 0, 0 );

    wxButton *item6 = new wxButton( parent, ID_LEVEL_COPY, _("Copy"), wxDefaultPosition, wxSize(40,-1), 0 );
    item6->Enable( FALSE );
    item5->Add( item6, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item7 = new wxButton( parent, ID_LEVEL_DEL, _("Del"), wxDefaultPosition, wxSize(40,-1), 0 );
    item7->Enable( FALSE );
    item5->Add( item7, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxButton *item8 = new wxButton( parent, ID_LEVEL_UP, _("Up"), wxDefaultPosition, wxSize(40,-1), 0 );
    item5->Add( item8, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxButton *item9 = new wxButton( parent, ID_LEVEL_DOWN, _("Down"), wxDefaultPosition, wxSize(40,-1), 0 );
    item5->Add( item9, 0, wxALIGN_CENTRE|wxALL, 5 );

    item2->Add( item5, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT, 5 );

    item1->Add( item2, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxStaticBox *item11 = new wxStaticBox( parent, -1, _("Level Properties") );
    wxStaticBoxSizer *item10 = new wxStaticBoxSizer( item11, wxVERTICAL );

    wxBoxSizer *item12 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item13 = new wxStaticText( parent, ID_TEXT, _("Stories:"), wxDefaultPosition, wxDefaultSize, 0 );
    item12->Add( item13, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxSpinCtrl *item14 = new wxSpinCtrl( parent, ID_STORIES, wxT("0"), wxDefaultPosition, wxSize(60,-1), 0, 0, 100, 0 );
    item12->Add( item14, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item10->Add( item12, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item15 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item16 = new wxStaticText( parent, ID_TEXT, _("Story Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item15->Add( item16, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item17 = new wxTextCtrl( parent, ID_STORY_HEIGHT, wxT(""), wxDefaultPosition, wxSize(60,-1), 0 );
    item15->Add( item17, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxStaticText *item18 = new wxStaticText( parent, ID_TEXT, _("meters"), wxDefaultPosition, wxDefaultSize, 0 );
    item15->Add( item18, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item10->Add( item15, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxStaticText *item19 = new wxStaticText( parent, ID_TEXT, _("Edges:"), wxDefaultPosition, wxDefaultSize, 0 );
    item10->Add( item19, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxString *strs20 = (wxString*) NULL;
    wxListBox *item20 = new wxListBox( parent, ID_EDGE, wxDefaultPosition, wxSize(60,-1), 0, strs20, wxLB_SINGLE );
    item10->Add( item20, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5 );

    item1->Add( item10, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    wxStaticBox *item22 = new wxStaticBox( parent, -1, _("Edge Properties") );
    wxStaticBoxSizer *item21 = new wxStaticBoxSizer( item22, wxVERTICAL );
    g_pEdgeGroup = item21;

    wxBoxSizer *item23 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item24 = new wxStaticText( parent, ID_TEXT, _("Material:"), wxDefaultPosition, wxDefaultSize, 0 );
    item23->Add( item24, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxTextCtrl *item25 = new wxTextCtrl( parent, ID_MATERIAL2, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_READONLY );
    item23->Add( item25, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP, 5 );

    wxButton *item26 = new wxButton( parent, ID_SET_MATERIAL, _("Set"), wxDefaultPosition, wxSize(40,-1), 0 );
    item23->Add( item26, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    item21->Add( item23, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item27 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item28 = new wxStaticText( parent, ID_TEXT, _("Facade:"), wxDefaultPosition, wxDefaultSize, 0 );
    item27->Add( item28, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item29 = new wxTextCtrl( parent, ID_FACADE, wxT(""), wxDefaultPosition, wxSize(80,-1), wxTE_PROCESS_ENTER );
    item27->Add( item29, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    item21->Add( item27, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item30 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item31 = new wxStaticText( parent, ID_TEXT, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
    item30->Add( item31, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxStaticBitmap *item32 = new wxStaticBitmap( parent, ID_COLOR2, vtuiBitmapsFunc( 0 ), wxDefaultPosition, wxSize(32,18) );
    item30->Add( item32, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item33 = new wxButton( parent, ID_SET_COLOR, _("Set"), wxDefaultPosition, wxSize(40,-1), 0 );
    item30->Add( item33, 0, wxALIGN_CENTRE|wxALL, 5 );

    item21->Add( item30, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxBoxSizer *item34 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item35 = new wxStaticText( parent, ID_TEXT, _("Slope:"), wxDefaultPosition, wxDefaultSize, 0 );
    item34->Add( item35, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item36 = new wxTextCtrl( parent, ID_EDGE_SLOPE, wxT(""), wxDefaultPosition, wxSize(60,-1), 0 );
    item34->Add( item36, 0, wxALIGN_CENTRE|wxRIGHT|wxBOTTOM, 5 );

    item21->Add( item34, 0, wxALIGN_CENTER_VERTICAL, 5 );

    wxTextCtrl *item37 = new wxTextCtrl( parent, ID_FEATURES, wxT(""), wxDefaultPosition, wxSize(-1,55), wxTE_MULTILINE );
    item21->Add( item37, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5 );

    wxBoxSizer *item38 = new wxBoxSizer( wxHORIZONTAL );

    wxButton *item39 = new wxButton( parent, ID_FEAT_CLEAR, _("Clear"), wxDefaultPosition, wxSize(40,-1), 0 );
    item38->Add( item39, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxButton *item40 = new wxButton( parent, ID_FEAT_WALL, _("Wall"), wxDefaultPosition, wxSize(32,-1), 0 );
    item38->Add( item40, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item41 = new wxButton( parent, ID_FEAT_WINDOW, _("Window"), wxDefaultPosition, wxSize(46,-1), 0 );
    item38->Add( item41, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    wxButton *item42 = new wxButton( parent, ID_FEAT_DOOR, _("Door"), wxDefaultPosition, wxSize(34,-1), 0 );
    item38->Add( item42, 0, wxALIGN_CENTRE|wxRIGHT|wxTOP|wxBOTTOM, 5 );

    item21->Add( item38, 0, wxALIGN_CENTRE, 5 );

    item1->Add( item21, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    item0->Add( item1, 0, wxALIGN_CENTRE|wxLEFT|wxRIGHT|wxTOP, 5 );

    wxBoxSizer *item43 = new wxBoxSizer( wxHORIZONTAL );

    item43->Add( 80, 20, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxButton *item44 = new wxButton( parent, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    item43->Add( item44, 0, wxALIGN_CENTRE|wxALL, 5 );

    item43->Add( 20, 20, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxButton *item45 = new wxButton( parent, ID_EDGES, _("Edges <<"), wxDefaultPosition, wxDefaultSize, 0 );
    item43->Add( item45, 0, wxALIGN_CENTRE|wxALL, 5 );

    item0->Add( item43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

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

wxSizer *LinearStructDialogFunc( wxWindow *parent, bool call_fit, bool set_sizer )
{
    wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item2 = new wxStaticText( parent, ID_TEXT, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
    item1->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxString *strs3 = (wxString*) NULL;
    wxChoice *item3 = new wxChoice( parent, ID_TYPE, wxDefaultPosition, wxSize(150,-1), 0, strs3, 0 );
    item1->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );

    item0->Add( item1, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item4 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item5 = new wxStaticText( parent, ID_TEXT, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add( item5, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item6 = new wxTextCtrl( parent, ID_HEIGHTEDIT, wxT(""), wxDefaultPosition, wxSize(40,-1), 0 );
    item4->Add( item6, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxSlider *item7 = new wxSlider( parent, ID_HEIGHTSLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item4->Add( item7, 0, wxALIGN_CENTRE|wxALL, 0 );

    item0->Add( item4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    wxBoxSizer *item8 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item9 = new wxStaticText( parent, ID_TEXT, _("Spacing:"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add( item9, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxTextCtrl *item10 = new wxTextCtrl( parent, ID_SPACINGEDIT, wxT(""), wxDefaultPosition, wxSize(40,-1), 0 );
    item8->Add( item10, 0, wxALIGN_CENTRE|wxALL, 5 );

    wxSlider *item11 = new wxSlider( parent, ID_SPACINGSLIDER, 0, 0, 100, wxDefaultPosition, wxSize(110,-1), wxSL_HORIZONTAL );
    item8->Add( item11, 0, wxALIGN_CENTRE|wxALL, 0 );

    item0->Add( item8, 0, wxALIGN_CENTRE|wxALL, 0 );

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

wxBitmap vtuiBitmapsFunc( size_t index )
{
    if (index == 0)
    {
        /* XPM */
        static const char *xpm_data[] = {
        /* columns rows colors chars-per-pixel */
        "32 18 5 1",
        "a c Black",
        "b c #FF0000",
        "c c #00FF00",
        "d c #0000FF",
        "e c #FFFFFF",
        /* pixels */
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaeaaaaaaeaaaaaaaaeaaeaaaaaaaa",
        "aaaaeaaaaaeaaaaaaaaaeaaeaaaaaaaa",
        "aaaaeaaaaaeaaaaaaaaaeaaeaaaaaaaa",
        "aaaaeaaaeeeeaaaaaaaaeaeeeaaaaaaa",
        "aaaaeaaaaaeaaaaaaaaaeaaeaaaaaaaa",
        "aaaeeaaeeaeaaeeaeaeaeaaeaaaaeaaa",
        "aaeaeaeaeaeaeaeaeaeaeaaeaaaeeeaa",
        "aaeaeaeaeaeaeaeaeaeaeaaeaaeeeeea",
        "aaeaeaeeaaeaeaeaeaeaeaaeaaaeeeaa",
        "aaeaeaeaaaeaeaeaeaeaeaaeaaaaeaaa",
        "aaaeeaaeeaeaaeaeaeaaeaaeaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aabbbbbbbbaaccccccccaadddddddaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        };
        wxBitmap bitmap( xpm_data );
        return bitmap;
    }
    return wxNullBitmap;
}


// End of generated file
