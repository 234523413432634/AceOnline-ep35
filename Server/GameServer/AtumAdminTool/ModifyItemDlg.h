#if !defined(AFX_MODIFYITEMDLG_H__CA46DF11_23EA_4860_B76C_F0627E552F84__INCLUDED_)
#define AFX_MODIFYITEMDLG_H__CA46DF11_23EA_4860_B76C_F0627E552F84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyItemDlg.h : header file
//

#include "SCUserAdminDlg.h"

#define SIZE_MAX_RARE_DESCRIPTION		1024
struct SRARE_DESCRIPTION
{
	char		szRareDescription[SIZE_MAX_RARE_DESCRIPTION];
	INT			nRareCodeNum;
};
typedef vector<SRARE_DESCRIPTION>		vectRARE_DESCRIPTION;

struct SENCHANT_DESCRIPTION
{
	char		szEnchantDescription[SIZE_MAX_RARE_DESCRIPTION];
	INT			nEnchantItemNum;
};
typedef vector<SENCHANT_DESCRIPTION>	vectENCHANT_DESCRIPTION;

struct SCOLOR_DESCRIPTION
{
	char		szDescription[SIZE_MAX_RARE_DESCRIPTION];
	INT			nColorItemNum;
};
typedef vector<SCOLOR_DESCRIPTION>		vectCOLOR_DESCRIPTION;

///////////////////////////////////////////////////////////////////////////////
// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 
struct SITEM_DESC_FOR_ADTOOL
{
	ITEM		*pItemInfo;
	char		szItemDesc[SIZE_MAX_RARE_DESCRIPTION];
};
typedef vector<SITEM_DESC_FOR_ADTOOL>		vectSITEM_DESC_FOR_ADTOOL;

/////////////////////////////////////////////////////////////////////////////
// CModifyItemDlg dialog

class CModifyItemDlg : public CDialog
{
	friend class CSCUserAdminDlg;
// Construction
public:
	CModifyItemDlg(CSCUserAdminDlg *i_pUserAdminDlg, BOOL i_bNoEdit=FALSE, CWnd* pParent = NULL);   // standard constructor

	char *GetRareParameterDescription(char *o_szRareDesc, RARE_ITEM_INFO *i_pRareInfo);
	INT GetRareCodeNumByRareDescription(char *i_szDesc);

	char *GetEnchantParameterDescription(char *o_szEnchantDesc, ITEM *i_pEnchantItemInfo);
	INT GetEnchantItemNumByEnchantDescription(char *i_szDesc);

	char *SetColorItemDescription(char *o_szColorDesc, ITEM *i_pColorItemInfo);
	INT GetColorItemNumByColorItemDescription(char *i_szDesc);

// Dialog Data
	//{{AFX_DATA(CModifyItemDlg)
	enum { IDD = IDD_DIALOG_MODIFY_ITEM };
	CString	m_szItemName;
	int		m_nItemCount;
	int		m_ctl_nEnchantCount;
	int		m_ctl_nInsertEnchatCount;
	//}}AFX_DATA

	INT		m_nItemNum;
	INT		m_nItemPrefixCodeNum;
	INT		m_nItemSuffixCodeNum;
	INT		m_nAddEnchantItemNum;
	BYTE	m_nItemKind;
	INT		m_nArmorColorItemNum;
	BOOL						m_bNoEdit;							// 2005-12-12 by cmkwon, 수정불가 Flag
	USHORT	m_usReqUnitKind;					// 2008-06-19 by cmkwon, AdminTool 수정(기어별 인챈트 추가 할수 있게) - 
	INT		m_nShapeItemNum;				// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - ShapeItemNum 필드 추가

	CSCUserAdminDlg *m_pUserAdminDlg;
	vectRARE_DESCRIPTION		m_vectRARE_DESCRIPTIONList;
	vectENCHANT_DESCRIPTION		m_vectENCHANT_DESCRIPTIONList;
	vectCOLOR_DESCRIPTION		m_vectCOLOR_DESCRIPTIONList;			// 2005-12-08 by cmkwon
	
	///////////////////////////////////////////////////////////////////////////////
	// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 
	vectSITEM_DESC_FOR_ADTOOL	 m_vectShapeItemDescList;			// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 
	vectSITEM_DESC_FOR_ADTOOL	 m_vectEffectItemDescList;			// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 
	char* MakeItemDesc4ADTool(char *o_szItemDesc, ITEM *i_pItem);
	INT GetShapeItemNumByItemDesc(char *i_szDesc);
	INT GetEffectItemNumByItemDesc(char *i_szDesc);

	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-24 by cmkwon, AdminTool수정:해당 아이템의 인챈트 리스트 보여주기 - 
	vectINT						m_vectEnchantItemNumList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyItemDlg)
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYITEMDLG_H__CA46DF11_23EA_4860_B76C_F0627E552F84__INCLUDED_)
