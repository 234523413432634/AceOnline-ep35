// INFOpInfo.cpp: implementation of the CINFOpInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "ShuttleChild.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "INFGameMain.h"
#include "D3DHanFont.h"
#include "AtumSound.h"
#include "QuestData.h"
#include "StoreData.h"
#include "ItemInfo.h"
#include "Interface.h"
#include "INFOpMain.h"
#include "INFOpInfo.h"
#include "AtumDatabase.h"
#include "PetManager.h"
#include "D3DHanFont.h"

#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)
#define STRING_CULL ::StringCullingUserData_ToBlank
#else
#define STRING_CULL ::StringCullingUserDataEx
#endif

#define PLAY_TIME				3.0f
#define PLAY_ADD_TIME			1.0f
#define MAX_PLAY_TIME			6.0f

#define OPWND_POS_X				(g_pD3dApp->GetBackBufferDesc().Width-342)
#define OPWND_POS_Y				(g_pD3dApp->GetBackBufferDesc().Height-187)

#define OPWND_BOTTOM_POS_Y		(g_pD3dApp->GetBackBufferDesc().Height)
#define OPWND_BOTTOM_POS_X		(g_pD3dApp->GetBackBufferDesc().Width)
#define OPWND_POS_Y_GAP			20
#define OPWND_POS_Y_FONT_GAP	 5
#define OPWND_POS_X_GAP			10

CINFOpInfo::CINFOpInfo(CINFOpMain* pParent)
{	
	m_pFontOpInfo = NULL;
}

CINFOpInfo::~CINFOpInfo()
{
	DeleteDeviceObjects();
}

HRESULT CINFOpInfo::InitDeviceObjects()
{
	DataHeader	* pDataHeader = NULL;
	char szImage[16];
	memset(szImage, 0x00, 16);	
	wsprintf(szImage,"PN_op");
	
	CINFImage*	BackImage;
	BackImage = new CINFImage;
	pDataHeader = g_pGameMain->FindResource(szImage);	
	BackImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	for(int i = 0; i< MAX_IMAGE; i++)
	{
		CINFImage* tempImage = new CINFImage;
		OP_INFO* temp = new OP_INFO;
		temp->sBackImage = BackImage;
		
		memset(szImage, 0x00, 16);	
		wsprintf(szImage,"PN_gener0%d",i + 1);

		tempImage = new CINFImage;
		pDataHeader = g_pGameMain->FindResource(szImage);
		tempImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
		temp->sImage = tempImage;		
		temp->spOperatorInfo = g_pDatabase->GetPtr_OperatorAction( i + 1 );
		temp->PlayCurrentTime = PLAY_TIME;
		temp->live = FALSE;
		temp->x = OPWND_BOTTOM_POS_X;
		temp->y = OPWND_POS_Y;

		m_vecOpInfo.push_back( temp );
	}

	m_pFontOpInfo = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 9, D3DFONT_ZENABLE, TRUE, 512, 32);
	m_pFontOpInfo->InitDeviceObjects(g_pD3dDev);
	return S_OK;
}
HRESULT CINFOpInfo::RestoreDeviceObjects()
{
	for(int i=0; i< m_vecOpInfo.size(); i++)
	{
		m_vecOpInfo[ i ]->sImage->RestoreDeviceObjects();
		m_vecOpInfo[ i ]->sBackImage->RestoreDeviceObjects();
	}
	m_pFontOpInfo->RestoreDeviceObjects();
	return S_OK;
}
HRESULT CINFOpInfo::InvalidateDeviceObjects()
{
	for(int i=0; i< m_vecOpInfo.size(); i++)
	{
		m_vecOpInfo[ i ]->sImage->InvalidateDeviceObjects();
		m_vecOpInfo[ i ]->sBackImage->InvalidateDeviceObjects();
	}
	m_pFontOpInfo->InvalidateDeviceObjects();
	return S_OK;
}

void CINFOpInfo::SetOperatorAction(int Type, int FunctionIndex)
{
	// 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
	if( !g_pSOption->sPetOPBalance )
	{
		return;
	}
	// end 2010. 10. 26 by jskim 펫 오퍼레이터 옵션 처리
	CItemInfo* pItem;
	tPET_CURRENTINFO * tempCurrentInfo; 
	if( Type == OP_PET )
	{
		pItem = g_pStoreData->FindItemInInventoryByWindowPos( POS_PET ); 
		if( pItem == NULL )
		{
			return;
		}

		tempCurrentInfo = g_pShuttleChild->GetPetManager()->GetPtr_PetCurrentData( pItem->UniqueNumber );
		if( tempCurrentInfo == NULL )
		{	
			return;
		}
	}

	int tempSourceIndex = NULL;
	if( tempCurrentInfo )
	{
		tempSourceIndex = tempCurrentInfo->SourceIndex_Field;
	}
	
	vector<OP_INFO*>::iterator it = m_vecOpInfo.begin();
	if(!CheckView(Type,FunctionIndex, tempSourceIndex))
	{
		while(it != m_vecOpInfo.end())
		{
			if( (*it)->spOperatorInfo->ActionType == Type &&
				(*it)->spOperatorInfo->FunctionIndex == FunctionIndex &&
				(*it)->spOperatorInfo->SourceIndex == tempSourceIndex )
			{
				(*it)->live = true;
				m_vecCurrentOpInfo.push_back((*it));
				break;
			}
			it++;
		}
	}
}

// 오퍼레이터 정보를 찾아오는 함수
OP_INFO* CINFOpInfo::GetOperatorAction( int i_Type, int i_FunctionIndex )
{
	vector<OP_INFO*>::iterator Get_it = m_vecOpInfo.begin();
	for (; Get_it != m_vecOpInfo.end(); Get_it++)
	{
		if ((*Get_it)->spOperatorInfo->ActionType == i_Type &&
			(*Get_it)->spOperatorInfo->FunctionIndex == i_FunctionIndex)
		{
			return (*Get_it);
		}
	}
	return FALSE;
}

BOOL CINFOpInfo::CheckView( int Type, int FunctionIndex, int SourceIndex /* = 0 */ )
{
	vector<OP_INFO*>::iterator it = m_vecCurrentOpInfo.begin();

	while(it != m_vecCurrentOpInfo.end())
	{
		if((*it)->spOperatorInfo->ActionType == Type &&
		   (*it)->spOperatorInfo->FunctionIndex == FunctionIndex && 
		   (*it)->spOperatorInfo->SourceIndex == SourceIndex )  
		{
			if((*it)->PlayCurrentTime < MAX_PLAY_TIME)
			{
			(*it)->PlayCurrentTime += PLAY_ADD_TIME;
			}			
			return TRUE;
		}
		it++;
	}
	return FALSE;
}

HRESULT CINFOpInfo::DeleteDeviceObjects()
{
	if(m_vecOpInfo[ 0 ]->sBackImage && m_vecOpInfo.size() > 0)
	{
		m_vecOpInfo[ 0 ]->sBackImage->DeleteDeviceObjects();
		SAFE_DELETE(m_vecOpInfo[ 0 ]->sBackImage);
	}

	for(int i=0; i< m_vecOpInfo.size(); i++)
	{
		if(m_vecOpInfo[ i ]->sImage && m_vecOpInfo.size() > 0)
		{
			m_vecOpInfo[ i ]->sImage->DeleteDeviceObjects();
			SAFE_DELETE(m_vecOpInfo[ i ]->sImage);
		}
	}
	
	if(m_pFontOpInfo)
	{
		m_pFontOpInfo->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontOpInfo);
	}
	return S_OK;
}

void CINFOpInfo::Render()
{
	vector<OP_INFO*>::iterator it = m_vecCurrentOpInfo.begin();

	while(it != m_vecCurrentOpInfo.end())
	{
		if((*it)->live == TRUE)
		{
			(*it)->sBackImage->Move((*it)->x, (*it)->y);
			(*it)->sBackImage->Render();

			(*it)->sImage->Move((*it)->x, (*it)->y);
			(*it)->sImage->Render();

			vector<string> vecMessage;
			STRING_CULL((*it)->spOperatorInfo->ActionDesc , (*it)->sBackImage->GetImgSize().x / 2 - (OPWND_POS_X_GAP*2) , &vecMessage, m_pFontOpInfo );
			
 			char	szBuff[1024];
			SIZE	size;
 			for(int i= 0; i <  vecMessage.size(); i++)
 			{
				string str = vecMessage[i];
				strcpy( szBuff, str.c_str() );
				size = m_pFontOpInfo->GetStringSize( szBuff );
				m_pFontOpInfo->DrawText( (*it)->x + (*it)->sBackImage->GetImgSize().x / 2 + OPWND_POS_X_GAP ,
					                     (*it)->y + (((*it)->sBackImage->GetImgSize().y - size.cy) / 2) - 
										 (size.cy * vecMessage.size() + OPWND_POS_Y_FONT_GAP) / 2 + 
										 (size.cy + OPWND_POS_Y_FONT_GAP) * i,
 										   NAME_COLOR_NORMAL,
 										   szBuff );
			}
		}
		it++;
	}
}

void CINFOpInfo::Tick()
{

	for(int i=0; i < m_vecCurrentOpInfo.size(); i++)
	{
		if(m_vecCurrentOpInfo[i]->live == TRUE)
		{
			if(m_vecCurrentOpInfo[i]->PlayCurrentTime >= 0.0f)
			{
				
				m_vecCurrentOpInfo[i]->PlayCurrentTime -= g_pD3dApp->GetCheckElapsedTime();
				if(m_vecCurrentOpInfo[i]->x > OPWND_POS_X)
				{
					m_vecCurrentOpInfo[i]->x -= OPWND_POS_Y_GAP;
				}
			}
			else
			{
				m_vecCurrentOpInfo[i]->live = FALSE;
				m_vecCurrentOpInfo[i]->x = OPWND_BOTTOM_POS_X;
				m_vecCurrentOpInfo[i]->PlayCurrentTime = PLAY_TIME;
				m_vecCurrentOpInfo.erase(m_vecCurrentOpInfo.begin()+i);
			}
		}
	}
}

int	CINFOpInfo::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_KEYDOWN:
		{
			return OnKeyDown(wParam, lParam);
		}
		break;
	}
	return INF_MSGPROC_NORMAL;	
}
int CINFOpInfo::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case VK_ESCAPE:
		{
			return INF_MSGPROC_BREAK;
		}
		break;
	}
	return INF_MSGPROC_NORMAL;		
}

