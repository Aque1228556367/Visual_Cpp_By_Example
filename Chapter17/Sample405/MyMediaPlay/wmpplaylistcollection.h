#if !defined(AFX_WMPPLAYLISTCOLLECTION_H__3B3B8C01_98B6_4666_97C7_7FC3A060C963__INCLUDED_)
#define AFX_WMPPLAYLISTCOLLECTION_H__3B3B8C01_98B6_4666_97C7_7FC3A060C963__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CWMPPlaylist;
class CWMPPlaylistArray;

/////////////////////////////////////////////////////////////////////////////
// CWMPPlaylistCollection wrapper class

class CWMPPlaylistCollection : public COleDispatchDriver
{
public:
	CWMPPlaylistCollection() {}		// Calls COleDispatchDriver default constructor
	CWMPPlaylistCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPPlaylistCollection(const CWMPPlaylistCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CWMPPlaylist newPlaylist(LPCTSTR bstrName);
	CWMPPlaylistArray getAll();
	CWMPPlaylistArray getByName(LPCTSTR bstrName);
	void remove(LPDISPATCH pItem);
	void setDeleted(LPDISPATCH pItem, BOOL varfIsDeleted);
	BOOL isDeleted(LPDISPATCH pItem);
	CWMPPlaylist importPlaylist(LPDISPATCH pItem);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPPLAYLISTCOLLECTION_H__3B3B8C01_98B6_4666_97C7_7FC3A060C963__INCLUDED_)
