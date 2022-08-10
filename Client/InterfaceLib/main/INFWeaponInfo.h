// INFWeaponInfo.h: interface for the CINFWeaponInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFWEAPONINFO_H__E615F872_AE06_4C2C_AEE8_890BB13F7420__INCLUDED_)
#define AFX_INFWEAPONINFO_H__E615F872_AE06_4C2C_AEE8_890BB13F7420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"

//#define LEFT_OVERHEAT_START_X	60
//#define RIGHT_OVERHEAT_START_X	33
#define OVERHEAT_START_Y		3
#define OVERHEAT_LENGTH			90
#define OVERHEAT_HEIGHT			4
#define FUEL_GAGE_LENGTH		62
#define FUEL_GAGE_HEIGHT		7

#define FLASH_TIME				0.5f


class CGameData;
class CINFImage;
class CINFWeaponInfo : public CINFBase  
{
public:
	CINFWeaponInfo(CAtumNode* pParent);
	virtual ~CINFWeaponInfo();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	void RenderLeftWeapon();
	void RenderRightWeapon();
	void ChangeWeapon(int nWeapon);
	void RenderWeaponNumber( int nWindowPosY, int nWindowPosX, int nValue);
	void RenderWeaponFuel( int nWindowPosY, int nWindowPosX, float fRate);
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CGameData		*	m_pWeaponData ;

	CINFImage*	m_pStImage;
	CINFImage*	m_pStWeaponImage;
	CINFImage*	m_pNdImage;
	CINFImage*	m_pNdWeaponImage;
	CINFImage*	m_pStOverHeatBar;
	CINFImage*	m_pNdOverHeatBar;
	CINFImage*	m_pEmptyWeaponImage;
	CINFImage*	m_pWeaponNumberImage[10];
	CINFImage*	m_pStFuelGageBar;
	CINFImage*	m_pStFuelUnderGageBar;
//	CINFImage*	m_pNdFuelGageBar;
//	CINFImage*	m_pNdFuelUnderGageBar;
	CINFImage*	m_pReloadImage;
	CINFImage*	m_pOverHeatImage;
	CINFImage*	m_pBulletEmptyImage;
	CINFImage*	m_pBulletLowImage;

	int			m_nLeftWeaponInfoPosX ;
	int			m_nRightWeaponInfoPosX ;
	float		m_fFlashTime;
	BOOL		m_bFlash;

};

#endif // !defined(AFX_INFWEAPONINFO_H__E615F872_AE06_4C2C_AEE8_890BB13F7420__INCLUDED_)
