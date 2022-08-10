// INFCityShop.cpp: implementation of the CINFCityShop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFCityShop.h"
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
//#define SHOP_SCROLL_NUMBER(i)		(m_mapItemInfo[i].size()<=0 ? 1:m_mapItemInfo[i].size())	// i��° ���� scroll number
#define SHOP_SCROLL_NUMBER(i)		(m_vecItemInfo[i].size()<=0 ? 0:m_vecItemInfo[i].size())	// i��° ���� scroll number
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

// 2006-03-07 by ispark, �� ���� ��ġ ����
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
#define SHOP_ITEM_NUMBER_Y			68//70
#define SHOP_CASH_START_Y			239//241
#define SHOP_ITEM_NAME_START_Y		51//53
#define SHOP_ITEM_PRICE_START_Y		68//70
#define FONT_TOTAL_PRICE_X			2
#define FONT_TOTAL_PRICE_Y			1
#define SHOP_TEX_X					CITY_SHOP_START_X + 420
#define SHOP_TEX_Y					CITY_SHOP_START_Y + 12
#else
#define SHOP_ITEM_NUMBER_Y			68//70//54
#define SHOP_CASH_START_Y			239//241
#define SHOP_ITEM_NAME_START_Y		51//53
#define SHOP_ITEM_PRICE_START_Y		68//70
#define FONT_TOTAL_PRICE_X			1
#define FONT_TOTAL_PRICE_Y			1//3
#define SHOP_TEX_X					CITY_SHOP_START_X + 420
#define SHOP_TEX_Y					CITY_SHOP_START_Y + 12
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CINFCityShop::CINFCityShop(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	FLOG( "CINFCityShop(CAtumNode* pParent)" );
	m_pParent = pParent;	// CGameMain*
	m_pGameData = NULL;

	int i;
	for(i=0;i<4;i++)
	{
		m_pOkButton[i] = NULL;
		m_pCancelButton[i] = NULL;
		m_pBuyButton[i] = NULL;// [3]�� NULL
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

CINFCityShop::~CINFCityShop()
{
	FLOG( "~CINFCityShop()" );
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


void CINFCityShop::InitData(BOOL bColorShop)//UINT nShopUniqueNumber, UINT nNPCTalkIndex)
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

HRESULT CINFCityShop::InitDeviceObjects()
{
	FLOG( "CINFCityShop::InitDeviceObjects()" );
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

		wsprintf(buf, "sbuy%d",i);//sbuy3�� ����.
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
	pDataHeader = FindResource("scash");
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

	return S_OK ;
}

HRESULT CINFCityShop::RestoreDeviceObjects()
{
	FLOG( "CINFCityShop::RestoreDeviceObjects()" );
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

	return S_OK ;
}

HRESULT CINFCityShop::DeleteDeviceObjects()
{
	FLOG( "CINFCityShop::DeleteDeviceObjects()" );
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
	return S_OK ;
}


HRESULT CINFCityShop::InvalidateDeviceObjects()
{
	FLOG( "CINFCityShop::InvalidateDeviceObjects()" );
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
	return S_OK ;
}


void CINFCityShop::Tick()
{
	FLOG( "CINFCityShop::Tick()" );


}

void CINFCityShop::Render()
{
	FLOG( "CINFCityShop::Render()" );
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
				wsprintf( temp1, "%d", (int)(CAtumSJ::GetCityWarTex(pItem->Price, m_fTexRate) + pItem->Price));
				MakeCurrencySeparator( temp2, temp1, 3, ',' );
				m_pFontItemName[i]->DrawText( CITY_SHOP_START_X+SHOP_ITEM_NAME_START_X, CITY_SHOP_START_Y+SHOP_ITEM_NAME_START_Y+SHOP_ITEM_SLOT_INTERVAL*i, GUI_FONT_COLOR, pItem->ItemName, 0L);
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
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
		wsprintf( temp1, "%d", GetTotalPrice() );
		MakeCurrencySeparator( temp2, temp1, 3, ',' );
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

	//////////////////
	// 2006-02-08 by ispark, ���� ����
	char chTexbuf[30] = {0,};
	sprintf(chTexbuf, STRMSG_C_060208_0000, m_fTexRate);
	m_pInfluenceTex->DrawText(SHOP_TEX_X, SHOP_TEX_Y, GUI_FONT_COLOR, chTexbuf, 0L);
}


int CINFCityShop::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFCityShop::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	if( g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_SHOP_SELL_ITEM ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_SHOP_SELL_ENERGY ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_SHOP_MULTI_SELL_ITEM ))
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
							wsprintf( buf, STRMSG_C_SHOP_0007, pITEM->ItemName, pITEM->MinTradeQuantity, temp2 );//"%s � �Ľðڽ��ϱ�?[����:%d���� %s(����)]"
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_SHOP_SELL_ENERGY,
								(DWORD)pItemInfo, 
								pItemInfo->CurrentCount);
						}
						else
						{
							g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_SHOP_0008, COLOR_SYSTEM );//"�����κ��� ���� �޴� ��... �ٽ� �õ� �ϼ���."
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
							wsprintf( buf, STRMSG_C_SHOP_0009, pITEM->ItemName, temp2);//"%s �� �Ľðڽ��ϱ�?[����:%s(����)]"
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_SHOP_SELL_ITEM,
								(DWORD)pItemInfo);
						}
						else
						{
							g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_SHOP_0008, COLOR_SYSTEM );//"�����κ��� ���� �޴���...�ٽ� �õ��ϼ���."
						}
					}
				}
				else
				{
					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_SHOP_0010, _MESSAGE );//"������ �������� �� �� �����ϴ�."
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
//			for(int i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
//			{
//				if( pt.x>CITY_SHOP_START_X+SHOP_BUY_BUTTON_START_X && 
//					pt.x<CITY_SHOP_START_X+SHOP_BUY_BUTTON_START_X+SHOP_BUY_BUTTON_SIZE_X &&
//					pt.y>CITY_SHOP_START_Y+SHOP_BUY_BUTTON_START_Y+SHOP_ITEM_SLOT_INTERVAL*i &&
//					pt.y<CITY_SHOP_START_Y+SHOP_BUY_BUTTON_START_Y+SHOP_BUY_BUTTON_SIZE_Y+SHOP_ITEM_SLOT_INTERVAL*i)
//				{
//					m_nBuyButtonState[i] = BUTTON_STATE_DOWN;
//				}
//			}
			int i;
			for(i=0;i<SHOP_TAB_NUMBER;i++)
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
				for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
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
								m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] += 
									m_vecItemInfo[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]->MinTradeQuantity;
							}

							if( GetTotalPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
							{//���� �� price�� ���������� ������ ����ؾ� �Ѵ�.
								m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]] = temp;
							}
						}
//						int temp = m_pnSelectItemNumber[m_nCurrentTab][i+m_nCurrentScrollNumber[m_nCurrentTab]]++;
//						if( GetTotalPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
//						{//���� �� price�� ���������� ������ ����ؾ� �Ѵ�.
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
				for(i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
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
//			for(int i=0;i<SHOP_ITEM_SLOT_NUMBER;i++)
//			{
//				if( pt.x>CITY_SHOP_START_X+SHOP_BUY_BUTTON_START_X && 
//					pt.x<CITY_SHOP_START_X+SHOP_BUY_BUTTON_START_X+SHOP_BUY_BUTTON_SIZE_X &&
//					pt.y>CITY_SHOP_START_Y+SHOP_BUY_BUTTON_START_Y+SHOP_ITEM_SLOT_INTERVAL*i && 
//					pt.y<CITY_SHOP_START_Y+SHOP_BUY_BUTTON_START_Y+SHOP_BUY_BUTTON_SIZE_Y+SHOP_ITEM_SLOT_INTERVAL*i)
//				{
//					if(m_nBuyButtonState[i] == BUTTON_STATE_DOWN)
//					{
//						OnBuyButtonClicked(i);
//					}
//					m_nBuyButtonState[i] = BUTTON_STATE_UP;
//				}
//			}

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
					// 2007-03-02 by bhsohn ���� ���� �߰� ����					
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
							wsprintf( buf, STRMSG_C_SHOP_0007, pITEM->ItemName, pITEM->MinTradeQuantity, temp2 );//"%s � �Ľðڽ��ϱ�?[����:%d���� %s(����)]"
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
						// ���� ������ ���� â �˾� 
						((CINFGameMain*)m_pParent)->PopupMultiItemSelect();
						// 2008-11-13 by bhsohn EP3-2 ���� ���� ���� �Ǹ� �ȵǴ� ���� ����
						g_pGameMain->SetItemInfo( 0, 0, 0, 0 );
						g_pGameMain->ClearSetIconInfo();
						return INF_MSGPROC_BREAK;
						// end 2008-11-13 by bhsohn EP3-2 ���� ���� ���� �Ǹ� �ȵǴ� ���� ����
					}
					// end 2007-03-02 by bhsohn ���� ���� �߰� ����
				}
				else
				{
					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_SHOP_0010, _MESSAGE );
				}
			}

			((CINFGameMain*)m_pParent)->SetItemInfo( 0, 0, 0, 0 );
		}
		break;
		// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
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
// 					if(GetTotalPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
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
			DWORD dwCode = lParam;
			if(m_pnSelectItemNumber[m_nCurrentTab] && g_pD3dApp->m_bChatMode == FALSE && m_pBuildingInfo->BuildingKind != BUILDINGKIND_TUNING_COLOR)
			{
				int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);				
				if((nNumber != -1 ) && m_nCurrentSelectSlot[m_nCurrentTab]>=0)
				{
					int temp = m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]];
					m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] *= 10;
					m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] += nNumber;
					if(GetTotalPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
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
		// end 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
	}
	return INF_MSGPROC_NORMAL;
}

void CINFCityShop::OnOkButtonClicked()
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
				// 2005-12-09 by ispark, ������ ������ ��
				if(m_pBuildingInfo->BuildingKind != BUILDINGKIND_TUNING_COLOR)
				{
					// 2008-07-16 by bhsohn �� ī���ͺ� ������ 10�� �̻� ���źҰ�
					//BuyItem((*it)->ItemNum, m_pnSelectItemNumber[tab][i]);
					BuyItem((*it)->ItemNum, m_pnSelectItemNumber[tab][i], (*it)->ItemKind);
				}
				else
					BuyItemColorShop((*it)->ItemNum);

				// 2005-03-07 by jschoi
//				g_pD3dApp->m_bRequestEnable = FALSE;
//
////				SHOP_ITEM* pItem = it->second;
//				SHOP_ITEM* pItem = *it;
//				MSG_FC_SHOP_BUY_ITEM sMsg;
//				memset(&sMsg,0x00,sizeof(sMsg));
//				sMsg.BuildingIndex = m_pBuildingInfo->BuildingIndex;
//				sMsg.ItemNum = pItem->ItemNum;
//				sMsg.Amount = m_pnSelectItemNumber[tab][i];
//				g_pFieldWinSocket->SendMsg( T_FC_SHOP_BUY_ITEM, (char*)&sMsg, sizeof(sMsg) );
//				m_pnSelectItemNumber[tab][i] = 0;
			}
			it++;
			i++;
		}
	}

}

void CINFCityShop::OnCancelButtonClicked()
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

void CINFCityShop::OnBuyButtonClicked(int nSlotNumber)
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
			if(GetTotalPrice() > ((CINFGameMain*)m_pParent)->m_pInven->GetItemSpi())
			{
				m_pnSelectItemNumber[m_nCurrentTab][m_nCurrentSelectSlot[m_nCurrentTab]] = 0;
					g_pD3dApp->m_pChat->CreateChatChild( STRMSG_C_SHOP_0011,COLOR_ERROR );//"�������� �����ϱ� ���� ���ǰ� �����մϴ�"
			}
		}
		if(m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber]>0)
		{
			if(m_pBuildingInfo->BuildingKind != BUILDINGKIND_TUNING_COLOR)
			{
				// 2008-07-16 by bhsohn �� ī���ͺ� ������ 10�� �̻� ���źҰ�
				//BuyItem((*it)->ItemNum, m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber]);
				BuyItem((*it)->ItemNum, m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber], (*it)->ItemKind);				
			}
			else
				BuyItemColorShop((*it)->ItemNum);

		}
		m_pnSelectItemNumber[m_nCurrentTab][nSlotNumber] = 0;
	}

}

UINT CINFCityShop::GetTotalPrice()
{
	FLOG( "CINFCityShop::GetTotalPrice()" );
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
				int price = pItem->Price * m_pnSelectItemNumber[tab][i] / (pItem->MinTradeQuantity == 0 ? 1.0f : pItem->MinTradeQuantity);
				int tex = CAtumSJ::GetCityWarTex(price, m_fTexRate); 
				total += price + tex;
			}
			it++;
			i++;
		}
	}
	
	return total;
}

void CINFCityShop::BuyItem(int nItemNum, int nAmount, int ItemKind)
{
	FLOG( "CINFCityShop::BuyItem(int nItemNum, int nAmount)" );

	// 2008-07-16 by bhsohn �� ī���ͺ� ������ 10�� �̻� ���źҰ�	
	if( !IS_COUNTABLE_ITEM(ItemKind) && IS_GENERAL_ITEM(ItemKind))
	{
		if(nAmount > MAX_ITEM_COUNTS_FOR_BUY)
		{
			char errStr[256];
			wsprintf(errStr,STRMSG_C_080716_0204);	// "�ش�������� �ѹ� ���Ž� �ִ� ������ 10���Դϴ�."	
			g_pD3dApp->m_pChat->CreateChatChild(errStr,COLOR_ERROR);
			return;
		}
	}	
	// end 2008-07-16 by bhsohn �� ī���ͺ� ������ 10�� �̻� ���źҰ�

	// 2005-03-07 by jschoi
	g_pD3dApp->m_bRequestEnable = FALSE;

	MSG_FC_SHOP_BUY_ITEM sMsg;
	memset(&sMsg,0x00,sizeof(sMsg));
	sMsg.BuildingIndex = m_pBuildingInfo->BuildingIndex;
	sMsg.ItemNum = nItemNum;
	sMsg.Amount = nAmount;
	g_pFieldWinSocket->SendMsg( T_FC_SHOP_BUY_ITEM, (char*)&sMsg, sizeof(sMsg) );
//	char buffer[SIZE_MAX_PACKET];
//	int nType = T_FC_SHOP_BUY_ITEM;
//	memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//	memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//	g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
}

void CINFCityShop::InputColorShopItem()
{
	// Į����� ���ý� Ŭ���̾�Ʈ ������ �˻��� ������ ����
	int i;
	for(i=0;i<4;i++)
	{
		// 2006-04-05 by ispark
		SAFE_DELETE_ARRAY(m_pnSelectItemNumber[i]);
		m_nCurrentScrollNumber[i] = 0;
		m_nCurrentSelectSlot[i] = -1;
		m_nMouseScrollPosition[i] = 0;
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

	CItemInfo *pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(POS_CENTER);
	if(pItemInfo)
	{
		for(i=1; i <= g_pD3dApp->GetUnitArmorColorMax();i++)
		{			
			ITEM *item = g_pDatabase->GetServerItemInfo(SOURCEINDEXTOITEMNUM(pItemInfo->ItemInfo->SourceIndex, i));
			if(item &&
				// 2007-08-10 by dgwoo ĳ���������� �÷��������� �Ǹ����� �ʴ´�.
				!COMPARE_BIT_FLAG(item->ItemAttribute, ITEM_ATTR_CASH_ITEM))		
			{
				SHOP_ITEM* pItemShop = new SHOP_ITEM;
				pItemShop->ItemNum							= item->ItemNum;
				strcpy(pItemShop->ItemName, item->ItemName);
				pItemShop->MinTradeQuantity					= item->MinTradeQuantity;
				pItemShop->Price							= item->Price;
				pItemShop->ItemKind							= item->Kind;
				
				// 2009-01-28 by bhsohn ĳ���� ó��
				pItemShop->CashShopIndex	= 0;
				// end 2009-01-28 by bhsohn ĳ���� ó��

				if(IS_BGEAR(item->ReqUnitKind))
				{					
					m_vecItemInfo[SHOP_TAB_B_GEAR].push_back(pItemShop);
					m_nCurrentTab = SHOP_TAB_B_GEAR;
				}
				if(IS_IGEAR(item->ReqUnitKind))
				{								
					m_vecItemInfo[SHOP_TAB_I_GEAR].push_back(pItemShop);
					m_nCurrentTab = SHOP_TAB_I_GEAR;
				}
				if(IS_MGEAR(item->ReqUnitKind))
				{					
					m_vecItemInfo[SHOP_TAB_M_GEAR].push_back(pItemShop);
					m_nCurrentTab = SHOP_TAB_M_GEAR;
				}
				if(IS_AGEAR(item->ReqUnitKind))
				{					
					m_vecItemInfo[SHOP_TAB_A_GEAR].push_back(pItemShop);
					m_nCurrentTab = SHOP_TAB_A_GEAR;
				}
			}
		}
	}
	
	for(i=0;i<4;i++)
	{
		SAFE_DELETE_ARRAY(m_pnSelectItemNumber[i]);
		if(m_vecItemInfo[i].size() > 0)
		{
			int num = m_vecItemInfo[i].size();
			m_pnSelectItemNumber[i] = new int[num];
			memset(m_pnSelectItemNumber[i], 0x00, num*sizeof(UINT));
		}
	}
}

int CINFCityShop::InputItem(char* pMsg)
{
	FLOG( "CINFCityShop::InputItem(char* pMsg)" );
	if(pMsg)
	{
		ITEM *item = g_pDatabase->GetServerItemInfo(((SHOP_ITEM*)pMsg)->ItemNum);
		if(item)
		{
			// 2006-01-11 by ispark, ���� ������ �ִ��� Ȯ��
			// ���� ���ؼ� �ߺ� �Է��� �Ǵ� ������ �ִ�. �׷��� ���� ������ ������ �Ѿ
		
			if(IS_BGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
//				m_mapItemInfo[SHOP_TAB_B_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_B_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_B_GEAR].push_back(pItem);
			}
			if(IS_IGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
//				m_mapItemInfo[SHOP_TAB_I_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_I_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_I_GEAR].push_back(pItem);
			}
			if(IS_MGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
//				m_mapItemInfo[SHOP_TAB_M_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_M_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_M_GEAR].push_back(pItem);
			}
			if(IS_AGEAR(item->ReqUnitKind))
			{
				SHOP_ITEM* pItem = new SHOP_ITEM;
				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
//				m_mapItemInfo[SHOP_TAB_A_GEAR][pItem->ItemNum] = pItem;
				if(FindCityShopData(SHOP_TAB_A_GEAR, pItem) == NULL)
					m_vecItemInfo[SHOP_TAB_A_GEAR].push_back(pItem);
			}
		}
		else
		{
			SHOP_ITEM* pItem = new SHOP_ITEM;
			memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
//			m_mapItemInfo[SHOP_TAB_B_GEAR][pItem->ItemNum] = pItem;
			if(FindCityShopData(SHOP_TAB_B_GEAR, pItem) == NULL)
			m_vecItemInfo[SHOP_TAB_B_GEAR].push_back(pItem);
		}
	}
	return sizeof(SHOP_ITEM);
}

void CINFCityShop::UpdateFindShopItem(int nTab, ITEM* pITEM)
{
	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[nTab].begin();
	while(it != m_vecItemInfo[nTab].end())
	{
		if( (*it)->ItemNum == pITEM->ItemNum )
		{
			(*it)->ItemKind = pITEM->Kind;
			strcpy( (*it)->ItemName, pITEM->ItemName );
			(*it)->ItemNum = pITEM->ItemNum;
			(*it)->MinTradeQuantity = pITEM->MinTradeQuantity;
			(*it)->Price = pITEM->Price;
			return;
		}
		it++;
	}
	SHOP_ITEM* pNew = new SHOP_ITEM;
	pNew->ItemKind = pITEM->Kind;
	strcpy( pNew->ItemName, pITEM->ItemName );
	pNew->ItemNum = pITEM->ItemNum;
	pNew->MinTradeQuantity = pITEM->MinTradeQuantity;
	pNew->Price = pITEM->Price;
	// 2009-01-28 by bhsohn ĳ���� ó��	
	pNew->CashShopIndex= 0;	
	// end 2009-01-28 by bhsohn ĳ���� ó��
	m_vecItemInfo[nTab].push_back( pNew );
}

void CINFCityShop::UpdateItem(int nItemNum)
{
	FLOG( "CINFCityShop::UpdateItem(int nItemNum)" );
	ITEM *pITEM = g_pDatabase->GetServerItemInfo(nItemNum);
	if(pITEM)
	{
		if(IS_BGEAR(pITEM->ReqUnitKind))
		{
			UpdateFindShopItem( SHOP_TAB_B_GEAR, pITEM);
		}
		if(IS_IGEAR(pITEM->ReqUnitKind))
		{
			UpdateFindShopItem( SHOP_TAB_B_GEAR, pITEM);
		}
		if(IS_MGEAR(pITEM->ReqUnitKind))
		{
			UpdateFindShopItem( SHOP_TAB_B_GEAR, pITEM);
		}
		if(IS_AGEAR(pITEM->ReqUnitKind))
		{
			UpdateFindShopItem( SHOP_TAB_B_GEAR, pITEM);
		}
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
	}
}


struct sort_EnergyItemByItemName
{
	bool operator()(SHOP_ITEM *p1, SHOP_ITEM *p2)
	{
		return strcmp(p1->ItemName, p2->ItemName) < 0;
	}
};


///////////////////////////////////////////////////////////////////////////////
/// \fn			void sortItemKindEnergyByItemName(vector<SHOP_ITEM*> *i_pVectorShopItemPtr)
/// \brief		
/// \author		cmkwon
/// \date		2004-12-03 ~ 2004-12-03
/// \warning	������ ���ʹ� ���ĵǾ� �־�� �Ѵ�
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void sortItemKindEnergyByItemName(vector<SHOP_ITEM*> *i_pVectorShopItemPtr)
{
	vector<SHOP_ITEM*>::iterator itStart = i_pVectorShopItemPtr->end(), itEnd = i_pVectorShopItemPtr->end();
	vector<SHOP_ITEM*>::iterator itr(i_pVectorShopItemPtr->begin());
	for (; itr != i_pVectorShopItemPtr->end(); itr++)
	{
		if ((*itr)->ItemKind == ITEMKIND_ENERGY)
		{
			if (itStart != i_pVectorShopItemPtr->end())
			{
				itStart = itr;
			}
			else
			{
				itEnd = itr;
			}
		}
	}

	if (itStart == i_pVectorShopItemPtr->end()
		|| itEnd == i_pVectorShopItemPtr->end())
	{
		return;
	}
	itEnd++;

	sort(itStart, itEnd, sort_EnergyItemByItemName());
}


int orderByKindRefineryItem(ITEM* i_pItem)
{
	switch(i_pItem->Kind)
	{
	case ITEMKIND_BULLET:
		{
		}
		return 100;
	case ITEMKIND_ENERGY:
		{
			// 2009-04-21 by bhsohn ������ DesParam�߰�
			//switch(i_pItem->DestParameter1)
			switch(i_pItem->ArrDestParameter[0])
			{
			case DES_GRADUAL_HP_UP:		return 101;
			case DES_GRADUAL_SP_UP:		return 102;
			case DES_GRADUAL_DP_UP:		return 103;
			case DES_GRADUAL_EP_UP:		return 104;
			}			
		}
		return 200;
	case ITEMKIND_SUPPORT:
		{
		}
		return 300;
	case ITEMKIND_TANK:
		{
		}
		return 400;
	case ITEMKIND_RADAR:
		{
			
		}
		return 500;
	}

	return 1000;
}


struct CompareRefineryItemByKind
{
	template<typename T>
		bool operator()(const T *pPtr1, const T *pPtr2)
	{
		ITEM* pITEM1 = g_pDatabase->GetServerItemInfo(pPtr1->ItemNum);
		ITEM* pITEM2 = g_pDatabase->GetServerItemInfo(pPtr2->ItemNum);
		if( pITEM1 == NULL || pITEM2 == NULL )
		{
			return false;
		}

		int order1 = orderByKindRefineryItem(pITEM1);		
		int order2 = orderByKindRefineryItem(pITEM2);
		if(order1 < order2)
		{
			return true;
		}
		return false;
	}
};

void CINFCityShop::InputItemDone()
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
			if(m_pBuildingInfo)
			{
				switch(m_pBuildingInfo->BuildingKind)
				{
				case BUILDINGKIND_REFINERY:
					{
						sort(m_vecItemInfo[i].begin(), m_vecItemInfo[i].end(), CompareRefineryItemByKind());

						sortItemKindEnergyByItemName(&m_vecItemInfo[i]);
					}
					break;
				default:
					{
						sort(m_vecItemInfo[i].begin(), m_vecItemInfo[i].end(), CompareLevel());
					}
				}
			}			
		}

	}
	//	m_bInputItemDone = TRUE;
	///////////////////////////////
	// UNLOCK BUILDING BUTTON
	///////////////////////////////
}


void CINFCityShop::SellItem( LONGLONG nUniqueNumber, int nAmount/*����**/, BYTE itemKind )
{
	FLOG( "CINFCityShop::SellItem( LONGLONG nUniqueNumber, int nAmount/*����*/, BYTE itemKind )" );
	
	// 2005-03-07 by jschoi
	g_pD3dApp->m_bRequestEnable = FALSE;

	MSG_FC_SHOP_SELL_ITEM sMsg;
	memset(&sMsg,0x00,sizeof(sMsg));
	char buffer[SIZE_MAX_PACKET];
	sMsg.Amount = nAmount;
	sMsg.ItemKind = itemKind;
	sMsg.ItemUniqueNumber = nUniqueNumber;
	sMsg.BuildingIndex = m_pBuildingInfo->BuildingIndex;
	int nType = T_FC_SHOP_SELL_ITEM;
	memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
	memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
	g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
}

void CINFCityShop::OnChangeWearItem()
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
				int nColorNum = item->ItemNum - nArmorColor;

				g_pGameMain->ChangeItemByShop(item->ItemNum, nColorNum);
			}
		}
	}
}


void CINFCityShop::BuyItemColorShop(int nItemNum)
{
	FLOG( "CINFCityShop::BuyItemColorShop(int nItemNum)" );
	// 2006-05-20 by ispark, �̹� �ϰ� �ִ� �����̶��
	CItemInfo *pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(POS_CENTER);
	if(pItemInfo)
	{
		int nArmorColor = 0;
		if(pItemInfo->ItemInfo->SourceIndex == 0)
			nArmorColor = pItemInfo->ItemNum;				
		else
			nArmorColor = pItemInfo->ItemInfo->SourceIndex;
		int nColorNum = nItemNum - nArmorColor;

		if(nColorNum == g_pShuttleChild->GetAmorColor())
		{
			char errStr[64];
			wsprintf(errStr,STRMSG_C_060519_0003);	// "���� ���� �ִ� Į���Դϴ�."
			g_pD3dApp->m_pChat->CreateChatChild(errStr,COLOR_ERROR);
			return;
		}
	}

	MSG_FC_SHOP_BUY_COLOR_ITEM sMsg;
	memset(&sMsg,0x00,sizeof(sMsg));
	sMsg.BuildingIndex = m_pBuildingInfo->BuildingIndex;
	sMsg.ItemNum = nItemNum;
	g_pFieldWinSocket->SendMsg( T_FC_SHOP_BUY_COLOR_ITEM, (char*)&sMsg, sizeof(sMsg) );
}

int CINFCityShop::GetScrollLine()
{
	int nInvenTotalNum = SHOP_SCROLL_NUMBER(m_nCurrentTab);
	int ntemp = nInvenTotalNum - SHOP_ITEM_SLOT_NUMBER;
	if(ntemp < 0)
	{
		ntemp = 0;
	}
	return ntemp;
}

float CINFCityShop::GetScrollLineInterval(int nScrollLineNum)
{
	int ntemp = GetScrollLine();
	float fLineNum = 0.0f;
	if(ntemp)
		fLineNum = (SHOP_SCROLL_MOVE_LENGTH * nScrollLineNum) / ntemp;

	return fLineNum;
}

int CINFCityShop::GetScrollLineNumber(float nLength)
{
	int ntemp = GetScrollLine();
	float fLineNum = (nLength * ntemp) / SHOP_SCROLL_MOVE_LENGTH;

	return (int)fLineNum;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityShop::FindCityShopData(SHOP_ITEM *pShopItem)
/// \brief		�� ������ �˻�
/// \author		ispark
/// \date		2006-01-11 ~ 2006-01-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
SHOP_ITEM* CINFCityShop::FindCityShopData(int nTabIndex, SHOP_ITEM *pShopItem)
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

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityShop::FindCityShopDataByColor(int nIndex)
/// \brief		�������� ���� ����Ÿ�� �̴���.
/// \author		ispark
/// \date		2006-05-19 ~ 2006-05-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
SHOP_ITEM* CINFCityShop::FindCityShopDataByColor(int nColor)
{
	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[m_nCurrentTab].begin();
	while(it != m_vecItemInfo[m_nCurrentTab].end())
	{
		SHOP_ITEM* pitShopSkill = *it;
		ITEM* item = g_pDatabase->GetServerItemInfo(pitShopSkill->ItemNum);

		if(item->ItemNum == nColor)
		{
			return pitShopSkill;
		}
		it++;
	}
			
	return NULL;
}
