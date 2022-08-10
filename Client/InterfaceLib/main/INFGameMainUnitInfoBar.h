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
//추가 - 문자출력을 위해서
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

// 2006-08-29 by dgwoo 각종 이벤트 관련 정보
struct EVENT_INFO
{//추가되는 요소를 변수로 추가...
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
// 2007-11-28 by dgwoo 선물메시지 구조체.
#define	GIFT_ICON_IMG_COUNT				2				// 선물 이미지 갯수.

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
	void			RenderCityUpInfo();							// 도시에서 사용
	void			RenderSpeed();
	void			HideRender();								// GUI가 숨겨진 상황(F키)에서 Render()
	void			RenderMainGage(BOOL bShowAll = TRUE);
	void			RenderGageString(BOOL bShowAll = TRUE);
	void			RenderPremiumCard(BOOL bIsCity);			// PremiumCard 렌더링
	void			RenderMapPosition(UINT x, UINT y);
	BOOL			RenderCurrentEvent(UINT x, UINT y);
	void			RenderHappyHourEvent(BOOL bIsCity);
	void			RenderTextHappyHourEvent();					
	void			RenderEventRecovery();
	void			RenderStringBar();
	void			RenderGiftIcon(BOOL i_bCity);							// 2007-11-28 by dgwoo 선물 받았을 경우 아이콘.

	virtual void	Tick();
	virtual int		WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int				WndProcCity(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int				GetMaxSize(int nNum);						// nNum의 자리수를 구한다.
	int				CutOffFirstNumber(int& nNum,int nMaxNum);	// nNum의 첫자리를 자른다 - 짤린값 리턴.
	void			ShowMapNameTitle(UINT x, UINT y);							// 게임 타이틀 바에 맵이름 표시
	BOOL			IsRenderMapName();					// 마우스 포인터가 레이더에 위치 하지 않으면 맵이름 렌더링	

	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	BOOL			IsHappyHourEvent();
	BOOL			IsHappyHourPcBang();
	void			SetHappyHourInfluence(BOOL bLevelup, BOOL bHappyHour, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	void			SetHappyHourPcBang(BOOL bLevelup, BOOL bPcBang, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	void			InitHappyHourInfo();
	void			AddGiftMsg(UINT i_NotifyMsgUID,UINT i_CharacterUID,char * NotifyString);
	void			DeleteGiftMsg();

	// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
	void			SetHappyHourMotherShip(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	void			SetHappyHourItem(BOOL bLevelup, BOOL bStart, MSG_FC_INFO_GET_HAPPY_HOUR_EVENT_INFO_OK* pMsg);
	// end 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가

protected:

	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	// 2008-03-14 by bhsohn 레벨업에 따른 해피아우어 처리
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
	
	// 2004-12-08 by jschoi - 추가
	CINFImage*		m_pImgMainGageBack;										// 메인 게이지 배경(좌상단)
	CINFImage*		m_pImgMainExpBack;										// 메인 경험치 배경(중앙하단)
	CINFImage*		m_pImgMainExpBar;										// 메인 경험치 막대(중앙하단)
	CINFImage*		m_pImgMainGageHP[GAMEMAIN_GAGE_HP_MAX_GRADE];			// 메인 게이지 HP
	CINFImage*		m_pImgMainGageDP[GAMEMAIN_GAGE_DP_MAX_GRADE];			// 메인 게이지 DP
	CINFImage*		m_pImgMainGageSP[GAMEMAIN_GAGE_SP_MAX_GRADE];			// 메인 게이지 SP
	CINFImage*		m_pImgMainGageBooster[GAMEMAIN_GAGE_BOOSTER_MAX_GRADE];	// 메인 게이지 Booster
	CINFImage*		m_pImgMainGageFuel[GAMEMAIN_GAGE_FUEL_MAX_GRADE];		// 메인 게이지 Fuel
	CINFImage*		m_pImgMainIconFuel[2];									// 메인 아이콘 Fuel
	CINFImage*		m_pImgMainSpeedNum;										// 메인 디지털 스피드
	CINFImage*		m_pImgMainMinus;										// 메인 디지털 스피드 마이너스(추가)	
	CINFImage*		m_pImgMainWarning;										// 메인 경고
	CINFImage*		m_pImgGeneralPremiumCard;								// General Premium Card Image

	// 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가

	BOOL			m_bPremiumToolTip;

	// end 2009. 03. 16 by ckPark 멤버쉽 툴팁 추가

	CINFImage*		m_pImgSuperPremiumCard;									// Super Premium Card Image
	CINFImage*		m_pImgHappyHourEvent;									// 해피아워 관련 이벤트 이미지
	CINFImage*		m_pImgPCHappyHourEvent;									// PC방 해피아워 관련 이벤트 이미지
	CINFImage*		m_pImgPCHomePremiumEvent;								// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	CINFImage*		m_pImgEventRecovery[GAMEMAIN_EVENT_RECOVERY_MAX];		// 이벤트 회복율 관련 이벤트 이미지
	CINFImage*		m_pImgGiftIcon[GIFT_ICON_IMG_COUNT];					// 선물 아이콘 이미지 
	//CINFImageBtn*	m_pImgVoiceChatIcon;									// 음성채팅 아이콘.
	CINFImage*	m_pImgVoiceChatIcon;									// 음성채팅 아이콘.
	CINFImage*		m_pImgVoiceSPKIcon;									// 스피커 아이콘.
	CD3DHanFont*	m_pFontEventRecovery;									// 이벤트 회복율 내용

	float			m_fGageRate[GAMEMAIN_GAGE_NUMBER];

	CD3DHanFont*	m_pFontGageInfo[GAMEMAIN_GAGE_LINE_NUMBER];
	char			m_szGageInfo[GAMEMAIN_GAGE_LINE_NUMBER][GAMEMAIN_GAGE_LINE_LENGTH];	

	CD3DHanFont*	m_pFontUnitPosInfo;

//	CINFImage*		m_pButtonShowHide[2][BUTTON_STATE_NUMBER];	//	GAMEMAIN_BUTTON_SHOW, GAMEMAIN_BUTTON_HIDE
	int				m_nButtonState;

	// 맵이름 표시
	CD3DHanFont*	m_pFontMapName;
	
	// 현재 이벤트 표시
	CD3DHanFont*	m_pFontCurrentEvent;
	CD3DHanFont*	m_pFontEventHappyHour;

	D3DXVECTOR2		m_v2MousePt;
	D3DXVECTOR2		m_v2RaderCenter;

	// 미션 이름 표시
	CD3DHanFont*	m_pFontMissionName;	

public:
	vector<string>	m_vecEventHappyHour;
	vector<GIFT_NOTIFY_MSG> m_vecGiftMsg;
	EVENT_INFO		m_HappyEventInfo;
	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	EVENT_INFO		m_HappyEventAllInfluInfo;		

	EVENT_INFO		m_PCHappyEventInfo;
	BOOL			m_bRenderEvent;
	BOOL			m_bRenderEventRecovery;
	int				m_nHappyHourX;
	int				m_nHappyHourY;
	int				m_nPCHappyHourX;
	int				m_nPCHappyHourY;
	BOOL			m_bMemberPCBang;
	// 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	BOOL			m_pMemberPremiumEvent;
	//end 2010. 06. 08 by jskim 홈프리미엄 UI 작업
	//--------------------------------------------------------------------------//
	//			m_BHappyHourEvent Flag				
	//			0x01				HappyHourEvent		해피 아워 이벤트
	//			0x10				PCHappyHourEvent	PC해피 아워 이벤트.
	//--------------------------------------------------------------------------//
	// 2007-11-01 by bhsohn 해피 아우어 이벤트 처리 방식 변경
	//BYTE			m_BHappyHourEvent;				
	BYTE			m_byHappyHourInfluence;
	BOOL			m_bHappyHourAllInfluence;
	BOOL			m_bPcBangHappyHour;
	
	// 2008-05-21 by bhsohn 모선전, 아이템 해피 아우어 추가
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
