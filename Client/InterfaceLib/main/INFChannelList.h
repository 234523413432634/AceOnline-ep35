// INFChannelList.h: interface for the CINFChannelList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCHANNELLIST_H__EA088774_3553_4314_9CA9_2E7F5EA5A054__INCLUDED_)
#define AFX_INFCHANNELLIST_H__EA088774_3553_4314_9CA9_2E7F5EA5A054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

#define CHANNEL_LIST_NUMBER				5
#define CHANNEL_LIST_STRING_LENGTH		64
#define CHANNEL_BUTTON_NUBER			3

class CD3DHanFont;
class CINFImage;
class CINFScrollBar;

class CINFChannelList : public CINFBase  
{
public:
	CINFChannelList(CAtumNode* pParent);
	virtual ~CINFChannelList();

	void Reset();
	void RecvStartChannelList(int nMapIndex, int nTargetIndex);
	void RecvChannelList(MEX_CHANNEL_INFO* pChannel);
	void RecvDoneChannelList();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnOkButtonClicked();

protected:
	BOOL		m_bRestored;
	CINFImage	*m_pImgBack;
	CINFImage	*m_pImgTitle;
	CINFImage	*m_pImgButtonOk[CHANNEL_BUTTON_NUBER];
	CINFImage	*m_pImgScrollBar;
	CINFImage	*m_pImgHightLight;

	CD3DHanFont *m_pFontChannelList[CHANNEL_LIST_NUMBER];
	char		m_szChannelList[CHANNEL_LIST_NUMBER][CHANNEL_LIST_STRING_LENGTH];
	CD3DHanFont *m_pFontMapName;
	char		m_szMapName[SIZE_MAX_MAP_NAME];

//	int			m_nCurrentSelectIndex;   // 화면상 번호
//	int			m_nCurrentScrollNumber;
	int			m_nChannelListNumber;	// 서버에서 받은 채널 리스트 개수
	int			m_nButtonState;	// ok button

	CVectorChannel m_vecChannelList;
	MSG_FC_EVENT_SELECT_CHANNEL m_msgEventSelectChannel;

	CINFScrollBar*	m_pScroll;
};

#endif // !defined(AFX_INFCHANNELLIST_H__EA088774_3553_4314_9CA9_2E7F5EA5A054__INCLUDED_)
