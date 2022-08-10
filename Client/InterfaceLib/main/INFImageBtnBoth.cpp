// INFImageBtnBoth.cpp: implementation of the CINFImageBtnBoth class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "INFGameMain.h"
#include "Interface.h"
#include "INFImageBtnBoth.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFImageBtnBoth::CINFImageBtnBoth()
{

}

CINFImageBtnBoth::~CINFImageBtnBoth()
{
	DeleteDeviceObjects();
}
void CINFImageBtnBoth::Init()
{
	m_nBtnBoth = BUTTON_BOTH_FRONT;						// �� �޸�.
	m_nBtnStatus = BUTTON_BOTH_STATE_NORMAL;					// ����.
	m_fPosX = 0;
	m_fPosY = 0;

	m_fWidth = 0;
	m_fHeight = 0;
	m_bShowBtn = TRUE;
	

	m_bOption = 0;


}

HRESULT CINFImageBtnBoth::InitDeviceObjects(char* i_szButtonName)
{
	DataHeader*		pDataHeader = NULL;
	char			buf[32];
	DeleteDeviceObjects();
	{		
		wsprintf(buf,"%s00",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_NORMAL])
		{
			m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_NORMAL] = new CINFImage;
		}
		m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_NORMAL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{		
		wsprintf(buf,"%s01",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_UP])
		{
			m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_UP] = new CINFImage;
		}
		m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{		
		wsprintf(buf,"%s11",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_UP])
		{
			m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_UP] = new CINFImage;
		}
		m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{		
		wsprintf(buf,"%s10",i_szButtonName);
		pDataHeader = g_pGameMain->FindResource(buf);
		if(NULL == pDataHeader)
		{
			DeleteDeviceObjects();
			return S_FALSE;
		}
		if(NULL == m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_NORMAL])
		{
			m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_NORMAL] = new CINFImage;
		}
		m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_NORMAL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}
	Init();
	return S_OK;
}
HRESULT CINFImageBtnBoth::InitDeviceObjects(char* pFrontNormal, char* pFrontUp, char* pBackNormal, char* pBackUp)
{
	DataHeader	* pDataHeader = NULL;
	DeleteDeviceObjects();
	{
		if(NULL == m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_NORMAL])
		{
			m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_NORMAL] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pFrontNormal);
		m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_NORMAL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_UP])
		{
			m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_UP] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pFrontUp);
		m_pImageBtn[BUTTON_BOTH_FRONT][BUTTON_BOTH_STATE_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_NORMAL])
		{
			m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_NORMAL] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pBackNormal);
		m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_NORMAL]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	{
		if(NULL == m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_UP])
		{
			m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_UP] = new CINFImage;
		}	
		
		pDataHeader = g_pGameMain->FindResource(pBackUp);
		m_pImageBtn[BUTTON_BOTH_BACK][BUTTON_BOTH_STATE_UP]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}
	Init();
	return S_OK;
}






HRESULT CINFImageBtnBoth::RestoreDeviceObjects()
{
	int nBoth = 0;
	int nState;
	for(nBoth = 0;nBoth < BUTTON_BOTH_STATE_NUMBER;nBoth++)
	{
		for(nState = 0 ; nState < BUTTON_BOTH_STATE_NUMBER ; nState++)
		{
			if(m_pImageBtn[nBoth][nState])
			{
				m_pImageBtn[nBoth][nState]->RestoreDeviceObjects();
			}
		}
	}
	
	return S_OK;
}

HRESULT CINFImageBtnBoth::DeleteDeviceObjects()
{
	int nBoth = 0;
	int nState;
	for(nBoth = 0;nBoth < BUTTON_BOTH_STATE_NUMBER;nBoth++)
	{
		for(nState = 0 ; nState < BUTTON_BOTH_STATE_NUMBER ; nState++)
		{
			if(m_pImageBtn[nBoth][nState])
			{
				m_pImageBtn[nBoth][nState]->DeleteDeviceObjects();
			}
		}
	}
	return S_OK;
}
HRESULT CINFImageBtnBoth::InvalidateDeviceObjects()
{	
	int nBoth = 0;
	int nState;
	for(nBoth = 0;nBoth < BUTTON_BOTH_STATE_NUMBER;nBoth++)
	{
		for(nState = 0 ; nState < BUTTON_BOTH_STATE_NUMBER ; nState++)
		{
			if(m_pImageBtn[nBoth][nState])
			{
				m_pImageBtn[nBoth][nState]->InvalidateDeviceObjects();
			}
		}
	}
	return S_OK;
}

void CINFImageBtnBoth::Render()
{
	if(FALSE == IsShowWindow())
	{
		return ;
	}	
	
	m_pImageBtn[m_nBtnBoth][m_nBtnStatus]->Move(m_fPosX, m_fPosY);
	m_pImageBtn[m_nBtnBoth][m_nBtnStatus]->Render();	
}


void CINFImageBtnBoth::SetBtnPosition(float i_fPosX, float i_fPosY)
{
	POINT ptGoCityBtn;
	ptGoCityBtn = GetImgSize();
	m_fPosX		= i_fPosX;
	m_fPosY		= i_fPosY;
	m_fWidth	= ptGoCityBtn.x;
	m_fHeight	= ptGoCityBtn.y;
}

POINT CINFImageBtnBoth::GetImgSize()
{
	return m_pImageBtn[m_nBtnBoth][m_nBtnStatus]->GetImgSize();
}

// ��ư ���� ���콺�� �ֳ�?
BOOL CINFImageBtnBoth::IsMouseOverlab(POINT ptPos)
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

BOOL CINFImageBtnBoth::OnMouseMove(POINT ptPos)
{
	if(FALSE == IsShowWindow())
	{
		return FALSE;
	}

	if(IsMouseOverlab(ptPos))
	{			
			// ���콺 ���� ��ư�� �ִ�.
		m_nBtnStatus = BUTTON_BOTH_STATE_UP;
		return TRUE;
	}
	m_nBtnStatus = BUTTON_BOTH_STATE_NORMAL;
	
	return FALSE;
}
BOOL CINFImageBtnBoth::OnLButtonDown(POINT ptPos)
{
	if(FALSE == IsShowWindow())
	{
		return FALSE;
	}
	
	if(IsMouseOverlab(ptPos))
	{
		
		
		// ���콺 ���� ��ư�� �ִ�.
		m_nBtnStatus = BUTTON_BOTH_STATE_UP;
		return TRUE;
	}	
	
	return FALSE;
}

BOOL CINFImageBtnBoth::OnLButtonUp(POINT ptPos)
{
	if(FALSE == IsShowWindow())
	{
		return FALSE;
	}
	

	
	if(IsMouseOverlab(ptPos))
	{
		if(BOTH_BTN_OPTION(m_bOption,BOTH_BTN_OPTION_AUTO_BOTH_CHANGE))
		{
			// ���콺 ���� ��ư�� �ִ�.	
			ChangeBoth();
		}
		return TRUE;
	}	
	return FALSE;
}

void CINFImageBtnBoth::ShowWindow(BOOL bShow)
{
	m_bShowBtn = bShow;
}
BOOL CINFImageBtnBoth::IsShowWindow()
{
	return m_bShowBtn;
}
BOOL CINFImageBtnBoth::ChangeBoth(int i_nBoth/* = -1*/)
{
	if(i_nBoth != -1)
	{
		m_nBtnBoth = i_nBoth;
		return TRUE;
	}
	if(m_nBtnBoth == BUTTON_BOTH_BACK)
	{
		m_nBtnBoth = BUTTON_BOTH_FRONT;
		return TRUE;
	}
	else if(m_nBtnBoth == BUTTON_BOTH_FRONT)
	{
		m_nBtnBoth = BUTTON_BOTH_BACK;
		return TRUE;
	}
	return FALSE;
}
int CINFImageBtnBoth::GetBoth()
{
	return m_nBtnBoth;
}
BYTE CINFImageBtnBoth::SetOption(BYTE i_bOption)
{
	BYTE bTempOpt = m_bOption;
	m_bOption = i_bOption;
	return bTempOpt;
}