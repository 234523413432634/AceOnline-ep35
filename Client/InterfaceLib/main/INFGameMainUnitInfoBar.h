// INFGameMainUnitInfoBar.h: interface for the CINFGameMainUnitInfoBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFGAMEMAINUNITINFOBAR_H__D89CEB23_A523_4B16_A8DD_203B1EEFA70F__INCLUDED_)
#define AFX_INFGAMEMAINUNITINFOBAR_H__D89CEB23_A523_4B16_A8DD_203B1EEFA70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

#define GAMEMAIN_BACK_UP_PIXEL			0
#define GAMEMAIN_BACK_DOWN_PIXEL		1

#define GAMEMAIN_GAGE_HP_UP				0
#define GAMEMAIN_GAGE_DP_UP				1
#define GAMEMAIN_GAGE_BURN_UP			2
#define GAMEMAIN_GAGE_SP_UP				3
#define GAMEMAIN_GAGE_EP_UP				4
#define GAMEMAIN_GAGE_SPEED_UP			5
#define GAMEMAIN_GAGE_EXP_UP			6
//�߰� - ��������� ���ؼ�
#define GAMEMAIN_NEW_STRING_HP			7
#define GAMEMAIN_NEW_STRING_MAX_HP		8
#define GAMEMAIN_NEW_STRING_DP			9
#define GAMEMAIN_NEW_STRING_MAX_DP		10
#define GAMEMAIN_NEW_STRING_MAX_SP		11

#define GAMEMAIN_GAGE_NUMBER			9		
#define GAMEMAIN_GAGE_LINE_NUMBER		12		
#define GAMEMAIN_GAGE_LINE_LENGTH		32

#define GAMEMAIN_BUTTON_SHOW			0
#define GAMEMAIN_BUTTON_HIDE			1

#define GAMEMAIN_GAGE_HP_MAX_GRADE		20
#define GAMEMAIN_GAGE_DP_MAX_GRADE		20
#define GAMEMAIN_GAGE_SP_MAX_GRADE		20
#define GAMEMAIN_GAGE_BOOSTER_MAX_GRADE	18
#define GAMEMAIN_GAGE_FUEL_MAX_GRADE	17

#define GAMEMAIN_EVENT_RECOVERY_MAX		5

// 2006-08-29 by dgwoo ���� �̺�Ʈ ���� ����
struct EVENT_INFO
{//�߰��Ǵ� ��Ҹ� ������ �߰�...
	float			fEXPRate;
	float			fSPIRate;
	float			fEXPRepairRate;
	float			fDropItemRate;
	float			fDropRareRate;
	float			fWarPointRate;
	EVENT_INFO(){
		fEXPRate = 0;
		fSPIRate = 0;
		fEXPRepairRate = 0;
		fDropItemRate = 0;
		fDropRareRate = 0;
		fWarPointRate = 0;
	};
};
// 2007-11-28 by dgwoo �����޽��� ����ü.
#define	GIFT_ICON_IMG_COUNT				2				// ���� �̹��� ����.

struct GIFT_NOTIFY_MSG
{
	UID64_t		NotifyMsgUID;
	UID64_t		CharacterUID;
	char		NotifyMsgString[SIZE_MAX_NOTIFY_MSG_STRING];
};

class CINFImage;
class CINFImageBtn;
class CD3DHanFont;
class CINFGameMainUnitInfoBar : public CINFBase  
{
public:
	CINFGameMainUnitInfoBar(CAtumNode* pParent);
	virtual ~CINFGameMainUnitInfoBar();

	void			UpdateAllGage();
	void			SetHP(float fCurrent, float fMax);
	void			SetDP(float fCurrent, float fMax);
	void			SetBURN(float fCurrent, float fMax);
	void			SetSP(float fCurrent, float fMax);
	void			SetEP(float fCurrent, float fMax);
	void			SetSpeed(float fCurrent, float fMin, float fMax);
	void			SetEXP(float fExp);
	void			SetHappyHourEventIconPos();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	void			Render();
	void			RenderCityUpInfo();							// ���ÿ��� ���
	void			RenderSpeed();
	void			HideRender();								// GUI�� ������ ��Ȳ(FŰ)���� Render()
	void			RenderMainGage(BOOL bShowAll = TRUE);
	void			RenderGageString(BOOL bShowAll = TRUE);
	void			RenderPremiumCard(BOOL bIsCity);			// PremiumCard ������
	void			RenderMapPosition(UINT x, UINT y);
	BOOL			RenderCurrentEvent(UINT x, UINT y);
	void			RenderHappyHourEvent(BOOL bIsCity);
	void			RenderTextHappyHourEvent();					
	void			RenderEventRecovery();
	void			RenderStringBar();
	void			RenderGiftIcon(BOOL i_bCity);							// 2007-11-28 by dgwoo ���� �޾��� ��� ������.

	virtual void	Tick();
	virtual int		WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int				WndProcCity(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int				GetMaxSize(int nNum);						// nNum�� �ڸ����� ���Ѵ�.
	int				CutOffFirstNumber(int& nNum,int nMaxNum);	// nNum�� ù�ڸ��� �ڸ��� - ©���� ����.
	void			ShowMapNameTitle(UINT x, UINT y);							// ���� Ÿ��Ʋ �ٿ� ���̸� ǥ��
	BOOL			IsRenderMapName();					// ���콺 �����Ͱ� ���̴��� ��ġ ���� ������ ���̸� ������	

	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	BOOL			IsHappyHourEvent();
	BOOL			IsHappyHourPcBang();
	void			SetHappyHourInfluence(BOOL bLevelup, BOOL bHappyHour, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	void			SetHappyHourPcBang(BOOL bLevelup, BOOL bPcBang, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	void			InitHappyHourInfo();
	void			AddGiftMsg(UINT i_NotifyMsgUID,UINT i_CharacterUID,char * NotifyString);
	void			DeleteGiftMsg();

	// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
	void			SetHappyHourMotherShip(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	void			SetHappyHourItem(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	// end 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�

protected:

	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	// 2008-03-14 by bhsohn �������� ���� ���Ǿƿ�� ó��
	void			SetHappyHourInfo(BOOL bLevelup, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg, EVENT_INFO* pEventInfo);	
	void			UpdateHappyHourTooltip();	

	void			CreateMsgBox();
	


protected:
	BOOL			m_bRestored;
	BOOL			m_bRenderMapName;
	float			m_fWarningTime;
	BOOL			m_bWarning;
	CINFImage*		m_pImgBackPixel[2];	
	CINFImage*		m_pImgBackMinimap;
	
	// 2004-12-08 by jschoi - �߰�
	CINFImage*		m_pImgMainGageBack;										// ���� ������ ���(�»��)
	CINFImage*		m_pImgMainExpBack;										// ���� ����ġ ���(�߾��ϴ�)
	CINFImage*		m_pImgMainExpBar;										// ���� ����ġ ����(�߾��ϴ�)
	CINFImage*		m_pImgMainGageHP[GAMEMAIN_GAGE_HP_MAX_GRADE];			// ���� ������ HP
	CINFImage*		m_pImgMainGageDP[GAMEMAIN_GAGE_DP_MAX_GRADE];			// ���� ������ DP
	CINFImage*		m_pImgMainGageSP[GAMEMAIN_GAGE_SP_MAX_GRADE];			// ���� ������ SP
	CINFImage*		m_pImgMainGageBooster[GAMEMAIN_GAGE_BOOSTER_MAX_GRADE];	// ���� ������ Booster
	CINFImage*		m_pImgMainGageFuel[GAMEMAIN_GAGE_FUEL_MAX_GRADE];		// ���� ������ Fuel
	CINFImage*		m_pImgMainIconFuel[2];									// ���� ������ Fuel
	CINFImage*		m_pImgMainSpeedNum;										// ���� ������ ���ǵ�
	CINFImage*		m_pImgMainMinus;										// ���� ������ ���ǵ� ���̳ʽ�(�߰�)	
	CINFImage*		m_pImgMainWarning;										// ���� ���
	CINFImage*		m_pImgGeneralPremiumCard;								// General Premium Card Image

	// 2009. 03. 16 by ckPark ����� ���� �߰�

	BOOL			m_bPremiumToolTip;

	// end 2009. 03. 16 by ckPark ����� ���� �߰�

	CINFImage*		m_pImgSuperPremiumCard;									// Super Premium Card Image
	CINFImage*		m_pImgHappyHourEvent;									// ���Ǿƿ� ���� �̺�Ʈ �̹���
	CINFImage*		m_pImgPCHappyHourEvent;									// PC�� ���Ǿƿ� ���� �̺�Ʈ �̹���
	CINFImage*		m_pImgPCHomePremiumEvent;								// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	CINFImage*		m_pImgEventRecovery[GAMEMAIN_EVENT_RECOVERY_MAX];		// �̺�Ʈ ȸ���� ���� �̺�Ʈ �̹���
	CINFImage*		m_pImgGiftIcon[GIFT_ICON_IMG_COUNT];					// ���� ������ �̹��� 
	//CINFImageBtn*	m_pImgVoiceChatIcon;									// ����ä�� ������.
	CINFImage*	m_pImgVoiceChatIcon;									// ����ä�� ������.
	CINFImage*		m_pImgVoiceSPKIcon;									// ����Ŀ ������.
	CD3DHanFont*	m_pFontEventRecovery;									// �̺�Ʈ ȸ���� ����

	float			m_fGageRate[GAMEMAIN_GAGE_NUMBER];

	CD3DHanFont*	m_pFontGageInfo[GAMEMAIN_GAGE_LINE_NUMBER];
	char			m_szGageInfo[GAMEMAIN_GAGE_LINE_NUMBER][GAMEMAIN_GAGE_LINE_LENGTH];	

	CD3DHanFont*	m_pFontUnitPosInfo;

//	CINFImage*		m_pButtonShowHide[2][BUTTON_STATE_NUMBER];	//	GAMEMAIN_BUTTON_SHOW, GAMEMAIN_BUTTON_HIDE
	int				m_nButtonState;

	// ���̸� ǥ��
	CD3DHanFont*	m_pFontMapName;
	
	// ���� �̺�Ʈ ǥ��
	CD3DHanFont*	m_pFontCurrentEvent;
	CD3DHanFont*	m_pFontEventHappyHour;

	D3DXVECTOR2		m_v2MousePt;
	D3DXVECTOR2		m_v2RaderCenter;

	// �̼� �̸� ǥ��
	CD3DHanFont*	m_pFontMissionName;	

public:
	vector<string>	m_vecEventHappyHour;
	vector<GIFT_NOTIFY_MSG> m_vecGiftMsg;
	EVENT_INFO		m_HappyEventInfo;
	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	EVENT_INFO		m_HappyEventAllInfluInfo;		

	EVENT_INFO		m_PCHappyEventInfo;
	BOOL			m_bRenderEvent;
	BOOL			m_bRenderEventRecovery;
	int				m_nHappyHourX;
	int				m_nHappyHourY;
	int				m_nPCHappyHourX;
	int				m_nPCHappyHourY;
	BOOL			m_bMemberPCBang;
	// 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	BOOL			m_pMemberPremiumEvent;
	//end 2010. 06. 08 by jskim Ȩ�����̾� UI �۾�
	//--------------------------------------------------------------------------//
	//			m_BHappyHourEvent Flag				
	//			0x01				HappyHourEvent		���� �ƿ� �̺�Ʈ
	//			0x10				PCHappyHourEvent	PC���� �ƿ� �̺�Ʈ.
	//--------------------------------------------------------------------------//
	// 2007-11-01 by bhsohn ���� �ƿ�� �̺�Ʈ ó�� ��� ����
	//BYTE			m_BHappyHourEvent;				
	BYTE			m_byHappyHourInfluence;
	BOOL			m_bHappyHourAllInfluence;
	BOOL			m_bPcBangHappyHour;
	
	// 2008-05-21 by bhsohn ����, ������ ���� �ƿ�� �߰�
	BOOL			m_bMotherHappyHour;
	EVENT_INFO		m_MotherShipEventInfo;

	BOOL			m_bItemHappyHour;
	EVENT_INFO		m_ItemEventInfo;
	

	int				m_nGiftX;
	int				m_nGiftY;
	POINT			m_ptGift;
	float			m_fGiftTime;

};

#endif // !defined(AFX_INFGAMEMAINUNITINFOBAR_H__D89CEB23_A523_4B16_A8DD_203B1EEFA70F__INCLUDED_)
