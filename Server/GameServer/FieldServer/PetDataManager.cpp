
//////////////////////////////////////////////////////////////////////
//	PetDataManager.cpp: interface for the CPetManager class.
//
//	Create Info : 2010. 06. 16. shCho & hsLee
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "PetDataManager.h"


CPetDataManager :: CPetDataManager()
{
	Initialize();
}

CPetDataManager :: ~CPetDataManager()
{
	Release();
}
	

void CPetDataManager :: Initialize ( void )
{
	vectorPetDataInfo::iterator iter = m_PetDataInfo.begin();
	for(;iter!=m_PetDataInfo.end();++iter)
	{
		iter->vectPetLevelDataInfo.clear();
	}
	m_PetDataInfo.clear();
}

BOOL CPetDataManager :: LoadDBData ( CODBCStatement *i_odbcstmt )
{

	if ( NULL == i_odbcstmt )
		return FALSE;

	if ( FALSE == LoadDB_PetBaseData( i_odbcstmt ) )
		return FALSE;

	if ( FALSE == LoadDB_PetLevelData( i_odbcstmt ) )
		return FALSE;

	return TRUE;
	
}


BOOL CPetDataManager :: LoadDB_PetBaseData ( CODBCStatement *i_odbcstmt )
{
	if ( NULL == i_odbcstmt )
		return FALSE;
	
	Release();

	return CAtumDBHelper::DBLoadPetBaseDataInfo( i_odbcstmt , &m_PetDataInfo );
}

BOOL CPetDataManager :: LoadDB_PetLevelData ( CODBCStatement *i_odbcstmt )
{
	if ( NULL == i_odbcstmt )
		return FALSE;

	return CAtumDBHelper::DBLoadPetLevelDataInfo ( i_odbcstmt , &m_PetDataInfo );
}

void CPetDataManager :: Release ( void )
{
	vectorPetDataInfo::iterator iter = m_PetDataInfo.begin();
	for(;iter!=m_PetDataInfo.end();++iter)
	{
		iter->vectPetLevelDataInfo.clear();
	}
	m_PetDataInfo.clear();
}

const tPET_LEVEL_DATA *CPetDataManager::GetPetLevelData ( const INT a_iPetIndex , const INT a_iPetLevel )
{
	const tPET_BASE_ALL_DATA *a_pData = GetPetData(a_iPetIndex);
	if(NULL == a_pData)
	{
		return NULL;
	}

	vectorPetLevelData::const_iterator cst_iter = a_pData->vectPetLevelDataInfo.begin();
	for(; cst_iter != a_pData->vectPetLevelDataInfo.end() ; ++cst_iter )
	{
		if(cst_iter->Level == a_iPetLevel)
		{
			return &*cst_iter;
		}
	}

	return NULL;
	
}

const tPET_BASEDATA *CPetDataManager::GetPetBaseData ( const INT a_iPetIndex )
{
	vectorPetDataInfo::iterator iter = m_PetDataInfo.begin();
	for( ; iter != m_PetDataInfo.end() ; ++iter )
	{
		if( a_iPetIndex == iter->BaseData.PetIndex )	
		{
			return &iter->BaseData;
		}
	}
	return NULL;
}

const tPET_BASE_ALL_DATA *CPetDataManager::GetPetData( const INT a_iPetIndex )
{
	vectorPetDataInfo::iterator it = m_PetDataInfo.begin();
	
	for (; it != m_PetDataInfo.end(); ++it )
	{
		if ( it->BaseData.PetIndex == a_iPetIndex )
		{
			return &*it;
		}
	}
	return NULL;
}

INT CPetDataManager::GetPetLevelDataFromAttackItemNum ( const INT a_iPetIndex , const INT a_iPetLevel )
{
	const tPET_BASE_ALL_DATA *a_pData = GetPetData(a_iPetIndex);
	if(NULL == a_pData)
	{
		return NULL;
	}

	vectorPetLevelData::const_iterator cst_iter = a_pData->vectPetLevelDataInfo.begin();
	for(; cst_iter != a_pData->vectPetLevelDataInfo.end() ; ++cst_iter )
	{
		if(cst_iter->Level == a_iPetLevel)
		{
			return cst_iter->PetAttackIndex;
		}
	}

	return NULL;
	
}

