// INFCityLab.cpp: implementation of the CINFCityLab class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INFCityLab.h"

#include "AtumApplication.h"
#include "INFImage.h"
#include "D3DHanFont.h"
#include "GameDataLast.h"
#include "INFCityBase.h"
#include "AtumDatabase.h"
#include "INFGameMain.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "INFWindow.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "StoreData.h"
//#include "INFScrollBar.h"

//#include "INFTrade.h"
#include "StoreData.h"
//#include "EnemyData.h"
#include "INFItemInfo.h"
#include "INFIcon.h"
//#include "INFImage.h"
//#include "GameDataLast.h"
#include "FieldWinSocket.h"
//#include "AtumDatabase.h"
//#include "SceneData.h"
#include "ItemInfo.h"
//#include "GameDataLast.h"
#include "Chat.h"
#include "Interface.h"
#include "dxutil.h"

#define RENEW_SHOP_SIZE_WIDTH	230

// 2006-08-17 by dgwoo �������� ������ ������ ����ϴ� DEFINE
//--------------------------------------------------------------------------//
#define LAB_ICON_X				25



//--------------------------------------------------------------------------//
#define BACK_START_X			(CITY_BASE_NPC_BOX_START_X+RENEW_SHOP_SIZE_WIDTH + 249)
#define BACK_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 33)
#define SOURCE_SLOT_START_X		(BACK_START_X + 30)
#define SOURCE_SLOT_START_Y		(BACK_START_Y + 34)

#define SLOT_INTERVAL_X			31
#define SLOT_INTERVAL_Y			32

// 2008-03-14 by bhsohn ���ս� ������
#define TARGET_SLOT_START_X		(BACK_START_X + 30)
#define TARGET_SLOT_START_Y		(BACK_START_Y + 150)

#define TARGET_FACTORY_SLOT_START_X		(BACK_START_X + 123)
 
#define CASH_START_X			(CITY_BASE_NPC_BOX_START_X+RENEW_SHOP_SIZE_WIDTH + 251)
#define OK_BUTTON_START_X		(CITY_BASE_NPC_BOX_START_X+RENEW_SHOP_SIZE_WIDTH + 361)
#define OK_BUTTON_START_Y		(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 240)
#define CANCEL_BUTTON_START_X	(CITY_BASE_NPC_BOX_START_X+RENEW_SHOP_SIZE_WIDTH + 398)
#define CANCEL_BUTTON_START_Y	(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 240)
#define BUTTON_SIZE_X			35
#define BUTTON_SIZE_Y			16

#define SOURCE_NUMBER_X			4
#define SOURCE_NUMBER_Y			2

// 2006-03-07 by ispark, �� ���� ��ġ ����
#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
#define CASH_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y + 239)//241)
#define SPI_START_X				(CASH_START_X + 5)
#define SPI_START_Y				(CASH_START_Y + 1)
#else
#define CASH_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y +239)//241)
#define SPI_START_X				(CASH_START_X + 4)
#define SPI_START_Y				(CASH_START_Y + 1)
#endif

// 2008-03-14 by bhsohn ���ս� ������
// ���� �Է� ��Ʈ�� (Ȯ��)
#define		MIX_NUM_EDIT_X		(BACK_START_X+31)
#define		MIX_NUM_EDIT_Y		(BACK_START_Y+162)
#define		MIX_NUM_EDIT_W		(70)
#define		MIX_NUM_EDIT_H		(20)
// �ִ� �۾� �� 
//#define		MIX_MAX_STRING_LEN					4

// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
#define		RARE_FIX_PREFIX							1
#define		RARE_FIX_SUFFIX							2

#define		RARE_FIX_ITEM							1
#define		ITIALIZE_ITEM							2
//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CINFCityLab::CINFCityLab(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	m_pParent						= pParent;
	m_pBuildingInfo					= pBuilding;
	m_bRestored						= FALSE;
	m_pImgBack						= NULL;
	// 2008-03-14 by bhsohn ���ս� ������
	m_pImgBackFactory				= NULL;
	m_pImgTitle						= NULL;
	m_pImgPrice						= NULL;
	m_pFontPrice					= NULL;

	m_nButtonState[0]				= BUTTON_STATE_NORMAL;
	m_nButtonState[1]				= BUTTON_STATE_NORMAL;
	m_pSelectItem					= NULL;
	m_bShowTarget					= FALSE;

	memset( m_pImgButton, 0x00, sizeof(DWORD)*LAB_BUTTON_NUMBER*4);
	memset( m_szPrice, 0x00, 64);

	m_bSelectDown = FALSE;

	// 2008-03-14 by bhsohn ���ս� ������
	m_pNumEditBox= NULL;

	// 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
	m_bIsEnchantCheck = FALSE;
	//end 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
}

CINFCityLab::~CINFCityLab()
{
	SAFE_DELETE(m_pImgBack);
	// 2008-03-14 by bhsohn ���ս� ������
	SAFE_DELETE(m_pImgBackFactory);	
	SAFE_DELETE(m_pImgTitle);
	SAFE_DELETE(m_pImgPrice);
	SAFE_DELETE(m_pFontPrice);

	// 2008-03-14 by bhsohn ���ս� ������
	SAFE_DELETE(m_pNumEditBox);	
	
	for(int i=0;i<4;i++)
	{
		SAFE_DELETE(m_pImgButton[0][i]);
		SAFE_DELETE(m_pImgButton[1][i]);		
		SAFE_DELETE(m_pImgButton[2][i]);		
	}
	InitData();
}

HRESULT CINFCityLab::InitDeviceObjects()
{
	FLOG( "CINFCityLab::InitDeviceObjects()" );
	DataHeader	* pDataHeader;

	m_pImgBack = new CINFImage;
	pDataHeader = FindResource("shlabbk");
	m_pImgBack->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize) ;

	// 2008-03-14 by bhsohn ���ս� ������
	m_pImgBackFactory = new CINFImage;
	pDataHeader = FindResource("shlabbk1");
	m_pImgBackFactory->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize) ;


	m_pImgTitle = new CINFImage;
	pDataHeader = FindResource("lab");
	m_pImgTitle->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize) ;

	m_pImgPrice = new CINFImage;
	pDataHeader = FindResource("shlacost");
	m_pImgPrice->InitDeviceObjects(pDataHeader->m_pData, pDataHeader->m_DataSize) ;

	for(int i=0;i<4;i++)
	{
		char buf[16];

		m_pImgButton[0][i] = new CINFImage;
		wsprintf(buf, "shlama0%d",i);
		pDataHeader = FindResource(buf);
		m_pImgButton[0][i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgButton[1][i] = new CINFImage;		
		wsprintf(buf, "shmcan0%d",i);
		pDataHeader = FindResource(buf);
		m_pImgButton[1][i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;

		m_pImgButton[2][i] = new CINFImage;		
		wsprintf(buf, "shlaok0%d",i);
		pDataHeader = FindResource(buf);
		m_pImgButton[2][i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize) ;
	}

	m_pFontPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);;
	m_pFontPrice->InitDeviceObjects(g_pD3dDev);

	// 2008-03-14 by bhsohn ���ս� ������
	{
		if(NULL == m_pNumEditBox)
		{
			m_pNumEditBox = new CINFNumEditBox;
		}
		char chBuff[32];
		char chMaxMixCnt[64];

		wsprintf(chBuff, "1");
		wsprintf(chMaxMixCnt, "%d", COUNT_MAX_MIXING_COUNT);

		POINT ptPos = {MIX_NUM_EDIT_X, MIX_NUM_EDIT_Y};
		m_pNumEditBox->InitDeviceObjects(9, ptPos, MIX_NUM_EDIT_W, TRUE, MIX_NUM_EDIT_H);				
		m_pNumEditBox->SetMaxStringLen(strlen(chMaxMixCnt));
		m_pNumEditBox->SetString(chBuff, 32);
	}	
	// end 2008-03-14 by bhsohn ���ս� ������

	return S_OK;
}


HRESULT CINFCityLab::RestoreDeviceObjects()
{
	if(!m_bRestored)
	{
		for(int i=0;i<4;i++)
		{
			m_pImgButton[0][i]->RestoreDeviceObjects();
			m_pImgButton[0][i]->Move(OK_BUTTON_START_X, OK_BUTTON_START_Y);
			m_pImgButton[1][i]->RestoreDeviceObjects();
			m_pImgButton[1][i]->Move(CANCEL_BUTTON_START_X, CANCEL_BUTTON_START_Y);
			m_pImgButton[2][i]->RestoreDeviceObjects();
			m_pImgButton[2][i]->Move(OK_BUTTON_START_X, OK_BUTTON_START_Y);
		}

		m_pImgBack->RestoreDeviceObjects();
		m_pImgBack->Move(BACK_START_X, BACK_START_Y);
		// 2008-03-14 by bhsohn ���ս� ������
		m_pImgBackFactory->RestoreDeviceObjects();
		m_pImgBackFactory->Move(BACK_START_X, BACK_START_Y);		
		// end 2008-03-14 by bhsohn ���ս� ������
		m_pImgTitle->RestoreDeviceObjects();
		m_pImgTitle->Move(CITY_BASE_NPC_BOX_START_X, CITY_BASE_NPC_BOX_START_Y);
		m_pImgPrice->RestoreDeviceObjects();
		m_pImgPrice->Move(CASH_START_X, CASH_START_Y);
		m_pFontPrice->RestoreDeviceObjects();

		// 2008-03-14 by bhsohn ���ս� ������		
		m_pNumEditBox->RestoreDeviceObjects();		
		// 2008-03-14 by bhsohn ���ս� ������
		
		m_bRestored = TRUE;
	}
	return S_OK;
}

HRESULT CINFCityLab::DeleteDeviceObjects()
{
	for(int i=0;i<4;i++)
	{
		m_pImgButton[0][i]->DeleteDeviceObjects();
		m_pImgButton[1][i]->DeleteDeviceObjects();
		m_pImgButton[2][i]->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgButton[0][i]);
		SAFE_DELETE(m_pImgButton[1][i]);
		SAFE_DELETE(m_pImgButton[2][i]);
	}
	
	m_pImgBack->DeleteDeviceObjects();
	// 2008-03-14 by bhsohn ���ս� ������
	m_pImgBackFactory->DeleteDeviceObjects();

	m_pImgTitle->DeleteDeviceObjects();
	m_pImgPrice->DeleteDeviceObjects();
	m_pFontPrice->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgBack);
	// 2008-03-14 by bhsohn ���ս� ������
	SAFE_DELETE(m_pImgBackFactory);
	
	SAFE_DELETE(m_pImgTitle);
	SAFE_DELETE(m_pImgPrice);
	SAFE_DELETE(m_pFontPrice);

	// 2008-03-14 by bhsohn ���ս� ������	
	if(m_pNumEditBox)
	{
		m_pNumEditBox->DeleteDeviceObjects();	
		SAFE_DELETE(m_pNumEditBox);
	}		
	// end 2008-03-14 by bhsohn ���ս� ������

	return S_OK;
}

HRESULT CINFCityLab::InvalidateDeviceObjects()
{
	if(m_bRestored)
	{
		for(int i=0;i<4;i++)
		{
			m_pImgButton[0][i]->InvalidateDeviceObjects();
			m_pImgButton[1][i]->InvalidateDeviceObjects();
			m_pImgButton[2][i]->InvalidateDeviceObjects();
		}

		m_pImgBack->InvalidateDeviceObjects();
		// 2008-03-14 by bhsohn ���ս� ������
		m_pImgBackFactory->InvalidateDeviceObjects();
		m_pImgTitle->InvalidateDeviceObjects();
		m_pImgPrice->InvalidateDeviceObjects();
		m_pFontPrice->InvalidateDeviceObjects();
		// 2008-03-14 by bhsohn ���ս� ������	
		m_pNumEditBox->InvalidateDeviceObjects();

		m_bRestored = FALSE;
	}
	return S_OK;
}

void CINFCityLab::Render()
{
//	m_pImgTitle->Render();
	// 2008-03-14 by bhsohn ���ս� ������
	//m_pImgBack->Render();	
	if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_FACTORY)
	{
		m_pImgBackFactory->Render();				
	}
	else
	{
		m_pImgBack->Render();				
	}	
	// end 2008-03-14 by bhsohn ���ս� ������
	m_pImgPrice->Render();

	// 2008-03-14 by bhsohn ���ս� ������	
	if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_FACTORY)
	{
		m_pNumEditBox->Render();
	}

	CINFIcon* pIcon = ((CINFGameMain*)m_pParent)->m_pIcon;
	vector<CItemInfo*>::iterator it = m_vecSource.begin();
	int i = 0;
	while(it != m_vecSource.end())
	{
		CItemInfo* pItem = *it;
		char buf[20];
//		wsprintf(buf, "%08d",pItem->ItemNum);					// 2005-08-23 by ispark


		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		//wsprintf(buf, "%08d",pItem->ItemInfo->SourceIndex);
		if( !pItem->ShapeItemNum )
			wsprintf(buf, "%08d", pItem->ItemInfo->SourceIndex);
		else
		{
			ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( pItem->ShapeItemNum );
			if( pShapeItem )
				wsprintf(buf, "%08d", pShapeItem->SourceIndex );
			else
				wsprintf(buf, "%08d", pItem->ItemInfo->SourceIndex);
		}

		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����



		pIcon->SetIcon( buf, SOURCE_SLOT_START_X+i%SOURCE_NUMBER_X*SLOT_INTERVAL_X+1, 
			SOURCE_SLOT_START_Y+i/SOURCE_NUMBER_X*SLOT_INTERVAL_Y+1, 1.0f );
		pIcon->Render();
		// 2006-08-16 by dgwoo ���丮�� ������ ���� ���.
		if(IS_COUNTABLE_ITEM(pItem->Kind))
		{
			wsprintf( buf, "%d", pItem->CurrentCount);
			SIZE size = m_pFontPrice->GetStringSize(buf);
			m_pFontPrice->DrawText(SOURCE_SLOT_START_X+i%SOURCE_NUMBER_X*SLOT_INTERVAL_X+1+LAB_ICON_X-size.cx, 
				SOURCE_SLOT_START_Y+i/SOURCE_NUMBER_X*SLOT_INTERVAL_Y+1,GUI_FONT_COLOR_W,buf,0L);
		}
		
		it++;
		i++;
	}
	if( m_bShowTarget )
	{
		it = m_vecTarget.begin();		
		i = 0;
		
		// 2008-03-14 by bhsohn ���ս� ������
		int nSlotStartX = TARGET_SLOT_START_X;
		if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_FACTORY)
		{
			nSlotStartX = TARGET_FACTORY_SLOT_START_X;
		}
		
		//while(it != m_vecTarget.end())
		if(it != m_vecTarget.end())
		{
			CItemInfo* pItem = *it;
			char buf[20];
//			wsprintf(buf, "%08d",pItem->ItemNum);				// 2005-08-23 by ispark


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

			//wsprintf(buf, "%08d",pItem->ItemInfo->SourceIndex);
			if( !pItem->ShapeItemNum )
				wsprintf( buf, "%08d",pItem->ItemInfo->SourceIndex );
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( pItem->ShapeItemNum );
				if( pShapeItem )
					wsprintf( buf, "%08d", pShapeItem->SourceIndex );
				else
					wsprintf( buf, "%08d",pItem->ItemInfo->SourceIndex );
			}

			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


			// 2008-03-14 by bhsohn ���ս� ������
			//pIcon->SetIcon( buf, TARGET_SLOT_START_X+i*SLOT_INTERVAL_X+1, TARGET_SLOT_START_Y+1, 1.0f );
			pIcon->SetIcon( buf, nSlotStartX+i*SLOT_INTERVAL_X+1, TARGET_SLOT_START_Y+1, 1.0f );
			
			pIcon->Render();

			// 2008-03-14 by bhsohn ���ս� ������
			if(IS_COUNTABLE_ITEM(pItem->Kind))
			{
				// ����� ���� ī���ͺ� ������ ���� ǥ�� 
				wsprintf( buf, "%d", pItem->CurrentCount);
				SIZE size = m_pFontPrice->GetStringSize(buf);
				
				// 2008-03-14 by bhsohn ���ս� ������
				//m_pFontPrice->DrawText(TARGET_SLOT_START_X+i*SLOT_INTERVAL_X+1+LAB_ICON_X-size.cx, 
				m_pFontPrice->DrawText(nSlotStartX+i*SLOT_INTERVAL_X+1+LAB_ICON_X-size.cx, 				
					TARGET_SLOT_START_Y+1,GUI_FONT_COLOR_W,buf,0L);
			}
			// end 2008-03-14 by bhsohn ���ս� ������

			//it++;
			i++;

		}
		// OK
		m_pImgButton[2][m_nButtonState[0]]->Render();
	}
	else
	{
		// SEND
		m_pImgButton[0][m_nButtonState[0]]->Render();
	}
	// CANCEL
	m_pImgButton[1][m_nButtonState[1]]->Render();
	if(m_szPrice[0] != NULL)
	{
		m_pFontPrice->DrawText(SPI_START_X, SPI_START_Y, GUI_FONT_COLOR, m_szPrice, 0L );
	}
}

void CINFCityLab::Tick()
{
}

int CINFCityLab::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{		
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			g_pGameMain->SetItemInfo( 0, 0, 0, 0 );
			
			if( pt.x > SOURCE_SLOT_START_X &&
				pt.x < SOURCE_SLOT_START_X + SLOT_INTERVAL_X*4)
			{
				if(	pt.y > SOURCE_SLOT_START_Y && 
					pt.y < SOURCE_SLOT_START_Y+SLOT_INTERVAL_Y*2)
				{
					int x = (pt.x - SOURCE_SLOT_START_X) / SLOT_INTERVAL_X;
					int y = (pt.y - SOURCE_SLOT_START_Y) / SLOT_INTERVAL_Y;
					int index = x + y * SOURCE_NUMBER_X;
					if( index >= 0 && m_vecSource.size() > index )
					{
						CItemInfo* pItemInfo = m_vecSource[index];
						if(pItemInfo)
						{
							// 2009-02-03 by bhsohn ���� ������ �� ����
							//g_pGameMain->m_pItemInfo->SetItemInfoUser( pItemInfo, pt.x, pt.y );
							g_pGameMain->SetItemInfoUser( pItemInfo, pt.x, pt.y );
							// end 2009-02-03 by bhsohn ���� ������ �� ����
						}
					}
				}
				else if( m_bShowTarget &&
					pt.y > TARGET_SLOT_START_Y && 
					pt.y < TARGET_SLOT_START_Y+SLOT_INTERVAL_Y)
				{
					// 2008-03-14 by bhsohn ���ս� ������
					//int index = (pt.x - TARGET_SLOT_START_X) / SLOT_INTERVAL_X;
					int nSlotStartX = TARGET_SLOT_START_X;
					if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_FACTORY)
					{
						nSlotStartX = TARGET_FACTORY_SLOT_START_X;
					}				
					int index = (pt.x - nSlotStartX) / SLOT_INTERVAL_X;
					// end 2008-03-14 by bhsohn ���ս� ������

					if( index >= 0 && m_vecTarget.size() > index )
					{
						CItemInfo* pItemInfo = m_vecTarget[index];
						if(pItemInfo)
						{
							// 2009-02-03 by bhsohn ���� ������ �� ����
							//g_pGameMain->m_pItemInfo->SetItemInfoUser( pItemInfo, pt.x, pt.y );
							g_pGameMain->SetItemInfoUser( pItemInfo, pt.x, pt.y );
							// end 2009-02-03 by bhsohn ���� ������ �� ����
						}
					}
				}
				else
				{
					g_pGameMain->SetItemInfo( 0, 0, 0, 0 );
				}
			}

			if(pt.y > OK_BUTTON_START_Y && 
				pt.y < OK_BUTTON_START_Y+BUTTON_SIZE_Y)
			{
				if( pt.x > OK_BUTTON_START_X && 
					pt.x < OK_BUTTON_START_X+BUTTON_SIZE_X)
				{
					if(m_nButtonState[0] != BUTTON_STATE_DOWN)
						m_nButtonState[0] = BUTTON_STATE_UP;
				}
				else 
				{
					m_nButtonState[0] = BUTTON_STATE_NORMAL;
				}
				/////////////////////////////////////////////////////////////////////////////
				
				if( pt.x > CANCEL_BUTTON_START_X && 
					pt.x < CANCEL_BUTTON_START_X+BUTTON_SIZE_X)
				{
					if(m_nButtonState[1] != BUTTON_STATE_DOWN)
						m_nButtonState[1] = BUTTON_STATE_UP;
				}
				else 
				{
					m_nButtonState[1] = BUTTON_STATE_NORMAL;
				}
			}
			else
			{
				m_nButtonState[0] = BUTTON_STATE_NORMAL;
				m_nButtonState[1] = BUTTON_STATE_NORMAL;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

//			if(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
//				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_LAB_POS)
//			{
//				m_bSelectDown = TRUE;
//			}

			// 2008-03-14 by bhsohn ���ս� ������
			BOOL bOldEditMode = m_pNumEditBox->IsEditMode();
			if(TRUE == m_pNumEditBox->OnLButtonDown(pt) && (m_pBuildingInfo->BuildingKind == BUILDINGKIND_FACTORY))
			{			
				if(!bOldEditMode)
				{
					UpdateMixPrice();// ���հ��� ǥ��
				}
				m_pNumEditBox->EnableEdit(TRUE);
				// ��ư���� ���콺�� �ִ�.
				return  INF_MSGPROC_BREAK;				
			}
			m_pNumEditBox->EnableEdit(FALSE);
			if(bOldEditMode)
			{				
				UpdateMixPrice();// ���հ��� ǥ��
			}
			// end 2008-03-14 by bhsohn ���ս� ������

			if(pt.y > OK_BUTTON_START_Y && 
				pt.y < OK_BUTTON_START_Y + BUTTON_SIZE_Y)
			{
				if( pt.x > OK_BUTTON_START_X && 
					pt.x < OK_BUTTON_START_X+BUTTON_SIZE_X)
				{
					m_nButtonState[0] = BUTTON_STATE_DOWN;
				}
				else 
				{
					m_nButtonState[0] = BUTTON_STATE_NORMAL;
				}
				if( pt.x > CANCEL_BUTTON_START_X && 
					pt.x < CANCEL_BUTTON_START_X+BUTTON_SIZE_X)
				{
					m_nButtonState[1] = BUTTON_STATE_DOWN;
				}
				else 
				{
					m_nButtonState[1] = BUTTON_STATE_NORMAL;
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			int nWindowPosY = g_pGameMain->m_nLeftWindowY;
						
			if(pt.y > OK_BUTTON_START_Y && 
				pt.y < OK_BUTTON_START_Y + BUTTON_SIZE_Y)
			{
				if( pt.x > OK_BUTTON_START_X && 
					pt.x < OK_BUTTON_START_X+BUTTON_SIZE_X)
				{
					// 2008-03-14 by bhsohn ���ս� ������
					m_pNumEditBox->EnableEdit(FALSE);
					
					if(m_bShowTarget)
					{
						OnButtonClicked(2);// OK
					}
					else
					{
						OnButtonClicked(0); // SEND
					}
					m_nButtonState[0] = BUTTON_STATE_UP;
				}
				else 
				{
					m_nButtonState[0] = BUTTON_STATE_NORMAL;
				}
				if( pt.x > CANCEL_BUTTON_START_X && 
					pt.x < CANCEL_BUTTON_START_X+BUTTON_SIZE_X)
				{
					OnButtonClicked(1);
					m_nButtonState[1] = BUTTON_STATE_UP;
				}
				else 
				{
					m_nButtonState[1] = BUTTON_STATE_NORMAL;
				}
			}	
			int nSourceMaxCount = 0;
			if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_LABORATORY)
			{
				// 2009. 01. 21 by ckPark ��æƮ Ȯ�� ���� ī��
				//nSourceMaxCount = 2;
				// Ȯ�� ���� ī�� ������ �ִ� 4���� �ø���
				// 2011-11-04 by hsson ���� �� ��� �������� �ִ� 4���ΰ��� 5������ �ø�
				//nSourceMaxCount = 3;
				nSourceMaxCount = 4;
				// end 2011-11-04 by hsson ���� �� ��� �������� �ִ� 4���ΰ��� 5������ �ø�
				// end 2009. 01. 21 by ckPark ��æƮ Ȯ�� ���� ī��
			}
			else if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_FACTORY)
			{
				nSourceMaxCount = (SOURCE_NUMBER_X*SOURCE_NUMBER_Y)-1;
			}
			if( pt.x > SOURCE_SLOT_START_X &&
				pt.x < SOURCE_SLOT_START_X + SLOT_INTERVAL_X*4 &&
				pt.y > SOURCE_SLOT_START_Y &&
				pt.y < SOURCE_SLOT_START_Y + SLOT_INTERVAL_Y*2 &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_INVEN_POS &&
				m_vecSource.size() <= nSourceMaxCount )//(SOURCE_NUMBER_X*SOURCE_NUMBER_Y)-1)
			{
				CItemInfo* pItemInfo = (CItemInfo*)((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem->pItem;

				if(IS_COUNTABLE_ITEM(pItemInfo->Kind))
				{					
					if(m_pSelectItem == NULL)
					{
						m_pSelectItem = pItemInfo;

						// ���������� ���丮�� �ƴϰų�, �������� ��þƮ,������ �ƴϸ� �޽��� �ڽ��� ����.
						if(	BUILDINGKIND_LABORATORY == m_pBuildingInfo->BuildingKind && 
							IS_SPECIAL_COUNTABLE_ITEM(pItemInfo->Kind) )
						{
							if(FindItemFromSource(pItemInfo->UniqueNumber) == NULL)
							{
//								InvenToSourceItem(((CINFGameMain*)m_pParent)->m_pInven->m_pSelectItem, 1);
								InvenToSourceItem(pItemInfo, 1);
							}
							m_pSelectItem = NULL;
						}
						else
						{
							((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox(
								STRMSG_C_CITYLAP_0001, _Q_LAB_ITEM_NUMBER, (DWORD)this, pItemInfo->CurrentCount);//"��� �ø��ðڽ��ϱ�?"
						}
					}					
				}
				else
				{
					if(pItemInfo->Wear != WEAR_NOT_ATTACHED)
					{
						((CINFGameMain*)m_pParent)->m_pInfWindow->AddMsgBox(
							STRMSG_C_CITYLAP_0002, _MESSAGE );//"����� �������� �ø� �� �����ϴ�."
					}
					else
					{
						// 2007-12-13 by dgwoo �ð��� �������̸鼭 ����� �������̶�� ���丮�� �ø��� ����.
						if((pItemInfo->ItemInfo->Kind == ITEMKIND_ACCESSORY_TIMELIMIT 
							|| COMPARE_BIT_FLAG(pItemInfo->ItemInfo->ItemAttribute, ITEM_ATTR_TIME_LIMITE)
							|| COMPARE_BIT_FLAG(pItemInfo->ItemInfo->ItemAttribute, ITEM_ATTR_DELETED_TIME_LIMITE_AFTER_USED)) // 2008-11-26 by bhsohn ����ð� ���� ������ ����
							&& pItemInfo->GetItemPassTime() != 0)
						{
							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_071212_0100,COLOR_ERROR);//"�ش� �������� ���� �� �� �ִ� ���°� �ƴմϴ�."
						}
						else
						{
							InvenToSourceItem(pItemInfo, 1);
						}
						
					}
					//m_vecSource.push_back(((CINFGameMain*)m_pParent)->m_pInven->m_pSelectItem);
				}
				// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
				if(g_pGameMain && g_pGameMain->m_pInven)
				{
					g_pGameMain->SetToolTip(NULL, 0, 0);
					g_pGameMain->m_pInven->SetItemInfo(NULL, 0, 0);
					g_pGameMain->m_pInven->SetMultiSelectItem(NULL);	// ���� ó�� ����
					g_pGameMain->m_pInven->SetSelectItem(NULL);
				}
				// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��

			}
		}
		break;
	case WM_KEYDOWN:
		{
			// 2008-03-14 by bhsohn ���ս� ������
			if(m_pNumEditBox->WndProc(uMsg, wParam, lParam))
			{
				UpdateMixPrice();// ���հ��� ǥ��
				return INF_MSGPROC_BREAK;
			}
			// end 2008-03-14 by bhsohn ���ս� ������
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFCityLab::OnButtonClicked(int nButton)
{
	switch(nButton)
	{
	case 0:	//	SEND
		{
			if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_LABORATORY)
			{
				if ( g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_ENCHANT_PREVENTION ) )
				{
					return;
				}

				// 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
				if ( FALSE == m_bIsEnchantCheck && IsWarning_EnchantFail() )
				{
					g_pGameMain->m_pInfWindow->AddMsgBox ( STRMSG_C_100618_0407, _Q_ENCHANT_PREVENTION );	//"��þƮ �ı����� ī�尡 ���� ��þƮ �������� �ı� �ɼ� �ֽ��ϴ�."	
					return;
				}

				m_bIsEnchantCheck = FALSE;
				//end 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
				BOOL bGamble = FALSE;

				MSG_FC_ITEM_USE_ENCHANT sMsg;
					memset((char*)&sMsg, 0x00, sizeof(sMsg));

				// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
				int nIsPrefix = NULL;
				int nOverlapItem = NULL;
				//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
				
				vector<CItemInfo*>::iterator it = m_vecSource.begin();

				CItemInfo *pcItemInfo = NULL;

				while(it != m_vecSource.end())
				{
					pcItemInfo = (CItemInfo *)*it;

					if( pcItemInfo->Kind == ITEMKIND_ENCHANT || pcItemInfo->Kind == ITEMKIND_GAMBLE)
					{
						// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
						//if(sMsg.EnchantItemUniqueNumber != 0)
//						
// 						{
// 							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_CITYLAP_0003,COLOR_ERROR);//"�߸��� ������ �����Դϴ�."
// 							InitData();
// 							return;
// 						}
						if(nOverlapItem == NULL)
						{
							nOverlapItem = pcItemInfo->Kind;
						}
						else
						{
							if(nOverlapItem != pcItemInfo->Kind)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
						}
					
						//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
						if(pcItemInfo->Kind == ITEMKIND_GAMBLE)
						{
							bGamble = TRUE;
						}
						// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
						//sMsg.EnchantItemUniqueNumber = (*it)->UniqueNumber;
						if(pcItemInfo->ItemInfo->IsExistDesParam(DES_RARE_FIX_PREFIX))
						{
							if(sMsg.EnchantItemUniqueNumber != 0)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							sMsg.EnchantItemUniqueNumber = pcItemInfo->UniqueNumber;
							nIsPrefix = RARE_FIX_PREFIX;							
						}
						else if(pcItemInfo->ItemInfo->IsExistDesParam(DES_RARE_FIX_SUFFIX))
						{
							if(sMsg.EnchantItemUniqueNumber2 != 0)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							sMsg.EnchantItemUniqueNumber2 = pcItemInfo->UniqueNumber;
							nIsPrefix = RARE_FIX_SUFFIX;
						}

						else if(pcItemInfo->ItemInfo->IsExistDesParam(DES_RARE_FIX_PREFIX_INITIALIZE))
						{
							if(sMsg.EnchantItemUniqueNumber != 0)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							sMsg.EnchantItemUniqueNumber = pcItemInfo->UniqueNumber;
							nIsPrefix = RARE_FIX_PREFIX;
						}
						else if(pcItemInfo->ItemInfo->IsExistDesParam(DES_RARE_FIX_SUFFIX_INITIALIZE))
						{
							if(sMsg.EnchantItemUniqueNumber2 != 0)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							sMsg.EnchantItemUniqueNumber2 = pcItemInfo->UniqueNumber;
							nIsPrefix = RARE_FIX_SUFFIX;
						}
						else
						{
							if(sMsg.EnchantItemUniqueNumber != 0)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							sMsg.EnchantItemUniqueNumber = pcItemInfo->UniqueNumber;
						}
						//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
					}
					else if(pcItemInfo->Kind == ITEMKIND_PREVENTION_DELETE_ITEM)
					{
// 						// 2008-05-29 by bhsohn ��þƮ ���� ���׼���
// 						if(sMsg.AttachItemUniqueNumber != 0)
// 						{
// 							g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_CITYLAP_0003,COLOR_ERROR);//"�߸��� ������ �����Դϴ�."
// 							InitData();
// 							return;
// 						}
//						sMsg.AttachItemUniqueNumber = pcItemInfo->UniqueNumber;
// 						// end 2008-05-29 by bhsohn ��þƮ ���� ���׼���

						
						// 2009. 01. 21 by ckPark ��æƮ Ȯ�� ���� ī��
						// �ı�����ī�峪 Ȯ������ī�� �Ѵ� ������ī�ε尡 �����Ƿ�
						// DES_ENCHANT_INCREASE_PROBABILITY �� �����ϸ� Ȯ�� ���� ī��� �ν�
						if( pcItemInfo->ItemInfo->GetParameterValue(DES_ENCHANT_INCREASE_PROBABILITY) != 0.0f )
						{
							if(sMsg.IncreaseProbabilityItemUID != 0)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							
							sMsg.IncreaseProbabilityItemUID = pcItemInfo->UniqueNumber;
						}
						// DES_ENCHANT_INCREASE_PROBABILITY �� �������� ������ �ı����� ī��� �ν�
						else
						{
							if(sMsg.AttachItemUniqueNumber != 0)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							sMsg.AttachItemUniqueNumber = pcItemInfo->UniqueNumber;
						}
						// end 2009. 01. 21 by ckPark ��æƮ Ȯ�� ���� ī��

					}
					// 2010. 02. 11 by ckPark �ߵ��� ����������

// 					else if(IS_WEAPON((*it)->Kind)
// 						|| ((*it)->Kind == ITEMKIND_DEFENSE)
// 						// 2008-09-26 by bhsohn �ű� ��þƮ ó��
// 						|| ((*it)->Kind == ITEMKIND_SUPPORT)
// 						|| ((*it)->Kind == ITEMKIND_RADAR))	
// 						// end 2008-09-26 by bhsohn �ű� ��þƮ ó��
					else if( IS_ENCHANT_TARGET_ITEMKIND( pcItemInfo->Kind ) )

					// end 2010. 02. 11 by ckPark �ߵ��� ����������
					{
						// 2008-05-29 by bhsohn ��þƮ ���� ���׼���
						if(sMsg.TargetItemUniqueNumber != 0)
						{
							ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
							return;
						}											
						// end 2008-05-29 by bhsohn ��þƮ ���� ���׼���
						sMsg.TargetItemUniqueNumber = pcItemInfo->UniqueNumber;
					}
					else
					{
						// 2008-05-29 by bhsohn ��þƮ ���� ���׼���
						ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
						return;
						// end 2008-05-29 by bhsohn ��þƮ ���� ���׼���
					}

					it++;
				}

				// 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����
				if(sMsg.EnchantItemUniqueNumber == 0 && sMsg.EnchantItemUniqueNumber2 != 0)
				{	
					sMsg.EnchantItemUniqueNumber = sMsg.EnchantItemUniqueNumber2;
					sMsg.EnchantItemUniqueNumber2 = NULL;
				}

				if(sMsg.EnchantItemUniqueNumber != 0 && sMsg.EnchantItemUniqueNumber2 != 0)
				{
					int IS_FIX_INFO = NULL;
					vector<CItemInfo*>::iterator it = m_vecSource.begin();
					while(it != m_vecSource.end())
					{
						if(IS_FIX_INFO == 0)
						{
							if((*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_PREFIX_INITIALIZE) ||
								(*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_SUFFIX_INITIALIZE))
							{
								IS_FIX_INFO = ITIALIZE_ITEM;
							}
							else if((*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_PREFIX) ||
									(*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_SUFFIX))
							{
								IS_FIX_INFO = RARE_FIX_ITEM;
							}
						}
						else
						{
							if(((*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_PREFIX_INITIALIZE) ||
								(*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_SUFFIX_INITIALIZE)) && 
								IS_FIX_INFO == RARE_FIX_ITEM)
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
							else if(((*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_PREFIX) ||
									(*it)->ItemInfo->IsExistDesParam(DES_RARE_FIX_SUFFIX)) && 
									IS_FIX_INFO == ITIALIZE_ITEM)	
							{
								ErrorMsg_InvalidEnchantList ( STRMSG_C_CITYLAP_0003 );
								return;
							}
						}
						it++;
					}
				}
				//end 2010. 04. 21 by jskim �ű� ��Ű �ӽ� ����

				if(bGamble == TRUE && sMsg.AttachItemUniqueNumber != 0)
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_CITYLAP_0003,COLOR_ERROR);
					InitData();
				}
				else if(sMsg.TargetItemUniqueNumber != 0 && sMsg.EnchantItemUniqueNumber != 0)
				{
					m_vecTarget = m_vecSource;
					m_vecSource.clear();
					m_bShowTarget = FALSE;
					g_pFieldWinSocket->SendMsg( T_FC_ITEM_USE_ENCHANT, (char*)&sMsg, sizeof(sMsg));

					g_pD3dApp->m_bRequestEnable = FALSE;			// 2006-06-19 by ispark

					//InitData();
				}
				else
				{
					g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_CITYLAP_0003,COLOR_ERROR);
					InitData();
				}
			}
			else if(m_pBuildingInfo->BuildingKind == BUILDINGKIND_FACTORY)
			{
				if(m_vecSource.size() == 0)
				{
					break;
				}
				char pPacket[SIZE_MAX_PACKET];
				MSG_FC_ITEM_MIX_ITEMS sMsg;
				memset(&sMsg, 0x00, sizeof(MSG_FC_ITEM_MIX_ITEMS));
				sMsg.NumOfItems = m_vecSource.size();
				
				// 2008-03-14 by bhsohn ���ս� ������
				char chBuff[256];
				m_pNumEditBox->GetString(chBuff, 256);
				sMsg.nMixCounts = atoi(chBuff);
				if(sMsg.nMixCounts > COUNT_MAX_MIXING_COUNT)
				{
					sMsg.nMixCounts = COUNT_MAX_MIXING_COUNT;
				}
				// end 2008-03-14 by bhsohn ���ս� ������

				memcpy( pPacket, (char*)&sMsg, sizeof(sMsg) );

				int i = 0;

				vector<CItemInfo*>::iterator it = m_vecSource.begin();

				while ( it != m_vecSource.end() )
				{
					ITEM_UNIQUE_NUMBER_W_COUNT itemCount;
					itemCount.ItemUniqueNumber = (*it)->UniqueNumber;
					itemCount.Count = (*it)->CurrentCount;
					memcpy( pPacket + sizeof(sMsg) + i*sizeof(ITEM_UNIQUE_NUMBER_W_COUNT),
						(char*)&itemCount, 
						sizeof(ITEM_UNIQUE_NUMBER_W_COUNT));
					it++;
					i++;
				}				

				g_pFieldWinSocket->SendMsg( T_FC_ITEM_MIX_ITEMS, 
											pPacket, 
											sizeof(sMsg)+sizeof(ITEM_UNIQUE_NUMBER_W_COUNT)*m_vecSource.size() );

				g_pD3dApp->m_bRequestEnable = FALSE;			// 2006-06-19 by ispark
				m_vecTarget = m_vecSource;
				m_vecSource.clear();
				m_bShowTarget = FALSE;
			}
		}
		break;

	case 1:	//	CANCEL
		{
			InitData();
		}
		break;

	case 2: // OK
		{
			InitData();
		}
		break;
	}
}

void CINFCityLab::InvenToSourceItem(CItemInfo* pItemInfo, int nCount)
{
	if(ITEMKIND_ENCHANT == pItemInfo->Kind || ITEMKIND_GAMBLE == pItemInfo->Kind)
	{
		MSG_FC_INFO_GET_ENCHANT_COST sMsg;
		sMsg.EnchantItemNum = pItemInfo->ItemNum;
		g_pFieldWinSocket->SendMsg( T_FC_INFO_GET_ENCHANT_COST, (char*)&sMsg, sizeof(sMsg));
	}
	// Inven���� �����.
	if(IS_COUNTABLE_ITEM(pItemInfo->Kind))
	{
		ASSERT_ASSERT(pItemInfo->CurrentCount >= nCount);
		
		vector<CItemInfo*>::iterator it = m_vecSource.begin();
		while( it != m_vecSource.end() )
		{
			if((*it)->UniqueNumber == pItemInfo->UniqueNumber )
			{
				(*it)->CurrentCount += nCount;
				break;
			}
			it++;
		}
		if( it == m_vecSource.end() )
		{
			CItemInfo* pNewItem = new CItemInfo((ITEM_GENERAL*)pItemInfo);

			// 2010. 02. 11 by ckPark �ߵ��� ����������
			//pNewItem->SetEnchantParam( pItemInfo->GetEnchantParamFactor(), pItemInfo->GetEnchantNumber() );
			// �ߵ��� ��æƮ �� ��Ÿ�� �߰� ����
			pNewItem->CopyItemInfo( pItemInfo );
			// end 2010. 02. 11 by ckPark �ߵ��� ����������

			pNewItem->CurrentCount = nCount;
			m_vecSource.push_back(pNewItem);
			// 2007-12-17 by bhsohn ���� ���� ǥ��
			// ���հ��� ǥ��
			UpdateMixPrice();
		}
		g_pStoreData->UpdateItemCount( pItemInfo->UniqueNumber, pItemInfo->CurrentCount - nCount);
	}
	else 
	{
		CItemInfo* pNewItem = new CItemInfo((ITEM_GENERAL*)pItemInfo);

		// 2010. 02. 11 by ckPark �ߵ��� ����������
		//pNewItem->SetEnchantParam( pItemInfo->GetEnchantParamFactor(), pItemInfo->GetEnchantNumber() );
		// �ߵ��� ��æƮ �� ��Ÿ�� �߰� ����
		pNewItem->CopyItemInfo( pItemInfo );
		// end 2010. 02. 11 by ckPark �ߵ��� ����������

//      ��æƮ�� �Ѿ˼��� 1�� ��� ����
//		pNewItem->CurrentCount = nCount;
		m_vecSource.push_back(pNewItem);
		g_pStoreData->DeleteItem( pItemInfo->UniqueNumber );
		// 2007-12-17 by bhsohn ���� ���� ǥ��
		// ���հ��� ǥ��
		UpdateMixPrice();
	}
	
	// 2006-06-21 by ispark, ����
//	if(	(g_pStoreData->m_mapItemUniqueNumber.size()/6)-2 < g_pGameMain->m_pInven->m_nInvenCurrentScroll)
//	{
//		g_pGameMain->m_pInven->m_nInvenCurrentScroll = (g_pStoreData->m_mapItemUniqueNumber.size()/6)-2;
//	}
}

BOOL CINFCityLab::PutRareInfo(MSG_FC_STORE_UPDATE_RARE_FIX* pMsg)
{
	vector<CItemInfo*>::iterator it = m_vecTarget.begin();
	while(it != m_vecTarget.end())
	{
		if((*it)->UniqueNumber == pMsg->ItemUID )
		{
			(*it)->ChangeRareInfo(pMsg->PrefixCodeNum, pMsg->SuffixCodeNum);
			return TRUE;
		}
		it++;
	}
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityLab::PutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg)
/// \brief		��æƮ �õ� ��� - ������ �������� �Ѱ��ش�.
/// \author		dhkwon
/// \date		2004-07-18 ~ 2004-07-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
//BOOL CINFCityLab::PutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg)
//{
//	FLOG( "CStoreData::PutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg)" );
//	vector<CItemInfo*>::iterator it = m_vecTarget.begin();
//	while(it != m_vecTarget.end())
//	{
//		if((*it)->UniqueNumber == pMsg->Enchant.TargetItemUniqueNumber )
//		{
//			(*it)->PutEnchant( pMsg->Enchant.DestParameter, pMsg->Enchant.ParameterValue );
//			return TRUE;
//		}
//		it ++;
//	}
//	return FALSE;
//}
BOOL CINFCityLab::PutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg)
{
	FLOG( "CStoreData::PutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg)" );
	vector<CItemInfo*>::iterator it = m_vecTarget.begin();
	while(it != m_vecTarget.end())
	{
		if((*it)->UniqueNumber == pMsg->Enchant.TargetItemUniqueNumber )
		{
			(*it)->AddEnchantItem( pMsg->Enchant.EnchantItemNum );
//			ITEM* pEnchantITEM = g_pDatabase->GetServerItemInfo( pMsg->Enchant.EnchantItemNum );
//			if( pEnchantITEM )
//			{
//				if( pEnchantITEM->DestParameter1 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter1, pEnchantITEM->ParameterValue1);
//				}
//				if( pEnchantITEM->DestParameter2 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter2, pEnchantITEM->ParameterValue2);
//				}
//				if( pEnchantITEM->DestParameter3 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter3, pEnchantITEM->ParameterValue3);
//				}
//				if( pEnchantITEM->DestParameter4 != DES_NULL )
//				{
//					(*it)->PutEnchant(pEnchantITEM->DestParameter4, pEnchantITEM->ParameterValue4);
//				}
//			}
			return TRUE;
		}
		it ++;
	}
	return FALSE;
}

void CINFCityLab::InitData()
{
	vector<CItemInfo*>::iterator it = m_vecSource.begin();
	while(it != m_vecSource.end())
	{
		(*it)->ItemWindowIndex = POS_INVALID_POSITION;
		if(g_pStoreData)
		{
			g_pStoreData->PutItem((char*)((ITEM_GENERAL*)(*it)), TRUE);
			CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( (*it)->UniqueNumber );
			ASSERT_ASSERT( pItemInfo );

			// 2010. 02. 11 by ckPark �ߵ��� ����������
			//pItemInfo->SetEnchantParam( (*it)->GetEnchantParamFactor(), (*it)->GetEnchantNumber() );
			// �ߵ��� ��æƮ �� ��Ÿ�� �߰� ����
			pItemInfo->CopyItemInfo( (*it) );
			// end 2010. 02. 11 by ckPark �ߵ��� ����������

		}
		SAFE_DELETE(*it);
		it++;
	}
	m_vecSource.clear();
	it = m_vecTarget.begin();
	while(it != m_vecTarget.end())
	{
		(*it)->ItemWindowIndex = POS_INVALID_POSITION;
		if(g_pStoreData)
		{
			g_pStoreData->PutItem((char*)((ITEM_GENERAL*)(*it)), TRUE);
			CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber( (*it)->UniqueNumber );
			ASSERT_ASSERT( pItemInfo );

			// 2010. 02. 11 by ckPark �ߵ��� ����������
			//pItemInfo->SetEnchantParam( (*it)->GetEnchantParamFactor(), (*it)->GetEnchantNumber() );
			// �ߵ��� ��æƮ �� ��Ÿ�� �߰� ����
			pItemInfo->CopyItemInfo( (*it) );
			// end 2010. 02. 11 by ckPark �ߵ��� ����������
		}
		SAFE_DELETE(*it);
		it++;
	}
	m_vecTarget.clear();
	
	g_pShuttleChild->ResortingItem();// ����
	if(g_pGameMain && g_pGameMain->m_pInven)
	{
		g_pGameMain->m_pInven->SetScrollEndLine();				// 2006-06-21 by ispark
		g_pGameMain->m_pInven->SetAllIconInfo();
	}
	memset( m_szPrice, 0x00, 64);
	m_bShowTarget = FALSE;
	// 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
	m_bIsEnchantCheck = FALSE;
	g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_ENCHANT_PREVENTION);
	//end 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�		
}

void CINFCityLab::SetPrice(int nPrice)
{
	wsprintf( m_szPrice, "%d", nPrice);
	if( g_pGameMain->m_pInven->GetItemSpi() < nPrice )
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_CITYLAP_0004,COLOR_ERROR);//"�����ᰡ �����մϴ�."
	}
}

void CINFCityLab::DeleteTargetItem(int nItemUniqueNumber)
{
	vector<CItemInfo*>::iterator it =  m_vecTarget.begin();
	while( it != m_vecTarget.end() )
	{
		if( (*it)->UniqueNumber == nItemUniqueNumber )
		{
			SAFE_DELETE( *it );
			m_vecTarget.erase( it );
			break;
		}
		it++;
	}
	if(m_vecTarget.size() > 0)
	{
		DBGOUT("Enchant/Mix Result(View)\n");
		m_bShowTarget = TRUE;
		g_pD3dApp->m_bRequestEnable = TRUE;			// 2006-06-19 by ispark
		g_pD3dApp->m_fRequestEnableTime = REQUEST_ENABLE_INIT_TIME;
	}
	else
	{
		m_bShowTarget = FALSE;
	}
}

void CINFCityLab::PutTargetItem(ITEM_GENERAL* pItem)
{
	vector<CItemInfo*>::iterator it =  m_vecTarget.begin();
	while( it != m_vecTarget.end() )
	{
		if( (*it)->UniqueNumber == pItem->UniqueNumber )
		{
			DBGOUT("Mix System Result - Already Being Item.");
			return;
		}
		it++;
	}
	CItemInfo * pNewItem = new CItemInfo(pItem);
	m_vecTarget.push_back(pNewItem);
	m_bShowTarget = TRUE;
	g_pD3dApp->m_bRequestEnable = TRUE;			// 2006-06-19 by ispark
	g_pD3dApp->m_fRequestEnableTime = REQUEST_ENABLE_INIT_TIME;
}

CItemInfo* CINFCityLab::GetTargetItemInfo()
{
	vector<CItemInfo*>::iterator it =  m_vecTarget.begin();
	while( it != m_vecTarget.end() )
	{
		if( (*it)->Kind != ITEMKIND_ENCHANT 
			&& (*it)->Kind != ITEMKIND_GAMBLE 
			&& (*it)->Kind != ITEMKIND_PREVENTION_DELETE_ITEM)
		{
			return *it;
		}
		it++;
	}

	return NULL;
}

CItemInfo* CINFCityLab::FindItemFromSource(UID64_t UniqueNumber)
{
	vector<CItemInfo*>::iterator it = m_vecSource.begin();
	while(it != m_vecSource.end())
	{
		if(UniqueNumber == (*it)->UniqueNumber)
		{
			return (*it);
		}
		it++;
	}
	return NULL;
}

CItemInfo* CINFCityLab::FindItemFromTarget(UID64_t UniqueNumber)
{
	vector<CItemInfo*>::iterator it = m_vecTarget.begin();
	while(it != m_vecTarget.end())
	{
		if(UniqueNumber == (*it)->UniqueNumber)
		{
			return (*it);
		}
		it++;
	}
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityLab::ReSetTargetItemNum(UID64_t UniqueNumber, int nItemNum)
/// \brief		���ս� ������ �ѹ��� �ٲ��.
/// \author		ispark
/// \date		2006-06-15 ~ 2006-06-15
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLab::ReSetTargetItemNum(UID64_t UniqueNumber, int nItemNum)
{
	CItemInfo* pItemInfo = FindItemFromTarget(UniqueNumber);
	ITEM* pItem = g_pDatabase->GetServerItemInfo(nItemNum);

	if(pItem == NULL || pItemInfo == NULL)
	{
		return;
	}
	
	pItemInfo->ItemInfo = pItem;
	pItemInfo->ItemNum = nItemNum;

	// 2009-04-07 by bhsohn ������ �ѹ� ���� ����
	pItemInfo->ResetRealItemInfo();
	// end 2009-04-07 by bhsohn ������ �ѹ� ���� ����
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityLab::SetSelectItem(CItemInfo* pItemInfo)
/// \brief		
/// \author		ispark
/// \date		2006-07-27 ~ 2006-07-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLab::SetSelectItem(CItemInfo* pItemInfo)
{

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityLab::UpdateMixPrice()
/// \brief		
/// \author		// 2007-12-17 by bhsohn ���� ���� ǥ��
/// \date		2007-12-17 ~ 2007-12-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLab::UpdateMixPrice()
{
	if(NULL == m_pBuildingInfo 
		|| m_pBuildingInfo->BuildingKind != BUILDINGKIND_FACTORY)
	{
		return;
	}
	// 2008-03-14 by bhsohn ���ս� ������
	char chBuff[256];
	m_pNumEditBox->GetString(chBuff, 256);
	INT nMixCounts = atoi(chBuff);
	if(nMixCounts <= 0)
	{
		return;
	}
	else if(nMixCounts > COUNT_MAX_MIXING_COUNT)
	{
		nMixCounts = COUNT_MAX_MIXING_COUNT;
	}
	// end 2008-03-14 by bhsohn ���ս� ������

	int nCnt =0;
	ITEM_MIXING_INFO	stMixInfo;
	memset(&stMixInfo, 0x00, sizeof(ITEM_MIXING_INFO));
	vector<CItemInfo*>::iterator it = m_vecSource.begin();
	while(it != m_vecSource.end())
	{
		if(nCnt >= COUNT_ITEM_MIXING_SOURCE)
		{
			break;
		}
		CItemInfo* pItem = (*it);
		// ������ ��ȣ
		stMixInfo.SourceItem[nCnt].ItemNum = pItem->ItemNum;
		// ����
		if(IS_COUNTABLE_ITEM(pItem->Kind))
		{
			// 2008-03-14 by bhsohn ���ս� ������
			//stMixInfo.SourceItem[nCnt].Count = pItem->CurrentCount;			
			stMixInfo.SourceItem[nCnt].Count = pItem->CurrentCount/nMixCounts;			
		}
		else
		{
			stMixInfo.SourceItem[nCnt].Count = 1;			
		}
		nCnt++;
		it++;
	}
	stMixInfo.NumOfSourceItems = nCnt;

	ITEM_MIXING_INFO* pMixInfo = g_pDatabase->GetMixerPrice(&stMixInfo);
	if(pMixInfo)
	{		
		int nAllPrice = pMixInfo->MixingCost*nMixCounts;
		if(nAllPrice >= 0)
		{
			SetPrice(nAllPrice);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void				OnOpenInfWnd();
/// \brief		// ó�� ���� ����
/// \author		// 2008-03-14 by bhsohn ���ս� ������
/// \date		2008-03-14 ~ 2008-03-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLab::OnOpenInfWnd()
{
	char chBuff[32];
	wsprintf(chBuff, "1");
	m_pNumEditBox->SetString(chBuff, 32);
	m_pNumEditBox->EnableEdit(FALSE);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void				OnOpenInfWnd();
/// \brief		// ó�� ���� ����
/// \author		// 2008-03-14 by bhsohn ���ս� ������
/// \date		2008-03-14 ~ 2008-03-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityLab::OnCloseInfWnd()
{
	m_pNumEditBox->EnableEdit(FALSE);
}


/************************************************************************************************************************************************************
**
**	��æƮ ���� ��� �ؾ� �ϴ��� üũ.
**
**	Create Info :	2010. 09. 27. by hsLee.
**
**	Base Info : 'ITEMKIND_PREVENTION_DELETE_ITEM' - ��æƮ �ı� ���� ī��� ��æƮ Ȯ�� ���� ī��� Kind�� ���� ������ 
**				'DES_ENCHANT_INCREASE_PROBABILITY' DesParam���� ������ ����. 
**
**	Update Info : '��æƮ �ı� ���� ī��'�� '��æƮ Ȯ�� ���� ī��'�� Kind���� ���Ƽ� ��� �޽��� ���� �Ѿ�� ���� ����.	2010. 09. 27. by hsLee.
** 
*************************************************************************************************************************************************************/
bool CINFCityLab :: IsWarning_EnchantFail ( void )
{

	bool bHavePreventionDeleteItem = FALSE;
	bool bWaringEnchantLevel = FALSE;
	bool bEnableEnchant = FALSE;
	
	vector<CItemInfo*>::iterator itr_SourceItem = m_vecSource.begin();
	
	CItemInfo *pcItemInfo = NULL;
	
	while( itr_SourceItem != m_vecSource.end() )
	{
		pcItemInfo = (CItemInfo *)*itr_SourceItem;
		
		if ( pcItemInfo->Kind == ITEMKIND_PREVENTION_DELETE_ITEM && pcItemInfo->ItemInfo->GetParameterValue(DES_ENCHANT_INCREASE_PROBABILITY) == 0.0f )
		{
			bHavePreventionDeleteItem = TRUE;
		}
		
		if ( pcItemInfo->GetEnchantNumber() >= 5 )
		{
			bWaringEnchantLevel = TRUE;
		}
		
		if ( pcItemInfo->Kind == ITEMKIND_ENCHANT && !pcItemInfo->ItemInfo->IsExistDesParam ( DES_ENCHANT_INITIALIZE ) )
		{
			bEnableEnchant = TRUE;
		}
		
		itr_SourceItem++;
	}

	if ( bEnableEnchant && bWaringEnchantLevel && !bHavePreventionDeleteItem )
		return true;

	return false;

}


/**************************************************************************************
**
**	��ȿ���� ���� ���� ���� ���� �޽��� ���.
**
**	Create Info :	2010. 09. 27. by hsLee.
**
***************************************************************************************/
void CINFCityLab :: ErrorMsg_InvalidEnchantList ( char *pszMessage , const bool a_bInitData /*= true*/ )
{

	if ( pszMessage && pszMessage[0] != 0 )
		g_pD3dApp->m_pChat->CreateChatChild ( pszMessage , COLOR_ERROR ); //"�߸��� ������ �����Դϴ�."

	if ( a_bInitData )
		InitData();
}