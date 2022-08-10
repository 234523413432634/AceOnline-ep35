// INFChangeCharactor.h: interface for the CINFChangeCharactor class.
//	// 2007-11-21 by dgwoo
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCHANGECHARACTOR_H__27F1FF14_9E52_4B46_A278_D4CC4708AFCB__INCLUDED_)
#define AFX_INFCHANGECHARACTOR_H__27F1FF14_9E52_4B46_A278_D4CC4708AFCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFImageBtn.h"

class CD3DHanFont;
class CINFImage;

#define CHARACTOR_FACE_SHOW_MAX				5

typedef struct {
	CINFImage*		pImgFace;
	char			szName[SIZE_MAX_CHARACTER_NAME];
	DWORD			nFaceNum;

} FACE_IMG_NUM;


class CINFChangeCharactor : public CINFBase  
{
public:
	CINFChangeCharactor(CAtumNode * pParent);
	virtual ~CINFChangeCharactor();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SetActive(BOOL i_bActive,UID64_t i_nUniqueNum = 0);
	BOOL GetActive()					{ return m_bActive;	}
	void SendChangeCharactor();
	void SetSelectFaceNum();

protected:
	CAtumNode			*			m_pParent;

	CINFImage			*			m_pImgBG;						// 캐릭변경 페이지의 배경.
	CINFImage			*			m_pImgSelect;					// 선택한 이미지.
	CINFImageBtn		*			m_pFemaleRightButton;			// 여자 페이지 넘김 버튼.
	CINFImageBtn		*			m_pFemaleLeftButton;			// 여자 페이지 넘김 버튼.
	CINFImageBtn		*			m_pMaleRightButton;				// 남자 페이지 넘김 버튼.
	CINFImageBtn		*			m_pMaleLeftButton;				// 남자 페이지 넘김 버튼.
	CINFImageBtn		*			m_pChangeButton;				// 변경하기 버튼.
	CINFImageBtn		*			m_pCancelButton;				// 취소 버튼.
	CD3DHanFont			*			m_pFontName;					// 캐릭터들의 이름.

	vector<FACE_IMG_NUM>			m_vecFaceFemale;				// 여성 얼굴.
	vector<FACE_IMG_NUM>			m_vecFaceMale;					// 남성 얼굴.

	BOOL							m_bActive;
	UID64_t							m_nUniqueNum;						// 사용한 아이템의 번호.

	//--------------------------------------------------------------------------//
	//								 DATA										//
	DWORD							m_nWindowX;						// 전체 창의 X좌표.
	DWORD							m_nWindowY;						// 전체 창의 Y좌표.

	INT								m_nSelect;						// 선택한 캐릭터가 몇번째냐?
	INT								m_nSelectFaceNum;				// 선택한 캐릭터의 FaceNum
	BOOL							m_bFemale;						// 여자쪽이냐?
	
	INT								m_nStartFemale;					// 처음 시작하는 여자 스크롤의 위치.
	INT								m_nStartMale;					// 처음 시작하는 남자 스크롤의 위치.


	//--------------------------------------------------------------------------//
	


};

#endif // !defined(AFX_INFCHANGECHARACTOR_H__27F1FF14_9E52_4B46_A278_D4CC4708AFCB__INCLUDED_)
