//
// Content3d.cpp
//
// 3D Content Management class.
//
// Copyright (c) 2003 Virtual Terrain Project.
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"
#include "vtdata/FilePath.h"
#include "vtdata/vtLog.h"
#include "Content3d.h"

vtItem3d::vtItem3d()
{
	m_pGroup = NULL;
}

vtItem3d::~vtItem3d()
{
	if (m_pGroup)
		m_pGroup->Destroy();
	m_pGroup = NULL;
}

bool vtItem3d::LoadModels(StringArray *pDataPaths)
{
	if (m_pGroup)
		return true;	// already loaded

	int i, models = NumModels();

	// attempt to instantiate the item
	vtGroup *pGroup;
	vtLOD *pLod;

	if (models > 1)
	{
		pLod = new vtLOD;
		m_pGroup = pLod;
	}
	else
	{
		pGroup = new vtLOD;
		m_pGroup = pGroup;
	}
	float ranges[20];
	ranges[0] = 0.0f;

	for (i = 0; i < models; i++)
	{
		vtModel *model = GetModel(i);
		vtNodeBase *pNode = vtLoadModel(model->m_filename);

		// if at first it's not found, and there are some data path(s) to search
		if (!pNode && pDataPaths != NULL)
		{
			// perhaps it's a relative path
			vtString fullpath = FindFileOnPaths(*pDataPaths, model->m_filename);
			if (fullpath != "")
				pNode = vtLoadModel(fullpath);
		}
		if (!pNode)
		{
			VTLOG("Couldn't load model from %hs\n",
				(const char *) model->m_filename);
			return false;
		}

		// Wrap in a transform node so that we can scale/rotate the node
		vtTransform *pTrans = new vtTransform();
		pTrans->AddChild(pNode);

		pTrans->Identity();
		if (model->m_filename.Right(3).CompareNoCase("3ds") == 0)
		{
			// Must rotate by 90 degrees for 3DS -> OpenGL
			pTrans->Rotate2(FPoint3(1.0f, 0.0f, 0.0f), -PID2f);
		}
		pTrans->Scale3(model->m_scale, model->m_scale, model->m_scale);

		m_pGroup->AddChild(pTrans);

		if (models > 1)
			ranges[i+1] = model->m_distance;
	}
	if (models > 1)
		pLod->SetRanges(ranges, models+1);

	return true;
}

///////////////////////////////////////////////////////////////////////

vtContentManager3d::vtContentManager3d()
{
	m_pDataPaths = NULL;
}

vtTransform *vtContentManager3d::CreateInstanceOfItem(vtItem *item)
{
	vtItem3d *pItem = (vtItem3d *) item;

	pItem->LoadModels(m_pDataPaths);

	if (pItem->m_pGroup)
	{
		vtTransform *xform = new vtTransform();
		xform->AddChild(pItem->m_pGroup);
		return xform;
	}
	return NULL;
}

