// AtumDatabase.cpp: implementation of the CAtumDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "AtumDatabase.h"
#include "AtumApplication.h"
#include "SceneData.h"
#include "FieldWinSocket.h"
#include "INFImage.h"
#include "INFItemInfo.h"

// 2007-11-22 by bhsohn 아레나 통합서버
#include "IMSocketManager.h"
//#include "IMSocket.h"

#include "MonsterData.h"
#include "dxutil.h"

#define GUILD_POINTER_SIZE		8	// loading시에 struct에서 제외할 사이즈

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAtumDatabase::CAtumDatabase()
{
	FLOG("CAtumDatabase::CAtumDatabase()");
	g_pDatabase = this;

	// 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기
	memset(&m_DefMapInfo, 0, sizeof(MAP_INFO));
	// end 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기
}

CAtumDatabase::~CAtumDatabase()
{
	FLOG("CAtumDatabase::~CAtumDatabase()");
	g_pDatabase = NULL;


	// 2005-02-04 by jschoi - 메모리 누수
	CVectorMixingInfoIterator it = m_VecMixingInfo.begin();
	while(it != m_VecMixingInfo.end())
	{
		SAFE_DELETE(*it);
		it++;
	}
	m_VecMixingInfo.clear();

	CMapGuildMarkIterator itGuildMark = m_mapGuildMark.begin();
	while(itGuildMark != m_mapGuildMark.end())
	{
		SAFE_DELETE(itGuildMark->second->pImage);
		SAFE_DELETE(itGuildMark->second->pData);
		SAFE_DELETE(itGuildMark->second);
		itGuildMark++;
	}
	m_mapGuildMark.clear();

	CMapMapInfoIterator itMapInfo = m_mapMapInfo.begin();
	while(itMapInfo != m_mapMapInfo.end())
	{
		SAFE_DELETE(itMapInfo->second);
		itMapInfo++;
	}
	m_mapMapInfo.clear();

	CVectorMysteryItemDropIterator itMystery = m_VecMysteryItem.begin();
	while(itMystery != m_VecMysteryItem.end())
	{
		SAFE_DELETE(*itMystery);
		itMystery++;
	}
	m_VecMysteryItem.clear();

	// 2009-03-04 by bhsohn 럭키 머신 수정안
	{		
		CVectorLuckyMachineIterator itLucky = m_VecLuckyMachine.begin();
		while(itLucky != m_VecLuckyMachine.end())
		{
			SAFE_DELETE(*itLucky);
			itLucky++;
		}
		m_VecLuckyMachine.clear();

	}
	// end 2009-03-04 by bhsohn 럭키 머신 수정안

	// 2010. 02. 11 by ckPark 발동류 장착아이템
	CVectorInvokingWearItemDPIt itDP = m_VecInvokingWearItemDPNum.begin();
	while( itDP != m_VecInvokingWearItemDPNum.end() )
	{
		SAFE_DELETE( (*itDP) );
		++itDP;
	}
	m_VecInvokingWearItemDPNum.clear();

	itDP = m_VecInvokingWearItemDPNumByUse.begin();
	while( itDP != m_VecInvokingWearItemDPNumByUse.end() )
	{
		SAFE_DELETE( (*itDP) );
		++itDP;
	}
	m_VecInvokingWearItemDPNumByUse.clear();
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	// 2010-06-15 by shcho&hslee 펫시스템
	DeletePetData();
	// End 2010-06-15 by shcho&hslee 펫시스템

}

BOOL CAtumDatabase::LoadItemData(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		ITEM * item = new ITEM;
		if( fread(item,sizeof(ITEM),1,fd) == 0)
			return FALSE;
		m_mapItemInfoTemp[item->ItemNum] = item;
	}
	return TRUE;
}

BOOL CAtumDatabase::LoadMonsterInfo(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		MEX_MONSTER_INFO * monster = new MEX_MONSTER_INFO;
		if( fread(monster,sizeof(MEX_MONSTER_INFO),1,fd) == 0)
			return FALSE;
		m_mapMonsterInfoTemp[monster->MonsterUnitKind] = monster;
	}
	return TRUE;
}

BOOL CAtumDatabase::LoadMapObjectInfo(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		MAPOBJECTINFO * object = new MAPOBJECTINFO;
		memset(object, 0x00, sizeof(MAPOBJECTINFO) );
		if( fread(object,sizeof(MAPOBJECTINFO),1,fd) == 0)
			return FALSE;
		m_mapObjectInfoTemp[object->Code] = object;
	}
	return TRUE;
}

BOOL CAtumDatabase::LoadRareItemData(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		RARE_ITEM_INFO * pRareItem = new RARE_ITEM_INFO;
		if( fread(pRareItem,sizeof(RARE_ITEM_INFO),1,fd) == 0)
			return FALSE;
		m_mapRareItemInfoTemp[pRareItem->CodeNum] = pRareItem;
	}
	return TRUE;
}

BOOL CAtumDatabase::LoadBuildingNPC(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	DBGOUT("---------------NPC INFO-----------------------------\n");
	for(int i=0;i<nCount;i++)
	{
//		RARE_ITEM_INFO * pRareItem = new RARE_ITEM_INFO;
//		if( fread(pRareItem,sizeof(RARE_ITEM_INFO),1,fd) == 0)
//			return FALSE;
//		m_mapRareItemInfoTemp[pRareItem->CodeNum] = pRareItem;
		BUILDINGNPC * pInfo = new BUILDINGNPC;
		if( fread(pInfo,sizeof(BUILDINGNPC),1,fd) == 0)
			return FALSE;
		m_mapBuildingNPCInfoTemp[pInfo->BuildingIndex] = pInfo;
//		DBGOUT("   index : %d, name : %s)\n",pInfo->NPCIndex, pInfo->NPCName);
	}
	DBGOUT("----------------------------------------------------\n");
	return TRUE;
}

BOOL CAtumDatabase::LoadGuildMark(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		GUILD_MARK_VERSION * pGuildMark = new GUILD_MARK_VERSION;
		if( fread(pGuildMark,sizeof(GUILD_MARK_VERSION)-GUILD_POINTER_SIZE,1,fd) == 0)
			return FALSE;
		pGuildMark->pData = new char[pGuildMark->nSizeOfImage];
		if( fread(pGuildMark->pData, pGuildMark->nSizeOfImage, 1, fd) == 0)
			return FALSE;
		pGuildMark->pImage = new CINFImage;
		pGuildMark->pImage->InitDeviceObjects( pGuildMark->pData, pGuildMark->nSizeOfImage );
		m_mapGuildMark[pGuildMark->nGuildUniqueNumber] = pGuildMark;
	}
	return TRUE;
}

BOOL CAtumDatabase::LoadMapInfo(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		MAP_INFO * pMapInfo = new MAP_INFO;
		if( fread(pMapInfo,sizeof(MAP_INFO),1,fd) == 0)
		{
			SAFE_DELETE(pMapInfo);
			return FALSE;
		}
		m_mapMapInfo[pMapInfo->MapIndex] = pMapInfo;
//		DBGOUT("MapInfo[%d]=[%s]\n",pMapInfo->MapIndex, pMapInfo->MapName);
	}
	return TRUE;
}

BOOL CAtumDatabase::LoadMysteryInfo(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		MYSTERY_ITEM_DROP * pMystery = new MYSTERY_ITEM_DROP;
		if( fread(pMystery,sizeof(MYSTERY_ITEM_DROP),1,fd) == 0)
		{
			SAFE_DELETE(pMystery);
			return FALSE;
		}
		m_VecMysteryItem.push_back(pMystery);
		//DBGOUT("pMystery->DropItemNum %3d : DropItemNum(%d) MysteryItemDropNum(%d)(%x)\n",i,pMystery->DropItemNum,pMystery->MysteryItemDropNum,pMystery);
	}
	return TRUE;
}

BOOL CAtumDatabase::LoadMixingInfo(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		ITEM_MIXING_INFO * pMixingInfo = new ITEM_MIXING_INFO;
		if( fread(pMixingInfo,sizeof(ITEM_MIXING_INFO),1,fd) == 0)
		{
			SAFE_DELETE(pMixingInfo);
			return FALSE;
		}
//		m_mapMixingInfo[pMixingInfo->TargetItemNum] = pMixingInfo;
		m_VecMixingInfo.push_back(pMixingInfo);
#ifdef _DEBUG
// 2006-02-10 by ispark, DBGOUT 내용 삭제
//		DBGOUT("MixingInfo[%d]--->",pMixingInfo->TargetItemNum);
//		for(int j=0;j<COUNT_ITEM_MIXING_SOURCE;j++)
//		{
//			if(pMixingInfo->SourceItem[j].ItemNum != 0 )
//			{
//				DBGOUT("[%d:%d],",pMixingInfo->SourceItem[j].ItemNum, pMixingInfo->SourceItem[j].Count);
//			}
//		}
//		DBGOUT("\n");
#endif
	}
	return TRUE;
}

BOOL CAtumDatabase::SaveItemData(FILE* fd)
{
	ASSERT_ASSERT(fd);
	return TRUE;
}

BOOL CAtumDatabase::SaveMonsterInfo(FILE* fd)
{
	ASSERT_ASSERT(fd);
	return TRUE;
}

BOOL CAtumDatabase::SaveMapObjectInfo(FILE* fd)
{
	ASSERT_ASSERT(fd);
	return TRUE;
}

BOOL CAtumDatabase::SaveRareItemData(FILE* fd)
{
	ASSERT_ASSERT(fd);
	return TRUE;
}

BOOL CAtumDatabase::SaveBuildingNPC(FILE* fd)
{
	ASSERT_ASSERT(fd);
	return TRUE;
}

BOOL CAtumDatabase::SaveGuildMark(FILE* fd)
{
	ASSERT_ASSERT(fd);
	DATA_HEADER header;
	header.nType = DB_GUILD_MARK;
	header.nDataCount = m_mapGuildMark.size();
	fwrite((char*)&header,sizeof(header),1,fd);
	CMapGuildMarkIterator it = m_mapGuildMark.begin();
	while(it != m_mapGuildMark.end())
	{
		GUILD_MARK_VERSION * pGuildMark = it->second;
		// 2007-08-03 by bhsohn 길드 마크 심사 시스템 구현
		if(pGuildMark->nSizeOfImage > 0)
		{
			fwrite( pGuildMark, sizeof(GUILD_MARK_VERSION) - GUILD_POINTER_SIZE, 1, fd );
			fwrite( pGuildMark->pData, pGuildMark->nSizeOfImage, 1, fd );
		}
		// end 2007-08-03 by bhsohn 길드 마크 심사 시스템 구현
		it++;
	}

	return TRUE;
}

BOOL CAtumDatabase::SaveMapInfo(FILE* fd)
{
	ASSERT_ASSERT(fd);
	DATA_HEADER header;
	header.nType = DB_MAP_INFO;
	header.nDataCount = m_mapMapInfo.size();
	fwrite((char*)&header,sizeof(header),1,fd);
	CMapMapInfoIterator it = m_mapMapInfo.begin();
	while(it != m_mapMapInfo.end())
	{
		MAP_INFO* pMapInfo = it->second;
		fwrite( pMapInfo, sizeof(MAP_INFO), 1, fd );
		it++;
	}
	return TRUE;
}
BOOL CAtumDatabase::SaveMixingInfo(FILE* fd)
{
	ASSERT_ASSERT(fd);
	DATA_HEADER header;
	header.nType = DB_MIXING_INFO;
	header.nDataCount = m_VecMixingInfo.size();
	fwrite((char*)&header,sizeof(header),1,fd);
	CVectorMixingInfoIterator it = m_VecMixingInfo.begin();
	while(it != m_VecMixingInfo.end())
	{
		ITEM_MIXING_INFO* pMixingInfo = *it;
		fwrite( pMixingInfo, sizeof(ITEM_MIXING_INFO), 1, fd );
		it++;
	}
	return TRUE;
}

void CAtumDatabase::InitDeviceObjects()
{
//	int nFileSize = 0;// 2006-06-22 by ispark
	FILE * fd;

	// 2006-07-04 by ispark
	// omi.tex 로딩 시스템 변경. 파일에 이상 유무를 판단한다. 이상시 게임 종료. 
	// 그외 게임상 omi 이상시는 그 때 체크해서 게임 종료를 시킨다.
	// 두번 체크(omi.tex, omi_o.tex)
	for(int nFileCount = 0; nFileCount < 2 ; nFileCount++)
	{
		fd = fopen(".\\Res-Tex\\omi.tex","rb");
		if(!fd)
		{
			DBGOUT("Data File Open Error(omi.tex)\n");
			g_pD3dApp->NetworkErrorMsgBox(STRERR_C_RESOURCE_0001);
			return;
		}

		// 파일 사이즈 조사
		fseek(fd, 0L, SEEK_END);
		int length = ftell(fd);
		if(length <= 0)
		{
			DBGOUT("------> File Size Error (omi.tex) <------\n");
			DBGOUT("<------= omi_o.tex Loading =------>\n");
			fclose(fd);

			// 마지막 파일 검사라면 종료한다.
			if(nFileCount == 1)
			{
				g_pD3dApp->NetworkErrorMsgBox(STRERR_C_RESOURCE_0001);
				return;
			}

			// omi_o.tex로 임시로딩
			// omi.tex를 지운다. (이미 파일 내용이 없기 때문이다. 그러므로 필요가 없어졌다.)
			// omi_o.tex를 omi.tex로 이름을 변경 후 로딩한다.
			remove(".\\Res-Tex\\omi.tex");
			int nResult = rename(".\\Res-Tex\\omi_o.tex",".\\Res-Tex\\omi.tex");
			if( nResult != 0 )
			{
				DBGOUT("Data File ReName Error(omi_o.tex)\n");
				g_pD3dApp->NetworkErrorMsgBox(STRERR_C_RESOURCE_0001);
				return;
			}
		}
		else
		{
			// 파일 이상무
			fseek(fd, 0L, SEEK_SET);
			break;
		}
	}

	while(TRUE)
	{
		int nRead = 0;
		DATA_HEADER header;
		if( fread(&header,sizeof(header),1,fd) == 0)
			break;
//		int size;
//		if( fread(&size,sizeof(int),1,fd) == 0)
//			break;
//		header.nType = DB_ITEM;
//		header.nDataCount = size;
//		nFileSize += header.nDataCount;
		switch(header.nType)
		{
			case DB_ITEM:
				{
					if(LoadItemData( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_ITEM)\n");
						return;
					}

	//				DBGOUT("Load DB_ITEM DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_MONSTER_INFO:
				{
					if(LoadMonsterInfo( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_MONSTER_INFO)\n");
						return;
					}
	//				DBGOUT("Load DB_MONSTER_INFO DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_MAPOBJECT:
				{
					if(LoadMapObjectInfo( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_MAPOBJECT)\n");
						return;
					}
	//				DBGOUT("Load DB_MAPOBJECT DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_RARE_ITEM:
				{
					if(LoadRareItemData( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_RARE_ITEM)\n");
						return;
					}
	//				DBGOUT("Load DB_RARE_ITEM DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_BUILDINGNPC:
				{
					if(LoadBuildingNPC( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_BUILDINGNPC)\n");
						return;
					}
	//				DBGOUT("Load DB_BUILDINGNPC DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_GUILD_MARK:
				{
					if(LoadGuildMark( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_GUILD_MARK)\n");
						return;
					}
	//				DBGOUT("Load DB_GUILD_MARK DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_MAP_INFO:
				{
					if(LoadMapInfo( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_MAP_INFO)\n");
						return;
					}
	//				DBGOUT("Load DB_MAP_INFO DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_MIXING_INFO:
				{
					if(LoadMixingInfo( fd, header.nDataCount ) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_MIXING_INFO)\n");
						return;
					}
	//				DBGOUT("Load DB_MIXING_INFO DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
				}
				break;
			case DB_MYSTERY_ITEM_DROP:
				{
					if(LoadMysteryInfo(fd,header.nDataCount) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_MYSTERY_ITEM_DROP)\n");
						return;
					}
				}
				break;
			// 2009-03-04 by bhsohn 럭키 머신 수정안
			case DB_LUCKYMACHINE:
				{
					if(LoadLuckyMachineInfo(fd,header.nDataCount) == FALSE)
					{
						DBGOUT("Data File Read Error(omi.tex : DB_LUCKYMACHINE)\n");
						return;
					}
				}
				break;
			// end 2009-03-04 by bhsohn 럭키 머신 수정안

			// 2010. 02. 11 by ckPark 발동류 장착아이템
			case DB_INVOKINGWEARITEM_DPNUM:
				{
					// 발동류 데스파람
					if( !LoadInvokingWearItemDPNum( fd, header.nDataCount ) )
					{
						DBGOUT("Data File Read Error(omi.tex : DB_INVOKINGWEARITEM_DPNUM)\n");
						return;
					}
				}
				break;

			case DB_INVOKINGWEARITEM_DPNUM_BY_USE:
				{
					// 사용류 데스파람
					if( !LoadInvokingWearItemDPNumByUse( fd, header.nDataCount ) )
					{
						DBGOUT("Data File Read Error(omi.tex : DB_INVOKINGWEARITEM_DPNUM_BY_USE)\n");
						return;
					}
				}
				break;
		// end 2010. 02. 11 by ckPark 발동류 장착아이템

		// 2010-06-15 by shcho&hslee 펫시스템
			case DB_PET_BASEDATA :

				if ( !LoadPetBaseData ( fd , header.nDataCount ) )
				{
					DBGOUT("Data File Read Error(omi.tex : DB_PET_BASEDATA)\n");
					return;
				}
				break;

			case DB_PET_LEVELDATA : 

				if ( !LoadPetLevelData ( fd , header.nDataCount ) )
				{
					DBGOUT("Data File Read Error(omi.tex : DB_PET_LEVELDATA)\n");
					return;
				}
				break;
            // 2011. 03. 08 by jskim 인피3차 구현
			case DB_PET_OPERATOR :
	
				if ( !LoadOperatorData ( fd , header.nDataCount ) )
				{
					DBGOUT("Data File Read Error(omi.tex : DB_PET_OPERATOR)\n");
					return;
				}
				break;
		// End 2010-06-15 by shcho&hslee 펫시스템
			// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
			case DB_DISSOLUTIONITEM:
				{
					if(!LoadDissolutionItemData( fd , header.nDataCount ) )
					{
						DBGOUT("Data File Read Error(omi.tex : DB_DISSOLUTIONITEM)\n");
						return;
					}
				}
				break;							 
            // end 2011. 03. 08 by jskim 인피3차 구현
			// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
			// 2010-08-10 by dgwoo 버닝맵 시스템
			case DB_BURNING_MAP:
				if(!LoadBurningMapData(fd , header.nDataCount))
				{
					DBGOUT("Data File Read Error(omi.tex : DB_BURNING_MAP)\n");
					return;
				}
				break;
			// 2010-08-10 by dgwoo 버닝맵 시스템

			// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
			case DB_MONSTER_MULTI_TARGET:
#ifdef MULTI_TARGET_JSKIM
				if(!LoadMultiTargetIndexData(fd , header.nDataCount))
				{
					DBGOUT("Data File Read Error(omi.tex : DB_MONSTER_MULTI_TARGET)\n");
					return;
				}
#endif
				break;
			//end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
		}

	}
	fclose(fd);
}

void CAtumDatabase::RestoreDeviceObjects()
{
	CMapGuildMarkIterator itGuildMark = m_mapGuildMark.begin();
	while(itGuildMark != m_mapGuildMark.end())
	{		
		itGuildMark->second->pImage->RestoreDeviceObjects();
		itGuildMark->second->pImage->SetRect( 0,0,24,12);
		itGuildMark++;
	}
}

void CAtumDatabase::InvalidateDeviceObjects()
{
	CMapGuildMarkIterator itGuildMark = m_mapGuildMark.begin();
	while(itGuildMark != m_mapGuildMark.end())
	{
		itGuildMark->second->pImage->InvalidateDeviceObjects();
		itGuildMark++;
	}
}

void CAtumDatabase::DeleteDeviceObjects()
{
	FLOG("CAtumDatabase::DeleteDeviceObjects()");
	char buf[256];
	wsprintf(buf,".\\Res-Tex\\omi_n.tex");
	FILE * fd;
	fd = fopen(buf,"w+b");
//	int nFileSize = 0;// 2006-06-22 by ispark
	// 2006-07-05 by ispark, 강제 종료는 저장을 시키지 않는다.
	if(fd && g_pD3dApp->m_bShutDown)
	{
		fclose(fd);
		remove(".\\Res-Tex\\omi_n.tex");
		fd = NULL;
	}

	if(fd)
	{
		// Item
		DATA_HEADER header;
		CMapItemInfoIterator itInfoItem;
		CMapItemInfoIterator itInfoItemTemp;
		itInfoItem = m_mapItemInfo.begin();
		while(itInfoItem != m_mapItemInfo.end())
		{
			if(itInfoItem->second)
			{
				ITEM * item = itInfoItem->second;
				itInfoItemTemp = m_mapItemInfoTemp.find(item->ItemNum);
				if(itInfoItemTemp != m_mapItemInfoTemp.end())
				{
					SAFE_DELETE(itInfoItemTemp->second);
					m_mapItemInfoTemp.erase(itInfoItemTemp);
				}
			}
			itInfoItem++;
		}
		//int temp = m_mapItemInfo.size() + m_mapItemInfoTemp.size();
		//fwrite(&temp,1,sizeof(int),fd);
		header.nType = DB_ITEM;
		header.nDataCount = m_mapItemInfo.size() + m_mapItemInfoTemp.size();
		fwrite(&header,1,sizeof(header),fd);
//		nFileSize += header.nDataCount;// 2006-06-22 by ispark
//		DBGOUT("Save DB_ITEM DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
		itInfoItem = m_mapItemInfo.begin();
		while(itInfoItem != m_mapItemInfo.end())
		{
			if(itInfoItem->second)
			{
				ITEM * item = itInfoItem->second;
				fwrite(item,1,sizeof(ITEM),fd);
				SAFE_DELETE(itInfoItem->second);
			}
			itInfoItem++;
		}
		m_mapItemInfo.clear();
		itInfoItemTemp = m_mapItemInfoTemp.begin();
		while(itInfoItemTemp != m_mapItemInfoTemp.end())
		{
			if(itInfoItemTemp->second)
			{
				ITEM * item = itInfoItemTemp->second;
				fwrite(item,1,sizeof(ITEM),fd);
				SAFE_DELETE(itInfoItemTemp->second);
			}
			itInfoItemTemp++;
		}
		m_mapItemInfoTemp.clear();
		// Monster
		CMapMonsterInfoIterator itInfoMon;
		CMapMonsterInfoIterator itInfoMonTemp;
		itInfoMon = m_mapMonsterInfo.begin();
		while(itInfoMon != m_mapMonsterInfo.end())
		{
			if(itInfoMon->second)
			{
				MEX_MONSTER_INFO * monster = itInfoMon->second;
				itInfoMonTemp = m_mapMonsterInfoTemp.find(monster->MonsterUnitKind);
				if(itInfoMonTemp != m_mapMonsterInfoTemp.end())
				{
					SAFE_DELETE(itInfoMonTemp->second);
					m_mapMonsterInfoTemp.erase(itInfoMonTemp);
				}
			}
			itInfoMon++;
		}
//		temp = m_mapMonsterInfo.size() + m_mapMonsterInfoTemp.size();
//		fwrite(&temp,1,sizeof(int),fd);
		header.nType = DB_MONSTER_INFO;
		header.nDataCount = m_mapMonsterInfo.size() + m_mapMonsterInfoTemp.size();
		fwrite(&header,1,sizeof(header),fd);
//		nFileSize += header.nDataCount;// 2006-06-22 by ispark
//		DBGOUT("Save DB_MONSTER_INFO DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
		itInfoMon = m_mapMonsterInfo.begin();
		while(itInfoMon != m_mapMonsterInfo.end())
		{
			if(itInfoMon->second)
			{
				MEX_MONSTER_INFO * monster = itInfoMon->second;
				fwrite(monster,1,sizeof(MEX_MONSTER_INFO),fd);
				SAFE_DELETE(itInfoMon->second);
			}
			itInfoMon++;
		}
		m_mapMonsterInfo.clear();
		itInfoMonTemp = m_mapMonsterInfoTemp.begin();
		while(itInfoMonTemp != m_mapMonsterInfoTemp.end())
		{
			if(itInfoMonTemp->second)
			{
				MEX_MONSTER_INFO * monster = itInfoMonTemp->second;
				fwrite(monster,1,sizeof(MEX_MONSTER_INFO),fd);
				SAFE_DELETE(itInfoMonTemp->second);
			}
			itInfoMonTemp++;
		}
		m_mapMonsterInfoTemp.clear();
		// Object
		CMapObjectInfoIterator itInfoObj;
		CMapObjectInfoIterator itInfoObjTemp;
		itInfoObj = m_mapObjectInfo.begin();
		while(itInfoObj != m_mapObjectInfo.end())
		{
			if(itInfoObj->second)
			{
				MAPOBJECTINFO * object = itInfoObj->second;
				itInfoObjTemp = m_mapObjectInfoTemp.find(object->Code);
				if(itInfoObjTemp != m_mapObjectInfoTemp.end())
				{
					SAFE_DELETE(itInfoObjTemp->second);
					m_mapObjectInfoTemp.erase(itInfoObjTemp);
				}
			}
			itInfoObj++;
		}
//		temp = m_mapObjectInfo.size() + m_mapObjectInfoTemp.size();
//		fwrite(&temp,1,sizeof(int),fd);
		header.nType = DB_MAPOBJECT;
		header.nDataCount = m_mapObjectInfo.size() + m_mapObjectInfoTemp.size();
		fwrite(&header,1,sizeof(header),fd);
//		nFileSize += header.nDataCount;// 2006-06-22 by ispark
//		DBGOUT("Save DB_MAPOBJECT DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
		itInfoObj = m_mapObjectInfo.begin();
		while(itInfoObj != m_mapObjectInfo.end())
		{
			if(itInfoObj->second)
			{
				MAPOBJECTINFO * object = itInfoObj->second;
				fwrite(object,1,sizeof(MAPOBJECTINFO),fd);
				SAFE_DELETE(itInfoObj->second);
			}
			itInfoObj++;
		}
		m_mapObjectInfo.clear();
		itInfoObjTemp = m_mapObjectInfoTemp.begin();
		while(itInfoObjTemp != m_mapObjectInfoTemp.end())
		{
			if(itInfoObjTemp->second)
			{
				MAPOBJECTINFO * object = itInfoObjTemp->second;
				fwrite(object,1,sizeof(MAPOBJECTINFO),fd);
				SAFE_DELETE(itInfoObjTemp->second);
			}
			itInfoObjTemp++;
		}
		m_mapObjectInfoTemp.clear();
		/////Rare Item info ///////////////////////////////////////////////////////////////////
		CMapRareItemInfoIterator itRareItem;
		CMapRareItemInfoIterator itRareItemTemp;
		itRareItem = m_mapRareItemInfo.begin();
		while(itRareItem != m_mapRareItemInfo.end())
		{
			if(itRareItem->second)
			{
				RARE_ITEM_INFO * pRareItem = itRareItem->second;
				itRareItemTemp = m_mapRareItemInfoTemp.find(pRareItem->CodeNum);
				if(itRareItemTemp != m_mapRareItemInfoTemp.end())
				{
					SAFE_DELETE(itRareItemTemp->second);
					m_mapRareItemInfoTemp.erase(itRareItemTemp);
				}
			}
			itRareItem++;
		}
//		temp = m_mapRareItemInfo.size() + m_mapRareItemInfoTemp.size();
//		fwrite(&temp,sizeof(int),1,fd);
		header.nType = DB_RARE_ITEM;
		header.nDataCount = m_mapRareItemInfo.size() + m_mapRareItemInfoTemp.size();
		fwrite(&header,1,sizeof(header),fd);
//		nFileSize += header.nDataCount;// 2006-06-22 by ispark
//		DBGOUT("Save DB_RARE_ITEM DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
		itRareItem = m_mapRareItemInfo.begin();
		while(itRareItem != m_mapRareItemInfo.end())
		{
			if(itRareItem->second)
			{
				RARE_ITEM_INFO * pRareItem = itRareItem->second;
				fwrite(pRareItem,1,sizeof(RARE_ITEM_INFO),fd);
				SAFE_DELETE(itRareItem->second);
			}
			itRareItem++;
		}
		m_mapRareItemInfo.clear();
		itRareItemTemp = m_mapRareItemInfoTemp.begin();
		while(itRareItemTemp != m_mapRareItemInfoTemp.end())
		{
			if(itRareItemTemp->second)
			{
				RARE_ITEM_INFO * pRareItem = itRareItemTemp->second;
				fwrite(pRareItem,1,sizeof(RARE_ITEM_INFO),fd);
				SAFE_DELETE(itRareItemTemp->second);
			}
			itRareItemTemp++;
		}
		m_mapRareItemInfoTemp.clear();
		/////BUILDINGNPC info ///////////////////////////////////////////////////////////////////
		CMapBuildingNPCIterator itBuildingNPC;
		CMapBuildingNPCIterator itBuildingNPCTemp;
		itBuildingNPC = m_mapBuildingNPCInfo.begin();
		while(itBuildingNPC != m_mapBuildingNPCInfo.end())
		{
			if(itBuildingNPC->second)
			{
				BUILDINGNPC * pBuildingNPC = itBuildingNPC->second;
				itBuildingNPCTemp = m_mapBuildingNPCInfoTemp.find(pBuildingNPC->BuildingIndex);
				if(itBuildingNPCTemp != m_mapBuildingNPCInfoTemp.end())
				{
					SAFE_DELETE(itBuildingNPCTemp->second);
					m_mapBuildingNPCInfoTemp.erase(itBuildingNPCTemp);
				}
			}
			itBuildingNPC++;
		}
//		temp = m_mapBuildingNPCInfo.size() + m_mapBuildingNPCInfoTemp.size();
//		fwrite(&temp,sizeof(int),1,fd);
		header.nType = DB_BUILDINGNPC;
		header.nDataCount = m_mapBuildingNPCInfo.size() + m_mapBuildingNPCInfoTemp.size();
		fwrite(&header,1,sizeof(header),fd);
//		nFileSize += header.nDataCount;// 2006-06-22 by ispark
//		DBGOUT("Save DB_BUILDINGNPC DataCount --> %d(Total %d)\n", header.nDataCount, nFileSize);
		itBuildingNPC = m_mapBuildingNPCInfo.begin();
		while(itBuildingNPC != m_mapBuildingNPCInfo.end())
		{
			if(itBuildingNPC->second)
			{
				BUILDINGNPC * pBuildingNPC = itBuildingNPC->second;
				fwrite(pBuildingNPC,1,sizeof(BUILDINGNPC),fd);
				SAFE_DELETE(itBuildingNPC->second);
			}
			itBuildingNPC++;
		}
		m_mapBuildingNPCInfo.clear();
		itBuildingNPCTemp = m_mapBuildingNPCInfoTemp.begin();
		while(itBuildingNPCTemp != m_mapBuildingNPCInfoTemp.end())
		{
			if(itBuildingNPCTemp->second)
			{
				BUILDINGNPC * pBuildingNPC = itBuildingNPCTemp->second;
				fwrite(pBuildingNPC,1,sizeof(BUILDINGNPC),fd);
				SAFE_DELETE(itBuildingNPCTemp->second);
			}
			itBuildingNPCTemp++;
		}
		m_mapBuildingNPCInfoTemp.clear();
		/////////////GUILD MARK///////////////////////////////////////////
		SaveGuildMark(fd);
//		nFileSize += m_mapGuildMark.size();// 2006-06-22 by ispark
//		DBGOUT("Save DB_GUILD_MARK DataCount --> %d(Total %d)\n", m_mapGuildMark.size(), nFileSize);

		////////////MAP_INFO//////////////////////////////////////////////
		SaveMapInfo(fd);
//		nFileSize += m_mapMapInfo.size();// 2006-06-22 by ispark
//		DBGOUT("Save DB_MAP_INFO DataCount --> %d(Total %d)\n", m_mapMapInfo.size(), nFileSize);
		
		SaveMixingInfo(fd);
//		nFileSize += m_VecMixingInfo.size();// 2006-06-22 by ispark
//		DBGOUT("Save DB_MIXING_INFO DataCount --> %d(Total %d)\n", m_VecMixingInfo.size(), nFileSize);
		
		fclose(fd);
		// 2008-02-12 by bhsohn omi_n.tex제거
		remove(".\\Res-Tex\\omi_n.tex");
		// end 2008-02-12 by bhsohn omi_n.tex제거
		//
		// 2007-07-11 by bhsohn omi 체크섬 추가
//		remove(".\\Res-Tex\\omi_o.tex");
//		rename(".\\Res-Tex\\omi.tex",".\\Res-Tex\\omi_o.tex");
//		rename(".\\Res-Tex\\omi_n.tex",".\\Res-Tex\\omi.tex");
	}
	else
	{
		// 아래 코드 정리해야 함(Info,InfoTemp 둘다 지우고 있음)////////////////
		CMapItemInfoIterator itInfoItem = m_mapItemInfo.begin();
		while(itInfoItem != m_mapItemInfo.end())
		{
			if(itInfoItem->second)
			{
				SAFE_DELETE(itInfoItem->second);
			}
			itInfoItem++;
		}
		m_mapItemInfo.clear();
		itInfoItem = m_mapItemInfoTemp.begin();
		while(itInfoItem != m_mapItemInfoTemp.end())
		{
			if(itInfoItem->second)
			{
				SAFE_DELETE(itInfoItem->second);
			}
			itInfoItem++;
		}
		m_mapItemInfoTemp.clear();
		CMapMonsterInfoIterator itInfoMon = m_mapMonsterInfo.begin();
		while(itInfoMon != m_mapMonsterInfo.end())
		{
			if(itInfoMon->second)
			{
				SAFE_DELETE(itInfoMon->second);
			}
			itInfoMon++;
		}
		m_mapMonsterInfo.clear();
		itInfoMon = m_mapMonsterInfoTemp.begin();
		while(itInfoMon != m_mapMonsterInfoTemp.end())
		{
			if(itInfoMon->second)
			{
				SAFE_DELETE(itInfoMon->second);
			}
			itInfoMon++;
		}
		m_mapMonsterInfoTemp.clear();
		CMapObjectInfoIterator itInfoObj = m_mapObjectInfo.begin();
		while(itInfoObj != m_mapObjectInfo.end())
		{
			if(itInfoObj->second)
			{
				SAFE_DELETE(itInfoObj->second);
			}
			itInfoObj++;
		}
		m_mapObjectInfo.clear();
		itInfoObj = m_mapObjectInfoTemp.begin();
		while(itInfoObj != m_mapObjectInfoTemp.end())
		{
			if(itInfoObj->second)
			{
				SAFE_DELETE(itInfoObj->second);
			}
			itInfoObj++;
		}
		m_mapObjectInfoTemp.clear();
	}
	CMapGuildMarkIterator itGuildMark = m_mapGuildMark.begin();
	while(itGuildMark != m_mapGuildMark.end())
	{
		itGuildMark->second->pImage->DeleteDeviceObjects();
		SAFE_DELETE(itGuildMark->second->pImage);
		SAFE_DELETE(itGuildMark->second->pData);
		SAFE_DELETE(itGuildMark->second);
		itGuildMark++;
	}
	m_mapGuildMark.clear();
	CMapOtherGuildInfoIterator itInfo = m_mapOtherGuildInfo.begin();
	while(itInfo != m_mapOtherGuildInfo.end())
	{
		SAFE_DELETE(itInfo->second);
		itInfo++;
	}
	m_mapOtherGuildInfo.clear();

	// 2010-06-15 by shcho&hslee 펫시스템
	DeletePetData();
	// End 2010-06-15 by shcho&hslee 펫시스템

}



MEX_MONSTER_INFO * CAtumDatabase::CheckMonsterInfo(int nMonType)
{
	FLOG("CAtumDatabase::CheckMonsterInfo(int nMonType)");
	MEX_MONSTER_INFO * monster = NULL;
	CMapMonsterInfoIterator itMon;
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapIsLoadingIterator itInfo = m_mapMonsterGetInfo.find(nMonType);
	if(itInfo == m_mapMonsterGetInfo.end())
	{
		// 2006-06-15 by ispark, 일정시간에 패킷을 보내는 것으로 변경
//		MSG_FC_INFO_GET_MONSTER_INFO sMsg;
//		sMsg.MonsterUnitKind = nMonType;
//		g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_MONSTER_INFO, (char*)&sMsg, sizeof(sMsg));
		SetIntDataByVector(g_pD3dApp->m_vecMonsterInfo, nMonType);

		BOOL bGetInfo = FALSE;
		m_mapMonsterGetInfo[nMonType] = bGetInfo;
		// 임시 정보
		itMon = m_mapMonsterInfoTemp.find(nMonType);
		if(itMon != m_mapMonsterInfoTemp.end())
			monster = itMon->second;
	}
	else
	{
		if(!itInfo->second)
		{
#ifdef _DEBUG
			// 정보 재요청 후 임시 정보를 꺼낸다.
			// 2006-06-15 by ispark, 일정시간에 패킷을 보내는 것으로 변경
//			MSG_FC_INFO_GET_MONSTER_INFO sMsg;
//			sMsg.MonsterUnitKind = nMonType;
//			g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_MONSTER_INFO, (char*)&sMsg, sizeof(sMsg));
			SetIntDataByVector(g_pD3dApp->m_vecMonsterInfo, nMonType);

			BOOL bGetInfo = FALSE;
			m_mapMonsterGetInfo[nMonType] = bGetInfo;
#endif // _DEBUG_endif
			// 임시 정보
			itMon = m_mapMonsterInfoTemp.find(nMonType);
			if(itMon != m_mapMonsterInfoTemp.end())
				monster = itMon->second;
		}
		else
		{// 정보 요청없이 맵에서 정보를 꺼낸다.
			itMon = m_mapMonsterInfo.find(nMonType);
			if(itMon != m_mapMonsterInfo.end())
				monster = itMon->second;
		}
	}
	LeaveCriticalSection(&g_pD3dApp->m_cs);
	if(!monster)
	{
		DBGOUT("Monster Info Is NULL : %d\n", nMonType);
	}
	return monster;
}

MAPOBJECTINFO* CAtumDatabase::CheckObjectInfo(int nObjType)
{
	FLOG("CAtumDatabase::CheckObjectInfo(int nObjType)");
	MAPOBJECTINFO * object = NULL;
	CMapObjectInfoIterator itObj;
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapIsLoadingIterator itInfo = m_mapObjectGetInfo.find(nObjType);
	if(itInfo == m_mapObjectGetInfo.end())
	{
		// 2006-06-15 by ispark, 일정시간에 패킷을 보내는 것으로 변경
//		g_pD3dApp->SendFieldSocketGetInfo(nObjType);
//		MSG_FC_INFO_GET_MAPOBJECT_INFO sMsg;
//		sMsg.Code = nObjType;
//		g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_MAPOBJECT_INFO, (char*)&sMsg, sizeof(sMsg));
		SetIntDataByVector(g_pD3dApp->m_vecMapObjectInfo, nObjType);

		BOOL bGetInfo = FALSE;
		m_mapObjectGetInfo[nObjType] = bGetInfo;
		// 임시 정보
		itObj = m_mapObjectInfoTemp.find(nObjType);
		if(itObj != m_mapObjectInfoTemp.end())
			object = itObj->second;
	}
	else
	{
		if(!itInfo->second)
		{
#ifdef _DEBUG
			// 정보 재요청 후 임시 정보를 꺼낸다.
//			MSG_FC_INFO_GET_MAPOBJECT_INFO sMsg;
//			sMsg.Code = nObjType;
//			g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_MAPOBJECT_INFO, (char*)&sMsg, sizeof(sMsg));
//			BOOL bGetInfo = FALSE;
//			m_mapObjectGetInfo[nObjType] = bGetInfo;
#endif //_DEBUG_endif
			// 임시 정보
			itObj = m_mapObjectInfoTemp.find(nObjType);
			if(itObj != m_mapObjectInfoTemp.end())
				object = itObj->second;
		}
		else
		{// 정보 요청없이 맵에서 정보를 꺼낸다.
			itObj = m_mapObjectInfo.find(nObjType);
			if(itObj != m_mapObjectInfo.end())
				object = itObj->second;
		}
	}
	LeaveCriticalSection(&g_pD3dApp->m_cs);
	return object;
}

ITEM * CAtumDatabase::GetServerItemInfo(int nItemNum)
{
	FLOG("CAtumDatabase::GetServerItemInfo(int nItemNum)");
	ITEM * item = NULL;
	if(nItemNum)
	{
		CMapItemInfoIterator itItem;
		EnterCriticalSection(&g_pD3dApp->m_cs);
		CMapIsLoadingIterator itInfo = m_mapItemGetInfo.find(nItemNum);
		if(itInfo == m_mapItemGetInfo.end())
		{// 정보 요청 정보가 없을때 - 정보요청 정보를 보관하고 아이템 정보요청을 한다.(임시 정보를 꺼낸다)
			// 임시 정보 
			itItem = m_mapItemInfoTemp.find(nItemNum);
			if(itItem != m_mapItemInfoTemp.end())
			{
				// 간단 아이템 정보 요청
				item = itItem->second;
				// 2006-06-15 by ispark, 일정시간에 패킷을 보내는 것으로 변경
//				MSG_FC_INFO_GET_SIMPLE_ITEM_INFO sMsg;
//				sMsg.ItemNum = nItemNum;
//				g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_SIMPLE_ITEM_INFO, (char*)&sMsg, sizeof(sMsg));
				SetIntDataByVector(g_pD3dApp->m_vecSimpleItemInfo, nItemNum);
			}
			else
			{
				// 아이템 전체 정보 요청
				// 2006-06-15 by ispark, 일정시간에 패킷을 보내는 것으로 변경
//				MSG_FC_INFO_GET_ITEM_INFO sMsg;
//				sMsg.ItemNum = nItemNum;
//				g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_ITEM_INFO, (char*)&sMsg, sizeof(sMsg));
				SetIntDataByVector(g_pD3dApp->m_vecItemInfo, nItemNum);
			}
			BOOL bGetInfo = FALSE;
			m_mapItemGetInfo[nItemNum] = bGetInfo;
		}
		else
		{// 정보 요청 정보가 있을때
			if(!itInfo->second)
			{
				// 임시 정보 
				itItem = m_mapItemInfoTemp.find(nItemNum);
				if(itItem != m_mapItemInfoTemp.end())
					item = itItem->second;
			}
			else
			{// 정보 요청없이 맵에서 정보를 꺼낸다.
				itItem = m_mapItemInfo.find(nItemNum);
				if(itItem != m_mapItemInfo.end())
					item = itItem->second;
			}
		}
		LeaveCriticalSection(&g_pD3dApp->m_cs);
	}
	return item;
}


ITEM * CAtumDatabase::UpdateItemInfo(ITEM &item)
{
	FLOG("CAtumDatabase::UpdateItemInfo(ITEM &item)");
	// 중량의 변화등은 영향을 주게 된다면 새로 셋팅되어야한다.
	ITEM * pInfo = NULL;
	ITEM  pInfoOld;
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapItemInfoIterator itItem = m_mapItemInfo.find(item.ItemNum);
	if(itItem != m_mapItemInfo.end())
	{
		memcpy(&pInfoOld,itItem->second,sizeof(ITEM));
		memcpy(itItem->second, &item, sizeof(ITEM) - SIZE_MAX_ITEM_DESCRIPTION);
		pInfo = itItem->second;
	}
	else
	{
		pInfo = new ITEM;
		memset(pInfo,0x00,sizeof(ITEM));
		memcpy(pInfo,&item,sizeof(ITEM) - SIZE_MAX_ITEM_DESCRIPTION);
		CMapItemInfoIterator itTemp = m_mapItemInfoTemp.find(pInfo->ItemNum);
		int nDescPoint = sizeof(ITEM)-SIZE_MAX_ITEM_DESCRIPTION;
		if(itTemp != m_mapItemInfoTemp.end())
		{
			memcpy( ((char*)pInfo)+nDescPoint, ((char*)itTemp->second)+nDescPoint, SIZE_MAX_ITEM_DESCRIPTION);
		}
		m_mapItemInfo[pInfo->ItemNum] = pInfo;
	}
	m_mapItemGetInfo[item.ItemNum] = TRUE;

	LeaveCriticalSection(&g_pD3dApp->m_cs);
	return pInfo;
}

ITEM * CAtumDatabase::UpdateSimpleItemInfo(MEX_ITEM_INFO &simpleInfo)
{
	CMapItemInfoIterator it = m_mapItemInfoTemp.find(simpleInfo.ItemNum);
	if(it != m_mapItemInfoTemp.end())
	{
		CMapItemInfoIterator it2 = m_mapItemInfo.find(simpleInfo.ItemNum);
		ITEM* pITEM = NULL;
		if(it2 == m_mapItemInfo.end())
		{
			pITEM = new ITEM;
			memcpy( pITEM, it->second, sizeof(ITEM) );
		}
		else
		{
			pITEM = it2->second;
		}
		pITEM->Kind = simpleInfo.Kind;
		pITEM->AbilityMin = simpleInfo.AbilityMin;
		pITEM->AbilityMax = simpleInfo.AbilityMax;
		pITEM->ReqUnitKind = simpleInfo.ReqUnitKind;
		pITEM->ReqMinLevel = simpleInfo.ReqMinLevel;
		pITEM->HitRate = simpleInfo.HitRate;
		pITEM->Defense = simpleInfo.Defense;
		pITEM->SpeedPenalty = simpleInfo.SpeedPenalty;
		pITEM->Range = simpleInfo.Range;
		pITEM->Price = simpleInfo.Price;
		// 2009-04-21 by bhsohn 아이템 DesParam추가
// 		pITEM->DestParameter1 = simpleInfo.DestParameter1;
// 		pITEM->ParameterValue1 = simpleInfo.ParameterValue1;
// 		pITEM->DestParameter2 = simpleInfo.DestParameter2;
// 		pITEM->ParameterValue2 = simpleInfo.ParameterValue2;
// 		pITEM->DestParameter3 = simpleInfo.DestParameter3;
// 		pITEM->ParameterValue3 = simpleInfo.ParameterValue3;
// 		pITEM->DestParameter4 = simpleInfo.DestParameter4;
// 		pITEM->ParameterValue4 = simpleInfo.ParameterValue4;
		int nArrParamCnt = 0;
		for(nArrParamCnt = 0; nArrParamCnt < SIZE_MAX_DESPARAM_COUNT_IN_ITEM; nArrParamCnt++)
		{
			pITEM->ArrDestParameter[nArrParamCnt] = simpleInfo.ArrDestParameter[nArrParamCnt];
			pITEM->ArrParameterValue[nArrParamCnt] = simpleInfo.ArrParameterValue[nArrParamCnt];

		}		
		// end 2009-04-21 by bhsohn 아이템 DesParam추가
		pITEM->ReAttacktime = simpleInfo.ReAttacktime;
		pITEM->Time = simpleInfo.Time;
		pITEM->RepeatTime = simpleInfo.RepeatTime;						// 2006-12-08 by ispark
		pITEM->RangeAngle = simpleInfo.RangeAngle;
		pITEM->MultiTarget = simpleInfo.MultiTarget;
		pITEM->ExplosionRange = simpleInfo.ExplosionRange;
		pITEM->ReactionRange = simpleInfo.ReactionRange;
		pITEM->ShotNum = simpleInfo.ShotNum;
		pITEM->MultiNum = simpleInfo.MultiNum;
		pITEM->AttackTime = simpleInfo.AttackTime;
		pITEM->ReqSP = simpleInfo.ReqSP;
		pITEM->OrbitType = simpleInfo.OrbitType;
		pITEM->ItemAttribute = simpleInfo.ItemAttribute;
		pITEM->BoosterAngle = simpleInfo.BoosterAngle;
		m_mapItemInfo[pITEM->ItemNum] = pITEM;
		m_mapItemGetInfo[pITEM->ItemNum] = TRUE;
	}
	return NULL;
}

RARE_ITEM_INFO * CAtumDatabase::GetServerRareItemInfo(int nCodeNum)
{
	FLOG("CAtumDatabase::GetServerRareItemInfo(int nItemNum)");
	RARE_ITEM_INFO * pRareItem = NULL;
	if(nCodeNum)
	{
		CMapRareItemInfoIterator itRareItem;
		EnterCriticalSection(&g_pD3dApp->m_cs);
		CMapIsLoadingIterator itGetInfo = m_mapRareItemGetInfo.find(nCodeNum);
		if(itGetInfo == m_mapRareItemGetInfo.end())
		{
			MSG_FC_INFO_GET_RARE_ITEM_INFO sMsg;
			sMsg.CodeNum = nCodeNum;
			g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_RARE_ITEM_INFO, (char*)&sMsg, sizeof(sMsg));
			BOOL bGetInfo = FALSE;
			m_mapRareItemGetInfo[nCodeNum] = bGetInfo;
			itRareItem = m_mapRareItemInfoTemp.find(nCodeNum);
			if(itRareItem != m_mapRareItemInfoTemp.end())
			{
				pRareItem = itRareItem->second;
			}
		}
		else
		{
			if(!itGetInfo->second)
			{
#ifdef _DEBUG
//				MSG_FC_INFO_GET_RARE_ITEM_INFO sMsg;
//				sMsg.CodeNum = nCodeNum;
//				g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_RARE_ITEM_INFO, (char*)&sMsg, sizeof(sMsg));
//				DBGOUT("ERROR : CAtumDatabase::GetServerRareItemInfo(int nCodeNum) : nCodeNum[%d], 레어 아이템 정보 테이블에 있는데 it->second가 NULL이다.\n",nCodeNum);
//				BOOL bGetInfo = FALSE;
//				m_mapItemGetInfo[nCodeNum] = bGetInfo;
#endif // _DEBUG_endif
				itRareItem = m_mapRareItemInfoTemp.find(nCodeNum);
				if(itRareItem != m_mapRareItemInfoTemp.end())
				{
					pRareItem = itRareItem->second;
				}
			}
			else
			{
				itRareItem = m_mapRareItemInfo.find(nCodeNum);
				if(itRareItem != m_mapRareItemInfo.end())
				{
					pRareItem = itRareItem->second;
				}
			}
		}
		LeaveCriticalSection(&g_pD3dApp->m_cs);
	}
	return pRareItem;
}
// 2010. 04. 21 by jskim 신규 럭키 머신 구현
CMapRareItemInfoList CAtumDatabase::GetServerRareItemList()
{
	return	m_mapRareItemInfoTemp;
}
//end 2010. 04. 21 by jskim 신규 럭키 머신 구현

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumDatabase::GetItemNameRareString(char* pOutFullName, int nItemNumber, int nPrefix, int nSuffix)
/// \brief		buf에 rare 스트링을 추가해준다.
/// \author		dgwoo
/// \date		2006-08-11 ~ 2006-08-11
/// \warning	
///
/// \param		buf:기본 무기 이름 , prefix:접두사 , suffix:접미사
/// \return		0 : 기본 아템 1 : 접두사 2 : 접미사 3 : 접두사,접미사.
///////////////////////////////////////////////////////////////////////////////
int CAtumDatabase::GetItemNameRareString(char* pOutFullName, int nItemNumber, int nPrefix, int nSuffix)
{
	int type = 0;
	char strPre[ITEMINFO_ITEM_FULL_NAME];
	char strSuf[ITEMINFO_ITEM_FULL_NAME];
	memset(strPre,0x00,ITEMINFO_ITEM_FULL_NAME);
	memset(strSuf,0x00,ITEMINFO_ITEM_FULL_NAME);

	ITEM* item = GetServerItemInfo(nItemNumber);

	if(item)
	{
		if(nPrefix > 0)
		{//접두사스트링 추가.
			RARE_ITEM_INFO* pre = GetServerRareItemInfo(nPrefix);
			if(pre)
			{
				sprintf(strPre,"%s ", pre->Name);
				type = 1;
			}
		}
		if(nSuffix > 0)
		{//접미사스트링 추가.
			RARE_ITEM_INFO* suf = GetServerRareItemInfo(nSuffix);
			if(suf)
			{
				sprintf(strSuf," %s", suf->Name);
				if(type)
				{
					type = 3;
				}
				type = 2;
			}
		}
		sprintf(pOutFullName,"%s%s%s", strPre,item->ItemName,strSuf);
	}
	
	return type;
}


RARE_ITEM_INFO * CAtumDatabase::UpdateRareItemInfo(RARE_ITEM_INFO &rareItem)
{
	FLOG("CAtumDatabase::UpdateItemInfo(ITEM &item)");
	// 중량의 변화등은 영향을 주게 된다면 새로 셋팅되어야한다.
	RARE_ITEM_INFO * pRareItem = NULL;
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapRareItemInfoIterator itRareItem = m_mapRareItemInfo.find(rareItem.CodeNum);
	if( itRareItem != m_mapRareItemInfo.end())
	{
		memcpy( itRareItem->second, &rareItem, sizeof(RARE_ITEM_INFO) );
		pRareItem = itRareItem->second;
	}
	else
	{
		pRareItem = new RARE_ITEM_INFO;
		memcpy(pRareItem, &rareItem, sizeof(RARE_ITEM_INFO));
		m_mapRareItemInfo[pRareItem->CodeNum] = pRareItem;
	}
	m_mapRareItemGetInfo[rareItem.CodeNum] = TRUE;
	LeaveCriticalSection(&g_pD3dApp->m_cs);
	return pRareItem;
}


MEX_MONSTER_INFO * CAtumDatabase::UpdateMonsterInfo(MEX_MONSTER_INFO *pMonster)
{
	FLOG("CAtumDatabase::UpdateMonsterInfo(MEX_MONSTER_INFO *pMonster)");
	MEX_MONSTER_INFO * pInfo = NULL;
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapMonsterInfoIterator itMon = m_mapMonsterInfo.find(pMonster->MonsterUnitKind);
	if(itMon != m_mapMonsterInfo.end())
	{
		memcpy(itMon->second, pMonster, sizeof(MEX_MONSTER_INFO));
		pInfo = itMon->second;
	}
	else
	{
		pInfo = new MEX_MONSTER_INFO;
		memcpy(pInfo,pMonster,sizeof(MEX_MONSTER_INFO));
		m_mapMonsterInfo[pInfo->MonsterUnitKind] = pInfo;
	}
	CMapMonsterIterator itMonster = g_pD3dApp->m_pScene->m_mapMonsterList.begin();
	while(itMonster != g_pD3dApp->m_pScene->m_mapMonsterList.end())
	{
		if(itMonster->second->m_info.MonsterUnitKind == pInfo->MonsterUnitKind)
			itMonster->second->Init();
		itMonster++;
	}
	m_mapMonsterGetInfo[pMonster->MonsterUnitKind] = TRUE;
	LeaveCriticalSection(&g_pD3dApp->m_cs);
	return pInfo;
}

MAPOBJECTINFO* CAtumDatabase::UpdateObjectInfo(MAPOBJECTINFO &obj)
{
	FLOG("CAtumDatabase::UpdateObjectInfo(MAPOBJECTINFO &obj)");
	MAPOBJECTINFO * pInfo  = NULL;
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapObjectInfoIterator itObj = m_mapObjectInfo.find(obj.Code);
	if(itObj != m_mapObjectInfo.end())
	{
		memcpy(itObj->second, &obj, sizeof(MAPOBJECTINFO));
		pInfo = itObj->second;
	}
	else
	{
		pInfo = new MAPOBJECTINFO;
		memcpy(pInfo,&obj,sizeof(MAPOBJECTINFO));
		m_mapObjectInfo[pInfo->Code] = pInfo;
	}
	m_mapObjectGetInfo[obj.Code] = TRUE;
	LeaveCriticalSection(&g_pD3dApp->m_cs);
	return pInfo;
}

BUILDINGNPC * CAtumDatabase::GetServerBuildingNPCInfoFromNPCIndex(int nNPCIndex)
{
	CMapBuildingNPCIterator it = m_mapBuildingNPCInfoTemp.begin();
	while(it != m_mapBuildingNPCInfoTemp.end())
	{
		if((it->second)->NPCIndex == nNPCIndex)
		{
			return it->second;
		}
		it++;
	}
	it = m_mapBuildingNPCInfo.begin();
	while(it != m_mapBuildingNPCInfo.end())
	{
		if((it->second)->NPCIndex == nNPCIndex)
		{
			return it->second;
		}
		it++;
	}
	return NULL;
}

void CAtumDatabase::FindBuildingNPCListOccupyShop(int nCityMapIndex, vector<BUILDINGNPC*> *pVecBuildingNPC)
{	
	CMapBuildingNPCIterator it = m_mapBuildingNPCInfoTemp.begin();
	while(it != m_mapBuildingNPCInfoTemp.end())
	{
		if((it->second)->OwnerCityMapIndex == nCityMapIndex)
		{
			BOOL bExist = FALSE;
			for(int i=0; i < pVecBuildingNPC->size(); i++)
			{
				if((*pVecBuildingNPC)[i]->MapIndex == it->second->MapIndex)
				{
					bExist = TRUE;
					break;
				}
			}
			if(FALSE == bExist)
			{
				pVecBuildingNPC->push_back(it->second);
			}
		}
		it++;
	}
	it = m_mapBuildingNPCInfo.begin();
	while(it != m_mapBuildingNPCInfo.end())
	{
		if((it->second)->OwnerCityMapIndex == nCityMapIndex)
		{
			BOOL bExist = FALSE;
			for(int i=0; i < pVecBuildingNPC->size(); i++)
			{
				if((*pVecBuildingNPC)[i]->MapIndex == it->second->MapIndex)
				{
					bExist = TRUE;
					break;
				}
			}
			if(FALSE == bExist)
			{
				pVecBuildingNPC->push_back(it->second);
			}
		}
		it++;
	}
}

BUILDINGNPC * CAtumDatabase::GetServerBuildingNPCInfo(int nBuildingIndex)
{
	BUILDINGNPC * pBuildingNPC = NULL;
	if(nBuildingIndex)
	{
		CMapBuildingNPCIterator itBuildingNPC;
		EnterCriticalSection(&g_pD3dApp->m_cs);
		CMapIsLoadingIterator itGetInfo = m_mapBuildingNPCGetInfo.find(nBuildingIndex);
		if(itGetInfo == m_mapBuildingNPCGetInfo.end())
		{
			DBGOUT("GetServerBuildingNPCInfo() : Rrequest BuildingInfo(%d) To Server\n", nBuildingIndex);
			MSG_FC_INFO_GET_BUILDINGNPC_INFO sMsg;
			sMsg.BuildingIndex = nBuildingIndex;
			g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_BUILDINGNPC_INFO, (char*)&sMsg, sizeof(sMsg));
			BOOL bGetInfo = FALSE;
			m_mapBuildingNPCGetInfo[nBuildingIndex] = bGetInfo;
			itBuildingNPC = m_mapBuildingNPCInfoTemp.find(nBuildingIndex);
			if(itBuildingNPC != m_mapBuildingNPCInfoTemp.end())
			{
				pBuildingNPC = itBuildingNPC->second;
			}
		}
		else
		{
			if(!itGetInfo->second)
			{
#ifdef _DEBUG
//				MSG_FC_INFO_GET_BUILDINGNPC_INFO sMsg;
//				sMsg.BuildingIndex = nBuildingIndex;
//				g_pFieldWinSocket->SendMsg(T_FC_INFO_GET_BUILDINGNPC_INFO, (char*)&sMsg, sizeof(sMsg));
//				DBGOUT("ERROR : CAtumDatabase::GetServerBuildingNPCInfo(int nBuildingIndex) : nBuildingIndex[%d], 빌딩NPC 정보 테이블에 있는데 it->second가 NULL이다.\n",nBuildingIndex);
//				BOOL bGetInfo = FALSE;
//				m_mapBuildingNPCGetInfo[nBuildingIndex] = bGetInfo;
#endif // _DEBUG_endif
				itBuildingNPC = m_mapBuildingNPCInfoTemp.find(nBuildingIndex);
				if(itBuildingNPC != m_mapBuildingNPCInfoTemp.end())
				{
					pBuildingNPC = itBuildingNPC->second;
				}
			}
			else
			{
				itBuildingNPC = m_mapBuildingNPCInfo.find(nBuildingIndex);
				if(itBuildingNPC != m_mapBuildingNPCInfo.end())
				{
					pBuildingNPC = itBuildingNPC->second;
				}
			}
		}
		LeaveCriticalSection(&g_pD3dApp->m_cs);
	}
	return pBuildingNPC;

}

BUILDINGNPC * CAtumDatabase::UpdateBuildingNPCInfo(BUILDINGNPC & buildingInfo)
{
	BUILDINGNPC * pInfo  = NULL;
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapBuildingNPCIterator itBuildingNPC = m_mapBuildingNPCInfo.find(buildingInfo.BuildingIndex);
	if(itBuildingNPC != m_mapBuildingNPCInfo.end())
	{
		memcpy(itBuildingNPC->second, &buildingInfo, sizeof(BUILDINGNPC));
		pInfo = itBuildingNPC->second;
	}
	else
	{
		pInfo = new BUILDINGNPC;
		memcpy(pInfo,&buildingInfo,sizeof(BUILDINGNPC));
		m_mapBuildingNPCInfo[pInfo->BuildingIndex] = pInfo;
	}
	m_mapBuildingNPCGetInfo[buildingInfo.BuildingIndex] = TRUE;
	LeaveCriticalSection(&g_pD3dApp->m_cs);
	return pInfo;

}

void CAtumDatabase::ReloadDatabase()
{
	FLOG("CAtumDatabase::ReloadDatabase()");
	CMapIsLoadingIterator itInfo = m_mapItemGetInfo.begin();
	while(itInfo != m_mapItemGetInfo.end())
	{
		itInfo->second = FALSE;
		itInfo++;
	}
	itInfo = m_mapMonsterGetInfo.begin();
	while(itInfo != m_mapMonsterGetInfo.end())
	{
		itInfo->second = FALSE;
		itInfo++;
	}
	itInfo = m_mapObjectGetInfo.begin();
	while(itInfo != m_mapObjectGetInfo.end())
	{
		itInfo->second = FALSE;
		itInfo++;
	}
}

CINFImage* CAtumDatabase::GetGuildMark(UINT nGuildUniqueNumber)
{
	CMapGuildMarkIterator it = m_mapGuildMark.find( nGuildUniqueNumber );
	if( it != m_mapGuildMark.end())
	{
		ASSERT_ASSERT(it->second->pImage);
		return it->second->pImage;
	}
	else
	{
		CMapIsLoadingIterator it2  = m_mapGuildMarkGetInfo.find(nGuildUniqueNumber);
		if( it2 == m_mapGuildMarkGetInfo.end())
		{
			MSG_IC_GUILD_GET_GUILD_MARK sMsg;
			sMsg.GuildUniqueNumber = nGuildUniqueNumber;
			g_pIMSocket->SendMsg( T_IC_GUILD_GET_GUILD_MARK, (char*)&sMsg, sizeof(sMsg));
			m_mapGuildMarkGetInfo[nGuildUniqueNumber] = TRUE;
		}
	}
	return NULL;
}
/*
void CAtumDatabase::UpdateGuildMark(UINT nGuildUniqueNumber, char* pData, int nSize)
{
	CMapGuildMarkIterator it = m_mapGuildMark.find( nGuildUniqueNumber );
	if( it != m_mapGuildMark.end())
	{
		it->second->InvalidateDeviceObjects();
		it->second->DeleteDeviceObjects();
		SAFE_DELETE(it->second);
	}
	CINFImage* pImage = new CINFImage;
	pImage->InitDeviceObjects( pData, nSize );
	pImage->RestoreDeviceObjects();
	pImage->SetRect( 0,0,24,12);
	m_mapGuildMark[nGuildUniqueNumber] = pImage;
}
*/
void CAtumDatabase::UpdateGuildMark( UINT nGuildUniqueNumber, int nGuildVersion,char* pData, int nSize)
{
	GUILD_MARK_VERSION *pGuildMark;
	CMapGuildMarkIterator it = m_mapGuildMark.find( nGuildUniqueNumber );
	if( it != m_mapGuildMark.end())
	{
		pGuildMark = it->second;
		pGuildMark->pImage->InvalidateDeviceObjects();
		pGuildMark->pImage->DeleteDeviceObjects();
		SAFE_DELETE(pGuildMark->pImage);
		SAFE_DELETE(pGuildMark->pData);
		m_mapGuildMark.erase(it);
	}
	else
	{
		pGuildMark = new GUILD_MARK_VERSION;
		memset( pGuildMark, 0x00, sizeof(GUILD_MARK_VERSION) );
	}
	pGuildMark->nGuildUniqueNumber = nGuildUniqueNumber;
	pGuildMark->nSizeOfImage = nSize;
	pGuildMark->nVersion = nGuildVersion;
	// 2007-08-03 by bhsohn 길드 마크 심사 시스템 구현	
	if(0 == nSize)
	{	
		pGuildMark->pData = NULL;
		pGuildMark->pImage = new CINFImage;
	}
	else
	{
		pGuildMark->pData = new char[nSize];
		memcpy( pGuildMark->pData, pData, nSize );
		pGuildMark->pImage = new CINFImage;		
		pGuildMark->pImage->InitDeviceObjects( pGuildMark->pData, nSize );	
		
		pGuildMark->pImage->RestoreDeviceObjects();
		pGuildMark->pImage->SetRect( 0,0,24,12);
	}
	// end 2007-08-03 by bhsohn 길드 마크 심사 시스템 구현	
	
	m_mapGuildMark[nGuildUniqueNumber] = pGuildMark;

	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CheckGuildMarkVersion(int nGuildUniqueNumber, int nGuildVersion )
/// \brief		저장된 길드마크의 버전이 예전 버전인지 확인하고 서버로 길드마크 요청
/// \author		dhkwon
/// \date		2004-06-01 ~ 2004-06-01
/// \warning	게임시작시 길드마크 요청부분, 타캐릭터 정보 요청 후 수행
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumDatabase::CheckGuildMarkVersion(int nGuildUniqueNumber, int nGuildVersion )
{
	GUILD_MARK_VERSION *pGuildMark;
	CMapGuildMarkIterator it = m_mapGuildMark.find( nGuildUniqueNumber );
	if( it != m_mapGuildMark.end())
	{
		pGuildMark = it->second;
		if(pGuildMark->nVersion != nGuildVersion)
		{
			MSG_IC_GUILD_GET_GUILD_MARK	sMsg;
			sMsg.GuildUniqueNumber = nGuildUniqueNumber;
			g_pIMSocket->SendMsg( T_IC_GUILD_GET_GUILD_MARK, (char*)&sMsg, sizeof(sMsg));
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			MEX_OTHER_GUILD_INFO* CAtumDatabase::GetOtherGuildInfo( int nGuildUniqueNumber )
/// \brief		다른 길드 정보 요청
/// \author		dhkwon
/// \date		2004-06-01 ~ 2004-06-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
MEX_OTHER_GUILD_INFO* CAtumDatabase::GetOtherGuildInfo( int nGuildUniqueNumber )
{
	CMapOtherGuildInfoIterator it = m_mapOtherGuildInfo.find(nGuildUniqueNumber);
	if( it == m_mapOtherGuildInfo.end())
	{
		CMapIsLoadingIterator it2  = m_mapOtherGuildInfoGetInfo.find(nGuildUniqueNumber);
		if( it2 == m_mapOtherGuildInfoGetInfo.end())
		{
			MSG_IC_GUILD_GET_OTHER_GUILD_INFO sMsg;
			sMsg.GuildUniqueNumber = nGuildUniqueNumber;
			g_pIMSocket->SendMsg( T_IC_GUILD_GET_OTHER_GUILD_INFO, (char*)&sMsg, sizeof(sMsg) );
		}
		return NULL;
	}
	return it->second;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CAtumDatabase::UpdateOtherGuildInfo(MEX_OTHER_GUILD_INFO* pMsg)
/// \brief		다른 길드 정보 업데이트
/// \author		dhkwon
/// \date		2004-06-01 ~ 2004-06-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumDatabase::UpdateOtherGuildInfo(MEX_OTHER_GUILD_INFO* pMsg)
{
	CMapOtherGuildInfoIterator it = m_mapOtherGuildInfo.find(pMsg->GuildUniqueNumber);
	if( it != m_mapOtherGuildInfo.end())
	{
		SAFE_DELETE(it->second);
	}
	MEX_OTHER_GUILD_INFO* pOther = new MEX_OTHER_GUILD_INFO;
	memcpy( pOther, pMsg, sizeof(MEX_OTHER_GUILD_INFO));
	m_mapOtherGuildInfo[pMsg->GuildUniqueNumber] = pOther;
	CheckGuildMarkVersion(pMsg->GuildUniqueNumber, pMsg->GuildMarkVersion );
}

MAP_INFO * CAtumDatabase::GetMapInfo(MapIndex_t nMapIndex)
{
	CMapMapInfoIterator it = m_mapMapInfo.find((USHORT)nMapIndex);
	if( it != m_mapMapInfo.end())
	{
		return it->second;
	}


	// 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기

// 	// 2006-07-04 by ispark, 맵 정보가 없을 때
// 	DBGOUT("\n== WARNING == Not MapInfo (%d)\n\n", nMapIndex);
// 	g_pD3dApp->NetworkErrorMsgBox(STRERR_C_RESOURCE_0001);
// 
// 	return NULL;

	return &m_DefMapInfo;

	// end 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기
}
void CAtumDatabase::FindMysteryInfo(INT i_nItemNum,vector<MYSTERY_ITEM_DROP*> *pVecItem)
{
	CVectorMysteryItemDropIterator it = m_VecMysteryItem.begin();
	while(it != m_VecMysteryItem.end())
	{
		if((*it)->MysteryItemDropNum == i_nItemNum)
		{
			pVecItem->push_back(*it);
			
		}
		it++;
	}
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		미스테리 아이템 정보를 얻어온다.
/// \author		// 2008-12-29 by bhsohn 럭키 머신 성공 이펙트 추가
/// \date		2008-12-29 ~ 2008-12-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
MYSTERY_ITEM_DROP* CAtumDatabase::GetMysteryInfo(INT	i_MysteryItemDropNum, INT i_nItemNum)
{
	CVectorMysteryItemDropIterator it = m_VecMysteryItem.begin();
	while(it != m_VecMysteryItem.end())
	{		
		if(((*it)->MysteryItemDropNum == i_MysteryItemDropNum)
			&&((*it)->DropItemNum == i_nItemNum))
		{
			return (*it);			
			
		}
		it++;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumDatabase::GetServerItemInfo(vectorItemInfoList *pItemList, int nKind)
/// \brief		아이템 종류로 모든 아이템 정보 가져오기
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumDatabase::GetServerItemInfo(vectorItemInfoList *pItemList, int nKind)
{
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapItemInfoIterator itInfo = m_mapItemInfoTemp.begin();
	while(itInfo != m_mapItemInfoTemp.end())
	{// 정보 요청 정보가 있을때
		if(itInfo->second->Kind == nKind)
		{
			pItemList->push_back(itInfo->second);
		}
		itInfo++;
	}
	LeaveCriticalSection(&g_pD3dApp->m_cs);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2007-12-17 by bhsohn 조합 가격 표시
/// \date		2007-12-17 ~ 2007-12-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
ITEM_MIXING_INFO* CAtumDatabase::GetMixerPrice(ITEM_MIXING_INFO* pMixInfo)
{
	CVectorMixingInfoIterator it = m_VecMixingInfo.begin();
	int nPrice = -1;	
	
	while(it != m_VecMixingInfo.end())
	{
		int nEqualCnt = 0;// 같은 갯수
		ITEM_MIXING_INFO* pMixingInfo = *it;

		if(pMixingInfo->NumOfSourceItems != pMixInfo->NumOfSourceItems)
		{
			it++;
			continue;
		}	
		
		int nSrcCnt = 0;
		int nDstCnt = 0;		

		for(nDstCnt = 0; nDstCnt < pMixInfo->NumOfSourceItems; nDstCnt++)
		{			
			for(nSrcCnt = 0;nSrcCnt< pMixingInfo->NumOfSourceItems;nSrcCnt++)
			{
				if((pMixingInfo->SourceItem[nSrcCnt].ItemNum == pMixInfo->SourceItem[nDstCnt].ItemNum)
					&&(pMixingInfo->SourceItem[nSrcCnt].Count == pMixInfo->SourceItem[nDstCnt].Count))
				{
					nEqualCnt++;
				}

			}
		}		
		if(nEqualCnt == pMixInfo->NumOfSourceItems)
		{
			return pMixingInfo;			
		}
		it++;
	}
	
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-04 by bhsohn 럭키 머신 수정안
/// \date		2009-03-04 ~ 2009-03-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumDatabase::LoadLuckyMachineInfo(FILE* fd, int nCount)
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		LUCKY_MACHINE_OMI * pMystery = new LUCKY_MACHINE_OMI;
		if( fread(pMystery,sizeof(LUCKY_MACHINE_OMI),1,fd) == 0)
		{
			SAFE_DELETE(pMystery);
			return FALSE;
		}
		m_VecLuckyMachine.push_back(pMystery);
		//DBGOUT("pMystery->DropItemNum %3d : DropItemNum(%d) MysteryItemDropNum(%d)(%x)\n",i,pMystery->DropItemNum,pMystery->MysteryItemDropNum,pMystery);
	}
	return TRUE;
}

// 2010. 02. 11 by ckPark 발동류 장착아이템
BOOL	CAtumDatabase::LoadInvokingWearItemDPNum( FILE* fd, int nCount )
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		INVOKING_WEAR_ITEM_DESTPARAM*	pDPNum = new INVOKING_WEAR_ITEM_DESTPARAM;
		if( fread( pDPNum, sizeof( INVOKING_WEAR_ITEM_DESTPARAM ), 1, fd ) == 0)
		{
			SAFE_DELETE( pDPNum );
			return FALSE;
		}
		m_VecInvokingWearItemDPNum.push_back( pDPNum );
	}
	return TRUE;
}

BOOL	CAtumDatabase::LoadInvokingWearItemDPNumByUse( FILE* fd, int nCount )
{
	ASSERT_ASSERT(fd);
	for(int i=0;i<nCount;i++)
	{
		INVOKING_WEAR_ITEM_DESTPARAM*	pDPNum = new INVOKING_WEAR_ITEM_DESTPARAM;
		if( fread( pDPNum, sizeof( INVOKING_WEAR_ITEM_DESTPARAM ), 1, fd ) == 0)
		{
			SAFE_DELETE( pDPNum );
			return FALSE;
		}
		m_VecInvokingWearItemDPNumByUse.push_back( pDPNum );
	}
	return TRUE;
}
// end 2010. 02. 11 by ckPark 발동류 장착아이템


// 2010-06-15 by shcho&hslee 펫시스템
/**************************************************************
**
**	펫 기본 정보 파일 읽기.
**
**	Create Info : 2010-06-15 by shcho&hslee
**
***************************************************************/
BOOL CAtumDatabase :: LoadPetBaseData ( FILE* fd , int nCount )
{

	ASSERT_ASSERT(fd);
	for ( int i = 0; i < nCount; i++ )
	{
		tPET_BASE_ALL_DATA *pPetBaseAllData = new tPET_BASE_ALL_DATA;

		if ( fread ( &pPetBaseAllData->BaseData , sizeof( tPET_BASEDATA ) , 1 , fd ) == 0 )
		{
			SAFE_DELETE( pPetBaseAllData );
			return FALSE;
		}

		m_VecPetAllData.push_back( pPetBaseAllData );
	}

	return TRUE;
}


/**************************************************************
**
**	펫 레벨업 정보 파일 읽기.
**
**	Create Info : 2010-06-15 by shcho&hslee
**
***************************************************************/
BOOL CAtumDatabase :: LoadPetLevelData ( FILE* fd , int nCount )
{

	ASSERT_ASSERT(fd);

	tPET_BASE_ALL_DATA *pPetBaseAllData = NULL;

	tPET_LEVEL_DATA sNewPetLevelData;

	for ( int i = 0; i < nCount; i++ )
	{
		memset( &sNewPetLevelData , 0x00 , sizeof( tPET_LEVEL_DATA ) );

		if ( fread ( &sNewPetLevelData , sizeof( tPET_LEVEL_DATA ) , 1 , fd ) == 0 )
			return FALSE;

		pPetBaseAllData = GetPtr_PetAllData( sNewPetLevelData.UniqueNumber );

		if ( NULL == pPetBaseAllData )
			return FALSE;
		
		pPetBaseAllData->vectPetLevelDataInfo.push_back	( sNewPetLevelData );
	}
	
	return TRUE;

}
BOOL CAtumDatabase :: LoadBurningMapData ( FILE* fd , int nCount )
{
	ASSERT_ASSERT(fd);
	for ( int i = 0; i < nCount; i++ )
	{
		BURNING_MAP_INFO * pBurning = new BURNING_MAP_INFO;
		if( fread(pBurning,sizeof(BURNING_MAP_INFO),1,fd) == 0)
		{
			SAFE_DELETE(pBurning);
			return FALSE;
		}
		m_VecBurningMapData.push_back(pBurning);
	}

	return TRUE;
	
}

tPET_BASE_ALL_DATA *CAtumDatabase :: GetPtr_PetAllData ( const INT a_PetUID )
{

	CVectorPetAllDataItr itr = m_VecPetAllData.begin();

	tPET_BASE_ALL_DATA *pPetBaseAllData = NULL;

	for ( ; itr != m_VecPetAllData.end(); ++itr )
	{
		
		pPetBaseAllData = (*itr);
		if ( NULL == pPetBaseAllData )
			continue;

		if ( pPetBaseAllData->BaseData.UniqueNumber == a_PetUID )
			return pPetBaseAllData;
	}

	return NULL;

}
BOOL CAtumDatabase::LoadOperatorData ( FILE* fd , int nCount )
{
	ASSERT_ASSERT(fd);
	for ( int i = 0; i < nCount; i++ )
	{
		OperatorInfo *pOperatorInfo = new OperatorInfo;

		if ( fread ( pOperatorInfo , sizeof( OperatorInfo ) , 1 , fd ) == 0 )
		{
			SAFE_DELETE( pOperatorInfo );
			return FALSE;
		}

		m_vecOptratorAction.push_back( pOperatorInfo );
	}
	
	return TRUE;
}
// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
BOOL CAtumDatabase::LoadMultiTargetIndexData ( FILE* fd , int nCount )
{
	ASSERT_ASSERT(fd);
	for ( int i = 0; i < nCount; i++ )
	{
		MONSTER_MULTI_TARGET MonsterMultiTargetInfo;
		memset( &MonsterMultiTargetInfo , 0x00 , sizeof( MONSTER_MULTI_TARGET ) );
		if ( fread ( &MonsterMultiTargetInfo , sizeof( MONSTER_MULTI_TARGET ) , 1 , fd ) == 0 )
		{
			return FALSE;
		}
		if(m_mapMultiTagetInfo[MonsterMultiTargetInfo.MonsterIndex].empty())
		{
			vectorMonsterMultiTarget vecMonsterMultiInfo;
			
			MONSTER_MULTI_TARGET TempMonsterMultiTargetInfo;
			TempMonsterMultiTargetInfo.MonsterIndex = MonsterMultiTargetInfo.MonsterIndex;
			TempMonsterMultiTargetInfo.PointIndex = 0;
			TempMonsterMultiTargetInfo.TargetPosition = D3DXVECTOR3(0, 0, 0);
			vecMonsterMultiInfo.push_back(TempMonsterMultiTargetInfo);

			// 2011. 06. 09 by jskim 멀티타겟 위치 변경
			//vecMonsterMultiInfo.push_back(MonsterMultiTargetInfo);
			MONSTER_MULTI_TARGET TempMonsterInfo;
			TempMonsterInfo = MonsterMultiTargetInfo;
			TempMonsterInfo.TargetPosition.x = MonsterMultiTargetInfo.TargetPosition.z;
			TempMonsterInfo.TargetPosition.z = -MonsterMultiTargetInfo.TargetPosition.x;
			vecMonsterMultiInfo.push_back(TempMonsterInfo);
			// end 2011. 06. 09 by jskim 멀티타겟 위치 변경
			
			m_mapMultiTagetInfo[MonsterMultiTargetInfo.MonsterIndex] = vecMonsterMultiInfo;
		}
		else
		{
			// 2011. 06. 09 by jskim 멀티타겟 위치 변경
			//m_mapMultiTagetInfo.find(MonsterMultiTargetInfo.MonsterIndex)->second.push_back( MonsterMultiTargetInfo );
			MONSTER_MULTI_TARGET TempMonsterInfo;
			TempMonsterInfo = MonsterMultiTargetInfo;
			TempMonsterInfo.TargetPosition.x = MonsterMultiTargetInfo.TargetPosition.z;
			TempMonsterInfo.TargetPosition.z = -MonsterMultiTargetInfo.TargetPosition.x;
			m_mapMultiTagetInfo.find(MonsterMultiTargetInfo.MonsterIndex)->second.push_back( TempMonsterInfo );
			// end 2011. 06. 09 by jskim 멀티타겟 위치 변경
		}
		
	}
	return TRUE;
}

int CAtumDatabase::GetMultiTargetIndexSize(int nMonsterIndex)
{
	return m_mapMultiTagetInfo.find(nMonsterIndex)->second.size();
}

#pragma warning(disable: 4700)

MONSTER_MULTI_TARGET CAtumDatabase::GetMultiTargetPosion(int nMonsterIndex, int nPosion)
{
	vectoritMonsterMultiTarget itr = m_mapMultiTagetInfo.find(nMonsterIndex)->second.begin();
	MONSTER_MULTI_TARGET tempInfo;
	for( ; itr != m_mapMultiTagetInfo.find(nMonsterIndex)->second.end(); ++itr)
	{
		if((*itr).MonsterIndex == nMonsterIndex && (*itr).PointIndex == nPosion)
		{ 
			tempInfo = (*itr);
			return tempInfo;
		}
	}
	return tempInfo;
}

vectorMonsterMultiTarget CAtumDatabase::GetvecMultiTargetInfo(int nMonsterIndex)
{
	return m_mapMultiTagetInfo.find(nMonsterIndex)->second;
}
// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템


/****************************************************************************************
**
**	펫 전체 정보 포인터 리턴. ( Pet Index 기준. ) Public.
**
**	Create Info : 2010. 07. 08	by hsLee.
**
*****************************************************************************************/
tPET_BASE_ALL_DATA *CAtumDatabase :: GetPtr_PetAllDataByIndex ( const INT a_PetIndex )
{

	CVectorPetAllDataItr itr = m_VecPetAllData.begin();

	tPET_BASE_ALL_DATA *pPetBaseAllData = NULL;

	for ( ; itr != m_VecPetAllData.end(); ++itr )
	{
		pPetBaseAllData = (*itr);
		if ( NULL == pPetBaseAllData )
			continue;

		if ( pPetBaseAllData->BaseData.PetIndex == a_PetIndex )
			return pPetBaseAllData;
	}

	return NULL;

}


// 
/****************************************************************************************
**
**	펫 레벨 정보 포인터 리턴. Public.
**
**	Create Info : 2010. 07. 09	by hsLee.
**
*****************************************************************************************/
tPET_LEVEL_DATA *CAtumDatabase :: GetPtr_PetLevelData ( const INT a_PetIndex , const INT a_PetLevel )
{
	tPET_BASE_ALL_DATA *psPetBaseAllData = GetPtr_PetAllDataByIndex ( a_PetIndex );

	if ( psPetBaseAllData )
		return psPetBaseAllData->rtn_LevelData ( a_PetLevel );

	return NULL;
}

/************************************************************
**
**	오퍼레이터 정보 가져오기.
**
**	Create Info :	2010-06-15 by shcho&hslee
**
*************************************************************/

OperatorInfo* CAtumDatabase :: GetPtr_OperatorAction( const INT FunctionIndex )
{
	vectorPreOperatorInfo::iterator it = m_vecOptratorAction.begin();
	
	while (it != m_vecOptratorAction.end())
	{
		if((*it)->FunctionIndex == FunctionIndex)
		{
			return (*it);
		}	
		it++;
	}
	return NULL;
}

/************************************************************
**
**	펫 기본 정보 메모리 해제.
**
**	Create Info :	2010-06-15 by shcho&hslee
**
*************************************************************/
void CAtumDatabase :: DeletePetData ( void )
{
	CVectorPetAllDataItr itPetBaseData = m_VecPetAllData.begin();
	
	while ( itPetBaseData != m_VecPetAllData.end() )
	{
		(*itPetBaseData)->vectPetLevelDataInfo.clear();

		SAFE_DELETE( (*itPetBaseData) );

		itPetBaseData++;
	}

	m_VecPetAllData.clear();
}

// End 2010-06-15 by shcho&hslee 펫시스템

// 2010-08-10 by dgwoo 버닝맵 시스템
BURNING_MAP_INFO *CAtumDatabase::GetPtr_BurningMapInfo(const MapIndex_t i_Index)
{
	CVectorBurningDataItr itBurning = m_VecBurningMapData.begin();
	BURNING_MAP_INFO *pBurning = NULL;
	while(itBurning != m_VecBurningMapData.end())
	{
		pBurning = (*itBurning);
		if(pBurning->MapIndex == i_Index)
			return pBurning;
		itBurning++;
	}
	return NULL;
}
// 2010-08-10 by dgwoo 버닝맵 시스템
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-04 by bhsohn 럭키 머신 수정안
/// \date		2009-03-04 ~ 2009-03-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumDatabase::GetLuckyMachineLen()
{
	return (int)m_VecLuckyMachine.size();

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		// 2009-03-04 by bhsohn 럭키 머신 수정안
/// \date		2009-03-04 ~ 2009-03-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
LUCKY_MACHINE_OMI * CAtumDatabase::GetLuckyMachineInfo(int nIdx)
{
	if((nIdx >= GetLuckyMachineLen())
		||(nIdx < 0))
	{
		return NULL;
	}

	return m_VecLuckyMachine[nIdx];

}


// 2010. 02. 11 by ckPark 발동류 장착아이템
void	CAtumDatabase::GetInvokingWearItemDPList( CVectorInvokingWearItemDP* pVec, InvokingDestParamID_t nIdx )
{
	for( CVectorInvokingWearItemDPIt it = m_VecInvokingWearItemDPNum.begin();
		 it != m_VecInvokingWearItemDPNum.end();
		 ++it )
	{
		if( (*it)->InvokingDestParamID == nIdx )
			pVec->push_back( (*it) );
	}
}

void	CAtumDatabase::GetInvokingWearItemDPByUseList( CVectorInvokingWearItemDP* pVec, InvokingDestParamID_t nIdx )
{
	for( CVectorInvokingWearItemDPIt it = m_VecInvokingWearItemDPNumByUse.begin();
		 it != m_VecInvokingWearItemDPNumByUse.end();
		 ++it )
	{
		if( (*it)->InvokingDestParamID == nIdx )
			pVec->push_back( (*it) );
	}
}
// end 2010. 02. 11 by ckPark 발동류 장착아이템


// 2009. 06. 09 by ckPark OMI 게임 시작시 체크섬 계산하도록 변경
void	CAtumDatabase::GetOMICheckSum( const char* szFilePath, BYTE omiCheckSum[32], long* pFileSize )
{
	memset(omiCheckSum, 0x00, 32);
	
	UINT uiCheckSum = 0;
	if(strlen(szFilePath) <=0)
	{
		return;
	}
	FILE *fp;
    fp=fopen(szFilePath, "rb");  
	if(NULL == fp)
	{
		return;
	}
	fseek( fp, 0L, SEEK_END );
	long lFileSize = ftell( fp );
	*pFileSize = lFileSize;			// 2007-05-28 by cmkwon
	fseek( fp, 0L, SEEK_SET );	

	BYTE *pFileData = new BYTE [lFileSize];
	memset(pFileData, 0x00, lFileSize);
	fread(pFileData, lFileSize, 1, fp);	

	sha256_encode(pFileData, lFileSize, omiCheckSum);
	
	fclose(fp);
	delete [] pFileData;
}
// end 2009. 06. 09 by ckPark OMI 게임 시작시 체크섬 계산하도록 변경

// 2010. 03. 18 by jskim 몬스터변신 카드
ITEM * CAtumDatabase::GetServerMonsterTransItemInfo(int nMonUintKind)
{
	EnterCriticalSection(&g_pD3dApp->m_cs);
	CMapItemInfoIterator itInfo = m_mapItemInfoTemp.begin();
	while(itInfo != m_mapItemInfoTemp.end())
	{// 정보 요청 정보가 있을때
		ITEM *pItemInfo = itInfo->second;

		if(pItemInfo->IsExistDesParam(DES_TRANSFORM_TO_MONSTER)
			&& nMonUintKind == (int)pItemInfo->GetParameterValue(DES_TRANSFORM_TO_MONSTER))
		{
			LeaveCriticalSection(&g_pD3dApp->m_cs);
			return pItemInfo;
		}
		itInfo++;
	}
	LeaveCriticalSection(&g_pD3dApp->m_cs);

	return NULL;
}
//end 2010. 03. 18 by jskim 몬스터변신 카드


/************************************************************
**
**	용해 아이템 정보 가져오기.
**
**	Create Info :	// 2010-08-31 by shcho&&jskim
**
*************************************************************/


BOOL CAtumDatabase::LoadDissolutionItemData( FILE* fd , int nCount )
{
	ASSERT_ASSERT(fd);
	tDissolutionItemInfo TempDisItem;

	for ( int i = 0; i < nCount; i++ )
	{
		memset( &TempDisItem , 0x00 , sizeof( tDissolutionItemInfo ) );

		if ( fread ( &TempDisItem , sizeof( tDissolutionItemInfo ) , 1 , fd ) == 0 )
		{
			return FALSE;
		}		
		m_vecDissolutionItemInfo.push_back( TempDisItem );
	}		
	return TRUE;
}

tDissolutionItemInfo CAtumDatabase :: Get_DissolutionitemInfo( const INT itemNum )
{
	vectorDissolutionItemInfo::iterator it = m_vecDissolutionItemInfo.begin();
	tDissolutionItemInfo tempDissolutionItem;
	memset( &tempDissolutionItem , 0x00 , sizeof( tDissolutionItemInfo ) );
	while (it != m_vecDissolutionItemInfo.end())
	{
		if((*it).SourceItemnum == itemNum)
		{
			return tempDissolutionItem;
		}	
		it++;
	}
	return tempDissolutionItem;
}

BOOL CAtumDatabase :: Is_DissolutionitemInfo( const INT itemNum )
{
	vectorDissolutionItemInfo::iterator it = m_vecDissolutionItemInfo.begin();
	tDissolutionItemInfo tempDissolutionItem;
	memset( &tempDissolutionItem , 0x00 , sizeof( tDissolutionItemInfo ) );
	while (it != m_vecDissolutionItemInfo.end())
	{
		if((*it).SourceItemnum == itemNum)
		{
			return TRUE;
		}	
		it++;
	}
	return FALSE;
}


