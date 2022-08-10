// INFArenaCreate.h: interface for the CINFArenaCreate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFARENACREATE_H__8ECA0A65_7C15_48B5_8DB4_C91FB72EC2B2__INCLUDED_)
#define AFX_INFARENACREATE_H__8ECA0A65_7C15_48B5_8DB4_C91FB72EC2B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"


class CINFArenaCreate : public CINFBase  
{
public:
	CINFArenaCreate(CAtumNode* pParent, BUILDINGNPC* pBuilding);
	CINFArenaCreate();
	virtual ~CINFArenaCreate();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	VOID			SetPos(UINT x, UINT y);
	VOID			AddAllPersons(SARENA_REQUEST_CREATE_TEAMINFO *pTeamInfo);
	VOID			ClearAllPersons();
	VOID			SetPersons(BYTE BMode);
	VOID			ClearPersons();
	VOID			ChangeArenaMode(BYTE BMode);
	VOID			ShowCreateWindow();
	VOID			HideCreateWindow();
	VOID			SendCreateTeam();

	BUILDINGNPC*	m_pBuildingInfo;


	
	CINFImage	*	m_pImgCreateB[BUTTON_STATE_NUMBER];			// ���� ��ư.
	CINFImage	*	m_pImgCancelB[BUTTON_STATE_NUMBER];			// ��� ��ư.
	//CINFImage	*	m_pImgCbArr[BUTTON_STATE_NUMBER];			// �޺� ��ư.

	UINT			m_nStateCreateB;							// ���� ��ư state
	UINT			m_nStateCancelB;							// ��� ��ư state
//	UINT			m_nStateCbArrCount;							// �ο� ��ư state
	//UINT			m_nStateCbArrMode;							// ��� ��ư state



	CINFImage	*	m_pImgAreCreate;							// �Ʒ��� ����â.
	CINFImage	*	m_pImgCbCount;								// �ο� �޺� ���.
	CINFImage	*	m_pImgCbAmode;								// ��� ���� �޺� ���.

	CD3DHanFont	*	m_pFontCount;								// �ο� ��Ʈ.
	CD3DHanFont	*	m_pFontMode;								// ��� ��Ʈ.
	CD3DHanFont	*	m_pFontPass;								// �н�����.
//--------------------------------------------------------------------------//
//						�� ������ �ʿ��� ����.
	UINT			m_nSelectMode;								// �� ������ ������ ���.
	UINT			m_nSelectCount;								// �� ������ ������ �ο���.
	CHAR			m_cTeamPW[SIZE_MAX_TEAM_PW];				// ��й�ȣ.
//--------------------------------------------------------------------------//
	int				m_ntempMode;								// �ӽ� ��� ��ȣ.
	BYTE			m_nMode;									// ��� ����
	BYTE			m_nCount;									// �ο� ���
	
	BOOL			m_bShow;									// �� ����â�� ���̰� �Ұ��ΰ�.
	UINT			m_nStartX;									// �������� ��ġ ��.
	UINT			m_nStartY;									// �������� ��ġ ��.

	BOOL			m_bCbCount;									// �ο� �޺� â�� �ٿ���ΰ�.
	BOOL			m_bCbMode;									// ��� �޺� â�� �ٿ���ΰ�.
	BOOL			m_bTxtPass;									// ��й�ȣ�� Ȱ��ȭ.

	vector<SARENA_REQUEST_CREATE_TEAMINFO>	m_vecAllPersons;		// ��� ����� �ο� ����Ʈ.
	vector<BYTE>							m_vecPersons;		// �ο��� ����Ʈ.

};

#endif // !defined(AFX_INFARENACREATE_H__8ECA0A65_7C15_48B5_8DB4_C91FB72EC2B2__INCLUDED_)
