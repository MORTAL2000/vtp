//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "vtlib/vtlib.h"

void makeVec4(osg::Vec4 &col, float r, float g, float b)
{
	col.set(r, g, b, 1.0f);
}

void makeVec4(osg::Vec4 &col, float r, float g, float b, float a)
{
	col.set(r, g, b, a);
}

///////////////////////////////////

#define FAB		osg::Material::FRONT_AND_BACK
#define GEO_ON	osg::StateAttribute::ON
#define GEO_OFF	osg::StateAttribute::OFF

vtMaterial::vtMaterial() : vtMaterialBase()
{
	m_pStateSet = new osg::StateSet;
	m_pMaterial = new osg::Material;
	m_pStateSet->setAttributeAndModes(m_pMaterial.get());

	// Not sure why this is required (should be the default!)
	m_pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}

void vtMaterial::SetDiffuse(float r, float g, float b, float a)
{
	m_pMaterial->setDiffuse(FAB, osg::Vec4(r, g, b, a));

	if (a < 1.0f)
		m_pStateSet->setMode(GL_BLEND, GEO_ON);
}
RGBAf vtMaterial::GetDiffuse()
{
	osg::Vec4 col = m_pMaterial->getDiffuse(FAB);
	return RGBAf(col[0], col[1], col[2], col[3]);
}

void vtMaterial::SetSpecular(float r, float g, float b)
{
	m_pMaterial->setSpecular(FAB, osg::Vec4(r, g, b, 1.0f));
}
RGBf vtMaterial::GetSpecular()
{
	osg::Vec4 col = m_pMaterial->getSpecular(FAB);
	return RGBf(col[0], col[1], col[2]);
}

void vtMaterial::SetAmbient(float r, float g, float b)
{
	m_pMaterial->setAmbient(FAB, osg::Vec4(r, g, b, 1.0f));
}
RGBf vtMaterial::GetAmbient()
{
	osg::Vec4 col = m_pMaterial->getAmbient(FAB);
	return RGBf(col[0], col[1], col[2]);
}

void vtMaterial::SetEmission(float r, float g, float b)
{
	m_pMaterial->setEmission(FAB, osg::Vec4(r, g, b, 1.0f));
}
RGBf vtMaterial::GetEmission()
{
	osg::Vec4 col = m_pMaterial->getEmission(FAB);
	return RGBf(col[0], col[1], col[2]);
}

void vtMaterial::SetCulling(bool bCulling)
{
	m_pStateSet->setMode(GL_CULL_FACE, bCulling ? GEO_ON : GEO_OFF);
}
bool vtMaterial::GetCulling()
{
	osg::StateAttribute::GLModeValue m = m_pStateSet->getMode(osg::StateAttribute::CULLFACE);
	return (m == GEO_ON);
}
void vtMaterial::SetLighting(bool bLighting)
{
	m_pStateSet->setMode(GL_LIGHTING, bLighting ? GEO_ON : GEO_OFF);
}
bool vtMaterial::GetLighting()
{
	osg::StateAttribute::GLModeValue m = m_pStateSet->getMode(osg::StateAttribute::LIGHTING);
	return (m == GEO_ON);
}

void vtMaterial::SetTransparent(bool bOn, bool bAdd)
{
	m_pStateSet->setMode(GL_BLEND, bOn ? GEO_ON : GEO_OFF);
	if (bAdd)
	{
		osg::Transparency *trans = new osg::Transparency();
//		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
//		trans->setFunction(GL_ONE, GL_ONE);
		trans->setFunction(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
//		trans->setFunction(GL_SRC_COLOR, GL_DST_COLOR);
		m_pStateSet->setAttribute(trans);
	}
}
bool vtMaterial::GetTransparent()
{
	osg::StateAttribute::GLModeValue m = m_pStateSet->getMode(osg::StateAttribute::TRANSPARENCY);
	return (m == GEO_ON);
}

void vtMaterial::SetTexture(vtImage *pImage)
{
	if (!m_pTexture)
		m_pTexture = new osg::Texture();

	m_pTexture->setImage(pImage->m_pOsgImage);

//	m_pStateSet->setMode(GL_TEXTURE, GEO_ON);
//	m_pStateSet->setAttribute(m_pTexture.get());
	m_pStateSet->setAttributeAndModes(m_pTexture.get(), osg::StateAttribute::ON);
}
vtImage *vtMaterial::GetTexture()
{
//	return m_pImage;
	return NULL;	// todo
}

void vtMaterial::SetClamp(bool bClamp)
{
	if (!m_pTexture)
		return;
	if (bClamp)
	{
		m_pTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP);
		m_pTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	}
	else
	{
		m_pTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
		m_pTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	}
}

bool vtMaterial::GetClamp()
{
	if (!m_pTexture)
		return false;
	osg::Texture::WrapMode w = m_pTexture->getWrap(osg::Texture::WRAP_S);
	return (w == osg::Texture::CLAMP);
}

void vtMaterial::SetMipMap(bool bMipMap)
{
	if (!m_pTexture)
		return;
	if (bMipMap)
		m_pTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	else
		m_pTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
}

bool vtMaterial::GetMipMap()
{
	if (!m_pTexture)
		return false;
	osg::Texture::FilterMode m = m_pTexture->getFilter(osg::Texture::MIN_FILTER);
	return (m == osg::Texture::LINEAR_MIPMAP_LINEAR);
}

extern osg::State *hack_global_state;

void vtMaterial::Apply()
{
	if (hack_global_state)
		hack_global_state->apply(m_pStateSet.get());
}


//////////////////////////////////////////////////////////////

int vtMaterialArray::AppendMaterial(vtMaterial *pMat)
{
	// nothing special to do
	return Append(pMat);
}


//////////////////////////////////////////////////////////////

vtMesh::vtMesh(GLenum PrimType, int VertType, int NumVertices) :
	vtMeshBase(PrimType, VertType, NumVertices)
{
	m_pGeoSet = new GeoSet2();

	// TEMPORARY FOR TESTING!
//	m_pGeoSet->setUseDisplayList(false);

	m_Vert.SetMaxSize(NumVertices);
	m_pGeoSet->setCoords(m_Vert.GetData(), m_Index.GetData());
	m_pGeoSet->setPrimLengths(m_PrimLen.GetData());

	// set backpointer so we can find ourselves later
	m_pGeoSet->m_pMesh = this;

	if (VertType & VT_Normals)
	{
		m_Norm.SetMaxSize(NumVertices);
		m_pGeoSet->setNormals(m_Norm.GetData(), m_Index.GetData());
		m_pGeoSet->setNormalBinding(osg::GeoSet::BIND_PERVERTEX);
	}
	if (VertType & VT_Colors)
	{
		m_Color.SetMaxSize(NumVertices);
		m_pGeoSet->setColors(m_Color.GetData(), m_Index.GetData());
		m_pGeoSet->setColorBinding(osg::GeoSet::BIND_PERVERTEX);
	}
	if (VertType & VT_TexCoords)
	{
		m_Tex.SetMaxSize(NumVertices);
		m_pGeoSet->setTextureCoords(m_Tex.GetData(), m_Index.GetData());
		m_pGeoSet->setTextureBinding(osg::GeoSet::BIND_PERVERTEX);
	}

	switch (PrimType)
	{
	case GL_POINTS:
		m_pGeoSet->setPrimType(osg::GeoSet::POINTS);
		m_pGeoSet->setNumPrims(NumVertices);
		break;
	case GL_LINES:
		m_pGeoSet->setPrimType(osg::GeoSet::LINES);
		m_pGeoSet->setNumPrims(NumVertices/2);
		break;
	case GL_TRIANGLES:
		m_pGeoSet->setPrimType(osg::GeoSet::TRIANGLES);
		m_pGeoSet->setNumPrims(NumVertices/3);
		break;
	case GL_LINE_STRIP:
		m_pGeoSet->setPrimType(osg::GeoSet::LINE_STRIP);
		break;
	case GL_TRIANGLE_STRIP:
		m_pGeoSet->setPrimType(osg::GeoSet::TRIANGLE_STRIP);
		break;
	case GL_QUADS:
		m_pGeoSet->setPrimType(osg::GeoSet::QUADS);
		break;
	case GL_TRIANGLE_FAN:
		m_pGeoSet->setPrimType(osg::GeoSet::TRIANGLE_FAN);
		break;
	case GL_POLYGON:
		m_pGeoSet->setPrimType(osg::GeoSet::POLYGON);
		break;
	}
}

void vtMesh::SendPointersToOSG()
{
	// in case they got reallocated, tell OSG again
	m_pGeoSet->setCoords(m_Vert.GetData(), m_Index.GetData());
	m_pGeoSet->setPrimLengths(m_PrimLen.GetData());

	if (m_iVtxType & VT_Normals)
		m_pGeoSet->setNormals(m_Norm.GetData(), m_Index.GetData());
	if (m_iVtxType & VT_Colors)
		m_pGeoSet->setColors(m_Color.GetData(), m_Index.GetData());
	if (m_iVtxType & VT_TexCoords)
		m_pGeoSet->setTextureCoords(m_Tex.GetData(), m_Index.GetData());
}

void vtMesh::AddTri(int p0, int p1, int p2)
{
	m_Index.Append(p0);
	m_Index.Append(p1);
	m_Index.Append(p2);
	m_PrimLen.Append(3);
//	m_pGeoSet->setNumPrims(m_pGeoSet->getNumPrims() + 1);
	m_pGeoSet->setNumPrims(m_Index.GetSize() / 3);

	SendPointersToOSG();
}

void vtMesh::AddFan(int p0, int p1, int p2, int p3, int p4, int p5)
{
	int len = 3;

	m_Index.Append(p0);
	m_Index.Append(p1);
	m_Index.Append(p2);

	if (p3 != -1) { m_Index.Append(p3); len = 4; }
	if (p4 != -1) { m_Index.Append(p4); len = 5; }
	if (p5 != -1) { m_Index.Append(p5); len = 6; }

	m_PrimLen.Append(len);
	m_pGeoSet->setNumPrims(m_pGeoSet->getNumPrims() + 1);

	SendPointersToOSG();
}

void vtMesh::AddFan(int *idx, int iNVerts)
{
	for (int i = 0; i < iNVerts; i++)
		m_Index.Append(idx[i]);

	m_PrimLen.Append(iNVerts);
	m_pGeoSet->setNumPrims(m_pGeoSet->getNumPrims() + 1);

	SendPointersToOSG();
}

void vtMesh::AddStrip(int iNVerts, unsigned short *pIndices)
{
	for (int i = 0; i < iNVerts; i++)
		m_Index.Append(pIndices[i]);

	m_PrimLen.Append(iNVerts);
	m_pGeoSet->setNumPrims(m_pGeoSet->getNumPrims() + 1);

	SendPointersToOSG();
}

void vtMesh::AddQuadStrip(int iNVerts, int iStartIndex)
{
	// for OSG, stored the same
	AddStrip2(iNVerts, iStartIndex);
}

void vtMesh::AddLine(int p0, int p1)
{
	m_Index.Append(p0);
	m_Index.Append(p1);

	SendPointersToOSG();
}

void vtMesh::SetVtxPos(int i, const FPoint3 &p)
{
	osg::Vec3 s;
	v2s(p, s);
	m_Vert.SetAt(i, s);
}

FPoint3 vtMesh::GetVtxPos(int i)
{
	FPoint3 p;
	s2v( m_Vert.GetAt(i), p);
	return p;
}

void vtMesh::SetVtxNormal(int i, const FPoint3 &p)
{
	osg::Vec3 s;
	v2s(p, s);
	m_Norm.SetAt(i, s);
}

FPoint3 vtMesh::GetVtxNormal(int i)
{
	FPoint3 p;
	s2v( m_Norm.GetAt(i), p);
	return p;
}

void vtMesh::SetVtxColor(int i, const RGBf &p)
{
	osg::Vec4 s;
	v2s(p, s);
	m_Color.SetAt(i, s);
}

RGBf vtMesh::GetVtxColor(int i)
{
	RGBf p;
	s2v( m_Color.GetAt(i), p);
	return p;
}

void vtMesh::SetVtxTexCoord(int i, const FPoint2 &p)
{
	osg::Vec2 s;
	v2s(p, s);
	m_Tex.SetAt(i, s);
}

FPoint2 vtMesh::GetVtxTexCoord(int i)
{
	FPoint2 p;
	s2v( m_Tex.GetAt(i), p);
	return p;
}

int vtMesh::GetNumPrims()
{
	return m_pGeoSet->getNumPrims();
}

void vtMesh::ReOptimize()
{
	m_pGeoSet->dirtyDisplayList();
}

void vtMesh::AllowOptimize(bool bAllow)
{
	m_pGeoSet->setUseDisplayList(bAllow);
}


