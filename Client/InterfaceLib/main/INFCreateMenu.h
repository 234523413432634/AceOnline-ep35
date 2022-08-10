// INFCreateMenu.h: interface for the CINFCreateMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCREATEMENU_H__88045B6C_4FA7_45E8_BDE4_1FF2FA9DDB47__INCLUDED_)
#define AFX_INFCREATEMENU_H__88045B6C_4FA7_45E8_BDE4_1FF2FA9DDB47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"


#define CRE_BUTTON_NUMBER					4
#define CRE_CHARACTER_INFO_NUMBER			8
#define CRE_CHARACTER_UNIT_NUMBER			4
#define CRE_CHARACTER_RADIO_BUTTON_NUMBER	2
#define CREATE_CHARACTER_RADIO_ALL_AUTTON	3
#define CRE_TOTAL_NUMBER					10

class CGameData;
class CINFImage;
class CD3DHanFont;
class CINFCreateMenu : public CINFBase
{
public:
	CINFCreateMenu(CAtumNode* pParent);
	virtual ~CINFCreateMenu();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	void	Render();
	virtual void Tick();
	virtual int		WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL	ErrCheckCharacterName(char * strName);
	void	OnButtonClicked(int i);
	void	CharacterSet(USHORT uUnitKind);
//	void	SetCharacterUnitStyle(BOOL bToolTip = FALSE);	// 2005-07-04 by ispark 자동 스탯 분배 삭제
	void	RenderPopUpWindowImage(int x, int y, int cx, int cy);

public:
	BOOL			m_bRestored;
	CGameData*		m_pGameData;
//	CINFImage*		m_pBack[CRE_CHARACTER_UNIT_NUMBER];
	CINFImage*		m_pBack;
	CINFImage*		m_pTitle;
	CINFImage*		m_pButton[CRE_BUTTON_NUMBER][2];
//	CINFImage*		m_pImgRadio[CRE_CHARACTER_RADIO_BUTTON_NUMBER];
	CINFImage*		m_pImgFocus[4];
	CINFImage*		m_pImgToolTip[9];
	CINFImage*		m_pImgTextPopUp[3];
	float			m_fButtonPos[CRE_BUTTON_NUMBER][2];
	int				m_nButtonState[CRE_BUTTON_NUMBER];

	// 2009-02-10 by bhsohn Japan Charcter Create
	//char			m_strCharacterName[SIZE_MAX_CHARACTER_NAME];
	char			m_strCharacterName[MAX_PATH];
	// end 2009-02-10 by bhsohn Japan Charcter Create
	CD3DHanFont*	m_pFontCharacterName;
	CD3DHanFont*	m_pFontCharacterInfo[CRE_CHARACTER_INFO_NUMBER];
	int				m_nCharacterNamePos[2];
	int				m_nCharacterInfoPos[CRE_CHARACTER_INFO_NUMBER][2];

	BOOL			m_bShowCursor;
	float			m_fChangeShowCursorTime;
	BOOL			m_bBlocking;//create시에 블락시키는 변수

	MSG_FC_CHARACTER_CREATE m_createUnit;
	int				m_nSelectUnit;
	int				m_nRadioButton[CREATE_CHARACTER_RADIO_ALL_AUTTON];
	int				m_nSelectUnitStyle;
	int				m_nFocus;
	int				m_nFocusStat;
	int				m_nCreateUnitStat;
//	int				m_nRenderToolTipIndex;		// 2005-07-04 by ispark 자동 스탯 분배 삭제

protected:
	int				m_nFaceUseIndex[CRE_TOTAL_NUMBER];			// 페이스 넘버
	int				m_nChoiseFaceIndex;			// 페이스 선택 번호
};

#endif // !defined(AFX_INFCREATEMENU_H__88045B6C_4FA7_45E8_BDE4_1FF2FA9DDB47__INCLUDED_)
