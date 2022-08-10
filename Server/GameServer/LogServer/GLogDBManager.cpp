// GLogDBManager.cpp: implementation of the CGLogDBManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLogDBManager.h"
#include "LogGlobal.h"
#include "AtumDBLogWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLogDBManager::CGLogDBManager()
:CAtumDBManager(COUNT_LOG_SERVER_DBWORKER)
{
	if(g_pLogGlobal->InMasangServer())
	{// 2006-05-21 by cmkwon
		m_dwCountDBWorker	= 3;
	}
}

CGLogDBManager::~CGLogDBManager()
{

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CGLogDBManager::InitGLogDB()
/// \brief		
/// \author		shcho, GLogDB ���� -
/// \date		2010-06-01 ~ 2010-06-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CGLogDBManager::InitGLogDB()
{
	BOOL bRet = m_OdbcStmt.Init(g_pGlobalGameServer->GetDBServerIP(), g_pGlobalGameServer->GetDBServerPort(), "GLog", (CHAR*)g_pGlobalGameServer->GetODBCUID(), (CHAR*)g_pGlobalGameServer->GetODBCPASSWORD(), g_pGlobalGameServer->GetMainWndHandle());
	if(FALSE == bRet)
	{
		// 2008-09-05 by cmkwon, DBServer ���� ���� �ý��� �α� ����� - 
		g_pGlobal->WriteSystemLogEX(TRUE, "[DB Error] fail to connect DBServer(CAtumDBManager::Init_GLogDB) !! %s,%d %s %s \r\n"
			, g_pGlobalGameServer->GetDBServerIP(), g_pGlobalGameServer->GetDBServerPort(), (CHAR*)g_pGlobalGameServer->GetODBCUID(), (CHAR*)g_pGlobalGameServer->GetODBCPASSWORD());
		return FALSE;
	}
	
	
	return TRUE;
}
BOOL CGLogDBManager::ProcessServerQuery(DB_QUERY dbquery, SQLHSTMT &hstmt, SQLHSTMT &hstmt_mc, SQLHSTMT &hstmt_extAuth)
{
	switch(dbquery.enumQuryType)
	{
	case QT_FL_GLOG_BUY_CASH_ITEM:					QP_FL_GLOG_BUY_CASH_ITEM(dbquery, hstmt);							break;
	case QT_FL_GLOG_CHARACTER_PLAY_TIME:			QP_FL_GLOG_CHARACTER_PLAY_TIME(dbquery, hstmt);						break;
	case QT_FL_GLOG_CONNECT_TOTAL_USER_COUNT:		QP_FL_GLOG_CONNECT_TOTAL_USER_COUNT(dbquery, hstmt);				break;
	case QT_FL_GLOG_CONNECT_ZONE_USER_COUNT:		QP_FL_GLOG_CONNECT_ZONE_USER_COUNT(dbquery, hstmt);					break;
	case QT_FL_GLOG_EVENT_PARTICIPATION_RATE:		QP_FL_GLOG_EVENT_PARTICIPATION_RATE(dbquery, hstmt);					break;

		
	default:
		{
			g_pGlobal->WriteSystemLogEX(TRUE, STRMSG_080904_0001, dbquery.enumQuryType, GetDBQueryTypeString(dbquery.enumQuryType));
			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CGLogDBManager::ProcessDinamicServerQuery(DB_QUERY *i_qQuery, CODBCStatement *i_pODBC)
{
	g_pGlobal->WriteSystemLogEX(TRUE, "[ERROR] CAtumLogDBManager::ProcessDinamicServerQuery# no such DB Query Type !! %d(%s)\r\n", i_qQuery->enumQuryType, GetDBQueryTypeString(i_qQuery->enumQuryType));
	return FALSE;
}

SQL_TIMESTAMP_STRUCT CGLogDBManager::GetDBCurrentdatetime()
{
	SYSTEMTIME Curtime;
	GetLocalTime(&Curtime);
 	SQL_TIMESTAMP_STRUCT cDate;
 	cDate.year = Curtime.wYear;
 	cDate.month = Curtime.wMonth;
 	cDate.day = Curtime.wDay;
 	cDate.hour = Curtime.wHour;
 	cDate.minute = Curtime.wMinute;
 	cDate.second = Curtime.wSecond;
 	cDate.fraction = Curtime.wMilliseconds * 1000000;

	return cDate;
}

void CGLogDBManager::QP_FL_GLOG_BUY_CASH_ITEM(DB_QUERY q, SQLHSTMT hstmt)
{
	MSG_FL_LOG_ITEM_BUY_ITEM *pRMsg = (MSG_FL_LOG_ITEM_BUY_ITEM*)q.pQueryParam;
	if(NULL == pRMsg)
	{
		g_pGlobal->WriteSystemLogEX(TRUE, "[ERROR] CGLogDBManager::QP_FL_GLOG_BUY_CASH_ITEM MSG_FL_LOG_ITEM_BUY_ITEM IS NULL !!\r\n");
		return;
	}
	/*[Stored Query Definition]************************************************
	CREATE PROCEDURE dbo.GLog_BuyCashItem_Insert
		@i_AccountName			[nvarchar] (128),		-- ���� �̸�
		@i_GamePublisher		[nvarchar] (128),		-- ���Ӽ��񽺻� �̸�
		@i_GameName				[nvarchar] (128),		-- ���� �̸�
		@i_CharacterName		[nvarchar] (128),		-- ������ �ɸ��� �̸�
		@i_CharacterLevel		[int],					-- ������ �ɸ��� ����
		@i_ItemName				[nvarchar] (128),		-- ������ ������ �̸�
		@i_CashCost				[int],					-- ������ ������ ���� ���� ����
		@i_ItemCount			[int],					-- ������ ������ ��
		@i_BuyDate				[datetime]				-- ���� ��¥
	AS
		INSERT INTO GLog.dbo.GLog_BuyCashItem([AccountName], [GamePublisher], [GameName], [CharacterName], [CharacterLevel], [ItemName], [CashCost], [ItemCount], [BuyDate])
			VALUES(@i_AccountName, @i_GamePublisher, @i_GameName, @i_CharacterName, @i_CharacterLevel, @i_ItemName, @i_CashCost, @i_ItemCount, @i_BuyDate)
	GO
	**************************************************************************/
	SQLBindParameter(m_OdbcStmt.m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->AccountName, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetGamePublisherName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, "ACEOnline", 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->CharacterName, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->CharacterLevel, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->ItemName, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->CashItemPrice, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->ChangeCount, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 9, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)&(this->GetDBCurrentdatetime()), 0, NULL);
	
	RETCODE ret = SQLExecDirect(m_OdbcStmt.m_hstmt, PROCEDURE_GLOG_100601_0001, SQL_NTS);
	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		ProcessLogMessages(SQL_HANDLE_STMT, m_OdbcStmt.m_hstmt, "@dbo.GLog_BuyCashItem_Insert Failed!\r\n", TRUE, q.pIOCPSocket);
		SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
		SAFE_DELETE(pRMsg);
		return;
	}
	SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
	SAFE_DELETE(pRMsg);
}

void CGLogDBManager::QP_FL_GLOG_CHARACTER_PLAY_TIME(DB_QUERY q, SQLHSTMT hstmt)
{
	MSG_FL_LOG_GAME_END *pRMsg = (MSG_FL_LOG_GAME_END*)q.pQueryParam;
	if(NULL == pRMsg)
	{
		g_pGlobal->WriteSystemLogEX(TRUE, "[ERROR] CGLogDBManager::QP_FL_GLOG_BUY_CASH_ITEM MSG_FL_LOG_GAME_END IS NULL !!\r\n");
		return;
	}
	SQL_TIMESTAMP_STRUCT cLoginDate;
	cLoginDate.year = pRMsg->LoginDate.Year;
	cLoginDate.month = pRMsg->LoginDate.Month;
	cLoginDate.day = pRMsg->LoginDate.Day;
	cLoginDate.hour = pRMsg->LoginDate.Hour;
	cLoginDate.minute = pRMsg->LoginDate.Minute;
	cLoginDate.second = pRMsg->LoginDate.Second;
	cLoginDate.fraction = 0;

	/*[Stored Query Definition]************************************************
	CREATE PROCEDURE dbo.GLog_CharacterPlayTime_Insert
		@i_AccountName				[nvarchar] (128),		-- ���� �̸�
		@i_GamePublisher			[nvarchar] (128),		-- ���Ӽ��񽺻� �̸�
		@i_GameName					[nvarchar] (128),		-- ���� �̸�
		@i_GameServerName			[nvarchar] (128),		-- ���Ӽ��� �̸�
		@i_CharacterName			[nvarchar] (128),		-- ������ �ɸ��� �̸�
		@i_LoginDate				[datetime],				-- �ɸ��� ���� ��¥
		@i_LogoutDate				[datetime],				-- �ɸ��� ���� ��¥
		@i_TotalPlayTime			[bigint],				-- �ɸ��� �����Ϻ��� ���ݱ��� �÷��� �ð�
		@i_PlayExp					[int],					-- �ɸ��� ���Ӻ��� ������� ȹ�� ����ġ
		@i_TotalExp					[bigint],				-- �ɸ��� �����Ϻ��� ���ݱ��� ȹ�� ����ġ
		@i_Race						[nvarchar] (128),		-- �ɸ��� ����
		@i_Class					[nvarchar] (128),		-- �ɸ��� ����
		@i_Level					[int],					-- �ɸ��� ���� �� ����
		@i_MostStayedInZoneName		[nvarchar] (128)		-- �ɸ��Ͱ� �����Ͽ� ����ñ��� ���� ���� �ӹ����� ���� �̸�
	AS
		INSERT INTO GLog.dbo.GLog_CharacterPlayTime([AccountName], [GamePublisher], [GameName], [GameServerName], [CharacterName], [LoginDate], [LogoutDate], [TotalPlayTime], [PlayExp], [TotalExp], [Race], [Class], [Level], [MostStayedInZoneName])
			VALUES(@i_AccountName, @i_GamePublisher, @i_GameName, @i_GameServerName, @i_CharacterName, @i_LoginDate, @i_LogoutDate,	@i_TotalPlayTime, @i_PlayExp, @i_TotalExp, @i_Race, @i_Class, @i_Level, @i_MostStayedInZoneName)
	GO
	**************************************************************************/
	SQLBindParameter(m_OdbcStmt.m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->AccountName, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetGamePublisherName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, "ACEOnline", 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetServerGroupName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->CharacterName, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)&cLoginDate, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 7, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)&(this->GetDBCurrentdatetime()), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 8, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &pRMsg->TotalPlayTime, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 9, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->PlayExp, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 10, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &pRMsg->TotalExp, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 11, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->CharacterRace, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 12, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->CharacterClass, 0, NULL);
	INT GLogTypeLevel = pRMsg->CharacterLevel;
	SQLBindParameter(m_OdbcStmt.m_hstmt, 13, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &GLogTypeLevel, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 14, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->MostStayedInZoneName, 0, NULL);
	
	RETCODE ret = SQLExecDirect(m_OdbcStmt.m_hstmt, PROCEDURE_GLOG_100601_0002, SQL_NTS);
	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		ProcessLogMessages(SQL_HANDLE_STMT, m_OdbcStmt.m_hstmt, "@dbo.GLog_CharacterPlayTime_Insert Failed!\r\n", TRUE, q.pIOCPSocket);
		SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
		SAFE_DELETE(pRMsg);
		return;
	}
	SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
	SAFE_DELETE(pRMsg);
}
void CGLogDBManager::QP_FL_GLOG_CONNECT_TOTAL_USER_COUNT(DB_QUERY q, SQLHSTMT hstmt)
{
	MSG_FL_LOG_SERVER_INFO_TOTAL *pRMsg = (MSG_FL_LOG_SERVER_INFO_TOTAL*)q.pQueryParam;
	if(NULL == pRMsg)
	{
		g_pGlobal->WriteSystemLogEX(TRUE, "[ERROR] CGLogDBManager::QP_FL_GLOG_CONNECT_TOTAL_USER_COUNT MSG_FL_LOG_SERVER_INFO_TOTAL IS NULL !!\r\n");
		return;
	}

	/*[Stored Query Definition]************************************************
	CREATE PROCEDURE dbo.GLog_ConnectTotalUserCount_Insert
		@i_Date				[datetime],					-- ���� �ð�
		@i_GamePublisher	[nvarchar] (128),			-- ���Ӽ��񽺻� �̸�
		@i_GameName			[nvarchar] (128),			-- ���� �̸�
		@i_GameServerName	[nvarchar] (128),			-- ���Ӽ��� �̸�
		@i_TotalUserCount	[int]						-- �ִ� ������ ��
	AS
		INSERT INTO GLog.dbo.GLog_ConnectTotalUserCount([Date],	[GamePublisher], [GameName], [GameServerName], [TotalUserCount])
			VALUES(@i_Date,	@i_GamePublisher, @i_GameName, @i_GameServerName, @i_TotalUserCount)
	GO
	**************************************************************************/
	SQLBindParameter(m_OdbcStmt.m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)&(this->GetDBCurrentdatetime()), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetGamePublisherName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, "ACEOnline", 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetServerGroupName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->ClientCount, 0, NULL);

	RETCODE ret = SQLExecDirect(m_OdbcStmt.m_hstmt, PROCEDURE_GLOG_100601_0003, SQL_NTS);
	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		ProcessLogMessages(SQL_HANDLE_STMT, m_OdbcStmt.m_hstmt, "@dbo.GLog_ConnectTotalUserCount_Insert Failed!\r\n", TRUE, q.pIOCPSocket);
		SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
		SAFE_DELETE(pRMsg);
		return;
	}
	SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
	SAFE_DELETE(pRMsg);
}
void CGLogDBManager::QP_FL_GLOG_CONNECT_ZONE_USER_COUNT(DB_QUERY q, SQLHSTMT hstmt)
{
	MSG_FL_LOG_SERVER_INFO_MAP *pRMsg = (MSG_FL_LOG_SERVER_INFO_MAP*)q.pQueryParam;
	if(NULL == pRMsg)
	{
		g_pGlobal->WriteSystemLogEX(TRUE, "[ERROR] CGLogDBManager::QP_FL_GLOG_CONNECT_ZONE_USER_COUNT MSG_FL_LOG_SERVER_INFO_MAP IS NULL !!\r\n");
		return;
	}

	/*[Stored Query Definition]************************************************
	CREATE PROCEDURE dbo.GLog_ConnectZoneUserCount_Insert
		@i_Date				[datetime],					-- ���� �ð�
		@i_GamePublisher	[nvarchar] (128),			-- ���Ӽ��񽺻� �̸�
		@i_GameName			[nvarchar] (128),			-- ���� �̸�
		@i_GameServerName	[nvarchar] (128),			-- ���Ӽ��� �̸�
		@i_ZoneName			[nvarchar] (128),			-- ���� ���� �̸�
		@i_ZoneUserCount	[int]						-- �ش� ���� ������ �ִ� ������ ��		
	AS
		INSERT INTO GLog.dbo.GLog_ConnectZoneUserCount([Date],	[GamePublisher], [GameName], [GameServerName], [ZoneName], [ZoneUserCount])
			VALUES(@i_Date,	@i_GamePublisher, @i_GameName, @i_GameServerName, @i_ZoneName, @i_ZoneUserCount)
	GO
	**************************************************************************/
	SQLBindParameter(m_OdbcStmt.m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)&(this->GetDBCurrentdatetime()), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetGamePublisherName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, "ACEOnline", 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetServerGroupName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, pRMsg->MapName, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->ClientCount, 0, NULL);

	RETCODE ret = SQLExecDirect(m_OdbcStmt.m_hstmt, PROCEDURE_GLOG_100601_0004, SQL_NTS);
	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		ProcessLogMessages(SQL_HANDLE_STMT, m_OdbcStmt.m_hstmt, "@dbo.GLog_ConnectZoneUserCount_Insert Failed!\r\n", TRUE, q.pIOCPSocket);
		SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
		SAFE_DELETE(pRMsg);
		return;
	}
	SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
	SAFE_DELETE(pRMsg);
}
void CGLogDBManager::QP_FL_GLOG_EVENT_PARTICIPATION_RATE(DB_QUERY q, SQLHSTMT hstmt)
{
	MSG_FL_LOG_EVENT_PARTICIPATION_RATE *pRMsg = (MSG_FL_LOG_EVENT_PARTICIPATION_RATE*)q.pQueryParam;
	if(NULL == pRMsg)
	{
		g_pGlobal->WriteSystemLogEX(TRUE, "[ERROR] CGLogDBManager::QP_FL_GLOG_EVENT_PARTICIPATION_RATE MSG_FL_LOG_EVENT_PARTICIPATION_RATE IS NULL !!\r\n");
		return;
	}
	SQL_TIMESTAMP_STRUCT cEventStartDate;
	cEventStartDate.year = pRMsg->StartTime.Year;
	cEventStartDate.month = pRMsg->StartTime.Month;
	cEventStartDate.day = pRMsg->StartTime.Day;
	cEventStartDate.hour = pRMsg->StartTime.Hour;
	cEventStartDate.minute = pRMsg->StartTime.Minute;
	cEventStartDate.second = pRMsg->StartTime.Second;
	cEventStartDate.fraction = 0;
	/*[Stored Query Definition]************************************************
	CREATE PROCEDURE dbo.GLog_EventParticipationRate_Insert
		@i_GamePublisher			[nvarchar] (128),			-- ���Ӽ��񽺻� �̸� 
		@i_GameName					[nvarchar] (128),			-- ���� �̸�
		@i_GameServerName			[nvarchar] (128),			-- ���Ӽ��� �̸�     
		@i_StartDate				[datetime],					-- �̺�Ʈ ���� ��¥
		@i_EndDate					[datetime],					-- �̺�Ʈ ���� ��¥
		@i_ParticipationCount		[int],						-- �̺�Ʈ ���� ���ο���
		@i_ParticipationRate		[smallint],					-- �̺�Ʈ ������ [0%~100%]
		@i_Description				[nvarchar] (512)			-- �̺�Ʈ ����	
	AS
		INSERT INTO GLog.dbo.GLog_EventParticipationRate([GamePublisher], [GameName], [GameServerName], [StartDate], [EndDate], [ParticipationCount], [ParticipationRate], [Description])
			VALUES(@i_GamePublisher, @i_GameName, @i_GameServerName, @i_StartDate, @i_EndDate, @i_ParticipationCount, @i_ParticipationRate, @i_Description)
	GO
	**************************************************************************/
	SQLBindParameter(m_OdbcStmt.m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetGamePublisherName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, "ACEOnline", 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 128, 0, g_pLogGlobal->GetServerGroupName(), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)&cEventStartDate, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)&(this->GetDBCurrentdatetime()), 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->ParticipationCount, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 7, SQL_PARAM_INPUT, SQL_C_USHORT, SQL_SMALLINT, 0, 0, &pRMsg->ParticipationRate, 0, NULL);
	SQLBindParameter(m_OdbcStmt.m_hstmt, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_GLOG_EVENT_DESCRIPTION, 0, pRMsg->Description, 0, NULL);
	RETCODE ret = SQLExecDirect(m_OdbcStmt.m_hstmt, PROCEDURE_GLOG_100601_0005, SQL_NTS);
	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
	{
		ProcessLogMessages(SQL_HANDLE_STMT, m_OdbcStmt.m_hstmt, "@dbo.GLog_EventParticipationRate_Insert Failed!\r\n", TRUE, q.pIOCPSocket);
		SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
		SAFE_DELETE(pRMsg);
		return;
	}
	SQLFreeStmt(m_OdbcStmt.m_hstmt, SQL_CLOSE);
	SAFE_DELETE(pRMsg);
}

