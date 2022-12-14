// INFChangeCharactor.cpp: implementation of the CINFChangeCharactor class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "INFChangeCharactor.h"
#include "Interface.h"
#include "INFPilotFace.h"
#include "INFGameMain.h"
#include "AtumApplication.h"
#include "FieldWinSocket.h"
#include "AtumDatabase.h"
#include "INFWindow.h"
#include "D3DHanFont.h"
#include "INFIcon.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "INFCityBase.h"
#include "ItemInfo.h"
#include "INFInven.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "Chat.h"
#include "StoreData.h"
#include "dxutil.h" 
#include "AtumSound.h"
#include "CInput.h"


//--------------------------------------------------------------------------//
#define CHANGE_CHARACTOR_WINDOW_W					487
#define CHANGE_CHARACTOR_WINDOW_H					83
#define	FEMALE_RIGHT_BUTTON_X						(m_nWindowX + 438)
#define	FEMALE_RIGHT_BUTTON_Y						(m_nWindowY + 41)
#define	MALE_RIGHT_BUTTON_X							(m_nWindowX + 438)
#define	MALE_RIGHT_BUTTON_Y							(m_nWindowY + 137)
#define	FEMALE_LEFT_BUTTON_X						(m_nWindowX + 60)
#define	FEMALE_LEFT_BUTTON_Y						(m_nWindowY + 41)
#define	MALE_LEFT_BUTTON_X							(m_nWindowX + 60)
#define	MALE_LEFT_BUTTON_Y							(m_nWindowY + 137)

#define	CHARACTOR_CHANGE_BUTTON_X					(m_nWindowX + 136)
#define	CHARACTOR_CHANGE_BUTTON_Y					(m_nWindowY + 243)

#define	CHARACTOR_CANCEL_BUTTON_X					(m_nWindowX + 244)
#define	CHARACTOR_CANCEL_BUTTON_Y					(m_nWindowY + 243)

#define FEMALE_FACE_START_X							(m_nWindowX + 91)
#define FEMALE_FACE_START_Y							(m_nWindowY + 42)
#define FEMALE_NAME_START_FONT_X					(FEMALE_FACE_START_X + 32)
#define FEMALE_NAME_FONT_Y							(FEMALE_FACE_START_Y + 67)
#define MALE_FACE_START_X							(m_nWindowX + 91)
#define MALE_FACE_START_Y							(m_nWindowY + 138)
#define MALE_NAME_START_FONT_X						(MALE_FACE_START_X + 32)
#define MALE_NAME_FONT_Y							(MALE_FACE_START_Y + 67)
#define FACE_GAP_X									69


#define FEMALE_FACE_AREA_X							FEMALE_FACE_START_X
#define FEMALE_FACE_AREA_W							(FACE_GAP_X * CHARACTOR_FACE_SHOW_MAX)
#define FEMALE_FACE_AREA_Y							FEMALE_FACE_START_Y
#define MALE_FACE_AREA_X							MALE_FACE_START_X
#define MALE_FACE_AREA_W							(FACE_GAP_X * CHARACTOR_FACE_SHOW_MAX)
#define MALE_FACE_AREA_Y							MALE_FACE_START_Y
#define FACE_IMAGE_H								83


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFChangeCharactor::CINFChangeCharactor(CAtumNode * pParent)
{
	m_pParent				= pParent;

	m_pImgBG				= NULL;
	m_pImgSelect			= NULL;
	m_pFemaleRightButton	= NULL;
	m_pFemaleLeftButton		= NULL;
	m_pMaleRightButton		= NULL;
	m_pMaleLeftButton		= NULL;
	m_pChangeButton			= NULL;
	m_pCancelButton			= NULL;
	m_pFontName				= NULL;

	m_vecFaceFemale.clear();
	m_vecFaceMale.clear();

	m_nWindowX				= 0;
	m_nWindowY				= 0;
	m_nSelect				= -1;
	m_nSelectFaceNum		= 0;
	m_bFemale				= TRUE;
	m_nStartFemale			= 0;
	m_nStartMale			= 0;

	m_bActive				= FALSE;
}
CINFChangeCharactor::~CINFChangeCharactor()
{
}
HRESULT CINFChangeCharactor::InitDeviceObjects()
{
	int i;
	DataHeader	* pDataHeader;
	char buf[64];
	if(m_vecFaceFemale.size() == 0)
	{// ???? 
		FACE_IMG_NUM sFace;
		for(i = 0 ; i < CHARACTER_MALE_COUNT ; i++)
		{
			wsprintf(buf,"c%03d",i);
			pDataHeader = FindResource(buf);
			sFace.pImgFace = new CINFImage;
			sFace.pImgFace->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
			sFace.nFaceNum = i;
			GetCharactorName(sFace.szName,i);
			m_vecFaceFemale.push_back(sFace);
		}
	}
	if(m_vecFaceMale.size() == 0)
	{// ????
		FACE_IMG_NUM sFace;
		for(i = 0 ; i < CHARACTER_MALE_COUNT ; i++)
		{
			wsprintf(buf,"c%03d",i+100);
			pDataHeader = FindResource(buf);
			sFace.pImgFace = new CINFImage;
			sFace.pImgFace->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
			sFace.nFaceNum = i+100;
			GetCharactorName(sFace.szName,i+100);
			m_vecFaceMale.push_back(sFace);
		}
	}
	
	wsprintf(buf,"cchangeBG");
	pDataHeader = FindResource(buf);
	m_pImgBG = new CINFImage;
	m_pImgBG->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );
	wsprintf(buf,"csel");
	pDataHeader = FindResource(buf);
	m_pImgSelect = new CINFImage;
	m_pImgSelect->InitDeviceObjects( pDataHeader->m_pData, pDataHeader->m_DataSize );

	wsprintf(buf,"crightB");
	if(m_pFemaleRightButton == NULL)
	{
		m_pFemaleRightButton = new CINFImageBtn;
	}
	m_pFemaleRightButton->InitDeviceObjects(buf);

	wsprintf(buf,"cleftB");
	if(m_pFemaleLeftButton == NULL)
	{
		m_pFemaleLeftButton = new CINFImageBtn;
	}
	m_pFemaleLeftButton->InitDeviceObjects(buf);

	wsprintf(buf,"crightB");
	if(m_pMaleRightButton == NULL)
	{
		m_pMaleRightButton = new CINFImageBtn;
	}
	m_pMaleRightButton->InitDeviceObjects(buf);

	wsprintf(buf,"cleftB");
	if(m_pMaleLeftButton == NULL)
	{
		m_pMaleLeftButton = new CINFImageBtn;
	}
	m_pMaleLeftButton->InitDeviceObjects(buf);

	wsprintf(buf,"cchangeB");
	if(m_pChangeButton == NULL)
	{
		m_pChangeButton = new CINFImageBtn;
	}
	m_pChangeButton->InitDeviceObjects(buf);

	wsprintf(buf,"ccancel");
	if(m_pCancelButton == NULL)
	{
		m_pCancelButton = new CINFImageBtn;
	}
	m_pCancelButton->InitDeviceObjects(buf);

	if(m_pFontName == NULL)
	{
		m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, FALSE,128,32);
	}
	m_pFontName->InitDeviceObjects(g_pD3dDev);

	m_nWindowX = (g_pD3dApp->GetBackBufferDesc().Width - CHANGE_CHARACTOR_WINDOW_W)/2;
	m_nWindowY = (g_pD3dApp->GetBackBufferDesc().Height - (CHANGE_CHARACTOR_WINDOW_H*2))/2;
	return S_OK;
}
HRESULT CINFChangeCharactor::RestoreDeviceObjects()
{
	vector<FACE_IMG_NUM>::iterator it = m_vecFaceFemale.begin();
	while(it != m_vecFaceFemale.end())
	{
		it->pImgFace->RestoreDeviceObjects();
		it++;
	}
	it = m_vecFaceMale.begin();
	while(it != m_vecFaceMale.end())
	{
		it->pImgFace->RestoreDeviceObjects();
		it++;
	}
	m_pImgBG->RestoreDeviceObjects();
	m_pImgSelect->RestoreDeviceObjects();
	m_pFemaleRightButton->RestoreDeviceObjects();
	m_pFemaleRightButton->SetBtnPosition(FEMALE_RIGHT_BUTTON_X,FEMALE_RIGHT_BUTTON_Y);
	m_pFemaleLeftButton->RestoreDeviceObjects();
	m_pFemaleLeftButton->SetBtnPosition(FEMALE_LEFT_BUTTON_X,FEMALE_LEFT_BUTTON_Y);
	m_pMaleRightButton->RestoreDeviceObjects();
	m_pMaleRightButton->SetBtnPosition(MALE_RIGHT_BUTTON_X,MALE_RIGHT_BUTTON_Y);
	m_pMaleLeftButton->RestoreDeviceObjects();
	m_pMaleLeftButton->SetBtnPosition(MALE_LEFT_BUTTON_X,MALE_LEFT_BUTTON_Y);
//	// 2007-11-23 by dgwoo ???? ???????? ???? 5?? ?????????? ???? ???????? ?????? ????????????.
//	m_pFemaleRightButton->EnableBtn(FALSE);
//	m_pFemaleLeftButton->EnableBtn(FALSE);
//	m_pMaleRightButton->EnableBtn(FALSE);
//	m_pMaleLeftButton->EnableBtn(FALSE);
//	//--------------------------------------------------------------------------//
	

	m_pChangeButton->RestoreDeviceObjects();
	m_pChangeButton->SetBtnPosition(CHARACTOR_CHANGE_BUTTON_X,CHARACTOR_CHANGE_BUTTON_Y);
	m_pCancelButton->RestoreDeviceObjects();
	m_pCancelButton->SetBtnPosition(CHARACTOR_CANCEL_BUTTON_X,CHARACTOR_CANCEL_BUTTON_Y);
	m_pFontName->RestoreDeviceObjects();
	// 2009-05-11 by bhsohn ???? ???? ?????? ????
	// 2009-01-12 by bhsohn ???? ???? ????????
// #ifdef LANGUAGE_JAPAN
// 	m_pFemaleRightButton->EnableBtn(FALSE);
// 	m_pFemaleLeftButton->EnableBtn(FALSE);
// 	m_pMaleRightButton->EnableBtn(FALSE);
// 	m_pMaleLeftButton->EnableBtn(FALSE);	
// #endif
	// end 2009-01-12 by bhsohn ???? ???? ????????
	// end 2009-05-11 by bhsohn ???? ???? ?????? ????
	return S_OK;
}
HRESULT CINFChangeCharactor::DeleteDeviceObjects()
{
	vector<FACE_IMG_NUM>::iterator it = m_vecFaceFemale.begin();
	while(it != m_vecFaceFemale.end())
	{
		it->pImgFace->DeleteDeviceObjects();
		SAFE_DELETE(it->pImgFace);
		it++;

	}
	it = m_vecFaceMale.begin();
	while(it != m_vecFaceMale.end())
	{
		it->pImgFace->DeleteDeviceObjects();
		SAFE_DELETE(it->pImgFace);
		it++;
	}

	m_pImgBG->DeleteDeviceObjects();
	m_pImgSelect->DeleteDeviceObjects();
	m_pFemaleRightButton->DeleteDeviceObjects();
	m_pFemaleLeftButton->DeleteDeviceObjects();
	m_pMaleRightButton->DeleteDeviceObjects();
	m_pMaleLeftButton->DeleteDeviceObjects();
	m_pCancelButton->DeleteDeviceObjects();
	m_pChangeButton->DeleteDeviceObjects();
	m_pFontName->DeleteDeviceObjects();
	SAFE_DELETE(m_pImgBG);
	SAFE_DELETE(m_pImgSelect);	
	SAFE_DELETE(m_pFemaleRightButton);
	SAFE_DELETE(m_pFemaleLeftButton);
	SAFE_DELETE(m_pMaleRightButton);
	SAFE_DELETE(m_pMaleLeftButton);
	SAFE_DELETE(m_pCancelButton);
	SAFE_DELETE(m_pChangeButton);
	SAFE_DELETE(m_pFontName);
	return S_OK;
}
HRESULT CINFChangeCharactor::InvalidateDeviceObjects()
{
	vector<FACE_IMG_NUM>::iterator it = m_vecFaceFemale.begin();
	while(it != m_vecFaceFemale.end())
	{
		it->pImgFace->InvalidateDeviceObjects();
		it++;
	}
	it = m_vecFaceMale.begin();
	while(it != m_vecFaceMale.end())
	{
		it->pImgFace->InvalidateDeviceObjects();
		it++;
	}

	m_pImgBG->InvalidateDeviceObjects();
	m_pImgSelect->InvalidateDeviceObjects();
	m_pFemaleRightButton->InvalidateDeviceObjects();
	m_pFemaleLeftButton->InvalidateDeviceObjects();
	m_pMaleRightButton->InvalidateDeviceObjects();
	m_pMaleLeftButton->InvalidateDeviceObjects();
	m_pCancelButton->InvalidateDeviceObjects();
	m_pChangeButton->InvalidateDeviceObjects();
	m_pFontName->InvalidateDeviceObjects();
	return S_OK;
}
void CINFChangeCharactor::Render()
{
	if(!m_bActive)
	{
		return;
	}
	m_pImgBG->Move(m_nWindowX,m_nWindowY);
	m_pImgBG->Render();

	m_pFemaleRightButton->Render();
	m_pFemaleLeftButton->Render();
	m_pMaleRightButton->Render();
	m_pMaleLeftButton->Render();
	m_pCancelButton->Render();
	m_pChangeButton->Render();

	// ?????? ???? ????.
	vector<FACE_IMG_NUM>::iterator it = m_vecFaceFemale.begin();
	SIZE size;
	int i = 0;
	int nCount = 0;
	{// ???? ??????.
		while(it != m_vecFaceFemale.end())
		{
			if(m_nStartFemale <= i)
			{
				it->pImgFace->Move(FEMALE_FACE_START_X+(FACE_GAP_X * nCount),FEMALE_FACE_START_Y);
				it->pImgFace->Render();
				size = m_pFontName->GetStringSize(it->szName);
				m_pFontName->DrawText(FEMALE_NAME_START_FONT_X+(FACE_GAP_X * nCount)-(size.cx/2),FEMALE_NAME_FONT_Y,GUI_FONT_COLOR_YM,it->szName,0L);
				nCount++;
				if(nCount >= CHARACTOR_FACE_SHOW_MAX)
				{
					break;
				}
			}
			it++;
			i++;
		}
	}
	i = nCount = 0;
	it = m_vecFaceMale.begin();
	{// ???? ??????.
		while(it != m_vecFaceMale.end())
		{
			if(m_nStartMale <= i)
			{
				it->pImgFace->Move(MALE_FACE_START_X+(FACE_GAP_X * nCount),MALE_FACE_START_Y);
				it->pImgFace->Render();
				size = m_pFontName->GetStringSize(it->szName);
				m_pFontName->DrawText(MALE_NAME_START_FONT_X+(FACE_GAP_X * nCount)-(size.cx/2),MALE_NAME_FONT_Y,GUI_FONT_COLOR_YM,it->szName,0L);
				nCount++;
				if(nCount >= CHARACTOR_FACE_SHOW_MAX)
				{
					break;
				}
			}
			it++;
			i++;
		}
	}
	if(m_nSelect >= 0)
	{
		if(m_bFemale)
		{// ???? ??
			m_pImgSelect->Move(FEMALE_FACE_START_X+(FACE_GAP_X * m_nSelect),FEMALE_FACE_START_Y);
		}
		else
		{// ???? ??
			m_pImgSelect->Move(MALE_FACE_START_X+(FACE_GAP_X * m_nSelect),MALE_FACE_START_Y);
		}
		m_pImgSelect->Render();
	}

	
	
}
void CINFChangeCharactor::Tick()
{
	if(!m_bActive)
		return;
	if(!g_pD3dApp->m_bCharacter)
	{// ?????? ?????? ???????? ???? ?????? ??????.
		SetActive(FALSE);
	}
}
int CINFChangeCharactor::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(!m_bActive)
	{
		return INF_MSGPROC_NORMAL;
	}
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(m_pFemaleRightButton->OnLButtonUp(pt))
			{
				if(CHARACTER_MALE_COUNT > m_nStartFemale + CHARACTOR_FACE_SHOW_MAX)
				{
					m_nStartFemale++;	
				}
				return INF_MSGPROC_BREAK;
			}
			if(m_pFemaleLeftButton->OnLButtonUp(pt))
			{
				if(m_nStartFemale > 0)
				{
					m_nStartFemale--;
				}
				return INF_MSGPROC_BREAK;
			}
			if(m_pMaleRightButton->OnLButtonUp(pt))
			{
				if(CHARACTER_FEMALE_COUNT > m_nStartMale + CHARACTOR_FACE_SHOW_MAX)
				{
					m_nStartMale++;
				}
				return INF_MSGPROC_BREAK;
			}
			if(m_pMaleLeftButton->OnLButtonUp(pt))
			{
				if(m_nStartMale > 0)
				{
					m_nStartMale--;
				}
				return INF_MSGPROC_BREAK;
			}
			if(m_pChangeButton->OnLButtonUp(pt))
			{
				SendChangeCharactor();
				return INF_MSGPROC_BREAK;
			}
			if(m_pCancelButton->OnLButtonUp(pt))
			{
				SetActive(FALSE);
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

			if(m_pFemaleRightButton->OnLButtonDown(pt) ||
				m_pFemaleLeftButton->OnLButtonDown(pt) ||
				m_pMaleRightButton->OnLButtonDown(pt) ||
				m_pMaleLeftButton->OnLButtonDown(pt) ||
				m_pCancelButton->OnLButtonDown(pt) ||
				m_pChangeButton->OnLButtonDown(pt))
			{
				return INF_MSGPROC_BREAK;
			}
			//--------------------------------------------------------------------------//
			//    ?????? ??????.
			if(pt.x > FEMALE_FACE_AREA_X &&
				pt.x < FEMALE_FACE_AREA_X + FEMALE_FACE_AREA_W &&
				pt.y > FEMALE_FACE_AREA_Y &&
				pt.y < FEMALE_FACE_AREA_Y + FACE_IMAGE_H)
			{// ???? ????.
				m_bFemale = TRUE;
				m_nSelect = (int)((pt.x - FEMALE_FACE_AREA_X)/FACE_GAP_X);
				SetSelectFaceNum();
				return INF_MSGPROC_BREAK;
			}

			if(pt.x > MALE_FACE_AREA_X &&
				pt.x < MALE_FACE_AREA_X + MALE_FACE_AREA_W &&
				pt.y > MALE_FACE_AREA_Y &&
				pt.y < MALE_FACE_AREA_Y + FACE_IMAGE_H)
			{// ???? ????.
				m_bFemale = FALSE;
				m_nSelect = (int)((pt.x - MALE_FACE_AREA_X)/FACE_GAP_X);
				SetSelectFaceNum();
				return INF_MSGPROC_BREAK;
			}	
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			m_pFemaleRightButton->OnMouseMove(pt);
			m_pFemaleLeftButton->OnMouseMove(pt);
			m_pMaleRightButton->OnMouseMove(pt);
			m_pMaleLeftButton->OnMouseMove(pt);
			m_pCancelButton->OnMouseMove(pt);
			m_pChangeButton->OnMouseMove(pt);

		}
		break;
	}
	return INF_MSGPROC_NORMAL;

}

void CINFChangeCharactor::SendChangeCharactor()
{
	MSG_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE sMsg;
	sMsg.pilotFace				= m_nSelectFaceNum;
	sMsg.ItemUniqueNumber		= m_nUniqueNum;
	g_pFieldWinSocket->SendMsg(T_FC_ITEM_USE_CARDITEM_CHANGEPILOTFACE,(char*)&sMsg,sizeof(sMsg));
	g_pD3dApp->m_bRequestEnable = FALSE;
}
void CINFChangeCharactor::SetActive(BOOL i_bActive,UID64_t i_nUniqueNum/* = 0*/)
{ 
	m_bActive = i_bActive;
	m_nUniqueNum = i_nUniqueNum;
	if(m_bActive)
	{// ?????? ???????????? ???? ?????? ????????.
		((CINFGameMain*)m_pParent)->LeftWindowShow(TRUE,LEFT_WINDOW_WEAPON);
	}
}
void CINFChangeCharactor::SetSelectFaceNum()
{
	int nCount = 0;
	int nSelect = 0;
	if(m_nSelect >= 0)
	{
		if(m_bFemale)
		{// ????.
			nSelect = m_nSelect + m_nStartFemale;
			vector<FACE_IMG_NUM>::iterator it = m_vecFaceFemale.begin();			
			while(it != m_vecFaceFemale.end())
			{
				if(nSelect == nCount)
				{
					break;
				}
				nCount++;
				it++;
			}
			m_nSelectFaceNum = it->nFaceNum;
		}
		else
		{// ????.
			//nSelect = m_nSelect + m_nStartFemale;
			nSelect = m_nSelect + m_nStartMale;
			
			vector<FACE_IMG_NUM>::iterator it = m_vecFaceMale.begin();			
			while(it != m_vecFaceMale.end())
			{
				if(nSelect == nCount)
				{
					break;
				}
				nCount++;
				it++;
			}
			m_nSelectFaceNum = it->nFaceNum;
		}
	}
}