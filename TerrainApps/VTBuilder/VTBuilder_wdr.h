//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: VTBuilder.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_VTBuilder_H__
#define __WDR_VTBuilder_H__

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "VTBuilder_wdr.h"
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
#define ID_EXTENT_N 10001
#define ID_EXTENT_W 10002
#define ID_EXTENT_E 10003
#define ID_EXTENT_S 10004
#define ID_DMS 10005
#define ID_EXTENT_ALL 10006
wxSizer *ExtentDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_BYTES 10007
#define ID_WIDTH 10008
#define ID_HEIGHT 10009
#define ID_LITTLE_ENDIAN 10010
#define ID_BIG_ENDIAN 10011
#define ID_VUNITS 10012
#define ID_CRS_SIMPLE 10013
#define ID_CRS_CURRENT 10014
#define ID_CRS_EXACT 10015
#define ID_CRS 10016
#define ID_EXT_SPACING 10017
#define ID_SPACING 10018
#define ID_EXT_EXACT 10019
#define ID_EXTENTS 10020
wxSizer *RawDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_PROPS 10021
#define ID_LEFT 10022
#define ID_TOP 10023
#define ID_RIGHT 10024
#define ID_BOTTOM 10025
wxSizer *LayerPropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_FIELD 10026
#define ID_DENSITY 10027
#define ID_BIOTYPE1 10028
#define ID_BIOTYPE2 10029
wxSizer *ImportVegFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define IDC_SAMPLING 10030
#define IDC_SCARCITY 10031
#define ID_SPECIES1 10032
#define ID_CHOICE_SPECIES 10033
#define ID_SPECIES2 10034
#define ID_CHOICE_BIOTYPE 10035
#define ID_SPECIES3 10036
#define ID_CHOICE_BIOTYPE_LAYER 10037
#define ID_DENSITY1 10038
#define ID_DENSITY2 10039
#define ID_CHOICE_DENSITY_LAYER 10040
#define ID_SIZE1 10041
#define ID_TEXT_FIXED_SIZE 10042
#define ID_SIZE2 10043
#define ID_SPIN_RANDOM_FROM 10044
#define ID_SPIN_RANDOM_TO 10045
wxSizer *DistribVegFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TOWER_XY 10046
#define ID_TOWER_TYPE 10047
#define ID_TOWER_MATERIAL 10048
#define ID_TOWER_ELEV 10049
wxSizer *TowerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_PROJ 10050
#define ID_SHOW_ALL_DATUMS 10051
#define ID_DATUM 10052
#define ID_HORUNITS 10053
#define ID_ZONE 10054
#define ID_PROJPARAM 10055
#define ID_STATEPLANE 10056
#define ID_PROJ_LOAD 10057
#define ID_PROJ_SAVE 10058
#define ID_LINE 10059
wxSizer *ProjectionDialog2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_STATEPLANES 10060
#define ID_NAD27 10061
#define ID_NAD83 10062
#define ID_RADIO_METERS 10063
#define ID_RADIO_FEET 10064
#define ID_RADIO_FEET_US 10065
wxSizer *StatePlaneDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_NUMLANES 10066
#define ID_HWYNAME 10067
#define ID_SIDEWALK 10068
#define ID_PARKING 10069
#define ID_MARGIN 10070
#define ID_SURFTYPE 10071
wxSizer *RoadPropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_INTTYPE 10072
#define ID_ROADNUM 10073
#define ID_BEHAVIOR 10074
wxSizer *NodePropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_RADIO_CREATE_NEW 10075
#define ID_RADIO_TO_FILE 10076
#define ID_TEXT_TO_FILE 10077
#define ID_DOTDOTDOT 10078
#define ID_SPACINGX 10079
#define ID_SPACINGY 10080
#define ID_SIZEX 10081
#define ID_SIZEY 10082
#define ID_CONSTRAIN 10083
#define ID_SMALLER 10084
#define ID_BIGGER 10085
#define ID_FLOATS 10086
#define ID_SHORTS 10087
#define ID_AREAX 10088
#define ID_AREAY 10089
#define ID_ESTX 10090
#define ID_ESTY 10091
wxSizer *ResampleDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_CONDITION 10092
#define ID_COMBO_VALUE 10093
wxSizer *SelectDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TEXT_SHOW 10094
#define ID_CHOICE_SHOW 10095
#define ID_TEXT_VERTICAL 10096
#define ID_CHOICE_VERTICAL 10097
#define ID_DEL_HIGH 10098
#define ID_LIST 10099
wxSizer *FeatInfoDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TOOLBAR 10100
#define ID_MINUTES 10101
#define ID_ELEVUNIT 10102
#define ID_RADIO_OUTLINE_ONLY 10103
#define ID_RADIO_COLOR 10104
#define ID_RADIO_NO_SHADING 10105
#define ID_RADIO_SIMPLE_SHADING 10106
#define ID_RADIO_CAST_SHADOWS 10107
#define ID_SPIN_CAST_ANGLE 10108
#define ID_SPIN_CAST_DIRECTION 10109
#define ID_CHECK_HIDE_UNKNOWN 10110
#define ID_CHECK_SHOW_ROAD_WIDTH 10111
#define ID_PATHNAMES 10112
wxSizer *OptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_USE_SPECIES 10113
#define ID_SPECIES_CHOICE 10114
#define ID_SPECIES_USE_FIELD 10115
#define ID_SPECIES_FIELD 10116
#define ID_SPECIES_ID 10117
#define ID_SPECIES_NAME 10118
#define ID_COMMON_NAME 10119
#define ID_BIOTYPE_INT 10120
#define ID_BIOTYPE_STRING 10121
#define ID_HEIGHT_RANDOM 10122
#define ID_HEIGHT_USE_FIELD 10123
#define ID_HEIGHT_FIELD 10124
wxSizer *VegFieldsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TYPE_CENTER 10125
#define ID_TYPE_FOOTPRINT 10126
#define ID_FLIP 10127
#define ID_CHOICE_HEIGHT_FIELD 10128
#define ID_CHOICE_HEIGHT_TYPE 10129
#define ID_TYPE_LINEAR 10130
#define ID_TYPE_INSTANCE 10131
#define ID_CHOICE_FILE_FIELD 10132
#define ID_INSIDE_AREA 10133
wxSizer *ImportStructFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_LAYERNAME 10134
#define ID_ELEVATION_FIELDNAME 10135
#define ID_ELEVATION_UNITS 10136
#define ID_TYPE_BUILDING 10137
#define ID_BUILD_FOUNDATIONS 10138
#define ID_USE_25D 10139
wxSizer *ImportStructFuncOGR( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_LEVEL_CHOICE 10140
wxSizer *LevelSelectionDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TILING 10141
wxSizer *SampleImageDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_BASE_URL 10142
#define ID_CHOICE_LAYERS 10143
#define ID_QUERY_LAYERS 10144
#define ID_CHOICE_FORMAT 10145
#define ID_QUERY 10146
wxSizer *MapServerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_SPLITTER1 10147
wxSizer *SpeciesListFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_LISTCTRL_SPECIES 10148
wxSizer *Species1Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_LISTCTRL_APPEARANCES 10149
wxSizer *Species2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_THEME 10150
#define ID_MPP 10151
wxSizer *TSDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap MyBitmapsFunc( size_t index );

#endif

// End of generated file
