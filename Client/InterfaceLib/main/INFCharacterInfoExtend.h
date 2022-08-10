// INFCharacterInfoExtend.h: interface for the CINFCharacterInfoExtend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCHARACTERINFOEXTEND_H__F4A3ED92_70D3_48E3_BE94_8B21CBDB874D__INCLUDED_)
#define AFX_INFCHARACTERINFOEXTEND_H__F4A3ED92_70D3_48E3_BE94_8B21CBDB874D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
//#include "INFInven.h"


#define CHARACTER_INFO		0
#define CHARACTER_AMMO		1
#define CHARACTER_UTC		2
#define CHARACTER_ARENA		3
#define CHARACTER_PARTNER	4		// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

#define CHARACTER_INTERFACE_FONT_NUM		6

#define STAT_ATTACK			0
#define STAT_DURABILITY		1
#define STAT_FUEL			2
#define STAT_INDUCTION		3
#define STAT_AVOID			4
#define STAT_KALISMA		5
#define STAT_NONE			8

#define STAT_BUTTON_DISABLE		0
#define STAT_BUTTON_UP			1
#define STAT_BUTTON_DOWN		2

#define CHAR_UTC_TYPE_NUMBER	4
#define CHAR_UTC_SLOT_NUMBER	5
#define MAX_CHAR_UTC_SLOT_NUMBER	10

#define C_QUEST_LIST_NUM		6
#define C_QUEST_DESC_NUM		5

// 2007-05-15 by bhsohn ��� ���� ���� ó��
#define STAT_SHUTTLEINFO_ATTACK		0		// ����
#define STAT_SHUTTLEINFO_DEFENCE	1		// ���
#define STAT_SHUTTLEINFO_FUEL		2		// ����
#define STAT_SHUTTLEINFO_SOUL		3		// ����
#define STAT_SHUTTLEINFO_DODGE		4		// ȸ��
#define STAT_SHUTTLEINFO_SHIELD		5		// ����
#define	MAX_STAT_SHUTTLEINFO		6

class CD3DHanFont;
class CINFImage;
class CAtumNode;
class CINFScrollBar;
class CSkillInfo;
class CINFImageBtn;		// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
class CINFArenaScrollBar;	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
class CINFCharacterInfoExtend : public CINFBase
{
public:
	CINFCharacterInfoExtend(CAtumNode* pParent);
	virtual ~CINFCharacterInfoExtend();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	void Render();
	void RenderSkillInShop();
	virtual void Tick();

	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int InfoWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int UTCWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int AmmoWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int WndProcSkillInShop(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int QuestWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int ArenaWndProc(UINT uMsg,WPARAM wParam,LPARAM lParam);
	int PartnerWndProc(UINT uMsg,WPARAM wParam,LPARAM lParam); // 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

	void SetAllUTCInfo();
	void SetSelectUTC( INVEN_DISPLAY_INFO* pDisplayInfo );
	void SendUseSkill( ITEM_BASE* pSkill );

	int GetCharacterQuestCount();
	void SetQuestDesc(int nQuestWindowDataIndex);
	int GetUtcMaxScrollNumber();
	void RenderShowStatInfo() ;
	void SendDeleteSelectItemSkill();
	void RenderNonQuest(int nWindowPosY, int nLine);
	void RenderStatDescToolTip(int nType, int x, int y);

	BOOL CheckUseSkillApprovalEnd(ITEM_BASE* pSkill);

	// 2008-09-22 by bhsohn EP3 ĳ���� â
	void SetCharacterInfoType(int nCharacterInfoType);
	BOOL IsShowWnd();
	void ShowCharacterInfoWnd(BOOL bShowWnd, POINT* pPos=NULL);
	void GetItemAttackInfo(CItemInfo *pItemInfo, char* o_pDstBuff);
	BOOL IsEnableItem(ITEM* pITEM);
	float GetDefaultPierce(BOOL bIsPrimaryAttack);
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	void Patner3D();
	void PatnerInfo();
	void PatnerDtail();
	void LevelExpBar( const Experience_t a_ExpNow , const Experience_t a_ExpMax );
	void StaminaBar( const int a_StaminaNow , const int a_StaminaMax );
	void StateBarUpdate();
	void ExpScrollUpdate();
	void SetBar(CINFImage* Image1, CINFImage* Image2, float MaxValue, float Value, float x, float y);
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ���� ������ ���� �Ѱ��ֱ�.
	void GetPtr_AttachmentedPetInfo ( INVEN_DISPLAY_INFO **o_ppInvenDisplayInfo , tPET_CURRENTINFO **o_ppPetCurInfo , tPET_BASEDATA **o_ppPetBaseData , tPET_LEVEL_DATA **o_ppPetLevelData );

public:
	BOOL					m_bRestored;
	ITEM_SKILL*			m_pDeleteSkill;// ���� ��ų ������(reference)


private:	
	BOOL					m_bInvalidated;

	//CINFImage			*	m_pAmmo;
	//CINFImage			*	m_pStatImage ;
	//CINFImage			*	m_pStat[3];
	CINFImage			*	m_pInfo;
	CINFImage			*	m_pInoBk;
	//CINFImage			*	m_pId;
	CINFImage			*	m_pUtc;
	CINFImage			*	m_pUtcScr;
//	CINFImage			*	m_pQuest;
//	CINFImage			*	m_pImgArenaTab;
	CINFImage			*	m_pQuestSelect;
	CINFImage			*	m_pSkillShopBack;
//	CINFImage			*	m_pScrollBar;
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	CINFImage			*	m_pPartnerInfoBk;
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â

	CD3DHanFont			*   m_CharacInfoFont[5];
	CD3DHanFont			*   m_StatInfoFont[7];
	CD3DHanFont			*	m_pFontName;
	CD3DHanFont			*	m_pFontLevel;
	CD3DHanFont			*	m_pFontGuild;
	CD3DHanFont			*	m_pFontGeneral;
	CD3DHanFont			*	m_pFontPropensity;
	CD3DHanFont			*	m_pFontItemNum[MAX_CHAR_UTC_SLOT_NUMBER];

	CD3DHanFont			*	m_pFontQuestList[C_QUEST_LIST_NUM];
//	CD3DHanFont			*	m_pFontQuestState[6];
	CD3DHanFont			*	m_pFontQuestDesc[C_QUEST_DESC_NUM];
	CD3DHanFont			*	m_pFontAmmoWeapon[CHARACTER_INTERFACE_FONT_NUM];	// 1�� ����/����, 2�� ����/��Ƽ��, ���, ȸ��
	CD3DHanFont			*	m_pFontAutoStat;
	CD3DHanFont			*	m_pFontStatDec;

	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	CINFImageBtn		*	m_pChangeNameBtn;		// �̸� ���� ��ư

	CD3DHanFont			*	m_pPartnerName;			// ��Ʈ�� �̸�
	CD3DHanFont			*	m_pPartnerLv;			// ��Ʈ�� ����
	CD3DHanFont			*	m_pPartnerType;			// ��Ʈ�� Ÿ�� ( ������, �����, ������, ���λ���)
	CD3DHanFont			*	m_pStamina;				// ��Ʈ�� ���׹̳�
	CD3DHanFont			*	m_pPartnerLvBar;		// ��Ʈ�� ������
	CD3DHanFont			*	m_pPartnerStaminaBar;	// ��Ʈ�� ���׹̳ʹ�
	CD3DHanFont			*	m_pPartnerGiveExp;		// ��Ʈ�ʿ��� �Ѱ��� ����ġ �ۼ�Ʈ

	
	CINFImage			*	m_pPartnerImageLvBar[2];		// ��Ʈ�� ������
	CINFImage			*	m_pPartnerImageStaminaBar[2];	// ��Ʈ�� ���׹̳ʹ�

	CINFArenaScrollBar	*	m_pExpScroll;			// ��Ʈ�� ����ġ ȹ�� Ȯ�� ��ũ�ѹ�

	
	CINFImage			*	m_pPartnerImage;
	CINFImageBtn		*	m_pPartnerBtnCancel;
	CINFImageBtn		*	m_pPartnerBtnOK;

	//2011. 03. 08 by jhAhn ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â(UI����)
	CINFImage			*	m_pPartnerSocet;
	CINFImage			*	m_pPartnerSocetClose;
	CINFImage			*	m_pPartnerSocetSelect;
	//end 2011. 03. 08 by jhAhn ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â(UI����)


	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	int						m_nCharacterInfoType;
	int						m_nStatType ;
	int						m_nButtonState ;
	int						m_nMissionProCount;		// ������ �̼� ī��Ʈ



	int					m_nCurrentUTCScroll;
	
	INVEN_DISPLAY_INFO	m_pSkillShopSkillDisplayInfo[CHAR_UTC_TYPE_NUMBER][MAX_CHAR_UTC_SLOT_NUMBER];
	INVEN_DISPLAY_INFO	m_pCharacterSkillDisplayInfo[CHAR_UTC_TYPE_NUMBER][MAX_CHAR_UTC_SLOT_NUMBER];

	CINFImage*			m_pSelectIcon;// ���콺 Ŭ���� ���� ���õ� ������ �̹���(reference)
	ITEM_SKILL*			m_pSelectSkill;// ��ų ������(reference)	
	BOOL				m_bUTCScrollLock;
	POINT				m_ptMouse;

//	int					m_nCurrentQuestListScroll;
//	int					m_nCurrentSelectQuestList;
//	BOOL				m_bQuestListLock;
//	int					m_nCurrentQuestDescScroll;
//	int					m_nCurrentSelectQuestDesc;
//	BOOL				m_bQuestDescLock;
	int					m_nRenderMoveIconIntervalWidth;
	int					m_nRenderMoveIconIntervalHeight;

	CINFScrollBar*		m_pQuestListScrollBar;
	CINFScrollBar*		m_pQuestDescScrollBar;
	vector<string>		m_vecQuestDescription;
	int					m_nOldQuestSelectDataIndex;

	CINFScrollBar*		m_pShopSkillScrollBar;
	BOOL				m_bLbuttonDown;	
//	BOOL				m_bToolTipStat;				// 2005-07-04 by ispark �ڵ� ���� �й� ����

private:
	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	void				GetStatShowInfo();
	void				RenderCharacterInfo();
	void				RenderCommandInfo();
	void				RenderSkillInfo();
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	void				RenderPartnerInfo();
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	void				OnClickStat(int nPos);
	void				UpdateBtnPos();
	BOOL				IsMouseCaps(POINT ptPos);
	void				GetDefenceRateString(BOOL bIsPrimaryAttack, char* pDefaultRate, char* pArmorRate, char* pPetRate);
	void				GetDodgeRateString(BOOL bIsPrimaryAttack, char* pDefaultRate, char* pArmorRate, char* pPetRate);
	void				RenderWeightStats();

	// 2008-12-16 by bhsohn A��� ������Ƽ�� ��ų ����� ���� ��ų ���� ���������� ��ų ���
	void				RefreshAGearSkillInfo(int nSkillItemNum);

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	void				OnClickNickNameBtn();
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���


private:
	// 2007-05-15 by bhsohn ��� ���� ���� ó��
	CD3DHanFont			*   m_StatInfoBoldFont;		// �β��� �۾�ü 
	CD3DHanFont			*   m_StatOverInfoFont;
	BOOL					m_bStatShow[MAX_STAT_SHUTTLEINFO];
	BOOL					m_nShowOverStat[MAX_STAT_SHUTTLEINFO];

	// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
	CINFImageBtn*			m_pOpenBtn;			// �ݱ�	
	CINFImageBtn*			m_pCloseBtn;
	
	
	CINFImageBtn*			m_pBonusStatBtn[MAX_STAT_SHUTTLEINFO];			// ���ʽ� ����

	POINT					m_ptBkPos;
	BOOL					m_bShowWnd;

	BOOL						m_bMove;
	POINT						m_ptCommOpMouse;

	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	CINFImageBtn*			m_pNickNameBtn;
	CD3DHanFont*			m_pFontNickName;
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
};

#endif // !defined(AFX_INFCHARACTERINFOEXTEND_H__F4A3ED92_70D3_48E3_BE94_8B21CBDB874D__INCLUDED_)
