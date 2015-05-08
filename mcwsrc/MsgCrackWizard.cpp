/******************************************************************************
    
    Windows API Message Cracker Wizard Tool
    for easier use of WINDOWSX.H message cracking macros

    (c) 2003-2005 Hernan Di Pietro

    Release 2.1

    version history
    1.0 - first release
    1.2   + multiple message selection feature
          + added missing message crackers for WM_HOTKEY and WM_COPYDATA
          + fixed small interface bugs
    2.0   + added WM_CTLCOLORxxx message crackers         
          + added show/hide target code
          + added enable/disable stay on top
          + added window transparency options for 2000/XP
          + added message filter
          + added bitmaps on list box
		  + added "No heading comments" option
		  + added "No TODO comments" option
          + fixed keyboard logic and tab stops
    2.1   - fixed clipboard-copy bug (Thanks to Agnel Kurian mailto:agnel.kurian@gmail.com)
                    
*******************************************************************************

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
#include "stdafx.h"
#include "MsgCrackWizard.h"
#include "resource.h"

// globals
int                 selItems[numMessages];
int                 nItems;
MEASUREITEMSTRUCT   mis;
UINT                fFilter;


///////////////////////////////////////////////////////////////////////////////
//  Process WM_CREATE message for window/dialog: Cls
//
BOOL Cls_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    // Allocate memory for the message list box
    SendDlgItemMessage (hwnd, IDC_MESSAGES, LB_INITSTORAGE, (WPARAM) numMessages,
        (LPARAM) sizeof(msginfo));  
    
    // load bitmaps for ownerdrawn controls
    hbmpKeyboard  = (HBITMAP)LoadImage (hInstance, MAKEINTRESOURCE(IDB_KEYBOARD), 
                          IMAGE_BITMAP, 16, 16, NULL);

    hbmpMouse     = (HBITMAP)LoadImage (hInstance, MAKEINTRESOURCE(IDB_MOUSE)   , 
                          IMAGE_BITMAP, 16, 16, NULL);

    hbmpClipboard = (HBITMAP)LoadImage (hInstance, MAKEINTRESOURCE(IDB_CLIPBOARD),
                          IMAGE_BITMAP, 16, 16, NULL);

    hbmpMDI       = (HBITMAP)LoadImage (hInstance, MAKEINTRESOURCE(IDB_MDI),
                          IMAGE_BITMAP, 16, 16, NULL);

    hbmpNonClient = (HBITMAP)LoadImage (hInstance, MAKEINTRESOURCE(IDB_NONCLIENT),
                          IMAGE_BITMAP, 16, 16, NULL);

    hbmpGeneral   = (HBITMAP)LoadImage (hInstance, MAKEINTRESOURCE(IDB_GENERAL),
                          IMAGE_BITMAP, 16, 16, NULL);

	hbmpWindow    = (HBITMAP)LoadImage (hInstance, MAKEINTRESOURCE(IDB_WINDOW),
		                  IMAGE_BITMAP, 16, 16, NULL);

    
    // Disable window transparency option if not present on current OS
    HMODULE hUser32;
    HMENU   hMenu;

    hUser32 = LoadLibrary("user32.dll");
    if (GetProcAddress (hUser32, "SetLayeredWindowAttributes") == NULL)
    {
        // not present on USER32.DLL, disable menus
        hMenu = GetMenu(hwnd);
        EnableMenuItem(hMenu, ID_WINDOWTRANSPARENCY_10, MF_GRAYED);
        EnableMenuItem(hMenu, ID_WINDOWTRANSPARENCY_25, MF_GRAYED);
        EnableMenuItem(hMenu, ID_WINDOWTRANSPARENCY_50, MF_GRAYED);
        EnableMenuItem(hMenu, ID_WINDOWTRANSPARENCY_75, MF_GRAYED);
        DrawMenuBar(hwnd);
    }
        
    FreeLibrary(hUser32);

    // Set message filter flags to include all
    fFilter = NOFILTER;

    // Setup Window Controls (fill list box,etc)
    SetupControls(hwnd);
    return 1L;
}

//
// process WM_ONCOMMAND
//
void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

    HMENU   hMenu;
    BYTE    bAlpha;         // window transparency alpha
    HMODULE hUser32;
    PSLWA   pSetLayeredWndAttr;

    switch (id)
    {
        // menus
        
    case ID_HELP_ABOUT:
        DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlg_DlgProc);
        break;

    case ID_FILE_EXIT:
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    case ID_EDIT_COPYMACRO:
        SendMessage (hwnd, WM_COMMAND, MAKEWPARAM(IDC_COPYMACRO, 0), 0);
        break;

    case ID_EDIT_COPYFUNCTION:
        SendMessage (hwnd, WM_COMMAND, MAKEWPARAM(IDC_COPYFUNC, 0), 0);
        break;
        
	case IDC_FILTERBTN:				// filter button on dialogbox
    case ID_EDIT_MESSAGEFILTERS:
		
        int iRes;
        iRes = (int)DialogBox (GetModuleHandle(0), MAKEINTRESOURCE(IDD_FILTER), 
            hwnd, FilterDlg_DlgProc);

        // update listbox with selected filters
        if (iRes == IDOK)
            FillListBox(hwnd, fFilter);
        
		break;

		
    case ID_VIEW_SHOWTARGETCODE:
        // collapse or expand the target code group
        RECT  rect;
        int   cyClient, cxClient;
        int   cyResize;
        
        GetWindowRect(hwnd, &rect);
        cyClient = rect.bottom - rect.top;
        cxClient = rect.right - rect.left;

        hMenu = GetMenu(hwnd);      

        // invert menu checkmark
        CheckMenuItem (hMenu, ID_VIEW_SHOWTARGETCODE, CheckMenuItem(hMenu, ID_VIEW_SHOWTARGETCODE, 
                        MF_CHECKED) == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED);

        // resize the window

        cyResize = 190;		// resize amount in pixels

        if (GetMenuState(hMenu, ID_VIEW_SHOWTARGETCODE, MF_BYCOMMAND) & MF_CHECKED) 
            cyClient += cyResize;
        else
            cyClient -= cyResize;

        SetWindowPos(hwnd, NULL, NULL, NULL, cxClient, cyClient, SWP_NOZORDER | SWP_NOMOVE);
        break;

    case ID_VIEW_STAYONTOP:
        // Enable-disable topmost window
        hMenu = GetMenu(hwnd);

        // invert menu checkmark
        CheckMenuItem (hMenu, ID_VIEW_STAYONTOP, CheckMenuItem(hMenu, ID_VIEW_STAYONTOP, 
                        MF_CHECKED) == MF_CHECKED ? MF_UNCHECKED : MF_CHECKED);

        if (GetMenuState(hMenu, ID_VIEW_STAYONTOP, MF_BYCOMMAND) & MF_CHECKED)
            SetWindowPos (hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        else
            SetWindowPos (hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        break;

        // Make Window Transparent (2000/XP Only)

    case ID_WINDOWTRANSPARENCY_SOLID:
        SetWindowLong (hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
        UpdateWindow (hwnd);
        break;

    case ID_WINDOWTRANSPARENCY_10: 
    case ID_WINDOWTRANSPARENCY_25: 
    case ID_WINDOWTRANSPARENCY_50:
    case ID_WINDOWTRANSPARENCY_75:

        if (id == ID_WINDOWTRANSPARENCY_SOLID) bAlpha = 255;
        if (id == ID_WINDOWTRANSPARENCY_10)    bAlpha = 192;
        if (id == ID_WINDOWTRANSPARENCY_25)    bAlpha = 128;
        if (id == ID_WINDOWTRANSPARENCY_50)    bAlpha = 64;
        if (id == ID_WINDOWTRANSPARENCY_75)    bAlpha = 25;

        // modify window style        
        SetWindowLong (hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

        // call function from USER32
        hUser32 = LoadLibrary("user32.dll");
        pSetLayeredWndAttr = (PSLWA)GetProcAddress (hUser32, "SetLayeredWindowAttributes");
        pSetLayeredWndAttr (hwnd, 0, bAlpha, LWA_ALPHA);
        FreeLibrary(hUser32);
        break;

        //
        // WM_COMMAND for Buttons
        //

    case IDC_COPYMACRO:
        CopyMacroToCB(hwnd);
        break;

    case IDC_COPYFUNC:
        CopyFuncToCB(hwnd);
        break;

    case IDC_CLOSE:
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    case IDC_WINDOWID:
        switch (codeNotify)
        {
            // update the macro/function edit boxes when the user changes
            // the WindowID combo box
        case CBN_SELCHANGE:
        case CBN_EDITCHANGE:
            UpdateUI(hwnd);
            break;
        }
        break;

    case IDC_MESSAGES:
        switch (codeNotify)
        {
        case LBN_SELCHANGE:
            // update the edit boxes and enable/disable the check when the list box is clicked
            if (SendDlgItemMessage(hwnd, IDC_MESSAGES, LB_GETSELCOUNT, 0, 0) == 0)
                EnableControls(hwnd, FALSE);
            else
                EnableControls (hwnd, TRUE);

            UpdateUI(hwnd);
            break;
        }
        break;

    case IDC_MAKEWNDPROC:
        // enable the radio buttons when 'make wnd proc' is checked
        EnableWindow(GetDlgItem(hwnd, IDC_DIALOG), 
            IsDlgButtonChecked(hwnd, IDC_MAKEWNDPROC) == BST_CHECKED ? TRUE :FALSE);
        EnableWindow(GetDlgItem(hwnd, IDC_RADWINDOW),
            IsDlgButtonChecked(hwnd, IDC_MAKEWNDPROC) == BST_CHECKED ? TRUE : FALSE);
        break;      

    case IDC_DIALOG:
    case IDC_RADWINDOW:
        UpdateUI(hwnd);
        break;
            
    }
}

//
//  Process WM_DRAWITEM message for window/dialog: Cls
//
void Cls_OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT * lpDrawItem)
{
    char    szTextBuf[MAX_PATH];
    int     x   = lpDrawItem->rcItem.left;
    int     y   = lpDrawItem->rcItem.top;

    switch (lpDrawItem->itemAction)
    {
    case ODA_DRAWENTIRE:
    case ODA_SELECT:

        // Draw message bitmap depending on type
        DrawItemBitmap (lpDrawItem, SelectItemBitmap(lpDrawItem));

        if (lpDrawItem->itemState & ODS_SELECTED)
        {
            // Draw selection state (uses new RECT to avoid erasing bitmap)     
            RECT rsel;
            CopyRect(&rsel, &lpDrawItem->rcItem);
            rsel.left += 16;

            SetBkMode(lpDrawItem->hDC, TRANSPARENT);
            SetTextColor(lpDrawItem->hDC, RGB(0xff, 0xff, 0xff));
            FillRect(lpDrawItem->hDC, &rsel, (HBRUSH)(COLOR_HIGHLIGHT+1));

            // Draw Text
            SendMessage(lpDrawItem->hwndItem, LB_GETTEXT, 
                lpDrawItem->itemID, (LPARAM) szTextBuf); 
            SetBkMode(lpDrawItem->hDC, TRANSPARENT);
            TextOut(lpDrawItem->hDC, lpDrawItem->rcItem.left + 18,
                lpDrawItem->rcItem.top, szTextBuf, (int)strlen(szTextBuf));
        }
        else
        {
            // Normal State
            SetTextColor(lpDrawItem->hDC, 0);
            DrawItemBitmap(lpDrawItem,SelectItemBitmap(lpDrawItem));
			
        }
        break;
    }
    
}

//
//  Process WM_MEASUREITEM message for window/dialog: Cls
//
void Cls_OnMeasureItem(HWND hwnd, MEASUREITEMSTRUCT * lpMeasureItem)
{
    // Set control size
    lpMeasureItem->itemHeight = 16;
}

void Cls_OnClose(HWND hwnd)
{
    // destroy allocated resources
    DeleteObject ((HBITMAP)hbmpKeyboard);
    DestroyWindow(hwnd);
}

void Cls_OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}


//
//  Process WM_INITDIALOG message for window/dialog: FilterDlg
//
BOOL FilterDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    // Mark checkbox depending on filter settings

    CheckDlgButton (hwnd, IDC_FGENERAL, ( fFilter & GENERAL? BST_CHECKED : BST_UNCHECKED));
    CheckDlgButton (hwnd, IDC_FKEYBOARD,( fFilter & KEYBOARD? BST_CHECKED : BST_UNCHECKED));
    CheckDlgButton (hwnd, IDC_FCLIPBRD, ( fFilter & CLIPBOARD? BST_CHECKED : BST_UNCHECKED));
    CheckDlgButton (hwnd, IDC_FNCLIENT, ( fFilter & NONCLIENT? BST_CHECKED : BST_UNCHECKED));
    CheckDlgButton (hwnd, IDC_FMDI,     ( fFilter & MDI? BST_CHECKED : BST_UNCHECKED));
    CheckDlgButton (hwnd, IDC_FMOUSE,   ( fFilter & MOUSE? BST_CHECKED : BST_UNCHECKED));

    return 1L;
}
//
//  Process WM_COMMAND message for window/dialog: AboutDlg
//
void AboutDlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    EndDialog(hwnd, IDOK);
}

 //
// AboutDlg  Dialog Procedure
//
BOOL CALLBACK AboutDlg_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        HANDLE_MSG (hwndDlg, WM_COMMAND, AboutDlg_OnCommand);
            //// TODO: Add dialog message crackers here...

    default: return FALSE;
    }
}

//
//  Process WM_COMMAND message for window/dialog: FilterDlg
//
void FilterDlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
        // apply filters

        if (IsDlgButtonChecked(hwnd, IDC_FMOUSE) == BST_CHECKED)
            fFilter |= MOUSE;
        else
            fFilter &= ~MOUSE;

        if (IsDlgButtonChecked(hwnd, IDC_FKEYBOARD) == BST_CHECKED)
            fFilter |= KEYBOARD;
        else
            fFilter &= ~KEYBOARD;

        if (IsDlgButtonChecked(hwnd, IDC_FCLIPBRD) == BST_CHECKED)
            fFilter |= CLIPBOARD;
        else
            fFilter &= ~CLIPBOARD;

        if (IsDlgButtonChecked(hwnd, IDC_FMDI) == BST_CHECKED)
            fFilter |= MDI;
        else
            fFilter &= ~MDI;

        if (IsDlgButtonChecked(hwnd, IDC_FGENERAL) == BST_CHECKED)
            fFilter |= GENERAL;
        else
            fFilter &= ~GENERAL;

        if (IsDlgButtonChecked(hwnd, IDC_FNCLIENT) == BST_CHECKED)
            fFilter |= NONCLIENT;
        else
            fFilter &= ~NONCLIENT;



        EndDialog(hwnd, IDOK);
        break;

    case IDCANCEL:
        EndDialog(hwnd, IDCANCEL);
        break;
    }
}


//
// FilterDlg  Dialog Procedure
//
BOOL CALLBACK FilterDlg_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        HANDLE_MSG (hwndDlg, WM_INITDIALOG, FilterDlg_OnInitDialog);
        HANDLE_MSG (hwndDlg, WM_COMMAND, FilterDlg_OnCommand);

            //// TODO: Add dialog message crackers here...

    default: return FALSE;
    }
}



//
// window (main dialog) procedure
//
BOOL CALLBACK MainDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        HANDLE_MSG(hwnd, WM_CLOSE,      Cls_OnClose);
        HANDLE_MSG(hwnd, WM_DESTROY,    Cls_OnDestroy);
        HANDLE_MSG(hwnd, WM_COMMAND,    Cls_OnCommand);
        HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
        HANDLE_MSG (hwnd, WM_DRAWITEM,  Cls_OnDrawItem);
        HANDLE_MSG (hwnd, WM_MEASUREITEM, Cls_OnMeasureItem);
        
    default:
        return FALSE;
        //return DefDlgProc(hwnd, msg, wParam, lParam);
    } 
}


//
// WINMAIN... the fun begins here!
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int nCmdShow)
{
    static char szClassName[] = "MessageCrackerWizard";
    HWND        hwnd;
    MSG         msg;
    WNDCLASSEX  wcex;
    HACCEL      hAccel;

    // Get the class for the system dialog class
    wcex.cbSize         = sizeof(wcex);
    GetClassInfoEx(NULL, "#32770", &wcex);
    wcex.style &= ~CS_GLOBALCLASS;

    // Register class
    wcex.lpszClassName  = szClassName;
    wcex.cbClsExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hbrBackground  = (HBRUSH) (COLOR_BTNFACE+1);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hIcon          = LoadIcon (hInstance, MAKEINTRESOURCE( IDI_MCWICON));
    wcex.hIconSm        = LoadIcon (hInstance, MAKEINTRESOURCE( IDI_MCWICON));
    wcex.cbWndExtra     = DLGWINDOWEXTRA;
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU1);
 
    if (!RegisterClassEx(&wcex))
    {
        MessageBox (NULL, "Error in RegisterClassEx", "error", MB_ICONERROR);
        return 0; 
    }

    // initialize common controls, accelerators
    InitCommonControls();
    hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCEL));

    // create the dialog    
    hwnd = CreateDialog (hInstance, MAKEINTRESOURCE(IDD_WIZARD), 0, MainDlgProc);

    if (hwnd == NULL)
    {
        MessageBox (NULL, "Can't create Main window", "error", MB_ICONERROR);
        return 0;
    }

    ShowWindow (hwnd, SW_NORMAL);

    // Message Loop
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        if (!TranslateAccelerator(hwnd, hAccel, &msg))
        {
            if (!IsDialogMessage(hwnd, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return (int)msg.wParam;
}

