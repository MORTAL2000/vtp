//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: VTBuilder.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_VTBuilder_H__
#define __WDR_VTBuilder_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "VTBuilder_wdr.h"
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
#include <wx/tglbtn.h>

// Declare window functions

const int ID_TEXT = 10000;
const int ID_EXTENT_N = 10001;
const int ID_EXTENT_W = 10002;
const int ID_EXTENT_E = 10003;
const int ID_EXTENT_S = 10004;
const int ID_DMS = 10005;
const int ID_EXTENT_ALL = 10006;
wxSizer *ExtentDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_BYTES = 10007;
const int ID_WIDTH = 10008;
const int ID_HEIGHT = 10009;
const int ID_LITTLE_ENDIAN = 10010;
const int ID_BIG_ENDIAN = 10011;
const int ID_VUNITS = 10012;
const int ID_CRS_SIMPLE = 10013;
const int ID_CRS_CURRENT = 10014;
const int ID_CRS_EXACT = 10015;
const int ID_CRS = 10016;
const int ID_EXT_SPACING = 10017;
const int ID_SPACING = 10018;
const int ID_EXT_EXACT = 10019;
const int ID_EXTENTS = 10020;
wxSizer *RawDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_PROPS = 10021;
const int ID_LEFT = 10022;
const int ID_TOP = 10023;
const int ID_RIGHT = 10024;
const int ID_BOTTOM = 10025;
wxSizer *LayerPropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FIELD = 10026;
const int ID_DENSITY = 10027;
const int ID_BIOTYPE1 = 10028;
const int ID_BIOTYPE2 = 10029;
wxSizer *ImportVegFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_SAMPLING = 10030;
const int IDC_SCARCITY = 10031;
const int ID_SPECIES1 = 10032;
const int ID_CHOICE_SPECIES = 10033;
const int ID_SPECIES2 = 10034;
const int ID_CHOICE_BIOTYPE = 10035;
const int ID_SPECIES3 = 10036;
const int ID_CHOICE_BIOTYPE_LAYER = 10037;
const int ID_DENSITY1 = 10038;
const int ID_TEXT_FIXED_DENSITY = 10039;
const int ID_DENSITY2 = 10040;
const int ID_DENSITY3 = 10041;
const int ID_CHOICE_DENSITY_LAYER = 10042;
const int ID_SIZE1 = 10043;
const int ID_TEXT_FIXED_SIZE = 10044;
const int ID_SIZE2 = 10045;
const int ID_SPIN_RANDOM_FROM = 10046;
const int ID_SPIN_RANDOM_TO = 10047;
wxSizer *DistribVegFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TOWER_XY = 10048;
const int ID_TOWER_TYPE = 10049;
const int ID_TOWER_MATERIAL = 10050;
const int ID_TOWER_ELEV = 10051;
wxSizer *TowerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_NUMLANES = 10052;
const int ID_HWYNAME = 10053;
const int ID_SIDEWALK = 10054;
const int ID_PARKING = 10055;
const int ID_MARGIN = 10056;
const int ID_LANE_WIDTH = 10057;
const int ID_SIDEWALK_WIDTH = 10058;
const int ID_CURB_HEIGHT = 10059;
const int ID_PARKING_WIDTH = 10060;
const int ID_MARGIN_WIDTH = 10061;
const int ID_SURFTYPE = 10062;
wxSizer *RoadPropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_INTTYPE = 10063;
const int ID_ROADNUM = 10064;
const int ID_BEHAVIOR = 10065;
const int ID_SCROLLED = 10066;
wxSizer *NodePropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RADIO_CREATE_NEW = 10067;
const int ID_RADIO_TO_FILE = 10068;
const int ID_TEXT_TO_FILE = 10069;
const int ID_DOTDOTDOT = 10070;
const int ID_RADIO_TO_TILES = 10071;
const int ID_TEXT_TILE_INFO = 10072;
const int ID_TILE_OPTIONS = 10073;
const int ID_DERIVED_IMAGES = 10074;
const int ID_RENDERING_OPTIONS = 10075;
const int ID_TEXT_TO_IMAGE_FILE = 10076;
const int ID_DOTDOTDOT2 = 10077;
const int ID_SPACINGX = 10078;
const int ID_SPACINGY = 10079;
const int ID_SIZEX = 10080;
const int ID_SIZEY = 10081;
const int ID_CONSTRAIN = 10082;
const int ID_SMALLER = 10083;
const int ID_BIGGER = 10084;
const int ID_FLOATS = 10085;
const int ID_SHORTS = 10086;
const int ID_FILL_GAPS = 10087;
const int ID_AREAX = 10088;
const int ID_AREAY = 10089;
const int ID_ESTX = 10090;
const int ID_ESTY = 10091;
wxSizer *ResampleDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CONDITION = 10092;
const int ID_COMBO_VALUE = 10093;
wxSizer *SelectDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TOOLBAR = 10094;
const int ID_MINUTES = 10095;
const int ID_ELEVUNIT = 10096;
const int ID_RADIO_OUTLINE_ONLY = 10097;
const int ID_RADIO_COLOR = 10098;
const int ID_RENDER_OPTIONS = 10099;
const int ID_CHECK_HIDE_UNKNOWN = 10100;
const int ID_CHECK_SHOW_ROAD_WIDTH = 10101;
const int ID_PATHNAMES = 10102;
wxSizer *OptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_USE_SPECIES = 10103;
const int ID_SPECIES_CHOICE = 10104;
const int ID_SPECIES_USE_FIELD = 10105;
const int ID_SPECIES_FIELD = 10106;
const int ID_SPECIES_ID = 10107;
const int ID_SPECIES_NAME = 10108;
const int ID_COMMON_NAME = 10109;
const int ID_BIOTYPE_INT = 10110;
const int ID_BIOTYPE_STRING = 10111;
const int ID_HEIGHT_RANDOM = 10112;
const int ID_HEIGHT_FIXED = 10113;
const int ID_HEIGHT_FIXED_VALUE = 10114;
const int ID_HEIGHT_USE_FIELD = 10115;
const int ID_HEIGHT_FIELD = 10116;
wxSizer *VegFieldsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TYPE_LINEAR = 10117;
const int ID_TYPE_INSTANCE = 10118;
const int ID_CHOICE_FILE_FIELD = 10119;
const int ID_TYPE_CENTER = 10120;
const int ID_TYPE_FOOTPRINT = 10121;
const int ID_CHOICE_HEIGHT_FIELD = 10122;
const int ID_CHOICE_HEIGHT_TYPE = 10123;
const int ID_RADIO_COLOR_DEFAULT = 10124;
const int ID_RADIO_COLOR_FIXED = 10125;
const int ID_COLOR3 = 10126;
const int ID_SET_COLOR1 = 10127;
const int ID_COLOR4 = 10128;
const int ID_SET_COLOR2 = 10129;
const int ID_RADIO_ROOF_DEFAULT = 10130;
const int ID_RADIO_ROOF_SINGLE = 10131;
const int ID_CHOICE_ROOF_TYPE = 10132;
const int ID_SLOPECNTR = 10133;
const int ID_RADIO_ROOF_FIELD = 10134;
const int ID_CHOICE_ROOF_FIELD = 10135;
const int ID_DEFAULTS_FILE = 10136;
const int ID_INSIDE_AREA = 10137;
wxSizer *ImportStructFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LAYERNAME = 10138;
const int ID_ELEVATION_FIELDNAME = 10139;
const int ID_ELEVATION_UNITS = 10140;
const int ID_TYPE_BUILDING = 10141;
const int ID_BUILD_FOUNDATIONS = 10142;
const int ID_USE_25D = 10143;
wxSizer *ImportStructFuncOGR( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LEVEL_CHOICE = 10144;
wxSizer *LevelSelectionDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TILING = 10145;
wxSizer *SampleImageDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_BASE_URL = 10146;
const int ID_QUERY_LAYERS = 10147;
const int ID_LIST_LAYERS = 10148;
const int ID_LAYER_DESC = 10149;
const int ID_LIST_STYLES = 10150;
const int ID_STYLE_DESC = 10151;
const int ID_CHOICE_FORMAT = 10152;
const int ID_QUERY = 10153;
wxSizer *MapServerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SPLITTER1 = 10154;
wxSizer *SpeciesListFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LISTCTRL_SPECIES = 10155;
wxSizer *Species1Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LISTCTRL_APPEARANCES = 10156;
wxSizer *Species2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_THEME = 10157;
const int ID_MPP = 10158;
wxSizer *TSDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_GEOTIFF = 10159;
const int ID_JPEG = 10160;
const int ID_CHOICE_COLORS = 10161;
const int ID_EDIT_COLORS = 10162;
const int ID_SHADING = 10163;
wxSizer *RenderBitmapDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LINK_FIELD = 10164;
wxSizer *ImageMapDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_EASTING = 10165;
const int ID_NORTHING = 10166;
const int ID_CHECK_ELEVATION = 10167;
const int ID_ELEVATION = 10168;
const int ID_SET_CRS = 10169;
const int ID_FORMAT_DECIMAL = 10170;
const int ID_FORMAT_DMS = 10171;
const int ID_LONGITUDE_WEST = 10172;
wxSizer *ImportPointDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FILE_DATA = 10173;
const int ID_GET_FILE_DATA = 10174;
const int ID_CHECK_USE1 = 10175;
const int ID_CHECK_USE2 = 10176;
const int ID_FILE_GAZ = 10177;
const int ID_GET_FILE_GAZ = 10178;
const int ID_FILE_ZIP = 10179;
const int ID_GET_FILE_ZIP = 10180;
const int ID_CHECK_USE3 = 10181;
const int ID_FILE_GNS = 10182;
const int ID_GET_FILE_GNS = 10183;
wxSizer *GeocodeDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_DEPTH = 10184;
const int ID_MAXERROR = 10185;
wxSizer *ChunkDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_TO_FOLDER = 10186;
const int ID_COLUMNS = 10187;
const int ID_ROWS = 10188;
const int ID_CHOICE_LOD0_SIZE = 10189;
const int ID_SPIN_NUM_LODS = 10190;
const int ID_TOTALX = 10191;
const int ID_TOTALY = 10192;
const int ID_CURX = 10193;
const int ID_CURY = 10194;
const int ID_OMIT_FLAT = 10195;
const int ID_TC_NONE = 10196;
const int ID_TC_OGL = 10197;
const int ID_TC_SQUISH_FAST = 10198;
const int ID_TC_SQUISH_SLOW = 10199;
wxSizer *TileDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RADIO_SHADING_NONE = 10200;
const int ID_RADIO_SHADING_QUICK = 10201;
const int ID_RADIO_SHADING_DOT = 10202;
const int ID_SPIN_CAST_ANGLE = 10203;
const int ID_SPIN_CAST_DIRECTION = 10204;
const int ID_AMBIENT = 10205;
const int ID_GAMMA = 10206;
const int ID_CHECK_SHADOWS = 10207;
wxSizer *RenderOptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_EXTENT1 = 10208;
const int ID_EXTENT2 = 10209;
const int ID_MATCH_LAYER = 10210;
const int ID_LAYER_RES = 10211;
const int ID_GROW = 10212;
const int ID_SHRINK = 10213;
const int ID_TILE_SIZE = 10214;
const int ID_SIZE_SPIN = 10215;
wxSizer *MatchDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RADIO1 = 10216;
const int ID_RADIO2 = 10217;
const int ID_RADIO3 = 10218;
const int ID_RADIO4 = 10219;
const int ID_RADIO5 = 10220;
const int ID_MAX_MEGAPIXELS = 10221;
const int ID_RADIO6 = 10222;
const int ID_RADIO7 = 10223;
const int ID_RADIO8 = 10224;
const int ID_RADIO9 = 10225;
const int ID_RADIO10 = 10226;
const int ID_SAMPLING_N = 10227;
wxSizer *PrefDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_DIST_CUTOFF = 10228;
wxSizer *GenGridDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

const int ID_VIEW_LAYER_UP = 10229;
const int ID_VIEW_LAYER_DOWN = 10230;
void MainToolBarFunc( wxToolBar *parent );

// Declare bitmap functions

wxBitmap MyBitmapsFunc( size_t index );

wxBitmap ToolBitmapsFunc( size_t index );

#endif

// End of generated file
