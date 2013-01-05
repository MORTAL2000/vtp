//
// MenuEnum.h
//
// Copyright (c) 2001-2013 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

// ID for the menu commands
enum
{
	// start at 1, as 0 is reserved on OSX
	ID_FILE_EXIT = 1,
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
	ID_FILE_MRU,
	ID_FILE_PREFS,
	ID_SPECIAL_FLIP,
	ID_SPECIAL_BATCH,
	ID_SPECIAL_DYMAX_TEXTURES,
	ID_SPECIAL_DYMAX_MAP,
	ID_SPECIAL_PROCESS_BILLBOARD,
	ID_SPECIAL_GEOCODE,
	ID_SPECIAL_RUN_TEST,

	ID_EDIT_DELETE,
	ID_EDIT_DESELECTALL,
	ID_EDIT_INVERTSELECTION,
	ID_EDIT_CROSSINGSELECTION,
	ID_EDIT_OFFSET,

	ID_LAYER_NEW,
	ID_LAYER_OPEN,
	ID_LAYER_SAVE,
	ID_LAYER_SAVE_AS,
	ID_MRU_LAYER,
	ID_MRU_IMPORT,
	ID_LAYER_IMPORT,
	ID_LAYER_IMPORTTIGER,
	ID_LAYER_IMPORTOSM,
	ID_LAYER_IMPORTNTF,
	ID_LAYER_IMPORTUTIL,
	ID_LAYER_IMPORT_MS,
	ID_LAYER_IMPORT_POINT,
	ID_LAYER_IMPORT_XML,
	ID_LAYER_IMPORT_DXF,
	ID_LAYER_PROPS,
	ID_LAYER_SETPROJ,
	ID_LAYER_CONVERTPROJ,
	ID_LAYER_COMBINE,
	ID_VIEW_SHOWLAYER,
	ID_VIEW_LAYER_UP,
	ID_VIEW_LAYER_DOWN,

	ID_VIEW_ZOOMIN,
	ID_VIEW_ZOOMOUT,
	ID_VIEW_ZOOMALL,
	ID_VIEW_ZOOM_LAYER,
	ID_VIEW_FULLVIEW,
	ID_VIEW_ZOOM_AREA,
	ID_VIEW_TOOLBAR,
	ID_VIEW_LAYERS,
	ID_VIEW_MAGNIFIER,
	ID_VIEW_PAN,
	ID_VIEW_DISTANCE,
	ID_VIEW_SETAREA,
	ID_VIEW_SHOWUTM,
	ID_VIEW_PROFILE,
	ID_VIEW_SCALE_BAR,
	ID_VIEW_SHOWGRID,
	ID_VIEW_WORLDMAP,
	ID_VIEW_OPTIONS,

	ID_ROAD_SELECTROAD,
	ID_ROAD_SELECTNODE,
	ID_ROAD_SELECTWHOLE,
	ID_ROAD_DIRECTION,
	ID_ROAD_EDIT,
	ID_ROAD_SHOWNODES,
	ID_ROAD_SELECTHWY,
	ID_ROAD_CLEAN,
	ID_ROAD_GUESS,

	ID_TOWER_ADD,
	ID_TOWER_SELECT,
	ID_TOWER_EDIT,

	ID_ELEV_SELECT,
	ID_ELEV_SCALE,
	ID_ELEV_VERT_OFFSET,
	ID_ELEV_REMOVERANGE,
	ID_ELEV_COMPUTE_DIFF,
	ID_ELEV_SETUNKNOWN,
	ID_ELEV_FILL_FAST,
	ID_ELEV_FILL_SLOW,
	ID_ELEV_FILL_REGIONS,
	ID_ELEV_EXPORT,
	ID_ELEV_EXPORT_TILES,
	ID_ELEV_COPY,
	ID_ELEV_PASTE_NEW,
	ID_ELEV_BITMAP,
	ID_ELEV_TOTIN,
	ID_ELEV_CONTOURS,
	ID_ELEV_CARVE,
	ID_ELEV_MERGETIN,
	ID_ELEV_TRIMTIN,

	ID_IMAGE_REPLACE_RGB,
	ID_IMAGE_CREATE_OVERVIEWS,
	ID_IMAGE_CREATE_OVER_ALL,
	ID_IMAGE_CREATE_MIPMAPS,
	ID_IMAGE_EXPORT_TILES,
	ID_IMAGE_EXPORT_PPM,

	ID_VEG_PLANTS,
	ID_VEG_BIOREGIONS,
	ID_VEG_REMAP,
	ID_VEG_EXPORTSHP,
	ID_VEG_HTML,

	ID_FEATURE_SELECT,
	ID_FEATURE_PICK,
	ID_FEATURE_TABLE,

	ID_STRUCTURE_EDIT_BLD,
	ID_STRUCTURE_ADD_LINEAR,
	ID_STRUCTURE_EDIT_LINEAR,
	ID_STRUCTURE_ADD_FOUNDATION,
	ID_STRUCTURE_ADD_POINTS,
	ID_STRUCTURE_DELETE_POINTS,
	ID_STRUCTURE_CONSTRAIN,
	ID_STRUCTURE_ADD_INST,
	ID_STRUCTURE_SELECT_USING_POLYGONS,
	ID_STRUCTURE_COLOUR_SELECTED_ROOFS,
	ID_STRUCTURE_CLEAN_FOOTPRINTS,
	ID_STRUCTURE_SELECT_INDEX,
	ID_STRUCTURE_EXPORT_FOOTPRINTS,
	ID_STRUCTURE_EXPORT_CANOMA,

	ID_RAW_SETTYPE,
	ID_RAW_ADDPOINTS,
	ID_RAW_ADDPOINT_TEXT,
	ID_RAW_ADDPOINTS_GPS,
	ID_RAW_ADDFEATURE_WKT,
	ID_RAW_SELECTCONDITION,
	ID_RAW_CONVERT_TOTIN,
	ID_RAW_CONVERT_TOPOLYS,
	ID_RAW_EXPORT_IMAGEMAP,
	ID_RAW_EXPORT_KML,
	ID_RAW_GENERATE_ELEVATION,
	ID_RAW_STYLE,
	ID_RAW_SCALE_H,
	ID_RAW_SCALE_V,
	ID_RAW_OFFSET_V,
	ID_RAW_CLEAN,
	ID_RAW_SELECT_BAD,

	ID_AREA_CLEAR,
	ID_AREA_ZOOM_ALL,
	ID_AREA_ZOOM_LAYER,
	ID_AREA_TYPEIN,
	ID_AREA_MATCH,
	ID_AREA_SAMPLE_ELEV,
	ID_AREA_SAMPLE_IMAGE,
	ID_AREA_SAMPLE_ELEV_OPT,
	ID_AREA_SAMPLE_IMAGE_OPT,
	ID_AREA_GENERATE_VEG,
	ID_AREA_VEG_DENSITY,
	ID_AREA_REQUEST_WFS,
	ID_AREA_REQUEST_WMS,
	ID_AREA_REQUEST_TSERVE,

	ID_HELP_DOC_LOCAL,
	ID_HELP_DOC_ONLINE,

	// Popup menu items
	ID_DISTANCE_CLEAR,
	ID_POPUP_PROPS,
	ID_POPUP_TO_TOP,
	ID_POPUP_TO_BOTTOM,
	ID_POPUP_SHOWALL,
	ID_POPUP_HIDEALL,
	ID_POPUP_OVR_DISK,
	ID_POPUP_OVR_MEM,

	ID_HIGHEST_MENU_ENUM,

	ID_FIRST_MRU_FILE = 200,
	ID_FIRST_MRU_LAYER = 250,
	ID_FIRST_MRU_IMPORT = 300,

	LayerTree_Ctrl = 1000
};

