// INFCommunityVOIP.h: interface for the CINFCommunityVOIP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCOMMUNITYVOIP_H__6F12A791_8818_478D_A570_9A17A2A91D8B__INCLUDED_)
#define AFX_INFCOMMUNITYVOIP_H__6F12A791_8818_478D_A570_9A17A2A91D8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

class CINFImage;
class DataHeader;
class CGameData;
class CD3DHanFont;

class CINFCommunityVOIP : public CINFBase  
{
public:
	CINFCommunityVOIP();
	virtual ~CINFCommunityVOIP();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void ClearWindowString(){ZERO_MEMORY(m_strInputMessage);}

private:
	BOOL OnButtonClicked();

private:
	CD3DHanFont			*   m_pFontInput;

	CINFImage*				m_pImgBackg;						// 백그라운드 이미지
	CINFImage*				m_pImgSelectMenu[3];				// 메뉴탭 선택 이미지
	CINFImage*				m_pImgOkButton[4];					// 버튼 이미지
	CINFImage*				m_pImgCancelButton[4];					// 버튼 이미지
	CINFImage*				m_pImgRadio[2];						// 라디오qjxms

	int						m_CenterX;
	int						m_CenterY;
	int						m_MoveX;
	int						m_MoveY;							
	POINT					m_ptWindowTitleDown;

	int						m_nMenuTab;
	int						m_nVOIPIndex;						// 통화설정

	BOOL					m_bMouseLDown;
	BOOL					m_bWindowTitleDown;		

	int						m_nOkButton;
	int						m_nCancelButton;

	char					m_strInputMessage[SIZE_MAX_CHARACTER_NAME];

};

#endif // !defined(AFX_INFCOMMUNITYVOIP_H__6F12A791_8818_478D_A570_9A17A2A91D8B__INCLUDED_)
