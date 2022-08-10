// INFOptionSystem.cpp: implementation of the CINFOptionSystem class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "INFSystem.h"
#include "AtumApplication.h"
#include "INFGameMain.h"
#include "INFWindow.h"
#include "D3DHanFont.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "AtumSound.h"
#include "Camera.h"
#include "Interface.h"
#include "FieldWinSocket.h"
#include "D3DHanFont.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "Chat.h"
#include "dxutil.h"
#include "StoreData.h"
#include "FxSystem.h"
#include "INFImageBtn.h"
#include "INFImageRadioBtn.h"
#include "D3DHanFont.h"
#include "INFListBox.h"
#include "INFGameMainChat.h"
#include "INFGameMainWisperChat.h"
#include "INFTarget.h"	// 2009-03-04 by bhsohn 메뉴창 띠울시, 마우스 없어질수 있는 문제 수정

#include "INFOptionSystem.h"
#include "CustomOptimizer.h"

// 2011-07-06 by shcho, hsson 아레나 게임 진입 시 캐릭터 선택 못하게 수정
#include "../InterfaceLib/main/INFGameArena.h"
// end 2011-07-06 by shcho, hsson 아레나 게임 진입 시 캐릭터 선택 못하게 수정

//ydkim. 04.07.02
#define END_GAME_TIMING_ATTACK		5000			// 게임도중 로그오프 게임종료 타이밍 


// 버튼관련 이벤트 
#define	OPTIONSYS_LOGOFF_BTN		0				// 로그오프
#define	OPTIONSYS_GAMEEND_BTN		1				// 게임종료
#define	OPTIONSYS_INITSETUP_BTN		2				// 초기화버튼

#define MIN_QUALITY_RENDER_TERRAIN		3
#define MIN_QUALITY_RENDER				0

// 옵션초기화 값
#define OPTION_DEFAULT_HIGH_TERRAINEFFECTRENDER			9
#define OPTION_DEFAULT_HIGH_TERRAINRENDER				9
#define OPTION_DEFAULT_HIGH_SHOWSHADOW					0
#define OPTION_DEFAULT_HIGH_OBJECTVIEW					9
#define OPTION_DEFAULT_HIGH_UNITDETAIL					9
#define OPTION_DEFAULT_HIGH_CONTRAST					0
#define OPTION_DEFAULT_HIGH_FILTER						0

#define OPTION_DEFAULT_MIDDLE_TERRAINEFFECTRENDER		7
#define OPTION_DEFAULT_MIDDLE_TERRAINRENDER				4
#define OPTION_DEFAULT_MIDDLE_SHOWSHADOW				0
#define OPTION_DEFAULT_MIDDLE_OBJECTVIEW				4
#define OPTION_DEFAULT_MIDDLE_UNITDETAIL				4
#define OPTION_DEFAULT_MIDDLE_CONTRAST					0
#define OPTION_DEFAULT_MIDDLE_FILTER					0

#define OPTION_DEFAULT_LOW_TERRAINEFFECTRENDER			0
#define OPTION_DEFAULT_LOW_TERRAINRENDER				0
#define OPTION_DEFAULT_LOW_SHOWSHADOW					0
#define OPTION_DEFAULT_LOW_OBJECTVIEW					0
#define OPTION_DEFAULT_LOW_UNITDETAIL					0
#define OPTION_DEFAULT_LOW_CONTRAST						0
#define OPTION_DEFAULT_LOW_FILTER						0

#define MODE_CAMERA_TYPE_FPS		1
#define MODE_CAMERA_TYPE_NORMAL		0

////////////// UI좌표
// 적용
#define OPTION_BTN_APP_X			81
#define OPTION_BTN_APP_Y			648
// 초기화
#define OPTION_BTN_INIT_X			160
#define OPTION_BTN_INIT_Y			648
// 로그오프
#define OPTION_BTN_LOGOFF_X			239
#define OPTION_BTN_LOGOFF_Y			648
// 게임종료
#define OPTION_BTN_GAMEEND_X			318
#define OPTION_BTN_GAMEEND_Y			648

// 라디오 버튼
#define OPTION_RADIO_GAME_INFO_X		306
#define OPTION_RADIO_GAME_INFO_Y		51
#define OPTION_RADIO_GAME_INFO_CAP_X	70
#define OPTION_RADIO_GAME_INFO_CAP_Y	16

// 해상도
#define OPTION_HAESANG_X	410 
#define OPTION_HAESANG_Y	284

// 최소 프레임
#define OPTION_RADIO_SMALLFRM_X		304
#define OPTION_RADIO_SMALLFRM_Y		413

// 닫기 버튼
#define OPTION_BTN_CLOSE_X			428
#define OPTION_BTN_CLOSE_Y			9

//////////////////////// 콤보박스 위치////////////////////////
#define OPTION_COMBO_MAIN_WIDTH			70
#define OPTION_COMBO_MAIN_HEIGHT		17
#define OPTION_COMBO_ELE_WIDTH			70
#define OPTION_COMBO_ELE_HEIGHT			13

// 시야거리
#define OPTION_COMBO_SEE_RANGE_X		307 
#define OPTION_COMBO_SEE_RANGE_Y		303
// 유닛디테일
#define OPTION_COMBO_UNIT_DETAIL_X		307 
#define OPTION_COMBO_UNIT_DETAIL_Y		319
// 그림자조절
#define OPTION_COMBO_SHADOW_X			307 
#define OPTION_COMBO_SHADOW_Y			335
// 이펙트 조절
#define OPTION_COMBO_EFFECT_X			307 
#define OPTION_COMBO_EFFECT_Y			351
// 감마 조절
#define OPTION_COMBO_GAMMA_X			307 
#define OPTION_COMBO_GAMMA_Y			367
// 대비 조절
#define OPTION_COMBO_CONTRAST_X			307 
#define OPTION_COMBO_CONTRAST_Y			383
// 필터효과
#define OPTION_COMBO_FILTER_X			307 
#define OPTION_COMBO_FILTER_Y			399
// 시점변환
#define OPTION_COMBO_SEE_CHANGE_X		307 
#define OPTION_COMBO_SEE_CHANGE_Y		460
// 효과음 볼륨
#define OPTION_COMBO_MUSIC_VOL_X		307 
#define OPTION_COMBO_MUSIC_VOL_Y		478

//////////////////////// ETC 라디오버튼 위치////////////////////////
// 마우스 포인터
#define OPTION_RADIO_MOUSE_X			304
#define OPTION_RADIO_MOUSE_Y			496
//헬프기능
#define OPTION_RADIO_HELPER_X			304
#define OPTION_RADIO_HELPER_Y			514
// 오퍼레이터 기능
#define OPTION_RADIO_OPER_X				304
#define OPTION_RADIO_OPER_Y				532
// 자동 수평유지
#define OPTION_RADIO_MAINTAIN_X			304
#define OPTION_RADIO_MAINTAIN_Y			550
// 마우스 상하 반전
#define OPTION_RADIO_REVERSE_TB_X		304
#define OPTION_RADIO_REVERSE_TB_Y		568
// 마우스 좌우 반전
#define OPTION_RADIO_REVERSE_LR_X		304
#define OPTION_RADIO_REVERSE_LR_Y		586
// 메뉴 사용시 유닛정지
#define OPTION_RADIO_MENU_X				304
#define OPTION_RADIO_MENU_Y				604
// Music 플레이어 보기
#define OPTION_RADIO_MP3_X				304
#define OPTION_RADIO_MP3_Y				622

// 2008-11-13 by bhsohn 조이스틱 작업
// 조이스틱 옵션
#define OPTION_JOYSTICK_BTN_X		306
#define OPTION_JOYSTICK_BTN_Y		588
// end 2008-11-13 by bhsohn 조이스틱 작업


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFOptionSystem::CINFOptionSystem(CAtumNode* pParent)
{
	m_pParent = pParent;
	
	m_bRestored = FALSE;
	m_bInvalidated = FALSE;
	memcpy(&m_pSOptionOld, g_pSOption, sizeof(sOPTION_SYSTEM));	
	memcpy(&m_struSOptionCharacterOld, g_pSOptionCharacter, sizeof(sOPTION_CHARACTER));	
	
	m_bQuitGameMessage = FALSE;
	m_bLogOffGameMessage = FALSE;
	m_fTickSecTime = 0.0f;
	m_fLastTickSecTime = 0.0f;
	m_bRenderToolTip = FALSE;	

	m_bShow = FALSE;

	m_pOptionBk = NULL;

	int nCnt = 0;
	for(nCnt = 0;nCnt < MODE_COMBO_NUMBER;nCnt++)
	{
		memset(m_strSelectModeComboData[nCnt], 0x00, MODE_COMBO_STR_LEN);
	}

	m_ptBakPos.x = m_ptBakPos.y = 0;
	m_ptBakSize.x = m_ptBakSize.y = 1;
	m_ptHaesangPos.x = m_ptHaesangPos.y = 0;
	memset(m_szHaesangTxt, 0x00,256);
	

	m_pOptionApp = NULL ;	// 적용
	m_pOptionInit = NULL;	// 초기화
	m_pOptionLogOff = NULL;	// 로그오프
	m_pOptionGameEnd= NULL;	// 로그오프

	// 2008-11-13 by bhsohn 조이스틱 작업
	m_pOptionJoystic = NULL;
	
	m_pFontHaeSang = NULL;

	int nMainId = 0;	
	// 게임옵션
	for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
	{
		for(nCnt = 0;nCnt < MAX_OPTION_SYS_CNT;nCnt++)
		{
			m_pGameOpRadioBtn[nMainId][nCnt] = NULL;
		}
	}

	memset(&m_struOpInfo, 0x00, sizeof(structOptionGameInfo));
	m_struOpInfo = InitOptionGameInfo();


	// 그래픽
	for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
	{
		m_pComboGraphic[nCnt] = NULL;
	}
	
	m_pMiniFrame = NULL;

	for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
	{
		m_pEtcRadio[nCnt] = NULL;
	}
	m_pCloseBtn = NULL;
	
}


CINFOptionSystem::~CINFOptionSystem()
{
	FLOG( "~CINFOptionSystem()" );		
	SAFE_DELETE(m_pOptionBk);	
	SAFE_DELETE(m_pOptionApp);	// 적용
	SAFE_DELETE(m_pOptionInit);	// 초기화
	SAFE_DELETE(m_pOptionLogOff);	// 로그오프
	SAFE_DELETE(m_pOptionGameEnd);	// 로그오프
	// 2008-11-13 by bhsohn 조이스틱 작업
	SAFE_DELETE(m_pOptionJoystic);
	SAFE_DELETE(m_pFontHaeSang);	
	
	int nCnt = 0;
	int nMainId = 0;	
	for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
	{
		for(nCnt = 0;nCnt < MAX_OPTION_SYS_CNT;nCnt++)
		{		
			SAFE_DELETE(m_pGameOpRadioBtn[nMainId][nCnt]);		
		}
	}
	
	for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
	{
		SAFE_DELETE(m_pComboGraphic[nCnt]);
	}	
	SAFE_DELETE(m_pMiniFrame);
	for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
	{
		SAFE_DELETE(m_pEtcRadio[nCnt]);	 
	}
	SAFE_DELETE(m_pCloseBtn );

}


HRESULT CINFOptionSystem::InitDeviceObjects()
{
	FLOG( "CINFOptionSystem::InitDeviceObjects()" );
	DataHeader	* pDataHeader ;
	int nCnt = 0;

	if(NULL == m_pOptionBk)
	{
		m_pOptionBk = new CINFImage;
	}
	pDataHeader = FindResource("optionbk");
	m_pOptionBk->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	

	// 적용
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];				
		wsprintf(szUpBtn, "optionapp3");
		wsprintf(szDownBtn, "optionapp1");
		wsprintf(szSelBtn, "optionapp0");
		wsprintf(szDisBtn, "optionapp2");
		if(NULL == m_pOptionApp)
		{
			m_pOptionApp = new CINFImageBtn;
		}
		m_pOptionApp->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	// 초기화
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];	
		wsprintf(szUpBtn, "optioninit3");
		wsprintf(szDownBtn, "optioninit1");
		wsprintf(szSelBtn, "optioninit0");
		wsprintf(szDisBtn, "optioninit2");		
		if(NULL == m_pOptionInit)
		{
			m_pOptionInit = new CINFImageBtn;
		}
		m_pOptionInit->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	// 로그오프
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];		
				
		wsprintf(szUpBtn, "optionoff3");
		wsprintf(szDownBtn, "optionoff1");
		wsprintf(szSelBtn, "optionoff0");
		wsprintf(szDisBtn, "optionoff2");		

		if(NULL == m_pOptionLogOff)
		{
			m_pOptionLogOff = new CINFImageBtn;
		}
		m_pOptionLogOff->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	
	// 게임종료
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];		
		wsprintf(szUpBtn, "optionend3");
		wsprintf(szDownBtn, "optionend1");
		wsprintf(szSelBtn, "optionend0");
		wsprintf(szDisBtn, "optionend2");
		if(NULL == m_pOptionGameEnd)
		{
			m_pOptionGameEnd = new CINFImageBtn;
		}
		m_pOptionGameEnd->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	// 2008-11-13 by bhsohn 조이스틱 작업	
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];		
		wsprintf(szUpBtn, "op_j3");
		wsprintf(szDownBtn, "op_j1");
		wsprintf(szSelBtn, "op_j0");
		wsprintf(szDisBtn, "op_j2");
		if(NULL == m_pOptionJoystic)
		{
			m_pOptionJoystic = new CINFImageBtn;
		}
		m_pOptionJoystic->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	// end 2008-11-13 by bhsohn 조이스틱 작업

	{	
		if(NULL == m_pFontHaeSang)
		{
			m_pFontHaeSang = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
		}
		m_pFontHaeSang->InitDeviceObjects(g_pD3dDev);
	}

	// 라디오 버튼
	{
		char chRadioOff[30], chRadioOn[30];
		
		wsprintf(chRadioOff, "radio_b");
		wsprintf(chRadioOn, "radio_a");
		
		int nMainId = 0;	
		for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
		{
			for(nCnt = 0;nCnt < MAX_OPTION_SYS_CNT;nCnt++)
			{		
				if(NULL == m_pGameOpRadioBtn[nMainId][nCnt])
				{		
					m_pGameOpRadioBtn[nMainId][nCnt] = new CINFImageRadioBtn;
				}				
				m_pGameOpRadioBtn[nMainId][nCnt]->InitDeviceObjects(chRadioOff, chRadioOn);
			}		
		}		
	}
	// 콤보 버튼
	{
		for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
		{
			if(NULL == m_pComboGraphic[nCnt])
			{
				m_pComboGraphic[nCnt] = new CINFListBox("cbopa","s_combo");				
				m_pComboGraphic[nCnt]->InitDeviceObjects();				
			}			
		}
		
		// 시야거리
		{
			char chTmpBuff[32];
			
			for(nCnt = 0;nCnt < 10;nCnt++)
			{
				sprintf(chTmpBuff, "%d", nCnt);
				m_pComboGraphic[OPTION_GRAPHIC_SEE_RANGE]->AddElement(chTmpBuff);	// 시야거리
				m_pComboGraphic[OPTION_GRAPHIC_UNIT_DETAIL]->AddElement(chTmpBuff);	// 유닛 디테일
				m_pComboGraphic[OPTION_GRAPHIC_SHADOW]->AddElement(chTmpBuff);	// 그림자조절
				m_pComboGraphic[OPTION_GRAPHIC_EFFECT]->AddElement(chTmpBuff);	// 이펙트 조절			
			}
			for(nCnt = 5;nCnt >= -4;nCnt--)
			{
				sprintf(chTmpBuff, "%d", nCnt);			
				m_pComboGraphic[OPTION_GRAPHIC_GAMMA]->AddElement(chTmpBuff);	// 감마 조절
			}
			{
				sprintf(chTmpBuff, "%s", STRMSG_C_INTERFACE_0035);						
				m_pComboGraphic[OPTION_GRAPHIC_CONTRAST]->AddElement(chTmpBuff);	// 대비 조절
				m_pComboGraphic[OPTION_GRAPHIC_FILTER]->AddElement(chTmpBuff);	// 필터 효과
			}
			for(nCnt = 1;nCnt < 10;nCnt++)
			{
				sprintf(chTmpBuff, "%d", nCnt);			
				m_pComboGraphic[OPTION_GRAPHIC_CONTRAST]->AddElement(chTmpBuff);	// 대비 조절
				m_pComboGraphic[OPTION_GRAPHIC_FILTER]->AddElement(chTmpBuff);	// 필터 효과			
			}

			// 시점변환
			sprintf(chTmpBuff, "%s", STRMSG_C_INTERFACE_0002);			//1 인칭
			m_pComboGraphic[OPTION_ETC_SEE_CHANGE]->AddElement(chTmpBuff);	// 시점변환			
			sprintf(chTmpBuff, "%s", STRMSG_C_INTERFACE_0003);			//3 인칭
			m_pComboGraphic[OPTION_ETC_SEE_CHANGE]->AddElement(chTmpBuff);	// 시점변환			
			
			// 볼륨 조절
			for(nCnt = 0;nCnt < 10;nCnt++)
			{
				sprintf(chTmpBuff, "%d", nCnt);
				m_pComboGraphic[OPTION_ETC_VOLUMNE]->AddElement(chTmpBuff);	// 볼륨
			}

			for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
			{
				m_pComboGraphic[nCnt]->UpdateItem();				
			}
		}		

		{
			char chRadioOff[30], chRadioOn[30];
			
			wsprintf(chRadioOff, "radio_17b");
			wsprintf(chRadioOn, "radio_17a");			
			
			if(NULL == m_pMiniFrame)
			{
				m_pMiniFrame = new CINFImageRadioBtn;
			}
			m_pMiniFrame->InitDeviceObjects(chRadioOff, chRadioOn);
		}		
	}

	// ETC라디오 버튼
	{
		char chRadioOff[30], chRadioOn[30];
		
		wsprintf(chRadioOff, "radio_17b");
		wsprintf(chRadioOn, "radio_17a");			
		
		for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
		{		
			if(NULL == m_pEtcRadio[nCnt])
			{		
				m_pEtcRadio[nCnt] = new CINFImageRadioBtn;
			}				
			m_pEtcRadio[nCnt]->InitDeviceObjects(chRadioOff, chRadioOn);
		}
				
	}	
	// 닫기 버튼
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "xclose");
		wsprintf(szDownBtn, "xclose");
		wsprintf(szSelBtn, "xclose");
		wsprintf(szDisBtn, "xclose");
		if(NULL == m_pCloseBtn)
		{
			m_pCloseBtn = new CINFImageBtn;
		}
		m_pCloseBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);
		
	}
	
	// 라디오 버튼 갱신
	UpdateOptionInterface(&m_struOpInfo);

	
	return S_OK ;
}

HRESULT CINFOptionSystem::RestoreDeviceObjects()
{
	FLOG( "CINFOptionSystem::RestoreDeviceObjects()" );
	
	int nCnt = 0;
	// 배경
	if(m_pOptionBk )
	{
		m_pOptionBk->RestoreDeviceObjects();	
		m_ptBakSize = m_pOptionBk->GetImgSize();

		m_ptBakPos.x = (g_pD3dApp->GetBackBufferDesc().Width/2 - m_ptBakSize.x/2);
		m_ptBakPos.y = (g_pD3dApp->GetBackBufferDesc().Height/2 - m_ptBakSize.y/2);

		if(m_ptBakPos.x < 0)
		{
			m_ptBakPos.x = 0;
		}
		if(m_ptBakPos.y < 0)
		{
			m_ptBakPos.y = 0;
		}
	}
	if(m_pOptionApp)
	{
		m_pOptionApp->RestoreDeviceObjects();
	}
	if(m_pOptionInit)
	{
		m_pOptionInit->RestoreDeviceObjects();
	}
	if(m_pOptionLogOff)
	{
		m_pOptionLogOff->RestoreDeviceObjects();
	}
	if(m_pOptionGameEnd)
	{
		m_pOptionGameEnd->RestoreDeviceObjects();
	}
	// 2008-11-13 by bhsohn 조이스틱 작업
	if(m_pOptionJoystic)
	{
		m_pOptionJoystic->RestoreDeviceObjects();
	}
	// end 2008-11-13 by bhsohn 조이스틱 작업

	if(m_pFontHaeSang)
	{
		m_pFontHaeSang->RestoreDeviceObjects();
	}

	{		
		int nMainId = 0;	
		for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
		{
			for(nCnt = 0;nCnt < MAX_OPTION_SYS_CNT;nCnt++)
			{	
				if(m_pGameOpRadioBtn[nMainId][nCnt])
				{
					m_pGameOpRadioBtn[nMainId][nCnt]->RestoreDeviceObjects();			
				}
			}
		}		
	}	
	{
		for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
		{	
			if(m_pComboGraphic[nCnt])
			{
				m_pComboGraphic[nCnt]->RestoreDeviceObjects();			
			}
		}
		
		if(m_pMiniFrame)
		{
			m_pMiniFrame->RestoreDeviceObjects();
		}

		for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
		{
			if(m_pEtcRadio[nCnt])
			{
				m_pEtcRadio[nCnt]->RestoreDeviceObjects();			
			}
		}		
	}
	if(m_pCloseBtn)
	{
		m_pCloseBtn->RestoreDeviceObjects();		
	}

	UpdateBtnPos(m_ptBakPos.x, m_ptBakPos.y);

	m_bRestored = TRUE;
	return S_OK ;
}

HRESULT CINFOptionSystem::DeleteDeviceObjects()
{
	FLOG( "CINFOptionSystem::DeleteDeviceObjects()" );
	
	if(m_pOptionBk)
	{
		m_pOptionBk->DeleteDeviceObjects();
		SAFE_DELETE(m_pOptionBk);
	}
	if(m_pOptionApp)
	{		
		m_pOptionApp->DeleteDeviceObjects();
		SAFE_DELETE(m_pOptionApp);
	}
	if(m_pOptionInit)
	{		
		m_pOptionInit->DeleteDeviceObjects();
		SAFE_DELETE(m_pOptionInit);
	}
	if(m_pOptionLogOff)
	{		
		m_pOptionLogOff->DeleteDeviceObjects();
		SAFE_DELETE(m_pOptionLogOff);
	}
	if(m_pOptionGameEnd)
	{		
		m_pOptionGameEnd->DeleteDeviceObjects();
		SAFE_DELETE(m_pOptionGameEnd);
	}
	// 2008-11-13 by bhsohn 조이스틱 작업
	if(m_pOptionJoystic)
	{
		m_pOptionJoystic->DeleteDeviceObjects();
		SAFE_DELETE(m_pOptionJoystic);
	}
	// end 2008-11-13 by bhsohn 조이스틱 작업
	if(m_pFontHaeSang)
	{
		m_pFontHaeSang->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontHaeSang);
	}

	int nCnt = 0;
	int nMainId = 0;	
	for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
	{
		for(nCnt = 0;nCnt < MAX_OPTION_SYS_CNT;nCnt++)
		{		
			if(m_pGameOpRadioBtn[nMainId][nCnt])
			{
				m_pGameOpRadioBtn[nMainId][nCnt]->DeleteDeviceObjects();	
				SAFE_DELETE(m_pGameOpRadioBtn[nMainId][nCnt]);
			}
		}
	}
	for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
	{			
		if(m_pComboGraphic[nCnt])
		{
			m_pComboGraphic[nCnt]->DeleteDeviceObjects();	
			SAFE_DELETE(m_pComboGraphic[nCnt]);
		}
	}	

	if(m_pMiniFrame)
	{
		m_pMiniFrame->DeleteDeviceObjects();	
		SAFE_DELETE(m_pMiniFrame);		
	}
	for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
	{
		if(m_pEtcRadio[nCnt])
		{
			m_pEtcRadio[nCnt]->DeleteDeviceObjects();	
			SAFE_DELETE(m_pEtcRadio[nCnt]);
		}
	}	

	if(m_pCloseBtn)
	{
		m_pCloseBtn->DeleteDeviceObjects();	
		SAFE_DELETE(m_pCloseBtn);
	}
	

	m_bInvalidated = FALSE;

	return S_OK ;
}


HRESULT CINFOptionSystem::InvalidateDeviceObjects()
{
	FLOG( "CINFOptionSystem::InvalidateDeviceObjects()" );
	
	if(m_pOptionBk )
		m_pOptionBk->InvalidateDeviceObjects();
	if(m_pOptionApp )
		m_pOptionApp->InvalidateDeviceObjects();
	if(m_pOptionInit)
		m_pOptionInit->InvalidateDeviceObjects();
	if(m_pOptionLogOff)
		m_pOptionLogOff->InvalidateDeviceObjects();
	if(m_pOptionGameEnd)
		m_pOptionGameEnd->InvalidateDeviceObjects();
	// 2008-11-13 by bhsohn 조이스틱 작업
	if(m_pOptionJoystic)
	{
		m_pOptionJoystic->InvalidateDeviceObjects();
	}
	// end 2008-11-13 by bhsohn 조이스틱 작업
	if(m_pFontHaeSang)
	{
		m_pFontHaeSang->InvalidateDeviceObjects();
	}
	int nCnt = 0;
	int nMainId = 0;	
	for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
	{
		for(nCnt = 0;nCnt < MAX_OPTION_SYS_CNT;nCnt++)
		{		
			if(m_pGameOpRadioBtn[nMainId][nCnt])
			{
				m_pGameOpRadioBtn[nMainId][nCnt]->InvalidateDeviceObjects();
			}
		}
	}
	for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
	{			
		if(m_pComboGraphic[nCnt])
		{
			m_pComboGraphic[nCnt]->InvalidateDeviceObjects();
		}
	}
		
	if(m_pMiniFrame)
	{
		m_pMiniFrame->InvalidateDeviceObjects();
	}
	for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
	{
		if(m_pEtcRadio[nCnt])
		{
			m_pEtcRadio[nCnt]->InvalidateDeviceObjects();	
		}
	}
	if(m_pCloseBtn)
	{
		m_pCloseBtn->InvalidateDeviceObjects();		
	}
	
	
	m_bRestored = FALSE;
	m_bInvalidated = TRUE;

	return S_OK ;
}


void CINFOptionSystem::Tick()
{
	FLOG( "CINFOptionSystem::Tick()" );
	
	if(TRUE == m_bQuitGameMessage)
	{
		DWORD dwCurTick = timeGetTime();
		if(dwCurTick - m_fLastTickSecTime < END_GAME_TIMING_ATTACK) 
		{
			if(dwCurTick - m_fLastTickSecTime > m_fTickSecTime)
			{
				m_fTickSecTime += 1000.0f;

				int tempTime = ((END_GAME_TIMING_ATTACK-m_fTickSecTime)/1000)+1;
				char message[256];
				
				if(TRUE == m_bLogOffGameMessage)
					wsprintf(message,STRMSG_C_INTERFACE_0036, tempTime);//"로그오프까지 \\r%d초\\r 남았습니다."
				else
					wsprintf(message,STRMSG_C_INTERFACE_0037, tempTime);//"게임종료까지 \\r%d초\\r 남았습니다."

//				g_pD3dApp->m_pChat->CreateChatChild(message,COLOR_SYSTEM);
				g_pGameMain->m_pInfWindow->SetMessageBoxTitleChange(message, _Q_QUIT_MESSAGE);				
			}
		}
		else
		{
			// 2008-10-30 by bhsohn 게임 종료 페이드 아웃시 락시스템 적용
			g_pD3dApp->EnterLock(FALSE);	// FALSE :Lock  TRUE : UnLock	
			// end 2008-10-30 by bhsohn 게임 종료 페이드 아웃시 락시스템 적용

			char message[256]; 
			wsprintf(message,STRMSG_C_INTERFACE_0038); //"종료."
			g_pD3dApp->m_pChat->CreateChatChild(message, COLOR_SYSTEM);
			if(FALSE == m_bLogOffGameMessage)
			{
				g_pD3dApp->m_bClientQuit = TRUE;	// GAME END 메세지 처리후 종료하기 위해 셋팅
				m_bLogOffGameMessage = FALSE;
			}
			
			m_bQuitGameMessage = FALSE;
			m_fTickSecTime = 0.0f;
			m_fLastTickSecTime = 0.0f;

			// 시네마
			if( g_pD3dApp->m_dwGameState == _CITY )
			{
				SendFieldSocketCharacterGameEnd();
			}
			else
			{
				if( g_pShuttleChild->InitCinemaCamera(PATTERN_CAMERA_GAME_END) == TRUE )
				{
					g_pD3dApp->StartFadeEffect(FALSE,1,D3DCOLOR_ARGB(0,0,0,0));
					g_pShuttleChild->m_nEventType = EVENT_GAME_END;
					g_pShuttleChild->ChangeUnitState( _WARP );
					g_pInterface->SaveCharacterFile();				// 2006-09-05 by ispark
				}
			}
			g_pD3dApp->m_pSound->StopD3DSound( SOUND_FLYING_M_A_GEAR );
			g_pD3dApp->m_pSound->StopD3DSound( SOUND_HIGH_BOOSTER );
			g_pD3dApp->m_pSound->StopD3DSound( SOUND_FLYING_B_I_GEAR );
			g_pD3dApp->m_pSound->StopD3DSound( SOUND_LOW_BOOSTER );
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFOptionSystem::OptionQualityCombo()
/// \brief		최소프레임 설정.
/// \author		
/// \date		
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFOptionSystem::OptionQualityCombo()
{
	m_struOpInfo.struSOptionSetup.sLowQuality ^= TRUE;	
	UpdateQuality(&m_struOpInfo.struSOptionSetup);

	// 라디오 버튼 갱신
	UpdateOptionInterface(&m_struOpInfo);

	//g_pInterface->SaveOptionFile();
	
	// 최소 프레임 모드를 키면 리로드한다. 	
	//g_pD3dApp->ReLoadEnemyRenderList();		
	// end 2007-08-29 by bhsohn 최소 프레임시 기본 아머만 로딩하게끔 변경
	return TRUE;
}

void CINFOptionSystem::UpdateQuality(sOPTION_SYSTEM* pOption)
{
	if(pOption->sLowQuality)
	{		
		pOption->sLowQuality				= TRUE;
		pOption->sTerrainRender			= MIN_QUALITY_RENDER;
		pOption->sTerrainEffectRender	= MIN_QUALITY_RENDER;
//		g_pSOption->sObjectViewDistance		= MIN_QUALITY_RENDER;
		pOption->sShadowState			= MIN_QUALITY_RENDER;
		pOption->sUnitDetail				= MIN_QUALITY_RENDER;
		pOption->sContrast				= MIN_QUALITY_RENDER;
		pOption->sFilter					= MIN_QUALITY_RENDER;
//		pOption->sReflactive				= FALSE;

		//SetFogLevel( g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex, TRUE );
	}
	else
	{
		// 말것인가
		memcpy(pOption, &m_pSOptionOld, sizeof(sOPTION_SYSTEM));
		pOption->sLowQuality				= FALSE;
		
		//SetFogLevel( g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex, TRUE );
	}

}


void CINFOptionSystem::Render()
{
	FLOG( "CINFOptionSystem::Render()" );	

	// Show여부 
	if(!IsOptionShow())
	{
		return;
	}

	// 배경
	{
		m_pOptionBk->Move(m_ptBakPos.x, m_ptBakPos.y);
		m_pOptionBk->Render();
	}

	// 버튼 
	{
		m_pOptionApp->Render();	// 적용
		m_pOptionInit->Render();	// 초기화
		m_pOptionLogOff->Render();	// 로그오프
		m_pOptionGameEnd->Render();	// 게임종료
		// 2008-11-13 by bhsohn 조이스틱 작업
		m_pOptionJoystic->Render();	// 조이스틱옵션
		// end 2008-11-13 by bhsohn 조이스틱 작업
	}
	// 그래픽
	{
		// 해상도
		m_pFontHaeSang->DrawText(m_ptHaesangPos.x,m_ptHaesangPos.y,
									GUI_FONT_COLOR_W,
									m_szHaesangTxt);
	}

	int nCnt =0;
	int nMainId = 0;	
	for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
	{
		for(nCnt =0; nCnt < MAX_OPTION_SYS_CNT; nCnt++)
		{		
			m_pGameOpRadioBtn[nMainId][nCnt]->Render();
		}	
	}
	
	m_pMiniFrame->Render();	
	
	for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
	{
		// 2008-11-13 by bhsohn 조이스틱 작업
		// 마우스 좌우 반전은 체크안함
		if(OPTION_ETC_MOUSE_REVERSE_LR == nCnt)
		{
			continue;
		}
		// end 2008-11-13 by bhsohn 조이스틱 작업

		m_pEtcRadio[nCnt]->Render();		
	}

	// 콤보박스는 가장 마지막에 랜더링 	
	{
		int nSelCombo = -1;
		for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
		{
			if(m_pComboGraphic[nCnt]->IsShowItem())
			{
				nSelCombo = nCnt;
				break;
			}
		}
		for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
		{	
			if(nCnt != nSelCombo)
			{
				m_pComboGraphic[nCnt]->Render();
			}
		}
		if(nSelCombo != -1)
		{
			m_pComboGraphic[nSelCombo]->Render();
		}
	}
	m_pCloseBtn->Render();	
}


int CINFOptionSystem::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFOptionSystem::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	// Show여부 
	if(!IsOptionShow())
	{
		return INF_MSGPROC_NORMAL;
	}

	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			return OnMouseMove(wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			return OnLButtonDown(wParam, lParam);
		}
		break;
	case WM_RBUTTONDOWN:
		{
//			 2007-11-28 by bhsohn 스크린 샷 모드 추가
//						if(g_pInterface->IsScreenShotMode())
//						{
//							OptionQualityCombo();
//						}
//						// end 2007-11-28 by bhsohn 스크린 샷 모드 추가
		}
		break;
	case WM_LBUTTONUP:
		{
			return OnLButtonUp(wParam, lParam);
		}
		break;
	}
	
	
	return INF_MSGPROC_NORMAL;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		게임종료시 호출되는 함수
/// \author		
/// \date		2008-03-25 ~ 2008-03-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFOptionSystem::SendFieldSocketCharacterGameEnd()
{
	if(g_pD3dApp->m_dwGameState != _WAITING)
	{
		g_pStoreData->SendFieldSocketItemIndexInfo();
		MSG_FC_CHARACTER_GAMEEND	sMsg;
		// 2007-11-22 by bhsohn 아레나 통합서버
		//sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
		CHARACTER* pMainInfo = g_pD3dApp->GetMFSMyShuttleInfo();
		sMsg.ClientIndex =pMainInfo->ClientIndex;

		// 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템
		sMsg.SelectCharacterView	= m_bLogOffGameMessage;	// 로그오프 여부
		// end 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템

		g_pFieldWinSocket->SendMsg(T_FC_CHARACTER_GAMEEND, (char*)&sMsg, sizeof(sMsg) );
		g_pD3dApp->ChangeGameState(_WAITING);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		콤보박스에서 명칭변경
/// \author		
/// \date		2008-03-25 ~ 2008-03-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFOptionSystem::SetComboData(int nIdx, char* pSrc)
{
	if((nIdx >= MODE_COMBO_NUMBER)
		|| (nIdx < 0))
	{
		return;
	}
	strncpy(m_strSelectModeComboData[nIdx], pSrc, MODE_COMBO_STR_LEN);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		현재 보이고 있냐 여부
/// \author		
/// \date		2008-03-25 ~ 2008-03-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFOptionSystem::IsOptionShow()
{
	return m_bShow;

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		보이게 안보이게
/// \author		
/// \date		2008-03-25 ~ 2008-03-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void  CINFOptionSystem::ShowOptionWnd(BOOL bShow)
{
	m_bShow = bShow;

	// 2009. 08. 19 by jsKim 랜딩 중 메뉴 생성할 경우 커서가 변하지 않는 버그
	if(bShow)
	{
		g_INFCnt++;
	}
	else
	{
		g_INFCnt--;
	}
	// end 2009. 08. 19 by jsKim 랜딩 중 메뉴 생성할 경우 커서가 변하지 않는 버그
	if(bShow)
	{
		// 2009-03-04 by bhsohn 메뉴창 띠울시, 마우스 없어질수 있는 문제 수정
		if(g_pInterface->m_pTarget)
		{
			g_pInterface->m_pTarget->SetMouseType(MOUSE_TYPE_0);
		}
		// end 2009-03-04 by bhsohn 메뉴창 띠울시, 마우스 없어질수 있는 문제 수정

		memcpy(&m_pSOptionOld, g_pSOption, sizeof(sOPTION_SYSTEM));
		memcpy(&m_struSOptionCharacterOld, g_pSOptionCharacter, sizeof(sOPTION_CHARACTER));	

		memcpy(&m_struOpInfo.struSOptionSetup, g_pSOption, sizeof(sOPTION_SYSTEM));		
		memcpy(&m_struOpInfo.struSOptionCharacter, g_pSOptionCharacter, sizeof(sOPTION_CHARACTER));		
		
		// 오퍼레이터
		m_struOpInfo.bOperator = g_pInterface->GetOperatorMode();

		// 옵션 ETC메뉴
		memcpy(&m_struOpInfo.struSOptionEtc, g_pSOptionEtc, sizeof(sOPTION_ETC));
		
		// 인터페이스 감추기
		//m_struOpInfo.struSOptionEtc.bRadioInfo[OPTION_RADIO_INTERFACE_HIDE] = !g_pInterface->GetShowInterface();			
		m_struOpInfo.struSOptionEtc.bRadioInfo[OPTION_RADIO_INTERFACE_HIDE] = g_pD3dApp->IsOptionEtc(OPTION_RADIO_INTERFACE_HIDE);

		// 라디오 버튼 갱신
		UpdateOptionInterface(&m_struOpInfo);	
		
		// 2008-11-13 by bhsohn 조이스틱 작업
		{
			CJoyStickInput *pJoyStick = g_pD3dApp->GetJoystickControl();
			BOOL bEnableBtn = FALSE;
			if(pJoyStick || g_pD3dApp->GetJoystickCtrlDeviceListLen() > 0)
			{
				bEnableBtn = TRUE;				
			}

			m_pOptionJoystic->EnableBtn(bEnableBtn);
		}
		// end 2008-11-13 by bhsohn 조이스틱 작업
		
	}
}
void CINFOptionSystem::UpdateBtnPos(int nBackPosX, int nBackPosY)
{
	int nCnt = 0;
 	int nPosX, nPosY;
	{
		nPosX = nBackPosX + OPTION_BTN_APP_X;
		nPosY = nBackPosY + OPTION_BTN_APP_Y;		
		m_pOptionApp->SetBtnPosition(nPosX, nPosY);
	}
	{
		nPosX = nBackPosX + OPTION_BTN_INIT_X;
		nPosY = nBackPosY + OPTION_BTN_INIT_Y;		
		m_pOptionInit->SetBtnPosition(nPosX, nPosY);
	}
	{
		nPosX = nBackPosX + OPTION_BTN_LOGOFF_X;
		nPosY = nBackPosY + OPTION_BTN_LOGOFF_Y;		
		m_pOptionLogOff->SetBtnPosition(nPosX, nPosY);
		// 2009-05-06 by bhsohn 중국 로그오프창 막음
	#if defined(LANGUAGE_CHINA) 
		#ifndef TAIWAN_RELEASE
			m_pOptionLogOff->EnableBtn(FALSE);
		#endif
	#endif
		// end 2009-05-06 by bhsohn 중국 로그오프창 막음
	}
	{
		nPosX = nBackPosX + OPTION_BTN_GAMEEND_X;
		nPosY = nBackPosY + OPTION_BTN_GAMEEND_Y;		
		m_pOptionGameEnd->SetBtnPosition(nPosX, nPosY);
	}
	// 2008-11-13 by bhsohn 조이스틱 작업		
	{
		nPosX = nBackPosX + OPTION_JOYSTICK_BTN_X;
		nPosY = nBackPosY + OPTION_JOYSTICK_BTN_Y;		
		m_pOptionJoystic->SetBtnPosition(nPosX, nPosY);				
	}
	// end 2008-11-13 by bhsohn 조이스틱 작업		
	
	int nMainId = 0;	
	for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
	{
		for(nCnt = 0;nCnt < MAX_OPTION_SYS_CNT;nCnt++)
		{
			nPosX = nBackPosX + OPTION_RADIO_GAME_INFO_X + (nCnt*OPTION_RADIO_GAME_INFO_CAP_X);
			nPosY = nBackPosY + OPTION_RADIO_GAME_INFO_Y+ (nMainId*OPTION_RADIO_GAME_INFO_CAP_Y);		
			m_pGameOpRadioBtn[nMainId][nCnt]->SetPosition(nPosX, nPosY, 60);		
		}
	}

	// 해상도
	{
		
		if(g_pD3dApp->m_IsFullMode)
		{
			wsprintf( m_szHaesangTxt, "%d*%d", g_pD3dApp->m_nWidth,g_pD3dApp->m_nHeight);
		}
		else
		{
			wsprintf( m_szHaesangTxt, "%d*%d%s", g_pD3dApp->m_nWidth,g_pD3dApp->m_nHeight,STRMSG_C_071221_0100);
		}
		SIZE sizeStrSize = m_pFontHaeSang->GetStringSize(m_szHaesangTxt);
		m_ptHaesangPos.x = nBackPosX + OPTION_HAESANG_X- sizeStrSize.cx;
		m_ptHaesangPos.y = nBackPosY + OPTION_HAESANG_Y;
	}

	{
		int nMainWidth, nMainHeight;
		int nEleWidth, nEleHeight;
		nMainWidth = OPTION_COMBO_MAIN_WIDTH;
		nMainHeight = OPTION_COMBO_MAIN_HEIGHT;
		nEleWidth = OPTION_COMBO_ELE_WIDTH;
		nEleHeight = OPTION_COMBO_ELE_HEIGHT;
		
		POINT	ptMainArena[MAX_OPTION_GRAPHIC_COMBO] =
		{
			{nBackPosX+OPTION_COMBO_SEE_RANGE_X, nBackPosY+OPTION_COMBO_SEE_RANGE_Y},
			{nBackPosX+OPTION_COMBO_UNIT_DETAIL_X, nBackPosY+OPTION_COMBO_UNIT_DETAIL_Y},
			{nBackPosX+OPTION_COMBO_SHADOW_X, nBackPosY+OPTION_COMBO_SHADOW_Y},
			{nBackPosX+OPTION_COMBO_EFFECT_X, nBackPosY+OPTION_COMBO_EFFECT_Y},
			{nBackPosX+OPTION_COMBO_GAMMA_X, nBackPosY+OPTION_COMBO_GAMMA_Y},
			{nBackPosX+OPTION_COMBO_CONTRAST_X, nBackPosY+OPTION_COMBO_CONTRAST_Y},
			{nBackPosX+OPTION_COMBO_FILTER_X, nBackPosY+OPTION_COMBO_FILTER_Y},
			{nBackPosX+OPTION_COMBO_SEE_CHANGE_X, nBackPosY+OPTION_COMBO_SEE_CHANGE_Y},
			{nBackPosX+OPTION_COMBO_MUSIC_VOL_X, nBackPosY+OPTION_COMBO_MUSIC_VOL_Y}
		};
		
		POINT	ptElementArena[MAX_OPTION_GRAPHIC_COMBO] =
		{
			{ptMainArena[0].x, ptMainArena[0].y + nMainHeight},
			{ptMainArena[1].x, ptMainArena[1].y + nMainHeight},
			{ptMainArena[2].x, ptMainArena[2].y + nMainHeight},
			{ptMainArena[3].x, ptMainArena[3].y + nMainHeight},
			{ptMainArena[4].x, ptMainArena[4].y + nMainHeight},
			{ptMainArena[5].x, ptMainArena[5].y + nMainHeight},
			{ptMainArena[6].x, ptMainArena[6].y + nMainHeight},
			{ptMainArena[7].x, ptMainArena[7].y + nMainHeight},
			{ptMainArena[8].x, ptMainArena[8].y + nMainHeight}
		};
		
		
		for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
		{
			m_pComboGraphic[nCnt]->SetMainArea(ptMainArena[nCnt].x, 
												ptMainArena[nCnt].y,
											nMainWidth, nMainHeight);
			m_pComboGraphic[nCnt]->SetElementArea(ptElementArena[nCnt].x,
													ptElementArena[nCnt].y,
													nEleWidth, nEleHeight);
			m_pComboGraphic[nCnt]->SetBGPos(ptElementArena[nCnt].x+6,
													ptElementArena[nCnt].y,
													nEleWidth, nEleHeight);
		}
	}
	{
		nPosX = nBackPosX + OPTION_RADIO_SMALLFRM_X;
		nPosY = nBackPosY + OPTION_RADIO_SMALLFRM_Y;
		m_pMiniFrame->SetPosition(nPosX, nPosY, 60);
	}
		
	// 체크버튼
	{
		POINT	ptRadio[MAX_OPTION_ETC_RADIO] =
		{
			{nBackPosX+OPTION_RADIO_MOUSE_X, nBackPosY+OPTION_RADIO_MOUSE_Y},
			{nBackPosX+OPTION_RADIO_HELPER_X, nBackPosY+OPTION_RADIO_HELPER_Y},
			{nBackPosX+OPTION_RADIO_OPER_X, nBackPosY+OPTION_RADIO_OPER_Y},
			{nBackPosX+OPTION_RADIO_MAINTAIN_X, nBackPosY+OPTION_RADIO_MAINTAIN_Y},
			{nBackPosX+OPTION_RADIO_REVERSE_TB_X, nBackPosY+OPTION_RADIO_REVERSE_TB_Y},
			{nBackPosX+OPTION_RADIO_REVERSE_LR_X, nBackPosY+OPTION_RADIO_REVERSE_LR_Y},
			{nBackPosX+OPTION_RADIO_MENU_X, nBackPosY+OPTION_RADIO_MENU_Y},
			{nBackPosX+OPTION_RADIO_MP3_X, nBackPosY+OPTION_RADIO_MP3_Y}			
		};
		for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
		{			
			m_pEtcRadio[nCnt]->SetPosition(ptRadio[nCnt].x, ptRadio[nCnt].y, 60);
		}
	}	
	// 닫기 버튼
	{		
		nPosX = nBackPosX + OPTION_BTN_CLOSE_X;
		nPosY = nBackPosY + OPTION_BTN_CLOSE_Y;	

		m_pCloseBtn->SetBtnPosition(nPosX, nPosY);
	}

}

int CINFOptionSystem::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	CheckMouseReverse(&pt);
	if(TRUE == m_pOptionApp->OnLButtonDown(pt))
	{
		// 버튼위에 마우스가 있다.
		return  INF_MSGPROC_BREAK;
	}		
	if(TRUE == m_pOptionInit->OnLButtonDown(pt))
	{
		// 버튼위에 마우스가 있다.
		return  INF_MSGPROC_BREAK;
	}		
	if(TRUE == m_pOptionLogOff->OnLButtonDown(pt))
	{
		// 버튼위에 마우스가 있다.
		return  INF_MSGPROC_BREAK;
	}		
	if(TRUE == m_pOptionGameEnd->OnLButtonDown(pt))
	{
		// 버튼위에 마우스가 있다.
		return  INF_MSGPROC_BREAK;
	}		
	// 2008-11-13 by bhsohn 조이스틱 작업
	if(TRUE == m_pOptionJoystic->OnLButtonDown(pt))
	{
		// 버튼위에 마우스가 있다.
		return  INF_MSGPROC_BREAK;
	}		
	// end 2008-11-13 by bhsohn 조이스틱 작업

	int nCnt = 0;	
	// 라디오 버튼 처리
	{		
		// 1:1전투
		int nMainId = 0;	
		BOOL bBreak = FALSE;
		for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
		{
			if(bBreak )
			{
				break;
			}
			for(nCnt = 0;nCnt <MAX_OPTION_SYS_CNT;nCnt++)
			{
				if(bBreak )
				{
					break;
				}
				if(TRUE == m_pGameOpRadioBtn[nMainId][nCnt]->OnLButtonDown(pt))
				{
					BOOL bRadioCheck = TRUE;
					if(OPTION_SYS_OFF == nCnt)
					{
						bRadioCheck = FALSE;
					}
					SetRadioInfo(nMainId, bRadioCheck);
					bBreak = TRUE;
				}		
			}	
		}
	}	

	
	// 그래픽 관련	
	int nGraphicOptionSel = -1;
	{
		for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
		{
			int nLBtnDown = m_pComboGraphic[nCnt]->LButtonDown(pt);
			if(-1 != nLBtnDown)				
			{
				// 안보이다가 보이는 상황
				nGraphicOptionSel = nCnt;
				break;
			}
		}
		// 선택된거를 제외한거 전체를 히든으로
		if(nGraphicOptionSel != -1)
		{
			for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
			{
				if(nCnt != nGraphicOptionSel)
				{
					m_pComboGraphic[nCnt]->ShowItem(FALSE);					
				}
			}
			// 옵션정보 갱신
			UpdateOptionInfo();
			// 라디오 버튼 갱신
			UpdateOptionInterface(&m_struOpInfo);
			return  INF_MSGPROC_BREAK;
		}			
	}
	// 그래픽 체크버튼
	{		
		if(TRUE == m_pMiniFrame->OnLButtonDown(pt))
		{
			// 최소 프레임 버튼클릭
			OptionQualityCombo();
			return  INF_MSGPROC_BREAK;			
		}		
	}

	{
		for(nCnt = 0;nCnt < MAX_OPTION_ETC_RADIO;nCnt++)
		{	
			// 2008-11-13 by bhsohn 조이스틱 작업
			// 마우스 좌우 반전은 체크안함
			if(OPTION_ETC_MOUSE_REVERSE_LR == nCnt)
			{
				continue;
			}
			// end 2008-11-13 by bhsohn 조이스틱 작업

			if(TRUE == m_pEtcRadio[nCnt]->OnLButtonDown(pt))
			{
				OnClickEtcRadio(nCnt);
				// 유저 인터페이스 갱신
				UpdateOptionInterface(&m_struOpInfo);
				return  INF_MSGPROC_BREAK;
			}
		}
	}
	{
		if(TRUE == m_pCloseBtn->OnLButtonDown(pt))
		{
			// 버튼위에 마우스가 있다.
			return  INF_MSGPROC_BREAK;
		}		
	}
	
	// 라디오 버튼 갱신
	UpdateOptionInterface(&m_struOpInfo);

	if((m_ptBakPos.x <= pt.x && pt.x <= (m_ptBakPos.x+m_ptBakSize.x))
		&& (m_ptBakPos.y <= pt.y && pt.y <= (m_ptBakPos.y+m_ptBakSize.y)))
	{
		// 배경위에서 버튼클릭
		return  INF_MSGPROC_BREAK;
	}


	return INF_MSGPROC_NORMAL;
}

int CINFOptionSystem::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	int nCnt = 0;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);

	m_pOptionApp->OnMouseMove(pt);	
	m_pOptionInit->OnMouseMove(pt);	
	m_pOptionLogOff->OnMouseMove(pt);	
	m_pOptionGameEnd->OnMouseMove(pt);	
	// 2008-11-13 by bhsohn 조이스틱 작업
	m_pOptionJoystic->OnMouseMove(pt);	
	// end 2008-11-13 by bhsohn 조이스틱 작업

	m_pCloseBtn->OnMouseMove(pt);	

	for(nCnt = 0;nCnt < MAX_OPTION_GRAPHIC_COMBO;nCnt++)
	{
		m_pComboGraphic[nCnt]->MouseMove(pt);
	}	

	return INF_MSGPROC_NORMAL;

}

int CINFOptionSystem::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);

	{
		if(TRUE == m_pOptionApp->OnLButtonUp(pt))
		{			
			// 적용버튼
			OnClickApply();
			// 버튼 클릭 			
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
			return  INF_MSGPROC_BREAK;
		}
	}
	{
		if(TRUE == m_pOptionInit->OnLButtonUp(pt))
		{	
			// 로그오프
			OnSystemButtonClick(OPTIONSYS_INITSETUP_BTN);
			// 버튼 클릭 			
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
			return  INF_MSGPROC_BREAK;
		}
	}
	{
		if(TRUE == m_pOptionLogOff->OnLButtonUp(pt))
		{	
			// 로그오프
			OnSystemButtonClick(OPTIONSYS_LOGOFF_BTN);
			// 버튼 클릭 			
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
			return  INF_MSGPROC_BREAK;
		}
	}
	{
		if(TRUE == m_pOptionGameEnd->OnLButtonUp(pt))
		{
			// 로그오프
			OnSystemButtonClick(OPTIONSYS_GAMEEND_BTN);

			// 버튼 클릭 			
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
			return  INF_MSGPROC_BREAK;
		}
	}
	// 2008-11-13 by bhsohn 조이스틱 작업
	{
		if(TRUE == m_pOptionJoystic->OnLButtonUp(pt))
		{
			OnClickJoystciOption();
			// 버튼 클릭 			
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
			return  INF_MSGPROC_BREAK;
		}		
	}
	// end 2008-11-13 by bhsohn 조이스틱 작업
	{
		if(TRUE == m_pCloseBtn->OnLButtonUp(pt))
		{				
			// 현재 윈도우를 숨긴다.
			ShowOptionWnd(FALSE);
			// 버튼 클릭 
			// 2009. 08. 19 by jsKim 랜딩 중 메뉴 생성할 경우 커서가 변하지 않는 버그
			g_INFCnt--;
			if(g_INFCnt==0)
			{
				g_pGameMain->m_bChangeMousePoint = FALSE;
			}
			// end 2009. 08. 19 by jsKim 랜딩 중 메뉴 생성할 경우 커서가 변하지 않는 버그
			g_pD3dApp->m_pSound->PlayD3DSound(SOUND_CLOSE_MENU, g_pShuttleChild->m_vPos, FALSE);
			return  INF_MSGPROC_BREAK;
		}
	}

	return INF_MSGPROC_NORMAL;
}

void CINFOptionSystem::OnSystemButtonClick(int nButton)
{
	DWORD dwCurTick = timeGetTime();
	
	// 2004-12-17 by jschoi - 워프중에는 종료를 할 수 없다.
	if( g_pShuttleChild->m_nCurrentPatternNumber == PATTERN_UNIT_WARP_OUT ||
		g_pShuttleChild->m_nCurrentPatternNumber == PATTERN_UNIT_WARP_IN  ||
		g_pShuttleChild->m_nCurrentPatternNumber == PATTERN_UNIT_CITY_OUT ||
		g_pShuttleChild->m_nCurrentPatternNumber == PATTERN_UNIT_CITY_IN  )
	{
		return;
	}
	// 2006-08-02 by ispark, 개인 상점
	if(g_pInterface->m_pBazaarShop)
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060802_0003,COLOR_ERROR);// "개인상점 이용중에는 사용 할 수 없습니다."
		return;
	}
	if(TRUE == m_bQuitGameMessage)
	{
		// 게임종료중에 못들어오게함
		return;
	}
	
	switch(nButton)
	{
	case OPTIONSYS_LOGOFF_BTN://선택
		{
			// 2011-07-06 by shcho, hsson 아레나 게임 진입 시 캐릭터 선택 못하게 수정
			if( g_pD3dApp->m_pInterface->IsArenaGameState( ARENA_GAME_STATE_TIMER )
			 || g_pD3dApp->m_pInterface->IsArenaGameState( ARENA_GAME_STATE_SCORE ) )
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_080225_0203, _MESSAGE); // "아레나에서는 이용할 수 없습니다."
				return;
			}
			// end 2011-07-06 by shcho, hsson 아레나 게임 진입 시 캐릭터 선택 못하게 수정

			m_bQuitGameMessage = TRUE;
			m_bLogOffGameMessage = TRUE;
			m_fLastTickSecTime = dwCurTick;
			g_pGameMain->RightWindowShow(FALSE,g_pGameMain->m_nRightWindowInfo);
			g_pGameMain->LeftWindowShow(FALSE,g_pGameMain->m_nLeftWindowInfo);
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_INTERFACE_0040, _Q_QUIT_MESSAGE);//"로그오프까지 5초 남았습니다."			

			// 현재 윈도우를 숨긴다.
			ShowOptionWnd(FALSE);

		}
		break;
	case OPTIONSYS_GAMEEND_BTN://종료
		{
			m_bQuitGameMessage = TRUE;
			m_fLastTickSecTime = dwCurTick;
			g_pGameMain->RightWindowShow(FALSE,g_pGameMain->m_nRightWindowInfo);
			g_pGameMain->LeftWindowShow(FALSE,g_pGameMain->m_nLeftWindowInfo);
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_INTERFACE_0041, _Q_QUIT_MESSAGE);//"게임종료까지 5초 남았습니다."

			// 현재 윈도우를 숨긴다.
			ShowOptionWnd(FALSE);
			return;
		}
		break;
	case OPTIONSYS_INITSETUP_BTN: // 초기화
		{
			m_struOpInfo = InitOptionGameInfo();
			// 라디오 버튼 갱신
			UpdateOptionInterface(&m_struOpInfo);

		}
		break;
	}
}
structOptionGameInfo CINFOptionSystem::InitOptionGameInfo()
{
	structOptionGameInfo	struTmpOpInfo;
	memset(&struTmpOpInfo, 0x00, sizeof(structOptionGameInfo));	

	g_pD3dApp->InitOptionEtcInfo(&struTmpOpInfo.struSOptionEtc);
	

	// 옵션정보
	{				
		struTmpOpInfo.struSOptionSetup.sSoundVolume = OPTION_DEFAULT_SOUNDVOLUME;
		struTmpOpInfo.struSOptionSetup.sMusicVolume = OPTION_DEFAULT_MUSICVOLUME;
		struTmpOpInfo.struSOptionSetup.sGammaCtrl = OPTION_DEFAULT_GAMMA;
		struTmpOpInfo.struSOptionSetup.sLowQuality	= OPTION_DEFAULT_LOWQUALITY;
		struTmpOpInfo.struSOptionSetup.sMouseReversLeft = OPTION_DEFAULT_REVERSE_LEFT;			// 마우스 좌우반전
		struTmpOpInfo.struSOptionSetup.sMouseReversUp = OPTION_DEFAULT_REVERSE_UP;				// 마우스 상하반전
		struTmpOpInfo.struSOptionSetup.sAutoBalance = OPTION_DEFAULT_AUTO_BALACE;				// 자동 수평조정
		struTmpOpInfo.struSOptionSetup.sMenuBalance = OPTION_DEFAULT_MENU_USE;					// 메뉴사용시 자동 수평조정
		struTmpOpInfo.struSOptionSetup.sMp3Player = OPTION_DEFAULT_MP3_USE;					// 뮤직플레이어
		struTmpOpInfo.struSOptionSetup.sHandle = TRUE ;										// 마우스 포인트 보이기
		switch(g_pD3dApp->m_bDegree)
		{
		case 2:// HIGH
			{
				struTmpOpInfo.struSOptionSetup.sTerrainEffectRender = OPTION_DEFAULT_HIGH_TERRAINEFFECTRENDER;
				struTmpOpInfo.struSOptionSetup.sTerrainRender = OPTION_DEFAULT_HIGH_TERRAINRENDER;
				struTmpOpInfo.struSOptionSetup.sShadowState = OPTION_DEFAULT_HIGH_SHOWSHADOW;
				struTmpOpInfo.struSOptionSetup.sUnitDetail = OPTION_DEFAULT_HIGH_UNITDETAIL;
				struTmpOpInfo.struSOptionSetup.sContrast = OPTION_DEFAULT_HIGH_CONTRAST;
				struTmpOpInfo.struSOptionSetup.sFilter = OPTION_DEFAULT_HIGH_FILTER;
			}
			break;
		case 1:// Middle
			{
				struTmpOpInfo.struSOptionSetup.sTerrainEffectRender = OPTION_DEFAULT_MIDDLE_TERRAINEFFECTRENDER;
				struTmpOpInfo.struSOptionSetup.sTerrainRender = OPTION_DEFAULT_MIDDLE_TERRAINRENDER;
				struTmpOpInfo.struSOptionSetup.sShadowState = OPTION_DEFAULT_MIDDLE_SHOWSHADOW;
				struTmpOpInfo.struSOptionSetup.sUnitDetail = OPTION_DEFAULT_MIDDLE_UNITDETAIL;
				struTmpOpInfo.struSOptionSetup.sContrast = OPTION_DEFAULT_MIDDLE_CONTRAST;
				struTmpOpInfo.struSOptionSetup.sFilter = OPTION_DEFAULT_MIDDLE_FILTER;
			}
			break;
		case 0:// LOW
			{
				struTmpOpInfo.struSOptionSetup.sTerrainEffectRender = OPTION_DEFAULT_LOW_TERRAINEFFECTRENDER;
				struTmpOpInfo.struSOptionSetup.sTerrainRender = OPTION_DEFAULT_LOW_TERRAINRENDER;
				struTmpOpInfo.struSOptionSetup.sShadowState = OPTION_DEFAULT_LOW_SHOWSHADOW;
				struTmpOpInfo.struSOptionSetup.sUnitDetail = OPTION_DEFAULT_LOW_UNITDETAIL;
				struTmpOpInfo.struSOptionSetup.sContrast = OPTION_DEFAULT_LOW_CONTRAST;
				struTmpOpInfo.struSOptionSetup.sFilter = OPTION_DEFAULT_LOW_FILTER;
			}
			break;
		}
		
		struTmpOpInfo.struSOptionSetup.sEyePt = FALSE;
		struTmpOpInfo.struSOptionSetup.sTarget = TRUE ;
		struTmpOpInfo.struSOptionSetup.sHeight = FALSE ;
		struTmpOpInfo.struSOptionSetup.sPKMode = 0 ;
		struTmpOpInfo.struSOptionSetup.InputType = 0 ;	
		
		// 채팅옵션 저장
		for(int i = 0; i < 12 /*CHAT_MENULIST_NUMBER*/ ; i++)
		{
			struTmpOpInfo.struSOptionSetup.m_bChatCurrentSelect[i] = TRUE;
		}
	}
	{
		struTmpOpInfo.struSOptionCharacter.sHelpDesk = TRUE;
		memset(struTmpOpInfo.struSOptionCharacter.UniqueNumber, 0x00, QSLOT_NUMBER*QSLOT_TAB_NUMBER*sizeof(UID64_t));
		memset(struTmpOpInfo.struSOptionCharacter.ItemNum, 0x00, QSLOT_NUMBER*QSLOT_TAB_NUMBER*sizeof(int));

	}
	{
		struTmpOpInfo.bOperator = TRUE;	// 오퍼레이터
	}

	return struTmpOpInfo;
}
void CINFOptionSystem::SetRadioInfo(int nMainId, BOOL bOnOff)
{
	m_struOpInfo.struSOptionEtc.bRadioInfo[nMainId] = bOnOff;
}

void CINFOptionSystem::UpdateOptionInterface(structOptionGameInfo* pOptionInfo)
{
	int nMainId = 0;
	for(nMainId = 0;nMainId < MAX_OPTION_RADIO;nMainId++)
	{
		if(pOptionInfo->struSOptionEtc.bRadioInfo[nMainId])
		{
			m_pGameOpRadioBtn[nMainId][OPTION_SYS_ON]->SetRadioBtn(TRUE);
			m_pGameOpRadioBtn[nMainId][OPTION_SYS_OFF]->SetRadioBtn(FALSE);
		}
		else
		{
			m_pGameOpRadioBtn[nMainId][OPTION_SYS_ON]->SetRadioBtn(FALSE);
			m_pGameOpRadioBtn[nMainId][OPTION_SYS_OFF]->SetRadioBtn(TRUE);
		}		
	}	
	
	// 그래픽옵션
	{	
		// 시야거리
		m_pComboGraphic[OPTION_GRAPHIC_SEE_RANGE]->SetSelectItem(GetGarphicOption_To_Cursel(OPTION_GRAPHIC_SEE_RANGE, pOptionInfo->struSOptionSetup.sTerrainRender));
		// 유닛 디테일
		m_pComboGraphic[OPTION_GRAPHIC_UNIT_DETAIL]->SetSelectItem(GetGarphicOption_To_Cursel(OPTION_GRAPHIC_UNIT_DETAIL, pOptionInfo->struSOptionSetup.sUnitDetail));
		// 그림자조절
		m_pComboGraphic[OPTION_GRAPHIC_SHADOW]->SetSelectItem(GetGarphicOption_To_Cursel(OPTION_GRAPHIC_SHADOW, pOptionInfo->struSOptionSetup.sShadowState));
		// 이펙트 조절
		m_pComboGraphic[OPTION_GRAPHIC_EFFECT]->SetSelectItem(GetGarphicOption_To_Cursel(OPTION_GRAPHIC_EFFECT, pOptionInfo->struSOptionSetup.sTerrainEffectRender));

		// 감마 조절		
		m_pComboGraphic[OPTION_GRAPHIC_GAMMA]->SetSelectItem(GetGarphicOption_To_Cursel(OPTION_GRAPHIC_GAMMA, pOptionInfo->struSOptionSetup.sGammaCtrl));
		// 대비 조절
		m_pComboGraphic[OPTION_GRAPHIC_CONTRAST]->SetSelectItem(GetGarphicOption_To_Cursel(OPTION_GRAPHIC_CONTRAST, pOptionInfo->struSOptionSetup.sContrast));
		// 필터 효과
		m_pComboGraphic[OPTION_GRAPHIC_FILTER]->SetSelectItem(GetGarphicOption_To_Cursel(OPTION_GRAPHIC_FILTER, pOptionInfo->struSOptionSetup.sFilter));
		
		// 최소 프레임모드
		m_pMiniFrame->SetRadioBtn(pOptionInfo->struSOptionSetup.sLowQuality);
	}

	// ETc옵션
	{
		// 시전변환
		m_pComboGraphic[OPTION_ETC_SEE_CHANGE]->SetSelectItem(GetEtcOption_To_Cursel(OPTION_ETC_SEE_CHANGE, pOptionInfo->struSOptionSetup.sEyePt));

		// 시전변환
		m_pComboGraphic[OPTION_ETC_VOLUMNE]->SetSelectItem(GetEtcOption_To_Cursel(OPTION_ETC_VOLUMNE, pOptionInfo->struSOptionSetup.sSoundVolume));

		// 마우스 포인터 보이기
		m_pEtcRadio[OPTION_ETC_SHOW_MOUSE]->SetRadioBtn(pOptionInfo->struSOptionSetup.sHandle);
		// 헬프기능
		m_pEtcRadio[OPTION_ETC_HELP]->SetRadioBtn(pOptionInfo->struSOptionCharacter.sHelpDesk);
		// 오퍼레이터 기능
		m_pEtcRadio[OPTION_ETC_OPERATOR]->SetRadioBtn(pOptionInfo->bOperator);
		// 자동 수평유지
		m_pEtcRadio[OPTION_ETC_MAINTAIN]->SetRadioBtn(pOptionInfo->struSOptionSetup.sAutoBalance);
		// 상하 반전 
		m_pEtcRadio[OPTION_ETC_MOUSE_REVERSE_TB]->SetRadioBtn(pOptionInfo->struSOptionSetup.sMouseReversUp);
		// 마우스 좌우 반전
		m_pEtcRadio[OPTION_ETC_MOUSE_REVERSE_LR]->SetRadioBtn(pOptionInfo->struSOptionSetup.sMouseReversLeft);
		// 메뉴 사용시 유닛정지
		// 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
		//m_pEtcRadio[OPTION_ETC_MENU_UNISTOP]->SetRadioBtn(pOptionInfo->struSOptionSetup.sMenuBalance);
		m_pEtcRadio[OPTION_ETC_PET_OP_SYS]->SetRadioBtn(pOptionInfo->struSOptionSetup.sPetOPBalance); 
		// end 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
		// Music플레이어 보기
		m_pEtcRadio[OPTION_ETC_MUSIC]->SetRadioBtn(pOptionInfo->struSOptionSetup.sMp3Player);
	}
	
}

void CINFOptionSystem::UpdateOptionInfo()
{
	structOptionGameInfo* pOptionInfo = &m_struOpInfo;
	// 그래픽옵션
	int nCursel = 0;
	{	
		// 시야거리
		nCursel = m_pComboGraphic[OPTION_GRAPHIC_SEE_RANGE]->GetSelect();
		pOptionInfo->struSOptionSetup.sTerrainRender = GetGarphicCursel_To_Option(OPTION_GRAPHIC_SEE_RANGE, nCursel);

		// 유닛 디테일
		nCursel = m_pComboGraphic[OPTION_GRAPHIC_UNIT_DETAIL]->GetSelect();
		pOptionInfo->struSOptionSetup.sUnitDetail = GetGarphicCursel_To_Option(OPTION_GRAPHIC_UNIT_DETAIL, nCursel);
		
		// 그림자조절
		nCursel = m_pComboGraphic[OPTION_GRAPHIC_SHADOW]->GetSelect();
		pOptionInfo->struSOptionSetup.sShadowState = GetGarphicCursel_To_Option(OPTION_GRAPHIC_SHADOW, nCursel);		

		// 이펙트 조절
		nCursel = m_pComboGraphic[OPTION_GRAPHIC_EFFECT]->GetSelect();
		pOptionInfo->struSOptionSetup.sTerrainEffectRender = GetGarphicCursel_To_Option(OPTION_GRAPHIC_EFFECT, nCursel);		

		// 감마 조절		
		nCursel = m_pComboGraphic[OPTION_GRAPHIC_GAMMA]->GetSelect();
		pOptionInfo->struSOptionSetup.sGammaCtrl = GetGarphicCursel_To_Option(OPTION_GRAPHIC_GAMMA, nCursel);
		
		// 대비 조절
		nCursel = m_pComboGraphic[OPTION_GRAPHIC_CONTRAST]->GetSelect();
		pOptionInfo->struSOptionSetup.sContrast = GetGarphicCursel_To_Option(OPTION_GRAPHIC_CONTRAST, nCursel);
		
		// 필터 효과
		nCursel = m_pComboGraphic[OPTION_GRAPHIC_FILTER]->GetSelect();
		pOptionInfo->struSOptionSetup.sFilter = GetGarphicCursel_To_Option(OPTION_GRAPHIC_FILTER, nCursel);		
	}

	// ETC 관련사항
	{		
		// 시점변환
		nCursel = m_pComboGraphic[OPTION_ETC_SEE_CHANGE]->GetSelect();
		pOptionInfo->struSOptionSetup.sEyePt = GetEtcCursel_To_Option(OPTION_ETC_SEE_CHANGE, nCursel);

		nCursel = m_pComboGraphic[OPTION_ETC_VOLUMNE]->GetSelect();
		pOptionInfo->struSOptionSetup.sSoundVolume = GetEtcCursel_To_Option(OPTION_ETC_VOLUMNE, nCursel);

	}
}

int CINFOptionSystem::GetGarphicOption_To_Cursel(int nMode, int nState)
{
	int nCurSel = nState;
	if(OPTION_GRAPHIC_GAMMA == nMode)
	{
		switch(nState)
		{
		case 5:
			{
				nCurSel = 0;
			}
			break;
		case 4:
			{
				nCurSel = 1;
			}
			break;
		case 3:
			{
				nCurSel = 2;
			}
			break;
		case 2:
			{
				nCurSel = 3;
			}
			break;
		case 1:
			{
				nCurSel = 4;
			}
			break;
		case 0:
			{
				nCurSel = 5;
			}
			break;
		case -1:
			{
				nCurSel = 6;
			}
			break;
		case -2:
			{
				nCurSel = 7;
			}
			break;
		case -3:
			{
				nCurSel = 8;
			}
			break;
		case -4:
			{
				nCurSel = 9;
			}
			break;
		}		
	}
	return nCurSel;
}
int CINFOptionSystem::GetGarphicCursel_To_Option(int nMode, int nCursel)
{
	int nState= nCursel;
	if(OPTION_GRAPHIC_GAMMA == nMode)
	{
		switch(nCursel)
		{
		case 0:
			{
				nState = 5;
			}
			break;
		case 1:
			{
				nState = 4;				
			}
			break;
		case 2:
			{
				nState = 3;
			}
			break;
		case 3:
			{
				nState = 2;				
			}
			break;
		case 4:
			{
				nState = 1;				
			}
			break;
		case 5:
			{
				nState = 0;				
			}
			break;
		case 6:
			{
				nState = -1;
			}
			break;
		case 7:
			{
				nState = -2;
			}
			break;
		case 8:
			{
				nState = -3;
			}
			break;
		case 9:
			{
				nState = -4;
			}
			break;
		}		
	}
	return nState;
}


int CINFOptionSystem::GetEtcOption_To_Cursel(int nMode, int nState)
{
	int nCurSel = nState;
	if(OPTION_ETC_SEE_CHANGE == nMode)
	{
		switch(nState)
		{
		case FALSE:
			{
				nCurSel = 1;
			}
			break;
		case TRUE:
			{
				nCurSel = 0;
			}
			break;
		}
	}
	else if(OPTION_ETC_VOLUMNE == nMode)
	{
		switch(nState)
		{
		case -10000:
			{
				nCurSel = 0;
			}
			break;
		case -3500:
			{
				nCurSel = 1;
			}
			break;
		case -3000:
			{
				nCurSel = 2;
			}
			break;
		case -2500:
			{
				nCurSel = 3;
			}
			break;
		case -2000:
			{
				nCurSel = 4;
			}
			break;
		case -1500:
			{
				nCurSel = 5;
			}
			break;
		case -1000:
			{
				nCurSel = 6;
			}
			break;
		case -600:
			{
				nCurSel = 7;
			}
			break;
		case -300:
			{
				nCurSel = 8;
			}
			break;
		case 0:
			{
				nCurSel = 9;
			}
			break;
		}		
	}
	return nCurSel;
}
int CINFOptionSystem::GetEtcCursel_To_Option(int nMode, int nCursel)
{
	int nState= nCursel;
	if(OPTION_ETC_SEE_CHANGE == nMode)
	{
		switch(nCursel)
		{
		case 1:
			{				
				nState = FALSE;
			}
			break;
		case 0:
			{				
				nState = TRUE;
			}
			break;
		}
	}
	else if(OPTION_ETC_VOLUMNE == nMode)
	{
		switch(nCursel)
		{
		case 0:
			{
				nState = -10000;
			}
			break;
		case 1:
			{
				nState = -3500;				
			}
			break;
		case 2:
			{
				nState = -3000;
			}
			break;
		case 3:
			{
				nState = -2500;				
			}
			break;
		case 4:
			{
				nState = -2000;				
			}
			break;
		case 5:
			{
				nState = -1500;				
			}
			break;
		case 6:
			{
				nState = -1000;
			}
			break;
		case 7:
			{
				nState = -600;
			}
			break;
		case 8:
			{
				nState = -300;
			}
			break;
		case 9:
			{
				nState = 0;
			}
			break;
		}		
	}
	return nState;
}

void CINFOptionSystem::OnClickEtcRadio(int nRadioId)
{
	structOptionGameInfo* pOptionInfo = &m_struOpInfo;

	switch(nRadioId)
	{		
	case OPTION_ETC_SHOW_MOUSE:// 마우스 포인터 보이기
		{
			if(IS_DT(g_pShuttleChild->m_myShuttleInfo.UnitKind) == FALSE )
			{
				pOptionInfo->struSOptionSetup.sHandle ^= TRUE;
			}
			else
			{
				pOptionInfo->struSOptionSetup.sHandle = TRUE;
			}
		}
		break;
	case OPTION_ETC_HELP:// 헬프기능
		{
			pOptionInfo->struSOptionCharacter.sHelpDesk ^= TRUE;
		}
		break;
	case OPTION_ETC_OPERATOR:// 오퍼레이터 기능
		{			
			pOptionInfo->bOperator ^= TRUE;			
		}
		break;
	case OPTION_ETC_MAINTAIN:// 수평유지
		{
			pOptionInfo->struSOptionSetup.sAutoBalance ^= TRUE;
		}
		break;
	case OPTION_ETC_MOUSE_REVERSE_TB:// 마우스 상하 반전
		{
			pOptionInfo->struSOptionSetup.sMouseReversUp ^= TRUE;
		}
		break;
	case OPTION_ETC_MOUSE_REVERSE_LR:// 마우스 좌우 반전
		{
			// 2008-11-13 by bhsohn 조이스틱 작업
			// 마우스 좌우 반전없어짐
			//pOptionInfo->struSOptionSetup.sMouseReversLeft ^= TRUE;
			// end 2008-11-13 by bhsohn 조이스틱 작업
		}
		break;
	// 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
	//case OPTION_ETC_MENU_UNISTOP:// 메뉴 사용시 유닛정지
	case OPTION_ETC_PET_OP_SYS:// 메뉴 사용시 유닛정지
	// end 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
		{
			// 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
			//pOptionInfo->struSOptionSetup.sMenuBalance ^= TRUE;
			pOptionInfo->struSOptionSetup.sPetOPBalance ^= TRUE;
			// end 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
		}
		break;
	case OPTION_ETC_MUSIC:// Music플레이어 보기
		{
			pOptionInfo->struSOptionSetup.sMp3Player ^= TRUE;
		}
		break;	
	}

}
// 적용버튼
void CINFOptionSystem::OnClickApply()
{
	// 인터페이스 위치
	{
		m_struOpInfo.struSOptionEtc.stRateRect = g_pGameMain->m_pChat->m_pSystemMsgW->GetSysMsgWndRect();
	}

	// 2009. 02. 03 by ckPark 채팅창 인터페이스 크기 저장
	m_struOpInfo.struSOptionEtc.stChatRect	= g_pGameMain->m_pChat->GetChatWndRect();
	// end 2009. 02. 03 by ckPark 채팅창 인터페이스 크기 저장

	// 시야거리변경
	BOOL bSetFogLevel = FALSE;
	if(m_pSOptionOld.sTerrainRender != m_struOpInfo.struSOptionSetup.sTerrainRender)
	{
		bSetFogLevel = TRUE;		
	}	
	// 감마값변경
	if(m_pSOptionOld.sGammaCtrl != m_struOpInfo.struSOptionSetup.sGammaCtrl)
	{
		UpdateGamma(m_struOpInfo.struSOptionSetup.sGammaCtrl);
	}
	// 최소 프레임 틀림
	if(m_pSOptionOld.sLowQuality != m_struOpInfo.struSOptionSetup.sLowQuality)
	{
		bSetFogLevel = TRUE;
		// 최소 프레임 모드를 키면 리소스를 리로드한다. 	
		g_pD3dApp->ReLoadEnemyRenderList();		
	}	

	// 시점 변환
	if(m_pSOptionOld.sEyePt != m_struOpInfo.struSOptionSetup.sEyePt)	
	{
		if(m_struOpInfo.struSOptionSetup.sEyePt)
		{
			if(g_pShuttleChild->m_dwState == _LANDED || g_pShuttleChild->m_bIsAir == FALSE)
			{
				g_pShuttleChild->m_bLandingOldCamtypeFPS = TRUE;
			}
			else
			{
				g_pD3dApp->m_pCamera->SetCamType( MODE_CAMERA_TYPE_FPS );
			}			
		}
		else
		{
			if(g_pShuttleChild->m_bLandingOldCamtypeFPS != TRUE)
			{
				g_pD3dApp->m_pCamera->SetCamType( MODE_CAMERA_TYPE_NORMAL );
			}

		}		
	}

	// Mp3플레이 변경
	if(m_pSOptionOld.sMp3Player != m_struOpInfo.struSOptionSetup.sMp3Player)	
	{
		g_pGameMain->m_bMp3PlayFlag = m_struOpInfo.struSOptionSetup.sMp3Player;
	}
	
	// 인터페이스 모두 감추기 버튼
	{
//		BOOL bShowInter = m_struOpInfo.struSOptionEtc.bRadioInfo[OPTION_RADIO_INTERFACE_HIDE];
//		g_pInterface->SetScreenShotMode(bShowInter);
		// 인터페이스 숨기기 보이기
		BOOL bShowInter = !m_struOpInfo.struSOptionEtc.bRadioInfo[OPTION_RADIO_INTERFACE_HIDE];
		g_pInterface->SetShowInterface(bShowInter);
	}	

	if(bSetFogLevel)
	{		
		SetFogLevel( g_pShuttleChild->m_myShuttleInfo.MapChannelIndex.MapIndex, TRUE );
	}

	memcpy(g_pSOption, &m_struOpInfo.struSOptionSetup, sizeof(sOPTION_SYSTEM));		
	memcpy(g_pSOptionCharacter, &m_struOpInfo.struSOptionCharacter, sizeof(sOPTION_CHARACTER));
	// 옵션 ETC메뉴
	memcpy(g_pSOptionEtc, &m_struOpInfo.struSOptionEtc, sizeof(sOPTION_ETC));

	// 2009-02-02 by bhsohn 셋업정보 제대로 안되는 버그 수정
	memcpy(&m_pSOptionOld, g_pSOption, sizeof(sOPTION_SYSTEM));
	// end 2009-02-02 by bhsohn 셋업정보 제대로 안되는 버그 수정

	{
		// 오퍼레이터 변수
		g_pInterface->SetOperatorMode(m_struOpInfo.bOperator);
	}

	// 2008-11-06 by bhsohn 마우스 가두기 모드 보완
	g_pD3dApp->RefreshMouseMode();
	// end 2008-11-06 by bhsohn 마우스 가두기 모드 보완
	

	// 저장
	g_pInterface->SaveOptionFile();
}

void CINFOptionSystem::UpdateGamma(int nGama)
{
	FLOG( "CINFSystem::UpdateGamma(int nGama)" );
    D3DGAMMARAMP	D3dGammaRamp;
    WORD			dwGamma = 0;

	if(nGama == 5)
		nGama = 256;
	else if(nGama == 4)
		nGama = 256;
	else if(nGama == 3)
		nGama = 256;
	else if(nGama == 2)
		nGama = 256;
	else if(nGama == 1)
		nGama = 256;
	else if(nGama == 0)
		nGama = 256;
	else if(nGama == -1)
		nGama = 216;
	else if(nGama == -2)
		nGama = 192;
	else if(nGama == -3)
		nGama = 176;
	else
		nGama = 168;

    ZeroMemory( &D3dGammaRamp, sizeof(D3dGammaRamp) );
	// 2005-01-04 by jschoi
//	g_pD3dDev->GetGammaRamp(&D3dGammaRamp ) ;
	g_pD3dDev->GetGammaRamp(0, &D3dGammaRamp ) ;

    for( int iColor = 0; iColor < 256; iColor++ )
    {
        D3dGammaRamp.red[iColor]   = dwGamma;
        D3dGammaRamp.green[iColor] = dwGamma;
        D3dGammaRamp.blue[iColor]  = dwGamma;

        dwGamma += (WORD)nGama ;
    }

	// 2005-01-04 by jschoi
//	g_pD3dDev->SetGammaRamp( D3DSGR_NO_CALIBRATION  , &D3dGammaRamp ) ;
	g_pD3dDev->SetGammaRamp(0, D3DSGR_NO_CALIBRATION  , &D3dGammaRamp ) ;
}

structOptionGameInfo* CINFOptionSystem::GetSystemOption()
{
	return &m_struOpInfo;
}

void CINFOptionSystem::RefreshShowInterface(BOOL bShowInterface)
{
	if(!IsOptionShow())
	{
		return;
	}
	m_struOpInfo.struSOptionEtc.bRadioInfo[OPTION_RADIO_INTERFACE_HIDE] = bShowInterface;	
	// 라디오 버튼 갱신
	UpdateOptionInterface(&m_struOpInfo);
}



// 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템
void	CINFOptionSystem::EnableLogOffBtn( BOOL bEnable )
{
	// 인피 던젼상에서는 로그오프 막고 메인필드서버로 갈때 다시 복수
	m_pOptionLogOff->EnableBtn( bEnable );

	// 2009-05-06 by bhsohn 중국 로그오프창 막음
	#if defined(LANGUAGE_CHINA) 
		#ifndef TAIWAN_RELEASE
			m_pOptionLogOff->EnableBtn(FALSE);
		#endif
	#endif
	// end 2009-05-06 by bhsohn 중국 로그오프창 막음
}
// end 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템




// 2008-11-13 by bhsohn 조이스틱 작업
void CINFOptionSystem::OnClickJoystciOption()
{
	BOOL bShow = g_pGameMain->IsShowOpJoystick();
	bShow ^= TRUE;
	g_pGameMain->ShowOpJoystick(bShow);
}