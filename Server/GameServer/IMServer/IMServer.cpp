// IMServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "IMGlobal.h"
#include "IMIOCP.h"
#include "IMIOCPSocket.h"
#include <fstream>
#include "PreIMWinsocket.h"
#include "config.h"
#include "VMemPool.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_pIMGlobal = new CIMGlobal;
#ifdef ARENA
	if(FALSE == g_pIMGlobal->InitGlobal("Arena IM Server"))
#else
	if(FALSE == g_pIMGlobal->InitGlobal("IM Server"))
#endif //ARENA
	{
		return FALSE;
	}

 	// TODO: Place code here.
	MSG			msg;

	// set config root path
	g_pIMGlobal->SetConfigRootPath();

	#ifdef ARENA
	g_pIMGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "ArenaIMSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());
#else
	g_pIMGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "IMSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());
#endif //ARENA
	char szSystemLog[256];
	sprintf(szSystemLog, "IM Server Start\r\n\r\n");
	g_pIMGlobal->WriteSystemLog(szSystemLog);

	if(FALSE == CIOCP::SocketInit())
	{
		return FALSE;
	}
	CVMemPool::vmPoolAddObject(sizeof(COverlapped), SIZE_MAX_IMSERVER_SESSION * 10);
	CVMemPool::vmPoolAddObject(sizeof(CSendPacket), 1000);
	CVMemPool::vmPoolAddObject(sizeof(CRecvPacket), 100);	

	if(CVMemPool::vmPoolInit() == FALSE)
	{
		return FALSE;
	}

	g_pIMGlobal->WndRegisterClass(hInstance, IDI_IMSERVER, _T("IM Server"));
	// Perform application initialization:
	if (FALSE == g_pIMGlobal->InitInstance (hInstance, nCmdShow, _T("IM Server"), _T("IM Server")))
	{
		return FALSE;
	}

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CVMemPool::vmPoolClean();
	CIOCP::SocketClean();

	sprintf(szSystemLog, "IM Server End\r\n\r\n\r\n");
	g_pIMGlobal->WriteSystemLog(szSystemLog);

	SAFE_DELETE(g_pIMGlobal);
	return msg.wParam;
}




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
			SetLastError(0);
			if(g_pIMGlobal->LoadConfiguration())
			{
				g_pIMGlobal->CreateIM2PreWinSokcet(hWnd);
				g_pIMGlobal->GetIM2PreWinSocket()->Connect(g_pIMGlobal->GetIPPreServer(), g_pIMGlobal->GetPortPreServer());
			}
			else
			{
				MessageBox(hWnd, "LoadConfiguration Error", "ERROR", MB_OK);
			}
		}
		break;
	case WM_PREIM_ASYNC_EVENT:
		{
			if(g_pIMGlobal->GetIM2PreWinSocket()){ g_pIMGlobal->GetIM2PreWinSocket()->OnAsyncEvent(lParam);}
		}
		break;
	case WM_PREIM_PACKET_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case CWinSocket::WS_ERROR:
				{
				}
				break;
			case CWinSocket::WS_CONNECTED:
				{
					g_pIMGlobal->EndTimerReconnect();
					if(HIWORD(wParam) == FALSE)
					{
						char	szSystemLog[256];
						sprintf(szSystemLog, "[Error] WndProc(), Can't connect to PreServer[%15s:%4d]\r\n",
							g_pIMGlobal->GetIPPreServer(), g_pIMGlobal->GetPortPreServer());
						g_pIMGlobal->WriteSystemLog(szSystemLog);
						DBGOUT(szSystemLog);

						g_pIMGlobal->StartTimerReconnect();
					}
					else
					{
						// 2007-12-18 by cmkwon, 시스템 로그 추가
						g_pIMGlobal->WriteSystemLogEX(TRUE, STRMSG_S_I2PRECONNECT_0000);

						if(g_pIMGlobal->InitServerSocket())
						{
							g_pIMGlobal->StartTimerTraffic();
							g_pIMGlobal->StartTimerAliveCheck();

							// send MSG_IP_CONNECT_IM_CONNECT
							INIT_MSG_WITH_BUFFER(MSG_IP_CONNECT_IM_CONNECT, T_IP_CONNECT_IM_CONNECT, pIMConnect, buf);
							strncpy(pIMConnect->ServerGroupName, g_pIMGlobal->GetServerGroupName(), SIZE_MAX_SERVER_NAME);
// 2006-05-10 by cmkwon, 아래와 같이 수정함 - IP도 포함시켜서 전송
//							pIMConnect->IMServerListenPort	= g_pIMGlobal->GetPortListening();
// 2006-05-23 by cmkwon, 아래와 같이 수정함
//							pIMConnect->IMServerID.SetValue(g_pIMGlobal->GetIPLocal(), g_pIMGlobal->GetPortListening());
							pIMConnect->IMServerID.SetValue(g_pIMGlobal->GetPublicIPLocal(), g_pIMGlobal->GetPortListening());
							g_pIMGlobal->GetIM2PreWinSocket()->Write(buf, MSG_SIZE(MSG_IP_CONNECT_IM_CONNECT));
						}
					}
				}
				break;
			case CWinSocket::WS_CLOSED:
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, STRMSG_S_I2PRECONNECT_0001,
						g_pIMGlobal->GetIPPreServer(), g_pIMGlobal->GetPortPreServer());
					g_pIMGlobal->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);

					g_pIMGlobal->EndServerSocket();
					g_pIMGlobal->StartTimerReconnect();
				}
				break;
			}
		}
		break;
	case WM_TIMER:
		{
			switch(wParam)
			{
			case TIMERID_TRAFFIC:
				{
					g_pIMGlobal->CheckServerThread();
					g_pIMGlobal->CalculateIOCPTraffic();
				}
				break;
			case TIMERID_ALIVE_CHECK:
				{
					//////////////////////////////////////////////////////
					// PreServer로 Alive 패킷을 전송한다
					if(g_pIMGlobal->GetIM2PreWinSocket() 
						&& g_pIMGlobal->GetIM2PreWinSocket()->IsConnected())
					{
						int nSendType = T_IP_CONNECT_ALIVE;
						g_pIMGlobal->GetIM2PreWinSocket()->Write((char*)&nSendType, SIZE_FIELD_TYPE_HEADER);

						g_pIMGlobal->StartTimerSendServerGroupInfo();
					}
					g_pIMGlobal->CheckClientAlive();
				}
				break;
			case TIMERID_RECONNECT:
				{					
					g_pIMGlobal->EndTimerReconnect();
					if(g_pIMGlobal->GetIM2PreWinSocket())
					{
						g_pIMGlobal->GetIM2PreWinSocket()->Connect(g_pIMGlobal->GetIPPreServer(), g_pIMGlobal->GetPortPreServer());
					}
				}
			case TIMERID_SERVER_GROUP_INFO:
				{
					if(g_pIMGlobal->GetIM2PreWinSocket() 
						&& g_pIMGlobal->GetIM2PreWinSocket()->IsConnected()
						&& g_pIMGlobal->GetGIOCP() 
						&& g_pIMGlobal->GetGIOCP()->GetListeningFlag())
					{
						INIT_MSG_WITH_BUFFER(MSG_IP_GET_SERVER_GROUP_INFO_ACK, T_IP_GET_SERVER_GROUP_INFO_ACK, pSACK, SendBuf);
						strncpy(pSACK->ServerGroupName, g_pIMGlobal->GetServerGroupName(), SIZE_MAX_SERVER_NAME);
						pSACK->IMCurrentUserCounts	= ((CIMIOCP*)g_pIMGlobal->GetGIOCP())->m_MapAccountUniqueNumber.size();
						pSACK->IMMaxUserCounts		= ((CIMIOCP*)g_pIMGlobal->GetGIOCP())->m_uiIMMaxTotalUserCounts;
						g_pIMGlobal->GetIM2PreWinSocket()->Write(SendBuf, MSG_SIZE(MSG_IP_GET_SERVER_GROUP_INFO_ACK));
					}
				}
				break;
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
			g_pIMGlobal->EndServerSocket();
			g_pIMGlobal->DestroyIM2PreWinSocket();
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


