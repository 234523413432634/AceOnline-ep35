// FieldGlobal.h: interface for the CFieldGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDGLOBAL_H__B6793946_A3E2_4778_A6DA_1EE835B77558__INCLUDED_)
#define AFX_FIELDGLOBAL_H__B6793946_A3E2_4778_A6DA_1EE835B77558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SIZE_FIELD2LOG_WINSOCKET		10

class CLogWinSocket;
typedef vector<CLogWinSocket*>			vectorF2LWSocketPtr;
typedef set<string>						setstring;					// 2006-08-18 by dhjin

class CFieldGlobal;
extern CFieldGlobal *			g_pFieldGlobal;

///////////////////////////////////////////////////////////////////////////////
/// \class		CFieldGlobal
///
/// \brief		
/// \author		cmkwon
/// \version	
/// \date		2004-03-19 ~ 2004-03-19
/// \warning	
///////////////////////////////////////////////////////////////////////////////
class CFieldIOCP;

class CPreWinSocket;
class CIMWinSocket;
class CArenaFieldWinSocket;
class CPCBangIPManager;
class CFieldGlobal : public CGlobalGameServer  
{
public:
	CFieldGlobal();
	virtual ~CFieldGlobal();

	///////////////////////////////////////////////////////////////////////////
	// Property
	void SetLastTickLogSystem(DWORD i_dwTick);
	DWORD GetLastTickLogSystem(void);
	void SetFieldServerGroupName(char *i_szFieldServerGroupName);
	char *GetFieldServerGroupName(void);
	void SetIPLogServer(char *i_szIP);
	char *GetIPLogServer(void);
	void SetIPIMServer(char *i_szIP);
	char *GetIPIMServer(void);
	char *GetIPVoIP1to1Server(void);
	char *GetIPVoIPNtoNServer(void);

	void SetPortLogServer(int i_nPort);
	int GetPortLogServer(void);
	void SetPortIMServer(int i_nPort);
	int GetPortIMServer(void);
	int GetPortVoIP1to1Server(void);
	int GetPortVoIPNtoNServer(void);

	CPreWinSocket * GetField2PreWinSocket(void);
	CIMWinSocket * GetField2IMWinSocket(void);
	CArenaFieldWinSocket * GetField2ArenaFieldWinSocket(void);				// 2007-12-26 by dhjin, �Ʒ��� ���� - 

	void ChecklRequestInCRTLib(void);

	char *GetMainORTestServerName(void);
	char *GetGamePublisherName(void);
	BOOL GetIsJamboreeServer(void);

	///////////////////////////////////////////////////////////////////////////
	// Method
	BOOL CreateAllF2WSocket(HWND i_hWnd);
	BOOL CreateField2PreWinSocket(HWND i_hWnd);
	BOOL CreateField2IMWinSocket(HWND i_hWnd);
	BOOL CreateField2ArenaFieldWinSocket(HWND i_hWnd);						// 2007-12-26 by dhjin, �Ʒ��� ���� - 
	void DestroyAllF2LWSocket(void);
	void DestroyField2PreWinSocket(void);
	void DestroyField2IMWinSocket(void);
	void DestroyField2ArenaFieldWinSocket(void);									// 2007-12-26 by dhjin, �Ʒ��� ���� - 
	BOOL SendLogFieldServer2LogServer(BYTE *szLogMsg, int nLength);
	BOOL SendLogFieldServer2LogServerORGFile(BYTE *szLogMsg, int nLength);
	BOOL ConnectAllF2LWSocket(char *i_szSvrIP, int i_nSvrPort);
	BOOL ReConnectAllF2LWSocket(char *i_szSvrIP, int i_nSvrPort);
	BOOL IsConnectedAllF2LWSocket(void);
	void OnF2LAsyncEvent(SOCKET i_hSocket, LONG i_nEvent);

	// 2009-04-20 by cmkwon, F2L ���� �ý��� ���� - 
	BOOL OnF2LClosed(CLogWinSocket *i_pF2LWinSoc);

	void SendArenaServerMFSInfo();						// 2008-01-17 by dhjin, �Ʒ��� ���� - �Ʒ��� ������ �ʵ� ���� ���� ����
	// 2008-01-31 by cmkwon, ���� ����/���� ���ɾ�� ������ �ý��� ���� - 
	BOOL Send2PreServer(BYTE *i_pData, int i_nDataLen);
	
	// 2008-09-08 by cmkwon, SCMonitor���� ReloadVersionInfo�ÿ� �Ϻ� üũ������(.\Res-Tex\*.*)�� ���ε��ϱ� - 
	BOOL LoadResObjCheckListW(BOOL i_bReloadOnlyRexTexDirectory=FALSE);

	// 2009-03-05 by cmkwon, �������� �Ʒ��� ���� ó�� - 
	BOOL IsArenaServer(void);

	// virtual Function
	virtual BOOL InitServerSocket(void);				// ���ϰ��� �ʱ�ȭ �Լ�
	virtual BOOL EndServerSocket(void);					// ���ϰ��� ���� �Լ�

	virtual BOOL LoadConfiguration(void);				// Server ������ ���� Configuration Load

	// start 2011-11-03 by shcho, yedang �˴ٿ��� ���� - üũ �Լ� �߰�
	// ���� üũ �Լ�
	BOOL checkSHUTDOWNMINORS(int birthdayYears /* ���� */ , ATUM_DATE_TIME currentTime/* ���� �ð� */);	
	// END 2011-11-03 by shcho, yedang �˴ٿ��� ���� - üũ �Լ� �߰�

	/*BOOL CheckAllowedNPCServerIP(char *i_szIP);*/		// 2013-04-01 by hskim, NPCServer ???? ?? ?? ??

protected:
	//////////////////////////////////////////////////////////////////////////
	// ������ Ÿ�̹� ���� ��� ����
	DWORD				m_dwLastTickLogSystem;			// FieldServer���� ���� ���� ������ LogServer�� �����ϱ� ���� TimerID

	//////////////////////////////////////////////////////////////////////////
	// Configuration Variables
	char				m_szFieldServerGroupName[SIZE_MAX_SERVER_NAME];	// one (Field)
	char				m_szIPLogServer[SIZE_MAX_IPADDRESS];			// one (Field)
	char				m_szIPIMServer[SIZE_MAX_IPADDRESS];				// one (Field)
	char				m_szIPVoIP1to1Server[SIZE_MAX_IPADDRESS];		// one (Field)
	char				m_szIPVoIPNtoNServer[SIZE_MAX_IPADDRESS];		// one (Field)
	int					m_nPortLogServer;								// one (Field)
	int					m_nPortIMServer;								// one (Field)
	int					m_nPortVoIP1to1Server;							// one (Field)
	int					m_nPortVoIPNtoNServer;							// one (Field)

	vectorF2LWSocketPtr	m_vectorF2LWSocketPtr;
	int					m_nSendIndexF2LWSocket;
	CPreWinSocket *		m_pField2PreWinSocket;
	CIMWinSocket *		m_pField2IMWinSocket;
	CArenaFieldWinSocket*	m_pField2ArenaFieldWinSocket;					// 2007-12-26 by dhjin, �Ʒ��� ���� - 

	// 2006-05-30 by cmkwon
	long				*m_plRequestInCRTLib;			

	char				m_szMainORTestServerName[SIZE_MAX_SERVER_NAME];			// 2007-04-09 by cmkwon
	char				m_szGamePublisherName[SIZE_MAX_GAME_PUBLISHER_NAME];	// 2007-04-09 by cmkwon
	BOOL				m_bIsJamboreeServer;									// 2007-04-09 by cmkwon

public:
	BOOL				LoadPCBangIPListFromConfig(void);	// 2006-08-18 by dhjin
	setstring			m_setPCBangIPList;					// 2006-08-18 by dhjin
	
	BOOL				m_bCheckLogServer;
	BOOL				m_bEventActivated;

	BOOL				m_bCashShopServiceFlag;							// 2007-01-10 by cmkwon, 
	BOOL				m_bUseSecondaryPasswordSystemFlag;				// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - CFieldGlobal �� ��� ���� �߰�
	BOOL GetUseSecondaryPasswordSystemFlag(void);						// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - CFieldGlobal �� ��� �Լ� �߰�

	DWORD				m_dwLastWndMsg;
	DWORD				m_dwLastWndMsgTick;
	DWORD				m_dwLastWndMsgWParam;
	DWORD				m_dwLastWndMsgLParam;
	DWORD				m_dwLastSocketMessage;
	DWORD				m_dwLastSocketMessageParam1;
	DWORD				m_dwLastSocketMessageParam2;

	CPCBangIPManager	*m_pPCBangIPManager;

	// 2007-12-26 by dhjin, �Ʒ��� ���� - �Ʒ��� ���� ����
	SARENA_SERVER_INFO	m_sArenaServerInfo;	

	///////////////////////////////////////////////////////////////////////////////
	// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
	SDBSERVER_GROUP		m_DBServerGroup;
	void SetDBServerGroup(SDBSERVER_GROUP *i_pDBServGroup);

	///////////////////////////////////////////////////////////////////////////////
	// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
	char				m_szBillingDBServerIP[SIZE_MAX_ODBC_CONN_STRING];
	int					m_nBillingDBServerPort;
	char				m_szBillingDBServerDatabaseName[SIZE_MAX_ODBC_CONN_STRING];
	char				m_szBillingDBServerUserID[SIZE_MAX_ODBC_CONN_STRING];
	char				m_szBillingDBServerPassword[SIZE_MAX_ODBC_CONN_STRING];
	char *GetBillingDBServerIP(void);
	int GetBillingDBServerPort(void);
	char *GetBillingDBServerDatabaseName(void);
	char *GetBillingDBServerUserID(void);
	char *GetBillingDBServerPassword(void);

	///////////////////////////////////////////////////////////////////////////////
	// 2009-06-03 by cmkwon, ���� ���ý� ���� �ý��� ��� ���� �÷��� �߰� - 
	BOOL				m_bUseInflSelectionRestrictSystem;
	BOOL GetUseInflSelectionRestrictSystem(void);
	void SetUseInflSelectionRestrictSystem(BOOL i_bFlag);

};
#endif // !defined(AFX_FIELDGLOBAL_H__B6793946_A3E2_4778_A6DA_1EE835B77558__INCLUDED_)