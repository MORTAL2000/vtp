//
// StructureLayer.h
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef STRUCTLAYER_H
#define STRUCTLAYER_H

#include "vtdata/shapelib/shapefil.h"
#include "vtdata/StructArray.h"
#include "Layer.h"

//////////////////////////////////////////////////////////

class vtStructureLayer : public vtLayer, public vtStructureArray
{
public:
	vtStructureLayer();

	bool GetExtent(DRECT &rect);
	void DrawLayer(wxDC* pDC, vtScaledView *pView);
	bool ConvertProjection(vtProjection &proj);
	bool OnSave();
	bool OnLoad();
	void GetProjection(vtProjection &proj);
	void SetProjection(vtProjection &proj);
	bool AppendDataFrom(vtLayer *pL);
	void Offset(const DPoint2 &p);

	void AddElementsFromSHP(const char *filename, vtProjection &proj);
//	void AddElementsFromSHPPoints(SHPHandle hSHP, int nElem);
//	void AddElementsFromSHPPolygons(const char *filename,
//									SHPHandle hSHP, int nElem);

	vtStructure *FindBuilding(DPoint2 &point, double epsilon);
	bool EditBuildingProperties();

	void DrawBuilding(wxDC* pDC, vtScaledView *pView, vtBuilding *bld);

	//inverts selection values on all roads and nodes.
	void InvertSelection();

protected:
	int m_size;	// size in pixels of the small crosshair at building center
};

#endif

