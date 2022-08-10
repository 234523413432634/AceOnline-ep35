  // MapWorkspace.cpp: implementation of the CMapWorkspace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOCP.h"
#include "MapWorkspace.h"
#include <sql.h>
#include <sqlext.h>
#include "MapProject.h"
#include "Config.h"
#include "AtumDBHelper.h"
#include "AtumSJ.h"

int		CMapWorkspace::ms_nSIZE_BLOCK_X		= 0;
int		CMapWorkspace::ms_nSIZE_BLOCK_Z		= 0;

///////////////////////////////////////////////////////////////////////////////
/// \fn			BLOCK_INDEX CMapWorkspace::SelectBlockIndexWithPosition(float x, float z)
/// \brief		������ ��ǥ�� ���ϴ� Block�� index�� �����Ѵ�.
/// \author		kelovon
/// \date		2004-03-24 ~ 2004-03-24
/// \warning
///
/// \param		x [in]
/// \param		z [in]
/// \return		BLOCK_INDEX
///////////////////////////////////////////////////////////////////////////////
BLOCK_INDEX CMapWorkspace::SelectBlockIndexWithPosition(float x, float z)
{
	BLOCK_INDEX ret;

	ret.sX = (int)(x / CMapWorkspace::ms_nSIZE_BLOCK_X);
	ret.sZ = (int)(z / CMapWorkspace::ms_nSIZE_BLOCK_Z);
	return ret;
}

//////////////////////////////////////////////////////////////////////
//
//		class CMapWorkspace
//
//////////////////////////////////////////////////////////////////////

CMapWorkspace::CMapWorkspace(CIOCP* pIOCP, int nSizeBlockX, int nSizeBlockZ)
{
	m_pIOCPServer			= pIOCP;
	ms_nSIZE_BLOCK_X		= nSizeBlockX;
	ms_nSIZE_BLOCK_Z		= nSizeBlockZ;

	m_DefaultMapIndex1		= -1;

	m_vectorPtrMapProject.clear();
	m_vectorPtrMapProject.reserve(10);
	m_mapMapObjectInfo.clear();
	m_CinemaObjectNumList.clear();	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!!

	////////////////////////////////////////////////////////////////////////////
	// DB���� MapObjectInfo Loading
	if(LoadAllObjectInfofromDB() == FALSE)
	{
		char	szError[1024];
		sprintf(szError, "[Error] CMapWorkspace::CMapWorkspace_ LoadAllObjectInfofromDB_() error\r\n");
		g_pGlobal->WriteSystemLog(szError);
		DBGOUT(szError);
		return ;
	}
}

CMapWorkspace::~CMapWorkspace()
{
	CMapProject * pMapProject = NULL;
	vector<CMapProject*>::iterator i = m_vectorPtrMapProject.begin();
	for (; i != m_vectorPtrMapProject.end(); i++)
	{
		pMapProject = *i;
		SAFE_DELETE(pMapProject);
	}
	m_vectorPtrMapProject.clear();

	m_mapMapObjectInfo.clear();
	m_CinemaObjectNumList.clear();	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!!
}

////////////////////////////////////////////////////////////////////////////////
//
// �� �� �� ��  : CMapWorkspace::GetMapProjectByMapIndex
// ��ȯ�Ǵ� ��  : CMapProject*
// �� �� �� ��  : MapIndex_t Mapindex
// �� �� �� ��  : ���ڷ� ���� ���� �̸��� �ش��ϴ� CMapProject�� �����ϴ� �Լ�
//					FieldServer�� PreServer���� �����
CMapProject* CMapWorkspace::GetMapProjectByMapIndex(const MapIndex_t MapIndex)
{
	// 2007-08-30 by cmkwon, üũ �߰�
	if(0 >= MapIndex){						return NULL;}	

	vector<CMapProject*>::iterator i = m_vectorPtrMapProject.begin();

	while(i != m_vectorPtrMapProject.end())
	{
		if ((*i)->m_nMapIndex == MapIndex)
		{
			return *i;
		}
		i++;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// �� �� �� ��  : CMapWorkspace::GetMapProjectByIndex
// ��ȯ�Ǵ� ��  : CMapProject*
// �� �� �� ��  : const int index
// �� �� �� ��  : �ε����� CMapProject�� �����ϴ� �Լ�
//					NPC Server���� ���
CMapProject* CMapWorkspace::GetMapProjectByIndex(const int index)
{
	if(index >= 0 && index < (int)m_vectorPtrMapProject.size())
	{
		return m_vectorPtrMapProject[index];
	}
	return NULL;
}

BOOL CMapWorkspace::LoadAllObjectInfofromDB(void)
{
	// reset
	m_mapMapObjectInfo.clear();

	SQLHENV		henv = SQL_NULL_HENV;
	SQLHDBC		hdbc = SQL_NULL_HDBC;
	SQLHSTMT	hstmt = SQL_NULL_HSTMT;

	RETCODE	ret;
	SQLINTEGER pcbNTS = SQL_NTS;
	SQLINTEGER cb1, cb2, cb3, cb4, cb5, cb6;
	MAPOBJECTINFO	retObjInfo;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);
	ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);

	ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - �Ʒ��� ���� ���� ��
//	ret = SQLConnect(hdbc, g_pGlobalGameServer->GetODBCDSN(), SQL_NTS, g_pGlobalGameServer->GetODBCUID(), SQL_NTS, g_pGlobalGameServer->GetODBCPASSWORD(), SQL_NTS);
	char szConnectionString[512];
	char szOutConnectionString[512]; SQLSMALLINT pcb;
#if defined(DB_SERVER_MYSQL)
	sprintf(szConnectionString, "DRIVER={MySQL ODBC 5.1 Driver};SERVER=%s;ADDRESS=%s,%d;NETWORK=DBMSSOCN;UID=%s;PWD=%s;DATABASE=%s"
		, g_pGlobalGameServer->GetDBServerIP(), g_pGlobalGameServer->GetDBServerIP(), g_pGlobalGameServer->GetDBServerPort(), (char*)g_pGlobalGameServer->GetODBCUID(), (char*)g_pGlobalGameServer->GetODBCPASSWORD(), g_pGlobalGameServer->GetDBServerDatabaseName());
#else
	sprintf(szConnectionString, "DRIVER={SQL Server};SERVER=%s;ADDRESS=%s,%d;NETWORK=DBMSSOCN;UID=%s;PWD=%s;DATABASE=%s"
		, g_pGlobalGameServer->GetDBServerIP(), g_pGlobalGameServer->GetDBServerIP(), g_pGlobalGameServer->GetDBServerPort(), (char*)g_pGlobalGameServer->GetODBCUID(), (char*)g_pGlobalGameServer->GetODBCPASSWORD(), g_pGlobalGameServer->GetDBServerDatabaseName());
#endif
	ret = SQLDriverConnect(hdbc, g_pGlobalGameServer->GetMainWndHandle(), (SQLCHAR*)szConnectionString, strlen(szConnectionString), (SQLCHAR*)szOutConnectionString, 512, &pcb, SQL_DRIVER_NOPROMPT);

	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		// 2008-09-05 by cmkwon, DBServer ���� ���� �ý��� �α� ����� - 
		g_pGlobal->WriteSystemLogEX(TRUE, "[DB Error] fail to connect DBServer(CMapWorkspace::LoadAllObjectInfofromDB_) !! %s,%d %s %s %s\r\n"
			, g_pGlobalGameServer->GetDBServerIP(), g_pGlobalGameServer->GetDBServerPort(), g_pGlobalGameServer->GetDBServerDatabaseName(), (CHAR*)g_pGlobalGameServer->GetODBCUID(), (CHAR*)g_pGlobalGameServer->GetODBCPASSWORD());
		// error
		CAtumDBHelper::ProcessLogMessagesStatic(SQL_HANDLE_DBC, hdbc, "", TRUE);

		return FALSE;
	}

	// prints DB Info
	char DatabaseName[40];
	char DSN[40];
	SQLSMALLINT StrLen;
	SQLGetInfo(hdbc, SQL_DATABASE_NAME, (SQLPOINTER)DatabaseName, sizeof(DatabaseName), &StrLen);
	SQLGetInfo(hdbc, SQL_DATA_SOURCE_NAME, (SQLPOINTER)DSN, sizeof(DSN), &StrLen);

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

	// 2008-07-02 by cmkwon, MySQL ���� ���� - 
	//ret = SQLExecDirect(hstmt, (UCHAR*)"SELECT Code, Alpha, Collision, CollisionForServer,\
	//											RenderIndex, ObjectRenderType FROM ti_MapObject WITH (NOLOCK)", SQL_NTS);
// 2008-08-27 by cmkwon, �������� Procedure�� ���� - 
//	ret = SQLExecDirect(hstmt, (UCHAR*)QUERY_080702_0244, SQL_NTS);
	ret = SQLExecDirect(hstmt, (UCHAR*)PROCEDURE_080827_0244, SQL_NTS);

	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		// error
		CAtumDBHelper::ProcessLogMessagesStatic(SQL_HANDLE_STMT, hstmt, "", TRUE);

		return FALSE;
	}

	SQLBindCol(hstmt, 1, SQL_C_LONG, &retObjInfo.Code, 0, &cb1);
	SQLBindCol(hstmt, 2, SQL_C_TINYINT, &retObjInfo.Alpha, 0, &cb2);
	SQLBindCol(hstmt, 3, SQL_C_TINYINT, &retObjInfo.Collision, 0, &cb3);
	SQLBindCol(hstmt, 4, SQL_C_TINYINT, &retObjInfo.CollisionForServer, 0, &cb4);
	SQLBindCol(hstmt, 5, SQL_C_USHORT, &retObjInfo.RenderIndex, 0, &cb5);
	SQLBindCol(hstmt, 6, SQL_C_TINYINT, &retObjInfo.ObjectRenderType, 0, &cb6);

	int nObjects = 0;
	memset(&retObjInfo, 0x00, sizeof(MAPOBJECTINFO));
	while ( (ret = SQLFetch(hstmt)) != SQL_NO_DATA)
	{
		m_mapMapObjectInfo.insertEZ(retObjInfo.Code, retObjInfo);

		nObjects++;
		memset(&retObjInfo, 0x00, sizeof(MAPOBJECTINFO));
	}
// 2005-12-16 by cmkwon
//	DBGOUT("MapObjectInfo Total Count: %d\n", nObjects);

	SQLFreeStmt(hstmt, SQL_CLOSE);

	////////////////////////////////////////////////////////////////////////////////
	// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ������Ʈ�� ����!!!!
	m_CinemaObjectNumList.clear();
	ret = SQLExecDirect(hstmt, (UCHAR*)PROCEDURE_090909_0501, SQL_NTS);
	
	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		// error
		CAtumDBHelper::ProcessLogMessagesStatic(SQL_HANDLE_STMT, hstmt, "", TRUE);
		
		return FALSE;
	}
	
	CINEMAINFO		tmCinemaInfo;
	MEMSET_ZERO(&tmCinemaInfo, sizeof(CINEMAINFO));

	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - 
	SQLINTEGER	arrCB[28] = {SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS,	SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS
							, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS,	SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS
							, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS,	SQL_NTS, SQL_NTS, SQL_NTS };	// 2010-03-31 by dhjin, ���Ǵ�Ƽ(�������) - // 2011-03-09 by hskim, �ó׸� ����Ʈ �ε��� ���� �߰� - // 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�
	SQLBindCol(hstmt, 1, SQL_C_ULONG, &tmCinemaInfo.CinemaNum,			0, &arrCB[1]);
	SQLBindCol(hstmt, 2, SQL_C_ULONG, &tmCinemaInfo.CinemaOrder,		0, &arrCB[2]);
	SQLBindCol(hstmt, 3, SQL_C_ULONG, &tmCinemaInfo.StartTime,			0, &arrCB[3]);
	SQLBindCol(hstmt, 4, SQL_C_ULONG, &tmCinemaInfo.EffectIdx,			0, &arrCB[4]);
	SQLBindCol(hstmt, 5, SQL_C_FLOAT, &tmCinemaInfo.EffectPosition_X,	0, &arrCB[5]);
	SQLBindCol(hstmt, 6, SQL_C_FLOAT, &tmCinemaInfo.EffectPosition_Y,	0, &arrCB[6]);
	SQLBindCol(hstmt, 7, SQL_C_FLOAT, &tmCinemaInfo.EffectPosition_Z,	0, &arrCB[7]);
	SQLBindCol(hstmt, 8, SQL_C_ULONG, &tmCinemaInfo.EffectPlayTime,		0, &arrCB[8]);
	SQLBindCol(hstmt, 9, SQL_C_ULONG, &tmCinemaInfo.EffectPlayCount,	0, &arrCB[9]);
	SQLBindCol(hstmt, 10, SQL_C_USHORT, &tmCinemaInfo.ObjectIdx,		0, &arrCB[10]);
	SQLBindCol(hstmt, 11, SQL_C_ULONG, &tmCinemaInfo.ChangeObjectIdx,	0, &arrCB[11]);
	SQLBindCol(hstmt, 12, SQL_C_ULONG, &tmCinemaInfo.ChangeTime,		0, &arrCB[12]);
	SQLBindCol(hstmt, 13, SQL_C_ULONG, &tmCinemaInfo.CameraTremble,		0, &arrCB[13]);
	SQLBindCol(hstmt, 14, SQL_C_TINYINT, &tmCinemaInfo.KeyMonster,		0, &arrCB[14]);
	SQLBindCol(hstmt, 15, SQL_C_ULONG, &tmCinemaInfo.MonsterIdx,		0, &arrCB[15]);
	SQLBindCol(hstmt, 16, SQL_C_ULONG, &tmCinemaInfo.SummonCount,		0, &arrCB[16]);
	SQLBindCol(hstmt, 17, SQL_C_ULONG, &tmCinemaInfo.SummonRandomPos,	0, &arrCB[17]);
	SQLBindCol(hstmt, 18, SQL_C_ULONG, &tmCinemaInfo.ObjectBodyConditionIdx,	0, &arrCB[18]);
	SQLBindCol(hstmt, 19, SQL_C_UBIGINT, &tmCinemaInfo.BodyCondition,	0, &arrCB[19]);
	SQLBindCol(hstmt, 20, SQL_C_CHAR, tmCinemaInfo.TipFileName,		SIZE_MAX_FILE_NAME, &arrCB[20]);
	SQLBindCol(hstmt, 21, SQL_C_CHAR, tmCinemaInfo.SkyFileName,		SIZE_MAX_FILE_NAME, &arrCB[21]);	
	SQLBindCol(hstmt, 22, SQL_C_CHAR, tmCinemaInfo.CinemaTalk,		SIZE_MAX_CINEMATALK_DESCRIPTION,&arrCB[22]);
	SQLBindCol(hstmt, 23, SQL_C_CHAR, tmCinemaInfo.SoundFileName,	SIZE_MAX_FILE_NAME,	&arrCB[23]);		// 2010-03-29 by cmkwon, ����2�� �ó׸��� ȿ���� ���� ���� �߰� - 
	// start 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�
	SQLBindCol(hstmt, 24, SQL_C_ULONG, &tmCinemaInfo.QuestIndex,		0, &arrCB[24]);		// 2011-03-09 by hskim, �ó׸� ����Ʈ �ε��� ���� �߰� -
	SQLBindCol(hstmt, 25, SQL_C_ULONG, &tmCinemaInfo.MonsterIdxType,	0, &arrCB[25]);
	SQLBindCol(hstmt, 26, SQL_C_ULONG, &tmCinemaInfo.CustomIdx,			0, &arrCB[26]);
	SQLBindCol(hstmt, 27, SQL_C_ULONG, &tmCinemaInfo.UpdateMonsterIdx,	0, &arrCB[27]);
	// end 2011-04-28 by hskim, ���Ǵ�Ƽ 3�� - �ó׸� ���� ��� �߰�

	while ( (ret = SQLFetch(hstmt)) != SQL_NO_DATA) {
		m_CinemaObjectNumList.push_back(tmCinemaInfo.ChangeObjectIdx);
		MEMSET_ZERO(&tmCinemaInfo, sizeof(CINEMAINFO));
	}
	
	SQLFreeStmt(hstmt, SQL_CLOSE);

	// cleanup odbc resources
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	SQLDisconnect(hdbc);
#ifndef _DEBUG
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
#endif
	SQLFreeHandle(SQL_HANDLE_ENV, henv);

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CMapWorkspace::ChangeMapInfluenceType2AllConflictArea(SHORT i_sMapInflTy, BOOL i_bAdd)	// 2009-01-12 by dhjin, ���� ���� - ���� �߰� ��Ʈ
/// \brief		
/// \author		cmkwon
/// \date		2006-02-09 ~ 2006-02-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CMapWorkspace::ChangeMapInfluenceType2AllConflictArea(SHORT i_sMapInflTy, BOOL i_bAdd)	// 2009-01-12 by dhjin, ���� ���� - ���� �߰� ��Ʈ
{
	int nCount = 0;
	for(int i=0; i < m_vectorPtrMapProject.size(); i++)
	{
		if(m_vectorPtrMapProject[i]->SetMapInfluenceType2ConflictArea(i_sMapInflTy, i_bAdd))	// 2009-01-12 by dhjin, ���� ���� - ���� �߰� ��Ʈ)
		{
			nCount;
		}
	}

	return nCount;		// 2006-02-09 by cmkwon, ����� MapProject ī��Ʈ
}


// 2008-09-10 by cmkwon, ���վƷ��� �ʼ���(map.cfg) ���� ���� - 
//BOOL CMapWorkspace::LoadAllProject(const char* pFileName)
BOOL CMapWorkspace::LoadAllProject(const char* pFileName, BOOL i_bIsArenaServer, vectMapIndexList *i_pvectArenaMapIndexList)
{
	const int SIZE_BUFF = 512;
	char buff[SIZE_BUFF];
	const char *token;
	char seps[] = " \t";
	CConfig		config;

	if (!config.LoadUserDefinedVariables(GLOBAL_CONFIG_FILE_PATH))
	{
		char	szError[1024];
		sprintf(szError, "[Error] LoadConfiguration LoadUserDefinedVariables() error, FileName[%s]\r\n"
			, GLOBAL_CONFIG_FILE_PATH);
		g_pGlobal->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	if (!config.LoadUserDefinedVariables(pFileName))
	{
		char	szError[1024];
		sprintf(szError, "[Error] CMapWorkspace::LoadAllProject_1 LoadUserDefinedVariables() error, FileName[%s]\r\n"
			, pFileName);
		g_pGlobal->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	ifstream fin;

	fin.open(pFileName);

	if (! fin.is_open())
	{	// cannot open file...

		int nErr = GetLastError();
		SetLastError(0);
		char	szError[1024];
		sprintf(szError, "[Error] CMapWorkspace::LoadAllProject_2 open() error, LastError[%d] ConfigFileName[%s]\r\n"
			, nErr, pFileName);
		g_pGlobal->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	BOOL		 bDefaultMapNameLoaded	= FALSE;
	while(TRUE)
	{
		memset(buff, 0x00, SIZE_BUFF);
		BOOL bFlagFileEnd = fin.getline(buff, SIZE_BUFF).eof();
		if(bFlagFileEnd == TRUE
			&& strcmp(buff, "") == 0)
		{
			break;
		}

		token = strtok(buff, seps);

		if (token == NULL
			|| strncmp(token, "#", 1) == 0
			|| strncmp(token, "$", 1) == 0)
		{	// ignore blank lines
			// ignore comments
			// ignore user defined variables

			continue;
		}

		if (!bDefaultMapNameLoaded)
		{
			if ( strcmp(token, "ServerGroupDefaultMap") != 0)
			{
				// map config file error!
				return FALSE;
			}

			token = config.strtok(NULL, seps);
			m_DefaultMapIndex1 = atoi(token);
			bDefaultMapNameLoaded = TRUE;
			continue;
		}

		PROJECTINFO		tempProjectInfo;
		memset(&tempProjectInfo, 0x00, sizeof(PROJECTINFO));

		// DefaultMapIndex�� ����
		tempProjectInfo.m_DeadDefaultMapIndex = m_DefaultMapIndex1;

		// MapName
		tempProjectInfo.m_nMapIndex = atoi(token);

		// ChannelCounts
		token = config.strtok(NULL, seps);
		tempProjectInfo.m_nCreateChannelCounts = max(1, atoi(token));

// 2005-06-22 by cmkwon
//		// MaxAltitude
//		token = config.strtok(NULL, seps);
//		tempProjectInfo.m_sMaximumAltitude = atoi(token);
//
//		// MinAltitude
//		token = config.strtok(NULL, seps);
//		tempProjectInfo.m_sMinimumAltitude = atoi(token);
//
//		// WaterHeight
//		token = config.strtok(NULL, seps);
//		tempProjectInfo.m_sWaterAltitude = atoi(token);

		// AutoCreateMonster, �ʿ� ������ ���� ������ ���� ���͸� �����ϴ����� Flag
		token = config.strtok(NULL, seps);
		if (stricmp(token, "TRUE") == 0) { tempProjectInfo.m_bAutoCreateMonster = TRUE; }
		else { tempProjectInfo.m_bAutoCreateMonster = FALSE; }
// 2005-06-22 by cmkwon
//		// 2004-11-22 by cmkwon, MaxUserCountsPerChannel
//		token = config.strtok(NULL, seps);
//		tempProjectInfo.m_dwMaxUserCounts = atoi(token);

		// FieldIP
		token = config.strtok(NULL, seps);
		STRNCPY_MEMSET(tempProjectInfo.m_strFieldIP, token, SIZE_MAX_IPADDRESS);

		// ListenPort
		token = config.strtok(NULL, seps);
		tempProjectInfo.m_sFieldListenPort = atoi(token);

		// UDPPort
		token = config.strtok(NULL, seps);
		tempProjectInfo.m_sFieldUDPPort = atoi(token);

		// NPCIP
		token = config.strtok(NULL, seps);
		STRNCPY_MEMSET(tempProjectInfo.m_strNPCIP, token, SIZE_MAX_IPADDRESS);

		// ListenPort
		token = config.strtok(NULL, seps);
		tempProjectInfo.m_sNPCListenPort = atoi(token);

		// UDPPort
		token = config.strtok(NULL, seps);
		tempProjectInfo.m_sNPCUDPPort = atoi(token);

		// MapXSize
		token = config.strtok(NULL, seps);
		tempProjectInfo.m_sXSize = atoi(token);

		// MapYSize
		token = config.strtok(NULL, seps);
		tempProjectInfo.m_sYSize = atoi(token);
// 2005-06-22 by cmkwon
//		// FrontPositionDistance ������ ��, ������Ʈ �浹 üũ�� ���� ���� ��ǥ�� �Ÿ���, ũ�� �̸� ȸ���� �Ѵ� 
//		token = config.strtok(NULL, seps); 
//		tempProjectInfo.m_fFrontPositionDistance = atof(token);

		// CreateNPCThread, NPC Server���� �ʿ� ���͸� ���� Thread�� �����ϴ����� Flag
		token = config.strtok(NULL, seps);
		if (stricmp(token, "TRUE") == 0) { tempProjectInfo.m_bCreateNPCThread = TRUE; }
		else { tempProjectInfo.m_bCreateNPCThread = FALSE; }

// 2005-06-22 by cmkwon
//		// TutorialMap
//		token = config.strtok(NULL, seps);
//		if (stricmp(token, "TRUE") == 0) { tempProjectInfo.m_bTutorialMap = TRUE; }
//		else { tempProjectInfo.m_bTutorialMap = FALSE; }
//
//		// ĳ���� ���� �ʿ��� �׾����� ���ư� DefaultMap
//		token = config.strtok(NULL, seps);
//		tempProjectInfo.m_DeadDefaultMapIndex = atoi(token);
//
//		// GuildWarMap
//		token = config.strtok(NULL, seps);
//		if (stricmp(token, "TRUE") == 0) { tempProjectInfo.m_bGuildWarMap = TRUE; }
//		else { tempProjectInfo.m_bGuildWarMap = FALSE; }
//
//		// AutoDPRecovery
//		token = config.strtok(NULL, seps);
//		if (stricmp(token, "TRUE") == 0) { tempProjectInfo.m_bAutoDPRecovery = TRUE; }
//		else { tempProjectInfo.m_bAutoDPRecovery = FALSE; }
//
//		// ���� ���̸� ���� ���� Ÿ�� ��ǥ ����
//		if (IS_CITY_MAP_INDEX(tempProjectInfo.m_nMapIndex))
//		{
//			tempProjectInfo.m_CityWarpTargetPosition = config.getPosition(NULL);
//		}
//		else
//		{
//			tempProjectInfo.m_CityWarpTargetPosition = D3DXVECTOR3(0, 0, 0);
//		}

// check: MapChannel ������, 20040322, kelovon
//		///////////////////////////////////////////////////////////////////////
//		// User-Friedly Map Name �Ҵ� -> check: �ð����� config�� �ű��!
//		///////////////////////////////////////////////////////////////////////
//		strncpy(pMapProject->m_bUserFriendlyMapName
//			, GetUserFriendlyMapName(tempProjectInfo.m_strFieldIP)
//			, SIZE_MAX_MAP_NAME);
//		///////////////////////////////////////////////////////////////////////
//		// User-Friedly Map Name �Ҵ� -> check: �ð����� config�� �ű��!
//		///////////////////////////////////////////////////////////////////////
		token = strtok(NULL, seps);

		if (token != NULL)
		{
			// invalid format
			return FALSE;
		}
		
		if(ST_FIELD_SERVER == m_pIOCPServer->GetServerType())
		{	// Field Server�� �ڽ��� �������� �ʴ� �ʵ� ��� loading �Ѵ�

		}
		else if(ST_NPC_SERVER == m_pIOCPServer->GetServerType())
		{	// NPC Server�� Local IP�� ���� �͸� loading �Ѵ�.

			if(0 != strcmp(tempProjectInfo.m_strNPCIP, m_pIOCPServer->GetLocalIPAddress()))
			{
				continue;
			}
		}
		else
		{
			ASSERT_NEVER_GET_HERE();
			continue;
		}

		///////////////////////////////////////////////////////////////////////////////
		// 2008-09-10 by cmkwon, ���վƷ��� �ʼ���(map.cfg) ���� ���� - 
		if(FALSE == i_bIsArenaServer)
		{
			vectMapIndexList::iterator itr = find(i_pvectArenaMapIndexList->begin(), i_pvectArenaMapIndexList->end(), tempProjectInfo.m_nMapIndex);
			if(itr != i_pvectArenaMapIndexList->end())
			{// 2008-09-10 by cmkwon, �Ʒ�����(ArenaMap)�̶�� �ε� �ʿ� ����.
				continue;
			}
		}
		else
		{
			if(FALSE == IS_INFLUENCE_CITY_MAP_INDEX(tempProjectInfo.m_nMapIndex))
			{
				vectMapIndexList::iterator itr = find(i_pvectArenaMapIndexList->begin(), i_pvectArenaMapIndexList->end(), tempProjectInfo.m_nMapIndex);
				if(itr == i_pvectArenaMapIndexList->end())
				{// 2008-09-10 by cmkwon, �Ʒ�����(ArenaMap)�� �ƴ϶�� �ε� �ʿ� ����.
					continue;
				}
			}
		}

		///////////////////////////////////////////////////////////////////////////////
		// DB�� ������ Map �Ķ���� �����ϱ�
		const MAP_INFO *pMapInfo = CAtumSJ::GetMapInfo(tempProjectInfo.m_nMapIndex);
		if(NULL == pMapInfo)
		{
			char	szError[1024];
			sprintf(szError, "[Error] CMapWorkspace::LoadAllProject_4 Can't InitMapProject, ProjectName[%4d]\r\n"
				, tempProjectInfo.m_nMapIndex);
			g_pGlobal->WriteSystemLog(szError);
			DBGOUT(szError);
			
			continue;
		}
		tempProjectInfo.m_dwMaxUserCounts			= pMapInfo->MaxUserCount;
		tempProjectInfo.m_sMaximumAltitude			= pMapInfo->MaxGroundHeight;
		tempProjectInfo.m_sMinimumAltitude			= pMapInfo->MinGroundHeight;
		tempProjectInfo.m_sWaterAltitude			= pMapInfo->WaterHeight;
		tempProjectInfo.m_bAutoDPRecovery			= pMapInfo->AutoRecoveryFlag;
		tempProjectInfo.m_fFrontPositionDistance	= pMapInfo->FrontPositionDistance;
		tempProjectInfo.m_DeadDefaultMapIndex		= pMapInfo->DefaultMapIndex;
		tempProjectInfo.m_bAutoDPRecovery			= pMapInfo->AutoRecoveryFlag;
		tempProjectInfo.m_CityWarpTargetPosition	= A2DX(pMapInfo->CityWarpTargetPosition);
		tempProjectInfo.m_nUserVisibleDiameter		= pMapInfo->UserVisibleDistance * 2;
		tempProjectInfo.m_nMonsterVisibleDiameter	= pMapInfo->MonsterVisibleDistance * 2;
		tempProjectInfo.m_nQuestIndexForWarp		= pMapInfo->QuestIndexForWarp;
		tempProjectInfo.m_nMapInfluenceType			= pMapInfo->MapInfluenceType;				// 2005-12-28 by cmkwon
		tempProjectInfo.m_nBeforeMapIndex			= pMapInfo->BeforeMapIndex;					// 2006-08-02 by cmkwon
		tempProjectInfo.m_VCNWarpObjectIndex		= pMapInfo->VCNWarpObjectIndex;				// 2006-12-08 by cmkwon
		tempProjectInfo.m_ANIWarpObjectIndex		= pMapInfo->ANIWarpObjectIndex;				// 2006-12-08 by cmkwon
		tempProjectInfo.m_TeleportWarpObjectIndex	= pMapInfo->TeleportWarpObjectIndex;		// 2007-09-15 by dhjin
		tempProjectInfo.m_nBeforeMapIndex2			= pMapInfo->BeforeMapIndex2;				// 2008-06-20 by cmkwon, EP3 ��� �ý��� ����(�ʴ� ����� 2�� ���� �� �� �ִ�) - 

		///////////////////////////////////////////////////////////////////////////////
		// 
		CMapProject *pMapProject = CreateChildMapProject(&tempProjectInfo);
		ASSERT_ASSERT(pMapProject != NULL);

		if(pMapProject->InitMapProject() == FALSE)
		{
			char	szError[1024];
			sprintf(szError, "[Error] CMapWorkspace::LoadAllProject_3 Can't InitMapProject, ProjectName[%4d]\r\n"
				, pMapProject->m_nMapIndex);
			g_pGlobal->WriteSystemLog(szError);
			DBGOUT(szError);

			SAFE_DELETE(pMapProject);
			continue;
		}

		m_vectorPtrMapProject.push_back(pMapProject);
		if(m_vectorPtrMapProject.size() > CLIENT_INDEX_START_NUM)
		{
			char	szError[1024];
			sprintf(szError, "[Error] LoadConfiguration invalid MapProject Size, size[%d] MaxSize[%d]\r\n"
				, m_vectorPtrMapProject.size(), CLIENT_INDEX_START_NUM);
			g_pGlobal->WriteSystemLog(szError);
			DBGOUT(szError);
			return FALSE;
		}

		///////////////////////////////////////////////////////////////////////////////		
		// 2010-04-08 by cmkwon, �������� �ʷε��� AlivePacket ���� �߰� - ���� 10�� �ε��ϰ� ��Ŷ�� �����Ѵ�.
		if(0 == m_vectorPtrMapProject.size()%10)
		{
			g_pGlobal->WriteSystemLogEX(TRUE, "  [Notify] CMapWorkspace::LoadAllProject# sent AlivePacket ! MapProjectListCnt(%d) \r\n", m_vectorPtrMapProject.size());

			m_pIOCPServer->SendAlivePacket2OtherServers();
		}
	}

	return TRUE;
}



///////////////////////////////////////////////////////////////////////////////
/// \fn			CMapProject * CMapWorkspace::CreateChildMapProject(PROJECTINFO * i_pProjectInfo)
/// \brief
/// \author		cmkwon
/// \date		2004-03-26 ~ 2004-03-26
/// \warning
///
/// \param
/// \return
///////////////////////////////////////////////////////////////////////////////
CMapProject * CMapWorkspace::CreateChildMapProject(PROJECTINFO * i_pProjectInfo)
{
	ASSERT_NEVER_GET_HERE();
	return NULL;
}