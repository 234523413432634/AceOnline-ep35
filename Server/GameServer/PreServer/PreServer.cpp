// PreServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "PreGlobal.h"
#include "PreIOCP.h"
#include "PreIOCPSocket.h"
#include "VMemPool.h"
#include "SPToMPWinSocket.h"		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 

// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 임시용
// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)

// start 2011-06-22 by hskim, 사설 서버 방지
// 공용으로 쓰기위해 PreGlobal.h 로 이동
//#ifdef  S_AUTHENTICATION_SERVER_HSKIM		// 2011-01-26 by hskim, 인증 서버 구현
//#define MasangPreServerIP		"c3.eyehs.kr"		// 테스트용 URL
//#define MasangPreServerPort		14999
//#else
//#define MasangPreServerIP		"61.39.170.131"
//#define MasangPreServerPort		15100
//#endif
// end 2011-06-22 by hskim, 사설 서버 방지


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
 	// TODO: Place code here.
	g_pPreGlobal = new CPreGlobal;
	if(FALSE == g_pPreGlobal->InitGlobal("Pre Server"))
	{
		return FALSE;
	}

	// set config root path
	g_pPreGlobal->SetConfigRootPath();
	g_pPreGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "PreSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());

	g_pPreGlobal->WriteSystemLogEX(TRUE, "Pre Server Start\r\n");

	if(FALSE == CIOCP::SocketInit())
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR] WinaMain SocketInit error!!\r\n");
		return FALSE;
	}

	CVMemPool::vmPoolAddObject(sizeof(COverlapped), SIZE_MAX_PRESERVER_SESSION * 10);
	CVMemPool::vmPoolAddObject(sizeof(CSendPacket), 100);		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
	CVMemPool::vmPoolAddObject(sizeof(CRecvPacket), 100);		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
	if(CVMemPool::vmPoolInit() == FALSE)
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR] WinaMain vmPoolInit error!!\r\n");
		return FALSE;
	}

#if defined(SERVICE_TYPE_TAIWANESE_SERVER_1)
	// 2008-10-08 by cmkwon, 대만 Netpower_Tpe 외부인증 구현 - 
	CoInitialize(NULL);			// COM 초기화
#endif

	g_pPreGlobal->WndRegisterClass(hInstance, IDI_PRESERVER, _T("Pre Server"));
	// Perform application initialization:
	if (!g_pPreGlobal->InitInstance (hInstance, nCmdShow, _T("Pre Server"), _T("Pre Server")))
	{
		return FALSE;
	}

	///////////////////////////////////////////////////////////////////////////
	// Main message loop:
	MSG			msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CVMemPool::vmPoolClean();
	CIOCP::SocketClean();

	g_pPreGlobal->WriteSystemLogEX(TRUE, "Pre Server End\r\n\r\n\r\n");

	SAFE_DELETE(g_pPreGlobal);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			SetLastError(0);
// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 아래와 같이 수정 함, g_pPreGlobal->InitServerSocket() 처리를 MasangPreServer 로 연결 후 처리하게 변경함
// 			if(g_pPreGlobal->LoadConfiguration())
// 			{
// 				if(g_pPreGlobal->InitServerSocket())
// 				{
// 					g_pPreGlobal->SetMainWndHandle(hWnd);
// 					g_pPreGlobal->StartTimerTraffic();
// 					g_pPreGlobal->StartTimerAliveCheck();
// 				}
// 			}
// 			else
// 			{
// 				MessageBox(hWnd, "LoadConfiguration Error", "ERROR", MB_OK);
// 				exit(0);
// 			}			
			
			// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
			g_pPreGlobal->SetMainWndHandle(hWnd);

			if(FALSE == g_pPreGlobal->LoadConfiguration())
			{
 				MessageBox(hWnd, "LoadConfiguration Error", "ERROR", MB_OK);
 				exit(0);
				break;
			}

#ifdef S_AUTHENTICATION_SERVER_HSKIM		// 2011-01-26 by hskim, 인증 서버 구현
			// _ATUM_AUTHENTICATION_SERVER 정의시 기존 인증서버시 사용 안함 (Authentication Server 프로젝트로 따로 구축)
#else
			if(0 == stricmp(MasangPreServerIP, g_pPreGlobal->GetPublicIPLocal()))				
			{// 2008-02-22 by cmkwon, 자신이 MasangPreServer 이면 바로 서비스를 시작한다.

				// start 2011-06-22 by hskim, 사설 서버 방지
				if(NULL != g_pPreGlobal->GetGIOCP() ) 
				{
					break;
				}
				// end 2011-06-22 by hskim, 사설 서버 방지

				if(FALSE == g_pPreGlobal->InitServerSocket())
				{
					g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR] WndProc InitServerSocket_ error !!");
				}
				else
				{
					g_pPreGlobal->StartTimerTraffic();
					g_pPreGlobal->StartTimerAliveCheck();
				}
				break;
			}
#endif

			// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
			if(FALSE == g_pPreGlobal->createPreToAllServer(hWnd))
			{
				g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR] createPreToAllServer_ error !!");
				exit(0);
				break;
			}
			if(FALSE == g_pPreGlobal->connectBySPToMPWinSoc(MasangPreServerIP, MasangPreServerPort))
			{
// start 2011-07-26 by hskim, 인증 서버 구현
//////////
// 기존
// 				g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR] connectBySPToMPWinSoc_ error !! IP(%s) Port(%d)", MasangPreServerIP, MasangPreServerPort);
// 				exit(0);
//				break;

//////////
// 수정
#ifdef SC_SECURITY_COMMAND_HSKIM

				// 도메인등 접속 실패 시 서버 바로 실행

				if(NULL != g_pPreGlobal->GetGIOCP() ) 
				{
					break;
				}

				if(FALSE == g_pPreGlobal->InitServerSocket())
				{
					g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR] WndProc InitServerSocket_ error !!");
				}
				else
				{
					g_pPreGlobal->StartTimerTraffic();
					g_pPreGlobal->StartTimerAliveCheck();
				}
				break;
#else
 				g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR] connectBySPToMPWinSoc_ error !! IP(%s) Port(%d)", MasangPreServerIP, MasangPreServerPort);
 				exit(0);
				break;
#endif
// end 2011-07-26 by hskim, 인증 서버 구현
			}

		}
		break;
	case WM_COMMAND:
		{
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		{
			switch(wParam)
			{
			case TIMERID_TRAFFIC:
				{
					g_pPreGlobal->CheckServerThread();
					g_pPreGlobal->CalculateIOCPTraffic();
				}
				break;
			case TIMERID_ALIVE_CHECK:
				{
					// 2005-01-04 by cmkwon, 다음주 업데이트에 수정해야함, 런처에서 AlivePacket을 전송하지 않는다
					g_pPreGlobal->CheckClientAlive();
				}
				break;
			}
		}
		break;
	case WM_DESTROY:
		{
			g_pPreGlobal->EndServerSocket();
			PostQuitMessage(0);
		}
		break;
	case WM_ASYNC_EVENT:	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
		{
			g_pPreGlobal->OnAsyncEventOfSPToMPWinSoc(wParam, lParam);
		}
		break;
	case WM_PACKET_NOTIFY:	// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
		{
			g_pPreGlobal->OnPacketNotifyOfSPToMPWinSoc(LOWORD(wParam), HIWORD(wParam));
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
   return 0;
}
