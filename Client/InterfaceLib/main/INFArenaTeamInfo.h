// INFArenaTeamInfo.h: interface for the CINFArenaTeamInfo class.
// 2007-05-02 by dgwoo	�Ʒ��� ������ �̵����� ���̴� ������â Ŭ����.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFARENATEAMINFO_H__7334AC59_4705_472D_AA0D_E0E0D49F12E8__INCLUDED_)
#define AFX_INFARENATEAMINFO_H__7334AC59_4705_472D_AA0D_E0E0D49F12E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFArenaScrollBar.h"

enum{
	ARENA_BUTTON_STATE_USERIN,
	ARENA_BUTTON_STATE_READY,
	ARENA_BUTTON_STATE_ENEMYSEARCH
};
#define ARENA_BUTTON_GAP						3.0f
#define ARENA_BUTTON_UREADY_GAP					120.0f			

// 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����
struct STRUCT_TEAM_CHARACTERINFO
{
	BYTE			ArenaState;				// 2007-04-17 by dhjin, ���� �Ʒ��� ����
	ClientIndex_t	ClientIndex;
	CHAR			CharacterName[SIZE_MAX_ARENA_FULL_NAME];	// 2007-04-17 by dhjin, �������� �̸�
};
// end 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����


class CINFImage;

class CINFArenaTeamInfo : public CINFBase  
{
public:
	CINFArenaTeamInfo();
	CINFArenaTeamInfo(CAtumNode* pParent);
	virtual ~CINFArenaTeamInfo();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Render();
	virtual void	Tick();
	int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	int				OnMouseWheel(WPARAM wParam, LPARAM lParam);
	int				OnLButtonDown(WPARAM wParam, LPARAM lParam);
	int				OnLButtonUp(WPARAM wParam, LPARAM lParam);
	int				OnMouseMove(WPARAM wParam, LPARAM lParam);
	VOID			SetMouseRect();

	VOID			SetState(BYTE state);
	VOID			AddTeamUserInfo(MSG_FC_ARENA_TEAM_MEMBER_LIST *pMsg);
	VOID			ClickReadyButton();
	VOID			AppCancel(BOOL bButton = TRUE);
	VOID			MoveInfoButton(POINT pt);
	void					TestDB();

	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	BOOL			IsArenaReady();


	CINFImage				*	m_pImgTeamInfoB[3][2];						// 0 ��������� 1: �غ� ����� 2: ������˻���.
	CINFImage				*	m_pImgBG;
	CINFImage				*	m_pImgReady;								// ���� ���� ������ �ٸ�����.
	CINFImage				*	m_pImgReadyB[BUTTON_STATE_NUMBER];			// �غ� 
	CINFImage				*	m_pImgUReadyB[BUTTON_STATE_NUMBER];			// �غ� ����.
	CINFImage				*	m_pImgAppCancelB[BUTTON_STATE_NUMBER];		// ��û ��ҹ�ư.
	CINFImage				*	m_pImgWinSizeB[2][BUTTON_STATE_NUMBER];		// ���� â ������.

	CD3DHanFont				*	m_pFontID;								// ���� �Ƶ� 
	CD3DHanFont				*	m_pFontState;							// �������� ���¸� ���ڷ�..

	int							m_nInfoButtonX;							// ���� ��ư�� X��ǥ.
	int							m_nInfoButtonY;							// ���� ��ư�� Y��ǥ.
	POINT						m_ptOld;								// ���� ��ǥ.
	BOOL						m_bInfoButton;							// ���� ��ư�� �̵����� �����ΰ�?


	UINT						m_nMainBState;							// �Ʒ��� ��ư.(0 ��������� 1: �غ� ����� 2: ������˻���.
	UINT						m_nMainBUnder;							// �Ʒ��� ��ư.(���콺 ����ΰ�?
	BOOL						m_bTeamInfoShow;						// �������� �����ٰ��ΰ�.

	UINT						m_nReadyB;								// �غ� ��ư�� ����.
	UINT						m_nUReadyB;								// �غ����� ��ư�� ����.
	UINT						m_nWinSizeB;							// ���� â�� ����� �����ϴ� ��ư�� ����.
	BOOL						m_bReady;								// ���� �غ� �����ΰ�.
	UINT						m_nAppCancel;							// ��û ��ҹ�ư.
	float						m_fArenaButtonGap;						// ��ư�� �����ð� gap�� �־� �����ϵ����Ѵ�.
	float						m_fUReadyButtonTime;					// �غ� ���� ������ �ð��� üũ.

	int							m_nPerson;								// ���� �ο�.
	int							m_nLimitPerson;							// ���� �ο�.

	
	// 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����
	//vector<SARENA_TEAM_CHARACTERINFO>		m_vecTeamUserInfo;
	vector<STRUCT_TEAM_CHARACTERINFO>		m_vecTeamUserInfo;	


	CINFArenaScrollBar		*	m_pScroll;					// ��ũ�� 


};

#endif // !defined(AFX_INFARENATEAMINFO_H__7334AC59_4705_472D_AA0D_E0E0D49F12E8__INCLUDED_)
