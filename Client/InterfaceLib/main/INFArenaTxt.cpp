// INFArenaTxt.cpp: implementation of the CINFArenaTxt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "INFArenaTxt.h"
#include "GameDataLast.h"
#include "INFGameMain.h"
#include "INFGameArena.h"

extern CAtumApplication * g_pD3dApp;

#define	COUNT_TIME			1.0f
#define ISSUE_TIME			5.0f

// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
// 페이드 모드
#define		TEAM_BK_FADE_NONE		-1
#define		TEAM_BK_FADE_OUT		0
#define		TEAM_BK_FADE_IN			1
#define		TEAM_BK_FADE_SHOW		2

#define		TEAM_BK_SHOW_TIME			(5.0f)	// 보여지는 시간
#define		TEAM_BK_FADE_TIME			(1.0f)	// 숨겨지는 시간

// enjd 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFArenaTxt::CINFArenaTxt(CAtumNode* pParent)
{
	m_pParent = pParent;
	m_nArenaShowState = ARENA_TXT_MODE_NONE;
	m_nArenaIssue = 0;
	m_nArenaCnt = 0;
	m_pGameData = NULL;
	int nCnt = 0;
	for(nCnt = 0; nCnt < MAX_ARENA_CNT;nCnt++)
	{
		m_pArenaCnt[nCnt] = NULL;
	}
	for(nCnt = 0; nCnt < ARENA_ISSUE_DRAW;nCnt++)
	{
		m_pArenaTxt[nCnt] = NULL;
	}
	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	for(nCnt = 0; nCnt < MAX_ARENA_TEAM_CNT;nCnt++)
	{
		m_pArenaTeamTxt[nCnt] = NULL;
	}	
	// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정	
	
	m_fArenaCntTick = 0.0f;

	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	m_nFadeMode = TEAM_BK_FADE_NONE;
	m_fFadeInTime = 0;
	m_dwBkAlpha = 0xffffffff;		
	m_fTeamInfoShowTime = 0;	// 보여진 시간 
	m_nInflIdx = ARENA_TEAM_BLUE;
	
}

CINFArenaTxt::~CINFArenaTxt()
{

}
HRESULT CINFArenaTxt::InitDeviceObjects()
{
	DataHeader	* pDataHeader = NULL;
	char buf[30] ;
	
	int nCnt = 0;
	int	i;
	for(nCnt = 0; nCnt < MAX_ARENA_CNT; nCnt++)
	{
		if(NULL == m_pArenaCnt[nCnt])
		{
			m_pArenaCnt[nCnt] = new CINFImage;
		}
		wsprintf(buf,"arecnt%d", nCnt);		
		
		pDataHeader = g_pGameMain->FindResource(buf);
		m_pArenaCnt[nCnt]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}	

	for(i = 0 ; i < ARENA_ISSUE_DRAW ; i++)
	{
		if(NULL == m_pArenaTxt[i])
		{
			m_pArenaTxt[i] = new CINFImage;
		}		
		wsprintf(buf,"issue%d",i+1);
		//wsprintf(buf,"arecnt0");		
		pDataHeader = g_pGameMain->FindResource(buf);
		m_pArenaTxt[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}
	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정	
	{
		// 블루팀
		if(NULL == m_pArenaTeamTxt[ARENA_TEAM_BLUE])
		{
			m_pArenaTeamTxt[ARENA_TEAM_BLUE] = new CINFImage;
		}		
		wsprintf(buf,"bluelogo");		
		pDataHeader = g_pGameMain->FindResource(buf);
		m_pArenaTeamTxt[ARENA_TEAM_BLUE]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		// 레드팀 
		if(NULL == m_pArenaTeamTxt[ARENA_TEAM_RED])
		{
			m_pArenaTeamTxt[ARENA_TEAM_RED] = new CINFImage;
		}		
		wsprintf(buf,"redlogo");		
		pDataHeader = g_pGameMain->FindResource(buf);
		m_pArenaTeamTxt[ARENA_TEAM_RED]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}		
	// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정	
	return S_OK ;	
}

HRESULT CINFArenaTxt::RestoreDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0; nCnt < MAX_ARENA_CNT;nCnt++)
	{
		m_pArenaCnt[nCnt]->RestoreDeviceObjects();	
	}
	for(nCnt = 0; nCnt < ARENA_ISSUE_DRAW;nCnt++)
	{
		m_pArenaTxt[nCnt]->RestoreDeviceObjects();	
	}
	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	for(nCnt = 0; nCnt < MAX_ARENA_TEAM_CNT;nCnt++)
	{
		m_pArenaTeamTxt[nCnt]->RestoreDeviceObjects();			
	}
	// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정

	return S_OK ;
}
HRESULT CINFArenaTxt::DeleteDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0; nCnt < MAX_ARENA_CNT;nCnt++)
	{
		m_pArenaCnt[nCnt]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pArenaCnt[nCnt]);
	}
	for(nCnt = 0; nCnt < ARENA_ISSUE_DRAW;nCnt++)
	{		
		m_pArenaTxt[nCnt]->DeleteDeviceObjects();	
		SAFE_DELETE(m_pArenaTxt[nCnt]);
	}
	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	for(nCnt = 0; nCnt < MAX_ARENA_TEAM_CNT;nCnt++)
	{
		m_pArenaTeamTxt[nCnt]->DeleteDeviceObjects();
		SAFE_DELETE(m_pArenaTeamTxt[nCnt]);		
	}
	// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정

	return S_OK ;
}
HRESULT CINFArenaTxt::InvalidateDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0; nCnt < MAX_ARENA_CNT;nCnt++)
	{
		m_pArenaCnt[nCnt]->InvalidateDeviceObjects();	
	}
	for(nCnt = 0; nCnt < ARENA_ISSUE_DRAW;nCnt++)
	{		
		m_pArenaTxt[nCnt]->InvalidateDeviceObjects();			
	}
	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	for(nCnt = 0; nCnt < MAX_ARENA_TEAM_CNT;nCnt++)
	{
		m_pArenaTeamTxt[nCnt]->InvalidateDeviceObjects();					
	}
	// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	
	return S_OK ;
}
void CINFArenaTxt::Tick()
{
	switch(m_nArenaShowState)
	{
	case ARENA_TXT_MODE_CNT:
		{
			FLOAT fElapsedTime = g_pD3dApp->GetCheckElapsedTime();
			m_fArenaCntTick += fElapsedTime;
			if(m_fArenaCntTick > COUNT_TIME)
			{
				m_fArenaCntTick = 0.0f;
				m_nArenaCnt --;
				if(m_nArenaCnt < 0)
				{
					m_nArenaCnt = 0;
					m_nArenaShowState = ARENA_TXT_MODE_NONE;					
					
					((CINFGameArena*)m_pParent)->StartWar();
				}
			}
		}
		break;
	case ARENA_TXT_MODE_TXT:
		{
			FLOAT fElapsedTime = g_pD3dApp->GetCheckElapsedTime();
			m_fArenaCntTick += fElapsedTime;
			if(m_fArenaCntTick > ISSUE_TIME)
			{
				m_nArenaShowState = ARENA_TXT_MODE_NONE;					
				((CINFGameArena*)m_pParent)->Finish();
			}
		}
		break;
		// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	case ARENA_TXT_TEAMINFO_TXT:
		{
			TickFadeMode();			
		}
		break;
		// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	}
}

void CINFArenaTxt::Render()
{		
	switch(m_nArenaShowState)
	{
	case ARENA_TXT_MODE_TXT:
		{
			if(m_nArenaIssue < ARENA_ISSUE_DRAW)
			{
				POINT ptArena = m_pArenaTxt[m_nArenaIssue]->GetImgSize();
				float fX,fY;
				fX = (g_pD3dApp->GetBackBufferDesc().Width/2)-(ptArena.x/2);
				fY = (g_pD3dApp->GetBackBufferDesc().Height/2)-(ptArena.y/2);
				
				m_pArenaTxt[m_nArenaIssue]->Move(fX, fY);
				m_pArenaTxt[m_nArenaIssue]->Render();		
			}	
		}
		break;
	case ARENA_TXT_MODE_CNT:
		{
			if(m_nArenaCnt >= 0 && m_nArenaCnt < MAX_ARENA_CNT)
			{
				POINT ptArena = m_pArenaCnt[m_nArenaCnt]->GetImgSize();
				float fX,fY;
				fX = (g_pD3dApp->GetBackBufferDesc().Width/2)-(ptArena.x/2);
				fY = (g_pD3dApp->GetBackBufferDesc().Height/2)-(ptArena.y/2);
				
				m_pArenaCnt[m_nArenaCnt]->Move(fX, fY);
				m_pArenaCnt[m_nArenaCnt]->Render();
			}
			
		}
		break;
		// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	case ARENA_TXT_TEAMINFO_TXT:
		{			
			POINT ptArena = m_pArenaTeamTxt[m_nInflIdx]->GetImgSize();
			float fX,fY;
			fX = (g_pD3dApp->GetBackBufferDesc().Width/2)-(ptArena.x/2);
			fY = 0;

			m_pArenaTeamTxt[m_nInflIdx]->SetColor(m_dwBkAlpha);
			m_pArenaTeamTxt[m_nInflIdx]->Move(fX, fY);
			m_pArenaTeamTxt[m_nInflIdx]->Render();
		}
		break;
		// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	}
}

void CINFArenaTxt::StartArenaCnt()
{
	m_nArenaShowState = ARENA_TXT_MODE_CNT;
	m_nArenaCnt = MAX_ARENA_CNT-1;
	m_fArenaCntTick = 0.0f;
}
void CINFArenaTxt::SetIssue(int issue,float fArenaTick)
{
	m_nArenaIssue = issue - 1;
	m_fArenaCntTick = fArenaTick;
}
void CINFArenaTxt::SetShowState(int ShowState)
{
	m_nArenaShowState = ShowState;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
/// \date		2008-04-17 ~ 2008-04-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFArenaTxt::ShowMyTeamLogo(BYTE byInfluence)
{
	if(COMPARE_INFLUENCE(byInfluence, INFLUENCE_TYPE_VCN))
	{
		m_nInflIdx = ARENA_TEAM_BLUE;
	}
	else if(COMPARE_INFLUENCE(byInfluence, INFLUENCE_TYPE_ANI))
	{
		m_nInflIdx = ARENA_TEAM_RED;
	}
	else
	{
		return;
	}	
	
	m_fTeamInfoShowTime = 0;	// 보여진 시간 
	m_nFadeMode = TEAM_BK_FADE_IN;
	m_fFadeInTime = 0;
	m_dwBkAlpha = 0;		
	SetShowState(ARENA_TXT_TEAMINFO_TXT);	// 아레나 팀정보 Show
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
/// \date		2008-04-17 ~ 2008-04-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFArenaTxt::HidingMyTeamLogo()
{
	m_fTeamInfoShowTime = 0;	// 보여진 시간 
	m_nFadeMode = TEAM_BK_FADE_OUT;
	m_fFadeInTime = 0;
	//m_dwBkAlpha = 0xffffffff;
	
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
/// \date		2008-04-17 ~ 2008-04-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFArenaTxt::HideMyTeamLogo()
{
	m_nFadeMode = TEAM_BK_FADE_NONE;				 
	//m_dwBkAlpha = 0;

	SetShowState(ARENA_TXT_MODE_NONE);	// 다 숨김
	((CINFGameArena*)m_pParent)->HideMyTeamLogo();
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
/// \date		2008-04-17 ~ 2008-04-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFArenaTxt::TickFadeMode()
{	
	switch(m_nFadeMode)
	{
		// 천천히 뜨는중
	case TEAM_BK_FADE_IN:
		{
			m_fFadeInTime += g_pD3dApp->GetCheckElapsedTime();			
			if(m_fFadeInTime > TEAM_BK_FADE_TIME)
			{
				m_nFadeMode = TEAM_BK_FADE_SHOW;				 
				m_dwBkAlpha = 0xffffffff;
				return;				
			}
			m_dwBkAlpha = g_pGameMain->GetCurrentColor(m_fFadeInTime, 
													ALPHA_FADE_IN, 
													TEAM_BK_FADE_TIME);	

		}
		break;
		// 보여지고 있는 상황
	case TEAM_BK_FADE_SHOW:
		{
			m_fTeamInfoShowTime += g_pD3dApp->GetCheckElapsedTime();			
			if(m_fTeamInfoShowTime > TEAM_BK_SHOW_TIME)
			{
				m_fTeamInfoShowTime = 0;
				HidingMyTeamLogo();
			}			
		}
		break;
		// 천천히 숨겨지는중
	case TEAM_BK_FADE_OUT:
		{		
			m_fFadeInTime += g_pD3dApp->GetCheckElapsedTime();			
			if(m_fFadeInTime > TEAM_BK_FADE_TIME)
			{
				HideMyTeamLogo();				
				return;				
			}
			m_dwBkAlpha = g_pGameMain->GetCurrentColor(m_fFadeInTime, 
													ALPHA_FADE_OUT, 
													TEAM_BK_FADE_TIME);	

		}
		break;
	}
	
}