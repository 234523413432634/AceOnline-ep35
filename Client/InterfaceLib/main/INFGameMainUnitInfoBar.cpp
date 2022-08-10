// INFGameMainUnitInfoBar.cpp: implementation of the CINFGameMainUnitInfoBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFGameMainUnitInfoBar.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "SceneData.h"
#include "D3DHanFont.h"
#include "Background.h"
#include "AtumDatabase.h"
#include "dxutil.h"
#include "PkNormalTimer.h"
#include "QuestData.h"
#include "INFGameMain.h"
#include "INFWindow.h"
#include "INFWeaponInfo.h"
#include "INFGameMainChat.h"

#define GAMEMAIN_GAGE_EXP_LENGTH					219//110// 미정

#define GAMEMAIN_BACK_GAGE_UP_SIZE_X				179
#define GAMEMAIN_BACK_GAGE_UP_SIZE_Y				48

#define GAMEMAIN_BACK_MINIMAP_SIZE_X				145
#define GAMEMAIN_BACK_MINIMAP_SIZE_Y				69
#define GAMEMAIN_BACK_MINIMAP_START_X				(g_pD3dApp->GetBackBufferDesc().Width - GAMEMAIN_BACK_MINIMAP_SIZE_X)
#define GAMEMAIN_BACK_MINIMAP_START_Y				0

#define GAMEMAIN_BACK_UP_SIZE_Y						22	// 화면 상단
#define GAMEMAIN_BACK_DOWN_SIZE_Y					39	// 화면 하단
#define GAMEMAIN_BACK_DOWN_START_Y					(g_pD3dApp->GetBackBufferDesc().Height - GAMEMAIN_BACK_DOWN_SIZE_Y)

#define GAMEMAIN_EXP_GAGE_START_X					((g_pD3dApp->GetBackBufferDesc().Width - 219)/2)
#define GAMEMAIN_EXP_GAGE_START_Y					(GAMEMAIN_BACK_DOWN_START_Y - 9)

#define GAMEMAIN_UNIT_POS_START_X					(g_pD3dApp->GetBackBufferDesc().Width - 30)
#define GAMEMAIN_UNIT_POS_START_Y					5

#define GAMEMAIN_BACK_GAGE_EXP_START_X				((g_pD3dApp->GetBackBufferDesc().Width - 234)/2)
#define GAMEMAIN_BACK_GAGE_EXP_START_Y				(GAMEMAIN_BACK_DOWN_START_Y - 12)

#define GAMEMAIN_STRING_FUEL_START_X				22

#define GAMEMAIN_STRING_EXP_START_X					((g_pD3dApp->GetBackBufferDesc().Width)/2 - 35)

// 스트링 위치 정의
#define GAMEMAIN_NEW_STRING_HP_START_X				17
#define GAMEMAIN_NEW_STRING_HP_START_Y				80
#define GAMEMAIN_GAGE_HP_UP_START_X					21
#define GAMEMAIN_GAGE_HP_UP_START_Y					92
#define GAMEMAIN_NEW_STRING_MAX_HP_START_Y			104
#define GAMEMAIN_NEW_STRING_DP_START_Y				80
#define GAMEMAIN_GAGE_DP_UP_START_X					114
#define GAMEMAIN_GAGE_DP_UP_START_Y					92
#define GAMEMAIN_NEW_STRING_MAX_DP_START_X			108
#define GAMEMAIN_NEW_STRING_MAX_DP_START_Y			104
#define GAMEMAIN_GAGE_SP_UP_START_X					130
#define GAMEMAIN_GAGE_SP_UP_START_Y					50
#define GAMEMAIN_NEW_STRING_MAX_SP_START_Y			62


// 메인 게이지 관련 정의

#define GAMEMAIN_GAGE_HP_START_X					15
#define GAMEMAIN_GAGE_HP_START_Y					29
#define GAMEMAIN_GAGE_DP_START_X					83
#define GAMEMAIN_GAGE_DP_START_Y					29
#define GAMEMAIN_GAGE_SP_START_X					120
#define GAMEMAIN_GAGE_SP_START_Y					22
#define GAMEMAIN_GAGE_BOOSTER_START_X				9
#define GAMEMAIN_GAGE_BOOSTER_START_Y				21
#define GAMEMAIN_GAGE_FUEL_START_X					6
#define GAMEMAIN_GAGE_FUEL_START_Y					5
#define GAMEMAIN_VOICECHAT_X						(g_pD3dApp->GetBackBufferDesc().Width-32)
#define GAMEMAIN_VOICECHAT_Y						(156)
#define GAMEMAIN_VOICECHAT_W						26
#define GAMEMAIN_VOICECHAT_H						26


// SPEED 스트링 관련 정의
#define SPEED_STRING_START_X						80	
#define SPEED_STRING_START_Y						90
#define SPEED_STRING_WIDTH							19
#define SPEED_STRING_HEIGHT							17

// 맵이름 관련 정의
#define GAME_MAP_NAME_RENDER_X						(g_pD3dApp->GetBackBufferDesc().Width-30)
#define GAME_MAP_NAME_RENDER_Y						4
#define GAME_MAP_NAME_TEXT_COLOR					RGB(200,200,200)
#define GAME_UNIT_POS_COLOR							RGB(200,200,200)

// 레이더 위치 정의
#define RADER_CENTER_POS_X							(g_pD3dApp->GetBackBufferDesc().Width-75)	
#define RADER_CENTER_POS_Y							82 + 16
#define RADER_RADIUS								64

#define GAME_EVENT_BASICPOS_X						192
#define GAME_EVENT_BASICPOS_Y						32

// 2006-03-07 by ispark, 언어에 따라 위치 수정
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn 태국 버전 추가
#define GAMEMAIN_STRING_FUEL_START_Y				3//5
#define GAMEMAIN_STRING_EXP_START_Y					(GAMEMAIN_BACK_DOWN_START_Y - 13)//11)
#define GAMEMAIN_NEW_STRING_MAX_HP_START_X			25//21
#define GAMEMAIN_NEW_STRING_DP_START_X				112//114
#define GAMEMAIN_NEW_STRING_MAX_SP_START_X			135//130
#define GAMEMAIN_EVENT_FONT_Y						2
#else
#define GAMEMAIN_STRING_FUEL_START_Y				3//5
#define GAMEMAIN_STRING_EXP_START_Y					(GAMEMAIN_BACK_DOWN_START_Y - 13)//11)
#define GAMEMAIN_NEW_STRING_MAX_HP_START_X			25//21
#define GAMEMAIN_NEW_STRING_DP_START_X				112//114
#define GAMEMAIN_NEW_STRING_MAX_SP_START_X			135//130
#define GAMEMAIN_EVENT_FONT_Y						2//0
#endif


#define INFOMAIN_GIFT_ICON_X				70
#define INFOMAIN_GIFT_CITY_ICON_Y			130
#define INFOMAIN_GIFT_FIELD_ICON_Y			89

// 2008-03-25 by dgwoo 모선전 진행 버튼.
#define MOTHERSHIP_BUTTON_X					(nBoldPosX+nBalonWidth)
#define MOTHERSHIP_BUTTON_Y					(nBoldPosY)



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFGameMainUnitInfoBar::CINFGameMainUnitInfoBar(CAtumNode* pParent)
{
	m_pParent = pParent;
	m_bRestored = FALSE;
	m_bWarning = FALSE;
	m_v2RaderCenter.x = RADER_CENTER_POS_X;
	m_v2RaderCenter.y = RADER_CENTER_POS_Y;
	m_v2MousePt.x = g_pD3dApp->GetBackBufferDesc().Width/2;
	m_v2MousePt.y = g_pD3dApp->GetBackBufferDesc().Height/2;

	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL] = NULL;
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL] = NULL;

	m_pImgBackMinimap = NULL;
	m_pFontUnitPosInfo = NULL;
	m_fWarningTime = 0;

	memset(m_fGageRate, 0x00, sizeof(float)*GAMEMAIN_GAGE_NUMBER);
	memset(m_pFontGageInfo, 0x00, sizeof(DWORD)*GAMEMAIN_GAGE_LINE_NUMBER);
	memset(m_szGageInfo, 0x00, GAMEMAIN_GAGE_LINE_NUMBER*GAMEMAIN_GAGE_LINE_LENGTH);
//	memset(m_pButtonShowHide, 0x00, sizeof(DWORD)*2*BUTTON_STATE_NUMBER);

	m_nButtonState = BUTTON_STATE_NORMAL;

	// 2004-12-08 by jschoi
	m_pImgMainGageBack = NULL;
	m_pImgMainExpBack = NULL;
	m_pImgMainExpBar = NULL;
	m_pImgMainSpeedNum = NULL;
	m_pImgMainMinus = NULL;
	m_pImgMainWarning = NULL;
	m_pImgGeneralPremiumCard = NULL;

	// 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가

	m_bPremiumToolTip = FALSE;

	// end 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가

	m_pImgSuperPremiumCard = NULL;
	m_pImgHappyHourEvent = NULL;
	m_pImgPCHappyHourEvent = NULL;
	// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	m_pImgPCHomePremiumEvent = NULL;
	//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	m_pImgVoiceChatIcon = NULL;

	int i;
	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		m_pImgEventRecovery[i] = NULL;
	}
	for( i = 0; i < GIFT_ICON_IMG_COUNT; i++)
	{
		m_pImgGiftIcon[i] = NULL;
	}

	memset(m_pImgMainGageHP,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_HP_MAX_GRADE);
	memset(m_pImgMainGageDP,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_DP_MAX_GRADE);
	memset(m_pImgMainGageSP,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_SP_MAX_GRADE);
	memset(m_pImgMainGageBooster,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_BOOSTER_MAX_GRADE);
	memset(m_pImgMainGageFuel,0x00,sizeof(DWORD)*GAMEMAIN_GAGE_FUEL_MAX_GRADE);
	memset(m_pImgMainIconFuel,0x00,sizeof(DWORD)*2);
	
	m_pFontMapName = NULL;
	m_pFontCurrentEvent = NULL;
	m_pFontEventHappyHour = NULL;
	m_pFontEventRecovery = NULL;
	m_bRenderEvent = FALSE;
	m_nHappyHourX = 0;
	m_nHappyHourY = 0;
	m_bRenderEventRecovery = FALSE;
	
	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	//m_BHappyHourEvent = 0x00;
	m_byHappyHourInfluence = 0x00;
	m_bPcBangHappyHour = FALSE;
	// end 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경

	m_bMemberPCBang = FALSE;	
	// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	m_pMemberPremiumEvent = FALSE;
	//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업

	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	memset(&m_HappyEventInfo, 0x00, sizeof(EVENT_INFO));				//세력 진형
	memset(&m_HappyEventAllInfluInfo, 0x00, sizeof(EVENT_INFO));		// 전체 진형
	memset(&m_PCHappyEventInfo, 0x00, sizeof(EVENT_INFO));				// pc방 
	m_bHappyHourAllInfluence = FALSE;

	m_vecGiftMsg.clear();
	m_fGiftTime = 0.0f;

	// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
	m_bMotherHappyHour = FALSE;
	memset(&m_MotherShipEventInfo, 0x00, sizeof(EVENT_INFO));

	m_bItemHappyHour = FALSE;
	memset(&m_ItemEventInfo, 0x00, sizeof(EVENT_INFO));
	// end 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가

	// 2008-10-20 by bhsohn VOIP 버그 수정
	m_pImgVoiceSPKIcon = NULL;
	
}

CINFGameMainUnitInfoBar::~CINFGameMainUnitInfoBar()
{
	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]);
	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]);

	SAFE_DELETE(m_pImgBackMinimap);
	SAFE_DELETE(m_pFontUnitPosInfo);

	int i=0;
	for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
	{
		SAFE_DELETE(m_pFontGageInfo[i]);
	}	

//	for(i=0;i<BUTTON_STATE_NUMBER;i++)
//	{
//		SAFE_DELETE(m_pButtonShowHide[0][i]);
//		SAFE_DELETE(m_pButtonShowHide[1][i]);
//	}

	// 2004-12-08 by jschoi
	SAFE_DELETE(m_pImgMainGageBack);
	SAFE_DELETE(m_pImgMainExpBack);
	SAFE_DELETE(m_pImgMainExpBar);
	SAFE_DELETE(m_pImgMainSpeedNum);
	SAFE_DELETE(m_pImgMainMinus);
	SAFE_DELETE(m_pImgMainWarning);
	SAFE_DELETE(m_pImgGeneralPremiumCard);
	SAFE_DELETE(m_pImgSuperPremiumCard);
	SAFE_DELETE(m_pImgHappyHourEvent);
	SAFE_DELETE(m_pImgPCHappyHourEvent);
	// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	SAFE_DELETE(m_pImgPCHomePremiumEvent);
	//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	SAFE_DELETE(m_pImgVoiceChatIcon);
	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		SAFE_DELETE(m_pImgEventRecovery[i]);
	}
	for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
	{
		SAFE_DELETE(m_pImgGiftIcon[i]);
	}
	for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
	{
		SAFE_DELETE(m_pImgMainGageHP[i]);
		SAFE_DELETE(m_pImgMainGageDP[i]);
		SAFE_DELETE(m_pImgMainGageSP[i]);
	}
	for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
	{
		SAFE_DELETE(m_pImgMainGageBooster[i]);
	}
	for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
	{
		SAFE_DELETE(m_pImgMainGageFuel[i]);
	}
	for(i=0;i<2;i++)
	{
		SAFE_DELETE(m_pImgMainIconFuel[i]);
	}

	SAFE_DELETE(m_pFontMapName);
	SAFE_DELETE(m_pFontCurrentEvent);
	SAFE_DELETE(m_pFontEventHappyHour);
	SAFE_DELETE(m_pFontEventRecovery);
	m_vecGiftMsg.clear();
}

void CINFGameMainUnitInfoBar::UpdateAllGage()
{

	SetHP((float)g_pShuttleChild->m_myShuttleInfo.CurrentHP, (float)g_pShuttleChild->m_myShuttleInfo.HP);
	SetDP((float)g_pShuttleChild->m_myShuttleInfo.CurrentDP, (float)g_pShuttleChild->m_myShuttleInfo.DP);
	SetBURN((float)g_pShuttleChild->m_fCurrentBURN, (float)g_pShuttleChild->m_fBURN);
	SetSP((float)g_pShuttleChild->m_myShuttleInfo.CurrentSP, (float)g_pShuttleChild->m_myShuttleInfo.SP);
	SetEP((float)g_pShuttleChild->m_myShuttleInfo.CurrentEP, (float)g_pShuttleChild->m_myShuttleInfo.EP);
	SetSpeed( g_pShuttleChild->m_fShuttleSpeed, 
			g_pShuttleChild->m_fRealShuttleSpeedMin, 
			g_pShuttleChild->m_fRealShuttleSpeedBoosterOn );
}

void CINFGameMainUnitInfoBar::SetHP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_HP], STRMSG_C_INTERFACE_0022);//"에너지"
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_HP_UP], "%4d", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_HP], "/%d", (int)fMax);
	m_fGageRate[GAMEMAIN_GAGE_HP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetDP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_DP], STRMSG_C_INTERFACE_0023);//"쉴드"
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_DP_UP], "%d", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_DP], "/%d", (int)fMax);
	m_fGageRate[GAMEMAIN_GAGE_DP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetBURN(float fCurrent, float fMax)
{
	m_fGageRate[GAMEMAIN_GAGE_BURN_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetSP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_SP_UP], "%4d/", (int)fCurrent);
	wsprintf(m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_SP], "%4d", (int)fMax);
	m_fGageRate[GAMEMAIN_GAGE_SP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetEP(float fCurrent, float fMax)
{
	if(fMax< fCurrent)
		fCurrent = fMax;
	wsprintf(m_szGageInfo[GAMEMAIN_GAGE_EP_UP], "%d/%d", (int)fCurrent, (int)fMax);
	m_fGageRate[GAMEMAIN_GAGE_EP_UP] = fCurrent/fMax;
}

void CINFGameMainUnitInfoBar::SetEXP(float fExp)
{
	// 2006-02-07 by ispark
	fExp = min(99.99f, fExp);
	fExp = max(0.00f, fExp);
	sprintf(m_szGageInfo[GAMEMAIN_GAGE_EXP_UP], "Lv.%d  %5.2f%%",g_pShuttleChild->m_myShuttleInfo.Level, fExp);
	m_fGageRate[GAMEMAIN_GAGE_EXP_UP] = fExp/100.0f;
}

void CINFGameMainUnitInfoBar::SetSpeed(float fCurrent, float fMin, float fMax)
{
	if(fMin > 0)
	{
		fMin = 0;// 최소 값은 0으로 한다.음수인 경우를 대비해서 이 값을 사용한다.
	}
	m_fGageRate[GAMEMAIN_GAGE_SPEED_UP] = (fCurrent-fMin)/(fMax-fMin);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourEvent(BOOL bStart)
/// \brief		이벤트 관련 아이콘들의 위치를 셋팅해주는 함수.
/// \author		dgwoo
/// \date		2007-01-25 ~ 2007-01-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourEventIconPos()
{
	// 해피아워 이벤트.
	if(g_pD3dApp->GetTestServerFlag() == FALSE)
	{
		m_nHappyHourX = g_pD3dApp->GetBackBufferDesc().Width - GAME_EVENT_BASICPOS_X;
	}
	else
	{
		m_nHappyHourX = g_pD3dApp->GetBackBufferDesc().Width - 120;
	}
	// PC방 가맹점.
	m_nPCHappyHourX = g_pD3dApp->GetBackBufferDesc().Width - 64;
}

HRESULT CINFGameMainUnitInfoBar::InitDeviceObjects()
{
	ASSERT_ASSERT(m_pGameData);
	DataHeader *pDataHeader = m_pGameData->Find("mnupbkpx");
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL] = new CINFImage;
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("mndnbkpx");
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL] = new CINFImage;
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("mnMinibk");
	m_pImgBackMinimap = new CINFImage;
	m_pImgBackMinimap->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	char buf[64];
	int i=0;
	for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
	{
		m_pFontGageInfo[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 8, D3DFONT_ZENABLE, TRUE, 256, 32);
		m_pFontGageInfo[i]->InitDeviceObjects(g_pD3dDev) ;
	}	

	m_pFontUnitPosInfo = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 8, D3DFONT_ZENABLE, FALSE, 256, 32);
	m_pFontUnitPosInfo->InitDeviceObjects(g_pD3dDev) ;
//	for(i=0;i<BUTTON_STATE_NUMBER;i++)
//	{
//		wsprintf( buf, "mnShow%02d", i);
//		pDataHeader = m_pGameData->Find(buf);
//		m_pButtonShowHide[GAMEMAIN_BUTTON_SHOW][i] = new CINFImage;
//		m_pButtonShowHide[GAMEMAIN_BUTTON_SHOW][i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
//		wsprintf( buf, "mnHide%02d", i);
//		pDataHeader = m_pGameData->Find(buf);
//		m_pButtonShowHide[GAMEMAIN_BUTTON_HIDE][i] = new CINFImage;
//		m_pButtonShowHide[GAMEMAIN_BUTTON_HIDE][i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
//	}

	// 2004-12-08 by jschoi
	pDataHeader = m_pGameData->Find("MainGB");
	m_pImgMainGageBack = new CINFImage;
	m_pImgMainGageBack->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("expbac");
	m_pImgMainExpBack = new CINFImage;
	m_pImgMainExpBack->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("expbar");
	m_pImgMainExpBar = new CINFImage;
	m_pImgMainExpBar->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("speedm");
	m_pImgMainSpeedNum = new CINFImage;
	m_pImgMainSpeedNum->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("sMin");
	m_pImgMainMinus = new CINFImage;
	m_pImgMainMinus->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("warn");
	m_pImgMainWarning = new CINFImage;
	m_pImgMainWarning->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("capri");
	m_pImgGeneralPremiumCard = new CINFImage;
	m_pImgGeneralPremiumCard->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	pDataHeader = m_pGameData->Find("caspri");
	m_pImgSuperPremiumCard = new CINFImage;
	m_pImgSuperPremiumCard->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	
	pDataHeader = m_pGameData->Find("ehapp_h");
	m_pImgHappyHourEvent = new CINFImage;
	m_pImgHappyHourEvent->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	
	pDataHeader = m_pGameData->Find("epchapp");
	m_pImgPCHappyHourEvent = new CINFImage;
	m_pImgPCHappyHourEvent->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	
	// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	pDataHeader = m_pGameData->Find("home_pre");
	m_pImgPCHomePremiumEvent = new CINFImage;
	m_pImgPCHomePremiumEvent->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업

	pDataHeader = m_pGameData->Find("spkicon");
	m_pImgVoiceSPKIcon = new CINFImage;
	m_pImgVoiceSPKIcon->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

	if(m_pImgVoiceChatIcon == NULL)
	{
		// 2008-10-20 by bhsohn VOIP 버그 수정
//		m_pImgVoiceChatIcon = new CINFImageBtn;
//		m_pImgVoiceChatIcon->InitDeviceObjects("voiceicon");
		pDataHeader = m_pGameData->Find("voiceicon");
		m_pImgVoiceChatIcon = new CINFImage;
		m_pImgVoiceChatIcon->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	}
	

	for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
	{
		wsprintf( buf, "ene%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageHP[i] = new CINFImage;
		m_pImgMainGageHP[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

		wsprintf( buf, "she%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageDP[i] = new CINFImage;
		m_pImgMainGageDP[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);

		wsprintf( buf, "skil%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageSP[i] = new CINFImage;
		m_pImgMainGageSP[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);	
	}

	for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
	{
		wsprintf( buf, "Bost%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageBooster[i] = new CINFImage;
		m_pImgMainGageBooster[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);	
	}

	for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
	{
		wsprintf( buf, "fue%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainGageFuel[i] = new CINFImage;
		m_pImgMainGageFuel[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);	
	}

	for(i=0;i<2;i++)
	{
		wsprintf( buf, "fuelG%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgMainIconFuel[i] = new CINFImage;
		m_pImgMainIconFuel[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);	
	}

	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		if(m_pImgEventRecovery)
		{
			wsprintf( buf, "growth%d", i+1);
			pDataHeader = m_pGameData->Find(buf);
			if(pDataHeader)
			{
				m_pImgEventRecovery[i] = new CINFImage;
				m_pImgEventRecovery[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
			}
		}
	}
	for(i=0;i<GIFT_ICON_IMG_COUNT;i++)
	{
		wsprintf( buf, "gift%02d", i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgGiftIcon[i] = new CINFImage;
		m_pImgGiftIcon[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);	
	}
	
	
	m_pFontMapName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);
	m_pFontMapName->InitDeviceObjects(g_pD3dDev);

	m_pFontCurrentEvent = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);
	m_pFontCurrentEvent->InitDeviceObjects(g_pD3dDev);
	
	m_pFontEventHappyHour = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);
	m_pFontEventHappyHour->InitDeviceObjects(g_pD3dDev);
	
	m_pFontEventRecovery = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,512,32);
	m_pFontEventRecovery->InitDeviceObjects(g_pD3dDev);

	return S_OK;
}

HRESULT CINFGameMainUnitInfoBar::RestoreDeviceObjects()
{
	if(!m_bRestored)
	{
		m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->RestoreDeviceObjects();
		m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->RestoreDeviceObjects();
		m_pImgBackMinimap->RestoreDeviceObjects();
		m_pFontUnitPosInfo->RestoreDeviceObjects();
		int i=0;
		for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
		{
			m_pFontGageInfo[i]->RestoreDeviceObjects() ;
		}		
		
//		for(i=0;i<BUTTON_STATE_NUMBER;i++)
//		{
//			m_pButtonShowHide[0][i]->RestoreDeviceObjects();
//			m_pButtonShowHide[1][i]->RestoreDeviceObjects();
//		}

		// 2004-12-08 by jschoi
		m_pImgMainGageBack->RestoreDeviceObjects();
		m_pImgMainExpBack->RestoreDeviceObjects();
		m_pImgMainExpBar->RestoreDeviceObjects();
		m_pImgMainSpeedNum->RestoreDeviceObjects();
		m_pImgMainMinus->RestoreDeviceObjects();
		m_pImgMainWarning->RestoreDeviceObjects();
		m_pImgGeneralPremiumCard->RestoreDeviceObjects();
		m_pImgSuperPremiumCard->RestoreDeviceObjects();
		m_pImgHappyHourEvent->RestoreDeviceObjects();
		m_pImgPCHappyHourEvent->RestoreDeviceObjects();
		// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
		m_pImgPCHomePremiumEvent->RestoreDeviceObjects();
		//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업
		m_pImgVoiceChatIcon->RestoreDeviceObjects();
		m_pImgVoiceSPKIcon->RestoreDeviceObjects();
		//m_pImgVoiceChatIcon->SetBtnPosition(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
		for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
		{
			if(m_pImgEventRecovery[i])
				m_pImgEventRecovery[i]->RestoreDeviceObjects();
		}
		for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
		{
			if(m_pImgGiftIcon[i])
				m_pImgGiftIcon[i]->RestoreDeviceObjects();
		}
		for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
		{
			m_pImgMainGageHP[i]->RestoreDeviceObjects();
			m_pImgMainGageDP[i]->RestoreDeviceObjects();
			m_pImgMainGageSP[i]->RestoreDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
		{
			m_pImgMainGageBooster[i]->RestoreDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
		{
			m_pImgMainGageFuel[i]->RestoreDeviceObjects();	
		}
		
		for(i=0;i<2;i++)
		{
			m_pImgMainIconFuel[i]->RestoreDeviceObjects();
		}

		if(m_pFontMapName)
	         m_pFontMapName->RestoreDeviceObjects();

		if(m_pFontCurrentEvent)
			m_pFontCurrentEvent->RestoreDeviceObjects();
		if(m_pFontEventHappyHour)
			m_pFontEventHappyHour->RestoreDeviceObjects();
		if(m_pFontEventRecovery)
			m_pFontEventRecovery->RestoreDeviceObjects();		

		m_bRestored = TRUE;
	}
	return S_OK;
}

HRESULT CINFGameMainUnitInfoBar::InvalidateDeviceObjects()
{
	if(m_bRestored)
	{
		m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->InvalidateDeviceObjects();
		m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->InvalidateDeviceObjects();
		m_pImgBackMinimap->InvalidateDeviceObjects();
		m_pFontUnitPosInfo->InvalidateDeviceObjects();
		int i=0;
		for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
		{
			m_pFontGageInfo[i]->InvalidateDeviceObjects() ;
		}
//		for(i=0;i<BUTTON_STATE_NUMBER;i++)
//		{
//			m_pButtonShowHide[0][i]->InvalidateDeviceObjects();
//			m_pButtonShowHide[1][i]->InvalidateDeviceObjects();
//		}

		// 2004-12-08 by jschoi
		m_pImgMainGageBack->InvalidateDeviceObjects();
		m_pImgMainExpBack->InvalidateDeviceObjects();
		m_pImgMainExpBar->InvalidateDeviceObjects();
		m_pImgMainSpeedNum->InvalidateDeviceObjects();
		m_pImgMainMinus->InvalidateDeviceObjects();
		m_pImgMainWarning->InvalidateDeviceObjects();
		m_pImgGeneralPremiumCard->InvalidateDeviceObjects();
		m_pImgSuperPremiumCard->InvalidateDeviceObjects();
		m_pImgHappyHourEvent->InvalidateDeviceObjects();
		m_pImgPCHappyHourEvent->InvalidateDeviceObjects();
		// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
		m_pImgPCHomePremiumEvent->InvalidateDeviceObjects();
		//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업
		m_pImgVoiceChatIcon->InvalidateDeviceObjects();
		m_pImgVoiceSPKIcon->InvalidateDeviceObjects();
		for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
		{
			if(m_pImgEventRecovery[i])
				m_pImgEventRecovery[i]->InvalidateDeviceObjects();
		}
		for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
		{
			if(m_pImgGiftIcon[i])
				m_pImgGiftIcon[i]->InvalidateDeviceObjects();
		}
		for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
		{
			m_pImgMainGageHP[i]->InvalidateDeviceObjects();
			m_pImgMainGageDP[i]->InvalidateDeviceObjects();
			m_pImgMainGageSP[i]->InvalidateDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
		{
			m_pImgMainGageBooster[i]->InvalidateDeviceObjects();	
		}

		for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
		{
			m_pImgMainGageFuel[i]->InvalidateDeviceObjects();	
		}
		
		for(i=0;i<2;i++)
		{
			m_pImgMainIconFuel[i]->InvalidateDeviceObjects();
		}

		if(m_pFontMapName )
			m_pFontMapName->InvalidateDeviceObjects();

		if(m_pFontCurrentEvent)
			m_pFontCurrentEvent->InvalidateDeviceObjects();
		if(m_pFontEventHappyHour)
			m_pFontEventHappyHour->InvalidateDeviceObjects();
		if(m_pFontEventRecovery)
			m_pFontEventRecovery->InvalidateDeviceObjects();		

		m_bRestored = FALSE;
	}
	return S_OK;
}

HRESULT CINFGameMainUnitInfoBar::DeleteDeviceObjects()
{
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->DeleteDeviceObjects();
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->DeleteDeviceObjects();
	m_pImgBackMinimap->DeleteDeviceObjects();
	m_pFontUnitPosInfo->DeleteDeviceObjects();

	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]);
	SAFE_DELETE(m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]);
	SAFE_DELETE(m_pImgBackMinimap);
	SAFE_DELETE(m_pFontUnitPosInfo);

	int i=0;
	for(i=0;i<GAMEMAIN_GAGE_LINE_NUMBER;i++)
	{
		m_pFontGageInfo[i]->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontGageInfo[i]);
	}	

//	for(i=0;i<BUTTON_STATE_NUMBER;i++)
//	{
//		m_pButtonShowHide[0][i]->DeleteDeviceObjects();
//		m_pButtonShowHide[1][i]->DeleteDeviceObjects();
//		SAFE_DELETE(m_pButtonShowHide[0][i]);
//		SAFE_DELETE(m_pButtonShowHide[1][i]);
//	}

	// 2004-12-08 by jschoi
	m_pImgMainGageBack->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainGageBack);
	m_pImgMainExpBack->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainExpBack);
	m_pImgMainExpBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainExpBar);
	m_pImgMainSpeedNum->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainSpeedNum);
	m_pImgMainMinus->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgMainMinus);
	for(i=0;i<GAMEMAIN_GAGE_HP_MAX_GRADE;i++)
	{
		m_pImgMainGageHP[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMainGageHP[i]);
		m_pImgMainGageDP[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMainGageDP[i]);
		m_pImgMainGageSP[i]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pImgMainGageSP[i]);
	}

	for(i=0;i<GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;i++)
	{
		m_pImgMainGageBooster[i]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pImgMainGageBooster[i]);
	}

	for(i=0;i<GAMEMAIN_GAGE_FUEL_MAX_GRADE;i++)
	{
		m_pImgMainGageFuel[i]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pImgMainGageFuel[i]);
	}

	for(i=0;i<2;i++)
	{
		m_pImgMainIconFuel[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMainIconFuel[i]);
	}

	if(m_pFontMapName ) 
	{
		m_pFontMapName->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontMapName ) ; 
	}

	if(m_pFontCurrentEvent)
	{
		m_pFontCurrentEvent->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontCurrentEvent ) ; 
	}

	if(m_pFontEventHappyHour)
	{
		m_pFontEventHappyHour->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontEventHappyHour ) ; 
	}
	if(m_pFontEventRecovery)
	{
		m_pFontEventRecovery->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontEventRecovery);
	}
	for(i = 0; i < GAMEMAIN_EVENT_RECOVERY_MAX; i++)
	{
		if(m_pImgEventRecovery[i])
		{
			m_pImgEventRecovery[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgEventRecovery[i]);
		}
	}
	for(i = 0; i < GIFT_ICON_IMG_COUNT; i++)
	{
		if(m_pImgGiftIcon[i])
		{
			m_pImgGiftIcon[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgGiftIcon[i]);
		}
	}	
	
	return S_OK;
}


void CINFGameMainUnitInfoBar::Render()//RenderCityUpInfo() 에서 같은 코드 사용 : 수정시 주의할것
{

	// down window - 아래 까만줄
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Move(0, GAMEMAIN_BACK_DOWN_START_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width, GAMEMAIN_BACK_DOWN_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Render();
	
	// 상점에선 기타 정보 렌더링을 안한다
	if(g_pD3dApp->m_dwGameState == _SHOP)
		return;

	// up window - 위에 까만줄
	//m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Move(GAMEMAIN_BACK_GAGE_UP_SIZE_X, 0);
	//m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width-GAMEMAIN_BACK_GAGE_UP_SIZE_X-GAMEMAIN_BACK_MINIMAP_SIZE_X,GAMEMAIN_BACK_UP_SIZE_Y);
	//m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Render();
	
	
	// 메인 배경
	m_pImgMainGageBack->Move(0,0);
	m_pImgMainGageBack->Render();

	// 경험치 배경
	m_pImgMainExpBack->Move(GAMEMAIN_BACK_GAGE_EXP_START_X,GAMEMAIN_BACK_GAGE_EXP_START_Y);
	m_pImgMainExpBack->Render();

	RenderMainGage();

	RenderSpeed();

	// minimap back
	m_pImgBackMinimap->Move(GAMEMAIN_BACK_MINIMAP_START_X, GAMEMAIN_BACK_MINIMAP_START_Y);
	m_pImgBackMinimap->Render();

	// gage string
	RenderGageString();
	
	const UINT nMapPosX = g_pD3dApp->GetBackBufferDesc().Width - 110;
	const UINT nMapPosY = 20;
	RenderMapPosition(nMapPosX,nMapPosY);

	UINT nStartX = g_pD3dApp->GetBackBufferDesc().Width;
	UINT nStartY = 4;

	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		nStartX -= (strlen(mapname->MapName)*6 + 30);
		ShowMapNameTitle(nStartX,nStartY);
	}

	nStartX -= 110;
	RenderCurrentEvent(nStartX, nStartY);		//도시 점령전이나 PK지역 렌더링.


	RenderPremiumCard(FALSE);					// 일반
	RenderHappyHourEvent(FALSE);
	RenderEventRecovery();						// 2006-04-24 by ispark, 이벤트 회복율
	RenderStringBar();							// 2006-06-08 by ispark, 이벤트 설명
	RenderGiftIcon(FALSE);
	// 2006-04-25 by ispark, 해피 아우어 스트링을 함수 안으로 옮겼다.	

}
void CINFGameMainUnitInfoBar::RenderGiftIcon(BOOL i_bCity)
{
	if(m_vecGiftMsg.size())
	{	
// 2008-05-19 by dgwoo 메인 인터페이스 위치 변경.
//		if(i_bCity)
//			m_nGiftY = g_pD3dApp->GetBackBufferDesc().Height - INFOMAIN_GIFT_CITY_ICON_Y;
//		else
			m_nGiftY = g_pD3dApp->GetBackBufferDesc().Height - INFOMAIN_GIFT_FIELD_ICON_Y;
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			m_nGiftY -= GAME_EVENT_BASICPOS_Y;
		m_ptGift = m_pImgGiftIcon[0]->GetImgSize();
		m_nGiftY -= m_ptGift.y;
		m_nGiftX = g_pD3dApp->GetBackBufferDesc().Width - INFOMAIN_GIFT_ICON_X;
		// 깜빡임 처리.(0.7초에 한번씩)
		m_fGiftTime += g_pD3dApp->GetElapsedTime();
		float ftime = m_fGiftTime * 10;
		ftime = (int)ftime % 14;
		if(ftime > 7)
		{
			m_pImgGiftIcon[0]->Move(m_nGiftX, m_nGiftY);
			m_pImgGiftIcon[0]->Render();
		}
		else
		{
			m_pImgGiftIcon[1]->Move(m_nGiftX, m_nGiftY);
			m_pImgGiftIcon[1]->Render();
		}
	}	

}
void CINFGameMainUnitInfoBar::HideRender()
{
	// up window - 위에 까만줄
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Move(GAMEMAIN_BACK_GAGE_UP_SIZE_X, 0);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width-GAMEMAIN_BACK_GAGE_UP_SIZE_X-GAMEMAIN_BACK_MINIMAP_SIZE_X,GAMEMAIN_BACK_UP_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Render();
	
	// 2004-12-08 by jschoi 
	// 메인 배경
	m_pImgMainGageBack->Move(0,0);
	m_pImgMainGageBack->Render();

	RenderMainGage(FALSE);

	RenderSpeed();

	// minimap back
	m_pImgBackMinimap->Move(GAMEMAIN_BACK_MINIMAP_START_X, GAMEMAIN_BACK_MINIMAP_START_Y);
	m_pImgBackMinimap->Render();

	// gage string
	RenderGageString(FALSE);

	const UINT nMapPosX = g_pD3dApp->GetBackBufferDesc().Width - 110;
	const UINT nMapPosY = 20;
	RenderMapPosition(nMapPosX,nMapPosY);

	UINT nStartX = g_pD3dApp->GetBackBufferDesc().Width;
	UINT nStartY = 4;

	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		nStartX -= (strlen(mapname->MapName)*6 + 30);
		ShowMapNameTitle(nStartX,nStartY);
	}

	nStartX -= 110;
	RenderCurrentEvent(nStartX, nStartY);
	
}

void CINFGameMainUnitInfoBar::RenderCityUpInfo()
{
	// up window
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Move(GAMEMAIN_BACK_GAGE_UP_SIZE_X, 0);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width - GAMEMAIN_BACK_GAGE_UP_SIZE_X,GAMEMAIN_BACK_UP_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_UP_PIXEL]->Render();

	// down window - 아래 까만줄
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Move(0, GAMEMAIN_BACK_DOWN_START_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->SetScale(g_pD3dApp->GetBackBufferDesc().Width, GAMEMAIN_BACK_DOWN_SIZE_Y);
	m_pImgBackPixel[GAMEMAIN_BACK_DOWN_PIXEL]->Render();
	
	// 2004-12-08 by jschoi 
	// 메인 배경
	m_pImgMainGageBack->Move(0,0);
	m_pImgMainGageBack->Render();

	// 경험치 배경
	m_pImgMainExpBack->Move(GAMEMAIN_BACK_GAGE_EXP_START_X,GAMEMAIN_BACK_GAGE_EXP_START_Y);
	m_pImgMainExpBack->Render();

	RenderMainGage();

	RenderSpeed();

	// gage string
	RenderGageString();


	UINT nStartX = g_pD3dApp->GetBackBufferDesc().Width;
	UINT nStartY = 4;

//	if(RenderCurrentEvent())
//	{
//		nStartX = g_pD3dApp->GetBackBufferDesc().Width - 160;
//	}
//	else
//	{
//		nStartX = g_pD3dApp->GetBackBufferDesc().Width - 30;
//	}
//
//	nStartY = 4;


	// 맵이름 표시
	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		nStartX -= (strlen(mapname->MapName)*6 + 30);
		ShowMapNameTitle(nStartX,nStartY);
	}

	// 2005-02-18 by jschoi - Premium Card Render
	RenderPremiumCard(TRUE);	// 도시
	// Render HappyHour
	RenderHappyHourEvent(TRUE);
	// 2006-08-29 by dgwoo RenderTextEvent
	RenderTextHappyHourEvent();

}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFGameMainUnitInfoBar::RenderTextHappyHourEvent()
/// \brief		해피아워 이벤트 관련 텍스트를 찍는다.
///
/// \author		dgwoo
/// \version	
/// \date		2006-08-29 ~ 2006-08-29
/// \warning	
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::RenderTextHappyHourEvent()
{

	int Height = 0;
	int leng = 0;
	vector<string>::iterator itU = m_vecEventHappyHour.begin();
	while (itU != m_vecEventHappyHour.end())
	{
		if(strlen((char*)(*itU).c_str())>leng)
		{
			leng = strlen((char*)(*itU).c_str());
		}
		itU++;
	}
	leng = leng*6.5;

	if(m_bRenderEvent == TRUE)
	{
		int nIdex = 0;
		vector<string>::iterator it = m_vecEventHappyHour.begin();
		while (it != m_vecEventHappyHour.end())
		{
			g_pGameMain->RenderPopUpWindowImage(m_nHappyHourX, m_nHappyHourY-20-(nIdex*20), leng, 1);
			m_pFontEventHappyHour->DrawText(m_nHappyHourX, m_nHappyHourY-20-(nIdex*20), GUI_FONT_COLOR_Y, (char*)(*it).c_str());
			
			it++;
			nIdex++;
		}
	}
}

void CINFGameMainUnitInfoBar::RenderGageString(BOOL bShowAll)
{
	if(m_szGageInfo[GAMEMAIN_GAGE_HP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_HP]->DrawText( GAMEMAIN_NEW_STRING_HP_START_X, 
														GAMEMAIN_NEW_STRING_HP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_HP],0L);		
		m_pFontGageInfo[GAMEMAIN_GAGE_HP_UP]->DrawText( GAMEMAIN_GAGE_HP_UP_START_X, 
														GAMEMAIN_GAGE_HP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_HP_UP],0L);
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_HP]->DrawText( GAMEMAIN_NEW_STRING_MAX_HP_START_X, 
														GAMEMAIN_NEW_STRING_MAX_HP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_HP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_DP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_DP]->DrawText( GAMEMAIN_NEW_STRING_DP_START_X, 
														GAMEMAIN_NEW_STRING_DP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_DP],0L);		
		m_pFontGageInfo[GAMEMAIN_GAGE_DP_UP]->DrawText( GAMEMAIN_GAGE_DP_UP_START_X, 
														GAMEMAIN_GAGE_DP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_DP_UP],0L);
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_DP]->DrawText( GAMEMAIN_NEW_STRING_MAX_DP_START_X, 
														GAMEMAIN_NEW_STRING_MAX_DP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_DP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_SP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_GAGE_SP_UP]->DrawText( GAMEMAIN_GAGE_SP_UP_START_X, 
														GAMEMAIN_GAGE_SP_UP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_SP_UP],0L);		
		m_pFontGageInfo[GAMEMAIN_NEW_STRING_MAX_SP]->DrawText( GAMEMAIN_NEW_STRING_MAX_SP_START_X, 
														GAMEMAIN_NEW_STRING_MAX_SP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_NEW_STRING_MAX_SP],0L);
	}

	if(m_szGageInfo[GAMEMAIN_GAGE_EP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_GAGE_EP_UP]->DrawText( GAMEMAIN_STRING_FUEL_START_X, 
														GAMEMAIN_STRING_FUEL_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_EP_UP],0L);
	}	

	if(	bShowAll &&
		m_szGageInfo[GAMEMAIN_GAGE_EXP_UP])
	{
		m_pFontGageInfo[GAMEMAIN_GAGE_EXP_UP]->DrawText( GAMEMAIN_STRING_EXP_START_X, 
														GAMEMAIN_STRING_EXP_START_Y,
														GUI_FONT_COLOR,
														m_szGageInfo[GAMEMAIN_GAGE_EXP_UP],0L);
	}

}


void CINFGameMainUnitInfoBar::Tick()
{
	const float RENDER_TIME = 0.5f;
	SetSpeed(g_pShuttleChild->m_fShuttleSpeed, 
			g_pShuttleChild->m_fRealShuttleSpeedMin, 
			g_pShuttleChild->m_fRealShuttleSpeedBoosterOn );
	m_fWarningTime += g_pD3dApp->GetElapsedTime();
	if(m_fWarningTime > RENDER_TIME)
	{
		m_bWarning = !m_bWarning;
		m_fWarningTime -= RENDER_TIME;
	}	
}

int CINFGameMainUnitInfoBar::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(WndProcCity(uMsg, wParam, lParam) == INF_MSGPROC_BREAK )
		return INF_MSGPROC_BREAK;
	
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(pt.x > m_nGiftX &&
				pt.x < m_nGiftX + m_ptGift.x &&
				pt.y > m_nGiftY &&
				pt.y < m_nGiftY + m_ptGift.y)
			{
				CreateMsgBox();
				return INF_MSGPROC_BREAK;
			}

			if(g_pGameMain->GetVoiceType() != VOICE_NONE &&
				pt.x > GAMEMAIN_VOICECHAT_X &&
				pt.x < GAMEMAIN_VOICECHAT_X + GAMEMAIN_VOICECHAT_W &&
				pt.y > GAMEMAIN_VOICECHAT_Y &&
				pt.y < GAMEMAIN_VOICECHAT_Y + GAMEMAIN_VOICECHAT_H)
			{
				g_pGameMain->m_pChat->ShowVoiceChatControl(TRUE);
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			int x,y;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > GAMEMAIN_VOICECHAT_X &&
				pt.x < GAMEMAIN_VOICECHAT_X + GAMEMAIN_VOICECHAT_W &&
				pt.y > GAMEMAIN_VOICECHAT_Y &&
				pt.y < GAMEMAIN_VOICECHAT_Y + GAMEMAIN_VOICECHAT_H)
			{// 음성아이콘 툴바 표시.
				char szTemp[128];
				memset(szTemp,0x00,128);
				switch(g_pGameMain->GetVoiceType())
				{
				case VOICE_ONE:
					{
						sprintf(szTemp,STRMSG_C_080519_0113);
					}
					break;
				case VOICE_PARTY:
					{
						sprintf(szTemp,STRMSG_C_080519_0110);
					}
					break;
				case VOICE_GUILD:
					{
						sprintf(szTemp,STRMSG_C_080519_0111);
					}
					break;
				default:
					{
						g_pGameMain->SetToolTip(0,0,NULL);
					}
					break;
				}
				g_pGameMain->SetToolTip(pt.x,pt.y,szTemp);
			}
			else
			{
				g_pGameMain->SetToolTip(0,0,NULL);
			}


			// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
			//if(m_BHappyHourEvent)
			if(IsHappyHourEvent())
			{
				m_bRenderEvent = FALSE;
				
				int x,y;
				if(g_pD3dApp->GetTestServerFlag() == FALSE)
				{
					x = g_pD3dApp->GetBackBufferDesc().Width - GAME_EVENT_BASICPOS_X;
				}
				else
				{
					x = g_pD3dApp->GetBackBufferDesc().Width -120;
				}
				y = g_pD3dApp->GetBackBufferDesc().Height - 54;

//				if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//					y -= GAME_EVENT_BASICPOS_Y;

				if( pt.x > x &&
					pt.x < x + 120 && pt.y > y && pt.y < y + 12)
				{
					m_bRenderEvent = TRUE;
				}
			}
			
			if(TRUE == g_bEventRecovery)
			{
				m_bRenderEventRecovery = FALSE;

				x = g_pD3dApp->GetBackBufferDesc().Width - 88;
				y = g_pD3dApp->GetBackBufferDesc().Height - 83;

				if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
					y -= GAME_EVENT_BASICPOS_Y;

				if( pt.x > x &&
					pt.x < x + 44 && pt.y > y && pt.y < y + 20)
				{
					m_bRenderEventRecovery = TRUE;
				}
			}
		}
		break;
	}
	
	return INF_MSGPROC_NORMAL;
}

int CINFGameMainUnitInfoBar::WndProcCity(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			m_v2MousePt.x = pt.x;
			m_v2MousePt.y = pt.y;
			m_bRenderEvent = FALSE;
			
			// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
			//if(m_BHappyHourEvent)
			if(IsHappyHourEvent())
			{
				int x,y;
				if(g_pD3dApp->GetTestServerFlag() == FALSE)
				{
					x = CHAT_MENU_CASH_START_X -177;
				}
				else
				{
					x = g_pD3dApp->GetBackBufferDesc().Width -177;
				}
				y = g_pD3dApp->GetBackBufferDesc().Height - 99;

				if( pt.x > x &&
					pt.x < x + 120 && pt.y > y && pt.y < y + 12)
				{
					m_bRenderEvent = TRUE;
				}
				
			}


			// 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가

			int	x	= g_pD3dApp->GetBackBufferDesc().Width - 64;
			int	y	= g_pD3dApp->GetBackBufferDesc().Height - 82;

			if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
				y -= GAME_EVENT_BASICPOS_Y;

			if(m_bMemberPCBang)
			{
				POINT	pt = m_pImgGeneralPremiumCard->GetImgSize();
				y -= pt.y;
			}

			RECT membership;
			membership.left		= x;
			membership.top		= y;
			membership.right	= x + m_pImgGeneralPremiumCard->GetImgSize().x;
			membership.bottom	= y + m_pImgGeneralPremiumCard->GetImgSize().y;

 			if(PtInRect(&membership, pt))
				m_bPremiumToolTip = TRUE;
			else
				m_bPremiumToolTip = FALSE;

			// end 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가
		}
		break;
	case WM_LBUTTONDOWN:
		{
		}
		break;
	case WM_LBUTTONUP:
		{
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFGameMainUnitInfoBar::RenderMainGage(BOOL bShowAll)
{
	UINT i;
	if(m_fGageRate[GAMEMAIN_GAGE_HP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_HP_UP]*GAMEMAIN_GAGE_HP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_HP_MAX_GRADE){i--;}

		if(i > 0)
		{
			m_pImgMainGageHP[i]->Move(GAMEMAIN_GAGE_HP_START_X, GAMEMAIN_GAGE_HP_START_Y);
			m_pImgMainGageHP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_DP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_DP_UP]*GAMEMAIN_GAGE_DP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_DP_MAX_GRADE){i--;}

		if(i > 0)
		{
			m_pImgMainGageDP[i]->Move(GAMEMAIN_GAGE_DP_START_X, GAMEMAIN_GAGE_DP_START_Y);
			m_pImgMainGageDP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_SP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_SP_UP]*GAMEMAIN_GAGE_SP_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_SP_MAX_GRADE){i--;}

		if(i > 0)
		{
			m_pImgMainGageSP[i]->Move(GAMEMAIN_GAGE_SP_START_X, GAMEMAIN_GAGE_SP_START_Y);
			m_pImgMainGageSP[i]->Render();
		}
	}
	if(m_fGageRate[GAMEMAIN_GAGE_BURN_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_BURN_UP]*GAMEMAIN_GAGE_BOOSTER_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_BOOSTER_MAX_GRADE){i--;}
		m_pImgMainGageBooster[i]->Move(GAMEMAIN_GAGE_BOOSTER_START_X, GAMEMAIN_GAGE_BOOSTER_START_Y);
		m_pImgMainGageBooster[i]->SetScale(1.125,1.125);
		m_pImgMainGageBooster[i]->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_EP_UP]>0)
	{
		i = m_fGageRate[GAMEMAIN_GAGE_EP_UP]*GAMEMAIN_GAGE_FUEL_MAX_GRADE;
		if(i>=GAMEMAIN_GAGE_FUEL_MAX_GRADE){i--;}
		m_pImgMainGageFuel[i]->Move(GAMEMAIN_GAGE_FUEL_START_X,GAMEMAIN_GAGE_FUEL_START_Y);
		m_pImgMainGageFuel[i]->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_EP_UP]>0.2f || !m_bWarning)
	{
		m_pImgMainIconFuel[0]->Move(GAMEMAIN_GAGE_FUEL_START_X,GAMEMAIN_GAGE_FUEL_START_Y);
		m_pImgMainIconFuel[0]->Render();
	}
	else
	{
		m_pImgMainIconFuel[1]->Move(GAMEMAIN_GAGE_FUEL_START_X,GAMEMAIN_GAGE_FUEL_START_Y);
		m_pImgMainIconFuel[1]->Render();
	}
	if(VOICE_NONE != g_pGameMain->GetVoiceType())
	{
		if(g_pGameMain->GetVOIPSpeaking())
		{
			m_pImgVoiceSPKIcon->Move(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
			m_pImgVoiceSPKIcon->Render();
		}
		else
		{
			m_pImgVoiceChatIcon->Move(GAMEMAIN_VOICECHAT_X,GAMEMAIN_VOICECHAT_Y);
			m_pImgVoiceChatIcon->Render();
		}		
	}


	// 2008-05-29 by dgwoo 메인 인터페이스 변경 기획.
	g_pGameMain->m_pWeaponInfo->RenderLeftWeapon();
	g_pGameMain->m_pWeaponInfo->RenderRightWeapon();

	//--------------------------------------------------------------------------//
	



	if(	bShowAll &&
		m_fGageRate[GAMEMAIN_GAGE_EXP_UP]>0)
	{
		m_pImgMainExpBar->Move(GAMEMAIN_EXP_GAGE_START_X, GAMEMAIN_EXP_GAGE_START_Y);
		m_pImgMainExpBar->SetRect(0,0,GAMEMAIN_GAGE_EXP_LENGTH*m_fGageRate[GAMEMAIN_GAGE_EXP_UP],9);
		m_pImgMainExpBar->Render();
	}
	if(m_fGageRate[GAMEMAIN_GAGE_HP_UP]<0.35f && m_bWarning)
	{
		m_pImgMainWarning->Move(GAMEMAIN_GAGE_HP_START_X+2, GAMEMAIN_GAGE_HP_START_Y);
		m_pImgMainWarning->Render();
	}
}

void CINFGameMainUnitInfoBar::RenderSpeed()
{
	// 2005-05-31 by jschoi - 유닛 상하 중력 적용
//	int nSpeed = (int)g_pShuttleChild->m_fShuttleSpeed;
	// 2005-12-12 by ispark, 캐릭터 상태에서는 무조건... 0
	int nSpeed = 0;
	if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
		nSpeed = 0;
	else
	{
		// 2010. 05. 17 by jskim A기어 지상 속도 1 적은 버그 수정
		//nSpeed = (int)(g_pShuttleChild->m_fShuttleSpeed - g_pShuttleChild->m_fTempGravity);
		//nSpeed = (int)((g_pShuttleChild->m_fShuttleSpeed - g_pShuttleChild->m_fTempGravity) + 1);
		//end. 05. 17 by jskim A기어 지상 속도 1 적은 버그 수정
		nSpeed = (int)((g_pShuttleChild->m_fShuttleSpeed - g_pShuttleChild->m_fTempGravity));

		if ( g_pShuttleChild->m_fShuttleSpeed > .0f )
			nSpeed += 1;
	}


	int nMaxNum = GetMaxSize(nSpeed);
	if(nMaxNum > 3)
	{
		nMaxNum = 3;
		nSpeed = 999;
	}
	UINT nPosX,nPosY,nNum;
	nPosX = SPEED_STRING_START_X - nMaxNum*8;
	nPosY = SPEED_STRING_START_Y;

	if(nSpeed < 0)
	{
		nPosX -= 7;
		m_pImgMainMinus->Move(nPosX,nPosY);
		m_pImgMainMinus->Render();		
		nPosX += 10;
		nSpeed = abs(nSpeed);
	}

	while(nMaxNum > 0)
	{
		nNum = CutOffFirstNumber(nSpeed,nMaxNum);
		m_pImgMainSpeedNum->Move(nPosX,nPosY);
		m_pImgMainSpeedNum->SetRect(nNum*SPEED_STRING_WIDTH,0,(nNum+1)*SPEED_STRING_WIDTH,SPEED_STRING_HEIGHT);	
		m_pImgMainSpeedNum->Render();		
		nPosX += 16; 
		nMaxNum--;
	}
}

int CINFGameMainUnitInfoBar::GetMaxSize(int nNum)
{
	int nMaxSize = 0;
	int nNumber = abs(nNum);
	if(nNumber >= 1000)
	{
		nMaxSize = 4;
	}
	else if(nNumber >= 100)
	{
		nMaxSize = 3;
	}
	else if(nNumber >= 10)
	{
		nMaxSize = 2;
	}
	else
	{
		nMaxSize = 1;
	}
	return nMaxSize;
}

int CINFGameMainUnitInfoBar::CutOffFirstNumber(int& nNum,int nMaxNum)
{
	int nResult = 0;
	if(nMaxNum == 3)
	{
		nResult = nNum/100;
		nNum = nNum%100;
		return nResult;
	}
	else if(nMaxNum == 2)
	{
		nResult = nNum/10;
		nNum = nNum%10;
		return nResult;
	}
	else if(nMaxNum == 1)
	{
		return nNum;
	}
	return 0;
}

void CINFGameMainUnitInfoBar::ShowMapNameTitle(UINT x, UINT y)
{
	char buf[256];
	memset(buf, 0x00, 256);
	MAP_INFO* mapname = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
	if(mapname)
	{
		strncpy(buf, mapname->MapName, sizeof(mapname->MapName));
		wsprintf(buf, "%s(%d)", mapname->MapName,g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.ChannelIndex);
		m_pFontMapName->DrawText(x, y, GAME_MAP_NAME_TEXT_COLOR, buf);
	}
}

void CINFGameMainUnitInfoBar::RenderMapPosition(UINT x, UINT y)
{
	char buf[64];
	int nHeightPerTile;

	if(IS_SPACE_MAP_INDEX(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex) == TRUE)
	{
		nHeightPerTile = (g_pD3dApp->m_pShuttleChild->m_vPos.y-g_pGround->m_projectInfo.fWaterHeight+ALTITUDE_SAPCE_ALTITUDE)/TILE_SIZE;
	}
	else
	{
		nHeightPerTile = (g_pD3dApp->m_pShuttleChild->m_vPos.y-g_pGround->m_projectInfo.fWaterHeight)/TILE_SIZE;
	}
	
	if(g_pD3dApp->m_fFPS > 60.0f)
	{
		//Green
		wsprintf(buf, "FPS: \\g%2d\\g X:%3d Y:%3d H:%2d", (int)g_pD3dApp->m_fFPS,(int)(g_pD3dApp->m_pShuttleChild->m_vPos.x/TILE_SIZE),
								 (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z/TILE_SIZE),
								 nHeightPerTile);
	}
	else if(g_pD3dApp->m_fFPS <= 60.0f && g_pD3dApp->m_fFPS >40.0f)
	{
		//Green
		wsprintf(buf, "FPS: \\g%2d\\g X:%3d Y:%3d H:%2d", (int)g_pD3dApp->m_fFPS,(int)(g_pD3dApp->m_pShuttleChild->m_vPos.x/TILE_SIZE),
								 (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z/TILE_SIZE),
								 nHeightPerTile);
	}
	else if(g_pD3dApp->m_fFPS < 40.0f && g_pD3dApp->m_fFPS > 30.0f)
	{
		//Yellow
		wsprintf(buf, "FPS: \\y%2d\\y X:%3d Y:%3d H:%2d", (int)g_pD3dApp->m_fFPS,(int)(g_pD3dApp->m_pShuttleChild->m_vPos.x/TILE_SIZE),
								 (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z/TILE_SIZE),
								 nHeightPerTile);
	}
	else if(g_pD3dApp->m_fFPS < 30.0f && g_pD3dApp->m_fFPS > 20.0f)
	{
		//Orange
		wsprintf(buf, "FPS: \\e%2d\\e X:%3d Y:%3d H:%2d", (int)g_pD3dApp->m_fFPS,(int)(g_pD3dApp->m_pShuttleChild->m_vPos.x/TILE_SIZE),
								 (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z/TILE_SIZE),
								 nHeightPerTile);
	}
	else if(g_pD3dApp->m_fFPS < 20.0f)
	{
		//Red
		wsprintf(buf, "FPS: \\r%2d\\r X:%3d Y:%3d H:%2d", (int)g_pD3dApp->m_fFPS,(int)(g_pD3dApp->m_pShuttleChild->m_vPos.x/TILE_SIZE),
								 (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z/TILE_SIZE),
								 nHeightPerTile);
	}


	/*wsprintf(buf, "FPS: %.1f X:%3d Y:%3d H:%2d",g_pD3dApp->m_fFPS,(int)(g_pD3dApp->m_pShuttleChild->m_vPos.x/TILE_SIZE),
								 (int)(g_pD3dApp->m_pShuttleChild->m_vPos.z/TILE_SIZE),
								 nHeightPerTile);*/ //2014-08-09 by St0rmy added FPS Counter colored

	m_pFontUnitPosInfo->DrawText( x - 20, y, GAME_UNIT_POS_COLOR, buf, 0L);
}

BOOL CINFGameMainUnitInfoBar::RenderCurrentEvent(UINT x, UINT y)
{
	if(g_pShuttleChild->IsWarpGateZone())
	{
		return FALSE;
	}
	
	if(	g_pShuttleChild && 
		g_pShuttleChild->m_pPkNormalTimer && 
		g_pShuttleChild->m_pPkNormalTimer->IsCityWar())
	{
		m_pFontCurrentEvent->DrawText(x, y, GUI_FONT_COLOR_YM, STRMSG_C_INTERFACE_0024);//"도시점령전 진행중"
		return TRUE;	// 도시점령전 중
	}

	if( g_pShuttleChild &&
		IsPkEnableMap(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex))
	{
		m_pFontCurrentEvent->DrawText(x+20, y, RGB(255,54,0), STRMSG_C_INTERFACE_0025);//"PK 가능 지역"
		return TRUE;	// PK 가능 맵
	}

	return FALSE;	// 아무런 이벤트가 없다.
}

BOOL CINFGameMainUnitInfoBar::IsRenderMapName()
{
	float fRadius;
	fRadius = D3DXVec2Length(&(m_v2MousePt - m_v2RaderCenter));
	if(fRadius > RADER_RADIUS)
	{
		return TRUE;
	}
	return FALSE;
}

void CINFGameMainUnitInfoBar::RenderPremiumCard(BOOL bIsCity)
{
	int x,y;

	x = g_pD3dApp->GetBackBufferDesc().Width - 64;

//	if(bIsCity)
//		y = g_pD3dApp->GetBackBufferDesc().Height - 107;
//	else
		y = g_pD3dApp->GetBackBufferDesc().Height - 82;

	if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
		y -= GAME_EVENT_BASICPOS_Y;

	if(m_bMemberPCBang)
	{
		POINT	pt = m_pImgGeneralPremiumCard->GetImgSize();
		y -= pt.y;
	}

	// 2006-07-05 by ispark, 프리미엄 개념 변경
	if(g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1)
	{
		m_pImgGeneralPremiumCard->Move(x,y);
		m_pImgGeneralPremiumCard->Render();

		// 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가

		if(m_bPremiumToolTip)
		{
			char szBuff[MAX_PATH];
			int curSec	= GetServerDateTime().GetTimeInSeconds();
			int	endSec	= g_pD3dApp->GetPrimiumCardInfo()->atumTimeExpireTime1.GetTimeInSeconds();

			int leftDay		= (endSec - curSec) / 86400;
			int leftHour	= (endSec - curSec) % 86400 / 3600;
			int leftMin		= (endSec - curSec) % 86400 % 3600 / 60;

			if(leftDay <= 0 && leftHour <= 0 && leftMin <= 100)
				sprintf(szBuff, STRMSG_C_090316_0302, leftMin);			// "[멤버십 잔여시간] 00분 남음"
			else
				sprintf(szBuff, STRMSG_C_090316_0301, leftDay, leftHour);	// "[멤버십 잔여시간] 00일 00시간 남음"

			POINT	drawPt;
			SIZE	strSize = m_pFontEventRecovery->GetStringSize(szBuff);
			drawPt.x	= x - strSize.cx;
			drawPt.y	= y - strSize.cy;

			g_pGameMain->RenderPopUpWindowImage(drawPt.x, drawPt.y + strSize.cy * 0.1f, strSize.cx, 1);
			m_pFontEventRecovery->DrawText(drawPt.x, drawPt.y, GUI_FONT_COLOR_Y, szBuff);
		}

		// end 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가
	}

}

void CINFGameMainUnitInfoBar::RenderHappyHourEvent(BOOL bIsCity)
{
	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	//if(m_BHappyHourEvent)
	if(IsHappyHourEvent())
	{	
// 2008-05-19 by dgwoo 메인 인터페이스 위치 변경.
//		if(bIsCity)
//			m_nHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 99;
//		else
			m_nHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 57;
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			m_nHappyHourY -= GAME_EVENT_BASICPOS_Y;

		m_pImgHappyHourEvent->Move(m_nHappyHourX, m_nHappyHourY);
		m_pImgHappyHourEvent->Render();
	}

	// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	if(m_pMemberPremiumEvent)
	{
		m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 87;
		m_pImgPCHomePremiumEvent->Move(m_nPCHappyHourX,m_nPCHappyHourY);
		m_pImgPCHomePremiumEvent->Render();
	}
	//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	else if(m_bMemberPCBang)
	{
// 2008-05-19 by dgwoo 메인 인터페이스 위치 변경.
//		if(bIsCity)
//			m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 107;
//		else
			m_nPCHappyHourY = g_pD3dApp->GetBackBufferDesc().Height - 82;
		
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			m_nPCHappyHourY -= GAME_EVENT_BASICPOS_Y;
		
		m_pImgPCHappyHourEvent->Move(m_nPCHappyHourX,m_nPCHappyHourY);
		m_pImgPCHappyHourEvent->Render();		
	}
}

void CINFGameMainUnitInfoBar::RenderEventRecovery()
{
	if(TRUE == g_bEventRecovery)
	{
		int nCount = ((int)(g_fEventRecoveryRate * 100.0f) / 5.0f) - 1;
		int nEventX = g_pD3dApp->GetBackBufferDesc().Width - 105;
		int nEventY = g_pD3dApp->GetBackBufferDesc().Height - 83;
// 2008-05-19 by dgwoo 메인 인터페이스 위치 변경.
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			nEventY -= GAME_EVENT_BASICPOS_Y;

		// 2009. 08. 21 by ckPark 이벤트 회복률 단계 버그 수정
		if( nCount > GAMEMAIN_EVENT_RECOVERY_MAX - 1 )
			nCount = GAMEMAIN_EVENT_RECOVERY_MAX - 1;
		if( nCount < 0 )
			nCount = 0;
		// end 2009. 08. 21 by ckPark 이벤트 회복률 단계 버그 수정

		if(m_pImgEventRecovery[nCount])
		{
			m_pImgEventRecovery[nCount]->Move(nEventX, nEventY);
			m_pImgEventRecovery[nCount]->Render();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::RenderStringBar()
/// \brief		이벤트 설명
/// \author		ispark
/// \date		2006-06-08 ~ 2006-06-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::RenderStringBar()
{
	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	//if(m_BHappyHourEvent)
	if(IsHappyHourEvent())
	{
		// 2006-04-25 by ispark, 마우스 위치일때 보여주는 스트링
		if(m_bRenderEvent == TRUE)
		{
			// 2006-04-24 by ispark, 수정
//			int Height = 0;
			int nRenderX = 0;
			int leng = 0;
			vector<string>::iterator itU = m_vecEventHappyHour.begin();
			while (itU != m_vecEventHappyHour.end())
			{
				int nlengTemp = 0;
				nlengTemp = m_pFontEventHappyHour->GetStringSize((char*)(*itU).c_str()).cx;
//				if(strlen((char*)(*itU).c_str())>leng)
				if(nlengTemp > leng)
				{
					leng = nlengTemp + 10;
//					leng = strlen((char*)(*itU).c_str());
				}
				itU++;
			}
//			leng = leng*6.5;
			nRenderX = m_nHappyHourX + 10;
			if(nRenderX + leng > g_pD3dApp->GetBackBufferDesc().Width)
			{
				nRenderX = g_pD3dApp->GetBackBufferDesc().Width - leng;
			}

			int nIdex = 0;
			vector<string>::iterator it = m_vecEventHappyHour.begin();
			while (it != m_vecEventHappyHour.end())
			{
				g_pGameMain->RenderPopUpWindowImage(nRenderX, m_nHappyHourY-20-(nIdex*20), leng, 1);
				m_pFontEventHappyHour->DrawText(nRenderX, m_nHappyHourY-20-(nIdex*20)-GAMEMAIN_EVENT_FONT_Y, GUI_FONT_COLOR_Y, (char*)(*it).c_str());
				
				it++;
				nIdex++;
			}

		}
	}	

	if(TRUE == g_bEventRecovery)
	{
		int nEventX = g_pD3dApp->GetBackBufferDesc().Width - 88;
		int nEventY = g_pD3dApp->GetBackBufferDesc().Height - 83;
// 2008-05-19 by dgwoo 메인 인터페이스 위치 변경.
//		if(g_pD3dApp->m_bCharacter && !g_pGround->m_bBazaar)
//			nEventY -= GAME_EVENT_BASICPOS_Y;

		if(TRUE == m_bRenderEventRecovery)
		{
			char buf[128] = {0,};

			// 2009. 08. 21 by ckPark 이벤트 회복률 단계 버그 수정
			if( g_fEventRecoveryRate > 0.25f )
				g_fEventRecoveryRate = 0.25f;
			if( g_fEventRecoveryRate < 0.0f )
				g_fEventRecoveryRate = 0.0f;
			// end 2009. 08. 21 by ckPark 이벤트 회복률 단계 버그 수정			

			sprintf(buf, STRMSG_C_060424_0002, (int)(g_fEventRecoveryRate * 100.0f));
			int leng = m_pFontEventRecovery->GetStringSize(buf).cx + 10;
			if(nEventX + leng > g_pD3dApp->GetBackBufferDesc().Width)
			{
				nEventX = g_pD3dApp->GetBackBufferDesc().Width - leng;
			}
			g_pGameMain->RenderPopUpWindowImage(nEventX, nEventY-13, leng, 1);
			m_pFontEventRecovery->DrawText(nEventX, nEventY-GAMEMAIN_EVENT_FONT_Y-13, GUI_FONT_COLOR_Y, buf);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFGameMainUnitInfoBar::IsHappyHourEvent()
/// \brief		
/// \author		// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMainUnitInfoBar::IsHappyHourEvent()
{	
	CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	if(m_bPcBangHappyHour)
	{
		return TRUE;
	}
	else if(TRUE == m_bHappyHourAllInfluence)
	{
		return TRUE;
	}	
	else if(COMPARE_INFLUENCE(m_byHappyHourInfluence, myShuttleInfo.InfluenceType))
	{
		return TRUE;
	}	
	// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
	else if(m_bMotherHappyHour || m_bItemHappyHour)
	{
		return TRUE;
	}
	// end 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFGameMainUnitInfoBar::IsHappyHourEvent()
/// \brief		
/// \author		// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFGameMainUnitInfoBar::IsHappyHourPcBang()
{
	return m_bPcBangHappyHour;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourInfluence(BYTE byInfluence)
/// \brief		
/// \author		// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourInfluence(BOOL bLevelup, BOOL bHappyHour, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	BYTE byInfluence = pMsg->byInfluenceType4;

	CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	
	// 각 세력별 해피 아우어 인포
	EVENT_INFO* pEventInfo = NULL;
	BOOL bAllInfluence = FALSE;
	if(byInfluence == INFLUENCE_TYPE_ALL_MASK)
	{
		bAllInfluence = TRUE;
		pEventInfo = &m_HappyEventAllInfluInfo;
	}
	else if(COMPARE_INFLUENCE(byInfluence, myShuttleInfo.InfluenceType))
	{
		pEventInfo = &m_HappyEventInfo;		
	}
	else
	{
		return;
	}	
	// 변수 초기화	
	memset(pEventInfo, 0x00, sizeof(EVENT_INFO));

	if(bHappyHour)
	{		
		if(bAllInfluence)
		{
			m_bHappyHourAllInfluence = TRUE;			
		}
		else
		{
			m_byHappyHourInfluence = byInfluence;

		}
		// 전체 세력 해피 아워 인포
		SetHappyHourInfo(bLevelup, pMsg, pEventInfo);
	}
	else
	{
		if(bAllInfluence)
		{
			m_bHappyHourAllInfluence = FALSE;			
		}
		else
		{
			m_byHappyHourInfluence  = 0;		
		}		
	}

	// 해피 아우어 툴팁 갱신 
	UpdateHappyHourTooltip();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourInfo(BYTE byInfluence)
/// \brief		
/// \author		// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourInfo(BOOL bLevelup, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg, EVENT_INFO* pEventInfo)
{
	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	
	
	if(pMsg->fEXPRate2 > 0.0f)
	{		
		if(!bLevelup) // 레벨업이 아닐떄만 채팅에 표시 // 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
		{
			sprintf(szNotice, STRMSG_C_EVENT_0003,(pMsg->fEXPRate2)*100);//"몬스터 경험치 %.0f%% 증가"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);			
		}
		
		pEventInfo->fEXPRate = (pMsg->fEXPRate2);		
	}
	if(pMsg->fDropRareRate2 > 0.0f)
	{
		if(!bLevelup) // 레벨업이 아닐떄만 채팅에 표시 // 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
		{
			sprintf(szNotice, STRMSG_C_EVENT_0004,(pMsg->fDropRareRate2)*100);//"레어옵션 드롭율 %.0f%% 증가"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fDropRareRate = (pMsg->fDropRareRate2) ;
		
	}
	if(pMsg->fEXPRepairRate2 > 0.0f )
	{
		if(!bLevelup) // 레벨업이 아닐떄만 채팅에 표시 // 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
		{
			sprintf(szNotice, STRMSG_C_EVENT_0005,(pMsg->fEXPRepairRate2)*100);//"죽었을 경우 패널티 %.0f%% 감소"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fEXPRepairRate = (pMsg->fEXPRepairRate2) ;		
	}
	if(pMsg->fDropItemRate2 > 0.0f )
	{
		if(!bLevelup) // 레벨업이 아닐떄만 채팅에 표시 // 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
		{
			sprintf(szNotice, STRMSG_C_EVENT_0006,(pMsg->fDropItemRate2)*100);//"아이템 드롭율 %.0f%% 증가"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fDropItemRate = (pMsg->fDropItemRate2);

	}
	if(pMsg->fSPIRate2 > 0.0f )
	{
		if(!bLevelup) // 레벨업이 아닐떄만 채팅에 표시 // 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
		{
			sprintf(szNotice, STRMSG_C_EVENT_0007,(pMsg->fSPIRate2)*100);//"스피량 %.0f%% 증가"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fSPIRate = (pMsg->fSPIRate2);
		
	}
	if(pMsg->fWarPointRate2 > 0.0f )
	{// 전쟁 포인트.
		if(!bLevelup) // 레벨업이 아닐떄만 채팅에 표시 // 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
		{
			sprintf(szNotice, STRMSG_C_070626_0100,(pMsg->fWarPointRate2)*100);//"전쟁 포인트 %d%% 증가"
			g_pGameMain->CreateChatChild(szNotice ,COLOR_SYSTEM);	
		}
		
		pEventInfo->fWarPointRate = (pMsg->fWarPointRate2);
		
	}	
	if(!bLevelup) // 레벨업이 아닐떄만 채팅에 표시 // 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
	{
		g_pGameMain->CreateChatChild(STRMSG_C_EVENT_0008 ,COLOR_SYSTEM);//"좋은 시간 되시기 바랍니다. ^^"	
	}
}

void CINFGameMainUnitInfoBar::UpdateHappyHourTooltip()
{
	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	float fTmp = 0.0f;

	{
		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
		//fTmp = m_HappyEventInfo.fEXPRate+m_HappyEventAllInfluInfo.fEXPRate+m_PCHappyEventInfo.fEXPRate;
		fTmp = m_HappyEventInfo.fEXPRate+m_HappyEventAllInfluInfo.fEXPRate+m_PCHappyEventInfo.fEXPRate
				+m_MotherShipEventInfo.fEXPRate+m_ItemEventInfo.fEXPRate;

		if(fTmp > 0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0003,(fTmp)*100);//"몬스터 경험치 %.0f%% 증가"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	{
		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
		//fTmp = m_HappyEventInfo.fDropRareRate +m_HappyEventAllInfluInfo.fDropRareRate+m_PCHappyEventInfo.fDropRareRate;
		fTmp = m_HappyEventInfo.fDropRareRate +m_HappyEventAllInfluInfo.fDropRareRate+m_PCHappyEventInfo.fDropRareRate
				+m_MotherShipEventInfo.fDropRareRate+m_ItemEventInfo.fDropRareRate;
		if(fTmp)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0004,(fTmp)*100);//"레어옵션 드롭율 %.0f%% 증가"
			m_vecEventHappyHour.push_back(szNotice);
		}
		
	}

	{
		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
		//fTmp = m_HappyEventInfo.fEXPRepairRate +m_HappyEventAllInfluInfo.fEXPRepairRate+m_PCHappyEventInfo.fEXPRepairRate;
		fTmp = m_HappyEventInfo.fEXPRepairRate +m_HappyEventAllInfluInfo.fEXPRepairRate+m_PCHappyEventInfo.fEXPRepairRate
				+m_MotherShipEventInfo.fEXPRepairRate+m_ItemEventInfo.fEXPRepairRate;

		// 패널티는 100%가 넘을수 없다. 
		if(fTmp > 1.0f)
		{
			fTmp = 1.0f;
		}
		
		if(fTmp > 0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0005,(fTmp)*100);//"죽었을 경우 패널티 %.0f%% 감소"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}

	{
		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
		//fTmp = m_HappyEventInfo.fDropItemRate +m_HappyEventAllInfluInfo.fDropItemRate+m_PCHappyEventInfo.fDropItemRate;
		fTmp = m_HappyEventInfo.fDropItemRate +m_HappyEventAllInfluInfo.fDropItemRate+m_PCHappyEventInfo.fDropItemRate
				+m_MotherShipEventInfo.fDropItemRate+m_ItemEventInfo.fDropItemRate;
		if(fTmp>0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0006,(fTmp)*100);//"아이템 드롭율 %.0f%% 증가"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}

	{
		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
		//fTmp = m_HappyEventInfo.fSPIRate +m_HappyEventAllInfluInfo.fSPIRate+m_PCHappyEventInfo.fSPIRate;
		fTmp = m_HappyEventInfo.fSPIRate +m_HappyEventAllInfluInfo.fSPIRate+m_PCHappyEventInfo.fSPIRate
				+m_MotherShipEventInfo.fSPIRate+m_ItemEventInfo.fSPIRate;

		if(fTmp > 0)
		{
			sprintf(szNotice, STRMSG_C_EVENT_0007,(fTmp)*100);//"스피량 %.0f%% 증가"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}

	{
		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
		//fTmp = m_HappyEventInfo.fWarPointRate +m_HappyEventAllInfluInfo.fWarPointRate+m_PCHappyEventInfo.fWarPointRate;
		fTmp = m_HappyEventInfo.fWarPointRate +m_HappyEventAllInfluInfo.fWarPointRate+m_PCHappyEventInfo.fWarPointRate
				+m_MotherShipEventInfo.fWarPointRate +m_ItemEventInfo.fWarPointRate;

		if(fTmp >0)
		{
			sprintf(szNotice, STRMSG_C_070626_0100,(fTmp)*100);//"스피량 %.0f%% 증가"
			m_vecEventHappyHour.push_back(szNotice);
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourPcBang(BOOL bPcBang)
/// \brief		
/// \author		// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
/// \date		2007-07-04 ~ 2007-07-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourPcBang(BOOL bLevelup, BOOL bPcBang, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	m_bPcBangHappyHour = bPcBang;

	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	memset(&m_PCHappyEventInfo,0x00,sizeof(EVENT_INFO));
	
	if(m_bPcBangHappyHour)
	{
		SetHappyHourInfo(bLevelup, pMsg, &m_PCHappyEventInfo);
	}	

	// 해피 아우어 툴팁 갱신 
	UpdateHappyHourTooltip();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourMotherShip(BOOL bPcBang)
/// \brief		// 모선전 해피 아우어
/// \author		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
/// \date		2008-05-21 ~ 2008-05-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourMotherShip(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	m_bMotherHappyHour = bStart;

	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	memset(&m_MotherShipEventInfo,0x00,sizeof(EVENT_INFO));
	
	if(m_bMotherHappyHour)
	{
		SetHappyHourInfo(bLevelup, pMsg, &m_MotherShipEventInfo);
	}	

	// 해피 아우어 툴팁 갱신 
	UpdateHappyHourTooltip();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::SetHappyHourItem(BOOL bPcBang)
/// \brief		아이템 해피 아우어
/// \author		// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
/// \date		2008-05-21 ~ 2008-05-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::SetHappyHourItem(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg)
{
	m_bItemHappyHour = bStart;

	char szNotice[1024];
	memset(szNotice, 0x00, 1024);
	memset(&m_ItemEventInfo,0x00,sizeof(EVENT_INFO));
	
	if(m_bItemHappyHour)
	{
		SetHappyHourInfo(bLevelup, pMsg, &m_ItemEventInfo);
	}	

	// 해피 아우어 툴팁 갱신 
	UpdateHappyHourTooltip();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::InitHappyHourInfo()
/// \brief		
/// \author		// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
/// \date		2007-11-01 ~ 2007-11-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::InitHappyHourInfo()
{
	m_vecEventHappyHour.clear(); // 툴팁 정보 초기화

	memset(&m_HappyEventInfo, 0x00, sizeof(EVENT_INFO));				//세력 진형
	memset(&m_HappyEventAllInfluInfo, 0x00, sizeof(EVENT_INFO));		// 전체 진형
	memset(&m_PCHappyEventInfo, 0x00, sizeof(EVENT_INFO));				// pc방 
	
	m_bHappyHourAllInfluence = FALSE;
	m_byHappyHourInfluence = 0x00;
	m_bPcBangHappyHour = FALSE;

	// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
	m_bMotherHappyHour = FALSE;
	memset(&m_MotherShipEventInfo, 0x00, sizeof(EVENT_INFO));

	m_bItemHappyHour = FALSE;
	memset(&m_ItemEventInfo, 0x00, sizeof(EVENT_INFO));
	// end 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::AddGiftMsg(UINT i_NotifyMsgUID,UINT i_CharacterUID,char * NotifyString)
/// \brief		선물 메시지를 추가한다.
/// \author		dgwoo
/// \date		2007-11-28 ~ 2007-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::AddGiftMsg(UINT i_nNotifyMsgUID,UINT i_nCharacterUID,char * i_cNotifyString)
{
	GIFT_NOTIFY_MSG stGiftMsg;
	stGiftMsg.NotifyMsgUID = i_nNotifyMsgUID;
	stGiftMsg.CharacterUID = i_nCharacterUID;
	memcpy(stGiftMsg.NotifyMsgString,i_cNotifyString,SIZE_MAX_NOTIFY_MSG_STRING);
	m_vecGiftMsg.push_back(stGiftMsg);
	g_pGameMain->CreateChatChild(STRMSG_C_071129_0100 ,COLOR_ITEM);	
	m_fGiftTime = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFGameMainUnitInfoBar::CreateMsgBox()
/// \brief		메시지 박스를 띄운다.
/// \author		dgwoo
/// \date		2007-11-28 ~ 2007-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFGameMainUnitInfoBar::CreateMsgBox()
{
	if(m_vecGiftMsg.size())
	{
		vector<GIFT_NOTIFY_MSG>::iterator it = m_vecGiftMsg.begin();
		g_pGameMain->m_pInfWindow->AddMsgBox(it->NotifyMsgString,_Q_GIFT_ITEM_RING_IN,0,0,0,it->NotifyMsgUID);	
	}
}
void CINFGameMainUnitInfoBar::DeleteGiftMsg()
{
	if(m_vecGiftMsg.size())
	{
		vector<GIFT_NOTIFY_MSG>::iterator it = m_vecGiftMsg.begin();
		m_vecGiftMsg.erase(it);
	}
	else
	{
		m_fGiftTime = 0.0f;
	}
}
