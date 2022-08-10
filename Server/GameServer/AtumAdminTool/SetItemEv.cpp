// SetItemEv.cpp : implementation file
//

#include "stdafx.h"
#include "atumadmintool.h"
#include "SetItemEv.h"
#include "AtumAdminToolDlg.h"
#include "AtumSJ.h"				// 2006-09-06 by cmkwon

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetItemEv dialog


CSetItemEv::CSetItemEv(BOOL i_bInsertItemEv, CWnd* pParent /*=NULL*/)
	: CDialog(CSetItemEv::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetItemEv)
	m_nCount = 0;
	m_nItemNum = 0;
	m_nLevel = 0;
	m_nCheckNumber = 0;	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 멤버변수 추가
	m_bPCBang = FALSE;
	m_StartDay = COleDateTime::GetCurrentTime();
	m_StartTime = COleDateTime::GetCurrentTime();
	m_EndDay = COleDateTime::GetCurrentTime();
	m_EndTime = COleDateTime::GetCurrentTime();
	m_bItemEvTypeOnlyone = FALSE;
	m_bItemEvTypeOneDay = FALSE;
	m_bItemEvTypeInflChange = FALSE;
	m_bItemEvTypeLevelUp = FALSE;
	m_bItemEvTypeCouponOnlyOne = FALSE;
	m_bItemEvTypeCouponOneDay = FALSE;
	m_bINFL_ANI = FALSE;
	m_bINFL_NORMAL = FALSE;
	m_bINFL_VCN = FALSE;
	m_bINFL_ALL = FALSE;
	m_bMemberShip = FALSE;
	m_bNewMember = FALSE;
	m_bUnitKindBGear = TRUE;
	m_bUnitKindMGear = TRUE;
	m_bUnitKindAGear = TRUE;
	m_bUnitKindIGear = TRUE;
	m_LastGameEndDateDay = COleDateTime::GetCurrentTime();
	m_LastGameEndDateTime = COleDateTime::GetCurrentTime();
	m_bCheckWithAccountUID		= FALSE;		// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
	m_bCheckWithCharacterUID	= FALSE;	// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
	m_nLevelMax = 0;
	m_nLevelMin = 0;
	//}}AFX_DATA_INIT
	m_bInsertItemEv = i_bInsertItemEv;

	MEMSET_ZERO(&m_ItemEv, sizeof(m_ItemEv));		// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
	m_pMainDlg = (CAtumAdminToolDlg*)AfxGetMainWnd();
	m_pODBCStmt = new CODBCStatement;
}

CSetItemEv::~CSetItemEv()
{
	SAFE_DELETE(m_pODBCStmt);	
}

void CSetItemEv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetItemEv)
	DDX_Text(pDX, IDC_COUNT_EDIT, m_nCount);
	DDX_Text(pDX, IDC_ITEMNUM_EDIT, m_nItemNum);
	DDX_Text(pDX, IDC_LEVEL_EDIT, m_nLevel);
	DDX_Text(pDX, IDC_EDIT3, m_nCheckNumber);	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 
	DDX_Check(pDX, IDC_PCBANG_CHECK, m_bPCBang);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_StartDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_EndDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_EndTime);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_OnlyOne_CHECK, m_bItemEvTypeOnlyone);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_OneDay_CHECK, m_bItemEvTypeOneDay);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_INFLCHANGE, m_bItemEvTypeInflChange);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_LEVELUP, m_bItemEvTypeLevelUp);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_COUPON_ONLYONE, m_bItemEvTypeCouponOnlyOne);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_COUPON_ONEDAY, m_bItemEvTypeCouponOneDay);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_LOGINEVENT, m_bItemEvTypeLoginEvent); // 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_INFL_ANI_CHECK, m_bINFL_ANI);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_INFL_NORMAL_CHECK, m_bINFL_NORMAL);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_INFL_VCN_CHECK, m_bINFL_VCN);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_INFL_ALL_CHECK, m_bINFL_ALL);
	DDX_Check(pDX, IDC_MEMBERSHIP_CHECK, m_bMemberShip);
	DDX_Check(pDX, IDC_NEWMEMBER_CHECK, m_bNewMember);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_UNITKIND_BGEAR_CHECK, m_bUnitKindBGear);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_UNITKIND_MGEAR_CHECK, m_bUnitKindMGear);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_UNITKIND_AGEAR_CHECK, m_bUnitKindAGear);
	DDX_Check(pDX, IDC_ITEM_EVENT_TYPE_UNITKIND_IGEAR_CHECK, m_bUnitKindIGear);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LAST_DATE, m_LastGameEndDateDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LAST_TIME, m_LastGameEndDateTime);
	DDX_Check(pDX, IDC_CHECK_LAST_GAME_END_DATE, m_bCheckLastGameEndDate);
	DDX_Check(pDX, IDC_CHECK_CHECK_WITH_ACCOUNTUID, m_bCheckWithAccountUID);
	DDX_Check(pDX, IDC_CHECK_CHECK_WITH_CHARACTERUID, m_bCheckWithCharacterUID);
	DDX_Text(pDX, IDC_LEVELMAX, m_nLevelMax);
	DDX_Text(pDX, IDC_LEVELMIN, m_nLevelMin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetItemEv, CDialog)
	//{{AFX_MSG_MAP(CSetItemEv)
	ON_BN_CLICKED(IDC_SET_ITEM_EVENT_BUTTON_OK, OnSetItemEventButtonOk)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_OnlyOne_CHECK, OnITEMEVENTTYPEOnlyOneCHECK)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_OneDay_CHECK, OnITEMEVENTTYPEOneDayCHECK)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_INFLCHANGE, OnITEMEVENTTYPEInflChangeCHECK)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_LEVELUP, OnITEMEVENTTYPELevelUpCHECK)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_COUPON_ONLYONE, OnITEMEVENTTYPECouponOnlyOneCHECK)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_COUPON_ONEDAY, OnITEMEVENTTYPECouponOneDayCHECK)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_LOGINEVENT, OnITEMEVENTTYPELoginEvent)			// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_INFL_NORMAL_CHECK, OnItemEventTypeInflNormalCheck)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_INFL_VCN_CHECK, OnItemEventTypeInflVcnCheck)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_INFL_ANI_CHECK, OnItemEventTypeInflAniCheck)
	ON_BN_CLICKED(IDC_ITEM_EVENT_TYPE_INFL_ALL_CHECK, OnItemEventTypeInflAllCheck)
	ON_BN_CLICKED(IDC_MEMBERSHIP_CHECK, OnMembershipCheck)
	ON_BN_CLICKED(IDC_CHECK_CHECK_WITH_ACCOUNTUID, OnCheckWithAccountUID)
	ON_BN_CLICKED(IDC_CHECK_CHECK_WITH_CHARACTERUID, OnCheckWithCharacterUID)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetItemEv message handlers

void CSetItemEv::OnSetItemEventButtonOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	m_ItemEv.StartTime.SetDateTime(m_StartDay.GetYear(),m_StartDay.GetMonth(),m_StartDay.GetDay(),m_StartTime.GetHour(),m_StartTime.GetMinute(),m_StartTime.GetSecond());
	m_ItemEv.EndTime.SetDateTime(m_EndDay.GetYear(),m_EndDay.GetMonth(),m_EndDay.GetDay(),m_EndTime.GetHour(),m_EndTime.GetMinute(),m_EndTime.GetSecond());
	
	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
	m_ItemEv.atLastGameEndDate.SetDateTime(m_LastGameEndDateDay.GetYear(),m_LastGameEndDateDay.GetMonth(),m_LastGameEndDateDay.GetDay(),m_LastGameEndDateTime.GetHour(),m_LastGameEndDateTime.GetMinute(),m_LastGameEndDateTime.GetSecond());

	if(m_ItemEv.StartTime >= m_ItemEv.EndTime)
	{
		AfxMessageBox("Time error !!");
		return;
	}
// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 하나도 체크하지 않은 것만 체크하면됨
//	if( (FALSE == m_bItemEvTypeOnlyone && FALSE == m_bItemEvTypeOneDay
//			&& FALSE == m_bItemEvTypeInflChange && FALSE == m_bItemEvTypeLevelUp) 
//		|| (TRUE == m_bItemEvTypeOnlyone && TRUE == m_bItemEvTypeOneDay
//			&& TRUE == m_bItemEvTypeInflChange && TRUE == m_bItemEvTypeLevelUp))
	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 로그인이벤트 체크 추가
	if(FALSE == (m_bItemEvTypeOnlyone | m_bItemEvTypeOneDay | m_bItemEvTypeInflChange | m_bItemEvTypeLevelUp | m_bItemEvTypeCouponOnlyOne | m_bItemEvTypeCouponOneDay | m_bItemEvTypeLoginEvent)) 
	{// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 쿠폰 이벤트 추가함
		AfxMessageBox("ItemEventType error !!");
		return;
	}
	
	if(FALSE == m_bINFL_NORMAL && FALSE == m_bINFL_VCN && FALSE == m_bINFL_ANI && FALSE == m_bINFL_ALL)
	{
		AfxMessageBox("InfluenceType error !!");
		return;
	}

	if(FALSE == m_bUnitKindBGear && FALSE == m_bUnitKindMGear && FALSE == m_bUnitKindAGear && FALSE == m_bUnitKindIGear)
	{
		AfxMessageBox("UnitKind error !!");
		return;		
	}

	m_ItemEv.ItemEventUID	= 0;
	if (TRUE == m_bItemEvTypeOnlyone)
	{
		m_ItemEv.ItemEventType	= ITEM_EVENT_TYPE_ONLYONE;
	}
	if (TRUE == m_bItemEvTypeOneDay)
	{
		m_ItemEv.ItemEventType	= ITEM_EVENT_TYPE_ONEDAY;
	}
	if (TRUE == m_bItemEvTypeInflChange)
	{
		m_ItemEv.ItemEventType	= ITEM_EVENT_TYPE_INFLCHANGE;
	}
	if (TRUE == m_bItemEvTypeLevelUp)
	{
		m_ItemEv.ItemEventType	= ITEM_EVENT_TYPE_LEVELUP;
	}
	if (TRUE == m_bItemEvTypeCouponOnlyOne)
	{// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
		m_ItemEv.ItemEventType	= ITEM_EVENT_TYPE_COUPON_ONLYONE;
	}
	if (TRUE == m_bItemEvTypeCouponOneDay)
	{// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
		m_ItemEv.ItemEventType	= ITEM_EVENT_TYPE_COUPON_ONEDAY;
	}
	if (TRUE == m_bItemEvTypeLoginEvent)
	{// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
		m_ItemEv.ItemEventType	= ITEM_EVENT_TYPE_LOGIN;
	}

	if (TRUE == m_bINFL_NORMAL)
	{
		m_ItemEv.byInfluenceType = INFLUENCE_TYPE_NORMAL;
	}

	if (TRUE == m_bINFL_VCN)
	{
		m_ItemEv.byInfluenceType = INFLUENCE_TYPE_VCN;
	}
	
	if (TRUE == m_bINFL_ANI)
	{
		m_ItemEv.byInfluenceType = INFLUENCE_TYPE_ANI;
	}
	
	if (TRUE == m_bINFL_ALL)
	{
		m_ItemEv.byInfluenceType = INFLUENCE_TYPE_ALL_MASK;
	}

	if (1 > m_nCount)
	{
		AfxMessageBox("Count error !!");	
		return;
	}

	if (0 > m_nLevel)
	{
		AfxMessageBox("Level error !!");	
		return;
	}

	if (FALSE == FindItem())
	{
		AfxMessageBox("Can't find ItemNum from ti_Item !!");	// 2009-11-19 by cmkwon
		return;
	}
//
//	if (FALSE == SetItemEventButtonCheckUP())
//	{
//		return;
//	}

	m_ItemEv.OnlyPCBang		= m_bPCBang;
	m_ItemEv.ItemNum		= m_nItemNum;
	m_ItemEv.Count			= m_nCount;
	m_ItemEv.MemberShip		= m_bMemberShip;
	m_ItemEv.ReqLevel		= m_nLevel;
	m_ItemEv.NewMember		= m_bNewMember;
	m_ItemEv.LoginCheckNumber = m_nCheckNumber;	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 
	// 2010-06-16 by jskim, 레벨별 이벤트 체크 기능 -

	if(m_nLevelMin > m_nLevelMax)
	{
		AfxMessageBox("level setting Error !!");
		return;
	}
	m_ItemEv.iLevelMin		= m_nLevelMin;
	m_ItemEv.iLevelMax		= m_nLevelMax;	
	//end 2010-06-16 by jskim, 레벨별 이벤트 체크 기능 -
	
	// 2007-07-25 by dhjin, 지급 유닛 설정
	m_ItemEv.UnitKind = 0;
	if(m_bUnitKindBGear)
	{
		m_ItemEv.UnitKind += UNITKIND_BGEAR_MASK;
	}
	if(m_bUnitKindMGear)
	{
		m_ItemEv.UnitKind += UNITKIND_MGEAR_MASK;
	}
	if(m_bUnitKindAGear)
	{
		m_ItemEv.UnitKind += UNITKIND_AGEAR_MASK;
	}
	if(m_bUnitKindIGear)
	{
		m_ItemEv.UnitKind += UNITKIND_IGEAR_MASK;
	}

	// 2007-07-25 by dhjin, 접두, 접미 옵션
	CComboBox *pComboPrefix = (CComboBox*)GetDlgItem(IDC_COMBO_ITEMEVENT_PREFIX);
	CComboBox *pComboSuffix = (CComboBox*)GetDlgItem(IDC_COMBO_ITEMEVENT_SUFFIX);

	CString szPrefixName, szSuffixName;

	m_ItemEv.PrefixCodeNum = 0;
	m_ItemEv.SuffixCodeNum = 0;
	if (pComboPrefix->GetCurSel() != -1)
	{
		pComboPrefix->GetLBText(pComboPrefix->GetCurSel(), szPrefixName);
		if (szPrefixName == STRMSG_S_SCADMINTOOL_0025)
		{
			m_nItemPrefixCodeNum = 0;
		}
		else
		{
			m_nItemPrefixCodeNum = GetRareCodeNumByRareDescription((LPSTR)(LPCSTR)szPrefixName);
			m_ItemEv.PrefixCodeNum = m_nItemPrefixCodeNum;
		}
	}
	if (pComboSuffix->GetCurSel() != -1)
	{
		pComboSuffix->GetLBText(pComboSuffix->GetCurSel(), szSuffixName);
		if (szSuffixName == STRMSG_S_SCADMINTOOL_0025)
		{
			m_nItemSuffixCodeNum = 0;
		}
		else
		{
			m_nItemSuffixCodeNum = GetRareCodeNumByRareDescription((LPSTR)(LPCSTR)szSuffixName);
			m_ItemEv.SuffixCodeNum = m_nItemSuffixCodeNum;
		}
	}	

	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
	m_ItemEv.UseLastGameEndDate	= m_bCheckLastGameEndDate;
	if(ITEM_EVENT_TYPE_ONLYONE != m_ItemEv.ItemEventType)
	{// 2008-02-01 by cmkwon, ITEM_EVENT_TYPE_ONLYONE 이외에서는 atLastGameEndDate 는 값이 설정되면 안된다.
		m_ItemEv.UseLastGameEndDate	= FALSE;		
	}

	// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
	m_ItemEv.CheckWithCharacterUID	= m_bCheckWithCharacterUID;

	CDialog::OnOK();
}

BOOL CSetItemEv::OnInitDialog() 
{
	CDialog::OnInitDialog();

		// Connect DB
	if (!m_pODBCStmt->Init(m_pMainDlg->m_pServerInfo4Admin->DBIP, m_pMainDlg->m_pServerInfo4Admin->DBPort, m_pMainDlg->m_pServerInfo4Admin->DBName,
							m_pMainDlg->m_pServerInfo4Admin->DBUID, m_pMainDlg->m_pServerInfo4Admin->DBPWD, GetSafeHwnd())
	)
	{
		MessageBox(STRERR_S_SCADMINTOOL_0013);
		EndDialog(-1);
		return FALSE;
	}

	CComboBox *pComboPrefix = (CComboBox*)GetDlgItem(IDC_COMBO_ITEMEVENT_PREFIX);
	CComboBox *pComboSuffix = (CComboBox*)GetDlgItem(IDC_COMBO_ITEMEVENT_SUFFIX);

	// 2010-04-20 by cmkwon, 신규 러키 머신 구현 -
	//if(IS_WEAPON(m_nItemKind))
	if(IS_RARE_TARGET_ITEMKIND(m_nItemKind))
	{
		CAtumDBHelper::LoadRareItemInfo(m_pODBCStmt, &m_mapRareItemInfo, &(m_pMainDlg->m_Localization),  &m_mapRareItemInfoName);

		// 2007-07-25 by dhjin, RareFix 리스트 생성
		pComboPrefix->AddString(STRMSG_S_SCADMINTOOL_0025);
		pComboSuffix->AddString(STRMSG_S_SCADMINTOOL_0025);	
			
		char szPrefixRareDesc[SIZE_MAX_RARE_DESCRIPTION];
		char szSuffixRareDesc[SIZE_MAX_RARE_DESCRIPTION];
		MEMSET_ZERO(szPrefixRareDesc, SIZE_MAX_RARE_DESCRIPTION);
		MEMSET_ZERO(szSuffixRareDesc, SIZE_MAX_RARE_DESCRIPTION);

		SRARE_DESCRIPTION tmDescrip;
		ez_map<INT, RARE_ITEM_INFO>::iterator itr = m_mapRareItemInfo.begin();
		while (m_mapRareItemInfo.end() != itr)
		{
			char szTemp[SIZE_MAX_RARE_DESCRIPTION];
			MEMSET_ZERO(szTemp, SIZE_MAX_RARE_DESCRIPTION);
			RARE_ITEM_INFO *pRareItemInfo = &(itr->second);
			memset(&tmDescrip, 0x00, sizeof(SRARE_DESCRIPTION));
			sprintf(tmDescrip.szRareDescription, "%s(%d)    [%s]"
				, pRareItemInfo->Name, pRareItemInfo->CodeNum
				, GetRareParameterDescription(szTemp, pRareItemInfo));
			tmDescrip.nRareCodeNum = pRareItemInfo->CodeNum;

			if (IS_RARE_PREFIX(pRareItemInfo->CodeNum))
			{
				if(COMPARE_ITEMKIND(pRareItemInfo->ReqItemKind, m_nItemKind))
				{
					m_vectRARE_DESCRIPTIONList.push_back(tmDescrip);
					pComboPrefix->AddString(tmDescrip.szRareDescription);
					if (m_nItemPrefixCodeNum == pRareItemInfo->CodeNum)
					{
						STRNCPY_MEMSET(szPrefixRareDesc, tmDescrip.szRareDescription, SIZE_MAX_RARE_DESCRIPTION);
					}
	 			}
			}
			else if (IS_RARE_SUFFIX(pRareItemInfo->CodeNum))
			{
				if(COMPARE_ITEMKIND(pRareItemInfo->ReqItemKind, m_nItemKind))
	 			{
					m_vectRARE_DESCRIPTIONList.push_back(tmDescrip);
					pComboSuffix->AddString(tmDescrip.szRareDescription);
					if (m_nItemSuffixCodeNum == pRareItemInfo->CodeNum)
					{
						STRNCPY_MEMSET(szSuffixRareDesc, tmDescrip.szRareDescription, SIZE_MAX_RARE_DESCRIPTION);
					}
	  			}
			}
			itr++;
		}

		if(0 < strlen(szPrefixRareDesc))
		{
			pComboPrefix->SetCurSel(pComboPrefix->FindString(0, szPrefixRareDesc));
		}
		if(0 < strlen(szSuffixRareDesc))
		{
			pComboSuffix->SetCurSel(pComboSuffix->FindString(0, szSuffixRareDesc));
		}

	}
	else
	{
		pComboPrefix->EnableWindow(FALSE);
		pComboSuffix->EnableWindow(FALSE);
	}

	// TODO: Add extra initialization here

	GetDlgItem(IDC_ITEM_EVENT_TYPE_INFL_ALL_CHECK)->SetWindowText(CAtumSJ::GetInfluenceTypeString(INFLUENCE_TYPE_ALL_MASK));
	GetDlgItem(IDC_ITEM_EVENT_TYPE_INFL_NORMAL_CHECK)->SetWindowText(CAtumSJ::GetInfluenceTypeString(INFLUENCE_TYPE_NORMAL));
	GetDlgItem(IDC_ITEM_EVENT_TYPE_INFL_VCN_CHECK)->SetWindowText(CAtumSJ::GetInfluenceTypeString(INFLUENCE_TYPE_VCN));
	GetDlgItem(IDC_ITEM_EVENT_TYPE_INFL_ANI_CHECK)->SetWindowText(CAtumSJ::GetInfluenceTypeString(INFLUENCE_TYPE_ANI));

	if(m_bInsertItemEv)
	{
//		m_ItemEv.ItemEventUID			= 0;
		m_ItemEv.ItemEventType			= ITEM_EVENT_TYPE_ONLYONE;
		m_ItemEv.OnlyPCBang				= m_bPCBang;
		m_ItemEv.ItemNum				= m_nItemNum;
		m_ItemEv.Count					= m_nCount;
		m_ItemEv.ReqLevel				= m_nLevel;
		m_ItemEv.LoginCheckNumber		= m_nCheckNumber;			// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 
		m_ItemEv.StartTime.SetDateTime(m_StartDay.GetYear(),m_StartDay.GetMonth(),m_StartDay.GetDay(),m_StartTime.GetHour(),m_StartTime.GetMinute(),m_StartTime.GetSecond());
		m_ItemEv.EndTime.SetDateTime(m_EndDay.GetYear(),m_EndDay.GetMonth(),m_EndDay.GetDay(),m_EndTime.GetHour(),m_EndTime.GetMinute(),m_EndTime.GetSecond());

		// 2008-09-24 by cmkwon, AdminTool-Item Event Management 에 LastGameEndDate 설정 관련 버그 수정 - 
		// 2009-04-21 by cmkwon, 버그 수정 - 
		//m_ItemEv.EndTime.SetDateTime(m_LastGameEndDateDay.GetYear(),m_LastGameEndDateDay.GetMonth(),m_LastGameEndDateDay.GetDay(),m_LastGameEndDateTime.GetHour(),m_LastGameEndDateTime.GetMinute(),m_LastGameEndDateTime.GetSecond());
		m_ItemEv.atLastGameEndDate.SetDateTime(m_LastGameEndDateDay.GetYear(),m_LastGameEndDateDay.GetMonth(),m_LastGameEndDateDay.GetDay(),m_LastGameEndDateTime.GetHour(),m_LastGameEndDateTime.GetMinute(),m_LastGameEndDateTime.GetSecond());

		m_ItemEv.MemberShip				= m_bMemberShip;
		m_ItemEv.NewMember				= m_bNewMember;
		m_ItemEv.UnitKind				= UNITKIND_ALL_MASK;		// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
		m_ItemEv.byInfluenceType		= INFLUENCE_TYPE_ALL_MASK;	// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
		m_ItemEv.CheckWithCharacterUID	= FALSE;					// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
		m_ItemEv.iLevelMin				= m_nLevelMin;				// 2010-06-16 by jskim, 레벨별 이벤트 체크 기능 -
		m_ItemEv.iLevelMax				= m_nLevelMax;				// 2010-06-16 by jskim, 레벨별 이벤트 체크 기능 -
	}
// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 아래와 같이 switch 문으로 수정	
//	if (FALSE == m_ItemEv.ItemEventType)
//	{
//		m_bItemEvTypeOnlyone			= FALSE;
//		m_bItemEvTypeOneDay				= FALSE;
//		m_bItemEvTypeInflChange			= FALSE;
//		m_bItemEvTypeLevelUp			= FALSE;
//	}
//	
//	if (ITEM_EVENT_TYPE_ONLYONE == m_ItemEv.ItemEventType)
//	{
//		m_bItemEvTypeOnlyone			= TRUE;
//		m_bItemEvTypeOneDay				= FALSE;
//		m_bItemEvTypeInflChange			= FALSE;
//		m_bItemEvTypeLevelUp			= FALSE;
//	}
//
//	if (ITEM_EVENT_TYPE_ONEDAY == m_ItemEv.ItemEventType)
//	{
//		m_bItemEvTypeOnlyone			= FALSE;
//		m_bItemEvTypeOneDay				= TRUE;
//		m_bItemEvTypeInflChange			= FALSE;
//		m_bItemEvTypeLevelUp			= FALSE;
//	}
//
//	if (ITEM_EVENT_TYPE_INFLCHANGE == m_ItemEv.ItemEventType)
//	{
//		m_bItemEvTypeOnlyone			= FALSE;
//		m_bItemEvTypeOneDay				= FALSE;
//		m_bItemEvTypeInflChange			= TRUE;
//		m_bItemEvTypeLevelUp			= FALSE;
//	}
//
//	if (ITEM_EVENT_TYPE_LEVELUP == m_ItemEv.ItemEventType)
//	{
//		m_bItemEvTypeOnlyone			= FALSE;
//		m_bItemEvTypeOneDay				= FALSE;
//		m_bItemEvTypeInflChange			= FALSE;
//		m_bItemEvTypeLevelUp			= TRUE;
//	}	

	m_bItemEvTypeOnlyone			= FALSE;
	m_bItemEvTypeOneDay				= FALSE;
	m_bItemEvTypeInflChange			= FALSE;
	m_bItemEvTypeLevelUp			= FALSE;
	m_bItemEvTypeCouponOnlyOne		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= FALSE;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	switch(m_ItemEv.ItemEventType)
	{
	case ITEM_EVENT_TYPE_ONLYONE:				m_bItemEvTypeOnlyone			= TRUE;			break;
	case ITEM_EVENT_TYPE_ONEDAY:				m_bItemEvTypeOneDay				= TRUE;			break;
	case ITEM_EVENT_TYPE_INFLCHANGE:			m_bItemEvTypeInflChange			= TRUE;			break;
	case ITEM_EVENT_TYPE_LEVELUP:				m_bItemEvTypeLevelUp			= TRUE;			break;
	case ITEM_EVENT_TYPE_COUPON_ONLYONE:		m_bItemEvTypeCouponOnlyOne		= TRUE;			break;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	case ITEM_EVENT_TYPE_COUPON_ONEDAY:			m_bItemEvTypeCouponOneDay		= TRUE;			break;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	case ITEM_EVENT_TYPE_LOGIN:					m_bItemEvTypeLoginEvent			= TRUE;			break;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	}

// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
// 	if (INFLUENCE_TYPE_NORMAL == m_ItemEv.byInfluenceType)
// 	{
// 		m_bINFL_NORMAL			= TRUE;
// 		m_bINFL_VCN				= FALSE;
// 		m_bINFL_ANI				= FALSE;		
// 		m_bINFL_ALL				= FALSE;
// 	}
// 
// 	if (INFLUENCE_TYPE_VCN == m_ItemEv.byInfluenceType)
// 	{
// 		m_bINFL_NORMAL			= FALSE;
// 		m_bINFL_VCN				= TRUE;
// 		m_bINFL_ANI				= FALSE;
// 		m_bINFL_ALL				= FALSE;
// 	}
// 	
// 	if (INFLUENCE_TYPE_ANI == m_ItemEv.byInfluenceType)
// 	{
// 		m_bINFL_NORMAL			= FALSE;
// 		m_bINFL_VCN				= FALSE;
// 		m_bINFL_ANI				= TRUE;
// 		m_bINFL_ALL				= FALSE;
// 	}
// 
// 	if (INFLUENCE_TYPE_ALL_MASK == m_ItemEv.byInfluenceType)
// 	{
// 		m_bINFL_NORMAL			= FALSE;
// 		m_bINFL_VCN				= FALSE;
// 		m_bINFL_ANI				= FALSE;
// 		m_bINFL_ALL				= TRUE;
// 	}
	///////////////////////////////////////////////////////////////////////////////
	// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
	m_bINFL_NORMAL			= FALSE;
	m_bINFL_VCN				= FALSE;
	m_bINFL_ANI				= FALSE;		
	m_bINFL_ALL				= FALSE;
	if(INFLUENCE_TYPE_ALL_MASK ==  m_ItemEv.byInfluenceType)
	{
		m_bINFL_ALL				= TRUE;
	}
	else if(COMPARE_BIT_FLAG(m_ItemEv.byInfluenceType, INFLUENCE_TYPE_NORMAL))
	{
		m_bINFL_NORMAL			= TRUE;
	}
	else if(COMPARE_BIT_FLAG(m_ItemEv.byInfluenceType, INFLUENCE_TYPE_VCN))
	{
		m_bINFL_VCN				= TRUE;
	}
	else if(COMPARE_BIT_FLAG(m_ItemEv.byInfluenceType, INFLUENCE_TYPE_ANI))
	{
		m_bINFL_ANI				= TRUE;
	}
	else
	{
		m_bINFL_ALL				= TRUE;
	}

	m_bPCBang				= m_ItemEv.OnlyPCBang;
	m_nItemNum				= m_ItemEv.ItemNum;
	m_nCount				= m_ItemEv.Count;
	m_nLevel				= m_ItemEv.ReqLevel;
	m_nCheckNumber			= m_ItemEv.LoginCheckNumber;	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 
	m_StartDay.SetDate(m_ItemEv.StartTime.Year, m_ItemEv.StartTime.Month, m_ItemEv.StartTime.Day);
	m_StartTime.SetTime(m_ItemEv.StartTime.Hour, m_ItemEv.StartTime.Minute, m_ItemEv.StartTime.Second);
	m_EndDay.SetDate(m_ItemEv.EndTime.Year, m_ItemEv.EndTime.Month, m_ItemEv.EndTime.Day);
	m_EndTime.SetTime(m_ItemEv.EndTime.Hour, m_ItemEv.EndTime.Minute, m_ItemEv.EndTime.Second);

	// 2008-09-24 by cmkwon, AdminTool-Item Event Management 에 LastGameEndDate 설정 관련 버그 수정 - 
	m_LastGameEndDateDay.SetDate(m_ItemEv.atLastGameEndDate.Year, m_ItemEv.atLastGameEndDate.Month, m_ItemEv.atLastGameEndDate.Day);
	m_LastGameEndDateTime.SetTime(m_ItemEv.atLastGameEndDate.Hour, m_ItemEv.atLastGameEndDate.Minute, m_ItemEv.atLastGameEndDate.Second);

	m_bMemberShip			= m_ItemEv.MemberShip;
	m_bNewMember			= m_ItemEv.NewMember;

	// 2007-07-25 by dhjin, 지급 유닛 설정
	if(FALSE == (UNITKIND_BGEAR_MASK & m_ItemEv.UnitKind))
	{
		m_bUnitKindBGear = FALSE;
	}
	if(FALSE == (UNITKIND_MGEAR_MASK & m_ItemEv.UnitKind))
	{
		m_bUnitKindMGear = FALSE;
	}
	if(FALSE == (UNITKIND_AGEAR_MASK & m_ItemEv.UnitKind))
	{
		m_bUnitKindAGear = FALSE;
	}
	if(FALSE == (UNITKIND_IGEAR_MASK & m_ItemEv.UnitKind))
	{
		m_bUnitKindIGear = FALSE;
	}

	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
	if(FALSE == m_bInsertItemEv)
	{
		m_bCheckLastGameEndDate = m_ItemEv.UseLastGameEndDate;
	}

	// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
	m_bCheckWithAccountUID		= FALSE;
	m_bCheckWithCharacterUID	= FALSE;
	if(FALSE == m_ItemEv.CheckWithCharacterUID)
	{
		m_bCheckWithAccountUID		= TRUE;
	}
	else
	{
		m_bCheckWithCharacterUID	= TRUE;
	}
	
	// 2010-06-16 by jskim, 레벨별 이벤트 체크 기능 -
	m_nLevelMin	= m_ItemEv.iLevelMin;
	m_nLevelMax	= m_ItemEv.iLevelMax;
	//end 2010-06-16 by jskim, 레벨별 이벤트 체크 기능 -

	UpdateData(FALSE);	
	ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSetItemEv::FindItem()
{
	CString szSQLQuery;
//	szSQLQuery.Format("SELECT ItemName FROM ti_Item where ItemNum = %d",m_nItemNum);
//
//	SQLINTEGER CB1=SQL_NTS;
//
//	SQLBindCol(m_pODBCStmt->m_hstmt, 1, SQL_C_CHAR, m_szItemName, SIZE_MAX_ITEM_NAME,		&CB1);

// 2008-07-02 by cmkwon, MySQL 지원 구현 - 
//	szSQLQuery.Format("SELECT ItemNum FROM ti_Item WITH (NOLOCK) where ItemNum = %d",m_nItemNum);

// 2008-08-27 by cmkwon, 날쿼리를 Procedure로 수정 - 
//	szSQLQuery.Format(QUERY_080702_0049,m_nItemNum);		// 2008-07-02 by cmkwon, MySQL 지원 구현 - 
//	
//	BOOL bRet = m_pODBCStmt->ExecuteQuery((LPCSTR)szSQLQuery);
	SQLHSTMT hstmt = m_pODBCStmt->GetSTMTHandle();
	SQLINTEGER arrCB2[2] = {SQL_NTS,SQL_NTS};
	SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &(m_nItemNum), 0,						&arrCB2[1]);
	BOOL bRet = m_pODBCStmt->ExecuteQuery((char*)(PROCEDURE_080827_0049));
	if (!bRet)
	{
		// clean up
		m_pODBCStmt->FreeStatement();
		MessageBox("ERROR");
		return FALSE;
	}
	int nRetItemNum = 0;
	arrCB2[1] = SQL_NTS;
	SQLBindCol(hstmt, 1, SQL_C_LONG, &nRetItemNum, 0,		&arrCB2[1]);
	// DB에 값이 없을때까지 loop를 돈다
	if ((bRet = SQLFetch(m_pODBCStmt->m_hstmt)) == SQL_NO_DATA)
	{
		m_pODBCStmt->FreeStatement();	// clean up
		MessageBox("NO FIND ITEM");
		return FALSE;
	}
	m_pODBCStmt->FreeStatement();	// clean up

	return (nRetItemNum == m_nItemNum);		// 2008-08-27 by cmkwon, 날쿼리를 Procedure로 수정 - 
}

//BOOL CSetItemEv::SetItemEventButtonCheckUP()
//{
//	CString		szStartDate, szEndDate, szItemEvType, szPCBangType, szInfluenceType; 
//	
//	szStartDate.Format("%04d-%02d-%02d %02d:%02d:%02d",
//		m_StartDay.GetYear(),m_StartDay.GetMonth(),m_StartDay.GetDay(),
//		m_StartTime.GetHour(),m_StartTime.GetMinute(),m_StartTime.GetSecond());
//	szEndDate.Format("%04d-%02d-%02d %02d:%02d:%02d",
//		m_EndDay.GetYear(),m_EndDay.GetMonth(),m_EndDay.GetDay(),
//		m_EndTime.GetHour(),m_EndTime.GetMinute(),m_EndTime.GetSecond());
//
//	if (ITEM_EVENT_TYPE_ONLYONE == m_ItemEv.ItemEventType)
//	{
//		szItemEvType.Format("ONCE");
//	}
//
//	if (ITEM_EVENT_TYPE_ONEDAY == m_ItemEv.ItemEventType)
//	{
//		szItemEvType.Format("DAILY");
//	}
//
//	if (INFLUENCE_TYPE_NORMAL == m_ItemEv.byInfluenceType)
//	{
//		szInfluenceType.Format("NORMAL");		
//	}
//
//	if (INFLUENCE_TYPE_VCN == m_ItemEv.byInfluenceType)
//	{
//		szInfluenceType.Format("VCN");
//	}
//	
//	if (INFLUENCE_TYPE_ANI == m_ItemEv.byInfluenceType)
//	{
//		szInfluenceType.Format("ANI");
//	}
//	
//	if (INFLUENCE_TYPE_ALL_MASK == m_ItemEv.byInfluenceType)
//	{
//		szInfluenceType.Format("ALL");
//	}
//
//	if (TRUE == m_bPCBang)
//	{
//		szPCBangType.Format("TRUE");
//	}
//
//	else 
//	{
//		szPCBangType.Format("FALSE");
//	}
//
//	CString Message;
//	Message.Format("ItemNum = %d, ItemName = %s,\n InfluenceType = %s, Count = %d,\nItemEventType = %s, OnlyPCbang = %s,\nPeriod = %s ~ %s"
//				,m_nItemNum,m_szItemName, szInfluenceType, m_nCount,szItemEvType,szPCBangType,szStartDate,szEndDate);
//	
//	if (IDOK == AfxMessageBox(Message,MB_OKCANCEL))
//	{
//		return TRUE;
//	}
//
//	return FALSE;
//}

void CSetItemEv::OnITEMEVENTTYPEOnlyOneCHECK() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bItemEvTypeOnlyone			= TRUE;
	m_bItemEvTypeOneDay				= FALSE;
	m_bItemEvTypeInflChange			= FALSE;
	m_bItemEvTypeLevelUp			= FALSE;
	m_bItemEvTypeCouponOnlyOne		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= FALSE;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	UpdateData(FALSE);

	this->ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
}

void CSetItemEv::OnITEMEVENTTYPEOneDayCHECK() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bItemEvTypeOnlyone			= FALSE;
	m_bItemEvTypeOneDay				= TRUE;
	m_bItemEvTypeInflChange			= FALSE;
	m_bItemEvTypeLevelUp			= FALSE;
	m_bItemEvTypeCouponOnlyOne		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= FALSE;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	UpdateData(FALSE);

	this->ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
}

void CSetItemEv::OnITEMEVENTTYPEInflChangeCHECK() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bItemEvTypeOnlyone			= FALSE;
	m_bItemEvTypeOneDay				= FALSE;
	m_bItemEvTypeInflChange			= TRUE;
	m_bItemEvTypeLevelUp			= FALSE;
	m_bItemEvTypeCouponOnlyOne		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= FALSE;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	UpdateData(FALSE);

	this->ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
}

void CSetItemEv::OnITEMEVENTTYPELevelUpCHECK() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bItemEvTypeOnlyone			= FALSE;
	m_bItemEvTypeOneDay				= FALSE;
	m_bItemEvTypeInflChange			= FALSE;
	m_bItemEvTypeLevelUp			= TRUE;
	m_bItemEvTypeCouponOnlyOne		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= FALSE;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	UpdateData(FALSE);

	this->ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CSetItemEv::OnITEMEVENTTYPECouponOnlyOneCHECK()
/// \brief		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - CSetItemEv::OnITEMEVENTTYPECouponOnlyOneCHECK() 추가
/// \author		cmkwon
/// \date		2008-01-11 ~ 2008-01-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CSetItemEv::OnITEMEVENTTYPECouponOnlyOneCHECK() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bItemEvTypeOnlyone			= FALSE;
	m_bItemEvTypeOneDay				= FALSE;
	m_bItemEvTypeInflChange			= FALSE;
	m_bItemEvTypeLevelUp			= FALSE;
	m_bItemEvTypeCouponOnlyOne		= TRUE;			// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= FALSE;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	UpdateData(FALSE);

	this->ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CSetItemEv::OnITEMEVENTTYPECouponOneDayCHECK()
/// \brief		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - CSetItemEv::OnITEMEVENTTYPECouponOneDayCHECK() 추가
/// \author		cmkwon
/// \date		2008-01-11 ~ 2008-01-11
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CSetItemEv::OnITEMEVENTTYPECouponOneDayCHECK() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bItemEvTypeOnlyone			= FALSE;
	m_bItemEvTypeOneDay				= FALSE;
	m_bItemEvTypeInflChange			= FALSE;
	m_bItemEvTypeLevelUp			= FALSE;
	m_bItemEvTypeCouponOnlyOne		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= TRUE;			// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= FALSE;		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	UpdateData(FALSE);

	this->ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
}

// IDC_ITEM_EVENT_TYPE_LOGINEVENT
// Start 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 툴 에디트 부분 추가
void CSetItemEv::OnITEMEVENTTYPELoginEvent() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bItemEvTypeOnlyone			= FALSE;
	m_bItemEvTypeOneDay				= FALSE;
	m_bItemEvTypeInflChange			= FALSE;
	m_bItemEvTypeLevelUp			= FALSE;
	m_bItemEvTypeCouponOnlyOne		= FALSE;		// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeCouponOneDay		= FALSE;			// 2008-01-11 by cmkwon, 아이템 이벤트 시스템에 신 쿠폰 시스템 추가 - 
	m_bItemEvTypeLoginEvent			= TRUE;
	UpdateData(FALSE);
	
	this->ResetSetItemEvControl();	// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - 
}
// End 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 툴 에디트 부분 추가

void CSetItemEv::OnItemEventTypeInflNormalCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bINFL_NORMAL			= TRUE;
	m_bINFL_VCN				= FALSE;
	m_bINFL_ANI				= FALSE;
	m_bINFL_ALL				= FALSE;
	UpdateData(FALSE);	
}

void CSetItemEv::OnItemEventTypeInflVcnCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bINFL_NORMAL			= FALSE;
	m_bINFL_VCN				= TRUE;
	m_bINFL_ANI				= FALSE;
	m_bINFL_ALL				= FALSE;
	UpdateData(FALSE);	
}

void CSetItemEv::OnItemEventTypeInflAniCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bINFL_NORMAL			= FALSE;
	m_bINFL_VCN				= FALSE;
	m_bINFL_ANI				= TRUE;
	m_bINFL_ALL				= FALSE;
	UpdateData(FALSE);	
}

void CSetItemEv::OnItemEventTypeInflAllCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bINFL_NORMAL			= FALSE;
	m_bINFL_VCN				= FALSE;
	m_bINFL_ANI				= FALSE;
	m_bINFL_ALL				= TRUE;
	UpdateData(FALSE);	
}

void CSetItemEv::OnMembershipCheck() 
{
	// TODO: Add your control notification handler code here
	
}

char *CSetItemEv::GetRareParameterDescription(char *o_szRareDesc, RARE_ITEM_INFO *i_pRareInfo)
{
// 2005-11-25 by cmkwon
//	switch(i_ReqItemKind)
//	{
//	case ITEMKIND_ALL_ITEM:					return "ITEMKIND_ALL_ITEM";
//	case ITEMKIND_ALL_WEAPON:				return "ITEMKIND_ALL_WEAPON";	
//	case ITEMKIND_PRIMARY_WEAPON_ALL:		return "ITEMKIND_PRIMARY_WEAPON_ALL";	
//	case ITEMKIND_PRIMARY_WEAPON_1:			return "ITEMKIND_PRIMARY_WEAPON_1";	
//	case ITEMKIND_PRIMARY_WEAPON_2:			return "ITEMKIND_PRIMARY_WEAPON_2";	
//	case ITEMKIND_SECONDARY_WEAPON_ALL:		return "ITEMKIND_SECONDARY_WEAPON_ALL";	
//	case ITEMKIND_SECONDARY_WEAPON_1:		return "ITEMKIND_SECONDARY_WEAPON_1";	
//	case ITEMKIND_SECONDARY_WEAPON_2:		return "ITEMKIND_SECONDARY_WEAPON_2";	
//	}
//
//	return "ITEMKIND_UNKNOWN";

	for(int i=0; i<SIZE_DES_PARAM_PER_RARE_ITEM_INFO; i++)
	{
		if(0 != i_pRareInfo->DesParameter[i])
		{
			sprintf(&o_szRareDesc[strlen(o_szRareDesc)], "%s(%4.2f), "
				, GetItemDesParameter(i_pRareInfo->DesParameter[i]), i_pRareInfo->ParameterValue[i]);
		}
	}
	
	if(2 < strlen(o_szRareDesc))
	{
		MEMSET_ZERO(&o_szRareDesc[strlen(o_szRareDesc)]-2, 2);
	}
	return o_szRareDesc;
}

INT CSetItemEv::GetRareCodeNumByRareDescription(char *i_szDesc)
{
	for(int i=0; i < m_vectRARE_DESCRIPTIONList.size(); i++)
	{
		if(0 == strcmp(i_szDesc, m_vectRARE_DESCRIPTIONList[i].szRareDescription))
		{
			return m_vectRARE_DESCRIPTIONList[i].nRareCodeNum;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CSetItemEv::ResetSetItemEvControl(void)
/// \brief		// 2008-02-01 by cmkwon, ItemEvent 에 LastGameEndDate 체크 루틴 추가 - CSetItemEv::ResetSetItemEvControl() 추가
/// \author		cmkwon
/// \date		2008-02-01 ~ 2008-02-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CSetItemEv::ResetSetItemEvControl(void)
{
	GetDlgItem(IDC_LEVEL_EDIT)->EnableWindow(m_bItemEvTypeLevelUp);
	GetDlgItem(IDC_EDIT3)->EnableWindow(m_bItemEvTypeLoginEvent);	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현
	GetDlgItem(IDC_DATETIMEPICKER_LAST_DATE)->EnableWindow(m_bItemEvTypeOnlyone);
	GetDlgItem(IDC_DATETIMEPICKER_LAST_TIME)->EnableWindow(m_bItemEvTypeOnlyone);
	GetDlgItem(IDC_CHECK_LAST_GAME_END_DATE)->EnableWindow(m_bItemEvTypeOnlyone);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
/// \author		cmkwon
/// \date		2009-11-19 ~ 2009-11-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CSetItemEv::OnCheckWithAccountUID() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bCheckWithAccountUID		= TRUE;
	m_bCheckWithCharacterUID	= FALSE;
	UpdateData(FALSE);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-11-19 by cmkwon, 아이템 이벤트에 Account/Character 체크 기능 추가 - 
/// \author		cmkwon
/// \date		2009-11-19 ~ 2009-11-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CSetItemEv::OnCheckWithCharacterUID() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bCheckWithCharacterUID	= TRUE;
	m_bCheckWithAccountUID		= FALSE;
	UpdateData(FALSE);
}
