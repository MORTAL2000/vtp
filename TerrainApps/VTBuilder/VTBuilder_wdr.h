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
const int ID_SPACINGX = 10074;
const int ID_SPACINGY = 10075;
const int ID_SIZEX = 10076;
const int ID_SIZEY = 10077;
const int ID_CONSTRAIN = 10078;
const int ID_SMALLER = 10079;
const int ID_BIGGER = 10080;
const int ID_FLOATS = 10081;
const int ID_SHORTS = 10082;
const int ID_AREAX = 10083;
const int ID_AREAY = 10084;
const int ID_ESTX = 10085;
const int ID_ESTY = 10086;
wxSizer *ResampleDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CONDITION = 10087;
const int ID_COMBO_VALUE = 10088;
wxSizer *SelectDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_SHOW = 10089;
const int ID_CHOICE_SHOW = 10090;
const int ID_TEXT_VERTICAL = 10091;
const int ID_CHOICE_VERTICAL = 10092;
const int ID_DEL_HIGH = 10093;
const int ID_LIST = 10094;
wxSizer *FeatInfoDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TOOLBAR = 10095;
const int ID_MINUTES = 10096;
const int ID_ELEVUNIT = 10097;
const int ID_RADIO_OUTLINE_ONLY = 10098;
const int ID_RADIO_COLOR = 10099;
const int ID_RADIO_NO_SHADING = 10100;
const int ID_RADIO_SIMPLE_SHADING = 10101;
const int ID_RADIO_CAST_SHADOWS = 10102;
const int ID_SPIN_CAST_ANGLE = 10103;
const int ID_SPIN_CAST_DIRECTION = 10104;
const int ID_CHECK_HIDE_UNKNOWN = 10105;
const int ID_CHECK_SHOW_ROAD_WIDTH = 10106;
const int ID_PATHNAMES = 10107;
wxSizer *OptionsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_USE_SPECIES = 10108;
const int ID_SPECIES_CHOICE = 10109;
const int ID_SPECIES_USE_FIELD = 10110;
const int ID_SPECIES_FIELD = 10111;
const int ID_SPECIES_ID = 10112;
const int ID_SPECIES_NAME = 10113;
const int ID_COMMON_NAME = 10114;
const int ID_BIOTYPE_INT = 10115;
const int ID_BIOTYPE_STRING = 10116;
const int ID_HEIGHT_RANDOM = 10117;
const int ID_HEIGHT_USE_FIELD = 10118;
const int ID_HEIGHT_FIELD = 10119;
wxSizer *VegFieldsDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TYPE_LINEAR = 10120;
const int ID_TYPE_INSTANCE = 10121;
const int ID_CHOICE_FILE_FIELD = 10122;
const int ID_TYPE_CENTER = 10123;
const int ID_TYPE_FOOTPRINT = 10124;
const int ID_CHOICE_HEIGHT_FIELD = 10125;
const int ID_CHOICE_HEIGHT_TYPE = 10126;
const int ID_RADIO_ROOF_DEFAULT = 10127;
const int ID_RADIO_ROOF_SINGLE = 10128;
const int ID_CHOICE_ROOF_TYPE = 10129;
const int ID_RADIO_ROOF_FIELD = 10130;
const int ID_CHOICE_ROOF_FIELD = 10131;
const int ID_INSIDE_AREA = 10132;
wxSizer *ImportStructFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LAYERNAME = 10133;
const int ID_ELEVATION_FIELDNAME = 10134;
const int ID_ELEVATION_UNITS = 10135;
const int ID_TYPE_BUILDING = 10136;
const int ID_BUILD_FOUNDATIONS = 10137;
const int ID_USE_25D = 10138;
wxSizer *ImportStructFuncOGR( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LEVEL_CHOICE = 10139;
wxSizer *LevelSelectionDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TILING = 10140;
wxSizer *SampleImageDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_BASE_URL = 10141;
const int ID_QUERY_LAYERS = 10142;
const int ID_LIST_LAYERS = 10143;
const int ID_LAYER_DESC = 10144;
const int ID_LIST_STYLES = 10145;
const int ID_STYLE_DESC = 10146;
const int ID_CHOICE_FORMAT = 10147;
const int ID_QUERY = 10148;
wxSizer *MapServerDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_SPLITTER1 = 10149;
wxSizer *SpeciesListFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LISTCTRL_SPECIES = 10150;
wxSizer *Species1Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LISTCTRL_APPEARANCES = 10151;
wxSizer *Species2Func( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_THEME = 10152;
const int ID_MPP = 10153;
wxSizer *TSDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_GEOTIFF = 10154;
const int ID_JPEG = 10155;
const int ID_CHOICE_COLORS = 10156;
const int ID_EDIT_COLORS = 10157;
const int ID_SHADING = 10158;
wxSizer *RenderBitmapDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LINK_FIELD = 10159;
wxSizer *ImageMapDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_EASTING = 10160;
const int ID_NORTHING = 10161;
const int ID_SET_CRS = 10162;
const int ID_FORMAT_DECIMAL = 10163;
const int ID_FORMAT_DMS = 10164;
const int ID_LONGITUDE_WEST = 10165;
wxSizer *ImportPointDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_FILE_DATA = 10166;
const int ID_GET_FILE_DATA = 10167;
const int ID_CHECK_USE1 = 10168;
const int ID_CHECK_USE2 = 10169;
const int ID_FILE_GAZ = 10170;
const int ID_GET_FILE_GAZ = 10171;
const int ID_FILE_ZIP = 10172;
const int ID_GET_FILE_ZIP = 10173;
const int ID_CHECK_USE3 = 10174;
const int ID_FILE_GNS = 10175;
const int ID_GET_FILE_GNS = 10176;
wxSizer *GeocodeDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_DEPTH = 10177;
const int ID_MAXERROR = 10178;
wxSizer *ChunkDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_TO_FOLDER = 10179;
const int ID_COLUMNS = 10180;
const int ID_ROWS = 10181;
const int ID_CHOICE_LOD0_SIZE = 10182;
const int ID_SPIN_NUM_LODS = 10183;
const int ID_TOTALX = 10184;
const int ID_TOTALY = 10185;
const int ID_CURX = 10186;
const int ID_CURY = 10187;
wxSizer *TileDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

wxBitmap MyBitmapsFunc( size_t index );

#endif

// End of generated file
