// INFCityInfinityShop.cpp: implementation of the CINFCityInfinityShop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "INFGameMain.h"
#include "Interface.h"
#include "AtumSound.h"
#include "D3DHanFont.h"
#include "INFCityBase.h"
#include "INFListBox.h"
#include "INFImageBtn.h"
#include "INFArenaScrollBar.h"
#include "INFEditBox.h"
#include "INFWindow.h"


#include "INFCityInfinityShop.h"
#include "AtumDatabase.h"
#include "INFIcon.h"
#include "ShuttleChild.h"
#include "StoreData.h"
#include "ItemInfo.h"

#define CITY_SHOP_START_X			(CITY_BASE_NPC_BOX_START_X+230)
#define CITY_SHOP_START_Y			(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y-9)

#define SHOP_TAB_START_X			(196+9)
#define SHOP_TAB_START_Y			33
#define SHOP_TAB_NUMBER				4
#define SHOP_ITEM_SLOT_START_X		(SHOP_TAB_START_X + 2)
#define SHOP_ITEM_SLOT_START_Y		51
#define SHOP_ITEM_SLOT_SIZE_X		253
#define SHOP_ITEM_SLOT_SIZE_Y		36
#define SHOP_ICON_START_X			(SHOP_ITEM_SLOT_START_X + 3)
#define SHOP_ICON_START_Y			53
#define SHOP_ICON_SIZE				30
#define SHOP_ITEM_SLOT_INTERVAL		36
#define SHOP_ITEM_NUMBER_X			(SHOP_TAB_START_X+210)
#define SHOP_NUMBER_BUTTON_X		(SHOP_TAB_START_X + 242)
#define SHOP_NUMBER_UP_BUTTON_Y		58
#define SHOP_NUMBER_BUTTON_SIZE_X	8
#define SHOP_NUMBER_BUTTON_SIZE_Y	7
#define SHOP_NUMBER_DOWN_BUTTON_Y	71
#define SHOP_BUY_BUTTON_START_X		(344+28)
#define SHOP_BUY_BUTTON_START_Y		70
#define SHOP_BUY_BUTTON_SIZE_X		39
#define SHOP_BUY_BUTTON_SIZE_Y		14
#define SHOP_CASH_START_X			(SHOP_TAB_START_X + 95)
#define SHOP_OK_BUTTON_START_X		(SHOP_TAB_START_X + 205)
#define SHOP_OK_BUTTON_START_Y		240
#define SHOP_OK_BUTTON_SIZE_X		35
#define SHOP_OK_BUTTON_SIZE_Y		16
#define SHOP_CANCEL_BUTTON_START_X	(SHOP_TAB_START_X + 242)
#define SHOP_CANCEL_BUTTON_START_Y	240

#define SHOP_SCROLL_START_X			(SHOP_TAB_START_X + 260)
#define SHOP_SCROLL_UP_START_Y		51
#define SHOP_SCROLL_SIZE_X			11
#define SHOP_SCROLL_SIZE_Y			12
#define SHOP_SCROLL_BAR_SIZE_Y		38
#define SHOP_SCROLL_DOWN_START_Y	217

#define SHOP_SCROLL_BAR_START_Y		65
#define SHOP_SCROLL_BAR_END_Y		215

#define SHOP_TAB_BUTTON_SIZE_X		60
#define SHOP_TAB_BUTTON_SIZE_Y		14

#define SHOP_SCROLL_LENGTH			150
#define SHOP_SCROLL_MOVE_LENGTH		(150-SHOP_SCROLL_BAR_SIZE_Y)
#define SHOP_SCROLL_NUMBER(i)		(m_vecItemInfo[i].size()<=0 ? 0:m_vecItemInfo[i].size())
#define SHOP_SCROLL_INTERVAL(i)		(SHOP_SCROLL_LENGTH / SHOP_SCROLL_NUMBER(i))

#define SHOP_ITEM_NAME_START_X		(SHOP_TAB_START_X + 46)

#define SHOP_SELL_ITEM_START_X		(227+28)
#define SHOP_SELL_ITEM_START_Y		51
#define SHOP_SELL_ITEM_END_X		(383+28)
#define SHOP_SELL_ITEM_END_Y		228

#define SHOP_TAB_B_GEAR				0
#define SHOP_TAB_I_GEAR				1
#define SHOP_TAB_M_GEAR				2
#define SHOP_TAB_A_GEAR				3

#define BOX_SIZE_X					417
#define BOX_SIZE_Y					275
#define END_OF_INVEN_X				200

#define SOURCEINDEXTOITEMNUM(i,j)	(((i/100)*100)+j)

#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)
#define SHOP_ITEM_NUMBER_Y			68
#define SHOP_CASH_START_Y			239
#define SHOP_ITEM_NAME_START_Y		51
#define SHOP_ITEM_PRICE_START_Y		68
#define FONT_TOTAL_PRICE_X			2
#define FONT_TOTAL_PRICE_Y			1
#define SHOP_TEX_X					CITY_SHOP_START_X + 420
#define SHOP_TEX_Y					CITY_SHOP_START_Y + 12
#else
#define SHOP_ITEM_NUMBER_Y			68
#define SHOP_CASH_START_Y			239
#define SHOP_ITEM_NAME_START_Y		51
#define SHOP_ITEM_PRICE_START_Y		68
#define FONT_TOTAL_PRICE_X			1
#define FONT_TOTAL_PRICE_Y			1
#define SHOP_TEX_X					CITY_SHOP_START_X + 420
#define SHOP_TEX_Y					CITY_SHOP_START_Y + 12
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityInfinityShop::CINFCityInfinityShop( CAtumNode* pParent )
{
	m_pParent			= pParent;
	
	m_nCurrentTab		= SHOP_TAB_B_GEAR;

	m_pOKButton			= NULL;

	m_pCancelButton		= NULL;
	int i;
	for( i=0; i<SHOP_TAB_NUMBER; ++i )
		m_pTab[i]	= NULL;

	m_pSlot				= NULL;
	m_pSelectSlot		= NULL;
	m_pCostBGLarge		= NULL;
	m_pCostBGSmall		= NULL;

	m_pScrollUpBtn		= NULL;
	m_pScrollDownBtn		= NULL;
	m_pScroll			= NULL;

	m_pFont				= NULL;
	m_pFontSmall		= NULL;

	for( i=0; i<SHOP_TAB_NUMBER; ++i )
	{
		m_nSelectSlot[i]	= -1;
		m_nScrollStep[i]	= 0;
	}

	m_bItemInputDone	= FALSE;
}

CINFCityInfinityShop::~CINFCityInfinityShop()
{
	DeleteDeviceObjects();
}

HRESULT CINFCityInfinityShop::InitDeviceObjects()
{
	if( m_pOKButton == NULL )
	{
		m_pOKButton	= new CINFImageBtn;
		m_pOKButton->InitDeviceObjects( "sauok3", "sauok1", "sauok0", "sauok2" );
	}

	if( m_pCancelButton == NULL )
	{
		m_pCancelButton	= new CINFImageBtn;
		m_pCancelButton->InitDeviceObjects( "shmcan03", "shmcan01", "shmcan00", "shmcan02" );
	}

	char szTemp[ 64 ];
	DataHeader*	pDataHeader;

	for( int i=0; i<4; ++i )
	{
		if( m_pTab[i] == NULL )
		{
			m_pTab[i] = new CINFImage;
			sprintf( szTemp, "stab%d", i );
			pDataHeader = FindResource( szTemp );
			m_pTab[i]->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
		}
	}

	if( m_pSlot == NULL )
	{
		m_pSlot = new CINFImage;
		pDataHeader = FindResource( "auslot" );
		m_pSlot->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	}
	
	if( m_pSelectSlot == NULL )
	{
		m_pSelectSlot = new CINFImage;
		pDataHeader = FindResource( "slosel" );
		m_pSelectSlot->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	}

	if( m_pCostBGLarge == NULL )
	{
		m_pCostBGLarge = new CINFImage;
		pDataHeader = FindResource( "if_orbbl" );
		m_pCostBGLarge->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );		
	}

	if( m_pCostBGSmall == NULL )
	{
		m_pCostBGSmall = new CINFImage;
		pDataHeader = FindResource( "if_orbbs" );
		m_pCostBGSmall->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );		
	}

	if( m_pScrollUpBtn == NULL )
	{
		m_pScrollUpBtn	= new CINFImageBtn;
		m_pScrollUpBtn->InitDeviceObjects( "c_scrlbt", "c_scrlbt", "c_scrlbt", "c_scrlbt" );
	}

	if( m_pScrollDownBtn == NULL )
	{
		m_pScrollDownBtn	= new CINFImageBtn;
		m_pScrollDownBtn->InitDeviceObjects( "c_scrlbt", "c_scrlbt", "c_scrlbt", "c_scrlbt" );
	}

	if( m_pScroll == NULL )
	{
		m_pScroll = new CINFArenaScrollBar;
		m_pScroll->InitDeviceObjects( 1, "c_scrlb" );
	}

	m_pFont = new CD3DHanFont( g_pD3dApp->GetFontStyle(), 8, D3DFONT_ZENABLE, TRUE, 1024, 32 );
	m_pFont->InitDeviceObjects( g_pD3dDev );

	m_pFontSmall = new CD3DHanFont( g_pD3dApp->GetFontStyle(), 6, D3DFONT_ZENABLE, TRUE, 1024, 32 );
	m_pFontSmall->InitDeviceObjects( g_pD3dDev );

	return S_OK;
}

HRESULT CINFCityInfinityShop::RestoreDeviceObjects()
{
	if( m_pOKButton )
		m_pOKButton->RestoreDeviceObjects();

	if( m_pCancelButton )
		m_pCancelButton->RestoreDeviceObjects();

	for( int i=0; i<4; ++i )
	{
		if( m_pTab[i] )
			m_pTab[i]->RestoreDeviceObjects();
	}

	if(	m_pSlot )
		m_pSlot->RestoreDeviceObjects();
	
	if( m_pSelectSlot )
		m_pSelectSlot->RestoreDeviceObjects();

	if( m_pCostBGLarge )
		m_pCostBGLarge->RestoreDeviceObjects();

	if( m_pCostBGSmall )
		m_pCostBGSmall->RestoreDeviceObjects();

	if( m_pScrollUpBtn )
		m_pScrollUpBtn->RestoreDeviceObjects();

	if( m_pScrollDownBtn )
		m_pScrollDownBtn->RestoreDeviceObjects();

	if( m_pScroll )
		m_pScroll->RestoreDeviceObjects();

	if( m_pFont )
		m_pFont->RestoreDeviceObjects();

	if( m_pFontSmall )
		m_pFontSmall->RestoreDeviceObjects();

	UpdateBtnPos();

	return S_OK;
}

HRESULT CINFCityInfinityShop::DeleteDeviceObjects()
{
	if( m_pOKButton )
	{
		m_pOKButton->DeleteDeviceObjects();
		SAFE_DELETE( m_pOKButton );
	}

	if( m_pCancelButton )
	{
		m_pCancelButton->DeleteDeviceObjects();
		SAFE_DELETE( m_pCancelButton );
	}

	for( int i=0; i<4; ++i )
	{
		if( m_pTab[i] )
		{
			m_pTab[i]->DeleteDeviceObjects();
			SAFE_DELETE( m_pTab[i] );
		}
	}

	if( m_pSlot )
	{
		m_pSlot->DeleteDeviceObjects();
		SAFE_DELETE( m_pSlot );
	}
	
	if( m_pSelectSlot )
	{
		m_pSelectSlot->DeleteDeviceObjects();
		SAFE_DELETE( m_pSelectSlot );
	}

	if( m_pCostBGLarge )
	{
		m_pCostBGLarge->DeleteDeviceObjects();
		SAFE_DELETE( m_pCostBGLarge );
	}

	if( m_pCostBGSmall )
	{
		m_pCostBGSmall->DeleteDeviceObjects();
		SAFE_DELETE( m_pCostBGSmall );
	}

	if( m_pScrollUpBtn )
	{
		m_pScrollUpBtn->DeleteDeviceObjects();
		SAFE_DELETE( m_pScrollUpBtn );
	}

	if( m_pScrollDownBtn )
	{
		m_pScrollDownBtn->DeleteDeviceObjects();
		SAFE_DELETE( m_pScrollDownBtn );
	}

	if( m_pScroll )
	{
		m_pScroll->DeleteDeviceObjects();
		SAFE_DELETE( m_pScroll );
	}

	if( m_pFont )
	{
		m_pFont->DeleteDeviceObjects();
		SAFE_DELETE( m_pFont );
	}

	if( m_pFontSmall )
	{
		m_pFontSmall->DeleteDeviceObjects();
		SAFE_DELETE( m_pFontSmall );
	}

	return S_OK;
}

HRESULT CINFCityInfinityShop::InvalidateDeviceObjects()
{
	if( m_pOKButton )
		m_pOKButton->InvalidateDeviceObjects();

	if( m_pCancelButton )
		m_pCancelButton->InvalidateDeviceObjects();

	for( int i=0; i<4; ++i )
	{
		if( m_pTab[i] )
			m_pTab[i]->InvalidateDeviceObjects();
	}

	if( m_pSlot )
		m_pSlot->InvalidateDeviceObjects();

	if( m_pSelectSlot )
		m_pSelectSlot->InvalidateDeviceObjects();

	if( m_pCostBGLarge )
		m_pCostBGLarge->InvalidateDeviceObjects();
	
	if( m_pCostBGSmall )
		m_pCostBGSmall->InvalidateDeviceObjects();

	if( m_pScrollUpBtn )
		m_pScrollUpBtn->InvalidateDeviceObjects();

	if( m_pScrollDownBtn )
		m_pScrollDownBtn->InvalidateDeviceObjects();
	
	if( m_pScroll )
		m_pScroll->InvalidateDeviceObjects();

	if( m_pFont )
		m_pFont->InvalidateDeviceObjects();

	if( m_pFontSmall )
		m_pFontSmall->InvalidateDeviceObjects();

	return S_OK;
}

void	CINFCityInfinityShop::UpdateBtnPos( void )
{
	m_pScroll->SetPosition( CITY_SHOP_START_X + SHOP_SCROLL_START_X,
							CITY_SHOP_START_Y + SHOP_SCROLL_UP_START_Y + 16,
							11, 110 );
	RECT rect = {
		CITY_SHOP_START_X + 205,
		CITY_SHOP_START_Y + SHOP_SCROLL_UP_START_Y,
		CITY_SHOP_START_X + 464,
		CITY_SHOP_START_Y + SHOP_SCROLL_UP_START_Y + 178
	};
	m_pScroll->SetMouseWhellRect( rect );
	rect.left	= CITY_SHOP_START_X + SHOP_SCROLL_START_X;
	rect.right	= rect.left + 11;
	rect.top	= CITY_SHOP_START_Y + SHOP_SCROLL_UP_START_Y + 12;
	rect.bottom	= rect.top + 150;
	m_pScroll->SetMouseBallRect( rect );
}

void	CINFCityInfinityShop::Render()
{
	// ??
	m_pTab[ m_nCurrentTab ]->Move( CITY_SHOP_START_X + SHOP_TAB_START_X, CITY_SHOP_START_Y + SHOP_TAB_START_Y );
	m_pTab[ m_nCurrentTab ]->Render();

	char szTemp[ 64 ];

	int nRenderCnt = 0;
	int i;
	for( i=0; i<m_vecItem[ m_nCurrentTab ].size() && nRenderCnt < SHOP_ITEM_SLOT_NUMBER; ++i )
	{
		if( i >= m_pScroll->GetScrollStep() )
		{
			// ???? ????
			if( m_nSelectSlot[ m_nCurrentTab ] != -1
				&& m_nSelectSlot[ m_nCurrentTab ] == i )
			{
				m_pSelectSlot->Move( CITY_SHOP_START_X + SHOP_ITEM_SLOT_START_X,
									 CITY_SHOP_START_Y + SHOP_ITEM_SLOT_START_Y + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt );
				m_pSelectSlot->Render();
			}
			else
			{
				m_pSlot->Move( CITY_SHOP_START_X + SHOP_ITEM_SLOT_START_X,
							   CITY_SHOP_START_Y + SHOP_ITEM_SLOT_START_Y + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt );
				m_pSlot->Render();
			}

			ITEM* pItem = g_pDatabase->GetServerItemInfo( m_vecItem[m_nCurrentTab][i].BuyItemNum );
			if( pItem )
			{
				// ?????? ??????
				sprintf( szTemp, "%08d", pItem->SourceIndex ) ;
				((CINFGameMain*)m_pParent)->m_pIcon->SetIcon( szTemp,
															  CITY_SHOP_START_X + SHOP_ICON_START_X,
															  CITY_SHOP_START_Y + SHOP_ICON_START_Y + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt + 1,
															  1.0f );
				((CINFGameMain*)m_pParent)->m_pIcon->Render();

				// ????
				m_pFont->DrawText( CITY_SHOP_START_X + SHOP_ITEM_NAME_START_X,
								   CITY_SHOP_START_Y + SHOP_ITEM_NAME_START_Y + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt,
								   GUI_FONT_COLOR,
								   pItem->ItemName );

				// ???? ????
				if( i == m_nSelectSlot[ m_nCurrentTab ] )
					sprintf( szTemp, "%3d", m_BuyInfo.ItemCount );
				else
					sprintf( szTemp, "%3d", 0 );

				m_pFont->DrawText( CITY_SHOP_START_X + SHOP_ITEM_NUMBER_X,
								   (CITY_SHOP_START_Y + SHOP_ITEM_NUMBER_Y + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt) - 1,
								   GUI_FONT_COLOR,
								   szTemp );

				// ???? ????
				for( int j=0; j<MAX_ORB_KIND; ++j )
				{
					ItemNum_t				nTradeItemNum	= 0;
					InfinityShopItemCnt_t	nTradeItemCount	= 0;

					GetOrbInfo( &(m_vecItem[m_nCurrentTab][i]), j, &nTradeItemNum, &nTradeItemCount );

					if( !nTradeItemNum )
						break;

					// ?????? ??????????
					m_pCostBGSmall->Move( CITY_SHOP_START_X + 241 + 33 * j,
										  CITY_SHOP_START_Y + 70 + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt );
					m_pCostBGSmall->Render();

					// ???? ?????? ??????
					ITEM* pTradeItem = g_pDatabase->GetServerItemInfo( nTradeItemNum );
					if( pTradeItem )
						sprintf( szTemp, "%08d", pTradeItem->SourceIndex ) ;

					((CINFGameMain*)m_pParent)->m_pIcon->SetIcon( szTemp,
																  CITY_SHOP_START_X + 242 + 33 * j,
																  CITY_SHOP_START_Y + 71 + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt,
																  0.39f );
					((CINFGameMain*)m_pParent)->m_pIcon->Render();

					// ???? ????
					itoa( nTradeItemCount, szTemp, 10 );
					m_pFontSmall->DrawText( CITY_SHOP_START_X + 262 - m_pFontSmall->GetStringSize( szTemp ).cx / 2 + 33 * j,
											CITY_SHOP_START_Y + 70 + SHOP_ITEM_SLOT_INTERVAL * nRenderCnt,
											GUI_FONT_COLOR,
											szTemp );
				}
			}

			++nRenderCnt;
		}
	}

	// ???? ???? ????
	if( m_BuyInfo.ItemNum )
	{
		for( i=0; i<m_BuyInfo.PriceInfo.size(); ++i )
		{
			// ??????????
			m_pCostBGLarge->Move( CITY_SHOP_START_X + SHOP_ICON_START_X + i * 43, CITY_SHOP_START_Y + 238 );
			m_pCostBGLarge->Render();

			// ??????
			sprintf( szTemp, "%08d", m_BuyInfo.PriceInfo[i].ItemNum );
			((CINFGameMain*)m_pParent)->m_pIcon->SetIcon( szTemp,
														  CITY_SHOP_START_X + 211 + 43 * i,
														  CITY_SHOP_START_Y + 239,
														  0.7f );
			((CINFGameMain*)m_pParent)->m_pIcon->Render();

			// ?????? ????
			sprintf( szTemp, "%d", m_BuyInfo.PriceInfo[i].ItemCount );
			m_pFont->DrawText( CITY_SHOP_START_X + 220 - m_pFont->GetStringSize( szTemp ).cx / 2 + 43 * i,
							   CITY_SHOP_START_Y + 260,
							   GUI_FONT_COLOR,
							   szTemp );
		}
	}

	m_pScrollUpBtn->SetBtnPosition( CITY_SHOP_START_X + SHOP_SCROLL_START_X,
									CITY_SHOP_START_Y + SHOP_SCROLL_UP_START_Y );
	m_pScrollUpBtn->Render();

	m_pScrollDownBtn->SetBtnPosition( CITY_SHOP_START_X + SHOP_SCROLL_START_X,
									  CITY_SHOP_START_Y + SHOP_SCROLL_DOWN_START_Y );
	m_pScrollDownBtn->Render();

	m_pScroll->SetOnlyMaxItem( m_vecItem[m_nCurrentTab].size() - SHOP_ITEM_SLOT_NUMBER + 1 < 1 ? 1 : m_vecItem[m_nCurrentTab].size() - SHOP_ITEM_SLOT_NUMBER + 1 );
	m_pScroll->Render();

	m_pOKButton->SetBtnPosition( CITY_SHOP_START_X+SHOP_OK_BUTTON_START_X, CITY_SHOP_START_Y+SHOP_OK_BUTTON_START_Y );
	m_pOKButton->Render();

	m_pCancelButton->SetBtnPosition( CITY_SHOP_START_X+SHOP_CANCEL_BUTTON_START_X, CITY_SHOP_START_Y+SHOP_CANCEL_BUTTON_START_Y );
	m_pCancelButton->Render();
}

int		CINFCityInfinityShop::WndProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !m_bItemInputDone
		|| g_pGameMain->m_pInfWindow->IsExistMsgBox( _Q_BUY_INFINITYSHOP_ITEM ) )
		return INF_MSGPROC_NORMAL;

	switch( uMsg )
	{
		case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			m_pOKButton->OnMouseMove( pt );
			m_pCancelButton->OnMouseMove( pt );

			for( int i=0; i<SHOP_ITEM_SLOT_NUMBER; ++i )
			{
				// ???? ?????? ????
				if( pt.x > CITY_SHOP_START_X+SHOP_ICON_START_X
					&& pt.x < CITY_SHOP_START_X+SHOP_ICON_START_X+SHOP_ICON_SIZE
					&& pt.y > CITY_SHOP_START_Y+SHOP_ICON_START_Y+SHOP_ITEM_SLOT_INTERVAL*i
					&& pt.y < CITY_SHOP_START_Y+SHOP_ICON_START_Y+SHOP_ITEM_SLOT_INTERVAL*i+SHOP_ICON_SIZE )
				{
					int nSelect = i + m_pScroll->GetScrollStep();
					if( nSelect >= 0
						&& nSelect < m_vecItem[ m_nCurrentTab ].size() )
					{
						ITEM* pItem = g_pDatabase->GetServerItemInfo( m_vecItem[ m_nCurrentTab ][ nSelect ].BuyItemNum );
						if( pItem )
							((CINFGameMain*)m_pParent)->SetItemInfoNormal( pItem, pt.x, pt.y, TRUE );
						else
							((CINFGameMain*)m_pParent)->SetItemInfoNormal( 0, 0, 0, TRUE );
					}
					else
					{
						((CINFGameMain*)m_pParent)->SetItemInfoNormal( 0, 0, 0, TRUE );
					}
					break;
				}
				else if( pt.x > CITY_SHOP_START_X+SHOP_ICON_START_X+SHOP_ICON_SIZE ||
					(pt.x > CITY_SHOP_START_X+END_OF_INVEN_X && pt.x < CITY_SHOP_START_X+SHOP_ICON_START_X) ||
					pt.y < CITY_SHOP_START_Y+SHOP_ICON_START_Y-5 ||
					pt.y > CITY_SHOP_START_Y+SHOP_ICON_START_Y+SHOP_ITEM_SLOT_INTERVAL*SHOP_ITEM_SLOT_NUMBER)
				{
					((CINFGameMain*)m_pParent)->SetItemInfoNormal( 0, 0, 0, TRUE );
				}

				// ???? ???? ?????? ????
				BOOL bBreak = FALSE;
				for( int j=0; j<MAX_ORB_KIND; ++j )
				{
					if( pt.x > CITY_SHOP_START_X + 242 + 33 * j
						&& pt.x < CITY_SHOP_START_X + 253 + 33 * j
						&& pt.y > CITY_SHOP_START_Y + 71 + SHOP_ITEM_SLOT_INTERVAL * i
						&& pt.y < CITY_SHOP_START_Y + 82 + SHOP_ITEM_SLOT_INTERVAL * i )
					{
						int nSelect = i + m_pScroll->GetScrollStep();
						if( nSelect >= 0
							&& nSelect < m_vecItem[ m_nCurrentTab ].size() )
						{
							ItemNum_t				nTradeItemNum	= 0;
							InfinityShopItemCnt_t	nTradeItemCount	= 0;

							GetOrbInfo( &(m_vecItem[ m_nCurrentTab ][ nSelect ]), j, &nTradeItemNum, &nTradeItemCount );

							if( nTradeItemNum )
							{
								ITEM* pItem = g_pDatabase->GetServerItemInfo( nTradeItemNum );
								if( pItem )
									((CINFGameMain*)m_pParent)->SetItemInfoNormal( pItem, pt.x, pt.y, TRUE);
								else
									((CINFGameMain*)m_pParent)->SetItemInfoNormal( 0, 0, 0, TRUE );
							}
							else
								((CINFGameMain*)m_pParent)->SetItemInfoNormal( 0, 0, 0, TRUE );

							bBreak = TRUE;
							break;
						}
					}
					else
						((CINFGameMain*)m_pParent)->SetItemInfoNormal( 0, 0, 0, TRUE );
				}

				if( bBreak )
					break;
			}

			if( m_pScroll->GetMouseMoveMode() )
			{
				m_pScroll->SetScrollPos( pt );
				return INF_MSGPROC_BREAK;
			}
		}
		break;

		case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if( m_pOKButton->OnLButtonDown( pt ) )
				return INF_MSGPROC_BREAK;

			if( m_pCancelButton->OnLButtonDown( pt ) )
				return INF_MSGPROC_BREAK;

			int i=0;
			// ?? ????
			for( i = 0; i < SHOP_TAB_NUMBER; ++i)
			{
				if( pt.x>CITY_SHOP_START_X+SHOP_TAB_START_X+SHOP_TAB_BUTTON_SIZE_X*i && 
					pt.x<CITY_SHOP_START_X+SHOP_TAB_START_X+SHOP_TAB_BUTTON_SIZE_X*(i+1) &&
					pt.y>CITY_SHOP_START_Y+SHOP_TAB_START_Y && 
					pt.y<CITY_SHOP_START_Y+SHOP_TAB_START_Y+SHOP_TAB_BUTTON_SIZE_Y)
				{
					m_nCurrentTab = i;
					m_pScroll->SetScrollStep( m_nScrollStep[ m_nCurrentTab ] );
					ClearBuyInfo();
					return INF_MSGPROC_BREAK;
				}
			}

			// ???? ???? ???? ???? ????
			if( pt.x > CITY_SHOP_START_X + SHOP_NUMBER_BUTTON_X && 
				pt.x < CITY_SHOP_START_X + SHOP_NUMBER_BUTTON_X + SHOP_NUMBER_BUTTON_SIZE_X )
			{
				for(i = 0; i<SHOP_ITEM_SLOT_NUMBER; ++i)
				{
					// 1????
					if( pt.y > CITY_SHOP_START_Y + SHOP_NUMBER_UP_BUTTON_Y + SHOP_ITEM_SLOT_INTERVAL * i
						&& pt.y < CITY_SHOP_START_Y + SHOP_NUMBER_UP_BUTTON_Y + SHOP_ITEM_SLOT_INTERVAL * i + SHOP_NUMBER_BUTTON_SIZE_Y )
					{
						int nSelect = i + m_pScroll->GetScrollStep();
						if( nSelect < m_vecItem[ m_nCurrentTab ].size()
							&& m_BuyInfo.ItemNum != 0 )
						{
							AddBuyInfo( &(m_vecItem[ m_nCurrentTab ][ nSelect ]), 1 );

							BOOL	bEnableBuy	= TRUE;
							for( std::vector<ItemPrice>::iterator it = m_BuyInfo.PriceInfo.begin();
							it != m_BuyInfo.PriceInfo.end();
							++it )
							{
								CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByItemNum( (*it).ItemNum );
								if( !pItemInfo || pItemInfo->CurrentCount < (*it).ItemCount )
								{
									bEnableBuy	= FALSE;
									break;
								}
							}

							if( !bEnableBuy )
								AddBuyInfo( &(m_vecItem[ m_nCurrentTab ][ nSelect ]), -1 );

							break;
						}
					}
					// 1????
					if( pt.y > CITY_SHOP_START_Y + SHOP_NUMBER_DOWN_BUTTON_Y + SHOP_ITEM_SLOT_INTERVAL * i
						&& pt.y < CITY_SHOP_START_Y + SHOP_NUMBER_DOWN_BUTTON_Y + SHOP_ITEM_SLOT_INTERVAL * i + SHOP_NUMBER_BUTTON_SIZE_Y )
					{
						int nSelect = i + m_pScroll->GetScrollStep();
						if( nSelect < m_vecItem[ m_nCurrentTab ].size()
							&& m_BuyInfo.ItemNum != 0 )
						{
							AddBuyInfo( &(m_vecItem[ m_nCurrentTab ][ nSelect ]), -1 );
						}
					}
				}
			}

			// ???? ?????? ?? ????
			if( m_pScroll->IsMouseWhellPos( pt ) )
			{
				RECT rect = m_pScroll->GetMouseWheelRect();
				
				int nHeight = ( rect.bottom - rect.top ) / SHOP_ITEM_SLOT_NUMBER;
				int nSelect = ( pt.y - rect.top ) / nHeight;
				if( nSelect >= SHOP_ITEM_SLOT_NUMBER )
					nSelect = SHOP_ITEM_SLOT_NUMBER - 1;

				if( m_pScroll->GetScrollStep() + nSelect == m_nSelectSlot[ m_nCurrentTab ] )
					return INF_MSGPROC_BREAK;

				if( m_pScroll->GetScrollStep() + nSelect < m_vecItem[ m_nCurrentTab ].size() )
				{
					m_nSelectSlot[ m_nCurrentTab ] = m_pScroll->GetScrollStep() + nSelect;

					ClearBuyInfo();

					m_BuyInfo.ItemNum	= m_vecItem[ m_nCurrentTab ][ m_nSelectSlot[ m_nCurrentTab ] ].BuyItemNum;
					m_BuyInfo.ItemCount	= 0;

					g_pGameMain->ChangeItemByShop( m_BuyInfo.ItemNum );
				}

				return INF_MSGPROC_BREAK;
			}

			if( m_pScroll->IsMouseBallPos( pt ) )
			{
				m_pScroll->SetMouseMoveMode( TRUE );
				return INF_MSGPROC_BREAK;
			}
		}
		break;

		case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if( m_pOKButton->OnLButtonUp( pt ) )
			{
				// 2010. 03. 08 by ckPark ???????? ???????? ???? ???????? 1?? ????
				if( !m_BuyInfo.ItemUID )
					m_BuyInfo.ItemUID	= m_vecItem[ m_nCurrentTab ][ m_nSelectSlot[ m_nCurrentTab ] ].InfinityShopUID;

				if( !m_BuyInfo.ItemNum )
					m_BuyInfo.ItemNum	= m_vecItem[ m_nCurrentTab ][ m_nSelectSlot[ m_nCurrentTab ] ].BuyItemNum;
				// end 2010. 03. 08 by ckPark ???????? ???????? ???? ???????? 1?? ????

				if( m_BuyInfo.ItemUID
					&& m_BuyInfo.ItemNum
					// 2010. 03. 08 by ckPark ???????? ???????? ???? ???????? 1?? ????
					//&& m_BuyInfo.ItemCount )
					&& m_BuyInfo.ItemCount >= 0 )
					// end 2010. 03. 08 by ckPark ???????? ???????? ???? ???????? 1?? ????
				{
					// "???????? ???? ?????????????"
					g_pGameMain->m_pInfWindow->AddMsgBox( STRMSG_C_091103_0323, _Q_BUY_INFINITYSHOP_ITEM );
				}

				return INF_MSGPROC_BREAK;
			}

			if( m_pCancelButton->OnLButtonUp( pt ) )
			{
				ClearBuyInfo();
				
				return INF_MSGPROC_BREAK;
			}

			if( m_pScrollUpBtn->OnLButtonUp( pt ) )
			{
				m_pScroll->SetScrollStep( m_pScroll->GetScrollStep() - 1 );
				m_nScrollStep[ m_nCurrentTab ] = m_pScroll->GetScrollStep();
				
				return INF_MSGPROC_BREAK;
			}

			if( m_pScrollDownBtn->OnLButtonUp( pt ) )
			{
				m_pScroll->SetScrollStep( m_pScroll->GetScrollStep() + 1 );
				m_nScrollStep[ m_nCurrentTab ] = m_pScroll->GetScrollStep();

				return INF_MSGPROC_BREAK;
			}

			if( m_pScroll->GetMouseMoveMode() )
			{
				m_pScroll->SetMouseMoveMode( FALSE );
				return INF_MSGPROC_BREAK;
			}
		}
		break;

		case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			if( m_pScroll->IsMouseWhellPos( pt ) )
			{
				m_pScroll->OnMouseWheel( wParam, lParam );
				m_nScrollStep[ m_nCurrentTab ] = m_pScroll->GetScrollStep();
				return INF_MSGPROC_BREAK;
			}
		}
		break;

		case WM_KEYDOWN:
		{
			// ?????? ???? ????
			if( m_nSelectSlot[ m_nCurrentTab ] != -1 && g_pD3dApp->m_bChatMode == FALSE )
			{
				DWORD dwCode = lParam;
				int nNumber = g_pGameMain->GetKeyDownToNumber( dwCode );
				if( nNumber != -1 )
				{
					INFINITY_SHOP_INFO*	pCurItem	= &(m_vecItem[ m_nCurrentTab ][ m_nSelectSlot[ m_nCurrentTab ] ]);

					AddBuyInfo( pCurItem, m_BuyInfo.ItemCount * 10 + nNumber - m_BuyInfo.ItemCount );

					BOOL	bEnableBuy	= TRUE;
					for( std::vector<ItemPrice>::iterator it = m_BuyInfo.PriceInfo.begin();
						 it != m_BuyInfo.PriceInfo.end();
						 ++it )
					{
						CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByItemNum( (*it).ItemNum );
						if( !pItemInfo || pItemInfo->CurrentCount < (*it).ItemCount )
						{
							bEnableBuy	= FALSE;
							break;
						}
					}

					if( !bEnableBuy )
						AddBuyInfo( pCurItem, m_BuyInfo.ItemCount / 10 - m_BuyInfo.ItemCount );
				}
				else if( wParam == VK_BACK )
				{
					if( m_BuyInfo.ItemCount > 0 )
						AddBuyInfo( &(m_vecItem[ m_nCurrentTab ][ m_nSelectSlot[ m_nCurrentTab ] ]),
									m_BuyInfo.ItemCount / 10 - m_BuyInfo.ItemCount );
				}
			}
		}
		break;
	}

	return INF_MSGPROC_NORMAL;
}

void	CINFCityInfinityShop::InitData( void )
{
	// ?????? ?????? ???? ?? ????
	if(IS_BT(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_B_GEAR;
	}
	else if(IS_OT(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_M_GEAR;
	}
	else if(IS_ST(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_I_GEAR;
	}
	else if(IS_DT(g_pD3dApp->m_pShuttleChild->m_myShuttleInfo.UnitKind))
	{
		m_nCurrentTab = SHOP_TAB_A_GEAR;
	}
	else
		m_nCurrentTab = SHOP_TAB_B_GEAR;

	for( int i=0; i<SHOP_TAB_NUMBER; ++i )
	{
		m_nSelectSlot[i]	= -1;
		m_nScrollStep[i]	= 0;
	}
	
	ClearItemInfo();
	ClearBuyInfo();

	m_bItemInputDone	= FALSE;
}

void	CINFCityInfinityShop::ClearItemInfo( void )
{
	for( int i=0; i<SHOP_ITEM_TAB_NUMBER; ++i )
		m_vecItem[i].clear();
}

void	CINFCityInfinityShop::ClearBuyInfo( void )
{
	m_BuyInfo.Clear();
}

void	CINFCityInfinityShop::GetOrbInfo( const INFINITY_SHOP_INFO* pItem, const int nIndex, ItemNum_t* pItemNum, InfinityShopItemCnt_t* pItemCount )
{
	if( nIndex < 0 || nIndex >= MAX_ORB_KIND )
	{
		*pItemNum	= 0;
		*pItemCount	= 0;
	}

	switch( nIndex )
	{
	case 0:
		*pItemNum	= pItem->TradeItemNum1;
		*pItemCount	= pItem->TradeItemCount1;
		break;
	case 1:
		*pItemNum	= pItem->TradeItemNum2;
		*pItemCount	= pItem->TradeItemCount2;
		break;
	case 2:
		*pItemNum	= pItem->TradeItemNum3;
		*pItemCount	= pItem->TradeItemCount3;
		break;
	case 3:
		*pItemNum	= pItem->TradeItemNum4;
		*pItemCount	= pItem->TradeItemCount4;
		break;
	case 4:
		*pItemNum	= pItem->TradeItemNum5;
		*pItemCount	= pItem->TradeItemCount5;
		break;
	}
}	

void	CINFCityInfinityShop::AddItemInfo( INFINITY_SHOP_INFO* pShopItem )
{
	ITEM* pItem = g_pDatabase->GetServerItemInfo( pShopItem->BuyItemNum );
	if( pItem )
	{
		if( IS_BGEAR( pItem->ReqUnitKind ) )
			m_vecItem[SHOP_TAB_B_GEAR].push_back( *pShopItem );

		if( IS_IGEAR( pItem->ReqUnitKind ) )
			m_vecItem[SHOP_TAB_I_GEAR].push_back( *pShopItem );

		if( IS_MGEAR( pItem->ReqUnitKind ) )
			m_vecItem[SHOP_TAB_M_GEAR].push_back( *pShopItem );

		if( IS_AGEAR( pItem->ReqUnitKind ) )
			m_vecItem[SHOP_TAB_A_GEAR].push_back( *pShopItem );
	}
}

void	CINFCityInfinityShop::AddBuyInfo( INFINITY_SHOP_INFO* pItem, int nCount )
{
	m_BuyInfo.ItemUID	= pItem->InfinityShopUID;

	m_BuyInfo.ItemNum	= pItem->BuyItemNum;

	m_BuyInfo.ItemCount += nCount;

	// 0???? ?????? ?????? ??????
	if( m_BuyInfo.ItemCount <= 0 )
	{
		m_BuyInfo.ItemCount = 0;
		m_BuyInfo.PriceInfo.clear();
		return;
	}

	for( int i=0; i<MAX_ORB_KIND; ++i )
	{
		ItemNum_t				nItemNum	= 0;
		InfinityShopItemCnt_t	nItemCount	= 0;

		GetOrbInfo( pItem, i, &nItemNum, &nItemCount );

		if( nItemNum )
		{
			BOOL bFind = FALSE;
			for( int j=0; j<m_BuyInfo.PriceInfo.size(); ++j )
			{
				// ???? ???? ???????? ?????? ???? ????
				if( nItemNum == m_BuyInfo.PriceInfo[j].ItemNum )
				{
					m_BuyInfo.PriceInfo[j].ItemCount += nItemCount * nCount;
					bFind = TRUE;
				}
			}

			// ???? ???? ???????? ?????? ???? ???? ????
			if( !bFind )
				m_BuyInfo.PriceInfo.push_back( ItemPrice( nItemNum, nItemCount * nCount ) );
		}
	}
}


BOOL	CINFCityInfinityShop::FindInfinityShopInfo_From_CurrentTab( ItemNum_t nItemNum, INFINITY_SHOP_INFO* pInfo )
{
	for( std::vector<INFINITY_SHOP_INFO>::iterator it = m_vecItem[m_nCurrentTab].begin();
		 it != m_vecItem[m_nCurrentTab].end();
		 ++it )
	{
		if( (*it).BuyItemNum == nItemNum )
		{
			memcpy( pInfo, &(*it), sizeof( INFINITY_SHOP_INFO ) );
			return TRUE;
		}
	}

	return FALSE;
}