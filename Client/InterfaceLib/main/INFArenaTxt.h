// INFArenaTxt.h: interface for the CINFArenaTxt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFARENATXT_H__898FDAB2_9755_49E4_956D_4DC82A6B7065__INCLUDED_)
#define AFX_INFARENATXT_H__898FDAB2_9755_49E4_956D_4DC82A6B7065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

// 아레나 카운트
#define		MAX_ARENA_CNT				6

// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
// 팀 갯수
#define		ARENA_TEAM_BLUE				0	// 블루팀
#define		ARENA_TEAM_RED				1	// 레드팀
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

	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	void ShowMyTeamLogo(BYTE byInfluence);
private:
	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	void HidingMyTeamLogo();	// 숨기고 있는 과정
	void HideMyTeamLogo();		// 완전히 숨김
	void TickFadeMode();	
	// end 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	

public:
private:
	CINFImage*	m_pArenaCnt[MAX_ARENA_CNT];					// 숫자 
	CINFImage*	m_pArenaTxt[ARENA_ISSUE_DRAW];				// 아레나 승패.
	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	CINFImage*	m_pArenaTeamTxt[MAX_ARENA_TEAM_CNT];				// 아레나 팀

	
	int			m_nArenaIssue;								// 
	int			m_nArenaShowState;

	// 카운트 숫자 
	int			m_nArenaCnt;
	float		m_fArenaCntTick;

	// 2008-04-17 by bhsohn 아레나 진입시, 자신의 팀 설정
	// 페이드 값
	int			m_nFadeMode;
	float		m_fFadeInTime;
	DWORD		m_dwBkAlpha;
	float		m_fTeamInfoShowTime;
	// 진형
	int			m_nInflIdx;
};

#endif // !defined(AFX_INFARENATXT_H__898FDAB2_9755_49E4_956D_4DC82A6B7065__INCLUDED_)
