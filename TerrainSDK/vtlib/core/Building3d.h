//
// Building3d.h
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef BUILDING3DH
#define BUILDING3DH

#include "vtdata/Building.h"
#include "vtdata/StructArray.h"

class vtHeightField;

typedef Array<FLine3 *> Footprints3d;
// Overrides DestructItems to call constructors
inline void Footprints3d::DestructItems(int first, int last)
{
	for (int i = first; i <= last; ++i)
	{
		FLine3 *pFL = GetAt(i);
		delete pFL;
	}
}

struct MatMesh
{
	int			m_iMatIdx;
	vtMesh		*m_pMesh;
	bool		m_bFans;
};

class vtBuilding3d : public vtBuilding
{
public:
	vtBuilding3d();
	~vtBuilding3d();

	// copy
	vtBuilding3d &operator=(const vtBuilding &v);

	//looks up materials for the building
	void FindMaterialIndices();

	void CreateShape(vtHeightField *pHeightField, bool roof=true,
		bool walls=true, bool details=true);

	void DestroyGeometry();
	void CreateGeometry(vtHeightField *pHeightField, bool bDoRoof,
						bool bDoWalls, bool details);
	vtTransform *GetTransform();
	void AdjustHeight(vtHeightField *pHeightField);

	// randomize building properties
	void Randomize(int iStories);

	// display a bounding box around to object to highlight it
	void ShowBounds(bool bShow);

protected:
	int FindMatIndex(BldMaterial bldApp, RGBi inputColor=RGBi(0,0,0));
	void CreateSharedMaterials();

protected:
	// material
	static vtMaterialArray *s_Materials;

	// the geometry is composed of several meshes, one for each potential material used
	Array<MatMesh>	m_Mesh;

	vtMesh *FindMatMesh(BldMaterial bm, RGBi color, bool bFans);

	// center of the building in world coordinates (the origin of
	// the building's local coordinate system)
	FPoint3 m_center;

	// Local-coordinate Footprints, one per level
	Footprints3d m_lfp;

	// internal methods
	void DetermineWorldFootprints(vtHeightField *pHeightField);
	float GetHeightOfStories();
	void CreateUpperPolygon(vtLevel *lev, FLine3 &poly, FLine3 &poly2);

	void CreateEdgeGeometry(vtLevel *pLev, FLine3 &poly1, FLine3 &poly2,
		int iWall, bool details);

	// create special, simple geometry for a level which is uniform
	void CreateUniformLevel(int iLevel, float fHeight);

	// creates a wall.  base_height is height from base of floor
	// (to make siding texture match up right.)
	void AddWallSection(vtEdge *pEdge, BldMaterial bmat,
		const FLine3 &quad, float h1, float h2, float hf1 = 1.0f);

	//adds a wall section with a door
	void AddDoorSection(vtEdge *pWall, vtEdgeFeature *pFeat,
		const FLine3 &quad);

	//adds a wall section with a window
	void AddWindowSection(vtEdge *pWall, vtEdgeFeature *pFeat,
		const FLine3 &quad);

	void AddWallNormal(vtEdge *pWall, vtEdgeFeature *pFeat,
			const FLine3 &quad);

	void AddFlatRoof(FLine3 &pp, vtLevel *pLev);
	void AddShedRoof(FLine3 &pp, vtLevel *pLev, float height);
	/*	Top view:
		Hip Roof:			Gable Roof:
		_______				_______
		|\   /|				|  |  |
		| \ / |				|  |  |
		|  |  |				|  |  |
		|  |  |				|  |  |
		| / \ |				|  |  |
		|/___\|				|__|__|
		Side view:
		  ______			___________
		 /      \           |         |
		/________\			|_________| 
		(triangular from the other side.)
	*/
	void	AddHipRoof(FLine3 &pp, vtLevel *pLev, float height);
	void	AddGableRoof(FLine3 &pp, vtLevel *pLev, float height);
	void	BuildRoofPanel(FPoint3 *v, int n, ...);
	FPoint3	Normal(const FPoint3 &p0, const FPoint3 &p1, const FPoint3 &p2);

	vtTransform	*m_pContainer;	// The transform which is used to position the building
	vtGeom		*m_pGeom;		// The geometry node which contains the building geometry
	vtGeom		*m_pHighlight;	// The wireframe highlight
};

#endif
