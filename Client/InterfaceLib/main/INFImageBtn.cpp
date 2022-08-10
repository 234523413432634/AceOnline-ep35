// INFImageBtn.cpp: implementation of the CINFImageBtn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "INFGameMain.h"
#include "Interface.h"


#include "INFImageBtn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFImageBtn::CINFImageBtn()
{
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_BTN_STATUS;nCnt++)
	{
		m_pImageBtn[nCnt] = NULL;
	}	
	m_nBtnStatus = BTN_STATUS_UP;
	m_fPosX = m_fPosY = 0;
	m_fWidth =  m_fHeight = 1;

	m_bShowBtn = TRUE;

	m_bBlingBtn = 0;
	m_fBlingTime = 0;
	m_fCapBlingTime = 0;

	m_bClick = FALSE;
	m_bPush					= FALSE;
}

CINFImageBtn::~CINFImageBtn()
{
	DeleteDeviceObjects();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			HRESULT CINFImageBtn::InitDeviceObjects(char* i_szButtonName)
/// \brief		기존의 버튼의 define을 기본으로 버튼 이름만 입력받아 버튼을 생성한다.
/// \author		dgwoo
/// \date		2007-10-23 ~ 2007-10-23
/// \warning	
// 인터페이스 버튼 상태
//#define BUTTON_STATE_UP			0
//#define BUTTON_STATE_DOWN			1
//#define BUTTON_STATE_DISABLE		2
//#define BUTTON_STATE_NORMAL		3
//
//#define BUTTON_STATE_NUMBER		4
//
///	
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
HRESULT CINFImageBtn::InitDeviceObjects(char* i_szButtonName)
{
	DataHeader*		pDataHeader = NULL;
	char			buf[32];
	DeleteDeviceObjects();
	{		
		wsprintf(buf,"%s3",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BTN_STATUS_UP])
		{
			m_pImageBtn[BTN_STATUS_UP] = new CINFImage;
		}
		m_pImageBtn[BTN_STATUS_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{		
		wsprintf(buf,"%s1",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BTN_STATUS_DOWN])
		{
			m_pImageBtn[BTN_STATUS_DOWN] = new CINFImage;
		}	

		m_pImageBtn[BTN_STATUS_DOWN]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{		
		wsprintf(buf,"%s0",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BTN_STATUS_SEL])
		{
			m_pImageBtn[BTN_STATUS_SEL] = new CINFImage;
		}
		m_pImageBtn[BTN_STATUS_SEL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{		
		wsprintf(buf,"%s2",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BTN_STATUS_DISABLE])
		{
			m_pImageBtn[BTN_STATUS_DISABLE] = new CINFImage;
		}	
		m_pImageBtn[BTN_STATUS_DISABLE]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}
	
	return S_OK;
}
HRESULT CINFImageBtn::InitDeviceObjects(char* pBtup, char* pBtDown, char* pSel, char* pDisable)
{
	DataHeader	* pDataHeader = NULL;
	DeleteDeviceObjects();
	{
		if(NULL == m_pImageBtn[BTN_STATUS_UP])
		{
			m_pImageBtn[BTN_STATUS_UP] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pBtup);
		m_pImageBtn[BTN_STATUS_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_DOWN])
		{
			m_pImageBtn[BTN_STATUS_DOWN] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pBtDown);
		m_pImageBtn[BTN_STATUS_DOWN]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_SEL])
		{
			m_pImageBtn[BTN_STATUS_SEL] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pSel);
		m_pImageBtn[BTN_STATUS_SEL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_DISABLE])
		{
			m_pImageBtn[BTN_STATUS_DISABLE] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pDisable);
		m_pImageBtn[BTN_STATUS_DISABLE]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}
	
	return S_OK;
}

// 오퍼레이터 이미지 로드
HRESULT CINFImageBtn::InitDeviceObjects_LoadOp(char* pBtup, char* pBtDown, char* pSel, char* pDisable)
{
	DataHeader	* pDataHeader = NULL;
	DeleteDeviceObjects();
	{
		if(NULL == m_pImageBtn[BTN_STATUS_UP])
		{
			m_pImageBtn[BTN_STATUS_UP] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource_LoadOp(pBtup);
		m_pImageBtn[BTN_STATUS_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_DOWN])
		{
			m_pImageBtn[BTN_STATUS_DOWN] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource_LoadOp(pBtDown);
		m_pImageBtn[BTN_STATUS_DOWN]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_SEL])
		{
			m_pImageBtn[BTN_STATUS_SEL] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource_LoadOp(pSel);
		m_pImageBtn[BTN_STATUS_SEL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_DISABLE])
		{
			m_pImageBtn[BTN_STATUS_DISABLE] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource_LoadOp(pDisable);
		m_pImageBtn[BTN_STATUS_DISABLE]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}
	
	return S_OK;
}

HRESULT CINFImageBtn::InitDeviceObjects_LoadSelect(char* pBtup, char* pBtDown, char* pSel, char* pDisable)
{
	DataHeader	* pDataHeader = NULL;
	DeleteDeviceObjects();
	{
		if(NULL == m_pImageBtn[BTN_STATUS_UP])
		{
			m_pImageBtn[BTN_STATUS_UP] = new CINFImage;
		}	
		
		pDataHeader = g_pInterface->FindResource_LoadSelect(pBtup);
		m_pImageBtn[BTN_STATUS_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_DOWN])
		{
			m_pImageBtn[BTN_STATUS_DOWN] = new CINFImage;
		}	
		
		pDataHeader = g_pInterface->FindResource_LoadSelect(pBtDown);
		m_pImageBtn[BTN_STATUS_DOWN]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_SEL])
		{
			m_pImageBtn[BTN_STATUS_SEL] = new CINFImage;
		}	
		
		pDataHeader = g_pInterface->FindResource_LoadSelect(pSel);
		m_pImageBtn[BTN_STATUS_SEL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BTN_STATUS_DISABLE])
		{
			m_pImageBtn[BTN_STATUS_DISABLE] = new CINFImage;
		}	
		
		pDataHeader = g_pInterface->FindResource_LoadSelect(pDisable);
		m_pImageBtn[BTN_STATUS_DISABLE]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}
	
	return S_OK;
}


HRESULT CINFImageBtn::RestoreDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_BTN_STATUS;nCnt++)
	{
		if(m_pImageBtn[nCnt])
		{
			m_pImageBtn[nCnt]->RestoreDeviceObjects();
		}
	}
	
	return S_OK;
}

HRESULT CINFImageBtn::DeleteDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_BTN_STATUS;nCnt++)
	{
		if(m_pImageBtn[nCnt])
		{
			m_pImageBtn[nCnt]->DeleteDeviceObjects();	
			SAFE_DELETE(m_pImageBtn[nCnt]);
		}
	}	
	return S_OK;
}
HRESULT CINFImageBtn::InvalidateDeviceObjects()
{	
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_BTN_STATUS;nCnt++)
	{
		m_pImageBtn[nCnt]->InvalidateDeviceObjects();
	}
	
	return S_OK;
}

void CINFImageBtn::Render()
{
	if(FALSE == IsShowWindow())
	{
		return ;
	}	
	if(m_bBlingBtn)
	{
		m_fBlingTime -= g_pD3dApp->GetCheckElapsedTime();
		if(m_fBlingTime < 0)
		{
			m_fBlingTime = m_fCapBlingTime;
			switch(m_nBtnStatus)
			{
			case BTN_STATUS_UP:
				{
					m_nBtnStatus = BTN_STATUS_DOWN;
				}
				break;
			case BTN_STATUS_DOWN:
				{
					m_nBtnStatus = BTN_STATUS_UP;
				}
				break;
			default:
				{
					m_bBlingBtn = FALSE;
				}
				break;
			}
		}
	}
	m_pImageBtn[m_nBtnStatus]->Move(m_fPosX, m_fPosY);
	m_pImageBtn[m_nBtnStatus]->Render();	
}


void CINFImageBtn::SetBtnPosition(float i_fPosX, float i_fPosY)
{
	POINT ptGoCityBtn;
	ptGoCityBtn = GetImgSize();
	m_fPosX		= i_fPosX;
	m_fPosY		= i_fPosY;
	m_fWidth	= ptGoCityBtn.x;
	m_fHeight	= ptGoCityBtn.y;
}

POINT CINFImageBtn::GetImgSize()
{
	return m_pImageBtn[m_nBtnStatus]->GetImgSize();
}

// 버튼 위에 마우스가 있냐?
BOOL CINFImageBtn::IsMouseOverlab(POINT ptPos)
{
	if((m_fPosX <= ptPos.x) &&(ptPos.x <= (m_fPosX+m_fWidth)))		
	{
		if((m_fPosY <= ptPos.y)	&&( ptPos.y <= (m_fPosY + m_fHeight) ))
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CINFImageBtn::OnMouseMove(POINT ptPos)
{
	if(FALSE == IsShowWindow())
	{
		return FALSE;
	}

	if(BTN_STATUS_DISABLE == m_nBtnStatus)
	{
		// Disalbe버튼 
		return FALSE;
	}
	if(IsMouseOverlab(ptPos))
	{			
		// 2007-09-05 by bhsohn 전진 기지전
		if(BTN_STATUS_DOWN != m_nBtnStatus)
		{
			// 마우스 위로 버튼이 있다.
			m_nBtnStatus = BTN_STATUS_SEL;
		}
		// end 2007-09-05 by bhsohn 전진 기지전
		return TRUE;
	}
	// 2008-05-13 by dgwoo Push botton이면 상태를 변경하지 않는다.
	if(m_bPush)
	{
		return FALSE;
	}

	if(FALSE == m_bBlingBtn )
	{
		m_nBtnStatus = BTN_STATUS_UP;
	}
	return FALSE;
}
BOOL CINFImageBtn::OnLButtonDown(POINT ptPos)
{
	if(FALSE == IsShowWindow())
	{
		return FALSE;
	}
	
	if(IsMouseOverlab(ptPos))
	{
		if(BTN_STATUS_DISABLE == m_nBtnStatus)
		{
			// Disalbe버튼 
			return TRUE;
		}
		m_bClick = TRUE;
		
		m_bBlingBtn = FALSE;
		// 마우스 위로 버튼이 있다.
		m_nBtnStatus = BTN_STATUS_DOWN;
		return TRUE;
	}	
	m_bClick = FALSE;
	return FALSE;
}

BOOL CINFImageBtn::OnLButtonUp(POINT ptPos)
{
	if(FALSE == IsShowWindow())
	{
		return FALSE;
	}
	BOOL bTmpClick = m_bClick;
	m_bClick = FALSE;

	if((BTN_STATUS_DOWN != m_nBtnStatus)
		&&(BTN_STATUS_SEL != m_nBtnStatus))
	{				
		return FALSE;
	}
	if(FALSE == m_bBlingBtn )
	{
		m_nBtnStatus = BTN_STATUS_UP;	
	}
	
	if(IsMouseOverlab(ptPos))
	{		
		if(bTmpClick)
		{			
			// 마우스 위로 버튼이 있다.			
			return TRUE;
		}
	}	
	return FALSE;
}

void CINFImageBtn::ShowWindow(BOOL bShow)
{
	m_bShowBtn = bShow;
}
BOOL CINFImageBtn::IsShowWindow()
{
	return m_bShowBtn;
}
// 버튼 깜빡임 설정 가능
void CINFImageBtn::SetBtnBlingBling(BOOL bSet, float fBlingTime)
{
	m_bBlingBtn = bSet;
	m_fCapBlingTime = fBlingTime;
	m_fBlingTime = fBlingTime;
}

void CINFImageBtn::PushButton(BOOL i_bPush)
{
	if(m_nBtnStatus == BTN_STATUS_DISABLE)
	{
		return;
	}
	m_bPush = i_bPush;	
	if(m_bPush)
	{
		m_nBtnStatus = BTN_STATUS_DOWN;
	}
	else
	{
		m_nBtnStatus = BTN_STATUS_UP;
	}

}
void CINFImageBtn::EnableBtn(BOOL bEnable)
{
	if(!bEnable)
	{
		m_nBtnStatus = BTN_STATUS_DISABLE;
	}
	else
	{
		m_nBtnStatus = BTN_STATUS_UP;
	}
}

// 2008-11-13 by bhsohn 조이스틱 작업
void CINFImageBtn::SetBtnState(int i_nBtnStatus)
{
	if(i_nBtnStatus < 0 || i_nBtnStatus >= MAX_BTN_STATUS)
	{
		return;
	}
	else if(NULL == m_pImageBtn[i_nBtnStatus])
	{
		return;
	}
	m_nBtnStatus = i_nBtnStatus;
}