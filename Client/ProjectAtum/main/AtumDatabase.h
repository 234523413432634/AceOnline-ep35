// AtumDatabase.h: interface for the CAtumDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_)
#define AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

// 2011. 03. 08 by jskim 인피3차 구현 - 퀘스트 시스템		
#include "AtumParam.h"

// typedef enum 
// {
// 	DB_ITEM,
// 	DB_MONSTER_INFO,
// 	DB_MAPOBJECT,
// 	DB_RARE_ITEM,
// 	DB_BUILDINGNPC,
// 	DB_GUILD_MARK,
// 	DB_MAP_INFO,
// 	DB_MIXING_INFO,
// 	DB_MYSTERY_ITEM_DROP,
// 	// 2009-03-04 by bhsohn 럭키 머신 수정안
// 	DB_LUCKYMACHINE,
// 	// end 2009-03-04 by bhsohn 럭키 머신 수정안
// 	// 2010. 02. 11 by ckPark 발동류 장착아이템
// 	DB_INVOKINGWEARITEM_DPNUM,			// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
// 	DB_INVOKINGWEARITEM_DPNUM_BY_USE,	// 2009-09-09 ~ 2010-02-10 by dhjin, 인피니티 - 발동류장착아이템
// 	// end 2010. 02. 11 by ckPark 발동류 장착아이템
// 
// 	// 2010-08-10 by dgwoo 버닝맵 시스템
// 	DB_BURNING_MAP,
// 	// 2010-08-10 by dgwoo 버닝맵 시스템
// 
// 	// 2010-06-15 by shcho&hslee 펫시스템
// 	DB_PET_BASEDATA,						// 2010-06-15 by shcho&hslee 펫시스템 - 펫 기본 정보.
// 	DB_PET_LEVELDATA,						// 2010-06-15 by shcho&hslee 펫시스템 - 펫 레벨업 관련정보.
// 	DB_OPERATOR_ACTION,						// 2010-06-15 by shcho&hslee 펫시스템 - 오퍼레이터 정보
// 	// End 2010-06-15 by shcho&hslee 펫시스템
// 	DB_DISSOLUTION_ITEM,						// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
// 	DB_MONSTER_ADD_TARGET,	
// 
// } DB_TYPE;

// ITEM
// struct DATA_HEADER
// {
// 	DB_TYPE nType;
// 	int nDataCount;
// };

// end 2011. 03. 08 by jskim 인피3차 구현 - 퀘스트 시스템		

// GUILD_MARK_VERSION FILE STRUCT
//----------------------------------------------------------------------------------------------------
//	          8           |				   	  ARRAY_(GUILD_MARK_VERSION):nNumber                      |
//----------------------------------------------------------------------------------------------------
//	          	          |       4     |      4             |      4       |ARRAY_(char):nSizeOfImage|
//----------------------------------------------------------------------------------------------------
//    nType   |  nNumber  |    nVersion | nGuildUniqueNumber | nSizeOfImage |              char       |
//----------------------------------------------------------------------------------------------------

struct GUILD_MARK_VERSION
{
	int nVersion;
	int nGuildUniqueNumber;
	int nSizeOfImage;
	CINFImage* pImage;
	char* pData;
};

typedef std::vector< OperatorInfo* > vectorPreOperatorInfo;

class CAtumDatabase  
{
public:
	CAtumDatabase();
	virtual ~CAtumDatabase();
	
	void InitDeviceObjects();
	void RestoreDeviceObjects();
	void InvalidateDeviceObjects();
	void DeleteDeviceObjects();

	ITEM *	GetServerItemInfo(int nItemNum);
	void GetServerItemInfo(vectorItemInfoList * pItemList, int nKind);
	ITEM * UpdateItemInfo(ITEM &item);
	ITEM * UpdateSimpleItemInfo(MEX_ITEM_INFO &simpleInfo);
	ITEM * GetServerMonsterTransItemInfo(int nMonUintKind);

	MEX_MONSTER_INFO * CheckMonsterInfo(int nMonType);
	MEX_MONSTER_INFO * UpdateMonsterInfo(MEX_MONSTER_INFO* pMonsterInfo);

	void FindMysteryInfo(INT i_nItemNum,vector<MYSTERY_ITEM_DROP*> *pVecBuildingNPC);
	
	// 2008-12-29 by bhsohn 럭키 머신 성공 이펙트 추가
	MYSTERY_ITEM_DROP* GetMysteryInfo(INT	i_MysteryItemDropNum, INT i_nItemNum);
	// end 2008-12-29 by bhsohn 럭키 머신 성공 이펙트 추가

	MAPOBJECTINFO * CheckObjectInfo(int nObjType);
	MAPOBJECTINFO * UpdateObjectInfo(MAPOBJECTINFO & obj);

	RARE_ITEM_INFO * GetServerRareItemInfo(int nCodeNum);
	// 2010. 04. 21 by jskim 신규 럭키 머신 구현
	CMapRareItemInfoList GetServerRareItemList();
	//end 2010. 04. 21 by jskim 신규 럭키 머신 구현
	RARE_ITEM_INFO * UpdateRareItemInfo(RARE_ITEM_INFO &rareItem);

	BUILDINGNPC * GetServerBuildingNPCInfoFromNPCIndex(int nNPCIndex);
	BUILDINGNPC * GetServerBuildingNPCInfo(int nBuildingIndex);
	BUILDINGNPC * UpdateBuildingNPCInfo(BUILDINGNPC & buildingInfo);

	CINFImage*	GetGuildMark(UINT nGuildUniqueNumber);
	void CheckGuildMarkVersion(int nGuildUniqueNumber, int nGuildVersion );
	void UpdateGuildMark(UINT nGuildUniqueNumber, int nGuildVersion, char* pData, int nSize);

	MEX_OTHER_GUILD_INFO* GetOtherGuildInfo( int nGuildUniqueNumber );
	void UpdateOtherGuildInfo(MEX_OTHER_GUILD_INFO* pMsg);

	MAP_INFO * GetMapInfo(MapIndex_t nMapIndex);
	void FindBuildingNPCListOccupyShop(int nCityMapIndex, vector<BUILDINGNPC*> *pVecItem);

	int GetItemNameRareString(char* pOutFullName, int nItemNumber, int nPrefix, int nSuffix);

	void ReloadDatabase();

	// 2007-12-17 by bhsohn 조합 가격 표시
	// 조합 가격을 알아온다.
	ITEM_MIXING_INFO* GetMixerPrice(ITEM_MIXING_INFO* pMixInfo);

	// 2009-03-04 by bhsohn 럭키 머신 수정안
	int GetLuckyMachineLen();
	LUCKY_MACHINE_OMI * GetLuckyMachineInfo(int nIdx);
	// end 2009-03-04 by bhsohn 럭키 머신 수정안

	// 2010. 02. 11 by ckPark 발동류 장착아이템
	// 발동류 데스파람 얻어오기
	void	GetInvokingWearItemDPList( CVectorInvokingWearItemDP* pVec, InvokingDestParamID_t nIdx );
	// 사용류 데스파람 얻어오기
	void	GetInvokingWearItemDPByUseList( CVectorInvokingWearItemDP* pVec, InvokingDestParamID_t nIdx );
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	// 2009. 06. 09 by ckPark OMI 게임 시작시 체크섬 계산하도록 변경
	void	GetOMICheckSum( const char* szFilePath, BYTE omiCheckSum[32], long* pFileSize );
	// end 2009. 06. 09 by ckPark OMI 게임 시작시 체크섬 계산하도록 변경

	// 2010-06-15 by shcho&hslee 펫시스템
	// 펫 전체 정보 포인터 리턴. ( Pet Index 기준. ) Public.
	tPET_BASE_ALL_DATA *GetPtr_PetAllDataByIndex ( const INT a_PetIndex );

	// 펫 레벨 정보 포인터 리턴.
	tPET_LEVEL_DATA *GetPtr_PetLevelData ( const INT a_PetIndex , const INT a_PetLevel );

	OperatorInfo* GetPtr_OperatorAction( const INT FunctionIndex );
	// End 2010-06-15 by shcho&hslee 펫시스템

	// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
	tDissolutionItemInfo Get_DissolutionitemInfo( const INT itemNum );
	BOOL Is_DissolutionitemInfo( const INT itemNum );
	// end 2010-08-31 by shcho&&jskim, 용해 시스템 구현

	// 2010-08-10 by dgwoo 버닝맵 시스템
	BURNING_MAP_INFO *GetPtr_BurningMapInfo(const MapIndex_t i_Index);
	// 2010-08-10 by dgwoo 버닝맵 시스템

	// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	int GetMultiTargetIndexSize(int nMonsterIndex);
	MONSTER_MULTI_TARGET GetMultiTargetPosion(int nMonsterIndex, int nPosion);
	vectorMonsterMultiTarget GetvecMultiTargetInfo(int nMonsterIndex);
	// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템

protected:
	BOOL LoadItemData(FILE* fd, int nCount);
	BOOL LoadMonsterInfo(FILE* fd, int nCount);
	BOOL LoadMapObjectInfo(FILE* fd, int nCount);
	BOOL LoadRareItemData(FILE* fd, int nCount);
	BOOL LoadBuildingNPC(FILE* fd, int nCount);
	BOOL LoadGuildMark(FILE* fd, int nCount);
	BOOL LoadMapInfo(FILE* fd, int nCount);
	BOOL LoadMixingInfo(FILE* fd, int nCount);
	BOOL LoadMysteryInfo(FILE* fd, int nCount);
	// 2009-03-04 by bhsohn 럭키 머신 수정안
	BOOL LoadLuckyMachineInfo(FILE* fd, int nCount);
	// end 2009-03-04 by bhsohn 럭키 머신 수정안

	// 2010. 02. 11 by ckPark 발동류 장착아이템
	BOOL LoadInvokingWearItemDPNum( FILE* fd, int nCount );
	BOOL LoadInvokingWearItemDPNumByUse( FILE* fd, int nCount );
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	// 2010-06-15 by shcho&hslee 펫시스템
	BOOL LoadPetBaseData ( FILE* fd , int nCount );
	BOOL LoadPetLevelData ( FILE* fd , int nCount );
	// 2010-08-10 by dgwoo 버닝맵 시스템
	BOOL LoadBurningMapData ( FILE* fd , int nCount );
	BOOL LoadOperatorData ( FILE* fd , int nCount );
	// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	BOOL LoadMultiTargetIndexData( FILE* fd , int nCount );
	// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	tPET_BASE_ALL_DATA *GetPtr_PetAllData ( const INT a_PetUID );

	void DeletePetData ( void );
	// End 2010-06-15 by shcho&hslee 펫시스템
	// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
	BOOL LoadDissolutionItemData( FILE* fd , int nCount );
	// end 2010-08-31 by shcho&&jskim, 용해 시스템 구현

	BOOL SaveItemData(FILE* fd);
	BOOL SaveMonsterInfo(FILE* fd);
	BOOL SaveMapObjectInfo(FILE* fd);
	BOOL SaveRareItemData(FILE* fd);
	BOOL SaveBuildingNPC(FILE* fd);
	BOOL SaveGuildMark(FILE* fd);
	BOOL SaveMapInfo(FILE* fd);
	BOOL SaveMixingInfo(FILE* fd);

	// 2010-06-15 by shcho&hslee 펫시스템
	BOOL SavePetBaseData ( FILE* fd );
	BOOL SavePetLevelData ( FILE* fd );
	// End 2010-06-15 by shcho&hslee 펫시스템

protected:
	CMapItemInfoList			m_mapItemInfo;					// 각 Item Data
	CMapItemInfoList			m_mapItemInfoTemp;				// 각 Item Data 임시
	CMapIsLoadingList			m_mapItemGetInfo;				// 각 Item Data - 정보를 요청했는지 
	CMapRareItemInfoList		m_mapRareItemInfo;				// 각 Rare Item Data
	CMapRareItemInfoList		m_mapRareItemInfoTemp;			// 각 Rare Item Data 임시
	CMapIsLoadingList			m_mapRareItemGetInfo;			// 각 Rare Item Data - 정보를 요청했는지 
	CMapMonsterInfoList			m_mapMonsterInfo;				// 각 Monster Data
	CMapMonsterInfoList			m_mapMonsterInfoTemp;			// 각 Monster Data 임시
	CMapIsLoadingList			m_mapMonsterGetInfo;			// 각 Monster Data - 정보를 요청했는지 
	CMapObjectInfoList			m_mapObjectInfo;				// 각 Object Data
	CMapObjectInfoList			m_mapObjectInfoTemp;			// 각 Object Data 임시
	CMapIsLoadingList			m_mapObjectGetInfo;				// 각 Object Data - 정보를 요청했는지 
	CMapBuildingNPCList			m_mapBuildingNPCInfo;			// 각 BUILDINGNPC
	CMapBuildingNPCList			m_mapBuildingNPCInfoTemp;		// 각 BUILDINGNPC 임시
	CMapIsLoadingList			m_mapBuildingNPCGetInfo;		// 각 BUILDINGNPC - 정보를 요청했는지
	CMapGuildMark				m_mapGuildMark;					// 길드 문장 정보
	CMapIsLoadingList			m_mapGuildMarkGetInfo;			// 길드 문장 정보 - 정보를 요청했는지
	CMapOtherGuildInfo			m_mapOtherGuildInfo;			// 다른 캐릭 길드 정보
	CMapIsLoadingList			m_mapOtherGuildInfoGetInfo;		// 다른 캐릭 길드 정보
	CMapMapInfo					m_mapMapInfo;					// 맵 정보(맵이름)
	CVectorMysteryItemDrop		m_VecMysteryItem;				// 미스터리 아이템, 럭키 머신 아이템.
	CVectorMixingInfo			m_VecMixingInfo;				// 조합 정보
	// 2009-03-04 by bhsohn 럭키 머신 수정안
	CVectorLuckyMachine			m_VecLuckyMachine;				// 럭키 머신 아이템 수정안
	// end 2009-03-04 by bhsohn 럭키 머신 수정안

	// 2010. 02. 11 by ckPark 발동류 장착아이템
	CVectorInvokingWearItemDP	m_VecInvokingWearItemDPNum;
	CVectorInvokingWearItemDP	m_VecInvokingWearItemDPNumByUse;
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	// 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기

	MAP_INFO					m_DefMapInfo;

	// end 2009. 01. 12 by ckPark MapInfo 없는 맵은 모선전 정보 안띄우기

	// 2010-06-15 by shcho&hslee 펫시스템
	CVectorPetAllData			m_VecPetAllData;	
	vectorPreOperatorInfo		m_vecOptratorAction;
	// End 2010-06-15 by shcho&hslee 펫시스템

	// 2010-08-10 by dgwoo 버닝맵 시스템
	CVectorBurningData			m_VecBurningMapData;

	// 2010-08-31 by shcho&&jskim, 용해 시스템 구현
	vectorDissolutionItemInfo	m_vecDissolutionItemInfo;
	// end 2010-08-31 by shcho&&jskim, 용해 시스템 구현
	// 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
	map<INT,vectorMonsterMultiTarget>	m_mapMultiTagetInfo;
	// end 2011. 03. 08 by jskim 인피3차 구현 - 넌 타겟 시스템
};

#endif // !defined(AFX_ATUMDATABASE_H__3842E2DD_C6C4_4D3B_9CFB_18F7EA62E851__INCLUDED_)
