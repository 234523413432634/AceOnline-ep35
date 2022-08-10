 #include "StdAfx.h"
#include "FieldMapChannel.h"
#include "FieldIOCP.h"
#include "FieldIOCPSocket.h"
#include "RacingDemon.h"
#include "Racing.h"
#include "AtumError.h"
#include "FieldGlobal.h"
#include "EXPDivisionManager.h"		// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - 

CFieldMapChannel::CFieldMapChannel(CFieldMapWorkspace *i_pWorkspace,
								   CFieldMapProject *i_pProject,
								   ChannelIndex_t i_nChannelIndex)
	: CMapChannel(i_pWorkspace, i_pProject, i_nChannelIndex)
{
	m_pFieldMapWorkspace				= i_pWorkspace;
	m_pFieldMapProject					= i_pProject;
	m_dwMaxUserCountsChannel			= m_pFieldMapProject->m_dwMaxUserCounts;
	m_pFieldIOCPMapChannel				= (CFieldIOCP*)i_pWorkspace->m_pIOCPServer;

	m_mapCharacterUniqueNumberMapProject.clear();

	m_enTotalNetworkState				= EN_NETWORK_STATE_BEST;
	m_dwModulusNumberTotalNetworkState	= MAX_MODULUS_NUMBER_TOTAL_NETWORK_STATE;

	InitializeCriticalSection(&m_crtlMapTraffic);
	MEMSET_ZERO(m_MapTraffic, sizeof(STrafficInfo) * 2);

	m_ArrFieldMonster					= new CFieldMonster[m_nSizemtvectorMonsterPtr];
	m_mtvectorMonsterPtr.lock();
	m_mtvectorMonsterPtr.reserve(m_nSizemtvectorMonsterPtr);
	for(int i = 0;i < m_nSizemtvectorMonsterPtr; i++)
	{
		m_ArrFieldMonster[i].SetMonsterIndex(i + MONSTER_CLIENT_INDEX_START_NUM);
		m_ArrFieldMonster[i].m_pCurrentFieldMapChannelMonster = this;
		m_mtvectorMonsterPtr.push_back(&m_ArrFieldMonster[i]);
	}
	m_mtvectorMonsterPtr.unlock();

	m_pRacing							= NULL;
	m_pRefCityWar1						= NULL;

	m_dwLastTickVCNInfluenceAttackedMsg		= 0;	// 2005-12-28 by cmkwon
	m_dwLastTickANIInfluenceAttackedMsg		= 0;	// 2005-12-28 by cmkwon

	m_dwLastTickStrategyPointMonsterDeaded	= 0;	// 2006-11-21 by cmkwon
	m_bStrategyPointMonsterDeaded			= FALSE;	// 2007-01-25 by cmkwon

	m_TelePortState							= TELEPORT_STATE_NOT_SUMMON;	// 2007-09-05 by dhjin
	m_ChangeBodyConMonsterIndex				= 0;	// 2007-09-10 by dhjin
	m_dwTeleportStateChangedTick			= 0;	// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - 
	m_TelePortSummonFirst					= FALSE;

	pKeyMonster_AliveForGameClear		= NULL;		// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - �ش� ���Ͱ� ������ ���Ǵ�Ƽ ����
}

CFieldMapChannel::~CFieldMapChannel()
{
	m_mapCharacterUniqueNumberMapProject.clear();

	DeleteCriticalSection(&m_crtlMapTraffic);

	SAFE_DELETE_ARRAY(m_ArrFieldMonster);

	SAFE_DELETE(m_pRacing);
}


BOOL CFieldMapChannel::InitMapChannel(void)
{
	CMapChannel::InitMapChannel();

	ResetMapChannel();

	if(IS_RACING_MAP_INDEX(this->m_MapChannelIndex.MapIndex))
	{
		m_pRacing = new CRacing;		
		m_pFieldIOCPMapChannel->m_pRacingDemon->PutRacingMapChannel(this);
	}
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CFieldMapChannel::GetExactCharacterIndexes(vector<ClientIndex_t> *o_pClientIndexVector, D3DXVECTOR3 *i_pVec3Pos, float i_fRadius, ClientIndex_t i_nClientIndexToExclude/*=INVALID_CLIENT_INDEX*/)
/// \brief		
/// \author		dhjin
/// \date		2006-11-27 ~ 2006-11-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CFieldMapChannel::GetExactCharacterIndexes(vector<ClientIndex_t> *o_pClientIndexVector, D3DXVECTOR3 *i_pVec3Pos, float i_fRadius, ClientIndex_t i_nClientIndexToExclude/*=INVALID_CLIENT_INDEX*/)
{
	this->GetAdjacentCharacterIndexes(i_pVec3Pos, 2*i_fRadius, o_pClientIndexVector, i_nClientIndexToExclude);

	if(o_pClientIndexVector->empty())
	{
		return 0;
	}

	vectClientIndex_t::iterator itr = o_pClientIndexVector->begin();
	while(itr != o_pClientIndexVector->end())
	{
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(*itr);
		if(NULL == pFISock
			|| FALSE == pFISock->IsValidCharacter(FALSE)
			|| i_fRadius < D3DXVec3Length(&(*i_pVec3Pos - pFISock->GetCharacter()->PositionVector)))
		{
			itr = o_pClientIndexVector->erase(itr);
			continue;
		}
//		char szTemp[1024];
//		sprintf(szTemp, "ExactCharacter CharacterName(%s) Distance(%5.2f) Pos(%5.2f, %5.2f, %5.2f)\r\n"
//			, pFISock->GetCharacter()->CharacterName, D3DXVec3Length(&(*i_pVec3Pos - pFISock->GetCharacter()->PositionVector))
//			, i_pVec3Pos->x, i_pVec3Pos->y, i_pVec3Pos->z);
//		DBGOUT(szTemp);

		itr++;
	}

	return o_pClientIndexVector->size();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CFieldMapChannel::GetExactMonsterIndexes(vector<ClientIndex_t> *o_pClientIndexVector, D3DXVECTOR3 *i_pVec3Pos, float i_fRadius)
/// \brief		
/// \author		dhjin
/// \date		2006-12-01 ~ 2006-12-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CFieldMapChannel::GetExactMonsterIndexes(vector<ClientIndex_t> *o_pClientIndexVector, D3DXVECTOR3 *i_pVec3Pos, float i_fRadius)
{
	this->GetAdjacentMonsterIndexes(i_pVec3Pos, 2*i_fRadius, o_pClientIndexVector);
	if(o_pClientIndexVector->empty())
	{
		return 0;
	}

	vectClientIndex_t::iterator itr(o_pClientIndexVector->begin());
	while(itr != o_pClientIndexVector->end())
	{
		CFieldMonster	*pFMon = GetFieldMonster(*itr, 30);		
		if(NULL == pFMon
			|| FALSE == pFMon->IsValidMonster()
			|| i_fRadius < D3DXVec3Length(&(*i_pVec3Pos - pFMon->PositionVector)))
		{
			itr = o_pClientIndexVector->erase(itr);
			continue;
		}
//		char szTemp[1024];
//		sprintf(szTemp, "ExactCharacter MonsterIndex(%d) Distance(%5.2f) Pos(%5.2f, %5.2f, %5.2f)\r\n"
//			, pFMon->MonsterIndex, D3DXVec3Length(&(*i_pVec3Pos - pFMon->PositionVector))
//			, i_pVec3Pos->x, i_pVec3Pos->y, i_pVec3Pos->z);
//		DBGOUT(szTemp);
		itr++;
	}
	return o_pClientIndexVector->size();
}

void CFieldMapChannel::DeleteDropItem(float x, float z, ITEM_GENERAL* pStoreItem)
{
	CMapBlock *pBlock = GetBlock(x, z);
	pBlock->DeleteDropItem(pStoreItem);
/*
#ifdef _DEBUG
DBGOUT("DeleteDropItem From MapProject: %x[%d][%d]\n", pStoreItem, pBlock->m_x, pBlock->m_z);
#endif
*/
}

void CFieldMapChannel::DeleteDropItem(D3DXVECTOR3 pos, ITEM_GENERAL* pStoreItem)
{
	DeleteDropItem(pos.x, pos.z, pStoreItem);
}

void CFieldMapChannel::DeleteDropItem(CMapBlock *pBlock, ITEM_GENERAL* pStoreItem)
{
	pBlock->DeleteDropItem(pStoreItem);
}

CFieldMonster *CFieldMapChannel::GetFieldMonster(ClientIndex_t i_MonsterIndex, int i_nTestIdx)
{
	int mIdx = i_MonsterIndex - MONSTER_CLIENT_INDEX_START_NUM;
	if(FALSE == IS_VALID_ARRAY_INDEX(mIdx, m_nSizemtvectorMonsterPtr))
	{
		DBGOUT("[ERROR] CFieldMapChannel::GetFieldMonster_1 MonsterIndex Error, Map(%s) MaxMonsterIndex(%d), InputMonsterIndex(%d) ==> TestIndex(%d)\n"
			, GET_MAP_STRING(m_MapChannelIndex), m_nSizemtvectorMonsterPtr + MONSTER_CLIENT_INDEX_START_NUM, i_MonsterIndex, i_nTestIdx);
		return NULL;
	}

	return m_ArrFieldMonster + mIdx;
}

BOOL CFieldMapChannel::FieldOnMonsterCreate(MSG_FN_MONSTER_CREATE *pMonsterCreate)
{
	ASSERT_ASSERT(pMonsterCreate);

	CFieldMonster	*pMonster = GetFieldMonster(pMonsterCreate->MonsterIndex, 10);
	if(NULL == pMonster || pMonster->m_enMonsterState != MS_NULL){		return FALSE;}

	ez_map<INT, MONSTER_INFO>::iterator itrMon = m_pFieldIOCPMapChannel->m_mapMonsterInfo.find(pMonsterCreate->MonsterUnitKind);
	if (itrMon == m_pFieldIOCPMapChannel->m_mapMonsterInfo.end())
	{
		// check: error
		ASSERT_NEVER_GET_HERE();
		return FALSE;
	}

	MONSTER_INFO &tmpMonsterInfo = itrMon->second;
	m_mtvectorMonsterPtr.lock();
	// from MonsterInfo
	pMonster->SetMonsterInfoPtr(&itrMon->second);

// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
	//pMonster->CurrentHP					= itrMon->second.MonsterHP;		// Current �Ҵ�

	// ������ ������ Ȯ�� ����. 
	pMonster->SetMonsterInfoExtend_AllData ( &pMonsterCreate->MonsterBalanceData );
	
	pMonster->CurrentHP					= pMonster->MonsterInfoExtend.fMaxHP;		// Current �Ҵ�
// End 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )

	// from MSG_FN_MONSTER_CREATE
	pMonster->m_enMonsterState			= MS_PLAYING;
	pMonster->BodyCondition				= pMonsterCreate->BodyCondition;
	pMonster->PositionVector			= A2DX(pMonsterCreate->PositionVector);
	D3DXVec3Normalize(&pMonster->TargetVector, &(A2DX(pMonsterCreate->TargetVector)));
	pMonster->m_dwTimeCreatedTick		= GetTickCount();							// ���� ���� �ð����� ��Ȯ�� ����� �ʿ� �����Ƿ� GetTickCount()�� �����
	pMonster->m_byObjectMonsterType		= pMonsterCreate->ObjectMonsterType;
	pMonster->m_byMonsterTargetType		= pMonsterCreate->MonsterTargetType1;
	pMonster->m_nTargetTypeData			= pMonsterCreate->TargetTypeData1;

	if(0 != pMonsterCreate->CltIdxForTargetType1)
	{
		pMonster->m_mtvectClientIdxForTargetType.pushBackLock(pMonsterCreate->CltIdxForTargetType1);
	}
	m_mtvectorMonsterPtr.unlock();

	///////////////////////////////////////////////////////////////////////////////
	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - �ذ� ���� ����
// 	////////////////////////////////////////////////////////////////////////////////
// 	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Key ���� ���� 
// 	if(TRUE == g_pFieldGlobal->IsArenaServer()
// 		&& COMPARE_MPOPTION_BIT(pMonster->MonsterInfoPtr->MPOption, MPOPTION_BIT_KEY_MONSTER)) {
// 		this->m_pFieldIOCPMapChannel->m_InfinityManager.CreateKeyMonster_DeadForNextStepW(this->m_MapChannelIndex.MapIndex, this->m_MapChannelIndex.ChannelIndex, pMonster->MonsterInfoPtr->MonsterUnitKind);
// 	}
	if(TRUE == g_pFieldGlobal->IsArenaServer())
	{
		this->CreateKeyMonster(pMonster);
	}

	///////////////////////////////////////////////////////////////////////////
	// Block �� �߰�
	if(FALSE == SetInitialPosition(pMonsterCreate->PositionVector.x, pMonsterCreate->PositionVector.z, pMonsterCreate->MonsterIndex))
	{
		char szTemp[256];
		sprintf(szTemp, "[Error] SetInitialPosition_3 Error, MapChannel(%s) UnitIndex(%5d) State(%2d) XZ(%5.0f, %5.0f) \r\n"
			, GET_MAP_STRING(this->m_MapChannelIndex), pMonster->MonsterIndex, pMonster->m_enMonsterState
			, pMonster->PositionVector.x, pMonster->PositionVector.z);
		DBGOUT(szTemp);
		g_pGlobal->WriteSystemLog(szTemp);
	}

//	///////////////////////////////////////////////////////////////////////////
//	// ���Ͱ� ���� �� ����߸� ������ ����, ���� ���� �� ����
//	pMonster->LockDropItemList();
//	pMonster->CreateDropItem(m_pFieldIOCPMapChannel);	// ���� ���� �� ����
//	pMonster->UnlockDropItemList();

	///////////////////////////////////////////////////////////////////////////
	// CreateOK �޼����� NPCServer�� �����Ѵ�.
	INIT_MSG_WITH_BUFFER(MSG_FN_MONSTER_CREATE_OK, T_FN_MONSTER_CREATE_OK, pSendCreateOK, SendBuf);
	pSendCreateOK->ChannelIndex		= pMonsterCreate->ChannelIndex;
	pSendCreateOK->MonsterIndex		= pMonsterCreate->MonsterIndex;
	Send2NPCServerW(SendBuf, MSG_SIZE(MSG_FN_MONSTER_CREATE_OK));
	m_pFieldIOCPMapChannel->m_uiAccumulatedMonsterCounts++;

	///////////////////////////////////////////////////////////////////////////
	// Client���Ե� ���� ���� �޼����� �����Ѵ�.
	INIT_MSG(MSG_FC_MONSTER_CREATED, T_FC_MONSTER_CREATED, pMsgMonCreated, SendBuf);
	pMsgMonCreated->MonsterIndex	= pMonsterCreate->MonsterIndex;
	pMsgMonCreated->MonsterUnitKind	= pMonsterCreate->MonsterUnitKind;
	pMsgMonCreated->MonsterForm		= pMonster->MonsterInfoPtr->MonsterForm;
	pMsgMonCreated->BodyCondition	= pMonsterCreate->BodyCondition;
	pMsgMonCreated->PositionVector	= pMonsterCreate->PositionVector;
	pMsgMonCreated->TargetVector	= pMonsterCreate->TargetVector;
	pMsgMonCreated->CurrentHP		= pMonster->CurrentHP;

	// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) )
	pMsgMonCreated->MaxHP			= (INT)pMonster->MonsterInfoExtend.fMaxHP;

	if(MONSTER_TARGETTYPE_TUTORIAL == pMonster->m_byMonsterTargetType
		|| MONSTER_TARGETTYPE_MISSION == pMonster->m_byMonsterTargetType)
	{
		BOOL bExistUnitInMapChannel = FALSE;
		mt_auto_lock mtCT(&pMonster->m_mtvectClientIdxForTargetType);
		m_pFieldIOCPMapChannel->SendInRangeClientIndexVectorAroundPosition(pMonster->PositionVector, &pMonster->m_mtvectClientIdxForTargetType, SendBuf
			, MSG_SIZE(MSG_FC_MONSTER_CREATED), this, this->GetMonsterVisibleDiameterW(), &bExistUnitInMapChannel);
	}
	else
	{
		m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(pMonster->PositionVector
			, SendBuf, MSG_SIZE(MSG_FC_MONSTER_CREATED), this, 0, FALSE);
	}

	if(m_pRefCityWar1
		&& CITYWAR_STATE_STARTED == m_pRefCityWar1->GetCityWarState()
		&& m_pRefCityWar1->CityWarQuestMonsterUID == pMonsterCreate->MonsterUnitKind)
	{
		pMonster->SetCityWarFieldMonster(m_pRefCityWar1);
		m_pFieldIOCPMapChannel->OnCityWarQuestMonsterCreated(m_pRefCityWar1->MapIndex);
	}

	if(COMPARE_MPOPTION_BIT(pMonster->MonsterInfoPtr->MPOption, MPOPTION_BIT_BOSS_MONSTER)
		&& IS_MOTHERSHIPWAR_MONSTER(pMonster->MonsterInfoPtr->Belligerence))
//		&& IS_INFLWAR_MONSTER(pMonster->MonsterInfoPtr->Belligerence))	// 2007-08-21 by dhjin, ���� ���� ��, ��������Ʈ�� ���� �����ϰ� ����
	{// 2006-11-21 by cmkwon, ���������� ���� ��ȯ

		CFieldIOCPSocket::OnInfluenceBossMonsterCreated(pMonster, this);
	}

	if(CFieldIOCPSocket::IsValidStrategyPointMonster(pMonster, this))
	{// 2006-11-21 by cmkwon, ��������Ʈ ���� ��ȿ�� üũ - ��������Ʈ ���� ���� ���� ó��
		CFieldIOCPSocket::OnStrategyPointMonsterCreated(pMonster, this);
	}

	// 2007-09-20 by cmkwon, �ڷ���Ʈ ��ȯ ���� ����
	if(IS_TELEPORT_MONSTER(pMonster->MonsterInfoPtr->Belligerence))
	{
		CFieldIOCPSocket::OnTeleportMonsterCreated(pMonster, this);
	}

	return TRUE;
}

BOOL CFieldMapChannel::FieldOnMonsterMove(MSG_FN_MONSTER_MOVE *pMove)
{
	ASSERT_ASSERT(pMove);

	CFieldMonster *ptmFMonster = GetFieldMonster(pMove->ClientIndex, 11);
	if(NULL == ptmFMonster
		|| ptmFMonster->m_enMonsterState != MS_PLAYING)
	{
		return FALSE;
	}

	ptmFMonster->m_nTargetIndex	= pMove->TargetIndex;
	D3DXVECTOR3	tmVector3Pos = A2DX(pMove->PositionVector);

	// update block position
	UpdateBlockPosition(ptmFMonster->PositionVector.x, ptmFMonster->PositionVector.z,
		tmVector3Pos.x, tmVector3Pos.z, ptmFMonster->MonsterIndex);

	// update position
	ptmFMonster->PositionVector	= A2DX(pMove->PositionVector);
	D3DXVec3Normalize(&ptmFMonster->TargetVector, &(A2DX(pMove->TargetVector)));

	///////////////////////////////////////////////////////////////////////////
	// Client�� ���� send MOVE_OK to client
	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_MOVE_OK, T_FC_MONSTER_MOVE_OK, pSendMMoveOK, SendBuf);
	pSendMMoveOK->MonsterIndex		= pMove->ClientIndex;
	pSendMMoveOK->TargetIndex		= ptmFMonster->GetAttackerCliIdx();		// 2006-11-07 by cmkwon
	pSendMMoveOK->PositionVector	= pMove->PositionVector;
	pSendMMoveOK->TargetVector		= pMove->TargetVector;

	ptmFMonster->m_mtVectCltIdxForMonsterMoveOK.clear();
	ptmFMonster->m_mtVectCltIdxForExcludeMonsterMoveOK.clear();
	BOOL bExistUnitInMapChannel = FALSE;
	vectorClientIndex tmClientIdxList;
	tmClientIdxList.reserve(10);
	ptmFMonster->GetAttackedInfoClientIndexList(&tmClientIdxList);

	vectorClientIndex::iterator itr(tmClientIdxList.begin());
	for(; itr != tmClientIdxList.end(); itr++)
	{
		ClientIndex_t tmClientIdx = *itr;

		if(IS_CHARACTER_CLIENT_INDEX(tmClientIdx))
		{
			CFieldIOCPSocket *pTmFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIdx);
			if(pTmFISock
				&& pTmFISock->IsValidCharacter(FALSE)
				&& m_MapChannelIndex.IsSameMapChannelIndex(pTmFISock->m_character.MapChannelIndex)
				&& FALSE == COMPARE_BODYCON_BIT(pTmFISock->m_character.BodyCondition, BODYCON_EVENT_HANDLE_MASK))
			{
				bExistUnitInMapChannel		= TRUE;

				// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ�ʿ����� ���� ������ ��� ������. �ذ� ���� ����
// 				float fDistance = GGetVec3LengthPlane(&(ptmFMonster->PositionVector-pTmFISock->m_character.PositionVector));
// 				if(fDistance < pMove->usSendRange)
// 				{
// 					pTmFISock->SendAddData(SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK));
// 					ptmFMonster->m_mtVectCltIdxForExcludeMonsterMoveOK.push_back(tmClientIdx);
// 				}
				if(TRUE == IS_MAP_INFLUENCE_INFINITY(this->GetMapInfluenceTypeW())) {
					pTmFISock->SendAddData(SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK));
					ptmFMonster->m_mtVectCltIdxForExcludeMonsterMoveOK.push_back(tmClientIdx);
				}
				else {
					float fDistance = GGetVec3LengthPlane(&(ptmFMonster->PositionVector-pTmFISock->m_character.PositionVector));
					if(fDistance < pMove->usSendRange)
					{
						pTmFISock->SendAddData(SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK));
						ptmFMonster->m_mtVectCltIdxForExcludeMonsterMoveOK.push_back(tmClientIdx);
				 	}
				}
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////	
	// 2007-07-19 by cmkwon, Ʃ�丮�� ���� ���� - MONSTER_TARGETTYPE_NORMAL�� ���̿��� Ÿ���� �ٸ��� ó��
	ptmFMonster->IncreaseSendCountsMonsterMoveOK();
	if(MONSTER_TARGETTYPE_NORMAL == ptmFMonster->m_byMonsterTargetType)
	{
		if(1 == ptmFMonster->GetSendCountsMonsterMoveOK()%2)
		{// ���͸� ���� ������ ���� ĳ�����Դ� ���� Move�� �ι��� �ѹ��� �����Ѵ�
			m_pFieldIOCPMapChannel->SendInRangeMonsterMoveOK(ptmFMonster, SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK), this, pMove->usSendRange);
		}
	}
	else
	{
		mt_auto_lock mtCT(&ptmFMonster->m_mtvectClientIdxForTargetType);
		m_pFieldIOCPMapChannel->SendInRangeClientIndexVectorAroundPosition(ptmFMonster->PositionVector
			, &ptmFMonster->m_mtvectClientIdxForTargetType, SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK), this, pMove->usSendRange, &bExistUnitInMapChannel);
		mtCT.auto_unlock_cancel();

		///////////////////////////////////////////////////////////////////////////////
		// 2005-04-18 by cmkwon, ó�� �ʿ�
		if(FALSE == bExistUnitInMapChannel)
		{
			this->OnMonsterDeadFieldMapChannel(ptmFMonster);
		}
	}
// 2007-07-19 by cmkwon, Ʃ�丮�� ���� ���� - ���� ���� ������
//	ptmFMonster->IncreaseSendCountsMonsterMoveOK();
//	if(1 == ptmFMonster->GetSendCountsMonsterMoveOK()%2)
//	{// ���͸� ���� ������ ���� ĳ�����Դ� ���� Move�� �ι��� �ѹ��� �����Ѵ�
//
//		if(MONSTER_TARGETTYPE_NORMAL == ptmFMonster->m_byMonsterTargetType)
//		{
//			m_pFieldIOCPMapChannel->SendInRangeMonsterMoveOK(ptmFMonster, SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK), this, pMove->usSendRange);
//		}
//		else
//		{
//			mt_auto_lock mtCT(&ptmFMonster->m_mtvectClientIdxForTargetType);
//			m_pFieldIOCPMapChannel->SendInRangeClientIndexVectorAroundPosition(ptmFMonster->PositionVector
//				, &ptmFMonster->m_mtvectClientIdxForTargetType, SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK), this, pMove->usSendRange, &bExistUnitInMapChannel);
//			mtCT.auto_unlock_cancel();
//
//			///////////////////////////////////////////////////////////////////////////////
//			// 2005-04-18 by cmkwon, ó�� �ʿ�
//			if(FALSE == bExistUnitInMapChannel)
//			{
//				this->OnMonsterDeadFieldMapChannel(ptmFMonster);
//			}
//		}
//	}

// 2006-05-30 by cmkwon 
// // 2006-05-30 by cmkwon, �̺������� lock�� �ʿ� ���� �κ���	
// // 	mt_auto_lock mtMMOK(&ptmFMonster->m_mtVectCltIdxForMonsterMoveOK);
// // 	mt_auto_lock mtMEMOK(&ptmFMonster->m_mtVectCltIdxForExcludeMonsterMoveOK);
// 	ptmFMonster->m_mtVectCltIdxForMonsterMoveOK.clear();
// 	ptmFMonster->m_mtVectCltIdxForExcludeMonsterMoveOK.clear();
// 	{
// 		BOOL bExistUnitInMapChannel = FALSE;
// 
// 		vectorClientIndex tmClientIdxList;
// 
// 		///////////////////////////////////////////////////////////////////////////////
// 		// ������ AttackedInfo ����Ʈ�� ĳ���Ϳ��Դ� Move�� �����ϰ� ���� ���� ����Ʈ ���� �׸� �߰��Ѵ�
// 		mt_auto_lock mtAAttacked(ptmFMonster->GetAttackedInfoPtrList());
// 		{
// 			DWORD				dwTmCurTick		= timeGetTime();
// 			ActionInfo			*pTmActionInfo	= NULL;
// 			CFieldIOCPSocket	*pTmFISock		= NULL;
// 			mtvectorActionInfoPtr::iterator itr(ptmFMonster->m_mtvectorAttackedInfoPtr.begin());
// 
// 			///////////////////////////////////////////////////////////////////////////////			
// 			// 2005-07-12 by cmkwon, ����� �ڵ�
// 			int					nCount = 0;
// 			int					nInitSize, nOldSize;
// 			nInitSize = nOldSize = ptmFMonster->m_mtvectorAttackedInfoPtr.size();
// 			mtvectorActionInfoPtr::iterator itrOld, itrInit;
// 			itrOld = itrInit = itr;
// 			mtvectorActionInfoPtr::iterator itrEndOld, itrEndInit;
// 			itrEndOld = itrEndInit = ptmFMonster->m_mtvectorAttackedInfoPtr.end();
// 
// 			while(itr != ptmFMonster->m_mtvectorAttackedInfoPtr.end())
// 			{
// 				if(itr >= ptmFMonster->m_mtvectorAttackedInfoPtr.end())
// 				{
// 					char szTemp[1024];
// 					sprintf(szTemp, "[Error] dead_1 Error, MapChannel(%s) MonIdx(%8d) WhileCount(%d) ==> InitSize(%d) InitBegin(0x%X) InitEnd(0x%X),  OldSize(%d) OldCurItr(0x%X) OldEndItr(0x%X),  CurSize(%d) Curitr(0x%X) CurEnd(0x%X),  CurThreadID(%X) OwnerThreadID(%X) LockCount(%d) RecursionCount(%d)\r\n"
// 						, GET_MAP_STRING(this->GetMapChannelIndex()), pMove->ClientIndex, nCount, nInitSize, itrInit, itrEndInit, nOldSize, itrOld, itrEndOld
// 						, ptmFMonster->m_mtvectorAttackedInfoPtr.size(), itr, ptmFMonster->m_mtvectorAttackedInfoPtr.end()
// 						, GetCurrentThreadId(), ptmFMonster->m_mtvectorAttackedInfoPtr.m_lock.OwningThread
// 						, ptmFMonster->m_mtvectorAttackedInfoPtr.m_lock.LockCount, ptmFMonster->m_mtvectorAttackedInfoPtr.m_lock.RecursionCount);
// 					DbgOut(szTemp);
// 					g_pGlobal->WriteSystemLog(szTemp);
// 					break;
// 				}
// 
// 				pTmActionInfo = *itr;
// 				if(IS_CHARACTER_CLIENT_INDEX(pTmActionInfo->UnitIndex))
// 				{
// 					pTmFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(pTmActionInfo->UnitIndex);
// 					if(pTmFISock
// 						&& pTmFISock->IsUsing()
// 						&& m_MapChannelIndex == pTmFISock->m_character.MapChannelIndex
// 						&& FALSE == COMPARE_BODYCON_BIT(pTmFISock->m_character.BodyCondition, BODYCON_EVENT_HANDLE_MASK))
// 					{
// 						bExistUnitInMapChannel		= TRUE;
// 						float fDistance = GGetVec3LengthPlane(&(ptmFMonster->PositionVector-pTmFISock->m_character.PositionVector));
// 						if(fDistance < pMove->usSendRange)
// 						{
// 							pTmFISock->SendAddData(SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK));
// 							ptmFMonster->m_mtVectCltIdxForExcludeMonsterMoveOK.push_back(pTmActionInfo->UnitIndex);
// 						}
// 					}
// // 2005-05-10 by cmkwon, ���� �ʿ����
// //					else
// //					{
// //						SAFE_DELETE (pTmActionInfo);
// //						itr = ptmFMonster->m_mtvectorAttackedInfoPtr.erase(itr);
// //						continue;
// //					}
// 				}
// 				itrOld = itr;
// 				itrEndOld = ptmFMonster->m_mtvectorAttackedInfoPtr.end();
// 				nOldSize = ptmFMonster->m_mtvectorAttackedInfoPtr.size();
// 				nCount++;
// 				itr++;
// 			}
// 		}
// 		mtAAttacked.auto_unlock_cancel();
// 
// 		ptmFMonster->IncreaseSendCountsMonsterMoveOK();
// 		if(1 == ptmFMonster->GetSendCountsMonsterMoveOK()%2)
// 		{// ���͸� ���� ������ ���� ĳ�����Դ� ���� Move�� �ι��� �ѹ��� �����Ѵ�
// 
// 			if(MONSTER_TARGETTYPE_NORMAL == ptmFMonster->m_byMonsterTargetType)
// 			{
// 				m_pFieldIOCPMapChannel->SendInRangeMonsterMoveOK(ptmFMonster, SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK), this, pMove->usSendRange);
// 			}
// 			else
// 			{
// 				mt_auto_lock mtCT(&ptmFMonster->m_mtvectClientIdxForTargetType);
// 				m_pFieldIOCPMapChannel->SendInRangeClientIndexVectorAroundPosition(ptmFMonster->PositionVector
// 					, &ptmFMonster->m_mtvectClientIdxForTargetType, SendBuf, MSG_SIZE(MSG_FC_MONSTER_MOVE_OK), this, pMove->usSendRange, &bExistUnitInMapChannel);
// 				mtCT.auto_unlock_cancel();
// 
// 				///////////////////////////////////////////////////////////////////////////////
// 				// 2005-04-18 by cmkwon, ó�� �ʿ�
// 				if(FALSE == bExistUnitInMapChannel)
// 				{
// 					this->OnMonsterDeadFieldMapChannel(ptmFMonster);
// 				}
// 			}
// 		}
// 	}
	return TRUE;
}

BOOL CFieldMapChannel::FieldOnMonsterDelete(MSG_FN_MONSTER_DELETE *pMonsterDelete)
{
	ASSERT_ASSERT(pMonsterDelete);

	CMonster	*pMonster = GetMonster(pMonsterDelete->MonsterIndex);
	if(NULL == pMonster || MS_NULL == pMonster->m_enMonsterState){			return FALSE;}

	if(FALSE == DeleteBlockPosition(pMonster->PositionVector.x, pMonster->PositionVector.z, pMonsterDelete->MonsterIndex))
	{
		char szTemp[256];
		sprintf(szTemp, "[Error] DeleteBlockPosition_4 Error, MapChannel(%s) UnitIndex(%5d) State(%2d) XZ(%5.0f, %5.0f) \r\n"
			, GET_MAP_STRING(this->m_MapChannelIndex), pMonster->MonsterIndex, pMonster->m_enMonsterState
			, pMonster->PositionVector.x, pMonster->PositionVector.z);
		DBGOUT(szTemp);
		g_pGlobal->WriteSystemLog(szTemp);
	}

	// start 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - ���� ���� Ŭ���̾�Ʈ �ݿ�
	if( TRUE == pMonsterDelete->CinemaDelete )
	{
		INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_CINEMA_DELETE_NOTIFY, T_FC_MONSTER_CINEMA_DELETE_NOTIFY, pMsg, pBuf);
		pMsg->MonsterIdx = pMonsterDelete->MonsterIndex;
		this->SendMessageToAllInChannel(pBuf, MSG_SIZE(MSG_FC_MONSTER_CINEMA_DELETE_NOTIFY));
	}
	// end 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - ���� ���� Ŭ���̾�Ʈ �ݿ�

// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - CFieldIOCPSocket::OnMonsterDead#���� ȣ��
// 	///////////////////////////////////////////////////////////////////////////////
// 	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - �ذ� ���� ����
// // 	////////////////////////////////////////////////////////////////////////////////
// // 	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Key ���� ���� 
// // 	if(TRUE == g_pFieldGlobal->IsArenaServer()
// // 		&& COMPARE_MPOPTION_BIT(pMonster->MonsterInfoPtr->MPOption, MPOPTION_BIT_KEY_MONSTER)) {
// // 		this->m_pFieldIOCPMapChannel->m_InfinityManager.DeleteKeyMonster_DeadForNextStepW(this->m_MapChannelIndex.MapIndex, this->m_MapChannelIndex.ChannelIndex, pMonster->MonsterInfoPtr->MonsterUnitKind);
// // 	}
// 	if(TRUE == g_pFieldGlobal->IsArenaServer())
// 	{
// 		this->DeleteKeyMonster(pMonster);
// 	}

	m_mtvectorMonsterPtr.lock();
	pMonster->ResetMonster();
	m_mtvectorMonsterPtr.unlock();

	return TRUE;
}

// start 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�
BOOL CFieldMapChannel::FieldOnMonsterChangeOk(MSG_FN_MONSTER_CHANGE_OK *pMonsterChangeOk)
{
	ASSERT_ASSERT(pMonsterChangeOk);

	MONSTER_INFO *pChangeMonInfo = NULL;
	CMonster	*pChangeMonster = NULL;
	CMonster	*pMonster = GetMonster(pMonsterChangeOk->MonsterIndex);

	if(NULL == pMonster || MS_NULL == pMonster->m_enMonsterState){			return FALSE;}

	pChangeMonInfo = m_pFieldIOCPMapChannel->GetMonsterInfo(pMonsterChangeOk->ChangeMonsterUnitKind);
	if(NULL == pChangeMonInfo) return FALSE;
	
	m_mtvectorMonsterPtr.lock();
	pMonster->MonsterInfoPtr = pChangeMonInfo;
	m_mtvectorMonsterPtr.unlock();
	
	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_CHANGE_INDEX, T_FC_MONSTER_CHANGE_INDEX, pMsg, pBuf);
	pMsg->MonsterIndex = pMonsterChangeOk->MonsterIndex;
	pMsg->ChangeMonsterUnitKind = pMonsterChangeOk->ChangeMonsterUnitKind;
	this->SendMessageToAllInChannel(pBuf, MSG_SIZE(MSG_FC_MONSTER_CHANGE_INDEX));
	
	return TRUE;
}
// end 2011-05-11 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰� - �ش� ��ä�� Ư�� ���� ���� ��� �߰�

void CFieldMapChannel::FieldDeleteAllMonster()
{
	if(m_nSizemtvectorMonsterPtr <= 0){			return;}

	m_mtvectorMonsterPtr.lock();
	for(int i = 0; i < m_nSizemtvectorMonsterPtr; i++)
	{
		if(m_mtvectorMonsterPtr[i]->m_enMonsterState != MS_NULL)
		{
			if(FALSE == DeleteBlockPosition(m_mtvectorMonsterPtr[i]->PositionVector.x, m_mtvectorMonsterPtr[i]->PositionVector.z, m_mtvectorMonsterPtr[i]->MonsterIndex))
			{
				char szTemp[256];
				sprintf(szTemp, "[Error] DeleteBlockPosition_5 Error, MapChannel(%s) UnitIndex(%5d) XZ(%5.0f, %5.0f)\n"
					, GET_MAP_STRING(this->m_MapChannelIndex), m_mtvectorMonsterPtr[i]->MonsterIndex
					, m_mtvectorMonsterPtr[i]->PositionVector.x, m_mtvectorMonsterPtr[i]->PositionVector.z);
				DBGOUT(szTemp);
				g_pGlobal->WriteSystemLog(szTemp);
			}
		}
		m_mtvectorMonsterPtr[i]->ResetMonster();
	}
	m_mtvectorMonsterPtr.unlock();
}

BOOL CFieldMapChannel::FieldOnGetCharacterInfo(MSG_FN_GET_CHARACTER_INFO * i_pGetCInfo)
{
	CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(i_pGetCInfo->ClientIndex);
	if(NULL == pFISock
		|| FALSE == pFISock->IsUsing())
	{
		return FALSE;
	}

	INIT_MSG_WITH_BUFFER(MSG_FN_GET_CHARACTER_INFO_OK, T_FN_GET_CHARACTER_INFO_OK, pSendCharacterInfoOK, SendBuf);
	pSendCharacterInfoOK->ChannelIndex			= m_MapChannelIndex.ChannelIndex;
	pSendCharacterInfoOK->ClientIndex			= pFISock->GetCharacter()->ClientIndex;
	pSendCharacterInfoOK->mexCharacter			= *pFISock->GetCharacter();
	pSendCharacterInfoOK->GuildMasterCharUID	= 0;
	pSendCharacterInfoOK->bStealthState1		= pFISock->m_bStealthState;
	pSendCharacterInfoOK->bInvisible			= pFISock->m_UnitRenderInfo.RI_Invisible;		// 2006-11-27 by dhjin
	Send2NPCServerW(SendBuf, MSG_SIZE(MSG_FN_GET_CHARACTER_INFO_OK));
	return TRUE;
}

BOOL CFieldMapChannel::FieldOnMissileMove(MSG_FN_MISSILE_MOVE * i_pMissileMove)
{
	return FALSE;
//	CFieldMonster *ptmFMonster = GetFieldMonster(i_pMissileMove->MonsterIndex, 12);
//	if(NULL == ptmFMonster
//		|| ptmFMonster->m_enMonsterState != MS_PLAYING)
//	{
//		return FALSE;
//	}
//
//	BYTE		SendBuf[256];
//	INIT_MSG(MSG_FC_MISSILE_MOVE_OK, T_FC_MISSILE_MOVE_OK, pSendMissileOK, SendBuf);
//	pSendMissileOK->ItemNum			= i_pMissileMove->ItemNum;
//	pSendMissileOK->MonsterIndex	= i_pMissileMove->MonsterIndex;
//	pSendMissileOK->WeaponIndex		= i_pMissileMove->WeaponIndex;
//	pSendMissileOK->PositionVector	= i_pMissileMove->PositionVector;
//	pSendMissileOK->TargetVector	= i_pMissileMove->TargetVector;
//	m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(A2DX(i_pMissileMove->PositionVector),
//		SendBuf, MSG_SIZE(MSG_FC_MISSILE_MOVE_OK), this);
//
//	return TRUE;
}

BOOL CFieldMapChannel::FieldOnMonsterHPRecovery(MSG_FN_MONSTER_HPRECOVERY * i_pHPRecovery)
{
	CFieldMonster *ptmFMonster = GetFieldMonster(i_pHPRecovery->MonsterIndex, 13);
	if(NULL == ptmFMonster)
	{
		return FALSE;
	}
	
	float fMonCurHP = ptmFMonster->IncreaseMonsterCurrentHP(i_pHPRecovery->RecoveryHP);
	if(fMonCurHP > 0.0f)
	{// ������ HP �������� ����
		
		FieldSendMonsterChangeInfo(ptmFMonster, T_FN_MONSTER_CHANGE_HP);
	}	
	return TRUE;
}

BOOL CFieldMapChannel::FieldOnMonsterHide(MSG_FN_MONSTER_HIDE * i_pMonHide)
{
	CFieldMonster *ptmFMonster = GetFieldMonster(i_pMonHide->ClientIndex, 14);
	if(NULL == ptmFMonster
		|| ptmFMonster->m_enMonsterState != MS_PLAYING
		|| TRUE == COMPARE_BODYCON_BIT(ptmFMonster->BodyCondition, BODYCON_DEAD_MASK))
	{
		return FALSE;
	}

	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_HIDE, T_FC_MONSTER_HIDE, pSendHide, SendBuf);
	pSendHide->MonsterIndex	= i_pMonHide->ClientIndex;
	m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(ptmFMonster->PositionVector,
		SendBuf, MSG_SIZE(MSG_FC_MONSTER_HIDE), this, 0, FALSE);

	return TRUE;
}

BOOL CFieldMapChannel::FieldOnMonsterShow(MSG_FN_MONSTER_SHOW * i_pMonShow)
{
	CFieldMonster *ptmFMonster = GetFieldMonster(i_pMonShow->ClientIndex, 15);
	if(NULL == ptmFMonster
		|| ptmFMonster->m_enMonsterState != MS_PLAYING
		|| TRUE == COMPARE_BODYCON_BIT(ptmFMonster->BodyCondition, BODYCON_DEAD_MASK))
	{
		return FALSE;
	}

	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_SHOW, T_FC_MONSTER_SHOW, pSendShow, SendBuf);
	pSendShow->MonsterIndex = i_pMonShow->ClientIndex;
	m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(ptmFMonster->PositionVector,
		SendBuf, MSG_SIZE(MSG_FC_MONSTER_SHOW), this, 0, FALSE);

	return TRUE;
}


BOOL CFieldMapChannel::FieldOnBattleAttackPrimary(MSG_FN_BATTLE_ATTACK_PRIMARY * i_pAttackPri)
{
	return FALSE;
}

BOOL CFieldMapChannel::FieldOnBattleAttackSecondary(MSG_FN_BATTLE_ATTACK_SECONDARY * i_pAttackSec)
{
	return FALSE;
}

BOOL CFieldMapChannel::FieldOnBattleAttackFind(MSG_FN_BATTLE_ATTACK_FIND * i_pAttackFind)
{
	return FALSE;
}

BOOL CFieldMapChannel::FieldOnMonsterChangeBodycondition(MSG_FN_MONSTER_CHANGE_BODYCONDITION * i_pChangeBody)
{
	CFieldMonster *ptmFMonster = GetFieldMonster(i_pChangeBody->ClientIndex, 16);
	if(NULL == ptmFMonster
		|| TRUE == COMPARE_BODYCON_BIT(ptmFMonster->BodyCondition, BODYCON_DEAD_MASK))
	{
		return FALSE;
	}

	if(ptmFMonster->BodyCondition != i_pChangeBody->BodyCondition)
	{
		ptmFMonster->BodyCondition = i_pChangeBody->BodyCondition;	
	}
	this->FieldSendMonsterChangeInfo(ptmFMonster, T_FC_MONSTER_CHANGE_BODYCONDITION);
	return TRUE;
}

BOOL CFieldMapChannel::FieldOnMonsterSkillUseSkill(MSG_FN_MONSTER_SKILL_USE_SKILL * i_pUseSkill)
{
	CFieldMonster *ptmFMonster = GetFieldMonster(i_pUseSkill->MonsterIndex, 17);
	if(NULL == ptmFMonster
		|| ptmFMonster->m_enMonsterState != MS_PLAYING
		|| TRUE == COMPARE_BODYCON_BIT(ptmFMonster->BodyCondition, BODYCON_DEAD_MASK))
	{
		return FALSE;
	}

	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_SKILL_USE_SKILL, T_FC_MONSTER_SKILL_USE_SKILL, pSeUseSkill, SendBuf);
	pSeUseSkill->MonsterIndex	= i_pUseSkill->MonsterIndex;
	pSeUseSkill->ClientIndex	= i_pUseSkill->ClientIndex;
	pSeUseSkill->SkillItemNum	= i_pUseSkill->SkillItemNum;
	m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(ptmFMonster->PositionVector,
		SendBuf, MSG_SIZE(MSG_FC_MONSTER_SKILL_USE_SKILL), this, 0, FALSE);
	return TRUE;
}


BOOL CFieldMapChannel::FieldOnMonsterSkillEndSkill(MSG_FN_MONSTER_SKILL_END_SKILL * i_pEndSkill)
{
	CFieldMonster *ptmFMonster = GetFieldMonster(i_pEndSkill->MonsterIndex, 18);
	if(NULL == ptmFMonster
		|| ptmFMonster->m_enMonsterState != MS_PLAYING
		|| TRUE == COMPARE_BODYCON_BIT(ptmFMonster->BodyCondition, BODYCON_DEAD_MASK))
	{
		return FALSE;
	}

	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_SKILL_END_SKILL, T_FC_MONSTER_SKILL_END_SKILL, pSeUseSkill, SendBuf);
	pSeUseSkill->MonsterIndex	= i_pEndSkill->MonsterIndex;
	pSeUseSkill->PositionVector = i_pEndSkill->PositionVector;
	pSeUseSkill->TargetVector	= i_pEndSkill->TargetVector;
	m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(ptmFMonster->PositionVector,
		SendBuf, MSG_SIZE(MSG_FC_MONSTER_SKILL_END_SKILL), this, 0, FALSE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::FieldOnMonsterAutoDestroyed(MSG_FN_MONSTER_AUTO_DESTROYED * i_pAutoDestroyed)
/// \brief		
/// \author		cmkwon
/// \date		2006-04-17 ~ 2006-04-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::FieldOnMonsterAutoDestroyed(MSG_FN_MONSTER_AUTO_DESTROYED * i_pAutoDestroyed)
{
	CFieldMonster *ptmFMonster = GetFieldMonster(i_pAutoDestroyed->MonsterIndex, 22);
	if(NULL == ptmFMonster
		|| ptmFMonster->m_enMonsterState != MS_PLAYING)
	{
		return FALSE;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2007-11-26 by cmkwon, ���� �ڵ����� �޽��� TCP�� ����(N->F) - 
	//						 TCP�� �����ϸ鼭 T_FN_MONSTER_CHANGE_BODYCONDITION, T_FN_MONSTER_DELETE ���� ���ÿ� ó��
	MSG_FN_MONSTER_CHANGE_BODYCONDITION tmChangeBodyCon;
	tmChangeBodyCon.ClientIndex		= i_pAutoDestroyed->MonsterIndex;
	tmChangeBodyCon.BodyCondition	= i_pAutoDestroyed->BodyCondition;
	this->FieldOnMonsterChangeBodycondition(&tmChangeBodyCon);

	if(COMPARE_MPOPTION_BIT(ptmFMonster->MonsterInfoPtr->MPOption, MPOPTION_BIT_BOSS_MONSTER)
		&& IS_MOTHERSHIPWAR_MONSTER(ptmFMonster->MonsterInfoPtr->Belligerence))
//		&& IS_INFLWAR_MONSTER(ptmFMonster->MonsterInfoPtr->Belligerence))		// 2007-08-21 by dhjin, ���� ���� ��, ��������Ʈ�� ���� �����ϰ� ����
	{// 2006-04-18 by cmkwon, ������ ���� ���Ͱ� �ڵ� ������

		CFieldIOCPSocket::OnInfluenceBossMonsterAutoDestroyed(ptmFMonster, this);
	}

	if(CFieldIOCPSocket::IsValidStrategyPointMonster(ptmFMonster, this))
	{// 2006-11-21 by cmkwon, ��������Ʈ ���� ��ȿ�� üũ - ��������Ʈ ���� �ڵ� ���� ó��
		CFieldIOCPSocket::OnStrategyPointMonsterAutoDestroyed(ptmFMonster, this);
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2007-11-26 by cmkwon, ���� �ڵ����� �޽��� TCP�� ����(N->F) - 
	//						 TCP�� �����ϸ鼭 T_FN_MONSTER_CHANGE_BODYCONDITION, T_FN_MONSTER_DELETE ���� ���ÿ� ó��
	MSG_FN_MONSTER_DELETE tmDelete;
	tmDelete.ChannelIndex			= i_pAutoDestroyed->MapChannIdx.ChannelIndex;
	tmDelete.MonsterIndex			= i_pAutoDestroyed->MonsterIndex;
	tmDelete.CinemaDelete			= FALSE;		// 2011-05-30 by hskim, ���Ǵ�Ƽ 3�� - ���� ���� Ŭ���̾�Ʈ �ݿ�
	this->FieldOnMonsterDelete(&tmDelete);

	return TRUE;
}


BOOL CFieldMapChannel::FieldSendMonsterChangeInfo(CFieldMonster * i_ptmFMonster, int i_nChangeType)
{
	int			nSendSize = 0;
	BYTE		buffer[SIZE_MAX_PACKET];
	switch(i_nChangeType)
	{
	case T_FN_MONSTER_CHANGE_HP:
		{
			// NPC Server�� ����
			INIT_MSG(MSG_FN_MONSTER_CHANGE_HP, T_FN_MONSTER_CHANGE_HP, pFNHP, buffer);
			pFNHP->ChannelIndex		= m_MapChannelIndex.ChannelIndex;
			pFNHP->MonsterIndex		= i_ptmFMonster->MonsterIndex;
			pFNHP->CurrentHP		= i_ptmFMonster->CurrentHP;
			Send2NPCServerW(buffer, MSG_SIZE(MSG_FN_MONSTER_CHANGE_HP));

			// Client���� ����
			INIT_MSG(MSG_FC_MONSTER_CHANGE_HP, T_FC_MONSTER_CHANGE_HP, pFCHP, buffer);
			pFCHP->MonsterIndex		= i_ptmFMonster->MonsterIndex;
			pFCHP->CurrentHP		= i_ptmFMonster->CurrentHP;

			nSendSize				= MSG_SIZE(MSG_FC_MONSTER_CHANGE_HP);			
		}
		break;
	case T_FN_MONSTER_CHANGE_BODYCONDITION:
		{
			// NPC Server�� ����
			INIT_MSG(MSG_FN_MONSTER_CHANGE_BODYCONDITION, T_FN_MONSTER_CHANGE_BODYCONDITION, pFNBody, buffer);
			pFNBody->ChannelIndex	= m_MapChannelIndex.ChannelIndex;
			pFNBody->ClientIndex	= i_ptmFMonster->MonsterIndex;
			pFNBody->BodyCondition	= i_ptmFMonster->BodyCondition;
			Send2NPCServerW(buffer, MSG_SIZE(MSG_FN_MONSTER_CHANGE_BODYCONDITION));

			if(FALSE == COMPARE_BODYCON_BIT(i_ptmFMonster->BodyCondition, BODYCON_DEAD_MASK))
			{
				return TRUE;
			}
			
			if(COMPARE_MPOPTION_BIT(i_ptmFMonster->MonsterInfoPtr->MPOption, MPOPTION_BIT_DEAD_FALL))
			{
				SET_BODYCON_BIT(i_ptmFMonster->BodyCondition, BODYCON_FALL_MASK);
			}
			else
			{
				SET_BODYCON_BIT(i_ptmFMonster->BodyCondition, BODYCON_EXPLOSION_MASK);
			}
			
			INIT_MSG(MSG_FC_MONSTER_CHANGE_BODYCONDITION, T_FC_MONSTER_CHANGE_BODYCONDITION, pFCBody, buffer);
			pFCBody->MonsterIndex	= i_ptmFMonster->MonsterIndex;
			pFCBody->BodyCondition	= i_ptmFMonster->BodyCondition;

			nSendSize				= MSG_SIZE(MSG_FC_MONSTER_CHANGE_BODYCONDITION);			
		}
		break;
	case T_FC_MONSTER_CHANGE_BODYCONDITION:
		{
			// Client���� ����
			INIT_MSG(MSG_FC_MONSTER_CHANGE_BODYCONDITION, T_FC_MONSTER_CHANGE_BODYCONDITION, pFCBody, buffer);
			pFCBody->MonsterIndex	= i_ptmFMonster->MonsterIndex;
			pFCBody->BodyCondition	= i_ptmFMonster->BodyCondition;

			nSendSize				= MSG_SIZE(MSG_FC_MONSTER_CHANGE_BODYCONDITION);			
		}
		break;
	default:
		{
			ASSERT_NEVER_GET_HERE();
			return FALSE;
		}
	}

	if(FALSE == IS_TUTORIAL_MAP_INDEX(this->GetMapChannelIndex().MapIndex))
	{
		////////////////////////////////////////////////////////////////////////////////
		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ �ʿ����� ä�ο� �ִ� ��� �������� �����Ѵ�. �ذ� ���� ����
//		m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(i_ptmFMonster->PositionVector, buffer,
//			nSendSize, this, 0, FALSE);
		if(IS_MAP_INFLUENCE_INFINITY(this->GetMapInfluenceTypeW())) {
			this->SendMessageToAllInChannel(buffer, nSendSize);
		}
		else {
			m_pFieldIOCPMapChannel->SendInRangeMessageAroundPosition(i_ptmFMonster->PositionVector, buffer,
				nSendSize, this, 0, FALSE);
		}
	}
	else
	{
		m_pFieldIOCPMapChannel->SendInRangeClientIndexVectorAroundPosition(i_ptmFMonster->PositionVector
			, &i_ptmFMonster->m_mtvectClientIdxForTargetType, buffer, nSendSize, this, this->GetMonsterVisibleDiameterW());
	}

	return TRUE;
}

void CFieldMapChannel::OnMonsterDeadFieldMapChannel(CFieldMonster *i_pFMonster)
{
	CCityWar *ptmCityWar = i_pFMonster->m_pCityWar2;
	if(ptmCityWar
		&& CITYWAR_STATE_STARTED == ptmCityWar->GetCityWarState())
	{
		m_pFieldIOCPMapChannel->OnCityWarQuestMonsterDead(ptmCityWar);
	}

// 2005-12-17 by cmkwon, ���� �� AttackTime ������ ���� NPC Server ���� ó���ϵ���  ������
//	///////////////////////////////////////////////////////////////////////////////
//	// 2005-10-28 by cmkwon, ���� �� ���� ó��
//	this->BattleAttackOnMonsterDead(i_pFMonster);

	///////////////////////////////////////////////////////////////////
	// ������ HP �������� ����
	this->FieldSendMonsterChangeInfo(i_pFMonster, T_FN_MONSTER_CHANGE_HP);

	///////////////////////////////////////////////////////////////////
	// ������ BodyCondition�� NPCServer�� ���� ĳ���Ϳ��� �����Ѵ�
	i_pFMonster->BodyCondition		= 0;
	SET_BODYCON_BIT(i_pFMonster->BodyCondition, BODYCON_DEAD_MASK);
	i_pFMonster->m_enMonsterState	= MS_DEAD;
	this->FieldSendMonsterChangeInfo(i_pFMonster, T_FN_MONSTER_CHANGE_BODYCONDITION);


	///////////////////////////////////////////////////////////////////////////////
	// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - 
	this->OnInfinityMonsterDead(i_pFMonster);
}

// 2005-12-17 by cmkwon, ���� �� AttackTime ������ ���� NPC Server ���� ó���ϵ���  ������
/////////////////////////////////////////////////////////////////////////////////
///// \fn			void CFieldMapChannel::BattleAttackOnMonsterDead(CFieldMonster *i_pFMonster)
///// \brief		
///// \author		cmkwon
///// \date		2005-10-28 ~ 2005-10-28
///// \warning	
/////
///// \param		
///// \return		
/////////////////////////////////////////////////////////////////////////////////
//void CFieldMapChannel::BattleAttackOnMonsterDead(CFieldMonster *i_pFMonster)
//{
//	MONSTER_INFO *pMonInfo = i_pFMonster->MonsterInfoPtr;
//
//	INIT_MSG_WITH_BUFFER(MSG_FN_ADMIN_SUMMON_MONSTER, T_FN_ADMIN_SUMMON_MONSTER, pSSummonMonster, SendBuf);
//	pSSummonMonster->ChannelIndex			= this->m_MapChannelIndex.ChannelIndex;
//	strncpy(pSSummonMonster->CharacterName, pMonInfo->MonsterName, SIZE_MAX_CHARACTER_NAME);
//	pSSummonMonster->MonsterTargetType1		= MONSTER_TARGETTYPE_NORMAL;
//	pSSummonMonster->TargetTypeData1		= 0;
//	pSSummonMonster->CltIdxForTargetType1	= 0;
//	pSSummonMonster->Position				= i_pFMonster->PositionVector;
//
//	for(int i=0; i < ARRAY_SIZE_MONSTER_ITEM; i++)
//	{
//		// 2005-10-28 by cmkwon, ��� ������ ���������� üũ
//		ITEM *pMonItem = pMonInfo->ItemInfo[i].pItemInfo;
//		if(NULL == pMonItem
//			|| 0 != pMonItem->Charging					// Charging=0 �� �������� ���� �� ����ϴ� ���� ������
//			|| DES_SUMMON != pMonItem->DestParameter1)	// ����� ��ȯ �����۸� ��� ����
//		{
//			continue;
//		}
//
//		// 2005-10-28 by cmkwon, ��� Ȯ�� üũ
//		int nRand = RAND256();
//		if(nRand > pMonItem->HitRate)
//		{
//			continue;
//		}
//
//		///////////////////////////////////////////////////////////////////////////////
//		// NPC Server�� ����
//		pSSummonMonster->MonsterUnitKind		= pMonItem->ParameterValue1;
//		pSSummonMonster->NumOfMonster			= max(1, pMonItem->MultiNum);
//		this->Send2NPCServerW(SendBuf, MSG_SIZE(MSG_FN_ADMIN_SUMMON_MONSTER));
//	}
//}


BOOL CFieldMapChannel::Send2NPCServerW(BYTE *pData, int nSize)
{
	return m_pFieldMapProject->Send2NPCServer(pData, nSize);
}

BOOL CFieldMapChannel::SendBodyCondition2NPCServer(ClientIndex_t clientIndex, BodyCond_t bodyCon)
{
	INIT_MSG_WITH_BUFFER(MSG_FN_CHARACTER_CHANGE_BODYCONDITION, T_FN_CHARACTER_CHANGE_BODYCONDITION, pMsgBodyCon, pMsgBodyConBuf);
	pMsgBodyCon->ClientIndex = clientIndex;
	pMsgBodyCon->BodyCondition = bodyCon;

	return Send2NPCServerW(pMsgBodyConBuf, MSG_SIZE(MSG_FN_CHARACTER_CHANGE_BODYCONDITION));
}

// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - CFieldMapChannel::SendMessageToAllInChannel#, �����߰�(i_nStartCityMapIdx)
void CFieldMapChannel::SendMessageToAllInChannel(BYTE *buffer, int size, BYTE i_byInfluenceMask/*=INFLUENCE_TYPE_ALL_MASK*/, MapIndex_t i_nStartCityMapIdx/*=VCN_CITY_MAP_INDEX*/)
{
	vector<ClientIndex_t>	ClientIndexVector;					// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	mt_auto_lock mtA(&m_mtClientIndexList);

	if(m_mtClientIndexList.empty())
	{
		return;
	}
		
	ClientIndexVector.reserve(m_mtClientIndexList.size());	
	ClientIndexVector.insert(ClientIndexVector.begin()
		, m_mtClientIndexList.begin(), m_mtClientIndexList.end());
	mtA.auto_unlock_cancel();

	m_pFieldIOCPMapChannel->SendInRangeClientIndexVector(&ClientIndexVector, buffer, size, 0, i_byInfluenceMask, i_nStartCityMapIdx);
}

void CFieldMapChannel::SendString128ToAllInChannel(BYTE string128_type, char *szString)
{
	vector<ClientIndex_t>	ClientIndexVector;					// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	m_mtClientIndexList.lock();
	{
		if(m_mtClientIndexList.empty())
		{
			m_mtClientIndexList.unlock();
			return;
		}
		
		ClientIndexVector.reserve(m_mtClientIndexList.size());	
		ClientIndexVector.insert(ClientIndexVector.begin()
			, m_mtClientIndexList.begin(), m_mtClientIndexList.end());
	}
	m_mtClientIndexList.unlock();
	m_pFieldIOCPMapChannel->SendString128ToClientIndexVector(&ClientIndexVector, string128_type, szString);
}

BOOL CFieldMapChannel::WarpToCityMapFieldMapChannel(MapIndex_t i_cityMapIndex, UID32_t i_excludeGuildUID)
{
	if(NULL == m_pFieldMapWorkspace->GetMapProjectByMapIndex(i_cityMapIndex))
	{
		return FALSE;
	}

	mtvectClientIndex_t	sClientIndexVector;					// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	int nCounts = 0;	
	mt_auto_lock mtCIL(&m_mtClientIndexList);
	{
		if(m_mtClientIndexList.empty())
		{
			return nCounts;
		}

		sClientIndexVector.reserve(m_mtClientIndexList.size());	
		sClientIndexVector.insert(sClientIndexVector.begin()
				, m_mtClientIndexList.begin(), m_mtClientIndexList.end());
	}
	mtCIL.auto_unlock_cancel();

	///////////////////////////////////////////////////////////////////////////////
	// 
	MAP_CHANNEL_INDEX tmMapChannIdx(i_cityMapIndex, 0);
	for(int i=0; i < sClientIndexVector.size(); i++)
	{
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(sClientIndexVector[i]);
		if(pFISock
			&& pFISock->IsUsing()
			&& ST_CLIENT_TYPE == pFISock->m_PeerSocketType)
		{
			if((FALSE == IS_VALID_UNIQUE_NUMBER(i_excludeGuildUID) || i_excludeGuildUID != pFISock->GetCharacter()->GuildUniqueNumber)
				&& FALSE == COMPARE_BODYCON_BIT(pFISock->GetCharacter()->BodyCondition, BODYCON_DEAD_MASK)
				&& FALSE == COMPARE_BODYCON_BIT(pFISock->GetCharacter()->BodyCondition, BODYCON_EVENT_HANDLE_MASK)
				&& pFISock->GetCurrentFieldMapChannel() == this)
			{
				pFISock->WarpToMap(tmMapChannIdx);
				nCounts++;
			}
		}
	}
	return nCounts;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::WarpToCityMapFieldMapChannelByInfluence(BYTE i_byexcludeInfuence)
/// \brief		���� ���� ���� ��� ������ ����.
/// \author		dhjin
/// \date		2007-08-20 ~ 2007-08-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::WarpToCityMapFieldMapChannelByInfluence(BYTE i_byexcludeInfuence)
{
	vectClientIndex_t	tmClientIndexList;	// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	if(FALSE == this->GetAllClientIndexList(&tmClientIndexList))
	{
		return FALSE;
	}

	int nCnt = tmClientIndexList.size();
	for(int i=0; i < nCnt; i++)
	{
		// 2007-10-17 by dhjin, �ذ� ���� ����
//		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
//		if(pFISock
//			&& pFISock->IsValidCharacter()
//			&& ERR_NO_ERROR == pFISock->IsEnableWarpToCityMap()
//			&& i_byexcludeInfuence != pFISock->GetCharacter()->InfluenceType)
//		{
//			pFISock->WarpToCityMap();
//		}

// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - �Ʒ��� ���� ����
// 		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
// 		if(pFISock
// 			&& pFISock->IsValidCharacter()
// 			&& i_byexcludeInfuence != pFISock->GetCharacter()->InfluenceType)
// 		{
// 			Err_t err = pFISock->IsEnableWarpToCityMap();
// 			if(ERR_NO_ERROR == err)
// 			{
// 				pFISock->WarpToCityMap();
// 			}
// 			else
// 			{
// 				g_pFieldGlobal->WriteSystemLogEX(TRUE, "[Notify]: Warp Err = [%6d] Characterinfo : [%s]\r\n", err, GetCharacterString(&pFISock->m_character, string()));
// 			}
// 		}

		///////////////////////////////////////////////////////////////////////////////
		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - 
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
		if(NULL == pFISock
			|| FALSE == pFISock->IsValidCharacter(FALSE)
			|| i_byexcludeInfuence == pFISock->GetCharacter()->InfluenceType)
		{
			continue;
		}
		Err_t errNum = pFISock->ClearCharacterForWarp();		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - ������ ���� ���� �۾�,CFieldMapChannel::WarpToCityMapFieldMapChannelByInfluence# ó��
		if(ERR_NO_ERROR != errNum)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] Can't warp in CFieldMapChannel::WarpToCityMapFieldMapChannelByInfluence# !! %s ErrorNum(%d) 1 \r\n", GetCharacterString(pFISock->GetCharacter(), string()), errNum);
			continue;
		}
		errNum = pFISock->IsEnableWarpToCityMap();
		if(ERR_NO_ERROR != errNum)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] Can't warp in CFieldMapChannel::WarpToCityMapFieldMapChannelByInfluence# !! %s ErrorNum(%d) 2 \r\n", GetCharacterString(pFISock->GetCharacter(), string()), errNum);
			continue;
		}
		pFISock->WarpToCityMap();
	}
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::WarpToCityMapFieldMapChannelByGuildUID(UID32_t i_nexcludeGuildUID)
/// \brief		���� ��� ���� ��� ������ ����.
/// \author		dhjin
/// \date		2007-08-21 ~ 2007-08-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::WarpToCityMapFieldMapChannelByGuildUID(UID32_t i_nexcludeGuildUID)
{
	vectClientIndex_t	tmClientIndexList;	// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	if(FALSE == this->GetAllClientIndexList(&tmClientIndexList))
	{
		return FALSE;
	}

	int nCnt = tmClientIndexList.size();
	for(int i=0; i < nCnt; i++)
	{
// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - �Ʒ��� ���� ����
// 		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
// 		if(pFISock
// 			&& pFISock->IsValidCharacter()
// 			&& i_nexcludeGuildUID != pFISock->GetCharacter()->GuildUniqueNumber)
// 		{
// 			Err_t err = pFISock->IsEnableWarpToCityMap();
// 			if(ERR_NO_ERROR == err)
// 			{
// 				pFISock->WarpToCityMap();
// 			}
// 			else
// 			{
// 				g_pFieldGlobal->WriteSystemLogEX(TRUE, "[Notify]: Warp Err = [%6d] Characterinfo : [%s]\r\n", err, GetCharacterString(&pFISock->m_character, string()));
// 			}
// 		}

		///////////////////////////////////////////////////////////////////////////////
		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - 
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
		if(NULL == pFISock
			|| FALSE == pFISock->IsValidCharacter(FALSE)
			|| i_nexcludeGuildUID == pFISock->GetCharacter()->GuildUniqueNumber)
		{
			continue;
		}
		Err_t errNum = pFISock->ClearCharacterForWarp();		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - ������ ���� ���� �۾�, CFieldMapChannel::WarpToCityMapFieldMapChannelByGuildUID# ó��
		if(ERR_NO_ERROR != errNum)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] Can't warp in CFieldMapChannel::WarpToCityMapFieldMapChannelByGuildUID# !! %s ErrorNum(%d) 1 \r\n", GetCharacterString(pFISock->GetCharacter(), string()), errNum);
			continue;
		}
		errNum = pFISock->IsEnableWarpToCityMap();
		if(ERR_NO_ERROR != errNum)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] Can't warp in CFieldMapChannel::WarpToCityMapFieldMapChannelByGuildUID# !! %s ErrorNum(%d) 2 \r\n", GetCharacterString(pFISock->GetCharacter(), string()), errNum);
			continue;
		}
		pFISock->WarpToCityMap();
	}
		
	return TRUE;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::WarpToOutPostCityMapFieldMapChannelByGuildUID(UID32_t i_nGuildUID, int i_nMapindex)
/// \brief		�������� ���� ���ܿ� �������� ���� ������ ����.
/// \author		dhjin
/// \date		2007-08-21 ~ 2007-08-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::WarpToOutPostCityMapFieldMapChannelByGuildUID(UID32_t i_nGuildUID, int i_nMapindex)
{
	vectClientIndex_t	tmClientIndexList;	// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	if(FALSE == this->GetAllClientIndexList(&tmClientIndexList))
	{
		return FALSE;
	}

	CFieldMapChannel *pFMChann = m_pFieldIOCPMapChannel->GetFieldMapChannelByMapChannelIndex(MAP_CHANNEL_INDEX(i_nMapindex, 0));
	if(NULL == pFMChann)
	{
		return FALSE;
	}

	int nCnt = tmClientIndexList.size();
	for(int i=0; i < nCnt; i++)
	{
// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - �Ʒ��� ���� ����
//		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
// 		if(pFISock
// 			&& pFISock->IsValidCharacter()
// 			&& ERR_NO_ERROR == pFISock->IsEnableWarpToCityMap()
// 			&& i_nGuildUID == pFISock->GetCharacter()->GuildUniqueNumber)
// 		{
// 			pFISock->WarpToMap(pFMChann->GetMapChannelIndex(), &pFMChann->GetCityWarpTargetPositionW(), TRUE);
// 		}

		///////////////////////////////////////////////////////////////////////////////
		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - CFieldMapChannel::WarpToOutPostCityMapFieldMapChannelByGuildUID# ó��
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
		if(NULL == pFISock
			|| FALSE == pFISock->IsValidCharacter(FALSE)
			|| i_nGuildUID != pFISock->GetCharacter()->GuildUniqueNumber)
		{
			continue;
		}
		Err_t errNum = pFISock->ClearCharacterForWarp();		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - ������ ���� ���� �۾�	
		if(ERR_NO_ERROR != errNum)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] Can't warp in CFieldMapChannel::WarpToOutPostCityMapFieldMapChannelByGuildUID# !! %s ErrNum(%d) 1 \r\n", GetCharacterString(pFISock->GetCharacter(), string()), errNum);
			continue;
		}
		pFISock->WarpToMap(pFMChann->GetMapChannelIndex(), &pFMChann->GetCityWarpTargetPositionW(), TRUE);
	}
		
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::WarpToCityMap(UID32_t i_excludeCharacterUID)
/// \brief		
/// \author		cmkwon
/// \date		2006-07-24 ~ 2006-07-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::WarpToCityMap(UID32_t i_excludeCharacterUID)
{
	vectClientIndex_t	tmClientIndexList;	// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	if(FALSE == this->GetAllClientIndexList(&tmClientIndexList))
	{
		return FALSE;
	}

	int nCnt = tmClientIndexList.size();
	for(int i=0; i < nCnt; i++)
	{
// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - �Ʒ��� ���� ������.
// 		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
// 		if(pFISock
// 			&& pFISock->IsValidCharacter()
// 			&& i_excludeCharacterUID != pFISock->GetCharacter()->CharacterUniqueNumber
// 			&& ERR_NO_ERROR == pFISock->IsEnableWarpToCityMap())
// 		{
// 			//////////////////////////////////////////////////////////////////////////
// 			// 2007-07-11 by dhjin, �Ʒ��� �ʿ��� ���� �Ʒ��� ���� ���̸� ������ Ż�� ó�� �Ѵ�.
// 			if(IS_MAP_INFLUENCE_ARENA(pFISock->m_pCurrentFieldMapChannel->GetMapInfluenceTypeW())
// 				&& pFISock->m_ArenaInfo.IsValidArenaState() )
// 			{
// 				if(pFISock->m_ArenaInfo.WatchState)
// 				{// 2007-06-21 by dhjin, �������̸� ���� ������ �ʱ�ȭ�Ѵ�.
// 					pFISock->WatchEnd();
// 				}
// 				else
// 				{
// 					m_pFieldIOCPMapChannel->m_ArenaManager.DeleteMember(pFISock);			// 2007-04-23 by dhjin, ���� ����
// 					pFISock->m_ArenaInfo.ResetArenaInfo();		
// 					pFISock->SendAddMessageType(T_FC_ARENA_REAVE_TEAM_OK);			// 2007-05-03 by dhjin, �Ʒ������� ���� ���� ���� ����
// 				}
// 			}
// 			pFISock->WarpToCityMap();
// 		}

		///////////////////////////////////////////////////////////////////////////////
		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - CFieldMapChannel::WarpToCityMap# ó��
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);
		if(NULL == pFISock
			|| FALSE == pFISock->IsValidCharacter(FALSE)
			|| i_excludeCharacterUID == pFISock->GetCharacter()->CharacterUniqueNumber)
		{
			continue;
		}
		Err_t errNum = pFISock->ClearCharacterForWarp();		// 2009-02-05 by cmkwon, ����� ���� ���� ���� ó�� ���� - ������ ���� ���� �۾�
		if(ERR_NO_ERROR != errNum)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] Can't warp in CFieldMapChannel::WarpToCityMap# !! %s ErrNum(%d) 1 \r\n", GetCharacterString(pFISock->GetCharacter(), string()), errNum);
			continue;
		}
		errNum = pFISock->IsEnableWarpToCityMap();
		if(ERR_NO_ERROR != errNum)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] Can't warp in CFieldMapChannel::WarpToCityMap# !! %s ErrNum(%d) 2 \r\n", GetCharacterString(pFISock->GetCharacter(), string()), errNum);
			continue;
		}
		//////////////////////////////////////////////////////////////////////////
		// 2007-07-11 by dhjin, �Ʒ��� �ʿ��� ���� �Ʒ��� ���� ���̸� ������ Ż�� ó�� �Ѵ�.
		if(IS_MAP_INFLUENCE_ARENA(pFISock->m_pCurrentFieldMapChannel->GetMapInfluenceTypeW())
			&& pFISock->m_ArenaInfo.IsValidArenaState() )
		{
			if(pFISock->m_ArenaInfo.WatchState)
			{// 2007-06-21 by dhjin, �������̸� ���� ������ �ʱ�ȭ�Ѵ�.
				pFISock->WatchEnd();
			}
			else
			{
				m_pFieldIOCPMapChannel->m_ArenaManager.DeleteMember(pFISock);			// 2007-04-23 by dhjin, ���� ����
				pFISock->m_ArenaInfo.ResetArenaInfo();		
				pFISock->SendAddMessageType(T_FC_ARENA_REAVE_TEAM_OK);			// 2007-05-03 by dhjin, �Ʒ������� ���� ���� ���� ����
			}
		}
		pFISock->WarpToCityMap();
	}
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CFieldMapChannel::InsertItemInMap(INT i_nItemNum, INT i_nItemCount, BYTE i_byInflMask/*=INFLUENCE_TYPE_ALL_MASK*/)
/// \brief		
/// \author		cmkwon
/// \date		2006-07-24 ~ 2006-07-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CFieldMapChannel::InsertItemInMap(INT i_nItemNum, INT i_nItemCount, BYTE i_byInflMask/*=INFLUENCE_TYPE_ALL_MASK*/)
{
	// 2008-02-20 by cmkwon, ��ī���ͺ� ������ ī��Ʈ üũ �߰�
	ITEM *pItemInfo = m_pFieldIOCPMapChannel->GetItemInfo(i_nItemNum);
	if(NULL == pItemInfo)
	{
		g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] CFieldMapChannel::InsertItemInMap_1 ItemNum error !!, ItemNum(%d) ItemCount(%d) InflueceType(%d)\r\n"
			, i_nItemNum, i_nItemCount, i_byInflMask);
		return 0;
	}
	if(FALSE == IS_COUNTABLE_ITEM(pItemInfo->Kind)
		&& 10 < i_nItemCount)
	{// 2008-02-20 by cmkwon, ��ī���ͺ� ������ ī��Ʈ�� �ִ� 10���� ������
		g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] CFieldMapChannel::InsertItemInMap_2 ItemCount error !!, ItemNum(%d) ItemCount(%d) InflueceType(%d)\r\n"
			, i_nItemNum, i_nItemCount, i_byInflMask);

		i_nItemCount	= 10;	// 2008-02-20 by cmkwon, ������ 10���� �����ؼ� �߰��� �����Ѵ�.
	}

	vectClientIndex_t	tmClientIndexList;	// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	if(FALSE == this->GetAllClientIndexList(&tmClientIndexList))
	{
		return 0;
	}

	INT nInsertedCount = 0;
	int nCnt = tmClientIndexList.size();
	for(int i=0; i < nCnt; i++)
	{
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);

		// 2008-01-10 by cmkwon, IsCheckInfluenceTypeANDSocketType() ���� ���� - RACE_GAMEMASTER �� üũ �ʿ� ����
		if(pFISock
			&& pFISock->IsValidCharacter(FALSE)
			&& pFISock->IsCheckInfluenceTypeANDSocketType(i_byInflMask, ST_CLIENT_TYPE, FALSE))
		{
			if(pFISock->m_ItemManager.InsertItemBaseByItemNum(i_nItemNum, i_nItemCount, IUT_BONUS_ITEM))
			{
				nInsertedCount++;
			}
		}
	}

	// 2007-11-05 by cmkwon, �ý��� �α� �߰� - CFieldMapChannel::InsertItemInMap() �Լ� ȣ�� �α� ����
	g_pGlobal->WriteSystemLogEX(TRUE, "  [Notify] CFieldMapChannel::InsertItemInMap_ InfluenceType(%10s:%3d) ItemNum(%8d) ItemCount(%4d) InsertedCount(%d)\r\n"
		, CAtumSJ::GetInfluenceTypeString(i_byInflMask), i_byInflMask, i_nItemNum, i_nItemCount, nInsertedCount);
	return nInsertedCount;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CFieldMapChannel::AddWarPointInMap(INT i_nAddWarPoint,  BOOL i_bEventBonus, BYTE i_byInflMask/*=INFLUENCE_TYPE_ALL_MASK*/, BYTE i_byWPUpdateTy/*=WPUT_GENERAL*/)
/// \brief		// 2007-06-14 by cmkwon, ������ ���� ����
///				// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - CFieldMapChannel::AddWarPointInMap()�� ����(, BYTE i_byWPUpdateTy=WPUT_GENERAL) �߰�
/// \author		cmkwon
/// \date		2007-06-14 ~ 2007-06-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CFieldMapChannel::AddWarPointInMap(INT i_nAddWarPoint, BOOL i_bEventBonus,  BYTE i_byInflMask/*=INFLUENCE_TYPE_ALL_MASK*/, BYTE i_byWPUpdateTy/*=WPUT_GENERAL*/)
{
	vectClientIndex_t	tmClientIndexList;	// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	if(FALSE == this->GetAllClientIndexList(&tmClientIndexList))
	{
		return 0;
	}

	INT nInsertedCount = 0;
	int nCnt = tmClientIndexList.size();
	for(int i=0; i < nCnt; i++)
	{
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);

		// 2008-01-10 by cmkwon, IsCheckInfluenceTypeANDSocketType() ���� ���� - RACE_GAMEMASTER üũ �ʿ� ����
		if(NULL == pFISock
			|| FALSE == pFISock->IsValidCharacter(FALSE)
			|| FALSE == pFISock->IsCheckInfluenceTypeANDSocketType(i_byInflMask, ST_CLIENT_TYPE, FALSE))
		{
			continue;
		}

		// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - CFieldIOCPSocket::WPAddWarPoint()�� ����(, BYTE i_byWPUpdateTy=WPUT_GENERAL) �߰�
		pFISock->WPAddWarPoint(i_nAddWarPoint, i_bEventBonus, i_byWPUpdateTy);
		nInsertedCount++;
	}

	// 2007-11-05 by cmkwon, �ý��� �α� �߰� - CFieldMapChannel::AddWarPointInMap() �Լ� ȣ�� �α� ����
	// 2009-01-22 by cmkwon, ���� ���� ���� �α� ���� - CFieldMapChannel::AddWarPointInMap()�� ����(, BYTE i_byWPUpdateTy=WPUT_GENERAL) �߰�
	g_pGlobal->WriteSystemLogEX(TRUE, "  [Notify] CFieldMapChannel::AddWarPointInMap_ InfluenceType(%10s:%3d) AddWarPoint(%4d) bEventBonus(%d) AddedCount(%d) %s\r\n"
		, CAtumSJ::GetInfluenceTypeString(i_byInflMask), i_byInflMask, i_nAddWarPoint, i_bEventBonus, nInsertedCount, GetWPUTString(i_byWPUpdateTy));
	return nInsertedCount;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::CalcMapTotalTraffic(void)
/// \brief		��Ŷ ���� �ý����� ���� �Լ�, �ʺ� Bandwidth�� ����ϰ� Bandwidth�� ���� ���� NetworkState�� �����ȴ�.
/// \author		cmkwon
/// \date		2004-03-23 ~ 2004-03-23
/// \warning
///
/// \return		����
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::CalcMapTotalTraffic(void)
{
	if(FALSE == m_pFieldMapWorkspace->GetLogFlagMapBandwidth())
	{// 2008-03-13 by cmkwon, ��Ը� ����� Ŭ���̾�Ʈ �ñ�°� ���� - 
		return;
	}

	char	szSysLog[1024];
	DWORD	dwCurTick	= timeGetTime();

	///////////////////////////////////////////////////////////////////////////
	// ���� ��ü�� �����Ѵ�.
	LockMapTraffic();
	memcpy(&m_MapTraffic[1], &m_MapTraffic[0], sizeof(STrafficInfo));		// �ι�° ��ü�� �����Ѵ�.
	memset(&m_MapTraffic[0], 0x00, sizeof(STrafficInfo));					// ù��° ��ü�� �ʱ�ȭ �Ѵ�.
	m_MapTraffic[0].dwTimeGapSecond		= dwCurTick;						// ù��° ��ü�� ���� �ð��� �����Ѵ�.
	UnlockMapTraffic();

	STrafficInfo *pTCP = &m_MapTraffic[1];

	///////////////////////////////////////////////////////////////////////////
	// TimeGap�� 1���� ������� 1�� �����Ѵ�.
	pTCP->dwTimeGapSecond		= max(1, (dwCurTick - pTCP->dwTimeGapSecond)/1000);
// 2004-11-22 by cmkwon, �ο����� ó��
//	///////////////////////////////////////////////////////////////////////////
//	// TCP LanHeader �� �����ش�, �����ִ� �ڵ带 ����
//	//m_MapTraffic[1].dwBytesSend			+= m_MapTraffic[1].dwCountSendPacket/5 * SIZE_TCP_LAN_HEADER;	// ��Ƽ� ������ �����̹Ƿ� �ܼ��� ���� ī��Ʈ�� �ƴ϶� 5�� ������ ��ŭ�� �����ش�.
//
//	if(m_dwMaxBandwidthChannel != 0)
//	{
//		///////////////////////////////////////////////////////////////////////////
//		// �� ��Ŷ ���� �ý����� ���� ���� ��ũ��ũ ���¸� ����Ѵ�.
//		
//		if(((pTCP->dwBytesSend*8)/pTCP->dwTimeGapSecond) * 100/m_dwMaxBandwidthChannel > 70)
//		{	//
//
//			sprintf(szSysLog, "[Notify] Total Network MaxBandwidth(%d) CurrentBandwidth(%d) MapName(%10s)\r\n",
//				m_dwMaxBandwidthChannel, ((pTCP->dwBytesSend*8)/pTCP->dwTimeGapSecond)
//				, GET_MAP_STRING(this->m_MapChannelIndex));
//			g_pGlobal->WriteSystemLog(szSysLog);
//			DBGOUT(szSysLog);
//		}
//	}

	///////////////////////////////////////////////////////////////////////////
	// ���� ��Ʈ��ũ ���¸� �ý��� �α׷� �����Ѵ�.
	if(((CFieldMapWorkspace*)m_pMapWorkspace)->GetLogFlagMapBandwidth())
	{
		///////////////////////////////////////////////////////////////////////////
		// Bandwidth
		UINT	TCPSend_bps, TCPSend_cps;
		TCPSend_bps = (pTCP->dwBytesSend * 8)/pTCP->dwTimeGapSecond;
		TCPSend_cps = pTCP->dwCountSendPacket/pTCP->dwTimeGapSecond;
		sprintf(szSysLog, "MapName : (%10s)	\t\t\t\t\t\t\t\t\t	Send[%10d bps, %6d cps]\r\n",
			GET_MAP_STRING(this->m_MapChannelIndex), TCPSend_bps, TCPSend_cps);
		g_pGlobal->WriteSystemLog(szSysLog, FALSE);
		//DBGOUT(szSysLog);
	}
}

BOOL CFieldMapChannel::IsCheckUserCountForWarp(CFieldIOCPSocket *i_pFISock)
{
// 2006-06-13 by cmkwon, ������ ���ؼ��� ������ ����� �Ѵ�.
// 	if(2*this->GetMaxUserCountsChannel() <= this->GetNumClients())
// 	{
// 		if(FALSE == COMPARE_RACE(i_pFISock->GetCharacter()->Race, RACE_OPERATION|RACE_GAMEMASTER))
// 		{
// 			return FALSE;
// 		}
// 	}
	return TRUE;
}


void CFieldMapChannel::AddMapSendTraffic(int nSendBytes, int nSendCounts)
{
	if(FALSE == m_pFieldMapWorkspace->GetLogFlagMapBandwidth())
	{// 2008-03-13 by cmkwon, ��Ը� ����� Ŭ���̾�Ʈ �ñ�°� ���� - FALSE �����̸� ����� ���� �ʴ´�.
		return;
	}

	LockMapTraffic();
	m_MapTraffic[0].dwBytesSend += nSendBytes;
	m_MapTraffic[0].dwCountSendPacket += nSendCounts;
	UnlockMapTraffic();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			INT CMapChannel::GetCrowdedness()
/// \brief		���� ä���� ȥ�⵵�� ��ȯ
/// \author		kelovon
/// \date		2004-03-29 ~ 2004-03-29
/// \warning
///
/// \return		INT ȥ�⵵
///////////////////////////////////////////////////////////////////////////////
INT CFieldMapChannel::GetCrowdedness()
{
	if(0 == this->GetMaxUserCountsChannel())
	{
		return 0;
	}

	return min(100, this->GetNumClients()*100/GetMaxUserCountsChannel());
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CFieldMapChannel::GetUserCounts(BYTE i_byInflTyMask, BYTE i_byMinLevel, BYTE i_byMaxLevel)
/// \brief		
/// \author		cmkwon
/// \date		2006-07-21 ~ 2006-07-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CFieldMapChannel::GetUserCounts(BYTE i_byInflTyMask, BYTE i_byMinLevel, BYTE i_byMaxLevel)
{
	vector<ClientIndex_t>	ClientIndexVector;					// �ٸ� ĳ���͵鿡�� ������ ���� �� set�� ���� buffer�� ���
	mt_auto_lock mtA(&m_mtClientIndexList);

	if(m_mtClientIndexList.empty())
	{
		return 0;
	}

	ClientIndexVector.reserve(m_mtClientIndexList.size());	
	ClientIndexVector.insert(ClientIndexVector.begin()
		, m_mtClientIndexList.begin(), m_mtClientIndexList.end());
	mtA.auto_unlock_cancel();

	int nRetCount	= 0;
	int nSize		= ClientIndexVector.size();
	for(int i=0; i < nSize; i++)
	{
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(ClientIndexVector[i]);

		// 2008-01-10 by cmkwon, IsCheckInfluenceTypeANDSocketType() ���� ���� - RACE_GAMEMASTER üũ �ʿ� ����
		if(pFISock && pFISock->IsValidCharacter(FALSE)
			&& pFISock->IsCheckInfluenceTypeANDSocketType(i_byInflTyMask, ST_CLIENT_TYPE, FALSE)
			&& pFISock->IsCheckLevel(i_byMinLevel, i_byMaxLevel))
		{
			nRetCount++;
		}
	}

	return nRetCount;
}

void CFieldMapChannel::ProcessRacing(struct tm *i_pRealTime)
{
	if(NULL == m_pRacing){						return;}

	BYTE	bySendBuf[SIZE_MAX_PACKET];
	DWORD	dwCurTick = timeGetTime();
	switch(m_pRacing->m_racingState)
	{
	case RACINGSTATE_STANDBY:
		{
			int		nAtumHour = (i_pRealTime->tm_hour%4)*6 + (i_pRealTime->tm_min*6)/60;
			int		nAtumMin = (i_pRealTime->tm_min*6)%60 + (i_pRealTime->tm_sec*6)/60;
			int		nAtumSecond = (i_pRealTime->tm_sec*6)%60;
			if(nAtumHour == m_pRacing->m_byRacingSystemStartHour-1)
			{
				if(nAtumMin%6 == 0
					&& nAtumSecond == 0)
				{
					m_pRacing->m_nRamainTimeForJoinRacing = (60-nAtumMin)/6 * 60;						// �ʴ����� ���
					if(60 == m_pRacing->m_nRamainTimeForJoinRacing)
					{
						m_pRacing->SetRacingState(RACINGSTATE_READY);
					}

					INIT_MSG(MSG_FC_RACING_RACINGNOTIFY, T_FC_RACING_RACINGNOTIFY, pSMsg, bySendBuf);
					pSMsg->mapChannIdx					= this->GetMapChannelIndex();
					pSMsg->dwRamainTimeForJoinRacing	= m_pRacing->m_nRamainTimeForJoinRacing;
					m_pRacing->Send2WaitingRoomUserList(bySendBuf, MSG_SIZE(MSG_FC_RACING_RACINGNOTIFY));
				}
			}
		}
		break;
	case RACINGSTATE_READY:
		{
			if(dwCurTick - m_pRacing->m_dwLastChangeStateTick > 1000)
			{
				m_pRacing->m_nRamainTimeForJoinRacing = 0;
				m_pRacing->SetRacingState(RACINGSTATE_INVITING);

				INIT_MSG(MSG_FC_RACING_RACINGNOTIFY, T_FC_RACING_RACINGNOTIFY, pSMsg, bySendBuf);
				pSMsg->mapChannIdx					= this->GetMapChannelIndex();
				pSMsg->dwRamainTimeForJoinRacing	= m_pRacing->m_nRamainTimeForJoinRacing;
				m_pRacing->Send2WaitingRoomUserList(bySendBuf, MSG_SIZE(MSG_FC_RACING_RACINGNOTIFY));
			}
		}
		break;
	case RACINGSTATE_INVITING:
		{
			if(dwCurTick - m_pRacing->m_dwLastChangeStateTick > 30*1000
				&& m_pRacing->m_vectorJoinedUserList.size() >= m_pRacing->m_byMinUserCounts)
			{				
				m_pRacing->SetRacingState(RACINGSTATE_INVITIED);
			}
		}
		break;
	case RACINGSTATE_INVITIED:
		{
			if(dwCurTick - m_pRacing->m_dwLastChangeStateTick > 30*1000)
			{				
				m_pRacing->SetRacingState(RACINGSTATE_COUNTDOWN);
			}
		}
		break;
	case RACINGSTATE_COUNTDOWN:
		{
			if(dwCurTick - m_pRacing->m_dwLastChangeStateTick > 1000)
			{
				m_pRacing->m_nCountdownCounts--;				
				if(m_pRacing->m_nCountdownCounts <= 0)
				{
					m_pRacing->SetRacingState(RACINGSTATE_STARTED);
				}
				else
				{
					m_pRacing->SetRacingState(RACINGSTATE_COUNTDOWN);
				}

				INIT_MSG(MSG_FC_RACING_COUNTDOWN, T_FC_RACING_COUNTDOWN, pSMsg, bySendBuf);
				pSMsg->byCountDowns = m_pRacing->m_nCountdownCounts;
				m_pRacing->Send2WaitingRoomUserList(bySendBuf, MSG_SIZE(MSG_FC_RACING_COUNTDOWN));
			}			
		}
		break;
	case RACINGSTATE_STARTED:
		{
			if(dwCurTick - m_pRacing->m_dwLastChangeStateTick > m_pRacing->m_nLimitTimeForRacing*1000)
			{
				m_pRacing->EndRacingGame();				
			}
		}
		break;
	}
}


void CFieldMapChannel::InRacingWaitingRoom(CFieldIOCPSocket *i_pFSocket)
{
	if(NULL == m_pRacing)
	{
		return;
	}
	
	m_pRacing->PutWaitingRoomUserList(i_pFSocket);
}
void CFieldMapChannel::OutRacingSystem(CFieldIOCPSocket *i_pFSocket)
{
	if(NULL == m_pRacing)
	{
		return;
	}

	m_pRacing->PopWaitingRoomUserList(i_pFSocket);
	m_pRacing->PopJoinedUserList(i_pFSocket);
}

int CFieldMapChannel::JoinRacing(CFieldIOCPSocket *i_pFSocket)
{
	if(NULL == m_pRacing
		|| RACINGSTATE_INVITING	!= m_pRacing->m_racingState)
	{
		return 0;
	}

	return m_pRacing->PutJoinedUserList(i_pFSocket);
}

BOOL CFieldMapChannel::IsJoinedUser(CFieldIOCPSocket *i_pFSocket)
{
	if(NULL == m_pRacing)
	{
		return FALSE;
	}

	return m_pRacing->IsJoinedUserList(i_pFSocket);
}

BOOL CFieldMapChannel::CheckPointCheck(CFieldIOCPSocket *i_pFSocket, BYTE i_byCheckPointIndex)
{
	if(NULL == m_pRacing
		|| RACINGSTATE_STARTED != m_pRacing->m_racingState)
	{
		return FALSE;
	}

	return m_pRacing->CheckPoint(i_pFSocket, i_byCheckPointIndex);
}


BOOL CFieldMapChannel::MakeRacingMessage(MessageType_t i_msgType, void *o_pMsg)
{
	if(FALSE == IS_RACING_MAP_INDEX(this->m_MapChannelIndex.MapIndex))
	{
		return FALSE;
	}

	switch(i_msgType)
	{
	case T_FC_RACING_RACINGINFO_REQUEST_ACK:
		{
			MSG_FC_RACING_RACINGINFO_REQUEST_ACK *pMsg = (MSG_FC_RACING_RACINGINFO_REQUEST_ACK*)o_pMsg;
			pMsg->mapChannelIndex				= this->GetMapChannelIndex();
			pMsg->byMaxUserCounts				= m_pRacing->m_byMaxUserCounts;
			pMsg->byMinUserCounts				= m_pRacing->m_byMinUserCounts;
			pMsg->byRacingGameNumber			= m_pRacing->m_byRacingGameNumber;
			pMsg->nEntryFee						= m_pRacing->m_nEntryFee;
			pMsg->nLimitTimeForRacing			= m_pRacing->m_nLimitTimeForRacing;
			pMsg->nRamainTimeForJoinRacing		= m_pRacing->m_nRamainTimeForJoinRacing;			
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CFieldMapChannel::SetCityWarFieldMapChannel(CCityWar *i_pCityWar)
{
	m_pRefCityWar1 = i_pCityWar;
}
BOOL CFieldMapChannel::MakeMSG_FC_CITYWAR_GET_OCCUPYINFO_OK(MSG_FC_CITYWAR_GET_OCCUPYINFO_OK *o_pOccupyInfo
															, UID32_t i_guildUID)
{	
	if(NULL == m_pRefCityWar1){										return FALSE;}

	o_pOccupyInfo->CurrentMapIndex3		= this->m_MapChannelIndex.MapIndex;
	o_pOccupyInfo->CityWarMapIndex3		= m_pRefCityWar1->MapIndex;
	o_pOccupyInfo->CityWarCityMapIndex3	= m_pRefCityWar1->CityMapIndex;
	o_pOccupyInfo->CityWarOccupyInfo3	= *m_pRefCityWar1->GetCITY_OCCUPY_INFO();

	if(o_pOccupyInfo->CityWarOccupyInfo3.OccupyGuildUID != i_guildUID)
	{// ���ɿ����� �ƴϸ� ������ �հ�� �������� �ʴ´�		
		o_pOccupyInfo->CityWarOccupyInfo3.nSumOfTex	= 0;		
	}
	return TRUE;
}
Err_t CFieldMapChannel::SetCityWarSettingTimeFieldMapChannel(ATUM_DATE_TIME *i_pSetTime, UID32_t i_guildUID, UID32_t i_charUID)
{
	if(NULL == m_pRefCityWar1)
	{
		return ERR_CITYWAR_NO_SUCH_CITYWAR_INFO;
	}
	if(m_pRefCityWar1->CityMapIndex != this->m_MapChannelIndex.MapIndex)
	{
		return ERR_CITYWAR_NOT_MATCHED_CITY_MAP_INDEX;
	}

	return m_pRefCityWar1->SetCityWarSettingTimeCityWar(i_pSetTime, i_guildUID, i_charUID);
}
Err_t CFieldMapChannel::SetCityWarTexFieldMapChannel(float i_fSetTex, UID32_t i_guildUID, UID32_t i_charUID)
{
	if(NULL == m_pRefCityWar1)
	{
		return ERR_CITYWAR_NO_SUCH_CITYWAR_INFO;
	}
	if(m_pRefCityWar1->CityMapIndex != this->m_MapChannelIndex.MapIndex)
	{
		return ERR_CITYWAR_NOT_MATCHED_CITY_MAP_INDEX;
	}

	return m_pRefCityWar1->SetCityWarTexCityWar(i_fSetTex, i_guildUID, i_charUID);
}
Err_t CFieldMapChannel::SetCityWarBriefingFieldMapChannel(char *i_szSetBriefing, UID32_t i_guildUID, UID32_t i_charUID)
{
	if(NULL == m_pRefCityWar1)
	{
		return ERR_CITYWAR_NO_SUCH_CITYWAR_INFO;
	}
	if(m_pRefCityWar1->CityMapIndex != this->m_MapChannelIndex.MapIndex)
	{
		return ERR_CITYWAR_NOT_MATCHED_CITY_MAP_INDEX;
	}

	return m_pRefCityWar1->SetCityWarBriefingCityWar(i_szSetBriefing, i_guildUID, i_charUID);
}
Err_t CFieldMapChannel::CityWarBringSumOfTex(int *o_pnBringTex, UID32_t i_guildUID, UID32_t i_charUID)
{
	if(NULL == m_pRefCityWar1)
	{
		return ERR_CITYWAR_NO_SUCH_CITYWAR_INFO;
	}
	if(m_pRefCityWar1->CityMapIndex != this->m_MapChannelIndex.MapIndex)
	{
		return ERR_CITYWAR_NOT_MATCHED_CITY_MAP_INDEX;
	}

	return m_pRefCityWar1->BringSumOfTexCityWar(o_pnBringTex, i_guildUID, i_charUID);
}
float CFieldMapChannel::CityWarGetTexPercent(int i_nBuildingIdx, UID32_t i_guildUID)
{
	if(NULL == m_pRefCityWar1)
	{
		return 0.0f;
	}

	if(FALSE == IS_VALID_UNIQUE_NUMBER(m_pRefCityWar1->OccupyGuildUID))
	{
		return 0.0f;
	}
// 2005-07-19 by cmkwon, ���������� ���� ���ܵ� ������ �����ϵ��� �Ѵ�.
//	if(i_guildUID == m_pRefCityWar1->OccupyGuildUID)
//	{
//		return 0.0f;
//	}

	BUILDINGNPC *pBuilding = m_pFieldMapProject->m_mapBuilding2Building.findEZ(i_nBuildingIdx);
	if(NULL == pBuilding)
	{
		return 0.0f;
	}

	if(m_pRefCityWar1->CityMapIndex != pBuilding->OwnerCityMapIndex)
	{
		return 0.0f;
	}

	if(m_pRefCityWar1->nDefenseCounts < pBuilding->OwnerOrderNumber)
	{
		return 0.0f;
	}

	return m_pRefCityWar1->fTexPercent;
}
int CFieldMapChannel::CityWarAddTex(int i_nTex)
{
	if(NULL == m_pRefCityWar1)
	{
		return 0;
	}

	return m_pRefCityWar1->AddTex(i_nTex);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::SetLastTickStrategyPointMonsterDeaded(DWORD i_dwTick)
/// \brief		
/// \author		cmkwon
/// \date		2006-11-21 ~ 2006-11-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::SetLastTickStrategyPointMonsterDeaded(DWORD i_dwTick)
{
	m_dwLastTickStrategyPointMonsterDeaded	= i_dwTick;
	
	///////////////////////////////////////////////////////////////////////////////
	// 2007-01-25 by cmkwon, 0�϶��� �ʱ�ȭ 0�� �ƴϸ� ���ĵȰ���
	if(0 == m_dwLastTickStrategyPointMonsterDeaded)
	{
		m_bStrategyPointMonsterDeaded		= FALSE;
	}
	else
	{
		m_bStrategyPointMonsterDeaded		= TRUE;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::IsOccupyStrategyPointMonster(void)
/// \brief		
/// \author		cmkwon
/// \date		2006-11-21 ~ 2006-11-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::IsOccupyStrategyPointMonster(void)
{
	DWORD dwCur = timeGetTime();
	if(m_bStrategyPointMonsterDeaded
		&& TERM_STRATEGYPOINT_OCCUPY_TIME > dwCur - m_dwLastTickStrategyPointMonsterDeaded)
	{// 2006-11-21 by cmkwon, 2�ð� ���ȸ� �����ȴ�.
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::SetTelePortState(int i_nTelePortState)
/// \brief		�ڷ���Ʈ ���� �� ����.
/// \author		dhjin
/// \date		2007-09-05 ~ 2007-09-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::SetTelePortState(int i_nTelePortState)
{
	if(TELEPORT_STATE_NONE == i_nTelePortState
		&& TELEPORT_STATE_NOT_SUMMON == m_TelePortState)
	{// 2007-11-06 by dhjin, �ڷ���Ʈ ���� �ı��ÿ� ���� ���� �߰��� �߰���
		this->SetTelePortSummonFirst(TRUE);
	}
	
	m_TelePortState = i_nTelePortState;
	m_dwTeleportStateChangedTick	= timeGetTime();	// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - 
	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CFieldMapChannel::GetTelePortState()
/// \brief		�ڷ���Ʈ ���� �� ������.
/// \author		dhjin
/// \date		2007-09-05 ~ 2007-09-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CFieldMapChannel::GetTelePortState()
{
	return m_TelePortState;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::IsInvincibleTelePortState(void)
/// \brief		// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - 
/// \author		cmkwon
/// \date		2007-09-20 ~ 2007-09-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::IsInvincibleTelePortState(void)
{
	DWORD dwCur = timeGetTime();
	if(TELEPORT_STATE_COMPLETE != this->GetTelePortState()
		&& dwCur - m_dwTeleportStateChangedTick < 5000)
	{// 2007-09-20 by cmkwon, �ڷ���Ʈ ���� - TELEPORT_STATE_COMPLETE ���¸� ������ ���°� ����� �� 5�ʰ��� ������ ���� ���
		return TRUE;
	}

	return TELEPORT_STATE_READY == this->GetTelePortState();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::SetTelePortSummonFirst(BOOL i_bTelePortSummonFirst)
/// \brief		�ڷ���Ʈ ó�� ��ȯ �� �������� üũ
/// \author		dhjin
/// \date		2007-11-06 ~ 2007-11-06
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::SetTelePortSummonFirst(BOOL i_bTelePortSummonFirst)
{
	m_TelePortSummonFirst	=	i_bTelePortSummonFirst;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::GetTelePortSummonFirst()
/// \brief		�ڷ���Ʈ ó�� ��ȯ �� �������� �� ������
/// \author		dhjin
/// \date		2007-11-06 ~ 2007-11-06
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::GetTelePortSummonFirst()
{
	return m_TelePortSummonFirst;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::InitmapCharacterUniqueNumberMapProject()
/// \brief		�Ʒ��� ���� - ���� �ʿ��� �������� ĳ���͵��� ����Ʈ �ʱ�ȭ
/// \author		dhjin
/// \date		2008-03-10 ~ 2008-03-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::InitmapCharacterUniqueNumberMapProject()
{
	m_mapCharacterUniqueNumberMapProject.clearLock();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::TeamArenaLeaveCommand(BYTE i_byInflMask)
/// \brief		�Ʒ��� ���� - ���� �ʿ� ���� �� ���� ���� ��θ� ���� ������ ������.
/// \author		dhjin
/// \date		2008-03-12 ~ 2008-03-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::TeamArenaLeaveCommand(BYTE i_byInflMask)
{
	vectClientIndex_t	tmClientIndexList;
	if(FALSE == this->GetAllClientIndexList(&tmClientIndexList))
	{
		return;
	}

	int nCnt = tmClientIndexList.size();
	for(int i=0; i < nCnt; i++)
	{
		CFieldIOCPSocket *pFISock = m_pFieldIOCPMapChannel->GetFieldIOCPSocket(tmClientIndexList[i]);

		if(NULL == pFISock
			|| FALSE == pFISock->IsValidCharacter(FALSE)
			|| FALSE == pFISock->IsCheckInfluenceTypeANDSocketType(i_byInflMask, ST_CLIENT_TYPE, FALSE))
		{
			continue;
		}

		// ���ñ�ȯ��Ż ���������� ����Ͽ� ���� ������ ������.
		pFISock->SendAddMessageType(T_FC_ARENA_USE_CITYWARPITEM);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::CreateKeyMonster(CFieldMonster * i_pKeyMonster)
/// \brief		���Ǵ�Ƽ(�������) - 
/// \author		dhjin
/// \date		2010-03-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::CreateKeyMonster(CFieldMonster * i_pKeyMonster)
{
	if(NULL == i_pKeyMonster) {
		return;
	}
	if(COMPARE_MPOPTION_BIT(i_pKeyMonster->MonsterInfoPtr->MPOption, MPOPTION_BIT_KEY_MONSTER))
	{
		// 2010-03-26 by cmkwon, ���Ǵ�Ƽ �ý��� �α� �߰� - 
		g_pFieldGlobal->WriteSystemLogEX(TRUE, "[Notify] [Infinity] OnCreated Key Monster !! %s MonsterUnitkind(%d) MPOPTION_BIT_KEY_MONSTER \r\n"
			, GetMapString(this->GetMapChannelIndex(), string()), i_pKeyMonster->MonsterInfoPtr->MonsterUnitKind);

		this->m_pFieldIOCPMapChannel->m_InfinityManager.CreateKeyMonster_DeadForNextStepW(this->m_MapChannelIndex.MapIndex, this->m_MapChannelIndex.ChannelIndex, i_pKeyMonster->MonsterInfoPtr->MonsterUnitKind);
	}
	else if(COMPARE_MPOPTION_BIT(i_pKeyMonster->MonsterInfoPtr->MPOption, MPOPTION_BIT_KEY_MONSTER_ALIVE_FOR_GAMECLEAR))
	{
		// 2010-03-26 by cmkwon, ���Ǵ�Ƽ �ý��� �α� �߰� - 
		g_pFieldGlobal->WriteSystemLogEX(TRUE, "[Notify] [Infinity] OnCreated Key Monster !! %s MonsterUnitkind(%d) MPOPTION_BIT_KEY_MONSTER_ALIVE_FOR_GAMECLEAR \r\n"
			, GetMapString(this->GetMapChannelIndex(), string()), i_pKeyMonster->MonsterInfoPtr->MonsterUnitKind);

		this->SetKeyMonsterClientIdx_AliveForGameClear(i_pKeyMonster);
		this->m_pFieldIOCPMapChannel->m_InfinityManager.CreateKeyMonster_AliveForGameClearW(this->m_MapChannelIndex.MapIndex, this->m_MapChannelIndex.ChannelIndex, i_pKeyMonster->MonsterInfoPtr->MonsterUnitKind);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		���Ǵ�Ƽ(�������) - 
///				// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - ����[void CFieldMapChannel::DeleteKeyMonster(CMonster * i_pKeyMonster)]
/// \author		dhjin
/// \date		2010-03-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - 
//void CFieldMapChannel::DeleteKeyMonster(CMonster *i_pKeyMonster)
void CFieldMapChannel::OnInfinityMonsterDead(CFieldMonster *i_pFMon)
{
	if(FALSE == IS_MAP_INFLUENCE_INFINITY(this->GetMapInfluenceTypeW())
		|| NULL == i_pFMon
		|| NULL == i_pFMon->MonsterInfoPtr)
	{
		return;
	}

	if(COMPARE_MPOPTION_BIT(i_pFMon->MonsterInfoPtr->MPOption, MPOPTION_BIT_KEY_MONSTER))
	{
		// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - 
		//this->m_pFieldIOCPMapChannel->m_InfinityManager.DeleteKeyMonster_DeadForNextStepW(this->m_MapChannelIndex.MapIndex, this->m_MapChannelIndex.ChannelIndex, i_pKeyMonster->MonsterInfoPtr->MonsterUnitKind);
		///////////////////////////////////////////////////////////////////////////////
		// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - 
		BOOL bCompensationFlag = FALSE;
		m_pFieldIOCPMapChannel->m_InfinityManager.DeleteKeyMonster_DeadForNextStepW(&bCompensationFlag, this->m_MapChannelIndex.MapIndex, this->m_MapChannelIndex.ChannelIndex, i_pFMon->MonsterInfoPtr->MonsterUnitKind);
		if(bCompensationFlag)
		{
			CEXPDivisionManager expDivisionMan(m_pFieldIOCPMapChannel, this);
			m_pFieldIOCPMapChannel->CreateDropItems(expDivisionMan.GetlitMonsterDropItemPtr(), i_pFMon, NULL, 0.0f, DROP_TYPE_DEAD_ALL_INFINITY_KEY_MONSTER);

			string strDropItemList;
			expDivisionMan.ProcessPickUpTenderItemsInInfinityMap(&strDropItemList, i_pFMon, &(m_pFieldIOCPMapChannel->m_InfinityManager));
		}
		
//		g_pFieldGlobal->WriteSystemLogEX(TRUE, "[TEMP] [Infinity] CFieldMapChannel::DeleteKeyMonster# 10000 KeyMonster for NextStep dead !! Map(%s) Monster(%d:%s) bCompensationFlag(%d) \r\n"
//			, GetMapString(m_MapChannelIndex, string()), i_pFMon->MonsterInfoPtr->MonsterUnitKind, i_pFMon->MonsterInfoPtr->MonsterName, bCompensationFlag);

	}
	else if(COMPARE_MPOPTION_BIT(i_pFMon->MonsterInfoPtr->MPOption, MPOPTION_BIT_KEY_MONSTER_ALIVE_FOR_GAMECLEAR))
	{
//		g_pFieldGlobal->WriteSystemLogEX(TRUE, "[TEMP] [Infinity] CFieldMapChannel::DeleteKeyMonster# 20000 MPOPTION_BIT_KEY_MONSTER_ALIVE_FOR_GAMECLEAR !! Map(%s) Monster(%d:%s) \r\n"
//			, GetMapString(m_MapChannelIndex, string()), i_pFMon->MonsterInfoPtr->MonsterUnitKind, i_pFMon->MonsterInfoPtr->MonsterName);

		this->DeadKeyMonsterClientIdx_AliveForGameClear();
		this->m_pFieldIOCPMapChannel->m_InfinityManager.DeleteKeyMonster_AliveForGameClearW(this->m_MapChannelIndex.MapIndex, this->m_MapChannelIndex.ChannelIndex, i_pFMon->MonsterInfoPtr->MonsterUnitKind);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::SetKeyMonsterClientIdx_AliveForGameClear(CFieldMonster * i_pKeyMonster)
/// \brief		���Ǵ�Ƽ(�������) - 
/// \author		dhjin
/// \date		2010-03-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::SetKeyMonsterClientIdx_AliveForGameClear(CFieldMonster * i_pKeyMonster)
{
	pKeyMonster_AliveForGameClear = i_pKeyMonster;

	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR, T_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR, pMsg, pBuf);
	pMsg->CurrentHP				= i_pKeyMonster->CurrentHP;
	pMsg->MonsterNum			= i_pKeyMonster->MonsterInfoPtr->MonsterUnitKind;
	pMsg->MonsterIdx			= i_pKeyMonster->MonsterIndex;

	// 2010. 06. 08 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (�Ʊ� ���� �뷱�� ����.)
	pMsg->MaxHP					= i_pKeyMonster->MonsterInfoExtend.fMaxHP;


	this->SendMessageToAllInChannel(pBuf, MSG_SIZE(MSG_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR));

	return TRUE;
}	

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldMapChannel::PenaltyKeyMonster_AliveForGameClear(char * i_szCharacterName, int i_PenaltyValue)
/// \brief		���Ǵ�Ƽ(�������) - 
/// \author		dhjin
/// \date		2010-03-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldMapChannel::PenaltyKeyMonster_AliveForGameClear(char * i_szCharacterName, int i_PenaltyValue)
{
	CFieldMonster *ptmFMon = pKeyMonster_AliveForGameClear;
	if(NULL == ptmFMon
		|| FALSE == ptmFMon->IsValidMonster())
	{
		return FALSE;
	}
	
	ptmFMon->DecreaseMonsterCurrentHP((ptmFMon->CurrentHP * i_PenaltyValue)/100, TRUE);
	
	// ����
	INIT_MSG_WITH_BUFFER(MSG_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP, T_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP, pMsg, pBuf);
	STRNCPY_MEMSET(pMsg->DeadCharactarName, i_szCharacterName, SIZE_MAX_CHARACTER_NAME);		// 2009-09-09 ~ 2010-01-13 by dhjin, ���Ǵ�Ƽ - ���� ���� �̸� ���� ���� �߰�,
	pMsg->CurrentHP				= ptmFMon->CurrentHP;
	pMsg->MonsterNum			= ptmFMon->MonsterInfoPtr->MonsterUnitKind;
	pMsg->MonsterIdx			= ptmFMon->MonsterIndex;
	this->SendMessageToAllInChannel(pBuf, MSG_SIZE(MSG_FC_INFINITY_CHANGE_ALIVE_FOR_GAMECLEAR_MONSTERHP));

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::DeadKeyMonsterClientIdx_AliveForGameClear()
/// \brief		���Ǵ�Ƽ(�������) - 
/// \author		dhjin
/// \date		2010-03-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::DeadKeyMonsterClientIdx_AliveForGameClear()
{
	pKeyMonster_AliveForGameClear = NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldMapChannel::SendKeyMonsterHP_AliveForGameClear(CFieldIOCPSocket * i_pFISoc)
/// \brief		���Ǵ�Ƽ(�������) - 
/// \author		dhjin
/// \date		2010-03-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldMapChannel::SendKeyMonsterHP_AliveForGameClear(CFieldIOCPSocket * i_pFISoc) 
{
	if(NULL == i_pFISoc
		|| FALSE == i_pFISoc->IsValidCharacter(FALSE))	
	{
		return;
	}

	CFieldMonster *ptmFMon = this->pKeyMonster_AliveForGameClear;
	if(NULL == ptmFMon
		|| FALSE == ptmFMon->IsValidMonster())
	{
		return;
	}

	INIT_MSG_WITH_BUFFER(MSG_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR, T_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR, pMsg, pBuf);
	pMsg->CurrentHP				= ptmFMon->CurrentHP;
	pMsg->MonsterNum			= ptmFMon->MonsterInfoPtr->MonsterUnitKind;
	pMsg->MonsterIdx			= ptmFMon->MonsterIndex;

	// 2010. 06. 08 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (�Ʊ� ���� �뷱�� ����.)
	pMsg->MaxHP					= ptmFMon->MonsterInfoExtend.fMaxHP;

	i_pFISoc->SendAddData(pBuf, MSG_SIZE(MSG_FC_MONSTER_CREATED_ALIVE_FOR_GAMECLEAR));
}



#ifdef _DEBUG

char* CFieldMapChannel::DBG_GET_CHARACTER_NAME(int idx)
{
	return ((CHARACTER*)(m_pFieldIOCPMapChannel->GetCharacterByArrayIndex(idx)))->CharacterName;
}

float CFieldMapChannel::DBG_GET_X_POSITION(int idx)
{
	if ( idx < MONSTER_CLIENT_INDEX_START_NUM )
		return ((CHARACTER*)(m_pFieldIOCPMapChannel->GetCharacterByArrayIndex(idx)))->PositionVector.x;
	else
		return GetFieldMonster(idx, 19)->PositionVector.x;
}

float CFieldMapChannel::DBG_GET_Y_POSITION(int idx)
{
	if ( idx < MONSTER_CLIENT_INDEX_START_NUM )
		return ((CHARACTER*)(m_pFieldIOCPMapChannel->GetCharacterByArrayIndex(idx)))->PositionVector.y;
	else
		return GetFieldMonster(idx, 20)->PositionVector.x;
}

float CFieldMapChannel::DBG_GET_Z_POSITION(int idx)
{
	if ( idx < MONSTER_CLIENT_INDEX_START_NUM )
		return ((CHARACTER*)(m_pFieldIOCPMapChannel->GetCharacterByArrayIndex(idx)))->PositionVector.z;
	else
		return GetFieldMonster(idx, 21)->PositionVector.z;
}


void CFieldMapChannel::DBG_PrintAllUnitPosition(void)
{
	DBGOUT("\n");
	DBGOUT("[%s\n", GET_MAP_STRING(m_MapChannelIndex));
	for (int i = 0; i < m_pMapProject->m_NUM_BLOCK_X;  i++)
	{
		for (int j = 0; j < m_pMapProject->m_NUM_BLOCK_Z;  j++)
		{
			BOOL printTail = FALSE;
			char tmpOut[1024];

			CMapBlock *pBlock = &m_arrMapBlock[i][j];
			pBlock->m_CharacterIndexMtlist.lock();
			// Block�� list�� ����
			mtlistUnitIndex_t::iterator itr(pBlock->m_CharacterIndexMtlist.begin());
			while(itr != pBlock->m_CharacterIndexMtlist.end())
			{
				sprintf(tmpOut, "MapBlock[%d][%d]: ", i, j);
				printTail = TRUE;

				char num[128];
				sprintf(num, " %d[%s] (%d,%d,%d)", *itr, DBG_GET_CHARACTER_NAME(*itr), (int)DBG_GET_X_POSITION(*itr), (int)DBG_GET_Y_POSITION(*itr), (int)DBG_GET_Z_POSITION(*itr));
				strcat(tmpOut, num);
				itr++;
			}
			pBlock->m_CharacterIndexMtlist.unlock();

			// ������
			if (printTail)
			{
				strcat(tmpOut, "\n");
				DBGOUT(tmpOut);
			}
		}
	}
	DBGOUT("\n");
}

#endif // _DEBUG