// FieldMapProject.h: interface for the CFieldMapProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDMAPPROJECT_H__A2E572D2_32EF_46A9_B701_F89F32D50966__INCLUDED_)
#define AFX_FIELDMAPPROJECT_H__A2E572D2_32EF_46A9_B701_F89F32D50966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IOCP.h"
#include "MapProject.h"
#include "AtumProtocol.h"

#define MAX_MODULUS_NUMBER_TOTAL_NETWORK_STATE			10
#define MIN_MODULUS_NUMBER_TOTAL_NETWORK_STATE			3

typedef vector<SHOP_ITEM>	vectSHOP_ITEM;				// 2006-10-20 by cmkwon
class CShopInfo
{
public:
	SHOP_ITEM *GetSHOP_ITEMPtr(int i_itemNum);
	SHOP_ITEM *GetSHOP_ITEMPtrFrombuffer(int i_itemNum);	// 2010-01-26 by cmkwon, 캐쉬 아이템 한정판매 시스템 구현 - 

// 2006-10-20 by cmkwon
//	map<UINT, SHOP_ITEM>	m_mapShopItem;			// ItemNum -> SHOP_ITEM
	vectSHOP_ITEM			m_vectShopItemList;		// 2006-10-20 by cmkwon
	GBUFFER					m_buffer;
};

typedef vector<WARP_TARGET_MAP_INFO_4_EXCHANGE>		 vectWARP_TARGET_MAP_INFO_4_EXCHANGE;		// 2007-01-29 by cmkwon

struct S_S1_CHARACTER_INFO		// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 구조체 추가
{
	UID32_t			CharacterUID1;
	char			CharacterName1[SIZE_MAX_CHARACTER_NAME];
};
typedef mt_vector<S_S1_CHARACTER_INFO>			mtvectS_S1_CHARACTER_INFO;		// 2007-08-30 by cmkwon, 회의룸 시스템 구현 -

///////////////////////////////////////////////////////////////////////////////
/// \class		CFieldMapProject
///
/// \brief
/// \author		cmkwon
/// \version
/// \date		2004-03-26 ~ 2004-03-26
/// \warning
///////////////////////////////////////////////////////////////////////////////
class CFieldMapChannel;
class CFieldMonster;
class CCityWar;
class CLocalization;
class CODBCStatement;
class CFieldMapProject : public CMapProject
{
public:
	CFieldMapProject(CMapWorkspace * i_pMapWorkspace, PROJECTINFO * i_pProjectInfo);
	virtual ~CFieldMapProject();

	void SetNPCServerStartFlag(BOOL i_bStartFlag);
	BOOL GetNPCServerStartFlag(void);

	BOOL LoadBUILDINGNPC(CODBCStatement *i_pOdbcStmt, CLocalization *i_pLocalization);			// 현재 맵에 속한 건물 및 담당 NPC의 정보를 loading
	BOOL LoadShopInfo(CODBCStatement *i_pOdbcStmt, CLocalization *i_pLocalization);			// 현재 맵에 속한 상점의 판매 아이템을 미리 loading
	BOOL LoadCityTargetWarpMap(CODBCStatement *i_pOdbcStmt);	// 도시에서 워프해나갈 수 있는 맵의 리스트를 미리 loading
	BOOL LoadWarpableUserList(CODBCStatement *i_pOdbcStmt);		// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 로딩 함수 추가

	// 캐릭이 죽었을 때 가야하는 default map과 관련
	BOOL SetDeadDefaultMap(void);
	CFieldMapProject* GetDeadDefaultMapProject(void);
	MapIndex_t GetDeadDefaultMapIndex(void);

	// Warp 관련
	D3DXVECTOR3 GetDefaultPoint(void); // position vector가 잘 못 되었을 때 혹은 죽었을 때, 기본 위치를 알기 위해
	EVENTINFO* GetEventInfoByWarpIndex(int WarpIndex);
	D3DXVECTOR3 GetRandomWarpPoint(int EventAreaIndex);
	void GetRandomPositionInRadius(D3DXVECTOR3 *In, D3DXVECTOR3 *Out, float Radius);
	EVENTINFO *GetEventInfoByObjectTypeAndDistance(DWORD i_dwObjType, D3DXVECTOR3 *i_pVec3Position);
	OBJECTINFOSERVER *GetRandomObjectInfoServerPtrByEventIndex(short i_sEventIndex);
	EVENTINFO *GetEventInfoByMinimumDistance(EventType_t i_eventTy, D3DXVECTOR3 *i_pVec3Position);
	int GetRandomWarpTargetEventIndex(void);

	WARP_TARGET_MAP_INFO_4_EXCHANGE *GetWarpInfoByTargetMapIndex(MapIndex_t i_mapIdx);


	BOOL ResetAllChannel(void);
	BOOL FieldOnMonsterCreateW(MSG_FN_MONSTER_CREATE * i_pMonCreate);
	BOOL FieldOnMonsterDeleteW(MSG_FN_MONSTER_DELETE * i_pMonDelete);
	BOOL FieldOnMonsterMoveW(MSG_FN_MONSTER_MOVE * i_pMonMove);
	BOOL FieldOnGetCharacterInfoW(MSG_FN_GET_CHARACTER_INFO * i_pGetCInfo);
	BOOL FieldOnMissileMoveW(MSG_FN_MISSILE_MOVE * i_pMissileMove);
	BOOL FieldOnMonsterHPRecoveryW(MSG_FN_MONSTER_HPRECOVERY * i_pHPRecovery);
	BOOL FieldOnMonsterHideW(MSG_FN_MONSTER_HIDE * i_pMonHide);
	BOOL FieldOnMonsterShowW(MSG_FN_MONSTER_SHOW * i_pMonShow);
	BOOL FieldOnBattleAttackPrimaryW(MSG_FN_BATTLE_ATTACK_PRIMARY * i_pAttackPri);
	BOOL FieldOnBattleAttackSecondaryW(MSG_FN_BATTLE_ATTACK_SECONDARY * i_pAttackSec);
	BOOL FieldOnBattleAttackFindW(MSG_FN_BATTLE_ATTACK_FIND * i_pAttackFind);
	BOOL FieldOnMonsterChangeBodyconditionW(MSG_FN_MONSTER_CHANGE_BODYCONDITION * i_pChangeBody);
	BOOL FieldOnMonsterSkillUseSkillW(MSG_FN_MONSTER_SKILL_USE_SKILL * i_pUseSkill);
	BOOL FieldOnMonsterSkillEndSkillW(MSG_FN_MONSTER_SKILL_END_SKILL * i_pEndSkill);
	BOOL FieldOnMonsterAutoDestroyedW(MSG_FN_MONSTER_AUTO_DESTROYED * i_pAutoDestroyed);
	BOOL FieldOnMonsterChangeOkW(MSG_FN_MONSTER_CHANGE_OK * i_pMonChangeOk);		// 2011-05-11 by hskim, 인피니티 3차 - 시네마 관련 기능 추가 - 해당 맵채널 특정 몬스터 변경 기능 추가

	CFieldMonster * GetFieldMonsterW(ChannelIndex_t i_channIdx, ClientIndex_t i_monsterIdx, int i_nTestIdx);

	// 이동 가능 좌표인지 체크
	BOOL CheckCharacterPosition(D3DXVECTOR3 *pPosVector3, BOOL bFlagChangeableHeight);

	// 날씨 변경
	BOOL ChangeWeather(BitFlag16_t weather, BOOL bOnOff);

	// NPC 서버에 전송
	BOOL Send2NPCServer(BYTE *pData, int nSize);
	BOOL SendDelayBuffer2NPCFerver(void);

	// 같은 맵에 있는 캐릭터들 모두에게 MSG 보내기
	// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - SendMessageToAllInAllMapChannels, 인자추가(i_nStartCityMapIdx)
	void SendMessageToAllInAllMapChannels(BYTE *buffer, int size, BYTE i_byInfluenceMask=INFLUENCE_TYPE_ALL_MASK, MapIndex_t i_nStartCityMapIdx=VCN_CITY_MAP_INDEX);
	void SendSummonMessageToAllChannels(MSG_FN_ADMIN_SUMMON_MONSTER *i_pSummonMonster);

	CFieldMapChannel *GetFieldMapChannelByIndex(int i_nIndex, BOOL i_bOnlyEnabledChannel=FALSE);
	CFieldMapChannel *GetRandomFieldMapChannel(BOOL i_bOnlyEnabledChannel);
	CFieldMapChannel *GetFirstFieldMapChannel(BOOL i_bOnlyEnabledChannel);
// 2004-12-07 by cmkwon, 채널 실시간 증가가 없어 필요없는 함수
//	CFieldMapChannel *GetLastFieldMapChannel(BOOL i_bOnlyEnabledChannel);
	void MakeMsg_AllChannelState(int *o_pChannelCounts, MSG_FN_CONNECT_SET_CHANNEL_STATE *o_pChannelState);
	void OnDoMinutelyWorkFieldMapProject(void);
	void OnDoSecondlyWorkFieldMapProject(ATUM_DATE_TIME *pDateTime);
	BOOL IsMultiMapChannel(BYTE i_byCharInflTy);

	///////////////////////////////////////////////////////////////////////////
	// virtual
	// 초기화 관련, 2004-03-26 by cmkwon
	virtual BOOL InitMapProject(void);

	// 채널 관련, added by kelovon, 20040324
	virtual BOOL InitializeMapChannels(int i_nChannel);
	virtual BOOL CleanMapChannels();
	virtual BOOL IncreaseMapChannels(int i_nChannelToAdd);

	void SetCityWarFieldMapProject(CCityWar *i_pCityWar);
	BYTE GetCityWarTeamTypeByGuildUID(UID32_t i_guildUID);
	BOOL IsCityWarStarted(void); 
// 2005-12-28 by cmkwon, 사용하지 않음
//	BOOL IsCheckQuestForWarp(CFieldIOCPSocket *i_pFISock);

	///////////////////////////////////////////////////////////////////////////////
	// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - CFieldMapProject에 멤버 함수 추가
	S_S1_CHARACTER_INFO *FindInWarpableUserList(UID32_t i_charUID);
	BOOL FindInWarpableUserListByCharacterName(S_S1_CHARACTER_INFO *o_ps1CharInfo, char *i_szCharName);
	BOOL InsertWarpableUserList(UID32_t i_charUID, char *i_szCharName);
	BOOL PopInWarpableUserListByCharacterName(S_S1_CHARACTER_INFO *o_ps1CharInfo, char *i_szCharName);
	BOOL IsWarpableUser(UID32_t i_charUID, USHORT i_usRace);
	BOOL SendWarpableUserList(CFieldIOCPSocket *i_pFISoc);
	static INT GetConferenceRoomMapIndex(BYTE i_byCharInflTy);

public:
	map<UINT, CShopInfo*>		m_mapShopInfo;								// BuildingIndex -> CShopInfo
	CFieldMapProject			*m_pDeadDefaultMapProject;					// 캐릭이 죽었을 때 가야하는 default map과 관련
	char						m_szUserFriendlyMapName[SIZE_MAX_MAP_NAME];	// 사용자가 읽을 수 있는 맵 이름
	BitFlag16_t					m_Weather;									// 날씨, WEATHER_XXX

	ez_map<UINT, BUILDINGNPC*>	m_mapBuilding2Building;					// BuildingIndex -> BUILDINGNPC, 건물 및 담당 NPC의 정보, 종료시 memory 해제 필요!
	ez_map<UINT, BUILDINGNPC*>	m_mapNPC2Building;						// NPCIndex -> BUILDINGNPC, 건물 및 담당 NPC의 정보, 종료시 memory 해제 불필요!
	GBUFFER_SIZE_MAX_PACKET		m_buffGetBuildingListOK;				// Previously created message buffer for MSG_FC_CITY_GET_BUILDING_LIST_OK
	GBUFFER_SIZE_MAX_PACKET		m_buffGetWarpTargetMapListOK;			// Previously created message buffer for MSG_FC_CITY_GET_WARP_TARGET_MAP_LIST_OK

// 2007-01-29 by cmkwon, 아래와 같이 수정함
//	list<WARP_TARGET_MAP_INFO_4_EXCHANGE>	m_listCityWarpTargetMapInfo;	// 도시맵일 경우 위프해나갈 수 있는 맵의 정보
	vectWARP_TARGET_MAP_INFO_4_EXCHANGE		m_vectCityWarpInfoList;			// 2007-01-29 by cmkwon

	BOOL						m_bNPCServerStart;			// NPC Server 가 준비 되었는지의 플래그로 T_FN_MAPPROJECT_START_OK_ACK를 받은 후 TRUE로 된다.
	CCityWar					*m_pRefCityWar2;

	int							m_nNextWarpTargetEventIndex;			// 2006-08-03 by cmkwon, 
	CFieldMapWorkspace			*m_pFieldMapWorkspace;

	///////////////////////////////////////////////////////////////////////////////
	// 2007-08-30 by cmkwon, 회의룸 시스템 구현 -
	mtvectS_S1_CHARACTER_INFO	m_mtvectWarpableUserList;		// 2007-08-30 by cmkwon, 회의룸 시스템 구현 - 멤버 변수 추가

	///////////////////////////////////////////////////////////////////////////////
	// 2010-01-26 by cmkwon, 캐쉬 아이템 한정판매 시스템 구현 - 
	BOOL LimitedEUpdate(UINT i_nBuildIdx, vectITEM_W_COUNT *i_pLimitedItemList);
};

#endif // !defined(AFX_FIELDMAPPROJECT_H__A2E572D2_32EF_46A9_B701_F89F32D50966__INCLUDED_)
