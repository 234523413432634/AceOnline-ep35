// INFSecuChanPassWnd.h: interface for the CINFSecuChanPassWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFSECUCHANPASSWND_H__A654CF1F_7C64_4C17_80E8_65FE24160372__INCLUDED_)
#define AFX_INFSECUCHANPASSWND_H__A654CF1F_7C64_4C17_80E8_65FE24160372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFSecuEditBox.h"

class CINFImage;
class CD3DHanFont;
class CINFSecuMain;

class CINFSecuChanPassWnd  : public CINFBase
{
public:
	CINFSecuChanPassWnd(CINFSecuMain* pMain);
	virtual ~CINFSecuChanPassWnd();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Render();
	virtual void	Tick();

	int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnCloseInfWnd();
	
	void ShowSetPassWnd();

private:
	int OnLButtonDown(WPARAM wParam, LPARAM lParam);
	int OnMouseMove(WPARAM wParam, LPARAM lParam);
	int OnLButtonUp(WPARAM wParam, LPARAM lParam);

	void UpdateBtnPos(int nBackPosX, int nBackPosY);

	void OnClickOk();
	void OnClickCancel();

	void RefreshEditCtl(int nEditMode, CINFSecuEditBox* pIEdit);

private:
	CINFSecuMain*		m_pINFSecuMain;

	CINFImage*			m_pSetPassBk;

	int				m_nBackPosX;
	int				m_nBackPosY;

	int				m_nCx;
	int				m_nCy;

	BOOL			m_bMouseLock;
	POINT			m_ptMouseLockCap;

	CINFImageBtn*	m_pSetOk;
	CINFImageBtn*	m_pSetCancel;

	CINFSecuEditBox*	m_pINFPassEditBox;
	CINFSecuEditBox*	m_pINFSecuChangeEditBox;
	CINFSecuEditBox*	m_pINFSecuComfirmEditBox;

	int				m_nSelEdit;
};

#endif // !defined(AFX_INFSECUCHANPASSWND_H__A654CF1F_7C64_4C17_80E8_65FE24160372__INCLUDED_)
