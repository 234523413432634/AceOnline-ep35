// INFImageRadioBtn.cpp: implementation of the CINFImageRadioBtn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "INFGameMain.h"
#include "Interface.h"

#include "INFImageRadioBtn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFImageRadioBtn::CINFImageRadioBtn()
{
	int nCnt = 0;
	for(nCnt = 0;nCnt <MAX_RADIO_STATUS;nCnt++)
	{
		m_pImageRadio[nCnt] = NULL;
	}			
	
	m_fPosX = m_fPosY = 0;
	m_fWidth = m_fHeight = 1;

	m_nRadioStatus = RADIO_STATUS_OFF;
}

CINFImageRadioBtn::~CINFImageRadioBtn()
{
	DeleteDeviceObjects();
}

HRESULT CINFImageRadioBtn::InitDeviceObjects(char* pRadioup, char* pRadioSel)
{
	DataHeader	* pDataHeader = NULL;
	
	// Off
	{
		m_pImageRadio[RADIO_STATUS_OFF] = new CINFImage;
		pDataHeader = g_pGameMain->FindResource(pRadioup);
		m_pImageRadio[RADIO_STATUS_OFF]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	// On
	{
		m_pImageRadio[RADIO_STATUS_ON] = new CINFImage;
		pDataHeader = g_pGameMain->FindResource(pRadioSel);
		m_pImageRadio[RADIO_STATUS_ON]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}	

	return S_OK;
}
HRESULT CINFImageRadioBtn::InitDeviceObjects_LoadSelect(char* pRadioup, char* pRadioSel)
{
	DataHeader	* pDataHeader = NULL;
	
	// Off
	{
		m_pImageRadio[RADIO_STATUS_OFF] = new CINFImage;
		pDataHeader = g_pInterface->FindResource_LoadSelect(pRadioup);
		m_pImageRadio[RADIO_STATUS_OFF]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}

	// On
	{
		m_pImageRadio[RADIO_STATUS_ON] = new CINFImage;
		pDataHeader = g_pInterface->FindResource_LoadSelect(pRadioSel);
		m_pImageRadio[RADIO_STATUS_ON]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);		
	}	

	return S_OK;
}

HRESULT CINFImageRadioBtn::RestoreDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0;nCnt <MAX_RADIO_STATUS;nCnt++)
	{
		m_pImageRadio[nCnt]->RestoreDeviceObjects();
	}			
	return S_OK;
}

HRESULT CINFImageRadioBtn::DeleteDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0;nCnt <MAX_RADIO_STATUS;nCnt++)
	{
		if(m_pImageRadio[nCnt])
		{
			m_pImageRadio[nCnt]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImageRadio[nCnt]);
		}
	}			
	
	return S_OK;
}

HRESULT CINFImageRadioBtn::InvalidateDeviceObjects()
{
	int nCnt = 0;
	for(nCnt = 0;nCnt <MAX_RADIO_STATUS;nCnt++)
	{
		m_pImageRadio[nCnt]->InvalidateDeviceObjects();
	}			
	return S_OK;
}

void CINFImageRadioBtn::Render()
{
	// ��ư 
	m_pImageRadio[m_nRadioStatus]->Move(m_fPosX, m_fPosY);
	m_pImageRadio[m_nRadioStatus]->Render();		
}

void CINFImageRadioBtn::SetPosition(float i_fPosX, float i_fPosY, float i_fStrWidth)
{
	POINT ptRadio;
	ptRadio = m_pImageRadio[RADIO_STATUS_OFF]->GetImgSize();	
	m_fPosX		= i_fPosX;
	m_fPosY		= i_fPosY;		
	
	m_fHeight	= ptRadio.y;
	m_fWidth	= i_fStrWidth;		// ��ư�� �۾����� ���� 	
}

void CINFImageRadioBtn::SetRadioBtn(BOOL i_bSelRadio)
{
	if(i_bSelRadio)
	{
		m_nRadioStatus = RADIO_STATUS_ON;
	}
	else
	{
		m_nRadioStatus = RADIO_STATUS_OFF;
	}
}
int CINFImageRadioBtn::GetRadioBtn()		// ���� ��ư ���� 
{
	return m_nRadioStatus;
}

BOOL CINFImageRadioBtn::OnLButtonDown(POINT pt)
{
	if((m_fPosX <= pt.x)
		&&(pt.x <= (m_fPosX+m_fWidth)))
	{		
		if((m_fPosY <= pt.y)
			&&(pt.y <= (m_fPosY+m_fHeight)))
		{
			return TRUE;
		}
	}
	return FALSE;
}