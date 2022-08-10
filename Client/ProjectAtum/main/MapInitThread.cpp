// MapInitThread.cpp: implementation of the CMapInitThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapInitThread.h"
#include "AtumApplication.h"
#include "SceneData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapInitThread::CMapInitThread()
{
}

CMapInitThread::~CMapInitThread()
{

}

DWORD CMapInitThread::Run()
{
	DBGOUT("Map Loading State : Loading Start\n");
	BOOL bResult = g_pD3dApp->m_pScene->InitBackground();
	if(!bResult)
		g_pD3dApp->CheckError(APP_ERR_MAPLOAD);
	m_bRunning = FALSE;

	// 2009. 09. 10 by ckPark �ʷε��� ��Ŷ���� ť�� �׾Ƶε��� ����
	PostMessage( g_pD3dApp->GetHwnd(), WM_PACKET_NOTIFY, MAKEWPARAM(CWinSocket::WS_RECEIVED, 0), 0 );
	// end 2009. 09. 10 by ckPark �ʷε��� ��Ŷ���� ť�� �׾Ƶε��� ����

	DBGOUT("Map Loading State : Loading Done\n");
	return 0;
}
