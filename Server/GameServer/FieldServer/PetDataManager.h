//////////////////////////////////////////////////////////////////////
//	PetDataManager.h: interface for the CPetManager class.
//
//	Create Info : 2010. 06. 16. shCho & hsLee
//
//////////////////////////////////////////////////////////////////////

#ifndef __PET_DATA_MANAGER__
#define __PET_DATA_MANAGER__

//#pragma once

#include "AtumParam.h"
#include "AtumFieldDBManager.h"

class CPetDataManager
{

	public :

		friend CAtumDBHelper;

	public :

				 CPetDataManager();
		virtual ~CPetDataManager();

		void Initialize ( void );
		void Release ( void );

		BOOL LoadDBData ( CODBCStatement *i_odbcstmt );
		BOOL LoadDB_PetBaseData ( CODBCStatement *i_odbcstmt );
		BOOL LoadDB_PetLevelData ( CODBCStatement *i_odbcstmt );
		const tPET_BASEDATA *GetPetBaseData ( const INT a_iPetIndex );
		const tPET_LEVEL_DATA *GetPetLevelData ( const INT a_iPetIndex , const INT a_Level );
		const tPET_BASE_ALL_DATA *GetPetData ( const INT a_iPetIndex );
		// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��(�� ���� ������ �ѹ� ���ϴ� �Լ� �߰�)
		INT GetPetLevelDataFromAttackItemNum ( const INT a_iPetIndex , const INT a_iPetLevel );
		// END 2010-06-15 by shcho&hslee ��ý��� - �� ���� ó��(�� ���� ������ �ѹ� ���ϴ� �Լ� �߰�)
	private :
		
		vectorPetDataInfo m_PetDataInfo;

};

#endif