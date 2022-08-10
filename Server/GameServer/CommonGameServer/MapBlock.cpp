#include "stdafx.h"
#include "MapBlock.h"
#include "MapChannel.h"

int CMapBlock::ms_nSIZE_BLOCK = 0;

CMapBlock::CMapBlock()
{
}

CMapBlock::~CMapBlock()
{
}

// 2010-04-09 by cmkwon, 인피2차 추가 수정(단계별 보상 추가) - 
DROPITEM* CMapBlock::GetDROPITEM_SetProcess(ITEM_GENERAL* pStoreItem, BOOL i_bPickupTenderItem/*=FALSE*/)
{
	m_DropItemMtmap.lock();
	mtmapDropItem::iterator itr = m_DropItemMtmap.find(pStoreItem);
	if (itr != m_DropItemMtmap.end())
	{
		DROPITEM *pDropItem = &itr->second;
		if (FALSE == pDropItem->bProcessing
			&& (i_bPickupTenderItem || FALSE == pDropItem->bTendering))	// 2010-04-09 by cmkwon, 인피2차 추가 수정(단계별 보상 추가) - 
		{
			pDropItem->bProcessing = TRUE;
		}
		else
		{
			pDropItem = NULL;
		}
		m_DropItemMtmap.unlock();
		return pDropItem;
	}
	m_DropItemMtmap.unlock();

	return NULL;
}

void CMapBlock::AllDeleteDropItem(void)
{
	// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 
	mt_auto_lock mtA(&m_DropItemMtmap);
	mtmapDropItem::iterator itr = m_DropItemMtmap.begin();
	for(; itr!=m_DropItemMtmap.end(); itr++)
	{
		DROPITEM *pDropItem = &itr->second;
		SAFE_DELETE(pDropItem->pItem);
	}
	m_DropItemMtmap.clear();
}