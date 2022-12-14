// INFCityStore.cpp: implementation of the CINFCityStore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFCityStore.h"
#include "INFCityBase.h"
#include "INFScrollbar.h"
#include "INFImage.h"
#include "D3dHanFont.h"
#include "ItemInfo.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "FieldWinSocket.h"
#include "GameDataLast.h"
#include "INFWindow.h"
#include "INFGameMain.h"
#include "INFItemInfo.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFIcon.h"
#include "AtumDatabase.h"
#include "dxutil.h"
#include "Chat.h"
#include "INFSelect.h"			// 2006-09-14 by dgwoo
#include "Interface.h"
/*
#define STORE_RESIZE_X			(CITY_BASE_NPC_BOX_START_X+230)
#define STORE_RESIZE_Y			(CITY_BASE_NPC_BOX_START_Y+5)

#define STORE_START_X			(STORE_RESIZE_X + 251)
#define STORE_START_Y			(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 23)
#define STORE_SIZE_X			184
#define STORE_SIZE_Y			201
#define SCROLL_START_X			(STORE_RESIZE_X + 423)
#define SCROLL_START_Y			(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 52)
#define SCROLL_LINE_LENGTH		159

#define OK_BUTTON_START_X		(STORE_START_X+112)
#define OK_BUTTON_START_Y		(STORE_START_Y+207)
#define CANCEL_BUTTON_START_X	(STORE_START_X+112+37)
#define CANCEL_BUTTON_START_Y	(STORE_START_Y+207)
#define CASH_BUTTON_START_X		(STORE_START_X+78)
#define CASH_BUTTON_START_Y		(STORE_START_Y+208)
#define BUTTON_SIZE_X			35
#define BUTTON_SIZE_Y			16

#define STORE_SLOT_START_X		(STORE_RESIZE_X + 255)
#define STORE_SLOT_START_Y		(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 51)
#define STORE_INTERVAL			32
#define STORE_SLOT_SIZE_X		157
#define STORE_SLOT_SIZE_Y		178
#define STORE_ICON_START_X		(STORE_RESIZE_X + 258)
#define STORE_ICON_START_Y		(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 53)
#define STORE_ICON_SIZE			30
#define STORE_STRING_START_X	(STORE_RESIZE_X + 291)
#define STORE_STRING_START_Y	(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 54)
#define STORE_COUNT_START_X		(STORE_RESIZE_X + 338)
#define STORE_COUNT_START_Y		(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 72)
#define STORE_UP_START_X		(STORE_RESIZE_X + 364)
#define STORE_UP_START_Y		(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 70)
#define STORE_DOWN_START_X		(STORE_RESIZE_X + 364)
#define STORE_DOWN_START_Y		(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 79)
#define STORE_UP_SIZE_X			8
#define STORE_UP_SIZE_Y			6

#define STORE_SPI_START_X		(STORE_RESIZE_X+328)
#define STORE_SPI_START_Y		(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 232)
#define STORE_SPI_SIZE_X		104
#define STORE_SPI_SIZE_Y		16
#define INVEN_SPI_START_X		(CITY_BASE_NPC_BOX_START_X+308)
#define INVEN_SPI_START_Y		(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 230)
#define INVEN_START_X			(CITY_BASE_NPC_BOX_START_X + 310)
#define INVEN_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 23)
#define INVEN_SPI_SIZE_X		104
#define INVEN_SPI_SIZE_Y		18
//*/
//#define SMALL_BUTTON_START_X	(STORE_RESIZE_X + 372)
//#define SMALL_BUTTON_START_Y	(STORE_RESIZE_Y - SIZE_NORMAL_WINDOW_Y + 70)
//#define SMALL_BUTTON_SIZE_X		39
//#define SMALL_BUTTON_SIZE_Y		14

// 2006-09-15 by dgwoo ???? ???? ???? ?? DEFINE
//--------------------------------------------------------------------------//
//?????? ?????? ???? ????.
#define STORE_RESIZE_X			(CITY_BASE_NPC_BOX_START_X+426)
#define STORE_RESIZE_Y			(CITY_BASE_NPC_BOX_START_Y-SIZE_NORMAL_WINDOW_Y)

//?????? ?????????? ????.
#define STORE_START_X			(STORE_RESIZE_X + 18)
#define STORE_START_Y			(STORE_RESIZE_Y + 28)
#define STORE_START_W			260
#define STORE_START_H			190

// Log ????.
#define STORE_START_LOG_X		(STORE_START_X + 15)
#define STORE_START_LOG_Y		(STORE_START_Y + 30)

// FONT SIZE
#define STORE_FONT_SIZE_H		13
#define	STORE_FONT_PARTITION	11

//?????? ??????.
#define	STORE_ITEM_COUNT_X		(STORE_RESIZE_X + 226)
#define	STORE_ITEM_COUNT_Y		(STORE_RESIZE_Y + 25)

#define SCROLL_START_X			(STORE_RESIZE_X + 262)
#define SCROLL_START_Y			(STORE_RESIZE_Y + 58)
#define SCROLL_LINE_LENGTH		159

#define STORE_SPI_IMG_X			(STORE_RESIZE_X + 140)
#define STORE_SPI_IMG_Y			(STORE_RESIZE_Y + 248)

#define STORE_SPI_TEXT_X		(STORE_RESIZE_X + 171)
#define STORE_SPI_TEXT_Y		(STORE_RESIZE_Y + 244)
#define STORE_SPI_TEXT_W		104
#define STORE_SPI_TEXT_H		16
#define STORE_SPI_TEXT_FONT_X	(STORE_SPI_TEXT_X + 3)
#define	STORE_SPI_TEXT_FONT_Y	(STORE_SPI_TEXT_Y + 1)

#define STORE_ICON_START_X		(STORE_RESIZE_X + 30)
#define STORE_ICON_START_Y		(STORE_RESIZE_Y + 58)
#define	STORE_INTERVAL			32
#define STORE_ICON_SIZE			30

#define INVEN_SPI_START_X		(CITY_BASE_NPC_BOX_START_X+308)
#define INVEN_SPI_START_Y		(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 223)  // 2007-07-06 by dgwoo 230 -> 223???? ????.
#define INVEN_START_X			(CITY_BASE_NPC_BOX_START_X + 310)
#define INVEN_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 23)
#define INVEN_SPI_SIZE_X		104
#define INVEN_SPI_SIZE_Y		18



//???? ??.
#define STORE_TAB_0_X			STORE_START_X
#define STORE_TAB_0_Y			STORE_START_Y
#define STORE_TAB_W				67
#define STORE_TAB_H				14
#define STORE_TAB_1_X			(STORE_TAB_0_X + STORE_TAB_W)
#define STORE_TAB_2_X			(STORE_TAB_1_X + STORE_TAB_W)

//???? ??.
#define STORE_TAB_3_X			STORE_START_X
#define STORE_TAB_1_Y			(STORE_RESIZE_Y + 228)
#define STORE_TAB_4_X			(STORE_TAB_3_X + STORE_TAB_W)

//--------------------------------------------------------------------------//

// 2006-03-07 by ispark, ?????? ???? ???? ????
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn ???? ???? ????
#define FONTSPI_Y				1
#define FONTSTORESIZE_Y			212
#else
#define FONTSPI_Y				1//2
#define FONTSTORESIZE_Y			212//210
#endif
// 2006-09-28 by dgwoo ???? ???? ???? ???? ????.
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn ???? ???? ????
#define STRING_CULL ::StringCullingUserData_ToBlank
#define STRING_CULL2 ::StringCullingUserData_ToBlank
#define CHAT_STRING_LENGTH			220
#define FONT_INPUT_Y				12	
#else
#define STRING_CULL ::StringCullingUserDataEx
#define STRING_CULL2 ::StringCullingUserDataEx
#define CHAT_STRING_LENGTH			220
#define FONT_INPUT_Y				12
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityStore::CINFCityStore(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	m_bRestored = FALSE;
	m_pParent = pParent;
	m_pBuildingInfo = pBuilding;
	int i;
	for(i = 0; i < STORE_TAB_COUNT; i++)
	{
		m_pBack[i] = NULL;
		m_pFontUserName[i] = NULL;
		m_pBack_NormalYedang[i] = NULL;
	}
	m_pBack_Normal = NULL;

	m_pCash = NULL;
	m_pSlot = NULL;
	m_pSelectSlot = NULL;
	m_pSpis = NULL;
	// 2007-02-12 by bhsohn Item ???? ???? ????
	m_pMultiItemSelImage = NULL;
	// end 2007-02-12 by bhsohn Item ???? ???? ????


	m_bInputItemDone = FALSE;		
//	m_pSelectIcon	 = NULL;
	m_pItemInfo = NULL;

	m_pFontSpi = NULL;
	m_pFontStoreSize = NULL;
	m_pFontItemNum = NULL;
	m_pFontLog	= NULL;
	m_pScroll = NULL;
	m_nItemSpi = 0;
	m_nLineCount = 0;
	m_pnSelectCurrentCount = NULL;
	m_hyItemSpiUniqueNumber = 0;

	m_nRenderMoveIconIntervalHeight = 0;
	m_nRenderMoveIconIntervalWidth = 0;	
	m_bSelectDown = FALSE;
	
}

CINFCityStore::~CINFCityStore()
{
	int i;
	for(i = 0; i < STORE_TAB_COUNT; i++)
	{
		SAFE_DELETE(m_pBack[i]);
//#if defined(LANGUAGE_KOREA)|| defined(LANGUAGE_CHINA)
		SAFE_DELETE(m_pBack_NormalYedang[i]);
//#endif
		SAFE_DELETE(m_pFontUserName[i])
	}
	SAFE_DELETE(m_pBack_Normal);
	SAFE_DELETE(m_pCash);
	SAFE_DELETE(m_pSlot);
	SAFE_DELETE(m_pSelectSlot);
	SAFE_DELETE(m_pSpis);
	// 2007-02-12 by bhsohn Item ???? ???? ????
	SAFE_DELETE(m_pMultiItemSelImage);	 
	// end 2007-02-12 by bhsohn Item ???? ???? ????
	SAFE_DELETE(m_pFontSpi);
	SAFE_DELETE(m_pFontStoreSize);
	SAFE_DELETE(m_pFontItemNum);
	SAFE_DELETE(m_pFontLog);
	SAFE_DELETE(m_pScroll);
	SAFE_DELETE_ARRAY(m_pnSelectCurrentCount);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityStore::InitData()
/// \brief		???? ?????? ??????
/// \author		dhkwon
/// \date		2004-07-14 ~ 2004-07-14
/// \warning	???? ?????? ???? ???????? ??????.
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::InitData()
{
	if(m_pScroll)
	{
		m_pScroll->Reset();
	}
	m_bInputItemDone = FALSE;
	m_nActTab = g_pSelect->GetCurrentSelectIndex();
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end() )
	{
		SAFE_DELETE( *it );
		it++;
	}
	m_vecItemInfo.clear();
	m_nItemSpi = 0;
	//SAFE_DELETE_ARRAY(m_pnSelectCurrentCount);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityStore::ChangeTab(int nTab)
/// \brief		
/// \author		dgwoo
/// \date		2006-09-15 ~ 2006-09-15
/// \warning	
///
/// \param		nTab???? ?????? ?????? ????????.
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::ChangeTab(int nTab)
{
// 2007-10-10 by dgwoo ?????? ???????? ?????????? ???????? ????????.
#if defined(GUILD_WAREHOUSE_ACCESS_HSSON)|| defined(LANGUAGE_CHINA)
	if(nTab == m_nActTab)
	{
		return ;
	}
#else
	if(0 == g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1)
	{
		return;
	}else if(nTab == m_nActTab)
	{
		return ;
	}
#endif

	//--------------------------------------------------------------------------//
	if(nTab < SELECT_MODE)
	{// ???????? ????.
		//if(NULL != g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1)
		//	CharacterTab(nTab);
		//else if(nTab == g_pSelect->GetCurrentSelectIndex())
			CharacterTab(nTab);
	}
	else 
	{// ???? ????.
		
		if(NULL != g_pShuttleChild->m_myShuttleInfo.GuildUniqueNumber)
		{
			GuildTab(nTab);
		}
		else
		{// ???????? ????????. error Message
			g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_061011_0100,COLOR_ERROR);
		}
	}
	// 2006-09-21 by dgwoo ???? ???? ???? ???? ?????? ???? ???????? ??????????.
	SetSelectItem(NULL);
	m_pScroll->SetNumberOfWindowList(STORE_SLOT_NUMBER_Y);
	m_bSelectDown = FALSE;

	// 2007-02-22 by bhsohn Item ???? ???? ???? ????
	// ???? ???????? ???? ?? ???? ?????? 
	g_pD3dApp->DelMultiItemList(TRUE);

}
void CINFCityStore::GuildTabLog()
{
	//m_pScroll->SetNumberOfWindowList(STORE_SLOT_NUMBER_Y);
	g_pD3dApp->m_bRequestEnable = FALSE;
	MSG_FC_STORE_LOG_GUILD_ITEM sMsg;
	sMsg.AccountUID		= g_pShuttleChild->m_myShuttleInfo.AccountUniqueNumber;
	sMsg.CharacterUID	= g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
	g_pFieldWinSocket->SendMsg( T_FC_STORE_LOG_GUILD_ITEM, (char*)&sMsg, sizeof(sMsg) );
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			SetItemFullName()
/// \brief		???? ???????? ???? ???? ?????????? ????.
/// \author		dgwoo
/// \date		2006-10-10 ~ 2006-10-10
/// \warning	
///
/// \param		char *o_szFullName, char * strName,int PrefixCodeNum, int SuffixCodeNum
/// \return		char * 
///////////////////////////////////////////////////////////////////////////////
char * CINFCityStore::SetItemFullName(char *o_szFullName, char * strName,int PrefixCodeNum, int SuffixCodeNum)
{
	char szPre[256] = {0,};
	char szSuf[256] = {0,};
	
	RARE_ITEM_INFO* pRefPrefixRareInfo = g_pDatabase->GetServerRareItemInfo(PrefixCodeNum);
	RARE_ITEM_INFO* pRefSuffixRareInfo = g_pDatabase->GetServerRareItemInfo(SuffixCodeNum);
	if(pRefPrefixRareInfo)
	{
		wsprintf( szPre, "\\g%s\\g ", pRefPrefixRareInfo->Name );
	}

	if( pRefSuffixRareInfo)
	{
			wsprintf( szSuf," \\g%s\\g", pRefSuffixRareInfo->Name);
	}

	wsprintf(o_szFullName, "%s%s%s",szPre, strName, szSuf );
	return o_szFullName;
}
void CINFCityStore::StringInOrderBound(MSG_FC_STORE_LOG_GUILD_ITEM_OK *pMsg)
{
	char buf[1024] = {0,};
	char Date[SIZE_MAX_ATUM_DATE_TIME_STRING] = {0,};
	char ItemName[ITEMINFO_ITEM_FULL_NAME] = {0,};
	//wsprintf(Date,"%s",pMsg->Time.GetDateTimeString(Date));
	pMsg->Time.GetLocalDateTimeString(string(),GetLanguageType());
	ITEM* pWeaponITEM = g_pDatabase->GetServerItemInfo(pMsg->ItemNum);
	SetItemFullName(ItemName, pWeaponITEM->ItemName,pMsg->PrefixCodeNum,pMsg->SuffixCodeNum);
	  
	if(T1_FL_LOG_ITEM_INSERT_TO_GUILDSTORE == pMsg->LogType)
	{// ???? ?????? ????????.
		if(pMsg->ItemNum == MONEY_ITEM_NUMBER)
		{
			wsprintf(buf,STRMSG_C_060927_0102,Date,pMsg->CharacterName,abs(pMsg->ItemChangeCount));
		}
		else
		{
			wsprintf(buf,STRMSG_C_060927_0100,Date,pMsg->CharacterName,ItemName,abs(pMsg->ItemChangeCount));
		}
	}
	else if(T1_FL_LOG_ITEM_DRAW_FROM_GUILDSTORE == pMsg->LogType)
	{// ???????????? ???????? ????????.
		if(pMsg->ItemNum == MONEY_ITEM_NUMBER)
		{
			wsprintf(buf,STRMSG_C_060927_0103,Date,pMsg->CharacterName,abs(pMsg->ItemChangeCount));
		}
		else
		{
			wsprintf(buf,STRMSG_C_060927_0101,Date,pMsg->CharacterName,ItemName,abs(pMsg->ItemChangeCount));
		}

	}
		
	///////////////////////////////////////////////////////////////////////////////
	//	1. ?????? ?????? Rendering ????
	//	2. ?????? ?????? Rendering ????
	// 2006-04-13 by ispark, ????
	int nLineCount = 0;
	int pFontTexWidth = m_pFontLog->GetStringSize(buf).cx;
	if(pFontTexWidth <= CHAT_STRING_LENGTH)
	{// ?????? ??????.
		nLineCount++;
	}
	else
	{// ?????? ??????.
		vector<string> vecChatMessage;
		vecChatMessage.clear();
		STRING_CULL(buf, CHAT_STRING_LENGTH, &vecChatMessage, m_pFontLog);
		nLineCount = vecChatMessage.size();
		vecChatMessage.clear();
	}
	m_nGuildLogTotalLine += nLineCount;
	//DBGOUT("m_nGuildLogTotalLine = %d  nLineCount = %d\n",m_nGuildLogTotalLine,nLineCount);
	STORE_LOG_DATA LogData;
	LogData.LogType = pMsg->LogType;
	STRNCPY_MEMSET(LogData.strDate,Date,SIZE_MAX_ATUM_DATE_TIME_STRING);
	STRNCPY_MEMSET(LogData.CharacterName,pMsg->CharacterName,SIZE_MAX_CHARACTER_NAME);
	STRNCPY_MEMSET(LogData.ItemName,ItemName,ITEMINFO_ITEM_FULL_NAME);
	LogData.ItemNum			= pMsg->ItemNum;
	LogData.ItemChangeCount = pMsg->ItemChangeCount;
	LogData.nLineCount		= nLineCount;
	m_vecLogStruct.push_back(LogData);
	

}
void CINFCityStore::HeaderGuildLog()
{
	m_nGuildLogTotalLine = 0;
	//g_pD3dApp->m_bRequestEnable = FALSE;
	//DBGOUT("HeaderGuildLog\n");
	m_vecLogStruct.clear();
}
void CINFCityStore::DoneGuildLog()
{
	// 2006-09-28 by dgwoo ???????? ?????? ???????? ???? ?????????? ?????? ????????.
	g_pD3dApp->m_bRequestEnable = TRUE;
	//DBGOUT("DoneGuildLog\n");
	m_pScroll->SetNumberOfWindowList(STORE_FONT_PARTITION);
	m_pScroll->SetNumberOfData(m_nGuildLogTotalLine);

}
void CINFCityStore::GuildTab(int nTab)
{
	m_nActTab = nTab;
	if(m_pScroll)
	{
		m_pScroll->Reset();
	}
	//DBGOUT("m_bRequstEnable = %d\n",g_pD3dApp->m_bRequestEnable);
	if(STORE_TAB_GUILD_LOG == nTab)
	{// ????.
		GuildTabLog();
		return ;
	}
	SetStoreItemSPI();
	
}

void CINFCityStore::SetStoreItemSPI()
{
	//?????? ???? ?????? ????.
	m_bInputItemDone = FALSE;
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end() )
	{
		SAFE_DELETE( *it );
		it++;
	}
	m_vecItemInfo.clear();
	m_nItemSpi = 0;
	
	g_pD3dApp->m_bRequestEnable = FALSE;
	MSG_FC_STORE_GET_ITEM sMsg;
	sMsg.AccountUniqueNumber = g_pShuttleChild->m_myShuttleInfo.AccountUniqueNumber;
	sMsg.bSendToClient = TRUE;
	sMsg.PossessCharacter = g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
//	sMsg.ItemStorage0 = ITEM_IN_GUILD_STORE;//ITEM_IN_STORE
	if(GetActTab() == TAB_GUILD)
	{
		sMsg.ItemStorage0 = ITEM_IN_GUILD_STORE;
	}
	else
	{
		sMsg.ItemStorage0 = ITEM_IN_STORE;
	}
	g_pFieldWinSocket->SendMsg( T_FC_STORE_GET_ITEM, (char*)&sMsg, sizeof(sMsg) );
}
void CINFCityStore::CharacterTab(int nTab)
{
	if(NULL == g_pSelect->m_guiUnitInfo[nTab].CharacterUniqueNumber)
	{//???????? ???? ????.
		return; 
	}
	MSG_FC_STORE_GET_ITEM sMsg;
	if(0 == g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1)
	{// ?????????? ????????.
		if(nTab == 0)
		{// ?????? ?????? ?????? ?????? ????.
			sMsg.PossessCharacter = g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
		}
		else
		{// ???? ???? ???? ????.
			return;
		}
	}
	else
	{// ???????? ????
		sMsg.PossessCharacter = g_pSelect->m_guiUnitInfo[nTab].CharacterUniqueNumber;
	}
	m_nActTab = nTab;
	if(m_pScroll)
	{
		m_pScroll->Reset();
	}
	//?????? ???? ????.
	m_bInputItemDone = FALSE;

	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end() )
	{
		SAFE_DELETE( *it );
		it++;
	}
	m_vecItemInfo.clear();
	m_nItemSpi = 0;
	g_pD3dApp->m_bRequestEnable = FALSE;
	 
	
	sMsg.AccountUniqueNumber = g_pShuttleChild->m_myShuttleInfo.AccountUniqueNumber;
	sMsg.bSendToClient = TRUE;
	// 2006-09-14 by dgwoo ???? ???????? ?????? ?????? ????????.
	
	sMsg.ItemStorage0 = ITEM_IN_STORE;
	g_pFieldWinSocket->SendMsg( T_FC_STORE_GET_ITEM, (char*)&sMsg, sizeof(sMsg) );
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityStore::PutItem(char* pMsg, BOOL bUpdate)
/// \brief		???????? ???????? ?? ????
/// \author		dhkwon
/// \date		2004-07-14 ~ 2004-07-14
/// \warning	bUpdate = TRUE ???? ???????? ??????, FALSE???? ????????.
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int	 CINFCityStore::PutItem(char* p, BOOL bUpdate)			// server???? ?????? ???? ????
{
	int usebyte = 0;

	if(IS_SKILL_ITEM(((ITEM_BASE*)p)->Kind))
	{
		DBGOUT("Skillitem(%d) is can't put in Store.\n", ((ITEM_BASE*)p)->ItemNum);
		usebyte = sizeof(ITEM_SKILL);
	}
	else
	{
		if(((ITEM_GENERAL*)p)->ItemNum == MONEY_ITEM_NUMBER)
		{
			m_hyItemSpiUniqueNumber = ((ITEM_GENERAL*)p)->UniqueNumber;
			if(bUpdate)
			{
				AddItemSpi(((ITEM_GENERAL*)p)->CurrentCount);
			}
			else
			{
				SetItemSpi(((ITEM_GENERAL*)p)->CurrentCount);
			}
//			SetItemSpi(((ITEM_GENERAL*)p)->CurrentCount);
			return sizeof(ITEM_GENERAL);
		}
		CItemInfo* pItemInfo = new CItemInfo((ITEM_GENERAL*)p);
		usebyte = sizeof(ITEM_GENERAL);
		switch(pItemInfo->Kind)
		{
		case ITEMKIND_ENERGY:
		case ITEMKIND_INGOT:
		case ITEMKIND_BULLET:
			{
				// Energy???? ???????? ?????? ?????????? ?????? ?????? ???? ??????????????.
				CVectorItemInfoIterator it = m_vecItemInfo.begin();
				while( it != m_vecItemInfo.end() )
				{
					if( (*it)->UniqueNumber == pItemInfo->UniqueNumber )
					{
						break;
					}
					it++;
				}
				if(it != m_vecItemInfo.end())
				{
					if(bUpdate)
					{
						(*it)->CurrentCount += pItemInfo->CurrentCount;
					}
					else
					{
						(*it)->CurrentCount = pItemInfo->CurrentCount;
					}
					delete pItemInfo;
				}
				else
				{
					m_vecItemInfo.push_back(pItemInfo);
				}
			}
			break;
		default:
			{
				AddItem(pItemInfo);
			}
			break;
		}
	}
	return sizeof(ITEM_GENERAL);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityStore::AddItem(CItemInfo* pItemInfo)
/// \brief		?????? ???????? vector?? ??????.
/// \author		dhkwon
/// \date		2004-07-14 ~ 2004-07-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::AddItem(CItemInfo* pItemInfo)
{
	//DBGOUT("Add Store %s(%d)\n", pItemInfo->ItemInfo->ItemName, pItemInfo->UniqueNumber);
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while( it != m_vecItemInfo.end() )
	{
		if( (*it)->UniqueNumber == pItemInfo->UniqueNumber )
		{
			DBGOUT("Already existent item in store(UniqueNum:%d).\n", pItemInfo->UniqueNumber);
			delete pItemInfo;
			return;
		}
		it++;
	}
	m_vecItemInfo.push_back(pItemInfo);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityStore::InputItemDone()	
/// \brief		???????? ???????? ???? ???? ?????? ????
///	
/// \author		dhkwon
/// \date		2004-07-14 ~ 2004-07-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::InputItemDone()
{
	// 2006-10-26 by ispark
	g_pD3dApp->m_bRequestEnable = TRUE;
	g_pD3dApp->m_fRequestEnableTime = REQUEST_ENABLE_INIT_TIME;

	m_bInputItemDone = TRUE;
	int nSize = m_vecItemInfo.size();
	m_pScroll->SetNumberOfData( nSize/STORE_SLOT_NUMBER_X );
	SAFE_DELETE_ARRAY(m_pnSelectCurrentCount);
	if(nSize>0)
	{
		m_pnSelectCurrentCount = new int[nSize];
		memset(m_pnSelectCurrentCount,0x00, sizeof(int)*nSize);
	}
	StoreItemSort();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityStore::FieldSocketSendItemToCharacter( UID64_t nUniqueNumber, int nCount )
/// \brief		???????? ?????? ?????????? ????
/// \author		dhkwon
/// \date		2004-07-14 ~ 2004-07-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::FieldSocketSendItemToCharacter( UID64_t nUniqueNumber, int nCount )
{
	MSG_FC_STORE_MOVE_ITEM sMsg;
	sMsg.ItemUniqueNumber	= nUniqueNumber;
	sMsg.ToItemStorage		= ITEM_IN_CHARACTER;
	g_pD3dApp->m_bRequestEnable = FALSE;				// 2006-10-25 by dgwoo

	// 2006-09-14 by dgwoo ???? ????.
	if(m_nActTab < SELECT_MODE)
	{//???????? ?????? ????.
		//sMsg.Uid32StoreCharacterUID = g_pSelect->m_guiUnitInfo[m_nActTab].CharacterUniqueNumber;
		sMsg.FromItemStorage	= ITEM_IN_STORE;
		
	}else
	{// ???????? ?????? ????.
		//sMsg.Uid32StoreCharacterUID = 0;
		sMsg.FromItemStorage		= ITEM_IN_GUILD_STORE;
	}
	sMsg.Count				= nCount;
	g_pFieldWinSocket->SendMsg( T_FC_STORE_MOVE_ITEM, (char*)&sMsg, sizeof(sMsg) );
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityStore::FieldSocketSendItemToStore( UID64_t nUniqueNumber, int nCount )
/// \brief		???????? ?????? ????
/// \author		dhkwon
/// \date		2004-07-14 ~ 2004-07-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::FieldSocketSendItemToStore( UID64_t nUniqueNumber, int nCount )
{
	MSG_FC_STORE_MOVE_ITEM sMsg;
	sMsg.ItemUniqueNumber	= nUniqueNumber;
	sMsg.FromItemStorage	= ITEM_IN_CHARACTER;
	g_pD3dApp->m_bRequestEnable = FALSE;				// 2006-10-25 by dgwoo

	// 2006-09-14 by dgwoo ???? ???? 
	if(m_nActTab < SELECT_MODE)
	{//?????? ?????? ?????? ????.
		//sMsg.Uid32StoreCharacterUID = g_pSelect->m_guiUnitInfo[m_nActTab].CharacterUniqueNumber;
	sMsg.ToItemStorage		= ITEM_IN_STORE;
	}else
	{// ???? ?????? ?????? ????.
		//sMsg.Uid32StoreCharacterUID = 0;
		sMsg.ToItemStorage		= ITEM_IN_GUILD_STORE;
	}
	
	sMsg.Count = nCount;
	g_pFieldWinSocket->SendMsg( T_FC_STORE_MOVE_ITEM, (char*)&sMsg, sizeof(sMsg) );
}

void CINFCityStore::UpdateItemCount(UID64_t nUniqueNumber, int nCount)
{
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end())
	{
		if((*it)->UniqueNumber == nUniqueNumber)
		{
			(*it)->CurrentCount = nCount;
			break;
		}
		it++;
	}
}

void CINFCityStore::DeleteItem(UID64_t nUniqueNumber)
{
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end())
	{
		if((*it)->UniqueNumber == nUniqueNumber)
		{
			SAFE_DELETE(*it);
			m_vecItemInfo.erase(it);
			InputItemDone();
			break;
		}
		it++;
	}
}

//void CINFCityStore::AddEnchantItem(UID64_t nUniqueNumber, BYTE nDestParam, float fParamValue)
//{
//	CVectorItemInfoIterator it = m_vecItemInfo.begin();
//	while(it != m_vecItemInfo.end())
//	{
//		if((*it)->UniqueNumber == nUniqueNumber)
//		{
//			(*it)->PutEnchant(nDestParam, fParamValue);
//			break;
//		}
//		it++;
//	}
//}

void CINFCityStore::AddEnchantItem(UID64_t nUniqueNumber, INT nEnchantItemNum)
{
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end())
	{
		if((*it)->UniqueNumber == nUniqueNumber)
		{
			(*it)->AddEnchantItem( nEnchantItemNum );
//			ITEM* pEnchantITEM = g_pDatabase->GetServerItemInfo( nEnchantItemNum );
//			if( pEnchantITEM )
//			{
//				if( pEnchantITEM->DestParameter1 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter1, pEnchantITEM->ParameterValue1);
//				}
//				if( pEnchantITEM->DestParameter2 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter2, pEnchantITEM->ParameterValue2);
//				}
//				if( pEnchantITEM->DestParameter3 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter3, pEnchantITEM->ParameterValue3);
//				}
//				if( pEnchantITEM->DestParameter4 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter4, pEnchantITEM->ParameterValue4);
//				}
//			}
			break;
		}
		it++;
	}
}

HRESULT CINFCityStore::InitDeviceObjects()
{
	DataHeader	* pDataHeader;
	int i;
		char buf[16];

	for(i = 0; i < STORE_TAB_COUNT; i++)
	{
		wsprintf(buf,"store0%d",i);
		
		pDataHeader = FindResource(buf);
		if(pDataHeader)
		{
			m_pBack[i] = new CINFImage;
			m_pBack[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		}
		m_pFontUserName[i] = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, FALSE,128,32);
		m_pFontUserName[i]->InitDeviceObjects(g_pD3dDev);
	}

	// 2006-10-17 by ispark, ???? ????
	wsprintf(buf, "store_n");
	pDataHeader = FindResource(buf);
	if(pDataHeader)
	{
		m_pBack_Normal = new CINFImage;
		m_pBack_Normal->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	}
#if defined(WAREHOUSE_SHARES_HSSON)|| defined(LANGUAGE_CHINA)
	//--------------------------------------------------------------------------//
	wsprintf(buf, "store_n1");
	pDataHeader = FindResource(buf);
	if(pDataHeader)
	{
		m_pBack_NormalYedang[0] = new CINFImage;
		m_pBack_NormalYedang[0]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
		m_pBack_NormalYedang[1] = new CINFImage;
		m_pBack_NormalYedang[1]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
		m_pBack_NormalYedang[2] = new CINFImage;
		m_pBack_NormalYedang[2]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	}

	wsprintf(buf, "store_n2");
	pDataHeader = FindResource(buf);
	if(pDataHeader)
	{
		m_pBack_NormalYedang[3] = new CINFImage;
		m_pBack_NormalYedang[3]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	}
	wsprintf(buf, "store_n3");
	pDataHeader = FindResource(buf);
	if(pDataHeader)
	{
		m_pBack_NormalYedang[4] = new CINFImage;
		m_pBack_NormalYedang[4]->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize);
	}
	//--------------------------------------------------------------------------//
#endif	
	
	m_pCash = new CINFImage;
	pDataHeader = FindResource("scash");
	m_pCash->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pSlot = new CINFImage;
	pDataHeader = FindResource("stslot");
	m_pSlot->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pSelectSlot = new CINFImage;
	pDataHeader = FindResource("stselect");
	m_pSelectSlot->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	
	m_pSpis = new CINFImage;
	pDataHeader = FindResource("stespi");
	m_pSpis->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	// 2007-02-12 by bhsohn Item ???? ???? ????
	m_pMultiItemSelImage = new CINFImage;
	pDataHeader = FindResource("selicon");
	m_pMultiItemSelImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;	
	// end 2007-02-12 by bhsohn Item ???? ???? ????

	m_pFontSpi = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontSpi->InitDeviceObjects(g_pD3dDev);
	m_pFontStoreSize = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontStoreSize->InitDeviceObjects(g_pD3dDev);
	m_pFontItemNum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE,  TRUE,256,32);
	m_pFontItemNum->InitDeviceObjects(g_pD3dDev);
	m_pFontLog = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9,D3DFONT_ZENABLE, FALSE, 256,32);
	m_pFontLog->InitDeviceObjects(g_pD3dDev);

	m_pScroll = new CINFScrollBar(this,
								SCROLL_START_X, 
								SCROLL_START_Y, 
								SCROLL_LINE_LENGTH,
								STORE_SLOT_NUMBER_Y);
	m_pScroll->SetGameData( m_pGameData );
	m_pScroll->InitDeviceObjects();
	m_pScroll->SetWheelRect(STORE_START_X, 
							STORE_START_Y,
							STORE_START_X+STORE_START_W,
							STORE_START_Y+STORE_START_H);
	return S_OK;

}


HRESULT CINFCityStore::RestoreDeviceObjects()
{
	int i;
	for(i = 0; i < STORE_TAB_COUNT; i++)
	{
		m_pBack[i]->RestoreDeviceObjects();
		m_pBack[i]->Move(STORE_START_X, STORE_START_Y);
//#if defined(LANGUAGE_KOREA)|| defined(LANGUAGE_CHINA)
		if(m_pBack_NormalYedang[i])
		{
			m_pBack_NormalYedang[i]->RestoreDeviceObjects();
			m_pBack_NormalYedang[i]->Move(STORE_START_X, STORE_START_Y);
		}
//#endif
		m_pFontUserName[i]->RestoreDeviceObjects();
	}
	m_pBack_Normal->RestoreDeviceObjects();
	m_pBack_Normal->Move(STORE_START_X, STORE_START_Y);
	
	m_pCash->RestoreDeviceObjects() ;
	m_pCash->Move(STORE_SPI_TEXT_X, STORE_SPI_TEXT_Y);
	m_pSlot->RestoreDeviceObjects() ;
	m_pSelectSlot->RestoreDeviceObjects() ;
	m_pSpis->RestoreDeviceObjects() ;
	m_pSpis->Move(STORE_SPI_IMG_X, STORE_SPI_IMG_Y);

	// 2007-02-12 by bhsohn Item ???? ???? ????	
	m_pMultiItemSelImage->RestoreDeviceObjects() ;
	// end 2007-02-12 by bhsohn Item ???? ???? ????

	m_pFontSpi->RestoreDeviceObjects();
	m_pFontStoreSize->RestoreDeviceObjects();
	m_pFontItemNum->RestoreDeviceObjects();
	m_pFontLog->RestoreDeviceObjects();
	m_pScroll->RestoreDeviceObjects();

	m_bRestored = TRUE;
	return S_OK;
}

HRESULT CINFCityStore::InvalidateDeviceObjects()
{
	int i;
	for(i = 0; i < STORE_TAB_COUNT; i++)
	{
		m_pBack[i]->InvalidateDeviceObjects();
//#if defined(LANGUAGE_KOREA)|| defined(LANGUAGE_CHINA)
		if(m_pBack_NormalYedang[i])
		{
			m_pBack_NormalYedang[i]->InvalidateDeviceObjects();
		}
//#endif
		m_pFontUserName[i]->InvalidateDeviceObjects();

	}
	m_pBack_Normal->InvalidateDeviceObjects();

	m_pCash->InvalidateDeviceObjects() ;
	m_pSlot->InvalidateDeviceObjects() ;
	m_pSelectSlot->InvalidateDeviceObjects() ;
	m_pSpis->InvalidateDeviceObjects() ;
	// 2007-02-12 by bhsohn Item ???? ???? ????		
	m_pMultiItemSelImage->InvalidateDeviceObjects() ;
	// end 2007-02-12 by bhsohn Item ???? ???? ????	


	m_pFontSpi->InvalidateDeviceObjects();
	m_pFontStoreSize->InvalidateDeviceObjects();
	m_pFontItemNum->InvalidateDeviceObjects();
	m_pFontLog->InvalidateDeviceObjects();
	m_pScroll->InvalidateDeviceObjects();
	
	m_bRestored = FALSE;
	return S_OK;
}

HRESULT CINFCityStore::DeleteDeviceObjects()
{
	int i;
	for(i = 0; i < STORE_TAB_COUNT; i++)
	{
		m_pBack[i]->DeleteDeviceObjects();
//#if defined(LANGUAGE_KOREA)|| defined(LANGUAGE_CHINA)
		if(m_pBack_NormalYedang[i])
		{
			m_pBack_NormalYedang[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pBack_NormalYedang[i]);
		}
//#endif
		m_pFontUserName[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pBack[i]);
		
		SAFE_DELETE(m_pFontUserName[i])
	}
	m_pBack_Normal->DeleteDeviceObjects();
	SAFE_DELETE(m_pBack_Normal);
	
	m_pCash->DeleteDeviceObjects() ;
	m_pSlot->DeleteDeviceObjects() ;
	m_pSelectSlot->DeleteDeviceObjects() ;
	
	SAFE_DELETE(m_pCash);
	SAFE_DELETE(m_pSlot);
	SAFE_DELETE(m_pSelectSlot);

	if(m_pSpis)
	{
		m_pSpis->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pSpis);
	}
	// 2007-02-12 by bhsohn Item ???? ???? ????			
	if(m_pMultiItemSelImage)
	{
		m_pMultiItemSelImage->DeleteDeviceObjects() ;
		SAFE_DELETE(m_pMultiItemSelImage);
	}
	// end 2007-02-12 by bhsohn Item ???? ???? ????		

	m_pFontSpi->DeleteDeviceObjects();
	m_pFontStoreSize->DeleteDeviceObjects();
	m_pFontItemNum->DeleteDeviceObjects();
	m_pFontLog->DeleteDeviceObjects();
	m_pScroll->DeleteDeviceObjects();
	SAFE_DELETE(m_pFontSpi);
	SAFE_DELETE(m_pFontLog);
	SAFE_DELETE(m_pScroll);
	return S_OK;
}

void CINFCityStore::RenderLog()
{
	
	int nStartLineCount = m_pScroll->GetCurrentScrollIndex();
	int nLogCount		= 0;									//log?? ?????? ????????.
	int nLineCount		= 0;									

	char buf[256] = {0,};

	vector<STORE_LOG_DATA>::iterator it = m_vecLogStruct.begin();

	while(it != m_vecLogStruct.end())
	{
		int nStartCount = nStartLineCount;
		if(nStartLineCount <= nLineCount + it->nLineCount)
		{// 2006-09-28 by dgwoo  ?????????? ??????.
			if(T1_FL_LOG_ITEM_INSERT_TO_GUILDSTORE == it->LogType)
			{// ???? ?????? ????????.
				if(it->ItemNum == MONEY_ITEM_NUMBER)
				{
					wsprintf(buf,STRMSG_C_060927_0102,it->strDate,it->CharacterName,abs(it->ItemChangeCount));
				}
				else
				{
					wsprintf(buf,STRMSG_C_060927_0100,it->strDate,it->CharacterName,it->ItemName,abs(it->ItemChangeCount));
				}
			}
			else if(T1_FL_LOG_ITEM_DRAW_FROM_GUILDSTORE == it->LogType)
			{// ???????????? ???????? ????????.
				if(it->ItemNum == MONEY_ITEM_NUMBER)
				{
					wsprintf(buf,STRMSG_C_060927_0103,it->strDate,it->CharacterName,abs(it->ItemChangeCount));
				}
				else
				{
					wsprintf(buf,STRMSG_C_060927_0101,it->strDate,it->CharacterName,it->ItemName,abs(it->ItemChangeCount));
				}

			}
				
			///////////////////////////////////////////////////////////////////////////////
			//	1. ?????? ?????? Rendering ????
			//	2. ?????? ?????? Rendering ????
			// 2006-04-13 by ispark, ????
			int pFontTexWidth = m_pFontLog->GetStringSize(buf).cx;
			if(pFontTexWidth <= CHAT_STRING_LENGTH)
			{// ?????? ??????.
				m_pFontLog->DrawText(STORE_START_LOG_X
					, STORE_START_LOG_Y + (STORE_FONT_SIZE_H * nLogCount)
					, GUI_FONT_COLOR
					, buf
					, 0L);
				nLogCount++;
				if(STORE_FONT_PARTITION < nLogCount)
				{
					return;
				}
			}
			else
			{// ????????????.
				vector<string> vecChatMessage;
				vecChatMessage.clear();
				STRING_CULL(buf, CHAT_STRING_LENGTH, &vecChatMessage, m_pFontLog);

				for(int i = 0; i <= vecChatMessage.size() - 1; i++)
				{
					if(nStartCount > nLineCount)
					{
						nStartCount--;
					}
					else
					{
						char* ptemp = (char*)vecChatMessage[i].c_str();
						m_pFontLog->DrawText(STORE_START_LOG_X
							, STORE_START_LOG_Y + (STORE_FONT_SIZE_H * nLogCount)
							, GUI_FONT_COLOR
							, ptemp
							, 0L);
						nLogCount++;
						if(STORE_FONT_PARTITION < nLogCount)
						{
							vecChatMessage.clear();
							return;
						}
					}
				}
				vecChatMessage.clear();
			}

		}
		nLineCount += it->nLineCount;
		it++;			
	}

	
}
void CINFCityStore::Render()
{		
	int i,j;

	// 2006-10-17 by ispark, ???? ????
	if(0 == g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1)
	{
#if defined(WAREHOUSE_SHARES_HSSON)|| defined(LANGUAGE_CHINA)
		RenderNormalYedang();
#else
		RenderNormal();
#endif	

	}
	// ?????? ????
	else
	{
		RenderMemberShip();
	}
	char buf[64];
	char temp1[64];
	char temp2[64];
	
	m_pScroll->Render();

	if(m_nActTab >= TAB_GUILD_LOG)
	{
		RenderLog();
		return;
	}
	m_pSpis->Render();
	m_pCash->Render();
	
	wsprintf( temp1, "%d", m_nItemSpi );
	MakeCurrencySeparator( temp2, temp1, 3, ',' );
	m_pFontSpi->DrawText(STORE_SPI_TEXT_FONT_X,STORE_SPI_TEXT_FONT_Y, GUI_FONT_COLOR, temp2, 0L);
	
	// 2006-09-18 by dgwoo ?????? ???????? ??????.
	// ??????
	if(m_nActTab >= TAB_CHARACTER_1 && m_nActTab <= TAB_CHARACTER_3)
	{
	//wsprintf( temp1, "[%3d/%d]", m_vecItemInfo.size(), SIZE_MAX_ITEM_GENERAL_IN_STORE - 1);	// 2006-06-23 by ispark, -1?? ???? ???????? ???????? ??????.
	// 2009. 11. 3 by jskim ????(????/???? ????) ?????? ???? ????
	//wsprintf( temp1, "[%3d/%d]", m_vecItemInfo.size(), CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1) - 1);	// 2006-06-23 by ispark, -1?? ???? ???????? ???????? ??????.
	// 2009. 12. 17 by jskim ????(????/???? ????) ??????
// 	CHARACTER* pMainInfo = g_pD3dApp->GetMFSMyShuttleInfo();
// 	if(g_pD3dApp->m_pInterface->m_pSelect->m_guiUnitInfo[m_nActTab].CharacterUniqueNumber == pMainInfo->CharacterUniqueNumber)
// 	{
// 		wsprintf( temp1, "[%3d/%d]", m_vecItemInfo.size(), CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, pMainInfo->GetAddedPermanentInventoryCount(ITEM_IN_STORE)) - 1);	// 2006-06-23 by ispark, -1?? ???? ???????? ???????? ??????.
// 	}
	if(g_pD3dApp->m_pInterface->m_pSelect->m_guiUnitInfo[m_nActTab].CharacterUniqueNumber == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber)
	{
		wsprintf( temp1, "[%3d/%d]", m_vecItemInfo.size(), CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, g_pShuttleChild->m_myShuttleInfo.GetAddedPermanentInventoryCount(ITEM_IN_STORE)) - 1);	// 2006-06-23 by ispark, -1?? ???? ???????? ???????? ??????.
	}
	//end 2009. 12. 17 by jskim ????(????/???? ????) ??????
	else
	{
		CHARACTER* pTargetInfo = new CHARACTER;			
		pTargetInfo->RacingPoint = g_pD3dApp->m_pInterface->m_pSelect->m_guiUnitInfo[m_nActTab].RacingPoint;
		wsprintf( temp1, "[%3d/%d]", m_vecItemInfo.size(), CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, pTargetInfo->GetAddedPermanentInventoryCount(ITEM_IN_STORE)) - 1);	// 2006-06-23 by ispark, -1?? ???? ???????? ???????? ??????.
	}	
	//end 2009. 11. 3 by jskim ????(????/???? ????) ?????? ???? ????
	}
	// ????
	else if(m_nActTab == TAB_GUILD)
	{
		wsprintf( temp1, "[%3d/%d]", m_vecItemInfo.size(), COUNT_IN_MEMBERSHIP_GUILDSTORE - 1);
	}
	m_pFontStoreSize->DrawText(STORE_ITEM_COUNT_X,STORE_ITEM_COUNT_Y, GUI_FONT_COLOR, temp1, 0L);

	int nStartIndex =m_pScroll->GetCurrentScrollIndex()*STORE_SLOT_NUMBER_X;
	
	for(i=0;i<STORE_SLOT_NUMBER_Y;i++)
	{
		for(j=0;j<STORE_SLOT_NUMBER_X;j++)
		{
			if(nStartIndex+(i*STORE_SLOT_NUMBER_X)+j >= m_vecItemInfo.size())
			{
				break;
			}
			CItemInfo* pItemInfo = m_vecItemInfo[nStartIndex+(i*STORE_SLOT_NUMBER_X)+j];
//			wsprintf(buf, "%08d", pItemInfo->ItemInfo->ItemNum);	// 2005-08-23 by ispark

			// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

			//wsprintf(buf, "%08d", pItemInfo->ItemInfo->SourceIndex);
			if( !pItemInfo->ShapeItemNum )
				wsprintf(buf, "%08d", pItemInfo->ItemInfo->SourceIndex);
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( pItemInfo->ShapeItemNum );
				if( pShapeItem )
					wsprintf(buf, "%08d", pShapeItem->SourceIndex );
				else
					wsprintf(buf, "%08d", pItemInfo->ItemInfo->SourceIndex);
			}

			// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

			CINFImage* pIcon = g_pGameMain->m_pIcon->FindIcon(buf);
			if(pIcon)
			{
				// 2007-02-12 by bhsohn Item ???? ???? ????				
				BOOL bMultiSel = FALSE;
				if(g_pD3dApp->CheckCityStoreMultItemSel(pItemInfo->UniqueNumber))
				{
					// ???? ?????? ?????? ??????
					bMultiSel = TRUE;
				}
				// end 2007-02-12 by bhsohn Item ???? ???? ????

				// 2007-03-22 by bhsohn ?????? ???? ???? ????
				if(g_pGameMain->IsDoingSkill(pItemInfo->ItemInfo->SourceIndex))
				{
					pIcon->SetScale(1.0f, 1.0f);
				}				
				// end 2007-03-22 by bhsohn ?????? ???? ???? ????

				pIcon->Move(STORE_ICON_START_X+STORE_INTERVAL*j+1, STORE_ICON_START_Y+STORE_INTERVAL*i+1 );
				pIcon->Render();
				
				if( IS_COUNTABLE_ITEM(pItemInfo->Kind) )
				{
					//CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( 
					//	pItemInfo->UniqueNumber );
					if( pItemInfo->CurrentCount > 1 )
					{
						// ?????? ????????.
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn ???? ???? ????
						wsprintf(buf, "%d",pItemInfo->CurrentCount);
						int len = strlen(buf) - 1;			// ?????? ???? ???? ?????????? ?????? -1?? ????.
						m_pFontItemNum->DrawText(STORE_ICON_START_X+STORE_INTERVAL*j + 21 - len*6,	// ?????? 6?? ???? ???? ?????? ????????.,
							STORE_ICON_START_Y+STORE_INTERVAL*i - 1, 
							QSLOT_COUNTERBLE_NUMBER,buf, 0L);
#else
						wsprintf(buf, "%d",pItemInfo->CurrentCount);
						int len = strlen(buf) - 1;			// ?????? ???? ???? ?????????? ?????? -1?? ????.
						m_pFontItemNum->DrawText(STORE_ICON_START_X+STORE_INTERVAL*j + 21 - len*6,	// ?????? 6?? ???? ???? ?????? ????????.,
							STORE_ICON_START_Y+STORE_INTERVAL*i - 1, 
							QSLOT_COUNTERBLE_NUMBER,buf, 0L);
#endif
					}
				}

				// 2010. 02. 11 by ckPark ?????? ??????????
				if( pItemInfo->ItemInfo->InvokingDestParamID
					|| pItemInfo->ItemInfo->InvokingDestParamIDByUse )
				{
					char buf[128];

					if( GetString_CoolTime( pItemInfo, buf ) )
					{
						int len = strlen(buf) - 1;

						int nFontPosX = STORE_ICON_START_X + STORE_INTERVAL * j + 21 - len * 6;
						int nFontPosY = STORE_ICON_START_Y + STORE_INTERVAL * i + 7;

						m_pFontItemNum->DrawText( nFontPosX, nFontPosY, QSLOT_COUNTERBLE_NUMBER, buf, 0L );
					}
				}
				// end 2010. 02. 11 by ckPark ?????? ??????????

				// 2007-02-12 by bhsohn Item ???? ???? ????
				if(bMultiSel)
				{
					float fXPos, fYPos;
					fXPos = STORE_ICON_START_X+STORE_INTERVAL*j+1;
					fYPos = STORE_ICON_START_Y+STORE_INTERVAL*i+1;
					m_pMultiItemSelImage->Move(fXPos, fYPos);
					m_pMultiItemSelImage->Render();
					
				}
				// END 2007-02-12 by bhsohn Item ???? ???? ????
			}
		}
	}
	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityStore::TextReduce(CD3DHanFont *pFont, int nCutPixelX, char* buf)
/// \brief		
/// \author		// 2008-02-21 by bhsohn ???? ?????? ????, ???? ".."???? ????
/// \date		2008-02-21 ~ 2008-02-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::TextReduce(CD3DHanFont *pFont, int nCutPixelX, char* buf)
{
	g_pGameMain->TextReduce(pFont, nCutPixelX, buf);
}

void CINFCityStore::Tick()
{
}

int CINFCityStore::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 2007-12-17 by bhsohn ?????? ?????? ?? ?????? ???? ??????????
	//if(!g_pD3dApp->m_bRequestEnable)
	if(!g_pD3dApp->IsLockMode())
	{// 2006-09-30 by dgwoo ?????? ???? ?????? ???? ???????? ????????.
		return INF_MSGPROC_BREAK;
	}
	if( g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_STORE_PUT_COUNTABLE_ITEM ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_STORE_PUT_ITEM ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_PUT_ITEM_SPI ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_GET_ITEM_SPI ) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_STORE_PUT_ITEM) ||
		g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_STORE_PUSH_ITEM ) ) // 2008-07-23 by bhsohn ???????? ?????? ???? ???? ???? ???????? ???? ???? ???? ?????? ????
	{
		return INF_MSGPROC_NORMAL;
	}
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

			if(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_STORE_POS)
			{
				m_bSelectDown = TRUE;
			}
			if(m_nActTab > SELECT_MODE)
			{
				break;
			}
			//--------------------------------------------------------------------------//
			// ?????? ?????? ?????? ???????? ????????.
			char buf[SIZE_MAX_CHARACTER_NAME] = {0,};
			if(pt.y > STORE_TAB_0_Y &&
				pt.y < STORE_TAB_0_Y + STORE_TAB_H)
			{
				if(0 == g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1)
				{
					if(pt.x > STORE_TAB_0_X &&
						pt.x < STORE_TAB_0_X + STORE_TAB_W)
					{
						wsprintf(buf,"%s",g_pShuttleChild->m_myShuttleInfo.CharacterName);
						g_pGameMain->SetToolTip(pt.x,pt.y,buf);
						return INF_MSGPROC_BREAK;
					}
				}
				else
				{
					if(pt.x > STORE_TAB_0_X &&
						pt.x < STORE_TAB_0_X + STORE_TAB_W)
					{
						wsprintf(buf,"%s",g_pSelect->m_guiUnitInfo[0].CharacterName);
						g_pGameMain->SetToolTip(pt.x,pt.y,buf);
						return INF_MSGPROC_BREAK;
					}
					if(pt.x > STORE_TAB_1_X &&
						pt.x < STORE_TAB_1_X + STORE_TAB_W)
					{
						wsprintf(buf,"%s",g_pSelect->m_guiUnitInfo[1].CharacterName);
						g_pGameMain->SetToolTip(pt.x,pt.y,buf);
						return INF_MSGPROC_BREAK;
					}
					if(pt.x > STORE_TAB_2_X &&
						pt.x < STORE_TAB_2_X + STORE_TAB_W)
					{
						wsprintf(buf,"%s",g_pSelect->m_guiUnitInfo[2].CharacterName);
						g_pGameMain->SetToolTip(pt.x,pt.y,buf);
						return INF_MSGPROC_BREAK;
					}
				}
			}
			

			
			//--------------------------------------------------------------------------//

			///////////////////////////////////////////////////////////////////////////
			// ???? 
			if( pt.x > STORE_ICON_START_X &&
				pt.x < STORE_ICON_START_X+STORE_INTERVAL*STORE_SLOT_NUMBER_X &&
				pt.y > STORE_ICON_START_Y &&
				pt.y < STORE_ICON_START_Y+STORE_INTERVAL*STORE_SLOT_NUMBER_Y)
			{
				int selectIndex = (pt.y - STORE_ICON_START_Y) / STORE_INTERVAL;
				int selectIndexwidth = (pt.x - STORE_ICON_START_X) / STORE_INTERVAL;
				int remain = (pt.y - STORE_ICON_START_Y) % STORE_INTERVAL;
				int remainwidth = (pt.x - STORE_ICON_START_X) % STORE_INTERVAL;
				
				if( selectIndex >= 0 && 
					remain < STORE_ICON_SIZE &&
					selectIndexwidth >= 0 &&
					remainwidth < STORE_ICON_SIZE)
				{
					int index = m_pScroll->GetCurrentScrollIndex()*STORE_SLOT_NUMBER_X;
					if( index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth < m_vecItemInfo.size() )
					{//???????? ???? ??.
						CItemInfo* pItemInfo = m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth];
						
						// 2009-02-03 by bhsohn ???? ?????? ???? ????
						//g_pGameMain->m_pItemInfo->SetItemInfoUser( pItemInfo, pt.x, pt.y );						
						g_pGameMain->SetItemInfoUser( pItemInfo, pt.x, pt.y );						
						// end 2009-02-03 by bhsohn ???? ?????? ???? ????
						//m_pItemInfoDrag = m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER)+selectIndexwidth];
					}
					else
					{
						// 2009-02-03 by bhsohn ???? ?????? ???? ????
						//g_pGameMain->m_pItemInfo->SetItemInfoUser( NULL, 0 , 0 );
						g_pGameMain->SetItemInfoUser( NULL, 0 , 0 );
						// end 2009-02-03 by bhsohn ???? ?????? ???? ????
					}
				}
				else
				{
					// 2009-02-03 by bhsohn ???? ?????? ???? ????
					//g_pGameMain->m_pItemInfo->SetItemInfoUser( NULL, 0 , 0 );
					g_pGameMain->SetItemInfoUser( NULL, 0 , 0 );
					// end 2009-02-03 by bhsohn ???? ?????? ???? ????
				}
			}
			else/*
			 if(pt.x > STORE_ICON_START_X+STORE_ICON_SIZE &&
								pt.x < STORE_START_X+STORE_SIZE_X &&
								pt.y > STORE_ICON_START_Y+STORE_ICON_SIZE &&
								pt.y < STORE_START_Y+STORE_SIZE_Y )*/			
			{
				// 2009-02-03 by bhsohn ???? ?????? ???? ????
				//g_pGameMain->m_pItemInfo->SetItemInfoUser( NULL, 0 , 0 );
				g_pGameMain->SetItemInfoUser( NULL, 0 , 0 );
				// end 2009-02-03 by bhsohn ???? ?????? ???? ????
			}
			//
			////////////////////////////////////////////////////////////////////////////////
		}
		break;


	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_STORE_POS)
			{
				m_bSelectDown = TRUE;
			}

			// 2008-08-22 by bhsohn EP3 ???????? ????
//			if( pt.x > INVEN_SPI_START_X &&
//				pt.x < INVEN_SPI_START_X+INVEN_SPI_SIZE_X &&
//				pt.y > INVEN_SPI_START_Y &&
//				pt.y < INVEN_SPI_START_Y+INVEN_SPI_SIZE_Y &&
//				g_pGameMain->m_pInfWindow->IsExistMsgBox(_Q_PUT_ITEM_SPI) == FALSE &&
//				g_pGameMain->m_pInven->GetItemSpi()>STORE_KEEPING_COST)
//			{
//				char buf[256];
//				wsprintf( buf, STRMSG_C_STORE_0001, STORE_KEEPING_COST);//"?????? ???????????????[???? : %d ????]"
//				g_pGameMain->m_pInfWindow->AddMsgBox(
//					buf, _Q_PUT_ITEM_SPI, 0, g_pGameMain->m_pInven->GetItemSpi()-STORE_KEEPING_COST);
//				return INF_MSGPROC_BREAK;
//			}
			// end 2008-08-22 by bhsohn EP3 ???????? ????
			if( pt.x > STORE_SPI_TEXT_X &&
				pt.x < STORE_SPI_TEXT_X+STORE_SPI_TEXT_W &&
				pt.y > STORE_SPI_TEXT_Y &&
				pt.y < STORE_SPI_TEXT_Y+STORE_SPI_TEXT_H &&
				GetItemSpi() > 0 &&
				g_pGameMain->m_pInfWindow->IsExistMsgBox(_Q_GET_ITEM_SPI) == FALSE)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(
					STRMSG_C_STORE_0002, _Q_GET_ITEM_SPI, 0, GetItemSpi());//"?????? ???????????????"
				return INF_MSGPROC_BREAK;
			}
			// ???? ?? ???? ?????? ??????????.
			if(pt.y > STORE_TAB_0_Y &&
				pt.y < STORE_TAB_0_Y + STORE_TAB_H)
			{
				if(pt.x > STORE_TAB_0_X &&
					pt.x < STORE_TAB_0_X + STORE_TAB_W)
				{
					ChangeTab(0);
				}
				if(pt.x > STORE_TAB_1_X &&
					pt.x < STORE_TAB_1_X + STORE_TAB_W)
				{
					ChangeTab(1);
				}
				if(pt.x > STORE_TAB_2_X &&
					pt.x < STORE_TAB_2_X + STORE_TAB_W)
				{
					ChangeTab(2);
				}
			}
			// ???? ???? ???? ?????? ??????????.
			if(pt.y > STORE_TAB_1_Y &&
				pt.y < STORE_TAB_1_Y + STORE_TAB_H)
			{
				if(pt.x > STORE_TAB_3_X &&
					pt.x < STORE_TAB_3_X + STORE_TAB_W)
				{
					ChangeTab(STORE_TAB_GUILD);
				}
				if(pt.x > STORE_TAB_4_X &&
					pt.x < STORE_TAB_4_X + STORE_TAB_W)
				{
					ChangeTab(STORE_TAB_GUILD_LOG);
				}

			}

			// 2007-03-02 by bhsohn ???? ???? ???? ????
			BOOL bPopup = FALSE;

			// ?????? ????
			if( pt.x > STORE_ICON_START_X &&
				pt.x < STORE_ICON_START_X+STORE_INTERVAL*STORE_SLOT_NUMBER_X &&
				pt.y > STORE_ICON_START_Y &&
				pt.y < STORE_ICON_START_Y+STORE_INTERVAL*STORE_SLOT_NUMBER_Y &&
				m_nActTab <= SELECT_MODE)
			{
				int selectIndex = (pt.y - STORE_ICON_START_Y) / STORE_INTERVAL;
				int selectIndexwidth = (pt.x - STORE_ICON_START_X) / STORE_INTERVAL;
				int remain = (pt.y - STORE_ICON_START_Y) % STORE_INTERVAL;
				int remainwidth = (pt.x - STORE_ICON_START_X) % STORE_INTERVAL;
				
				if( selectIndex >= 0 && 
					remain < STORE_ICON_SIZE &&
					selectIndexwidth >= 0 &&
					remainwidth < STORE_ICON_SIZE)
				{
					int index = m_pScroll->GetCurrentScrollIndex()*STORE_SLOT_NUMBER_X;
					if( index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth < m_vecItemInfo.size() )
					{
						m_nRenderMoveIconIntervalHeight = pt.y - (STORE_ICON_START_Y + (selectIndex * STORE_INTERVAL));
						m_nRenderMoveIconIntervalWidth = pt.x - (STORE_ICON_START_X + (selectIndexwidth * STORE_INTERVAL));	

//						g_pGameMain->m_nIconPosX  = (STORE_ICON_SIZE/2);
//						g_pGameMain->m_nIconPosY  = (STORE_ICON_SIZE/2);

// 2006-07-27 by ispark
//						m_pItemInfo = m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER)+selectIndexwidth];
//						char buf[16];
////						wsprintf(buf, "%08d", m_pItemInfo->ItemInfo->ItemNum);			// 2005-08-23 by ispark
//						wsprintf(buf, "%08d", m_pItemInfo->ItemInfo->SourceIndex);
//						g_pGameMain->m_pSelectIcon = ((CINFGameMain*)m_pParent)->m_pIcon->FindIcon(buf);
						
						// 2007-02-12 by bhsohn Item ???? ???? ????
						// SetSelectItem(m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth]);
						BOOL bMuitiItemSel = FALSE;						
						if(g_pD3dApp->GetCtrlBtnClick())
						{							
							bMuitiItemSel = TRUE;						
						}						
						
						if(!bMuitiItemSel)
						{
							// 2007-03-02 by bhsohn ???? ???? ???? ????
							BOOL bMultiDragSel = FALSE;
							
							// ???? ???????? ?? ?????????
							if(g_pD3dApp->CheckCityStoreMultItemSel(m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth]->UniqueNumber))
							{
								bMultiDragSel = TRUE;
							}
							if(!bMultiDragSel)
							{
							SetMultiSelectCityStoreItem(NULL);	// ???? ???? ????
							}
							// end 2007-03-02 by bhsohn ???? ???? ???? ????
						SetSelectItem(m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth]);
						}						
						else
						{
							SetMultiSelectCityStoreItem(m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth]);
						}												
						// ???? ????
						bPopup = TRUE;
						// end 2007-02-12 by bhsohn Item ???? ???? ????
						return INF_MSGPROC_BREAK;
					}
					else
					{
//						g_pGameMain->m_pSelectIcon = NULL;
					}
				}
				else
				{
					SetSelectItem(NULL);
//					g_pGameMain->m_pSelectIcon = NULL;
				}
			}
			if(!bPopup)
			{
//				g_pGameMain->m_pSelectIcon = NULL;
				// 2007-03-02 by bhsohn ???? ???? ???? ????
				// ?????? ?????? ???????? ????. 
				int nStoreMultiItem = ((CINFGameMain*)m_pParent)->GetCityStoreMultiSelectItem();
				if(nStoreMultiItem > 0)
				{
					SetMultiSelectCityStoreItem(NULL);
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
			if(m_nActTab > SELECT_MODE)
			{// 2006-10-17 by dgwoo ???? ?????????? ?????? ???????? ?????????? ??????.
				break;
			}
			
			// 2008-08-22 by bhsohn EP3 ???????? ????
			// ?????? ?????? ??????
			// ???? -> ????????
//			if(m_bSelectDown &&
//				((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
//				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_STORE_POS)
//			{					
//				if( pt.x>INVEN_START_X && 
//					pt.x<INVEN_START_X + 94 &&
//					pt.y > INVEN_START_Y &&
//					pt.y < INVEN_START_Y + 200)
//					
//				{
//					CItemInfo* pItemInfo = (CItemInfo*)((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem->pItem;
//
//					// 2007-03-02 by bhsohn ???? ???? ???? ????
//					int nStoreMultiItem = ((CINFGameMain*)m_pParent)->GetCityStoreMultiSelectItem();
//					if(nStoreMultiItem <= 0)
//					{
//					if(IS_COUNTABLE_ITEM(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem->pItem->Kind))
//					{
//						char buf[256];
//						wsprintf( buf, STRMSG_C_STORE_0003, pItemInfo->ItemInfo->ItemName);//"%s ?????? ???????? ???????????????"
//						g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_STORE_PUSH_ITEM,
//								(DWORD)pItemInfo,pItemInfo->CurrentCount);
//					}
//					else
//					{
//						FieldSocketSendItemToCharacter( pItemInfo->UniqueNumber, 1 );
//					}
//					}
//					else
//					{
//						((CINFGameMain*)m_pParent)->PopupStoreMultiItemSelect();
//					}
//					// end 2007-03-02 by bhsohn ???? ???? ???? ????								
//
//					SetSelectItem(NULL);
//					m_bSelectDown = FALSE;
//				}
//				else
//				{
//					SetSelectItem(NULL);
//					m_bSelectDown = FALSE;
//				}
//			}
			// end 2008-08-22 by bhsohn EP3 ???????? ????
			g_pGameMain->m_pSelectIcon = NULL;
			m_pItemInfo = NULL;

			
			
			// ???????? -> ????
//			if( g_pGameMain->m_pInven->m_pSelectItem &&
			if(	((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_INVEN_POS &&
				pt.x > STORE_START_X && 
				pt.x < STORE_START_X+STORE_START_W &&
				pt.y > STORE_START_Y &&
				pt.y < STORE_START_Y+STORE_START_H)
			{
				CItemInfo* pItemInfo = (CItemInfo*)((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem->pItem;

				// 2007-03-02 by bhsohn ???? ???? ???? ????
				int nInvenMultiItem = g_pD3dApp->GetMultiSelectItem();				
				
				// ???? ?????? ?????? ???????? ?????
				if(nInvenMultiItem <= 0)				
				{					
				if(pItemInfo->Wear == WEAR_NOT_ATTACHED )
				{
					char buf[256];
					ITEM *pITEM = pItemInfo->GetItemInfo();
					if(pITEM)
					{
						if( IS_COUNTABLE_ITEM(pItemInfo->Kind))
						{
//							if(g_pGameMain->m_pInven->m_pSelectItem->Kind == ITEMKIND_ENERGY)
//							{
//								g_pD3dApp->m_pChat->CreateChatChild("?????????? ?????? ???? ?? ????????.",COLOR_ERROR);
//								return INF_MSGPROC_NORMAL;
//							}
							wsprintf( buf, STRMSG_C_STORE_0004, pITEM->ItemName, STORE_KEEPING_COST);//"%s ?????? ???????????????[????:%d(????)]"
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_STORE_PUT_COUNTABLE_ITEM,
								(DWORD)pItemInfo,
								pItemInfo->CurrentCount);
						}
						else
						{
							wsprintf( buf, STRMSG_C_STORE_0005, pITEM->ItemName, STORE_KEEPING_COST);//"%s ?? ???????????????[????:%d(????)]"
							g_pGameMain->m_pInfWindow->AddMsgBox(buf, _Q_STORE_PUT_ITEM,
								(DWORD)pItemInfo);
						}
					}
				}
				else
				{
					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_STORE_0006, _MESSAGE );//"?????? ???????? ???? ?? ????????."
				}
				}
				else
				{
					// ?????? ???? ???????? ?????? ???? 
					((CINFGameMain*)m_pParent)->PopupMultiItemSelect();				
					
					// 2008-11-13 by bhsohn EP3-2 ???? ???? ???? ???? ?????? ???? ????
					SetSelectItem(NULL);
					m_bSelectDown = FALSE;
					g_pGameMain->ClearSetIconInfo();
					return INF_MSGPROC_BREAK;
					// end 2008-11-13 by bhsohn EP3-2 ???? ???? ???? ???? ?????? ???? ????
				}
				// end 2007-03-02 by bhsohn ???? ???? ???? ????
				SetSelectItem(NULL);
				m_bSelectDown = FALSE;
			}
		}
		break;
	case WM_CHAR:
		{
		

		}
		break;
		// 2007-02-12 by bhsohn Item ???? ???? ????
	case WM_RBUTTONDOWN:
		{
			BOOL bPopup = FALSE;
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if( pt.x > STORE_ICON_START_X &&
				pt.x < STORE_ICON_START_X+STORE_INTERVAL*STORE_SLOT_NUMBER_X &&
				pt.y > STORE_ICON_START_Y &&
				pt.y < STORE_ICON_START_Y+STORE_INTERVAL*STORE_SLOT_NUMBER_Y &&
				m_nActTab <= SELECT_MODE)
			{
				int selectIndex = (pt.y - STORE_ICON_START_Y) / STORE_INTERVAL;
				int selectIndexwidth = (pt.x - STORE_ICON_START_X) / STORE_INTERVAL;
				int remain = (pt.y - STORE_ICON_START_Y) % STORE_INTERVAL;
				int remainwidth = (pt.x - STORE_ICON_START_X) % STORE_INTERVAL;
				if( selectIndex >= 0 && 
					remain < STORE_ICON_SIZE &&
					selectIndexwidth >= 0 &&
					remainwidth < STORE_ICON_SIZE)
				{					
					int index = m_pScroll->GetCurrentScrollIndex()*STORE_SLOT_NUMBER_X;
					if( index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth < m_vecItemInfo.size() )
					{
						// ???? ???????? ?? ?????????
						if(g_pD3dApp->CheckCityStoreMultItemSel(m_vecItemInfo[index+(selectIndex*STORE_SLOT_NUMBER_X)+selectIndexwidth]->UniqueNumber))
						{							
			int nStoreMultiItem = ((CINFGameMain*)m_pParent)->GetCityStoreMultiSelectItem();
			if(nStoreMultiItem > 0)
			{
								bPopup = TRUE;
				((CINFGameMain*)m_pParent)->PopupStoreMultiItemSelect();
							}							
						}						
					}					
				}
			}
			if(!bPopup)
			{
				int nStoreMultiItem = ((CINFGameMain*)m_pParent)->GetCityStoreMultiSelectItem();
				if(nStoreMultiItem > 0)
				{
					SetMultiSelectCityStoreItem(NULL);	// ???? ???? ????
				}				
			}
			else
			{
				return INF_MSGPROC_BREAK;
			}
		}
		break;
		// end 2007-02-12 by bhsohn Item ???? ???? ????
	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CINFCityStore::OnButtonClicked(int nButton)
/// \brief		0 : ok, 1 : cancel
/// \author		dhkwon
/// \date		2004-07-14 ~ 2004-07-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::OnButtonClicked(int nButton)
{
//	if(nButton == 0) // OK
//	{
//		for(int i=0;i<m_vecItemInfo.size();i++)
//		{
//			if(m_pnSelectCurrentCount[i] > 0)
//			{
//				FieldSocketSendItemToCharacter(m_vecItemInfo[i]->UniqueNumber, m_pnSelectCurrentCount[i]);
//			}
//		}
//		memset(m_pnSelectCurrentCount, 0x00, sizeof(int)*m_vecItemInfo.size() );
//	}
//	else if(nButton == 1) // CANCEL
//	{
//		memset(m_pnSelectCurrentCount, 0x00, sizeof(int)*m_vecItemInfo.size() );
//	}
//	else if(nButton == 2) //  GET
//	{
//		int index = m_pScroll->GetCurrentSelectDataIndex();
//		if( index >=0 &&
//			index < m_vecItemInfo.size() )
//		{
//			FieldSocketSendItemToCharacter(m_vecItemInfo[index]->UniqueNumber, m_pnSelectCurrentCount[index]);
//		}
//	}
}

CItemInfo* CINFCityStore::FindItemInfo( UID64_t nUniqueNumber )
{
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end())
	{
		if((*it)->UniqueNumber == nUniqueNumber)
		{
			return *it;
		}
		it++;
	}
	return NULL;
}

struct CompareKindStore
{
	template<typename T>
		bool operator()(const T *pPtr1, const T *pPtr2)
	{
		ITEM* pITEM1 = g_pDatabase->GetServerItemInfo(pPtr1->ItemNum);
		ITEM* pITEM2 = g_pDatabase->GetServerItemInfo(pPtr2->ItemNum);
		if( pITEM1 == NULL || pITEM2 == NULL )
		{
			return false;
		}
		if(pITEM1->Kind < pITEM2->Kind)
		{
			return true;
		}
		else if(pITEM1->Kind == pITEM2->Kind)
		{
			if(pITEM1->ReqMinLevel < pITEM2->ReqMinLevel)
			{
				return true;
			}
			else if(pITEM1->ReqMinLevel == pITEM2->ReqMinLevel)
			{
				if(pITEM1->ItemNum < pITEM2->ItemNum)
				{
					return true;
				}
			}
		}
		return false;
	}
};

void CINFCityStore::StoreItemSort()
{
	sort(m_vecItemInfo.begin(), m_vecItemInfo.end(), CompareKindStore());
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityStore::SetSelectItem(CItemInfo* pItemInfo)
/// \brief		
/// \author		ispark
/// \date		2006-07-27 ~ 2006-07-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::SetSelectItem(CItemInfo* pItemInfo)
{
	POINT ptIcon;
	ptIcon.x = m_nRenderMoveIconIntervalWidth;
	ptIcon.y = m_nRenderMoveIconIntervalHeight;
	m_pSelectItem.pItem = NULL;

	if(pItemInfo)
	{
		char buf[16];

		// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????
		//wsprintf(buf, "%08d", pItemInfo->ItemInfo->SourceIndex);
		ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( pItemInfo->GetShapeItemNum() );

		int tempSourceIndex = NULL;
		if( pShapeItem )
		{
			tempSourceIndex = pShapeItem->SourceIndex;
		}
		else
		{
			tempSourceIndex = pItemInfo->ItemInfo->SourceIndex;
		}

		wsprintf(buf, "%08d", tempSourceIndex );
		// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

		m_pSelectItem.pItem = pItemInfo;

		strcpy(m_pSelectItem.IconName, buf);
		strcpy(m_pSelectItem.Name, pItemInfo->ItemInfo->ItemName);

		((CINFGameMain*)m_pParent)->SetSelectItem(&m_pSelectItem, ptIcon, ITEM_STORE_POS);
	}
	else
	{
		((CINFGameMain*)m_pParent)->SetSelectItem(NULL, ptIcon, ITEM_STORE_POS);
	}	
}
	
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityStore::RenderNormal()
/// \brief		???? ???? ????
/// \author		ispark
/// \date		2006-10-17 ~ 2006-10-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::RenderNormal()
{
	char buf[64];
	
	m_pBack_Normal->Render();

	//???? ?????? ??????.
	// 2006-10-17 by ispark, ?????? ????
	wsprintf(buf ,"%s",g_pSelect->m_guiUnitInfo[m_nActTab].CharacterName);
	// 2008-02-21 by bhsohn ???? ?????? ????, ???? ".."???? ????
	TextReduce(m_pFontUserName[0], 60, buf);
	//TextReduce(10,buf);
	if(buf)
		m_pFontUserName[0]->DrawText(STORE_TAB_0_X+1,STORE_TAB_0_Y,GUI_FONT_COLOR,buf,0L);	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityStore::RenderMemberShip()
/// \brief		?????? ???? ????
/// \author		ispark
/// \date		2006-10-17 ~ 2006-10-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::RenderMemberShip()
{
	char buf[64];

	m_pBack[m_nActTab]->Render();

	wsprintf(buf ,"%s",g_pSelect->m_guiUnitInfo[0].CharacterName);
	// 2008-02-21 by bhsohn ???? ?????? ????, ???? ".."???? ????
	TextReduce(m_pFontUserName[0], 60, buf);
	//TextReduce(10,buf);
	if(buf)
		m_pFontUserName[0]->DrawText(STORE_TAB_0_X+1,STORE_TAB_0_Y,(m_nActTab == TAB_CHARACTER_1)?GUI_FONT_COLOR:GUI_FONT_COLOR_G,buf,0L);

	wsprintf(buf ,"%s",g_pSelect->m_guiUnitInfo[1].CharacterName);	
	// 2008-02-21 by bhsohn ???? ?????? ????, ???? ".."???? ????
	TextReduce(m_pFontUserName[1], 60, buf);
	//TextReduce(10,buf);
	if(buf)
		m_pFontUserName[1]->DrawText(STORE_TAB_1_X+1,STORE_TAB_0_Y,(m_nActTab == TAB_CHARACTER_2)?GUI_FONT_COLOR:GUI_FONT_COLOR_G,buf,0L);
	wsprintf(buf ,"%s",g_pSelect->m_guiUnitInfo[2].CharacterName);
	// 2008-02-21 by bhsohn ???? ?????? ????, ???? ".."???? ????
	TextReduce(m_pFontUserName[2], 60, buf);
	//TextReduce(10,buf);
	if(buf)
		m_pFontUserName[2]->DrawText(STORE_TAB_2_X+1,STORE_TAB_0_Y,(m_nActTab == TAB_CHARACTER_3)?GUI_FONT_COLOR:GUI_FONT_COLOR_G,buf,0L);
	wsprintf(buf ,STRMSG_C_060920_0100);
	if(buf)
		m_pFontUserName[3]->DrawText(STORE_TAB_3_X+9,STORE_TAB_1_Y,(m_nActTab == TAB_GUILD)?GUI_FONT_COLOR:GUI_FONT_COLOR_G,buf,0L);
	wsprintf(buf ,STRMSG_C_060920_0101);
	if(buf)
		m_pFontUserName[4]->DrawText(STORE_TAB_4_X+5,STORE_TAB_1_Y,(m_nActTab == TAB_GUILD_LOG)?GUI_FONT_COLOR:GUI_FONT_COLOR_G,buf,0L);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityStore::RenderNormalYedang()
/// \brief		?????? ?????????? ?????? ???? ?????? ????????????.
/// \author		dgwoo
/// \date		2007-10-10 ~ 2007-10-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::RenderNormalYedang()
{
	char buf[64];
	if(STORE_TAB_GUILD > m_nActTab)
	{
		if(m_pBack_NormalYedang[0])
		{
			m_pBack_NormalYedang[0]->Render();
		}
	}
	else
	{
		if(m_pBack_NormalYedang[m_nActTab])
		{
			m_pBack_NormalYedang[m_nActTab]->Render();
		}
	}

		
	//wsprintf(buf ,"%s",g_pSelect->m_guiUnitInfo[0].CharacterName);
	wsprintf(buf ,"%s",g_pShuttleChild->m_myShuttleInfo.CharacterName);
	
	// 2008-02-21 by bhsohn ???? ?????? ????, ???? ".."???? ????
	TextReduce(m_pFontUserName[0], 60, buf);
	//TextReduce(10,buf);
	if(buf)
		m_pFontUserName[0]->DrawText(STORE_TAB_0_X+1,STORE_TAB_0_Y,GUI_FONT_COLOR,buf,0L);	
	wsprintf(buf ,STRMSG_C_060920_0100);
	if(buf)
		m_pFontUserName[3]->DrawText(STORE_TAB_3_X+9,STORE_TAB_1_Y,(m_nActTab == TAB_GUILD)?GUI_FONT_COLOR:GUI_FONT_COLOR_G,buf,0L);
	wsprintf(buf ,STRMSG_C_060920_0101);
	if(buf)
		m_pFontUserName[4]->DrawText(STORE_TAB_4_X+5,STORE_TAB_1_Y,(m_nActTab == TAB_GUILD_LOG)?GUI_FONT_COLOR:GUI_FONT_COLOR_G,buf,0L);
}



///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		???? ????
/// \author		bhsohn
/// \date		2007-02-21 ~ 2007-02-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityStore::SetMultiSelectCityStoreItem(CItemInfo* pItemInfo)
{			
	POINT ptIcon;
	ptIcon.x = m_nRenderMoveIconIntervalWidth;
	ptIcon.y = m_nRenderMoveIconIntervalHeight;

	if(pItemInfo)
	{
		char buf[16];

		// 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

		//wsprintf(buf, "%08d", pItemInfo->ItemInfo->SourceIndex);
		ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( pItemInfo->GetShapeItemNum() );

		int tempSourceIndex = NULL;
		if( pShapeItem )
		{
			tempSourceIndex = pShapeItem->SourceIndex;
		}
		else
		{
			tempSourceIndex = pItemInfo->ItemInfo->SourceIndex;
		}
		wsprintf(buf, "%08d", tempSourceIndex );
		// end 2009. 08. 27 by ckPark ?????? ?????? ???? ?????? ????

		m_pSelectItem.pItem = pItemInfo;
		
		strcpy(m_pSelectItem.IconName, buf);
		strcpy(m_pSelectItem.Name, pItemInfo->ItemInfo->ItemName);		
	((CINFGameMain*)m_pParent)->SetMultiSelectCityStoreItem(pItemInfo, 
			((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem,
			ptIcon,
			&m_pSelectItem);			
	}
	else
	{
		((CINFGameMain*)m_pParent)->SetMultiSelectCityStoreItem(pItemInfo, 
			((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem,
			ptIcon,
			NULL);	
	}
	
}




///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		???? ?????? ???????? ???????? ???? ?????? ????????.
/// \author		bhsohn
/// \date		2007-02-22 ~ 2007-02-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityStore::GetStoreFreeSize()
{
	int nFreeSize = 0;
	int nItemSize = m_vecItemInfo.size();
	int nMaxStoreSize = 0;
	if(m_nActTab >= TAB_CHARACTER_1 && m_nActTab <= TAB_CHARACTER_3)
	{	
		// 2009. 11. 3 by jskim ????(????/???? ????) ?????? ???? ????
		//nFreeSize = (CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1) - 1) - nItemSize;		
		// 2009. 12. 17 by jskim ????(????/???? ????) ?????? 
// 		CHARACTER* pMainInfo = g_pD3dApp->GetMFSMyShuttleInfo();	
// 		if(g_pD3dApp->m_pInterface->m_pSelect->m_guiUnitInfo[m_nActTab].CharacterUniqueNumber == pMainInfo->CharacterUniqueNumber)
// 		{
// 			nFreeSize = (CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, pMainInfo->GetAddedPermanentInventoryCount(ITEM_IN_STORE)) - 1) - nItemSize;		
// 		}
		if(g_pD3dApp->m_pInterface->m_pSelect->m_guiUnitInfo[m_nActTab].CharacterUniqueNumber == g_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber)
		{
			nFreeSize = (CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, g_pShuttleChild->m_myShuttleInfo.GetAddedPermanentInventoryCount(ITEM_IN_STORE)) - 1) - nItemSize;		
		}
		//end 2009. 12. 17 by jskim ????(????/???? ????) ?????? 
		else
		{
			CHARACTER* pTargetInfo = new CHARACTER;			
			pTargetInfo->RacingPoint = g_pD3dApp->m_pInterface->m_pSelect->m_guiUnitInfo[m_nActTab].RacingPoint;
			nFreeSize = (CAtumSJ::GetMaxStoreSize((BOOL)g_pD3dApp->GetPrimiumCardInfo()->nCardItemNum1, pTargetInfo->GetAddedPermanentInventoryCount(ITEM_IN_STORE)) - 1) - nItemSize;		
		}
		// 2009. 11. 3 by jskim ????(????/???? ????) ?????? ???? ????
	}
	// ????
	else if(m_nActTab == TAB_GUILD)
	{		
		nFreeSize = (COUNT_IN_MEMBERSHIP_GUILDSTORE - 1) - nItemSize;		
	}

	return nFreeSize;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL IsItemAddStror(UID64_t		nUniqueNumber)
/// \brief		???? ???????? ??????????.
/// \author		// 2007-03-09 by bhsohn ???? ???? ???? ???? ????
/// \date		2007-03-09 ~ 2007-03-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityStore::IsStoreHave(int nItemNum)
{
	BOOL bHave = FALSE;
	
	CVectorItemInfoIterator it = m_vecItemInfo.begin();
	while(it != m_vecItemInfo.end() )
	{
		if(  nItemNum == (*it)->ItemNum)
		{
			bHave = TRUE;
			break;
		}
		it++;
	}
	return bHave;
	
}