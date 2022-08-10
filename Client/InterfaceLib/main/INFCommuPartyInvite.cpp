// INFCommuPartyInvite.cpp: implementation of the CINFCommuPartyInvite class.
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
#include "INFCommunity.h"
#include "INFEditBox.h"
#include "IMSocketManager.h"
#include "INFImageRadioBtn.h"
#include "Chat.h"

#include "INFCommuPartyInvite.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Ŀ�´�Ƽ â �ɼ�
#define	COMMUNITY_OPINVITEBK_X				230
#define	COMMUNITY_OPINVITEBK_Y				0
#define	COMMUNITY_OPINVITEBK_WIDTH			290
#define	COMMUNITY_OPINVITEBK_HEIGHT			278
#define	COMMUNITY_OPINVITEBK_CAPS_HEIGHT	20

// �ʴ�
#define	COMMUNITY_OPINVITE_INVITE1_X		189
#define	COMMUNITY_OPINVITE_INVITE1_Y		67

// ���ΰ�ħ
#define	COMMUNITY_OPINVITE_REFRESH_X		78
#define	COMMUNITY_OPINVITE_REFRESH_Y		227

// �ʴ�
#define	COMMUNITY_OPINVITE_INVITE2_X		146
#define	COMMUNITY_OPINVITE_INVITE2_Y		227

// �ݱ�
#define	COMMUNITY_OPINVITE_CLOSE_X			213
#define	COMMUNITY_OPINVITE_CLOSE_Y			253

// �������� ����
#define LETTER_USER_EDIT_X						53
#define LETTER_USER_EDIT_Y						68
#define LETTER_USER_EDIT_W						165
#define LETTER_USER_READ_FONT_LINE_HEIGHT		15

#define MAX_ONEPATE_USER						5

#define RECOMMEND_USER_EDIT_X						63
#define RECOMMEND_USER_EDIT_Y						129
#define RECOMMEND_USER_CAP_Y						18

// ���� ��� ����
#define	PARTYINVITE_JOIN_X				41
#define	PARTYINVITE_JOIN_Y				127
#define	PARTYINVITE_JOIN_CAP_Y			18

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCommuPartyInvite::CINFCommuPartyInvite(CAtumNode* pParent)
{
	m_pParent = pParent;
	
	m_bShow = FALSE;
	m_bMove = FALSE;

	m_pFormat = NULL;
	m_ptCommOpBk.x = m_ptCommOpBk.y = 0;
	m_ptCommOpMouse.x = m_ptCommOpMouse.y = 0;

	m_pCloseBtn = NULL;
	m_pInviteBtn = NULL;
	m_pSelInviteBtn = NULL;
	m_pRefreshBtn = NULL;

	m_pEditUser = NULL;		// �޴� ����
	m_vecPartyInviteInfo.clear();
	m_pFontText = NULL;
	
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_INVITE_USER;nCnt++)
	{
		m_pPartyJoint[nCnt] = NULL;
	}
}

CINFCommuPartyInvite::~CINFCommuPartyInvite()
{
	m_vecPartyInviteInfo.clear();

	SAFE_DELETE(m_pFormat);
		
	SAFE_DELETE(m_pCloseBtn);
	SAFE_DELETE(m_pInviteBtn);	
	SAFE_DELETE(m_pSelInviteBtn);
	SAFE_DELETE(m_pRefreshBtn);		

	SAFE_DELETE(m_pEditUser);		// �޴� ����
	SAFE_DELETE(m_pFontText);

	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_INVITE_USER;nCnt++)
	{		
		SAFE_DELETE(m_pPartyJoint[nCnt]);		
	}
	
}

HRESULT CINFCommuPartyInvite::InitDeviceObjects()
{
	DataHeader	* pDataHeader= NULL;
	int nCnt = 0;

	POINT ptBkPos = ((CINFCommunity*)m_pParent)->GetCommunityBkPos();

	// Ŀ�´�Ƽ �ɼǹ�	
	m_ptCommOpBk.x = ptBkPos.x + COMMUNITY_OPINVITEBK_X;
	m_ptCommOpBk.y = (g_pD3dApp->GetBackBufferDesc().Height/2) - COMMUNITY_OPINVITEBK_HEIGHT/2;


	{
		if(NULL == m_pFormat)
		{
			m_pFormat = new CINFImage;	
		}		
		pDataHeader = FindResource("p_bk1");
		m_pFormat->InitDeviceObjects(pDataHeader->m_pData,pDataHeader->m_DataSize);
	}
		
	{
		// �ʴ�
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "c_sbt03");
		wsprintf(szDownBtn, "c_sbt01");
		wsprintf(szSelBtn, "c_sbt00");
		wsprintf(szDisBtn, "c_sbt02");
		if(NULL == m_pInviteBtn)
		{
			m_pInviteBtn = new CINFImageBtn;
		}
		m_pInviteBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	
	{
		// �ʴ�
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "c_sbt03");
		wsprintf(szDownBtn, "c_sbt01");
		wsprintf(szSelBtn, "c_sbt00");
		wsprintf(szDisBtn, "c_sbt02");
		if(NULL == m_pSelInviteBtn)
		{
			m_pSelInviteBtn = new CINFImageBtn;
		}
		m_pSelInviteBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}
	
	{
		// ���ΰ�ħ
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "c_pr3");
		wsprintf(szDownBtn, "c_pr1");
		wsprintf(szSelBtn, "c_pr0");
		wsprintf(szDisBtn, "c_pr2");		
		if(NULL == m_pRefreshBtn)
		{
			m_pRefreshBtn = new CINFImageBtn;
		}
		m_pRefreshBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	{
		// �ݱ�
		char szUpBtn[30], szDownBtn[30], szSelBtn[30], szDisBtn[30];
		wsprintf(szUpBtn, "shnpc063");
		wsprintf(szDownBtn, "shnpc061");
		wsprintf(szSelBtn, "shnpc060");
		wsprintf(szDisBtn, "shnpc062");
		if(NULL == m_pCloseBtn)
		{
			m_pCloseBtn = new CINFImageBtn;
		}
		m_pCloseBtn->InitDeviceObjects(szUpBtn, szDownBtn, szSelBtn, szDisBtn);		
	}

	{
		if(NULL == m_pEditUser)
		{
			m_pEditUser = new CINFEditBox;
		}
		POINT ptPos = {LETTER_USER_EDIT_X, LETTER_USER_EDIT_Y};
		m_pEditUser->InitDeviceObjects(9, ptPos, LETTER_USER_EDIT_W, TRUE, LETTER_USER_READ_FONT_LINE_HEIGHT);				
		m_pEditUser->SetStringMaxBuff(SIZE_MAX_CHARACTER_NAME);
	}
	{
		m_pFontText = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()), 9, D3DFONT_ZENABLE, FALSE,128,32);
		m_pFontText->InitDeviceObjects(g_pD3dDev);
	}
	{
		char chRadioOff[30], chRadioOn[30];
		wsprintf(chRadioOff, "radio_17b");
		wsprintf(chRadioOn, "radio_17a");
		
		for(nCnt = 0;nCnt < MAX_INVITE_USER;nCnt++)
		{		
			if(NULL == m_pPartyJoint[nCnt])
			{		
				m_pPartyJoint[nCnt] = new CINFImageRadioBtn;
			}				
			m_pPartyJoint[nCnt]->InitDeviceObjects(chRadioOff, chRadioOn);
		}		
	}
	
	
	return S_OK ;
}

HRESULT CINFCommuPartyInvite::RestoreDeviceObjects()
{
	if(m_pFormat )
	{
		m_pFormat->RestoreDeviceObjects();
	}
	if(m_pCloseBtn)
	{
		m_pCloseBtn->RestoreDeviceObjects();						
	}
	if(m_pInviteBtn)
	{
		m_pInviteBtn->RestoreDeviceObjects();						
	}
	if(m_pSelInviteBtn)
	{
		m_pSelInviteBtn->RestoreDeviceObjects();
	}
	if(m_pRefreshBtn)
	{
		m_pRefreshBtn->RestoreDeviceObjects();						
	}

	if(m_pEditUser)
	{
		m_pEditUser->RestoreDeviceObjects();		
	}
	if(m_pFontText)
	{
		m_pFontText->RestoreDeviceObjects();
	}
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_INVITE_USER;nCnt++)
	{	
		if(m_pPartyJoint[nCnt])
		{
			m_pPartyJoint[nCnt]->RestoreDeviceObjects();			
		}
	}

	// UI���� ���� 
	UpdateUIPos();

	
	return S_OK ;
}

HRESULT CINFCommuPartyInvite::DeleteDeviceObjects()
{
	if(m_pFormat )
	{
		m_pFormat->DeleteDeviceObjects();
		SAFE_DELETE(m_pFormat );
	}
	if(m_pCloseBtn)
	{		
		m_pCloseBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pCloseBtn);
	}
	if(m_pInviteBtn)
	{		
		m_pInviteBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pInviteBtn);
	}
	if(m_pSelInviteBtn)
	{
		m_pSelInviteBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pSelInviteBtn);
	}
	if(m_pRefreshBtn)
	{		
		m_pRefreshBtn->DeleteDeviceObjects();
		SAFE_DELETE(m_pRefreshBtn);
	}
	if(m_pEditUser)
	{
		m_pEditUser->DeleteDeviceObjects();
		SAFE_DELETE(m_pEditUser);		
	}
	if(m_pFontText)
	{
		m_pFontText->DeleteDeviceObjects();
		SAFE_DELETE(m_pFontText);
	}
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_INVITE_USER;nCnt++)
	{		
		if(m_pPartyJoint[nCnt])
		{
			m_pPartyJoint[nCnt]->DeleteDeviceObjects();	
			SAFE_DELETE(m_pPartyJoint[nCnt]);
		}
	}

	return S_OK ;
}

HRESULT CINFCommuPartyInvite::InvalidateDeviceObjects()
{
	if(m_pFormat)
	{
		m_pFormat->InvalidateDeviceObjects();
	}
	if(m_pCloseBtn)
	{		
		m_pCloseBtn->InvalidateDeviceObjects();		
	}
	if(m_pInviteBtn)
	{		
		m_pInviteBtn->InvalidateDeviceObjects();		
	}
	if(m_pSelInviteBtn)
	{		
		m_pSelInviteBtn->InvalidateDeviceObjects();		
	}
	if(m_pRefreshBtn)
	{
		m_pRefreshBtn->InvalidateDeviceObjects();		
	}
	if(m_pEditUser)
	{
		m_pEditUser->InvalidateDeviceObjects();
	}
	if(m_pFontText)
	{
		m_pFontText->InvalidateDeviceObjects();
	}
	int nCnt = 0;
	for(nCnt = 0;nCnt < MAX_INVITE_USER;nCnt++)
	{		
		if(m_pPartyJoint[nCnt])
		{
			m_pPartyJoint[nCnt]->InvalidateDeviceObjects();
		}
	}


	return S_OK ;
}

void CINFCommuPartyInvite::Render()
{
	if(!IsShowWindow())
	{
		return;
	}
	POINT ptBkPos = m_ptCommOpBk;
	if(m_pFormat)
	{		
		m_pFormat->Move(ptBkPos.x, ptBkPos.y);
		m_pFormat->Render() ;
	}
	
	m_pCloseBtn->Render();		
	m_pInviteBtn->Render();		
	m_pRefreshBtn->Render();		
	m_pSelInviteBtn->Render();		

	m_pEditUser->Tick();
	m_pEditUser->Render();

	int nCnt =0;
	int nInviteUser = (int)m_vecPartyInviteInfo.size();
	for(nCnt =0; nCnt < MAX_INVITE_USER; nCnt++)
	{	
		if(nCnt >= nInviteUser)
		{
			break;
		}		
		m_pPartyJoint[nCnt]->Render();
	}	

	RenderUserMem();
}

void CINFCommuPartyInvite::Tick()
{
	if(!IsShowWindow())
	{
		return;
	}

}

int CINFCommuPartyInvite::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(!IsShowWindow())
	{
		return INF_MSGPROC_NORMAL;
	}
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(IsMouseCaps(pt))
			{
				m_ptCommOpMouse.x = pt.x - m_ptCommOpBk.x;
				m_ptCommOpMouse.y = pt.y - m_ptCommOpBk.y;
				m_bMove = TRUE;
				return INF_MSGPROC_BREAK;
			}
						
			{
				if(TRUE == m_pCloseBtn->OnLButtonDown(pt))
				{					
					return  INF_MSGPROC_BREAK;
				}		
			}
			{
				if(TRUE == m_pInviteBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}		
			{
				if(TRUE == m_pRefreshBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}
			
			{
				if(TRUE == m_pSelInviteBtn->OnLButtonDown(pt))
				{
					// ��ư���� ���콺�� �ִ�.
					return  INF_MSGPROC_BREAK;
				}		
			}
			int nCnt = 0;
			for(nCnt = 0;nCnt <MAX_INVITE_USER;nCnt++)
			{					
				if(TRUE == m_pPartyJoint[nCnt]->OnLButtonDown(pt))
				{						
					OnClickJoint(nCnt);
					return  INF_MSGPROC_BREAK;
				}		
			}

			if((pt.x >= m_ptCommOpBk.x && (pt.x <= m_ptCommOpBk.x+COMMUNITY_OPINVITEBK_WIDTH))
				&& (pt.y >= m_ptCommOpBk.y && (pt.y <= m_ptCommOpBk.y+COMMUNITY_OPINVITEBK_HEIGHT)))
			{
				// ������ �������� �ִ�.
				return  INF_MSGPROC_BREAK;
			}
			
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_bMove)
			{
				m_ptCommOpBk.x = pt.x - m_ptCommOpMouse.x;
				m_ptCommOpBk.y = pt.y - m_ptCommOpMouse.y;				
				// UI���� ���� 
				UpdateUIPos();
				return INF_MSGPROC_BREAK;
			}
			
			m_pCloseBtn->OnMouseMove(pt);
			m_pInviteBtn->OnMouseMove(pt);	
			m_pRefreshBtn->OnMouseMove(pt);		
			m_pSelInviteBtn->OnMouseMove(pt);		

		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			if(m_bMove)
			{
				m_bMove = FALSE;
				return INF_MSGPROC_BREAK;
			}
						
			{
				if(TRUE == m_pCloseBtn->OnLButtonUp(pt))
				{			
					// ��ư���� ���콺�� �ִ�.
					ShowWindow(FALSE);					
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
					return  INF_MSGPROC_BREAK;				
				}
			}
			{
				if(TRUE == m_pInviteBtn->OnLButtonUp(pt))
				{			
					char chUserName[SIZE_MAX_CHARACTER_NAME];
					m_pEditUser->GetString(chUserName, SIZE_MAX_CHARACTER_NAME);
					// 2008-07-14 by bhsohn EP3 ���� ó��
					if(g_pGameMain->IsRejectUser(chUserName))
					{
						g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_080714_0207,COLOR_ERROR);//"\\y�ź� ��Ͽ� ��ϵ� ����Դϴ�."
						g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
						return INF_MSGPROC_BREAK;
					}

					((CINFCommunity*)m_pParent)->PartySendInviteUser(chUserName);	// ���� �ʴ�
					
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
					return  INF_MSGPROC_BREAK;				
				}
			}			
			{
				if(TRUE == m_pRefreshBtn->OnLButtonUp(pt))
				{				
					RqInvitePartyInfo();	// �ٽ� ��û
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
					return  INF_MSGPROC_BREAK;				
				}
			}
			
			{
				if(TRUE == m_pSelInviteBtn->OnLButtonUp(pt))
				{		
					OnClickSelInvite();
					g_pD3dApp->m_pSound->PlayD3DSound(SOUND_SELECT_BUTTON, D3DXVECTOR3(0,0,0), FALSE);											
					return  INF_MSGPROC_BREAK;				
				}
			}
			
		}
		break;
	case WM_IME_STARTCOMPOSITION:
//	case WM_IME_NOTIFY:
	case WM_IME_COMPOSITION:
	case WM_INPUTLANGCHANGE:	
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_SETCONTEXT:	
	case WM_CHAR:
	case WM_KEYDOWN:
		{
			if(m_pEditUser->WndProc(uMsg, wParam, lParam, NULL, TRUE))
			{
				return INF_MSGPROC_BREAK;
			}

		}
		break;
	}

	return INF_MSGPROC_NORMAL;		
}

void CINFCommuPartyInvite::ShowWindow(BOOL bShow)
{
	m_bShow = bShow;

	m_bMove = FALSE;		// ��Ʈ���� �����δ�.
	if(bShow)
	{
		POINT ptBkPos = ((CINFCommunity*)m_pParent)->GetCommunityBkPos();

		// Ŀ�´�Ƽ �ɼǹ�	
		m_ptCommOpBk.x = ptBkPos.x + COMMUNITY_OPINVITEBK_X;
		m_ptCommOpBk.y = (g_pD3dApp->GetBackBufferDesc().Height/2) - COMMUNITY_OPINVITEBK_HEIGHT/2;

		m_pEditUser->EnableEdit(TRUE, TRUE);

		// UI���� ���� 
		UpdateUIPos();
		
		RqInvitePartyInfo();
	}
	else
	{
		m_pEditUser->EnableEdit(FALSE, FALSE);
	}
}

BOOL CINFCommuPartyInvite::IsShowWindow()
{
	return m_bShow;
}

BOOL CINFCommuPartyInvite::IsMouseCaps(POINT ptPos)
{
	if((ptPos.x >= m_ptCommOpBk.x && (ptPos.x <= m_ptCommOpBk.x+COMMUNITY_OPINVITEBK_WIDTH))
		&& (ptPos.y >= m_ptCommOpBk.y && (ptPos.y <= m_ptCommOpBk.y+COMMUNITY_OPINVITEBK_CAPS_HEIGHT)))
	{
		return TRUE;
	}
	return FALSE;

}

void CINFCommuPartyInvite::UpdateUIPos()
{
	POINT ptBkPos = m_ptCommOpBk;

	int nCnt = 0;
	int nPosX, nPosY;
	nPosX = nPosY = 0;
	
	{
		nPosX = ptBkPos.x + COMMUNITY_OPINVITE_CLOSE_X;
		nPosY = ptBkPos.y + COMMUNITY_OPINVITE_CLOSE_Y;		
		m_pCloseBtn->SetBtnPosition(nPosX, nPosY);	
	}
	{
		nPosX = ptBkPos.x + COMMUNITY_OPINVITE_INVITE1_X;
		nPosY = ptBkPos.y + COMMUNITY_OPINVITE_INVITE1_Y;		
		m_pInviteBtn->SetBtnPosition(nPosX, nPosY);	
	}	
	{
		nPosX = ptBkPos.x + COMMUNITY_OPINVITE_REFRESH_X;
		nPosY = ptBkPos.y + COMMUNITY_OPINVITE_REFRESH_Y;		
		m_pRefreshBtn->SetBtnPosition(nPosX, nPosY);	
	}
	
	{
		nPosX = ptBkPos.x + COMMUNITY_OPINVITE_INVITE2_X;
		nPosY = ptBkPos.y + COMMUNITY_OPINVITE_INVITE2_Y;		
		m_pSelInviteBtn->SetBtnPosition(nPosX, nPosY);	
	}

	{
		nPosX = ptBkPos.x + LETTER_USER_EDIT_X;
		nPosY = ptBkPos.y + LETTER_USER_EDIT_Y;		
		m_pEditUser->SetPos(nPosX, nPosY);
	}	

	{		
		// ���� ��� ����		
		for(nCnt = 0;nCnt < MAX_INVITE_USER;nCnt++)
		{
			nPosX = ptBkPos.x + PARTYINVITE_JOIN_X;
			nPosY = ptBkPos.y + PARTYINVITE_JOIN_Y+ (nCnt*PARTYINVITE_JOIN_CAP_Y);		
			m_pPartyJoint[nCnt]->SetPosition(nPosX, nPosY, 60);		
		}		
	}
}

void CINFCommuPartyInvite::OnClickInviteBtn()
{	
}

void CINFCommuPartyInvite::RqInvitePartyInfo()
{
	m_vecPartyInviteInfo.clear();
	int nCnt =0;
	for(nCnt =0; nCnt < MAX_INVITE_USER; nCnt++)
	{			
		m_pPartyJoint[nCnt]->SetRadioBtn(FALSE);		
	}	
	// Lock
	{
		vector<MessageType_t> vecUnLockMsg;
		vecUnLockMsg.clear();
		vecUnLockMsg.push_back(T_IC_PARTY_RECOMMENDATION_MEMBER);		
		vecUnLockMsg.push_back(T_IC_PARTY_RECOMMENDATION_MEMBER_OK);		
		// �ϳ��� ��Ī �Ǿ ���� Ǯ����. 
		g_pD3dApp->EnterMultiLock(FALSE, T_IC_PARTY_RECOMMENDATION_MEMBER, vecUnLockMsg, MULTI_LOCK_ONE_MATCHING);
	}

	g_pIMSocket->SendMsg( T_IC_PARTY_RECOMMENDATION_MEMBER, NULL, NULL);		
	
}

void CINFCommuPartyInvite::AddInvitePartyInfo(SRECOMMENDATION_MEMBER_INFO* pMember)
{
	SRECOMMENDATION_MEMBER_INFO stTmp;	
	memcpy(&stTmp, pMember, sizeof(SRECOMMENDATION_MEMBER_INFO));

	m_vecPartyInviteInfo.push_back(stTmp);

}
void CINFCommuPartyInvite::RenderUserMem()
{
	POINT ptBkPos = m_ptCommOpBk;

	vector<SRECOMMENDATION_MEMBER_INFO>::iterator itUser = m_vecPartyInviteInfo.begin();
	int nCnt = 0;
	for(nCnt =0; nCnt < MAX_ONEPATE_USER;nCnt++)
	{
		if(itUser == m_vecPartyInviteInfo.end())
		{
			break;
		}
		SRECOMMENDATION_MEMBER_INFO stTmp = (*itUser);
		m_pFontText->DrawText(ptBkPos.x+RECOMMEND_USER_EDIT_X, 
					ptBkPos.y+RECOMMEND_USER_EDIT_Y+ (RECOMMEND_USER_CAP_Y*nCnt), 
					GUI_FONT_COLOR, 
					stTmp.CharacterName);

		itUser++;
	}
}

void CINFCommuPartyInvite::OnClickJoint(int nIdx)
{
	int nInviteUser = (int)m_vecPartyInviteInfo.size();
	if( nIdx < 0
		&& nIdx >= nInviteUser)
	{
		return;
	}	
	BOOL bCheck = m_pPartyJoint[nIdx]->GetRadioBtn();
	bCheck ^= TRUE;
	m_pPartyJoint[nIdx]->SetRadioBtn(bCheck);
}
void CINFCommuPartyInvite::OnClickSelInvite()
{
	int nCnt =0;
	int nInviteUser = (int)m_vecPartyInviteInfo.size();
	for(nCnt =0; nCnt < MAX_INVITE_USER; nCnt++)
	{	
		if(nCnt >= nInviteUser)
		{
			break;
		}		
		if(m_pPartyJoint[nCnt]->GetRadioBtn())
		{
			SRECOMMENDATION_MEMBER_INFO stInfo = m_vecPartyInviteInfo[nCnt];
			((CINFCommunity*)m_pParent)->PartySendInviteUser(stInfo.CharacterName);	// ���� �ʴ�
		}
	}
}