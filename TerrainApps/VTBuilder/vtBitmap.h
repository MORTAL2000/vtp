//
// vtBitmap.h
//
// Copyright (c) 2003 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef VTBITMAP_H
#define VTBITMAP_H

#include "vtdata/vtDIB.h"

/**
 * This class provides an encapsulation of "bitmap" behavior, which can
 * either use the Win32 DIBSection methods, or the wxWindows Bitmap methods.
 *
 * Set USE_DIBSECTIONS to 1 to get the DIBSection functionality.
 */
class vtBitmap : public vtBitmapBase
{
public:
	vtBitmap();
	virtual ~vtBitmap();

	bool Allocate(int iXSize, int iYSize, int iDepth = 24);
	void SetPixel24(int x, int y, unsigned char r, unsigned char g, unsigned char b);
	void SetPixel24(int x, int y, const RGBi &rgb)
	{
		SetPixel24(x, y, rgb.r, rgb.g, rgb.b);
	}
	void GetPixel24(int x, int y, RGBi &rgb) const;

	unsigned char GetPixel8(int x, int y) const;
	void SetPixel8(int x, int y, unsigned char color);

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	unsigned int GetDepth() const;

	void ContentsChanged();

	wxBitmap	*m_pBitmap;

protected:
	bool Allocate8(int iXSize, int iYSize);
	bool Allocate24(int iXSize, int iYSize);

#if USE_DIBSECTIONS
	// A DIBSection is a special kind of bitmap, handled as a HBITMAP,
	//  created with special methods, and accessed as a giant raw
	//  memory array.
	unsigned char *m_pScanline;
	int m_iScanlineWidth;
#else
	// For non-Windows platforms, or Windows platforms if we're being more
	//  cautious, the Bitmap is device-dependent and therefore can't be
	//  relied upon to store data the way we expect.  Hence, we must have
	//  both a wxImage (portable and easy to use, but can't be directly
	//  rendered) and a wxBitmap (which can be drawn to the window).
	//
	// This is less memory efficient and slower.
	//
	wxImage		*m_pImage;
#endif
};

#endif // VTBITMAP_H

