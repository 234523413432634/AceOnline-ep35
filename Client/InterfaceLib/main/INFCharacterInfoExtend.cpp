// INFCharacterInfoExtend.cpp: implementation of the CINFCharacterInfoExtend class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFGameMain.h"
#include "QuestData.h"
#include "D3DHanFont.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "FieldWinSocket.h"
#include "INFIcon.h"
#include "AtumDatabase.h"
#include "Interface.h"
#include "INFPilotFace.h"
#include "INFWindow.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "AtumSJ.h"
#include "Skill.h"
#include "WeaponItemInfo.h"
#include "StoreData.h"
#include "SkillInfo.h"
#include "INFScrollBar.h"
#include "INFCityBase.h"
#include "Chat.h"
#include "INFSkill.h"
#include "INFCommunity.h"
#include "INFCommunityGuild.h"
#include "INFSelect.h"
#include "dxutil.h"
#include "INFCityBazaar.h"
#include "INFImageBtn.h"		// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
#include "AtumSound.h"			// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
#include "INFItemInfo.h"
// 2009-02-13 by bhsohn ���� ��ŷ �ý���
#include "WorldRankManager.h"
// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

#include "INFCharacterInfoExtend.h"
#include "INFArenaScrollBar.h"	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
#include "PetManager.h"			// 2010-06-15 by shcho&hslee ��ý��� - �� �����͸� �������� �Լ�

#include "CustomOptimizer.h"

//#define INFO_HP_START_X		56
#define INFO_START_X		248
#define INFO_START_Y		69
#define INFO_START_INTERVAL_X		240


#define INFO_INTERVAL		18

#define CHAR_UTC_START_X		(nWindowPosX+31)
#define CHAR_UTC_START_Y		(nWindowPosY+217)
#define CHAR_UTC_ICON_SIZE		30
#define CHAR_UTC_INTERVAL_X		113
#define CHAR_UTC_INTERVAL_Y		36

#define UTC_SCROLL_BUTTON_START_X			(nWindowPosX+485)
#define UTC_SCROLL_BAR_SIZE_X				11
#define UTC_SCROLL_BAR_SIZE_Y				30
//#define UTC_MAX_SCROLL_NUMBER				max(max(g_pD3dApp->m_pShuttleChild->m_mapSkillAttack.size(),g_pD3dApp->m_pShuttleChild->m_mapSkillDefense.size()),max(g_pD3dApp->m_pShuttleChild->m_mapSkillSupport.size(),g_pD3dApp->m_pShuttleChild->m_mapSkillAttribute.size()))
#define UTC_MAX_SCROLL_NUMBER				GetUtcMaxScrollNumber()
#define UTC_SCROLL_BUTTON_UP_START_Y		71
#define UTC_SCROLL_BUTTON_DOWN_START_Y		247
#define UTC_SCROLL_BAR_START_Y				212
#define UTC_SCROLL_BAR_END_Y				538
#define UTC_SCROLL_INTERVAL					(UTC_MAX_SCROLL_NUMBER==0 ? 0:((UTC_SCROLL_BAR_END_Y-UTC_SCROLL_BAR_START_Y)/UTC_MAX_SCROLL_NUMBER))

#define CHARACTER_FACE_START_X				17
#define CHARACTER_FACE_START_Y				171
#define CHARACTER_FACE_SIZE_X				66
#define CHARACTER_FACE_SIZE_Y				86

#define AMMO_INTERVAL						18
#define AMMO_DEFENSE_START_X				20

#define C_QUEST_START_X						(nWindowPosX+19)
#define C_QUEST_START_Y						70
#define C_QUEST_SIZE_X						171
#define C_QUEST_SIZE_Y						103
//#define C_QUEST_STATE_START_X				136
//#define C_QUEST_STATE_START_Y				70
#define C_QUEST_INTERVAL					17
#define C_QUEST_DESC_START_X				(nWindowPosX+20)
#define C_QUEST_DESC_START_Y				178
#define C_QUEST_DESC_INTERVAL				15
#define C_QUEST_DESC_SIZE_X					171
#define C_QUEST_DESC_SIZE_Y					78


#define QUEST_LIST_SCROLL_START_X		(nWindowPosX+198)
#define QUEST_LIST_SCROLL_START_Y		84
#define QUEST_LIST_SCROLL_LINE_LENGTH	76
#define QUEST_DESC_SCROLL_START_X		(nWindowPosX+198)
#define QUEST_DESC_SCROLL_START_Y		185
#define QUEST_DESC_SCROLL_LINE_LENGTH	61

//#define CHAR_SCROLL_BAR_SIZE_X					11
//#define CHAR_SCROLL_BAR_SIZE_Y					30

//#define CHAR_QUEST_LIST_SCROLL_BAR_START_X		192
//#define CHAR_QUEST_LIST_SCROLL_BAR_START_Y		83
//#define CHAR_QUEST_LIST_SCROLL_BAR_LENGTH		(76-CHAR_SCROLL_BAR_SIZE_Y)
//#define CHAR_QUEST_LIST_SCROLL_BAR_INTERVAL(count)		(count==0 ? 0:(CHAR_QUEST_LIST_SCROLL_BAR_LENGTH/count))

//#define CHAR_QUEST_DESC_SCROLL_BAR_START_X		192
//#define CHAR_QUEST_DESC_SCROLL_BAR_START_Y		185
//#define CHAR_QUEST_DESC_SCROLL_BAR_LENGTH		(61-30)
//#define CHAR_QUEST_DESC_SCROLL_BAR_INTERVAL(count)		(count==0 ? 0:(CHAR_QUEST_DESC_SCROLL_BAR_LENGTH/count))
#define SHOP_START_X				CITY_BASE_NPC_BOX_START_X
#define SHOP_START_Y				(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y)
// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//#define SHOP_SKILL_BACK_START_X		(SHOP_START_X+26)
//#define SHOP_SKILL_BACK_START_Y		(SHOP_START_Y+34)
//#define SHOP_SKILL_START_X			(SHOP_SKILL_BACK_START_X+6)
//#define SHOP_SKILL_START_Y			(SHOP_SKILL_BACK_START_Y+29)
//#define SHOP_SKILL_INTERVAL_X		43
//#define SHOP_SKILL_INTERVAL_Y		32
//#define SHOP_SKILL_SPI_START_X		(SHOP_SKILL_BACK_START_X+26)
//#define SHOP_SKILL_SPI_START_Y		(SHOP_SKILL_BACK_START_Y+238)
//#define SHOP_SKILL_SCROLL_START_X	(SHOP_SKILL_BACK_START_X+174)
//#define SHOP_SKILL_SCROLL_START_Y	(SHOP_SKILL_BACK_START_Y+8)
//#define SHOP_SKILL_LENGTH			181
//#define SHOP_SKILL_BACK_SIZE_X		166
//#define SHOP_SKILL_BACK_SIZE_Y		181
#define SHOP_SKILL_BACK_START_X		(SHOP_START_X)
#define SHOP_SKILL_BACK_START_Y		(SHOP_START_Y)
#define SHOP_SKILL_START_X			(SHOP_SKILL_BACK_START_X+20)
#define SHOP_SKILL_START_Y			(SHOP_SKILL_BACK_START_Y+57)
#define SHOP_SKILL_INTERVAL_X		116
#define SHOP_SKILL_INTERVAL_Y		35
#define SHOP_SKILL_SPI_START_X		(SHOP_SKILL_BACK_START_X+26)
#define SHOP_SKILL_SPI_START_Y		(SHOP_SKILL_BACK_START_Y+238)
#define SHOP_SKILL_SCROLL_START_X	(SHOP_SKILL_BACK_START_X+489)
#define SHOP_SKILL_SCROLL_START_Y	(SHOP_SKILL_BACK_START_Y+58)
#define SHOP_SKILL_LENGTH			181
#define SHOP_SKILL_BACK_SIZE_X		500
#define SHOP_SKILL_BACK_SIZE_Y		181
// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��

#define SKILL_DROP_SIZE				22

// 29/03/2006 by ispark, �� ���� ��ġ ����
//#ifdef LANGUAGE_ENGLISH
//#define INFO_LEVEL_START_X			18//13
//#define INFO_LEVEL_START_Y			25//26
//#define INFO_ID_START_Y				24//26
//#define OTHER_INFO_START_Y			184//186
//
//#define GUILD_START_Y						96
//#define GENERAL_START_Y						87
//#define PROPENSITY_START_Y					105
//
//#define AMMO_START_X				80//71
//#define AMMO_START_Y				68//70
//
//#define STATINFO_START_X0			55//50
//#define STATINFO_START_X1			160//155
//
//#define CHARACTER_AMMO_TEXT_X1		26
//#define CHARACTER_AMMO_TEXT_X2		61
//
//#define SHOWSTATINFO_Y1				186
//#define SHOWSTATINFO_Y2				205
//#define SHOWSTATINFO_Y3				223
//#define SHOWSTATINFO_Y4				241
//#endif
//
//#ifdef LANGUAGE_KOREA
//#define INFO_LEVEL_START_X			13
//#define INFO_LEVEL_START_Y			24//26
//#define INFO_ID_START_Y				25//26
//#define OTHER_INFO_START_Y			184//186
//
//#define GUILD_START_Y				67//69
//#define GENERAL_START_Y				85//87
//#define PROPENSITY_START_Y			103//105
//#define AMMO_START_X				71
//#define AMMO_START_Y				68//70
//
//#define STATINFO_START_X0			50
//#define STATINFO_START_X1			155
//
//#define CHARACTER_AMMO_TEXT_X1		0
//#define CHARACTER_AMMO_TEXT_X2		51
//
//#define SHOWSTATINFO_Y1				186//187
//#define SHOWSTATINFO_Y2				205//206
//#define SHOWSTATINFO_Y3				223//224
//#define SHOWSTATINFO_Y4				241//243
//#endif
//
//#ifdef LANGUAGE_CHINA
//#define INFO_LEVEL_START_X			13
//#define INFO_LEVEL_START_Y			24//26
//#define INFO_ID_START_Y				25//26
//#define OTHER_INFO_START_Y			184//186
//
//#define GUILD_START_Y				67//69
//#define GENERAL_START_Y				85//87
//#define PROPENSITY_START_Y			103//105
//#define AMMO_START_X				71
//#define AMMO_START_Y				68//70
//
//#define STATINFO_START_X0			50
//#define STATINFO_START_X1			155
//
//#define CHARACTER_AMMO_TEXT_X1		0
//#define CHARACTER_AMMO_TEXT_X2		51
//
//#define SHOWSTATINFO_Y1				186//187
//#define SHOWSTATINFO_Y2				205//206
//#define SHOWSTATINFO_Y3				223//224
//#define SHOWSTATINFO_Y4				241//243
//#endif
//
//#ifdef LANGUAGE_VIETNAM
//#define INFO_LEVEL_START_X			18//13
//#define INFO_LEVEL_START_Y			25//26
//#define INFO_ID_START_Y				24//26
//#define OTHER_INFO_START_Y			184//186
//
//#define GUILD_START_Y						69
//#define GENERAL_START_Y						87
//#define PROPENSITY_START_Y					105
//
//#define AMMO_START_X				118//80//71
//#define AMMO_START_Y				68//70
//
//#define STATINFO_START_X0			55//50
//#define STATINFO_START_X1			160//155
//
//#define CHARACTER_AMMO_TEXT_X1		13//26
//#define CHARACTER_AMMO_TEXT_X2		99//61
//
//#define SHOWSTATINFO_Y1				186
//#define SHOWSTATINFO_Y2				205
//#define SHOWSTATINFO_Y3				223
//#define SHOWSTATINFO_Y4				241
//#endif
//// 2008-04-30 by bhsohn �±� ���� �߰�
//#ifdef LANGUAGE_THAI
//	#define INFO_LEVEL_START_X			18//13
//	#define INFO_LEVEL_START_Y			25//26
//	#define INFO_ID_START_Y				24//26
//	#define OTHER_INFO_START_Y			184//186
//
//	#define GUILD_START_Y						69
//	#define GENERAL_START_Y						87
//	#define PROPENSITY_START_Y					105
//
//	#define AMMO_START_X				80//71
//	#define AMMO_START_Y				68//70
//
//	#define STATINFO_START_X0			55//50
//	#define STATINFO_START_X1			160//155
//
//	#define CHARACTER_AMMO_TEXT_X1		26
//	#define CHARACTER_AMMO_TEXT_X2		61
//
//	#define SHOWSTATINFO_Y1				186
//	#define SHOWSTATINFO_Y2				205
//	#define SHOWSTATINFO_Y3				223
//	#define SHOWSTATINFO_Y4				241
//#endif
//// 2008-04-30 by bhsohn �±� ���� �߰�
#define GENERAL_START_X						248
#define GENERAL_START_Y						110

#define GUILD_START_X						248
#define GUILD_START_Y						92

#define GUILD_MARK_START_X						130
#define GUILD_MARK_START_Y						94

#define PROPENSITY_START_X					486
#define PROPENSITY_START_Y					56

#define PERSONAL_STAT_X						486
#define PERSONAL_STAT_Y						74

#define GUILDWAR_STAT_X						486
#define GUILDWAR_STAT_Y						92

#define INFO_LEVEL_START_X			248
#define INFO_LEVEL_START_Y			74

#define INFO_ID_START_X		100
#define INFO_ID_START_Y		56

// 2009-02-13 by bhsohn ���� ��ŷ �ý���
#define WR_NICKNAME_START_X						248
#define WR_NICKNAME_START_Y						128
// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

//////////////// ���� ��Ʈ��//////////////// 
#define STATINFO_START_X0			209
#define STATINFO_START_X1			443

#define SHOWSTATINFO_Y1				196
#define SHOWSTATINFO_Y2				215
#define SHOWSTATINFO_Y3				233
#define SHOWSTATINFO_Y4				251

//////////////// ���� ��ư//////////////// 
#define STAT_TOOLTIP_LEFT_START_X			175
#define STAT_TOOLTIP_RIGHT_START_X			410

#define STAT_TOOLTIP_ATTACK_START_Y			198
#define STAT_TOOLTIP_ENDURANCE_START_Y		198
#define STAT_TOOLTIP_FUEL_START_Y			198
#define STAT_TOOLTIP_SOUL_START_Y			216
#define STAT_TOOLTIP_DODGE_START_Y			234
#define STAT_TOOLTIP_DEFENSE_START_Y		216
#define STAT_TOOLTIP_SIZE_X					64
#define STAT_TOOLTIP_SIZE_Y					13


#define OTHER_INFO_START_Y			405

// 2007-05-15 by bhsohn ��� ���� ���� ó��
// �������� �۾� ����
#define	OVER_STAT_CAP0_X			(13)
#define	OVER_STAT_CAP1_X			(24)
#define	OVER_STAT_CAPX				30

// 2007-06-07 by dgwoo �Ʒ��� ����â.
#define ARENA_GAP_H							18

#define ARENA_SCORE_X						(nWindowPosX + 248)
#define ARENA_SCORE_Y						(nWindowPosY + 463)

#define ARENA_SCORE_PERCENTAGE_X			(nWindowPosX + 248)
#define ARENA_SCORE_PERCENTAGE_Y			(ARENA_SCORE_Y + ARENA_GAP_H)

#define ARENA_COMPULSION_END_X				(nWindowPosX + 248)
#define ARENA_COMPULSION_END_Y				(ARENA_SCORE_PERCENTAGE_Y + ARENA_GAP_H)

// ���� ����Ʈ
#define ARENA_COMMULATION_POINT_X			(nWindowPosX + 248)
#define ARENA_COMMULATION_POINT_Y			(ARENA_COMPULSION_END_Y + ARENA_GAP_H + ARENA_GAP_H + 5)

// ���� ����Ʈ
#define ARENA_FUSIBLE_POINT_X				(nWindowPosX + 248)
#define ARENA_FUSIBLE_POINT_Y				(ARENA_COMMULATION_POINT_Y + ARENA_GAP_H)

#define AMMO_START_X				248
#define AMMO_START_Y				309
#define AMMO_START_INTERVAL_X		240

#define INVEN_WEIGHT_START_X	486
#define INVEN_WEIGHT_START_Y	(464)

#define AMMO_WEIGHT_START_X				486
#define AMMO_WEIGHT_START_Y				482

#define WEIGHT_FUEL_START_X				486
#define WEIGHT_FUEL_START_Y				500

#define WEIGHT_BOOSTER_START_X				486
#define WEIGHT_BOOSTER_START_Y				518

#define WEIGHT_SPEED_START_X				486
#define WEIGHT_SPEED_START_Y				536


#define INFO_TAB_POX_X			24
#define INFO_TAB_POX_Y			155

#define INFO_TAB_POX_W			80
#define INFO_TAB_POX_H			23

#define ATTACK_TOOLIP_W			150

// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
#define PARTNER_NAMECHANGE_BTN_X 432
#define PARTNER_NAMECHANGE_BTN_Y 207 

#define PARTNER_OKCANCEL_BTN_X  347
#define PARTNER_OKCANCEL_BTN_Y  549

#define PARTNER_INFO_X			 222
#define PARTNER_INFO_Y			 207
#define PARTNER_INFO_Y_GAP		 18 

#define PARTNER_DTAIL_INFO_X		477
#define PARTNER_DTAIL_INFO_Y		325
#define PARTNER_DTAIL_INFO_Y_GAP	30

// 2010-06-15 by shcho&hslee ��ý��� - �� Ÿ�� �� ���� ����. - AtumParam.h �ű�.
/*
#define PARTNER_TYPE_ATT		 1
#define PARTNER_TYPE_DFN		 2
#define PARTNER_TYPE_BUF		 3
#define PARTNER_TYPE_STORE		 4
*/
// End 2010-06-15 by shcho&hslee ��ý��� - �� Ÿ�� �� ���� ����.


#define PARTNER_EXP_POS_X		 160
#define PARTNER_EXP_POS_Y		 329 + 42

#define PARTNER_STAMENA_POS_X	 160
#define PARTNER_STAMENA_POS_Y	 359

#define PARTNER_EXP_SCROLL		 50
#define PARTNER_EXP_SCROLL_POS_X 157
#define PARTNER_EXP_SCROLL_POS_Y 387 + 8
#define PARTNER_EXP_SCROLL_POS_W 219
#define PARTNER_EXP_SCROLL_POS_H 0

//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

/////////////////////////////////////////////////////////////////////////

#define PARTNER_IMAGE_POS_X			40
#define PARTNER_IMAGE_POS_Y			209

#define PARTNER_SOCKET_POS_X		75
#define PARTNER_SOCKET_POS_Y		444
#define PARTNER_SOCKET_GAP			13
					

/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCharacterInfoExtend::CINFCharacterInfoExtend(CAtumNode* pParent)
{
	FLOG( "CINFCharacterInfoExtend(CAtumNode* pParent)" );
	//m_pAmmo = NULL;
	//m_pStatImage = NULL;
	m_pInfo = NULL;
	m_pInoBk = NULL;
	//m_pId = NULL;
	m_pUtc = NULL;
	m_pUtcScr = NULL;
//	m_pImgArenaTab = NULL;
//	m_pScrollBar = NULL;
	m_pQuestSelect = NULL;
	m_pSkillShopBack = NULL;

	m_pParent = pParent;
	m_nCharacterInfoType = CHARACTER_INFO;
	m_nStatType = STAT_BUTTON_UP ;
	
	int i;

	for (i=0 ; i<5 ; i++)
	{
		m_CharacInfoFont[i] = NULL ;
	}
	for(i=0 ; i<7 ; i++)
	{
		m_StatInfoFont[i] = NULL ;
	}
	
	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	m_StatOverInfoFont = NULL;
	m_StatInfoBoldFont = NULL;

//	for(i=0 ; i<3 ; i++)
//	{
//		m_pStat[i] = NULL ;
//	}
	m_pFontName = NULL;
	m_pFontLevel = NULL;
	m_pFontGuild = NULL;
	m_pFontGeneral = NULL;
	m_pFontPropensity = NULL;
	m_pFontAutoStat = NULL;
	m_pFontStatDec = NULL;
	for(i=0 ; i<CHARACTER_INTERFACE_FONT_NUM ; i++)
	{
		m_pFontAmmoWeapon[i] = NULL ;
	}

	m_nCurrentUTCScroll = 0;
	memset(m_pSkillShopSkillDisplayInfo, 0x00, sizeof(INVEN_DISPLAY_INFO)*CHAR_UTC_TYPE_NUMBER*MAX_CHAR_UTC_SLOT_NUMBER);
	memset(m_pCharacterSkillDisplayInfo, 0x00, sizeof(INVEN_DISPLAY_INFO)*CHAR_UTC_TYPE_NUMBER*MAX_CHAR_UTC_SLOT_NUMBER);
	m_pSelectIcon = NULL;
	m_pSelectSkill = NULL;
	m_bUTCScrollLock = FALSE;
	m_ptMouse.x = 0;
	m_ptMouse.y = 0;

	for(i=0;i<C_QUEST_LIST_NUM;i++)
	{
		m_pFontQuestList[i] = NULL;
//		m_pFontQuestState[i] = NULL;
	}
	for(i=0;i<C_QUEST_DESC_NUM;i++)
	{
		m_pFontQuestDesc[i] = NULL;
	}
	for(i=0; i<MAX_CHAR_UTC_SLOT_NUMBER; i++)
	{
		m_pFontItemNum[i] = NULL;
	}
//	m_nCurrentQuestListScroll = 0;
//	m_nCurrentSelectQuestList = 0;
//	m_bQuestListLock = FALSE;
//	m_nCurrentQuestDescScroll = 0;
//	m_nCurrentSelectQuestDesc = 0;
//	m_bQuestDescLock = FALSE;
	m_bRestored = FALSE;
	m_bInvalidated = FALSE;
	m_nRenderMoveIconIntervalWidth  = 0;
	m_nRenderMoveIconIntervalHeight = 0;
	m_pQuestListScrollBar = NULL;
	m_pQuestDescScrollBar = NULL;
	m_pShopSkillScrollBar = NULL;
	m_nOldQuestSelectDataIndex = 0;

	m_pDeleteSkill = NULL;
	m_nMissionProCount = 0;
	m_bLbuttonDown = FALSE;	
//	m_bToolTipStat = FALSE;						// 2005-07-04 by ispark �ڵ� ���� �й� ����

	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	int nTmpCnt=0;
	for(nTmpCnt=0;nTmpCnt < MAX_STAT_SHUTTLEINFO;nTmpCnt++)
	{
		m_bStatShow[nTmpCnt] = TRUE;
		m_nShowOverStat[nTmpCnt] = 0;
		m_pBonusStatBtn[nTmpCnt] = NULL; // ���ʽ� ����
	}
	// end 2007-05-15 by bhsohn ��� ���� ���� ó��

	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	m_pOpenBtn = NULL;			
	m_pCloseBtn = NULL;

	m_ptBkPos.x = m_ptBkPos.y = 0;
	m_bShowWnd = FALSE;

	m_bMove = FALSE;	
	m_ptCommOpMouse.x = m_ptCommOpMouse.y = 0;

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	m_pNickNameBtn = NULL;
	m_pFontNickName = NULL;
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pChangeNameBtn	= NULL;
	m_pPartnerInfoBk	= NULL;
	m_pPartnerName		= NULL;
	m_pPartnerLv		= NULL;
	m_pPartnerType		= NULL;
	m_pStamina			= NULL;
	m_pPartnerLvBar		= NULL;
	m_pPartnerStaminaBar= NULL;
	m_pPartnerGiveExp	= NULL;
	m_pExpScroll		= NULL;
	
	m_pPartnerSocet			= NULL;
	m_pPartnerSocetClose	= NULL;
	m_pPartnerSocetSelect	= NULL;
	
	
	for(i=0; i < 2; i++)
	{
		m_pPartnerImageLvBar[i] = NULL;
		m_pPartnerImageStaminaBar[i] = NULL;
	}

	m_pPartnerImage		= NULL;
	m_pPartnerBtnCancel	= NULL;
	m_pPartnerBtnOK		= NULL;

	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
}

CINFCharacterInfoExtend::~CINFCharacterInfoExtend()
{
	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	SAFE_DELETE(m_pOpenBtn);	
	SAFE_DELETE(m_pCloseBtn);
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO;nCnt++)
	{
		m_pBonusStatBtn[nCnt] = NULL; // ���ʽ� ����
	}	
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	SAFE_DELETE(m_pNickNameBtn);
	SAFE_DELETE(m_pFontNickName);
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	
	FLOG( "~CINFCharacterInfoExtend()" );
	//SAFE_DELETE(m_pAmmo );
	//SAFE_DELETE(m_pStatImage ) ;
	SAFE_DELETE(m_pInfo);
	SAFE_DELETE(m_pInoBk);
	//SAFE_DELETE(m_pId);
	SAFE_DELETE(m_pUtc);
	SAFE_DELETE(m_pUtcScr);
	SAFE_DELETE(m_pSkillShopBack);
//	SAFE_DELETE(m_pImgArenaTab);
//	SAFE_DELETE(m_pScrollBar);
	SAFE_DELETE(m_pQuestListScrollBar);
	SAFE_DELETE(m_pQuestDescScrollBar);
	SAFE_DELETE(m_pShopSkillScrollBar);
	SAFE_DELETE(m_pQuestSelect);
	SAFE_DELETE(m_pFontName);
	SAFE_DELETE(m_pFontLevel);
	SAFE_DELETE(m_pFontGuild);
	SAFE_DELETE(m_pFontGeneral);
	SAFE_DELETE(m_pFontPropensity);
	SAFE_DELETE(m_pFontAutoStat);
	SAFE_DELETE(m_pFontStatDec);
	int i;
	for(i=0 ; i<5 ; i++)
	{
		SAFE_DELETE(m_CharacInfoFont[i] ) ;
	}
	for(i=0 ; i<7 ; i++)
	{
		SAFE_DELETE(m_StatInfoFont[i] ) ;
	}
	
	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	SAFE_DELETE(m_StatOverInfoFont);
	SAFE_DELETE(m_StatInfoBoldFont);	

//	for(i=0 ; i<3 ; i++)
//	{
//		SAFE_DELETE(m_pStat[i] );
//	}
	for(i=0;i<C_QUEST_LIST_NUM;i++)
	{
		SAFE_DELETE(m_pFontQuestList[i]);
//		SAFE_DELETE(m_pFontQuestState[i]);
	}
	for(i=0;i<C_QUEST_DESC_NUM;i++)
	{
		SAFE_DELETE(m_pFontQuestDesc[i]);
	}
	for(i=0 ; i<CHARACTER_INTERFACE_FONT_NUM ; i++)
	{
		SAFE_DELETE(m_pFontAmmoWeapon[i]);
	}
	for(i=0; i<MAX_CHAR_UTC_SLOT_NUMBER; i++)
	{
		SAFE_DELETE(m_pFontItemNum[i]);
	}
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	SAFE_DELETE(m_pChangeNameBtn);
	SAFE_DELETE(m_pPartnerInfoBk);	
	SAFE_DELETE(m_pPartnerName);
	SAFE_DELETE(m_pPartnerLv);
	SAFE_DELETE(m_pPartnerType);
	SAFE_DELETE(m_pStamina);
	


	SAFE_DELETE(m_pPartnerSocet	);
	SAFE_DELETE(m_pPartnerSocetClose);
	SAFE_DELETE(m_pPartnerSocetSelect);

	SAFE_DELETE(m_pPartnerImage);
	
	SAFE_DELETE(m_pExpScroll);

	for(i=0; i < 2; i++)
	{
		SAFE_DELETE(m_pPartnerImageLvBar[i]);
		SAFE_DELETE(m_pPartnerImageStaminaBar[i]);
	}
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
}

HRESULT CINFCharacterInfoExtend::InitDeviceObjects()
{
	FLOG( "CINFCharacterInfoExtend::InitDeviceObjects()" );
	//����
	DataHeader	* pDataHeader ;

//	m_pAmmo = new CINFImage;
//	pDataHeader = FindResource("ammo");
//	m_pAmmo->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

//		m_pStatImage = new CINFImage;
//	pDataHeader = FindResource("stat");
//	m_pStatImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pInfo = new CINFImage;
	pDataHeader = FindResource("in_bk1");
	m_pInfo->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pInoBk = new CINFImage;
	pDataHeader = FindResource("in_bk0");
	m_pInoBk->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

//		m_pId = new CINFImage;
//	pDataHeader = FindResource("ID");
//	m_pId->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pUtc = new CINFImage;
	pDataHeader = FindResource("in_bk2");
	m_pUtc->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pPartnerInfoBk = new CINFImage;
	pDataHeader = FindResource("in_bk3");
	m_pPartnerInfoBk->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pExpScroll = new CINFArenaScrollBar;
	m_pExpScroll->InitDeviceObjects(0, "c_scrlbt");

	m_pChangeNameBtn = new CINFImageBtn;
	m_pChangeNameBtn->InitDeviceObjects("PN_change");

	m_pPartnerName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pPartnerName->InitDeviceObjects(g_pD3dDev);

	m_pPartnerLv = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pPartnerLv->InitDeviceObjects(g_pD3dDev);

	m_pPartnerType = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pPartnerType->InitDeviceObjects(g_pD3dDev);

	m_pStamina = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pStamina->InitDeviceObjects(g_pD3dDev);

	m_pPartnerLvBar = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pPartnerLvBar->InitDeviceObjects(g_pD3dDev);

	m_pPartnerStaminaBar = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pPartnerStaminaBar->InitDeviceObjects(g_pD3dDev);

	m_pPartnerGiveExp = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,256,32);
	m_pPartnerGiveExp->InitDeviceObjects(g_pD3dDev);

	m_pPartnerImageLvBar[0] = new CINFImage;
	pDataHeader = FindResource("PN_exp");
	m_pPartnerImageLvBar[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pPartnerImageLvBar[1] = new CINFImage;
	pDataHeader = FindResource("PN_exp1");
	m_pPartnerImageLvBar[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	


	m_pPartnerImageStaminaBar[0] = new CINFImage;
	pDataHeader = FindResource("PN_sta");
	m_pPartnerImageStaminaBar[0]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pPartnerImageStaminaBar[1] = new CINFImage;
	pDataHeader = FindResource("PN_sta1");
	m_pPartnerImageStaminaBar[1]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//��Ʈ�� �ý��� ���� ��Ʈ�� ����â ���Ϻκ�
	
	m_pPartnerImage = new CINFImage;
	pDataHeader = FindResource("PN_01");
	m_pPartnerImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	//��Ʈ�� �̹����κ� 
	
	m_pPartnerSocet = new CINFImage;
	pDataHeader = FindResource("PN_soc01");
	m_pPartnerSocet->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	//��Ʈ�� ���� ��Ȱ��ȭ ����
	m_pPartnerSocetClose = new CINFImage;
	pDataHeader = FindResource("PN_soc02");
	m_pPartnerSocetClose->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	//��Ʈ�� ���� ���ȭ ����
	m_pPartnerSocetSelect = new CINFImage;
	pDataHeader = FindResource("PN_soc03");
	m_pPartnerSocetSelect->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	//��Ʈ�� ���� ���� ����	

		

	{
		// �ݱ�
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "PN_can00");
		wsprintf(szDownBtn, "PN_can01");
		wsprintf(szSelBtn, "PN_can02");
		wsprintf(szDisBtn, "PN_can03");
		if(NULL == m_pPartnerBtnCancel)
		{
			m_pPartnerBtnCancel = new CINFImageBtn;
		}
		m_pPartnerBtnCancel->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	
	{
		// �ݱ�
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "if_lvapp0");
		wsprintf(szDownBtn, "if_lvapp1");
		wsprintf(szSelBtn, "if_lvapp2");
		wsprintf(szDisBtn, "if_lvapp3");
		if(NULL == m_pPartnerBtnOK)
		{
			m_pPartnerBtnOK = new CINFImageBtn;
		}
		m_pPartnerBtnOK->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	
	//��Ʈ�� ��� ��ư ���� 

	
	//��Ʈ�� ���� ȭ�� 

	///////////////////////////////////////////////////////////////////////////////////////////////////

	m_pUtcScr = new CINFImage;
	pDataHeader = FindResource("c_scrlb");
	m_pUtcScr->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pSkillShopBack = new CINFImage;
	pDataHeader = FindResource("shskill");
	m_pSkillShopBack->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

//		m_pImgArenaTab = new CINFImage;
//	pDataHeader = FindResource("arena_t");
//	m_pImgArenaTab->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pQuestSelect = new CINFImage;
	pDataHeader = FindResource("q_select");
	m_pQuestSelect->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	int i;
	for(i=0 ; i<5 ; i++)
	{
		m_CharacInfoFont[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
		m_CharacInfoFont[i]->InitDeviceObjects(g_pD3dDev) ;
	}
	for(i=0 ; i<7 ; i++)
	{
		m_StatInfoFont[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),10, D3DFONT_ZENABLE,  FALSE,256,32);
		m_StatInfoFont[i]->InitDeviceObjects(g_pD3dDev) ;
	}

	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	m_StatOverInfoFont = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
	m_StatOverInfoFont->InitDeviceObjects(g_pD3dDev) ;	

	m_StatInfoBoldFont = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE|D3DFONT_BOLD,  FALSE,256,32);
	m_StatInfoBoldFont->InitDeviceObjects(g_pD3dDev) ;	
	

//	for(i=0 ; i<3 ; i++)
//	{
//		m_pStat[i] = new CINFImage;
//		char Buf[30] ;
//		wsprintf(Buf, "stat0%d", i+1) ;
// 		pDataHeader = FindResource(Buf);
//		m_pStat[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
//	}
	m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),10, D3DFONT_ZENABLE,  FALSE,256,32);
	m_pFontName->InitDeviceObjects(g_pD3dDev) ;

	m_pFontLevel = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),10, D3DFONT_ZENABLE,  FALSE,256,32);
	m_pFontLevel->InitDeviceObjects(g_pD3dDev) ;

	m_pFontGuild = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
	m_pFontGuild->InitDeviceObjects(g_pD3dDev) ;
	m_pFontGeneral = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
	m_pFontGeneral->InitDeviceObjects(g_pD3dDev) ;
	m_pFontPropensity = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
	m_pFontPropensity->InitDeviceObjects(g_pD3dDev) ;
	m_pFontAutoStat = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
	m_pFontAutoStat->InitDeviceObjects(g_pD3dDev) ;
	m_pFontStatDec = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,512,32);
	m_pFontStatDec->InitDeviceObjects(g_pD3dDev) ;

	for(i=0;i<C_QUEST_LIST_NUM;i++)
	{
		m_pFontQuestList[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
		m_pFontQuestList[i]->InitDeviceObjects(g_pD3dDev) ;
//		m_pFontQuestState[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,128,32);
//		m_pFontQuestState[i]->InitDeviceObjects(g_pD3dDev) ;
	}
	for(i=0;i<C_QUEST_DESC_NUM;i++)
	{
		m_pFontQuestDesc[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
		m_pFontQuestDesc[i]->InitDeviceObjects(g_pD3dDev) ;
	}
	for(i=0 ; i<CHARACTER_INTERFACE_FONT_NUM ; i++)
	{
		m_pFontAmmoWeapon[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,256,32);
		m_pFontAmmoWeapon[i]->InitDeviceObjects(g_pD3dDev) ;
	}
	for(i=0; i<MAX_CHAR_UTC_SLOT_NUMBER; i++)
	{
		m_pFontItemNum[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  TRUE,256,32);
		m_pFontItemNum[i]->InitDeviceObjects(g_pD3dDev);
	}

	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;
	
	m_pQuestListScrollBar = new CINFScrollBar(this,
								QUEST_LIST_SCROLL_START_X-3, 
								nWindowPosY+QUEST_LIST_SCROLL_START_Y+1, 
								QUEST_LIST_SCROLL_LINE_LENGTH,
								C_QUEST_LIST_NUM);
	m_pQuestListScrollBar->SetGameData( m_pGameData );
	m_pQuestListScrollBar->InitDeviceObjects();
	m_pQuestDescScrollBar = new CINFScrollBar(this,
								QUEST_DESC_SCROLL_START_X, 
								nWindowPosY+QUEST_DESC_SCROLL_START_Y, 
								QUEST_DESC_SCROLL_LINE_LENGTH,
								C_QUEST_DESC_NUM);
	m_pQuestDescScrollBar->SetGameData( m_pGameData );
	m_pQuestDescScrollBar->InitDeviceObjects();
	m_pShopSkillScrollBar = new CINFScrollBar(this,
								SHOP_SKILL_SCROLL_START_X, 
								SHOP_SKILL_SCROLL_START_Y, 
								SHOP_SKILL_LENGTH,
								CHAR_UTC_SLOT_NUMBER);
	m_pShopSkillScrollBar->SetGameData( m_pGameData );
	m_pShopSkillScrollBar->InitDeviceObjects();
	m_pShopSkillScrollBar->SetWheelRect(SHOP_SKILL_BACK_START_X, 
		SHOP_SKILL_BACK_START_Y,
		SHOP_SKILL_BACK_START_X+SHOP_SKILL_BACK_SIZE_X,
		SHOP_SKILL_BACK_START_Y+SHOP_SKILL_BACK_SIZE_Y);

	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	{
		// �ݱ�
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "uopbtn3");
		wsprintf(szDownBtn, "uopbtn1");
		wsprintf(szSelBtn, "uopbtn0");
		wsprintf(szDisBtn, "uopbtn2");
		if(NULL == m_pOpenBtn)
		{
			m_pOpenBtn = new CINFImageBtn;
		}
		m_pOpenBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	int nCnt = 0;	
	for(nCnt = 0;nCnt< MAX_STAT_SHUTTLEINFO;nCnt++)
	{		
		// �ݱ�
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "stat02");
		wsprintf(szDownBtn, "stat03");
		wsprintf(szSelBtn, "stat03");
		wsprintf(szDisBtn, "stat01");
		if(NULL == m_pBonusStatBtn[nCnt])
		{
			m_pBonusStatBtn[nCnt] = new CINFImageBtn;
		}
		m_pBonusStatBtn[nCnt]->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	{
		// �ݱ�
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

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	CWorldRankManager*	pWorldRankManager = g_pD3dApp->GetWorldRankManager();	
	if(pWorldRankManager->GetUseWorldRanking())
	{	
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];		
		wsprintf(szUpBtn, "op_j3");
		wsprintf(szDownBtn, "op_j1");
		wsprintf(szSelBtn, "op_j0");
		wsprintf(szDisBtn, "op_j2");
		if(NULL == m_pNickNameBtn)
		{
			m_pNickNameBtn = new CINFImageBtn;
			m_pNickNameBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
		}		
		if(NULL == m_pFontNickName)
		{
			m_pFontNickName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE,  FALSE,512,32);
			m_pFontNickName->InitDeviceObjects(g_pD3dDev) ;
		}
	}
	
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	return S_OK ;
}



HRESULT CINFCharacterInfoExtend::RestoreDeviceObjects()
{
	FLOG( "CINFCharacterInfoExtend::RestoreDeviceObjects()" );
	//m_pAmmo->RestoreDeviceObjects();
	//m_pStatImage->RestoreDeviceObjects();

	m_pInfo->RestoreDeviceObjects();
	m_pInoBk->RestoreDeviceObjects();
	//m_pId->RestoreDeviceObjects();
	m_pUtc->RestoreDeviceObjects();
	m_pUtcScr->RestoreDeviceObjects();
	m_pSkillShopBack->RestoreDeviceObjects();
	//m_pImgArenaTab->RestoreDeviceObjects();
//	m_pScrollBar->RestoreDeviceObjects();
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pPartnerInfoBk->RestoreDeviceObjects();
	m_pChangeNameBtn->RestoreDeviceObjects();
	m_pPartnerName->RestoreDeviceObjects();
	m_pExpScroll->RestoreDeviceObjects();
	m_pPartnerLv->RestoreDeviceObjects();
	m_pPartnerType->RestoreDeviceObjects();
	m_pStamina->RestoreDeviceObjects();
	m_pPartnerLvBar->RestoreDeviceObjects();
	m_pPartnerStaminaBar->RestoreDeviceObjects();
	m_pPartnerGiveExp->RestoreDeviceObjects();

	m_pPartnerImage->RestoreDeviceObjects();
	m_pPartnerBtnCancel->RestoreDeviceObjects();
	m_pPartnerBtnOK->RestoreDeviceObjects();

	int i;
	for(i=0; i < 2; i++)
	{
		m_pPartnerImageLvBar[i]->RestoreDeviceObjects();
		m_pPartnerImageStaminaBar[i]->RestoreDeviceObjects();
	}
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pFontName->RestoreDeviceObjects();
	m_pFontLevel->RestoreDeviceObjects();
	m_pFontGuild->RestoreDeviceObjects();
	m_pFontGeneral->RestoreDeviceObjects();
	m_pFontPropensity->RestoreDeviceObjects();
	m_pFontAutoStat->RestoreDeviceObjects();
	m_pFontStatDec->RestoreDeviceObjects();
	m_pQuestListScrollBar->RestoreDeviceObjects();
	m_pQuestDescScrollBar->RestoreDeviceObjects();
	m_pQuestSelect->RestoreDeviceObjects();
	m_pShopSkillScrollBar->RestoreDeviceObjects();

	
	m_pPartnerSocet->RestoreDeviceObjects();
	m_pPartnerSocetClose->RestoreDeviceObjects();
	m_pPartnerSocetSelect->RestoreDeviceObjects();

	for(i=0 ; i<CHARACTER_INTERFACE_FONT_NUM ; i++)
	{
		m_pFontAmmoWeapon[i]->RestoreDeviceObjects();
	}

	for( i=0 ; i<5 ; i++)
	{
		m_CharacInfoFont[i]->RestoreDeviceObjects() ;
	}
	for(i=0 ; i<7 ; i++)
	{
		m_StatInfoFont[i]->RestoreDeviceObjects() ;
	}
	// 2007-05-15 by bhsohn ��� ���� ���� ó��	
	m_StatOverInfoFont->RestoreDeviceObjects() ;
	m_StatInfoBoldFont->RestoreDeviceObjects() ;

//	for(i=0 ; i<3 ; i++)
//	{
//		m_pStat[i]->RestoreDeviceObjects() ;
//	}
	for(i=0;i<C_QUEST_LIST_NUM;i++)
	{
		m_pFontQuestList[i]->RestoreDeviceObjects() ;
//		m_pFontQuestState[i]->RestoreDeviceObjects() ;
	}
	for(i=0;i<C_QUEST_DESC_NUM;i++)
	{
		m_pFontQuestDesc[i]->RestoreDeviceObjects() ;
	}
	for(i=0; i<MAX_CHAR_UTC_SLOT_NUMBER; i++)
	{
		m_pFontItemNum[i]->RestoreDeviceObjects() ;
	}
	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	if(m_pOpenBtn)
	{
		m_pOpenBtn->RestoreDeviceObjects();						
	}
	if(m_pCloseBtn)
	{
		m_pCloseBtn->RestoreDeviceObjects();						
	}
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO;nCnt++)
	{
		m_pBonusStatBtn[nCnt]->RestoreDeviceObjects();
	}	
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	if(m_pNickNameBtn)
	{
		m_pNickNameBtn->RestoreDeviceObjects();
	}
	if(m_pFontNickName)
	{
		m_pFontNickName->RestoreDeviceObjects();
	}
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	m_bRestored = TRUE;
	return S_OK ;
}

HRESULT CINFCharacterInfoExtend::DeleteDeviceObjects()
{
	FLOG( "CINFCharacterInfoExtend::DeleteDeviceObjects()" );
//	m_pAmmo->DeleteDeviceObjects();
//	SAFE_DELETE(m_pAmmo );
//	m_pStatImage->DeleteDeviceObjects();
//	SAFE_DELETE(m_pStatImage );

	m_pInfo->DeleteDeviceObjects();
	SAFE_DELETE(m_pInfo );
	m_pInoBk->DeleteDeviceObjects();
	SAFE_DELETE(m_pInoBk );
//	m_pId->DeleteDeviceObjects();
//	SAFE_DELETE(m_pId );
	m_pUtc->DeleteDeviceObjects();
	SAFE_DELETE(m_pUtc );
	m_pUtcScr->DeleteDeviceObjects();
	SAFE_DELETE(m_pUtcScr );
	m_pSkillShopBack->DeleteDeviceObjects();
	SAFE_DELETE(m_pSkillShopBack );
//	m_pImgArenaTab->DeleteDeviceObjects();
//	SAFE_DELETE(m_pImgArenaTab );
//	m_pScrollBar->DeleteDeviceObjects();
//	SAFE_DELETE(m_pScrollBar );
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pPartnerInfoBk->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerInfoBk);
	m_pExpScroll->DeleteDeviceObjects();
	SAFE_DELETE(m_pExpScroll);
	m_pChangeNameBtn->DeleteDeviceObjects();
	SAFE_DELETE(m_pChangeNameBtn);

	m_pPartnerSocet->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerSocet);
	m_pPartnerSocetClose->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerSocetClose);
	m_pPartnerSocetSelect->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerSocetSelect);

	m_pPartnerImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerImage);

	m_pPartnerBtnCancel->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerBtnCancel);
	m_pPartnerBtnOK->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerBtnOK);
	
	
	m_pPartnerName->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerName);
	m_pPartnerLv->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerLv);
	m_pPartnerType->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerType);
	m_pStamina->DeleteDeviceObjects();
	SAFE_DELETE(m_pStamina);
	m_pPartnerLvBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerLvBar);
	m_pPartnerStaminaBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerStaminaBar);
	m_pPartnerGiveExp->DeleteDeviceObjects();
	SAFE_DELETE(m_pPartnerGiveExp);
	int i;
	for(i=0; i<2; i++)
	{
		m_pPartnerImageLvBar[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pPartnerImageLvBar[i]);
		m_pPartnerImageStaminaBar[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pPartnerImageStaminaBar[i]);
	}
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pFontName->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontName );
	m_pFontLevel->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontLevel );
	m_pFontGuild->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontGuild );
	m_pFontGeneral->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontGeneral );
	m_pFontPropensity->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontPropensity );
	m_pFontAutoStat->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontAutoStat );
	m_pFontStatDec->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontStatDec );
	m_pQuestListScrollBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pQuestListScrollBar );
	m_pQuestDescScrollBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pQuestDescScrollBar );
	m_pQuestSelect->DeleteDeviceObjects();
	SAFE_DELETE(m_pQuestSelect );
	m_pShopSkillScrollBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pShopSkillScrollBar );
	for(i=0 ; i<CHARACTER_INTERFACE_FONT_NUM ; i++)
	{
		m_pFontAmmoWeapon[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontAmmoWeapon[i] );
	}

	for( i=0 ; i<5 ; i++)
	{
		if(m_CharacInfoFont[i])
		{
			m_CharacInfoFont[i]->DeleteDeviceObjects() ;
			SAFE_DELETE(m_CharacInfoFont[i] );
		}
	}
	for(i=0 ; i<7 ; i++)
	{
		if(m_StatInfoFont[i])
		{
			m_StatInfoFont[i]->DeleteDeviceObjects() ;
			SAFE_DELETE(m_StatInfoFont[i] );
		}
	}
	// 2007-05-15 by bhsohn ��� ���� ���� ó��	
	if(m_StatOverInfoFont)
	{
		m_StatOverInfoFont->DeleteDeviceObjects() ;
		SAFE_DELETE(m_StatOverInfoFont );
	}		
	if(m_StatInfoBoldFont)
	{
		m_StatInfoBoldFont->DeleteDeviceObjects() ;
		SAFE_DELETE(m_StatInfoBoldFont );
	}	

//	for(i=0 ; i<3 ; i++)
//	{
//		m_pStat[i]->DeleteDeviceObjects() ;
//		SAFE_DELETE(m_pStat[i] );
//	}
	for(i=0;i<C_QUEST_LIST_NUM;i++)
	{
		m_pFontQuestList[i]->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontQuestList[i] );
//		m_pFontQuestState[i]->DeleteDeviceObjects() ;
//		SAFE_DELETE(m_pFontQuestState[i] );
	}
	for(i=0;i<C_QUEST_DESC_NUM;i++)
	{
		m_pFontQuestDesc[i]->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontQuestDesc[i] );
	}
	for(i=0; i<MAX_CHAR_UTC_SLOT_NUMBER; i++)
	{
		m_pFontItemNum[i]->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pFontItemNum[i] );
	}
	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	if(m_pOpenBtn)
	{		
		m_pOpenBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pOpenBtn);
	}	
	if(m_pCloseBtn)
	{
		m_pCloseBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pCloseBtn);
	}
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO;nCnt++)
	{
		m_pBonusStatBtn[nCnt]->DeleteDeviceObjects();
		SAFE_DELETE(m_pBonusStatBtn[nCnt]);
	}	
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	if(m_pNickNameBtn)
	{
		m_pNickNameBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pNickNameBtn);
	}
	if(m_pFontNickName)
	{
		m_pFontNickName->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontNickName);
	}
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	m_bInvalidated = FALSE;

	return S_OK ;
}


HRESULT CINFCharacterInfoExtend::InvalidateDeviceObjects()
{
	FLOG( "CINFCharacterInfoExtend::InvalidateDeviceObjects()" );
	//m_pAmmo->InvalidateDeviceObjects();
	//m_pStatImage->InvalidateDeviceObjects();
	
	m_pInfo->InvalidateDeviceObjects();
	m_pInoBk->InvalidateDeviceObjects();
	//m_pId->InvalidateDeviceObjects();
	m_pUtc->InvalidateDeviceObjects();
	m_pUtcScr->InvalidateDeviceObjects();
	m_pSkillShopBack->InvalidateDeviceObjects();
//	m_pImgArenaTab->InvalidateDeviceObjects();
//	m_pScrollBar->InvalidateDeviceObjects();
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pPartnerInfoBk->InvalidateDeviceObjects();
	m_pPartnerName->InvalidateDeviceObjects();
	m_pChangeNameBtn->InvalidateDeviceObjects();
	m_pPartnerImage->InvalidateDeviceObjects();

	m_pPartnerBtnCancel->InvalidateDeviceObjects();
	m_pPartnerBtnOK->InvalidateDeviceObjects();
	m_pExpScroll->InvalidateDeviceObjects();
	m_pPartnerLv->InvalidateDeviceObjects();
	m_pPartnerType->InvalidateDeviceObjects();
	m_pStamina->InvalidateDeviceObjects();
	m_pPartnerLvBar->InvalidateDeviceObjects();
	m_pPartnerStaminaBar->InvalidateDeviceObjects();
	m_pPartnerGiveExp->InvalidateDeviceObjects();

	m_pPartnerSocet->InvalidateDeviceObjects();
	m_pPartnerSocetClose->InvalidateDeviceObjects();
	m_pPartnerSocetSelect->InvalidateDeviceObjects();
	int i;
	for(i=0; i< 2; i++)
	{
		m_pPartnerImageLvBar[i]->InvalidateDeviceObjects();
		m_pPartnerImageStaminaBar[i]->InvalidateDeviceObjects();
	}	
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	m_pQuestListScrollBar->InvalidateDeviceObjects();
	m_pQuestDescScrollBar->InvalidateDeviceObjects();
	m_pQuestSelect->InvalidateDeviceObjects();
	m_pShopSkillScrollBar->InvalidateDeviceObjects();

	for(i=0 ; i<5 ; i++)
	{
		m_CharacInfoFont[i]->InvalidateDeviceObjects() ;
	}
	for(i=0 ; i<7 ; i++)
	{
		m_StatInfoFont[i]->InvalidateDeviceObjects() ;
	}
	// 2007-05-15 by bhsohn ��� ���� ���� ó��		
	m_StatOverInfoFont->InvalidateDeviceObjects() ;
	m_StatInfoBoldFont->InvalidateDeviceObjects() ;

//	for(i=0 ; i<3 ; i++)
//	{
//		m_pStat[i]->InvalidateDeviceObjects() ;
//	}

	m_pFontName->InvalidateDeviceObjects();
	m_pFontLevel->InvalidateDeviceObjects();
	m_pFontGuild->InvalidateDeviceObjects();
	m_pFontGeneral->InvalidateDeviceObjects();
	m_pFontPropensity->InvalidateDeviceObjects();
	m_pFontAutoStat->InvalidateDeviceObjects();
	m_pFontStatDec->InvalidateDeviceObjects();
	for(i=0;i<C_QUEST_LIST_NUM;i++)
	{
		m_pFontQuestList[i]->InvalidateDeviceObjects() ;
//		m_pFontQuestState[i]->InvalidateDeviceObjects() ;
	}
	for(i=0;i<C_QUEST_DESC_NUM;i++)
	{
		m_pFontQuestDesc[i]->InvalidateDeviceObjects() ;
	}
	for(i=0 ; i<CHARACTER_INTERFACE_FONT_NUM ; i++)
	{
		m_pFontAmmoWeapon[i]->InvalidateDeviceObjects();
	}
	for(i=0; i<MAX_CHAR_UTC_SLOT_NUMBER; i++)
	{
		m_pFontItemNum[i]->InvalidateDeviceObjects() ;
	}
	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	if(m_pOpenBtn)
	{		
		m_pOpenBtn->InvalidateDeviceObjects();		
	}
	if(m_pCloseBtn)
	{
		m_pCloseBtn->InvalidateDeviceObjects();				
	}
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO;nCnt++)
	{
		m_pBonusStatBtn[nCnt]->InvalidateDeviceObjects();		
	}	
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	if(m_pNickNameBtn)
	{
		m_pNickNameBtn->InvalidateDeviceObjects();		
	}
	if(m_pFontNickName)
	{
		m_pFontNickName->InvalidateDeviceObjects();		
	}
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	
	m_bRestored = FALSE;
	m_bInvalidated = TRUE;

	return S_OK ;
}


void CINFCharacterInfoExtend::Tick()
{
	FLOG( "CINFCharacterInfoExtend::Tick()" );

	if(!IsShowWnd())
	{
		return;
	}
//	if(m_nCharacterInfoType == CHARACTER_QUEST)
//	{
//		if(m_pQuestListScrollBar)
//		{
//			m_pQuestListScrollBar->SetNumberOfData( g_pQuestData->GetProgressQuestNum() + g_pQuestData->m_vecQuest.size());
//			m_pQuestListScrollBar->SetScrollLinePos( QUEST_LIST_SCROLL_START_X, g_pGameMain->m_nRightWindowY+QUEST_LIST_SCROLL_START_Y);
//			m_pQuestListScrollBar->SetWheelRect(C_QUEST_START_X, 
//				g_pGameMain->m_nRightWindowY+C_QUEST_START_Y,
//				C_QUEST_START_X+C_QUEST_SIZE_X,
//				g_pGameMain->m_nRightWindowY+C_QUEST_START_Y+C_QUEST_SIZE_Y);
//			if(m_nOldQuestSelectDataIndex != m_pQuestListScrollBar->GetCurrentSelectDataIndex())
//			{
//				m_nOldQuestSelectDataIndex = m_pQuestListScrollBar->GetCurrentSelectDataIndex();
//				SetQuestDesc(m_nOldQuestSelectDataIndex);
//			}
//		}
//		if(m_pQuestDescScrollBar)
//		{
//			//m_pQuestDescScrollBar->SetNumberOfData( m_vecQuestDescription.size() );
//			m_pQuestDescScrollBar->SetScrollLinePos( QUEST_DESC_SCROLL_START_X, g_pGameMain->m_nRightWindowY+QUEST_DESC_SCROLL_START_Y);
//			m_pQuestDescScrollBar->SetWheelRect(C_QUEST_DESC_START_X, 
//				g_pGameMain->m_nRightWindowY+C_QUEST_DESC_START_Y,
//				C_QUEST_DESC_START_X+C_QUEST_DESC_SIZE_X,
//				g_pGameMain->m_nRightWindowY+C_QUEST_DESC_START_Y+C_QUEST_DESC_SIZE_Y);
//		}
//	}

	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	// ���� ������ ����.
	GetStatShowInfo();
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	Patner3D();
	ExpScrollUpdate();
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
}

// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
void CINFCharacterInfoExtend::Patner3D()
{
	// ��Ʈ�� 3D ȭ��
}

void CINFCharacterInfoExtend::PatnerInfo()
{

	// 2010-06-15 by shcho&hslee ��ý��� - �� �������ͽ� â ó��.
	//INVEN_DISPLAY_INFO *pEquipPetInfo = NULL;
	tPET_CURRENTINFO *psPetCurrentInfo = NULL;
	tPET_BASEDATA *psPetBaseData = NULL;
	tPET_LEVEL_DATA *psPetLevelData = NULL;

	GetPtr_AttachmentedPetInfo ( NULL , &psPetCurrentInfo , &psPetBaseData , &psPetLevelData );

	if ( psPetCurrentInfo && psPetBaseData && psPetLevelData )
	{
		// �⺻ ����
		/*
		char * tempName = "�Ƿη�";
		int	   tempLv	= 18;
		int	   tempType = PARTNER_TYPE_ATT;
		int tempMaxStamena = 100000;
		int tempStamena = 6000;
		*/
		
		
		int nWindowPosX = m_ptBkPos.x;
		int nWindowPosY = m_ptBkPos.y;

		char szTemp[256] = {0, };

		// �̸�
		//strcpy(szTemp, tempName);
		strcpy ( szTemp , psPetCurrentInfo->szPetName );
		m_pPartnerName->DrawText(nWindowPosX + PARTNER_INFO_X, nWindowPosY + PARTNER_INFO_Y, GUI_FONT_COLOR, szTemp, 0L);
		// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
		//Ÿ��
		memset ( szTemp , 0x00 , sizeof( szTemp ) );
		strcpy ( szTemp , g_pInterface->GetString_PetType ( psPetBaseData->PetKind ) );
		m_pPartnerType->DrawText(nWindowPosX + PARTNER_INFO_X, nWindowPosY + PARTNER_INFO_Y + PARTNER_INFO_Y_GAP, GUI_FONT_COLOR, szTemp, 0L);


		//����
		memset(szTemp, 0x00, sizeof(szTemp));
		//wsprintf( szTemp, STRMSG_C_100608_0401, tempLv);
		wsprintf ( szTemp , STRMSG_C_100608_0401 , psPetCurrentInfo->PetLevel );
		m_pPartnerLv->DrawText(nWindowPosX + PARTNER_INFO_X, nWindowPosY + PARTNER_INFO_Y + PARTNER_INFO_Y_GAP * 2, GUI_FONT_COLOR, szTemp, 0L);

		//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

		/*
		switch(tempType)
		{

		case PARTNER_TYPE_ATT:
			{
			
				strcpy(szTemp,STRMSG_C_100608_0405);
			}
			break;
		case PARTNER_TYPE_DFN:
			{
				strcpy(szTemp,STRMSG_C_100608_0404);
			}
			break;
		case PARTNER_TYPE_BUF:
			{
				strcpy(buf,STRMSG_C_100608_0406);
			}
			break;
		case PARTNER_TYPE_STORE:
			{
				strcpy(buf,STRMSG_C_100608_0407);
			}
			break;
		}*/
		
	
		// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
		//m_pPartnerType->DrawText(nWindowPosX + PARTNER_INFO_X, nWindowPosY + PARTNER_INFO_Y + PARTNER_INFO_Y_GAP * 2, GUI_FONT_COLOR, szTemp, 0L);
		//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
 
		//���׹̳�
		memset(szTemp, 0x00, sizeof(szTemp));
		//wsprintf( szTemp, STRMSG_C_100608_0403, tempStamena,tempMaxStamena);
		wsprintf ( szTemp , STRMSG_C_100608_0403 , (DWORD)psPetCurrentInfo->Stamina , (DWORD)psPetLevelData->Stamina );
		m_pStamina->DrawText(nWindowPosX + PARTNER_INFO_X, nWindowPosY + PARTNER_INFO_Y + PARTNER_INFO_Y_GAP * 3, GUI_FONT_COLOR, szTemp, 0L);
	}

	if ( !psPetCurrentInfo )
	{
		m_pChangeNameBtn->SetBtnState ( BTN_STATUS_DISABLE );
	}
	else 
	{
		if ( m_pChangeNameBtn->GetBtnState() == BTN_STATUS_DISABLE )
			m_pChangeNameBtn->SetBtnState ( BTN_STATUS_UP );
	}

	// �̸� ���� ��ư 
	m_pChangeNameBtn->SetBtnPosition( m_ptBkPos.x + PARTNER_NAMECHANGE_BTN_X, m_ptBkPos.y + PARTNER_NAMECHANGE_BTN_Y );
	m_pChangeNameBtn->Render();

	m_pPartnerImage->Move(m_ptBkPos.x + PARTNER_IMAGE_POS_X , m_ptBkPos.y + PARTNER_IMAGE_POS_Y);
	m_pPartnerImage->Render();


	//2011. 03. 08 by jhAhn ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â(UI����)
	for (int i = 0 ; i < 2 ; i++)
	{
		for (int j = 0 ; j < 3 ; j++)
		{

			m_pPartnerSocet->Move(
				m_ptBkPos.x + PARTNER_SOCKET_POS_X + (m_pPartnerSocet->GetImgSize().x + PARTNER_SOCKET_GAP) * j ,
				m_ptBkPos.y + PARTNER_SOCKET_POS_Y + (m_pPartnerSocet->GetImgSize().y + PARTNER_SOCKET_GAP) * i ); 
			m_pPartnerSocet->Render();

		}
	}
	

	m_pPartnerBtnOK->SetBtnPosition(m_ptBkPos.x + PARTNER_OKCANCEL_BTN_X  , m_ptBkPos.y + PARTNER_OKCANCEL_BTN_Y   ); 
	m_pPartnerBtnOK->Render();

	m_pPartnerBtnCancel->SetBtnPosition(m_ptBkPos.x + PARTNER_OKCANCEL_BTN_X + m_pPartnerBtnCancel->GetImgSize().x + 7 , m_ptBkPos.y + PARTNER_OKCANCEL_BTN_Y   );
	m_pPartnerBtnCancel->Render();
	//end 2011. 03. 08 by jhAhn ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â(UI����)

	


}

/****************************************************
**
**	�� ���� ���� ���.
**
**	Create Info :	??. ??. ??.
**	
*****************************************************/
void CINFCharacterInfoExtend::PatnerDtail()
{

	// 2010-06-15 by shcho&hslee ��ý��� - ���¹̳�, ����ġ �� ���� ó�� ����.
	tPET_CURRENTINFO *psPetCurInfo = NULL;
	tPET_LEVEL_DATA *psPetLevelData = NULL;

	GetPtr_AttachmentedPetInfo ( NULL , &psPetCurInfo , NULL , &psPetLevelData );

	if ( !psPetCurInfo || !psPetLevelData )
		return;

	tPET_LEVEL_DATA *psPetLevelDataPrev = g_pDatabase->GetPtr_PetLevelData ( psPetCurInfo->PetIndex , psPetCurInfo->PetLevel-1 );

	// ���� ����
	/*
	LevelExpBar();
	StaminaBar();
	*/

	Experience_t ExpNow = 0; 
	Experience_t ExpMax = 0;

	if ( psPetLevelDataPrev )
	{
		ExpNow = psPetCurInfo->PetExp - psPetLevelDataPrev->NeedExp;
		ExpMax = psPetLevelData->NeedExp - psPetLevelDataPrev->NeedExp;
	}
	else
	{
		ExpNow = psPetCurInfo->PetExp;
		ExpMax = psPetLevelData->NeedExp;
	}

	LevelExpBar( ExpNow , ExpMax );

//	StaminaBar( psPetCurInfo->Stamina , psPetLevelData->Stamina );

	m_pExpScroll->SetOnlyMaxItem( PARTNER_EXP_SCROLL, TRUE );
	m_pExpScroll->Render();

	char szTemp[256] = {0, };
	/*
	char buf[256];
	int tempMaxStamena = 100000;
	int tempStamena = 6000;
	int tempLv = 18;
	float tempMaxExp = 2000.0f;
	float temExp = 240.0f;
	*/
	float fExpPer = .0f;

	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;

	// Level & Exp(Per).
	SIZE szSize = {0,0};
	//memset(buf, 0x00, sizeof(buf));

	if ( psPetLevelData->NeedExp > .0f )
		fExpPer = ((float)ExpNow / (float)ExpMax ) * 100.0f;
	
	//sprintf( buf, STRMSG_C_100608_0402, tempLv,(float(temExp / tempMaxExp) * 100));
	sprintf ( szTemp , STRMSG_C_100608_0402 , psPetCurInfo->PetLevel , fExpPer );
	szSize = m_pFontGeneral->GetStringSize(szTemp);
	m_pPartnerLvBar->DrawText(nWindowPosX + PARTNER_DTAIL_INFO_X - szSize.cx, nWindowPosY + PARTNER_DTAIL_INFO_Y + 40, GUI_FONT_COLOR, szTemp, 0L);
	
	// Stamina
	/*
	memset(buf, 0x00, sizeof(buf));
	sprintf( buf, STRMSG_C_100608_0403, (int)tempStamena,(int)tempMaxStamena);
	*/
//	sprintf ( szTemp , STRMSG_C_100608_0403 , (DWORD)psPetCurInfo->Stamina , (DWORD)psPetLevelData->Stamina );
//	szSize = m_pFontGeneral->GetStringSize(szTemp);
//	m_pPartnerStaminaBar->DrawText(nWindowPosX + PARTNER_DTAIL_INFO_X - szSize.cx, nWindowPosY + PARTNER_DTAIL_INFO_Y + PARTNER_DTAIL_INFO_Y_GAP, GUI_FONT_COLOR, szTemp, 0L);

}

void CINFCharacterInfoExtend::SetBar(CINFImage* Image1, CINFImage* Image2, float MaxValue, float Value, float x, float y)
{
	// 2010-06-15 by shcho&hslee ��ý��� - ���� ó�� MaxValue == 0.0f ����.
	if ( MaxValue <= .0f )
		return;

	RECT ImageRect1, ImageRect2;
	POINT ImageSize1, ImageSize2;
	int fTemp = 0.0f;
	float fValue = (Value / MaxValue) * 100.0f;
	
	ImageSize1 = Image1->GetImgSize();
	ImageSize2 = Image2->GetImgSize();

	if(100.0f > fValue && ImageSize2.x * 2 > ((float)ImageSize1.x * fValue / 100.0f))
	{
		fTemp = (ImageSize2.x * 2 - ((float)ImageSize1.x * (fValue / 100.0f))) / 2;
		ImageRect1.left = 0; 
		ImageRect1.top = 0;
		ImageRect1.right = ImageSize2.x - fTemp;
		ImageRect1.bottom = ImageSize1.y;

		ImageRect2.left = fTemp;
		ImageRect2.top = 0;
		ImageRect2.right = ImageSize2.x;
		ImageRect2.bottom = ImageSize2.y;
	}
	else
	{
		ImageSize1.x = ((float)ImageSize1.x * (fValue / 100.0f));
		ImageRect1.left = 0;
		ImageRect1.top = 0;
		ImageRect1.right = ImageSize1.x - ImageSize2.x;
		ImageRect1.bottom = ImageSize1.y;
		
		ImageRect2.left = 0;
		ImageRect2.top = 0;
		ImageRect2.right = ImageSize2.x;
		ImageRect2.bottom = ImageSize2.y;
	}

	Image1->SetRect(ImageRect1.left, ImageRect1.top, ImageRect1.right, ImageRect1.bottom);

	ImageRect2.left = fTemp;
	ImageRect2.top = 0;
	ImageRect2.right = ImageSize2.x;
	ImageRect2.bottom = ImageSize2.y;
		
	Image2->SetRect(ImageRect2.left, ImageRect2.top, ImageRect2.right, ImageRect2.bottom);

	Image1->Move(x , y);
	Image2->Move(x + ImageRect1.right, y);
}


// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ���� ������ ���� �Ѱ��ֱ�.
void CINFCharacterInfoExtend :: GetPtr_AttachmentedPetInfo ( INVEN_DISPLAY_INFO **o_ppInvenDisplayInfo , tPET_CURRENTINFO **o_ppPetCurInfo , tPET_BASEDATA **o_ppPetBaseData , tPET_LEVEL_DATA **o_ppPetLevelData )
{

	INVEN_DISPLAY_INFO *pInvenDisplayInfo = g_pGameMain->m_pInven->rtnPtr_AttachmentItemInfo ( POS_PET );

	if ( !pInvenDisplayInfo )
		return;

	if ( NULL != o_ppInvenDisplayInfo )
		*o_ppInvenDisplayInfo = pInvenDisplayInfo;

	tPET_CURRENTINFO *pPetCurrentInfo = g_pShuttleChild->GetPetManager()->GetPtr_PetCurrentData ( pInvenDisplayInfo->pItem->UniqueNumber );

	if ( !pPetCurrentInfo )
		return;

	if ( NULL != o_ppPetCurInfo )
		*o_ppPetCurInfo = pPetCurrentInfo;

	tPET_BASE_ALL_DATA *pPetAllData = g_pDatabase->GetPtr_PetAllDataByIndex ( pPetCurrentInfo->PetIndex );

	if ( !pPetAllData )
		return;

	if ( NULL != o_ppPetBaseData )
		*o_ppPetBaseData = &pPetAllData->BaseData;

	if ( NULL != o_ppPetLevelData )
		*o_ppPetLevelData = pPetAllData->rtn_LevelData ( pPetCurrentInfo->PetLevel );

}


/****************************************************************************************
**
**	�� ���¹̳� �� ���.
**
**	Create Info : ??. ??. ??.
**
**	Update Info : 2010. 07. 09. by hsLee. ���¹̳����� ���ڷ� �ް� ����.
**
*****************************************************************************************/
void CINFCharacterInfoExtend::StaminaBar( const int a_StaminaNow , const int a_StaminaMax )
{
	// 2010-06-15 by shcho&hslee ��ý��� - ���¹̳��� ��� ����.
	/*
	int tempMaxStamena = 100000;
	int tempStamena = 6000;

	SetBar(m_pPartnerImageStaminaBar[0], m_pPartnerImageStaminaBar[1], tempMaxStamena, tempStamena, m_ptBkPos.x + PARTNER_STAMENA_POS_X, m_ptBkPos.y + PARTNER_STAMENA_POS_Y);
	*/
	SetBar(m_pPartnerImageStaminaBar[0], m_pPartnerImageStaminaBar[1], (float)a_StaminaMax, (float)a_StaminaNow, m_ptBkPos.x + PARTNER_STAMENA_POS_X, m_ptBkPos.y + PARTNER_STAMENA_POS_Y);
	

	m_pPartnerImageStaminaBar[0]->Render();	
	m_pPartnerImageStaminaBar[1]->Render();
}


/****************************************************************************************
**
**	�� ����ġ �� ���.
**
**	Create Info : ??. ??. ??.
**
**	Update Info : 2010. 07. 09. by hsLee. ����ġ���� ���ڷ� �ް� ����.
**
*****************************************************************************************/
void CINFCharacterInfoExtend::LevelExpBar( const Experience_t a_ExpNow , const Experience_t a_ExpMax )
{
	// 2010-06-15 by shcho&hslee ��ý��� - ����ġ�� ��� ����.
	/*
	float tempMaxExp = 2000.0f;
	float temExp = 240.0f;

	SetBar(m_pPartnerImageLvBar[0], m_pPartnerImageLvBar[1], tempMaxExp, temExp, m_ptBkPos.x + PARTNER_EXP_POS_X, m_ptBkPos.y + PARTNER_EXP_POS_Y);
	*/
	SetBar(m_pPartnerImageLvBar[0], m_pPartnerImageLvBar[1], (float)a_ExpMax, (float)a_ExpNow, m_ptBkPos.x + PARTNER_EXP_POS_X, m_ptBkPos.y + PARTNER_EXP_POS_Y);
	

	m_pPartnerImageLvBar[0]->Render();
	m_pPartnerImageLvBar[1]->Render();
}

void CINFCharacterInfoExtend::ExpScrollUpdate()
{
	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;
	
	// end 2007-05-15 by bhsohn ��� ���� ���� ó��
	m_pExpScroll->SetPosition( nWindowPosX + PARTNER_EXP_SCROLL_POS_X, nWindowPosY + PARTNER_EXP_SCROLL_POS_Y, PARTNER_EXP_SCROLL_POS_W, PARTNER_EXP_SCROLL_POS_H);
	RECT rect = {
		nWindowPosX + PARTNER_EXP_SCROLL_POS_X,
			nWindowPosY + PARTNER_EXP_SCROLL_POS_Y,
			nWindowPosX + PARTNER_EXP_SCROLL_POS_X + PARTNER_EXP_SCROLL_POS_W,
			nWindowPosY + PARTNER_EXP_SCROLL_POS_Y + 10
	};
	m_pExpScroll->SetMouseBallRect( rect );
}
//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCharacterInfoExtend::RenderSkillInShop()
/// \brief		�������� ���� â�� �� ��ų ������
/// \author		dhkwon
/// \date		2004-10-18 ~ 2004-10-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::RenderSkillInShop()
{
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//	if(m_pSkillShopBack )
//	{
//		m_pSkillShopBack->Move(SHOP_SKILL_BACK_START_X,SHOP_SKILL_BACK_START_Y);
//		m_pSkillShopBack->Render() ;
//	}
	// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	CINFIcon* pIcon = ((CINFGameMain*)m_pParent)->m_pIcon;
	for(int i=0;i<CHAR_UTC_TYPE_NUMBER;i++)
	{
		for(int j=0;j<CHAR_UTC_SLOT_NUMBER;j++)
		{
			if(m_pSkillShopSkillDisplayInfo[i][j].pItem)
			{
				// 2005-11-28 by ispark, SourceIndex�� ����, ��ų�� SKILL_BASE_NUM���� �Ѵ�.
				char buf[64];
				wsprintf(buf, "%08d", SKILL_BASE_NUM(m_pSkillShopSkillDisplayInfo[i][j].pItem->ItemInfo->SourceIndex));
				pIcon->SetIcon(buf,
//					SHOP_SKILL_START_X+CHAR_UTC_INTERVAL_X*i+1, 
//					SHOP_SKILL_START_Y+CHAR_UTC_INTERVAL_Y*j+1, 
					SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+1, 
					SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j+1, 
					1.0f);
				pIcon->Render();
				
				if(m_pSkillShopSkillDisplayInfo[i][j].pItem->ItemInfo->SkillLevel > 0)
				{
					char buf[128];

					// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//					wsprintf(buf, "%d",m_pUTCDisplayInfo[i][j].pItem->ItemInfo->SkillLevel);
//					m_pFontItemNum[i]->DrawText(SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+21,
//										SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j+14,
//						GUI_FONT_COLOR_Y,buf, 0L);
					
					{
						// ��ų����
						//"LV%d"
						wsprintf(buf, STRMSG_C_080922_0202, m_pSkillShopSkillDisplayInfo[i][j].pItem->ItemInfo->SkillLevel);
						m_pFontItemNum[i]->DrawText(SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+21+20,
							SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j,
							GUI_FONT_COLOR,buf, 0L);
					}
					{
						// ��ų�̸�
						strncpy(buf, m_pSkillShopSkillDisplayInfo[i][j].pItem->ItemInfo->ItemName, SIZE_MAX_ITEM_NAME);
						
						// 2008-10-23 by bhsohn ��ų�� �Ѿ�� ���� ó��
						g_pGameMain->TextReduce(m_pFontItemNum[i], 73, buf);

						m_pFontItemNum[i]->DrawText(SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+21+20,
							SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j+14,
							GUI_FONT_COLOR,buf, 0L);
					}

					// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��

//#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
//					wsprintf(buf, "%d",m_pUTCDisplayInfo[i][j].pItem->ItemInfo->SkillLevel);
//					m_pFontItemNum[i]->DrawText(SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+21,
//										SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j+14,
//						GUI_FONT_COLOR_Y,buf, 0L);
//#else
//					wsprintf(buf, "%d",m_pUTCDisplayInfo[i][j].pItem->ItemInfo->SkillLevel);
//					m_pFontItemNum[i]->DrawText(SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+21,SHOP_SKILL_START_Y+CHAR_UTC_INTERVAL_Y*j+14,
//						GUI_FONT_COLOR_Y,buf, 0L);

//					wsprintf(buf, "%4.d",m_pUTCDisplayInfo[i][j].pItem->ItemInfo->SkillLevel);
//					m_pFontItemNum[i]->DrawText(SHOP_SKILL_START_X+CHAR_UTC_INTERVAL_X*i+2,SHOP_SKILL_START_Y+CHAR_UTC_INTERVAL_Y*j+15,
//						GUI_FONT_COLOR_Y,buf, 0L);
//#endif
				}
			}
		}
	}
	if(m_pSelectIcon)
	{
		POINT ptCursor;
		GetCursorPos( &ptCursor );
		ScreenToClient( g_pD3dApp->GetHwnd(), &ptCursor );
		CheckMouseReverse(&ptCursor);

		m_pSelectIcon->Move(ptCursor.x-m_nRenderMoveIconIntervalWidth, ptCursor.y-m_nRenderMoveIconIntervalHeight);
		m_pSelectIcon->Render();

	}
	m_pShopSkillScrollBar->Render();
}

void CINFCharacterInfoExtend::Render()
{
	FLOG( "CINFCharacterInfoExtend::Render()" );

	if(!IsShowWnd())
	{
		return;
	}

	// �������� ����
	RenderCommandInfo();
	
	switch(m_nCharacterInfoType)
	{
	case CHARACTER_INFO:
		{
			RenderCharacterInfo();			
		}
		break;

	case CHARACTER_AMMO:
		{
		}
		break;
	case CHARACTER_UTC:
		{
			RenderSkillInfo();
		}		
		break;

	case CHARACTER_ARENA:
		{
			
		}
		break;
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	case CHARACTER_PARTNER:
		{
			RenderPartnerInfo();
		}
		break;
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	}
}

void CINFCharacterInfoExtend::SetAllUTCInfo()
{
	FLOG( "CINFCharacterInfoExtend::SetAllUTCInfo()" );

	m_pShopSkillScrollBar->SetNumberOfData( GetUtcMaxScrollNumber() );
	char strIconName[64];
	
	memset(m_pSkillShopSkillDisplayInfo, 0x00, sizeof(INVEN_DISPLAY_INFO)*CHAR_UTC_TYPE_NUMBER*MAX_CHAR_UTC_SLOT_NUMBER);
	memset(m_pCharacterSkillDisplayInfo, 0x00, sizeof(INVEN_DISPLAY_INFO)*CHAR_UTC_TYPE_NUMBER*MAX_CHAR_UTC_SLOT_NUMBER);
	

//	map<int, ITEM_SKILL*>::iterator itSkill = g_pShuttleChild->m_pSkill->m_mapEnableSkill.begin();
	map<int, CSkillInfo*>::iterator itSkillinfo = g_pShuttleChild->m_pSkill->m_mapSkill.begin();
	while(itSkillinfo != g_pShuttleChild->m_pSkill->m_mapSkill.end() )
	{
		CSkillInfo* pSkillInfo = itSkillinfo->second;
		int nTemp = pSkillInfo->ItemNum / 1000;
		int nWindowNum = (pSkillInfo->ItemNum  % nTemp) / 10 -1;
		int nSkillType = pSkillInfo->ItemNum /1000 - (pSkillInfo->ItemNum /10000)*10;

		// ��ų���� ���� ����
		if(pSkillInfo->ItemInfo && nWindowNum >= m_nCurrentUTCScroll && nWindowNum < m_nCurrentUTCScroll+CHAR_UTC_SLOT_NUMBER)
		{
//			wsprintf(strIconName,"%08d",SKILL_BASE_NUM(pSkillInfo->ItemNum));	// 2005-08-23 by ispark
			wsprintf(strIconName,"%08d",SKILL_BASE_NUM(pSkillInfo->ItemInfo->SourceIndex));
			strcpy(m_pSkillShopSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].IconName, strIconName);
			if(pSkillInfo)
			{
				strcpy(m_pSkillShopSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].Name, pSkillInfo->ItemInfo->ItemName);
			}
			else
			{
				memset(m_pSkillShopSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].Name,0x00, sizeof(m_pSkillShopSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].Name));
			}
			m_pSkillShopSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].pItem = pSkillInfo;
		}
		// ĳ������â 
		if(pSkillInfo->ItemInfo && nWindowNum >= m_nCurrentUTCScroll && nWindowNum < m_nCurrentUTCScroll+MAX_CHAR_UTC_SLOT_NUMBER)
		{
//			wsprintf(strIconName,"%08d",SKILL_BASE_NUM(pSkillInfo->ItemNum));	// 2005-08-23 by ispark
			wsprintf(strIconName,"%08d",SKILL_BASE_NUM(pSkillInfo->ItemInfo->SourceIndex));
			strcpy(m_pCharacterSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].IconName, strIconName);
			if(pSkillInfo)
			{
				strcpy(m_pCharacterSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].Name, pSkillInfo->ItemInfo->ItemName);
			}
			else
			{
				memset(m_pCharacterSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].Name,0x00, sizeof(m_pCharacterSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].Name));
			}
			m_pCharacterSkillDisplayInfo[nSkillType][nWindowNum-m_nCurrentUTCScroll].pItem = pSkillInfo;
		}		
		itSkillinfo++;
	}

}

int CINFCharacterInfoExtend::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFCharacterInfoExtend::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	if(!IsShowWnd())
	{
		return INF_MSGPROC_NORMAL;
	}

	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
//			POINT pt = MAKEPOINT(lParam);
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			m_pCloseBtn->OnMouseMove(pt);
			m_pOpenBtn->OnMouseMove(pt);	
			// 2009-02-13 by bhsohn ���� ��ŷ �ý���
			if(m_pNickNameBtn)
			{
				m_pNickNameBtn->OnMouseMove(pt);
			}
			// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

			if(m_bMove)
			{
				m_ptBkPos.x = pt.x - m_ptCommOpMouse.x;
				m_ptBkPos.y = pt.y - m_ptCommOpMouse.y;				
				// UI���� ���� 
				UpdateBtnPos();
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
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;

			{
				if(TRUE == m_pCloseBtn->OnLButtonDown(pt))
				{					
					return  INF_MSGPROC_BREAK;
				}		
			}
			{
				if(TRUE == m_pOpenBtn->OnLButtonDown(pt))
				{					
					return  INF_MSGPROC_BREAK;
				}		
			}
			// 2009-02-13 by bhsohn ���� ��ŷ �ý���
			if(m_pNickNameBtn)
			{
				
				if(TRUE == m_pNickNameBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}
			}
			// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

			if(IsMouseCaps(pt))
			{
				m_ptCommOpMouse.x = pt.x - m_ptBkPos.x;
				m_ptCommOpMouse.y = pt.y - m_ptBkPos.y;
				m_bMove = TRUE;
				g_pInterface->SetWindowOrder(WNDCharacterWnd);
				return INF_MSGPROC_BREAK;
			}			

			if(pt.y>nWindowPosY + INFO_TAB_POX_Y && pt.y<nWindowPosY + INFO_TAB_POX_Y + INFO_TAB_POX_H)
			{
				if(pt.x>=nWindowPosX+INFO_TAB_POX_X &&
				   pt.x<nWindowPosX+INFO_TAB_POX_X + INFO_TAB_POX_W)
				{
					m_nCharacterInfoType = CHARACTER_INFO;
				}
				else if(pt.x>nWindowPosX+INFO_TAB_POX_X + INFO_TAB_POX_W&&
				   pt.x<nWindowPosX+INFO_TAB_POX_X + 2*INFO_TAB_POX_W)
				{
					m_nCharacterInfoType = CHARACTER_UTC;							
					
					int nTemp = m_nCurrentUTCScroll;
					// ��ũ�� �ʱ�ȭ
					m_nCurrentUTCScroll = 0;
					if(m_nCurrentUTCScroll>GetUtcMaxScrollNumber())
					{
						m_nCurrentUTCScroll = GetUtcMaxScrollNumber();
					}				
					
					if(nTemp != m_nCurrentUTCScroll)
					{
						SetAllUTCInfo();
					}
				}
				else if(pt.x>nWindowPosX+INFO_TAB_POX_X + INFO_TAB_POX_W&&
					pt.x<nWindowPosX+INFO_TAB_POX_X + 3*INFO_TAB_POX_W)
				{
#ifdef SC_GROWING_PARTNER_HSKIM_JHAHN
					m_nCharacterInfoType = CHARACTER_PARTNER;
#endif // SC_GROWING_PARTNER_HSKIM_JHAHN
				}				

			}

			// 2005-08-05 by ispark
			// AMMO â�ȿ� ���콺 Ŭ���� ��ȿ
			POINT ptBkSize = m_pInoBk->GetImgSize();
			if(pt.y>nWindowPosY &&
				pt.y<nWindowPosY+ptBkSize.y&&
				pt.x>nWindowPosX &&
				pt.x<nWindowPosX + ptBkSize.x)
			{
				g_pInterface->SetWindowOrder(WNDCharacterWnd);				
			}		
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			{
				if(TRUE == m_pOpenBtn->OnLButtonUp(pt))
				{			
					// ��ư���� ���콺�� �ִ�.					
					g_pGameMain->m_pCommunity->OnPopupUserOpenSetup(TRUE);
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
					return  INF_MSGPROC_BREAK;				
				}
			}

//			POINT pt = MAKEPOINT(lParam);
			{				
				if(TRUE == m_pCloseBtn->OnLButtonUp(pt))
				{			
					g_pGameMain->RightWindowShow(TRUE, RIGHT_WINDOW_INFO);
					// ��ư���� ���콺�� �ִ�.										
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
					return  INF_MSGPROC_BREAK;				
				}
			}
			// 2009-02-13 by bhsohn ���� ��ŷ �ý���
			if(m_pNickNameBtn)
			{				
				if(TRUE == m_pNickNameBtn->OnLButtonUp(pt))
				{
					OnClickNickNameBtn();
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}
			}
			// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

			if(m_bMove)
			{
				m_bMove = FALSE;
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	}
	switch(m_nCharacterInfoType)
	{
	case CHARACTER_INFO:
		{
			return InfoWndProc( uMsg, wParam, lParam);
		}
		break;
	case CHARACTER_AMMO:
		{
			return AmmoWndProc( uMsg, wParam, lParam);
			
		}
		break;
	case CHARACTER_UTC:
		{
			return UTCWndProc(uMsg, wParam, lParam);
		}
		break;
	case CHARACTER_ARENA:
		{
			return ArenaWndProc(uMsg,wParam,lParam);
		}
		break;
		// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	case CHARACTER_PARTNER:
		{
			return PartnerWndProc(uMsg,wParam,lParam);
		}
		break;
		//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	}
	if(WM_MOUSEMOVE == uMsg)
	{
		int nWindowPosX = m_ptBkPos.x;
		int nWindowPosY = m_ptBkPos.y;

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
		CheckMouseReverse(&pt);
		
		POINT ptBkSize = m_pInoBk->GetImgSize();
		if(pt.y>nWindowPosY &&
			pt.y<nWindowPosY+ptBkSize.y&&
			pt.x>nWindowPosX &&
			pt.x<nWindowPosX + ptBkSize.x)
		{
			return INF_MSGPROC_BREAK;
		}		
	}

	return INF_MSGPROC_NORMAL;
}


int CINFCharacterInfoExtend::GetCharacterQuestCount()
{
	FLOG( "CINFCharacterInfoExtend::GetCharacterQuestCount()" );
	map<int, MEX_QUEST_INFO*>::iterator it = g_pQuestData->m_mapCharacterQuest.begin();
	int count = 0;
	while(it != g_pQuestData->m_mapCharacterQuest.end())
	{
		if(it->second->QuestState == QUEST_STATE_IN_PROGRESS)
		{
			count++;
		}
		it++;
	}
	return count;
}

int CINFCharacterInfoExtend::QuestWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFCharacterInfoExtend::QuestWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	if(m_pQuestListScrollBar)
	{
		if(m_pQuestListScrollBar->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		{
			return INF_MSGPROC_BREAK;
		}
	}
	if(m_pQuestDescScrollBar)
	{
		if(m_pQuestDescScrollBar->WndProc(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
		{
			return INF_MSGPROC_BREAK;
		}
	}
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
//			POINT pt = MAKEPOINT(lParam);
//			if(m_bQuestListLock)
//			{
//				int nMove = pt.y - m_ptMouse.y;
//				int count = GetCharacterQuestCount();
//				if(count > 0 && abs(nMove) > CHAR_QUEST_LIST_SCROLL_BAR_INTERVAL(count))
//				{
//					m_nCurrentQuestListScroll += nMove / CHAR_QUEST_LIST_SCROLL_BAR_INTERVAL(count);
//					if(m_nCurrentQuestListScroll < 0)
//						m_nCurrentQuestListScroll = 0;
//					if(m_nCurrentQuestListScroll > count)
//						m_nCurrentQuestListScroll = count;
//					m_ptMouse = pt;
//				}
//			}
//			if(m_bQuestDescLock)////// �����ؾ� �Ѵ�.
//			{
//				int nMove = pt.y - m_ptMouse.y;
//				int count = 4;// line number
//				if(abs(nMove) > CHAR_QUEST_DESC_SCROLL_BAR_INTERVAL(count))
//				{
//					m_nCurrentQuestDescScroll += nMove / CHAR_QUEST_DESC_SCROLL_BAR_INTERVAL(count);
//					if(m_nCurrentQuestDescScroll < 0)
//						m_nCurrentQuestDescScroll = 0;
//					if(m_nCurrentQuestDescScroll > count)
//						m_nCurrentQuestDescScroll = count;
//					m_ptMouse = pt;
//				}
//			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
//			POINT pt = MAKEPOINT(lParam);
//			int nWindowPosY = g_pGameMain->m_nRightWindowY;
//			int count = GetCharacterQuestCount();
//			if( pt.x > nWindowPosX+CHAR_QUEST_LIST_SCROLL_BAR_START_X &&
//				pt.x < nWindowPosX+CHAR_QUEST_LIST_SCROLL_BAR_START_X+CHAR_SCROLL_BAR_SIZE_X &&
//				pt.y > nWindowPosY+CHAR_QUEST_LIST_SCROLL_BAR_START_Y+CHAR_QUEST_LIST_SCROLL_BAR_INTERVAL(count)*m_nCurrentQuestListScroll &&
//				pt.y < nWindowPosY+CHAR_QUEST_LIST_SCROLL_BAR_START_Y+CHAR_QUEST_LIST_SCROLL_BAR_INTERVAL(count)*m_nCurrentQuestListScroll+CHAR_SCROLL_BAR_SIZE_Y )
//			{
//				m_bQuestListLock = TRUE;
//				m_ptMouse = pt;
//			}
		}
		break;
	case WM_LBUTTONUP:
		{
//			m_bQuestListLock = FALSE;
		}
		break;
//#define CHAR_QUEST_LINE_SIZE_X			169
//#define CHAR_QUEST_LINE_SIZE_Y			16
//#define	CHAR_QUEST_LINE_START_X			19
//#define	CHAR_QUEST_LINE_START_Y			70

	case WM_LBUTTONDBLCLK:
		{
/*			POINT pt = MAKEPOINT(lParam);
			int nWindowPosY = g_pGameMain->m_nRightWindowY;
			if( g_pQuestData->m_mapCharacterQuest.size()>0 && 
				pt.x>nWindowPosX+CHAR_QUEST_LINE_START_X && 
				pt.x<nWindowPosX+CHAR_QUEST_LINE_START_X+CHAR_QUEST_LINE_SIZE_X)
			{
				int line = (pt.y-nWindowPosY-CHAR_QUEST_LINE_START_Y)/CHARACTER_QUEST_INTERVAL;
				if(line >=0 && line < 6 && pt.y>nWindowPosY+CHAR_QUEST_LINE_START_Y)
				{
					map<int, MEX_QUEST_INFO*>::iterator it = g_pQuestData->m_mapCharacterQuest.begin();
					int i = -1;
					while(it != g_pQuestData->m_mapCharacterQuest.end() )
					{
						if(it->second->QuestState == QUEST_STATE_IN_PROGRESS)
						{
							i++;
							if(line == i)
								break;
						}
						it++;
					}
					if(it == g_pQuestData->m_mapCharacterQuest.end() )
						return INF_MSGPROC_NORMAL;
					MEX_QUEST_INFO* pInfo = it->second;
					map<int, CQuest*>::iterator it2 = g_pQuestData->m_mapQuest.find(pInfo->QuestIndex);
					if(it2 != g_pQuestData->m_mapQuest.end())
					{
						if(it2->second->QuestEndType == QUEST_END_TYPE_IMMEDIATE)//Ŭ���� ��� ���� ������
						{
							MSG_FC_QUEST_ACCEPT_QUEST sMsg;
							memset(&sMsg,0x00,sizeof(sMsg));
							char buffer[SIZE_MAX_PACKET];
							sMsg.QuestIndex = pInfo->QuestIndex;
							int nType = T_FC_QUEST_ACCEPT_QUEST;
							memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
							memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
							g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
						}
						else if(it2->second->QuestEndType == QUEST_END_TYPE_REQESTED_BY_CLIENT)
						{// �������� Ŭ���̾�Ʈ ����Ʈ�� �߰� ��ȭ�� �����ش�.
							g_pGameMain->m_pMission->SetQuest(it2->second,pInfo);
						}
					}
				}
			}
*/		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

int CINFCharacterInfoExtend::WndProcSkillInShop(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int bReturn = m_pShopSkillScrollBar->WndProc( uMsg, wParam, lParam );
	if( m_nCurrentUTCScroll != m_pShopSkillScrollBar->GetCurrentScrollIndex())
	{
		m_nCurrentUTCScroll = m_pShopSkillScrollBar->GetCurrentScrollIndex();
		SetAllUTCInfo();
	}
	if( bReturn == INF_MSGPROC_BREAK )
	{
		return INF_MSGPROC_BREAK;
	}

	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		{
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.x>SHOP_SKILL_START_X && 
				pt.x<SHOP_SKILL_START_X+SHOP_SKILL_BACK_SIZE_X &&
				pt.y>SHOP_SKILL_START_Y && 
				pt.y<SHOP_SKILL_START_Y+SHOP_SKILL_BACK_SIZE_Y)
			{
				int i = ( pt.x - SHOP_SKILL_START_X ) / SHOP_SKILL_INTERVAL_X;
				if( i>=0 && 
					i<CHAR_UTC_TYPE_NUMBER &&
					pt.x<SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+CHAR_UTC_ICON_SIZE)
				{
					int j = (pt.y - SHOP_SKILL_START_Y) / SHOP_SKILL_INTERVAL_Y;
					if( j >=0 && 
						j<CHAR_UTC_SLOT_NUMBER &&
						pt.y<SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j+CHAR_UTC_ICON_SIZE &&
						m_pSkillShopSkillDisplayInfo[i][j].pItem)
					{
						((CINFGameMain*)m_pParent)->SetItemInfo(m_pSkillShopSkillDisplayInfo[i][j].pItem->UniqueNumber, 
																m_pSkillShopSkillDisplayInfo[i][j].pItem->ItemNum, pt.x, pt.y);
					}
					else
						((CINFGameMain*)m_pParent)->SetItemInfo(0,0,0,0);
				}
				else
					((CINFGameMain*)m_pParent)->SetItemInfo(0,0,0,0);
			}
//			else
//			{
//				((CINFGameMain*)m_pParent)->SetItemInfo(0,0,0,0);
//			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.x>SHOP_SKILL_START_X && 
				pt.x<SHOP_SKILL_START_X+SHOP_SKILL_BACK_SIZE_X &&
				pt.y>SHOP_SKILL_START_Y && 
				pt.y<SHOP_SKILL_START_Y+SHOP_SKILL_BACK_SIZE_Y)
			{
				int i = ( pt.x - SHOP_SKILL_START_X ) / SHOP_SKILL_INTERVAL_X;
				if( i>=0 && 
					i<CHAR_UTC_TYPE_NUMBER &&
					pt.x<SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i+CHAR_UTC_ICON_SIZE)
				{
					int j = (pt.y - SHOP_SKILL_START_Y) / SHOP_SKILL_INTERVAL_Y;
					if( j >=0 && 
						j<CHAR_UTC_SLOT_NUMBER &&
						pt.y<SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j+CHAR_UTC_ICON_SIZE )
					{

						m_nRenderMoveIconIntervalWidth =  pt.x - (SHOP_SKILL_START_X+SHOP_SKILL_INTERVAL_X*i);
						m_nRenderMoveIconIntervalHeight = pt.y - (SHOP_SKILL_START_Y+SHOP_SKILL_INTERVAL_Y*j);

						if(	m_pSkillShopSkillDisplayInfo[i][j].pItem &&
							m_pSkillShopSkillDisplayInfo[i][j].pItem->ItemInfo->SkillType != SKILLTYPE_PERMANENT)	
						{
							SetSelectUTC( &m_pSkillShopSkillDisplayInfo[i][j] );
						}
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

			if( m_pSelectIcon &&
				m_pSelectSkill &&
				pt.x>SKILL_SHOP_SPI_START_X+1 && 
				pt.x<SKILL_SHOP_SPI_START_X+1+SKILL_DROP_SIZE &&
				pt.y>SKILL_SHOP_SPI_START_Y+1 && 
				pt.y<SKILL_SHOP_SPI_START_Y+1+SKILL_DROP_SIZE)
			{
				if( !((CINFGameMain*)m_pParent)->m_pInfWindow->IsExistMsgBox(_Q_ITEM_DELETE) &&
					!((CINFGameMain*)m_pParent)->m_pInfWindow->IsExistMsgBox(_Q_ITEM_DELETE_NUM))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRERR_C_SKILL_0012,COLOR_SKILL_USE);//"��ų ������ ���� �������� �ʽ��ϴ�."
//					char buf[256];
//					ITEM *pITEM = g_pDatabase->GetServerItemInfo(m_pSelectSkill->ItemNum);
//					if(pITEM)
//					{
//						m_pDeleteSkill = m_pSelectSkill;
//						wsprintf(buf, "��ų %s ��(��)  �����Ͻðڽ��ϱ�?", pITEM->ItemName);
//						g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_ITEM_DELETE_SKILL);
//					}
				}
			}
			SetSelectUTC(NULL);
			((CINFGameMain*)m_pParent)->SetItemInfo(0,0, 0,0);
		}
		break;

	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCharacterInfoExtend::SendDeleteSelectItemSkill()
/// \brief		���� �۵����� ����
/// \author		dhkwon
/// \date		2004-10-18 ~ 2004-10-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::SendDeleteSelectItemSkill()
{
	ASSERT_ASSERT(m_pDeleteSkill);
	MSG_FC_ITEM_THROW_AWAY_ITEM sMsg;
	sMsg.Amount = 1;
	sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
	sMsg.ItemUniqueNumber = m_pDeleteSkill->UniqueNumber;
	g_pFieldWinSocket->SendMsg( T_FC_ITEM_THROW_AWAY_ITEM, (char*)&sMsg, sizeof(sMsg) );
	m_pDeleteSkill = NULL;
}

int CINFCharacterInfoExtend::UTCWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFCharacterInfoExtend::UTCWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient( g_pD3dApp->GetHwnd(), &pt );
			CheckMouseReverse(&pt);

			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;
			
			if( pt.x>CHAR_UTC_START_X && pt.x<CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*CHAR_UTC_TYPE_NUMBER &&
				pt.y>CHAR_UTC_START_Y && pt.y<CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*MAX_CHAR_UTC_SLOT_NUMBER)
			{

				int nTemp = m_nCurrentUTCScroll;

				if((int)wParam > 0)
				{
					m_nCurrentUTCScroll--;
					if(m_nCurrentUTCScroll<0)
						m_nCurrentUTCScroll = 0;
					else if(m_nCurrentUTCScroll>GetUtcMaxScrollNumber())
						m_nCurrentUTCScroll = GetUtcMaxScrollNumber();
				}
				else
				{
					m_nCurrentUTCScroll++;
					if(m_nCurrentUTCScroll<0)
						m_nCurrentUTCScroll = 0;
					else if(m_nCurrentUTCScroll>GetUtcMaxScrollNumber())
						m_nCurrentUTCScroll = GetUtcMaxScrollNumber();
				}

				if(nTemp != m_nCurrentUTCScroll)
						SetAllUTCInfo();
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
			m_bLbuttonDown = FALSE;
			
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;

			if(m_bUTCScrollLock)
			{
				int nMove = (int)(pt.y-m_ptMouse.y);
				if(abs(nMove)>UTC_SCROLL_INTERVAL)
				{
					int nTemp = m_nCurrentUTCScroll;
					m_ptMouse = pt;
					int max = UTC_SCROLL_INTERVAL;
					if(max>0)
					{
						m_nCurrentUTCScroll += nMove/max;
						if(m_nCurrentUTCScroll<0)
							m_nCurrentUTCScroll = 0;
						else if(m_nCurrentUTCScroll>GetUtcMaxScrollNumber())
							m_nCurrentUTCScroll = GetUtcMaxScrollNumber();
						if(nTemp != m_nCurrentUTCScroll)
							SetAllUTCInfo();
					}
				}
			}
			if( pt.x>CHAR_UTC_START_X-20 && pt.x<CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*CHAR_UTC_TYPE_NUMBER+20 &&
				pt.y>CHAR_UTC_START_Y && pt.y<CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*MAX_CHAR_UTC_SLOT_NUMBER+20)
			{
				int i = ( pt.x - CHAR_UTC_START_X ) / CHAR_UTC_INTERVAL_X;
				if( i>=0 && 
					i<CHAR_UTC_TYPE_NUMBER &&
					pt.x<CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i+CHAR_UTC_ICON_SIZE)
				{
					int j = (pt.y - CHAR_UTC_START_Y) / CHAR_UTC_INTERVAL_Y;
					if( j >=0 && 
						j<MAX_CHAR_UTC_SLOT_NUMBER &&
						pt.y<CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j+CHAR_UTC_ICON_SIZE &&
						m_pCharacterSkillDisplayInfo[i][j].pItem)
					{
						//((CINFGameMain*)m_pParent)->SetToolTip(pt.x, pt.y, m_pCharacterSkillDisplayInfo[i][j].Name );
						((CINFGameMain*)m_pParent)->SetItemInfo(m_pCharacterSkillDisplayInfo[i][j].pItem->UniqueNumber, 
																m_pCharacterSkillDisplayInfo[i][j].pItem->ItemNum, pt.x, pt.y);
					}
					else
						((CINFGameMain*)m_pParent)->SetItemInfo(0,0,0,0);
						//((CINFGameMain*)m_pParent)->SetToolTip(0,0,NULL);
				}
				else
					((CINFGameMain*)m_pParent)->SetItemInfo(0,0,0,0);
					//((CINFGameMain*)m_pParent)->SetToolTip(0,0,NULL);
			}
			else
			{
				((CINFGameMain*)m_pParent)->SetItemInfo(0,0,0,0);
			}
				//((CINFGameMain*)m_pParent)->SetToolTip(0,0,NULL);
			{					
				POINT ptBkSize = m_pInoBk->GetImgSize();
				if(pt.y>nWindowPosY &&
					pt.y<nWindowPosY+ptBkSize.y&&
					pt.x>nWindowPosX &&
					pt.x<nWindowPosX + ptBkSize.x)
				{
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
			
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;			

			if( pt.x>CHAR_UTC_START_X && pt.x<CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*CHAR_UTC_TYPE_NUMBER &&
				pt.y>CHAR_UTC_START_Y && pt.y<CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*MAX_CHAR_UTC_SLOT_NUMBER)
			{
				int i = ( pt.x - CHAR_UTC_START_X ) / CHAR_UTC_INTERVAL_X;
				if( i>=0 && i<CHAR_UTC_TYPE_NUMBER &&
					pt.x<CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i+CHAR_UTC_ICON_SIZE)
				{
					int j = (pt.y - CHAR_UTC_START_Y) / CHAR_UTC_INTERVAL_Y;
					if( j >=0 && j<MAX_CHAR_UTC_SLOT_NUMBER &&
						pt.y<CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j+CHAR_UTC_ICON_SIZE)
					{

						m_nRenderMoveIconIntervalWidth =  pt.x - (CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i);
						m_nRenderMoveIconIntervalHeight = pt.y - (CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j);

						if(	m_pCharacterSkillDisplayInfo[i][j].pItem &&
							m_pCharacterSkillDisplayInfo[i][j].pItem->ItemInfo->SkillType != SKILLTYPE_PERMANENT)	
						{
							SetSelectUTC( &m_pCharacterSkillDisplayInfo[i][j] );
							m_bLbuttonDown = TRUE;
							//((CINFGameMain*)m_pParent)->SetItemInfo(m_pCharacterSkillDisplayInfo[i][j].pItem->UniqueNumber, m_pCharacterSkillDisplayInfo[i][j].pItem->ItemNum, pt.x, pt.y);
							return INF_MSGPROC_BREAK;
						}
					}
				}
			}
			if( pt.x>UTC_SCROLL_BUTTON_START_X && pt.x<UTC_SCROLL_BUTTON_START_X+UTC_SCROLL_BAR_SIZE_X &&
				pt.y>nWindowPosY+UTC_SCROLL_BAR_START_Y+m_nCurrentUTCScroll*UTC_SCROLL_INTERVAL && pt.y<nWindowPosY+UTC_SCROLL_BAR_START_Y+m_nCurrentUTCScroll*UTC_SCROLL_INTERVAL+UTC_SCROLL_BAR_SIZE_Y)
			{
				m_bUTCScrollLock =	TRUE;
				m_ptMouse = pt;

			}

			// 2005-08-02 by ispark
			// â�ȿ� ���콺 Ŭ���� ��ȿ
			POINT ptBkSize = m_pInoBk->GetImgSize();
			if(pt.y>nWindowPosY &&
				pt.y<nWindowPosY+ptBkSize.y&&
				pt.x>nWindowPosX &&
				pt.x<nWindowPosX + ptBkSize.x)
			{
				return INF_MSGPROC_BREAK;
			}		

			// 2006-07-27 by ispark, ���� �������� ������ �ִٸ�
			if(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem && 
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_SKILL_POS)
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			//			POINT pt = MAKEPOINT(lParam);
			if(m_bLbuttonDown)
			{
				m_bLbuttonDown = FALSE;
			}
			else
			{
				// 2005-12-01 by ispark, �����Կ��� LBUTTONUP�� ��
				if(((CINFGameMain*)m_pParent)->m_pQuickSlot->LButtonUpQuickSlot(pt))
				{
					// �����Կ����� SelectItem ���� ����
					break;
				}
				else if(((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_SKILL_POS)
				{
					SetSelectUTC(NULL);
				}
			}

			((CINFGameMain*)m_pParent)->SetItemInfo(0,0, 0,0);

			m_bUTCScrollLock = FALSE;
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;
			
			if( pt.x>CHAR_UTC_START_X && pt.x<CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*CHAR_UTC_TYPE_NUMBER &&
				pt.y>CHAR_UTC_START_Y && pt.y<CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*MAX_CHAR_UTC_SLOT_NUMBER)
			{
				int i = ( pt.x - CHAR_UTC_START_X ) / CHAR_UTC_INTERVAL_X;
				if( i>=0 && i<CHAR_UTC_TYPE_NUMBER &&
					pt.x<CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i+CHAR_UTC_ICON_SIZE)
				{
					int j = (pt.y - CHAR_UTC_START_Y) / CHAR_UTC_INTERVAL_Y;
					if( j >=0 && j<MAX_CHAR_UTC_SLOT_NUMBER &&
						pt.y<CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j+CHAR_UTC_ICON_SIZE)
					{
						m_nRenderMoveIconIntervalWidth =  pt.x - (CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i);
						m_nRenderMoveIconIntervalHeight = pt.y - (CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j);

						if(	m_pCharacterSkillDisplayInfo[i][j].pItem &&
							m_pCharacterSkillDisplayInfo[i][j].pItem->ItemInfo->SkillType != SKILLTYPE_PERMANENT)	
						{
							SendUseSkill(m_pCharacterSkillDisplayInfo[i][j].pItem);	
						}
					}
				}
			}
			if( pt.x>UTC_SCROLL_BUTTON_START_X && pt.x<UTC_SCROLL_BUTTON_START_X+UTC_SCROLL_BAR_SIZE_X &&
				pt.y>nWindowPosY+UTC_SCROLL_BAR_START_Y+m_nCurrentUTCScroll*UTC_SCROLL_INTERVAL && pt.y<nWindowPosY+UTC_SCROLL_BAR_START_Y+m_nCurrentUTCScroll*UTC_SCROLL_INTERVAL+UTC_SCROLL_BAR_SIZE_Y)
			{
//				m_bUTCScrollLock =	TRUE;
				m_ptMouse = pt;
			}

		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}
int CINFCharacterInfoExtend::ArenaWndProc(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;

			POINT ptBkSize = m_pInoBk->GetImgSize();
			if(pt.y>nWindowPosY &&
				pt.y<nWindowPosY+ptBkSize.y&&
				pt.x>nWindowPosX &&
				pt.x<nWindowPosX + ptBkSize.x)
			{
				return INF_MSGPROC_BREAK;
			}		
		}
		break;
	}
	return INF_MSGPROC_NORMAL;

}

// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
int CINFCharacterInfoExtend::PartnerWndProc(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;

	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	CheckMouseReverse(&pt);

	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			if(m_pChangeNameBtn)
				m_pChangeNameBtn->OnMouseMove(pt);

			if( m_pExpScroll->GetMouseMoveMode() )
			{
				m_pExpScroll->SetScrollPos( pt, TRUE);
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if(m_pChangeNameBtn)
				m_pChangeNameBtn->OnLButtonDown(pt);

			if( m_pExpScroll->IsMouseBallPos( pt ) )
			{
				m_pExpScroll->SetMouseMoveMode( TRUE );
				return INF_MSGPROC_BREAK;
			}
			POINT ptBkSize = m_pInoBk->GetImgSize();
			if(pt.y>nWindowPosY &&
				pt.y<nWindowPosY+ptBkSize.y&&
				pt.x>nWindowPosX &&
				pt.x<nWindowPosX + ptBkSize.x)
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			if(m_pChangeNameBtn->OnLButtonUp(pt))
			{
				g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_100608_0408, _Q_PARTNER_NEW_NAME_CHANGE );//"��Ʈ�� �̸��� �Է��ϼ���"
			}
			if(m_pExpScroll->GetMouseMoveMode())
			{
				m_pExpScroll->SetMouseMoveMode( FALSE );
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFCharacterInfoExtend::SetSelectUTC( INVEN_DISPLAY_INFO* pDisplayInfo )
{
	FLOG( "CINFCharacterInfoExtend::SetSelectUTC( INVEN_DISPLAY_INFO* pDisplayInfo )" );
	POINT ptIcon;
	ptIcon.x = m_nRenderMoveIconIntervalWidth;
	ptIcon.y = m_nRenderMoveIconIntervalHeight;

	((CINFGameMain*)m_pParent)->SetSelectItem(pDisplayInfo, ptIcon, ITEM_SKILL_POS);

//	if(pDisplayInfo)
//	{
//		m_pSelectIcon = ((CINFGameMain*)m_pParent)->m_pIcon->FindIcon(pDisplayInfo->IconName);
//		m_pSelectSkill = (ITEM_SKILL*)pDisplayInfo->pItem;
//		g_pGameMain->m_pQuickSlot->m_pSelectItem = (ITEM_BASE*)m_pSelectSkill;
//	}
//	else
//	{
//		m_pSelectIcon = NULL;
//		m_pSelectSkill = NULL;
//	}

}


///////////////////////////////////////////////////////////////////////////////
/// \fn			SendUseSkill( ITEM_BASE* pSkill )
/// \brief		��ų�� ����Ѵ�.
/// \author		jschoi
/// \date		2004-10-04 ~ 2004-10-04
/// \warning	����� ��ų�� ������� ��� ��Ŭ �����ϴ� �κ��� �ִ�.
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::SendUseSkill( ITEM_BASE* pSkill )
{
	FLOG( "CINFCharacterInfoExtend::SendUseSkill( ITEM_BASE* pSkill )" );
	// 2006-07-28 by ispark, ĳ���Ϳ� ��ų
	if(g_pD3dApp->m_bCharacter &&
		!IS_BAZAAR_SKILL(pSkill->ItemInfo))
	{
		// ĳ���Ϳ� ��ų �ƴ�
		return;
	}

	// 2006-07-30 by ispark, ��ų ����� �޽��� �ڽ��� �㰡 �ؾ��ϴ� ��ų�� üũ�Ѵ�.
	if(!CheckUseSkillApprovalEnd(pSkill))
	{
		return;
	}

	if( pSkill->ItemInfo->SkillType == SKILLTYPE_PERMANENT )
	{
		ASSERT_ASSERT(pSkill->ItemInfo->SkillType != SKILLTYPE_PERMANENT);
		return;
	}

	BOOL bUse = TRUE;
	if(	pSkill->ItemInfo->SkillType == SKILLTYPE_TOGGLE )
	{
		CSkillInfo* pSkillInfo = g_pShuttleChild->m_pSkill->FindUsingSkillInfo(pSkill->ItemNum);
		if(pSkillInfo != NULL)
		{
//			if(	pSkillInfo->GetSkillState() == SKILL_STATE_WAIT_REATTACK ||
//				pSkillInfo->GetSkillState() == SKILL_STATE_RELEASE )
//			{
//				return;
//			}
			pSkillInfo->ChangeSkillState(SKILL_STATE_WAIT_REATTACK);
			g_pGameMain->m_pInfSkill->DeleteSkillInfo(pSkillInfo);
			g_pShuttleChild->m_pSkill->EraseUsingSkill(pSkillInfo);
			bUse = FALSE;
		}
	}
	
	// 2008-12-16 by bhsohn A��� ������Ƽ�� ��ų ����� ���� ��ų ���� ���������� ��ų ���
	CHARACTER ShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
	if(IS_DT(ShuttleInfo.UnitKind))
	{
		// A�� �ش����
		RefreshAGearSkillInfo(pSkill->ItemNum);
	}
	// end 2008-12-16 by bhsohn A��� ������Ƽ�� ��ų ����� ���� ��ų ���� ���������� ��ų ���

	if(bUse)
	{
		g_pShuttleChild->m_pSkill->UseSkill( (CSkillInfo*)pSkill );
	}
	else
	{
//		g_pShuttleChild->m_pSkill->ReleaseAllUsingToggleSkill();
		
//		(*itSkillInfo)->ChangeSkillState(SKILL_STATE_WAIT_REATTACK);
//		g_pGameMain->m_pInfSkill->DeleteSkillInfo(*itSkillInfo);
//		SafeDeleteSkillInfo(*itSkillInfo);
//		m_vecUsingSkill.erase(itSkillInfo);	


//		MSG_FC_SKILL_CANCEL_SKILL sMsg;
//		memset(&sMsg,0x00,sizeof(sMsg));
//		char buffer[SIZE_MAX_PACKET];
//		int nType = T_FC_SKILL_CANCEL_SKILL;
//		sMsg.SkillItemUniqueNumber = pSkill->UniqueNumber;
//		memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//		memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//		g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
		}

//	if(g_pD3dApp->m_pShuttleChild->m_bIsAir == TRUE && pSkill->ItemInfo->SkillType == 3)		// ���߿��� �����带 ����Ҷ� ������]
//	{
//	}
//	else if( pSkill->ItemInfo->SkillType == 3 ||				// ���� ��� �̰ų�
//		(g_pShuttleChild->m_dwState == _NORMAL					// �Ϲݻ��׿���.. 
//		&& g_pShuttleChild->m_nEventType != EVENT_GAME_END) )	// ��ų ��� ���� - jschoi 
//	{
//		if(bUse)
//		{
//			g_pShuttleChild->m_pSkill->UseSkill( (CSkillInfo*)pSkill );
//			//		MSG_FC_SKILL_USE_SKILL sMsg;
//			//		memset(&sMsg,0x00,sizeof(sMsg));
//			//		char buffer[SIZE_MAX_PACKET];
//			//		int nType = T_FC_SKILL_USE_SKILL;
//			//		sMsg.SkillItemUniqueNumber = pSkill->UniqueNumber;
//			//		// target ???
//			//		sMsg.AttackIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
//			//		sMsg.TargetIndex = 0;
//			//		memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//			//		memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//			//		g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
//		}
//		else
//		{
//			MSG_FC_SKILL_CANCEL_SKILL sMsg;
//			memset(&sMsg,0x00,sizeof(sMsg));
//			char buffer[SIZE_MAX_PACKET];
//			int nType = T_FC_SKILL_CANCEL_SKILL;
//			sMsg.SkillItemUniqueNumber = pSkill->UniqueNumber;
//			memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
//			memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
//			g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
//		}
//	}
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-12-16 by bhsohn A��� ������Ƽ�� ��ų ����� ���� ��ų ���� ���������� ��ų ���
/// \date		2008-09-26 ~ 2008-09-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::RefreshAGearSkillInfo(int i_nSkillItemNum)
{	
	switch(SKILL_BASE_NUM(i_nSkillItemNum))
	{
	case AGEAR_SKILL_BASENUM_SIEGEMODE:
	case AGEAR_SKILL_BASENUM_SIEGEDEFENSEMODE:
		{
		}
		break;
	default:
		{
			return;
		}
		break;
	}	

	CSkillInfo *pGroundAccelSkillInfo = 
		g_pShuttleChild->m_pSkill->FindUsingSkillInfoByBaseNum(AGEAR_SKILL_BASENUM_GROUNDACCELERATOR);
	if(NULL == pGroundAccelSkillInfo)
	{
		// �׶��� ����
		return;
	}

	pGroundAccelSkillInfo->ChangeSkillState(SKILL_STATE_WAIT_REATTACK);
	g_pGameMain->m_pInfSkill->DeleteSkillInfo(pGroundAccelSkillInfo);
	g_pShuttleChild->m_pSkill->EraseUsingSkill(pGroundAccelSkillInfo);
}



int CINFCharacterInfoExtend::InfoWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFCharacterInfoExtend::InfoWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;
//			m_bToolTipStat = FALSE;					// 2005-07-04 by ispark �ڵ� ���� �й� ����

			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			((CINFGameMain*)m_pParent)->SetToolTip(0,0,NULL);

			// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
			
	
			int nCnt = 0;
			for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO;nCnt++)
			{
				m_pBonusStatBtn[nCnt]->OnMouseMove(pt);	
			}	
			// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
			
			// 2007-05-15 by bhsohn ��� ���� ���� ó��
			BOOL bOverStat[MAX_STAT_SHUTTLEINFO];			
			for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO; nCnt++)
			{
				bOverStat[nCnt] = (m_nShowOverStat[nCnt] > 0);
			}			
				

			if( pt.y > nWindowPosY+STAT_TOOLTIP_ATTACK_START_Y &&
				pt.y < nWindowPosY+STAT_TOOLTIP_ATTACK_START_Y+STAT_TOOLTIP_SIZE_Y)
			{				
				if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_ATTACK]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0001);//"���ݽ� �������� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				// 2007-05-15 by bhsohn ��� ���� ���� ó��
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X-OVER_STAT_CAP0_X
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_ATTACK]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0001);//"���ݽ� �������� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_ATTACK])
					&& (m_bStatShow[STAT_SHUTTLEINFO_ATTACK]))
				{
					char buf[64];
					const GEAR_STAT_CHANGE_VALUE* pStat = CAtumSJ::GetGearStatChangeValueStruct( g_pShuttleChild->m_myShuttleInfo.UnitKind );
					
					if(pStat && (g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0))
					{
						sprintf( buf, STRMSG_C_TOOLTIP_0002, pStat->GearStat1.AttackPart);//"\\y���� ���� ������: %d"
						g_pGameMain->SetToolTip( pt.x, pt.y, buf);
						return INF_MSGPROC_BREAK;
					}					
				}
				// 2007-05-15 by bhsohn ��� ���� ���� ó��
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP0_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_ATTACK]))
				{				
					// �ʰ��� ����
					char buf[64];
					sprintf( buf, STRMSG_C_070516_0201);//"\\y�ʰ��� ����"
					g_pGameMain->SetToolTip( pt.x, pt.y, buf);
					return INF_MSGPROC_BREAK;
				}
				if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X 
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_FUEL]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0005);//"������ ���� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				// 2007-05-15 by bhsohn ��� ���� ���� ó��
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X -OVER_STAT_CAP0_X
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_FUEL]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0005);//"������ ���� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_FUEL])
					&&(m_bStatShow[STAT_SHUTTLEINFO_FUEL]))
				{
					char buf[64];
					const GEAR_STAT_CHANGE_VALUE* pStat = CAtumSJ::GetGearStatChangeValueStruct( g_pShuttleChild->m_myShuttleInfo.UnitKind );					
					if(pStat && (g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0))
					{
						sprintf( buf, STRMSG_C_TOOLTIP_0006, pStat->GearStat1.FuelPart);//"\\y���� ���� ������: %d"
						g_pGameMain->SetToolTip( pt.x, pt.y, buf);
						return INF_MSGPROC_BREAK;
					}					
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP0_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_FUEL]))
				{
					// �ʰ��� ����
					char buf[64];
					sprintf( buf, STRMSG_C_070516_0201);//"\\y�ʰ��� ����"
					g_pGameMain->SetToolTip( pt.x, pt.y, buf);
					return INF_MSGPROC_BREAK;
				}

				
			}
			else if( pt.y > nWindowPosY+STAT_TOOLTIP_DEFENSE_START_Y &&
				pt.y < nWindowPosY+STAT_TOOLTIP_DEFENSE_START_Y+STAT_TOOLTIP_SIZE_Y)
			{
				if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X
				&& (FALSE == bOverStat[STAT_SHUTTLEINFO_DEFENCE]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0003);//"�´� �������� ���ҽ��� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X- OVER_STAT_CAP1_X
				&& (TRUE == bOverStat[STAT_SHUTTLEINFO_DEFENCE]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0003);//"�´� �������� ���ҽ��� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_DEFENCE])
					&&(m_bStatShow[STAT_SHUTTLEINFO_DEFENCE]))
				{
					char buf[64];
					const GEAR_STAT_CHANGE_VALUE* pStat = CAtumSJ::GetGearStatChangeValueStruct( g_pShuttleChild->m_myShuttleInfo.UnitKind );

					// 2007-05-15 by bhsohn ��� ���� ���� ó��
					if(pStat && (g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0))
					{
						sprintf( buf, STRMSG_C_TOOLTIP_0004, pStat->GearStat1.DefensePart);//����->���//"\\y��� ���� ������: %d"
						g_pGameMain->SetToolTip( pt.x, pt.y, buf);
						return INF_MSGPROC_BREAK;
					}					
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP1_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_DEFENCE]))
				{
					// �ʰ��� ����
					char buf[64];
					sprintf( buf, STRMSG_C_070516_0201);//"\\y�ʰ��� ����"
					g_pGameMain->SetToolTip( pt.x, pt.y, buf);
					return INF_MSGPROC_BREAK;
				}

				
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X 
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_SOUL]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0007);//"��ų�� ����� �� �ִ� ��ų ����Ʈ�� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				// 2007-05-15 by bhsohn ��� ���� ���� ó��
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X -OVER_STAT_CAP1_X
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_SOUL]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0007);//"��ų�� ����� �� �ִ� ��ų ����Ʈ�� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
				&& (FALSE == bOverStat[STAT_SHUTTLEINFO_SOUL])
				&&(m_bStatShow[STAT_SHUTTLEINFO_SOUL]))
				{
					char buf[64];
					const GEAR_STAT_CHANGE_VALUE* pStat = CAtumSJ::GetGearStatChangeValueStruct( g_pShuttleChild->m_myShuttleInfo.UnitKind );

					// 2007-05-15 by bhsohn ��� ���� ���� ó��
					if(pStat && (g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0))
					{
						sprintf( buf, STRMSG_C_TOOLTIP_0008, pStat->GearStat1.SoulPart);//"\\y���� ���� ������: %d"
						g_pGameMain->SetToolTip( pt.x, pt.y, buf);
						return INF_MSGPROC_BREAK;
					}					
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP1_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
				&& (TRUE == bOverStat[STAT_SHUTTLEINFO_SOUL]))
				{
					// �ʰ��� ����
					char buf[64];
					sprintf( buf, STRMSG_C_070516_0201);//"\\y�ʰ��� ����"
					g_pGameMain->SetToolTip( pt.x, pt.y, buf);
					return INF_MSGPROC_BREAK;
				}
			}
			else if( pt.y > nWindowPosY+STAT_TOOLTIP_DODGE_START_Y &&
				pt.y < nWindowPosY+STAT_TOOLTIP_DODGE_START_Y+STAT_TOOLTIP_SIZE_Y)
			{
				if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_DODGE]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0009);//"���ݿ� ���� ȸ�Ǹ� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				// 2007-05-15 by bhsohn ��� ���� ���� ó��
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP0_X 
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_DODGE]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0009);//"���ݿ� ���� ȸ�Ǹ� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y
					&& (FALSE == bOverStat[STAT_SHUTTLEINFO_DODGE])
					&& (m_bStatShow[STAT_SHUTTLEINFO_DODGE]))
				{ 
					char buf[64];
					const GEAR_STAT_CHANGE_VALUE* pStat = CAtumSJ::GetGearStatChangeValueStruct( g_pShuttleChild->m_myShuttleInfo.UnitKind );
					
					if(pStat && (g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0))
					{
						sprintf( buf, STRMSG_C_TOOLTIP_0010, pStat->GearStat1.DodgePart);//"\\yȸ�� ���� ������: %d"
						g_pGameMain->SetToolTip( pt.x, pt.y, buf);
						return INF_MSGPROC_BREAK;
					}				
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP0_X &&
					pt.x < nWindowPosX+STAT_TOOLTIP_LEFT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y
					&& (TRUE == bOverStat[STAT_SHUTTLEINFO_DODGE]))
				{
					// �ʰ��� ����
					char buf[64];
					sprintf( buf, STRMSG_C_070516_0201);//"\\y�ʰ��� ����"
					g_pGameMain->SetToolTip( pt.x, pt.y, buf);
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X 
				&& (FALSE == bOverStat[STAT_SHUTTLEINFO_SHIELD]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0011);//"������ ���� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP1_X
				&& (TRUE == bOverStat[STAT_SHUTTLEINFO_SHIELD]))
				{
					g_pGameMain->SetToolTip( pt.x, pt.y, STRMSG_C_TOOLTIP_0011);//"������ ���� �������� �ݴϴ�."
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X &&
				pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
				&& (FALSE == bOverStat[STAT_SHUTTLEINFO_SHIELD])
				&& (m_bStatShow[STAT_SHUTTLEINFO_SHIELD]))
				{
					char buf[64];
					const GEAR_STAT_CHANGE_VALUE* pStat = CAtumSJ::GetGearStatChangeValueStruct( g_pShuttleChild->m_myShuttleInfo.UnitKind );
					
					if(pStat && (g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0))
					{
						sprintf( buf, STRMSG_C_TOOLTIP_0012, pStat->GearStat1.ShieldPart); //���->����//"\\y���� ���� ������: %d"
						g_pGameMain->SetToolTip( pt.x, pt.y, buf);
						return INF_MSGPROC_BREAK;
					}					
				}
				else if( pt.x > nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X - OVER_STAT_CAP1_X&&
				pt.x < nWindowPosX+STAT_TOOLTIP_RIGHT_START_X+STAT_TOOLTIP_SIZE_X+STAT_TOOLTIP_SIZE_Y 
				&& (TRUE == bOverStat[STAT_SHUTTLEINFO_SHIELD]))
				{
					// �ʰ��� ����
					char buf[64];
					sprintf( buf, STRMSG_C_070516_0201);//"\\y�ʰ��� ����"
					g_pGameMain->SetToolTip( pt.x, pt.y, buf);
					return INF_MSGPROC_BREAK;
				}
			}
			// 2008-09-22 by bhsohn EP3 ĳ���� â
			else if( pt.y > nWindowPosY + (AMMO_START_Y+(AMMO_INTERVAL)) &&
				pt.y < nWindowPosY + (AMMO_START_Y+(AMMO_INTERVAL))+STAT_TOOLTIP_SIZE_Y)
			{
				if( pt.x > (nWindowPosX+AMMO_START_X -ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+AMMO_START_X))					
				{
					char chToolTip[MAX_PATH];				
					memset(chToolTip, 0x00, MAX_PATH);

					if(g_pShuttleChild->m_pPrimaryWeapon)
					{							
						char chTmp1[128], chTmp2[128],chTmp3[128];
						//"�Ǿ : %.2f"
						float fStatPierce = g_pShuttleChild->m_pPrimaryWeapon->GetStatPierce();
						float fEnchantPierce = g_pShuttleChild->m_pPrimaryWeapon->GetPrimaryEnchantPierce();
						
						float fItemPierce = g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_01;						
						// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
						//fItemPierce = ((float)fItemPierce / (float)PROB256_MAX_VALUE *100.0f);
						fItemPierce = ((float)fItemPierce / (float)PROB100_MAX_VALUE *100.0f);

						// 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��
						float fPreSufPierce = g_pShuttleChild->m_pPrimaryWeapon->GetPreSufFixItemInfoRate(DES_PIERCE_UP_01);
						// end 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��

						// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���																	
						fStatPierce = FloatSecRangeSharp(fStatPierce);
						fEnchantPierce = FloatSecRangeSharp(fEnchantPierce);
						fItemPierce = FloatSecRangeSharp(fItemPierce);
						
						// 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��
						fItemPierce += fPreSufPierce;
						// end 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��
						
						sprintf( chTmp1, STRMSG_C_080923_0200, fStatPierce);
						sprintf( chTmp2, STRMSG_C_080923_0200, fEnchantPierce);
						sprintf( chTmp3, STRMSG_C_080923_0200, fItemPierce);
						
						if(fEnchantPierce > 0)
						{
							if(fItemPierce > 0)
							{
								sprintf( chToolTip, "%s\\e[+%s]\\e\\g[+%s]\\g", chTmp1, chTmp2, chTmp3);
							}
							else
							{
								sprintf( chToolTip, "%s\\e[+%s]\\e", chTmp1, chTmp2);
							}							
						}
						else
						{
							if(fItemPierce > 0)
							{
								sprintf( chToolTip, "%s\\g[+%s]\\g", chTmp1, chTmp3);
							}
							else
							{
								sprintf( chToolTip, "%s", chTmp1);								
							}
							
						}							
						g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//						
						return INF_MSGPROC_BREAK;
					}					
					else
					{
						char chTmp1[128], chTmp2[128];
						float fStatPierce = GetDefaultPierce(TRUE);			
						float fItemPierce = g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_01;						
						// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
						//fItemPierce = ((float)fItemPierce / (float)PROB256_MAX_VALUE *100.0f);
						fItemPierce = ((float)fItemPierce / (float)PROB100_MAX_VALUE *100.0f);

						// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���
						fStatPierce = FloatSecRangeSharp(fStatPierce);
						fItemPierce = FloatSecRangeSharp(fItemPierce);

						sprintf( chTmp1, STRMSG_C_080923_0200, fStatPierce);			
						sprintf( chTmp2, STRMSG_C_080923_0200, fItemPierce);			
						if(fItemPierce > 0)
						{
							sprintf( chToolTip, "%s\\g[+%s]\\g", chTmp1, chTmp2);
						}
						else
						{
							sprintf( chToolTip, "%s", chTmp1);								
						}						

						g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//						

						return INF_MSGPROC_BREAK;
					}
				}
				else if( pt.x > (nWindowPosX+AMMO_START_X+AMMO_START_INTERVAL_X-ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+AMMO_START_X+AMMO_START_INTERVAL_X))					
				{
					char chToolTip[MAX_PATH];				
					memset(chToolTip, 0x00, MAX_PATH);

					if(g_pShuttleChild->m_pSecondaryWeapon)
					{
						char chTmp1[128], chTmp2[128], chTmp3[128];
						//"�Ǿ : %.2f"
						float fStatPierce = g_pShuttleChild->m_pSecondaryWeapon->GetStatPierce();
						float fEnchantPierce = g_pShuttleChild->m_pSecondaryWeapon->GetSecondaryEnchantPierce();
						float fItemPierce = g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_02;						
						// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
						//fItemPierce = ((float)fItemPierce / (float)PROB256_MAX_VALUE *100.0f);
						fItemPierce = ((float)fItemPierce / (float)PROB100_MAX_VALUE *100.0f);

						// 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��
						float fPreSufPierce = g_pShuttleChild->m_pSecondaryWeapon->GetPreSufFixItemInfoRate(DES_PIERCE_UP_02);
						// end 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��

						// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���
						fStatPierce = FloatSecRangeSharp(fStatPierce);
						fEnchantPierce = FloatSecRangeSharp(fEnchantPierce);
						fItemPierce = FloatSecRangeSharp(fItemPierce);

						// 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��
						fItemPierce += fPreSufPierce;
						// end 2009-02-16 by bhsohn ����, ���� �Ǿ �� �Ⱥ��̴� ���� ó��
						
						sprintf( chTmp1, STRMSG_C_080923_0200, fStatPierce);
						sprintf( chTmp2, STRMSG_C_080923_0200, fEnchantPierce);
						sprintf( chTmp3, STRMSG_C_080923_0200, fItemPierce);

						if(fEnchantPierce > 0)
						{
							if(fItemPierce > 0)
							{
								sprintf( chToolTip, "%s\\e[+%s]\\e\\g[+%s]\\g", chTmp1, chTmp2, chTmp3);
							}
							else
							{
								sprintf( chToolTip, "%s\\e[+%s]\\e", chTmp1, chTmp2);
							}							
						}
						else
						{
							if(fItemPierce > 0)
							{
								sprintf( chToolTip, "%s\\g[+%s]\\g", chTmp1, chTmp3);
							}
							else
							{
								sprintf( chToolTip, "%s", chTmp1);								
							}
						}							

						g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//

						return INF_MSGPROC_BREAK;
					}
					else
					{
						char chTmp1[128], chTmp2[128];
						float fStatPierce = GetDefaultPierce(FALSE);			
						float fItemPierce = g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_02;						
						// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
						//fItemPierce = ((float)fItemPierce / (float)PROB256_MAX_VALUE *100.0f);
						fItemPierce = ((float)fItemPierce / (float)PROB100_MAX_VALUE *100.0f);

						// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���						
						fStatPierce = FloatSecRangeSharp(fStatPierce);
						fItemPierce = FloatSecRangeSharp(fItemPierce);

						sprintf( chTmp1, STRMSG_C_080923_0200, fStatPierce);			
						sprintf( chTmp2, STRMSG_C_080923_0200, fItemPierce);			
						if(fItemPierce > 0)
						{
							sprintf( chToolTip, "%s\\g[+%s]\\g", chTmp1, chTmp2);
						}
						else
						{
							sprintf( chToolTip, "%s", chTmp1);								
						}						

						g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//						

						return INF_MSGPROC_BREAK;
					}
				}

			}
			else if( pt.y > nWindowPosY + (AMMO_START_Y+(AMMO_INTERVAL*2)) &&
				pt.y < nWindowPosY + (AMMO_START_Y+(AMMO_INTERVAL*2))+STAT_TOOLTIP_SIZE_Y)
			{
				if( pt.x > (nWindowPosX+AMMO_START_X -ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+AMMO_START_X))					
				{
					if(g_pShuttleChild->m_pPrimaryWeapon)
					{
						CItemInfo *	pItemInfo = g_pShuttleChild->m_pPrimaryWeapon->GetClassItemInfo();
						char chToolTip[MAX_PATH];				
						memset(chToolTip, 0x00, MAX_PATH);
						GetItemAttackInfo(pItemInfo, chToolTip);		
						
						g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//"���ݿ� ���� ȸ�Ǹ� �������� �ݴϴ�."
						return INF_MSGPROC_BREAK;
					}
					
				}
				else if( pt.x > (nWindowPosX+AMMO_START_X+AMMO_START_INTERVAL_X-ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+AMMO_START_X+AMMO_START_INTERVAL_X))					
				{
					if(g_pShuttleChild->m_pSecondaryWeapon)
					{
						CItemInfo *	pItemInfo = g_pShuttleChild->m_pSecondaryWeapon->GetClassItemInfo();
						char chToolTip[MAX_PATH];				
						memset(chToolTip, 0x00, MAX_PATH);
						GetItemAttackInfo(pItemInfo, chToolTip);		
						
						g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//"���ݿ� ���� ȸ�Ǹ� �������� �ݴϴ�."
						return INF_MSGPROC_BREAK;
					}
					
				}

			}
			else if( pt.y > nWindowPosY + (OTHER_INFO_START_Y) &&
				pt.y < nWindowPosY + (OTHER_INFO_START_Y+STAT_TOOLTIP_SIZE_Y))
			{
				if( pt.x > (nWindowPosX+INFO_START_X -ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+INFO_START_X))					
				{
					// �⺻���� ����� 
//					float fAllDefence = 
//						((float)CAtumSJ::GetDefenseC( &g_pShuttleChild->m_myShuttleInfo, 
//						&g_pShuttleChild->m_paramFactor, TRUE ) / PROB256_MAX_VALUE)*100.0f;	
					char pDefaultRate[128],pArmorRate[128], pPetRate[128];					
					char chToolTip[MAX_PATH];									
					
					memset(pDefaultRate, 0x00, 128);	
					memset(pArmorRate, 0x00, 128);	
					memset(pPetRate, 0x00, 128);	

					memset(chToolTip, 0x00, MAX_PATH);	
					
					GetDefenceRateString(TRUE, pDefaultRate,pArmorRate, pPetRate);
					
					sprintf(chToolTip, "%s", pDefaultRate);
					if(strlen(pArmorRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pArmorRate);
					}					
					
					if(strlen(pPetRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pPetRate);
					}
					
					g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > (nWindowPosX+INFO_START_X+INFO_START_INTERVAL_X  -ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+INFO_START_X+INFO_START_INTERVAL_X ))					
				{

					char pDefaultRate[128],pArmorRate[128], pPetRate[128];					
					char chToolTip[MAX_PATH];									
					
					memset(pDefaultRate, 0x00, 128);	
					memset(pArmorRate, 0x00, 128);	
					memset(pPetRate, 0x00, 128);	

					memset(chToolTip, 0x00, MAX_PATH);	
										

					GetDodgeRateString(TRUE, pDefaultRate, pArmorRate, pPetRate);

					sprintf(chToolTip, "%s", pDefaultRate);
					
					if(strlen(pArmorRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pArmorRate);
					}										
					if(strlen(pPetRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pPetRate);
					}
					g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//"���ݿ� ���� ȸ�Ǹ� �������� �ݴϴ�."

					return INF_MSGPROC_BREAK;
				}		
				
				
			}
			else if( pt.y > nWindowPosY + (OTHER_INFO_START_Y+INFO_INTERVAL) &&
				pt.y < nWindowPosY + (OTHER_INFO_START_Y+INFO_INTERVAL+STAT_TOOLTIP_SIZE_Y))
			{
				
				if( pt.x > (nWindowPosX+INFO_START_X -ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+INFO_START_X))					
				{
					// ��޹��� ����� 
//					float fAllDefence = 
//						((float)CAtumSJ::GetDefenseC( &g_pShuttleChild->m_myShuttleInfo, 
//						&g_pShuttleChild->m_paramFactor, TRUE ) / PROB256_MAX_VALUE)*100.0f;	
					char pDefaultRate[128],pArmorRate[128], pPetRate[128];					
					char chToolTip[MAX_PATH];									
					
					memset(pDefaultRate, 0x00, 128);	
					memset(pArmorRate, 0x00, 128);	
					memset(pPetRate, 0x00, 128);	

					memset(chToolTip, 0x00, MAX_PATH);	
					
					GetDefenceRateString(FALSE, pDefaultRate,pArmorRate, pPetRate);
					
					sprintf(chToolTip, "%s", pDefaultRate);
					if(strlen(pArmorRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pArmorRate);
					}					
					
					if(strlen(pPetRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pPetRate);
					}
					
					g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);
					return INF_MSGPROC_BREAK;
				}
				else if( pt.x > (nWindowPosX+INFO_START_X+INFO_START_INTERVAL_X -ATTACK_TOOLIP_W)
					&&pt.x < (nWindowPosX+INFO_START_X+INFO_START_INTERVAL_X))					
				{
					char pDefaultRate[128],pArmorRate[128], pPetRate[128];					
					char chToolTip[MAX_PATH];									
					
					memset(pDefaultRate, 0x00, 128);	
					memset(pArmorRate, 0x00, 128);	
					memset(pPetRate, 0x00, 128);	

					memset(chToolTip, 0x00, MAX_PATH);	
										

					GetDodgeRateString(FALSE, pDefaultRate, pArmorRate, pPetRate);

					sprintf(chToolTip, "%s", pDefaultRate);
					
					if(strlen(pArmorRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pArmorRate);
					}										
					if(strlen(pPetRate) > 0)
					{
						sprintf(chToolTip, "%s%s", chToolTip, pPetRate);
					}
					g_pGameMain->SetToolTip( pt.x, pt.y, chToolTip);//"���ݿ� ���� ȸ�Ǹ� �������� �ݴϴ�."					
					return INF_MSGPROC_BREAK;

				}

			}
			{								
				POINT ptBkSize = m_pInoBk->GetImgSize();
				if(pt.y>nWindowPosY &&
					pt.y<nWindowPosY+ptBkSize.y&&
					pt.x>nWindowPosX &&
					pt.x<nWindowPosX + ptBkSize.x)
				{
					return INF_MSGPROC_BREAK;
				}		
			}
			// end 2008-09-22 by bhsohn EP3 ĳ���� â			
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;
						
			// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��									
			{
				int nCnt = 0;
				for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO;nCnt++)
				{					
					if(TRUE == m_pBonusStatBtn[nCnt]->OnLButtonDown(pt))
					{
						OnClickStat(nCnt);
						return  INF_MSGPROC_BREAK;
					}
				}	
			}
			// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

			// 2005-08-02 by ispark
			// â�ȿ� ���콺 Ŭ���� ��ȿ
			POINT ptBkSize = m_pInoBk->GetImgSize();
			if(pt.y>nWindowPosY &&
				pt.y<nWindowPosY+ptBkSize.y&&
				pt.x>nWindowPosX &&
				pt.x<nWindowPosX + ptBkSize.x)
			{
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	case WM_LBUTTONUP:
		{
//			POINT pt = MAKEPOINT(lParam);
			m_nButtonState = STAT_BUTTON_UP ;
			m_nStatType = STAT_NONE ;

			// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
						
			{
				int nCnt = 0;
				for(nCnt = 0;nCnt < MAX_STAT_SHUTTLEINFO;nCnt++)
				{
					if(TRUE == m_pBonusStatBtn[nCnt]->OnLButtonUp(pt))
					{
						//g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
						return  INF_MSGPROC_BREAK;
					}					
				}	
			}
			// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFCharacterInfoExtend::RenderShowStatInfo()
{
	FLOG( "CINFCharacterInfoExtend::ShowStatInfo()" );
	
	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;


	char	buff[30] ;
	CShuttleChild* pShuttle = g_pD3dApp->m_pShuttleChild;

	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	if(pShuttle)
	{
		// X��ǥ
		FLOAT fAllPosX[MAX_STAT_SHUTTLEINFO] =
		{
				nWindowPosX+STATINFO_START_X0,		// ����
				nWindowPosX+STATINFO_START_X0,		// ���
				nWindowPosX+STATINFO_START_X1,		// ����
				nWindowPosX+STATINFO_START_X1,		// ����
				nWindowPosX+STATINFO_START_X0,		// ȸ��
				nWindowPosX+STATINFO_START_X1// ����
		};
		// Y��ǥ
		FLOAT fAllPosY[MAX_STAT_SHUTTLEINFO] =
		{
				nWindowPosY+ SHOWSTATINFO_Y1,				// ����
				nWindowPosY+ SHOWSTATINFO_Y2,				// ���	
				nWindowPosY+ SHOWSTATINFO_Y1,				// ����
				nWindowPosY+ SHOWSTATINFO_Y2,				// ����
				nWindowPosY+ SHOWSTATINFO_Y3,				// ȸ��
				nWindowPosY+ SHOWSTATINFO_Y3				// ����
		};	

		FLOAT fOverStatPosX[MAX_STAT_SHUTTLEINFO] =
		{
				nWindowPosX+STATINFO_START_X0-OVER_STAT_CAP0_X,		// ����
				nWindowPosX+STATINFO_START_X0-OVER_STAT_CAP0_X,		// ���
				nWindowPosX+STATINFO_START_X1-OVER_STAT_CAP1_X,		// ����
				nWindowPosX+STATINFO_START_X1-OVER_STAT_CAP1_X,		// ����
				nWindowPosX+STATINFO_START_X0-OVER_STAT_CAP0_X,		// ȸ��
				nWindowPosX+STATINFO_START_X1-OVER_STAT_CAP1_X		// ����
		};
		FLOAT fPosX, fPosY;		
		char szOvrbuff[256] ;
		wsprintf(szOvrbuff, "");

		fPosX = fPosY = 0;
		
		// ���� 
		{			
			fPosX = fAllPosX[STAT_SHUTTLEINFO_ATTACK];
			fPosY = fAllPosY[STAT_SHUTTLEINFO_ATTACK];		
			if(m_nShowOverStat[STAT_SHUTTLEINFO_ATTACK] > 0)
			{
				fPosX = fOverStatPosX[STAT_SHUTTLEINFO_ATTACK];
				wsprintf(szOvrbuff, "(+%d)", m_nShowOverStat[STAT_SHUTTLEINFO_ATTACK]);
				if(m_StatOverInfoFont)
				{				
					// ���������� �׸���. 
					m_StatOverInfoFont->DrawText(fPosX+OVER_STAT_CAPX, fPosY, GUI_FONT_COLOR_R, szOvrbuff, 0 );
				}

				// �β��� �۾��� �׷��ش�.
				wsprintf(buff, "\\e%4d", (int)pShuttle->m_myShuttleInfo.TotalGearStat.AttackPart);//+(int)pShuttle->m_paramFactor.pfp_ATTACK_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
				
			}
			else if(m_nShowOverStat[STAT_SHUTTLEINFO_ATTACK] == 0)
			{
				// �β��� �۾��� �׷��ش�.
				wsprintf(buff, "\\e%4d", (int)pShuttle->m_myShuttleInfo.TotalGearStat.AttackPart);//+(int)pShuttle->m_paramFactor.pfp_ATTACK_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
				
			}
			else
			{
				wsprintf(buff, "%4d", (int)pShuttle->m_myShuttleInfo.TotalGearStat.AttackPart);//+(int)pShuttle->m_paramFactor.pfp_ATTACK_PART) ;
				if(m_StatInfoFont[0])
				{
					m_StatInfoFont[0]->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}			
		}

		// ���
		{			
			fPosX = fAllPosX[STAT_SHUTTLEINFO_DEFENCE];
			fPosY = fAllPosY[STAT_SHUTTLEINFO_DEFENCE];		
			if(m_nShowOverStat[STAT_SHUTTLEINFO_DEFENCE] > 0)
			{
				fPosX = fOverStatPosX[STAT_SHUTTLEINFO_DEFENCE];
				wsprintf(szOvrbuff, "(+%d)", m_nShowOverStat[STAT_SHUTTLEINFO_DEFENCE]);
				if(m_StatOverInfoFont)
				{				
					// ���������� �׸���. 
					m_StatOverInfoFont->DrawText(fPosX+OVER_STAT_CAPX, fPosY, GUI_FONT_COLOR_R, szOvrbuff, 0 );
				}
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.DefensePart);//+(int)pShuttle->m_paramFactor.pfp_DEFENSE_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else if(m_nShowOverStat[STAT_SHUTTLEINFO_DEFENCE] == 0)
			{
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.DefensePart);//+(int)pShuttle->m_paramFactor.pfp_DEFENSE_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else
			{
				wsprintf(buff, "%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.DefensePart);//+(int)pShuttle->m_paramFactor.pfp_DEFENSE_PART) ;
				if(m_StatInfoFont[1])
				{
					m_StatInfoFont[1]->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}			
		}

		// ����
		{			
			fPosX = fAllPosX[STAT_SHUTTLEINFO_FUEL];
			fPosY = fAllPosY[STAT_SHUTTLEINFO_FUEL];		
			if(m_nShowOverStat[STAT_SHUTTLEINFO_FUEL] > 0)
			{
				fPosX = fOverStatPosX[STAT_SHUTTLEINFO_FUEL];
				wsprintf(szOvrbuff, "(+%d)", m_nShowOverStat[STAT_SHUTTLEINFO_FUEL]);
				if(m_StatOverInfoFont)
				{				
					// ���������� �׸���. 
					m_StatOverInfoFont->DrawText(fPosX+OVER_STAT_CAPX, fPosY, GUI_FONT_COLOR_R, szOvrbuff, 0 );
				}
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.FuelPart);//+(int)pShuttle->m_paramFactor.pfp_FUEL_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else if(m_nShowOverStat[STAT_SHUTTLEINFO_FUEL] == 0)
			{
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.FuelPart);//+(int)pShuttle->m_paramFactor.pfp_FUEL_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else
			{
				wsprintf(buff, "%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.FuelPart);//+(int)pShuttle->m_paramFactor.pfp_FUEL_PART) ;
				if(m_StatInfoFont[2])
				{
					m_StatInfoFont[2]->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			
		}

		// ����
		{			
			fPosX = fAllPosX[STAT_SHUTTLEINFO_SOUL];
			fPosY = fAllPosY[STAT_SHUTTLEINFO_SOUL];		
			if(m_nShowOverStat[STAT_SHUTTLEINFO_SOUL] > 0)
			{
				fPosX = fOverStatPosX[STAT_SHUTTLEINFO_SOUL];
				wsprintf(szOvrbuff, "(+%d)", m_nShowOverStat[STAT_SHUTTLEINFO_SOUL]);
				if(m_StatOverInfoFont)
				{				
					// ���������� �׸���. 
					m_StatOverInfoFont->DrawText(fPosX+OVER_STAT_CAPX, fPosY, GUI_FONT_COLOR_R, szOvrbuff, 0 );
				}
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.SoulPart);//+(int)pShuttle->m_paramFactor.pfp_SOUL_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else if(m_nShowOverStat[STAT_SHUTTLEINFO_SOUL] == 0)
			{
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.SoulPart);//+(int)pShuttle->m_paramFactor.pfp_SOUL_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}

			}
			else
			{
				wsprintf(buff, "%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.SoulPart);//+(int)pShuttle->m_paramFactor.pfp_SOUL_PART) ;
				if(m_StatInfoFont[3])
				{
					m_StatInfoFont[3]->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}			
		}

		// ȸ��
		{			
			fPosX = fAllPosX[STAT_SHUTTLEINFO_DODGE];
			fPosY = fAllPosY[STAT_SHUTTLEINFO_DODGE];		
			if(m_nShowOverStat[STAT_SHUTTLEINFO_DODGE] > 0)
			{
				fPosX = fOverStatPosX[STAT_SHUTTLEINFO_DODGE];
				wsprintf(szOvrbuff, "(+%d)", m_nShowOverStat[STAT_SHUTTLEINFO_DODGE]);
				if(m_StatOverInfoFont)
				{				
					// ���������� �׸���. 
					m_StatOverInfoFont->DrawText(fPosX+OVER_STAT_CAPX, fPosY, GUI_FONT_COLOR_R, szOvrbuff, 0 );
				}
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.DodgePart);//+(int)pShuttle->m_paramFactor.pfp_DODGE_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else if(m_nShowOverStat[STAT_SHUTTLEINFO_DODGE] == 0)
			{
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.DodgePart);//+(int)pShuttle->m_paramFactor.pfp_DODGE_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else
			{
				wsprintf(buff, "%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.DodgePart);//+(int)pShuttle->m_paramFactor.pfp_DODGE_PART) ;
				if(m_StatInfoFont[4])
				{
					m_StatInfoFont[4]->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			
		}

		// ����
		{			
			fPosX = fAllPosX[STAT_SHUTTLEINFO_SHIELD];
			fPosY = fAllPosY[STAT_SHUTTLEINFO_SHIELD];		
			if(m_nShowOverStat[STAT_SHUTTLEINFO_SHIELD] > 0)
			{
				fPosX = fOverStatPosX[STAT_SHUTTLEINFO_SHIELD];
				wsprintf(szOvrbuff, "(+%d)", m_nShowOverStat[STAT_SHUTTLEINFO_SHIELD]);
				if(m_StatOverInfoFont)
				{				
					// ���������� �׸���. 
					m_StatOverInfoFont->DrawText(fPosX+OVER_STAT_CAPX, fPosY, GUI_FONT_COLOR_R, szOvrbuff, 0 );
				}
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.ShieldPart);//+(int)pShuttle->m_paramFactor.pfp_SHIELD_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else if(m_nShowOverStat[STAT_SHUTTLEINFO_SHIELD] == 0)
			{
				wsprintf(buff, "\\e%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.ShieldPart);//+(int)pShuttle->m_paramFactor.pfp_SHIELD_PART) ;
				if(m_StatInfoBoldFont)
				{
					m_StatInfoBoldFont->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}
			else
			{
				wsprintf(buff, "%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.TotalGearStat.ShieldPart);//+(int)pShuttle->m_paramFactor.pfp_SHIELD_PART) ;
				if(m_StatInfoFont[5])
				{
					m_StatInfoFont[5]->DrawText(fPosX, fPosY,GUI_FONT_COLOR, buff, 0 );
				}
			}			
		}
		
		wsprintf(buff, "%4d", (int)g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat) ;
		if(m_StatInfoFont[6])
			m_StatInfoFont[6]->DrawText(nWindowPosX+STATINFO_START_X0-115, nWindowPosY+ SHOWSTATINFO_Y4,
			GUI_FONT_COLOR, buff, 0 );	
		
	}	
	// end 2007-05-15 by bhsohn ��� ���� ���� ó��
	
	if(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0)
	{
		// X��ǥ
		int  nPosX[MAX_STAT_SHUTTLEINFO] =
		{
				nWindowPosX+STATINFO_START_X0+30,		// ����
				nWindowPosX+STATINFO_START_X0+30,		// ���
				nWindowPosX+STATINFO_START_X1+30,		// ����
				nWindowPosX+STATINFO_START_X1+30,		// ����
				nWindowPosX+STATINFO_START_X0+30,		// ȸ��
				nWindowPosX+STATINFO_START_X1+30		// ����
		};
		// Y��ǥ
		int nPosY[MAX_STAT_SHUTTLEINFO] =
		{
				nWindowPosY+ SHOWSTATINFO_Y1+3,				// ����
				nWindowPosY+ SHOWSTATINFO_Y2+3,				// ���	
				nWindowPosY+ SHOWSTATINFO_Y1+3,				// ����
				nWindowPosY+ SHOWSTATINFO_Y2+3,				// ����
				nWindowPosY+ SHOWSTATINFO_Y3+3,				// ȸ��
				nWindowPosY+ SHOWSTATINFO_Y3+3				// ����
		};	

		
		int nPos = 0;
				
		for(nPos = 0; nPos<MAX_STAT_SHUTTLEINFO ; nPos++)
		{
			m_pBonusStatBtn[nPos]->SetBtnPosition(nPosX[nPos], nPosY[nPos]);	
			m_pBonusStatBtn[nPos]->Render();
		}
	}
}

int CINFCharacterInfoExtend::GetUtcMaxScrollNumber()
{
	int Utc[4]={0,0,0,0};
//	map<int,ITEM_SKILL*>::iterator itSkill = g_pShuttleChild->m_pSkill->m_mapSkill.begin();
	map<int,CSkillInfo*>::iterator itSkillInfo = g_pShuttleChild->m_pSkill->m_mapSkill.begin();
	while(itSkillInfo != g_pShuttleChild->m_pSkill->m_mapSkill.end())
	{
		int nTemp = itSkillInfo->second->ItemNum / 1000;
		int nWindowNum = (itSkillInfo->second->ItemNum  % nTemp) / 10 -1;
		Utc[SKILL_KIND(itSkillInfo->second->ItemNum)] = max(Utc[SKILL_KIND(itSkillInfo->second->ItemNum)], nWindowNum) ;
		itSkillInfo++;
	}
	return max(max(Utc[0],Utc[1]),max(Utc[2],Utc[3]));
}

#define C_QUEST_DESC_TEXT_NUM		28
void CINFCharacterInfoExtend::SetQuestDesc(int nQuestWindowDataIndex)
{
	if(nQuestWindowDataIndex < 0)
	{
		m_pQuestListScrollBar->Reset();
		m_pQuestDescScrollBar->Reset();
		m_vecQuestDescription.clear();
		return;
	}
	m_pQuestDescScrollBar->Reset();
	m_vecQuestDescription.clear();
	int index =0;
	map<int, MEX_QUEST_INFO*>::iterator it = g_pQuestData->m_mapCharacterQuest.begin();
	while(it != g_pQuestData->m_mapCharacterQuest.end() )
	{
		if(it->second->QuestState == QUEST_STATE_IN_PROGRESS)
		{
			if(index == nQuestWindowDataIndex)
			{
				break;
			}
			index ++;
		}
		it++;
	}
	if(it == g_pQuestData->m_mapCharacterQuest.end() )
	{
		return;
	}
	CQuest* pQuest = g_pQuestData->FindQuest( it->second->QuestIndex );
	if(pQuest == NULL)
	{
		DBGOUT("CINFCharacterInfoExtend::SetQuestDesc(%d) Can't Find Quest.\n", nQuestWindowDataIndex);
		return;
	}
	if(strlen(pQuest->QuestDescription) == 0)
	{
		DBGOUT("CINFCharacterInfoExtend::SetQuestDesc(%d) Quest (%d) description is empty.\n", nQuestWindowDataIndex, pQuest->QuestIndex);
		return;
	}
	int i = 0;
	int nPoint = 0;
	int nCheckPoint = 0;
	int nBreakPoint = 0;
	int nLine = 0;
	int nLineLength = C_QUEST_DESC_TEXT_NUM;
//	if(strlen(strNPCTalk) > CITY_NPCTALK_SIZE+CITY_NPCTALK_SIZE/2 ||
//		strlen(strNPCTalk) < CITY_NPCTALK_SIZE/3*2)
//	{
//		nLineLength = CITY_NPCTALK_SIZE-1;
//	}
//	else 
//	{
//		nLineLength = strlen(strNPCTalk)/3 * 2 - 1;
//	}
	char szBuffer[MAX_PATH];
	memset( szBuffer, 0x00, MAX_PATH );
	while(TRUE)
	{
		if(pQuest->QuestDescription[i] == ' ' || 
			pQuest->QuestDescription[i] == '.' || 
			pQuest->QuestDescription[i] == '!' || 
			pQuest->QuestDescription[i] == NULL)
		{
			if(nPoint >= nLineLength)
			{
				memcpy( szBuffer, pQuest->QuestDescription + nCheckPoint, nBreakPoint+1);
				m_vecQuestDescription.push_back( (string)szBuffer );
				memset( szBuffer, 0x00, MAX_PATH );
				
				nPoint -= nBreakPoint;
				nCheckPoint += nBreakPoint+1;
				nBreakPoint = nPoint-1;
				nLine ++;
				i++;
				continue;
			}
			if(pQuest->QuestDescription[i] == NULL)
			{
				memcpy( szBuffer, pQuest->QuestDescription + nCheckPoint, nPoint);
				m_vecQuestDescription.push_back( (string)szBuffer );
				memset( szBuffer, 0x00, MAX_PATH );
				break;
			}
			nBreakPoint = nPoint;
		}
		i++;
		nPoint++;
	}
	if(pQuest->IsCityWar)
	{
		wsprintf( szBuffer, STRMSG_C_QUEST_0009, it->second->szCityWarServerGroupName );//"����:%s"
		m_vecQuestDescription.push_back( (string)szBuffer );
	}
	m_pQuestDescScrollBar->SetNumberOfData( m_vecQuestDescription.size() );
}
void CINFCharacterInfoExtend::RenderNonQuest(int nWindowPosY, int nLine)
{
	int nWindowPosX = m_ptBkPos.x;
	nWindowPosY = m_ptBkPos.y;

	// ����Ʈ ���� ������Ʈ
	g_pQuestData->NotifyStartQuest();
	int mScrollIndex	= m_pQuestListScrollBar->GetCurrentScrollIndex() - m_nMissionProCount;
	
	vector<Quest_Data*>::iterator it = g_pQuestData->m_vecQuest.begin();
	while(it != g_pQuestData->m_vecQuest.end())
	{		
		Quest_Data* pInfo = (*it);
		if(mScrollIndex <= 0 && nLine < C_QUEST_LIST_NUM)
		{
			m_pFontQuestList[nLine]->DrawText(C_QUEST_START_X,
				nWindowPosY+C_QUEST_START_Y+C_QUEST_INTERVAL*nLine+1,
				RGB(128,128,255),
				pInfo->szMissionName);
			/////////////////////////////////////////////////////////////////////////////////////////////
			// ����
			if(m_pQuestListScrollBar->GetCurrentSelectWindowIndex() == nLine)
			{
				char buffChar[1024];
				memset(buffChar, 0x00, 1024);
				
				m_pFontQuestDesc[0]->DrawText(C_QUEST_DESC_START_X+1,
					nWindowPosY+C_QUEST_DESC_START_Y+0*C_QUEST_DESC_INTERVAL+1,
					GUI_FONT_COLOR_Y,
					STRMSG_C_QUEST_0010 );//"�̼�����"

				CQuest* pQuest = g_pQuestData->FindQuest( pInfo->nIndex );
				if(pQuest->ReqLevel.Max > 100)
				{
					wsprintf(buffChar, STRMSG_C_QUEST_0011, pQuest->ReqLevel.Min);//"���ѷ���: %d ~"
				}
				else
				{
					wsprintf(buffChar, STRMSG_C_QUEST_0012,pQuest->ReqLevel.Min, pQuest->ReqLevel.Max);//"���ѷ���: %d ~ %d "
				}				
				m_pFontQuestDesc[2]->DrawText(C_QUEST_DESC_START_X+1,
					nWindowPosY+C_QUEST_DESC_START_Y+2*C_QUEST_DESC_INTERVAL+1,
					GUI_FONT_COLOR,
					buffChar );

				memset(buffChar, 0x00, 1024);
				wsprintf(buffChar, STRMSG_C_QUEST_0013, pInfo->szMAPName);//"��:%s"
				m_pFontQuestDesc[3]->DrawText(C_QUEST_DESC_START_X+1,
					nWindowPosY+C_QUEST_DESC_START_Y+3*C_QUEST_DESC_INTERVAL+1,
					GUI_FONT_COLOR,
					buffChar );

				memset(buffChar, 0x00, 1024);
				wsprintf(buffChar, "NPC: %s", pInfo->szNPCName);
				m_pFontQuestDesc[4]->DrawText(C_QUEST_DESC_START_X+1,
					nWindowPosY+C_QUEST_DESC_START_Y+4*C_QUEST_DESC_INTERVAL+1,
					GUI_FONT_COLOR,
					buffChar );				
			}
			//
			///////////////////////////////////////////////////////////////////////////////////////////////	

			nLine++;			
		}		
		mScrollIndex--;
		it++;
	}
}	
		
void CINFCharacterInfoExtend::RenderStatDescToolTip(int nType, int x, int y)
{
	char buff[512];
	ZERO_MEMORY(buff);
	
	switch(nType) {
	case AUTOSTAT_TYPE_FREESTYLE:			wsprintf(buff, STRMSG_C_TOOLTIP_0021);	break;// "���ϴ� ���·� ���������� ���� ����"
	case AUTOSTAT_TYPE_BGEAR_ATTACK:		wsprintf(buff, STRMSG_C_TOOLTIP_0022);	break;// "���ݷ��� ��ȭ�� ���� ����"
	case AUTOSTAT_TYPE_BGEAR_MULTI:			wsprintf(buff, STRMSG_C_TOOLTIP_0023);	break;// "�پ��� ��Ƽ��� ���� ����"
	case AUTOSTAT_TYPE_IGEAR_ATTACK:		wsprintf(buff, STRMSG_C_TOOLTIP_0022);	break;// "���ݷ��� ��ȭ�� ���� ����"
	case AUTOSTAT_TYPE_IGEAR_DODGE:			wsprintf(buff, STRMSG_C_TOOLTIP_0024);	break;// "ȸ�Ƿ��� ��ȭ�� ���� ����"
	case AUTOSTAT_TYPE_AGEAR_ATTACK:		wsprintf(buff, STRMSG_C_TOOLTIP_0022);	break;// "���ݷ��� ��ȭ�� ���� ����"
	case AUTOSTAT_TYPE_AGEAR_SHIELD:		wsprintf(buff, STRMSG_C_TOOLTIP_0025);	break;// "�������� ��ȭ�� ���� ����"
	case AUTOSTAT_TYPE_MGEAR_DEFENSE:		wsprintf(buff, STRMSG_C_TOOLTIP_0026);	break;// "������ ��ȭ�� ���� ����"
	case AUTOSTAT_TYPE_MGEAR_SUPPORT:		wsprintf(buff, STRMSG_C_TOOLTIP_0027);	break;// "����� �����ɷ��� ��ȭ�� ���� ����"
	}

	g_pGameMain->RenderPopUpWindowImage(x, y, strlen(buff)*6.5, 1);
	m_pFontStatDec->DrawText(x, y, GUI_FONT_COLOR,buff);
}

int CINFCharacterInfoExtend::AmmoWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			int nWindowPosX = m_ptBkPos.x;
			int nWindowPosY = m_ptBkPos.y;

			POINT ptBkSize = m_pInoBk->GetImgSize();
			if(pt.y>nWindowPosY &&
				pt.y<nWindowPosY+ptBkSize.y&&
				pt.x>nWindowPosX &&
				pt.x<nWindowPosX + ptBkSize.x)
			{
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCharacterInfoExtend::CheckUseSkillApprovalEnd(ITEM_BASE* pSkill)
/// \brief		������� ��ų ���� �㰡 üũ
/// \author		ispark
/// \date		2006-07-30 ~ 2006-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCharacterInfoExtend::CheckUseSkillApprovalEnd(ITEM_BASE* pSkill)
{
	CSkillInfo* pSkillInfo = g_pShuttleChild->m_pSkill->FindUsingSkillInfo(pSkill->ItemNum);
	if(pSkillInfo && pSkillInfo->GetbApprovalEnd() == FALSE)
	{
		// ��ų�� ����� ���� ������
		if(g_pInterface->m_pBazaarShop &&
			pSkill->UniqueNumber == pSkillInfo->UniqueNumber &&
			IS_BAZAAR_SKILL(pSkillInfo->ItemInfo))
		{
			// 2006-08-01 by ispark, ������ �����̸�
			if(g_pInterface->m_pBazaarShop->GetbBazaarShopStart())
			{
				char msgBox[256] = {0,};
				if(g_pInterface->m_pBazaarShop->GetbBazaarShopType() == 1)
				{
					wsprintf(msgBox, STRMSG_C_060730_0000, STRMSG_C_060730_0002);		// "%s ������ �����Ͻðڽ��ϱ�?"
				}	
				else if(g_pInterface->m_pBazaarShop->GetbBazaarShopType() == 2)
				{
					wsprintf(msgBox, STRMSG_C_060730_0000, STRMSG_C_060730_0003);		// "%s ������ �����Ͻðڽ��ϱ�?"
				}
				g_pGameMain->m_pInfWindow->AddMsgBox(msgBox, _Q_BAZAAR_OPEN_SHOP_END, (DWORD)pSkillInfo);

				return FALSE;
			}
		}
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		������ ������ ���� ����
/// \author		// 2007-05-15 by bhsohn ��� ���� ���� ó��
/// \date		2007-05-15 ~ 2007-05-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::GetStatShowInfo()
{	
	//(m_bStatShow, m_nShowOverStat)
	// ��ü ���� 
	GEAR_STAT stMyShuttleFullStatInfo = g_pD3dApp->m_pShuttleChild->GetMyShuttleFullStatInfo();	

	// 2009. 12. 29 by ckPark ���� 100���� ĳ���ʹ� �ִ뽺�� 300, ���� 100�ʰ� ĳ���ʹ� �ִ뽺�� 340 ����

// 	// ����
// 	m_bStatShow[STAT_SHUTTLEINFO_ATTACK] = TRUE;
// 	m_nShowOverStat[STAT_SHUTTLEINFO_ATTACK] = stMyShuttleFullStatInfo.AttackPart - COUNT_MAX_STAT_POINT;		
// 	if(stMyShuttleFullStatInfo.AttackPart >= COUNT_MAX_STAT_POINT)
// 	{
// 		m_bStatShow[STAT_SHUTTLEINFO_ATTACK] = FALSE;				
// 	}	
// 	m_pBonusStatBtn[STAT_SHUTTLEINFO_ATTACK]->ShowWindow(m_bStatShow[STAT_SHUTTLEINFO_ATTACK]);
// 
// 	// ���
// 	m_bStatShow[STAT_SHUTTLEINFO_DEFENCE] = TRUE;
// 	m_nShowOverStat[STAT_SHUTTLEINFO_DEFENCE] = stMyShuttleFullStatInfo.DefensePart - COUNT_MAX_STAT_POINT;		
// 	if(stMyShuttleFullStatInfo.DefensePart >= COUNT_MAX_STAT_POINT)
// 	{
// 		m_bStatShow[STAT_SHUTTLEINFO_DEFENCE] = FALSE;		
// 	}	
// 	m_pBonusStatBtn[STAT_SHUTTLEINFO_DEFENCE]->ShowWindow(m_bStatShow[STAT_SHUTTLEINFO_DEFENCE]);
// 
// 	// ����
// 	m_bStatShow[STAT_SHUTTLEINFO_FUEL] = TRUE;
// 	m_nShowOverStat[STAT_SHUTTLEINFO_FUEL] = stMyShuttleFullStatInfo.FuelPart - COUNT_MAX_STAT_POINT;		
// 	if(stMyShuttleFullStatInfo.FuelPart >= COUNT_MAX_STAT_POINT)
// 	{
// 		m_bStatShow[STAT_SHUTTLEINFO_FUEL] = FALSE;		
// 	}	
// 	m_pBonusStatBtn[STAT_SHUTTLEINFO_FUEL]->ShowWindow(m_bStatShow[STAT_SHUTTLEINFO_FUEL]);
// 
// 	// ����
// 	m_bStatShow[STAT_SHUTTLEINFO_SOUL] = TRUE;
// 	m_nShowOverStat[STAT_SHUTTLEINFO_SOUL] = stMyShuttleFullStatInfo.SoulPart - COUNT_MAX_STAT_POINT;		
// 	if(stMyShuttleFullStatInfo.SoulPart >= COUNT_MAX_STAT_POINT)
// 	{
// 		m_bStatShow[STAT_SHUTTLEINFO_SOUL] = FALSE;	
// 	}	
// 	m_pBonusStatBtn[STAT_SHUTTLEINFO_SOUL]->ShowWindow(m_bStatShow[STAT_SHUTTLEINFO_SOUL]);
// 
// 	// ȸ��
// 	m_bStatShow[STAT_SHUTTLEINFO_DODGE] = TRUE;
// 	m_nShowOverStat[STAT_SHUTTLEINFO_DODGE] = stMyShuttleFullStatInfo.DodgePart - COUNT_MAX_STAT_POINT;
// 	if(stMyShuttleFullStatInfo.DodgePart >= COUNT_MAX_STAT_POINT)
// 	{
// 		m_bStatShow[STAT_SHUTTLEINFO_DODGE] = FALSE;		
// 	}	
// 	m_pBonusStatBtn[STAT_SHUTTLEINFO_DODGE]->ShowWindow(m_bStatShow[STAT_SHUTTLEINFO_DODGE]);
// 	
// 	// ����
// 	m_bStatShow[STAT_SHUTTLEINFO_SHIELD] = TRUE;
// 	m_nShowOverStat[STAT_SHUTTLEINFO_SHIELD] = stMyShuttleFullStatInfo.ShieldPart - COUNT_MAX_STAT_POINT;		
// 	if(stMyShuttleFullStatInfo.ShieldPart >= COUNT_MAX_STAT_POINT)
// 	{
// 		m_bStatShow[STAT_SHUTTLEINFO_SHIELD] = FALSE;		
// 	}		
// 	m_pBonusStatBtn[STAT_SHUTTLEINFO_SHIELD]->ShowWindow(m_bStatShow[STAT_SHUTTLEINFO_SHIELD]);

	int nLv = g_pD3dApp->m_pShuttleChild->GetMyShuttleInfo().Level;
	for( int i=0; i<MAX_STAT_SHUTTLEINFO; ++i )
	{
		int nStat = 0;
		switch( i )
		{
		case STAT_SHUTTLEINFO_ATTACK:
			nStat = stMyShuttleFullStatInfo.AttackPart;
			break;
		case STAT_SHUTTLEINFO_DEFENCE:
			nStat = stMyShuttleFullStatInfo.DefensePart;
			break;
		case STAT_SHUTTLEINFO_FUEL:
			nStat = stMyShuttleFullStatInfo.FuelPart;
			break;
		case STAT_SHUTTLEINFO_SOUL:
			nStat = stMyShuttleFullStatInfo.SoulPart;
			break;
		case STAT_SHUTTLEINFO_DODGE:
			nStat = stMyShuttleFullStatInfo.DodgePart;
			break;
		case STAT_SHUTTLEINFO_SHIELD:
			nStat = stMyShuttleFullStatInfo.ShieldPart;
			break;
		}

		m_bStatShow[i] = TRUE;
		if( (nLv <= CHARACTER_LEVEL_100 && nStat >= CHARACTER_LEVEL_100_MAX_STAT_POINT)
			|| (nLv > CHARACTER_LEVEL_100 && nStat >= CHARACTER_LEVEL_110_MAX_STAT_POINT) )
		{
			m_bStatShow[i] = FALSE;
		}
		m_pBonusStatBtn[i]->ShowWindow(m_bStatShow[i]);

		if( nLv <= CHARACTER_LEVEL_100 )
			m_nShowOverStat[i] = nStat - CHARACTER_LEVEL_100_MAX_STAT_POINT;
		else if( nLv > CHARACTER_LEVEL_100 )
			m_nShowOverStat[i] = nStat - CHARACTER_LEVEL_110_MAX_STAT_POINT;
	}

	// end 2009. 12. 29 by ckPark ���� 100���� ĳ���ʹ� �ִ뽺�� 300, ���� 100�ʰ� ĳ���ʹ� �ִ뽺�� 340 ����
}

void CINFCharacterInfoExtend::SetCharacterInfoType(int nCharacterInfoType)
{
	m_nCharacterInfoType = nCharacterInfoType;
}

void CINFCharacterInfoExtend::ShowCharacterInfoWnd(BOOL bShowWnd, POINT* pPos/*=NULL*/)
{
	m_bShowWnd = bShowWnd;
	if(pPos)
	{
		m_ptBkPos = (*pPos);
	}
	else
	{
		POINT ptSize = m_pInoBk->GetImgSize();
		m_ptBkPos.x = (g_pD3dApp->GetBackBufferDesc().Width-ptSize.x)/2;
		m_ptBkPos.y = (g_pD3dApp->GetBackBufferDesc().Height-ptSize.y)/2;
	}	
	if(bShowWnd)
	{
		int nTemp = m_nCurrentUTCScroll;
		// ��ũ�� �ʱ�ȭ
		m_nCurrentUTCScroll = 0;
		if(m_nCurrentUTCScroll>GetUtcMaxScrollNumber())
		{
			m_nCurrentUTCScroll = GetUtcMaxScrollNumber();
		}				
					
		if(nTemp != m_nCurrentUTCScroll)
		{
			SetAllUTCInfo();
		}

		m_bMove = FALSE;
		m_ptCommOpMouse.x = m_ptCommOpMouse.y = 0;
		g_pInterface->SetWindowOrder(WNDCharacterWnd);		

		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
		if(m_pNickNameBtn)
		{
			CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
			if(0 == strlen(myShuttleInfo.NickName))
			{
				// ������ ����.
				m_pNickNameBtn->ShowWindow(TRUE);
			}
			else
			{
				m_pNickNameBtn->ShowWindow(FALSE);
			}
			if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING )
			{
				// �Ʒ��� ���� ����
				m_pNickNameBtn->ShowWindow(FALSE);
			}

		}
		// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	}
}

BOOL CINFCharacterInfoExtend::IsShowWnd()
{
	return m_bShowWnd;
}

void CINFCharacterInfoExtend::RenderCommandInfo()
{
	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;	
	char buff[MAX_PATH];
	memset(buff, 0x00, MAX_PATH);

	if(m_pInoBk )
	{
		m_pInoBk->Move(nWindowPosX, nWindowPosY);
		m_pInoBk->Render() ;
	}
	SIZE szSize = {0,0};

		
	wsprintf(buff, "%d", g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Level);	
	szSize = m_pFontLevel->GetStringSize(buff);
	m_pFontLevel->DrawText(	nWindowPosX + INFO_LEVEL_START_X - szSize.cx,
							nWindowPosY + INFO_LEVEL_START_Y, 
							GUI_FONT_COLOR, 
							buff, 0 );

	char szCharacterName[SIZE_MAX_ARENA_FULL_NAME];
	memset(szCharacterName, 0x00, SIZE_MAX_ARENA_FULL_NAME);
	strncpy(szCharacterName, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.CharacterName, SIZE_MAX_CHARACTER_NAME);
	g_pD3dApp->ConevertArenaRenderUserName(g_pD3dApp->GetArenaState(), szCharacterName);	
	m_pFontName->DrawText(nWindowPosX+INFO_ID_START_X ,
							nWindowPosY+ INFO_ID_START_Y, 
							GUI_FONT_COLOR, szCharacterName, 0 );	
	
	//
	CINFImage* pFace = ((CInterface*)m_pParent->m_pParent)->m_pPilotFace->FindPilotImage(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.PilotFace);
	if(pFace)
	{
		pFace->Move(nWindowPosX+26,nWindowPosY + 57);
		pFace->Render();
	}	
	if( g_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber != 0 )
	{
		wsprintf(buff, "%s", g_pShuttleChild->m_myShuttleInfo.GuildName );//"�Ҽ�:%s"					
		szSize = m_pFontGuild->GetStringSize(buff);
		m_pFontGuild->DrawText( nWindowPosX+GUILD_START_X-szSize.cx, 
			nWindowPosY + GUILD_START_Y, 
			GUI_FONT_COLOR, buff, 0 );

		CINFImage* pMark = g_pDatabase->GetGuildMark(g_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber);
		if(pMark)
		{
			pMark->Move(nWindowPosX+GUILD_START_X-szSize.cx-30, nWindowPosY + GUILD_MARK_START_Y);
			pMark->Render();
		}		
	}
	
	wsprintf(buff, "%s", (LPTSTR)CAtumSJ::GetStatusByLevel(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Level) );//"�ź�:%s"	
	szSize = m_pFontGeneral->GetStringSize(buff);
	m_pFontGeneral->DrawText( nWindowPosX + GENERAL_START_X - szSize.cx,
		nWindowPosY + GENERAL_START_Y, 
								GUI_FONT_COLOR, buff,0 );
	
	wsprintf(buff,"%d",g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.Propensity);//"��:%d"	
	szSize = m_pFontPropensity->GetStringSize(buff);
	m_pFontPropensity->DrawText( nWindowPosX+PROPENSITY_START_X - szSize.cx,
		nWindowPosY + PROPENSITY_START_Y, 
		GUI_FONT_COLOR, buff,0 );
	
	wsprintf(buff, STRMSG_C_080923_0203, g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.PKWinPoint,g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.PKLossPoint);//"������:%3d�� %3d��"	
	szSize = m_pFontGuild->GetStringSize(buff);
	m_pFontGuild->DrawText( nWindowPosX + PERSONAL_STAT_X - szSize.cx,
								nWindowPosY + PERSONAL_STAT_Y, 
								GUI_FONT_COLOR, buff, 0 );
	
	// ��� ��
	if( g_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber != 0 )
	{
		MSG_IC_GUILD_GET_GUILD_INFO_OK *pInfo = g_pGameMain->m_pCommunity->GetGuild()->GetGuildInfo();
		if(pInfo)
		{
			wsprintf(buff, STRMSG_C_080923_0203, pInfo->WarWinPoint, pInfo->WarLossPoint);//"�����:%3d�� %3d��"			
			szSize = m_pFontGuild->GetStringSize(buff);
			m_pFontGuild->DrawText( nWindowPosX + GUILDWAR_STAT_X - szSize.cx, 
				nWindowPosY + GUILDWAR_STAT_Y, 
				GUI_FONT_COLOR, buff, 0 );
		}
	}
		
	
	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	if(m_pOpenBtn)
	{				
		int nPosX = nWindowPosX + 415;
		int	nPosY = nWindowPosY + 149;
		
		m_pOpenBtn->SetBtnPosition(nPosX, nPosY);	
		m_pOpenBtn->Render();			
	}	
	if(m_pCloseBtn)
	{				
		int nPosX = nWindowPosX + 490;
		int	nPosY = nWindowPosY + 7;
		
		m_pCloseBtn->SetBtnPosition(nPosX, nPosY);	
		m_pCloseBtn->Render();			
	}
	// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	if(m_pNickNameBtn)
	{
		int nPosX = nWindowPosX + 203;
		int	nPosY = nWindowPosY + 128;

		CHARACTER myShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
		if(0 == strlen(myShuttleInfo.NickName) && !m_pNickNameBtn->IsShowWindow())
		{
			// ������ ����.
			m_pNickNameBtn->ShowWindow(TRUE);
		}
		else if((strlen(myShuttleInfo.NickName) > 0) && m_pNickNameBtn->IsShowWindow())
		{
			m_pNickNameBtn->ShowWindow(FALSE);
		}
		if(g_pD3dApp->GetArenaState() == ARENA_STATE_ARENA_GAMING && m_pNickNameBtn->IsShowWindow())
		{
			// �Ʒ��� ���� ����
			m_pNickNameBtn->ShowWindow(FALSE);
		}
		
		if(m_pNickNameBtn->IsShowWindow())
		{
			m_pNickNameBtn->SetBtnPosition(nPosX, nPosY);	
			m_pNickNameBtn->Render();
		}
		else
		{
			wsprintf(buff, "%s", myShuttleInfo.NickName);
			szSize = m_pFontNickName->GetStringSize(buff);
			m_pFontNickName->DrawText( nWindowPosX + WR_NICKNAME_START_X - szSize.cx, 
										nWindowPosY + WR_NICKNAME_START_Y, 
										GUI_FONT_COLOR, buff, 0 );			

		}
	}
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

	
}

void CINFCharacterInfoExtend::RenderCharacterInfo()
{

	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;
	char buff[MAX_PATH];	
	SIZE szSizeTmp={0,0};
	SIZE szSize = {0,0};
	memset(buff, 0x00, MAX_PATH);

	if(m_pInfo )
	{
		m_pInfo->Move(nWindowPosX+22,nWindowPosY + 153);
		m_pInfo->Render() ;
	}

	RenderShowStatInfo() ;
	
	
	// �Ƹ� ����
	
	{
//		if(m_pAmmo )
//		{
//			m_pAmmo->Move(nWindowPosX+12,nWindowPosY + 48);
//			m_pAmmo->Render() ;
//		}
		
		CItemInfo * pArmorItemInfo = g_pStoreData->FindItemInInventoryByWindowPos( POS_CENTER );

		CParamFactor paramCharctorParam = (*g_pShuttleChild->GetShuttleParamFactor());
		
		if(pArmorItemInfo)
		{
			CParamFactor * pParamArmor = pArmorItemInfo->GetEnchantParamFactor();
			if(pParamArmor)
			{
				paramCharctorParam += (*pParamArmor);
			}
		}		
		
		{
			sprintf( buff, STRMSG_C_080923_0200, ((float)CAtumSJ::GetDefenseC( &g_pShuttleChild->m_myShuttleInfo, 
							// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
							//&paramCharctorParam, TRUE ) / PROB256_MAX_VALUE)*100.0f );//"���� �⺻���� : %.2f%%"
							&paramCharctorParam, TRUE ) / PROB100_MAX_VALUE)*100.0f );//"���� �⺻���� : %.2f%%"
			szSize = m_CharacInfoFont[0]->GetStringSize(buff);
			m_CharacInfoFont[0]->DrawText(nWindowPosX+INFO_START_X - szSize.cx, 
				nWindowPosY+OTHER_INFO_START_Y,
				GUI_FONT_COLOR, buff, 0 );
			
			sprintf( buff, STRMSG_C_080923_0200, ((float)CAtumSJ::GetDefenseC( &g_pShuttleChild->m_myShuttleInfo, 
							// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
							//&paramCharctorParam, FALSE ) / PROB256_MAX_VALUE)*100.0f );//"       ��޹��� : %.2f%%"
							&paramCharctorParam, FALSE ) / PROB100_MAX_VALUE)*100.0f );//"       ��޹��� : %.2f%%"
			szSize = m_CharacInfoFont[0]->GetStringSize(buff);
			m_CharacInfoFont[1]->DrawText(nWindowPosX+INFO_START_X- szSize.cx, 
				nWindowPosY+OTHER_INFO_START_Y+INFO_INTERVAL,
				GUI_FONT_COLOR, buff, 0 );

			sprintf( buff, STRMSG_C_080923_0200, //"ȸ�Ƿ� �⺻���� : %.2f%%"
				(CAtumSJ::GetDefenseProbabilityC( &g_pShuttleChild->m_myShuttleInfo, 
				// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
				//(pArmorItemInfo==NULL?NULL:pArmorItemInfo->GetRealItemInfo()), &paramCharctorParam, TRUE ) / PROB256_MAX_VALUE)*100.0f );
				(pArmorItemInfo==NULL?NULL:pArmorItemInfo->GetRealItemInfo()), &paramCharctorParam, TRUE ) / PROB100_MAX_VALUE)*100.0f );
			szSize = m_CharacInfoFont[3]->GetStringSize(buff);
			m_CharacInfoFont[3]->DrawText(nWindowPosX+INFO_START_X+INFO_START_INTERVAL_X - szSize.cx, 
										nWindowPosY+OTHER_INFO_START_Y,
										GUI_FONT_COLOR, buff, 0 );
		
			sprintf( buff, STRMSG_C_080923_0200, //"       ��޹��� : %.2f%%"
				(CAtumSJ::GetDefenseProbabilityC( &g_pShuttleChild->m_myShuttleInfo, 
				// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
				//(pArmorItemInfo==NULL?NULL:pArmorItemInfo->GetRealItemInfo()), &paramCharctorParam, FALSE ) / PROB256_MAX_VALUE)*100.0f );
				(pArmorItemInfo==NULL?NULL:pArmorItemInfo->GetRealItemInfo()), &paramCharctorParam, FALSE ) / PROB100_MAX_VALUE)*100.0f );
			szSize = m_CharacInfoFont[4]->GetStringSize(buff);
			m_CharacInfoFont[4]->DrawText(nWindowPosX+INFO_START_X+INFO_START_INTERVAL_X - szSize.cx, 
										nWindowPosY+OTHER_INFO_START_Y+INFO_INTERVAL,
										GUI_FONT_COLOR, buff, 0 );
		}
		
		
		
		
		
		if(g_pShuttleChild->m_pPrimaryWeapon)
		{
			CItemInfo *	pPrimaryItemInfo = g_pShuttleChild->m_pPrimaryWeapon->GetClassItemInfo();			
			CParamFactor paramPrimaryParam = (*g_pShuttleChild->GetShuttleParamFactor());		

			// 2008-11-11 by bhsohn Ȯ�� ���� �߸� ���� ���� ����
//			if(pPrimaryItemInfo)
//			{
//				//CParamFactor * pParamPrimaryWeapon = pPrimaryItemInfo->GetEnchantParamFactor();
//				CParamFactor * pParamPrimaryWeapon = pPrimaryItemInfo->GetParamFactor();
//				if(pParamPrimaryWeapon)
//				{
//					paramPrimaryParam += (*pParamPrimaryWeapon);
//				}
//			}		
			// end 2008-11-11 by bhsohn Ȯ�� ���� �߸� ���� ���� ����

			
			{
				// 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����

// 				sprintf( buff, STRMSG_C_080923_0200,//"����Ȯ�� : %.2f"
// 					(CAtumSJ::GetAttackProbabilityC(g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo(), 
// 					&paramPrimaryParam, 
// 					TRUE, g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart )*100)/255);	// ĳ������ ���� Ȯ��

				sprintf( buff, STRMSG_C_080923_0200,//"����Ȯ�� : %.2f"
						// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
						 //(CAtumSJ::GetAttackProbabilityC(g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo(),&paramPrimaryParam,
						 //TRUE, g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart, g_pShuttleChild->m_myShuttleInfo.Level )*100)/255);	// ĳ������ ���� Ȯ��
						 (CAtumSJ::GetAttackProbabilityC(g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo(),&paramPrimaryParam,
						 TRUE, g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart, g_pShuttleChild->m_myShuttleInfo.Level )*100)/PROB100_MAX_VALUE);	// ĳ������ ���� Ȯ��

				// end 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����

				szSize = m_pFontAmmoWeapon[0]->GetStringSize(buff);
				m_pFontAmmoWeapon[0]->DrawText( nWindowPosX+AMMO_START_X-szSize.cx, 
												nWindowPosY + AMMO_START_Y, GUI_FONT_COLOR, buff, 0L );
			}
			{			
				//"�Ǿ : %.2f"
				float fTotalPierce = g_pShuttleChild->m_pPrimaryWeapon->GetTotalPierce(TRUE);					
				sprintf( buff, STRMSG_C_080923_0200, fTotalPierce);
				
				szSize = m_pFontAmmoWeapon[0]->GetStringSize(buff);
				m_pFontAmmoWeapon[0]->DrawText( nWindowPosX+AMMO_START_X-szSize.cx, 
												nWindowPosY + AMMO_START_Y+(AMMO_INTERVAL), GUI_FONT_COLOR, buff, 0L );
			}

			{
				//"���ݷ� : %.2f ~ %.2f"
				sprintf( buff, STRMSG_C_080923_0201, 
					CAtumSJ::GetMinAttackC(&g_pShuttleChild->m_myShuttleInfo, g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo(), &paramPrimaryParam, TRUE ), 
					CAtumSJ::GetMaxAttackC(&g_pShuttleChild->m_myShuttleInfo, g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo(), &paramPrimaryParam, TRUE ) );
				szSize = m_pFontAmmoWeapon[0]->GetStringSize(buff);
				m_pFontAmmoWeapon[0]->DrawText( nWindowPosX+AMMO_START_X-szSize.cx, 
												nWindowPosY + AMMO_START_Y+(AMMO_INTERVAL*2), GUI_FONT_COLOR, buff, 0L );
			}
			{
				sprintf( buff, STRMSG_C_080923_0201, CAtumSJ::GetMinAttackPerSecondC(&g_pShuttleChild->m_myShuttleInfo, //"�ʴ���ݷ� : %.2f ~ %.2f"
					g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo(), &paramPrimaryParam, TRUE ), 
					CAtumSJ::GetMaxAttackPerSecondC(&g_pShuttleChild->m_myShuttleInfo, 
					g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo(), &paramPrimaryParam, TRUE ) );
				szSize = m_pFontAmmoWeapon[1]->GetStringSize(buff);
				m_pFontAmmoWeapon[1]->DrawText( nWindowPosX+AMMO_START_X-szSize.cx, nWindowPosY + AMMO_START_Y+(AMMO_INTERVAL*3), GUI_FONT_COLOR, buff, 0L );				
				
			}			
		}
		else
		{
			float fStatPierce = GetDefaultPierce(TRUE);			
			float fItemPierce = g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_01;						
			// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
			//fItemPierce = ((float)fItemPierce / (float)PROB256_MAX_VALUE *100.0f);
			fItemPierce = ((float)fItemPierce / (float)PROB100_MAX_VALUE *100.0f);

			// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���
			fStatPierce = FloatSecRangeSharp(fStatPierce);
			fItemPierce = FloatSecRangeSharp(fItemPierce);

			sprintf( buff, STRMSG_C_080923_0200, (fStatPierce+fItemPierce));			

			szSize = m_pFontAmmoWeapon[0]->GetStringSize(buff);
			m_pFontAmmoWeapon[0]->DrawText( nWindowPosX+AMMO_START_X-szSize.cx, 
												nWindowPosY + AMMO_START_Y+(AMMO_INTERVAL), GUI_FONT_COLOR, buff, 0L );
		}
		if(g_pShuttleChild->m_pSecondaryWeapon)
		{
			CItemInfo *	pSecondItemInfo = g_pShuttleChild->m_pSecondaryWeapon->GetClassItemInfo();			
			CParamFactor paramSecondParam = (*g_pShuttleChild->GetShuttleParamFactor());		

			// 2008-11-11 by bhsohn Ȯ�� ���� �߸� ���� ���� ����
//			if(pSecondItemInfo)
//			{
//				CParamFactor * pParamSecondWeapon = pSecondItemInfo->GetEnchantParamFactor();
//				if(pParamSecondWeapon)
//				{
//					paramSecondParam += (*pParamSecondWeapon);
//				}
//			}
			// end 2008-11-11 by bhsohn Ȯ�� ���� �߸� ���� ���� ����
			
			{
				// 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����

// 				sprintf( buff, STRMSG_C_080923_0200,//"����Ȯ�� : %.2f"
// 					(CAtumSJ::GetAttackProbabilityC(g_pShuttleChild->m_pSecondaryWeapon->GetRealItemInfo(),
// 					&paramSecondParam, FALSE, g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart)*100)/255 );	// ĳ������ ���� Ȯ��

				sprintf( buff, STRMSG_C_080923_0200,//"����Ȯ�� : %.2f"
						// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
						// (CAtumSJ::GetAttackProbabilityC(g_pShuttleChild->m_pSecondaryWeapon->GetRealItemInfo(),
						// &paramSecondParam, FALSE, g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart, g_pShuttleChild->m_myShuttleInfo.Level)*100)/255 );	// ĳ������ ���� Ȯ��
						(CAtumSJ::GetAttackProbabilityC(g_pShuttleChild->m_pSecondaryWeapon->GetRealItemInfo(),
						 &paramSecondParam, FALSE, g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart, g_pShuttleChild->m_myShuttleInfo.Level)*100)/PROB100_MAX_VALUE);	// ĳ������ ���� Ȯ��

				// end 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����

				szSize = m_pFontAmmoWeapon[2]->GetStringSize(buff);
				m_pFontAmmoWeapon[2]->DrawText( nWindowPosX + AMMO_START_X+AMMO_START_INTERVAL_X-szSize.cx, 
					nWindowPosY + AMMO_START_Y, GUI_FONT_COLOR, buff, 0L );
				
			}

			{				
				//"�Ǿ : %.2f"
				float fTotalPierce = g_pShuttleChild->m_pSecondaryWeapon->GetTotalPierce(FALSE);					
				sprintf( buff, STRMSG_C_080923_0200, fTotalPierce);				
				
				szSize = m_pFontAmmoWeapon[2]->GetStringSize(buff);
				m_pFontAmmoWeapon[2]->DrawText( nWindowPosX+AMMO_START_X+AMMO_START_INTERVAL_X-szSize.cx, 
												nWindowPosY + AMMO_START_Y+(AMMO_INTERVAL), GUI_FONT_COLOR, buff, 0L );
			}

			{
				//"���ݷ� : %.2f ~ %.2f"
				sprintf( buff, STRMSG_C_080923_0201, 
					CAtumSJ::GetMinAttackC(&g_pShuttleChild->m_myShuttleInfo,g_pShuttleChild->m_pSecondaryWeapon->GetRealItemInfo(), &paramSecondParam, FALSE ), 
					CAtumSJ::GetMaxAttackC(&g_pShuttleChild->m_myShuttleInfo, g_pShuttleChild->m_pSecondaryWeapon->GetRealItemInfo(), &paramSecondParam, FALSE ));				
				szSize = m_pFontAmmoWeapon[2]->GetStringSize(buff);
				m_pFontAmmoWeapon[2]->DrawText( nWindowPosX+AMMO_START_X+AMMO_START_INTERVAL_X-szSize.cx, 
								nWindowPosY + AMMO_START_Y+(AMMO_INTERVAL*2), GUI_FONT_COLOR, buff, 0L );
			}
			
			{
				sprintf( buff, STRMSG_C_080923_0201, CAtumSJ::GetMinAttackPerSecondC(&g_pShuttleChild->m_myShuttleInfo, 
					g_pShuttleChild->m_pSecondaryWeapon->GetRealItemInfo(), &paramSecondParam, FALSE ), 
					CAtumSJ::GetMaxAttackPerSecondC(&g_pShuttleChild->m_myShuttleInfo, 
					g_pShuttleChild->m_pSecondaryWeapon->GetRealItemInfo(), &paramSecondParam, FALSE ) );
				szSize = m_pFontAmmoWeapon[3]->GetStringSize(buff);
				m_pFontAmmoWeapon[3]->DrawText( nWindowPosX + AMMO_START_X+AMMO_START_INTERVAL_X-szSize.cx, 
					nWindowPosY + AMMO_START_Y+AMMO_INTERVAL*3, GUI_FONT_COLOR, buff, 0L );				
			}
		}
		else
		{			
			//"�Ǿ : %.2f"
			float fStatPierce = GetDefaultPierce(FALSE);	
			float fItemPierce = g_pShuttleChild->GetShuttleParamFactor()->pfm_PIERCE_UP_02;						
			// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
			//fItemPierce = ((float)fItemPierce / (float)PROB256_MAX_VALUE *100.0f);
			fItemPierce = ((float)fItemPierce / (float)PROB100_MAX_VALUE *100.0f);

			// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���
			fStatPierce = FloatSecRangeSharp(fStatPierce);
			fItemPierce = FloatSecRangeSharp(fItemPierce);

			sprintf( buff, STRMSG_C_080923_0200, (fStatPierce+fItemPierce));			
			
			szSize = m_pFontAmmoWeapon[2]->GetStringSize(buff);
			m_pFontAmmoWeapon[2]->DrawText( nWindowPosX+AMMO_START_X+AMMO_START_INTERVAL_X-szSize.cx, 
				nWindowPosY + AMMO_START_Y+(AMMO_INTERVAL), GUI_FONT_COLOR, buff, 0L );					
		}
		
		
		wsprintf(buff, STRMSG_C_080923_0202, //"�� �� �� : %d%%(%dKg/%dKg)"
			(int) (g_pStoreData->GetTotalWeight() / CAtumSJ::GetTransport(&g_pShuttleChild->m_myShuttleInfo) *100.0f ), 
			(int) g_pStoreData->GetTotalWeight(), (int)CAtumSJ::GetTransport(&g_pShuttleChild->m_myShuttleInfo) );
		szSize = m_pFontAmmoWeapon[4]->GetStringSize(buff);
		m_pFontAmmoWeapon[4]->DrawText( nWindowPosX+AMMO_WEIGHT_START_X-szSize.cx, 
			nWindowPosY + AMMO_WEIGHT_START_Y, 
			GUI_FONT_COLOR, buff, 0L );
		
		// 2009. 11. 3 by jskim ĳ��(�κ�/â�� Ȯ��) ������ �߰� ����
		//wsprintf(buff, "%d/%d", (int)(g_pStoreData->GetTotalUseInven()), 			
		//CAtumSJ::GetMaxInventorySize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1) - 1);	// -1�� ���� �������� �����ϴ� ���̴�.
		// 2009. 12. 17 by jskim ĳ��(�κ�/â�� Ȯ��) ����� 
		//CHARACTER* pMainInfo = g_pD3dApp->GetMFSMyShuttleInfo();
		//	wsprintf(buff, "%d/%d", (int)(g_pStoreData->GetTotalUseInven()), 			
		//	CAtumSJ::GetMaxInventorySize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, pMainInfo->GetAddedPermanentInventoryCount()) - 1);	// -1�� ���� �������� �����ϴ� ���̴�.
			wsprintf(buff, "%d/%d", (int)(g_pStoreData->GetTotalUseInven()), 			
			CAtumSJ::GetMaxInventorySize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, g_pShuttleChild->m_myShuttleInfo.GetAddedPermanentInventoryCount()) - 1);	// -1�� ���� �������� �����ϴ� ���̴�.
		//end 2009. 12. 17 by jskim ĳ��(�κ�/â�� Ȯ��) �����
		//end 2009. 11. 3 by jskim ĳ��(�κ�/â�� Ȯ��) ������ �߰� ����
		szSize = m_pFontAmmoWeapon[5]->GetStringSize(buff);
		m_pFontAmmoWeapon[5]->DrawText(nWindowPosX+INVEN_WEIGHT_START_X-szSize.cx,
								nWindowPosY + INVEN_WEIGHT_START_Y, GUI_FONT_COLOR, 
								buff, 0L);
		
	}
	
	{
//		m_pImgArenaTab->Move(nWindowPosX+12,nWindowPosY + 48);
//		m_pImgArenaTab->Render();
		
		CHARACTER ShuttleInfo = g_pShuttleChild->GetMyShuttleInfo();
		wsprintf(buff,STRMSG_C_070607_0108,ShuttleInfo.ArenaWin,ShuttleInfo.ArenaLose);		
		szSize = m_pFontGeneral->GetStringSize(buff);
		m_pFontGeneral->DrawText(ARENA_SCORE_X-szSize.cx,ARENA_SCORE_Y,GUI_FONT_COLOR,buff);
		UINT nPer = 0;
		if((ShuttleInfo.ArenaWin+ShuttleInfo.ArenaLose) > 0)
		{
			FLOAT fPer = (FLOAT)ShuttleInfo.ArenaWin/(FLOAT)(ShuttleInfo.ArenaWin+ShuttleInfo.ArenaLose);
			nPer = fPer*100;
		}
		wsprintf(buff,"%d%%",nPer);		
		szSize = m_pFontGeneral->GetStringSize(buff);
		m_pFontGeneral->DrawText(ARENA_SCORE_PERCENTAGE_X-szSize.cx,ARENA_SCORE_PERCENTAGE_Y,GUI_FONT_COLOR,buff);
		
		wsprintf(buff,STRMSG_C_070607_0107,ShuttleInfo.ArenaDisConnect);		
		szSize = m_pFontGeneral->GetStringSize(buff);
		m_pFontGeneral->DrawText(ARENA_COMPULSION_END_X-szSize.cx,ARENA_COMPULSION_END_Y,GUI_FONT_COLOR,buff);
		
		char buf[MAX_PATH];
		wsprintf(buf,"%d",ShuttleInfo.CumulativeWarPoint);
		MakeCurrencySeparator(buff,buf,3,',');		
		szSize = m_pFontGeneral->GetStringSize(buff);
		m_pFontGeneral->DrawText(ARENA_COMMULATION_POINT_X-szSize.cx,ARENA_COMMULATION_POINT_Y,GUI_FONT_COLOR,buff);
		
		wsprintf(buf,"%d",ShuttleInfo.WarPoint);
		MakeCurrencySeparator(buff,buf,3,',');		
		szSize = m_pFontGeneral->GetStringSize(buff);
		m_pFontGeneral->DrawText(ARENA_FUSIBLE_POINT_X-szSize.cx,ARENA_FUSIBLE_POINT_Y,GUI_FONT_COLOR,buff);
		
	}
	
	// ���緮�� ���� ���� �Ҹ��, �ν��� �ð�, �̵� �ӵ� ǥ��
	RenderWeightStats();	

}

void CINFCharacterInfoExtend::RenderSkillInfo()
{
	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;
	char buff[MAX_PATH];	
	SIZE szSizeTmp={0,0};
	memset(buff, 0x00, MAX_PATH);
	
	if(m_pUtc )
	{
		m_pUtc->Move(nWindowPosX+22,nWindowPosY + 153);
		m_pUtc->Render() ;
	}
	CINFIcon* pIcon = ((CINFGameMain*)m_pParent)->m_pIcon;
	for(int i=0;i<CHAR_UTC_TYPE_NUMBER;i++)
	{
		for(int j=0;j<MAX_CHAR_UTC_SLOT_NUMBER;j++)
		{
			if(m_pCharacterSkillDisplayInfo[i][j].pItem)
			{
				// 2005-11-28 by ispark, SourceIndex�� ����, ��ų�� SKILL_BASE_NUM���� �Ѵ�.
				char buf[64];
				wsprintf(buf, "%08d", SKILL_BASE_NUM(m_pCharacterSkillDisplayInfo[i][j].pItem->ItemInfo->SourceIndex));
				pIcon->SetIcon(buf,
					CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i+1, CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j+1, 1.0f);
				pIcon->Render();
				
				//						if( IS_COUNTABLE_ITEM(m_pCharacterSkillDisplayInfo[i][j].pItem->Kind) )
				//						{
				//							CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( 
				//								m_pCharacterSkillDisplayInfo[i][j].pItem->UniqueNumber );
				//							if( pItemInfo->CurrentCount > 1 )
				//							{
				// ������ �����ش�.
				if(m_pCharacterSkillDisplayInfo[i][j].pItem->ItemInfo->SkillLevel > 0)
				{
					char buf[256];
					{
						// ��ų����
						//"LV%d"
						wsprintf(buf, STRMSG_C_080922_0202, m_pCharacterSkillDisplayInfo[i][j].pItem->ItemInfo->SkillLevel);
						m_pFontItemNum[i]->DrawText(CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i+33,
							CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j,
							GUI_FONT_COLOR,buf, 0L);
					}
					{
						// ��ų�̸�
						strncpy(buf, m_pCharacterSkillDisplayInfo[i][j].pItem->ItemInfo->ItemName, SIZE_MAX_ITEM_NAME);

						// 2008-10-23 by bhsohn ��ų�� �Ѿ�� ���� ó��
						g_pGameMain->TextReduce(m_pFontItemNum[i], 73, buf);

						m_pFontItemNum[i]->DrawText(CHAR_UTC_START_X+CHAR_UTC_INTERVAL_X*i+33,
							CHAR_UTC_START_Y+CHAR_UTC_INTERVAL_Y*j+14,
							GUI_FONT_COLOR,buf, 0L);
					}
				}
				//							}
				//						}
			}
		}
	}
	// 2006-07-27 by ispark
	//			if(m_pSelectIcon)
	//			{
	//				POINT ptCursor;
	//				GetCursorPos( &ptCursor );
	//				ScreenToClient( g_pD3dApp->GetHwnd(), &ptCursor );
	//				CheckMouseReverse(&ptCursor);				
	//
	//				m_pSelectIcon->Move(ptCursor.x-m_nRenderMoveIconIntervalWidth, ptCursor.y-m_nRenderMoveIconIntervalHeight);
	//				m_pSelectIcon->Render();
	//
	//			}
	m_pUtcScr->Move(UTC_SCROLL_BUTTON_START_X,
		nWindowPosY+UTC_SCROLL_BAR_START_Y+UTC_SCROLL_INTERVAL*m_nCurrentUTCScroll);
	m_pUtcScr->Render() ;
	
}

// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
void CINFCharacterInfoExtend::RenderPartnerInfo()
{
	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;
	char buff[MAX_PATH];	
	SIZE szSizeTmp={0,0};
	memset(buff, 0x00, MAX_PATH);
	
	if(m_pPartnerInfoBk)
	{
		m_pPartnerInfoBk->Move(nWindowPosX + 22,nWindowPosY + 153);
		m_pPartnerInfoBk->Render();
	}

	PatnerInfo();
	PatnerDtail();

	sprintf(buff, STRMSG_C_100608_0410, m_pExpScroll->GetScrollStep());
	szSizeTmp = m_pFontGeneral->GetStringSize(buff);
//	m_pPartnerGiveExp->DrawText(nWindowPosX + PARTNER_DTAIL_INFO_X - szSizeTmp.cx, nWindowPosY + PARTNER_DTAIL_INFO_Y + PARTNER_DTAIL_INFO_Y_GAP * 2, GUI_FONT_COLOR, buff, 0L);

}
//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

void CINFCharacterInfoExtend::OnClickStat(int nPos)
{
	if(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.BonusStat>0)
	{
		// 2007-05-15 by bhsohn ��� ���� ���� ó��
		int nShowBtn = -1;
		
		MSG_FC_CHARACTER_USE_BONUSSTAT sMsg;
		memset(&sMsg,0x00,sizeof(sMsg));
		char buffer[SIZE_MAX_PACKET];
		sMsg.ClientIndex = g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.ClientIndex;
		
		switch(nPos)
		{
		case STAT_ATTACK:
			{
				sMsg.KindOfStat = STAT_ATTACK_PART;
				nShowBtn= STAT_SHUTTLEINFO_ATTACK;
			}
			break;
		case STAT_DURABILITY:
			{
				sMsg.KindOfStat = STAT_DEFENSE_PART;
				nShowBtn= STAT_SHUTTLEINFO_DEFENCE;
			}
			break;
		case STAT_FUEL:
			{
				sMsg.KindOfStat = STAT_FUEL_PART;
				nShowBtn= STAT_SHUTTLEINFO_FUEL;
			}
			break;
		case STAT_INDUCTION:
			{
				sMsg.KindOfStat = STAT_SOUL_PART;
				nShowBtn= STAT_SHUTTLEINFO_SOUL;
			}
			break;
		case STAT_AVOID:
			{
				sMsg.KindOfStat = STAT_DODGE_PART;
				nShowBtn= STAT_SHUTTLEINFO_DODGE;
			}
			break;
		case STAT_KALISMA:
			{
				sMsg.KindOfStat = STAT_SHIELD_PART;
				nShowBtn= STAT_SHUTTLEINFO_SHIELD;
			}
			break;
		}		
		
		if(nShowBtn >= 0)
		{
			if(m_bStatShow[nShowBtn])
			{
				int nType = T_FC_CHARACTER_USE_BONUSSTAT;
				memcpy(buffer, &nType, SIZE_FIELD_TYPE_HEADER);
				memcpy(buffer+SIZE_FIELD_TYPE_HEADER, &sMsg, sizeof(sMsg));
				
#ifdef CUSTOM_OPTIMIZER_HSSON
				if( g_cCustomOptimizer.m_bStatGoGo )
				{
					for( int i = 0; i < 19; ++i )
						g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				}
#endif // CUSTOM_OPTIMIZER_HSSON

				g_pD3dApp->m_pFieldWinSocket->Write(buffer, SIZE_FIELD_TYPE_HEADER + sizeof(sMsg));
				g_pD3dApp->m_bRequestEnable = FALSE;			// 2006-09-18 by ispark, �޼��� ������ ��ٸ���.				
				
			}									
		}		
	}		
}
BOOL CINFCharacterInfoExtend::IsMouseCaps(POINT ptPos)
{
	POINT ptBakPos = m_ptBkPos;
	POINT ptSize = m_pInoBk->GetImgSize();
	if((ptPos.x >= ptBakPos.x && (ptPos.x <= ptBakPos.x+ptSize.x))
		&& (ptPos.y >= ptBakPos.y && (ptPos.y <= ptBakPos.y+20)))
	{
		return TRUE;
	}
	return FALSE;

}
void CINFCharacterInfoExtend::UpdateBtnPos()
{

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		������ ���ݷ��� ���´�.
/// \author		// 2008-09-22 by bhsohn EP3 ĳ���� â
/// \date		2008-09-24 ~ 2008-09-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::GetItemAttackInfo(CItemInfo *pItemInfo, char* o_pDstBuff)
{
	CItemInfo*	pRefItemInfo = pItemInfo;
	ITEM		*pRefITEM = pItemInfo->GetItemInfo();
	RARE_ITEM_INFO *pRefPrefixRareInfo = pRefItemInfo->GetPrefixRareInfo();
	RARE_ITEM_INFO *pRefSuffixRareInfo = pRefItemInfo->GetSuffixRareInfo();
	CParamFactor *pRefEnchant = pRefItemInfo->GetEnchantParamFactor();
	BOOL bEnableItem = IsEnableItem( pRefItemInfo->GetRealItemInfo() );

	float fEnchantAttackMin = pRefEnchant ? pRefEnchant->pfm_MINATTACK_01+ pRefEnchant->pfm_MINATTACK_02 : 0;
	float fEnchantAttackMax = pRefEnchant ? pRefEnchant->pfm_MAXATTACK_01+ pRefEnchant->pfm_MAXATTACK_02 : 0;
	float fRareInfoAttackMin = 0;
	float fRareInfoAttackMax = 0;
	BYTE nEnchantShotNum = pRefEnchant ? pRefEnchant->pfp_SHOTNUM_01 : 0;
	BYTE nEnchantMultiNum = pRefEnchant ? pRefEnchant->pfp_MULTINUM_02 : 0;
	BYTE nRareInfoShotNum = 0;
	BYTE nRareInfoMultiNum = 0;
	if(pRefPrefixRareInfo)
	{
		for(int i=0; i<SIZE_DES_PARAM_PER_RARE_ITEM_INFO; i++)
		{
			if( pRefPrefixRareInfo->DesParameter[i] == DES_MINATTACK_01 || 
				pRefPrefixRareInfo->DesParameter[i] == DES_MINATTACK_02)
			{
				fRareInfoAttackMin += pRefPrefixRareInfo->ParameterValue[i];
			}
			else if(pRefPrefixRareInfo->DesParameter[i] == DES_MAXATTACK_01 ||
				pRefPrefixRareInfo->DesParameter[i] == DES_MAXATTACK_02)
			{
				fRareInfoAttackMax += pRefPrefixRareInfo->ParameterValue[i];
			}
			else if(pRefPrefixRareInfo->DesParameter[i] == DES_SHOTNUM_01  ||
				pRefPrefixRareInfo->DesParameter[i] == DES_SHOTNUM_02)
			{
				nRareInfoShotNum += (BYTE)pRefPrefixRareInfo->ParameterValue[i];
			}
			else if(//pRefPrefixRareInfo->DesParameter[i] == DES_MULTINUM_01 ||
				pRefPrefixRareInfo->DesParameter[i] == DES_MULTINUM_02)
			{
				nRareInfoMultiNum += (BYTE)pRefPrefixRareInfo->ParameterValue[i];
			}
		}
	}
	if(pRefSuffixRareInfo)
	{
		for(int i=0; i<SIZE_DES_PARAM_PER_RARE_ITEM_INFO; i++)
		{
			if( pRefSuffixRareInfo->DesParameter[i] == DES_MINATTACK_01 || 
				pRefSuffixRareInfo->DesParameter[i] == DES_MINATTACK_02)
			{
				fRareInfoAttackMin += pRefSuffixRareInfo->ParameterValue[i];
			}
			else if(pRefSuffixRareInfo->DesParameter[i] == DES_MAXATTACK_01 ||
				pRefSuffixRareInfo->DesParameter[i] == DES_MAXATTACK_02)
			{
				fRareInfoAttackMax += pRefSuffixRareInfo->ParameterValue[i];
			}
			else if(pRefSuffixRareInfo->DesParameter[i] == DES_SHOTNUM_01 ||
				pRefSuffixRareInfo->DesParameter[i] == DES_SHOTNUM_02)
			{
				nRareInfoShotNum += (BYTE)pRefSuffixRareInfo->ParameterValue[i];
			}
			else if(//pRefSuffixRareInfo->DesParameter[i] == DES_MULTINUM_01 ||
				pRefSuffixRareInfo->DesParameter[i] == DES_MULTINUM_02)
			{
				nRareInfoMultiNum += (BYTE)pRefSuffixRareInfo->ParameterValue[i];
			}
		}
	}

	sprintf( o_pDstBuff, STRMSG_C_080923_0204, pRefITEM->AbilityMin );//"���� : (%.0f"
	if(fEnchantAttackMin > 0)
		sprintf( o_pDstBuff, "%s\\e[+%.0f%%]\\e", o_pDstBuff, fEnchantAttackMin*100.0f );
	else if(fEnchantAttackMin < 0) 
		sprintf( o_pDstBuff, "%s\\e[%.0f%%]\\e", o_pDstBuff, fEnchantAttackMin*100.0f );
	if(fRareInfoAttackMin > 0)
		sprintf( o_pDstBuff, "%s\\g[+%.0f%%]\\g", o_pDstBuff, fRareInfoAttackMin*100.0f );
	else if(fRareInfoAttackMin < 0) 
		sprintf( o_pDstBuff, "%s\\g[%.0f%%]\\g", o_pDstBuff, fRareInfoAttackMin*100.0f );

	sprintf( o_pDstBuff, "%s ~ %.0f", o_pDstBuff, pRefITEM->AbilityMax );
	if(fEnchantAttackMax > 0)
		sprintf( o_pDstBuff, "%s\\e[+%.0f%%]\\e", o_pDstBuff, fEnchantAttackMax*100.0f );
	else if(fEnchantAttackMin < 0) 
		sprintf( o_pDstBuff, "%s\\e[%.0f%%]\\e", o_pDstBuff, fEnchantAttackMax*100.0f );
	if(fRareInfoAttackMax > 0)
		sprintf( o_pDstBuff, "%s\\g[+%.0f%%]\\g", o_pDstBuff, fRareInfoAttackMax*100.0f );
	else if(fRareInfoAttackMin < 0) 
		sprintf( o_pDstBuff, "%s\\g[%.0f%%]\\g", o_pDstBuff, fRareInfoAttackMax*100.0f );
	sprintf( o_pDstBuff, "%s) X (%d",o_pDstBuff,pRefITEM->ShotNum);

	if(nEnchantShotNum>0)
		sprintf( o_pDstBuff, "%s\\e[+%d]\\e", o_pDstBuff, nEnchantShotNum );
	else if(nEnchantShotNum<0)
		sprintf( o_pDstBuff, "%s\\e[%d]\\e", o_pDstBuff, nEnchantShotNum );
	if(nRareInfoShotNum>0)
		sprintf( o_pDstBuff, "%s\\g[+%d]\\g", o_pDstBuff, nRareInfoShotNum );
	else if(nRareInfoShotNum<0)
		sprintf( o_pDstBuff, "%s\\g[%d]\\g", o_pDstBuff, nRareInfoShotNum );
	sprintf( o_pDstBuff, "%s X %d",o_pDstBuff,pRefITEM->MultiNum);

	if(nEnchantMultiNum>0)
		sprintf( o_pDstBuff, "%s\\e[+%d]\\e", o_pDstBuff, nEnchantMultiNum );
	else if(nEnchantMultiNum<0)
		sprintf( o_pDstBuff, "%s\\e[%d]\\e", o_pDstBuff, nEnchantMultiNum );
	if(nRareInfoMultiNum>0)
		sprintf( o_pDstBuff, "%s\\g[+%d]\\g", o_pDstBuff, nRareInfoMultiNum );
	else if(nRareInfoMultiNum<0)
		sprintf( o_pDstBuff, "%s\\g[%d]\\g", o_pDstBuff, nRareInfoMultiNum );
	strcat(o_pDstBuff, ")");
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFItemInfo::IsEnableItem(ITEM* pITEM)
/// \brief		
/// \author		dhkwon
/// \date		2004-06-12 ~ 2004-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCharacterInfoExtend::IsEnableItem(ITEM* pITEM)
{
	if( pITEM->ReqGearStat.AttackPart <= g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart &&
		pITEM->ReqGearStat.ShieldPart <= g_pShuttleChild->m_myShuttleInfo.TotalGearStat.ShieldPart &&
		pITEM->ReqGearStat.DodgePart <= g_pShuttleChild->m_myShuttleInfo.TotalGearStat.DodgePart &&
		pITEM->ReqGearStat.DefensePart <= g_pShuttleChild->m_myShuttleInfo.TotalGearStat.DefensePart &&
		pITEM->ReqGearStat.FuelPart <= g_pShuttleChild->m_myShuttleInfo.TotalGearStat.FuelPart &&
		pITEM->ReqMinLevel <= g_pShuttleChild->m_myShuttleInfo.Level &&
		pITEM->ReqMaterial <= g_pShuttleChild->m_myShuttleInfo.Material &&
		CompareBitFlag( pITEM->ReqRace , g_pShuttleChild->m_myShuttleInfo.Race ) &&
		pITEM->ReqGearStat.SoulPart <= g_pShuttleChild->m_myShuttleInfo.TotalGearStat.SoulPart &&
		pITEM->ReqSP <= g_pShuttleChild->m_myShuttleInfo.SP &&
		CompareBitFlag( pITEM->ReqUnitKind, g_pShuttleChild->m_myShuttleInfo.UnitKind ) )
	{
		if(	pITEM->ReqMaxLevel == 0 ||
			pITEM->ReqMaxLevel >= g_pShuttleChild->m_myShuttleInfo.Level)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}		
	}
	else
	{
		return FALSE;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFItemInfo::IsEnableItem(ITEM* pITEM)
/// \brief		
/// \author		dhkwon
/// \date		2004-06-12 ~ 2004-06-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CINFCharacterInfoExtend::GetDefaultPierce(BOOL bIsPrimaryAttack)
{	
	int nAttackPart = g_pShuttleChild->m_myShuttleInfo.TotalGearStat.AttackPart;
	float LevelPierce = CAtumSJ::GetLevelStatValue(min(COUNT_MAX_STAT_POINT,nAttackPart))->AttackPart_PierceAttackProbability;	

	CParamFactor paramCharctorParam = (*g_pShuttleChild->GetShuttleParamFactor());	
	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)	
	//LevelPierce = ((float)LevelPierce / (float)PROB256_MAX_VALUE *100.0f);
	LevelPierce = ((float)LevelPierce / (float)PROB100_MAX_VALUE *100.0f);

	return LevelPierce;
	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFItemInfo::IsEnableItem(ITEM* pITEM)
/// \brief		
/// \author		// 2008-09-26 by bhsohn �ű� ��þƮ ó��
/// \date		2008-09-26 ~ 2008-09-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::GetDefenceRateString(BOOL bIsPrimaryAttack, char* pDefaultRate, char* pArmorRate, char* pPetRate)
{
	CItemInfo* pArmorItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_CENTER ); 
	CItemInfo* pPetItem = g_pStoreData->FindItemInInventoryByWindowPos(POS_PET);	// �ð��� �Ǽ��縮
	
	CParamFactor paramCharctorParam = (*g_pShuttleChild->GetShuttleParamFactor());	
	float fArmorDefence = 0.0f;
	float fArmorDefenceRate = 0.0f;

	if(pArmorItem)
	{
		CParamFactor *pArmorParamFacotor = pArmorItem->GetEnchantParamFactor();
		if(pArmorParamFacotor)
		{
			paramCharctorParam += (*pArmorParamFacotor);
			fArmorDefence = (bIsPrimaryAttack?pArmorParamFacotor->pfp_DEFENSE_01:pArmorParamFacotor->pfp_DEFENSE_02);		
			// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
			//fArmorDefenceRate = (fArmorDefence /PROB256_MAX_VALUE) * 100.0f;
			fArmorDefenceRate = (fArmorDefence /PROB100_MAX_VALUE) * 100.0f;
		}
	}
	
	float fAllDefence = 0.0f;

	fAllDefence = (float)CAtumSJ::GetDefenseC( &g_pShuttleChild->m_myShuttleInfo,  
			&paramCharctorParam, bIsPrimaryAttack );
	
	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)	
//	float fAllDefenceRate = (fAllDefence /PROB256_MAX_VALUE) * 100.0f;					
	float fAllDefenceRate = (fAllDefence /PROB100_MAX_VALUE) * 100.0f;					
	
	// 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����

// 	float fDefaultDefence = 
// 		(float)CAtumSJ::GetDefenseC_DecreaseRate(g_pShuttleChild->m_myShuttleInfo.TotalGearStat.DefensePart)*PROB256_MAX_VALUE;
	float fDefaultDefence = 
		// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%) ���Ȱ��õȰ� �׳� 255�� 
		(float)CAtumSJ::GetDefenseC_DecreaseRate(g_pShuttleChild->m_myShuttleInfo.TotalGearStat.DefensePart, g_pShuttleChild->m_myShuttleInfo.Level)*PROB256_MAX_VALUE;
		//(float)CAtumSJ::GetDefenseC_DecreaseRate(g_pShuttleChild->m_myShuttleInfo.TotalGearStat.DefensePart, g_pShuttleChild->m_myShuttleInfo.Level)*PROB100_MAX_VALUE;

	// end 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����
	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%) ���Ȱ��õȰ� �׳� 255�� 
	float fDefaultDefenceRate = (fDefaultDefence/PROB256_MAX_VALUE) * 100.0f;
	//float fDefaultDefenceRate = (fDefaultDefence/PROB100_MAX_VALUE) * 100.0f;
	
	// 2011-07-04 by hsson ����â ���� ���콺�� ���� �� ������ ��ġ ���� ����
	float fPetEnchant = fAllDefence - fDefaultDefenceRate - fArmorDefence;
	// end 2011-07-04 by hsson ����â ���� ���콺�� ���� �� ������ ��ġ ���� ����

	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
	//float fPetEnchantRate = (fPetEnchant /PROB256_MAX_VALUE) * 100.0f;
	float fPetEnchantRate = (fPetEnchant /PROB100_MAX_VALUE) * 100.0f;

	char chTmp[128];
	memset(chTmp, 0x00, 128);	

	// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���
	fAllDefenceRate = FloatSecRangeSharp(fAllDefenceRate);
	fDefaultDefenceRate = FloatSecRangeSharp(fDefaultDefenceRate);
	fPetEnchantRate = FloatSecRangeSharp(fPetEnchantRate);
	
	if(fDefaultDefenceRate > 0)
	{
		sprintf( pDefaultRate, STRMSG_C_080923_0200, fDefaultDefenceRate);//"���� �⺻���� : %.2f%%"
	}
	if(fArmorDefenceRate > 0)
	{
		sprintf(chTmp, STRMSG_C_080923_0200, fArmorDefenceRate);
		sprintf(pArmorRate, "\\e[+%s]\\e", chTmp);
	}
	
	if(fPetEnchant > 0)
	{
		sprintf(chTmp, STRMSG_C_080923_0200, fPetEnchantRate);
		sprintf(pPetRate, "\\g[+%s]\\g", chTmp);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFItemInfo::IsEnableItem(ITEM* pITEM)
/// \brief		
/// \author		// 2008-09-26 by bhsohn �ű� ��þƮ ó��
/// \date		2008-09-26 ~ 2008-09-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::GetDodgeRateString(BOOL bIsPrimaryAttack, char* pDefaultRate, char* pArmorRate, char* pPetRate)
{
	CItemInfo* pArmorItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_CENTER ); 
	CItemInfo* pPetItem = g_pStoreData->FindItemInInventoryByWindowPos(POS_PET);	// �ð��� �Ǽ��縮
	CParamFactor paramCharctorParam = (*g_pShuttleChild->GetShuttleParamFactor());	
	float fArmorDefence = 0.0f;
	float fArmorDefenceRate = 0.0f;
	if(pArmorItem)
	{
		CParamFactor *pArmorParamFacotor = pArmorItem->GetEnchantParamFactor();
		if(pArmorParamFacotor)
		{
			paramCharctorParam += (*pArmorParamFacotor);
			
			fArmorDefence = (bIsPrimaryAttack?pArmorParamFacotor->pfp_DEFENSEPROBABILITY_01:pArmorParamFacotor->pfp_DEFENSEPROBABILITY_02);		
			// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
			//fArmorDefenceRate = (fArmorDefence /PROB256_MAX_VALUE) * 100.0f;
			fArmorDefenceRate = (fArmorDefence /PROB100_MAX_VALUE) * 100.0f;
		}
	}
	
	float fAllDefence = 0.0f;

	fAllDefence = CAtumSJ::GetDefenseProbabilityC( &g_pShuttleChild->m_myShuttleInfo, 
			(pArmorItem==NULL?NULL:pArmorItem->GetRealItemInfo()), 
			&paramCharctorParam, bIsPrimaryAttack );

	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
	//float fAllDefenceRate = (fAllDefence /PROB256_MAX_VALUE) * 100.0f;
	float fAllDefenceRate = (fAllDefence /PROB100_MAX_VALUE) * 100.0f;
	
	// 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����

// 	float fDefaultDefence = 		
// 		((float)CAtumSJ::GetDefenseProbabilityC_Rate(g_pShuttleChild->m_myShuttleInfo.TotalGearStat.DodgePart)) 
// 		* PROB256_MAX_VALUE;

	float fDefaultDefence = 		
		((float)CAtumSJ::GetDefenseProbabilityC_Rate(g_pShuttleChild->m_myShuttleInfo.TotalGearStat.DodgePart, g_pShuttleChild->m_myShuttleInfo.Level)) 
		// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%) ���ȿ� ���� ���� 255�� ��.
		* PROB256_MAX_VALUE;
		//* PROB100_MAX_VALUE;

	// end 2010. 02. 19 by ckPark 100�����̸��Ͻ� 300�����ʰ����� ����Ǵ� ���� ����
	
	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%) ���ȿ� ���� ���� 255�� ��.
	float fDefaultDefenceRate = (fDefaultDefence/PROB256_MAX_VALUE) * 100;						
	//float fDefaultDefenceRate = (fDefaultDefence/PROB100_MAX_VALUE) * 100;

	// 2011-07-04 by hsson ����â ���� ���콺�� ���� �� ������ ��ġ ���� ����	
	float fPetEnchant = fAllDefence - fDefaultDefenceRate - fArmorDefence;
	// end 2011-07-04 by hsson ����â ���� ���콺�� ���� �� ������ ��ġ ���� ����

	// 2010-07-28 by dgwoo Ȯ�� ���� ���� (255 => 100%)
	//float fPetEnchantRate = (fPetEnchant /PROB256_MAX_VALUE) * 100.0f;
	float fPetEnchantRate = (fPetEnchant /PROB100_MAX_VALUE) * 100.0f;

	// 2008-03-19 by bhsohn FLOAT�� ������ �Ͽ� ���	
	fAllDefenceRate = FloatSecRangeSharp(fAllDefenceRate);
	fDefaultDefenceRate = FloatSecRangeSharp(fDefaultDefenceRate);
	fPetEnchantRate = FloatSecRangeSharp(fPetEnchantRate);

	char chTmp[128];
	memset(chTmp, 0x00, 128);	
	
	if(fDefaultDefenceRate > 0)
	{
		sprintf( pDefaultRate, STRMSG_C_080923_0200, fDefaultDefenceRate);//"���� �⺻���� : %.2f%%"
	}
	if(fArmorDefence > 0)
	{
		sprintf(chTmp, STRMSG_C_080923_0200, fArmorDefenceRate);
		sprintf(pArmorRate, "\\e[+%s]\\e", chTmp);
	}
	
	if(fPetEnchant > 0)
	{
		sprintf(chTmp, STRMSG_C_080923_0200, fPetEnchantRate);
		sprintf(pPetRate, "\\g[+%s]\\g", chTmp);
	}
	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFItemInfo::IsEnableItem(ITEM* pITEM)
/// \brief		// ���緮�� ���� ���� �Ҹ��, �ν��� �ð�, �̵� �ӵ� ǥ��
/// \author		// 2008-09-26 by bhsohn �ű� ��þƮ ó��
/// \date		2008-09-26 ~ 2008-09-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::RenderWeightStats()
{
	int nWindowPosX = m_ptBkPos.x;
	int nWindowPosY = m_ptBkPos.y;

	char chFuel[256],chBooster[256],chSpeed[256];
	
	memset(chFuel, 0x00, 256);
	memset(chBooster, 0x00, 256);
	memset(chSpeed, 0x00, 256);

	int nWeight = (int) (g_pStoreData->GetTotalWeight() / CAtumSJ::GetTransport(&g_pShuttleChild->m_myShuttleInfo) *100.0f );
	if(nWeight < 70)
	{
		wsprintf(chFuel, STRMSG_C_081014_0200);		// "����"
		wsprintf(chBooster, STRMSG_C_081014_0200);	// "����"
		wsprintf(chSpeed, STRMSG_C_081014_0200);	// "����"
	}
	else if((nWeight >= 70) && (nWeight < 80))
	{
		wsprintf(chFuel, STRMSG_C_081014_0201);		// "���� �Һ� 2�� ����"
		wsprintf(chBooster, STRMSG_C_081014_0200);	// "����"
		wsprintf(chSpeed, STRMSG_C_081014_0200);	// "����"
	}
	else if((nWeight >= 80) && (nWeight < 90))
	{
		wsprintf(chFuel, STRMSG_C_081014_0201);		// "���� �Һ� 2�� ����"
		wsprintf(chBooster, STRMSG_C_081014_0202);	// "�ν��� ��� �Ұ�"
		wsprintf(chSpeed, STRMSG_C_081014_0200);	// "����"
	}
	else if(nWeight >= 90)
	{
		wsprintf(chFuel, STRMSG_C_081014_0201);		// "���� �Һ� 2�� ����"
		wsprintf(chBooster, STRMSG_C_081014_0202);	// "�ν��� ��� �Ұ�"
		wsprintf(chSpeed, STRMSG_C_081014_0203);	// "���� �ӵ� �̵�"
	}	
	
	SIZE szSize = {0,0};
	{		
		// ���� �Ҹ�
		szSize = m_pFontGeneral->GetStringSize(chFuel);
		m_pFontGeneral->DrawText(nWindowPosX+WEIGHT_FUEL_START_X-szSize.cx,
								nWindowPosY + WEIGHT_FUEL_START_Y, GUI_FONT_COLOR, 
								chFuel, 0L);
	}

	{		
		// �ν��� �ð�
		szSize = m_pFontGeneral->GetStringSize(chBooster);
		m_pFontGeneral->DrawText(nWindowPosX+WEIGHT_BOOSTER_START_X-szSize.cx,
								nWindowPosY + WEIGHT_BOOSTER_START_Y, GUI_FONT_COLOR, 
								chBooster, 0L);
	}
	{		
		// �̵� �ӵ�
		szSize = m_pFontGeneral->GetStringSize(chSpeed);
		m_pFontGeneral->DrawText(nWindowPosX+WEIGHT_SPEED_START_X-szSize.cx,
								nWindowPosY + WEIGHT_SPEED_START_Y, GUI_FONT_COLOR, 
								chSpeed, 0L);
	}
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-02-13 by bhsohn ���� ��ŷ �ý���
/// \date		2009-02-24 ~ 2009-02-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCharacterInfoExtend::OnClickNickNameBtn()
{
	char chTmp[512];
	ZERO_MEMORY(chTmp);

	wsprintf(chTmp, STRMSG_C_090224_0201);
	
	// �г��� ����â
	g_pGameMain->m_pInfWindow->AddMsgBox(chTmp, _Q_CREATE_NICKNAME_OKCANCEL);

}
