// INFChannelList.cpp: implementation of the CINFChannelList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFChannelList.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "INFGameMain.h"
#include "D3DHanFont.h"
#include "GameDataLast.h"
#include "INFWindow.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "FieldWinSocket.h"
#include "INFScrollBar.h"
#include "ObjectChild.h"
#include "ClientParty.h"
#include "dxutil.h"
#include "AtumDatabase.h"

#define CHANNEL_LIST_SIZE_X				233
#define CHANNEL_LIST_SIZE_Y				201
#define CHANNEL_LIST_START_X			((g_pD3dApp->GetBackBufferDesc().Width - CHANNEL_LIST_SIZE_X)/2)
#define CHANNEL_LIST_START_Y			((g_pD3dApp->GetBackBufferDesc().Height - CHANNEL_LIST_SIZE_Y)/2)
#define CHANNEL_LIST_TITLE_START_X		(CHANNEL_LIST_START_X+9)
#define CHANNEL_LIST_TITLE_START_Y		(CHANNEL_LIST_START_Y+6)
#define CHANNEL_LIST_BACK_START_X		(CHANNEL_LIST_START_X+12)
#define CHANNEL_LIST_BACK_START_Y		(CHANNEL_LIST_START_Y+27)
#define CHANNEL_LIST_MAPNAME_START_X	(CHANNEL_LIST_START_X+31)
#define CHANNEL_LIST_MAPNAME_START_Y	(CHANNEL_LIST_START_Y+53)
#define CHANNEL_LIST_LIST_START_X		(CHANNEL_LIST_START_X+31)
#define CHANNEL_LIST_LIST_START_Y		(CHANNEL_LIST_START_Y+70)
#define CHANNEL_LIST_LINE_INTERVAL		17
#define CHANNEL_LIST_LIST_SIZE_X		162
#define CHANNEL_LIST_OK_BUTTON_START_X	(CHANNEL_LIST_START_X+172)
#define CHANNEL_LIST_OK_BUTTON_START_Y	(CHANNEL_LIST_START_Y+161)
#define CHANNEL_LIST_OK_BUTTON_SIZE_X	38
#define CHANNEL_LIST_OK_BUTTON_SIZE_Y	17

#define SCROLL_START_X					(CHANNEL_LIST_START_X+202)
#define SCROLL_START_Y					(CHANNEL_LIST_START_Y+69)
#define SCROLL_END_Y					(CHANNEL_LIST_START_Y+154)
#define SCROLL_LINE_LENGTH				(SCROLL_END_Y - SCROLL_START_Y)

#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI) // 2008-04-30 by bhsohn 태국 버전 추가
#define CHANNEL_LIST_TEXT_Y				0
#else
#define CHANNEL_LIST_TEXT_Y				1
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFChannelList::CINFChannelList(CAtumNode* pParent)
{
	g_pChannelList = this;
	m_pParent = pParent;
	m_bRestored = FALSE;
	m_pImgBack = NULL;
	m_pImgTitle = NULL;
	m_pImgScrollBar = NULL;
	memset(m_pFontChannelList, 0x00, sizeof(DWORD)*CHANNEL_LIST_NUMBER);
	memset(m_pImgButtonOk, 0x00, sizeof(DWORD)*CHANNEL_BUTTON_NUBER);
	m_pFontMapName = NULL;
	m_pImgHightLight = NULL;
	m_pScroll = NULL;

	Reset();
}

CINFChannelList::~CINFChannelList()
{
	g_pChannelList = NULL;
	SAFE_DELETE(m_pImgBack);
	SAFE_DELETE(m_pImgTitle);
	SAFE_DELETE(m_pImgScrollBar);
	SAFE_DELETE(m_pImgHightLight);
	for(int i=0;i<CHANNEL_LIST_NUMBER;i++)
	{
		SAFE_DELETE(m_pFontChannelList[i]);
	}
	for(int i=0;i<CHANNEL_BUTTON_NUBER;i++)
	{
		SAFE_DELETE(m_pImgButtonOk[i]);
	}
	SAFE_DELETE(m_pScroll);
}

void CINFChannelList::Reset()
{
//	m_nCurrentSelectIndex = 0;
//	m_nCurrentScrollNumber = 0;
	memset(m_szChannelList, 0x00, CHANNEL_LIST_NUMBER*CHANNEL_LIST_STRING_LENGTH);
	memset(m_szMapName, 0x00, SIZE_MAX_MAP_NAME);
	m_nButtonState = BUTTON_STATE_NORMAL;
	m_nChannelListNumber = 0;

	CVectorChannelIterator it = m_vecChannelList.begin();
	while(it != m_vecChannelList.end())
	{
		SAFE_DELETE(*it);
		it++;
	}
	m_vecChannelList.clear();
	memset(&m_msgEventSelectChannel, 0x00, sizeof(MSG_FC_EVENT_SELECT_CHANNEL));
}

void CINFChannelList::RecvStartChannelList(int nMapIndex, int nTargetIndex)
{
	Reset();
	m_msgEventSelectChannel.MapChannelIndex.MapIndex = nMapIndex;
	m_msgEventSelectChannel.WarpTargetIndex = nTargetIndex;
}

void CINFChannelList::RecvChannelList(MEX_CHANNEL_INFO* pChannel)
{
	MEX_CHANNEL_INFO* pNew = new MEX_CHANNEL_INFO;
	memcpy(pNew, pChannel, sizeof(MEX_CHANNEL_INFO));
/*	if(m_vecChannelList.size() <CHANNEL_LIST_NUMBER)
	{
		if(pChannel->Crowdedness<30)
		{
			wsprintf(m_szChannelList[m_vecChannelList.size()],"%3d%20s",pNew->ChannelIndex,"원할");
		}
		else if(pChannel->Crowdedness<60)
		{
			wsprintf(m_szChannelList[m_vecChannelList.size()],"%3d%20s",pNew->ChannelIndex,"보통");
		}
		else
		{
			wsprintf(m_szChannelList[m_vecChannelList.size()],"%3d%20s",pNew->ChannelIndex,"혼잡");
		}
	}*/
	m_vecChannelList.push_back(pNew);
}

void CINFChannelList::RecvDoneChannelList()
{
	m_nChannelListNumber = m_vecChannelList.size();
	m_pScroll->SetNumberOfData( m_nChannelListNumber );
}

HRESULT CINFChannelList::InitDeviceObjects()
{
	DataHeader* pDataHeader;
	pDataHeader = m_pGameData->Find("chbk");
	m_pImgBack = new CINFImage;
	m_pImgBack->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	pDataHeader = m_pGameData->Find("chtitle");
	m_pImgTitle = new CINFImage;
	m_pImgTitle->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	pDataHeader = m_pGameData->Find("c_scrlb");
	m_pImgScrollBar = new CINFImage;
	m_pImgScrollBar->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	pDataHeader = m_pGameData->Find("chhlgt");
	m_pImgHightLight = new CINFImage;
	m_pImgHightLight->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	for(int i=0;i<CHANNEL_BUTTON_NUBER;i++)
	{
		char buf[64];
		wsprintf(buf, "shlaok0%d",i);
		pDataHeader = m_pGameData->Find(buf);
		m_pImgButtonOk[i] = new CINFImage;
		m_pImgButtonOk[i]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	}
	for(int i=0;i<CHANNEL_LIST_NUMBER;i++)
	{
		m_pFontChannelList[i] = new CD3DHanFont( _T(g_pD3dApp->GetFontStyle()), 9, D3DFONT_ZENABLE, FALSE, 256, 32);
		m_pFontChannelList[i]->InitDeviceObjects(g_pD3dDev) ;
	}
	m_pFontMapName = new CD3DHanFont( _T(g_pD3dApp->GetFontStyle()), 9, D3DFONT_ZENABLE, FALSE, 256, 32);
	m_pFontMapName->InitDeviceObjects(g_pD3dDev) ;

	m_pScroll = new CINFScrollBar(this,
								SCROLL_START_X, 
								SCROLL_START_Y, 
								SCROLL_LINE_LENGTH,
								CHANNEL_LIST_NUMBER);
	m_pScroll->SetGameData( m_pGameData );
	m_pScroll->InitDeviceObjects();
	m_pScroll->SetWheelRect(CHANNEL_LIST_LIST_START_X, 
		CHANNEL_LIST_LIST_START_Y,
		CHANNEL_LIST_LIST_START_X+CHANNEL_LIST_LIST_SIZE_X,
		CHANNEL_LIST_LIST_START_Y+CHANNEL_LIST_LINE_INTERVAL*CHANNEL_LIST_NUMBER);
	return S_OK;
}

HRESULT CINFChannelList::RestoreDeviceObjects()
{
	if(!m_bRestored)
	{
		m_pImgBack->RestoreDeviceObjects();
		m_pImgTitle->RestoreDeviceObjects();
		m_pImgScrollBar->RestoreDeviceObjects();
		m_pImgHightLight->RestoreDeviceObjects();
		for(int i=0;i<CHANNEL_BUTTON_NUBER;i++)
		{
			m_pImgButtonOk[i]->RestoreDeviceObjects();
		}
		for(int i=0;i<CHANNEL_LIST_NUMBER;i++)
		{
			m_pFontChannelList[i]->RestoreDeviceObjects() ;
		}
		m_pFontMapName->RestoreDeviceObjects();
		m_pScroll->RestoreDeviceObjects();

		m_bRestored = TRUE;
	}
	return S_OK;
}

HRESULT CINFChannelList::InvalidateDeviceObjects()
{
	if(m_bRestored)
	{
		m_pImgBack->InvalidateDeviceObjects();
		m_pImgTitle->InvalidateDeviceObjects();
		m_pImgScrollBar->InvalidateDeviceObjects();
		m_pImgHightLight->InvalidateDeviceObjects();
		for(int i=0;i<CHANNEL_BUTTON_NUBER;i++)
		{
			m_pImgButtonOk[i]->InvalidateDeviceObjects();
		}
		for(int i=0;i<CHANNEL_LIST_NUMBER;i++)
		{
			m_pFontChannelList[i]->InvalidateDeviceObjects() ;
		}
		m_pFontMapName->InvalidateDeviceObjects();
		m_pScroll->InvalidateDeviceObjects();

		m_bRestored = FALSE;
	}
	return S_OK;
}

HRESULT CINFChannelList::DeleteDeviceObjects()
{
	m_pImgBack->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgBack);
	m_pImgTitle->InvalidateDeviceObjects();
	SAFE_DELETE(m_pImgTitle);
	m_pImgScrollBar->InvalidateDeviceObjects();
	SAFE_DELETE(m_pImgScrollBar);
	m_pImgHightLight->InvalidateDeviceObjects();
	SAFE_DELETE(m_pImgHightLight);
	for(int i=0;i<CHANNEL_BUTTON_NUBER;i++)
	{
		m_pImgButtonOk[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgButtonOk[i]);
	}
	for(int i=0;i<CHANNEL_LIST_NUMBER;i++)
	{
		m_pFontChannelList[i]->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontChannelList[i]);
	}
	m_pFontMapName->InvalidateDeviceObjects();
	SAFE_DELETE(m_pFontMapName);
	m_pScroll->DeleteDeviceObjects();
	SAFE_DELETE(m_pScroll);
	return S_OK;
}


void CINFChannelList::Render()
{
	g_pGameMain->m_pInfWindow->RenderCenterWindow( CHANNEL_LIST_START_X, 
												CHANNEL_LIST_START_Y, 
												CHANNEL_LIST_SIZE_X, 
												CHANNEL_LIST_SIZE_Y, FALSE);
	m_pImgBack->Move(CHANNEL_LIST_BACK_START_X, CHANNEL_LIST_BACK_START_Y);
	m_pImgBack->Render();
	m_pImgTitle->Move(CHANNEL_LIST_TITLE_START_X, CHANNEL_LIST_TITLE_START_Y);
	m_pImgTitle->Render();
//	if(m_nCurrentSelectIndex != -1 )
//	{
//		m_pImgHightLight->Move(CHANNEL_LIST_LIST_START_X+1, 
//			CHANNEL_LIST_LIST_START_Y+CHANNEL_LIST_LINE_INTERVAL*m_nCurrentSelectIndex+1);
//		m_pImgHightLight->Render();
//	}
	if(m_pScroll->GetCurrentSelectWindowIndex() >= 0 &&
		m_pScroll->GetCurrentSelectWindowIndex() < CHANNEL_LIST_NUMBER)
	{
		m_pImgHightLight->Move(CHANNEL_LIST_LIST_START_X+1, 
			CHANNEL_LIST_LIST_START_Y+CHANNEL_LIST_LINE_INTERVAL*m_pScroll->GetCurrentSelectWindowIndex()+1);
		m_pImgHightLight->Render();
	}
	
	if(m_nButtonState != BUTTON_STATE_NORMAL)
	{
		m_pImgButtonOk[m_nButtonState]->Move(CHANNEL_LIST_OK_BUTTON_START_X,CHANNEL_LIST_OK_BUTTON_START_Y);
		m_pImgButtonOk[m_nButtonState]->Render();
	}
	if(m_szMapName[0])
	{
		m_pFontMapName->DrawText(CHANNEL_LIST_MAPNAME_START_X,
			CHANNEL_LIST_MAPNAME_START_Y,
			GUI_FONT_COLOR,
			m_szMapName,0L);
	}
//	for(int i=0;i<m_nChannelListNumber;i++)
//	{
//		m_pFontChannelList[i]->DrawText(CHANNEL_LIST_LIST_START_X+1,
//			CHANNEL_LIST_LIST_START_Y+CHANNEL_LIST_LINE_INTERVAL*i+1,
//			m_nCurrentSelectIndex == i ? GUI_SELECT_FONT_COLOR : GUI_FONT_COLOR,
//			m_szChannelList[i],0L);
//	}
	for(int i=0;i<CHANNEL_LIST_NUMBER;i++)
	{
		int index = m_pScroll->GetCurrentScrollIndex()+i;
		if(index >= m_vecChannelList.size())
		{
			break;
		}
		MEX_CHANNEL_INFO* pChannel = m_vecChannelList[index];
		char stChannelIndex[32] = {0,};

		// 2006-11-08 by ispark, 중립 지역에서는 일반 숫자로 표시
		//MAP_INFO* pMapInfo = g_pDatabase->GetMapInfo(g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex);
		// 2007-02-06 by dgwoo 맵인덱스를 워프시 통과할 맵으로 변경.
		MAP_INFO* pMapInfo = g_pDatabase->GetMapInfo(m_msgEventSelectChannel.MapChannelIndex.MapIndex);
		if(MAP_INFLUENCE_NEUTRALITY == pMapInfo->MapInfluenceType)
		{
			// 중립지역
// 2007-02-06 by dgwoo 중립지역은 모두 전쟁지대이다.
//			if(0 >= index)
//				wsprintf(stChannelIndex, "%d", pChannel->ChannelIndex);
//			else
//				wsprintf(stChannelIndex, "%d", pChannel->ChannelIndex);
			wsprintf(stChannelIndex, "%d(%s)", pChannel->ChannelIndex,STRMSG_C_061106_0100);
		}
		else
		{
			// 2010. 11. 15. by hsLee. 버닝타임 맵일 경우 무조건 안전 지대로 표시.
			if ( NULL == g_pDatabase->GetPtr_BurningMapInfo( pMapInfo->MapIndex ) )
			{
				// 2006-11-06 by dgwoo 전쟁지대와 안전지대를 표시.
				if(0 >= index)
					wsprintf(stChannelIndex, "%d(%s)", pChannel->ChannelIndex,STRMSG_C_061106_0100);
				else
					wsprintf(stChannelIndex, "%d(%s)", pChannel->ChannelIndex,STRMSG_C_061106_0101);
			}
			else
			{
				wsprintf(stChannelIndex, "%d(%s)", pChannel->ChannelIndex,STRMSG_C_061106_0101);
			}
		}

		if(pChannel->Crowdedness<30)
		{
			wsprintf(m_szChannelList[i],"%s",STRMSG_C_SERVER_0001);//"원활"
		}
		else if(pChannel->Crowdedness<60)
		{
			wsprintf(m_szChannelList[i],"%s",STRMSG_C_SERVER_0002);//"보통"
		}
		else
		{
			wsprintf(m_szChannelList[i],"%s",STRMSG_C_SERVER_0003);//"혼잡"
		}
		m_pFontChannelList[i]->DrawText(CHANNEL_LIST_LIST_START_X+1,
			CHANNEL_LIST_LIST_START_Y+CHANNEL_LIST_LINE_INTERVAL*i+CHANNEL_LIST_TEXT_Y,
			m_pScroll->GetCurrentSelectWindowIndex() == i ? GUI_SELECT_FONT_COLOR : GUI_FONT_COLOR,
			stChannelIndex,0L);
		m_pFontChannelList[i]->DrawText(CHANNEL_LIST_LIST_START_X+111,
			CHANNEL_LIST_LIST_START_Y+CHANNEL_LIST_LINE_INTERVAL*i+CHANNEL_LIST_TEXT_Y,
			m_pScroll->GetCurrentSelectWindowIndex() == i ? GUI_SELECT_FONT_COLOR : GUI_FONT_COLOR,
			m_szChannelList[i],0L);
	}
	m_pScroll->Render();
}

void CINFChannelList::Tick()
{

}

int CINFChannelList::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_pScroll)
	{
		if(m_pScroll->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		{
			return INF_MSGPROC_BREAK;
		}
	}
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.y > CHANNEL_LIST_OK_BUTTON_START_Y && 
				pt.y < CHANNEL_LIST_OK_BUTTON_START_Y + CHANNEL_LIST_OK_BUTTON_SIZE_Y &&
				pt.x > CHANNEL_LIST_OK_BUTTON_START_X && 
				pt.x < CHANNEL_LIST_OK_BUTTON_START_X+CHANNEL_LIST_OK_BUTTON_SIZE_X)
			{
				if(m_nButtonState != BUTTON_STATE_DOWN)
					m_nButtonState = BUTTON_STATE_UP;
			}
			else 
			{
				m_nButtonState = BUTTON_STATE_NORMAL;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.y > CHANNEL_LIST_OK_BUTTON_START_Y && 
				pt.y < CHANNEL_LIST_OK_BUTTON_START_Y + CHANNEL_LIST_OK_BUTTON_SIZE_Y &&
				pt.x > CHANNEL_LIST_OK_BUTTON_START_X && 
				pt.x < CHANNEL_LIST_OK_BUTTON_START_X+CHANNEL_LIST_OK_BUTTON_SIZE_X)
			{
				m_nButtonState = BUTTON_STATE_DOWN;
			}
			else 
			{
				m_nButtonState = BUTTON_STATE_NORMAL;
			}
//			if( pt.x > CHANNEL_LIST_LIST_START_X && 
//				pt.x < CHANNEL_LIST_LIST_START_X + CHANNEL_LIST_LIST_SIZE_X &&
//				pt.y > CHANNEL_LIST_LIST_START_Y && 
//				pt.y < CHANNEL_LIST_LIST_START_Y + CHANNEL_LIST_LINE_INTERVAL*CHANNEL_LIST_NUMBER)
//			{
//				int i = (pt.y-CHANNEL_LIST_LIST_START_Y)/CHANNEL_LIST_LINE_INTERVAL;
//				if(i>=0 && i<CHANNEL_LIST_NUMBER)
//				{
//					if(m_vecChannelList.size() >= i + m_nCurrentScrollNumber)
//					{
//						m_nCurrentSelectIndex = i;
//					}
//				}
//			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.y > CHANNEL_LIST_OK_BUTTON_START_Y && 
				pt.y < CHANNEL_LIST_OK_BUTTON_START_Y + CHANNEL_LIST_OK_BUTTON_SIZE_Y &&
				pt.x > CHANNEL_LIST_OK_BUTTON_START_X && 
				pt.x < CHANNEL_LIST_OK_BUTTON_START_X+CHANNEL_LIST_OK_BUTTON_SIZE_X)
			{
				if(m_nButtonState == BUTTON_STATE_DOWN)
				{
					OnOkButtonClicked();
				}
				m_nButtonState = BUTTON_STATE_UP;
			}
			else 
			{
				m_nButtonState = BUTTON_STATE_NORMAL;
			}
		}
		break;
 	case WM_LBUTTONDBLCLK:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.x > CHANNEL_LIST_LIST_START_X &&
				pt.x < CHANNEL_LIST_LIST_START_X+CHANNEL_LIST_LIST_SIZE_X &&
				pt.y > CHANNEL_LIST_LIST_START_Y &&
				pt.y < CHANNEL_LIST_LIST_START_Y+CHANNEL_LIST_LINE_INTERVAL*CHANNEL_LIST_NUMBER)
			{
				OnOkButtonClicked();
			}

		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFChannelList::OnOkButtonClicked()
{
//	int index = m_nCurrentScrollNumber + m_nCurrentSelectIndex;
//	if(m_nCurrentSelectIndex >= 0 && 
//		index >= 0 && 
//		index < m_vecChannelList.size())
//	{
//		m_msgEventSelectChannel.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
//		m_msgEventSelectChannel.MapChannelIndex.ChannelIndex = m_vecChannelList[index]->ChannelIndex;
//		g_pD3dApp->m_pFieldWinSocket->SendMsg(T_FC_EVENT_SELECT_CHANNEL, (char*)&m_msgEventSelectChannel, sizeof(m_msgEventSelectChannel));
//
//		DBGOUT("필드서버 상황 : 채널 선택 전송[Map:%d][Channel:%d]\n", 
//			m_msgEventSelectChannel.MapChannelIndex.MapIndex,
//			m_msgEventSelectChannel.MapChannelIndex.ChannelIndex );
//	}
	int nCurrentSelectRealIndex = m_pScroll->GetCurrentSelectDataIndex();
	if( nCurrentSelectRealIndex >= 0 && 
		nCurrentSelectRealIndex < m_vecChannelList.size())
	{
		m_msgEventSelectChannel.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
		m_msgEventSelectChannel.MapChannelIndex.ChannelIndex = m_vecChannelList[nCurrentSelectRealIndex]->ChannelIndex;
		// 내가 파티 마스터라면 MSG_FC_EVENT_SELECT_CHANNEL_WITH_PARTY 를 보낸다.
//		if(g_pShuttleChild->m_infoParty.bPartyType == _PARTYMASTER)
		if(g_pShuttleChild->m_pClientParty->GetPartyInfo().bPartyType == _PARTYMASTER)
		{
			g_pShuttleChild->m_pClientParty->FSendEventSelectChannelWithParty(m_msgEventSelectChannel);
//			INIT_MSG_WITH_BUFFER(MSG_FC_EVENT_SELECT_CHANNEL_WITH_PARTY, T_FC_EVENT_SELECT_CHANNEL_WITH_PARTY, sMsg, buffer);
//			
//			sMsg->ClientIndex		= m_msgEventSelectChannel.ClientIndex;
//			sMsg->WarpTargetIndex	= m_msgEventSelectChannel.WarpTargetIndex;
//			sMsg->MapChannelIndex	= m_msgEventSelectChannel.MapChannelIndex;
//			
//			int cont = 0;
//			for(int i=0;i<MAX_PARTY_NUMBER - 1;i++)
//			{
//				if(g_pShuttleChild->m_nCharactUniqueNumber[i])
//				{
//					memcpy(buffer+MSG_SIZE(MSG_FC_EVENT_SELECT_CHANNEL_WITH_PARTY)+i*sizeof(UINT), &g_pShuttleChild->m_nCharactUniqueNumber[i], sizeof(UINT));
//					cont++;
//				}
//			}
//			sMsg->nPartyMembers = cont;
//			
//			g_pD3dApp->m_pFieldWinSocket->Write(buffer, MSG_SIZE(MSG_FC_EVENT_SELECT_CHANNEL_WITH_PARTY) + cont*sizeof(UINT));
//			
//			if(g_pShuttleChild->m_dwState != _NORMAL && g_pShuttleChild->m_infoParty.bPartyType == _PARTYMASTER)
//			{
//				for(int i=0;i<MAX_PARTY_NUMBER-1;i++)
//				{
//					g_pShuttleChild->m_nCharactUniqueNumber[i] = 0;
//				}
//			}
//			DBGOUT("필드서버 상황 : 채널 선택 후 파티 워프시 파티원 정보를 서버로 전송[Map:%d][Channel:%d]\n", 
//			m_msgEventSelectChannel.MapChannelIndex.MapIndex,
//			m_msgEventSelectChannel.MapChannelIndex.ChannelIndex );		
		}
		else
		{			
			g_pD3dApp->m_pFieldWinSocket->SendMsg(T_FC_EVENT_SELECT_CHANNEL, (char*)&m_msgEventSelectChannel, sizeof(m_msgEventSelectChannel));

			DBGOUT("Field Server State : Send --> T_FC_EVENT_SELECT_CHANNEL [Map:%d][Channel:%d]\n", 
			m_msgEventSelectChannel.MapChannelIndex.MapIndex,
			m_msgEventSelectChannel.MapChannelIndex.ChannelIndex );
		}		
	}
}

