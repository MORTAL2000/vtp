//
// Dynamic Terrain class
//
// This is the parent class for terrain which can redefine it's
// surface at render time.
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"
#include "vtlib/core/HeightField.h"
#include "DynTerrain.h"

vtDynTerrainGeom::vtDynTerrainGeom() : vtDynGeom()
{
	m_fPixelError = 2.0f;
	m_iPolygonTarget = 10000;

	m_bCulleveryframe = true;
	m_bCullonce = false;
	m_bDetailTexture = false;
	m_pDetailMat = NULL;

	m_fXLookup = m_fZLookup = NULL;
}

vtDynTerrainGeom::~vtDynTerrainGeom()
{
	delete m_fXLookup;
	delete m_fZLookup;
}

void vtDynTerrainGeom::Init2()
{
}

void vtDynTerrainGeom::BasicInit(vtLocalGrid *pLocalGrid)
{
	// initialize the HeightField
	Initialize(pLocalGrid);

	// allocate and set the xz lookup tables
	m_fXLookup = new float[m_iXPoints];
	m_fZLookup = new float[m_iYPoints];
	int i;
	for (i = 0; i < m_iXPoints; i++)
		m_fXLookup[i] = m_Conversion.m_WorldExtents.left + i * m_fXStep;
	for (i = 0; i < m_iYPoints; i++)
		m_fZLookup[i] = m_Conversion.m_WorldExtents.bottom - i * m_fZStep;

	m_iTotalTriangles = m_iXPoints * m_iYPoints * 2;
}


void vtDynTerrainGeom::SetOptions(bool bUseTriStrips, int iTPatchDim, int iTPatchSize)
{
	m_bUseTriStrips = bUseTriStrips;
	m_iTPatchDim = iTPatchDim;
	m_iTPatchSize = iTPatchSize;
}

bool vtDynTerrainGeom::FindAltitudeAtPoint(const FPoint3 &p, float &fAltitude,
									FPoint3 *vNormal)
{
	int iX = (int)((p.x - m_Conversion.m_WorldExtents.left) / m_fXStep);
	int iZ = (int)(-(p.z - m_Conversion.m_WorldExtents.bottom) / m_fZStep);

	// safety check
	if (iX < 0 || iX >= m_iXPoints-1 || iZ < 0 || iZ >= m_iYPoints-1)
	{
		fAltitude = 0.0f;
		if (vNormal) vNormal->Set(0.0f, 1.0f, 0.0f);
		return false;
	}

	FPoint3 p0, p1, p2, p3;
	GetLocation(iX, iZ, p0);
	GetLocation(iX+1, iZ, p1);
	GetLocation(iX+1, iZ+1, p2);
	GetLocation(iX, iZ+1, p3);

	// find fractional amount (0..1 across quad)
	float fX = (float)  (p.x - p0.x) / m_fXStep;
	float fZ = (float) -(p.z - p0.z) / m_fZStep;

	// which way is this quad split?
	if ((iX + iZ) & 1)
	{
		// which of the two triangles in the quad is it?
		if (fX + fZ < 1)
		{
			fAltitude = p0.y + fX * (p1.y - p0.y) + fZ * (p3.y - p0.y);

			if (vNormal)
			{
				// find normal also
				FPoint3 edge0 = p1 - p0;
				FPoint3 edge1 = p3 - p0;
				*vNormal = edge0.Cross(edge1);
				vNormal->Normalize();
			}
		}
		else
		{
			fAltitude = p2.y + (1.0f-fX) * (p3.y - p2.y) + (1.0f-fZ) * (p1.y - p2.y);

			if (vNormal)
			{
				// find normal also
				FPoint3 edge0 = p3 - p2;
				FPoint3 edge1 = p1 - p2;
				*vNormal = edge0.Cross(edge1);
				vNormal->Normalize();
			}
		}
	}
	else
	{
		if (fX > fZ)
		{
			fAltitude = p0.y + fX * (p1.y - p0.y) + fZ * (p2.y - p1.y);

			if (vNormal)
			{
				// find normal also
				FPoint3 edge0 = p1 - p0;
				FPoint3 edge1 = p2 - p1;
				*vNormal = edge0.Cross(edge1);
				vNormal->Normalize();
			}
		}
		else
		{
			fAltitude = p0.y + fX * (p2.y - p3.y) + fZ * (p3.y - p0.y);

			if (vNormal)
			{
				// find normal also
				FPoint3 edge0 = p2 - p3;
				FPoint3 edge1 = p3 - p0;
				*vNormal = edge0.Cross(edge1);
				vNormal->Normalize();
			}
		}
	}
	return true;
}


void vtDynTerrainGeom::SetCull(bool bOnOff)
{
	m_bCulleveryframe = bOnOff;
}

void vtDynTerrainGeom::CullOnce()
{
	m_bCullonce = true;
}

void vtDynTerrainGeom::SetPixelError(float fPixelError)
{
	m_fPixelError = fPixelError;
}

float vtDynTerrainGeom::GetPixelError()
{
	return m_fPixelError;
}

void vtDynTerrainGeom::SetPolygonCount(int iPolygonCount)
{
	m_iPolygonTarget = iPolygonCount;
}

int vtDynTerrainGeom::GetPolygonCount()
{
	return m_iPolygonTarget;
}

void vtDynTerrainGeom::SetDetailMaterial(vtMaterial *pApp, float fTiling)
{
	m_pDetailMat = pApp;
	m_bDetailTexture = (m_pDetailMat != NULL);
	m_fDetailTiling = fTiling;
}

void vtDynTerrainGeom::EnableDetail(bool bOn)
{
	m_bDetailTexture = (m_pDetailMat != NULL && bOn);
}

int vtDynTerrainGeom::GetNumDrawnTriangles()
{
	return m_iDrawnTriangles;
}

///////////////////////////////////////////////////////////////////////
//
// Overrides for vtDynGeom
//
void vtDynTerrainGeom::DoCalcBoundBox(FBox3 &box)
{
	// derive bounding box from known terrain origin and size

	// units are those of the coordinate space below the transform
	box.Set(0,			m_fMinHeight, 0,
			m_iXPoints, m_fMaxHeight, m_iYPoints);
}

void vtDynTerrainGeom::DoCull(FPoint3 &eyepos_ogl, IPoint2 window_size, float fov)
{
	// make sure we cull at least every 300 ms
	bool bCullThisFrame = false;
#if 0
	static float last_time = 0.0f;
	float this_time = vtGetTime();
	if ((this_time - last_time) > 0.3f)
	{
		bCullThisFrame = true;
		last_time = this_time;
	}
#endif
	if (m_bCulleveryframe || m_bCullonce || bCullThisFrame)
	{
		DoCulling(eyepos_ogl, window_size, fov);
		m_bCullonce = false;
	}
}

//////////////////////////////////////////////////////////////////////

void vtDynTerrainGeom::SetupTexGen(float fTiling)
{
	GLfloat sPlane[4] = { fTiling * 1.0f / (m_iXPoints-1), 0.0f, 0.0f, 0.0f };
	GLfloat tPlane[4] = { 0.0f, 0.0f, fTiling * 1.0f / -(m_iYPoints-1), 0.0f };

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_2D);
}

void vtDynTerrainGeom::SetupBlockTexGen(int a, int b)
{
	// carefully determine the right u,v offset, leaving a
	// half-texel of buffer at the edge of each patch
	float uv_offset = 1.0f / m_iTPatchSize / 2.0f;

	float grid_offset_x = uv_offset * ((m_iXPoints-1)/4.0f) * 2.0f;
	float grid_offset_y = uv_offset * (-(m_iYPoints-1)/4.0f) * 2.0f;

	float factor_x = (float) (1.0 / ((m_iXPoints-1)/4.00+grid_offset_x));
	float factor_y = (float) (1.0 / (-(m_iYPoints-1)/4.00+grid_offset_y));

	GLfloat sPlane[4] = { factor_x, 0.00, 0.0, (a*2+1) * uv_offset };
	GLfloat tPlane[4] = { 0.0, 0.00, factor_y, -(b*2+1) * uv_offset };

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_2D);
}

void vtDynTerrainGeom::DisableTexGen()
{
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

GLboolean ca, va, na, ia, ta;

void vtDynTerrainGeom::PreRender() const
{
#if VTLIB_DSM || 0
	// preserve
	ca = glIsEnabled(GL_COLOR_ARRAY);
	va = glIsEnabled(GL_VERTEX_ARRAY);
	na = glIsEnabled(GL_NORMAL_ARRAY);
	ia = glIsEnabled(GL_INDEX_ARRAY);
	ta = glIsEnabled(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif

	// get ready to count drawn triangles
	vtDynTerrainGeom *pHack = (vtDynTerrainGeom *)this;
	pHack->m_iDrawnTriangles = 0;
}

void vtDynTerrainGeom::PostRender() const
{
#if VTLIB_DSM || 0
	// restore
	if (ca) glEnableClientState(GL_COLOR_ARRAY);
	if (va) glEnableClientState(GL_VERTEX_ARRAY);
	if (na) glEnableClientState(GL_NORMAL_ARRAY);
	if (ia) glEnableClientState(GL_INDEX_ARRAY);
	if (ta) glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
}

///////////////////////////////////////////////////////////////
// Helper

//
// Compute base-2 logarithm of an integer.
// There's probably an even simpler way to do this with sneaky
// logical ops or without a loop, but this works.
//
int vt_log2(int n)
{
	int temp = n, i;
	for (i = 0; temp > 1; i++)
		temp >>= 1;
	return i;
}


