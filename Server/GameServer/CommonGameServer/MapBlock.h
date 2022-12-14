#ifndef __ATUM_MAP_BLOCK_H__
#define __ATUM_MAP_BLOCK_H__

//#include "stdafx.h"
//#include "IOCP.h"
#include "VMemPool.h"

/******************************************************************************
	ATUM Map 관리용 모듈
	* Map > Block > Tile
******************************************************************************/
#define SIZE_MAP_TILE_SIZE						40
#define	SIZE_MAP_BLOCK_SIDE						960		// 일단, SIZE_VISIBLE_RADIUS/2 테스트를 통해 최적의 값 정해야 함
#define SIZE_BLOCK_X							SIZE_MAP_BLOCK_SIDE
#define SIZE_BLOCK_Z							SIZE_MAP_BLOCK_SIDE
#define SIZE_CHARACTER_VISIBLE_SIDE				2000	// 캐릭터 시야
#define SIZE_MONSTER_VISIBLE_SIDE				1440	// 몬스터 시야

#define	SIZE_MAP_BLOCK_SIDE_FOR_NPCSERVER		960		// NPC Server에서 사용하는 MapBlockSize
#define SIZE_BLOCK_X_FOR_NPCSERVER				SIZE_MAP_BLOCK_SIDE_FOR_NPCSERVER
#define SIZE_BLOCK_Z_FOR_NPCSERVER				SIZE_MAP_BLOCK_SIDE_FOR_NPCSERVER

#define SIZE_MONSTER_CREATION_RANGE				180.0f	// 몬스터가 생성될 때 이 거리 안에 캐릭터가 있으면 생성되지 않음
#define COUNT_MAX_ADMIN_SUMMON_MONSTER			20		// 몬스터 소환시 한번에 소환할수 있는 최대 크기
#define SIZE_TILE_ADMIN_SUMMON_MONSTER_REGION	2		// 몬스터 소환시 생성하는 영역의 타일 블럭(2 + 1 + 2)

#define SIZE_MAX_EXPERIENCE_DIVISION_RADIUS		(SIZE_MONSTER_VISIBLE_SIDE*2)	// 경험치 분배시 몬스터를 기준으로 이거리 안에 있어야함

// 주어진 좌표를 Tile Index로 변환한다
#define CHANGE_TO_TILEINDEX(x)		((int)((x)/SIZE_MAP_TILE_SIZE))


//#define _MAP_BLOCK_LIST
typedef list<ClientIndex_t> ClientIndexList;
typedef vector<ClientIndex_t> ClientIndexVector;

#define MAX_DROPITEM_DELAY					15000	// miliseconds
#define SIZE_MAX_DROP_ITEM_PRIORITY_INFO	20
#define DROP_ITEM_RADIUS					80

enum EnumPriorityInfoType
{
	PIT_NONE		= 0,
	PIT_CHARACTER	= 1,
	PIT_PARTY		= 2
};

struct PRIORITY_INFO
{
	EnumPriorityInfoType	ePrioryInfoType;			// 캐릭터에 대한 것인지, 파티에 대한 것인지 구분
	UID32_t					CharacterUniqueNumber;		// PIT_CHARACTER일 때 캐릭터 UID
	PartyID_t				PartyID;					// PIT_PARTY일 때 PartyID
	DWORD					dwDelay;					// miliseconds
};

struct DROPITEM
{
	ITEM_GENERAL		*pItem;						// new로 생성되어 할당됨!
	PRIORITY_INFO		priorityInfoArray[SIZE_MAX_DROP_ITEM_PRIORITY_INFO];
	int					priorityInfoCount;
	DWORD				dwStartTick;				// miliseconds
	D3DXVECTOR3			Position;
	BOOL				bProcessing;
	UID32_t				FirstCharacterUID1;				// charcter UID
	BOOL				bTendering;					// 2009-09-09 ~ 2010 by dhjin, 인피니티 - TRUE = 입찰상태				

public:
	DROPITEM()
	{
		pItem				= NULL;
		MEMSET_ZERO(priorityInfoArray, SIZE_MAX_DROP_ITEM_PRIORITY_INFO*sizeof(PRIORITY_INFO));
		priorityInfoCount	= 0;
		dwStartTick			= 0;
		Position.x			= 0;
		Position.y			= 0;
		Position.z			= 0;
		bProcessing			= FALSE;
		FirstCharacterUID1	= 0;
		bTendering			= FALSE;			// 2009-09-09 ~ 2010 by dhjin, 인피니티 - TRUE = 입찰상태	
	}

#ifdef _ATUM_SERVER
	void * operator new(size_t size)
	{
		return CVMemPool::vmObjectNew(size);
	}

	void operator delete(void* p)
	{
		CVMemPool::vmObjectDelete(p, sizeof(DROPITEM));
	};
#endif // _ATUM_SERVER
};

typedef mt_map<ITEM_GENERAL*, DROPITEM> mtmapDropItem;	// ITEM_GENERAL*는 프로토콜 전송시는 UINT로 함

/*
+ 마인 반응 시간 관리 방법
	- 떨어졌을 때 시간을 dwStartTick을 저장한다.
	- 주위에 유닛이 걸렸을 때
		(1) dwStartTick이 0보다 크면, currentTick비교를 해서 적용시간을 결정한다.
			만약 적용 시간 이후면 dwStartTick을 0으로 바꾼 후 처리한다.
		(2) dwStartTick이 0이거나 작으면 바로 마인 공격을 한다.
+ 고유 넘버는 DROPMINE의 pointer로 한다.
+ 자료구조는 set을 사용
+
*/
struct DROPMINE
{
	UID32_t				CharacterUniqueNumber;		// 떨어뜨린 character, 소유자
													// 이미 폭파된 경우는 timer 처리를 위해서 INVAILD_UNIQUE_NUMBER를 할당
													// 구조체의 삭제는 timer가 관리
	ClientIndex_t		ClientIndex;				// 떨어뜨린 character, 소유자
	ITEM*				pItemInfo;
	D3DXVECTOR3			Position;
	TimeUnit_t			dwStartTick;				// miliseconds, by GetTickCount()

	void * operator new(size_t size)
	{
		return CVMemPool::vmObjectNew(size);
	}
	void operator delete(void* p)
	{
		CVMemPool::vmObjectDelete(p, sizeof(DROPMINE));
	}
};

typedef struct _RECTANGLE
{
	float fMinX;
	float fMinZ;
	float fMaxX;
	float fMaxZ;
} RECTANGLE;

struct TWO_BLOCK_INDEXES
{
	short sMinX;
	short sMinZ;
	short sMaxX;
	short sMaxZ;
};

struct BLOCK_INDEX
{
	short sX;
	short sZ;
};

// start 2011-03-23 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가
struct MONSTER_MAPBLOCK_INFO
{
	ClientIndex_t	MonsterIndex;					// 몬스터 고유 번호
	BLOCK_INDEX		Block;							// 블럭 좌표
	
	MONSTER_MAPBLOCK_INFO()		{ MonsterIndex = 0; Block.sX = 0; Block.sZ = 0; }
	MONSTER_MAPBLOCK_INFO(ClientIndex_t	Index, short x, short y)		{ MonsterIndex = Index; Block.sX = x; Block.sZ = y; }
	~MONSTER_MAPBLOCK_INFO()		{}
};

typedef mt_vector<MONSTER_MAPBLOCK_INFO>	mtvectorMTMonsterIndex;
// end 2011-03-23 by hskim, 인피니티 3차 - 몬스터 멀티 타겟팅 기능 추가

class CSkinnedMesh;
typedef struct _OBJECTINFOSERVER
{
	DWORD			m_dwObjType;			// Object 타입
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vVel;
	D3DXVECTOR3		m_vUp;
	EVENTINFO		m_EventInfo;
	CSkinnedMesh	*m_pSkinnedMesh;
	D3DXMATRIX		m_matrix;
	DWORD			dwObjBossMonResTime;		// 2006-11-22 by cmkwon, 
	MONSTER_INFO	*m_pMonsterInfo;			// 2007-08-18 by cmkwon, 오브젝트 몬스터 소환 정보에 MONSTER_INFO * 설정하기
	// start 2011-06-02 인피니티 3차 - 스텝 6 - 주기적 소환 기능 제작
	BYTE			m_bNotCreateMonster;
	MONSTER_BALANCE_DATA	MonsterBalanceInfo;
	// end 2011-06-02 인피니티 3차 - 스텝 6 - 주기적 소환 기능 제작
} OBJECTINFOSERVER;

typedef vector<OBJECTINFOSERVER>	vectorObjectInfoServer;
typedef vector<OBJECTINFOSERVER*>	vectorObjectInfoServerPtr;

typedef mt_vector<ClientIndex_t>	mtlistUnitIndex_t;
typedef mt_vector<ClientIndex_t>	mtvectClientIndex_t;
typedef vector<ClientIndex_t>		vectClientIndex_t;			// 2006-07-24 by cmkwon
typedef mt_set<DROPMINE*>			mtsetDropMine;

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 변경 오브젝트를 위해!!!! 아 힘들어...
typedef mt_vector<DWORD>				mtDeletedObjectInfoList;	// 2009-09-09 ~ 2010-01 by dhjin, 인피니티 - 소스 체크
typedef mt_vector<OBJECTINFOSERVER>		mtNewObjectInfoList;		// 2009-09-09 ~ 2010-01 by dhjin, 인피니티 - 소스 체크

class CMapChannel;

class CMapBlock
{
public:
	CMapBlock();
	virtual ~CMapBlock();

	// 캐릭터와 몬스터 공통
	inline BOOL InsertUnit(ClientIndex_t clientIndex);
	inline BOOL DeleteUnit(ClientIndex_t clientIndex);

	// 캐릭터
	inline BOOL InsertCharacter(ClientIndex_t clientIndex);
	inline BOOL DeleteCharacter(ClientIndex_t clientIndex);
	inline void ResetCharacter();					// 2008-02-20 by dhjin, 아레나 통합 -

	// 몬스터
	inline BOOL InsertMonster(ClientIndex_t clientIndex);
	inline BOOL DeleteMonster(ClientIndex_t clientIndex);

	inline int GetNumCharachter();
	inline int GetNumMonster();
	inline int GetNumItem();

public:
	CMapChannel			*m_pMapChannel;

	mtlistUnitIndex_t	m_CharacterIndexMtlist;
	mtlistUnitIndex_t	m_MonsterIndexMtlist;

	///////////////////////////////////////////////////////////////////////////
	// item
	mtmapDropItem		m_DropItemMtmap;	// 생성된 아이템의 pointer를 저장

	inline void InsertDropItem(ITEM_GENERAL* pStoreItem, DROPITEM *pDropItem);
	inline int DeleteDropItem(ITEM_GENERAL* pStoreItem);

	// 2010-04-09 by cmkwon, 인피2차 추가 수정(단계별 보상 추가) - 
	DROPITEM* GetDROPITEM_SetProcess(ITEM_GENERAL* pStoreItem, BOOL i_bPickupTenderItem=FALSE);

	void AllDeleteDropItem(void);		// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 

	///////////////////////////////////////////////////////////////////////////
	// item
	mtsetDropMine		m_setMapBlockDropMine;	// 생성된 아이템의 pointer를 저장

	// map block index
	short				m_x;	// map block x index
	short				m_z;	// map block z index

	//! map block의 center position X
	float				m_CenterPositionX;
	//! map block의 center position Z
	float				m_CenterPositionZ;

	static int			ms_nSIZE_BLOCK;
};

void CMapBlock::InsertDropItem(ITEM_GENERAL* pStoreItem, DROPITEM *pDropItem)
{
	m_DropItemMtmap.insertLock(pStoreItem, *pDropItem);
}

int CMapBlock::DeleteDropItem(ITEM_GENERAL* pStoreItem)
{
	int ret = 0;
	m_DropItemMtmap.lock();
	ret = m_DropItemMtmap.erase(pStoreItem);
	m_DropItemMtmap.unlock();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMapBlock::InsertUnit
// 반환되는 형  : void
// 함 수 인 자  : ClientIndex_t clientIndex
// 함 수 설 명  : inline 함수
//					캐릭터와 몬스터를 구별하여 MapBlock에 추가하는 함수를 호출한다.
BOOL CMapBlock::InsertUnit(ClientIndex_t clientIndex)
{
	if (clientIndex < MONSTER_CLIENT_INDEX_START_NUM)
	{
		return InsertCharacter(clientIndex);
	}
	else
	{
		return InsertMonster(clientIndex);
	}
}


////////////////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMapBlock::DeleteUnit
// 반환되는 형  : void
// 함 수 인 자  : ClientIndex_t clientIndex
// 함 수 설 명  : 캐릭터와 몬스터를 구별하여 MapBlock에서 삭제하는 함수를 호출
BOOL CMapBlock::DeleteUnit(ClientIndex_t clientIndex)
{
	if (clientIndex < MONSTER_CLIENT_INDEX_START_NUM)
	{
		return DeleteCharacter(clientIndex);
	}
	else
	{
		return DeleteMonster(clientIndex);
	}
}

// Block을 list으로 구현 한것
////////////////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMapBlock::InsertCharacter
// 반환되는 형  : void
// 함 수 인 자  : ClientIndex_t clientIndex ==> MapBlock에 추가할 캐릭터 인덱스
// 함 수 설 명  : MapBlock의 캐릭터의 인덱스 리스트에 clientIndex를 추가한다.
BOOL CMapBlock::InsertCharacter(ClientIndex_t clientIndex)
{	
	m_CharacterIndexMtlist.lock();
	if(0 == m_CharacterIndexMtlist.capacity())
	{
		// 2007-07-16 by cmkwon, 기본 사이즈 10으로 수정함
		//m_CharacterIndexMtlist.reserve(ms_nSIZE_BLOCK/8);
		m_CharacterIndexMtlist.reserve(10);
	}

#ifdef _DEBUG
	assert(clientIndex < MONSTER_CLIENT_INDEX_START_NUM);
	mtlistUnitIndex_t::iterator itr = find(m_CharacterIndexMtlist.begin(), m_CharacterIndexMtlist.end(), clientIndex);
	if(itr != m_CharacterIndexMtlist.end())
	{
		char szSystemLog[256];
		sprintf(szSystemLog, "====> InsertCharacter Error Index[%4d]\r\n", clientIndex);
		g_pGlobal->WriteSystemLog(szSystemLog);
		DBGOUT(szSystemLog);
		m_CharacterIndexMtlist.unlock();
		return FALSE;
	}
	m_CharacterIndexMtlist.push_back(clientIndex);
#else
	m_CharacterIndexMtlist.push_back(clientIndex);
#endif
	m_CharacterIndexMtlist.unlock();

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMapBlock::DeleteCharacter
// 반환되는 형  : void
// 함 수 인 자  : ClientIndex_t clientIndex
// 함 수 설 명  : MapBlock의 캐릭터 인덱스 리스트에서 clientIndex를 삭제한다.
BOOL CMapBlock::DeleteCharacter(ClientIndex_t clientIndex)
{	
	m_CharacterIndexMtlist.lock();
#ifdef _DEBUG
	assert(clientIndex < MONSTER_CLIENT_INDEX_START_NUM);
	mtlistUnitIndex_t::iterator itr = find(m_CharacterIndexMtlist.begin(), m_CharacterIndexMtlist.end(), clientIndex);
	if(itr == m_CharacterIndexMtlist.end())
	{
		char szSystemLog[256];
		sprintf(szSystemLog, "====> DeleteCharacter Error Index[%4d]\r\n", clientIndex);
		g_pGlobal->WriteSystemLog(szSystemLog);
		DBGOUT(szSystemLog);
		m_CharacterIndexMtlist.unlock();
		return FALSE;
	}
	m_CharacterIndexMtlist.erase(remove(m_CharacterIndexMtlist.begin(), m_CharacterIndexMtlist.end(), clientIndex)
		, m_CharacterIndexMtlist.end());
#else
	m_CharacterIndexMtlist.erase(remove(m_CharacterIndexMtlist.begin(), m_CharacterIndexMtlist.end(), clientIndex)
		, m_CharacterIndexMtlist.end());
#endif
	m_CharacterIndexMtlist.unlock();
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CMapBlock::ResetCharacter()
/// \brief		아레나 통합 -
/// \author		dhjin
/// \date		2008-02-20 ~ 2008-02-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CMapBlock::ResetCharacter()
{
	m_CharacterIndexMtlist.clearLock();
}

////////////////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMapBlock::InsertMonster
// 반환되는 형  : void
// 함 수 인 자  : ClientIndex_t clientIndex
// 함 수 설 명  : MabBlock의 몬스터 인덱스 리스트에 clientIndex를 추가한다.
BOOL CMapBlock::InsertMonster(ClientIndex_t clientIndex)
{
	m_MonsterIndexMtlist.lock();
	if(0 == m_MonsterIndexMtlist.capacity())
	{
		// 2007-07-16 by cmkwon, 기본 사이즈 10으로 수정함
		//m_MonsterIndexMtlist.reserve(ms_nSIZE_BLOCK/8);
		m_MonsterIndexMtlist.reserve(10);
	}
#ifdef _DEBUG
	assert(clientIndex >= MONSTER_CLIENT_INDEX_START_NUM);
	mtlistUnitIndex_t::iterator itr = find(m_MonsterIndexMtlist.begin(), m_MonsterIndexMtlist.end(), clientIndex);
	if(itr != m_MonsterIndexMtlist.end())
	{
		char szSystemLog[256];
		sprintf(szSystemLog, "====> InsertMonster Error Index[%5d]\r\n", clientIndex);
		g_pGlobal->WriteSystemLog(szSystemLog);
		DBGOUT(szSystemLog);
		m_MonsterIndexMtlist.unlock();
		return FALSE;
	}
	m_MonsterIndexMtlist.push_back(clientIndex);
#else
	m_MonsterIndexMtlist.push_back(clientIndex);
#endif
	m_MonsterIndexMtlist.unlock();

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMapBlock::DeleteMonster
// 반환되는 형  : void
// 함 수 인 자  : ClientIndex_t clientIndex
// 함 수 설 명  : MapBlock의 몬스터 인덱스 리스트에서 clientIndex를 삭제한다.
BOOL CMapBlock::DeleteMonster(ClientIndex_t clientIndex)
{	
#ifdef _DEBUG
	assert(clientIndex >= MONSTER_CLIENT_INDEX_START_NUM);
	m_MonsterIndexMtlist.lock();
	mtlistUnitIndex_t::iterator itr = find(m_MonsterIndexMtlist.begin(), m_MonsterIndexMtlist.end(), clientIndex);
	if(itr == m_MonsterIndexMtlist.end())
	{
		char szSystemLog[256];
		sprintf(szSystemLog, "====> DeleteMonster Error Index[%5d]\r\n", clientIndex);
		g_pGlobal->WriteSystemLog(szSystemLog);
		DBGOUT(szSystemLog);
		m_MonsterIndexMtlist.unlock();
		return FALSE;
	}
	m_MonsterIndexMtlist.erase(remove(m_MonsterIndexMtlist.begin(), m_MonsterIndexMtlist.end(), clientIndex)
		, m_MonsterIndexMtlist.end());
	m_MonsterIndexMtlist.unlock();
#else
	m_MonsterIndexMtlist.lock();
	m_MonsterIndexMtlist.erase(remove(m_MonsterIndexMtlist.begin(), m_MonsterIndexMtlist.end(), clientIndex)
		, m_MonsterIndexMtlist.end());
	m_MonsterIndexMtlist.unlock();
#endif
	
	return TRUE;
}

int CMapBlock::GetNumCharachter()
{
	return m_CharacterIndexMtlist.size();
}

int CMapBlock::GetNumMonster()
{
	return m_MonsterIndexMtlist.size();
}

int CMapBlock::GetNumItem()
{
	return m_DropItemMtmap.size();
}

#endif
