// INFToolTip.h: interface for the CINFToolTip class.
//	2007-09-19 by dgwoo ���� ������ ȭ�鿡 �̹����� ��� Ŭ����.
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

	map<UINT, CINFImage*> m_mapToolTip;				// ���� ������ �������ִ� map
	CINFImage*		m_pImgTemp;						// ���� ��ϵ� �̹��� �ּҰ�.
	BOOL			m_IsShow;						// ���� �������� �ϴ°�?
	float			m_fLifeTime;					// �������� ���� �ð�.


};

#endif // !defined(AFX_INFTOOLTIP_H__DC6DA211_4954_4DFC_8831_7850FC864D34__INCLUDED_)
