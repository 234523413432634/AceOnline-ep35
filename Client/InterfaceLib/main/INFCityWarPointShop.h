// INFCityWarPointShop.h: interface for the CINFCityWarPointShop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCITYWARPOINTSHOP_H__2A3317E5_5800_4084_814C_9EBDEC10C6D7__INCLUDED_)
#define AFX_INFCITYWARPOINTSHOP_H__2A3317E5_5800_4084_814C_9EBDEC10C6D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
class CINFImage;
class CD3DHanFont;
class CINFCityWarPointShop : public CINFBase  
{
public:
	CINFCityWarPointShop(CAtumNode* pParent, BUILDINGNPC* pBuilding, CGameData *pGameData);
	virtual ~CINFCityWarPointShop();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	BOOL IsInputItemDone() { return m_bInputItemDone; }
	void InitData();
//	void InitData(MSG_FC_EVENT_ENTER_BUILDING* pMsg);
	int InputItem(char* pMsg);
	void InputItemDone();//m_pnSelectItemNumber �迭 �ʱ�ȭ
	void SellItem( LONGLONG nUniqueNumber, int nAmount/* ����**/, BYTE itemKind );
	
	// 2009. 09. 16 by ckpark ������Ʈ �������� ��ī���ͺ�������� 10���̻� ���Ը��ϵ��� ����
	//void BuyItem(int nItemNum, int nAmount);
	void BuyItem(int nItemNum, int nAmount, int ItemKind);
	// end 2009. 09. 16 by ckpark ������Ʈ �������� ��ī���ͺ�������� 10���̻� ���Ը��ϵ��� ����

	UINT GetTotalWarPointPrice();

	void OnOkButtonClicked();
	void OnCancelButtonClicked();
	void OnBuyButtonClicked(int nSlotNumber);
	void OnChangeWearItem();	// �������� ������ �����غ��� 

	void UpdateItem(int nItemNum);
	void UpdateFindShopItem(int nTab, ITEM* pITEM);
	void InputColorShopItem();

	SHOP_ITEM* FindCityShopDataByColor(int nColor);

protected:
	SHOP_ITEM* FindCityShopData(int nTabIndex, SHOP_ITEM* pShopItem);
	int GetScrollLineNumber(float nLength);
	float GetScrollLineInterval(int nScrollLineNum);
	int GetScrollLine();

public:
	BOOL			m_bInputItemDone;// InputItemDone�� �� ��� TRUE, �� ���� TRUE�̸� ������ ����Ʈ�� �ٽ� ���� �ʴ´�.
	BOOL			m_bRestored;
	BOOL			m_bInvalidated;

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

	vector<SHOP_ITEM*> m_vecItemInfo[SHOP_ITEM_TAB_NUMBER];

	int				m_nCurrentScrollNumber[SHOP_ITEM_TAB_NUMBER];
	int				m_nMouseScrollPosition[SHOP_ITEM_TAB_NUMBER];
	BOOL			m_bScrollLock;
	POINT			m_ptMouse;
	CD3DHanFont*	m_pFontItemName[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontItemPrice[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontItemNumber[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontTotalPrice;

	int*			m_pnSelectItemNumber[SHOP_ITEM_TAB_NUMBER];// array, �� �������� ������ ������ ������ �����Ѵ�.
	int				m_nCurrentSelectSlot[SHOP_ITEM_TAB_NUMBER];
	BUILDINGNPC*	m_pBuildingInfo;	

	CD3DHanFont*	m_pInfluenceTex;
};

#endif // !defined(AFX_INFCITYWARPOINTSHOP_H__2A3317E5_5800_4084_814C_9EBDEC10C6D7__INCLUDED_)
