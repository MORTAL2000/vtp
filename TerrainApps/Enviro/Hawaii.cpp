//
// Hawai`i.cpp
//
// Terrain implementation specific to the Big Island of Hawai`i.
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"
#include "vtlib/core/Building3d.h"
#include "vtlib/core/DynTerrain.h"
#include "Hawaii.h"
#include "Nevada.h"


///////////////////////////////

IslandTerrain::IslandTerrain() : PTerrain()
{
	// Points of Interest
	// top left (x,y) then bottom right (x,y)

	AddPointOfInterest(283376, 2182614, 287025, 2181205, "Hilo Airport", "http://www.hawaii.gov/dot/hilo.htm");
	AddPointOfInterest(240459, 2202455, 244033, 2188779, "Mauna Kea", "/Html/maunakea.htm");
	AddPointOfInterest(226689, 2157368, 227719, 2153045, "Mauna Loa", "http://www.yahoo.com");
	AddPointOfInterest(188873, 2153990, 195080, 2156953, "Kealakekua bay", "/Html/kealakekua.htm");
	AddPointOfInterest(253500, 2103500, 282500, 2080000, "Lo`ihi", "/Html/loihi_seamount.htm");
}

IslandTerrain::~IslandTerrain()
{
}

void IslandTerrain::create_telescopes()
{
#if 0
	// this works, but overrides the structures indicates in TParams
	// we can do something like this once we have support for multiple
	// structure layers
	CreateStructuresFromXML(m_strDataPath + "BuildingData/tscope_loc.vtst");
#elif 1
	vtStructureArray3d sa;
	vtString fname = FindFileOnPaths(m_DataPaths, "BuildingData/tscope_loc.vtst");
	if (fname == "")
		return;
	bool success = sa.ReadXML(fname);
	if (!success)
		return;

	int num_structs = sa.GetSize();
	sa.SetHeightField(m_pHeightField);
	for (int i = 0; i < num_structs; i++)
	{
		vtStructure3d *str = sa.GetStructure(i);

		success = sa.ConstructStructure(str);
		if (!success)
			continue;

		vtTransform *pTrans = str->GetTransform();
		if (pTrans)
			m_pLodGrid->AppendToGrid(pTrans);
	}
#endif
}


vtGeom *IslandTerrain::make_red_cube()
{
	vtGeom *thebox = new vtGeom();
	float ws = 100.0f * WORLD_SCALE;	// convert 100m to 3d system units

	//code to make it a Shape
	vtMesh *mesh = new vtMesh(GL_TRIANGLE_FAN, VT_Normals, 24);
	FPoint3 size(ws, ws, ws);
	FPoint3 half = size / 2;	// Block() will double the size
	mesh->CreateBlock(half);

	vtMaterialArray *looks = new vtMaterialArray();
	looks->AddRGBMaterial1(RGBf(1.0f, 0.0f, 0.0f));
	thebox->SetMaterials(looks);
	thebox->AddMesh(mesh, 0);

	return thebox;
}

void IslandTerrain::create_airports()
{
#if 0
	vtTransform *ITO = LoadModel("Culture/ITO.dsm");
	vtTransform *KOA = LoadModel("Culture/KOA.dsm");
	vtTransform *MUE = LoadModel("Culture/MUE.dsm");

	float scale = WORLD_SCALE;

	if (ITO)
	{
		ITO->Scale2(scale, scale, scale);
		PlantModelAtPoint(ITO, DPoint2(283575, 2181163();
 		AddNode(ITO);
	}
	if (KOA)
	{
		KOA->Scale2(scale, scale, scale);
		PlantModelAtPoint(KOA, DPoint2(180290, 2184990));
 		AddNode(KOA);
	}
	if (MUE)
	{
		MUE->Scale2(scale, scale, scale);
		PlantModelAtPoint(MUE, DPoint2(219990, 2213505));
 		AddNode(MUE);
	}

/*	float fSizeExag = m_Params.m_fVehicleSize, fSpeedExag = m_Params.m_fVehicleSpeed;

	for (int i = 0; i < 3; i++)
	{
		vtTransform *copy = CreateVehicle("747", RGBf(1.0f, 1.0f, 0.0f));
		AddNode(copy);

		PlaneEngine *pEng = new PlaneEngine(fSizeExag, fSpeedExag, ITO);
		pEng->SetTarget(copy);
		pEng->SetHoop(i*2);
		AddEngine(pEng, pScene);
	}
*/
#endif
}


void IslandTerrain::CreateCustomCulture(bool bDoSound)
{
	DPoint2 bound[8];
	bound[0].Set(237387, 2219678);
	bound[1] = bound[0] + DPoint2(0.0, -96.64);
	bound[2] = bound[1] + DPoint2(82.5, 0.0);
	bound[3] = bound[1] + DPoint2(178.2, 0.0);
	bound[4] = bound[3] + DPoint2(0.0, 30.48);
	bound[5] = bound[4] + DPoint2(-178.2 + 37.44f, 0.0);
	bound[6] = bound[5] + DPoint2(0.0, 96.64f - 30.48);
	bound[7] = bound[2] + DPoint2(0.0, 12.2);

#if 0
	if (m_Params.m_bBuildings)
	{
		if (PointIsInTerrain(bound[7].x, bound[7].y)) // if area includes ben's house
		{
			// test ability to import a max model (a house)
			vtTransform *house = LoadModel("BuildingModels/house3.dsm");
			if (house)
			{
				// scale was one unit = 1 i
				// so adjust to fit our units, one unit = (1/WORLD_SCALE) meters
				// 1 inch = 2.54 centimeters = .0254 meters
				float scale = .0254f * WORLD_SCALE;
				house->Scale2(scale, scale, scale);

				// plant it on the ground
				PlantModelAtPoint(house, bound[7]);

//  			AddNode(house);
				AddNodeToLodGrid(house);
			}
		}
#if 1
		//import the lighthouses
		vtTransform *lighthouse1 = LoadModel("BuildingModels/mahukonalthse.dsm");
		if (lighthouse1)
		{
			// scale was one unit = 1 m

			float scale = WORLD_SCALE;
			lighthouse1->Scale2(scale, scale, scale);

			// plant it on the ground
			PlantModelAtPoint(lighthouse1, DPoint2(197389, 2230283));

// 			AddNode(lighthouse1);
			AddNodeToLodGrid(lighthouse1);
		}
#endif
	}
#endif

	if (m_Params.m_bAirports)
	{
		create_airports();
		// more max-modeled buildings
		if (PointIsInTerrain(DPoint2(240749, 2194370))) // if area includes top of Mauna Kea
			create_telescopes();
	}

#if 1
	if (PointIsInTerrain(DPoint2(234900, 2185840))) // if area includes saddle
	{
		vtTransform *bench = LoadModel("Culture/parkbench.3ds");
		if (bench)
		{
			float scale = 3.0f * 0.01f * WORLD_SCALE;
			bench->Scale3(scale, scale*1.1f, scale);
			PlantModelAtPoint(bench, DPoint2(234900, 2185840));
			m_pLodGrid->AppendToGrid(bench);
		}
	}
#endif

#if 1
	if (PointIsInTerrain(DPoint2(227611, 2155222))) // if area includes top of Mauna Loa
	{
		vtGeom *thebox = make_red_cube();
	}
#endif

//	if (m_Params.m_bRoads && m_Params.m_bVehicles)
//		create_road_vehicles(pScene);

	if (m_Params.m_bVehicles)
	{
		SetupVehicles();
		create_airplanes(m_Params.m_fVehicleSize, m_Params.m_fVehicleSpeed, bDoSound);
		create_ground_vehicles(m_Params.m_fVehicleSize, m_Params.m_fVehicleSpeed);
	}

	if (m_Params.m_bDetailTexture)
	{
		m_pDetailMats = new vtMaterialArray();
		vtString path = FindFileOnPaths(m_DataPaths, "GeoTypical/grass_repeat2_512.bmp");
		vtImage *pDetailTexture = new vtImage(path);
		if (pDetailTexture->LoadedOK())
		{
			int index = m_pDetailMats->AddTextureMaterial(pDetailTexture,
							 true,	// culling
							 false,	// lighting
							 true,	// transp: blend
							 false,	// additive
							 0.0f, 1.0f,	// ambient, diffuse
							 0.5f, 0.0f,	// alpha, emmisive
							 true, false,	// texgen, clamp
							 true);			// mipmap
			m_pDetailMat = m_pDetailMats->GetAt(index);

			FRECT r = m_pHeightField->m_Conversion.m_WorldExtents;
			float width_meters = r.Width() / WORLD_SCALE;
			m_pDynGeom->SetDetailMaterial(m_pDetailMat, 0.025f * width_meters);
		}
	}
}

///////////////////////////////////////

#if 0
	// Test xfrog plant geometry
	XfrogModel_ptr tree = LoadXFrogTree(m_strDataPath + "PlantModels/papaya1.xfr");
	vtGeom *pPlantShape = CreateShapeFromXfrogTree(tree, 1.0f);
	pPlantShape->SetName2("Plant");

	for (int i = 0; i < m_br.m_Types.GetSize(); i++)
		LookupPlantIndices(m_br.m_Types[i]);
#endif


void IslandTerrain::create_airplanes(float fSize, float fSpeed, bool bDoSound)
{
#if 0
	// make x planes
	for (int i = 0; i < 6; i++)
	{
		vtTransform *copy = CreateVehicle("747", RGBf(1.0f, 1.0f, 0.0f), fSize);
		AddNode(copy);

		// make it bigger and faster than real life
		float fSpeedExag = fSpeed;

		// attach engine
		AirportCodes code;
//		if (i < 3)
			code = KOA;
//		else
//			code = ITO;

		PlaneEngine *pEng = new PlaneEngine(fSpeedExag, code);
		pEng->SetTarget(copy);
		pEng->SetHoop(i);
		AddEngine(pEng);

#if 0
		if (bDoSound)
		{
			//sound stuff
			vtSound3D* plane = new vtSound3D(m_strDataPath + "Vehicles/Airport-trim1.wav");
			plane->Initialize();
			plane->SetName2("Plane Sound");
			plane->SetModel(1,1,200,200);	//set limit of how far away sound can be heard
			plane->SetTarget(copy);			//set target
			plane->SetMute(true);			//mute the sound until later
			plane->Play(0, 0.0f);			//play the sound (muted)
			AddEngine(plane, pScene);
		}
#endif
	}
#endif
}

