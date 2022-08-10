// ThreadCheck.cpp: implementation of the CThreadCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadCheck.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadCheck::CThreadCheck()
{
	m_nSettingThreadCounts		= 0;
	m_bSettingCompletionFlag	= FALSE;
	m_dwCheckTick				= 3000;
	m_ThreadInfoDB.reserve(10);
}

CThreadCheck::~CThreadCheck()
{
}

SThreadInfo *CThreadCheck::GetThreadInfo(DWORD threadId)
{
	if(FALSE == m_bSettingCompletionFlag){		return FALSE;}

	mt_vector<SThreadInfo>::iterator itr = m_ThreadInfoDB.begin();
	while (itr != m_ThreadInfoDB.end())
	{
		if(itr->dwThreadId == threadId)
		{
			return itr;
		}
		itr++;
	}
	return NULL;
}

BOOL CThreadCheck::AddThreadInfo(SThreadInfo threadInfo)
{	
	m_ThreadInfoDB.lock();
	if(m_bSettingCompletionFlag
		|| GetThreadInfo(threadInfo.dwThreadId))
	{
		m_ThreadInfoDB.unlock();
		return FALSE;
	}
	m_ThreadInfoDB.push_back(threadInfo);
	if(m_nSettingThreadCounts == m_ThreadInfoDB.size())
	{
		m_bSettingCompletionFlag = TRUE;
	}
	m_ThreadInfoDB.unlock();
	return TRUE;
}

SThreadInfo * CThreadCheck::CheckThreadInfo(void)
{
	if(FALSE == m_bSettingCompletionFlag){	return NULL;}
	
	DWORD	dwCurTick = GetTickCount();
	mt_vector<SThreadInfo>::iterator itr = m_ThreadInfoDB.begin();
	while (itr != m_ThreadInfoDB.end())
	{
		if(itr->bThreadUseFlag
			&& dwCurTick - itr->dwLastUseStartTick > m_dwCheckTick)
		{
			return itr;
		}
		itr++;
	}
	return NULL;
}