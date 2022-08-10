// INFCityArena.cpp: implementation of the CINFCityArena class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFCityArena.h"
#include "AtumApplication.h"
#include "INFCitySupply.h"
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
#include "Interface.h"
#include "INFGameArena.h"
#include "INFListbox.h"

#define ARENA_START_X			(CITY_BASE_NPC_BOX_START_X)									// 윈도우 창 젤 앞단.
#define ARENA_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_ARENA_WINDOW_Y + 20)			// 바를 제외한 젤 윗단.

#define ARENA_CREATE_W					230
#define ARENA_CREATE_H					200
#define ARENA_START_CREATE_X			((g_pD3dApp->GetBackBufferDesc().Width - ARENA_CREATE_W ) /2 )
#define ARENA_START_CREATE_Y			((g_pD3dApp->GetBackBufferDesc().Height - ARENA_CREATE_H ) /2 )

#define ARENA_MATCH_LIST_GAP			20
#define ARENA_LIST_COUNT				8

#define ARENA_FONT_X					ARENA_START_X + 3
#define ARENA_FONT_Y					CITY_BASE_NPC_BOX_START_Y - SIZE_ARENA_WINDOW_Y + 2

#define ARENA_LIST_ROOM_X				ARENA_START_X + 9
#define ARENA_LIST_ROOM_Y				ARENA_START_Y + 4

#define ARENA_LIST_REFRESH_BUTTON_X		ARENA_START_X + 526
#define ARENA_LIST_REFRESH_BUTTON_Y		ARENA_START_Y + 3
#define ARENA_LIST_REFRESH_BUTTON_W		21
#define ARENA_LIST_REFRESH_BUTTON_H		19


#define ARENA_INFLURENCE_LIST_X				ARENA_START_X + 14
#define ARENA_INFLURENCE_LIST_Y				ARENA_START_Y + 3
#define ARENA_INFLURENCE_LIST_W				103
#define ARENA_INFLURENCE_LIST_H				17

#define ARENA_INFLURENCE_LIST_ITEM_X		(ARENA_INFLURENCE_LIST_X)
#define ARENA_INFLURENCE_LIST_ITEM_Y		(ARENA_INFLURENCE_LIST_Y + ARENA_INFLURENCE_LIST_H)
#define ARENA_INFLURENCE_LIST_ITEM_W		103
#define ARENA_INFLURENCE_LIST_ITEM_H		13

#define ARENA_WAR_STATE_X					ARENA_START_X + 118
#define ARENA_WAR_STATE_Y					ARENA_START_Y + 3
#define ARENA_WAR_STATE_W					103
#define ARENA_WAR_STATE_H					17

#define ARENA_WAR_STATE_ITEM_X				(ARENA_WAR_STATE_X)
#define ARENA_WAR_STATE_ITEM_Y				(ARENA_WAR_STATE_Y + ARENA_WAR_STATE_H)
#define ARENA_WAR_STATE_ITEM_W				103
#define ARENA_WAR_STATE_ITEM_H				13

#define ARENA_WAR_STATE_COUNT				3

#define ARENA_LIST_OPTION_H					13
// 검색 버튼.
#define ARENA_TEAM_SEARCH_BUTTON_X		ARENA_START_X + 225
#define ARENA_TEAM_SEARCH_BUTTON_Y		ARENA_START_Y + 3
#define ARENA_TEAM_SEARCH_BUTTON_W		47//38			// 2007-08-02 by dgwoo 해외이미지가 크기에 맞춰서 
#define ARENA_TEAM_SEARCH_BUTTON_H		17

#define ARENA_LIST_ROOM_NUMBER_FONT_X		ARENA_START_X + 60
#define ARENA_LIST_ROOM_NUMBER_FONT_Y		ARENA_START_Y + 72

#define ARENA_LIST_ROOM_ID_FONT_X		ARENA_START_X + 67 + 80
#define	ARENA_LIST_ROOM_ID_FONT_Y		ARENA_START_Y + 72

// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
#define ARENA_LIST_ROOM_EVENT_FONT_X		(ARENA_START_X + 67)
#define	ARENA_LIST_ROOM_EVENT_FONT_Y		(ARENA_START_Y + 72)

#define ARENA_LIST_ROOM_MODE_X			ARENA_START_X + 277//233
#define ARENA_LIST_ROOM_MODE_Y			ARENA_START_Y + 76

#define ARENA_LIST_ROOM_LEVEL_X			ARENA_START_X + 348
#define ARENA_LIST_ROOM_LEVEL_Y			ARENA_START_Y + 72

#define ARENA_LIST_ROOM_PERSON_X		ARENA_START_X + 392
#define ARENA_LIST_ROOM_PERSON_Y		ARENA_START_Y + 72

#define ARENA_LIST_ROOM_LOCK_X			ARENA_START_X + 425
#define ARENA_LIST_ROOM_LOCK_Y			ARENA_START_Y + 72

#define ARENA_LIST_ROOM_STATE_X			ARENA_START_X + 480
#define ARENA_LIST_ROOM_STATE_Y			ARENA_START_Y + 72

#define ARENA_LIST_SELECT_X				ARENA_START_X + 26
#define ARENA_LIST_SELECT_Y				ARENA_START_Y + 70

#define ARENA_LIST_W					490
#define ARENA_LIST_H					168

//--------------------------------------------------------------------------//
//							스크롤
#define ARENA_LIST_SCROLL_LINE_LENGTH	195
#define ARENA_LIST_SCROLL_WHELL_AREA_X	(ARENA_START_X + 24)
#define ARENA_LIST_SCROLL_WHELL_AREA_Y	(ARENA_START_Y + 46)
#define ARENA_LIST_SCROLL_WHELL_AREA_W	(ARENA_LIST_SCROLL_WHELL_AREA_X + 525)
#define ARENA_LIST_SCROLL_WHELL_AREA_H	(ARENA_LIST_SCROLL_WHELL_AREA_Y + 185)

#define ARENA_LIST_SCROLL_DRAG_AREA_X	(ARENA_START_X + 518)
#define ARENA_LIST_SCROLL_DRAG_AREA_Y	(ARENA_START_Y + 43)
#define ARENA_LIST_SCROLL_DRAG_AREA_W	(ARENA_LIST_SCROLL_DRAG_AREA_X + 18)
#define ARENA_LIST_SCROLL_DRAG_AREA_H	(ARENA_LIST_SCROLL_DRAG_AREA_Y + 150)

// 2007-05-15 by bhsohn 스크롤 관련 버그 수정
#define	ARENA_LIST_SCROLL_DRAG_BALL_CAP		55
//--------------------------------------------------------------------------//





//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityArena::CINFCityArena(CAtumNode* pParent, BUILDINGNPC* pBuilding, CGameData *pGameData)
{
	m_pParent = pParent;	// CGameMain*
	m_pGameData = pGameData;
	m_pBuildingInfo = pBuilding;

	m_nTab = 0;
	m_BArenaMode = ARENAMODE_DEATHMATCH;
	
	m_nTeamInfoB = BUTTON_STATE_NORMAL;
	m_nRefresh = BUTTON_STATE_NORMAL;
	m_nSearch = BUTTON_STATE_NORMAL;

	m_pArenaCreate = NULL;
	m_nSelectIndex = -1;

	m_BRequestTeamState = ARENA_REQUEST_TEAM_STATE_OUR;
	

	if(m_pArenaCreate == NULL)
	{
		m_pArenaCreate = new CINFArenaCreate(this, m_pBuildingInfo);
		m_pArenaCreate->SetGameData(m_pGameData);
//		m_pArenaCreate->InitDeviceObjects();
//		m_pArenaCreate->RestoreDeviceObjects();
	}

	// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
	m_pBoldFont = NULL;

}

CINFCityArena::~CINFCityArena()
{

}
HRESULT CINFCityArena::DeleteDeviceObjects()
{
	int i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgRefreshB[i]->DeleteDeviceObjects();
		m_pImgSearch[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgRefreshB[i]);
		SAFE_DELETE(m_pImgSearch[i]);

	}
	for(i = 0 ; i < ARENA_ROOM_LOCKMODE ; i++)
	{
		m_pImgLock[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgLock[i]);
	}
	for(i = 0 ; i < ARENA_WAR_MODE_END ; i++)
	{
		m_pImgArenaMode[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgArenaMode[i]);
	}
	m_pLBoxInf->DeleteDeviceObjects();
	m_pLBoxState->DeleteDeviceObjects();
	m_pScroll->DeleteDeviceObjects();
	m_pFontRoomNum->DeleteDeviceObjects();
	// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
	m_pBoldFont->DeleteDeviceObjects();	 

	m_pFontUserID->DeleteDeviceObjects();
	m_pFontPerson->DeleteDeviceObjects();
	m_pFontState->DeleteDeviceObjects();
	m_pFontLevel->DeleteDeviceObjects();
	
	SAFE_DELETE(m_pLBoxInf);
	SAFE_DELETE(m_pLBoxState);
	SAFE_DELETE(m_pScroll);
	SAFE_DELETE(m_pFontRoomNum);
	// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
	SAFE_DELETE(m_pBoldFont);	

	SAFE_DELETE(m_pFontUserID);
	SAFE_DELETE(m_pFontPerson);
	SAFE_DELETE(m_pFontState);
	SAFE_DELETE(m_pFontLevel);

	
	m_pImgSelectTeam->DeleteDeviceObjects();
	m_pImgAreRoomList->DeleteDeviceObjects();
	m_pImgAreFont->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgSelectTeam);
	SAFE_DELETE(m_pImgAreRoomList);
	SAFE_DELETE(m_pImgAreFont);

	m_pArenaCreate->DeleteDeviceObjects();

	return S_OK;
}
HRESULT CINFCityArena::InitDeviceObjects()
{
	int i;
	DataHeader	* pDataHeader;
	char buf[64];
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		wsprintf( buf, "refresh%d", i);
		pDataHeader = FindResource(buf);
		m_pImgRefreshB[i] = new CINFImage;
		m_pImgRefreshB[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
		wsprintf( buf, "searchb%d", i);
		pDataHeader = FindResource(buf);
		m_pImgSearch[i] = new CINFImage;
		m_pImgSearch[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );


	}
	for(i = 0 ; i < ARENA_ROOM_LOCKMODE ; i++)
	{
		wsprintf( buf, "lock%d", i);
		pDataHeader = FindResource(buf);
		m_pImgLock[i] = new CINFImage;
		m_pImgLock[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	}
	for(i = 0 ; i < ARENA_WAR_MODE_END ; i++)
	{
		wsprintf( buf, "amode%d", i);
		pDataHeader = FindResource(buf);
		m_pImgArenaMode[i] = new CINFImage;
		m_pImgArenaMode[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	}
	//--------------------------------------------------------------------------//
	// 리스트 박스 설정.
	if(NULL == m_pLBoxInf)
	{
		m_pLBoxInf = new CINFListBox("cbarena","cbarenab");
		m_pLBoxInf->AddElement(STRMSG_C_080225_0200);
		m_pLBoxInf->AddElement(STRMSG_C_080225_0201);
		// 2007-11-22 by bhsohn 아레나 통합서버
//		if(COMPARE_INFLUENCE(g_pShuttleChild->m_myShuttleInfo.InfluenceType,INFLUENCE_TYPE_ANI))
//			m_pLBoxInf->m_nSelect = 1;
		m_pLBoxInf->UpdateItem();
		m_pLBoxInf->SetMainArea(ARENA_INFLURENCE_LIST_X,ARENA_INFLURENCE_LIST_Y,ARENA_INFLURENCE_LIST_W,ARENA_INFLURENCE_LIST_H);
		m_pLBoxInf->SetElementArea(ARENA_INFLURENCE_LIST_ITEM_X,ARENA_INFLURENCE_LIST_ITEM_Y,ARENA_INFLURENCE_LIST_ITEM_W,ARENA_INFLURENCE_LIST_ITEM_H);
		m_pLBoxInf->InitDeviceObjects();
	}
	if(NULL == m_pLBoxState)
	{
		m_pLBoxState = new CINFListBox("cbarena","cbarenab");
		m_pLBoxState->AddElement(STRMSG_C_070608_0102);
		m_pLBoxState->AddElement(STRMSG_C_070608_0103);
		m_pLBoxState->UpdateItem();
		m_pLBoxState->SetMainArea(ARENA_WAR_STATE_X,ARENA_WAR_STATE_Y,ARENA_WAR_STATE_W,ARENA_WAR_STATE_H);
		m_pLBoxState->SetElementArea(ARENA_WAR_STATE_ITEM_X,ARENA_WAR_STATE_ITEM_Y,ARENA_WAR_STATE_ITEM_W,ARENA_WAR_STATE_ITEM_H);
		m_pLBoxState->InitDeviceObjects();

	}
	//--------------------------------------------------------------------------//

	char szScBall[30];	
	if(NULL == m_pScroll)
	{
		m_pScroll = new CINFArenaScrollBar;
	}
	//wsprintf(szScBk,"arescroll");
	wsprintf(szScBall,"c_scrlb");				

	m_pScroll->InitDeviceObjects(ARENA_LIST_COUNT, szScBall);

	
	m_pFontRoomNum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontRoomNum->InitDeviceObjects(g_pD3dDev);
	// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
	m_pBoldFont = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE|D3DFONT_BOLD, FALSE,128,32);
	m_pBoldFont->InitDeviceObjects(g_pD3dDev);	

	m_pFontUserID = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontUserID->InitDeviceObjects(g_pD3dDev);
	m_pFontPerson = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontPerson->InitDeviceObjects(g_pD3dDev);
	m_pFontState = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontState->InitDeviceObjects(g_pD3dDev);
	m_pFontLevel = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontLevel->InitDeviceObjects(g_pD3dDev);


	pDataHeader = FindResource("selectteam");
	m_pImgSelectTeam = new CINFImage;
	m_pImgSelectTeam->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	
	pDataHeader = FindResource("matchtab");
	m_pImgAreRoomList = new CINFImage;
	m_pImgAreRoomList->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

	pDataHeader = FindResource("arenafont");
	m_pImgAreFont = new CINFImage;
	m_pImgAreFont->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

	m_pArenaCreate->InitDeviceObjects();
	return S_OK;
}
HRESULT CINFCityArena::RestoreDeviceObjects()
{
	int i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgRefreshB[i]->RestoreDeviceObjects();
		m_pImgSearch[i]->RestoreDeviceObjects();
	}
	for(i = 0 ; i < ARENA_ROOM_LOCKMODE ; i++)
	{
		m_pImgLock[i]->RestoreDeviceObjects();
	}
	for(i = 0 ; i < ARENA_WAR_MODE_END ; i++)
	{
		m_pImgArenaMode[i]->RestoreDeviceObjects();
	}

	RECT rc;

	// 휠마우스 위치 영역.
	rc.left		= ARENA_LIST_SCROLL_WHELL_AREA_X;
	rc.top		= ARENA_LIST_SCROLL_WHELL_AREA_Y;
	rc.bottom	= ARENA_LIST_SCROLL_WHELL_AREA_H;
	rc.right	= ARENA_LIST_SCROLL_WHELL_AREA_W;
	m_pScroll->SetMouseWhellRect(rc);

	// 마우스 클릭 후 드레그 가능 영역.
	rc.left		= ARENA_LIST_SCROLL_DRAG_AREA_X;
	rc.top		= ARENA_LIST_SCROLL_DRAG_AREA_Y;
    // 2007-05-15 by bhsohn 스크롤 관련 버그 수정
	rc.bottom	= ARENA_LIST_SCROLL_DRAG_AREA_H+ARENA_LIST_SCROLL_DRAG_BALL_CAP;
	rc.right	= ARENA_LIST_SCROLL_DRAG_AREA_W;
	m_pScroll->SetMouseBallRect(rc);

	// 스크롤 인식 범위.
	m_pScroll->SetPosition(ARENA_LIST_SCROLL_DRAG_AREA_X, ARENA_LIST_SCROLL_DRAG_AREA_Y
		, (ARENA_LIST_SCROLL_DRAG_AREA_W)-(ARENA_LIST_SCROLL_DRAG_AREA_X), 
		(ARENA_LIST_SCROLL_DRAG_AREA_H)-(ARENA_LIST_SCROLL_DRAG_AREA_Y));
	m_pScroll->RestoreDeviceObjects();					


	m_pLBoxInf->RestoreDeviceObjects();
	m_pLBoxState->RestoreDeviceObjects();
	m_pFontRoomNum->RestoreDeviceObjects();
	// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
	m_pBoldFont->RestoreDeviceObjects();	 

	m_pFontUserID->RestoreDeviceObjects();
	m_pFontPerson->RestoreDeviceObjects();
	m_pFontState->RestoreDeviceObjects();
	m_pFontLevel->RestoreDeviceObjects();

	m_pImgSelectTeam->RestoreDeviceObjects();
	m_pImgAreRoomList->RestoreDeviceObjects();
	m_pImgAreFont->RestoreDeviceObjects();

	m_pArenaCreate->RestoreDeviceObjects();

	return S_OK;
}
HRESULT CINFCityArena::InvalidateDeviceObjects()
{
	int i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgRefreshB[i]->InvalidateDeviceObjects();
		m_pImgSearch[i]->InvalidateDeviceObjects();
	}
	for(i = 0 ; i < ARENA_ROOM_LOCKMODE ; i++)
	{
		m_pImgLock[i]->InvalidateDeviceObjects();

	}
	for(i = 0 ; i < ARENA_WAR_MODE_END ; i++)
	{
		m_pImgArenaMode[i]->InvalidateDeviceObjects();
	}
	m_pLBoxInf->InvalidateDeviceObjects();
	m_pLBoxState->InvalidateDeviceObjects();
	m_pScroll->InvalidateDeviceObjects();
	m_pFontRoomNum->InvalidateDeviceObjects();
	// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
	m_pBoldFont->InvalidateDeviceObjects();
	
	m_pFontUserID->InvalidateDeviceObjects();
	m_pFontPerson->InvalidateDeviceObjects();
	m_pFontLevel->InvalidateDeviceObjects();
	m_pFontState->InvalidateDeviceObjects();

	
	m_pImgSelectTeam->InvalidateDeviceObjects();
	m_pImgAreRoomList->InvalidateDeviceObjects();
	m_pImgAreFont->InvalidateDeviceObjects();

	m_pArenaCreate->InvalidateDeviceObjects();
	return S_OK;
}
void CINFCityArena::Render()
{
	char buf[64];
	m_pImgAreRoomList->Move(ARENA_LIST_ROOM_X,ARENA_LIST_ROOM_Y);
	m_pImgAreRoomList->Render();

	m_pImgAreFont->Move(ARENA_FONT_X,ARENA_FONT_Y);
	m_pImgAreFont->Render();

//	m_pImgRefreshB[m_nRefresh]->Move(ARENA_LIST_REFRESH_BUTTON_X,ARENA_LIST_REFRESH_BUTTON_Y);
//	m_pImgRefreshB[m_nRefresh]->Render();
	m_pImgSearch[m_nSearch]->Move(ARENA_TEAM_SEARCH_BUTTON_X,ARENA_TEAM_SEARCH_BUTTON_Y);
	m_pImgSearch[m_nSearch]->Render();

	m_pLBoxInf->Render();
	m_pLBoxState->Render();


	m_pScroll->Render();

	SIZE size;
	int i=0;
	// Temp
	
	// 2008-02-25 by bhsohn 아레나 유저 정보 서버도 표시하게 변경
	//vector<SARENA_TEAM_INFO>::iterator it = m_vecTeamList.begin();
	vector<STRUCT_TEAM_INFO>::iterator it = m_vecTeamList.begin();

	int nCnt = 0;
	for(nCnt = 0;nCnt < m_pScroll->GetScrollStep(); nCnt++)
	{
		if(it == m_vecTeamList.end())
		{
			break;
		}
		// 스크롤 스텝
		it++;
	}
	for(i = 0 ; i < ARENA_LIST_COUNT ; i++)
	{
		if(it == m_vecTeamList.end())
		{// 리스트가 없을시에 통과.
			break;
		}
		// 방번호.
		wsprintf(buf,"%d",it->TeamNum);
		size = m_pFontRoomNum->GetStringSize(buf);
		m_pFontRoomNum->DrawText(ARENA_LIST_ROOM_NUMBER_FONT_X - size.cx,
			ARENA_LIST_ROOM_NUMBER_FONT_Y + (ARENA_MATCH_LIST_GAP * i),
			GUI_FONT_COLOR_W,
			buf);

		// 유저 ID
		if(ARENA_REQUEST_TEAM_STATE_OTHER == m_BRequestTeamState)
			wsprintf(buf,STRMSG_C_070612_0100);
		else
			wsprintf(buf,"%s",it->CharacterName);
		size = m_pFontUserID->GetStringSize(buf);
		// 2008-03-10 by bhsohn 이벤트 아레나방 관련처리
		float fNamePosX = ARENA_LIST_ROOM_ID_FONT_X - (size.cx/2);
		if(it->TeamEvent)
		{			
			float fEventPosX = ARENA_LIST_ROOM_EVENT_FONT_X;
			char szEventbuf[64];
			wsprintf(szEventbuf,STRMSG_C_080225_0206);
			m_pBoldFont->DrawText(fEventPosX,
				ARENA_LIST_ROOM_EVENT_FONT_Y + (ARENA_MATCH_LIST_GAP * i),
				GUI_FONT_COLOR_W,
				szEventbuf);
			// 위치갱신
			SIZE sizeEvent = m_pBoldFont->GetStringSize(szEventbuf);
			fNamePosX = (sizeEvent.cx/2) + ARENA_LIST_ROOM_ID_FONT_X - (size.cx/2);
		}		

		//m_pFontRoomNum->DrawText(ARENA_LIST_ROOM_ID_FONT_X - (size.cx/2),
		m_pFontRoomNum->DrawText(fNamePosX,
			ARENA_LIST_ROOM_ID_FONT_Y + (ARENA_MATCH_LIST_GAP * i),
			GUI_FONT_COLOR_W,
			buf);

		// 모드.
		// it->Arenamode 1 : 데스매치 2 : 라운드아레나.
		m_pImgArenaMode[it->ArenaMode-1]->Move(ARENA_LIST_ROOM_MODE_X - (m_pImgArenaMode[it->ArenaMode-1]->GetImgSize().x / 2) 
			,ARENA_LIST_ROOM_MODE_Y + (ARENA_MATCH_LIST_GAP * i));
		m_pImgArenaMode[it->ArenaMode-1]->Render();

		// 레벨 
		wsprintf(buf,"%d-%d",it->TeamStartLevel,it->TeamEndLevel);
		size = m_pFontLevel->GetStringSize(buf);
		m_pFontLevel->DrawText(ARENA_LIST_ROOM_LEVEL_X - (size.cx/2),
			ARENA_LIST_ROOM_LEVEL_Y + (ARENA_MATCH_LIST_GAP * i),
			GUI_FONT_COLOR_W,
			buf);


		// 인원수.
		wsprintf(buf,"%d/%d",it->CurrentTeamSize,it->TeamSize);
		size = m_pFontPerson->GetStringSize(buf);
		m_pFontPerson->DrawText(ARENA_LIST_ROOM_PERSON_X - (size.cx/2),
			ARENA_LIST_ROOM_PERSON_Y + (ARENA_MATCH_LIST_GAP * i),
			GUI_FONT_COLOR_W,
			buf);
		// 공개 여부.
		m_pImgLock[it->TeamLock]->Move(ARENA_LIST_ROOM_LOCK_X,ARENA_LIST_ROOM_LOCK_Y + (ARENA_MATCH_LIST_GAP * i));
		m_pImgLock[it->TeamLock]->Render();

		// 상태.
		if(it->ArenaState == ARENA_STATE_JOINING 
			|| it->ArenaState == ARENA_STATE_READY)
		{
			wsprintf(buf,STRMSG_C_070607_0100);
			size = m_pFontState->GetStringSize(buf);
			m_pFontState->DrawText(ARENA_LIST_ROOM_STATE_X - (size.cx/2),
				ARENA_LIST_ROOM_STATE_Y + (ARENA_MATCH_LIST_GAP * i),
				GUI_FONT_COLOR_G,
				buf);
		}
		else if(it->ArenaState == ARENA_STATE_READY_FINISH)
		{
			wsprintf(buf,STRMSG_C_070607_0101);
			size = m_pFontState->GetStringSize(buf);
			m_pFontState->DrawText(ARENA_LIST_ROOM_STATE_X - (size.cx/2),
				ARENA_LIST_ROOM_STATE_Y + (ARENA_MATCH_LIST_GAP * i),
				GUI_FONT_COLOR_Y,
				buf);
		}
		else if(it->ArenaState > ARENA_STATE_READY_FINISH)
		{
			wsprintf(buf,STRMSG_C_070607_0102);
			size = m_pFontState->GetStringSize(buf);
			m_pFontState->DrawText(ARENA_LIST_ROOM_STATE_X - (size.cx/2),
				ARENA_LIST_ROOM_STATE_Y + (ARENA_MATCH_LIST_GAP * i),
				GUI_FONT_COLOR_R,
				buf);
		}

		// 현재 선택한 목록인가.
		if(m_nSelectIndex == i)
		{
			m_pImgSelectTeam->Move(ARENA_LIST_SELECT_X,ARENA_LIST_SELECT_Y + (ARENA_MATCH_LIST_GAP * i));
			m_pImgSelectTeam->Render();
		}
		it++;

	}
	if(m_pArenaCreate)
		m_pArenaCreate->Render();

}

VOID CINFCityArena::CreateRoom()
{
	// 아레나에 참가한 상태라면 리턴.
	if(g_pInterface->m_pGameArena)
	{
		if(g_pInterface->m_pGameArena->IsArenaGameState(ARENA_GAME_STATE_NORMAL))
		{
			return;
		}
	}
	// 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	if(TRUE == g_pD3dApp->IsDoingInfluenceWar())
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070427_0104,COLOR_ERROR); //"세력전이 진행 중이므로 참가할 수 없습니다."
		return;
	}
	// end 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	// 2008-03-10 by bhsohn 아레나 관련 버그 수정
	if(TRUE == g_pInterface->IsArenaGameState(ARENA_GAME_STATE_TEAMINFO))
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0207,COLOR_ERROR);//"이미 아레나 대기방에 참여중입니다."
		return;	
	}
	// end 2008-03-10 by bhsohn 아레나 관련 버그 수정

	m_pArenaCreate->ShowCreateWindow();
	m_pArenaCreate->SetPos(ARENA_START_CREATE_X,ARENA_START_CREATE_Y);
	g_pFieldWinSocket->SendMsg(T_FC_ARENA_REQUEST_CREATE_TEAMINFO,NULL,0);
}
VOID CINFCityArena::Init()
{
	if(m_pArenaCreate)
		m_pArenaCreate->m_bShow = FALSE;
}

BOOL CINFCityArena::App()
{
	// 아레나에 참가한 상태라면 리턴.
	if(g_pInterface->m_pGameArena)
	{
		if(g_pInterface->m_pGameArena->IsArenaGameState(ARENA_GAME_STATE_NORMAL))
		{
			return FALSE;
		}
	}
	// 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	if(TRUE == g_pD3dApp->IsDoingInfluenceWar())
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070427_0104,COLOR_ERROR); //"세력전이 진행 중이므로 참가할 수 없습니다."
		return FALSE;
	}
	// end 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	// 2008-03-10 by bhsohn 아레나 관련 버그 수정
	if(TRUE == g_pInterface->IsArenaGameState(ARENA_GAME_STATE_TEAMINFO))
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0207,COLOR_ERROR);//"이미 아레나 대기방에 참여중입니다."
		return FALSE;	
	}
	// end 2008-03-10 by bhsohn 아레나 관련 버그 수정

	// 2008-02-25 by bhsohn 아레나 유저 정보 서버도 표시하게 변경
	//SARENA_TEAM_INFO * TeamInfo = GetSelectListTeam();
	STRUCT_TEAM_INFO* TeamInfo = GetSelectListTeam();
	if(TeamInfo == NULL)
		return FALSE;
	if(TeamInfo->TeamLock)
	{// 비번이 있을경우.
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_070430_0100, _Q_ARENA_PASSWORD);
	}else
	{// 비번이 없을경우.
		// 2007-11-22 by bhsohn 아레나 통합서버
//		MSG_FC_ARENA_ENTER_TEAM sMsg;
//		sMsg.ArenaMode = TeamInfo->ArenaMode;
//		sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
//		sMsg.TeamNum = TeamInfo->TeamNum;
//		memset(sMsg.TeamPW,0x00,sizeof(sMsg.TeamPW));
//		g_pFieldWinSocket->SendMsg(T_FC_ARENA_ENTER_TEAM,(char*)&sMsg,sizeof(sMsg));
		SendArenaEnterRoom(NULL);
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			VOID CINFCityArena::EnemyInfo()
/// \brief		상대팀정보 요청.
/// \author		dgwoo
/// \date		2007-05-25 ~ 2007-05-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFCityArena::EnemyInfo()
{
	MSG_FC_ARENA_REQUEST_TEAM sMsg;
	memset(&sMsg, 0x00, sizeof(MSG_FC_ARENA_REQUEST_TEAM));
	
	sMsg.ArenaMode = m_BArenaMode;
	// 2007-11-22 by bhsohn 아레나 통합서버
	//sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
	CHARACTER*	pArenaCharacterInfo = g_pD3dApp->GetArenaCharacterInfo();
	sMsg.ClientIndex = pArenaCharacterInfo->ClientIndex;
	// end 2007-11-22 by bhsohn 아레나 통합서버

	m_BRequestTeamState = ARENA_REQUEST_TEAM_STATE_OTHER;
	sMsg.RequestTeamState = m_BRequestTeamState;
	sMsg.StartTeamNum = -1;
	g_pFieldWinSocket->SendMsg(T_FC_ARENA_REQUEST_TEAM,(char*)&sMsg,sizeof(sMsg));

	// 2007-11-22 by bhsohn 아레나 통합서버
	// Lock
	{
		vector<MessageType_t> vecUnLockMsg;
		vecUnLockMsg.clear();
		vecUnLockMsg.push_back(T_FC_ARENA_REQUEST_TEAM);		
		vecUnLockMsg.push_back(T_FC_ARENA_REQUEST_TEAM_OK);		
		// 하나만 매칭 되어도 락이 풀린다. 
		g_pD3dApp->EnterMultiLock(TRUE, T_FC_ARENA_REQUEST_TEAM, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
	}
	
	// end 2007-11-22 by bhsohn 아레나 통합서버
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			VOID CINFCityArena::QuickApp()
/// \brief		빠른 신청.
/// \author		dgwoo
/// \date		2007-06-07 ~ 2007-06-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFCityArena::QuickApp()
{
	// 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	if(TRUE == g_pD3dApp->IsDoingInfluenceWar())
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070427_0104,COLOR_ERROR); //"세력전이 진행 중이므로 참가할 수 없습니다."
		return;
	}
	// end 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	// 2008-03-10 by bhsohn 아레나 관련 버그 수정
	if(TRUE == g_pInterface->IsArenaGameState(ARENA_GAME_STATE_TEAMINFO))
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0207,COLOR_ERROR);//"이미 아레나 대기방에 참여중입니다."
		return ;	
	}
	// end 2008-03-10 by bhsohn 아레나 관련 버그 수정
	g_pFieldWinSocket->SendMsg(T_FC_ARENA_QUICK_ENTER_TEAM,NULL,0);
}
// 2008-02-25 by bhsohn 아레나 유저 정보 서버도 표시하게 변경
//SARENA_TEAM_INFO* CINFCityArena::GetSelectListTeam()
STRUCT_TEAM_INFO* CINFCityArena::GetSelectListTeam()
{
	if(m_nSelectIndex < 0)
		return NULL;
	int nStep = m_pScroll->GetScrollStep();
	nStep = nStep + m_nSelectIndex;
	if(m_vecTeamList.size() <= nStep)
		return NULL;
	return &m_vecTeamList[nStep];
	
}

VOID CINFCityArena::AppCancel()
{
	if(m_pArenaCreate)
	{
		m_pArenaCreate->m_bShow = FALSE;
	}
	// 2007-11-22 by bhsohn 아레나 통합서버
//	MSG_FC_ARENA_REAVE_TEAM sMsg;
//	sMsg.ArenaMode = m_BArenaMode;
//	sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
	if(g_pInterface->m_pGameArena->GetTeamNum() >= 0)
	{// 방번호가 없을때는 오류.
//		sMsg.TeamNum = g_pInterface->m_pGameArena->GetTeamNum();
//		g_pFieldWinSocket->SendMsg(T_FC_ARENA_REAVE_TEAM,(char*)&sMsg,sizeof(sMsg));
		g_pInterface->m_pGameArena->SendArenaLeaveTeam(m_BArenaMode);

	}
	
}
VOID CINFCityArena::ReFresh()
{
	// 2007-11-22 by bhsohn 아레나 통합서버
//	MSG_FC_ARENA_REQUEST_TEAM sMsg;
//	sMsg.ArenaMode = m_BArenaMode;					
//	//sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
//	sMsg.ClientIndex = pArenaCharacterInfo->ClientIndex;
//	sMsg.RequestTeamState = m_BRequestTeamState;
//	sMsg.StartTeamNum = -1;
//	m_vecTeamList.clear();
//	g_pFieldWinSocket->SendMsg(T_FC_ARENA_REQUEST_TEAM,(char*)&sMsg,sizeof(sMsg));
	m_vecTeamList.clear();
	SendArenaRequestTeam(-1);	
}

BYTE CINFCityArena::ChangeTab(BYTE BMode)
{
	m_nTab = BMode;
	return BMode;
}
VOID CINFCityArena::AllModePersonInfo(MSG_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK *pMsg)
{
	SARENA_REQUEST_CREATE_TEAMINFO *pTeamInfo = (SARENA_REQUEST_CREATE_TEAMINFO *)((char *)pMsg + sizeof(MSG_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK));
	int i = 0;
	m_pArenaCreate->m_nMode = 0;
	m_pArenaCreate->ClearAllPersons();
	for(i = 0 ; i < pMsg->ArenaRequetCreateTeamInfoListCount ; i++)
	{
		m_pArenaCreate->AddAllPersons(pTeamInfo);
		pTeamInfo++;
	}
	// 현재 등록된 인원수를 모드에 맞게 다시 셋팅해준다.
	m_pArenaCreate->SetPersons(m_pArenaCreate->m_nSelectMode);

}
void CINFCityArena::TestDB()
{
	int nItemLen = 10;
	long lBuffLen = sizeof(MSG_FC_ARENA_REQUEST_TEAM_OK)+(sizeof(SARENA_TEAM_INFO)*nItemLen);
	MSG_FC_ARENA_REQUEST_TEAM_OK *pMsg = (MSG_FC_ARENA_REQUEST_TEAM_OK *)malloc(lBuffLen);
	memset(pMsg, 0x00, lBuffLen);

	SARENA_TEAM_INFO *pTeamInfo = (SARENA_TEAM_INFO *)((char *)pMsg + sizeof(MSG_FC_ARENA_REQUEST_TEAM_OK));

	pMsg->ArenaTeamInfoTotalCount = nItemLen;
	pMsg->ArenaTeamInfoListCount = nItemLen;

	for(int nCnt = 0;nCnt < nItemLen;nCnt++)
	{
		pTeamInfo->TeamLock = 0;
		pTeamInfo->TeamSize = 6;
		pTeamInfo->CurrentTeamSize = 1;
		pTeamInfo->ArenaMode = 1;		
		pTeamInfo->TeamNum = 0;
		wsprintf(pTeamInfo->CharacterName, "Team%d", nCnt);
		pTeamInfo++;
	}
	ArenaTeamListInput(pMsg);
	free(pMsg);
}

VOID CINFCityArena::ArenaTeamListInput(MSG_FC_ARENA_REQUEST_TEAM_OK *pMsg)
{
	SARENA_TEAM_INFO *pTeamInfo = (SARENA_TEAM_INFO*)((char *)pMsg + sizeof(MSG_FC_ARENA_REQUEST_TEAM_OK));
// 2007-10-25 by dgwoo
//	m_vecTeamList.clear();
	m_nTeamTotalCount =  pMsg->ArenaTeamInfoTotalCount;
	m_BRequestTeamState = pMsg->RequetTeamState;
	int i = 0;
	for(i = 0 ; i < pMsg->ArenaTeamInfoListCount ; i++)
	{
		// 2008-02-25 by bhsohn 아레나 유저 정보 서버도 표시하게 변경
		STRUCT_TEAM_INFO sTeamInfo;
		memset(&sTeamInfo, 0x00, sizeof(STRUCT_TEAM_INFO));
		{			
			sTeamInfo.TeamLock = pTeamInfo->TeamLock;
			sTeamInfo.TeamEvent = pTeamInfo->TeamEvent;
			sTeamInfo.TeamSize = pTeamInfo->TeamSize;			
			sTeamInfo.CurrentTeamSize = pTeamInfo->CurrentTeamSize;		
			sTeamInfo.ArenaMode = pTeamInfo->ArenaMode;		
			sTeamInfo.ArenaState = pTeamInfo->ArenaState;					
			sTeamInfo.TeamStartLevel = pTeamInfo->TeamStartLevel;					
			sTeamInfo.TeamEndLevel = pTeamInfo->TeamEndLevel;					
			sTeamInfo.TeamNum = pTeamInfo->TeamNum;								
			strncpy(sTeamInfo.CharacterName, pTeamInfo->CharacterName, SIZE_MAX_CHARACTER_NAME);
		}		
		g_pD3dApp->ConevertArenaRenderUserName(ARENA_STATE_ARENA_GAMING, sTeamInfo.CharacterName);
		//m_vecTeamList.push_back((*pTeamInfo));
		m_vecTeamList.push_back(sTeamInfo);
		// end 2007-11-22 by bhsohn 아레나 통합서버
		
		
		pTeamInfo++;
	}
	m_pScroll->SetOnlyMaxItem(m_nTeamTotalCount);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityArena::IsInfluenceEqual()
/// \brief		리스트창의 선택한 값이 나와 같은 세력이라면. 
/// \author		dgwoo
/// \date		2007-06-11 ~ 2007-06-11
/// \warning	
///
/// \param		
/// \return		같은세력 : TRUE    ,    다른 세력 : FALSE
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityArena::IsInfluenceEqual()
{
	// 2007-11-22 by bhsohn 아레나 통합서버
//	BOOL bBCUInfSelect = FALSE;
//	BOOL bBCUInfCha	= FALSE;
//	if(m_pLBoxInf->GetSelect() == 0)
//		bBCUInfSelect = TRUE;
//	if(COMPARE_INFLUENCE(g_pShuttleChild->m_myShuttleInfo.InfluenceType,INFLUENCE_TYPE_VCN))
//		bBCUInfCha = TRUE;
//	if(bBCUInfSelect == bBCUInfCha)
//		return TRUE;
//	else
//		return FALSE;
	// 아군이 처음으로 바뀌었다.
	if(m_pLBoxInf->GetSelect() == 0)
	{
		return TRUE;
	}
	return FALSE;
}
VOID CINFCityArena::RequestTeamList()
{
	m_vecTeamList.clear();
	// 2007-10-26 by dgwoo 갱신시 스크롤 초기화.
	m_pScroll->SetMaxItem(1);		
	m_nTeamTotalCount = 0;

	if(IsInfluenceEqual())
	{
		// 2007-11-22 by bhsohn 아레나 통합서버
		// 같은 세력이면.
//		MSG_FC_ARENA_REQUEST_TEAM sMsg;
//		sMsg.ArenaMode = m_BArenaMode;
//		sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
		if(m_pLBoxState->GetSelect() == 0)
		{
			m_BRequestTeamState = ARENA_REQUEST_TEAM_STATE_OUR;
			
		}else
		{
			m_BRequestTeamState = ARENA_REQUEST_TEAM_STATE_JOINING;
		}
//		sMsg.RequestTeamState = m_BRequestTeamState;
//		sMsg.StartTeamNum = -1;
//		g_pFieldWinSocket->SendMsg(T_FC_ARENA_REQUEST_TEAM,(char*)&sMsg,sizeof(sMsg));
		SendArenaRequestTeam(-1);
		// end 2007-11-22 by bhsohn 아레나 통합서버
	}else
	{// 다른 세력이면.
		EnemyInfo();
	}
}

int CINFCityArena::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
	CheckMouseReverse(&pt);
	BOOL bClick = FALSE;	
	bClick = m_pScroll->IsMouseWhellPos(pt);
	if(bClick)		
	{
		int nScrollStep = m_pScroll->OnMouseWheel(wParam, lParam);

		// 팀 목록 리스트를 새로 받아야 할 경우를 체크한다.
		int nListSize = m_vecTeamList.size();
		if(nListSize < m_nTeamTotalCount)
		{
			if(nListSize <= nScrollStep + ARENA_LIST_COUNT)
			{// 팀 목록중 가장 아랫 부분이다. 방목록을 새로 요청하도록한다.
				// 2007-11-22 by bhsohn 아레나 통합서버
//				MSG_FC_ARENA_REQUEST_TEAM sMsg;
//				sMsg.ArenaMode = m_BArenaMode;
//				sMsg.RequestTeamState = m_BRequestTeamState;
//				sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
//				sMsg.StartTeamNum = m_vecTeamList[nListSize-1].TeamNum;
//				g_pFieldWinSocket->SendMsg(T_FC_ARENA_REQUEST_TEAM,(char*)&sMsg,sizeof(sMsg));				
				SendArenaRequestTeam(m_vecTeamList[nListSize-1].TeamNum);
				// end 2007-11-22 by bhsohn 아레나 통합서버
			}
		}
		return INF_MSGPROC_BREAK;
	}
	return INF_MSGPROC_NORMAL;	
}
int CINFCityArena::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
	CheckMouseReverse(&pt);
	int nCnt = 0;
	BOOL bClick = FALSE;	
	bClick = m_pScroll->IsMouseBallPos(pt);
	if(bClick)		
	{
		m_pScroll->SetMouseMoveMode(TRUE);
		return INF_MSGPROC_BREAK;
		
	}	
	return INF_MSGPROC_NORMAL;
}
int CINFCityArena::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	int nCnt = 0;
	BOOL bClick = FALSE;	
	bClick = m_pScroll->GetMouseMoveMode();
	if(bClick)		
	{
		m_pScroll->SetMouseMoveMode(FALSE);			
	}		
	return INF_MSGPROC_NORMAL;
}

int CINFCityArena::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
	CheckMouseReverse(&pt);

	int nCnt = 0;
	if(m_pScroll->GetMouseMoveMode())
	{
		if(FALSE == m_pScroll->IsMouseScrollPos(pt))
		{// 스크롤 잡고 있는걸 해제한다.
			m_pScroll->SetMouseMoveMode(FALSE);
			return INF_MSGPROC_NORMAL;			
		}
		m_pScroll->SetScrollPos(pt);
		int nScrollStep = m_pScroll->GetScrollStep();
		
		// 팀 목록 리스트를 새로 받아야 할 경우를 체크한다.
		int nListSize = m_vecTeamList.size();
		if(nListSize < m_nTeamTotalCount)
		{
			if(nListSize <= nScrollStep + ARENA_LIST_COUNT)
			{// 팀 목록중 가장 아랫 부분이다. 방목록을 새로 요청하도록한다.
				// 2007-11-22 by bhsohn 아레나 통합서버
//				MSG_FC_ARENA_REQUEST_TEAM sMsg;
//				sMsg.ArenaMode = m_BArenaMode;					
//				sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
//				sMsg.StartTeamNum = m_vecTeamList[nListSize-1].TeamNum;
//				g_pFieldWinSocket->SendMsg(T_FC_ARENA_REQUEST_TEAM,(char*)&sMsg,sizeof(sMsg));
				SendArenaRequestTeam(m_vecTeamList[nListSize-1].TeamNum);
			}
		}
		return INF_MSGPROC_BREAK;			
	}
	return INF_MSGPROC_NORMAL;
}
void CINFCityArena::Tick()
{

	if(m_pArenaCreate)
		m_pArenaCreate->Tick();
}
int CINFCityArena::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_pArenaCreate->m_bShow)
	{
		if(INF_MSGPROC_BREAK == m_pArenaCreate->WndProc(uMsg,wParam,lParam))
			return INF_MSGPROC_BREAK;
		return INF_MSGPROC_NORMAL;
	}
	switch(uMsg)
	{
		case WM_MOUSEWHEEL:
			{
				return OnMouseWheel(wParam,lParam);
			}
			break;

		case WM_MOUSEMOVE:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				m_pLBoxInf->MouseMove(pt);
				m_pLBoxState->MouseMove(pt);

				if(pt.x > ARENA_LIST_REFRESH_BUTTON_X &&
					pt.x < ARENA_LIST_REFRESH_BUTTON_X + ARENA_LIST_REFRESH_BUTTON_W &&
					pt.y > ARENA_LIST_REFRESH_BUTTON_Y &&
					pt.y < ARENA_LIST_REFRESH_BUTTON_Y + ARENA_LIST_REFRESH_BUTTON_H)
				{
					m_nRefresh = BUTTON_STATE_UP;
				}
				else
				{
					m_nRefresh = BUTTON_STATE_NORMAL;
				}
				if(pt.x > ARENA_TEAM_SEARCH_BUTTON_X &&
					pt.x < ARENA_TEAM_SEARCH_BUTTON_X + ARENA_TEAM_SEARCH_BUTTON_W &&
					pt.y > ARENA_TEAM_SEARCH_BUTTON_Y &&
					pt.y < ARENA_TEAM_SEARCH_BUTTON_Y + ARENA_TEAM_SEARCH_BUTTON_H)
				{
					m_nSearch = BUTTON_STATE_UP;
				}
				else
				{
					m_nSearch = BUTTON_STATE_NORMAL;
				}
				return OnMouseMove(wParam,lParam);

			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				if(1 == m_pLBoxInf->LButtonDown(pt))
				{
					if(IsInfluenceEqual())
					{// 같은 세력이면.
						m_pLBoxState->SetMainButtonEnisable();
					}
					else
					{
						m_pLBoxState->SetMainButtonDisable();
						m_pLBoxState->SetSelectItem(1);
						m_pLBoxState->m_nSelect = 0;
					}
				}
				m_pLBoxState->LButtonDown(pt);
					
				if(pt.x > ARENA_LIST_REFRESH_BUTTON_X &&
					pt.x < ARENA_LIST_REFRESH_BUTTON_X + ARENA_LIST_REFRESH_BUTTON_W &&
					pt.y > ARENA_LIST_REFRESH_BUTTON_Y &&
					pt.y < ARENA_LIST_REFRESH_BUTTON_Y + ARENA_LIST_REFRESH_BUTTON_H)
				{
					m_nRefresh = BUTTON_STATE_DOWN;
				}
				else
				{
					m_nRefresh = BUTTON_STATE_NORMAL;
				}
				if(pt.x > ARENA_TEAM_SEARCH_BUTTON_X &&
					pt.x < ARENA_TEAM_SEARCH_BUTTON_X + ARENA_TEAM_SEARCH_BUTTON_W &&
					pt.y > ARENA_TEAM_SEARCH_BUTTON_Y &&
					pt.y < ARENA_TEAM_SEARCH_BUTTON_Y + ARENA_TEAM_SEARCH_BUTTON_H)
				{
					m_nSearch = BUTTON_STATE_DOWN;
				}
				else
				{
					m_nSearch = BUTTON_STATE_NORMAL;
				}
				// 방 선택.
				if(pt.x > ARENA_LIST_SELECT_X &&
					pt.x < ARENA_LIST_SELECT_X + ARENA_LIST_W &&
					pt.y > ARENA_LIST_SELECT_Y &&
					pt.y < ARENA_LIST_SELECT_Y + ARENA_LIST_H)
				{
					int temp = ARENA_LIST_SELECT_Y;
					temp = (pt.y - temp);
					temp = (int)temp / ARENA_MATCH_LIST_GAP;
					if(temp >= 0 &&
						temp < ARENA_LIST_COUNT)
					{
						m_nSelectIndex = temp;
						
					}
				}
				return OnLButtonDown(wParam,lParam);
			}
			break;
		case WM_LBUTTONUP:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				if(pt.x > ARENA_TEAM_SEARCH_BUTTON_X &&
					pt.x < ARENA_TEAM_SEARCH_BUTTON_X + ARENA_TEAM_SEARCH_BUTTON_W &&
					pt.y > ARENA_TEAM_SEARCH_BUTTON_Y &&
					pt.y < ARENA_TEAM_SEARCH_BUTTON_Y + ARENA_TEAM_SEARCH_BUTTON_H)
				{
					RequestTeamList();					
				}
				else
				{
					m_nSearch = BUTTON_STATE_NORMAL;
				}

				if(pt.x > ARENA_LIST_REFRESH_BUTTON_X &&
					pt.x < ARENA_LIST_REFRESH_BUTTON_X + ARENA_LIST_REFRESH_BUTTON_W &&
					pt.y > ARENA_LIST_REFRESH_BUTTON_Y &&
					pt.y < ARENA_LIST_REFRESH_BUTTON_Y + ARENA_LIST_REFRESH_BUTTON_H)
				{
					m_nRefresh = BUTTON_STATE_UP;
//					ReFresh();
				}
				else
				{
					m_nRefresh = BUTTON_STATE_NORMAL;
				}

				return OnLButtonUp(wParam,lParam);

			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				
				// 방 선택.
				if(pt.x > ARENA_LIST_SELECT_X &&
					pt.x < ARENA_LIST_SELECT_X + ARENA_LIST_W &&
					pt.y > ARENA_LIST_SELECT_Y &&
					pt.y < ARENA_LIST_SELECT_Y + ARENA_LIST_H)
				{
					App();
//					int temp = ARENA_LIST_SELECT_Y;
//					temp = (pt.y - temp);
//					temp = (int)temp / ARENA_MATCH_LIST_GAP;
//					if(temp >= 0 &&
//						temp < ARENA_LIST_COUNT)
//					{
//						m_nSelectIndex = temp;
//					}
				}
				return OnLButtonDown(wParam,lParam);

			}
			break;

	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 아레나 팀 요청
/// \author		// 2007-11-22 by bhsohn 아레나 통합서버
/// \date		2008-01-03 ~ 2008-01-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////	
void CINFCityArena::SendArenaRequestTeam(int nStartTeamNum)
{	
	// 2008-04-24 by bhsohn 아레나 상점에서 팀 정보를 요청하고 마우스로 스크롤을 조작하면 클라이언트 종료되는 현상
	if(g_pD3dApp->IsLockMode() == FALSE)
	{
		return;
	}
	// end 2008-04-24 by bhsohn 아레나 상점에서 팀 정보를 요청하고 마우스로 스크롤을 조작하면 클라이언트 종료되는 현상
	CHARACTER*	pArenaCharacterInfo = g_pD3dApp->GetArenaCharacterInfo();
	MSG_FC_ARENA_REQUEST_TEAM sMsg;
	memset(&sMsg, 0x00, sizeof(MSG_FC_ARENA_REQUEST_TEAM));

	sMsg.ArenaMode = m_BArenaMode;					
	//sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
	sMsg.ClientIndex = pArenaCharacterInfo->ClientIndex;
	sMsg.RequestTeamState = m_BRequestTeamState;
	sMsg.StartTeamNum = nStartTeamNum;	
	g_pFieldWinSocket->SendMsg(T_FC_ARENA_REQUEST_TEAM,(char*)&sMsg,sizeof(sMsg));
	
	// 2007-11-22 by bhsohn 아레나 통합서버	
	// Lock
	{
		vector<MessageType_t> vecUnLockMsg;
		vecUnLockMsg.clear();
		vecUnLockMsg.push_back(T_FC_ARENA_REQUEST_TEAM);		
		vecUnLockMsg.push_back(T_FC_ARENA_REQUEST_TEAM_OK);		
		// 하나만 매칭 되어도 락이 풀린다. 
		g_pD3dApp->EnterMultiLock(TRUE, T_FC_ARENA_REQUEST_TEAM, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
	}
	// end 2007-11-22 by bhsohn 아레나 통합서버
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 아레나 참가
/// \author		// 2007-11-22 by bhsohn 아레나 통합서버
/// \date		2008-01-03 ~ 2008-01-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////	
void CINFCityArena::SendArenaEnterRoom(char* TeamPW)
{
	// 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	if(TRUE == g_pD3dApp->IsDoingInfluenceWar())
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070427_0104,COLOR_ERROR); //"세력전이 진행 중이므로 참가할 수 없습니다."
		return;
	}
	// end 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	// 2008-03-10 by bhsohn 아레나 관련 버그 수정
	if(TRUE == g_pInterface->IsArenaGameState(ARENA_GAME_STATE_TEAMINFO))
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0207,COLOR_ERROR);//"이미 아레나 대기방에 참여중입니다."
		return;	
	}
	// end 2008-03-10 by bhsohn 아레나 관련 버그 수정

	// 2008-02-25 by bhsohn 아레나 유저 정보 서버도 표시하게 변경
	//SARENA_TEAM_INFO * TeamInfo = GetSelectListTeam();
	STRUCT_TEAM_INFO* TeamInfo = GetSelectListTeam();

	if(TeamInfo == NULL)
	{
		return ;
	}
	CHARACTER*	pArenaCharacterInfo = g_pD3dApp->GetArenaCharacterInfo();
	MSG_FC_ARENA_ENTER_TEAM sMsg;
	memset(&sMsg, 0x00, sizeof(MSG_FC_ARENA_ENTER_TEAM));

	sMsg.ArenaMode = TeamInfo->ArenaMode;
	sMsg.ClientIndex = pArenaCharacterInfo->ClientIndex;
	sMsg.TeamNum = TeamInfo->TeamNum;

	if(TeamPW)
	{
		STRNCPY_MEMSET(sMsg.TeamPW, TeamPW, SIZE_MAX_TEAM_PW);
	}
	
	g_pFieldWinSocket->SendMsg(T_FC_ARENA_ENTER_TEAM,(char*)&sMsg,sizeof(sMsg));
}