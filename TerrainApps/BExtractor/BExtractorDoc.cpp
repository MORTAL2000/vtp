//
// BExtractorDoc.cpp : implementation of the BExtractorDoc class
//
// Copyright (c) 2001 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "stdafx.h"
#include "BExtractor.h"
#include "BExtractorDoc.h"
#include "BExtractorView.h"
#include "ProjectionDlg.h"
#include "BImage.h"
#include "ProgDlg.h"
#include "Dib.h"
#include "xmlhelper/easyxml.hpp"

// GBM
#include "GBMWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////
// Helper

void ShowErrorMessage(int error)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				  FORMAT_MESSAGE_FROM_SYSTEM |	 
				  FORMAT_MESSAGE_IGNORE_INSERTS,	
				  NULL,
				  error,
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				  (LPTSTR) &lpMsgBuf,	0,	NULL );
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	LocalFree( lpMsgBuf );
}

CGBM *CreateMonoBitmap(CGBM *pGBM)
{
	CProgressDlg prog(CG_IDS_PROGRESS_CAPTION);
	prog.Create(NULL);	// top level
	prog.SetPos(0);

	int w = pGBM->GetWidth();
	int h = pGBM->GetHeight();
	CGBM *pNew = new CGBM(w, h, 8);

	int x, y;
	GBMRGB rgb;
	byte color8;

	for (y = 0; y < h; y++)
	{
		prog.SetPos(y*200/h);
		for (x = 0; x < w; x++)
		{
			pGBM->GetPixel24(x, y, rgb);
			 //if color is black, white, or gray, don't change it
			if (rgb.r == rgb.g && rgb.g == rgb.b)
				color8 = rgb.b;
			else
				color8 = 0xff;
			pNew->SetPixel8(x, y, color8);
		}
	}
	return pNew;
}

/////////////////////////////////////////////////////////////////////////////
// BExtractorDoc

IMPLEMENT_DYNCREATE(BExtractorDoc, CDocument)

BEGIN_MESSAGE_MAP(BExtractorDoc, CDocument)
	//{{AFX_MSG_MAP(BExtractorDoc)
	ON_COMMAND(ID_IMPORTIMAGE, OnImportimage)
	ON_COMMAND(ID_FUNCTIONS_CLEARBUILDINGS, OnFunctionsClearbuildings)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FULLRES, OnUpdateFullres)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BExtractorDoc construction/destruction

BExtractorDoc::BExtractorDoc()
{
	m_pImage = NULL;
	m_picLoaded = false;
	
	m_hdd = DrawDibOpen();
	m_proj.SetUTM(true);
}

BExtractorDoc::~BExtractorDoc()
{
	if (m_hdd) 
	{
		DrawDibClose(m_hdd);
		m_hdd = NULL;
	}
	DeleteContents();
}

BOOL BExtractorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void BExtractorDoc::DeleteContents()
{
	if (m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	m_Buildings.Empty();
}

/////////////////////////////////////////////////////////////////////////////
// BExtractorDoc serialization

void BExtractorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{

	}
}

/////////////////////////////////////////////////////////////////////////////
// BExtractorDoc diagnostics

#ifdef _DEBUG
void BExtractorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void BExtractorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////
// BExtractorDoc commands
void BExtractorDoc::PreFloodFillDIB(CDib *bm)
{	
	int width = bm->GetWidth();
	int height = bm->GetHeight();
	byte target = 0x00;
	int result = 0;
	int result2 = 0;

	CProgressDlg prog(CGS_KERNEL);
	prog.Create(NULL);	// top level
	prog.SetPos(0);
	for (int i = 0; i < width; i++)
	{
		prog.SetPos(i*200/width);
		for (int j = 0; j < height; j++)
		{
			if (bm->GetPixel8(i,j) == target)
			{
				result = Fill(bm, i, j, 0x00, 0x22, width, height, 0); //0x22=arbitrary value

				if (result > 120)
				{
					// We have something too big to be a building. 
					// The reason this # had to be 200 and not something
					// slightly larger than building size is because sometimes
					// the building pixels bleed into some thin lines made up
					// of black pixels that get added to the overall count.
					// So to avoid losing these buildings (or buildings whose
					// black pixels bleed into each other), the number is
					// bigger. 

					// This is also why the Fill method takes the diag
					// parameter, it tells it whether include pixels diagonal
					// to each other in the flood fill count (lines tend to
					// be diagonal)
					result2 = Fill(bm, i, j, 0x22, 0xff, width, height, 0); //get rid of it
				}
				else
				{
					//put the pixels back to what they were
					Fill(bm, i, j, 0x22, 0x00, width, height, 0);
				}
			}
		}
	}
}

void BExtractorDoc::FloodFillDIB(CDib *bm)
{
	int width = bm->GetWidth();
	int height = bm->GetHeight();
	byte target = 0x00;
	int result = 0;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (bm->GetPixel8(i,j) == target)
			{
				result = Fill(bm, i, j, 0x00, 0xff, width, height, 1);
				DPoint2 point;
				point.x = i_UTMx(i);
				point.y = i_UTMy(j);

				// rough heuristic: adjusts the coordinate more towards the  
				//center of the original building
				point.x += 5;

				vtBuilding *bld = new vtBuilding();
				bld->SetLocation(point);
				vtStructure *str = m_Buildings.NewStructure();
				str->SetBuilding(bld);
				m_Buildings.Append(str);
			}
		}
	}
}


//
// old_v = initial pixel value that you are looking to fill region of
// new_v = new value to fill area with
//
int BExtractorDoc::Fill(CDib *bm, int x, int y, byte old_v, byte new_v,
						  int w, int h, int diag, int count)
{
	byte val = bm->GetPixel8(x, y);
	int size = 0;

	// beware stack overflow - 1000 is a typically safe amount of recursion
	if (count > 1000)
		return 1;

	if (val == old_v)
	{
		bm->SetPixel8(x, y, new_v);
		size++;
		if (x+1 != w) size += Fill(bm, x+1, y, old_v, new_v, w, h, diag, count+1);
		if (x-1 >= 0) size += Fill(bm, x-1, y, old_v, new_v, w, h, diag, count+1);
		if (y+1 != h) size += Fill(bm, x, y+1, old_v, new_v, w, h, diag, count+1);
		if (y-1 >= 0)size += Fill(bm, x, y-1, old_v, new_v, w, h, diag, count+1);
		if ( (x+1 != w)&&(y+1 != h)&&(diag == 1) )
			size += Fill(bm, x+1, y+1, old_v, new_v, w, h, diag, count+1);
		if ( (x+1 != w)&&(y-1 >= 0)&&(diag == 1) )
			size += Fill(bm, x+1, y-1, old_v, new_v, w, h, diag, count+1);
		if ( (x-1 >= 0)&&(y+1 != h)&&(diag == 1) )
			size += Fill(bm, x-1, y+1, old_v, new_v, w, h, diag, count+1);
		if ( (x-1 >= 0)&&(y-1 >= 0)&&(diag == 1) )
			size += Fill(bm, x-1, y-1, old_v, new_v, w, h, diag, count+1);
	}
	return size;
}

float BExtractorDoc::i_UTMx(int ix)
{
	return (ix * m_pImage->m_xMetersPerPixel + m_pImage->m_xUTMoffset);
}

float BExtractorDoc::i_UTMy(int iy)
{
	return ((m_pImage->m_PixelSize.y - 1 - iy) * m_pImage->m_yMetersPerPixel
		+ m_pImage->m_yUTMoffset);
}

BOOL BExtractorDoc::OnOpenDocument(LPCTSTR szPathName) 
{
	CString name = szPathName;
	CString ext = name.Right(4);

	bool success = false;
	if (!ext.CompareNoCase(".tif")) 
	{
		OnImportimage2(szPathName);
		SetPathName(szPathName, true);
		SetPathName("Untitled", false);
		return false;
	}
	else if (!ext.CompareNoCase(".bcf"))
	{
		if (m_picLoaded == false)
		{
			AfxMessageBox("Sorry, you cannot load a .BCF file "
				"without having an image loaded!");
			return false;
		}

		// read in the bcf.
		success = m_Buildings.ReadBCF(szPathName);
		if (success)
		{
			for (int i = 0; i < m_Buildings.GetSize(); i++)
			{
				vtStructure *str = m_Buildings.GetAt(i);
				vtBuilding *bld = str->GetBuilding();
				bld->RectToPoly();
			}
			if (m_Buildings.m_proj.GetUTMZone() == -1)
			{
				// loading file with unknown zone, assume the current
				m_Buildings.m_proj.SetUTMZone(m_proj.GetUTMZone());
			}
		}
	}
	else if (!ext.CompareNoCase("vtst"))
	{
		try
		{
			success = m_Buildings.ReadXML(szPathName);
		}
		catch (xh_io_exception &e)
		{
			string str = "Problem opening file: ";
			str += e.getFormattedMessage();
			AfxMessageBox(str.c_str());
		}
	}
	else
	{
		CString str;
		str.Format("Sorry, don't know how to load the file:\n%s", szPathName);
		AfxMessageBox(str);
	}
	if (success)
	{
		POSITION pos = GetFirstViewPosition();
		BExtractorView* pFirstView = (BExtractorView*)GetNextView( pos );
		pFirstView->Invalidate();
	}
	return success;
}


BOOL BExtractorDoc::OnSaveDocument(LPCTSTR szPathName)
{
	return m_Buildings.WriteXML(szPathName);
}


//
// TIF stuff 
//
void BExtractorDoc::OnImportimage()
{
	CFileDialog openDialog(TRUE, "*.tif", "");

	openDialog.m_ofn.lpstrFilter = "Image Files (*.tif, *.bmp)\0*.tif;*.bmp\0";

	if (openDialog.DoModal() != IDOK)
		return;

	CString str = openDialog.GetPathName();
	const char *szPathName = str;

	if (m_pImage) delete m_pImage; 

	OnImportimage2(szPathName);
}

void BExtractorDoc::OnImportimage2(LPCTSTR szPathName) 
{
	m_picLoaded = false;
	m_pImage = new CBImage();

	if (1)
	{
		CProgressDlg prog(CG_IDS_PROGRESS_CAPTION3);
		prog.Create(NULL);	// top level
	//	prog.SetPos(0);
	//	prog.SetPos(y*200/h);
		bool success = m_pImage->LoadFromFile(szPathName);
		if (!success)
			return;
	}

	// don't know projection unless (until) we read geotiff

	// get utm zone from a dialog
	CProjectionDlg dlg;
	dlg.m_iZone = -1;
	if (dlg.DoModal() != IDOK)
		return;

	m_proj.SetUTMZone(dlg.m_iZone);
	m_Buildings.m_proj.SetUTMZone(dlg.m_iZone);

	// is image >50MB?
	if (m_pImage->m_PixelSize.x * m_pImage->m_PixelSize.y > 50000000)
	{
		CString str;
		str.Format("Warning!  That image is really large (%d * %d)\n"
			"You can save memory by disabling color display.\n"
			"Do you want to do this?",
			m_pImage->m_PixelSize.x, m_pImage->m_PixelSize.y);
		int result = AfxMessageBox(str, MB_YESNO);
		if (result == IDYES)
		{
			delete m_pImage->m_pSourceGBM;
			m_pImage->m_pSourceGBM = NULL;
		}
	}
	m_picLoaded = true;

	// Tell the view to zoom to the freshly loaded bitmap
	POSITION pos = GetFirstViewPosition();
	BExtractorView* pFirstView = (BExtractorView*)GetNextView( pos );
	m_Buildings.Empty(); //clear out any old buildings we have lying around
	pFirstView->ZoomToImage(m_pImage);
}


void BExtractorDoc::OnFunctionsClearbuildings() 
{
	m_Buildings.Empty();
	POSITION pos = GetFirstViewPosition();
	BExtractorView* pFirstView = (BExtractorView*)GetNextView( pos );
	pFirstView->Invalidate();
}


void BExtractorDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_picLoaded);
}

void BExtractorDoc::OnUpdateFullres(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_picLoaded);
}
