// INFMapName.cpp: implementation of the CINFMapName class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFMapName.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "dxutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFMapName::CINFMapName()
{
	FLOG( "CINFMapName()" );
	
	m_pGameData = NULL;
	m_bRestored = FALSE;
}

CINFMapName::~CINFMapName()
{
	FLOG( "~CINFMapName()" );
	
	map<int, CINFImage*>::iterator it = m_mapMapName.begin();
	while(it != m_mapMapName.end())
	{
		CINFImage* pImage = it->second;
		SAFE_DELETE(pImage);
		it++;
	}
	m_mapMapName.clear();
	SAFE_DELETE(m_pGameData);
}

HRESULT CINFMapName::InitDeviceObjects(char* strTexture)
{
	FLOG( "CINFMapName::InitDeviceObjects(char* pData, int nSize)" );

	char strPath[256];
	g_pD3dApp->LoadPath( strPath, IDS_DIRECTORY_TEXTURE, strTexture);
	SetResourceFile(strPath);
	
	return S_OK;
}

HRESULT CINFMapName::RestoreDeviceObjects()
{
	FLOG( "CINFMapName::RestoreDeviceObjects()" );

	if(!m_bRestored)
	{
		map<int, CINFImage*>::iterator it = m_mapMapName.begin();
		while(it != m_mapMapName.end())
		{
			CINFImage* pImage = it->second;
			pImage->RestoreDeviceObjects();
			it++;
		}
		m_bRestored = TRUE;
	}

	return S_OK;
}

HRESULT CINFMapName::InvalidateDeviceObjects()
{
	FLOG( "CINFMapName::InvalidateDeviceObjects()" );

	if(m_bRestored)
	{
		map<int, CINFImage*>::iterator it = m_mapMapName.begin();
		while(it != m_mapMapName.end())
		{
			CINFImage* pImage = it->second;
			pImage->InvalidateDeviceObjects();
			it++;
		}
		m_bRestored = FALSE;
	}

	return S_OK;
}

HRESULT CINFMapName::DeleteDeviceObjects()
{
	FLOG( "CINFMapName::DeleteDeviceObjects()" );

	map<int, CINFImage*>::iterator it = m_mapMapName.begin();
	while(it != m_mapMapName.end())
	{
		CINFImage* pImage = it->second;
		pImage->DeleteDeviceObjects();
		SAFE_DELETE(pImage);
		it++;
	}
	m_mapMapName.clear();

	SAFE_DELETE(m_pGameData);
	
	return S_OK;
}

HRESULT CINFMapName::SetResourceFile(char* szFileName)
{
	FLOG( "CINFMapName::SetResourceFile(char* szFileName)" );
	SAFE_DELETE(m_pGameData);
	m_pGameData = new CGameData;
	m_pGameData->SetFile(szFileName, FALSE, NULL, 0);

	return S_OK;
}

CINFImage* CINFMapName::FindMapNameImage(int nType)
{
	FLOG( "CINFMapName::FindMapNameImage(int nType)" );
	map<int, CINFImage*>::iterator it = m_mapMapName.find(nType);
	if(it != m_mapMapName.end())
	{
		return it->second;
	}

	if(!m_pGameData)
		return NULL;
	char buf[20];
	wsprintf(buf, "%04d",nType);
	DataHeader* pHeader;
	pHeader = m_pGameData->Find(buf);
	if(pHeader)
	{
		CINFImage* pFace = new CINFImage();
		pFace->InitDeviceObjects(pHeader->m_pData,pHeader->m_DataSize);
		pFace->RestoreDeviceObjects();
		m_mapMapName[nType] = pFace;
		return pFace;
	}
	return NULL;
}

void CINFMapName::Render()
{
	FLOG( "CINFMapName::Render()" );	
}

void CINFMapName::Tick()
{
	FLOG( "CINFMapName::Tick()" );
}