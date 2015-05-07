// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__AC952C3A_9B6B_4319_8D6E_E7F509348A88__INCLUDED_)
#define AFX_DIB_H__AC952C3A_9B6B_4319_8D6E_E7F509348A88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
                              
#define PalVersion   0x300                                 // ��ɫ��汾

class CDib : public CObject  
{
public:
	CDib();
	virtual ~CDib();
//operations
public:
	// ���ڲ���DIB�ĺ�������
	BOOL   DrawDib(HDC, LPRECT,HGLOBAL, LPRECT,CPalette*);//��ʾλͼ
	BOOL   ConstructPalette(HGLOBAL,CPalette* );         //�����߼���ɫ��
	LPSTR  GetBits(LPSTR);                               //ȡ��λͼ���ݵ���ڵ�ַ
	DWORD  GetWidth(LPSTR);                              //ȡ��λͼ�Ŀ��
	DWORD  GetHeight(LPSTR);                             //ȡ��λͼ�ĸ߶�
	WORD   GetPalSize(LPSTR);                            //ȡ�õ�ɫ��Ĵ�С
	WORD   GetColorNum(LPSTR);                            //ȡ��λͼ��������ɫ��Ŀ
	WORD   GetBitCount(LPSTR);                            //ȡ��λͼ����ɫ���
	HGLOBAL CopyObject(HGLOBAL);                         //���ڸ���λͼ����

	BOOL   SaveFile(HGLOBAL , CFile&);                    //�洢λͼΪ�ļ�
	HGLOBAL   LoadFile(CFile&);                          //���ļ��м���λͼ


// �ڶ�ͼ����д���ʱ�����λͼ���ֽڿ�ȱ�����4�ı�������һҪ��
//	��������˺���GetRequireWidth�����������ֱȽ���������
	int     GetReqByteWidth(int );                     //ת������ֽ���GetRequireByteWidth
	long    GetRectWidth(LPCRECT );                    //ȡ������Ŀ��
	long    GetRectHeight(LPCRECT);                    //ȡ������ĸ߶�
public:
	void ClearMemory();
	void InitMembers();
public:
	LPBITMAPINFO        lpbminfo;	// ָ��BITMAPINFO�ṹ��ָ��
	LPBITMAPINFOHEADER  lpbmihrd;	//ָ��BITMAPINFOHEADER�ṹ��ָ��
	BITMAPFILEHEADER	bmfHeader;  //BITMAPFILEHEADER�ṹ
	LPSTR				lpdib;      //ָ��DIB��ָ��
	LPSTR				lpDIBBits;  // DIB����ָ��
	DWORD				dwDIBSize;  //DIB��С

	HGLOBAL				m_hDib;//DIB����ľ��
	
	RGBQUAD*			lpRgbQuag;//ָ����ɫ���ָ��
};

#endif // !defined(AFX_DIB_H__AC952C3A_9B6B_4319_8D6E_E7F509348A88__INCLUDED_)