// PreGlobal.h: interface for the CPreGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREGLOBAL_H__C876B35F_9CED_4C8B_BB4C_3BB6B23FD13D__INCLUDED_)
#define AFX_PREGLOBAL_H__C876B35F_9CED_4C8B_BB4C_3BB6B23FD13D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GlobalGameServer.h"
#include "AtumProtocol.h"			// 2007-05-02 by cmkwon


typedef vector<SGAME_SERVER_GROUP>			vectSGAME_SERVER_GROUP;		// 2007-05-02 by cmkwon


class CPreIOCP;
class CPreIOCPSocket;
class CPreGlobal;
class CSecurityManager;			// 2011-06-22 by hskim, 사설 서버 방지

extern CPreGlobal *		g_pPreGlobal;

// start 2011-06-22 by hskim, 사설 서버 방지
#ifdef  S_AUTHENTICATION_SERVER_HSKIM		// 2011-01-26 by hskim, 인증 서버 구현
#define MasangPreServerIP		"ggas.masangsoft.com"		// 인증서버 Domain
#define MasangPreServerPort		14999
#else
#define MasangPreServerIP		"61.39.170.131"
#define MasangPreServerPort		15100
#endif
// end 2011-06-22 by hskim, 사설 서버 방지

///////////////////////////////////////////////////////////////////////////////
/// \class		CPreGlobal
///
/// \brief
/// \author		cmkwon
/// \version
/// \date		2004-03-18 ~ 2004-03-18
/// \warning	오직 하나의 객체만을 생성할수 있다, 생성은 되지만 정상적인 처리가 되지 않는다.
///////////////////////////////////////////////////////////////////////////////
class CServerGroup;
class CSPToMPWinSocket;		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
class CPreGlobal : public CGlobalGameServer
{
	friend class CPreIOCP;

public:
	CPreGlobal();
	virtual ~CPreGlobal();

	void Reset();

	BOOL InitGlobal(char * i_szServerName);		// 2011-06-22 by hskim, 사설 서버 방지

	///////////////////////////////////////////////////////////////////////////
	// Property
	void	SetUploadFTPIP(char *i_szIP);
	char*	GetUploadFTPIP(void);
	void	SetUploadFTPPort(int i_nPort);
	int		GetUploadFTPPort(void);
	void	SetUploadFTPAccount(char * i_szAccount);
	char*	GetUploadFTPAccount(void);
	void	SetUploadFTPPassword(char * i_szPassword);
	char*	GetUploadFTPPassword(void);

	void	SetDownloadFTPPort(int i_nPort);
	int		GetDownloadFTPPort(void);
	void	SetDownloadFTPAccount(char * i_szAccount);
	char*	GetDownloadFTPAccount(void);
	void	SetDownloadFTPPassword(char * i_szPassword);
	char*	GetDownloadFTPPassword(void);


	VersionInfo GetClientReinstallVersion(void);
	BOOL GetRandomFieldSelect(void) { return m_bRandomFieldSelect; }

	///////////////////////////////////////////////////////////////////////////////
	// 2007-01-08 by cmkwon, Auto Update FTP or HTTP
	int		GetAutoUpdateServerType(void);
	const char * GetDownloadServerIP(void);
	int		GetDownloadServerPort(void);
	char *	GetDownloadServerAccountName(void);
	char *	GetDownloadServerPassword(void);
	char *	GetClientUpdateDownloadDir(void);
	char *	GetLauncherFileDownloadPath(void);
	char *	GetDeleteFileListDownloadPath(void);
	char *	GetNoticeFileDownloadPath(void);

	///////////////////////////////////////////////////////////////////////////////
	// 2007-01-08 by cmkwon
	void AddDownloadHttpIP(const char * i_szIP);
	const char * GetRandomDownloadHttpIP(void);


	///////////////////////////////////////////////////////////////////////////
	// Method
	void AddDownloadFTPIP(char * i_szIP);
	const char *GetRandomDownloadFTPIP(void);

	BOOL CheckAllowedList(CServerGroup *i_pGroupInfo, char * i_szAccountName, char * i_szPrivateIP, USHORT i_nAccountType);
	void PrintAllowedList(void);
	BOOL CheckAllowedIP(char *i_szPublicIP);		// 2007-10-19 by cmkwon, AllowedIP 시스템 변경 - 허가 IP 체크 함수 

	CServerGroup * GetServerGroupForLoading(const char * szServerGruopName);
	int GetEnableServerGroupCount(void);	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 

	// 2007-05-02 by cmkwon
	// 2007-09-05 by cmkwon, EXE_1에 로그인 서버 선택 인터페이스 수정 - 인자추가(, USHORT i_usTab8OrderIndex), 인자 제거(, USHORT i_usPreServerPort, 포트는 기본 포트 사용)
	BOOL InsertGameServerGroup(char *i_szGameServerGroupName, char *i_szPreServerIP, int i_nTab8OrderIndex);
	BOOL Make_MSG_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST(MSG_PC_CONNECT_GET_GAME_SERVER_GROUP_LIST_OK *o_pGameServerGroupList);
	BOOL Make_MSG_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST_OK(MSG_PC_CONNECT_GET_NEW_GAME_SERVER_GROUP_LIST_OK *o_pGameServerGroupList);	// 2007-09-05 by cmkwon, EXE_1에 로그인 서버 선택 인터페이스 수정 - 신버전 함수 추가

	// 2007-07-06 by cmkwon, OnlyChoiceServer 플래그 구현 추가
	BOOL GetOnlyChoiceServer(void);

	///////////////////////////////////////////////////////////////////////////////
	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
	BOOL createPreToAllServer(HWND i_hWnd);
	BOOL connectBySPToMPWinSoc(char *i_szIP, int i_nPort);
	BOOL sendToMasangPreServer(BYTE *i_pData, int i_nDataLen);
	BOOL OnAsyncEventOfSPToMPWinSoc(SOCKET i_hSocket, LONG i_nEvent);
	BOOL OnPacketNotifyOfSPToMPWinSoc(WORD i_wNotifyTy, WORD i_wParam);

	char * GetGamePublisherName(void);		// 2010-06-01 by shcho, GLogDB 관련 -

	void SendToAuthenticationServer();		// 2011-06-22 by hskim, 사설 서버 방지

public:
	// virtual Function
	virtual BOOL InitServerSocket(void);				// 소켓관련 초기화 함수
	virtual BOOL EndServerSocket(void);					// 소켓관련 종료 함수

	virtual BOOL LoadConfiguration(void);				// Server 설정을 위한 Configuration Load

protected:
	// 다운로드용
	vector<string>			m_vectorDownloadFTPIP;
	int						m_nDownloadFTPPort;
	char					m_szDownloadFTPAccount[SIZE_MAX_ACCOUNT_NAME];
	char					m_szDownloadFTPPassword[SIZE_MAX_PASSWORD];

	// 업로드용 및 PreServer 연결용
	char					m_szUploadFTPIP[SIZE_MAX_FTP_URL];	// 업데이트 및 PreServer의 업데이트 버전 확인을 위한 FTP server
	int						m_nUploadFTPPort;
	char					m_szUploadFTPAccount[SIZE_MAX_ACCOUNT_NAME];
	char					m_szUploadFTPPassword[SIZE_MAX_PASSWORD];

	VersionInfo				m_ClientReinstallVersion;		// re-install version
	vector<VersionInfo>		m_vectorCriticalUpdateVersion;	// critical update version list
	vector<string>			m_AllowedIPList;
	set<string>				m_AllowedAccounts;
	BOOL					m_bRandomFieldSelect;			// Pre Server에서 최초로 접속해야 할 Field Server의 IP를 받을 때 Random으로 받을지에 대한 여부
	vector<CServerGroup*>	m_AllServerGroupVectorForLoading;	// 다 로딩한 후에는 바로 삭제함

	///////////////////////////////////////////////////////////////////////////////	
	// 2007-05-02 by cmkwon, PreServer 여러개 등록
	vectSGAME_SERVER_GROUP	m_vectGameServerGroupList;

	// 2007-07-06 by cmkwon, OnlyChoiceServer 플래그 구현 추가
	BOOL					m_bIsOnlyChoiceServer;				// 2007-07-06 by cmkwon, OnlyChoiceServer 플래그 구현 추가

	char					m_szGamePublisherName[SIZE_MAX_GAME_PUBLISHER_NAME];		// 2010-06-01 by shcho, GLogDB 관련 -
public:
	BOOL					m_bIgnoreClientVersionUpdate;
	int						m_nServerGroupLimiteUserCount;		// 2006-10-11 by cmkwon

public:
	// 클라이언트 업데이트 경로
	char					m_szClientFTPUpdateUploadDir[SIZE_MAX_FTP_FILE_PATH];	// UPDATE_DIR// 2005-12-23 by cmkwon, 수정함
	char					m_szClientFTPUpdateDownloadDir[SIZE_MAX_FTP_FILE_PATH];	// 2005-12-23 by cmkwon, 추가함, UPDATE_DWONLOAD_DIR
	char					m_szLauncherFileUploadPath[SIZE_MAX_FTP_FILE_PATH];		// LAUNCHER_FILE_NAME,// 2005-12-23 by cmkwon 수정
	char					m_szLauncherFileDownloadPath[SIZE_MAX_FTP_FILE_PATH];	// 2005-12-23 by cmkwon, 추가함
	char					m_szDeleteFileListUploadPath[SIZE_MAX_FTP_FILE_PATH];	// DELFILELIST_FILE_NAME// 2005-12-23 by cmkwon
	char					m_szDeleteFileListDownloadPath[SIZE_MAX_FTP_FILE_PATH];	// DELFILELIST_FILE_NAME// 2005-12-23 by cmkwon
	char					m_szNoticeFileUploadPath[SIZE_MAX_FTP_FILE_PATH];		// NOTICE_FILE_NAME// 2005-12-23 by cmkwon
	char					m_szNoticeFileDownloadPath[SIZE_MAX_FTP_FILE_PATH];		// NOTICE_FILE_NAME// 2005-12-23 by cmkwon
	char					m_szVersionListFileUploadPath[SIZE_MAX_FTP_FILE_PATH];	// 2007-01-08 by cmkwon

	///////////////////////////////////////////////////////////////////////////////	
	// 2007-01-06 by cmkwon, Http Auto Update server 구현 추가
	// 2007-01-06 by cmkwon, HTTP Server 정보
	int						m_nAutoUpdateServerType;						// 2007-01-06 by cmkwon, AU_SERVER_TYPE_XXX
	vector<string>			m_vectDownloadHttpServer;
	USHORT					m_nDownloadHttpServerPort;
	char					m_szDownloadHttpServerAccountName[SIZE_MAX_ACCOUNT_NAME];
	char					m_szDownloadHttpServerPassword[SIZE_MAX_PASSWORD];
	char					m_szClientHttpUpdateDownloadDir[SIZE_MAX_FTP_FILE_PATH];
	char					m_szLauncherFileDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];
	char					m_szDeleteFileListDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];
	char					m_szNoticeFileDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];
	char					m_szVersionListFileDownloadHttpPath[SIZE_MAX_FTP_FILE_PATH];	// 2007-01-08 by cmkwon

	///////////////////////////////////////////////////////////////////////////////
	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
	CSPToMPWinSocket		*m_pSPToMPWinsoc;				

	CSecurityManager		*m_pSecurityManager;			// 2011-06-22 by hskim, 사설 서버 방지
};

#endif // !defined(AFX_PREGLOBAL_H__C876B35F_9CED_4C8B_BB4C_3BB6B23FD13D__INCLUDED_)
