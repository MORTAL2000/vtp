//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: vtui.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_vtui_H__
#define __WDR_vtui_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "vtui_wdr.h"
#endif

// Include wxWidgets' headers

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
#include <wx/toolbar.h>

// Declare window functions

const int ID_LEVEL = 10001;
const int ID_LEVEL_COPY = 10002;
const int ID_LEVEL_DEL = 10003;
const int ID_LEVEL_UP = 10004;
const int ID_LEVEL_DOWN = 10005;
const int ID_LINE1 = 10006;
const int ID_EDITHEIGHTS = 10007;
const int ID_SET_ROOF_TYPE = 10008;
const int ID_STORIES = 10009;
const int ID_STORY_HEIGHT = 10010;
const int ID_MATERIAL1 = 10011;
const int ID_SET_MATERIAL = 10012;
const int ID_COLOR1 = 10013;
const int ID_SET_COLOR = 10014;
const int ID_EDGE_SLOPES = 10015;
const int ID_SET_EDGE_SLOPES = 10016;
const int ID_EDGES = 10017;
wxSizer *BuildingDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *g_pTopGroup;
const int ID_EDGE = 10018;
extern wxSizer *g_pEdgeGroup;
const int ID_MATERIAL2 = 10019;
const int ID_MODIFY_FACADE = 10020;
const int ID_FACADE = 10021;
const int ID_COLOR2 = 10022;
const int ID_EDGE_SLOPE = 10023;
const int ID_FEATURES = 10024;
const int ID_FEAT_CLEAR = 10025;
const int ID_FEAT_WALL = 10026;
const int ID_FEAT_WINDOW = 10027;
const int ID_FEAT_DOOR = 10028;
wxSizer *BuildingEdgesDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LINEAR_STRUCTURE_STYLE = 10029;
const int ID_POST_TYPE = 10030;
const int ID_POST_SPACING_EDIT = 10031;
const int ID_POST_SPACING_SLIDER = 10032;
const int ID_POST_HEIGHT_EDIT = 10033;
const int ID_POST_HEIGHT_SLIDER = 10034;
const int ID_POST_SIZE_EDIT = 10035;
const int ID_POST_SIZE_SLIDER = 10036;
const int ID_CONN_TYPE = 10037;
const int ID_CONN_TOP_EDIT = 10038;
const int ID_CONN_TOP_SLIDER = 10039;
const int ID_CONN_BOTTOM_EDIT = 10040;
const int ID_CONN_BOTTOM_SLIDER = 10041;
const int ID_CONN_WIDTH_EDIT = 10042;
const int ID_CONN_WIDTH_SLIDER = 10043;
wxSizer *LinearStructDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_HEIGHTGRID = 10044;
const int ID_RECALCULATEHEIGHTS = 10045;
const int ID_BASELINEOFFSET = 10046;
wxSizer *HeightDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RADIO_CONTENT = 10047;
const int ID_CHOICE_FILE = 10048;
const int ID_CHOICE_TYPE = 10049;
const int ID_CHOICE_ITEM = 10050;
const int ID_RADIO_MODEL = 10051;
const int ID_MODEL_FILE = 10052;
const int ID_BROWSE_MODEL_FILE = 10053;
const int ID_LOCATION = 10054;
wxSizer *InstanceDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_MAP_OFFSET = 10055;
const int ID_UNITS1 = 10056;
const int ID_MAP_DIST = 10057;
const int ID_UNITS2 = 10058;
const int ID_GEOD_DIST = 10059;
const int ID_UNITS3 = 10060;
const int ID_GROUND_DIST = 10061;
const int ID_UNITS4 = 10062;
const int ID_VERTICAL = 10063;
const int ID_UNITS5 = 10064;
wxSizer *DistanceDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CMAP_FILE = 10065;
const int ID_RELATIVE = 10066;
const int ID_BLEND = 10067;
const int ID_COLORLIST = 10068;
const int ID_CHANGE_COLOR = 10069;
const int ID_DELETE_ELEVATION = 10070;
const int ID_HEIGHT_TO_ADD = 10071;
const int ID_ADD = 10072;
const int ID_SAVE_CMAP = 10073;
const int ID_SAVE_AS_CMAP = 10074;
const int ID_LOAD_CMAP = 10075;
wxSizer *ColorMapDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap vtuiBitmapsFunc( size_t index );

#endif

// End of generated file
