//
// StructArray.h
//
// Copyright (c) 2001-2003 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef STRUCTARRAYH
#define STRUCTARRAYH

#include "MathTypes.h"
#include "Projections.h"
#include "Structure.h"
#include <stdio.h>


/** This structure stores a description of how an imported file should be
   intepreted as built structure data. */
class StructImportOptions
{
public:
	vtStructureType type;
	DRECT			rect;
	bool			bInsideOnly;
	bool			bFlip;

	vtString		m_strFieldNameHeight;
	enum HeightType { STORIES, METERS, FEET } m_HeightType;

	vtString		m_strFieldNameFile;
};


/**
 * The vtStructureArray class contains a list of Built Structures
 * (vtStructure objects).  It can be loaded and saved to VTST files
 * with the ReadXML and WriteXML methods.
 *
 */
class vtStructureArray : public Array<vtStructure*>
{
public:
	vtStructureArray() { m_pEditBuilding = NULL; }
	~vtStructureArray() { Empty(); }
	virtual void DestructItems(int first, int last);	// override

	void DeleteSelected();
	virtual void DestroyStructure(int i) {}

	bool ReadSHP(const char *pathname, StructImportOptions &opt,
		void progress_callback(int) = NULL);
	void AddElementsFromOGR(class OGRDataSource *datasource,
		StructImportOptions &opt, void progress_callback(int) = NULL);

	bool ReadBCF(const char *pathname);		// read a .bcf file
	bool ReadBCF_Old(FILE *fp);				// support obsolete format
	bool ReadXML(const char *pathname);

	bool WriteSHP(const char *pathname);
	bool WriteXML(const char *pathname);
	bool WriteXML_Old(const char *pathname);

	bool FindClosestBuildingCorner(const DPoint2 &point, double epsilon,
						   int &building, int &corner, double &distance);
	bool FindClosestBuildingCenter(const DPoint2 &point, double epsilon,
						   int &building, double &distance);
	bool FindClosestLinearCorner(const DPoint2 &point, double epsilon,
						   int &structure, int &corner, double &distance);

	/** Find the structure which is closest to the given point, if it is within
	 * 'epsilon' distance.  The structure index and distance are returned by
	 * reference.
	 */
	bool FindClosestStructure(const DPoint2 &point, double epsilon,
			int &building, double &distance, bool bSkipBuildings = false);

	bool IsEmpty() { return (GetSize() == 0); }
	void GetExtents(DRECT &ext);

	// selection
	int NumSelected();
	void DeselectAll();

	// override these 'Factory' methods so that the vtStructureArray base
	// methods can be capable of handling subclasses of vtBuilding
	virtual vtBuilding *NewBuilding();
	virtual vtFence *NewFence();
	virtual vtStructInstance *NewInstance();

	// override to catch edit hightlighting
	virtual void SetEditedEdge(vtBuilding *bld, int lev, int edge);

	vtProjection m_proj;

protected:
	// used to indicate which edge should be hightlighted during editing
	vtBuilding *m_pEditBuilding;
	int m_iEditLevel;
	int m_iEditEdge;
};

extern vtStructureArray g_DefaultStructures;

// Helpers
int GetSHPType(const char *filename);

bool SetupDefaultStructures(const char *fname = NULL);
vtBuilding *GetClosestDefault(vtBuilding *pBld);

// When needed, we could also have:
//vtFence *GetClosestDefault(vtFence *pBld);
//vtStructInstance *GetClosestDefault(vtStructInstance *pBld);

#endif	// STRUCTARRAYH

