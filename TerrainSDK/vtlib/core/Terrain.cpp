//
// Terrain.cpp
//
// Copyright (c) 2001-2007 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"

#include "vtdata/vtLog.h"
#include "vtdata/CubicSpline.h"

#include "Terrain.h"
#include "Light.h"
#include "Building3d.h"
#include "IntersectionEngine.h"
#include "Fence3d.h"
#include "vtTin3d.h"
#include "PagedLodGrid.h"

#include "TVTerrain.h"
#include "SMTerrain.h"
#include "CustomTerrain.h"
#include "SRTerrain.h"
#include "DemeterTerrain.h"
#include "TiledGeom.h"
// add your own LOD method header here!


// The Terrain uses two LOD grids (class vtLodGrid, a sparse grid of LOD cells)
//  of size LOD_GRIDSIZE x LOD_GRIDSIZE to group structures and vegetation.
//  This allows them to be culled more efficiently.
#define LOD_GRIDSIZE		128


//////////////////////////////////////////////////////////////////////

vtTerrain::vtTerrain()
{
	m_bIsCreated = false;

	m_ocean_color.Set(40.0f/255, 75.0f/255, 124.0f/255);	// unshaded color
	m_fog_color.Set(1.0f, 1.0f, 1.0f);

	m_pTerrainGroup = NULL;
	m_pImage = NULL;
	m_pImageSource = NULL;
	m_pTerrMats = NULL;
	m_bBothSides = false;
	m_bTextureInitialized = false;
	m_iShadowTextureUnit = -1;

	m_pRoadMap = NULL;
	m_pInputGrid = NULL;
	m_pHeightField = NULL;
	m_bPreserveInputGrid = false;
	m_pElevGrid = NULL;
	m_pTextureColors = NULL;
	m_pDetailMats = NULL;
	m_pScaledFeatures = NULL;

	m_pHorizonGeom = NULL;
	m_pOceanGeom = NULL;
	m_pRoadGroup = NULL;

	// vegetation
	m_pVegGrid = NULL;
	m_pPlantList = NULL;

	m_pBBEngine = NULL;
	m_pEngineGroup = NULL;

	m_bShowPOI = true;
	m_pPOIGroup = NULL;

	m_pDynGeom = NULL;
	m_pDynGeomScale = NULL;
	m_pTin = NULL;
	m_pTiledGeom = NULL;
	m_pPagedStructGrid = NULL;

	// structures
	m_pActiveStructLayer = NULL;
	m_pStructGrid = NULL;

	// abstracts
	m_pActiveAbstractLayer = NULL;

	m_CamLocation.Identity();
	m_bVisited = false;

	m_CenterGeoLocation.Set(-999, -999);	// initially unknown

	m_pOverlay = NULL;
	m_progress_callback = NULL;
}

vtTerrain::~vtTerrain()
{
	VTLOG("Terrain destructing: '%s'\n", (const char *) GetName());

	// Remove the things this terrain has added to the scene
	if (m_pBBEngine)
	{
		m_pEngineGroup->RemoveChild(m_pBBEngine);
		delete m_pBBEngine;
	}

	// some things need to be manually deleted
	m_Content.ReleaseContents();
	m_Content.Empty();

	m_AnimContainer.Empty();

	unsigned int i, size = m_PointsOfInterest.GetSize();
	for (i = 0; i < size; i++)
	{
		POIPtr p = m_PointsOfInterest.GetAt(i);
		delete p;
	}

	size = m_Layers.GetSize();
	for (i = 0; i < size; i++)
	{
		vtStructureLayer *slay = dynamic_cast<vtStructureLayer*>(m_Layers[i]);
		vtAbstractLayer *alay = dynamic_cast<vtAbstractLayer*>(m_Layers[i]);
		vtImageLayer *ilay = dynamic_cast<vtImageLayer*>(m_Layers[i]);
		if (slay)
			delete slay;
		else if (alay)
			delete alay;
		else if (ilay)
			delete ilay;
	}

	// Do not delete the PlantList, the application may be sharing the same
	// list with several different terrains.
//	delete m_pPlantList;

	if (!m_bPreserveInputGrid)
		delete m_pElevGrid;

	if (m_pImage)
		m_pImage->Release();
	if (m_pImageSource != m_pImage)
		m_pImageSource->Release();
	m_ImageTiles.Release();

	delete m_pRoadMap;
	if (m_pRoadGroup)
	{
		m_pTerrainGroup->RemoveChild(m_pRoadGroup);
		m_pRoadGroup->Release();
	}
	if (m_pHorizonGeom)
	{
		m_pTerrainGroup->RemoveChild(m_pHorizonGeom);
		m_pHorizonGeom->Release();
	}
	if (m_pOceanGeom)
	{
		m_pTerrainGroup->RemoveChild(m_pOceanGeom);
		m_pOceanGeom->Release();
	}
	if (m_pStructGrid)
	{
		m_pTerrainGroup->RemoveChild(m_pStructGrid);
		m_pStructGrid->Release();
	}
	if (m_pVegGrid)
	{
		m_pTerrainGroup->RemoveChild(m_pVegGrid);
		m_pVegGrid->Release();
	}
//	delete m_pInputGrid;	// don't delete, copied to m_pElevGrid
	if (m_pDynGeom)
	{
		m_pDynGeomScale->RemoveChild(m_pDynGeom);
		m_pDynGeom->Release();
	}
	if (m_pDynGeomScale)
	{
		m_pTerrainGroup->RemoveChild(m_pDynGeomScale);
		m_pDynGeomScale->Release();
	}

	delete m_pTin;

	if (m_pTiledGeom)
	{
		//m_pDynGeomScale->RemoveChild(m_pTiledGeom);
		m_pTiledGeom->Release();
	}

	// This will mop up anything remaining in the terrain's scenegraph
	if (m_pTerrainGroup != (vtGroup*) NULL)
		m_pTerrainGroup->Release();

	if (m_pTerrMats)
		m_pTerrMats->Release();

	delete m_pTextureColors;

	if (m_pDetailMats)
		m_pDetailMats->Release();
}


///////////////////////////////////////////////////////////////////////

/**
 * Tells the terrain what file contains the parameters to use.
 *
 * \param fname The name of a terrain parameters file, e.g. "Simple.xml".
 */
bool vtTerrain::SetParamFile(const char *fname)
{
	m_strParamFile = fname;
	return LoadParams();
}

bool vtTerrain::LoadParams()
{
	TParams params;
	bool success = params.LoadFrom(m_strParamFile);
	if (success)
		SetParams(params);
	return success;
}

/**
 * Set all of the parameters for this terrain.
 *
 * \param Params An object which contains all the parameters for the terrain.
 *
 * \par Note that you can set individual parameters like this:
\code
	TParams &par = pTerrain->GetParams();
	par.SetBoolValue(STR_SKY, false);
\endcode
 */
void vtTerrain::SetParams(const TParams &Params)
{
	m_Params = Params;
	
	RGBi color;
	if (m_Params.GetValueRGBi(STR_FOGCOLOR, color))
	{
		if (color.r != -1)
			m_fog_color = color;
	}
	if (m_Params.GetValueRGBi(STR_BGCOLOR, color))
	{
		if (color.r != -1)
			m_background_color = color;
	}
}

/**
 * Returns a direct reference to the parameters object for this terrain, so
 * that you can get and set the parameters.
 *
 * \par Example:
\code
	TParams &par = pTerrain->GetParams();
	par.SetBoolValue(STR_SKY, false);
\endcode
 */
TParams &vtTerrain::GetParams()
{
	return m_Params;
}

/**
 * This method allows you to give the terrain a grid to use directly
 * instead of loading the BT file specified in the TParams.
 *
 * You must allocate this grid dynamically with 'new', since vtTerrain
 * will 'delete' it after using it during initialization.  If you don't
 * want the memory to be deleted, pass 'true' for bPreserve.
 *
 * \param pGrid The grid object which the terrain should use.
 * \param bPreserve True if the terrain should not delete the grid object,
 * otherwise false.
 *
 */
void vtTerrain::SetLocalGrid(vtElevationGrid *pGrid, bool bPreserve)
{
	m_pInputGrid = pGrid;
	m_bPreserveInputGrid = bPreserve;
}

/**
 * This method allows you to give the terrain a TIN to use directly
 * instead of loading a .tin file as specified in the TParams.
 */
void vtTerrain::SetTin(vtTin3d *pTin)
{
	m_pTin = pTin;
}


///////////////////////////////////////////////////////////////////////

void vtTerrain::_CreateRoads()
{
	// for GetValueFloat below
	LocaleWrap normal_numbers(LC_NUMERIC, "C");

	vtString road_fname = "RoadData/";
	road_fname += m_Params.GetValueString(STR_ROADFILE);
	vtString road_path = FindFileOnPaths(vtGetDataPath(), road_fname);
	if (road_path == "")
		return;

	VTLOG("Creating Roads: ");
	m_pRoadMap = new vtRoadMap3d;

	VTLOG("  Reading from file '%s'\n", (const char *) road_path);
	bool success = m_pRoadMap->ReadRMF(road_path,
		m_Params.GetValueBool(STR_HWY),
		m_Params.GetValueBool(STR_PAVED),
		m_Params.GetValueBool(STR_DIRT));
	if (!success)
	{
		VTLOG("	read failed.\n");
		delete m_pRoadMap;
		m_pRoadMap = NULL;
		return;
	}

	//some nodes may not have any roads attached to them.  delete them.
	m_pRoadMap->RemoveUnusedNodes();

	m_pRoadMap->DetermineSurfaceAppearance();

	m_pRoadMap->SetHeightOffGround(m_Params.GetValueFloat(STR_ROADHEIGHT));
	m_pRoadMap->DrapeOnTerrain(m_pHeightField);
	m_pRoadMap->BuildIntersections();

	m_pRoadMap->SetLodDistance(m_Params.GetValueFloat(STR_ROADDISTANCE) * 1000);	// convert km to m

	bool bDoTexture = m_Params.GetValueBool(STR_TEXROADS);
	m_pRoadGroup = m_pRoadMap->GenerateGeometry(bDoTexture, m_progress_callback);
	m_pTerrainGroup->AddChild(m_pRoadGroup);

	if (m_Params.GetValueBool(STR_ROADCULTURE))
		m_pRoadMap->GenerateSigns(m_pStructGrid);

	if (m_pRoadMap && m_Params.GetValueBool(STR_ROADCULTURE))
	{
		NodeGeom* node = m_pRoadMap->GetFirstNode();
		vtIntersectionEngine *lightEngine;
		char string[50];
		while (node)
		{
			if (node->HasLights())
			{
				// add an traffic control engine
				lightEngine = new vtIntersectionEngine(node);
				sprintf(string, "Traffic Control: Node %i", node->m_id);
				lightEngine->SetName2(string);
				AddEngine(lightEngine);
			}
			node = (NodeGeom*)node->m_pNext;
		}
	}
}


///////////////////

void vtTerrain::_CreateTextures(const FPoint3 &light_dir, bool progress_callback(int))
{
	// measure total texture processing time
	clock_t c1 = clock();

	int iTiles = 4;		// fixed for now
	TextureEnum eTex = m_Params.GetTextureEnum();

	if (!m_pTerrMats)
		m_pTerrMats = new vtMaterialArray;

	float ambient, diffuse, emmisive;
	diffuse = 1.0f;
	ambient = emmisive = 0.0f;

	int iTileSize = m_Params.GetValueInt(STR_TILESIZE);
	bool bRetain = m_Params.GetValueBool(STR_TEXTURE_RETAIN);

	bool bFirstTime = !m_bTextureInitialized;
	if (bFirstTime)
	{
		if (eTex == TE_SINGLE || eTex == TE_DERIVED)
			m_pImage = new vtImage;
		if (bRetain)
			m_pImageSource = new vtImage;
		else
			m_pImageSource = m_pImage;
	}
	// TODO: simplify this logic; it shouldn't need to be so complex.
	bool bLoad = (bFirstTime || !bRetain);
	bool bLoadSingle = bLoad && (eTex == TE_SINGLE || (eTex == TE_TILED && bRetain));
	bool bLoadTiles = bLoad && (eTex == TE_TILED && !bRetain);

	vtString texture_path;
	if (bLoadSingle || bLoadTiles)	// look for texture
	{
		vtString texname;
		if (eTex == TE_SINGLE)
		{
			texname = m_Params.GetValueString(STR_TEXTUREFILE);
			VTLOG("  Single Texture: '%s'\n", (const char *) texname);
		}
		else
		{
			texname = m_Params.GetValueString(STR_TEXTURE4BY4);
			VTLOG("  Tiled Texture: '%s'\n", (const char *) texname);
		}

		vtString texture_fname = "GeoSpecific/";
		texture_fname += texname;

		VTLOG("  Looking for: %s\n", (const char *) texture_fname);
		texture_path = FindFileOnPaths(vtGetDataPath(), texture_fname);
		if (texture_path == "")
		{
			// failed to find texture
			VTLOG("  Failed to find texture.\n");
			eTex = TE_NONE;
			bLoadSingle = bLoadTiles = false;
		}
		else
			VTLOG("  Found texture, path is: %s\n", (const char *) texture_path);
	}
	if (bLoadSingle)	// load texture
	{
		// Load a DIB of the whole, large texture
		clock_t r1 = clock();
		bool result = m_pImageSource->Read(texture_path, false, progress_callback);
		if (result)
		{
			int depth = m_pImageSource->GetDepth();
			VTLOG("  Load texture: depth %d, %.3f seconds.\n", depth, (float)(clock() - r1) / CLOCKS_PER_SEC);
		}
		else
		{
			VTLOG("  Failed to load texture.\n");
			m_pTerrMats->AddRGBMaterial(RGBf(1.0f, 1.0f, 1.0f),
										RGBf(0.2f, 0.2f, 0.2f),
										true, false);
			eTex = TE_NONE;
			_SetErrorMessage("Failed to load texture.");
		}
		// TODO? check that image size is correct, and warn if not.
	}
	if ((eTex == TE_SINGLE || eTex == TE_DERIVED) && bFirstTime)
	{
		// If the user has asked for 16-bit textures to be sent down to the
		//  card (internal memory format), then tell this vtImage
		m_pImage->Set16Bit(m_Params.GetValueBool(STR_REQUEST16BIT));
	}
	if (eTex == TE_TILED && bFirstTime)
	{
		int w, h, depth;
		vtImageInfo(texture_path, w, h, depth);
		m_ImageTiles.Create(iTileSize, depth);

		// If the user has asked for 16-bit textures to be sent down to the
		//  card (internal memory format), then tell this vtImage
		bool b16bit = m_Params.GetValueBool(STR_REQUEST16BIT);
		int i, j;
		for (i = 0; i < iTiles; i++)
			for (j = 0; j < iTiles; j++)
				m_ImageTiles.m_Tiles[i][j]->Set16Bit(b16bit);
	}
	if (bLoadTiles)
	{
		// alternate loading: load straight into tiled images
		clock_t r1 = clock();
		bool result = m_ImageTiles.Load(texture_path, progress_callback);
		if (result)
			VTLOG("  Load texture: %.3f seconds.\n", (float)(clock() - r1) / CLOCKS_PER_SEC);
		else
		{
			VTLOG("  Failed to load texture.\n");
			m_pTerrMats->AddRGBMaterial(RGBf(1.0f, 1.0f, 1.0f),
										RGBf(0.2f, 0.2f, 0.2f),
										true, false);
			eTex = TE_NONE;
			_SetErrorMessage("Failed to load texture.");
		}
	}

	vtHeightFieldGrid3d *pHFGrid = GetHeightFieldGrid3d();

	if (eTex == TE_DERIVED)
	{
		if (bFirstTime)
		{
			// Derive color from elevation.
			// Determine the correct size for the derived texture: ideally
			// as large as the input grid, but not larger than the hardware
			// texture size limit.
			int tmax = vtGetMaxTextureSize();

			int cols, rows;
			pHFGrid->GetDimensions(cols, rows);

			int tsize = cols-1;
			if ((tmax > 0) && (tsize > tmax))
				tsize = tmax;
			VTLOG("\t grid width is %d, texture max is %d, creating artificial texture of dimension %d\n",
				cols, tmax, tsize);

			m_pImageSource->Create(tsize, tsize, 24, false);
		}
		if (bFirstTime || !bRetain)
		{
			// This method is virtual to allow subclasses to customize the Dib,
			//  before we turn it into an vtImage
			PaintDib(progress_callback);
		}
	}

	if (bRetain)
	{
		// We need to copy from the retained image to the displayed image
		if (eTex == TE_SINGLE || eTex == TE_DERIVED)
		{
			if (bFirstTime)
			{
				int w = m_pImageSource->GetWidth();
				int h = m_pImageSource->GetHeight();
				int d = m_pImageSource->GetDepth();
				m_pImage->Create(w, h, d);
			}
			m_pImageSource->BlitTo(*m_pImage, 0, 0);
		}
		else if (eTex == TE_TILED)
		{
			m_pImageSource->BlitTo(m_ImageTiles, 0, 0);
		}
	}

	// If we get this far, we can consider the texture initialized
	m_bTextureInitialized = true;

	if (eTex == TE_NONE)	// none or failed to find texture
	{
		// no texture: create plain white material
		m_pTerrMats->AddRGBMaterial(RGBf(1.0f, 1.0f, 1.0f),
									RGBf(0.2f, 0.2f, 0.2f),
									true, false);
		return;
	}
	if (m_Params.GetValueBool(STR_PRELIGHT) && pHFGrid)
	{
		// apply pre-lighting (darkening)
		vtBitmapBase *target;
		if (eTex == TE_TILED)
			target = &m_ImageTiles;
		else
			target = m_pImage;
		_ApplyPreLight(pHFGrid, target, light_dir, progress_callback);
	}

	// The terrain's base texture will always use unit 0
	m_TextureUnits.ReserveTextureUnit();

	if (eTex == TE_SINGLE || eTex == TE_DERIVED)
	{
		// single texture
		if (bFirstTime)
			_CreateSingleMaterial(ambient, diffuse, emmisive);
		else
		{
			VTLOG("Marking texture image as modified.\n");
			vtMaterial *mat = m_pTerrMats->GetAt(0);
			mat->ModifiedTexture();
		}
	}
	if (eTex == TE_TILED)
	{
		if (bFirstTime)
			_CreateTiledMaterials(iTiles, ambient, diffuse, emmisive);
		else
		{
			// we don't need to re-create the materials, but we do have to
			//  let the scenegraph know the texture contents have changed.
			for (unsigned int i = 0; i < m_pTerrMats->GetSize(); i++)
				m_pTerrMats->GetAt(i)->ModifiedTexture();
		}
	}
	VTLOG("  Total CreateTextures: %.3f seconds.\n", (float)(clock() - c1) / CLOCKS_PER_SEC);
}

//
// prepare detail texture
//
void vtTerrain::_CreateDetailTexture()
{
	// for GetValueFloat below
	LocaleWrap normal_numbers(LC_NUMERIC, "C");

	vtString fname = m_Params.GetValueString(STR_DTEXTURE_NAME);
	vtString path = FindFileOnPaths(vtGetDataPath(), fname);
	if (path == "")
	{
		vtString prefix = "GeoTypical/";
		path = FindFileOnPaths(vtGetDataPath(), prefix+fname);
		if (path == "")
			return;
	}
	vtDIB dib;
	if (!dib.Read(path))
		return;

	m_pDetailMats = new vtMaterialArray;
	vtImage *pDetailTexture = new vtImage(&dib);

	int index = m_pDetailMats->AddTextureMaterial(pDetailTexture,
					 true,	// culling
					 false,	// lighting
					 true,	// transp: blend
					 false,	// additive
					 0.0f, 1.0f,	// ambient, diffuse
					 0.5f, 0.0f,	// alpha, emmisive
					 true, false,	// texgen, clamp
					 true);			// mipmap
	vtMaterial *pDetailMat = m_pDetailMats->GetAt(index);

	// pass ownership to the material
	pDetailTexture->Release();

	float scale = m_Params.GetValueFloat(STR_DTEXTURE_SCALE);
	float dist = m_Params.GetValueFloat(STR_DTEXTURE_DISTANCE);

	FRECT r = m_pHeightField->m_WorldExtents;
	float width_meters = r.Width();
	m_pDynGeom->SetDetailMaterial(pDetailMat, width_meters / scale, dist);
}

//
// This is the default implementation for PaintDib.  It colors from elevation.
// Developer might override it.
//
void vtTerrain::PaintDib(bool progress_callback(int))
{
	if (!m_pTextureColors)
	{
		// If this member hasn't been set by a subclass, then we can go ahead
		//  and use the info from the terrain parameters
		m_pTextureColors = new ColorMap;
		ColorMap cmap;
		vtString name = m_Params.GetValueString(STR_COLOR_MAP);
		if (name != "")
		{
			if (!m_pTextureColors->Load(name))
			{
				// Look on data paths
				vtString name2 = "GeoTypical/";
				name2 += name;
				name2 = FindFileOnPaths(vtGetDataPath(), name2);
				if (name2 != "")
					m_pTextureColors->Load(name2);
			}
		}
		// If the colors weren't provided by a subclass, and couldn't be
		//  loaded either, then make up some default colors.
		if (m_pTextureColors->Num() == 0)
		{
			m_pTextureColors->m_bRelative = true;
			m_pTextureColors->Add(0, RGBi(0x20, 0x90, 0x20));	// medium green
			m_pTextureColors->Add(1, RGBi(0x40, 0xE0, 0x40));	// light green
			m_pTextureColors->Add(2, RGBi(0xE0, 0xD0, 0xC0));	// tan
			m_pTextureColors->Add(3, RGBi(0xE0, 0x80, 0x10));	// orange
			m_pTextureColors->Add(4, RGBi(0xE0, 0xE0, 0xE0));	// light grey
		}
	}
	vtHeightFieldGrid3d *pHFGrid = GetHeightFieldGrid3d();
	pHFGrid->ColorDibFromElevation(m_pImageSource, m_pTextureColors, 4000);
}

/**
 * Set the array of colors to be used when automatically generating the
 * terrain texture from the elevation values.  This is the color map which
 * is used for automatic generation of texture from elevation, when the
 * terrain is built normally with the "Derived" texture option.
 * The colors brackets go from the lowest elevation value to the highest.
 *
 * \param colors A pointer to a colormap.  The terrain takes ownership of
 *		the ColorMap object so it will be deleted when the terrain is deleted.
 *
 * \par Example:
	\code
	ColorMap *colors = new ColorMap;
	colors->m_bRelative = false;
	colors->Add(100, RGBi(0,255,0));
	colors->Add(200, RGBi(255,200,150));
	pTerr->SetTextureColors(colors);
	\endcode
 */
void vtTerrain::SetTextureColors(ColorMap *colors)
{
	m_pTextureColors = colors;
}

/**
 * This method sets the terrain's color map to a series of white and black
 * bands which indicate elevation contour lines.  This is the color map
 * which is used for automatic generation of texture from elevation, when
 * the terrain is built normally with the "Derived" texture option.
 *
 * You can use this function either before the terrain is built, or
 * afterwards if you intend to re-build the textures.
 *
 * \par Example:
	\code
	vtTerrain *pTerr = new vtTerrain;
	pTerr->SetTextureColors(100, 4);
	\endcode
 *
 * \param fInterval  The vertical spacing between the contours.  For example,
 *		if the elevation range of your data is from 50 to 350 meters, then
 *		an fIterval of 100 will place contour bands at 100,200,300 meters.
 * \param fSize  The vertical thickness of each contour band, generally a
 *		few meters.  A band of this thickness will be centered on each contour
 *		line of the desired elevation.
 */
void vtTerrain::SetTextureContours(float fInterval, float fSize)
{
	// Create a color map and fill it with contour strip bands
	ColorMap *cmap = new ColorMap;
	cmap->m_bBlend = true;
	cmap->m_bRelative = false;

	RGBi white(255,255,255);
	RGBi black(0,0,0);

	float fMin, fMax;
	m_pHeightField->GetHeightExtents(fMin, fMax);
	int start = (int) (fMin / fInterval);
	int stop = (int) (fMax / fInterval);

	cmap->Add(fMin, white);
	for (int i = start; i < stop; i++)
	{
		// create a black stripe of the desired vertical thickness
		cmap->Add(i * fInterval - fSize*0.8f, white);
		cmap->Add(i * fInterval - fSize*0.5f, black);
		cmap->Add(i * fInterval + fSize*0.5f, black);
		cmap->Add(i * fInterval + fSize*0.8f, white);
	}

	// Set these as the desired color bands for the next PainDib
	m_pTextureColors = cmap;
}


/**
 * Re-create the ground texture.  This is useful if you ahve changed the
 * time of day, and want to see the lighting/shading of the terrain updated.
 */
void vtTerrain::RecreateTextures(vtTransform *pSunLight, bool progress_callback(int))
{
	_CreateTextures(pSunLight->GetDirection(), progress_callback);
}

/**
 * Get the image (vtImage) of the ground texture, if there is one.  If the
 * texture is more complicated (multi or tiled) then NULL is returned.
 */
vtImage *vtTerrain::GetTextureImage()
{
	return m_pImage;
}


/////////////////////

bool vtTerrain::_CreateDynamicTerrain()
{
	int texture_patches;
	if (m_Params.GetTextureEnum() == TE_TILED)
		texture_patches = 4;	// tiled, which is always 4x4
	else
		texture_patches = 1;	// assume one texture

	LodMethodEnum method = m_Params.GetLodMethod();
	VTLOG(" LOD method %d\n", method);

	if (method == LM_TOPOVISTA)
	{
		m_pDynGeom = new TVTerrain();
		m_pDynGeom->SetName2("TV Geom");
	}
	else if (method == LM_MCNALLY)
	{
		m_pDynGeom = new SMTerrain();
		m_pDynGeom->SetName2("Seumas Geom");
	}
	else if (method == LM_DEMETER)
	{
#if 0	// disabled until its working
		m_pDynGeom = new DemeterTerrain();
		m_pDynGeom->SetName2("Demeter Geom");
#endif
	}
	else if (method == LM_CUSTOM)
	{
		m_pDynGeom = new CustomTerrain();
		m_pDynGeom->SetName2("CustomTerrain Geom");
	}
	else if (method == LM_ROETTGER)
	{
		m_pDynGeom = new SRTerrain();
		m_pDynGeom->SetName2("Roettger Geom");
	}
	// else if (method == LM_YOURMETHOD)
	// {
	//	add your own LOD method here!
	// }
	if (!m_pDynGeom)
	{
		_SetErrorMessage("Unknown LOD method.");
		return false;
	}

	m_pDynGeom->SetOptions(m_Params.GetValueBool(STR_TRISTRIPS),
		texture_patches, m_Params.GetValueInt(STR_TILESIZE));

	DTErr result = m_pDynGeom->Init(m_pElevGrid, m_fVerticalExag);
	if (result != DTErr_OK)
	{
		m_pDynGeom->Release();
		m_pDynGeom = NULL;

		_CreateErrorMessage(result, m_pElevGrid);
		VTLOG(" Could not initialize CLOD: %s\n", (const char *) m_strErrorMsg);
		return false;
	}

#if VTLIB_OSG
	//
	// This is a hack to allow a transparent terrain surface.
	//  In order for OSG to draw the transparent surface correctly, it needs
	//  to know it's in the the "TRANSPARENT" render bin.  But because
	//  our surface draws itself, OSG doesn't know at binning time that
	//  it's transparent.  So, we have to tell it ahead of time.
	//
	if (m_Params.GetTextureEnum() == TE_SINGLE)
	{
		vtMaterial *mat = m_pTerrMats->GetAt(0);
		if (mat->GetTransparent())
		{
			osg::StateSet *sset = m_pDynGeom->GetOsgNode()->getOrCreateStateSet();
			sset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		}
	}
#endif

	m_pDynGeom->SetPolygonTarget(m_Params.GetValueInt(STR_TRICOUNT));
	m_pDynGeom->SetMaterials(m_pTerrMats);

	// build heirarchy (add terrain to scene graph)
	m_pDynGeomScale = new vtTransform;
	m_pDynGeomScale->SetName2("Dynamic Geometry Scaling Container");

	FPoint2 spacing = m_pElevGrid->GetWorldSpacing();
	m_pDynGeomScale->Scale3(spacing.x, m_fVerticalExag, -spacing.y);

	m_pDynGeomScale->AddChild(m_pDynGeom);
	m_pTerrainGroup->AddChild(m_pDynGeomScale);

	// the Dynamic terrain will be the heightfield used at runtime, so extend
	//  it with the terrain's culture
	m_pDynGeom->SetCulture(this);

	return true;
}

void vtTerrain::SetVerticalExag(float fExag)
{
	m_fVerticalExag = fExag;

	if (m_pDynGeom != NULL)
	{
		FPoint2 spacing = m_pDynGeom->GetWorldSpacing();
		m_pDynGeomScale->Identity();
		m_pDynGeomScale->Scale3(spacing.x, m_fVerticalExag, -spacing.y);

		m_pDynGeom->SetVerticalExag(m_fVerticalExag);
	}
	else if (m_pTiledGeom != NULL)
	{
		m_pTiledGeom->SetVerticalExag(m_fVerticalExag);
	}
	if (m_pScaledFeatures != NULL)
	{
		m_pScaledFeatures->Identity();
		m_pScaledFeatures->Scale3(1.0f, m_fVerticalExag, 1.0f);
	}
}

void vtTerrain::_CreateErrorMessage(DTErr error, vtElevationGrid *pGrid)
{
	int x, y;
	pGrid->GetDimensions(x, y);
	switch (error)
	{
	case DTErr_OK:
		m_strErrorMsg = "No Error";
		break;
	case DTErr_EMPTY_EXTENTS:
		m_strErrorMsg.Format("The elevation has empty extents.");
		break;
	case DTErr_NOTSQUARE:
		m_strErrorMsg.Format("The elevation grid (%d x %d) is not square.", x, y);
		break;
	case DTErr_NOTPOWER2:
		m_strErrorMsg.Format("The elevation grid (%d x %d) is of an unsupported size.",
			x, y);
		break;
	case DTErr_NOMEM:
		m_strErrorMsg = "Not enough memory for CLOD.";
		break;
	default:
		m_strErrorMsg = "Unknown error.";
	}
}

void vtTerrain::_SetErrorMessage(const vtString &msg)
{
	m_strErrorMsg = msg;
	VTLOG("\t%s.\n", (const char *) msg);
}


bool vtTerrain::AddFence(vtFence3d *fen)
{
	vtStructureArray3d *structs = GetStructureLayer();
	if (!structs)
		return false;

	structs->Append(fen);
	fen->CreateNode(this);

	// Add to LOD grid
	AddNodeToStructGrid(fen->GetGeom());
	return true;
}

void vtTerrain::AddFencepoint(vtFence3d *f, const DPoint2 &epos)
{
	// Adding a fence point might change the fence extents such that it moves
	// to a new LOD cell.  So, remove it from the LOD grid, add the point,
	// then add it back.
	m_pStructGrid->RemoveFromGrid(f->GetGeom());

	f->AddPoint(epos);

	f->CreateNode(this);

	AddNodeToStructGrid(f->GetGeom());
}

void vtTerrain::RedrawFence(vtFence3d *f)
{
	f->CreateNode(this);
}

// routes
void vtTerrain::AddRoute(vtRoute *f)
{
	m_Routes.Append(f);

	// Add directly
	m_pTerrainGroup->AddChild(f->GetGeom());
}

void vtTerrain::add_routepoint_earth(vtRoute *route, const DPoint2 &epos,
									 const char *structname)
{
	VTLOG("Route AddPoint %.1lf %.1lf\n", epos.x, epos.y);
	route->AddPoint(epos, structname);
	route->BuildGeometry(m_pHeightField);
}

void vtTerrain::RedrawRoute(vtRoute *route)
{
	route->BuildGeometry(m_pHeightField);
}

void vtTerrain::SaveRoute()
{
}

/**
 * Create a horizontal plane at sea level.
 *
 * If the terrain has a large body of water on 1 or more sides, this method
 * is useful for extending the water to the horizon by creating additional
 * ocean plane geometry.
 *
 * \param fAltitude The height (Y-value) of the horizontal plane.
 * \param bWater True for a watery material, false for a land material
 * \param bHorizon If true, create tiles extending from the terrain extents
 *		to the horizon.
 * \param bCenter If true, create a tile in the center (covering the terrain
 *		extents).
 * \param fTransparency A value from 0 (tranparent) to 1 (opaque)
 */
void vtTerrain::CreateArtificialHorizon(float fAltitude, bool bWater, bool bHorizon,
										  bool bCenter, float fTransparency)
{
	// for GetValueFloat below
	LocaleWrap normal_numbers(LC_NUMERIC, "C");

	int VtxType;

	vtMaterialArray *pHorizonMaterials = new vtMaterialArray;

	// Ocean material: texture waves
	vtString fname = FindFileOnPaths(vtGetDataPath(), "GeoTypical/ocean1_256.jpg");
	pHorizonMaterials->AddTextureMaterial2(fname,
		false, false,		// culling, lighting
		false,				// the texture itself has no alpha
		false,				// additive
		TERRAIN_AMBIENT,	// ambient
		1.0f,				// diffuse
		fTransparency,		// alpha
		TERRAIN_EMISSIVE,	// emissive
		false,				// texgen
		false,				// clamp
		false);				// don't mipmap: allowing texture aliasing to
							// occur, it actually looks more water-like
		VtxType = VT_Normals;

	// Ground plane (horizon) material
	pHorizonMaterials->AddRGBMaterial1(RGBf(1.0f, 0.8f, 0.6f),
		false, true, false);		// cull, light, wire

	FRECT world_extents = m_pHeightField->m_WorldExtents;
	FPoint2 world_size(world_extents.Width(), world_extents.Height());

	// You can adjust these factors:
	const int STEPS = 5;
	const int TILING = 1;

	if (bWater)
	{
		vtGeom *pOceanGeom = new vtGeom;
		pOceanGeom->SetMaterials(pHorizonMaterials);

		float fOceanPlaneLevel = m_Params.GetValueFloat(STR_OCEANPLANELEVEL);

		FPoint2 tile_size = world_size / TILING;
		for (int i = -STEPS*TILING; i < (STEPS+1)*TILING; i++)
		{
			for (int j = -(STEPS)*TILING; j < (STEPS+1)*TILING; j++)
			{
				// skip center tile
				if (i >= 0 && i < TILING &&
					j >= 0 && j < TILING)
				{
					// we are in the middle
					if (!bCenter) continue;
				}
				else {
					if (!bHorizon) continue;
				}

				FPoint2 base;
				base.x = world_extents.left + (i * tile_size.x);
				base.y = world_extents.top - ((j+1) * tile_size.y);

				vtMesh *mesh = new vtMesh(vtMesh::TRIANGLE_STRIP, VT_Normals | VT_TexCoords, 4);
				mesh->CreateRectangle(1, 1, 0, 2, 1, base, base+tile_size,
					fOceanPlaneLevel, 5.0f);

				pOceanGeom->AddMesh(mesh, 0);	// 0 = ocean material
				mesh->Release();	// pass ownership to the Geometry
			}
		}
		m_pOceanGeom = new vtMovGeom(pOceanGeom);
		m_pOceanGeom->SetName2("Ocean plane");
		m_pTerrainGroup->AddChild(m_pOceanGeom);
	}
	if (bHorizon)
	{
		vtGeom *pHorizonGeom = new vtGeom;
		pHorizonGeom->SetMaterials(pHorizonMaterials);

		FPoint2 tile_size = world_size;
		for (int i = -STEPS; i < (STEPS+1); i++)
		{
			for (int j = -(STEPS); j < (STEPS+1); j++)
			{
				// skip center tile
				if (i == 0 && j == 0)
					// we are in the middle
					continue;

				FPoint2 base;
				base.x = world_extents.left + (i * tile_size.x);
				base.y = world_extents.top - ((j+1) * tile_size.y);

				vtMesh *mesh = new vtMesh(vtMesh::TRIANGLE_STRIP, VT_Normals, 4);
				mesh->CreateRectangle(1, 1, 0, 2, 1, base, base+tile_size,
					fAltitude, 5.0f);

				pHorizonGeom->AddMesh(mesh, 1);	// 1 = land material
				mesh->Release();	// pass ownership to the Geometry
			}
		}
		m_pHorizonGeom = new vtMovGeom(pHorizonGeom);
		m_pHorizonGeom->SetName2("Horizon plane");
		m_pTerrainGroup->AddChild(m_pHorizonGeom);
	}
	// pass ownership
	pHorizonMaterials->Release();
}


//
// set global projection based on this terrain's heightfield
//
void vtTerrain::SetGlobalProjection()
{
	if (m_pHeightField)
		g_Conv = m_pHeightField->m_Conversion;
}

/**
 * For this terrain, look at its elevation source, and determine the extents
 * of that data, in geographic coords.  This is done without actually doing
 * a full load of the data, to quickly describe the terrain's location on
 * the earth.
 */
bool vtTerrain::GetGeoExtentsFromMetadata()
{
	vtString name = "Elevation/";
	name += m_Params.GetValueString(STR_ELEVFILE);
	vtString fname = FindFileOnPaths(vtGetDataPath(), name);
	if (fname == "")
	{
		VTLOG("\t'%s' not found on data paths.\n", (const char *)name);
		return false;
	}
	bool success;
	int type = m_Params.GetValueInt(STR_SURFACE_TYPE);
	if (type == 0)	// grid
	{
		vtElevationGrid grid;
		success = grid.LoadBTHeader(fname);
		if (!success)
		{
			VTLOG("\tCouldn't load BT header.\n");
			return false;
		}
		success = grid.GetCorners(m_Corners_geo, true);	// true=Geo
		if (!success)
		{
			VTLOG("\tCouldn't get terrain corners.\n");
			return false;
		}
	}
	else if (type == 1)	// tin
	{
		return false;	// TODO
	}
	else if (type == 2)	// tileset
	{
		TiledDatasetDescription set;
		success = set.Read(fname);
		if (!success)
		{
			VTLOG("\tCouldn't load Tileset description.\n");
			return false;
		}
		success = set.GetCorners(m_Corners_geo, true);	// true=Geo
		if (!success)
		{
			VTLOG("\tCouldn't get terrain corners.\n");
			return false;
		}
	}
	return true;
}


///////////////////////////////////////////////
// Built Structures

/**
 * Attempt to load structures from a VTST file.  If successful, the structures
 * will be added to the Terrain's set of structure arrays.
 */
vtStructureLayer *vtTerrain::LoadStructuresFromXML(const vtString &strFilename)
{
	VTLOG("LoadStructuresFromXML '%s'\n", (const char *) strFilename);
	vtStructureLayer *structures = NewStructureLayer();
	if (!structures->ReadXML(strFilename))
	{
		VTLOG("\tCouldn't load file.\n");
		m_Layers.Remove(structures);
		delete structures;
		m_pActiveStructLayer = NULL;
		return NULL;
	}
	return structures;
}

void vtTerrain::CreateStructures(vtStructureArray3d *structures)
{
	int num_structs = structures->GetSize();
	VTLOG("CreateStructures, %d structs\n", num_structs);

	bool bPaging = m_Params.GetValueBool("PagingStructures");
	if (bPaging)
	{
		// Don't construct geometry, just add to the paged structure grid
		m_iPagingStructureMax = m_Params.GetValueInt("PagingStructureMax");
		m_fPagingStructureDist = m_Params.GetValueInt("PagingStructureDist");

		VTLOG("\tAppending %d structures to the paged grid.\n", num_structs);
		for (int i = 0; i < num_structs; i++)
		{
			m_pPagedStructGrid->AppendToGrid(structures, i);
		}
	}
	else
	{
		int suceeded = 0;
		for (int i = 0; i < num_structs; i++)
		{
			bool bSuccess = CreateStructure(structures, i);
			if (bSuccess)
				suceeded++;
			if (m_progress_callback != NULL)
				m_progress_callback(i * 100 / num_structs);
		}
		VTLOG("\tSuccessfully created and added %d of %d structures.\n",
			suceeded, num_structs);
	}
}

bool vtTerrain::CreateStructure(vtStructureArray3d *structures, int index)
{
	vtStructure3d *str3d = structures->GetStructure3d(index);

	// Construct
	bool bSuccess = structures->ConstructStructure(str3d);
	if (!bSuccess)
	{
		VTLOG("\tFailed to create stucture %d\n", index);
		return false;
	}

	bSuccess = false;
	vtTransform *pTrans = str3d->GetContainer();
	if (pTrans)
		bSuccess = AddNodeToStructGrid(pTrans);
	else
	{
		vtGeom *pGeom = str3d->GetGeom();
		if (pGeom)
			bSuccess = AddNodeToStructGrid(pGeom);
	}
	if (!bSuccess)
	{
		VTLOG("\tWarning: Structure %d apparently not within bounds of terrain grid.\n", index);
		structures->DestroyStructure(index);
	}

	return bSuccess;
}

void vtTerrain::SetStructureLayer(vtStructureLayer *sa)
{
	m_pActiveStructLayer = sa;
}

/**
 * Get the currently active structure layer for this terrain.
 */
vtStructureLayer *vtTerrain::GetStructureLayer()
{
	return m_pActiveStructLayer;
}

/**
 * Create a new structure array for this terrain, and return it.
 */
vtStructureLayer *vtTerrain::NewStructureLayer()
{
	vtStructureLayer *slay = new vtStructureLayer;

	// these structures will use the heightfield and projection of this terrain
	slay->SetTerrain(this);
	slay->m_proj = m_proj;

	m_Layers.Append(slay);
	m_pActiveStructLayer = slay;
	return slay;
}

/**
 * Delete all the selected structures in the terrain's active structure array.
 */
int vtTerrain::DeleteSelectedStructures()
{
	vtStructureArray3d *structures = GetStructureLayer();

	// first remove them from the terrain
	for (unsigned int i = 0; i < structures->GetSize(); i++)
	{
		vtStructure *str = structures->GetAt(i);
		if (str->IsSelected())
		{
			// Remove it from the paging grid
			if (m_pPagedStructGrid)
				m_pPagedStructGrid->RemoveFromGrid(structures, i);

			vtStructure3d *str3d = structures->GetStructure3d(i);
			vtNode *node = str3d->GetContainer();
			if (!node)
				node = str3d->GetGeom();
			RemoveNodeFromStructGrid(node);
		}
	}

	// then do a normal delete-selected
	return structures->DeleteSelected();
}

bool vtTerrain::FindClosestStructure(const DPoint2 &point, double epsilon,
					   int &structure, double &closest, float fMaxInstRadius,
					   float fLinearWidthBuffer)
{
	structure = -1;
	closest = 1E8;

	// if all structures are hidden, don't find them
	if (!GetFeatureVisible(TFT_STRUCTURES))
		return false;

	double dist;
	int i, index, layers = m_Layers.GetSize();
	for (i = 0; i < layers; i++)
	{
		vtStructureLayer *slay = dynamic_cast<vtStructureLayer*>(m_Layers[i]);
		if (!slay)
			continue;
		if (slay->FindClosestStructure(point, epsilon, index, dist,
			fMaxInstRadius, fLinearWidthBuffer))
		{
			if (dist < closest)
			{
				structure = index;
				closest = dist;
				m_pActiveStructLayer = slay;
			}
		}
	}
	return (structure != -1);
}

/**
 * Loads an external 3D model as a movable node.  The file will be looked for
 * on the Terrain's data path, and wrapped with a vtTransform so that it can
 * be moved.
 *
 * To add the model to the Terrain's scene graph, use <b>AddModel</b> or
 * <b>AddModelToLodGrid</b>.  To plant the model on the terrain, use
 * <b>PlantModel</b> or <b>PlantModelAtPoint</b>.
 *
 * You should also make sure that your model is displayed at the correct
 * scale.  If the units are of the model are not meters, you should scale
 * the correct factor so that it matches the units of the Terrain:
 *
 * \par Example:
	\code
MyTerrain::CreateCustomCulture()
{
	// model is in centimeters (cm)
	vtTransform *pFountain = LoadModel("Culture/fountain.3ds");

	pFountain->Scale3(.01f, .01f, .01f);

	PlantModelAtPoint(pFountain, DPoint2(217690, 4123475));
	AddModel(pFountain);
}
	\endcode
 */
vtTransform *vtTerrain::LoadModel(const char *filename, bool bAllowCache)
{
	vtNode *node = NULL;
	vtString path = FindFileOnPaths(vtGetDataPath(), filename);
	if (path == "")
	{
		VTLOG("Couldn't locate file '%s'\n", filename);
	}
	else
		node = vtNode::LoadModel(path, bAllowCache);

	if (node)
	{
		vtTransform *trans = new vtTransform;
		trans->AddChild(node);
		return trans;
	}
	else
		return NULL;
}


/**
 * "Plants" a model on the ground.  This is done by moving the model directly
 * up or down such that its local origin is at the height of the terrain.
 *
 * Note: this function does not add the model to the terrain's scene
 * graph.  Use <b>AddNode</b> for that operation.
 */
void vtTerrain::PlantModel(vtTransform *model)
{
	FPoint3 pos = model->GetTrans();
	m_pHeightField->FindAltitudeAtPoint(pos, pos.y);
	model->SetTrans(pos);
}


/**
 * "Plants" a model on the ground.  This is done by moving the node to the
 * indicated earth coordinate, then moving it directly up or down such that
 * its local origin is at the height of the terrain.
 *
 * \param model The model to be placed on the terrain.
 * \param pos The position (in earth coordinates) at which to place it.
 * This position is assumed to be in the same coordinate system that
 * the Terrain is using.
 *
 * Note: this function does not add the model to the terrain's scene
 * graph.  Use <b>AddNode</b> for that operation.
 */
void vtTerrain::PlantModelAtPoint(vtTransform *model, const DPoint2 &pos)
{
	FPoint3 wpos;

	m_pHeightField->m_Conversion.convert_earth_to_local_xz(pos.x, pos.y, wpos.x, wpos.z);
	m_pHeightField->FindAltitudeAtPoint(wpos, wpos.y);
	model->SetTrans(wpos);
}

void vtTerrain::_CreateCulture()
{
	// Read terrain-specific content file
	vtString con_file = m_Params.GetValueString(STR_CONTENT_FILE);
	if (con_file != "")
	{
		VTLOG(" Looking for terrain-specific content file: '%s'\n", (const char *) con_file);
		vtString fname = FindFileOnPaths(vtGetDataPath(), con_file);
		if (fname != "")
		{
			VTLOG("  Found.\n");
			try
			{
				m_Content.ReadXML(fname);
			}
			catch (xh_io_exception &ex)
			{
				// display (or a least log) error message here
				VTLOG("  XML error:");
				VTLOG(ex.getFormattedMessage().c_str());
				return;
			}
		}
		else
			VTLOG("  Not found.\n");
	}

	// Always create a LOD grid for structures, as the user might create some
	// The LOD distances are in meters
	_SetupStructGrid((float) m_Params.GetValueInt(STR_STRUCTDIST));

	// create roads
	if (m_Params.GetValueBool(STR_ROADS))
		_CreateRoads();

	m_pBBEngine = new vtSimpleBillboardEngine(PID2f);
	m_pBBEngine->SetName2("Billboard Engine");
	m_pEngineGroup->AddChild(m_pBBEngine);

	_CreateVegetation();
	_CreateStructures();

	// create utility structures (routes = towers and wires)
	if (m_Params.GetValueBool(STR_ROUTEENABLE))
	{
		// TODO
	}

	// create HUD overlay geometry
	vtString fname;
	int x, y;
	if (m_Params.GetOverlay(fname, x, y))
	{
		vtImageSprite *pSprite = new vtImageSprite;
		if (pSprite->Create(fname, true))	// blending true
		{
			m_pOverlay = new vtGroup;
			IPoint2 size = pSprite->GetSize();
			pSprite->SetPosition((float) x, (float) y+size.y, (float) x+size.x, (float) y);
			m_pOverlay->AddChild(pSprite->GetNode());
		}
	}

	// Let any terrain subclasses provide their own culture
	CreateCustomCulture();
}


//
// Create an LOD grid to contain and efficiently hide stuff that's far away
//
void vtTerrain::_SetupVegGrid(float fLODDistance)
{
	// must have a terrain with some size
	if (!m_pHeightField)
		return;

	FRECT world_extents;
	world_extents = m_pHeightField->m_WorldExtents;

	FPoint3 org(world_extents.left, 0.0f, world_extents.bottom);
	FPoint3 size(world_extents.right, 0.0f, world_extents.top);

	m_pVegGrid = new vtSimpleLodGrid;
	m_pVegGrid->Setup(org, size, LOD_GRIDSIZE, fLODDistance, m_pHeightField);
	m_pVegGrid->SetName2("Vegetation LOD Grid");
	m_pTerrainGroup->AddChild(m_pVegGrid);
}

// create vegetation
void vtTerrain::_CreateVegetation()
{
	// The vegetation nodes will be contained in an LOD Grid
	_SetupVegGrid((float) m_Params.GetValueInt(STR_VEGDISTANCE));

	m_PIA.SetHeightField(m_pHeightField);

	// In case we don't load any plants, or fail to load, we will start with
	// an empty plant array, which needs to match the projection of the rest
	// of the terrain.
	m_PIA.SetProjection(GetProjection());

	clock_t r1 = clock();	// start timing
	if (m_Params.GetValueBool(STR_TREES))
	{
		vtString fname = m_Params.GetValueString(STR_TREEFILE);

		// Read the VF file
		vtString plants_fname = "PlantData/";
		plants_fname += fname;

		VTLOG("\tLooking for plants file: %s\n", (const char *) plants_fname);

		vtString plants_path = FindFileOnPaths(vtGetDataPath(), plants_fname);
		if (plants_path == "")
		{
			VTLOG("\tNot found.\n");
		}
		else
		{
			VTLOG("\tFound: %s\n", (const char *) plants_path);

			bool success;
			if (!fname.Right(3).CompareNoCase("shp"))
				success = m_PIA.ReadSHP(plants_path);
			else
				success = m_PIA.ReadVF(plants_path);
			if (success)
			{
				VTLOG("\tLoaded plants file.\n");
				m_PIA.SetFilename(plants_path);
			}
			else
				VTLOG("\tCouldn't load VF file.\n");
		}
	}
	VTLOG1("  Creating Plant geometry..\n");
	// Create the 3d plants
	int created = m_PIA.CreatePlantNodes(m_progress_callback);
	VTLOG("\tCreated: %d of %d plants\n", created, m_PIA.GetNumEntities());
	if (m_PIA.NumOffTerrain())
		VTLOG("\t%d were off the terrain.\n", m_PIA.NumOffTerrain());

	int i, size = m_PIA.GetNumEntities();
	for (i = 0; i < size; i++)
	{
		vtTransform *pTrans = m_PIA.GetPlantNode(i);

		// add tree to scene graph
		if (pTrans)
			AddNodeToVegGrid(pTrans);
	}
	VTLOG(" Vegetation: %.3f seconds.\n", (float)(clock() - r1) / CLOCKS_PER_SEC);
}

//
// Create an LOD grid to contain and efficiently hide stuff that's far away
//
void vtTerrain::_SetupStructGrid(float fLODDistance)
{
	// must have a terrain with some size
	if (!m_pHeightField)
		return;

	FRECT world_extents;
	world_extents = m_pHeightField->m_WorldExtents;

	FPoint3 org(world_extents.left, 0.0f, world_extents.bottom);
	FPoint3 size(world_extents.right, 0.0f, world_extents.top);

	bool bPaging = m_Params.GetValueBool("PagingStructures");
	if (bPaging)
	{
		m_pPagedStructGrid = new vtPagedStructureLodGrid;
		m_pStructGrid = m_pPagedStructGrid;
	}
	else
		m_pStructGrid = new vtSimpleLodGrid;

	m_pStructGrid->Setup(org, size, LOD_GRIDSIZE, fLODDistance, m_pHeightField);
	m_pStructGrid->SetName2("Structures LOD Grid");
	m_pTerrainGroup->AddChild(m_pStructGrid);
}

void vtTerrain::_CreateStructures()
{
	// create built structures
	vtStructure3d::InitializeMaterialArrays();

	unsigned int i, num = m_Params.m_Layers.size();
	for (i = 0; i < num; i++)
	{
		const vtTagArray &lay = m_Params.m_Layers[i];

		// Look for structure layers
		vtString ltype = lay.GetValueString("Type");
		if (ltype != TERR_LTYPE_STRUCTURE)
			continue;

		VTLOG(" Layer %d: Structure\n", i);
		vtString building_fname = "BuildingData/";
		building_fname += lay.GetValueString("Filename");

		VTLOG("\tLooking for structures file: %s\n", (const char *) building_fname);

		vtString building_path = FindFileOnPaths(vtGetDataPath(), building_fname);
		if (building_path == "")
			VTLOG("\tNot found.\n");
		else
		{
			VTLOG("\tFound: %s\n", (const char *) building_path);
			vtStructureArray3d *sa = LoadStructuresFromXML(building_path);
			if (sa)
			{
				// If the user wants it to start hidden, hide it
				bool bVisible;
				if (lay.GetValueBool("visible", bVisible))
					sa->SetEnabled(bVisible);
			}
		}
	}
	int created = 0;
	for (i = 0; i < m_Layers.GetSize(); i++)
	{
		vtStructureLayer *slay = dynamic_cast<vtStructureLayer*>(m_Layers[i]);
		if (slay)
		{
			CreateStructures(slay);
			created++;
		}
	}
	if (created == 0)
	{
		// No structures loaded, but the user might want to create some later,
		//  so create a default structure set, and set the projection to match
		//  the terrain.
		vtStructureLayer *slay = NewStructureLayer();
		slay->SetFilename("Untitled.vtst");
		slay->m_proj = m_proj;
	}
}

/////////////////////////

void vtTerrain::_CreateAbstractLayers()
{
	// Go through the layers in the terrain parameters, and try to load them
	unsigned int i, num = m_Params.m_Layers.size();
	for (i = 0; i < num; i++)
	{
		const vtTagArray &lay = m_Params.m_Layers[i];

		// Look for abstract layers
		vtString ltype = lay.GetValueString("Type");
		if (ltype != TERR_LTYPE_ABSTRACT)
			continue;

		VTLOG(" Layer %d: Abstract\n", i);
		for (unsigned int j = 0; j < lay.NumTags(); j++)
		{
			const vtTag *tag = lay.GetTag(j);
			VTLOG("   Tag '%s': '%s'\n", (const char *)tag->name, (const char *)tag->value);
		}

		vtString fname = lay.GetValueString("Filename");
		vtString path = FindFileOnPaths(vtGetDataPath(), fname);
		if (path == "")
		{
			vtString prefix = "PointData/";
			path = FindFileOnPaths(vtGetDataPath(), prefix+fname);
		}
		if (path == "")
		{
			VTLOG("Couldn't find features file '%s'\n", (const char *) fname);
			continue;
		}

		vtFeatureLoader loader;
		vtFeatureSet *feat = loader.LoadFrom(path);
		if (!feat)
		{
			VTLOG("Couldn't read features from file '%s'\n", (const char *) path);
			continue;
		}
		VTLOG("Successfully read features from file '%s'\n", (const char *) path);

		// Copy all the other attributes to the new featureset
		VTLOG1("  Setting featureset properties.\n");
		feat->GetProperties() = lay;

		VTLOG1("  Constructing and appending layer.\n");
		vtAbstractLayer *layer = new vtAbstractLayer;
		layer->pSet = feat;
		m_Layers.Append(layer);
	}

	// Now for each layer that we have, create the geometry and labels
	for (i = 0; i < m_Layers.GetSize(); i++)
	{
		vtAbstractLayer *layer = dynamic_cast<vtAbstractLayer*>(m_Layers[i]);
		if (layer)
			layer->CreateStyledFeatures(this);
	}
}

/////////////////////////

void vtTerrain::_CreateImageLayers()
{
	// Must have something to drape on
	if (!GetHeightField())
		return;

	// Go through the layers in the terrain parameters, and try to load them
	unsigned int i, num = m_Params.m_Layers.size();
	for (i = 0; i < num; i++)
	{
		const vtTagArray &lay = m_Params.m_Layers[i];

		// Look for image layers
		vtString ltype = lay.GetValueString("Type");
		if (ltype != TERR_LTYPE_IMAGE)
			continue;

		VTLOG(" Layer %d: Image\n", i);
		for (unsigned int j = 0; j < lay.NumTags(); j++)
		{
			const vtTag *tag = lay.GetTag(j);
			VTLOG("   Tag '%s': '%s'\n", (const char *)tag->name, (const char *)tag->value);
		}

		vtString fname = lay.GetValueString("Filename");
		vtString path = FindFileOnPaths(vtGetDataPath(), fname);
		if (path == "")
		{
			vtString prefix = "GeoSpecific/";
			path = FindFileOnPaths(vtGetDataPath(), prefix+fname);
		}
		if (path == "")
		{
			VTLOG("Couldn't find image layer file '%s'\n", (const char *) fname);
			continue;
		}

		vtImageLayer *ilayer = new vtImageLayer;
		if (!ilayer->m_pImage->Read(path, true, m_progress_callback))
		{
			VTLOG("Couldn't read image from file '%s'\n", (const char *) path);
			continue;
		}
		VTLOG("Read image from file '%s'\n", (const char *) path);

		DRECT extents = ilayer->m_pImage->GetExtents();
		if (extents.IsEmpty())
		{
			VTLOG("Couldn't get extents from image, so we can't use it as an image overlay.\n");
			continue;
		}

		// Copy all the other attributes to the new layer (TODO?)
		//feat->GetProperties() = lay;

		m_Layers.Append(ilayer);

		ilayer->m_pMultiTexture = AddMultiTextureOverlay(ilayer->m_pImage,
			ilayer->m_pImage->GetExtents(), GL_DECAL);
	}
}

//
// \param TextureMode One of GL_DECAL, GL_MODULATE, GL_BLEND, GL_REPLACE, GL_ADD
//
vtMultiTexture *vtTerrain::AddMultiTextureOverlay(vtImage *pImage, const DRECT &extents,
									   int TextureMode)
{
	DRECT TerrainExtents = GetHeightField()->GetEarthExtents();

	int iTextureUnit = m_TextureUnits.ReserveTextureUnit();
	if (iTextureUnit == -1)
		return NULL;

		// Calculate the mapping of texture coordinates
	DPoint2 scale;
	FPoint2 offset;
	vtHeightFieldGrid3d *grid = GetDynTerrain();

	if (grid)
	{
		int iCols, iRows;
		grid->GetDimensions(iCols, iRows);

		// input values go from (0,0) to (Cols-1,Rows-1)
		// output values go from 0 to 1
		scale.Set(1.0/(iCols - 1), 1.0/(iRows - 1));

		// stretch the (0-1) over the data extents
		scale.x *= (TerrainExtents.Width() / extents.Width());
		scale.y *= (TerrainExtents.Height() / extents.Height());
	}
	else	// might be a TiledGeom, or a TIN
	{
		// Map input values (0-terrain size in world coords) to 0-1
		scale.Set(1.0/extents.Width(), -1.0/extents.Height());
	}

	// and offset it to place it at the right place
	offset.x = (extents.left - TerrainExtents.left) / extents.Width();
	offset.y = (extents.bottom - TerrainExtents.bottom) / extents.Height();

	// apply it to the node that is above the terrain surface
	return GetTerrainSurfaceNode()->AddMultiTexture(iTextureUnit, pImage,
		TextureMode, scale, offset);
}

vtNode *vtTerrain::GetTerrainSurfaceNode()
{
	if (GetDynTerrain())
		return GetDynTerrain();
	else if (GetTiledGeom())
		return GetTiledGeom();
	else if (GetTin())
		return GetTin()->GetGeometry();
	return NULL;
}

void vtTerrain::SetFog(bool fog)
{
	m_bFog = fog;
	if (m_bFog)
	{
		float dist = (float) m_Params.GetValueInt(STR_FOGDISTANCE) * 1000;

		if (m_fog_color.r != -1)
			m_pTerrainGroup->SetFog(true, 0, dist, m_fog_color);
		else
			m_pTerrainGroup->SetFog(true, 0, dist);
	}
	else
		m_pTerrainGroup->SetFog(false);
}

void vtTerrain::SetFogColor(const RGBf &color)
{
	m_fog_color = color;
	if (m_bFog)
		SetFog(true);
}

void vtTerrain::SetFogDistance(float fMeters)
{
	m_Params.SetValueInt(STR_FOGDISTANCE, (int) (fMeters / 1000));
	if (m_bFog)
		SetFog(true);
}

void vtTerrain::SetBgColor(const RGBf &color)
{
	m_background_color = color;
}


///////////////////////////////////////////////////////////////////////
//////////////////////////// Time Methods /////////////////////////////

/**
 * Get the time at which a terrain is set to begin.
 */
vtTime vtTerrain::GetInitialTime()
{
	const char *str = m_Params.GetValueString(STR_INITTIME);

	VTLOG("Initial time: %s\n", str);

	vtTime localtime;
	localtime.SetFromString(str);
	return localtime;
}

/**
 * Given a time value, convert it from the LT (local time) of the center of
 * this terrain to GMT.  Local time is defined precisely by longitude,
 * e.g. at noon local time, the sun is exactly halfway across the sky.
 *
 * Note that this is different that the "standard time" of a given place,
 * which involves finding out what time zone is in effect (complicated!)
 */
void vtTerrain::TranslateToGMT(vtTime &time)
{
	if (m_CenterGeoLocation.x == -999)
		_ComputeCenterLocation();

	time.Increment(-m_iDifferenceFromGMT);
}

/**
 * Given a time value, convert it to the LT (local time) of the center of
 * this terrain from GMT.  Local time is defined precisely by longitude,
 * e.g. at noon local time, the sun is exactly halfway across the sky.
 *
 * Note that this is different that the "standard time" of a given place,
 * which involves finding out what time zone is in effect (complicated!)
 */
void vtTerrain::TranslateFromGMT(vtTime &time)
{
	if (m_CenterGeoLocation.x == -999)
		_ComputeCenterLocation();

	time.Increment(m_iDifferenceFromGMT);
}

DPoint2 vtTerrain::GetCenterGeoLocation()
{
	if (m_CenterGeoLocation.x == -999)
		_ComputeCenterLocation();

	return m_CenterGeoLocation;
}

void vtTerrain::_ComputeCenterLocation()
{
	vtHeightField3d *pHF = GetHeightField();
	DRECT drect = pHF->GetEarthExtents();
	drect.GetCenter(m_CenterGeoLocation);

	// must convert from whatever we CRS are, to Geographic
	vtProjection Dest;
	Dest.SetWellKnownGeogCS("WGS84");

	// We won't fail on tricky Datum conversions, but we still might
	//  conceivably fail if the GDAL/PROJ files aren't found.
	OCT *trans = CreateConversionIgnoringDatum(&m_proj, &Dest);
	if (trans)
	{
		trans->Transform(1, &m_CenterGeoLocation.x, &m_CenterGeoLocation.y);
		delete trans;
	}

	// calculate offset FROM GMT
	// longitude of 180 deg = 12 hours = 720 min = 43200 sec
	m_iDifferenceFromGMT = (int) (m_CenterGeoLocation.x / 180 * 43200);
}


void vtTerrain::CreateStep0()
{
	// Only do this method once
	if (m_pTerrainGroup)
		return;

	// create terrain group - this holds all surfaces for the terrain
	m_pTerrainGroup = new vtGroup;
	m_pTerrainGroup->SetName2("Terrain Group");
#ifdef VTLIB_PSM
	m_pTerrainGroup->IncUse();
#endif

	// create engine group, the parent of all engines for this terrain
	m_pEngineGroup = new vtEngine;
	vtString name = "Engines for ";
	name += GetName();
	m_pEngineGroup->SetName2(name);
	vtGetScene()->AddEngine(m_pEngineGroup);
	m_AnimContainer.SetEngineContainer(m_pEngineGroup);
}

/**
 * First step in terrain creation: load elevation.
 * You can use these methods to build a terrain step by step, or simply
 * use the method vtTerrainScene::BuildTerrain, which calls them all.
 */
bool vtTerrain::CreateStep1()
{
	VTLOG("Step1\n");

	// for GetValueFloat below
	LocaleWrap normal_numbers(LC_NUMERIC, "C");

	m_fVerticalExag = m_Params.GetValueFloat(STR_VERTICALEXAG);

	// User may have have supplied a grid directly, via SetLocalGrid
	if (m_pInputGrid)
	{
		m_pElevGrid = m_pInputGrid;
		m_pElevGrid->SetupConversion(m_Params.GetValueFloat(STR_VERTICALEXAG));
		m_pHeightField = m_pElevGrid;
		m_proj = m_pElevGrid->GetProjection();
		// set global projection based on this terrain
		g_Conv = m_pElevGrid->m_Conversion;
		m_bIsCreated = true;
		return true;
	}
	// User may have supplied a TIN directly, via SetTin
	if (m_pTin)
	{
		m_pHeightField = m_pTin;
		m_proj = m_pTin->m_proj;
		// set global projection based on this terrain
		g_Conv = m_pTin->m_Conversion;
		m_bIsCreated = true;
		return true;
	}

	vtString fname;
	vtString elev_file = m_Params.GetValueString(STR_ELEVFILE);
	fname = "Elevation/";
	fname += elev_file;
	VTLOG("\tLooking for elevation file: %s\n", (const char *) fname);

	vtString elev_path = FindFileOnPaths(vtGetDataPath(), fname);
	if (elev_path == "")
	{
		VTLOG("\t\tNot found.\n");

		vtString msg;
		msg.Format("Couldn't find elevation '%s'", (const char *) elev_file);
		_SetErrorMessage(msg);
		return false;
	}

	VTLOG("\tFound elevation at: %s\n", (const char *) elev_path);
	int surface_type = m_Params.GetValueInt(STR_SURFACE_TYPE);
	if (surface_type == 0)
	{
		// Elevation input is a single grid; load it
		m_pElevGrid = new vtElevationGrid;

		vtElevGridError err;
		bool status = m_pElevGrid->LoadFromBT(elev_path, m_progress_callback, &err);
		if (status == false)
		{
			if (err == EGE_READ_CRS)
				_SetErrorMessage("Grid load failed: couldn't read projection");
			else if (err == EGE_UNSUPPORTED_VERSION)
				_SetErrorMessage("Grid load failed: unsupported version");
			else if (err == EGE_FILE_OPEN)
				_SetErrorMessage("Grid load failed: couldn't open");
			return false;
		}
		VTLOG("\tGrid load succeeded.\n");

		// set global projection based on this terrain
		m_proj = m_pElevGrid->GetProjection();

		int col, row;
		m_pElevGrid->GetDimensions(col, row);
		VTLOG("\t\tSize: %d x %d.\n", col, row);
		DRECT rect = m_pElevGrid->GetEarthExtents();
		VTLOG("\t\tEarth Extents LRTB: %lg %lg %lg %lg\n",
			rect.left, rect.right, rect.top, rect.bottom);

		float exag = m_Params.GetValueFloat(STR_VERTICALEXAG);
		VTLOG("\t\tVertical exaggeration: %g\n", exag);
		m_pElevGrid->SetupConversion(exag);

		g_Conv = m_pElevGrid->m_Conversion;

		FRECT frect = m_pElevGrid->m_WorldExtents;
		VTLOG("\t\tWorld Extents LRTB: %g %g %g %g\n",
			frect.left, frect.right, frect.top, frect.bottom);

		m_pHeightField = m_pElevGrid;

		// Apply ocean depth
		if (m_Params.GetValueBool(STR_DEPRESSOCEAN))
		{
			float fOceanDepth = m_Params.GetValueFloat(STR_DEPRESSOCEANLEVEL);
			m_pElevGrid->ReplaceValue(0, fOceanDepth);
		}
	}
	else if (surface_type == 1)
	{
		// Elevation input is a single TIN
		if (!m_pTin)
		{
			// if they did not provide us with a TIN, try to load it
			m_pTin = new vtTin3d;
			bool status = m_pTin->Read(elev_path);

			if (status == false)
			{
				_SetErrorMessage("TIN load failed.");
				return false;
			}
			VTLOG("\tTIN load succeeded.\n");

			m_proj = m_pTin->m_proj;
			g_Conv = m_pTin->m_Conversion;

			m_pHeightField = m_pTin;
		}
	}
	else if (surface_type == 2)
	{
		vtString tex_file = m_Params.GetValueString(STR_TEXTUREFILE);
		fname = "GeoSpecific/";
		fname += tex_file;
		VTLOG("\tLooking for texture file: %s\n", (const char *) fname);

		vtString tex_path = FindFileOnPaths(vtGetDataPath(), fname);
		if (tex_path == "")
		{
			VTLOG("\t\tNot found.\n");

			vtString msg;
			msg.Format("Couldn't find texture '%s'", (const char *) tex_path);
			_SetErrorMessage(msg);
			return false;
		}
		VTLOG("\tFound texture at: %s\n", (const char *) tex_path);

		// Elevation input is a set of tiles, which will be loaded later as needed
		m_pTiledGeom = new vtTiledGeom;
		m_pTiledGeom->SetName2("Tiled Geometry Container");
		m_pTiledGeom->SetVerticalExag(m_fVerticalExag);
		m_pTiledGeom->SetVertexTarget(m_Params.GetValueInt(STR_VERTCOUNT));

		// tile cache size is in MB for the user, but bytes for the class
		int tile_cache_mb = m_Params.GetValueInt(STR_TILE_CACHE_SIZE);
		//m_pTiledGeom->SetTileCacheSize(tile_cache_mb * 1024 * 1024);

		bool bThread = m_Params.GetValueBool(STR_TILE_THREADING);
		bool bGradual = m_Params.GetValueBool(STR_TEXTURE_GRADUAL);
		bool status = m_pTiledGeom->ReadTileList(elev_path, tex_path,
			bThread, bGradual);

		if (status == false)
		{
			_SetErrorMessage("Tile list load failed.");
			return false;
		}
		m_pHeightField = m_pTiledGeom;
		g_Conv = m_pHeightField->m_Conversion;
		m_proj = m_pTiledGeom->m_proj;

		// The tiled geometry base texture will always use texture unit 0
		m_TextureUnits.ReserveTextureUnit();
	}
	char type[10], value[2048];
	m_proj.GetTextDescription(type, value);
	VTLOG(" Projection of the terrain: %s, '%s'\n", type, value);
	DRECT ext = m_pHeightField->GetEarthExtents();
	VTLOG(" Earth extents LRTB: %lf %lf %lf %lf\n", ext.left, ext.right, ext.top, ext.bottom);

	m_bIsCreated = true;
	return true;
}

/**
 * Next step in terrain creation: create textures.
 */
bool vtTerrain::CreateStep2(vtTransform *pSunLight)
{
	VTLOG("Step2\n");

	// if we aren't going to produce the terrain surface, nothing to do
	if (m_Params.GetValueBool(STR_SUPPRESS))
		return true;

	int type = m_Params.GetValueInt(STR_SURFACE_TYPE);
	int tex = m_Params.GetValueInt(STR_TEXTURE);
	if (type == 0 ||	// single grid
		(type == 1 && tex == 1))	// TIN, single texture
		_CreateTextures(pSunLight->GetDirection(), m_progress_callback);
	return true;
}

/**
 * Next step in terrain creation: create 3D geometry for the terrain.
 */
bool vtTerrain::CreateStep3()
{
	VTLOG("Step3\n");

	// if we aren't going to produce the terrain surface, nothing to do
	if (m_Params.GetValueBool(STR_SUPPRESS))
		return true;

	if (m_Params.GetValueInt(STR_SURFACE_TYPE) == 0)	// single grid
		return CreateFromGrid();
	else if (m_Params.GetValueInt(STR_SURFACE_TYPE) == 1)	// TIN
		return CreateFromTIN();
	else if (m_Params.GetValueInt(STR_SURFACE_TYPE) == 2)	// tiles
		return CreateFromTiles();
	return true;
}

bool vtTerrain::CreateFromTIN()
{
	bool bDropShadow = true;

	// build heirarchy (add terrain to scene graph)
	int tex = m_Params.GetValueInt(STR_TEXTURE);
	if (tex == 1)
		m_pTin->SetTextureMaterials(m_pTerrMats);
	vtGeom *geom = m_pTin->CreateGeometry(bDropShadow);
	m_pTerrainGroup->AddChild(geom);

	return true;
}

// for timing how long the CLOD takes to initialize
clock_t tm1;

bool vtTerrain::CreateFromGrid()
{
	VTLOG(" CreateFromGrid\n");
	tm1 = clock();

	// create elegant dynamic LOD terrain
	if (!_CreateDynamicTerrain())
	{
		return false;
	}
	else
	{
		m_pDynGeom->SetEnabled(true);
		m_pHeightField = m_pDynGeom;
	}

	if (!m_bPreserveInputGrid && !m_Params.GetValueBool(STR_ALLOW_GRID_SCULPTING))
	{
		// we don't need the original grid any more
		delete m_pElevGrid;
		m_pElevGrid = NULL;
	}
	return true;
}

bool vtTerrain::CreateFromTiles()
{
	// m_pTiledGeom already exists (although probably should be unbundled)
	m_pTerrainGroup->AddChild(m_pTiledGeom);

	// the tileset will be the heightfield used at runtime, so extend
	//  it with the terrain's culture
	m_pTiledGeom->SetCulture(this);

	return true;
}

/**
 * Next step in terrain creation: additional CLOD construction.
 */
bool vtTerrain::CreateStep4()
{
	VTLOG("Step4\n");

	// some algorithms need an additional stage of initialization
	if (m_pDynGeom != NULL)
	{
		m_pDynGeom->Init2();

		clock_t tm2 = clock();
		float time = ((float)tm2 - tm1)/CLOCKS_PER_SEC;
		VTLOG("CLOD construction: %.3f seconds.\n", time);
	}

	if (m_Params.GetValueBool(STR_DETAILTEXTURE))
		_CreateDetailTexture();

	return true;
}

/**
 * Next step in terrain creation: create the culture and labels.
 */
bool vtTerrain::CreateStep5()
{
	VTLOG("Step5\n");

	// must have a heightfield by this point
	if (!m_pHeightField)
		return false;

	// Node to put all the scale features under
	m_pScaledFeatures = new vtTransform;
	m_pScaledFeatures->SetName2("Scaled Features");
	m_pScaledFeatures->Scale3(1.0f, m_fVerticalExag, 1.0f);
	m_pTerrainGroup->AddChild(m_pScaledFeatures);

	_CreateCulture();

	bool bWater = m_Params.GetValueBool(STR_OCEANPLANE);
	bool bHorizon = m_Params.GetValueBool(STR_HORIZON);

	float minh, maxh;
	m_pHeightField->GetHeightExtents(minh, maxh);
	if (minh == INVALID_ELEVATION)
		minh = 0.0f;

	if (bWater || bHorizon)
	{
		bool bCenter = bWater;
		CreateArtificialHorizon(minh, bWater, bHorizon, bCenter, 0.5f);
	}

	_CreateAbstractLayers();

	_CreateImageLayers();

	// Engines will be activated later in vtTerrainScene::SetTerrain
	ActivateEngines(false);

	// Read stored locations
	vtString loc = "Locations/";
	loc += m_Params.GetValueString(STR_LOCFILE);
	vtString path = FindFileOnPaths(vtGetDataPath(), loc);
	if (path != "")
	{
		VTLOG("Reading locations file: %s.\n", (const char *) path);
		m_LocSaver.Read(path);
	}
	VTLOG1("Setup location saver coordinate conversion.\n");
	m_LocSaver.SetConversion(m_pHeightField->m_Conversion);
	m_LocSaver.SetProjection(m_proj);

	// Read stored animpaths
	for (unsigned int i = 0; i < m_Params.m_AnimPaths.size(); i++)
	{
		vtString fname1 = m_Params.m_AnimPaths[i];
		vtString fname2 = "Locations/" + fname1;
		vtString path = FindFileOnPaths(vtGetDataPath(), fname2);
		if (path == "")
			continue;

		VTLOG("Reading animpath: %s.\n", (const char *) path);
		vtAnimPath *anim = new vtAnimPath;
		// Ensure that anim knows the projection
		if (!anim->SetProjection(GetProjection()))
		{
			// no projection, no functionality
			delete anim;
			continue;
		}
		if (!anim->Read(path))
		{
			delete anim;
			continue;
		}
		vtAnimPathEngine *engine = new vtAnimPathEngine(anim);
		engine->SetName2("AnimPathEngine");
		engine->SetTarget(vtGetScene()->GetCamera());
		engine->SetEnabled(false);
		AddEngine(engine);

		vtAnimEntry *entry = new vtAnimEntry;
		entry->m_pAnim = anim;
		entry->m_pEngine = engine;
		entry->m_Name = fname1;

		m_AnimContainer.Append(entry);
	}

	return true;
}

void vtTerrain::SetProgressCallback(ProgFuncPtrType progress_callback)
{
	m_progress_callback = progress_callback;
}

bool vtTerrain::ProgressCallback(int i)
{
	if (m_progress_callback != NULL)
		return m_progress_callback(i);
	else
		return false;
}

bool vtTerrain::IsCreated()
{
	return m_bIsCreated;
}

void vtTerrain::Enable(bool bVisible)
{
	m_pTerrainGroup->SetEnabled(bVisible);
}

/**
 * Return the center of the bounding sphere that encloses the terrain's
 * dynamic geometry.
 */
FPoint3 vtTerrain::GetCenter()
{
	GetTerrainBounds();
	return m_bound_sphere.center;
}

/**
 * Return the radius of the bounding sphere that encloses the terrain's
 * dynamic geometry.
 */
float vtTerrain::GetRadius()
{
	GetTerrainBounds();
	return m_bound_sphere.radius;
}

void vtTerrain::GetTerrainBounds()
{
	if (m_pDynGeomScale != NULL)
		m_pDynGeomScale->GetBoundSphere(m_bound_sphere);
	else
		m_bound_sphere.Empty();
}

/**
 * Tests whether a given point (in Earth coordinates) is within the current
 * extents of the terrain.
 */
bool vtTerrain::PointIsInTerrain(const DPoint2 &p)
{
	float x, z;
	m_pHeightField->m_Conversion.ConvertFromEarth(p, x,  z);	// convert earth -> XZ
	return m_pHeightField->ContainsWorldPoint(x, z);
}

/**
 * The base CreateCustomCulture does nothing; this virtual method is meant to
 * be overridden by your terrain subclass to add its own culture.
 */
void vtTerrain::CreateCustomCulture()
{
}

/**
 * Add an engine to this terrain's group of engines.
 * The engine will be enabled only when the terrain is visible.
 */
void vtTerrain::AddEngine(vtEngine *pE)
{
	// add to this Terrain's engine list
	m_pEngineGroup->AddChild(pE);
}

void vtTerrain::ActivateEngines(bool bActive)
{
	m_pEngineGroup->SetEnabled(bActive);
}

//////////////////////////

void vtTerrain::SetFeatureVisible(TFType ftype, bool bOn)
{
	switch (ftype)
	{
	case TFT_TERRAINSURFACE:
		if (m_pDynGeom)
			m_pDynGeom->SetEnabled(bOn);
		else if (m_pTiledGeom)
			m_pTiledGeom->SetEnabled(bOn);
		break;
	case TFT_HORIZON:
		if (m_pHorizonGeom)
			m_pHorizonGeom->SetEnabled(bOn);
		break;
	case TFT_OCEAN:
		if (m_pOceanGeom)
			m_pOceanGeom->SetEnabled(bOn);
		break;
	case TFT_VEGETATION:
		if (m_pVegGrid)
			m_pVegGrid->SetEnabled(bOn);
		break;
	case TFT_STRUCTURES:
		if (m_pStructGrid)
			m_pStructGrid->SetEnabled(bOn);
		break;
	case TFT_ROADS:
		if (m_pRoadGroup)
			m_pRoadGroup->SetEnabled(bOn);
		break;
	}
}

bool vtTerrain::GetFeatureVisible(TFType ftype)
{
	switch (ftype)
	{
	case TFT_TERRAINSURFACE:
		if (m_pDynGeom)
			return m_pDynGeom->GetEnabled();
		else if (m_pTiledGeom)
			return m_pTiledGeom->GetEnabled();
		break;
	case TFT_HORIZON:
		if (m_pHorizonGeom)
			return m_pHorizonGeom->GetEnabled();
		break;
	case TFT_OCEAN:
		if (m_pOceanGeom)
			return m_pOceanGeom->GetEnabled();
		break;
	case TFT_VEGETATION:
		if (m_pVegGrid)
			return m_pVegGrid->GetEnabled();
		break;
	case TFT_STRUCTURES:
		if (m_pStructGrid)
			return m_pStructGrid->GetEnabled();
		break;
	case TFT_ROADS:
		if (m_pRoadGroup)
			return m_pRoadGroup->GetEnabled();
		break;
	}
	return false;
}

void vtTerrain::SetLODDistance(TFType ftype, float fDistance)
{
	switch (ftype)
	{
	case TFT_TERRAINSURFACE:
	case TFT_OCEAN:
		break;
	case TFT_VEGETATION:
		if (m_pVegGrid)
			m_pVegGrid->SetDistance(fDistance);
		break;
	case TFT_STRUCTURES:
		if (m_pStructGrid)
		{
			if (fDistance != m_pStructGrid->GetDistance())
				VTLOG("Structure LOD dist = %.1f\n", fDistance);
			m_pStructGrid->SetDistance(fDistance);
			EnforcePageOut();
		}
		break;
	case TFT_ROADS:
		if (m_pRoadMap)
			m_pRoadMap->SetLodDistance(fDistance);
		break;
	}
}

float vtTerrain::GetLODDistance(TFType ftype)
{
	switch (ftype)
	{
	case TFT_TERRAINSURFACE:
	case TFT_OCEAN:
		break;
	case TFT_VEGETATION:
		if (m_pVegGrid)
			return m_pVegGrid->GetDistance();
		break;
	case TFT_STRUCTURES:
		if (m_pStructGrid)
			return m_pStructGrid->GetDistance();
		break;
	case TFT_ROADS:
		if (m_pRoadMap)
			return m_pRoadMap->GetLodDistance();
		break;
	}
	return 0.0f;
}

/**
 * Return the heightfield for this terrain.  It may be a grid, or a TIN.
 * If you know that your data is a grid, you can use GetHeightFieldGrid3d()
 * to get that specifically.
 */
vtHeightField3d *vtTerrain::GetHeightField()
{
	return m_pHeightField;
}

/**
 * Return the heightfield grid for this terrain.
 * During the construction of the terain, this may be a source vtElevationGrid.
 * Later, at runtime, it is likely to be one of the dynamic geometry (CLOD)
 * grids.
 */
vtHeightFieldGrid3d *vtTerrain::GetHeightFieldGrid3d()
{
	// if we still have the source elevation, use it
	if (m_pElevGrid)
		return m_pElevGrid;

	// otherwise, later on, we might only have the runtime (CLOD) grid
	else if (m_pDynGeom)
		return m_pDynGeom;

	return NULL;	// no grid to return, possible because it's a TIN
}

bool vtTerrain::FindAltitudeOnCulture(const FPoint3 &p3, float &fAltitude,
									  bool bTrue, int iCultureFlags) const
{
	// beware - OSG can be picking about the length of this segment.  It
	//  is a numerical precision issue.  If we use 1E9,-1E9 then it fails
	//  to find some objects.  Instead, search just in the range of elevation
	//  for this terrain, plus a margin to include potential culture.
	float minh, maxh;
	m_pHeightField->GetHeightExtents(minh, maxh);
	FPoint3 start(p3.x, maxh + 1000, p3.z);
	FPoint3 end(p3.x, minh - 1000, p3.z);

	vtHitList hlist;

	if (iCultureFlags & CE_STRUCTURES)
		vtIntersect(m_pStructGrid, start, end, hlist);

	if ((iCultureFlags & CE_ROADS) && m_pRoadGroup)
		vtIntersect(m_pRoadGroup, start, end, hlist);

	if (hlist.size() > 0)
	{
		// take first match encountered
		vtString name = hlist[0].node->GetName2();
		fAltitude =  hlist[0].point.y;

		if (bTrue)
		{
			const vtDynTerrainGeom *dg = GetDynTerrain();
			if (dg)
				fAltitude /= dg->GetVerticalExag();
		}
		return true;
	}
	return false;
}

int vtTerrain::GetShadowTextureUnit()
{
	if (m_iShadowTextureUnit == -1)
		m_iShadowTextureUnit = m_TextureUnits.ReserveTextureUnit();
	return m_iShadowTextureUnit;
}

/*
 * Creates an array of materials for the dynamic LOD terrain geometry.
 */
void vtTerrain::_CreateSingleMaterial(float ambient, float diffuse, float emmisive)
{
	bool bTransp = (m_pImage->GetDepth() == 32);
	m_pTerrMats->AddTextureMaterial(m_pImage,
		!m_bBothSides,		// culling
		false,		// lighting
		bTransp,	// transparency blending
		false,		// additive
		ambient, diffuse,
		1.0f,		// alpha
		emmisive,
		true,		// texgen
		false,		// clamp
		m_Params.GetValueBool(STR_MIPMAP));
}

void vtTerrain::_CreateTiledMaterials(int patches, float ambient,
									  float diffuse, float emmisive)
{
	for (int i = 0; i < patches; i++)
	{
		for (int j = 0; j < patches; j++)
		{
			vtImage *image = m_ImageTiles.m_Tiles[i][j];
			m_pTerrMats->AddTextureMaterial(image,
				!m_bBothSides, 	// culling
				false,		// lighting
				false,		// transparency
				false,		// additive
				ambient, diffuse,
				1.0f,		// alpha
				emmisive,
				true,		// texgen
				false,		// clamp
				m_Params.GetValueBool(STR_MIPMAP));
		}
	}
}


void vtTerrain::_ApplyPreLight(vtHeightFieldGrid3d *pElevGrid, vtBitmapBase *bitmap,
							  const FPoint3 &light_dir, bool progress_callback(int))
{
	// for GetValueFloat below
	LocaleWrap normal_numbers(LC_NUMERIC, "C");

	VTLOG("  Prelighting texture: ");

	clock_t c1 = clock();

	float shade_factor = m_Params.GetValueFloat(STR_PRELIGHTFACTOR);
	bool bTrue = m_Params.GetValueBool("ShadeTrue");
	bool bQuick = m_Params.GetValueBool("ShadeQuick");
	float ambient = 0.25f;
	float gamma = 0.80f;
	if (m_Params.GetValueBool(STR_CAST_SHADOWS))
	{
		// A more accurate shading, still a little experimental
		pElevGrid->ShadowCastDib(bitmap, light_dir, shade_factor, ambient, progress_callback);
	}
	else if (bQuick)
		pElevGrid->ShadeQuick(bitmap, shade_factor, bTrue, progress_callback);
	else
		pElevGrid->ShadeDibFromElevation(bitmap, light_dir, shade_factor,
			ambient, gamma, bTrue, progress_callback);

	clock_t c2 = clock();

	clock_t c3 = c2 - c1;
	VTLOG("%.3f seconds.\n", (float)c3 / CLOCKS_PER_SEC);
}

/**
 * Create geometry on the terrain for a 2D line by draping the point onto
 * the terrain surface.
 *
 * \param pMF	A vtMeshFactory which will produces the mesh geometry.
 * \param line	The 2D line to drape, in Earth coordinates.
 * \param fOffset	An offset to elevate each point in the resulting geometry,
 *		useful for keeping it visibly above the ground.
 * \param bInterp	True to interpolate between the vertices of the input
 *		line. This is generally desirable when the ground is much more finely
 *		spaced than the input line.
 * \param bCurve	True to interpret the vertices of the input line as
 *		control points of a curve.  The created geometry will consist of
 *		a draped line which passes through the control points.
 * \param bTrue		True to use the true elevation of the terrain, ignoring
 *		whatever scale factor is being used to exaggerate elevation for
 *		display.
 * \return The approximate length of the resulting 3D line mesh.
 *
 * \par Example:
	\code
	DLine2 line = ...;
	vtTerrain *pTerr = ...;
	vtGeom *pLineGeom = new vtGeom;
	pTerr->AddNode(pLineGeom);
	vtMeshFactory mf(pLineGeom, vtMesh::LINE_STRIP, 0, 30000, 1);
	float length = pTerr->AddSurfaceLineToMesh(&mf, dline, 10, true);
	\endcode
 */
float vtTerrain::AddSurfaceLineToMesh(vtMeshFactory *pMF, const DLine2 &line,
									 float fOffset, bool bInterp, bool bCurve,
									 bool bTrue)
{
	unsigned int i, j;
	FPoint3 v1, v2, v;

	float fSpacing=0;
	if (bInterp)
	{
		// try to guess how finely to tessellate our line
		if (m_pDynGeom)
		{
			FPoint2 spacing = m_pDynGeom->GetWorldSpacing();
			fSpacing = std::min(spacing.x, spacing.y) / 2;
		}
		else if (m_pTin)
		{
			// TINs don't have a grid spacing.  In lieu of using a completely
			//  different (more correct) algorithm for draping, just estimate.
			DRECT ext = m_pTin->GetEarthExtents();
			FPoint2 p1, p2;
			m_pHeightField->m_Conversion.convert_earth_to_local_xz(ext.left, ext.bottom, p1.x, p1.y);
			m_pHeightField->m_Conversion.convert_earth_to_local_xz(ext.right, ext.top, p2.x, p2.y);
			fSpacing = (p2 - p1).Length() / 1000.0f;
		}
		else if (m_pTiledGeom)
		{
			// There is no ideal way to drape a line on a tileset of tiles
			//  with varying resolution.  For now, just use the highest (LOD0)
			//  grid density at the starting point.
			FPoint2 spacing = m_pTiledGeom->GetWorldSpacingAtPoint(line[0]);
			fSpacing = std::min(spacing.x, spacing.y);
		}
	}

	float fTotalLength = 0.0f;
	pMF->PrimStart();
	int iVerts = 0;
	unsigned int points = line.GetSize();
	if (bCurve)
	{
		DPoint2 p2, last(1E9,1E9);
		DPoint3 p3;

		int spline_points = 0;
		CubicSpline spline;
		for (i = 0; i < points; i++)
		{
			p2 = line[i];
			if (i > 1 && p2 == last)
				continue;
			p3.Set(p2.x, p2.y, 0);
			spline.AddPoint(p3);
			spline_points++;
			last = p2;
		}
		spline.Generate();

		// estimate how many steps to subdivide this line into
		double dLinearLength = line.Length();
		float fLinearLength, dummy;
		m_pHeightField->m_Conversion.ConvertVectorFromEarth(DPoint2(dLinearLength,0.0), fLinearLength, dummy);
		double full = (double) (spline_points-1);
		int iSteps = (unsigned int) (fLinearLength / fSpacing);
		if (iSteps < 3)
			iSteps = 3;
		double dStep = full / iSteps;

		FPoint3 last_v;
		double f;
		for (f = 0; f <= full; f += dStep)
		{
			spline.Interpolate(f, &p3);

			m_pHeightField->m_Conversion.convert_earth_to_local_xz(p3.x, p3.y, v.x, v.z);
			m_pHeightField->FindAltitudeAtPoint(v, v.y, bTrue);
			v.y += fOffset;
			pMF->AddVertex(v);
			iVerts++;

			// keep a running total of approximate ground length
			if (f > 0)
				fTotalLength += (v - last_v).Length();
			last_v = v;
		}
	}
	else
	{
		// not curved: straight line in earth coordinates
		FPoint3 last_v;
		for (i = 0; i < points; i++)
		{
			if (bInterp)
			{
				v1 = v2;
				m_pHeightField->m_Conversion.convert_earth_to_local_xz(line[i].x, line[i].y, v2.x, v2.z);
				if (i == 0)
					continue;

				// estimate how many steps to subdivide this segment into
				FPoint3 diff = v2 - v1;
				float fLen = diff.Length();
				unsigned int iSteps = (unsigned int) (fLen / fSpacing);
				if (iSteps < 1) iSteps = 1;

				for (j = (i == 1 ? 0:1); j <= iSteps; j++)
				{
					// simple linear interpolation of the ground coordinate
					v.Set(v1.x + diff.x / iSteps * j, 0.0f, v1.z + diff.z / iSteps * j);
					m_pHeightField->FindAltitudeAtPoint(v, v.y, bTrue);
					v.y += fOffset;
					pMF->AddVertex(v);
					iVerts++;

					// keep a running total of approximate ground length
					if (j > 0)
						fTotalLength += (v - last_v).Length();
					last_v = v;
				}
			}
			else
			{
				m_pHeightField->m_Conversion.ConvertFromEarth(line[i], v.x, v.z);
				m_pHeightField->FindAltitudeAtPoint(v, v.y, bTrue);
				v.y += fOffset;
				pMF->AddVertex(v);
			}
		}
	}
	pMF->PrimEnd();
	return fTotalLength;
}


///////////////////////////////////////////////////////////////////////
// Layers

void vtTerrain::RemoveLayer(vtLayer *lay, bool progress_callback(int))
{
	vtStructureLayer *slay = dynamic_cast<vtStructureLayer*>(lay);
	vtAbstractLayer *alay = dynamic_cast<vtAbstractLayer*>(lay);
	if (slay)
	{
		// first remove each structure from the terrain
		for (unsigned int i = 0; i < slay->GetSize(); i++)
		{
			if (progress_callback != NULL)
				progress_callback(i * 99 / slay->GetSize());

			// Remove it from the paging grid
			if (m_pPagedStructGrid)
				m_pPagedStructGrid->RemoveFromGrid(slay, i);

			vtStructure3d *str3d = slay->GetStructure3d(i);
			RemoveNodeFromStructGrid(str3d->GetContainer());
			str3d->DeleteNode();
		}

		// Be certain we're not still trying to page it in
		if (m_pPagedStructGrid)
			m_pPagedStructGrid->ClearQueue(slay);

		delete slay;

		// If that was the current layer, deal with it
		if (slay == m_pActiveStructLayer)
			m_pActiveStructLayer = NULL;
	}
	else if (alay)
	{
		// first remove them from the terrain
		RemoveFeatureGeometry(alay);
		delete alay;

		// If that was the current layer, deal with it
		if (alay == m_pActiveAbstractLayer)
			m_pActiveAbstractLayer = NULL;
	}
	m_Layers.Remove(lay);
}

/**
 * Currently handled by this method: structure and abstract layers.
 */
vtLayer *vtTerrain::LoadLayer(const char *fname)
{
	VTLOG1("vtTerrain::LoadLayer\n");

	vtString ext = GetExtension(fname);
	if (!ext.CompareNoCase(".vtst"))
	{
		return LoadStructuresFromXML(fname);
	}
	else if (!ext.CompareNoCase(".shp"))
	{
		vtFeatureLoader loader;
		vtFeatureSet *feat = loader.LoadFrom(fname);
		if (!feat)
		{
			VTLOG("Couldn't read features from file '%s'\n", fname);
			return NULL;
		}
		VTLOG("Successfully read features from file '%s'\n", fname);
		vtAbstractLayer *alay = new vtAbstractLayer;
		alay->pSet = feat;
		m_Layers.Append(alay);
		return alay;
	}
	return NULL;
}


///////////////////////////////////////////////////////////////////////
// Plants

/**
 * Create a new plant instance at a given location and add it to the terrain.
 * \param pos The 2D earth position of the new plant.
 * \param iSpecies Index of the species in the terrain's plant list.
 *		If you don't know the index, you can find it with
 *		 vtSpeciesList::GetSpeciesIdByName or vtSpeciesList::GetSpeciesIdByCommonName.
 * \param fSize Height of the new plant (meters).
 */
bool vtTerrain::AddPlant(const DPoint2 &pos, int iSpecies, float fSize)
{
	int num = m_PIA.AddPlant(pos, fSize, iSpecies);
	if (num == -1)
		return false;

	if (!m_PIA.CreatePlantNode(num))
		return false;

	vtTransform *pTrans = m_PIA.GetPlantNode(num);

	// add tree to scene graph
	AddNodeToVegGrid(pTrans);
	return true;
}

/**
 * Delete all the selected plants in the terrain's plant array.
 */
int vtTerrain::DeleteSelectedPlants()
{
	int num_deleted = 0;

	// first remove them from the terrain
	for (int i = m_PIA.GetNumEntities() - 1; i >= 0; i--)
	{
		if (m_PIA.IsSelected(i))
		{
			vtTransform *pTrans = m_PIA.GetPlantNode(i);
			if (pTrans != NULL)
			{
				vtGroup *pParent = pTrans->GetParent();
				if (pParent)
				{
					pParent->RemoveChild(pTrans);
					m_PIA.DeletePlant(i);
					num_deleted ++;
				}
			}
		}
	}
	return num_deleted;
}

/**
 * Set the list of plant species that this terrain should use.  Using this
 * method allows a set of species to be shared between many terrains.
 */
void vtTerrain::SetPlantList(vtSpeciesList3d *pPlantList)
{
	m_pPlantList = pPlantList;
	m_PIA.SetPlantList(m_pPlantList);
}

/**
 * Adds a node to the terrain.
 * The node will be added directly to this specific terrain, so it will be
 * hidden whenever the terrain is not active.
 *
 * \sa AddNodeToVegGrid, AddNodeToStructGrid
 */
void vtTerrain::AddNode(vtNode *pNode)
{
	m_pTerrainGroup->AddChild(pNode);
}

/**
 * Adds a node to the terrain.
 * The node will be added to the Vegetation LOD Grid of the terrain, so it
 * will be culled when it is far from the viewer.  This method is used by
 * the terrain vegetation methods, and you can also use it directly if you
 * have your own vegetation nodes to add.
 *
 * \sa AddNode
 */
bool vtTerrain::AddNodeToVegGrid(vtTransform *pTrans)
{
	if (!m_pVegGrid)
		return false;
	return m_pVegGrid->AppendToGrid(pTrans);
}

/**
 * Adds a node to the terrain.
 * The node will be added to the Structure LOD Grid of the terrain, so it will be
 * culled when it is far from the viewer.  This is usually desirable when
 * the models are complicated or there are lot of them.
 *
 * There is another form of this method which takes a vtGeom node instead.
 *
 * \sa AddNode
 */
bool vtTerrain::AddNodeToStructGrid(vtTransform *pTrans)
{
	if (!m_pStructGrid)
		return false;
	return m_pStructGrid->AppendToGrid(pTrans);
}

/**
 * Adds a node to the terrain.
 * The node will be added to the Structure LOD Grid of the terrain, so it will be
 * culled when it is far from the viewer.  This is usually desirable when
 * the models are complicated or there are lot of them.
 *
 * There is another form of this method which takes a vtTransform node instead.
 *
 * \sa AddNode
 */
bool vtTerrain::AddNodeToStructGrid(vtGeom *pGeom)
{
	if (!m_pStructGrid)
		return false;
	return m_pStructGrid->AppendToGrid(pGeom);
}


/**
 * Removes a node from the terrain.
 *
 * \sa RemoveNodeFromStructGrid
 */
void vtTerrain::RemoveNode(vtNode *pNode)
{
	m_pTerrainGroup->RemoveChild(pNode);
}

/**
 * Removes a node from the terrain's structure LOD grid.
 *
 * \sa RemoveNode
 */
void vtTerrain::RemoveNodeFromStructGrid(vtNode *pNode)
{
	if (m_pStructGrid)
		m_pStructGrid->RemoveNodeFromGrid(pNode);
}

int vtTerrain::DoStructurePaging()
{
	if (!m_pPagedStructGrid)
		return 0;

	vtCamera *cam = vtGetScene()->GetCamera();
	FPoint3 CamPos = cam->GetTrans();

	m_pPagedStructGrid->DoPaging(CamPos, m_iPagingStructureMax,
		m_fPagingStructureDist);
	return m_pPagedStructGrid->GetQueueSize();
}

void vtTerrain::SetStructurePageOutDistance(float f)
{
	if (m_pPagedStructGrid)
	{
		m_fPagingStructureDist = f;
		EnforcePageOut();
	}
}

void vtTerrain::EnforcePageOut()
{
	// The page-out distance should never be less than the structure LOD
	//  distance, otherwise we might be trying to load and unload the same
	//  structures.
	float fStructLodDist = GetLODDistance(TFT_STRUCTURES);
	if (m_fPagingStructureDist < fStructLodDist)
		m_fPagingStructureDist = fStructLodDist;
}

////////////////////////////////////////////////////////////////////////////
// Abstracts

void vtTerrain::SetAbstractLayer(vtAbstractLayer *alay)
{
	m_pActiveAbstractLayer = alay;
}

/** Get the currently active abstract layer for this terrain. */
vtAbstractLayer *vtTerrain::GetAbstractLayer()
{
	return m_pActiveAbstractLayer;
}

void vtTerrain::RemoveFeatureGeometry(vtAbstractLayer *alay)
{
	// labels might be targets of the billboard engine
	vtGroup *labels = alay->pLabelGroup;
	if (labels)
	{
		for (unsigned int i = 0; i < labels->GetNumChildren(); i++)
			GetBillboardEngine()->RemoveTarget(labels->GetChild(i));
	}
	alay->ReleaseGeometry();
}


////////////////////////////////////////////////////////////////////////////
// Scenarios

void vtTerrain::ActivateScenario(int iScenario)
{
	ScenarioParams &ScenarioParams = m_Params.m_Scenarios[iScenario];
	vtStringArray &ActiveLayers = ScenarioParams.GetActiveLayers();

	unsigned int iNumActiveLayers = ActiveLayers.size();

	for (unsigned int i = 0; i < m_Layers.GetSize(); i++)
	{
		vtLayer *lay = m_Layers[i];
		vtString Name = StartOfFilename(lay->GetLayerName());
		RemoveFileExtensions(Name);

		bool bFound = false;
		for (unsigned int j = 0; j < iNumActiveLayers; j++)
			if (Name == ActiveLayers[j])
				bFound = true;
		lay->SetVisible(bFound);
	}
}


////////////////////////////////////////////////////////////////////////////
// Dynamic elevation

/**
 * If you have told vtTerrain to preserve a copy of the original elevation
 * grid in memory, you can modify that grid, then call this method to update
 * the CLOD surface.  This can take up a few seconds, depending on the size
 * of your grid.
 */
void vtTerrain::UpdateElevation()
{
	if (!m_pDynGeom)
		return;
	SRTerrain *sr = dynamic_cast<SRTerrain*>(m_pDynGeom);
	if (!sr)
		return;
	sr->ReInit(m_pElevGrid);
}

/**
 * Drape all the culture on the terrain again, to keep them on the surface
 * in the case when the elevation values have changed.
 *
 * \param area You can speed up this function by passing the area to re-drape
 *		in.  Otherwise, simply pass an empty area, and all culture will be
 *		re-draped.
 */
void vtTerrain::RedrapeCulture(const DRECT &area)
{
	// Tell the terrain to re-drape all its structure instances.
	for (unsigned int i = 0; i < m_Layers.GetSize(); i++)
	{
		vtStructureLayer *slay = dynamic_cast<vtStructureLayer *>(m_Layers[i]);
		if (slay)
		{
			for (unsigned int j = 0; j < slay->GetSize(); j++)
			{
				vtStructure *st = slay->GetAt(j);
				vtStructure3d *s3 = slay->GetStructure3d(j);

				// If we were given an area, omit structures outside it
				if (!area.IsEmpty() && !st->IsContainedBy(area))
					continue;

				// A fence might need re-draping, so we have to rebuild geometry
				vtFence3d *f3 = dynamic_cast<vtFence3d*>(s3);
				if (f3)
					f3->CreateNode(this);

				// A building's geometry will not change, only move up or down
				vtBuilding3d *b3 = dynamic_cast<vtBuilding3d*>(s3);
				if (b3)
					b3->AdjustHeight(m_pHeightField);

				// A instance's geometry will not change, only move up or down
				vtStructInstance3d *si = dynamic_cast<vtStructInstance3d*>(s3);
				if (si)
					si->UpdateTransform(m_pHeightField);

			}
		}
		//vtAbstractLayer *alay = dynamic_cast<vtAbstractLayer *>(m_Layers[i]);
	}
	// And plants
	for (unsigned int i = 0; i < m_PIA.GetNumEntities(); i++)
	{
		m_PIA.UpdateTransform(i);
	}
	// What else?  Abstract Layers. Roads, perhaps.
}

