// INFWeaponInfo.cpp: implementation of the CINFWeaponInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFWeaponInfo.h"
#include "INFGameMain.h"
#include "AtumApplication.h"
#include "StoreData.h"
#include "INFWindow.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "ItemInfo.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "WeaponItemInfo.h"
#include "dxutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define LEFT_WEAPON_NUMBER g_pShuttleChild->m_pPrimaryWeapon->GetItemGeneral()->CurrentCount// ������ ��� ���� �����(USE FUEL)
#define RIGHT_WEAPON_NUMBER g_pShuttleChild->m_pSecondaryWeapon->GetItemGeneral()->CurrentCount


#define FIRST_WEAPON_START_X	23
#define FIRST_WEAPON_START_Y	178
#define FIRST_WEAPON_GAGE_X		(FIRST_WEAPON_START_X + 37)
#define FIRST_WEAPON_GAGE_Y		(FIRST_WEAPON_START_Y + 3)
#define FIRST_WEAPON_FONT_X		(FIRST_WEAPON_START_X + 55)
#define FIRST_WEAPON_FONT_Y		(FIRST_WEAPON_START_Y + 10)

#define SECOND_WEAPON_START_X	23
#define SECOND_WEAPON_START_Y	207
#define SECOND_WEAPON_GAGE_X	(SECOND_WEAPON_START_X + 37)
#define SECOND_WEAPON_GAGE_Y	(SECOND_WEAPON_START_Y + 3)
#define SECOND_WEAPON_FONT_X	(SECOND_WEAPON_START_X + 55)
#define SECOND_WEAPON_FONT_Y	(SECOND_WEAPON_START_Y + 10)


#define LEFT_WEAPON_NUMBER_X	5
#define LEFT_WEAPON_NUMBER_Y	57
#define WEAPON_NUMBER_SIZE		10
// 2007-10-15 by bhsohn �Ѿ� ������ �߰� ó��
//#define RIGHT_WEAPON_NUMBER_X	(g_pD3dApp->GetBackBufferDesc().Width - 45) // 45 = WEAPON_NUMBER_SIZE*4(4�ڸ�����) + LEFT_WEAPON_NUMBER_X
#define RIGHT_WEAPON_NUMBER_X	(g_pD3dApp->GetBackBufferDesc().Width - 52) // 50 = WEAPON_NUMBER_SIZE*5(5�ڸ�����) + LEFT_WEAPON_NUMBER_X

#define LEFT_FUEL_X				1
#define LEFT_FUEL_Y				59

CINFWeaponInfo::CINFWeaponInfo(CAtumNode* pParent)
{
	FLOG( "CINFWeaponInfo(CAtumNode* pParent)" );
	m_pStImage = NULL ;
	m_pStWeaponImage = NULL;
	m_pNdImage = NULL ;
	m_pNdWeaponImage = NULL;
	m_pStOverHeatBar = NULL;
	m_pNdOverHeatBar = NULL;
	m_pEmptyWeaponImage = NULL;
	m_pStFuelGageBar = NULL;
	m_pStFuelUnderGageBar = NULL;
//	m_pNdFuelGageBar = NULL;
//	m_pNdFuelUnderGageBar = NULL;
	m_pReloadImage = NULL;
	m_pOverHeatImage = NULL;
	m_pBulletEmptyImage = NULL;
	m_pBulletLowImage = NULL;


	m_nLeftWeaponInfoPosX = 0 ;
	m_nRightWeaponInfoPosX = g_pD3dApp->GetBackBufferDesc().Width - SIZE_WEAPON_X;

	m_pParent = pParent;
	memset(m_pWeaponNumberImage, 0x00, sizeof(INT)*10);
}

CINFWeaponInfo::~CINFWeaponInfo()
{
	FLOG( "~CINFWeaponInfo()" );
	SAFE_DELETE(m_pStImage) ;
	SAFE_DELETE(m_pStWeaponImage);
	SAFE_DELETE(m_pNdImage) ;
	SAFE_DELETE(m_pNdWeaponImage);
	SAFE_DELETE(m_pStOverHeatBar) ;
	SAFE_DELETE(m_pNdOverHeatBar);
	SAFE_DELETE(m_pEmptyWeaponImage);
	SAFE_DELETE(m_pWeaponData);
	SAFE_DELETE(m_pStFuelGageBar);
	SAFE_DELETE(m_pStFuelUnderGageBar);
//	SAFE_DELETE(m_pNdFuelGageBar);
//	SAFE_DELETE(m_pNdFuelUnderGageBar);
	SAFE_DELETE(m_pReloadImage);
	SAFE_DELETE(m_pOverHeatImage);
	SAFE_DELETE(m_pBulletEmptyImage);
	SAFE_DELETE(m_pBulletLowImage);

	for(int i=0;i<10;i++)
		SAFE_DELETE(m_pWeaponNumberImage[i]);
}

HRESULT CINFWeaponInfo::InitDeviceObjects()
{
	FLOG( "CINFWeaponInfo::InitDeviceObjects()" );
	char strPath[256];
	g_pD3dApp->LoadPath( strPath, IDS_DIRECTORY_TEXTURE, "weapon.tex");
	m_pWeaponData = new CGameData;
	m_pWeaponData->SetFile(strPath, FALSE, NULL, 0);

	m_pStImage = new CINFImage;
	DataHeader	* pDataHeader = FindResource("1sta");
	m_pStImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pNdImage = new CINFImage;
	pDataHeader = FindResource("2nda");
	m_pNdImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pStOverHeatBar = new CINFImage;
	pDataHeader = FindResource("1stgage");
	m_pStOverHeatBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pNdOverHeatBar = new CINFImage;
	pDataHeader = FindResource("2ndgage");
	m_pNdOverHeatBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pEmptyWeaponImage = new CINFImage;
	pDataHeader = FindResource("weslot");
	m_pEmptyWeaponImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pStFuelGageBar = new CINFImage;
	pDataHeader = FindResource("beam1_g");
	m_pStFuelGageBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pStFuelUnderGageBar = new CINFImage;
	pDataHeader = FindResource("beam1_b");
	m_pStFuelUnderGageBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

/*	m_pNdFuelGageBar = new CINFImage;
	pDataHeader = FindResource("beam2_g");
	m_pNdFuelGageBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pNdFuelUnderGageBar = new CINFImage;
	pDataHeader = FindResource("beam2_b");
	m_pNdFuelUnderGageBar->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
*/
	m_pReloadImage = new CINFImage;
	pDataHeader = FindResource("reload");
	m_pReloadImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	m_pOverHeatImage = new CINFImage;
	pDataHeader = FindResource("weover");
	m_pOverHeatImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	m_pBulletEmptyImage = new CINFImage;
	pDataHeader = FindResource("weempty");
	m_pBulletEmptyImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	m_pBulletLowImage = new CINFImage;
	pDataHeader = FindResource("welow");
	m_pBulletLowImage->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

	for(int i=0;i<10;i++)
	{
		char buf[16];
		wsprintf(buf, "B%d", i);
		m_pWeaponNumberImage[i] = new CINFImage;
		pDataHeader = FindResource(buf);
		m_pWeaponNumberImage[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	}

	return S_OK ;
}

HRESULT CINFWeaponInfo::RestoreDeviceObjects()
{
	FLOG( "CINFWeaponInfo::RestoreDeviceObjects()" );
	m_nRightWeaponInfoPosX = g_pD3dApp->GetBackBufferDesc().Width - SIZE_WEAPON_X;
	if(m_pStImage )
		m_pStImage->RestoreDeviceObjects();
	if(m_pNdImage )
		m_pNdImage->RestoreDeviceObjects();
	if(m_pStOverHeatBar )
		m_pStOverHeatBar->RestoreDeviceObjects();
	if(m_pNdOverHeatBar )
		m_pNdOverHeatBar->RestoreDeviceObjects();
	if(m_pEmptyWeaponImage )
		m_pEmptyWeaponImage->RestoreDeviceObjects();
	if(m_pStFuelGageBar )
		m_pStFuelGageBar->RestoreDeviceObjects();
	if(m_pStFuelUnderGageBar )
		m_pStFuelUnderGageBar->RestoreDeviceObjects();
/*	if(m_pNdFuelGageBar )
		m_pNdFuelGageBar->RestoreDeviceObjects();
	if(m_pNdFuelUnderGageBar )
		m_pNdFuelUnderGageBar->RestoreDeviceObjects();
*/	if(m_pReloadImage )
		m_pReloadImage->RestoreDeviceObjects();
	if(m_pOverHeatImage )
		m_pOverHeatImage->RestoreDeviceObjects();
	if(m_pBulletEmptyImage )
		m_pBulletEmptyImage->RestoreDeviceObjects();
	if(m_pBulletLowImage )
		m_pBulletLowImage->RestoreDeviceObjects();
	for(int i=0;i<10;i++)
	{
		m_pWeaponNumberImage[i]->RestoreDeviceObjects();
	}
	ChangeWeapon(1);
	ChangeWeapon(2);
	return S_OK ;
}

void CINFWeaponInfo::ChangeWeapon(int nWeapon)// nWeapon == 1 then 1�� ����, 2 then 2�� ����
{
	FLOG( "CINFWeaponInfo::ChangeWeapon(int nWeapon)" );

	if(nWeapon == 1)
	{
//		map<int, ITEM_GENERAL*>::iterator it = g_pStoreData->m_mapItemInInventory.find(POS_PROWOUT);// FIRST WEAPON
		CItemInfo *pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(POS_PROWOUT);
//		if(it != g_pStoreData->m_mapItemInInventory.end())
		if(pItemInfo)
		{
//			ITEM_GENERAL* pItem = it->second;
			char buf[16];
//			wsprintf(buf, "%08d",pItemInfo->ItemNum);	// 2005-08-23 by ispark
			wsprintf(buf, "%08d",pItemInfo->ItemInfo->SourceIndex);
			DataHeader	*  pHeader = m_pWeaponData->Find(buf);
			if(m_pStWeaponImage)
			{
				m_pStWeaponImage->InvalidateDeviceObjects();
				m_pStWeaponImage->DeleteDeviceObjects();
				SAFE_DELETE(m_pStWeaponImage);
			}
			if(pHeader)
			{
				m_pStWeaponImage = new CINFImage();
				m_pStWeaponImage->InitDeviceObjects(pHeader->m_pData,pHeader->m_DataSize);
				m_pStWeaponImage->RestoreDeviceObjects();
			}
		}
		else
		{
			if(m_pStWeaponImage)
			{
				m_pStWeaponImage->InvalidateDeviceObjects();
				m_pStWeaponImage->DeleteDeviceObjects();
				SAFE_DELETE(m_pStWeaponImage);
			}
		}
	}
	else if(nWeapon == 2)
	{
//		map<int, ITEM_GENERAL*>::iterator it = g_pStoreData->m_mapItemInInventory.find(POS_WINGOUT);// SECOND WEAPON
		CItemInfo *pItemInfo = g_pStoreData->FindItemInInventoryByWindowPos(POS_WINGOUT);
//		if(it != g_pStoreData->m_mapItemInInventory.end())
		if(pItemInfo)
		{
//			ITEM_GENERAL* pItem = it->second;
			char buf[16];
//			wsprintf(buf, "%08d",pItemInfo->ItemNum);	// 2005-08-23 by ispark
			wsprintf(buf, "%08d",pItemInfo->ItemInfo->SourceIndex);
			DataHeader	*  pHeader = m_pWeaponData->Find(buf);
			if(m_pNdWeaponImage)
			{
				m_pNdWeaponImage->InvalidateDeviceObjects();
				m_pNdWeaponImage->DeleteDeviceObjects();
				SAFE_DELETE(m_pNdWeaponImage);
			}
			if(pHeader)
			{
				m_pNdWeaponImage = new CINFImage();
				m_pNdWeaponImage->InitDeviceObjects(pHeader->m_pData,pHeader->m_DataSize);
				m_pNdWeaponImage->RestoreDeviceObjects();
			}
		}
		else
		{
			if(m_pNdWeaponImage)
			{
				m_pNdWeaponImage->InvalidateDeviceObjects();
				m_pNdWeaponImage->DeleteDeviceObjects();
				SAFE_DELETE(m_pNdWeaponImage);
			}
		}
	}

}

HRESULT CINFWeaponInfo::DeleteDeviceObjects()
{
	FLOG( "CINFWeaponInfo::DeleteDeviceObjects()" );
	if(m_pStImage )
		m_pStImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pStImage ) ;

	if(m_pStWeaponImage )
		m_pStWeaponImage->DeleteDeviceObjects() ;
	SAFE_DELETE(m_pStWeaponImage );

	if(m_pNdImage )
		m_pNdImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pNdImage ) ;

	if(m_pNdWeaponImage )
		m_pNdWeaponImage->DeleteDeviceObjects() ;
	SAFE_DELETE(m_pNdWeaponImage );

	if(m_pStOverHeatBar )
		m_pStOverHeatBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pStOverHeatBar ) ;

	if(m_pNdOverHeatBar )
		m_pNdOverHeatBar->DeleteDeviceObjects() ;
	SAFE_DELETE(m_pNdOverHeatBar );

	if(m_pEmptyWeaponImage )
		m_pEmptyWeaponImage->DeleteDeviceObjects() ;
	SAFE_DELETE(m_pEmptyWeaponImage );

	if(m_pStFuelGageBar )
		m_pStFuelGageBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pStFuelGageBar );
	if(m_pStFuelUnderGageBar )
		m_pStFuelUnderGageBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pStFuelUnderGageBar );
/*	if(m_pNdFuelGageBar )
		m_pNdFuelGageBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pNdFuelGageBar );
	if(m_pNdFuelUnderGageBar )
		m_pNdFuelUnderGageBar->DeleteDeviceObjects();
	SAFE_DELETE(m_pNdFuelUnderGageBar );
*/	if(m_pReloadImage )
		m_pReloadImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pReloadImage );
	if(m_pOverHeatImage )
		m_pOverHeatImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pOverHeatImage );
	if(m_pBulletEmptyImage )
		m_pBulletEmptyImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pBulletEmptyImage );
	if(m_pBulletLowImage )
		m_pBulletLowImage->DeleteDeviceObjects();
	SAFE_DELETE(m_pBulletLowImage );
	for(int i=0;i<10;i++)
	{
		m_pWeaponNumberImage[i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pWeaponNumberImage[i] );
	}
	return S_OK ;
}


HRESULT CINFWeaponInfo::InvalidateDeviceObjects()
{
	FLOG( "CINFWeaponInfo::InvalidateDeviceObjects()" );
	if(m_pStImage )
		m_pStImage->InvalidateDeviceObjects() ;
	if(m_pStWeaponImage )
		m_pStWeaponImage->InvalidateDeviceObjects() ;
	if(m_pNdImage )
		m_pNdImage->InvalidateDeviceObjects() ;
	if(m_pNdWeaponImage )
		m_pNdWeaponImage->InvalidateDeviceObjects() ;
	if(m_pStOverHeatBar )
		m_pStOverHeatBar->InvalidateDeviceObjects() ;
	if(m_pNdOverHeatBar )
		m_pNdOverHeatBar->InvalidateDeviceObjects() ;
	if(m_pEmptyWeaponImage )
		m_pEmptyWeaponImage->InvalidateDeviceObjects() ;
	if(m_pStFuelGageBar )
		m_pStFuelGageBar->InvalidateDeviceObjects();
	if(m_pStFuelUnderGageBar )
		m_pStFuelUnderGageBar->InvalidateDeviceObjects();
/*	if(m_pNdFuelGageBar )
		m_pNdFuelGageBar->InvalidateDeviceObjects();
	if(m_pNdFuelUnderGageBar )
		m_pNdFuelUnderGageBar->InvalidateDeviceObjects();
*/	if(m_pReloadImage )
		m_pReloadImage->InvalidateDeviceObjects();
	if(m_pOverHeatImage )
		m_pOverHeatImage->InvalidateDeviceObjects();
	if(m_pBulletEmptyImage )
		m_pBulletEmptyImage->InvalidateDeviceObjects();
	if(m_pBulletLowImage )
		m_pBulletLowImage->InvalidateDeviceObjects();
	for(int i=0;i<10;i++)
	{
		m_pWeaponNumberImage[i]->InvalidateDeviceObjects();
	}

	return S_OK ;
}


void CINFWeaponInfo::Tick()
{
	FLOG( "CINFWeaponInfo::Tick()" );
	if(m_fFlashTime < FLASH_TIME)
	{
		m_fFlashTime += g_pD3dApp->GetCheckElapsedTime();
	}
	else
	{
		m_fFlashTime = 0;
		m_bFlash = !m_bFlash;
	}


}

void CINFWeaponInfo::RenderLeftWeapon()
{
	FLOG( "CINFWeaponInfo::RenderLeftWeapon()" );
 	int nWindowPosY = g_pGameMain->m_nLeftWindowY;

	// ���������� ������ ������ �ʴ´�
	if(g_pD3dApp->m_dwGameState == _SHOP)
		return;
	// 2007-03-27 by bhsohn ������ ���� �������̽� ����
	if(g_pShuttleChild->IsObserverMode())
	{
		return;
	}
	// end 2007-03-27 by bhsohn ������ ���� �������̽� ����

//	if(m_pStImage )
//	{
//		m_pStImage->Move(m_nLeftWeaponInfoPosX, nWindowPosY);
//		m_pStImage->Render() ;
//	}
//	if(m_pStOverHeatBar)
	if(g_pShuttleChild->m_pPrimaryWeapon)
	{
// 2008-05-29 by dgwoo ���� �������̽� ���� ��ȹ.
//		m_pStOverHeatBar->Move(m_nLeftWeaponInfoPosX+LEFT_OVERHEAT_START_X, nWindowPosY+OVERHEAT_START_Y);
////		m_pStOverHeatBar->SetRect(0, 0, OVERHEAT_LENGTH*g_pD3dApp->m_pShuttleChild->m_fPrimaryWeaponActionRate, OVERHEAT_HEIGHT);
//		m_pStOverHeatBar->SetRect(0, 0, OVERHEAT_LENGTH*g_pShuttleChild->m_pPrimaryWeapon->GetOverHeatRate(), OVERHEAT_HEIGHT);
//		m_pStOverHeatBar->Render();
		m_pStOverHeatBar->Move(FIRST_WEAPON_GAGE_X, FIRST_WEAPON_GAGE_Y);
//		m_pStOverHeatBar->SetRect(0, 0, OVERHEAT_LENGTH*g_pD3dApp->m_pShuttleChild->m_fPrimaryWeaponActionRate, OVERHEAT_HEIGHT);
		m_pStOverHeatBar->SetRect(0, 0, OVERHEAT_LENGTH*g_pShuttleChild->m_pPrimaryWeapon->GetOverHeatRate(), OVERHEAT_HEIGHT);
		m_pStOverHeatBar->Render();
	}
	// 2008-10-20 by dgwoo ���� �̹����� �ʿ����.
	//if(m_pStWeaponImage )		// ���⸦ ������ ������
	if(g_pShuttleChild && g_pShuttleChild->m_pPrimaryWeapon)
	{
		
//		if(g_pD3dApp->m_pShuttleChild && g_pD3dApp->m_pShuttleChild->m_pItemPrimary )
		if(g_pShuttleChild && g_pShuttleChild->m_pPrimaryWeapon )
		{
			if(IS_PRIMARY_WEAPON_1(g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo()->Kind))
			{
				if(LEFT_WEAPON_NUMBER == 0)
				{
					m_pBulletEmptyImage->Move(FIRST_WEAPON_START_X, FIRST_WEAPON_START_Y);
					m_pBulletEmptyImage->Render();
				}
				else if( g_pShuttleChild->m_pPrimaryWeapon->IsOverHeat())
				{
					m_pOverHeatImage->Move(FIRST_WEAPON_START_X, FIRST_WEAPON_START_Y);
					m_pOverHeatImage->Render();
				}
				else if(LEFT_WEAPON_NUMBER < 100 && m_bFlash)//���������� ���
				{
					m_pBulletLowImage->Move(FIRST_WEAPON_START_X, FIRST_WEAPON_START_Y);
					m_pBulletLowImage->Render();
				}
				else
				{
					// 2006-07-19 by dgwoo m_nLeftWeaponInfoPosX�߰� �ִϸ��̼ǿ� ���� �۾��� ������ ��ġ�� �������ش�.
					RenderWeaponNumber(FIRST_WEAPON_FONT_Y, FIRST_WEAPON_FONT_X, LEFT_WEAPON_NUMBER);
				}
			}
			else if(IS_PRIMARY_WEAPON_2(g_pShuttleChild->m_pPrimaryWeapon->GetRealItemInfo()->Kind))// ���� �����
			{
				float fRate = g_pShuttleChild->m_myShuttleInfo.CurrentEP/(float)g_pShuttleChild->m_myShuttleInfo.EP;
				RenderWeaponFuel( nWindowPosY, LEFT_FUEL_X, fRate );
				if(fRate == 0)
				{
					m_pBulletEmptyImage->Move(m_nLeftWeaponInfoPosX+3, nWindowPosY + 10);
					m_pBulletEmptyImage->Render();
				}
				else if( fRate < 0.1f)
				{
					m_pBulletLowImage->Move(m_nLeftWeaponInfoPosX+3, nWindowPosY + 10);
					m_pBulletLowImage->Render();
				}
// 2008-10-20 by dgwoo ���� �̹����� �ʿ����.
//				else if(g_pShuttleChild->m_pPrimaryWeapon->IsOverHeat() == FALSE)
//				{
//					m_pStWeaponImage->Move(m_nLeftWeaponInfoPosX+3, nWindowPosY + 10);
//					m_pStWeaponImage->Render() ;
//				}
				else//���������� ���
				{
					m_pOverHeatImage->Move(m_nLeftWeaponInfoPosX+3, nWindowPosY + 10);
					m_pOverHeatImage->Render() ;
				}
			}
		}
		
	}
	else
	{
		m_pBulletEmptyImage->Move(FIRST_WEAPON_START_X, FIRST_WEAPON_START_Y);
		m_pBulletEmptyImage->Render();

//		m_pEmptyWeaponImage->Move(m_nLeftWeaponInfoPosX+3, nWindowPosY + 10);
//		m_pEmptyWeaponImage->Render() ;
	}
}

void CINFWeaponInfo::RenderRightWeapon()
{
	FLOG( "CINFWeaponInfo::RenderRightWeapon()" );
	int nWindowPosY = g_pGameMain->m_nRightWindowY;

	// ���������� ������ ������ �ʴ´�
	if(g_pD3dApp->m_dwGameState == _SHOP)
		return;
	// 2007-03-27 by bhsohn ������ ���� �������̽� ����
	if(g_pShuttleChild->IsObserverMode())
	{
		return;
	}
	// end 2007-03-27 by bhsohn ������ ���� �������̽� ����
	
//	if(m_pNdImage )
//	{
//		m_pNdImage->Move(m_nRightWeaponInfoPosX, nWindowPosY);
//		m_pNdImage->Render() ;
//	}
//	if(m_pNdOverHeatBar)
	if(g_pShuttleChild->m_pSecondaryWeapon)
	{
//		int startX = (1.0f-g_pD3dApp->m_pShuttleChild->m_fSecondaryWeaponActionRate)*OVERHEAT_LENGTH;
		int startX = (g_pShuttleChild->m_pSecondaryWeapon->GetReattackTimeRate())*OVERHEAT_LENGTH;
		if(g_pD3dApp->m_bCharacter)
			startX = OVERHEAT_LENGTH;
		m_pStOverHeatBar->Move(SECOND_WEAPON_GAGE_X, SECOND_WEAPON_GAGE_Y);
		//m_pStOverHeatBar->SetRect(startX, 0, OVERHEAT_LENGTH, OVERHEAT_HEIGHT);
		m_pStOverHeatBar->SetRect(0, 0, startX, OVERHEAT_HEIGHT);
		m_pStOverHeatBar->Render();
	}
// 2008-10-20 by dgwoo ���� �̹����� �ʿ����.
//	if(m_pNdWeaponImage )		// ���⸦ ������ ������
	if(g_pShuttleChild->m_pSecondaryWeapon)
	{

		if(RIGHT_WEAPON_NUMBER == 0)
		{
			m_pBulletEmptyImage->Move(SECOND_WEAPON_START_X, SECOND_WEAPON_START_Y);
			m_pBulletEmptyImage->Render();
		}
		else if( RIGHT_WEAPON_NUMBER < 10 && m_bFlash)
		{
			m_pBulletLowImage->Move(SECOND_WEAPON_START_X, SECOND_WEAPON_START_Y);
			m_pBulletLowImage->Render();
		}
		else //if(g_pD3dApp->m_pShuttleChild->m_bSecondaryWeaponAction)
		{
			if(RIGHT_WEAPON_NUMBER >= 0)
			{
				RenderWeaponNumber( SECOND_WEAPON_FONT_Y, SECOND_WEAPON_FONT_X, RIGHT_WEAPON_NUMBER);
			}
		}
	}
	else
	{
		m_pBulletEmptyImage->Move(SECOND_WEAPON_START_X, SECOND_WEAPON_START_Y);
		m_pBulletEmptyImage->Render();
	}
}

void CINFWeaponInfo::RenderWeaponFuel( int nWindowPosY, int nWindowPosX, float fRate)
{
	FLOG( "CINFWeaponInfo::RenderWeaponFuel( int nWindowPosY, int nWindowPosX, float fRate)" );
	if(fRate>0)
	{
		m_pStFuelUnderGageBar->Move(nWindowPosX, nWindowPosY+LEFT_FUEL_Y);
		m_pStFuelUnderGageBar->Render();
		m_pStFuelGageBar->Move(nWindowPosX, nWindowPosY+LEFT_FUEL_Y);
		m_pStFuelGageBar->SetRect(0, 0, FUEL_GAGE_LENGTH*fRate, FUEL_GAGE_HEIGHT);
		m_pStFuelGageBar->Render();
	}
	else
	{
		m_pReloadImage->Move(nWindowPosX, nWindowPosY+LEFT_WEAPON_NUMBER_Y);
		m_pReloadImage->Render() ;
	}
}

void CINFWeaponInfo::RenderWeaponNumber( int nWindowPosY, int nWindowPosX, int nValue)
{
	FLOG( "CINFWeaponInfo::RenderWeaponNumber( int nWindowPosY, int nWindowPosX, int nValue)" );
	if(nValue > 0)
	{
//		for(int i=0;i<5;i++) // 5 : 5�ڸ�����
//		{
//			int nNum = nValue%10;
//			m_pWeaponNumberImage[nNum]->Move(nWindowPosX+WEAPON_NUMBER_SIZE*(4-i), nWindowPosY+LEFT_WEAPON_NUMBER_Y);
//			m_pWeaponNumberImage[nNum]->Render();
//			nValue /= 10;
//		}
		for(int i=0;i<5;i++) // 5 : 5�ڸ�����
		{
			int nNum = nValue%10;
			m_pWeaponNumberImage[nNum]->Move(nWindowPosX+WEAPON_NUMBER_SIZE*(4-i), nWindowPosY);
			m_pWeaponNumberImage[nNum]->Render();
			nValue /= 10;
		}
	}
	else
	{
//		m_pReloadImage->Move(nWindowPosX, nWindowPosY+LEFT_WEAPON_NUMBER_Y);
//		m_pReloadImage->Render() ;
	}
}

int CINFWeaponInfo::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FLOG( "CINFWeaponInfo::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)" );
	return INF_MSGPROC_NORMAL;


}
