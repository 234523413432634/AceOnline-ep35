// LogIOCPSocket.h: interface for the CLogIOCPSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGIOCPSOCKET_H__23324694_E31B_4344_9DF9_F0EB3B36EED2__INCLUDED_)
#define AFX_LOGIOCPSOCKET_H__23324694_E31B_4344_9DF9_F0EB3B36EED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogIOCP.h"
#include "AtumDBManager.h"
#include "odbcstatement.h"

class CLogIOCPSocket : public CIOCPSocket
{
	friend CLogIOCP;
public:
	CLogIOCPSocket();
	virtual ~CLogIOCPSocket();

public:
	virtual BOOL OnRecvdPacketLogServer(const char* pPacket, int nLength, BYTE nSeq, char* pPeerIP = "", int nPeerPort = 0, SThreadInfo *i_pThreadInfo=NULL);
	virtual void OnConnect(void);
	virtual void OnClose(int reason);

	BOOL Process_FL_LOG_LOGIN(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_LOGOUT(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_LEVEL(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_EXP(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_STAT(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_GAME_START(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_GAME_END(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_QUEST_COMPLETION(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_QUEST_COMPENSATION(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_PKWIN(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_PKLOSS(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_PvEWIN(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_PvELOSS(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_DEAD(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_WARP(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_CREATE_CHARACTER(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_DELETE_CHARACTER(const char* pPacket, int nLength, int &nBytesUsed);

	BOOL Process_FL_LOG_ITEM_CHARACTER_ITEM(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_GET_ITEM(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_ADD_ITEM_BY_COMMAND(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_INSERT_TO_STORE(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_DRAW_FROM_STORE(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_TRADE_SEND(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_TRADE_RECV(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_THROWAWAY_ITEM(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_BUY_ITEM(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_SELL_ITEM(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_USE_ITEM(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_USE_ENERGY(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_USE_ENCHANT(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_STORE_ITEM(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_USE_MIX(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_USE_CHANGE_CHARACTER_NAME_ORIGIN(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_BAZAAR_SEND(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_BAZAAR_RECV(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_INSERT_TO_GUILDSTORE(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_DRAW_FROM_GUILDSTORE(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_ITEM_SPI(const char* pPacket, int nLength, int &nBytesUsed);			// 2006-10-27 by cmkwon
	BOOL Process_FL_LOG_ITEM_GET_ITEM_BY_ITEMEVENT(const char* pPacket, int nLength, int &nBytesUsed);	// 2007-01-11 by cmkwon
	BOOL Process_FL_LOG_WARPOINT(const char* pPacket, int nLength, int &nBytesUsed);					// 2007-05-15 by dhjin
	BOOL Process_FL_LOG_ARENA_TEAM_MATCH(const char* pPacket, int nLength, int &nBytesUsed);			// 2007-06-11 by dhjin
	BOOL Process_FL_LOG_TUTORIAL_COMPLETION(const char* pPacket, int nLength, int &nBytesUsed);			// 2007-07-06 by dhjin
	BOOL Process_FL_LOG_OUTPOST_START(const char* pPacket, int nLength, int &nBytesUsed);			// 2007-10-02 by dhjin
	BOOL Process_FL_LOG_OUTPOST_END(const char* pPacket, int nLength, int &nBytesUsed);			// 2007-10-02 by dhjin
	BOOL Process_FL_LOG_EXPEDIENCYFUND(const char* pPacket, int nLength, int &nBytesUsed);			// 2007-10-02 by dhjin

	BOOL Process_FL_LOG_SERVER_INFO_MAP(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_SERVER_INFO_TOTAL(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_HACKING_LOG(const char* pPacket, int nLength, int &nBytesUsed);

	BOOL Process_FL_LOG_SPEED_HACK(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_MEMORY_HACK(const char* pPacket, int nLength, int &nBytesUsed);

	BOOL Process_FL_LOG_MONSTER_BOSS(const char* pPacket, int nLength, int &nBytesUsed);

	//////////////////////////////////////////////////////////////////////////
	// 2008-04-01 by dhjin, ����, ������ ����â ��ȹ�� - 
	BOOL Process_FL_LOG_MS_WAR(const char* pPacket, int nLength, int &nBytesUsed);
	BOOL Process_FL_LOG_SP_WAR(const char* pPacket, int nLength, int &nBytesUsed);


	BOOL Process_FL_LOG_START_FIELD_SERVER(const char* pPacket, int nLength, int &nBytesUsed);

	BOOL Process_FL_LOG_INFLWAR_START(const char* pPacket, int nLength, int &nBytesUsed);				// 2007-10-16 by cmkwon, �α� �߰� -
	BOOL Process_FL_LOG_INFLWAR_END(const char* pPacket, int nLength, int &nBytesUsed);					// 2007-10-16 by cmkwon, �α� �߰� -
	BOOL Process_FL_LOG_OUTPOSTWAR_RESET_START(const char* pPacket, int nLength, int &nBytesUsed);		// 2007-10-16 by cmkwon, �α� �߰� -
	BOOL Process_FL_LOG_OUTPOSTWAR_RESET_DESTROY(const char* pPacket, int nLength, int &nBytesUsed);	// 2007-10-16 by cmkwon, �α� �߰� -
	BOOL Process_FL_LOG_OUTPOSTWAR_RESET_COMPLETE(const char* pPacket, int nLength, int &nBytesUsed);		// 2007-10-16 by cmkwon, �α� �߰� -
	BOOL Process_FL_LOG_OUTPOSTWAR_PROTECTOR_DESTROY(const char* pPacket, int nLength, int &nBytesUsed);// 2007-10-16 by cmkwon, �α� �߰� -
	BOOL Process_FL_LOG_OUTPOSTWAR_SET_NEXTTIME(const char* pPacket, int nLength, int &nBytesUsed);		// 2007-10-16 by cmkwon, �α� �߰� -

	BOOL Process_FL_LOG_POLL_VOTE(const char* pPacket, int nLength, int &nBytesUsed);					// 2007-11-09 by dhjin
	BOOL Process_FL_LOG_POLL_DELETE_LEADERCANDIDATE(const char* pPacket, int nLength, int &nBytesUsed);	// 2007-11-09 by dhjin
	BOOL Process_FL_LOG_DISMEMBER_GUILD(const char* pPacket, int nLength, int &nBytesUsed);				// 2007-11-09 by dhjin
	BOOL Process_FL_LOG_NOTIFY_MSG_DELETE(const char* pPacket, int nLength, int &nBytesUsed);			// 2007-11-28 by cmkwon, �����ý��� ���� -
	BOOL Process_FL_LOG_ITEM_ATTACH_ITEM(const char* pPacket, int nLength, int &nBytesUsed);			// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - 
	BOOL Process_FL_LOG_ITEM_DETACH_ITEM(const char* pPacket, int nLength, int &nBytesUsed);			// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - 
	BOOL Process_FL_LOG_ITEM_DELETE(const char* pPacket, int nLength, int &nBytesUsed);				// 2008-01-23 by cmkwon, S_F, S_L: ����/�������� ���� �α׿� �߰� - 
	BOOL Process_FL_LOG_USE_COUPON(const char* pPacket, int nLength, int &nBytesUsed);				// 2008-01-23 by cmkwon, S_F, S_L: ���� ��� ���� �α׿� �߰� - 
	
	BOOL Process_FL_LOG_WAR_CONTRIBUTION(const char* pPacket, int nLength, int &nBytesUsed);		// 2008-12-29 by dhjin, ���� ���� �߰���
	BOOL Process_FL_LOG_WAR_CONTRIBUTION_GEAR(const char* pPacket, int nLength, int &nBytesUsed);		// 2008-12-29 by dhjin, ���� ���� �߰���

	BOOL Process_FL_LOG_LUCKY_DROP(const char* pPacket, int nLength, int &nBytesUsed);		// 2009-03-31 by dhjin, ��Ű�ӽ� �α�
	BOOL Process_FL_LOG_INFINITY_START(const char* pPacket, int nLength, int &nBytesUsed);						// 193 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
	BOOL Process_FL_LOG_INFINITY_START_ITEM(const char* pPacket, int nLength, int &nBytesUsed);					// 194 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���۽� ������ ���� ����
	BOOL Process_FL_LOG_INFINITY_CINEMA(const char* pPacket, int nLength, int &nBytesUsed);						// 195 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� �α�
	BOOL Process_FL_LOG_MONSTER_SKILL(const char* pPacket, int nLength, int &nBytesUsed);						// 196 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ų ����
	BOOL Process_FL_LOG_HPACTION_TALK(const char* pPacket, int nLength, int &nBytesUsed);						// 197 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ��ȭ ����
	BOOL Process_FL_LOG_INFINITY_FIN(const char* pPacket, int nLength, int &nBytesUsed);						// 198 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� ���� ���� 
	BOOL Process_FL_LOG_INFINITY_FIN_ITEM(const char* pPacket, int nLength, int &nBytesUsed);					// 199 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ������ ���� ����
	BOOL Process_FL_LOG_INFINITY_FIN_ALIVE_KEY_MONSTER(const char* pPacket, int nLength, int &nBytesUsed);		// 200 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ����� ����ִ� ���� ����
	BOOL Process_FL_LOG_INFINITY_LEAVE_ITEM(const char* pPacket, int nLength, int &nBytesUsed);					// 201 - // 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� ���ӷα� �߰�, ���� Ż��� ������ ���� ����
	BOOL Process_FL_LOG_EVENT_PARTICIPATION_RATE(const char* pPacket, int nLength, int &nBytesUsed);			// 68 -  // 2010-06-01 by shcho, GLogDB ���� -


private:
	CODBCStatement		m_ODBCStmt;			

	static CLogIOCP		*ms_pLogIOCP;
};

#endif // !defined(AFX_LOGIOCPSOCKET_H__23324694_E31B_4344_9DF9_F0EB3B36EED2__INCLUDED_)
