// NPCServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "NPCGlobal.h"
#include "NPCIOCP.h"
#include "NPCIOCPSocket.h"
#include "config.h"
#include "VMemPool.h"
#include "N2FSocket.h"
#include "Monster.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_pNPCGlobal = new CNPCGlobal;
#ifdef ARENA
	if(FALSE == g_pNPCGlobal->InitGlobal("Arena NPC Server"))
#else	
	if(FALSE == g_pNPCGlobal->InitGlobal("NPC Server"))
#endif //ARENA
	{
		return FALSE;
	}

 	// TODO: Place code here.
	MSG			msg;

	// set config root path
	g_pNPCGlobal->SetConfigRootPath();

#ifdef ARENA
	g_pNPCGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "ArenaNPCSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());
#else
	g_pNPCGlobal->GetSystemLogManagerPtr()->InitLogManger(TRUE, "NPCSystem", (char*)(string(CONFIG_ROOT) + "../log/SystemLog/").c_str());
#endif //ARENA
	char szSystemLog[256];
	sprintf(szSystemLog, "NPC Server Start\r\n\r\n");
	g_pNPCGlobal->WriteSystemLog(szSystemLog);

	if(FALSE == CIOCP::SocketInit())
	{
		return FALSE;
	}

	CVMemPool::vmPoolAddObject(sizeof(ActionInfo), SIZE_MAX_FIELDSERVER_SESSION * 5);
	CVMemPool::vmPoolAddObject(sizeof(COverlapped), SIZE_MAX_UDP_CHANNEL_SESSION * 20);		// 2010-04-09 by cmkwon, NPCServer 메모리 부족으로 수정함 - 기존 세션당 100개
	CVMemPool::vmPoolAddObject(sizeof(EVENTINFO), SIZE_MAX_UDP_CHANNEL_SESSION*200);			// 2010-04-14 by cmkwon, 서버 메모리 부족 문제 수정 - 맵당 200개의 타일 이벤트 정보 설정 예상
	CVMemPool::vmPoolAddObject(sizeof(CSendPacket), 1000);
	CVMemPool::vmPoolAddObject(sizeof(CRecvPacket), 100);	

	if(CVMemPool::vmPoolInit() == FALSE)
	{
		return FALSE;
	}

	g_pNPCGlobal->WndRegisterClass(hInstance, IDI_NPCSERVER, "NPC Server");
	// Perform application initialization:
	if (FALSE == g_pNPCGlobal->InitInstance (hInstance, nCmdShow, "NPC Server", "NPC Server"))
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

	sprintf(szSystemLog, "NPC Server End\r\n\r\n\r\n");
	DBGOUT(szSystemLog);
	g_pNPCGlobal->WriteSystemLog(szSystemLog);

	SAFE_DELETE(g_pNPCGlobal);
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
			HRESULT hr;
			if( FAILED(hr = g_pNPCGlobal->m_D3DApp.Create(g_pNPCGlobal->GetInstanceHandle(), hWnd)) )
			{
				g_pNPCGlobal->WriteSystemLogEX(TRUE, "====================================================================================================\r\n");
				g_pNPCGlobal->WriteSystemLogEX(TRUE, STRMSG_S_N2NOTIFY_0000);
				g_pNPCGlobal->WriteSystemLogEX(TRUE, "====================================================================================================\r\n");
			}

			SetLastError(0);
			if(g_pNPCGlobal->LoadConfiguration())
			{
				g_pNPCGlobal->CreateN2FSocket(hWnd);
				g_pNPCGlobal->GetN2FSocket()->Connect(g_pNPCGlobal->GetIPFieldServer(), g_pNPCGlobal->GetPortFieldServer());
			}
			else
			{
				MessageBox(hWnd, "LoadConfiguration Error1000", "ERROR", MB_OK);
			}
		}
		break;
	case WM_N2F_ASYNC_EVENT:
		{
			if(g_pNPCGlobal->GetN2FSocket())
			{
				g_pNPCGlobal->GetN2FSocket()->OnAsyncEvent(lParam);
			}
		}
		break;
	case WM_N2F_PACKET_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case CWinSocket::WS_CONNECTED:
				{
					g_pNPCGlobal->EndTimerReconnect();

					if(HIWORD(wParam) == FALSE)
					{
						char	szSystemLog[256];
						sprintf(szSystemLog, "[Error] WndProc(), Can't connect to FieldServer[%15s:%4d] Reconnect\r\n",
							g_pNPCGlobal->GetIPFieldServer(), g_pNPCGlobal->GetPortFieldServer());
						g_pNPCGlobal->WriteSystemLog(szSystemLog);
						DBGOUT(szSystemLog);

						g_pNPCGlobal->StartTimerReconnect();
					}
					else
					{
						DBGOUT(STRMSG_S_N2FIELDCONNECT_0000);

						int nSendType = T_FN_NPCSERVER_START;
						g_pNPCGlobal->GetN2FSocket()->Write((char*)&nSendType, SIZE_FIELD_TYPE_HEADER);
					}
				}
				break;
			case CWinSocket::WS_RECEIVED:
				{
					char * pPacket = NULL;
					int len,nType;
					g_pNPCGlobal->GetN2FSocket()->Read(&pPacket, len);
					if(pPacket)
					{
						nType = 0;
						memcpy(&nType, pPacket, SIZE_FIELD_TYPE_HEADER);
						switch(nType)
						{
						case T_FN_NPCSERVER_START_OK:
							{
								if(g_pNPCGlobal->InitServerSocket())
								{
									g_pNPCGlobal->GetN2FSocket()->SetNPCIOCP((CNPCIOCP*)g_pNPCGlobal->GetGIOCP());
									g_pNPCGlobal->StartTimerTraffic();
									g_pNPCGlobal->StartTimerAliveCheck();
								}
							}
							break;
						case T_FN_NPCSERVER_SUMMON_JACO_MONSTER:
							{
							}
							break;
						}
						SAFE_DELETE(pPacket);		// 2006-04-19 by cmkwon
					}

				}
				break;
			case CWinSocket::WS_CLOSED:
				{
					char	szSystemLog[256];
					sprintf(szSystemLog, STRMSG_S_N2FIELDCONNECT_0001,
						g_pNPCGlobal->GetIPFieldServer(), g_pNPCGlobal->GetPortFieldServer());
					g_pNPCGlobal->WriteSystemLog(szSystemLog);
					DBGOUT(szSystemLog);

					g_pNPCGlobal->EndServerSocket();
					g_pNPCGlobal->StartTimerReconnect();
				}
				break;
			case CWinSocket::WS_ERROR:
				{
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
	case WM_TIMER:
		{
			switch(wParam)
			{
			case TIMERID_TRAFFIC:
				{
					g_pNPCGlobal->CheckServerThread();
					g_pNPCGlobal->CalculateIOCPTraffic();
				}
				break;
			case TIMERID_ALIVE_CHECK:
				{
					//////////////////////////////////////////////////////
					// Field Server로 Alive를 전송한다
					if(g_pNPCGlobal->GetN2FSocket()
						&& g_pNPCGlobal->GetN2FSocket()->IsConnected())
					{
						int nSendType = T_FN_CONNECT_ALIVE;
						g_pNPCGlobal->GetN2FSocket()->Write((char*)&nSendType, SIZE_FIELD_TYPE_HEADER);
					}

					//////////////////////////////////////////////////////
					// NPC Server는 TCP 접속이 없으므로 Alive Check를 하지 않는다
					//g_pNPCGlobal->CheckClientAlive();
				}
				break;
			case TIMERID_RECONNECT:
				{
					g_pNPCGlobal->EndTimerReconnect();
					if(g_pNPCGlobal->GetN2FSocket())
					{
						g_pNPCGlobal->GetN2FSocket()->Connect(g_pNPCGlobal->GetIPFieldServer(), g_pNPCGlobal->GetPortFieldServer());
					}
				}
				break;
			}

		}
		break;
	case WM_DESTROY:
		{
			g_pNPCGlobal->EndServerSocket();
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

