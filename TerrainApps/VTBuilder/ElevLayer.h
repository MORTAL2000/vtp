//
// ElevLayer.h
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef ELEVLAYER_H
#define ELEVLAYER_H

#include "wx/image.h"
#include "Layer.h"
#include "vtdata/vtTin.h"

class vtElevationGrid;
class vtDIB;

class vtTin2d : public vtTin
{
public:
	void DrawTin(wxDC* pDC, vtScaledView *pView);
};

//////////////////////////////////////////////////////////

class vtElevLayer : public vtLayer 
{
public:
	vtElevLayer();
	vtElevLayer(const DRECT &area, int iColumns, int iRows,
		bool bFloats, float fScale, vtProjection proj);
	virtual ~vtElevLayer();

	// overrides
	bool GetExtent(DRECT &rect);
	void DrawLayer(wxDC* pDC, vtScaledView *pView);
	bool ConvertProjection(vtProjection &proj);
	bool OnSave();
	bool OnLoad();
	void GetProjection(vtProjection &proj);
	void SetProjection(vtProjection &proj);
	void GetPropertyText(wxString &str);
	char *vtElevLayer::GetFileExtension();

	void DrawLayerBitmap(wxDC* pDC, vtScaledView *pView);
	void DrawLayerOutline(wxDC* pDC, vtScaledView *pView);
	bool AppendDataFrom(vtLayer *pL);
	void ReRender() { m_bBitmapRendered = false; }
	void ReImage();
	bool IsGrid() { return m_pGrid != NULL; }

	void SetupDefaults();

	// heightfield operations
	void Offset(const DPoint2 &p);
	float GetElevation(DPoint2 &p);
	bool ImportFromFile(wxString &strFileName, void progress_callback(int am));

	// grid operations
	void Resample(int iNewWidth, int iNewHeight);
	void FillGaps();
	void DetermineMeterSpacing();

	// TIN operations
	void SetTin(vtTin2d *pTin);
	void MergeSharedVerts(bool bSilent = false);

	// drawing
	void PaintDibFromElevation(vtDIB *dib, bool bShade);
	void GenerateShadedColor(int i, int j, int &r, int &g, int &b);
	void GenerateColorFromGrid1(int i, int j, int &r, int &g, int &b);
	void GenerateColorFromGrid2(int i, int j, int &r, int &g, int &b);
	void ShadePixel(int i, int j, int &r, int &g, int &b, int bias);
	void SetupBitmap(wxDC* pDC);
	void RenderBitmap();

	static bool	m_bShowElevation;
	static bool	m_bShading;
	static bool m_bDoMask;

	vtElevationGrid	*m_pGrid;
	vtTin2d *m_pTin;

protected:
	bool	m_bHasBitmap;
	bool	m_bBitmapRendered;
	bool	m_bHasMask;
	float	m_fSpacing;

	int m_iRows, m_iColumns;

	wxBitmap	*m_pBitmap;
	wxMask		*m_pMask;
	wxImage		*m_pImage;
};

#endif
