//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: vtui.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_vtui_H__
#define __WDR_vtui_H__

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "vtui_wdr.h"
#endif

// Include wxWindows' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>

// Declare window functions

#define ID_TEXT 10000
#define ID_LEVEL 10001
#define ID_LEVEL_COPY 10002
#define ID_LEVEL_DEL 10003
#define ID_LEVEL_UP 10004
#define ID_LEVEL_DOWN 10005
#define ID_EDITHEIGHTS 10006
#define ID_STORIES 10007
#define ID_STORY_HEIGHT 10008
#define ID_MATERIAL1 10009
#define ID_SET_MATERIAL 10010
#define ID_COLOR1 10011
#define ID_SET_COLOR 10012
#define ID_EDGE_SLOPES 10013
#define ID_SET_EDGE_SLOPES 10014
#define ID_EDGES 10015
wxSizer *BuildingDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *g_pTopGroup;
#define ID_EDGE 10016
extern wxSizer *g_pEdgeGroup;
#define ID_MATERIAL2 10017
#define ID_MODIFY_FACADE 10018
#define ID_FACADE 10019
#define ID_COLOR2 10020
#define ID_EDGE_SLOPE 10021
#define ID_FEATURES 10022
#define ID_FEAT_CLEAR 10023
#define ID_FEAT_WALL 10024
#define ID_FEAT_WINDOW 10025
#define ID_FEAT_DOOR 10026
wxSizer *BuildingEdgesDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TYPE 10027
#define ID_HEIGHTEDIT 10028
#define ID_HEIGHTSLIDER 10029
#define ID_SPACINGEDIT 10030
#define ID_SPACINGSLIDER 10031
wxSizer *LinearStructDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_HEIGHTGRID 10032
#define ID_RECALCULATEHEIGHTS 10033
#define ID_BASELINEOFFSET 10034
wxSizer *HeightDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_RADIO_CONTENT 10035
#define ID_CHOICE_FILE 10036
#define ID_CHOICE_TYPE 10037
#define ID_CHOICE_ITEM 10038
#define ID_RADIO_MODEL 10039
#define ID_MODEL_FILE 10040
#define ID_BROWSE_MODEL_FILE 10041
#define ID_LOCATION 10042
wxSizer *InstanceDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_MAP_OFFSET 10043
#define ID_UNITS1 10044
#define ID_MAP_DIST 10045
#define ID_UNITS2 10046
#define ID_GEOD_DIST 10047
#define ID_UNITS3 10048
#define ID_GROUND_DIST 10049
#define ID_UNITS4 10050
#define ID_VERTICAL 10051
#define ID_UNITS5 10052
wxSizer *DistanceDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap vtuiBitmapsFunc( size_t index );

#endif

// End of generated file
