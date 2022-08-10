// INFGameMainQSlot.h: interface for the CINFGameMainQSlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFGAMEMAINQSLOT_H__FFB099C3_2ED9_43D2_A454_A5491DE43A39__INCLUDED_)
#define AFX_INFGAMEMAINQSLOT_H__FFB099C3_2ED9_43D2_A454_A5491DE43A39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
//#include "GameDataLast.h"
//#include "INFImage.h"
//#include "INFInven.h"

#define QSLOT_NUMBER		10
#define QSLOT_TAB_NUMBER	3//8

#define QSLOT_BUTTON_UP		0
#define QSLOT_BUTTON_DOWN	1

#define QSLOT_BUTTON_STATE_NUMBER	4
#define QSLOT_BUTTON_NUMBER			2

#define QSLOT_ICON_SIZE		 28
#define QSLOT_COUNTERBLE_NUMBER		RGB(255,255,255)

#define QSLOT_ITEMTYPE_NONE		0	// ������ ������ Ÿ��
#define QSLOT_ITEMTYPE_QSLOT	1	// ������ ������ Ÿ��
#define QSLOT_ITEMTYPE_SKILL	2	// ������ ������ Ÿ��
#define QSLOT_ITEMTYPE_ITEM		3	// ������ ������ Ÿ��

#define QSLOT_SIZE_X			318//254
#define QSLOT_SIZE_Y			30
#define QSLOT_ICON_INTERVAL		32
#define QSLOT_TIMER				0.4f

// 2008-11-13 by bhsohn ���̽�ƽ �۾�
// ���̽�ƽ���� ����� ���� ��ų��
typedef struct 
{
	int		nCurrentTab;
	int		nSlotNumber;			// ����Ϸ��� Ű ����
} structJoystikcSkillList;
// end 2008-11-13 by bhsohn ���̽�ƽ �۾�


class CAtumNode;
class CINFImage;
class CD3DHanFont;

class CINFGameMainQSlot : public CINFBase  
{
public:
	CINFGameMainQSlot(CAtumNode* pParent);
	virtual ~CINFGameMainQSlot();

	void SetQSlotInfo(int nTab, int nNumber, ITEM_BASE* pItem);
	// 2008-12-15 by bhsohn ��ü�� �׾�����, ����Ŭ������ ��ų �ߵ� ���� ����
	//void UseQuickSlot(int nCurrentTab, int nSlotNumber);
	BOOL UseQuickSlot(int nCurrentTab, int nSlotNumber);
	// end 2008-12-15 by bhsohn ��ü�� �׾�����, ����Ŭ������ ��ų �ߵ� ���� ����
	BOOL IsValidQSlotInfo(int nTab, int nNumber);
	void UpdateQick(int nItemNum) ;
	void SetAllQSlotInfo();
	BOOL LButtonUpQuickSlot(POINT pt);
	void StartReattackTime(ITEM *pItem);

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// 2007-07-09 by bhsohn ��ݰ� ���ڻ��� ���� ���� ������ ó��
	BOOL IsBazarOpen();

	// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
	void RefreshQSlotInfo();

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	void AddCurrentTab();
	void AddJoystikcQuickSlotList(int nCurrentTab, int nSlotNumber);
	void TickJoysticSlot();
	
	// 2008-12-15 by bhsohn ��ü�� �׾�����, ����Ŭ������ ��ų �ߵ� ���� ����
	BOOL IsPossibleJoysticSlot();

	// 2010. 04. 01 by ckPark ���ҽ� ���� �ý��۽� ���丮�� �����ҿ��� ������ ȸ���� �� ������ �ȵǴ� ���� �ذ�
	void	SetIconName( CItemInfo* pItemInfo, char* szName );
	void	UpdateIconName( CItemInfo* pItemInfo );
	// end 2010. 04. 01 by ckPark ���ҽ� ���� �ý��۽� ���丮�� �����ҿ��� ������ ȸ���� �� ������ �ȵǴ� ���� �ذ�

protected:
	void SetToolTip(int x, int y, ITEM_BASE* pItem);
	void SetSelectItem(INVEN_DISPLAY_INFO* pDisplayInfo);
	BOOL RenderDisableSkill(int nSkillNum);
	void RenderSkillReAttackTime(int nItemNum, int nRenderIndex);
	void RenderItemUsableReAttackTime(int nItemNum, int nRenderIndex);
	
	BOOL IsQSlotShowTime(ITEM *ItemInfo);

public:
	INVEN_DISPLAY_INFO m_pQSlotInfo[QSLOT_TAB_NUMBER][QSLOT_NUMBER];//8x8=64���� ����Ű ����
	INVEN_DISPLAY_INFO m_pSelectItem;
//	ITEM_BASE*		   m_pSelectItem;
	int				   m_nSelectSlotNumber;
	int				   m_nCurrentTab;							//���� ������ ����ġ.
	int				   m_nItemType;
	int			m_nX;
	int			m_nY;	

	BOOL				m_bLButtonDown;

protected:
	BOOL		m_bRestored;
	CINFImage*	m_pBack;
	CINFImage*	m_pNumber;
	CINFImage*	m_pImgTabButton[QSLOT_BUTTON_NUMBER][QSLOT_BUTTON_STATE_NUMBER];
	CINFImage*	m_pImgDisSkill;
	int			m_nButtonState[QSLOT_BUTTON_NUMBER];	
	float		m_fQSlotTimer;	
	int			m_nRenderMoveIconIntervalWidth;
	int			m_nRenderMoveIconIntervalHeight;

	CD3DHanFont*		m_vecFontLine[QSLOT_NUMBER];
	// 2007-01-22 by bhsohn ��Ű ���� ���̽� ������
	CD3DHanFont*		m_pFontTabNum;

	int			m_nQSlotSwapTab;
	int			m_nQSlotSwapNum;
	BOOL		m_bQSlotSwapFlag;

	ITEM_BASE*  m_pQSlotMove;

	// 2007-07-09 by bhsohn ��ݰ� ���ڻ��� ���� ���� ������ ó��	
	float					m_fClickBazaar;

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	float					m_fJoystikcSkillList;
	deque<structJoystikcSkillList>	m_vecJoystikcSkillList;
};

#endif // !defined(AFX_INFGAMEMAINQSLOT_H__FFB099C3_2ED9_43D2_A454_A5491DE43A39__INCLUDED_)
