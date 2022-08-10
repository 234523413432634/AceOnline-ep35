// CINFMp3Player.cpp: implementation of the CINFMp3Player class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFMp3Player.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "D3DHanFont.h"
#include "INFScrollBar.h"
#include "INFGameMain.h"
#include "INFWindow.h"
// 2009-01-20 by bhsohn 사운드 시스템 변경
//#include "MusicMP3.h"
#include "MusicMP3Ex.h"
// end 2009-01-20 by bhsohn 사운드 시스템 변경
#include "AtumSound.h"
#include "Interface.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "dxutil.h"

// 기본 포지션 DEFINE
#define MP3PLAYER_BASE_POS_X		(g_pD3dApp->GetBackBufferDesc().Width-251)
#define MP3PLAYER_BASE_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height-37)

// 기본 버튼 상태
#define MP3PLAYER_BUTTON_STATE_NOR		0
#define MP3PLAYER_BUTTON_STATE_OVE		1
#define MP3PLAYER_BUTTON_STATE_PUH		2

// 버튼 종류
#define MP3PLAYER_BUTTON_PRVE			0
#define MP3PLAYER_BUTTON_PLAY			1
#define MP3PLAYER_BUTTON_NEXT			2
#define MP3PLAYER_BUTTON_STOP			3
#define MP3PLAYER_BUTTON_FULL			4
#define MP3PLAYER_BUTTON_MINI			5

// 버튼 사이즈
#define MP3PLAYER_BUTTON_SIZE_W			9
#define MP3PLAYER_BUTTON_SIZE_H			13

// 스크롤 위치
#define MP3PLAYER_POS_X				(g_pD3dApp->GetBackBufferDesc().Width-126)
#define MP3PLAYER_POS_Y				(g_pD3dApp->GetBackBufferDesc().Height-31)
#define MP3PLAYER_LINE_LENGTH		72
#define MP3PLAYER_VOLUM_STEP		20
#define MP3PLAYER_VOLUM_LEVEL		50
#define MP3PLAYER_LINE_GAB			12

#define MP3PLAYER_LIST_POS_X		(g_pD3dApp->GetBackBufferDesc().Width-14)
#define MP3PLAYER_LIST_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height-164)
#define MP3PLAYER_LIST_LINE_LENGTH	104
#define MP3PLAYER_LIST_LINE_GAB		9

#define MP3PLAYER_LOOP				100
#define MP3PLAYER_END				0

// 탭설정
#define MP3PLAYER_TAB_DEFAULT		0	// 기본 재생방식 (리스트 순서가 끝나면 끝)
#define MP3PLAYER_TAB_REPEAT		1	// 기본 재생방식 (리스트 순서가 끝나면 처음부터 다시 재생),
#define MP3PLAYER_TAB_REPEAT1		2	// 한곡만 반복
#define MP3PLAYER_TAB_RANDOM		3	// 무작위 재생 방식

#define MP3PLAYER_TAB_WIDTH			61
#define MP3PLAYER_TAB_HEIGHT		17

#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM) || defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn 태국 버전 추가
#define MP3PLAYER_BASE_POS_MINUS		130
#else
#define MP3PLAYER_BASE_POS_MINUS		132
#endif

//#define MP3PLAYER_
//#define MP3PLAYER_
//#define MP3PLAYER_

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFMp3Player::CINFMp3Player()
{
	FLOG( "CINFMp3Player()" );	

	g_pGameMain->m_bMp3PlayFlag = g_pSOption->sMp3Player;
	m_pImgBack		= NULL;
	int i;
	for(i=0; i<MP3PLAYER_BASE_TAB; i++)
		m_pImgTab[i] = NULL;
	for(i=0; i<MP3PLAYER_BUTTON_STATE; i++)
	{
		m_pImgHidenButton[i]=NULL;
		m_pImgMiniButton[i]=NULL;
		m_pImgNextButton[i]=NULL;
		m_pImgPlayButton[i]=NULL;
		m_pImgPrvButton[i]=NULL;
		m_pImgShowListButton[i]=NULL;
		m_pImgStopButton[i]=NULL;
	}
	m_pImgVolum = NULL;
	m_pImgListBox = NULL;
	m_pImgMiniBase = NULL;
	m_pImgSelectMp3 = NULL;
	
	for(i=0; i<MP3PLAYER_MAX_LIST; i++)
		m_pFontTitle[i]	= NULL;
	m_bMp3PlayListShow = FALSE;				// 시작시 메뉴리스트 보이기
	m_bBaseSizeFull = TRUE;					// 시작시 뮤직플레이어 미니사이즈로 하거나 아님 아니거나
	for(i=0; i<MP3PLAYER_BUTTON_MAIN_STATE; i++)
	{
		m_nButtonStateMain[i] = MP3PLAYER_BUTTON_STATE_NOR;
		m_bButtonStateMain[i] = FALSE;
	}
	m_pScroll = NULL;
	m_pScrollVolum = NULL;
	memset(m_strDirectory, 0x00, MAX_PATH);
	m_vecMp3FileNames.clear();
	m_nCurrentRenderIndex = 0;
	m_nCurrentRenderSelect = 0;
	m_nSelectTab = MP3PLAYER_TAB_REPEAT;
	m_bPlay_Mute = TRUE;
	m_LnMutePos = 0;
	m_bStop_Flag = FALSE;
	memset(m_strMp3Name, 0x00, MAX_PATH);
	m_bMp3Play = FALSE;	
	m_bOriBGSound = TRUE;
	
	// 관리자, 운영자, 데모계정만 디렉토리 변경가능
	if(COMPARE_RACE(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Race,RACE_OPERATION|RACE_GAMEMASTER|RACE_DEMO))
	{
		m_bSetMp3Dir = TRUE;
	}
	else
	{
		m_bSetMp3Dir = FALSE;
	}
}

CINFMp3Player::~CINFMp3Player()
{
	FLOG( "~CINFMp3Player()" );
	
	SAFE_DELETE(m_pImgBack);
	int i;
	for(i=0; i<MP3PLAYER_BASE_TAB; i++)
		SAFE_DELETE(m_pImgTab[i]);
	for(i=0; i<MP3PLAYER_BUTTON_STATE; i++)
	{
		SAFE_DELETE(m_pImgHidenButton[i]);
		SAFE_DELETE(m_pImgMiniButton[i]);
		SAFE_DELETE(m_pImgNextButton[i]);
		SAFE_DELETE(m_pImgPlayButton[i]);
		SAFE_DELETE(m_pImgPrvButton[i]);
		SAFE_DELETE(m_pImgShowListButton[i]);
		SAFE_DELETE(m_pImgStopButton[i]);
	}
	SAFE_DELETE(m_pImgVolum);
	SAFE_DELETE(m_pImgListBox);
	SAFE_DELETE(m_pImgMiniBase);
	SAFE_DELETE(m_pImgSelectMp3);

	for(i=0; i<MP3PLAYER_MAX_LIST; i++)		
		SAFE_DELETE(m_pFontTitle[i]);
	SAFE_DELETE(m_pScroll);
	SAFE_DELETE(m_pScrollVolum);
//	SAFE_DELETE(m_pMp3);
}

HRESULT CINFMp3Player::InitDeviceObjects()
{
	FLOG( "CINFMp3Player::InitDeviceObjects(char* pData, int nSize)" );

	DataHeader	* pDataHeader ;
	char buf[32];
	memset(buf, 0x00, 32);
	
	// 이미지 관련
	wsprintf( buf, "mp_bas");	
	m_pImgBack = new CINFImage;
	pDataHeader = FindResource(buf);
	m_pImgBack->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	int i;
	for(i=0; i<MP3PLAYER_BASE_TAB; i++)
	{
		wsprintf( buf, "mp_tab%d", i);
		m_pImgTab[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgTab[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	}
	
	for(i=0; i<MP3PLAYER_BUTTON_STATE; i++)
	{
		wsprintf( buf, "mp_hi%d", i);
		m_pImgHidenButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgHidenButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		wsprintf( buf, "mp_mi%d", i);
		m_pImgMiniButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgMiniButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		wsprintf( buf, "mp_ne%d", i);
		m_pImgNextButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgNextButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		wsprintf( buf, "mp_pl%d", i);
		m_pImgPlayButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgPlayButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		wsprintf( buf, "mp_pr%d", i);
		m_pImgPrvButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgPrvButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		wsprintf( buf, "mp_sh%d", i);
		m_pImgShowListButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgShowListButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		wsprintf( buf, "mp_st%d", i);
		m_pImgStopButton[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgStopButton[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	}
	m_pImgVolum = new CINFImage;
	pDataHeader = FindResource("mp_vol");
	m_pImgVolum->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	
	m_pImgListBox = new CINFImage;
	pDataHeader = FindResource("mp_lis");
	m_pImgListBox->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	
	m_pImgMiniBase = new CINFImage;
	pDataHeader = FindResource("mp_min");
	m_pImgMiniBase->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	
	m_pImgSelectMp3 = new CINFImage;
	pDataHeader = FindResource("mp_sel");
	m_pImgSelectMp3->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	
	// 폰트 관련
	for(i=0; i<MP3PLAYER_MAX_LIST; i++)
	{
		m_pFontTitle[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, FALSE, 256,32);
		m_pFontTitle[i]->InitDeviceObjects(g_pD3dDev) ;
	}	

	// 스크롤 관련
	m_pScroll = new CINFScrollBar(this,
								MP3PLAYER_LIST_POS_X, 
								MP3PLAYER_LIST_POS_Y, 
								MP3PLAYER_LIST_LINE_LENGTH,
								MP3PLAYER_LIST_LINE_GAB);
	m_pScroll->SetGameData( m_pGameData );
	m_pScroll->InitDeviceObjects();

	m_pScrollVolum = new CINFScrollBar(this,
								MP3PLAYER_POS_X, 
								MP3PLAYER_POS_Y, 
								MP3PLAYER_LINE_LENGTH,
								1,
								6,	// 기타 스크롤바 사이즈
								11, // 기타 스크롤바 사이즈
								"mp_vol",
								INFSCROLL_TYPE_HORIZONTAL
								);
	m_pScrollVolum->SetGameData( m_pGameData );
	m_pScrollVolum->InitDeviceObjects();
	m_pScrollVolum->SetNumberOfData( MP3PLAYER_VOLUM_LEVEL );
	
//	int nVol = MP3PLAYER_VOLUM_LEVEL-((g_pSOption->sMusicVolume*-1)/200);
//	m_pScrollVolum->SetCurrentIndex(nVol);
	m_pScrollVolum->SetCurrentIndex(g_pSOption->sMusicVolume);
	g_pSOption->sMusicVolume+=1;
//	m_pMp3 = new CMusicMP3();
	
	return S_OK;
}

HRESULT CINFMp3Player::RestoreDeviceObjects()
{
	FLOG( "CINFMp3Player::RestoreDeviceObjects()" );

	m_pScroll->SetScrollLinePos( MP3PLAYER_LIST_POS_X,
		MP3PLAYER_LIST_POS_Y);
	m_pScroll->SetWheelRect(MP3PLAYER_BASE_POS_X-1, 
							MP3PLAYER_BASE_POS_Y-132,
							g_pD3dApp->GetBackBufferDesc().Width-4,
							g_pD3dApp->GetBackBufferDesc().Height-39);
	m_pScrollVolum->SetScrollLinePos( MP3PLAYER_POS_X,MP3PLAYER_POS_Y);
	m_pScrollVolum->SetWheelRect(g_pD3dApp->GetBackBufferDesc().Width-256, 
								g_pD3dApp->GetBackBufferDesc().Height-37,
								g_pD3dApp->GetBackBufferDesc().Width-9,
								g_pD3dApp->GetBackBufferDesc().Height-24+(2*MP3PLAYER_VOLUM_STEP));


	m_pImgBack->RestoreDeviceObjects();
	int i;
	for(i=0; i<MP3PLAYER_BASE_TAB; i++)
		m_pImgTab[i]->RestoreDeviceObjects();
	for(i=0; i<MP3PLAYER_BUTTON_STATE; i++)
	{
		m_pImgHidenButton[i]->RestoreDeviceObjects();
		m_pImgMiniButton[i]->RestoreDeviceObjects();
		m_pImgNextButton[i]->RestoreDeviceObjects();
		m_pImgPlayButton[i]->RestoreDeviceObjects();
		m_pImgPrvButton[i]->RestoreDeviceObjects();
		m_pImgShowListButton[i]->RestoreDeviceObjects();
		m_pImgStopButton[i]->RestoreDeviceObjects();
	}
	m_pImgVolum->RestoreDeviceObjects();
	m_pImgListBox->RestoreDeviceObjects();
	m_pImgMiniBase->RestoreDeviceObjects();
	m_pImgSelectMp3->RestoreDeviceObjects();	
	for(i=0; i<MP3PLAYER_MAX_LIST; i++)
		m_pFontTitle[i]->RestoreDeviceObjects();

	m_pScrollVolum->RestoreDeviceObjects();
	m_pScrollVolum->SetWheelRect(g_pD3dApp->GetBackBufferDesc().Width-256, 
		g_pD3dApp->GetBackBufferDesc().Height-37,
		g_pD3dApp->GetBackBufferDesc().Width-9,
		g_pD3dApp->GetBackBufferDesc().Height-24+(2*MP3PLAYER_VOLUM_STEP));
	
	m_pScroll->RestoreDeviceObjects();
	m_pScroll->SetWheelRect(MP3PLAYER_BASE_POS_X-1, 
							MP3PLAYER_BASE_POS_Y-132,
							g_pD3dApp->GetBackBufferDesc().Width-4,
							g_pD3dApp->GetBackBufferDesc().Height-39);
	
	return S_OK;
}

HRESULT CINFMp3Player::InvalidateDeviceObjects()
{
	FLOG( "CINFMp3Player::InvalidateDeviceObjects()" );

	m_pImgBack->InvalidateDeviceObjects();
	int i;
	for(i=0; i<MP3PLAYER_BASE_TAB; i++)
		m_pImgTab[i]->InvalidateDeviceObjects();
	for(i=0; i<MP3PLAYER_BUTTON_STATE; i++)
	{
		m_pImgHidenButton[i]->InvalidateDeviceObjects();
		m_pImgMiniButton[i]->InvalidateDeviceObjects();
		m_pImgNextButton[i]->InvalidateDeviceObjects();
		m_pImgPlayButton[i]->InvalidateDeviceObjects();
		m_pImgPrvButton[i]->InvalidateDeviceObjects();
		m_pImgShowListButton[i]->InvalidateDeviceObjects();
		m_pImgStopButton[i]->InvalidateDeviceObjects();
	}
	m_pImgVolum->InvalidateDeviceObjects();
	m_pImgListBox->InvalidateDeviceObjects();
	m_pImgMiniBase->InvalidateDeviceObjects();
	m_pImgSelectMp3->InvalidateDeviceObjects();

	for(i=0; i<MP3PLAYER_MAX_LIST; i++)
		m_pFontTitle[i]->InvalidateDeviceObjects();
	m_pScrollVolum->InvalidateDeviceObjects();
	m_pScroll->InvalidateDeviceObjects();
	
	return S_OK;
}

HRESULT CINFMp3Player::DeleteDeviceObjects()
{
	FLOG( "CINFMp3Player::DeleteDeviceObjects()" );
	
	m_pImgBack->DeleteDeviceObjects();
	m_pImgVolum->DeleteDeviceObjects();
	m_pImgListBox->DeleteDeviceObjects();
	m_pImgMiniBase->DeleteDeviceObjects();
	m_pImgSelectMp3->DeleteDeviceObjects();
	m_pScrollVolum->DeleteDeviceObjects();
	m_pScroll->DeleteDeviceObjects();

	SAFE_DELETE(m_pImgBack);
	SAFE_DELETE(m_pImgVolum);
	SAFE_DELETE(m_pImgListBox);
	SAFE_DELETE(m_pImgMiniBase);
	SAFE_DELETE(m_pImgSelectMp3);
	SAFE_DELETE(m_pScrollVolum);
	SAFE_DELETE(m_pScroll);
	
	int i;
	for(i=0; i<MP3PLAYER_BASE_TAB; i++)
	{
		m_pImgTab[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgTab[i]);
	}
	for(i=0; i<MP3PLAYER_BUTTON_STATE; i++)
	{
		m_pImgHidenButton[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgHidenButton[i]);
		
		m_pImgMiniButton[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgMiniButton[i]);
				
		m_pImgNextButton[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgNextButton[i]);
			
		m_pImgPlayButton[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgPlayButton[i]);
			
		m_pImgPrvButton[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgPrvButton[i]);
			
		m_pImgShowListButton[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgShowListButton[i]);
		m_pImgStopButton[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgStopButton[i]);
	}
	for(i=0; i<MP3PLAYER_MAX_LIST; i++)
	{
		m_pFontTitle[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontTitle[i]);
	}
//	if(m_pMp3)
//	{
//		m_pMp3->Atum_MusicStop();
//		SAFE_DELETE(m_pMp3);
//	}

	return S_OK;
}

void CINFMp3Player::Render()
{
	FLOG( "CINFMp3Player::Render()" );	

	if(m_pImgBack && m_bBaseSizeFull == TRUE)
	{
		// 풀사이즈 엠피3
		m_pImgBack->Move(MP3PLAYER_BASE_POS_X, MP3PLAYER_BASE_POS_Y);
		m_pImgBack->Render();
		// 버튼 관련 렌더링
		RenderButtonState();
		m_pScrollVolum->Render();
	}
	else
	{
		// 미니사이즈 엠피3
		m_pImgMiniBase->Move(MP3PLAYER_BASE_POS_X+200, MP3PLAYER_BASE_POS_Y);
		m_pImgMiniBase->Render();
	}

	// 리스트 박스 보이기
	if(m_bMp3PlayListShow)
	{
		RenderPlayListBox();
		m_pScroll->Render();
	}	
}

void CINFMp3Player::Tick()
{
	FLOG( "CINFMp3Player::Tick()" );

//	m_pScroll->SetScrollLinePos( MP3PLAYER_LIST_POS_X,
//		MP3PLAYER_LIST_POS_Y);
//	m_pScroll->SetWheelRect(MP3PLAYER_BASE_POS_X-1, 
//							MP3PLAYER_BASE_POS_Y-132,
//							g_pD3dApp->GetBackBufferDesc().Width-4,
//							g_pD3dApp->GetBackBufferDesc().Height-39);
//	m_pScrollVolum->SetScrollLinePos( MP3PLAYER_POS_X,MP3PLAYER_POS_Y);
//	m_pScrollVolum->SetWheelRect(g_pD3dApp->GetBackBufferDesc().Width-256, 
//		g_pD3dApp->GetBackBufferDesc().Height-37,
//		g_pD3dApp->GetBackBufferDesc().Width-9,
//		g_pD3dApp->GetBackBufferDesc().Height-24+(2*MP3PLAYER_VOLUM_STEP));

	// 2006-09-15 by ispark
	if(g_pD3dApp->m_pSound->GetMusicMp3() == NULL)
	{
		return;
	}

	if(m_bBaseSizeFull)
	{		
		// 2006-03-15 by ispark, 볼륨 버그 수정
		// 2006-03-22 by ispark
		int nVol = m_pScrollVolum->GetCurrentScrollIndex();
		if(g_pSOption->sMusicVolume != nVol)
		{
			int nNewVol = -10000;
			if(nVol > 0)
			{
				nNewVol = GetMusicVolume(nVol);
			}
//			nVol = ((nVol*200)-10000);		
			g_pSOption->sMusicVolume = nVol;
			g_pD3dApp->m_pSound->GetMusicMp3()->SetAtumMusicVolume(nNewVol);
		}
	}
	if(m_bOriBGSound)
	{// 2008-03-26 by dgwoo 배경음악이 플레이중에는 반복한다.
		return;
	}
	// 기타 옵션 설정
	switch(m_nSelectTab) 
	{
	case MP3PLAYER_TAB_DEFAULT:
		{
			if(g_pD3dApp->m_pSound->GetMusicMp3()->m_bNowPlay == FALSE)
			{
				vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
				while(it != m_vecMp3FileNames.end())
				{
					if(m_nCurrentRenderIndex == (*it).nIndex)
					{
						if(m_vecMp3FileNames.size()-1 > m_nCurrentRenderIndex)
						{
							m_nCurrentRenderIndex = (*it).nIndex + 1;
							Play_Mp3Music();
							break;
						}
						else
						{// 리스트가 끝나면 노래 멈춤.
						}
					}
					it++;
				}
				
			}
		}
		break;
	case MP3PLAYER_TAB_RANDOM:
		{			
			if(g_pD3dApp->m_pSound->GetMusicMp3()->m_bNowPlay == FALSE)
			{
				int nCnt = 0;
//				vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
//				while(it != m_vecMp3FileNames.end())
//				{
//					if(m_nCurrentRenderIndex == m_vecMp3FileNames[nCnt].nIndex)
//					{						
//						m_nCurrentRenderIndex = m_vecMp3FileNames[m_vecRandom[nCnt]].nIndex;
//						Play_Mp3Music();
//						break;
//					}
//					nCnt++;
//					it++;
//				}
//
				vector<int>::iterator it = m_vecRandom.begin();
				while(it != m_vecRandom.end())
				{
					if(m_nCurrentRenderIndex == m_vecMp3FileNames[m_vecRandom[nCnt]].nIndex)
					{
						nCnt++;
						if(nCnt>m_vecRandom.size()-1)
							nCnt = 0;
						m_nCurrentRenderIndex = m_vecMp3FileNames[m_vecRandom[nCnt]].nIndex;
						Play_Mp3Music();
						break;
					}					
					nCnt++;
					it++;
				}
				
			}
		}
		break;
	case MP3PLAYER_TAB_REPEAT:
		{
			if(g_pD3dApp->m_pSound->GetMusicMp3()->m_bNowPlay == FALSE)
			{
				vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
				while(it != m_vecMp3FileNames.end())
				{
					if(m_nCurrentRenderIndex == (*it).nIndex)
					{
						if(m_vecMp3FileNames.size()-1 > m_nCurrentRenderIndex)
						{
							m_nCurrentRenderIndex = (*it).nIndex + 1;
							Play_Mp3Music();
							break;
						}
						else
						{
							m_nCurrentRenderIndex = m_vecMp3FileNames[0].nIndex;
							Play_Mp3Music();
							break;
						}
					}
					it++;
				}
				
			}
		}
		break;
	case MP3PLAYER_TAB_REPEAT1:
		{
			if(g_pD3dApp->m_pSound->GetMusicMp3()->m_bNowPlay == FALSE)
			{
				vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
				while(it != m_vecMp3FileNames.end())
				{
					if(m_nCurrentRenderIndex == (*it).nIndex)
					{
						if(it != m_vecMp3FileNames.end())
						{
													
							Play_Mp3Music();
							//m_nCurrentRenderIndex = (*it).nIndex;	
							break;
						}						
					}
					it++;
				}
				
			}
		}
		break;
	}	
}

int CINFMp3Player::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFMp3Player::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	if(m_pScrollVolum && m_pScroll)
	{
		// 볼륨저장
		if(m_pScrollVolum->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		{
			g_pInterface->SaveOptionFile();
			return INF_MSGPROC_BREAK;
		}
		// 스크롤 관련
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
			
			// 미니 사이즈 일때는 브레이크 
			if(m_bBaseSizeFull == FALSE)
				break;				
			
			for(int i=0; i<MP3PLAYER_BUTTON_MAIN_STATE; i++)
				m_nButtonStateMain[i] = MP3PLAYER_BUTTON_STATE_NOR;
			//////////////////////////////////////////////////////////
			// 버튼 관련
			if( pt.y>(MP3PLAYER_BASE_POS_Y)
				&& pt.y<(MP3PLAYER_BASE_POS_Y+MP3PLAYER_BUTTON_SIZE_H))
			{
				if( pt.x>(MP3PLAYER_BASE_POS_X+51)
					&& pt.x<(MP3PLAYER_BASE_POS_X+51+MP3PLAYER_BUTTON_SIZE_W))
				{	// 뒤로
					m_nButtonStateMain[MP3PLAYER_BUTTON_PRVE] = MP3PLAYER_BUTTON_STATE_OVE;					
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+67)
					&& pt.x<(MP3PLAYER_BASE_POS_X+67+MP3PLAYER_BUTTON_SIZE_W))
				{	// 재생
					m_nButtonStateMain[MP3PLAYER_BUTTON_PLAY] = MP3PLAYER_BUTTON_STATE_OVE;					
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+81)
					&& pt.x<(MP3PLAYER_BASE_POS_X+81+MP3PLAYER_BUTTON_SIZE_W))
				{	// 앞으로
					m_nButtonStateMain[MP3PLAYER_BUTTON_NEXT] = MP3PLAYER_BUTTON_STATE_OVE;					
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+95)
					&& pt.x<(MP3PLAYER_BASE_POS_X+95+MP3PLAYER_BUTTON_SIZE_W))
				{	// 정지
					m_nButtonStateMain[MP3PLAYER_BUTTON_STOP] = MP3PLAYER_BUTTON_STATE_OVE;					
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+225)
					&& pt.x<(MP3PLAYER_BASE_POS_X+225+MP3PLAYER_BUTTON_SIZE_W))
				{	// 플레이 리스트
					m_nButtonStateMain[MP3PLAYER_BUTTON_FULL] = MP3PLAYER_BUTTON_STATE_OVE;					
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+238)
					&& pt.x<(MP3PLAYER_BASE_POS_X+238+MP3PLAYER_BUTTON_SIZE_W))
				{	// 풀모드
					m_nButtonStateMain[MP3PLAYER_BUTTON_MINI] = MP3PLAYER_BUTTON_STATE_OVE;					
				}
			}

			// 리스트 박스 안
			if(m_bMp3PlayListShow == TRUE)
			{
				if( pt.y>(MP3PLAYER_BASE_POS_Y-132)
					&& pt.y<(MP3PLAYER_BASE_POS_Y+2))
				{
					if( pt.x>(MP3PLAYER_BASE_POS_X-1)
						&& pt.x<(MP3PLAYER_BASE_POS_X+233))
					{
						return INF_MSGPROC_BREAK;
					}
				}
			}

			//
			/////////////////////////////////////////////////////////
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// 2005-10-05 by ispark
			// 정지시에만 사용하도록 수정
//			if(g_pD3dApp->m_bCharacter == FALSE && (g_pShuttleChild->m_bUnitStop == FALSE && g_pShuttleChild->m_bLandedMove == FALSE))
			if(!g_pShuttleChild->GetIsUseInterface())
			{
				break;
			}

			// 미니 사이즈 일때는 브레이크 
			if(m_bBaseSizeFull == FALSE)
			{
				if( pt.y>(MP3PLAYER_BASE_POS_Y)
					&& pt.y<(MP3PLAYER_BASE_POS_Y+MP3PLAYER_BUTTON_SIZE_H))
				{
					if( pt.x>(MP3PLAYER_BASE_POS_X+200)
						&& pt.x<MP3PLAYER_BASE_POS_X+247)
					{	// 풀사이즈
						m_bBaseSizeFull = TRUE;
						return INF_MSGPROC_BREAK;
					}
				}
			}			
			
			for(int i=0; i<MP3PLAYER_BUTTON_MAIN_STATE; i++)
				m_bButtonStateMain[i] = FALSE;
			//////////////////////////////////////////////////////////
			// 버튼 관련
			if( pt.y>(MP3PLAYER_BASE_POS_Y)
			 && pt.y<(MP3PLAYER_BASE_POS_Y+MP3PLAYER_BUTTON_SIZE_H))
			{
				if( pt.x>(MP3PLAYER_BASE_POS_X+51)
					&& pt.x<(MP3PLAYER_BASE_POS_X+51+MP3PLAYER_BUTTON_SIZE_W))
				{	// 뒤로					
					m_nButtonStateMain[MP3PLAYER_BUTTON_PRVE] = MP3PLAYER_BUTTON_STATE_PUH;
					m_bButtonStateMain[MP3PLAYER_BUTTON_PRVE] = TRUE;
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+67)
					&& pt.x<(MP3PLAYER_BASE_POS_X+67+MP3PLAYER_BUTTON_SIZE_W))
				{	// 재생
					m_nButtonStateMain[MP3PLAYER_BUTTON_PLAY] = MP3PLAYER_BUTTON_STATE_PUH;
					m_bButtonStateMain[MP3PLAYER_BUTTON_PLAY] = TRUE;
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+81)
					&& pt.x<(MP3PLAYER_BASE_POS_X+81+MP3PLAYER_BUTTON_SIZE_W))
				{	// 앞으로
					m_nButtonStateMain[MP3PLAYER_BUTTON_NEXT] = MP3PLAYER_BUTTON_STATE_PUH;
					m_bButtonStateMain[MP3PLAYER_BUTTON_NEXT] = TRUE;
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+95)
					&& pt.x<(MP3PLAYER_BASE_POS_X+95+MP3PLAYER_BUTTON_SIZE_W))
				{	// 정지
					m_nButtonStateMain[MP3PLAYER_BUTTON_STOP] = MP3PLAYER_BUTTON_STATE_PUH;
					m_bButtonStateMain[MP3PLAYER_BUTTON_STOP] = TRUE;
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+225)
					&& pt.x<(MP3PLAYER_BASE_POS_X+225+MP3PLAYER_BUTTON_SIZE_W))
				{	// 플레이 리스트
					m_nButtonStateMain[MP3PLAYER_BUTTON_FULL] = MP3PLAYER_BUTTON_STATE_PUH;
					m_bButtonStateMain[MP3PLAYER_BUTTON_FULL] = TRUE;
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+238)
					&& pt.x<(MP3PLAYER_BASE_POS_X+238+MP3PLAYER_BUTTON_SIZE_W))
				{	// 풀모드
					m_nButtonStateMain[MP3PLAYER_BUTTON_MINI] = MP3PLAYER_BUTTON_STATE_PUH;
					m_bButtonStateMain[MP3PLAYER_BUTTON_MINI] = TRUE;
					return INF_MSGPROC_BREAK;
				}
				else if(pt.x>(MP3PLAYER_BASE_POS_X)
					&& pt.x<(MP3PLAYER_BASE_POS_X+43)
					&& TRUE == m_bSetMp3Dir)
				{// 디렉토리 가져오기					
					g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_ETC_0002,
								_Q_MP3_DIRECTORY);
				}
			}
			
			// 리스트 박스 안
			if(m_bMp3PlayListShow == TRUE)
			{
				// 탭
				if( pt.y>(MP3PLAYER_BASE_POS_Y-19)
					&& pt.y<(MP3PLAYER_BASE_POS_Y-2))
				{
					for(int i=0; i<MP3PLAYER_BASE_TAB; i++)
					{
						if( pt.x>(MP3PLAYER_BASE_POS_X-1-(i*MP3PLAYER_TAB_WIDTH))
							&& pt.x<(MP3PLAYER_BASE_POS_X+MP3PLAYER_TAB_WIDTH+(i*MP3PLAYER_TAB_WIDTH)))
						{
							m_nSelectTab = i;
							if(m_nSelectTab == MP3PLAYER_TAB_RANDOM)
							{
								RandomPlayList();
							}
							g_pInterface->SetWindowOrder(WNDMp3Player);
							return INF_MSGPROC_BREAK;
						}
					}
				}

				// 리스트
				if( pt.y>(MP3PLAYER_BASE_POS_Y-132)
					&& pt.y<(MP3PLAYER_BASE_POS_Y+2))
				{
					if( pt.x>(MP3PLAYER_BASE_POS_X-1)
						&& pt.x<(MP3PLAYER_BASE_POS_X+233))
					{
						// 2008-03-04 by dgwoo 배경음악 버그 수정.
						for(int i = 0 ; i < MP3PLAYER_MAX_LIST ; i++)
						{
							if((MP3PLAYER_BASE_POS_Y - 130 + (i*MP3PLAYER_LINE_GAB)) < pt.y
								&& (MP3PLAYER_BASE_POS_Y-130+(i*MP3PLAYER_LINE_GAB) + MP3PLAYER_LINE_GAB) > pt.y)
							{
								if(m_vecMp3FileNames.size()>m_pScroll->GetCurrentScrollIndex()+i)
									m_nCurrentRenderSelect = m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].nIndex;
							}
						}
						g_pInterface->SetWindowOrder(WNDMp3Player);
						return INF_MSGPROC_BREAK;
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
			
			// 미니 사이즈 일때는 브레이크 
			if(m_bBaseSizeFull == FALSE)
				break;
			
			//////////////////////////////////////////////////////////
			// 버튼 관련
			if( pt.y>(MP3PLAYER_BASE_POS_Y)
			 && pt.y<(MP3PLAYER_BASE_POS_Y+MP3PLAYER_BUTTON_SIZE_H))
			{
				if( pt.x>(MP3PLAYER_BASE_POS_X+51)
					&& pt.x<(MP3PLAYER_BASE_POS_X+51+MP3PLAYER_BUTTON_SIZE_W))
				{	// 뒤로
					if(m_bButtonStateMain[MP3PLAYER_BUTTON_PRVE] == TRUE)
					{
						//
						if(m_vecMp3FileNames.size() <= 0)
							break;
						m_LnMutePos = 0;
						m_bPlay_Mute = TRUE;
						if(m_nCurrentRenderIndex <= m_vecMp3FileNames[0].nIndex)
						{
							m_nCurrentRenderIndex = m_vecMp3FileNames[m_vecMp3FileNames.size()-1].nIndex;
							Play_Mp3Music();
							break;
						}
						
						BOOL bFalse = FALSE;
						vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
						while(it != m_vecMp3FileNames.end())
						{
							if(m_nCurrentRenderIndex == (*it).nIndex)
							{
								it--;
								m_nCurrentRenderIndex = (*it).nIndex;
								bFalse = TRUE;
								break;
							}
							
							it++;
						}
						if(FALSE == bFalse)
						{
							m_nCurrentRenderIndex = m_vecMp3FileNames[m_vecMp3FileNames.size()-1].nIndex;
						}
						Play_Mp3Music();

					}
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+67)
					&& pt.x<(MP3PLAYER_BASE_POS_X+67+MP3PLAYER_BUTTON_SIZE_W))
				{	// 재생, 멈춤.
					if(m_bButtonStateMain[MP3PLAYER_BUTTON_PLAY] == TRUE)
					{
						if(m_vecMp3FileNames.size() <= 0)
						{
							g_pD3dApp->m_pSound->m_bPlayMusic = FALSE;
							m_bStop_Flag = FALSE;
							break;
						}
						if(m_bStop_Flag)
						{// 정지 => 재생 일경우 선택된 음악을 재생시킨다.
							m_nCurrentRenderIndex = m_nCurrentRenderSelect;
							Play_Mp3Music();
							m_bStop_Flag = FALSE;
							break;
						}

						if(m_bPlay_Mute)
						{// 멈춤.
							if(m_bOriBGSound)
							{
								Play_Mp3Music();
								m_bOriBGSound = FALSE;
							}
							else
							{
								g_pD3dApp->m_pSound->GetMusicMp3()->Atum_MusicStop();
								m_LnMutePos = g_pD3dApp->m_pSound->GetMusicMp3()->m_pLPos;
								m_bPlay_Mute = FALSE;
							}
						}
						else
						{// 재생.
							if(m_LnMutePos != 0)
							{
								Play_Mp3Music(TRUE);
								m_bPlay_Mute = 0;
							}
							else
							{
								Play_Mp3Music();
							}

//							if(m_vecMp3FileNames.size() <= 0)
//							{//
//								g_pD3dApp->m_pSound->GetMusicMp3()->Atum_MusicStop();
//								m_LnMutePos = g_pD3dApp->m_pSound->GetMusicMp3()->m_pLPos;
//								m_bStop_Flag = FALSE;
//								break;
//							}
//							else
//							{// mp3파일 리스트가 있을경우.
//								m_nCurrentRenderIndex = m_nCurrentRenderSelect;
//								Play_Mp3Music();
//								m_bStop_Flag = FALSE;
//								break;
//							}
							m_bPlay_Mute = TRUE;
						}
						

//						if(m_bStop_Flag == FALSE)
//						{
//							m_nCurrentRenderIndex = m_nCurrentRenderSelect;
//							Play_Mp3Music();
//							m_bStop_Flag = FALSE;
//							break;
//						}
//						if(m_bPlay_Mute)
//						{
//							g_pD3dApp->m_pSound->GetMusicMp3()->Atum_MusicStop();
//							m_LnMutePos = g_pD3dApp->m_pSound->GetMusicMp3()->m_pLPos;
//							m_bPlay_Mute = FALSE;
//						}
//						else
//						{
//							if(m_LnMutePos != 0)
//							{
//								Play_Mp3Music(TRUE);
//								m_bPlay_Mute = 0;
//							}
//							else
//							{
//								Play_Mp3Music();
//							}
//							
//							m_bPlay_Mute = TRUE;
//						}
						
					}
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+81)
					&& pt.x<(MP3PLAYER_BASE_POS_X+81+MP3PLAYER_BUTTON_SIZE_W))
				{	// 앞으로
					if(m_bButtonStateMain[MP3PLAYER_BUTTON_NEXT] == TRUE)
					{
						if(m_vecMp3FileNames.size() <= 0)
							break;
						m_LnMutePos = 0;
						m_bPlay_Mute = TRUE;
						if(m_vecMp3FileNames.size()-1 <= m_nCurrentRenderIndex)
						{
							m_nCurrentRenderIndex = m_vecMp3FileNames[0].nIndex;
							Play_Mp3Music();
							break;
						}
						
						vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
						while(it != m_vecMp3FileNames.end())
						{
							if(m_nCurrentRenderIndex == (*it).nIndex)
							{
								it++;
								m_nCurrentRenderIndex = (*it).nIndex;								
								break;
							}
							
							it++;
						}
						
						Play_Mp3Music();
					}
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+95)
					&& pt.x<(MP3PLAYER_BASE_POS_X+95+MP3PLAYER_BUTTON_SIZE_W))
				{	// 정지
					if(m_bButtonStateMain[MP3PLAYER_BUTTON_STOP] == TRUE)
					{
						g_pD3dApp->m_pSound->GetMusicMp3()->Atum_MusicStop();
						m_bMp3Play = FALSE;
						m_bStop_Flag = TRUE;
						m_bOriBGSound = FALSE;
					}
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+225)
					&& pt.x<(MP3PLAYER_BASE_POS_X+225+MP3PLAYER_BUTTON_SIZE_W))
				{	// 플레이 리스트
					if(m_bButtonStateMain[MP3PLAYER_BUTTON_FULL] == TRUE)
					{
						m_bMp3PlayListShow = !m_bMp3PlayListShow;
						// 리스트 활성이 되면 누르면 자동으로 창 우선 순위에 넣어서 상위에 찍도록 한다.
						if(m_bMp3PlayListShow == TRUE)
							g_pInterface->SetWindowOrder(WNDMp3Player);
					}
				}
				else if( pt.x>(MP3PLAYER_BASE_POS_X+238)
					&& pt.x<(MP3PLAYER_BASE_POS_X+238+MP3PLAYER_BUTTON_SIZE_W))
				{	// 풀모드
					if(m_bButtonStateMain[MP3PLAYER_BUTTON_MINI] == TRUE)
					{
						m_bBaseSizeFull = !m_bBaseSizeFull;
						if(m_bBaseSizeFull == FALSE)
							m_bMp3PlayListShow = FALSE;
					}
				}
			}
			
			for(int i=0; i<MP3PLAYER_BUTTON_MAIN_STATE; i++)
			{	// 초기화
				m_nButtonStateMain[i] = MP3PLAYER_BUTTON_STATE_NOR;
				m_bButtonStateMain[i] = FALSE;
			}
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// 리스트 박스 안(재생음악 선택)
			if(m_bMp3PlayListShow == TRUE)
			{
				if( pt.y>(MP3PLAYER_BASE_POS_Y-132)
					&& pt.y<(MP3PLAYER_BASE_POS_Y+2))
				{
					if( pt.x>(MP3PLAYER_BASE_POS_X-1)
						&& pt.x<(MP3PLAYER_BASE_POS_X+233))
					{
						int nTemp=0;
						for(int i=0; i<MP3PLAYER_MAX_LIST+1; i++)
						{							
							if((MP3PLAYER_BASE_POS_Y-130+nTemp)<pt.y 
							&& (MP3PLAYER_BASE_POS_Y-130+nTemp+MP3PLAYER_LINE_GAB)>pt.y)
							{
								if(m_vecMp3FileNames.size()>m_pScroll->GetCurrentScrollIndex()+i-1)
									m_nCurrentRenderIndex = m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i-1].nIndex;
								Play_Mp3Music();
							}

							nTemp = (i*MP3PLAYER_LINE_GAB);
						}
						return INF_MSGPROC_BREAK;
					}
				}
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_DELETE)
			{
				if(m_bMp3PlayListShow == TRUE)
				{
					g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_ETC_0003,//"선택하신 곡을 플레이 리스트에서 삭제하시겠습니까?"
						_Q_MP3_PLAYLIST_DEL);
					return INF_MSGPROC_BREAK;					
				}
			}
		}
	}
	return INF_MSGPROC_NORMAL;
}

void CINFMp3Player::RenderButtonState()
{
	// 버튼 상태 렌더링
	m_pImgPrvButton[m_nButtonStateMain[MP3PLAYER_BUTTON_PRVE]]->Move(MP3PLAYER_BASE_POS_X+51,MP3PLAYER_BASE_POS_Y);
	m_pImgPrvButton[m_nButtonStateMain[MP3PLAYER_BUTTON_PRVE]]->Render();
	m_pImgPlayButton[m_nButtonStateMain[MP3PLAYER_BUTTON_PLAY]]->Move(MP3PLAYER_BASE_POS_X+67,MP3PLAYER_BASE_POS_Y);
	m_pImgPlayButton[m_nButtonStateMain[MP3PLAYER_BUTTON_PLAY]]->Render();
	m_pImgNextButton[m_nButtonStateMain[MP3PLAYER_BUTTON_NEXT]]->Move(MP3PLAYER_BASE_POS_X+81,MP3PLAYER_BASE_POS_Y);
	m_pImgNextButton[m_nButtonStateMain[MP3PLAYER_BUTTON_NEXT]]->Render();
	m_pImgStopButton[m_nButtonStateMain[MP3PLAYER_BUTTON_STOP]]->Move(MP3PLAYER_BASE_POS_X+95,MP3PLAYER_BASE_POS_Y);
	m_pImgStopButton[m_nButtonStateMain[MP3PLAYER_BUTTON_STOP]]->Render();
	
	if(m_bMp3PlayListShow == FALSE)
	{
		m_pImgShowListButton[m_nButtonStateMain[MP3PLAYER_BUTTON_FULL]]->Move(MP3PLAYER_BASE_POS_X+225,MP3PLAYER_BASE_POS_Y);
		m_pImgShowListButton[m_nButtonStateMain[MP3PLAYER_BUTTON_FULL]]->Render();
	}
	else
	{
		m_pImgHidenButton[m_nButtonStateMain[MP3PLAYER_BUTTON_FULL]]->Move(MP3PLAYER_BASE_POS_X+225,MP3PLAYER_BASE_POS_Y);
		m_pImgHidenButton[m_nButtonStateMain[MP3PLAYER_BUTTON_FULL]]->Render();
	}
	m_pImgMiniButton[m_nButtonStateMain[MP3PLAYER_BUTTON_MINI]]->Move(MP3PLAYER_BASE_POS_X+238,MP3PLAYER_BASE_POS_Y);
	m_pImgMiniButton[m_nButtonStateMain[MP3PLAYER_BUTTON_MINI]]->Render();
}

void CINFMp3Player::FindMp3File()
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	char fname[MAX_PATH];
	BOOL bResult=TRUE;
	char Path[MAX_PATH];
	int  nCnt=0;
	Mp3File_t tempMp3Name;

	// 2006-09-15 by ispark
	if(g_pD3dApp->m_pSound->GetMusicMp3() == NULL)
	{
		return;
	}

	g_pD3dApp->m_pSound->GetMusicMp3()->Atum_MusicStop();
	m_vecMp3FileNames.clear();
	if(strlen(m_strDirectory)>0)
	{
		memset(Path, 0x00, MAX_PATH);
		strncpy(Path, m_strDirectory, strlen(m_strDirectory));
	}
	else
	{
		GetCurrentDirectory( MAX_PATH, Path );
		strcat(Path, "\\Music\\*.mp3");
		strncpy(m_strDirectory,Path, strlen(Path));
	}

	hSrch = FindFirstFile(Path, &wfd);
	if(hSrch == INVALID_HANDLE_VALUE)
	{
		DBGOUT("FindFirstFile : INVALID_HANDLE_VALUE = %d\n",GetLastError());
		FindClose(hSrch);
		return ;
	}
	while(bResult)
	{
		memset(&tempMp3Name, 0x00, sizeof(Mp3File_t));
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			wsprintf(fname, "[ %s ]", wfd.cFileName);
		}
		else
		{
			wsprintf(fname, "%s", wfd.cFileName);
			tempMp3Name.nIndex = nCnt;
			strncpy(tempMp3Name.szFileNameString, fname, strlen(fname));
			m_vecMp3FileNames.push_back(tempMp3Name);
		}
		nCnt++;
		bResult = FindNextFile(hSrch, &wfd);
	}
	m_pScroll->SetNumberOfData( m_vecMp3FileNames.size() );
	m_nCurrentRenderIndex = 0;
	m_nCurrentRenderSelect = 0;
	FindClose(hSrch);

	vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
	while(it != m_vecMp3FileNames.end())
	{
		DBGOUT("MP3 File : %s\n", (*it).szFileNameString);
		it++;
	}
}

void CINFMp3Player::RenderPlayListBox()
{
	m_pImgListBox->Move(MP3PLAYER_BASE_POS_X-1, MP3PLAYER_BASE_POS_Y-149);
	m_pImgListBox->Render();
	
	// 탭 표시
	m_pImgTab[m_nSelectTab]->Move(MP3PLAYER_BASE_POS_X-1, MP3PLAYER_BASE_POS_Y-19);
	m_pImgTab[m_nSelectTab]->Render();
	
	int nLineGab = 0;
	for(int i=0; i<MP3PLAYER_MAX_LIST; i++)
	{
		if(m_vecMp3FileNames.size() > m_pScroll->GetCurrentScrollIndex() +i)
		{			
			// 선택 표시
			if(m_nCurrentRenderSelect == m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].nIndex)
			{
				m_pImgSelectMp3->Move(MP3PLAYER_BASE_POS_X+5, MP3PLAYER_BASE_POS_Y-130+nLineGab);
				m_pImgSelectMp3->Render();
			}
			if(strlen(m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].szFileNameString)>37)
			{
				FileNameCull(m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].szFileNameString);
			}
			else
			{
				memset(m_strMp3Name, 0x00, MAX_PATH);
				strncpy(m_strMp3Name, m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].szFileNameString, strlen(m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].szFileNameString));
			}
			// 곡명 표시
			if(m_nCurrentRenderIndex == m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].nIndex)
			{
				if(m_nCurrentRenderSelect == m_vecMp3FileNames[m_pScroll->GetCurrentScrollIndex()+i].nIndex)
				{					
					m_pFontTitle[i]->DrawText(MP3PLAYER_BASE_POS_X+5, MP3PLAYER_BASE_POS_Y-MP3PLAYER_BASE_POS_MINUS+nLineGab, GUI_FONT_COLOR_G,
						m_strMp3Name);
				}
				else
				{
					m_pFontTitle[i]->DrawText(MP3PLAYER_BASE_POS_X+5, MP3PLAYER_BASE_POS_Y-MP3PLAYER_BASE_POS_MINUS+nLineGab, GUI_FONT_COLOR_YM,
						m_strMp3Name);
				}
			}
			else
				m_pFontTitle[i]->DrawText(MP3PLAYER_BASE_POS_X+5, MP3PLAYER_BASE_POS_Y-MP3PLAYER_BASE_POS_MINUS+nLineGab, GUI_SELECT_FONT_COLOR,
					m_strMp3Name);		
			
			nLineGab += MP3PLAYER_LINE_GAB;			
		}
	}

//	vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
//	while(it != m_vecMp3FileNames.end())
//	{
//		if(nBreakCnt>MP3PLAYER_MAX_LIST)
//			break;
//		it++;
//		nBreakCnt++;
//	}
}

void CINFMp3Player::DeleteSelectPlayList()
{
	vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
	while(it != m_vecMp3FileNames.end())
	{
		if(m_nCurrentRenderSelect == (*it).nIndex)
		{
			it = m_vecMp3FileNames.erase(it);
			continue;
		}
		
		it++;
	}	
}

void CINFMp3Player::Play_Mp3Music(BOOL bMute)
{
	char buffDir[1024];
	memset(buffDir, 0x00, 1024);
	
	g_pD3dApp->m_pSound->SetDefaultMusicLoop(FALSE);
	vector<Mp3File_t>::iterator it = m_vecMp3FileNames.begin();
	while(it != m_vecMp3FileNames.end())
	{
		if(m_nCurrentRenderIndex == (*it).nIndex)
		{
			// 폴더 뒤에붙은 (*.mp3) 삭제 
			strncpy(buffDir, m_strDirectory, strlen(m_strDirectory)-5);
			strcat(buffDir, (*it).szFileNameString);
			
			break;
		}
		
		it++;
	}	
	g_pD3dApp->m_pSound->GetMusicMp3()->Atum_MusicStop();
	if(buffDir != NULL)	
		g_pD3dApp->m_pSound->GetMusicMp3()->Atum_MusicInit(buffDir);
	// 2006-03-22 by ispark
	int nVolume = GetMusicVolume(g_pSOption->sMusicVolume);
//	g_pD3dApp->m_pSound->GetMusicMp3()->Atum_PlayMP3(g_pSOption->sMusicVolume);
	g_pD3dApp->m_pSound->GetMusicMp3()->Atum_PlayMP3(nVolume);
	if(g_pD3dApp->m_pSound->m_bPlayMusic && g_pD3dApp->m_pSound->GetMusicMp3())
	{
		if(bMute)
			g_pD3dApp->m_pSound->GetMusicMp3()->Atum_LoopMusic(m_LnMutePos);
		else
			g_pD3dApp->m_pSound->GetMusicMp3()->Atum_LoopMusic();
	}
	g_pD3dApp->m_pSound->m_bPlayMusic = TRUE;
	g_pD3dApp->m_pSound->GetMusicMp3()->m_bNowPlay = TRUE;
	m_bMp3Play = TRUE;
	m_bOriBGSound = FALSE;
}

void CINFMp3Player::FileNameCull(char *strName)
{
	vector<string> vecTemp;
	StringCullingUserData(strName, 35, &vecTemp);	// 전체 스트링 절단내기
	if(vecTemp.size()>0)
	{
		char buff[MAX_PATH];
		memset(buff, 0x00, MAX_PATH);
		
		strncpy(buff, vecTemp[0].c_str(), strlen(vecTemp[0].c_str()));
		strcat(buff, "..");
		memset(m_strMp3Name, 0x00, MAX_PATH);
		strncpy(m_strMp3Name, buff, strlen(buff));
	}
}

void CINFMp3Player::RandomPlayList()
{
	m_vecRandom.clear();
	int nNameSize = m_vecMp3FileNames.size();
	if(nNameSize <= 1)
		return;
	BOOL nLoop = TRUE;
	BOOL bFush = FALSE;

	int nVelRate = ((int)rand())%nNameSize;
	m_vecRandom.push_back(nVelRate);
	
	while(nLoop)
	{
		bFush = FALSE;
		nVelRate = ((int)rand())%nNameSize;
		vector<int>::iterator it = m_vecRandom.begin();
		while(it != m_vecRandom.end())
		{
			if(*it == nVelRate)
			{
				bFush = TRUE;
			}
			it++;
		}
		
		if(bFush == FALSE)
		{
			m_vecRandom.push_back(nVelRate);
			if(m_vecRandom.size() == nNameSize)
				nLoop = FALSE;
		}
	}	
}