//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: VTBuilder.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_VTBuilder_H__
#define __WDR_VTBuilder_H__

#ifdef __GNUG__
    #pragma interface "VTBuilder_wdr.cpp"
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
#define ID_COLOR1 10001
#define ID_COLOR2 10002
#define ID_TRIM 10003
#define ID_COLOR3 10004
#define ID_ELEVATED 10005
#define ID_STORIES 10006
#define ID_ROOF 10007
wxSizer *BuildingDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_EXTENT_N 10008
#define ID_EXTENT_W 10009
#define ID_EXTENT_E 10010
#define ID_EXTENT_S 10011
#define ID_EXTENT_ALL 10012
wxSizer *ExtentDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_XY 10013
#define ID_DUMMY 10014
#define ID_DIST 10015
wxSizer *DistanceDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_BYTES 10016
#define ID_WIDTH 10017
#define ID_HEIGHT 10018
#define ID_UTM 10019
#define ID_FLOATING 10020
#define ID_VUNITS 10021
#define ID_SPACING 10022
wxSizer *RawDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_PROPS 10023
#define ID_LEFT 10024
#define ID_TOP 10025
#define ID_RIGHT 10026
#define ID_BOTTOM 10027
wxSizer *ElevPropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_CAPTION 10028
#define ID_GEO 10029
#define ID_UTMZONE 10030
#define ID_ALBERS 10031
#define ID_PAR1 10032
#define ID_PAR2 10033
#define ID_MERIDIAN 10034
#define ID_STATEPLANE 10035
#define ID_SPCHOICE 10036
#define ID_LINE 10037
#define ID_DATUM 10038
wxSizer *ProjectionDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_FIELD 10039
#define ID_DENSITY 10040
#define ID_BIOTYPE1 10041
#define ID_BIOTYPE2 10042
wxSizer *ImportVegFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define IDC_SAMPLING 10043
#define IDC_SCARCITY 10044
wxSizer *DistribVegFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TOWER_XY 10045
#define ID_TOWER_TYPE 10046
#define ID_TOWER_MATERIAL 10047
#define ID_TOWER_ELEV 10048
wxSizer *TowerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_PROJ 10049
#define ID_HORUNITS 10050
#define ID_ZONE 10051
#define ID_PROJPARAM 10052
wxSizer *ProjectionDialog2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_STATEPLANES 10053
#define ID_NAD27 10054
#define ID_NAD83 10055
wxSizer *StatePlaneDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_NUMLANES 10056
#define ID_HWYNAME 10057
#define ID_SIDEWALK 10058
#define ID_PARKING 10059
#define ID_MARGIN 10060
#define ID_SURFTYPE 10061
wxSizer *RoadPropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_INTTYPE 10062
#define ID_ROADNUM 10063
#define ID_BEHAVIOR 10064
wxSizer *NodePropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_SPACINGX 10065
#define ID_SPACINGY 10066
#define ID_SIZEX 10067
#define ID_SIZEY 10068
#define ID_CONSTRAIN 10069
#define ID_SMALLER 10070
#define ID_BIGGER 10071
#define ID_FLOATS 10072
#define ID_SHORTS 10073
#define ID_AREAX 10074
#define ID_AREAY 10075
#define ID_ESTX 10076
#define ID_ESTY 10077
wxSizer *ResampleDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_CONDITION 10078
#define ID_COMBO_VALUE 10079
wxSizer *SelectDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_LIST 10080
wxSizer *FeatInfoDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TOOLBAR 10081
#define ID_MINUTES 10082
#define ID_ELEVUNIT 10083
#define ID_PATHNAMES 10084
wxSizer *OptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap MyBitmapsFunc( size_t index );

#endif

// End of generated file
