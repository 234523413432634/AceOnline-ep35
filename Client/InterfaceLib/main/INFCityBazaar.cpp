// INFCityBazaar.cpp: implementation of the CINFCityBazaar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFCityBazaar.h"
#include "INFCityBase.h"
#include "INFScrollbar.h"
#include "INFImage.h"
#include "D3dHanFont.h"
#include "ItemInfo.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "FieldWinSocket.h"
#include "GameDataLast.h"
#include "StoreData.h"
#include "WeaponItemInfo.h"
#include "INFWindow.h"
#include "INFGameMain.h"
#include "INFItemInfo.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFIcon.h"
#include "AtumDatabase.h"
#include "dxutil.h"
#include "Chat.h"
#include "INFComboBoxEX.h"
#include "Interface.h"
#include "INFGameMainChat.h"
#include "ChatTab_t.h"
#include "SceneData.h"
#include "EnemyData.h"
#include "AtumSound.h"
#include "ChatMoveData.h"

#define CITY_SHOP_START_X				(CITY_BASE_NPC_BOX_START_X + 230)
#define CITY_SHOP_START_Y				(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y - 9)

// 2006-08-29 by dgwoo 
#define BAZAAR_SHOP_MINIBAR_W			210
#define	BAZAAR_SHOP_MINIBAR_H			18
#define BAZAAR_SHOP_MINIBAR_Y			(g_pD3dApp->GetBackBufferDesc().Height - 39 - BAZAAR_SHOP_MINIBAR_H)
#define BAZAAR_SHOP_MINIBAR_X			((g_pD3dApp->GetBackBufferDesc().Width-BAZAAR_SHOP_MINIBAR_W))

#define BAZAAR_SHOP_WINDOW_X			(CITY_SHOP_START_X + 194)
#define BAZAAR_SHOP_WINDOW_Y			(CITY_SHOP_START_Y + 9)
#define BAZAAR_SHOP_WINDOW_W			339
#define BAZAAR_SHOP_WINDOW_H			275

#define BAZAAR_SHOP_TAB_START_X			(BAZAAR_SHOP_WINDOW_X + 11)
#define BAZAAR_SHOP_TAB_START_Y			(BAZAAR_SHOP_WINDOW_Y + 30)
#define BAZAAR_SHOP_TAB_W				46
#define BAZAAR_SHOP_TAB_H				14
#define BAZAAR_SHOP_TAB_BACK_W			316
#define BAZAAR_SHOP_TAB_BACK_H			208

#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_X	(BAZAAR_SHOP_WINDOW_X + 181)
#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_Y	(BAZAAR_SHOP_WINDOW_Y + 22)
#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_W	132


#define BAZAAR_OPEN_NAME_X				BAZAAR_VISIT_TOTAL_PRICE_X
#define BAZAAR_OPEN_NAME_Y				BAZAAR_VISIT_TOTAL_PRICE_Y

#define BAZAAR_SHOP_OPEN_START_X		(BAZAAR_SHOP_WINDOW_X + 253)
#define BAZAAR_SHOP_OPEN_START_Y		(BAZAAR_SHOP_WINDOW_Y + 243)
#define BAZAAR_SHOP_OPEN_STOP_X			(BAZAAR_SHOP_WINDOW_X + 292)
#define BAZAAR_SHOP_OPEN_STOP_Y			BAZAAR_SHOP_OPEN_START_Y


#define BAZAAR_SHOP_ITEM_X				(BAZAAR_SHOP_WINDOW_X + 17)
#define BAZAAR_SHOP_ITEM_Y				(BAZAAR_SHOP_WINDOW_Y + 51)
#define BAZAAR_SHOP_ITEM_W				290
#define BAZAAR_SHOP_ITEM_H				36
#define BAZAAR_SHOP_SELITEM_X			(BAZAAR_SHOP_WINDOW_X + 16)
#define BAZAAR_SHOP_SELITEM_Y			(BAZAAR_SHOP_WINDOW_Y + 50)

//?????? ?????? ????.
#define	BAZAAR_SHOP_MIN_X				(BAZAAR_SHOP_WINDOW_X + 316)
#define	BAZAAR_SHOP_MIN_Y				(BAZAAR_SHOP_WINDOW_Y + 5)
#define BAZAAR_SHOP_ACT_X				(BAZAAR_SHOP_MINIBAR_X + 195)
#define BAZAAR_SHOP_ACT_Y				(BAZAAR_SHOP_MINIBAR_Y + 4)
#define	BAZAAR_SHOP_MIN_H				12
#define BAZAAR_SHOP_MIN_W				10

#define BAZAAR_SHOP_ICON_X				(BAZAAR_SHOP_ITEM_X + 4)
#define BAZAAR_SHOP_ICON_Y				(BAZAAR_SHOP_ITEM_Y + 4)
#define BAZAAR_SHOP_ICON_WH				28

#define BAZAAR_SHOP_RIGHT_BTN_X			(BAZAAR_SHOP_WINDOW_X + 267)
#define BAZAAR_SHOP_RIGHT_BTN_Y			(BAZAAR_SHOP_WINDOW_Y + 60)

#define BAZAAR_SHOP_LOG_STRING_LENGTH	282
#define BAZAAR_SHOP_LOG_X				(BAZAAR_SHOP_WINDOW_X + 21)
#define BAZAAR_SHOP_LOG_Y				(BAZAAR_SHOP_WINDOW_Y + 51)
#define BAZAAR_SHOP_LOG_LINE_COUNT		12

//|-------------------------------------------------|
//|		1	  			|			2		   	    |
//|-------------------------------------------------|
//|		3				|			4			    |
//|-------------------------------------------------|

#define BAZAAR_OPEN_1_BUY_X				(BAZAAR_SHOP_ITEM_X+40)
#define BAZAAR_OPEN_1_SEL_X				(BAZAAR_SHOP_ITEM_X+62)
#define BAZAAR_OPEN_1_Y					(BAZAAR_SHOP_ITEM_Y+2)
#define BAZAAR_OPEN_1_BUY_W				75
#define BAZAAR_OPEN_1_SEL_W				67
#define BAZAAR_OPEN_1_H					13

#define BAZAAR_OPEN_2_SEL_X				(BAZAAR_SHOP_ITEM_X+160)
#define BAZAAR_OPEN_2_BUY_X				(BAZAAR_SHOP_ITEM_X+161)
#define BAZAAR_OPEN_2_Y					(BAZAAR_SHOP_ITEM_Y+2)
#define	BAZAAR_OPEN_2_SEL_W				85
#define	BAZAAR_OPEN_2_BUY_W				BAZAAR_OPEN_2_SEL_W
#define BAZAAR_OPEN_3_BUY_X				(BAZAAR_SHOP_ITEM_X+40)
#define BAZAAR_OPEN_3_Y					(BAZAAR_SHOP_ITEM_Y+16)
#define BAZAAR_OPEN_4_SEL_X				BAZAAR_OPEN_2_SEL_X
#define BAZAAR_OPEN_4_BUY_X				BAZAAR_OPEN_2_SEL_X
#define BAZAAR_OPEN_4_Y					(BAZAAR_SHOP_ITEM_Y+16)



//???? ?????? ???????? ???? ??????.
#define BAZAAR_OPEN_1_ICON_X			(BAZAAR_SHOP_ITEM_X+118)
#define BAZAAR_OPEN_1_ICON_Y			(BAZAAR_SHOP_ITEM_Y+7)
#define BAZAAR_OPEN_1_ICON_W			100
#define BAZAAR_OPEN_2_ICON_X			(BAZAAR_SHOP_ITEM_X+118)
#define BAZAAR_OPEN_2_ICON_Y			(BAZAAR_SHOP_ITEM_Y+BAZAAR_OPEN_1_H+8)

//???? ?????? ???????? ????.
#define BAZAAR_OPEN_COMBO_KIND_X		BAZAAR_OPEN_1_X
#define BAZAAR_OPEN_COMBO_KIND_Y		(BAZAAR_OPEN_1_Y+BAZAAR_OPEN_1_H)
#define BAZAAR_OPEN_COMBO_NAME_X		BAZAAR_OPEN_1_X
#define BAZAAR_OPEN_COMBO_NAME_Y		(BAZAAR_OPEN_1_Y+BAZAAR_OPEN_1_H+BAZAAR_OPEN_1_H)

#define BAZAAR_SHOP_BTN_W				36
#define BAZAAR_SHOP_BTN_H				19
#define BAZAAR_SHOP_BTN_OUT_W			48

#define BAZAAR_SHOP_SCROLL_MAX_LINE		(BAZAARSHOP_ITEMCOUNT - SHOP_ITEM_SLOT_NUMBER)
#define BAZAAR_SHOP_OPEN_SCROLL_X		(BAZAAR_SHOP_TAB_START_X + 301)
#define BAZAAR_SHOP_SCROLL_Y			(BAZAAR_SHOP_WINDOW_Y + 52)
#define BAZAAR_SHOP_SCROLL_W			11
#define BAZAAR_SHOP_SCROLL_H			38
#define BAZAAR_SHOP_SCROLL_LINE_LENGTH	(181 - BAZAAR_SHOP_SCROLL_H)


/*--------------------------------------------------------------------------*/
//   Visit
#define BAZAAR_VISIT_TOTAL_PRICE_X	(BAZAAR_SHOP_WINDOW_X + 11)
#define BAZAAR_VISIT_TOTAL_PRICE_Y	(BAZAAR_SHOP_WINDOW_Y + 243)
#define BAZAAR_VISIT_TOTAL_PRICE_W	230

#define	BAZAAR_VISIT_TEXT_H             13

#define BAZAAR_VISIT_NAME_X				(BAZAAR_SHOP_ITEM_X+38)
#define BAZAAR_VISIT_NAME_Y				(BAZAAR_SHOP_ITEM_Y+2)
#define BAZAAR_VISIT_NAME_W				208

#define BAZAAR_VISIT_OUT_X				(BAZAAR_SHOP_WINDOW_X + 279)
#define BAZAAR_VISIT_OUT_Y				BAZAAR_SHOP_OPEN_START_Y

#define BAZAAR_SHOP_VISIT_SCROLL_X			(BAZAAR_SHOP_TAB_START_X + 300)

//SEL
#define	BAZAAR_VISIT_SEL_PRICE_X		(BAZAAR_SHOP_ITEM_X+66)
#define	BAZAAR_VISIT_SEL_PRICE_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define	BAZAAR_VISIT_SEL_PRICE_W		85

#define BAZAAR_VISIT_SEL_COUNT_X		(BAZAAR_SHOP_ITEM_X+201)
#define BAZAAR_VISIT_SEL_COUNT_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define BAZAAR_VISIT_SEL_COUNT_W		45

#define BAZAAR_VISIT_SEL_ITEM_COUNT_X	(BAZAAR_SHOP_ICON_X + 25)
#define BAZAAR_VISIT_SEL_ITEM_COUNT_Y	BAZAAR_SHOP_ICON_Y

//BUY
#define	BAZAAR_VISIT_BUY_PRICE_X		(BAZAAR_SHOP_ITEM_X+67)
#define	BAZAAR_VISIT_BUY_PRICE_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define	BAZAAR_VISIT_BUY_PRICE_W		70

#define BAZAAR_VISIT_BUY_COUNT_X		(BAZAAR_SHOP_ITEM_X+182)
#define BAZAAR_VISIT_BUY_COUNT_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define BAZAAR_VISIT_BUY_COUNT_W		64

#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn ???? ???? ????
#define STRING_CULL ::StringCullingUserData_ToBlank
#else
#define STRING_CULL ::StringCullingUserDataEx
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityBazaar::CINFCityBazaar()
{
	m_pGameData			= NULL;
	m_byBazaarType		= 0;
	m_byBazaarTypeState	= 0;

	m_bLButtonDown		= FALSE;
	m_bScrollLock		= FALSE;

	m_nScrollBtn		= 0;

	m_bBazaarShopStart  = FALSE;
	m_bBazaarShopEnd	= FALSE;

	g_pInterface->SetWindowOrder(WNDBazaarShop);
}

CINFCityBazaar::~CINFCityBazaar()
{

}

int CINFCityBazaar::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return INF_MSGPROC_NORMAL;
}

int CINFCityBazaar::GetShopItemCount(UID64_t itemUID)
{
	return 0;
}

CItemInfo *	CINFCityBazaar::GetShopItemInfo(UID64_t itemUID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
int	CINFCityBazaar::GetScrollLine()
{
	int ntemp = m_nScrollMaxCount - m_nScrollMaxLine;

	if(ntemp < 0)
	{
		ntemp = 0;
	}
	return ntemp;
}

int	CINFCityBazaar::GetScrollLineNumber(float nLength)
{
	int ntemp = GetScrollLine();
	float fLineNum = (nLength * ntemp) / BAZAAR_SHOP_SCROLL_LINE_LENGTH;

	return (int)fLineNum;
}

float CINFCityBazaar::GetScrollLineInterval(int nScrollLineNum)
{
	int ntemp = GetScrollLine();
	float fLineNum = 0.0f;
	if(ntemp)
		fLineNum = (BAZAAR_SHOP_SCROLL_LINE_LENGTH * nScrollLineNum) / ntemp;

	return fLineNum;
}

void CINFCityBazaar::SetScrollEndLine()
{
	m_nScrollPosition = 0;
	m_nScrollLine = GetScrollLine();
	if(m_nScrollLine)
		m_nScrollPosition = BAZAAR_SHOP_SCROLL_LINE_LENGTH;
}

void CINFCityBazaar::InitScrollLine()
{
	m_nScrollPosition = 0;
	m_nScrollLine = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFCityBazaar::UnderBarDrawText(CD3DHanFont *pHanFont,FLOAT sx,FLOAT sy,DWORD dwColor,TCHAR* strText,DWORD dwFlags)
/// \brief		???????? ???????? ???????? ????
///
/// \author		dgwoo
/// \version	
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaar::UnderBarDrawText(CD3DHanFont *pHanFont,FLOAT sx,FLOAT sy,DWORD dwColor,TCHAR* strText,DWORD dwFlags)
{
	char buftemp[256] = {0,};

	wsprintf(buftemp,"%s_",strText);
	pHanFont->DrawText(sx,sy,dwColor,buftemp,dwColor);
	return ;
}
BOOL CINFCityBazaar::GetPointInType(POINT &pt,int type,int Num)
{
	
	// visit buy
	//--------------------------------------------------------------------------
	if(type == BAZAAR_VISIT_BUY_COUNT)
	{
		if(pt.x > BAZAAR_VISIT_BUY_COUNT_X &&
			pt.x < BAZAAR_VISIT_BUY_COUNT_X +BAZAAR_VISIT_BUY_COUNT_W &&
			pt.y > BAZAAR_VISIT_BUY_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) &&
			pt.y < BAZAAR_VISIT_BUY_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_VISIT_TEXT_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_BTN)
	{
		if(	pt.x >= BAZAAR_SHOP_RIGHT_BTN_X &&
				pt.x <= BAZAAR_SHOP_RIGHT_BTN_X + BAZAAR_SHOP_BTN_W &&
				pt.y >= BAZAAR_SHOP_RIGHT_BTN_Y + (Num * BAZAAR_SHOP_ITEM_H) &&
				pt.y <= BAZAAR_SHOP_RIGHT_BTN_Y + (Num * BAZAAR_SHOP_ITEM_H)+ BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_BTN_VISIT_OUT)
	{
		if(pt.x >= BAZAAR_VISIT_OUT_X &&
			pt.x <= BAZAAR_VISIT_OUT_X + BAZAAR_SHOP_BTN_OUT_W &&
			pt.y >= BAZAAR_VISIT_OUT_Y &&
			pt.y <= BAZAAR_VISIT_OUT_Y + BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	// visit sell
	//--------------------------------------------------------------------------
	else if(type == BAZAAR_ICON)
	{
		if(pt.x >= BAZAAR_SHOP_ICON_X &&
				pt.x <= BAZAAR_SHOP_ICON_X + BAZAAR_SHOP_ICON_WH &&
				pt.y >= BAZAAR_SHOP_ITEM_Y &&
				pt.y <= BAZAAR_SHOP_ITEM_Y + (BAZAAR_SHOP_ITEM_H * SHOP_ITEM_SLOT_NUMBER))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_VISIT_SEL_COUNT)
	{
		if(pt.x > BAZAAR_VISIT_SEL_COUNT_X &&
					pt.x < BAZAAR_VISIT_SEL_COUNT_X +BAZAAR_VISIT_SEL_COUNT_W &&
					pt.y > BAZAAR_VISIT_SEL_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) &&
					pt.y < BAZAAR_VISIT_SEL_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_VISIT_TEXT_H)
		{
			return TRUE;	
		}
		return FALSE;
	}
	// open buy
	//--------------------------------------------------------------------------
	else if(type == BAZAAR_OPEN_1_BUY)
	{
		if( pt.x > BAZAAR_OPEN_1_BUY_X &&
					pt.x < BAZAAR_OPEN_1_BUY_X + BAZAAR_OPEN_1_ICON_W &&
					pt.y > BAZAAR_OPEN_1_Y + (BAZAAR_SHOP_ITEM_H * Num)&&
					pt.y < BAZAAR_OPEN_1_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_3_BUY)
	{
		if(pt.x > BAZAAR_OPEN_3_BUY_X &&
					pt.x < BAZAAR_OPEN_3_BUY_X + BAZAAR_OPEN_1_ICON_W &&
					pt.y > BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H *Num)&&
					pt.y < BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H *Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_2_BUY)
	{
		if(pt.x > BAZAAR_OPEN_2_BUY_X &&
					pt.x < BAZAAR_OPEN_2_BUY_X + BAZAAR_OPEN_1_BUY_W &&
					pt.y > BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H *Num)&&
					pt.y < BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H *Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_4_BUY)
	{
		if(pt.x > BAZAAR_OPEN_4_BUY_X &&
					pt.x < BAZAAR_OPEN_4_BUY_X + BAZAAR_OPEN_1_BUY_W &&
					pt.y > BAZAAR_OPEN_4_Y + (BAZAAR_SHOP_ITEM_H *Num)&&
					pt.y < BAZAAR_OPEN_4_Y + (BAZAAR_SHOP_ITEM_H *Num) + BAZAAR_OPEN_1_H)
	{
			return TRUE;
		}
		return FALSE;
	}
	// open sell
	//--------------------------------------------------------------------------
	else if(type == BAZAAR_OPEN_2_SEL)
	{
		if(pt.x > BAZAAR_OPEN_2_SEL_X &&
					pt.x < BAZAAR_OPEN_2_SEL_X + BAZAAR_OPEN_1_SEL_W &&
					pt.y > BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H * Num)&&
					pt.y < BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_3_SEL)
	{
		if(pt.x > BAZAAR_OPEN_1_SEL_X &&
					pt.x < BAZAAR_OPEN_1_SEL_X + BAZAAR_OPEN_1_SEL_W &&
					pt.y > BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H * Num)&&
					pt.y < BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	//???? ?????? ?????? ??????..
	//--------------------------------------------------------------------------//
	else if(type == BAZAAR_SHOP_WINDOW)
	{
		if(pt.x >= BAZAAR_SHOP_WINDOW_X &&
				pt.x <= BAZAAR_SHOP_WINDOW_X + BAZAAR_SHOP_WINDOW_W &&
				pt.y >= BAZAAR_SHOP_WINDOW_Y &&
				pt.y <= BAZAAR_SHOP_WINDOW_Y + BAZAAR_SHOP_WINDOW_H)
		{
			return TRUE;
		}
		return FALSE;
	}else if(type == BAZAAR_SHOP_TAB)
	{
		if(pt.x >= (BAZAAR_SHOP_TAB_START_X + (Num * BAZAAR_SHOP_TAB_W)) && 
					pt.x <= (BAZAAR_SHOP_TAB_START_X + ((Num + 1) * BAZAAR_SHOP_TAB_W)) &&
					pt.y >= BAZAAR_SHOP_TAB_START_Y && 
					pt.y <= BAZAAR_SHOP_TAB_START_Y + BAZAAR_SHOP_TAB_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_SCROLL)
	{
		if(pt.x >= BAZAAR_SHOP_OPEN_SCROLL_X &&
				pt.x <= BAZAAR_SHOP_OPEN_SCROLL_X + BAZAAR_SHOP_SCROLL_W &&
				pt.y >= BAZAAR_SHOP_SCROLL_Y + Num &&
				pt.y <= BAZAAR_SHOP_SCROLL_Y + Num + BAZAAR_SHOP_SCROLL_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_VISIT_SCROLL)
	{
		if(pt.x >= BAZAAR_SHOP_VISIT_SCROLL_X &&
				pt.x <= BAZAAR_SHOP_VISIT_SCROLL_X + BAZAAR_SHOP_SCROLL_W &&
				pt.y >= BAZAAR_SHOP_SCROLL_Y + Num &&
				pt.y <= BAZAAR_SHOP_SCROLL_Y + Num + BAZAAR_SHOP_SCROLL_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_TAB_WHEEL)
	{
		if(pt.x >= BAZAAR_SHOP_TAB_START_X &&
				pt.x <= BAZAAR_SHOP_TAB_START_X + BAZAAR_SHOP_TAB_BACK_W &&
				pt.y >= BAZAAR_SHOP_TAB_START_Y &&
				pt.y <= BAZAAR_SHOP_TAB_START_Y + BAZAAR_SHOP_TAB_BACK_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_OPEN_START)
	{
		if(pt.x >= BAZAAR_SHOP_OPEN_START_X &&
				pt.x <= BAZAAR_SHOP_OPEN_START_X + BAZAAR_SHOP_BTN_W &&
				pt.y >= BAZAAR_SHOP_OPEN_START_Y  &&
				pt.y <= BAZAAR_SHOP_OPEN_START_Y + BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_OPEN_STOP)
	{
		if(pt.x >= BAZAAR_SHOP_OPEN_STOP_X &&
					pt.x <= BAZAAR_SHOP_OPEN_STOP_X + BAZAAR_SHOP_BTN_W &&
					pt.y >= BAZAAR_SHOP_OPEN_STOP_Y &&
					pt.y <= BAZAAR_SHOP_OPEN_STOP_Y + BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_ITEM)
	{
		if(pt.x >= BAZAAR_SHOP_ITEM_X &&
					pt.x <= BAZAAR_SHOP_ITEM_X + BAZAAR_SHOP_ITEM_W &&
					pt.y >= BAZAAR_SHOP_ITEM_Y + (Num * BAZAAR_SHOP_ITEM_H)&&
					pt.y <= BAZAAR_SHOP_ITEM_Y + ((Num + 1) * BAZAAR_SHOP_ITEM_H))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_NAME)
	{
		if(pt.x >= BAZAAR_OPEN_NAME_X + 38 &&
					pt.x <= BAZAAR_OPEN_NAME_X + 231 &&
					pt.y >= BAZAAR_OPEN_NAME_Y &&
					pt.y <= BAZAAR_OPEN_NAME_Y + 18)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_ITEM_AREA)
	{
		if(pt.x > BAZAAR_SHOP_ITEM_X &&
				pt.x < BAZAAR_SHOP_ITEM_X + BAZAAR_SHOP_ITEM_W &&
				pt.y > BAZAAR_SHOP_ITEM_Y &&
				pt.y < BAZAAR_SHOP_ITEM_Y + BAZAAR_SHOP_ITEM_H * SHOP_ITEM_SLOT_NUMBER)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_MIN)
	{
		if(pt.x > BAZAAR_SHOP_MIN_X &&
				pt.x < BAZAAR_SHOP_MIN_X + BAZAAR_SHOP_MIN_W &&
				pt.y > BAZAAR_SHOP_MIN_Y &&
				pt.y < BAZAAR_SHOP_MIN_Y + BAZAAR_SHOP_MIN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_ACT)
	{
		if(pt.x > BAZAAR_SHOP_MINIBAR_X &&
				pt.x < BAZAAR_SHOP_MINIBAR_X + BAZAAR_SHOP_MINIBAR_W &&
				pt.y > BAZAAR_SHOP_MINIBAR_Y &&
				pt.y < BAZAAR_SHOP_MINIBAR_Y + BAZAAR_SHOP_MINIBAR_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::SetItemInfo(CItemInfo* pSelectItem, int x, int y)
/// \brief		?????? ???? ????????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaar::SetItemInfo(CItemInfo* pSelectItem, int x, int y)
{
	if(m_pCurrentItemInfo != pSelectItem) 
	{
		if(pSelectItem) 
		{
			// 2009-02-03 by bhsohn ???? ?????? ???? ????
			//g_pGameMain->m_pItemInfo->SetItemInfoUser( pSelectItem, x, y );
			g_pGameMain->SetItemInfoUser( pSelectItem, x, y );
			// end 2009-02-03 by bhsohn ???? ?????? ???? ????
		}
		else 
		{
			g_pGameMain->SetItemInfo( 0, 0, 0, 0); 
		}
		m_pCurrentItemInfo = pSelectItem;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::InitVisitData()
/// \brief		
/// \author		// 2007-11-01 by bhsohn ???? ???????? ???? ????
/// \date		2007-11-01 ~ 2007-11-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void	CINFCityBazaar::CloseVisitShop()
{

}

//////////////////////////////////////////////////////////////////////////
// ???? ???? ??????
CINFCityBazaarOpen::CINFCityBazaarOpen(CAtumNode* pParent, CGameData* pGameData, int nBazaarType)
{
	m_pParent			= pParent;	// CGameMain*
	m_pGameData			= pGameData;

	m_byBazaarType		= nBazaarType;
	m_byTabIndex		= 0;

	m_nStartBtnState	= BTN_STATE_NORMAL;
	m_nStopBtnState		= BTN_STATE_NORMAL;
	m_nOutBtnState		= BTN_STATE_NORMAL;
	m_nMinBtnState		= BTN_STATE_NORMAL;

	m_byFocusText		= TEXT_NON;
	m_nScrollPosition	= 0;
	m_nScrollLine		= 0;
	m_nSelectIndex		= -1;

	memset(m_nComboState,0,sizeof(m_nComboState));

	m_nTotal			= 0;

	// ????
	m_nScrollMaxCount	= BAZAARSHOP_ITEMCOUNT;
	m_nScrollMaxLine	= SHOP_ITEM_SLOT_NUMBER;

	m_ClientIndex		= 0;
	m_nComboActive		= 0;
	m_nLogMaxCount		= 0;

	m_byBazaarTypeState	= 1;
	m_bSelectItem		= FALSE;
//	m_bBazaarMinAct		= FALSE;
	m_bBazaarMinAct		= TRUE;

	POINT pt;
	pt.x = pt.y = 0;
	SetSelectItem(NULL, pt);
}

CINFCityBazaarOpen::~CINFCityBazaarOpen()
{

}

HRESULT CINFCityBazaarOpen::InitDeviceObjects()
{
	int i;
	char buf[16] = {0,};
	DataHeader	* pDataHeader;
	
	CheckBtnState();

	m_pBackWindow = new CINFImage;
	wsprintf(buf,"sellback");
	pDataHeader = FindResource(buf);
	m_pBackWindow->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	
	for(i = 0 ; i < 4; i++)
	{
		//???? ????
		m_pDelItemBtn[i] = new CINFImage;
		wsprintf(buf, "canBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pDelItemBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//???? ????
		m_pPutItemBtn[i] = new CINFImage;
		wsprintf(buf, "putBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pPutItemBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//???? ????.
		m_pStartBtn[i] = new CINFImage;
		wsprintf(buf, "startBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pStartBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//???? ????.
		m_pStopBtn[i] = new CINFImage;
		wsprintf(buf, "stopBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pStopBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	
		//??????.
		m_pMinBtn[i] = new CINFImage;
		wsprintf(buf,"c_down0%d",i);
		pDataHeader = FindResource(buf);
		m_pMinBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//??????.
		m_pActBtn[i] = new CINFImage;
		wsprintf(buf,"c_up0%d",i);
		pDataHeader = FindResource(buf);
		m_pActBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		
	}
	//?????? ??.
	m_pMinBar = new CINFImage;
	wsprintf(buf, "selbar");
	pDataHeader = FindResource(buf);
	m_pMinBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);


	//???? .
	m_pShopName = new CINFImage;
	wsprintf(buf, "BackName");
	pDataHeader = FindResource(buf);
	m_pShopName->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	//???? ????.
	m_pBackTotal = new CINFImage;
	wsprintf(buf, "BackTotal");
	pDataHeader = FindResource(buf);
	m_pBackTotal->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	// ?????? ????
	m_pScrollButton = new CINFImage;
	pDataHeader = FindResource("c_scrlb");
	m_pScrollButton->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	

	/*--------------------------------------------------------------------------*/
	// ???? ???? ?????? ???? ??????
	//?? ????
	m_pBackTab[0] = new CINFImage;
	wsprintf(buf, "BackTab_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackTab[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	//?????? ????.
	m_pBackItem = new CINFImage;
	wsprintf(buf, "BackItem_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackItem->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	// ???? ????
	m_pSelectBar = new CINFImage;
	wsprintf(buf, "SelItem_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pSelectBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	if(m_byBazaarType == 1)
	{
		//????
		m_pBackTab[1] = new CINFImage;
		wsprintf(buf, "sellLogTab");
		pDataHeader = FindResource(buf);
		m_pBackTab[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//?????? ????.
		m_pBackList = new CINFImage;
		wsprintf(buf, "BackList_0");
		pDataHeader = FindResource(buf);
		m_pBackList->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}
	else if(m_byBazaarType == 2)
	{
		//????
		m_pBackTab[1] = new CINFImage;
		wsprintf(buf, "buyLogTab");
		pDataHeader = FindResource(buf);
		m_pBackTab[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//?????? ????.
		m_pBackList = new CINFImage;
		wsprintf(buf, "BackList");
		pDataHeader = FindResource(buf);
		m_pBackList->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//comboBox ??????.
		m_pArrowIcon[0] = new CINFImage;
		wsprintf(buf,"mnQdn00");
		pDataHeader = FindResource(buf);
		m_pArrowIcon[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		m_pArrowIcon[1] = new CINFImage;
		wsprintf(buf,"mnQdn01");
		pDataHeader = FindResource(buf);
		m_pArrowIcon[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		// ???? ?????? ???? ???? ???? ?????? ????.
		OnReadyBuyItem();
	}
	/*--------------------------------------------------------------------------*/
	//m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_2_SEL_W,32);
	m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemPrice->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_1_BUY_W,32);
	m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemCount->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemSum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_2_SEL_W,32);
	m_pFontItemSum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemSum->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,70,32);
	//m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_1_SEL_W,32);
	m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,190,32);
	m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontName->InitDeviceObjects(g_pD3dDev);
	//m_pFontTotal = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,107,32);
	m_pFontTotal = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontTotal->InitDeviceObjects(g_pD3dDev);
	//m_pFontLogMsg = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_SHOP_LOG_STRING_LENGTH,32);
	m_pFontLogMsg = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,512,32);
	m_pFontLogMsg->InitDeviceObjects(g_pD3dDev);
	//m_pFontShopType= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_SHOP_LOG_STRING_LENGTH,32);
	m_pFontShopType= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,512,32);
	m_pFontShopType->InitDeviceObjects(g_pD3dDev);

	m_pComboKindEx = new CINFComboBoxEX(this, m_pGameData);
	m_pComboKindEx->CreateImage("Name","SelName","Sm-Scroll");
	m_pComboKindEx->InitDeviceObjects();
	m_pComboNameEx = new CINFComboBoxEX(this, m_pGameData);
	m_pComboNameEx->CreateImage("Name","SelName","Sm-Scroll");
	m_pComboNameEx->InitDeviceObjects();

	return S_OK;
}

HRESULT CINFCityBazaarOpen::RestoreDeviceObjects()
{
	int i;
	m_pBackWindow->RestoreDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->RestoreDeviceObjects();
		m_pPutItemBtn[i]->RestoreDeviceObjects();
		m_pStartBtn[i]->RestoreDeviceObjects();
		m_pStopBtn[i]->RestoreDeviceObjects();

		m_pMinBtn[i]->RestoreDeviceObjects();
		m_pActBtn[i]->RestoreDeviceObjects();
	}
	m_pMinBar->RestoreDeviceObjects();

	for(i = 0; i < 2; i++)
	{
		m_pBackTab[i]->RestoreDeviceObjects();
	}
	
	m_pFontItemPrice->RestoreDeviceObjects();
	m_pFontItemCount->RestoreDeviceObjects();
	m_pFontItemName->RestoreDeviceObjects();
	m_pFontItemSum->RestoreDeviceObjects();
	m_pBackList->RestoreDeviceObjects();
	m_pBackItem->RestoreDeviceObjects();
	m_pShopName->RestoreDeviceObjects();
	m_pBackTotal->RestoreDeviceObjects();
	m_pScrollButton->RestoreDeviceObjects();
	m_pSelectBar->RestoreDeviceObjects();


	m_pFontName->RestoreDeviceObjects();
	m_pFontTotal->RestoreDeviceObjects();
	m_pFontLogMsg->RestoreDeviceObjects();
	m_pFontShopType->RestoreDeviceObjects();

	if(m_byBazaarType == 2)
	{
		for(i = 0; i < 2; i++)
		{
			m_pArrowIcon[i]->RestoreDeviceObjects();
		}
		m_pComboKindEx->RestoreDeviceObject();
		m_pComboNameEx->RestoreDeviceObject();
	}
	
	return S_OK;
}

HRESULT CINFCityBazaarOpen::DeleteDeviceObjects()
{
	int i;
	m_pBackWindow->DeleteDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->DeleteDeviceObjects();
		m_pPutItemBtn[i]->DeleteDeviceObjects();
		m_pStartBtn[i]->DeleteDeviceObjects();
		m_pStopBtn[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pDelItemBtn[i]);
		SAFE_DELETE(m_pPutItemBtn[i]);
		SAFE_DELETE(m_pStartBtn[i]);
		SAFE_DELETE(m_pStopBtn[i]);
	
		m_pMinBtn[i]->DeleteDeviceObjects();
		m_pActBtn[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pMinBtn[i]);
		SAFE_DELETE(m_pActBtn[i]);
	}
	m_pMinBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pMinBar);
	
	for(i = 0; i < 2; i++)
	{
		m_pBackTab[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pBackTab[i]);
	}

	m_pShopName->DeleteDeviceObjects();
	m_pBackTotal->DeleteDeviceObjects();
	m_pBackList->DeleteDeviceObjects();
	m_pBackItem->DeleteDeviceObjects();
	m_pScrollButton->DeleteDeviceObjects();
	m_pSelectBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pShopName);
	SAFE_DELETE(m_pBackTotal);
	SAFE_DELETE(m_pBackList);
	SAFE_DELETE(m_pBackItem);
	SAFE_DELETE(m_pScrollButton);
	SAFE_DELETE(m_pSelectBar);

	m_pFontItemName->DeleteDeviceObjects();
	m_pFontItemPrice->DeleteDeviceObjects();
	m_pFontItemCount->DeleteDeviceObjects();
	m_pFontItemSum->DeleteDeviceObjects();
	m_pFontName->DeleteDeviceObjects();
	m_pFontTotal->DeleteDeviceObjects();
	m_pFontLogMsg->DeleteDeviceObjects();
	m_pFontShopType->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontItemName);
	SAFE_DELETE(m_pFontItemPrice);
	SAFE_DELETE(m_pFontItemCount);
	SAFE_DELETE(m_pFontName);
	SAFE_DELETE(m_pFontTotal);
	SAFE_DELETE(m_pFontLogMsg);
	SAFE_DELETE(m_pFontShopType);

	if(m_byBazaarType == 2)
	{
		for(i = 0; i < 2; i++)
		{
			m_pArrowIcon[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pArrowIcon[i]);
		}
		m_pComboKindEx->DeleteDeviceObject();
		m_pComboNameEx->DeleteDeviceObject();
	}

	InitOpenData();

	if(g_pGameMain)
		g_pGameMain->SetItemInfo( 0, 0, 0, 0); 

	if(g_pCharacterChild)
	{
		g_pCharacterChild->DeleteChatMoveShop();
	}

	return S_OK;
}

HRESULT CINFCityBazaarOpen::InvalidateDeviceObjects()
{
	int i;

	m_pBackWindow->InvalidateDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->InvalidateDeviceObjects();
		m_pPutItemBtn[i]->InvalidateDeviceObjects();
		m_pStartBtn[i]->InvalidateDeviceObjects();
		m_pStopBtn[i]->InvalidateDeviceObjects();
	
		m_pMinBtn[i]->InvalidateDeviceObjects();
		m_pActBtn[i]->InvalidateDeviceObjects();
	}
	m_pMinBar->InvalidateDeviceObjects();
	
	for(i = 0; i < 2; i++)
	{
		m_pBackTab[i]->InvalidateDeviceObjects();
	}

	m_pBackList->InvalidateDeviceObjects();
	m_pBackItem->InvalidateDeviceObjects();
	m_pShopName->InvalidateDeviceObjects();
	m_pBackTotal->InvalidateDeviceObjects();
	m_pScrollButton->InvalidateDeviceObjects();
	m_pSelectBar->InvalidateDeviceObjects();
	
	m_pFontItemName->InvalidateDeviceObjects();
	m_pFontItemPrice->InvalidateDeviceObjects();
	m_pFontItemCount->InvalidateDeviceObjects();
	m_pFontItemSum->InvalidateDeviceObjects();
	m_pFontName->InvalidateDeviceObjects();
	m_pFontTotal->InvalidateDeviceObjects();
	m_pFontLogMsg->InvalidateDeviceObjects();
	m_pFontShopType->InvalidateDeviceObjects();

	if(m_byBazaarType == 2)
	{
		for(i = 0; i < 2; i++)
		{
			m_pArrowIcon[i]->InvalidateDeviceObjects();
		}

		m_pComboKindEx->InitDeviceObjects();
		m_pComboNameEx->InitDeviceObjects();
	}
	
	return S_OK;
}

void CINFCityBazaarOpen::SetDataCombo(int nComboActive)
{
	if(nComboActive == 1)
	{
		if(m_pComboKindEx->m_vecData.size() == 0)
		{
			int i = 0, count = 0;
			while(g_arrItemKindString[i].byItemKind0 != ITEMKIND_UNKNOWN)
			{
				ComboData Data;
				
				if(g_arrItemKindString[i].bIsBazaarItemKind)
				{
					
					wsprintf(Data.DataName,"%s",g_arrItemKindString[i].szItemKindName);
					Data.nData = g_arrItemKindString[i].byItemKind0;
					m_pComboKindEx->m_vecData.push_back(Data);
					count++;
				}
				i++;
			}
			
			sort(m_pComboKindEx->m_vecData.begin(), m_pComboKindEx->m_vecData.end());
			m_pComboKindEx->SetScrollBarInfo(214,5,119,9,30);
			m_pComboKindEx->SetComboInfo(count,8,204,15);
		}
	}
	else if(nComboActive == 2)
	{
		// ???? ???????? ???? ?? ???? ????.
		int nInputItemIndex = m_vecOpenBazaarItem.size() - 1;
		if(nInputItemIndex >= 0)
		{
			if(m_vecOpenBazaarItem[nInputItemIndex].pItemBase)
			{
				SAFE_DELETE(m_vecOpenBazaarItem[nInputItemIndex].pItemBase);
			}
		}

		vectorItemInfoList ItemList;
		g_pDatabase->GetServerItemInfo(&ItemList, m_pComboKindEx->m_vecData[m_pComboKindEx->m_nSelectDataIndex].nData);

		m_pComboNameEx->m_vecData.clear();
		int i = 0, count = 0;
		vectorItemInfoList::iterator itItem = ItemList.begin();
		while(itItem != ItemList.end())
		{
			ComboData Data;
	
			if(COMPARE_BIT_FLAG((*itItem)->ItemAttribute, ITEM_ATTR_BAZAAR_ITEM))
			{
				wsprintf(Data.DataName,"%s", (*itItem)->ItemName);
				Data.nData = (*itItem)->ItemNum;
				m_pComboNameEx->m_vecData.push_back(Data);
				count++;
			}
			
			itItem++;
		}
		
		sort(m_pComboNameEx->m_vecData.begin(), m_pComboNameEx->m_vecData.end());
		m_pComboNameEx->SetScrollBarInfo(214,5,119,9,30);
		m_pComboNameEx->SetComboInfo(count,8,204,15);
	}		
}

void CINFCityBazaarOpen::Render()
{
	// 2006-08-29 by dgwoo ???????? ??????&???????????? .
	if(!m_bBazaarMinAct)
	{//??????????.
		Render_Disable();
		return;
	}

	// ?????? ????????
	g_pGameMain->m_pInven->RenderOnCityBase();

	//????
	m_pBackWindow->Move(BAZAAR_SHOP_WINDOW_X, BAZAAR_SHOP_WINDOW_Y);
	m_pBackWindow->Render();

	if(m_byTabIndex == 1)
	{
		// ???? ??
		Render_Log();
	}
	else 
	{
		// ???? ??
		/*--------------------------------------------------------------------------*/
		// ???? ??????
		Render_Common();

		/*--------------------------------------------------------------------------*/
		// ?????? ??????
		if(m_byBazaarType == 1)
		{
			Render_Sell();
		}
		else if(m_byBazaarType == 2)
		{
			Render_Buy();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFCityBazaarOpen::RenderDisabled()
/// \brief		?????????? ???????? ?????????????? ??????.
///
/// \author		dgwoo
/// \version	
/// \date		2006-08-29 ~ 2006-08-29
/// \warning	
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Render_Disable()
{
	char temp[64] = {0,};
	m_pMinBar->Move(BAZAAR_SHOP_MINIBAR_X,BAZAAR_SHOP_MINIBAR_Y);
	m_pMinBar->Render();
	if(m_byBazaarType == 1)
		wsprintf(temp,STRMSG_C_060829_0100);
	else
		wsprintf(temp,STRMSG_C_060829_0101);
	m_pFontShopType->DrawText(BAZAAR_SHOP_MINIBAR_X + 5,BAZAAR_SHOP_MINIBAR_Y + 2,GUI_FONT_COLOR_W,temp,0L);
	
	m_pActBtn[m_nMinBtnState]->Move(BAZAAR_SHOP_ACT_X,BAZAAR_SHOP_ACT_Y);
	m_pActBtn[m_nMinBtnState]->Render();
}

void CINFCityBazaarOpen::Render_Common()
{
	m_pBackTab[0]->Move(BAZAAR_SHOP_TAB_START_X, BAZAAR_SHOP_TAB_START_Y);
	m_pBackTab[0]->Render();

	m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y);
	m_pBackList->Render();

	//?????? ????.
	m_pMinBtn[m_nMinBtnState]->Move(BAZAAR_SHOP_MIN_X,BAZAAR_SHOP_MIN_Y);
	m_pMinBtn[m_nMinBtnState]->Render();
	

	//???? ??????
	m_pBackTotal->Move(BAZAAR_SHOP_OPEN_TOTAL_PRICE_X, BAZAAR_SHOP_OPEN_TOTAL_PRICE_Y);
	m_pBackTotal->Render();
	
	// ???? ????.
	char temp1[64];
	char temp2[64];
	wsprintf( temp1, "%d", m_nTotal );
	MakeCurrencySeparator( temp2, temp1, 3, ',' );
	//?????? ?????? ????..
	SIZE texSize = m_pFontTotal->GetStringSize(temp2);
	m_pFontTotal->DrawText(BAZAAR_SHOP_OPEN_TOTAL_PRICE_X+BAZAAR_SHOP_OPEN_TOTAL_PRICE_W-texSize.cx,BAZAAR_SHOP_OPEN_TOTAL_PRICE_Y, GUI_FONT_COLOR_W,temp2, 0L);

	//???? 
	m_pShopName->Move(BAZAAR_OPEN_NAME_X, BAZAAR_OPEN_NAME_Y);
	m_pShopName->Render();
	if(m_byFocusText == TEXT_NAME)
		UnderBarDrawText(m_pFontName,BAZAAR_OPEN_NAME_X+40, BAZAAR_OPEN_NAME_Y,GUI_FONT_COLOR_W,m_strInputMessage,0L);
	else
	m_pFontName->DrawText(BAZAAR_OPEN_NAME_X+40, BAZAAR_OPEN_NAME_Y,GUI_FONT_COLOR_W,m_strInputMessage,0L);

	//???? ????.
	m_pStartBtn[m_nStartBtnState]->Move(BAZAAR_SHOP_OPEN_START_X, BAZAAR_SHOP_OPEN_START_Y);
	m_pStartBtn[m_nStartBtnState]->Render();

	m_pStopBtn[m_nStopBtnState]->Move(BAZAAR_SHOP_OPEN_STOP_X, BAZAAR_SHOP_OPEN_STOP_Y);
	m_pStopBtn[m_nStopBtnState]->Render();

	// ??????
	m_pScrollButton->Move(BAZAAR_SHOP_OPEN_SCROLL_X, BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
	m_pScrollButton->Render();
}

void CINFCityBazaarOpen::Render_Sell()
{
	/*--------------------------------------------------------------------------*/
	//?????? ???? ???? ?? ????.	
	int i = 0;
	int nItemCount = m_vecOpenBazaarItem.size();
	if(nItemCount < m_nScrollLine)
		return;
	
	vector<OPEN_BAZAAR_ITEM>::iterator ite = m_vecOpenBazaarItem.begin();
	while(ite != m_vecOpenBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}

			// ????
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}

			// ??????
			char buf[64] = {0,};
			char buf1[64] = {0,};
			//???????? ?????? ???? ????..


			// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

			//wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
			if( !ite->pItemBase->ShapeItemNum )
				wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemBase->ShapeItemNum );
				if( pShapeItem )
					wsprintf( buf, "%08d", pShapeItem->SourceIndex );
				else
					wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
			}

			// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

			g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
			g_pGameMain->m_pIcon->Render();


			// 2010. 02. 11 by ckPark ?????? ??????????
			if( (*ite).pItemBase->ItemInfo->InvokingDestParamID
				|| (*ite).pItemBase->ItemInfo->InvokingDestParamIDByUse )
			{
				char buf[128];

				if( GetString_CoolTime( (*ite).pItemBase, buf ) )
				{
					int nFontPosX = BAZAAR_SHOP_ICON_X;
					int nFontPosY = BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H) + 6;

					m_pFontItemName->DrawText( nFontPosX, nFontPosY, GUI_FONT_COLOR, buf, 0L );
				}
			}
			// end 2010. 02. 11 by ckPark ?????? ??????????


			// ?????? ????
			vector<string> vecChatMessage;
			vecChatMessage.clear();
			STRING_CULL(ite->pItemBase->ItemInfo->ItemName, BAZAAR_OPEN_1_SEL_W, &vecChatMessage, m_pFontItemName);
			wsprintf(buf1,"%s",(char*)vecChatMessage[0].c_str());
			m_pFontItemName->DrawText(BAZAAR_OPEN_1_SEL_X,BAZAAR_OPEN_1_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemCount);
			SIZE size = m_pFontItemCount->GetStringSize(buf1);
			if(size.cx > BAZAAR_OPEN_1_SEL_W)
				size.cx = BAZAAR_OPEN_1_SEL_W;
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemName,BAZAAR_OPEN_1_SEL_X,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemName->DrawText(BAZAAR_OPEN_1_SEL_X+(BAZAAR_OPEN_1_SEL_W-size.cx)/2,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemPrice);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_SEL_W)
				size.cx = BAZAAR_OPEN_2_SEL_W;
			if(m_byFocusText == TEXT_PRICE && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_2_SEL_X,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_2_SEL_X+BAZAAR_OPEN_2_SEL_W-size.cx,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			wsprintf( buf1, "%d", ite->nItemTotal);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemSum->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_SEL_W)
				size.cx = BAZAAR_OPEN_2_SEL_W;
			m_pFontItemSum->DrawText(BAZAAR_OPEN_4_SEL_X+BAZAAR_OPEN_2_SEL_W-size.cx,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);


			

			//???? ????.
			if(ite->bRegister)
			{
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
			else
			{
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
		}

		ite++;
		i++;
	}
}

void CINFCityBazaarOpen::Render_Buy()
{
	/*--------------------------------------------------------------------------*/
	//?????? ???? ???? ?? ????.	
	int i = 0;
	SIZE size;
	char buf[64] = {0,};
	char buf1[64] = {0,};
	int nItemCount = m_vecOpenBazaarItem.size();
	if(nItemCount < m_nScrollLine)
		return;
	
	vector<OPEN_BAZAAR_ITEM>::iterator ite = m_vecOpenBazaarItem.begin();
	while(ite != m_vecOpenBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}

			// ????
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();

			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}

			//?????????? ???? ???? ?????? ??????
			if(m_nComboState[nLineCount][0] == COMBO_UNDER)
			{
				m_pArrowIcon[0]->Move(BAZAAR_OPEN_1_ICON_X,BAZAAR_OPEN_1_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[0]->Render();
			}
			else if(m_nComboState[nLineCount][0] == COMBO_CLICK)
			{
				m_pArrowIcon[1]->Move(BAZAAR_OPEN_1_ICON_X,BAZAAR_OPEN_1_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[1]->Render();
			}
			if(m_nComboState[nLineCount][1] == COMBO_UNDER)
			{
				m_pArrowIcon[0]->Move(BAZAAR_OPEN_2_ICON_X,BAZAAR_OPEN_2_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[0]->Render();
			}
			else if(m_nComboState[nLineCount][1] == COMBO_CLICK)
			{
				m_pArrowIcon[1]->Move(BAZAAR_OPEN_2_ICON_X,BAZAAR_OPEN_2_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[1]->Render();
			}

			if(ite->pItemBase)
			{
				// ??????

				// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

				//wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
				if( !ite->pItemBase->ShapeItemNum )
					wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
				else
				{
					ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemBase->ShapeItemNum );
					if( pShapeItem )
						wsprintf( buf, "%08d", pShapeItem->SourceIndex );
					else
						wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
				}

				// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????


				g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
				g_pGameMain->m_pIcon->Render();

				vector<string> vecChatMessage;
				vecChatMessage.clear();
				wsprintf( buf1, "%s", CAtumSJ::GetItemKindName(ite->pItemBase->ItemInfo->Kind));
				STRING_CULL(buf1, BAZAAR_OPEN_1_BUY_W, &vecChatMessage, m_pFontItemCount);
				size = m_pFontItemCount->GetStringSize((char*)vecChatMessage[0].c_str());
				m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,(char*)vecChatMessage[0].c_str(),0L);
				
				vecChatMessage.clear();
				STRING_CULL(ite->pItemBase->ItemInfo->ItemName, BAZAAR_OPEN_1_BUY_W, &vecChatMessage, m_pFontItemCount);
				wsprintf(buf1,"%s",(char*)vecChatMessage[0].c_str());
				size = m_pFontItemCount->GetStringSize(buf1);
				m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			}

			wsprintf( buf1, "%d", ite->nItemCount);
			size = m_pFontItemPrice->GetStringSize(buf1);
			if(size.cx > BAZAAR_OPEN_2_BUY_W)
				size.cx = BAZAAR_OPEN_2_BUY_W;
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_2_BUY_X,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_2_BUY_X+(BAZAAR_OPEN_2_BUY_W-size.cx)/2,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemPrice);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_BUY_W)
				size.cx = BAZAAR_OPEN_2_BUY_W;
			if(m_byFocusText == TEXT_PRICE && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_4_BUY_X,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_4_BUY_X+BAZAAR_OPEN_2_BUY_W-size.cx,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			//???? ????.
			if(ite->bRegister)
			{
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
			else
			{
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
		}

		ite++;
		i++;
	}

	// ????
	int nBuyItemIndex = nItemCount - 1;
	int nRenderIndex = nBuyItemIndex - m_nScrollLine;
	if(nRenderIndex >= 0 &&
		nRenderIndex < SHOP_ITEM_SLOT_NUMBER)
	{
		if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL &&
			m_pComboKindEx->m_nSelectDataIndex != -1)
		{
			vector<string> vecChatMessage;
			vecChatMessage.clear();
			wsprintf( buf1, "%s", CAtumSJ::GetItemKindName(m_pComboKindEx->m_vecData[m_pComboKindEx->m_nSelectDataIndex].nData));
			STRING_CULL(buf1, BAZAAR_OPEN_1_BUY_W, &vecChatMessage, m_pFontItemCount);
			size = m_pFontItemCount->GetStringSize((char*)vecChatMessage[0].c_str());
			m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,(char*)vecChatMessage[0].c_str(),0L);
		}
		else if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL &&
				m_pComboKindEx->m_nSelectDataIndex == -1)
		{
			m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,STRMSG_C_060801_0100,0L);
		}
		if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL)
		{
			m_pFontItemCount->DrawText(BAZAAR_OPEN_3_BUY_X,BAZAAR_OPEN_3_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,STRMSG_C_060801_0101,0L);
		}
	}

	//???? ?????? ????????.
	if(m_nComboActive== 1)
	{
		m_pComboKindEx->ComboRender();
	}
	else if(m_nComboActive == 2)
	{
		m_pComboNameEx->ComboRender();
	}
}

void CINFCityBazaarOpen::Render_Log()
{
	m_pBackTab[1]->Move(BAZAAR_SHOP_TAB_START_X, BAZAAR_SHOP_TAB_START_Y);
	m_pBackTab[1]->Render();

	// ??????
	m_pScrollButton->Move(BAZAAR_SHOP_OPEN_SCROLL_X, BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
	m_pScrollButton->Render();


	// ?????? ????
	int j = 0;
	int nMaxLineCount = 0;
	int nRenderIndex = m_nScrollLine;
	int nRenderedLineCounts	= 0;
	int nMaxRenderLineCounts = BAZAAR_SHOP_LOG_LINE_COUNT;

	if(0 >= m_LogChat.m_nStoredLineCounts ||
		nRenderIndex >= m_LogChat.m_nStoredLineCounts)
		return;

	int pFontTexWidth = m_pFontLogMsg->GetStringSize(m_LogChat.GetChatLine(nRenderIndex)).cx;

	for(j = 0; j < BAZAAR_SHOP_LOG_LINE_COUNT; j++)
	{
		m_pFontLogMsg->DrawText(BAZAAR_SHOP_LOG_X
			, BAZAAR_SHOP_LOG_Y + (CHAT_FONT_LINE_HEIGHT * nRenderedLineCounts)
			, m_LogChat.GetColorType(nRenderIndex)
			, m_LogChat.GetChatLine(nRenderIndex)
			, 0L);

		nRenderedLineCounts++;
		nRenderIndex++;

		if(m_LogChat.m_nStoredLineCounts <= nRenderIndex ||
			nMaxRenderLineCounts <= nRenderedLineCounts)
		{
			break;
		}						

	}
}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFCityBazaarOpen::Render_Combo()
/// \brief		???? ?????? ????
///
/// \author		dgwoo
/// \version	
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///////////////////////////////////////////////////////////////////////////////


void CINFCityBazaarOpen::Tick()
{

}

int CINFCityBazaarOpen::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nResultProc = INF_MSGPROC_NORMAL;
	int i;
	// 2006-08-29 by dgwoo ?????????? ???? ???????? ??????.
	if(!m_bBazaarMinAct && m_byTabIndex == 0)
	{//??????????.
		if(INF_MSGPROC_BREAK == WndProc_Disable(uMsg, wParam,  lParam))
		{
			return INF_MSGPROC_BREAK;
		}
		return INF_MSGPROC_NORMAL;
	}
	//???? ?????? ?????? ???????? ?????????? ???? ?????? ?????? ????????.
	if(m_byTabIndex == 0 && m_nComboActive != 0)
	{
		if(m_nComboActive == 1)
		{
			if(INF_MSGPROC_BREAK == m_pComboKindEx->WndProc(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		else if(m_nComboActive == 2)
		{
			if(INF_MSGPROC_BREAK == m_pComboNameEx->WndProc(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
	}

	/*--------------------------------------------------------------------------*/
	// ???? ??????
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			m_bScrollLock = FALSE;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(GetPointInType(pt,BAZAAR_SHOP_WINDOW))
			{
				g_pInterface->SetWindowOrder(WNDBazaarShop);
			}
			
			// ??
			int nOldTab = m_byTabIndex;
			for(i = 0; i < 2; i++)
			{
				if(GetPointInType(pt,BAZAAR_SHOP_TAB,i))
				{
					m_byTabIndex = i;
					if(m_byTabIndex == 0)
					{
						// ?????? ???? ????
						m_nScrollMaxCount = BAZAARSHOP_ITEMCOUNT;
						m_nScrollMaxLine  = SHOP_ITEM_SLOT_NUMBER;
						InitScrollLine();
					}
					else if(m_byTabIndex == 1)
					{
						m_nScrollMaxCount = m_LogChat.m_nStoredLineCounts;
						m_nScrollMaxLine  = BAZAAR_SHOP_LOG_LINE_COUNT;
						SetScrollEndLine();
					}

					return INF_MSGPROC_BREAK;
				}
			}

			// ??????
			if(GetPointInType(pt,BAZAAR_SHOP_SCROLL,m_nScrollPosition))
			{
				m_nScrollBtn = pt.y - (BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
				m_bScrollLock = TRUE;
				return INF_MSGPROC_BREAK;
			}			

		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// ??????
			if(m_bScrollLock &&
				pt.x >= BAZAAR_SHOP_OPEN_SCROLL_X - 5 && 
				pt.x <= BAZAAR_SHOP_OPEN_SCROLL_X + BAZAAR_SHOP_SCROLL_W + 5)
			{
				int nScrollBtnY = pt.y - m_nScrollBtn;
				if(nScrollBtnY >= BAZAAR_SHOP_SCROLL_Y &&
					nScrollBtnY <= BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					m_nScrollPosition = nScrollBtnY - BAZAAR_SHOP_SCROLL_Y;
					m_nScrollLine = GetScrollLineNumber(m_nScrollPosition);
				}
				else if(nScrollBtnY < BAZAAR_SHOP_SCROLL_Y)
				{
					InitScrollLine();
				}
				else if(nScrollBtnY > BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					SetScrollEndLine();
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

			if(GetPointInType(pt,BAZAAR_SHOP_ITEM_AREA))
			{
				if((int)wParam<0)
				{
					m_nScrollLine++;
					if(m_nScrollLine > GetScrollLine())
					{
						SetScrollEndLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}
				else
				{
					m_nScrollLine--;
					if(m_nScrollLine < 0)
					{
						InitScrollLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}

				return INF_MSGPROC_BREAK;
			}
			
		}
	}
	/*--------------------------------------------------------------------------*/
	// ????, ???? ?? ??????
	if(m_byTabIndex == 0)
	{
		if(WndProc_Common(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;

		/*--------------------------------------------------------------------------*/
		// ?? ??????
		if(m_byBazaarType == 1)
		{
			nResultProc = WndProc_Sell(uMsg, wParam, lParam);
		}
		else if(m_byBazaarType == 2)
		{
			nResultProc = WndProc_Buy(uMsg, wParam, lParam);
		}
	}
	
	return nResultProc;
}

int CINFCityBazaarOpen::WndProc_Disable(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_LBUTTONUP:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				
				if(GetPointInType(pt,BAZAAR_SHOP_ACT))
				{
					m_nMinBtnState = BTN_STATE_NORMAL;
					m_bBazaarMinAct = TRUE;
					// 2008-08-22 by bhsohn EP3 ???????? ????
					g_pGameMain->m_pInven->ShowAllInven(TRUE); // ???????????? ???? ????????
				}

			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				if(GetPointInType(pt,BAZAAR_SHOP_ACT))
				{
					m_nMinBtnState = BTN_STATE_CLICK;
				}

			}
			break;
		case WM_MOUSEMOVE:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);

				if(GetPointInType(pt,BAZAAR_SHOP_ACT))
				{
					if(m_nMinBtnState != BTN_STATE_CLICK)
						m_nMinBtnState = BTN_STATE_OVER;
				}
				else
				{
					m_nMinBtnState = BTN_STATE_NORMAL;
				}
			}
			break;
			
	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityBazaarOpen::WndProc_Common(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;

	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_nStartBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_START))
			{
				m_nStartBtnState = BTN_STATE_NORMAL;
				OnButtonClicked(OPEN_START);
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_STOP))
			{
				m_nStopBtnState = BTN_STATE_NORMAL;
				OnButtonClicked(OPEN_END);
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_MIN))
			{//?????? ?????? ????????.
				m_nMinBtnState = BTN_STATE_NORMAL;
				m_bBazaarMinAct = FALSE;

				// 2008-08-22 by bhsohn EP3 ???????? ????
				g_pGameMain->m_pInven->ShowAllInven(FALSE);

				return INF_MSGPROC_BREAK;
			}
	
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		
			m_bLButtonDown = TRUE;
			m_byFocusText = TEXT_NON;
			g_pD3dApp->m_bChatMode = FALSE;			

			// 2009-02-26 by bhsohn Japan IME
			int nOldSelectIndex = m_nSelectIndex;
			// end 2009-02-26 by bhsohn Japan IME

			if(m_nStartBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_START))
			{
				m_nStartBtnState = BTN_STATE_CLICK;
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_STOP))
			{
				m_nStopBtnState = BTN_STATE_CLICK;
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_MIN))
			{
				m_nMinBtnState = BTN_STATE_CLICK;
			}
		
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				//???????? ?????? ?????? ??????????.
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_CLICK;
				}

				// ????
				if(!g_pGameMain->m_stSelectItem.pSelectItem && 
					GetPointInType(pt,BAZAAR_SHOP_ITEM,i))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						m_nSelectIndex = nItemIndex;
						break;
					}
					else
					{
						m_nSelectIndex = -1;
					}
				}
				else
				{
					m_nSelectIndex = -1;
				}
			}

			// ???? ???? ????(????)
			if(m_bBazaarShopStart == FALSE &&
				GetPointInType(pt,BAZAAR_OPEN_NAME))
			{
				if(m_byFocusText != TEXT_NAME)
				{
				//	memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
				}
				m_byFocusText = TEXT_NAME;
				g_pD3dApp->m_bChatMode = TRUE;
				
				// 2007.04.24 by bhsohn China IME Working
//#ifdef LANGUAGE_CHINA	
				// 2009-01-12 by bhsohn Japan Working				
#ifdef IS_USE_ONOFF_IME
				g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
				// 2009-02-26 by bhsohn Japan IME
				if(nOldSelectIndex != m_nSelectIndex)
				{					
					g_pD3dApp->CleanIMEControl();					
				}
				// end 2009-02-26 by bhsohn Japan IME
#endif
				
				return INF_MSGPROC_BREAK;
			}
			else
			{
				//???? ?????? ???????????? Name?? ???????? ????.
				if(//!(m_nStartBtnState != BTN_STATE_DEACTIVE &&
					m_bBazaarShopStart  ||
					GetPointInType(pt,BAZAAR_SHOP_OPEN_START))
				{
					//memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
					//g_pD3dApp->CleanText();
				}
				else
				{
					memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
					g_pD3dApp->CleanText();
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

			if(m_nStartBtnState != BTN_STATE_DEACTIVE)
			{
				if(GetPointInType(pt,BAZAAR_SHOP_OPEN_START))//BAZAAR_SHOP_OPEN_START
				{
					if(m_nStartBtnState != BTN_STATE_CLICK)
						m_nStartBtnState = BTN_STATE_OVER;
				}
				else
				{
					m_nStartBtnState = BTN_STATE_NORMAL;
				}
		
				if(GetPointInType(pt,BAZAAR_SHOP_OPEN_STOP))//BAZAAR_SHOP_OPEN_STOP
				{
					if(m_nStopBtnState != BTN_STATE_CLICK)
						m_nStopBtnState = BTN_STATE_OVER;
				}
				else
				{
					m_nStopBtnState = BTN_STATE_NORMAL;
				}
				
			}
			if(GetPointInType(pt,BAZAAR_SHOP_MIN))
			{
				if(m_nMinBtnState != BTN_STATE_CLICK)
					m_nMinBtnState = BTN_STATE_OVER;
			}
			else
			{
				m_nMinBtnState = BTN_STATE_NORMAL;
			}

			//???????? ?????? ?????? ??????????.
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE)
				{
					if(GetPointInType(pt,BAZAAR_BTN,i))//BAZAAR_BTN
					{
						if(m_nPutDelState[i] != BTN_STATE_CLICK)
							m_nPutDelState[i] = BTN_STATE_OVER;
					}
					else
					{
						m_nPutDelState[i] = BTN_STATE_NORMAL;
					}
				}
			}

			// ?????? ????
			if(!g_pGameMain->m_stSelectItem.pSelectItem)
			{
				SetItemInfo(NULL, 0 ,0);
				
				if(GetPointInType(pt,BAZAAR_ICON))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						SetItemInfo((CItemInfo *)(m_vecOpenBazaarItem[nItemIndex].pItemBase), pt.x, pt.y);
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
		}
		break;
		case WM_IME_STARTCOMPOSITION:
		case WM_IME_COMPOSITION:
		case WM_INPUTLANGCHANGE:	
		case WM_IME_ENDCOMPOSITION:
		case WM_IME_SETCONTEXT:	
		case WM_CHAR:
		{
			if( m_byFocusText == TEXT_NAME && g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				int bFlag = FALSE;
				if(INF_MSGPROC_BREAK == g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam))
					bFlag = TRUE;

				//////////////////////////////////////////////////////////////////////////
				char text[256];
				char stringtext[512];
				ZERO_MEMORY(text);
				ZERO_MEMORY(stringtext);

				
				// 2007-11-06 by bhsohn ?????? ????????????  ?????? ?????? ???? ????
				//int strlenInput = g_input.GetInput(text, sizeof(text));
				int nLanguageConversion = g_pD3dApp->m_inputkey.GetInputLanguage();					
				int strlenInput = g_input.GetInput(text, sizeof(text), nLanguageConversion);

				strcpy(stringtext, text);
				ZERO_MEMORY(text);
				int strlenComp = g_input.GetComp(text, sizeof(text));
				strcat(stringtext, text);
				
				if( strlenInput+strlenComp >= SIZE_MAX_BAZAAR_NAME )
				{
					keybd_event(VK_BACK, 0, KEYEVENTF_EXTENDEDKEY, 0);
				}	
				else if(strlen(stringtext) > 0)
				{
						memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
					strncpy(m_strInputMessage,stringtext,strlen(stringtext));
				}
				else if(strlen(m_strInputMessage))
				{
					memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
				}

				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_INPUT_CHAT, g_pShuttleChild->m_vPos, FALSE);
				if(TRUE == bFlag)
					return INF_MSGPROC_BREAK;

			}
			else if(!g_pD3dApp->m_bChatMode)
			{
				// 2009-01-30 by bhsohn ???? ???? ???? ???? ?????? ????
				//g_pD3dApp->CleanText();
			}
		}
		break;
		// 2007-06-11 by bhsohn China IME Working
	case WM_KEYDOWN:
		{
			#ifdef LANGUAGE_CHINA
			if( m_byFocusText == TEXT_NAME && g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				return g_pD3dApp->m_inputkey.OnIMEKeyDown(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam);
			}
			#endif			
		}
		break;
	}

	return INF_MSGPROC_NORMAL;
}

int CINFCityBazaarOpen::WndProc_Sell(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_BAZAAR_POS)
			{
				m_bSelectItem = TRUE;
			}

		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		
			m_bLButtonDown = FALSE;
			m_byFocusText = TEXT_NON;

			if(g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_BAZAAR_POS)
			{
				m_bSelectItem = TRUE;
			}

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				// ?????? ???? ????
				if(m_bBazaarShopStart == FALSE &&
					m_nSelectIndex == m_nScrollLine + i &&
					!m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
				{
					if(GetPointInType(pt,BAZAAR_OPEN_2_SEL,i))
					{
						m_byFocusText = TEXT_PRICE;
						g_pD3dApp->m_bChatMode = TRUE;
						// 2007.04.24 by bhsohn China IME Working
						// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
						g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_3_SEL,i))//BAZAAR_OPEN_3_SEL
					{
						// ???? ?????? ????
						if(IS_COUNTABLE_ITEM(m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->Kind))
						{
							m_byFocusText = TEXT_COUNT;
							g_pD3dApp->m_bChatMode = TRUE;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = 0;
							// 2007.04.24 by bhsohn China IME Working
							// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
							g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
						}
						break;
					}
				}
				else 
				{
				}

				// ?????? ????
				if(!g_pGameMain->m_stSelectItem.pSelectItem && m_bSelectItem == FALSE)
				{
					if(pt.x >= BAZAAR_SHOP_ICON_X &&
						pt.x <= BAZAAR_SHOP_ICON_X + BAZAAR_SHOP_ICON_WH &&
						pt.y >= BAZAAR_SHOP_ITEM_Y &&
						pt.y <= BAZAAR_SHOP_ITEM_Y + BAZAAR_SHOP_ITEM_H + (i * BAZAAR_SHOP_ITEM_H))
					{
						int nItemIndex = GetItemIndexByPos(pt.y);
						if(nItemIndex != -1 && m_vecOpenBazaarItem[nItemIndex].bRegister == FALSE)
						{
							POINT ptIcon;
							ptIcon.x = pt.x - BAZAAR_SHOP_ICON_X + 1;
							ptIcon.y = pt.y - (BAZAAR_SHOP_ICON_Y + (i * BAZAAR_SHOP_ITEM_H)) + 1;
							SetSelectItem(m_vecOpenBazaarItem[nItemIndex].pItemBase, ptIcon);
							SetItemInfo(NULL, 0 ,0);
							break;
						}
					}
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

			if(m_bBazaarShopStart == FALSE &&
				GetPointInType(pt,BAZAAR_SHOP_ITEM_AREA)&&	//BAZAAR_SHOP_ITEM_AREA
				g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_INVEN_POS)
			{
				OnSellItem((CItemInfo *)g_pGameMain->m_stSelectItem.pSelectItem->pItem);
				
				// 2008-08-22 by bhsohn EP3 ???????? ????
				if(g_pGameMain && g_pGameMain->m_pInven)
				{
					// ??????
					g_pGameMain->SetToolTip(NULL, 0, 0);
					g_pGameMain->m_pInven->SetItemInfo(NULL, 0, 0);						
					g_pGameMain->m_pInven->SetSelectItem(NULL);
				}					
				// end 2008-08-22 by bhsohn EP3 ???????? ????
			}
			
			//???????? ???? ????
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))//BAZAAR_BTN
				{
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					m_nPutDelState[i] = BTN_STATE_NORMAL;
					// ?????? ???? ?????? ????
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						if(m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
						{
							// ?????? ???? ????
							OnButtonClicked(OPEN_CANCEL);
							return INF_MSGPROC_BREAK;
						}
						else
						{
							// ?????? ????
							OnButtonClicked(OPEN_REGISTER);
							return INF_MSGPROC_BREAK;
						}
					}
				}
			}

			// ???? ???? ?????? ??????
			if(m_bSelectItem &&
				g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_BAZAAR_POS)
			{
				if(pt.x >= CITY_BASE_NPC_BOX_START_X &&
					pt.x <= BAZAAR_SHOP_WINDOW_X &&
					pt.y >= BAZAAR_SHOP_WINDOW_Y &&
					pt.y <= BAZAAR_SHOP_WINDOW_Y + BAZAAR_SHOP_WINDOW_H)
				{
					OnSellDelItem(g_pGameMain->m_stSelectItem.pSelectItem->pItem->UniqueNumber);
				}

				POINT ptIcon;
				ptIcon.x = 0;
				ptIcon.y = 0;
				SetSelectItem(NULL, ptIcon);
				m_bSelectItem = FALSE;
			}
		}
		break;
		// 2009-01-30 by bhsohn ???? ???? ???? ???? ????
//	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nTotal;
// 				if(m_byFocusText == TEXT_PRICE)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nPrice;
// 							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 					
// 							nPrice *= 10;
// 							nPrice += code - '0';
// 							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount * nPrice;
// 							if(nPrice > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								nPrice = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 				else if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nCount;
// 							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					
// 							nCount *= 10;
// 							nCount += code - '0';
// 							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * nCount;
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "???????? ?????????????? ??????????????.(???????????? 20????)"
// 								nCount = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
// 							CheckSellItemCount();				// ?????? ???? ????
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 			}
// 		}
//		break;
	case WM_KEYDOWN:
		{
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;
				INT64 nTotal;
				if(m_byFocusText == TEXT_PRICE)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nPrice;
							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							
							nPrice *= 10;
							nPrice += nNumber;
							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount * nPrice;
							if(nPrice > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								nPrice = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
				else if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nCount;
							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
							
							nCount *= 10;
							nCount += nNumber;
							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * nCount;
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "???????? ?????????????? ??????????????.(???????????? 20????)"
								nCount = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
							CheckSellItemCount();				// ?????? ???? ????
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
			}
		}
		break;
		// end 2009-01-30 by bhsohn ???? ???? ???? ???? ???? ????
	}
	return INF_MSGPROC_NORMAL;
}

int CINFCityBazaarOpen::WndProc_Buy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			memset(m_nComboState,0,sizeof(m_nComboState));

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
			
				//?????? ?????????? ?????????? ?????????? ????.
				if( GetPointInType(pt,BAZAAR_OPEN_1_BUY,i))
				
				{
					m_nComboState[i][0] = COMBO_UNDER;
				}
				else if(GetPointInType(pt,BAZAAR_OPEN_3_BUY,i))
				{
					//m_byFocusText = TEXT_COUNT;
					m_nComboState[i][1] = COMBO_UNDER;
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
			memset(m_nComboState,0,sizeof(m_nComboState));
			m_bLButtonDown = FALSE;
			//???? ?????? ???????? ????????.
			RenderRect rt;
			if(m_nComboActive == 1)
			{
				rt = m_pComboKindEx->GetComboRect();
				if(!PointInRect(pt,rt))
					m_nComboActive = 0;
			}
			else if(m_nComboActive == 2)
			{
				rt = m_pComboNameEx->GetComboRect();
				if(!PointInRect(pt,rt))
					m_nComboActive = 0;
			}
		
		
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_bBazaarShopStart == FALSE &&
					m_nSelectIndex == m_nScrollLine + i &&
					!m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
				{
					//?????? ?????????? ?????????? ?????????? ????.
					if(GetPointInType(pt,BAZAAR_OPEN_1_BUY,i))
					{
						m_nComboState[i][0] = COMBO_CLICK;
						if(!m_nComboActive)
						{
							m_nComboActive = 1;
							m_pComboKindEx->m_nSelectDataIndex = -1;
							SetDataCombo(m_nComboActive);
							m_pComboKindEx->SetComboPt(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y + (BAZAAR_SHOP_ITEM_H *i) + BAZAAR_OPEN_1_H);
						}
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_2_BUY,i))
					{
						// ???? ?????? ????
						if(	m_vecOpenBazaarItem[m_nSelectIndex].pItemBase)
						{
							int nKind =  m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->Kind;
							if(IS_COUNTABLE_ITEM(m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->Kind))
							{
								m_byFocusText = TEXT_COUNT;
								g_pD3dApp->m_bChatMode = TRUE;
								// 2006-08-01 by dgwoo ???????? ???????? 1 -> 0???? ????.
								m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = 0;
								// 2007.04.24 by bhsohn China IME Working
								// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
								g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
							}
						}
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_3_BUY,i))
					{
						//m_byFocusText = TEXT_COUNT;
						m_nComboState[i][1] = COMBO_CLICK;
						if(!m_nComboActive &&
							m_pComboKindEx->m_nSelectDataIndex >= 0)
						{
							m_nComboActive = 2;
							m_pComboNameEx->m_nSelectDataIndex = -1;
							m_pComboNameEx->SetComboPt(BAZAAR_OPEN_3_BUY_X,BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H *i) + BAZAAR_OPEN_1_H);
						}
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_4_BUY,i))
					{
						m_byFocusText = TEXT_PRICE;
						g_pD3dApp->m_bChatMode = TRUE;
						// 2007.04.24 by bhsohn China IME Working
						// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
						g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
						break;
					}
					else
					{
						m_byFocusText = TEXT_NON;
					}
				}
				else
				{

					m_byFocusText = TEXT_NON;
				}
			}
			// 2007.04.24 by bhsohn China IME Working
			// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
			g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
			
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			//???????? ???? ????
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					// ?????? ???? ?????? ????
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						if(m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
						{
							// ?????? ???? ????
							OnButtonClicked(OPEN_CANCEL);
						}
						else
						{
							// ?????? ????
							OnButtonClicked(OPEN_REGISTER);
						}
					}
					
					m_nPutDelState[i] = BTN_STATE_NORMAL;
				}
			}

			// ???? ???? ????
			if(m_nComboActive == 1)
			{
				if(m_pComboKindEx->m_nSelectDataIndex >= 0)
				{
					// ?????? ???? ?????? ???? ????
					SetDataCombo(2);
					m_nComboActive = 0;
				}
			}
			else if(m_nComboActive == 2)
			{
				if(m_pComboNameEx->m_nSelectDataIndex >= 0)
				{
					m_nComboActive = 0;
					int nItemNum = m_pComboNameEx->m_vecData[m_pComboNameEx->m_nSelectDataIndex].nData;
					int nItemKind = m_pComboKindEx->m_vecData[m_pComboKindEx->m_nSelectDataIndex].nData;
					OnBuyItem(nItemNum, nItemKind);
				}
			}


		}
		break;
		// 2009-01-30 by bhsohn ???? ???? ???? ???? ????
//	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nTotal;
// 				if(m_byFocusText == TEXT_PRICE)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nPrice;
// 							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 							nPrice *= 10;
// 							nPrice += code - '0';
// 							nTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 
// 							//?????? ?????? ???? ???????? ?????? ???????? ????????.
// 							if(nPrice > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								nPrice = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 				else if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nCount;
// 							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 							nCount *= 10;
// 							nCount += code - '0';
// 
// 							nTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 
// 							//?????? ?????? ???? ???????? ?????? ???????? ????????.
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "???????? ?????????????? ??????????????.(???????????? 20????)"
// 								nCount = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 							// 2006-07-28 by dgwoo ???????? ????????.
// 							//CheckSellItemCount();				// ?????? ???? ????
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 			}
// 		}
//		break;
	case WM_KEYDOWN:
		{
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;
				INT64 nTotal;
				if(m_byFocusText == TEXT_PRICE)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nPrice;
							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							nPrice *= 10;
							nPrice += nNumber;
							nTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
							
							//?????? ?????? ???? ???????? ?????? ???????? ????????.
							if(nPrice > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								nPrice = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
				else if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nCount;
							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
							nCount *= 10;
							nCount += nNumber;
							
							nTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							
							//?????? ?????? ???? ???????? ?????? ???????? ????????.
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "???????? ?????????????? ??????????????.(???????????? 20????)"
								nCount = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							
							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							// 2006-07-28 by dgwoo ???????? ????????.
							//CheckSellItemCount();				// ?????? ???? ????
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CheckBtnState()
/// \brief		???? ???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CheckBtnState()
{
	// 2006-07-28 by ispark, ?????? ???? ???? ????
	int i = 0;
	if(m_bBazaarShopStart)
	{
		m_nStartBtnState = BTN_STATE_DEACTIVE;
		m_nStopBtnState = BTN_STATE_NORMAL;

		for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
		{
			m_nPutDelState[i] = BTN_STATE_DEACTIVE;
		}
	}
	else
	{
		m_nStartBtnState = BTN_STATE_NORMAL;
		m_nStopBtnState = BTN_STATE_NORMAL;

		for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
		{
			m_nPutDelState[i] = BTN_STATE_NORMAL;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_RegSellItemOK(MSG_FC_BAZAAR_SELL_PUT_ITEM_OK* pMsg)
/// \brief		?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_RegSellItemOK(MSG_FC_BAZAAR_SELL_PUT_ITEM_OK* pMsg)
{
	// ?????? ???? ????
 	OPEN_BAZAAR_ITEM * pItemInfo = FindItem(pMsg->itemUID);
	if(!pItemInfo)
		return;
		
	pItemInfo->bRegister = TRUE;	
	pItemInfo->pItemBase->CurrentCount = pItemInfo->nItemCount;
	// 2007-11-14 by bhsohn ???? ?????? ?????? ?????? ??????, ???? ???? ???? ?????????? ???? ????	
	if(IS_WEAPON(pItemInfo->pItemBase->Kind))
	{
		// ???? ????????.
		pItemInfo->pItemBase->CurrentCount = pItemInfo->nBulletCount;
	}

	// ???????? ?????? ????
	if(IS_COUNTABLE_ITEM(pItemInfo->pItemBase->Kind))
	{
		CItemInfo* pOrgItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(pItemInfo->pItemBase->UniqueNumber);
		g_pStoreData->UpdateItemCount(pItemInfo->pItemBase->UniqueNumber, pOrgItemInfo->CurrentCount - pItemInfo->nItemCount);
	}
	else
	{
		g_pStoreData->DeleteItem(pItemInfo->pItemBase->UniqueNumber);
	}

	// ?? ???? ????
	CalTotalPrice();

	g_pD3dApp->m_bRequestEnable = TRUE;			// ???? ?????? ????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_RegBuyItemOK(MSG_FC_BAZAAR_BUY_PUT_ITEM_OK* pMsg)
/// \brief		?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_RegBuyItemOK(MSG_FC_BAZAAR_BUY_PUT_ITEM_OK* pMsg)
{
	// ?????? ???? ????
	OPEN_BAZAAR_ITEM * pItemInfo = FindItem(pMsg->itemNum0, 1, TRUE);
	if(!pItemInfo)
		return;
		
	pItemInfo->bRegister = TRUE;
	pItemInfo->nItemIndex = pMsg->nBuyItemIndex0;

	// ?? ???? ????
	CalTotalPrice(); 	

	// ???? ???? ????
	OnReadyBuyItem();

	m_pComboKindEx->m_nSelectDataIndex = -1;
	g_pD3dApp->m_bRequestEnable = TRUE;			// ???? ?????? ????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_DelSellItemOK(MSG_FC_BAZAAR_SELL_CANCEL_ITEM_OK* pMsg)
/// \brief		?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_DelSellItemOK(MSG_FC_BAZAAR_SELL_CANCEL_ITEM_OK* pMsg)
{
	OPEN_BAZAAR_ITEM * it = FindItem(pMsg->itemUID);

	// ???????? ?? ????
	if(IS_COUNTABLE_ITEM(it->pItemBase->Kind))
	{
		CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(it->pItemBase->ItemNum);
		if( pItemInfo )
		{
			pItemInfo->CurrentCount += it->pItemBase->CurrentCount;
		}
		else
		{
			g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition( it->pItemBase );
		}
	}
	else
	{
		g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition( it->pItemBase );
	}

	g_pShuttleChild->ResortingItem();
	g_pShuttleChild->SetShuttleData(5);
	g_pGameMain->m_pInven->SetAllIconInfo();
	
	// ????
	if(it)
	{
		vector<vector<OPEN_BAZAAR_ITEM>::iterator> toDeleteIterators = getEraseIteratorsFromBazarItem(it);
		for (int i = 0; i < toDeleteIterators.size(); i++)
		{
			m_vecOpenBazaarItem.erase(toDeleteIterators[i]);
		}

		// 2010. 02. 11 by ckPark ?????? ??????????
		SetItemInfo( NULL, 0, 0 );
		// end 2010. 02. 11 by ckPark ?????? ??????????
	}

	//?????? ???? ??????????.
	CalTotalPrice();
	
	g_pD3dApp->m_bRequestEnable = TRUE;			// ???? ?????? ????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_DelBuyItemOK(MSG_FC_BAZAAR_BUY_CANCEL_ITEM_OK* pMsg)
/// \brief		?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_DelBuyItemOK(MSG_FC_BAZAAR_BUY_CANCEL_ITEM_OK* pMsg)
{
	// ????
	OPEN_BAZAAR_ITEM * it = FindItem(pMsg->nBuyItemIndex0, 2);
	if(it)
	{
		SAFE_DELETE(it->pItemBase);
		vector<vector<OPEN_BAZAAR_ITEM>::iterator> toDeleteIterators = getEraseIteratorsFromBazarItem(it);
		for (int i = 0; i < toDeleteIterators.size(); i++)
		{
			m_vecOpenBazaarItem.erase(toDeleteIterators[i]);
		}

		// 2010. 02. 11 by ckPark ?????? ??????????
		SetItemInfo( NULL, 0, 0 );
		// end 2010. 02. 11 by ckPark ?????? ??????????
	}

	//?????? ???? ??????????.
	CalTotalPrice();
	
	g_pD3dApp->m_bRequestEnable = TRUE;			// ???? ?????? ????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnSellItem(CItemInfo* pSelectItem)
/// \brief		?????? ???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnSellItem(CItemInfo* pSelectItem)
{
	// 2006-08-04 by ispark, ???? ?????? ???? ???????? ????
	if(!CheckOnSellItem(pSelectItem))
	{
		return;
	}

	// ?????? ????
	OPEN_BAZAAR_ITEM stSellItem;

	stSellItem.pItemBase = new CItemInfo((ITEM_GENERAL*)pSelectItem);
	stSellItem.pItemBase->ChangeRareInfo(pSelectItem->PrefixCodeNum, pSelectItem->SuffixCodeNum);

	// 2010. 02. 11 by ckPark ?????? ??????????
	//stSellItem.pItemBase->SetEnchantParam(pSelectItem->GetEnchantParamFactor(),  pSelectItem->GetEnchantNumber());
	// ?????? ?????? ?? ?????? ???? ????
	stSellItem.pItemBase->CopyItemInfo( pSelectItem );
	// end 2010. 02. 11 by ckPark ?????? ??????????

	stSellItem.nItemCount = 1;	

	// 2007-11-14 by bhsohn ???? ?????? ?????? ?????? ??????, ???? ???? ???? ?????????? ???? ????
	//stSellItem.pItemBase->CurrentCount = 1;
	// ???????? ???????? ????????.
	if(IS_WEAPON(stSellItem.pItemBase->Kind))
	{
		stSellItem.nBulletCount = stSellItem.pItemBase->CurrentCount;		
	}	
	stSellItem.pItemBase->CurrentCount = 1;	
	// end 2007-11-14 by bhsohn ???? ?????? ?????? ?????? ??????, ???? ???? ???? ?????????? ???? ????	

	m_vecOpenBazaarItem.push_back(stSellItem);

	// ???? ?????? ????????
	if(m_vecOpenBazaarItem.size() > m_nScrollLine + SHOP_ITEM_SLOT_NUMBER)
	{
		m_nScrollLine++;
		if(m_nScrollLine > BAZAAR_SHOP_SCROLL_MAX_LINE)
		{
			SetScrollEndLine();
		}
		else
		{
			m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnSellDelItem(UID64_t itemUID)
/// \brief		?????? ???? ???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnSellDelItem(UID64_t itemUID)
{
	OPEN_BAZAAR_ITEM * it = FindItem(itemUID);

	// ????
	if(it)
	{
		vector<vector<OPEN_BAZAAR_ITEM>::iterator> toDeleteIterators = getEraseIteratorsFromBazarItem(it);
		for (int i = 0; i < toDeleteIterators.size(); i++)
		{
			m_vecOpenBazaarItem.erase(toDeleteIterators[i]);
		}

		// 2010. 02. 11 by ckPark ?????? ??????????
		SetItemInfo( NULL, 0, 0 );
		// end 2010. 02. 11 by ckPark ?????? ??????????
	}

	//?????? ???? ??????????.
	CalTotalPrice();

}

///////////////////////////////////////////////////////////////////////////////
/// \class		PointInRect(POINT &pt,RenderRect &rt);
/// \brief		???????? rt ?? ???????? ?????????? ??????????.
///
/// \author		dgwoo
/// \version	
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///////////////////////////////////////////////////////////////////////////////
bool CINFCityBazaarOpen::PointInRect(POINT &pt,RenderRect &rt)
{
	if(pt.x > rt.x &&
		pt.x < rt.x + rt.w &&
		pt.y > rt.y &&
		pt.y < rt.y + rt.h)
	{
		return TRUE;
	}
	return FALSE;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_DelItem(int nSelectItem)
/// \brief		?????? ???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_DelItem(int nSelectItem)
{
	// ?????? ???? ????
	if(m_nSelectIndex != -1)
	{
	if(m_byBazaarType == 1)
	{
		MSG_FC_BAZAAR_SELL_CANCEL_ITEM sMsg;
		sMsg.itemUID = m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->UniqueNumber;
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_CANCEL_ITEM, (char*)&sMsg, sizeof(sMsg));
	}
	else if(m_byBazaarType == 2)
	{
		MSG_FC_BAZAAR_BUY_CANCEL_ITEM sMsg;
		sMsg.nBuyItemIndex0 = m_vecOpenBazaarItem[m_nSelectIndex].nItemIndex;
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_CANCEL_ITEM, (char*)&sMsg, sizeof(sMsg));
	}
		
	g_pD3dApp->m_bRequestEnable = FALSE;			// ???? ?????? ????????
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_RegItem(int nSelectItem)
/// \brief		?????? ???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_RegItem(int nSelectItem)
{
	if(m_nSelectIndex != -1)
	{
		// ???? ???? ????
		if(m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice <= 0)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0103 , _MESSAGE);		// "?????? ?????? ??????.
			return;
		}
		if(m_vecOpenBazaarItem[m_nSelectIndex].nItemCount <= 0)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0104 , _MESSAGE);		// "?????? ??????????.
			return;
		}
	

		// ?????? ????
		if(m_byBazaarType == 1)
		{
			// ???????? ???? ???? ????
			// 2006-08-02 by dgwoo (???? ???? + ???????? ???????? ????) = 20???? ???????? ???? ????????.
			int tempSpi = g_pGameMain->m_pInven->GetItemSpi();
			int total = tempSpi + m_nTotal;
			if(MAX_ITEM_COUNTS < total)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005 , _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
				return;
			}

			// ?????? ????
			MSG_FC_BAZAAR_SELL_PUT_ITEM sMsg;
			sMsg.itemUID = m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->UniqueNumber;
			sMsg.nAmount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
			sMsg.nEachPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
			g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_PUT_ITEM, (char*)&sMsg, sizeof(sMsg));
		}
		else if(m_byBazaarType == 2)
		{
			// ???????? ???? ???? ????
			if(m_vecOpenBazaarItem[m_nSelectIndex].pItemBase == NULL)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060803_0000 , _MESSAGE);		// "???????? ??????????"
				return;
			}
			INT64 tempTotal = m_nTotal + (m_vecOpenBazaarItem[m_nSelectIndex].nItemCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice);
			if(tempTotal > g_pGameMain->m_pInven->GetItemSpi())
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0002 ,_MESSAGE);		//	"???????? ?????? ??????????.
				return;
			}

			// ?????? ????
			MSG_FC_BAZAAR_BUY_PUT_ITEM sMsg;
			sMsg.itemNum0 = m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->ItemNum;
			sMsg.nAmount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
			sMsg.nEachPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
			g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_PUT_ITEM, (char*)&sMsg, sizeof(sMsg));
		}
	
		g_pD3dApp->m_bRequestEnable = FALSE;			// ???? ?????? ????????
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnReadyBuyItem()
/// \brief		?????? ???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnReadyBuyItem()
{
	// ?????? ???? MAX?? ????????.
	if(m_vecOpenBazaarItem.size() == BAZAARSHOP_ITEMCOUNT)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0000, _MESSAGE);	// "?????? ?????? ?? ?? ????????."
		return;
	}

	// ?????? ????
	OPEN_BAZAAR_ITEM stBuyItem;
	m_vecOpenBazaarItem.push_back(stBuyItem);

	// ???? ?????? ????????
	if(m_vecOpenBazaarItem.size() > m_nScrollLine + SHOP_ITEM_SLOT_NUMBER)
	{
		m_nScrollLine++;
		if(m_nScrollLine > BAZAAR_SHOP_SCROLL_MAX_LINE)
		{
			SetScrollEndLine();
		}
		else
		{
			m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnBuyItem(int ItemNum)
/// \brief		???????? ?????? ?????? ????
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnBuyItem(int ItemNum, int ItemKind)
{
	// 2006-08-04 by ispark, ???? ?????? ???? ???????? ????
	if(!CheckOnBuyItem(ItemNum, ItemKind))
	{
		return;
	}

	// ?????? ????
	int nInputItemIndex = m_vecOpenBazaarItem.size() - 1;
	if(nInputItemIndex >= 0)
	{
		if(m_vecOpenBazaarItem[nInputItemIndex].pItemBase)
		{
			SAFE_DELETE(m_vecOpenBazaarItem[nInputItemIndex].pItemBase);
		}

		ITEM_GENERAL stItemBase;
		stItemBase.ItemNum				= ItemNum;
		stItemBase.UniqueNumber			= 0;
		stItemBase.Kind					= ItemKind;
		stItemBase.PrefixCodeNum		= 0;
		stItemBase.SuffixCodeNum		= 0;
		stItemBase.CurrentCount			= 0;

		CItemInfo * pItemInfo = new CItemInfo(&stItemBase);
		m_vecOpenBazaarItem[nInputItemIndex].pItemBase = pItemInfo;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_OpenShop()
/// \brief		???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_OpenShop()
{
	//???? ???? ?????? ?????? ?????? ?????? ???????? ??????.
	if( 2 > strlen(m_strInputMessage))
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0102, _MESSAGE);		// "?????????? ?????? ???????? 2???? ??????????.
		return;
	}
	// 2006-08-01 by dgwoo ?????????? Sell:0  Buy:1?? ?????? ???? ?????? ?????? ??????????.
	if(m_vecOpenBazaarItem.size() <= (m_byBazaarType-1))
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRERR_ERROR_0025, _MESSAGE);			// "???? ???????? ????????.
		return;
	}

	// ???? ?? ?? ?????? ????
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		// ???? ???? ???? ??????
		if(!it->bRegister)
		{
			if(m_byBazaarType == 2)
			{
				if(!it->pItemBase)
				{
					m_vecOpenBazaarItem.erase(it);

					// 2010. 02. 11 by ckPark ?????? ??????????
					SetItemInfo( NULL, 0, 0 );
					// end 2010. 02. 11 by ckPark ?????? ??????????

					break;
				}
			}
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0001, _MESSAGE);	// "?????? ?????? ?????? ??????."
			return;
		}

		it++;
	}

	// ?????? ????
	if(m_byBazaarType == 1)
	{
		MSG_FC_BAZAAR_SELL_START sMsg;
		strncpy(sMsg.szBazaarName, m_strInputMessage, SIZE_MAX_BAZAAR_NAME);
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_START, (char*)&sMsg, sizeof(sMsg));
	}
	else if(m_byBazaarType == 2)
	{
		MSG_FC_BAZAAR_BUY_START sMsg;
		strncpy(sMsg.szBazaarName, m_strInputMessage, SIZE_MAX_BAZAAR_NAME);
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_START, (char*)&sMsg, sizeof(sMsg));
	}
	
	g_pD3dApp->m_bRequestEnable = FALSE;			// ???? ?????? ????????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_CloseShop()
/// \brief		???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_CloseShop()
{
	m_bBazaarShopEnd = TRUE; // ?????? ?????? ?????? ?????? ?????? ?? ???? ??????.	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_OpenShopOK()
/// \brief		???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_OpenShopOK()
{
	m_bBazaarShopStart = TRUE;
	CheckBtnState();

	if(m_byBazaarType == 1)
	{
		if(g_pCharacterChild)
		{
			char szBazaarName [SIZE_MAX_BAZAAR_FULL_NAME];
			
			// 2007-07-09 by bhsohn China Working
			memset(szBazaarName , 0x00, SIZE_MAX_BAZAAR_FULL_NAME);

			wsprintf(szBazaarName, STRMSG_C_060811_0000, m_strInputMessage);
			g_pCharacterChild->m_pMoveChatShop = new CChatMoveData(NULL,szBazaarName,COLOR_SKILL_USE,11,500,32,240,TRUE, 0x0001);
			g_pCharacterChild->m_pMoveChatShop->InitDeviceObjects();
			g_pCharacterChild->m_pMoveChatShop->RestoreDeviceObjects();
		}
	}
	else if(m_byBazaarType == 2)
	{
		if(g_pCharacterChild)
		{
			char szBazaarName [SIZE_MAX_BAZAAR_FULL_NAME];
			
			// 2007-07-09 by bhsohn China Working
			memset(szBazaarName , 0x00, SIZE_MAX_BAZAAR_FULL_NAME);

			wsprintf(szBazaarName, STRMSG_C_060811_0001, m_strInputMessage);
			g_pCharacterChild->m_pMoveChatShop = new CChatMoveData(NULL,szBazaarName,GUI_FONT_COLOR_YM,11,500,32,240,TRUE, 0x0001);
			g_pCharacterChild->m_pMoveChatShop->InitDeviceObjects();
			g_pCharacterChild->m_pMoveChatShop->RestoreDeviceObjects();
		}
	}

	char strLogMsg[1024];

	// 2007-07-09 by bhsohn China Working
	memset(strLogMsg, 0x00, 1024);

	ATUM_DATE_TIME tmATime(TRUE);
	wsprintf(strLogMsg, STRMSG_C_060730_0004, g_pShuttleChild->m_myShuttleInfo.CharacterName, tmATime.GetLocalDateTimeString(string(),GetLanguageType(), TRUE));
	
	CheckLogMsg(strLogMsg, GUI_FONT_COLOR_W);
	g_pD3dApp->m_bRequestEnable = TRUE;			// ???? ?????? ????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CalTotalPrice()
/// \brief		???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CalTotalPrice()
{
	m_nTotal = 0;

	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		m_nTotal += it->nItemTotal;

		it++;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CINFCityBazaarOpen::GetItemIndexByPos(int nPosY)
/// \brief		?????????? ?????? ?????? ????????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityBazaarOpen::GetItemIndexByPos(int nPosY)
{
	int nItemCount = m_vecOpenBazaarItem.size();
	if(nItemCount >= m_nScrollLine)
	{
		int nPtLine = (nPosY - BAZAAR_SHOP_ITEM_Y) / BAZAAR_SHOP_ITEM_H;

		if(nPtLine + m_nScrollLine < nItemCount)
		{
			return nPtLine + m_nScrollLine;
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CINFCityBazaarOpen::GetShopItemCount(UID64_t itemUID)
/// \brief		
/// \author		ispark
/// \date		2006-08-10 ~ 2006-08-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityBazaarOpen::GetShopItemCount(UID64_t itemUID)
{
	OPEN_BAZAAR_ITEM* pOpenItem = FindItem(itemUID);

	int nItemCount = 0;

	if(pOpenItem)
	{
		nItemCount = pOpenItem->nItemCount;
	}
	return nItemCount;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(CItemInfo *pItemInfo)
/// \brief		???? ?????? ???? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(CItemInfo *pItemInfo)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		if(it->pItemBase->UniqueNumber == pItemInfo->UniqueNumber)
		{
			return &*it;
		}

		it++;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(UID64_t itemUID)
/// \brief		?????? UID?? ?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(UID64_t itemUID)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		if(it->pItemBase->UniqueNumber == itemUID)
		{
			return &*it;
		}

		it++;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(int nItemNum, BYTE nItemType, BOOL bRegister)
/// \brief		?????? ItemNum?? ?????? ???????? ?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(int nItemNum, BYTE nItemType, BOOL bRegister)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		if(nItemType == 1)
		{
			if(it->pItemBase->ItemNum == nItemNum && bRegister == FALSE)
			{
				return &*it;
			}
			else if(bRegister == TRUE && 
					it->pItemBase->ItemNum == nItemNum &&
					it->bRegister == FALSE)
			{
				return &*it;
			}
		}
		else if(nItemType == 2)
		{
			if(it->nItemIndex == nItemNum)
			{
				return &*it;
			}
		}

		it++;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CItemInfo *	CINFCityBazaarOpen::GetShopItemInfo(UID64_t itemUID)
/// \brief		?????? ???? ?? ?????? ????
/// \author		ispark
/// \date		2006-09-04 ~ 2006-09-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CItemInfo *	CINFCityBazaarOpen::GetShopItemInfo(UID64_t itemUID)
{
	// 2008-12-08 by dgwoo ???????? ???????? ????.
	OPEN_BAZAAR_ITEM* pItem = FindItem(itemUID);
	if(pItem)
		return pItem->pItemBase;
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CheckSellItemCount()
/// \brief		?? ?????????? ???? ?????? ?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CheckSellItemCount()
{
	if(m_nSelectIndex != -1)
	{
		CItemInfo* pOnItemInfo = (CItemInfo *)m_vecOpenBazaarItem[m_nSelectIndex].pItemBase;
		CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(pOnItemInfo->UniqueNumber);
		if(pItemInfo && pItemInfo->CurrentCount < m_vecOpenBazaarItem[m_nSelectIndex].nItemCount)
		{
			m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = pItemInfo->CurrentCount;
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityBazaarOpen::CheckBuyCountItem(int nKind, int nItemNum)
/// \brief		
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityBazaarOpen::CheckBuyCountItem(int nKind, int nItemNum)
{
	if(IS_COUNTABLE_ITEM(nKind))
	{
		vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
		while(it != m_vecOpenBazaarItem.end())
		{
			if(it->pItemBase && it->pItemBase->ItemNum == nItemNum)
			{
				return TRUE;
			}

			it++;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
/// \brief		???? ???????? ???????? 
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
{
	CEnemyData * pEnemy = NULL;
	CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
	if(itEnemy != g_pScene->m_mapEnemyList.end())
	{
		pEnemy = itEnemy->second;
	}

	if(pEnemy)
	{
		OPEN_BAZAAR_ITEM* pBazaarItem = FindItem(pMsg->itemUID);
		if(pBazaarItem)
		{
			char strLogMsg[1024];
			ATUM_DATE_TIME tmATime(TRUE);
			wsprintf(strLogMsg, STRMSG_C_060731_0000, 
					pEnemy->m_infoCharacter.CharacterInfo.CharacterName, 
					pBazaarItem->pItemBase->ItemInfo->ItemName, 
					pMsg->nAmount0, 
					pMsg->nAmount0 * pBazaarItem->nItemPrice,
					tmATime.GetLocalDateTimeString(string(),GetLanguageType(), TRUE));

			CheckLogMsg(strLogMsg, COLOR_SKILL_USE);
			//?????? ???????? ?????? ?????????? ?????? ???? ??????????.
			pBazaarItem->nItemCount -= pMsg->nAmount0;
			pBazaarItem->pItemBase->CurrentCount = pBazaarItem->nItemCount;
			pBazaarItem->nItemTotal = pBazaarItem->nItemCount * pBazaarItem->nItemPrice;
			m_nTotal = m_nTotal - (pMsg->nAmount0 * pBazaarItem->nItemPrice);

			// 2010. 03. 15 by jskim ?????? ???????? ???? ?????? ?????? ?????? 2?? ???????? ???? ????
			CItemInfo* pOrgItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(pMsg->itemUID);
			if(pOrgItemInfo)
			{
				g_pStoreData->UpdateItemCount(pMsg->itemUID, pOrgItemInfo->CurrentCount - pBazaarItem->nItemCount);
			}
			//end 2010. 03. 15 by jskim ?????? ???????? ???? ?????? ?????? ?????? 2?? ???????? ???? ????
			// ?????? ???? ?? 0 ?????? ????
			if(pBazaarItem->nItemCount <= 0)
			{
				SAFE_DELETE(pBazaarItem->pItemBase);
				vector<vector<OPEN_BAZAAR_ITEM>::iterator> toDeleteIterators = getEraseIteratorsFromBazarItem(pBazaarItem);
				for (int i = 0; i < toDeleteIterators.size(); i++)
				{
					m_vecOpenBazaarItem.erase(toDeleteIterators[i]);
				}

				// 2010. 02. 11 by ckPark ?????? ??????????
				SetItemInfo( NULL, 0, 0 );
				// end 2010. 02. 11 by ckPark ?????? ??????????

				if(m_vecOpenBazaarItem.size() <= 0)
				{
					// ???? ???????? ?????? ????
				}
			}
		}
	}
	else
	{
		CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.begin();
		while(itEnemy != g_pScene->m_mapEnemyList.end())
		{
			DbgOut("?????? ???? ???? (%d)\n", itEnemy->second->m_infoCharacter.CharacterInfo.ClientIndex);
			itEnemy++;
		}

		DbgOut("?????? ???? ???? (%d)\n", pMsg->clientIndex0);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
/// \brief		???????????? ??????????.
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
{
	CEnemyData * pEnemy = NULL;
	CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
	if(itEnemy != g_pScene->m_mapEnemyList.end())
	{
		pEnemy = itEnemy->second;
	}

	if(pEnemy)
	{
		OPEN_BAZAAR_ITEM* pBazaarItem = FindItem(pMsg->nBuyItemIndex0, 2);
		if(pBazaarItem)
		{
			char strLogMsg[1024];
			ATUM_DATE_TIME tmATime(TRUE);
			wsprintf(strLogMsg, STRMSG_C_060731_0002, 
					pEnemy->m_infoCharacter.CharacterInfo.CharacterName, 
					pBazaarItem->pItemBase->ItemInfo->ItemName, 
					pMsg->nAmount0, 
					pMsg->nAmount0 * pBazaarItem->nItemPrice,
					tmATime.GetLocalDateTimeString(string(),GetLanguageType(), TRUE));

			CheckLogMsg(strLogMsg, GUI_FONT_COLOR_YM);
			pBazaarItem->nItemCount -= pMsg->nAmount0;
			pBazaarItem->nItemTotal = pBazaarItem->nItemCount * pBazaarItem->nItemPrice;
			m_nTotal = m_nTotal - (pMsg->nAmount0 * pBazaarItem->nItemPrice);

			// ?????? ???? ?? 0 ?????? ????
			if(pBazaarItem->nItemCount <= 0)
			{
				vector<vector<OPEN_BAZAAR_ITEM>::iterator> toDeleteIterators = getEraseIteratorsFromBazarItem(pBazaarItem);
				for (int i = 0; i < toDeleteIterators.size(); i++)
				{
					m_vecOpenBazaarItem.erase(toDeleteIterators[i]);
				}

				// 2010. 02. 11 by ckPark ?????? ??????????
				SetItemInfo( NULL, 0, 0 );
				// end 2010. 02. 11 by ckPark ?????? ??????????

				if(m_vecOpenBazaarItem.size() <= 0)
				{
					// ???? ???????? ?????? ????
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			?????? ???? ????
/// \brief		
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_CustomerInfoOK(MSG_FC_BAZAAR_CUSTOMER_INFO_OK* pMsg)
{
	CEnemyData * pEnemy = NULL;
	CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
	if(itEnemy != g_pScene->m_mapEnemyList.end())
	{
		pEnemy = itEnemy->second;
	}

	if(pEnemy)
	{
		char strLogMsg[1024];
		ATUM_DATE_TIME tmATime(TRUE);
		wsprintf(strLogMsg, STRMSG_C_060731_0001, pEnemy->m_infoCharacter.CharacterInfo.CharacterName, tmATime.GetLocalDateTimeString(string(),GetLanguageType(), TRUE));
		CheckLogMsg(strLogMsg, GUI_FONT_COLOR_W);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CheckLogMsg(char * msgLog, DWORD dwColor)
/// \brief		???? ?????? ????
/// \author		ispark
/// \date		2006-08-01 ~ 2006-08-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CheckLogMsg(char * msgLog, DWORD dwColor)
{
	int nMsgCount = 1;
	vector<string> vecChatMessage;
	vecChatMessage.clear();
	STRING_CULL(msgLog, BAZAAR_SHOP_LOG_STRING_LENGTH, &vecChatMessage, m_pFontLogMsg);

	for(int i = 0; i < vecChatMessage.size(); i++)
	{
		m_LogChat.PushChatLine((char*)vecChatMessage[i].c_str(), dwColor);
	}

	if(m_byTabIndex == 1)
	{
		m_nScrollMaxCount = m_LogChat.m_nStoredLineCounts;
		SetScrollEndLine();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityBazaarOpen::CheckOnSellItem(CItemInfo* pSelectItem)
/// \brief		???? ?????? ???? ?????????? ????
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityBazaarOpen::CheckOnSellItem(CItemInfo* pSelectItem)
{
	// ?????? ?????? ??????.
	// ?????? ???? MAX?? ????????.
	// ???????????? ???? ?????? ????.
	if(pSelectItem->Wear != WEAR_NOT_ATTACHED)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_SHOP_0010, _MESSAGE);		// "?????? ???????? ?? ?? ????????."
		return FALSE;
	}
	else if(FindItem(pSelectItem))
	{
		// ????
		g_pGameMain->m_pInfWindow->AddMsgBox(STRERR_ERROR_0140, _MESSAGE);		// "?????? ???? ???????? ????????."
		return FALSE;
	}
	else if(m_vecOpenBazaarItem.size() == BAZAARSHOP_ITEMCOUNT)
	{
		// ???? MAX
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0000, _MESSAGE);	// "?????? ?????? ?? ?? ????????."
		return FALSE;
	}
	else if(!COMPARE_BIT_FLAG(pSelectItem->ItemInfo->ItemAttribute, ITEM_ATTR_BAZAAR_ITEM))
	{
		// ???? ?? ?? ???? ??????
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0003, _MESSAGE);	// "?????? ?? ?? ???? ?????? ??????."
		return FALSE;
	}

	// ?????? ???? ????
	int nItemListCount = m_vecOpenBazaarItem.size();
	if(nItemListCount > 0)
	{
		if(!m_vecOpenBazaarItem[nItemListCount - 1].bRegister)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0001, _MESSAGE);	// "?????? ?????? ?????? ??????."
			return FALSE;
		}
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityBazaarOpen::CheckOnBuyItem(int nItemNum, int nItemKind)
/// \brief		???? ?????? ???? ?????????? ????
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityBazaarOpen::CheckOnBuyItem(int nItemNum, int nItemKind)
{
	if(CheckBuyCountItem(nItemKind, nItemNum))
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060803_0004, _MESSAGE);		// "???? ???????? ???? ?????? ?? ?? ????????."
		m_pComboNameEx->m_nSelectDataIndex = -1;
		return FALSE;
	}

	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnButtonClicked(int nButton)
/// \brief		???? ???? ???? ???? ????
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnButtonClicked(int nButton)
{
	if(nButton == OPEN_START)
	{
		// ???? ????
		Send_OpenShop();
	}
	else if(nButton == OPEN_END)
	{
		// ???? ??????
		Send_CloseShop();
	}
	else if(nButton == OPEN_REGISTER)
	{
		// ?????? ????
		Send_RegItem(m_nSelectIndex);
	}
	else if(nButton == OPEN_CANCEL)
	{
		// ?????? ???? ????
		Send_DelItem(m_nSelectIndex);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::InitOpenData()
/// \brief		???? ???? ?????? ??????, ???? ?????? ?????? ?????????? ??????
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::InitOpenData()
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		// ???? ?????? ?????????? ??????
		if(m_byBazaarType == 1 && it->bRegister)
		{
			if(IS_COUNTABLE_ITEM(it->pItemBase->Kind))
			{
				CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(it->pItemBase->ItemNum);
				if( pItemInfo )
				{
					pItemInfo->CurrentCount += it->nItemCount;
				}
				else
				{
					g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition( it->pItemBase );
				}
			}
			else
			{
				g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition( it->pItemBase );
			}
		}
		else
		{
			SAFE_DELETE(it->pItemBase);
		}
		it++;
	}

	if(m_vecOpenBazaarItem.size() > 0 && m_byBazaarType == 1)
	{
		g_pShuttleChild->ResortingItem();
		g_pShuttleChild->SetShuttleData(5);
		if(g_pGameMain && g_pGameMain->m_pInven)
		{
			g_pGameMain->m_pInven->SetAllIconInfo();
		}
	}
	
	m_vecOpenBazaarItem.clear();

	// 2010. 02. 11 by ckPark ?????? ??????????
	SetItemInfo( NULL, 0, 0 );
	// end 2010. 02. 11 by ckPark ?????? ??????????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::SetSelectItem(CItemInfo* pSelectItem, POINT pt)
/// \brief		?????? ????
/// \author		ispark
/// \date		2006-08-07 ~ 2006-08-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::SetSelectItem(CItemInfo* pSelectItem, POINT pt)
{
	if(pSelectItem != NULL)
	{
		// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

		//wsprintf(m_DisplayInfo.IconName, "%08d", pSelectItem->ItemInfo->SourceIndex);
		ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( pSelectItem->GetShapeItemNum() );

		int tempSourceIndex = NULL;
		if( pShapeItem )
		{
			tempSourceIndex = pShapeItem->SourceIndex;
		}
		else
		{
			tempSourceIndex = pSelectItem->ItemInfo->SourceIndex;
		}

		wsprintf( m_DisplayInfo.IconName, "%08d", tempSourceIndex );	
		// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

		wsprintf(m_DisplayInfo.Name, "%s", pSelectItem->ItemInfo->ItemName);
		m_DisplayInfo.pItem = pSelectItem;

		g_pGameMain->SetSelectItem(&m_DisplayInfo, pt, ITEM_BAZAAR_POS);
	}
	else
	{
		memset(m_DisplayInfo.IconName, 0x00, sizeof(m_DisplayInfo.IconName));
		memset(m_DisplayInfo.Name, 0x00, sizeof(m_DisplayInfo.Name));
		m_DisplayInfo.pItem = NULL;

		g_pGameMain->SetSelectItem(NULL, pt, ITEM_BAZAAR_POS);
	}
}










//////////////////////////////////////////////////////////////////////////
// ???? ???? ??????
CINFCityBazaarVisit::CINFCityBazaarVisit(CAtumNode* pParent, CGameData* pGameData, int nBazaarType, ClientIndex_t clientIndex)
{
	m_pParent			= pParent;	// CGameMain*
	m_pGameData			= pGameData;

	m_nScrollLine		= 0;
	m_nSelectIndex		= -1;
	m_nSum				= 0;
	m_byFocusText		= TEXT_NON;
	m_nOutBtnState		= BTN_STATE_NORMAL;

	m_byBazaarType		= nBazaarType;
	m_ClientIndex		= clientIndex;
	m_nSum				= 0;

	// ????
	m_nScrollMaxCount = BAZAARSHOP_ITEMCOUNT;
	m_nScrollMaxLine  = SHOP_ITEM_SLOT_NUMBER;
	m_bBazaarMinAct	  = TRUE;

	m_byBazaarTypeState	= 2;
}

CINFCityBazaarVisit::~CINFCityBazaarVisit()
{

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::InitVisitData()
/// \brief		?????? ?????? ??????
/// \author		ispark
/// \date		2006-08-02 ~ 2006-08-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::InitVisitData()
{
	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while(it != m_vecVisitBazaarItem.end())
	{
		SAFE_DELETE(it->pItemInfo);
		it++;
	}
	m_vecVisitBazaarItem.clear();

	// 2010. 02. 11 by ckPark ?????? ??????????
	SetItemInfo( NULL, 0, 0 );
	// end 2010. 02. 11 by ckPark ?????? ??????????

	if(g_pGameMain)
		g_pGameMain->SetItemInfo( 0, 0, 0, 0);

	m_nScrollLine		= 0;
	m_nSelectIndex		= -1;
	m_nSum				= 0;
	m_nScrollMaxCount = BAZAARSHOP_ITEMCOUNT;
	m_nScrollMaxLine  = SHOP_ITEM_SLOT_NUMBER;
}

HRESULT CINFCityBazaarVisit::InitDeviceObjects()
{
	int i;
	char buf[16] = {0,};
	DataHeader	* pDataHeader;
	
	m_pBackWindow = new CINFImage;
	wsprintf(buf,"sellback");
	pDataHeader = FindResource(buf);
	m_pBackWindow->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	
	for(i = 0; i < 4; i++)
	{
		//???? ????
		m_pDelItemBtn[i] = new CINFImage;
		wsprintf(buf, "canBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pDelItemBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		//?????? ????.
		m_pStopBtn[i] = new CINFImage;
		wsprintf(buf, "exitBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pStopBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}

	//?????? ????.
	m_pBackList = new CINFImage;
	wsprintf(buf, "BackList");
	pDataHeader = FindResource(buf);
	m_pBackList->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	//???? ????.
	m_pSum = new CINFImage;
	wsprintf(buf, "BackSum");
	pDataHeader = FindResource(buf);
	m_pSum->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	// ?????? ????
	m_pScrollButton = new CINFImage;
	pDataHeader = FindResource("c_scrlb");
	m_pScrollButton->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	

	/*--------------------------------------------------------------------------*/
	// ???? ???? ?????? ???? ??????
	//?? ????.
	m_pBackTab = new CINFImage;
	wsprintf(buf, "BackTabV_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackTab->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	//?????? ????.
	m_pBackItem = new CINFImage;
	wsprintf(buf, "BackItemV_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackItem->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	// ???? ????
	m_pSelectBar = new CINFImage;
	wsprintf(buf, "SelItemV_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pSelectBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	if(m_byBazaarType == 1)
	{
		for(i = 0; i < 4; i++)
		{
			//???? ????.
			m_pOKBtn[i] = new CINFImage;
			wsprintf(buf, "buyBtn_%d",i);
			pDataHeader = FindResource(buf);
			m_pOKBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		}

	}
	else if(m_byBazaarType == 2)
	{
		for(i = 0; i < 4; i++)
		{
			//???? ????.
			m_pOKBtn[i] = new CINFImage;
			wsprintf(buf, "sellBtn_%d",i);
			pDataHeader = FindResource(buf);
			m_pOKBtn[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		}
	}
	/*--------------------------------------------------------------------------*/

	// 2006-11-01 by dgwoo	
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_NAME_W,32);
	m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_PRICE_W,32);
	m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemPrice->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_COUNT_W,32);
	m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,64,32);
	m_pFontItemCount->InitDeviceObjects(g_pD3dDev);
	//m_pFontBuySellItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_COUNT_W,32);
	m_pFontBuySellItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,64,32);
	m_pFontBuySellItemCount->InitDeviceObjects(g_pD3dDev);

	m_pFontSumPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontSumPrice->InitDeviceObjects(g_pD3dDev);

	return S_OK;
}

HRESULT CINFCityBazaarVisit::RestoreDeviceObjects()
{
	int i;
	m_pBackWindow->RestoreDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->RestoreDeviceObjects();
		m_pOKBtn[i]->RestoreDeviceObjects();
		m_pStopBtn[i]->RestoreDeviceObjects();
	}

	m_pBackTab->RestoreDeviceObjects();
	m_pBackItem->RestoreDeviceObjects();
	m_pSum->RestoreDeviceObjects();
	m_pBackList->RestoreDeviceObjects();
	m_pScrollButton->RestoreDeviceObjects();
	m_pSelectBar->RestoreDeviceObjects();


	m_pFontItemName->RestoreDeviceObjects();
	m_pFontItemPrice->RestoreDeviceObjects();
	m_pFontItemCount->RestoreDeviceObjects();
	m_pFontBuySellItemCount->RestoreDeviceObjects();

	m_pFontSumPrice->RestoreDeviceObjects();

	return S_OK;
}

HRESULT CINFCityBazaarVisit::DeleteDeviceObjects()
{
	int i;
	m_pBackWindow->DeleteDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->DeleteDeviceObjects();
		m_pOKBtn[i]->DeleteDeviceObjects();
		m_pStopBtn[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pDelItemBtn[i]);
		SAFE_DELETE(m_pOKBtn[i]);
		SAFE_DELETE(m_pStopBtn[i]);
	}

	m_pBackTab->DeleteDeviceObjects();
	m_pBackItem->DeleteDeviceObjects();
	m_pSum->DeleteDeviceObjects();
	m_pBackList->DeleteDeviceObjects();
	m_pScrollButton->DeleteDeviceObjects();
	m_pSelectBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pBackTab);
	SAFE_DELETE(m_pBackItem);
	SAFE_DELETE(m_pSum);
	SAFE_DELETE(m_pBackList);
	SAFE_DELETE(m_pScrollButton);
	SAFE_DELETE(m_pSelectBar);


	m_pFontItemName->DeleteDeviceObjects();
	m_pFontItemPrice->DeleteDeviceObjects();
	m_pFontItemCount->DeleteDeviceObjects();
	m_pFontBuySellItemCount->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontBuySellItemCount);
	SAFE_DELETE(m_pFontItemName);
	SAFE_DELETE(m_pFontItemPrice);
	SAFE_DELETE(m_pFontItemCount);

	m_pFontSumPrice->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontSumPrice);

	InitVisitData();									// 2006-08-02 by ispark
	// 2009-04-13 by bhsohn ???? ???? ??????????, ?????? ?????? ???? ????
// 	g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_BUY_OK);
// 	g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_SELL_OK);
	if(g_pGameMain && g_pGameMain->m_pInfWindow)
	{
		g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_BUY_OK);
		g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_SELL_OK);
	}
	// end 2009-04-13 by bhsohn ???? ???? ??????????, ?????? ?????? ???? ????

	return S_OK;
}

HRESULT CINFCityBazaarVisit::InvalidateDeviceObjects()
{
	int i;
	m_pBackWindow->InvalidateDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->InvalidateDeviceObjects();
		m_pOKBtn[i]->InvalidateDeviceObjects();
		m_pStopBtn[i]->InvalidateDeviceObjects();
	}

	m_pBackTab->InvalidateDeviceObjects();
	m_pBackItem->InvalidateDeviceObjects();
	m_pSum->InvalidateDeviceObjects();
	m_pBackList->InvalidateDeviceObjects();
	m_pScrollButton->InvalidateDeviceObjects();
	m_pSelectBar->InvalidateDeviceObjects();

	m_pFontItemName->InvalidateDeviceObjects();
	m_pFontItemPrice->InvalidateDeviceObjects();
	m_pFontItemCount->InvalidateDeviceObjects();
	m_pFontBuySellItemCount->InvalidateDeviceObjects();

	m_pFontSumPrice->InvalidateDeviceObjects();

	return S_OK;
}

void CINFCityBazaarVisit::Render()
{

	if ( GetbBazaarShopEnd() )
		return;

	// ?????? ????????
	g_pGameMain->m_pInven->RenderOnCityBase();

	/*--------------------------------------------------------------------------*/
	// ???? ??????
	Render_Common();

	/*--------------------------------------------------------------------------*/
	// ?????? ??????
	if(m_byBazaarType == 1)
	{
		Render_Sell();
	}
	else if(m_byBazaarType == 2)
	{
		Render_Buy();
	}
}

void CINFCityBazaarVisit::Render_Common()
{
	//???? ???? ????.
	m_pBackWindow->Move(BAZAAR_SHOP_WINDOW_X,BAZAAR_SHOP_WINDOW_Y);
	m_pBackWindow->Render();

	m_pBackTab->Move(BAZAAR_SHOP_TAB_START_X, BAZAAR_SHOP_TAB_START_Y);
	m_pBackTab->Render();

	m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y);
	m_pBackList->Render();
	//????
	m_pSum->Move(BAZAAR_VISIT_TOTAL_PRICE_X, BAZAAR_VISIT_TOTAL_PRICE_Y);
	m_pSum->Render();

	char temp1[64];
	char temp2[64];
	wsprintf( temp1, "%d", m_nSum );
	MakeCurrencySeparator( temp2, temp1, 3, ',' );

	//?????? ?????? ????..
	SIZE texSize = m_pFontSumPrice->GetStringSize(temp2);
	m_pFontSumPrice->DrawText(BAZAAR_VISIT_TOTAL_PRICE_X+BAZAAR_VISIT_TOTAL_PRICE_W-texSize.cx,BAZAAR_VISIT_TOTAL_PRICE_Y, GUI_FONT_COLOR_W,temp2, 0L);

	// ??????
	m_pStopBtn[m_nOutBtnState]->Move(BAZAAR_VISIT_OUT_X, BAZAAR_VISIT_OUT_Y);
	m_pStopBtn[m_nOutBtnState]->Render();

	// ??????
	m_pScrollButton->Move(BAZAAR_SHOP_VISIT_SCROLL_X, BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
	m_pScrollButton->Render();
}

void CINFCityBazaarVisit::Render_Sell()
{
	/*--------------------------------------------------------------------------*/
	//?????? ???? ???? ?? ????.	
	int i = 0;
	int nItemCount = m_vecVisitBazaarItem.size();
	if(nItemCount < m_nScrollLine)
		return;
	
	vector<VISIT_BAZAAR_ITEM>::iterator ite = m_vecVisitBazaarItem.begin();
	while(ite != m_vecVisitBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}
			// ????
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}

			// ??????
			SIZE size;
			char buf[64] = {0,};
			char buf1[64] = {0,};


			// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????
			//wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			if( !ite->pItemInfo->ShapeItemNum )
				wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemInfo->ShapeItemNum );
				if( pShapeItem )
					wsprintf(buf, "%08d", pShapeItem->SourceIndex );
				else
					wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex );
					
			}
			// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????


			g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
			g_pGameMain->m_pIcon->Render();

			// 2010. 02. 11 by ckPark ?????? ??????????
			if( (*ite).pItemInfo->ItemInfo->InvokingDestParamID
				|| (*ite).pItemInfo->ItemInfo->InvokingDestParamIDByUse )
			{
				char buf[128];

				if( GetString_CoolTime( (*ite).pItemInfo, buf ) )
				{
					int nFontPosX = BAZAAR_SHOP_ICON_X;
					int nFontPosY = BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H) + 6;

					m_pFontItemName->DrawText( nFontPosX, nFontPosY, GUI_FONT_COLOR, buf, 0L );
				}
			}
			// end 2010. 02. 11 by ckPark ?????? ??????????

			// ?????? ???? ????
			if(ite->nAmount0 > 1)
			{
				wsprintf( buf1, "%d", ite->nAmount0);
				size = m_pFontBuySellItemCount->GetStringSize(buf1);
				m_pFontBuySellItemCount->DrawText(BAZAAR_VISIT_SEL_ITEM_COUNT_X-size.cx,BAZAAR_VISIT_SEL_ITEM_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			}

			// ?????? ????
			wsprintf(buf1,"%s", ite->cItemName);
			m_pFontItemName->DrawText(BAZAAR_VISIT_NAME_X,BAZAAR_VISIT_NAME_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			// ????
			wsprintf( buf1, "%d", ite->nEachPrice0);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
		    m_pFontItemPrice->DrawText(BAZAAR_VISIT_SEL_PRICE_X+BAZAAR_VISIT_SEL_PRICE_W-size.cx,BAZAAR_VISIT_SEL_PRICE_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			// ???? ????
			wsprintf( buf1, "%d", ite->nCurrentCount);
			size = m_pFontItemCount->GetStringSize(buf1);
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemCount,BAZAAR_VISIT_SEL_COUNT_X,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemCount->DrawText(BAZAAR_VISIT_SEL_COUNT_X+(BAZAAR_VISIT_SEL_COUNT_W-size.cx)/2,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			// ????
			wsprintf( buf1, "%d", m_nSum);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontSumPrice->GetStringSize(buf);
			m_pFontSumPrice->DrawText(BAZAAR_VISIT_TOTAL_PRICE_X+BAZAAR_VISIT_TOTAL_PRICE_W-size.cx,BAZAAR_VISIT_TOTAL_PRICE_Y,GUI_FONT_COLOR_W,buf,0L);

			//???? ?? ???? ????.
			m_pOKBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pOKBtn[m_nPutDelState[nLineCount]]->Render();
		}

		ite++;
		i++;
	}
}

void CINFCityBazaarVisit::Render_Buy()
{
	/*--------------------------------------------------------------------------*/
	//?????? ???? ???? ?? ????.	
	int i = 0;
	int nItemCount = m_vecVisitBazaarItem.size();
	if(nItemCount < m_nScrollLine)
		return;
	
	vector<VISIT_BAZAAR_ITEM>::iterator ite = m_vecVisitBazaarItem.begin();
	while(ite != m_vecVisitBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}
			// ????
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}

			// ??????
			SIZE size;
			char buf[64] = {0,};
			char buf1[64] = {0,};


			// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

			//wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			if( !ite->pItemInfo->ShapeItemNum )
				wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemInfo->ShapeItemNum );
				if( pShapeItem )
					wsprintf(buf, "%08d", pShapeItem->SourceIndex);
				else
					wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			}

			// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????


			g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
			g_pGameMain->m_pIcon->Render();

			// ?????? ???? ????
			if(ite->nAmount0 > 1)
			{
				wsprintf( buf1, "%d", ite->nAmount0);
				size = m_pFontBuySellItemCount->GetStringSize(buf1);
				m_pFontBuySellItemCount->DrawText(BAZAAR_VISIT_SEL_ITEM_COUNT_X-size.cx,BAZAAR_VISIT_SEL_ITEM_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			}

			// ?????? ????
			wsprintf(buf1,"%s", ite->cItemName);
			m_pFontItemName->DrawText(BAZAAR_VISIT_NAME_X,BAZAAR_VISIT_NAME_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			// ????
			wsprintf( buf1, "%d", ite->nEachPrice0);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
		    m_pFontItemPrice->DrawText(BAZAAR_VISIT_SEL_PRICE_X+BAZAAR_OPEN_1_BUY_W-size.cx,BAZAAR_VISIT_SEL_PRICE_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			// ???? ????
			wsprintf( buf1, "%d", ite->nCurrentCount);
			size = m_pFontItemCount->GetStringSize(buf1);
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemCount,BAZAAR_VISIT_BUY_COUNT_X,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemCount->DrawText(BAZAAR_VISIT_BUY_COUNT_X+(BAZAAR_VISIT_BUY_COUNT_W-size.cx)/2,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			// ????
			wsprintf( buf1, "%d", m_nSum);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontSumPrice->GetStringSize(buf);
			m_pFontSumPrice->DrawText(BAZAAR_VISIT_TOTAL_PRICE_X+BAZAAR_VISIT_TOTAL_PRICE_W-size.cx,BAZAAR_VISIT_TOTAL_PRICE_Y,GUI_FONT_COLOR_W,buf,0L);

			//???? ?? ???? ????.
			if(ite->bExistence == FALSE)
			{
				m_nPutDelState[nLineCount] = BTN_STATE_DEACTIVE;
			}else
			{// 2008-06-10 by dgwoo ???????????? ???? ?????? ???????? ???????? ????.
				if(m_nPutDelState[nLineCount] == BTN_STATE_DEACTIVE)
					m_nPutDelState[nLineCount] = BTN_STATE_NORMAL;
			}
			
			m_pOKBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pOKBtn[m_nPutDelState[nLineCount]]->Render();
		}

		ite++;
		i++;
	}
}

void CINFCityBazaarVisit::Tick()
{

}


int CINFCityBazaarVisit::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nResultProc = INF_MSGPROC_NORMAL;

	
	/*--------------------------------------------------------------------------*/
	// ???? ??????
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			m_bScrollLock = FALSE;

			if(pt.x >= BAZAAR_VISIT_OUT_X &&
				pt.x <= BAZAAR_VISIT_OUT_X + BAZAAR_SHOP_BTN_OUT_W &&
				pt.y >= BAZAAR_VISIT_OUT_Y &&
				pt.y <= BAZAAR_VISIT_OUT_Y + BAZAAR_SHOP_BTN_H)
			{
				// ????
				CloseVisitShop();
				m_nOutBtnState = BTN_STATE_NORMAL;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				// ????
				CloseVisitShop();
				m_nOutBtnState = BTN_STATE_NORMAL;
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			//???????? ???? ???? ???? 
				//???????? ?????? ?????? ??????????.
			int i;
				for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
				{
					if(m_nPutDelState[i] != BTN_STATE_DEACTIVE)
					{
						if(GetPointInType(pt,BAZAAR_BTN,i))//BAZAAR_BTN
						{
							if(m_nPutDelState[i] != BTN_STATE_CLICK)
								m_nPutDelState[i] = BTN_STATE_OVER;
						}
						else
						{
							m_nPutDelState[i] = BTN_STATE_NORMAL;
						}
					}
				}

			if(GetPointInType(pt,BAZAAR_BTN_VISIT_OUT))
			{
				if(m_nOutBtnState != BTN_STATE_CLICK)
					m_nOutBtnState = BTN_STATE_OVER;
			}
			else
			{
				m_nOutBtnState = BTN_STATE_NORMAL;
			}
		
			// ??????
			if(m_bScrollLock &&
				pt.x >= BAZAAR_SHOP_VISIT_SCROLL_X - 5 && 
				pt.x <= BAZAAR_SHOP_VISIT_SCROLL_X + BAZAAR_SHOP_SCROLL_W + 5)
			{
				int nScrollBtnY = pt.y - m_nScrollBtn;
				if(nScrollBtnY >= BAZAAR_SHOP_SCROLL_Y &&
					nScrollBtnY <= BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					m_nScrollPosition = nScrollBtnY - BAZAAR_SHOP_SCROLL_Y;
					m_nScrollLine = GetScrollLineNumber(m_nScrollPosition);
				}
				else if(nScrollBtnY < BAZAAR_SHOP_SCROLL_Y)
				{
					InitScrollLine();
				}
				else if(nScrollBtnY > BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					SetScrollEndLine();
				}
			}

			// ?????? ????
			if(!g_pGameMain->m_stSelectItem.pSelectItem)
			{
				SetItemInfo(NULL, 0 ,0);
				
				if(GetPointInType(pt,BAZAAR_ICON))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						SetItemInfo((m_vecVisitBazaarItem[nItemIndex].pItemInfo), pt.x, pt.y);
					}
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			int i = 0;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);			
			
			g_pD3dApp->m_bChatMode = FALSE;			

			// 2007.04.24 by bhsohn China IME Working
			// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
			g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif

			if(GetPointInType(pt,BAZAAR_BTN_VISIT_OUT))
			{
				m_nOutBtnState = BTN_STATE_CLICK;
			}
		
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				//???????? ?????? ?????? ??????????.
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_CLICK;
				}

				// ????
				if(!g_pGameMain->m_stSelectItem.pSelectItem && 
					GetPointInType(pt,BAZAAR_SHOP_ITEM,i))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						m_nSelectIndex = nItemIndex;
						// 2006-08-02 by dgwoo ???????? ?????????????? ???? ???? ???? ????????.
						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
						break;
					}
					else
					{
						m_nSelectIndex = -1;
					}
				}
				else
				{
					m_nSelectIndex = -1;
				}
			}

			// ??????
			if(GetPointInType(pt,BAZAAR_SHOP_SCROLL,m_nScrollPosition))
			{
				m_nScrollBtn = pt.y - (BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
				m_bScrollLock = TRUE;
				return INF_MSGPROC_BREAK;
			}	
		}
		break;
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			if(GetPointInType(pt,BAZAAR_SHOP_ITEM_AREA))
			{
				if((int)wParam<0)
				{
					m_nScrollLine++;
					if(m_nScrollLine > BAZAAR_SHOP_SCROLL_MAX_LINE)
					{
						SetScrollEndLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}
				else
				{
					m_nScrollLine--;
					if(m_nScrollLine < 0)
					{
						InitScrollLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}

				return INF_MSGPROC_BREAK;
			}
			
		}
		break;
	}


	if(m_byBazaarType == 1)
	{
		nResultProc = WndProc_Sell(uMsg, wParam, lParam);
	}
	else if(m_byBazaarType == 2)
	{
		nResultProc = WndProc_Buy(uMsg, wParam, lParam);
	}
	
	return nResultProc;
}

int CINFCityBazaarVisit::WndProc_Sell(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			m_bLButtonDown = FALSE;
			m_byFocusText = TEXT_NON;

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				// ?????? ???? ????
				if(m_nSelectIndex == m_nScrollLine + i)
				{
					//???????? ?????????? ???? ????????.
					int kind = m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemInfo->Kind;
					if(IS_COUNTABLE_ITEM(kind) &&
						GetPointInType(pt,BAZAAR_VISIT_SEL_COUNT,i))
					{
						m_byFocusText = TEXT_COUNT;
						g_pD3dApp->m_bChatMode = TRUE;
						break;
					}

					if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
						GetPointInType(pt,BAZAAR_BTN,i))
					{
						m_nPutDelState[i] = BTN_STATE_CLICK;
						break;
					}
				}
			}
			// 2007.04.24 by bhsohn China IME Working
			// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
			g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
		
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			//???????? ???? ????
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_NORMAL;
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					// ?????? ???? ?????? ????
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						// ?????? ????
						Send_SellBuyItem();
						return INF_MSGPROC_BREAK;
					}
				}
			}		

		}
		break;
		// 2009-01-30 by bhsohn ???? ???? ???? ???? ????
// 	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nCount;
// 				if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 							nCount *= 10;
// 							nCount += code - '0';
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								nCount = MAX_ITEM_COUNTS;							
// 							}
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
// 							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
// 						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 					}
// 				}
// 			}
// 		}
// 		break;
	case WM_KEYDOWN:
		{			
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;
				INT64 nCount;
				if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
							nCount *= 10;
							nCount += nNumber;
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								nCount = MAX_ITEM_COUNTS;							
							}
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
					}
				}
			}
		}
		break;				
		// end 2009-01-30 by bhsohn ???? ???? ???? ???? ???? ????
	}
	return INF_MSGPROC_NORMAL;
}


int CINFCityBazaarVisit::WndProc_Buy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			int i;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			m_bLButtonDown = FALSE;
			m_byFocusText = TEXT_NON;

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				// ?????? ???? ????
				if(m_nSelectIndex == m_nScrollLine + i)
				{
					if(GetPointInType(pt,BAZAAR_VISIT_BUY_COUNT,i))
					{
						m_byFocusText = TEXT_COUNT;
						g_pD3dApp->m_bChatMode = TRUE;
						break;
					}
				}

				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_CLICK;
					break;
				}
			}		
			// 2007.04.24 by bhsohn China IME Working
			// 2009-01-12 by bhsohn Japan Working
#ifdef IS_USE_ONOFF_IME
//#ifdef LANGUAGE_CHINA	
			g_pD3dApp->m_inputkey.EnableIMEControl(g_pD3dApp->m_bChatMode);
#endif
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			int i;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			//???????? ???? ????
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_NORMAL;
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					// ?????? ???? ?????? ????
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						// ?????? ????
						Send_SellBuyItem();
						return INF_MSGPROC_BREAK;
					}
				}
			}		
		}
		break;
		// 2009-01-30 by bhsohn ???? ???? ???? ???? ????
//	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nCount;
// 				if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 							nCount *= 10;
// 							nCount += code - '0';
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
// 								nCount = MAX_ITEM_COUNTS;
// 							}
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
// 							CItemInfo* pItemInfo = NULL;
// 							pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
// 							// 2007-06-19 by bhsohn ???????????? ???????? ???????? ???? ???? ???????? ???? ????
// //							if(pItemInfo != NULL)
// //								m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount,pItemInfo->CurrentCount);
// 							int nMaxCount = 1;
// 							if(pItemInfo != NULL)
// 							{
// 								if( IS_COUNTABLE_ITEM(pItemInfo->Kind))
// 								{
// 									nMaxCount = pItemInfo->CurrentCount;
// 								}								
// 							}
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, nMaxCount);
// 							// end 2007-06-19 by bhsohn ???????????? ???????? ???????? ???? ???? ???????? ???? ????
// 							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
// 						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 					}
// 				}
// 			}
// 		}
//		break;
case WM_KEYDOWN:
		{
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;

				INT64 nCount;
				if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )					
					{
						if(m_nSelectIndex != -1)
						{
							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
							nCount *= 10;
							nCount += nNumber;
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "?????? ?????????????? ??????????????.(???????????? 20??)"
								nCount = MAX_ITEM_COUNTS;
							}
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
							CItemInfo* pItemInfo = NULL;
							pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
							// 2007-06-19 by bhsohn ???????????? ???????? ???????? ???? ???? ???????? ???? ????
//							if(pItemInfo != NULL)
//								m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount,pItemInfo->CurrentCount);
							int nMaxCount = 1;
							if(pItemInfo != NULL)
							{
								if( IS_COUNTABLE_ITEM(pItemInfo->Kind))
								{
									nMaxCount = pItemInfo->CurrentCount;
								}								
							}
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, nMaxCount);
							// end 2007-06-19 by bhsohn ???????????? ???????? ???????? ???? ???? ???????? ???? ????
							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
					}
				}
			}
		}
		break;
		// end 2009-01-30 by bhsohn ???? ???? ???? ???? ???? ????
	}

	return INF_MSGPROC_NORMAL;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Recv_SetSellItem(SBAZAAR_SELL_ITEM *pSellItem)
/// \brief		???? ?????? ????
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SetSellItem(SBAZAAR_SELL_ITEM *pSellItem)
{
	VISIT_BAZAAR_ITEM VisitItem;

	VisitItem.nAmount0			= pSellItem->nSellAmount0;
	VisitItem.nEachPrice0		= pSellItem->nSellEachPrice0;
	// ?????? ?????? 1?? ???? ????
	if(pSellItem->nSellAmount0 <= 1)
	{
		VisitItem.nCurrentCount = 1;
	}

	ITEM_GENERAL* pItemBase		= new ITEM_GENERAL;
	pItemBase->ItemNum			= pSellItem->nSellItemNum0;
	pItemBase->UniqueNumber		= pSellItem->itemUID;
	pItemBase->CurrentCount		= pSellItem->nSellAmount0;


	// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

	//pItemBase->ColorCode		= pSellItem->ColorCode0;
	pItemBase->ShapeItemNum		= pSellItem->ShapeItemNum0;
	pItemBase->ColorCode		= pSellItem->EffectItemNum0;

	// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

	
	// 2007-07-09 by bhsohn ???? ???? ???? ????
	pItemBase->PrefixCodeNum	= pSellItem->PrefixCodeNum0;
	pItemBase->SuffixCodeNum	= pSellItem->SuffixCodeNum0;
	// end 2007-07-09 by bhsohn ???? ???? ???? ????

	VisitItem.pItemInfo = new CItemInfo(pItemBase);
	VisitItem.pItemInfo->ChangeRareInfo(pSellItem->PrefixCodeNum0, pSellItem->SuffixCodeNum0);

	// 2010. 02. 11 by ckPark ?????? ??????????
	// ???????? ?????? ?????? ???? ????
	VisitItem.pItemInfo->SetCoolElapsedTime( pSellItem->CoolingTime * 1000 );
	// end 2010. 02. 11 by ckPark ?????? ??????????

	SetItemFullName(&VisitItem);
	m_vecVisitBazaarItem.push_back(VisitItem);

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Recv_SetBuyItem(SBAZAAR_BUY_ITEM *pBuyItem)
/// \brief		???? ?????? ????
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SetBuyItem(SBAZAAR_BUY_ITEM *pBuyItem)
{
	VISIT_BAZAAR_ITEM VisitItem;

	VisitItem.nAmount0			= pBuyItem->nBuyAmount0;
	VisitItem.nEachPrice0		= pBuyItem->nBuyEachPrice0;
	VisitItem.nItemIndex		= pBuyItem->nBuyItemIndex0;

	CItemInfo * pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(pBuyItem->nBuyItemNum0);
	if(pItemInfo)
	{
		VisitItem.bExistence	= TRUE;
	}

	ITEM_GENERAL* pItemBase		= new ITEM_GENERAL;
	pItemBase->ItemNum			= pBuyItem->nBuyItemNum0;
	pItemBase->UniqueNumber		= 0;

	VisitItem.pItemInfo = new CItemInfo(pItemBase);

	SetItemFullName(&VisitItem);
	m_vecVisitBazaarItem.push_back(VisitItem);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Recv_SetSellEnchantItem(UID64_t itemUID, int EnchantItemNum)
/// \brief		???? ?????? ????
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SetSellEnchantItem(UID64_t itemUID, int EnchantItemNum)
{
	VISIT_BAZAAR_ITEM VisitItem;

	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while(it != m_vecVisitBazaarItem.end())
	{
		if( it->pItemInfo->UniqueNumber == itemUID)
		{
			it->pItemInfo->AddEnchantItem( EnchantItemNum );
			SetItemFullName(&*it);
			break;
		}
		it++;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CINFCityBazaarVisit::GetItemIndexByPos(int nPosY)
/// \brief		?????????? ?????? ?????? ????????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityBazaarVisit::GetItemIndexByPos(int nPosY)
{
	int nItemCount = m_vecVisitBazaarItem.size();
	if(nItemCount >= m_nScrollLine)
	{
		int nPtLine = (nPosY - BAZAAR_SHOP_ITEM_Y) / BAZAAR_SHOP_ITEM_H;

		if(nPtLine + m_nScrollLine < nItemCount)
		{
			return nPtLine + m_nScrollLine;
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::CheckItemCount()
/// \brief		???? ?????? ??????
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::CheckItemCount()
{
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Send_SellBuyItem(BOOL bRequest)
/// \brief		?????? ???? ?? ???? ????
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Send_SellBuyItem(BOOL bRequest)
{
	const CItemInfo* a_pItemInfo = NULL;

	if( 0 >= m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0104, _MESSAGE);		// "?????? ????????????.
		return;
	}

	// 2006-08-03 by ispark, ???????? ?????????? ???????? ????
	if(m_byBazaarType == 2 && bRequest == FALSE)
	{
		//pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
		a_pItemInfo = g_pStoreData->FindItemInInventoryByItemInfo ( m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo );
		if(a_pItemInfo == NULL)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRERR_ERROR_0025, _MESSAGE);		// "???? ???????? ????????."
			return;
		}
	}

	if(m_nSelectIndex != -1 && bRequest == TRUE)
	{
		if(m_byBazaarType == 1)
		{
			// ?????? ????
			MSG_FC_BAZAAR_SELL_BUY_ITEM sMsg;
			sMsg.clientIndex0 = m_ClientIndex;
			sMsg.itemUID = m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->UniqueNumber;
			sMsg.nAmount0 = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;

			g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_BUY_ITEM, (char*)&sMsg, sizeof(sMsg));
			g_pD3dApp->m_bRequestEnable = FALSE;			// ???? ?????? ????????
		}
		else if(m_byBazaarType == 2)
		{
			// ?????? ????
			//pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
			a_pItemInfo = g_pStoreData->FindItemInInventoryByItemInfo ( m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo );
			if(a_pItemInfo)
			{
				MSG_FC_BAZAAR_BUY_SELL_ITEM sMsg;
				sMsg.clientIndex0 = m_ClientIndex;
				sMsg.nBuyItemIndex0 = m_vecVisitBazaarItem[m_nSelectIndex].nItemIndex;
				sMsg.itemUID = a_pItemInfo->UniqueNumber;
				sMsg.nAmount0 = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
				g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_SELL_ITEM, (char*)&sMsg, sizeof(sMsg));
				g_pD3dApp->m_bRequestEnable = FALSE;			// ???? ?????? ????????
			}
		}
	}
	else if(m_nSelectIndex != -1 && bRequest == FALSE)
	{
		char msgSellBuy[256];
		if(m_byBazaarType == 1)
		{
			wsprintf(msgSellBuy, STRMSG_C_SHOP_0006, m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemInfo->ItemName);
			g_pGameMain->m_pInfWindow->AddMsgBox(msgSellBuy, _Q_BAZAAR_SELL_OK);	// "%s ???????? ???? ?????????????"
		}
		else if(m_byBazaarType == 2)
		{
			wsprintf(msgSellBuy, STRMSG_C_060802_0004, m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemInfo->ItemName);
			g_pGameMain->m_pInfWindow->AddMsgBox(msgSellBuy, _Q_BAZAAR_BUY_OK);	// "%s ???????? ???? ?????????????"
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::CloseVisitShop()
/// \brief		???? ????
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::CloseVisitShop()
{
	// 2009-04-15 by bhsohn ???????? ?????? ?????? ???? ????
	if(g_pD3dApp && g_pD3dApp->m_bChatMode)
	{
		g_pD3dApp->EnableChatMode(FALSE, TRUE);
	}
	// end 2009-04-15 by bhsohn ???????? ?????? ?????? ???? ????
	m_bBazaarShopEnd = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::SetItemFullName(VISIT_BAZAAR_ITEM* pVisitItem)
/// \brief		?????? ?????? ????
/// \author		ispark
/// \date		2006-07-30 ~ 2006-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::SetItemFullName(VISIT_BAZAAR_ITEM* pVisitItem)
{
	char strItemInfo[ITEMINFO_ITEM_FULL_NAME];
	memset( strItemInfo, 0x00, ITEMINFO_ITEM_FULL_NAME);

	RARE_ITEM_INFO* pRefPrefixRareInfo = pVisitItem->pItemInfo->GetPrefixRareInfo();
	RARE_ITEM_INFO* pRefSuffixRareInfo = pVisitItem->pItemInfo->GetSuffixRareInfo();

	if(pRefPrefixRareInfo)
	{
		wsprintf( strItemInfo, "\\g%s\\g", pRefPrefixRareInfo->Name );
	}

	if(pRefPrefixRareInfo || pRefSuffixRareInfo)
	{
		if(pVisitItem->pItemInfo->GetEnchantParamFactor())
		{
			wsprintf( strItemInfo,"%s \\e%s\\e", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);
		}
		else
		{
			wsprintf( strItemInfo,"%s \\g%s\\g", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);
		}
	}
	else
	{
		if(pVisitItem->pItemInfo->GetEnchantParamFactor())
		{
			wsprintf( strItemInfo,"%s \\e%s\\e", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);				
		}
		else
		{
			wsprintf( strItemInfo,"%s %s", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);				
		}
	}

	if(pRefSuffixRareInfo)
	{
		wsprintf( strItemInfo, "%s \\g%s\\g", strItemInfo, pRefSuffixRareInfo->Name );
	}

	memcpy(pVisitItem->cItemName, strItemInfo, ITEMINFO_ITEM_FULL_NAME);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
/// \brief		???? ???? ???? ????
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
{
	// ??????
	VISIT_BAZAAR_ITEM * pBazaarVisitItem = FindItem(pMsg->itemUID);
	if(pBazaarVisitItem)
	{
		pBazaarVisitItem->nAmount0 -= pMsg->nAmount0;
		if(pBazaarVisitItem->nAmount0 <= 0)
		{
			SAFE_DELETE(pBazaarVisitItem->pItemInfo);
			vector<vector<VISIT_BAZAAR_ITEM>::iterator> toDeleteIterators = getEraseIteratorsFromBazarVisitItem(pBazaarVisitItem);
			for (int i = 0; i < toDeleteIterators.size(); i++)
			{
				m_vecVisitBazaarItem.erase(toDeleteIterators[i]);
			}

			// 2010. 02. 11 by ckPark ?????? ??????????
			SetItemInfo( NULL, 0, 0 );
			// end 2010. 02. 11 by ckPark ?????? ??????????

			if(m_vecVisitBazaarItem.size() <= 0)
			{
				// ????
				CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
				if(itEnemy != g_pScene->m_mapEnemyList.end())
				{
					itEnemy->second->DeleteChatMoveShop();
				}
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060801_0000, COLOR_ERROR);
				CloseVisitShop();
			}
		}
		// 2006-08-02 by dgwoo ?????? ???? ???? ?????????? ?????? ?????? ?????? ?????? ??????????.
		if(pBazaarVisitItem->nAmount0 < m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount)
			m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = pBazaarVisitItem->nAmount0;
	}

	g_pD3dApp->m_bRequestEnable = TRUE;			// ???? ?????? ????????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
/// \brief		???? ???? ???? ????
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
{
	// ??????
	VISIT_BAZAAR_ITEM * pBazaarVisitItem = FindItem(pMsg->nBuyItemIndex0);
	if(pBazaarVisitItem)
	{
		pBazaarVisitItem->nAmount0 -= pMsg-> nAmount0;
		pBazaarVisitItem->pItemInfo->CurrentCount = pBazaarVisitItem->nAmount0;
		if(pBazaarVisitItem->nAmount0 <= 0)
		{
			SAFE_DELETE(pBazaarVisitItem->pItemInfo);
			vector<vector<VISIT_BAZAAR_ITEM>::iterator> toDeleteIterators = getEraseIteratorsFromBazarVisitItem(pBazaarVisitItem);
			for (int i = 0; i < toDeleteIterators.size(); i++)
			{
				m_vecVisitBazaarItem.erase(toDeleteIterators[i]);
			}

			// 2010. 02. 11 by ckPark ?????? ??????????
			SetItemInfo( NULL, 0, 0 );
			// end 2010. 02. 11 by ckPark ?????? ??????????

			if(m_vecVisitBazaarItem.size() <= 0)
			{
				// ????
				CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
				if(itEnemy != g_pScene->m_mapEnemyList.end())
				{
					itEnemy->second->DeleteChatMoveShop();
				}
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060801_0000, COLOR_ERROR);
				CloseVisitShop();
			}
		}
		// 2006-08-02 by dgwoo
		m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = 0;
	}

	g_pD3dApp->m_bRequestEnable = TRUE;			// ???? ?????? ????????
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(UID64_t itemUID)
/// \brief		?????? UID?? ?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VISIT_BAZAAR_ITEM * CINFCityBazaarVisit::FindItem(UID64_t itemUID)
{
	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while(it != m_vecVisitBazaarItem.end())
	{
		if(it->pItemInfo->UniqueNumber == itemUID)
		{
			return &*it;
		}

		it++;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(int nItemIndex)
/// \brief		?????? ?????? ???????? ?????? ????
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VISIT_BAZAAR_ITEM * CINFCityBazaarVisit::FindItem(int nItemIndex)
{
	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while(it != m_vecVisitBazaarItem.end())
	{
		if(it->nItemIndex == nItemIndex)
		{
			return &*it;
		}

		it++;
	}

	return NULL;
}

vector<vector<OPEN_BAZAAR_ITEM>::iterator> CINFCityBazaarOpen::getEraseIteratorsFromBazarItem(OPEN_BAZAAR_ITEM *openBazarItem)
{
	vector<OPEN_BAZAAR_ITEM>::iterator openbazar_iterator = this->m_vecOpenBazaarItem.begin();
	vector<vector<OPEN_BAZAAR_ITEM>::iterator> iterators;
	for (int i = 0; openbazar_iterator != this->m_vecOpenBazaarItem.end(); i++, openbazar_iterator++)
	{
		if (&this->m_vecOpenBazaarItem[i] == openBazarItem)
		{
			iterators.push_back(openbazar_iterator);
		}
	}

	return iterators;
}

vector<vector<VISIT_BAZAAR_ITEM>::iterator> CINFCityBazaarVisit::getEraseIteratorsFromBazarVisitItem(VISIT_BAZAAR_ITEM *visitBazarItem)
{
	vector<VISIT_BAZAAR_ITEM>::iterator visitbazar_iterator = this->m_vecVisitBazaarItem.begin();
	vector<vector<VISIT_BAZAAR_ITEM>::iterator> iterators;
	for (int i = 0; visitbazar_iterator != this->m_vecVisitBazaarItem.end(); i++, visitbazar_iterator++)
	{
		if (&this->m_vecVisitBazaarItem[i] == visitBazarItem)
		{
			iterators.push_back(visitbazar_iterator);
		}
	}

	return iterators;
}