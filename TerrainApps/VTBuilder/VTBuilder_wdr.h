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

const int ID_PROJ = 10052;
const int ID_SHOW_ALL_DATUMS = 10053;
const int ID_DATUM = 10054;
const int ID_HORUNITS = 10055;
const int ID_ZONE = 10056;
const int ID_PROJPARAM = 10057;
const int ID_STATEPLANE = 10058;
const int ID_PROJ_LOAD = 10059;
const int ID_PROJ_SAVE = 10060;
const int ID_LINE = 10061;
wxSizer *ProjectionDialog2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_STATEPLANES = 10062;
const int ID_NAD27 = 10063;
const int ID_NAD83 = 10064;
const int ID_RADIO_METERS = 10065;
const int ID_RADIO_FEET = 10066;
const int ID_RADIO_FEET_US = 10067;
wxSizer *StatePlaneDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_NUMLANES = 10068;
const int ID_HWYNAME = 10069;
const int ID_SIDEWALK = 10070;
const int ID_PARKING = 10071;
const int ID_MARGIN = 10072;
const int ID_SURFTYPE = 10073;
wxSizer *RoadPropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_INTTYPE = 10074;
const int ID_ROADNUM = 10075;
const int ID_BEHAVIOR = 10076;
const int ID_SCROLLED = 10077;
wxSizer *NodePropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_RADIO_CREATE_NEW = 10078;
const int ID_RADIO_TO_FILE = 10079;
const int ID_TEXT_TO_FILE = 10080;
const int ID_DOTDOTDOT = 10081;
const int ID_RADIO_TO_TILES = 10082;
const int ID_TEXT_TILE_INFO = 10083;
const int ID_TILE_OPTIONS = 10084;
const int ID_SPACINGX = 10085;
const int ID_SPACINGY = 10086;
const int ID_SIZEX = 10087;
const int ID_SIZEY = 10088;
const int ID_CONSTRAIN = 10089;
const int ID_SMALLER = 10090;
const int ID_BIGGER = 10091;
const int ID_FLOATS = 10092;
const int ID_SHORTS = 10093;
const int ID_AREAX = 10094;
const int ID_AREAY = 10095;
const int ID_ESTX = 10096;
const int ID_ESTY = 10097;
wxSizer *ResampleDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CONDITION = 10098;
const int ID_COMBO_VALUE = 10099;
wxSizer *SelectDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_SHOW = 10100;
const int ID_CHOICE_SHOW = 10101;
const int ID_TEXT_VERTICAL = 10102;
const int ID_CHOICE_VERTICAL = 10103;
const int ID_DEL_HIGH = 10104;
const int ID_LIST = 10105;
wxSizer *FeatInfoDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TOOLBAR = 10106;
const int ID_MINUTES = 10107;
const int ID_ELEVUNIT = 10108;
const int ID_RADIO_OUTLINE_ONLY = 10109;
const int ID_RADIO_COLOR = 10110;
const int ID_RADIO_NO_SHADING = 10111;
const int ID_RADIO_SIMPLE_SHADING = 10112;
const int ID_RADIO_CAST_SHADOWS = 10113;
const int ID_SPIN_CAST_ANGLE = 10114;
const int ID_SPIN_CAST_DIRECTION = 10115;
const int ID_CHECK_HIDE_UNKNOWN = 10116;
const int ID_CHECK_SHOW_ROAD_WIDTH = 10117;
const int ID_PATHNAMES = 10118;
wxSizer *OptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_USE_SPECIES = 10119;
const int ID_SPECIES_CHOICE = 10120;
const int ID_SPECIES_USE_FIELD = 10121;
const int ID_SPECIES_FIELD = 10122;
const int ID_SPECIES_ID = 10123;
const int ID_SPECIES_NAME = 10124;
const int ID_COMMON_NAME = 10125;
const int ID_BIOTYPE_INT = 10126;
const int ID_BIOTYPE_STRING = 10127;
const int ID_HEIGHT_RANDOM = 10128;
const int ID_HEIGHT_USE_FIELD = 10129;
const int ID_HEIGHT_FIELD = 10130;
wxSizer *VegFieldsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TYPE_CENTER = 10131;
const int ID_TYPE_FOOTPRINT = 10132;
const int ID_FLIP = 10133;
const int ID_CHOICE_HEIGHT_FIELD = 10134;
const int ID_CHOICE_HEIGHT_TYPE = 10135;
const int ID_TYPE_LINEAR = 10136;
const int ID_TYPE_INSTANCE = 10137;
const int ID_CHOICE_FILE_FIELD = 10138;
const int ID_INSIDE_AREA = 10139;
wxSizer *ImportStructFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LAYERNAME = 10140;
const int ID_ELEVATION_FIELDNAME = 10141;
const int ID_ELEVATION_UNITS = 10142;
const int ID_TYPE_BUILDING = 10143;
const int ID_BUILD_FOUNDATIONS = 10144;
const int ID_USE_25D = 10145;
wxSizer *ImportStructFuncOGR( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LEVEL_CHOICE = 10146;
wxSizer *LevelSelectionDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TILING = 10147;
wxSizer *SampleImageDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_BASE_URL = 10148;
const int ID_CHOICE_LAYERS = 10149;
const int ID_QUERY_LAYERS = 10150;
const int ID_CHOICE_FORMAT = 10151;
const int ID_QUERY = 10152;
wxSizer *MapServerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SPLITTER1 = 10153;
wxSizer *SpeciesListFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LISTCTRL_SPECIES = 10154;
wxSizer *Species1Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LISTCTRL_APPEARANCES = 10155;
wxSizer *Species2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_THEME = 10156;
const int ID_MPP = 10157;
wxSizer *TSDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_GEOTIFF = 10158;
const int ID_JPEG = 10159;
const int ID_CHOICE_COLORS = 10160;
const int ID_EDIT_COLORS = 10161;
const int ID_SHADING = 10162;
wxSizer *RenderBitmapDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LINK_FIELD = 10163;
wxSizer *ImageMapDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_EASTING = 10164;
const int ID_NORTHING = 10165;
const int ID_SET_CRS = 10166;
const int ID_FORMAT_DECIMAL = 10167;
const int ID_FORMAT_DMS = 10168;
const int ID_LONGITUDE_WEST = 10169;
wxSizer *ImportPointDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FILE_DATA = 10170;
const int ID_GET_FILE_DATA = 10171;
const int ID_CHECK_USE1 = 10172;
const int ID_CHECK_USE2 = 10173;
const int ID_FILE_GAZ = 10174;
const int ID_GET_FILE_GAZ = 10175;
const int ID_FILE_ZIP = 10176;
const int ID_GET_FILE_ZIP = 10177;
const int ID_CHECK_USE3 = 10178;
const int ID_FILE_GNS = 10179;
const int ID_GET_FILE_GNS = 10180;
wxSizer *GeocodeDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_DEPTH = 10181;
const int ID_MAXERROR = 10182;
wxSizer *ChunkDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_TO_FOLDER = 10183;
const int ID_COLUMNS = 10184;
const int ID_ROWS = 10185;
const int ID_CHOICE_LOD0_SIZE = 10186;
const int ID_SPIN_NUM_LODS = 10187;
const int ID_TOTALX = 10188;
const int ID_TOTALY = 10189;
const int ID_CURX = 10190;
const int ID_CURY = 10191;
wxSizer *TileDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap MyBitmapsFunc( size_t index );

#endif

// End of generated file
