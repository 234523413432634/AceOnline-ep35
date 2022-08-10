#ifndef _ATUM_FIELD_MAP_CHANNEL_H_
#define _ATUM_FIELD_MAP_CHANNEL_H_

#include "MapChannel.h"
#include "FieldMapProject.h"
#include "FieldMonster.h"

typedef mt_map<UID32_t, CFieldIOCPSocket*>					mtmapUID2FieldIOCPSocket;

///////////////////////////////////////////////////////////////////////////////
/// \class		CFieldMapChannel
///
/// \brief		Map�� ���� ����Ÿ ����: Characters, Monsters, DropItems ��
/// \author		kelovon
/// \version
/// \date		2004-03-24 ~ 2004-03-24
/// \warning
///////////////////////////////////////////////////////////////////////////////
class CRacing;
class CCityWar;
class CFieldMapChannel : public CMapChannel
{
public:
	CFieldMapChannel(CFieldMapWorkspace *i_pWorkspace, CFieldMapProject *i_pProject, ChannelIndex_t i_nChannelIndex);
	virtual ~CFieldMapChannel();

	int GetExactCharacterIndexes(vector<ClientIndex_t> *o_pClientIndexVector, D3DXVECTOR3 *i_pVec3Pos, float i_fRadius, ClientIndex_t i_nClientIndexToExclude = INVALID_CLIENT_INDEX);
	int GetExactMonsterIndexes(vector<ClientIndex_t> *o_pClientIndexVector, D3DXVECTOR3 *i_pVec3Pos, float i_fRadius);

	// DropItem ���� ���� �Լ�
	void DeleteDropItem(float x, float z, ITEM_GENERAL* pStoreItem);
	void DeleteDropItem(D3DXVECTOR3 pos, ITEM_GENERAL* pStoreItem);	// y��ǥ�� ���õ�
	void DeleteDropItem(CMapBlock *pBlock, ITEM_GENERAL* pStoreItem);

	// moster ����
	CFieldMonster *GetFieldMonster(ClientIndex_t i_MonsterIndex, int i_nTestIdx);
	BOOL FieldOnMonsterCreate(MSG_FN_MONSTER_CREATE *pMonsterCreate);
	void FieldDeleteAllMonster(void);
	BOOL FieldOnMonsterDelete(MSG_FN_MONSTER_DELETE *pMonsterDelete);
	BOOL FieldOnMonsterMove(MSG_FN_MONSTER_MOVE *pMove);
	BOOL FieldOnGetCharacterInfo(MSG_FN_GET_CHARACTER_INFO * i_pGetCInfo);
	BOOL FieldOnMissileMove(MSG_FN_MISSILE_MOVE * i_pMissileMove);
	BOOL FieldOnMonsterHPRecovery(MSG_FN_MONSTER_HPRECOVERY * i_pHPRecovery);
	BOOL FieldOnMonsterHide(MSG_FN_MONSTER_HIDE * i_pMonHide);
	BOOL FieldOnMonsterShow(MSG_FN_MONSTER_SHOW * i_pMonShow);
	BOOL FieldOnBattleAttackPrimary(MSG_FN_BATTLE_ATTACK_PRIMARY * i_pAttackPri);
	BOOL FieldOnBattleAttackSecondary(MSG_FN_BATTLE_ATTACK_SECONDARY * i_pAttackSec);
	BOOL FieldOnBattleAttackFind(MSG_FN_BATTLE_ATTACK_FIND * i_pAttackFind);
	BOOL FieldOnMonsterChangeBodycondition(MSG_FN_MONSTER_CHANGE_BODYCONDITION * i_pChangeBody);
	BOOL FieldOnMonsterSkillUseSkill(MSG_FN_MONSTER_SKILL_USE_SKILL * i_pUseSkill);
	BOOL FieldOnMonsterSkillEndSkill(MSG_FN_MONSTER_SKILL_END_SKILL * i_pEndSkill);
	BOOL FieldSendMonsterChangeInfo(CFieldMonster * i_ptmFMonster, int i_nChangeType);
	BOOL FieldOnMonsterAutoDestroyed(MSG_FN_MONSTER_AUTO_DESTROYED * i_pAutoDestroyed);
	BOOL FieldOnMonsterChangeOk(MSG_FN_MONSTER_CHANGE_OK *pMonsterChangeOk);		// 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�

	void OnMonsterDeadFieldMapChannel(CFieldMonster *i_pFMonster);
// 2005-12-17 by cmkwon, ���� �� AttackTime ������ ���� NPC Server ���� ó���ϵ���  ������
//	void BattleAttackOnMonsterDead(CFieldMonster *i_pFMonster);

	// NPC ���� ����
	BOOL Send2NPCServerW(BYTE *pData, int nSize);
	BOOL SendBodyCondition2NPCServer(ClientIndex_t clientIndex, BodyCond_t bodyCon);

	// ���� ä�ο� �ִ� ĳ���͵� ��ο��� MSG ������
	// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - CFieldMapChannel::SendMessageToAllInChannel#, �����߰�(i_nStartCityMapIdx)
	void SendMessageToAllInChannel(BYTE *buffer, int size, BYTE i_byInfluenceMask=INFLUENCE_TYPE_ALL_MASK, MapIndex_t i_nStartCityMapIdx=VCN_CITY_MAP_INDEX);
	void SendString128ToAllInChannel(BYTE string128_type, char *szString);

	// ���� ä�ο� �ִ� ĳ���͸� ��� Ư�� ���ø����� ������Ų��
	BOOL WarpToCityMapFieldMapChannel(MapIndex_t i_cityMapIndex, UID32_t i_excludeGuildUID);
	BOOL WarpToCityMapFieldMapChannelByInfluence(BYTE i_byexcludeInfuence);		// 2007-08-20 by dhjin, ���� ���� ���� ��� ������ ����.
	BOOL WarpToCityMapFieldMapChannelByGuildUID(UID32_t i_nexcludeGuildUID);	// 2007-08-20 by dhjin, ���� ��� ���� ��� ������ ����.
	BOOL WarpToOutPostCityMapFieldMapChannelByGuildUID(UID32_t i_nGuildUID, int i_nMapindex);	// 2007-08-20 by dhjin, �������� ���� ���ܿ� �������� ���� ������ ����.
	BOOL WarpToCityMap(UID32_t i_excludeCharacterUID);


	// ������ ����
	int InsertItemInMap(INT i_nItemNum, INT i_nItemCount, BYTE i_byInflMask=INFLUENCE_TYPE_ALL_MASK);

	// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - CFieldMapChannel::AddWarPointInMap()�� ����(, BYTE i_byWPUpdateTy=WPUT_GENERAL) �߰�
	int AddWarPointInMap(INT i_nAddWarPoint, BOOL i_bEventBonus, BYTE i_byInflMask=INFLUENCE_TYPE_ALL_MASK, BYTE i_byWPUpdateTy=WPUT_GENERAL);				// 2007-06-14 by cmkwon, ������ ���� ���� - 

	// CMapProject�� wrapper �Լ�
	inline EVENTINFO* GetTileEventInfoW(const D3DXVECTOR3 *pPosVector3);

	// CFieldMapProject�� wrapper �Լ�
	CFieldMapProject* GetDeadDefaultMapProjectW() {			return m_pFieldMapProject->GetDeadDefaultMapProject(); }
	MapIndex_t GetDeadDefaultMapIndexW() {					return m_pFieldMapProject->GetDeadDefaultMapIndex(); }
	inline D3DXVECTOR3 GetDefaultPointW() {					return m_pFieldMapProject->GetDefaultPoint(); } // position vector�� �� �� �Ǿ��� �� Ȥ�� �׾��� ��, �⺻ ��ġ�� �˱� ����
	BOOL IsCheckUserCountForWarp(CFieldIOCPSocket *i_pFISock);

	EVENTINFO *GetEventInfoByObjectTypeAndDistanceW(DWORD i_dwObjType, D3DXVECTOR3 *i_pVec3Position)
	{
		return m_pFieldMapProject->GetEventInfoByObjectTypeAndDistance(i_dwObjType, i_pVec3Position);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// \fn			EVENTINFO *GetEventInfoByMinimumDistanceW(EventType_t i_eventTy, D3DXVECTOR3 *i_pVec3Position)
	/// \brief		
	/// \author		cmkwon
	/// \date		2005-12-12 ~ 2005-12-12
	/// \warning	
	///
	/// \param		
	/// \return		
	///////////////////////////////////////////////////////////////////////////////
	EVENTINFO *GetEventInfoByMinimumDistanceW(EventType_t i_eventTy, D3DXVECTOR3 *i_pVec3Position)
	{
		return m_pFieldMapProject->GetEventInfoByMinimumDistance(i_eventTy, i_pVec3Position);
	}

	///////////////////////////////////////////////////////////////////////////
	// Property
	DWORD GetModulusNumberTotalNetworkState(void){		return m_dwModulusNumberTotalNetworkState;}
	DWORD GetMaxUserCountsChannel(void){					return m_dwMaxUserCountsChannel;}
	
	void AddMapSendTraffic(int nSendBytes, int nSendCounts);

	// ���� Bandwidth ���
	void CalcMapTotalTraffic(void);
	void LockMapTraffic(void){			EnterCriticalSection(&m_crtlMapTraffic);};
	void UnlockMapTraffic(void){		LeaveCriticalSection(&m_crtlMapTraffic);};

	INT GetCrowdedness(void);
	int GetUserCounts(BYTE i_byInflTyMask, BYTE i_byMinLevel, BYTE i_byMaxLevel);

	void ProcessRacing(struct tm *i_pRealTime);
	void InRacingWaitingRoom(CFieldIOCPSocket *i_pFSocket);	
	void OutRacingSystem(CFieldIOCPSocket *i_pFSocket);
	int JoinRacing(CFieldIOCPSocket *i_pFSocket);
	BOOL IsJoinedUser(CFieldIOCPSocket *i_pFSocket);
	BOOL CheckPointCheck(CFieldIOCPSocket *i_pFSocket, BYTE i_byCheckPointIndex);

	BOOL MakeRacingMessage(MessageType_t i_msgType, void *o_pMsg);

	void SetCityWarFieldMapChannel(CCityWar *i_pCityWar);
	BOOL MakeMSG_FC_CITYWAR_GET_OCCUPYINFO_OK(MSG_FC_CITYWAR_GET_OCCUPYINFO_OK *o_pOccupyInfo, UID32_t i_guildUID);
	Err_t SetCityWarSettingTimeFieldMapChannel(ATUM_DATE_TIME *i_pSetTime, UID32_t i_guildUID, UID32_t i_charUID);
	Err_t SetCityWarTexFieldMapChannel(float i_fSetTex, UID32_t i_guildUID, UID32_t i_charUID);
	Err_t SetCityWarBriefingFieldMapChannel(char *i_szSetBriefing, UID32_t i_guildUID, UID32_t i_charUID);
	Err_t CityWarBringSumOfTex(int *o_pnBringTex, UID32_t i_guildUID, UID32_t i_charUID);
	float CityWarGetTexPercent(int i_nBuildingIdx, UID32_t i_guildUID);
	int CityWarAddTex(int i_nTex);

	///////////////////////////////////////////////////////////////////////////////	
	// 2006-11-21 by cmkwon, ��������Ʈ ���� ����
	void SetLastTickStrategyPointMonsterDeaded(DWORD i_dwTick);
	BOOL IsOccupyStrategyPointMonster(void);

	//////////////////////////////////////////////////////////////////////////
	// 2007-09-05 by dhjin, �ڷ���Ʈ ���� �߰�
	void SetTelePortState(int i_nTelePortState);		// 2007-09-05 by dhjin, �ڷ���Ʈ ���� �� ����.
	int GetTelePortState();								// 2007-09-05 by dhjin, �ڷ���Ʈ ���� �� ������.
	BOOL IsInvincibleTelePortState(void);				// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - 
	void SetTelePortSummonFirst(BOOL i_bTelePortSummonFirst);	// 2007-11-06 by dhjin, �ڷ���Ʈ ó�� ��ȯ �� �������� üũ
	BOOL GetTelePortSummonFirst();						// 2007-11-06 by dhjin. �ڷ���Ʈ ó�� ��ȯ �� �������� �� ������

	//////////////////////////////////////////////////////////////////////////
	// 2008-03-10 by dhjin, �Ʒ��� ���� - 
	void InitmapCharacterUniqueNumberMapProject();		// 2008-03-10 by dhjin, �Ʒ��� ���� - ���� �ʿ��� �������� ĳ���͵��� ����Ʈ �ʱ�ȭ
	void TeamArenaLeaveCommand(BYTE i_byInflMask);		// 2008-03-12 by dhjin, �Ʒ��� ���� - ���� �ʿ� ���� �� ���� ���� ��θ� ���� ������ ������.

	//////////////////////////////////////////////////////////////////////////
	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) -	
	void CreateKeyMonster(CFieldMonster	*i_pKeyMonster);

// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - 
//	void DeleteKeyMonster(CMonster	*i_pKeyMonster);
	void OnInfinityMonsterDead(CFieldMonster *i_pFMon);

	BOOL SetKeyMonsterClientIdx_AliveForGameClear(CFieldMonster	*i_pKeyMonster);	
	BOOL PenaltyKeyMonster_AliveForGameClear(char * i_szCharacterName, int i_PenaltyValue);
	void DeadKeyMonsterClientIdx_AliveForGameClear();
	void SendKeyMonsterHP_AliveForGameClear(CFieldIOCPSocket * i_pFISoc);

	///////////////////////////////////////////////////////////////////////////
	// virtual
	virtual BOOL InitMapChannel(void);

#ifdef _DEBUG
	// ������
	char* DBG_GET_CHARACTER_NAME(int idx);
	float DBG_GET_X_POSITION(int idx);
	float DBG_GET_Y_POSITION(int idx);
	float DBG_GET_Z_POSITION(int idx);
	void DBG_PrintAllUnitPosition(void);
#endif // _DEBUG_endif

public:
	CFieldMapWorkspace	*m_pFieldMapWorkspace;
	CFieldMapProject	*m_pFieldMapProject;
	CFieldIOCP			*m_pFieldIOCPMapChannel;

	mtmapUID2FieldIOCPSocket	m_mapCharacterUniqueNumberMapProject;	// ���� �ʿ��� �������� ĳ���͵��� ����Ʈ

protected:
	EN_NETWORK_STATE		m_enTotalNetworkState;						// IOCPServer Network State �� Map Network State �� ���� �Ѱ�
	DWORD					m_dwModulusNumberTotalNetworkState;

	DWORD					m_dwMaxUserCountsChannel;					// 2004-11-22 by cmkwon, ä�κ� MaxUserCounts <--// ä�κ��� MaxBandwidth�� ���� �����Ҽ� �ְ� ä�κ��� ��� ������ �д�
	CRITICAL_SECTION		m_crtlMapTraffic;
	STrafficInfo			m_MapTraffic[2];

	CFieldMonster			*m_ArrFieldMonster;
	CRacing					*m_pRacing;

	INT						m_TelePortState;						// 2007-09-05 by dhjin, �ڷ���Ʈ �ý��� ���°�.
	DWORD					m_dwTeleportStateChangedTick;			// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - 
	BOOL					m_TelePortSummonFirst;					// 2007-11-06 by dhjin, �ڷ���Ʈ�� ��ȯ �Ǹ� �ʱⰪ�� TRUE�� �����Ѵ�.

	CFieldMonster			*pKeyMonster_AliveForGameClear;			// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - �ش� ���Ͱ� ������ ���Ǵ�Ƽ ����

public:
	CCityWar				*m_pRefCityWar1;

	DWORD					m_dwLastTickVCNInfluenceAttackedMsg;	// 2005-12-28 by cmkwon, ������������ ���ݴ��ϴ� �޽����� ���� ������ �ð�
	DWORD					m_dwLastTickANIInfluenceAttackedMsg;	// 2005-12-28 by cmkwon, �˸����� ���ݴ��ϴ� �޽����� ���� ������ �ð�

	DWORD					m_dwLastTickStrategyPointMonsterDeaded;	// 2006-11-21 by cmkwon, ��������Ʈ ���� ���� �ð�
	BOOL					m_bStrategyPointMonsterDeaded;			// 2007-01-25 by cmkwon, ��������Ʈ ���� ���� �÷���

	ClientIndex_t			m_ChangeBodyConMonsterIndex;			// 2007-09-10 by dhjin,	�ٵ� ������� BODYCON_MON_BUILDING => BODYCON_MON_BUILDED ���°� �ʿ��� ���� ���� ����. ���� �����Ѵ�. ������ �� �ʿ� �� ���� ���̾���.
};


EVENTINFO* CFieldMapChannel::GetTileEventInfoW(const D3DXVECTOR3 *pPosVector3)
{
	return m_pFieldMapProject->GetTileEventInfo(pPosVector3);
}


#endif //_ATUM_MAP_FIELD_CHANNEL_H_
