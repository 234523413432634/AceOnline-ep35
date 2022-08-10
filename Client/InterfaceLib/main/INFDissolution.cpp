// INFDissolution.cpp: implementation of the CINFDissolution class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameDataLast.h"
#include "INFImage.h"
#include "INFLuckyMachine.h"
#include "AtumDatabase.h"
#include "AtumApplication.h"
#include "INFGameMain.h"
#include "INFIcon.h"
#include "ItemInfo.h"
#include "FieldWinSocket.h"
#include "INFCityBase.h"
#include "StoreData.h"
#include "Chat.h"
#include "INFInvenExtend.h"
#include "ShuttleChild.h"
#include "AtumSound.h"
#include "D3DHanFont.h"
#include "INFGameMain.h"
#include "INFWindow.h" 
#include "INFDissolution.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define DISSOLUTION_MAIN_BG_X						(CITY_BASE_NPC_BOX_START_X + 426)
#define DISSOLUTION_MAIN_BG_Y						(CITY_BASE_NPC_BOX_START_Y - 275)

#define DISSOLUTION_LOGO_X							(DISSOLUTION_MAIN_BG_X + 6)
#define DISSOLUTION_LOGO_Y							(DISSOLUTION_MAIN_BG_Y + 5)

#define DISSOLUTION_START_X							(DISSOLUTION_MAIN_BG_X + 105)
#define DISSOLUTION_START_Y							(DISSOLUTION_MAIN_BG_Y + 135)

#define DISSOLUTION_TAKE_X							(DISSOLUTION_MAIN_BG_X + 105)
#define DISSOLUTION_TAKE_Y							(DISSOLUTION_MAIN_BG_Y + 231)

#define DIS_START									0
#define DIS_ING										1
#define DIS_END										2

#define DIS_STEP_TIME								0.05

#define DIS_EFF_STEP_TIME							0.5

#define	DIS_BG_STEP_TIME							0.15

#define DIS_FADE_TIME							    0.7f


#define DIS_EFF_X									(DISSOLUTION_MAIN_BG_X + 62)
#define DIS_EFF_Y									(DISSOLUTION_MAIN_BG_Y + 0)

#define DIS_SEL_ITEM_X								(DISSOLUTION_MAIN_BG_X + 133)
#define DIS_SEL_ITEM_Y								(DISSOLUTION_MAIN_BG_Y + 71)

#define DIS_TAKE_ITEM_X								(DISSOLUTION_MAIN_BG_X + 133)
#define DIS_TAKE_ITEM_Y								(DISSOLUTION_MAIN_BG_Y + 188)

#define DIS_EFF_ITEM_X								(DIS_TAKE_ITEM_X - 10)
#define DIS_EFF_ITEM_Y								(DISSOLUTION_MAIN_BG_Y + 178)

#define DIS_EFF_ITEM_GAP_X							39

#define DIS_CARD_SIZE_W								28
#define DIS_CARD_SIZE_H								28

#define DIS_TAKE_FONT_X								(DIS_TAKE_ITEM_X + 27)
#define DIS_TAKE_FONT_Y								(DISSOLUTION_MAIN_BG_Y + 203)

CINFDissolution::CINFDissolution(CAtumNode* pParent, BUILDINGNPC* pBuilding)
{
	m_pParent = pParent;

	m_fTimeFadeInBG = 0.0f;
	m_bBoom = TRUE;

	m_bStartClick = FALSE;

	m_fTimeEffectAniBG	=	0.0f;
}

CINFDissolution::~CINFDissolution()
{
	DeleteDeviceObjects();
}


HRESULT CINFDissolution::InitDeviceObjects()
{

	m_TakeItemFont = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 8, D3DFONT_ZENABLE, TRUE, 1024, 32);
	m_TakeItemFont->InitDeviceObjects(g_pD3dDev); 
	
	DataHeader	* pDataHeader;
	
	m_pImgDissolutionBG = new CINFImage; 
	pDataHeader = FindResource("Dis_BG");
	m_pImgDissolutionBG->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	m_pImgDissolutionLogo = new CINFImage; 
	pDataHeader = FindResource("Dis_logo");
	m_pImgDissolutionLogo->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);

	// 2011. 02. 08 by jhahn 용해 배경 애니메이션 
	int i;
	for (i = 0 ; i < EFFECT_BG_MAX ; i++)
	{
		char temp[256];
		m_pImgDissolutionAniBG[i] = new CINFImage;
		
		if( i < EFFECT_BG_MAX )
		{
			wsprintf(temp,"Dis_BG%02d",i + 1);
		}
		else
		{
			wsprintf(temp,"Dis_BG%02d",EFFECT_BG_MAX - 1);			
		}
		
		pDataHeader = FindResource(temp);
		m_pImgDissolutionAniBG[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
			
	}
	// end 2011. 02. 08 by jhahn 용해 배경 애니메이션 	

	for(  i = 0; i < EFFECT_MAX + 1; i++)
	{
		char temp[256];
		m_pImgDissolutionEffect[i] = new CINFImage;
	
		if(i < EFFECT_MAX - 2)
		{
			wsprintf(temp,"Dis_Eff%02d",i + 1);
		}
		else
		{
			wsprintf(temp,"Dis_Eff%02d",EFFECT_MAX - 1);			
		}

		pDataHeader = FindResource(temp);
		m_pImgDissolutionEffect[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}

	for(i = 0; i < TAKE_EFFECT_MAX; i++)
	{
		char temp[256];
		m_pImgDissolutionTakeEffect[i] = new CINFImage;
		wsprintf(temp,"Dis_slot%d",i + 1);
		pDataHeader = FindResource(temp);
		m_pImgDissolutionTakeEffect[i]->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}
	m_pBtnStart = new CINFImageBtn;
	m_pBtnStart->InitDeviceObjects("Dis_but0");

	m_pBtnTake = new CINFImageBtn;
	m_pBtnTake->InitDeviceObjects("Dis_but1");

	m_nState = FALSE;
	m_nEffStep = NULL;
	m_fTimeEffectBG = NULL;

	m_pSelectItemInfo = NULL;
	return S_OK;
}

HRESULT CINFDissolution::RestoreDeviceObjects()
{
	if(m_TakeItemFont)
	{
		m_TakeItemFont->RestoreDeviceObjects();
	}
	m_pImgDissolutionBG->RestoreDeviceObjects();
	m_pImgDissolutionLogo->RestoreDeviceObjects();
	
	int i;
	for(i = 0; i < EFFECT_MAX; i++)
	{
		m_pImgDissolutionEffect[i]->RestoreDeviceObjects();
	}
	
	for(i = 0; i < TAKE_EFFECT_MAX; i++)
	{
		m_pImgDissolutionTakeEffect[i]->RestoreDeviceObjects();
	}


	// 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	for(i = 0; i < EFFECT_BG_MAX; i++)
	{
		m_pImgDissolutionAniBG[i]->RestoreDeviceObjects();
	}
	// end 2011. 02. 08 by jhahn 용해 배경 애니메이션 	

	m_pBtnStart->RestoreDeviceObjects();
	m_pBtnStart->SetBtnPosition(DISSOLUTION_START_X, DISSOLUTION_START_Y);

	m_pBtnTake->RestoreDeviceObjects();
	m_pBtnTake->SetBtnPosition(DISSOLUTION_TAKE_X, DISSOLUTION_TAKE_Y);

	return S_OK;
}

HRESULT CINFDissolution::DeleteDeviceObjects()
{
	if(m_TakeItemFont)
	{
		m_TakeItemFont->DeleteDeviceObjects();
		SAFE_DELETE(m_TakeItemFont);
	}

	if(m_pImgDissolutionBG)
	{
		m_pImgDissolutionBG->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgDissolutionBG);
	}
	
	if(m_pImgDissolutionLogo)
	{
		m_pImgDissolutionLogo->DeleteDeviceObjects();
		SAFE_DELETE(m_pImgDissolutionLogo);
	}
	
	
	
	int i;
	for(i = 0; i < EFFECT_MAX; i++)
	{
		if(m_pImgDissolutionEffect[i])
		{
			m_pImgDissolutionEffect[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgDissolutionEffect[i]);
		}
	}
	
	// 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	for(i = 0; i < EFFECT_BG_MAX; i++)
	{
		if(m_pImgDissolutionAniBG[i])
		{		
			m_pImgDissolutionAniBG[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgDissolutionAniBG[i]);
		}
	
	}
	// end 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	for(i = 0; i < TAKE_EFFECT_MAX; i++)
	{
		if(m_pImgDissolutionTakeEffect[i])
		{
			m_pImgDissolutionTakeEffect[i]->DeleteDeviceObjects();
			SAFE_DELETE(m_pImgDissolutionTakeEffect[i]);
		}
	}
	if(m_pBtnStart)
	{
		m_pBtnStart->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnStart);
	}

	if(m_pBtnTake)
	{
		m_pBtnTake->DeleteDeviceObjects();
		SAFE_DELETE(m_pBtnTake);
	}

	return S_OK;
}

HRESULT CINFDissolution::InvalidateDeviceObjects()
{
	if(m_TakeItemFont)
	{
		m_TakeItemFont->InvalidateDeviceObjects();
	}
	if(m_pImgDissolutionBG)
	{
		m_pImgDissolutionBG->InvalidateDeviceObjects();
	}	
	if(m_pImgDissolutionLogo)
	{
		m_pImgDissolutionLogo->InvalidateDeviceObjects();
	}		
	int i;
	for(i = 0; i < EFFECT_MAX; i++)
	{
		if(m_pImgDissolutionEffect)
		{
			m_pImgDissolutionEffect[i]->InvalidateDeviceObjects();
		}
	}	
	for(i = 0; i < TAKE_EFFECT_MAX; i++)
	{
		if(m_pImgDissolutionTakeEffect[i])
		{
			m_pImgDissolutionTakeEffect[i]->InvalidateDeviceObjects();
		}		
	}

	// 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	for(i = 0; i < EFFECT_BG_MAX; i++)
	{
		if(m_pImgDissolutionAniBG[i])
		{
			m_pImgDissolutionAniBG[i]->InvalidateDeviceObjects();
		}		
	}
	// end 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	if(m_pBtnStart)
	{
		m_pBtnStart->InvalidateDeviceObjects();
	}

	if(m_pBtnTake)
	{
		m_pBtnTake->InvalidateDeviceObjects();
	}

	return S_OK;
}
int CINFDissolution::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_pBtnTake->OnMouseMove(pt))
			{
				return INF_MSGPROC_BREAK;
			}			
			if(m_pBtnStart->OnMouseMove(pt))
			{
				return INF_MSGPROC_BREAK;
			}

			if(pt.x > DIS_SEL_ITEM_X &&
				pt.x < DIS_SEL_ITEM_X + DIS_CARD_SIZE_W &&
				pt.y > DIS_SEL_ITEM_Y &&
				pt.y < DIS_SEL_ITEM_Y + DIS_CARD_SIZE_H &&
				m_pSelectItemInfo)
			{
				g_pGameMain->SetItemInfo1(m_pSelectItemInfo,
							m_pSelectItemInfo->ItemNum, pt.x, pt.y, 0, FALSE); 
			}
			else
			{
				g_pGameMain->SetItemInfo(0,0,0,0);
			}
			
			for(int i=0; i< m_vecTakeItemInfo.size(); i++)
			{
				if(pt.x > DIS_TAKE_ITEM_X + (DIS_CARD_SIZE_W * i) + (DIS_EFF_ITEM_GAP_X * i) &&
					pt.x < DIS_TAKE_ITEM_X + (DIS_CARD_SIZE_W * i) + (DIS_EFF_ITEM_GAP_X * i) + DIS_CARD_SIZE_W &&
					pt.y > DIS_TAKE_ITEM_Y &&
					pt.y < DIS_TAKE_ITEM_Y + DIS_CARD_SIZE_H &&
					m_vecTakeItemInfo[i].i_ItemInfo)
				{
					g_pGameMain->SetItemInfo1(m_vecTakeItemInfo[i].i_ItemInfo,
						m_vecTakeItemInfo[i].i_ItemInfo->ItemNum, pt.x, pt.y, 0, FALSE);
					return INF_MSGPROC_BREAK;
				}
				else
				{
					g_pGameMain->SetItemInfo(0,0,0,0);
				}
			}
			return INF_MSGPROC_BREAK;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(m_pBtnTake->OnLButtonDown(pt))
			{
				return INF_MSGPROC_BREAK;
			}			
			if(m_pBtnStart->OnLButtonDown(pt))
			{
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

			if(m_pBtnTake->OnLButtonUp(pt))
			{ 
				PrizeItemGiveMe();
				return INF_MSGPROC_BREAK;
			}
			
			if(m_pBtnStart->OnLButtonUp(pt))
			{
				StartDissolution();
				return INF_MSGPROC_BREAK;
			}

			if(pt.x > DIS_SEL_ITEM_X &&
				pt.x < DIS_SEL_ITEM_X + DIS_CARD_SIZE_W &&
				pt.y > DIS_SEL_ITEM_Y &&
				pt.y < DIS_SEL_ITEM_Y + DIS_CARD_SIZE_H &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem &&
				((CINFGameMain*)m_pParent)->m_stSelectItem.bySelectType == ITEM_INVEN_POS)
			{
				// 2011. 02. 08 by jhahn 아이템 드래그 중 죽는 버그 수정
				//UpLoadItem(NULL);
				CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(((CINFGameMain*)m_pParent)->m_stSelectItem.pSelectItem->pItem->UniqueNumber);
				UpLoadItem(pItemInfo);
				// end 2011. 02. 08 by jhahn 아이템 드래그 중 죽는 버그 수정
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

void CINFDissolution::Render()
{
	m_pImgDissolutionBG->Move(DISSOLUTION_MAIN_BG_X, DISSOLUTION_MAIN_BG_Y);
	m_pImgDissolutionBG->Render();

	
	
	
	// 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	m_pImgDissolutionAniBG[m_nEffBgStep]->Move(DISSOLUTION_MAIN_BG_X, DISSOLUTION_MAIN_BG_Y);
	m_pImgDissolutionAniBG[m_nEffBgStep]->Render();
	// end 2011. 02. 08 by jhahn 용해 배경 애니메이션 
	

	m_pImgDissolutionLogo->Move(DISSOLUTION_LOGO_X, DISSOLUTION_LOGO_Y);
	m_pImgDissolutionLogo->Render();

	m_pBtnStart->Render();
	m_pBtnTake->Render();

	RenderItem(m_pSelectItemInfo);
	
	switch(m_nState)
	{
	case DIS_ING:
		{
			m_pImgDissolutionEffect[m_nEffStep]->Move(DIS_EFF_X, DIS_EFF_Y);
			m_pImgDissolutionEffect[m_nEffStep]->Render();
		}
		break;		
	case DIS_END:
		{
			RenderItem(m_vecTakeItemInfo);
			if(m_bBoom && !g_pGameMain->m_pInfWindow->IsExistMsgBox(_Q_DIS_BOOM))
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_100901_0402, _Q_DIS_BOOM);//"용해를 통해 아무것도 얻지 못하였습니다."
			}		
		}
		break;
	}
}

void CINFDissolution::RenderItem(CItemInfo* nSelectItem)
{
 	if(nSelectItem != NULL && 
 		nSelectItem->ItemInfo->SourceIndex != NULL)
 	{
 		CINFIcon* pIcon = ((CINFGameMain*)m_pParent)->m_pIcon;
  		char buf[20];
  		wsprintf(buf, "%08d",nSelectItem->ItemInfo->SourceIndex);
 		pIcon->SetIcon( buf, DIS_SEL_ITEM_X, DIS_SEL_ITEM_Y, 1.0f );
 		pIcon->Render();
  	}

}

void CINFDissolution::RenderItem(vector<DIS_ITEM_INFO> vecTakeItem)
{
 	CINFIcon* pIcon = ((CINFGameMain*)m_pParent)->m_pIcon;

	if(vecTakeItem.size() != NULL && m_nState == DIS_END && m_bBoom == FALSE)
	{
	 	for(int i=0 ; i < vecTakeItem.size(); i++)
	 	{
	 		char buf[20], buf2[20];
	 		wsprintf(buf, "%08d",vecTakeItem[i].i_ItemInfo->GetItemInfo()->SourceIndex);
	 		pIcon->SetIcon( buf, DIS_TAKE_ITEM_X + (DIS_CARD_SIZE_W * i) + (DIS_EFF_ITEM_GAP_X * i), DIS_TAKE_ITEM_Y, 1.0f );

			DWORD imagecolor = ((CINFGameMain*)m_pParent)->GetCurrentColor(m_fTimeFadeInBG,ALPHA_FADE_IN, DIS_FADE_TIME);
			CINFImage*  TempImage = new CINFImage;
			memcpy(TempImage,pIcon->FindIcon(buf),sizeof(CINFImage));

			TempImage->SetColor(imagecolor);
			TempImage->Move(DIS_TAKE_ITEM_X + (DIS_CARD_SIZE_W * i) + (DIS_EFF_ITEM_GAP_X * i), DIS_TAKE_ITEM_Y);
			TempImage->Render();
			SAFE_DELETE(TempImage);

			CItemInfo* TakeItem = g_pStoreData->FindItemInInventoryByUniqueNumber(m_vecTakeItemInfo[i].i_ItemInfo->UniqueNumber);
			if(TakeItem)
			{
				itoa(m_vecTakeItemInfo[i].i_count - TakeItem->CurrentCount ,buf2, 10);
			}
			else
			{
				itoa(m_vecTakeItemInfo[i].i_count,buf2, 10);
					
			}

			m_TakeItemFont->DrawText(DIS_TAKE_FONT_X + (DIS_CARD_SIZE_W * i) + (DIS_EFF_ITEM_GAP_X * i) - m_TakeItemFont->GetStringSize(buf2).cx,
										DIS_TAKE_FONT_Y,
										GUI_FONT_COLOR,
										buf2);
			m_pImgDissolutionTakeEffect[m_nEffStep]->Move(DIS_EFF_ITEM_X + (DIS_CARD_SIZE_W * i) + (DIS_EFF_ITEM_GAP_X * i) , DIS_EFF_ITEM_Y);
			m_pImgDissolutionTakeEffect[m_nEffStep]->Render();

	 	}
	}
}

void CINFDissolution::Tick()
{
	m_fTimeEffectBG += g_pD3dApp->GetElapsedTime();

	// 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	m_fTimeEffectAniBG += g_pD3dApp->GetElapsedTime();
	if(m_fTimeEffectAniBG >= DIS_BG_STEP_TIME)
	{
		m_fTimeEffectAniBG = NULL;
		m_nEffBgStep += 1;
		if (m_nEffBgStep >= EFFECT_BG_MAX)
		{
			m_nEffBgStep = NULL;
		}

	}	
	// end 2011. 02. 08 by jhahn 용해 배경 애니메이션 	
	switch(m_nState)
	{
	case DIS_START:
		{
			if(m_nEffStep != NULL)
			{
				ResetInfo();
			}
		}
		break;
	case DIS_ING:
		{
			if(m_fTimeEffectBG >= DIS_STEP_TIME)
			{
				m_nEffStep += 1;
				m_fTimeEffectBG = NULL;
				if(m_nEffStep >= EFFECT_MAX)
				{
					m_nState = DIS_END;
					m_nEffStep = NULL;
					SAFE_DELETE(m_pSelectItemInfo);
				}
			}
		}
		break;
	case DIS_END:
		{
			m_fTimeFadeInBG += g_pD3dApp->GetElapsedTime();
			if(m_fTimeEffectBG >= DIS_EFF_STEP_TIME && m_bBoom == FALSE)
			{
				m_fTimeEffectBG = NULL;
				m_nEffStep += 1;
				if(m_nEffStep >= TAKE_EFFECT_MAX)
				{
					m_nEffStep = NULL;
				}
			}
		}
		break;
	}
}

BOOL CINFDissolution::IsCloseDissolution()
{
	if(m_nState == DIS_ING)
	{
		return FALSE;
	}
	PrizeItemGiveMe();

	return TRUE;
}

void CINFDissolution::EnterDissolutionShop()
{
	g_pGameMain->ShowShopInven(BUILDINGKIND_DISSOLUTION, FALSE);
}

void CINFDissolution::OnCloseInfWnd()
{
	ResetInfo();
}

void CINFDissolution::UpLoadItem(CItemInfo* i_pItem)
{
	if(i_pItem == NULL &&
	    m_nState == DIS_START &&
	    !g_pGameMain->m_stSelectItem.pSelectItem &&
	    !g_pGameMain->m_stSelectItem.pSelectItem->pItem)
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100901_0403,COLOR_ERROR);//"\\y용해할 아이템이 없습니다.\\y"
		return;
	}

	if(m_nState != DIS_START)
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100901_0403,COLOR_ERROR);//"\\y용해가 진행중입니다.\\y"
		return;
	}
	// 2011. 02. 08 by jhahn 아이템 드래그 중 죽는 버그 수정
	if(g_pDatabase->Is_DissolutionitemInfo(i_pItem->ItemNum) == FALSE)
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100421_0401,COLOR_ERROR);//"\\y올려 놓을 수 없습니다.\\y"
		return;
	}
	// end 2011. 02. 08 by jhahn 아이템 드래그 중 죽는 버그 수정
	
	if(g_pGameMain->m_stSelectItem.pSelectItem &&
		g_pGameMain->m_stSelectItem.pSelectItem->pItem &&
		NULL == i_pItem)
	{
		m_pSelectItemInfo = new CItemInfo((CItemInfo*)g_pGameMain->m_stSelectItem.pSelectItem->pItem);
		m_pSelectItemInfo->CopyItemInfo((CItemInfo*)g_pGameMain->m_stSelectItem.pSelectItem->pItem);
	}
	else if(m_pSelectItemInfo == NULL)
	{
		m_pSelectItemInfo = new CItemInfo(i_pItem);
		m_pSelectItemInfo->CopyItemInfo(i_pItem);
	}
	else
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100901_0406,COLOR_ERROR);//"\\y용해할 아이템이 올려져 있습니다.\\y"
		return;
	}

	if(IS_COUNTABLE_ITEM(m_pSelectItemInfo->Kind))
	{
		m_pSelectItemInfo->CurrentCount = 1;
		g_pStoreData->UpdateItemCount(i_pItem->UniqueNumber, i_pItem->CurrentCount - m_pSelectItemInfo->CurrentCount);
	}
	else
	{
		g_pStoreData->DeleteItem( m_pSelectItemInfo->UniqueNumber );
	}
}

void CINFDissolution::StartDissolution()
{
	if(m_pSelectItemInfo && m_bStartClick == FALSE)
	{
 		MSG_FC_DISSOLVED_ITEM msg;
		memset( &msg, 0, sizeof( MSG_FC_DISSOLVED_ITEM ) );

		msg.UniqueNumber = m_pSelectItemInfo->UniqueNumber;
		msg.Itemnum = m_pSelectItemInfo->ItemNum;
		m_bStartClick = TRUE;		
		g_pFieldWinSocket->SendMsg( T_FC_DISSOLVED_ITEM, (char*)(&msg), sizeof( MSG_FC_DISSOLVED_ITEM ) );	

		// 2011-03-08 by jhahn 용해 사운드
		g_pD3dApp->m_pSound->PlayD3DSound(SOUND_DISSOLUTION, D3DXVECTOR3(0,0,0), FALSE);
		// end 2011-03-08 by jhahn 용해 사운드
	}
	else if(m_nState != DIS_START)
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100901_0403,COLOR_ERROR);//"\\y용해가 진행중입니다.\\y"
	}
	else
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100901_0404,COLOR_ERROR);//"\\y용해할 아이템이 없습니다.\\y"
	}
}

void CINFDissolution::PrizeItemGiveMe()
{
	if(m_nState == DIS_START)
	{
		if(m_pSelectItemInfo)
		{
			ITEM_GENERAL itemGeneral;
 			itemGeneral = (ITEM_GENERAL)(*m_pSelectItemInfo);
 			itemGeneral.ItemWindowIndex = POS_INVALID_POSITION;
 			g_pStoreData->PutItem((char*)&itemGeneral, TRUE);

			// 2011-03-25 by hsson 인첸된 무기, 아머를 옵션머신 돌린 후 받았을 경울 인첸이 사라지는 버그 수정
			g_pStoreData->FindItemInInventoryByUniqueNumber(m_pSelectItemInfo->UniqueNumber)->CopyItemInfo(m_pSelectItemInfo);
			// end 2011-03-25 by hsson 인첸된 무기, 아머를 옵션머신 돌린 후 받았을 경울 인첸이 사라지는 버그 수정

			ResetInfo();
		}
		else
		{
			// 2011-11-23 by hsson 용해상점에서 Esc누르면 나오는 안내 메시지 제거
			//g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100901_0405,COLOR_ERROR);//"\\y받을 아이템이 없습니다.\\y"
			// end 2011-11-23 by hsson 용해상점에서 Esc누르면 나오는 안내 메시지 제거
			ResetInfo();
		}		
	}
	else if(m_nState == DIS_ING)
	{
		g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_100901_0403, COLOR_SYSTEM); //"\\y용해가 진행중입니다.\\y"
	}
	else if(m_nState == DIS_END)
	{
		for(int i=0; i < m_vecTakeItemInfo.size(); i++)
		{
			CItemInfo* TakeItem = g_pStoreData->FindItemInInventoryByUniqueNumber(m_vecTakeItemInfo[i].i_ItemInfo->UniqueNumber);
			if(IS_COUNTABLE_ITEM(m_vecTakeItemInfo[i].i_ItemInfo->Kind) && TakeItem != NULL)
			{
				char buf[256];
				wsprintf(buf,STRMSG_C_081124_0103,TakeItem->GetItemInfo()->ItemName, m_vecTakeItemInfo[i].i_count - TakeItem->CurrentCount); //"%s아이템  %d개 획득"	 
				g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);

				int aa= m_vecTakeItemInfo[i].i_count;
				g_pStoreData->UpdateItemCount(TakeItem->UniqueNumber, m_vecTakeItemInfo[i].i_count);
			}	
			else
			{
				ITEM_GENERAL itemGeneral;
				memset(&itemGeneral,0x00,sizeof(ITEM_GENERAL));

				itemGeneral = (ITEM_GENERAL)(*m_vecTakeItemInfo[i].i_ItemInfo);
				itemGeneral.ItemWindowIndex = POS_INVALID_POSITION;
				itemGeneral.CurrentCount = m_vecTakeItemInfo[i].i_count;
				g_pStoreData->PutItem((char*)&itemGeneral, TRUE);

				char buf[256];
				wsprintf(buf,STRMSG_C_081124_0103,itemGeneral.ItemInfo->ItemName,itemGeneral.CurrentCount); //"%s아이템  %d개 획득"	 
				g_pD3dApp->m_pChat->CreateChatChild(buf,COLOR_ERROR);
			}
		}
		ResetInfo();
	}
}

void CINFDissolution::ResetInfo()
{
	m_nEffStep	= NULL;
	m_nState	= DIS_START;
	m_bBoom		= TRUE;
	m_bStartClick = FALSE;

	m_fTimeFadeInBG = NULL;
	m_fTimeEffectBG	= NULL;
	m_nEffStep = NULL;

	m_pSelectItemInfo = NULL;
	m_vecTakeItemInfo.clear();

	g_pShuttleChild->ResortingItem();// 여기
	if(g_pGameMain && g_pGameMain->m_pInven)
	{
		g_pGameMain->m_pInven->SetScrollEndLine();				// 2006-06-21 by ispark
		g_pGameMain->m_pInven->SetAllIconInfo();
	}
	g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_DIS_BOOM);
}	

void CINFDissolution::SetTakeItem( ITEM_GENERAL i_Item )
{
	DIS_ITEM_INFO disItem;
	memset(&disItem, 0x00, sizeof(DIS_ITEM_INFO));
	CItemInfo* TakeInfo = new CItemInfo(&i_Item);
			
	if(TakeInfo != NULL)
	{
		disItem.i_ItemInfo = TakeInfo;
		disItem.i_count = TakeInfo->CurrentCount;

		m_vecTakeItemInfo.push_back( disItem ); 
	}
 }

void CINFDissolution::SetTakeItem(MSG_FC_TRADE_UPDATE_ITEM_COUNT * pMsg)
{
	CItemInfo* TakeInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(pMsg->ItemUniqueNumber);

	DIS_ITEM_INFO disItem;
	memset(&disItem, 0x00, sizeof(DIS_ITEM_INFO));

	if(TakeInfo)
	{
		disItem.i_ItemInfo = TakeInfo;
		disItem.i_count = pMsg->NewCount;

		m_vecTakeItemInfo.push_back( disItem ); 
	}
}

void CINFDissolution::SetDeleteItem(const UID64_t a_ItemUniqueNumber)
{
	if(m_pSelectItemInfo->UniqueNumber == a_ItemUniqueNumber)
	{
		SAFE_DELETE(m_pSelectItemInfo);
	}
}