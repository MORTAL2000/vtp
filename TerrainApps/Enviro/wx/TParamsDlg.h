//
// Name: TParamsDlg.h
//
// Copyright (c) 2002-2003 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#ifndef __TParamsDlg_H__
#define __TParamsDlg_H__

#if defined(__GNUG__) && !defined(__APPLE__)
	#pragma interface "TParamsDlg.cpp"
#endif

#include "enviro_wdr.h"
#include "vtui/AutoDialog.h"
#include "vtui/wxString2.h"
#include "vtdata/TParams.h"

// WDR: class declarations

/**
 * wxListBoxEventHandler is a roudabout way of catching events on our
 * listboxes, to implement the "Delete" key operation on them.
 */
class wxListBoxEventHandler: public wxEvtHandler
{
public:
	wxListBoxEventHandler(class TParamsDlg *dlg, wxListBox *box);
	void OnChar(wxKeyEvent& event);

private:
	class TParamsDlg *m_pDlg;
	wxListBox *m_pBox;
	DECLARE_EVENT_TABLE()
};

//----------------------------------------------------------------------------
// TParamsDlg
//----------------------------------------------------------------------------

class TParamsDlg: public AutoDialog
{
public:
	// constructors and destructors
	TParamsDlg( wxWindow *parent, wxWindowID id, const wxString &title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE );
	~TParamsDlg();

	void OnInitDialog(wxInitDialogEvent& event);

	bool TransferDataToWindow();
	bool TransferDataFromWindow();

	void SetParams(const TParams &Params);
	void GetParams(TParams &Params);
	void SetDataPaths(const vtStringArray &paths) { m_datapaths = paths; }
	void UpdateTiledTextureFilename();
	void UpdateEnableState();
	void RefreshLabelFields();
	void RefreshLocationFields();

	wxString2	m_strFilename;
	wxString2	m_strFilenameTin;
	float   m_fVerticalExag;
	bool	m_bTin;

	// navigation
	int		m_iMinHeight;
	int     m_iNavStyle;
	float   m_fNavSpeed;
	wxString2	m_strLocFile;
	int		m_iInitLocation;	wxString2	m_strInitLocation;
	float   m_fHither;

	// LOD
	int		m_iLodMethod;
	float   m_fPixelError;
	int		m_iTriCount;
	bool	m_bTriStrips;
	bool	m_bDetailTexture;

	// time
	bool	m_bTimeOn;
	int		m_iInitTime;
	float   m_fTimeSpeed;

	// texture
	int		m_iTexture;
	int		m_iTilesize;
	wxString2	m_strTextureSingle;
	wxString2	m_strTextureBase;
	wxString2	m_strTextureFilename;
	bool	m_bJPEG;
	bool	m_bMipmap;
	bool	m_b16bit;
	bool	m_bPreLight;
	bool	m_bPreLit;
	float   m_fPreLightFactor;

	// culture
	bool	m_bRoads;
	wxString2	m_strRoadFile;
	bool	m_bHwy;
	bool	m_bPaved;
	bool	m_bDirt;
	float   m_fRoadHeight;
	float   m_fRoadDistance;
	bool	m_bTexRoads;
	bool	m_bRoadCulture;

	bool	m_bTrees;
	wxString2	m_strVegFile;
	int		m_iVegDistance;

	bool	m_bFog;
	float	m_fFogDistance;

	wxStringArray	m_strStructFiles;
	int		m_iStructDistance;

	bool	m_bSky;
	wxString2	m_strSkyTexture;
	bool	m_bOceanPlane;
	float	m_fOceanPlaneLevel;
	bool	m_bDepressOcean;
	float	m_fDepressOceanLevel;
	bool	m_bHorizon;
//  bool	m_bOverlay;

	bool	m_bLabels;
	wxString2	m_strLabelFile;
	PointStyle	m_Style;

//  bool	m_bVehicles;
//  float   m_fVehicleSize;
//  float   m_fVehicleSpeed;
//  int		m_iNumCars;

	bool	m_bRouteEnable;
	wxString2 m_strRouteFile;

	wxString2 m_strInitTime;
//  wxString2	m_strMemRequired;

	// WDR: method declarations for TParamsDlg
	wxChoice* GetNavStyle()  { return (wxChoice*) FindWindow( ID_NAV_STYLE ); }
	wxRadioButton* GetUseGrid()  { return (wxRadioButton*) FindWindow( ID_USE_GRID ); }
	wxRadioButton* GetUseTin()  { return (wxRadioButton*) FindWindow( ID_USE_TIN ); }
	wxComboBox* GetLocfile()  { return (wxComboBox*) FindWindow( ID_LOCFILE ); }
	wxRadioButton* GetTiled()  { return (wxRadioButton*) FindWindow( ID_TILED ); }
	wxRadioButton* GetDerived()  { return (wxRadioButton*) FindWindow( ID_DERIVED ); }
	wxRadioButton* GetSingle()  { return (wxRadioButton*) FindWindow( ID_SINGLE ); }
	wxRadioButton* GetNone()  { return (wxRadioButton*) FindWindow( ID_NONE ); }
	wxTextCtrl* GetLightFactor()  { return (wxTextCtrl*) FindWindow( ID_LIGHT_FACTOR ); }
	wxComboBox* GetRoadfile()  { return (wxComboBox*) FindWindow( ID_ROADFILE ); }
	wxComboBox* GetTreefile()  { return (wxComboBox*) FindWindow( ID_TREEFILE ); }
	wxComboBox* GetTfilesingle()  { return (wxComboBox*) FindWindow( ID_TFILESINGLE ); }
	wxChoice* GetLodmethod()  { return (wxChoice*) FindWindow( ID_LODMETHOD ); }
	wxComboBox* GetFilename()  { return (wxComboBox*) FindWindow( ID_FILENAME ); }
	wxComboBox* GetFilenameTin()  { return (wxComboBox*) FindWindow( ID_FILENAME_TIN ); }
	wxComboBox* GetSkytexture()  { return (wxComboBox*) FindWindow( ID_SKYTEXTURE ); }
	wxTextCtrl* GetFogDistance()  { return (wxTextCtrl*) FindWindow( ID_FOG_DISTANCE ); }
	wxTextCtrl* GetDepressOceanOffset()  { return (wxTextCtrl*) FindWindow( ID_DEPRESSOCEANOFFSET ); }
	wxTextCtrl* GetOceanPlaneOffset()  { return (wxTextCtrl*) FindWindow( ID_OCEANPLANEOFFSET ); }
	wxComboBox* GetLabelFile()  { return (wxComboBox*) FindWindow( ID_LABEL_FILE ); }
	wxChoice* GetLocField()  { return (wxChoice*) FindWindow( ID_INIT_LOCATION ); }
	wxChoice* GetLabelField()  { return (wxChoice*) FindWindow( ID_LABEL_FIELD ); }
	wxListBox* GetStructFiles()  { return (wxListBox*) FindWindow( ID_STRUCTFILES ); }

	bool	m_bReady;
	bool	m_bSetting;
	vtStringArray m_datapaths;

private:
	// WDR: member variable declarations for TParamsDlg
	wxChoice* m_pNavStyle;
	wxTextCtrl* m_pPreLightFactor;
	wxListBox* m_pStructFiles;
	wxComboBox* m_pRoadFile;
	wxComboBox* m_pTreeFile;
	wxComboBox* m_pTextureFileSingle;
	wxChoice* m_pLodMethod;
	wxComboBox* m_pFilename;
	wxComboBox* m_pFilenameTin;
	wxRadioButton* m_pNone;
	wxRadioButton* m_pSingle;
	wxRadioButton* m_pDerived;
	wxRadioButton* m_pTiled;
	wxComboBox* m_pLocFile;
	wxComboBox* m_pSkyTexture;
	wxComboBox* m_pLabelFile;
	wxChoice* m_pLabelField;
	wxChoice* m_pLocField;
	wxListBoxEventHandler *m_pBoxHandler;

private:
	// WDR: handler declarations for TParamsDlg
	void OnTextureFileBase( wxCommandEvent &event );
	void OnTileSize( wxCommandEvent &event );
	void OnTextureNone( wxCommandEvent &event );
	void OnTextureSingle( wxCommandEvent &event );
	void OnTextureDerived( wxCommandEvent &event );
	void OnTextureTiled( wxCommandEvent &event );
	void OnCheckBox( wxCommandEvent &event );
	void OnListDblClick( wxCommandEvent &event );
	void OnChoiceLabelFile( wxCommandEvent &event );
	void OnChoiceLocFile( wxCommandEvent &event );
	void OnChoiceInitLocation( wxCommandEvent &event );

private:
	DECLARE_EVENT_TABLE()
};

#endif	// __TParamsDlg_H__

