//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: enviro.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_enviro_H__
#define __WDR_enviro_H__

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "enviro_wdr.h"
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
#include <wx/toolbar.h>

// Declare window functions

#define ID_TEXT 10000
#define ID_EARTHVIEW 10001
#define ID_IMAGETEXT 10002
#define ID_IMAGE 10003
#define ID_TERRAIN 10004
#define ID_TNAME 10005
#define ID_EDITPROP 10006
#define ID_TERRMAN 10007
#define ID_OPTIONS 10008
#define ID_OPENGL 10009
wxSizer *StartupDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_SCENETREE 10010
#define ID_ENABLED 10011
#define ID_ZOOMTO 10012
#define ID_REFRESH 10013
wxSizer *SceneGraphFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_NOTEBOOK 10014
wxSizer *TParamsFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_SPECIES 10015
#define ID_COMMON_NAMES 10016
#define ID_LANGUAGE 10017
#define ID_PLANT_HEIGHT_EDIT 10018
#define ID_HEIGHT_SLIDER 10019
#define ID_PLANT_INDIVIDUAL 10020
#define ID_PLANT_LINEAR 10021
#define ID_PLANT_CONTINUOUS 10022
#define ID_PLANT_VARIANCE_EDIT 10023
#define ID_PLANT_VARIANCE_SLIDER 10024
#define ID_PLANT_SPACING_EDIT 10025
wxSizer *PlantDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_LOCLIST 10026
#define ID_SAVE 10027
#define ID_LOAD 10028
#define ID_RECALL 10029
#define ID_STORE 10030
#define ID_STOREAS 10031
#define ID_REMOVE 10032
#define ID_LINE 10033
#define ID_ANIMS 10034
#define ID_NEW_ANIM 10035
#define ID_SAVE_ANIM 10036
#define ID_LOAD_ANIM 10037
#define ID_RESET 10038
#define ID_STOP 10039
#define ID_RECORD1 10040
#define ID_PLAY 10041
#define ID_ANIM_POS 10042
#define ID_ACTIVE 10043
#define ID_SPEEDSLIDER 10044
#define ID_SPEED 10045
#define ID_LOOP 10046
#define ID_CONTINUOUS 10047
#define ID_SMOOTH 10048
#define ID_POS_ONLY 10049
#define ID_RECORD_LINEAR 10050
#define ID_RECORD_INTERVAL 10051
#define ID_RECORD_SPACING 10052
wxSizer *LocationDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_CAMX 10053
#define ID_CAMY 10054
#define ID_CAMZ 10055
#define ID_FOV 10056
#define ID_FOVSLIDER 10057
#define ID_NEAR 10058
#define ID_NEARSLIDER 10059
#define ID_FAR 10060
#define ID_FARSLIDER 10061
#define ID_SPEED_UNITS 10062
#define ID_ACCEL 10063
#define ID_LOD_VEG 10064
#define ID_SLIDER_VEG 10065
#define ID_LOD_STRUCT 10066
#define ID_SLIDER_STRUCT 10067
#define ID_LOD_ROAD 10068
#define ID_SLIDER_ROAD 10069
wxSizer *CameraDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

wxSizer *TextDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_STRUCTTYPE 10070
wxSizer *UtilDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_USE_GRID 10071
#define ID_FILENAME 10072
#define ID_LODMETHOD 10073
#define ID_TRICOUNT 10074
#define ID_PIXELERROR 10075
#define ID_TRISTRIPS 10076
#define ID_USE_TIN 10077
#define ID_FILENAME_TIN 10078
#define ID_VERTEXAG 10079
wxSizer *TParams1Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_NONE 10080
#define ID_SINGLE 10081
#define ID_TFILESINGLE 10082
#define ID_DERIVED 10083
#define ID_CHOICE_COLORS 10084
#define ID_EDIT_COLORS 10085
#define ID_TILED 10086
#define ID_TILESIZE 10087
#define ID_TFILEBASE 10088
#define ID_JPEG 10089
#define ID_TFILENAME 10090
#define ID_MIPMAP 10091
#define ID_16BIT 10092
#define ID_PRELIGHT 10093
#define ID_LIGHT_FACTOR 10094
#define ID_CAST_SHADOWS 10095
#define ID_DETAILTEXTURE 10096
#define ID_DT_NAME 10097
#define ID_DT_SCALE 10098
#define ID_DT_DISTANCE 10099
wxSizer *TParams2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_PLANTS 10100
#define ID_TREEFILE 10101
#define ID_VEGDISTANCE 10102
#define ID_ROADS 10103
#define ID_ROADFILE 10104
#define ID_ROADHEIGHT 10105
#define ID_ROADDISTANCE 10106
#define ID_TEXROADS 10107
#define ID_ROADCULTURE 10108
#define ID_HIGHWAYS 10109
#define ID_PAVED 10110
#define ID_DIRT 10111
#define ID_CONTENT_FILE 10112
#define ID_STRUCTFILES 10113
#define ID_STRUCT_DISTANCE 10114
#define ID_CHECK_STRUCTURE_SHADOWS 10115
#define ID_CHOICE_SHADOW_REZ 10116
#define ID_VEHICLES 10117
wxSizer *TParams3Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_NAV_STYLE 10118
#define ID_MINHEIGHT 10119
#define ID_NAVSPEED 10120
#define ID_LOCFILE 10121
#define ID_INIT_LOCATION 10122
#define ID_HITHER 10123
#define ID_TEXT_INIT_TIME 10124
#define ID_SET_INIT_TIME 10125
#define ID_TIMEMOVES 10126
#define ID_TIMESPEED 10127
wxSizer *TParams4Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TREECTRL 10128
#define ID_ADD_PATH 10129
#define ID_ADD_TERRAIN 10130
#define ID_COPY 10131
#define ID_DELETE 10132
#define ID_EDIT_PARAMS 10133
wxSizer *TerrManFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_OCEANPLANE 10134
#define ID_OCEANPLANEOFFSET 10135
#define ID_DEPRESSOCEAN 10136
#define ID_DEPRESSOCEANOFFSET 10137
#define ID_SKY 10138
#define ID_SKYTEXTURE 10139
#define ID_HORIZON 10140
#define ID_FOG 10141
#define ID_FOG_DISTANCE 10142
#define ID_COLOR3 10143
#define ID_BGCOLOR 10144
wxSizer *TParams5Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_RAWFILES 10145
#define ID_STYLE 10146
wxSizer *TParams6Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *g_pLayerSizer1;
extern wxSizer *g_pLayerSizer2;
#define ID_LAYER_ACTIVE 10147
#define ID_LAYER_VISIBLE 10148
#define ID_SHADOW_VISIBLE  10149
#define ID_LAYER_ZOOM_TO 10150
#define ID_LAYER_SAVE 10151
#define ID_LAYER_CREATE 10152
#define ID_LAYER_REMOVE 10153
#define ID_SHOW_ALL 10154
#define ID_LAYER_TREE 10155
wxSizer *LayerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_SPIN_YEAR 10156
#define ID_SPIN_MONTH 10157
#define ID_SPIN_DAY 10158
#define ID_SPIN_HOUR 10159
#define ID_SPIN_MINUTE 10160
#define ID_SPIN_SECOND 10161
#define ID_TEXT_SPEED 10162
#define ID_SLIDER_SPEED 10163
wxSizer *TimeDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_FULLSCREEN 10164
#define ID_TEXTURE_COMPRESSION 10165
#define ID_DISABLE_MIPMAPS 10166
#define ID_SELECTION_CUTOFF 10167
#define ID_SELECTION_RADIUS 10168
#define ID_PLANTSIZE 10169
#define ID_ONLY_AVAILABLE_SPECIES 10170
#define ID_CHOICE_CONTENT 10171
wxSizer *OptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_FEATURE_TYPE 10172
#define ID_GEOMETRY 10173
#define ID_COLOR 10174
#define ID_TEXT_LABELS 10175
#define ID_TEXT_FIELD 10176
#define ID_COLOR_FIELD 10177
#define ID_LABEL_HEIGHT 10178
#define ID_LABEL_SIZE 10179
wxSizer *StyleDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap MyBitmapsFunc( size_t index );

#endif

// End of generated file
