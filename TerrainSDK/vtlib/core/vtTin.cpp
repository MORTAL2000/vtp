//
// vtTin.cpp
//
// Class which represents a Triangular Irregular Network.
//
// Copyright (c) 2002 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"
#include "vtTin.h"

void vtTin::Read(const char *fname)
{
#if 1
	FILE *fp = fopen(fname, "rb");
	if (!fp)
		return;

	int num;
	FPoint3 f;

	fread(&num, 1, sizeof(int), fp);
	m_points.SetMaxSize(num);
	for (int i = 0; i < num; i++)
	{
		fread(&f.x, 3, sizeof(float), fp);

		m_points.Append(f);
	}
	fclose(fp);

	// now try to read projection from corresponding .prj file
	char prj_name[256];
	strcpy(prj_name, fname);
	strcpy(prj_name + strlen(prj_name) - 4, ".prj");
	FILE *fp2 = fopen(prj_name, "rb");
	if (!fp2)
		return;
	char wkt_buf[2000], *wkt = wkt_buf;
	fgets(wkt, 2000, fp2);
	OGRErr err = m_proj.importFromWkt((char **) &wkt);
	if (err != OGRERR_NONE)
		return;
	fclose(fp2);
#else
	m_points.SetMaxSize(3);
//	m_points.Append(FPoint3(0,0,0));
//	m_points.Append(FPoint3(10,0,0));
//	m_points.Append(FPoint3(0,10,0));
	m_points.Append(FPoint3(-5,-5,0));
	m_points.Append(FPoint3(5,-5,0));
	m_points.Append(FPoint3(-5,5,0));
#endif

	ComputeExtents();
	Initialize(this);
}

FPoint3 ComputeNormal(const FPoint3 &p1, const FPoint3 &p2, const FPoint3 &p3)
{
	FPoint3 d1 = (p2 - p1);
	FPoint3 d2 = (p3 - p1);
	FPoint3 cross = d1.Cross(d2);
	cross.Normalize();
	return cross;
}


#define MAX_CHUNK_VERTS	30000

vtGeom *vtTin::CreateGeometry(bool bDropShadowMesh)
{
	// set up materials
	vtMaterialArray *pMats = new vtMaterialArray();
	bool lighting = false;
	pMats->AddRGBMaterial1(RGBf(1, 1, 1), false, lighting, false);
	pMats->AddRGBMaterial1(RGBf(0.5f, 0.5f, 0.5f), false, false, false);
	pMats->AddRGBMaterial1(RGBf(0, 0, 0), false, false, false);

	m_pGeom = new vtGeom();
	m_pGeom->SetMaterials(pMats);

	int i, j, remaining;
	int points = m_points.GetSize();

	// Break it up into a series of meshes - this is good for both
	// culling and memory management

	FPoint3 ep, wp;		// earth point, world point
	FPoint3 p[3], norm;
	FPoint3 light_dir(1, 1, 0);
	RGBf color;
	float r, g=1.0f, b=0.5f;

	int base = 0;
	remaining = points;
	while (remaining)
	{
		int chunk = remaining;
		if (chunk > MAX_CHUNK_VERTS)
			chunk = MAX_CHUNK_VERTS;
		int tris = chunk / 3;

		vtMesh *pMesh = new vtMesh(GL_TRIANGLES, VT_Normals|VT_Colors, chunk);

		for (i = 0; i < tris; i++)
		{
			for (j = 0; j < 3; j++)
				m_Conversion.ConvertFromEarth(m_points[base + (i*3+j)], p[j]);
			norm = ComputeNormal(p[0], p[1], p[2]);

			float shade = norm.Dot(light_dir);	// shading 0 (dark) to 1 (light)

			for (j = 0; j < 3; j++)
			{
				r = (m_points[i*3+j].z - m_fMinHeight) / (m_fMaxHeight - m_fMinHeight);
				pMesh->AddVertex(p[j]);
				pMesh->SetVtxNormal(i*3+j, norm);

				color.Set(r, g, b);
				color *= shade;
				pMesh->SetVtxColor(i*3+j, color);
			}
		}
		m_pGeom->AddMesh(pMesh, 0);
		m_Meshes.Append(pMesh);

		if (bDropShadowMesh)
		{
			vtMesh *pShadowMesh = new vtMesh(GL_TRIANGLES, 0, chunk);
			for (i = 0; i < chunk; i++)
			{
				ep = m_points[base+i];
				ep.z = m_fMinHeight - 4.9;
				m_Conversion.ConvertFromEarth(ep, wp);
				pShadowMesh->AddVertex(wp);
			}
			m_pGeom->AddMesh(pShadowMesh, 2);
		}

		remaining -= chunk;
		base += chunk;
	}

	if (bDropShadowMesh)
	{
		vtMesh *pBaseMesh = new vtMesh(GL_TRIANGLE_FAN, 0, 4);

		ep.Set(m_EarthExtents.left - 10, m_EarthExtents.bottom - 10, m_fMinHeight - 5);
		m_Conversion.ConvertFromEarth(ep, wp);
		pBaseMesh->AddVertex(wp);

		ep.Set(m_EarthExtents.right + 10, m_EarthExtents.bottom - 10, m_fMinHeight - 5);
		m_Conversion.ConvertFromEarth(ep, wp);
		pBaseMesh->AddVertex(wp);

		ep.Set(m_EarthExtents.right + 10, m_EarthExtents.top + 10, m_fMinHeight - 5);
		m_Conversion.ConvertFromEarth(ep, wp);
		pBaseMesh->AddVertex(wp);

		ep.Set(m_EarthExtents.left - 10, m_EarthExtents.top + 10, m_fMinHeight - 5);
		m_Conversion.ConvertFromEarth(ep, wp);
		pBaseMesh->AddVertex(wp);

		pBaseMesh->AddFan(0, 1, 2, 3);
		m_pGeom->AddMesh(pBaseMesh, 1);
	}
	return m_pGeom;
}

void vtTin::Write(const char *fname)
{
}

void vtTin::ComputeExtents()
{
	m_EarthExtents.SetRect(1E9, -1E9, -1E9, 1E9);

	m_fMinHeight = 1E9;
	m_fMaxHeight = -1E9;

	int size = m_points.GetSize();
	for (int j = 0; j < size; j++)
	{
		DPoint2 p(m_points[j].x, m_points[j].y);
		m_EarthExtents.GrowToContainPoint(p);

		float z = m_points[j].z;
		if (z > m_fMaxHeight) m_fMaxHeight = z;
		if (z < m_fMinHeight) m_fMinHeight = z;
	}
}

bool vtTin::FindAltitudeAtPoint(const FPoint3 &input, float &fAltitude, FPoint3 *vNormal)
{
	// First try to identify which triangle
	FPoint2 p(input.x, input.z);

	FPoint3 wp1, wp2, wp3;
	FPoint2 p1, p2, p3;
	bool good;

	for (int m = 0; m < m_Meshes.GetSize(); m++)
	{
		vtMesh *mesh = m_Meshes[m];
		int tris = mesh->GetNumVertices() / 3;
		for (int i = 0; i < tris; i++)
		{
			// get world points
			wp1 = mesh->GetVtxPos(i*3+0);
			wp2 = mesh->GetVtxPos(i*3+1);
			wp3 = mesh->GetVtxPos(i*3+2);
			// convert to 2d
			p1.Set(wp1.x, wp1.z);
			p2.Set(wp2.x, wp2.z);
			p3.Set(wp3.x, wp3.z);

			if (!PointInTriangle(p, p1, p2, p3))
				continue;

			// compute barycentric coordinates with respect to the triangle
			float bary[3], val;
			good = BarycentricCoords(p1, p2, p3, p, bary);
			if (!good)
				continue;

			// compute barycentric combination of function values at vertices
			val = bary[0]*wp1.y +
				  bary[1]*wp2.y +
				  bary[2]*wp3.y;
			fAltitude = val;
			return true;
		}
	}
	return false;
}


/*
 * Algorithm from 'Fast, Minimum Storage Ray-Triangle Intersection',
 * Thomas M�ller and Ben Trumbore, 1997
 * Adapted to use C++ and the vtdata math classes.
 */
#define EPSILON 0.000001
bool intersect_triangle(const FPoint3 &orig, const FPoint3 &dir,
			const FPoint3 &vert0, const FPoint3 &vert1, const FPoint3 &vert2,
			float &t, float &u, float &v)
{
	FPoint3 edge1, edge2, tvec, pvec, qvec;
	float det,inv_det;

	/* find vectors for two edges sharing vert0 */
	edge1 = vert1 - vert0;
	edge2 = vert2 - vert0;

	/* begin calculating determinant - also used to calculate U parameter */
	pvec = dir.Cross(edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = edge1.Dot(pvec);

	if (det < EPSILON)
		return false;

	/* calculate distance from vert0 to ray origin */
	tvec = orig - vert0;

	/* calculate U parameter and test bounds */
	u = tvec.Dot(pvec);
	if (u < 0.0 || u > det)
		return false;

	/* prepare to test V parameter */
	qvec = tvec.Cross(edge1);

	 /* calculate V parameter and test bounds */
	v = dir.Dot(qvec);
	if (v < 0.0 || u + v > det)
		return false;

	/* calculate t, scale parameters, ray intersects triangle */
	t = edge2.Dot(qvec);
	inv_det = 1.0 / det;
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;

	return true;
}

bool vtTin::CastRayToSurface(const FPoint3 &point, const FPoint3 &dir, FPoint3 &result)
{
	FPoint3 wp1, wp2, wp3;
	float i, t, u, v, closest = 1E9;

	for (int m = 0; m < m_Meshes.GetSize(); m++)
	{
		vtMesh *mesh = m_Meshes[m];
		int tris = mesh->GetNumVertices() / 3;
		for (i = 0; i < tris; i++)
		{
			// get world points
			wp1 = mesh->GetVtxPos(i*3+0);
			wp2 = mesh->GetVtxPos(i*3+1);
			wp3 = mesh->GetVtxPos(i*3+2);
			if (intersect_triangle(point, dir, wp1, wp2, wp3, t, u, v))
			{
				if (t < closest)
					closest = t;
			}
		}
	}
	if (closest == 1E9)
		return false;

	result = point + (dir * closest);
	return true;
}

FPoint3 vtTin::FindVectorToClosestVertex(const FPoint3 &pos)
{
	FPoint3 vert, diff, closest_diff;
	float len, minlen = 1E9;

	for (int m = 0; m < m_Meshes.GetSize(); m++)
	{
		vtMesh *mesh = m_Meshes[m];
		int points = mesh->GetNumVertices();
		for (int i = 0; i < points; i++)
		{
			vert = mesh->GetVtxPos(i);
			diff = vert - pos;
			len = diff.Length();
			if (len < minlen)
			{
				minlen = len;
				closest_diff = diff;
			}
		}
	}
	return closest_diff;
}

