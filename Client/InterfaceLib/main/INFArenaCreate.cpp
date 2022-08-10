// INFArenaCreate.cpp: implementation of the CINFArenaCreate class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AtumApplication.h"
#include "INFArenaCreate.h"
#include "INFCitySupply.h"
#include "INFCityBase.h"
#include "INFScrollbar.h"
#include "INFImage.h"
#include "D3dHanFont.h"
#include "ItemInfo.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "FieldWinSocket.h"
#include "GameDataLast.h"
#include "StoreData.h"
#include "WeaponItemInfo.h"
#include "INFWindow.h"
#include "INFGameMain.h"
#include "INFItemInfo.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFIcon.h"
#include "AtumDatabase.h"
#include "dxutil.h"
#include "Chat.h"
#include "Interface.h"
#include "INFGameArena.h"


#define MAX_PASSWORD									4

#define ARENA_CREATE_BUTTON_X							136
#define ARENA_CREATE_BUTTON_Y							168

#define ARENA_CANCEL_BUTTON_X							179
#define ARENA_CANCEL_BUTTON_Y							ARENA_CREATE_BUTTON_Y

#define ARENA_BASE_BUTTON_W								38 
#define ARENA_BASE_BUTTON_H								17

#define ARENA_CREATE_COUNT_X							100	
#define ARENA_CREATE_COUNT_Y							54
#define ARENA_CREATE_COUNT_W							32
#define ARENA_CREATE_COUNT_H							15
#define ARENA_CREATE_COUNT_COMBO_X						119
#define ARENA_CREATE_COUNT_COMBO_Y						55
#define ARENA_CREATE_COUNT_FONT_X						117
#define ARENA_CREATE_COUNT_FONT_Y						53

#define ARENA_CREATE_MODE_X								100
#define ARENA_CREATE_MODE_Y								82
#define ARENA_CREATE_MODE_W								102
#define ARENA_CREATE_MODE_H								15
#define ARENA_CREATE_MODE_COMBO_X						188
#define ARENA_CREATE_MODE_COMBO_Y						83
#define ARENA_CREATE_MODE_FONT_X						147
#define ARENA_CREATE_MODE_FONT_Y						81

#define ARENA_CREATE_PASS_X								100
#define ARENA_CREATE_PASS_Y								110
#define ARENA_CREATE_PASS_W								85
#define ARENA_CREATE_PASS_H								15
#define ARENA_CREATE_PASS_FONT_X						106
#define ARENA_CREATE_PASS_FONT_Y						110



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFArenaCreate::CINFArenaCreate(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	m_pParent = pParent;	// CGameMain*
	m_pGameData = NULL;
	m_pBuildingInfo = pBuilding;

	m_bShow = FALSE;
	m_nStateCancelB = BUTTON_STATE_NORMAL;
	m_nStateCreateB = BUTTON_STATE_NORMAL;
//	m_nStateCbArrCount = BUTTON_STATE_NORMAL;
//	m_nStateCbArrMode = BUTTON_STATE_NORMAL;
	m_ntempMode = -1;

	m_nStartX = m_nStartY = 0;
}
CINFArenaCreate::CINFArenaCreate()
{
	m_bShow = FALSE;
	m_nStateCancelB = BUTTON_STATE_NORMAL;
	m_nStateCreateB = BUTTON_STATE_NORMAL;
//	m_nStateCbArrCount = BUTTON_STATE_NORMAL;
//	m_nStateCbArrMode = BUTTON_STATE_NORMAL;

	m_nStartX = m_nStartY = 0;
}

CINFArenaCreate::~CINFArenaCreate()
{

}
HRESULT CINFArenaCreate::InitDeviceObjects()
{
	int i;
	DataHeader	* pDataHeader;
	char buf[64];
	for(i = 0 ; i < BUTTON_STATE_NUMBER ; i++)
	{
		wsprintf(buf,"scre%d",i);
		pDataHeader = FindResource(buf);
		m_pImgCreateB[i] = new CINFImage;
		m_pImgCreateB[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

//		wsprintf(buf,"comarr%d",i);
//		pDataHeader = FindResource(buf);
//		m_pImgCbArr[i] = new CINFImage;
//		m_pImgCbArr[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
//
		wsprintf(buf,"shmcan0%d",i);
		pDataHeader = FindResource(buf);
		m_pImgCancelB[i] = new CINFImage;
		m_pImgCancelB[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

	}

	m_pFontCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontCount->InitDeviceObjects(g_pD3dDev);
	m_pFontMode = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontMode->InitDeviceObjects(g_pD3dDev);
	m_pFontPass = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	m_pFontPass->InitDeviceObjects(g_pD3dDev);

	pDataHeader = FindResource("arecreate");
	m_pImgAreCreate = new CINFImage;
	m_pImgAreCreate->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

	pDataHeader = FindResource("cbcount");
	m_pImgCbCount = new CINFImage;
	m_pImgCbCount->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

	pDataHeader = FindResource("cbamode");
	m_pImgCbAmode = new CINFImage;
	m_pImgCbAmode->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

	
	return S_OK;


}
HRESULT CINFArenaCreate::RestoreDeviceObjects()
{
	int i;
	for(i = 0; i < BUTTON_STATE_NUMBER; i++)
	{
		m_pImgCreateB[i]->RestoreDeviceObjects();
//		m_pImgCbArr[i]->RestoreDeviceObjects();
		m_pImgCancelB[i]->RestoreDeviceObjects();
	}
	m_pFontCount->RestoreDeviceObjects();
	m_pFontMode->RestoreDeviceObjects();
	m_pFontPass->RestoreDeviceObjects();

	m_pImgAreCreate->RestoreDeviceObjects();
	m_pImgCbCount->RestoreDeviceObjects();
	m_pImgCbAmode->RestoreDeviceObjects();
	return S_OK;
}
HRESULT CINFArenaCreate::DeleteDeviceObjects()
{
	int i;
	DbgOut("Arena Create DeleteDeviceObjects()\n");
	for(i = 0; i < BUTTON_STATE_NUMBER; i++)
	{
		m_pImgCreateB[i]->DeleteDeviceObjects();
//		m_pImgCbArr[i]->DeleteDeviceObjects();
		m_pImgCancelB[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgCreateB[i]);
//		SAFE_DELETE(m_pImgCbArr[i]);
		SAFE_DELETE(m_pImgCancelB[i]);
	}
	m_pFontCount->DeleteDeviceObjects();
	m_pFontMode->DeleteDeviceObjects();
	m_pFontPass->DeleteDeviceObjects();

	m_pImgAreCreate->DeleteDeviceObjects();
	m_pImgCbCount->DeleteDeviceObjects();
	m_pImgCbAmode->DeleteDeviceObjects();

	SAFE_DELETE(m_pImgAreCreate);
	SAFE_DELETE(m_pImgCbCount);
	SAFE_DELETE(m_pImgCbCount);

	return S_OK;
}
HRESULT CINFArenaCreate::InvalidateDeviceObjects()
{
	int i;
	for(i = 0; i < BUTTON_STATE_NUMBER; i++)
	{
		m_pImgCreateB[i]->InvalidateDeviceObjects();
//		m_pImgCbArr[i]->InvalidateDeviceObjects();
		m_pImgCancelB[i]->InvalidateDeviceObjects();
	}
	m_pFontCount->InvalidateDeviceObjects();
	m_pFontMode->InvalidateDeviceObjects();
	m_pFontPass->InvalidateDeviceObjects();

	m_pImgAreCreate->InvalidateDeviceObjects();
	m_pImgCbCount->InvalidateDeviceObjects();
	m_pImgCbAmode->InvalidateDeviceObjects();


	return S_OK;
}
void CINFArenaCreate::Render()
{
	char ctemp[64];
	int i;
	SIZE size;
	if(m_bShow)
	{
		m_pImgAreCreate->Move(m_nStartX,m_nStartY);
		m_pImgAreCreate->Render();

		m_pImgCreateB[m_nStateCreateB]->Move(m_nStartX + ARENA_CREATE_BUTTON_X, m_nStartY + ARENA_CREATE_BUTTON_Y);
		m_pImgCreateB[m_nStateCreateB]->Render();

		m_pImgCancelB[m_nStateCancelB]->Move(m_nStartX + ARENA_CANCEL_BUTTON_X, m_nStartY + ARENA_CANCEL_BUTTON_Y);
		m_pImgCancelB[m_nStateCancelB]->Render();

//		m_pImgCbArr[m_nStateCbArrCount]->Move(m_nStartX + ARENA_CREATE_COUNT_COMBO_X,m_nStartY + ARENA_CREATE_COUNT_COMBO_Y);
//		m_pImgCbArr[m_nStateCbArrCount]->Render();
//
//		m_pImgCbArr[m_nStateCbArrMode]->Move(m_nStartX + ARENA_CREATE_MODE_COMBO_X,m_nStartY + ARENA_CREATE_MODE_COMBO_Y);
//		m_pImgCbArr[m_nStateCbArrMode]->Render();

		wsprintf(ctemp,"%d",m_nCount);
		size = m_pFontCount->GetStringSize(ctemp);
		m_pFontCount->DrawText(m_nStartX + ARENA_CREATE_COUNT_FONT_X - size.cx,m_nStartY + ARENA_CREATE_COUNT_FONT_Y,GUI_FONT_COLOR_W,ctemp);

		if(m_nSelectMode == ARENAMODE_DEATHMATCH)
			wsprintf(ctemp,"%s",STRMSG_C_070427_0100);
		else
			wsprintf(ctemp,"%s",STRMSG_C_070427_0101);
		size = m_pFontCount->GetStringSize(ctemp);
		m_pFontMode->DrawText(m_nStartX + ARENA_CREATE_MODE_FONT_X - (size.cx/2),m_nStartY + ARENA_CREATE_MODE_FONT_Y,GUI_FONT_COLOR_W,ctemp);

		if(m_bCbCount)
		{// 인원 콤보 박스 열기.
			for(i = 0; i < m_vecPersons.size(); i++)
			{
				
				// 콤보 배경 이미지
				m_pImgCbCount->Move(m_nStartX + ARENA_CREATE_COUNT_X, 
					m_nStartY + ARENA_CREATE_COUNT_Y + ARENA_CREATE_COUNT_H +(ARENA_CREATE_COUNT_H * i));
				m_pImgCbCount->Render();
				
				// 인원 숫자.
				wsprintf(ctemp,"%d",m_vecPersons[i]);
				size = m_pFontCount->GetStringSize(ctemp);
				m_pFontCount->DrawText(m_nStartX + ARENA_CREATE_COUNT_FONT_X - size.cx,
					m_nStartY + ARENA_CREATE_COUNT_FONT_Y + ARENA_CREATE_COUNT_H + (ARENA_CREATE_COUNT_H * i),
					GUI_FONT_COLOR_Y,ctemp);
			}

		}
		if(m_bCbMode)
		{// 모드 콤보 박스 열기.
			for(i = 0; i < m_nMode; i++)
			{
				m_pImgCbAmode->Move(m_nStartX + ARENA_CREATE_MODE_X,
					m_nStartY + ARENA_CREATE_MODE_Y + ARENA_CREATE_MODE_H + (ARENA_CREATE_MODE_H * i));
				m_pImgCbAmode->Render();

				if((i+1) == ARENAMODE_DEATHMATCH)
					wsprintf(ctemp,"%s",STRMSG_C_070427_0100);
				else if((i+1) == ARENAMODE_ROUND)
					wsprintf(ctemp,"%s",STRMSG_C_070427_0101);
				size = m_pFontCount->GetStringSize(ctemp);
				m_pFontMode->DrawText(m_nStartX + ARENA_CREATE_MODE_FONT_X - (size.cx/2),
					m_nStartY + ARENA_CREATE_MODE_FONT_Y + ARENA_CREATE_MODE_H + (ARENA_CREATE_MODE_H * i),
					GUI_FONT_COLOR_Y,ctemp);

			}

		}
		if(m_bTxtPass)
		{// 비밀번호 입력중일경우.
			wsprintf(ctemp,"%s_",m_cTeamPW);
			m_pFontPass->DrawText(m_nStartX + ARENA_CREATE_PASS_FONT_X,
				m_nStartY + ARENA_CREATE_PASS_FONT_Y,
				GUI_FONT_COLOR_W,ctemp);
		}else
		{
			if(strlen(m_cTeamPW))
			{
				wsprintf(ctemp,"%s",m_cTeamPW);
					m_pFontPass->DrawText(m_nStartX + ARENA_CREATE_PASS_FONT_X,
						m_nStartY + ARENA_CREATE_PASS_FONT_Y,
						GUI_FONT_COLOR_W,ctemp);


			}
		}
	}
}
void CINFArenaCreate::Tick()
{
	
}
int CINFArenaCreate::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_bShow)
	{
		switch(uMsg)
		{
			case WM_MOUSEMOVE:
				{
					POINT pt;
					pt.x = LOWORD(lParam);
					pt.y = HIWORD(lParam);
					CheckMouseReverse(&pt);

					if(pt.y > ARENA_CREATE_BUTTON_Y + m_nStartY &&
						pt.y < ARENA_CREATE_BUTTON_Y + ARENA_BASE_BUTTON_H + m_nStartY)
					{
						if(pt.x > ARENA_CREATE_BUTTON_X + m_nStartX &&
							pt.x < ARENA_CREATE_BUTTON_X + ARENA_BASE_BUTTON_W + m_nStartX)
						{
							m_nStateCreateB = BUTTON_STATE_UP;
						}
						else
						{
							m_nStateCreateB = BUTTON_STATE_NORMAL;
						}
						if(pt.x > ARENA_CANCEL_BUTTON_X + m_nStartX &&
							pt.x < ARENA_CANCEL_BUTTON_X + ARENA_BASE_BUTTON_W + m_nStartX)
						{
							m_nStateCancelB = BUTTON_STATE_UP;
						}
						else
						{
							m_nStateCancelB = BUTTON_STATE_NORMAL;
						}

					}else
					{
						m_nStateCreateB = BUTTON_STATE_NORMAL;
						m_nStateCancelB = BUTTON_STATE_NORMAL;
					}
//					// 콤보 박스 처리(인원).
//					if(pt.x > ARENA_CREATE_COUNT_X + m_nStartX &&
//						pt.x < ARENA_CREATE_COUNT_X + ARENA_CREATE_COUNT_W + m_nStartX &&
//						pt.y > ARENA_CREATE_COUNT_Y + m_nStartY &&
//						pt.y < ARENA_CREATE_COUNT_Y + ARENA_CREATE_COUNT_H + m_nStartY)
//					{
//						m_nStateCbArrCount = BUTTON_STATE_UP;
//					}
//					else
//					{
//						m_nStateCbArrCount = BUTTON_STATE_NORMAL;
//					}
//					// 콤보 박스 처리(모드).
//					if(pt.x > ARENA_CREATE_MODE_X + m_nStartX &&
//						pt.x < ARENA_CREATE_MODE_X + ARENA_CREATE_MODE_W + m_nStartX &&
//						pt.y > ARENA_CREATE_MODE_Y + m_nStartY &&
//						pt.y < ARENA_CREATE_MODE_Y + ARENA_CREATE_MODE_H + m_nStartY)
//					{
//						m_nStateCbArrMode = BUTTON_STATE_UP;
//					}
//					else
//					{
//						m_nStateCbArrMode = BUTTON_STATE_NORMAL;
//					}

				}
				break;
			case WM_LBUTTONDOWN:
				{
					POINT pt;
					pt.x = LOWORD(lParam);
					pt.y = HIWORD(lParam);
					CheckMouseReverse(&pt);
					// 콤보 박스가 활성화 되어있을대는 제일 우선적으로 처리한다.
					if(m_bCbCount &&
						pt.x > ARENA_CREATE_COUNT_X + m_nStartX &&
						pt.x < ARENA_CREATE_COUNT_X + ARENA_CREATE_COUNT_W + m_nStartX )
//						pt.y > ARENA_CREATE_COUNT_Y + m_nStartY &&
//						pt.y < ARENA_CREATE_COUNT_Y + ARENA_CREATE_COUNT_H + m_nStartY)
					{
						int nTempSelectCount = (pt.y - (ARENA_CREATE_COUNT_Y + ARENA_CREATE_COUNT_H + m_nStartY)) / ARENA_CREATE_COUNT_H;

						if(nTempSelectCount < 0 
							|| nTempSelectCount > m_vecPersons.size())
						{
						}
						else
						{
							m_nSelectCount = nTempSelectCount;
							m_nCount = m_vecPersons[m_nSelectCount];
						}
						m_bCbCount = FALSE;
						
						break;
					}
				

					if(m_bCbMode &&
						pt.x > ARENA_CREATE_MODE_X + m_nStartX &&
						pt.x < ARENA_CREATE_MODE_X + ARENA_CREATE_MODE_W + m_nStartX )
//						pt.y > ARENA_CREATE_MODE_Y + m_nStartY &&
//						pt.y < ARENA_CREATE_MODE_Y + ARENA_CREATE_MODE_H + m_nStartY)
					{
						int nTempSelectMode = (pt.y - (ARENA_CREATE_MODE_Y +ARENA_CREATE_MODE_H + m_nStartY)) / ARENA_CREATE_MODE_H;
						if(nTempSelectMode < 0 
							|| nTempSelectMode >= m_nMode)			
						{
						}
						else
						{
							m_nSelectMode = nTempSelectMode + 1;			// 1 데스 매치 2 라운드 이다 0은 없기때문에 1을 더해준다.
						}
						m_bCbMode = FALSE;
						break;

					}
				
					//--------------------------------------------------------------------------//
					

				
					if(pt.y > ARENA_CREATE_BUTTON_Y + m_nStartY &&
						pt.y < ARENA_CREATE_BUTTON_Y + ARENA_BASE_BUTTON_H + m_nStartY)
					{
						if(pt.x > ARENA_CREATE_BUTTON_X + m_nStartX &&
							pt.x < ARENA_CREATE_BUTTON_X + ARENA_BASE_BUTTON_W + m_nStartX)
						{
							m_nStateCreateB = BUTTON_STATE_DOWN;
						}
						else
						{
							m_nStateCreateB = BUTTON_STATE_NORMAL;
						}
						if(pt.x > ARENA_CANCEL_BUTTON_X + m_nStartX &&
							pt.x < ARENA_CANCEL_BUTTON_X + ARENA_BASE_BUTTON_W + m_nStartX)
						{
							m_nStateCancelB = BUTTON_STATE_DOWN;
						}
						else
						{
							m_nStateCancelB = BUTTON_STATE_NORMAL;
						}

					}else
					{
						m_nStateCreateB = BUTTON_STATE_NORMAL;
						m_nStateCancelB = BUTTON_STATE_NORMAL;
					}
					// 콤보 박스 처리(인원).
					if(!m_bCbMode &&
						pt.x > ARENA_CREATE_COUNT_X + m_nStartX &&
						pt.x < ARENA_CREATE_COUNT_X + ARENA_CREATE_COUNT_W + m_nStartX &&
						pt.y > ARENA_CREATE_COUNT_Y + m_nStartY &&
						pt.y < ARENA_CREATE_COUNT_Y + ARENA_CREATE_COUNT_H + m_nStartY)
					{
//						m_nStateCbArrCount = BUTTON_STATE_DOWN;
						m_bCbCount = TRUE;
					}
					else
					{
//						m_nStateCbArrCount = BUTTON_STATE_NORMAL;
						m_bCbCount = FALSE;
					}
					// 콤보 박스 처리(모드).
					if(!m_bCbCount &&
						pt.x > ARENA_CREATE_MODE_X + m_nStartX &&
						pt.x < ARENA_CREATE_MODE_X + ARENA_CREATE_MODE_W + m_nStartX &&
						pt.y > ARENA_CREATE_MODE_Y + m_nStartY &&
						pt.y < ARENA_CREATE_MODE_Y + ARENA_CREATE_MODE_H + m_nStartY)
					{
//						m_nStateCbArrMode = BUTTON_STATE_DOWN;
						m_bCbMode = TRUE;
					}
					else
					{
//						m_nStateCbArrMode = BUTTON_STATE_NORMAL;
						m_bCbMode = FALSE;
					}



				}
				break;
			case WM_LBUTTONUP:
				{
					POINT pt;
					pt.x = LOWORD(lParam);
					pt.y = HIWORD(lParam);
					CheckMouseReverse(&pt);
					if(pt.y > ARENA_CREATE_BUTTON_Y + m_nStartY &&
						pt.y < ARENA_CREATE_BUTTON_Y + ARENA_BASE_BUTTON_H + m_nStartY)
					{
						if(pt.x > ARENA_CREATE_BUTTON_X + m_nStartX &&
							pt.x < ARENA_CREATE_BUTTON_X + ARENA_BASE_BUTTON_W + m_nStartX)
						{
							m_nStateCreateB = BUTTON_STATE_UP;
							SendCreateTeam();
							HideCreateWindow();
						}
						else
						{
							m_nStateCreateB = BUTTON_STATE_NORMAL;
						}
						if(pt.x > ARENA_CANCEL_BUTTON_X + m_nStartX &&
							pt.x < ARENA_CANCEL_BUTTON_X + ARENA_BASE_BUTTON_W + m_nStartX)
						{
							m_nStateCancelB = BUTTON_STATE_UP;
							HideCreateWindow();
						}
						else
						{
							m_nStateCancelB = BUTTON_STATE_NORMAL;
						}

					}else
					{
						m_nStateCreateB = BUTTON_STATE_NORMAL;
						m_nStateCancelB = BUTTON_STATE_NORMAL;
					}
					// 비밀번호 
					if(pt.x > ARENA_CREATE_PASS_X + m_nStartX &&
						pt.x < ARENA_CREATE_PASS_X + m_nStartX + ARENA_CREATE_PASS_W &&
						pt.y > ARENA_CREATE_PASS_Y + m_nStartY &&
						pt.y < ARENA_CREATE_PASS_Y + m_nStartY + ARENA_CREATE_PASS_H)
					{
						m_bTxtPass = TRUE;
					}
					else
					{
						m_bTxtPass = FALSE;
					}
//					// 콤보 박스 처리(인원).
//					if(pt.x > ARENA_CREATE_COUNT_X + m_nStartX &&
//						pt.x < ARENA_CREATE_COUNT_X + ARENA_CREATE_COUNT_W + m_nStartX &&
//						pt.y > ARENA_CREATE_COUNT_Y + m_nStartY &&
//						pt.y < ARENA_CREATE_COUNT_Y + ARENA_CREATE_COUNT_H + m_nStartY)
//					{
//						m_nStateCbArrCount = BUTTON_STATE_UP;
//					}
//					else
//					{
//						m_nStateCbArrCount = BUTTON_STATE_NORMAL;
//					}
//					// 콤보 박스 처리(모드).
//					if(pt.x > ARENA_CREATE_MODE_X + m_nStartX &&
//						pt.x < ARENA_CREATE_MODE_X + ARENA_CREATE_MODE_W + m_nStartX &&
//						pt.y > ARENA_CREATE_MODE_Y + m_nStartY &&
//						pt.y < ARENA_CREATE_MODE_Y + ARENA_CREATE_MODE_H + m_nStartY)
//					{
//						m_nStateCbArrMode = BUTTON_STATE_UP;
//					}
//					else
//					{
//						m_nStateCbArrMode = BUTTON_STATE_NORMAL;
//					}
				}
				break;
				// 2009-01-30 by bhsohn 상점 숫자 입력 방식 변경
// 			case WM_CHAR:
// 				{
// 					if(m_bTxtPass)
// 					{
// 						char code = wParam;
// 						int num = strlen(m_cTeamPW);
// 						if(code == VK_BACK)
// 						{
// 							if(num > 0)
// 								m_cTeamPW[num-1] = NULL;
// 						}
// 						if(num > MAX_PASSWORD)
// 						{
// 							break;
// 						}
// 						if(code >= '0' && code <= '9' )
// 						{
// 							m_cTeamPW[num] = code;
// 							m_cTeamPW[num+1] = NULL;
// 						}
// 						
// 					}
// 				}
// 				break;
			case WM_KEYDOWN:
				{
					if(m_bTxtPass)
					{
						DWORD dwCode = lParam;

						int num = strlen(m_cTeamPW);
						if(0x000e0001 == dwCode)
						{
							if(num > 0)
								m_cTeamPW[num-1] = NULL;
						}
						if(num > MAX_PASSWORD)
						{
							break;
						}
						int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
						if(nNumber != -1 )					
						{
							m_cTeamPW[num] = '0'+nNumber;
							m_cTeamPW[num+1] = NULL;

						}						
					}
				}
				break;
			// end 2009-01-30 by bhsohn 상점 숫자 입력 방식 변경
		}
	}

	return INF_MSGPROC_NORMAL;
}

VOID CINFArenaCreate::SetPos(UINT x, UINT y)
{
	m_nStartX = x;
	m_nStartY = y;
}

VOID CINFArenaCreate::AddAllPersons(SARENA_REQUEST_CREATE_TEAMINFO *pTeamInfo)
{
	if(pTeamInfo->ArenaMode != m_ntempMode)
	{
		m_nMode++;
		m_ntempMode = pTeamInfo->ArenaMode;
	}
	m_vecAllPersons.push_back((*pTeamInfo));
	
}

VOID CINFArenaCreate::ClearAllPersons()
{
	m_ntempMode = -1;
	m_vecAllPersons.clear();
}
VOID CINFArenaCreate::SetPersons(BYTE BMode)
{
	ClearPersons();
	vector<SARENA_REQUEST_CREATE_TEAMINFO>::iterator it = m_vecAllPersons.begin();
	while(it != m_vecAllPersons.end())
	{
		if(it->ArenaMode == BMode)
			m_vecPersons.push_back(it->ReqMemberNum);
		it++;
	}
	m_nCount = m_vecPersons[m_nSelectCount];
}

VOID CINFArenaCreate::ClearPersons()
{
	m_vecPersons.clear();
}
VOID CINFArenaCreate::ChangeArenaMode(BYTE BMode)
{
	SetPersons(BMode);
	m_nSelectMode = (UINT)BMode;
}
VOID CINFArenaCreate::ShowCreateWindow()
{
	m_bShow = TRUE;
	m_nSelectCount = 0;
	memset(m_cTeamPW,0x00,SIZE_MAX_TEAM_PW);
	m_nSelectMode = ARENAMODE_DEATHMATCH;

}
VOID CINFArenaCreate::HideCreateWindow()
{
	m_bShow = FALSE;
	ClearPersons();
	memset(m_cTeamPW,0x00,SIZE_MAX_TEAM_PW);
}
VOID CINFArenaCreate::SendCreateTeam()
{
	// 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	if(TRUE == g_pD3dApp->IsDoingInfluenceWar())
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_070427_0104,COLOR_ERROR); //"세력전이 진행 중이므로 참가할 수 없습니다."
		return;
	}
	// end 2008-03-07 by bhsohn 세력전시, 아레나 이용 못하게 변경
	// 2008-03-10 by bhsohn 아레나 관련 버그 수정
	if(TRUE == g_pInterface->IsArenaGameState(ARENA_GAME_STATE_TEAMINFO))
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080225_0207,COLOR_ERROR);//"이미 아레나 대기방에 참여중입니다."
		return;	
	}
	// end 2008-03-10 by bhsohn 아레나 관련 버그 수정

	MSG_FC_ARENA_CREATE_TEAM sMsg;
	memset(&sMsg,0x00,sizeof(MSG_FC_ARENA_CREATE_TEAM));
	sMsg.ArenaMode = m_nSelectMode;
	// 2007-11-22 by bhsohn 아레나 통합서버
	//sMsg.ClientIndex = g_pShuttleChild->m_myShuttleInfo.ClientIndex;
	CHARACTER*	pArenaCharacterInfo = g_pD3dApp->GetArenaCharacterInfo();
	sMsg.ClientIndex = pArenaCharacterInfo->ClientIndex;

	sMsg.TeamSize = m_nCount;
	//비밀번호 처리.
	int size = strlen(m_cTeamPW);
	if(size > 0)
	{
		sMsg.TeamLock = TRUE;
		//memcpy(sMsg.TeamPW,m_cTeamPW,size);
		strncpy(sMsg.TeamPW, m_cTeamPW, SIZE_MAX_TEAM_PW);
	}
	else
	{
		sMsg.TeamLock = FALSE;
	}
	g_pFieldWinSocket->SendMsg(T_FC_ARENA_CREATE_TEAM,(char*)&sMsg,sizeof(sMsg));
}
