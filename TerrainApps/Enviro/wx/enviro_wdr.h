//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: enviro.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_enviro_H__
#define __WDR_enviro_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "enviro_wdr.h"
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

const int ID_TEXT = 10000;
const int ID_EARTHVIEW = 10001;
const int ID_IMAGETEXT = 10002;
const int ID_IMAGE = 10003;
const int ID_TERRAIN = 10004;
const int ID_TNAME = 10005;
const int ID_EDITPROP = 10006;
const int ID_TERRMAN = 10007;
const int ID_OPTIONS = 10008;
const int ID_OPENGL = 10009;
wxSizer *StartupDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SCENETREE = 10010;
const int ID_ENABLED = 10011;
const int ID_ZOOMTO = 10012;
const int ID_REFRESH = 10013;
wxSizer *SceneGraphFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_NOTEBOOK = 10014;
wxSizer *TParamsFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SPECIES = 10015;
const int ID_COMMON_NAMES = 10016;
const int ID_LANGUAGE = 10017;
const int ID_PLANT_HEIGHT_EDIT = 10018;
const int ID_HEIGHT_SLIDER = 10019;
const int ID_PLANT_INDIVIDUAL = 10020;
const int ID_PLANT_LINEAR = 10021;
const int ID_PLANT_CONTINUOUS = 10022;
const int ID_PLANT_VARIANCE_EDIT = 10023;
const int ID_PLANT_VARIANCE_SLIDER = 10024;
const int ID_PLANT_SPACING_EDIT = 10025;
wxSizer *PlantDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LOCLIST = 10026;
const int ID_SAVE = 10027;
const int ID_LOAD = 10028;
const int ID_RECALL = 10029;
const int ID_STORE = 10030;
const int ID_STOREAS = 10031;
const int ID_REMOVE = 10032;
const int ID_LINE = 10033;
const int ID_ANIMS = 10034;
const int ID_NEW_ANIM = 10035;
const int ID_SAVE_ANIM = 10036;
const int ID_LOAD_ANIM = 10037;
const int ID_RESET = 10038;
const int ID_STOP = 10039;
const int ID_RECORD1 = 10040;
const int ID_PLAY = 10041;
const int ID_ANIM_POS = 10042;
const int ID_ACTIVE = 10043;
const int ID_SPEEDSLIDER = 10044;
const int ID_SPEED = 10045;
const int ID_LOOP = 10046;
const int ID_CONTINUOUS = 10047;
const int ID_SMOOTH = 10048;
const int ID_POS_ONLY = 10049;
const int ID_RECORD_LINEAR = 10050;
const int ID_RECORD_INTERVAL = 10051;
const int ID_RECORD_SPACING = 10052;
wxSizer *LocationDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CAMX = 10053;
const int ID_CAMY = 10054;
const int ID_CAMZ = 10055;
const int ID_FOV_TEXT = 10056;
const int ID_FOV = 10057;
const int ID_FOVSLIDER = 10058;
const int ID_NEAR = 10059;
const int ID_NEARSLIDER = 10060;
const int ID_FAR = 10061;
const int ID_FARSLIDER = 10062;
const int ID_SPEED_UNITS = 10063;
const int ID_ACCEL = 10064;
const int ID_LOD_VEG = 10065;
const int ID_SLIDER_VEG = 10066;
const int ID_LOD_STRUCT = 10067;
const int ID_SLIDER_STRUCT = 10068;
const int ID_LOD_ROAD = 10069;
const int ID_SLIDER_ROAD = 10070;
wxSizer *CameraDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

wxSizer *TextDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_STRUCTTYPE = 10071;
wxSizer *UtilDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_USE_GRID = 10072;
const int ID_FILENAME = 10073;
const int ID_LODMETHOD = 10074;
const int ID_TRICOUNT = 10075;
const int ID_PIXELERROR = 10076;
const int ID_TRISTRIPS = 10077;
const int ID_USE_TIN = 10078;
const int ID_FILENAME_TIN = 10079;
const int ID_VERTEXAG = 10080;
wxSizer *TParams1Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_NONE = 10081;
const int ID_SINGLE = 10082;
const int ID_TFILESINGLE = 10083;
const int ID_DERIVED = 10084;
const int ID_CHOICE_COLORS = 10085;
const int ID_EDIT_COLORS = 10086;
const int ID_TILED = 10087;
const int ID_TILESIZE = 10088;
const int ID_TFILEBASE = 10089;
const int ID_JPEG = 10090;
const int ID_TFILENAME = 10091;
const int ID_MIPMAP = 10092;
const int ID_16BIT = 10093;
const int ID_PRELIGHT = 10094;
const int ID_LIGHT_FACTOR = 10095;
const int ID_CAST_SHADOWS = 10096;
const int ID_DETAILTEXTURE = 10097;
const int ID_DT_NAME = 10098;
const int ID_DT_SCALE = 10099;
const int ID_DT_DISTANCE = 10100;
wxSizer *TParams2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_PLANTS = 10101;
const int ID_TREEFILE = 10102;
const int ID_VEGDISTANCE = 10103;
const int ID_ROADS = 10104;
const int ID_ROADFILE = 10105;
const int ID_ROADHEIGHT = 10106;
const int ID_ROADDISTANCE = 10107;
const int ID_TEXROADS = 10108;
const int ID_ROADCULTURE = 10109;
const int ID_HIGHWAYS = 10110;
const int ID_PAVED = 10111;
const int ID_DIRT = 10112;
const int ID_CONTENT_FILE = 10113;
const int ID_STRUCTFILES = 10114;
const int ID_STRUCT_DISTANCE = 10115;
const int ID_CHECK_STRUCTURE_SHADOWS = 10116;
const int ID_CHOICE_SHADOW_REZ = 10117;
const int ID_DARKNESS = 10118;
const int ID_VEHICLES = 10119;
wxSizer *TParams3Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_NAV_STYLE = 10120;
const int ID_MINHEIGHT = 10121;
const int ID_NAVSPEED = 10122;
const int ID_LOCFILE = 10123;
const int ID_INIT_LOCATION = 10124;
const int ID_HITHER = 10125;
const int ID_ANIM_PATHS = 10126;
const int ID_TEXT_INIT_TIME = 10127;
const int ID_SET_INIT_TIME = 10128;
const int ID_TIMEMOVES = 10129;
const int ID_TIMESPEED = 10130;
wxSizer *TParams4Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TREECTRL = 10131;
const int ID_ADD_PATH = 10132;
const int ID_ADD_TERRAIN = 10133;
const int ID_COPY = 10134;
const int ID_DELETE = 10135;
const int ID_EDIT_PARAMS = 10136;
wxSizer *TerrManFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_OCEANPLANE = 10137;
const int ID_OCEANPLANEOFFSET = 10138;
const int ID_DEPRESSOCEAN = 10139;
const int ID_DEPRESSOCEANOFFSET = 10140;
const int ID_SKY = 10141;
const int ID_SKYTEXTURE = 10142;
const int ID_HORIZON = 10143;
const int ID_FOG = 10144;
const int ID_FOG_DISTANCE = 10145;
const int ID_COLOR3 = 10146;
const int ID_BGCOLOR = 10147;
wxSizer *TParams5Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RAWFILES = 10148;
const int ID_STYLE = 10149;
const int ID_OVERLAY_FILE = 10150;
const int ID_OVERLAY_DOTDOTDOT = 10151;
const int ID_OVERLAY_X = 10152;
const int ID_OVERLAY_Y = 10153;
wxSizer *TParams6Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

extern wxSizer *g_pLayerSizer1;
extern wxSizer *g_pLayerSizer2;
const int ID_LAYER_ACTIVE = 10154;
const int ID_LAYER_VISIBLE = 10155;
const int ID_SHADOW_VISIBLE  = 10156;
const int ID_LAYER_ZOOM_TO = 10157;
const int ID_LAYER_SAVE = 10158;
const int ID_LAYER_CREATE = 10159;
const int ID_LAYER_REMOVE = 10160;
const int ID_SHOW_ALL = 10161;
const int ID_LAYER_TREE = 10162;
wxSizer *LayerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SPIN_YEAR = 10163;
const int ID_SPIN_MONTH = 10164;
const int ID_SPIN_DAY = 10165;
const int ID_SPIN_HOUR = 10166;
const int ID_SPIN_MINUTE = 10167;
const int ID_SPIN_SECOND = 10168;
const int ID_TEXT_SPEED = 10169;
const int ID_SLIDER_SPEED = 10170;
wxSizer *TimeDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FULLSCREEN = 10171;
const int ID_WINX = 10172;
const int ID_WINY = 10173;
const int ID_WIN_XSIZE = 10174;
const int ID_WIN_YSIZE = 10175;
const int ID_SIZE_INSIDE = 10176;
const int ID_TEXTURE_COMPRESSION = 10177;
const int ID_DISABLE_MIPMAPS = 10178;
const int ID_SELECTION_CUTOFF = 10179;
const int ID_SELECTION_RADIUS = 10180;
const int ID_PLANTSIZE = 10181;
const int ID_ONLY_AVAILABLE_SPECIES = 10182;
const int ID_CHOICE_CONTENT = 10183;
wxSizer *OptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FEATURE_TYPE = 10184;
const int ID_GEOMETRY = 10185;
const int ID_GEOM_COLOR = 10186;
const int ID_GEOM_HEIGHT = 10187;
const int ID_TESSELLATE = 10188;
const int ID_TEXT_LABELS = 10189;
const int ID_LABEL_COLOR = 10190;
const int ID_TEXT_FIELD = 10191;
const int ID_COLOR_FIELD = 10192;
const int ID_LABEL_HEIGHT = 10193;
const int ID_LABEL_SIZE = 10194;
wxSizer *StyleDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap MyBitmapsFunc( size_t index );

#endif

// End of generated file
