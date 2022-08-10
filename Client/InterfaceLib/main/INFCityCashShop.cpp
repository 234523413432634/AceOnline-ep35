// CINFCityCashShop.cpp: implementation of the CINFCityCashShop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFCityCashShop.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "D3DHanFont.h"
#include "AtumDatabase.h"
#include "INFGameMain.h"
#include "INFIcon.h"
#include "ItemInfo.h"
#include "INFItemInfo.h"
#include "INFScrollBar.h"
#include "FieldWinSocket.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "Interface.h"
#include "INFCityBase.h"
#include "INFWindow.h"
#include "INFGameMain.h"
#include "Chat.h"
#include "dxutil.h"
#include "StoreData.h"
#include "INFInven.h"
#include "AtumSound.h"	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가

#define		CASHSHOP_RENDER_START_X				((int)(g_pD3dApp->GetBackBufferDesc().Width - 591 ) /2 )		// 상점 렌더링 시작위치	X
#define		CASHSHOP_RENDER_START_Y				((int)(g_pD3dApp->GetBackBufferDesc().Height/2) - 199)			// 상점 렌더링 시작위치	Y
#define		CASHSHOP_RENDER_TAB_X				(14+CASHSHOP_RENDER_START_X)			// 선택탭 렌더링 시작 위치
#define		CASHSHOP_RENDER_TAB_Y				(28+CASHSHOP_RENDER_START_Y)			// 선택탭 렌더링 시작 위치
#define		CASHSHOP_RENDER_BUY_BUTTON_X		(512+CASHSHOP_RENDER_START_X)		// 충전하기 시작 위치
#define		CASHSHOP_RENDER_BUY_BUTTON_Y		(357+CASHSHOP_RENDER_START_Y)		// 충전하기 시작 위치
#define		CASHSHOP_RENDER_BUY_BUTTON_W		68									// 버튼 사이즈
#define		CASHSHOP_RENDER_BUY_BUTTON_H		24									// 버튼 사이즈
#define		CASHSHOP_RENDER_CHARGE_BUTTON_X		(545+CASHSHOP_RENDER_START_X)		// 구입하기 시작 위치
#define		CASHSHOP_RENDER_CHARGE_BUTTON_Y		(299+CASHSHOP_RENDER_START_Y)		// 구입하기 시작 위치
#define		CASHSHOP_RENDER_CHARGE_BUTTON_W		90									// 버튼 사이즈
#define		CASHSHOP_RENDER_CHARGE_BUTTON_H		29									// 버튼 사이즈
// 2007-11-14 by dgwoo 선물하기 버튼.
#define		CASHSHOP_RENDER_GIFT_BUTTON_X		(545+CASHSHOP_RENDER_START_X)		// 선물하기 시작 위치
#define		CASHSHOP_RENDER_GIFT_BUTTON_Y		(329+CASHSHOP_RENDER_START_Y)		// 선물하기 시작 위치

// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
#define		CASHSHOP_RENDER_CHARGE_BTN_X		(643+CASHSHOP_RENDER_START_X)		// 선물하기 시작 위치
#define		CASHSHOP_RENDER_CHARGE_BTN_Y		(357+CASHSHOP_RENDER_START_Y)		// 선물하기 시작 위치
// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가

#define		CASHSHOP_RENDER_FONT_ICONINFO_X		(CASHSHOP_RENDER_START_X+124)		// 아이콘 정보 렌더링을 위한 시작 위치
#define		CASHSHOP_RENDER_FONT_ICONINFO_Y		(CASHSHOP_RENDER_START_Y+62)		// 아이콘 정보 렌더링을 위한 시작 위치
#define		CASHSHOP_RENDER_FONT_ICONINFO_GAB	64									// 아이템 정보 사이의 갭
#define		CASHSHOP_RENDER_SELECT_TAB_GAB		24									// 셀렉트 탭 사이의 갭

#define		CASHSHOP_RENDER_BIGICON_START_X		(CASHSHOP_RENDER_START_X+25)		// 캐쉬아이콘 시작 위치
#define		CASHSHOP_RENDER_BIGICON_START_Y		(CASHSHOP_RENDER_START_Y+55)		// 캐쉬아이콘 시작 위치
#define		CASHSHOP_RENDER_BIGICON_W			84									// 캐쉬 빅아이콘 W
#define		CASHSHOP_RENDER_BIGICON_H			64									// 캐쉬 빅아이콘 H

#define		CASHSHOP_RENDER_CITY_GAB			88		// 도시와 필드 상점사이의 갭
#define		CASHSHOP_RENDER_GAME_GAB			41		// 도시와 필드 상점사이의 갭
#define		CASHSHOP_FONT_LINE_HEIGHT			15		// 한 라인의 높이
#define		CASHSHOP_SIDE_WIDTH_ENGLISH			5.5		// 영문 글자 WIDTH
#define		CASHSHOP_SHOW_ICON_MAX				5		// 보여줄수 있는 최대 갯수

#define		CASHSHOP_BUTTON_STATE_NOM			0		// 버튼 상태
#define		CASHSHOP_BUTTON_STATE_OVE			1		// 버튼 상태
#define		CASHSHOP_BUTTON_STATE_PUH			2		// 버튼 상태
#define		CASHSHOP_BUTTON_STATE_DIS			3		// 버튼 상태

#define		CASHSHOP_SCROLL_START_X				(CASHSHOP_RENDER_START_X+441)
#define		CASHSHOP_SCROLL_START_Y				(CASHSHOP_RENDER_START_Y+62)
#define		CASHSHOP_SCROLL_LINE_LENGTH			297
#define		CASHSHOP_SCROLL_RECT_START_X		(CASHSHOP_RENDER_START_X+14)
#define		CASHSHOP_SCROLL_RECT_START_Y		(CASHSHOP_RENDER_START_X+41)
#define		CASHSHOP_SCROLL_RECT_W				(CASHSHOP_RENDER_START_X+440)//314)	// 2008-08-13 by dgwoo 사이즈 변경.
#define		CASHSHOP_SCROLL_RECT_H				(CASHSHOP_RENDER_START_X+339)

#define		CASHSHOP_ITEM_INFO_ICON_X			(CASHSHOP_RENDER_START_X+540)//416)		// 아이템 정보창에 아이콘 렌더링 포지션
#define		CASHSHOP_ITEM_INFO_ICON_Y			(CASHSHOP_RENDER_START_Y+49)		// 아이템 정보창에 아이콘 렌더링 포지션
#define		CASHSHOP_ITEM_INFO_NAME_X			(CASHSHOP_ITEM_INFO_ICON_X+42)		// 아이템 정보창에 아이템 이름 레더링 
#define		CASHSHOP_ITEM_INFO_NAME_Y			(CASHSHOP_ITEM_INFO_ICON_Y+62)		// 아이템 정보창에 아이템 이름 레더링(이름은 가운데 정렬)
#define		CASHSHOP_ITEM_INFO_X				(CASHSHOP_RENDER_START_X+361)		// 아이템 정보창에 아이템 이름 레더링 

#define		CASHSHOP_ITEM_SELECT_RECT_X			(CASHSHOP_RENDER_START_X+23)			// 아이템 선택 가능창 
#define		CASHSHOP_ITEM_SELECT_RECT_Y			(CASHSHOP_RENDER_START_Y+54)			// 아이템 선택 가능창 
#define		CASHSHOP_ITEM_SELECT_RECT_W			405
#define		CASHSHOP_ITEM_SELECT_RECT_H			64

#define		CASHSHOP_ITEM_TAB_X					(CASHSHOP_RENDER_TAB_X)
#define		CASHSHOP_ITEM_TAB_Y					(CASHSHOP_RENDER_TAB_Y)
#define		CASHSHOP_ITEM_TAB_W					80
#define		CASHSHOP_ITEM_TAB_H					14

#define		CASHSHOP_ITEM_CLOSE_X				(CASHSHOP_RENDER_START_X+700)
#define		CASHSHOP_ITEM_CLOSE_Y				(CASHSHOP_RENDER_START_Y+3)
#define		CASHSHOP_ITEM_CLOSE_BUTTON_W		16
#define		CASHSHOP_ITEM_CLOSE_BUTTON_H		16
#define		CASHSHOP_ITEM_SHOP_MOVE_H			19
#define		CASHSHOP_ITEM_SHOP_MOVE_W			591

#define		CASHSHOP_TIME_MORE_ITEM				0.5f
#define		CASH_SHOP_ITEM_INFO_DES				8

#define		CASH_SHOP_GEAR_ROTATION_KEY_X		475//342			// 2008-10-28 by dgwoo 캐쉬상점 인터페이스 변경.
#define		CASH_SHOP_GEAR_ROTATION_KEY_Y		254

// 2008-10-28 by bhsohn 캐쉬 상점 구조 변경
// Mirror 위치
#define		CASH_SHOP_GEAR_UNIT_X			495
#define		CASH_SHOP_GEAR_UNIT_Y			94
// end 2008-10-28 by bhsohn 캐쉬 상점 구조 변경

#define ROTATION_NONE			-1
#define ROTATION_LEFT			0
#define ROTATION_RIGHT			1
#define ROTATION_UP				2
#define ROTATION_DOWN			3
#define ROTATION_ORIGINAL		4

#define ROTATION_STATE_N		-1		// 보통
#define ROTATION_STATE_O		0		// 오버
#define ROTATION_STATE_P		1		// 눌림

#define SOURCEINDEXTOITEMNUM(i,j)	(((i/100)*100)+j)

//#define		CASHSHOP_ITEM_PREMIUM_CARD			0
//#define		CASHSHOP_ITEM_OPTION_ITEM			1
//#define		CASHSHOP_ITEM_CARD_ITEM				2
//#define		CASHSHOP_ITEM_ACCESSORY_ITEM		3
//#define		CASHSHOP_ITEM_SKIN_ITEM				4							// 2007-08-07 by dgwoo 스킨 탭 추가.
//#define		CASHSHOP_ITEM_PACKAGE				5							// 2008-10-20 by dgwoo 패키지 탭 추가


// 2006-06-07 by ispark
#ifdef LANGUAGE_ENGLISH
	#define		STRING_CULL ::StringCullingUserData_ToBlank
	#define		CASHSHOP_ITEM_DESC_MAX				175

	#define		CASHSHOP_TEX						1.0f
	#define		CASHSHOP_RENDER_MYCASH_X			(CASHSHOP_RENDER_START_X + 525)		// 내캐쉬 렌더링 포지션
	#define		CASHSHOP_RENDER_MYCASH_Y			(CASHSHOP_RENDER_BUY_BUTTON_Y+4)		// 내캐쉬 렌더링 포지션(기본 12DIGIT)
#endif


#ifdef LANGUAGE_VIETNAM
	#define		STRING_CULL ::StringCullingUserData_ToBlank
	#define		CASHSHOP_ITEM_DESC_MAX				175

	#define		CASHSHOP_TEX						1.0f
	#define		CASHSHOP_RENDER_MYCASH_X			(CASHSHOP_RENDER_START_X + 545)//525)		// 내캐쉬 렌더링 포지션
	#define		CASHSHOP_RENDER_MYCASH_Y			(CASHSHOP_RENDER_BUY_BUTTON_Y+4)		// 내캐쉬 렌더링 포지션(기본 12DIGIT)
#endif


#ifdef KOR_CASHSHOP_INTERFACE_HSSON
	#define		STRING_CULL ::StringCullingUserDataEx
	#define		CASHSHOP_ITEM_DESC_MAX				175//28

	#define		CASHSHOP_TEX						1.0f
	#define		CASHSHOP_RENDER_MYCASH_X			(CASHSHOP_RENDER_START_X + 525)		// 내캐쉬 렌더링 포지션
	#define		CASHSHOP_RENDER_MYCASH_Y			(CASHSHOP_RENDER_BUY_BUTTON_Y+4)		// 내캐쉬 렌더링 포지션(기본 12DIGIT)
#endif

// 2008-12-04 by bhsohn Japan Working
#ifdef LANGUAGE_JAPAN
	#define		STRING_CULL ::StringCullingUserDataEx
	#define		CASHSHOP_ITEM_DESC_MAX				175//28

	#define		CASHSHOP_TEX						1.0f
	#define		CASHSHOP_RENDER_MYCASH_X			(CASHSHOP_RENDER_START_X + 525)		// 내캐쉬 렌더링 포지션
	#define		CASHSHOP_RENDER_MYCASH_Y			(CASHSHOP_RENDER_BUY_BUTTON_Y+4)		// 내캐쉬 렌더링 포지션(기본 12DIGIT)
#endif
// end 2008-12-04 by bhsohn Japan Working


#ifdef LANGUAGE_CHINA
	#define		STRING_CULL ::StringCullingUserDataEx
	#define		CASHSHOP_ITEM_DESC_MAX				175//28

	#define		CASHSHOP_TEX						1.0f
	#define		CASHSHOP_RENDER_MYCASH_X			(CASHSHOP_RENDER_START_X + 525)		// 내캐쉬 렌더링 포지션
	#define		CASHSHOP_RENDER_MYCASH_Y			(CASHSHOP_RENDER_BUY_BUTTON_Y+4)		// 내캐쉬 렌더링 포지션(기본 12DIGIT)
#endif


// 2008-04-30 by bhsohn 태국 버전 추가
#ifdef LANGUAGE_THAI
	#define		STRING_CULL ::StringCullingUserData_ToBlank
	#define		CASHSHOP_ITEM_DESC_MAX				175

	#define		CASHSHOP_TEX						1.0f
	#define		CASHSHOP_RENDER_MYCASH_X			(CASHSHOP_RENDER_START_X + 525)		// 내캐쉬 렌더링 포지션
	#define		CASHSHOP_RENDER_MYCASH_Y			(CASHSHOP_RENDER_BUY_BUTTON_Y+4)		// 내캐쉬 렌더링 포지션(기본 12DIGIT)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityCashShop::CINFCityCashShop(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	FLOG( "CINFCityCashShop(CAtumNode* pParent, BUILDINGNPC* pBuilding)" );
	m_pParent = pParent;	// CGameMain*
	m_pBuildingInfo = pBuilding;
	
	m_pImgBack		= NULL;
	m_pImgSelectItem = NULL;
	int i;
	for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
		m_pImgTab[i] = NULL;
	for(i=0; i<CASH_SHOP_BUTTON_STATE_ALL;i++)
	{
		m_pImgChargeButton[i] = NULL;
		m_pImgBuyButton[i] = NULL;
	}

	for(i=0; i<CASH_SHOP_ITEM_FONT;i++)
	{
		m_pFontItem[i] = NULL;
	}
	for(i=0; i<CASH_SHOP_ITEM_INFO;i++)
	{
		m_pFontItemInfo[i] = NULL;
	}
	m_bInputItemDone = FALSE;
	m_nCurrentSelectTab	= 0;
	m_nCurrentMouseStateCharge		= CASHSHOP_BUTTON_STATE_NOM;
	m_bCurrentMouseStateCharge		= FALSE;
	m_nCurrentMouseStateBuy			= CASHSHOP_BUTTON_STATE_NOM;
	m_nGiftButtonState				= BUTTON_STATE_NORMAL;
	m_bCurrentMouseStateBuy			= FALSE;
	m_nItemSelect					= 0;
	for(i=0;i<MAX_CASH_SHOP_TAB;i++)
		m_vecImgCashIcon[i].clear();
	for(i=0;i<INVEN_ROTATION_STATE;i++)
	{
		for(int j=0;j<INVEN_ROTATION_NUM;j++)
		{
			m_pDirection[i][j] = NULL;
		}
	}
	m_pRotationBase = NULL;

	m_pScroll = NULL;
	m_nMyCashPoint = 0;
	m_nGiftCardPoint = 0;
	
	m_bItemBuySend = FALSE;
	m_bMoveShop	= FALSE;
	m_nShopOldPosX = 0;
	m_nShopOldPosY = 0;
	m_nShopMovePosX = 0;
	m_nShopMovePosY = 0;
	for(i=0; i<4; i++)
		m_pImgMoreItem[i] = NULL;
	m_fTimeMoreIcon = CASHSHOP_TIME_MORE_ITEM;
	m_bMoreItemRenderFlag = TRUE;
	m_pImgGiftButton = NULL;		  
	m_nGiveTargetCharacterUID = 0;
	m_nButtonState = ROTATION_STATE_N;
	m_nRotationState = ROTATION_NONE;
	
	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
	m_pImgChargeBtn = NULL;	
	m_pImgChargeCloseBtn = NULL;
	m_pWebChargeBk = NULL;
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가

	// 2008-10-28 by bhsohn 캐쉬 상점 구조 변경
	for(i=0;i< CASH_SHOP_VIEW_TAB;i++)
	{
		m_nShopTapEndPosX[i] = -1;
	}

	// 2006-06-08 by ispark, 탭 위치가 조금씩 다르므로 다르게 처리
// #ifdef LANGUAGE_ENGLISH
// 	m_nShopTapEndPosX[0] = 91;
// 	m_nShopTapEndPosX[1] = 168;
// 	m_nShopTapEndPosX[2] = 245;
// 	m_nShopTapEndPosX[3] = 322;
// 
// #endif
// #ifdef LANGUAGE_VIETNAM
// 	m_nShopTapEndPosX[0] = 91;
// 	m_nShopTapEndPosX[1] = 168;
// 	m_nShopTapEndPosX[2] = 245;
// 	m_nShopTapEndPosX[3] = 322;
// 	m_nShopTapEndPosX[4] = 399;
// 
// #endif
// #ifdef LANGUAGE_KOREA
// 	m_nShopTapEndPosX[0] = 91;
// 	m_nShopTapEndPosX[1] = 168;
// 	m_nShopTapEndPosX[2] = 245;
// 	m_nShopTapEndPosX[3] = 310;
// 	m_nShopTapEndPosX[4] = 310;
// 	m_nShopTapEndPosX[5] = 380;			// 2008-10-20 by dgwoo 패키지 탭 추가
// 
// #endif
// 	// 2009-01-12 by bhsohn 신규 캐쉬샵 작업
// 	// 2008-12-04 by bhsohn Japan Working
// #ifdef LANGUAGE_JAPAN
// // 	m_nShopTapEndPosX[0] = 91;
// // 	m_nShopTapEndPosX[1] = 168;
// // 	m_nShopTapEndPosX[2] = 245;
// // 	m_nShopTapEndPosX[3] = 310;
// // 	m_nShopTapEndPosX[4] = 310;
// // 	m_nShopTapEndPosX[5] = 380;			// 2008-10-20 by dgwoo 패키지 탭 추가
// 	m_nShopTapEndPosX[CASHSHOP_ITEM_RECOMMAND] = 91;
// 	m_nShopTapEndPosX[CASHSHOP_ITEM_LUCKY_MECHINE] = 168;
// 	m_nShopTapEndPosX[CASHSHOP_ITEM_OPTION_ITEM] = 245;
// 	m_nShopTapEndPosX[CASHSHOP_ITEM_CARD_ITEM] = 310;
// 	m_nShopTapEndPosX[CASHSHOP_ITEM_ACCESSORY_ITEM] = 380;
// 	m_nShopTapEndPosX[CASHSHOP_ITEM_PACKAGE] = 450;			// 패키지 탭 추가
// #endif
// 	// end 2008-12-04 by bhsohn Japan Working
// 	// end 2009-01-12 by bhsohn 신규 캐쉬샵 작업
// 
// #ifdef LANGUAGE_CHINA
// //	m_nShopTapEndPosX[0] = 41;
// //	m_nShopTapEndPosX[1] = 106;
// //	m_nShopTapEndPosX[2] = 173;
// //	m_nShopTapEndPosX[3] = 244;
// 	m_nShopTapEndPosX[0] = 91;
// 	m_nShopTapEndPosX[1] = 168;
// 	m_nShopTapEndPosX[2] = 245;
// 	m_nShopTapEndPosX[3] = 322;
// 
// #endif
// 	// 2008-04-30 by bhsohn 태국 버전 추가
// #ifdef LANGUAGE_THAI
// //	m_nShopTapEndPosX[0] = 78;
// //	m_nShopTapEndPosX[1] = 130;
// //	m_nShopTapEndPosX[2] = 167;
// //	m_nShopTapEndPosX[3] = 233;	
// 	m_nShopTapEndPosX[0] = 91;
// 	m_nShopTapEndPosX[1] = 168;
// 	m_nShopTapEndPosX[2] = 245;
// 	m_nShopTapEndPosX[3] = 322;
// 
// #endif
	// end 2008-04-30 by bhsohn 태국 버전 추가

	// 2009-01-28 by bhsohn 캐쉬샵 처리
	int nPosX = 91;	
	for(i=0;i< CASH_SHOP_VIEW_TAB;i++)
	{
		m_nShopTapEndPosX[i] = nPosX;
		nPosX += 75;
	}
	for(i=0;i< CASH_SHOP_VIEW_TAB;i++)
	{
		m_nTabToItemIdx[i] = -1;		
	}	
	m_nSkinItemIdx = -2;

	for(i=0;i< MAX_NEW_CASHSHOP_IMAGE;i++)
	{
		m_pImgNewTab[i] = NULL;
	}
	m_nNewPlayIndex = 0;
	m_fNewPlayTime = 1.0f;
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	m_pSoldOut_Item			= NULL;
	m_pSoldOut_ToolTip		= NULL;
	for( i=0; i<2; ++i )
		m_pLimitedEdtion[ i ]	= NULL;

	m_bBling			= TRUE;
	m_nBlingStartTime	= 0;
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
}

CINFCityCashShop::~CINFCityCashShop()
{
	FLOG( "~CINFCityCashShop()" );
	int i;
	SAFE_DELETE(m_pImgBack);
	SAFE_DELETE(m_pImgSelectItem);
	for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
		SAFE_DELETE(m_pImgTab[i]);
	for(i=0; i<CASH_SHOP_BUTTON_STATE_ALL;i++)
	{
		SAFE_DELETE(m_pImgChargeButton[i]);
		SAFE_DELETE(m_pImgBuyButton[i]);
	}

	for(i=0; i<CASH_SHOP_ITEM_FONT;i++)
	{
		SAFE_DELETE(m_pFontItem[i]);
	}	
	for(i=0; i<CASH_SHOP_ITEM_INFO;i++)
	{
		SAFE_DELETE(m_pFontItemInfo[i]);
	}
	SAFE_DELETE(m_pImgGiftButton);
	
	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
	SAFE_DELETE(m_pImgChargeBtn);	
	SAFE_DELETE(m_pImgChargeCloseBtn);
	SAFE_DELETE(m_pWebChargeBk);
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가

	for(i=0;i<MAX_CASH_SHOP_TAB;i++)
	{
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[i].begin();
		while(it != m_vecItemInfo[i].end())
		{
			SHOP_ITEM* pItem = *it;
			delete pItem;
			pItem = NULL;
			it++;
		}
		m_vecItemInfo[i].clear();

		vector<CashItemIcon>::iterator itImg = m_vecImgCashIcon[i].begin();
		while(itImg != m_vecImgCashIcon[i].end())
		{
			// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
			SAFE_DELETE(itImg->pDataHeader);

			SAFE_DELETE((CINFImage*)itImg->vecImgCashIcon);
			itImg++;
		}
		m_vecImgCashIcon[i].clear();
		SAFE_DELETE(m_pScroll);
	}
	for(i=0;i<INVEN_ROTATION_STATE;i++)
	{
		for(int j=0;j<INVEN_ROTATION_NUM;j++)
		{
			SAFE_DELETE(m_pDirection[i][j]);
		}
	}
	SAFE_DELETE(m_pRotationBase);

	for(i=0; i<4; i++)
		SAFE_DELETE(m_pImgMoreItem[i]);

	// 2009-01-28 by bhsohn 캐쉬샵 처리
	for(i=0;i< MAX_NEW_CASHSHOP_IMAGE;i++)
	{
		SAFE_DELETE(m_pImgNewTab[i]);
	}
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	SAFE_DELETE( m_pSoldOut_Item );
	SAFE_DELETE( m_pSoldOut_ToolTip );
	for( i=0; i<2; ++i )
		SAFE_DELETE( m_pLimitedEdtion[ i ] );
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
}

void CINFCityCashShop::InitData()
{
	m_bInputItemDone = FALSE;
	// 2007-11-15 by dgwoo 캐쉬샾을 처음 열었을 경우 멤버쉽 탭이기때문에 비활성화 시켜준다.
	if(m_pImgGiftButton)
	{
		m_pImgGiftButton->EnableBtn(FALSE);
	}
	
	for(int i=0;i<MAX_CASH_SHOP_TAB;i++)
	{
		vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[i].begin();
		while(it != m_vecItemInfo[i].end())
		{
			SHOP_ITEM* pItem = *it;
			delete pItem;
			pItem = NULL;
			it++;
		}
		m_vecItemInfo[i].clear();

		vector<CashItemIcon>::iterator itImg = m_vecImgCashIcon[i].begin();
		while(itImg != m_vecImgCashIcon[i].end())
		{
			// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
			SAFE_DELETE(itImg->pDataHeader);

			if((CINFImage*)itImg->vecImgCashIcon != NULL)
			{
				SAFE_DELETE((CINFImage*)itImg->vecImgCashIcon);
			}
			itImg++;
		}
		m_vecImgCashIcon[i].clear();
	}	

	// 2009-03-02 by bhsohn 캐쉬샵 버그 수정
	g_pGameMain->m_bBuyMessage		= FALSE;
	// end 2009-03-02 by bhsohn 캐쉬샵 버그 수정

}

void CINFCityCashShop::InputItemDone()
{
//	CashItemSort();								// 2006-10-20 by ispark, 정렬 취소
//	m_bInputItemDone = TRUE;					// 2007-10-05 by dgwoo 아머가 바뀔때마다 리스트를 재요청한다.
	g_pD3dApp->m_bRequestEnable = TRUE;			// 2006-07-07 by ispark, 메세지 응답 완료
}

int CINFCityCashShop::InputItem(char* pMsg)
{
	FLOG( "CINFCityCashShop::InputItem(char* pMsg)" );
	
	if(pMsg)
	{
		ITEM *item = g_pDatabase->GetServerItemInfo(((SHOP_ITEM*)pMsg)->ItemNum);

		// 2009-01-28 by bhsohn 캐쉬샵 처리
		SHOP_ITEM* pShopItem = ((SHOP_ITEM*)pMsg);
		BYTE byCashIndex = GET_TABINDEX_BY_CASHSHOPINDEX(pShopItem->CashShopIndex);
		BYTE byReNewIndex = GET_CASHSHOP_BIT_BY_CASHSHOPINDEX(pShopItem->CashShopIndex);
		
		// 일반 탭
		if(item 
			&& (byCashIndex >= 0)
			&& (byCashIndex < (MAX_CASH_SHOP_TAB-1)))
		{
			SHOP_ITEM* pItem = new SHOP_ITEM;			
 			
			memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
			if(FindCashShopData(byCashIndex, pItem->ItemNum) == NULL)
			{				
				CashItemIcon pTemp;			
				m_vecItemInfo[byCashIndex].push_back(pItem);
				
				pTemp.nItemNum = pItem->ItemNum;				
				pTemp.pDataHeader = NULL;
				pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);					
				
				m_vecImgCashIcon[byCashIndex].push_back(pTemp);
			}	
			else
			{
				// 어떠한 거에도 추가하지 않은 아이템이다.
				SAFE_DELETE(pItem);
			}			
		}

		// 추천 탭
		if(item && (IS_RECOMMEND_CASHSHOPITEM_BY_CASHSHOPINDEX(byReNewIndex)))
		{	
			// 0 번은 추천탭CASH_ITEMKIND_RECOMMEND_ITEM
			SHOP_ITEM* pRecommandItem = new SHOP_ITEM;						
			
			memcpy(pRecommandItem, pMsg, sizeof(SHOP_ITEM));
			if(FindCashShopData(CASH_ITEMKIND_RECOMMEND_ITEM, pRecommandItem->ItemNum) == NULL)
			{				
				CashItemIcon pTemp;			
				m_vecItemInfo[CASH_ITEMKIND_RECOMMEND_ITEM].push_back(pRecommandItem);
				
				pTemp.nItemNum = pRecommandItem->ItemNum;				
				pTemp.pDataHeader = NULL;
				pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);					
				
				m_vecImgCashIcon[CASH_ITEMKIND_RECOMMEND_ITEM].push_back(pTemp);
			}	
			else
			{
				// 어떠한 거에도 추가하지 않은 아이템이다.
				SAFE_DELETE(pRecommandItem);
			}			
		}
//		if(item)
// 		{
// 			// 2006-01-11 by ispark, 같은 정보가 있는지 확인
// 			// 렉에 의해서 중복 입력이 되는 현상이 있다. 그래서 같은 정보가 있으면 넘어감
// 
// 			SHOP_ITEM* pItem = new SHOP_ITEM;
// 			CashItemIcon pTemp;
// 
// // 2006-06-08 by ispark, Sharging에서 SummonMonster로 변경
// //			if(item->Charging == CASH_ITEMKIND_PREMIUM_CARD)
// 			if(item->SummonMonster == CASH_ITEMKIND_PREMIUM_CARD)
// 			{
// 				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
// 				if(FindCashShopData(CASHSHOP_ITEM_PREMIUM_CARD, pItem) == NULL)
// 				{
// 					m_vecItemInfo[CASHSHOP_ITEM_PREMIUM_CARD].push_back(pItem);
// 				
// 					pTemp.nItemNum = pItem->ItemNum;
// //					pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(pItem->ItemNum);	// 2005-08-23 by ispark
// 
// 					// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
// 					//pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(item->SourceIndex);
// 					pTemp.pDataHeader = NULL;
// 					pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);					
// 					
// 					m_vecImgCashIcon[CASHSHOP_ITEM_PREMIUM_CARD].push_back(pTemp);
// 				}
// 			}
// 			else if(item->SummonMonster == CASH_ITEMKIND_OPTION_ITEM)
// 			{
// 				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
// 				if(FindCashShopData(CASHSHOP_ITEM_OPTION_ITEM, pItem) == NULL)
// 				{
// 					m_vecItemInfo[CASHSHOP_ITEM_OPTION_ITEM].push_back(pItem);
// 
// 					pTemp.nItemNum = pItem->ItemNum;
// //					pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(pItem->ItemNum);	// 2005-08-23 by ispark
// 
// 					// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
// 					//pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(item->SourceIndex);
// 					pTemp.pDataHeader = NULL;
// 					pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);
// 
// 					m_vecImgCashIcon[CASHSHOP_ITEM_OPTION_ITEM].push_back(pTemp);
// 				}
// 			}
// 			else if(item->SummonMonster == CASH_ITEMKIND_CARD_ITEM)
// 			{
// 				//CASH_ITEMKIND_WASTEFUL_ITEM
// 				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
// 				if(FindCashShopData(CASHSHOP_ITEM_CARD_ITEM, pItem) == NULL)
// 				{
// 					m_vecItemInfo[CASHSHOP_ITEM_CARD_ITEM].push_back(pItem);
// 
// 					pTemp.nItemNum = pItem->ItemNum;
// //						pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(pItem->ItemNum);	// 2005-08-23 by ispark
// 
// 					// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
// 					//pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(item->SourceIndex);
// 					pTemp.pDataHeader = NULL;
// 					pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);
// 
// 					m_vecImgCashIcon[CASHSHOP_ITEM_CARD_ITEM].push_back(pTemp);
// 				}
// 			}
// 			else if(item->SummonMonster == CASH_ITEMKIND_ACCESSORY_ITEM)
// 			{
// 				memcpy(pItem, pMsg, sizeof(SHOP_ITEM));
// 				if(FindCashShopData(CASHSHOP_ITEM_ACCESSORY_ITEM, pItem) == NULL)
// 				{
// 					m_vecItemInfo[CASHSHOP_ITEM_ACCESSORY_ITEM].push_back(pItem);
// 
// 					pTemp.nItemNum = pItem->ItemNum;
// //					pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(pItem->ItemNum);	// 2005-08-23 by ispark
// 
// 					// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
// 					//pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(item->SourceIndex);
// 					pTemp.pDataHeader = NULL;
// 					pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);
// 
// 					m_vecImgCashIcon[CASHSHOP_ITEM_ACCESSORY_ITEM].push_back(pTemp);
// 				}
// 			}
// 			// 2008-10-20 by dgwoo 패키지 탭 추가
// 			else if(item->SummonMonster == CASH_ITEMKIND_PACKAGE_ITEM)
// 			{
// 				memcpy(pItem,pMsg,sizeof(SHOP_ITEM));
// 				if(FindCashShopData(CASHSHOP_ITEM_PACKAGE, pItem) == NULL)
// 				{
// 					m_vecItemInfo[CASHSHOP_ITEM_PACKAGE].push_back(pItem);
// 					pTemp.nItemNum = pItem->ItemNum;
// 					// 2008-10-28 by bhsohn 캐쉬 상점 구조 변경
// 					// 초기화 안하면 오류가 난다.
// 					pTemp.pDataHeader = NULL;	
// 					pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(item->SourceIndex);
// 					m_vecImgCashIcon[CASHSHOP_ITEM_PACKAGE].push_back(pTemp);
// 				}
// 			}
// 			// 2008-10-20 by dgwoo 패키지 탭 추가
// 		}
		// end 2009-01-28 by bhsohn 캐쉬샵 처리
	}
	
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	//m_pScroll->SetNumberOfData( m_vecImgCashIcon[CASH_ITEMKIND_PREMIUM_CARD].size() );	
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	return sizeof(SHOP_ITEM);
}

HRESULT CINFCityCashShop::InitDeviceObjects()
{
	FLOG( "CINFCityCashShop::InitDeviceObjects(char* pData, int nSize)" );
	int i;
	DataHeader	* pDataHeader ;
	char buf[32];
	memset(buf, 0x00, 32);
	wsprintf( buf, "ca_bas");
	
	m_pImgBack = new CINFImage;
	pDataHeader = FindResource(buf);
	m_pImgBack->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	wsprintf( buf, "casel");
	m_pImgSelectItem = new CINFImage;
	pDataHeader = FindResource(buf);
	m_pImgSelectItem->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	
	for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
	{
		// 2009-01-12 by bhsohn 신규 캐쉬샵 작업
		if(m_nShopTapEndPosX[i] < 0)
		{
			continue;
		}
		// end 2009-01-12 by bhsohn 신규 캐쉬샵 작업

		memset(buf, 0x00, 32);

		
		// 2009. 06. 08 by ckPark 캐쉬샵 신형 UI(럭키머신)로 변경

// 		wsprintf( buf, "ca_ad%d",i);
// 		// 2009-01-12 by bhsohn 신규 캐쉬샵 작업		
// 		#ifdef LANGUAGE_JAPAN
// 			wsprintf( buf, "ca1_ad%d",i);
// 		#endif
// 		// end 2009-01-12 by bhsohn 신규 캐쉬샵 작업		

		wsprintf( buf, "ca1_ad%d",i);

		// end 2009. 06. 08 by ckPark 캐쉬샵 신형 UI(럭키머신)로 변경


		pDataHeader = FindResource(buf);
		if(pDataHeader)
		{
			m_pImgTab[i] = new CINFImage;
			m_pImgTab[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;		
		}
	}
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	// end 2009-01-28 by bhsohn 캐쉬샵 처리
	for(i=0;i<INVEN_ROTATION_STATE;i++)
	{
		for(int j=0;j<INVEN_ROTATION_NUM;j++)
		{
			
			ZERO_MEMORY(buf);
			wsprintf(buf, "inven%d%d", i, j);

			m_pDirection[i][j] = new CINFImage;
			pDataHeader = FindResource(buf);
			m_pDirection[i][j]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
		}
	}
	wsprintf(buf,"innom");
	m_pRotationBase = new CINFImage;
	pDataHeader = FindResource(buf);
	m_pRotationBase->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);


	for(i=0; i<CASH_SHOP_BUTTON_STATE_ALL;i++)
	{
		memset(buf, 0x00, 32);
		wsprintf( buf, "canob%d",i);
		m_pImgChargeButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgChargeButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	

		memset(buf, 0x00, 32);
		wsprintf( buf, "cachb%d",i);
		m_pImgBuyButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgBuyButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	
	}

	// 2009-01-12 by bhsohn 신규 캐쉬샵 작업
//#ifdef LANGUAGE_KOREA
#if defined(NEW_CASHSHOP_INTERFACE_HSSON) || defined(LANGUAGE_JAPAN)
	wsprintf(buf,"cagift");
	if(NULL == m_pImgGiftButton)
	{
		m_pImgGiftButton = new CINFImageBtn;
	}
	if(S_FALSE == m_pImgGiftButton->InitDeviceObjects(buf))
	{
		m_pImgGiftButton->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgGiftButton);
	}
	#ifdef YEDANG_RELEASE
//		if(m_pImgGiftButton && (FALSE == g_pD3dApp->IsTestServerDefine()))
//		{		
//			// 선물하기 숨기기
//			m_pImgGiftButton->ShowWindow(FALSE);
//		}
		
	#endif
#endif	
	// end 2009-01-12 by bhsohn 신규 캐쉬샵 작업

	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
	{
		BOOL bUseCashShop = FALSE;
#if defined(KOR_CASHSHOP_REFILL_WEB_HSSON) || defined(LANGUAGE_JAPAN)
		#ifndef YEDANG_RELEASE
			bUseCashShop = TRUE;
		#endif		
#endif
		if(bUseCashShop)
		{
			if(NULL == m_pImgChargeBtn)
			{
				wsprintf(buf,"cachg");
				
				m_pImgChargeBtn = new CINFImageBtn;			
				if(S_FALSE == m_pImgChargeBtn->InitDeviceObjects(buf))
				{
					m_pImgChargeBtn->DeleteDeviceObjects();
					SAFE_DELETE(m_pImgChargeBtn);
				}
			}		
			if(NULL == m_pImgChargeCloseBtn)
			{
				char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
				wsprintf(szUpBtn, "xclose");
				wsprintf(szDownBtn, "xclose");
				wsprintf(szSelBtn, "xclose");
				wsprintf(szDisBtn, "xclose");
				
				m_pImgChargeCloseBtn = new CINFImageBtn;			
				m_pImgChargeCloseBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		

				m_pImgChargeCloseBtn->ShowWindow(FALSE);	// 처음엔 숨기자
			}		
			
			if(NULL == m_pWebChargeBk)
			{
				char chWebPagebuf[32];
				memset(chWebPagebuf, 0x00, 32);
				wsprintf( chWebPagebuf, "cabk");
				
				DataHeader	* pWebDataHeader  = FindResource(chWebPagebuf);
				if(pWebDataHeader)
				{
					m_pWebChargeBk = new CINFImage;			
					m_pWebChargeBk->InitDeviceObjects(pWebDataHeader->m_pData, pWebDataHeader->m_DataSize) ;
				}
				
			}
		}
	}
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가

	for(i=0; i<4; i++)
	{
		memset(buf, 0x00, 32);
		wsprintf( buf, "more_s%d",i);
		m_pImgMoreItem[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgMoreItem[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	
	}
	
	for(i=0; i<CASH_SHOP_ITEM_FONT;i++)
	{
		// 2007-10-16 by bhsohn 케쉬샵 아이템 이름은 볼드로 함.
		//m_pFontItem[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,256,32);		
		if(0 == i%3)
		{
			m_pFontItem[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE|D3DFONT_BOLD,  TRUE,512,32);		// 2008-10-22 by dgwoo 256 ->512 로 변경
		}
		else
		{
			m_pFontItem[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);		// 2008-10-22 by dgwoo 256 ->512 로 변경
		}		
		m_pFontItem[i]->InitDeviceObjects(g_pD3dDev) ;
	}
	for(i=0; i<CASH_SHOP_ITEM_INFO;i++)
	{
		// 2007-10-16 by bhsohn 케쉬샵 아이템 이름은 볼드로 함.
		//m_pFontItemInfo[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,256,32);
		if(0 == i)
		{
			m_pFontItemInfo[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE|D3DFONT_BOLD,  TRUE,512,32);		// 2008-10-22 by dgwoo 256 ->512 로 변경
		}
		else
		{
			m_pFontItemInfo[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);		// 2008-10-22 by dgwoo 256 ->512 로 변경
		}
		
		m_pFontItemInfo[i]->InitDeviceObjects(g_pD3dDev) ;
	}
	m_pScroll = new CINFScrollBar(this,
								CASHSHOP_SCROLL_START_X, 
								CASHSHOP_SCROLL_START_Y, 
								CASHSHOP_SCROLL_LINE_LENGTH,
								CASHSHOP_SHOW_ICON_MAX);
	m_pScroll->SetGameData( m_pGameData );
	m_pScroll->InitDeviceObjects();
	m_pScroll->SetWheelRect(CASHSHOP_SCROLL_RECT_START_X, 
							CASHSHOP_SCROLL_RECT_START_Y,
							CASHSHOP_SCROLL_RECT_W,
							CASHSHOP_SCROLL_RECT_H);

	// 2009-01-28 by bhsohn 캐쉬샵 처리
	for(i=0;i< MAX_NEW_CASHSHOP_IMAGE;i++)
	{
		memset(buf, 0x00, 32);
		wsprintf( buf, "ca_n%d",i);
		pDataHeader = FindResource(buf);

		if(pDataHeader)
		{
			m_pImgNewTab[i] = new CINFImage;		
			m_pImgNewTab[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	
		}
	}
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	m_pSoldOut_Item		= new CINFImage;
	pDataHeader = FindResource( "soldouts" );
	m_pSoldOut_Item->InitDeviceObjects( pDataHeader->m_pData,pDataHeader->m_DataSize );

	m_pSoldOut_ToolTip	= new CINFImage;
	pDataHeader = FindResource( "soldoutl" );
	m_pSoldOut_ToolTip->InitDeviceObjects( pDataHeader->m_pData,pDataHeader->m_DataSize );

	for( i=0; i<2; ++i )
	{
		m_pLimitedEdtion[ i ]	= new CINFImage;
		sprintf( buf, "limited%d", i );
		pDataHeader	= FindResource( buf );
		m_pLimitedEdtion[ i ]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	}
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

	return S_OK;
}

HRESULT CINFCityCashShop::RestoreDeviceObjects()
{
	FLOG( "CINFCityCashShop::RestoreDeviceObjects()" );
	int i;
	m_pImgBack->RestoreDeviceObjects();
	m_pImgSelectItem->RestoreDeviceObjects();
	for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
	{
		if(m_pImgTab[i])
		{
			m_pImgTab[i]->RestoreDeviceObjects();
		}
	}
	for(i=0;i<INVEN_ROTATION_STATE;i++)
	{
		for(int j=0;j<INVEN_ROTATION_NUM;j++)
		{
			m_pDirection[i][j]->RestoreDeviceObjects();
		}
	}
	m_pRotationBase->RestoreDeviceObjects();

	for(i=0; i<CASH_SHOP_BUTTON_STATE_ALL;i++)
	{
		m_pImgChargeButton[i]->RestoreDeviceObjects();
		m_pImgBuyButton[i]->RestoreDeviceObjects();
	}
	if(m_pImgGiftButton)
	{
		m_pImgGiftButton->RestoreDeviceObjects();
		m_pImgGiftButton->SetBtnPosition(CASHSHOP_RENDER_GIFT_BUTTON_X+m_nShopMovePosX,CASHSHOP_RENDER_GIFT_BUTTON_Y+m_nShopMovePosY);
	}
	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	if(m_pImgChargeBtn)
	{		
		m_pImgChargeBtn->RestoreDeviceObjects();
		m_pImgChargeBtn->SetBtnPosition(CASHSHOP_RENDER_CHARGE_BTN_X+m_nShopMovePosX,
			CASHSHOP_RENDER_CHARGE_BTN_Y+m_nShopMovePosY);
	}
	if(m_pImgChargeCloseBtn)
	{
		m_pImgChargeCloseBtn->RestoreDeviceObjects();		
	}
	if(m_pWebChargeBk)
	{
		m_pWebChargeBk->RestoreDeviceObjects();
	}
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	for(i=0; i<4; i++)
	{
		m_pImgMoreItem[i]->RestoreDeviceObjects();
	}
	
	for(i=0; i<CASH_SHOP_ITEM_FONT;i++)
	{
		m_pFontItem[i]->RestoreDeviceObjects();
	}
	for(i=0; i<CASH_SHOP_ITEM_INFO;i++)
	{
		m_pFontItemInfo[i]->RestoreDeviceObjects();
	}
	for(i=0; i<MAX_CASH_SHOP_TAB; i++)
	{
		vector<CashItemIcon>::iterator itImg = m_vecImgCashIcon[i].begin();
		while(itImg != m_vecImgCashIcon[i].end())
		{
			if(itImg->nItemNum > 0)
			{
				// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
				//itImg->vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(itImg->nItemNum);				
				if(itImg->vecImgCashIcon)
				{
					itImg->vecImgCashIcon->RestoreDeviceObjects();
				}
				// end 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
				
				//itImg->vecImgCashIcon->RestoreDeviceObjects();
			}
			itImg++;
		}
	}
	m_pScroll->RestoreDeviceObjects();
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	for(i=0;i< MAX_NEW_CASHSHOP_IMAGE;i++)
	{			
		if(m_pImgNewTab[i])
		{			 
			m_pImgNewTab[i]->RestoreDeviceObjects() ;	
		}
	}
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	m_pSoldOut_Item->RestoreDeviceObjects();
	m_pSoldOut_ToolTip->RestoreDeviceObjects();

	for( i=0; i<2; ++i )
		m_pLimitedEdtion[ i ]->RestoreDeviceObjects();
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

	return S_OK;
}

HRESULT CINFCityCashShop::InvalidateDeviceObjects()
{
	FLOG( "CINFCityCashShop::InvalidateDeviceObjects()" );

	m_pImgBack->InvalidateDeviceObjects();
	m_pImgSelectItem->InvalidateDeviceObjects();
	int i;
	for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
	{
		if(m_pImgTab[i])
		{
			m_pImgTab[i]->InvalidateDeviceObjects();
		}
	}
	for(i=0;i<INVEN_ROTATION_STATE;i++)
	{
		for(int j=0;j<INVEN_ROTATION_NUM;j++)
		{
			m_pDirection[i][j]->InvalidateDeviceObjects();
		}
	}
	m_pRotationBase->InvalidateDeviceObjects();

	for(i=0; i<CASH_SHOP_BUTTON_STATE_ALL;i++)
	{
		m_pImgChargeButton[i]->InvalidateDeviceObjects();
		m_pImgBuyButton[i]->InvalidateDeviceObjects();
	}
	if(m_pImgGiftButton)
	{
		m_pImgGiftButton->InvalidateDeviceObjects();
	}
	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	if(m_pImgChargeBtn)
	{
		m_pImgChargeBtn->InvalidateDeviceObjects();
	}
	if(m_pImgChargeCloseBtn)
	{
		m_pImgChargeCloseBtn->InvalidateDeviceObjects();
	}
	if(m_pWebChargeBk)
	{
		m_pWebChargeBk->InvalidateDeviceObjects();
	}
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	for(i=0; i<4; i++)
	{
		m_pImgMoreItem[i]->InvalidateDeviceObjects();
	}

	for(i=0; i<CASH_SHOP_ITEM_FONT;i++)
	{
		m_pFontItem[i]->InvalidateDeviceObjects();
	}
	for(i=0; i<CASH_SHOP_ITEM_INFO;i++)
	{
		m_pFontItemInfo[i]->InvalidateDeviceObjects();
	}
	for(i=0; i<MAX_CASH_SHOP_TAB; i++)
	{
		vector<CashItemIcon>::iterator itImg = m_vecImgCashIcon[i].begin();
		while(itImg != m_vecImgCashIcon[i].end())
		{
			if(itImg->nItemNum > 0)
			{
				if(itImg->vecImgCashIcon != NULL)
					itImg->vecImgCashIcon->InvalidateDeviceObjects();
			}
			itImg++;
		}
	}
	m_pScroll->InvalidateDeviceObjects();
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	for(i=0;i< MAX_NEW_CASHSHOP_IMAGE;i++)
	{			
		if(m_pImgNewTab[i])
		{			 
			m_pImgNewTab[i]->InvalidateDeviceObjects();	
		}
	}
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	m_pSoldOut_Item->InvalidateDeviceObjects();
	m_pSoldOut_ToolTip->InvalidateDeviceObjects();

	for( i=0; i<2; ++i )
		m_pLimitedEdtion[ i ]->InvalidateDeviceObjects();
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

	return S_OK;
}

HRESULT CINFCityCashShop::DeleteDeviceObjects()
{
	FLOG( "CINFCityCashShop::DeleteDeviceObjects()" );
	
	///////////////////////////////////////////////////////////////////
	m_pImgBack->DeleteDeviceObjects();
	m_pImgSelectItem->DeleteDeviceObjects();
	int i;
	for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
	{
		if(m_pImgTab[i])
		{
			m_pImgTab[i]->DeleteDeviceObjects();
		}
	}
	for(i=0;i<INVEN_ROTATION_STATE;i++)
	{
		for(int j=0;j<INVEN_ROTATION_NUM;j++)
		{
			m_pDirection[i][j]->DeleteDeviceObjects();
			SAFE_DELETE(m_pDirection[i][j]);
		}
	}
	m_pRotationBase->DeleteDeviceObjects();
	SAFE_DELETE(m_pRotationBase);

	for(i=0; i<CASH_SHOP_BUTTON_STATE_ALL;i++)
	{
		m_pImgChargeButton[i]->DeleteDeviceObjects();
		m_pImgBuyButton[i]->DeleteDeviceObjects();
	}
	if(m_pImgGiftButton)
	{
		m_pImgGiftButton->DeleteDeviceObjects();
	}
	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	if(m_pImgChargeBtn)
	{
		m_pImgChargeBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgChargeBtn);
	}
	if(m_pImgChargeCloseBtn)
	{
		m_pImgChargeCloseBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgChargeCloseBtn);
	}
	if(m_pWebChargeBk)
	{
		m_pWebChargeBk->DeleteDeviceObjects();
		SAFE_DELETE(m_pWebChargeBk);
	}
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	for(i=0; i<CASH_SHOP_ITEM_FONT;i++)
	{
		m_pFontItem[i]->DeleteDeviceObjects();
	}
	for(i=0; i<CASH_SHOP_ITEM_INFO;i++)
	{
		m_pFontItemInfo[i]->DeleteDeviceObjects();
	}
	for(i=0; i<MAX_CASH_SHOP_TAB; i++)
	{
		vector<CashItemIcon>::iterator itImg = m_vecImgCashIcon[i].begin();
		while(itImg != m_vecImgCashIcon[i].end())
		{
			// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
			SAFE_DELETE(itImg->pDataHeader);

			if((CINFImage*)itImg->vecImgCashIcon != NULL)
			{
				(CINFImage*)itImg->vecImgCashIcon->DeleteDeviceObjects();
				SAFE_DELETE((CINFImage*)itImg->vecImgCashIcon);
			}
			
			itImg++;
		}
		m_vecImgCashIcon[i].clear();
	}
	
	m_pScroll->DeleteDeviceObjects();	

	////////////////////////////////////////////////////////////////////
	SAFE_DELETE(m_pImgBack);
	SAFE_DELETE(m_pImgSelectItem);
	for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
		SAFE_DELETE(m_pImgTab[i]);
	for(i=0; i<CASH_SHOP_BUTTON_STATE_ALL;i++)
	{
		SAFE_DELETE(m_pImgChargeButton[i]);
		SAFE_DELETE(m_pImgBuyButton[i]);
	}
	
	for(i=0; i<CASH_SHOP_ITEM_FONT;i++)
	{
		SAFE_DELETE(m_pFontItem[i]);
	}
	for(i=0; i<CASH_SHOP_ITEM_INFO;i++)
	{
		SAFE_DELETE(m_pFontItemInfo[i]);
	}
	for(i=0;i<3;i++)
	{
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
	SAFE_DELETE(m_pScroll);
	for(i=0; i<4; i++)
	{
		m_pImgMoreItem[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMoreItem[i]);
	}
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	for(i=0;i< MAX_NEW_CASHSHOP_IMAGE;i++)
	{			
		if(m_pImgNewTab[i])
		{			 
			m_pImgNewTab[i]->DeleteDeviceObjects();	
			SAFE_DELETE(m_pImgNewTab[i]);
		}
	}
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	m_pSoldOut_Item->DeleteDeviceObjects();
	SAFE_DELETE( m_pSoldOut_Item );
	m_pSoldOut_ToolTip->DeleteDeviceObjects();
	SAFE_DELETE( m_pSoldOut_ToolTip );

	for( i=0; i<2; ++i )
	{
		m_pLimitedEdtion[ i ]->DeleteDeviceObjects();
		SAFE_DELETE( m_pLimitedEdtion[ i ] );
	}
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

	return S_OK;
}

void CINFCityCashShop::Render()
{
	FLOG( "CINFCityCashShop::Render()" );
	// 도시와 필드에서 렌더링 위치 수정
	if(m_fTimeMoreIcon > 0)
	{
		m_fTimeMoreIcon -= g_pD3dApp->GetElapsedTime();
	}
	if(m_fTimeMoreIcon < 0)
	{
		m_fTimeMoreIcon = CASHSHOP_TIME_MORE_ITEM;
		m_bMoreItemRenderFlag = !m_bMoreItemRenderFlag;
	}

	m_pItem = NULL;
	char buf[512];
	memset(buf, 0x00, 512);
	char buf2[512];
	memset(buf2, 0x00, 512);
	if(g_pD3dApp->m_dwGameState == _CITY)
	{
		// 도시상에서 렌더링 위치
		//nShopGap = CASHSHOP_RENDER_CITY_GAB;
	}
	else
	{
		// 필드상에서 렌더링 위치
		//nShopGap = CASHSHOP_RENDER_GAME_GAB;	
	}
	//m_nCityRenderGab = nShopGap;
	
	m_pScroll->SetScrollLinePos(	CASHSHOP_SCROLL_START_X+m_nShopMovePosX, 
		CASHSHOP_SCROLL_START_Y+m_nShopMovePosY);
	m_pScroll->SetWheelRect(CASHSHOP_SCROLL_RECT_START_X+m_nShopMovePosX, 
								CASHSHOP_SCROLL_RECT_START_Y+m_nShopMovePosY,
								CASHSHOP_SCROLL_RECT_W,
								CASHSHOP_SCROLL_RECT_H);
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	int nSelTab = GetTabToItemIdx(m_nCurrentSelectTab);
	if(nSelTab == -1)
	{
		m_nItemSelect = 0;
	}
	else if(nSelTab != -1 && m_vecImgCashIcon[nSelTab].size() <= (m_nItemSelect+m_pScroll->GetCurrentScrollIndex()))
	{
		m_nItemSelect = 0;
	}
	
	// 배경 화면 렌더링
	m_pImgBack->Move(CASHSHOP_RENDER_START_X+m_nShopMovePosX, CASHSHOP_RENDER_START_Y+m_nShopMovePosY);
	m_pImgBack->Render();
	
	// 탭렌더링
	// 2008-10-28 by bhsohn 캐쉬 상점 구조 변경
	if(m_pImgTab[m_nCurrentSelectTab])
	{
		m_pImgTab[m_nCurrentSelectTab]->Move(CASHSHOP_RENDER_TAB_X+m_nShopMovePosX,CASHSHOP_RENDER_TAB_Y+m_nShopMovePosY);
		m_pImgTab[m_nCurrentSelectTab]->Render();
	}

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
// 	// 셀렉트 탭 렌더링
// 	m_pImgSelectItem->Move(CASHSHOP_RENDER_TAB_X+m_nShopMovePosX+9,
// 		CASHSHOP_RENDER_TAB_Y+m_nShopMovePosY+CASHSHOP_RENDER_SELECT_TAB_GAB+(64*m_nItemSelect));
// 	m_pImgSelectItem->Render();
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

	// More 스크롤 렌더링
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	if(nSelTab != -1 && (m_vecImgCashIcon[nSelTab].size()-m_pScroll->GetCurrentScrollIndex())>CASHSHOP_SHOW_ICON_MAX-1)
	{
		m_pImgMoreItem[0]->Move(CASHSHOP_SCROLL_START_X+m_nShopMovePosX-4, CASHSHOP_SCROLL_START_Y+m_nShopMovePosY+298);
		m_pImgMoreItem[0]->Render();
		
		if(m_bMoreItemRenderFlag)
		{
			m_pImgMoreItem[3]->Move(CASHSHOP_SCROLL_START_X+m_nShopMovePosX-4, CASHSHOP_SCROLL_START_Y+m_nShopMovePosY+298);
			m_pImgMoreItem[3]->Render();
		}
	}
	if(m_pScroll->GetCurrentScrollIndex()>0)
	{
		m_pImgMoreItem[2]->Move(CASHSHOP_SCROLL_START_X+m_nShopMovePosX-4, CASHSHOP_SCROLL_START_Y+m_nShopMovePosY-12);
		m_pImgMoreItem[2]->Render();
		
		if(m_bMoreItemRenderFlag)
		{
			m_pImgMoreItem[1]->Move(CASHSHOP_SCROLL_START_X+m_nShopMovePosX-4, CASHSHOP_SCROLL_START_Y+m_nShopMovePosY-12);
			m_pImgMoreItem[1]->Render();
		}
	}
	
	// 아이콘 렌더링
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	//if(m_vecImgCashIcon[m_nCurrentSelectTab].size()>m_pScroll->GetCurrentScrollIndex())
	if(nSelTab != -1 && m_vecImgCashIcon[nSelTab].size()>m_pScroll->GetCurrentScrollIndex())
	{		
		int nCount = 0;
		int nItemCountNum = 1;
		vector<CashItemIcon>::iterator itCash = m_vecImgCashIcon[nSelTab].begin();
		while (itCash != m_vecImgCashIcon[nSelTab].end())
		{
			if(m_pScroll->GetCurrentScrollIndex()>=nItemCountNum)
			{
				itCash++;
				nItemCountNum++;
				continue;
			}

			if(nCount>CASHSHOP_SHOW_ICON_MAX-1)
				break;
			if(itCash->vecImgCashIcon != NULL)
			{
				itCash->vecImgCashIcon->Move(CASHSHOP_RENDER_BIGICON_START_X+m_nShopMovePosX,
				CASHSHOP_RENDER_BIGICON_START_Y+m_nShopMovePosY+(CASHSHOP_RENDER_BIGICON_H*nCount));
				itCash->vecImgCashIcon->Render();
				// 2009-01-28 by bhsohn 캐쉬샵 처리
				SHOP_ITEM* pShopInfo = FindCashShopData(nSelTab, itCash->nItemNum);
				if(pShopInfo)
				{
					RenderNewShopInfo(CASHSHOP_RENDER_BIGICON_START_X+m_nShopMovePosX, 
						CASHSHOP_RENDER_BIGICON_START_Y+m_nShopMovePosY+(CASHSHOP_RENDER_BIGICON_H*nCount),
						pShopInfo);
				}			
				// end 2009-01-28 by bhsohn 캐쉬샵 처리
			}			
			
			// 아이콘 설명
			ITEM *item = g_pDatabase->GetServerItemInfo(itCash->nItemNum);			
			
			m_pFontItem[nCount*3]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX, 
				CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount),
				RGB(255,255,255), item->ItemName, 0L);
			
			wsprintf( buf, STRMSG_C_SHOP_0001, item->MinTradeQuantity);//"%d개/1팩"
			m_pFontItem[(nCount*3)+1]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX, 
				CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount)+CASHSHOP_FONT_LINE_HEIGHT,
				RGB(178,190,255), buf, 0L);

			// 2006-06-07 by ispark, 세금 체크
//			wsprintf( buf, "%d", (int)(item->CashPrice*1.1f));
			wsprintf( buf, "%d", (int)(item->CashPrice * CASHSHOP_TEX));
			MakeCurrencySeparator( buf2, buf, 3, ',' );
			m_pFontItem[(nCount*3)+2]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX, 
				CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount)+(CASHSHOP_FONT_LINE_HEIGHT*2),
				GUI_FONT_COLOR_YM, buf2, 0L);
			
			m_pFontItem[(nCount*3)+2]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX+45, 
				CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount)+(CASHSHOP_FONT_LINE_HEIGHT*2),
				GUI_FONT_COLOR_YM, STRMSG_C_SHOP_0002, 0L);//"캐쉬"
			
			if( g_pShuttleChild->m_myShuttleInfo.Level>=item->ReqMinLevel && 
				(g_pShuttleChild->m_myShuttleInfo.Level<=item->ReqMaxLevel || item->ReqMaxLevel == 0))
			{
				if(item->ReqMaxLevel == 0)
				{
					wsprintf( buf, "\\q[Level %2.d]", item->ReqMinLevel);
					m_pFontItem[(nCount*3)+2]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX+101, 
						CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount)+(CASHSHOP_FONT_LINE_HEIGHT*2),
						GUI_FONT_COLOR_YM, buf, 0L);
				}
				else
				{
					wsprintf( buf, "\\q[Level %2.d~%2.d]", item->ReqMinLevel, item->ReqMaxLevel);
					m_pFontItem[(nCount*3)+2]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX+83, 
						CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount)+(CASHSHOP_FONT_LINE_HEIGHT*2),
						GUI_FONT_COLOR_YM, buf, 0L);
				}
			}
			else
			{
				if(item->ReqMaxLevel == 0)
				{
					wsprintf( buf, "\\r[Level %2.d]", item->ReqMinLevel);
					m_pFontItem[(nCount*3)+2]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX+101, 
						CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount)+(CASHSHOP_FONT_LINE_HEIGHT*2),
						GUI_FONT_COLOR_YM, buf, 0L);
				}
				else
				{
					wsprintf( buf, "\\r[Level %2.d~%2.d]", item->ReqMinLevel, item->ReqMaxLevel);
					m_pFontItem[(nCount*3)+2]->DrawText(CASHSHOP_RENDER_FONT_ICONINFO_X+m_nShopMovePosX+83, 
						CASHSHOP_RENDER_FONT_ICONINFO_Y+m_nShopMovePosY+(CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount)+(CASHSHOP_FONT_LINE_HEIGHT*2),
						GUI_FONT_COLOR_YM, buf, 0L);
				}
			}

			// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
			SHOP_ITEM* pShopInfo = FindCashShopData(nSelTab, itCash->nItemNum);
			if( pShopInfo && pShopInfo->IsLimitedEditionShopItem() )
			{
				CINFImage* pImg;
				if( m_bBling )
					pImg = m_pLimitedEdtion[ 0 ];
				else
					pImg = m_pLimitedEdtion[ 1 ];

				if( pShopInfo->IsSoldOutShopItem() )
					pImg = m_pLimitedEdtion[ 0 ];

				pImg->Move( CASHSHOP_RENDER_BIGICON_START_X + m_nShopMovePosX - 2,
							CASHSHOP_RENDER_BIGICON_START_Y + m_nShopMovePosY - 3 + (CASHSHOP_RENDER_BIGICON_H*nCount) );
				pImg->Render();

				sprintf( buf, STRMSG_C_100127_0301, pShopInfo->RemainCountForLimitedEdition );
				m_pFontItem[(nCount*3)+2]->DrawText( CASHSHOP_RENDER_BIGICON_START_X + m_nShopMovePosX + 295, 
													 CASHSHOP_RENDER_FONT_ICONINFO_Y + m_nShopMovePosY + (CASHSHOP_RENDER_FONT_ICONINFO_GAB*nCount) + (CASHSHOP_FONT_LINE_HEIGHT*2),
													 GUI_FONT_COLOR, buf, 0L);

				if( pShopInfo->IsSoldOutShopItem() )
				{
					m_pSoldOut_Item->Move( CASHSHOP_RENDER_BIGICON_START_X + m_nShopMovePosX - 2,
										   CASHSHOP_RENDER_BIGICON_START_Y + m_nShopMovePosY - 3 + (CASHSHOP_RENDER_BIGICON_H*nCount) );
					m_pSoldOut_Item->Render();
				}
			}
			// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

			nCount++;
			itCash++;
		}
	}

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	// 현재 선택한 캐쉬 아이템
	m_pImgSelectItem->Move( CASHSHOP_RENDER_TAB_X + m_nShopMovePosX + 9,
						    CASHSHOP_RENDER_TAB_Y + m_nShopMovePosY + CASHSHOP_RENDER_SELECT_TAB_GAB + ( 64 * m_nItemSelect ) );
	m_pImgSelectItem->Render();
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

	
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	//if(m_nCurrentSelectTab == CASHSHOP_ITEM_SKIN_ITEM)		//CASHSHOP_ITEM_SKIN_ITEM				4	
	if(nSelTab != -1 && nSelTab == GetSkinItemIndex())		//CASHSHOP_ITEM_SKIN_ITEM				4	
	{
		g_pShuttleChild->RenderInvenBack();
		// 2008-10-28 by bhsohn 캐쉬 상점 구조 변경
		//g_pShuttleChild->RenderMirror(1);
		POINT ptMirrorPos;
		ptMirrorPos.x = CASHSHOP_RENDER_START_X+CASH_SHOP_GEAR_UNIT_X;
		ptMirrorPos.y = CASHSHOP_RENDER_START_Y+CASH_SHOP_GEAR_UNIT_Y;		
		g_pShuttleChild->RenderMirror(&ptMirrorPos);

		// 로테이션 이미지
		if(m_nButtonState == ROTATION_NONE || m_nRotationState == ROTATION_STATE_N)
		{
			m_pRotationBase->Move(CASHSHOP_RENDER_START_X+CASH_SHOP_GEAR_ROTATION_KEY_X , CASHSHOP_RENDER_START_Y+CASH_SHOP_GEAR_ROTATION_KEY_Y);
			m_pRotationBase->Render();
		}
		else
		{
			m_pDirection[m_nButtonState][m_nRotationState]->Move(CASHSHOP_RENDER_START_X+CASH_SHOP_GEAR_ROTATION_KEY_X,CASHSHOP_RENDER_START_Y+CASH_SHOP_GEAR_ROTATION_KEY_Y);
			m_pDirection[m_nButtonState][m_nRotationState]->Render();
		}

		// 2009-01-28 by bhsohn 캐쉬샵 처리
//		if(m_vecImgCashIcon[m_nCurrentSelectTab].size() > (m_nItemSelect+m_pScroll->GetCurrentScrollIndex()))
// 		{
// 			m_pItem = g_pDatabase->GetServerItemInfo(m_vecImgCashIcon[m_nCurrentSelectTab][m_nItemSelect+m_pScroll->GetCurrentScrollIndex()].nItemNum);
// 		}
		if(m_vecImgCashIcon[nSelTab].size() > (m_nItemSelect+m_pScroll->GetCurrentScrollIndex()))
		{
			m_pItem = g_pDatabase->GetServerItemInfo(m_vecImgCashIcon[nSelTab][m_nItemSelect+m_pScroll->GetCurrentScrollIndex()].nItemNum);
		}
	}

	// 아이템 정보 창 렌더링	
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	//else if(m_nItemSelect+m_pScroll->GetCurrentScrollIndex() < m_vecImgCashIcon[m_nCurrentSelectTab].size())
	else if(nSelTab != -1 && m_nItemSelect+m_pScroll->GetCurrentScrollIndex() < m_vecImgCashIcon[nSelTab].size())
	{
		char chDelChar[10] = {0,};
		int nDelChar;
		wsprintf(chDelChar, "    ");
		nDelChar = m_pFontItemInfo[1]->GetStringSize(chDelChar).cx;
		
		memset(buf, 0x00, 512);
		memset(buf2, 0x00, 512);
		// 2009-01-28 by bhsohn 캐쉬샵 처리
		//ITEM *item = g_pDatabase->GetServerItemInfo(m_vecImgCashIcon[m_nCurrentSelectTab][m_nItemSelect+m_pScroll->GetCurrentScrollIndex()].nItemNum);		
		ITEM *item = g_pDatabase->GetServerItemInfo(m_vecImgCashIcon[nSelTab][m_nItemSelect+m_pScroll->GetCurrentScrollIndex()].nItemNum);		
		
		if(m_vecImgCashIcon[nSelTab][m_nItemSelect+m_pScroll->GetCurrentScrollIndex()].vecImgCashIcon != NULL)
		{
			m_vecImgCashIcon[nSelTab][m_nItemSelect+m_pScroll->GetCurrentScrollIndex()].vecImgCashIcon->Move(CASHSHOP_ITEM_INFO_ICON_X+m_nShopMovePosX,
				CASHSHOP_ITEM_INFO_ICON_Y+m_nShopMovePosY);
			m_vecImgCashIcon[nSelTab][m_nItemSelect+m_pScroll->GetCurrentScrollIndex()].vecImgCashIcon->Render();
		}

// 2006-06-08 by ispark, 이름 위치 수정
//		int nCharlen = (strlen(item->ItemName)*CASHSHOP_SIDE_WIDTH_ENGLISH)/2;
		int nCharlen = m_pFontItemInfo[0]->GetStringSize(item->ItemName).cx / 2;
		m_pFontItemInfo[0]->DrawText(CASHSHOP_ITEM_INFO_NAME_X+m_nShopMovePosX-nCharlen,CASHSHOP_ITEM_INFO_NAME_Y+m_nShopMovePosY,RGB(255,255,255),
			item->ItemName);
		if(item->ReqMaxLevel == 0)
		{
//			wsprintf( buf, "%d",(int)(item->CashPrice*1.1f));CASHSHOP_TEX
			wsprintf( buf, "%d",(int)(item->CashPrice*CASHSHOP_TEX));
			MakeCurrencySeparator( buf2, buf, 3, ',' );
			wsprintf( buf, STRMSG_C_SHOP_0003, item->MinTradeQuantity, buf2, item->ReqMinLevel);//"%3.d개/1팩 \\e%s 캐쉬 \\q[Level %d]"
//			nCharlen = (strlen(buf)*CASHSHOP_SIDE_WIDTH_ENGLISH)/2;
			nCharlen = m_pFontItemInfo[1]->GetStringSize(buf).cx;
			nCharlen = (nCharlen - nDelChar) / 2;
			m_pFontItemInfo[1]->DrawText(CASHSHOP_ITEM_INFO_NAME_X+m_nShopMovePosX-nCharlen,CASHSHOP_ITEM_INFO_NAME_Y+m_nShopMovePosY+CASHSHOP_FONT_LINE_HEIGHT,
				RGB(178,190,255), buf, 0L);
		}
		else
		{
//			wsprintf( buf, "%d",(int)(item->CashPrice*1.1f));CASHSHOP_TEX
			wsprintf( buf, "%d",(int)(item->CashPrice*CASHSHOP_TEX));
			MakeCurrencySeparator( buf2, buf, 3, ',' );
			wsprintf( buf, STRMSG_C_SHOP_0004, item->MinTradeQuantity, buf2,  //"%3.d개/1팩 \\e%s 캐쉬 \\q[Level %d~%d]"
				item->ReqMinLevel, item->ReqMaxLevel);
//			nCharlen = (strlen(buf)*CASHSHOP_SIDE_WIDTH_ENGLISH)/2;
			nCharlen = m_pFontItemInfo[1]->GetStringSize(buf).cx;
			nCharlen = (nCharlen - nDelChar) / 2;
			m_pFontItemInfo[1]->DrawText(CASHSHOP_ITEM_INFO_NAME_X+m_nShopMovePosX-nCharlen,CASHSHOP_ITEM_INFO_NAME_Y+m_nShopMovePosY+CASHSHOP_FONT_LINE_HEIGHT,
				RGB(178,190,255), buf, 0L);
		}

		// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
		SHOP_ITEM* pShopInfo = FindCashShopData( nSelTab, item->ItemNum );
		if( pShopInfo && pShopInfo->IsLimitedEditionShopItem() )
		{
			sprintf( buf, STRMSG_C_100127_0301, pShopInfo->RemainCountForLimitedEdition );	// "\\y남은 개수: %d개\\y"

			m_pFontItemInfo[1]->DrawText( CASHSHOP_ITEM_INFO_NAME_X + m_nShopMovePosX - m_pFontItemInfo[1]->GetStringSize( buf ).cx / 2,
										  CASHSHOP_ITEM_INFO_NAME_Y + m_nShopMovePosY + CASHSHOP_FONT_LINE_HEIGHT * 2,
										  GUI_FONT_COLOR, buf, 0L );
		}
		// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

		m_pItem = item;
		
	}

	// 나의 캐쉬 찍기	
//	wsprintf( buf, "%d", (int)(m_nMyCashPoint*1.1f));
	wsprintf( buf, "%d", (int)((m_nMyCashPoint+m_nGiftCardPoint)*CASHSHOP_TEX));
	MakeCurrencySeparator( buf2, buf, 3, ',' );
	m_pFontItemInfo[CASH_SHOP_ITEM_INFO-1]->DrawText(CASHSHOP_RENDER_MYCASH_X+m_nShopMovePosX, CASHSHOP_RENDER_MYCASH_Y+m_nShopMovePosY,
		GUI_FONT_COLOR_YM, buf2);			
	
	// 2006-06-08 by ispark, 상품권 없음
	// 2006-10-13 by ispark, 한글 있음
	// 2007-10-16 by bhsohn 보너스 캐쉬제거
//#ifdef LANGUAGE_KOREA
//	// 상품권
//	wsprintf( buf, "%d", (int)(m_nGiftCardPoint*1.1f));
//	wsprintf( buf, "%d", (int)(m_nGiftCardPoint*CASHSHOP_TEX));
//	MakeCurrencySeparator( buf2, buf, 3, ',' );
//	m_pFontItemInfo[CASH_SHOP_ITEM_INFO-1]->DrawText(CASHSHOP_RENDER_MYCASH_X+m_nShopMovePosX, CASHSHOP_RENDER_MYCASH_Y+m_nShopMovePosY - 23,
//		GUI_FONT_COLOR_YM, buf2);
//#endif
//
#ifdef LANGUAGE_CHINA
	// 상품권
	wsprintf( buf, "%d", (int)(m_nGiftCardPoint*1.1f));
	wsprintf( buf, "%d", (int)(m_nGiftCardPoint*CASHSHOP_TEX));
	MakeCurrencySeparator( buf2, buf, 3, ',' );
	m_pFontItemInfo[CASH_SHOP_ITEM_INFO-1]->DrawText(CASHSHOP_RENDER_MYCASH_X+m_nShopMovePosX, CASHSHOP_RENDER_MYCASH_Y+m_nShopMovePosY - 23,
		GUI_FONT_COLOR_YM, buf2);
#endif
	
	// 버튼렌더링
	m_pImgChargeButton[m_nCurrentMouseStateCharge]->Move(CASHSHOP_RENDER_CHARGE_BUTTON_X+m_nShopMovePosX,
	CASHSHOP_RENDER_CHARGE_BUTTON_Y+m_nShopMovePosY);
	m_pImgChargeButton[m_nCurrentMouseStateCharge]->Render();
	if(m_pImgGiftButton)
	{
	// 선물하기 버튼 렌더링.
		m_pImgGiftButton->Render();
	}
	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	if(m_pImgChargeBtn)
	{
		m_pImgChargeBtn->Render();
	}	
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
	
	// 2007-10-16 by bhsohn 케쉬샵 충전버튼 막음
//	m_pImgBuyButton[m_nCurrentMouseStateBuy]->Move(CASHSHOP_RENDER_BUY_BUTTON_X+m_nShopMovePosX,
//	CASHSHOP_RENDER_BUY_BUTTON_Y+m_nShopMovePosY);
//	m_pImgBuyButton[m_nCurrentMouseStateBuy]->Render();

	// 아이콘 설명
	RenderDescIcon();
	
	// 스크롤 렌더링 
	m_pScroll->Render();
	if(g_pGameMain->m_bSendCashItemBuy)
	{
		if(m_nMyCashPoint+m_nGiftCardPoint >= m_pItem->CashPrice)
		{
			// 2005-03-07 by jschoi
			g_pD3dApp->m_bRequestEnable = FALSE;

			MSG_FC_SHOP_BUY_CASH_ITEM sMsg;
			memset(&sMsg,0x00,sizeof(sMsg));
			sMsg.BuildingIndex = CASH_SHOP_BUILDING_INDEX;
			sMsg.ItemNum = m_pItem->ItemNum;
			sMsg.Amount = m_pItem->MinTradeQuantity;
			sMsg.GiveTargetCharacterUID = m_nGiveTargetCharacterUID?m_nGiveTargetCharacterUID:0;
			g_pFieldWinSocket->SendMsg( T_FC_SHOP_BUY_CASH_ITEM, (char*)&sMsg, sizeof(sMsg) );
			g_pGameMain->m_bSendCashItemBuy = FALSE;
			m_nGiveTargetCharacterUID = 0;
		}
		else
		{
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_SHOP_0005,COLOR_ERROR);//"캐쉬가 부족합니다."
			g_pGameMain->m_bSendCashItemBuy = FALSE;
		}
	}

	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
	if(m_pWebChargeBk )
	{
		if(g_pD3dApp->GetWeb() == TRUE)
		{
			int nWebPoxX = WEB_START_X-24;
			int nWebPoxY = WEB_START_Y-52;		
			m_pWebChargeBk->Move(nWebPoxX, nWebPoxY);
			m_pWebChargeBk->Render();

			if(m_pImgChargeCloseBtn)
			{
				if(!m_pImgChargeCloseBtn->IsShowWindow())
				{
					POINT ptSize = m_pWebChargeBk->GetImgSize();
					m_pImgChargeCloseBtn->ShowWindow(TRUE);
					m_pImgChargeCloseBtn->SetBtnPosition(nWebPoxX+ptSize.x - 24, nWebPoxY+8);
				}

				m_pImgChargeCloseBtn->Render();
			}			
			
		}
		else
		{
			if(m_pImgChargeCloseBtn && m_pImgChargeCloseBtn->IsShowWindow())
			{				
				m_pImgChargeCloseBtn->ShowWindow(FALSE);
			}
		}		
	}
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
}
void CINFCityCashShop::OnChangeWearItem()
{
	ITEM *item = NULL;
	if( m_nItemSelect < 0 )
		return;

	// 2009-01-28 by bhsohn 캐쉬샵 처리
	int nSelTab = GetTabToItemIdx(m_nCurrentSelectTab);
	if(nSelTab == -1)
	{
		return;
	}
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	int nSelectTotalIdx = m_nItemSelect + m_pScroll->GetCurrentScrollIndex();
	

	if(m_vecItemInfo[nSelTab].size() > nSelectTotalIdx)
	{
		item =  g_pDatabase->GetServerItemInfo(m_vecItemInfo[nSelTab][nSelectTotalIdx]->ItemNum);
	}
	if(item)
	{
		if(CompareBitFlag(item->ReqUnitKind ,g_pShuttleChild->m_myShuttleInfo.UnitKind))
		{// 같은 기어의 스킨만 변경한다.
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
void CINFCityCashShop::Tick()
{
	FLOG( "CINFCityCashShop::Tick()" );

	if(m_bTurnLeft)		
		g_pShuttleChild->MirrorTurnUp();
	if(m_bTurnRight)	
		g_pShuttleChild->MirrorTurnDown();
	if(m_bTurnUp)		
		g_pShuttleChild->MirrorTurnLeft();
	if(m_bTurnDown)		
		g_pShuttleChild->MirrorTurnRight();

	// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	DWORD nCurTime = timeGetTime();
	if( nCurTime - m_nBlingStartTime > 1000 )
	{
		m_nBlingStartTime	= nCurTime;

		m_bBling			= !m_bBling;
	}
	// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
}
void CINFCityCashShop::SetByPushButton(BOOL bFlag)
{
	for(int i=0; i<4; i++)
	{
		m_bByPush[i] = FALSE;
	}
}

int CINFCityCashShop::ProcessRotationUnit(POINT pt, UINT uMsg)
{
	if(uMsg == WM_LBUTTONUP)	SetByPushButton(FALSE);

	m_nRotationState = ROTATION_NONE;
	m_nButtonState	 = ROTATION_STATE_N;
	
	m_bTurnLeft	= FALSE;
	m_bTurnRight = FALSE;
	m_bTurnUp = FALSE;
	m_bTurnDown = FALSE;


	int PosX = CASHSHOP_RENDER_START_X+CASH_SHOP_GEAR_ROTATION_KEY_X;
	int PosY = CASHSHOP_RENDER_START_Y+CASH_SHOP_GEAR_ROTATION_KEY_Y;

	if( pt.x>PosX && pt.x< PosX+12 && pt.y>PosY+8 && pt.y<PosY+30)
	{	// 왼쪽 돌리기
		switch(uMsg)
		{
		case WM_MOUSEMOVE:
			m_nRotationState = ROTATION_LEFT;
			m_nButtonState = ROTATION_STATE_O;
			if(m_bByPush[0] == TRUE)
			{
				m_nRotationState = ROTATION_LEFT;
				m_nButtonState = ROTATION_STATE_P;
				m_bTurnLeft = TRUE;	
			}
			break;
		case WM_LBUTTONDOWN:
			m_nRotationState = ROTATION_LEFT;
			m_nButtonState = ROTATION_STATE_P;
			m_bTurnLeft = TRUE;	
			m_bByPush[0] = TRUE;
			return INF_MSGPROC_BREAK;
		case WM_LBUTTONUP:
			m_nRotationState = ROTATION_LEFT;
			m_nButtonState = ROTATION_STATE_N;			
			return INF_MSGPROC_BREAK;
		}
	}
	else if( pt.x>PosX+34 && pt.x< PosX+46 && pt.y>PosY+8 && pt.y<PosY+30)
	{	// 오른쪽 돌리기
		switch(uMsg)
		{
		case WM_LBUTTONDOWN:
			m_nRotationState = ROTATION_RIGHT;
			m_nButtonState = ROTATION_STATE_P;
			m_bTurnRight = TRUE;
			m_bByPush[1] = TRUE;
			return INF_MSGPROC_BREAK;
		case WM_MOUSEMOVE:
			m_nRotationState = ROTATION_RIGHT;
			m_nButtonState = ROTATION_STATE_O;
			if(m_bByPush[1] == TRUE)
			{
				m_nRotationState = ROTATION_RIGHT;
				m_nButtonState = ROTATION_STATE_P;
				m_bTurnRight = TRUE;
			}

			break;		
		case WM_LBUTTONUP:
			m_nRotationState = ROTATION_RIGHT;
			m_nButtonState = ROTATION_STATE_N;
			return INF_MSGPROC_BREAK;
		}
	}
	else if( pt.x>PosX+13 && pt.x< PosX+33 && pt.y>PosY && pt.y<PosY+10)
	{	// 위쪽 돌리기
		switch(uMsg)
		{
		case WM_MOUSEMOVE:
			m_nRotationState = ROTATION_UP;
			m_nButtonState = ROTATION_STATE_O;
			if(m_bByPush[2] == TRUE)
			{
				m_nRotationState = ROTATION_UP;
				m_nButtonState = ROTATION_STATE_P;
				m_bTurnUp = TRUE;
			}
			break;
		case WM_LBUTTONDOWN:
			m_nRotationState = ROTATION_UP;
			m_nButtonState = ROTATION_STATE_P;
			m_bTurnUp = TRUE;
			m_bByPush[2] = TRUE;
			return INF_MSGPROC_BREAK;
		case WM_LBUTTONUP:
			m_nRotationState = ROTATION_UP;
			m_nButtonState = ROTATION_STATE_N;
			
			return INF_MSGPROC_BREAK;
		}
	}
	else if( pt.x>PosX+13 && pt.x<PosX+33 && pt.y>PosY+26 && pt.y<PosY+38)
	{	// 아래쪽 돌리기
		switch(uMsg)
		{
		case WM_MOUSEMOVE:
			m_nRotationState = ROTATION_DOWN;
			m_nButtonState = ROTATION_STATE_O;
			if(m_bByPush[3] == TRUE)
			{
				m_nRotationState = ROTATION_DOWN;
				m_nButtonState = ROTATION_STATE_P;
				m_bTurnDown = TRUE;
			}
			break;
		case WM_LBUTTONDOWN:
			m_nRotationState = ROTATION_DOWN;
			m_nButtonState = ROTATION_STATE_P;
			m_bTurnDown = TRUE;
			m_bByPush[3] = TRUE;
			return INF_MSGPROC_BREAK;
		case WM_LBUTTONUP:
			m_nRotationState = ROTATION_DOWN;
			m_nButtonState = ROTATION_STATE_N;
			return INF_MSGPROC_BREAK;
		}
	}
	else if( pt.x>PosX+13 && pt.x<PosX+33 && pt.y>PosY+13 && pt.y<PosY+25)
	{	// 중앙 돌리기
		switch(uMsg)
		{
		case WM_MOUSEMOVE:
			m_nRotationState = ROTATION_ORIGINAL;
			m_nButtonState = ROTATION_STATE_O;
			break;
		case WM_LBUTTONDOWN:
			m_nRotationState = ROTATION_ORIGINAL;
			m_nButtonState = ROTATION_STATE_P;
			g_pShuttleChild->MirrorTurnOrig();
			return INF_MSGPROC_BREAK;
		case WM_LBUTTONUP:
			m_nRotationState = ROTATION_ORIGINAL;
			m_nButtonState = ROTATION_STATE_N;
			return INF_MSGPROC_BREAK;
		}
	}

	return INF_MSGPROC_NORMAL;
}
int CINFCityCashShop::ProcessRotationUnitWnd(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 기본 시작 X 위치 = 16
	// 기본 시작 Y 위치 = nWindowPosY + 207	
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			if(ProcessRotationUnit(pt, uMsg) == INF_MSGPROC_BREAK)
				return INF_MSGPROC_BREAK;
		}
		break;
	}	
	return INF_MSGPROC_NORMAL;
}

int CINFCityCashShop::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFCityCashShop::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
	if(g_pD3dApp->GetWeb() == TRUE)
	{
		if(INF_MSGPROC_BREAK == WndWebProc(uMsg, wParam, lParam))
		{
			return INF_MSGPROC_BREAK;
		}
		return INF_MSGPROC_NORMAL;
	}
	// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가

// 2008-08-13 by dgwoo 구입 메시지창이 떠있을경우엔 스크롤 및 다른 컨트롤이 안되도록 수정.
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	int nSelTmpTab = GetTabToItemIdx(m_nCurrentSelectTab);

	if(g_pGameMain->m_bBuyMessage == TRUE)
	{
		return INF_MSGPROC_NORMAL;
	}
	if(m_pScroll)
	{
		// 2009-01-28 by bhsohn 캐쉬샵 처리
		int nOldScroll = m_pScroll->GetCurrentScrollIndex();
		if(m_pScroll->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		{
			// 2009-01-28 by bhsohn 캐쉬샵 처리
			if(nOldScroll != m_pScroll->GetCurrentScrollIndex())
			{
				UpdateGiftButton(nSelTmpTab, m_nItemSelect);
			}				
			// end 2009-01-28 by bhsohn 캐쉬샵 처리

			return INF_MSGPROC_BREAK;
		}
		// 2009-01-28 by bhsohn 캐쉬샵 처리
		if(nOldScroll != m_pScroll->GetCurrentScrollIndex())
		{
			UpdateGiftButton(nSelTmpTab, m_nItemSelect);			
		}				
		// end 2009-01-28 by bhsohn 캐쉬샵 처리
	}
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	//if(m_nCurrentSelectTab == CASHSHOP_ITEM_SKIN_ITEM)	
	if(nSelTmpTab != -1 && nSelTmpTab == GetSkinItemIndex())
	{
		if(ProcessRotationUnitWnd(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		{
			return INF_MSGPROC_BREAK;
		}
	}

	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		{
			OnChangeWearItem();
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			// 2007-10-16 by bhsohn 케쉬샵 충전버튼 막음
//			if( pt.y > CASHSHOP_RENDER_BUY_BUTTON_Y+m_nShopMovePosY && 
//				pt.y < CASHSHOP_RENDER_BUY_BUTTON_Y+m_nShopMovePosY + CASHSHOP_RENDER_BUY_BUTTON_H &&
//				pt.x > CASHSHOP_RENDER_BUY_BUTTON_X+m_nShopMovePosX && 
//				pt.x < CASHSHOP_RENDER_BUY_BUTTON_X+m_nShopMovePosX + CASHSHOP_RENDER_BUY_BUTTON_W)
//			{
//				if(m_bCurrentMouseStateBuy)
//					m_nCurrentMouseStateBuy = CASHSHOP_BUTTON_STATE_PUH;
//				else if(m_nCurrentMouseStateBuy != CASHSHOP_BUTTON_STATE_PUH)
//					m_nCurrentMouseStateBuy = CASHSHOP_BUTTON_STATE_OVE;
//			}
//			else 
//			{
//				m_nCurrentMouseStateBuy = CASHSHOP_BUTTON_STATE_NOM;
//			}

			if( pt.y > CASHSHOP_RENDER_CHARGE_BUTTON_Y+m_nShopMovePosY && 
				pt.y < CASHSHOP_RENDER_CHARGE_BUTTON_Y+m_nShopMovePosY + CASHSHOP_RENDER_CHARGE_BUTTON_H &&
				pt.x > CASHSHOP_RENDER_CHARGE_BUTTON_X+m_nShopMovePosX && 
				pt.x < CASHSHOP_RENDER_CHARGE_BUTTON_X+m_nShopMovePosX + CASHSHOP_RENDER_CHARGE_BUTTON_W)
			{
				if(m_bCurrentMouseStateCharge)
					m_nCurrentMouseStateCharge = CASHSHOP_BUTTON_STATE_PUH;
				else if(m_nCurrentMouseStateCharge != CASHSHOP_BUTTON_STATE_PUH)
					m_nCurrentMouseStateCharge = CASHSHOP_BUTTON_STATE_OVE;
			}
			else 
			{
				m_nCurrentMouseStateCharge = CASHSHOP_BUTTON_STATE_NOM;
			}

			// 창이동
			if( m_bMoveShop )
			{
				//m_nStartFAQPositionX = m_nFAQBoxStartXOld + pt.x - m_pointBeforeMousePoints.x;
				//m_nStartFAQPositionY = m_nFAQBoxStartYOld + pt.y - m_pointBeforeMousePoints.y;

				m_nShopMovePosX = m_nShopOldPosX + pt.x - m_pointBeforeMousePoints.x;
				m_nShopMovePosY = m_nShopOldPosY + pt.y - m_pointBeforeMousePoints.y;
			}
			if(m_pImgGiftButton)
				m_pImgGiftButton->OnMouseMove(pt);
			// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
			if(m_pImgChargeBtn)
			{
				m_pImgChargeBtn->OnMouseMove(pt);
			}			
			// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		

			//m_nCityRenderGab;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// 메세지 박스렌더링 상태에서 모든다운정지
			BOOL bBreak =  FALSE;
			vector<CINFMessageBox*>::iterator it = g_pGameMain->m_pInfWindow->m_vecMessageBox.begin();
			while(it != g_pGameMain->m_pInfWindow->m_vecMessageBox.end())
			{				
				CINFMessageBox* pMsgBox = *it;
				// 메세지 박스 지우기(교환)
				if(_Q_CASHITEM_BUY == pMsgBox->m_nMsgType)
				{
					bBreak = TRUE;					
				}
				it++;
			}
			if(TRUE == bBreak) break;

			// 2007-10-16 by bhsohn 케쉬샵 충전버튼 막음			
//			if( pt.y > CASHSHOP_RENDER_BUY_BUTTON_Y+m_nShopMovePosY && 
//				pt.y < CASHSHOP_RENDER_BUY_BUTTON_Y+m_nShopMovePosY + CASHSHOP_RENDER_BUY_BUTTON_H &&
//				pt.x > CASHSHOP_RENDER_BUY_BUTTON_X+m_nShopMovePosX && 
//				pt.x < CASHSHOP_RENDER_BUY_BUTTON_X+m_nShopMovePosX + CASHSHOP_RENDER_BUY_BUTTON_W)
//			{
//				m_bCurrentMouseStateBuy = TRUE;
//				m_nCurrentMouseStateBuy = CASHSHOP_BUTTON_STATE_PUH;
//				return INF_MSGPROC_BREAK;
//			}
//			else 
//			{
//				m_nCurrentMouseStateBuy = CASHSHOP_BUTTON_STATE_NOM;
//			}
			if(m_pImgGiftButton)
				m_pImgGiftButton->OnLButtonDown(pt);
			// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
			if(m_pImgChargeBtn)
			{
				if(TRUE == m_pImgChargeBtn->OnLButtonDown(pt))
				{
					return INF_MSGPROC_BREAK;
				}
			}				
			// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		

			if( pt.y > CASHSHOP_RENDER_CHARGE_BUTTON_Y+m_nShopMovePosY && 
				pt.y < CASHSHOP_RENDER_CHARGE_BUTTON_Y+m_nShopMovePosY + CASHSHOP_RENDER_CHARGE_BUTTON_H &&
				pt.x > CASHSHOP_RENDER_CHARGE_BUTTON_X+m_nShopMovePosX && 
				pt.x < CASHSHOP_RENDER_CHARGE_BUTTON_X+m_nShopMovePosX + CASHSHOP_RENDER_CHARGE_BUTTON_W)
			{
				m_bCurrentMouseStateCharge = TRUE;
				m_nCurrentMouseStateCharge = CASHSHOP_BUTTON_STATE_PUH;
				return INF_MSGPROC_BREAK;
			}
			else 
			{
				m_nCurrentMouseStateCharge = CASHSHOP_BUTTON_STATE_NOM;
			}

			// 아이템 선택
			int i;
			for(i=0; i<CASHSHOP_SHOW_ICON_MAX; i++)
			{
				if( pt.y > CASHSHOP_ITEM_SELECT_RECT_Y+m_nShopMovePosY && 
					pt.y < CASHSHOP_ITEM_SELECT_RECT_Y+m_nShopMovePosY + CASHSHOP_ITEM_SELECT_RECT_H+(i*CASHSHOP_ITEM_SELECT_RECT_H) &&
					pt.x > CASHSHOP_ITEM_SELECT_RECT_X+m_nShopMovePosX && 
					pt.x < CASHSHOP_ITEM_SELECT_RECT_X+m_nShopMovePosX + CASHSHOP_ITEM_SELECT_RECT_W)
				{
					// 2009-01-28 by bhsohn 캐쉬샵 처리					
					int nSelTab = GetTabToItemIdx(m_nCurrentSelectTab);

					//if(m_vecImgCashIcon[m_nCurrentSelectTab].size() > (i+m_pScroll->GetCurrentScrollIndex()))
					if(nSelTab != -1 && m_vecImgCashIcon[nSelTab].size() > (i+m_pScroll->GetCurrentScrollIndex()))
					{
					    m_nItemSelect = i;
						// 2009-01-28 by bhsohn 캐쉬샵 처리
						//if(m_nCurrentSelectTab == CASHSHOP_ITEM_SKIN_ITEM)
						if(nSelTab != -1 && nSelTab == GetSkinItemIndex())						
						{
							OnChangeWearItem();
						}
						// 2009-01-28 by bhsohn 캐쉬샵 처리
						UpdateGiftButton(nSelTab, m_nItemSelect);
						// end 2009-01-28 by bhsohn 캐쉬샵 처리
					}					
					return INF_MSGPROC_BREAK;
				}
			}

			// 탭 선택
			for(i=0; i<CASH_SHOP_VIEW_TAB; i++)
			{
				// 2008-10-28 by bhsohn 캐쉬 상점 구조 변경
// 				if(m_nShopTapEndPosX[i] < 0)
// 				{
// 					continue;
// 				}
				// end 2008-10-28 by bhsohn 캐쉬 상점 구조 변경
				// 2009-01-28 by bhsohn 캐쉬샵 처리
				int nSelTab = GetTabToItemIdx(i);
				if(nSelTab == -1)
				{
					continue;
				}
				else if(m_vecItemInfo[nSelTab].empty())
				{
					continue;
				}
				// end 2009-01-28 by bhsohn 캐쉬샵 처리
				if( pt.y > CASHSHOP_ITEM_TAB_Y+m_nShopMovePosY && 
					pt.y < CASHSHOP_ITEM_TAB_Y+m_nShopMovePosY+CASHSHOP_ITEM_TAB_H &&
					pt.x > CASHSHOP_ITEM_TAB_X+m_nShopMovePosX && 
//					pt.x < CASHSHOP_ITEM_TAB_X+m_nShopMovePosX + CASHSHOP_ITEM_TAB_W+(i*CASHSHOP_ITEM_TAB_W))
					pt.x < CASHSHOP_ITEM_TAB_X+m_nShopMovePosX + m_nShopTapEndPosX[i])
				{					
					// 2009-01-28 by bhsohn 캐쉬샵 처리
					m_nCurrentSelectTab = i;
					if(m_pImgGiftButton)
					{
						// 2007-11-14 by dgwoo 멤버쉽 탭이나 스킨 탭일경우 선물하기 버튼을 비활성화 한다.
						// 2009-01-28 by bhsohn 캐쉬샵 처리
// 						if(m_nCurrentSelectTab == CASHSHOP_ITEM_PREMIUM_CARD ||
// 							m_nCurrentSelectTab == CASHSHOP_ITEM_SKIN_ITEM) 
// 						{
// 							m_pImgGiftButton->EnableBtn(FALSE);
// 						}else
// 						{
// 							m_pImgGiftButton->EnableBtn(TRUE);
// 						}
						// end 2009-01-28 by bhsohn 캐쉬샵 처리
					}
					m_nItemSelect = 0;
					// 2009-01-28 by bhsohn 캐쉬샵 처리
					int nSelTab = GetTabToItemIdx(m_nCurrentSelectTab);
					// end 2009-01-28 by bhsohn 캐쉬샵 처리

					if(nSelTab != -1)
					{
						m_pScroll->Reset();
						m_pScroll->SetNumberOfData( m_vecImgCashIcon[nSelTab].size() );
					}

					// 2007-08-10 by cmkwon, 아머 컬러 탭일 경우 컬러를 적용해준다
					// 2009-01-28 by bhsohn 캐쉬샵 처리
					//if(m_nCurrentSelectTab == CASHSHOP_ITEM_SKIN_ITEM)
					if(nSelTab != -1 && nSelTab == GetSkinItemIndex())					
					{
						OnChangeWearItem();
					}
					// 2009-01-28 by bhsohn 캐쉬샵 처리
					// 선물하기 버튼 갱신
					UpdateGiftButton(nSelTab, m_nItemSelect);
					// end 2009-01-28 by bhsohn 캐쉬샵 처리
					return INF_MSGPROC_BREAK;
				}
			}

			// 닫기 버튼 클릭
			if( pt.y > CASHSHOP_ITEM_CLOSE_Y+m_nShopMovePosY && 
				pt.y < CASHSHOP_ITEM_CLOSE_Y+m_nShopMovePosY+CASHSHOP_ITEM_CLOSE_BUTTON_H &&
				pt.x > CASHSHOP_ITEM_CLOSE_X+m_nShopMovePosX && 
				pt.x < CASHSHOP_ITEM_CLOSE_X+m_nShopMovePosX + CASHSHOP_ITEM_CLOSE_BUTTON_W)
			{	
				g_pInterface->m_pCityBase->OnCityNPCButtonDown(CITY_NPC_BUTTON_CLOSE);
			}

			// 창이동
// 2007-08-10 by dgwoo 캐쉬 상점 이동 불가
//			if( pt.y > CASHSHOP_RENDER_START_Y+m_nShopMovePosY && 
//				pt.y < CASHSHOP_RENDER_START_Y+m_nShopMovePosY+CASHSHOP_ITEM_SHOP_MOVE_H &&
//				pt.x > CASHSHOP_RENDER_START_X+m_nShopMovePosX && 
//				pt.x < CASHSHOP_RENDER_START_X+m_nShopMovePosX + CASHSHOP_ITEM_SHOP_MOVE_W)
//			{
//				m_pointBeforeMousePoints	= pt;
//				m_nShopOldPosX				= m_nShopMovePosX;
//				m_nShopOldPosY				= m_nShopMovePosY;
//				
//				m_bMoveShop					= TRUE;				
//			}
			
			// 사각 영역에 들어오면 클릭 제외
			if(pt.x >= CASHSHOP_RENDER_START_X + m_nShopMovePosX && pt.x <= CASHSHOP_RENDER_START_X + m_nShopMovePosX + CASHSHOP_ITEM_SHOP_MOVE_W &&
				pt.y >= CASHSHOP_RENDER_START_Y + m_nShopMovePosY && pt.y <= CASHSHOP_RENDER_START_Y + m_nShopMovePosY + 397)
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			// 2007-10-16 by bhsohn 케쉬샵 충전버튼 막음
//			if( pt.y > CASHSHOP_RENDER_BUY_BUTTON_Y+m_nShopMovePosY && 
//				pt.y < CASHSHOP_RENDER_BUY_BUTTON_Y+m_nShopMovePosY + CASHSHOP_RENDER_BUY_BUTTON_H &&
//				pt.x > CASHSHOP_RENDER_BUY_BUTTON_X+m_nShopMovePosX && 
//				pt.x < CASHSHOP_RENDER_BUY_BUTTON_X+m_nShopMovePosX + CASHSHOP_RENDER_BUY_BUTTON_W &&
//				m_bCurrentMouseStateBuy)
//			{
//				
//				// 충전 보내기
//				SendChargeCash();
//			}
//			else 
			if( pt.y > CASHSHOP_RENDER_CHARGE_BUTTON_Y+m_nShopMovePosY && 
				pt.y < CASHSHOP_RENDER_CHARGE_BUTTON_Y+m_nShopMovePosY + CASHSHOP_RENDER_CHARGE_BUTTON_H &&
				pt.x > CASHSHOP_RENDER_CHARGE_BUTTON_X+m_nShopMovePosX && 
				pt.x < CASHSHOP_RENDER_CHARGE_BUTTON_X+m_nShopMovePosX + CASHSHOP_RENDER_CHARGE_BUTTON_W &&
				m_bCurrentMouseStateCharge)
			{
				// 구입 보내기
				if(m_pItem != NULL)
				{
					// 2008-08-13 by dgwoo 구입 메시지창이 떠있을경우엔 스크롤 및 다른 컨트롤이 안되도록 수정.
					g_pGameMain->m_bBuyMessage = TRUE;
					SendBuyItem(m_pItem);
				}
			}
			// 2007-11-14 by dgwoo 선물 버튼 클릭.
			if(m_pImgGiftButton &&
				m_pImgGiftButton->OnLButtonUp(pt))
			{
				// 2008-08-13 by dgwoo 구입 메시지창이 떠있을경우엔 스크롤 및 다른 컨트롤이 안되도록 수정.
				g_pGameMain->m_bBuyMessage = TRUE;
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_071115_0100,_Q_GIFT_CHARACTER_TEXT,0,0,0,m_pItem->ItemNum);
			}
			m_bMoveShop = FALSE;
			m_bCurrentMouseStateCharge	= FALSE;
			m_bCurrentMouseStateBuy		= FALSE;
			m_nCurrentMouseStateCharge	= CASHSHOP_BUTTON_STATE_NOM;
			m_nCurrentMouseStateBuy		= CASHSHOP_BUTTON_STATE_NOM;

			// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
			if(m_pImgChargeBtn && TRUE == m_pImgChargeBtn->OnLButtonUp(pt))
			{
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
				OnClickCashChargeBtn();
				return INF_MSGPROC_BREAK;
			}						
			// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가		
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
int CINFCityCashShop::WndWebProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_pImgChargeCloseBtn)
			{
				m_pImgChargeCloseBtn->OnMouseMove(pt);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_pImgChargeCloseBtn)
			{
				if(TRUE == m_pImgChargeCloseBtn->OnLButtonDown(pt))
				{
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

			if((m_pImgChargeCloseBtn && TRUE == m_pImgChargeCloseBtn->OnLButtonUp(pt)) 
				&& (g_pD3dApp->GetWeb() == TRUE))
			{
				g_pFieldWinSocket->SendMsg( T_FC_CHARACTER_GET_CASH_MONEY_COUNT, NULL, 0 );
				g_pD3dApp->PopupWebWindow(FALSE);
				
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);							
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
// end 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가


void CINFCityCashShop::RenderDescIcon()
{
	// 2006-06-08 by ispark, 국가별로 변경
	char buff[CASH_SHOP_ITEM_INFO_DES][128];
	memset(buff, 0x00, CASH_SHOP_ITEM_INFO_DES*128);
//	char *token;
//	char seps[] = "$";
//	char buffer[1024];
	vector<string> m_vecCashDesc;

	if(m_pItem)
	{
//		strncpy(buffer, m_pItem->Description, sizeof(m_pItem->Description));
		STRING_CULL(m_pItem->Description, CASHSHOP_ITEM_DESC_MAX, &m_vecCashDesc, m_pFontItemInfo[2]);
		
//		token = strtok(buffer, seps);
//		if(token != NULL)
//			strncpy(buff[0], token, strlen(token));	token = strtok(NULL, seps);		
//		if(token != 0)
//			strncpy(buff[1], token, strlen(token));	token = strtok(NULL, seps);		
//		if(token != 0)
//			strncpy(buff[2], token, strlen(token));	token = strtok(NULL, seps);
//		if(token != 0)
//			strncpy(buff[3], token, strlen(token));	token = strtok(NULL, seps);
//		if(token != 0)
//			strncpy(buff[4], token, strlen(token));	token = strtok(NULL, seps);
//		if(token != 0)
//			strncpy(buff[5], token, strlen(token));	token = strtok(NULL, seps);
//		if(token != 0)
//			strncpy(buff[6], token, strlen(token));	token = strtok(NULL, seps);
//		if(token != 0)
//			strncpy(buff[7], token, strlen(token)); 
		int i = 0;
		vector<string>::iterator it = m_vecCashDesc.begin();
		while(it != m_vecCashDesc.end())
		{
			m_pFontItemInfo[i+2]->DrawText(CASHSHOP_ITEM_INFO_NAME_X+m_nShopMovePosX - 80,
				CASHSHOP_ITEM_INFO_NAME_Y+m_nShopMovePosY+CASHSHOP_FONT_LINE_HEIGHT+(CASHSHOP_FONT_LINE_HEIGHT*(i+1))+23,
				GUI_FONT_COLOR, (char*)(*it).c_str(), 0L);		
			
			i++;
			it++;
		}
//		for(int i=0;i<CASH_SHOP_ITEM_INFO_DES;i++)
//		{
//			if(strlen(buff[i])>0)
//			{
//				int nCharlen = (strlen(buff[i])*CASHSHOP_SIDE_WIDTH_ENGLISH)/2;
//				m_pFontItemInfo[i+2]->DrawText(CASHSHOP_ITEM_INFO_NAME_X+m_nShopMovePosX-nCharlen,
//					CASHSHOP_ITEM_INFO_NAME_Y+m_nShopMovePosY+CASHSHOP_FONT_LINE_HEIGHT+(CASHSHOP_FONT_LINE_HEIGHT*(i+1))+23,
//					GUI_FONT_COLOR, buff[i], 0L);		
//			}
//		}

		// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
		SHOP_ITEM* pShopInfo = FindCashShopData( m_nCurrentSelectTab, m_pItem->ItemNum );
		if( pShopInfo && pShopInfo->IsLimitedEditionShopItem() && pShopInfo->IsSoldOutShopItem() )
		{
			m_pSoldOut_ToolTip->Move( CASHSHOP_RENDER_START_X + 467, CASHSHOP_RENDER_START_Y + 41 );
			m_pSoldOut_ToolTip->Render();
		}
		// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
	}
}
void CINFCityCashShop::SendBuyItem(ITEM *pItem)
{
	// 아이템 사기
	char buf[512];
	memset(buf, 0x00, 512);
	wsprintf( buf, STRMSG_C_SHOP_0006,pItem->ItemName);//"%s 아이템을 구매 하시겠습니까?"
	m_nGiveTargetCharacterUID = 0;

	//void AddMsgBox(char* strMsg, int nType, DWORD dwData1=0, DWORD dwData2=0, int nLiveTime=0,UID64_t UniqueNumber=0, char* strName=NULL);
	// 2007-10-16 by bhsohn 특정 글씨만 볼드로 처리
	//g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_CASHITEM_BUY);	
	g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_CASHITEM_BUY, 0, 0, 0, 0, pItem->ItemName);	
}
void CINFCityCashShop::SendChargeCash()
{	
	// 2008-04-30 by bhsohn 태국 버전 추가
//#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM) || defined(YEDANG_RELEASE)|| defined(LANGUAGE_CHINA) 
//	// 2006-06-23 by ispark, 충전 홈페이지 메세지 박스 출력
//	g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060623_0000, _MESSAGE);
//
//#else
//	// 캐쉬 충전하기
//	g_pD3dApp->ShowWebWindow();
//#endif
	// end 2008-04-30 by bhsohn 태국 버전 추가
}

struct CompareKindCashShop
{
	template<typename T>
		bool operator()(const T pPtr1, const T pPtr2)
	{
		ITEM* pITEM1 = g_pDatabase->GetServerItemInfo(pPtr1.nItemNum);
		ITEM* pITEM2 = g_pDatabase->GetServerItemInfo(pPtr2.nItemNum);
		if( pITEM1 == NULL || pITEM2 == NULL )
		{
			return false;
		}
		if(pITEM1->Kind < pITEM2->Kind)
		{
			return true;
		}
		else if(pITEM1->Kind == pITEM2->Kind)
		{
			if(pITEM1->ReqMinLevel < pITEM2->ReqMinLevel)
			{
				return true;
			}
			else if(pITEM1->ReqMinLevel == pITEM2->ReqMinLevel)
			{
				if(pITEM1->ItemNum < pITEM2->ItemNum)
				{
					return true;
				}
			}
		}
		return false;
	}
};

void CINFCityCashShop::CashItemSort()
{
	for(int i=0; i<MAX_CASH_SHOP_TAB; i++)
	{
		sort(m_vecImgCashIcon[i].begin(), m_vecImgCashIcon[i].end(), CompareKindCashShop());
	}
}

// 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템
void	CINFCityCashShop::UpdateCashItemRemainCount( ItemNum_t nItemNum, INT nRemainCount )
{
	for( int i=0; i<MAX_CASH_SHOP_TAB; ++i )
	{
		SHOP_ITEM* pItem = FindCashShopData( i, nItemNum );
		if( pItem )
			pItem->RemainCountForLimitedEdition	= nRemainCount;
	}
}
// end 2010. 01. 27 by ckPark 캐쉬 아이템 한정 판매 시스템

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityCashShop::FindCashShopData(int nTabIndex, SHOP_ITEM *pCashShop)
/// \brief		캐쉬 데이타 검색
/// \author		ispark
/// \date		2006-01-11 ~ 2006-01-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
// 2009-01-28 by bhsohn 캐쉬샵 처리
SHOP_ITEM* CINFCityCashShop::FindCashShopData(int nTabIndex, UINT ItemNum)
{
	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[nTabIndex].begin();
	while(it != m_vecItemInfo[nTabIndex].end())
	{
		SHOP_ITEM* pitCashShop = *it;
		if(ItemNum == pitCashShop->ItemNum)
		{
			return pitCashShop;
		}

		it++;
	}
	
	return NULL;
}
void CINFCityCashShop::InputCashColorShopItem()
{
	// 2009-01-28 by bhsohn 캐쉬샵 처리
	// 칼라상점 선택시 클라이언트 내에서 검색후 아이템 설정
// 	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[CASHSHOP_ITEM_SKIN_ITEM].begin();
// 	while(it != m_vecItemInfo[CASHSHOP_ITEM_SKIN_ITEM].end())
// 	{
// 		SHOP_ITEM* pItem = *it;
// 		delete pItem;
// 		pItem = NULL;
// 		it++;
// 	}
// 	m_vecItemInfo[CASHSHOP_ITEM_SKIN_ITEM].clear();
// 	CashItemIcon pTemp;
// 	CItemInfo *pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(POS_CENTER);
// 	if(pItemInfo)
// 	{
// 		for(int i=1; i <= g_pD3dApp->GetUnitArmorColorMax(); i++)
// 		{			
// 			ITEM *item = g_pDatabase->GetServerItemInfo(SOURCEINDEXTOITEMNUM(pItemInfo->ItemInfo->SourceIndex, i));
// 			if(item)
// 			{
// 				if(COMPARE_BIT_FLAG(item->ItemAttribute, ITEM_ATTR_CASH_ITEM))
// 				{
// 					SHOP_ITEM* pItemShop = new SHOP_ITEM;
// 					pItemShop->ItemNum							= item->ItemNum;
// 					strcpy(pItemShop->ItemName, item->ItemName);
// 					pItemShop->MinTradeQuantity					= item->MinTradeQuantity;
// 					pItemShop->Price							= item->CashPrice;
// 					pItemShop->ItemKind							= item->Kind;
// 					m_vecItemInfo[CASHSHOP_ITEM_SKIN_ITEM].push_back(pItemShop);
// 
// 					pTemp.nItemNum = item->ItemNum;
// 					
// 					// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
// 					//pTemp.vecImgCashIcon = g_pGameMain->m_pItemInfo->FindBigIcon(item->SourceIndex);
// 					pTemp.pDataHeader = NULL;
// 					pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);
// 					
// 					m_vecImgCashIcon[CASHSHOP_ITEM_SKIN_ITEM].push_back(pTemp);
// 				}
// 			}
// 		}
// 	}	
	// CASH_ITEMKIND_COLOR_ITEM(9) 벡터는 무조건 아머가 있다.
	// 최대 벡터수는 10개이므로 9에는 어떤 값도 없다.
	ReLoadSkinItemVector();
	
	RefreshGetSkinItemIndex();	// 상점 정보 갱신		
	int nVecPos = 0;	// 가장 앞에있는 벡터의 크기
	if(m_vecImgCashIcon[nVecPos].size() == 0)
	{
		nVecPos = GetNonEmptyNextIndex(0);	// 가장 앞에있는 벡터의 크기
	}
	// 2009-03-02 by bhsohn 캐쉬샵 버그 수정
	m_pScroll->Reset();
	// end 2009-03-02 by bhsohn 캐쉬샵 버그 수정
	m_pScroll->SetNumberOfData( m_vecImgCashIcon[nVecPos].size() );
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	// 2009-03-02 by bhsohn 캐쉬샵 버그 수정
	{
		// 아이템 받기 완료
		int nSelTab = GetTabToItemIdx(m_nCurrentSelectTab);
		if(nSelTab != -1)
		{
			UpdateGiftButton(nSelTab, m_nItemSelect);
		}
	}
	// end 2009-03-02 by bhsohn 캐쉬샵 버그 수정
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityCashShop::RefreshGetSkinItemIndex()
/// \brief		
/// \author		// 2009-01-28 by bhsohn 캐쉬샵 처리
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityCashShop::ReLoadSkinItemVector()
{
	if(m_vecItemInfo[CASH_ITEMKIND_COLOR_ITEM].empty())
	{
		// 아머 정보가 없으면 갱신을 안한다.
		return;
	}
	vector<SHOP_ITEM*>::iterator it = m_vecItemInfo[CASH_ITEMKIND_COLOR_ITEM].begin();
	while(it != m_vecItemInfo[CASH_ITEMKIND_COLOR_ITEM].end())
	{
		SHOP_ITEM* pItem = *it;
		delete pItem;
		pItem = NULL;
		it++;
	}	
	m_vecItemInfo[CASH_ITEMKIND_COLOR_ITEM].clear();

	// 2009-01-28 by bhsohn 캐쉬샵 처리
	{
		vector<CashItemIcon>::iterator itImg = m_vecImgCashIcon[CASH_ITEMKIND_COLOR_ITEM].begin();
		while(itImg != m_vecImgCashIcon[CASH_ITEMKIND_COLOR_ITEM].end())
		{			
			SAFE_DELETE(itImg->pDataHeader);
			
			if((CINFImage*)itImg->vecImgCashIcon != NULL)
			{
				(CINFImage*)itImg->vecImgCashIcon->DeleteDeviceObjects();
				SAFE_DELETE((CINFImage*)itImg->vecImgCashIcon);
			}
			itImg++;
		}
		m_vecImgCashIcon[CASH_ITEMKIND_COLOR_ITEM].clear();
	}
	// end 2009-01-28 by bhsohn 캐쉬샵 처리

	CashItemIcon pTemp;
	CItemInfo *pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(POS_CENTER);
	if(pItemInfo)
	{
		for(int i=1; i <= g_pD3dApp->GetUnitArmorColorMax(); i++)
		{			
			ITEM *item = g_pDatabase->GetServerItemInfo(SOURCEINDEXTOITEMNUM(pItemInfo->ItemInfo->SourceIndex, i));
			if(item)
			{
				if(COMPARE_BIT_FLAG(item->ItemAttribute, ITEM_ATTR_CASH_ITEM))
				{
					SHOP_ITEM* pItemShop = new SHOP_ITEM;
					pItemShop->ItemNum							= item->ItemNum;
					strcpy(pItemShop->ItemName, item->ItemName);
					pItemShop->MinTradeQuantity					= item->MinTradeQuantity;
					pItemShop->Price							= item->CashPrice;
					pItemShop->ItemKind							= item->Kind;
					m_vecItemInfo[CASH_ITEMKIND_COLOR_ITEM].push_back(pItemShop);
					
					pTemp.nItemNum = item->ItemNum;
					
					// 캐쉬 아이템 alt+tab버그 수정					
					pTemp.pDataHeader = NULL;
					pTemp.vecImgCashIcon = FindCashIcon(item->SourceIndex, pTemp.pDataHeader);
					
					m_vecImgCashIcon[CASH_ITEMKIND_COLOR_ITEM].push_back(pTemp);
				}
			}
		}
	}	

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFItemInfo::LoadNPCImage(int nNPCIndex)
/// \brief		
/// \author		// 2007-08-21 by bhsohn 캐쉬 아이템 alt+tab버그 수정
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CINFImage* CINFCityCashShop::FindCashIcon(int nItemNum, DataHeader*	pDataHeader)
{			
	SAFE_DELETE(pDataHeader);
	CGameData gameData;
	gameData.SetFile( ".\\Res-Tex\\bigitem.tex", FALSE, NULL, 0, FALSE );
	char szName[32];
	wsprintf(szName, "%08d", nItemNum);
	pDataHeader = gameData.FindFromFile(szName);
	if(pDataHeader == NULL)
	{
		return NULL;
	}
	CINFImage *pImage = new CINFImage;
	pImage->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	pImage->RestoreDeviceObjects();
	return pImage;
}
void CINFCityCashShop::SendMsgGift(MSG_FC_SHOP_CHECK_GIVE_TARGET_OK* pMsg)
{
	char buf[SIZE_MAX_STRING_256];
	wsprintf(buf,STRMSG_C_071115_0101,m_pItem->ItemName);
	m_nGiveTargetCharacterUID = pMsg->GiveTargetCharUID;
	g_pGameMain->m_pInfWindow->AddMsgBox(buf,_Q_GIFT_ITEM,0,0,0,0,m_pItem->ItemName);	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFItemInfo::LoadNPCImage(int nNPCIndex)
/// \brief		
/// \author		// 2009-01-28 by bhsohn 캐쉬샵 처리
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityCashShop::UpdateGiftButton(int i_nCurrentSelectTab, int i_nItemSelect)
{		
	if(NULL == m_pImgGiftButton)
	{
		return;
	}
	int nSelectTotalIdx = i_nItemSelect + m_pScroll->GetCurrentScrollIndex();

	if((i_nCurrentSelectTab < 0)
		|| (i_nCurrentSelectTab >= (MAX_CASH_SHOP_TAB-1))
		|| (m_vecImgCashIcon[i_nCurrentSelectTab].size() <= nSelectTotalIdx))
	{
		// 초과 방지
		m_pImgGiftButton->EnableBtn(FALSE);
		return;
	}
	else if(i_nCurrentSelectTab == GetSkinItemIndex())
	{
		// 스킨탭
		m_pImgGiftButton->EnableBtn(FALSE);
		return;
	}
		
	SHOP_ITEM* pShotItem = m_vecItemInfo[i_nCurrentSelectTab][nSelectTotalIdx];
	if(!pShotItem)
	{
		m_pImgGiftButton->EnableBtn(FALSE);
		return;
	}	

	BOOL bEnableGift = TRUE;
	if(pShotItem->ItemNum == 0)
	{
		bEnableGift = FALSE;
	}
	else
	{
		ITEM *pSelItem = g_pDatabase->GetServerItemInfo(pShotItem->ItemNum);
		if(pSelItem)
		{
			if(COMPARE_BIT_FLAG(pSelItem->ItemAttribute, ITEM_ATTR_CASH_ITEM_PREMIUM_CARD))
			{
				// 프리미엄 카드는 선물하기 불가
				bEnableGift = FALSE;
			}
		}
	}	

	m_pImgGiftButton->EnableBtn(bEnableGift);	

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityCashShop::RefreshGetSkinItemIndex()
/// \brief		
/// \author		// 2009-01-28 by bhsohn 캐쉬샵 처리
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityCashShop::RefreshGetSkinItemIndex()
{		
	// 정렬을 한다.	
	int nTapIdx = 0;	
	{		
		int nNextTap = 0;
		int nTap = 0;
		int nCnt = 0;
		BOOL bSelIdx[MAX_CASH_SHOP_TAB];
		for(nTap = 0;nTap < (MAX_CASH_SHOP_TAB);nTap++)
		{
			m_nTabToItemIdx[nTap] = -1;		
			bSelIdx[nTap] = FALSE;
		}	
		
		for(nTap = 0;nTap < (MAX_CASH_SHOP_TAB-1);nTap++)
		{			
			if(bSelIdx[nTap])
			{
				// 이미 선택한 아이템 
				continue;
			}
			if(m_vecItemInfo[nTap].size() > 0)
			{
				m_nTabToItemIdx[nTapIdx] = nTap;
				bSelIdx[nTap] = TRUE;		// 선택되었다.
				nTapIdx++;
			}
			else
			{
				// 현재 탭이 0이면 다음에 0이 아닌 텝을 찾는다.
				nNextTap = GetNonEmptyNextIndex(nTap);
				if(nTap != nNextTap && !bSelIdx[nNextTap])	// 한번도 안선택한 탭이다.
				{
					//SwapItemVector(nTap, nNextTap); // 같으면 이동할 필요가 없다.
					m_nTabToItemIdx[nTapIdx] = nNextTap;
					bSelIdx[nNextTap] = TRUE;		// 선택되었다.
					nTapIdx++;					
				}
			}			
		}
	}
	m_nSkinItemIdx = -2;	//

	// 빈 벡터를 찾는다.	
	if(m_vecItemInfo[CASH_ITEMKIND_COLOR_ITEM].size() > 0)	// 전에 스킨 벡터에 값이 있었다.
	{			
		m_nSkinItemIdx = CASH_ITEMKIND_COLOR_ITEM;
	}	
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityCashShop::RefreshGetSkinItemIndex()
/// \brief		
/// \author		// 2009-01-28 by bhsohn 캐쉬샵 처리
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityCashShop::GetSkinItemIndex()
{
	return m_nSkinItemIdx;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityCashShop::RefreshGetSkinItemIndex()
/// \brief		
/// \author		// 2009-01-28 by bhsohn 캐쉬샵 처리
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityCashShop::GetNonEmptyNextIndex(int i_nStartIdx)
{
	int nNonEmptyIdx = i_nStartIdx;
	int nTap = 0;
	for(nTap = (i_nStartIdx+1);nTap < (MAX_CASH_SHOP_TAB-1);nTap++)
	{
		if(m_vecItemInfo[nTap].size() > 0)
		{
			// 크기가 0이 아닌 템을 리턴한다.
			nNonEmptyIdx = nTap;
			break;
		}

	}
	return nNonEmptyIdx;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityCashShop::RefreshGetSkinItemIndex()
/// \brief		
/// \author		// 2009-01-28 by bhsohn 캐쉬샵 처리
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityCashShop::GetTabToItemIdx(int i_nIdx)
{
	if(i_nIdx < 0 || i_nIdx >= MAX_CASH_SHOP_TAB)
	{
		return -1;
	}
	return m_nTabToItemIdx[i_nIdx];
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityCashShop::RenderNewShopInfo(int i_nPosX, int i_nPosY, SHOP_ITEM* i_pShopInfo)
/// \brief		
/// \author		// 2009-01-28 by bhsohn 캐쉬샵 처리
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityCashShop::RenderNewShopInfo(int i_nPosX, int i_nPosY, SHOP_ITEM* i_pShopInfo)
{
	m_fNewPlayTime -= g_pD3dApp->GetCheckElapsedTime();

	if(m_fNewPlayTime < 0)
	{
		m_fNewPlayTime = 1.0f;
		m_nNewPlayIndex++;
		if(m_nNewPlayIndex >= MAX_NEW_CASHSHOP_IMAGE)
		{
			m_nNewPlayIndex = 0;
		}
	}		
	BYTE byCashIndex = GET_TABINDEX_BY_CASHSHOPINDEX(i_pShopInfo->CashShopIndex);
	BYTE byReNewIndex = GET_CASHSHOP_BIT_BY_CASHSHOPINDEX(i_pShopInfo->CashShopIndex);

	if(!IS_NEW_CASHSHOPITEM_BY_CASHSHOPINDEX(byReNewIndex))
	{
		// 신총 아이템이 아니다.
		return;
	}
	else if(NULL == m_pImgNewTab[m_nNewPlayIndex])
	{
		return;
	}	
	int nPosX = i_nPosX;
	int nPosY = i_nPosY;
	m_pImgNewTab[m_nNewPlayIndex]->Move(nPosX, nPosY);
	m_pImgNewTab[m_nNewPlayIndex]->Render();
				
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityCashShop::RenderNewShopInfo(int i_nPosX, int i_nPosY, SHOP_ITEM* i_pShopInfo)
/// \brief		
/// \author		// 2009-02-24 by bhsohn 캐쉬샵 충전 웹페이지 추가
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityCashShop::OnClickCashChargeBtn()
{
	g_pD3dApp->PopupWebWindow(TRUE);
}
