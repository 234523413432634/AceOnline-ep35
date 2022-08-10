// INFArenaScrollBar.cpp: implementation of the CINFArenaScrollBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFImage.h"
#include "GameDataLast.h"
#include "INFGameMain.h"

#include "INFArenaScrollBar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFArenaScrollBar::CINFArenaScrollBar()
{
	m_pScrollButton = NULL;
	m_pScrollBk = NULL;
	m_fScrollPosX = m_fScrollPosY = 0;
	m_fScrollBallPosX = m_fScrollBallPosY = 0;

	m_fScrollWidth = m_fScrollHeight = m_nOneStep= m_nMaxStepCnt= 1;
	m_nScrollPos = 0;
	m_nScrollStep = 0;

	memset(&m_rcMouseWhell, 0x00, sizeof(RECT));
	memset(&m_rcMouseBall, 0x00, sizeof(RECT));
	m_bMouseMode = FALSE;

	m_rcBallRender.left = 0;
	m_rcBallRender.top = 0;
	m_rcBallRender.right = 1;
	m_rcBallRender.bottom =1;

	m_bBallRender = TRUE;
}

CINFArenaScrollBar::~CINFArenaScrollBar()
{
	if(m_pScrollButton)
	{
		m_pScrollButton->DeleteDeviceObjects();
		SAFE_DELETE(m_pScrollButton);
	}
	if(m_pScrollBk)
	{
		m_pScrollBk->DeleteDeviceObjects();
		SAFE_DELETE(m_pScrollBk);
	}
}

HRESULT CINFArenaScrollBar::InitDeviceObjects(int i_nOneStepCnt,char* i_pszScrollBk, char* i_pszScrollBtn)
{
	DataHeader	* pDataHeader = NULL;	
	
	m_nOneStep			= i_nOneStepCnt;	
	m_nMaxStepCnt		= i_nOneStepCnt;
	m_nScrollPos = 0;
	
	{
		if(NULL == m_pScrollButton)
		{
			m_pScrollButton = new CINFImage;
		}		
		pDataHeader = g_pGameMain->FindResource(i_pszScrollBtn);
		m_pScrollButton->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}
	
	{
		if(NULL == m_pScrollBk)
		{
			m_pScrollBk = new CINFImage;
		}		
		pDataHeader = g_pGameMain->FindResource(i_pszScrollBk);
		m_pScrollBk->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}	
	return S_OK ;
}
HRESULT CINFArenaScrollBar::InitDeviceObjects(int i_nOneStepCnt, char* i_pszScrollBtn)
{
	DataHeader	* pDataHeader = NULL;	
	
	m_nOneStep			= i_nOneStepCnt;	
	m_nMaxStepCnt		= i_nOneStepCnt;
	m_nScrollPos = 0;
	
	{
		if(NULL == m_pScrollButton)
		{
			m_pScrollButton = new CINFImage;
		}		
		pDataHeader = g_pGameMain->FindResource(i_pszScrollBtn);
		m_pScrollButton->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}
	
	return S_OK ;
}

void CINFArenaScrollBar::SetMaxItem(int i_nMaxItem)
{
	// 스크롤볼 위치 초기화
	m_fScrollBallPosX	= m_fScrollPosX;
	m_fScrollBallPosY	= m_fScrollPosY;

	m_nMaxStepCnt = i_nMaxItem; 
	m_nScrollStep = 0;
}

// 2007-06-12 by bhsohn 미션 인터페이스 수정안
// 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
//void CINFArenaScrollBar::SetOnlyMaxItem(int i_nMaxItem)
void CINFArenaScrollBar::SetOnlyMaxItem(int i_nMaxItem , BOOL IsPosX /* = FALSE */)
//end 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
{
	m_nMaxStepCnt = i_nMaxItem;

	int nExtendItem = m_nMaxStepCnt - m_nOneStep;
	if(nExtendItem < 1)
	{
		nExtendItem = 1;
		m_nScrollStep = 0;
	}
	
	m_nScrollStep = max(0,m_nScrollStep);
	m_nScrollStep = min(m_nScrollStep, nExtendItem);
	
	// 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
	//float fOneStepPixel = m_fScrollHeight/nExtendItem;
	//m_fScrollBallPosY = m_fScrollPosY + (fOneStepPixel*m_nScrollStep);
	if(!IsPosX)
	{
		float fOneStepPixel = m_fScrollHeight/nExtendItem;
		m_fScrollBallPosY = m_fScrollPosY + (fOneStepPixel*m_nScrollStep);
	}
	else
	{
		float fOneStepPixel = m_fScrollWidth/nExtendItem;
		m_fScrollBallPosX = m_fScrollBallPosX + (fOneStepPixel*m_nScrollStep);
	}
	//end 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
	//DBGOUT("m_fScrollBallPosY[%.2f] fOneStepPixel[%.2f] m_nScrollStep[%d] \n", m_fScrollBallPosY, fOneStepPixel, m_nScrollStep);
}

HRESULT CINFArenaScrollBar::RestoreDeviceObjects()
{
	m_pScrollButton->RestoreDeviceObjects();
	POINT ptSize = m_pScrollButton->GetImgSize();
	
	m_rcBallRender.left = 0;
	m_rcBallRender.top = 0;
	m_rcBallRender.right = ptSize.x;
	m_rcBallRender.bottom = ptSize.y;


	if(m_pScrollBk)
		m_pScrollBk->RestoreDeviceObjects();
	return S_OK ;
}

HRESULT CINFArenaScrollBar::DeleteDeviceObjects()
{
	m_pScrollButton->DeleteDeviceObjects();	
	SAFE_DELETE(m_pScrollButton);
	if(m_pScrollBk)
	{
		m_pScrollBk->DeleteDeviceObjects();	
		SAFE_DELETE(m_pScrollBk);
	}
	return S_OK ;
}

HRESULT CINFArenaScrollBar::InvalidateDeviceObjects()
{
	m_pScrollButton->InvalidateDeviceObjects();
	if(m_pScrollBk)
		m_pScrollBk->InvalidateDeviceObjects();
	return S_OK ;
}

void CINFArenaScrollBar::SetPosition(float i_fPosX, float i_fPosY,float i_fWidth, float i_fHeight)
{
	m_fScrollPosX		= i_fPosX;
	m_fScrollPosY		= i_fPosY;
	m_fScrollWidth		= i_fWidth;
	m_fScrollHeight		= i_fHeight;

	m_fScrollBallPosX	= m_fScrollPosX;
	m_fScrollBallPosY	= m_fScrollPosY;
	
	// 2008-08-22 by bhsohn EP3 인벤토리 처리
	// 위치 재갱신
	int nExtendItem = m_nMaxStepCnt - m_nOneStep;
	if(nExtendItem > 0)
	{
		float fOneStepPixel = m_fScrollHeight/nExtendItem;
		m_fScrollBallPosY = m_fScrollPosY + (fOneStepPixel*m_nScrollStep);
	}
	// end 2008-08-22 by bhsohn EP3 인벤토리 처리

}

void CINFArenaScrollBar::Render()
{
	// 배경
	if(m_pScrollBk)
	{
		m_pScrollBk->Move(m_fScrollPosX, m_fScrollPosY);
		m_pScrollBk->Render();	
	}

	// 위치
	if(m_bBallRender)
	{
		m_pScrollButton->Move(m_fScrollBallPosX, m_fScrollBallPosY);
		m_pScrollButton->SetRect(m_rcBallRender.left, m_rcBallRender.top, m_rcBallRender.right, m_rcBallRender.bottom);
		m_pScrollButton->Render();	
	}
	
}

void CINFArenaScrollBar::Tick()
{
	
}

void CINFArenaScrollBar::SetMouseWhellRect(RECT rcMouse)
{
	m_rcMouseWhell = rcMouse;
}

// 휠 인식 위치냐
BOOL CINFArenaScrollBar::IsMouseWhellPos(POINT ptPos)
{
	if((m_rcMouseWhell.left <= ptPos.x) &&(ptPos.x <= m_rcMouseWhell.right))		
	{
		if((m_rcMouseWhell.top <= ptPos.y)	&&(ptPos.y <= m_rcMouseWhell.bottom ))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CINFArenaScrollBar::SetMouseBallRect(RECT rcMouse)
{
	m_rcMouseBall = rcMouse;
}

// 볼 인식 위치냐
BOOL CINFArenaScrollBar::IsMouseBallPos(POINT ptPos)
{
	POINT ptBall = m_pScrollButton->GetImgSize();
	float fMaxX,fMaxY;

	fMaxX = m_fScrollBallPosX + ptBall.x;
	fMaxY = m_fScrollBallPosY + ptBall.y;

	if((m_fScrollBallPosX <= ptPos.x) &&(ptPos.x <= fMaxX))		
	{
		if((m_fScrollBallPosY <= ptPos.y) &&(ptPos.y <= fMaxY))
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 스크롤 인식 위치냐
BOOL CINFArenaScrollBar::IsMouseScrollPos(POINT ptPos)
{
	if((m_rcMouseBall.left <= ptPos.x) &&(ptPos.x <= m_rcMouseBall.right))		
	{
		if((m_rcMouseBall.top <= ptPos.y)	&&(ptPos.y <= m_rcMouseBall.bottom ))
		{
			return TRUE;
		}
	}

	return FALSE;
}


int CINFArenaScrollBar::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	int nExtendItem = m_nMaxStepCnt - m_nOneStep;
	if(nExtendItem <= 0)
	{
		return 0;
	}
	if((int)wParam<0)
	{
		m_nScrollStep ++;
	}
	else
	{
		m_nScrollStep--;
	}
	
	m_nScrollStep = max(0,m_nScrollStep);
	m_nScrollStep = min(m_nScrollStep, nExtendItem);

	float fOneStepPixel = m_fScrollHeight/nExtendItem;
	
	m_fScrollBallPosY = m_fScrollPosY + (fOneStepPixel*m_nScrollStep);

	return m_nScrollStep;
}
void CINFArenaScrollBar::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{

}

int CINFArenaScrollBar::GetScrollStep()
{
	return m_nScrollStep;
}

void CINFArenaScrollBar::SetScrollStep(int nStep)
{
	m_nScrollStep = nStep;
	
	int nExtendItem = m_nMaxStepCnt - m_nOneStep;
	if(nExtendItem <= 1)
	{
		nExtendItem = 1;		
	}

	float fOneStepPixel = m_fScrollHeight/nExtendItem;
	m_fScrollBallPosY = m_fScrollPosY + (fOneStepPixel*m_nScrollStep);
	
}

void CINFArenaScrollBar::SetMouseMoveMode(BOOL bMode)
{
	m_bMouseMode = bMode;
}
BOOL CINFArenaScrollBar::GetMouseMoveMode()
{
	return m_bMouseMode;
}
// 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
//void CINFArenaScrollBar::SetScrollPos(POINT i_ptPos)
void CINFArenaScrollBar::SetScrollPos(POINT i_ptPos, BOOL IsPosX /* = FALSE */)
//end 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
{
	int nExtendItem = m_nMaxStepCnt - m_nOneStep;
	if(nExtendItem <= 0)
	{
		return;
	}
	POINT ptBall	= m_pScrollButton->GetImgSize();
	POINT ptBk;
	// 2007-05-15 by bhsohn 스크롤 관련 버그 수정
	if(m_pScrollBk)
	{
		ptBk		= m_pScrollBk->GetImgSize();
	}
	else
	{
		ptBk.x		= m_fScrollWidth;
		ptBk.y		= m_fScrollHeight;
	}
	
	// 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
// 	m_fScrollBallPosY = i_ptPos.y - ptBall.y/2;	 
// 	
// 	float fOneStepPixel = m_fScrollHeight/nExtendItem;
// 	m_fScrollBallPosY = max(m_fScrollPosY,m_fScrollBallPosY);
// 	m_fScrollBallPosY = min(m_fScrollBallPosY, m_fScrollPosY+(nExtendItem*fOneStepPixel));
// 	
// 	
// 	float fMinDiff = ptBk.y;
// 	int nCnt, nSelStep;
// 	float fY, fTmpY;
// 	nCnt = nSelStep = 0;
// 	fY = fTmpY = 0;
// 	
// 	// 2007-05-15 by bhsohn 스크롤 관련 버그 수정
// 	for(nCnt = 0;nCnt <= nExtendItem;nCnt++)
// 	{
// 		fY = m_fScrollPosY + (fOneStepPixel*nCnt);
// 		fTmpY = abs(i_ptPos.y - fY);
// 		if(fMinDiff > fTmpY)
// 		{
// 			fMinDiff = fTmpY;
// 			nSelStep = nCnt;
// 		}
// 	}
// 	m_nScrollStep = nSelStep;
// 	m_nScrollStep = min(m_nScrollStep, nExtendItem);
	if(!IsPosX)
	{
		m_fScrollBallPosY = i_ptPos.y - ptBall.y/2;	 
		
		float fOneStepPixel = m_fScrollHeight/nExtendItem;
		m_fScrollBallPosY = max(m_fScrollPosY,m_fScrollBallPosY);
		m_fScrollBallPosY = min(m_fScrollBallPosY, m_fScrollPosY+(nExtendItem*fOneStepPixel));
		
		
		float fMinDiff = ptBk.y;
		int nCnt, nSelStep;
		float fY, fTmpY;
		nCnt = nSelStep = 0;
		fY = fTmpY = 0;
		
		// 2007-05-15 by bhsohn 스크롤 관련 버그 수정
		for(nCnt = 0;nCnt <= nExtendItem;nCnt++)
		{
			fY = m_fScrollPosY + (fOneStepPixel*nCnt);
			fTmpY = abs(i_ptPos.y - fY);
			if(fMinDiff > fTmpY)
			{
				fMinDiff = fTmpY;
				nSelStep = nCnt;
			}
		}
		m_nScrollStep = nSelStep;
		m_nScrollStep = min(m_nScrollStep, nExtendItem);
	}
	else
	{
		m_fScrollBallPosX = i_ptPos.x - ptBall.x/2;	 
		
		float fOneStepPixel = m_fScrollWidth/nExtendItem;
		m_fScrollBallPosX = max(m_fScrollPosX,m_fScrollBallPosX);
		m_fScrollBallPosX = min(m_fScrollBallPosX, m_fScrollPosX+(nExtendItem*fOneStepPixel));
				
		float fMinDiff = ptBk.x;
		int nCnt, nSelStep;
		float fX, fTmpX;
		nCnt = nSelStep = 0;
		fX = fTmpX = 0;
		
		// 2007-05-15 by bhsohn 스크롤 관련 버그 수정
		for(nCnt = 0;nCnt <= nExtendItem;nCnt++)
		{
			fX = m_fScrollPosX + (fOneStepPixel*nCnt);
			fTmpX = abs(i_ptPos.x - fX);
			if(fMinDiff > fTmpX)
			{
				fMinDiff = fTmpX;
				nSelStep = nCnt;
			}
		}
		m_nScrollStep = nSelStep;
		m_nScrollStep = min(m_nScrollStep, nExtendItem);
	}
	//end 2010. 06. 07 by jskim 파트너 시스템 구현 - 스크롤바 X이동 구현
}

POINT CINFArenaScrollBar::GetImgBkSize()
{
	// 2007-06-12 by bhsohn 미션 인터페이스 수정안
	// 이미지가 없을시 
	if(NULL == m_pScrollBk)
	{
		POINT ptSize;
		ptSize.x = m_fScrollWidth;
		ptSize.y = m_fScrollHeight;
		return ptSize;
	}

	return m_pScrollBk->GetImgSize();
}


void CINFArenaScrollBar::SetBallRenderHeight(int nPosY)
{
	if(NULL == m_pScrollButton)
	{
		return;
	}	
	if(nPosY < 0)
	{
		m_bBallRender = FALSE;
		return;
	}
	POINT ptSize = m_pScrollButton->GetImgSize();	
	if(nPosY > ptSize.y)
	{
		nPosY = ptSize.y;
	}

	m_bBallRender = TRUE;
	m_rcBallRender.top = 0;
	m_rcBallRender.bottom = nPosY;
}

int CINFArenaScrollBar::GetMaxStepCnt()
{
	return m_nMaxStepCnt;
}