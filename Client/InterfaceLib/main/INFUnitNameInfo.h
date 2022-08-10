// INFUnitNameInfo.h: interface for the CINFUnitNameInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFUNITNAMEINFO_H__580A7F50_EF83_4ADC_B707_DE01602B3EE7__INCLUDED_)
#define AFX_INFUNITNAMEINFO_H__580A7F50_EF83_4ADC_B707_DE01602B3EE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

#define NAME_INFO_BALON_CHAT		9

class CChatMoveData;
class CINFImage;
class CD3DHanFont;
class CINFUnitNameInfo : public CINFBase
{
public:
	CINFUnitNameInfo(CAtumNode* pParent);
	virtual ~CINFUnitNameInfo();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void	Render();
	virtual void	Tick();

	void	RenderCharacterInfo(int x, int y, CChatMoveData* pChatData, char* strName, 
	BOOL	bShowHP, float fHP, int nGuildUniqueNumber, int nCharacterUniqueNumber, char *strMent, DWORD dwNameColor);
	void	RenderChatBalon(int x, int y, int cx, int cy);
	void	ChatCreateInfo( int nStringLength, char *strMsgChat, char *strFromCharacterName);
	// 2009. 09. 18 by ckPark 인피니티 필드 HP에 따른 몬스터 대화
	void	MonsterChatCreateInfo( int nStringLength, char *strMsgChat, int nMonsterUID );
	// end 2009. 09. 18 by ckPark 인피니티 필드 HP에 따른 몬스터 대화
	DWORD	GetNameColor(BYTE byCityWarTeamType, BYTE byInfluenceLeader);
	DWORD	GetInfluenceColor(int byInfluence, BYTE byInfluenceLeader);
	
public:
//	CINFImage	*	m_pUnitInfo;
//	CINFImage	*	m_pPartyUnitInfo;
//	CINFImage	*	m_pMonsterInfo;
//
//	CINFImage	*	m_pPartyUnitHP;
//	CINFImage	*	m_pPartyUnitEP;
//	CINFImage	*	m_pMonsterHP;
//	CINFImage	*	m_pUp;
//	CINFImage	*	m_pDown;
	CINFImage	*	m_pBalonChat[NAME_INFO_BALON_CHAT];

	CD3DHanFont*	m_pFontMent;

	float			m_fRenderDistance;
	int		nOldx;
	int		nOldy;
	char	m_strChatFullLen[1024];

	// 2007-02-23 by bhsohn ID가 뒤로 밀리는 현상 처리	
	POINT	m_ptUnitNameFirst;	// 처음위치	
};

#endif // !defined(AFX_INFUNITNAMEINFO_H__580A7F50_EF83_4ADC_B707_DE01602B3EE7__INCLUDED_)
