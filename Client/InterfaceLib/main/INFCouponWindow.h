// INFCouponWindow.h: interface for the CINFCouponWindow class.
// // 2008-01-07 by dgwoo 쿠폰 시스템.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCOUPONWINDOW_H__33BDBA33_62DA_4D66_B66F_3E2ACFB66378__INCLUDED_)
#define AFX_INFCOUPONWINDOW_H__33BDBA33_62DA_4D66_B66F_3E2ACFB66378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFImageBtn.h"

#define MAX_COUPON_NUMBER_SIZE			(SIZE_MAX_COUPON_NUMBER+1)
class CINFCouponWindow  : public CINFBase  
{
public:
	CINFCouponWindow(CAtumNode* pParent);
	CINFCouponWindow();
	virtual ~CINFCouponWindow();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void InitCouponNumber();
	void SetShow(BOOL i_bShow);
	void SetWindowPoint(POINT i_ptWindow);
	void SetString(char * i_pChar,INT nSize);
	void SendCouponNumber();
	void SetActive(MSG_FC_EVENT_COUPON_EVENT_INFO* pMsg);
private:
	BOOL			m_bShow;

	CINFImageBtn*	m_pImgOkB;
	CINFImageBtn*	m_pImgCancelB;
	CINFImage*		m_pImgBackGround;
	CD3DHanFont	*	m_pFont;								// 쿠폰 번호.


	POINT			m_ptWindow;								// 윈도우 창 위치.


	//--------------------------------------------------------------------------//
	//  DATA

	char			m_strCouponNumber[MAX_COUPON_NUMBER_SIZE];
	MSG_FC_EVENT_COUPON_EVENT_INFO m_CouponInfo;
};

#endif // !defined(AFX_INFCOUPONWINDOW_H__33BDBA33_62DA_4D66_B66F_3E2ACFB66378__INCLUDED_)
