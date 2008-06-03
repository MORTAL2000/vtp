//
// MenuEnum.h
//
// Copyright (c) 2001-2008 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

// ID for the menu commands
enum
{
	// start at 1, as 0 is reserved on OSX
	ID_FILE_EXIT = 1,
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_PREFS,
	ID_SPECIAL_DYMAX_TEXTURES,
	ID_SPECIAL_DYMAX_MAP,
	ID_SPECIAL_PROCESS_BILLBOARD,
	ID_SPECIAL_GEOCODE,
	ID_FILE_SAVE,

	ID_EDIT_DELETE,
	ID_EDIT_DESELECTALL,
	ID_EDIT_INVERTSELECTION,
	ID_EDIT_CROSSINGSELECTION,
	ID_EDIT_OFFSET,

	ID_LAYER_NEW,
	ID_LAYER_OPEN,
	ID_LAYER_SAVE,
	ID_LAYER_SAVE_AS,
	ID_LAYER_IMPORT,
	ID_LAYER_IMPORTTIGER,
	ID_LAYER_IMPORTNTF,
	ID_LAYER_IMPORTUTIL,
	ID_LAYER_IMPORT_MS,
	ID_LAYER_IMPORT_POINT,
	ID_LAYER_IMPORT_XML,
	ID_LAYER_IMPORT_DXF,
	ID_LAYER_PROPS,
	ID_LAYER_SETPROJ,
	ID_LAYER_CONVERTPROJ,
	ID_LAYER_FLATTEN,
	ID_VIEW_SHOWLAYER,

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

	ID_ELEV_REMOVERANGE,
	ID_ELEV_SETUNKNOWN,
	ID_ELEV_FILL_FAST,
	ID_ELEV_FILL_SLOW,
	ID_ELEV_FILL_REGIONS,
	ID_ELEV_SCALE,
	ID_ELEV_EXPORT,
	ID_ELEV_EXPORT_TILES,
	ID_ELEV_COPY,
	ID_ELEV_PASTE_NEW,
	ID_ELEV_SELECT,
	ID_ELEV_BITMAP,
	ID_ELEV_MERGETIN,
	ID_ELEV_TRIMTIN,

	ID_IMAGE_REPLACE_RGB,
	ID_IMAGE_CREATE_OVERVIEWS,
	ID_IMAGE_EXPORT_TILES,
	ID_IMAGE_EXPORT_PPM,

	ID_ROAD_SELECTROAD,
	ID_ROAD_SELECTNODE,
	ID_ROAD_SELECTWHOLE,
	ID_ROAD_DIRECTION,
	ID_ROAD_EDIT,
	ID_ROAD_SHOWNODES,
	ID_ROAD_SELECTHWY,
	ID_ROAD_CLEAN,
	ID_ROAD_GUESS,
	ID_ROAD_FLATTEN,

	ID_TOWER_ADD,
	ID_TOWER_SELECT,
	ID_TOWER_EDIT,

	ID_VEG_PLANTS,
	ID_VEG_BIOREGIONS,
	ID_VEG_REMAP,
	ID_VEG_EXPORTSHP,

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
	ID_STRUCTURE_EXPORT_FOOTPRINTS,

	ID_RAW_SETTYPE,
	ID_RAW_ADDPOINTS,
	ID_RAW_ADDPOINT_TEXT,
	ID_RAW_ADDPOINTS_GPS,
	ID_RAW_SELECTCONDITION,
	ID_RAW_EXPORT_IMAGEMAP,
	ID_RAW_EXPORT_KML,
	ID_RAW_GENERATE_ELEVATION,
	ID_RAW_STYLE,
	ID_RAW_SCALE,

	ID_AREA_ZOOM_ALL,
	ID_AREA_ZOOM_LAYER,
	ID_AREA_TYPEIN,
	ID_AREA_MATCH,
	ID_AREA_EXPORT_ELEV,
	ID_AREA_EXPORT_IMAGE,
	ID_AREA_EXPORT_ELEV_SPARSE,
	ID_AREA_EXPORT_IMAGE_OPT,
	ID_AREA_GENERATE_VEG,
	ID_AREA_VEG_DENSITY,
	ID_AREA_REQUEST_WFS,
	ID_AREA_REQUEST_WMS,
	ID_AREA_REQUEST_TSERVE,

	ID_HELP_DOC_LOCAL,
	ID_HELP_DOC_ONLINE,

	// Popup menu items
	ID_DISTANCE_CLEAR,
	ID_POPUP_TO_TOP,
	ID_POPUP_TO_BOTTOM,
	ID_POPUP_SHOWALL,
	ID_POPUP_HIDEALL,

	ID_HIGHEST_MENU_ENUM,

	LayerTree_Ctrl = 1000
};

