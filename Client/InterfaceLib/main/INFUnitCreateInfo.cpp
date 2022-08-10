// INFUnitCreateInfo.cpp: implementation of the CUnitCreateInfo class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "RangeTime.h"
#include "INFImage.h"
#include "INFUnitCreateInfo.h"
#include "AtumApplication.h"
#include "GameDataLast.h"
#include "dxutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define IMAGE_SCALE					((float)g_pD3dApp->GetBackBufferDesc().Width/800.0f)
#define UNIT_CREATE_INFO_SIZE_X		(474*IMAGE_SCALE)
#define UNIT_CREATE_INFO_Y			(100*IMAGE_SCALE)

#define UNIT_CREATE_INFO_START_X	((g_pD3dApp->GetBackBufferDesc().Width/2)-200)
#define UNIT_CREATE_INFO_START_Y	(UNIT_CREATE_INFO_Y)

#define VIEWING_TIME				(D3DX_PI/2.0f+0.5f)

CINFUnitCreateInfo::CINFUnitCreateInfo(CAtumNode* pParent)
{
	m_pParent = pParent;
	m_bRestored = FALSE;
	m_fIncreaseViewingTime = VIEWING_TIME;
}

CINFUnitCreateInfo::~CINFUnitCreateInfo()
{

}


HRESULT CINFUnitCreateInfo::InitDeviceObjects()
{
	//time Setting
	//m_tRemainTime.Set();	
	//
	m_pBGear = new CINFImage;
	DataHeader * pDataHeader = FindResource("B");
	m_pBGear->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pIGear = new CINFImage;
	pDataHeader = FindResource("I");
	m_pIGear->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pMGear = new CINFImage;
	pDataHeader = FindResource("M");
	m_pMGear->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pAGear = new CINFImage;
	pDataHeader = FindResource("A");
	m_pAGear->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	return S_OK;
}

HRESULT CINFUnitCreateInfo::RestoreDeviceObjects()
{
	if(!m_bRestored)
	{
		m_pBGear->RestoreDeviceObjects();
		m_pBGear->Move(UNIT_CREATE_INFO_START_X, UNIT_CREATE_INFO_START_Y);
//		m_pBGear->SetScale(IMAGE_SCALE,IMAGE_SCALE);
		
		m_pIGear->RestoreDeviceObjects();
		m_pIGear->Move(UNIT_CREATE_INFO_START_X, UNIT_CREATE_INFO_START_Y);
//		m_pIGear->SetScale(IMAGE_SCALE,IMAGE_SCALE);
		
		m_pMGear->RestoreDeviceObjects();
		m_pMGear->Move(UNIT_CREATE_INFO_START_X, UNIT_CREATE_INFO_START_Y);
//		m_pMGear->SetScale(IMAGE_SCALE,IMAGE_SCALE);
		
		m_pAGear->RestoreDeviceObjects();
		m_pAGear->Move(UNIT_CREATE_INFO_START_X, UNIT_CREATE_INFO_START_Y);
//		m_pAGear->SetScale(IMAGE_SCALE,IMAGE_SCALE);

		m_bRestored = TRUE;

	}
	return S_OK;
}

HRESULT CINFUnitCreateInfo::DeleteDeviceObjects()
{
	m_pBGear->DeleteDeviceObjects();
	SAFE_DELETE(m_pBGear);
	m_pIGear->DeleteDeviceObjects();
	SAFE_DELETE(m_pIGear);
	m_pMGear->DeleteDeviceObjects();
	SAFE_DELETE(m_pMGear);
	m_pAGear->DeleteDeviceObjects();
	SAFE_DELETE(m_pAGear);

	return S_OK;
}

HRESULT CINFUnitCreateInfo::InvalidateDeviceObjects()
{
	if(m_bRestored)
	{
		m_pBGear->InvalidateDeviceObjects();
		m_pIGear->InvalidateDeviceObjects();
		m_pMGear->InvalidateDeviceObjects();
		m_pAGear->InvalidateDeviceObjects();

		m_bRestored = FALSE;
	}
	return S_OK;
}

void CINFUnitCreateInfo::StartView( )
{
	m_tRemainTime.Set( VIEWING_TIME );
}

void CINFUnitCreateInfo::Tick( float fElapedTime )
{
	m_tRemainTime.Tick( fElapedTime );
}

void CINFUnitCreateInfo::Render( int nUnitKind )
{
	int uUnitKind = UNITKIND_BT01 << (4*nUnitKind) ;
	BOOL bRemainTime = m_tRemainTime.IsRemain();
	DWORD dwColor = 0x00FFFFFF;
	
	if( bRemainTime )
	{
		DWORD alpha = 0;
		alpha = 255* (1.0f - m_tRemainTime.GetRemainRate() );
		alpha = alpha << 24;
		dwColor = dwColor | alpha;
	}
	else
	{
		dwColor = 0xFFFFFFFF;
	}

	switch(uUnitKind)
	{
	case UNITKIND_BT01:
		{
			m_pBGear->SetColor( dwColor);
			m_pBGear->Render();
		}
		break;
	case UNITKIND_OT01:
		{
			m_pMGear->SetColor( dwColor);
			m_pMGear->Render();
		}
		break;
	case UNITKIND_DT01:
		{
			m_pAGear->SetColor( dwColor);
			m_pAGear->Render();
		}
		break;
	case UNITKIND_ST01:
		{
			m_pIGear->SetColor( dwColor);
			m_pIGear->Render();
		}
		break;
		
	default:
		break;
	}

}


