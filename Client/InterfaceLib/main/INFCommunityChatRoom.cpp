// INFCommunityChatRoom.cpp: implementation of the CINFCommunityChatRoom class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "D3DHanFont.h"
#include "INFScrollBar.h"
#include "INFComboBox.h"
#include "INFGameMain.h"
#include "INFCommunity.h"
#include "GameDataLast.h"
#include "INFImageBtn.h"
#include "INFArenaScrollBar.h"
#include "AtumSound.h"
#include "INFEditBox.h"
#include "ShuttleChild.h"
#include "Chat.h"
#include "INFCommunityChatRoom.h"
#include "INFListBox.h"
#include "INFEditBox.h"
#include "INFImageRadioBtn.h"
#include "INFGameMainChat.h"
#include "INFGameMain.h"
#include "IMSocketManager.h"
#include "INFWindow.h"
#include "INFSecuEditBox.h"
#include "INFGameMainChat.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define CHATROOM_MAIN_W						519
#define CHATROOM_MAIN_H						404


#define CHATROOM_BTN_TIME_GAP				0.5f


#define CHATROOM_TAB_LIST_X					(m_ptCommunityPos.x + 21)
#define CHATROOM_TAB_LIST_Y					(m_ptCommunityPos.y + 49)
#define CHATROOM_TAB_ROOM_X					(m_ptCommunityPos.x + 148)
#define CHATROOM_TAB_ROOM_Y					(m_ptCommunityPos.y + 49)
#define CHATROOM_TAB_W						124
#define CHATROOM_TAB_H						23

#define CHATROOM_LIST_BG_X					(m_ptCommunityPos.x + 21)
#define CHATROOM_LIST_BG_Y					(m_ptCommunityPos.y + 50)
#define CHATROOM_LIST_INFO_BTN_X			(m_ptCommunityPos.x + 216)
#define CHATROOM_LIST_INFO_BTN_Y			(m_ptCommunityPos.y + 363)
#define CHATROOM_LIST_CRE_BTN_X				(m_ptCommunityPos.x + 283)
#define CHATROOM_LIST_CRE_BTN_Y				(m_ptCommunityPos.y + 363)
#define CHATROOM_LIST_ADMIS_BTN_X			(m_ptCommunityPos.x + 350)
#define CHATROOM_LIST_ADMIS_BTN_Y			(m_ptCommunityPos.y + 363)
#define CHATROOM_LIST_UPDATE_BTN_X			(m_ptCommunityPos.x + 417)
#define CHATROOM_LIST_UPDATE_BTN_Y			(m_ptCommunityPos.y + 363)
#define CHATROOM_LIST_DATA_START_X			(m_ptCommunityPos.x + 30)
#define CHATROOM_LIST_DATA_START_Y			(m_ptCommunityPos.y + 103)
#define CHATROOM_LIST_DATA_START_W			452
#define CHATROOM_LIST_DATA_START_H			253
#define CHATROOM_LIST_DATA_GAP_H			(21)
#define CHATROOM_LIST_DATA_NUMBER_FONT_X	(m_ptCommunityPos.x + 53)
#define CHATROOM_LIST_DATA_LOCK_FONT_X		(m_ptCommunityPos.x + 86)
#define CHATROOM_LIST_DATA_SUBJECT_FONT_X	(m_ptCommunityPos.x + 210)
#define CHATROOM_LIST_DATA_RM_FONT_X		(m_ptCommunityPos.x + 350)
#define CHATROOM_LIST_DATA_VOICE_X			(m_ptCommunityPos.x + 340)
#define CHATROOM_LIST_DATA_MAXMEMBER_FONT_X	(m_ptCommunityPos.x + 460)

// ?????? ?????? ??????
#define CHATROOM_LIST_SCR_COUNT				12
#define CHATROOM_LIST_SCR_X					(m_ptCommunityPos.x + 486)
#define CHATROOM_LIST_SCR_Y					(m_ptCommunityPos.y + 108)
#define CHATROOM_LIST_SCR_W					13
#define CHATROOM_LIST_SCR_H					245
#define CHATROOM_LIST_SCR_WHELL_L			(m_ptCommunityPos.x + 30)
#define CHATROOM_LIST_SCR_WHELL_R			(m_ptCommunityPos.x + 505)
#define CHATROOM_LIST_SCR_WHELL_T			(m_ptCommunityPos.y + 100)
#define CHATROOM_LIST_SCR_WHELL_B			(m_ptCommunityPos.y + 355)
#define CHATROOM_LIST_SCR_BALL_L			(m_ptCommunityPos.x + 480)
#define CHATROOM_LIST_SCR_BALL_R			(m_ptCommunityPos.x + 505)
#define CHATROOM_LIST_SCR_BALL_T			(m_ptCommunityPos.y + 108)
#define CHATROOM_LIST_SCR_BALL_B			(m_ptCommunityPos.y + 355)

#define CHATROOM_BG_X						(m_ptCommunityPos.x + 21)
#define CHATROOM_BG_Y						(m_ptCommunityPos.y + 50)
#define CHATROOM_SELECT_X					(m_ptCommunityPos.x + 43)
#define CHATROOM_SELECT_Y					(m_ptCommunityPos.y + 142)
#define CHATROOM_SELECT_W					(202)
#define CHATROOM_SELECT_H					(21)

#define CHATROOM_DATA_MAXMEMBER_X			(m_ptCommunityPos.x + 130)
#define CHATROOM_DATA_MAXMEMBER_Y			(m_ptCommunityPos.y + 101)
#define CHATROOM_DATA_START_Y				(m_ptCommunityPos.y + 142)
#define CHATROOM_DATA_CHEIF_X				(m_ptCommunityPos.x + 44)
#define CHATROOM_DATA_NAME_X				(m_ptCommunityPos.x + 75)
#define CHATROOM_DATA_VOICE_X				(m_ptCommunityPos.x + 196)
#define CHATROOM_DATA_GAP_H					(21)


#define CHATROOM_CHARGE_BTN_X				(m_ptCommunityPos.x + 33)
#define CHATROOM_CHARGE_BTN_Y				(m_ptCommunityPos.y + 342)
#define CHATROOM_INVITE_BTN_X				(m_ptCommunityPos.x + 90)
#define CHATROOM_INVITE_BTN_Y				(m_ptCommunityPos.y + 342)
#define CHATROOM_OUT_BTN_X					(m_ptCommunityPos.x + 147)
#define CHATROOM_OUT_BTN_Y					(m_ptCommunityPos.y + 342)
#define CHATROOM_EXIT_BTN_X					(m_ptCommunityPos.x + 204)
#define CHATROOM_EXIT_BTN_Y					(m_ptCommunityPos.y + 342)
#define CHATROOM_VOICE_OK_BTN_X				(m_ptCommunityPos.x + 311)
#define CHATROOM_VOICE_OK_BTN_Y				(m_ptCommunityPos.y + 329)
#define CHATROOM_VOICE_CAN_BTN_X			(m_ptCommunityPos.x + 378)
#define CHATROOM_VOICE_CAN_BTN_Y			(m_ptCommunityPos.y + 329)
#define CHATROOM_COUNT_MAIN_LB_X			(m_ptCommunityPos.x + 358)
#define CHATROOM_COUNT_MAIN_LB_Y			(m_ptCommunityPos.y + 179)
#define CHATROOM_COUNT_ELEMENT_LB_X			(m_ptCommunityPos.x + 369)
#define CHATROOM_COUNT_ELEMENT_LB_Y			(m_ptCommunityPos.y + 192)
#define CHATROOM_COUNT_MAIN_LB_W			(70)
#define CHATROOM_COUNT_MAIN_LB_H			(17)
#define CHATROOM_COUNT_ELEMENT_LB_W			(70)
#define CHATROOM_COUNT_ELEMENT_LB_H			(13)
#define CHATROOM_EDIT_SUBJECT_X				(m_ptCommunityPos.x + 289)
#define CHATROOM_EDIT_SUBJECT_Y				(m_ptCommunityPos.y + 131)
#define CHATROOM_EDIT_SUBJECT_W				(190)
#define CHATROOM_EDIT_SUBJECT_H				(19)
#define CHATROOM_VOICE_SPK_VOLUM_X			(m_ptCommunityPos.x + 316)
#define CHATROOM_VOICE_SPK_VOLUM_Y			(m_ptCommunityPos.y + 296)
#define CHATROOM_VOICE_CHAT_ING_X			(m_ptCommunityPos.x + 294)
#define CHATROOM_VOICE_CHAT_ING_Y			(m_ptCommunityPos.y + 235)
#define CHATROOM_INPUT_KEY_POS_X			(m_ptCommunityPos.x + 296)
#define CHATROOM_INPUT_KEY_POS_Y			(m_ptCommunityPos.y + 257)
#define CHATROOM_INPUT_FREE_POS_X			(m_ptCommunityPos.x + 296)
#define CHATROOM_INPUT_FREE_POS_Y			(m_ptCommunityPos.y + 275)
#define CHATROOM_SECU_X						(m_ptCommunityPos.x + 362)
#define CHATROOM_SECU_Y						(m_ptCommunityPos.y + 159)
#define CHATROOM_SECU_W						(76)
#define CHATROOM_SECU_H						(16)


// ?????? ?????? 
#define CHATROOM_SCR_COUNT					9
#define CHATROOM_SCR_X						(m_ptCommunityPos.x + 247)
#define CHATROOM_SCR_Y						(m_ptCommunityPos.y + 145)
#define CHATROOM_SCR_W						13
#define CHATROOM_SCR_H						180
#define CHATROOM_SCR_WHELL_L				(m_ptCommunityPos.x + 43)
#define CHATROOM_SCR_WHELL_R				(m_ptCommunityPos.x + 260)
#define CHATROOM_SCR_WHELL_T				(m_ptCommunityPos.y + 142)
#define CHATROOM_SCR_WHELL_B				(m_ptCommunityPos.y + 330)
#define CHATROOM_SCR_BALL_L					(m_ptCommunityPos.x + 243)
#define	CHATROOM_SCR_BALL_R					(m_ptCommunityPos.x + 263)
#define CHATROOM_SCR_BALL_T					(m_ptCommunityPos.y + 140)
#define CHATROOM_SCR_BALL_B					(m_ptCommunityPos.y + 337)

// ?????? ???? ?????? ??.
#define CHATROOM_CREATE_DEFUALT_X			((g_pD3dApp->GetBackBufferDesc().Width - 238)/2)
#define CHATROOM_CREATE_DEFUALT_Y			((g_pD3dApp->GetBackBufferDesc().Height - 258)/2)
#define CHATROOM_CREATE_W					238
#define CHATROOM_CREATE_H					256
#define CHATROOM_CREATE_OK_BTN_X			(m_ptCreatePos.x + 53)
#define CHATROOM_CREATE_OK_BTN_Y			(m_ptCreatePos.y + 232)
#define CHATROOM_CREATE_CAN_BTN_X			(m_ptCreatePos.x + 120)
#define CHATROOM_CREATE_CAN_BTN_Y			(m_ptCreatePos.y + 232)
#define CHATROOM_CREATE_COUNT_MAIN_LB_X		(m_ptCreatePos.x + 100)
#define CHATROOM_CREATE_COUNT_MAIN_LB_Y		(m_ptCreatePos.y + 98)
#define CHATROOM_CREATE_COUNT_ELEMENT_LB_X	(m_ptCreatePos.x + 106)
#define CHATROOM_CREATE_COUNT_ELEMENT_LB_Y	(m_ptCreatePos.y + 111)
#define CHATROOM_CREATE_EDIT_SUBJECT_X		(m_ptCreatePos.x + 25)
#define CHATROOM_CREATE_EDIT_SUBJECT_Y		(m_ptCreatePos.y + 57)
#define CHATROOM_CREATE_EDIT_SUBJECT_W		(194)
#define CHATROOM_CREATE_EDIT_SUBJECT_H		(19)
#define CHATROOM_CREATE_VOICE_SPK_VOLUM_X	(m_ptCreatePos.x + 58)
#define CHATROOM_CREATE_VOICE_SPK_VOLUM_Y	(m_ptCreatePos.y + 203)
#define CHATROOM_CREATE_VOICE_CHAT_ING_X	(m_ptCreatePos.x + 36)
#define CHATROOM_CREATE_VOICE_CHAT_ING_Y	(m_ptCreatePos.y + 142)
#define CHATROOM_CREATE_INPUT_KEY_POS_X		(m_ptCreatePos.x + 38)
#define CHATROOM_CREATE_INPUT_KEY_POS_Y		(m_ptCreatePos.y + 165)
#define CHATROOM_CREATE_INPUT_FREE_POS_X	(m_ptCreatePos.x + 38)
#define CHATROOM_CREATE_INPUT_FREE_POS_Y	(m_ptCreatePos.y + 183)
#define CHATROOM_CREATE_SECU_X				(m_ptCreatePos.x + 101)
#define CHATROOM_CREATE_SECU_Y				(m_ptCreatePos.y + 79)
#define CHATROOM_CREATE_SECU_W				(76)
#define CHATROOM_CREATE_SECU_H				(16)


// ?????? ????.
#define CHATROOM_INFO_DEFUALT_X				((g_pD3dApp->GetBackBufferDesc().Width - 225)/2)
#define CHATROOM_INFO_DEFUALT_Y				((g_pD3dApp->GetBackBufferDesc().Height - 282)/2)
#define CHATROOM_INFO_DEFUALT_W				(225)
#define CHATROOM_INFO_DEFUALT_H				(282)
#define CHATROOM_INFO_BAR_H					(27)

#define CHATROOM_INFO_CLOSE_BTN_X			(m_ptChatRoomInfoPos.x + 80)
#define CHATROOM_INFO_CLOSE_BTN_Y			(m_ptChatRoomInfoPos.y + 257)
#define CHATROOM_INFO_DATA_START_X			(m_ptChatRoomInfoPos.x + 8)
#define CHATROOM_INFO_DATA_START_Y			(m_ptChatRoomInfoPos.y + 97)
#define CHATROOM_INFO_DATA_CHIEF_X			(m_ptChatRoomInfoPos.x + 12)
#define CHATROOM_INFO_DATA_NAME_X			(m_ptChatRoomInfoPos.x + 39)
#define CHATROOM_INFO_DATA_GAP_H			(21)
#define CHATROOM_INFO_DATA_SUBEJCT_X		(m_ptChatRoomInfoPos.x + 10)
#define CHATROOM_INFO_DATA_SUBEJCT_Y		(m_ptChatRoomInfoPos.y + 54)
#define CHATROOM_INFO_DATA_MEXMEMBER_X		(m_ptChatRoomInfoPos.x + 172)
#define CHATROOM_INFO_DATA_MEXMEMBER_Y		(m_ptChatRoomInfoPos.y + 36)

#define CHATROOM_INFO_SCR_COUNT				7
#define CHATROOM_INFO_SCR_X					(m_ptChatRoomInfoPos.x + 211)
#define CHATROOM_INFO_SCR_Y					(m_ptChatRoomInfoPos.y + 103)
#define CHATROOM_INFO_SCR_W					13
#define CHATROOM_INFO_SCR_H					140
#define CHATROOM_INFO_SCR_WHELL_L			(m_ptChatRoomInfoPos.x + 8)
#define CHATROOM_INFO_SCR_WHELL_R			(m_ptChatRoomInfoPos.x + 209)
#define CHATROOM_INFO_SCR_WHELL_T			(m_ptChatRoomInfoPos.y + 96)
#define CHATROOM_INFO_SCR_WHELL_B			(m_ptChatRoomInfoPos.y + 244)
#define CHATROOM_INFO_SCR_BALL_L			(m_ptChatRoomInfoPos.x + 209)
#define CHATROOM_INFO_SCR_BALL_R			(m_ptChatRoomInfoPos.x + 225)
#define CHATROOM_INFO_SCR_BALL_T			(m_ptChatRoomInfoPos.y + 75)
#define CHATROOM_INFO_SCR_BALL_B			(m_ptChatRoomInfoPos.y + 253)



CINFCommunityChatRoom::CINFCommunityChatRoom(CAtumNode* pParent)
{
	m_pParent = pParent;

	m_pImgRoomListBG		= NULL;
	m_pImgLock[0]			= NULL;
	m_pImgLock[1]			= NULL;
	m_pImgSel				= NULL;
	m_pScrRoomList			= NULL;
	m_pScrRoomInfo			= NULL;
	m_pBtnInfo				= NULL;
	m_pBtnCreate			= NULL;
	m_pBtnAdmission			= NULL;
	m_pBtnRoomListUpdate	= NULL;
	m_pLBChatRoom			= NULL;

	m_pBtnCharge			= NULL;
	m_pBtnInvite			= NULL;
	m_pBtnOut				= NULL;
	m_pBtnExit				= NULL;
	m_pBtnVoiceOk			= NULL;
	m_pBtnVoiceCan			= NULL;

	m_pRoomCreateBG			= NULL;
	m_pBtnCreateOk			= NULL;
	m_pBtnCreateCan			= NULL;
	m_pLBCreateRoom			= NULL;
	m_pRoomInfoBG			= NULL;
	m_pBtnRoomInfoClose		= NULL;

	m_pEBChatRoomCS			= NULL;
	m_pEBCreateCS			= NULL;
	
	m_nChatRoomTab			= CHATROOM_TAB_LIST;
	m_bShowRoomInfo			= FALSE;
	m_bShowCreate			= FALSE;
	m_nVoiceInput			= 0;
	m_nPersonNum[0] = 2;
	m_nPersonNum[1] = 4;
	m_nPersonNum[2] = 8;
	m_nPersonNum[3] = 12;
	m_nPersonNum[4] = 16;
	m_nPersonNum[5] = 20;
	m_nPersonNum[6] = 40;

	m_ptChatRoomInfoPos.x	= CHATROOM_INFO_DEFUALT_X;
	m_ptChatRoomInfoPos.y	= CHATROOM_INFO_DEFUALT_Y;
	m_ptCreatePos.x			= CHATROOM_CREATE_DEFUALT_X;
	m_ptCreatePos.y			= CHATROOM_CREATE_DEFUALT_Y;

	m_vecRoomList.clear();


}

CINFCommunityChatRoom::~CINFCommunityChatRoom()
{

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void InitSetting();
/// \brief		???????? ???? ???????? ????????.
/// \author		dgwoo
/// \date		2008-06-19 ~ 2008-06-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCommunityChatRoom::InitSetting()
{
	SetButtonActive();
}
HRESULT CINFCommunityChatRoom::InitDeviceObjects()
{
	m_ptCommunityPos =  ((CINFCommunity*)m_pParent)->GetCommunityBkPos();
	DataHeader	* pDataHeader= NULL;

	m_pImgBG = new CINFImage;
	pDataHeader = FindResource("commubk3");
	m_pImgBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgRoomListBG = new CINFImage;
	pDataHeader = FindResource("RlistBG");
	m_pImgRoomListBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgLock[0] = new CINFImage;
	pDataHeader = FindResource("lock0");
	m_pImgLock[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgLock[1] = new CINFImage;
	pDataHeader = FindResource("lock1");
	m_pImgLock[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgSel = new CINFImage;
	pDataHeader = FindResource("c_ps");
	m_pImgSel->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgSpkVolBar = new CINFImage;
	pDataHeader = FindResource("scrl_b");
	m_pImgSpkVolBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);


	if(NULL == m_pBtnInfo)
	{
		m_pBtnInfo = new CINFImageBtn;
	}
	m_pBtnInfo->InitDeviceObjects("roominfo");
	if(NULL == m_pBtnCreate)
	{
		m_pBtnCreate = new CINFImageBtn;
	}
	m_pBtnCreate->InitDeviceObjects("createb");
	if(NULL == m_pBtnAdmission)
	{
		m_pBtnAdmission = new CINFImageBtn;
	}
	m_pBtnAdmission->InitDeviceObjects("rooment");
	if(NULL == m_pBtnRoomListUpdate)
	{
		m_pBtnRoomListUpdate = new CINFImageBtn;
	}
	m_pBtnRoomListUpdate->InitDeviceObjects("RlistUpd");
	if(NULL == m_pScrRoomList)
	{
		m_pScrRoomList = new CINFArenaScrollBar;
	}
	m_pScrRoomList->InitDeviceObjects(CHATROOM_LIST_SCR_COUNT,"c_scrlb");
	if(NULL == m_pScrRoomInfo)
	{
		m_pScrRoomInfo = new CINFArenaScrollBar;
	}
	m_pScrRoomInfo->InitDeviceObjects(CHATROOM_INFO_SCR_COUNT,"c_scrlb");
	//--------------------------------------------------------------------------//
	m_pImgRoomBg = new CINFImage;
	pDataHeader = FindResource("RMinfoBG");
	m_pImgRoomBg->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgChatRoomSel = new CINFImage;
	pDataHeader = FindResource("sel_CU");
	m_pImgChatRoomSel->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	if(NULL == m_pScrRoom)
	{
		m_pScrRoom = new CINFArenaScrollBar;
	}
	m_pScrRoom->InitDeviceObjects(CHATROOM_SCR_COUNT,"c_scrlb");

	m_pImgRoomChief = new CINFImage;
	pDataHeader = FindResource("roomchief");
	m_pImgRoomChief->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	if(NULL == m_pBtnCharge)
	{
		m_pBtnCharge = new CINFImageBtn;
	}
	m_pBtnCharge->InitDeviceObjects("c_sbt3");
	if(NULL == m_pBtnInvite)
	{
		m_pBtnInvite = new CINFImageBtn;
	}
	m_pBtnInvite->InitDeviceObjects("p_bt0");
	if(NULL == m_pBtnOut)
	{
		m_pBtnOut = new CINFImageBtn;
	}
	m_pBtnOut->InitDeviceObjects("p_bt2");
	if(NULL == m_pBtnExit)
	{
		m_pBtnExit = new CINFImageBtn;
	}
	m_pBtnExit->InitDeviceObjects("Rexit");
	

	if(NULL == m_pBtnVoiceOk)
	{
		m_pBtnVoiceOk = new CINFImageBtn;
	}
	m_pBtnVoiceOk->InitDeviceObjects("lr_ok");
	if(NULL == m_pBtnVoiceCan)
	{
		m_pBtnVoiceCan = new CINFImageBtn;
	}
	m_pBtnVoiceCan->InitDeviceObjects("lr_can");

	// ?????? ???? ??????.
	m_pRoomCreateBG = new CINFImage;
	pDataHeader = FindResource("Rcreate");
	m_pRoomCreateBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	if(NULL == m_pBtnCreateOk)
	{
		m_pBtnCreateOk = new CINFImageBtn;
	}
	m_pBtnCreateOk->InitDeviceObjects("createb");
	if(NULL == m_pBtnCreateCan)
	{
		m_pBtnCreateCan = new CINFImageBtn;
	}
	m_pBtnCreateCan->InitDeviceObjects("lr_can");
	if(m_pLBCreateRoom == NULL)
	{
		m_pLBCreateRoom = new CINFListBox("cbopa","s_combo");
		m_pLBCreateRoom->InitDeviceObjects();
	}

	// ?????? ??????.
	m_pRoomInfoBG = new CINFImage;
	pDataHeader = FindResource("RinfoBG");
	m_pRoomInfoBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	if(NULL == m_pBtnRoomInfoClose)
	{
		m_pBtnRoomInfoClose = new CINFImageBtn;
	}
	m_pBtnRoomInfoClose->InitDeviceObjects("shnpc06");
	if(m_pLBChatRoom == NULL)
	{
		m_pLBChatRoom = new CINFListBox("cbopa","s_combo");
		m_pLBChatRoom->InitDeviceObjects();
	}
	int i;
	char szTemp[16],szTemp1[16];

	for(i = 0; i < CHATROOM_ADMISSION_NUMBER_COUNT; i++)
	{
		memset(szTemp,0x00,16);
		sprintf(szTemp,"%d",m_nPersonNum[i]);
		m_pLBChatRoom->AddElement(szTemp);
		m_pLBCreateRoom->AddElement(szTemp);
	}
	m_pLBChatRoom->SetSelectItem(0);
	m_pLBCreateRoom->SetSelectItem(0);

	if(NULL == m_pEBChatRoomCS)
	{
		m_pEBChatRoomCS = new CINFEditBox;
	}
	POINT ptPos = {CHATROOM_CREATE_EDIT_SUBJECT_X, CHATROOM_CREATE_EDIT_SUBJECT_Y};
	m_pEBChatRoomCS->InitDeviceObjects(9, ptPos, CHATROOM_CREATE_EDIT_SUBJECT_W, TRUE, CHATROOM_CREATE_EDIT_SUBJECT_H);				
	m_pEBChatRoomCS->SetStringMaxBuff(CHATROOM_SUBJECT_MAX_SIZE);		
	if(NULL == m_pEBCreateCS)
	{
		m_pEBCreateCS = new CINFEditBox;
	}
	ptPos.x = CHATROOM_EDIT_SUBJECT_X;
	ptPos.y = CHATROOM_EDIT_SUBJECT_Y;
	m_pEBCreateCS->InitDeviceObjects(9, ptPos, CHATROOM_EDIT_SUBJECT_W, TRUE, CHATROOM_EDIT_SUBJECT_H);				
	m_pEBCreateCS->SetStringMaxBuff(CHATROOM_SUBJECT_MAX_SIZE);	
	
	// ???????? ???? ?? ????????.
	m_pCBVoiceChat = new CINFImageRadioBtn;
	strcpy(szTemp,"radio_17b");
	strcpy(szTemp1,"radio_17a");
	m_pCBVoiceChat->InitDeviceObjects(szTemp,szTemp1);
	m_pImgRadioBtn[0] = new CINFImage;
	pDataHeader = FindResource("radio_b");
	m_pImgRadioBtn[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pImgRadioBtn[1] = new CINFImage;
	pDataHeader = FindResource("radio_a");
	m_pImgRadioBtn[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	m_pFontRoomNum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pFontRoomNum->InitDeviceObjects(g_pD3dDev);

	if(NULL == m_pSEChatRoomSecu)
	{
		m_pSEChatRoomSecu = new CINFSecuEditBox;
	}
	ptPos.x = CHATROOM_SECU_X;
	ptPos.y = CHATROOM_SECU_Y;
	m_pSEChatRoomSecu->InitDeviceObjects(9, ptPos, CHATROOM_SECU_W, TRUE, CHATROOM_SECU_H);		
	m_pSEChatRoomSecu->SetMaxStringLen(SIZE_MAX_TEAM_PW-1);

	if(NULL == m_pSECreateSecu)
	{
		m_pSECreateSecu = new CINFSecuEditBox;
	}
	ptPos.x = CHATROOM_CREATE_SECU_X;
	ptPos.y = CHATROOM_CREATE_SECU_Y;
	m_pSECreateSecu->InitDeviceObjects(9, ptPos, CHATROOM_CREATE_SECU_W, TRUE, CHATROOM_CREATE_SECU_H);		
	m_pSECreateSecu->SetMaxStringLen(SIZE_MAX_TEAM_PW-1);
	return S_OK;
}
HRESULT CINFCommunityChatRoom::RestoreDeviceObjects()
{
	m_pImgBG->RestoreDeviceObjects();
	m_pImgRoomListBG->RestoreDeviceObjects();
	m_pImgLock[0]->RestoreDeviceObjects();
	m_pImgLock[1]->RestoreDeviceObjects();
	m_pImgSel->RestoreDeviceObjects();
	m_pBtnInfo->RestoreDeviceObjects();
	m_pBtnCreate->RestoreDeviceObjects();
	m_pBtnAdmission->RestoreDeviceObjects();
	m_pBtnRoomListUpdate->RestoreDeviceObjects();
	m_pScrRoomList->RestoreDeviceObjects();
	m_pScrRoomInfo->RestoreDeviceObjects();
	m_pImgSpkVolBar->RestoreDeviceObjects();

	m_pImgRoomBg->RestoreDeviceObjects();
	m_pImgChatRoomSel->RestoreDeviceObjects();
	m_pImgRoomChief->RestoreDeviceObjects();
	m_pScrRoom->RestoreDeviceObjects();
	m_pBtnCharge->RestoreDeviceObjects();
	m_pBtnInvite->RestoreDeviceObjects();
	m_pBtnOut->RestoreDeviceObjects();
	m_pBtnExit->RestoreDeviceObjects();
	m_pBtnVoiceOk->RestoreDeviceObjects();
	m_pBtnVoiceCan->RestoreDeviceObjects();

	m_pRoomCreateBG->RestoreDeviceObjects();
	m_pBtnCreateOk->RestoreDeviceObjects();
	m_pBtnCreateCan->RestoreDeviceObjects();

	m_pRoomInfoBG->RestoreDeviceObjects();
	m_pBtnRoomInfoClose->RestoreDeviceObjects();

	m_pLBChatRoom->RestoreDeviceObjects();
	m_pLBCreateRoom->RestoreDeviceObjects();

	m_pEBChatRoomCS->RestoreDeviceObjects();
	m_pEBCreateCS->RestoreDeviceObjects();

	m_pCBVoiceChat->RestoreDeviceObjects();
	m_pImgRadioBtn[0]->RestoreDeviceObjects();
	m_pImgRadioBtn[1]->RestoreDeviceObjects();

	m_pFontRoomNum->RestoreDeviceObjects();

	m_pSEChatRoomSecu->RestoreDeviceObjects();
	m_pSECreateSecu->RestoreDeviceObjects();
	return S_OK;
}
HRESULT CINFCommunityChatRoom::InvalidateDeviceObjects()
{
	m_pImgBG->InvalidateDeviceObjects();
	m_pImgRoomListBG->InvalidateDeviceObjects();
	m_pImgLock[0]->InvalidateDeviceObjects();
	m_pImgLock[1]->InvalidateDeviceObjects();
	m_pImgSel->InvalidateDeviceObjects();
	m_pScrRoomList->InvalidateDeviceObjects();
	m_pScrRoomInfo->InvalidateDeviceObjects();
	m_pBtnInfo->InvalidateDeviceObjects();
	m_pBtnCreate->InvalidateDeviceObjects();
	m_pBtnAdmission->InvalidateDeviceObjects();
	m_pBtnRoomListUpdate->InvalidateDeviceObjects();
	m_pImgSpkVolBar->InvalidateDeviceObjects();
	
	m_pImgRoomBg->InvalidateDeviceObjects();
	m_pImgChatRoomSel->InvalidateDeviceObjects();
	m_pImgRoomChief->InvalidateDeviceObjects();
	m_pScrRoom->InvalidateDeviceObjects();
	m_pBtnCharge->InvalidateDeviceObjects();
	m_pBtnInvite->InvalidateDeviceObjects();
	m_pBtnOut->InvalidateDeviceObjects();
	m_pBtnExit->InvalidateDeviceObjects();
	m_pBtnVoiceOk->InvalidateDeviceObjects();
	m_pBtnVoiceCan->InvalidateDeviceObjects();

	m_pRoomCreateBG->InvalidateDeviceObjects();
	m_pBtnCreateOk->InvalidateDeviceObjects();
	m_pBtnCreateCan->InvalidateDeviceObjects();

	m_pRoomInfoBG->InvalidateDeviceObjects();
	m_pBtnRoomInfoClose->InvalidateDeviceObjects();
	
	m_pLBChatRoom->InvalidateDeviceObjects();
	m_pLBCreateRoom->InvalidateDeviceObjects();

	m_pEBChatRoomCS->InvalidateDeviceObjects();
	m_pEBCreateCS->InvalidateDeviceObjects();

	m_pCBVoiceChat->InvalidateDeviceObjects();
	m_pImgRadioBtn[0]->InvalidateDeviceObjects();
	m_pImgRadioBtn[1]->InvalidateDeviceObjects();
	m_pFontRoomNum->InvalidateDeviceObjects();

	m_pSEChatRoomSecu->RestoreDeviceObjects();
	m_pSECreateSecu->RestoreDeviceObjects();
	return S_OK;
}
HRESULT CINFCommunityChatRoom::DeleteDeviceObjects()
{
	m_pImgBG->DeleteDeviceObjects();
	m_pImgRoomListBG->DeleteDeviceObjects();
	m_pImgLock[0]->DeleteDeviceObjects();
	m_pImgLock[1]->DeleteDeviceObjects();
	m_pImgSel->DeleteDeviceObjects();
	m_pBtnInfo->DeleteDeviceObjects();
	m_pBtnCreate->DeleteDeviceObjects();
	m_pBtnAdmission->DeleteDeviceObjects();
	m_pBtnRoomListUpdate->DeleteDeviceObjects();
	m_pImgSpkVolBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgBG);
	SAFE_DELETE(m_pImgRoomListBG);
	SAFE_DELETE(m_pImgLock[0]);
	SAFE_DELETE(m_pImgLock[1]);
	SAFE_DELETE(m_pImgSel);
	SAFE_DELETE(m_pBtnInfo);
	SAFE_DELETE(m_pBtnCreate);
	SAFE_DELETE(m_pBtnAdmission);
	SAFE_DELETE(m_pBtnRoomListUpdate);
	SAFE_DELETE(m_pImgSpkVolBar);
	m_pScrRoomList->DeleteDeviceObjects();
	m_pScrRoomInfo->DeleteDeviceObjects();
	SAFE_DELETE(m_pScrRoomList);
	SAFE_DELETE(m_pScrRoomInfo);

	m_pImgRoomBg->DeleteDeviceObjects();
	m_pImgChatRoomSel->DeleteDeviceObjects();
	m_pImgRoomChief->DeleteDeviceObjects();
	m_pScrRoom->DeleteDeviceObjects();
	m_pBtnCharge->DeleteDeviceObjects();
	m_pBtnInvite->DeleteDeviceObjects();
	m_pBtnOut->DeleteDeviceObjects();
	m_pBtnExit->DeleteDeviceObjects();
	m_pBtnVoiceOk->DeleteDeviceObjects();
	m_pBtnVoiceCan->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgRoomBg);
	SAFE_DELETE(m_pImgChatRoomSel);
	SAFE_DELETE(m_pImgRoomChief);
	SAFE_DELETE(m_pScrRoom);
	SAFE_DELETE(m_pBtnCharge);
	SAFE_DELETE(m_pBtnInvite);
	SAFE_DELETE(m_pBtnOut);
	SAFE_DELETE(m_pBtnExit);
	SAFE_DELETE(m_pBtnVoiceOk);
	SAFE_DELETE(m_pBtnVoiceCan);

	m_pRoomCreateBG->DeleteDeviceObjects();
	m_pBtnCreateOk->DeleteDeviceObjects();
	m_pBtnCreateCan->DeleteDeviceObjects();
	SAFE_DELETE(m_pRoomCreateBG);
	SAFE_DELETE(m_pBtnCreateOk);
	SAFE_DELETE(m_pBtnCreateCan);

	m_pRoomInfoBG->DeleteDeviceObjects();
	m_pBtnRoomInfoClose->DeleteDeviceObjects();
	SAFE_DELETE(m_pRoomInfoBG);
	SAFE_DELETE(m_pBtnRoomInfoClose);

	m_pLBChatRoom->DeleteDeviceObjects();
	m_pLBCreateRoom->DeleteDeviceObjects();
	SAFE_DELETE(m_pLBCreateRoom);
	SAFE_DELETE(m_pLBChatRoom);

	m_pEBChatRoomCS->DeleteDeviceObjects();
	m_pEBCreateCS->DeleteDeviceObjects();
	SAFE_DELETE(m_pEBChatRoomCS);
	SAFE_DELETE(m_pEBCreateCS);

	m_pCBVoiceChat->DeleteDeviceObjects();
	m_pImgRadioBtn[0]->DeleteDeviceObjects();
	m_pImgRadioBtn[1]->DeleteDeviceObjects();
	SAFE_DELETE(m_pCBVoiceChat);
	SAFE_DELETE(m_pImgRadioBtn[0]);
	SAFE_DELETE(m_pImgRadioBtn[1]);

	m_pFontRoomNum->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontRoomNum);

	m_pSEChatRoomSecu->RestoreDeviceObjects();
	m_pSECreateSecu->RestoreDeviceObjects();
	SAFE_DELETE(m_pSECreateSecu);
	SAFE_DELETE(m_pSEChatRoomSecu);


	return S_OK;
}

void CINFCommunityChatRoom::Tick()
{
	if(m_fTimeBtnGap < CHATROOM_BTN_TIME_GAP)
	{
		m_fTimeBtnGap += g_pD3dApp->GetCheckElapsedTime();
	}
	else
	{
		m_fTimeBtnGap = CHATROOM_BTN_TIME_GAP;
	}
	if(m_pEBChatRoomCS)
		m_pEBChatRoomCS->Tick();
	if(m_pEBCreateCS)
		m_pEBCreateCS->Tick();
}

void CINFCommunityChatRoom::Render(POINT i_ptParent)
{
	m_pImgBG->Move(i_ptParent.x,i_ptParent.y);
	m_pImgBG->Render();
	switch(m_nChatRoomTab)
	{
		case CHATROOM_TAB_LIST:
			RenderList();
			break;
		case CHATROOM_TAB_ROOM:
			RenderChatRoom();
			break;
	}
	RenderCreateRoom();
	RenderRoomInfo();
}
void CINFCommunityChatRoom::RenderList()
{
	m_pImgRoomListBG->Move(CHATROOM_LIST_BG_X,CHATROOM_LIST_BG_Y);
	m_pImgRoomListBG->Render();

	m_pBtnInfo->SetBtnPosition(CHATROOM_LIST_INFO_BTN_X,CHATROOM_LIST_INFO_BTN_Y);
	m_pBtnInfo->Render();
	m_pBtnCreate->SetBtnPosition(CHATROOM_LIST_CRE_BTN_X,CHATROOM_LIST_CRE_BTN_Y);
	m_pBtnCreate->Render();
	m_pBtnAdmission->SetBtnPosition(CHATROOM_LIST_ADMIS_BTN_X,CHATROOM_LIST_ADMIS_BTN_Y);
	m_pBtnAdmission->Render();
	m_pBtnRoomListUpdate->SetBtnPosition(CHATROOM_LIST_UPDATE_BTN_X,CHATROOM_LIST_UPDATE_BTN_Y);
	m_pBtnRoomListUpdate->Render();

	RECT rtWhell;
	rtWhell.bottom		= CHATROOM_LIST_SCR_WHELL_B;
	rtWhell.left		= CHATROOM_LIST_SCR_WHELL_L;
	rtWhell.right		= CHATROOM_LIST_SCR_WHELL_R;
	rtWhell.top			= CHATROOM_LIST_SCR_WHELL_T;
	m_pScrRoomList->SetPosition(CHATROOM_LIST_SCR_X,CHATROOM_LIST_SCR_Y,CHATROOM_LIST_SCR_W,CHATROOM_LIST_SCR_H);
	m_pScrRoomList->SetMouseWhellRect(rtWhell);
	rtWhell.bottom		= CHATROOM_LIST_SCR_BALL_B;
	rtWhell.left		= CHATROOM_LIST_SCR_BALL_L;
	rtWhell.right		= CHATROOM_LIST_SCR_BALL_R;
	rtWhell.top			= CHATROOM_LIST_SCR_BALL_T;
	m_pScrRoomList->SetMouseBallRect(rtWhell);

	// ?????? ???? 
	char buf[128];
	SIZE size;
	vector<SCHATROOM_LIST_INFO>::iterator it =m_vecRoomList.begin();
	it += m_pScrRoomList->GetScrollStep();
	for(int i = 0 ; i < CHATROOM_LIST_SCR_COUNT ; i++)
	{
		if(it == m_vecRoomList.end())
		{// ???????? ???????? ????.
			break;
		}
		// ??????.
		wsprintf(buf,"%d",it->ChatRoomNum);
		size = m_pFontRoomNum->GetStringSize(buf);
		m_pFontRoomNum->DrawText(CHATROOM_LIST_DATA_NUMBER_FONT_X - (INT)(size.cx/2),
			CHATROOM_LIST_DATA_START_Y+3 + (CHATROOM_LIST_DATA_GAP_H * i),
			GUI_FONT_COLOR_W,
			buf);
		if(!it->ChatRoomLock)
		{
			m_pImgLock[0]->Move(CHATROOM_LIST_DATA_LOCK_FONT_X,CHATROOM_LIST_DATA_START_Y+3 + (CHATROOM_LIST_DATA_GAP_H * i));
			m_pImgLock[0]->Render();
		}
		else
		{
			m_pImgLock[1]->Move(CHATROOM_LIST_DATA_LOCK_FONT_X,CHATROOM_LIST_DATA_START_Y+3 + (CHATROOM_LIST_DATA_GAP_H * i));
			m_pImgLock[1]->Render();
		}
		// ??????.
		wsprintf(buf,"%s",it->ChatRoomName);
		size = m_pFontRoomNum->GetStringSize(buf);
		m_pFontRoomNum->DrawText(CHATROOM_LIST_DATA_SUBJECT_FONT_X - (INT)(size.cx/2),
			CHATROOM_LIST_DATA_START_Y+3 + (CHATROOM_LIST_DATA_GAP_H * i),
			GUI_FONT_COLOR_W,
			buf);
		// ????.
		wsprintf(buf,"%s",it->ChatRoomMasterName);
		size = m_pFontRoomNum->GetStringSize(buf);
		m_pFontRoomNum->DrawText(CHATROOM_LIST_DATA_RM_FONT_X - (INT)(size.cx/2),
			CHATROOM_LIST_DATA_START_Y+3 + (CHATROOM_LIST_DATA_GAP_H * i),
			GUI_FONT_COLOR_W,
			buf);
		// ????.
		
		// ????.
		wsprintf(buf,"%d/%d",it->Membercount,it->MaxMembercount);
		size = m_pFontRoomNum->GetStringSize(buf);
		m_pFontRoomNum->DrawText(CHATROOM_LIST_DATA_MAXMEMBER_FONT_X - (INT)(size.cx/2),
			CHATROOM_LIST_DATA_START_Y+3 + (CHATROOM_LIST_DATA_GAP_H * i),
			GUI_FONT_COLOR_W,
			buf);
		it++;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	if(m_nSelect >= 0)
	{
		m_pImgSel->Move(CHATROOM_LIST_DATA_START_X,CHATROOM_LIST_DATA_START_Y+(CHATROOM_LIST_DATA_GAP_H * m_nSelect));
		m_pImgSel->Render();
	}
	

	m_pScrRoomList->Render();
	
}
void CINFCommunityChatRoom::RenderChatRoom()
{
	m_pImgRoomBg->Move(CHATROOM_LIST_BG_X,CHATROOM_LIST_BG_Y);
	m_pImgRoomBg->Render();

	m_pBtnCharge->SetBtnPosition(CHATROOM_CHARGE_BTN_X,CHATROOM_CHARGE_BTN_Y);
	m_pBtnCharge->Render();
	m_pBtnInvite->SetBtnPosition(CHATROOM_INVITE_BTN_X,CHATROOM_INVITE_BTN_Y);
	m_pBtnInvite->Render();
	m_pBtnOut->SetBtnPosition(CHATROOM_OUT_BTN_X,CHATROOM_OUT_BTN_Y);
	m_pBtnOut->Render();
	m_pBtnExit->SetBtnPosition(CHATROOM_EXIT_BTN_X,CHATROOM_EXIT_BTN_Y);
	m_pBtnExit->Render();
	m_pBtnVoiceOk->SetBtnPosition(CHATROOM_VOICE_OK_BTN_X,CHATROOM_VOICE_OK_BTN_Y);
	m_pBtnVoiceOk->Render();
	m_pBtnVoiceCan->SetBtnPosition(CHATROOM_VOICE_CAN_BTN_X,CHATROOM_VOICE_CAN_BTN_Y);
	m_pBtnVoiceCan->Render();
	m_pSEChatRoomSecu->SetPos(CHATROOM_SECU_X,CHATROOM_SECU_Y);
	m_pSEChatRoomSecu->Tick();
	m_pSEChatRoomSecu->Render();
	if(m_pEBChatRoomCS)
	{
		m_pEBChatRoomCS->SetPos(CHATROOM_EDIT_SUBJECT_X,CHATROOM_EDIT_SUBJECT_Y);
		m_pEBChatRoomCS->Render();
	}
	if(m_nSelect >= 0)
	{
		m_pImgChatRoomSel->Move(CHATROOM_SELECT_X,CHATROOM_SELECT_Y+(CHATROOM_DATA_GAP_H * m_nSelect));
		m_pImgChatRoomSel->Render();
	}


	m_pImgSpkVolBar->Move(CHATROOM_VOICE_SPK_VOLUM_X + m_nPosVolum,CHATROOM_VOICE_SPK_VOLUM_Y);
	m_pImgSpkVolBar->Render();


	RECT rtWhell;
	rtWhell.bottom		= CHATROOM_SCR_WHELL_B;
	rtWhell.left		= CHATROOM_SCR_WHELL_L;
	rtWhell.right		= CHATROOM_SCR_WHELL_R;
	rtWhell.top			= CHATROOM_SCR_WHELL_T;
	m_pScrRoom->SetPosition(CHATROOM_SCR_X,CHATROOM_SCR_Y,CHATROOM_SCR_W,CHATROOM_SCR_H);
	m_pScrRoom->SetMouseWhellRect(rtWhell);
	rtWhell.bottom		= CHATROOM_SCR_BALL_B;
	rtWhell.left		= CHATROOM_SCR_BALL_L;
	rtWhell.right		= CHATROOM_SCR_BALL_R;
	rtWhell.top			= CHATROOM_SCR_BALL_T;
	m_pScrRoom->SetMouseBallRect(rtWhell);
	m_pScrRoom->Render();
	
	char buf[128];
	wsprintf(buf,"%d/%d",m_stMyRoomInfo.ChatRoomInfoListCount,m_stMyRoomInfo.ChatRoomMaxCount);
	m_pFontRoomNum->DrawText(CHATROOM_DATA_MAXMEMBER_X ,
		CHATROOM_DATA_MAXMEMBER_Y,
		GUI_FONT_COLOR_W,
		buf);
	

	vector<SCHATROOM_MEMBER_INFO>::iterator it =m_vecMyMember.begin();
	it += m_pScrRoom->GetScrollStep();
	for(int i = 0 ; i < CHATROOM_SCR_COUNT ; i++)
	{
		if(it == m_vecMyMember.end())
		{// ???????? ???????? ????.
			break;
		}
		if(m_stMyRoomInfo.MasterCharacterUID == it->CharacterUID)
		{// ???? ??????.
			m_pImgRoomChief->Move(CHATROOM_DATA_CHEIF_X,CHATROOM_DATA_START_Y + (CHATROOM_DATA_GAP_H * i));
			m_pImgRoomChief->Render();
		}

		// ?????? ??.
		wsprintf(buf,"%s",it->CharacterName);
		m_pFontRoomNum->DrawText(CHATROOM_DATA_NAME_X ,
			CHATROOM_DATA_START_Y + 2 + (CHATROOM_DATA_GAP_H * i),
			GUI_FONT_COLOR_W,
			buf);
		// ????.

		it++;
	}


	m_pCBVoiceChat->SetPosition(CHATROOM_VOICE_CHAT_ING_X,CHATROOM_VOICE_CHAT_ING_Y,60);
	m_pCBVoiceChat->Render();
	if(m_nVoiceInput)
	{
		m_pImgRadioBtn[1]->Move(CHATROOM_INPUT_FREE_POS_X,CHATROOM_INPUT_FREE_POS_Y);
		m_pImgRadioBtn[1]->Render();
		m_pImgRadioBtn[0]->Move(CHATROOM_INPUT_KEY_POS_X,CHATROOM_INPUT_KEY_POS_Y);
		m_pImgRadioBtn[0]->Render();
	}
	else
	{
		m_pImgRadioBtn[0]->Move(CHATROOM_INPUT_FREE_POS_X,CHATROOM_INPUT_FREE_POS_Y);
		m_pImgRadioBtn[0]->Render();
		m_pImgRadioBtn[1]->Move(CHATROOM_INPUT_KEY_POS_X,CHATROOM_INPUT_KEY_POS_Y);
		m_pImgRadioBtn[1]->Render();
	}


	m_pLBChatRoom->SetMainArea(CHATROOM_COUNT_MAIN_LB_X,CHATROOM_COUNT_MAIN_LB_Y,CHATROOM_COUNT_MAIN_LB_W,CHATROOM_COUNT_MAIN_LB_H);
	m_pLBChatRoom->SetElementArea(CHATROOM_COUNT_ELEMENT_LB_X,CHATROOM_COUNT_ELEMENT_LB_Y,CHATROOM_COUNT_ELEMENT_LB_W,CHATROOM_COUNT_ELEMENT_LB_H);
	m_pLBChatRoom->Render();

}
void CINFCommunityChatRoom::RenderCreateRoom()
{
	if(!m_bShowCreate)
		return;

	m_pRoomCreateBG->Move(m_ptCreatePos.x,m_ptCreatePos.y);
	m_pRoomCreateBG->Render();

	m_pBtnCreateOk->SetBtnPosition(CHATROOM_CREATE_OK_BTN_X,CHATROOM_CREATE_OK_BTN_Y);
	m_pBtnCreateOk->Render();
	m_pBtnCreateCan->SetBtnPosition(CHATROOM_CREATE_CAN_BTN_X,CHATROOM_CREATE_CAN_BTN_Y);
	m_pBtnCreateCan->Render();

	if(m_pEBCreateCS)
	{
		m_pEBCreateCS->SetPos(CHATROOM_CREATE_EDIT_SUBJECT_X,CHATROOM_CREATE_EDIT_SUBJECT_Y);
		m_pEBCreateCS->Render();
	}
	m_pSECreateSecu->SetPos(CHATROOM_CREATE_SECU_X,CHATROOM_CREATE_SECU_Y);
	m_pSECreateSecu->Tick();
	m_pSECreateSecu->Render();

	m_pImgSpkVolBar->Move(CHATROOM_CREATE_VOICE_SPK_VOLUM_X + m_nPosVolum,CHATROOM_CREATE_VOICE_SPK_VOLUM_Y);
	m_pImgSpkVolBar->Render();


	m_pCBVoiceChat->SetPosition(CHATROOM_CREATE_VOICE_CHAT_ING_X,CHATROOM_CREATE_VOICE_CHAT_ING_Y,60);
	m_pCBVoiceChat->Render();
	if(m_nVoiceInput)
	{
		m_pImgRadioBtn[1]->Move(CHATROOM_CREATE_INPUT_FREE_POS_X,CHATROOM_CREATE_INPUT_FREE_POS_Y);
		m_pImgRadioBtn[1]->Render();
		m_pImgRadioBtn[0]->Move(CHATROOM_CREATE_INPUT_KEY_POS_X,CHATROOM_CREATE_INPUT_KEY_POS_Y);
		m_pImgRadioBtn[0]->Render();
	}
	else
	{
		m_pImgRadioBtn[0]->Move(CHATROOM_CREATE_INPUT_FREE_POS_X,CHATROOM_CREATE_INPUT_FREE_POS_Y);
		m_pImgRadioBtn[0]->Render();
		m_pImgRadioBtn[1]->Move(CHATROOM_CREATE_INPUT_KEY_POS_X,CHATROOM_CREATE_INPUT_KEY_POS_Y);
		m_pImgRadioBtn[1]->Render();
	}


	m_pLBCreateRoom->SetMainArea(CHATROOM_CREATE_COUNT_MAIN_LB_X,CHATROOM_CREATE_COUNT_MAIN_LB_Y,CHATROOM_COUNT_MAIN_LB_W,CHATROOM_COUNT_MAIN_LB_H);
	m_pLBCreateRoom->SetElementArea(CHATROOM_CREATE_COUNT_ELEMENT_LB_X,CHATROOM_CREATE_COUNT_ELEMENT_LB_Y,CHATROOM_COUNT_ELEMENT_LB_W,CHATROOM_COUNT_ELEMENT_LB_H);
	m_pLBCreateRoom->Render();

}
void CINFCommunityChatRoom::RenderRoomInfo()
{
	if(!m_bShowRoomInfo)
		return;
	m_pRoomInfoBG->Move(m_ptChatRoomInfoPos.x , m_ptChatRoomInfoPos.y);
	m_pRoomInfoBG->Render();
	m_pBtnRoomInfoClose->SetBtnPosition(CHATROOM_INFO_CLOSE_BTN_X,CHATROOM_INFO_CLOSE_BTN_Y);
	m_pBtnRoomInfoClose->Render();
	RECT rtWhell;
	rtWhell.bottom		= CHATROOM_INFO_SCR_WHELL_B;
	rtWhell.left		= CHATROOM_INFO_SCR_WHELL_L;
	rtWhell.right		= CHATROOM_INFO_SCR_WHELL_R;
	rtWhell.top			= CHATROOM_INFO_SCR_WHELL_T;
	m_pScrRoomInfo->SetPosition(CHATROOM_INFO_SCR_X,CHATROOM_INFO_SCR_Y,CHATROOM_INFO_SCR_W,CHATROOM_INFO_SCR_H);
	m_pScrRoomInfo->SetMouseWhellRect(rtWhell);
	rtWhell.bottom		= CHATROOM_INFO_SCR_BALL_B;
	rtWhell.left		= CHATROOM_INFO_SCR_BALL_L;
	rtWhell.right		= CHATROOM_INFO_SCR_BALL_R;
	rtWhell.top			= CHATROOM_INFO_SCR_BALL_T;
	m_pScrRoomInfo->SetMouseBallRect(rtWhell);
	m_pScrRoomInfo->Render();


	char buf[128];
	wsprintf(buf,"%d/%d",m_stOtherRoomInfo.ChatRoomInfoListCount,m_stOtherRoomInfo.ChatRoomMaxCount);
	m_pFontRoomNum->DrawText(CHATROOM_INFO_DATA_MEXMEMBER_X ,
		CHATROOM_INFO_DATA_MEXMEMBER_Y,
		GUI_FONT_COLOR_W,
		buf);
	
	wsprintf(buf,"%s",m_stOtherRoomInfo.ChatRoomName);
	m_pFontRoomNum->DrawText(CHATROOM_INFO_DATA_SUBEJCT_X ,
		CHATROOM_INFO_DATA_SUBEJCT_Y,
		GUI_FONT_COLOR_W,
		buf);

	vector<SCHATROOM_MEMBER_INFO>::iterator it =m_vecOtherMember.begin();
	it += m_pScrRoomInfo->GetScrollStep();
	for(int i = 0 ; i < CHATROOM_INFO_SCR_COUNT ; i++)
	{
		if(it == m_vecOtherMember.end())
		{// ???????? ???????? ????.
			break;
		}
		if(m_stOtherRoomInfo.MasterCharacterUID == it->CharacterUID)
		{// ???? ??????.
			m_pImgRoomChief->Move(CHATROOM_INFO_DATA_CHIEF_X,CHATROOM_INFO_DATA_START_Y + (CHATROOM_INFO_DATA_GAP_H * i));
			m_pImgRoomChief->Render();
		}

		// ?????? ??.
		wsprintf(buf,"%s",it->CharacterName);
		//size = m_pFontRoomNum->GetStringSize(buf);
		m_pFontRoomNum->DrawText(CHATROOM_INFO_DATA_NAME_X ,
			CHATROOM_INFO_DATA_START_Y + (CHATROOM_INFO_DATA_GAP_H * i),
			GUI_FONT_COLOR_W,
			buf);
		// ????.
		it++;
	}
}

int CINFCommunityChatRoom::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_bShowCreate)
	{
		if(INF_MSGPROC_BREAK == WndProcChatRoomCreate(uMsg,wParam,lParam))
		{
			return INF_MSGPROC_BREAK;
		}
	}
	if(m_bShowRoomInfo)
	{
		if(INF_MSGPROC_BREAK == WndProcChatRoomInfo(uMsg,wParam,lParam))
		{
			return INF_MSGPROC_BREAK;
		}
	}
	if(m_nChatRoomTab == CHATROOM_TAB_ROOM)
	{
		if(INF_MSGPROC_BREAK == WndProcChatRoom(uMsg,wParam,lParam))
			return INF_MSGPROC_BREAK;
	}
	if(m_nChatRoomTab == CHATROOM_TAB_LIST)
	{
		if(INF_MSGPROC_BREAK == WndProcList(uMsg,wParam,lParam))
			return INF_MSGPROC_BREAK;
	}
	
	return INF_MSGPROC_NORMAL;
}
int CINFCommunityChatRoom::WndProcList(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);		
			BOOL bClick = FALSE;	
			bClick = m_pScrRoomList->IsMouseWhellPos(pt);
			if(bClick)		
			{
				int nScrollStep = m_pScrRoomList->OnMouseWheel(wParam, lParam);

				int nListSize = m_vecRoomList.size();
				if(nListSize < m_nListTotalRoomCount)
				{
					if(nListSize <= nScrollStep + CHATROOM_LIST_SCR_COUNT)
					{ 
						SendRoomListRequest(m_vecRoomList[nListSize-1].ChatRoomNum);
					}
				}
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);		
			if(pt.x > m_ptCommunityPos.x &&
				pt.x < m_ptCommunityPos.x + CHATROOM_MAIN_W &&
				pt.y > m_ptCommunityPos.y &&
				pt.y < m_ptCommunityPos.y + CHATROOM_MAIN_H)
			{
				int nCnt = 0;
				if(m_pScrRoomList->GetMouseMoveMode())
				{
					if(FALSE == m_pScrRoomList->IsMouseScrollPos(pt))
					{// ?????? ???? ?????? ????????.
						m_pScrRoomList->SetMouseMoveMode(FALSE);
						return INF_MSGPROC_NORMAL;			
					}
					m_pScrRoomList->SetScrollPos(pt);
					int nScrollStep = m_pScrRoomList->GetScrollStep();
					
					int nListSize = m_vecRoomList.size();
					if(nListSize < m_nListTotalRoomCount)
					{
						if(nListSize <= nScrollStep + CHATROOM_LIST_SCR_COUNT)
						{
							SendRoomListRequest(m_vecRoomList[nListSize-1].ChatRoomNum);
						}
					}
					return INF_MSGPROC_BREAK;			
				}


				m_pBtnAdmission->OnMouseMove(pt);
				m_pBtnCreate->OnMouseMove(pt);
				m_pBtnInfo->OnMouseMove(pt);
				m_pBtnRoomListUpdate->OnMouseMove(pt);

				return INF_MSGPROC_BREAK;
			}


		}
		break;
	case WM_LBUTTONDOWN:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			if(pt.x > m_ptCommunityPos.x &&
				pt.x < m_ptCommunityPos.x + CHATROOM_MAIN_W &&
				pt.y > m_ptCommunityPos.y &&
				pt.y < m_ptCommunityPos.y + CHATROOM_MAIN_H)
			{
				if(pt.x > CHATROOM_TAB_ROOM_X &&
					pt.x < CHATROOM_TAB_ROOM_X + CHATROOM_TAB_W &&
					pt.y > CHATROOM_TAB_ROOM_Y &&
					pt.y < CHATROOM_TAB_ROOM_Y + CHATROOM_TAB_H)
				{
					ChangeTab(CHATROOM_TAB_ROOM);
				}

				m_pBtnAdmission->OnLButtonDown(pt);
				m_pBtnCreate->OnLButtonDown(pt);
				m_pBtnInfo->OnLButtonDown(pt);
				m_pBtnRoomListUpdate->OnLButtonDown(pt);
				if(pt.x > CHATROOM_LIST_DATA_START_X &&
					pt.x < CHATROOM_LIST_DATA_START_X + CHATROOM_LIST_DATA_START_W &&
					pt.y > CHATROOM_LIST_DATA_START_Y &&
					pt.y < CHATROOM_LIST_DATA_START_Y + CHATROOM_LIST_DATA_START_H)
				{
					m_nSelect = (INT)((pt.y - CHATROOM_LIST_DATA_START_Y)/CHATROOM_LIST_DATA_GAP_H);
				}

				return INF_MSGPROC_BREAK;
			}


		}
		break;
	case WM_LBUTTONUP:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			if(pt.x > m_ptCommunityPos.x &&
				pt.x < m_ptCommunityPos.x + CHATROOM_MAIN_W &&
				pt.y > m_ptCommunityPos.y &&
				pt.y < m_ptCommunityPos.y + CHATROOM_MAIN_H)
			{
				if(m_pBtnAdmission->OnLButtonUp(pt))
				{
					SendEnterRoom();
				}
				if(m_pBtnCreate->OnLButtonUp(pt))
				{
					m_bShowCreate = TRUE;
					char buf[CHATROOM_SUBJECT_MAX_SIZE];
					memset(buf,0x00,CHATROOM_SUBJECT_MAX_SIZE);
					switch(rand()%3)
					{
					case 0:
						wsprintf(buf,STRMSG_C_080625_0101,g_pShuttleChild->GetMyShuttleInfo().CharacterName);
						break;
					case 1:
						strcpy(buf,STRMSG_C_080625_0102);
						break;
					case 2:
						strcpy(buf,STRMSG_C_080625_0103);
						break;
					}
					m_pEBCreateCS->SetString(buf,CHATROOM_SUBJECT_MAX_SIZE);
				}
				if(m_pBtnInfo->OnLButtonUp(pt))
				{
					m_bShowRoomInfo = TRUE;
					SendChatRoomInfo();
				}
				if(m_pBtnRoomListUpdate->OnLButtonUp(pt))
				{
					m_vecRoomList.clear();
					ChangeTab(CHATROOM_TAB_LIST);
				}

				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
int CINFCommunityChatRoom::WndProcChatRoom(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			BOOL bClick = m_pScrRoom->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pScrRoom->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			m_pBtnCharge->OnMouseMove(pt);
			m_pBtnInvite->OnMouseMove(pt);
			m_pBtnOut->OnMouseMove(pt);
			m_pBtnExit->OnMouseMove(pt);
			m_pBtnVoiceCan->OnMouseMove(pt);
			m_pBtnVoiceOk->OnMouseMove(pt);
			m_pLBChatRoom->MouseMove(pt);
			if(m_bVolumCon)
			{// ???? ???? ????????.
				m_nPosVolum += (pt.x - m_ptOldVolumPos.x);
				if(m_nPosVolum > VOICECHAT_SPK_W)
				{
					m_nPosVolum = VOICECHAT_SPK_W;
				}else if(m_nPosVolum < 0)
				{
					m_nPosVolum = 0;
				}
				DWORD nVolum;
				nVolum = (DWORD)(m_nPosVolum/VOICECHAT_SPK_W)*100;
				m_ptOldVolumPos = pt;
				g_pGameMain->m_pChat->SetVoiceChatVolum(nVolum);
			}

			if(pt.x > m_ptCommunityPos.x &&
				pt.x < m_ptCommunityPos.x + CHATROOM_MAIN_W &&
				pt.y > m_ptCommunityPos.y &&
				pt.y < m_ptCommunityPos.y + CHATROOM_MAIN_H)
			{
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	case WM_LBUTTONDOWN:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			AllEditBoxEnable();
			if(pt.x > m_ptCommunityPos.x &&
				pt.x < m_ptCommunityPos.x + CHATROOM_MAIN_W &&
				pt.y > m_ptCommunityPos.y &&
				pt.y < m_ptCommunityPos.y + CHATROOM_MAIN_H)
			{
				m_pBtnCharge->OnLButtonDown(pt);
				m_pBtnInvite->OnLButtonDown(pt);
				m_pBtnOut->OnLButtonDown(pt);
				m_pBtnExit->OnLButtonDown(pt);
				m_pBtnVoiceCan->OnLButtonDown(pt);
				m_pBtnVoiceOk->OnLButtonDown(pt);
				
				// 2009-01-12 by bhsohn ???? ???? ????????
//				m_pLBChatRoom->LButtonDown(pt);
// 				if(TRUE == m_pSEChatRoomSecu->OnLButtonDown(pt))					
// 				{	
// 					AllEditBoxEnable();
// 					m_pSEChatRoomSecu->EnableEdit(TRUE);				
// 					return  INF_MSGPROC_BREAK;
// 				}
// 				if(m_pEBChatRoomCS->OnLButtonDown(pt))
// 				{
// 					AllEditBoxEnable();
// 					m_pEBChatRoomCS->EnableEdit(TRUE,TRUE);				
// 				}
				if(m_stMyRoomInfo.MasterCharacterUID == g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber)
				{
					m_pLBChatRoom->LButtonDown(pt);

					if(TRUE == m_pSEChatRoomSecu->OnLButtonDown(pt))				
					{	
						AllEditBoxEnable();
						m_pSEChatRoomSecu->EnableEdit(TRUE);				
						return  INF_MSGPROC_BREAK;
					}
					
					if(m_pEBChatRoomCS->OnLButtonDown(pt))
					{
						AllEditBoxEnable();
						m_pEBChatRoomCS->EnableEdit(TRUE,TRUE);				
					}
				}
				
				if(m_pCBVoiceChat->OnLButtonDown(pt))
				{
// 2008-07-08 by dgwoo ???????? ???????? ??????.
//					BOOL bRadio = m_pCBVoiceChat->GetRadioBtn();
//					m_pCBVoiceChat->SetRadioBtn(!bRadio);
				}
				// 2008-10-20 by bhsohn VOIP ???? ????
				// ???????? ????
//				if(pt.x > CHATROOM_VOICE_SPK_VOLUM_X + m_nPosVolum &&
//					pt.x < CHATROOM_VOICE_SPK_VOLUM_X + m_nPosVolum + m_pImgSpkVolBar->GetImgSize().x &&
//					pt.y > CHATROOM_VOICE_SPK_VOLUM_Y &&
//					pt.y < CHATROOM_VOICE_SPK_VOLUM_Y + m_pImgSpkVolBar->GetImgSize().y)
//				{
//					m_bVolumCon = TRUE;
//					m_ptOldVolumPos = pt;
//				}
				if(pt.x > CHATROOM_SELECT_X &&
					pt.x < CHATROOM_SELECT_X + CHATROOM_SELECT_W &&
					pt.y > CHATROOM_SELECT_Y &&
					pt.y < CHATROOM_SELECT_Y + CHATROOM_SCR_H)
				{
					m_nSelect = (INT)((pt.y - CHATROOM_DATA_START_Y)/CHATROOM_DATA_GAP_H);
				}

				if(pt.x > CHATROOM_TAB_LIST_X &&
					pt.x < CHATROOM_TAB_LIST_X + CHATROOM_TAB_W &&
					pt.y > CHATROOM_TAB_LIST_Y &&
					pt.y < CHATROOM_TAB_LIST_Y + CHATROOM_TAB_H)
				{
					ChangeTab(CHATROOM_TAB_LIST);
				}
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	case WM_LBUTTONUP:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			if(m_pBtnCharge->OnLButtonUp(pt))
			{
				if((m_vecMyMember.size()-m_pScrRoom->GetScrollStep()) <= m_nSelect ||
					m_nSelect < 0)
				{// ???????? ????.
					g_pGameMain->CreateChatChild(STRMSG_C_080625_0106,COLOR_ITEM);
					break;
				}
				if(m_stMyRoomInfo.MasterCharacterUID != g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber)
				{// ?????? ??????.
					break;
				}
				MSG_IC_CHATROOM_CHANGE_MASTER sMsg;
				sMsg.ChatRoomNum = m_stMyRoomInfo.ChatRoomNum;
				vector<SCHATROOM_MEMBER_INFO>::iterator it =m_vecMyMember.begin();
				it += (m_pScrRoom->GetScrollStep()+m_nSelect);
				sMsg.NewCharacterUID = it->CharacterUID;
				g_pIMSocket->SendMsg(T_IC_CHATROOM_CHANGE_MASTER, (char*)&sMsg, sizeof(sMsg));
			}
			if(m_pBtnInvite->OnLButtonUp(pt))
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_PARTY_0024, _Q_CHATROOM_INVITE,m_stMyRoomInfo.ChatRoomNum);
			}
			if(m_pBtnOut->OnLButtonUp(pt))
			{
				if((m_vecMyMember.size()-m_pScrRoom->GetScrollStep()) <= m_nSelect ||
					m_nSelect < 0)
				{// ???????? ????.
					g_pGameMain->CreateChatChild(STRMSG_C_080625_0106,COLOR_ITEM);
					break;
				}

				MSG_IC_CHATROOM_BAN sMsg;
				sMsg.ChatRoomNum = m_stMyRoomInfo.ChatRoomNum;
				vector<SCHATROOM_MEMBER_INFO>::iterator it =m_vecMyMember.begin();
				it += (m_pScrRoom->GetScrollStep()+m_nSelect);
				sMsg.BanCharacterUID = it->CharacterUID;
				memcpy(sMsg.BanCharacterName,it->CharacterName,SIZE_MAX_CHARACTER_NAME);
				g_pIMSocket->SendMsg(T_IC_CHATROOM_BAN, (char*)&sMsg, sizeof(sMsg));
			}
			if(m_pBtnExit->OnLButtonUp(pt))
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_080625_0105, _Q_CHATROOM_OUT);
			}
			if(m_pBtnVoiceCan->OnLButtonUp(pt))
			{
			}
			if(m_pBtnVoiceOk->OnLButtonUp(pt))
			{
				ModifyChatRoom();
			}
			if(m_bVolumCon)
			{// ???? ???? ????????.				
				if(m_nPosVolum > VOICECHAT_SPK_W)
				{
					m_nPosVolum = VOICECHAT_SPK_W;
				}else if(m_nPosVolum < 0)
				{
					m_nPosVolum = 0;
				}
				DWORD nVolum;
				nVolum = (DWORD)(m_nPosVolum/VOICECHAT_SPK_W)*100;				
				// 2008-10-20 by bhsohn VOIP ???? ????
				// ???????? ????
				//g_pGameMain->SetVoiceVolum(nVolum);			
				m_bVolumCon = FALSE;
			}


			if(pt.x > m_ptCommunityPos.x &&
				pt.x < m_ptCommunityPos.x + CHATROOM_MAIN_W &&
				pt.y > m_ptCommunityPos.y &&
				pt.y < m_ptCommunityPos.y + CHATROOM_MAIN_H)
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(INF_MSGPROC_BREAK == m_pSEChatRoomSecu->WndProc(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
	case WM_IME_STARTCOMPOSITION:
//	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_SETCONTEXT:	
	case WM_CHAR:
		{		
			if(m_pEBChatRoomCS->WndProc(uMsg, wParam, lParam, NULL, TRUE))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;	

	}
	return INF_MSGPROC_NORMAL;
}
int	CINFCommunityChatRoom::WndProcChatRoomCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);	
			m_pBtnCreateOk->OnMouseMove(pt);
			m_pBtnCreateCan->OnMouseMove(pt);
			m_pLBCreateRoom->MouseMove(pt);
			if(m_bVolumCon)
			{// ???? ???? ????????.
				m_nPosVolum += (pt.x - m_ptOldVolumPos.x);
				if(m_nPosVolum > VOICECHAT_SPK_W)
				{
					m_nPosVolum = VOICECHAT_SPK_W;
				}else if(m_nPosVolum < 0)
				{
					m_nPosVolum = 0;
				}
				DWORD nVolum;
				nVolum = (DWORD)(m_nPosVolum/VOICECHAT_SPK_W)*100;
				m_ptOldVolumPos = pt;
				g_pGameMain->m_pChat->SetVoiceChatVolum(nVolum);

			}



		}
		break;
	case WM_LBUTTONDOWN:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			AllEditBoxEnable();
			if(pt.x > m_ptCreatePos.x &&
				pt.x < m_ptCreatePos.x + CHATROOM_CREATE_W &&
				pt.y > m_ptCreatePos.y &&
				pt.y < m_ptCreatePos.y + CHATROOM_CREATE_H)
			{
				m_pBtnCreateOk->OnLButtonDown(pt);
				m_pBtnCreateCan->OnLButtonDown(pt);
				m_pLBCreateRoom->LButtonDown(pt);
				if(m_pEBCreateCS->OnLButtonDown(pt))
				{
					AllEditBoxEnable();
					m_pEBCreateCS->EnableEdit(TRUE,FALSE);
				}

				if(TRUE == m_pSECreateSecu->OnLButtonDown(pt))
				{	
					AllEditBoxEnable();
					m_pSECreateSecu->EnableEdit(TRUE);				
					return  INF_MSGPROC_BREAK;
				}


				if(m_pCBVoiceChat->OnLButtonDown(pt))
				{
					BOOL bRadio = m_pCBVoiceChat->GetRadioBtn();
					m_pCBVoiceChat->SetRadioBtn(!bRadio);
				}
				// 2008-10-20 by bhsohn VOIP ???? ????
				// ???????? ????
//				if(pt.x > CHATROOM_CREATE_VOICE_SPK_VOLUM_X + m_nPosVolum &&
//					pt.x < CHATROOM_CREATE_VOICE_SPK_VOLUM_X + m_nPosVolum + m_pImgSpkVolBar->GetImgSize().x &&
//					pt.y > CHATROOM_CREATE_VOICE_SPK_VOLUM_Y &&
//					pt.y < CHATROOM_CREATE_VOICE_SPK_VOLUM_Y + m_pImgSpkVolBar->GetImgSize().y)
//				{
//					m_bVolumCon = TRUE;
//					m_ptOldVolumPos = pt;
//				}
				return INF_MSGPROC_BREAK;
			}



		}
		break;
	case WM_LBUTTONUP:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			
			if(pt.x > m_ptCreatePos.x &&
				pt.x < m_ptCreatePos.x + CHATROOM_CREATE_W &&
				pt.y > m_ptCreatePos.y &&
				pt.y < m_ptCreatePos.y + CHATROOM_CREATE_H)
			{

				if(m_pBtnCreateOk->OnLButtonUp(pt))
				{
					MSG_IC_CHATROOM_CREATE sMsg;
					memset(&sMsg,0x00,sizeof(sMsg));
					m_pSECreateSecu->GetString(sMsg.ChatRoomPW,SIZE_MAX_TEAM_PW);
					if(strlen(sMsg.ChatRoomPW))
					{
						sMsg.ChatRoomLock = TRUE;
					}
					else
					{
						sMsg.ChatRoomLock = FALSE;
					}
					sMsg.ChatRoomMaxCount = GetListBoxSelect(m_pLBCreateRoom->GetSelect());
					
					m_pEBCreateCS->GetString(sMsg.ChatRoomName, SIZE_MAX_CHATROOM_NAME);
					g_pIMSocket->SendMsg(T_IC_CHATROOM_CREATE, (char*)&sMsg, sizeof(sMsg));

					memset(&m_stMyRoomInfo,0x00,sizeof(CHATROOM_INFO));
					m_stMyRoomInfo.ChatRoomLock = sMsg.ChatRoomLock;
					m_stMyRoomInfo.ChatRoomMaxCount = GetListBoxSelect(m_pLBCreateRoom->GetSelect());
					m_pSECreateSecu->GetString(m_stMyRoomInfo.ChatRoomPW,SIZE_MAX_TEAM_PW);
					m_stMyRoomInfo.MasterCharacterUID = g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber;
					

					m_pEBCreateCS->GetString(m_stMyRoomInfo.ChatRoomName, SIZE_MAX_CHATROOM_NAME);
					
					
					m_bShowCreate = FALSE;
				}
				if(m_pBtnCreateCan->OnLButtonUp(pt))
				{
					m_bShowCreate = FALSE;
				}
				if(m_pLBCreateRoom->LButtonUp(pt))
				{

				}
				if(m_bVolumCon)
				{// ???? ???? ????????.
					if(m_nPosVolum > VOICECHAT_SPK_W)
					{
						m_nPosVolum = VOICECHAT_SPK_W;
					}else if(m_nPosVolum < 0)
					{
						m_nPosVolum = 0;
					}
					DWORD nVolum;
					nVolum = (DWORD)(m_nPosVolum/VOICECHAT_SPK_W)*100;
					// 2008-10-20 by bhsohn VOIP ???? ????
					// ???????? ????
					//g_pGameMain->SetVoiceVolum(nVolum);				
					m_bVolumCon = FALSE;
				}
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(INF_MSGPROC_BREAK == m_pSECreateSecu->WndProc(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
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
		{		
			if(m_pEBCreateCS->WndProc(uMsg, wParam, lParam, NULL, TRUE))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;	
	
	}
	return INF_MSGPROC_NORMAL;
}
int	CINFCommunityChatRoom::WndProcChatRoomInfo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch(uMsg)
	{
		
	case WM_MOUSEMOVE:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);		
			m_pBtnRoomInfoClose->OnMouseMove(pt);
			if(m_bInfoMoving)
			{
				m_ptChatRoomInfoPos.x += (pt.x - m_ptOldPos.x);
				m_ptChatRoomInfoPos.y += (pt.y - m_ptOldPos.y);
				if(m_ptChatRoomInfoPos.x < 0)
				{
					m_ptChatRoomInfoPos.x = 0;
				}else if(m_ptChatRoomInfoPos.x + CHATROOM_INFO_DEFUALT_W > g_pD3dApp->GetBackBufferDesc().Width)
				{
					m_ptChatRoomInfoPos.x = g_pD3dApp->GetBackBufferDesc().Width - CHATROOM_INFO_DEFUALT_W;
				}
				if(m_ptChatRoomInfoPos.y < 0)
				{
					m_ptChatRoomInfoPos.y = 0;
				}else if(m_ptChatRoomInfoPos.y + CHATROOM_INFO_DEFUALT_H > g_pD3dApp->GetBackBufferDesc().Height)
				{
					m_ptChatRoomInfoPos.y = g_pD3dApp->GetBackBufferDesc().Height - CHATROOM_INFO_DEFUALT_H;
				}
				m_ptOldPos = pt;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			if(pt.x > m_ptChatRoomInfoPos.x &&
				pt.x < m_ptChatRoomInfoPos.x + CHATROOM_INFO_DEFUALT_W &&
				pt.y > m_ptChatRoomInfoPos.y &&
				pt.y < m_ptChatRoomInfoPos.y + CHATROOM_INFO_DEFUALT_H)
			{
				m_pBtnRoomInfoClose->OnLButtonDown(pt);

				if(pt.x > m_ptChatRoomInfoPos.x &&
					pt.x < m_ptChatRoomInfoPos.x + CHATROOM_INFO_DEFUALT_W &&
					pt.y > m_ptChatRoomInfoPos.y &&
					pt.y < m_ptChatRoomInfoPos.y + CHATROOM_INFO_BAR_H)
				{
					m_bInfoMoving = TRUE;
					m_ptOldPos = pt;
				}
				return INF_MSGPROC_BREAK;

			}

			
		}
		break;
	case WM_LBUTTONUP:
		{
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
			m_bInfoMoving = FALSE;
			if(pt.x > m_ptChatRoomInfoPos.x &&
				pt.x < m_ptChatRoomInfoPos.x + CHATROOM_INFO_DEFUALT_W &&
				pt.y > m_ptChatRoomInfoPos.y &&
				pt.y < m_ptChatRoomInfoPos.y + CHATROOM_INFO_DEFUALT_H)
			{
				if(m_pBtnRoomInfoClose->OnLButtonUp(pt))
				{
					m_bShowRoomInfo = FALSE;
					return INF_MSGPROC_BREAK;
				}
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}	
INT CINFCommunityChatRoom::GetListBoxSelect(INT i_nIndex)
{
	INT nCount = 0;
	if(i_nIndex < 0 || i_nIndex > CHATROOM_ADMISSION_NUMBER_COUNT)
		return nCount;
	nCount = m_nPersonNum[i_nIndex];
	return nCount;
}
INT CINFCommunityChatRoom::GetListBoxSelectItem(INT i_nCount)
{
	INT nIndex = 0;
	for(nIndex = 0; nIndex < CHATROOM_ADMISSION_NUMBER_COUNT; nIndex++)
	{
		if(i_nCount == m_nPersonNum[nIndex])
		{
			return nIndex;
		}
	}
	return -1;

}
void CINFCommunityChatRoom::ChangeTab(DWORD i_nTab)
{
	m_nSelect = -1;
	switch(i_nTab)
	{
	case CHATROOM_TAB_ROOM:
		{
			m_nChatRoomTab = CHATROOM_TAB_ROOM;
		}
		break;
	case CHATROOM_TAB_LIST:
		{
			m_nChatRoomTab = CHATROOM_TAB_LIST;
			
			if(m_vecRoomList.size() == 0)
			{
				SendRoomListRequest(1);
			}
			
		}
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCommunityChatRoom::SendChatRoomInfo()
/// \brief		?????? ???????? ?????? ????.
/// \author		dgwoo
/// \date		2008-06-25 ~ 2008-06-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCommunityChatRoom::SendChatRoomInfo()
{
	if(m_nSelect < 0)
		return FALSE;
	memset(&m_stOtherRoomInfo,0x00,sizeof(m_stOtherRoomInfo));
	m_vecOtherMember.clear();
	vector<SCHATROOM_LIST_INFO>::iterator it =m_vecRoomList.begin();
	int nCnt = 0;
	int nPos = (m_pScrRoomList->GetScrollStep()+m_nSelect);
	if( nPos >= (int)m_vecRoomList.size())
	{
		return FALSE;
	}
	//it += nPos;
	MSG_IC_CHATROOM_MEMBER_INFO sMsg;
	sMsg.ChatRoomNum = m_vecRoomList[nPos].ChatRoomNum;
	g_pIMSocket->SendMsg(T_IC_CHATROOM_OTHER_MEMBER_INFO, (char*)&sMsg, sizeof(sMsg));
	return TRUE;
}
BOOL CINFCommunityChatRoom::SendEnterRoom()
{
	if(m_nSelect < 0)
		return FALSE;

	vector<SCHATROOM_LIST_INFO>::iterator it =m_vecRoomList.begin();

	int nCnt = 0;
	int nPos = (m_pScrRoomList->GetScrollStep()+m_nSelect);
	if( nPos >= (int)m_vecRoomList.size())
	{
		return FALSE;
	}
	//it += nPos;
	if(m_vecRoomList[nPos].ChatRoomLock)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_070430_0100,_Q_CHATROOM_PASSWORD,m_vecRoomList[nPos].ChatRoomNum);
	}
	else
	{ 
		MSG_IC_CHATROOM_JOIN sMsg;
		
		// 2009-04-13 by bhsohn ???? ?? ???? ????
		memset(&sMsg, 0x00, sizeof(MSG_IC_CHATROOM_JOIN));
		// end 2009-04-13 by bhsohn ???? ?? ???? ????

		sMsg.ChatRoomNum = m_vecRoomList[nPos].ChatRoomNum;
		sMsg.ChatRoomLock = FALSE;
		
		g_pIMSocket->SendMsg(T_IC_CHATROOM_JOIN, (char*)&sMsg, sizeof(sMsg));

	}
	

	return TRUE;
}
SCHATROOM_LIST_INFO* CINFCommunityChatRoom::FindChatRoomList(INT i_nRoomNum)
{
	vector<SCHATROOM_LIST_INFO>::iterator it = m_vecRoomList.begin();
	while(it != m_vecRoomList.end())
	{
		if(it->ChatRoomNum == i_nRoomNum)
		{
			return &*it;
		}
	}
	return NULL;
}
void CINFCommunityChatRoom::AddRoomList(MSG_IC_CHATROOM_LIST_INFO_OK * pMsg)
{
	m_pScrRoomList->SetMaxItem(pMsg->ChatRoomInfoTotalCount);
	m_nListTotalRoomCount = pMsg->ChatRoomInfoTotalCount;
	
	SCHATROOM_LIST_INFO* pRoom= (SCHATROOM_LIST_INFO*)((char *)pMsg + sizeof(MSG_IC_CHATROOM_LIST_INFO_OK));
	SCHATROOM_LIST_INFO stRoom;
	
	int i;
	for(i = 0 ; i < pMsg->ChatRoomInfoListCount; i++)
	{
		memset(&stRoom,0x00,sizeof(stRoom));
		strncpy(stRoom.ChatRoomName, pRoom->ChatRoomName,SIZE_MAX_CHATROOM_NAME);
		strncpy(stRoom.ChatRoomMasterName, pRoom->ChatRoomMasterName,SIZE_MAX_CHARACTER_NAME);
		stRoom.ChatRoomLock			= pRoom->ChatRoomLock;
		stRoom.ChatRoomNum			= pRoom->ChatRoomNum;
		stRoom.MaxMembercount		= pRoom->MaxMembercount;
		stRoom.Membercount			= pRoom->Membercount;
		m_vecRoomList.push_back(stRoom);
		pRoom++;
	}
	

}
void CINFCommunityChatRoom::InitMyRoomInfo()
{
	m_vecMyMember.clear();
	memset(&m_stMyRoomInfo,0x00,sizeof(CHATROOM_INFO));
	
}
void CINFCommunityChatRoom::AddMyRoomInvite(MSG_IC_CHATROOM_ACCEPT_INVITE_OK * pMsg)
{
	SCHATROOM_MEMBER_INFO sMemberInfo;
	memcpy(sMemberInfo.CharacterName,pMsg->CharacterName,SIZE_MAX_CHARACTER_NAME);
	sMemberInfo.CharacterUID = pMsg->CharacterUID;
	m_vecMyMember.push_back(sMemberInfo);
	m_stMyRoomInfo.ChatRoomInfoListCount++;
}
void CINFCommunityChatRoom::SendRoomListRequest(INT i_nRoomNum)
{
	if(m_fTimeBtnGap < CHATROOM_BTN_TIME_GAP)
	{
		return;
	}
	MSG_IC_CHATROOM_LIST_INFO sMsg;
	if(m_vecRoomList.size() > 0)
	{
		sMsg.StartNum = i_nRoomNum;
	}
	else
	{
		sMsg.StartNum = 0;
	}
	g_pIMSocket->SendMsg(T_IC_CHATROOM_LIST_INFO, (char*)&sMsg, sizeof(sMsg));
}
void CINFCommunityChatRoom::ModifyChatRoom()
{
	if(m_stMyRoomInfo.ChatRoomNum == 0)
	{
		return;
	}
	char szbuf[SIZE_MAX_CHATROOM_NAME];
	memset(szbuf,0x00,SIZE_MAX_CHATROOM_NAME);
	m_pEBChatRoomCS->GetString(szbuf,SIZE_MAX_CHATROOM_NAME);
	if(strcmp(szbuf,m_stMyRoomInfo.ChatRoomName))
	{// ?????? ?????? ????.
		MSG_IC_CHATROOM_CHANGE_NAME sMsg;
		memcpy(sMsg.ChatRoomName,szbuf,SIZE_MAX_CHATROOM_NAME);
		sMsg.ChatRoomNum			= m_stMyRoomInfo.ChatRoomNum;
		g_pIMSocket->SendMsg(T_IC_CHATROOM_CHANGE_NAME, (char*)&sMsg, sizeof(sMsg));
	}
	if(m_stMyRoomInfo.ChatRoomMaxCount != GetListBoxSelect(m_pLBChatRoom->GetSelect()))
	{// ???? ???? ????.
		MSG_IC_CHATROOM_CHANGE_MAX_MEMBER sMsg;
		sMsg.ChatRoomNum			= m_stMyRoomInfo.ChatRoomNum;
		sMsg.ChatRoomMaxMember		= GetListBoxSelect(m_pLBChatRoom->GetSelect());
		g_pIMSocket->SendMsg(T_IC_CHATROOM_CHANGE_MAX_MEMBER, (char*)&sMsg, sizeof(sMsg));
	}
	m_pSEChatRoomSecu->GetString(szbuf,SIZE_MAX_TEAM_PW);
	if(strcmp(szbuf, m_stMyRoomInfo.ChatRoomPW))
	{// ?????? ???? ????.
		MSG_IC_CHATROOM_CHANGE_LOCK_PW sMsg;
		sMsg.ChatRoomNum			= m_stMyRoomInfo.ChatRoomNum;
		if(strlen(szbuf) == 0)
		{
			sMsg.ChatRoomLock = FALSE;
			memset(sMsg.ChatRoomPW,0x00,SIZE_MAX_TEAM_PW);
		}
		else
		{
			m_pSEChatRoomSecu->GetString(sMsg.ChatRoomPW,SIZE_MAX_TEAM_PW);
			sMsg.ChatRoomLock = TRUE;
		}
		g_pIMSocket->SendMsg(T_IC_CHATROOM_CHANGE_LOCK_PW, (char*)&sMsg, sizeof(sMsg));
	}
}
void CINFCommunityChatRoom::AllEditBoxEnable()
{
	if(m_pEBChatRoomCS->IsEditMode())
	{
		m_pEBChatRoomCS->BackupTxtString();
	}
	if(m_pEBCreateCS->IsEditMode())
	{
		m_pEBCreateCS->BackupTxtString();
	}
	m_pEBChatRoomCS->EnableEdit(FALSE,FALSE);
	m_pEBCreateCS->EnableEdit(FALSE,FALSE);
	m_pSEChatRoomSecu->EnableEdit(FALSE);
	m_pSECreateSecu->EnableEdit(FALSE);
}
void CINFCommunityChatRoom::AddMyRoomInfo(MSG_IC_CHATROOM_MEMBER_INFO_OK * pMsg)
{
	m_pScrRoom->SetMaxItem(pMsg->ChatRoomMaxCount);
	m_nMyInfoTotCnt = pMsg->ChatRoomMaxCount;

	
	SCHATROOM_MEMBER_INFO* pRoom= (SCHATROOM_MEMBER_INFO*)((char *)pMsg + sizeof(MSG_IC_CHATROOM_MEMBER_INFO_OK));
	SCHATROOM_MEMBER_INFO stRoom;
	
	memset(&m_stMyRoomInfo,0x00,sizeof(CHATROOM_INFO));
	m_vecMyMember.clear();
	memcpy(m_stOtherRoomInfo.ChatRoomName, pMsg->ChatRoomName,SIZE_MAX_CHATROOM_NAME);
	m_stMyRoomInfo.MasterCharacterUID	= pMsg->MasterCharacterUID;
	m_stMyRoomInfo.ChatRoomLock			= pMsg->ChatRoomLock;
	m_stMyRoomInfo.ChatRoomNum			= pMsg->ChatRoomNum;
	m_stMyRoomInfo.ChatRoomMaxCount		= pMsg->ChatRoomMaxCount;
	m_stMyRoomInfo.ChatRoomInfoListCount	= pMsg->ChatRoomInfoListCount;
	int i;
	for(i = 0 ; i < pMsg->ChatRoomInfoListCount; i++)
	{
		memset(&stRoom,0x00,sizeof(SCHATROOM_MEMBER_INFO));
		memcpy(stRoom.CharacterName,pRoom->CharacterName,SIZE_MAX_CHARACTER_NAME);
		stRoom.CharacterUID				= pRoom->CharacterUID;
		m_vecMyMember.push_back(stRoom);
		pRoom++;
	}
	m_pEBChatRoomCS->SetString(m_stOtherRoomInfo.ChatRoomName,SIZE_MAX_CHATROOM_NAME);
	m_pSEChatRoomSecu->SetString(pMsg->ChatRoomPW,SIZE_MAX_TEAM_PW);
	m_pLBChatRoom->SetSelectItem(GetListBoxSelectItem(pMsg->ChatRoomMaxCount));
	SetButtonActive();
	ChangeTab(CHATROOM_TAB_ROOM);
}
void CINFCommunityChatRoom::AddOtherRoomInfo(MSG_IC_CHATROOM_MEMBER_INFO_OK * pMsg)
{
	m_pScrRoomInfo->SetMaxItem(pMsg->ChatRoomMaxCount);
	m_nOtherInfoTotCnt = pMsg->ChatRoomMaxCount;
	
	SCHATROOM_MEMBER_INFO* pRoom= (SCHATROOM_MEMBER_INFO*)((char *)pMsg + sizeof(MSG_IC_CHATROOM_MEMBER_INFO_OK));
	SCHATROOM_MEMBER_INFO stRoom;
	
	memset(&m_stOtherRoomInfo,0x00,sizeof(stRoom));
	m_vecOtherMember.clear();
	memcpy(m_stOtherRoomInfo.ChatRoomName, pMsg->ChatRoomName,SIZE_MAX_CHATROOM_NAME);
	m_stOtherRoomInfo.MasterCharacterUID	= pMsg->MasterCharacterUID;
	m_stOtherRoomInfo.ChatRoomLock			= pMsg->ChatRoomLock;
	m_stOtherRoomInfo.ChatRoomNum			= pMsg->ChatRoomNum;
	m_stOtherRoomInfo.ChatRoomMaxCount		= pMsg->ChatRoomMaxCount;
	m_stOtherRoomInfo.ChatRoomInfoListCount	= pMsg->ChatRoomInfoListCount;
	int i;
	for(i = 0 ; i < pMsg->ChatRoomInfoListCount; i++)
	{
		memcpy(stRoom.CharacterName,pRoom->CharacterName,SIZE_MAX_CHARACTER_NAME);
		stRoom.CharacterUID				= pRoom->CharacterUID;
		m_vecOtherMember.push_back(stRoom);
		pRoom++;
	}	

}
void CINFCommunityChatRoom::SetButtonActive()
{
	// 2009-01-12 by bhsohn ???? ???? ????????
	BOOL bEnabelOkBtn = TRUE;

	if(m_stMyRoomInfo.ChatRoomNum == 0)
	{// ???????? ?????? ???? ???? ????.
		m_pBtnCharge->EnableBtn(FALSE);
		m_pBtnInvite->EnableBtn(FALSE);
		m_pBtnOut->EnableBtn(FALSE);
		m_pBtnExit->EnableBtn(FALSE);
		m_pBtnCreate->EnableBtn(TRUE);
		m_pBtnAdmission->EnableBtn(TRUE);

	}
	else if(m_stMyRoomInfo.MasterCharacterUID == g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber)
	{// ?????? ?????? ????.
		m_pBtnCharge->EnableBtn(TRUE);
		m_pBtnInvite->EnableBtn(TRUE);
		m_pBtnOut->EnableBtn(TRUE);
		m_pBtnExit->EnableBtn(TRUE);
		m_pBtnCreate->EnableBtn(FALSE);
		m_pBtnAdmission->EnableBtn(FALSE);
	}
	else
	{// ???????? ???? ??????????.
		m_pBtnCharge->EnableBtn(FALSE);
		// 2009-01-12 by bhsohn ???? ???? ????????
		// ???? ?????? ?????? ????
		//m_pBtnInvite->EnableBtn(TRUE);
		bEnabelOkBtn = FALSE;
		m_pBtnInvite->EnableBtn(FALSE);
		// end 2009-01-12 by bhsohn ???? ???? ????????
		m_pBtnOut->EnableBtn(FALSE);
		m_pBtnExit->EnableBtn(TRUE);
		m_pBtnCreate->EnableBtn(FALSE);
		m_pBtnAdmission->EnableBtn(FALSE);		
	}

	// 2009-01-12 by bhsohn ???? ???? ????????
	m_pBtnVoiceOk->EnableBtn(bEnabelOkBtn);
	m_pBtnVoiceCan->EnableBtn(bEnabelOkBtn);
	// end 2009-01-12 by bhsohn ???? ???? ????????
}
void CINFCommunityChatRoom::CreateMyRoomOK(MSG_IC_CHATROOM_CREATE_OK* pMsg)
{
	m_stMyRoomInfo.ChatRoomNum = pMsg->ChatRoomNum;
	SCHATROOM_MEMBER_INFO sMember;
	sMember.CharacterUID = g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
	memcpy(sMember.CharacterName,g_pShuttleChild->m_myShuttleInfo.CharacterName,SIZE_MAX_CHARACTER_NAME);
	m_vecMyMember.push_back(sMember);
	m_stMyRoomInfo.ChatRoomInfoListCount++;
	m_pLBChatRoom->SetSelectItem(GetListBoxSelectItem(m_stMyRoomInfo.ChatRoomMaxCount));
	m_stMyRoomInfo.MasterCharacterUID = g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
	m_pEBChatRoomCS->SetString(m_stMyRoomInfo.ChatRoomName,SIZE_MAX_CHATROOM_NAME);
	m_pSEChatRoomSecu->SetString(m_stMyRoomInfo.ChatRoomPW,SIZE_MAX_TEAM_PW);
	SetButtonActive();


}
void CINFCommunityChatRoom::ChangeLockPWOK(MSG_IC_CHATROOM_CHANGE_LOCK_PW_OK* pMsg)
{
	char buf[SIZE_MAX_TEAM_PW];
	m_stMyRoomInfo.ChatRoomLock = pMsg->ChatRoomLock;
	m_pSEChatRoomSecu->GetString(buf,SIZE_MAX_TEAM_PW);
	memcpy(m_stMyRoomInfo.ChatRoomPW,buf,SIZE_MAX_TEAM_PW);
}
void CINFCommunityChatRoom::InitMyChatRoom()
{
	memset(&m_stMyRoomInfo,0x00,sizeof(m_stMyRoomInfo));
	m_vecMyMember.clear();
	m_pEBChatRoomCS->InitString();
	m_pSEChatRoomSecu->InitString();
	m_pLBChatRoom->SetSelectItem(0);
}
void CINFCommunityChatRoom::ChatRoomLeaveOK(MSG_IC_CHATROOM_LEAVE_OK* pMsg)
{
	char buf[256];
	memset(&buf,0x00,256);
	if(pMsg->CharacterUID == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber)
	{// ?? ?????? ???????? ??????????.
		InitMyChatRoom();
		SetButtonActive();
		g_pGameMain->m_pChat->SetChatRoomAct(FALSE);
	}
	else
	{
		vector<SCHATROOM_MEMBER_INFO>::iterator it = m_vecMyMember.begin();
		while(m_vecMyMember.end() != it)
		{
			if(it->CharacterUID == pMsg->CharacterUID)
			{
				wsprintf(buf,STRMSG_C_080715_0101,it->CharacterName);
				g_pGameMain->CreateChatChild(buf,COLOR_ITEM);
				it = m_vecMyMember.erase(it);
				m_stMyRoomInfo.ChatRoomInfoListCount--;
				break;
			}
			it++;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCommunityChatRoom::ChatRoomBan(MSG_IC_CHATROOM_BAN_OK* pMsg)
/// \brief		???????? ???? ?????? ?????? ??????????.
/// \author		dgwoo
/// \date		2008-07-01 ~ 2008-07-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCommunityChatRoom::ChatRoomBan(MSG_IC_CHATROOM_BAN_OK* pMsg)
{
	char buf[256];
	memset(&buf,0x00,256);
	if(pMsg->BanCharacterUID == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber)
	{
		InitMyChatRoom();
		SetButtonActive();
		g_pGameMain->CreateChatChild(STRMSG_C_080625_0108,COLOR_ITEM);
		g_pGameMain->m_pChat->SetChatRoomAct(FALSE);
		
	}
	else
	{
		vector<SCHATROOM_MEMBER_INFO>::iterator it = m_vecMyMember.begin();
		while(m_vecMyMember.end() != it)
		{
			if(it->CharacterUID == pMsg->BanCharacterUID)
			{
				wsprintf(buf,STRMSG_C_080715_0100,pMsg->BanCharacterName);
				g_pGameMain->CreateChatChild(buf,COLOR_ITEM);
				it = m_vecMyMember.erase(it);
				m_stMyRoomInfo.ChatRoomInfoListCount--;
				break;
			}
			it++;
		}
	}
}

void CINFCommunityChatRoom::UpdateBtnPos()
{
	m_ptCommunityPos =  ((CINFCommunity*)m_pParent)->GetCommunityBkPos();	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		?????? ??????, ???????? ??????
/// \author		// 2009-04-14 by bhsohn ???? ???? ?????? ??????, ?????? ????
/// \date		2009-04-14 ~ 2009-04-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCommunityChatRoom::OutChatRoom()
{
	if(m_stMyRoomInfo.ChatRoomNum == 0)
	{
		// ????????
		return;
	}
	MSG_IC_CHATROOM_LEAVE sMsg;
	memset(&sMsg, 0x00, sizeof(MSG_IC_CHATROOM_LEAVE));

	sMsg.ChatRoomNum = m_stMyRoomInfo.ChatRoomNum;
	memcpy(sMsg.LeaveCharacterName,g_pShuttleChild->m_myShuttleInfo.CharacterName,SIZE_MAX_CHARACTER_NAME);
	g_pIMSocket->SendMsg(T_IC_CHATROOM_LEAVE, (char*)&sMsg, sizeof(sMsg));
}