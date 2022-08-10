// INFCityWarPointShop.cpp: implementation of the CINFCityWarPointShop class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "INFCityWarPointShop.h"
#include "INFGameMain.h"
#include "AtumApplication.h"
#include "FieldWinSocket.h"
#include "AtumDatabase.h"
#include "INFWindow.h"
#include "D3DHanFont.h"
#include "INFIcon.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "INFCityBase.h"
#include "ItemInfo.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "Chat.h"
#include "StoreData.h"
#include "dxutil.h"

#define CITY_SHOP_START_X			(CITY_BASE_NPC_BOX_START_X+230)
#define CITY_SHOP_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y-9)

//#define SHOP_TAB_START_X			(221+28)
//#define SHOP_TAB_START_Y			33
//#define SHOP_TAB_NUMBER				4
//#define SHOP_ITEM_SLOT_START_X		(227+28)
//#define SHOP_ITEM_SLOT_START_Y		51
//#define SHOP_ITEM_SLOT_SIZE_X		157
//#define SHOP_ITEM_SLOT_SIZE_Y		36
//#define SHOP_ICON_START_X			(230+28)
//#define SHOP_ICON_START_Y			53
//#define SHOP_ICON_SIZE				30
//#define SHOP_ITEM_SLOT_INTERVAL		36
//#define SHOP_ITEM_NUMBER_X			(308+28)//346
//#define SHOP_NUMBER_BUTTON_X		(336+28)//347
//#define SHOP_NUMBER_UP_BUTTON_Y		58//69
//#define SHOP_NUMBER_BUTTON_SIZE_X	8
//#define SHOP_NUMBER_BUTTON_SIZE_Y	7
//#define SHOP_NUMBER_DOWN_BUTTON_Y	71//79
//#define SHOP_BUY_BUTTON_START_X		(344+28)
//#define SHOP_BUY_BUTTON_START_Y		70
//#define SHOP_BUY_BUTTON_SIZE_X		39
//#define SHOP_BUY_BUTTON_SIZE_Y		14
//#define SHOP_CASH_START_X			(223+28)
#define SHOP_CASH_FONT_START_X		(223+28+98)
//#define SHOP_OK_BUTTON_START_X		(333+28)
//#define SHOP_OK_BUTTON_START_Y		240
//#define SHOP_OK_BUTTON_SIZE_X		35
//#define SHOP_OK_BUTTON_SIZE_Y		16
//#define SHOP_CANCEL_BUTTON_START_X	(370+28)
//#define SHOP_CANCEL_BUTTON_START_Y	240
//
//#define SHOP_SCROLL_START_X			(388+28)
//#define SHOP_SCROLL_UP_START_Y		51
//#define SHOP_SCROLL_SIZE_X			11
//#define SHOP_SCROLL_SIZE_Y			12
//#define SHOP_SCROLL_BAR_SIZE_Y		38//30
//#define SHOP_SCROLL_DOWN_START_Y	217
//
//#define SHOP_SCROLL_BAR_START_Y		65
//#define SHOP_SCROLL_BAR_END_Y		215
//
//#define SHOP_TAB_BUTTON_SIZE_X		47
//#define SHOP_TAB_BUTTON_SIZE_Y		14
//
//#define SHOP_SCROLL_LENGTH			150	// 150 : scroll bar line length
//#define SHOP_SCROLL_MOVE_LENGTH		(150-SHOP_SCROLL_BAR_SIZE_Y)
////#define SHOP_SCROLL_NUMBER(i)		(m_mapItemInfo[i].size()<=0 ? 1:m_mapItemInfo[i].size())	// i번째 탭의 scroll number
//#define SHOP_SCROLL_NUMBER(i)		(m_vecItemInfo[i].size()<=0 ? 0:m_vecItemInfo[i].size())	// i번째 탭의 scroll number
//#define SHOP_SCROLL_INTERVAL(i)		(SHOP_SCROLL_LENGTH / SHOP_SCROLL_NUMBER(i))
//
//#define SHOP_ITEM_NAME_START_X		(260+28)
//
//#define SHOP_SELL_ITEM_START_X		(227+28)
//#define SHOP_SELL_ITEM_START_Y		51
//#define SHOP_SELL_ITEM_END_X		(383+28)
//#define SHOP_SELL_ITEM_END_Y		228
#define SHOP_TAB_START_X			(196+9)//(221+28)
#define SHOP_TAB_START_Y			33
#define SHOP_TAB_NUMBER				4
#define SHOP_ITEM_SLOT_START_X		(SHOP_TAB_START_X + 2)//(227+28)
#define SHOP_ITEM_SLOT_START_Y		51
#define SHOP_ITEM_SLOT_SIZE_X		253//157
#define SHOP_ITEM_SLOT_SIZE_Y		36
#define SHOP_ICON_START_X			(SHOP_ITEM_SLOT_START_X + 3)//(230+28)
#define SHOP_ICON_START_Y			53
#define SHOP_ICON_SIZE				30
#define SHOP_ITEM_SLOT_INTERVAL		36
#define SHOP_ITEM_NUMBER_X			(SHOP_TAB_START_X+210)
#define SHOP_NUMBER_BUTTON_X		(SHOP_TAB_START_X + 242)
#define SHOP_NUMBER_UP_BUTTON_Y		58
#define SHOP_NUMBER_BUTTON_SIZE_X	8
#define SHOP_NUMBER_BUTTON_SIZE_Y	7
#define SHOP_NUMBER_DOWN_BUTTON_Y	71
#define SHOP_BUY_BUTTON_START_X		(344+28)
#define SHOP_BUY_BUTTON_START_Y		70
#define SHOP_BUY_BUTTON_SIZE_X		39
#define SHOP_BUY_BUTTON_SIZE_Y		14
#define SHOP_CASH_START_X			(SHOP_TAB_START_X + 95)
#define SHOP_OK_BUTTON_START_X		(SHOP_TAB_START_X + 205)
#define SHOP_OK_BUTTON_START_Y		240
#define SHOP_OK_BUTTON_SIZE_X		35
#define SHOP_OK_BUTTON_SIZE_Y		16
#define SHOP_CANCEL_BUTTON_START_X	(SHOP_TAB_START_X + 242)
#define SHOP_CANCEL_BUTTON_START_Y	240

#define SHOP_SCROLL_START_X			(SHOP_TAB_START_X + 260)
#define SHOP_SCROLL_UP_START_Y		51
#define SHOP_SCROLL_SIZE_X			11
#define SHOP_SCROLL_SIZE_Y			12
#define SHOP_SCROLL_BAR_SIZE_Y		38//30
#define SHOP_SCROLL_DOWN_START_Y	217

#define SHOP_SCROLL_BAR_START_Y		65
#define SHOP_SCROLL_BAR_END_Y		215

#define SHOP_TAB_BUTTON_SIZE_X		60
#define SHOP_TAB_BUTTON_SIZE_Y		14

#define SHOP_SCROLL_LENGTH			150	// 150 : scroll bar line length
#define SHOP_SCROLL_MOVE_LENGTH		(150-SHOP_SCROLL_BAR_SIZE_Y)
//#define SHOP_SCROLL_NUMBER(i)		(m_mapItemInfo[i].size()<=0 ? 1:m_mapItemInfo[i].size())	// i번째 탭의 scroll number
#define SHOP_SCROLL_NUMBER(i)		(m_vecItemInfo[i].size()<=0 ? 0:m_vecItemInfo[i].size())	// i번째 탭의 scroll number
#define SHOP_SCROLL_INTERVAL(i)		(SHOP_SCROLL_LENGTH / SHOP_SCROLL_NUMBER(i))

#define SHOP_ITEM_NAME_START_X		(SHOP_TAB_START_X + 46)

#define SHOP_SELL_ITEM_START_X		(227+28)
#define SHOP_SELL_ITEM_START_Y		51
#define SHOP_SELL_ITEM_END_X		(383+28)
#define SHOP_SELL_ITEM_END_Y		228
#define SHOP_TAB_B_GEAR				0
#define SHOP_TAB_I_GEAR				1
#define SHOP_TAB_M_GEAR				2
#define SHOP_TAB_A_GEAR				3

#define BOX_SIZE_X					417
#define BOX_SIZE_Y					275
#define END_OF_INVEN_X				200

#define SOURCEINDEXTOITEMNUM(i,j)	(((i/100)*100)+j)

// 2006-03-07 by ispark, 언어에 따라 위치 수정
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn 태국 버전 추가
#define SHOP_ITEM_NUMBER_Y			68//70
#define SHOP_CASH_START_Y			239//241
#define SHOP_ITEM_NAME_START_Y		51//53
#define SHOP_ITEM_PRICE_START_Y		68//70
#define FONT_TOTAL_PRICE_X			35
#define FONT_TOTAL_PRICE_Y			1
#define SHOP_TEX_X					CITY_SHOP_START_X + 420
#define SHOP_TEX_Y					CITY_SHOP_START_Y + 12
#else
#define SHOP_ITEM_NUMBER_Y			68//70//54
#define SHOP_CASH_START_Y			239//241
#define SHOP_ITEM_NAME_START_Y		51//53
#define SHOP_ITEM_PRICE_START_Y		68//70
#define FONT_TOTAL_PRICE_X			34
#define FONT_TOTAL_PRICE_Y			1//3
#define SHOP_TEX_X					CITY_SHOP_START_X + 420
#define SHOP_TEX_Y					CITY_SHOP_START_Y + 12
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CINFCityWarPointShop::InputItemDone()
{
	FLOG( "CINFCityShop::InputItemDone()" );
	for(int i=0;i<4;i++)
	{
		SAFE_DELETE_ARRAY(m_pnSelectItemNumber[i]);
		if(m_vecItemInfo[i].size() > 0)
		{
			int num = m_vecItemInfo[i].size();
			m_pnSelectItemNumber[i] = new int[num];
			memset(m_pnSelectItemNumber[i], 0x00, num*sizeof(UINT));
		}

	}
	//	m_bInputItemDone = TRUE;
	///////////////////////////////
	// UNLOCK BUILDING BUTTON
	///////////////////////////////
}
int CINFCityWarPointShop::InputItem(char* pMsg)
{
	FLOG( "CINFCityShop::InputItem(char* pMsg)" );
	if(pMsg)
	{
		ITEM *item = g_pDatabase->GetServerItemInfo(((SHOP_ITEM*)pMsg)->ItemNum);
		if(item)
		{
			// 2006-01-11 by ispark, 같은 정보가 있는지 확인
			// 렉에 의해서 중복 입력이 되는 현상이 있다. 그래서 같은 정보가 있으면 넘어감
		
			if(IS_BGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
				pItem->Price = item->CashPrice;
//				m_mapItemInfo[SHOP_TAB_B_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_B_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_B_GEAR].push_back(pItem);
			}
			if(IS_IGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
				pItem->Price = item->CashPrice;
//				m_mapItemInfo[SHOP_TAB_I_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_I_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_I_GEAR].push_back(pItem);
			}
			if(IS_MGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
				pItem->Price = item->CashPrice;
//				m_mapItemInfo[SHOP_TAB_M_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_M_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_M_GEAR].push_back(pItem);
			}
			if(IS_AGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
				pItem->Price = item->CashPrice;
//				m_mapItemInfo[SHOP_TAB_A_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_A_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_A_GEAR].push_back(pItem);
			}
		}
		else
		{
			SHOP_ITEM* pItem = new SHOP_ITEM;
			memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
			pItem->Price = item->CashPrice;
//			m_mapItemInfo[SHOP_TAB_B_GEAR][pItem->ItemNum] = pItem;
			if(FindCityShopData(SHOP_TAB_B_GEAR, pItem) == NULL)
			m_vecItemInfo[SHOP_TAB_B_GEAR].push_back(pItem);
		}
	}
	return sizeof(SHOP_ITEM);
}

// 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경
//void CINFCityWarPointShop::BuyItem(int nItemNum, int nAmount)
void CINFCityWarPointShop::BuyItem(int nItemNum, int nAmount, int ItemKind)
// end 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경
{
	// 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경
	
	if( !IS_COUNTABLE_ITEM(ItemKind) && IS_GENERAL_ITEM(ItemKind))
	{
		if(nAmount > MAX_ITEM_COUNTS_FOR_BUY)
		{
			char errStr[256];
			wsprintf(errStr,STRMSG_C_080716_0204);	// "해당아이템은 한번 구매시 최대 개수는 10개입니다."	
			g_pD3dApp->m_pChat->CreateChatChild(errStr,COLOR_ERROR);
			return;
		}
	}

	// end 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경
	
	
	
	//g_pD3dApp->m_bRequestEnable = FALSE;
	MSG_FC_SHOP_BUY_WARPOINT_ITEM sMsg;
	memset(&sMsg,0x00,sizeof(sMsg));
	sMsg.BuildingIndex = m_pBuildingInfo->BuildingIndex;
	sMsg.ItemNum = nItemNum;
	sMsg.Amount = nAmount;
	g_pFieldWinSocket->SendMsg( T_FC_SHOP_BUY_WARPOINT_ITEM, (char*)&sMsg, sizeof(sMsg) );
}
void CINFCityWarPointShop::OnChangeWearItem()
{
	int nSlotNumber = m_nCurrentSelectSlot[m_nCurrentTab];
	ITEM *item = NULL;
	if( nSlotNumber < 0 )
		return;

	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[m_nCurrentTab].begin();
	for(int i=0;i<nSlotNumber;i++){
		if(it != m_vecItemInfo[m_nCurrentTab].end()){
			it++;
		}
		else{
			break;
		}
	}
	if(it != m_vecItemInfo[m_nCurrentTab].end()){
		if(m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber] == 0){
			item = g_pDatabase->GetServerItemInfo((*it)->ItemNum);
		}
	}

	if(item)
	{
		if(m_pBuildingInfo->BuildingKind != BUILDINGKIND_TUNING_COLOR)
			g_pGameMain->ChangeItemByShop(item->ItemNum);
		else
		{
			// g_pGameMain->ChangeItemByShop(item->ItemNum, nUnitColor);
			CItemInfo *pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(POS_CENTER);
			if(pItemInfo)
			{
				int nArmorColor = 0;
				if(pItemInfo->ItemInfo->SourceIndex == 0)
					nArmorColor = pItemInfo->ItemNum;				
				else
					nArmorColor = pItemInfo->ItemInfo->SourceIndex;
				int nColorNum = item->ItemNum-nArmorColor;

				g_pGameMain->ChangeItemByShop(item->ItemNum, nColorNum);
			}
		}
	}
}
void CINFCityWarPointShop::OnOkButtonClicked()
{
	FLOG( "CINFCityShop::OnOkButtonClicked()" );
	for(int tab=0;tab<4;tab++)
	{
//		map<int,SHOP_ITEM*>::iterator it = m_mapItemInfo[tab].begin();
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[tab].begin();
		int i=0;
//		while(it != m_mapItemInfo[tab].end())
		while(it != m_vecItemInfo[tab].end())
		{
			if(m_pnSelectItemNumber[tab][i]>0)
			{
				
				// 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경
				
				//BuyItem((*it)->ItemNum, m_pnSelectItemNumber[tab][i]);
				BuyItem((*it)->ItemNum, m_pnSelectItemNumber[tab][i], (*it)->ItemKind);

				// end 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경

			}
			it++;
			i++;
		}
	}

}

void CINFCityWarPointShop::OnCancelButtonClicked()
{
	for(int tab=0;tab<4;tab++)
	{
//		map<int,SHOP_ITEM*>::iterator it = m_mapItemInfo[tab].begin();
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[tab].begin();
		int i=0;
//		while(it != m_mapItemInfo[tab].end())
		while(it != m_vecItemInfo[tab].end())
		{
			m_pnSelectItemNumber[tab][i] = 0;
			it++;
			i++;
		}
	}
//	MSG_FC_EVENT_LEAVE_BUILDING sMsg;
//	sMsg.BuildingIndex = m_pBuildingInfo->BuildingIndex;
//	g_pFieldWinSocket->SendMsg( T_FC_EVENT_LEAVE_BUILDING, (char*)&sMsg, sizeof(sMsg) );
	
}

void CINFCityWarPointShop::OnBuyButtonClicked(int nSlotNumber)
{
	FLOG( "CINFCityShop::OnBuyButtonClicked(int nSlotNumber)" );
	if( nSlotNumber < 0 )
	{
		return;
	}
	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[m_nCurrentTab].begin();
	for(int i=0;i<nSlotNumber;i++)
	{
		if(it != m_vecItemInfo[m_nCurrentTab].end())
		{
			it++;
		}
		else
		{
			break;
		}
	}
	if(it != m_vecItemInfo[m_nCurrentTab].end())
	{
		if(m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber] == 0)
		{
			m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber] = (*it)->MinTradeQuantity;
			// 2007-07-06 by dgwoo 스피에서 워포인트로..
			//if( GetTotalWarPointPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
			if( GetTotalWarPointPrice() > g_pShuttleChild->GetMyShuttleInfo().WarPoint)
			{
				m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] = 0;
					g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_070622_0100,COLOR_ERROR );//"전쟁 포인트가 부족합니다."
			}
		}
		if(m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber]>0)
		{
			
			// 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경
			//BuyItem((*it)->ItemNum, m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber]);
			BuyItem((*it)->ItemNum, m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber], (*it)->ItemKind);
			// end 2009. 09. 16 by ckpark 워포인트 상점에서 논카운터블아이템을 10개이상 구입못하도록 변경

		}
		m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber] = 0;
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			UINT CINFCityWarPointShop::GetTotalWarPointPrice()
/// \brief		워 포인트에서 
/// \author		dgwoo
/// \date		2007-06-13 ~ 2007-06-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
UINT CINFCityWarPointShop::GetTotalWarPointPrice()
{
	FLOG( "CINFCityShop::GetTotalWarPointPrice()" );
	int total = 0;
	for(int tab=0;tab<4;tab++)
	{
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[tab].begin();
		int i=0;
		while(it != m_vecItemInfo[tab].end())
		{
			if(m_pnSelectItemNumber[tab][i]>0)
			{
				SHOP_ITEM* pItem = *it;
				int Cashprice = pItem->Price * m_pnSelectItemNumber[tab][i] / (pItem->MinTradeQuantity == 0 ? 1.0f : pItem->MinTradeQuantity);
				total += Cashprice;
			}
			it++;
			i++;
		}
	}
	
	return total;
}
void CINFCityWarPointShop::InitData()
{
	if(IS_BT(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_B_GEAR;
	}
	else if(IS_OT(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_M_GEAR;
	}
	else if(IS_ST(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_I_GEAR;
	}
	else if(IS_DT(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_A_GEAR;
	}
	for(int i=0;i<4;i++)
	{
		SAFE_DELETE_ARRAY(m_pnSelectItemNumber[i]);
		m_nCurrentScrollNumber[i] = 0;
		m_nCurrentSelectSlot[i] = -1;
		m_nMouseScrollPosition[i] = 0;					// 2006-04-05 by ispark
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[i].begin();
		while(it != m_vecItemInfo[i].end())
		{
			SHOP_ITEM* pItem = *it;
			delete pItem;
			pItem = NULL;
			it++;
		}
		m_vecItemInfo[i].clear();
	}	
}
int CINFCityWarPointShop::GetScrollLine()
{
	int nInvenTotalNum = SHOP_SCROLL_NUMBER(m_nCurrentTab);
	int ntemp = nInvenTotalNum - SHOP_ITEM_SLOT_NUMBER;
	if(ntemp < 0)
	{
		ntemp = 0;
	}
	return ntemp;
}

float CINFCityWarPointShop::GetScrollLineInterval(int nScrollLineNum)
{
	int ntemp = GetScrollLine();
	float fLineNum = 0.0f;
	if(ntemp)
		fLineNum = (SHOP_SCROLL_MOVE_LENGTH * nScrollLineNum) / ntemp;

	return fLineNum;
}

int CINFCityWarPointShop::GetScrollLineNumber(float nLength)
{
	int ntemp = GetScrollLine();
	float fLineNum = (nLength * ntemp) / SHOP_SCROLL_MOVE_LENGTH;

	return (int)fLineNum;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityShop::FindCityShopData(SHOP_ITEM *pShopItem)
/// \brief		샵 아이템 검색
/// \author		ispark
/// \date		2006-01-11 ~ 2006-01-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
SHOP_ITEM* CINFCityWarPointShop::FindCityShopData(int nTabIndex, SHOP_ITEM *pShopItem)
{
	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[nTabIndex].begin();
	while(it != m_vecItemInfo[nTabIndex].end())
	{
		SHOP_ITEM* pitShopSkill = *it;
		if(pShopItem->ItemNum == pitShopSkill->ItemNum)
		{
			return pShopItem;
		}

		it++;
	}
	
	return NULL;
}
CINFCityWarPointShop::CINFCityWarPointShop(CAtumNode* pParent, BUILDINGNPC* pBuilding, CGameData *pGameData)
{
	m_pParent = pParent;	// CGameMain*
	m_pGameData = pGameData;

	int i;
	for(i=0;i<4;i++)
	{
		m_pOkButton[i] = NULL;
		m_pCancelButton[i] = NULL;
		m_pBuyButton[i] = NULL;// [3]은 NULL
		m_pItemTab[i] = NULL;
		m_pnSelectItemNumber[i] = NULL;
		m_nCurrentScrollNumber[i] = 0;
		m_nCurrentSelectSlot[i] = -1;
		m_nMouseScrollPosition[i] = 0;
	}
	m_pCash = NULL;
	m_pSlot = NULL;
	m_pScrollUpDown = NULL;
	m_pScrollBar = NULL;
	m_pSelectSlot = NULL;
	m_pFontTotalPrice = NULL;

	m_nCurrentTab = SHOP_TAB_B_GEAR;
	m_nOkButtonState = BUTTON_STATE_NORMAL;
	m_nCancelButtonState = BUTTON_STATE_NORMAL;

	for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
	{
		m_nBuyButtonState[i] = BUTTON_STATE_NORMAL;
		m_pFontItemName[i] = NULL;
		m_pFontItemPrice[i] = NULL;
		m_pFontItemNumber[i] = NULL;
	}
	m_bScrollLock = FALSE;
	m_ptMouse.x = 0;
	m_ptMouse.y = 0;
	m_bRestored = FALSE;
	m_bInvalidated = FALSE;
	m_bInputItemDone = FALSE;
	m_pBuildingInfo = pBuilding;

	m_pInfluenceTex = NULL;

}

CINFCityWarPointShop::~CINFCityWarPointShop()
{
	int i;
	for(i=0;i<4;i++)
	{
		SAFE_DELETE(m_pOkButton[i]);
		SAFE_DELETE(m_pCancelButton[i]);
		SAFE_DELETE(m_pBuyButton[i]);
		SAFE_DELETE(m_pItemTab[i]);
		SAFE_DELETE_ARRAY(m_pnSelectItemNumber[i]);

//		map<int, SHOP_ITEM*>::iterator it = m_mapItemInfo[i].begin();
//		while(it != m_mapItemInfo[i].end())
//		{
//			SHOP_ITEM* pItem = it->second;
//			delete pItem;
//			pItem = NULL;
//			it++;
//		}
//		m_mapItemInfo[i].clear();
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[i].begin();
		while(it != m_vecItemInfo[i].end())
		{
			SHOP_ITEM* pItem = *it;
			delete pItem;
			pItem = NULL;
			it++;
		}
		m_vecItemInfo[i].clear();

	}
	for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
	{
		SAFE_DELETE(m_pFontItemName[i]);
		SAFE_DELETE(m_pFontItemPrice[i]);
		SAFE_DELETE(m_pFontItemNumber[i]);
	}
	SAFE_DELETE(m_pCash);
	SAFE_DELETE(m_pSlot);
	SAFE_DELETE(m_pScrollUpDown);
	SAFE_DELETE(m_pScrollBar);
	SAFE_DELETE(m_pSelectSlot);
	SAFE_DELETE(m_pFontTotalPrice);

	SAFE_DELETE(m_pInfluenceTex);

}
HRESULT CINFCityWarPointShop::InitDeviceObjects()
{
	DataHeader	* pDataHeader;

	int i;
	for(i=0;i<4;i++)
	{
		char buf[16];

		m_pOkButton[i] = new CINFImage;
		wsprintf(buf, "sauok%d",i);
		pDataHeader = FindResource(buf);
		m_pOkButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pCancelButton[i] = new CINFImage;
		wsprintf(buf, "shmcan0%d",i);
		pDataHeader = FindResource(buf);
		m_pCancelButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		wsprintf(buf, "sbuy%d",i);//sbuy3은 없음.
		pDataHeader = FindResource(buf);
		if(pDataHeader)
		{
			m_pBuyButton[i] = new CINFImage;
			m_pBuyButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
		}

		m_pItemTab[i] = new CINFImage;
		wsprintf(buf, "stab%d",i);
		pDataHeader = FindResource(buf);
		m_pItemTab[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	}

	m_pCash = new CINFImage;
	pDataHeader = FindResource("wcash");
	m_pCash->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pSlot = new CINFImage;
	pDataHeader = FindResource("auslot");
	m_pSlot->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pScrollUpDown = new CINFImage;
	pDataHeader = FindResource("c_scrlbt");
	m_pScrollUpDown->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pScrollBar = new CINFImage;
	pDataHeader = FindResource("c_scrlb");
	m_pScrollBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pSelectSlot = new CINFImage;
	pDataHeader = FindResource("slosel");
	m_pSelectSlot->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
	{
		m_pFontItemName[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
		m_pFontItemName[i]->InitDeviceObjects(g_pD3dDev);
		m_pFontItemPrice[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
		m_pFontItemPrice[i]->InitDeviceObjects(g_pD3dDev);
		m_pFontItemNumber[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
		m_pFontItemNumber[i]->InitDeviceObjects(g_pD3dDev);
	}
	m_pFontTotalPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontTotalPrice->InitDeviceObjects(g_pD3dDev);

	m_pInfluenceTex = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,256,32);
	m_pInfluenceTex->InitDeviceObjects(g_pD3dDev);
	return S_OK;
}
HRESULT CINFCityWarPointShop::RestoreDeviceObjects()
{
	int i;
	for(i=0;i<4;i++)
	{
		m_pOkButton[i]->RestoreDeviceObjects();
		m_pCancelButton[i]->RestoreDeviceObjects();
		if(m_pBuyButton[i])
			m_pBuyButton[i]->RestoreDeviceObjects();
		m_pItemTab[i]->RestoreDeviceObjects();
	}
	m_pCash->RestoreDeviceObjects();
	m_pSlot->RestoreDeviceObjects();
	m_pScrollUpDown->RestoreDeviceObjects();
	m_pScrollBar->RestoreDeviceObjects();
	m_pSelectSlot->RestoreDeviceObjects();
	for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
	{
		m_pFontItemName[i]->RestoreDeviceObjects();
		m_pFontItemPrice[i]->RestoreDeviceObjects();
		m_pFontItemNumber[i]->RestoreDeviceObjects();
	}
	m_pFontTotalPrice->RestoreDeviceObjects();

	m_bRestored = TRUE;

	m_pInfluenceTex->RestoreDeviceObjects();
	return S_OK;
}
HRESULT CINFCityWarPointShop::DeleteDeviceObjects()
{
	int i;
	for(i=0;i<4;i++)
	{
		m_pOkButton[i]->DeleteDeviceObjects();
		m_pCancelButton[i]->DeleteDeviceObjects();
		if(m_pBuyButton[i])
			m_pBuyButton[i]->DeleteDeviceObjects();
		m_pItemTab[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pOkButton[i]);
		SAFE_DELETE(m_pCancelButton[i]);
		SAFE_DELETE(m_pBuyButton[i]);
		SAFE_DELETE(m_pItemTab[i]);
//		map<int, SHOP_ITEM*>::iterator it = m_mapItemInfo[i].begin();
//		while(it != m_mapItemInfo[i].end())
//		{
//			SHOP_ITEM* pItem = it->second;
//			delete pItem;
//			pItem = NULL;
//			it++;
//		}
//		m_mapItemInfo[i].clear();
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[i].begin();
		while(it != m_vecItemInfo[i].end())
		{
			SHOP_ITEM* pItem = *it;
			delete pItem;
			pItem = NULL;
			it++;
		}
		m_vecItemInfo[i].clear();
	}
	m_pCash->DeleteDeviceObjects();
	m_pSlot->DeleteDeviceObjects();

	SAFE_DELETE(m_pItemTab[3]);
	SAFE_DELETE(m_pCash);
	SAFE_DELETE(m_pSlot);

	m_pScrollUpDown->DeleteDeviceObjects();
	SAFE_DELETE(m_pScrollUpDown);
	m_pScrollBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pScrollBar);
	m_pSelectSlot->DeleteDeviceObjects();
	SAFE_DELETE(m_pSelectSlot);
	for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
	{
		m_pFontItemName[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontItemName[i]);
		m_pFontItemPrice[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontItemPrice[i]);
		m_pFontItemNumber[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontItemNumber[i]);
	}

	m_pFontTotalPrice->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontTotalPrice);

//	memset(&m_buildingInfo, 0x00, sizeof(BUILDINGNPC));
	m_bInvalidated = FALSE;

	m_pInfluenceTex->DeleteDeviceObjects();
	SAFE_DELETE(m_pInfluenceTex);
	return S_OK;
}
HRESULT CINFCityWarPointShop::InvalidateDeviceObjects()
{
	int i;
	for(i=0;i<4;i++)
	{
		m_pOkButton[i]->InvalidateDeviceObjects();
		m_pCancelButton[i]->InvalidateDeviceObjects();
		if(m_pBuyButton[i])
			m_pBuyButton[i]->InvalidateDeviceObjects();
		m_pItemTab[i]->InvalidateDeviceObjects();
	}
	m_pCash->InvalidateDeviceObjects();
	m_pSlot->InvalidateDeviceObjects();
	m_pScrollUpDown->InvalidateDeviceObjects();
	m_pScrollBar->InvalidateDeviceObjects();
	m_pSelectSlot->InvalidateDeviceObjects();

	for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
	{
		m_pFontItemName[i]->InvalidateDeviceObjects();
		m_pFontItemPrice[i]->InvalidateDeviceObjects();
		m_pFontItemNumber[i]->InvalidateDeviceObjects();
	}
	m_pFontTotalPrice->InvalidateDeviceObjects();
	m_bRestored = FALSE;
	m_bInvalidated = TRUE;

	m_pInfluenceTex->InvalidateDeviceObjects();
	return S_OK;
}
void CINFCityWarPointShop::Render()
{
	int nPosX = CITY_SHOP_START_X+SHOP_TAB_START_X;
	int nPosY = CITY_SHOP_START_Y+SHOP_TAB_START_Y;
	
	m_pItemTab[m_nCurrentTab]->Move(nPosX, nPosY);
	m_pItemTab[m_nCurrentTab]->Render();

	int nSelectNumber = 0;

	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[m_nCurrentTab].begin();
	int i;
	for(i=0;i<m_nCurrentScrollNumber[m_nCurrentTab];i++)
	{
		if(it != m_vecItemInfo[m_nCurrentTab].end())
		{
			it++;
			nSelectNumber++;
		}
		else
		{
			break;
		}
	}
	if(m_pnSelectItemNumber[m_nCurrentTab])
	{
		for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
		{
			if(m_nCurrentSelectSlot[m_nCurrentTab] >= 0 && m_nCurrentSelectSlot[m_nCurrentTab] == nSelectNumber+i)
			{
				m_pSelectSlot->Move(CITY_SHOP_START_X+SHOP_ITEM_SLOT_START_X, CITY_SHOP_START_Y+SHOP_ITEM_SLOT_START_Y+SHOP_ITEM_SLOT_INTERVAL*i);
				m_pSelectSlot->Render();
			}
			else
			{
				m_pSlot->Move(CITY_SHOP_START_X+SHOP_ITEM_SLOT_START_X, CITY_SHOP_START_Y+SHOP_ITEM_SLOT_START_Y+SHOP_ITEM_SLOT_INTERVAL*i);
				m_pSlot->Render();
			}
			if(it != m_vecItemInfo[m_nCurrentTab].end())
			{
				SHOP_ITEM* pItem = *it;
				char buf[64];
				// 2005-08-23 by ispark
				ITEM* pOriItem = g_pDatabase->GetServerItemInfo(pItem->ItemNum);
				wsprintf( buf, "%08d", pOriItem->SourceIndex);
				((CINFGameMain*)m_pParent)->m_pIcon->SetIcon( buf,CITY_SHOP_START_X+SHOP_ICON_START_X,CITY_SHOP_START_Y+SHOP_ICON_START_Y+SHOP_ITEM_SLOT_INTERVAL*i+1, 1.0f );
				((CINFGameMain*)m_pParent)->m_pIcon->Render();

				char temp1[64];
				char temp2[64];
				wsprintf( temp1, "%d", (int)(pItem->Price));
				MakeCurrencySeparator( temp2, temp1, 3, ',' );
				m_pFontItemName[i]->DrawText( CITY_SHOP_START_X+SHOP_ITEM_NAME_START_X, CITY_SHOP_START_Y+SHOP_ITEM_NAME_START_Y+SHOP_ITEM_SLOT_INTERVAL*i, GUI_FONT_COLOR, pItem->ItemName, 0L);
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn 태국 버전 추가
				wsprintf(buf, "%s", temp2);
#else
				wsprintf(buf, "%7s", temp2);
#endif
				m_pFontItemPrice[i]->DrawText( CITY_SHOP_START_X+SHOP_ITEM_NAME_START_X,CITY_SHOP_START_Y+SHOP_ITEM_PRICE_START_Y+SHOP_ITEM_SLOT_INTERVAL*i, GUI_FONT_COLOR, buf, 0L);
				it++;

				wsprintf(buf, "%3d", m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]);
				m_pFontItemNumber[i]->DrawText( CITY_SHOP_START_X+SHOP_ITEM_NUMBER_X, (CITY_SHOP_START_Y+SHOP_ITEM_NUMBER_Y+SHOP_ITEM_SLOT_INTERVAL*i)-1, GUI_FONT_COLOR, buf, 0L);
			}
		}
		m_pCash->Move(CITY_SHOP_START_X+SHOP_CASH_START_X, CITY_SHOP_START_Y+SHOP_CASH_START_Y);
		m_pCash->Render();
		char temp1[64];
		char temp2[64];
		wsprintf( temp1, "%d", GetTotalWarPointPrice() );
		MakeCurrencySeparator( temp2, temp1, 3, ',' );
		//SIZE size = m_pFontTotalPrice->GetStringSize(temp2);
		m_pFontTotalPrice->DrawText( CITY_SHOP_START_X+SHOP_CASH_START_X + FONT_TOTAL_PRICE_X, CITY_SHOP_START_Y+SHOP_CASH_START_Y + FONT_TOTAL_PRICE_Y, GUI_FONT_COLOR, temp2, 0L);
	}

	m_pOkButton[m_nOkButtonState]->Move(CITY_SHOP_START_X+SHOP_OK_BUTTON_START_X, CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y);
	m_pOkButton[m_nOkButtonState]->Render();
	m_pCancelButton[m_nCancelButtonState]->Move(CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X, CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y);
	m_pCancelButton[m_nCancelButtonState]->Render();

	//////////////////

	// scroll rendering
	m_pScrollUpDown->Move( CITY_SHOP_START_X+SHOP_SCROLL_START_X, CITY_SHOP_START_Y+SHOP_SCROLL_UP_START_Y);
	m_pScrollUpDown->Render();
	m_pScrollUpDown->Move( CITY_SHOP_START_X+SHOP_SCROLL_START_X, CITY_SHOP_START_Y+SHOP_SCROLL_DOWN_START_Y);
	m_pScrollUpDown->Render();

//	m_pScrollBar->Move( CITY_SHOP_START_X+SHOP_SCROLL_START_X,
//		CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y+m_nCurrentScrollNumber[m_nCurrentTab]*SHOP_SCROLL_INTERVAL(m_nCurrentTab));
	m_pScrollBar->Move( CITY_SHOP_START_X+SHOP_SCROLL_START_X,
		CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y+m_nMouseScrollPosition[m_nCurrentTab]);
	m_pScrollBar->Render();
}
void CINFCityWarPointShop::Tick()
{
}
int CINFCityWarPointShop::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if( g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_SHOP_SELL_ITEM ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_SHOP_SELL_ENERGY ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_SHOP_MULTI_SELL_ITEM ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_STORE_MULTI_PUT_ITEM ) || 
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_STORE_MULTI_GET_ITEM )) // 2007-02-12 by bhsohn Item 다중 선택 처리		
	{
		return INF_MSGPROC_NORMAL;
	}
	switch(uMsg)
	{
	case WM_RBUTTONDOWN:
		{
			if(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_INVEN_POS)
			{
				CItemInfo* pItemInfo = (CItemInfo*)((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem->pItem;

				if(pItemInfo->Wear == WEAR_NOT_ATTACHED )
				{
					if( IS_COUNTABLE_ITEM(pItemInfo->Kind))
					{
						char buf[128];
						ITEM *pITEM = pItemInfo->GetItemInfo();
						if(pITEM)
						{
							char temp1[64];
							char temp2[64];
							wsprintf( temp1, "%d", CAtumSJ::GetItemSellingPriceAtShop(pITEM) );
							MakeCurrencySeparator( temp2, temp1, 3, ',' );
							wsprintf( buf, STRMSG_C_SHOP_0007, pITEM->ItemName, pITEM->MinTradeQuantity, temp2 );//"%s 몇개 파시겠습니까?[가격:%d개당 %s(스피)]"
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_SHOP_SELL_ENERGY,
								(DWORD)pItemInfo, 
								pItemInfo->CurrentCount);
						}
						else
						{
							g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_SHOP_0008, COLOR_SYSTEM );//"서버로부터 정보 받는 중... 다시 시도 하세요."
						}
					}
					else
					{
						char buf[128];
						ITEM *pITEM = pItemInfo->GetItemInfo();
						if(pITEM)
						{
							char temp1[64];
							char temp2[64];
							wsprintf( temp1, "%d", CAtumSJ::GetItemSellingPriceAtShop(pITEM) );
							MakeCurrencySeparator( temp2, temp1, 3, ',' );
							wsprintf( buf, STRMSG_C_SHOP_0009, pITEM->ItemName, temp2);//"%s 를 파시겠습니까?[가격:%s(스피)]"
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_SHOP_SELL_ITEM,
								(DWORD)pItemInfo);
						}
						else
						{
							g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_SHOP_0008, COLOR_SYSTEM );//"서버로부터 정보 받는중...다시 시도하세요."
						}
					}
				}
				else
				{
					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_SHOP_0010, _MESSAGE );//"장착된 아이템은 팔 수 없습니다."
				}

			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.x > CITY_SHOP_START_X &&
				pt.x < CITY_SHOP_START_X+BOX_SIZE_X &&
				pt.y > CITY_SHOP_START_Y &&
				pt.y < CITY_SHOP_START_Y+BOX_SIZE_Y )
			{
				if( pt.x> CITY_SHOP_START_X+SHOP_OK_BUTTON_START_X && 
					pt.x<CITY_SHOP_START_X+SHOP_OK_BUTTON_START_X+SHOP_OK_BUTTON_SIZE_X &&
					pt.y>CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y && 
					pt.y<CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y+SHOP_OK_BUTTON_SIZE_Y)
				{
					if(m_nOkButtonState != BUTTON_STATE_DOWN)
					{
						m_nOkButtonState = BUTTON_STATE_UP;
					}
				}
				else
				{
					m_nOkButtonState = BUTTON_STATE_NORMAL;
				}
				if( pt.x> CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X && 
					pt.x<CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X+SHOP_OK_BUTTON_SIZE_X &&
					pt.y>CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y &&
					pt.y<CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y+SHOP_OK_BUTTON_SIZE_Y)
				{
					if(m_nCancelButtonState != BUTTON_STATE_DOWN)
					{
						m_nCancelButtonState = BUTTON_STATE_UP;
					}
				}
				else
				{
					m_nCancelButtonState = BUTTON_STATE_NORMAL;
				}
				for(int i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
				{
					if( pt.x > CITY_SHOP_START_X+SHOP_ICON_START_X && 
						pt.x < CITY_SHOP_START_X+SHOP_ICON_START_X+SHOP_ICON_SIZE &&
						pt.y > CITY_SHOP_START_Y+SHOP_ICON_START_Y+SHOP_ITEM_SLOT_INTERVAL*i &&
						pt.y < CITY_SHOP_START_Y+SHOP_ICON_START_Y+SHOP_ITEM_SLOT_INTERVAL*i+SHOP_ICON_SIZE)
					{
						vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[m_nCurrentTab].begin();
						for( int j=0;j<i+m_nCurrentScrollNumber[m_nCurrentTab];j++)
						{
							if(it != m_vecItemInfo[m_nCurrentTab].end())
							{
								it++;
							}
							else
							{
								break;
							}
						}
						if(it != m_vecItemInfo[m_nCurrentTab].end())
						{
							((CINFGameMain*)m_pParent)->SetItemInfo( 0, (*it)->ItemNum, pt.x, pt.y);
						}
						break;
					}
					else if( pt.x > CITY_SHOP_START_X+SHOP_ICON_START_X+SHOP_ICON_SIZE ||
						(pt.x > CITY_SHOP_START_X+END_OF_INVEN_X && pt.x < CITY_SHOP_START_X+SHOP_ICON_START_X) ||
						pt.y < CITY_SHOP_START_Y+SHOP_ICON_START_Y-5 ||
						pt.y > CITY_SHOP_START_Y+SHOP_ICON_START_Y+SHOP_ITEM_SLOT_INTERVAL*SHOP_ITEM_SLOT_NUMBER)
					{
						((CINFGameMain*)m_pParent)->SetItemInfo( 0, NULL, 0, 0);
					}

				}
			}
			else
			{
				((CINFGameMain*)m_pParent)->SetItemInfo( 0, NULL, 0, 0);
			}
			if(m_bScrollLock)
			{
				if(pt.x > CITY_SHOP_START_X+SHOP_SCROLL_START_X - 4 && 
					pt.x < CITY_SHOP_START_X+SHOP_SCROLL_START_X+SHOP_SCROLL_SIZE_X + 5)
				{
					if(pt.y > CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y &&
						pt.y < CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y+SHOP_SCROLL_LENGTH)
					{
	//					int interval = SHOP_SCROLL_INTERVAL(m_nCurrentTab);
						if(GetScrollLine() > 0)
						{
							int nMove = pt.y - m_ptMouse.y;
						if(nMove != 0)
						{
								m_nMouseScrollPosition[m_nCurrentTab] += nMove; 
								m_nCurrentScrollNumber[m_nCurrentTab] = GetScrollLineNumber(m_nMouseScrollPosition[m_nCurrentTab]);
								if(m_nMouseScrollPosition[m_nCurrentTab] <= 0)
								{
								m_nCurrentScrollNumber[m_nCurrentTab] = 0;
									m_nMouseScrollPosition[m_nCurrentTab] = 0;
								}
								else if(m_nMouseScrollPosition[m_nCurrentTab] >= SHOP_SCROLL_MOVE_LENGTH)
								{
									m_nCurrentScrollNumber[m_nCurrentTab] = GetScrollLine();
									m_nMouseScrollPosition[m_nCurrentTab] = SHOP_SCROLL_MOVE_LENGTH;
								}

							m_ptMouse = pt;
						}
						}
					}
					else if(pt.y <= CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y)
					{
						m_nCurrentScrollNumber[m_nCurrentTab] = 0;	
						m_nMouseScrollPosition[m_nCurrentTab] = 0;
					}
					else if(pt.y >= CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y+SHOP_SCROLL_LENGTH)
					{
						m_nCurrentScrollNumber[m_nCurrentTab] = GetScrollLine();
						m_nMouseScrollPosition[m_nCurrentTab] = SHOP_SCROLL_MOVE_LENGTH;
					}
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			m_bScrollLock = FALSE;
			if( pt.x>CITY_SHOP_START_X+ SHOP_OK_BUTTON_START_X && 
				pt.x<CITY_SHOP_START_X+SHOP_OK_BUTTON_START_X+SHOP_OK_BUTTON_SIZE_X &&
				pt.y>CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y && 
				pt.y<CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y+SHOP_OK_BUTTON_SIZE_Y)
			{
				m_nOkButtonState = BUTTON_STATE_DOWN;
			}
			if( pt.x>CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X && 
				pt.x<CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X+SHOP_OK_BUTTON_SIZE_X &&
				pt.y>CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y && 
				pt.y<CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y+SHOP_OK_BUTTON_SIZE_Y)
			{
				m_nCancelButtonState = BUTTON_STATE_DOWN;
			}
			for(int i=0;i<SHOP_TAB_NUMBER;i++)
			{
				if( pt.x>CITY_SHOP_START_X+SHOP_TAB_START_X+SHOP_TAB_BUTTON_SIZE_X*i && 
					pt.x<CITY_SHOP_START_X+SHOP_TAB_START_X+SHOP_TAB_BUTTON_SIZE_X*(i+1) &&
					pt.y>CITY_SHOP_START_Y+SHOP_TAB_START_Y && 
					pt.y<CITY_SHOP_START_Y+SHOP_TAB_START_Y+SHOP_TAB_BUTTON_SIZE_Y)
				{
					OnCancelButtonClicked();
					m_nCurrentTab = i;
				}
			}
			if( pt.x > CITY_SHOP_START_X+SHOP_SCROLL_START_X && 
				pt.x < CITY_SHOP_START_X+SHOP_SCROLL_START_X+SHOP_SCROLL_SIZE_X &&
				GetScrollLine() > 0)
			{
				if( pt.y > CITY_SHOP_START_Y+SHOP_SCROLL_UP_START_Y && 
					pt.y<CITY_SHOP_START_Y+SHOP_SCROLL_UP_START_Y+SHOP_SCROLL_SIZE_Y)
				{
					m_nCurrentScrollNumber[m_nCurrentTab]--;
					if(m_nCurrentScrollNumber[m_nCurrentTab]<0)
					{
						m_nCurrentScrollNumber[m_nCurrentTab] = 0;
						m_nMouseScrollPosition[m_nCurrentTab] = 0;
					}
					else
					{
						m_nMouseScrollPosition[m_nCurrentTab] = GetScrollLineInterval(m_nCurrentScrollNumber[m_nCurrentTab]);
					}
				}
				if( pt.y > CITY_SHOP_START_Y+SHOP_SCROLL_DOWN_START_Y && 
					pt.y<CITY_SHOP_START_Y+SHOP_SCROLL_DOWN_START_Y+SHOP_SCROLL_SIZE_Y)
				{
					m_nCurrentScrollNumber[m_nCurrentTab]++;
					if(m_nCurrentScrollNumber[m_nCurrentTab] > GetScrollLine())
					{
						m_nCurrentScrollNumber[m_nCurrentTab] = GetScrollLine();
						m_nMouseScrollPosition[m_nCurrentTab] = SHOP_SCROLL_MOVE_LENGTH;
					}
					else
					{
						m_nMouseScrollPosition[m_nCurrentTab] = GetScrollLineInterval(m_nCurrentScrollNumber[m_nCurrentTab]);
					}
				}
				if( pt.y > CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y+m_nMouseScrollPosition[m_nCurrentTab] &&
					pt.y < CITY_SHOP_START_Y+SHOP_SCROLL_BAR_START_Y+m_nMouseScrollPosition[m_nCurrentTab]+SHOP_SCROLL_BAR_SIZE_Y)
				{
					m_bScrollLock = TRUE;
					m_ptMouse = pt;
				}
			}
			if( pt.x > CITY_SHOP_START_X+SHOP_NUMBER_BUTTON_X && 
				pt.x < CITY_SHOP_START_X+SHOP_NUMBER_BUTTON_X+SHOP_NUMBER_BUTTON_SIZE_X)
			{
				for(int i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
				{
					if( pt.y>CITY_SHOP_START_Y+SHOP_NUMBER_UP_BUTTON_Y+SHOP_ITEM_SLOT_INTERVAL*i &&
						pt.y<CITY_SHOP_START_Y+SHOP_NUMBER_UP_BUTTON_Y+SHOP_ITEM_SLOT_INTERVAL*i+SHOP_NUMBER_BUTTON_SIZE_Y)
					{
						if(m_vecItemInfo[m_nCurrentTab].size() > i+m_nCurrentScrollNumber[m_nCurrentTab] )
						{
							int temp = m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]];
							if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_TUNING_COLOR)
							{
								if(m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] >= 1)
									m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] = 1;
								else
									m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] += 
									m_vecItemInfo[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]->MinTradeQuantity;
							}
							else
							{
								USHORT nCount = m_vecItemInfo[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]->MinTradeQuantity;
								m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] += nCount;
							}
							// 2007-07-06 by dgwoo 스피에서 워포인트로..
							//if( GetTotalWarPointPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
							if( GetTotalWarPointPrice() > g_pShuttleChild->GetMyShuttleInfo().WarPoint)
							{//더한 후 price가 원래돈보다 많으면 취소해야 한다.
								m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] = temp;
							}
						}
//						int temp = m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]++;
//						if( GetTotalPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
//						{//더한 후 price가 원래돈보다 많으면 취소해야 한다.
//							m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] = temp;
//						}
					}
					if( pt.y>CITY_SHOP_START_Y+SHOP_NUMBER_DOWN_BUTTON_Y+SHOP_ITEM_SLOT_INTERVAL*i &&
						pt.y<CITY_SHOP_START_Y+SHOP_NUMBER_DOWN_BUTTON_Y+SHOP_ITEM_SLOT_INTERVAL*i+SHOP_NUMBER_BUTTON_SIZE_Y)
					{
						if(m_vecItemInfo[m_nCurrentTab].size() > i+m_nCurrentScrollNumber[m_nCurrentTab] )
						{
							int temp = m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]];
							m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] -= 
								m_vecItemInfo[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]->MinTradeQuantity;
							if(m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]<0)
								m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] = 0;
						}
//						m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] --;
//						if(m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]<0)
//							m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] = 0;
					}
				}
			}
			if( pt.x > CITY_SHOP_START_X+SHOP_ITEM_SLOT_START_X && 
				pt.x < CITY_SHOP_START_X+SHOP_ITEM_SLOT_START_X + SHOP_ITEM_SLOT_SIZE_X)
			{
				for(int i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
				{
					if( pt.y > CITY_SHOP_START_Y+SHOP_ITEM_SLOT_START_Y+SHOP_ITEM_SLOT_SIZE_Y*i &&
						pt.y < CITY_SHOP_START_Y+SHOP_ITEM_SLOT_START_Y+SHOP_ITEM_SLOT_SIZE_Y*(i+1))
					{
//						OnCancelButtonClicked();
						if(m_nCurrentSelectSlot[m_nCurrentTab] != m_nCurrentScrollNumber[m_nCurrentTab]+i)						
							OnCancelButtonClicked();
						m_nCurrentSelectSlot[m_nCurrentTab] = m_nCurrentScrollNumber[m_nCurrentTab]+i;
						OnChangeWearItem();
					}
				}
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			if( pt.x > CITY_SHOP_START_X+SHOP_ITEM_SLOT_START_X &&
				pt.x < CITY_SHOP_START_X+SHOP_ITEM_SLOT_START_X+SHOP_ITEM_SLOT_SIZE_X &&
				pt.y > CITY_SHOP_START_Y+SHOP_ITEM_SLOT_START_Y &&
				pt.y < CITY_SHOP_START_Y+SHOP_ITEM_SLOT_START_Y+SHOP_ITEM_SLOT_SIZE_Y*SHOP_ITEM_SLOT_NUMBER &&
				GetScrollLine() > 0)
			{
				if((int)wParam<0)
				{
					m_nCurrentScrollNumber[m_nCurrentTab]++;
					if(m_nCurrentScrollNumber[m_nCurrentTab] > GetScrollLine())
					{
						m_nCurrentScrollNumber[m_nCurrentTab] = GetScrollLine();
						m_nMouseScrollPosition[m_nCurrentTab] = SHOP_SCROLL_MOVE_LENGTH;
					}
					else
					{
						m_nMouseScrollPosition[m_nCurrentTab] = GetScrollLineInterval(m_nCurrentScrollNumber[m_nCurrentTab]);
					}
//					if(m_nCurrentScrollNumber[m_nCurrentTab]>SHOP_SCROLL_LENGTH/SHOP_SCROLL_INTERVAL(m_nCurrentTab))
//						m_nCurrentScrollNumber[m_nCurrentTab] = SHOP_SCROLL_LENGTH/SHOP_SCROLL_INTERVAL(m_nCurrentTab);
					return INF_MSGPROC_BREAK;
				}
				else
				{
					m_nCurrentScrollNumber[m_nCurrentTab]--;
					if(m_nCurrentScrollNumber[m_nCurrentTab]<0)
					{
						m_nCurrentScrollNumber[m_nCurrentTab] = 0;
						m_nMouseScrollPosition[m_nCurrentTab] = 0;
					}
					else
					{
						m_nMouseScrollPosition[m_nCurrentTab] = GetScrollLineInterval(m_nCurrentScrollNumber[m_nCurrentTab]);
					}

					return INF_MSGPROC_BREAK;
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			m_bScrollLock = FALSE;
			if( pt.x>CITY_SHOP_START_X+ SHOP_OK_BUTTON_START_X && 
				pt.x<CITY_SHOP_START_X+SHOP_OK_BUTTON_START_X+SHOP_OK_BUTTON_SIZE_X &&
				pt.y>CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y &&
				pt.y<CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y+SHOP_OK_BUTTON_SIZE_Y)
			{
				int nBuy = 0;
				if(m_nOkButtonState == BUTTON_STATE_DOWN)
				{
					for(int i=0; i<SHOP_ITEM_TAB_NUMBER; i++)
					{
						for(int j=0; j<m_vecItemInfo[i].size(); j++)
						{
							if(m_pnSelectItemNumber[i][j])
							{
								nBuy = 1;
							}
						}
					}
					if(nBuy)
					{
						OnOkButtonClicked();
					}
					else
					{
						OnBuyButtonClicked(m_nCurrentSelectSlot[m_nCurrentTab]);
					}
				}
				m_nOkButtonState = BUTTON_STATE_UP;
			}
			if( pt.x>CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X && 
				pt.x<CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X+SHOP_OK_BUTTON_SIZE_X &&
				pt.y>CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y && 
				pt.y<CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y+SHOP_OK_BUTTON_SIZE_Y)
			{
				if(m_nCancelButtonState == BUTTON_STATE_DOWN)
				{
					OnCancelButtonClicked();
				}
				m_nCancelButtonState = BUTTON_STATE_UP;
			}

			if(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_INVEN_POS &&
				pt.x > CITY_SHOP_START_X+SHOP_SELL_ITEM_START_X && 
				pt.x < CITY_SHOP_START_X+SHOP_SELL_ITEM_END_X &&
				pt.y > CITY_SHOP_START_Y+SHOP_SELL_ITEM_START_Y &&
				pt.y<CITY_SHOP_START_Y+SHOP_SELL_ITEM_END_Y)
			{
				CItemInfo* pItemInfo = (CItemInfo*)((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem->pItem;

				if(pItemInfo->Wear == WEAR_NOT_ATTACHED )
				{
					// 2007-03-02 by bhsohn 다중 선택 추가 보안					
					int nSelItemCnt = g_pD3dApp->GetMultiSelectItem();
					if(nSelItemCnt <= 0)
					{						
					if( IS_COUNTABLE_ITEM(pItemInfo->Kind))
					{
						char buf[128];
						ITEM *pITEM = pItemInfo->GetItemInfo();
						if(pITEM)
						{
							char temp1[64];
							char temp2[64];
							wsprintf( temp1, "%d", CAtumSJ::GetItemSellingPriceAtShop(pITEM) );
							MakeCurrencySeparator( temp2, temp1, 3, ',' );
							wsprintf( buf, STRMSG_C_SHOP_0007, pITEM->ItemName, pITEM->MinTradeQuantity, temp2 );//"%s 몇개 파시겠습니까?[가격:%d개당 %s(스피)]"
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_SHOP_SELL_ENERGY,
								(DWORD)pItemInfo, 
								pItemInfo->CurrentCount);
						}
						else
						{
							g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_SHOP_0008, COLOR_SYSTEM );
						}
					}
					else
					{
						char buf[128];
						ITEM *pITEM = pItemInfo->GetItemInfo();						
						if(pITEM)
						{
							char temp1[64];
							char temp2[64];
							wsprintf( temp1, "%d", CAtumSJ::GetItemSellingPriceAtShop(pITEM) );
							MakeCurrencySeparator( temp2, temp1, 3, ',' );
							wsprintf( buf, STRMSG_C_SHOP_0009, pITEM->ItemName, temp2);
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_SHOP_SELL_ITEM,
								(DWORD)pItemInfo);
						}
						else
						{
							g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_SHOP_0008, COLOR_SYSTEM );
						}
					}
					}
					else
					{
						// 다중 아이템 선택 창 팝업 
						((CINFGameMain*)m_pParent)->PopupMultiItemSelect();
						// 2008-11-13 by bhsohn EP3-2 에서 다중 선택 판매 안되는 버그 수정
						((CINFGameMain*)m_pParent)->SetItemInfo( 0, 0, 0, 0 );
						g_pGameMain->ClearSetIconInfo();

						return INF_MSGPROC_BREAK;
						// end 2008-11-13 by bhsohn EP3-2 에서 다중 선택 판매 안되는 버그 수정
						
					}
					// end 2007-03-02 by bhsohn 다중 선택 추가 보안
				}
				else
				{
					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_SHOP_0010, _MESSAGE );
				}
			}

			((CINFGameMain*)m_pParent)->SetItemInfo( 0, 0, 0, 0 );
		}
		break;
		// 2009-01-30 by bhsohn 상점 숫자 입력 방식 변경
	case WM_CHAR:
		{
			char code = wParam;
// 			if(m_pnSelectItemNumber[m_nCurrentTab] && g_pD3dApp->m_bChatMode == FALSE && m_pBuildingInfo->BuildingKind != BUILDINGKIND_TUNING_COLOR)
// 			{
// 				if(code >= '0' && code <= '9' && m_nCurrentSelectSlot[m_nCurrentTab]>=0)
// 				{
// 					int temp = m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]];
// 					m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] *= 10;
// 					m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] += code - '0';
// 					// 2007-07-06 by dgwoo 스피에서 워포인트로..
// 					//if( GetTotalWarPointPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
// 					if( GetTotalWarPointPrice() > g_pShuttleChild->GetMyShuttleInfo().WarPoint)
// 						m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] = temp;
// 				}
// 				else if( code == VK_BACK )
// 				{
// 					if( m_nCurrentSelectSlot[m_nCurrentTab] >= 0 && 
// 						m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] > 0 )
// 					{
// 						m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] /= 10;
// 					}
// 				}
// 			}
			if( code == VK_ESCAPE )
			{
				OnCancelButtonClicked();
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(m_pnSelectItemNumber[m_nCurrentTab] && g_pD3dApp->m_bChatMode == FALSE && m_pBuildingInfo->BuildingKind != BUILDINGKIND_TUNING_COLOR)
			{
				DWORD dwCode = lParam;
				int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
				if(nNumber != -1  && m_nCurrentSelectSlot[m_nCurrentTab]>=0)
				{
					int temp = m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]];
					m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] *= 10;
					m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] += nNumber;
					// 2007-07-06 by dgwoo 스피에서 워포인트로..
					//if( GetTotalWarPointPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
					if( GetTotalWarPointPrice() > g_pShuttleChild->GetMyShuttleInfo().WarPoint)
						m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] = temp;
				}
				else if(0x000e0001 == dwCode)
				{
					if( m_nCurrentSelectSlot[m_nCurrentTab] >= 0 && 
						m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] > 0 )
					{
						m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] /= 10;
					}
				}
			}
		
		}
		break;
		// end 2009-01-30 by bhsohn 상점 숫자 입력 방식 변경
	}
	return INF_MSGPROC_NORMAL;
}
