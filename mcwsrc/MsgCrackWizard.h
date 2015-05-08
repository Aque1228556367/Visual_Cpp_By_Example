/*****************************************************************

 Message Cracker Wizard -- Assistant for Win32 Developers
Copyright (C) 2003-2005 Hernán Di Pietro

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


  ***************************************************************************/
#ifndef MSGCRACKWIZARD_H
#define MSGCRACKWIZARD_H
#include "stdafx.h"

// global variables with enough large buffers..  ;)
#define BUFFER			 5000
const  SIZE_T cbStrBuf = 5000;
const  SIZE_T MAX_WINDOW_ID   = 1024;

// ownerdrawn listbox handles
extern HBITMAP  hbmpKeyboard, hbmpMouse, hbmpClipboard, hbmpGeneral, hbmpMDI, hbmpNonClient;
extern HBITMAP  hbmpWindow;

// define for window transparency
#define WS_EX_LAYERED	0x80000
#define LWA_ALPHA		2

// typedef for pointer to SetLayeredWindowAttributes
typedef DWORD (WINAPI * PSLWA) (HWND, DWORD, BYTE, DWORD);

//
// function prototypes
//
BOOL CALLBACK FilterDlg_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlg_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void CopyMacroToCB	(HWND hwnd);
void CopyFuncToCB	(HWND hwnd);
void SetupControls	(HWND hwnd);
void FillListBox	(HWND hwnd, UINT filter);
void UpdateUI		(HWND hwnd);
void EnableControls (HWND hwnd, BOOL fEnabled);

// ownerdrawn-related functions
HBITMAP SelectItemBitmap(const DRAWITEMSTRUCT* lpDrawItem);
void    DrawItemBitmap (const DRAWITEMSTRUCT* lpDrawItem, HBITMAP hPic);


// message types
#define		KEYBOARD		1
#define		MOUSE			2
#define		CLIPBOARD		4
#define     GENERAL			8
#define		NONCLIENT		16
#define		MDI				32
#define     NOFILTER        KEYBOARD | \
	                        MOUSE | \
							GENERAL | \
							NONCLIENT| \
							MDI   | \
							CLIPBOARD;
extern UINT  fFilter;

//
// structure to hold window messages properties
//
const struct MESSAGEINFO
{
	UINT		fType;
    char*		WM_msg;
    char*		fnname;
    char*		params;
    char*		rettype;
	//char* desc;
} extern msginfo[] = { 

	KEYBOARD,	"WM_VKEYTOITEM",        "OnVkeyToItem",     "(HWND hwnd, UINT vk, HWND hwndListbox, int iCaret)", "int",
	KEYBOARD,	"WM_SYSKEYDOWN",        "OnSysKeyDown",     "(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)", "void",
	KEYBOARD,	"WM_SYSKEYUP",          "OnSysKeyUp",       "(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)", "void",
	KEYBOARD,	"WM_SYSCHAR",           "OnSysChar",        "(HWND hwnd, TCHAR ch, int cRepeat)", "void",
	KEYBOARD,	"WM_SYSDEADCHAR",       "OnSysDeadChar",    "(HWND hwnd, TCHAR ch, int cRepeat)", "void",
	KEYBOARD,	"WM_KEYUP",             "OnKeyUp",          "(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)", "void",
	KEYBOARD,	"WM_KEYDOWN",           "OnKeyDown",        "(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)", "void",
	KEYBOARD,	"WM_CHAR",              "OnChar",           "(HWND hwnd, TCHAR ch, int cRepeat)", "void",
	KEYBOARD,	"WM_DEADCHAR",          "OnDeadChar",       "(HWND hwnd, TCHAR ch, int cRepeat)", "void",
	KEYBOARD,	"WM_HOTKEY",			"OnHotKey",			"(HWND hwnd, int idHotKey, UINT fuModifiers, UINT vk)", "void",
	KEYBOARD,	"WM_CHARTOITEM",        "OnCharToItem",     "(HWND hwnd, UINT ch, HWND hwndListbox, int iCaret)", "int",
	GENERAL,	"WM_COMPACTING",		"OnCompacting",     "(HWND hwnd, UINT compactRatio)", "void",
	GENERAL,	"WM_WININICHANGE",      "OnWinIniChange",   "(HWND hwnd, LPCTSTR lpszSectionName)", "void",
    GENERAL,    "WM_SYSCOLORCHANGE",    "OnSysColorChange", "(HWND hwnd)", "void",
    GENERAL,    "WM_QUERYNEWPALETTE",   "OnQueryNewPalette","(HWND hwnd)", "BOOL",
    GENERAL,    "WM_PALETTEISCHANGING", "OnPaletteIsChanging", "(HWND hwnd, HWND hwndPaletteChange)", "void",
    GENERAL,    "WM_PALETTECHANGED",    "OnPaletteChanged", "(HWND hwnd, HWND hwndPaletteChange)", "void",
	GENERAL,	"WM_FONTCHANGE",        "OnFontChange",     "(HWND hwnd)", "void",
    GENERAL,    "WM_SPOOLERSTATUS",     "OnSpoolerStatus",  "(HWND hwnd, UINT status, int cJobInQueue)", "void", 
    GENERAL,    "WM_DEVMODECHANGE",     "OnDevModeChange",  "(HWND hwnd, LPCTSTR lpszDeviceName)", "void", 
    GENERAL,    "WM_TIMECHANGE",        "OnTimeChange",     "(HWND hwnd)", "void",  
    GENERAL,    "WM_POWER",             "OnPower",          "(HWND hwnd, int code)", "void",
    GENERAL,    "WM_QUERYENDSESSION",   "OnQueryEndSession","(HWND hwnd)", "BOOL",
    GENERAL,    "WM_ENDSESSION",        "OnEndSession",     "(HWND hwnd, BOOL fEnding)", "void",
    GENERAL,    "WM_QUIT",              "OnQuit",           "(HWND hwnd, int exitCode)", "void",
    GENERAL,    "WM_SYSTEMERROR",       "OnSystemError",    "(HWND hwnd, int errCode)", "void",
    GENERAL,    "WM_CREATE",            "OnCreate",         "(HWND hwnd, LPCREATESTRUCT lpCreateStruct)", "BOOL",
    NONCLIENT,  "WM_NCCREATE",          "OnNCCreate",       "(HWND hwnd, LPCREATESTRUCT lpCreateStruct)", "BOOL",
    GENERAL,    "WM_DESTROY",           "OnDestroy",        "(HWND hwnd)", "void",
    NONCLIENT,  "WM_NCDESTROY",         "OnNCDestroy",      "(HWND hwnd)", "void",
    GENERAL,    "WM_SHOWWINDOW",        "OnShowWindow",     "(HWND hwnd, BOOL fShow, UINT status)", "void",
    GENERAL,    "WM_SETREDRAW",         "OnSetRedraw",      "(HWND hwnd, BOOL fRedraw)", "void",
    GENERAL,    "WM_ENABLE",            "OnEnable",         "(HWND hwnd, BOOL fEnable)", "void",
    GENERAL,    "WM_SETTEXT",           "OnSetText",        "(HWND hwnd, LPCTSTR lpszText)", "void",
    GENERAL,    "WM_GETTEXT",           "OnGetText",        "(HWND hwnd, int cchTextMax, LPTSTR lpszText)", "INT",
    GENERAL,    "WM_GETTEXTLENGTH",     "OnGetTextLength",  "(HWND hwnd)", "INT",
    GENERAL,    "WM_WINDOWPOSCHANGING", "OnWindowPosChanging", "(HWND hwnd, LPWINDOWPOS lpwpos)", "BOOL",
    GENERAL,    "WM_WINDOWPOSCHANGED",  "OnWindowPosChanged", "(HWND hwnd, const LPWINDOWPOS lpwpos)", "void",
    GENERAL,    "WM_MOVE",              "OnMove",           "(HWND hwnd, int x, int y)", "void",
    GENERAL,    "WM_SIZE",              "OnSize",           "(HWND hwnd, UINT state, int cx, int cy)", "void",
    GENERAL,    "WM_CLOSE",             "OnClose",          "(HWND hwnd)", "void",
    GENERAL,    "WM_QUERYOPEN",         "OnQueryOpen",      "(HWND hwnd)", "BOOL",
    GENERAL,    "WM_GETMINMAXINFO",     "OnGetMinMaxInfo",  "(HWND hwnd, LPMINMAXINFO lpMinMaxInfo)", "void",
    GENERAL,    "WM_PAINT",             "OnPaint",          "(HWND hwnd)", "void",
    GENERAL,    "WM_ERASEBKGND",        "OnEraseBkgnd",     "(HWND hwnd, HDC hdc)", "BOOL",
    GENERAL,    "WM_ICONERASEBKGND",    "OnIconEraseBkgnd", "(HWND hwnd, HDC hdc)", "BOOL",
    NONCLIENT,  "WM_NCPAINT",           "OnNCPaint",        "(HWND hwnd, HRGN hrgn)", "void",
    NONCLIENT,  "WM_NCCALCSIZE",        "OnNCCalcSize",     "(HWND hwnd, BOOL fCalcValidRects, NCCALCSIZE_PARAMS * lpcsp)", "UINT",
    NONCLIENT,  "WM_NCHITTEST",         "OnNCHitTest",      "(HWND hwnd, int x, int y)", "UINT",
    GENERAL,    "WM_QUERYDRAGICON",     "OnQueryDragIcon",  "(HWND hwnd)", "HICON",
    MOUSE,      "WM_DROPFILES",         "OnDropFiles",      "(HWND hwnd, HDROP hdrop)", "void",
    GENERAL,    "WM_ACTIVATE",          "OnActivate",       "(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized)","void",
    GENERAL,    "WM_ACTIVATEAPP",       "OnActivateApp",    "(HWND hwnd, BOOL fActivate, DWORD dwThreadId)", "void",
    NONCLIENT,  "WM_NCACTIVATE",        "OnNCActivate",     "(HWND hwnd, BOOL fActive, HWND hwndActDeact, BOOL fMinimized)", "BOOL",
    GENERAL,    "WM_SETFOCUS",          "OnSetFocus",       "(HWND hwnd, HWND hwndOldFocus)", "void",
    GENERAL,    "WM_KILLFOCUS",         "OnKillFocus",      "(HWND hwnd, HWND hwndNewFocus)", "void",
    MOUSE,      "WM_MOUSEMOVE",         "OnMouseMove",      "(HWND hwnd, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_LBUTTONDOWN",       "OnLButtonDown",    "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_LBUTTONDBLCLK",     "OnLButtonDblClk",  "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_LBUTTONUP",         "OnLButtonUp",      "(HWND hwnd, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_RBUTTONDOWN",       "OnRButtonDown",    "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_RBUTTONDBLCLK",     "OnRButtonDblClk",  "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_RBUTTONUP",         "OnRButtonUp",      "(HWND hwnd, int x, int y, UINT flags)", "void",
    MOUSE,      "WM_MBUTTONDOWN",       "OnMButtonDown",    "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_MBUTTONDBLCLK",     "OnMButtonDblclk",  "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)", "void",
    MOUSE,      "WM_MBUTTONUP",         "OnMButtonUp",      "(HWND hwnd, int x, int y, UINT flags)", "void",
    MOUSE,      "WM_MOUSEWHEEL",        "OnMouseWheel",     "(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys)", "void",
    NONCLIENT,  "WM_NCMOUSEMOVE",       "OnNCMouseMove",    "(HWND hwnd, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCLBUTTONDOWN",     "OnNCLButtonDown",  "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCLBUTTONDBLCLK",   "OnNCLButtonDblClk","(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCLBUTTONUP",       "OnNCLButtonUp",    "(HWND hwnd, int x, int y, UINT codeHitTest) ", "void",
    NONCLIENT,  "WM_NCRBUTTONDOWN",     "OnNCRButtonDown",  "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCRBUTTONDBLCLK",   "OnNCRButtonDblClk","(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCRBUTTONUP",       "OnNCRButtonUp",    "(HWND hwnd, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCMBUTTONDOWN",     "OnNCMButtonDown",  "(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCMBUTTONDBLCLK",   "OnNCMButtonDblClk","(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)", "void",
    NONCLIENT,  "WM_NCMBUTTONUP",       "OnNCMButtonUp",    "(HWND hwnd, int x, int y, UINT codeHitTest)", "void",
    MOUSE,      "WM_MOUSEACTIVATE",     "OnMouseActivate",  "(HWND hwnd, HWND hwndTopLevel, UINT codeHitTest, UINT msg)", "int",
    GENERAL,    "WM_CANCELMODE",        "OnCancelMode",     "(HWND hwnd)", "void",
    GENERAL,    "WM_TIMER",             "OnTimer",          "(HWND hwnd, UINT id)", "void",
    GENERAL,    "WM_INITMENU",          "OnInitMenu",       "(HWND hwnd, HMENU hMenu)", "void",
    GENERAL,    "WM_INITMENUPOPUP",     "OnInitMenuPopup",  "(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu)", "void",
    GENERAL,    "WM_MENUSELECT",        "OnMenuSelect",     "(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)", "void",
    GENERAL,    "WM_MENUCHAR",          "OnMenuChar",       "(HWND hwnd, UINT ch, UINT flags, HMENU hmenu)", "DWORD",
    GENERAL,    "WM_COMMAND",           "OnCommand",        "(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)", "void",
    GENERAL,    "WM_HSCROLL",           "OnHScroll",        "(HWND hwnd, HWND hwndCtl, UINT code, int pos)", "void",
    GENERAL,    "WM_VSCROLL",           "OnVScroll",        "(HWND hwnd, HWND hwndCtl, UINT code, int pos)", "void",
    CLIPBOARD,  "WM_CUT",               "OnCut",            "(HWND hwnd)", "void",
    CLIPBOARD,  "WM_COPY",              "OnCopy",           "(HWND hwnd)", "void",
    CLIPBOARD,  "WM_PASTE",             "OnPaste",          "(HWND hwnd)", "void",
    CLIPBOARD,  "WM_CLEAR",             "OnClear",          "(HWND hwnd)", "void",
    CLIPBOARD,  "WM_UNDO",              "OnUndo",           "(HWND hwnd)", "void",
    CLIPBOARD,  "WM_RENDERFORMAT",      "OnRenderFormat",   "(HWND hwnd, UINT fmt)", "HANDLE",
    CLIPBOARD,  "WM_RENDERALLFORMATS",  "OnRenderAllFormats","(HWND hwnd)", "void",
    CLIPBOARD,  "WM_DESTROYCLIPBOARD",  "OnDestroyClipboard", "(HWND hwnd)", "void",
    CLIPBOARD,  "WM_DRAWCLIPBOARD",     "OnDrawClipboard"   , "(HWND hwnd)", "void",
    CLIPBOARD,  "WM_PAINTCLIPBOARD",    "OnPaintClipboard",   "(HWND hwnd, HWND hwndCBViewer, const LPPAINTSTRUCT lpPaintStruct)", "void",
    CLIPBOARD,  "WM_SIZECLIPBOARD",     "OnSizeClipboard",    "(HWND hwnd, HWND hwndCBViewer, const LPRECT lprc)", "void",
    CLIPBOARD,  "WM_VSCROLLCLIPBOARD",  "OnVScrollClipboard", "(HWND hwnd, HWND hwndCBViewer, UINT code, int pos)", "void",
    CLIPBOARD,  "WM_HSCROLLCLIPBOARD",  "OnHScrollClipboard", "(HWND hwnd, HWND hwndCBViewer, UINT code, int pos)", "void",
    CLIPBOARD,  "WM_ASKCBFORMATNAME",   "OnAskCBFormatName",    "(HWND hwnd, int cchMax, LPTSTR rgchName)", "void",
    CLIPBOARD,  "WM_CHANGECBCHAIN",     "OnChangeCBChain",      "(HWND hwnd, HWND hwndRemove, HWND hwndNext)", "void",
    MOUSE,      "WM_SETCURSOR",         "OnSetCursor",          "(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg)", "BOOL",
    GENERAL,    "WM_SYSCOMMAND",        "OnSysCommand",         "(HWND hwnd, UINT cmd, int x, int y)", "void",
    MDI,        "WM_MDICREATE",         "OnMDICreate",          "(HWND hwnd, const LPMDICREATESTRUCT lpmcs)", "HWND",
    MDI,        "WM_MDIDESTROY",        "OnMDIDestroy",         "(HWND hwnd, HWND hwndDestroy)", "void",
    MDI,        "WM_MDIACTIVATE",       "OnMDIActivate",        "(HWND hwnd, BOOL fActive, HWND hwndActivate, HWND hwndDeactivate)", "void",
    MDI,        "WM_MDIRESTORE",        "OnMDIRestore",         "(HWND hwnd, HWND hwndRestore)","void",
    MDI,        "WM_MDINEXT",           "OnMDINext",            "(HWND hwnd, HWND hwndCur, BOOL fPrev)", "HWND",
    MDI,        "WM_MDIMAXIMIZE",       "OnMDIMaximize",        "(HWND hwnd, HWND hwndMaximize)", "void",
    MDI,        "WM_MDITILE",           "OnMDITile",            "(HWND hwnd, UINT cmd)", "BOOL",
    MDI,        "WM_MDICASCADE",        "OnMDICascade",         "(HWND hwnd, UINT cmd)", "BOOL",
    MDI,        "WM_MDIICONARRANGE",    "OnMDIIconArrange",     "(HWND hwnd)", "void",
    MDI,        "WM_MDIGETACTIVE",      "OnMDIGetActive",       "(HWND hwnd)", "HWND",
    MDI,        "WM_MDISETMENU",        "OnMDISetMenu",         "(HWND hwnd, BOOL fRefresh, HMENU hmenuFrame, HMENU hmenuWindow)", "HMENU",
    GENERAL,    "WM_CHILDACTIVATE",     "OnChildActivate",      "(HWND hwnd)", "void",
    GENERAL,    "WM_INITDIALOG",        "OnInitDialog",         "(HWND hwnd, HWND hwndFocus, LPARAM lParam)", "BOOL",
    GENERAL,    "WM_NEXTDLGCTL",        "OnNextDlgCtl",         "(HWND hwnd, HWND hwndSetFocus, BOOL fNext)", "HWND",
    MOUSE,      "WM_PARENTNOTIFY",      "OnParentNotify",       "(HWND hwnd, UINT msg, HWND hwndChild, int idChild)", "void",
    GENERAL,    "WM_ENTERIDLE",         "OnEnterIdle",          "(HWND hwnd, UINT source, HWND hwndSource)", "void",
    GENERAL,    "WM_GETDLGCODE",        "OnGetDlgCode",         "(HWND hwnd, LPMSG lpmsg)", "UINT",
    GENERAL,    "WM_CTLCOLORBTN",       "OnCtlColorBtn",        "(HWND hwnd, HDC hdc, HWND hwndChild, int type)", "HBRUSH",
	GENERAL,    "WM_CTLCOLORDLG",       "OnCtlColorDlg",        "(HWND hwnd, HDC hdc, HWND hwndChild, int type)", "HBRUSH",
	GENERAL,    "WM_CTLCOLOREDIT",      "OnCtlColorEdit",       "(HWND hwnd, HDC hdc, HWND hwndChild, int type)", "HBRUSH",
	GENERAL,    "WM_CTLCOLORLISTBOX",   "OnCtlColorListbox",    "(HWND hwnd, HDC hdc, HWND hwndChild, int type)", "HBRUSH",
	GENERAL,    "WM_CTLCOLORMSGBOX",    "OnCtlColorMsgbox",     "(HWND hwnd, HDC hdc, HWND hwndChild, int type)", "HBRUSH",
	GENERAL,    "WM_CTLCOLORSCROLLBAR", "OnCtlColorScrollbar",  "(HWND hwnd, HDC hdc, HWND hwndChild, int type)", "HBRUSH",
	GENERAL,    "WM_CTLCOLORSTATIC",    "OnCtlColorStatic",     "(HWND hwnd, HDC hdc, HWND hwndChild, int type)", "HBRUSH",
	GENERAL,    "WM_SETFONT",           "OnSetFont",            "(HWND hwndCtl, HFONT hfont, BOOL fRedraw)", "void",
    GENERAL,    "WM_GETFONT",           "OnGetFont",            "(HWND hwnd)", "HFONT",
    GENERAL,    "WM_DRAWITEM",          "OnDrawItem",           "(HWND hwnd, const DRAWITEMSTRUCT * lpDrawItem)", "void",
    GENERAL,    "WM_MEASUREITEM",       "OnMeasureItem",        "(HWND hwnd, MEASUREITEMSTRUCT * lpMeasureItem)", "void",
    GENERAL,    "WM_DELETEITEM",        "OnDeleteItem",         "(HWND hwnd, const DELETEITEMSTRUCT * lpDeleteItem)", "void",
    GENERAL,    "WM_COMPAREITEM",       "OnCompareItem",        "(HWND hwnd, const COMPAREITEMSTRUCT * lpCompareItem)", "int",
    GENERAL,    "WM_QUEUESYNC",         "OnQueueSync",          "(HWND hwnd)", "void",
	GENERAL,    "WM_COMMNOTIFY",        "OnCommNotify",         "(HWND hwnd, int cid, UINT flags)", "void",
    GENERAL,    "WM_DISPLAYCHANGE",     "OnDisplayChange",      "(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen)", "void",
    GENERAL,    "WM_DEVICECHANGE",      "OnDeviceChange",       "(HWND hwnd, UINT uEvent, DWORD dwEventData)", "BOOL",
    GENERAL,    "WM_CONTEXTMENU",       "OnContextMenu",        "(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos)", "void",
	GENERAL,    "WM_COPYDATA",			"OnCopyData",			"(HWND hwnd, HWND hwndFrom, PCOPYDATASTRUCT pcds)", "BOOL"
};
//
// count elements of msginfo structure
//
const int  numMessages = sizeof(msginfo) / sizeof(msginfo[0]);

// array for selected messages in the list box
extern int selItems[numMessages];
extern int nItems;

#endif // !MSGCRACKWIZARD_H
