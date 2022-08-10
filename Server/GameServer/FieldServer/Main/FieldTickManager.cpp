#include "stdafx.h"
#include "FieldTickManager.h"
#include "FieldIOCP.h"

CFieldTickManager::CFieldTickManager(CFieldIOCP *i_pFieldIOCP, DWORD i_nTickInterval /* = FIELD_DEFAULT_TICK_INTERVAL */)
: CTickManager(i_nTickInterval)
{
	m_pFieldIOCP6 = i_pFieldIOCP;
}

CFieldTickManager::~CFieldTickManager()
{
}

void CFieldTickManager::DoTickEvent(ATUM_DATE_TIME *pDateTime, TICK_EVENT *pTickEvent)
{
#ifdef _DEBUG
	DBGOUT(STRMSG_S_F2NOTIFY_0141, pDateTime->GetDateTimeString(STRNBUF(SIZE_MAX_ATUM_DATE_TIME_STRING)));
#endif
	
	return;
}

void CFieldTickManager::DoEveryTickWork(ATUM_DATE_TIME *pDateTime)
{
}

void CFieldTickManager::DoDailyWork(ATUM_DATE_TIME *pDateTime)
{
	m_pFieldIOCP6->ResetAllP2PPKFamePoint();
}

void CFieldTickManager::DoHourlyWork(ATUM_DATE_TIME *pDateTime)
{
	m_pFieldIOCP6->OnDoHourlyWorkIOCP(pDateTime);
}

void CFieldTickManager::DoMinutelyWork(ATUM_DATE_TIME *pDateTime)
{
	m_pFieldIOCP6->OnDoMinutelyWorkIOCP(pDateTime);
}

void CFieldTickManager::DoSecondlyWork(ATUM_DATE_TIME *pDateTime)
{
	m_pFieldIOCP6->OnDoSecondlyWorkFIOCP(pDateTime);
}
