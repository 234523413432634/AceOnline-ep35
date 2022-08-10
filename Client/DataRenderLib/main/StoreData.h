// StoreData.h: interface for the CStoreData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_)
#define AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
struct struInfluenceWarBackupWaingInfo
{
	UID64_t		UniqueNumber;					// ������ ������ȣ
	INT			nRealItemNum;					// ���� ������ ��ȣ
	INT			nInfluenceItemNum;				// ������ ������ ��ȣ
};
// end 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�

// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//class CINFInven;
class CINFInvenExtend;
// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
class CINFTrade;
///////////////////////////////////////////////////////////////////////////////
/// \class		CStoreData
///
/// \brief		Item table, enchant, store
/// \author		dhkwon
/// \version	
/// \date		2004-04-28 ~ 2004-04-28
/// \warning	
///////////////////////////////////////////////////////////////////////////////
class CStoreData  
{
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	//friend CINFInven;
	friend CINFInvenExtend;
	friend CINFTrade;
public:
	CStoreData();
	virtual ~CStoreData();

	void	CreateChatOfItemUpdate( int nItemNum, int nOrgItemCount, int nNewItemCount );
	ITEM*	GetItemInfoFromItemGeneral(ITEM_GENERAL* pItem);
	void	SendFieldSocketItemIndexInfo(void);
	void	ItemChangeWindowPosition(MSG_FC_ITEM_CHANGE_WINDOW_POSITION_OK * pMsg);
	void	UpdateItemCount( UID64_t nUniqueNumber, INT nCount);
	void	UpdateUnitInfoByUpdateItemInfo( ITEM* pItem );
	void	UpdateItemInfo( int nItemNum);
	void	ResortingItemInInventory();

	BOOL	PutEnchant(MSG_FC_ITEM_PUT_ENCHANT* pMsg);
	BOOL	PutRareInfo(MSG_FC_STORE_UPDATE_RARE_FIX* pMsg);
	
	INT		PutItem(char * p, BOOL bUpdate = FALSE);
	INT		PutItemStore(char * p);

	UINT GetCurrentCountItemInInventoryByItemNum( INT nItemNum );
	CItemInfo* FindItemInInventoryByWindowPos( int nWindowPos );
	CItemInfo* FindItemInInventoryByUniqueNumber( UID64_t hyUniqueNumber );
	CItemInfo* FindItemInInventoryByItemNum( INT nItemNum );

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	// ������ ���������� �������� ã�´�
	CItemInfo* FindItemInWearByItemNum( INT nItemNum );
	// end 2010. 02. 11 by ckPark �ߵ��� ����������
	
	const CItemInfo* FindItemInInventoryByItemInfo ( CItemInfo *a_pcItemInfo );		// �κ� ������ �˻�. ( ������ ���� ����. )	2010. 09. 08. by hsLee.

	CItemInfo* FindBulletItem( BYTE bCaliber );
	void	DeleteItem( UID64_t hyUniqueNumber );
	void	TutorialBackUpItemAll();
	void	TutorialRollBackItemAll();
	void	TutorialNonWearItem(BYTE bPos);
	void	SetTutorialWearItem(int nCenter,int nProw,int nRear,int nWingOut,int nProowOut);
	void	SetTutorialWearItemMap(BYTE bPos,int nItemNum);
//	ITEM_GENERAL* FindItemInInventoryByWindowPos( int nWindowPos );
//	ITEM_GENERAL* FindItemInInventoryByUniqueNumber( LONGLONG hyUniqueNumber );
//	ITEM_ENCHANT* FindEnchantInfo( LONGLONG hyUniqueNumber );
//	ITEM_ENCHANT* FindEnchantInfoByWindowPos( int nWindowPos );
//	void	DeleteItemAndEnchant( LONGLONG hyUniqueNumber );
	BOOL IsWearItem(BYTE nReqItemKind);

	// 2004.6.14
	void SetWearItemData(CItemInfo* pItemInfo);
	void UpdateWearItemData(CItemInfo* pItemInfo, BOOL bWearItem=FALSE);
	void AddItemDataToUniqueNumberAndWindowPosition(CItemInfo* pItemInfo);
	float GetTotalWeight() { return m_fWeight; }
	float GetTotalUseInven(){ return m_mapItemWindowPosition.size();}
	int GetEmptySlotNumber();
	ITEM* FindBulletItemToDB(BYTE bCaliber);

	CItemInfo* SerchRevivalUseItem();

	// 2007-06-12 by bhsohn �̼� �������̽� ������
	BOOL IsShuttleWearItem(int nWearItem);
	BOOL IsTutorialLesson6Success();
	BOOL IsTutorialItemBackUp()			{	return m_bTutorialBackUp; }

	// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
	void SetInfluenceMarkInfo(BOOL bStart);
	void ChangeInfluenceMark(BYTE i_byInfluence);
	BYTE GetChangeInfluenceMark();
	void UpdateInfluenceMark();
	void RestoreInfluenceMark();
	void InitInfluenceMark();
	void UpdateEnemyInfluenceMark();
	BOOL IsInfluenceMark();	
	int	GetInfluenceMarkShow(BYTE i_byInfluence);

	// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
	void RqChangeItemPos(BOOL i_bRqPos);
	// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������

	// 2009-04-02 by bhsohn ��Ű �ӽ� �߰� ��ȹ��
	void UpdateCoinItemCount(UID64_t nUniqueNumber);
	// end 2009-04-02 by bhsohn ��Ű �ӽ� �߰� ��ȹ��

protected:
	float GetTotalItemWeight();

	// 2007-05-28 by bhsohn �����ۿ� ���� üũ�� �߰�
	void SendItemCheckSum(int nItemWear, int nItemKind, int nItemNum);
	// 2007-07-16 by dgwoo Ʃ�丮�� �ʿ��� ����ϴ� ������ ���� ����.
	void			TutorialCompulsionItemSetting(CItemInfo * pItemInfo);

	// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
	void CreateChatWeight();
	// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������

	// 2010. 03. 04 by ckPark ������ ���ϴ� �������� �����Ͽ��� ��� ���� ��� ���� ����
	void Create_FuelStatChanged_WeightOver_Message( Stat_t nChangedFuelStat );
	// end 2010. 03. 04 by ckPark ������ ���ϴ� �������� �����Ͽ��� ��� ���� ��� ���� ����

public:
	int SearchEmpty()
	{
		// m_mapItemWindowPosition�� ����ִ� �ε����� ã�´�.
		int InventoryIndex = POS_ITEMWINDOW_OFFSET;

		for(;;)
		{
			if( m_mapItemWindowPosition.find(InventoryIndex) == m_mapItemWindowPosition.end() )
				return InventoryIndex;

			InventoryIndex++;
		}

		return 0;
	}

//	CMapItemInInventoryList	m_mapItemInInventory;	// ������ �κ��丮
	CMapItemWindowInventory	m_mapItemWindowPosition;
	CMapItemInventory		m_mapItemUniqueNumber;		// new ������ �κ��丮

	CMapItemWindowInventory	m_mapItemWindowPositionBackUp;
	CMapItemInventory		m_mapItemUniqueNumberBackUp;		// new ������ �κ��丮
protected:

//	CMapItemEnchantList		m_mapEnchantItem;		// ��æƮ ������ ����
	float					m_fWeight;
	BOOL					m_bTutorialBackUp;		// 2007-07-02 by dgwoo Ʃ�丮��� ���������� �����Ͽ��°�.?

	// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
	BYTE					m_byMarkInfluence;
	struInfluenceWarBackupWaingInfo	m_struInfluenceWarBackupWaingInfo;
	BOOL					m_bInfluenceMarkWar;

// deleted
//	VOID	SetItemNumber(UINT uniqueNumber, int itemNumber);

	// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
	// ä�� ǥ�� ���緮
	float					m_fGearChatWeight;
	BOOL					m_bRqChangeItemPos;
	// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������

};

#endif // !defined(AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_)
