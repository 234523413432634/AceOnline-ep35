// AtumLauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AtumLauncher.h"
#include "AtumLauncherDlg.h"
#include <iostream>
#include <strstream>
#include <fstream>
#include "dbgout_c.h"
#include "ftpdownload.h"
#include <direct.h>
#include "PreServerIPDlg.h"
#include "md5_lib_src.h"
#include "LoginSuccessDlg.h"
#include "Wininet.h"
#include "FTPManager.h"
#include "ZipArchive/ZipArchive.h"
// ysw
#include <afxhtml.h>
#include "MGameDecryption.h"
#include "AtumError.h"
#include "HttpManager.h"					// 2007-01-08 by cmkwon
#include "screenkeyboarddlg.h"				// 2007-09-10 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
#include "DlgGuardAgreement.h"				// 2009-08-31 by cmkwon, Gameforge4D ���Ӱ��� ����â ���� - 

#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
// 2009-10-29 by cmkwon, ��Ʈ�� X-TRAP �ڵ�������Ʈ ��� ���� - 
#pragma comment(lib, "XTrap4Launcher_mt.lib")
#include "Security/XTrap4Launcher.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - ������� �߰�
// 2009-04-23 by cmkwon, ���þ� Innova Frost �ӽ� �����ϱ� - �Ʒ��� ���� define ���� ó�� ��.
//#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1) && defined(_USING_INNOVA_FROST_)

// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - 
//#pragma comment(lib, "ayyo_game.lib")
//#include "SharedMemory.h"					// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - 
//#include "ShieldSecurity.h"					// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - 
///////////////////////////////////////////////////////////////////////////////
// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - 
#include "Security\shieldSecurity.h"				// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - 
#include "Security\shieldSecurityDll.h"				// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - 

#endif // END - #if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NOTICE_FILE_NAME "notice.txt"
#define DELFILELIST_FILE_NAME "deletefilelist.txt"

#define STRING_SERVER_GROUP_NAME_DELIMIT				" "
#define TICKGAP_NETWORK_STATE_WORST_PING_TICK			1500		// 2007-06-21 by cmkwon, ��� Ping �ӵ��� �����ϵ��� ������

struct SWINDOW_DEGREE
{
	char	*szWindowDegreeName;
	int		nCX;
	int		nCY;
	int		nDegree;
};

// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �߰���
SWINDOW_DEGREE g_pWindowDegreeList[] =
{
//	{STRMSG_WINDOW_DEGREE_1024x768_LOW,		1024, 768, 0},
//	{STRMSG_WINDOW_DEGREE_1024x768_MEDIUM,	1024, 768, 1},
	{STRMSG_WINDOW_DEGREE_1024x768_HIGH,	1024, 768, 2},

//	{STRMSG_WINDOW_DEGREE_1280x720_LOW,	1280, 720, 0},
//	{STRMSG_WINDOW_DEGREE_1280x720_MEDIUM,	1280, 720, 1},
	{STRMSG_WINDOW_DEGREE_1280x720_HIGH,	1280, 720, 2},
	
//	{STRMSG_WINDOW_DEGREE_W1280x800_LOW,	1280, 800, 0},
//	{STRMSG_WINDOW_DEGREE_W1280x800_MEDIUM,	1280, 800, 1},
	{STRMSG_WINDOW_DEGREE_1280x800_HIGH,	1280, 800, 2},
	
//	{STRMSG_WINDOW_DEGREE_1280x960_LOW,		1280, 960, 0},
//	{STRMSG_WINDOW_DEGREE_1280x960_MEDIUM,	1280, 960, 1},
	{STRMSG_WINDOW_DEGREE_1280x960_HIGH,	1280, 960, 2},
	
//	{STRMSG_WINDOW_DEGREE_1280x1024_LOW,	1280, 1024, 0},
//	{STRMSG_WINDOW_DEGREE_1280x1024_MEDIUM,	1280, 1024, 1},
	{STRMSG_WINDOW_DEGREE_1280x1024_HIGH,	1280, 1024, 2},
	
	// 2008-02-11 by cmkwon, �ػ� �߰�(1440x900) - 
//	{STRMSG_WINDOW_DEGREE_1440x900_LOW,		1440, 900, 0},
//	{STRMSG_WINDOW_DEGREE_1440x900_MEDIUM,	1440, 900, 1},
	{STRMSG_WINDOW_DEGREE_1440x900_HIGH,	1440, 900, 2},

//	{STRMSG_WINDOW_DEGREE_1600x900_LOW,	1600, 900, 0},
//	{STRMSG_WINDOW_DEGREE_1600x900_MEDIUM,	1600, 900, 1},
	{STRMSG_WINDOW_DEGREE_1600x900_HIGH,	1600, 900, 2},
	
//	{STRMSG_WINDOW_DEGREE_1600x1200_LOW,	1600, 1200, 0},
//	{STRMSG_WINDOW_DEGREE_1600x1200_MEDIUM,	1600, 1200, 1},
	{STRMSG_WINDOW_DEGREE_1600x1200_HIGH,	1600, 1200, 2},

//	{STRMSG_WINDOW_DEGREE_1680x1050_LOW		,	1680, 1050, 0},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
//	{STRMSG_WINDOW_DEGREE_1680x1050_MEDIUM	,	1680, 1050, 1},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1680x1050_HIGH	,	1680, 1050, 2},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 

//	{STRMSG_WINDOW_DEGREE_1920x1080_LOW		,	1920, 1080, 0},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
//	{STRMSG_WINDOW_DEGREE_1920x1080_MEDIUM	,	1920, 1080, 1},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1920x1080_HIGH	,	1920, 1080, 2},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 

//	{STRMSG_WINDOW_DEGREE_1920x1200_LOW		,	1920, 1200, 0},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
//	{STRMSG_WINDOW_DEGREE_1920x1200_MEDIUM	,	1920, 1200, 1},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_1920x1200_HIGH	,	1920, 1200, 2},		// 2009-10-16 by cmkwon, ���� �ػ� �߰�(1680x1050,1920x1080,1920x1200) - 
	{STRMSG_WINDOW_DEGREE_2560x1440_HIGH	,	2560, 1440, 2 },
	{STRMSG_WINDOW_DEGREE_2560x1080_HIGH	,	2560, 1080, 2 },

//	{STRMSG_WINDOW_DEGREE_3440x1440_LOW		,	3440, 1440, 0 },		
//	{STRMSG_WINDOW_DEGREE_3440x1440_MEDIUM	,	3440, 1440, 1 },		
	{STRMSG_WINDOW_DEGREE_3440x1440_HIGH	,	3440, 1440, 2 },		

	{STRMSG_WINDOW_DEGREE_3840x2160_HIGH	,	3840, 2160, 2 },
	{STRMSG_WINDOW_DEGREE_5120x2160_HIGH	,	5120, 2160, 2 },

	{NULL, 0, 0, 0}		// 2007-12-28 by cmkwon, ���� �����ϱ� ����
};



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// 2008-12-17 by ckPark ���þ� ����
// ���þƴ� ������ ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	#define ICON_IMAGE_ID		NULL
#else
	#define ICON_IMAGE_ID		IDB_ICON_VTC
#endif
// end 2008-12-17 by ckPark ���þ� ����

/////////////////////////////////////////////////////////////////////////////
// CAtumLauncherDlg dialog
// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - ���� ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){   return 0;}
CAtumLauncherDlg::CAtumLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAtumLauncherDlg::IDD, pParent), m_ctrlServerList(IDB_SERVERUSER_VTC, IDB_LISTBG_VTC, ICON_IMAGE_ID)
{
	//{{AFX_DATA_INIT(CAtumLauncherDlg)
	m_nServer = -1;
	m_szAccountName = _T("");
	m_szPassword = _T("");
	m_staticNumFileCtrl = _T("");
	m_nWindowDegree = 0;
	m_ctlbWindowMode = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pUpdateWinsocket = 0;
	m_nOldSel = 0;
//	m_pFieldWinsocket = 0;
	m_bControlEnabled = TRUE;

	m_StaticBrushBlack.CreateSolidBrush(RGB(0, 0, 0));
	m_StaticBrushGray.CreateSolidBrush(RGB(23, 23, 23));
	m_ListBrushGray.CreateSolidBrush(RGB(212, 208, 200));
	
	

	// 2008-12-17 by ckPark ���þ� ����
	// ���þƾƴ� ����� �������� �Ѵ�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	m_listBrush.CreateStockObject(NULL_BRUSH);
#else
	m_listBrush.CreateSolidBrush(RGB(29,29,40));
#endif
	// end 2008-12-17 by ckPark ���þ� ����




	m_progressBk.CreateSolidBrush(RGB(79,79,79));	
	m_progressBar.CreateSolidBrush(RGB(99, 123, 246));	

	m_pUpdateFTPManager	= NULL;
	m_pHost = NULL;
	m_pHttpManager		= NULL;				// 2007-01-08 by cmkwon
	SetFTPUpdateState(UPDATE_STATE_INIT);


	strcpy(m_szLocalIP, "127.0.0.1");

	m_nBirthYear		= 0;				// 2007-06-05 by cmkwon

	///////////////////////////////////////////////////////////////////////////////
	// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 
	m_nMaxNetworkCheckCount		= 5;
	m_nCurNetworkCheckCount		= -1;
	m_dwNetworkCheckSendTick	= 0;
	m_dwSumPacketTickGap		= 0;

	///////////////////////////////////////////////////////////////////////////////
	// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� - �ʱ�ȭ ��ġ ����
	m_Cur_Percent				= 0;
	m_SelectFlag				= FALSE;	
	m_bCancelFlag				= FALSE;
	m_bProcessingVersionUpdate	= FALSE;
	m_bShowPreServerIPDlg		= TRUE;

	// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
	m_pScreenKeyboardDlg			= NULL;
	m_pInputEditFromScreenKeyboard	= NULL;
	m_bHideScreenKeyboardByScreenKeyboardWindow	= FALSE; // 2007-09-18 by cmkwon, ȭ��Ű���� ���� - 

	m_vectServerGroupList.clear();		// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - 

	m_bGuardAgreementReg		= FALSE;	// 2009-08-31 by cmkwon, Gameforge4D ���Ӱ��� ����â ���� - 
}

void CAtumLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAtumLauncherDlg)
	
	
	// 2008-12-17 by ckPark ���þ� ����
	// ���þ� ���� ��Ʈ�ѵ�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	DDX_Control(pDX, IDC_COMBO_WINDOW_DEGREE_LAUNCHER, m_ctrlComboWindowDegree);
	DDX_Control(pDX, IDC_CHECK_WINDOWS_MODE, m_ctrlCheckWindowMode);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrlEditPassword);
#endif
	// end 2008-12-17 by ckPark ���þ� ����



	DDX_Control(pDX, IDC_CHECK_REMEMBER_ID, m_ctlBtnRememberID);
	DDX_Control(pDX, IDC_COMBO_SERVER_LIST, m_comboServerList);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_ctrlEditAccount);
	DDX_Control(pDX, IDC_LIST, m_ctrlServerList);					// 2006-05-02 by ispark
	DDX_Control(pDX, IDC_PROGRESS1, m_progressCtrl);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_szAccountName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_szPassword);
	DDV_MaxChars(pDX, m_szPassword, 14);
	DDX_Text(pDX, IDC_DOWNLOAD_FILENUM, m_staticNumFileCtrl);
	DDX_CBIndex(pDX, IDC_COMBO_WINDOW_DEGREE_LAUNCHER, m_nWindowDegree);
	DDX_Check(pDX, IDC_CHECK_WINDOWS_MODE, m_ctlbWindowMode);
	DDX_Control(pDX, IDGO, m_KbcGO);
	DDX_Control(pDX, IDJOIN, m_kbcBtnJoin);
	DDX_Control(pDX, IDC_BTN_HOMEPAGE, m_bmpBtnHomepage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAtumLauncherDlg, CDialog)
	//{{AFX_MSG_MAP(CAtumLauncherDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDJOIN, OnJoin)
	ON_BN_CLICKED(IDSECRET, OnSecret)
	ON_BN_CLICKED(IDEND, OnEnd)
	ON_BN_CLICKED(IDDECA, OnDeca)
	ON_BN_CLICKED(IDBATTAL, OnBattal)
	ON_BN_CLICKED(IDSHARIN, OnSharin)
	ON_BN_CLICKED(IDPHILON, OnPhilon)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDCAN, OnCan)
	ON_BN_CLICKED(IDMIN, OnMin)
	ON_EN_SETFOCUS(IDC_EDIT_ACCOUNT, OnSetfocusEditAccount)
	ON_EN_SETFOCUS(IDC_EDIT_PASSWORD, OnSetfocusEditPassword)
	ON_BN_CLICKED(IDC_BTN_VIEW_SCREEN_KEYBOARD, OnBtnViewScreenKeyboard)
	ON_BN_CLICKED(IDC_BTN_HOMEPAGE, OnBtnHomepage)
	ON_BN_CLICKED(IDGO, OnOk)
	ON_BN_CLICKED(IDC_CHECK_WINDOWS_MODE, OnCheckWindowsMode)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PACKET_NOTIFY, OnSocketNotify)
	ON_MESSAGE(WM_ASYNC_EVENT, OnAsyncSocketMessage)
	ON_MESSAGE(WM_DOWNLOAD_GAMEFILES_DONE, OnDownLoadGamefilesDone)

	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_ERROR, OnUpdateFileDownloadError)
	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_INIT, OnUpdateFileDownloadInit)
	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_PROGRESS, OnUpdateFileDownloadProgress)
	ON_MESSAGE(WM_UPDATEFILE_DOWNLOAD_OK, OnUpdateFileDownloadOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAtumLauncherDlg message handlers


BOOL CAtumLauncherDlg::ReadNoticeFile()
{
	char	szLine[10000];
	CString strTemp;

	m_NoticeEdit = "";

	FILE		*fp;
#ifdef _ATUM_DEVELOP
	fp = fopen(m_szExecutePathReg + NOTICE_FILE_NAME, "r");
#else
	fp = fopen(NOTICE_FILE_NAME, "r");
#endif

	if (fp == NULL)
	{
		//szLine[0] = '\0';
		//strcpy(temp, m_NoticeEdit);
		//m_NoticeEdit.Format("%s%s",temp, szLine);
	}
	else
	{
		while(!feof(fp))
		{
			memset(szLine, 0x00, sizeof(szLine));
			if(fgets(szLine, 10000, fp)==NULL)
			{
				break;
			}

			szLine[strlen(szLine)-1] = 0;
			strTemp = m_NoticeEdit;
			m_NoticeEdit.Format("%s\r\n%s", strTemp, szLine);
		}
		fclose(fp);
	}

	// 2007-09-07 by cmkwon, ������� �ʴ� ���̹Ƿ� ��Ʈ���� ������
	//GetDlgItem(IDC_NOTICE)->SetWindowText(m_NoticeEdit);
	return TRUE;
}

// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� - �ּ�ó����
//#define IMAGE_GEAR_X_SIZE						580
//#define IMAGE_GEAR_Y_SIZE						558
//
//#define IMAGE_SERVERLIST_X_SIZE					653
//#define IMAGE_SERVERLIST_Y_SIZE					260
//
//#define IMAGE_USECLASS_X_SIZE					85
//#define IMAGE_USECLASS_Y_SIZE					85
//
//#define IMAGE_UPDATEBAR_X_SIZE					512
//#define IMAGE_UPDATEBAR_Y_SIZE					50
//
//#define IMAGE_GO_BUTTON_X_SIZE					125
//#define IMAGE_GO_BUTTON_Y_SIZE					23
//
//#define IMAGE_GO_BUTTON_X_SIZE_S2				190		// 2006-10-02 by cmkwon
//#define IMAGE_GO_BUTTON_Y_SIZE_S2				73		// 2006-10-02 by cmkwon
//
//#define IMAGE_JOIN_BUTTON_X_SIZE				125
//#define IMAGE_JOIN_BUTTON_Y_SIZE				23
//
//#define IMAGE_CENTERBAR_X_SIZE					794
//#define IMAGE_CENTERBAR_Y_SIZE					107
//
//#define IMAGE_TITLE_X_SIZE						794
//#define IMAGE_TITLE_Y_SIZE						24
//
/////////////////////////////////////////////////////////////////////////////////
//// 2007-03-13 by cmkwon, This is GameStart BTN position of China
//#define DEF_GO_L_CHN							662			// 2006-10-02 by cmkwon
//#define DEF_GO_T_CHN							492			// 2006-10-02 by cmkwon
//#define IMAGE_GO_BUTTON_X_SIZE_CHN				124			// 2007-03-13 by cmkwon
//#define IMAGE_GO_BUTTON_Y_SIZE_CHN				23			// 2007-03-13 by cmkwon
//
//// 7/13/2006 by dgwoo CTRL RECT
//#ifndef _GLOBAL_ENG_SERVER			// 2006-09-07 by cmkwon, ����(#ifdef _VTC_VIET_SERVER --> #ifndef _GLOBAL_ENG_SERVER)
//	#define DEF_HOST_L			17
//	#define DEF_HOST_T			58
//	#define	DEF_HOST_R			563
//	#define DEF_HOST_B			540
//	#define DEF_SCREEN_X		800
//	#define DEF_SCREEN_Y		624
//	#define DEF_BG_L			0
//	#define DEF_BG_T			24	
//	#define DEF_DEGREE_L		591
//	#define DEF_DEGREE_T		553
//	#define DEF_DEGREE_R		195
//	#define DEF_DEGREE_B		20
//	#define DEF_ACCOUNT_L		666	
//	#define DEF_ACCOUNT_T		440
//	#define DEF_ACCOUNT_R		117
//	#define DEF_ACCOUNT_B		15
//	#define DEF_PASSWORD_L		666
//	#define DEF_PASSWORD_T		463
//	#define	DEF_SERVERLIST_L	598
//	#define	DEF_SERVERLIST_T	154
//	#define	DEF_SERVERLIST_R	176
//	#define	DEF_SERVERLIST_B	250
//	#define DEF_GO_L			676
//	#define DEF_GO_T			492
//	#define DEF_GO_R			125
//	#define DEF_GO_B			23
//	#define DEF_FILEVERSION_L	90
//	#define DEF_FILEVERSION_T	579
//	#define DEF_FILEVERSION_R	100
//	#define DEF_FILEVERSION_B	13
//	#define DEF_FILEINFO_L		190
//	#define DEF_FILEINFO_R		290
//
//	#define DEF_SCREENSIZE_FILEINFO_MINUS		24
//
//	#define DEF_ACCOUNT_L_S2	666						// 2006-10-02 by cmkwon
//	#define DEF_ACCOUNT_T_S2	518						// 2006-10-02 by cmkwon
//	#define DEF_ACCOUNT_R_S2	117						// 2006-10-02 by cmkwon
//	#define DEF_ACCOUNT_B_S2	15						// 2006-10-02 by cmkwon
//	#define DEF_PASSWORD_L_S2	666						// 2006-10-02 by cmkwon
//	#define DEF_PASSWORD_T_S2	534						// 2006-10-02 by cmkwon
//	#define DEF_GO_L_S2			592						// 2006-10-02 by cmkwon
//	#define DEF_GO_T_S2			442						// 2006-10-02 by cmkwon
//
//#else
//	#define DEF_HOST_L			0
//	#define DEF_HOST_T			24
//	#define	DEF_HOST_R			812
//	#define DEF_HOST_B			493
//	#define DEF_SCREEN_X		800
//	#define DEF_SCREEN_Y		600
//	#define DEF_BG_L			0
//	#define DEF_BG_T			493
//	#define DEF_DEGREE_L		652
//	#define DEF_DEGREE_T		526
//	#define DEF_DEGREE_R		131
//	#define DEF_DEGREE_B		100
//	#define DEF_ACCOUNT_L		332		
//	#define DEF_ACCOUNT_T		501
//	#define DEF_ACCOUNT_R		124
//	#define DEF_ACCOUNT_B		14
//	#define DEF_PASSWORD_L		504	
//	#define	DEF_PASSWORD_T		501
//	#define	DEF_SERVERLIST_L	76
//	#define	DEF_SERVERLIST_T	526
//	#define	DEF_SERVERLIST_R	230
//	#define	DEF_SERVERLIST_B	100	
//	#define DEF_GO_L			654
//	#define DEF_GO_T			496
//	#define DEF_GO_R			125
//	#define DEF_GO_B			23
//	#define DEF_FILEVERSION_L	27
//	#define DEF_FILEVERSION_T	561
//	#define DEF_FILEVERSION_R	90
//	#define DEF_FILEVERSION_B	13
//	#define DEF_FILEINFO_L		119
//	#define DEF_FILEINFO_R		250
//	#define DEF_SCREENSIZE_FILEINFO_MINUS		45
//#endif

// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [����-�ʼ�] ��ó Interface ��ġ ���� �ϱ�

///////////////////////////////////////////////////////////////////////////////
// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� -
#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)
	#define EXE2_LAUNCHER_BG_SIZE_X					800
	#define EXE2_LAUNCHER_BG_SIZE_Y					624
	
	#define EXE2_BG_TITLE_BAR_SIZE_X				EXE2_LAUNCHER_BG_SIZE_X	// Ÿ��Ʋ�� �̹��� Width
	#define EXE2_BG_TITLE_BAR_SIZE_Y				27						// Ÿ��Ʋ�� Height

	#define EXE2_BG_BACKGROUND_IMAGE_SIZE_X			EXE2_LAUNCHER_BG_SIZE_X									// ��� �̹��� Width
	#define EXE2_BG_BACKGROUND_IMAGE_SIZE_Y			(EXE2_LAUNCHER_BG_SIZE_Y - EXE2_BG_TITLE_BAR_SIZE_Y)	// ��� �̹��� Height

	#define EXE2_BG_WEBCONTROL_POS_X				235		// �������� ��Ʈ�� ��ġ X
	#define EXE2_BG_WEBCONTROL_POS_Y				73		// �������� ��Ʈ�� ��ġ Y
	#define EXE2_BG_WEBCONTROL_WIDTH				544		// �������� ��Ʈ�� Width
	#define EXE2_BG_WEBCONTROL_HEIGHT				480		// �������� ��Ʈ�� Height

	#define EXE2_BG_RESOLUTION_COMBOBOX_POS_X		17		// �ػ� ���� Combo Box ��ġ X
	#define EXE2_BG_RESOLUTION_COMBOBOX_POS_Y		529		// �ػ� ���� Combo Box ��ġ Y
	#define EXE2_BG_RESOLUTION_COMBOBOX_WIDTH		194		// �ػ� ���� Combo Box Width
	#define EXE2_BG_RESOLUTION_COMBOBOX_HEIGHT		16		// �ػ� ���� Combo Box Height

	#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		118		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ X
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		512		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_WIDTH		13		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box Width
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_HEIGHT		13		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box Height

	#define EXE2_BG_ACCOUNTNAME_EDIT_POS_X			94		// AccountName Edit Box ��ġ X
	#define EXE2_BG_ACCOUNTNAME_EDIT_POS_Y			421		// AccountName Edit Box ��ġ Y
	#define EXE2_BG_ACCOUNTNAME_EDIT_WIDTH			121		// AccountName Edit Box Width
	#define EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT			16		// AccountName Edit Box Height

	#define EXE2_BG_PASSWORD_EDIT_POS_X				94		// Password Edit Box ��ġ X
	#define EXE2_BG_PASSWORD_EDIT_POS_Y				440		// Password Edit Box ��ġ Y
	#define EXE2_BG_PASSWORD_EDIT_WIDTH				121		// Password Edit Box Width
	#define EXE2_BG_PASSWORD_EDIT_HEIGHT			16		// Password Edit Box Height

	#define EXE2_BG_SERVERLIST_BOX_POS_X			42		// ServerList Box ��ġ X
	#define EXE2_BG_SERVERLIST_BOX_POS_Y			166		// ServerList Box ��ġ Y
	#define EXE2_BG_SERVERLIST_BOX_WIDTH			173		// ServerList Box Width
	#define EXE2_BG_SERVERLIST_BOX_HEIGHT			239		// ServerList Box Height

	#define EXE2_BG_SERVERLIST_ITEM_BG_WIDTH		174		// ServerList Item Background Width
	#define EXE2_BG_SERVERLIST_ITEM_BG_HEIGHT		25		// ServerList Item Background Height

	#define EXE2_BG_SERVERLIST_ITEM_ICON_POS_X		0		// ServerList Item Icon ��ġ X
	#define EXE2_BG_SERVERLIST_ITEM_ICON_POS_Y		0		// ServerList Item Icon ��ġ Y
	#define EXE2_BG_SERVERLIST_ITEM_ICON_WIDTH		26		// ServerList Item Icon Width
	#define EXE2_BG_SERVERLIST_ITEM_ICON_HEIGHT		26		// ServerList Item Icon Height

	#define EXE2_BG_MINIMIZED_BTN_POS_X				752		// Minimized Button ��ġ X
	#define EXE2_BG_MINIMIZED_BTN_POS_Y				0		// Minimized Button ��ġ Y
	#define EXE2_BG_MINIMIZED_BTN_WIDTH				21		// Minimized Button Width
	#define EXE2_BG_MINIMIZED_BTN_HEIGHT			27		// Minimized Button Height
	#define EXE2_BG_CANCEL_BTN_POS_X				772		// Cancel Button ��ġ X
	#define EXE2_BG_CANCEL_BTN_POS_Y				0		// Cancel Button ��ġ Y
	#define EXE2_BG_CANCEL_BTN_WIDTH				21		// Cancel Button Width
	#define EXE2_BG_CANCEL_BTN_HEIGHT				27		// Cancel Button Height

	#define EXE2_BG_GAMESTART_BTN_POS_X				110		// GameStart Button ��ġ X
	#define EXE2_BG_GAMESTART_BTN_POS_Y				461		// GameStart Button ��ġ Y
	#define EXE2_BG_GAMESTART_BTN_WIDTH				106		// GameStart Button Width
	#define EXE2_BG_GAMESTART_BTN_HEIGHT			28		// GameStart Button Height

	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_X		17		// Update Progress Bar ��ġ X
	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_Y		607		// Update Progress Bar ��ġ Y
	#define EXE2_BG_UPDATE_PROGRESS_BAR_WIDTH		375		// Update Progress Bar Width
	#define EXE2_BG_UPDATE_PROGRESS_BAR_HEIGHT		5		// Update Progress Bar Height

	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X		19		// Download file info static control ��ġ X
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y		575		// Download file info static control ��ġ Y
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH		200		// Download file info static control Width
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT		13		// Download file info static control Height
	#define EXE2_BG_DOWNLOAD_FILE_FONT_SIZE			16		// Download file info static control font Size
	#define EXE2_BG_DOWNLOAD_FILE_FONT_WEIGHT		FW_BOLD	// Download file info static control font ����
	#define EXE2_BG_DOWNLOAD_FILE_FONT_COLOR		RGB(255,255,255)	// Download file info static control font Color

	#define EXE2_BG_UPDATE_INFO_STATIC_POS_X		19		// Update info static control ��ġ X
	#define EXE2_BG_UPDATE_INFO_STATIC_POS_Y		590		// Update info static control ��ġ Y
	#define EXE2_BG_UPDATE_INFO_STATIC_WIDTH		290		// Update info static control Width
	#define EXE2_BG_UPDATE_INFO_STATIC_HEIGHT		13		// Update info static control Height
	#define EXE2_BG_UPDATE_INFO_FONT_SIZE			16		// Update info static control font Size
	#define EXE2_BG_UPDATE_INFO_FONT_WEIGHT			FW_NORMAL	// Update info static control font ����
	#define EXE2_BG_UPDATE_INFO_FONT_COLOR			RGB(255,255,255)	// Update info static control font Color

	// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - üũ�ڽ� ��ġ
	#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		666		// Remember ID CheckBox ��ġ X
	#define EXE2_BG_REMEMBERID_CHECKBOX_POS_Y		480		// Remember ID CheckBox ��ġ Y
	#define EXE2_BG_REMEMBERID_CHECKBOX_WIDTH		13		// Remember ID CheckBox Width
	#define EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT		13		// Remember ID CheckBox Height

#else	// #if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)




// 2008-12-23 by ckPark �Ϻ� ����
// 	#define EXE2_LAUNCHER_BG_SIZE_X					796
// 	#define EXE2_LAUNCHER_BG_SIZE_Y					618
// �Ϻ� ��׶��� ��Ʈ�� ��ġ
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)

	#define EXE2_LAUNCHER_BG_SIZE_X					650
	#define EXE2_LAUNCHER_BG_SIZE_Y					70

#else

	#define EXE2_LAUNCHER_BG_SIZE_X					796
	#define EXE2_LAUNCHER_BG_SIZE_Y					618

#endif
// end 2008-12-23 by ckPark �Ϻ� ����




	#define EXE2_BG_TITLE_BAR_SIZE_X				EXE2_LAUNCHER_BG_SIZE_X	// Ÿ��Ʋ�� �̹��� Width
	#define EXE2_BG_TITLE_BAR_SIZE_Y				24						// Ÿ��Ʋ�� Height

	#define EXE2_BG_BACKGROUND_IMAGE_SIZE_X			EXE2_LAUNCHER_BG_SIZE_X									// ��� �̹��� Width
	#define EXE2_BG_BACKGROUND_IMAGE_SIZE_Y			(EXE2_LAUNCHER_BG_SIZE_Y - EXE2_BG_TITLE_BAR_SIZE_Y)	// ��� �̹��� Height

	#define EXE2_BG_WEBCONTROL_POS_X				17		// �������� ��Ʈ�� ��ġ X
	#define EXE2_BG_WEBCONTROL_POS_Y				58		// �������� ��Ʈ�� ��ġ Y
	#define EXE2_BG_WEBCONTROL_WIDTH				546		// �������� ��Ʈ�� Width
	#define EXE2_BG_WEBCONTROL_HEIGHT				482		// �������� ��Ʈ�� Height
	


// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	#define EXE2_BG_RESOLUTION_COMBOBOX_POS_X		693		// �ػ� ���� Combo Box ��ġ X
	#define EXE2_BG_RESOLUTION_COMBOBOX_POS_Y		530		// �ػ� ���� Combo Box ��ġ Y
	#define EXE2_BG_RESOLUTION_COMBOBOX_WIDTH		95		// �ػ� ���� Combo Box Width
	#define EXE2_BG_RESOLUTION_COMBOBOX_HEIGHT		16		// �ػ� ���� Combo Box Height
#else
	#define EXE2_BG_RESOLUTION_COMBOBOX_POS_X		591		// �ػ� ���� Combo Box ��ġ X
	#define EXE2_BG_RESOLUTION_COMBOBOX_POS_Y		553		// �ػ� ���� Combo Box ��ġ Y
	#define EXE2_BG_RESOLUTION_COMBOBOX_WIDTH		195		// �ػ� ���� Combo Box Width
	#define EXE2_BG_RESOLUTION_COMBOBOX_HEIGHT		20		// �ػ� ���� Combo Box Height
#endif
// end 2008-12-17 by ckPark ���þ� ����



	#if defined(SERVICE_TYPE_KOREAN_SERVER_1)
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		720		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ X
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		531		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
// 2008-01-15 by cmkwon, 2000_Yedang-Global_Kor ������Ʈ �߰� - �Ʒ��� ���� ����
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2)
// 2008-04-25 by cmkwon, Gameforge4D_Deu �߰��� - 
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2)
// 2008-05-02 by cmkwon, WinnerOnline_Tha �߰��ϱ� - �Ʒ��� ���� ����
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)
// 2008-05-29 by cmkwon, ���� ���� �߰�(Innova_Rus ���þƾ� �߰�) - �Ʒ��� ���� ����
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1)
// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - �Ʒ��� ���� 3�� ���� �߰�
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1)
// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1)
// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
#elif defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		685		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ X
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		531		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
	#elif defined(SERVICE_TYPE_CHINESE_SERVER_1) || defined(SERVICE_TYPE_TAIWANESE_SERVER_1)
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		706		// 2008-01-17 by cmkwon, Exe2: Yetime_Chn �������� ��� üũ�ڽ� ��ġ ���� - 
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		531		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
	#elif defined(SERVICE_TYPE_RUSSIAN_SERVER_1)


// 2008-12-17 by ckPark ���þ� ����
// 		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		648		// 2008-01-17 by cmkwon, Exe2: Yetime_Chn �������� ��� üũ�ڽ� ��ġ ���� - 
// 		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		516		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		600		// 2008-01-17 by cmkwon, Exe2: Yetime_Chn �������� ��� üũ�ڽ� ��ġ ���� - 
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		557		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
// end 2008-12-17 by ckPark ���þ� ����



	#else
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X		720		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ X
		#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		531		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
	#endif
	// 2008-06-20 by cmkwon, Innova_Rus ��û���� ��ġ�� Yǥ�� �ٸ��� ������ ���� ���� �߰���
	//#define EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y		531		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ Y
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_WIDTH		13		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box Width
	#define EXE2_BG_WINDOWSMODE_CHECKBOX_HEIGHT		13		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box Height

	#if defined(SERVICE_TYPE_KOREAN_SERVER_2)
		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_X			666		// AccountName Edit Box ��ġ X
		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_Y			518		// AccountName Edit Box ��ġ Y
		#define EXE2_BG_ACCOUNTNAME_EDIT_WIDTH			117		// AccountName Edit Box Width
		#define EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT			15		// AccountName Edit Box Height

		#define EXE2_BG_PASSWORD_EDIT_POS_X				666		// Password Edit Box ��ġ X
		#define EXE2_BG_PASSWORD_EDIT_POS_Y				534		// Password Edit Box ��ġ Y
		#define EXE2_BG_PASSWORD_EDIT_WIDTH				117		// Password Edit Box Width
		#define EXE2_BG_PASSWORD_EDIT_HEIGHT			15		// Password Edit Box Height	
	//#elif defined(SERVICE_TYPE_THAI_SERVER_1)	// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
	#elif defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)	
		// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_X			630		// AccountName Edit Box ��ġ X
		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_Y			440		// AccountName Edit Box ��ġ Y
		#define EXE2_BG_ACCOUNTNAME_EDIT_WIDTH			117		// AccountName Edit Box Width
		#define EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT			15		// AccountName Edit Box Height

		#define EXE2_BG_PASSWORD_EDIT_POS_X				630		// Password Edit Box ��ġ X
		#define EXE2_BG_PASSWORD_EDIT_POS_Y				463		// Password Edit Box ��ġ Y
		#define EXE2_BG_PASSWORD_EDIT_WIDTH				117		// Password Edit Box Width
		#define EXE2_BG_PASSWORD_EDIT_HEIGHT			15		// Password Edit Box Height
	#else
		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_X			666		// AccountName Edit Box ��ġ X
		#define EXE2_BG_ACCOUNTNAME_EDIT_POS_Y			440		// AccountName Edit Box ��ġ Y
		#define EXE2_BG_ACCOUNTNAME_EDIT_WIDTH			117		// AccountName Edit Box Width
		#define EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT			15		// AccountName Edit Box Height

		#define EXE2_BG_PASSWORD_EDIT_POS_X				666		// Password Edit Box ��ġ X
		#define EXE2_BG_PASSWORD_EDIT_POS_Y				463		// Password Edit Box ��ġ Y
		#define EXE2_BG_PASSWORD_EDIT_WIDTH				117		// Password Edit Box Width
		#define EXE2_BG_PASSWORD_EDIT_HEIGHT			15		// Password Edit Box Height
	#endif

	#define EXE2_BG_SERVERLIST_BOX_POS_X			598		// ServerList Box ��ġ X
	#define EXE2_BG_SERVERLIST_BOX_POS_Y			154		// ServerList Box ��ġ Y
	#define EXE2_BG_SERVERLIST_BOX_WIDTH			176		// ServerList Box Width
	#define EXE2_BG_SERVERLIST_BOX_HEIGHT			250		// ServerList Box Height

	#define EXE2_BG_SERVERLIST_ITEM_BG_WIDTH		177		// ServerList Item Background Width
	#define EXE2_BG_SERVERLIST_ITEM_BG_HEIGHT		25		// ServerList Item Background Height

	#define EXE2_BG_SERVERLIST_ITEM_ICON_POS_X		3		// ServerList Item Icon ��ġ X
	#define EXE2_BG_SERVERLIST_ITEM_ICON_POS_Y		8		// ServerList Item Icon ��ġ Y
	#define EXE2_BG_SERVERLIST_ITEM_ICON_WIDTH		19		// ServerList Item Icon Width
	#define EXE2_BG_SERVERLIST_ITEM_ICON_HEIGHT		10		// ServerList Item Icon Height




	// 2008-12-17 by ckPark ���þ� ���� - �Ʒ��� ���� ���þƸ� �ٸ� ��ǥ�� ���� ��.
	// 	#define EXE2_BG_MINIMIZED_BTN_POS_X				758		// Minimized Button ��ġ X
	// 	#define EXE2_BG_MINIMIZED_BTN_POS_Y				0		// Minimized Button ��ġ Y
	// 	#define EXE2_BG_MINIMIZED_BTN_WIDTH				16		// Minimized Button Width
	// 	#define EXE2_BG_MINIMIZED_BTN_HEIGHT			20		// Minimized Button Height
	// 	#define EXE2_BG_CANCEL_BTN_POS_X				778		// Cancel Button ��ġ X
	// 	#define EXE2_BG_CANCEL_BTN_POS_Y				0		// Cancel Button ��ġ Y
	// 	#define EXE2_BG_CANCEL_BTN_WIDTH				16		// Cancel Button Width
	// 	#define EXE2_BG_CANCEL_BTN_HEIGHT				20		// Cancel Button Height
	
	#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		#define EXE2_BG_MINIMIZED_BTN_POS_X				748		// Minimized Button ��ġ X
		#define EXE2_BG_MINIMIZED_BTN_POS_Y				0		// Minimized Button ��ġ Y
		#define EXE2_BG_MINIMIZED_BTN_WIDTH				21		// Minimized Button Width
		#define EXE2_BG_MINIMIZED_BTN_HEIGHT			21		// Minimized Button Height
		#define EXE2_BG_CANCEL_BTN_POS_X				773		// Cancel Button ��ġ X
		#define EXE2_BG_CANCEL_BTN_POS_Y				0		// Cancel Button ��ġ Y
		#define EXE2_BG_CANCEL_BTN_WIDTH				21		// Cancel Button Width
		#define EXE2_BG_CANCEL_BTN_HEIGHT				21		// Cancel Button Height
	#else
		#define EXE2_BG_MINIMIZED_BTN_POS_X				758		// Minimized Button ��ġ X
		#define EXE2_BG_MINIMIZED_BTN_POS_Y				0		// Minimized Button ��ġ Y
		#define EXE2_BG_MINIMIZED_BTN_WIDTH				16		// Minimized Button Width
		#define EXE2_BG_MINIMIZED_BTN_HEIGHT			20		// Minimized Button Height
		#define EXE2_BG_CANCEL_BTN_POS_X				778		// Cancel Button ��ġ X
		#define EXE2_BG_CANCEL_BTN_POS_Y				0		// Cancel Button ��ġ Y
		#define EXE2_BG_CANCEL_BTN_WIDTH				16		// Cancel Button Width
		#define EXE2_BG_CANCEL_BTN_HEIGHT				20		// Cancel Button Height
	#endif
		// end 2008-12-17 by ckPark ���þ� ����




	#if defined(SERVICE_TYPE_KOREAN_SERVER_2)
		#define EXE2_BG_GAMESTART_BTN_POS_X				592		// GameStart Button ��ġ X
		#define EXE2_BG_GAMESTART_BTN_POS_Y				442		// GameStart Button ��ġ Y
		#define EXE2_BG_GAMESTART_BTN_WIDTH				190		// GameStart Button Width
		#define EXE2_BG_GAMESTART_BTN_HEIGHT			73		// GameStart Button Height
	#elif defined(SERVICE_TYPE_CHINESE_SERVER_1) || defined(SERVICE_TYPE_TAIWANESE_SERVER_1)
		#define EXE2_BG_GAMESTART_BTN_POS_X				662		// GameStart Button ��ġ X
		#define EXE2_BG_GAMESTART_BTN_POS_Y				492		// GameStart Button ��ġ Y
		#define EXE2_BG_GAMESTART_BTN_WIDTH				124		// GameStart Button Width
		#define EXE2_BG_GAMESTART_BTN_HEIGHT			23		// GameStart Button Height
	//#elif defined(SERVICE_TYPE_THAI_SERVER_1)	// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
	#elif defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
		// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
		#define EXE2_BG_GAMESTART_BTN_POS_X				628		// GameStart Button ��ġ X
		#define EXE2_BG_GAMESTART_BTN_POS_Y				505		// GameStart Button ��ġ Y
		#define EXE2_BG_GAMESTART_BTN_WIDTH				125		// GameStart Button Width
		#define EXE2_BG_GAMESTART_BTN_HEIGHT			23		// GameStart Button Height
	// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - �Ʒ��� ���� 3�� ���� �߰�
	//#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)
// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1)
// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  
//#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
		// 2008-10-20 by cmkwon, Gameforge4D(Engilsh, German)�� ���� ���� ����ϱ� ��� �߰� - �߰���
		#define EXE2_BG_GAMESTART_BTN_POS_X				676		// GameStart Button ��ġ X
		#define EXE2_BG_GAMESTART_BTN_POS_Y				502		// GameStart Button ��ġ Y
		#define EXE2_BG_GAMESTART_BTN_WIDTH				125		// GameStart Button Width
		#define EXE2_BG_GAMESTART_BTN_HEIGHT			23		// GameStart Button Height



	// 2008-12-17 by ckPark ���þ� ����
	#elif defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
		#define EXE2_BG_GAMESTART_BTN_POS_X				648		// GameStart Button ��ġ X
		#define EXE2_BG_GAMESTART_BTN_POS_Y				492		// GameStart Button ��ġ Y
		#define EXE2_BG_GAMESTART_BTN_WIDTH				125		// GameStart Button Width
		#define EXE2_BG_GAMESTART_BTN_HEIGHT			23		// GameStart Button Height
	// 2008-12-17 by ckPark ���þ� ����



	#else
		#define EXE2_BG_GAMESTART_BTN_POS_X				676		// GameStart Button ��ġ X
		#define EXE2_BG_GAMESTART_BTN_POS_Y				492		// GameStart Button ��ġ Y
		#define EXE2_BG_GAMESTART_BTN_WIDTH				125		// GameStart Button Width
		#define EXE2_BG_GAMESTART_BTN_HEIGHT			23		// GameStart Button Height
	#endif




// 2008-12-23 by ckPark �Ϻ� ����
#if !defined(SERVICE_TYPE_JAPANESE_SERVER_1)

	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_X		26		// Update Progress Bar ��ġ X
	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_Y		602		// Update Progress Bar ��ġ Y = (EXE2_LAUNCHER_BG_SIZE_Y - 23)
	#define EXE2_BG_UPDATE_PROGRESS_BAR_WIDTH		748		// Update Progress Bar Width = (EXE2_LAUNCHER_BG_SIZE_X - 2*EXE2_BG_UPDATE_PROGRESS_BAR_POS_X)
	#define EXE2_BG_UPDATE_PROGRESS_BAR_HEIGHT		7		// Update Progress Bar Height

	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X		90		// Download file info static control ��ġ X
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y		579		// Download file info static control ��ġ Y
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH		200		// Download file info static control Width
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT		13		// Download file info static control Height
	#define EXE2_BG_DOWNLOAD_FILE_FONT_SIZE			12		// Download file info static control font Size
	#define EXE2_BG_DOWNLOAD_FILE_FONT_WEIGHT		FW_NORMAL	// Download file info static control font ����

#else
	// �Ϻ� ���α׷�����, �ؽ�Ʈ ��ġ

	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_X		42		// Update Progress Bar ��ġ X
	#define EXE2_BG_UPDATE_PROGRESS_BAR_POS_Y		36		// Update Progress Bar ��ġ Y = (EXE2_LAUNCHER_BG_SIZE_Y - 23)
	#define EXE2_BG_UPDATE_PROGRESS_BAR_WIDTH		574		// Update Progress Bar Width = (EXE2_LAUNCHER_BG_SIZE_X - 2*EXE2_BG_UPDATE_PROGRESS_BAR_POS_X)
	#define EXE2_BG_UPDATE_PROGRESS_BAR_HEIGHT		16		// Update Progress Bar Height

	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X		63		// Download file info static control ��ġ X
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y		14		// Download file info static control ��ġ Y
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH		140		// Download file info static control Width
	#define EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT		13		// Download file info static control Height
	#define EXE2_BG_DOWNLOAD_FILE_FONT_SIZE			12		// Download file info static control font Size
	#define EXE2_BG_DOWNLOAD_FILE_FONT_WEIGHT		FW_NORMAL	// Download file info static control font ����

#endif

// end 2008-12-23 by ckPark �Ϻ� ����




// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	#define EXE2_BG_DOWNLOAD_FILE_FONT_COLOR		RGB(255, 255, 255)	// Download file info static control font Color
#else
	#define EXE2_BG_DOWNLOAD_FILE_FONT_COLOR		RGB(0,0,0)	// Download file info static control font Color
#endif
// end 2008-12-17 by ckPark ���þ� ����



// 2008-12-23 by ckPark �Ϻ� ����

#if !defined(SERVICE_TYPE_JAPANESE_SERVER_1)

	#define EXE2_BG_UPDATE_INFO_STATIC_POS_X		190		// Update info static control ��ġ X
	#define EXE2_BG_UPDATE_INFO_STATIC_POS_Y		579		// Update info static control ��ġ Y
	#define EXE2_BG_UPDATE_INFO_STATIC_WIDTH		290		// Update info static control Width
	#define EXE2_BG_UPDATE_INFO_STATIC_HEIGHT		13		// Update info static control Height
	#define EXE2_BG_UPDATE_INFO_FONT_SIZE			12		// Update info static control font Size
	#define EXE2_BG_UPDATE_INFO_FONT_WEIGHT			FW_NORMAL	// Update info static control font ����

#else

	// �Ϻ� ������Ʈ ���� ��ġ

	#define EXE2_BG_UPDATE_INFO_STATIC_POS_X		163		// Update info static control ��ġ X
	#define EXE2_BG_UPDATE_INFO_STATIC_POS_Y		14		// Update info static control ��ġ Y
	#define EXE2_BG_UPDATE_INFO_STATIC_WIDTH		422		// Update info static control Width
	#define EXE2_BG_UPDATE_INFO_STATIC_HEIGHT		13		// Update info static control Height
	#define EXE2_BG_UPDATE_INFO_FONT_SIZE			12		// Update info static control font Size
	#define EXE2_BG_UPDATE_INFO_FONT_WEIGHT			FW_NORMAL	// Update info static control font ����

#endif

// end 2008-12-23 by ckPark �Ϻ� ����



// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	#define EXE2_BG_UPDATE_INFO_FONT_COLOR			RGB(255, 255, 255)	// Update info static control font Color
#else
	#define EXE2_BG_UPDATE_INFO_FONT_COLOR			RGB(0,0,0)	// Update info static control font Color
#endif
// end 2008-12-17 by ckPark ���þ� ����



	// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - üũ�ڽ� ��ġ
	#if defined(SERVICE_TYPE_KOREAN_SERVER_1)
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		666		// Remember ID CheckBox ��ġ X
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_Y		480		// Remember ID CheckBox ��ġ Y
		#define EXE2_BG_REMEMBERID_CHECKBOX_WIDTH		13		// Remember ID CheckBox Width
		#define EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT		13		// Remember ID CheckBox Height
	// #elif defined(SERVICE_TYPE_THAI_SERVER_1)
	#elif defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		630		// Remember ID CheckBox ��ġ X
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_Y		486		// Remember ID CheckBox ��ġ Y
		#define EXE2_BG_REMEMBERID_CHECKBOX_WIDTH		13		// Remember ID CheckBox Width
		#define EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT		13		// Remember ID CheckBox Height
	// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - �Ʒ��� ���� 3�� ���� �߰�
	//#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)
// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//	#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1)
// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  
//elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
#elif defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
		// 2008-10-20 by cmkwon, Gameforge4D(Engilsh, German)�� ���� ���� ����ϱ� ��� �߰� - �߰���
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		666		// Remember ID CheckBox ��ġ X
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_Y		483		// Remember ID CheckBox ��ġ Y
		#define EXE2_BG_REMEMBERID_CHECKBOX_WIDTH		13		// Remember ID CheckBox Width
		#define EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT		13		// Remember ID CheckBox Height		
	#else
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_X		666		// Remember ID CheckBox ��ġ X
		#define EXE2_BG_REMEMBERID_CHECKBOX_POS_Y		480		// Remember ID CheckBox ��ġ Y
		#define EXE2_BG_REMEMBERID_CHECKBOX_WIDTH		13		// Remember ID CheckBox Width
		#define EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT		13		// Remember ID CheckBox Height
	#endif

#endif

BOOL CAtumLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2009-08-31 by cmkwon, Gameforge4D ���Ӱ��� ����â ���� - 
#if defined(_DEFINED_GAMEFORGE4D_)
	if(FALSE == this->m_bGuardAgreementReg)
	{
		CDlgGuardAgreement GuardDlg;
		if(IDOK != GuardDlg.DoModal())
		{
			OnOK();
			return FALSE;
		}
		this->m_bGuardAgreementReg	= TRUE;
		((CAtumLauncherApp*)AfxGetApp())->WriteProfile();
	}
#endif

#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)
	///////////////////////////////////////////////////////////////////////////////
	// 2007-09-10 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
	m_pScreenKeyboardDlg	= new CScreenKeyboardDlg(this);
	m_pScreenKeyboardDlg->Create(IDD_DLG_SCREEN_KEYBOARD, this);
	// 2007-09-18 by cmkwon, ȭ��Ű���� ���� - �н����� �Է½ÿ��� Ȱ��ȭ �ǵ��� �ϴ� �����
	//m_pScreenKeyboardDlg->ShowWindow(SW_SHOW);
	m_pScreenKeyboardDlg->ShowWindow(SW_HIDE);
#endif

	// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� - ��û�ñ��� ��ư�� �������� �ȴ´�
	//GetDlgItem(IDC_BTN_VIEW_SCREEN_KEYBOARD)->ShowWindow(SW_SHOW);		


	// �۾� ǥ���ٿ� ���α׷��� ǥ��
	AfxGetApp()->m_pMainWnd->SetWindowText(STRMSG_WINDOW_TEXT);
	// �۾� ǥ���ٿ� ������ ǥ��
	ModifyStyle(0,WS_SYSMENU);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	///////////////////////////////////////////////////////////////////////////
	// TODO: Add extra initialization here

	CWinSocket::SocketInit();		// Initialize winsock 2.0

	this->MoveWindow2Center();	// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� - ȭ�� �߾����� ��ġ
	RECT rtBG;
	this->GetClientRect(&rtBG);

	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� �ػ� ����Ʈ �ʱ�ȭ
	this->InitSupportedWindowResolutionList();		
	
	///////////////////////////////////////////////////////////////////////////////
	// 2007-05-07 by cmkwon, �ػ� ������ �� ���� ���� �����ϱ� ����
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER);
	if(pComboBox)
	{
		

		
		
		// 2008-12-17 by ckPark ���þ� ����
		// ���þ��� ���� ���� ��Ʈ�ѿ��� â��带 ������
		// �߰����� �Ӽ��� �������ش�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		this->InsertWindowDegreeList(pComboBox, m_ctrlCheckWindowMode.GetCheck());
		m_ctrlComboWindowDegree.SetBitMap(IDB_COMBOBOX);
		m_ctrlComboWindowDegree.SetTextColor(RGB(18, 236, 218));
		m_ctrlComboWindowDegree.SetBackColor(RGB(0, 0, 0));
#else
		this->InsertWindowDegreeList(pComboBox, m_ctlbWindowMode);
#endif
		// end 2008-12-17 by ckPark ���þ� ����




		int nIdx = this->FindWindowDegreeComboBoxIndex(pComboBox, (LPSTR)(LPCSTR)m_csWindowsResolutionReg);
		nIdx = max(0, nIdx);
		pComboBox->SetCurSel(nIdx);

// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - ���� ���� CAtumLauncherDlg::InsertWindowDegreeList() ���� ó��
//// 2007-07-24 by cmkwon, ��ó���� 800*600 �ػ� ���� - �޺��ڽ��� �߰����� �ʴ´�
////		pComboBox->AddString(STRMSG_WINDOW_DEGREE_800x600_LOW);
////		pComboBox->AddString(STRMSG_WINDOW_DEGREE_800x600_MEDIUM);	
////		pComboBox->AddString(STRMSG_WINDOW_DEGREE_800x600_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1024x768_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1024x768_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1024x768_HIGH);
//
//		// 2007-08-23 by cmkwon, Wide �ػ� 1280x720(16:9) �߰� - 
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x720_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x720_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x720_HIGH);
//
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x800_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x800_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x800_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x960_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x960_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x960_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x1024_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x1024_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x1024_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1600x900_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1600x900_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1600x900_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1600x1200_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1600x1200_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1600x1200_HIGH);
//
//		pComboBox->SetCurSel(max(0, m_nWindowDegreeReg-3));			// 2007-07-24 by cmkwon, ��ó���� 800*600 �ػ� ���� - ������Ʈ������ �������� �״�� ����Ѵ�.
	}
	
    m_fontServerGroupListBox.CreateFont(16, 0, 0, 0, SG_BOX_FONT_WEIGHT, 0, FALSE, FALSE, SG_BOX_FONT_CHARSET, OUT_DEFAULT_PRECIS,
							  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH , SG_BOX_FONT_FACENAME);    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
    GetDlgItem(IDC_LIST)->SetFont(&m_fontServerGroupListBox);

	
	m_bitmapBtnCancel.AutoLoad(IDCAN, this);
	m_bitmapBtnMin.AutoLoad(IDMIN, this);
// 2008-01-08 by cmkwon, Yedang-Global ������Ʈ�� �߰�
//#if defined(_GLOBAL_ENG_SERVER)			// 2006-09-07 by cmkwon, ����(#ifdef _VTC_VIET_SERVER --> #ifndef _GLOBAL_ENG_SERVER)
//	m_KbcGO.SetBmpButtonImage(IDB_GOBTN, RGB(0,0,255));
//#elif defined(_KOREA_SERVER_2)		// 2006-10-02 by cmkwon
#if defined(SERVICE_TYPE_KOREAN_SERVER_2)		// 2006-10-02 by cmkwon
	m_KbcGO.SetBmpButtonImage(IDB_GO_S2, RGB(0,0,255));
#elif defined(SERVICE_TYPE_CHINESE_SERVER_1)				// 2007-03-13 by cmkwon
	m_KbcGO.SetBmpButtonImage(IDB_GO_CHN, RGB(0,0,255));
#else
	m_KbcGO.SetBmpButtonImage(IDB_GO_VTC, RGB(0,0,255));
#endif

	m_KbcGO.SetToolTipText("Game Start");
	m_kbcBtnJoin.SetBmpButtonImage(IDB_JOINBTN, RGB(0,0,255));
	m_kbcBtnJoin.SetToolTipText("Join");


	///////////////////////////////////////////////////////////////////////////////
	// ��Ʈ�� ��ġ �����ϱ� ----> Start

	// 2007-09-07 by cmkwon, WebBrowser control
	char strWebAddress[1024];
	STRNCPY_MEMSET(strWebAddress, LAUNCHER_WEB_URL, 1024);
#ifdef S_ACCESS_INTERNAL_SERVER_HSSON
	//strWebAddress		= TESTSERVER_LAUNCHER_WEB_URL;			// 2006-08-04 by cmkwon, �׼� Launcher ��������
	STRNCPY_MEMSET(strWebAddress, TESTSERVER_LAUNCHER_WEB_URL, 1024);
#endif

// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - �Ʒ��� ���� 3�� ���� �߰�
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)
// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1)
// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
	///////////////////////////////////////////////////////////////////////////////
	// 2008-10-16 by cmkwon, Gameforge4D(Eng,Deu) Launcher Registry event ���� - Registry URL �� �ִٸ� �� URL�� �����Ѵ�.
	if(FALSE == m_strEventURL.IsEmpty())
	{
		STRNCPY_MEMSET(strWebAddress, m_strEventURL, 1024);
	}
#endif // END - #if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)

	RECT rt;
	rt.left		= EXE2_BG_WEBCONTROL_POS_X;
	rt.top		= EXE2_BG_WEBCONTROL_POS_Y;
	rt.right	= EXE2_BG_WEBCONTROL_POS_X + EXE2_BG_WEBCONTROL_WIDTH;
	rt.bottom	= EXE2_BG_WEBCONTROL_POS_Y + EXE2_BG_WEBCONTROL_HEIGHT;


	// 2008-12-23 by ckPark �Ϻ� ����
	//m_pHost		= new Host(m_hWnd,strWebAddress,NULL,NULL,NULL, &rt);
	// �Ϻ��� ���������� �Ⱥ����ֹǷ� �ƿ� Host���� ����
#if !defined(SERVICE_TYPE_JAPANESE_SERVER_1)
	m_pHost		= new Host(m_hWnd,strWebAddress,NULL,NULL,NULL, &rt);
#endif
	// end 2008-12-23 by ckPark �Ϻ� ����




	// �ػ� ���� ComboBox
	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->MoveWindow(EXE2_BG_RESOLUTION_COMBOBOX_POS_X, EXE2_BG_RESOLUTION_COMBOBOX_POS_Y, EXE2_BG_RESOLUTION_COMBOBOX_WIDTH, EXE2_BG_RESOLUTION_COMBOBOX_HEIGHT);

	// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - Windows Mode Check Box ��ġ ũ�� ����
	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->MoveWindow(EXE2_BG_WINDOWSMODE_CHECKBOX_POS_X, EXE2_BG_WINDOWSMODE_CHECKBOX_POS_Y, EXE2_BG_WINDOWSMODE_CHECKBOX_WIDTH, EXE2_BG_WINDOWSMODE_CHECKBOX_HEIGHT);

	

	
	// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	// ���þ� üũ�ڽ� �߰� ����
	m_ctrlCheckWindowMode.SetBitMap(IDB_CB_UNCHECK, IDB_CB_CHECK);
#endif
	// end 2008-12-17 by ckPark ���þ� ����





// 2008-01-22 by cmkwon, S_Exe2: ���� ���� ��ó��  ���������� ����
// #if defined(SERVICE_TYPE_KOREAN_SERVER_2) && !defined(_TEST_SERVER)
// 	// 2008-01-09 by cmkwon, Yedang_Kor_Main ���������� ��Ȱ��ȭ - ���������� üũ�ڽ� �Ⱥ��̰� ����
// 	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->ShowWindow(SW_HIDE);
// #endif

// 2007-09-07 by cmkwon, ������� �ʰ� �ִ� ����
//	// CharacterName Static
//	GetDlgItem(IDC_CHARACTER_NAME)->MoveWindow(0, 0, 124, 14);
//	GetDlgItem(IDC_CHARACTER_NAME)->SetWindowText(g_szMGameID);
	GetDlgItem(IDC_CHARACTER_NAME)->ShowWindow(SW_HIDE);

	// AccountName Edit Box, Password Edit Box
	GetDlgItem(IDC_EDIT_ACCOUNT)->MoveWindow(EXE2_BG_ACCOUNTNAME_EDIT_POS_X, EXE2_BG_ACCOUNTNAME_EDIT_POS_Y, EXE2_BG_ACCOUNTNAME_EDIT_WIDTH, EXE2_BG_ACCOUNTNAME_EDIT_HEIGHT);
	GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow(EXE2_BG_PASSWORD_EDIT_POS_X, EXE2_BG_PASSWORD_EDIT_POS_Y, EXE2_BG_PASSWORD_EDIT_WIDTH, EXE2_BG_PASSWORD_EDIT_HEIGHT);



	// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	// ���þ� ����Ʈ �ڽ� �߰�����
	m_ctrlEditAccount.SetBitMap(IDB_EDITBG);
	m_ctrlEditPassword.SetBitMap(IDB_EDITBG);
#endif
	// end 2008-12-17 by ckPark ���þ� ����



#if !defined(SERVICE_TYPE_KOREAN_SERVER_2) || defined(_DEBUG)	// 2007-09-07 by cmkwon, �ѱ� ��Ÿ�Ӹ� Release�� �Է��� ����
	GetDlgItem(IDC_EDIT_ACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
#endif

	// ��������Ʈ List Box
	GetDlgItem(IDC_LIST)->MoveWindow(EXE2_BG_SERVERLIST_BOX_POS_X, EXE2_BG_SERVERLIST_BOX_POS_Y, EXE2_BG_SERVERLIST_BOX_WIDTH, EXE2_BG_SERVERLIST_BOX_HEIGHT);
	GetDlgItem(IDC_LIST)->ShowWindow(SW_SHOW);		
	m_ctrlServerList.SetItemHeight(26);
	m_ctrlServerList.SetItemBGImageSize(EXE2_BG_SERVERLIST_ITEM_BG_WIDTH, EXE2_BG_SERVERLIST_ITEM_BG_HEIGHT);
	m_ctrlServerList.SetItemIconImage(EXE2_BG_SERVERLIST_ITEM_ICON_POS_X, EXE2_BG_SERVERLIST_ITEM_ICON_POS_Y, EXE2_BG_SERVERLIST_ITEM_ICON_WIDTH, EXE2_BG_SERVERLIST_ITEM_ICON_HEIGHT);
	m_ServerList = (CListBoxEBX *)GetDlgItem(IDC_LIST);



	// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	// ���þ� ��������Ʈ ����� ����
	m_ServerList->SetColorKey(RGB(150, 162, 161));
#endif
	// end 2008-12-17 by ckPark ���þ� ����



	// Minimized Button, Cancel Button
	GetDlgItem(IDMIN)->MoveWindow(EXE2_BG_MINIMIZED_BTN_POS_X, EXE2_BG_MINIMIZED_BTN_POS_Y, EXE2_BG_MINIMIZED_BTN_WIDTH, EXE2_BG_MINIMIZED_BTN_HEIGHT);
	GetDlgItem(IDCAN)->MoveWindow(EXE2_BG_CANCEL_BTN_POS_X, EXE2_BG_CANCEL_BTN_POS_Y, EXE2_BG_CANCEL_BTN_WIDTH, EXE2_BG_CANCEL_BTN_HEIGHT);

	// Game Start Button
	GetDlgItem(IDGO)->MoveWindow(EXE2_BG_GAMESTART_BTN_POS_X, EXE2_BG_GAMESTART_BTN_POS_Y, EXE2_BG_GAMESTART_BTN_WIDTH, EXE2_BG_GAMESTART_BTN_HEIGHT);

	// 2007-09-07 by cmkwon, ������� �ʴ� ��ư��
	//// Join Button
	//GetDlgItem(IDJOIN)->MoveWindow(nPosX, nPosY, IMAGE_JOIN_BUTTON_X_SIZE, IMAGE_JOIN_BUTTON_Y_SIZE);

	// Update Progress Bar
	m_progressCtrl.MoveWindow(EXE2_BG_UPDATE_PROGRESS_BAR_POS_X, EXE2_BG_UPDATE_PROGRESS_BAR_POS_Y, EXE2_BG_UPDATE_PROGRESS_BAR_WIDTH, EXE2_BG_UPDATE_PROGRESS_BAR_HEIGHT);



	// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	// ���þƴ� ���α׷��� �� ������ �ٸ���
	m_progressCtrl.SetBkColor(RGB(0, 0, 0));
	m_progressCtrl.SetGradientColors(RGB(18, 236, 218), RGB(18, 236, 218));


	// 2008-12-23 by ckPark �Ϻ� ����
#elif defined(SERVICE_TYPE_JAPANESE_SERVER_1)
	// �Ϻ� ���α׷����� ���� ��׶��� �÷�
	m_progressCtrl.SetBkColor(RGB(0, 186, 215));
	m_progressCtrl.SetGradientColors(RGB(255, 102, 0), RGB(255, 102, 0));
#else
	// end 2008-12-23 by ckPark �Ϻ� ����


	m_progressCtrl.SetGradientColors(RGB(255, 0, 0), RGB(0, 0, 255));
#endif
	// end 2008-12-17 by ckPark ���þ� ����



	// Download File Version Num
	GetDlgItem(IDC_DOWNLOAD_FILENUM)->MoveWindow(EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X, EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y, EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH, EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT);
	long wndStyle = ::GetWindowLong(GetDlgItem(IDC_DOWNLOAD_FILENUM)->m_hWnd, GWL_STYLE);
    ::SetWindowLong(GetDlgItem(IDC_DOWNLOAD_FILENUM)->m_hWnd, GWL_STYLE, wndStyle | SS_CENTERIMAGE);	// ����� ������ �����߾�(SS_CENTERIMAGE)�Ӽ��� �߰�
	m_fontDownloadFileNum.CreateFont(EXE2_BG_DOWNLOAD_FILE_FONT_SIZE, 0, 0, 0, EXE2_BG_DOWNLOAD_FILE_FONT_WEIGHT, 0, FALSE, FALSE, SG_BOX_FONT_CHARSET, OUT_DEFAULT_PRECIS,
							  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH , SG_BOX_FONT_FACENAME);    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
	GetDlgItem(IDC_DOWNLOAD_FILENUM)->SetFont(&m_fontDownloadFileNum);

	// Download File Info
	GetDlgItem(IDC_FILE_INFO)->MoveWindow(EXE2_BG_UPDATE_INFO_STATIC_POS_X, EXE2_BG_UPDATE_INFO_STATIC_POS_Y, EXE2_BG_UPDATE_INFO_STATIC_WIDTH, EXE2_BG_UPDATE_INFO_STATIC_HEIGHT);
	wndStyle = ::GetWindowLong(GetDlgItem(IDC_FILE_INFO)->m_hWnd, GWL_STYLE);
    ::SetWindowLong(GetDlgItem(IDC_FILE_INFO)->m_hWnd, GWL_STYLE, wndStyle | SS_CENTERIMAGE);	// ����� ������ �����߾�(SS_CENTERIMAGE)�Ӽ��� �߰�
	m_fontFileInfo.CreateFont(EXE2_BG_UPDATE_INFO_FONT_SIZE, 0, 0, 0, EXE2_BG_UPDATE_INFO_FONT_WEIGHT, 0, FALSE, FALSE, SG_BOX_FONT_CHARSET, OUT_DEFAULT_PRECIS,
							  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH , SG_BOX_FONT_FACENAME);    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
	GetDlgItem(IDC_FILE_INFO)->SetFont(&m_fontFileInfo);

	
#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1)
	///////////////////////////////////////////////////////////////////////////////
	// 2007-09-27 by cmkwon, Homepage���� ��ư �߰�(��Ʈ�� VTC-Intecom ��û) - 
	GetDlgItem(IDC_BTN_HOMEPAGE)->MoveWindow(645, 38, 115, 18);
	GetDlgItem(IDC_BTN_HOMEPAGE)->ShowWindow(SW_SHOW);
	m_bmpBtnHomepage.LoadBitmaps(IDB_HOMEPAGE_UP, IDB_HOMEPAGE_DOWN, IDB_HOMEPAGE_FOCUS);
#endif

// 2008-10-20 by cmkwon, Gameforge4D(Engilsh, German)�� ���� ���� ����ϱ� ��� �߰� - �Ʒ��� ���� ����
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1)	// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - �Ʒ��� ���� 3�� ���� �߰�
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)	// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1)
// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
	///////////////////////////////////////////////////////////////////////////////
	// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
	m_ctlBtnRememberID.ShowWindow(SW_SHOW);
	m_ctlBtnRememberID.MoveWindow(EXE2_BG_REMEMBERID_CHECKBOX_POS_X, EXE2_BG_REMEMBERID_CHECKBOX_POS_Y, EXE2_BG_REMEMBERID_CHECKBOX_WIDTH, EXE2_BG_REMEMBERID_CHECKBOX_HEIGHT);

	if(FALSE == m_szAccountNameReg.IsEmpty())
	{
		m_ctlBtnRememberID.SetCheck(TRUE);
	}
#endif


	
	
	
	// 2008-12-23 by ckPark �Ϻ� ����
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
	// �Ϻ� ���Ŀ� �ʿ���� ui�� ���� ����
	GetDlgItem(IDC_LIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDMIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDJOIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDSECRET)->ShowWindow(SW_HIDE);
	GetDlgItem(IDEND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHARACTER_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_SERVER_LIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_VIEW_SCREEN_KEYBOARD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_HOMEPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK_REMEMBER_ID)->ShowWindow(SW_HIDE);
#endif
	// end 2008-12-23 by ckPark �Ϻ� ����





	// ��Ʈ�� ��ġ �����ϱ� ----> End
	///////////////////////////////////////////////////////////////////////////////


	
	///////////////////////////////////////////////////////////////////////////////
	// ��� ȭ�� ����� ----> Start
	
	CDC *pDC = GetDC();
	int nXScreen = EXE2_LAUNCHER_BG_SIZE_X;
	int nYScreen = EXE2_LAUNCHER_BG_SIZE_Y;
	m_BackGround.CreateCompatibleBitmap(pDC, nXScreen, nYScreen);
		
	CDC		memDCBackGround;	
	memDCBackGround.CreateCompatibleDC(pDC);
	CBitmap	*pOldBitmapBackGround = memDCBackGround.SelectObject(&m_BackGround);
	memDCBackGround.PatBlt(0,0,nXScreen,nYScreen,BLACKNESS);						// ����� ���������� �ʱ�ȭ
	
	CDC tmMemDC;
	tmMemDC.CreateCompatibleDC(pDC);

	CBitmap tmBitmap;
	CBitmap *pTmOldBitmap;





	// 2008-12-23 by ckPark �Ϻ� ����

// 	// Ÿ��Ʋ�� �׸���(Title Bar)
// 	tmBitmap.LoadBitmap(IDB_TITLE);
// 	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
// 	memDCBackGround.BitBlt(0, 0, EXE2_BG_TITLE_BAR_SIZE_X, EXE2_BG_TITLE_BAR_SIZE_Y, &tmMemDC, 0, 0, SRCCOPY);
// 	tmMemDC.SelectObject(pTmOldBitmap);
// 	tmBitmap.DeleteObject();
// 	
// 	// ��� ȭ�� �׸���(Background)
// 	tmBitmap.LoadBitmap(IDB_BG_VTC);
// 	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
// 	memDCBackGround.BitBlt(0, EXE2_BG_TITLE_BAR_SIZE_Y,EXE2_BG_BACKGROUND_IMAGE_SIZE_X, EXE2_BG_BACKGROUND_IMAGE_SIZE_Y,&tmMemDC,0,0,SRCCOPY);
// 	tmMemDC.SelectObject(pTmOldBitmap);
// 	tmBitmap.DeleteObject();
// 	
// 	memDCBackGround.SelectObject(pOldBitmapBackGround);

#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
	// �Ϻ� ���Ĵ� Ÿ��Ʋ �ٰ� ����
	// ��� ȭ�� �׸���(Background)
	tmBitmap.LoadBitmap(IDB_BG_VTC);
	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
	memDCBackGround.BitBlt(0, 0,EXE2_LAUNCHER_BG_SIZE_X, EXE2_LAUNCHER_BG_SIZE_Y,&tmMemDC,0,0,SRCCOPY);
	tmMemDC.SelectObject(pTmOldBitmap);
	tmBitmap.DeleteObject();
	
	memDCBackGround.SelectObject(pOldBitmapBackGround);

#else

	// Ÿ��Ʋ�� �׸���(Title Bar)
	tmBitmap.LoadBitmap(IDB_TITLE);
	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
	memDCBackGround.BitBlt(0, 0, EXE2_BG_TITLE_BAR_SIZE_X, EXE2_BG_TITLE_BAR_SIZE_Y, &tmMemDC, 0, 0, SRCCOPY);
	tmMemDC.SelectObject(pTmOldBitmap);
	tmBitmap.DeleteObject();

	// ��� ȭ�� �׸���(Background)
	tmBitmap.LoadBitmap(IDB_BG_VTC);
	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
	memDCBackGround.BitBlt(0, EXE2_BG_TITLE_BAR_SIZE_Y,EXE2_BG_BACKGROUND_IMAGE_SIZE_X, EXE2_BG_BACKGROUND_IMAGE_SIZE_Y,&tmMemDC,0,0,SRCCOPY);
	tmMemDC.SelectObject(pTmOldBitmap);
	tmBitmap.DeleteObject();

	memDCBackGround.SelectObject(pOldBitmapBackGround);

#endif
	
	// end 2008-12-23 by ckPark �Ϻ� ����







	// ��� ȭ�� ����� ----> End
	///////////////////////////////////////////////////////////////////////////////

	DisableControls();
	SetPrivateIP();

	// timeout�� �߻��ϸ� ���� ������ ����
	SetTimer(TIMERID_CONNECT_PRESERVER, 200, NULL);
	SetTimer(TIMERID_SEND_ALIVE_PACKET, 30000, NULL);
	SetTimer(TIMERID_NETWORK_STATE_CHECK, 1000, NULL);		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ

#ifndef _DEBUG
	DeleteFile("AtumLauncher_dbg.exe");
#endif

	ShowWindow(SW_SHOW);
	this->GetPublicLocalIP(m_szLocalIP);		// 2006-05-07 by cmkwon
	return TRUE;  // return TRUE  unless you set the focus to a control

///////////////////////////////////////////////////////////////////////////////	
// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� - ���� ���� ���� ������
//	///////////////////////////////////////////////////////////////////////////////
//	// 2007-05-07 by cmkwon, �ػ� ������ �� ���� ���� �����ϱ� ����
//	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER);
//	if(pComboBox)
//	{
//// 2007-07-24 by cmkwon, ��ó���� 800*600 �ػ� ���� - �޺��ڽ��� �߰����� �ʴ´�
////		pComboBox->AddString(STRMSG_WINDOW_DEGREE_800x600_LOW);
////		pComboBox->AddString(STRMSG_WINDOW_DEGREE_800x600_MEDIUM);	
////		pComboBox->AddString(STRMSG_WINDOW_DEGREE_800x600_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1024x768_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1024x768_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1024x768_HIGH);
//
//		// 2007-08-23 by cmkwon, Wide �ػ� 1280x720(16:9) �߰� - 
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x720_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x720_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x720_HIGH);
//
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x800_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x800_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1280x800_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x960_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x960_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x960_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x1024_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x1024_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1280x1024_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1600x900_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1600x900_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_W1600x900_HIGH);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1600x1200_LOW);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1600x1200_MEDIUM);
//		pComboBox->AddString(STRMSG_WINDOW_DEGREE_1600x1200_HIGH);
//		pComboBox->SetCurSel(max(0, m_nWindowDegreeReg-3));			// 2007-07-24 by cmkwon, ��ó���� 800*600 �ػ� ���� - ������Ʈ������ �������� �״�� ����Ѵ�.
//	}
//	
//    m_fontServerGroupListBox.CreatePointFont(90, "����ü");    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
//    GetDlgItem(IDC_LIST)->SetFont(&m_fontServerGroupListBox);
//
//    m_fontNoticeBox.CreateFont(16, 0, 0, 0, SG_BOX_FONT_WEIGHT, 0,
//							  FALSE, FALSE, SG_BOX_FONT_CHARSET, OUT_DEFAULT_PRECIS,
//							  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
//							  FIXED_PITCH , SG_BOX_FONT_FACENAME);    // "System" Font�� ��ǥ���� Fixed Font�Ӵ�.
//    GetDlgItem(IDC_NOTICE)->SetFont(&m_fontNoticeBox);
//
//	m_Cur_Percent=0;
//	m_SelectFlag = FALSE;
//
//	
//	m_bitmapBtnCancel.AutoLoad(IDCAN, this);
//	m_bitmapBtnMin.AutoLoad(IDMIN, this);
//#if defined(_GLOBAL_ENG_SERVER)			// 2006-09-07 by cmkwon, ����(#ifdef _VTC_VIET_SERVER --> #ifndef _GLOBAL_ENG_SERVER)
//	m_KbcGO.SetBmpButtonImage(IDB_GOBTN, RGB(0,0,255));
//#elif defined(_KOREA_SERVER_2)		// 2006-10-02 by cmkwon
//	m_KbcGO.SetBmpButtonImage(IDB_GO_S2, RGB(0,0,255));
//#elif defined(_CHN_S1)				// 2007-03-13 by cmkwon
//	m_KbcGO.SetBmpButtonImage(IDB_GO_CHN, RGB(0,0,255));
//#else
//	m_KbcGO.SetBmpButtonImage(IDB_GO_VTC, RGB(0,0,255));
//#endif
//
//	m_KbcGO.SetToolTipText("Game Start");
//	m_kbcBtnJoin.SetBmpButtonImage(IDB_JOINBTN, RGB(0,0,255));
//	m_kbcBtnJoin.SetToolTipText("Join");
//
//
//	//GetDlgItem(IDC_CHARACTER_NAME)->SetWindowText(g_szAccountName);
////////////////////////////////////////////////////////////////////////////
//// 2006-05-02 by ispark, ��������
//	char* strWebAddress = LAUNCHER_WEB_URL;
//#ifdef _TEST_SERVER
//	strWebAddress		= TESTSERVER_LAUNCHER_WEB_URL;			// 2006-08-04 by cmkwon, �׼� Launcher ��������
//#endif
////	HWND hWnd = GetDlgItem(IDC_WEB)->m_hWnd;
//
//// 2007-09-07 by cmkwon, �Ʒ��� ���� ������
////	m_pHost = new Host(m_hWnd,strWebAddress,NULL,NULL,NULL);
////	RECT rt;
////	rt.left = DEF_HOST_L;
////	rt.top = DEF_HOST_T;
////	rt.right = DEF_HOST_R;
////	rt.bottom = DEF_HOST_B;
////	m_pHost->ReSizeRect(rt);
//	RECT rt;
//	rt.left		= DEF_HOST_L;
//	rt.top		= DEF_HOST_T;
//	rt.right	= DEF_HOST_R;
//	rt.bottom	= DEF_HOST_B;
//	m_pHost		= new Host(m_hWnd,strWebAddress,NULL,NULL,NULL, &rt);
//
//
/////////////////////////////////////////////////////////////////////////////////
//// ��� ȭ�� �����
//	// 2006-05-02 by ispark, ��ó ��� ȭ�� ����
//
//	CDC *pDC = GetDC();
//// 2004-11-08 by cmkwon
////	int nXScreen = GetSystemMetrics(SM_CXSCREEN);
////	int nYScreen = GetSystemMetrics(SM_CYSCREEN);
//	int nXScreen = DEF_SCREEN_X;
//	int nYScreen = DEF_SCREEN_Y;
//	m_BackGround.CreateCompatibleBitmap(pDC, nXScreen, nYScreen);
//		
//	CDC		memDCBackGround;	
//	memDCBackGround.CreateCompatibleDC(pDC);
//	CBitmap	*pOldBitmapBackGround = memDCBackGround.SelectObject(&m_BackGround);
//	memDCBackGround.PatBlt(0,0,nXScreen,nYScreen,BLACKNESS);						// ����� ���������� �ʱ�ȭ
//	
//	CDC tmMemDC;
//	int nPosX, nPosY;	
//	
//	// Gear �׸���
//	CBitmap tmBitmap;
//	CBitmap *pTmOldBitmap;
////	tmBitmap.LoadBitmap(IDB_GEAR);		
//	tmMemDC.CreateCompatibleDC(pDC);
////	CBitmap *pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
//	nPosX = nXScreen - IMAGE_GEAR_X_SIZE;
//	nPosY = nYScreen - (IMAGE_GEAR_Y_SIZE + 50);
////	memDCBackGround.BitBlt(nPosX, nPosY, IMAGE_GEAR_X_SIZE, IMAGE_GEAR_Y_SIZE, &tmMemDC, 0, 0, SRCCOPY);
////	tmMemDC.SelectObject(pTmOldBitmap);
////	tmBitmap.DeleteObject();
//
//	// ServerList �׸���
////	tmBitmap.LoadBitmap(IDB_SERVERLIST);
////	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
//	nPosX = (nXScreen - IMAGE_SERVERLIST_X_SIZE)/2;
//	nPosY = (nYScreen - IMAGE_SERVERLIST_Y_SIZE)/2;
//	int nServerListPosX = nPosX;
//	int nServerListPosY = nPosY;
////	memDCBackGround.BitBlt(nPosX, nPosY, IMAGE_SERVERLIST_X_SIZE, IMAGE_SERVERLIST_Y_SIZE, &tmMemDC, 0, 0, SRCCOPY);
////	tmMemDC.SelectObject(pTmOldBitmap);
////	tmBitmap.DeleteObject();
//
//	// Ÿ��Ʋ�� �׸���
//	tmBitmap.LoadBitmap(IDB_TITLE);
//	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
//	nPosX = 0;
//	nPosY = 0;
//	memDCBackGround.BitBlt(nPosX, nPosY, IMAGE_TITLE_X_SIZE, IMAGE_TITLE_Y_SIZE, &tmMemDC, 0, 0, SRCCOPY);
//	tmMemDC.SelectObject(pTmOldBitmap);
//	tmBitmap.DeleteObject();
//
//
//// 7/13/2006 by dgwoo, NEW UpdateBar �׸���
//#ifndef _GLOBAL_ENG_SERVER			// 2006-09-07 by cmkwon, ����(#ifdef _VTC_VIET_SERVER --> #ifndef _GLOBAL_ENG_SERVER)
//	tmBitmap.LoadBitmap(IDB_BG_VTC);
//	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
//	nPosX = 0;
//	nPosY = IMAGE_TITLE_Y_SIZE;
//	memDCBackGround.BitBlt(nPosX,nPosY,DEF_SCREEN_X,DEF_SCREEN_Y,&tmMemDC,0,0,SRCCOPY);
//	tmMemDC.SelectObject(pTmOldBitmap);
//	tmBitmap.DeleteObject();
//#else
//	tmBitmap.LoadBitmap(IDB_CENTER);
//	pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
//	nPosX = 0;
//	nPosY = nYScreen - IMAGE_CENTERBAR_Y_SIZE;
//	memDCBackGround.BitBlt(nPosX, nPosY, IMAGE_CENTERBAR_X_SIZE, IMAGE_CENTERBAR_Y_SIZE, &tmMemDC, 0, 0, SRCCOPY);
//	tmMemDC.SelectObject(pTmOldBitmap);
//	tmBitmap.DeleteObject();
//#endif
//
//
////	if(nXScreen > IMAGE_UPDATEBAR_X_SIZE * 2)
////	{
////		// UpdateCenterBar �׸���
////		tmBitmap.LoadBitmap(IDB_BARCENTER);
////		pTmOldBitmap = tmMemDC.SelectObject(&tmBitmap);
////		nPosX = (nXScreen - IMAGE_UPDATEBAR_X_SIZE)/2;
////		nPosY = nYScreen - IMAGE_UPDATEBAR_Y_SIZE;
////		memDCBackGround.BitBlt(nPosX, nPosY, IMAGE_UPDATEBAR_X_SIZE, IMAGE_UPDATEBAR_Y_SIZE, &tmMemDC, 0, 0, SRCCOPY);
////		tmMemDC.SelectObject(pTmOldBitmap);
////		tmBitmap.DeleteObject();
////	}
//
//	memDCBackGround.SelectObject(pOldBitmapBackGround);
////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//// ��Ʈ�� ��ġ �����ϱ�
//	
//	// �ػ� ���� ComboBox
//// 7/12/2006 by dgwoo
//	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->MoveWindow(DEF_DEGREE_L, DEF_DEGREE_T, 
//															 DEF_DEGREE_R, DEF_DEGREE_B);
//
//	// CharacterName Static
//	nPosX = nServerListPosX + 80;
//	nPosY = nServerListPosY + 5;
//	GetDlgItem(IDC_CHARACTER_NAME)->MoveWindow(nPosX, nPosY, 124, 14);
//	GetDlgItem(IDC_CHARACTER_NAME)->SetWindowText(g_szMGameID);
//#if defined(_KOREA_SERVER_2)		// 2006-10-02 by cmkwon
//	#if defined(_DEBUG)
//		GetDlgItem(IDC_EDIT_ACCOUNT)->MoveWindow(DEF_ACCOUNT_L_S2, DEF_ACCOUNT_T_S2, DEF_ACCOUNT_R_S2, DEF_ACCOUNT_B_S2);
//		GetDlgItem(IDC_EDIT_ACCOUNT)->ShowWindow(SW_SHOW);
//		GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow(DEF_PASSWORD_L_S2, DEF_PASSWORD_T_S2, DEF_ACCOUNT_R, DEF_ACCOUNT_B);
//		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
//	#endif
//// 2007-03-13 by cmkwon, �������� ��� �Ƶ�/��� �Է� ��Ʈ�� �����ֱ�
////// 2007-03-06 by cmkwon, �߰���(|| defined(_MASANG15_SERVER))
////#elif defined(_DEBUG) || defined(_MASANG15_SERVER) || defined(_MASANG51_SERVER) || defined(_GLOBAL_ENG_SERVER) || defined(_VTC_VIET_SERVER) || defined(_KOREA_SERVER_2) || defined(_CHN_S1)
//#else
//	GetDlgItem(IDC_EDIT_ACCOUNT)->MoveWindow(DEF_ACCOUNT_L, DEF_ACCOUNT_T, DEF_ACCOUNT_R, DEF_ACCOUNT_B);
//	GetDlgItem(IDC_EDIT_ACCOUNT)->ShowWindow(SW_SHOW);
//	GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow(DEF_PASSWORD_L, DEF_PASSWORD_T, DEF_ACCOUNT_R, DEF_ACCOUNT_B);
//	GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
//#endif
//
//
//
//	///////////////////////////////////////////////////////////////////////////////
//	// ��������Ʈ List
//	GetDlgItem(IDC_LIST)->MoveWindow(DEF_SERVERLIST_L, DEF_SERVERLIST_T, DEF_SERVERLIST_R,DEF_SERVERLIST_B);
//	GetDlgItem(IDC_COMBO_SERVER_LIST)->MoveWindow(DEF_SERVERLIST_L, DEF_SERVERLIST_T, DEF_SERVERLIST_R, DEF_SERVERLIST_B);
//#ifndef _GLOBAL_ENG_SERVER			// 2006-09-07 by cmkwon, ����(#ifdef _VTC_VIET_SERVER --> #ifndef _GLOBAL_ENG_SERVER)
//	GetDlgItem(IDC_LIST)->ShowWindow(SW_SHOW);		
//	GetDlgItem(IDC_COMBO_SERVER_LIST)->ShowWindow(SW_HIDE);
//	m_ctrlServerList.SetItemHeight(25);
//	m_ServerList = (CListBoxEBX *)GetDlgItem(IDC_LIST);
//#else
//	GetDlgItem(IDC_LIST)->ShowWindow(SW_HIDE);		
//	GetDlgItem(IDC_COMBO_SERVER_LIST)->ShowWindow(SW_SHOW);
//	m_ServerList = (CComboBoxEBX *)GetDlgItem(IDC_COMBO_SERVER_LIST);
//#endif
//
//	
//	// �������� EditBox
//	nPosX = nServerListPosX + 245;
//	nPosY = nServerListPosY + 49;
//	GetDlgItem(IDC_NOTICE)->MoveWindow(nPosX, nPosY, 382, 166);
//	GetDlgItem(IDC_NOTICE)->ShowWindow(SW_HIDE);
//
//	// Min Button
////	nPosX = nServerListPosX + 612;
////	nPosY = nServerListPosY;
////	GetDlgItem(IDMIN)->MoveWindow(nPosX, nPosY, 16, 20);
//	nPosX = 752;
//	nPosY = 0;
//	GetDlgItem(IDMIN)->MoveWindow(nPosX, nPosY, 16, 20);
//
//	// Cancel Button
////	nPosX = nServerListPosX + 628;
////	nPosY = nServerListPosY;
////	GetDlgItem(IDCAN)->MoveWindow(nPosX, nPosY, 16, 20);
//	nPosX = 772;
//	nPosY = 0;
//	GetDlgItem(IDCAN)->MoveWindow(nPosX, nPosY, 16, 20);
//
//	// GO Button
//// 2006-05-02 by ispark
////	nPosX = nServerListPosX + 54;
////	nPosY = nServerListPosY + 216;
//#if defined(_KOREA_SERVER_2)
//	GetDlgItem(IDGO)->MoveWindow(DEF_GO_L_S2, DEF_GO_T_S2, IMAGE_GO_BUTTON_X_SIZE_S2, IMAGE_GO_BUTTON_Y_SIZE_S2);
//#elif defined(_CHN_S1)				// 2007-03-13 by cmkwon
//	GetDlgItem(IDGO)->MoveWindow(DEF_GO_L_CHN, DEF_GO_T_CHN, IMAGE_GO_BUTTON_X_SIZE_CHN, IMAGE_GO_BUTTON_Y_SIZE_CHN);
//#else
//	GetDlgItem(IDGO)->MoveWindow(DEF_GO_L, DEF_GO_T, IMAGE_GO_BUTTON_X_SIZE, IMAGE_GO_BUTTON_Y_SIZE);
//#endif
//	// 2005-11-10 by cmkwon, Join Button
//	nPosX = nServerListPosX + 265;
//	nPosY = nServerListPosY + 226;
//	GetDlgItem(IDJOIN)->MoveWindow(nPosX, nPosY, IMAGE_JOIN_BUTTON_X_SIZE, IMAGE_JOIN_BUTTON_Y_SIZE);
//
//	// Update Progress
//// 7/12/2006 by dgwoo
//	nPosX = 26;	
//	nPosY = nYScreen - 23;
//	m_progressCtrl.MoveWindow(nPosX, nPosY, nXScreen - (nPosX*2), 7);
//
//	// Download File Version Num
//// 7/12/2006 by dgwoo
//	GetDlgItem(IDC_DOWNLOAD_FILENUM)->MoveWindow(DEF_FILEVERSION_L, DEF_FILEVERSION_T, DEF_FILEVERSION_R, DEF_FILEVERSION_B);
//
//	// Download File Info
//// 7/12/2006 by dgwoo
//	GetDlgItem(IDC_FILE_INFO)->MoveWindow(DEF_FILEINFO_L, DEF_FILEVERSION_T, DEF_FILEINFO_R, DEF_FILEVERSION_B);
////
/////////////////////////////////////////////////////////////////////////////////
//
//
//	m_progressCtrl.SetGradientColors(RGB(255, 0, 0), RGB(0, 0, 255));
//
//	// Initialize winsock 2.0
//	CWinSocket::SocketInit();
//
//	// set default values & settings
//	m_bCancelFlag = FALSE;
//	m_bProcessingVersionUpdate = FALSE;
//	m_bShowPreServerIPDlg = TRUE;
////	m_FtpDownload.SetMainDlg(this);
//	DisableControls();
//	SetPrivateIP();
//
//// 2006-05-03 by cmkwon, ���������� ��ó�� ��ȭ�鿡�� ó���Ѵ�.
//// 	// �ϴ� Notice �ε� - ���� ����... ���߿� notice�� �ٽ� �ٿ� ������ �������...
//// 	if (!ReadNoticeFile())
//// 	{
//// 		//AtumMessageBox("Notice File Error!");
//// 		//EndDialog(-1);
//// 		//return FALSE;
//// 	}
//
//	// timeout�� �߻��ϸ� ���� ������ ����
//	SetTimer(TIMERID_CONNECT_PRESERVER, 200, NULL);
//	SetTimer(TIMERID_SEND_ALIVE_PACKET, 30000, NULL);
//	SetTimer(TIMERID_NETWORK_STATE_CHECK, 1000, NULL);		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
//
//#ifndef _DEBUG
//	DeleteFile("AtumLauncher_dbg.exe");
//#endif
//
//	int nXScreen1 = GetSystemMetrics(SM_CXSCREEN);
//	int nYScreen1 = GetSystemMetrics(SM_CYSCREEN);
//
//	CRect rect((nXScreen1-800)/2, (nYScreen1-600)/2, (nXScreen1-800)/2+800, (nYScreen1-600)/2+DEF_SCREEN_Y);
//	this->MoveWindow(&rect);
//	ShowWindow(SW_SHOW);
//
//	this->GetPublicLocalIP(m_szLocalIP);		// 2006-05-07 by cmkwon
//	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CAtumLauncherDlg::ConnectPreServer()
{
// Pre Server IP â ����
//	char preServerIP[SIZE_MAX_IPADDRESS];

// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - ���� ũŰ�� �� �ʿ� �ϴ�.
//	char preServerIP[128];
	char preServerIP[1024];		// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 
#ifdef _ATUM_DEVELOP
	char ExecutableBinary[256];
	char ExecutePath[256];
	CPreServerIPDlg	dlg(m_szPreServerIPReg, m_szExecutableBinaryReg, m_szExecutePathReg,
						m_szPreServerIPHistoryReg, m_szExecuteBinHistoryReg, m_szExecutePathHistoryReg);
	dlg.m_bWindowMode = ((m_nWindowModeReg==GAME_MODE_WINDOW)?TRUE:FALSE);

// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - ó�� �ʿ����� ����
//	// window mode�̸� �ػ� combo box�� disable��Ŵ
//	if (m_nWindowModeReg == GAME_MODE_WINDOW)
//	{
//		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(FALSE);
//	}
//	else
//	{
//		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow();
//	}

	if (m_bShowPreServerIPDlg)
	{
		if (dlg.DoModal() != IDOK)
		{
			return FALSE;
		}
	}

	STRNCPY_MEMSET(preServerIP, dlg.m_preserver_ip, 128);
	m_szPreServerIPReg = dlg.m_preserver_ip;
	STRNCPY_MEMSET(ExecutableBinary, dlg.m_executable_bin, 256);
	m_szExecutableBinaryReg = dlg.m_executable_bin;
	STRNCPY_MEMSET(ExecutePath, dlg.m_execute_path, 256);
	m_szExecutePathReg = dlg.m_execute_path;
	m_szPreServerIPHistoryReg = dlg.m_szPreServerIPHistory;
	m_szExecuteBinHistoryReg = dlg.m_szExecuteBinHistory;
	m_szExecutePathHistoryReg = dlg.m_szExecutePathHistory;
	m_nWindowModeReg = ((dlg.m_bWindowMode==TRUE)?GAME_MODE_WINDOW:GAME_MODE_FULLSCREEN);
	///////////////////////////////////////////////////////////////////////////////
	// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �߰��Ѱ�
	if(GAME_MODE_WINDOW == m_nWindowModeReg)
	{
		
		
		
		// 2008-12-17 by ckPark ���þ� ����
		// ���þƴ� üũ�ڽ� ���¸� �������� ���� ���´�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		m_ctrlCheckWindowMode.SetCheck(TRUE);
#else
		this->m_ctlbWindowMode		= TRUE;
#endif
		// end 2008-12-17 by ckPark ���þ� ����





		this->CheckDlgButton(IDC_CHECK_WINDOWS_MODE, 1);
	}
	((CAtumLauncherApp*)AfxGetApp())->WriteProfile();

	m_bUpdateClientFile = dlg.m_bUpdateClientFile;

#else
	// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - domain ���� �����Ǹ� ���̰� ������� �ִ�.
	//STRNCPY_MEMSET(preServerIP, m_szPreServerIPReg, SIZE_MAX_IPADDRESS);
	STRNCPY_MEMSET(preServerIP, m_szPreServerIPReg, 1024);		// 2009-01-15 by cmkwon, PreServer, DBServer ���� DNS�� ���� �����ϰ� ���� - 
	m_szPreServerIPReg = m_szPreServerIPReg;
#endif


	// Make socket instance & connect
	m_pUpdateWinsocket = new CUpdateWinSocket(GetSafeHwnd());
	// 2004-11-19 by cmkwon
	//if (!m_pUpdateWinsocket->Connect(GGetIPByName(preServerIP, preServerIP), PRE_SERVER_PORT))

	int nPreServerPort = PRE_SERVER_PORT;		// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - ��Ʈ�� ���� �� �� �ְ� ����

// 2009-04-23 by cmkwon, ���þ� Innova Frost �ӽ� �����ϱ� - �Ʒ��� ���� define ���� ó�� ��.
//#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1) && defined(_USING_INNOVA_FROST_)

// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - 
// 	// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - ReadLoginAddr() ȣ��
// 	char ip[AYYO_SECURITY_BUF_SIZE] = {0};
// 	int port = 0;
// 	try
// 	{
// 		ReadLoginAddr(ip, port);
// 	}
// 	catch (std::runtime_error runErr)
// 	{
// 		CString strErr;
// 		strErr.Format("[Error] call ReadLoginAddr() error !! %s", runErr.what());
// 		AfxMessageBox(strErr);
// 		return FALSE;
// 	}
// 	catch(...)
// 	{
// 		CString strErr;
// 		strErr.Format("[Error] call ReadLoginAddr() error !! unknown error(%d)", GetLastError());
// 		AfxMessageBox(strErr);
// 		return FALSE;
// 	}	
// 	STRNCPY_MEMSET(preServerIP, ip, 128);	// IP ����
// 	nPreServerPort		= port;				// Port ����
	///////////////////////////////////////////////////////////////////////////////
	// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - 
	//DbgOut("[TEMP] 090710 frostInitialize 2-1 \r\n");
	frostInitialize(".\\Frost\\gameShieldDll.dll");
	//DbgOut("[TEMP] 090710 frostInitialize 2-2 \r\n");
#endif // END - #if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)

// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������ ��Ʈ�� ���� �õ�
//	if (!m_pUpdateWinsocket->Connect(preServerIP, PRE_SERVER_PORT))
	if (!m_pUpdateWinsocket->Connect(preServerIP, nPreServerPort))
	{
 		int err = GetLastError();
//		AtumMessageBox("������ ����Ǿ� ���� �ʰų� ���� ���Դϴ�.\n\n�׽�Ʈ �ð��� �ָ� 24�ð�,\n\n���� ����10�ú��� ����24�ñ����Դϴ�.");
 		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0004);
		SAFE_DELETE(m_pUpdateWinsocket);
		EndDialog(-1);
		return FALSE;
	}
	m_PreSD = m_pUpdateWinsocket->GetSocketDescriptor();

	return TRUE;
}

void CAtumLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if(SC_MAXIMIZE == nID)
	{// �ִ�ȭ�� ���´�.

		return;
	}
	
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAtumLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC PaintDC (this);
		CDC		dcMem;
		BITMAP	stBitmap;

		dcMem.CreateCompatibleDC(&PaintDC);
		CBitmap *OldBitmap = dcMem.SelectObject(&m_BackGround);

		m_BackGround.GetObject(sizeof(BITMAP), &stBitmap);
		PaintDC.BitBlt(0, 0, stBitmap.bmWidth, stBitmap.bmHeight, &dcMem, 0, 0, SRCCOPY);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAtumLauncherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


struct sort_MEX_SERVER_GROUP_INFO_FOR_LAUNCHER_By_Crowdedness
{
	bool operator()(MEX_SERVER_GROUP_INFO_FOR_LAUNCHER op1, MEX_SERVER_GROUP_INFO_FOR_LAUNCHER op2)
	{
		return op1.Crowdedness < op2.Crowdedness;				// �������� ����
	}
};


LONG CAtumLauncherDlg::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	if(NULL == m_pUpdateWinsocket)
	{
		return 0L;
	}

	switch(LOWORD(wParam))
	{
	case CUpdateWinSocket::WS_ERROR:
		{
		}
		break;
	case CUpdateWinSocket::WS_CONNECTED:
		{
			if (HIWORD(wParam) == TRUE)
			{
				m_pUpdateWinsocket->WriteMessageType(T_PC_CONNECT_GET_SERVER_GROUP_LIST);

				INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_SINGLE_FILE_VERSION_CHECK, T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK, msgSFVer, msgSFVerBuf);
				// delete file list version
				msgSFVer->DeleteFileListVersion[0] = m_CurrentDelFileListVersion.GetVersion()[0];
				msgSFVer->DeleteFileListVersion[1] = m_CurrentDelFileListVersion.GetVersion()[1];
				msgSFVer->DeleteFileListVersion[2] = m_CurrentDelFileListVersion.GetVersion()[2];
				msgSFVer->DeleteFileListVersion[3] = m_CurrentDelFileListVersion.GetVersion()[3];
				// notice version
				msgSFVer->NoticeVersion[0] = m_CurrentNoticeVersion.GetVersion()[0];
				msgSFVer->NoticeVersion[1] = m_CurrentNoticeVersion.GetVersion()[1];
				msgSFVer->NoticeVersion[2] = m_CurrentNoticeVersion.GetVersion()[2];
				msgSFVer->NoticeVersion[3] = m_CurrentNoticeVersion.GetVersion()[3];

				m_pUpdateWinsocket->Write((char*)msgSFVerBuf, MSG_SIZE(MSG_PC_CONNECT_SINGLE_FILE_VERSION_CHECK));
			}
			else
			{
//				AtumMessageBox("������ ����Ǿ� ���� �ʰų� ���� ���Դϴ�.\n\n�׽�Ʈ �ð��� �ָ� 24�ð�,\n\n���� ����10�ú��� ����24�ñ����Դϴ�.");
				AtumMessageBox(STRERR_S_ATUMLAUNCHER_0005);
				EndDialog(-1);
			}
		}
		break;
	case CUpdateWinSocket::WS_CLOSED:
		{
			SAFE_DELETE(m_pUpdateWinsocket);
#ifdef _DEBUG
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0006);
#endif

			OnCancel();
		}
		break;
	case CUpdateWinSocket::WS_RECEIVED:
		{
			char * pPacket = NULL;
			int len,nType;
			m_pUpdateWinsocket->Read(&pPacket, len);

			if(pPacket)
			{
				nType = 0;
				memcpy(&nType, pPacket, SIZE_FIELD_TYPE_HEADER);

				switch(nType)
				{
				case T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK_OK:
					{
// 2006-05-03 by cmkwon, ���������� ��ó�� ��ȭ�鿡�� ó���Ѵ�.
// 						// Notice �ε�
// 						if (!ReadNoticeFile())
// 						{
// 							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0007);
// 							EndDialog(-1);
// 							return FALSE;
// 						}
//						DbgOut("	2007-07-13 by cmkwon, T_PC_CONNECT_SINGLE_FILE_VERSION_CHECK_OK\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 

						/////////////////////////////////////////////
						// Send Client Version
						INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
						msgVersion->ClientVersion[0] = m_CurrentVersion.GetVersion()[0];
						msgVersion->ClientVersion[1] = m_CurrentVersion.GetVersion()[1];
						msgVersion->ClientVersion[2] = m_CurrentVersion.GetVersion()[2];
						msgVersion->ClientVersion[3] = m_CurrentVersion.GetVersion()[3];
						m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));

						// �ϴ� ���α�
						SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0000);
					}
					break;
				case T_PC_CONNECT_SINGLE_FILE_UPDATE_INFO:
					{
						MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO *pMsgUpdate
							= (MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO*)(pPacket + SIZE_FIELD_TYPE_HEADER);
						// �������
						VersionInfo TmpDelVerion(pMsgUpdate->NewDeleteFileListVersion);
						if (TmpDelVerion != m_CurrentDelFileListVersion)
						{
							// delete file ó��
							if (m_bUpdateClientFile)
							{
								///////////////////////////////////////////////////////////////////////////////
								// 2007-01-08 by cmkwon, Http Update ó�� �߰�
								switch(pMsgUpdate->nAutoUpdateServerType)
								{
								case AU_SERVER_TYPE_HTTP:
									{
										ProcessDeleteFileListByHttp(pMsgUpdate);
									}
									break;
								default:
									{
										if (!ProcessDeleteFileList(pMsgUpdate))
										{
											// ��ȭ�� ���� ������ FTP�� �������� ���ϴ� ������ ������ �� �����Ƿ�,
											// �����ص� �׳� �ѱ��. 20041030, kelovon
											//OnCancel();
										}
									}
								}
							}
							m_CurrentDelFileListVersion = TmpDelVerion;
						}
// 2006-05-03 by cmkwon, ���������� ��ó�� ��ȭ�鿡�� ó���Ѵ�.
// 						VersionInfo TmpNoticeVerion(pMsgUpdate->NewNoticeVersion);
// 						if (TmpNoticeVerion != m_CurrentNoticeVersion)
// 						{
// 							// notice.txt�� �ٿ�ε����
// 							if (!ProcessNoticeFile(pMsgUpdate))
// 							{
// 								// ��ȭ�� ���� ������ FTP�� �������� ���ϴ� ������ ������ �� �����Ƿ�,
// 								// �����ص� �׳� �ѱ��. 20041030, kelovon
// 								//OnCancel();
// 							}
// 							m_CurrentNoticeVersion = TmpNoticeVerion;
// 						}
						
						// ������Ʈ���� ����
						((CAtumLauncherApp*)AfxGetApp())->WriteProfile();

// 2006-05-03 by cmkwon, ���������� ��ó�� ��ȭ�鿡�� ó���Ѵ�.
// 						// Notice �ε�
// 						if (!ReadNoticeFile())
// 						{
// 							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0007);
// 							EndDialog(-1);
// 							return FALSE;
// 						}

//						DbgOut("	2007-07-13 by cmkwon, T_PC_CONNECT_SINGLE_FILE_UPDATE_INFO\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 
						/////////////////////////////////////////////
						// Send Client Version
						INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
						msgVersion->ClientVersion[0] = m_CurrentVersion.GetVersion()[0];
						msgVersion->ClientVersion[1] = m_CurrentVersion.GetVersion()[1];
						msgVersion->ClientVersion[2] = m_CurrentVersion.GetVersion()[2];
						msgVersion->ClientVersion[3] = m_CurrentVersion.GetVersion()[3];
						m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));
						// �ϴ� ���α�
						SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0000);
					}
					break;
				case T_PC_CONNECT_VERSION_OK:
					{
//						DbgOut("	2007-07-13 by cmkwon, T_PC_CONNECT_VERSION_OK\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 
						m_bProcessingVersionUpdate = TRUE;
						EnableControls();
						NTStartNetworkCheck();		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ

#ifndef _DEBUG
						DeleteFile("AtumLauncher_dbg.exe");
#endif

#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
						// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - ���� ��ư ó��
						this->OnOk();
#endif
					}
					break;
				case T_PC_CONNECT_REINSTALL_CLIENT:
					{
						m_bProcessingVersionUpdate = TRUE;
						MSG_PC_CONNECT_REINSTALL_CLIENT *pReinstall
							= (MSG_PC_CONNECT_REINSTALL_CLIENT*)(pPacket + SIZE_FIELD_TYPE_HEADER);
						VersionInfo currentVersion;
						currentVersion.SetVersion(pReinstall->LatestVersion[0]
													, pReinstall->LatestVersion[1]
													, pReinstall->LatestVersion[2]
													, pReinstall->LatestVersion[3]);

#ifdef _ATUM_DEVELOP
						if (!m_bUpdateClientFile)
						{

							/////////////////////////////////////////////
							// Send Client Version
							INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
							msgVersion->ClientVersion[0] = pReinstall->LatestVersion[0];
							msgVersion->ClientVersion[1] = pReinstall->LatestVersion[1];
							msgVersion->ClientVersion[2] = pReinstall->LatestVersion[2];
							msgVersion->ClientVersion[3] = pReinstall->LatestVersion[3];
							m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));
							EnableControls();
							NTStartNetworkCheck();		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
							SetProgressGroupText("update completed");
							break;
						}
#endif
						CString tmpMsg;
						tmpMsg.Format(STRMSG_S_050930, STRMSG_S_GAMEHOMEPAGE_DOMAIN);
						tmpMsg += currentVersion.GetVersionString();
						AtumMessageBox(tmpMsg);
// 2005-09-30 by cmkwon
//						string tmpMsg = STRERR_S_ATUMLAUNCHER_0008;
//						tmpMsg += currentVersion.GetVersionString();
//						AtumMessageBox(tmpMsg.c_str());
						OnCancel();
					}
					break;
				case T_PC_CONNECT_UPDATE_INFO:
					{
						MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo
							= (MSG_PC_CONNECT_UPDATE_INFO*)(pPacket + SIZE_FIELD_TYPE_HEADER);

#ifdef _ATUM_DEVELOP
						if (!m_bUpdateClientFile)
						{
							/////////////////////////////////////////////
							// Send Client Version
							INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
							msgVersion->ClientVersion[0] = pMsgUpdateInfo->UpdateVersion[0];
							msgVersion->ClientVersion[1] = pMsgUpdateInfo->UpdateVersion[1];
							msgVersion->ClientVersion[2] = pMsgUpdateInfo->UpdateVersion[2];
							msgVersion->ClientVersion[3] = pMsgUpdateInfo->UpdateVersion[3];
							m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));
							EnableControls();
							NTStartNetworkCheck();		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
							SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0000);
							break;
						}
#endif

						// download update file
						switch(pMsgUpdateInfo->nAutoUpdateServerType)
						{
						case AU_SERVER_TYPE_HTTP:
							{
								if(FALSE == DownloadUpdateFileByHttp(pMsgUpdateInfo))
								{
									AtumMessageBox(STRERR_S_ATUMLAUNCHER_0009);
									ShellExecute(NULL, "open", STRMSG_S_GAMEHOMEPAGE_DOMAIN, NULL, NULL, SW_SHOWNORMAL);
									exit(0);
								}
							}
							break;
						default:
							{
								if(FALSE == DownloadUpdateFile(pMsgUpdateInfo))
								{
									AtumMessageBox(STRERR_S_ATUMLAUNCHER_0009);
									ShellExecute(NULL, "open", STRMSG_S_GAMEHOMEPAGE_DOMAIN, NULL, NULL, SW_SHOWNORMAL);
									exit(0);
								}
							}
						}
						m_msg_PC_CONNECT_UPDATE_INFO = *pMsgUpdateInfo;

// 2004-07-06, cmkwon OnUpdateFileDownloadOK()�Լ��� �̵�						
//						// extract update file
//						ExtractUpdateFile(pMsgUpdateInfo);
//
//						// update completed
//						VersionInfo OldVersion(pMsgUpdateInfo->OldVersion);
//						VersionInfo UpdateVersion(pMsgUpdateInfo->UpdateVersion);
//						char strBuffer[256];
//						sprintf(strBuffer, "update completed(%s -> %s)", OldVersion.GetVersionString(),
//							UpdateVersion.GetVersionString());
//						SetProgressGroupText(strBuffer);
//
//						// set current cliet version
//						m_CurrentVersion = UpdateVersion;
//
//						// On DownLoadGamefilesDone
//						OnDownLoadGamefilesDone(NULL, NULL);

					}
					break;
				case T_PC_CONNECT_LOGIN_OK:
					{
						MSG_PC_CONNECT_LOGIN_OK *pConnOK;
						pConnOK = (MSG_PC_CONNECT_LOGIN_OK*)(pPacket + SIZE_FIELD_TYPE_HEADER);

// 2009-04-23 by cmkwon, ���þ� Innova Frost �ӽ� �����ϱ� - �Ʒ��� ���� define ���� ó�� ��.
//#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1) && defined(_USING_INNOVA_FROST_)
// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - ���� �ҽ� �ּ� ó��
// 						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - SetUserName() ȣ�� ó��
// 						try
// 						{
// 							SetUserName((LPCSTR)m_szAccountName);
// 						}
// 						catch (std::runtime_error runErr)
// 						{
// 							CString strErr;
// 							strErr.Format("[Error] call SetUserName() error !! %s", runErr.what());
// 							AfxMessageBox(strErr);
// 							exit(0);
// 						}
// 						catch(...)
// 						{
// 							CString strErr;
// 							strErr.Format("[Error] call SetUserName() error !! unknown error(%d)", GetLastError());
// 							exit(0);
// 						}
// 						DbgOut("[090130] call SetUserName(%s)\r\n", m_szAccountName);
// 										
// 
// 						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - ChangeGameAddr() ȣ�� ó��
// 						struct in_addr laddr;
// 						int GameFServIP, GameFServPort, LocalFServIP, LocalFServPort;
// 						GameFServIP		= inet_addr(pConnOK->FieldServerIP);
// 						GameFServPort	= pConnOK->FieldServerPort;
// 
// 						try
// 						{
// 							ChangeGameAddr(GameFServIP, GameFServPort, LocalFServIP, LocalFServPort);
// 						}
// 						catch (std::runtime_error runErr)
// 						{
// 							CString strErr;
// 							strErr.Format("[Error] call FieldServer ChangeGameAddr() error !! %s", runErr.what());
// 							AfxMessageBox(strErr);
// 							exit(0);
// 						}
// 						catch(...)
// 						{
// 							CString strErr;
// 							strErr.Format("[Error] call FieldServer ChangeGameAddr() error !! unknown error(%d)", GetLastError());
// 							AfxMessageBox(strErr);
// 							exit(0);
// 						}
// 
// 						laddr.s_addr	= LocalFServIP;		
// 						STRNCPY_MEMSET(pConnOK->FieldServerIP, inet_ntoa(laddr), SIZE_MAX_IPADDRESS);
// 						pConnOK->FieldServerPort	= LocalFServPort;
// 
// 						int GameIMServIP, GameIMServPort, LocalIMServIP, LocalIMServPort;
// 						GameIMServIP	= inet_addr(pConnOK->IMServerIP);
// 						GameIMServPort	= pConnOK->IMServerPort;
// 
// 						try
// 						{
// 							ChangeGameAddr(GameIMServIP, GameIMServPort, LocalIMServIP, LocalIMServPort);
// 						}
// 						catch (std::runtime_error runErr)
// 						{
// 							CString strErr;
// 							strErr.Format("[Error] call IMServer ChangeGameAddr() error !! %s", runErr.what());
// 							AfxMessageBox(strErr);
// 							exit(0);
// 						}
// 						catch(...)
// 						{
// 							CString strErr;
// 							strErr.Format("[Error] call IMServer ChangeGameAddr() error !! unknown error(%d)", GetLastError());
// 							AfxMessageBox(strErr);
// 							exit(0);
// 						}
// 		
// 						laddr.s_addr	= LocalIMServIP;		
// 						STRNCPY_MEMSET(pConnOK->IMServerIP, inet_ntoa(laddr), SIZE_MAX_IPADDRESS);
// 						pConnOK->IMServerPort	= LocalIMServPort;						
						///////////////////////////////////////////////////////////////////////////////
						// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - 
						//DbgOut("[TEMP] 090710 frostSetUserName 1 \r\n");
						frostSetUserName((LPCSTR)m_szAccountName);
						//DbgOut("[TEMP] 090710 frostSetUserName 2 \r\n");
#endif // END - #if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)

						char szEncodedString[SIZE_MAX_PASSWORD_MD5_STRING];
						BYTE byPass[SIZE_MAX_PASSWORD_MD5];
						MD5 MD5_instance;
						
						char szTmPassword[1024];			// 2006-05-22 by cmkwon, ����� �߰� ��Ʈ�� ����
						MEMSET_ZERO(szTmPassword, 1024);
						wsprintf(szTmPassword, "%s%s", MD5_PASSWORD_ADDITIONAL_STRING, m_szPassword);
						MD5_instance.MD5Encode(szTmPassword, byPass);
						MD5_instance.MD5Binary2String(byPass, szEncodedString);

						// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 2�ܰ� ������ �����Ѵ�.
						m_szAccountName	= pConnOK->AccountName;

						char cmdLine[1024];		MEMSET_ZERO(cmdLine, 1024);
						//_chdir(".\\down");
						CString szTmpWindowDegree;
// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �Ʒ��� ���� ������
//						switch(m_nWindowDegreeReg)
//						{
//// 2007-07-24 by cmkwon, ��ó���� 800*600 �ػ� ���� - 
////						case WINDOW_DEGREE_800x600_LOW:			szTmpWindowDegree = "800 600 0";		break;
////						case WINDOW_DEGREE_800x600_MEDIUM:		szTmpWindowDegree = "800 600 1";		break;
////						case WINDOW_DEGREE_800x600_HIGH:		szTmpWindowDegree = "800 600 2";		break;
//						case WINDOW_DEGREE_1024x768_LOW:		szTmpWindowDegree = "1024 768 0";		break;
//						case WINDOW_DEGREE_1024x768_MEDIUM:		szTmpWindowDegree = "1024 768 1";		break;
//						case WINDOW_DEGREE_1024x768_HIGH:		szTmpWindowDegree = "1024 768 2";		break;
//						case WINDOW_DEGREE_1280x960_LOW:		szTmpWindowDegree = "1280 960 0";		break;
//						case WINDOW_DEGREE_1280x960_MEDIUM:		szTmpWindowDegree = "1280 960 1";		break;
//						case WINDOW_DEGREE_1280x960_HIGH:		szTmpWindowDegree = "1280 960 2";		break;
//						case WINDOW_DEGREE_1280x1024_LOW:		szTmpWindowDegree = "1280 1024 0";		break;
//						case WINDOW_DEGREE_1280x1024_MEDIUM:	szTmpWindowDegree = "1280 1024 1";		break;
//						case WINDOW_DEGREE_1280x1024_HIGH:		szTmpWindowDegree = "1280 1024 2";		break;
//						case WINDOW_DEGREE_1600x1200_LOW:		szTmpWindowDegree = "1600 1200 0";		break;
//						case WINDOW_DEGREE_1600x1200_MEDIUM:	szTmpWindowDegree = "1600 1200 1";		break;
//						case WINDOW_DEGREE_1600x1200_HIGH:		szTmpWindowDegree = "1600 1200 2";		break;
//						case WINDOW_DEGREE_W1280x800_LOW:		szTmpWindowDegree = "1280 800 0";		break;
//						case WINDOW_DEGREE_W1280x800_MEDIUM:	szTmpWindowDegree = "1280 800 1";		break;
//						case WINDOW_DEGREE_W1280x800_HIGH:		szTmpWindowDegree = "1280 800 2";		break;
//						case WINDOW_DEGREE_W1600x900_LOW:		szTmpWindowDegree = "1600 900 0";		break;
//						case WINDOW_DEGREE_W1600x900_MEDIUM:	szTmpWindowDegree = "1600 900 1";		break;
//						case WINDOW_DEGREE_W1600x900_HIGH:		szTmpWindowDegree = "1600 900 2";		break;
//
//						// 2007-08-23 by cmkwon, Wide �ػ� 1280x720(16:9) �߰� - 
//						case WINDOW_DEGREE_W1280x720_LOW:		szTmpWindowDegree = "1280 720 0";		break;
//						case WINDOW_DEGREE_W1280x720_MEDIUM:	szTmpWindowDegree = "1280 720 1";		break;
//						case WINDOW_DEGREE_W1280x720_HIGH:		szTmpWindowDegree = "1280 720 2";		break;
//						default:
//							{
//								szTmpWindowDegree = "1024 768 2";
//							}
//						}

						// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - ������
						int nCX, nCY, nDegree;
						if(FALSE == this->FindWindowResolutionByWindowDegree(&nCX, &nCY, &nDegree, (LPSTR)(LPCSTR)m_csWindowsResolutionReg))
						{
							nCX		= 1024;		nCY		= 768;		nDegree		= 2;	// 2007-12-28 by cmkwon, �⺻��
						}
						szTmpWindowDegree.Format("%d %d %d", nCX, nCY, nDegree);

						DBGOUT(" Resolution ==> %s\r\n", szTmpWindowDegree);

						///////////////////////////////////////////////////////////////////////////////
						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
						char szAppPath[1024];		MEMSET_ZERO(szAppPath, 1024);
						char szCmdParam[1024];		MEMSET_ZERO(szCmdParam, 1024);
						STRNCPY_MEMSET(szAppPath, CLIENT_EXEUTE_FILE_NAME, 1024);

#ifndef _ATUM_DEVELOP
						// Release��
						CString szAccountNameLow = g_szMGameID;
						szAccountNameLow.MakeLower();
// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
// 						sprintf(cmdLine, "%s %s %d %s %d %s %s %d %s INET %s %s %s %s"
// 							, CLIENT_EXEUTE_FILE_NAME
// 							, pConnOK->FieldServerIP, pConnOK->FieldServerPort
// 							, pConnOK->IMServerIP, pConnOK->IMServerPort
// 							, szAccountNameLow, szEncodedString
// 							, m_nWindowModeReg, szTmpWindowDegree,
// 							(LPCSTR)g_szMGameSeed, (LPCSTR)g_szMGameID, (LPCSTR)g_szMGameEncryptedID, (LPCSTR)g_szMGameEncryptedPWD);
						///////////////////////////////////////////////////////////////////////////////
						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
						sprintf(szCmdParam, "%s %d %s %d %s %s %d %s INET %s %s %s %s"
							, pConnOK->FieldServerIP, pConnOK->FieldServerPort
							, pConnOK->IMServerIP, pConnOK->IMServerPort
							, szAccountNameLow, szEncodedString
							, m_nWindowModeReg, szTmpWindowDegree,
							(LPCSTR)g_szMGameSeed, (LPCSTR)g_szMGameID, (LPCSTR)g_szMGameEncryptedID, (LPCSTR)g_szMGameEncryptedPWD);
						sprintf(cmdLine, "%s %s", szAppPath, szCmdParam);

	#if defined(SERVICE_TYPE_KOREAN_SERVER_2)		// 2006-10-02 by cmkwon

// 2008-01-22 by cmkwon, S_Exe2: ���� ���� ��ó��  ���������� ����
// 		#if defined(SERVICE_TYPE_KOREAN_SERVER_2) && !defined(_TEST_SERVER)
// 						// 2008-01-09 by cmkwon, Yedang_Kor_Main ���������� ��Ȱ��ȭ - �׻� Ǯ���� ����
// 						m_nWindowModeReg	= GAME_MODE_FULLSCREEN;
// 		#endif

						// 2008-01-08 by cmkwon, WindowMode �߰��� - �Ʒ��� ���� ����
						//sprintf(cmdLine, "%s %s %d %s %d %s",
						//	CLIENT_EXEUTE_FILE_NAME,
						//	pConnOK->FieldServerIP, pConnOK->FieldServerPort,
						//	pConnOK->IMServerIP, pConnOK->IMServerPort, szTmpWindowDegree);

// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
// 						sprintf(cmdLine, "%s %s %d %s %d %s %d", CLIENT_EXEUTE_FILE_NAME, pConnOK->FieldServerIP, pConnOK->FieldServerPort,
// 							pConnOK->IMServerIP, pConnOK->IMServerPort, szTmpWindowDegree, m_nWindowModeReg);
//
//						// 2007-05-17 by cmkwon, for���� ������
//						sprintf(&(cmdLine[strlen(cmdLine)]), " %s %s %s %s %s %s"
//							, g_szArrargv[1], g_szArrargv[2], g_szArrargv[3]
//							, g_szArrargv[4], g_szArrargv[5], g_szArrargv[6]);

						///////////////////////////////////////////////////////////////////////////////
						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
						sprintf(szCmdParam, "%s %d %s %d %s %d", pConnOK->FieldServerIP, pConnOK->FieldServerPort, pConnOK->IMServerIP, pConnOK->IMServerPort, szTmpWindowDegree, m_nWindowModeReg);
						sprintf(&(szCmdParam[strlen(szCmdParam)]), " %s %s %s %s %s %s"
							, g_szArrargv[1], g_szArrargv[2], g_szArrargv[3]
							, g_szArrargv[4], g_szArrargv[5], g_szArrargv[6]);
						sprintf(cmdLine, "%s %s", szAppPath, szCmdParam);

	#else

// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
// 						sprintf(cmdLine, "%s %s %d %s %d %s %s %d %s",
// 							CLIENT_EXEUTE_FILE_NAME,
// 							pConnOK->FieldServerIP, pConnOK->FieldServerPort,
// 							pConnOK->IMServerIP, pConnOK->IMServerPort,
// 							m_szAccountName, szEncodedString,
// 							m_nWindowModeReg, szTmpWindowDegree);
						///////////////////////////////////////////////////////////////////////////////
						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
 						sprintf(szCmdParam, "%s %d %s %d %s %s %d %s", pConnOK->FieldServerIP, pConnOK->FieldServerPort, pConnOK->IMServerIP, pConnOK->IMServerPort, m_szAccountName, szEncodedString, m_nWindowModeReg, szTmpWindowDegree);
						sprintf(cmdLine, "%s %s", szAppPath, szCmdParam);

	#endif // END - #if defined(SERVICE_TYPE_KOREAN_SERVER_2)		// 2006-10-02 by cmkwon
#else
						// ���߿�
// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
// 						sprintf(cmdLine, "%s %s %d %s %d %s %s %d %s DEVELOP",
// 							m_szExecutableBinaryReg,
// 							pConnOK->FieldServerIP, pConnOK->FieldServerPort,
// 							pConnOK->IMServerIP, pConnOK->IMServerPort,
// 							m_szAccountName + m_szCrocessSuffix, szEncodedString,
// 							m_nWindowModeReg, szTmpWindowDegree);
						///////////////////////////////////////////////////////////////////////////////
						// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
						sprintf(szCmdParam, "%s %d %s %d %s %s %d %s DEVELOP", pConnOK->FieldServerIP, pConnOK->FieldServerPort, pConnOK->IMServerIP, pConnOK->IMServerPort, m_szAccountName + m_szCrocessSuffix, szEncodedString, m_nWindowModeReg, szTmpWindowDegree);
						sprintf(cmdLine, "%s %s", szAppPath, szCmdParam);

#endif// end_#ifndef _ATUM_DEVELOP


#ifdef _ATUM_DEVELOP
						if (m_szExecutableBinaryReg.IsEmpty())
						{
							char buf[128];
							sprintf(buf, "%s %d %s %d %s %s %d %s DEVELOP",
												pConnOK->FieldServerIP, pConnOK->FieldServerPort,
												pConnOK->IMServerIP, pConnOK->IMServerPort,
												m_szAccountName, szEncodedString, m_nWindowModeReg, szTmpWindowDegree);
							CLoginSuccessDlg ldlg(buf);
							if (ldlg.DoModal() != IDOK)
							{
								return FALSE;
							}
							m_bProcessingVersionUpdate = TRUE;
							OnCancel();
							break;
						}
#endif
						if (m_szCrocessSuffix == "")
						{
							// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
							//ExecGame(cmdLine);
							ExecGame(cmdLine, szAppPath, szCmdParam);
						}
						else
						{
							// ũ�μ����� ���� ����
							ExecGameCrocess(cmdLine);
						}

						OnCancel();
					}
					break;
				case T_PC_CONNECT_GET_SERVER_GROUP_LIST_OK:
					{
						MSG_PC_CONNECT_GET_SERVER_GROUP_LIST_OK *pServerListOK
							= (MSG_PC_CONNECT_GET_SERVER_GROUP_LIST_OK*)(pPacket+SIZE_FIELD_TYPE_HEADER);

						if (pServerListOK->NumOfServerGroup <= 0)
						{
							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0010);
							OnCancel();
							return 0;
						}

						MEX_SERVER_GROUP_INFO_FOR_LAUNCHER *pArrMexServerGroup
							= ((MEX_SERVER_GROUP_INFO_FOR_LAUNCHER*)(pPacket + MSG_SIZE(MSG_PC_CONNECT_GET_SERVER_GROUP_LIST_OK)));

// 2005-01-01 by cmkwon, ������ ä���� �߰��ϸ鼭 sorting�� ������						
//						///////////////////////////////////////////////////////////////////////////////
//						// �������� 2���̻��̸� ȥ�⵵ ������ ���� �Ѵ�
//						if(pServerListOK->NumOfServerGroup >= 2)
//						{							
//							sort(&pArrMexServerGroup[0], &pArrMexServerGroup[pServerListOK->NumOfServerGroup]
//								, sort_MEX_SERVER_GROUP_INFO_FOR_LAUNCHER_By_Crowdedness());
//						}

						BOOL	bSelectedServerGroupName = FALSE;
						int		nIndexMinCrowdednessServerGroup = -1;
						int		nMinCrowdedness = 100;
						int		nCrowdedIndex = -1;
						///////////////////////////////////////////////////////////////////////////////
						// �������� ����Ʈ�� �߰��Ѵ�
						for (int i = 0; i < pServerListOK->NumOfServerGroup; i++)
						{
							MEX_SERVER_GROUP_INFO_FOR_LAUNCHER *pMexServerGroup
								= &pArrMexServerGroup[i];

							///////////////////////////////////////////////////////////////////////////////
							// ȥ�⵵ ������ ServerGroupName�� �߰��Ѵ�
							CString strTemp;
							COLORREF	fontColor;

							///////////////////////////////////////////////////////////////////////////////
							// ȥ�⵵ ������ �߰��� ServerGroupName�� List�� �߰��Ѵ�
							// 2006-05-02 by ispark, �޺��� ����
							if(0 >= pMexServerGroup->Crowdedness)
							{
								strTemp.Format(STRERR_S_ATUMLAUNCHER_0011, pMexServerGroup->ServerGroupName, STRING_SERVER_GROUP_NAME_DELIMIT);
								fontColor = RGB(180, 180, 180);
								nCrowdedIndex = -1; 
							}
							else
							{
								nCrowdedIndex = min(9, (int)(pMexServerGroup->Crowdedness)/10);
#if defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
								// 2008-07-24 by cmkwon, WinnerOnline_Tha CCU�� 80% �̻��̸� 100%�� �����ֱ�(K0000369) - 
								nCrowdedIndex = (nCrowdedIndex < 7) ? nCrowdedIndex : 9;
#endif
								strTemp.Format("%-16s%s", pMexServerGroup->ServerGroupName, STRING_SERVER_GROUP_NAME_DELIMIT);
								fontColor = RGB(255, 255, 255);
							}

							///////////////////////////////////////////////////////////////////////////////
							// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - m_vectServerGroupList �� �߰��Ѵ�.
							SSERVER_GROUP_FOR_LAUNCHER tmSerGroup;
							tmSerGroup.nIndex	= i;
							STRNCPY_MEMSET(tmSerGroup.szServerGroupName, pMexServerGroup->ServerGroupName, SIZE_MAX_SERVER_NAME);
							m_vectServerGroupList.push_back(tmSerGroup);
							
#ifdef SERVICE_TYPE_CHINESE_SERVER_1	// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� - �߱��� ȥ�⵵ �̹����� �׸��� �ʰ� ��Ʈ��ũ Ping �ӵ��� �����ش�
							m_ServerList->InsertItem(i, strTemp, pMexServerGroup->Crowdedness, DEF_COL, fontColor, nCrowdedIndex, this->NTGetPingAverageTime(), TRUE);
#else
							// 7/13/2006 by dgwoo
							m_ServerList->InsertItem(i, strTemp, pMexServerGroup->Crowdedness, DEF_COL, fontColor, nCrowdedIndex);
#endif
							///////////////////////////////////////////////////////////////////////////////
							// ������ ������ ServerGroupName�� ���Ѵ�
							if(FALSE == m_strServerGroupName.IsEmpty()
								&& 0 == strnicmp((LPSTR)(LPCSTR)m_strServerGroupName, pMexServerGroup->ServerGroupName, SIZE_MAX_SERVER_NAME)
								&& pMexServerGroup->Crowdedness > 0)
							{// Crowdedness�� 0�̸� ���� ���� ������

								// 7/13/2006 by dgwoo
								m_ServerList->SetCurSel(i);
								m_nOldSel					= i;		// 2007-06-21 by cmkwon, ������ ���� ���� ���� - ���õ� index�� �����Ѵ�.
								bSelectedServerGroupName = TRUE;
							}

							if(pMexServerGroup->Crowdedness > 0
								&& pMexServerGroup->Crowdedness < nMinCrowdedness)
							{
								nIndexMinCrowdednessServerGroup = i;
								nMinCrowdedness = pMexServerGroup->Crowdedness;
							}
						}
						
						if(FALSE == bSelectedServerGroupName)
						{
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
							// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - ���������� ��ȿ���� ������ �׳� ����
							AtumMessageBox(STRERR_S_ATUMLAUNCHER_0012);
							OnCancel();
							return 0;
#endif
							if(nIndexMinCrowdednessServerGroup == -1)
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0012);
								OnCancel();
							}
							// 7/13/2006 by dgwoo
							m_ServerList->SetCurSel(nIndexMinCrowdednessServerGroup);
							m_nOldSel					= nIndexMinCrowdednessServerGroup;		// 2007-06-21 by cmkwon, ������ ���� ���� ���� - ���õ� index�� �����Ѵ�.
						}						
					}
					break;

				case T_PC_CONNECT_NETWORK_CHECK_OK:		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
					{
						MSG_PC_CONNECT_NETWORK_CHECK_OK *pRMsg = (MSG_PC_CONNECT_NETWORK_CHECK_OK*)(pPacket + SIZE_FIELD_TYPE_HEADER);
						this->NTOnReceivedNetworkCheckOK(pRMsg->nCheckCount);
						m_ServerList->UpdateNetworkState(this->NTGetPingAverageTime());		// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
						m_ServerList->Invalidate();											// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
					}
					break;

				case T_PC_CONNECT_LOGIN_BLOCKED:
					{
						MSG_PC_CONNECT_LOGIN_BLOCKED *pLoginBlocked
							= (MSG_PC_CONNECT_LOGIN_BLOCKED*)(pPacket+SIZE_FIELD_TYPE_HEADER);

						char szTemp[1024];
						wsprintf(szTemp, STRMSG_S_050506
							, pLoginBlocked->szAccountName, pLoginBlocked->szBlockedReasonForUser
							, pLoginBlocked->atimeStart.GetDateTimeString(STRNBUF(SIZE_MAX_ATUM_DATE_TIME_STRING))
							, pLoginBlocked->atimeEnd.GetDateTimeString(STRNBUF(SIZE_MAX_ATUM_DATE_TIME_STRING)));
						AtumMessageBox(szTemp);
						OnCancel();
					}
					break;
				case T_ERROR:
					{
						MSG_ERROR *pRecvMsg;
						pRecvMsg = (MSG_ERROR*)(pPacket + SIZE_FIELD_TYPE_HEADER);

						char buf[1024];
						Err_t error = pRecvMsg->ErrorCode;

						DBGOUT(STRERR_S_ATUMLAUNCHER_0013, GetErrorString(pRecvMsg->ErrorCode), pRecvMsg->ErrorCode, "ST_PRE_SERVER", m_pUpdateWinsocket->m_szPeerIP);

						switch (error)
						{
						case ERR_COMMON_LOGIN_FAILED:
							{
								AtumMessageBox(STRMSG_060824_0000);
								GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
								((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetSel(0, -1);
							}
							break;
						case ERR_PROTOCOL_INVALID_PRESERVER_CLIENT_STATE:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0015);
								OnCancel();
							}
							break;
						case ERR_PROTOCOL_EMPTY_ACCOUNTNAME:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0016);
								GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
								((CEdit*)GetDlgItem(IDC_EDIT_ACCOUNT))->SetSel(0, -1);
							}
							break;
						case ERR_PROTOCOL_DUPLICATE_LOGIN:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0017);
								OnCancel();
							}
							break;
						case ERR_PROTOCOL_ALL_FIELD_SERVER_NOT_ALIVE:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0018);
								//OnCancel();
							}
							break;
						case ERR_PROTOCOL_IM_SERVER_NOT_ALIVE:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0019);
								//OnCancel();
							}
							break;
						case ERR_COMMON_SERVICE_TEMPORARILY_PAUSED:
							{
								static BOOL bMsgBox = FALSE;
								if(FALSE == bMsgBox)
								{
									bMsgBox = TRUE;
									AtumMessageBox(STRERR_S_ATUMLAUNCHER_0020);
									OnCancel();
								}
							}
							break;
						case ERR_PROTOCOL_LIMIT_GROUP_USER_COUNT:
							{
								AtumMessageBox(STRERR_S_ATUMLAUNCHER_0021);
								OnCancel();
							}
							break;
						case ERR_PROTOCOL_ACCOUNT_BLOCKED:
							{
								char szErrString[512];
								memset(szErrString, 0x00, 512);
								memcpy(szErrString, ((BYTE*)pRecvMsg) + sizeof(MSG_ERROR), pRecvMsg->StringLength);
								sprintf(buf, STRERR_S_ATUMLAUNCHER_0022, szErrString);
								AtumMessageBox(buf);
								OnCancel();
							}
							break;
						case ERR_COMMON_INVALID_CLIENT_VERSION:
							{
								AtumMessageBox(STRERR_061011_0000);		// 2006-10-11 by cmkwon, ����(STRERR_S_ATUMLAUNCHER_0023-->STRERR_061011_0000)
								OnCancel();
							}
							break;
						case ERR_DB_NO_SUCH_ACCOUNT:		// 2006-09-19 by cmkwon, ��ϵ��� ���� ������
							{
								AtumMessageBox(STRMSG_060824_0000);
							}
							break;
						case ERR_PERMISSION_DENIED:			// 2006-09-27 by cmkwon, ���� ������ �����ϴ�.
							{
								AtumMessageBox(STRMSG_060927_0000);		// 2006-09-27 by cmkwon, "���� ���� ���� ���Դϴ�. �ڼ��� ������ Ȩ�������� �����ϼ���."
								OnCancel();
							}
							break;
						case ERR_NO_SEARCH_CHARACTER:		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
						case ERR_DB_EXECUTION_FAILED:		// 2008-04-29 by cmkwon, ������ ���� DB�� �߰�(�ű� ���� ĳ���� ���� ���� �ý����߰�) - 
							{
								AtumMessageBox(STRMSG_080430_0001);		// 2008-04-30 by cmkwon, "�����Ͻ� ������ �ű� ĳ���� ������ ���ѵ� ���� �Դϴ�."
							}
							break;

						default:
							{
								sprintf(buf, STRERR_S_ATUMLAUNCHER_0024, GetErrorString(pRecvMsg->ErrorCode), pRecvMsg->ErrorCode);
								AtumMessageBox(buf);
								OnCancel();
							}
							break;
						}
					}
				default:
					{
					}
				}

				SAFE_DELETE(pPacket);
			}
		}
		break;
	}

	return 0;
}

BOOL CAtumLauncherDlg::DownloadUpdateFile(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
{
	if(m_pUpdateFTPManager){		return FALSE;}

	VersionInfo OldVersion(pMsgUpdateInfo->OldVersion);
	VersionInfo UpdateVersion(pMsgUpdateInfo->UpdateVersion);
	char szDownLoadFileName[256];
// 2005-12-23 by cmkwon
//	sprintf(szDownLoadFileName, "%s/%s_%s.zip",	pMsgUpdateInfo->FtpUpdateDir, OldVersion.GetVersionString(), UpdateVersion.GetVersionString());
	sprintf(szDownLoadFileName, "%s/%s_%s.zip",	pMsgUpdateInfo->FtpUpdateDownloadDir, OldVersion.GetVersionString(), UpdateVersion.GetVersionString());

	DbgOut("Updating game data file(%s) From %s:%d by FTP\r\n", szDownLoadFileName, pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort);

	m_pUpdateFTPManager = new CFTPManager;
	
	BOOL bRet = m_pUpdateFTPManager->ConnectToServer(pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort,
									pMsgUpdateInfo->FtpAccountName, pMsgUpdateInfo->FtpPassword);
	if (!bRet)
	{
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0025);		
		return FALSE;
	}

	HINTERNET hFile;
	int nFileSize = m_pUpdateFTPManager->GetFileSize(szDownLoadFileName, hFile);
	if (nFileSize == -1)
	{
		DbgOut(STRERR_S_ATUMLAUNCHER_0026, szDownLoadFileName);
// 2006-05-26 by cmkwon, FTP Server �ɼǿ� List �����ֱ� ������ �ȵǾ� ���� ���� �ִ�
// 		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0027);
// 		return FALSE;
		nFileSize		= 1000*1024*1024;			// 2008-11-27 by cmkwon, �⺻ 1000MBytes�� ������. // 2006-05-26 by cmkwon, �⺻ 100MBytes�� ������
	}

	m_progressCtrl.SetRange32(0, nFileSize);
	SetProgressGroupText((LPCSTR)(CString("updating from ") + OldVersion.GetVersionString()
							+ " to " + UpdateVersion.GetVersionString()));
	
	SetFTPUpdateState(UPDATE_STATE_DOWNLOADING);
	bRet = m_pUpdateFTPManager->DownloadFile(szDownLoadFileName, NULL, NULL, GetSafeHwnd());
	if (!bRet)
	{
		delete m_pUpdateFTPManager;
		m_pUpdateFTPManager = NULL;
		this->SetFTPUpdateState(UPDATE_STATE_INIT);
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0028);
		return FALSE;
	}

	return TRUE;
}

void CAtumLauncherDlg::ExtractUpdateFile(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
{
	VersionInfo OldVersion(pMsgUpdateInfo->OldVersion);
	VersionInfo UpdateVersion(pMsgUpdateInfo->UpdateVersion);
	char szUpdateFileName[256];
	sprintf(szUpdateFileName, "%s_%s.zip", OldVersion.GetVersionString(),
				UpdateVersion.GetVersionString());

	// extract zip file
	CZipArchive ZipOut;

	FILE* fp = NULL;
	errno_t no = fopen_s(&fp, szUpdateFileName, "rb");
	if (!no)
	{
		fclose(fp);
		// error
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0029);
		exit(0);
	}
	fclose(fp);

	ZipOut.Open(szUpdateFileName, CZipArchive::zipOpen);

	// 2010-04-28 by cmkwon, ��ó ��Ʈ�� ���� ����(K0002816) - 
	SetProgressGroupText((LPCSTR)(CString("extracting ") + szUpdateFileName));
	m_progressCtrl.SetRange32(0, ZipOut.GetCount());
	for (int i = 0; i < ZipOut.GetCount(); i++)
	{
		//if (!ZipOut.IsFileDirectory(i))
		if (!(ZipOut.GetFileInfo(i))->IsDirectory())
		{
			CZipFileHeader zipFileHeader;
			ZipOut.GetFileInfo(zipFileHeader, i);
			CString targetFileName = zipFileHeader.GetFileName();
			DWORD fileAttr = GetFileAttributes(targetFileName);
			if (fileAttr & FILE_ATTRIBUTE_READONLY != 0)
			{
				fileAttr = fileAttr & ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributes(targetFileName, fileAttr);
			}
		}

		ZipOut.ExtractFile(i, "./", true);
		m_progressCtrl.SetPos(i+1);
	}

	ZipOut.Close();

	DeleteFile(szUpdateFileName);

	return;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::DownloadUpdateFileByHttp(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
/// \brief		
/// \author		cmkwon
/// \date		2007-01-08 ~ 2007-01-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::DownloadUpdateFileByHttp(MSG_PC_CONNECT_UPDATE_INFO *pMsgUpdateInfo)
{
	if(m_pHttpManager){						return FALSE;}

	VersionInfo OldVersion(pMsgUpdateInfo->OldVersion);
	VersionInfo UpdateVersion(pMsgUpdateInfo->UpdateVersion);
	char szDownLoadFileName[SIZE_MAX_FTP_FILE_PATH];
	char szDownLoadFileFullPath[SIZE_MAX_FTP_FILE_PATH];

	sprintf(szDownLoadFileName, "%s_%s.zip", OldVersion.GetVersionString(), UpdateVersion.GetVersionString());
	sprintf(szDownLoadFileFullPath, "%s/%s", pMsgUpdateInfo->FtpUpdateDownloadDir, szDownLoadFileName);

	DbgOut("Updating game data file(%s) From %s:%d by Http\r\n", szDownLoadFileName, pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort);

	m_pHttpManager		= new CHttpManager;

	SetFTPUpdateState(UPDATE_STATE_DOWNLOADING);
	Err_t errCode = m_pHttpManager->DownloadFileByHttp(pMsgUpdateInfo->FtpIP, pMsgUpdateInfo->FtpPort, szDownLoadFileFullPath, szDownLoadFileName, TRUE, this->GetSafeHwnd());
	if (ERR_NO_ERROR != errCode)
	{
		SAFE_DELETE(m_pHttpManager);
		this->SetFTPUpdateState(UPDATE_STATE_INIT);
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0028);
		return FALSE;
	}

	SetProgressGroupText((LPCSTR)(CString("updating from ") + OldVersion.GetVersionString()	+ " to " + UpdateVersion.GetVersionString()));
	return TRUE;
}

// WPARAM: Socket descriptor
LONG CAtumLauncherDlg::OnAsyncSocketMessage(WPARAM wParam, LPARAM lParam)
{
	if ((SOCKET)wParam == m_PreSD)
		m_pUpdateWinsocket->OnAsyncEvent(lParam);
/*	else if ((SOCKET)wParam == m_FieldSD)
		m_pFieldWinsocket->OnAsyncEvent(lParam);*/

	return 0;
}

LONG CAtumLauncherDlg::OnDownLoadGamefilesDone(WPARAM wParam, LPARAM lParam)
{
	if (m_bCancelFlag)
	{
		return -1;
	}

	CString cstrVersion = m_CurrentVersion.GetVersionString();
	SetFileNumText((char*)(LPCTSTR)("VER " + cstrVersion));

	///////////////////////////////////////////////////////////////////////////
	// �ٿ�ε� �Ϸ��� ���� ���� �� �ٽ� CONNECT_VERSION ����
	((CAtumLauncherApp*)AfxGetApp())->WriteProfile();

	/////////////////////////////////////////////
	// Send Version
	INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_VERSION, T_PC_CONNECT_VERSION, msgVersion, msgVersionBuff);
	msgVersion->ClientVersion[0] = m_CurrentVersion.GetVersion()[0];
	msgVersion->ClientVersion[1] = m_CurrentVersion.GetVersion()[1];
	msgVersion->ClientVersion[2] = m_CurrentVersion.GetVersion()[2];
	msgVersion->ClientVersion[3] = m_CurrentVersion.GetVersion()[3];
	m_pUpdateWinsocket->Write(msgVersionBuff, MSG_SIZE(MSG_PC_CONNECT_VERSION));

	return 0;
}

void CAtumLauncherDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here

// 2009-11-19 by cmkwon, ���þ� AdminTool�� FrostLib �����ϱ� - 
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1) && defined(_USING_INNOVA_FROST_)
	///////////////////////////////////////////////////////////////////////////////
	// 2009-11-19 by cmkwon, ���þ� AdminTool�� FrostLib �����ϱ� - 
	frostFinalize();
#endif // END - #if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)

	SAFE_DELETE(m_pUpdateWinsocket);

	CWinSocket::SocketClean();
}

void CAtumLauncherDlg::OnOk()
{
	// TODO: Add your control notification handler code here
	if(m_SelectFlag)
	{
		UpdateData();
		// 7/13/2006 by dgwoo
		if (m_ServerList->GetCurSel() == LB_ERR
			|| m_ServerList->GetCount() < 1)
		{
			AtumMessageBox(STRMSG_S_ATUMLAUNCHER_0001);
			return;
		}

		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� -
		CString csWDegree;
		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->GetWindowText(csWDegree);
		if(csWDegree.IsEmpty())
		{
			AtumMessageBox(STRMSG_071228_0001);
			return;
		}



		// 2008-12-17 by ckPark ���þ� ����
		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - üũ ��ư�� Ȯ�� �Ѵ�.		
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		// ���þƴ� üũ�ڽ� ���¸� ��Ʈ�ѿ��� ���´�
		if(FALSE == m_ctrlCheckWindowMode.GetCheck())
#else
		if(FALSE == this->IsDlgButtonChecked(IDC_CHECK_WINDOWS_MODE))
#endif
		// end 2008-12-17 by ckPark ���þ� ����


		{
			m_nWindowModeReg		= GAME_MODE_FULLSCREEN;
		}
		else
		{
			m_nWindowModeReg		= GAME_MODE_WINDOW;
		}

		SendLogin(LOGIN_TYPE_DIRECT);
// 2007-03-06 by cmkwon, ������ �ҽ� ���ŷ� �ʿ� ����
//		//////////////////////////////////////////////////////////////////////
//		// Send Login
//#if defined(_ATUM_DEVELOP) || defined(_MASANG15_SERVER) || defined(_MASANG51_SERVER) || defined(_GLOBAL_ENG_SERVER) || defined(_VTC_VIET_SERVER) || defined(_KOREA_SERVER_2)
//		SendLogin(LOGIN_TYPE_DIRECT);
//#else
//		SendLogin(LOGIN_TYPE_MGAME);
//#endif// end_ATUM_DEVELOP

//		m_nServerGroupReg = m_nServer;
		m_szAccountName.MakeLower();
		m_szAccountNameReg = m_szAccountName;
		m_szPasswordReg = m_szPassword;
// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - �ʿ� ����
//		m_nWindowDegreeReg = m_nWindowDegree+3;		// 2007-07-24 by cmkwon, ��ó���� 800*600 �ػ� ���� - ���� ������Ʈ������ ����ϱ� ���ؼ�




		// 2008-12-17 by ckPark ���þ� ����
		// ���þƴ� ��Ʈ���� ��Ʈ�ѿ��� ���� ���´�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		m_csWindowsResolutionReg	= reinterpret_cast<char*>(m_ctrlComboWindowDegree.GetItemData(m_ctrlComboWindowDegree.GetCurSel()));
#else
		m_csWindowsResolutionReg	= csWDegree;	// 2007-12-27 by cmkwon, �������� ��� ��� �߰� -
#endif
		// end 2008-12-17 by ckPark ���þ� ����




		((CAtumLauncherApp*)AfxGetApp())->WriteProfile();

		// ���� ���� ��ư ������ ������ �� ����
		DisableControls();
		SetTimer(TIMERID_ENABLE_CONTROL, 2000, NULL);
	}
	else
	{
		AfxMessageBox(STRMSG_S_ATUMLAUNCHER_0001);
	}
}

BOOL CAtumLauncherDlg::SendLogin(BYTE i_nLoginType)
{
	INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_LOGIN, T_PC_CONNECT_LOGIN, msgLogin, msgLoginBuf);

	msgLogin->LoginType = i_nLoginType;
	if (i_nLoginType == LOGIN_TYPE_DIRECT)
	{
		// ũ�μ��� ������
		// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 
		//STRNCPY_MEMSET(msgLogin->AccountName, m_szAccountName + m_szCrocessSuffix, SIZE_MAX_ACCOUNT_NAME);
		STRNCPY_MEMSET(msgLogin->AccountName, m_szAccountName + m_szCrocessSuffix, SIZE_MAX_ORIGINAL_ACCOUNT_NAME);
	}
	else if (i_nLoginType == LOGIN_TYPE_MGAME)
	{		
		CString szTmpMGameID	= g_szMGameID;
		szTmpMGameID.MakeLower();
		m_szAccountName			= szTmpMGameID;
		// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 
		//STRNCPY_MEMSET(msgLogin->AccountName, szTmpMGameID, SIZE_MAX_ACCOUNT_NAME);
		STRNCPY_MEMSET(msgLogin->AccountName, szTmpMGameID, SIZE_MAX_ORIGINAL_ACCOUNT_NAME);
	}
	else
	{
		return FALSE;
	}

// 2009-06-09 by cmkwon, �Ϻ� Arario dbg�� ���� �����ϰ� ���� - �н����嵵 1111�� ����
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1) && defined(_DEBUG)
	m_szPassword			= "1111";
#endif // END - #if defined(SERVICE_TYPE_JAPANESE_SERVER_1) && defined(_DEBUG)

	if (i_nLoginType == LOGIN_TYPE_DIRECT)
	{
		MD5 MD5_instance;
		char szTmPassword[1024];			// 2006-05-22 by cmkwon, ����� �߰� ��Ʈ�� ����
		MEMSET_ZERO(szTmPassword, 1024);
		wsprintf(szTmPassword, "%s%s", MD5_PASSWORD_ADDITIONAL_STRING, m_szPassword);
		MD5_instance.MD5Encode(szTmPassword, msgLogin->Password);
	}
	else if (i_nLoginType == LOGIN_TYPE_MGAME)
	{
		MEMSET_ZERO(msgLogin->Password, SIZE_MAX_PASSWORD_MD5);
	}
	else
	{
		return FALSE;
	}

///////////////////////////////////////////////////////////////////////////////
// 2006-10-02 by cmkwon
#if defined(SERVICE_TYPE_KOREAN_SERVER_2) && !defined(_DEBUG)
	// 2008-10-08 by cmkwon, �븸 2�ܰ� ���� �ý��� ���� ����(email->uid) - 
	//STRNCPY_MEMSET(msgLogin->AccountName, g_szArrargv[1], SIZE_MAX_ACCOUNT_NAME);
	STRNCPY_MEMSET(msgLogin->AccountName, g_szArrargv[1], SIZE_MAX_ORIGINAL_ACCOUNT_NAME);
	MD5 MD5_instance;
	MD5_instance.MD5String2Binary(g_szArrargv[2], msgLogin->Password);

	///////////////////////////////////////////////////////////////////////////////
	// 2007-03-29 by cmkwon, ������Ű ����
	STRNCPY_MEMSET(msgLogin->WebLoginAuthKey, g_szArrargv[5], SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY);
#endif

	// 7/13/2006 by dgwoo
	int nCrowdedness = m_ServerList->GetCrowdedness(m_ServerList->GetCurSel());
	if(0 == nCrowdedness)
	{
		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0030);
		return FALSE;
	}

	CString szSelectedServerName;
// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - �Ʒ��� ���� ������
// 	///////////////////////////////////////////////////////////////////////////////
// 	// ������ ServerGroupName�� �����´�(ȥ�⵵�� ���ԵǾ��ִ�)
// 	// 7/13/2006 by dgwoo
// 	m_ServerList->GetTextString(m_ServerList->GetCurSel(), szSelectedServerName);
// 	///////////////////////////////////////////////////////////////////////////////
// 	// ������ ServerGroupName���� ȥ�⵵ ������ �����Ѵ�
// 	int nServerNameEndIndex = szSelectedServerName.FindOneOf(STRING_SERVER_GROUP_NAME_DELIMIT);
// 	szSelectedServerName.Delete(nServerNameEndIndex, szSelectedServerName.GetLength() - nServerNameEndIndex);
	if(FALSE == this->FindServerGroupName(&szSelectedServerName, m_ServerList->GetCurSel()))
	{// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - �ε����� �����׷� �̸��� �˻��Ѵ�.
		AtumMessageBox("Invalid ServerGroup");
		return FALSE;
	}
	
	///////////////////////////////////////////////////////////////////////////////
	// ServerGroupName�� �����Ѵ�
	m_strServerGroupName = szSelectedServerName;
	STRNCPY_MEMSET(msgLogin->FieldServerGroupName, szSelectedServerName, SIZE_MAX_SERVER_NAME);
	STRNCPY_MEMSET(msgLogin->PrivateIP, m_PrivateIP, SIZE_MAX_IPADDRESS);
// 2007-06-05 by cmkwon, �ʿ���� - �Ʒ��� ���� ������
//	if (i_nLoginType == LOGIN_TYPE_DIRECT)
//	{
//		msgLogin->MGameSEX = 0;
//		msgLogin->MGameYear = 0;
//	}
//	else if (i_nLoginType == LOGIN_TYPE_MGAME)
//	{
//		msgLogin->MGameSEX = atoi(g_szMGameSEX);
//		msgLogin->MGameYear = atoi(g_szMGameYear);
//	}
//	else
//	{
//		return FALSE;
//	}
	msgLogin->MGameSEX		= 0;							// 2007-06-05 by cmkwon, ���� - ��=0, ����=1, ����=2
	msgLogin->MGameYear		= this->m_nBirthYear;			// 2007-06-05 by cmkwon

// 2008-02-11 by cmkwon, Yedang_Global_Eng �ܺ� ���� ó�� - Yedang_Global_Eng �� �н����� ������ WebLoginAuthKey �� �����, Password �� ���󿡼��� �����
#if defined(SERVICE_TYPE_CHINESE_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_1)
	// 2007-07-03 by cmkwon, �߱� Yetime ��� ��ȣ MD5 ���� ���� - �ӽ÷� WebLoginAuthKey �ʵ� �����
	STRNCPY_MEMSET(msgLogin->WebLoginAuthKey, (LPCSTR)m_szPassword, SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY);	
#endif
//	DbgOut(" Password:%s", msgLogin->WebLoginAuthKey);

#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
	// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - MSG_PC_CONNECT_LOGIN�� SesstionKey�� �����Ѵ�.
	STRNCPY_MEMSET(msgLogin->WebLoginAuthKey, (LPCSTR)m_csSessionKey, SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY);
#endif

#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
	///////////////////////////////////////////////////////////////////////////////
	// 2010-04-26 by cmkwon, ���þ� Innva ����/���� �ý��� ���� - ��ȣȭ ���� ���� �н����带 �ѱ��.
	STRNCPY_MEMSET(msgLogin->WebLoginAuthKey, (LPCSTR)m_szPassword, SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY);
#endif

	return m_pUpdateWinsocket->Write(msgLoginBuf, MSG_SIZE(MSG_PC_CONNECT_LOGIN));
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::AtumMessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption/*=NULL*/, UINT nType/*=MB_OK*/)
/// \brief		
/// \author		cmkwon
/// \date		2006-04-20 ~ 2006-04-20
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::AtumMessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption/*=NULL*/, UINT nType/*=MB_OK*/)
{
// 2008-05-09 by cmkwon, EXE1, EXE2 ���� �±��� ������ ���� �ذ�
//#ifdef SERVICE_TYPE_VIETNAMESE_SERVER_1
#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
	WCHAR wcText[1024];
	MEMSET_ZERO(wcText, sizeof(wcText));
	WCHAR wcCaption[1024];
	MEMSET_ZERO(wcCaption, sizeof(wcCaption));
	// 2008-05-09 by cmkwon, CodePage ���� �߰� - 
	//MultiByteToWideChar(1258, 0, lpszText, strlen(lpszText)+1, wcText, sizeof(wcText)/sizeof(wcText[0]));
	MultiByteToWideChar(CODE_PAGE, 0, lpszText, strlen(lpszText)+1, wcText, sizeof(wcText)/sizeof(wcText[0]));

	char	szCaption[1024] = STRMSG_WINDOW_TEXT;
	if(lpszCaption)
	{
		strncpy(szCaption, lpszCaption, 1023);
	}
	// 2008-05-09 by cmkwon, CodePage ���� �߰� - 
	//MultiByteToWideChar(1258, 0, szCaption, strlen(szCaption)+1, wcCaption, sizeof(wcCaption)/sizeof(wcCaption[0]));
	MultiByteToWideChar(CODE_PAGE, 0, szCaption, strlen(szCaption)+1, wcCaption, sizeof(wcCaption)/sizeof(wcCaption[0]));
	return ::MessageBoxW(GetSafeHwnd(), wcText, wcCaption, nType);
#else

	if(lpszCaption)
	{
		return MessageBox(lpszText, lpszCaption, nType);
	}
	return MessageBox(lpszText, STRMSG_WINDOW_TEXT, nType);	
#endif	
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::ProcessDeleteFileListByHttp(MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO *pUpdateInfo)
/// \brief		
/// \author		cmkwon
/// \date		2007-01-08 ~ 2007-01-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::ProcessDeleteFileListByHttp(MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO *pUpdateInfo)
{
	char			szDelFileName[SIZE_MAX_FTP_FILE_PATH];
	CHttpManager	httpMan;
	Err_t			errCode;

	///////////////////////////////////////////////////////////////////////////////
	// 2007-01-08 by cmkwon, �ӽ� ���� �̸�
	STRNCPY_MEMSET(szDelFileName, "tmDelete.txt", SIZE_MAX_FTP_FILE_PATH);
	errCode = httpMan.DownloadFileByHttp(pUpdateInfo->FtpIP, pUpdateInfo->FtpPort, pUpdateInfo->DeleteFileListDownloadPath, szDelFileName);
	if(ERR_NO_ERROR != errCode)
	{
		return FALSE;
	}

#ifdef _DEBUG
		char	szDir[512];
		GetCurrentDirectory(512, szDir);
#endif

	///////////////////////////////////////////////////////////////////////////////		
	// ó��
	ifstream isDel;
	isDel.open(szDelFileName);
	if(false == isDel.is_open())
	{
		return FALSE;
	}
	char delFileLine[SIZE_MAX_FTP_FILE_PATH];
	bool bFileEndFlag = false;
	do
	{
		isDel.getline(delFileLine, SIZE_MAX_FTP_FILE_PATH);
		bFileEndFlag = isDel.eof();
		if(bFileEndFlag)
		{
			break;
		}

		// 0x0D(CR)�� �������� ���� ��� ������
		if (delFileLine[strlen(delFileLine)-1] == 0x0D)
		{
			delFileLine[strlen(delFileLine)-1] = '\0';
		}

		if (delFileLine[0] == '#')
		{// comment��

			continue;
		}

		::DeleteFile(delFileLine);
		SetLastError(0);				// 2007-01-08 by cmkwon
	}while(false == bFileEndFlag);
	isDel.close();

	///////////////////////////////////////////////////////////////////////////////
	// 2007-01-08 by cmkwon, �ӽ� ������ �����Ѵ�
	::DeleteFile(szDelFileName);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::MoveWindow2Center(void)
/// \brief		// 2007-09-07 by cmkwon, ��Ʈ�� ��ó �������̽� ���� -
/// \author		cmkwon
/// \date		2007-09-07 ~ 2007-09-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::MoveWindow2Center(void)
{
	int nWidth	= EXE2_LAUNCHER_BG_SIZE_X + 6;
	int nHeight	= EXE2_LAUNCHER_BG_SIZE_Y + 6;

	LONG x,y;
	x=LONG((GetSystemMetrics(SM_CXSCREEN)-nWidth)/2); 
	y=LONG((GetSystemMetrics(SM_CYSCREEN)-nHeight)/2);
	
	MoveWindow(x, y, nWidth, nHeight, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::PushCharFromScreenKeyboard(char i_cPushChar)
/// \brief		// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
/// \author		cmkwon
/// \date		2007-09-11 ~ 2007-09-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::PushCharFromScreenKeyboard(char i_cPushChar)
{
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	if(NULL == m_pInputEditFromScreenKeyboard)
	{
		m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_ACCOUNT);
	}

	CString strCurText, strResultText;
	m_pInputEditFromScreenKeyboard->GetWindowText(strCurText);
	strResultText.Format("%s%c", strCurText, i_cPushChar);
	m_pInputEditFromScreenKeyboard->SetWindowText(strResultText);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::DeleteCharFromScreenKeyboard(void)
/// \brief		// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� -
/// \author		cmkwon
/// \date		2007-09-11 ~ 2007-09-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::DeleteCharFromScreenKeyboard(void)
{
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	if(NULL == m_pInputEditFromScreenKeyboard)
	{
		m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_ACCOUNT);
	}

	CString strCurText;
	m_pInputEditFromScreenKeyboard->GetWindowText(strCurText);
	if(strCurText.IsEmpty())
	{
		return;
	}
	strCurText.Delete(strCurText.GetLength()-1);
	m_pInputEditFromScreenKeyboard->SetWindowText(strCurText);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::HideScreenKeyboardByScreenKeyboardWindow(void)
/// \brief		// 2007-09-18 by cmkwon, ȭ��Ű���� ���� - 
/// \author		cmkwon
/// \date		2007-09-18 ~ 2007-09-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::HideScreenKeyboardByScreenKeyboardWindow(void)
{
	m_bHideScreenKeyboardByScreenKeyboardWindow	= TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::FindWindowResolutionByWindowDegree(int *o_pnCX, int *o_pnCY, int *o_pnDegree, char *i_szWindowDegreeName)
/// \brief		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - CAtumLauncherDlg::FindWindowResolutionByWindowDegree() �߰�
/// \author		cmkwon
/// \date		2007-12-28 ~ 2007-12-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::FindWindowResolutionByWindowDegree(int *o_pnCX, int *o_pnCY, int *o_pnDegree, char *i_szWindowDegreeName)
{
	*o_pnCX		= 0;
	*o_pnCY		= 0;
	*o_pnDegree	= 0;

	for(int i=0; g_pWindowDegreeList[i].szWindowDegreeName != NULL; i++)
	{
		if(0 == strncmp(g_pWindowDegreeList[i].szWindowDegreeName, i_szWindowDegreeName, SIZE_MAX_WINDOW_DEGREE_NAME))
		{
			*o_pnCX		= g_pWindowDegreeList[i].nCX;
			*o_pnCY		= g_pWindowDegreeList[i].nCY;
			*o_pnDegree	= g_pWindowDegreeList[i].nDegree;
			return TRUE;
		}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::InsertWindowDegreeList(CComboBox *i_pComboBox, BOOL i_bWindowsMode)
/// \brief		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - CAtumLauncherDlg::InsertWindowDegreeList() �߰�
/// \author		cmkwon
/// \date		2007-12-28 ~ 2007-12-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::InsertWindowDegreeList(CComboBox *i_pComboBox, BOOL i_bWindowsMode)
{
	i_pComboBox->ResetContent();	// 2007-12-28 by cmkwon, ��� ������ �ʱ�ȭ

	int nCXScreen = GetSystemMetrics(SM_CXSCREEN);
	int nCYScreen = GetSystemMetrics(SM_CYSCREEN);

	int nInsertedCnts = 0;
	for(int i=0; g_pWindowDegreeList[i].szWindowDegreeName != NULL; i++)
	{
		if(FALSE == this->IsSupportedResolution(g_pWindowDegreeList[i].nCX, g_pWindowDegreeList[i].nCY))
		{// 2008-01-03 by cmkwon, �����ϴ� �ػ� ����Ʈ�� �����ֱ� - �������� �ʴ� �ػ󵵴� �������� �ȴ´�
			continue;
		}

		if( FALSE == i_bWindowsMode
			|| (nCXScreen >= g_pWindowDegreeList[i].nCX	&& nCYScreen >= g_pWindowDegreeList[i].nCY) )
		{
			i_pComboBox->AddString(g_pWindowDegreeList[i].szWindowDegreeName);



			// 2008-12-17 by ckPark ���þ� ����
			// ���þƴ� ��Ʈ���� ��Ʈ�ѿ��� ���� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
			i_pComboBox->SetItemData(i, (DWORD)(g_pWindowDegreeList[i].szWindowDegreeName));
#endif
			// end 2008-12-17 by ckPark ���þ� ����



			nInsertedCnts++;
		}
	}



	// 2008-12-17 by ckPark ���þ� ����
	// �޺��ڽ� ���Ž� �ٽ� �ѹ� �׸���
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	i_pComboBox->Invalidate(TRUE);
#endif
	// end 2008-12-17 by ckPark ���þ� ����




	return nInsertedCnts;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::FindWindowDegreeComboBoxIndex(CComboBox *i_pComboBox, char *i_szWindowDegreeName)
/// \brief		// 2007-12-27 by cmkwon, �������� ��� ��� �߰� - CAtumLauncherDlg::FindWindowDegreeComboBoxIndex() �߰�
/// \author		cmkwon
/// \date		2007-12-28 ~ 2007-12-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::FindWindowDegreeComboBoxIndex(CComboBox *i_pComboBox, char *i_szWindowDegreeName)
{
	int nItemCnts = i_pComboBox->GetCount();
	for(int i=0; i < nItemCnts; i++)
	{
		CString csWDegree;

		
		
		// 2008-12-17 by ckPark ���þ� ����
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
		csWDegree = (char*)(i_pComboBox->GetItemDataPtr(i));
#else
		i_pComboBox->GetLBText(i, csWDegree);
#endif
		// end 2008-12-17 by ckPark ���þ� ����




		if(0 == csWDegree.Compare(i_szWindowDegreeName))
		{
			return i;
		}
	}

	return -1;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::InitSupportedWindowResolutionList(void)
/// \brief		// 2008-01-03 by cmkwon, �����ϴ� �ػ� ����Ʈ�� �����ֱ� - CAtumLauncherDlg::InitSupportedWindowResolutionList() �߰�
/// \author		cmkwon
/// \date		2008-01-03 ~ 2008-01-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::InitSupportedWindowResolutionList(void)
{
 	///////////////////////////////////////////////////////////////////////////////
 	// 2008-06-12 by cmkwon, �ӽ� üũ��, ���� �ػ� �α� ���Ϸ� ���� - �ʿ� ������� �ּ����� ó��
// 	BOOL bSaveFile	= TRUE;
// 	CSystemLogManager resultLog;
// 	if(FALSE == resultLog.InitLogManger(TRUE, "LauncherLog", "./"))
// 	{
// 		bSaveFile	= FALSE;
// 	}

	DEVMODE devMode;
	INT32 modeExist;
	for (int i=0; ;i++) 
	{
		modeExist = EnumDisplaySettings(NULL, i, &devMode);
		if (!modeExist) 
		{
			break;
		}

		
// 2008-06-12 by cmkwon, �ӽ� üũ��, ���� �ػ� �α� ���Ϸ� ����
// 		if(bSaveFile)
// 		{
// 			// 2008-05-23 by cmkwon, üũ��
// 			//DbgOut("Resolution Idx(%3d) %4d x %4d , BitsPerPel(%2d) Frequency(%3d)\r\n", i, devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel, devMode.dmDisplayFrequency);
// 			char szResult[2048];
// 			MEMSET_ZERO(szResult, 2048);
// 			sprintf(szResult, "Resolution Idx(%3d) %4d x %4d , BitsPerPel(%2d) Frequency(%3d)\r\n", i, devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel, devMode.dmDisplayFrequency);
// 			resultLog.WriteSystemLog(szResult);
// 		}

// 2008-10-31 by cmkwon, ��ó(Luncher)���� �ػ� üũ�� �ȼ��� üũ�� ����(�����Ʈ�� üũ���� ����) - üũ �ʿ� ����
//		// 2008-06-12 by cmkwon, Win98, Win98ME ���� �ػ� 1���� ������ �ʴ� ���� ����(K0000227) - win98, win98ME ������ dmDisplayFrequency �� 0���� ���ϵǰ� ����.
//		if( 32 != devMode.dmBitsPerPel
//			|| (0 != devMode.dmDisplayFrequency && 60 != devMode.dmDisplayFrequency) )
//		{
//			continue;
//		}

		m_vectSupportedResolutionList.push_back(devMode);
	}

	return m_vectSupportedResolutionList.size();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::IsSupportedResolution(int i_nWidth, int i_nHeight)
/// \brief		// 2008-01-03 by cmkwon, �����ϴ� �ػ� ����Ʈ�� �����ֱ� - CAtumLauncherDlg::IsSupportedResolution() �߰�
/// \author		cmkwon
/// \date		2008-01-03 ~ 2008-01-03
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::IsSupportedResolution(int i_nWidth, int i_nHeight)
{
	int nCnts = m_vectSupportedResolutionList.size();

	for(int i=0; i < nCnts; i++)
	{
		DEVMODE *pDevMode = &(m_vectSupportedResolutionList[i]);
		if(pDevMode->dmPelsWidth == i_nWidth
			&& pDevMode->dmPelsHeight == i_nHeight)
		{
			return TRUE;
		}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::FindServerGroupName(CString *o_pcsServerGroupName, int i_nFindIndex)
/// \brief		// 2008-02-14 by cmkwon, ��ó���� �����׷� ���� ������ ���� ���࿡ ������ ������ ���� - CAtumLauncherDlg::FindServerGroupName() �߰�
/// \author		cmkwon
/// \date		2008-02-14 ~ 2008-02-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::FindServerGroupName(CString *o_pcsServerGroupName, int i_nFindIndex)
{
	o_pcsServerGroupName->Empty();
	int i = 0;
	for(i=0; i < m_vectServerGroupList.size(); i++)
	{
		if(i_nFindIndex == m_vectServerGroupList[i].nIndex)
		{
			*o_pcsServerGroupName = m_vectServerGroupList[i].szServerGroupName;
			return TRUE;
		}
	}
	return FALSE;
}





/*
BOOL CAtumLauncherDlg::SetCurrentClientVersion()
{
	const int SIZE_BUFF = 512;
	char buff[SIZE_BUFF];
	char *token;
	char seps[] = " \t";

	ifstream fin;

	CString cstrVersionFile = CLIENT_DOWNLOAD_DIR;
	cstrVersionFile += CLIENT_VERSION_FILE_NAME;
	fin.open((LPCTSTR)cstrVersionFile);

	if (! fin.is_open())
	{
#ifdef _ATUM_DEVELOP
		m_CurrentVersion.SetVersion(0, 0, 0, 0);
		return TRUE;
#else // _ATUM_DEVELOP
		return FALSE;
#endif // _ATUM_DEVELOP
	}

	fin.getline(buff, SIZE_BUFF);

	token = strtok(buff, seps);

	m_CurrentVersion.SetVersion(token);

	fin.close();

	return TRUE;
}
*/


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::NTStartNetworkCheck(void)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ 
/// \author		cmkwon
/// \date		2007-06-18 ~ 2007-06-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::NTStartNetworkCheck(void)
{
	if(NULL == m_pUpdateWinsocket
		|| FALSE == m_pUpdateWinsocket->IsConnected()
		|| -1 != m_nCurNetworkCheckCount)
	{
		return FALSE;
	}


	// 2007-06-18 by cmkwon, �ʱ�ȭ
	m_dwSumPacketTickGap		= 0;
	m_dwNetworkCheckSendTick	= timeGetTime();

	INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_NETWORK_CHECK, T_PC_CONNECT_NETWORK_CHECK, pNetCheck, SendBuf);
	pNetCheck->nCheckCount		= m_nCurNetworkCheckCount;	
	m_pUpdateWinsocket->Write(SendBuf, MSG_SIZE(MSG_PC_CONNECT_NETWORK_CHECK));
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::NTOnReceivedNetworkCheckOK(int i_nCheckCount)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
/// \author		cmkwon
/// \date		2007-06-18 ~ 2007-06-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::NTOnReceivedNetworkCheckOK(int i_nCheckCount)
{
	if(NULL == m_pUpdateWinsocket
		|| FALSE == m_pUpdateWinsocket->IsConnected()
		|| m_nCurNetworkCheckCount != i_nCheckCount)
	{
		return NTGetPingAverageTime();
	}
	
	DWORD dwCurTick				= timeGetTime();

	m_nCurNetworkCheckCount++;
	m_dwSumPacketTickGap		+= dwCurTick - m_dwNetworkCheckSendTick;

	Sleep(5);		// 2007-06-19 by cmkwon, �ణ�� �ð����� �д�

	m_dwNetworkCheckSendTick	= timeGetTime();

	if(m_nMaxNetworkCheckCount <= m_nCurNetworkCheckCount)
	{
		return NTGetPingAverageTime();
	}
	INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_NETWORK_CHECK, T_PC_CONNECT_NETWORK_CHECK, pNetCheck, SendBuf);
	pNetCheck->nCheckCount		= m_nCurNetworkCheckCount;	
	m_pUpdateWinsocket->Write(SendBuf, MSG_SIZE(MSG_PC_CONNECT_NETWORK_CHECK));

	return NTGetPingAverageTime();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CAtumLauncherDlg::NTGetPingAverageTime(void)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
/// \author		cmkwon
/// \date		2007-06-19 ~ 2007-06-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumLauncherDlg::NTGetPingAverageTime(void)
{
	if(0 >= m_nCurNetworkCheckCount)
	{// 2007-06-19 by cmkwon, ���ۻ��°� �ƴϰų� ó�� ��Ŷ�� ���� ���� ���� �ϰ��

		return 0;		// 2007-06-21 by cmkwon, ��� Ping �ӵ��� �����ϵ��� ������ - 
	}

	DWORD dwAverageTick = m_dwSumPacketTickGap/m_nCurNetworkCheckCount;

// 2007-06-21 by cmkwon, ��� Ping �ӵ��� �����ϵ��� ������
//	const int nBestStateTick	= 100;
//	const int nWorstStateTick	= 300;
//	if(dwAverageTick <= nBestStateTick)
//	{
//		nRetState = 100;
//	}
//	else if(dwAverageTick >= nWorstStateTick)
//	{
//		nRetState = 1;
//	}
//	else
//	{
//		nRetState = 100 - ( 100 * (dwAverageTick-nBestStateTick) )/(nWorstStateTick - nBestStateTick);
//	}
//	

// 2007-07-13 by cmkwon, �ʿ� ����
//	DbgOut("	 AverageTickGap[%8d] <== Count(%d), SumTickGap(%8d)\r\n"
//		, dwAverageTick, m_nCurNetworkCheckCount, m_dwSumPacketTickGap);

	return dwAverageTick;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumLauncherDlg::NTCheckTimeOver(DWORD *o_pdwPingTime)
/// \brief		// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ
/// \author		cmkwon
/// \date		2007-06-19 ~ 2007-06-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumLauncherDlg::NTCheckTimeOver(DWORD *o_pdwPingTime)
{
	if(0 > m_nCurNetworkCheckCount
		|| m_nMaxNetworkCheckCount <= m_nCurNetworkCheckCount)
	{
		return FALSE;
	}

	DWORD dwCurTick				= timeGetTime();
	if(TICKGAP_NETWORK_STATE_WORST_PING_TICK > dwCurTick - m_dwNetworkCheckSendTick)
	{// 2007-06-19 by cmkwon, ó���� �ʿ� �����Ƿ� �׳� ���� ���¸� ����
		*o_pdwPingTime = NTGetPingAverageTime();
	}
	else
	{
		// 2007-06-19 by cmkwon, ���� ��Ŷ�� �ʱ�ȭ �ϰ� ���� ��Ŷ ����
		*o_pdwPingTime = NTOnReceivedNetworkCheckOK(m_nCurNetworkCheckCount);
	}

	return TRUE;
}


char* CAtumLauncherDlg::GetFileName(char *szFullPathName, char *szFileName)
{
	char *token;
	char seps[] = "/";
	int len = strlen(szFullPathName);

	strcpy(szFileName, szFullPathName);

	token = strtok(szFileName, seps);
	len -= strlen(token);

	while( len > 7 )
	{
		token = strtok(NULL, seps);
		len -= strlen(token);
	}

	STRNCPY_MEMSET(szFileName, token, SIZE_MAX_FTP_FILE_PATH);

	return szFileName;
}

// devide���ڸ� ���� ����Ʈ�� �ִ´�.
BOOL CAtumLauncherDlg::Tokenizer(CList <CString, CString&>& lsString, CString strMsg, TCHAR devide)
{
	if( strMsg.IsEmpty() ) return FALSE;
	int nStart = 0;
	int pos;
	if( strMsg[strMsg.GetLength()-1] != devide )
		strMsg += devide;
	pos = strMsg.Find( devide, nStart );
	if( pos == -1)
		lsString.AddTail( strMsg );
	while( (pos = strMsg.Find( devide, nStart )) != -1 )	{
		lsString.AddTail( strMsg.Mid( nStart, pos - nStart ) );
		nStart = pos+1;
	}
	return TRUE;
}

int CAtumLauncherDlg::CreateDirectory(CString strParent, CList<CString, CString&> &lsDir)
{
	POSITION pos = lsDir.GetHeadPosition();
	strParent += lsDir.GetNext(pos);
	if(pos)// �������� ���丮�� �ƴ� ������ ����
	{
		CFileFind finder;
		if(finder.FindFile(strParent))
		{

		    finder.FindNextFile();
			if(!finder.IsDirectory())
			{
				DeleteFile(strParent); // ���Ϸ� �����ϸ� �����.
				if(!::CreateDirectory(strParent,NULL))
					return -1;
			}
		} else
			if(!::CreateDirectory(strParent,NULL))
				return -1;

		lsDir.GetPrev(pos);
		lsDir.RemoveAt(pos);
		strParent += '/';
		if(CreateDirectory(strParent,lsDir)==-1)
			return -1;
	}
	return 0;

}

void CAtumLauncherDlg::SetProgressRange(int up)
{
	m_progressCtrl.SetRange32(0, up);
}

void CAtumLauncherDlg::SetProgressPos(int pos)
{
	m_progressCtrl.SetPos(pos);
}

void CAtumLauncherDlg::SetFileNumText(char* str)
{
	CWnd *pWndStatus = GetDlgItem(IDC_DOWNLOAD_FILENUM);
// 2007-09-11 by cmkwon, �Ʒ��� ���� ������
//	InvalidateRect(CRect(90,579,190,592),true);
	InvalidateRect(CRect(EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X,EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y,EXE2_BG_DOWNLOAD_FILE_STATIC_POS_X + EXE2_BG_DOWNLOAD_FILE_STATIC_WIDTH,EXE2_BG_DOWNLOAD_FILE_STATIC_POS_Y+EXE2_BG_DOWNLOAD_FILE_STATIC_HEIGHT),true);
	
	pWndStatus->SetWindowText(str);
}

void CAtumLauncherDlg::SetProgressGroupText(const char* str)
{
	//ysw : ����
	CWnd *pWndStatus = GetDlgItem(IDC_FILE_INFO);
	// 7/10/2006 by dgwoo �۾��� �ܻ��� ���°��� �������� �κ�.

// 2007-09-11 by cmkwon, �Ʒ��� ���� ������
//	InvalidateRect(CRect(190,579,480, 592),true);
	InvalidateRect(CRect(EXE2_BG_UPDATE_INFO_STATIC_POS_X,EXE2_BG_UPDATE_INFO_STATIC_POS_Y,EXE2_BG_UPDATE_INFO_STATIC_POS_X+EXE2_BG_UPDATE_INFO_STATIC_WIDTH, EXE2_BG_UPDATE_INFO_STATIC_POS_Y+EXE2_BG_UPDATE_INFO_STATIC_HEIGHT),true);
	
	CPaintDC dc(this);
	CBitmap *oldbitmap;
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	oldbitmap = (CBitmap *)memDC.SelectObject(&m_BackGround);
	dc.BitBlt(EXE2_BG_UPDATE_INFO_STATIC_POS_X,EXE2_BG_UPDATE_INFO_STATIC_POS_Y,EXE2_BG_UPDATE_INFO_STATIC_WIDTH,EXE2_BG_UPDATE_INFO_STATIC_HEIGHT, &memDC,EXE2_BG_UPDATE_INFO_STATIC_POS_X,EXE2_BG_UPDATE_INFO_STATIC_POS_Y,SRCCOPY);
	memDC.SelectObject(oldbitmap);
	memDC.DeleteDC();
	
	WCHAR wcText[1024]; 
	MEMSET_ZERO(wcText, sizeof(wcText)); 
	// 2008-05-09 by cmkwon, CodePage ���� �߰� - 
	//MultiByteToWideChar(1258, 0, str, strlen(str)+1, wcText, sizeof(wcText)/sizeof(wcText[0])); 
	MultiByteToWideChar(CODE_PAGE, 0, str, strlen(str)+1, wcText, sizeof(wcText)/sizeof(wcText[0])); 
	::SetWindowTextW(pWndStatus->GetSafeHwnd(), wcText);
}


void CAtumLauncherDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	m_bCancelFlag = TRUE;
	if (!m_bProcessingVersionUpdate)
	{
//		AtumMessageBox("Operation Canceled!");
	}

	CDialog::OnCancel();
}

void CAtumLauncherDlg::DisableControls()
{
	m_bControlEnabled = FALSE;

	GetDlgItem(IDC_EDIT_ACCOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDGO)->EnableWindow(FALSE);
	m_KbcGO.SetButtonDisable();
	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(FALSE);	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� ����
	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->EnableWindow(FALSE);			// 2008-01-17 by cmkwon, �������� ���� �����ϱ� - ���� ����

	m_ctlBtnRememberID.EnableWindow(FALSE);			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - üũ�ڽ� ��ġ

	//ysw : ����
//	GetDlgItem(IDC_DECA_SERVER)->EnableWindow(FALSE);
//	GetDlgItem(IDC_BATTALUS_SERVER)->EnableWindow(FALSE);
//	GetDlgItem(IDC_SHARRINE_SERVER)->EnableWindow(FALSE);
//	GetDlgItem(IDC_PHILON_SERVER)->EnableWindow(FALSE);


	SendDlgItemMessage(IDOK, BM_SETSTYLE, BS_PUSHBUTTON, (LONG)TRUE);
	SendDlgItemMessage(IDCANCEL, BM_SETSTYLE, BS_DEFPUSHBUTTON, (LONG)TRUE);
	GetDlgItem(IDCANCEL)->SetFocus();
}

void CAtumLauncherDlg::EnableControls()
{
//	DbgOut("	2007-07-13 by cmkwon, 111\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 
	m_bControlEnabled = TRUE;

	int nLower, nUpper;
	m_progressCtrl.GetRange(nLower, nUpper);
	m_progressCtrl.SetPos(nUpper);

	GetDlgItem(IDC_EDIT_ACCOUNT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDGO)->EnableWindow(TRUE);
	m_KbcGO.SetButtonEnable();
// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� ����
//	if (m_nWindowModeReg == GAME_MODE_WINDOW)
//	{
//		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(FALSE);
//	}
//	else
//	{
//		GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(TRUE);
//	}
	GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER)->EnableWindow(TRUE);	// 2008-01-03 by cmkwon, �������� ���� �����ϱ� - ���� ����
	GetDlgItem(IDC_CHECK_WINDOWS_MODE)->EnableWindow(TRUE);				// 2008-01-17 by cmkwon, �������� ���� �����ϱ� - ���� ����
	GetDlgItem(IDC_LIST)->EnableWindow(TRUE);

	m_ctlBtnRememberID.EnableWindow();			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - üũ�ڽ� ��ġ

	GetDlgItem(IDC_EDIT_ACCOUNT)->GetWindowText(m_szAccountNameReg);
	if (m_szAccountNameReg == "")
	{
		GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetSel(0, -1);
	}
#ifdef _DEBUG
	//	- beta service������ ���� ���� �Ұ�����, 12.16.

//ysw : ����
//	GetDlgItem(IDC_DECA_SERVER)->EnableWindow(TRUE);
//	GetDlgItem(IDC_BATTALUS_SERVER)->EnableWindow(TRUE);
//	GetDlgItem(IDC_SHARRINE_SERVER)->EnableWindow(TRUE);
//	GetDlgItem(IDC_PHILON_SERVER)->EnableWindow(TRUE);
	//*/
#endif
	// reset default button
	SendDlgItemMessage(IDCANCEL, BM_SETSTYLE, BS_PUSHBUTTON, (LONG)TRUE);
	SendDlgItemMessage(IDOK, BM_SETSTYLE, BS_DEFPUSHBUTTON, (LONG)TRUE);
//	DbgOut("	2007-07-13 by cmkwon, 222\r\n");	// 2007-07-13 by cmkwon, �׽�Ʈ 
}

void CAtumLauncherDlg::SetPrivateIP()
{
	// �ڽ��� IP Address�� ���Ѵ�
	char	host[100];
	HOSTENT	*p;
	char	ip[SIZE_MAX_IPADDRESS];

	gethostname(host, 100);
	if(p = gethostbyname(host))
	{
		sprintf(ip, "%d.%d.%d.%d", (BYTE)p->h_addr_list[0][0], (BYTE)p->h_addr_list[0][1],(BYTE)p->h_addr_list[0][2], (BYTE)p->h_addr_list[0][3]);
		STRNCPY_MEMSET(m_PrivateIP, ip, SIZE_MAX_IPADDRESS);
	}
}

BOOL CAtumLauncherDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DestroyWindow();
}

void CAtumLauncherDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default


	if (nIDEvent == TIMERID_CONNECT_PRESERVER)
	{
		KillTimer(TIMERID_CONNECT_PRESERVER);

		BOOL ret = ConnectPreServer();

		if (ret)
		{
			// succeeded
			m_SelectFlag = TRUE;
//			m_nServerGroupReg = SERVER_DECA;
			m_nServer = SERVER_DECA;

//ysw : ����
			// Set default radio button
/*			int ServerGroup = IDC_DECA_SERVER;
			if ( m_nServerGroupReg == SERVER_DECA )
			{
				ServerGroup = IDC_DECA_SERVER;
			}
			else if ( m_nServerGroupReg == SERVER_BATTALUS )
			{
				ServerGroup = IDC_BATTALUS_SERVER;
			}
			else if ( m_nServerGroupReg == SERVER_SHARRINE )
			{
				ServerGroup = IDC_SHARRINE_SERVER;
			}
			else if ( m_nServerGroupReg == SERVER_PHILON )
			{
				ServerGroup = IDC_PHILON_SERVER;
			}
*/
		#ifdef _DEBUG
//			CButton* pBtn= (CButton* )GetDlgItem(ServerGroup);
//			pBtn->SetCheck( TRUE );
		#else
//			CButton* pBtn= (CButton* )GetDlgItem(IDC_BATTALUS_SERVER);
//			pBtn->SetCheck( TRUE );

		//ysw : ����
//			GetDlgItem(IDC_DECA_SERVER)->EnableWindow(FALSE);
//			GetDlgItem(IDC_BATTALUS_SERVER)->EnableWindow(FALSE);
//			GetDlgItem(IDC_SHARRINE_SERVER)->EnableWindow(FALSE);
//			GetDlgItem(IDC_PHILON_SERVER)->EnableWindow(FALSE);
		#endif

			CString txt = m_CurrentVersion.GetVersionString();
			SetFileNumText((char*)(LPCTSTR)("VER " + txt));

			// set account name
// 2005-08-22 by cmkwon, for jpn alpha test
// 2007-03-06 by cmkwon, for debug
//#if defined(_DEBUG) || (  !defined(_MASANG15_SERVER) && (!defined(_MASANG51_SERVER)) && (!defined(_GLOBAL_ENG_SERVER)) && (!defined(_VTC_VIET_SERVER)) && (!defined(_KOREA_SERVER_2))  )

// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - �Ʒ��� ���� ���� ��
// #if defined(_DEBUG)
// 			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
// 			GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_szPasswordReg);
// 			((CEdit*)GetDlgItem(IDC_EDIT_ACCOUNT))->SetSel(0, -1);
// #endif

#if defined(_DEBUG)
			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
			GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_szPasswordReg);

// 2008-10-20 by cmkwon, Gameforge4D(Engilsh, German)�� ���� ���� ����ϱ� ��� �߰� - �Ʒ��� ���� ����
//#elif defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1)		// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - �Ʒ��� ���� 3�� ���� �߰�
//#elif defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1)		// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - 
// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) -  
//#elif defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1)
// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  
//#elif defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
#elif defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1) || defined(SERVICE_TYPE_SINGAPORE_1) || defined(SERVICE_TYPE_INDONESIA_SERVER_1)
			// 2008-06-17 by cmkwon, WinnerOnline_Tha Launcher���� ���� ���� ���� ����ϱ�(K0000243) - ����� AccountName �� �����Ѵ�.
			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
#endif

#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
			// 2008-12-18 by cmkwon, �Ϻ� Arario ��ó ���� - ���� �����ϱ�
			GetDlgItem(IDC_EDIT_ACCOUNT)->SetWindowText(m_szAccountNameReg);
#endif 
	//		m_szAccountNameReg = "��������\r\nTest��...\r\n������Ʈ ����\r\n���ָ� �߰�\r\n������ �߰�\r\n66\r\n77\r\n88\r\n99\r\n00\r\n00\r\n11\r\n22\r\n33\r\n44\r\n55\r\n";
	//		GetDlgItem(IDC_NOTICE)->SetWindowText(m_szAccountNameReg);


		}
		else
		{
			// failed
			EndDialog(-1);
			return;
		}
	}
	else if (nIDEvent == TIMERID_ENABLE_CONTROL)
	{
		KillTimer(nIDEvent);
		EnableControls();
	}
	else if(nIDEvent == TIMERID_SEND_ALIVE_PACKET)
	{
		if(m_pUpdateWinsocket
			&& m_pUpdateWinsocket->IsConnected())
		{
			m_pUpdateWinsocket->WriteMessageType(T_PC_CONNECT_ALIVE);
		}
	}
	else if(TIMERID_NETWORK_STATE_CHECK == nIDEvent)
	{// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ

		DWORD dwPingGapTick = 0;
		if(this->NTCheckTimeOver(&dwPingGapTick))
		{
			// 2007-06-18 by cmkwon, ��Ʈ��ũ ���� üũ - ȭ�鿡 ǥ��
			m_ServerList->UpdateNetworkState(this->NTGetPingAverageTime());		// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
			m_ServerList->Invalidate();											// 2007-06-22 by cmkwon, �߱� ��Ʈ��ũ ���� �����ֱ� -
		}
	}

	CDialog::OnTimer(nIDEvent);
}


//ysw : �߰�
void CAtumLauncherDlg::OnJoin()
{
	// TODO: Add your control notification handler code here
	CString strTmp;
	strTmp.Format("%s/%s", STRMSG_S_GAMEHOMEPAGE_DOMAIN, URL_REGISTER_PAGE);
	ShellExecute(NULL, "open", strTmp, NULL, NULL, SW_SHOWNORMAL);
}

void CAtumLauncherDlg::OnSecret()
{
	// TODO: Add your control notification handler code here
	WinExec("explorer.exe http://www.atumonline.com/7_members/login.asp ", SW_SHOW);
}

void CAtumLauncherDlg::OnEnd()
{
	// TODO: Add your control notification handler code here
	CDialog::DestroyWindow();
}

void CAtumLauncherDlg::OnDeca()
{
	// TODO: Add your control notification handler code here
	m_SelectFlag = TRUE;
	m_nServer = SERVER_DECA;
}

void CAtumLauncherDlg::OnBattal()
{
	// TODO: Add your control notification handler code here

}

void CAtumLauncherDlg::OnSharin()
{
	// TODO: Add your control notification handler code here

}

void CAtumLauncherDlg::OnPhilon()
{
	// TODO: Add your control notification handler code here

}

#define CUR_BAR_X		170
#define CUR_BAR_Y		41
#define CUR_BAR_WIDTH	258
#define CUR_BAR_HEIGHT	20

/*--------------------------------------------------------------------
	 DrawProgressBar
--------------------------------------------------------------------*/
int CAtumLauncherDlg::DrawProgressBar()
{
	CClientDC	dc(this);
	CDC			MemDC;
	CBitmap		* pOldBmp;
	CBrush		BlueBrush(RGB(0, 84, 166));
	CBrush		GrayBrush(RGB(109, 207, 246));

	CRect		ProRect;
	CBitmap		Percent;

	char		 Junk[10];
	TEXTMETRIC	 TextMetric;

	MemDC.CreateCompatibleDC(&dc);
	Percent.CreateCompatibleBitmap(&dc, CUR_BAR_WIDTH, CUR_BAR_HEIGHT);
	pOldBmp = (CBitmap *)MemDC.SelectObject(&Percent);

	ProRect.SetRect(0, 0, CUR_BAR_WIDTH, CUR_BAR_HEIGHT);
	MemDC.FillRect(&ProRect, &GrayBrush);
	ProRect.SetRect(0, 0, m_Cur_Rect , CUR_BAR_HEIGHT);
	MemDC.FillRect(&ProRect, &BlueBrush);

	MemDC.SetBkMode(TRANSPARENT);
	MemDC.SetTextColor(RGB(0, 0, 0));
	MemDC.GetTextMetrics(&TextMetric);

	wsprintf(Junk, "%d%%", m_Cur_Percent);
	MemDC.TextOut(CUR_BAR_WIDTH/2 - (TextMetric.tmAveCharWidth * lstrlen(Junk)/2),
				CUR_BAR_HEIGHT/2 - (TextMetric.tmHeight/2), (LPCSTR)Junk, lstrlen(Junk));

	dc.BitBlt(CUR_BAR_X, CUR_BAR_Y, CUR_BAR_WIDTH, CUR_BAR_HEIGHT, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(&pOldBmp);

	return	true;
}


/*----------------------------------------------------------------------------*
*			Set_Cur_Percent
*-----------------------------------------------------------------------------*/
void CAtumLauncherDlg::Set_Cur_Percent(DWORD CurSize)
{
	m_Cur_Percent = CurSize;
	if(m_Cur_Percent > 100) m_Cur_Percent = 100;

	m_Cur_Rect = (int)( (m_Cur_Percent*CUR_BAR_WIDTH)/100 );
}

void CAtumLauncherDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);

	// fake windows into thinking your clicking on the caption, does not
	// maximizeon double click
	
	// ���콺�� ��� ������ �̵�
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

//	if(m_FTPUpdateState == UPDATE_STATE_DOWNLOADING)
//	{
//		AtumMessageBox("���� �ֽ� ������Ʈ�� ���� �� �Դϴ�.\n\n������Ʈ �Ϸ� �� ���� ��ư�� Ŭ���� �ּ���.");
//	}
}


UINT CAtumLauncherDlg::OnNcHitTest(CPoint point)
{
     UINT nHitTest = CDialog::OnNcHitTest( point );
     // also fake windows out, but this maximizes the window
     // when you double click on it.
     return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
}


HBRUSH CAtumLauncherDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	switch(nCtlColor)
	{
	case CTLCOLOR_EDIT:
		{		
			if((GetDlgItem(IDC_EDIT_ACCOUNT)->m_hWnd == pWnd->m_hWnd)
				|| (GetDlgItem(IDC_EDIT_PASSWORD)->m_hWnd == pWnd->m_hWnd))
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));
				return m_StaticBrushBlack;
			}
		}
		break;
		
	case CTLCOLOR_STATIC:
		{
			if(GetDlgItem(IDC_FILE_INFO)->m_hWnd == pWnd->m_hWnd)
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(EXE2_BG_UPDATE_INFO_FONT_COLOR);		
				return (HBRUSH)GetStockObject(NULL_BRUSH);
			}
			else if(GetDlgItem(IDC_DOWNLOAD_FILENUM)->m_hWnd == pWnd->m_hWnd)
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(EXE2_BG_DOWNLOAD_FILE_FONT_COLOR);		
				return (HBRUSH)GetStockObject(NULL_BRUSH);
			}
			else if(GetDlgItem(IDC_CHARACTER_NAME)->m_hWnd == pWnd->m_hWnd )
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));		
				return m_StaticBrushGray;
			}
		}
		break;
	case CTLCOLOR_LISTBOX:
		{
			if(GetDlgItem(IDC_LIST)->m_hWnd == pWnd->m_hWnd )
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetBkColor(RGB(29, 29, 40));
				pDC->SetTextColor(RGB(189,194,198));
				return m_listBrush;
			}
		}
		break;
	default:
		{			
		}
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

// 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ������.
//void CAtumLauncherDlg::ExecGame(char *cmdLine)
void CAtumLauncherDlg::ExecGame(char *cmdLine, char *i_szAppPath/*=NULL*/, char *i_szCmdParam/*=NULL*/)
{
#ifdef _ATUM_DEVELOP
	SetCurrentDirectory(m_szExecutePathReg);
#endif

// 2009-07-10 by cmkwon, ���þ� Frost �ű� Lib�� ���� - ���� �ҽ� �ּ� ó��
// // 2009-01-30 by cmkwon, ���þ� Innova ��ó �ý���(���ν�Ʈ) ���� - �Ʒ��� ���� ���þƸ� ���� ó��, AyyoCreateProcess() ȣ�� ó��
// // 2009-04-23 by cmkwon, ���þ� Innova Frost �ӽ� �����ϱ� - �Ʒ��� ���� define ���� ó�� ��.
// //#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
// #if defined(SERVICE_TYPE_RUSSIAN_SERVER_1) && defined(_USING_INNOVA_FROST_)
// 	if(NULL == i_szAppPath
// 		|| NULL == i_szCmdParam)
// 	{
// 		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0032);
// 		return;
// 	}
// 
// 
// 	char szFullParm[MAX_PATH];
// 	MEMSET_ZERO(szFullParm, MAX_PATH);
// 	_snprintf(szFullParm, MAX_PATH-1, "%s %s", i_szAppPath, i_szCmdParam);
// 	BOOL bReted = AyyoCreateProcess(i_szAppPath, szFullParm);
// 	if(FALSE == bReted)
// 	{
// 		AtumMessageBox(STRERR_S_ATUMLAUNCHER_0033);
// 		return;
// 	}
// 	return;
// #endif

#if defined(SERVICE_TYPE_VIETNAMESE_SERVER_1) || defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
	///////////////////////////////////////////////////////////////////////////////
	// 2009-10-29 by cmkwon, ��Ʈ�� X-TRAP �ڵ�������Ʈ ��� ���� - CAtumLauncherDlg::ExecGame#,
	XTrap_L_Patch(XTRAP_KEY_STRING, NULL, 60);
#endif

	UINT ret = WinExec(cmdLine, SW_SHOWNORMAL);
	DbgOut("EXE 2 CommandLine : %s, RetCode(%d)\r\n", cmdLine, ret);		// 2007-05-16 by cmkwon
	if ( ret <= 31 )	// exec failed...
	{
		switch (ret)
		{
		case 0:						// The system is out of memory or resources.
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0031);
			break;
		case ERROR_BAD_FORMAT:		// The .exe file is invalid.
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0032);
			break;
		case ERROR_FILE_NOT_FOUND:	// The specified file was not found.
#ifdef _ATUM_DEVELOP
			AtumMessageBox(CString("File not Found!\nbin: ") + cmdLine
				+ "\npath: " + m_szExecutePathReg);
#else
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0033);
#endif
			break;
		case ERROR_PATH_NOT_FOUND:	// The specified path was not found.
			AtumMessageBox(STRERR_S_ATUMLAUNCHER_0034);
			break;
		default:
			break;
		}
	}
}

void CAtumLauncherDlg::ExecGameCrocess(char *cmdLine)
{
	DWORD dwExitCode;
	PROCESS_INFORMATION pi;

	STARTUPINFO si = {sizeof(si)};
	ZeroMemory(&si,sizeof(si));

	CreateProcess(
		NULL,				// name of executable module
		cmdLine,			// command line string
		NULL,				//LPSECURITY_ATTRIBUTES lpProcessAttributes, // SD
		NULL,				//LPSECURITY_ATTRIBUTES lpThreadAttributes,  // SD
		0,					//BOOL bInheritHandles,                      // handle inheritance option
		0,					//DWORD dwCreationFlags,                     // creation flags
		NULL,				//LPVOID lpEnvironment,                      // new environment block
		NULL,				//LPCTSTR lpCurrentDirectory,                // current directory name
		&si,				//LPSTARTUPINFO lpStartupInfo,               // startup information
		&pi					//LPPROCESS_INFORMATION lpProcessInformation // process information
		);


	GetExitCodeProcess(pi.hProcess, &dwExitCode);
	if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_OBJECT_0) {
		// Process ����
		//AtumMessageBox("Process Terminated!");
	}

	CloseHandle( pi.hThread );
	CloseHandle( pi.hProcess );
}

BOOL CAtumLauncherDlg::ProcessDeleteFileList(MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO *pUpdateInfo)
{
#ifdef _DEBUG
	VersionInfo DVersion(pUpdateInfo->NewDeleteFileListVersion);
	DBGOUT(STRMSG_S_ATUMLAUNCHER_0002, DVersion.GetVersionString());
#endif

	HINTERNET hInternet;
	HINTERNET hFtpConnect;
	HINTERNET hDir;
	HINTERNET hDelFile;
	WIN32_FIND_DATA pDirInfo;
	int nFileSize;

	hInternet = InternetOpen("Atum Pre Server", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL)
	{
		// check: error
		// 2005-01-13 by cmkwon, DeleteFile, NoticeFile FTP ���� ���� ������ �޽����ڽ� ����
		//AtumMessageBox("InternetOpen ERROR!");
		DbgOut("InternetOpen ERROR: %d", GetLastError());
		return FALSE;
	}

	DbgOut("Updating delete file list(%s) From %s:%d \r\n", pUpdateInfo->DeleteFileListDownloadPath, pUpdateInfo->FtpIP, pUpdateInfo->FtpPort);

	hFtpConnect = InternetConnect(hInternet, pUpdateInfo->FtpIP, pUpdateInfo->FtpPort, pUpdateInfo->FtpAccountName, pUpdateInfo->FtpPassword, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
	if (hFtpConnect == NULL)
	{
		// check: error
		// 2005-01-13 by cmkwon, DeleteFile, NoticeFile FTP ���� ���� ������ �޽����ڽ� ����
		//AtumMessageBox("InternetConnect ERROR!");
		DbgOut("InternetConnect ERROR: %d\r\n", GetLastError());
		return FALSE;
	}

	if ( !(hDir = FtpFindFirstFile (hFtpConnect, pUpdateInfo->DeleteFileListDownloadPath, &pDirInfo, 0, 0) ) )
	{
		DWORD dwLastErr = GetLastError();
		if (dwLastErr == ERROR_NO_MORE_FILES)
		{
			DbgOut("No more files here\r\n");
			return FALSE;
		}
		else if (dwLastErr == ERROR_INTERNET_EXTENDED_ERROR)
		{
			DWORD dwError;
			TCHAR szErr[2048]; DWORD dwErrLen = 2048;
			if (InternetGetLastResponseInfo(&dwError, szErr, &dwErrLen))
			{
				CString szErrStr;
				szErrStr.Format("DFile Error: %s\r\n", szErr);
				// 2005-01-13 by cmkwon, DeleteFile, NoticeFile FTP ���� ���� ������ �޽����ڽ� ����
				//AtumMessageBox(szErrStr);
				DbgOut("%s\n", szErrStr);
			}
			return FALSE;
		}
		else
		{
			// check: error
			CString szErrStr;
			szErrStr.Format("DFile Error: %d", GetLastError());
			// 2005-01-13 by cmkwon, DeleteFile, NoticeFile FTP ���� ���� ������ �޽����ڽ� ����
			//AtumMessageBox(szErrStr);
			DbgOut("%s\n", szErrStr);
			return FALSE;
		}
	}
	else
	{
		nFileSize = pDirInfo.nFileSizeLow;
	}

	// GUI ����
	SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0003);
	m_progressCtrl.SetRange32(0, nFileSize);

	////////////////////////////
	// file buffer
	string delFileBuffer = "";

	////////////////////////////
	// open remote file
	hDelFile = FtpOpenFile(hFtpConnect, pUpdateInfo->DeleteFileListDownloadPath, GENERIC_READ, FTP_TRANSFER_TYPE_BINARY, NULL);
	char *buffer = new char[DOWNLOAD_BUFFER_SIZE];
	DWORD amount_read = DOWNLOAD_BUFFER_SIZE;
	UINT total_read = 0;

	while (TRUE)
	{
		if (!InternetReadFile (hDelFile, buffer, DOWNLOAD_BUFFER_SIZE, &amount_read))
		{
			// error
			// 2005-01-13 by cmkwon, DeleteFile, NoticeFile FTP ���� ���� ������ �޽����ڽ� ����
			//AtumMessageBox("Reading file failed");
			return FALSE;
		}

		if(0 == amount_read)
		{// 2006-06-30 by cmkwon
			break;
		}

		delFileBuffer.append(buffer, amount_read);

		total_read += amount_read;
		m_progressCtrl.SetPos(total_read);
	}

	delFileBuffer += "\r\n";

	///////////////////////////
	// ó��
	istrstream isDel(delFileBuffer.c_str());
	char delFileLine[SIZE_MAX_FTP_FILE_PATH];
	int isOffset = 0;
	while(isOffset < nFileSize)
	{
		if (isDel.getline(delFileLine, SIZE_MAX_FTP_FILE_PATH).eof())
		{
			break;
		}

		isOffset += (strlen(delFileLine) + 1);

		// 0x0D�� �������� ���� ��� ������
		if (delFileLine[strlen(delFileLine)-1] == 0x0D)
		{
			delFileLine[strlen(delFileLine)-1] = '\0';
		}

		if (delFileLine[0] == '#')
		{
			// comment��
			continue;
		}

#ifdef _DEBUG
		char	szDir[512];
		GetCurrentDirectory(512, szDir);
#endif

		DeleteFile(delFileLine);
	}

	// delete buffer
	delete buffer;

	// close resources
	InternetCloseHandle(hDelFile);
	InternetCloseHandle(hDir);
	InternetCloseHandle(hFtpConnect);
	InternetCloseHandle(hInternet);

	return TRUE;
}

BOOL CAtumLauncherDlg::ProcessNoticeFile(MSG_PC_CONNECT_SINGLE_FILE_UPDATE_INFO *pUpdateInfo)
{
	BOOL bRet = FALSE;
	CFTPManager noticeFTPManager;

	DbgOut("Updating notice file(%s) From %s:%d \r\n", pUpdateInfo->NoticeFileDownloadPath, pUpdateInfo->FtpIP, pUpdateInfo->FtpPort);

	bRet = noticeFTPManager.ConnectToServer(pUpdateInfo->FtpIP, pUpdateInfo->FtpPort, pUpdateInfo->FtpAccountName, pUpdateInfo->FtpPassword);
	if (!bRet)
	{
		return FALSE;
	}

	// Find file info
	WIN32_FIND_DATA fileInfo;
	HINTERNET hFile = noticeFTPManager.GetFileInfo(pUpdateInfo->NoticeFileDownloadPath, &fileInfo);
	if (hFile == NULL)
	{
		return FALSE;
	}

	// set file length
	int nFileSize = fileInfo.nFileSizeLow;

	// GUI ����
	SetProgressGroupText(STRMSG_S_ATUMLAUNCHER_0004);
	m_progressCtrl.SetRange32(0, nFileSize);

	// �ٿ�ε�
	bRet = noticeFTPManager.DownloadFile(pUpdateInfo->NoticeFileDownloadPath, "notice.txt", &m_progressCtrl);
	if (!bRet)
	{
		return FALSE;
	}

	noticeFTPManager.CloseConnection();

	return TRUE;
}

void CAtumLauncherDlg::OnSelchangeList()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE) ;
	int nSel = m_ctrlServerList.GetCurSel();
	if(m_ctrlServerList.GetServerCheck(nSel))
	{
		m_ctrlServerList.SetCurSel(nSel);
		m_nOldSel = nSel;
	}
	else
	{
		m_ctrlServerList.SetCurSel(m_nOldSel);
	}
}

void CAtumLauncherDlg::OnCan()
{
	// TODO: Add your control notification handler code here

	if(UPDATE_STATE_DOWNLOADING == m_FTPUpdateState
		|| UPDATE_STATE_DOWNLOADED == m_FTPUpdateState)
	{
		if(m_pUpdateFTPManager)
		{
			m_pUpdateFTPManager->m_bDownloadThreadCancelFlag = TRUE;
			if(m_pUpdateFTPManager->m_hDownloadThread)
			{
				DWORD dwRet;
				dwRet = WaitForSingleObject(m_pUpdateFTPManager->m_hDownloadThread, INFINITE);
				if(WAIT_OBJECT_0 != dwRet)
				{
					// ������ WAIT_FAILED��
					int nError = GetLastError();
					SetLastError(0);
				}
				CloseHandle(m_pUpdateFTPManager->m_hDownloadThread);
				m_pUpdateFTPManager->m_hDownloadThread = NULL;				
				Sleep(100);
			}
			SAFE_DELETE(m_pHost);
			delete m_pUpdateFTPManager;
			m_pUpdateFTPManager = NULL;
			this->SetFTPUpdateState(UPDATE_STATE_INIT);
		}

		if(m_pHttpManager)
		{// 2007-01-08 by cmkwon
			m_pHttpManager->ThreadEnd(1000);
			SAFE_DELETE(m_pHttpManager);
			this->SetFTPUpdateState(UPDATE_STATE_INIT);
		}

		VersionInfo OldVersion(m_msg_PC_CONNECT_UPDATE_INFO.OldVersion);
		VersionInfo UpdateVersion(m_msg_PC_CONNECT_UPDATE_INFO.UpdateVersion);
		char szUpdateFileName[256];
		sprintf(szUpdateFileName, "%s_%s.zip", OldVersion.GetVersionString(),
			UpdateVersion.GetVersionString());
		DeleteFile(szUpdateFileName);
	}
	CDialog::OnCancel();
}

BOOL CAtumLauncherDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (m_bControlEnabled)
		{
			OnOk();
		}
		return TRUE;
	}

///////////////////////////////////////////////////////////////////////////////
// 2009-07-08 by cmkwon, ���þ� ��ó ���� ��û(���콺��Ŭ�� ����) - 	
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
	if(WM_RBUTTONDOWN == pMsg->message)
	{
		return TRUE;
	}
#endif

	return CDialog::PreTranslateMessage(pMsg);
}



LONG CAtumLauncherDlg::OnUpdateFileDownloadError(WPARAM wParam, LPARAM lParam)
{
	if(UPDATE_STATE_DOWNLOADING != m_FTPUpdateState){		return FALSE;}

	char szErrString[1024];
	char szErrAddStr[1024];
	MEMSET_ZERO(szErrString, 1024);
	MEMSET_ZERO(szErrAddStr, 1024);
// 2007-01-05 by cmkwon, �Ʒ��� ���� ERR_XXX�� ������
//	switch(wParam)
//	{
//	case DOWNLOAD_ERR_FTP_CONNECT:
//		{
//			strcpy(szErrAddStr, STRERR_S_ATUMEXE_0006);
//		}
//		break;
//	case DOWNLOAD_ERR_FTP_OPENFILE:
//		{
//			strcpy(szErrAddStr, STR_DOWNLOAD_ERR_FTPCONNECT);
//		}
//		break;
//	case DOWNLOAD_ERR_CREATE_LOCAL_FILE:
//		{
//			strcpy(szErrAddStr, STR_DOWNLOAD_ERR_CREATE_LOCAL_FILE);
//		}
//		break;
//	case DOWNLOAD_ERR_READ_REMOTE_FILE:
//		{
//			strcpy(szErrAddStr, STR_DOWNLOAD_ERR_READ_REMOTE_FILE);
//		}
//		break;
//	default:
//		{
//			wsprintf(szErrAddStr, "Nomal download error(%d) !!", wParam);
//		}
//	}
	switch(wParam)
	{
	case ERR_CANNOT_CONNECT_AUTO_UPDATE_SERVER:
		{
			strcpy(szErrAddStr, STRERR_S_ATUMEXE_0006);
		}
		break;
	case ERR_LOCAL_FILE_CREATE_FAIL:
		{
			strcpy(szErrAddStr, STRCMD_CS_COMMON_DOWNLOAD_0001);
		}
		break;
	case ERR_UPDATE_FILE_NOT_FOUND:
		{
			strcpy(szErrAddStr, STRCMD_CS_COMMON_DOWNLOAD_0000);
		}
		break;
	case ERR_UPDATE_FILE_DOWNLOADING_FAIL:	
		{
			strcpy(szErrAddStr, STRCMD_CS_COMMON_DOWNLOAD_0002);
		}
		break;
	default:
		{
			wsprintf(szErrAddStr, "Nomal download error(%d) !!", wParam);
		}
	}

	wsprintf(szErrString, STRMSG_060526_0001
		, STRMSG_S_GAMEHOMEPAGE_DOMAIN, szErrAddStr);
	AtumMessageBox(szErrString);
	OnCancel();
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			LONG CAtumLauncherDlg::OnUpdateFileDownloadInit(WPARAM wParam, LPARAM lParam)
/// \brief		
/// \author		cmkwon
/// \date		2007-01-08 ~ 2007-01-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
LONG CAtumLauncherDlg::OnUpdateFileDownloadInit(WPARAM wParam, LPARAM lParam)
{
	m_progressCtrl.SetRange32(0, wParam);
	m_progressCtrl.SetPos(0);
	return TRUE;
}

LONG CAtumLauncherDlg::OnUpdateFileDownloadProgress(WPARAM wParam, LPARAM lParam)
{
	if(UPDATE_STATE_DOWNLOADING != m_FTPUpdateState){		return FALSE;}

	m_progressCtrl.SetPos(wParam);
	return TRUE;
}

LONG CAtumLauncherDlg::OnUpdateFileDownloadOK(WPARAM wParam, LPARAM lParam)
{
	if(UPDATE_STATE_DOWNLOADING != m_FTPUpdateState){		return FALSE;}
	this->SetFTPUpdateState(UPDATE_STATE_DOWNLOADED);

	if(m_pUpdateFTPManager)
	{
		if(m_pUpdateFTPManager->m_hDownloadThread)
		{
			DWORD dwRet;
			dwRet = WaitForSingleObject(m_pUpdateFTPManager->m_hDownloadThread, 1000);
			if(WAIT_OBJECT_0 != dwRet)
			{
				// ������ WAIT_FAILED��
				int nError = GetLastError();
				SetLastError(0);
			}
			CloseHandle(m_pUpdateFTPManager->m_hDownloadThread);
			m_pUpdateFTPManager->m_hDownloadThread = NULL;

			Sleep(100);
		}

		delete m_pUpdateFTPManager;
		m_pUpdateFTPManager = NULL;
		this->SetFTPUpdateState(UPDATE_STATE_INIT);
	}
	if(m_pHttpManager)
	{
		m_pHttpManager->ThreadEnd(1000);
		SAFE_DELETE(m_pHttpManager);		
		this->SetFTPUpdateState(UPDATE_STATE_INIT);
	}

	// extract update file
	ExtractUpdateFile(&m_msg_PC_CONNECT_UPDATE_INFO);
	
	// update completed
	VersionInfo OldVersion(m_msg_PC_CONNECT_UPDATE_INFO.OldVersion);
	VersionInfo UpdateVersion(m_msg_PC_CONNECT_UPDATE_INFO.UpdateVersion);
	char strBuffer[256];
	sprintf(strBuffer, STRMSG_S_ATUMLAUNCHER_0005, OldVersion.GetVersionString(),
		UpdateVersion.GetVersionString());
	SetProgressGroupText(strBuffer);
	
	// set current cliet version
	m_CurrentVersion = UpdateVersion;
	
	// On DownLoadGamefilesDone
	OnDownLoadGamefilesDone(NULL, NULL);

	memset(&m_msg_PC_CONNECT_UPDATE_INFO, 0x00, sizeof(MSG_PC_CONNECT_UPDATE_INFO));

	return TRUE;
}

void CAtumLauncherDlg::OnMin() 
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(SW_MINIMIZE);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CAtumLauncherDlg::OnBtnHomepage() 
/// \brief		// 2007-09-27 by cmkwon, Homepage���� ��ư �߰�(��Ʈ�� VTC-Intecom ��û) - 
/// \author		cmkwon
/// \date		2007-09-27 ~ 2007-09-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CAtumLauncherDlg::OnBtnHomepage() 
{
	// TODO: Add your control notification handler code here

	ShellExecute(NULL, "open", STRMSG_S_GAMEHOMEPAGE_DOMAIN, NULL, NULL, SW_SHOWNORMAL);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *CAtumLauncherDlg::GetPublicLocalIP(char *o_szLocalIP)
/// \brief		
/// \author		cmkwon
/// \date		2006-04-10 ~ 2006-04-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char *CAtumLauncherDlg::GetPublicLocalIP(char *o_szLocalIP)
{
	GGetLocalIP(o_szLocalIP, IP_TYPE_PUBLIC);
	return o_szLocalIP;
}

void CAtumLauncherDlg::OnSetfocusEditAccount() 
{
	// TODO: Add your control notification handler code here
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_ACCOUNT);	
}

void CAtumLauncherDlg::OnSetfocusEditPassword() 
{
	// TODO: Add your control notification handler code here
	
	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}

	m_pInputEditFromScreenKeyboard = GetDlgItem(IDC_EDIT_PASSWORD);	

	///////////////////////////////////////////////////////////////////////////////
	// 2007-09-18 by cmkwon, ȭ��Ű���� ���� - ȭ��Ű���� �����쿡�� Hide ��ų��� ó���� ����
	if(FALSE == m_bHideScreenKeyboardByScreenKeyboardWindow)
	{
		// 2007-09-18 by cmkwon, ȭ��Ű���� ���� - �н����� �Է½ÿ��� Ȱ��ȭ �ȴ�.
		m_pScreenKeyboardDlg->ShowWindow(SW_SHOW);
	}
	m_bHideScreenKeyboardByScreenKeyboardWindow	= FALSE;
}

void CAtumLauncherDlg::OnBtnViewScreenKeyboard() 
{
	// TODO: Add your control notification handler code here

	if(NULL == m_pScreenKeyboardDlg)
	{
		return;
	}
	
	// 2007-09-11 by cmkwon, ��Ʈ�� ȭ��Ű���� ���� - ȭ�� Ű���带 �����ش�
	m_pScreenKeyboardDlg->ShowWindow(SW_SHOW);
}

void CAtumLauncherDlg::OnCheckWindowsMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_WINDOW_DEGREE_LAUNCHER);
	if(NULL == pComboBox)
	{
		return;
	}

	CString csBeforeWDegree;
	pComboBox->GetWindowText(csBeforeWDegree);

	
	
	// 2008-12-17 by ckPark ���þ� ����
	// // ���þƴ� üũ�ڽ�
#if defined(SERVICE_TYPE_RUSSIAN_SERVER_1)		// ���þ� ��ó �������̽� ����
	this->InsertWindowDegreeList(pComboBox, m_ctrlCheckWindowMode.GetCheck());
#else
	this->InsertWindowDegreeList(pComboBox, m_ctlbWindowMode);
#endif
	// end 2008-12-17 by ckPark ���þ� ����




	int nIdx = this->FindWindowDegreeComboBoxIndex(pComboBox, (LPSTR)(LPCSTR)csBeforeWDegree);
	nIdx = max(0, nIdx);
	pComboBox->SetCurSel(nIdx);
}
