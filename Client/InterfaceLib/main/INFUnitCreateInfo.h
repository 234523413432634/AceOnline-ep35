// INFUnitCreateInfo.h: interface for the CUnitCreateInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFUNITCREATEINFO_H__1244E4AD_A756_471B_8F2A_F05AA9642656__INCLUDED_)
#define AFX_INFUNITCREATEINFO_H__1244E4AD_A756_471B_8F2A_F05AA9642656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

class CINFImage;

class CINFUnitCreateInfo : public CINFBase
{
public:
	CINFUnitCreateInfo(CAtumNode* pParent);
	virtual ~CINFUnitCreateInfo();


	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();


	void Render( int nUnitKind );
	virtual void Tick( float fElapedTime );
	void StartView( );


protected:
	BOOL			m_bRestored;
	//img data
	CINFImage*		m_pBGear;
	CINFImage*		m_pIGear;
	CINFImage*		m_pMGear;
	CINFImage*		m_pAGear;

	//tick data
	CRemainTime     m_tRemainTime;
	float			m_fIncreaseViewingTime;

};

#endif // !defined(AFX_INFUNITCREATEINFO_H__1244E4AD_A756_471B_8F2A_F05AA9642656__INCLUDED_)
