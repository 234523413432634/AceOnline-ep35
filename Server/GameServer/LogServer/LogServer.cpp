// LogServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
// 2008-11-21 by cmkwon, LogServer를 MFC에서 Win32 프로젝트로 변경 - 
//#include "LogServer.h"
//#include "LogServerDlg.h"
#include "resource.h"		// 2008-11-21 by cmkwon, LogServer를 MFC에서 Win32 프로젝트로 변경 - 
#include "LogIOCP.h"
#include "VMemPool.h"
#include "LogGlobal.h"

// 2008-11-21 by cmkwon, LogServer를 MFC에서 Win32 프로젝트로 변경 - 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// TODO: Place code here.
	g_pLogGlobal = new CLogGlobal;
#ifdef ARENA
	if(FALSE == g_pLogGlobal->InitGlobal("Arena Log Server"))
#else
	if(FALSE == g_pLogGlobal->InitGlobal("Log Server"))
#endif //ARENA
	{
		return FALSE;
	}

	// set config root path
	g_pLogGlobal->LoadConfiguration();	
#ifdef ARENA
	g_pLogGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "ArenaLogSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());
#else
	g_pLogGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "LogSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());
#endif //ARENA
	char szSystemLog[256];
	sprintf(szSystemLog, "Log Server Start\r\n\r\n");
	g_pLogGlobal->WriteSystemLog(szSystemLog);

	if(FALSE == CIOCP::SocketInit())
	{
		g_pLogGlobal->WriteSystemLogEX(TRUE, "[ERROR] WinaMain SocketInit error!!\r\n");
		return FALSE;
	}

	CIOCP::SocketInit();
	CVMemPool::vmPoolAddObject(sizeof(COverlapped), SIZE_MAX_LOGSERVER_SESSION * 100);
	if(CVMemPool::vmPoolInit() == FALSE)
	{
		g_pLogGlobal->WriteSystemLogEX(TRUE, "[ERROR] WinaMain vmPoolInit error!!\r\n");
		return FALSE;
	}

	g_pLogGlobal->WndRegisterClass(hInstance, IDI_LOGSERVER, "Log Server");
	// Perform application initialization:
	if (FALSE == g_pLogGlobal->InitInstance (hInstance, nCmdShow, "Log Server", "Log Server"))
	{
		return FALSE;
	}

	// Main message loop:
	MSG			msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CVMemPool::vmPoolClean();
	CIOCP::SocketClean();

	g_pLogGlobal->WriteSystemLogEX(TRUE, "Log Server End\r\n\r\n\r\n");

	SAFE_DELETE(g_pLogGlobal);
	return msg.wParam;
}

// 2008-11-21 by cmkwon, LogServer를 MFC에서 Win32 프로젝트로 변경 - 
//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			if(FALSE == g_pLogGlobal->InitServerSocket())
			{
				g_pLogGlobal->WriteSystemLogEX(TRUE, "[ERROR] LogServer call InitServerSocket() error !!\r\n");			
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
	case WM_DESTROY:
		{
			g_pLogGlobal->EndServerSocket();
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

