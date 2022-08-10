// INFArenaTeamInfo.cpp: implementation of the CINFArenaTeamInfo class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "INFArenaTeamInfo.h"
#include "AtumApplication.h"
#include "ShuttleChild.h"
#include "GameDataLast.h"
#include "INFImage.h"
#include "D3dHanFont.h"
#include "INFGameArena.h"
#include "Chat.h"


//--------------------------------------------------------------------------//
#define ARENA_TEAMINFO_COUNT					7
#define ARENA_TEAMINFO_GAP						20



//#define ARENA_TEAMINFO_BUTTON_X					(g_pD3dApp->GetBackBufferDesc().Width - 326 + m_nInfoButtonX)
//#define ARENA_TEAMINFO_BUTTON_Y					(22 + m_nInfoButtonY)
#define ARENA_TEAMINFO_BUTTON_X					(m_nInfoButtonX)
#define ARENA_TEAMINFO_BUTTON_Y					(m_nInfoButtonY)
#define ARENA_TEAMINFO_BUTTON_W					177
#define ARENA_TEAMINFO_BUTTON_H					25

#define ARENA_TEAMINFO_BUTTON_LIMIT_X			(g_pD3dApp->GetBackBufferDesc().Width - (ARENA_TEAMINFO_BUTTON_W))
#define ARENA_TEAMINFO_BUTTON_LIMIT_Y			(g_pD3dApp->GetBackBufferDesc().Height - (ARENA_TEAMINFO_BUTTON_H + 40))

#define ARENA_TEAMINFO_INFO_START_X				ARENA_TEAMINFO_BUTTON_X
#define ARENA_TEAMINFO_INFO_START_Y				ARENA_TEAMINFO_BUTTON_Y + 25

#define ARENA_TEAMINFO_WINDOWSIZE_X				ARENA_TEAMINFO_BUTTON_X + 154
#define ARENA_TEAMINFO_WINDOWSIZE_Y				ARENA_TEAMINFO_BUTTON_Y + 4
#define ARENA_TEAMINFO_WINDOWSIZE_W				18
#define ARENA_TEAMINFO_WINDOWSIZE_H				17

#define ARENA_TEAMINFO_STATE_FONT_X				ARENA_TEAMINFO_INFO_START_X + 17
#define ARENA_TEAMINFO_STATE_FONT_Y				ARENA_TEAMINFO_INFO_START_Y + 20

#define ARENA_TEAMINFO_USER_FONT_X				ARENA_TEAMINFO_INFO_START_X + 22
#define ARENA_TEAMINFO_USER_FONT_Y				ARENA_TEAMINFO_INFO_START_Y + 50

#define ARENA_TEAMINFO_USER_READY_X				ARENA_TEAMINFO_INFO_START_X + 13
#define ARENA_TEAMINFO_USER_READY_Y				ARENA_TEAMINFO_INFO_START_Y + 50

#define ARENA_TEAMINFO_READY_X					ARENA_TEAMINFO_INFO_START_X + 23
#define ARENA_TEAMINFO_READY_Y					ARENA_TEAMINFO_INFO_START_Y + 212
#define ARENA_TEAMINFO_APPCANCEL_X				ARENA_TEAMINFO_INFO_START_X + 90
#define ARENA_TEAMINFO_APPCANCEL_Y				ARENA_TEAMINFO_READY_Y
#define ARENA_TEAMINFO_APPCANCEL_W				64
#define ARENA_TEAMINFO_APPCANCEL_H				19


//--------------------------------------------------------------------------//
//							Scroll
#define	ARENA_TEAMINFO_SCROLL_WHELL_AREA_X		(ARENA_TEAMINFO_INFO_START_X + 13)
#define	ARENA_TEAMINFO_SCROLL_WHELL_AREA_Y		(ARENA_TEAMINFO_INFO_START_Y + 50)
#define	ARENA_TEAMINFO_SCROLL_WHELL_AREA_W		(ARENA_TEAMINFO_SCROLL_WHELL_AREA_X + 156)
#define	ARENA_TEAMINFO_SCROLL_WHELL_AREA_H		(ARENA_TEAMINFO_SCROLL_WHELL_AREA_Y + 140)

#define	ARENA_TEAMINFO_SCROLL_DRAG_AREA_X		(ARENA_TEAMINFO_INFO_START_X + 157)
#define	ARENA_TEAMINFO_SCROLL_DRAG_AREA_Y		(ARENA_TEAMINFO_INFO_START_Y + 50)
#define	ARENA_TEAMINFO_SCROLL_DRAG_AREA_W		(ARENA_TEAMINFO_SCROLL_DRAG_AREA_X + 20)
#define	ARENA_TEAMINFO_SCROLL_DRAG_AREA_H		(ARENA_TEAMINFO_SCROLL_DRAG_AREA_Y + 101)
							  
// 2007-05-15 by bhsohn 스크롤 관련 버그 수정
#define	ARENA_TEAMINFO_SCROLL_DRAG_BALL_CAP		55
//--------------------------------------------------------------------------//



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CINFArenaTeamInfo::CINFArenaTeamInfo(CAtumNode* pParent)
{
	m_pParent = pParent;
	int i;
	for(i = 0 ; i < 3 ; i++)
	{
		m_pImgTeamInfoB[i][0] = NULL;
		m_pImgTeamInfoB[i][1] = NULL;
	}
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgReadyB[i] = NULL;
		m_pImgUReadyB[i] = NULL;
		m_pImgAppCancelB[i] = NULL;
		m_pImgWinSizeB[0][i] = NULL;
		m_pImgWinSizeB[1][i] = NULL;
	}
	m_pFontID = NULL;
	m_pFontState = NULL;

	m_pScroll = NULL;
	m_pImgBG = NULL;
	m_pImgReady = NULL;

	m_nReadyB = BUTTON_STATE_NORMAL;
	m_nUReadyB = BUTTON_STATE_NORMAL;
	m_nAppCancel = BUTTON_STATE_NORMAL;

	m_bTeamInfoShow = TRUE;

	m_nLimitPerson = 0;
	m_nPerson = 0;

	m_nInfoButtonX = g_pD3dApp->GetBackBufferDesc().Width - 326;
	m_nInfoButtonY = 22;
	
	m_bInfoButton = FALSE;

	// 2007-11-22 by bhsohn 아레나 통합서버
	m_fUReadyButtonTime = ARENA_BUTTON_UREADY_GAP;

}
CINFArenaTeamInfo::CINFArenaTeamInfo()
{
	int i;
	for(i = 0 ; i < 3 ; i++)
	{
		m_pImgTeamInfoB[i][0] = NULL;
		m_pImgTeamInfoB[i][1] = NULL;
	}
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgReadyB[i] = NULL;
		m_pImgUReadyB[i] = NULL;
		m_pImgAppCancelB[i] = NULL;
		m_pImgWinSizeB[0][i] = NULL;
		m_pImgWinSizeB[1][i] = NULL;

	}
	m_pFontID = NULL;
	m_pFontState = NULL;

	m_pScroll = NULL;
	m_pImgBG = NULL;
	m_pImgReady = NULL;

	m_nReadyB = BUTTON_STATE_NORMAL;
	m_nUReadyB = BUTTON_STATE_NORMAL;
	m_nAppCancel = BUTTON_STATE_NORMAL;

	m_bTeamInfoShow = FALSE;
}

CINFArenaTeamInfo::~CINFArenaTeamInfo()
{

}
VOID CINFArenaTeamInfo::AddTeamUserInfo(MSG_FC_ARENA_TEAM_MEMBER_LIST *pMsg)
{
	SARENA_TEAM_CHARACTERINFO *pTeamInfo = (SARENA_TEAM_CHARACTERINFO *)((char *)pMsg + sizeof(MSG_FC_ARENA_TEAM_MEMBER_LIST));
	int i = 0;
	m_nPerson = 0;
	m_vecTeamUserInfo.clear();
	for(i = 0 ; i < pMsg->ArenaTeamCharacterNameListCount ; i++)
	{
		// 2007-11-22 by bhsohn 아레나 통합서버
		CHARACTER*	pArenaCharacterInfo = g_pD3dApp->GetArenaCharacterInfo();
		//if(pTeamInfo->ClientIndex == g_pShuttleChild->m_myShuttleInfo.ClientIndex)
		if(pTeamInfo->ClientIndex == pArenaCharacterInfo->ClientIndex)		
		{
			if(pTeamInfo->ArenaState == ARENA_STATE_READY_FINISH)
			{
				m_bReady = TRUE;
			}
			if(pTeamInfo->ArenaState == ARENA_STATE_READY)
			{
				m_fUReadyButtonTime = ARENA_BUTTON_UREADY_GAP;
				m_bReady = FALSE;
			}
		}
		// 2007-11-22 by bhsohn 아레나 통합서버
		// 팀인포		
		STRUCT_TEAM_CHARACTERINFO sTeamInfo;
		memset(&sTeamInfo, 0x00, sizeof(STRUCT_TEAM_CHARACTERINFO));
		{
			sTeamInfo.ArenaState = pTeamInfo->ArenaState;
			sTeamInfo.ClientIndex = pTeamInfo->ClientIndex;
			strncpy(sTeamInfo.CharacterName, pTeamInfo->CharacterName, SIZE_MAX_CHARACTER_NAME);
		}
		// 이름변경 
		g_pD3dApp->ConevertArenaRenderUserName(ARENA_STATE_ARENA_GAMING, sTeamInfo.CharacterName);
		//m_vecTeamUserInfo.push_back((*pTeamInfo));
		m_vecTeamUserInfo.push_back(sTeamInfo);

		pTeamInfo++;
	}
	m_nPerson = i;
	m_pScroll->SetMaxItem(i);
	
	// 현재 상태를 갱신시켜준다.
	if(pMsg->ArenaTeamState-1 >= ARENA_BUTTON_STATE_USERIN &&		// 0
		pMsg->ArenaTeamState-1 <= ARENA_BUTTON_STATE_ENEMYSEARCH)	// 2
	{
		SetState(pMsg->ArenaTeamState - 1);
	}
}
VOID CINFArenaTeamInfo::SetState(BYTE state)
{
	m_nMainBState = state;
}
HRESULT CINFArenaTeamInfo::InitDeviceObjects()
{
	int i;
	DataHeader	* pDataHeader;
	char buf[30];	
	if(NULL == m_pScroll)
	{
		m_pScroll = new CINFArenaScrollBar;
	}
	wsprintf(buf,"c_scrlb");				
	m_pScroll->InitDeviceObjects(ARENA_TEAMINFO_COUNT, buf);

	for(i = 0 ; i < 3; i++)
	{
		wsprintf( buf, "ainfob%d0", i);
		pDataHeader = FindResource(buf);
		m_pImgTeamInfoB[i][0] = new CINFImage;
		m_pImgTeamInfoB[i][0]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

		wsprintf( buf, "ainfob%d1", i);
		pDataHeader = FindResource(buf);
		m_pImgTeamInfoB[i][1] = new CINFImage;
		m_pImgTeamInfoB[i][1]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	}
	for(i = 0; i < BUTTON_STATE_NUMBER ; i++)
	{
		wsprintf(buf,"startare%d",i);
		pDataHeader = FindResource(buf);
		m_pImgReadyB[i] = new CINFImage;
		m_pImgReadyB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		wsprintf(buf,"ustaare%d",i);
		pDataHeader = FindResource(buf);
		m_pImgUReadyB[i] = new CINFImage;
		m_pImgUReadyB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		
		wsprintf(buf,"appcencel%d",i);
		pDataHeader = FindResource(buf);
		m_pImgAppCancelB[i] = new CINFImage;
		m_pImgAppCancelB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		wsprintf(buf,"ainfo0%d",i);
		pDataHeader = FindResource(buf);
		m_pImgWinSizeB[0][i] = new CINFImage;
		m_pImgWinSizeB[0][i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		wsprintf(buf,"ainfo1%d",i);
		pDataHeader = FindResource(buf);
		m_pImgWinSizeB[1][i] = new CINFImage;
		m_pImgWinSizeB[1][i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	}

	m_pFontID = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontID->InitDeviceObjects(g_pD3dDev);
	m_pFontState = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontState->InitDeviceObjects(g_pD3dDev);
	

	pDataHeader = FindResource("areinfo");
	m_pImgBG = new CINFImage;
	m_pImgBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	pDataHeader = FindResource("areready");
	m_pImgReady = new CINFImage;
	m_pImgReady->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	
	return S_OK;
}
HRESULT CINFArenaTeamInfo::RestoreDeviceObjects()
{
	int i;
	for(i = 0 ; i < 3 ; i++)
	{
		m_pImgTeamInfoB[i][0]->RestoreDeviceObjects();
		m_pImgTeamInfoB[i][1]->RestoreDeviceObjects();
	}
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgReadyB[i]->RestoreDeviceObjects();
		m_pImgUReadyB[i]->RestoreDeviceObjects();
		m_pImgAppCancelB[i]->RestoreDeviceObjects();
		m_pImgWinSizeB[0][i]->RestoreDeviceObjects();
		m_pImgWinSizeB[1][i]->RestoreDeviceObjects();
	}

	m_pFontID->RestoreDeviceObjects();
	m_pFontState->RestoreDeviceObjects();

	m_pImgBG->RestoreDeviceObjects();
	m_pImgReady->RestoreDeviceObjects();
	
	SetMouseRect();

	m_pScroll->RestoreDeviceObjects();	
	return S_OK;

}
VOID CINFArenaTeamInfo::SetMouseRect()
{
	RECT rc;
	// 휠마우스 위치 영역.
	rc.left		= ARENA_TEAMINFO_SCROLL_WHELL_AREA_X;
	rc.top		= ARENA_TEAMINFO_SCROLL_WHELL_AREA_Y;
	rc.bottom	= ARENA_TEAMINFO_SCROLL_WHELL_AREA_H;
	rc.right	= ARENA_TEAMINFO_SCROLL_WHELL_AREA_W;
	m_pScroll->SetMouseWhellRect(rc);

	// 마우스 클릭 후 드레그 가능 영역.
	rc.left		= ARENA_TEAMINFO_SCROLL_DRAG_AREA_X;
	rc.top		= ARENA_TEAMINFO_SCROLL_DRAG_AREA_Y; 
    // 2007-05-15 by bhsohn 스크롤 관련 버그 수정
	rc.bottom	= ARENA_TEAMINFO_SCROLL_DRAG_AREA_H+ARENA_TEAMINFO_SCROLL_DRAG_BALL_CAP;
	rc.right	= ARENA_TEAMINFO_SCROLL_DRAG_AREA_W;
	m_pScroll->SetMouseBallRect(rc);

	// 스크롤 인식 범위.
	m_pScroll->SetPosition(ARENA_TEAMINFO_SCROLL_DRAG_AREA_X, ARENA_TEAMINFO_SCROLL_DRAG_AREA_Y, 
		(ARENA_TEAMINFO_SCROLL_DRAG_AREA_W)-(ARENA_TEAMINFO_SCROLL_DRAG_AREA_X), 
		(ARENA_TEAMINFO_SCROLL_DRAG_AREA_H)-(ARENA_TEAMINFO_SCROLL_DRAG_AREA_Y));
}

void CINFArenaTeamInfo::TestDB()
{
	int nItemLen = 10;
	long lBuffLen = sizeof(MSG_FC_ARENA_TEAM_MEMBER_LIST)+(sizeof(SARENA_TEAM_CHARACTERINFO)*nItemLen);
	MSG_FC_ARENA_TEAM_MEMBER_LIST *pMsg = (MSG_FC_ARENA_TEAM_MEMBER_LIST *)malloc(lBuffLen);
	memset(pMsg, 0x00, lBuffLen);

	SARENA_TEAM_CHARACTERINFO *pTeamInfo = (SARENA_TEAM_CHARACTERINFO *)((char *)pMsg + sizeof(MSG_FC_ARENA_TEAM_MEMBER_LIST));

	pMsg->ArenaTeamCharacterNameListCount = nItemLen;
	pMsg->ArenaTeamState = ARENA_BUTTON_STATE_USERIN;

	for(int nCnt = 0;nCnt < nItemLen;nCnt++)
	{
		pTeamInfo->ArenaState = ARENA_STATE_READY_FINISH;
		pTeamInfo->ClientIndex = 100;
		wsprintf(pTeamInfo->CharacterName, "Team%d", nCnt);
		pTeamInfo++;
	}	
	AddTeamUserInfo(pMsg);
	free(pMsg);

}
HRESULT CINFArenaTeamInfo::DeleteDeviceObjects()
{
	int i;
	for(i = 0 ; i < 3 ; i++)
	{
		m_pImgTeamInfoB[i][0]->DeleteDeviceObjects();
		m_pImgTeamInfoB[i][1]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgTeamInfoB[i][0]);
		SAFE_DELETE(m_pImgTeamInfoB[i][1]);
	}
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgReadyB[i]->DeleteDeviceObjects();
		m_pImgUReadyB[i]->DeleteDeviceObjects();
		m_pImgAppCancelB[i]->DeleteDeviceObjects();
		m_pImgWinSizeB[0][i]->DeleteDeviceObjects();
		m_pImgWinSizeB[1][i]->DeleteDeviceObjects();

		SAFE_DELETE(m_pImgReadyB[i]);
		SAFE_DELETE(m_pImgUReadyB[i]);
		SAFE_DELETE(m_pImgAppCancelB[i]);
		SAFE_DELETE(m_pImgWinSizeB[0][i]);
		SAFE_DELETE(m_pImgWinSizeB[1][i]);
	}
	m_pFontID->DeleteDeviceObjects();
	m_pFontState->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontID);
	SAFE_DELETE(m_pFontState);

	m_pScroll->DeleteDeviceObjects();
	m_pImgBG->DeleteDeviceObjects();
	m_pImgReady->DeleteDeviceObjects();
	SAFE_DELETE(m_pScroll);
	SAFE_DELETE(m_pImgBG);
	SAFE_DELETE(m_pImgReady);
	return S_OK;

}
HRESULT CINFArenaTeamInfo::InvalidateDeviceObjects()
{
	int i;
	for(i = 0 ; i < 3 ; i++)
	{
		m_pImgTeamInfoB[i][0]->InvalidateDeviceObjects();
		m_pImgTeamInfoB[i][1]->InvalidateDeviceObjects();
	}
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgReadyB[i]->InvalidateDeviceObjects();
		m_pImgUReadyB[i]->InvalidateDeviceObjects();
		m_pImgAppCancelB[i]->InvalidateDeviceObjects();
		m_pImgWinSizeB[0][i]->InvalidateDeviceObjects();
		m_pImgWinSizeB[1][i]->InvalidateDeviceObjects();
		

	}
	m_pFontID->InvalidateDeviceObjects();
	m_pFontState->InvalidateDeviceObjects();

	m_pScroll->InvalidateDeviceObjects();
	m_pImgBG->InvalidateDeviceObjects();
	m_pImgReady->InvalidateDeviceObjects();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFArenaTeamInfo::MoveInfoButton(POINT pt)
/// \brief		버튼을 이동할 경우.
/// \author		dgwoo
/// \date		2007-06-01 ~ 2007-06-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFArenaTeamInfo::MoveInfoButton(POINT pt)
{
	m_nInfoButtonX += pt.x - m_ptOld.x;
	m_nInfoButtonY += pt.y - m_ptOld.y;
	if(m_nInfoButtonX < 0)
		m_nInfoButtonX = 0;
	if(m_nInfoButtonX > ARENA_TEAMINFO_BUTTON_LIMIT_X)
		m_nInfoButtonX = ARENA_TEAMINFO_BUTTON_LIMIT_X;
	if(m_nInfoButtonY < 0)
		m_nInfoButtonY = 0;
	if(m_nInfoButtonY > ARENA_TEAMINFO_BUTTON_LIMIT_Y)
		m_nInfoButtonY = ARENA_TEAMINFO_BUTTON_LIMIT_Y;
	m_ptOld = pt;
	SetMouseRect();
	//DbgOut("MoveInfoButton X = %d, Y = %d\n",m_nInfoButtonX, m_nInfoButtonY);
}
void CINFArenaTeamInfo::Render()
{
	int i;
	m_pImgTeamInfoB[m_nMainBState][m_nMainBUnder]->Move(ARENA_TEAMINFO_BUTTON_X,ARENA_TEAMINFO_BUTTON_Y);
	m_pImgTeamInfoB[m_nMainBState][m_nMainBUnder]->Render();

	m_pImgWinSizeB[m_bTeamInfoShow][m_nWinSizeB]->Move(ARENA_TEAMINFO_WINDOWSIZE_X,ARENA_TEAMINFO_WINDOWSIZE_Y);
	m_pImgWinSizeB[m_bTeamInfoShow][m_nWinSizeB]->Render();

	if(m_bTeamInfoShow)
	{// 팀정보를 보여준다.(현재 팀state, 유저명, ready상태등)
		// 배경.
		m_pImgBG->Move(ARENA_TEAMINFO_INFO_START_X,ARENA_TEAMINFO_INFO_START_Y);
		m_pImgBG->Render();
		
		// team state
		char buf[64];
		switch(m_nMainBState)
		{
			case ARENA_BUTTON_STATE_USERIN:
				{
					wsprintf(buf,STRMSG_C_070502_0100,m_nPerson,m_nLimitPerson);
				}
				break;
			case ARENA_BUTTON_STATE_READY:
				{
					wsprintf(buf,STRMSG_C_070502_0101,m_nPerson,m_nLimitPerson);
				}
				break;
			case ARENA_BUTTON_STATE_ENEMYSEARCH:
				{
					wsprintf(buf,STRMSG_C_070502_0102,m_nPerson,m_nLimitPerson);
				}
				break;
		}
		// 2007-05-28 by dgwoo 세력전이 진행중일 경우는 모든 진행을 멈춘다.(모선전, 거점전)
		if(g_pD3dApp->IsWarMotherShip())
		{
			memset(buf,0x00,64);
			wsprintf(buf,STRMSG_C_070502_0103,m_nPerson,m_nLimitPerson);
		}
		m_pFontState->DrawText(ARENA_TEAMINFO_STATE_FONT_X ,
			ARENA_TEAMINFO_STATE_FONT_Y,
			GUI_FONT_COLOR_W,
			buf);

		// User Name and State
		// 2008-02-25 by bhsohn 아레나 유저 정보 서버도 표시하게 변경
		//vector<SARENA_TEAM_CHARACTERINFO>::iterator it = m_vecTeamUserInfo.begin();
		vector<STRUCT_TEAM_CHARACTERINFO>::iterator it = m_vecTeamUserInfo.begin();
		
		int nCnt = 0;
		for(nCnt = 0;nCnt < m_pScroll->GetScrollStep(); nCnt++)
		{
			if(it == m_vecTeamUserInfo.end())
			{
				break;
			}
			// 스크롤 스텝
			it++;
		}
		for(i = 0; i < ARENA_TEAMINFO_COUNT; i++)
		{
			if(it == m_vecTeamUserInfo.end())
			{
				break;
			}
			wsprintf(buf,"%s",it->CharacterName);
			m_pFontID->DrawText(ARENA_TEAMINFO_USER_FONT_X,
				ARENA_TEAMINFO_USER_FONT_Y + (i * ARENA_TEAMINFO_GAP),
				GUI_FONT_COLOR_W,
				buf);

			if(it->ArenaState == ARENA_STATE_READY_FINISH)
			{// 준비 버튼을 눌렀을경우.
				m_pImgReady->Move(ARENA_TEAMINFO_USER_READY_X,
					ARENA_TEAMINFO_USER_READY_Y + (i * ARENA_TEAMINFO_GAP));
				m_pImgReady->Render();
			}
			it++;
		}
		// Button
		if(m_bReady)
		{// 준비 해제 버튼을 보여줌.
			m_pImgUReadyB[m_nReadyB]->Move(ARENA_TEAMINFO_READY_X,ARENA_TEAMINFO_READY_Y);
			m_pImgUReadyB[m_nReadyB]->Render();
		}
		else
		{//	준비 버튼을 보여줌.
			m_pImgReadyB[m_nUReadyB]->Move(ARENA_TEAMINFO_READY_X,ARENA_TEAMINFO_READY_Y);
			m_pImgReadyB[m_nUReadyB]->Render();
		}
		m_pImgAppCancelB[m_nAppCancel]->Move(ARENA_TEAMINFO_APPCANCEL_X,ARENA_TEAMINFO_APPCANCEL_Y);
		m_pImgAppCancelB[m_nAppCancel]->Render();
		
		// Scroll
		m_pScroll->Render();
	}
}
void CINFArenaTeamInfo::Tick()
{
	FLOAT fElapsedTime = g_pD3dApp->GetCheckElapsedTime();
	m_fArenaButtonGap += fElapsedTime;
	m_fUReadyButtonTime -= fElapsedTime;
	if(m_bReady == FALSE 
		&& m_fUReadyButtonTime < 0)
	{// 준비 해제 상태로 오래있을경우 자동 신청취소된다.
		AppCancel(FALSE);

		// 2007-11-22 by bhsohn 아레나 통합서버
		m_fUReadyButtonTime = ARENA_BUTTON_UREADY_GAP;
	}
}
int	CINFArenaTeamInfo::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
	CheckMouseReverse(&pt);
	BOOL bClick = FALSE;	
	bClick = m_pScroll->IsMouseWhellPos(pt);
	if(bClick)		
	{
		m_pScroll->OnMouseWheel(wParam, lParam);
		return INF_MSGPROC_BREAK;
	}		
	return INF_MSGPROC_NORMAL;	

}
int	CINFArenaTeamInfo::OnLButtonDown(WPARAM wParam, LPARAM lParam)
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
int	CINFArenaTeamInfo::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	BOOL bClick = FALSE;	
	bClick = m_pScroll->GetMouseMoveMode();
	if(bClick)		
	{
		m_pScroll->SetMouseMoveMode(FALSE);			
	}		
	return INF_MSGPROC_NORMAL;

}
int	CINFArenaTeamInfo::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
	CheckMouseReverse(&pt);

	int nCnt = 0;
	if(m_pScroll->GetMouseMoveMode())
	{
		if(FALSE == m_pScroll->IsMouseScrollPos(pt))
		{
			m_pScroll->SetMouseMoveMode(FALSE);
			return INF_MSGPROC_NORMAL;			
		}
		m_pScroll->SetScrollPos(pt);
		return INF_MSGPROC_BREAK;			
	}
	return INF_MSGPROC_NORMAL;

}
int CINFArenaTeamInfo::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_MOUSEWHEEL:
			{
				if(m_bTeamInfoShow)
				return OnMouseWheel(wParam,lParam);
			}
			break;
		case WM_MOUSEMOVE:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				
				if( m_bInfoButton)
//					pt.x > ARENA_TEAMINFO_BUTTON_X &&
//					pt.x < ARENA_TEAMINFO_BUTTON_X + ARENA_TEAMINFO_BUTTON_W &&
//					pt.y > ARENA_TEAMINFO_BUTTON_Y &&
//					pt.y < ARENA_TEAMINFO_BUTTON_Y + ARENA_TEAMINFO_BUTTON_H)
				{
					MoveInfoButton(pt);
					return INF_MSGPROC_BREAK;
				}
// 2007-06-01 by dgwoo 버튼이 아니므로 버튼 이미지가 필요없다.
//				if(pt.x > ARENA_TEAMINFO_BUTTON_X &&
//					pt.x < ARENA_TEAMINFO_BUTTON_X + ARENA_TEAMINFO_BUTTON_W &&
//					pt.y > ARENA_TEAMINFO_BUTTON_Y &&
//					pt.y < ARENA_TEAMINFO_BUTTON_Y + ARENA_TEAMINFO_BUTTON_H)
//				{
//					m_nMainBUnder = 1;
//				}
//				else
//				{
//					m_nMainBUnder = 0;
//				}
		
				if(pt.x > ARENA_TEAMINFO_WINDOWSIZE_X &&
					pt.x < ARENA_TEAMINFO_WINDOWSIZE_X + ARENA_TEAMINFO_WINDOWSIZE_W &&
					pt.y > ARENA_TEAMINFO_WINDOWSIZE_Y &&
					pt.y < ARENA_TEAMINFO_WINDOWSIZE_Y + ARENA_TEAMINFO_WINDOWSIZE_H)
				{
					m_nWinSizeB = BUTTON_STATE_UP;
				}
				else
				{
					m_nWinSizeB = BUTTON_STATE_NORMAL;
				}

				if(pt.x > ARENA_TEAMINFO_READY_X &&
					pt.x < ARENA_TEAMINFO_READY_X + ARENA_TEAMINFO_APPCANCEL_W &&
					pt.y > ARENA_TEAMINFO_READY_Y &&
					pt.y < ARENA_TEAMINFO_READY_Y + ARENA_TEAMINFO_APPCANCEL_H)
				{
					if(m_bReady)
					{// 
						m_nReadyB = BUTTON_STATE_UP;

					}else
					{// 
						m_nUReadyB = BUTTON_STATE_UP;

					}
				}
				else
				{
					m_nReadyB = BUTTON_STATE_NORMAL;
					m_nUReadyB = BUTTON_STATE_NORMAL;
				}
				// AppCancel 신청 취소 버튼.
				if(pt.x > ARENA_TEAMINFO_APPCANCEL_X &&
					pt.x < ARENA_TEAMINFO_APPCANCEL_X + ARENA_TEAMINFO_APPCANCEL_W &&
					pt.y > ARENA_TEAMINFO_APPCANCEL_Y &&
					pt.y < ARENA_TEAMINFO_APPCANCEL_Y + ARENA_TEAMINFO_APPCANCEL_H)
				{
					m_nAppCancel = BUTTON_STATE_UP;
				}
				else
				{
					m_nAppCancel = BUTTON_STATE_NORMAL;
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
				// Main Button
				if(pt.x > ARENA_TEAMINFO_BUTTON_X &&
					pt.x < ARENA_TEAMINFO_BUTTON_X + ARENA_TEAMINFO_BUTTON_W &&
					pt.y > ARENA_TEAMINFO_BUTTON_Y &&
					pt.y < ARENA_TEAMINFO_BUTTON_Y + ARENA_TEAMINFO_BUTTON_H)
				{
					//m_bTeamInfoShow = !m_bTeamInfoShow;
					m_bInfoButton = TRUE;
					m_ptOld = pt;
					return INF_MSGPROC_BREAK;
				}
				if(pt.x > ARENA_TEAMINFO_WINDOWSIZE_X &&
					pt.x < ARENA_TEAMINFO_WINDOWSIZE_X + ARENA_TEAMINFO_WINDOWSIZE_W &&
					pt.y > ARENA_TEAMINFO_WINDOWSIZE_Y &&
					pt.y < ARENA_TEAMINFO_WINDOWSIZE_Y + ARENA_TEAMINFO_WINDOWSIZE_H)
				{
					m_nWinSizeB = BUTTON_STATE_DOWN;
					return INF_MSGPROC_BREAK;
				}
				
				// Ready Button
				if(pt.x > ARENA_TEAMINFO_READY_X &&
					pt.x < ARENA_TEAMINFO_READY_X + ARENA_TEAMINFO_APPCANCEL_W &&
					pt.y > ARENA_TEAMINFO_READY_Y &&
					pt.y < ARENA_TEAMINFO_READY_Y + ARENA_TEAMINFO_APPCANCEL_H)
				{
					if(m_bReady)
					{// 
						m_nReadyB = BUTTON_STATE_DOWN;
					}else
					{// 
						m_nUReadyB = BUTTON_STATE_DOWN;
					}
					return INF_MSGPROC_BREAK;
				}
				// AppCancel 신청 취소 버튼.
				if(pt.x > ARENA_TEAMINFO_APPCANCEL_X &&
					pt.x < ARENA_TEAMINFO_APPCANCEL_X + ARENA_TEAMINFO_APPCANCEL_W &&
					pt.y > ARENA_TEAMINFO_APPCANCEL_Y &&
					pt.y < ARENA_TEAMINFO_APPCANCEL_Y + ARENA_TEAMINFO_APPCANCEL_H)
				{
					m_nAppCancel = BUTTON_STATE_DOWN;
					return INF_MSGPROC_BREAK;
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
				m_bInfoButton = FALSE;
				if(pt.x > ARENA_TEAMINFO_WINDOWSIZE_X &&
					pt.x < ARENA_TEAMINFO_WINDOWSIZE_X + ARENA_TEAMINFO_WINDOWSIZE_W &&
					pt.y > ARENA_TEAMINFO_WINDOWSIZE_Y &&
					pt.y < ARENA_TEAMINFO_WINDOWSIZE_Y + ARENA_TEAMINFO_WINDOWSIZE_H)
				{
					m_bTeamInfoShow = !m_bTeamInfoShow;
					return INF_MSGPROC_BREAK;
				}

				if(pt.x > ARENA_TEAMINFO_READY_X &&
					pt.x < ARENA_TEAMINFO_READY_X + ARENA_TEAMINFO_APPCANCEL_W &&
					pt.y > ARENA_TEAMINFO_READY_Y &&
					pt.y < ARENA_TEAMINFO_READY_Y + ARENA_TEAMINFO_APPCANCEL_H)
				{
					ClickReadyButton();
					return INF_MSGPROC_BREAK;
				}
				// AppCancel 신청 취소 버튼.
				if(pt.x > ARENA_TEAMINFO_APPCANCEL_X &&
					pt.x < ARENA_TEAMINFO_APPCANCEL_X + ARENA_TEAMINFO_APPCANCEL_W &&
					pt.y > ARENA_TEAMINFO_APPCANCEL_Y &&
					pt.y < ARENA_TEAMINFO_APPCANCEL_Y + ARENA_TEAMINFO_APPCANCEL_H)
				{
					AppCancel();
					return INF_MSGPROC_BREAK;
				}

				return OnLButtonUp(wParam,lParam);
			}
			break;
	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			VOID CINFArenaTeamInfo::AppCancel(BOOL bButton)
/// \brief		아레나 신청을 취소한다.
/// \author		dgwoo
/// \date		2007-05-17 ~ 2007-05-17
/// \warning	
///
/// \param		bButton : 버튼으로 누른상태인가? 기본은 버튼으로 한다.
/// \return		
///////////////////////////////////////////////////////////////////////////////
VOID CINFArenaTeamInfo::AppCancel(BOOL bButton)
{
	// 2007-05-11 by bhsohn 아레나 버그수정
	if(bButton
		&& !m_bTeamInfoShow)
	{// 팀인포가 보이는 상태가 아니라면 버튼인식을 하지 않는다.
		return;
	}

	// 2007-11-22 by bhsohn 아레나 통합서버
//	MSG_FC_ARENA_REAVE_TEAM sMsg;
//	sMsg.ArenaMode = ((CINFGameArena*)m_pParent)->m_nArenaMode;
//	sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
	if(((CINFGameArena*)m_pParent)->GetTeamNum() >= 0)
	{// 방번호가 없을때는 오류.
//		sMsg.TeamNum = ((CINFGameArena*)m_pParent)->GetTeamNum();
//		g_pFieldWinSocket->SendMsg(T_FC_ARENA_REAVE_TEAM,(char*)&sMsg,sizeof(sMsg));
		((CINFGameArena*)m_pParent)->SendArenaLeaveTeam(((CINFGameArena*)m_pParent)->m_nArenaMode);

	}else
	{
		DbgOut("T_FC_ARENA_REAVE_TEAM (not Team Number)\n");
	}
}

VOID CINFArenaTeamInfo::ClickReadyButton()
{
	if(!m_bTeamInfoShow)
	{// 팀인포가 보이는 상태가 아니라면 버튼인식을 하지 않는다.
		return;
	}
	if(m_fArenaButtonGap > ARENA_BUTTON_GAP)
	{
		if(m_bReady)
		{// 준비 해제.
			g_pFieldWinSocket->SendMsg(T_FC_ARENA_TEAM_READY_FINISH_CANCEL,NULL,NULL);
		}else
		{
			// 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
			if(TRUE == g_pD3dApp->IsDoingInfluenceWar())
			{
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070427_0104,COLOR_ERROR); //"세력전이 진행 중이므로 참가할 수 없습니다."
				return;
			}
			// end 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경

			// 준비 
			g_pFieldWinSocket->SendMsg(T_FC_ARENA_TEAM_READY_FINISH,NULL,NULL);
		}
		m_fArenaButtonGap = 0;
	}else
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070510_0100,COLOR_ERROR);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		아레나 레뒤 상태 체크
/// \author		// 2007-11-22 by bhsohn 아레나 통합서버
/// \date		2007-12-17 ~ 2007-12-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFArenaTeamInfo::IsArenaReady()
{
	return m_bReady;
}