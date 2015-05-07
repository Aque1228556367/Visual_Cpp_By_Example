#if !defined(AFX_WMPMEDIA_H__4B3A4463_8963_404D_9DA8_3C2965B08F6E__INCLUDED_)
#define AFX_WMPMEDIA_H__4B3A4463_8963_404D_9DA8_3C2965B08F6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CWMPMedia wrapper class

class CWMPMedia : public COleDispatchDriver
{
public:
	CWMPMedia() {}		// Calls COleDispatchDriver default constructor
	CWMPMedia(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPMedia(const CWMPMedia& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIsIdentical(LPDISPATCH pIWMPMedia);
	CString GetSourceURL();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetImageSourceWidth();
	long GetImageSourceHeight();
	long GetMarkerCount();
	double getMarkerTime(long MarkerNum);
	CString getMarkerName(long MarkerNum);
	double GetDuration();
	CString GetDurationString();
	long GetAttributeCount();
	CString getAttributeName(long lIndex);
	CString getItemInfo(LPCTSTR bstrItemName);
	void setItemInfo(LPCTSTR bstrItemName, LPCTSTR bstrVal);
	CString getItemInfoByAtom(long lAtom);
	BOOL isMemberOf(LPDISPATCH pPlaylist);
	BOOL isReadOnlyItem(LPCTSTR bstrItemName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPMEDIA_H__4B3A4463_8963_404D_9DA8_3C2965B08F6E__INCLUDED_)
