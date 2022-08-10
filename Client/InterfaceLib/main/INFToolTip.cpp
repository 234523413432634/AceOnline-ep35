// INFToolTip.cpp: implementation of the CINFToolTip class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFToolTip.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "dxutil.h"

#define	TOOLTIP_SHOW_TIME			3.0f
#define TOOLTIP_RENDER_Y			150.f

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFToolTip::CINFToolTip()
{
	m_pImgTemp					= NULL;
	m_fLifeTime					= 0;
	m_IsShow					= TRUE;
}

CINFToolTip::~CINFToolTip()
{

}

void CINFToolTip::SetImgType(UINT i_nType)
{
	map<UINT, CINFImage*>::iterator it = m_mapToolTip.find(i_nType);
	m_pImgTemp = it->second;
	m_fLifeTime = TOOLTIP_SHOW_TIME;
}
void CINFToolTip::Render()
{
	if(m_fLifeTime > 0 
		&& m_IsShow)
	{
		float fUnLifeTime =  TOOLTIP_SHOW_TIME - m_fLifeTime;
		DWORD dwAlpha = GetCurrentColor(fUnLifeTime, ALPHA_DELAY_WAVE, TOOLTIP_SHOW_TIME,2.0f);
		
		POINT pt = m_pImgTemp->GetImgSize();
		DWORD nX = (int)(g_pD3dApp->GetBackBufferDesc().Width - pt.x)/2;
		DWORD nY = TOOLTIP_RENDER_Y;
		m_pImgTemp->SetColor(dwAlpha);
		m_pImgTemp->Move(nX,nY);
		m_pImgTemp->Render();
	}
}
void CINFToolTip::Tick()
{
	if(m_fLifeTime <= 0)
	{
		m_fLifeTime = 0;
	}
	else
	{
		m_fLifeTime -= g_pD3dApp->GetElapsedTime();
	}
}

HRESULT CINFToolTip::InitDeviceObjects()
{
	DataHeader	* pDataHeader;
	//char buf[16];

	CINFImage * pImage;

	pImage = new CINFImage;
	pDataHeader = FindResource("ustelsuc");
	pImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	m_mapToolTip[TOOLTIP_IMGTYPE_TELEPORT_SUC] = pImage;

	pImage = new CINFImage;
	pDataHeader = FindResource("usteldes");
	pImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	m_mapToolTip[TOOLTIP_IMGTYPE_TELEPORT_DESTROY] = pImage;

	return S_OK;
}
HRESULT CINFToolTip::RestoreDeviceObjects()
{
	map<UINT, CINFImage*>::iterator it = m_mapToolTip.begin();
	while(it != m_mapToolTip.end())
	{
		CINFImage* pImage = it->second;
		pImage->RestoreDeviceObjects();
		it++;
	}
	return S_OK;
}
HRESULT CINFToolTip::DeleteDeviceObjects()
{
	map<UINT, CINFImage*>::iterator it = m_mapToolTip.begin();
	while(it != m_mapToolTip.end())
	{
		CINFImage* pImage = it->second;
		pImage->DeleteDeviceObjects();
		SAFE_DELETE(pImage);
		it++;
	}
	m_mapToolTip.clear();
	return S_OK;
}
HRESULT CINFToolTip::InvalidateDeviceObjects()
{
	map<UINT, CINFImage*>::iterator it = m_mapToolTip.begin();
	while(it != m_mapToolTip.end())
	{
		CINFImage* pImage = it->second;
		pImage->InvalidateDeviceObjects();
		it++;
	}
	return S_OK;
}
