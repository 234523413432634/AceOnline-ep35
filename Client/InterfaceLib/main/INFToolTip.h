// INFToolTip.h: interface for the CINFToolTip class.
//	2007-09-19 by dgwoo 게임 진행중 화면에 이미지를 띄울 클래스.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFTOOLTIP_H__DC6DA211_4954_4DFC_8831_7850FC864D34__INCLUDED_)
#define AFX_INFTOOLTIP_H__DC6DA211_4954_4DFC_8831_7850FC864D34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

class CINFImage;
class DataHeader;
class CGameData;


class CINFToolTip : public CINFBase  
{
public:
	CINFToolTip();
	virtual ~CINFToolTip();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();

	void SetImgType(UINT i_nType);

	map<UINT, CINFImage*> m_mapToolTip;				// 툴팁 정보를 가지고있는 map
	CINFImage*		m_pImgTemp;						// 현재 등록된 이미지 주소값.
	BOOL			m_IsShow;						// 현재 보여져야 하는가?
	float			m_fLifeTime;					// 보여지는 남은 시간.


};

#endif // !defined(AFX_INFTOOLTIP_H__DC6DA211_4954_4DFC_8831_7850FC864D34__INCLUDED_)
