// INFCityLeader.cpp: implementation of the CINFCityLeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFCityLeader.h"
#include "Interface.h"
#include "INFPilotFace.h"
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
#include "INFSelect.h"
#include "INFPilotFace.h"
#include "INFMotherShipManager.h"
#include "INFCurselEditBox.h"	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
 

#define LEADER_BAR_NAME_X			(CITY_BASE_NPC_BOX_START_X + 5)
#define LEADER_BAR_NAME_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_CITYLEADER_WINDOWL_Y + 2)			// ?ٸ? ?????? ?? ????.
#define LEADER_STARTL_X				(CITY_BASE_NPC_BOX_START_X)									// ?????? â ?? ?մ?.
#define LEADER_STARTL_Y				(CITY_BASE_NPC_BOX_START_Y - SIZE_CITYLEADER_WINDOWL_Y + 20)			// ?ٸ? ?????? ?? ????.
#define LEADER_STARTR_X				(LEADER_STARTL_X + SIZE_CITYLEADER_WINDOWL_X)
#define LEADER_STARTR_Y				(CITY_BASE_NPC_BOX_START_Y - SIZE_CITYLEADER_WINDOWL_Y + 20)			// ?ٸ? ?????? ?? ????.

// ???? â ???? ?? ??ư ??ġ.
#define LEADER_BGL_X				(LEADER_STARTL_X + 14)
#define LEADER_BGL_Y				(LEADER_STARTL_Y + 7)

#define TITLE_POS_X					(LEADER_BGL_X)
#define TITLE_POS_Y					(LEADER_BGL_Y -24)


#define LEADER_BRIGADE_NOTICE_BUTTON_X				(LEADER_BGL_X + 16)
#define LEADER_BRIGADE_NOTICE_BUTTON_Y				(LEADER_BGL_Y + 23)
#define LEADER_EXPENCE_BUTTON_X						(LEADER_BGL_X + 16)
#define LEADER_EXPENCE_BUTTON_Y						(LEADER_BGL_Y + 61)
//#define LEADER_WAR_TIME_SET_BUTTON_X			(LEADER_BGL_X + 16)
//#define LEADER_WAR_TIME_SET_BUTTON_Y			(LEADER_BGL_Y + 98)
#define LEADER_POLL_BUTTON_X						(LEADER_BGL_X + 16)
#define LEADER_POLL_BUTTON_Y						(LEADER_BGL_Y + 98)
#define LEADER_POLL_DATE_BUTTON_X					(LEADER_BGL_X + 16)
#define LEADER_POLL_DATE_BUTTON_Y					(LEADER_BGL_Y + 135)
#define LEADER_WARINFO_BUTTON_X						(LEADER_BGL_X + 16)
#define LEADER_WARINFO_BUTTON_Y						(LEADER_BGL_Y + 172)
#define LEADER_LEFT_BUTTON_W						124
#define	LEADER_LEFT_BUTTON_H						29

// ?????? ???? ?? ??ư??ġ.
//--------------------------------------------------------------------------//

#define LEADER_BGR_X								(LEADER_STARTR_X + 12)
#define LEADER_BGR_Y								(LEADER_STARTR_Y + 7)

// ???? ???? ????.
#define LEADER_WRITE_BUTTON_X						(LEADER_BGR_X + 11)
#define LEADER_WRITE_BUTTON_Y						(LEADER_BGR_Y + 47)
#define LEADER_REV_BUTTON_X							(LEADER_BGR_X + 79)
#define LEADER_REV_BUTTON_Y							(LEADER_BGR_Y + 47)
#define LEADER_DEL_BUTTON_X							(LEADER_BGR_X + 147)
#define LEADER_DEL_BUTTON_Y							(LEADER_BGR_Y + 47)
#define LEADER_APP_BUTTON_X							(LEADER_BGR_X + 238)
#define LEADER_APP_BUTTON_Y							(LEADER_BGR_Y + 205)
#define LEADER_RIGHT_BUTTON_W						65
#define	LEADER_RIGHT_BUTTON_H						19

//#define LEADER_NOTICE_EDIT_W						260
#define LEADER_NOTICE_EDIT_W						240
#define LEADER_NOTICE_EDIT_H						110

#define LEADER_NOTICE_EDIT_X						(LEADER_BGR_X + 25)
#define LEADER_NOTICE_EDIT_Y						(LEADER_BGR_Y + 86)
#define LEADER_NOTICE_FONT_LINE_HEIGHT				15

// ?ǰ??? ????.
#define LEADER_EXPENCE_OK_BUTTON_X					(LEADER_BGR_X + 238)
#define LEADER_EXPENCE_OK_BUTTON_Y					(LEADER_BGR_Y + 202)

#define LEADER_EXPENCE_LATE_FONT_X					(LEADER_BGR_X + 247)
#define LEADER_EXPENCE_LATE_FONT_Y					(LEADER_BGR_Y + 55)
#define LEADER_EXPENCE_CUMEXP_FONT_X				(LEADER_BGR_X + 247)
#define LEADER_EXPENCE_CUMEXP_FONT_Y				(LEADER_BGR_Y + 86)
#define LEADER_EXPENCE_EXP_FONT_X					(LEADER_BGR_X + 247)
#define LEADER_EXPENCE_EXP_FONT_Y					(LEADER_BGR_Y + 116)

// ???? ?ð? ????.
#define LEADER_WARTIME_RADIO_BUTTON_START_X			(LEADER_BGR_X + 35)
#define LEADER_WARTIME_RADIO_BUTTON_START_Y			(LEADER_BGR_Y + 161)
#define LEADER_WARTIME_RADIO_BUTTON_GAP_Y			19
#define LEADER_WARTIME_RADIO_BUTTON_W				17
#define LEADER_WARTIME_RADIO_BUTTON_H				17

#define LEADER_NEXT_WARTIME_DATE_FONT_X				(LEADER_BGR_X + 74)
#define LEADER_NEXT_WARTIME_DATE_FONT_Y				(LEADER_BGR_Y + 67)
#define LEADER_NEXT_WARTIME_TIME_FONT_X				(LEADER_BGR_X + 74)
#define LEADER_NEXT_WARTIME_TIME_FONT_Y				(LEADER_BGR_Y + 117)

#define LEADER_SEL_WARTIME_FONT_X					(LEADER_BGR_X + 57)
#define LEADER_SEL_WARTIME_FONT_Y					(LEADER_BGR_Y + 167)
#define LEADER_SEL_WARTIME_FONT_GAP_H				18 



#define LEADER_OK_BUTTON_X							(LEADER_BGR_X + 238)
#define LEADER_OK_BUTTON_Y							(LEADER_BGR_Y + 202)

// ???? ?????? ???? 
#define LEADER_WAR_TIME_X							(LEADER_BGR_X + 11)
#define LEADER_WAR_TIME_Y							(LEADER_BGR_Y + 202)
//--------------------------------------------------------------------------//
//							???ý??? ?߰?									//

//         ?ĺ? ????â.

// ???? 
#define LEADER_POLL_INFO_BUTTON_X					(LEADER_BGR_X + 14)
#define LEADER_POLL_INFO_BUTTON_Y					(LEADER_BGR_Y + 32)
// ????
#define LEADER_POLL_APP_BUTTON_X					(LEADER_BGR_X + 112)
#define LEADER_POLL_APP_BUTTON_Y					(LEADER_BGR_Y + 32)
// ??ǥ
#define LEADER_POLL_VOTE_BUTTON_X					(LEADER_BGR_X + 36)
#define LEADER_POLL_VOTE_BUTTON_Y					(LEADER_BGR_Y + 184)
// ????
#define LEADER_POLL_LIST_BUTTON_X					(LEADER_BGR_X + 225)
#define LEADER_POLL_LIST_BUTTON_Y					(LEADER_BGR_Y + 210)
#define LEADER_POLL_LIST_BUTTON_W					76
#define LEADER_POLL_LIST_BUTTON_H					21

// ???? 
#define LEADER_POLL_INFO_LEVEL_FONT_X				(LEADER_BGR_X + 183)
#define LEADER_POLL_INFO_LEVEL_FONT_Y				(LEADER_BGR_Y + 59)
// ???ܸ?ũ.
#define LEADER_POLL_GUILDMARK_IMG_X					(LEADER_BGR_X + 180)
#define LEADER_POLL_GUILDMARK_IMG_Y					(LEADER_BGR_Y + 82)
// ???? ?̹???.
#define LEADER_POLL_FACE_IMG_X						(LEADER_BGR_X + 21)
#define LEADER_POLL_FACE_IMG_Y						(LEADER_BGR_Y + 58)
// ???ܸ?.
#define LEADER_POLL_GUILDNAME_FONT_X				(LEADER_POLL_GUILDMARK_IMG_X + 30)
#define LEADER_POLL_GUILDNAME_FONT_Y				(LEADER_POLL_GUILDMARK_IMG_Y - 3)
// ???ܸ???
#define LEADER_POLL_GUILDFAME_FONT_X				(LEADER_BGR_X + 209)
#define LEADER_POLL_GUILDFAME_FONT_Y				(LEADER_BGR_Y + 100)
// id
#define LEADER_POLL_ID_FONT_X						(LEADER_BGR_X + 71)
#define LEADER_POLL_ID_FONT_Y						(LEADER_BGR_Y + 161)


//       ???? ?ۼ?.
#define LEADER_POLL_APPSUC_BUTTON_X					(LEADER_POLL_LIST_BUTTON_X)
#define LEADER_POLL_APPSUC_BUTTON_Y					(LEADER_POLL_LIST_BUTTON_Y)

#define LEADER_POLL_PLEDGE_EDIT_X					(LEADER_BGR_X + 24)
#define LEADER_POLL_PLEDGE_EDIT_Y					(LEADER_BGR_Y + 83)
//#define LEADER_POLL_PLEDGE_EDIT_W					256
#define LEADER_POLL_PLEDGE_EDIT_W					246
#define LEADER_POLL_PLEDGE_EDIT_H					106

#define LEADER_POLL_PLEDGE_VIEW_EDIT_X				(LEADER_BGR_X + 133)
#define LEADER_POLL_PLEDGE_VIEW_EDIT_Y				(LEADER_BGR_Y + 124)
#define LEADER_POLL_PLEDGE_VIEW_EDIT_W				143
#define LEADER_POLL_PLEDGE_VIEW_EDIT_H				74


//       ???? ????.
// ?ĺ? ??û ?Ⱓ. 
#define LEADER_POLL_APP_CENTER_FONT_X				(LEADER_BGR_X + 157)
#define LEADER_POLL_APP_CENTER_FONT_Y				(LEADER_BGR_Y + 80)
// ??ǥ ???? ?Ⱓ.
#define LEADER_POLL_JOIN_CENTER_FONT_X				(LEADER_BGR_X + 157)
#define LEADER_POLL_JOIN_CENTER_FONT_Y				(LEADER_BGR_Y + 132)
// ??????.
#define LEADER_POLL_ELECT_CENTER_FONT_X				(LEADER_BGR_X + 106)
#define LEADER_POLL_ELECT_CENTER_FONT_Y				(LEADER_BGR_Y + 182)

//       ?ĺ? ????Ʈ.
#define LEADER_POLL_SELECT_BUTTON_X					LEADER_POLL_LIST_BUTTON_X
#define LEADER_POLL_SELECT_BUTTON_Y					LEADER_POLL_LIST_BUTTON_Y

// ????Ʈ ????.
#define LEADER_POLL_LIST_BG_X						(LEADER_BGR_X + 14)
#define LEADER_POLL_LIST_BG_Y						(LEADER_BGR_Y + 52)

#define LEADER_POLL_LIST_AREA_X						(LEADER_BGR_X + 22)
#define LEADER_POLL_LIST_AREA_Y						(LEADER_BGR_Y + 81)
#define LEADER_POLL_LIST_AREA_W						258
#define LEADER_POLL_LIST_AREA_H						119
#define LEADER_POLL_LIST_SELECT_H					17

#define LEADER_POLL_LIST_NUMBER_X					(LEADER_BGR_X + 39)
#define LEADER_POLL_LIST_START_Y					(LEADER_BGR_Y + 81)
#define LEADER_POLL_LIST_CONDIDATE_NAME_X			(LEADER_BGR_X + 123)
#define LEADER_POLL_LIST_GUILD_NAME_X				(LEADER_BGR_X + 236)

// ????Ʈ ??ũ??.
#define LEADER_POLL_LIST_MAX_SCROLL_LINE			7
#define LEADER_POLL_LIST_SCROLL_X					(LEADER_BGR_X + 286)
#define LEADER_POLL_LIST_SCROLL_Y					(LEADER_BGR_Y + 83)
#define LEADER_POLL_LIST_SCROLL_W					11
#define LEADER_POLL_LIST_SCROLL_H					78
#define LEADER_POLL_LIST_SCROLL_WHELL_X				(LEADER_BGR_X + 22)
#define LEADER_POLL_LIST_SCROLL_WHELL_Y				(LEADER_BGR_Y + 82)
#define LEADER_POLL_LIST_SCROLL_WHELL_W				279	
#define LEADER_POLL_LIST_SCROLL_WHELL_H				120
#define LEADER_POLL_LIST_SCROLL_BALL_X				(LEADER_BGR_X + 270)
#define LEADER_POLL_LIST_SCROLL_BALL_Y				(LEADER_BGR_Y + 53)
#define LEADER_POLL_LIST_SCROLL_BALL_W				46
#define LEADER_POLL_LIST_SCROLL_BALL_H				180
// ???? ??ũ?? 													
#define LEADER_POLL_PLEDGE_MAX_SCROLL_LINE			6
#define LEADER_POLL_PLEDGE_SCROLL_X					(LEADER_BGR_X + 286)
#define LEADER_POLL_PLEDGE_SCROLL_Y					(LEADER_BGR_Y + 76)
#define LEADER_POLL_PLEDGE_SCROLL_W					11
#define LEADER_POLL_PLEDGE_SCROLL_H					68
#define LEADER_POLL_PLEDGE_SCROLL_WHELL_X			(LEADER_BGR_X + 22)
#define LEADER_POLL_PLEDGE_SCROLL_WHELL_Y			(LEADER_BGR_Y + 82)
#define LEADER_POLL_PLEDGE_SCROLL_WHELL_W			279	
#define LEADER_POLL_PLEDGE_SCROLL_WHELL_H			120
#define LEADER_POLL_PLEDGE_SCROLL_BALL_X			(LEADER_BGR_X + 270)
#define LEADER_POLL_PLEDGE_SCROLL_BALL_Y			(LEADER_BGR_Y + 53)
#define LEADER_POLL_PLEDGE_SCROLL_BALL_W			46
#define LEADER_POLL_PLEDGE_SCROLL_BALL_H			180
// ???? ?? ??ũ??
#define LEADER_POLL_PLEDGE_VIEW_MAX_SCROLL_LINE		4
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_X			(LEADER_BGR_X + 280)
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_Y			(LEADER_BGR_Y + 124)
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_W			11
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_H			36
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_X		(LEADER_BGR_X + 130)
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_Y		(LEADER_BGR_Y + 124)
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_W		164
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_H		76
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_BALL_X		(LEADER_BGR_X + 315)
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_BALL_Y		(LEADER_BGR_Y + 234)
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_BALL_W		32
#define LEADER_POLL_PLEDGE_VIEW_SCROLL_BALL_H		113

//--------------------------------------------------------------------------//
//							???? ???? â.
#define LEADER_WARINFO_BG_X							(LEADER_BGR_X)// + 22)
#define LEADER_WARINFO_BG_Y							(LEADER_BGR_Y)// + 8)


// 2009. 01. 12 by ckPark ???? ???? ?ý???
//#define LEADER_WARINFO_TAB_W						(116)
#define LEADER_WARINFO_TAB_W						(91)
// end 2009. 01. 12 by ckPark ???? ???? ?ý???


#define LEADER_WARINFO_TAB_H						(25)
#define LEADER_WARINFO_TAB_Y						(LEADER_BGR_Y)
#define LEADER_WARINFO_TAB_INFLUENCE_X				(LEADER_BGR_X)
#define LEADER_WARINFO_TAB_MOTHERSHIP_X				(LEADER_WARINFO_TAB_INFLUENCE_X + LEADER_WARINFO_TAB_W)
#define LEADER_WARINFO_TAB_OUTPOST_X				(LEADER_WARINFO_TAB_MOTHERSHIP_X + LEADER_WARINFO_TAB_W)
#define LEADER_WARINFO_TAB_WARPOINT_X				(LEADER_WARINFO_TAB_OUTPOST_X + LEADER_WARINFO_TAB_W)

// ?????? ??
#define WARINFO_INFLUENCE_BG1_X						(LEADER_BGR_X + 18)
#define WARINFO_INFLUENCE_BG1_Y						(LEADER_BGR_Y + 45)
#define WARINFO_INFLUENCE_BG2_X						(LEADER_BGR_X + 244)
#define WARINFO_INFLUENCE_BG2_Y						(LEADER_BGR_Y + 45)
#define WARINFO_INFLUENCE_FONT_POINT_H				31				
#define WARINFO_INFLUENCE_FONT_1_CENTER_X			(LEADER_BGR_X + 178)
#define WARINFO_INFLUENCE_FONT_2_CENTER_X			(LEADER_BGR_X + 405)
#define WARINFO_INFLUENCE_FONT_LEADER_Y				(LEADER_BGR_Y + 89)
#define WARINFO_INFLUENCE_FONT_LEADER1_Y			(WARINFO_INFLUENCE_FONT_LEADER_Y + WARINFO_INFLUENCE_FONT_POINT_H)
#define WARINFO_INFLUENCE_FONT_LEADER2_Y			(WARINFO_INFLUENCE_FONT_LEADER1_Y + WARINFO_INFLUENCE_FONT_POINT_H)
#define WARINFO_INFLUENCE_FONT_POINT_Y				(WARINFO_INFLUENCE_FONT_LEADER2_Y + WARINFO_INFLUENCE_FONT_POINT_H)

// ?????????? ??
#define WARINFO_OUTPOST_FONT_OUTPOST_CENTER_X		(LEADER_BGR_X + 56)
#define WARINFO_OUTPOST_FONT_INFLUENCE_CENTER_X		(LEADER_BGR_X + 119)
// 2007-12-17 by dgwoo ???????̽? ????.
#define WARINFO_OUTPOST_FONT_GUILD_CENTER_X			(LEADER_BGR_X + 247)
#define WARINFO_OUTPOST_FONT_GUILDLEADER_CENTER_X	(LEADER_BGR_X + 186)
#define WARINFO_OUTPOST_FONT_GUILDLEADER_W			70
//#define WARINFO_OUTPOST_FONT_GUILD_CENTER_X			(LEADER_BGR_X + 286)
#define WARINFO_OUTPOST_FONT_GUILDMARK_X			(LEADER_BGR_X + 240)
#define WARINFO_OUTPOST_FONT_GUILDNAME_X			(WARINFO_OUTPOST_FONT_GUILDMARK_X + 28)
#define WARINFO_OUTPOST_FONT_GUILDNAME_W			65
#define WARINFO_OUTPOST_FONT_SCHEDULE_CENTER_X		(LEADER_BGR_X + 396)

#define WARINFO_OUTPOST_FONT_DATA_1_Y				(LEADER_BGR_Y + 106)
#define WARINFO_OUTPOST_FONT_DATA_1_GUILDNAME_Y		(LEADER_BGR_Y + 97)
#define WARINFO_OUTPOST_FONT_DATA_1_GUILDLEADER_Y	(LEADER_BGR_Y + 112)
#define WARINFO_OUTPOST_GUILDMARK_1_Y				(WARINFO_OUTPOST_FONT_DATA_1_GUILDNAME_Y + 3)
#define WARINFO_OUTPOST_FONT_H						(32)

// 2008-03-19 by bhsohn ??????, ?????? ????â
// ????????ũ??
#define MOTHERSHIP_INFO_VIEW_MAX_SCROLL_LINE		5
#define MOTHERSHIP_INFO_VIEW_SCROLL_X			(LEADER_BGR_X + 476)
#define MOTHERSHIP_INFO_VIEW_SCROLL_Y			(LEADER_BGR_Y + 74)
#define MOTHERSHIP_INFO_VIEW_SCROLL_W			11
#define MOTHERSHIP_INFO_VIEW_SCROLL_H			93
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_X		(LEADER_BGR_X + 55)
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_Y		(LEADER_BGR_Y + 74)
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_W		434
#define MOTHERSHIP_INFO_VIEW_SCROLL_WHELL_H		133
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_X		(LEADER_BGR_X + 465)
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_Y		(LEADER_BGR_Y + 74)
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_W		32
#define MOTHERSHIP_INFO_VIEW_SCROLL_BALL_H		123

// ?????۵? ??ġ
// ???? ????
#define MOTHERSHIP_WARINFO_VIEW_ATT_INFL_X			(LEADER_BGR_X + 52)
#define MOTHERSHIP_WARINFO_VIEW_ATT_INFL_Y			(LEADER_BGR_Y + 71)
#define MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_X		(LEADER_BGR_X + 52)
#define MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_Y		(LEADER_BGR_Y + 83)
#define MOTHERSHIP_WARINFO_VIEW_POINT_X				(LEADER_BGR_X + 135)
#define MOTHERSHIP_WARINFO_VIEW_POINT_Y				(LEADER_BGR_Y + 77)
#define MOTHERSHIP_WARINFO_VIEW_TIME_X				(LEADER_BGR_X + 289)
#define MOTHERSHIP_WARINFO_VIEW_TIME_Y				(LEADER_BGR_Y + 77)
#define MOTHERSHIP_WARINFO_VIEW_WININFL_X			(LEADER_BGR_X + 437)
#define MOTHERSHIP_WARINFO_VIEW_WININFL_Y			(LEADER_BGR_Y + 77)
#define MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT			(27)

// ??????
#define POINTWAR_WARINFO_VIEW_ATT_INFL_X			(LEADER_BGR_X + 37)
#define POINTWAR_WARINFO_VIEW_ATT_INFL_Y			(LEADER_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_POINT_X				(LEADER_BGR_X + 117)
#define POINTWAR_WARINFO_VIEW_POINT_Y				(LEADER_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_TIME_X				(LEADER_BGR_X + 289)
#define POINTWAR_WARINFO_VIEW_TIME_Y				(LEADER_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_WININFL_X				(LEADER_BGR_X + 437)
#define POINTWAR_WARINFO_VIEW_WININFL_Y				(LEADER_BGR_Y + 83)
#define POINTWAR_WARINFO_VIEW_CAP_HEIGHT			(27)

// ?????? ???? ?ɼ?
#define MOTHERSHIP_OPTION_X							(LEADER_BGR_X + 353)
#define MOTHERSHIP_OPTION_Y 						(LEADER_BGR_Y + 212)

// end 2008-03-19 by bhsohn ??????, ?????? ????â



// 2009. 01. 12 by ckPark ???? ???? ?ý???
#define WARDECLARE_BTN_X							(LEADER_BGR_X + 200)
#define WARDECLARE_BTN_Y 							(LEADER_BGR_Y + 212)

#define OUR_THIS_TAKEOFF_X							(LEADER_BGR_X + 43)
#define OUR_THIS_TAKEOFF_Y							(LEADER_BGR_Y + 81)
#define OUR_NEXT_TAKEOFF_X							(LEADER_BGR_X + 43)
#define OUR_NEXT_TAKEOFF_Y							(LEADER_BGR_Y + 142)

#define ENEMY_THIS_TAKEOFF_X						(LEADER_BGR_X + 275)
#define ENEMY_THIS_TAKEOFF_Y						(LEADER_BGR_Y + 81)
#define ENEMY_NEXT_TAKEOFF_X						(LEADER_BGR_X + 275)
#define ENEMY_NEXT_TAKEOFF_Y						(LEADER_BGR_Y + 142)

#define OUR_THIS_TAKEOFFTIME_X						(LEADER_BGR_X + 48)
#define OUR_THIS_TAKEOFFTIME_Y						(LEADER_BGR_Y + 105)
#define OUR_NEXT_TAKEOFFTIME_X						(LEADER_BGR_X + 48)
#define OUR_NEXT_TAKEOFFTIME_Y						(LEADER_BGR_Y + 167)

#define ENEMY_THIS_TAKEOFFTIME_X					(LEADER_BGR_X + 280)
#define ENEMY_THIS_TAKEOFFTIME_Y					(LEADER_BGR_Y + 105)
#define ENEMY_NEXT_TAKEOFFTIME_X					(LEADER_BGR_X + 280)
#define ENEMY_NEXT_TAKEOFFTIME_Y					(LEADER_BGR_Y + 167)

// end 2009. 01. 12 by ckPark ???? ???? ?ý???



// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
// ??ũ?? ?? ????
#define	MAX_SCROLL_LINE			7
#define	SCROLL_BALL_POSX					288
#define	SCROLL_BALL_POSY					78
#define	SCROLL_BALL_WIDTH					11
#define	SCROLL_BALL_SCROLL_CAP				30

#define	SCROLL_WIDTH						330
#define	SCROLL_HEIGHT						78
#define	SCROLL_WHELL_HEIGHT					150
// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????

// 2008-08-19 by bhsohn ??????, ?????? ???? ??ȯ ?ð????? ????
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
// end 2008-08-19 by bhsohn ??????, ?????? ???? ??ȯ ?ð????? ????



//--------------------------------------------------------------------------//

#define	MAX_NEXT_WAR_RADIO							3

//--------------------------------------------------------------------------//

#define STRING_CULL ::StringCullingUserDataEx	

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityLeader::CINFCityLeader(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	m_pParent = pParent;	// CGameMain*
	m_pBuildingInfo = pBuilding;

	m_pFontExp		= NULL;

	m_fExplate = 0.0f;
	m_nCumulativeExp = 	m_nExp = 0;

	m_nSelWarTimeRadioB		= 0;
	m_nWarTimeMaxCount		= MAX_NEXT_WAR_RADIO;	
	m_BPollState			= LEADER_POLL_LIST;
	m_pImgPAppB				= NULL;
	m_pImgPUnAppB			= NULL;
	m_nRSelectB_1			= 0;
	m_nRSelectB_2			= BUTTON_BOTH_STATE_NORMAL;
	m_nBrigadeNoticeB		= BUTTON_STATE_NORMAL;
	m_nDelB					= BUTTON_STATE_NORMAL;
	m_nExpenceB				= BUTTON_STATE_NORMAL;
	m_nExpenceOkB			= BUTTON_STATE_NORMAL;
	m_nOkB					= BUTTON_STATE_NORMAL;
	m_nRevB					= BUTTON_STATE_NORMAL;

	// ????????.
	m_nLPollB				= BUTTON_STATE_NORMAL;
	m_nLDateB				= BUTTON_STATE_NORMAL;
	m_nPInfoB				= BUTTON_STATE_NORMAL;
	m_nRVoteB				= BUTTON_STATE_NORMAL;
	m_nRSelectB_2			= BUTTON_BOTH_STATE_NORMAL;	

	// 2007-09-05 by bhsohn ???? ??????
	///////////////////???? ????///////////////////
	m_pNoticeWrite = NULL;
	m_pRegist = NULL;
	m_pNoticeEditBox = NULL;
	m_pEditPledge = NULL;
	m_pEditPledgeView = NULL;
	///////////////////?ǰ??? ????///////////////////	
	m_pExpenceOkBtn = NULL;
	m_pWarNextOkBtn = NULL;

	
	///////////////////???? ?ð? ???? ???? ó??///////////////////	
	m_vecNextWarTimeList.clear();
	m_OutPostNextWarTime.Year 
		= m_OutPostNextWarTime.Month 
		= m_OutPostNextWarTime.Day 
		= m_OutPostNextWarTime.Hour 
		= m_OutPostNextWarTime.Minute 
		= m_OutPostNextWarTime.Second = 0;

	m_pImgGuildMark				= NULL;
	m_pImgFace					= NULL;
	m_pPilotFace				= NULL;

	m_pScrollPollList			= NULL;
	m_pScrollPollPledge			= NULL;
	m_pScrollPollPledgeView		= NULL;


	// 2008-03-19 by bhsohn ??????, ?????? ????â
	m_pScrollMotherShipInfo			= NULL;
	m_pFontWarInfo		= NULL;
	m_pBtnMotherShipInfo = NULL;


	// 2009. 01. 12 by ckPark ???? ???? ?ý???
	m_pFontWarDeclare	= NULL;
	m_pBtnWarDeclare		= NULL;
	// end 2009. 01. 12 by ckPark ???? ???? ?ý???


	m_nSelectNum				= -1;

	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	m_pINFScrollBar = NULL;
	
}

CINFCityLeader::~CINFCityLeader()
{

}
void CINFCityLeader::ButtonClickWrite()
{
//	memset(m_cNoticeString,0x00,SIZE_MAX_NOTICE);
//	m_bWriteMode = TRUE;
	char chBlank[16];
	memset(chBlank, 0x00, 16);

	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	m_pNoticeEditBox->SetString(chBlank, 16, 0, TRUE);		// ????
	m_pNoticeEditBox->EnableEdit(TRUE, FALSE);
	
	m_pNoticeEditBox->BackupTxtString();	
	m_pINFScrollBar->SetMaxItem(0);
}

void CINFCityLeader::ButtonClickApp()
{
	//m_bWriteMode = FALSE;
	m_pNoticeEditBox->EnableEdit(FALSE, FALSE);
	MSG_FC_INFO_NOTICE_REG sMsg;
	memset(&sMsg, 0x00, sizeof(MSG_FC_INFO_NOTICE_REG));
	sMsg.GuildUID = g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber;		
	m_pNoticeEditBox->GetString(sMsg.NoticeString, SIZE_MAX_NOTICE);

	g_pFieldWinSocket->SendMsg(T_FC_INFO_NOTICE_REG,(char*)&sMsg,sizeof(sMsg));
}
void CINFCityLeader::ButtonClickPollApp()
{// ?ĺ? ???? ??ư.
	ChangePollState(LEADER_POLL_APP);
}
void CINFCityLeader::ButtonClickPollAppSuc()
{// ?ڽ??? ?ĺ??? ????.
	m_pNoticeEditBox->EnableEdit(FALSE, FALSE);	
	MSG_FC_CITY_POLL_REG_LEADER_CANDIDATE sMsg;
	sMsg.CharacterUID		= g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber;
	sMsg.GuildUID			= g_pShuttleChild->GetMyShuttleInfo().GuildUniqueNumber;
	m_pEditPledge->GetString(sMsg.CampaignPromises,SIZE_MAX_CAMPAIGNPROMISES);
	g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_REG_LEADER_CANDIDATE,(char*)&sMsg,sizeof(sMsg));
}
void CINFCityLeader::ButtonClickPollInfo()
{// ?ĺ? ???? ??û.
	SendCandidateInfo();
}

INT CINFCityLeader::SetChangeRadioButton(INT i_nSel)
{
	m_nSelWarTimeRadioB = i_nSel;
	return m_nSelWarTimeRadioB;
}
void CINFCityLeader::SetNotice(char *i_szNotice)
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
		wsprintf(chBuff, STRMSG_C_070816_0102);
	}	
	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	//int nLine = m_pNoticeEditBox->SetString(chBuff, strlen(chBuff)+1);	
	int nLine = m_pNoticeEditBox->SetString(chBuff, strlen(chBuff)+1, 0, TRUE);	
	
	m_pINFScrollBar->SetMaxItem(nLine);
}

void CINFCityLeader::ChangeLeaderState(DWORD i_dState)
{
	m_nRWindowState = i_dState;
	MapIndex_t	MapIndex = g_pShuttleChild->GetShuttleInfo()->MapChannelIndex.MapIndex;

	BOOL bShowBtn = FALSE;
	if(g_pD3dApp->IsMyShuttleLeader())
	{
		bShowBtn = TRUE;
	}

	switch(m_nRWindowState)
	{
	case LEADER_STATE_NOTICE:
		{			
			m_pNoticeWrite->ShowWindow(bShowBtn);
			m_pRegist->ShowWindow(bShowBtn);

			MSG_FC_INFO_NOTICE_REQUEST sMsg;
			sMsg.NoticeState = NOTICE_LEADER;
			sMsg.MapIndex = MapIndex;
			g_pFieldWinSocket->SendMsg(T_FC_INFO_NOTICE_REQUEST,(char*)&sMsg,sizeof(sMsg));
		}
		break;
	case LEADER_STATE_EXPENCE:
		{
			m_pExpenceOkBtn->ShowWindow(bShowBtn);

			MSG_FC_INFO_EXPEDIENCYFUND_REQUEST sMsg;
			sMsg.MapIndex = MapIndex;
			g_pFieldWinSocket->SendMsg(T_FC_INFO_EXPEDIENCYFUND_REQUEST,(char*)&sMsg,sizeof(sMsg));
		}
		break;
	case LEADER_STATE_POLL:
		{// ?ĺ??? ?? ?ĺ? ????Ʈ.
			//ChangePollState(LEADER_POLL_LIST);
			//SendLeaderCandidateList();
		}
		break;
	case LEADER_STATE_POLLDATE:
		{// ???? ????.
			g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_REQUEST_POLL_DATE,NULL,NULL);
		}
		break;
	case LEADER_STATE_WARINFO:
		{// ???? ????.
			ChangeWarInfoState(LEADER_WARINFO_INFLUENCE);
		}
		break;
	}
}
HRESULT CINFCityLeader::InitDeviceObjects()
{
	DataHeader	* pDataHeader;
	int i,j;
	char buf[16];

	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	{			
		char  szScBall[30];	
		if(NULL == m_pINFScrollBar)
		{
			m_pINFScrollBar = new CINFArenaScrollBar;
		}		
		wsprintf(szScBall,"c_scrlb");
		
		m_pINFScrollBar->InitDeviceObjects(MAX_SCROLL_LINE, szScBall);
	}
	// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????

	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i] = new CINFImage;
		//wsprintf(buf, "Onotice%d",i);
		wsprintf(buf, "inflnotb%d",i);
		
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


		m_pImgWriteB[i] = new CINFImage;
		wsprintf(buf, "Owrite%d",i);
		pDataHeader = FindResource(buf);
		m_pImgWriteB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgRevB[i] = new CINFImage;
		wsprintf(buf, "Orev%d",i);
		pDataHeader = FindResource(buf);
		m_pImgRevB[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	}
	for(j= 0 ; j < BUTTON_BOTH_STATE_NUMBER ; j++)
	{
		for(i = 0 ; i < BUTTON_BOTH_STATE_NUMBER ; i++)
		{
			m_pImgRSelectB[j][i] = new CINFImage;
			wsprintf(buf, "lselectB%d%d",j,i);
			pDataHeader = FindResource(buf);
			m_pImgRSelectB[j][i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

		}
	}
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

	m_pImgTitle = new CINFImage;
	pDataHeader = FindResource("aleader");				
	m_pImgTitle->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgOutPostLBG = new CINFImage;
	pDataHeader = FindResource("outpostB");
	m_pImgOutPostLBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgBriNoticeBG = new CINFImage;
	//pDataHeader = FindResource("OnoticeB");
	pDataHeader = FindResource("inflnotB");
	
	m_pImgBriNoticeBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgPollDateABG = new CINFImage;
	pDataHeader = FindResource("pdateaBG");
	m_pImgPollDateABG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgPollDateVBG = new CINFImage;
	pDataHeader = FindResource("pdatevBG");
	m_pImgPollDateVBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgExpenceBG = new CINFImage;
	pDataHeader = FindResource("lexpenB");
	m_pImgExpenceBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pFontExp = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontExp->InitDeviceObjects(g_pD3dDev);

	m_pImgVniBG = new CINFImage;
	pDataHeader = FindResource("lvniBG");
	m_pImgVniBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgAniBG = new CINFImage;
	pDataHeader = FindResource("laniBG");
	m_pImgAniBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgListBG = new CINFImage;
	pDataHeader = FindResource("llistBG");
	m_pImgListBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgRSelect = new CINFImage;
	pDataHeader = FindResource("lselect");
	m_pImgRSelect->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgPInfoBG = new CINFImage;
	pDataHeader = FindResource("pinfoBG");
	m_pImgPInfoBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgAppBG = new CINFImage;
	pDataHeader = FindResource("pledgeBG");
	m_pImgAppBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pPilotFace = new CINFPilotFace;
	m_pPilotFace->InitDeviceObjects("face.tex");

	


	{
		char szButtonName[32];

		// 2007-10-16 by dgwoo ?? ?ý??? 
		// ?˸??? ?? ??ư.
		wsprintf(szButtonName, "LpollaB");
		if(NULL == m_pImgLPollAB)
		{
			m_pImgLPollAB = new CINFImageBtn;
		}
		m_pImgLPollAB->InitDeviceObjects(szButtonName);	

		// ?????????? ?? ??ư.

		wsprintf(szButtonName,"LpollvB");
		if(NULL == m_pImgLPollVB)
		{
			m_pImgLPollVB = new CINFImageBtn;
		}
		m_pImgLPollVB->InitDeviceObjects(szButtonName);	

		// ???? ???? ??ư.
		wsprintf(szButtonName,"LdateB");
		if(NULL == m_pImgLDateB)
		{
			m_pImgLDateB = new CINFImageBtn;
		}
		m_pImgLDateB->InitDeviceObjects(szButtonName);	
		// ???? ???? ??ư.
		wsprintf(szButtonName,"warfieldB");
		if(NULL == m_pImgLWarInfoB)
		{
			m_pImgLWarInfoB = new CINFImageBtn;
		}
		m_pImgLWarInfoB->InitDeviceObjects(szButtonName);
		// ?ĺ? ???? ??ư.
		wsprintf(szButtonName,"pinfoB");
		if(NULL == m_pImgPInfoB)
		{
			m_pImgPInfoB = new CINFImageBtn;
		}
		m_pImgPInfoB->InitDeviceObjects(szButtonName);	
		// ??ǥ ??ư.
		wsprintf(szButtonName,"pollB");
		if(NULL == m_pImgRVoteB)
		{
			m_pImgRVoteB = new CINFImageBtn;
		}
		m_pImgRVoteB->InitDeviceObjects(szButtonName);	
		// ?ĺ? ???? ??ư.
		wsprintf(szButtonName,"pappB");
		if(NULL == m_pImgPAppB)
		{
			m_pImgPAppB = new CINFImageBtn;
		}
		m_pImgPAppB->InitDeviceObjects(szButtonName);	
		// ?ĺ? Ż?? ??ư.
		wsprintf(szButtonName,"punappB");
		if(NULL == m_pImgPUnAppB)
		{
			m_pImgPUnAppB = new CINFImageBtn;
		}
		m_pImgPUnAppB->InitDeviceObjects(szButtonName);	

		wsprintf(szButtonName,"pleappB");
		if(NULL == m_pImgAppSucB)
		{
			m_pImgAppSucB = new CINFImageBtn;
		}
		m_pImgAppSucB->InitDeviceObjects(szButtonName);
	}
	// 2007-09-05 by bhsohn ???? ??????
	// ??ư
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

	// ????Ʈ ?ڽ?
	{
		if(NULL == m_pNoticeEditBox)
		{
			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
			//m_pNoticeEditBox = new CINFEditBox;
			m_pNoticeEditBox = new CINFCurselEditBox;
		}
		POINT ptPos = {LEADER_NOTICE_EDIT_X, LEADER_NOTICE_EDIT_Y};
		m_pNoticeEditBox->InitDeviceObjects(9, ptPos, LEADER_NOTICE_EDIT_W, TRUE, LEADER_NOTICE_FONT_LINE_HEIGHT);		
		m_pNoticeEditBox->SetOnePageItemCnt(MAX_SCROLL_LINE);	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????

		SetNotice(STRMSG_C_070816_0102);
	}
	// ???? ????Ʈ ?ڽ?.
	{
		if(NULL == m_pEditPledge)
		{
			//m_pEditPledge = new CINFEditBox;
			m_pEditPledge = new CINFCurselEditBox;
		}
		POINT ptPos = {LEADER_POLL_PLEDGE_EDIT_X,LEADER_POLL_PLEDGE_EDIT_Y};
		m_pEditPledge->InitDeviceObjects(9,ptPos,LEADER_POLL_PLEDGE_EDIT_W,TRUE,LEADER_NOTICE_FONT_LINE_HEIGHT);
		m_pEditPledge->SetStringMaxBuff(SIZE_MAX_STRING_512);
		m_pEditPledge->SetOnePageItemCnt(LEADER_POLL_PLEDGE_MAX_SCROLL_LINE);	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	}
	// ???? ?? ????Ʈ ?ڽ?.
	{
		if(NULL == m_pEditPledgeView)
		{
			m_pEditPledgeView = new CINFEditBox;
		}
		POINT ptPos = {LEADER_POLL_PLEDGE_VIEW_EDIT_X,LEADER_POLL_PLEDGE_VIEW_EDIT_Y};
		m_pEditPledgeView->InitDeviceObjects(9,ptPos,LEADER_POLL_PLEDGE_VIEW_EDIT_W,TRUE,LEADER_NOTICE_FONT_LINE_HEIGHT);
	}

	// ?ǰ??? ????
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

	// Ȯ?? ??ư
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
	// ??ũ??
	{
		char  szScBall[30];	
		// ?? ????Ʈ.
		if(NULL == m_pScrollPollList)
		{
			m_pScrollPollList = new CINFArenaScrollBar;
		}		
		wsprintf(szScBall,"c_scrlb");
		m_pScrollPollList->InitDeviceObjects(LEADER_POLL_LIST_MAX_SCROLL_LINE, szScBall);
		// ???? ?ۼ? ????Ʈ ?ڽ?.
		if(NULL == m_pScrollPollPledge)
		{
			m_pScrollPollPledge = new CINFArenaScrollBar;
		}
		wsprintf(szScBall,"c_scrlb");
		m_pScrollPollPledge->InitDeviceObjects(LEADER_POLL_PLEDGE_MAX_SCROLL_LINE,szScBall);
		// ???? ?ۼ??? ????Ʈ ?? ?ڽ?.(?ĺ? ????)
		if(NULL == m_pScrollPollPledgeView)
		{
			m_pScrollPollPledgeView = new CINFArenaScrollBar;
		}
		wsprintf(szScBall,"c_scrlb");
		m_pScrollPollPledgeView->InitDeviceObjects(LEADER_POLL_PLEDGE_VIEW_MAX_SCROLL_LINE,szScBall);

		// ??????
		// 2008-03-19 by bhsohn ??????, ?????? ????â
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
		// end 2008-03-19 by bhsohn ??????, ?????? ????â


		// 2009. 01. 12 by ckPark ???? ???? ?ý???
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
		// end 2009. 01. 12 by ckPark ???? ???? ?ý???
	}


	// 
	ChangeLeaderState(LEADER_STATE_NOTICE);
	m_BInfluence = g_pShuttleChild->m_myShuttleInfo.InfluenceType;

	if(g_pD3dApp->IsMyShuttleLeader())
	{
		m_nExpenceB = BUTTON_STATE_NORMAL;
	}
	else
	{
		m_nExpenceB = BUTTON_STATE_DISABLE;
	}


	return S_OK;
}
HRESULT CINFCityLeader::RestoreDeviceObjects()
{
	int j,i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i]->RestoreDeviceObjects() ;
		m_pImgDelB[i]->RestoreDeviceObjects() ;
		m_pImgExpenceB[i]->RestoreDeviceObjects() ;
		m_pImgWriteB[i]->RestoreDeviceObjects() ;
		m_pImgRevB[i]->RestoreDeviceObjects() ;
		

	}
	for(i = 0 ; i < LEADER_WARINFO_END ; i++)
	{
		m_pImgWarInfoBG[i]->RestoreDeviceObjects();
	}
	m_pImgWarInfoInflAni->RestoreDeviceObjects();
	m_pImgWarInfoInflBcu->RestoreDeviceObjects();
	m_pImgTitle->RestoreDeviceObjects();
	m_pImgOutPostLBG->RestoreDeviceObjects();
	m_pImgBriNoticeBG->RestoreDeviceObjects();
	m_pImgPollDateABG->RestoreDeviceObjects();
	m_pImgPollDateVBG->RestoreDeviceObjects();
	m_pImgExpenceBG->RestoreDeviceObjects();
	m_pFontExp->RestoreDeviceObjects();
	// 2008-03-19 by bhsohn ??????, ?????? ????â
	m_pFontWarInfo->RestoreDeviceObjects();

	m_pImgPInfoBG->RestoreDeviceObjects();
	m_pImgVniBG->RestoreDeviceObjects();
	m_pImgAniBG->RestoreDeviceObjects();
	m_pImgListBG->RestoreDeviceObjects();
	m_pImgRSelect->RestoreDeviceObjects();
	m_pImgAppBG->RestoreDeviceObjects();
	m_pPilotFace->RestoreDeviceObjects();
	for(j= 0 ; j < BUTTON_BOTH_STATE_NUMBER ; j++)
	{
		for(i = 0 ; i < BUTTON_BOTH_STATE_NUMBER ; i++)
		{
			m_pImgRSelectB[j][i]->RestoreDeviceObjects();
		}
	}
	
	{
		
		// ?? ?ý??? ??ư.
		m_pImgLPollAB->RestoreDeviceObjects();
		m_pImgLPollAB->SetBtnPosition(LEADER_POLL_BUTTON_X,LEADER_POLL_BUTTON_Y);

		m_pImgLPollVB->RestoreDeviceObjects();
		m_pImgLPollVB->SetBtnPosition(LEADER_POLL_BUTTON_X,LEADER_POLL_BUTTON_Y);

		m_pImgLDateB->RestoreDeviceObjects();
		m_pImgLDateB->SetBtnPosition(LEADER_POLL_DATE_BUTTON_X,LEADER_POLL_DATE_BUTTON_Y);

		m_pImgLWarInfoB->RestoreDeviceObjects();
		m_pImgLWarInfoB->SetBtnPosition(LEADER_WARINFO_BUTTON_X,LEADER_WARINFO_BUTTON_Y);

		m_pImgPInfoB->RestoreDeviceObjects();
		m_pImgPInfoB->SetBtnPosition(LEADER_POLL_INFO_BUTTON_X,LEADER_POLL_INFO_BUTTON_Y);

		m_pImgRVoteB->RestoreDeviceObjects();
		m_pImgRVoteB->SetBtnPosition(LEADER_POLL_VOTE_BUTTON_X,LEADER_POLL_VOTE_BUTTON_Y);

		m_pImgPAppB->RestoreDeviceObjects();
		m_pImgPAppB->SetBtnPosition(LEADER_POLL_APP_BUTTON_X,LEADER_POLL_APP_BUTTON_Y);

		m_pImgPUnAppB->RestoreDeviceObjects();
		m_pImgPUnAppB->SetBtnPosition(LEADER_POLL_APP_BUTTON_X,LEADER_POLL_APP_BUTTON_Y);

		m_pImgAppSucB->RestoreDeviceObjects();
		m_pImgAppSucB->SetBtnPosition(LEADER_POLL_LIST_BUTTON_X,LEADER_POLL_LIST_BUTTON_Y);
	}
	// 2007-09-05 by bhsohn ???? ??????
	{	
		
		float fPosX = LEADER_WRITE_BUTTON_X;
		float fPosY = LEADER_WRITE_BUTTON_Y;		

		m_pNoticeWrite->RestoreDeviceObjects();		
		m_pNoticeWrite->SetBtnPosition(fPosX, fPosY);
	}

	// ????
	{			
		float fPosX = LEADER_APP_BUTTON_X;
		float fPosY = LEADER_APP_BUTTON_Y;		

		m_pRegist->RestoreDeviceObjects();		
		m_pRegist->SetBtnPosition(fPosX, fPosY);
	}
	
	// ?ǰ??? ????
	{			
		float fPosX = LEADER_EXPENCE_OK_BUTTON_X;
		float fPosY = LEADER_EXPENCE_OK_BUTTON_Y;		

		m_pExpenceOkBtn->RestoreDeviceObjects();		
		m_pExpenceOkBtn->SetBtnPosition(fPosX, fPosY);
	}
	
	{			
		float fPosX = LEADER_OK_BUTTON_X;
		float fPosY = LEADER_OK_BUTTON_Y;		

		m_pWarNextOkBtn->RestoreDeviceObjects();		
		m_pWarNextOkBtn->SetBtnPosition(fPosX, fPosY);
	}
	// 
	{
		m_pNoticeEditBox->RestoreDeviceObjects();	
		m_pEditPledge->RestoreDeviceObjects();
		m_pEditPledgeView->RestoreDeviceObjects();
	}
	// ??ũ??.
	{
		//POINT ptScroll;
		RECT rcMouseWhell, rcMousePos;
		// ????Ʈ ??ũ??.
		m_pScrollPollList->RestoreDeviceObjects();
		m_pScrollPollList->SetPosition(LEADER_POLL_LIST_SCROLL_X,LEADER_POLL_LIST_SCROLL_Y,LEADER_POLL_LIST_SCROLL_W,LEADER_POLL_LIST_SCROLL_H);
		rcMouseWhell.left		= LEADER_POLL_LIST_SCROLL_WHELL_X;
		rcMouseWhell.top		= LEADER_POLL_LIST_SCROLL_WHELL_Y;
		rcMouseWhell.right		= LEADER_POLL_LIST_SCROLL_WHELL_X + LEADER_POLL_LIST_SCROLL_WHELL_W;
		rcMouseWhell.bottom		= LEADER_POLL_LIST_SCROLL_WHELL_Y + LEADER_POLL_LIST_SCROLL_WHELL_H;
		m_pScrollPollList->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= LEADER_POLL_LIST_SCROLL_BALL_X;
		rcMousePos.top			= LEADER_POLL_LIST_SCROLL_BALL_Y;
		rcMousePos.right		= LEADER_POLL_LIST_SCROLL_BALL_X + LEADER_POLL_LIST_SCROLL_BALL_W;
		rcMousePos.bottom		= LEADER_POLL_LIST_SCROLL_BALL_Y + LEADER_POLL_LIST_SCROLL_BALL_H;
		m_pScrollPollList->SetMouseBallRect(rcMousePos);
		
		// ???? ????Ʈ ?ڽ? ??ũ??.
		m_pScrollPollPledge->RestoreDeviceObjects();
		m_pScrollPollPledge->SetPosition(LEADER_POLL_PLEDGE_SCROLL_X,LEADER_POLL_PLEDGE_SCROLL_Y,LEADER_POLL_PLEDGE_SCROLL_W,LEADER_POLL_PLEDGE_SCROLL_H);
		rcMouseWhell.left		= LEADER_POLL_PLEDGE_SCROLL_WHELL_X;
		rcMouseWhell.top		= LEADER_POLL_PLEDGE_SCROLL_WHELL_Y;
		rcMouseWhell.right		= LEADER_POLL_PLEDGE_SCROLL_WHELL_X + LEADER_POLL_PLEDGE_SCROLL_WHELL_W;
		rcMouseWhell.bottom		= LEADER_POLL_PLEDGE_SCROLL_WHELL_Y + LEADER_POLL_PLEDGE_SCROLL_WHELL_H;
		m_pScrollPollPledge->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= LEADER_POLL_PLEDGE_SCROLL_BALL_X;
		rcMousePos.top			= LEADER_POLL_PLEDGE_SCROLL_BALL_Y;
		rcMousePos.right		= LEADER_POLL_PLEDGE_SCROLL_BALL_X + LEADER_POLL_PLEDGE_SCROLL_BALL_W;
		rcMousePos.bottom		= LEADER_POLL_PLEDGE_SCROLL_BALL_Y + LEADER_POLL_PLEDGE_SCROLL_BALL_H;
		m_pScrollPollPledge->SetMouseBallRect(rcMousePos);
		// ???? ??(????Ʈ)?ڽ? ??ũ??.
		m_pScrollPollPledgeView->RestoreDeviceObjects();
		m_pScrollPollPledgeView->SetPosition(LEADER_POLL_PLEDGE_VIEW_SCROLL_X,LEADER_POLL_PLEDGE_VIEW_SCROLL_Y,LEADER_POLL_PLEDGE_VIEW_SCROLL_W,LEADER_POLL_PLEDGE_VIEW_SCROLL_H);
		rcMouseWhell.left		= LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_X;
		rcMouseWhell.top		= LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_Y;
		rcMouseWhell.right		= LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_X + LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_W;
		rcMouseWhell.bottom		= LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_Y + LEADER_POLL_PLEDGE_VIEW_SCROLL_WHELL_H;
		m_pScrollPollPledgeView->SetMouseWhellRect(rcMouseWhell);
		rcMousePos.left			= LEADER_POLL_LIST_SCROLL_BALL_X;
		rcMousePos.top			= LEADER_POLL_LIST_SCROLL_BALL_Y;
		rcMousePos.right		= LEADER_POLL_LIST_SCROLL_BALL_X + LEADER_POLL_LIST_SCROLL_BALL_W;
		rcMousePos.bottom		= LEADER_POLL_LIST_SCROLL_BALL_Y + LEADER_POLL_LIST_SCROLL_BALL_H;
		m_pScrollPollPledgeView->SetMouseBallRect(rcMousePos);

		// 2008-03-19 by bhsohn ??????, ?????? ????â
		// ?????? ????
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
		
		// 2009. 01. 12 by ckPark ???? ???? ?ý???

		m_pFontWarDeclare->RestoreDeviceObjects();

		if(m_pBtnWarDeclare)
		{
			m_pBtnWarDeclare->RestoreDeviceObjects();		
			m_pBtnWarDeclare->SetBtnPosition(WARDECLARE_BTN_X, WARDECLARE_BTN_Y);
		}
		// end 2009. 01. 12 by ckPark ???? ???? ?ý???
	}
	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	{		
		m_pINFScrollBar->RestoreDeviceObjects();		
		UpdateScrollPos((LEADER_BGR_X), (LEADER_BGR_Y), SCROLL_WIDTH, SCROLL_HEIGHT, SCROLL_WHELL_HEIGHT);		
	}
	// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????

	return S_OK;
}
HRESULT CINFCityLeader::DeleteDeviceObjects()
{
	int j,i;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i]->DeleteDeviceObjects();
		m_pImgDelB[i]->DeleteDeviceObjects();
		m_pImgExpenceB[i]->DeleteDeviceObjects();
		m_pImgWriteB[i]->DeleteDeviceObjects();
		m_pImgRevB[i]->DeleteDeviceObjects();


		SAFE_DELETE(m_pImgBrigadeNoticeB[i]);
		SAFE_DELETE(m_pImgDelB[i]);
		SAFE_DELETE(m_pImgExpenceB[i]);
		SAFE_DELETE(m_pImgWriteB[i]);
		SAFE_DELETE(m_pImgRevB[i]);

	}
	for(i = 0 ; i < LEADER_WARINFO_END ; i++)
	{
		m_pImgWarInfoBG[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgWarInfoBG[i]);
	}
	
	m_pImgWarInfoInflAni->DeleteDeviceObjects();
	m_pImgWarInfoInflBcu->DeleteDeviceObjects();
	m_pImgTitle->DeleteDeviceObjects();
	m_pImgOutPostLBG->DeleteDeviceObjects();
	m_pImgBriNoticeBG->DeleteDeviceObjects();
	m_pImgPollDateABG->DeleteDeviceObjects();
	m_pImgPollDateVBG->DeleteDeviceObjects();
	m_pImgExpenceBG->DeleteDeviceObjects();
	m_pFontExp->DeleteDeviceObjects();
	// 2008-03-19 by bhsohn ??????, ?????? ????â
	m_pFontWarInfo->DeleteDeviceObjects();

	SAFE_DELETE(m_pImgWarInfoInflBcu);
	SAFE_DELETE(m_pImgWarInfoInflAni);
	SAFE_DELETE(m_pImgTitle);
	SAFE_DELETE(m_pImgOutPostLBG);
	SAFE_DELETE(m_pImgBriNoticeBG);
	SAFE_DELETE(m_pImgPollDateABG);
	SAFE_DELETE(m_pImgPollDateVBG);
	SAFE_DELETE(m_pImgExpenceBG);
	SAFE_DELETE(m_pFontExp);
	// 2008-03-19 by bhsohn ??????, ?????? ????â
	SAFE_DELETE(m_pFontWarInfo);
	
	for(j= 0 ; j < BUTTON_BOTH_STATE_NUMBER ; j++)
	{
		for(i = 0 ; i < BUTTON_BOTH_STATE_NUMBER ; i++)
		{
			m_pImgRSelectB[j][i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgRSelectB[j][i]);
		}
	}
	
	m_pImgPInfoBG->DeleteDeviceObjects();
	m_pImgVniBG->DeleteDeviceObjects();
	m_pImgAniBG->DeleteDeviceObjects();
	m_pImgListBG->DeleteDeviceObjects();
	m_pImgRSelect->DeleteDeviceObjects();
	m_pImgAppBG->DeleteDeviceObjects();
	m_pPilotFace->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgPInfoBG);
	SAFE_DELETE(m_pImgVniBG);
	SAFE_DELETE(m_pImgAniBG);
	SAFE_DELETE(m_pImgListBG);
	SAFE_DELETE(m_pImgRSelect);
	SAFE_DELETE(m_pImgAppBG);
	SAFE_DELETE(m_pPilotFace);


	m_pImgPAppB->DeleteDeviceObjects();
	m_pImgPUnAppB->DeleteDeviceObjects();
	m_pImgAppSucB->DeleteDeviceObjects();
	m_pImgLPollAB->DeleteDeviceObjects();
	m_pImgLPollVB->DeleteDeviceObjects();
	m_pImgLDateB->DeleteDeviceObjects();
	m_pImgLWarInfoB->DeleteDeviceObjects();
	m_pImgPInfoB->DeleteDeviceObjects();
	m_pImgRVoteB->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgPAppB);
	SAFE_DELETE(m_pImgPUnAppB);
	SAFE_DELETE(m_pImgAppSucB);
	SAFE_DELETE(m_pImgLPollAB);
	SAFE_DELETE(m_pImgLPollVB);
	SAFE_DELETE(m_pImgLDateB);
	SAFE_DELETE(m_pImgLWarInfoB);
	SAFE_DELETE(m_pImgPInfoB);
	SAFE_DELETE(m_pImgRVoteB);


	// 2007-09-05 by bhsohn ???? ??????
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
	if(m_pEditPledge)
	{
		m_pEditPledge->DeleteDeviceObjects();
		SAFE_DELETE(m_pEditPledge);
	}
	if(m_pEditPledgeView)
	{
		m_pEditPledgeView->DeleteDeviceObjects();
		SAFE_DELETE(m_pEditPledgeView);
	}
	if(m_pScrollPollList)
	{
		m_pScrollPollList->DeleteDeviceObjects();
		SAFE_DELETE(m_pScrollPollList);
	}
	if(m_pScrollPollPledge)
	{
		m_pScrollPollPledge->DeleteDeviceObjects();
		SAFE_DELETE(m_pScrollPollPledge);
	}
	if(m_pScrollPollPledgeView)
	{
		m_pScrollPollPledgeView->DeleteDeviceObjects();
		SAFE_DELETE(m_pScrollPollPledgeView);
	}

	// 2008-03-19 by bhsohn ??????, ?????? ????â
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
	// end 2008-03-19 by bhsohn ??????, ?????? ????â



	// 2009. 01. 12 by ckPark ???? ???? ?ý???
	m_pFontWarDeclare->DeleteDeviceObjects();

	SAFE_DELETE(m_pFontWarDeclare);
	
	if(m_pBtnWarDeclare)
	{
		m_pBtnWarDeclare->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnWarDeclare);
	}
	// end 2009. 01. 12 by ckPark ???? ???? ?ý???




	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	if(m_pINFScrollBar)
	{
		m_pINFScrollBar->DeleteDeviceObjects();	
		SAFE_DELETE(m_pINFScrollBar);
	}
	// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	

	
	return S_OK;
}
HRESULT CINFCityLeader::InvalidateDeviceObjects()
{
	int i,j;
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		m_pImgBrigadeNoticeB[i]->InvalidateDeviceObjects();
		m_pImgDelB[i]->InvalidateDeviceObjects();
		m_pImgExpenceB[i]->InvalidateDeviceObjects();
		m_pImgWriteB[i]->InvalidateDeviceObjects();
		m_pImgRevB[i]->InvalidateDeviceObjects();

	}

	m_pImgWarInfoInflAni->InvalidateDeviceObjects();
	m_pImgWarInfoInflBcu->InvalidateDeviceObjects();
	
	m_pImgTitle->InvalidateDeviceObjects();
	m_pImgOutPostLBG->InvalidateDeviceObjects();
	m_pImgBriNoticeBG->InvalidateDeviceObjects();
	m_pImgPollDateVBG->InvalidateDeviceObjects();
	m_pImgPollDateABG->InvalidateDeviceObjects();
	m_pImgExpenceBG->InvalidateDeviceObjects();
	m_pFontExp->InvalidateDeviceObjects();
	// 2008-03-19 by bhsohn ??????, ?????? ????â
	m_pFontWarInfo->InvalidateDeviceObjects();

	for(j= 0 ; j < BUTTON_BOTH_STATE_NUMBER ; j++)
	{
		for(i = 0 ; i < BUTTON_BOTH_STATE_NUMBER ; i++)
		{
			m_pImgRSelectB[j][i]->InvalidateDeviceObjects();
		}
	}
	for(i = 0 ; i < LEADER_WARINFO_END ; i++)
	{
		m_pImgWarInfoBG[i]->InvalidateDeviceObjects();
	}
	m_pImgVniBG->InvalidateDeviceObjects();
	m_pImgAniBG->InvalidateDeviceObjects();
	m_pImgListBG->InvalidateDeviceObjects();
	m_pImgRSelect->InvalidateDeviceObjects();
	m_pImgPInfoBG->InvalidateDeviceObjects();
	m_pImgAppBG->InvalidateDeviceObjects();

	m_pImgPAppB->InvalidateDeviceObjects();
	m_pImgPUnAppB->InvalidateDeviceObjects();
	m_pImgLPollAB->InvalidateDeviceObjects();
	m_pImgLPollVB->InvalidateDeviceObjects();
	m_pImgLDateB->InvalidateDeviceObjects();
	m_pImgLWarInfoB->InvalidateDeviceObjects();
	m_pImgPInfoB->InvalidateDeviceObjects();
	m_pImgRVoteB->InvalidateDeviceObjects();
	m_pImgAppSucB->InvalidateDeviceObjects();
	m_pPilotFace->InvalidateDeviceObjects();

	// 2007-09-05 by bhsohn ???? ??????
	m_pNoticeEditBox->InvalidateDeviceObjects();
	m_pEditPledge->InvalidateDeviceObjects();
	m_pEditPledgeView->InvalidateDeviceObjects();
	m_pNoticeWrite->InvalidateDeviceObjects();		
	m_pRegist->InvalidateDeviceObjects();		

	m_pExpenceOkBtn->InvalidateDeviceObjects();		
	m_pWarNextOkBtn->InvalidateDeviceObjects();		

	m_pScrollPollList->InvalidateDeviceObjects();
	m_pScrollPollPledge->InvalidateDeviceObjects();
	m_pScrollPollPledgeView->InvalidateDeviceObjects();
	// 2008-03-19 by bhsohn ??????, ?????? ????â
	m_pScrollMotherShipInfo->InvalidateDeviceObjects();
	if(m_pBtnMotherShipInfo)
	{
		m_pBtnMotherShipInfo->InvalidateDeviceObjects();		
	}


	// 2009. 01. 12 by ckPark ???? ???? ?ý???
	m_pFontWarDeclare->InvalidateDeviceObjects();
	
	if(m_pBtnWarDeclare)
		m_pBtnWarDeclare->InvalidateDeviceObjects();
	// end 2009. 01. 12 by ckPark ???? ???? ?ý???



	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	if(m_pINFScrollBar)
	{
		m_pINFScrollBar->InvalidateDeviceObjects();
	}
	// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????

	return S_OK;
}

void CINFCityLeader::Render()
{
	
	// ???? ????.
	m_pImgOutPostLBG->Move(LEADER_BGL_X,LEADER_BGL_Y);
	m_pImgOutPostLBG->Render();

	// Ÿ??Ʋ 	
	m_pImgTitle->Move(TITLE_POS_X,TITLE_POS_Y);
	m_pImgTitle->Render();	


	// ???? ??ư 
	m_pImgBrigadeNoticeB[m_nBrigadeNoticeB]->Move(LEADER_BRIGADE_NOTICE_BUTTON_X,LEADER_BRIGADE_NOTICE_BUTTON_Y);
	m_pImgBrigadeNoticeB[m_nBrigadeNoticeB]->Render();
	m_pImgExpenceB[m_nExpenceB]->Move(LEADER_EXPENCE_BUTTON_X,LEADER_EXPENCE_BUTTON_Y);
	m_pImgExpenceB[m_nExpenceB]->Render();
	if(INFLUENCE_TYPE_VCN == m_BInfluence)
	{
		m_pImgLPollVB->Render();
	}
	else
	{
		m_pImgLPollAB->Render();
	}
	m_pImgLDateB->Render();
	m_pImgLWarInfoB->Render();

	// ?????? â.
	switch(m_nRWindowState)
	{
	case LEADER_STATE_NOTICE:
		{// ???? ???? 
			// ????.
			m_pImgBriNoticeBG->Move(LEADER_BGR_X,LEADER_BGR_Y);
			m_pImgBriNoticeBG->Render();			
			
			// 2007-09-05 by bhsohn ???? ??????
			m_pNoticeWrite->Render();
			m_pRegist->Render();
			m_pNoticeEditBox->Tick();
			//m_pNoticeEditBox->Render(0, 7);
			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
			m_pNoticeEditBox->Render(m_pINFScrollBar->GetScrollStep(), MAX_SCROLL_LINE);
			m_pINFScrollBar->Render();		
			// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
			

		}
		break;
	case LEADER_STATE_EXPENCE:
		{// ?ǰ??? ????.
			// ????.
			m_pImgExpenceBG->Move(LEADER_BGR_X,LEADER_BGR_Y);
			m_pImgExpenceBG->Render();

			char temp1[512],temp2[512];
			SIZE size;
			
			sprintf(temp1,"%.1f%%",m_fExplate);
			size = m_pFontExp->GetStringSize(temp1);
			m_pFontExp->DrawText(LEADER_EXPENCE_LATE_FONT_X - size.cx,LEADER_EXPENCE_LATE_FONT_Y,GUI_FONT_COLOR,
				temp1, 0L);
			wsprintf(temp1,"%d",m_nCumulativeExp);                                                                                                                               
			MakeCurrencySeparator( temp2, temp1, 3, ',' );
			size = m_pFontExp->GetStringSize(temp2);
			m_pFontExp->DrawText(LEADER_EXPENCE_CUMEXP_FONT_X - size.cx,LEADER_EXPENCE_CUMEXP_FONT_Y,GUI_FONT_COLOR,
				temp2,0L);
			wsprintf(temp1,"%d",m_nExp);
			MakeCurrencySeparator( temp2, temp1, 3, ',' );
			size = m_pFontExp->GetStringSize(temp2);
			m_pFontExp->DrawText(LEADER_EXPENCE_EXP_FONT_X - size.cx,LEADER_EXPENCE_EXP_FONT_Y,GUI_FONT_COLOR,
				temp2,0L);
//			m_pImgExpenceOkB[m_nExpenceOkB]->Move(LEADER_EXPENCE_OK_BUTTON_X,LEADER_EXPENCE_OK_BUTTON_Y);
//			m_pImgExpenceOkB[m_nExpenceOkB]->Render();

			m_pExpenceOkBtn->Render();
			
		}
		break;
	case LEADER_STATE_POLL:
		{// ??.
			RenderPoll();

		}
		break;
	case LEADER_STATE_POLLDATE:
		{
			// ????.
			if(INFLUENCE_TYPE_VCN == m_BInfluence)
			{
				m_pImgPollDateVBG->Move(LEADER_BGR_X,LEADER_BGR_Y);
				m_pImgPollDateVBG->Render();
			}
			else
			{
				m_pImgPollDateABG->Move(LEADER_BGR_X,LEADER_BGR_Y);
				m_pImgPollDateABG->Render();
			}
			string strStart,strEnd;
			SIZE size;
			char cResult[512];
			ATUM_DATE_TIME tmpDate;
			tmpDate.GetLocalString_MMDD(m_AppStartDate.Month,m_AppStartDate.Day,strStart,GetLanguageType());
			tmpDate.GetLocalString_MMDD(m_AppEndDate.Month,m_AppEndDate.Day,strEnd,GetLanguageType());
			// ?ĺ? ??û ?Ⱓ.
			wsprintf(cResult,STRMSG_C_071030_0100,strStart.c_str(),m_AppStartDate.Hour,m_AppStartDate.Minute,
				strEnd.c_str(),m_AppEndDate.Hour,m_AppEndDate.Minute);					//"%s %02d:%02d ~ %s %02d:%02d"
			size = m_pFontExp->GetStringSize(cResult);
			m_pFontExp->DrawText(LEADER_POLL_APP_CENTER_FONT_X - (size.cx/2),LEADER_POLL_APP_CENTER_FONT_Y,GUI_FONT_COLOR,cResult);
			// ??ǥ ???? ?Ⱓ.
			tmpDate.GetLocalString_MMDD(m_VoteStartDate.Month,m_VoteStartDate.Day,strStart,GetLanguageType());
			tmpDate.GetLocalString_MMDD(m_VoteEndDate.Month,m_VoteEndDate.Day,strEnd,GetLanguageType());
			wsprintf(cResult,STRMSG_C_071030_0100,strStart.c_str(),m_VoteStartDate.Hour,m_VoteStartDate.Minute,
				strEnd.c_str(),m_VoteEndDate.Hour,m_VoteEndDate.Minute);					//"%s %02d:%02d ~ %s %02d:%02d")
			size = m_pFontExp->GetStringSize(cResult);
			m_pFontExp->DrawText(LEADER_POLL_JOIN_CENTER_FONT_X - (size.cx/2),LEADER_POLL_JOIN_CENTER_FONT_Y,GUI_FONT_COLOR,cResult);
			// ??????.
			tmpDate.GetLocalString_MMDD(m_Election.Month,m_Election.Day,strStart,GetLanguageType());
			wsprintf(cResult,STRMSG_C_071030_0101,strStart.c_str(),m_Election.Hour,m_Election.Minute);					//"%s %02d:%02d"
			size = m_pFontExp->GetStringSize(cResult);
			m_pFontExp->DrawText(LEADER_POLL_ELECT_CENTER_FONT_X - (size.cx/2),LEADER_POLL_ELECT_CENTER_FONT_Y,GUI_FONT_COLOR,cResult);     
			
		}
		break;
	case LEADER_STATE_WARINFO:
		{// ???? ????.
			RenderWarInfo();
		}
		break;
	}
}
void CINFCityLeader::RenderWarInfo()
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
			{// ??????????.
				m_pImgWarInfoInflBcu->Move(WARINFO_INFLUENCE_BG1_X,WARINFO_INFLUENCE_BG1_Y);
				m_pImgWarInfoInflBcu->Render();
				m_pImgWarInfoInflAni->Move(WARINFO_INFLUENCE_BG2_X,WARINFO_INFLUENCE_BG2_Y);
				m_pImgWarInfoInflAni->Render();
				// ?Ʊ? ????.
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
				// ???? ????.
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
			{// ?˸???.
				m_pImgWarInfoInflAni->Move(WARINFO_INFLUENCE_BG1_X,WARINFO_INFLUENCE_BG1_Y);
				m_pImgWarInfoInflAni->Render();
				m_pImgWarInfoInflBcu->Move(WARINFO_INFLUENCE_BG2_X,WARINFO_INFLUENCE_BG2_Y);
				m_pImgWarInfoInflBcu->Render();
				// ?Ʊ? ????.
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
				// ???? ????.
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
					GUI_FONT_COLOR,rbuf);
			}

		}
		break;

		
	// 2009. 01. 12 by ckPark ???? ???? ?ý???
	case LEADER_WARINFO_DECLAREWAR:
		{
			m_pImgWarInfoBG[LEADER_WARINFO_DECLAREWAR]->Move(LEADER_WARINFO_BG_X,LEADER_WARINFO_BG_Y);
			m_pImgWarInfoBG[LEADER_WARINFO_DECLAREWAR]->Render();
			
			// ???? ???? ????
			RenderWarInfoDeclareWar();
		}
		break;
	// end 2009. 01. 12 by ckPark ???? ???? ?ý???


	case LEADER_WARINFO_MOTHERSHIP:
		{
			m_pImgWarInfoBG[LEADER_WARINFO_MOTHERSHIP]->Move(LEADER_WARINFO_BG_X,LEADER_WARINFO_BG_Y);
			m_pImgWarInfoBG[LEADER_WARINFO_MOTHERSHIP]->Render();

			// 2008-03-19 by bhsohn ??????, ?????? ????â
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
				{//??????.
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

					// 2007-12-17 by dgwoo ???????̽? ????.
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
					// ???? ??ũ.
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
						// 2007-10-05 by bhsohn ??,??,?? ??Ʈ?? ?ý??? ?߰?
						// ???Ͻ?				
		//				wsprintf(temp1, STRMSG_C_070910_0205, m_OutPostNextWarTime.Month,
		//														m_OutPostNextWarTime.Day,
		//														m_OutPostNextWarTime.Hour);	
						string szStrBuf;
						it->OutpostDate.GetLocalString_MMDD(it->OutpostDate.Month, it->OutpostDate.Day, szStrBuf,GetLanguageType());						
						// 2007-10-08 by bhsohn ?????????? ?ð? ǥ?? ????
						//wsprintf(temp1, STRMSG_C_070910_0205, szStrBuf.c_str(), m_OutPostNextWarTime.Hour);	
						wsprintf(temp1, STRMSG_C_071030_0101, szStrBuf.c_str(), it->OutpostDate.Hour, it->OutpostDate.Minute);	
						sz = m_pFontExp->GetStringSize(temp1);
						m_pFontExp->DrawText(nPosX-(sz.cx/2),nPosY, GUI_FONT_COLOR,temp1,0L);
						// end 2007-10-05 by bhsohn ??,??,?? ??Ʈ?? ?ý??? ?߰?
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

			// 2008-03-19 by bhsohn ??????, ?????? ????â
			RenderWarInfoPointWar();
		}
		break;
	}
}
void CINFCityLeader::RenderPoll()
{
	char tempBuf[512];
	SIZE size;
	// ????.
	if(INFLUENCE_TYPE_VCN == m_BInfluence)
	{
		m_pImgVniBG->Move(LEADER_BGR_X,LEADER_BGR_Y);
		m_pImgVniBG->Render();
	}
	else
	{
		m_pImgAniBG->Move(LEADER_BGR_X,LEADER_BGR_Y);
		m_pImgAniBG->Render();
	}
	// ??ư.
	m_pImgPInfoB->Render();
	if(m_bCandidate)
	{
		m_pImgPUnAppB->Render();
	}
	else
	{
		m_pImgPAppB->Render();
	}
		
	// ????.
	switch(m_BPollState)
	{
	case LEADER_POLL_APP:
		{
			m_pImgAppBG->Move(LEADER_POLL_LIST_BG_X,LEADER_POLL_LIST_BG_Y);
			m_pImgAppBG->Render();

			m_pImgAppSucB->Render();
			m_pEditPledge->Tick();
			//m_pEditPledge->Render(0,6);
			m_pEditPledge->Render(m_pScrollPollPledge->GetScrollStep(), LEADER_POLL_PLEDGE_MAX_SCROLL_LINE);

			m_pScrollPollPledge->Render();
		}
		break;
	case LEADER_POLL_LIST:
		{
			m_pImgListBG->Move(LEADER_POLL_LIST_BG_X,LEADER_POLL_LIST_BG_Y);
			m_pImgListBG->Render();

			m_pImgRSelectB[0][m_nRSelectB_2]->Move(LEADER_POLL_SELECT_BUTTON_X,LEADER_POLL_SELECT_BUTTON_Y);
			m_pImgRSelectB[0][m_nRSelectB_2]->Render();

			if(m_vecCandidateList.size() > 0)
			{
				int i = 0;
				vector<MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK>::iterator it = m_vecCandidateList.begin();
				it += m_pScrollPollList->GetScrollStep();
				DWORD FontColor;
				while(it != m_vecCandidateList.end())
				{
					FontColor = GUI_FONT_COLOR;
					if((*it).DeleteCandidate)
					{
						FontColor = GUI_FONT_COLOR_G;
					} 
					memset(tempBuf,0x00,512);
					wsprintf(tempBuf,"%d",(*it).LeaderCandidateNum);
					m_pFontExp->DrawText(LEADER_POLL_LIST_NUMBER_X,LEADER_POLL_LIST_START_Y + (i * LEADER_POLL_LIST_SELECT_H)
						,FontColor,tempBuf,0L);
					
					memset(tempBuf,0x00,512);
					wsprintf(tempBuf,"%s",(*it).CharacterName);
					size = m_pFontExp->GetStringSize(tempBuf);
					m_pFontExp->DrawText(LEADER_POLL_LIST_CONDIDATE_NAME_X-(size.cx/2),LEADER_POLL_LIST_START_Y + (i * LEADER_POLL_LIST_SELECT_H)
						,FontColor,tempBuf,0L);

					memset(tempBuf,0x00,512);
					wsprintf(tempBuf,"%s",(*it).GuildName);
					size = m_pFontExp->GetStringSize(tempBuf);
					m_pFontExp->DrawText(LEADER_POLL_LIST_GUILD_NAME_X-(size.cx/2),LEADER_POLL_LIST_START_Y + (i * LEADER_POLL_LIST_SELECT_H),FontColor,tempBuf,0L);
					if(m_nSelectNum == i &&
						FontColor != GUI_FONT_COLOR_G)
					{
						m_pImgRSelect->Move(LEADER_POLL_LIST_AREA_X,LEADER_POLL_LIST_AREA_Y + (i * LEADER_POLL_LIST_SELECT_H));
						m_pImgRSelect->Render();
					}
					
					i++;
					it++;
					// 2008-05-26 by dgwoo ???? ?ĺ? ????Ʈâ???? ?ĺ? ????Ʈ?? ????? ???? ????.
					if(LEADER_POLL_LIST_MAX_SCROLL_LINE <= i)
					{
						break;
					}
				}
			}

			m_pScrollPollList->Render();
		}
		break;
	case LEADER_POLL_INFO:
		{
			// ???? ?? ??ư.
			m_pImgPInfoBG->Move(LEADER_POLL_LIST_BG_X,LEADER_POLL_LIST_BG_Y);
			m_pImgPInfoBG->Render();
			m_pImgRVoteB->Render();
			m_pImgRSelectB[1][m_nRSelectB_2]->Move(LEADER_POLL_SELECT_BUTTON_X,LEADER_POLL_SELECT_BUTTON_Y);
			m_pImgRSelectB[1][m_nRSelectB_2]->Render();

			// ????. 
			if(m_pImgFace)
			{
				m_pImgFace->Move(LEADER_POLL_FACE_IMG_X,LEADER_POLL_FACE_IMG_Y);
				m_pImgFace->Render();
			}
			// ???? ??ũ.
			if(m_pImgGuildMark)
			{
				m_pImgGuildMark->Move(LEADER_POLL_GUILDMARK_IMG_X,LEADER_POLL_GUILDMARK_IMG_Y);
				m_pImgGuildMark->Render();
			}
			// ????
			memset(tempBuf,0x00,512);
			wsprintf(tempBuf,"%d",m_sCandidateInfo.Level);
			m_pFontExp->DrawText(LEADER_POLL_INFO_LEVEL_FONT_X,LEADER_POLL_INFO_LEVEL_FONT_Y,GUI_FONT_COLOR,tempBuf);
			// ??????
			memset(tempBuf,0x00,512);
			wsprintf(tempBuf,"%s",m_sCandidateInfo.GuildName);
			m_pFontExp->DrawText(LEADER_POLL_GUILDNAME_FONT_X,LEADER_POLL_GUILDNAME_FONT_Y,GUI_FONT_COLOR,tempBuf);
			// ĳ???? ??
			memset(tempBuf,0x00,512);
			wsprintf(tempBuf,"%s",m_sCandidateInfo.CharacterName);
			size = m_pFontExp->GetStringSize(tempBuf);
			m_pFontExp->DrawText(LEADER_POLL_ID_FONT_X - (size.cx/2),LEADER_POLL_ID_FONT_Y,GUI_FONT_COLOR,tempBuf);
			// ???? ????.
			memset(tempBuf,0x00,512);
			wsprintf(tempBuf,"%d",m_sCandidateInfo.GuildFame);
			m_pFontExp->DrawText(LEADER_POLL_GUILDFAME_FONT_X,LEADER_POLL_GUILDFAME_FONT_Y,GUI_FONT_COLOR,tempBuf);
			// ????
//			m_pEditPledge->SetString(m_sCandidateInfo.CampaignPromises,SIZE_MAX_CAMPAIGNPROMISES);
			m_pEditPledgeView->Render(m_pScrollPollPledgeView->GetScrollStep(),LEADER_POLL_PLEDGE_VIEW_MAX_SCROLL_LINE);
			m_pScrollPollPledgeView->Render();
		}
		break;
	}
}
void CINFCityLeader::Tick()
{
}
void CINFCityLeader::WriteAppPLedge()
{
	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	//m_pEditPledge->InitString();		
	char chBlank[16];
	memset(chBlank, 0x00, 16);
	m_pEditPledge->SetString(chBlank, 16, 0, TRUE);		// ????

	m_pEditPledge->EnableEdit(TRUE, FALSE);

	m_pEditPledge->BackupTxtString();	
	
	m_pScrollPollPledge->SetMaxItem(0);
}
void CINFCityLeader::SendLeaderCandidateList()
{
// 2007-11-20 by dgwoo ?????? ???????쿣 ?? ????Ʈ?? ?׳ɺ????ش?.
	if(m_vecCandidateList.size() == 0)
	{
		g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST,NULL,NULL);
	}
	else
	{
		ChangePollState(LEADER_POLL_LIST);
	}
}

int CINFCityLeader::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			BOOL	bList = FALSE;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > LEADER_BRIGADE_NOTICE_BUTTON_X &&
				pt.x < LEADER_BRIGADE_NOTICE_BUTTON_X + LEADER_LEFT_BUTTON_W &&
				pt.y > LEADER_BRIGADE_NOTICE_BUTTON_Y &&
				pt.y < LEADER_BRIGADE_NOTICE_BUTTON_Y + LEADER_LEFT_BUTTON_H)
			{
				m_nBrigadeNoticeB = BUTTON_STATE_NORMAL;
				ChangeLeaderState(LEADER_STATE_NOTICE);
			}
			if( pt.x > LEADER_EXPENCE_BUTTON_X &&
				pt.x < LEADER_EXPENCE_BUTTON_X + LEADER_LEFT_BUTTON_W &&
				pt.y > LEADER_EXPENCE_BUTTON_Y &&
				pt.y < LEADER_EXPENCE_BUTTON_Y + LEADER_LEFT_BUTTON_H)
			{
				if(g_pD3dApp->IsMyShuttleLeader())
				{
					m_nExpenceB = BUTTON_STATE_NORMAL;
					ChangeLeaderState(LEADER_STATE_EXPENCE);
				}
				else
				{
					m_nExpenceB = BUTTON_STATE_DISABLE;
				}
			}
			if(m_pImgLPollAB->OnLButtonUp(pt)) 
			{
				//ChangeLeaderState(LEADER_STATE_POLL);
				bList = TRUE;
			}
			if(m_pImgLPollVB->OnLButtonUp(pt))
			{
				//ChangeLeaderState(LEADER_STATE_POLL);
				bList = TRUE;
			}
			if(bList)
			{
				// 2007-11-20 by dgwoo ???ý????? state?? ?????????? ?????? ó??.
				//ChangeLeaderState(LEADER_STATE_POLL);
				SendLeaderCandidateList();
			}
			
			if(m_pImgLDateB->OnLButtonUp(pt))
			{
				ChangeLeaderState(LEADER_STATE_POLLDATE);
			}
			if(m_pImgLWarInfoB->OnLButtonUp(pt))
			{
				ChangeLeaderState(LEADER_STATE_WARINFO);
			}

		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > LEADER_BRIGADE_NOTICE_BUTTON_X &&
				pt.x < LEADER_BRIGADE_NOTICE_BUTTON_X + LEADER_LEFT_BUTTON_W &&
				pt.y > LEADER_BRIGADE_NOTICE_BUTTON_Y &&
				pt.y < LEADER_BRIGADE_NOTICE_BUTTON_Y + LEADER_LEFT_BUTTON_H)
			{
				m_nBrigadeNoticeB = BUTTON_STATE_DOWN;
			}
			if(pt.x > LEADER_EXPENCE_BUTTON_X &&
				pt.x < LEADER_EXPENCE_BUTTON_X + LEADER_LEFT_BUTTON_W &&
				pt.y > LEADER_EXPENCE_BUTTON_Y &&
				pt.y < LEADER_EXPENCE_BUTTON_Y + LEADER_LEFT_BUTTON_H)
			{
				if(g_pD3dApp->IsMyShuttleLeader())
				{				
					m_nExpenceB = BUTTON_STATE_DOWN;
				}
				else
				{
					m_nExpenceB = BUTTON_STATE_DISABLE;
				}
			}
			m_pImgLPollAB->OnLButtonDown(pt);
			m_pImgLPollVB->OnLButtonDown(pt);
			m_pImgLDateB->OnLButtonDown(pt);
			m_pImgLWarInfoB->OnLButtonDown(pt);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > LEADER_BRIGADE_NOTICE_BUTTON_X &&
				pt.x < LEADER_BRIGADE_NOTICE_BUTTON_X + LEADER_LEFT_BUTTON_W &&
				pt.y > LEADER_BRIGADE_NOTICE_BUTTON_Y &&
				pt.y < LEADER_BRIGADE_NOTICE_BUTTON_Y + LEADER_LEFT_BUTTON_H)
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

			if(g_pD3dApp->IsMyShuttleLeader())
			{
				if(	pt.x > LEADER_EXPENCE_BUTTON_X &&
					pt.x < LEADER_EXPENCE_BUTTON_X + LEADER_LEFT_BUTTON_W &&
					pt.y > LEADER_EXPENCE_BUTTON_Y &&
					pt.y < LEADER_EXPENCE_BUTTON_Y + LEADER_LEFT_BUTTON_H)
				{
					if(m_nExpenceB != BUTTON_STATE_DOWN)
					{
						m_nExpenceB = BUTTON_STATE_UP;
					}
				}
				else
				{
					m_nExpenceB = BUTTON_STATE_NORMAL;
				}
			}
			m_pImgLPollAB->OnMouseMove(pt);
			m_pImgLPollVB->OnMouseMove(pt);
			m_pImgLDateB->OnMouseMove(pt);
			m_pImgLWarInfoB->OnMouseMove(pt);			
			

		}
		break;
	}
	switch(m_nRWindowState)
	{
	case LEADER_STATE_NOTICE:
		{
			if(INF_MSGPROC_BREAK == WndProcNotice(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case LEADER_STATE_EXPENCE:
		{
			if(INF_MSGPROC_BREAK == WndProcExpence(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case LEADER_STATE_POLL:
		{
			if(INF_MSGPROC_BREAK == WndProcPoll(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	case LEADER_STATE_WARINFO:
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
int CINFCityLeader::WndProcWarInfo(UINT uMsg,WPARAM wParam,LPARAM lParam)
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


	// 2009. 01. 12 by ckPark ???? ???? ?ý???

// 	// 2008-03-19 by bhsohn ??????, ?????? ????â
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
// 	// end 2008-03-19 by bhsohn ??????, ?????? ????â


	// ?? ?ǿ? ???Ͽ? ?޼??? ???ν????? ?и?
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
	// end 2009. 01. 12 by ckPark ???? ???? ?ý???



	return INF_MSGPROC_NORMAL;
}
int CINFCityLeader::WndProcPoll(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(m_bCandidate)
			{
				if(m_pImgPUnAppB->OnLButtonUp(pt))
				{// ?ĺ? Ż??.
					ButtonClickDeleteCandidate();
				}
			}
			else
			{
				if(m_pImgPAppB->OnLButtonUp(pt))
				{// ?ĺ? ????.
					ChangePollState(LEADER_POLL_APP);				
				}
			}

			if(m_pImgPInfoB->OnLButtonUp(pt))
			{// ?ĺ? ?????? ????.
				ButtonClickPollInfo();			
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			m_pImgPAppB->OnLButtonDown(pt);
			m_pImgPUnAppB->OnLButtonDown(pt);
			m_pImgPInfoB->OnLButtonDown(pt);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			m_pImgPAppB->OnMouseMove(pt);
			m_pImgPUnAppB->OnMouseMove(pt);
			m_pImgPInfoB->OnMouseMove(pt);

		}
		break;
	}
	switch(m_BPollState)
	{
	case LEADER_POLL_APP:
		{
			if(INF_MSGPROC_BREAK == WndProcPollApp(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case LEADER_POLL_LIST:
		{
			if(INF_MSGPROC_BREAK == WndProcPollList(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case LEADER_POLL_INFO:
		{
			if(INF_MSGPROC_BREAK == WndProcPollInfo(uMsg,wParam,lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;

	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityLeader::WndProcPollInfo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(m_pImgRVoteB->OnLButtonUp(pt))
			{// ??ǥ.
				ButtonClickVote();
				//m_pInfWindow->AddMsgBox(STRMSG_C_070928_0201, _Q_SECOND_PASS_CANCEL_MSG);
			}
			if(pt.x > LEADER_POLL_LIST_BUTTON_X &&
				pt.x < LEADER_POLL_LIST_BUTTON_X + LEADER_POLL_LIST_BUTTON_W &&
				pt.y > LEADER_POLL_LIST_BUTTON_Y &&
				pt.y < LEADER_POLL_LIST_BUTTON_Y + LEADER_POLL_LIST_BUTTON_H)
			{
				//ChangePollState(LEADER_POLL_LIST);
				SendLeaderCandidateList();
			}
			BOOL bClick = m_pScrollPollPledgeView->GetMouseMoveMode();
			if(bClick)
			{
				m_pScrollPollPledgeView->SetMouseMoveMode(FALSE);
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
			m_pImgRVoteB->OnLButtonDown(pt);
			BOOL bClick = m_pScrollPollPledgeView->IsMouseBallPos(pt);
			if(bClick)
			{
				m_pScrollPollPledgeView->SetMouseMoveMode(TRUE);
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
			m_pImgRVoteB->OnMouseMove(pt);
			if(pt.x > LEADER_POLL_LIST_BUTTON_X &&
				pt.x < LEADER_POLL_LIST_BUTTON_X + LEADER_POLL_LIST_BUTTON_W &&
				pt.y > LEADER_POLL_LIST_BUTTON_Y &&
				pt.y < LEADER_POLL_LIST_BUTTON_Y + LEADER_POLL_LIST_BUTTON_H)
			{
				m_nRSelectB_2 = BUTTON_BOTH_STATE_UP;
			}
			else
			{
				m_nRSelectB_2 = BUTTON_BOTH_STATE_NORMAL;
			}

			if(m_pScrollPollPledgeView->GetMouseMoveMode())
			{
				if(FALSE == m_pScrollPollPledgeView->IsMouseScrollPos(pt))
				{
					m_pScrollPollPledgeView->SetMouseMoveMode(FALSE);
				}
				else
				{
					m_pScrollPollPledgeView->SetScrollPos(pt);
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
			BOOL bClick = m_pScrollPollPledgeView->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pScrollPollPledgeView->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;

	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityLeader::WndProcPollList(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > LEADER_POLL_LIST_BUTTON_X &&
				pt.x < LEADER_POLL_LIST_BUTTON_X + LEADER_POLL_LIST_BUTTON_W &&
				pt.y > LEADER_POLL_LIST_BUTTON_Y &&
				pt.y < LEADER_POLL_LIST_BUTTON_Y + LEADER_POLL_LIST_BUTTON_H)
			{
				SendCandidateInfo();
			}
			if(pt.x > LEADER_POLL_LIST_AREA_X &&
				pt.x < LEADER_POLL_LIST_AREA_X + LEADER_POLL_LIST_AREA_W &&
				pt.y > LEADER_POLL_LIST_AREA_Y &&
				pt.y < LEADER_POLL_LIST_AREA_Y + LEADER_POLL_LIST_AREA_H)
			{
				int nSelect = (pt.y - LEADER_POLL_LIST_AREA_Y)/LEADER_POLL_LIST_SELECT_H;
				if(nSelect >= 0 &&
					nSelect < LEADER_POLL_LIST_MAX_SCROLL_LINE)
				{
					m_nSelectNum = nSelect;
				}
			}
			BOOL bClick = m_pScrollPollList->GetMouseMoveMode();
			if(bClick)
			{
				m_pScrollPollList->SetMouseMoveMode(FALSE);
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
			BOOL bClick = m_pScrollPollList->IsMouseBallPos(pt);
			if(bClick)
			{
				m_pScrollPollList->SetMouseMoveMode(TRUE);
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
			if(pt.x > LEADER_POLL_LIST_BUTTON_X &&
				pt.x < LEADER_POLL_LIST_BUTTON_X + LEADER_POLL_LIST_BUTTON_W &&
				pt.y > LEADER_POLL_LIST_BUTTON_Y &&
				pt.y < LEADER_POLL_LIST_BUTTON_Y + LEADER_POLL_LIST_BUTTON_H)
			{
				m_nRSelectB_2 = BUTTON_BOTH_STATE_UP;
			}
			else
			{
				m_nRSelectB_2 = BUTTON_BOTH_STATE_NORMAL;
			}
			if(m_pScrollPollList->GetMouseMoveMode())
			{
				if(FALSE == m_pScrollPollList->IsMouseScrollPos(pt))
				{
					m_pScrollPollList->SetMouseMoveMode(FALSE);
				}
				else
				{
					m_pScrollPollList->SetScrollPos(pt);
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
			BOOL bClick = m_pScrollPollList->IsMouseWhellPos(pt);
			if(bClick)		
			{			
				m_pScrollPollList->OnMouseWheel(wParam, lParam);	
				return INF_MSGPROC_BREAK;
			}
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			// ?? ????.
			if(pt.x > LEADER_POLL_LIST_AREA_X &&
				pt.x < LEADER_POLL_LIST_AREA_X + LEADER_POLL_LIST_AREA_W &&
				pt.y > LEADER_POLL_LIST_AREA_Y &&
				pt.y < LEADER_POLL_LIST_AREA_Y + LEADER_POLL_LIST_AREA_H)
			{
				int nSelect = (pt.y - LEADER_POLL_LIST_AREA_Y)/LEADER_POLL_LIST_SELECT_H;
				if(nSelect >= 0 &&
					nSelect < LEADER_POLL_LIST_MAX_SCROLL_LINE)
				{
					m_nSelectNum = nSelect;
					SendCandidateInfo();
				}
			}
		}
		break;

	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityLeader::WndProcPollApp(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(m_pImgAppSucB->OnLButtonUp(pt))
			{// ??û ?Ϸ?.
				//g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_REG_LEADER_CANDIDATE,NULL,NULL);
				ButtonClickPollAppSuc();

			}
			if(pt.x > LEADER_POLL_PLEDGE_EDIT_X &&
				pt.x < LEADER_POLL_PLEDGE_EDIT_X + LEADER_POLL_PLEDGE_EDIT_W &&
				pt.y > LEADER_POLL_PLEDGE_EDIT_Y &&
				pt.y < LEADER_POLL_PLEDGE_EDIT_Y + LEADER_POLL_PLEDGE_EDIT_H)
			{
				WriteAppPLedge();
			}
			BOOL bClick = m_pScrollPollPledge->GetMouseMoveMode();
			if(bClick)
			{
				m_pScrollPollPledge->SetMouseMoveMode(FALSE);
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
			m_pImgAppSucB->OnLButtonDown(pt);
			BOOL bClick = m_pScrollPollPledge->IsMouseBallPos(pt);
			if(bClick)
			{
				m_pScrollPollPledge->SetMouseMoveMode(TRUE);
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
			m_pImgAppSucB->OnMouseMove(pt);
			if(m_pScrollPollPledge->GetMouseMoveMode())
			{
				if(FALSE == m_pScrollPollPledge->IsMouseScrollPos(pt))
				{
					m_pScrollPollPledge->SetMouseMoveMode(FALSE);
				}
				else
				{
					m_pScrollPollPledge->SetScrollPos(pt);
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
			BOOL bClick = m_pScrollPollPledge->IsMouseWhellPos(pt);
			if(bClick)
			{			
				m_pScrollPollPledge->OnMouseWheel(wParam, lParam);	
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
	case WM_KEYDOWN:
	// 2010. 04. 12 by ckPark ???????? ???? ????Ʈ ?ڽ? ???? ????
	case WM_KEYUP:
	// end 2010. 04. 12 by ckPark ???????? ???? ????Ʈ ?ڽ? ???? ????
		{
			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
			if(m_pEditPledge->IsEditMode())
			{				
				int nLienCnt = -1;
				int nArrowScroll = 0;
				BOOL bRtn = FALSE;
				BOOL bStrCat =FALSE;
				bRtn = m_pEditPledge->WndProc(uMsg, wParam, lParam, m_pScrollPollPledge->GetScrollStep(), 
					&nLienCnt, &nArrowScroll, &bStrCat);
				
				if(nLienCnt < 0)
				{
					// ?ƹ? ó???? ???ߴ?.
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
						case VK_LEFT:	// ???????? ?̵?
						case VK_UP:
						case VK_RIGHT:
						case VK_DOWN:
							{
								// ????Ű?? ?????? ??ũ?? ??ġ ???? 
								if(nLienCnt > LEADER_POLL_PLEDGE_MAX_SCROLL_LINE 
									&& nArrowScroll !=0)
								{
									nMaxStep = m_pScrollPollPledge->GetMaxStepCnt();
									nScrollStep = m_pScrollPollPledge->GetScrollStep() + nArrowScroll;
									nScrollStep = max(0, nScrollStep);						
									nScrollStep = min(nMaxStep, nScrollStep);						
									m_pScrollPollPledge->SetScrollStep(nScrollStep);
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
				
				nMaxStep = max(nLienCnt, LEADER_POLL_PLEDGE_MAX_SCROLL_LINE);
				nScrollStep = nMaxStep - LEADER_POLL_PLEDGE_MAX_SCROLL_LINE;
				if(nScrollStep < 0)
				{
					nScrollStep = 0;
				}						
				if(m_pEditPledge->IsLastPos())
				{
					// ???? ?????? ?????̳??					
					
					// ?ִ? ???????? ?????ְ?
					m_pScrollPollPledge->SetMaxItem(nMaxStep);					
					// ??Ʈ???? ?ڿ? ???̴? ?????? ?ƴϴ?.
					// ??ũ?? ??ġ?? ???? ?Ʒ?
					m_pScrollPollPledge->SetScrollStep(nScrollStep);								
				}					
				else
				{
					m_pScrollPollPledge->SetOnlyMaxItem(nMaxStep);
					m_pEditPledge->RefreshEndCurselPos();	// ????????ġ ????
				}
				
				if(bRtn)
				{
					return INF_MSGPROC_BREAK;
				}					
				
			}
		}
		break;
//		{
//			int nLienCnt = 0;
//			BOOL bRtn = FALSE;
//			bRtn = m_pEditPledge->WndProc(uMsg, wParam, lParam, &nLienCnt);			
//			
//			int nMaxStep = max(nLienCnt, LEADER_POLL_PLEDGE_MAX_SCROLL_LINE);			
//			
//			// ?ִ? ???????? ?????ְ?
//			m_pScrollPollPledge->SetMaxItem(nMaxStep);
//			
//			int nScrollStep = nMaxStep - LEADER_POLL_PLEDGE_MAX_SCROLL_LINE;
//			if(nScrollStep < 0)
//			{
//				nScrollStep = 0;
//			}
//
//			// ??ũ?? ??ġ?? ???? ?Ʒ?
//			m_pScrollPollPledge->SetScrollStep(nScrollStep);		
//			if(bRtn)
//			{
//				return INF_MSGPROC_BREAK;
//			}
//
//		}
//		break;
	}
	return INF_MSGPROC_NORMAL;
}

int CINFCityLeader::WndProcNotice(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// 2007-09-05 by bhsohn ???? ??????
//			if(pt.x > LEADER_WRITE_BUTTON_X &&
//				pt.x < LEADER_WRITE_BUTTON_X + LEADER_RIGHT_BUTTON_W &&
//				pt.y > LEADER_WRITE_BUTTON_Y &&
//				pt.y < LEADER_WRITE_BUTTON_Y + LEADER_RIGHT_BUTTON_H)
//			{
//				m_nWriteB = BUTTON_STATE_NORMAL;
//			}
			{
				if(TRUE == m_pNoticeWrite->OnLButtonUp(pt))
				{	
					// ??ư Ŭ?? 
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					// ??ư Ŭ??
					ButtonClickWrite();					
					return  INF_MSGPROC_BREAK;
				}
			}
			
			{
				if(TRUE == m_pRegist->OnLButtonUp(pt))
				{	
					// ??ư Ŭ?? 
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);			
					// ??ư Ŭ??
					ButtonClickApp();					
					return  INF_MSGPROC_BREAK;
				}
			}

			if(pt.x > LEADER_APP_BUTTON_X &&
				pt.x < LEADER_APP_BUTTON_X + LEADER_RIGHT_BUTTON_W &&
				pt.y > LEADER_APP_BUTTON_Y &&
				pt.y < LEADER_APP_BUTTON_Y + LEADER_RIGHT_BUTTON_H)
			{
				m_nAppB = BUTTON_STATE_NORMAL;
			}
			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
			{
				BOOL bClick = m_pINFScrollBar->GetMouseMoveMode();
				if(bClick)		
				{
					m_pINFScrollBar->SetMouseMoveMode(FALSE);	
					return INF_MSGPROC_BREAK;
				}
			}
			// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????

		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			// ???? ??ư
			{
				if(TRUE == m_pNoticeWrite->OnLButtonDown(pt))
				{
					// ??ư???? ???콺?? ?ִ?.
					return  INF_MSGPROC_BREAK;
				}		
			}
			
			{
				if(TRUE == m_pRegist->OnLButtonDown(pt))
				{
					// ??ư???? ???콺?? ?ִ?.
					return  INF_MSGPROC_BREAK;
				}		
			}
			

			if(pt.x > LEADER_APP_BUTTON_X &&
				pt.x < LEADER_APP_BUTTON_X + LEADER_RIGHT_BUTTON_W &&
				pt.y > LEADER_APP_BUTTON_Y &&
				pt.y < LEADER_APP_BUTTON_Y + LEADER_RIGHT_BUTTON_H)
			{
				m_nAppB = BUTTON_STATE_DOWN;
			}
			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
			{
				BOOL bClick = m_pINFScrollBar->IsMouseBallPos(pt);
				if(bClick)		
				{
					m_pINFScrollBar->SetMouseMoveMode(TRUE);
					return INF_MSGPROC_BREAK;
				}		
			}
			// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????

		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// 2007-09-05 by bhsohn ???? ??????
			m_pNoticeWrite->OnMouseMove(pt);
			m_pRegist->OnMouseMove(pt);

			if(pt.x > LEADER_APP_BUTTON_X &&
				pt.x < LEADER_APP_BUTTON_X + LEADER_RIGHT_BUTTON_W &&
				pt.y > LEADER_APP_BUTTON_Y &&
				pt.y < LEADER_APP_BUTTON_Y + LEADER_RIGHT_BUTTON_H)
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

			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
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
			// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
		}
		break;
	case WM_IME_STARTCOMPOSITION:
//	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_SETCONTEXT:	
	case WM_CHAR:
	case WM_KEYDOWN:	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	// 2010. 04. 12 by ckPark ???????? ???? ????Ʈ ?ڽ? ???? ????
	case WM_KEYUP:
	// end 2010. 04. 12 by ckPark ???????? ???? ????Ʈ ?ڽ? ???? ????
		{
			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
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
					// ?ƹ? ó???? ???ߴ?.
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
						case VK_LEFT:	// ???????? ?̵?
						case VK_UP:
						case VK_RIGHT:
						case VK_DOWN:
							{
								// ????Ű?? ?????? ??ũ?? ??ġ ???? 
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
					// ???? ?????? ?????̳??					
					
					// ?ִ? ???????? ?????ְ?
					m_pINFScrollBar->SetMaxItem(nMaxStep);					
					// ??Ʈ???? ?ڿ? ???̴? ?????? ?ƴϴ?.
					// ??ũ?? ??ġ?? ???? ?Ʒ?
					m_pINFScrollBar->SetScrollStep(nScrollStep);								
				}					
				else
				{
					m_pINFScrollBar->SetOnlyMaxItem(nMaxStep);
					m_pNoticeEditBox->RefreshEndCurselPos();	// ????????ġ ????
				}
				
				if(bRtn)
				{
					return INF_MSGPROC_BREAK;
				}					
				
			}		
			
			
			// end 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
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
			// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
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
int CINFCityLeader::WndProcExpence(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(pt.x > LEADER_EXPENCE_OK_BUTTON_X &&
				pt.x < LEADER_EXPENCE_OK_BUTTON_X + LEADER_RIGHT_BUTTON_W &&
				pt.y > LEADER_EXPENCE_OK_BUTTON_Y &&
				pt.y < LEADER_EXPENCE_OK_BUTTON_Y + LEADER_RIGHT_BUTTON_H)
			{
				m_nExpenceOkB = BUTTON_STATE_NORMAL;
			}

			// 2007-09-05 by bhsohn ???? ??????
			{
				if(TRUE == m_pExpenceOkBtn->OnLButtonUp(pt))
				{					
					// ??ư Ŭ?? 
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
			if(pt.x > LEADER_EXPENCE_OK_BUTTON_X &&
				pt.x < LEADER_EXPENCE_OK_BUTTON_X + LEADER_RIGHT_BUTTON_W &&
				pt.y > LEADER_EXPENCE_OK_BUTTON_Y &&
				pt.y < LEADER_EXPENCE_OK_BUTTON_Y + LEADER_RIGHT_BUTTON_H)
			{
				m_nExpenceOkB = BUTTON_STATE_DOWN;
			}

			// 2007-09-05 by bhsohn ???? ??????
			{
				if(TRUE == m_pExpenceOkBtn->OnLButtonDown(pt))
				{
					// ??ư???? ???콺?? ?ִ?.
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
			if(pt.x > LEADER_EXPENCE_OK_BUTTON_X &&
				pt.x < LEADER_EXPENCE_OK_BUTTON_X + LEADER_RIGHT_BUTTON_W &&
				pt.y > LEADER_EXPENCE_OK_BUTTON_Y &&
				pt.y < LEADER_EXPENCE_OK_BUTTON_Y + LEADER_RIGHT_BUTTON_H)
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

			// 2007-09-05 by bhsohn ???? ??????
			m_pExpenceOkBtn->OnMouseMove(pt);

		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFCityLeader::OnClickExpenceOk()
{
	char buf[256];
	ZERO_MEMORY(buf);
	wsprintf(buf, STRMSG_C_070910_0201);//"ȯ?޹??? ?ݾ??? ?Է??ϼ???."
	((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox(buf,_Q_INFLUENCE_WAR_EXPENCE_OK_MSG, 0, m_nExp);
}


// ?ǰ??? ???? ???? ??????Ʈ
void CINFCityLeader::SetExpenceInfo(float fExplate,DWORD nCumulativeExp, DWORD nExp)
{
	m_fExplate = fExplate/(10.0f);
	m_nCumulativeExp = nCumulativeExp;
	m_nExp = nExp;

}
// ???? ?ð? ???? ???? ó??
void CINFCityLeader::SetNextWarInfo(ATUM_DATE_TIME OutPostNextWarTime, INT nOutPostNextWarSelectTimeChoice, vector<ATUM_DATE_TIME> vectmpTimeList)
{
// 2008-10-13 by dgwoo ???????? ?ð??????ϴ? ?κ? ??????	
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
// ???? ????????
VOID CINFCityLeader::ReFresh()
{
	ChangeLeaderState(LEADER_STATE_NOTICE);
	ClearCandidateList();
	memset(&m_sCandidateInfo,0x00,sizeof(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK));
}
// ?ݱ? ??ư Ŭ??
void CINFCityLeader::OnCloseInfWnd()
{
	m_pNoticeEditBox->InitString();		
	m_pNoticeEditBox->EnableEdit(FALSE, FALSE);

	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	m_pINFScrollBar->SetMaxItem(0);
}
void CINFCityLeader::ChangePollState(BYTE i_BPollState)
{
	ChangeLeaderState(LEADER_STATE_POLL);
	switch(i_BPollState)
	{
	case LEADER_POLL_LIST:
		{
			// ?ĺ? ????Ʈ?? ?ѹ??? ??û?Ѵ?.
			m_pImgPInfoB->EnableBtn(TRUE);
//			if(m_vecCandidateList.size() == 0)
//				g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST,NULL,NULL);
		}
		break;
	case LEADER_POLL_APP:
		{
			m_pImgPInfoB->EnableBtn(FALSE);
		}
		break;
	case LEADER_POLL_INFO:
		{
			m_pImgPInfoB->EnableBtn(FALSE);
		}
		break;
	}
	m_BPollState = i_BPollState;
}
void CINFCityLeader::ChangeWarInfoState(BYTE i_BWarInfoState)
{
	switch(i_BWarInfoState)
	{
	case LEADER_WARINFO_INFLUENCE:
		{
			g_pFieldWinSocket->SendMsg(T_FC_CITY_WARINFO_INFLUENCE,NULL,NULL);
		}
		break;

		
	// 2009. 01. 12 by ckPark ???? ???? ?ý???
	case LEADER_WARINFO_DECLAREWAR:
		{
			// ?Ϲ? ?????? ???? ?ƹ??͵? ????
			if( COMPARE_INFLUENCE( g_pShuttleChild->m_myShuttleInfo.InfluenceType, INFLUENCE_TYPE_NORMAL ) )
				break;
			
			int		nOurMothershipNum;
			int		nEnemyMothershipNum;
			
			// ?? ???¿? ???? ?ڽŰ? ???? ???? ??ȣ ????
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
			
			// ???? ?ؽ?Ʈ ????
			MEX_MONSTER_INFO* pMonsterInfo = g_pDatabase->CheckMonsterInfo(nOurMothershipNum);
			sprintf(m_szOurThisTakeOff, STRMSG_C_090113_0301, pMonsterInfo->MonsterName);
			sprintf(m_szOurNextTakeOff, STRMSG_C_090113_0302, pMonsterInfo->MonsterName);
			pMonsterInfo = g_pDatabase->CheckMonsterInfo(nEnemyMothershipNum);
			sprintf(m_szEnemyThisTakeOff, STRMSG_C_090113_0301, pMonsterInfo->MonsterName);
			sprintf(m_szEnemyNextTakeOff, STRMSG_C_090113_0302,	pMonsterInfo->MonsterName);
			
			
			// ?ð? ?ؽ?Ʈ ????
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
				// ?ϳ??? ??Ī ?Ǿ ???? Ǯ????. 
				g_pD3dApp->EnterMultiLock(TRUE, T_FC_INFO_DECLARATION_MSWAR_INFO, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
			}
			
			g_pFieldWinSocket->SendMsg(T_FC_INFO_DECLARATION_MSWAR_INFO, 0, 0);
		}
		break;
	// end 2009. 01. 12 by ckPark ???? ???? ?ý???



	case LEADER_WARINFO_MOTHERSHIP:
		{
			// 2008-03-19 by bhsohn ??????, ?????? ????â
			if(m_bStateWarInfo != i_BWarInfoState)
			{
				//TestMotherDB();
				InitWarInfoMothership();				
				RqMotherShipDB();
			}
//			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051114_0001, COLOR_ERROR );
//			return;
		}
		break;
	case LEADER_WARINFO_OUTPOST:
		{
			g_pFieldWinSocket->SendMsg(T_FC_CITY_WARINFO_OUTPOST,NULL,NULL);
		}
		break;
	case LEADER_WARINFO_POINT:
		{
			// 2008-03-19 by bhsohn ??????, ?????? ????â
//			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_051114_0001, COLOR_ERROR );
			if(m_bStateWarInfo != i_BWarInfoState)
			{
				//TestPointWarDB();
				InitWarInfoPointWar();				
				RqPointWarDB();
			}
//			return;
		}
		break;
	}
	m_bStateWarInfo = i_BWarInfoState;
}
void CINFCityLeader::SendCandidateInfo()
{
	int nStep = m_pScrollPollList->GetScrollStep();
	nStep += m_nSelectNum;
	if(nStep < 0 ||
		m_vecCandidateList.size() <= nStep)
	{
		return;
	}
	if(m_vecCandidateList[nStep].DeleteCandidate)
	{// ?ѹ? Ż???? ?????? ?????? ????????.
		return;
	}
	m_nCandidateNum = m_vecCandidateList[nStep].LeaderCandidateNum;
	MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO sMsg;
	sMsg.LeaderCandidateNum = m_nCandidateNum;
	g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO,(char*)&sMsg,sizeof(sMsg));
}
void CINFCityLeader::ButtonClickVote()
{// ??ǥ ??ư Ŭ??.
//	MSG_FC_CITY_POLL_VOTE sMsg;
//	sMsg.LeaderCandidateNum		= m_nCandidateNum;
//	sMsg.CharacterUID			= m_sCandidateInfo.CharacterUID;
//	sMsg.VoteCharacterUID		= g_pShuttleChild->GetMyShuttleInfo().CharacterUniqueNumber;
//	g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_VOTE,(char*)&sMsg,sizeof(sMsg));
	char buf[128];
	wsprintf(buf,STRMSG_C_071029_0108,m_sCandidateInfo.CharacterName);
	((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox(buf,_Q_POLL_CANDIDATE_VOTE);
}
void CINFCityLeader::AddCandidateList(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_LIST_OK * pMsg)
{
	m_vecCandidateList.push_back(*pMsg);
}
void CINFCityLeader::AddCandidateListDone()
{
	ChangePollState(LEADER_POLL_LIST);
	m_pScrollPollList->SetMaxItem(m_vecCandidateList.size());
}
void CINFCityLeader::ClearCandidateList()
{
	m_vecCandidateList.clear();
}
void CINFCityLeader::SetCandidate(BOOL i_bCandidate)
{
	m_bCandidate = i_bCandidate;
	if(m_bCandidate)
	{
		m_pImgPAppB->EnableBtn(FALSE);
		m_pImgPUnAppB->EnableBtn(TRUE);
	}
	else
	{
		m_pImgPAppB->EnableBtn(TRUE);
		m_pImgPUnAppB->EnableBtn(FALSE);
	}
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityLeader::SetCandidateInfo(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK * pMsg)
/// \brief		?ĺ? ???? ????.
/// \author		dgwoo
/// \date		2007-10-30 ~ 2007-10-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::SetCandidateInfo(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK * pMsg)
{
	m_pImgGuildMark			= NULL;
	m_pImgFace				= NULL;
	ChangePollState(LEADER_POLL_INFO);
	memcpy(&m_sCandidateInfo,pMsg,sizeof(MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO_OK));
	m_pImgFace = m_pPilotFace->FindPilotImage(m_sCandidateInfo.PilotFace);
	// 2008-10-29 by bhsohn ????Ʈ ?ڽ? ???? ????
	//int nMaxLineNum = m_pEditPledgeView->SetString(pMsg->CampaignPromises,SIZE_MAX_CAMPAIGNPROMISES);
	int nMaxLineNum = m_pEditPledgeView->SetString(pMsg->CampaignPromises,SIZE_MAX_CAMPAIGNPROMISES, TRUE);
	m_pScrollPollPledgeView->SetMaxItem(nMaxLineNum);
	
}
void CINFCityLeader::SetCandidateInfoGuildMark(UID32_t i_nGuildUID)
{
	m_pImgGuildMark = g_pDatabase->GetGuildMark(i_nGuildUID);
}
void CINFCityLeader::SetPollDate(MSG_FC_CITY_POLL_REQUEST_POLL_DATE_OK * pMsg)
{
	m_AppEndDate				= pMsg->ApplicationEndDate;
	m_AppStartDate				= pMsg->ApplicationStartDate;
	m_VoteStartDate				= pMsg->VoteStartDate;
	m_VoteEndDate				= pMsg->VoteEndDate;
	m_Election					= pMsg->Election;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityLeader::PollRegLeaderCandidateOk()
/// \brief		?ĺ? ?????? ?Ϸ? ?Ǿ???????.
/// \author		dgwoo
/// \date		2007-10-31 ~ 2007-10-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::PollRegLeaderCandidateOk(INT i_nCandidateNum)
{
	ClearCandidateList();
	//ChangePollState() ?Լ? ?????? ???? ??û?? ?ٽ? ???? ?ʵ??? -1 ????.
	m_nSelectNum = -1;
	m_pScrollPollList->SetScrollStep(0);
	// 2007-11-08 by dgwoo ?ĺ??? ?????? ?Ϸ? ?Ǿ??????? Ż?𰡴??ϰ? ??ư ????.
	SetCandidate(TRUE);
	MSG_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO sMsg;
	sMsg.LeaderCandidateNum = i_nCandidateNum;
	m_nCandidateNum = i_nCandidateNum;
	g_pFieldWinSocket->SendMsg(T_FC_CITY_POLL_REQUEST_LEADER_CANDIDATE_INFO,(char*)&sMsg,sizeof(sMsg));
}
void CINFCityLeader::DeleteCandidateOk()
{
	ClearCandidateList();
	return;
}
void CINFCityLeader::ButtonClickDeleteCandidate()
{
	char buf[512];
	wsprintf(buf,STRMSG_C_071029_0101);
	((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox(buf,_Q_POLL_CANDIDATE_DELETE);
}
void CINFCityLeader::AddOutPostInfo(SCITY_WARINFO_OUTPOST * i_pOutPostInfo)
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
void CINFCityLeader::ClearOutPostInfo()
{
	m_vecOutPostInfo.clear();
}
void CINFCityLeader::SetWarInfoInfluence(MSG_FC_CITY_WARINFO_INFLUENCE_OK *pMsg)
{
	memcpy(&m_sInfluenceInfo,pMsg,sizeof(MSG_FC_CITY_WARINFO_INFLUENCE_OK));
}
BOOL CINFCityLeader::SetGuildMark(UID32_t i_nGuildUID)
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
/// \brief		// ?????? ???? ?ʱ?ȭ
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::InitWarInfoMothership()
{
	m_vecMotherShipInfo.clear();
	m_pScrollMotherShipInfo->SetMaxItem(m_vecMotherShipInfo.size());

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::AddWarInfoMothership(BYTE byAttackBelligerence,	// ???ݼ???
											BYTE byWinBelligerence,		// ?¸?????
											char* pMonName,				// ?????̸?
											int nWarpoint,				// ????????Ʈ
											ATUM_DATE_TIME	timeStartWarTime,	// ???۽ð?
											ATUM_DATE_TIME	timeEndWarTime)		//?????ð?	
{
	structMotherShipInfo sMsg;
	memset(&sMsg, 0x00, sizeof(structMotherShipInfo));

	// ???? ????
	if(IS_VCN_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0101);
	}	

	// ?¸? ????
	if(IS_VCN_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0101);
	}	
	else if(0 == byWinBelligerence)	// (0:??????)
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070607_0102);		
	}
	
	// ???? ?̸?
	if(pMonName)
	{
		strncpy(sMsg.chMotherShipName, pMonName, SIZE_MAX_MONSTER_NAME);
	}

	// ????????Ʈ
	char chWarPoint[64];								// ????????Ʈ
	wsprintf(chWarPoint, "%d", nWarpoint);
	MakeCurrencySeparator( sMsg.chWarPoint, chWarPoint, 3, ',' );

	// ?????? ???? ?ð?	
	string szStartStrBuf;
	timeStartWarTime.GetLocalString_MMDD(timeStartWarTime.Month, 
										timeStartWarTime.Day, 
										szStartStrBuf,
										GetLanguageType());	

	// 2008-04-22 by bhsohn ????/?????? ???????? ?????? ǥ?? ?ϰ? ????
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

	// 2008-08-19 by bhsohn ??????, ?????? ???? ??ȯ ?ð????? ????
	sMsg.SummonTime = timeStartWarTime;

	m_vecMotherShipInfo.push_back(sMsg);	
		
	// 2008-08-19 by bhsohn ??????, ?????? ???? ??ȯ ?ð????? ????
	sort(m_vecMotherShipInfo.begin(), m_vecMotherShipInfo.end(), sort_MotherShip_summontime());	

	m_pScrollMotherShipInfo->SetMaxItem(m_vecMotherShipInfo.size());
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::RenderWarInfoMothership()
{
	// ??ũ?? ????
	m_pScrollMotherShipInfo->Render();

	// 2009. 01. 12 by ckPark ???? ???? ?ý???
	//m_pBtnMotherShipInfo->Render();	// ???????????? ?̵?
	// end 2009. 01. 12 by ckPark ???? ???? ?ý???

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

		// ???ݼ???
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chAttackInfluence);
			nX = MOTHERSHIP_WARINFO_VIEW_ATT_INFL_X - (sizeFont.cx/2);
			nY = MOTHERSHIP_WARINFO_VIEW_ATT_INFL_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chAttackInfluence, 0L);
		}

		// ?𼱸? 
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chMotherShipName);
			nX = MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_X - (sizeFont.cx/2);;
			nY = MOTHERSHIP_WARINFO_VIEW_ATT_MOTHER_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chMotherShipName, 0L);
		}

		// ????????Ʈ
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chWarPoint);
			nX = MOTHERSHIP_WARINFO_VIEW_POINT_X - (sizeFont.cx/2);;
			nY = MOTHERSHIP_WARINFO_VIEW_POINT_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chWarPoint, 0L);
		}

		// ?ð?
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chTimeCap);
			nX = MOTHERSHIP_WARINFO_VIEW_TIME_X - (sizeFont.cx/2);;
			nY = MOTHERSHIP_WARINFO_VIEW_TIME_Y + (nLine*MOTHERSHIP_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chTimeCap, 0L);
		}

		// ?¸? ????
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
/// \brief		// ?????? ???? ?ʱ?ȭ
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::InitWarInfoPointWar()
{
	m_vecWarPointInfo.clear();
	m_pScrollMotherShipInfo->SetMaxItem(m_vecWarPointInfo.size());

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::AddWarInfoPointWar(BYTE byAttackBelligerence,	// ???ݼ???
											BYTE byWinBelligerence,		// ?¸?????(0:??????)
											char* pMapName,				// ???̸?											
											ATUM_DATE_TIME	timeStartWarTime,	// ???۽ð?
											ATUM_DATE_TIME	timeEndWarTime)		//?????ð?	
{
	structWarPointInfo sMsg;
	memset(&sMsg, 0x00, sizeof(structWarPointInfo));

	// ???? ????
	if(IS_VCN_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byAttackBelligerence))
	{
		wsprintf(sMsg.chAttackInfluence,STRMSG_C_070608_0101);
	}	

	// ?¸? ????
	if(IS_VCN_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0100);
	}
	else if(IS_ANI_INFLUENCE_TYPE(byWinBelligerence))
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070608_0101);
	}
	// 2008-04-22 by bhsohn ????/?????? ???????? ?????? ǥ?? ?ϰ? ????
	else if(0 == byWinBelligerence) //(0:??????)
	{
		wsprintf(sMsg.chWinInfluence,STRMSG_C_070607_0102);		
	}
	// end 2008-04-22 by bhsohn ????/?????? ???????? ?????? ǥ?? ?ϰ? ????
	
	// ???? ?̸?
	if(pMapName)
	{
		strncpy(sMsg.MapName, pMapName, SIZE_MAX_MAP_NAME);
	}

	// ?????? ???? ?ð?	
	string szStartStrBuf;
	timeStartWarTime.GetLocalString_MMDD(timeStartWarTime.Month, 
										timeStartWarTime.Day, 
										szStartStrBuf,
										GetLanguageType());	

	// 2008-04-22 by bhsohn ????/?????? ???????? ?????? ǥ?? ?ϰ? ????
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
	// 2008-08-19 by bhsohn ??????, ?????? ???? ??ȯ ?ð????? ????
	sMsg.SummonTime = timeStartWarTime;
	

	m_vecWarPointInfo.push_back(sMsg);
	
	// 2008-08-19 by bhsohn ??????, ?????? ???? ??ȯ ?ð????? ????
	sort(m_vecWarPointInfo.begin(), m_vecWarPointInfo.end(), sort_WarPoint_summontime());	

	m_pScrollMotherShipInfo->SetMaxItem(m_vecWarPointInfo.size());
}




// 2009. 01. 12 by ckPark ???? ???? ?ý???

void	CINFCityLeader::SetWarDeclareTime( const ATUM_DATE_TIME thisWarDeclare, char* pStr )
{
	// ???? ???????? ?⵵?? 0?̸? ?????? ????
	if(thisWarDeclare.Year == 0)
		sprintf(pStr, STRMSG_C_090113_0321);		// ?????? ????
	else
	{	// %d??%d??%d?? %d:%d
		std::string strYYYYMMDD;
		thisWarDeclare.GetLocalString_YYYYMMDD(thisWarDeclare.Year, thisWarDeclare.Month, thisWarDeclare.Day, strYYYYMMDD, GetLanguageType());
		sprintf(pStr, STRMSG_C_090113_0322, strYYYYMMDD.c_str(), thisWarDeclare.Hour, thisWarDeclare.Minute );
	}
}

void	CINFCityLeader::RenderWarInfoDeclareWar(void)
{
	m_pBtnWarDeclare->Render();
	
	m_pBtnMotherShipInfo->Render();

	m_pFontWarDeclare->DrawText( OUR_THIS_TAKEOFF_X, OUR_THIS_TAKEOFF_Y, GUI_FONT_COLOR, m_szEnemyThisTakeOff );
	m_pFontWarDeclare->DrawText( OUR_NEXT_TAKEOFF_X, OUR_NEXT_TAKEOFF_Y, GUI_FONT_COLOR, m_szEnemyNextTakeOff );
	m_pFontWarDeclare->DrawText( ENEMY_THIS_TAKEOFF_X, ENEMY_THIS_TAKEOFF_Y, GUI_FONT_COLOR,  m_szOurThisTakeOff );
	m_pFontWarDeclare->DrawText( ENEMY_NEXT_TAKEOFF_X, ENEMY_NEXT_TAKEOFF_Y, GUI_FONT_COLOR,  m_szOurNextTakeOff );

	m_pFontWarDeclare->DrawText( OUR_THIS_TAKEOFFTIME_X, OUR_THIS_TAKEOFFTIME_Y, GUI_FONT_COLOR,	m_szOurThisTakeOffTime );
	m_pFontWarDeclare->DrawText( OUR_NEXT_TAKEOFFTIME_X, OUR_NEXT_TAKEOFFTIME_Y, GUI_FONT_COLOR,	m_szOurNextTakeOffTime );
	m_pFontWarDeclare->DrawText( ENEMY_THIS_TAKEOFFTIME_X, ENEMY_THIS_TAKEOFFTIME_Y, GUI_FONT_COLOR, m_szEnemyThisTakeOffTime );
	m_pFontWarDeclare->DrawText( ENEMY_NEXT_TAKEOFFTIME_X, ENEMY_NEXT_TAKEOFFTIME_Y, GUI_FONT_COLOR, m_szEnemyNextTakeOffTime);
}
// end 2009. 01. 12 by ckPark ???? ???? ?ý???





///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::RenderWarInfoPointWar()
{
	// ??ũ?? ????
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

		// ???ݼ???
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chAttackInfluence);
			nX = POINTWAR_WARINFO_VIEW_ATT_INFL_X - (sizeFont.cx/2);
			nY = POINTWAR_WARINFO_VIEW_ATT_INFL_Y + (nLine*POINTWAR_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chAttackInfluence, 0L);
		}

		// ????????Ʈ ??????
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.MapName);
			nX = POINTWAR_WARINFO_VIEW_POINT_X - (sizeFont.cx/2);;
			nY = POINTWAR_WARINFO_VIEW_POINT_Y + (nLine*POINTWAR_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.MapName, 0L);
		}

		// ?ð?
		{
			sizeFont = m_pFontWarInfo->GetStringSize(sMsg.chTimeCap);
			nX = POINTWAR_WARINFO_VIEW_TIME_X - (sizeFont.cx/2);;
			nY = POINTWAR_WARINFO_VIEW_TIME_Y + (nLine*POINTWAR_WARINFO_VIEW_CAP_HEIGHT);
			m_pFontWarInfo->DrawText(nX, nY, GUI_FONT_COLOR_W, sMsg.chTimeCap, 0L);
		}

		// ?¸? ????
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
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityLeader::WndProcWarInfoSub(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
				// ??ư Ŭ?? 
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
				// ??ư???? ???콺?? ?ִ?.
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


// 2009. 01. 12 by ckPark ???? ???? ?ý???
int		CINFCityLeader::WndProcInfluenceInfoTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return INF_MSGPROC_NORMAL;
}

int		CINFCityLeader::WndProcMotherShipResultTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 2009-03-13 by bhsohn ?????? ???? ??ũ??â ???? ????
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
	// end 2009-03-13 by bhsohn ?????? ???? ??ũ??â ???? ????
	return INF_MSGPROC_NORMAL;
}

int		CINFCityLeader::WndProcWarDeclareTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// ???????? â
			if(TRUE == m_pBtnWarDeclare->OnLButtonUp(pt))
			{
				// ??ư Ŭ?? 
				// 2009. 11. 11 by jskim  ?Ϲݼ??????? ???????? ??ư?? ?????? ???? ƨ???? ????
				if(COMPARE_INFLUENCE( g_pShuttleChild->m_myShuttleInfo.InfluenceType, INFLUENCE_TYPE_NORMAL ))
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_091111_0401,COLOR_ERROR);// "???????? ?????? ?Ұ????մϴ?."
					return INF_MSGPROC_BREAK;
				}
				//end 2009. 11. 11 by jskim  ?Ϲݼ??????? ???????? ??ư?? ?????? ???? ƨ???? ????
				g_pGameMain->GetINFMotherShipManager()->GetWarDeclareWindow()->ShowWarDeclare();
				g_pInterface->SetWindowOrder(WNDWarDecalre);
				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_BUTTON_OK, D3DXVECTOR3(0,0,0), FALSE);
				return  INF_MSGPROC_BREAK;
			}

			// ?????? ?ɼ?
			if(TRUE == m_pBtnMotherShipInfo->OnLButtonUp(pt))
			{
				// ??ư Ŭ?? 
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
				// ??ư???? ???콺?? ?ִ?.
				return  INF_MSGPROC_BREAK;
			}

			if(TRUE == m_pBtnMotherShipInfo->OnLButtonDown(pt))
			{
				// ??ư???? ???콺?? ?ִ?.
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

int		CINFCityLeader::WndProcOutPostTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return INF_MSGPROC_NORMAL;
}

int		CINFCityLeader::WndProcPointWarTab(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
// end 2009. 01. 12 by ckPark ???? ???? ?ý???



///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::TestMotherDB()
{
	for(int nCnt = 0;nCnt <10;nCnt++)
	{
		char chMonster[20];
		wsprintf(chMonster, "ROCK%d", nCnt);

		ATUM_DATE_TIME	timeStartWarTime(TRUE);
		ATUM_DATE_TIME	timeEndWarTime(TRUE);

		AddWarInfoMothership(INFLUENCE_TYPE_VCN,	// ???ݼ???
											INFLUENCE_TYPE_VCN,		// ?¸?????
											chMonster,				// ?????̸?
											100000,				// ????????Ʈ
											timeStartWarTime,	// ???۽ð?
											timeEndWarTime);	//?????ð?	
		
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::TestPointWarDB()
{
	for(int nCnt = 0;nCnt <10;nCnt++)
	{
		char chMonster[20];
		wsprintf(chMonster, "ROCK%d", nCnt);

		ATUM_DATE_TIME	timeStartWarTime(TRUE);
		ATUM_DATE_TIME	timeEndWarTime(TRUE);

		AddWarInfoPointWar(INFLUENCE_TYPE_VCN,	// ???ݼ???
											INFLUENCE_TYPE_VCN,		// ?¸?????
											chMonster,				// ?????̸?											
											timeStartWarTime,	// ???۽ð?
											timeEndWarTime);	//?????ð?	
		
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		?????? ???? ??û
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::RqMotherShipDB()
{
	g_pFieldWinSocket->SendMsg(T_FC_INFO_MSWARINFO_RESULT,NULL,NULL);
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		?????? ???? ??û
/// \author		// 2008-03-19 by bhsohn ??????, ?????? ????â
/// \date		2008-03-19 ~ 2008-03-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLeader::RqPointWarDB()
{
	g_pFieldWinSocket->SendMsg(T_FC_INFO_SPWARINFO_RESULT,NULL,NULL);
}


void CINFCityLeader::UpdateScrollPos(float fPosX, float fPosY, float fWidth, float fHeight, int nWhellHeight)
{		
	POINT ptScroll;
	RECT rcMouseWhell, rcMousePos;
	
	// ?? ??ġ???? 
	rcMouseWhell.left		= fPosX;
	rcMouseWhell.top		= fPosY;
	rcMouseWhell.right		= rcMouseWhell.left + fWidth;
	rcMouseWhell.bottom		= rcMouseWhell.top + nWhellHeight;
	
	
	// ???콺 ??ġ ????
	rcMousePos.left			= fPosX + SCROLL_BALL_POSX;
	rcMousePos.top			= fPosY + SCROLL_BALL_POSY;
	rcMousePos.right		= rcMousePos.left;
	rcMousePos.bottom		= rcMousePos.top;
		
	// Resotre?? ?ؾ????? ?̹??? ũ?⸦ ?˼? ?ִ?. 
	m_pINFScrollBar->SetPosition(rcMousePos.left, rcMousePos.top, SCROLL_BALL_WIDTH, fHeight);
	m_pINFScrollBar->SetMouseWhellRect(rcMouseWhell);			

	ptScroll = m_pINFScrollBar->GetImgBkSize();
	
	rcMousePos.bottom		= rcMousePos.top + ptScroll.y + SCROLL_BALL_SCROLL_CAP;
	rcMousePos.top			-= SCROLL_BALL_SCROLL_CAP;
	rcMousePos.right		= rcMousePos.left + SCROLL_BALL_SCROLL_CAP;
	rcMousePos.left			-= SCROLL_BALL_SCROLL_CAP;					
	
	m_pINFScrollBar->SetMouseBallRect(rcMousePos);
}
