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

#include "stdafx.h"
#include "msgcrackwizard.h"
#include "resource.h"

HBITMAP		hbmpKeyboard, hbmpMouse, hbmpClipboard;
HBITMAP		hbmpGeneral, hbmpNonClient, hbmpMDI, hbmpWindow;

//
// fill the list box with the messages (and apply filters)
//
void FillListBox(HWND hwnd, UINT filter)
{
	int itemdx;

	// first clear all items if any
	SendDlgItemMessage(hwnd, IDC_MESSAGES, LB_RESETCONTENT, 0, 0);

	// add messages to listbox
	for (int i = 0; i < numMessages; i++)
	{
		// check for filter
		if (msginfo[i].fType & fFilter)
		{
            itemdx = (int)SendDlgItemMessage (hwnd, IDC_MESSAGES, LB_ADDSTRING, 0, (LPARAM)msginfo[i].WM_msg); 
			// add a bitmap index depending on type
			SendDlgItemMessage (hwnd, IDC_MESSAGES, LB_SETITEMDATA, (WPARAM)itemdx, (LPARAM)msginfo[i].fType);
		}
	}

}

// 
// configure controls
//
void SetupControls(HWND hwnd)
{
    FillListBox(hwnd, fFilter);	

	// put fonts
	SendDlgItemMessage(hwnd, IDC_HANDLEMSG, WM_SETFONT, (WPARAM)GetStockObject(ANSI_FIXED_FONT), 0);
	SendDlgItemMessage(hwnd, IDC_MSGFUNCTION,WM_SETFONT, (WPARAM)GetStockObject(ANSI_FIXED_FONT), 0);

	// disable necessary controls when there is no selection on list
	EnableControls (hwnd, FALSE);
	SendDlgItemMessage(hwnd, IDC_RADWINDOW, BM_SETCHECK, BST_CHECKED, 0);
}

//
// Updates the program interface
//
void UpdateUI(HWND hwnd)
{
	char  szMacro[BUFFER];
	char  szSuffix[BUFFER];
	char  szFuncName[BUFFER];
	char  szFuncDef[BUFFER];
	char  szParams[BUFFER];
	char  szType[BUFFER];
	char  szMessage[BUFFER];

	ZeroMemory (szMacro, sizeof(szMacro));
	ZeroMemory (szFuncDef, sizeof(szFuncDef));

	// locate the selected messages

	nItems = (int)SendDlgItemMessage (hwnd, IDC_MESSAGES, LB_GETSELITEMS, 
		numMessages, (LPARAM)&selItems);

	// update number of selected messages static box
	char szStatic[255];
	wsprintf(szStatic, "%d message(s) selected.", nItems);
	SetDlgItemText(hwnd, IDC_NUMSELECT, szStatic);

	if (nItems)
	{

		// update interface with all selected messages

		for (int index = 0; index < nItems; index++)
		{
			SendDlgItemMessage(hwnd, IDC_MESSAGES, LB_GETTEXT, selItems[index], (LPARAM) szMessage); 

			// construct HANDLE_MSG macro

			if ( (IsDlgButtonChecked(hwnd, IDC_MAKEWNDPROC) == BST_CHECKED) &&
				(IsDlgButtonChecked(hwnd, IDC_DIALOG)   == BST_CHECKED ) )
				strcat (szMacro, "HANDLE_MSG (hwndDlg, ");
			else
				strcat (szMacro, "HANDLE_MSG (hwnd, ");

			strcat (szMacro, szMessage);

			// search for message parameters in the structure
			for (int j=0; j < numMessages; j++)
			{
				if (!strcmp(msginfo[j].WM_msg, szMessage))
				{
					strcpy(szFuncName, msginfo[j].fnname);
					strcpy(szParams,   msginfo[j].params);
					strcpy(szType,     msginfo[j].rettype);
				}
			}

			GetDlgItemText(hwnd, IDC_WINDOWID, szSuffix, 100);  

			// construct both complete macro and functions

			strcat (szMacro, ", ");
			strcat (szMacro, szSuffix);
			strcat (szMacro, "_");
			strcat (szMacro, szFuncName);
			strcat (szMacro, ");");
			strcat (szMacro, "\r\n");

			strcat (szFuncDef, szType);
			strcat (szFuncDef, " ");
			strcat (szFuncDef, szSuffix);
			strcat (szFuncDef, "_");
			strcat (szFuncDef, szFuncName);
			strcat (szFuncDef, szParams);
			strcat (szFuncDef, "\r\n");
		}
	}
	else
	{
		strcpy (szMacro, "");
		strcpy (szFuncDef, "");
	}

	// put text to edit boxes
	SetDlgItemText(hwnd, IDC_HANDLEMSG, szMacro);
	SetDlgItemText(hwnd, IDC_MSGFUNCTION, szFuncDef);
}

// disable some controls on the dialog
void EnableControls(HWND hwnd, BOOL fEnabled)
{
    EnableWindow(GetDlgItem(hwnd, IDC_WINDOWID), fEnabled);
	EnableWindow(GetDlgItem(hwnd, IDC_MAKEWNDPROC), fEnabled);
	EnableWindow(GetDlgItem(hwnd, IDC_DIALOG), fEnabled);
	EnableWindow(GetDlgItem(hwnd, IDC_RADWINDOW), fEnabled);
	EnableWindow(GetDlgItem(hwnd, IDC_COPYMACRO), fEnabled);
	EnableWindow(GetDlgItem(hwnd, IDC_COPYFUNC), fEnabled);
}

//
// select bitmap for ownerdrawn control based on msginfo[].fType
//
HBITMAP SelectItemBitmap(const DRAWITEMSTRUCT* lpDrawItem)
{
	HBITMAP hPic;

	// select bitmap for listbox
	if (lpDrawItem->CtlID == IDC_MESSAGES)
	{
		switch (lpDrawItem->itemData)
		{
		case KEYBOARD:
			hPic = hbmpKeyboard;
			break;

		case MOUSE:
			hPic = hbmpMouse;
			break;

		case CLIPBOARD:
			hPic = hbmpClipboard;
			break;

		case GENERAL:
			hPic = hbmpGeneral;
			break;

		case MDI:
			hPic = hbmpMDI;
			break;

		case NONCLIENT:
			hPic = hbmpNonClient;
			break;
		}
	}

	// select bitmap for WindowID combobox
	if (lpDrawItem->CtlID == IDC_WINDOWID)
		hPic = hbmpWindow;
	
	return hPic;
}

// draw the ownerdrawn bitmap
//
void DrawItemBitmap (const DRAWITEMSTRUCT* lpDrawItem, HBITMAP hPic)
{
	HDC		hdcMem;
	HGDIOBJ hbmpOld;
	char    szTextBuf[MAX_PATH];

	// Erase rectangle 
	FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, (HBRUSH)(COLOR_WINDOW+1));

	hdcMem = CreateCompatibleDC(lpDrawItem->hDC); 
	hbmpOld = SelectObject(hdcMem, hPic); 

	BitBlt(lpDrawItem->hDC, 
		lpDrawItem->rcItem.left, lpDrawItem->rcItem.top, 
		lpDrawItem->rcItem.right - lpDrawItem->rcItem.left, 
		lpDrawItem->rcItem.bottom - lpDrawItem->rcItem.top, 
		hdcMem, 0, 0, SRCCOPY);

	// Draw Text
	SendMessage(lpDrawItem->hwndItem, LB_GETTEXT, 
		lpDrawItem->itemID, (LPARAM) szTextBuf); 

	TextOut(lpDrawItem->hDC, lpDrawItem->rcItem.left + 18,
		lpDrawItem->rcItem.top, szTextBuf, (int)strlen(szTextBuf));

	SelectObject(hdcMem, hbmpOld); 
	DeleteDC(hdcMem);
}