//
// StartupDlg.cpp : implementation file
//

#include "StdAfx.h"

#include "vtlib/vtlib.h"
#include "vtlib/core/Terrain.h"
#include "vtlib/core/TerrainScene.h"
#include "StartupDlg.h"
#include "ChooseDlg.h"
#include "../Enviro.h"	// for GetTerrainScene

CStartupDlg g_StartDlg;

void CStartupDlg::GetOptionsFrom(EnviroOptions &opt)
{
	m_iLaunch = (opt.m_bEarthView ? 0 : 1);
	m_strImage = opt.m_strImage;
	m_strTName = opt.m_strInitTerrain;
	m_bFullscreen = opt.m_bFullscreen;
	m_bGravity = opt.m_bGravity;
	m_bHtmlpane = opt.m_bHtmlpane;
	m_bFloatingToolbar = opt.m_bFloatingToolbar;
	m_bSound = opt.m_bSound;
	m_bVCursor = opt.m_bVCursor;
	m_bSpeedTest = opt.m_bSpeedTest;
	m_bQuakeNavigation = opt.m_bQuakeNavigation;
	m_fPlantSize = opt.m_fPlantScale;
	m_bShadows = opt.m_bShadows;
}

void CStartupDlg::PutOptionsTo(EnviroOptions &opt)
{
	opt.m_bEarthView = (m_iLaunch == 0);
	opt.m_strImage = m_strImage;
	opt.m_strInitTerrain = m_strTName;
	opt.m_bFullscreen = m_bFullscreen;
	opt.m_bGravity = m_bGravity;
	opt.m_bHtmlpane = m_bHtmlpane;
	opt.m_bFloatingToolbar = m_bFloatingToolbar;
	opt.m_bSound = m_bSound;
	opt.m_bVCursor = m_bVCursor;
	opt.m_bSpeedTest = m_bSpeedTest;
	opt.m_bQuakeNavigation = m_bQuakeNavigation;
	opt.m_fPlantScale = m_fPlantSize;
	opt.m_bShadows = m_bShadows;
}

/////////////////////////////////////////////////////////////////////////////
// CStartupDlg dialog


CStartupDlg::CStartupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartupDlg)
	m_bFullscreen = FALSE;
	m_bGravity = FALSE;
	m_bHtmlpane = FALSE;
	m_bFloatingToolbar = FALSE;
	m_bSound = FALSE;
	m_bVCursor = FALSE;
	m_bSpeedTest = FALSE;
	m_bQuakeNavigation = FALSE;
	m_iLaunch = -1;
	m_strTName = _T("");
	m_strImage = _T("");
	m_fPlantSize = 0.0f;
	m_bShadows = FALSE;
	//}}AFX_DATA_INIT
}


void CStartupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartupDlg)
	DDX_Control(pDX, IDC_IMAGE, m_cbImage);
	DDX_Control(pDX, IDC_STATICIMAGE, m_csImage);
	DDX_Control(pDX, IDC_TSELECT, m_cbTSelect);
	DDX_Control(pDX, IDC_TNAME, m_editTName);
	DDX_Check(pDX, IDC_FULLSCREEN, m_bFullscreen);
	DDX_Check(pDX, IDC_GRAVITY, m_bGravity);
	DDX_Check(pDX, IDC_HTMLPANE, m_bHtmlpane);
	DDX_Check(pDX, IDC_TOOLBAR, m_bFloatingToolbar);
	DDX_Check(pDX, IDC_SOUND, m_bSound);
	DDX_Check(pDX, IDC_VCURSOR, m_bVCursor);
	DDX_Check(pDX, IDC_SPEEDTEST, m_bSpeedTest);
	DDX_Check(pDX, IDC_QUAKEENGINE, m_bQuakeNavigation);
	DDX_Radio(pDX, IDC_LAUNCH1, m_iLaunch);
	DDX_Text(pDX, IDC_TNAME, m_strTName);
	DDX_Text(pDX, IDC_IMAGE, m_strImage);
	DDX_Text(pDX, IDC_PLANTSIZE, m_fPlantSize);
	DDX_Check(pDX, IDC_SHADOWS, m_bShadows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartupDlg, CDialog)
	//{{AFX_MSG_MAP(CStartupDlg)
	ON_BN_CLICKED(IDC_OPENGL_INFO, OnOpenglInfo)
	ON_BN_CLICKED(IDC_TSELECT, OnTSelect)
	ON_BN_CLICKED(IDC_LAUNCH1, OnChangeLaunch)
	ON_BN_CLICKED(IDC_LAUNCH2, OnChangeLaunch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//
// This function replaces CComboBox::Dir, because that method
//  does not support non-8.3 directory names (or file names)
//  in Win9x operating systems.
//
void AddFilesToComboBox(CComboBox *box, CString wildcard)
{
	CFileFind finder; 
	BOOL bWorking = finder.FindFile(wildcard); 
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDirectory())
		{
			CString str = finder.GetFileName();
			box->AddString(str.Left(str.GetLength()-9));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStartupDlg message handlers

BOOL CStartupDlg::OnInitDialog() 
{
	vtTerrain *pTerr = GetTerrainScene()->FindTerrainByName(m_strTName);
	if (pTerr)
		m_strTName = pTerr->GetName();
	else
		m_strTName = "none";

	CDialog::OnInitDialog();

	StringArray &paths = g_Options.m_DataPaths;
	for (int i = 0; i < paths.GetSize(); i++)
	{
		CString path = (const char *) (*paths[i]);
		AddFilesToComboBox(&m_cbImage, path + "WholeEarth/*_0106.png");
	}
	m_cbImage.SelectString(-1, m_strImage);

	UpdateState();

	return TRUE;  // return TRUE unless you set the focus to a control
}

//
// Helper: find the largest texture size supported by OpenGL
//
void ShowOGLInfo(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
		1,                     // version number 
		PFD_DRAW_TO_WINDOW |   // support window 
		PFD_SUPPORT_OPENGL |   // support OpenGL 
		PFD_DOUBLEBUFFER,      // double buffered 
		PFD_TYPE_RGBA,         // RGBA type 
		24,                    // 24-bit color depth 
		0, 0, 0, 0, 0, 0,      // color bits ignored 
		0, 0, 0,               // no alpha buffer 
		0, 0, 0, 0,            // accum bits ignored 
		32, 0, 0,              // 32-bit z-buffer 
		PFD_MAIN_PLANE,        // main layer
		0,                     // reserved 
		0, 0, 0                // layer masks ignored
	};
	int  iPixelFormat;
	// get the best available match of pixel format for the device context  
	iPixelFormat = ChoosePixelFormat(hdc, &pfd);
	// make that the pixel format of the device context 
	SetPixelFormat(hdc, iPixelFormat, &pfd);

	HGLRC device = wglCreateContext(hdc);
	if (device == NULL)
	{
		DWORD lasterror = GetLastError();
		// 2000 The pixel format is invalid.  ERROR_INVALID_PIXEL_FORMAT 
	}
	wglMakeCurrent(hdc, device);
	GLint value;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &value);
	GLenum error = glGetError();
	if (error == GL_INVALID_OPERATION)
		value = 0;

	CString str;
	str.Format("OpenGL Version: %s\nVendor: %s\nRenderer: %s\nMaximum Texture Dimension: %d\nExtensions: %s",
		glGetString(GL_VERSION), glGetString(GL_VENDOR),
		glGetString(GL_RENDERER), value, glGetString(GL_EXTENSIONS));
	AfxMessageBox(str);

	wglDeleteContext(device);
//	return value;
}


void CStartupDlg::OnOpenglInfo() 
{
	// check the OpenGL max texture size
	HWND hwnd = GetSafeHwnd();
	CDC *pDC = GetDC();
	HDC hdc = pDC->GetSafeHdc();
	ShowOGLInfo(hdc);
}

void CStartupDlg::OnTSelect() 
{
	UpdateData(TRUE);
	CChooseDlg dlg;
	dlg.m_strTName = m_strTName;
	if (dlg.DoModal() == IDOK)
		m_strTName = dlg.m_strTName;
	UpdateData(FALSE);
}


void CStartupDlg::OnChangeLaunch() 
{
	UpdateData(TRUE);
	UpdateState();
}

void CStartupDlg::UpdateState()
{
	m_csImage.EnableWindow(m_iLaunch == 0);
	m_cbImage.EnableWindow(m_iLaunch == 0);
	m_editTName.EnableWindow(m_iLaunch == 1);
	m_cbTSelect.EnableWindow(m_iLaunch == 1);
}
