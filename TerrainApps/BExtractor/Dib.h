////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See dib.cpp

#ifndef _INC_VFW
#pragma message ("NOTE: You can speed compilation by including <vfw.h> in stdafx.h")
#include <vfw.h>
#endif

class GDALRasterBand;
class CGBM;

// global functions for ordinary CBitmap too
//
extern CSize GetBitmapSize(CBitmap* pBitmap);
extern BOOL  DrawBitmap(CDC& dc, CBitmap* pBitmap,
	const CRect* rcDst=NULL, const CRect* rcSrc=NULL);

////////////////
// CDib implements Device Independent Bitmaps as a form of CBitmap. 
//
class CDib : public CBitmap {
protected:
	DECLARE_DYNAMIC(CDib)
	BITMAP	m_bm;		// stored for speed
	CPalette m_pal;		// palette
	HDRAWDIB m_hdd;		// for DrawDib	
	void *m_data;

	BITMAPINFOHEADER *m_bmi;
	RGBQUAD *m_colors;
	int m_stride;

public:
	CDib();
	CDib(CDC* pDC, CGBM *pGBM, HDRAWDIB hdd);
	CDib(CDC* pDC, CSize &size, HDRAWDIB hdd);
	CDib(CDC* pDC, GDALRasterBand *poBand, HDRAWDIB hdd);
	~CDib();

	CSize	GetSize() { return CSize(m_bm.bmWidth, m_bm.bmHeight); }
	BOOL Attach(HGDIOBJ hbm);
	BOOL Load(LPCTSTR szPathName);
	BOOL Load(HINSTANCE hInst, LPCTSTR lpResourceName);
	BOOL Load(HINSTANCE hInst, UINT uID)
		{ return Load(hInst, MAKEINTRESOURCE(uID)); }

	// Universal Draw function can use DrawDib or not.
	BOOL Draw(CDC& dc, const CRect* rcDst=NULL, const CRect* rcSrc=NULL,
		BOOL bUseDrawDib=TRUE, CPalette* pPal=NULL, BOOL bForeground=FALSE);

	void GetDIBFromSection();
	BOOL DeleteObject();
	BOOL CreatePalette(CPalette& pal);
	CPalette* GetPalette()  { return &m_pal; }

	UINT GetColorTable(RGBQUAD* colorTab, UINT nColors);

	void	GetPixel24(int x, int y, RGBQUAD &rgb);
	byte	GetPixel8(int x, int y);
	void	SetPixel8(int x, int y, byte val);
	int		GetWidth() { return m_bm.bmWidth; }
	int		GetHeight() { return m_bm.bmHeight; }
	BITMAPINFOHEADER *GetDIBHeader() { return m_bmi; }
	char	*GetData() { return (char *) m_data; }
};

CDib *CreateMonoDib(CDC *pDC, CDib *pDib, HDRAWDIB hdd);

