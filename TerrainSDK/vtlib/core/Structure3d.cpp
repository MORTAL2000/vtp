//
// Structure3d.cpp
//
// Copyright (c) 2001-2002 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"

#include "Structure3d.h"
#include "Building3d.h"
#include "Fence3d.h"
#include "Terrain.h"


///////////////////////////////////////////////////////////////////////

vtStructInstance3d::vtStructInstance3d() : vtStructInstance()
{
	m_pContainer = NULL;
	m_pHighlight = NULL;
	m_pModel = NULL;
}

bool vtStructInstance3d::CreateShape(vtHeightField *pHeightField)
{
	if (!m_pContainer)
	{
		// constructing for the first time
		m_pContainer = new vtTransform();
	}

	const char *filename = GetValue("filename");
	if (filename)
	{
		m_pModel = vtLoadModel(filename);
		if (!m_pModel)
			return false;
		m_pContainer->AddChild(m_pModel);
	}
	const char *itemname = GetValue("itemname");
	if (itemname)
	{
		// TODO: use ContentManager to create model
	}
	const char *scale = GetValue("scale");
	if (scale)
	{
		double sc = atof(scale);
		if (sc != 0.0)
			m_fScale = sc;
	}

	UpdateTransform(pHeightField);
	return true;
}

void vtStructInstance3d::UpdateTransform(vtHeightField *pHeightField)
{
	m_pContainer->Identity();

	if (m_fScale != 1.0f)
		m_pContainer->Scale3(m_fScale, m_fScale, m_fScale);

	// try to work around 3DS coordinate axes difference problem
	vtString fname2 = GetValue("filename");
	int dot = fname2.ReverseFind('.');
	if (dot > 0)
	{
		vtString ext = fname2.Mid(dot+1);
		if (ext.CompareNoCase("3ds") == 0)
		{
			// Must rotate by 90 degrees for 3DS MAX -> OpenGL
			m_pContainer->Rotate2(FPoint3(1.0f, 0.0f, 0.0f), -PID2f);
		}
	}

	if (m_fRotation != 0.0f)
		m_pContainer->Rotate2(FPoint3(0,1,0), m_fRotation);

	FPoint3 surface_pos;
	pHeightField->ConvertEarthToSurfacePoint(m_p, surface_pos);
	m_pContainer->SetTrans(surface_pos);
}

/**
 * Display some bounding wires around the object to highlight it.
 */
void vtStructInstance3d::ShowBounds(bool bShow)
{
	if (bShow)
	{
		if (!m_pHighlight)
		{
			// the highlight geometry doesn't exist, so create it
			// get bounding sphere
			FSphere sphere;
			m_pModel->GetBoundSphere(sphere);

			m_pHighlight = CreateBoundSphereGeom(sphere);
			m_pContainer->AddChild(m_pHighlight);
		}
		m_pHighlight->SetEnabled(true);
	}
	else
	{
		if (m_pHighlight)
			m_pHighlight->SetEnabled(false);
	}
}

// implement vtStructure3d methods
bool vtStructInstance3d::CreateNode(vtHeightField *hf, const char *options)
{
	bool bSuccess = CreateShape(hf);
	if (!bSuccess)
	{
		// try again, looking on the standards data paths
		vtTag *tag = FindTag("filename");
		if (tag)
		{
			vtString fullpath = FindFileOnPaths(vtTerrain::m_DataPaths, tag->value);
			if (fullpath != "")
			{
				tag->value = fullpath;
				// try again
				bSuccess = CreateShape(hf);
			}
		}
	}
	return bSuccess;
}


///////////////////////////////////////////////////////////////////////
//
// vtStructureArray3d
//

vtBuilding *vtStructureArray3d::NewBuilding()
{
	// Make sure that subsequent operations on this building are done in with
	// the correct local coordinate system
	vtBuilding::s_Conv.Setup(m_proj.GetUnits(), DPoint2(0, 0));

	return new vtBuilding3d;
}

vtFence *vtStructureArray3d::NewFence()
{
	return new vtFence3d;
}

vtStructInstance *vtStructureArray3d::NewInstance()
{
	return new vtStructInstance3d;
}

vtStructure3d *vtStructureArray3d::GetStructure3d(int i)
{
	vtStructure *str = GetAt(i);

	if (str->GetType() == ST_BUILDING)
		return (vtStructure3d *) (vtBuilding3d *) str;

	if (str->GetType() == ST_FENCE)
		return (vtStructure3d *) (vtFence3d *) str;

	if (str->GetType() == ST_INSTANCE)
		return (vtStructure3d *) (vtStructInstance3d *) str;

	return NULL;
}

bool vtStructureArray3d::ConstructStructure(vtStructure3d *str,
													const char *options)
{
	return str->CreateNode(m_pHeightField, options);
}

void vtStructureArray3d::ReConstructStructure(vtStructure3d *str,
											  const char *options)
{
	str->DeleteNode();
	str->CreateNode(m_pHeightField, options);
}

void vtStructureArray3d::OffsetSelectedStructures(const DPoint2 &offset)
{
	vtStructure *str;
	for (int i = 0; i < GetSize(); i++)
	{
		str = GetAt(i);
		if (!str->IsSelected())
			continue;
		if (str->GetType() == ST_BUILDING)
		{
			vtBuilding3d *bld = GetBuilding(i);
			bld->Offset(offset);
			bld->AdjustHeight(m_pHeightField);

			// Should really move the building to a new cell in the LOD
			// Grid, but unless it's moving really far we don't need to
			// worry about this.
		}
		if (str->GetType() == ST_FENCE)
		{
			vtFence3d *fen = GetFence(i);
			// TODO: implement moving of fences?
		}
		if (str->GetType() == ST_INSTANCE)
		{
			vtStructInstance3d *inst = GetInstance(i);
			inst->Offset(offset);
			inst->UpdateTransform(m_pHeightField);
		}
	}
}

void vtStructureArray3d::VisualDeselectAll()
{
	for (int i = 0; i < GetSize(); i++)
	{
		vtStructure *str = (vtStructure *) GetAt(i);
		vtStructure3d *str3d = GetStructure3d(i);

		str->Select(false);
		str3d->ShowBounds(false);
	}
}

