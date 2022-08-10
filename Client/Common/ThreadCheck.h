// ThreadCheck.h: interface for the CThreadCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADCHECK_H__2B0EE6F6_46EA_4BE1_8465_36AA5FDE16B2__INCLUDED_)
#define AFX_THREADCHECK_H__2B0EE6F6_46EA_4BE1_8465_36AA5FDE16B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mt_stl.h"

#define SIZE_MAX_THREAD_COMMENT					64

typedef struct
{
	DWORD	dwThreadId;
	char	szThreadComment[SIZE_MAX_THREAD_COMMENT];
	BOOL	bThreadUseFlag;
	DWORD	dwLastUseStartTick;
} SThreadInfo;

class CThreadCheck
{
public:
	CThreadCheck();
	virtual ~CThreadCheck();

	SThreadInfo *GetThreadInfo(DWORD threadId);
	BOOL AddThreadInfo(SThreadInfo threadInfo);
	SThreadInfo * CheckThreadInfo(void);
	void SetCheckThreadCounts(int nThreadCounts){	m_nSettingThreadCounts = nThreadCounts;};

protected:
	int							m_nSettingThreadCounts;
	BOOL						m_bSettingCompletionFlag;
	DWORD						m_dwCheckTick;
	mt_vector<SThreadInfo>		m_ThreadInfoDB;
};

#endif // !defined(AFX_THREADCHECK_H__2B0EE6F6_46EA_4BE1_8465_36AA5FDE16B2__INCLUDED_)
