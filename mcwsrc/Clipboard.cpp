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

//
// Copia la macro al clipboard
//
void CopyMacroToCB(HWND hwnd)
{
    HGLOBAL hGlobal;
	char    WindowID[BUFFER];
	char*	pGlobalStr;
	char    szMacro[BUFFER];
	char    szWndProcHdr[] = "_WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)\r\n";
	char    szDlgProcHdr[] = "_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)\r\n";
    int length;	//	04MAR2005 ACJK - length of text copied by EM_GETLINE
	// guardar el Window ID, y la macro
	GetDlgItemText(hwnd, IDC_WINDOWID,  WindowID, BUFFER);
	GetDlgItemText(hwnd, IDC_HANDLEMSG, szMacro, BUFFER);

	// reservar memoria para el clipboard
	hGlobal = GlobalAlloc(GHND | GMEM_SHARE, cbStrBuf);
	pGlobalStr = (char*)GlobalLock(hGlobal);

	if (IsDlgButtonChecked(hwnd, IDC_MAKEWNDPROC) == BST_CHECKED)
	{
		// construir todo el wndproc
		if (IsDlgButtonChecked(hwnd, IDC_RADWINDOW) == BST_CHECKED)
		{
			// WNDPROC
			// encabezado
			
			// skip comments if checkbox is enabled
			if (IsDlgButtonChecked(hwnd, IDC_NOHEADINGCOMMENTS) == BST_UNCHECKED)
			{
				strcat (pGlobalStr, "//\r\n");
				strcat (pGlobalStr, "// ");
				strcat (pGlobalStr, WindowID);
				strcat (pGlobalStr, " ");
				strcat (pGlobalStr, " Window Procedure\r\n//\r\n");
			}
			strcat (pGlobalStr, "LRESULT CALLBACK ");
			strcat (pGlobalStr, WindowID);
			strcat (pGlobalStr, szWndProcHdr);
			strcat (pGlobalStr, "{\r\n");
			strcat (pGlobalStr, "\tswitch(msg)\r\n");
			strcat (pGlobalStr, "\t{\r\n");
			for (int i = 0; i < nItems; i++)
			{
				// set first word prior to EM_GETLINE

				*(WORD*)szMacro = BUFFER;
				length = SendDlgItemMessage(hwnd, IDC_HANDLEMSG, EM_GETLINE, i, (LPARAM)szMacro);	// 04MAR2005 ACJK: Save return value in length
				szMacro[length] = '\0';	// 04MAR2005 ACJK: According to MSDN EM_GETLINE does put '\0' at the end
                strcat (pGlobalStr, "\t");
                strcat (pGlobalStr, szMacro);
				strcat (pGlobalStr, "\r\n");
			}

			if (IsDlgButtonChecked(hwnd, IDC_NOTODOCOMMENTS) == BST_UNCHECKED)
                strcat (pGlobalStr, "\r\n\t\t//// TODO: Add window message crackers here...\r\n");

			strcat (pGlobalStr, "\r\n\tdefault: return DefWindowProc (hwnd, msg, wParam, lParam);");
			strcat (pGlobalStr, "\r\n\t}");
			strcat (pGlobalStr, "\r\n}");
		}

		// Dialog Procedure

		else if (IsDlgButtonChecked(hwnd, IDC_DIALOG) == BST_CHECKED)
		{
			// DLGPROC (modal)
			// encabezado

			// skip comments?
			if (IsDlgButtonChecked(hwnd, IDC_NOHEADINGCOMMENTS) == BST_UNCHECKED)
			{
				strcat (pGlobalStr, "//\r\n");
				strcat (pGlobalStr, "// ");
				strcat (pGlobalStr, WindowID);
				strcat (pGlobalStr, " ");
				strcat (pGlobalStr, " Dialog Procedure\r\n//\r\n");
			}
			strcat (pGlobalStr, "BOOL CALLBACK ");
			strcat (pGlobalStr, WindowID);
			strcat (pGlobalStr, szDlgProcHdr);
			strcat (pGlobalStr, "{\r\n");
			strcat (pGlobalStr, "\tswitch(msg)\r\n");
			strcat (pGlobalStr, "\t{\r\n");
			for (int i = 0; i < nItems; i++)
			{
				*(WORD*)szMacro = BUFFER;
				length = SendDlgItemMessage(hwnd, IDC_HANDLEMSG, EM_GETLINE, i, (LPARAM)szMacro);	// 04MAR2005 ACJK: Save return value in length
				szMacro[length] = '\0';	// 04MAR2005 ACJK: According to MSDN EM_GETLINE does put '\0' at the end
                strcat (pGlobalStr, "\t");
                strcat (pGlobalStr, szMacro);
				strcat (pGlobalStr, "\r\n");
			}

			if (IsDlgButtonChecked(hwnd, IDC_NOTODOCOMMENTS) == BST_UNCHECKED)
                strcat (pGlobalStr, "\r\n\t\t//// TODO: Add dialog message crackers here...\r\n");

			strcat (pGlobalStr, "\r\n\tdefault: return FALSE;");
			strcat (pGlobalStr, "\r\n\t}");
			strcat (pGlobalStr, "\r\n}");
		}
	}
	else
	{
		// macro sola sin windowproc
		strcpy (pGlobalStr, szMacro);
	}

	GlobalUnlock(hGlobal);

	OpenClipboard(hwnd);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hGlobal);
    CloseClipboard();
}

// copia la funcion al clipboard
void CopyFuncToCB(HWND hwnd)
{
	HGLOBAL hGlobal;
	char*	pGlobalStr;
	char   WindowID[BUFFER];
	char   szFunc[BUFFER];
	char   szMessage[BUFFER];

	// guardar el Window ID, encabezado de la funcion y nombre de mensaje
	GetDlgItemText(hwnd, IDC_WINDOWID,  WindowID, BUFFER);
    
 	// alojar memoria
	hGlobal = GlobalAlloc(GHND | GMEM_SHARE, cbStrBuf);
	pGlobalStr = (char*)GlobalLock(hGlobal);

	for (int i = 0; i < nItems; i++)
	{
		ZeroMemory (szMessage, sizeof(szMessage));
		ZeroMemory (szFunc,    sizeof(szFunc));
		SendDlgItemMessage(hwnd, IDC_MESSAGES, LB_GETTEXT, selItems[i], (LPARAM) szMessage); 

		// set first word of szFunc to max characters before use EM_GETLINE
        *(WORD*)szFunc = BUFFER;
		
		// now send the message to get the line text
		SendDlgItemMessage(hwnd, IDC_MSGFUNCTION, EM_GETLINE, (WPARAM) i, (LPARAM) szFunc);

		// skip comments?
		if (IsDlgButtonChecked(hwnd, IDC_NOHEADINGCOMMENTS) == BST_UNCHECKED)
		{
            strcat (pGlobalStr, "//\r\n// ");
			strcat (pGlobalStr, " Process ");
			strcat (pGlobalStr, szMessage);
			strcat (pGlobalStr, " message for window/dialog: ");
			strcat (pGlobalStr, WindowID);
			strcat (pGlobalStr, "\r\n//\r\n");
		}
		strcat (pGlobalStr, szFunc);
		strcat (pGlobalStr, "\r\n{\r\n");

		if (IsDlgButtonChecked(hwnd, IDC_NOTODOCOMMENTS) == BST_UNCHECKED)
            strcat (pGlobalStr, "\t// TODO: Add your message processing code here...");

		strcat (pGlobalStr, "\r\n}\r\n\r\n");
	}

	// desbloquear memoria y copiar al clipboard el texto
	GlobalUnlock(hGlobal);
	
	OpenClipboard(hwnd);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hGlobal);
    CloseClipboard();
     
}