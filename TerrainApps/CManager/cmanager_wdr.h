//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: cmanager.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_cmanager_H__
#define __WDR_cmanager_H__

#ifdef __GNUG__
    #pragma interface "cmanager_wdr.h"
#endif

// Include wxWindows' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>

// Declare window functions

#define ID_SCENETREE 10000
#define ID_ENABLED 10001
#define ID_ZOOMTO 10002
#define ID_REFRESH 10003
wxSizer *SceneGraphFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TEXT 10004
#define ID_ITEM 10005
#define ID_TYPECHOICE 10006
#define ID_ADDTAG 10007
#define ID_REMOVETAG 10008
#define ID_EDITTAG 10009
#define ID_TAGLIST 10010
wxSizer *PropDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_FILENAME 10011
#define ID_DISTANCE 10012
#define ID_SCALE 10013
#define ID_STATUS 10014
wxSizer *ModelDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

#define ID_TAGNAME 10015
#define ID_TAGTEXT 10016
wxSizer *TagDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

// Declare toolbar functions

// Declare bitmap functions

#endif

// End of generated file
