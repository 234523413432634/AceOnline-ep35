// INFOptionSystem.h: interface for the CINFOptionSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOPTIONSYSTEM_H__664F80FC_7B76_47AA_9E60_9F4272DA8E82__INCLUDED_)
#define AFX_INFOPTIONSYSTEM_H__664F80FC_7B76_47AA_9E60_9F4272DA8E82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFGameMainQSlot.h"
#include "INFSystem.h"

class CAtumNode;
class CINFImage;
class CD3DHanFont;
class CINFImageBtn;
class CINFImageRadioBtn;
class CD3DHanFont;
class CINFListBox;

// ������ư ����
#define		OPTION_SYS_ON			0
#define		OPTION_SYS_OFF			1
#define		MAX_OPTION_SYS_CNT		2

// �׷��� �ɼ�  �޸�
#define		OPTION_GRAPHIC_SEE_RANGE		0	// �þ߰Ÿ�
#define		OPTION_GRAPHIC_UNIT_DETAIL		1	// ���� ������
#define		OPTION_GRAPHIC_SHADOW			2	// �׸�������
#define		OPTION_GRAPHIC_EFFECT			3	// ����Ʈ ����
#define		OPTION_GRAPHIC_GAMMA			4	// ���� ����
#define		OPTION_GRAPHIC_CONTRAST			5	// ��� ����
#define		OPTION_GRAPHIC_FILTER			6	// ���� ȿ��
// ��Ÿ �ɼ� �޺�
#define		OPTION_ETC_SEE_CHANGE			7	// ������ȯ
#define		OPTION_ETC_VOLUMNE				8	// ���� ����
#define		MAX_OPTION_GRAPHIC_COMBO		9


// ��Ÿ �ɼ� üũ ��ư
#define		OPTION_ETC_SHOW_MOUSE			0	// ���콺 ������ ���̱�
#define		OPTION_ETC_HELP					1	// �������
#define		OPTION_ETC_OPERATOR				2	// ���۷����� ���
#define		OPTION_ETC_MAINTAIN				3	// ��������
#define		OPTION_ETC_MOUSE_REVERSE_TB		4	// ���콺 ���� ����
#define		OPTION_ETC_MOUSE_REVERSE_LR		5	// ���콺 �¿� ����
// 2010. 10. 26 by jskim �� ���۷����� �ɼ� ó��
//#define		OPTION_ETC_MENU_UNISTOP			6	// �޴� ���� ��������
#define		OPTION_ETC_PET_OP_SYS			6	// �޴� ���� ��������
// end 2010. 10. 26 by jskim �� ���۷����� �ɼ� ó��
#define		OPTION_ETC_MUSIC				7	// Music�÷��̾� ����
#define		MAX_OPTION_ETC_RADIO			8	



typedef struct 
{		
	sOPTION_SYSTEM			struSOptionSetup;
	sOPTION_CHARACTER		struSOptionCharacter;
	sOPTION_ETC				struSOptionEtc;	// �ٸ� �ɼ�
	
	BOOL		bOperator;								// ���۷�����
	
} structOptionGameInfo;


class CINFOptionSystem  : public CINFBase
{
public:	
	CINFOptionSystem(CAtumNode* pParent);
	virtual ~CINFOptionSystem();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	void Render();
	virtual void Tick();

	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void SendFieldSocketCharacterGameEnd();

	void SetComboData(int nIdx, char* pSrc);

	BOOL IsOptionShow();
	void  ShowOptionWnd(BOOL bShow);

	structOptionGameInfo* GetSystemOption();

	void RefreshShowInterface(BOOL bShowInterface);


	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	void	EnableLogOffBtn( BOOL bEnable );
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


private:
	void UpdateBtnPos(int nBackPosX, int nBackPosY);

	int OnLButtonDown(WPARAM wParam, LPARAM lParam);
	int OnMouseMove(WPARAM wParam, LPARAM lParam);
	int OnLButtonUp(WPARAM wParam, LPARAM lParam);

	// �ý��� ��ư Ŭ�� 
	void OnSystemButtonClick(int nButton);

	structOptionGameInfo InitOptionGameInfo();

	// ���� ��ư ����
	void SetRadioInfo(int nMainId, BOOL bOnOff);

	// �ɼ� �������̽� ���� 
	void UpdateOptionInterface(structOptionGameInfo* pOptionInfo);
	// �ɼǰ� ����
	void UpdateOptionInfo();

	// �ּ� ������ Ŭ��
	BOOL OptionQualityCombo();
	void UpdateQuality(sOPTION_SYSTEM* pOption);

	// �׷��ȿɼ� Ŀ������ ���´�.
	int GetGarphicOption_To_Cursel(int nMode, int nState);
	int GetGarphicCursel_To_Option(int nMode, int nCursel);

	// Etc�ɼ�
	int GetEtcOption_To_Cursel(int nMode, int nState);
	int GetEtcCursel_To_Option(int nMode, int nState);

	// ���� ��ư Ŭ��
	void OnClickEtcRadio(int nRadioId);

	// �����ư
	void OnClickApply();

	// ��������
	void UpdateGamma(int nGama);

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	void OnClickJoystciOption();

	
public:
	BOOL				m_bRestored;
	BOOL				m_bInvalidated;
	BOOL				m_bRenderToolTip;

	BOOL			m_bQuitGameMessage;
	BOOL			m_bLogOffGameMessage;
	float			m_fTickSecTime;
	float			m_fLastTickSecTime;
private:
	// �ʱ�ȭ�� ���� ���� ����
	sOPTION_SYSTEM			m_pSOptionOld;
	sOPTION_CHARACTER		m_struSOptionCharacterOld;

	// ���� �¾����Ͽ� ����� ����
	structOptionGameInfo	m_struOpInfo;


	CINFImage	*	m_pOptionBk;
	char			m_strSelectModeComboData[MODE_COMBO_NUMBER][MODE_COMBO_STR_LEN];

	BOOL			m_bShow;		// 

	POINT			m_ptBakPos;		// ��ġ
	POINT			m_ptBakSize;	// ũ��

	
	
	
	CINFImageBtn*	m_pOptionApp;	// ����
	CINFImageBtn*	m_pOptionInit;	// �ʱ�ȭ
	CINFImageBtn*	m_pOptionLogOff;	// �α׿���
	CINFImageBtn*	m_pOptionGameEnd;	// ��������

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	CINFImageBtn*	m_pOptionJoystic;	// ���̽�ƽ �ɼ�

	// �ػ�
	CD3DHanFont *	m_pFontHaeSang;		
	POINT			m_ptHaesangPos;		
	char			m_szHaesangTxt[256];		

	// ���� ��ư 
	CINFImageRadioBtn*		m_pGameOpRadioBtn[MAX_OPTION_RADIO][MAX_OPTION_SYS_CNT];

	// �׷��� �޺� �ڽ�
	CINFListBox *			m_pComboGraphic[MAX_OPTION_GRAPHIC_COMBO];
	CINFImageRadioBtn*		m_pMiniFrame;	// �ʱ�ȭ

	// ��Ÿ �ɼ�	
	CINFImageRadioBtn*		m_pEtcRadio[MAX_OPTION_ETC_RADIO];		

	// �ݱ� ��ư
	CINFImageBtn*			m_pCloseBtn;
	

};

#endif // !defined(AFX_INFOPTIONSYSTEM_H__664F80FC_7B76_47AA_9E60_9F4272DA8E82__INCLUDED_)
