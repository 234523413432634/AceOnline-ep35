// INFCityOutPost.cpp: implementation of the CINFCityOutPost class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "INFCityOutPost.h"
#include "INFGameMain.h"
#include "AtumApplication.h"
#include "FieldWinSocket.h"
#include "AtumDatabase.h"
#include "INFWindow.h"
#include "D3DHanFont.h"
#include "INFIcon.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "INFCityBase.h"
#include "ItemInfo.h"
#include "INFInven.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "Chat.h"
#include "StoreData.h"
#include "dxutil.h" 
#include "AtumSound.h"
#include "CInput.h"
#include "INFMotherShipManager.h"	// 2008-10-16 by bhsohn �������� ����, ������ ����â
#include "INFCurselEditBox.h"		// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����


// 2009. 01. 12 by ckPark ���� ���� �ý���
#include "Interface.h"
// end 2009. 01. 12 by ckPark ���� ���� �ý���


#define OUTPOST_BAR_NAME_X			(CITY_BASE_NPC_BOX_START_X + 5)
#define OUTPOST_BAR_NAME_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_CITYLEADER_WINDOWL_Y + 2)			// �ٸ� ������ �� ����.
#define OUTPOST_STARTL_X			(CITY_BASE_NPC_BOX_START_X)									// ������ â �� �մ�.
#define OUTPOST_STARTL_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_CITYLEADER_WINDOWL_Y + 20)			// �ٸ� ������ �� ����.
#define OUTPOST_STARTR_X			(OUTPOST_STARTL_X + SIZE_CITYLEADER_WINDOWL_X)
#define OUTPOST_STARTR_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_CITYLEADER_WINDOWL_Y + 20)			// �ٸ� ������ �� ����.

// ���� â ��� �� ��ư ��ġ.
#define OUTPOST_BGL_X				(OUTPOST_STARTL_X + 14)
#define OUTPOST_BGL_Y				(OUTPOST_STARTL_Y + 7)

#define TITLE_POS_X					(OUTPOST_BGL_X)
#define TITLE_POS_Y					(OUTPOST_BGL_Y -24)

#define OUTPOST_BRIGADE_NOTICE_BUTTON_X			(OUTPOST_BGL_X + 16)
#define OUTPOST_BRIGADE_NOTICE_BUTTON_Y			(OUTPOST_BGL_Y + 23)
#define OUTPOST_EXPENCE_BUTTON_X				(OUTPOST_BGL_X + 16)
#define OUTPOST_EXPENCE_BUTTON_Y				(OUTPOST_BGL_Y + 61)
#define OUTPOST_WAR_TIME_SET_BUTTON_X			(OUTPOST_BGL_X + 16)
#define OUTPOST_WAR_TIME_SET_BUTTON_Y			(OUTPOST_BGL_Y + 98)
#define OUTPOST_WARINFO_BUTTON_X				(OUTPOST_BGL_X + 16)
#define OUTPOST_WARINFO_BUTTON_Y				(OUTPOST_BGL_Y + 135)
#define OUTPOST_LEFT_BUTTON_W					124
#define	OUTPOST_LEFT_BUTTON_H					29

// ������ ��� �� ��ư��ġ.
//--------------------------------------------------------------------------//

#define OUTPOST_BGR_X				(OUTPOST_STARTR_X + 12)
#define OUTPOST_BGR_Y				(OUTPOST_STARTR_Y + 7)

// ���� ���� ����.
#define OUTPOST_WRITE_BUTTON_X					(OUTPOST_BGR_X + 11)
#define OUTPOST_WRITE_BUTTON_Y					(OUTPOST_BGR_Y + 47)
#define OUTPOST_REV_BUTTON_X					(OUTPOST_BGR_X + 79)
#define OUTPOST_REV_BUTTON_Y					(OUTPOST_BGR_Y + 47)
#define OUTPOST_DEL_BUTTON_X					(OUTPOST_BGR_X + 147)
#define OUTPOST_DEL_BUTTON_Y					(OUTPOST_BGR_Y + 47)
#define OUTPOST_APP_BUTTON_X					(OUTPOST_BGR_X + 238)
#define OUTPOST_APP_BUTTON_Y					(OUTPOST_BGR_Y + 205)
#define OUTPOST_RIGHT_BUTTON_W					65
#define	OUTPOST_RIGHT_BUTTON_H					19

//#define OUTPOST_NOTICE_EDIT_W					260
#define OUTPOST_NOTICE_EDIT_W					240
#define OUTPOST_NOTICE_EDIT_H					110

#define OUTPOST_NOTICE_EDIT_X					(OUTPOST_BGR_X + 25)
#define OUTPOST_NOTICE_EDIT_Y					(OUTPOST_BGR_Y + 86)
#define OUTPOST_NOTICE_FONT_LINE_HEIGHT			15

// �ǰ��� ����.
#define OUTPOST_EXPENCE_OK_BUTTON_X				(OUTPOST_BGR_X + 238)
#define OUTPOST_EXPENCE_OK_BUTTON_Y				(OUTPOST_BGR_Y + 202)

#define OUTPOST_EXPENCE_LATE_FONT_X				(OUTPOST_BGR_X + 247)
#define OUTPOST_EXPENCE_LATE_FONT_Y				(OUTPOST_BGR_Y + 55)
#define OUTPOST_EXPENCE_CUMEXP_FONT_X			(OUTPOST_BGR_X + 247)
#define OUTPOST_EXPENCE_CUMEXP_FONT_Y			(OUTPOST_BGR_Y + 86)
#define OUTPOST_EXPENCE_EXP_FONT_X				(OUTPOST_BGR_X + 247)
#define OUTPOST_EXPENCE_EXP_FONT_Y				(OUTPOST_BGR_Y + 116)

// ���� �ð� ����.
#define OUTPOST_WARTIME_RADIO_BUTTON_START_X	(OUTPOST_BGR_X + 35)
#define OUTPOST_WARTIME_RADIO_BUTTON_START_Y	(OUTPOST_BGR_Y + 161)
#define OUTPOST_WARTIME_RADIO_BUTTON_GAP_Y		19
#define OUTPOST_WARTIME_RADIO_BUTTON_W			17
#define OUTPOST_WARTIME_RADIO_BUTTON_H			17

#define OUTPOST_NEXT_WARTIME_DATE_FONT_X		(OUTPOST_BGR_X + 74)
#define OUTPOST_NEXT_WARTIME_DATE_FONT_Y		(OUTPOST_BGR_Y + 67)
#define OUTPOST_NEXT_WARTIME_TIME_FONT_X		(OUTPOST_BGR_X + 74)
#define OUTPOST_NEXT_WARTIME_TIME_FONT_Y		(OUTPOST_BGR_Y + 117)

#define OUTPOST_SEL_WARTIME_FONT_X				(OUTPOST_BGR_X + 57)
#define OUTPOST_SEL_WARTIME_FONT_Y				(OUTPOST_BGR_Y + 167)
#define OUTPOST_SEL_WARTIME_FONT_GAP_H			18 



#define OUTPOST_OK_BUTTON_X						(OUTPOST_BGR_X + 238)
#define OUTPOST_OK_BUTTON_Y						(OUTPOST_BGR_Y + 202)

#define	MAX_NEXT_WAR_RADIO		3



// 2009. 01. 12 by ckPark ���� ���� �ý���
#define WARDECLARE_BTN_X							(OUTPOST_BGR_X + 200)
#define WARDECLARE_BTN_Y 							(OUTPOST_BGR_Y + 212)

#define OUR_THIS_TAKEOFF_X							(OUTPOST_BGR_X + 43)
#define OUR_THIS_TAKEOFF_Y							(OUTPOST_BGR_Y + 81)
#define OUR_NEXT_TAKEOFF_X							(OUTPOST_BGR_X + 43)
#define OUR_NEXT_TAKEOFF_Y							(OUTPOST_BGR_Y + 142)

#define ENEMY_THIS_TAKEOFF_X						(OUTPOST_BGR_X + 275)
#define ENEMY_THIS_TAKEOFF_Y						(OUTPOST_BGR_Y + 81)
#define ENEMY_NEXT_TAKEOFF_X						(OUTPOST_BGR_X + 275)
#define ENEMY_NEXT_TAKEOFF_Y						(OUTPOST_BGR_Y + 142)

#define OUR_THIS_TAKEOFFTIME_X						(OUTPOST_BGR_X + 48)
#define OUR_THIS_TAKEOFFTIME_Y						(OUTPOST_BGR_Y + 105)
#define OUR_NEXT_TAKEOFFTIME_X						(OUTPOST_BGR_X + 48)
#define OUR_NEXT_TAKEOFFTIME_Y						(OUTPOST_BGR_Y + 167)

#define ENEMY_THIS_TAKEOFFTIME_X					(OUTPOST_BGR_X + 280)
#define ENEMY_THIS_TAKEOFFTIME_Y					(OUTPOST_BGR_Y + 105)
#define ENEMY_NEXT_TAKEOFFTIME_X					(OUTPOST_BGR_X + 280)
#define ENEMY_NEXT_TAKEOFFTIME_Y					(OUTPOST_BGR_Y + 167)

// end 2009. 01. 12 by ckPark ���� ���� �ý���



// ��ũ�� �� ����
#define	MAX_SCROLL_LINE			7
#define	SCROLL_BALL_POSX					288
#define	SCROLL_BALL_POSY					78
#define	SCROLL_BALL_WIDTH					11
#define	SCROLL_BALL_SCROLL_CAP				30

#define	SCROLL_WIDTH						330
#define	SCROLL_HEIGHT						78
#define	SCROLL_WHELL_HEIGHT					150


//--------------------------------------------------------------------------//
//							���� ���� â.
#define LEADER_WARINFO_BG_X							(OUTPOST_BGR_X)// + 22)
#define LEADER_WARINFO_BG_Y							(OUTPOST_BGR_Y)// + 8)



// 2009. 01. 12 by ckPark ���� ���� �ý���
//#define LEADER_WARINFO_TAB_W						(116)
#define LEADER_WARINFO_TAB_W						(91)
// end 2009. 01. 12 by ckPark ���� ���� �ý���






#define LEADER_WARINFO_TAB_H						(25)
#define LEADER_WARINFO_TAB_Y						(OUTPOST_BGR_Y)
#define LEADER_WARINFO_TAB_INFLUENCE_X				(OUTPOST_BGR_X)
#define LEADER_WARINFO_TAB_MOTHERSHIP_X				(LEADER_WARINFO_TAB_INFLUENCE_X + LEADER_WARINFO_TAB_W)
#define LEADER_WARINFO_TAB_OUTPOST_X				(LEADER_WARINFO_TAB_MOTHERSHIP_X + LEADER_WARINFO_TAB_W)
#define LEADER_WARINFO_TAB_WARPOINT_X				(LEADER_WARINFO_TAB_OUTPOST_X + LEADER_WARINFO_TAB_W)

// ������ ��
#define WARINFO_INFLUENCE_BG1_X						(OUTPOST_BGR_X + 18)
#define WARINFO_INFLUENCE_BG1_Y						(OUTPOST_BGR_Y + 45)
#define WARINFO_INFLUENCE_BG2_X						(OUTPOST_BGR_X + 244)
#define WARINFO_INFLUENCE_BG2_Y						(OUTPOST_BGR_Y + 45)
#define WARINFO_INFLUENCE_FONT_POINT_H				31				
#define WARINFO_INFLUENCE_FONT_1_CENTER_X			(OUTPOST_BGR_X + 178)
#define WARINFO_INFLUENCE_FONT_2_CENTER_X			(OUTPOST_BGR_X + 405)
#define WARINFO_INFLUENCE_FONT_LEADER_Y				(OUTPOST_BGR_Y + 89)
#define WARINFO_INFLUENCE_FONT_LEADER1_Y			(WARINFO_INFLUENCE_FONT_LEADER_Y + WARINFO_INFLUENCE_FONT_POINT_H)
#define WARINFO_INFLUENCE_FONT_LEADER2_Y			(WARINFO_INFLUENCE_FONT_LEADER1_Y + WARINFO_INFLUENCE_FONT_POINT_H)
#define WARINFO_INFLUENCE_FONT_POINT_Y				(WARINFO_INFLUENCE_FONT_LEADER2_Y + WARINFO_INFLUENCE_FONT_POINT_H)

// ���������� ��
#define WARINFO_OUTPOST_FONT_OUTPOST_CENTER_X		(OUTPOST_BGR_X + 56)
#define WARINFO_OUTPOST_FONT_INFLUENCE_CENTER_X		(OUTPOST_BGR_X + 119)
// 2007-12-17 by dgwoo �������̽� ����.
#define WARINFO_OUTPOST_FONT_GUILD_CENTER_X			(OUTPOST_BGR_X + 247)
#define WARINFO_OUTPOST_FONT_GUILDLEADER_CENTER_X	(OUTPOST_BGR_X + 186)
#define WARINFO_OUTPOST_FONT_GUILDLEADER_W			70
//#define WARINFO_OUTPOST_FONT_GUILD_CENTER_X			(LEADER_BGR_X + 286)
#define WARINFO_OUTPOST_FONT_GUILDMARK_X			(OUTPOST_BGR_X + 240)
#define WARINFO_OUTPOST_FONT_GUILDNAME_X			(WARINFO_OUTPOST_FONT_GUILDMARK_X + 28)
#define WARINFO_OUTPOST_FONT_GUILDNAME_W			65
#define WARINFO_OUTPOST_FONT_SCHEDULE_CENTER_X		(OUTPOST_BGR_X + 396)

#define WARINFO_OUTPOST_FONT_DATA_1_Y				(OUTPOST_BGR_Y + 106)
#define WARINFO_OUTPOST_FONT_DATA_1_GUILDNAME_Y		(OUTPOST_BGR_Y + 97)
#define WARINFO_OUTPOST_FONT_DATA_1_GUILDLEADER_Y	(OUTPOST_BGR_Y + 112)
#define WARINFO_OUTPOST_GUILDMARK_1_Y				(WARINFO_OUTPOST_FONT_DATA_1_GUILDNAME_Y + 3)
#define WARINFO_OUTPOST_FONT_H						(32)

// 2008-10-16 by bhsohn �������� ����, ������ ����â
// ��������ũ��
#define MOTHERSHIP_INFO_VIEW_MAX_SCROLL_LINE		5
#define MOTHERSHIP_INFO_VIEW_SCROLL_X			(OUTPOST_BGR_X + 476)
#define MOTHERSHIP_INFO_VIEW_SCROLL_Y			(OUTPOST_BGR_Y + 74)
#define MOTHERSHIP_INFO_VIEW_SCROLL_W			11
#define MOTHERSHIP_INFO_VIEW_SCROLL_H			93
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_X		(OUTPOST_BGR_X + 55)
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_Y		(OUTPOST_BGR_Y + 74)
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_W		434
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_H		133
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_X		(OUTPOST_BGR_X + 465)
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_Y		(OUTPOST_BGR_Y + 74)
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_W		32
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_H		123

// �����۵� ��ġ
// ���� ����
#define MOTHERSHIP_WARINFO_VIEW_ATT_INFL_X			(OUTPOST_BGR_X + 52)
#define MOTHERSHIP_WARINFO_VIEW_ATT_INFL_Y			(OUTPOST_BGR_Y + 71)
#define MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_X		(OUTPOST_BGR_X + 52)
#define MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_Y		(OUTPOST_BGR_Y + 83)
#define MOTHERSHIP_WARINFO_VIEW_POINT_X				(OUTPOST_BGR_X + 135)
#define MOTHERSHIP_WARINFO_VIEW_POINT_Y				(OUTPOST_BGR_Y + 77)
#define MOTHERSHIP_WARINFO_VIEW_TIME_X				(OUTPOST_BGR_X + 289)
#define MOTHERSHIP_WARINFO_VIEW_TIME_Y				(OUTPOST_BGR_Y + 77)
#define MOTHERSHIP_WARINFO_VIEW_WININFL_X			(OUTPOST_BGR_X + 437)
#define MOTHERSHIP_WARINFO_VIEW_WININFL_Y			(OUTPOST_BGR_Y + 77)
#define MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT			(27)

// ������
#define POINTWAR_WARINFO_VIEW_ATT_INFL_X			(OUTPOST_BGR_X + 37)
#define POINTWAR_WARINFO_VIEW_ATT_INFL_Y			(OUTPOST_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_POINT_X				(OUTPOST_BGR_X + 117)
#define POINTWAR_WARINFO_VIEW_POINT_Y				(OUTPOST_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_TIME_X				(OUTPOST_BGR_X + 289)
#define POINTWAR_WARINFO_VIEW_TIME_Y				(OUTPOST_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_WININFL_X				(OUTPOST_BGR_X + 437)
#define POINTWAR_WARINFO_VIEW_WININFL_Y				(OUTPOST_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_CAP_HEIGHT			(27)

// ������ ���� �ɼ�
#define MOTHERSHIP_OPTION_X							(OUTPOST_BGR_X + 353)
#define MOTHERSHIP_OPTION_Y 						(OUTPOST_BGR_Y + 212)

struct sort_MotherShip_summontime: binary_function<structMotherShipInfo, structMotherShipInfo, bool>
{
	bool operator()(structMotherShipInfo pTime1, structMotherShipInfo pTime2)
	{
        if(pTime1.SummonTime < pTime2.SummonTime)
		{
			return TRUE;
		}		
		return FALSE;
    };
};
struct sort_WarPoint_summontime: binary_function<structWarPointInfo, structWarPointInfo, bool>
{
	bool operator()(structWarPointInfo pTime1, structWarPointInfo pTime2)
	{
        if(pTime1.SummonTime < pTime2.SummonTime)
		{
			return TRUE;
		}		
		return FALSE;
    };
};

// end 2008-10-16 by bhsohn �������� ����, ������ ����â

//--------------------------------------------------------------------------//

#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
	#define STRING_CULL ::StringCullingUserData_ToBlank
#else
	#define STRING_CULL ::StringCullingUserDataEx	
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityOutPost::CINFCityOutPost(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	m_pParent = pParent;	// CGameMain*
	m_pBuildingInfo = pBuilding;

	m_pFontExp		= NULL;

	m_fExplate = 0.0f;
	m_nCumulativeExp = 	m_nExp = 0;

	m_nSelWarTimeRadioB		= 0;
	m_nWarTimeMaxCount		= MAX_NEXT_WAR_RADIO;	

	m_nBrigadeNoticeB		= BUTTON_STATE_NORMAL;
	m_nDelB					= BUTTON_STATE_NORMAL;
	m_nExpenceB				= BUTTON_STATE_NORMAL;
	m_nExpenceOkB			= BUTTON_STATE_NORMAL;
	m_nOkB					= BUTTON_STATE_NORMAL;
	m_nOutPostWarTimeB		= BUTTON_STATE_NORMAL;
	//m_nWriteB				= BUTTON_STATE_NORMAL;
	m_nRevB					= BUTTON_STATE_NORMAL;
	//m_bWriteMode			= FALSE;		

	// 2007-09-05 by bhsohn ���� ������
	///////////////////���� ����///////////////////
	m_pNoticeWrite = NULL;
	m_pRegist = NULL;
	m_pNoticeEditBox = NULL;
	///////////////////�ǰ��� ����///////////////////	
	m_pExpenceOkBtn = NULL;
	m_pWarNextOkBtn = NULL;

	
	///////////////////���� �ð� ���� ���� ó��///////////////////	
	m_vecNextWarTimeList.clear();
	m_OutPostNextWarTime.Year 
		= m_OutPostNextWarTime.Month 
		= m_OutPostNextWarTime.Day 
		= m_OutPostNextWarTime.Hour 
		= m_OutPostNextWarTime.Minute 
		= m_OutPostNextWarTime.Second = 0;

	m_pINFScrollBar = NULL;
	
	m_pImgTitle = NULL;

	// 2008-10-16 by bhsohn �������� ����, ������ ����â
	m_pScrollMotherShipInfo			= NULL;
	m_pFontWarInfo		= NULL;
	m_pBtnMotherShipInfo = NULL;

	// 2009. 01. 12 by ckPark ���� ���� �ý���
	m_pFontWarDeclare	= NULL;
	m_pBtnWarDeclare		= NULL;
	// end 2009. 01. 12 by ckPark ���� ���� �ý���
	
}

CINFCityOutPost::~CINFCityOutPost()
{

}
void CINFCityOutPost::ButtonClickWrite()
{
//	memset(m_cNoticeString,0x00,SIZE_MAX_NOTICE);
//	m_bWriteMode = TRUE;
	//m_pNoticeEditBox->InitString();		
	char chBlank[16];
	memset(chBlank, 0x00, 16);

	m_pNoticeEditBox->SetString(chBlank, 16, 0, TRUE);		// ����
	m_pNoticeEditBox->EnableEdit(TRUE, FALSE);
	
	// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
	//m_pINFScrollBar->SetMaxItem(0);
	m_pNoticeEditBox->BackupTxtString();	
	m_pNoticeEditBox->SetFirstLine();	// ���� ���������� �̵�

	m_pINFScrollBar->SetMaxItem(0);
	
}

void CINFCityOutPost::ButtonClickApp()
{
	//m_bWriteMode = FALSE;
	m_pNoticeEditBox->EnableEdit(FALSE, FALSE);
	MSG_FC_INFO_NOTICE_REG sMsg;
	memset(&sMsg, 0x00, sizeof(MSG_FC_INFO_NOTICE_REG));
	sMsg.GuildUID = g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber;		
	m_pNoticeEditBox->GetString(sMsg.NoticeString, SIZE_MAX_NOTICE);

	g_pFieldWinSocket->SendMsg(T_FC_INFO_NOTICE_REG,(char*)&sMsg,sizeof(sMsg));
}

INT CINFCityOutPost::SetChangeRadioButton(INT i_nSel)
{
	m_nSelWarTimeRadioB = i_nSel;
	return m_nSelWarTimeRadioB;
}
void CINFCityOutPost::SetNotice(char *i_szNotice)
{
	if(NULL == m_pNoticeEditBox)
	{
		return;
	}	
	char chBuff[SIZE_MAX_NOTICE];
	ZERO_MEMORY(chBuff);

	m_pNoticeEditBox->InitString();
	if(strlen(i_szNotice) > 0)
	{		
		strncpy(chBuff, i_szNotice, strlen(i_szNotice));	
	}
	else
	{
		wsprintf(chBuff, STRMSG_C_070816_0108);
	}
	// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
	//int nLine = m_pNoticeEditBox->SetString(chBuff, strlen(chBuff)+1);	
	int nLine = m_pNoticeEditBox->SetString(chBuff, strlen(chBuff)+1, 0, TRUE);	

	m_pINFScrollBar->SetMaxItem(nLine);
}

void CINFCityOutPost::ChangeOutPostState(DWORD i_dState)
{
	m_nRWindowState = i_dState;
	MapIndex_t	MapIndex = g_pShuttleChild->GetShuttleInfo()->MapChannelIndex.MapIndex;

	BOOL bShowBtn = FALSE;
	if(g_pD3dApp->IsMyShuttleGuildMaster())
	{
		bShowBtn = TRUE;
	}

	switch(m_nRWindowState)
	{
	case OUTPOST_STATE_NOTICE:
		{			
			m_pNoticeWrite->ShowWindow(bShowBtn);
			m_pRegist->ShowWindow(bShowBtn);

			MSG_FC_INFO_NOTICE_REQUEST sMsg;
			sMsg.NoticeState = NOTICE_GUILDCOMMANDER;
			sMsg.MapIndex = MapIndex;
			g_pFieldWinSocket->SendMsg(T_FC_INFO_NOTICE_REQUEST,(char*)&sMsg,sizeof(sMsg));
		}
		break;
	case OUTPOST_STATE_EXPENCE:
		{
			m_pExpenceOkBtn->ShowWindow(bShowBtn);

			MSG_FC_INFO_EXPEDIENCYFUND_REQUEST sMsg;
			sMsg.MapIndex = MapIndex;
			g_pFieldWinSocket->SendMsg(T_FC_INFO_EXPEDIENCYFUND_REQUEST,(char*)&sMsg,sizeof(sMsg));
		}
		break;
	case OUTPOST_STATE_WARTIME:
		{
			RqNextWarTime();	
			
			// 2008-11-27 by bhsohn �����ڰ� �������� �ð� ���� �Ҽ� �ִ� ���� ����
			//m_pWarNextOkBtn->ShowWindow(bShowBtn);
			m_pWarNextOkBtn->ShowWindow(FALSE);
		}
		break;
	case OUTPOST_STATE_WARINFO:
		{
			ChangeWarInfoState(LEADER_WARINFO_INFLUENCE);
		}
		break;
	}
}
void CINFCityOutPost::ChangeWarInfoState(BYTE i_BWarInfoState)
{
	switch(i_BWarInfoState)
	{
	case LEADER_WARINFO_INFLUENCE:
		{
			g_pFieldWinSocket->SendMsg(T_FC_CITY_WARINFO_INFLUENCE,NULL,NULL);
		}
		break;

		
		// 2009. 01. 12 by ckPark ���� ���� �ý���
	case LEADER_WARINFO_DECLAREWAR:
		{
			// �Ϲ� ������ ��� �ƹ��͵� ����
			if( COMPARE_INFLUENCE( g_pShuttleChild->m_myShuttleInfo.InfluenceType, INFLUENCE_TYPE_NORMAL ) )
				break;
			
			int		nOurMothershipNum;
			int		nEnemyMothershipNum;
			
			if( COMPARE_INFLUENCE( g_pShuttleChild->m_myShuttleInfo.InfluenceType, INFLUENCE_TYPE_ANI ) )
			{
				nOurMothershipNum	= ANI_MOTHERSHIP_NUMBER;
				nEnemyMothershipNum	= BCU_MOTHERSHIP_NUMBER;
			}			
			else if( COMPARE_INFLUENCE( g_pShuttleChild->m_myShuttleInfo.InfluenceType, INFLUENCE_TYPE_VCN ) )
			{
				nOurMothershipNum	= BCU_MOTHERSHIP_NUMBER;
				nEnemyMothershipNum	= ANI_MOTHERSHIP_NUMBER;
			}
			else
			{
				break;
			}
			
			MEX_MONSTER_INFO* pMonsterInfo = g_pDatabase->CheckMonsterInfo(nOurMothershipNum);
			sprintf(m_szOurThisTakeOff, STRMSG_C_090113_0301, pMonsterInfo->MonsterName);
			sprintf(m_szOurNextTakeOff, STRMSG_C_090113_0302, pMonsterInfo->MonsterName);
			pMonsterInfo = g_pDatabase->CheckMonsterInfo(nEnemyMothershipNum);
			sprintf(m_szEnemyThisTakeOff, STRMSG_C_090113_0301, pMonsterInfo->MonsterName);
			sprintf(m_szEnemyNextTakeOff, STRMSG_C_090113_0302,	pMonsterInfo->MonsterName);
			
			
			ATUM_DATE_TIME tempDate;
			tempDate.Year	= 0;
			SetWarDeclareTime(tempDate, m_szOurThisTakeOffTime);
			SetWarDeclareTime(tempDate, m_szOurNextTakeOffTime);
			SetWarDeclareTime(tempDate, m_szEnemyThisTakeOffTime);
			SetWarDeclareTime(tempDate, m_szEnemyNextTakeOffTime);
			
			// Lock
			{
				vector<MessageType_t> vecUnLockMsg;
				vecUnLockMsg.clear();
				vecUnLockMsg.push_back(T_FC_INFO_DECLARATION_MSWAR_INFO);
				vecUnLockMsg.push_back(T_FC_INFO_DECLARATION_MSWAR_INFO_OK);
				// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
				g_pD3dApp->EnterMultiLock(TRUE, T_FC_INFO_DECLARATION_MSWAR_INFO, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
			}
			
			g_pFieldWinSocket->SendMsg(T_FC_INFO_DECLARATION_MSWAR_INFO, 0, 0);
		}
		break;
		// end 2009. 01. 12 by ckPark ���� ���� �ý���

	case LEADER_WARINFO_MOTHERSHIP:
		{
			//g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051114_0001, COLOR_ERROR,CHAT_TAB_SYSTEM );
			//return;
			// 2008-10-16 by bhsohn �������� ����, ������ ����â
			if(m_bStateWarInfo != i_BWarInfoState)
			{
				//TestMotherDB();
				InitWarInfoMothership();				
				RqMotherShipDB();
			}
		}
		break;

	case LEADER_WARINFO_OUTPOST:
		{
			g_pFieldWinSocket->SendMsg(T_FC_CITY_WARINFO_OUTPOST,NULL,NULL);
		}
		break;
	case LEADER_WARINFO_POINT:
		{
			// 2008-10-16 by bhsohn �������� ����, ������ ����â
//			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051114_0001, COLOR_ERROR,CHAT_TAB_SYSTEM);
//			return;
			if(m_bStateWarInfo != i_BWarInfoState)
			{
				//TestPointWarDB();
				InitWarInfoPointWar();				
				RqPointWarDB();
			}
			// end 2008-10-16 by bhsohn �������� ����, ������ ����â
		}
		break;
	}
	m_bStateWarInfo = i_BWarInfoState;
}
HRESULT CINFCityOutPost::InitDeviceObjects()
{
	DataHeader	* pDataHeader;
	int i;
	char buf[16];
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i] = new CINFImage;
		wsprintf(buf, "Onotice%d",i);
		pDataHeader = FindResource(buf);
		m_pImgBrigadeNoticeB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgDelB[i] = new CINFImage;
		wsprintf(buf, "Odel%d",i);
		pDataHeader = FindResource(buf);
		m_pImgDelB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgExpenceB[i] = new CINFImage;
		wsprintf(buf, "Oexpence%d",i);
		pDataHeader = FindResource(buf);
		m_pImgExpenceB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

//		m_pImgExpenceOkB[i] = new CINFImage;
//		wsprintf(buf, "Oreveb%d",i);
//		pDataHeader = FindResource(buf);
//		m_pImgExpenceOkB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

//		m_pImgAppB[i] = new CINFImage;
//		wsprintf(buf, "Oapp%d",i);
//		pDataHeader = FindResource(buf);
//		m_pImgAppB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

//		m_pImgOkB[i] = new CINFImage;
//		wsprintf(buf, "Ook%d",i);
//		pDataHeader = FindResource(buf);
//		m_pImgOkB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgOutPostWarTimeB[i] = new CINFImage;
		wsprintf(buf, "Owartime%d",i);
		pDataHeader = FindResource(buf);
		m_pImgOutPostWarTimeB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgWriteB[i] = new CINFImage;
		wsprintf(buf, "Owrite%d",i);
		pDataHeader = FindResource(buf);
		m_pImgWriteB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgRevB[i] = new CINFImage;
		wsprintf(buf, "Orev%d",i);
		pDataHeader = FindResource(buf);
		m_pImgRevB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	}
	// ���� ���� ��ư.
	wsprintf(buf,"warfieldB");
	if(NULL == m_pImgLWarInfoB)
	{
		m_pImgLWarInfoB = new CINFImageBtn;
	}
	m_pImgLWarInfoB->InitDeviceObjects(buf);

	for(i = 0 ; i < LEADER_WARINFO_END ; i++)
	{
		m_pImgWarInfoBG[i] = new CINFImage;
		wsprintf(buf,"warfield%d",i);
		pDataHeader = FindResource(buf);
		m_pImgWarInfoBG[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}

	m_pImgWarInfoInflAni = new CINFImage;
	pDataHeader = FindResource("inflAbg");
	m_pImgWarInfoInflAni->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgWarInfoInflBcu = new CINFImage;
	pDataHeader = FindResource("inflBbg");
	m_pImgWarInfoInflBcu->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);


	m_pImgRadioB[RADIOBUTTON_STATE_SELECT] = new CINFImage;
	pDataHeader = FindResource("radio_17a");
	m_pImgRadioB[RADIOBUTTON_STATE_SELECT]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	
	m_pImgRadioB[RADIOBUTTON_STATE_NORMAL] = new CINFImage;
	pDataHeader = FindResource("radio_17b");
	m_pImgRadioB[RADIOBUTTON_STATE_NORMAL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgOutPostLBG = new CINFImage;
	pDataHeader = FindResource("outpostB");
	m_pImgOutPostLBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgBriNoticeBG = new CINFImage;
	pDataHeader = FindResource("OnoticeB");
	m_pImgBriNoticeBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgOutPostTimeSetBG = new CINFImage;
	pDataHeader = FindResource("wartimeB");
	m_pImgOutPostTimeSetBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgExpenceBG = new CINFImage;
	pDataHeader = FindResource("OexpenB");
	m_pImgExpenceBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	
	m_pImgTitle = new CINFImage;
	pDataHeader = FindResource("outpost");
	m_pImgTitle->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pFontExp = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontExp->InitDeviceObjects(g_pD3dDev);

	// 2007-09-05 by bhsohn ���� ������
	// ��ư
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "Owrite3");
		wsprintf(szDownBtn, "Owrite1");
		wsprintf(szSelBtn, "Owrite0");
		wsprintf(szDisBtn, "Owrite2");
		if(NULL == m_pNoticeWrite)
		{
			m_pNoticeWrite = new CINFImageBtn;
		}
		m_pNoticeWrite->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "Oapp3");
		wsprintf(szDownBtn, "Oapp1");
		wsprintf(szSelBtn, "Oapp0");
		wsprintf(szDisBtn, "Oapp2");
		if(NULL == m_pRegist)
		{
			m_pRegist = new CINFImageBtn;
		}
		m_pRegist->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	// ����Ʈ �ڽ�
	{
		if(NULL == m_pNoticeEditBox)
		{
			// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
			//m_pNoticeEditBox = new CINFEditBox;
			m_pNoticeEditBox = new CINFCurselEditBox;
		}
		POINT ptPos = {OUTPOST_NOTICE_EDIT_X, OUTPOST_NOTICE_EDIT_Y};
		m_pNoticeEditBox->InitDeviceObjects(9, ptPos, OUTPOST_NOTICE_EDIT_W, TRUE, OUTPOST_NOTICE_FONT_LINE_HEIGHT);		
		m_pNoticeEditBox->SetOnePageItemCnt(MAX_SCROLL_LINE);	// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
		
	}

	// �ǰ��� ����
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "Oreveb3");
		wsprintf(szDownBtn, "Oreveb1");
		wsprintf(szSelBtn, "Oreveb0");
		wsprintf(szDisBtn, "Oreveb2");
		if(NULL == m_pExpenceOkBtn)
		{
			m_pExpenceOkBtn = new CINFImageBtn;
		}
		m_pExpenceOkBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	// Ȯ�� ��ư
	{
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "Ook3");
		wsprintf(szDownBtn, "Ook1");
		wsprintf(szSelBtn, "Ook0");
		wsprintf(szDisBtn, "Ook2");
		if(NULL == m_pWarNextOkBtn)
		{
			m_pWarNextOkBtn = new CINFImageBtn;
		}
		m_pWarNextOkBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	// ���� ���� ��ũ��
	{
		char  szScBall[30];	
		if(NULL == m_pINFScrollBar)
		{
			m_pINFScrollBar = new CINFArenaScrollBar;
		}		
		wsprintf(szScBall,"c_scrlb");
		
		m_pINFScrollBar->InitDeviceObjects(MAX_SCROLL_LINE, szScBall);

		// ����
		// 2008-10-16 by bhsohn �������� ����, ������ ����â
		if(NULL == m_pScrollMotherShipInfo)
		{
			m_pScrollMotherShipInfo = new CINFArenaScrollBar;
		}
		wsprintf(szScBall,"c_scrlb");
		m_pScrollMotherShipInfo->InitDeviceObjects(MOTHERSHIP_INFO_VIEW_MAX_SCROLL_LINE,szScBall);		

		m_pFontWarInfo= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
		m_pFontWarInfo->InitDeviceObjects(g_pD3dDev);

		{
			char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
			wsprintf(szUpBtn, "minfobtn3");
			wsprintf(szDownBtn, "minfobtn1");
			wsprintf(szSelBtn, "minfobtn0");
			wsprintf(szDisBtn, "minfobtn2");
			if(NULL == m_pBtnMotherShipInfo)
			{
				m_pBtnMotherShipInfo = new CINFImageBtn;
			}
			m_pBtnMotherShipInfo->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);
			
		}
		
		// end 2008-10-16 by bhsohn �������� ����, ������ ����â


		// 2009. 01. 12 by ckPark ���� ���� �ý���
		m_pFontWarDeclare	= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
		m_pFontWarDeclare->InitDeviceObjects(g_pD3dDev);
		
		{
			char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
			wsprintf(szUpBtn, "wdbtn3");
			wsprintf(szDownBtn, "wdbtn1");
			wsprintf(szSelBtn, "wdbtn0");
			wsprintf(szDisBtn, "wdbtn2");
			if(NULL == m_pBtnWarDeclare)
			{
				m_pBtnWarDeclare	= new CINFImageBtn;
			}
			m_pBtnWarDeclare->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);
		}
		// end 2009. 01. 12 by ckPark ���� ���� �ý���



	}	
	
	SetNotice(STRMSG_C_070816_0108);
	
	// 
	ChangeOutPostState(OUTPOST_STATE_NOTICE);

	if(FALSE == g_pD3dApp->IsMyShuttleGuildMaster())
	{
		m_nExpenceB = BUTTON_STATE_DISABLE ;
	}

	return S_OK;
}
HRESULT CINFCityOutPost::RestoreDeviceObjects()
{
	int i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i]->RestoreDeviceObjects() ;
		m_pImgDelB[i]->RestoreDeviceObjects() ;
		m_pImgExpenceB[i]->RestoreDeviceObjects() ;
		//m_pImgExpenceOkB[i]->RestoreDeviceObjects() ;
		//m_pImgOkB[i]->RestoreDeviceObjects() ;
		m_pImgOutPostWarTimeB[i]->RestoreDeviceObjects() ;
		m_pImgWriteB[i]->RestoreDeviceObjects() ;
		m_pImgRevB[i]->RestoreDeviceObjects() ;
	}
	for(i = 0 ; i < LEADER_WARINFO_END ; i++)
	{
		m_pImgWarInfoBG[i]->RestoreDeviceObjects();
	}
	m_pImgWarInfoInflAni->RestoreDeviceObjects();
	m_pImgWarInfoInflBcu->RestoreDeviceObjects();

	m_pImgLWarInfoB->RestoreDeviceObjects();
	m_pImgLWarInfoB->SetBtnPosition(OUTPOST_WARINFO_BUTTON_X,OUTPOST_WARINFO_BUTTON_Y);


	m_pImgRadioB[RADIOBUTTON_STATE_NORMAL]->RestoreDeviceObjects();
	m_pImgRadioB[RADIOBUTTON_STATE_SELECT]->RestoreDeviceObjects();
	m_pImgOutPostLBG->RestoreDeviceObjects();
	m_pImgBriNoticeBG->RestoreDeviceObjects();
	m_pImgOutPostTimeSetBG->RestoreDeviceObjects();
	m_pImgExpenceBG->RestoreDeviceObjects();
	m_pImgTitle->RestoreDeviceObjects();
	m_pFontExp->RestoreDeviceObjects();

	// 2007-09-05 by bhsohn ���� ������
	{	
		
		float fPosX = OUTPOST_WRITE_BUTTON_X;
		float fPosY = OUTPOST_WRITE_BUTTON_Y;		

		m_pNoticeWrite->RestoreDeviceObjects();		
		m_pNoticeWrite->SetBtnPosition(fPosX, fPosY);
	}

	// ���
	{			
		float fPosX = OUTPOST_APP_BUTTON_X;
		float fPosY = OUTPOST_APP_BUTTON_Y;		

		m_pRegist->RestoreDeviceObjects();		
		m_pRegist->SetBtnPosition(fPosX, fPosY);
	}
	
	// �ǰ��� ����
	{			
		float fPosX = OUTPOST_EXPENCE_OK_BUTTON_X;
		float fPosY = OUTPOST_EXPENCE_OK_BUTTON_Y;		

		m_pExpenceOkBtn->RestoreDeviceObjects();		
		m_pExpenceOkBtn->SetBtnPosition(fPosX, fPosY);
	}
	
	{			
		float fPosX = OUTPOST_OK_BUTTON_X;
		float fPosY = OUTPOST_OK_BUTTON_Y;		

		m_pWarNextOkBtn->RestoreDeviceObjects();		
		m_pWarNextOkBtn->SetBtnPosition(fPosX, fPosY);
		// 2008-11-27 by bhsohn �����ڰ� �������� �ð� ���� �Ҽ� �ִ� ���� ����		
		m_pWarNextOkBtn->ShowWindow(FALSE);
		// end 2008-11-27 by bhsohn �����ڰ� �������� �ð� ���� �Ҽ� �ִ� ���� ����		
	}
	// 
	{
		m_pNoticeEditBox->RestoreDeviceObjects();		
	}
	{		
		m_pINFScrollBar->RestoreDeviceObjects();		
		UpdateScrollPos((OUTPOST_BGR_X), (OUTPOST_BGR_Y ), SCROLL_WIDTH, SCROLL_HEIGHT, SCROLL_WHELL_HEIGHT);		
	}
	// 2008-10-16 by bhsohn �������� ����, ������ ����â
	{
		
		RECT rcMouseWhell, rcMousePos;
		// ���� ����
		m_pScrollMotherShipInfo->RestoreDeviceObjects();
		m_pScrollMotherShipInfo->SetPosition(MOTHERSHIP_INFO_VIEW_SCROLL_X,MOTHERSHIP_INFO_VIEW_SCROLL_Y,MOTHERSHIP_INFO_VIEW_SCROLL_W,MOTHERSHIP_INFO_VIEW_SCROLL_H);
		rcMouseWhell.left		= MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_X;
		rcMouseWhell.top		= MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_Y;
		rcMouseWhell.right		= MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_X + MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_W;
		rcMouseWhell.bottom		= MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_Y + MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_H;
		m_pScrollMotherShipInfo->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= MOTHERSHIP_INFO_VIEW_SCROLL_BALL_X;
		rcMousePos.top			= MOTHERSHIP_INFO_VIEW_SCROLL_BALL_Y;
		rcMousePos.right		= MOTHERSHIP_INFO_VIEW_SCROLL_BALL_X + MOTHERSHIP_INFO_VIEW_SCROLL_BALL_W;
		rcMousePos.bottom		= MOTHERSHIP_INFO_VIEW_SCROLL_BALL_Y + MOTHERSHIP_INFO_VIEW_SCROLL_BALL_H;
		m_pScrollMotherShipInfo->SetMouseBallRect(rcMousePos);
		
		if(m_pBtnMotherShipInfo)
		{
			m_pBtnMotherShipInfo->RestoreDeviceObjects();		
			m_pBtnMotherShipInfo->SetBtnPosition(MOTHERSHIP_OPTION_X, MOTHERSHIP_OPTION_Y);
		}		

		m_pFontWarInfo->RestoreDeviceObjects();		
	}
	// end 2008-10-16 by bhsohn �������� ����, ������ ����â


	// 2009. 01. 12 by ckPark ���� ���� �ý���
	
	m_pFontWarDeclare->RestoreDeviceObjects();
	
	if(m_pBtnWarDeclare)
	{
		m_pBtnWarDeclare->RestoreDeviceObjects();		
		m_pBtnWarDeclare->SetBtnPosition(WARDECLARE_BTN_X, WARDECLARE_BTN_Y);
	}
		// end 2009. 01. 12 by ckPark ���� ���� �ý���


	return S_OK;
}
HRESULT CINFCityOutPost::DeleteDeviceObjects()
{
	int i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i]->DeleteDeviceObjects() ;
		m_pImgDelB[i]->DeleteDeviceObjects() ;
		m_pImgExpenceB[i]->DeleteDeviceObjects() ;
		//m_pImgExpenceOkB[i]->DeleteDeviceObjects() ;
		//m_pImgOkB[i]->DeleteDeviceObjects() ;
		m_pImgOutPostWarTimeB[i]->DeleteDeviceObjects() ;
		m_pImgWriteB[i]->DeleteDeviceObjects() ;
		m_pImgRevB[i]->DeleteDeviceObjects() ;

		SAFE_DELETE(m_pImgBrigadeNoticeB[i]);
		SAFE_DELETE(m_pImgDelB[i]);
		SAFE_DELETE(m_pImgExpenceB[i]);
		//SAFE_DELETE(m_pImgExpenceOkB[i]);
		//SAFE_DELETE(m_pImgOkB[i]);
		SAFE_DELETE(m_pImgOutPostWarTimeB[i]);
		SAFE_DELETE(m_pImgWriteB[i]);
		SAFE_DELETE(m_pImgRevB[i]);
	}
	m_pImgRadioB[RADIOBUTTON_STATE_NORMAL]->DeleteDeviceObjects();
	m_pImgRadioB[RADIOBUTTON_STATE_SELECT]->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgRadioB[RADIOBUTTON_STATE_NORMAL]);
	SAFE_DELETE(m_pImgRadioB[RADIOBUTTON_STATE_SELECT]);

	m_pImgOutPostLBG->DeleteDeviceObjects();
	m_pImgBriNoticeBG->DeleteDeviceObjects();
	m_pImgOutPostTimeSetBG->DeleteDeviceObjects();
	m_pImgExpenceBG->DeleteDeviceObjects();
	m_pImgTitle->DeleteDeviceObjects();
	m_pFontExp->DeleteDeviceObjects();

	SAFE_DELETE(m_pImgOutPostLBG);
	SAFE_DELETE(m_pImgBriNoticeBG);
	SAFE_DELETE(m_pImgOutPostTimeSetBG);
	SAFE_DELETE(m_pImgExpenceBG);
	SAFE_DELETE(m_pImgTitle);	
	SAFE_DELETE(m_pFontExp);
	for(i = 0 ; i < LEADER_WARINFO_END ; i++)
	{
		m_pImgWarInfoBG[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgWarInfoBG[i]);
	}
	
	m_pImgWarInfoInflAni->DeleteDeviceObjects();
	m_pImgWarInfoInflBcu->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgWarInfoInflBcu);
	SAFE_DELETE(m_pImgWarInfoInflAni);

	m_pImgLWarInfoB->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgLWarInfoB);



	// 2007-09-05 by bhsohn ���� ������
	if(m_pNoticeWrite)
	{
		m_pNoticeWrite->DeleteDeviceObjects();	
		SAFE_DELETE(m_pNoticeWrite);
	}
	if(m_pRegist)
	{
		m_pRegist->DeleteDeviceObjects();	
		SAFE_DELETE(m_pRegist);
	}
	
	if(m_pExpenceOkBtn)
	{
		m_pExpenceOkBtn->DeleteDeviceObjects();	
		SAFE_DELETE(m_pExpenceOkBtn);
	}
	if(m_pWarNextOkBtn)
	{
		m_pWarNextOkBtn->DeleteDeviceObjects();	
		SAFE_DELETE(m_pWarNextOkBtn);
	}

	if(m_pNoticeEditBox)
	{
		m_pNoticeEditBox->DeleteDeviceObjects();	
		SAFE_DELETE(m_pNoticeEditBox);
	}
	if(m_pINFScrollBar)
	{
		m_pINFScrollBar->DeleteDeviceObjects();	
		SAFE_DELETE(m_pINFScrollBar);
	}

	// 2008-10-16 by bhsohn �������� ����, ������ ����â
	if(m_pFontWarInfo)
	{
		m_pFontWarInfo->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontWarInfo);
	}
	if(m_pScrollMotherShipInfo)
	{
		m_pScrollMotherShipInfo->DeleteDeviceObjects();
		SAFE_DELETE(m_pScrollMotherShipInfo);
	}
	if(m_pBtnMotherShipInfo)
	{
		m_pBtnMotherShipInfo->DeleteDeviceObjects();	
		SAFE_DELETE(m_pBtnMotherShipInfo);
	}
	// end 2008-10-16 by bhsohn �������� ����, ������ ����â



	// 2009. 01. 12 by ckPark ���� ���� �ý���
	m_pFontWarDeclare->DeleteDeviceObjects();
	
	SAFE_DELETE(m_pFontWarDeclare);
	
	if(m_pBtnWarDeclare)
	{
		m_pBtnWarDeclare->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnWarDeclare);
	}
	// end 2009. 01. 12 by ckPark ���� ���� �ý���


	return S_OK;
}
HRESULT CINFCityOutPost::InvalidateDeviceObjects()
{
	int i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i]->InvalidateDeviceObjects() ;
		m_pImgDelB[i]->InvalidateDeviceObjects() ;
		m_pImgExpenceB[i]->InvalidateDeviceObjects() ;
		//m_pImgExpenceOkB[i]->InvalidateDeviceObjects() ;
		//m_pImgOkB[i]->InvalidateDeviceObjects() ;
		m_pImgOutPostWarTimeB[i]->InvalidateDeviceObjects() ;
		m_pImgWriteB[i]->InvalidateDeviceObjects() ;
		m_pImgRevB[i]->InvalidateDeviceObjects() ;
	}
	m_pImgRadioB[RADIOBUTTON_STATE_NORMAL]->InvalidateDeviceObjects();
	m_pImgRadioB[RADIOBUTTON_STATE_SELECT]->InvalidateDeviceObjects();

	m_pImgOutPostLBG->InvalidateDeviceObjects();
	m_pImgBriNoticeBG->InvalidateDeviceObjects();
	m_pImgOutPostTimeSetBG->InvalidateDeviceObjects();
	m_pImgExpenceBG->InvalidateDeviceObjects();
	m_pImgTitle->InvalidateDeviceObjects();
	m_pFontExp->InvalidateDeviceObjects();

	for(i = 0 ; i < LEADER_WARINFO_END ; i++)
	{
		m_pImgWarInfoBG[i]->InvalidateDeviceObjects();
	}
	m_pImgWarInfoInflAni->InvalidateDeviceObjects();
	m_pImgWarInfoInflBcu->InvalidateDeviceObjects();
	m_pImgLWarInfoB->InvalidateDeviceObjects();


	// 2007-09-05 by bhsohn ���� ������
	m_pNoticeEditBox->InvalidateDeviceObjects();		
	m_pNoticeWrite->InvalidateDeviceObjects();		
	m_pRegist->InvalidateDeviceObjects();		

	m_pExpenceOkBtn->InvalidateDeviceObjects();		
	m_pWarNextOkBtn->InvalidateDeviceObjects();	
	
	m_pINFScrollBar->InvalidateDeviceObjects();

	// 2008-10-16 by bhsohn �������� ����, ������ ����â
	m_pFontWarInfo->InvalidateDeviceObjects();	
	m_pScrollMotherShipInfo->InvalidateDeviceObjects();
	if(m_pBtnMotherShipInfo)
	{
		m_pBtnMotherShipInfo->InvalidateDeviceObjects();		
	}
	// end 2008-10-16 by bhsohn �������� ����, ������ ����â


	// 2009. 01. 12 by ckPark ���� ���� �ý���
	m_pFontWarDeclare->InvalidateDeviceObjects();
	
	if(m_pBtnWarDeclare)
		m_pBtnWarDeclare->InvalidateDeviceObjects();
	// end 2009. 01. 12 by ckPark ���� ���� �ý���
	
	
	return S_OK;
}

void CINFCityOutPost::Render()
{
	// ���� ���.
	m_pImgOutPostLBG->Move(OUTPOST_BGL_X,OUTPOST_BGL_Y);
	m_pImgOutPostLBG->Render();

	// Ÿ��Ʋ 	
	m_pImgTitle->Move(TITLE_POS_X,TITLE_POS_Y);
	m_pImgTitle->Render();	

	// ���� ��ư 
	m_pImgBrigadeNoticeB[m_nBrigadeNoticeB]->Move(OUTPOST_BRIGADE_NOTICE_BUTTON_X,OUTPOST_BRIGADE_NOTICE_BUTTON_Y);
	m_pImgBrigadeNoticeB[m_nBrigadeNoticeB]->Render();
	m_pImgExpenceB[m_nExpenceB]->Move(OUTPOST_EXPENCE_BUTTON_X,OUTPOST_EXPENCE_BUTTON_Y);
	m_pImgExpenceB[m_nExpenceB]->Render();
	m_pImgOutPostWarTimeB[m_nOutPostWarTimeB]->Move(OUTPOST_WAR_TIME_SET_BUTTON_X,OUTPOST_WAR_TIME_SET_BUTTON_Y);
	m_pImgOutPostWarTimeB[m_nOutPostWarTimeB]->Render();
	m_pImgLWarInfoB->Render();

	// ������ â.
	switch(m_nRWindowState)
	{
	case OUTPOST_STATE_NOTICE:
		{// ���� ���� 
			// ���.
			m_pImgBriNoticeBG->Move(OUTPOST_BGR_X,OUTPOST_BGR_Y);
			m_pImgBriNoticeBG->Render();			
			// 2007-09-05 by bhsohn ���� ������
//			m_pImgWriteB[m_nWriteB]->Move(OUTPOST_WRITE_BUTTON_X,OUTPOST_WRITE_BUTTON_Y);
//			m_pImgWriteB[m_nWriteB]->Render();

//			m_pImgRevB[m_nRevB]->Move(OUTPOST_REV_BUTTON_X,OUTPOST_REV_BUTTON_Y);
//			m_pImgRevB[m_nRevB]->Render();
//			m_pImgDelB[m_nDelB]->Move(OUTPOST_DEL_BUTTON_X,OUTPOST_DEL_BUTTON_Y);
//			m_pImgDelB[m_nDelB]->Render();
//			m_pImgAppB[m_nAppB]->Move(OUTPOST_APP_BUTTON_X,OUTPOST_APP_BUTTON_Y);
//			m_pImgAppB[m_nAppB]->Render();

			// 2007-09-05 by bhsohn ���� ������
			m_pNoticeWrite->Render();
			m_pRegist->Render();
			
			m_pNoticeEditBox->Tick();
			m_pNoticeEditBox->Render(m_pINFScrollBar->GetScrollStep(), MAX_SCROLL_LINE);

			m_pINFScrollBar->Render();		

		}
		break;
	case OUTPOST_STATE_EXPENCE:
		{// �ǰ��� ����.
			// ���.
			m_pImgExpenceBG->Move(OUTPOST_BGR_X,OUTPOST_BGR_Y);
			m_pImgExpenceBG->Render();

			char temp1[512],temp2[512];
			SIZE size;
			
			//wsprintf(temp1,"%.0f%%",m_fExplate);
			sprintf(temp1,"%.1f%%",m_fExplate);
			size = m_pFontExp->GetStringSize(temp1);
			m_pFontExp->DrawText(OUTPOST_EXPENCE_LATE_FONT_X - size.cx,OUTPOST_EXPENCE_LATE_FONT_Y,GUI_FONT_COLOR,
				temp1, 0L);
			wsprintf(temp1,"%d",m_nCumulativeExp);                                                                                                                               
			MakeCurrencySeparator( temp2, temp1, 3, ',' );
			size = m_pFontExp->GetStringSize(temp2);
			m_pFontExp->DrawText(OUTPOST_EXPENCE_CUMEXP_FONT_X - size.cx,OUTPOST_EXPENCE_CUMEXP_FONT_Y,GUI_FONT_COLOR,
				temp2,0L);
			wsprintf(temp1,"%d",m_nExp);
			MakeCurrencySeparator( temp2, temp1, 3, ',' );
			size = m_pFontExp->GetStringSize(temp2);
			m_pFontExp->DrawText(OUTPOST_EXPENCE_EXP_FONT_X - size.cx,OUTPOST_EXPENCE_EXP_FONT_Y,GUI_FONT_COLOR,
				temp2,0L);
//			m_pImgExpenceOkB[m_nExpenceOkB]->Move(OUTPOST_EXPENCE_OK_BUTTON_X,OUTPOST_EXPENCE_OK_BUTTON_Y);
//			m_pImgExpenceOkB[m_nExpenceOkB]->Render();

			m_pExpenceOkBtn->Render();
			
		}
		break;
	case OUTPOST_STATE_WARTIME:
		{// ����ð� ����.
			// ���.
			m_pImgOutPostTimeSetBG->Move(OUTPOST_BGR_X,OUTPOST_BGR_Y);
			m_pImgOutPostTimeSetBG->Render();
			
			//m_pFontExp->DrawText(OUTPOST_NEXT_WARTIME_FONT_X,OUTPOST_NEXT_WARTIME_FONT_Y,GUI_FONT_COLOR,)

			// RADIO ��ư.			
			int nPosX, nPosY;
			char temp1[512];
			ZERO_MEMORY(temp1);				

			if(m_OutPostNextWarTime.Year != 0)
			{				
				// �����
				nPosX = OUTPOST_NEXT_WARTIME_DATE_FONT_X;
				nPosY = OUTPOST_NEXT_WARTIME_DATE_FONT_Y;
				// 2007-10-05 by bhsohn ��,��,�� ��Ʈ�� �ý��� �߰�
//				#ifdef LANGUAGE_VIETNAM
//				wsprintf(temp1, STRMSG_C_070910_0202, m_OutPostNextWarTime.Day, m_OutPostNextWarTime.Month,
//																m_OutPostNextWarTime.Year);
//				#else
//				wsprintf(temp1, STRMSG_C_070910_0202, m_OutPostNextWarTime.Year, m_OutPostNextWarTime.Month,
//																m_OutPostNextWarTime.Day);
//				#endif
//				m_pFontExp->DrawText(nPosX,nPosY,
//												GUI_FONT_COLOR,
//												temp1,0L);
				// end 2007-09-20 by bhsohn ��Ʈ�� ��, ��, �� ��ġ ����
				// 2007-10-05 by bhsohn ��,��,�� ��Ʈ�� �ý��� �߰�
				string szStrBuf;
				m_OutPostNextWarTime.GetLocalString_YYYYMMDD(m_OutPostNextWarTime.Year, 
																m_OutPostNextWarTime.Month, 
																m_OutPostNextWarTime.Day, szStrBuf,GetLanguageType());	
				m_pFontExp->DrawText(nPosX,nPosY,
												GUI_FONT_COLOR,
												(char*)szStrBuf.c_str(),0L);
				// end 2007-10-05 by bhsohn ��,��,�� ��Ʈ�� �ý��� �߰�

				
				// �����
				ATUM_DATE_TIME tmpDstDateTime = m_OutPostNextWarTime;
				tmpDstDateTime.AddDateTime(0,0,0,0,OUTPOST_WARTIME,0);

				nPosX = OUTPOST_NEXT_WARTIME_TIME_FONT_X;
				nPosY = OUTPOST_NEXT_WARTIME_TIME_FONT_Y;
				wsprintf(temp1, STRMSG_C_070910_0203, m_OutPostNextWarTime.Hour, m_OutPostNextWarTime.Minute,
																tmpDstDateTime.Hour, tmpDstDateTime.Minute);
				m_pFontExp->DrawText(nPosX,nPosY,
												GUI_FONT_COLOR,
												temp1,0L);

			}
			
			// 2008-10-13 by dgwoo �������� �ð������ϴ� �κ� ������ 
			// ���̵� ��ư ����
			//RenderRadioBtn();			

//			m_pImgOkB[m_nOkB]->Move(OUTPOST_OK_BUTTON_X,OUTPOST_OK_BUTTON_Y);
//			m_pImgOkB[m_nOkB]->Render();
			m_pWarNextOkBtn->Render();
		}
		break;
	case OUTPOST_STATE_WARINFO:
		{
			RenderWarInfo();
		}
		break;
	}
}
void CINFCityOutPost::RenderWarInfo()
{
	SIZE sz;
	char buf[32],rbuf[32];
	switch(m_bStateWarInfo)
	{
	case LEADER_WARINFO_INFLUENCE:
		{
			
			m_pImgWarInfoBG[LEADER_WARINFO_INFLUENCE]->Move(LEADER_WARINFO_BG_X,LEADER_WARINFO_BG_Y);
			m_pImgWarInfoBG[LEADER_WARINFO_INFLUENCE]->Render();

			if(IS_VCN_INFLUENCE_TYPE(g_pShuttleChild->GetMyShuttleInfo().InfluenceType))
			{// ����������.
				m_pImgWarInfoInflBcu->Move(WARINFO_INFLUENCE_BG1_X,WARINFO_INFLUENCE_BG1_Y);
				m_pImgWarInfoInflBcu->Render();
				m_pImgWarInfoInflAni->Move(WARINFO_INFLUENCE_BG2_X,WARINFO_INFLUENCE_BG2_Y);
				m_pImgWarInfoInflAni->Render();
				// �Ʊ� ����.
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.VCNInfluenceLeader);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.VCNInfluenceLeader);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.VCNInfluenceSubLeader1);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER1_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.VCNInfluenceSubLeader1);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.VCNInfluenceSubLeader2);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER2_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.VCNInfluenceSubLeader2);
				wsprintf(buf,"%d",m_sInfluenceInfo.VCNInfluencePoint);
				MakeCurrencySeparator(rbuf,buf,3,',');
				sz = m_pFontExp->GetStringSize(rbuf);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_POINT_Y,
					GUI_FONT_COLOR,rbuf);
				// ��� ����.
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.ANIInfluenceLeader);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.ANIInfluenceLeader);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.ANIInfluenceSubLeader1);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER1_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.ANIInfluenceSubLeader1);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.ANIInfluenceSubLeader2);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER2_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.ANIInfluenceSubLeader2);
				wsprintf(buf,"%d",m_sInfluenceInfo.ANIInfluencePoint);
				MakeCurrencySeparator(rbuf,buf,3,',');
				sz = m_pFontExp->GetStringSize(rbuf);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_POINT_Y,
					GUI_FONT_COLOR,rbuf);
			}
			else if(IS_ANI_INFLUENCE_TYPE(g_pShuttleChild->GetMyShuttleInfo().InfluenceType))
			{// �˸���.
				m_pImgWarInfoInflAni->Move(WARINFO_INFLUENCE_BG1_X,WARINFO_INFLUENCE_BG1_Y);
				m_pImgWarInfoInflAni->Render();
				m_pImgWarInfoInflBcu->Move(WARINFO_INFLUENCE_BG2_X,WARINFO_INFLUENCE_BG2_Y);
				m_pImgWarInfoInflBcu->Render();
				// �Ʊ� ����.
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.ANIInfluenceLeader);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.ANIInfluenceLeader);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.ANIInfluenceSubLeader1);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER1_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.ANIInfluenceSubLeader1);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.ANIInfluenceSubLeader2);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER2_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.ANIInfluenceSubLeader2);
				wsprintf(buf,"%d",m_sInfluenceInfo.ANIInfluencePoint);
				MakeCurrencySeparator(rbuf,buf,3,',');
				sz = m_pFontExp->GetStringSize(rbuf);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_1_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_POINT_Y,
					GUI_FONT_COLOR,rbuf);
				// ��� ����.
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.VCNInfluenceLeader);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.VCNInfluenceLeader);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.VCNInfluenceSubLeader1);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER1_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.VCNInfluenceSubLeader1);
				sz = m_pFontExp->GetStringSize(m_sInfluenceInfo.VCNInfluenceSubLeader2);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_LEADER2_Y,
					GUI_FONT_COLOR,m_sInfluenceInfo.VCNInfluenceSubLeader2);
				wsprintf(buf,"%d",m_sInfluenceInfo.VCNInfluencePoint);
				MakeCurrencySeparator(rbuf,buf,3,',');
				sz = m_pFontExp->GetStringSize(rbuf);
				m_pFontExp->DrawText(WARINFO_INFLUENCE_FONT_2_CENTER_X - (sz.cx/2),WARINFO_INFLUENCE_FONT_POINT_Y,
					//GUI_FONT_COLOR,buf);
					GUI_FONT_COLOR,rbuf);// 2008-11-3 by bhsohn �������� �ʿ��� ������Ʈ ���� ��©���� ������ ���� ����
			}

		}
		break;

		
		// 2009. 01. 12 by ckPark ���� ���� �ý���
	case LEADER_WARINFO_DECLAREWAR:
		{
			m_pImgWarInfoBG[LEADER_WARINFO_DECLAREWAR]->Move(LEADER_WARINFO_BG_X,LEADER_WARINFO_BG_Y);
			m_pImgWarInfoBG[LEADER_WARINFO_DECLAREWAR]->Render();
			
			RenderWarInfoDeclareWar();
		}
		break;
		// end 2009. 01. 12 by ckPark ���� ���� �ý���

	case LEADER_WARINFO_MOTHERSHIP:
		{
			m_pImgWarInfoBG[LEADER_WARINFO_MOTHERSHIP]->Move(LEADER_WARINFO_BG_X,LEADER_WARINFO_BG_Y);
			m_pImgWarInfoBG[LEADER_WARINFO_MOTHERSHIP]->Render();

			// 2008-10-16 by bhsohn �������� ����, ������ ����â
			RenderWarInfoMothership();
		}
		break;

	case LEADER_WARINFO_OUTPOST:
		{
			
			m_pImgWarInfoBG[LEADER_WARINFO_OUTPOST]->Move(LEADER_WARINFO_BG_X,LEADER_WARINFO_BG_Y);
			m_pImgWarInfoBG[LEADER_WARINFO_OUTPOST]->Render();
			int i = 0;
			vector<ST_WARINFO_OUTPOST>::iterator it = m_vecOutPostInfo.begin();
			
			while(it != m_vecOutPostInfo.end())
			{
				{//������.
					memset(buf,0x00,32);
					MAP_INFO * pMapInfo = g_pDatabase->GetMapInfo(it->MapIndex);
					
					sz = m_pFontExp->GetStringSize(pMapInfo->MapName);
					m_pFontExp->DrawText(WARINFO_OUTPOST_FONT_OUTPOST_CENTER_X-(sz.cx/2),WARINFO_OUTPOST_FONT_DATA_1_Y + (i * WARINFO_OUTPOST_FONT_H),
						GUI_FONT_COLOR,pMapInfo->MapName);

					if(IS_VCN_INFLUENCE_TYPE(it->Influence))
					{
						wsprintf(buf,STRMSG_C_070608_0100);
					}else if(IS_ANI_INFLUENCE_TYPE(it->Influence))
					{
						wsprintf(buf,STRMSG_C_070608_0101);
					}
					sz = m_pFontExp->GetStringSize(buf);
					
					m_pFontExp->DrawText(WARINFO_OUTPOST_FONT_INFLUENCE_CENTER_X-(sz.cx/2),WARINFO_OUTPOST_FONT_DATA_1_Y + (i * WARINFO_OUTPOST_FONT_H),
						GUI_FONT_COLOR,buf);

					// 2007-12-17 by dgwoo �������̽� ����.
					wsprintf(buf,"%s",it->GuildCommander);
					sz = m_pFontExp->GetStringSize(buf);
					m_pFontExp->DrawText(WARINFO_OUTPOST_FONT_GUILD_CENTER_X-(sz.cx/2),WARINFO_OUTPOST_FONT_DATA_1_GUILDLEADER_Y + (i * WARINFO_OUTPOST_FONT_H),
						GUI_FONT_COLOR,buf);

					wsprintf(buf,"%s",it->GuildName);
					sz = m_pFontExp->GetStringSize(buf);
					float fIsGuild = 0;
					if(it->pGuildMark)
					{
						fIsGuild = 12;
					}
					m_pFontExp->DrawText(WARINFO_OUTPOST_FONT_GUILD_CENTER_X-(sz.cx/2)+fIsGuild,WARINFO_OUTPOST_FONT_DATA_1_GUILDNAME_Y + (i * WARINFO_OUTPOST_FONT_H),
						GUI_FONT_COLOR,buf);
					// ��� ��ũ.
					if(it->pGuildMark != NULL)
					{
						it->pGuildMark->Move(WARINFO_OUTPOST_FONT_GUILD_CENTER_X-(sz.cx/2)-12,WARINFO_OUTPOST_GUILDMARK_1_Y + (i * WARINFO_OUTPOST_FONT_H));
						it->pGuildMark->Render();
					}

					int nPosX, nPosY;
					char temp1[512];
					nPosX = nPosY = 0;
					nPosX = WARINFO_OUTPOST_FONT_SCHEDULE_CENTER_X;
					nPosY = WARINFO_OUTPOST_FONT_DATA_1_Y + (i * WARINFO_OUTPOST_FONT_H);
					if(it->OutpostDate.Year != 0)
					{					
						// 2007-10-05 by bhsohn ��,��,�� ��Ʈ�� �ý��� �߰�
						// ���Ͻ�				
		//				wsprintf(temp1, STRMSG_C_070910_0205, m_OutPostNextWarTime.Month,
		//														m_OutPostNextWarTime.Day,
		//														m_OutPostNextWarTime.Hour);	
						string szStrBuf;
						it->OutpostDate.GetLocalString_MMDD(it->OutpostDate.Month, it->OutpostDate.Day, szStrBuf,GetLanguageType());						
						// 2007-10-08 by bhsohn ���������� �ð� ǥ�� ����
						//wsprintf(temp1, STRMSG_C_070910_0205, szStrBuf.c_str(), m_OutPostNextWarTime.Hour);	
						wsprintf(temp1, STRMSG_C_071030_0101, szStrBuf.c_str(), it->OutpostDate.Hour, it->OutpostDate.Minute);	
						sz = m_pFontExp->GetStringSize(temp1);
						m_pFontExp->DrawText(nPosX-(sz.cx/2),nPosY, GUI_FONT_COLOR,temp1,0L);
						// end 2007-10-05 by bhsohn ��,��,�� ��Ʈ�� �ý��� �߰�
					}
					else
					{
						//wsprintf(temp1, STRMSG_C_070910_0206);	
					}
					
					
				}
				it++;
				i++;
			}
		}
		break;
	case LEADER_WARINFO_POINT:
		{
			m_pImgWarInfoBG[LEADER_WARINFO_POINT]->Move(LEADER_WARINFO_BG_X,LEADER_WARINFO_BG_Y);
			m_pImgWarInfoBG[LEADER_WARINFO_POINT]->Render();

			// 2008-10-16 by bhsohn �������� ����, ������ ����â
			RenderWarInfoPointWar();
		}
		break;
	}
}
void CINFCityOutPost::RenderRadioBtn()
{	
	int i;
	int nPosX, nPosY;
	char temp1[512];
	ZERO_MEMORY(temp1);				

	vector<ATUM_DATE_TIME>::iterator itTimeList = m_vecNextWarTimeList.begin();
	for(i = 0 ; i < m_nWarTimeMaxCount ; i++)
	{
		nPosX = OUTPOST_WARTIME_RADIO_BUTTON_START_X;
		nPosY = OUTPOST_WARTIME_RADIO_BUTTON_START_Y + (OUTPOST_WARTIME_RADIO_BUTTON_GAP_Y * i);
		if(i == m_nSelWarTimeRadioB)
		{
			m_pImgRadioB[RADIOBUTTON_STATE_SELECT]->Move(nPosX,nPosY);
			m_pImgRadioB[RADIOBUTTON_STATE_SELECT]->Render();
		}
		else
		{
			m_pImgRadioB[RADIOBUTTON_STATE_NORMAL]->Move(nPosX,nPosY);
			m_pImgRadioB[RADIOBUTTON_STATE_NORMAL]->Render();
		}				
		{
			// �ð��� ����ش�.
			nPosX = OUTPOST_SEL_WARTIME_FONT_X;
			nPosY = OUTPOST_SEL_WARTIME_FONT_Y + (OUTPOST_SEL_WARTIME_FONT_GAP_H * i);
			
			if(itTimeList != m_vecNextWarTimeList.end())
			{
				ATUM_DATE_TIME tmpDstDateTime = (*itTimeList);						
				tmpDstDateTime.AddDateTime(0,0,0,0,OUTPOST_WARTIME,0);
				
				wsprintf(temp1, STRMSG_C_070910_0203, (*itTimeList).Hour, (*itTimeList).Minute,
					tmpDstDateTime.Hour, tmpDstDateTime.Minute);
				m_pFontExp->DrawText(nPosX,nPosY,
					GUI_FONT_COLOR,
					temp1,0L);
				itTimeList++;
			}				
			
		}				
	}	
}
void CINFCityOutPost::Tick()
{
}
int CINFCityOutPost::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > OUTPOST_BRIGADE_NOTICE_BUTTON_X &&
				pt.x < OUTPOST_BRIGADE_NOTICE_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_BRIGADE_NOTICE_BUTTON_Y &&
				pt.y < OUTPOST_BRIGADE_NOTICE_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				m_nBrigadeNoticeB = BUTTON_STATE_NORMAL;
				ChangeOutPostState(OUTPOST_STATE_NOTICE);
			}
			if(pt.x > OUTPOST_EXPENCE_BUTTON_X &&
				pt.x < OUTPOST_EXPENCE_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_EXPENCE_BUTTON_Y &&
				pt.y < OUTPOST_EXPENCE_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				if(TRUE == g_pD3dApp->IsMyShuttleGuildMaster())
				{
					m_nExpenceB = BUTTON_STATE_NORMAL;
					ChangeOutPostState(OUTPOST_STATE_EXPENCE);
				}			
				else
				{
					m_nExpenceB = BUTTON_STATE_DISABLE ;
				}
			}
			if(pt.x > OUTPOST_WAR_TIME_SET_BUTTON_X &&
				pt.x < OUTPOST_WAR_TIME_SET_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_WAR_TIME_SET_BUTTON_Y &&
				pt.y < OUTPOST_WAR_TIME_SET_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				m_nOutPostWarTimeB = BUTTON_STATE_NORMAL;
				ChangeOutPostState(OUTPOST_STATE_WARTIME);
			}
			if(m_pImgLWarInfoB->OnLButtonUp(pt))
			{
				ChangeOutPostState(OUTPOST_STATE_WARINFO);
			}


		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > OUTPOST_BRIGADE_NOTICE_BUTTON_X &&
				pt.x < OUTPOST_BRIGADE_NOTICE_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_BRIGADE_NOTICE_BUTTON_Y &&
				pt.y < OUTPOST_BRIGADE_NOTICE_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				m_nBrigadeNoticeB = BUTTON_STATE_DOWN;
			}
			if(pt.x > OUTPOST_EXPENCE_BUTTON_X &&
				pt.x < OUTPOST_EXPENCE_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_EXPENCE_BUTTON_Y &&
				pt.y < OUTPOST_EXPENCE_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				if(TRUE == g_pD3dApp->IsMyShuttleGuildMaster())
				{
					m_nExpenceB = BUTTON_STATE_DOWN;
				}
				else
				{
					m_nExpenceB = BUTTON_STATE_DISABLE ;
				}
			}
			if(pt.x > OUTPOST_WAR_TIME_SET_BUTTON_X &&
				pt.x < OUTPOST_WAR_TIME_SET_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_WAR_TIME_SET_BUTTON_Y &&
				pt.y < OUTPOST_WAR_TIME_SET_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				m_nOutPostWarTimeB = BUTTON_STATE_DOWN;
			}
			m_pImgLWarInfoB->OnLButtonDown(pt);

		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > OUTPOST_BRIGADE_NOTICE_BUTTON_X &&
				pt.x < OUTPOST_BRIGADE_NOTICE_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_BRIGADE_NOTICE_BUTTON_Y &&
				pt.y < OUTPOST_BRIGADE_NOTICE_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				if(m_nBrigadeNoticeB != BUTTON_STATE_DOWN)
				{
					m_nBrigadeNoticeB = BUTTON_STATE_UP;
				}
			}
			else
			{
				m_nBrigadeNoticeB = BUTTON_STATE_NORMAL;
			}

			
			if(pt.x > OUTPOST_EXPENCE_BUTTON_X &&
				pt.x < OUTPOST_EXPENCE_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_EXPENCE_BUTTON_Y &&
				pt.y < OUTPOST_EXPENCE_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				if(TRUE == g_pD3dApp->IsMyShuttleGuildMaster())
				{
					if(m_nExpenceB != BUTTON_STATE_DOWN)
					{
						m_nExpenceB = BUTTON_STATE_UP;
					}
				}
				else
				{
					m_nExpenceB = BUTTON_STATE_DISABLE ;
				}
			}
			else
			{
				if(TRUE == g_pD3dApp->IsMyShuttleGuildMaster())
				{
					m_nExpenceB = BUTTON_STATE_NORMAL;
				}
				else
				{
					m_nExpenceB = BUTTON_STATE_DISABLE ;
				}
			}
			if(pt.x > OUTPOST_WAR_TIME_SET_BUTTON_X &&
				pt.x < OUTPOST_WAR_TIME_SET_BUTTON_X + OUTPOST_LEFT_BUTTON_W &&
				pt.y > OUTPOST_WAR_TIME_SET_BUTTON_Y &&
				pt.y < OUTPOST_WAR_TIME_SET_BUTTON_Y + OUTPOST_LEFT_BUTTON_H)
			{
				if(m_nOutPostWarTimeB != BUTTON_STATE_DOWN)
				{
					m_nOutPostWarTimeB = BUTTON_STATE_UP;
				}
			}
			else
			{
				m_nOutPostWarTimeB = BUTTON_STATE_NORMAL;
			}
			m_pImgLWarInfoB->OnMouseMove(pt);
		}
		break;
	}
	switch(m_nRWindowState)
	{
	case OUTPOST_STATE_NOTICE:
		{
			if(INF_MSGPROC_BREAK == WndProcNotice(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case OUTPOST_STATE_EXPENCE:
		{
			if(INF_MSGPROC_BREAK == WndProcExpence(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case OUTPOST_STATE_WARTIME:
		{
			if(INF_MSGPROC_BREAK == WndProcWarTime(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case OUTPOST_STATE_WARINFO:
		{
			if(INF_MSGPROC_BREAK == WndProcWarInfo(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityOutPost::WndProcNotice(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			// 2007-09-05 by bhsohn ���� ������
			//			if(pt.x > OUTPOST_WRITE_BUTTON_X &&
			//				pt.x < OUTPOST_WRITE_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
			//				pt.y > OUTPOST_WRITE_BUTTON_Y &&
			//				pt.y < OUTPOST_WRITE_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			//			{
			//				m_nWriteB = BUTTON_STATE_NORMAL;
			//			}
			{
				if(TRUE == m_pNoticeWrite->OnLButtonUp(pt))
				{	
					// ��ư Ŭ�� 
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					// ��ư Ŭ��
					ButtonClickWrite();					
					return  INF_MSGPROC_BREAK;
				}
			}
			
			{
				if(TRUE == m_pRegist->OnLButtonUp(pt))
				{	
					// ��ư Ŭ�� 
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					// ��ư Ŭ��
					ButtonClickApp();					
					return  INF_MSGPROC_BREAK;
				}
			}
			
			//			if(pt.x > OUTPOST_REV_BUTTON_X &&
			//				pt.x < OUTPOST_REV_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
			//				pt.y > OUTPOST_REV_BUTTON_Y &&
			//				pt.y < OUTPOST_REV_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			//			{
			//				m_nRevB = BUTTON_STATE_NORMAL;
			//			}
			//			if(pt.x > OUTPOST_DEL_BUTTON_X &&
			//				pt.x < OUTPOST_DEL_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
			//				pt.y > OUTPOST_DEL_BUTTON_Y &&
			//				pt.y < OUTPOST_DEL_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			//			{
			//				m_nDelB = BUTTON_STATE_NORMAL;
			//			}
			if(pt.x > OUTPOST_APP_BUTTON_X &&
				pt.x < OUTPOST_APP_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
				pt.y > OUTPOST_APP_BUTTON_Y &&
				pt.y < OUTPOST_APP_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			{
				m_nAppB = BUTTON_STATE_NORMAL;
			}
			{
				BOOL bClick = m_pINFScrollBar->GetMouseMoveMode();
				if(bClick)		
				{
					m_pINFScrollBar->SetMouseMoveMode(FALSE);	
					return INF_MSGPROC_BREAK;
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
			// 2007-09-05 by bhsohn ���� ������
//			if(pt.x > OUTPOST_WRITE_BUTTON_X &&
//				pt.x < OUTPOST_WRITE_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
//				pt.y > OUTPOST_WRITE_BUTTON_Y &&
//				pt.y < OUTPOST_WRITE_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
//			{
//				m_nWriteB = BUTTON_STATE_DOWN;
//			}
			// ���� ��ư
			{
				if(TRUE == m_pNoticeWrite->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}
			
			{
				if(TRUE == m_pRegist->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}
			
//			if(pt.x > OUTPOST_REV_BUTTON_X &&
//				pt.x < OUTPOST_REV_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
//				pt.y > OUTPOST_REV_BUTTON_Y &&
//				pt.y < OUTPOST_REV_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
//			{
//				m_nRevB = BUTTON_STATE_DOWN;
//			}
//			if(pt.x > OUTPOST_DEL_BUTTON_X &&
//				pt.x < OUTPOST_DEL_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
//				pt.y > OUTPOST_DEL_BUTTON_Y &&
//				pt.y < OUTPOST_DEL_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
//			{
//				m_nDelB = BUTTON_STATE_DOWN;
//			}
			if(pt.x > OUTPOST_APP_BUTTON_X &&
				pt.x < OUTPOST_APP_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
				pt.y > OUTPOST_APP_BUTTON_Y &&
				pt.y < OUTPOST_APP_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			{
				m_nAppB = BUTTON_STATE_DOWN;
			}

			{
				BOOL bClick = m_pINFScrollBar->IsMouseBallPos(pt);
				if(bClick)		
				{
					m_pINFScrollBar->SetMouseMoveMode(TRUE);
					return INF_MSGPROC_BREAK;
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

			// 2007-09-05 by bhsohn ���� ������
			m_pNoticeWrite->OnMouseMove(pt);
			m_pRegist->OnMouseMove(pt);
//			if(pt.x > OUTPOST_WRITE_BUTTON_X &&
//				pt.x < OUTPOST_WRITE_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
//				pt.y > OUTPOST_WRITE_BUTTON_Y &&
//				pt.y < OUTPOST_WRITE_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
//			{
//				if(m_nWriteB != BUTTON_STATE_DOWN)
//				{
//					m_nWriteB = BUTTON_STATE_UP;
//				}
//			}
//			else
//			{
//				m_nWriteB = BUTTON_STATE_NORMAL;
//			}

//			if(pt.x > OUTPOST_REV_BUTTON_X &&
//				pt.x < OUTPOST_REV_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
//				pt.y > OUTPOST_REV_BUTTON_Y &&
//				pt.y < OUTPOST_REV_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
//			{
//				if(m_nRevB != BUTTON_STATE_DOWN)
//				{
//					m_nRevB = BUTTON_STATE_UP;
//				}
//			}
//			else
//			{
//				m_nRevB = BUTTON_STATE_NORMAL;
//			}
//			if(pt.x > OUTPOST_DEL_BUTTON_X &&
//				pt.x < OUTPOST_DEL_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
//				pt.y > OUTPOST_DEL_BUTTON_Y &&
//				pt.y < OUTPOST_DEL_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
//			{
//				if(m_nDelB != BUTTON_STATE_DOWN)
//				{
//					m_nDelB = BUTTON_STATE_UP;
//				}
//			}
//			else
//			{
//				m_nDelB = BUTTON_STATE_NORMAL;
//			}
			if(pt.x > OUTPOST_APP_BUTTON_X &&
				pt.x < OUTPOST_APP_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
				pt.y > OUTPOST_APP_BUTTON_Y &&
				pt.y < OUTPOST_APP_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			{
				if(m_nAppB != BUTTON_STATE_DOWN)
				{
					m_nAppB = BUTTON_STATE_UP;
				}
			}
			else
			{
				m_nAppB = BUTTON_STATE_NORMAL;
			}
			{
				if(m_pINFScrollBar->GetMouseMoveMode())
				{
					if(FALSE == m_pINFScrollBar->IsMouseScrollPos(pt))
					{
						m_pINFScrollBar->SetMouseMoveMode(FALSE);						
					}
					else
					{
						m_pINFScrollBar->SetScrollPos(pt);	
						return INF_MSGPROC_BREAK;
					}								
				}
			}
		}
		break;
	case WM_IME_STARTCOMPOSITION:
//	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_SETCONTEXT:	
	case WM_CHAR:
	case WM_KEYDOWN:	// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
	// 2010. 04. 12 by ckPark �������� ���� ����Ʈ �ڽ� ��� ����
	case WM_KEYUP:
	// end 2010. 04. 12 by ckPark �������� ���� ����Ʈ �ڽ� ��� ����
		{
			// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
			if(m_pNoticeEditBox->IsEditMode())
			{				
				int nLienCnt = -1;
				int nArrowScroll = 0;
				BOOL bRtn = FALSE;
				BOOL bStrCat =FALSE;
				bRtn = m_pNoticeEditBox->WndProc(uMsg, wParam, lParam, m_pINFScrollBar->GetScrollStep(), 
					&nLienCnt, &nArrowScroll, &bStrCat);
				
				if(nLienCnt < 0)
				{
					// �ƹ� ó���� ���ߴ�.
					return INF_MSGPROC_NORMAL;
				}			
				int nMaxStep = 0;			
				int nScrollStep = 0;
				switch(uMsg)
				{
				case WM_KEYDOWN:
					{
						switch(wParam)
						{
						case VK_LEFT:	// �������� �̵�
						case VK_UP:
						case VK_RIGHT:
						case VK_DOWN:
							{
								// ����Ű�� ������ ��ũ�� ��ġ ���� 
								if(nLienCnt > MAX_SCROLL_LINE 
									&& nArrowScroll !=0)
								{
									nMaxStep = m_pINFScrollBar->GetMaxStepCnt();
									nScrollStep = m_pINFScrollBar->GetScrollStep() + nArrowScroll;
									nScrollStep = max(0, nScrollStep);						
									nScrollStep = min(nMaxStep, nScrollStep);						
									m_pINFScrollBar->SetScrollStep(nScrollStep);
								}
								
								return INF_MSGPROC_NORMAL;
							}
							break;
						case VK_RETURN:
							{
								return INF_MSGPROC_BREAK;
							}
							break;
						}
					}
					break;
				}
				
				nMaxStep = max(nLienCnt, MAX_SCROLL_LINE);
				nScrollStep = nMaxStep - MAX_SCROLL_LINE;
				if(nScrollStep < 0)
				{
					nScrollStep = 0;
				}						
				if(m_pNoticeEditBox->IsLastPos())
				{
					// ���� ������ �����̳�?					
					
					// �ִ� �������� �����ְ�
					m_pINFScrollBar->SetMaxItem(nMaxStep);					
					// ��Ʈ���� �ڿ� ���̴� ����� �ƴϴ�.
					// ��ũ�� ��ġ�� ���� �Ʒ�
					m_pINFScrollBar->SetScrollStep(nScrollStep);								
				}					
				else
				{
					m_pINFScrollBar->SetOnlyMaxItem(nMaxStep);
					m_pNoticeEditBox->RefreshEndCurselPos();	// ��������ġ ����
				}
				
				if(bRtn)
				{
					return INF_MSGPROC_BREAK;
				}					
				
			}		
			
			
			// end 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
//			if(m_bWriteMode)
//			{
//				int bFlag = FALSE;
//				g_nRenderCandidate = SET_MAIN_CHAT_CANDIDATE;
//
//				if(INF_MSGPROC_BREAK == g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam))
//					bFlag = TRUE;
//				/*--------------------------------------------------------------------------*/				
//				if(strlen(g_pD3dApp->m_inputkey.m_full_str)!=0)
//				{
//					memset(m_cNoticeString,0x00,SIZE_MAX_CHAT_MESSAGE);
//					if(wParam == 34 && g_pD3dApp->m_pShuttleChild->m_bOldPToPPos != 200 && g_pD3dApp->m_inputkey.m_str_pos == 1)
//					{
//						char tempName[SIZE_MAX_CHARACTER_NAME+2] = {0,};
//						wsprintf(tempName, "%s ", g_pD3dApp->m_pShuttleChild->m_strChatPToP[g_pD3dApp->m_pShuttleChild->m_bOldPToPPos]);
//
//						int nNameSize = strlen(tempName);
//						wchar_t wTmName[SIZE_MAX_CHARACTER_NAME];
//						memset(wTmName, 0x00, sizeof(wTmName[0])*SIZE_MAX_CHARACTER_NAME);
//						MultiByteToWideChar(g_input.GetCodePage(), 0, tempName, nNameSize + 1, wTmName, nNameSize + 1);
//						for(int j = 0; j < wcslen(wTmName); j++)
//						{
//							g_input.SetInputWideChar(wTmName[j]);
//						}
//
//						g_pD3dApp->m_inputkey.SetGameText(g_pD3dApp->m_inputkey.GetInputLanguage());
//
//					}
//					strncpy(m_cNoticeString,g_pD3dApp->m_inputkey.m_full_str,strlen(g_pD3dApp->m_inputkey.m_full_str));
//				}
//				else
//				{
//					memset(m_cNoticeString,0x00,sizeof(m_cNoticeString));
//					
//				}
//				/*--------------------------------------------------------------------------*/
//		
//				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_INPUT_CHAT, g_pShuttleChild->m_vPos, FALSE);
//				if(TRUE == bFlag)
//					return INF_MSGPROC_BREAK;
//			}
		}
		break;
		// 2008-10-29 by bhsohn ����Ʈ �ڽ� ���� ����
//	case WM_KEYDOWN:
//		{
//			if(m_pNoticeEditBox->WndProc(uMsg, wParam, lParam))
//			{
//				return INF_MSGPROC_BREAK;
//			}
//		}
//		break;
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			BOOL bClick = m_pINFScrollBar->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pINFScrollBar->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityOutPost::WndProcExpence(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > OUTPOST_EXPENCE_OK_BUTTON_X &&
				pt.x < OUTPOST_EXPENCE_OK_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
				pt.y > OUTPOST_EXPENCE_OK_BUTTON_Y &&
				pt.y < OUTPOST_EXPENCE_OK_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			{
				m_nExpenceOkB = BUTTON_STATE_NORMAL;
			}

			// 2007-09-05 by bhsohn ���� ������
			{
				if(TRUE == m_pExpenceOkBtn->OnLButtonUp(pt))
				{					
					// ��ư Ŭ�� 
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					OnClickExpenceOk();
					return  INF_MSGPROC_BREAK;
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
			if(pt.x > OUTPOST_EXPENCE_OK_BUTTON_X &&
				pt.x < OUTPOST_EXPENCE_OK_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
				pt.y > OUTPOST_EXPENCE_OK_BUTTON_Y &&
				pt.y < OUTPOST_EXPENCE_OK_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			{
				m_nExpenceOkB = BUTTON_STATE_DOWN;
			}

			// 2007-09-05 by bhsohn ���� ������
			{
				if(TRUE == m_pExpenceOkBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
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
			if(pt.x > OUTPOST_EXPENCE_OK_BUTTON_X &&
				pt.x < OUTPOST_EXPENCE_OK_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
				pt.y > OUTPOST_EXPENCE_OK_BUTTON_Y &&
				pt.y < OUTPOST_EXPENCE_OK_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
			{
				if(m_nExpenceOkB != BUTTON_STATE_DOWN)
				{
					m_nExpenceOkB = BUTTON_STATE_UP;
				}
			}
			else
			{
				m_nExpenceOkB = BUTTON_STATE_NORMAL;
			}

			// 2007-09-05 by bhsohn ���� ������
			m_pExpenceOkBtn->OnMouseMove(pt);

		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFCityOutPost::OnClickExpenceOk()
{
	char buf[256];
	ZERO_MEMORY(buf);
	wsprintf(buf, STRMSG_C_070910_0201);//"������ %s ��� �����ðڽ��ϱ�?"
	((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox(buf,_Q_INFLUENCE_WAR_EXPENCE_OK_MSG, 0, m_nExp);
}

int CINFCityOutPost::WndProcWarTime(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);			
			
			{
				if(TRUE == m_pWarNextOkBtn->OnLButtonUp(pt))
				{	
					// ���������� Ȯ�� ��ư Ŭ�� 
					OnClickNextWarTime();
					// ��ư Ŭ�� 
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					// ��ư Ŭ��					
					return  INF_MSGPROC_BREAK;
				}
			}

			if(g_pD3dApp->IsMyShuttleGuildMaster())
			{
// 2008-10-13 by dgwoo �������� �ð������ϴ� �κ� ������ 
//				int i;
//				for(i = 0 ; i < m_nWarTimeMaxCount ; i++)
//				{
//					if(pt.x > OUTPOST_WARTIME_RADIO_BUTTON_START_X &&
//						pt.x < OUTPOST_WARTIME_RADIO_BUTTON_START_X + OUTPOST_WARTIME_RADIO_BUTTON_W &&
//						pt.y > OUTPOST_WARTIME_RADIO_BUTTON_START_Y + (OUTPOST_WARTIME_RADIO_BUTTON_GAP_Y * i) &&
//						pt.y < OUTPOST_WARTIME_RADIO_BUTTON_START_Y + OUTPOST_WARTIME_RADIO_BUTTON_H + (OUTPOST_WARTIME_RADIO_BUTTON_GAP_Y * i))
//					{
//						SetChangeRadioButton(i);
//					}
//				}
			}


		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);			
			
			{
				if(TRUE == m_pWarNextOkBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
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
//			if(pt.x > OUTPOST_OK_BUTTON_X &&
//				pt.x < OUTPOST_OK_BUTTON_X + OUTPOST_RIGHT_BUTTON_W &&
//				pt.y > OUTPOST_OK_BUTTON_Y &&
//				pt.y < OUTPOST_OK_BUTTON_Y + OUTPOST_RIGHT_BUTTON_H)
//			{
//				if(m_nOkB != BUTTON_STATE_DOWN)
//				{
//					m_nOkB = BUTTON_STATE_UP;
//				}
//			}
//			else
//			{
//				m_nOkB = BUTTON_STATE_NORMAL;
//			}
			m_pWarNextOkBtn->OnMouseMove(pt);
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityOutPost::WndProcWarInfo(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.y > LEADER_WARINFO_TAB_Y &&
				pt.y < LEADER_WARINFO_TAB_Y + LEADER_WARINFO_TAB_H &&
				pt.x > LEADER_WARINFO_TAB_INFLUENCE_X &&
				pt.x < LEADER_WARINFO_TAB_INFLUENCE_X + (LEADER_WARINFO_TAB_W * LEADER_WARINFO_END))
			{
				int nSelTab = (int)((pt.x - LEADER_WARINFO_TAB_INFLUENCE_X)/LEADER_WARINFO_TAB_W);
				ChangeWarInfoState(nSelTab);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
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

	}




	// 2009. 01. 12 by ckPark ���� ���� �ý���
	

// 	// 2008-03-19 by bhsohn ����, ������ ����â
// 	switch(m_bStateWarInfo)
// 	{
// 	case LEADER_WARINFO_MOTHERSHIP:
// 	case LEADER_WARINFO_POINT:
// 		{			
// 			if(INF_MSGPROC_BREAK == WndProcWarInfoSub(uMsg,wParam,lParam))
// 			{
// 				return INF_MSGPROC_BREAK;
// 			}
// 		}
// 		break;
// 	}
// 	// end 2008-03-19 by bhsohn ����, ������ ����â



	switch(m_bStateWarInfo)
	{
	case LEADER_WARINFO_INFLUENCE:
		if( WndProcInfluenceInfoTab( uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
		break;
		
	case LEADER_WARINFO_DECLAREWAR:
		if( WndProcWarDeclareTab( uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
		break;
		
	case LEADER_WARINFO_MOTHERSHIP:
		if( WndProcMotherShipResultTab( uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
		break;

	case LEADER_WARINFO_OUTPOST:
		if( WndProcOutPostTab( uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
		break;
		
	case LEADER_WARINFO_POINT:
		if( WndProcPointWarTab( uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;
		break;
	}
	// end 2009. 01. 12 by ckPark ���� ���� �ý���




	return INF_MSGPROC_NORMAL;
}
// �ǰ��� ���� ���� ������Ʈ
void CINFCityOutPost::SetExpenceInfo(float fExplate,DWORD nCumulativeExp, DWORD nExp)
{
	m_fExplate = fExplate/(10.0f);
	m_nCumulativeExp = nCumulativeExp;
	m_nExp = nExp;

}
// ���� �ð� ���� ���� ó��
void CINFCityOutPost::SetNextWarInfo(ATUM_DATE_TIME OutPostNextWarTime, INT nOutPostNextWarSelectTimeChoice, vector<ATUM_DATE_TIME> vectmpTimeList)
{
// 2008-10-13 by dgwoo �������� �ð������ϴ� �κ� ������
//	m_vecNextWarTimeList.clear();
//	m_nWarTimeMaxCount = vectmpTimeList.size();
//	if(m_nWarTimeMaxCount > MAX_NEXT_WAR_RADIO)
//	{
//		m_nWarTimeMaxCount = MAX_NEXT_WAR_RADIO;
//	}
//	
//	m_OutPostNextWarTime = OutPostNextWarTime;
//	m_nSelWarTimeRadioB = nOutPostNextWarSelectTimeChoice;
//	m_vecNextWarTimeList = vectmpTimeList;	

}
// ���� �ð� ���� 
void CINFCityOutPost::OnClickNextWarTime()
{
	// 2008-11-27 by bhsohn �����ڰ� �������� �ð� ���� �Ҽ� �ִ� ���� ����
	return;
	// end 2008-11-27 by bhsohn �����ڰ� �������� �ð� ���� �Ҽ� �ִ� ���� ����

	INIT_MSG_WITH_BUFFER(MSG_FC_OUTPOST_NEXTWAR_SET_TIME, T_FC_OUTPOST_NEXTWAR_SET_TIME, pSMsg, SendBuf);	
	pSMsg->OutPostNextWarSelectTimeChoice = m_nSelWarTimeRadioB;
	g_pFieldWinSocket->Write(SendBuf, MSG_SIZE(MSG_FC_OUTPOST_NEXTWAR_SET_TIME));	
}
// ���� ���������� �ð� ��û 
void CINFCityOutPost::RqNextWarTime()
{
	g_pFieldWinSocket->SendMsg(T_FC_OUTPOST_NEXTWAR_INFO_REQUEST,NULL,0);
}
// ���� ��������
VOID CINFCityOutPost::ReFresh()
{
	ChangeOutPostState(OUTPOST_STATE_NOTICE);
}
// �ݱ� ��ư Ŭ��
void CINFCityOutPost::OnCloseInfWnd()
{
	m_pNoticeEditBox->InitString();		
	m_pNoticeEditBox->EnableEdit(FALSE, FALSE);

	m_pINFScrollBar->SetMaxItem(0);
}

void CINFCityOutPost::UpdateScrollPos(float fPosX, float fPosY, float fWidth, float fHeight, int nWhellHeight)
{		
	POINT ptScroll;
	RECT rcMouseWhell, rcMousePos;
	
	// �� ��ġ���� 
	rcMouseWhell.left		= fPosX;
	rcMouseWhell.top		= fPosY;
	rcMouseWhell.right		= rcMouseWhell.left + fWidth;
	rcMouseWhell.bottom		= rcMouseWhell.top + nWhellHeight;
	
	
	// ���콺 ��ġ ����
	rcMousePos.left			= fPosX + SCROLL_BALL_POSX;
	rcMousePos.top			= fPosY + SCROLL_BALL_POSY;
	rcMousePos.right		= rcMousePos.left;
	rcMousePos.bottom		= rcMousePos.top;
		
	// Resotre�� �ؾ����� �̹��� ũ�⸦ �˼� �ִ�. 
	m_pINFScrollBar->SetPosition(rcMousePos.left, rcMousePos.top, SCROLL_BALL_WIDTH, fHeight);
	m_pINFScrollBar->SetMouseWhellRect(rcMouseWhell);			

	ptScroll = m_pINFScrollBar->GetImgBkSize();
	
	rcMousePos.bottom		= rcMousePos.top + ptScroll.y + SCROLL_BALL_SCROLL_CAP;
	rcMousePos.top			-= SCROLL_BALL_SCROLL_CAP;
	rcMousePos.right		= rcMousePos.left + SCROLL_BALL_SCROLL_CAP;
	rcMousePos.left			-= SCROLL_BALL_SCROLL_CAP;					
	
	m_pINFScrollBar->SetMouseBallRect(rcMousePos);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityOutPost::AddOutPostInfo(SCITY_WARINFO_OUTPOST * i_pOutPostInfo)
/// \brief		���������� �������� �߰� ��������.
/// \author		dgwoo
/// \date		2007-12-07 ~ 2007-12-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::AddOutPostInfo(SCITY_WARINFO_OUTPOST * i_pOutPostInfo)
{
	ST_WARINFO_OUTPOST stWarInfo;
	memset(&stWarInfo,0x00,sizeof(ST_WARINFO_OUTPOST));
	stWarInfo.GuildUID = i_pOutPostInfo->GuildUID;
	stWarInfo.MapIndex = i_pOutPostInfo->MapIndex;
	stWarInfo.OutpostDate = i_pOutPostInfo->OutpostDate;
	memcpy(stWarInfo.GuildCommander,i_pOutPostInfo->GuildCommander,SIZE_MAX_CHARACTER_NAME);
	memcpy(stWarInfo.GuildName,i_pOutPostInfo->GuildName,SIZE_MAX_GUILD_NAME);
	stWarInfo.Influence = i_pOutPostInfo->Influence;
	if(stWarInfo.GuildUID)
	{
		stWarInfo.pGuildMark = g_pDatabase->GetGuildMark(stWarInfo.GuildUID);
		if(stWarInfo.pGuildMark == NULL)
		{
			MSG_FC_INFO_GET_GUILDMARK sMsg;
			sMsg.GuildUID = stWarInfo.GuildUID;
			g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_GUILDMARK,(char*)&sMsg,sizeof(sMsg));
		}
	}
	m_vecOutPostInfo.push_back(stWarInfo);
}
void CINFCityOutPost::ClearOutPostInfo()
{
	m_vecOutPostInfo.clear();
}
void CINFCityOutPost::SetWarInfoInfluence(MSG_FC_CITY_WARINFO_INFLUENCE_OK *pMsg)
{
	memcpy(&m_sInfluenceInfo,pMsg,sizeof(MSG_FC_CITY_WARINFO_INFLUENCE_OK));
}
BOOL CINFCityOutPost::SetGuildMark(UID32_t i_nGuildUID)
{
	vector<ST_WARINFO_OUTPOST>::iterator it = m_vecOutPostInfo.begin();
	while(it != m_vecOutPostInfo.end())
	{
		if(it->GuildUID == i_nGuildUID)
		{
			it->pGuildMark = g_pDatabase->GetGuildMark(i_nGuildUID);
		}
		it++;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// ���� ���� �ʱ�ȭ
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::InitWarInfoMothership()
{
	m_vecMotherShipInfo.clear();
	m_pScrollMotherShipInfo->SetMaxItem(m_vecMotherShipInfo.size());

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���� ���� ��û
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::RqMotherShipDB()
{
	g_pFieldWinSocket->SendMsg(T_FC_INFO_MSWARINFO_RESULT,NULL,NULL);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::AddWarInfoMothership(BYTE byAttackBelligerence,	// ���ݼ���
											BYTE byWinBelligerence,		// �¸�����
											char* pMonName,				// ���̸�
											int nWarpoint,				// ��������Ʈ
											ATUM_DATE_TIME	timeStartWarTime,	// ���۽ð�
											ATUM_DATE_TIME	timeEndWarTime)		//����ð�	
{
	structMotherShipInfo sMsg;
	memset(&sMsg, 0x00, sizeof(structMotherShipInfo));

	// ���� ����
	if(IS_VCN_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0101);
	}	

	// �¸� ����
	if(IS_VCN_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0101);
	}	
	else if(0 == byWinBelligerence)	// (0:������)
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070607_0102);		
	}
	
	// �� �̸�
	if(pMonName)
	{
		strncpy(sMsg.chMotherShipName, pMonName, SIZE_MAX_MONSTER_NAME);
	}

	// ��������Ʈ
	char chWarPoint[64];								// ��������Ʈ
	wsprintf(chWarPoint, "%d", nWarpoint);
	MakeCurrencySeparator( sMsg.chWarPoint, chWarPoint, 3, ',' );

	// ������ ���� �ð�	
	string szStartStrBuf;
	timeStartWarTime.GetLocalString_MMDD(timeStartWarTime.Month, 
										timeStartWarTime.Day, 
										szStartStrBuf,
										GetLanguageType());	

	// 2008-04-22 by bhsohn ��/������ �������� ������ ǥ�� �ϰ� ����
	if(0 == timeEndWarTime.Year)
	{
		wsprintf(sMsg.chTimeCap, "%s %02d:%02d ~ ", (char*)szStartStrBuf.c_str(), 
												timeStartWarTime.Hour, 
												timeStartWarTime.Minute);
	}
	else
	{
		string szEndStrBuf;
		timeEndWarTime.GetLocalString_MMDD(timeEndWarTime.Month, 
			timeEndWarTime.Day, 
			szEndStrBuf,
			GetLanguageType());	
		
		wsprintf(sMsg.chTimeCap, "%s %02d:%02d ~ %s %02d:%02d ", (char*)szStartStrBuf.c_str(), timeStartWarTime.Hour, timeStartWarTime.Minute,
			(char*)szEndStrBuf.c_str(), timeEndWarTime.Hour, timeEndWarTime.Minute);
	}

	// 2008-08-19 by bhsohn ������, ���� ���� ��ȯ �ð����� ����
	sMsg.SummonTime = timeStartWarTime;

	m_vecMotherShipInfo.push_back(sMsg);	
		
	// 2008-08-19 by bhsohn ������, ���� ���� ��ȯ �ð����� ����
	sort(m_vecMotherShipInfo.begin(), m_vecMotherShipInfo.end(), sort_MotherShip_summontime());	

	m_pScrollMotherShipInfo->SetMaxItem(m_vecMotherShipInfo.size());
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::RenderWarInfoMothership()
{
	// ��ũ�� ����
	m_pScrollMotherShipInfo->Render();


	// 2009. 01. 12 by ckPark ���� ���� �ý���
	//m_pBtnMotherShipInfo->Render();
	// end 2009. 01. 12 by ckPark ���� ���� �ý���




	vector<structMotherShipInfo>::iterator it = m_vecMotherShipInfo.begin();
	int nCnt=0;
	for(nCnt=0; nCnt < m_pScrollMotherShipInfo->GetScrollStep();nCnt++)
	{
		if(it != m_vecMotherShipInfo.end())
		{
			it++;
		}
	}		
	
	int nLine = 0;
	int nX,nY;
	SIZE sizeFont;
	nX = nY = 0;

	while(it != m_vecMotherShipInfo.end())
	{
		if(nLine >= MOTHERSHIP_INFO_VIEW_MAX_SCROLL_LINE)
		{
			break;
		}
		structMotherShipInfo sMsg = (*it);

		// ���ݼ���
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chAttackInfluence);
			nX = MOTHERSHIP_WARINFO_VIEW_ATT_INFL_X - (sizeFont.cx/2);
			nY = MOTHERSHIP_WARINFO_VIEW_ATT_INFL_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chAttackInfluence, 0L);
		}

		// �𼱸� 
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chMotherShipName);
			nX = MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_X - (sizeFont.cx/2);;
			nY = MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chMotherShipName, 0L);
		}

		// ��������Ʈ
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chWarPoint);
			nX = MOTHERSHIP_WARINFO_VIEW_POINT_X - (sizeFont.cx/2);;
			nY = MOTHERSHIP_WARINFO_VIEW_POINT_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chWarPoint, 0L);
		}

		// �ð�
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chTimeCap);
			nX = MOTHERSHIP_WARINFO_VIEW_TIME_X - (sizeFont.cx/2);;
			nY = MOTHERSHIP_WARINFO_VIEW_TIME_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chTimeCap, 0L);
		}

		// �¸� ����
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chWinInfluence);
			nX = MOTHERSHIP_WARINFO_VIEW_WININFL_X - (sizeFont.cx/2);;
			nY = MOTHERSHIP_WARINFO_VIEW_WININFL_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chWinInfluence, 0L);
		}

		it++;
		nLine++;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// ���� ���� �ʱ�ȭ
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::InitWarInfoPointWar()
{
	m_vecWarPointInfo.clear();
	m_pScrollMotherShipInfo->SetMaxItem(m_vecWarPointInfo.size());

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		������ ���� ��û
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::RqPointWarDB()
{
	g_pFieldWinSocket->SendMsg(T_FC_INFO_SPWARINFO_RESULT,NULL,NULL);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::AddWarInfoPointWar(BYTE byAttackBelligerence,	// ���ݼ���
											BYTE byWinBelligerence,		// �¸�����(0:������)
											char* pMapName,				// ���̸�											
											ATUM_DATE_TIME	timeStartWarTime,	// ���۽ð�
											ATUM_DATE_TIME	timeEndWarTime)		//����ð�	
{
	structWarPointInfo sMsg;
	memset(&sMsg, 0x00, sizeof(structWarPointInfo));

	// ���� ����
	if(IS_VCN_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0101);
	}	

	// �¸� ����
	if(IS_VCN_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0101);
	}
	// 2008-04-22 by bhsohn ��/������ �������� ������ ǥ�� �ϰ� ����
	else if(0 == byWinBelligerence) //(0:������)
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070607_0102);		
	}
	// end 2008-04-22 by bhsohn ��/������ �������� ������ ǥ�� �ϰ� ����
	
	// �� �̸�
	if(pMapName)
	{
		strncpy(sMsg.MapName, pMapName, SIZE_MAX_MAP_NAME);
	}

	// ������ ���� �ð�	
	string szStartStrBuf;
	timeStartWarTime.GetLocalString_MMDD(timeStartWarTime.Month, 
										timeStartWarTime.Day, 
										szStartStrBuf,
										GetLanguageType());	

	// 2008-04-22 by bhsohn ��/������ �������� ������ ǥ�� �ϰ� ����
	if(0 == timeEndWarTime.Year)
	{
		wsprintf(sMsg.chTimeCap, "%s %02d:%02d ~ ", (char*)szStartStrBuf.c_str(), 
													timeStartWarTime.Hour, 
													timeStartWarTime.Minute);

	}
	else
	{
		string szEndStrBuf;
		timeEndWarTime.GetLocalString_MMDD(timeEndWarTime.Month, 
			timeEndWarTime.Day, 
			szEndStrBuf,
			GetLanguageType());	
		
		wsprintf(sMsg.chTimeCap, "%s %02d:%02d ~ %s %02d:%02d ", (char*)szStartStrBuf.c_str(), timeStartWarTime.Hour, timeStartWarTime.Minute,
			(char*)szEndStrBuf.c_str(), timeEndWarTime.Hour, timeEndWarTime.Minute);
	}
	// 2008-08-19 by bhsohn ������, ���� ���� ��ȯ �ð����� ����
	sMsg.SummonTime = timeStartWarTime;
	

	m_vecWarPointInfo.push_back(sMsg);
	
	// 2008-08-19 by bhsohn ������, ���� ���� ��ȯ �ð����� ����
	sort(m_vecWarPointInfo.begin(), m_vecWarPointInfo.end(), sort_WarPoint_summontime());	

	m_pScrollMotherShipInfo->SetMaxItem(m_vecWarPointInfo.size());
}


// 2009. 01. 12 by ckPark ���� ���� �ý���

void	CINFCityOutPost::SetWarDeclareTime( const ATUM_DATE_TIME thisWarDeclare, char* pStr )
{
	if(thisWarDeclare.Year == 0)
		sprintf(pStr, STRMSG_C_090113_0321);		// ���� ����
	else
	{
		// %d��%d��%d�� %d:%d
		std::string strYYYYMMDD;
		thisWarDeclare.GetLocalString_YYYYMMDD(thisWarDeclare.Year, thisWarDeclare.Month, thisWarDeclare.Day, strYYYYMMDD, GetLanguageType());
		sprintf(pStr, STRMSG_C_090113_0322, strYYYYMMDD.c_str(), thisWarDeclare.Hour, thisWarDeclare.Minute );
	}
}

void	CINFCityOutPost::RenderWarInfoDeclareWar(void)
{
	m_pBtnWarDeclare->Render();
	
	m_pBtnMotherShipInfo->Render();
	
	m_pFontWarDeclare->DrawText( OUR_THIS_TAKEOFF_X, OUR_THIS_TAKEOFF_Y, GUI_FONT_COLOR, m_szEnemyThisTakeOff );
	m_pFontWarDeclare->DrawText( OUR_NEXT_TAKEOFF_X, OUR_NEXT_TAKEOFF_Y, GUI_FONT_COLOR, m_szEnemyNextTakeOff );
	m_pFontWarDeclare->DrawText( ENEMY_THIS_TAKEOFF_X, ENEMY_THIS_TAKEOFF_Y, GUI_FONT_COLOR,  m_szOurThisTakeOff );
	m_pFontWarDeclare->DrawText( ENEMY_NEXT_TAKEOFF_X, ENEMY_NEXT_TAKEOFF_Y, GUI_FONT_COLOR,  m_szOurNextTakeOff );
	
	m_pFontWarDeclare->DrawText( OUR_THIS_TAKEOFFTIME_X, OUR_THIS_TAKEOFFTIME_Y, GUI_FONT_COLOR, m_szOurThisTakeOffTime );
	m_pFontWarDeclare->DrawText( OUR_NEXT_TAKEOFFTIME_X, OUR_NEXT_TAKEOFFTIME_Y, GUI_FONT_COLOR,  m_szOurNextTakeOffTime );
	m_pFontWarDeclare->DrawText( ENEMY_THIS_TAKEOFFTIME_X, ENEMY_THIS_TAKEOFFTIME_Y, GUI_FONT_COLOR, m_szEnemyThisTakeOffTime );
	m_pFontWarDeclare->DrawText( ENEMY_NEXT_TAKEOFFTIME_X, ENEMY_NEXT_TAKEOFFTIME_Y, GUI_FONT_COLOR, m_szEnemyNextTakeOffTime);
}
// end 2009. 01. 12 by ckPark ���� ���� �ý���


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-10-16 by bhsohn �������� ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityOutPost::RenderWarInfoPointWar()
{
	// ��ũ�� ����
	m_pScrollMotherShipInfo->Render();

	vector<structWarPointInfo>::iterator it = m_vecWarPointInfo.begin();
	int nCnt=0;
	for(nCnt=0; nCnt < m_pScrollMotherShipInfo->GetScrollStep();nCnt++)
	{
		if(it != m_vecWarPointInfo.end())
		{
			it++;
		}
	}		
	
	int nLine = 0;
	int nX,nY;
	SIZE sizeFont;
	nX = nY = 0;

	while(it != m_vecWarPointInfo.end())
	{
		if(nLine >= MOTHERSHIP_INFO_VIEW_MAX_SCROLL_LINE)
		{
			break;
		}
		structWarPointInfo sMsg = (*it);

		// ���ݼ���
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chAttackInfluence);
			nX = POINTWAR_WARINFO_VIEW_ATT_INFL_X - (sizeFont.cx/2);
			nY = POINTWAR_WARINFO_VIEW_ATT_INFL_Y + (nLine*POINTWAR_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chAttackInfluence, 0L);
		}

		// ��������Ʈ ������
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.MapName);
			nX = POINTWAR_WARINFO_VIEW_POINT_X - (sizeFont.cx/2);;
			nY = POINTWAR_WARINFO_VIEW_POINT_Y + (nLine*POINTWAR_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.MapName, 0L);
		}

		// �ð�
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chTimeCap);
			nX = POINTWAR_WARINFO_VIEW_TIME_X - (sizeFont.cx/2);;
			nY = POINTWAR_WARINFO_VIEW_TIME_Y + (nLine*POINTWAR_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chTimeCap, 0L);
		}

		// �¸� ����
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chWinInfluence);
			nX = POINTWAR_WARINFO_VIEW_WININFL_X - (sizeFont.cx/2);;
			nY = POINTWAR_WARINFO_VIEW_WININFL_Y + (nLine*POINTWAR_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chWinInfluence, 0L);
		}

		it++;
		nLine++;
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-19 by bhsohn ����, ������ ����â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityOutPost::WndProcWarInfoSub(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			BOOL bClick = m_pScrollMotherShipInfo->GetMouseMoveMode();
			if(bClick)
			{
				m_pScrollMotherShipInfo->SetMouseMoveMode(FALSE);
				return INF_MSGPROC_BREAK;
			}
			if(TRUE == m_pBtnMotherShipInfo->OnLButtonUp(pt))
			{					
				// ��ư Ŭ�� 
				g_pGameMain->GetINFMotherShipManager()->ShowWindowOption();
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_BUTTON_OK, D3DXVECTOR3(0,0,0), FALSE);
				return  INF_MSGPROC_BREAK;
			}			
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			BOOL bClick = m_pScrollMotherShipInfo->IsMouseBallPos(pt);
			if(bClick)
			{
				m_pScrollMotherShipInfo->SetMouseMoveMode(TRUE);
				return INF_MSGPROC_BREAK;
			}
			if(TRUE == m_pBtnMotherShipInfo->OnLButtonDown(pt))
			{
				// ��ư���� ���콺�� �ִ�.
				return  INF_MSGPROC_BREAK;
			}	
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			m_pBtnMotherShipInfo->OnMouseMove(pt);
			
			if(m_pScrollMotherShipInfo->GetMouseMoveMode())
			{
				if(FALSE == m_pScrollMotherShipInfo->IsMouseScrollPos(pt))
				{
					m_pScrollMotherShipInfo->SetMouseMoveMode(FALSE);
				}
				else
				{
					m_pScrollMotherShipInfo->SetScrollPos(pt);
					return INF_MSGPROC_BREAK;
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
			BOOL bClick = m_pScrollMotherShipInfo->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pScrollMotherShipInfo->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;

	}
	//return INF_MSGPROC_BREAK;
	return INF_MSGPROC_NORMAL;
}



// 2009. 01. 12 by ckPark ���� ���� �ý���
int		CINFCityOutPost::WndProcInfluenceInfoTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return INF_MSGPROC_NORMAL;
}

int		CINFCityOutPost::WndProcMotherShipResultTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 2009-03-13 by bhsohn ���� ���� ��ũ��â ���� ����
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			BOOL bClick = m_pScrollMotherShipInfo->GetMouseMoveMode();
			if(bClick)
			{
				m_pScrollMotherShipInfo->SetMouseMoveMode(FALSE);
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
			BOOL bClick = m_pScrollMotherShipInfo->IsMouseBallPos(pt);
			if(bClick)
			{
				m_pScrollMotherShipInfo->SetMouseMoveMode(TRUE);
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
			
			if(m_pScrollMotherShipInfo->GetMouseMoveMode())
			{
				if(FALSE == m_pScrollMotherShipInfo->IsMouseScrollPos(pt))
					m_pScrollMotherShipInfo->SetMouseMoveMode(FALSE);
				else
				{
					m_pScrollMotherShipInfo->SetScrollPos(pt);
					return INF_MSGPROC_BREAK;
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
			BOOL bClick = m_pScrollMotherShipInfo->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pScrollMotherShipInfo->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	// end 2009-03-13 by bhsohn ���� ���� ��ũ��â ���� ����
	return INF_MSGPROC_NORMAL;
}

int		CINFCityOutPost::WndProcWarDeclareTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);


			if(TRUE == m_pBtnWarDeclare->OnLButtonUp(pt))
			{
				// ��ư Ŭ�� 
				g_pGameMain->GetINFMotherShipManager()->GetWarDeclareWindow()->ShowWarDeclare();
				g_pInterface->SetWindowOrder(WNDWarDecalre);
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_BUTTON_OK, D3DXVECTOR3(0,0,0), FALSE);
				return  INF_MSGPROC_BREAK;
			}			

			if(TRUE == m_pBtnMotherShipInfo->OnLButtonUp(pt))
			{
				// ��ư Ŭ�� 
				g_pGameMain->GetINFMotherShipManager()->ShowWindowOption();
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_BUTTON_OK, D3DXVECTOR3(0,0,0), FALSE);
				return  INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);


			if(TRUE == m_pBtnWarDeclare->OnLButtonDown(pt))
			{
				// ��ư���� ���콺�� �ִ�.
				return  INF_MSGPROC_BREAK;
			}



			if(TRUE == m_pBtnMotherShipInfo->OnLButtonDown(pt))
			{
				// ��ư���� ���콺�� �ִ�.
				return  INF_MSGPROC_BREAK;
			}	
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			m_pBtnWarDeclare->OnMouseMove(pt);
			m_pBtnMotherShipInfo->OnMouseMove(pt);			
		}
		break;	
	}

	return INF_MSGPROC_NORMAL;
}

int		CINFCityOutPost::WndProcOutPostTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return INF_MSGPROC_NORMAL;
}

int		CINFCityOutPost::WndProcPointWarTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			BOOL bClick = m_pScrollMotherShipInfo->GetMouseMoveMode();
			if(bClick)
			{
				m_pScrollMotherShipInfo->SetMouseMoveMode(FALSE);
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
			BOOL bClick = m_pScrollMotherShipInfo->IsMouseBallPos(pt);
			if(bClick)
			{
				m_pScrollMotherShipInfo->SetMouseMoveMode(TRUE);
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
			
			if(m_pScrollMotherShipInfo->GetMouseMoveMode())
			{
				if(FALSE == m_pScrollMotherShipInfo->IsMouseScrollPos(pt))
					m_pScrollMotherShipInfo->SetMouseMoveMode(FALSE);
				else
				{
					m_pScrollMotherShipInfo->SetScrollPos(pt);
					return INF_MSGPROC_BREAK;
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
			BOOL bClick = m_pScrollMotherShipInfo->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pScrollMotherShipInfo->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}

	return INF_MSGPROC_NORMAL;
}
// end 2009. 01. 12 by ckPark ���� ���� �ý���