// FieldGlobal.cpp: implementation of the CFieldGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FieldGlobal.h"
#include "LogWinSocket.h"
#include "PreWinSocket.h"
#include "IMWinSocket.h"
#include "ArenaFieldWinSocket.h"		// 2007-12-26 by dhjin, �Ʒ��� ���� - 
#include "FieldIOCP.h"
#include "Config.h"
#include "PCBangIPManager.h"

CFieldGlobal *			g_pFieldGlobal = NULL;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFieldGlobal::CFieldGlobal()
{
	if(g_pFieldGlobal)
	{
		return;
	}
	g_pFieldGlobal				= this;

	m_dwLastTickLogSystem		= 0;
	memset(m_szFieldServerGroupName, 0x00, SIZE_MAX_SERVER_NAME);
	memset(m_szIPLogServer, 0x00, SIZE_MAX_IPADDRESS);
	memset(m_szIPIMServer, 0x00, SIZE_MAX_IPADDRESS);
	memset(m_szIPVoIP1to1Server, 0x00, SIZE_MAX_IPADDRESS);
	m_nPortLogServer			= 0;
	m_nPortIMServer				= 0;
	m_nPortVoIP1to1Server		= 0;

	m_vectorF2LWSocketPtr.reserve(SIZE_FIELD2LOG_WINSOCKET);
	m_nSendIndexF2LWSocket		= 0;
	m_pField2PreWinSocket		= NULL;
	m_pField2IMWinSocket		= NULL;
	m_pField2ArenaFieldWinSocket = NULL;					// 2007-12-26 by dhjin, �Ʒ��� ���� - 

	m_bEventActivated			= FALSE;

	m_plRequestInCRTLib			= NULL;		// 2006-05-30 by cmkwon
	m_plRequestInCRTLib			= (long*)0x10261538;		// 2006-05-30 by cmkwon

	m_bCashShopServiceFlag		= FALSE;	// 2007-01-10 by cmkwon
	m_bUseSecondaryPasswordSystemFlag	= FALSE;	// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - �ʱ�ȭ

	MEMSET_ZERO(m_szMainORTestServerName, SIZE_MAX_SERVER_NAME);		// 2007-04-09 by cmkwon
	MEMSET_ZERO(m_szGamePublisherName, SIZE_MAX_GAME_PUBLISHER_NAME);	// 2007-04-09 by cmkwon
	m_bIsJamboreeServer			= FALSE;	// 2007-04-09 by cmkwon

	strcpy(m_szMainORTestServerName, "Main");
	strcpy(m_szGamePublisherName, "Masangsoft");

	m_pPCBangIPManager			= NULL;
	MEMSET_ZERO(&m_sArenaServerInfo, sizeof(SARENA_SERVER_INFO));		// 2008-01-17 by dhjin, �Ʒ��� ���� -  


	///////////////////////////////////////////////////////////////////////////////
	// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 	
	MEMSET_ZERO(m_szBillingDBServerIP, SIZE_MAX_ODBC_CONN_STRING);
	m_nBillingDBServerPort		= 0;
	MEMSET_ZERO(m_szBillingDBServerDatabaseName, SIZE_MAX_ODBC_CONN_STRING);
	MEMSET_ZERO(m_szBillingDBServerUserID, SIZE_MAX_ODBC_CONN_STRING);
	MEMSET_ZERO(m_szBillingDBServerPassword, SIZE_MAX_ODBC_CONN_STRING);

	///////////////////////////////////////////////////////////////////////////////
	// 2009-06-03 by cmkwon, ���� ���ý� ���� �ý��� ��� ���� �÷��� �߰� - �ʱ�ȭ
	m_bUseInflSelectionRestrictSystem	= FALSE;
}

CFieldGlobal::~CFieldGlobal()
{
	EndServerSocket();
	this->DestroyField2PreWinSocket();
	this->DestroyField2IMWinSocket();
	this->DestroyAllF2LWSocket();

	g_pGlobalGameServer = NULL;
	SAFE_DELETE(m_pPCBangIPManager);
}


//////////////////////////////////////////////////////////////////////
// Property
//////////////////////////////////////////////////////////////////////
void CFieldGlobal::SetLastTickLogSystem(DWORD i_dwTick)
{
	m_dwLastTickLogSystem  = i_dwTick;
}

DWORD CFieldGlobal::GetLastTickLogSystem(void)
{
	return m_dwLastTickLogSystem;
}

void CFieldGlobal::SetFieldServerGroupName(char *i_szFieldServerGroupName)
{
	STRNCPY_MEMSET(m_szFieldServerGroupName, i_szFieldServerGroupName, SIZE_MAX_SERVER_NAME);
}

char *CFieldGlobal::GetFieldServerGroupName(void)
{
	return m_szFieldServerGroupName;
}

void CFieldGlobal::SetIPLogServer(char *i_szIP)
{
	memcpy(m_szIPLogServer, i_szIP, SIZE_MAX_IPADDRESS);
}

char *CFieldGlobal::GetIPLogServer(void)
{
	return m_szIPLogServer;
}

void CFieldGlobal::SetIPIMServer(char *i_szIP)
{
	memcpy(m_szIPIMServer, i_szIP, SIZE_MAX_IPADDRESS);
}

char *CFieldGlobal::GetIPIMServer(void)
{
	return m_szIPIMServer;
}

char *CFieldGlobal::GetIPVoIP1to1Server(void)
{
	return m_szIPVoIP1to1Server;
}

char *CFieldGlobal::GetIPVoIPNtoNServer(void)
{
	return m_szIPVoIPNtoNServer;
}


void CFieldGlobal::SetPortLogServer(int i_nPort)
{
	m_nPortLogServer = i_nPort;
}

int CFieldGlobal::GetPortLogServer(void)
{
	return m_nPortLogServer;
}

void CFieldGlobal::SetPortIMServer(int i_nPort)
{
	m_nPortIMServer = i_nPort;
}

int CFieldGlobal::GetPortIMServer(void)
{
	return m_nPortIMServer;
}

int CFieldGlobal::GetPortVoIP1to1Server(void)
{
	return m_nPortVoIP1to1Server;
}

int CFieldGlobal::GetPortVoIPNtoNServer(void)
{
	return m_nPortVoIPNtoNServer;
}

CPreWinSocket * CFieldGlobal::GetField2PreWinSocket(void)
{
	return m_pField2PreWinSocket;
}

CIMWinSocket * CFieldGlobal::GetField2IMWinSocket(void)
{
	return m_pField2IMWinSocket;
}

CArenaFieldWinSocket * CFieldGlobal::GetField2ArenaFieldWinSocket(void)
{
	return m_pField2ArenaFieldWinSocket;					// 2007-12-26 by dhjin, �Ʒ��� ���� - ;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldGlobal::ChecklRequestInCRTLib(void)
/// \brief		
/// \author		cmkwon
/// \date		2006-05-30 ~ 2006-05-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldGlobal::ChecklRequestInCRTLib(void)
{
#ifdef _DEBUG
	if(NULL != m_plRequestInCRTLib
		&& 0 > (*m_plRequestInCRTLib))
	{// 2006-05-30 by cmkwon, CRTLib�� debug ����϶� 
		*m_plRequestInCRTLib	= 1;		// 2006-05-30 by cmkwon
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CFieldGlobal::GetMainORTestServerName(void)
/// \brief		
/// \author		cmkwon
/// \date		2007-04-09 ~ 2007-04-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CFieldGlobal::GetMainORTestServerName(void)
{
	return m_szMainORTestServerName;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CFieldGlobal::GetGamePublisherName(void)
/// \brief		
/// \author		cmkwon
/// \date		2007-04-09 ~ 2007-04-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CFieldGlobal::GetGamePublisherName(void)
{
	return m_szGamePublisherName;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
/// \author		cmkwon
/// \date		2007-04-09 ~ 2007-04-09
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::GetIsJamboreeServer(void)
{
	return m_bIsJamboreeServer;
}


///////////////////////////////////////////////////////////////////////////
// Method
///////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::CreateAllF2WSocket(HWND i_hWnd)
{
	if( false == m_vectorF2LWSocketPtr.empty() )
	{
		return FALSE;
	}

	if( NULL == m_hMainWndHandle )
	{
		m_hMainWndHandle = i_hWnd;
	}


	for( int i = 0; i < SIZE_FIELD2LOG_WINSOCKET; i++ )
	{
		CLogWinSocket *pF2LWSocket = new CLogWinSocket( m_hMainWndHandle , WM_LOG_ASYNC_EVENT , WM_LOG_PACKET_NOTIFY );
		m_vectorF2LWSocketPtr.push_back( pF2LWSocket );
		if ( m_vectorF2LWSocketPtr.size() >= SIZE_FIELD2LOG_WINSOCKET )
		{
			break;
		}
	}
	 
	return TRUE;
}

BOOL CFieldGlobal::CreateField2PreWinSocket(HWND i_hWnd)
{
	if(m_pField2PreWinSocket){		return FALSE;}
	if(NULL == m_hMainWndHandle)
	{
		m_hMainWndHandle = i_hWnd;
	}

	m_pField2PreWinSocket = new CPreWinSocket(m_hMainWndHandle, WM_PRE_ASYNC_EVENT, WM_PRE_PACKET_NOTIFY);
	return TRUE;
}

BOOL CFieldGlobal::CreateField2IMWinSocket(HWND i_hWnd)
{
	if(m_pField2IMWinSocket){		return FALSE;}
	if(NULL == m_hMainWndHandle)
	{
		m_hMainWndHandle = i_hWnd;
	}

	m_pField2IMWinSocket = new CIMWinSocket(m_hMainWndHandle, WM_IM_ASYNC_EVENT, WM_IM_PACKET_NOTIFY);
	return TRUE;
}

BOOL CFieldGlobal::CreateField2ArenaFieldWinSocket(HWND i_hWnd)
{// 2007-12-26 by dhjin, �Ʒ��� ���� - 
	if(m_pField2ArenaFieldWinSocket){		return FALSE;}
	if(NULL == m_hMainWndHandle)
	{
		m_hMainWndHandle = i_hWnd;
	}

	m_pField2ArenaFieldWinSocket = new CArenaFieldWinSocket(m_hMainWndHandle, WM_FIELD_ASYNC_EVENT, WM_FIELD_PACKET_NOTIFY);
	return TRUE;
}

void CFieldGlobal::DestroyAllF2LWSocket(void)
{
	// 2009-04-20 by cmkwon, �ý��� �α� �߰� - 
	this->WriteSystemLogEX(TRUE, "  [Notify] CFieldGlobal::DestroyAllF2LWSocket# \r\n");

	int nSize = m_vectorF2LWSocketPtr.size();
	for(int i=0; i < nSize; i++)
	{
		if(m_vectorF2LWSocketPtr[i]
			&& INVALID_SOCKET != m_vectorF2LWSocketPtr[i]->GetSocketHandle())
		{
			m_vectorF2LWSocketPtr[i]->CloseSocket();
		}
	}
	for_each(m_vectorF2LWSocketPtr.begin(), m_vectorF2LWSocketPtr.end(), Delete_Object());
	m_vectorF2LWSocketPtr.clear();
}

void CFieldGlobal::DestroyField2PreWinSocket(void)
{
	// 2009-03-19 by cmkwon, �ý��� �α� �߰� - FieldServer 
	this->WriteSystemLogEX(TRUE, "  [Notify] CFieldGlobal::DestroyField2PreWinSocket# 0x%X IsConnected(%d) \r\n", m_pField2ArenaFieldWinSocket, (m_pField2ArenaFieldWinSocket)?m_pField2ArenaFieldWinSocket->IsConnected():FALSE);

	if(m_pField2PreWinSocket && m_pField2PreWinSocket->IsConnected())
	{
		m_pField2PreWinSocket->CloseSocket();
	}
	SAFE_DELETE(m_pField2PreWinSocket);
}

void CFieldGlobal::DestroyField2IMWinSocket(void)
{
	// 2009-03-19 by cmkwon, �ý��� �α� �߰� - FieldServer 
	this->WriteSystemLogEX(TRUE, "  [Notify] CFieldGlobal::DestroyField2IMWinSocket# 0x%X IsConnected(%d) \r\n", m_pField2IMWinSocket, (m_pField2IMWinSocket)?m_pField2IMWinSocket->IsConnected():FALSE);

	if(m_pField2IMWinSocket && m_pField2IMWinSocket->IsConnected())
	{
		m_pField2IMWinSocket->CloseSocket();
	}
	SAFE_DELETE(m_pField2IMWinSocket);
}

void CFieldGlobal::DestroyField2ArenaFieldWinSocket(void)
{// 2007-12-26 by dhjin, �Ʒ��� ���� - 
	// 2009-03-19 by cmkwon, �ý��� �α� �߰� - FieldServer 
	this->WriteSystemLogEX(TRUE, "  [Notify] CFieldGlobal::DestroyField2ArenaFieldWinSocket# 0x%X IsConnected(%d) \r\n", m_pField2ArenaFieldWinSocket, (m_pField2ArenaFieldWinSocket)?m_pField2ArenaFieldWinSocket->IsConnected():FALSE);

	if(m_pField2ArenaFieldWinSocket && m_pField2ArenaFieldWinSocket->IsConnected())
	{
		m_pField2ArenaFieldWinSocket->CloseSocket();
	}
	SAFE_DELETE(m_pField2ArenaFieldWinSocket);
}

///////////////////////////////////////////////////////////////////////////
// virtual Function
///////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::InitServerSocket(void)
{
	if(FALSE == IsArenaServer())
	{// 2007-12-26 by dhjin, �Ʒ��� ���� - �Ʒ��� ������ �ƴϸ� ����
		if(NULL == m_pField2PreWinSocket || m_pField2PreWinSocket->IsConnected() == FALSE
			|| NULL == m_pField2IMWinSocket || m_pField2IMWinSocket->IsConnected() == FALSE
			|| NULL == m_pField2ArenaFieldWinSocket)
		{
			return FALSE;
		}
	}
	else
	{
		if(NULL == m_pField2PreWinSocket || m_pField2PreWinSocket->IsConnected() == FALSE
			|| NULL == m_pField2IMWinSocket || m_pField2IMWinSocket->IsConnected() == FALSE)
		{
			return FALSE;
		}
	}
		
	// check log server�� TRUE�̸� log server ���̴� ���� ���� �� ��
	if (m_bCheckLogServer
		&& FALSE == this->IsConnectedAllF2LWSocket())
	{
		return FALSE;
	}

	MessageType_t msgType = T_FL_LOG_START_FIELD_SERVER;
	this->SendLogFieldServer2LogServer((BYTE*)&msgType, sizeof(msgType));

	if (NULL != m_pGIOCP)
	{
		return FALSE;
	}

	// 2009-03-19 by cmkwon, �ý��� �α� �߰� - 
	this->WriteSystemLogEX(TRUE, "  [Notify] CFieldGlobal::InitServerSocket# Starting... \r\n");

	m_dwLastTickLogSystem = GetTickCount() - (TIMERGAP_LOGSYSTEM - 60000);			// FieldServer�� �����ϰ� 1���Ŀ� �ѹ� ���������� �α� ������ �����. ���� ���ʹ� 5�а��� �ѹ��� �α׸� �����

	//////////////////////////////////////////////////////////////////////////
	// 2007-08-07 by dhjin, CPCBangIPManager ����
	m_pPCBangIPManager = new CPCBangIPManager;	

	m_pGIOCP = new CFieldIOCP(m_nPortListening, m_szIPLocal);
	((CFieldIOCP*)m_pGIOCP)->m_pPreWinSocket = m_pField2PreWinSocket;
	((CFieldIOCP*)m_pGIOCP)->m_pIMWinSocket = m_pField2IMWinSocket;
	if(FALSE == IsArenaServer())
	{// 2007-12-26 by dhjin, �Ʒ��� ���� - �Ʒ��� ������ �ƴϸ� ����
		((CFieldIOCP*)m_pGIOCP)->m_pArenaFieldWinSocket = m_pField2ArenaFieldWinSocket;
	}
	if(m_pGIOCP->IOCPInit() == FALSE)
	{
		char	szSystemLog[256];
		sprintf(szSystemLog, "[Error] FieldServer IOCPInit Error\r\n");
		this->WriteSystemLog(szSystemLog);
		DBGOUT(szSystemLog);
		MessageBox(NULL, szSystemLog, "ERROR", MB_OK);
		return FALSE;
	}
	//-- CMKWON 2003-06-12 NPC Server�� ���� T_FN_NPCSERVER_START�� �ް� ó���ϵ��� ����
	//m_pGIOCP->OpenUDPPortForOtherServer();

	m_pField2PreWinSocket->SetFieldIOCP(((CFieldIOCP*)m_pGIOCP));
	m_pField2IMWinSocket->SetFieldIOCP(((CFieldIOCP*)m_pGIOCP));
	if(m_pField2ArenaFieldWinSocket)
	{
		m_pField2ArenaFieldWinSocket->SetFieldIOCP(((CFieldIOCP*)m_pGIOCP));	// 2009-04-17 by cmkwon, ����Arena ���� ���� ���� - ���⿡�� �����ؾ� ��.
	}

	///////////////////////////////////////////////////////////////////////////
	// PRE server�� Connect �� Map ���� ���� - by kelovon
	INIT_MSG_WITH_BUFFER(MSG_FP_CONNECT_FIELD_CONNECT, T_FP_CONNECT_FIELD_CONNECT, msgConnect, SendBuf);
	STRNCPY_MEMSET(msgConnect->FieldServerGroupName, this->GetFieldServerGroupName(), SIZE_MAX_SERVER_NAME);
// 2006-05-23 by cmkwon, �Ʒ��� ���� ������
//	msgConnect->FieldServerID.SetValue(m_pGIOCP->GetLocalIPAddress(), m_pGIOCP->GetListenerPort());
	msgConnect->FieldServerID.SetValue(g_pFieldGlobal->GetPublicIPLocal(), m_pGIOCP->GetListenerPort());
	msgConnect->NumOfMapIndex = ((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject.size();	// ���Ŀ� ���񽺵Ǵ� map ���� �Ҵ�
	msgConnect->ArenaFieldServerCheck = m_sArenaServerInfo.ArenaFieldServerCheck;		// 2007-12-26 by dhjin, �Ʒ��� ���� - TRUE => �Ʒ��� �ʵ� ����
	msgConnect->DBServerGroup			= this->m_DBServerGroup;		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - CFieldIOCP::IOCPInit() ���� ������

	int offset = 0;
	int NumOfMapServiced = 0;
	for (int i = 0; i < msgConnect->NumOfMapIndex; i++)
	{
		SERVER_ID tmpID;
		tmpID.SetValue(((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject[i]->m_strFieldIP
					, ((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject[i]->m_sFieldListenPort);
		if (tmpID == ((CFieldIOCP*)m_pGIOCP)->m_FieldServerID)
		{
			*(USHORT*)((char*)SendBuf + MSG_SIZE(MSG_FP_CONNECT_FIELD_CONNECT) + offset)
				= ((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject[i]->m_nMapIndex;
			offset += sizeof(USHORT);
			NumOfMapServiced++;
		}
	}
	msgConnect->NumOfMapIndex = NumOfMapServiced;
	m_pField2PreWinSocket->Write((char*)SendBuf, MSG_SIZE(MSG_FP_CONNECT_FIELD_CONNECT) + offset);

	// 2007-12-17 by cmkwon, �ý��� �α� �߰�
	this->WriteSystemLogEX(TRUE, "[Notify] CFieldGlobal::InitServerSocket_ send to PreServer !!, Service map counts(%3d), Send Bytes(%d)\r\n", NumOfMapServiced, MSG_SIZE(MSG_FP_CONNECT_FIELD_CONNECT) + offset);

	///////////////////////////////////////////////////////////////////////////
	// IM server�� Connect �� Map ���� ���� - by kelovon
	offset = 0;

	*(MessageType_t*)SendBuf = T_FI_CONNECT;
	offset += SIZE_FIELD_TYPE_HEADER;

	MSG_FI_CONNECT *pMsgConn = (MSG_FI_CONNECT*)(SendBuf + offset);
	pMsgConn->NumOfMapIndex = ((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject.size();	// ���Ŀ� ���񽺵Ǵ� map ���� �Ҵ�
	pMsgConn->FieldServerID = ((CFieldIOCP*)m_pGIOCP)->m_FieldServerID;
	if(IsArenaServer())
	{// 2008-02-28 by dhjin, �Ʒ��� ���� - �Ʒ��� �����̸� IM������ �Ʒ��� ���� bit�� üũ�Ͽ� ������.
		pMsgConn->ArenaServerCheck = TRUE;
	}
	else
	{
		pMsgConn->ArenaServerCheck = FALSE;
	}
	offset += sizeof(MSG_FI_CONNECT);

	NumOfMapServiced = 0;
	for (int i = 0; i < pMsgConn->NumOfMapIndex; i++)
	{
		SERVER_ID tmpID;
		tmpID.SetValue(((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject[i]->m_strFieldIP
					, ((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject[i]->m_sFieldListenPort);
		if (tmpID == ((CFieldIOCP*)m_pGIOCP)->m_FieldServerID)
		{
			*(USHORT*)((char*)SendBuf + offset)
				= ((CFieldIOCP*)m_pGIOCP)->GetMapWorkspace()->m_vectorPtrMapProject[i]->m_nMapIndex;
			offset += sizeof(USHORT);
			NumOfMapServiced++;
		}
	}
	pMsgConn->NumOfMapIndex = NumOfMapServiced;

	m_pField2IMWinSocket->Write((char*)SendBuf, offset);
	// 2007-12-17 by cmkwon, �ý��� �α� �߰�
	this->WriteSystemLogEX(TRUE, "[Notify] CFieldGlobal::InitServerSocket_ send to IMServer !!, Service map counts(%3d), Send Bytes(%d)\r\n", NumOfMapServiced, offset);

	CGlobalGameServer::InitServerSocket();

	// 2009-03-19 by cmkwon, �ý��� �α� �߰� - 
	this->WriteSystemLogEX(TRUE, "  [Notify] CFieldGlobal::InitServerSocket# Started \r\n");

	return TRUE;
}

BOOL CFieldGlobal::EndServerSocket(void)
{
	// 2009-03-19 by cmkwon, �ý��� �α� �߰� - �Ʒ��� ���� ����
	//this->WriteSystemLogEX(TRUE, "[Notify] CFieldGlobal::EndServerSocket\r\n");	// 2007-12-17 by cmkwon, �ý��� �α� �߰�
	this->WriteSystemLogEX(TRUE, "  [Notify] CFieldGlobal::EndServerSocket# \r\n");

	CGlobalGameServer::EndServerSocket();

	return TRUE;
}

BOOL CFieldGlobal::LoadConfiguration(void)
{
	LoadAbuseAndProhibitedName();
// 2007-01-22 by dhjin, PC�� ����Ʈ �ǽð����� ����
//	LoadPCBangIPListFromConfig();// 2006-08-18 by dhjin, pc�� ����Ʈ .cfg���� �б�.

	///////////////////////////////////////////////////////////////////////////////
	// 2007-05-07 by cmkwon, ĳ���͸� ������ ��밡���� ���� ����Ʈ�� �ε��Ѵ�.
	// 2007-05-07 by cmkwon, ���ڸ���Ʈ����(AllLetterList.cfg)�� ������ üũ �� �ʿ� ����
	CAtumSJ::LoadAllLetterList((string(CONFIG_ROOT)+string("./AllLetterList.cfg")).c_str());

	const int SIZE_BUFF = 512;
	char		buff[SIZE_BUFF];
	char		buffBackup[SIZE_BUFF];		// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
	const char	*token;
	char		seps[] = " \t";
	ifstream	fin;
	CConfig		config;

	if (!config.LoadUserDefinedVariables(GLOBAL_CONFIG_FILE_PATH))
	{
		char	szError[1024];
		sprintf(szError, "[Error] LoadConfiguration LoadUserDefinedVariables_1() error, FileName[%s]\r\n"
			, GLOBAL_CONFIG_FILE_PATH);
		this->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	if (!config.LoadUserDefinedVariables( FIELD_SERVER_CONFIG_FILE_PATH))
	{
		char	szError[1024];
		sprintf(szError, "[Error] LoadConfiguration LoadUserDefinedVariables_2() error, FileName[%s]\r\n"
			, FIELD_SERVER_CONFIG_FILE_PATH);
		this->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	fin.open(FIELD_SERVER_CONFIG_FILE_PATH);
	if (!fin.is_open())
	{	// cannot open file...

		int nErr = GetLastError();
		SetLastError(0);
		char	szError[1024];
		sprintf(szError, "[Error] LoadConfiguration open() error, LastError[%d] ConfigFileName[%s]\r\n"
			, nErr, FIELD_SERVER_CONFIG_FILE_PATH);
		this->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	while(TRUE)
	{
		memset(buff, 0x00, SIZE_BUFF);
		BOOL bFlagFileEnd = fin.getline(buff, SIZE_BUFF).eof();
		if(bFlagFileEnd == TRUE
			&& strcmp(buff, "") == 0)
		{
			break;
		}

		STRNCPY_MEMSET(buffBackup, buff, SIZE_BUFF);	// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 

		token = strtok(buff, seps);

		if (token == NULL
			|| strncmp(token, "#", 1) == 0
			|| strncmp(token, "$", 1) == 0)
		{	// ignore blank lines
			// ignore comments
			// ignore user defined variables

			continue;
		}

		if(stricmp(token, "LocalIPAddress") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") == 0)
			{
				this->SetIPLocal("127.0.0.1");
			}
			else
			{
				this->SetIPLocal((char*)token);
			}
		}
		else if(stricmp(token, "LocalPublicIPAddress") == 0)
		{// 2006-05-23 by cmkwon,
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			this->SetPublicIPLocal((char*)token);
		}
		else if(stricmp(token, "LocalListenPort") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetPortListening(atoi(token));
			}
		}
		else if(stricmp(token, "LanguageType") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			this->m_nLanguageType = atoi(token);
			if(FALSE == IS_VALID_LANGUAGE_TYPE(this->m_nLanguageType))
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
		}
		else if(stricmp(token, "ODBCDSN") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed. ODBCDSN\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				STRNCPY_MEMSET((char*)m_szODBCDSN, token, SIZE_MAX_ODBC_CONN_STRING);
			}
		}
		else if(stricmp(token, "ODBCUID") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed. ODBCUID\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				STRNCPY_MEMSET((char*)m_szODBCUID, token, SIZE_MAX_ODBC_CONN_STRING);
				///////////////////////////////////////////////////////////////////////////////
				// 2008-09-01 by cmkwon, global.cfg ���Ͽ� DB ID/PWD ��ȣȭ - 
				BYTE byEncodedBinary[1024];
				MEMSET_ZERO(byEncodedBinary, 1024);
				if(XOR::XORString2Binary(byEncodedBinary, (char*)token))
				{
					MEMSET_ZERO(m_szODBCUID, SIZE_MAX_ODBC_CONN_STRING);
					XOR::XOREncode((BYTE*)m_szODBCUID, byEncodedBinary, strlen(token)/2, STR_XOR_KEY_STRING_DB_ID_PWD);
				}
			}
		}
		else if(stricmp(token, "ODBCPASSWD") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed. ODBCPASSWD\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				STRNCPY_MEMSET((char*)m_szODBCPASSWORD, token, SIZE_MAX_ODBC_CONN_STRING);
				///////////////////////////////////////////////////////////////////////////////
				// 2008-09-01 by cmkwon, global.cfg ���Ͽ� DB ID/PWD ��ȣȭ - 
				BYTE byEncodedBinary[1024];
				MEMSET_ZERO(byEncodedBinary, 1024);
				if(XOR::XORString2Binary(byEncodedBinary, (char*)token))
				{
					MEMSET_ZERO(m_szODBCPASSWORD, SIZE_MAX_ODBC_CONN_STRING);
					XOR::XOREncode((BYTE*)m_szODBCPASSWORD, byEncodedBinary, strlen(token)/2, STR_XOR_KEY_STRING_DB_ID_PWD);
				}
			}
		}
		else if(stricmp(token, "LOGDB_ODBCDSN") == 0)
		{// 2007-12-03 by cmkwon, ���� �α� DB ���� ���� �ϱ� ���� ���� - LOGDB_ODBCDSN ��������
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed. ODBCDSN\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				// 2007-12-03 by cmkwon, ���� �α� DB ���� ���� �ϱ� ���� ���� - m_szLogDBODBCDSN �����ϱ�
				STRNCPY_MEMSET((char*)m_szLogDBODBCDSN, token, SIZE_MAX_ODBC_CONN_STRING);
			}
		}
		else if(stricmp(token, "LOGDB_ODBCUID") == 0)
		{// 2007-12-03 by cmkwon, ���� �α� DB ���� ���� �ϱ� ���� ���� - LOGDB_ODBCUID ��������
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed. ODBCUID\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				// 2007-12-03 by cmkwon, ���� �α� DB ���� ���� �ϱ� ���� ���� - m_szLogDBODBCUID �����ϱ�
				STRNCPY_MEMSET((char*)m_szLogDBODBCUID, token, SIZE_MAX_ODBC_CONN_STRING);
				///////////////////////////////////////////////////////////////////////////////
				// 2008-09-01 by cmkwon, global.cfg ���Ͽ� DB ID/PWD ��ȣȭ - 
				BYTE byEncodedBinary[1024];
				MEMSET_ZERO(byEncodedBinary, 1024);
				if(XOR::XORString2Binary(byEncodedBinary, (char*)token))
				{
					MEMSET_ZERO(m_szLogDBODBCUID, SIZE_MAX_ODBC_CONN_STRING);
					XOR::XOREncode((BYTE*)m_szLogDBODBCUID, byEncodedBinary, strlen(token)/2, STR_XOR_KEY_STRING_DB_ID_PWD);
				}
			}
		}
		else if(stricmp(token, "LOGDB_ODBCPASSWD") == 0)
		{// 2007-12-03 by cmkwon, ���� �α� DB ���� ���� �ϱ� ���� ���� - LOGDB_ODBCPASSWD ��������
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed. ODBCPASSWD\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				// 2007-12-03 by cmkwon, ���� �α� DB ���� ���� �ϱ� ���� ���� - m_szLogDBODBCPASSWORD �����ϱ�
				STRNCPY_MEMSET((char*)m_szLogDBODBCPASSWORD, token, SIZE_MAX_ODBC_CONN_STRING);
				///////////////////////////////////////////////////////////////////////////////
				// 2008-09-01 by cmkwon, global.cfg ���Ͽ� DB ID/PWD ��ȣȭ - 
				BYTE byEncodedBinary[1024];
				MEMSET_ZERO(byEncodedBinary, 1024);
				if(XOR::XORString2Binary(byEncodedBinary, (char*)token))
				{
					MEMSET_ZERO(m_szLogDBODBCPASSWORD, SIZE_MAX_ODBC_CONN_STRING);
					XOR::XOREncode((BYTE*)m_szLogDBODBCPASSWORD, byEncodedBinary, strlen(token)/2, STR_XOR_KEY_STRING_DB_ID_PWD);
				}
			}
		}
		else if(stricmp(token, "FieldServerGroupName") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetFieldServerGroupName((char*)token);
			}
		}
		else if(stricmp(token, "PreServer") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetIPPreServer((char*)token);
			}
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetPortPreServer(atoi(token));
			}
		}
		else if(stricmp(token, "IMServer") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetIPIMServer((char*)token);
			}
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetPortIMServer(atoi(token));
			}
		}
		else if(stricmp(token, "LogServer") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetIPLogServer((char*)token);
			}
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			if(strcmp(token, "") != 0)
			{
				this->SetPortLogServer(atoi(token));
			}
		}
		else if(stricmp(token, "VoIP1to1Server") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			STRNCPY_MEMSET(m_szIPVoIP1to1Server, token, SIZE_MAX_IPADDRESS);

			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			m_nPortVoIP1to1Server = atoi(token);
		}
		else if(stricmp(token, "VoIPNtoNServer") == 0)
		{
			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			STRNCPY_MEMSET(m_szIPVoIPNtoNServer, token, SIZE_MAX_IPADDRESS);

			token = config.strtok(NULL, seps);
			if (token == NULL)
			{
				char *msg = "Loading Configuration File Failed.\n";
				DBGOUT(msg);
				MessageBox(NULL, msg, "Error", MB_OK);
				return FALSE;
			}
			m_nPortVoIPNtoNServer = atoi(token);
		}
		else if (stricmp(token, "CheckLogServer") == 0)
		{
			token = config.strtok(NULL, seps);

			if (token == NULL || (stricmp(token, "TRUE") != 0 && stricmp(token, "FALSE") != 0))
			{
				char	szSystemLog[256];
				sprintf(szSystemLog, "Loading Configuration File Failed: CheckLogServer\r\n");
				this->WriteSystemLog(szSystemLog);
				DBGOUT(szSystemLog);
				return FALSE;
			}

			if (stricmp(token, "TRUE") == 0)
			{
				m_bCheckLogServer = TRUE;
			}
			else if (stricmp(token, "FALSE") == 0)
			{
				m_bCheckLogServer = FALSE;
			}
			else
			{
				// unreachable
				return FALSE;
			}
		}
		else if(stricmp(token, "ServerGroupName") == 0)
		{
			token = config.strtok(NULL, seps);
			if(strcmp(token, "") != 0)
			{
				this->SetServerGroupName((char*)token);
			}
		}
// 2008-09-24 by cmkwon, global.cfg ���� ���� - ServerGroupInfo �� ���� ��.
// 		else if(stricmp(token, "ServerGroup") == 0)
// 		{
// 			token = config.strtok(NULL, seps);
// 			if (token == NULL)
// 			{
// 				char	szSystemLog[256];
// 				sprintf(szSystemLog, "[Error] CPreIOCP::LoadAllServers Config Initialization Error2: ServerGroup\r\n");
// 				WriteSystemLog(szSystemLog);
// 				DBGOUT(szSystemLog);
// 				return FALSE;
// 			}
// 
// 			char szGroupName[SIZE_MAX_SERVER_NAME];
// 			STRNCPY_MEMSET(szGroupName, token, SIZE_MAX_SERVER_NAME);
// 
// 			BOOL nServerIDforMGame = 10061;
// 			token = config.strtok(NULL, seps);
// 			if(token)
// 			{
// 				nServerIDforMGame = atoi(token);
// 			}
// 
// 			if (FALSE == InsertServerGroupforMGame(szGroupName, nServerIDforMGame))
// 			{				
// 				DBGOUT("[ERROR] Already ServerGroupName : %20s, ServerID(%5d)\n", szGroupName, nServerIDforMGame);
// 			}
// 		}
		else if(0 == stricmp(token, "IsTestServer"))
		{
			token = config.strtok(NULL, seps);
			if(token == NULL)
			{
				m_bIsTestServer = FALSE;
			}
			else
			{
				if (stricmp(token, "FALSE") == 0)
				{
					m_bIsTestServer = FALSE;
				}
				else
				{
					m_bIsTestServer = TRUE;
				}
			}
		}
		else if(0 == stricmp(token, "MainORTestServerName"))		// 2007-04-09 by cmkwon
		{
			token = config.strtok(NULL, seps);
			if(token)
			{
				STRNCPY_MEMSET(m_szMainORTestServerName, token, SIZE_MAX_SERVER_NAME);
			}
		}
		else if(0 == stricmp(token, "GamePublisher"))				// 2007-04-09 by cmkwon
		{
			token = config.strtok(NULL, seps);
			if(token)
			{
				STRNCPY_MEMSET(m_szGamePublisherName, token, SIZE_MAX_GAME_PUBLISHER_NAME);
			}
		}
		else if(0 == stricmp(token, "IsJamboreeServer"))				// 2007-04-09 by cmkwon
		{
			token = config.strtok(NULL, seps);
			if(token == NULL)
			{
				m_bIsJamboreeServer = FALSE;
			}
			else
			{
				if (stricmp(token, "FALSE") == 0)
				{
					m_bIsJamboreeServer = FALSE;
				}
				else
				{
					m_bIsJamboreeServer = TRUE;
				}
			}
		}
		else if(0 == stricmp(token, "CashShopServiceFlag"))
		{// 2007-01-10 by cmkwon
			
			token = config.strtok(NULL, seps);
			if(token == NULL)
			{
				m_bCashShopServiceFlag = FALSE;
			}
			else
			{
				if (0 == stricmp(token, "TRUE"))
				{
					m_bCashShopServiceFlag = TRUE;
				}
				else
				{
					m_bCashShopServiceFlag = FALSE;
				}
			}
		}
		else if(0 == stricmp(token, "UseSecondaryPasswrodSystemFlag"))
		{// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - field.cfg ���� �߰�
			
			token = config.strtok(NULL, seps);
			if(token == NULL)
			{
				m_bUseSecondaryPasswordSystemFlag = FALSE;
			}
			else
			{
				if (0 == stricmp(token, "TRUE"))
				{
					m_bUseSecondaryPasswordSystemFlag = TRUE;
				}
				else
				{
					m_bUseSecondaryPasswordSystemFlag = FALSE;
				}
			}
		}
		// 2007-12-26 by dhjin, �Ʒ��� ���� - �Ʒ��� ���� ����
		else if(0 == stricmp(token, "ArenaServerFlag"))
		{
			token = config.strtok(NULL, seps);
			if(NULL == token)
			{
				char	szSystemLog[256];
				sprintf(szSystemLog, "Loading Configuration File Failed: ArenaServerLoading\r\n");
				this->WriteSystemLog(szSystemLog);
				DBGOUT(szSystemLog);
				return FALSE;
			}
			
			if(0 == stricmp(token, "TRUE"))
			{
				m_sArenaServerInfo.ArenaFieldServerCheck	= TRUE;
			}
			else if(0 == stricmp(token, "FALSE"))
			{// 2007-12-26 by dhjin, �Ʒ��� ���� ���� ����
				m_sArenaServerInfo.ArenaFieldServerCheck	= FALSE;
				// 2007-12-26 by dhjin, �Ʒ��� ���� �̸� ����
				token = config.strtok(NULL, seps);
				if(NULL == token)
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, "Loading Configuration File Failed: ArenaServerName\r\n");
					this->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);
					return FALSE;
				}				
				STRNCPY_MEMSET(m_sArenaServerInfo.ArenaServerName, token, SIZE_MAX_SERVER_NAME);
				// 2007-12-26 by dhjin, �Ʒ��� ���� ID ����
				token = config.strtok(NULL, seps);
				if(NULL == token)
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, "Loading Configuration File Failed: ArenaServerID\r\n");
					this->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);
					return FALSE;
				}
				m_sArenaServerInfo.ArenaServerID	= atoi(token);
				// 2007-12-26 by dhjin, �Ʒ��� Field ���� IP ����
				token = config.strtok(NULL, seps);
				if(NULL == token)
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, "Loading Configuration File Failed: ArenaFieldServerIP\r\n");
					this->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);
					return FALSE;
				}				
				STRNCPY_MEMSET(m_sArenaServerInfo.ArenaFieldServerIP, token, SIZE_MAX_IPADDRESS);
				// 2007-12-26 by dhjin, �Ʒ��� Field ���� Port ����
				token = config.strtok(NULL, seps);
				if(NULL == token)
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, "Loading Configuration File Failed: ArenaFieldServerPort\r\n");
					this->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);
					return FALSE;
				}
				m_sArenaServerInfo.ArenaFieldServerPort	= atoi(token);
				// 2007-12-26 by dhjin, �Ʒ��� IM ���� IP ����
				token = config.strtok(NULL, seps);
				if(NULL == token)
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, "Loading Configuration File Failed: ArenaIMServerIP\r\n");
					this->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);
					return FALSE;
				}				
				STRNCPY_MEMSET(m_sArenaServerInfo.ArenaIMServerIP, token, SIZE_MAX_IPADDRESS);
				// 2007-12-26 by dhjin, �Ʒ��� IM ���� Port ����
				token = config.strtok(NULL, seps);
				if(NULL == token)
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, "Loading Configuration File Failed: ArenaIMServerPort\r\n");
					this->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);
					return FALSE;
				}
				m_sArenaServerInfo.ArenaIMServerPort	= atoi(token);
			}
		}// 2007-12-26 by dhjin, �Ʒ��� ���� - �Ʒ��� ���� ����
		else if(0 == stricmp(token, CONFIG_NAME_DB_SERVER_IP))
		{// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
			
			token = config.strtok(NULL, seps);
			if (NULL == token)
			{
				char szErr[1024];
				sprintf(szErr, "[ERROR] CFieldGlobal::LoadConfiguration error !! %s, %s\r\n", CONFIG_NAME_DB_SERVER_IP, buffBackup);
				MessageBox(NULL, szErr, "Error", MB_OK);
				return FALSE;
			}
			
			STRNCPY_MEMSET(m_szDBServerIP, token, SIZE_MAX_ODBC_CONN_STRING);
		}
		else if(0 == stricmp(token, CONFIG_NAME_DB_SERVER_PORT))
		{// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
			
			token = config.strtok(NULL, seps);
			if (NULL == token)
			{
				char szErr[1024];
				sprintf(szErr, "[ERROR] CFieldGlobal::LoadConfiguration error !! %s, %s\r\n", CONFIG_NAME_DB_SERVER_PORT, buffBackup);
				MessageBox(NULL, szErr, "Error", MB_OK);
				return FALSE;
			}
			
			m_nDBServerPort = atoi(token);			
		}
		else if(0 == stricmp(token, CONFIG_NAME_DB_SERVER_DATABASE_NAEE))
		{// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
			
			token = config.strtok(NULL, seps);
			if (NULL == token)
			{
				char szErr[1024];
				sprintf(szErr, "[ERROR] CFieldGlobal::LoadConfiguration error !! %s, %s\r\n", CONFIG_NAME_DB_SERVER_DATABASE_NAEE, buffBackup);
				MessageBox(NULL, szErr, "Error", MB_OK);
				return FALSE;
			}
			
			STRNCPY_MEMSET(m_szDBServerDatabaseName, token, SIZE_MAX_ODBC_CONN_STRING);
		}
		else if(0 == stricmp(token, CONFIG_NAME_LOGDB_DB_SERVER_IP))
		{// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
			
			token = config.strtok(NULL, seps);
			if (NULL == token)
			{
				char szErr[1024];
				sprintf(szErr, "[ERROR] CFieldGlobal::LoadConfiguration error !! %s, %s\r\n", CONFIG_NAME_LOGDB_DB_SERVER_IP, buffBackup);
				MessageBox(NULL, szErr, "Error", MB_OK);
				return FALSE;
			}
			
			STRNCPY_MEMSET(m_szLogDBDBServerIP, token, SIZE_MAX_ODBC_CONN_STRING);
		}
		else if(0 == stricmp(token, CONFIG_NAME_LOGDB_DB_SERVER_PORT))
		{// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
			
			token = config.strtok(NULL, seps);
			if (NULL == token)
			{
				char szErr[1024];
				sprintf(szErr, "[ERROR] CFieldGlobal::LoadConfiguration error !! %s, %s\r\n", CONFIG_NAME_LOGDB_DB_SERVER_PORT, buffBackup);
				MessageBox(NULL, szErr, "Error", MB_OK);
				return FALSE;
			}
			
			m_nLogDBDBServerPort = atoi(token);			
		}
		else if(0 == stricmp(token, CONFIG_NAME_LOGDB_DB_SERVER_DATABASE_NAEE))
		{// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
			
			token = config.strtok(NULL, seps);
			if (NULL == token)
			{
				char szErr[1024];
				sprintf(szErr, "[ERROR] CFieldGlobal::LoadConfiguration error !! %s, %s\r\n", CONFIG_NAME_LOGDB_DB_SERVER_DATABASE_NAEE, buffBackup);
				MessageBox(NULL, szErr, "Error", MB_OK);
				return FALSE;
			}
			
			STRNCPY_MEMSET(m_szLogDBDBServerDatabaseName, token, SIZE_MAX_ODBC_CONN_STRING);
		}
		else if(0 == stricmp(token, "AllowedToolIP"))
		{// 2008-06-05 by cmkwon, AdminTool, Monitor ���� ���� IP�� server config file �� �����ϱ� - 
			
			token = config.strtok(NULL, seps);			
			if (token == NULL)
			{
				continue;
			}
			this->AddAllowedToolIP(token);
		}
		else if(0 == stricmp(token, "BillingDBServerIP"))
		{// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 

			token = config.strtok(NULL, seps);
			if(token)
			{
				STRNCPY_MEMSET(m_szBillingDBServerIP, token, SIZE_MAX_ODBC_CONN_STRING);
			}
		}
		else if(0 == stricmp(token, "BillingDBServerPort"))
		{// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
			token = config.strtok(NULL, seps);
			if(token)
			{
				m_nBillingDBServerPort = atoi(token);
			}
		}
		else if(0 == stricmp(token, "BillingDBServerDatabaseName"))
		{// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
			token = config.strtok(NULL, seps);
			if(token)
			{
				STRNCPY_MEMSET(m_szBillingDBServerDatabaseName, token, SIZE_MAX_ODBC_CONN_STRING);
			}
		}
		else if(0 == stricmp(token, "BillingDBServerUserID"))
		{// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
			token = config.strtok(NULL, seps);
			if(token)
			{
				STRNCPY_MEMSET(m_szBillingDBServerUserID, token, SIZE_MAX_ODBC_CONN_STRING);
				///////////////////////////////////////////////////////////////////////////////
				// 2008-09-01 by cmkwon, global.cfg ���Ͽ� DB ID/PWD ��ȣȭ - 
				BYTE byEncodedBinary[1024];
				MEMSET_ZERO(byEncodedBinary, 1024);
				if(XOR::XORString2Binary(byEncodedBinary, (char*)token))
				{
					MEMSET_ZERO(m_szBillingDBServerUserID, SIZE_MAX_ODBC_CONN_STRING);
					XOR::XOREncode((BYTE*)m_szBillingDBServerUserID, byEncodedBinary, strlen(token)/2, STR_XOR_KEY_STRING_DB_ID_PWD);
				}
			}
		}
		else if(0 == stricmp(token, "BillingDBServerPassword"))
		{// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
			token = config.strtok(NULL, seps);
			if(token)
			{
				STRNCPY_MEMSET(m_szBillingDBServerPassword, token, SIZE_MAX_ODBC_CONN_STRING);
				///////////////////////////////////////////////////////////////////////////////
				// 2008-09-01 by cmkwon, global.cfg ���Ͽ� DB ID/PWD ��ȣȭ - 
				BYTE byEncodedBinary[1024];
				MEMSET_ZERO(byEncodedBinary, 1024);
				if(XOR::XORString2Binary(byEncodedBinary, (char*)token))
				{
					MEMSET_ZERO(m_szBillingDBServerPassword, SIZE_MAX_ODBC_CONN_STRING);
					XOR::XOREncode((BYTE*)m_szBillingDBServerPassword, byEncodedBinary, strlen(token)/2, STR_XOR_KEY_STRING_DB_ID_PWD);
				}
			}
		}
		else if(stricmp(token, "ServerGroupInfo") == 0)
		{// 2008-09-24 by cmkwon, global.cfg ���� ���� - ServerGroup �� ������ ����
			
			// 2008-09-24 by cmkwon, Syntax						= [ServerGroupName]			[ServerGroupID]		[Enable Flag]
			token = config.strtok(NULL, seps);
			if (NULL == token)
			{
				continue;
			}
			char szTemp[CONFIG_SIZE_BUFF];
			STRNCPY_MEMSET(szTemp, token, CONFIG_SIZE_BUFF);
			vectstring tokenList;
			CConfig::GetTokenList(&tokenList, szTemp, seps);
			if(3 > tokenList.size())
			{
				if(0 != tokenList.size())
				{
					g_pGlobal->WriteSystemLogEX(TRUE, "[Error] CFieldGlobal::LoadConfiguration# error !! %s\r\n", buffBackup);
					return FALSE;
				}
				continue;
			}
			
			if(SIZE_MAX_SERVER_NAME <= strlen(tokenList[0].c_str()))
			{
				g_pGlobal->WriteSystemLogEX(TRUE, "[Error] CFieldGlobal::LoadConfiguration# longer than max servergroupname !! %s\r\n", buffBackup);
				return FALSE;
			}
			
			char	szGroupName[SIZE_MAX_SERVER_NAME];
			STRNCPY_MEMSET(szGroupName, tokenList[0].c_str(), SIZE_MAX_SERVER_NAME);
			int		nMGameServerID		= atoi(tokenList[1].c_str());			
			BOOL	bEnableServerGroup	= FALSE;			
			if(0 == stricmp(tokenList[2].c_str(), "TRUE"))
			{
				bEnableServerGroup	= TRUE;
			}
			
			if(nMGameServerID < SERVERGROUP_START_ID)
			{
				g_pGlobal->WriteSystemLogEX(TRUE, "[Error] CFieldGlobal::LoadConfiguration# smaller than min ServerGroupID !! %s\r\n", buffBackup);
				return FALSE;
			}
			
			if (FALSE == InsertServerGroupforMGame(szGroupName, nMGameServerID))
			{
				g_pGlobal->WriteSystemLogEX(TRUE, "[Error] CFieldGlobal::LoadConfiguration# Same ServerGroupName registered already !! %s\r\n", buffBackup);
				return FALSE;
			}

			g_pGlobal->WriteSystemLogEX(TRUE, "	ServerGroup: %20s, Enable(%d) MGameServerID(%5d)\r\n", szGroupName, bEnableServerGroup, nMGameServerID);
		}
		// 2009-06-03 by cmkwon, ���� ���ý� ���� �ý��� ��� ���� �÷��� �߰� - 
		else if(0 == stricmp(token, "UseInflSelectionRestrictSystem"))
		{
			token = config.strtok(NULL, seps);
			if (token
				&& 0 == stricmp("TRUE", token))
			{
				g_pFieldGlobal->SetUseInflSelectionRestrictSystem(TRUE);
			}
			else
			{
				g_pFieldGlobal->SetUseInflSelectionRestrictSystem(FALSE);
			}
		}
		else
		{
			// configuration file error!
			assert(0);
		}
	}
	fin.close();

	m_nMGameServerID1 = GetServerIDforMGame(GetServerGroupName());

	if(strcmp(this->GetIPLocal(), "") == 0
		|| strcmp(this->GetFieldServerGroupName(), "") == 0
		|| strcmp(this->GetIPPreServer(), "") == 0
		|| strcmp(this->GetIPIMServer(), "") == 0
		|| strcmp(this->GetIPLogServer(), "") == 0
		|| strcmp(this->GetIPVoIP1to1Server(), "") == 0
		|| strcmp(this->GetIPVoIPNtoNServer(), "") == 0
		|| this->GetPortListening() == 0
		|| this->GetPortLogServer() == 0
		|| this->GetPortIMServer() == 0
		|| this->GetPortPreServer() == 0
		|| this->GetPortVoIP1to1Server() == 0
		|| this->GetPortVoIPNtoNServer() == 0)
	{
		char	szError[1024];
		sprintf(szError, "[Error] LoadConfiguration() Loading Configuration Failed, LocalIP[%s] FieldServerGroupName[%s] PreServer[%s:%d] LogServer[%s:%d] IMServer[%s:%d]\r\n"
			, this->GetIPLocal(), this->GetFieldServerGroupName(),
			this->GetIPPreServer(), this->GetPortPreServer(),
			this->GetIPLogServer(), this->GetPortLogServer(),
			this->GetIPIMServer(), this->GetPortIMServer());
		this->WriteSystemLog(szError);
		DBGOUT(szError);

		MessageBox(NULL, szError, "ERROR", MB_OK);
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2007-12-03 by cmkwon, ���� �α� DB ���� ���� �ϱ� ���� ���� - üũ �߰�
// 2008-07-11 by cmkwon, MySQL ������ ���� ����(IP,Port �� DB ���� ����) - 
//	if(0 == strcmp((LPSTR)this->GetLogDBODBCDSN(), "")
	if(0 == strcmp((LPSTR)this->GetLogDBODBCUID(), "")
		|| 0 == strcmp((LPSTR)this->GetLogDBODBCPASSWORD(), ""))
	{
		char	szError[1024];
		sprintf(szError, "[Error] CFieldGlobal::LoadConfiguration_ You must set LogDBServer !!, LOGDB_ODBCUID(%s) LOGDB_ODBCPASSWORD(%s)\r\n"
			, (LPSTR)this->GetLogDBODBCUID(), (LPSTR)this->GetLogDBODBCPASSWORD());
		MessageBox(NULL, szError, "ERROR", MB_OK);
		return FALSE;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2008-08-26 by cmkwon, ��Ʈ�� VTC-Intecom_Viet 2�� �н����� �ý��� ���� ���� - �Ʒ��� �������� ��� 2�� �н����带 ������� �ʵ��� �Ѵ�.
	if(IsArenaServer())
	{
		m_bUseSecondaryPasswordSystemFlag	= FALSE;	// 2008-08-26 by cmkwon, ��Ʈ�� VTC-Intecom_Viet 2�� �н����� �ý��� ���� ���� - FALSE�� ����
	}

	return m_Localization.LoadConfiguration((char*)LOCALIZATION_CONFIG_DIRECTORY_PATH, this->m_nLanguageType);
}

BOOL CFieldGlobal::SendLogFieldServer2LogServer(BYTE *szLogMsg, int nLength)
{
// 2009-04-20 by cmkwon, F2L ���� �ý��� ���� - �Ʒ��� ���� ������.
// 	int nIndex = m_nSendIndexF2LWSocket;
// 	if(false == m_vectorF2LWSocketPtr.empty())
// 	{
// 		m_nSendIndexF2LWSocket = (++m_nSendIndexF2LWSocket)%m_vectorF2LWSocketPtr.size();
// 		nIndex = nIndex%m_vectorF2LWSocketPtr.size();
// 		if (m_vectorF2LWSocketPtr[nIndex]->IsConnected())
// 		{
// 			int nSize = m_vectorF2LWSocketPtr[nIndex]->GetSendBufferCounts();
// 			if(nSize > 1000)
// 			{
// 				char szTemp[512];
// 				sprintf(szTemp, "[ERROR] LogError, Index(%3d) SendBufferSize(%4d)\r\n", nIndex, nSize);
// 				this->WriteSystemLog(szTemp);
// 			}
// 			if (m_vectorF2LWSocketPtr[nIndex]->Write(szLogMsg, nLength) == TRUE)
// 			{
// 				return TRUE;
// 			}
// 		}
// 	}
// 	char szTemp[512];
// 	sprintf(szTemp, "[ERROR] SendLogError, ArraySize(%2d) Index(%3d)\r\n"
// 		, m_vectorF2LWSocketPtr.size(), nIndex);
// 	this->WriteSystemLog(szTemp);
	///////////////////////////////////////////////////////////////////////////////
	// 2009-04-20 by cmkwon, F2L ���� �ý��� ���� - �Ʒ����� ó���ϰ� ����
	if(m_vectorF2LWSocketPtr.empty())
	{
		g_pFieldGlobal->WriteSystemLogEX(TRUE, "  [ERROR] Nothing F2L socket !! ArraySize(%d) \r\n", m_vectorF2LWSocketPtr.size());
		return FALSE;
	}

	int nCurF2LSocketIndex = m_nSendIndexF2LWSocket;
	for(int i = 0; i < SIZE_FIELD2LOG_WINSOCKET; i++)
	{
		int nIdx = (nCurF2LSocketIndex + i)%m_vectorF2LWSocketPtr.size();
		if(NULL == m_vectorF2LWSocketPtr[nIdx]
			|| FALSE == m_vectorF2LWSocketPtr[nIdx]->IsConnected())
		{
			continue;
		}
		int nSize = m_vectorF2LWSocketPtr[nIdx]->GetSendBufferCounts();
		if(nSize > 500)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "  [Notify] LogError, Index(%3d) CLogWinSocket(0x%X) SendBufferSize(%4d) \r\n", nIdx, m_vectorF2LWSocketPtr[nIdx], nSize);
		}
		if (m_vectorF2LWSocketPtr[nIdx]->Write(szLogMsg, nLength))
		{
			m_nSendIndexF2LWSocket = (++nIdx)%m_vectorF2LWSocketPtr.size();
			return TRUE;
		}
		g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] F2L send to LogServer fail !!, Index(%3d) CLogWinSocket(0x%X) SendBufferSize(%4d), SockHandle(%d) IsConnected(%d) \r\n"
			, nIdx, m_vectorF2LWSocketPtr[nIdx], nSize, m_vectorF2LWSocketPtr[nIdx]->GetSocketHandle(), m_vectorF2LWSocketPtr[nIdx]->IsConnected());
	}

	g_pFieldGlobal->WriteSystemLogEX(TRUE, "[ERROR] F2L send to LogServer all fail !!, ArraySize(%d) \r\n", m_vectorF2LWSocketPtr.size());	
	return FALSE;
}

BOOL CFieldGlobal::SendLogFieldServer2LogServerORGFile(BYTE *szLogMsg, int nLength)
{
//	if(this->GetPtrFieldGameLogManager()->GetFileHandle() == NULL)
//	{
//		if(FALSE == this->GetPtrFieldGameLogManager()->InitLogManger(TRUE, "FieldGameLog", (char*)(string(CONFIG_ROOT) + "../log/GameLog/").c_str()))
//		{
//			return FALSE;
//		}
//	}
//	this->WriteGameLog(*(MessageType_t*)szLogMsg, (MSG_FL_LOG*)(szLogMsg+SIZE_FIELD_TYPE_HEADER), (char*)szLogMsg + MSG_SIZE(MSG_FL_LOG));

	return TRUE;
}


void CFieldGlobal::OnF2LAsyncEvent(SOCKET i_hSocket, LONG i_nEvent)
{
	int nSize = m_vectorF2LWSocketPtr.size();
	for(int i=0; i < nSize; i++)
	{
		if(m_vectorF2LWSocketPtr[i]
			&& m_vectorF2LWSocketPtr[i]->GetSocketHandle() == i_hSocket)
		{
			if(FD_CLOSE == WSAGETSELECTEVENT(i_nEvent))
			{
				// 2009-05-06 by cmkwon, �ý��� �α� �߰�(F2L����) - 
				this->WriteSystemLogEX(TRUE, "[Notify] ON FD_Close(%s:%d) SockH(%ld) ErrorCode(%d) \r\n", m_vectorF2LWSocketPtr[i]->m_szPeerIP, m_vectorF2LWSocketPtr[i]->m_nPeerPort, m_vectorF2LWSocketPtr[i]->GetSocketHandle(), WSAGETSELECTERROR(i_nEvent));
			}
			m_vectorF2LWSocketPtr[i]->OnAsyncEvent(i_nEvent);
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-04-20 by cmkwon, F2L ���� �ý��� ���� - 
/// \author		cmkwon
/// \date		2009-04-20 ~ 2009-04-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::OnF2LClosed(CLogWinSocket *i_pF2LWinSoc)
{
	if(NULL == i_pF2LWinSoc)
	{
		return FALSE;
	}

	int nSize = m_vectorF2LWSocketPtr.size();
	for(int i=0; i < nSize; i++)
	{
		if(m_vectorF2LWSocketPtr[i]
			&& m_vectorF2LWSocketPtr[i] == i_pF2LWinSoc)
		{
			g_pFieldGlobal->WriteSystemLogEX(TRUE, "  [Notify] F2L socket closed ! Index(%2d) CLogWinSocket(0x%X) \r\n", i, i_pF2LWinSoc);
			i_pF2LWinSoc->CloseSocket();			
			return TRUE;
		}
	}
	return FALSE;
}



///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldGlobal::Send2PreServer(BYTE *i_pData, int i_nDataLen)
/// \brief		// 2007-11-19 by cmkwon, ���� ��/���� ��ɾ�� ������ �ý��� ���� - CFieldGlobal::Send2PreServer() �߰�
/// \author		cmkwon
/// \date		2008-01-31 ~ 2008-01-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::Send2PreServer(BYTE *i_pData, int i_nDataLen)
{
	CPreWinSocket *pF2PreSoc = this->GetField2PreWinSocket();
	if(NULL == pF2PreSoc
		|| FALSE == pF2PreSoc->IsConnected())
	{
		return FALSE;
	}

	return pF2PreSoc->Write(i_pData, i_nDataLen);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldGlobal::LoadResObjCheckListW(BOOL i_bReloadOnlyRexTexDirectory/*=FALSE*/)
/// \brief		// 2008-09-08 by cmkwon, SCMonitor���� ReloadVersionInfo�ÿ� �Ϻ� üũ������(.\Res-Tex\*.*)�� ���ε��ϱ� - 
/// \author		cmkwon
/// \date		2008-09-08 ~ 2008-09-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::LoadResObjCheckListW(BOOL i_bReloadOnlyRexTexDirectory/*=FALSE*/)
{
	if(NULL == m_pGIOCP)
	{
		return FALSE;
	}

	CFieldIOCP *pFIOCP = (CFieldIOCP*)(m_pGIOCP);

	if(NULL == pFIOCP
		|| FALSE == pFIOCP->GetListeningFlag()
		|| FALSE == pFIOCP->GetServiceStartFlag())
	{
		return FALSE;
	}

	return pFIOCP->LoadResObjCheckList(i_bReloadOnlyRexTexDirectory);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldGlobal::IsArenaServer(void)
/// \brief		// 2009-03-05 by cmkwon, �������� �Ʒ��� ���� ó�� - 
/// \author		cmkwon
/// \date		2009-03-05 ~ 2009-03-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::IsArenaServer(void)
{
#ifdef ARENA
	return true;
#else
	return m_sArenaServerInfo.ArenaFieldServerCheck;
#endif
}
BOOL CFieldGlobal::ConnectAllF2LWSocket(char *i_szSvrIP, int i_nSvrPort)
{
	int nSize = m_vectorF2LWSocketPtr.size();
	for(int i=0; i < nSize; i++)
	{
		if(m_vectorF2LWSocketPtr[i]
			&& FALSE == m_vectorF2LWSocketPtr[i]->IsConnected())
		{
			m_vectorF2LWSocketPtr[i]->Connect(i_szSvrIP, i_nSvrPort);
		}
	}

	return TRUE;
}

BOOL CFieldGlobal::ReConnectAllF2LWSocket(char *i_szSvrIP, int i_nSvrPort)
{
	int nSize = m_vectorF2LWSocketPtr.size();
	for(int i=0; i < nSize; i++)
	{
		if(m_vectorF2LWSocketPtr[i]
			&& INVALID_SOCKET == m_vectorF2LWSocketPtr[i]->GetSocketHandle())
		{
			m_vectorF2LWSocketPtr[i]->Connect(i_szSvrIP, i_nSvrPort);
		}
	}

	return TRUE;
}

BOOL CFieldGlobal::IsConnectedAllF2LWSocket(void)
{
	int nSize = m_vectorF2LWSocketPtr.size();
	for(int i=0; i < nSize; i++)
	{
		if(NULL == m_vectorF2LWSocketPtr[i]
			|| FALSE == m_vectorF2LWSocketPtr[i]->IsConnected())
		{
			return FALSE;
		}
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldGlobal::LoadPCBangIPListFromConfig()
/// \brief		PC�� ����Ʈ �ε�.
/// \author		dhjin
/// \date		2006-08-14 ~ 2006-08-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::LoadPCBangIPListFromConfig()
{

	const int	SIZE_BUFF = 1024;
	char		buff[SIZE_BUFF];
	const char	*token;
	char		seps[] = " \t";
	
	ifstream	fin;
	CConfig		config;

	if (!config.LoadUserDefinedVariables( PCBANG_IPADDR_FILE_PATH))
	{
		char	szError[1024];
		sprintf(szError, "[Error] LoadPCBangIPListFromConfig LoadUserDefinedVariables_2() error, FileName[%s]\r\n"
			, FIELD_SERVER_CONFIG_FILE_PATH);
		this->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	fin.open(PCBANG_IPADDR_FILE_PATH);
	if (!fin.is_open())
	{	// cannot open file...

		int nErr = GetLastError();
		SetLastError(0);
		char	szError[1024];
		sprintf(szError, "[Error] LoadPCBangIPListFromConfig open() error, LastError[%d] ConfigFileName[%s]\r\n"
			, nErr, PCBANG_IPADDR_FILE_PATH);
		this->WriteSystemLog(szError);
		DBGOUT(szError);
		return FALSE;
	}

	
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

		if (strchr(token,'~'))
		{
			char token0[SIZE_BUFF];
			strcpy(token0,token);
			char * pIPStart0 = strtok(token0,"~");
			char * pIPEndD   = strtok(NULL," \t");
			
			char * pIPClassA = strtok(pIPStart0,".");
			char * pIPClassB = strtok(NULL,".");
			char * pIPClassC = strtok(NULL,".");
			char * pIPClassD = strtok(NULL," \t");
			
			int iIPStartA	 = atoi(pIPClassA);
			int iIPStartB	 = atoi(pIPClassB);
			int iIPStartC	 = atoi(pIPClassC);
			int iIPStartD	 = atoi(pIPClassD);
			int iIPEndD		 = atoi(pIPEndD);
			
			if (FALSE == IS_IN_RANGE(0, iIPStartA, 255) ||
				FALSE == IS_IN_RANGE(0, iIPStartB, 255) ||
				FALSE == IS_IN_RANGE(0, iIPStartC, 255) ||
				FALSE == IS_IN_RANGE(0, iIPStartD, 255))
			{
				char	szError[1024];
				sprintf(szError, "[Error] LoadPCBangIPListFromConfig open() error, ConfigFileName[%s] ==> %s\r\n"
					, PCBANG_IPADDR_FILE_PATH, token);
				this->WriteSystemLog(szError);
				DBGOUT(szError);
				return FALSE;
			}			
			
			int IPClassDGap	 = (iIPEndD - iIPStartD);

			if ( 0 > IPClassDGap)
			{
				char	szError[1024];
				sprintf(szError, "[Error] LoadPCBangIPListFromConfig open() error, ConfigFileName[%s] ==> %s\r\n"
					, PCBANG_IPADDR_FILE_PATH, token);
				this->WriteSystemLog(szError);
				DBGOUT(szError);
				return FALSE;
			}
			
			for (int i=0 ; i <= IPClassDGap; i++)
			{				
				char szIP[SIZE_BUFF];
				sprintf(szIP, "%d.%d.%d.%d", iIPStartA, iIPStartB, iIPStartC, iIPStartD+i);
				m_setPCBangIPList.insert(szIP);
			}
			
			continue;
		}

		char token0[SIZE_BUFF];
		strcpy(token0,token);
	
		char * pIPClassA = strtok(token0,".");
		char * pIPClassB = strtok(NULL,".");
		char * pIPClassC = strtok(NULL,".");
		char * pIPClassD = strtok(NULL," \t");
		
		int iIPStartA	 = atoi(pIPClassA);
		int iIPStartB	 = atoi(pIPClassB);
		int iIPStartC	 = atoi(pIPClassC);
		int iIPStartD	 = atoi(pIPClassD);

		if (FALSE == IS_IN_RANGE(0, iIPStartA, 255) ||
			FALSE == IS_IN_RANGE(0, iIPStartB, 255) ||
			FALSE == IS_IN_RANGE(0, iIPStartC, 255) ||
			FALSE == IS_IN_RANGE(0, iIPStartD, 255))
		{
			char	szError[1024];
			sprintf(szError, "[Error] LoadPCBangIPListFromConfig open() error, ConfigFileName[%s] ==> %s\r\n"
				, PCBANG_IPADDR_FILE_PATH, token);
			this->WriteSystemLog(szError);
			DBGOUT(szError);
			return FALSE;
		}

		char szIP[SIZE_BUFF];
		sprintf(szIP, "%d.%d.%d.%d", iIPStartA, iIPStartB, iIPStartC, iIPStartD);
		m_setPCBangIPList.insert(szIP);
	}

	fin.close();
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldGlobal::GetUseSecondaryPasswordSystemFlag(void)
/// \brief		// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - CFieldGlobal �� ��� �Լ� �߰�
/// \author		cmkwon
/// \date		2007-09-12 ~ 2007-09-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::GetUseSecondaryPasswordSystemFlag(void)
{
	return m_bUseSecondaryPasswordSystemFlag;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldGlobal::SetDBServerGroup(SDBSERVER_GROUP *i_pDBServGroup)
/// \brief		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - CFieldGlobal::SetDBServerGroup() �߰�
/// \author		cmkwon
/// \date		2008-04-29 ~ 2008-04-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldGlobal::SetDBServerGroup(SDBSERVER_GROUP *i_pDBServGroup)
{
	m_DBServerGroup		= *i_pDBServGroup;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CFieldGlobal::GetBillingDBServerIP(void)
/// \brief		// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
/// \author		cmkwon
/// \date		2008-07-30 ~ 2008-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CFieldGlobal::GetBillingDBServerIP(void)
{
	return m_szBillingDBServerIP;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CFieldGlobal::GetBillingDBServerPort(void)
/// \brief		// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
/// \author		cmkwon
/// \date		2008-07-30 ~ 2008-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CFieldGlobal::GetBillingDBServerPort(void)
{
	return m_nBillingDBServerPort;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CFieldGlobal::GetBillingDBServerDatabaseName(void)
/// \brief		// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
/// \author		cmkwon
/// \date		2008-07-30 ~ 2008-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CFieldGlobal::GetBillingDBServerDatabaseName(void)
{
	return m_szBillingDBServerDatabaseName;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CFieldGlobal::GetBillingDBServerUserID(void)
/// \brief		// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
/// \author		cmkwon
/// \date		2008-07-30 ~ 2008-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CFieldGlobal::GetBillingDBServerUserID(void)
{
	return m_szBillingDBServerUserID;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CFieldGlobal::GetBillingDBServerPassword(void)
/// \brief		// 2008-07-30 by cmkwon, Yedang_Kor ���� DBServer ���� �����ϵ��� ���� - 
/// \author		cmkwon
/// \date		2008-07-30 ~ 2008-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CFieldGlobal::GetBillingDBServerPassword(void)
{
	return m_szBillingDBServerPassword;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldGlobal::SendArenaServerMFSInfo()
/// \brief		�Ʒ��� ���� - �Ʒ��� ������ �ʵ� ���� ���� ����
/// \author		dhjin
/// \date		2008-01-17 ~ 2008-01-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldGlobal::SendArenaServerMFSInfo()
{
	// 2009-04-17 by cmkwon, ����Arena ���� ���� ���� - CFieldGlobal::InitServerSocket()���� �����ϰ� ����
	//m_pField2ArenaFieldWinSocket->SetFieldIOCP(((CFieldIOCP*)m_pGIOCP));

	// 2007-12-27 by dhjin, �Ʒ��� ���� - �Ʒ��� ������ �ʵ� ���� ���� ����
	INIT_MSG_WITH_BUFFER(MSG_FtoA_MFSINFO, T_FtoA_MFSINFO, pMsgFtoAConn, FtoASendBuf);
	pMsgFtoAConn->MFS_ID	= this->GetMGameServerID();
	pMsgFtoAConn->MFS_Port	= this->GetPortListening();
	STRNCPY_MEMSET(pMsgFtoAConn->MFS_Name, this->GetFieldServerGroupName(), SIZE_MAX_SERVER_NAME);
	STRNCPY_MEMSET(pMsgFtoAConn->MFS_IP, this->GetPublicIPLocal(), SIZE_MAX_IPADDRESS);

	m_pField2ArenaFieldWinSocket->Write((char*)FtoASendBuf, MSG_SIZE(MSG_FtoA_MFSINFO));
	this->WriteSystemLogEX(TRUE, "[Notify] CFieldGlobal::InitServerSocket_ send to ArenaServer !!\r\n");
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldGlobal::GetUseInflSelectionRestrictSystem(void)
/// \brief		// 2009-06-03 by cmkwon, ���� ���ý� ���� �ý��� ��� ���� �÷��� �߰� - 
/// \author		cmkwon
/// \date		2009-06-03 ~ 2009-06-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::GetUseInflSelectionRestrictSystem(void)
{
	return m_bUseInflSelectionRestrictSystem;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CFieldGlobal::SetUseInflSelectionRestrictSystem(BOOL i_bFlag)
/// \brief		// 2009-06-03 by cmkwon, ���� ���ý� ���� �ý��� ��� ���� �÷��� �߰� - 
/// \author		cmkwon
/// \date		2009-06-03 ~ 2009-06-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CFieldGlobal::SetUseInflSelectionRestrictSystem(BOOL i_bFlag)
{
	m_bUseInflSelectionRestrictSystem	= i_bFlag;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CFieldGlobal::checkSHUTDOWNMINORS(int i_birthdayYears /* ���� */ , ATUM_DATE_TIME currentTime/* ���� �ð� */)
/// \brief		// start 2011-11-03 by shcho, yedang �˴ٿ��� ����
/// \author		shcho
/// \date		20111110 ~
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CFieldGlobal::checkSHUTDOWNMINORS(int i_birthdayYears /* ���� */ , ATUM_DATE_TIME currentTime/* ���� �ð� */) 
{ // �⵵�� üũ �Լ�
	int nCurrentTime = (currentTime.Year*10000)+(currentTime.Month*100)+(currentTime.Day);
	
	if(10000 > i_birthdayYears)
	{ // �⵵�϶� 
		i_birthdayYears = i_birthdayYears * 10000; // �� 16�� (17��)
	}
	
	// �ƴϸ� ������ �����Ѵ�.
	if(160000 <= nCurrentTime-i_birthdayYears)
	{ // ���� 
		return FALSE;
	}
	else
	{ // 16�� �̸� 
		return TRUE;
	}
}

// 2013-04-01 by hskim, NPCServer ???? ?? ?? ??
/*BOOL CFieldGlobal::CheckAllowedNPCServerIP(char *i_szIP)
{
	if (0 == strncmp(this->GetIPNPCServer(), i_szIP, strlen(this->GetIPNPCServer())))
	{		
		return TRUE;
	}

	g_pGlobalGameServer->WriteSystemLogEX(TRUE, "  [Notify] CheckAllowedNPCServerIP ==> Not Allowed (%s) !!\r\n", i_szIP);

	return FALSE;
}*/
// end 2013-04-01 by hskim, NPCServer ???? ?? ?? ??
