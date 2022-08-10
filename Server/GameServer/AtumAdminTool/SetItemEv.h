#if !defined(AFX_SETITEMEV_H__9A3ACBE4_BE60_4576_B1BD_A3F5F31F58AB__INCLUDED_)
#define AFX_SETITEMEV_H__9A3ACBE4_BE60_4576_B1BD_A3F5F31F58AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetItemEv.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetItemEv dialog
#include "ODBCStatement.h" //For DB Access

class CAtumAdminToolDlg;

#define SIZE_MAX_RARE_DESCRIPTION		1024
struct SRARE_DESCRIPTION
{
	char		szRareDescription[SIZE_MAX_RARE_DESCRIPTION];
	INT			nRareCodeNum;
};
typedef vector<SRARE_DESCRIPTION>		vectRARE_DESCRIPTION;

class CSetItemEv : public CDialog
{
// Construction
public:
//	BOOL SetItemEventButtonCheckUP();	//사용자에게 등록 확인 시켜주는 메세지 박스
	BOOL FindItem();					//존재하는 아이템인지 검색
	CSetItemEv(BOOL i_bInsertItemEv, CWnd* pParent = NULL);   // standard constructor
	~CSetItemEv();

	CODBCStatement				*m_pODBCStmt; //DB 접근 클래스 포인터
	CAtumAdminToolDlg			*m_pMainDlg; //AtumAdminToll 다이얼로그 클래스

	SITEM_EVENT_INFO		m_ItemEv;
	char m_szItemName[SIZE_MAX_ITEM_NAME];

	ez_map<INT, RARE_ITEM_INFO>		m_mapRareItemInfo;
	ez_map<string, RARE_ITEM_INFO>	m_mapRareItemInfoName;

	vectRARE_DESCRIPTION		m_vectRARE_DESCRIPTIONList;

	char *GetRareParameterDescription(char *o_szRareDesc, RARE_ITEM_INFO *i_pRareInfo);
	INT GetRareCodeNumByRareDescription(char *i_szDesc);

	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
	void ResetSetItemEvControl(void);

// Dialog Data
	//{{AFX_DATA(CSetItemEv)
	enum { IDD = IDD_DLG_SET_ITEMEV };
	int		m_nCount;
	int		m_nItemNum;
	int		m_nLevel;
	int		m_nCheckNumber;	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	BOOL	m_bPCBang;
	COleDateTime	m_StartDay;
	COleDateTime	m_StartTime;
	COleDateTime	m_EndDay;
	COleDateTime	m_EndTime;
	COleDateTime	m_LastGameEndDateDay;
	COleDateTime	m_LastGameEndDateTime;
	BOOL	m_bItemEvTypeOnlyone;
	BOOL	m_bItemEvTypeOneDay;
	BOOL	m_bItemEvTypeInflChange;
	BOOL	m_bItemEvTypeLevelUp;
	BOOL	m_bItemEvTypeCouponOnlyOne;
	BOOL	m_bItemEvTypeCouponOneDay;
	BOOL	m_bItemEvTypeLoginEvent; // 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	BOOL	m_bINFL_ANI;
	BOOL	m_bINFL_NORMAL;
	BOOL	m_bINFL_VCN;
	BOOL	m_bINFL_ALL;
	BOOL	m_bMemberShip;
	BOOL	m_bNewMember;
	BOOL	m_bUnitKindBGear;
	BOOL	m_bUnitKindMGear;
	BOOL	m_bUnitKindAGear;
	BOOL	m_bUnitKindIGear;
	INT		m_nItemPrefixCodeNum;
	INT		m_nItemSuffixCodeNum;
	INT		m_nItemKind;
	BOOL	m_bCheckLastGameEndDate;
	BOOL	m_bCheckWithAccountUID;
	BOOL	m_bCheckWithCharacterUID;
	int		m_nLevelMax;
	int		m_nLevelMin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetItemEv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bInsertItemEv;

	// Generated message map functions
	//{{AFX_MSG(CSetItemEv)
	afx_msg void OnSetItemEventButtonOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnITEMEVENTTYPEOnlyOneCHECK();
	afx_msg void OnITEMEVENTTYPEOneDayCHECK();
	afx_msg void OnITEMEVENTTYPEInflChangeCHECK();
	afx_msg void OnITEMEVENTTYPELevelUpCHECK();
	afx_msg void OnITEMEVENTTYPECouponOnlyOneCHECK();
	afx_msg void OnITEMEVENTTYPECouponOneDayCHECK();
	afx_msg void OnITEMEVENTTYPELoginEvent();		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	afx_msg void OnItemEventTypeInflNormalCheck();
	afx_msg void OnItemEventTypeInflVcnCheck();
	afx_msg void OnItemEventTypeInflAniCheck();
	afx_msg void OnItemEventTypeInflAllCheck();
	afx_msg void OnMembershipCheck();
	afx_msg void OnCheckWithAccountUID();
	afx_msg void OnCheckWithCharacterUID();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETITEMEV_H__9A3ACBE4_BE60_4576_B1BD_A3F5F31F58AB__INCLUDED_)
