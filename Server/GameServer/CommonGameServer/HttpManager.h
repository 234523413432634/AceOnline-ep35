// HttpManager.h: interface for the CHttpManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPMANAGER_H__E13E07CA_89E6_4697_A0E6_C9C5FDECC8F7__INCLUDED_)
#define AFX_HTTPMANAGER_H__E13E07CA_89E6_4697_A0E6_C9C5FDECC8F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define HM_SIZE_MAX_FILE_NAME				1024

class CHttpManager  
{
public:
	CHttpManager();
	~CHttpManager();

	HANDLE GetDownloadThreadHandle(void);
	void SetDownloadThreadCancelFlag(BOOL i_bCancelFlag);
	BOOL ThreadEnd(DWORD i_dwWaitTimems);

	Err_t DownloadFileByHttp(const char *i_pServerName, int i_nServerPort, const char *i_pRemoteFileName, const char *i_pLocalFileName, BOOL i_bUseThread=FALSE, HWND i_hUpdateWindow=0);
	Err_t _DownLoadFileByHttp(void);

	void PostMessage2UpdateWindow(UINT i_uiMsgTy, WPARAM i_wParam, LPARAM i_lParam);
private:
	HANDLE		m_hDownloadThread;
	BOOL		m_bDownloadThreadCancelFlag;
	char		m_szServerName[HM_SIZE_MAX_FILE_NAME];
	int			m_nServerPort;
	char		m_szRemoteFileName[HM_SIZE_MAX_FILE_NAME];
	char		m_szLocalFileName[HM_SIZE_MAX_FILE_NAME];
	HWND		m_hUpdateWindow;
};

#endif // !defined(AFX_HTTPMANAGER_H__E13E07CA_89E6_4697_A0E6_C9C5FDECC8F7__INCLUDED_)
