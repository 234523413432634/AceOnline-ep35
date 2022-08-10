// INFCommunityUserOpenSetup.h: interface for the CINFCommunityUserOpenSetup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCOMMUNITYUSEROPENSETUP_H__6F69520C_4A61_4147_A99B_A4CB4A790E1D__INCLUDED_)
#define AFX_INFCOMMUNITYUSEROPENSETUP_H__6F69520C_4A61_4147_A99B_A4CB4A790E1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

// ���� ���� ���� 
#define		OPENSETUP_INFO_DEGREE	0	// ���
#define		OPENSETUP_INFO_POS		1	// ��ġ
#define		OPENSETUP_INFO_HONOR	2	// ��
#define		OPENSETUP_INFO_BELONG	3	// �Ҽ�
#define		OPENSETUP_INFO_CONTIME	4	// ���� ������
#define		MAX_OPENSETUP_INFO		5

// On/Off
#define		OPENSETUP_ON			0
#define		OPENSETUP_OFF			1
#define		MAX_OPENSETUP_CNT		2

class CINFCommunityUserOpenSetup  : public CINFBase
{
public:
	CINFCommunityUserOpenSetup(CAtumNode* pParent);
	virtual ~CINFCommunityUserOpenSetup();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Tick();
	void	Render();

	int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void ShowWindow(BOOL bShow, BOOL bCharacter);
	BOOL IsShowWindow();
	
private:
	BOOL IsMouseCaps(POINT ptPos);
	void UpdateUIPos();
	
	void UpdateRadioBtn();			

	void OnClickGuildInfo(int nMainId, int nSubId);
	void OnClickNormalInfo(int nMainId, int nSubId);

	void InitControl();
	int GetChangeOptionInfo();
	void OnApply();

	
private:
	CINFImage*	m_pBkImage;	

	BOOL		m_bMove;
	BOOL		m_bShow;

	POINT					m_ptCommOpBk;
	POINT					m_ptCommOpMouse;	

	CINFImageBtn*			m_pCloseBtn;			// �ݱ�
	CINFImageBtn*			m_pOkBtn;				// ����
	CINFImageBtn*			m_pXCloseBtn;			// �ݱ�

	// ���� ����
	CINFImageRadioBtn*		m_pRadioGuildInfo[MAX_OPENSETUP_INFO][MAX_OPENSETUP_CNT];	// ����
	BOOL					m_bGuildInfo[MAX_OPENSETUP_INFO];

	CINFImageRadioBtn*		m_pRadioUserInfo[MAX_OPENSETUP_INFO][MAX_OPENSETUP_CNT];	// �Ϲ�
	BOOL					m_bNormalInfo[MAX_OPENSETUP_INFO];

};

#endif // !defined(AFX_INFCOMMUNITYUSEROPENSETUP_H__6F69520C_4A61_4147_A99B_A4CB4A790E1D__INCLUDED_)
