// INFCityArena.h: interface for the CINFCityArena class.
// 2007-04-19 by dgwoo
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCITYARENA_H__81371F39_ACB1_4435_AF54_E6C8C699A632__INCLUDED_)
#define AFX_INFCITYARENA_H__81371F39_ACB1_4435_AF54_E6C8C699A632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFArenaCreate.h"
#include "INFArenaScrollBar.h"


class CINFListBox;

// ������, ���.
enum{
	ARENA_ROOM_UNLOCK,
	ARENA_ROOM_LOCK,
	ARENA_ROOM_LOCKMODE
};

// �Ʒ��� â�� �� ����. Ȯ���Ҽ� �����Ƿ�.
enum{
	ARENA_BACK_TAB_BATTLE,
	ARENA_BACK_TAB_END
};

// 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����
struct STRUCT_TEAM_INFO
{
	BOOL			TeamLock;				// 2007-04-17 by dhjin, �� ���� ����  0 : ����, 1: ����� 
	BOOL			TeamEvent;				// 2008-03-10 by dhjin, �Ʒ��� ���� - �̺�Ʈ������ 0: �Ϲ��� 1: �̺�Ʈ��
	BYTE			TeamSize;				// 2007-04-17 by dhjin, �� �ο� ���� 
	BYTE			CurrentTeamSize;		// 2007-04-25 by dhjin, ���� �� �ο�
	BYTE			ArenaMode;				// 2007-04-17 by dhjin, �Ʒ��� ���   1 : DeathMatch, 2 : Round, so on..
	BYTE			ArenaState;				// 2007-06-05 by dhjin, ���� �Ʒ��� ����
	BYTE			TeamStartLevel;			// 2007-06-05 by dhjin, ���� ���� ����
	BYTE			TeamEndLevel;			// 2007-06-05 by dhjin, ���� �� ����
	INT				TeamNum;				// 2007-04-17 by dhjin, �� ��ȣ
	CHAR			CharacterName[SIZE_MAX_ARENA_FULL_NAME];		// 2007-04-17 by dhjin, ���� �̸�
};
// end 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����

class CINFImage;
class CINFCityArena : public CINFBase  
{
public:
	CINFCityArena(CAtumNode* pParent, BUILDINGNPC* pBuilding, CGameData *pGameData);
	virtual ~CINFCityArena();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	VOID			CreateRoom();
	BOOL			App();
	VOID			AppCancel();
	VOID			QuickApp();										// ������û.
	VOID			Init();											//ó�� �����Ҷ� �����ؾ��Ұ�	
	VOID			ReFresh();										// ���� ����� ���� ��û�Ѵ�.	
	VOID			ArenaTeamListInput(MSG_FC_ARENA_REQUEST_TEAM_OK *);
	BYTE			ChangeTab(BYTE BMode);							// �� ����.
	VOID			EnemyInfo();									// ����� ������ ��û�Ѵ�.
	VOID			RequestTeamList();								// ������ ����Ʈ�ڽ��� �������� ����Ʈ ����Ʈ�� ��û�Ѵ�.
	BOOL			IsInfluenceEqual();								// ���� ���°� ����Ʈ�� ������ ���� ������?
	
	VOID			AllModePersonInfo(MSG_FC_ARENA_REQUEST_CREATE_TEAMINFO_OK *pTeamInfo);		// ��忡 ���� �ο������� �����Ѵ�.
	int				OnMouseWheel(WPARAM wParam, LPARAM lParam);
	int				OnLButtonDown(WPARAM wParam, LPARAM lParam);
	int				OnLButtonUp(WPARAM wParam, LPARAM lParam);
	int				OnMouseMove(WPARAM wParam, LPARAM lParam);

	// 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����
	//SARENA_TEAM_INFO* GetSelectListTeam();
	STRUCT_TEAM_INFO* GetSelectListTeam();
	
	void			TestDB();

	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���	
	void			SendArenaRequestTeam(int nStartTeamNum);		// �Ʒ��� �� ��û
	void			SendArenaEnterRoom(char* TeamPW);				// �Ʒ��� ����

	BUILDINGNPC*	m_pBuildingInfo;



	CINFImage	*	m_pImgRefreshB[BUTTON_STATE_NUMBER];		// ���ΰ�ħ ��ư.
	CINFImage	*	m_pImgSearch[BUTTON_STATE_NUMBER];			// �˻� ��ư.Faq_df
	CINFImage	*	m_pImgLock[ARENA_ROOM_LOCKMODE];			// ���� ������� ���������� �̹���.
	CINFImage	*	m_pImgArenaMode[ARENA_WAR_MODE_END];		// ������ �Ʒ��� ����� �̹���.
	CINFImage	*	m_pImgAreFont;								// �Ʒ��� ���� ���� ��Ʈ�̹���.
	CINFImage	*	m_pImgAreRoomList;							// �Ʒ��� ��� ��.
	CINFImage	*	m_pImgScroll;								// ��ũ�� 
	CINFImage	*	m_pImgScrollBar;							// ��ũ�� ���.
	CINFImage	*	m_pImgSelectTeam;							// ������ �� 

	CD3DHanFont *	m_pFontRoomNum;								// ��ѹ�.
	CD3DHanFont *	m_pFontUserID;								// �����Ƶ�.
	CD3DHanFont *	m_pFontPerson;								// �ο�.
	CD3DHanFont	*	m_pFontState;								// �� ����.
	CD3DHanFont	*	m_pFontLevel;								// �� ����.

	// 2008-03-10 by bhsohn �̺�Ʈ �Ʒ����� ����ó��
	CD3DHanFont *	m_pBoldFont;								// ��ѹ�.

	CINFListBox *	m_pLBoxInf;									// ���� ���� ����Ʈ �ڽ�.
	CINFListBox *	m_pLBoxState;								// ���� ��.

	UINT			m_nTab;										// �� ��ȣ.
	BYTE			m_BArenaMode;								// �Ʒ��� ��� 1 : DeathMatch, 2 : Round, so on..

	UINT			m_nTeamInfoB;								// �� ���� ��ư ����.
	UINT			m_nRefresh;									// ���� ��ħ ��ư ����.
	UINT			m_nSearch;									// �˻� ��ư�� ����.

	int				m_nSelectIndex;								// ������ ������ �ε���.
	int				m_nTeamTotalCount;							// �� ��� ���ο���.

	BYTE			m_BRequestTeamState;						// 2007-06-05 by dhjin, �� ���� ��û �÷��� 1 : ��� ����, 2 : �����. 3 : ����� ����

	CINFArenaCreate 	*					m_pArenaCreate;				// �� ������ Ŭ������ �ּ�.
	
	// 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����
	//vector<SARENA_TEAM_INFO>				m_vecTeamList;				// �� ���.
	vector<STRUCT_TEAM_INFO>				m_vecTeamList;				// �� ���.
	
	//--------------------------------------------------------------------------//
	//    ��ũ�� ���� ���� .
	CINFArenaScrollBar	*					m_pScroll;					// ��ũ�� 

};

#endif // !defined(AFX_INFCITYARENA_H__81371F39_ACB1_4435_AF54_E6C8C699A632__INCLUDED_)
