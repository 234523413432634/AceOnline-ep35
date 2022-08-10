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


	
	CINFImage	*	m_pImgCreateB[BUTTON_STATE_NUMBER];			// 생성 버튼.
	CINFImage	*	m_pImgCancelB[BUTTON_STATE_NUMBER];			// 취소 버튼.
	//CINFImage	*	m_pImgCbArr[BUTTON_STATE_NUMBER];			// 콤보 버튼.

	UINT			m_nStateCreateB;							// 생성 버튼 state
	UINT			m_nStateCancelB;							// 취소 버튼 state
//	UINT			m_nStateCbArrCount;							// 인원 버튼 state
	//UINT			m_nStateCbArrMode;							// 모드 버튼 state



	CINFImage	*	m_pImgAreCreate;							// 아레나 생성창.
	CINFImage	*	m_pImgCbCount;								// 인원 콤보 배경.
	CINFImage	*	m_pImgCbAmode;								// 모드 선택 콤보 배경.

	CD3DHanFont	*	m_pFontCount;								// 인원 폰트.
	CD3DHanFont	*	m_pFontMode;								// 모드 폰트.
	CD3DHanFont	*	m_pFontPass;								// 패스워드.
//--------------------------------------------------------------------------//
//						방 생성시 필요한 변수.
	UINT			m_nSelectMode;								// 방 생성시 선택한 모드.
	UINT			m_nSelectCount;								// 방 생성시 선택한 인원수.
	CHAR			m_cTeamPW[SIZE_MAX_TEAM_PW];				// 비밀번호.
//--------------------------------------------------------------------------//
	int				m_ntempMode;								// 임시 모드 번호.
	BYTE			m_nMode;									// 모드 갯수
	BYTE			m_nCount;									// 인원 명수
	
	BOOL			m_bShow;									// 방 생성창을 보이게 할것인가.
	UINT			m_nStartX;									// 렌더링할 위치 값.
	UINT			m_nStartY;									// 렌더링할 위치 값.

	BOOL			m_bCbCount;									// 인원 콤보 창을 뛰울것인가.
	BOOL			m_bCbMode;									// 모드 콤보 창을 뛰울것인가.
	BOOL			m_bTxtPass;									// 비밀번호가 활성화.

	vector<SARENA_REQUEST_CREATE_TEAMINFO>	m_vecAllPersons;		// 모든 모드의 인원 리스트.
	vector<BYTE>							m_vecPersons;		// 인원의 리스트.

};

#endif // !defined(AFX_INFARENACREATE_H__8ECA0A65_7C15_48B5_8DB4_C91FB72EC2B2__INCLUDED_)
