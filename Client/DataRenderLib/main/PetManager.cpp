// Petmanager.cpp: implementation of the CPetdata class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AtumDatabase.h"
#include "PetManager.h"
#include "WeaponItemInfo.h"
#include "AtumData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CAtumDatabase			*g_pDatabase;

CPetManager::CPetManager()
{
	DeleteAllPetCurrentData();
	InitAttackData();
}

CPetManager::~CPetManager()
{
	DeleteAllPetCurrentData();
}
//데이터 넣기
BOOL CPetManager::InsertPetCurrentData( tPET_CURRENTINFO* i_PetCurrentInfo)
{
	if(i_PetCurrentInfo == NULL)
	{ // 데이터 없으면 리턴 
		return FALSE;
	}

	if ( GetPtr_PetCurrentData( i_PetCurrentInfo->CreatedPetUID ) )
	{
		UpdatePetCurrentData( i_PetCurrentInfo );
		return TRUE;
	}

	m_vectPetCurrentData.push_back( i_PetCurrentInfo );	
	return TRUE;
}

//데이터 업데이트
BOOL CPetManager::UpdatePetCurrentData(tPET_CURRENTINFO* i_PetCurrentInfo)
{
	if(i_PetCurrentInfo == NULL)
	{ // 데이터 없으면 리턴
		return FALSE;
	}

	vecPetCurrentInfo::iterator itr = m_vectPetCurrentData.begin();
	for( ; itr != m_vectPetCurrentData.end() ; ++itr )
	{

		tPET_CURRENTINFO *pPetCurData = (tPET_CURRENTINFO*)(*itr);

		if ( pPetCurData->CreatedPetUID == i_PetCurrentInfo->CreatedPetUID )
		{
			memcpy( pPetCurData , i_PetCurrentInfo , sizeof( tPET_CURRENTINFO ) );
			break;
		}
	}

	return TRUE;
}

//데이터 삭제
BOOL CPetManager::DeletePetCurrentData( UID64_t CreatedPetUID )
{
	int i = 0;

	vecPetCurrentInfo::iterator itr = m_vectPetCurrentData.begin();
	for( ; itr != m_vectPetCurrentData.end() ; ++itr )
	{
		// 데이터가 없으면 컨티뉴~
		if( *itr == NULL)
			continue;

		if ( (*itr)->CreatedPetUID != CreatedPetUID )
			continue;

		SAFE_DELETE ( *itr );

		m_vectPetCurrentData.erase( itr ); 

		break;
	}

	return TRUE;
}


/**************************************************************************
**
**	펫 정보 모두 삭제.
**
**	Create Info :	2010-06-15 by shcho&hslee
**
***************************************************************************/
BOOL CPetManager :: DeleteAllPetCurrentData ( void )
{

	vecPetCurrentInfo::iterator itr = m_vectPetCurrentData.begin();

	for( ; itr != m_vectPetCurrentData.end() ; ++itr )
	{
		// 데이터가 없으면 컨티뉴~
		if( *itr == NULL)
			continue;

		SAFE_DELETE ( *itr );
	}

	m_vectPetCurrentData.clear(); 

	return TRUE;

}


/**************************************************************************
**
**	펫 정보 포인터 리턴.
**
**	Create Info :	2010-06-15 by shcho&hslee
**
***************************************************************************/
tPET_CURRENTINFO *CPetManager :: GetPtr_PetCurrentData ( UID64_t PetUID )
{

	vecPetCurrentInfo::iterator itr = m_vectPetCurrentData.begin();

	for (; itr != m_vectPetCurrentData.end(); ++itr )
	{

		if ( (*itr)->CreatedPetUID == PetUID )
			return (*itr);
	}

	return NULL;

}


/**************************************************************
**
**	펫의 출력 SourceIndex값 리턴.
**
**	Create Info :	2010. 07. 09. by hsLee.
**
***************************************************************/
int CPetManager :: GetSourceIndex_PetCurrentData ( UID64_t PetUID , bool bCharacter )
{

	int iRtn_SrcIdx = 0;

	tPET_CURRENTINFO *psPetCurInfo = GetPtr_PetCurrentData( PetUID );

	if ( !psPetCurInfo )
		return iRtn_SrcIdx;

	tPET_LEVEL_DATA *psPetLevelData = g_pDatabase->GetPtr_PetLevelData ( psPetCurInfo->PetIndex , psPetCurInfo->PetLevel );

	if ( !psPetLevelData )
		return iRtn_SrcIdx;

	if ( bCharacter )
		iRtn_SrcIdx = psPetLevelData->CitySourceIndex;
	else
		iRtn_SrcIdx = psPetLevelData->FieldSourceIndex;

	return iRtn_SrcIdx;
}

void CPetManager::InitAttackData( void )
 {
// 	if(m_pPetAttack)
// 	{
// 		SAFE_DELETE(m_pPetAttack);
// 	}
// 
// 	m_pPetAttack = new ATTACK_DATA;
}
// void CPetManager::SetPetBaseData(MSG_FC_ITEM_PET_BASEDATA i_baseData)
// void CPetManager::SetPetSkillData(MSG_FC_ITEM_PET_SKILLDATA i_skillData)
// void CPetManager::SetPetSocketData(MSG_FC_ITEM_PET_SOCKETDATA i_socketData)

