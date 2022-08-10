// FxSystem.h: interface for the CFxSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FXSYSTEM_H__F4C9D4BE_FA35_45C6_8E1C_057C3762E3CF__INCLUDED_)
#define AFX_FXSYSTEM_H__F4C9D4BE_FA35_45C6_8E1C_057C3762E3CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d3d9.h"
#include "SkinnedMesh.h"

class CFxSystem  
{
public:
	CFxSystem();
	virtual ~CFxSystem();
	void	InitDeviceObjects();
	void	RestoreDeviceObjects();
	void	InvalidateDeviceObjects();
	void	DeleteDeviceObjects();
	void	Tick(float fElapsedTime);
	void	BeginTargetSurface();
	void	EndTargetSurface();
	LPDIRECT3DTEXTURE9	GetTargetSurface() { return m_pTargetTexture[0]; }
	void	SetSourceAlpha(BYTE byAlpha) { m_byAlpha = byAlpha; }
	BYTE	GetSourceAlpha() { return m_byAlpha; }
	BOOL	IsRenderBlurFilter() { return m_bSupportBlurFilter; }
	BOOL	GetMetarSurface(){return m_bSupportMetal;}
	BOOL	GetEnvSurface(){return m_bSupportEvn;}
	
	void	MakeTargetSurface();
	void	DrawTargetSurface();
	void	MakeGaussFilterSurface();
	void	DrawGaussFilterSurface();
	// ��Ż
	void	DrawMetalFilterBegin(D3DXMATRIX mWorld, D3DXMATRIX mView, D3DXMATRIX mProj, UINT ipattr, DWORD nType=0);
	void	SetMeshFrame(SMeshContainer *pMesh){m_pframeCur = pMesh;}
	
	// ȯ�汤
	void	DrawEvnFilterBegin(D3DXMATRIX mWorld, D3DXMATRIX mView, D3DXMATRIX mProj, UINT ipattr, DWORD nType=0);

	BOOL	IsRenderGaussBlur()	{ return m_bSupportGaussBlur; }
	HRESULT CreatePSFromCompiledFile (LPDIRECT3DDEVICE9 pd3dDevice,TCHAR* strPSPath,LPDIRECT3DPIXELSHADER9& pPS);
	HRESULT CreateEffectFromCompiledFile(LPDIRECT3DDEVICE9 pd3dDevice,TCHAR* strFilePath,LPD3DXEFFECT& pEffect);

public:
	float				m_fEffectTime;

	LPDIRECT3DTEXTURE9	m_pTargetTexture[2];
	LPDIRECT3DSURFACE9	m_pTargetSurface[2];

	BYTE				m_byAlpha;
	BOOL				m_bSupportBlurFilter;
	SMeshContainer		*m_pframeCur;		// �޽� ������

	// ���콺 �� ����
	LPDIRECT3DTEXTURE9	m_pGaussFilterTexture[2];
	LPDIRECT3DSURFACE9	m_pGaussFilterSurface[2];

	// ���̴�
	LPD3DXEFFECT		    m_pEffect;		// ����Ʈ
	D3DXHANDLE				m_hTechnique;	// ��ũ��
	D3DXHANDLE				m_hafWeight;	// ����ġ �迭
	D3DXHANDLE				m_htSrcMap;		// �ؽ�ó		
	DWORD					m_dwGaussBlurNum;
	BOOL					m_bUseGaussBlur;				// ���콺�� �����
	BOOL					m_bSupportGaussBlur;			// �������̴� 1.1 + �ȼ����̴� 1.1 �̻� ����
	DWORD					m_dwShaderVersion;				// 1(1.1) 2(2.0)

	// ���̴� (�ݼӱ�)
	LPD3DXEFFECT		    m_pEffectMetal;		// ����Ʈ
	D3DXHANDLE				m_hTechniqueMetal;	// ��ũ��
	D3DXHANDLE				m_hmWVP;			// ����-������ȯ���
	D3DXHANDLE				m_hmW;				// ����-���庯ȯ���
	D3DXHANDLE				m_hvLightDir;		// ��������
	D3DXHANDLE				m_hvColor;			// ������
	D3DXHANDLE				m_hvEyePos;			// ������ ��ġ	
	BOOL					m_bSupportMetal;	// ��� ����

	// ���̴� (ȯ��)
	LPD3DXEFFECT			m_pEffectEvn;
    LPDIRECT3DTEXTURE9		m_pSphereMap;
	BOOL					m_bSupportEvn;	
};

#endif
