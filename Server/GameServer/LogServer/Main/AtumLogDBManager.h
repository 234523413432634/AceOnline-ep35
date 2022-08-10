// AtumLogDBManager.h: interface for the CAtumLogDBManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMLOGDBMANAGER_H__27E199C3_F294_4E0C_A634_0E7656E7339A__INCLUDED_)
#define AFX_ATUMLOGDBMANAGER_H__27E199C3_F294_4E0C_A634_0E7656E7339A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumDBManager.h"

class CLogIOCP;
class CAtumLogDBManager : public CAtumDBManager  
{
public:
	CAtumLogDBManager(CLogIOCP *i_pLogIOCP);
	virtual ~CAtumLogDBManager();


	BOOL ProcessServerQuery(DB_QUERY dbquery, SQLHSTMT &hstmt, SQLHSTMT &hstmt_mc, SQLHSTMT &hstmt_extAuth);

	void QP_FL_LOG_LOGIN(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_LOGOUT(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_LEVEL(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_EXP(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_STAT(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_GAME_START(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_GAME_END(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_QUEST_COMPLETION(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_PKWIN(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_PKLOSS(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_DEAD(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_WARP(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_SPEED_HACK(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_CREATE_CHARACTER(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_DELETE_CHARACTER(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_MEMORY_HACK(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_PvEWIN(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_PvELOSS(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_CHARACTER_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_GET_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_ADD_ITEM_BY_COMMAND(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_INSERT_TO_STORE(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_DRAW_FROM_STORE(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_TRADE_SEND(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_TRADE_RECV(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_GUILD_STORE(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_THROWAWAY_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_BUY_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_SELL_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_USE_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_USE_ENERGY(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_USE_ENCHANT(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_STORE_ITEM(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_USE_MIX(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_ITEM_USE_CHANGE_CHARACTER_NAME_ORIGIN(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_SERVER_INFO_MAP(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_SERVER_INFO_TOTAL(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_MONSTER_BOSS(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_START_FIELD_SERVER(DB_QUERY q, SQLHSTMT hstmt);
	void QP_FL_LOG_MS_WAR(DB_QUERY q, SQLHSTMT hstmt);	// 2008-04-01 by dhjin, 모선전, 거점전 정보창 기획안 - 모선전 로그 추가
	void QP_FL_LOG_SP_WAR(DB_QUERY q, SQLHSTMT hstmt);	// 2008-04-01 by dhjin, 모선전, 거점전 정보창 기획안 - 거점전 로그 추가

	///////////////////////////////////////////////////////////////////////////////
	// 2008-12-01 by cmkwon, 쿼리별로 스레드를 만들어 처리하는 시스템 구축 - 
	virtual BOOL ProcessDinamicServerQuery(DB_QUERY *i_qQuery, CODBCStatement *i_pODBC);

protected:
	CLogIOCP		*m_pLogIOCP2;
};

#endif // !defined(AFX_ATUMLOGDBMANAGER_H__27E199C3_F294_4E0C_A634_0E7656E7339A__INCLUDED_)
