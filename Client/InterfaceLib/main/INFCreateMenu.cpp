// INFCreateMenu.cpp: implementation of the CINFCreateMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RangeTime.h"
#include "INFUnitCreateInfo.h"
#include "INFCreateMenu.h"
#include "AtumApplication.h"
#include "oleauto.h"
#include "INFSelect.h"
#include "D3DHanFont.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "AbuseFilter.h"
#include "INFWindow.h"
#include "INFSelectBack.h"
#include "INFPilotFace.h"
#include "FieldWinSocket.h"
#include "INFSelectMenu.h"
#include "AtumSJ.h"
#include "AtumSound.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "dxutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CREATE_FONT_COLOR		RGB(222,222,222)

#define CRE_BUTTON_STATE_UP		0
#define CRE_BUTTON_STATE_DOWN	1
#define CRE_BUTTON_STATE_NORMAL	2

#define POS_CRE_TITLE_X		g_pD3dApp->GetBackBufferDesc().Width /2 - 294/2
#define POS_CRE_BACK_X		g_pD3dApp->GetBackBufferDesc().Width /2 - 640/2	
#define POS_CRE_BACK_Y		g_pD3dApp->GetBackBufferDesc().Height - 148

#define POS_CRE_CHAR_FACE_X	POS_CRE_BACK_X+46
#define POS_CRE_CHAR_FACE_Y	POS_CRE_BACK_Y+26

// 2005-07-05 by ispark
// CreateMenu UI 변경에 따른 좌표 수정
//#define POS_CRE_OK_START_X		POS_CRE_BACK_X+448
#define POS_CRE_OK_START_Y		POS_CRE_BACK_Y+67
//#define POS_CRE_CANCEL_START_X	POS_CRE_BACK_X+525
#define POS_CRE_CANCEL_START_Y	POS_CRE_BACK_Y+67
#define POS_CRE_OK_START_X		POS_CRE_BACK_X+411
#define POS_CRE_CANCEL_START_X	POS_CRE_BACK_X+488

#define POS_CRE_LEFT_START_X		POS_CRE_BACK_X-21
#define POS_CRE_LEFT_START_Y		POS_CRE_BACK_Y+61
#define POS_CRE_RIGHT_START_X		POS_CRE_BACK_X+108
#define POS_CRE_RIGHT_START_Y		POS_CRE_BACK_Y+61

#define CRE_BUTTON_OK		0
#define CRE_BUTTON_CANCEL	1
#define CRE_BUTTON_LEFT		2
#define CRE_BUTTON_RIGHT	3

#define CRE_SIZE_BUTTON_X(i)	(i > 1 ? 28 : 77)
#define CRE_SIZE_BUTTON_Y(i)	(i > 1 ? 36 : 36)

#define POS_CRE_CHARACTER_INFO_START_X	256
#define DISTANCE_CRE_CHARACTER_INFO_X	88
#define DISTANCE_CRE_CHARACTER_INFO_Y	18

// 캐릭터 추가시 아래 숫자를 증가시켜야 한다.
//#define CRE_FEMALE_LAST_NUMBER	3
//#define CRE_MAN_LAST_NUMBER		103

#define CREATE_CHARACTER_INFO_RACE		0	// 종족

#define CREATE_CHARACTER_INFO_DODGE		2	// 회피
#define CREATE_CHARACTER_INFO_ATTACK	3	// 공격
#define CREATE_CHARACTER_INFO_SOUL		4	// 감응
#define CREATE_CHARACTER_INFO_FUEL		5	// 연료
#define CREATE_CHARACTER_INFO_DEFENSE	6	// 방어
#define CREATE_CHARACTER_INFO_ENDURANCE	7	// 내구

#define CRE_CHANGE_SHOW_CURSOR_TIME		0.7f

#define CREATE_CHARACTER_INFO_A			0
#define CREATE_CHARACTER_INFO_B			1
#define CREATE_CHARACTER_INFO_M			3
#define CREATE_CHARACTER_INFO_I			2

#define CREATE_CHARACTER_INFO_UNIT_STYLE_U	-1
#define CREATE_CHARACTER_INFO_UNIT_STYLE_A	0
#define CREATE_CHARACTER_INFO_UNIT_STYLE_D	1
#define CREATE_CHARACTER_INFO_UNIT_STYLE_F	2

#define CREATE_CHARACTER_INFO_RADIO_DEF		1
#define CREATE_CHARACTER_INFO_RADIO_SEL		0

#define CREATE_CHARACTER_FOCUS_NAME			0
#define CREATE_CHARACTER_FOCUS_STEC			1
#define CREATE_CHARACTER_FOCUS_NAME_UNABLE	2
#define CREATE_CHARACTER_FOCUS_SAME_NAME	3
#define CREATE_CHARACTER_FOCUS_NONE			-1

#define CREATE_CHARACTER_INFO_STAT_X		((g_pD3dApp->GetBackBufferDesc().Width - 400)/2)
#define CREATE_CHARACTER_INFO_STAT_Y		(g_pD3dApp->GetBackBufferDesc().Height-217)

// 2006-03-07 by ispark, 언어에 따라 위치 수정
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn 태국 버전 추가
	//#define POS_CRE_CHARACTER_NAME_X		215//243
	#ifdef INNOVA_RELEASE
		#define POS_CRE_CHARACTER_NAME_X		225//243	// 2008-09-18 by bhsohn 러시아 캐릭 생성창에서 캐릭입력 위치 변경
	#else
		#define POS_CRE_CHARACTER_NAME_X		215//243
	#endif
	#define POS_CRE_CHARACTER_NAME_Y		28//32
	#define POS_CRE_CHARACTER_INFO_START_Y	48//50
	#define CREATE_CHARACTER_INFO_RACE_X	25
	#define CREATE_CHARACTER_FOCUS_NAME_X	207
#else
#define POS_CRE_CHARACTER_NAME_X		243
#define POS_CRE_CHARACTER_NAME_Y		28//32
#define POS_CRE_CHARACTER_INFO_START_Y	47//48//50		// 2006-08-11 by dgwoo캐릭터 생성시 Y값 위치 변경.
#define CREATE_CHARACTER_INFO_RACE_X	30
#define CREATE_CHARACTER_FOCUS_NAME_X	232
#endif
CINFCreateMenu::CINFCreateMenu(CAtumNode* pParent)
{
	FLOG( "CINFCreateMenu(CAtumNode* pParent)" );
	m_pParent = pParent;
	m_bRestored = FALSE;
	m_pGameData = NULL;

	// 2005-07-05 by ispark
	// 자동 스탯 분배 삭제
//	for(int i=0; i<CRE_CHARACTER_UNIT_NUMBER; i++)
//		m_pBack[i] = NULL;
	m_pBack = NULL;
//	for(i=0; i<CRE_CHARACTER_RADIO_BUTTON_NUMBER; i++)
//		m_pImgRadio[i] = NULL;
	
	m_pTitle = NULL;
	m_pImgFocus[0] = NULL;
	m_pImgFocus[1] = NULL;
	m_pImgFocus[2] = NULL;
	m_pImgFocus[3] = NULL;
	int i;
	for(i=0;i<9;i++)
		m_pImgToolTip[i] = NULL;
	memset(&m_createUnit, 0x00, sizeof(MSG_FC_CHARACTER_CREATE));

	for(i=0;i<2;i++)
	{
		m_pButton[CRE_BUTTON_OK][i] = NULL;
		m_pButton[CRE_BUTTON_CANCEL][i] = NULL;
		m_pButton[CRE_BUTTON_LEFT][i] = NULL;
		m_pButton[CRE_BUTTON_RIGHT][i] = NULL;
	}
	m_fButtonPos[CRE_BUTTON_OK][0] = 0.0f;
	m_fButtonPos[CRE_BUTTON_OK][1] = 0.0f;
	m_fButtonPos[CRE_BUTTON_CANCEL][0] = 0.0f;
	m_fButtonPos[CRE_BUTTON_CANCEL][1] = 0.0f;
	m_fButtonPos[CRE_BUTTON_LEFT][0] = 0.0f;
	m_fButtonPos[CRE_BUTTON_LEFT][1] = 0.0f;
	m_fButtonPos[CRE_BUTTON_RIGHT][0] = 0.0f;
	m_fButtonPos[CRE_BUTTON_RIGHT][1] = 0.0f;

	m_nButtonState[CRE_BUTTON_OK] = CRE_BUTTON_STATE_NORMAL;
	m_nButtonState[CRE_BUTTON_CANCEL] = CRE_BUTTON_STATE_NORMAL;
	m_nButtonState[CRE_BUTTON_LEFT] = CRE_BUTTON_STATE_NORMAL;
	m_nButtonState[CRE_BUTTON_RIGHT] = CRE_BUTTON_STATE_NORMAL;

	// 2009-02-10 by bhsohn Japan Charcter Create
	//memset(m_strCharacterName, 0x00, SIZE_MAX_CHARACTER_NAME);
	ZERO_MEMORY(m_strCharacterName);
	// end 2009-02-10 by bhsohn Japan Charcter Create
	m_pFontCharacterName = NULL;
	memset(m_pFontCharacterInfo, 0x00, sizeof(DWORD)*CRE_CHARACTER_INFO_NUMBER);
	m_nCharacterNamePos[0] = 0;
	m_nCharacterNamePos[1] = 0;
	memset(*m_nCharacterInfoPos, 0x00, sizeof(DWORD)*SEL_CHARACTER_INFO_NUMBER*2);

	m_bShowCursor = FALSE;
	m_fChangeShowCursorTime = 0.0f;

	m_bBlocking = FALSE;
	m_nSelectUnit = UNITKIND_BGEAR;
	for(i=0; i<CREATE_CHARACTER_RADIO_ALL_AUTTON; i++)
		m_nRadioButton[i] = CREATE_CHARACTER_INFO_RADIO_DEF;
//	m_nSelectUnitStyle = CREATE_CHARACTER_INFO_UNIT_STYLE_U;	// 2005-07-04 by ispark 자동 스탯 분배 삭제
	m_nSelectUnitStyle = CREATE_CHARACTER_INFO_UNIT_STYLE_F;
	m_nFocus = CREATE_CHARACTER_FOCUS_NONE;
	m_nFocusStat  = CREATE_CHARACTER_FOCUS_NONE;
//	m_nCreateUnitStat = -1;
	m_nCreateUnitStat = AUTOSTAT_TYPE_FREESTYLE;				// 2005-07-04 by ispark 자동 스탯 분배 삭제
//	m_nRenderToolTipIndex = -1;									// 2005-07-04 by ispark 자동 스탯 분배 삭제
	for(i=0; i<3; i++)
		m_pImgTextPopUp[i] = NULL;
	// 2005-09-12 by ispark
	// 사용할 수 있는 FACE 넘버를 부여한다.
	for(i = 0; i < CRE_TOTAL_NUMBER; i++)
		m_nFaceUseIndex[i] = -1;
	//여자 캐릭터 
	m_nFaceUseIndex[0] = 0;
	m_nFaceUseIndex[1] = 1;
	m_nFaceUseIndex[2] = 2;
	m_nFaceUseIndex[3] = 3;
	m_nFaceUseIndex[4] = 4;
	//남자 캐릭터
	m_nFaceUseIndex[5] = 100;
	m_nFaceUseIndex[6] = 101;
	m_nFaceUseIndex[7] = 102;
	m_nFaceUseIndex[8] = 103;
	m_nFaceUseIndex[9] = 104;
	

	// 남자를 기준으로 잡았다
	m_nChoiseFaceIndex = 6;
	m_createUnit.PilotFace = m_nFaceUseIndex[m_nChoiseFaceIndex];
}

CINFCreateMenu::~CINFCreateMenu()
{
	FLOG( "~CINFCreateMenu()" );

	// 2005-07-05 by ispark
	// 자동 스탯 분배 삭제
//	for(int i=0; i<CRE_CHARACTER_UNIT_NUMBER; i++)
//		SAFE_DELETE( m_pBack[i] );
	SAFE_DELETE(m_pBack);
//	for(i=0; i<CRE_CHARACTER_RADIO_BUTTON_NUMBER; i++)
//		SAFE_DELETE( m_pImgRadio[i] );

	SAFE_DELETE( m_pTitle );
	SAFE_DELETE( m_pImgFocus[0] );
	SAFE_DELETE( m_pImgFocus[1] );
	SAFE_DELETE( m_pImgFocus[2] );
	SAFE_DELETE( m_pImgFocus[3] );
	int i;
	for(i=0;i<9;i++)
		SAFE_DELETE( m_pImgToolTip[i]);
	for(i=0;i<CRE_BUTTON_NUMBER;i++)
	{
		SAFE_DELETE(m_pButton[i][0]);
		SAFE_DELETE(m_pButton[i][1]);
	}
	SAFE_DELETE( m_pFontCharacterName );
	for(i=0;i<SEL_CHARACTER_INFO_NUMBER; i++)
		SAFE_DELETE( m_pFontCharacterInfo[i] );
	for(i=0; i<3; i++)
		SAFE_DELETE(m_pImgTextPopUp[i]);
}

HRESULT CINFCreateMenu::InitDeviceObjects()
{
	FLOG( "CINFCreateMenu::InitDeviceObjects()" );
	char buf[32];
	DataHeader * pDataHeader;

	m_pFontCharacterName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),10, D3DFONT_ZENABLE,  TRUE,512,32);
	m_pFontCharacterName->InitDeviceObjects(g_pD3dDev);

	int i;
	for(i=0;i<CRE_CHARACTER_INFO_NUMBER; i++)
	{
		m_pFontCharacterInfo[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,128,32);
		m_pFontCharacterInfo[i]->InitDeviceObjects(g_pD3dDev);
	}

	// 2005-07-05 by ispark
	// 자동 스탯 분배 삭제 
//	for(i=0; i<CRE_CHARACTER_UNIT_NUMBER; i++)
//	{
		wsprintf(buf, "creback");
//		m_pBack[i] = new CINFImage;
//		pDataHeader = FindResource(buf);
//		m_pBack[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		m_pBack = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pBack->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
//	}

//	m_pImgRadio[0] = new CINFImage;
//	pDataHeader = FindResource("radio_a");
//	m_pImgRadio[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
//	m_pImgRadio[1] = new CINFImage;
//	pDataHeader = FindResource("radio_b");
//	m_pImgRadio[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	
	m_pImgFocus[0] = new CINFImage;
	pDataHeader = FindResource("selfocn");
	m_pImgFocus[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgFocus[1] = new CINFImage;
	pDataHeader = FindResource("selfocs");
	m_pImgFocus[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgFocus[2] = new CINFImage;
	pDataHeader = FindResource("selfoc1");
	m_pImgFocus[2]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgFocus[3] = new CINFImage;
	pDataHeader = FindResource("selfoc2");
	m_pImgFocus[3]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	for(i=0;i<9;i++)
	{
		wsprintf( buf, "toimg%d",i);
		m_pImgToolTip[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgToolTip[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}	

	m_pTitle = new CINFImage;
	pDataHeader = FindResource("cretitle");
	m_pTitle->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	
	for(i=0;i<CRE_BUTTON_NUMBER;i++)
	{
		for(int j=0;j<2;j++)
		{
			wsprintf( buf, "crebtn%d%d",i,j);
			m_pButton[i][j] =new CINFImage;
			pDataHeader = FindResource(buf);
			if(pDataHeader)
				m_pButton[i][j]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
//			else
//				ERROR Reporting ( exit )
		}
	}
	
	for(i=0; i<3; i++)
	{
		wsprintf(buf, "boxtip%d",i);		
		m_pImgTextPopUp[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pImgTextPopUp[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	}

	return S_OK ;
}


HRESULT CINFCreateMenu::RestoreDeviceObjects()
{
	FLOG( "CINFCreateMenu::RestoreDeviceObjects()" );
	m_pFontCharacterName->RestoreDeviceObjects();
	m_nCharacterNamePos[0] = POS_CRE_BACK_X+POS_CRE_CHARACTER_NAME_X;
	m_nCharacterNamePos[1] = POS_CRE_BACK_Y+POS_CRE_CHARACTER_NAME_Y;
	int i;
	for(i=0;i<CRE_CHARACTER_INFO_NUMBER; i++)
	{
		m_pFontCharacterInfo[i]->RestoreDeviceObjects();
		m_nCharacterInfoPos[i][0] = POS_CRE_BACK_X+POS_CRE_CHARACTER_INFO_START_X+DISTANCE_CRE_CHARACTER_INFO_X*(i%2);
		m_nCharacterInfoPos[i][1] = POS_CRE_BACK_Y+POS_CRE_CHARACTER_INFO_START_Y+DISTANCE_CRE_CHARACTER_INFO_Y*(i/2);
	}

	// 2005-07-05 by ispark
	// 자동 스탯 분배 삭제
//	for(i=0; i<CRE_CHARACTER_UNIT_NUMBER; i++)
//		m_pBack[i]->RestoreDeviceObjects();
	m_pBack->RestoreDeviceObjects();
//	for(i=0; i<CRE_CHARACTER_RADIO_BUTTON_NUMBER; i++)
//		m_pImgRadio[i]->RestoreDeviceObjects();

	m_pTitle->RestoreDeviceObjects();
	m_pImgFocus[0]->RestoreDeviceObjects();
	m_pImgFocus[1]->RestoreDeviceObjects();
	m_pImgFocus[2]->RestoreDeviceObjects();
	m_pImgFocus[3]->RestoreDeviceObjects();
	for(i=0;i<9;i++)
		m_pImgToolTip[i]->RestoreDeviceObjects();
	for(i=0;i<CRE_BUTTON_NUMBER;i++)
	{
		m_pButton[i][0]->RestoreDeviceObjects();
		m_pButton[i][1]->RestoreDeviceObjects();
	}
	
	m_fButtonPos[CRE_BUTTON_OK][0] = POS_CRE_OK_START_X;
	m_fButtonPos[CRE_BUTTON_OK][1] = POS_CRE_OK_START_Y;
	m_fButtonPos[CRE_BUTTON_CANCEL][0] = POS_CRE_CANCEL_START_X;
	m_fButtonPos[CRE_BUTTON_CANCEL][1] = POS_CRE_CANCEL_START_Y;
	m_fButtonPos[CRE_BUTTON_LEFT][0] = POS_CRE_LEFT_START_X;
	m_fButtonPos[CRE_BUTTON_LEFT][1] = POS_CRE_LEFT_START_Y;
	m_fButtonPos[CRE_BUTTON_RIGHT][0] = POS_CRE_RIGHT_START_X;
	m_fButtonPos[CRE_BUTTON_RIGHT][1] = POS_CRE_RIGHT_START_Y;

	for(i=0; i<3; i++)
	{
		if(m_pImgTextPopUp[i])
			m_pImgTextPopUp[i]->RestoreDeviceObjects();
	}
	
	m_bRestored = TRUE;
	return S_OK ;
}

HRESULT CINFCreateMenu::InvalidateDeviceObjects()
{
	FLOG( "CINFCreateMenu::InvalidateDeviceObjects()" );
	m_pFontCharacterName->InvalidateDeviceObjects();
	int i;
	for(i=0;i<CRE_CHARACTER_INFO_NUMBER; i++)
	{
		m_pFontCharacterInfo[i]->InvalidateDeviceObjects();
	}

	// 2005-07-05 by ispark
	// 자동 스탯 분배 삭제
//	for(i=0; i<CRE_CHARACTER_UNIT_NUMBER; i++)
//		m_pBack[i]->InvalidateDeviceObjects();
	m_pBack->InvalidateDeviceObjects();
//	for(i=0; i<CRE_CHARACTER_RADIO_BUTTON_NUMBER; i++)
//		m_pImgRadio[i]->InvalidateDeviceObjects();

	m_pTitle->InvalidateDeviceObjects();
	m_pImgFocus[0]->InvalidateDeviceObjects();
	m_pImgFocus[1]->InvalidateDeviceObjects();
	m_pImgFocus[2]->InvalidateDeviceObjects();
	m_pImgFocus[3]->InvalidateDeviceObjects();
	for(i=0;i<9;i++)
		m_pImgToolTip[i]->InvalidateDeviceObjects();
	for(i=0;i<CRE_BUTTON_NUMBER;i++)
	{
		m_pButton[i][0]->InvalidateDeviceObjects();
		m_pButton[i][1]->InvalidateDeviceObjects();
	}
	for(i=0; i<3; i++)
	{
		if ( m_pImgTextPopUp[i] )
			m_pImgTextPopUp[i]->InvalidateDeviceObjects();
	}
	
	m_bRestored = FALSE;
	return S_OK ;
}

HRESULT CINFCreateMenu::DeleteDeviceObjects()
{
	FLOG( "CINFCreateMenu::DeleteDeviceObjects()" );
	m_pFontCharacterName->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontCharacterName);
	int i;
	for(i=0;i<CRE_CHARACTER_INFO_NUMBER; i++)
	{
		m_pFontCharacterInfo[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontCharacterInfo[i]);
	}

	// 2005-07-05 by ispark
	// 자동 스탯 분배 삭제
//	for(i=0; i<CRE_CHARACTER_UNIT_NUMBER; i++)
//	{
//		m_pBack[i]->DeleteDeviceObjects();
//		SAFE_DELETE(m_pBack[i]);
//	}
	SAFE_DELETE(m_pBack);
//	for(i=0; i<CRE_CHARACTER_RADIO_BUTTON_NUMBER; i++)
//	{
//		m_pImgRadio[i]->DeleteDeviceObjects();
//		SAFE_DELETE(m_pImgRadio[i]);
//	}		

	m_pTitle->DeleteDeviceObjects();
	SAFE_DELETE(m_pTitle);
	m_pImgFocus[0]->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgFocus[0]);
	m_pImgFocus[1]->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgFocus[1]);
	m_pImgFocus[2]->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgFocus[2]);
	m_pImgFocus[3]->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgFocus[3]);
	for(i=0;i<9;i++)
	{
		m_pImgToolTip[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgToolTip[i]);
	}
	for(i=0;i<CRE_BUTTON_NUMBER;i++)
	{
		m_pButton[i][0]->DeleteDeviceObjects();
		m_pButton[i][1]->DeleteDeviceObjects();
		SAFE_DELETE(m_pButton[i][0]);
		SAFE_DELETE(m_pButton[i][1]);
	}
	for(i=0; i<3; i++)
	{
		if ( m_pImgTextPopUp[i] )
			m_pImgTextPopUp[i]->DeleteDeviceObjects();

		SAFE_DELETE(m_pImgTextPopUp[i]);
	}


	return S_OK ;
}

void CINFCreateMenu::Tick()
{
	FLOG( "CINFCreateMenu::Tick()" );
	m_fChangeShowCursorTime += g_pD3dApp->GetElapsedTime();
	if(m_fChangeShowCursorTime > CRE_CHANGE_SHOW_CURSOR_TIME)
	{
		m_bShowCursor = !m_bShowCursor;
		m_fChangeShowCursorTime = 0;
	}
}

void CINFCreateMenu::Render()
{
	FLOG( "CINFCreateMenu::Render()" );
	m_pTitle->Move(POS_CRE_TITLE_X, 0);
	m_pTitle->Render();	

	// 2005-07-05 by ispark
	// 자동 스탯 분배 삭제
//	m_pBack[m_nSelectUnit]->Move(POS_CRE_BACK_X, POS_CRE_BACK_Y);
//	m_pBack[m_nSelectUnit]->Render();
	m_pBack->Move(POS_CRE_BACK_X, POS_CRE_BACK_Y);
	m_pBack->Render();
	for(int i=0;i<CRE_BUTTON_NUMBER;i++)
	{
		if(m_nButtonState[i] != CRE_BUTTON_STATE_NORMAL)
		{
			m_pButton[i][m_nButtonState[i]]->Move(m_fButtonPos[i][0]+37,m_fButtonPos[i][1]);
			m_pButton[i][m_nButtonState[i]]->Render();
		}
	}
	CINFImage* pFace = ((CINFSelect*)m_pParent)->m_pPilotFace->FindPilotImage(m_createUnit.PilotFace);
	if(pFace)
	{
		pFace->Move(POS_CRE_CHAR_FACE_X,POS_CRE_CHAR_FACE_Y);
		pFace->Render();
	}
	char buf[1024];
	memset(buf, 0x00, sizeof(buf));
	if(m_bShowCursor)
		wsprintf(buf, "%s_", m_strCharacterName);
	else if(strlen(m_strCharacterName)>0)
		strcpy( buf, m_strCharacterName);
	if(buf[0])
	{
		m_pFontCharacterName->DrawText(m_nCharacterNamePos[0], m_nCharacterNamePos[1], CREATE_FONT_COLOR, buf, 0L);
	}

	if(SET_CREATEMENU_CANDIDATE == g_nRenderCandidate)
		g_pD3dApp->RenderCandidate(m_nCharacterNamePos[0], m_nCharacterNamePos[1]-15);

	// 2007-05-21 by bhsohn China IME Working
	g_pD3dApp->RenderIMEType(m_nCharacterNamePos[0], m_nCharacterNamePos[1]-15);

//	strcpy( buf, GetRaceString(m_createUnit.Race));
	if(COMPARE_RACE(m_createUnit.Race, RACE_DECA))
		strcpy( buf, STRMSG_C_SELECT_0001);//"데카"
	if(COMPARE_RACE(m_createUnit.Race, RACE_BATTALUS))
		strcpy( buf, STRMSG_C_SELECT_0002);//"바탈러스"
	if(COMPARE_RACE(m_createUnit.Race, RACE_DEMO))
		strcpy( buf, STRMSG_C_SELECT_0003);//"데모"
	if(COMPARE_RACE(m_createUnit.Race, RACE_GAMEMASTER))
		strcpy( buf, STRMSG_C_SELECT_0004);//"게임마스터"
	if(COMPARE_RACE(m_createUnit.Race, RACE_OPERATION))
		strcpy( buf, STRMSG_C_SELECT_0005);//"관리자"
	if(COMPARE_RACE(m_createUnit.Race, RACE_GUEST))
		strcpy( buf, STRMSG_C_SELECT_0006);//"게스트"
	if(COMPARE_RACE(m_createUnit.Race, RACE_MONITOR))
		strcpy( buf, STRMSG_C_SELECT_0007);//"모니터"

	m_pFontCharacterInfo[CREATE_CHARACTER_INFO_RACE]->DrawText(m_nCharacterInfoPos[CREATE_CHARACTER_INFO_RACE][0]-CREATE_CHARACTER_INFO_RACE_X, m_nCharacterInfoPos[CREATE_CHARACTER_INFO_RACE][1], CREATE_FONT_COLOR, buf, 0L);
	wsprintf( buf, "%d", m_createUnit.GearStat1.AttackPart);
	m_pFontCharacterInfo[CREATE_CHARACTER_INFO_ATTACK]->DrawText(m_nCharacterInfoPos[CREATE_CHARACTER_INFO_ATTACK][0], m_nCharacterInfoPos[CREATE_CHARACTER_INFO_ATTACK][1], CREATE_FONT_COLOR, buf, 0L);
	wsprintf( buf, "%d", m_createUnit.GearStat1.DefensePart);
	m_pFontCharacterInfo[CREATE_CHARACTER_INFO_ENDURANCE]->DrawText(m_nCharacterInfoPos[CREATE_CHARACTER_INFO_ENDURANCE][0], m_nCharacterInfoPos[CREATE_CHARACTER_INFO_ENDURANCE][1], CREATE_FONT_COLOR, buf, 0L);
	wsprintf( buf, "%d", m_createUnit.GearStat1.FuelPart);
	m_pFontCharacterInfo[CREATE_CHARACTER_INFO_FUEL]->DrawText(m_nCharacterInfoPos[CREATE_CHARACTER_INFO_FUEL][0], m_nCharacterInfoPos[CREATE_CHARACTER_INFO_FUEL][1], CREATE_FONT_COLOR, buf, 0L);
	wsprintf( buf, "%d", m_createUnit.GearStat1.SoulPart);
	m_pFontCharacterInfo[CREATE_CHARACTER_INFO_SOUL]->DrawText(m_nCharacterInfoPos[CREATE_CHARACTER_INFO_SOUL][0], m_nCharacterInfoPos[CREATE_CHARACTER_INFO_SOUL][1], CREATE_FONT_COLOR, buf, 0L);
	wsprintf( buf, "%d", m_createUnit.GearStat1.DodgePart);
	m_pFontCharacterInfo[CREATE_CHARACTER_INFO_DODGE]->DrawText(m_nCharacterInfoPos[CREATE_CHARACTER_INFO_DODGE][0], m_nCharacterInfoPos[CREATE_CHARACTER_INFO_DODGE][1], CREATE_FONT_COLOR, buf, 0L);
	wsprintf( buf, "%d", m_createUnit.GearStat1.ShieldPart);
	m_pFontCharacterInfo[CREATE_CHARACTER_INFO_DEFENSE]->DrawText(m_nCharacterInfoPos[CREATE_CHARACTER_INFO_DEFENSE][0], m_nCharacterInfoPos[CREATE_CHARACTER_INFO_DEFENSE][1], CREATE_FONT_COLOR, buf, 0L);

	// 2005-07-04 by ispark 
	// 자동 스탯 분배 삭제
	// Render Radio Button
//	for(i=0; i<CREATE_CHARACTER_RADIO_ALL_AUTTON; i++)
//	{
//		m_pImgRadio[m_nRadioButton[i]]->Move(POS_CRE_BACK_X+390, POS_CRE_BACK_Y+70+(i*17));
//		m_pImgRadio[m_nRadioButton[i]]->Render();
//	}

	// 이름이 없거나 이름이 같거나 이름에 형식이 틀릴때
	if(m_nFocus != CREATE_CHARACTER_FOCUS_NONE)
	{
		if(m_nFocus == CREATE_CHARACTER_FOCUS_NAME)
		{
			m_pImgFocus[CREATE_CHARACTER_FOCUS_NAME]->Move(POS_CRE_BACK_X+CREATE_CHARACTER_FOCUS_NAME_X, POS_CRE_BACK_Y-10);
			m_pImgFocus[CREATE_CHARACTER_FOCUS_NAME]->Render();
		}
		else if(m_nFocus == CREATE_CHARACTER_FOCUS_NAME_UNABLE)
		{
			m_pImgFocus[CREATE_CHARACTER_FOCUS_NAME_UNABLE]->Move(POS_CRE_BACK_X+CREATE_CHARACTER_FOCUS_NAME_X, POS_CRE_BACK_Y-10);
			m_pImgFocus[CREATE_CHARACTER_FOCUS_NAME_UNABLE]->Render();
		}
		else if(m_nFocus == CREATE_CHARACTER_FOCUS_SAME_NAME)
		{
			m_pImgFocus[CREATE_CHARACTER_FOCUS_SAME_NAME]->Move(POS_CRE_BACK_X+CREATE_CHARACTER_FOCUS_NAME_X, POS_CRE_BACK_Y-10);
			m_pImgFocus[CREATE_CHARACTER_FOCUS_SAME_NAME]->Render();
		}
	}
	
	if(m_nFocusStat == CREATE_CHARACTER_FOCUS_STEC)
	{
		m_pImgFocus[CREATE_CHARACTER_FOCUS_STEC]->Move(POS_CRE_BACK_X+376,POS_CRE_BACK_Y+4);
		m_pImgFocus[CREATE_CHARACTER_FOCUS_STEC]->Render();
	}	

	// 2005-07-04 by ispark 
	// 자동 스탯 분배 삭제
	// 툴팁관련 렌더링
//	if(m_nRenderToolTipIndex != -1)
//	{
//		m_pImgToolTip[m_nRenderToolTipIndex]->Move(CREATE_CHARACTER_INFO_STAT_X,CREATE_CHARACTER_INFO_STAT_Y);
//		m_pImgToolTip[m_nRenderToolTipIndex]->Render();
//	}
}

int CINFCreateMenu::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFCreateMenu::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
//	if(m_bBlocking)
//	{
//		return INF_MSGPROC_NORMAL;
//	}
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
 			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// 아이디나 스텟을 누르면 이미지 렌더링 해제
			if( pt.x > m_nCharacterNamePos[0] && pt.x < m_nCharacterNamePos[0] + 130 &&
				pt.y > m_nCharacterNamePos[1] && pt.y < m_nCharacterNamePos[1] + 15)
			{
				m_nFocus = CREATE_CHARACTER_FOCUS_NONE;
				break;
			}
			
			for(int i=0; i<CRE_BUTTON_NUMBER; i++)
			{
				if( pt.x > m_fButtonPos[i][0]+37 && pt.x < m_fButtonPos[i][0]+37 + CRE_SIZE_BUTTON_X(i) &&
					pt.y > m_fButtonPos[i][1] && pt.y < m_fButtonPos[i][1] + CRE_SIZE_BUTTON_Y(i) )
				{
					m_nButtonState[i] = CRE_BUTTON_STATE_DOWN;
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);
				}
				else
				{
					m_nButtonState[i] = CRE_BUTTON_STATE_NORMAL;
				}
			}

			// 2005-07-04 by ispark 
			// 자동 스탯 분배 삭제
			// Radio Button
//			for(i=0; i<CREATE_CHARACTER_RADIO_ALL_AUTTON; i++)
//			{				
//				if( pt.x > POS_CRE_BACK_X+396 && pt.x < POS_CRE_BACK_X+448 &&
//					pt.y > POS_CRE_BACK_Y+75+(i*17)  && pt.y < POS_CRE_BACK_Y+87+(i*17))
//				{
//					for(int j=0; j<CREATE_CHARACTER_RADIO_ALL_AUTTON; j++)
//						m_nRadioButton[j] = CREATE_CHARACTER_INFO_RADIO_DEF;
//					m_nRadioButton[i] = CREATE_CHARACTER_INFO_RADIO_SEL;
//					m_nSelectUnitStyle = i;
//					m_nFocusStat = CREATE_CHARACTER_FOCUS_NONE;
//					SetCharacterUnitStyle();
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
			for(int i=0; i<CRE_BUTTON_NUMBER; i++)
			{
				if( pt.x > m_fButtonPos[i][0]+37 && pt.x < m_fButtonPos[i][0]+37 + CRE_SIZE_BUTTON_X(i) &&
					pt.y > m_fButtonPos[i][1] && pt.y < m_fButtonPos[i][1] + CRE_SIZE_BUTTON_Y(i) )
				{
					if(m_nButtonState[i] == CRE_BUTTON_STATE_DOWN)
					{
						m_nButtonState[i] = CRE_BUTTON_STATE_UP;
						OnButtonClicked(i);
					}
					else
					{
						m_nButtonState[i] = CRE_BUTTON_STATE_NORMAL;
					}
				}
				else
				{
					m_nButtonState[i] = CRE_BUTTON_STATE_NORMAL;
				}
			}
			for(int i=0; i<CRE_BUTTON_NUMBER; i++)
				m_nButtonState[i] = CRE_BUTTON_STATE_NORMAL;
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			BOOL bChangeMouseState = FALSE;
//			m_nRenderToolTipIndex = -1;						// 2005-07-04 by ispark 자동 스탯 분배 삭제
			for(int i=0; i<CRE_BUTTON_NUMBER; i++)
			{
				if( pt.x > m_fButtonPos[i][0]+37 && pt.x < m_fButtonPos[i][0]+37 + CRE_SIZE_BUTTON_X(i) &&
					pt.y > m_fButtonPos[i][1] && pt.y < m_fButtonPos[i][1] + CRE_SIZE_BUTTON_Y(i) )
				{
					if(m_nButtonState[i] != CRE_BUTTON_STATE_DOWN)
					{
						m_nButtonState[i] = CRE_BUTTON_STATE_UP;
					}
					((CINFSelect*)m_pParent)->SetMouseState( SELECT_MOUSE_STATE_UP );
					bChangeMouseState = TRUE;
				}
				else
				{
					m_nButtonState[i] = CRE_BUTTON_STATE_NORMAL;
					if(!bChangeMouseState) {
						((CINFSelect*)m_pParent)->SetMouseState( SELECT_MOUSE_STATE_NORMAL ); }
				}
			}

			// 2005-07-04 by ispark 
			// 자동 스탯 분배 삭제
			// 스텟분배 툴팁
//			for(i=0; i<CREATE_CHARACTER_RADIO_ALL_AUTTON; i++)
//			{				
//				if( pt.x > POS_CRE_BACK_X+396 && pt.x < POS_CRE_BACK_X+448 &&
//					pt.y > POS_CRE_BACK_Y+75+(i*17)  && pt.y < POS_CRE_BACK_Y+87+(i*17))
//				{
//					m_nSelectUnitStyle = i;
//					SetCharacterUnitStyle(TRUE);
//				}				
//			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFCreateMenu::OnButtonClicked(int i)
{
	FLOG( "CINFCreateMenu::OnButtonClicked(int i)" );
	switch(i)
	{
	case CRE_BUTTON_OK:
		{
			// 2007-07-25 by bhsohn 유저가 튜토리얼맵에 있어서 마을로 갔을시, 첫번쨰 유저로 간주
			g_pD3dApp->EndNarrationSound();

			BOOL bFlag = FALSE;
			if(strlen(m_strCharacterName)==0)
			{
//				2005-05-13 by ydkim
//				char buf[256];
//				LoadString(NULL, IDS_MSGBOX_INPUT_NAME, buf, sizeof(buf));
//				CINFWindow* pWindow = ((CINFSelect*)m_pParent)->m_pInfWindow;
//				if(!pWindow->IsExistMsgBox(_Q_SELECT_DELETE))
//				{
//					pWindow->AddMsgBox(buf, _MESSAGE_ERROR_CREATE);
//				}
				m_nFocus = CREATE_CHARACTER_FOCUS_NAME;
				bFlag = TRUE;
			}
			else if(!ErrCheckCharacterName(m_strCharacterName))
			{
				m_nFocus = CREATE_CHARACTER_FOCUS_NAME_UNABLE;

				// 2009-02-10 by bhsohn Japan Charcter Create
				//memset(m_strCharacterName,0x00,SIZE_MAX_CHARACTER_NAME);
				ZERO_MEMORY(m_strCharacterName);
				// end 2009-02-10 by bhsohn Japan Charcter Create
				g_pD3dApp->CleanText();
				bFlag = TRUE;
			}
			
			// 2005-07-04 by ispark 
			// 자동 스탯 분배 삭제
//			if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_U || 
//					m_nCreateUnitStat == CREATE_CHARACTER_INFO_UNIT_STYLE_U)
//			{
////				2005-05-13 by ydkim
////				CINFWindow* pWindow = ((CINFSelect*)m_pParent)->m_pInfWindow;
////				if(!pWindow->IsExistMsgBox(_Q_SELECT_DELETE))
////				{
////					pWindow->AddMsgBox(STRMSG_C_SELECT_0008, _MESSAGE_ERROR_CREATE);//"스탯 분배 옵션을 선택하여 주십시오."
////				}
//				m_nFocusStat = CREATE_CHARACTER_FOCUS_STEC;
//				bFlag = TRUE;
//			}
			
			if(FALSE == bFlag) 
			{
				MSG_FC_CHARACTER_CREATE sMsg;
				memset(&sMsg,0x00,sizeof(sMsg));
				// 2009-02-10 by bhsohn Japan Charcter Create
				//strcpy(m_createUnit.CharacterName, m_strCharacterName);
				STRNCPY_MEMSET(m_createUnit.CharacterName, m_strCharacterName, SIZE_MAXUSE_CHARACTER_NAME);
				// end 2009-02-10 by bhsohn Japan Charcter Create
				sMsg = m_createUnit;
				if(ErrCheckCharacterName(sMsg.CharacterName))
				{
					sMsg.AutoStatType1 = m_nCreateUnitStat;
					sMsg.AccountUniqueNumber = g_pD3dApp->m_accountUniqueNumber;
					char buffer[SIZE_MAX_PACKET];
					int nType = T_FC_CHARACTER_CREATE;
					memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
					memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
					g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
					m_bBlocking = TRUE;

					g_pD3dApp->m_bRequestEnable = FALSE;
				}
				else
				{// 캐릭터 이름 에러
					CINFWindow* pWindow = ((CINFSelect*)m_pParent)->m_pInfWindow;
					if(!pWindow->IsExistMsgBox(_Q_SELECT_DELETE))
					{
						pWindow->AddMsgBox(STRMSG_C_SELECT_0009, _MESSAGE_ERROR_CREATE);//"올바르지 않은 이름입니다"
					}
				}
				// 2009-02-10 by bhsohn Japan Charcter Create
				//memset(m_strCharacterName,0x00,SIZE_MAX_CHARACTER_NAME);
				ZERO_MEMORY(m_strCharacterName);
				// end 2009-02-10 by bhsohn Japan Charcter Create
				g_pD3dApp->CleanText();
//				g_input.SetChangeEnterState();
				//g_pD3dApp->m_inputkey.ToggleHanEng(g_pD3dApp->GetHwnd(),IME_CMODE_NATIVE);
			}
		}
		break;
	case CRE_BUTTON_CANCEL:
		{
			// 2007-07-25 by bhsohn 유저가 튜토리얼맵에 있어서 마을로 갔을시, 첫번쨰 유저로 간주
			g_pD3dApp->EndNarrationSound();
			
			// 초기화
			// 2005-07-04 by ispark 
			// 자동 스탯 분배 삭제
			g_pSelect->m_pCreateMenu->m_nCreateUnitStat = AUTOSTAT_TYPE_FREESTYLE;
//			g_pSelect->m_pCreateMenu->m_nRenderToolTipIndex = -1;
			g_pSelect->m_pCreateMenu->m_nFocusStat = -1;
			g_pSelect->m_pCreateMenu->m_nFocus = -1;
			
			m_nButtonState[CRE_BUTTON_CANCEL] = CRE_BUTTON_STATE_NORMAL;
			((CINFSelect*)m_pParent)->m_pSelectBack->ChangeMode(SELECT_MODE);
			((CINFSelect*)m_pParent)->m_pSelectBack->m_bInitEffectItem = false;
			g_pD3dApp->DeleteEffectList();
			g_pD3dApp->ChangeGameState(_SELECT);
			m_nCreateUnitStat = AUTOSTAT_TYPE_FREESTYLE;
		}
		break;

	// 2005-07-04 by ispark
	// CRE_BUTTON_LEFT와 CRE_BUTTON_RIGHT 이 부분은 쓰고 있지 않음
	case CRE_BUTTON_LEFT:
		{
//			m_nCreateUnitStat = -1;		// 2005-07-04 by ispark 자동 스탯 분배 삭제
			// 2009-02-10 by bhsohn Japan Charcter Create
			//memset(m_strCharacterName,0x00,SIZE_MAX_CHARACTER_NAME);
			ZERO_MEMORY(m_strCharacterName);
			// end 2009-02-10 by bhsohn Japan Charcter Create
			g_pD3dApp->CleanText();

			// 2005-09-12 by ispark		Face 선택시 현재 개방된 Face만 선택
			for(int j = 0; j < CRE_TOTAL_NUMBER; j++)
			{
				m_nChoiseFaceIndex--;
				if(0 > m_nChoiseFaceIndex)
					m_nChoiseFaceIndex = CRE_TOTAL_NUMBER - 1;

				if(m_nFaceUseIndex[m_nChoiseFaceIndex] != -1)
				{
					m_createUnit.PilotFace = m_nFaceUseIndex[m_nChoiseFaceIndex];
					break;
				}
			}			
		}
		break;
	case CRE_BUTTON_RIGHT:
		{
//			m_nCreateUnitStat = -1;		// 2005-07-04 by ispark 자동 스탯 분배 삭제
			// 2009-02-10 by bhsohn Japan Charcter Create
			//memset(m_strCharacterName,0x00,SIZE_MAX_CHARACTER_NAME);
			ZERO_MEMORY(m_strCharacterName);
			// end 2009-02-10 by bhsohn Japan Charcter Create
			g_pD3dApp->CleanText();

			// 2005-09-12 by ispark		Face 선택시 현재 개방된 Face만 선택
			for(int j = 0; j < CRE_TOTAL_NUMBER; j++)
			{
				m_nChoiseFaceIndex++;
//				if(CRE_TOTAL_NUMBER <= m_nChoiseFaceIndex)
//					m_nChoiseFaceIndex = 0;
				m_nChoiseFaceIndex = m_nChoiseFaceIndex % CRE_TOTAL_NUMBER;

				if(m_nFaceUseIndex[m_nChoiseFaceIndex] != -1)
				{
					m_createUnit.PilotFace = m_nFaceUseIndex[m_nChoiseFaceIndex];
					break;
				}
			}			
		}
		break;
	}
}

void CINFCreateMenu::CharacterSet(USHORT uUnitKind)
{
	FLOG( "CINFCreateMenu::CharacterSet(USHORT uUnitKind)" );
	m_createUnit.AccountUniqueNumber = g_pD3dApp->m_accountUniqueNumber;
	strcpy( m_createUnit.CharacterName, m_strCharacterName);
	m_createUnit.UnitKind = uUnitKind;
	m_createUnit.Race = RACE_DECA;
	if(m_createUnit.PilotFace >= 100)
		m_createUnit.Gender = 1;
	else
		m_createUnit.Gender = 0;
	const GEAR_STAT_CHANGE_VALUE* pStat = CAtumSJ::GetGearStatChangeValueStruct(uUnitKind);
	m_createUnit.GearStat1.AttackPart = pStat->GearStat1.AttackPart;
	m_createUnit.GearStat1.FuelPart = pStat->GearStat1.FuelPart;
	m_createUnit.GearStat1.DefensePart = pStat->GearStat1.DefensePart;
	m_createUnit.GearStat1.SoulPart = pStat->GearStat1.SoulPart;
	m_createUnit.GearStat1.ShieldPart = pStat->GearStat1.ShieldPart;
	m_createUnit.GearStat1.DodgePart = pStat->GearStat1.DodgePart;

	// 스텟 분배 방식 
	// 2005-07-04 by ispark 
	// 자동 스탯 분배 삭제
//	m_nSelectUnitStyle	= CREATE_CHARACTER_INFO_UNIT_STYLE_U;
	m_nSelectUnitStyle	= CREATE_CHARACTER_INFO_UNIT_STYLE_F;
//	for(int j=0; j<CREATE_CHARACTER_RADIO_ALL_AUTTON; j++)
//		m_nRadioButton[j] = CREATE_CHARACTER_INFO_RADIO_DEF;
	switch(m_createUnit.UnitKind)
	{
	case UNITKIND_BGEAR:	m_nSelectUnit = CREATE_CHARACTER_INFO_B;	break;
	case UNITKIND_MGEAR:	m_nSelectUnit = CREATE_CHARACTER_INFO_M;	break;
	case UNITKIND_AGEAR:	m_nSelectUnit = CREATE_CHARACTER_INFO_A;	break;
	case UNITKIND_IGEAR:	m_nSelectUnit = CREATE_CHARACTER_INFO_I;	break;
	}
}

BOOL CINFCreateMenu::ErrCheckCharacterName(char * strName)
{
	FLOG("CAtumApplication::ErrCheckCharacterName(char * strName)");

	int strLen = strlen(strName);

	int nLen = MultiByteToWideChar(CP_ACP, 0, strName,
		strlen(strName), NULL, NULL);
	BSTR bmsg = ::SysAllocStringLen(NULL, nLen);
	if (bmsg == NULL)
		return FALSE;
	MultiByteToWideChar(CP_ACP, 0, strName, strlen(strName),
		bmsg, nLen);

    BYTE *rtval = new BYTE[strLen*4];
    int i;

    for(i=0;i<strLen;i++)
    {
/*		if((strName[i] >= 'A' && strName[i] <= 'Z') ||
			(strName[i] >= 'a' && strName[i] <= 'z') ||
			(strName[i] == '_') || (strName[i] >= '0' && strName[i] <= '9'))
		{
			continue;
		}
*/
		if( bmsg[i] > 0x0040 && bmsg[i] < 0x005b)
		{//영어(대문자)
			continue;
		}
		if( bmsg[i] > 0x0060 && bmsg[i] < 0x007b)
		{//영어(소문자)
			continue;
		}
		if( bmsg[i] >= 0x0030 && bmsg[i] <= 0x0039)
		{//숫자
			continue;
		}
		if( bmsg[i] == 0x005f)//'_'
		{//특수문자
			continue;
		}

//		if( bmsg[i] > 0x0040 && bmsg[i] < 0x007b)
//		{//영어
//			continue;
//		}
//		if( bmsg[i] > 0x0029 && bmsg[i] < 0x0031+9)
//		{//숫자
//			continue;
//		}

		// 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//#ifdef LANGUAGE_KOREA
//		//if(PRIMARYLANGID(g_input.GetLangId()) == LANG_KOREAN)
//		{
//			if(bmsg[i] == 0 )
//			{				
//				int temp,temp2;
//				char bufChat[SIZE_MAX_CHARACTER_NAME] = {0,};
//				strncpy(bufChat,strName,strlen(strName));
//				// 2006-04-13 by ispark
//				g_pD3dApp->CheckReadyStringFiltering(bufChat, &temp, &temp2);
//	//			g_pD3dApp->m_pAbuseFilter->AbuseFiltering(bufChat,&temp,&temp2);
//
//				// 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//				delete[] rtval;
//				// end 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리				
//				if(temp > 0)
//					return FALSE;
//				return TRUE;
//			}
//			if (bmsg[i] < 0xAC00 || bmsg[i] > 0xd7a3)
//			{
//				rtval[i*4] = rtval[i*4+1]= rtval[i*4+2]= rtval[i*4+3] = 0;
//				// 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//				delete[] rtval;
//				// end 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//				return FALSE;
//			}
//			else
//			{
//				int chohab = bmsg[i] - 0xAc00;
//				int cho = chohab /21 / 28;
//				int chung = (chohab % (21*28)) / 28;
//				int chong = chohab % 28;
//				
//				switch (cho)
//				{
//				case 0:			// 가
//				case 1:			// 까
//				case 5:			// 라
//				case 15:		// 카
//				case 11:		// 아
//				case 2:			// 나
//				case 12:		// 자
//				case 16:		// 타
//				case 9:			// 사
//				case 18:		// 하
//				case 3:			// 다
//				case 4:			// 따
//				case 10:		// 싸
//				case 13:		// 짜
//				case 14:		// 차
//				case 6:			// 마
//				case 7:			// 바
//				case 8:			// 빠
//				case 17:		// 파
//					break;
//				default:
//					{					
//						// 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//						delete[] rtval;
//						// end 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//						return FALSE;
//					}
//				}
//				
//				
//				switch (chung)
//				{
//				case 0:			// 아
//				case 1:			// 애
//				case 2:			// 야
//				case 3:			// 얘
//				case 4:			// 어
//				case 5:			// 에
//				case 6:			// 여
//				case 7:			// 예
//				case 8:			// 오
//				case 17:		// 유
//				case 9:			// 와
//				case 12:		// 요
//				case 10:		// 왜
//				case 11:		// 외
//				case 13:		// 우
//				case 14:		// 워
//				case 15:		// 웨
//				case 16:		// 위
//				case 18:		// 으
//				case 19:		// 의
//				case 20:		// 이
//					break;
//				default:
//					{
//						// 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//						delete[] rtval;
//						// end 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//						
//						return FALSE;
//					}
//				}
//				
//				
//				switch (chong)
//				{
//				case 0:			// 아
//				case 1:			// 악
//				case 2:			// 앆
//				case 3:			// 앇
//				case 8:			// 알
//				case 9:			// 앍
//				case 10:		// 앎
//				case 11:		// 앏
//				case 12:		// 앐
//				case 13:		// 앑
//				case 14:		// 앒
//				case 15:		// 앓
//				case 24:		// 앜
//				case 4:			// 안
//				case 5:			// 앉
//				case 6:			// 않
//				case 22:		// 앚
//				case 19:		// 앗
//				case 21:		// 앙
//				case 7:			// 앋
//				case 20:		// 았
//				case 23:		// 앛
//				case 25:		// 앝
//				case 27:		// 앟
//				case 16:		// 암
//				case 17:		// 압
//				case 18:		// 앖
//				case 26:		// 앞
//					break;
//				default:
//					{
//						// 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
//						delete[] rtval;
//						// end 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리						
//						return FALSE;
//					}
//				}
//				
//			}
//        }
		// end 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
    }
//	if(PRIMARYLANGID(g_input.GetLangId()) == LANG_KOREAN)
	{
		int temp,temp2;
		// 2009-02-11 by bhsohn Japan MemBug
		//char bufChat[SIZE_MAX_CHARACTER_NAME] = {0,};
		char bufChat[MAX_PATH] = {0,};
		ZERO_MEMORY(bufChat);
		// end 2009-02-11 by bhsohn Japan MemBug
		strncpy(bufChat,strName,strlen(strName));
		// 2006-04-13 by ispark
		g_pD3dApp->CheckReadyStringFiltering(bufChat, &temp, &temp2);
//		g_pD3dApp->m_pAbuseFilter->AbuseFiltering(bufChat,&temp,&temp2);
		// 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
		delete[] rtval;
		// end 2007-10-22 by bhsohn 캐릭터명 공백 관련 처리
		if(temp > 0)
			return FALSE;
	}
	return TRUE;
}

// 2005-07-04 by ispark 
// 자동 스탯 분배 삭제
//void CINFCreateMenu::SetCharacterUnitStyle(BOOL bToolTip)
//{
//	switch(m_nSelectUnit) 
//	{
//	case CREATE_CHARACTER_INFO_B:
//		{
//			if(!bToolTip)
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nCreateUnitStat		= AUTOSTAT_TYPE_BGEAR_ATTACK;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nCreateUnitStat = AUTOSTAT_TYPE_BGEAR_MULTI;
//				else m_nCreateUnitStat = AUTOSTAT_TYPE_FREESTYLE;
//			}
//			else
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nRenderToolTipIndex		= AUTOSTAT_TYPE_BGEAR_ATTACK;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nRenderToolTipIndex = AUTOSTAT_TYPE_BGEAR_MULTI;
//				else m_nRenderToolTipIndex = AUTOSTAT_TYPE_FREESTYLE;
//			}
//		}
//		break;
//	case CREATE_CHARACTER_INFO_A:
//		{
//			if(!bToolTip)
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nCreateUnitStat		= AUTOSTAT_TYPE_AGEAR_ATTACK;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nCreateUnitStat = AUTOSTAT_TYPE_AGEAR_SHIELD;
//				else m_nCreateUnitStat = AUTOSTAT_TYPE_FREESTYLE;
//			}
//			else
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nRenderToolTipIndex		= AUTOSTAT_TYPE_AGEAR_ATTACK;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nRenderToolTipIndex = AUTOSTAT_TYPE_AGEAR_SHIELD;
//				else m_nRenderToolTipIndex = AUTOSTAT_TYPE_FREESTYLE;
//			}
//		}
//		break;
//	case CREATE_CHARACTER_INFO_M:
//		{
//			if(!bToolTip)
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nCreateUnitStat		= AUTOSTAT_TYPE_MGEAR_DEFENSE;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nCreateUnitStat = AUTOSTAT_TYPE_MGEAR_SUPPORT;
//				else m_nCreateUnitStat = AUTOSTAT_TYPE_FREESTYLE;
//			}
//			else
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nRenderToolTipIndex		= AUTOSTAT_TYPE_MGEAR_DEFENSE;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nRenderToolTipIndex = AUTOSTAT_TYPE_MGEAR_SUPPORT;
//				else m_nRenderToolTipIndex = AUTOSTAT_TYPE_FREESTYLE;
//			}
//		}
//		break;
//	case CREATE_CHARACTER_INFO_I:
//		{
//			if(!bToolTip)
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nCreateUnitStat		= AUTOSTAT_TYPE_IGEAR_ATTACK;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nCreateUnitStat = AUTOSTAT_TYPE_IGEAR_DODGE;
//				else m_nCreateUnitStat = AUTOSTAT_TYPE_FREESTYLE;
//			}
//			else
//			{
//				if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_A) m_nRenderToolTipIndex		= AUTOSTAT_TYPE_IGEAR_ATTACK;
//				else if(m_nSelectUnitStyle == CREATE_CHARACTER_INFO_UNIT_STYLE_D) m_nRenderToolTipIndex = AUTOSTAT_TYPE_IGEAR_DODGE;
//				else m_nRenderToolTipIndex = AUTOSTAT_TYPE_FREESTYLE;
//			}
//		}
//		break;
//	}
//}

void CINFCreateMenu::RenderPopUpWindowImage(int x, int y, int cx, int cy)
{
	//FLOG( "CINFCreateMenu::RenderPopUpWindowImage(int x, int y, int cx, int cy, int cstringLen)" );
	FLOG( "CINFCreateMenu::RenderPopUpWindowImage(int x, int y, int cx, int cy)" );

	m_pImgTextPopUp[0]->Move(x-7, y-2);
	m_pImgTextPopUp[0]->Render();

	m_pImgTextPopUp[1]->Move(x, y-2);
	m_pImgTextPopUp[1]->SetScale(cx, 1);
	m_pImgTextPopUp[1]->Render();

	m_pImgTextPopUp[2]->Move(x+cx, y-2);
	m_pImgTextPopUp[2]->Render();
}
