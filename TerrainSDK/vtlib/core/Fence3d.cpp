//
// Fence3d.cpp
//
// Creates fence geometry, drapes on a terrain
//
// Copyright (c) 2001-2006 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"
#include "Light.h"
#include "Terrain.h"
#include "Fence3d.h"
#include "TerrainScene.h"

// statics
vtMaterialDescriptorArray3d vtFence3d::s_FenceMats;
int vtFence3d::s_mi_wire, vtFence3d::s_mi_metal, vtFence3d::s_mi_hightlight;


vtFence3d::vtFence3d() : vtFence()
{
	Init();
}

void vtFence3d::Init()
{
	m_pContainer = NULL;
	m_pFenceGeom = NULL;
	m_pHighlightMesh = NULL;
	m_bBuilt = false;
}

void vtFence3d::CreateMaterials()
{
	s_FenceMats.InitializeMaterials();

	// Materials for Posts

	// wood fence post
	s_FenceMats.Append(new vtMaterialDescriptor("wood",
		"Culture/fencepost_64.jpg", VT_MATERIAL_SELFCOLOURED_TEXTURE, -1, -1));

	// steel post textured material
	s_FenceMats.Append(new vtMaterialDescriptor("steel",
		"Culture/chainpost32.jpg", VT_MATERIAL_SELFCOLOURED_TEXTURE, -1, -1));

	// Materials for Connections

	// wire material
	s_mi_wire = s_FenceMats.GetMatArray()->AddRGBMaterial(RGBf(0.0f, 0.0f, 0.0f), // diffuse
		RGBf(0.4f, 0.4f, 0.4f),	// ambient
		false, true, false,		// culling, lighting, wireframe
		0.6f);					// alpha

	// metal material (grey)
	s_mi_metal = s_FenceMats.GetMatArray()->AddRGBMaterial(RGBf(0.4f, 0.4f, 0.4f), // diffuse
		RGBf(0.3f, 0.3f, 0.3f));	// ambient

	// chainlink material: twosided, ambient, and alpha-blended
	s_FenceMats.Append(new vtMaterialDescriptor("chain-link",
		"Culture/chain128-4.png", VT_MATERIAL_SELFCOLOURED_TEXTURE, 0.5f, 0.5f, true, true, true));

	// create drystone textured material
	s_FenceMats.Append(new vtMaterialDescriptor("drystone",
		"Culture/drystone_wall_512.jpg", VT_MATERIAL_SELFCOLOURED_TEXTURE, 2.4f, 1.2f));
	s_FenceMats.Append(new vtMaterialDescriptor("stone",
		"Culture/stone256.jpg", VT_MATERIAL_SELFCOLOURED_TEXTURE, 2.5f, -1));

	// create privet textured material
	s_FenceMats.Append(new vtMaterialDescriptor("privet",
		"Culture/privet_256.jpg", VT_MATERIAL_SELFCOLOURED_TEXTURE, 1.2f, 1.2f, true));

	// create railing textured materials: twosided, ambient, and alpha-blended
	s_FenceMats.Append(new vtMaterialDescriptor("railing_pipe",
		"Culture/railing_pipe.png", VT_MATERIAL_SELFCOLOURED_TEXTURE, 1, -1, true, true, true));
	s_FenceMats.Append(new vtMaterialDescriptor("railing_wire",
		"Culture/railing_wire.png", VT_MATERIAL_SELFCOLOURED_TEXTURE, 1, -1, true, true, true));
	s_FenceMats.Append(new vtMaterialDescriptor("railing_eu",
		"Culture/railing_eu.png", VT_MATERIAL_SELFCOLOURED_TEXTURE, 1, -1, true, true, true));

	// add red material for display of unknown material
	s_FenceMats.Append(new vtMaterialDescriptor("unknown", "",
		VT_MATERIAL_COLOURED, 1, 1, true, true, false, RGBi(255,0,0)));

	// highlight (yellow)
	s_mi_hightlight = s_FenceMats.GetMatArray()->AddRGBMaterial(RGBf(1.0f, 1.0f, 0.0f), // diffuse
		RGBf(0,0,0),	// ambient
		false, false, true,		// culling, lighting, wireframe
		0.7f);					// alpha

	s_FenceMats.CreateMaterials();
}

void vtFence3d::AddFencepost(const FPoint3 &p1, vtMaterialDescriptor *desc)
{
	// create fencepost block
	vtMesh *pPostMesh = new vtMesh(vtMesh::TRIANGLE_FAN, VT_Normals | VT_TexCoords, 20);

	FPoint3 PostSize(m_Params.m_fPostWidth, m_Params.m_fPostHeight, m_Params.m_fPostDepth);
	pPostMesh->CreateOptimizedBlock(PostSize);

	// scoot over and upwards to put it above ground
	FMatrix4 t;
	t.Identity();
	t.Translate(p1);
	pPostMesh->TransformVertices(t);

	m_pFenceGeom->AddMesh(pPostMesh, desc->GetMaterialIndex());
	pPostMesh->Release();	// pass ownership
}

vtMaterialDescriptor *vtFence3d::FindDescriptor(const vtString &type)
{
	RGBf dummy;
	vtMaterialDescriptor *desc = s_FenceMats.FindMaterialDescriptor(type, dummy);
	if (!desc)
		desc = s_FenceMats.FindMaterialDescriptor("unknown", dummy);
	return desc;
}

FPoint3 SidewaysVector(const FPoint3 &p0, const FPoint3 &p1)
{
	FPoint3 diff = p1 - p0;
	FPoint3 up(0,1,0);
	FPoint3 cross = diff.Cross(up);
	cross.Normalize();
	return cross;
}

void vtFence3d::AddFenceMeshes(vtHeightField3d *pHeightField)
{
	unsigned int i, j;
	unsigned int numfencepts = m_pFencePts.GetSize();

	FLine3 p3;

	FPoint3 diff, fp;
	FPoint3 PostSize(m_Params.m_fPostWidth, m_Params.m_fPostHeight,
		m_Params.m_fPostDepth);

	// first, project the posts from earth to world
	m_Posts3d.SetSize(numfencepts);
	for (i = 0; i < numfencepts; i++)
		// true = include culture
		pHeightField->ConvertEarthToSurfacePoint(m_pFencePts[i], m_Posts3d[i], true);

	if (m_Params.m_PostType != "none")
	{
		// has posts
		// determine where the fence posts go
		for (i = 0; i < numfencepts; i++)
		{
			if (i == numfencepts-1)
			{
				p3.Append(m_Posts3d[i]);
				continue;
			}
			// get start and end group points for this section
			FPoint3 wpos1 = m_Posts3d[i];
			FPoint3 wpos2 = m_Posts3d[i+1];

			// look at world distance (approximate meters, _not_ earth
			//  coordinates, which might be in e.g. feet or degrees)
			diff = wpos2 - wpos1;
			float distance = sqrt(diff.x*diff.x+diff.z*diff.z);
			unsigned int segments = (unsigned int) (distance / m_Params.m_fPostSpacing);
			if (segments < 1) segments = 1;
			FPoint3 diff_per_segment = diff / (float) segments;

			for (j = 0; j < segments; j++)
			{
				fp = wpos1 + (diff_per_segment * (float)j);

				if (i > 0 && i < numfencepts-1)
				{
					// randomly offset by up to 4% of fence spacing, for "realism"
					fp.x += random_offset(0.04f * m_Params.m_fPostSpacing);
					fp.z += random_offset(0.04f * m_Params.m_fPostSpacing);
				}
				// false: true elevation, true: include culture (structures and roads)
				pHeightField->FindAltitudeAtPoint(fp, fp.y, false, CE_ALL);
				p3.Append(fp);
			}
		}
		// generate the posts
		vtMaterialDescriptor *desc = FindDescriptor(m_Params.m_PostType);
		for (i = 0; i < p3.GetSize(); i++)
			AddFencepost(p3[i], desc);
	}
	else
	{
		// no post spacing to consider, so just use the input vertices
		p3.SetSize(numfencepts);
		for (i = 0; i < numfencepts; i++)
			p3[i] = m_Posts3d[i];
	}

	unsigned int npoints = p3.GetSize();

	bool bLeft = false, bRight = false, bWires = (npoints > 1);
	if (m_Params.m_PostExtension != "none")
	{
		if (m_Params.m_PostExtension == "left")
			bLeft = true;
		if (m_Params.m_PostExtension == "right")
			bRight = true;
		if (m_Params.m_PostExtension == "double")
			bLeft = bRight = true;
	}
	if (bLeft || bRight)
	{
		// create extension prism(s)
		vtMesh *pMesh = new vtMesh(vtMesh::TRIANGLE_FAN, VT_Normals, 20);

		FPoint2 size(m_Params.m_fPostWidth, m_Params.m_fPostWidth);
		FPoint2 size1 = size * 0.9f;
		FPoint2 size2 = size * 0.5f;
		FPoint3 sideways, upward;

		float wire_height[3] = { 0.3f, 0.6f, 0.9f };

		vtMesh *pWiresLeft, *pWiresRight;
		if (bLeft && bWires)
			pWiresLeft = new vtMesh(vtMesh::LINE_STRIP, 0, npoints*3);
		if (bRight && bWires)
			pWiresRight = new vtMesh(vtMesh::LINE_STRIP, 0, npoints*3);

		for (i = 0; i < npoints; i++)
		{
			FPoint3 base = p3[i] + FPoint3(0.0f, PostSize.y, 0.0f);
			if (i < npoints-1)
			{
				// determine side-pointing normal
				sideways = SidewaysVector(p3[i], p3[i+1]);
			}
			if (bLeft && bWires)
			{
				upward = -sideways + FPoint3(0,1,0);
				upward.SetLength(0.35);	// roughly 1 foot is standard
				pMesh->CreatePrism(base,
					upward, size1, size2);

				for (j = 0; j < 3; j++)
					pWiresLeft->SetVtxPos(j*npoints + i, base + upward * wire_height[j]);
			}
			if (bRight && bWires)
			{
				upward = sideways + FPoint3(0,1,0);
				upward.SetLength(0.35);	// roughly 1 foot is standard
				pMesh->CreatePrism(base, upward, size1, size2);

				for (j = 0; j < 3; j++)
					pWiresRight->SetVtxPos(j*npoints + i, base + upward * wire_height[j]);
			}
		}
		m_pFenceGeom->AddMesh(pMesh, s_mi_metal);
		pMesh->Release();	// pass ownership

		if (bLeft && bWires)
		{
			pWiresLeft->AddStrip2(npoints, 0);
			pWiresLeft->AddStrip2(npoints, npoints);
			pWiresLeft->AddStrip2(npoints, npoints*2);
			m_pFenceGeom->AddMesh(pWiresLeft, s_mi_wire);
			pWiresLeft->Release();	// pass ownership
		}
		if (bRight && bWires)
		{
			pWiresRight->AddStrip2(npoints, 0);
			pWiresRight->AddStrip2(npoints, npoints);
			pWiresRight->AddStrip2(npoints, npoints*2);
			m_pFenceGeom->AddMesh(pWiresRight, s_mi_wire);
			pWiresRight->Release();	// pass ownership
		}
	}

	// if not enough points, nothing connections to create
	if (npoints < 2)
		return;

	if (m_Params.m_ConnectType == "none")
	{
		// nothing to do
	}
	else if (m_Params.m_ConnectType == "wire")
	{
		// the 3 wires
		if (npoints > 1)
		{
			float wire_height[3] = { 0.42f, 0.66f, 0.91f };

			vtMesh *pWireMesh = new vtMesh(vtMesh::LINE_STRIP, 0, npoints);
			int vidx = 0;
			for (j = 0; j < 3; j++)
			{
				int start = vidx;
				for (i = 0; i < npoints; i++)
				{
					pWireMesh->AddVertex(p3[i] + FPoint3(0, (PostSize.y * wire_height[j]), 0));
					vidx++;
				}
				pWireMesh->AddStrip2(npoints, start);
			}
			m_pFenceGeom->AddMesh(pWireMesh, s_mi_wire);
			pWireMesh->Release();	// pass ownership
		}
	}
	else if (m_Params.m_fConnectWidth == 0.0f)
	{
		vtMesh *pMesh = new vtMesh(vtMesh::TRIANGLE_STRIP, VT_TexCoords, 100);

		// A single thin strip polygon with a single texture.
		vtMaterialDescriptor *desc = FindDescriptor(m_Params.m_ConnectType);
		FPoint2 uvscale = desc->GetUVScale();

		float u = 0.0f;
		float vertical_meters = m_Params.m_fConnectTop - m_Params.m_fConnectBottom;
		float v_top;
		if (uvscale.y == -1)
			v_top = 1.0f;
		else
			v_top = vertical_meters / uvscale.y;

		int vidx = 0;
		for (i = 0; i < npoints; i++)
		{
			pMesh->SetVtxPUV(vidx++, p3[i] + FPoint3(0, m_Params.m_fConnectBottom, 0), u, 0.0);
			pMesh->SetVtxPUV(vidx++, p3[i] + FPoint3(0, m_Params.m_fConnectTop, 0), u, v_top);

			if (i < npoints-1)
			{
				// increment u based on the length of each fence segment
				float length_meters = (p3[i+1] - p3[i]).Length();
				u += (length_meters / desc->GetUVScale().x);
			}
		}
		pMesh->AddStrip2(npoints * 2, 0);

		m_pFenceGeom->AddMesh(pMesh, desc->GetMaterialIndex());
		pMesh->Release();	// pass ownership
	}
	else if (m_Params.m_fConnectWidth > 0.0f)
	{
		vtMesh *pMesh = new vtMesh(vtMesh::TRIANGLE_STRIP, VT_TexCoords | VT_Normals, 100);

		// a solid block, with top/left/right sides, made of 3 strips
		vtMaterialDescriptor *desc = FindDescriptor(m_Params.m_ConnectType);
		FPoint2 uvscale = desc->GetUVScale();
		float vertical_meters = m_Params.m_fConnectTop - m_Params.m_fConnectBottom;

		float u = 0.0f;
		float v1, v2;
		for (int i = 0; i < 3; i++)
		{
			float y1, y2;
			float z1, z2;
			FPoint3 pos, sideways, normal;

			// determine v texture coordinate
			switch (i)
			{
			case 0:
				v1 = 0.0f;
				if (uvscale.y == -1)
					v2 = 1.0f;
				else
					v2 = vertical_meters / uvscale.y;
				break;
			case 1:
				v1 = 0.0f;
				if (uvscale.y == -1)
					v2 = 1.0f;
				else
					v2 = m_Params.m_fConnectWidth / uvscale.y;
				break;
			case 2:
				v2 = 0.0f;
				if (uvscale.y == -1)
					v1 = 1.0f;
				else
					v1 = vertical_meters / uvscale.y;
				break;
			}

			// determine Y and Z values
			switch (i)
			{
			case 0:
				y1 = m_Params.m_fConnectBottom;
				y2 = m_Params.m_fConnectTop;
				z1 = m_Params.m_fConnectWidth / 2;
				z2 = m_Params.m_fConnectWidth / 2;
				break;
			case 1:
				y1 = m_Params.m_fConnectTop;
				y2 = m_Params.m_fConnectTop;
				z1 = m_Params.m_fConnectWidth / 2;
				z2 = -m_Params.m_fConnectWidth / 2;
				break;
			case 2:
				y1 = m_Params.m_fConnectTop;
				y2 = m_Params.m_fConnectBottom;
				z1 = -m_Params.m_fConnectWidth / 2;
				z2 = -m_Params.m_fConnectWidth / 2;
				break;
			}

			int vidx;
			int start = pMesh->GetNumVertices();
			for (j = 0; j < npoints; j++)
			{
				if (j < npoints-1)
				{
					// determine normal (used for shading and thickness)
					sideways = SidewaysVector(p3[j], p3[j+1]);
					switch (i)
					{
					case 0: normal = sideways; break;
					case 1: normal.Set(0,1,0); break;	// up
					case 2: normal = -sideways; break;
					}
				}

				pos = p3[j];
				pos.y += y2;
				pos += (sideways * z2);
				vidx = pMesh->AddVertex(pos);
				pMesh->SetVtxTexCoord(vidx, FPoint2(u, v2));
				pMesh->SetVtxNormal(vidx, normal);

				pos = p3[j];
				pos.y += y1;
				pos += (sideways * z1);
				vidx = pMesh->AddVertex(pos);
				pMesh->SetVtxTexCoord(vidx, FPoint2(u, v1));
				pMesh->SetVtxNormal(vidx, normal);

				if (j < npoints-1)
				{
					// increment u based on the length of each fence segment
					float length_meters = (p3[j+1] - p3[j]).Length();
					u += (length_meters / desc->GetUVScale().x);
				}
			}
			pMesh->AddStrip2(npoints * 2, start);
		}

		// add cap at beginning
		u = m_Params.m_fConnectWidth / desc->GetUVScale().x;
		v2 = vertical_meters / uvscale.y;

		int start =
		pMesh->AddVertex(pMesh->GetVtxPos(npoints*2*2+1));
		pMesh->AddVertex(pMesh->GetVtxPos(npoints*2*2));
		pMesh->AddVertex(pMesh->GetVtxPos(0));
		pMesh->AddVertex(pMesh->GetVtxPos(1));
		pMesh->SetVtxNormal(start+0, p3[0] - p3[1]);
		pMesh->SetVtxNormal(start+1, p3[0] - p3[1]);
		pMesh->SetVtxNormal(start+2, p3[0] - p3[1]);
		pMesh->SetVtxNormal(start+3, p3[0] - p3[1]);
		pMesh->SetVtxTexCoord(start+0, FPoint2(u, 0.0f));
		pMesh->SetVtxTexCoord(start+1, FPoint2(u, v2));
		pMesh->SetVtxTexCoord(start+2, FPoint2(0.0f, 0.0f));
		pMesh->SetVtxTexCoord(start+3, FPoint2(0.0f, v2));
		pMesh->AddStrip2(4, start);

		// add cap at end
		start =
		pMesh->AddVertex(pMesh->GetVtxPos(npoints*2-2));
		pMesh->AddVertex(pMesh->GetVtxPos(npoints*2-1));
		pMesh->AddVertex(pMesh->GetVtxPos(npoints*3*2-1));
		pMesh->AddVertex(pMesh->GetVtxPos(npoints*3*2-2));
		pMesh->SetVtxNormal(start+0, p3[npoints-1] - p3[npoints-2]);
		pMesh->SetVtxNormal(start+1, p3[npoints-1] - p3[npoints-2]);
		pMesh->SetVtxNormal(start+2, p3[npoints-1] - p3[npoints-2]);
		pMesh->SetVtxNormal(start+3, p3[npoints-1] - p3[npoints-2]);
		pMesh->SetVtxTexCoord(start+0, FPoint2(0.0f, 0.0f));
		pMesh->SetVtxTexCoord(start+1, FPoint2(0.0f, v2));
		pMesh->SetVtxTexCoord(start+2, FPoint2(u, 0.0f));
		pMesh->SetVtxTexCoord(start+3, FPoint2(u, v2));
		pMesh->AddStrip2(4, start);

		m_pFenceGeom->AddMesh(pMesh, desc->GetMaterialIndex());
		pMesh->Release();	// pass ownership
	}
}

void vtFence3d::DestroyGeometry()
{
	if (m_pFenceGeom)
	{
		// Destroy the meshes so they can be re-made
		while (m_pFenceGeom->GetNumMeshes())
		{
			vtMesh *pMesh = m_pFenceGeom->GetMesh(0);
			m_pFenceGeom->RemoveMesh(pMesh);
		}
		m_pHighlightMesh = NULL;
	}
	m_bBuilt = false;
}

/////////////////////////////////////
// Implement vtStructure3d methods

/**
 * Build (or rebuild) the geometry for a fence.
 */
bool vtFence3d::CreateNode(vtTerrain *pTerr)
{
	bool bHighlighted = (m_pHighlightMesh != NULL);
	if (m_bBuilt)
	{
		// was build before; destroy meshes in order to re-build
		DestroyGeometry();
	}
	else
	{
		static bool bFirstTime = true;
		if (bFirstTime == true)
		{
			bFirstTime = false;
			CreateMaterials();
		}

		m_pFenceGeom = new vtGeom;
		m_pFenceGeom->SetName2("Fence");
		m_pFenceGeom->SetMaterials(s_FenceMats.GetMatArray());

		if (bFirstTime)
			s_FenceMats.GetMatArray()->Release();
	}

	// create surface and shape
	AddFenceMeshes(pTerr->GetHeightField());

	if (bHighlighted)
		ShowBounds(true);

	m_bBuilt = true;
	return true;
}

void vtFence3d::DeleteNode()
{
	DestroyGeometry();
	m_pFenceGeom->Release();
	m_pFenceGeom = NULL;
}

void vtFence3d::ShowBounds(bool bShow)
{
	if (m_pHighlightMesh)
	{
		// remove previous
		m_pFenceGeom->RemoveMesh(m_pHighlightMesh);
		m_pHighlightMesh = NULL;
	}
	if (bShow)
	{
		// Simple bounding sphere
//		FSphere sphere;
//		m_pFenceGeom->GetBoundSphere(sphere);
//		m_pHighlightMesh = CreateSphereMesh(sphere);

		// border around the feature
		unsigned int i, npoints = m_pFencePts.GetSize();
		m_pHighlightMesh = new vtMesh(vtMesh::LINE_STRIP, 0, npoints*2);
		FPoint3 sideways;
		FPoint3 up(0,1,0);
		for (i = 0; i < npoints; i++)
		{
			if (i < npoints-1)
			{
				// determine normal
				sideways = SidewaysVector(m_Posts3d[i], m_Posts3d[i+1]);
				sideways.SetLength(1.0f + m_Params.m_fConnectWidth);
			}
			m_pHighlightMesh->AddVertex(m_Posts3d[i] + sideways + up);
			m_pHighlightMesh->AddVertex(m_Posts3d[i] - sideways + up);
		}
		std::vector<unsigned short> idx;
		for (i = 0; i < npoints; i++) idx.push_back(i*2);
		for (i = 0; i < npoints; i++) idx.push_back((npoints*2)-1 - i*2);
		idx.push_back(0);
		m_pHighlightMesh->AddStrip(idx.size(), &idx.front());

		// Also some lines as handles for the control points
		float height = max(m_Params.m_fPostHeight, m_Params.m_fConnectTop);
		height += 1.0f;
		for (i = 0; i < npoints; i++)
		{
			int v0 = m_pHighlightMesh->AddVertex(m_Posts3d[i]);
			int v1 = m_pHighlightMesh->AddVertex(m_Posts3d[i] + FPoint3(0,height,0));
			m_pHighlightMesh->AddLine(v0, v1);
		}
		m_pFenceGeom->AddMesh(m_pHighlightMesh, s_mi_hightlight);
		m_pHighlightMesh->Release();	// pass ownership
	}
}


