// AllGuildItemManager.cpp: implementation of the CAllGuildItemManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumError.h"
#include "FieldIOCP.h"
#include "GuildItemManager.h"
#include "AllGuildItemManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAllGuildItemManager::CAllGuildItemManager()
{

}

CAllGuildItemManager::~CAllGuildItemManager()
{

}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		cmkwon
/// \date		2006-09-25 ~ 2006-09-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
mtmapAllGuildItem *CAllGuildItemManager::GetmtmapAllGuildItemPtr(void)
{
	return &m_mtmapAllGuildItem;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CGuildItemManager *CAllGuildItemManager::GetGuildItemMangerNoLock(UID32_t i_GuildUID)
/// \brief		
/// \author		cmkwon
/// \date		2006-09-25 ~ 2006-09-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CGuildItemManager *CAllGuildItemManager::GetGuildItemMangerNoLock(UID32_t i_GuildUID)
{
	mtmapAllGuildItem::iterator itrmap = m_mtmapAllGuildItem.find(i_GuildUID);
	if (itrmap == m_mtmapAllGuildItem.end())
	{
		return NULL;
	}

	
	return itrmap->second;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAllGuildItemManager::InsertGuildItemManagerNoLock(CGuildItemManager *i_pGuildManager)
/// \brief		
/// \author		cmkwon
/// \date		2006-09-25 ~ 2006-09-25
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAllGuildItemManager::InsertGuildItemManagerNoLock(CGuildItemManager *i_pGuildManager)
{

	m_mtmapAllGuildItem.insert(pair<UID32_t, CGuildItemManager*>(i_pGuildManager->GetGuildUID(), i_pGuildManager));
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAllGuildItemManager::OnDoHourlyWorkAllGuildItemManager(ATUM_DATE_TIME *pDateTime)
/// \brief		
/// \author		dhjin
/// \date		2006-09-28 ~ 2006-09-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAllGuildItemManager::OnDoHourlyWorkAllGuildItemManager(ATUM_DATE_TIME *pDateTime)
{
	mt_auto_lock mta(&m_mtmapAllGuildItem);

	DWORD dwTime	= timeGetTime();
	mtmapAllGuildItem::iterator itrmap = m_mtmapAllGuildItem.begin();
	while(itrmap != m_mtmapAllGuildItem.end())
	{
		CGuildItemManager *pGuildItemMan = itrmap->second;
		if (3600000 < (dwTime - pGuildItemMan->GetReqLoadLastTick()))
		{
			pGuildItemMan->ResetGuildItemManager();
			m_mtmapAllGuildItem.erase(itrmap++);
			SAFE_DELETE(pGuildItemMan);
			continue;
		}

		itrmap++;
	}

}



