//
// ElevLayer.h
//
// Copyright (c) 2001-2003 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef ELEVLAYER_H
#define ELEVLAYER_H

#include "wx/image.h"
#include "Layer.h"
#include "vtdata/vtTin.h"

#define SHADING_BIAS	200

class vtHeightField;
class vtElevationGrid;
class vtDIB;
class vtBitmap;

class vtTin2d : public vtTin
{
public:
	vtTin2d();

	void DrawTin(wxDC* pDC, vtScaledView *pView);
	void ComputeEdgeLengths();
	void CullLongEdgeTris();
	void FreeEdgeLengths();
	void SetConstraint(bool bConstrain, double fMaxEdge);

	double *m_fEdgeLen;
	bool m_bConstrain;
	double m_fMaxEdge;
};

//////////////////////////////////////////////////////////

class ElevDrawOptions
{
public:
	ElevDrawOptions()
	{
		m_bShowElevation = true;
		m_bShading = true;
		m_bCastShadows = false;
		m_bDoMask = true;
		m_iCastAngle = 30;
		m_iCastDirection = 90;
	}
	bool operator != (const ElevDrawOptions &val)
	{
		return (m_bShowElevation != val.m_bShowElevation ||
			m_bShading != val.m_bShading ||
			m_bCastShadows != val.m_bCastShadows ||
			m_bDoMask != val.m_bDoMask ||
			m_iCastAngle != val.m_iCastAngle ||
			m_iCastDirection != val.m_iCastDirection);
	}
	bool m_bShowElevation;
	bool m_bShading;
	bool m_bCastShadows;
	bool m_bDoMask;
	int m_iCastAngle;
	int m_iCastDirection;
};

//////////////////////////////////////////////////////////

class vtElevLayer : public vtLayer 
{
public:
	vtElevLayer();
	vtElevLayer(const DRECT &area, int iColumns, int iRows,
		bool bFloats, float fScale, const vtProjection &proj);
	virtual ~vtElevLayer();

	// overrides
	bool GetExtent(DRECT &rect);
	void DrawLayer(wxDC* pDC, vtScaledView *pView);
	bool TransformCoords(vtProjection &proj);
	bool OnSave();
	bool OnLoad();
	void GetProjection(vtProjection &proj);
	void SetProjection(const vtProjection &proj);
	void GetPropertyText(wxString &str);
	wxString GetFileExtension();
	bool AskForSaveFilename();

	void DrawLayerBitmap(wxDC* pDC, vtScaledView *pView);
	void DrawLayerOutline(wxDC* pDC, vtScaledView *pView);
	bool AppendDataFrom(vtLayer *pL);
	void ReRender() { m_bBitmapRendered = false; }
	void ReImage();
	bool IsGrid() { return m_pGrid != NULL; }

	void SetupDefaults();

	// heightfield operations
	vtHeightField *GetHeightField();
	void Offset(const DPoint2 &p);
	float GetElevation(DPoint2 &p);
	bool ImportFromFile(const wxString2 &strFileName, void progress_callback(int am));

	// grid operations
	void Resample(int iNewWidth, int iNewHeight);
	bool FillGaps();
	void DetermineMeterSpacing();

	// TIN operations
	void SetTin(vtTin2d *pTin);
	vtTin2d *GetTin() { return m_pTin; }
	void MergeSharedVerts(bool bSilent = false);

	// drawing
	void SetupBitmap(wxDC* pDC);
	void RenderBitmap();
	void SetupDefaultColors(ColorMap &cmap);

	static ElevDrawOptions m_draw;

	vtElevationGrid	*m_pGrid;
	vtTin2d *m_pTin;

	bool NeedsDraw();

protected:
	bool	m_bNeedsDraw;
	bool	m_bBitmapRendered;
	bool	m_bHasMask;
	float	m_fSpacing;
	bool	m_bPreferGZip;	// user wants their elevation treated as a .gz file

	int m_iColumns, m_iRows;
	int m_iImageWidth, m_iImageHeight;

	vtBitmap	*m_pBitmap;
	wxMask		*m_pMask;
};

// Helper
FPoint3 LightDirection(float angle, float direction);

#endif	// ELEVLAYER_H

