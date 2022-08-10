// AuthenticationServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "AuthenticationGlobal.h"
#include "AuthenticationIOCP.h"
#include "AuthenticationIOCPSocket.h"
#include "VMemPool.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
 	// TODO: Place code here.
	g_pAuthenticationGlobal = new CAuthenticationGlobal;
	if(FALSE == g_pAuthenticationGlobal->InitGlobal("Authentication Server"))
	{
		return FALSE;
	}

	// set config root path
	g_pAuthenticationGlobal->SetConfigRootPath();
	g_pAuthenticationGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "AuthenticationSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());

	g_pAuthenticationGlobal->WriteSystemLogEX(TRUE, "Authentication Server Start\r\n");

	if(FALSE == CIOCP::SocketInit())
	{
		g_pAuthenticationGlobal->WriteSystemLogEX(TRUE, "[ERROR] WinaMain SocketInit error!!\r\n");
		return FALSE;
	}

	CVMemPool::vmPoolAddObject(sizeof(COverlapped), SIZE_MAX_AUTHSERVER_SESSION * 10);
	CVMemPool::vmPoolAddObject(sizeof(CSendPacket), 100);		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
	CVMemPool::vmPoolAddObject(sizeof(CRecvPacket), 100);		// 2008-02-22 by cmkwon, ServerPreServer->MasangPreServer 로 서비스 정보 전송 시스템 추가 - 
	if(CVMemPool::vmPoolInit() == FALSE)
	{
		g_pAuthenticationGlobal->WriteSystemLogEX(TRUE, "[ERROR] WinaMain vmPoolInit error!!\r\n");
		return FALSE;
	}

#if defined(SERVICE_TYPE_TAIWANESE_SERVER_1)
	// 2008-10-08 by cmkwon, 대만 Netpower_Tpe 외부인증 구현 - 
	CoInitialize(NULL);			// COM 초기화
#endif

	g_pAuthenticationGlobal->WndRegisterClass(hInstance, IDI_AUTHENTICATIONSERVER, _T("Authentication Server"));
	// Perform application initialization:
	if (!g_pAuthenticationGlobal->InitInstance (hInstance, nCmdShow, _T("Authentication Server"), _T("Authentication Server")))
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

	g_pAuthenticationGlobal->WriteSystemLogEX(TRUE, "Authentication Server End\r\n\r\n\r\n");

	SAFE_DELETE(g_pAuthenticationGlobal);
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

			g_pAuthenticationGlobal->SetMainWndHandle(hWnd);

			if(FALSE == g_pAuthenticationGlobal->LoadConfiguration())
			{
 				MessageBox(hWnd, "LoadConfiguration Error", "ERROR", MB_OK);
 				exit(0);
				break;
			}

			if(FALSE == g_pAuthenticationGlobal->InitServerSocket())
			{
				g_pAuthenticationGlobal->WriteSystemLogEX(TRUE, "[ERROR] WndProc InitServerSocket_ error !!");
			}
			else
			{
				g_pAuthenticationGlobal->StartTimerTraffic();
				g_pAuthenticationGlobal->StartTimerAliveCheck();
			}

			break;
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
					g_pAuthenticationGlobal->CheckServerThread();
					g_pAuthenticationGlobal->CalculateIOCPTraffic();
				}
				break;
			case TIMERID_ALIVE_CHECK:
				{
				}
				break;
			}
		}
		break;

	case WM_DESTROY:
		{
			g_pAuthenticationGlobal->EndServerSocket();
			PostQuitMessage(0);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
   return 0;
}
