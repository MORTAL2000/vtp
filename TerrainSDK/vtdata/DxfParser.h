//
// DxfParser.h
//
// Class for parsing a DXF File.
//
// Copyright (c) 2004 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef DXFPARSER_H
#define DXFPARSER_H

#include <deque>
#include <vector>
#include <set>
#include "vtString.h"
#include "MathTypes.h"

enum DxfEntityType
{
	DET_Point,
	DET_Polyline,
	DET_Polygon,
	DET_3DFace
};

class DxfEntity
{
public:
	DxfEntity() {};
	std::vector<DPoint3> m_points;
	DxfEntityType m_iType;
	int m_iLayer;
};

class DxfCodeValue
{
public:
	DxfCodeValue() { m_iCode = -1; }
	int m_iCode;
	vtString m_sValue;
};

/**
 * This class parses the entire contents of a DXF file.  It is up to the
 * caller to go through the resulting entities and use what is desired.
 *
 * \par Example:
\code
	std::vector<DxfEntity> entities;
	std::vector<vtString> layers;

	DxfParser parser(fname, entities, layers);
	bool bSuccess = parser.RetreiveEntities();
	if (bSuccess)
	{
		// Look through the entities and take what is needed.
	}
\endcode
*/
class DxfParser
{
public:
	DxfParser(const vtString &sFileName,
		std::vector<DxfEntity> &entities,
		std::vector<vtString> &layers);
	bool RetreiveEntities(void progress_callback(int) = NULL);
	vtString GetFileName() { return m_sFileName; }
	void SetFileName(const vtString & sFileName) { m_sFileName = sFileName; }
	vtString GetLastError() { return m_strMessage; }

protected:
	std::vector<DxfEntity> & m_entities;
	std::vector<vtString> & m_layers;
	vtString m_sFileName;
	FILE * m_pFile;
	size_t m_iLine;
	size_t m_iLineCount;
	int m_iCounter;
	long m_iEndPosition;
	vtString m_strMessage;

	bool ParseSection();
	bool ReadCodeValue(DxfCodeValue &);
	void SkipSection();
	void ReadEntitySection(void progress_callback(int));
	void ReadPoint();
	void ReadPolyline();
	void ReadLine();
	void ReadVertex(std::vector<DPoint3> &);
	int GetLayerIndex(const vtString &);
	void ReadLWPolyline();
	void Read3DFace();
};

#endif	// DXFPARSER_H

