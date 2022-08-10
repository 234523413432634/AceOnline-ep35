// CINFCityAuction.h: interface for the CINFCityShop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCITYAUCTION_H__9B6EB8A3_634C_4255_A627_69015270E88C__INCLUDED_)
#define AFX_INFCITYAUCTION_H__9B6EB8A3_634C_4255_A627_69015270E88C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

typedef struct
{
	int				AuctionKind;									// ������ ����
	char			SellerCharacterName[SIZE_MAX_CHARACTER_NAME];	// ������ ������ ����
//	ITEM_GENERAL	AuctionItemGeneral;								// ��� ������
	int 			AuctionPrice;									// ��� ����
	ATUM_DATE_TIME	AuctionStartDate;								// ��� ���� �ð�
	CItemInfo*		pItemInfo;
} AuctionItem_t;

class CINFImage;
class CD3DHanFont;
class CINFCityAuction : public CINFBase  
{
public:
	CINFCityAuction(CAtumNode* pParent, BUILDINGNPC* pBuilding);
	virtual ~CINFCityAuction();

	BOOL IsInputItemDone() { return m_bInputItemDone; }

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void InitData();
	
	void InputItemDone();//m_pnSelectItemNumber �迭 �ʱ�ȭ
	void BuyItem(int nItemNum, int nAmount);
	void InputItem(MSG_FC_AUCTION_INSERT_ITEM* pMsg);
	void AuctionItemInfoView(int nTab);

	void OnOkButtonClicked();
	void OnCancelButtonClicked();
	void OnBuyButtonClicked(int nSlotNumber);
	void AddEnchantItem(BYTE nKind, UID64_t nUniqueNumber, INT nEnchantItemNum);

//	void GetAuctionItemList(int nAuctionItemKind);

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

	//vector<SHOP_ITEM*> m_vecItemInfo[SHOP_ITEM_TAB_NUMBER];
	// ������ �����ֱ� ���� ����ü
	vector<AuctionItem_t> m_vecAuctionItem[SHOP_ITEM_TAB_NUMBER];

	int				m_nCurrentScrollNumber[SHOP_ITEM_TAB_NUMBER];
	BOOL			m_bScrollLock;
	POINT			m_ptMouse;
	CD3DHanFont*	m_pFontItemName[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontItemPrice[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontItemNumber[SHOP_ITEM_SLOT_NUMBER];
	CD3DHanFont*	m_pFontTotalPrice;
	CD3DHanFont*	m_pFontDate;

	int*			m_pnSelectItemNumber[SHOP_ITEM_TAB_NUMBER];
	int				m_nCurrentSelectSlot[SHOP_ITEM_TAB_NUMBER];
	BUILDINGNPC*	m_pBuildingInfo;
};

#endif // !defined(AFX_INFCITYSHOP_H__9B6EB8A3_634C_4255_A627_69015270E88C__INCLUDED_)
