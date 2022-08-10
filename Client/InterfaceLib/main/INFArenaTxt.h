// INFArenaTxt.h: interface for the CINFArenaTxt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFARENATXT_H__898FDAB2_9755_49E4_956D_4DC82A6B7065__INCLUDED_)
#define AFX_INFARENATXT_H__898FDAB2_9755_49E4_956D_4DC82A6B7065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

// �Ʒ��� ī��Ʈ
#define		MAX_ARENA_CNT				6

// 2008-04-17 by bhsohn �Ʒ��� ���Խ�, �ڽ��� �� ����
// �� ����
#define		ARENA_TEAM_BLUE				0	// �����
#define		ARENA_TEAM_RED				1	// ������
#define		MAX_ARENA_TEAM_CNT			2

class CINFImage;

class CINFArenaTxt  : public CINFBase
{
public:
	CINFArenaTxt(CAtumNode* pParent);
	CINFArenaTxt();
	virtual ~CINFArenaTxt();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Render();
	virtual void Tick();

	void StartArenaCnt();
	void SetIssue(int issue,float fArenaTick = 0);
	void SetShowState(int ShowState);

	// 2008-04-17 by bhsohn �Ʒ��� ���Խ�, �ڽ��� �� ����
	void ShowMyTeamLogo(BYTE byInfluence);
private:
	// 2008-04-17 by bhsohn �Ʒ��� ���Խ�, �ڽ��� �� ����
	void HidingMyTeamLogo();	// ����� �ִ� ����
	void HideMyTeamLogo();		// ������ ����
	void TickFadeMode();	
	// end 2008-04-17 by bhsohn �Ʒ��� ���Խ�, �ڽ��� �� ����
	

public:
private:
	CINFImage*	m_pArenaCnt[MAX_ARENA_CNT];					// ���� 
	CINFImage*	m_pArenaTxt[ARENA_ISSUE_DRAW];				// �Ʒ��� ����.
	// 2008-04-17 by bhsohn �Ʒ��� ���Խ�, �ڽ��� �� ����
	CINFImage*	m_pArenaTeamTxt[MAX_ARENA_TEAM_CNT];				// �Ʒ��� ��

	
	int			m_nArenaIssue;								// 
	int			m_nArenaShowState;

	// ī��Ʈ ���� 
	int			m_nArenaCnt;
	float		m_fArenaCntTick;

	// 2008-04-17 by bhsohn �Ʒ��� ���Խ�, �ڽ��� �� ����
	// ���̵� ��
	int			m_nFadeMode;
	float		m_fFadeInTime;
	DWORD		m_dwBkAlpha;
	float		m_fTeamInfoShowTime;
	// ����
	int			m_nInflIdx;
};

#endif // !defined(AFX_INFARENATXT_H__898FDAB2_9755_49E4_956D_4DC82A6B7065__INCLUDED_)
