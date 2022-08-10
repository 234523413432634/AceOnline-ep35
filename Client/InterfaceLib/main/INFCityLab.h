// INFCityStore.h: interface for the CINFCityLab class.
// 2004.07.15 ydKim
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCITYLAB_H__AD058082_959A_4B02_BEDD_AAE54DE7B3E0__INCLUDED_)
#define AFX_INFCITYLAB_H__AD058082_959A_4B02_BEDD_AAE54DE7B3E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

// 2008-03-14 by bhsohn 조합식 개선안
#include "INFNumEditBox.h"

#define LAB_BUTTON_NUMBER			3

class CINFImage;
class CD3DHanFont;

class CINFCityLab : public CINFBase  
{
public:
	CINFCityLab(CAtumNode* pParent, BUILDINGNPC* pBuilding);
	virtual ~CINFCityLab();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnButtonClicked(int nButton);	

	void InitData();	// m_vecsource를 초기화 m_vectarget 초기화 	
	void InvenToSourceItem(CItemInfo* pItemInfo, int nCount);
	void SetPrice(int nPrice);
	void DeleteTargetItem(int nItemUniqueNumber);
	BOOL PutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg);
	BOOL PutRareInfo(MSG_FC_STORE_UPDATE_RARE_FIX* pMsg);
	void PutTargetItem(ITEM_GENERAL* pItem);
	CItemInfo*	GetTargetItemInfo();
	CItemInfo*	FindItemFromSource(UID64_t UniqueNumber);
	CItemInfo*  FindItemFromTarget(UID64_t UniqueNumber);

	void ReSetTargetItemNum(UID64_t UniqueNumber, int nItemNum);

	void SetSelectItem(CItemInfo* pItemInfo);

	// 2008-03-14 by bhsohn 조합식 개선안	
	void				OnOpenInfWnd();		// 처음 상점 오픈
	void				OnCloseInfWnd();	// 상점 클로우즈

	// 인챈트 실패 경고 해야 하는지 체크.
	bool IsWarning_EnchantFail ( void );

protected :

	// 유효하지 않은 조합 관련 에러 메시지 출력.
	void ErrorMsg_InvalidEnchantList ( char *pszMessage , const bool a_bInitData = true );
	
private:
	// 2007-12-17 by bhsohn 조합 가격 표시
	void UpdateMixPrice();

public:
	CItemInfo	*		m_pSelectItem;
	BOOL				m_bIsEnchantCheck;

protected:
	BOOL				m_bRestored;

	CINFImage	*		m_pImgButton[LAB_BUTTON_NUMBER][4];	// 0 : 제조(SEND), 1 : cancel, 2 : ok
	int					m_nButtonState[2];
	
	CINFImage	*		m_pImgBack;
	CINFImage	*		m_pImgBackFactory;	// 연구소배경 // 2008-03-14 by bhsohn 조합식 개선안
	
	CINFImage	*		m_pImgTitle;
	CINFImage	*		m_pImgPrice;
	// 2008-03-14 by bhsohn 조합식 개선안
	CINFNumEditBox*		m_pNumEditBox;

	CD3DHanFont *		m_pFontPrice;
	char				m_szPrice[64];
	vector<CItemInfo*>  m_vecSource;
	vector<CItemInfo*>  m_vecTarget;
	BOOL				m_bShowTarget;
	BUILDINGNPC*		m_pBuildingInfo;

	BOOL				m_bSelectDown;

};

#endif // !defined(AFX_INFCITYSTORE_H__AD058082_959A_4B02_BEDD_AAE54DE7B3E0__INCLUDED_)
