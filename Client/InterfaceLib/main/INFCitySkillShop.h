// INFCitySkillShop.h: interface for the CINFCitySkillShop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCITYSKILLSHOP_H__4400101C_3F11_4453_BECA_919258E27AC6__INCLUDED_)
#define AFX_INFCITYSKILLSHOP_H__4400101C_3F11_4453_BECA_919258E27AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

class CINFImage;
class CD3DHanFont;
class CINFCitySkillShop : public CINFBase  
{
public:
	CINFCitySkillShop(CAtumNode* pParent, BUILDINGNPC* pBuilding);
	virtual ~CINFCitySkillShop();

	BOOL IsInputItemDone() { return m_bInputItemDone; }

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void InitData();
	int InputItem(char* pMsg);
	void InputItemDone();//m_pnSelectItemNumber 배열 초기화
//	void SellItem( LONGLONG nUniqueNumber, int nAmount/*개수*/, BYTE itemKind );
//	void BuyItem(int nItemNum, int nAmount);
	UINT GetTotalPrice();
	void ReloadSkillItemList();

	void OnOkButtonClicked();
	void OnCancelButtonClicked();
//	void OnBuyButtonClicked(int nSlotNumber);

	void UpdateItem(int nItemNum);

protected:
	SHOP_ITEM* FindSkillShopData(SHOP_ITEM* pShopSkill);

public:
	BOOL			m_bInputItemDone;// InputItemDone이 온 경우 TRUE, 이 값이 TRUE이면 아이템 리스트를 다시 받지 않는다.
	BOOL			m_bRestored;
	BOOL			m_bInvalidated;
//	BOOL			m_bCashErr;

	CINFImage	*	m_pOkButton[4];
	CINFImage	*	m_pCancelButton[4];
	CINFImage	*	m_pBuyButton[4];
	CINFImage	*	m_pCash;
	CINFImage	*	m_pSlot;
	CINFImage	*	m_pItemTab[4];
	CINFImage	*	m_pScrollUpDown;
	CINFImage	*	m_pScrollBar;
	CINFImage	*	m_pSelectSlot;

	int				m_nCurrentTab;
	int				m_nOkButtonState;
	int				m_nCancelButtonState;
	int				m_nBuyButtonState[SHOP_ITEM_SLOT_NUMBER];

//	map<int,SHOP_ITEM*>	m_mapItemInfo[SHOP_ITEM_TAB_NUMBER];//기어별로 아이템 넣기
	vector<SHOP_ITEM*> m_vecItemInfo[SHOP_ITEM_TAB_NUMBER];
	vector<SHOP_ITEM*> m_vecAllSkillData;

	int				m_nCurrentScrollNumber[SHOP_ITEM_TAB_NUMBER];
	BOOL			m_bScrollLock;
	POINT			m_ptMouse;
	CD3DHanFont*	m_pFontItemName[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontItemPrice[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontItemNumber[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontTotalPrice;

	int*			m_pnSelectItemNumber[SHOP_ITEM_TAB_NUMBER];// array, 각 상점별로 선택한 아이템 갯수를 저장한다.
	int				m_nCurrentSelectSlot[SHOP_ITEM_TAB_NUMBER];
	BUILDINGNPC*	m_pBuildingInfo;

	CD3DHanFont*	m_pInfluenceTex;
};

#endif // !defined(AFX_INFCITYSKILLSHOP_H__4400101C_3F11_4453_BECA_919258E27AC6__INCLUDED_)
