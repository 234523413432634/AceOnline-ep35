// INFSecuSelectMenu.h: interface for the CINFSecuSelectMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFSECUSELECTMENU_H__588A87F2_B946_43C0_A164_08BF2AEFDAE6__INCLUDED_)
#define AFX_INFSECUSELECTMENU_H__588A87F2_B946_43C0_A164_08BF2AEFDAE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CINFSelect;
class CINFEditBox;
class CINFSecuEditBox;

class CINFSecuSelectMenu  : public CINFBase
{
public:
	CINFSecuSelectMenu(CINFSelect* pMain);
	virtual ~CINFSecuSelectMenu();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Render();
	virtual void	Tick();

	int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnCloseInfWnd();
	
	void ShowSetPassWnd();

	BOOL IsShowWnd();
	void ShowSecutiryWnd(BOOL bShowWnd);

private:
	int OnLButtonDown(WPARAM wParam, LPARAM lParam);
	int OnMouseMove(WPARAM wParam, LPARAM lParam);
	int OnLButtonUp(WPARAM wParam, LPARAM lParam);

	void UpdateBtnPos(int nBackPosX, int nBackPosY);

	void OnClickOk();
	void OnClickCancel();

	void RefreshEditCtl(int nEditMode);
	

private:
	CINFSelect*		m_pINFSelect;

	CINFImage*			m_pSetPassBk;

	int				m_nBackPosX;
	int				m_nBackPosY;

	int				m_nCx;
	int				m_nCy;

	BOOL			m_bMouseLock;
	POINT			m_ptMouseLockCap;

	CINFImageBtn*	m_pSetOk;
	CINFImageBtn*	m_pSetCancel;

	CINFEditBox*		m_pINFUserName;
	CINFSecuEditBox*	m_pINFSecuPassWord;

	int				m_nSelEdit;
	BOOL			m_bShowWnd ;
};

#endif // !defined(AFX_INFSECUSELECTMENU_H__588A87F2_B946_43C0_A164_08BF2AEFDAE6__INCLUDED_)
