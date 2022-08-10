// GLogDBManager.h: interface for the CGLogDBManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOGDBMANAGER_H__0D10233B_B919_4E3A_94FA_BD9DD1E4091E__INCLUDED_)
#define AFX_GLOGDBMANAGER_H__0D10233B_B919_4E3A_94FA_BD9DD1E4091E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\COMMONGAMESERVER\AtumDBManager.h"

class CGLogDBManager : public CAtumDBManager  
{
public:
	CGLogDBManager();
	virtual ~CGLogDBManager();

	BOOL InitGLogDB();		// 2010-06-01 by shcho, GLogDB ���� -
	BOOL ProcessServerQuery(DB_QUERY dbquery, SQLHSTMT &hstmt, SQLHSTMT &hstmt_mc, SQLHSTMT &hstmt_extAuth);
	virtual BOOL ProcessDinamicServerQuery(DB_QUERY *i_qQuery, CODBCStatement *i_pODBC);

private:
	void QP_FL_GLOG_BUY_CASH_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_GLOG_CHARACTER_PLAY_TIME(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_GLOG_CONNECT_TOTAL_USER_COUNT(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_GLOG_CONNECT_ZONE_USER_COUNT(DB_QUERY q, SQLHSTMT hstmt);
	//GLog_Event_Insert	��������.
	void QP_FL_GLOG_EVENT_PARTICIPATION_RATE(DB_QUERY q, SQLHSTMT hstmt);

	SQL_TIMESTAMP_STRUCT GetDBCurrentdatetime();			// DB ����Ÿ���� datetime�� �� ������ ���� ���� �ð��� �����´�.

private:
	CODBCStatement			m_OdbcStmt;
};

#endif // !defined(AFX_GLOGDBMANAGER_H__0D10233B_B919_4E3A_94FA_BD9DD1E4091E__INCLUDED_)
