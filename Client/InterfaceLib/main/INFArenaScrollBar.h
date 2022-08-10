// INFArenaScrollBar.h: interface for the CINFArenaScrollBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFARENASCROLLBAR_H__B39A7475_C9CD_4F06_BED7_7E4AF3CC067E__INCLUDED_)
#define AFX_INFARENASCROLLBAR_H__B39A7475_C9CD_4F06_BED7_7E4AF3CC067E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CINFImage;

class CINFArenaScrollBar  : public CINFBase
{
public:
	CINFArenaScrollBar();
	virtual ~CINFArenaScrollBar();

	HRESULT InitDeviceObjects(int i_nOneStepCnt,char* i_pszScrollBk, char* i_pszScrollBtn);
	HRESULT CINFArenaScrollBar::InitDeviceObjects(int i_nOneStepCnt, char* i_pszScrollBtn);
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	void	Render();
	virtual void	Tick();

	void SetMaxItem(int i_nMaxItem);
	void SetMouseWhellRect(RECT rcMouse);
	void SetMouseBallRect(RECT rcMouse);
	BOOL IsMouseWhellPos(POINT ptPos);
	BOOL IsMouseBallPos(POINT ptPos);
	BOOL IsMouseScrollPos(POINT ptPos);

	void SetPosition(float i_fPosX, float i_fPosY,float i_fWidth, float i_fHeight);
	
	int OnMouseWheel(WPARAM wParam, LPARAM lParam);
	void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	void SetMouseMoveMode(BOOL bMode);
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��ũ�ѹ� X�̵� ����
	//void SetScrollPos(POINT i_ptPos);
	void SetScrollPos(POINT i_ptPos, BOOL IsPosX = FALSE);
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��ũ�ѹ� X�̵� ����

	POINT GetImgBkSize();

	int GetScrollStep();	
	BOOL GetMouseMoveMode();
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��ũ�ѹ� X�̵� ����
	//void SetOnlyMaxItem(int i_nMaxItem);
	void SetOnlyMaxItem(int i_nMaxItem , BOOL IsPosX = FALSE);	
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��ũ�ѹ� X�̵� ����


	void SetBallRenderHeight(int nPosY);

	void SetScrollStep(int nStep);

	int GetMaxStepCnt();

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	// �� ������ ���´�
	inline	RECT	GetMouseWheelRect( void )
	{
		return m_rcMouseWhell;
	}
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


private:	
	CINFImage	*	m_pScrollButton;
	CINFImage	*	m_pScrollBk;

	float			m_fScrollPosX;
	float			m_fScrollPosY;

	float			m_fScrollBallPosX;
	float			m_fScrollBallPosY;

	float			m_fScrollWidth;
	float			m_fScrollHeight;

	int				m_nOneStep;
	int				m_nMaxStepCnt;
	int				m_nScrollPos;
	
	int				m_nScrollStep;

	RECT			m_rcMouseWhell;
	RECT			m_rcMouseBall;

	BOOL			m_bMouseMode;

	RECT			m_rcBallRender;

	BOOL			m_bBallRender;

};

#endif // !defined(AFX_INFARENASCROLLBAR_H__B39A7475_C9CD_4F06_BED7_7E4AF3CC067E__INCLUDED_)
