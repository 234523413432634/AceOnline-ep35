#include "stdafx.h"
#include "AtumPreDBManager.h"
#include "PreIOCPSocket.h"
#include "PreIOCP.h"
#include "md5_lib_src.h"
#include "AtumError.h"
#include "PreGlobal.h"
#include "GenericHTTPClient.h"		// 2008-10-08 by cmkwon, 대만 Netpower_Tpe 외부인증 구현 - 
#include "AccountBlockManager.h"

#if defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
#include "SOAPConnect.h"		// 2010-11-29 by shcho, 아르헨티나 외부인증 변경 SOAP 처리
#endif


// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 외부인증 헤더파일 추가, 라이브러리 설정
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)
#include "ArarioAuth.h"
#pragma comment(lib, "ArAuth4Cli.lib")
#endif 

CAtumPreDBManager::CAtumPreDBManager(CPreIOCP *pPreIOCP)
:CAtumDBManager(COUNT_PRE_SERVER_DBWORKER)
{
	m_pPreIOCP2 = pPreIOCP;

	if(g_pPreGlobal->IsExternalAuthentication())
	{
// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 아래와 같이 수정함.
// // 2008-10-08 by cmkwon, 대만 Netpower_Tpe 외부인증 구현 - 외부인증을 DB를 사용하지 않고 웹인증으로 처리한다.
// #if !defined(SERVICE_TYPE_TAIWANESE_SERVER_1)
// 		m_bExtAuthDBConnect		= TRUE;
// #endif

		m_bExtAuthDBConnect		= TRUE;
// 2008-10-08 by cmkwon, 대만 Netpower_Tpe 외부인증 구현 - 외부인증은 사용하지만, DB를 사용하지 않고 웹인증으로 처리한다. 그러므로 아래의 처리를 한다.
// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 외부 인증은 사용하지만, Arario 에서 제공한 모듈을 사용 할 것임
// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 러시아도 추가
#if defined(SERVICE_TYPE_TAIWANESE_SERVER_1) || defined(SERVICE_TYPE_JAPANESE_SERVER_1) || defined(SERVICE_TYPE_RUSSIAN_SERVER_1)
		m_bExtAuthDBConnect		= FALSE;
#endif

	}

	if(g_pPreGlobal->InMasangServer())
	{// 2006-05-21 by cmkwon
		m_dwCountDBWorker	= 3;
	}
}

BOOL CAtumPreDBManager::ProcessServerQuery(DB_QUERY dbquery, SQLHSTMT &hstmt, SQLHSTMT &hstmt_mc, SQLHSTMT &hstmt_extAuth)
{
	switch(dbquery.enumQuryType)
	{
	case QT_PRE_Login:			QP_PRE_Login(dbquery, hstmt, hstmt_extAuth);		break;
	case QT_BlockUser:			QP_BlockUser(dbquery, hstmt);		break;
	case QT_UnblockUser:		QP_UnblockUser(dbquery, hstmt);		break;
	case QT_MGameLogin:			QP_MGameLogin(dbquery, hstmt);		break;
	case QT_LogTotalUser:		QP_LogTotalUser(dbquery, hstmt);	break;
	case QT_InsertGlogAccount:  QP_InsertGlogAccount(dbquery, hstmt); break;
	default:
		{
			// error: no such DB query type
			DBGOUT("Error! No such DB query type! %d\n", dbquery.enumQuryType);
			return FALSE;
		}
		break;
	}

	return TRUE;
}

// QT_PRE_Login
void CAtumPreDBManager::QP_PRE_Login(DB_QUERY q, SQLHSTMT &hstmt, SQLHSTMT &hstmt_extAuth)
{
	MSG_PC_CONNECT_LOGIN	*pRMsg = (MSG_PC_CONNECT_LOGIN*)q.pQueryParam;
	CAccountInfo			accInfo;


	_strlwr(pRMsg->AccountName);			// 2006-06-02 by cmkwon, 소문자로 변환

	// 2009-01-23 by cmkwon, 터키 i,I 문자 문제 처리 - 인증시 계정 처리, 이미 소문자 처리가 되어 있지만 코드는 추가한다.
	LowercaseOnly_i_forTurkish(pRMsg->AccountName, SIZE_MAX_ACCOUNT_NAME);
    // 2010-11-29 by shcho, 아르헨티나 외부인증 변경 SOAP 처리
	if(g_pPreGlobal->IsExternalAuthentication() || g_pPreGlobal->GetIsExtAuthUseSOAP())
	{// 2006-04-27 by cmkwon, 외부 DB 인증 사용시 처리 추가
		INT		nExtAccountIDNum = 0;

		// 2008-10-08 by cmkwon, 대만 2단계 계정 시스템 지원 구현(email->uid) -
		char szOriginalAccountName[SIZE_MAX_ORIGINAL_ACCOUNT_NAME];
		STRNCPY_MEMSET(szOriginalAccountName, pRMsg->AccountName, SIZE_MAX_ORIGINAL_ACCOUNT_NAME);

		// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 
		if(FALSE == this->ExternalAuthentication(&accInfo, pRMsg, hstmt, hstmt_extAuth, q.pIOCPSocket->GetPeerIP4()))
		{
			((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_COMMON_LOGIN_FAILED);
		}
		else
		{
			if(LANGUAGE_TYPE_TAIWANESE == g_pPreGlobal->GetLanguageType())
			{// 2008-10-09 by cmkwon, 대만 Netpower_Tpe는 여기에서 계정 블럭을 체크한다.
				SBLOCKED_ACCOUNT_INFO tmBlockedInfo;
				MEMSET_ZERO(&tmBlockedInfo, sizeof(SBLOCKED_ACCOUNT_INFO));
				BOOL bBlocked = m_pPreIOCP2->m_pAccountBlockManager->IsCheckBlockedAccountInfoByAccountName(&tmBlockedInfo, pRMsg->AccountName, NULL);
				if(bBlocked)
				{
					INIT_MSG_WITH_BUFFER(MSG_PC_CONNECT_LOGIN_BLOCKED, T_PC_CONNECT_LOGIN_BLOCKED, pSBlocked, SendBuf);
					// 2008-10-08 by cmkwon, 대만 2단계 계정 시스템 지원 구현(email->uid) -
					//STRNCPY_MEMSET(pSBlocked->szAccountName, tmBlockedInfo.szBlockedAccountName, SIZE_MAX_ACCOUNT_NAME);		// 2007-01-10 by cmkwon
					STRNCPY_MEMSET(pSBlocked->szAccountName, szOriginalAccountName, SIZE_MAX_ORIGINAL_ACCOUNT_NAME);	// 2008-10-08 by cmkwon, 대만 2단계 계정 시스템 지원 구현(email->uid) -, // 2007-01-10 by cmkwon

					pSBlocked->nBlockedType		= tmBlockedInfo.enBlockedType;
					pSBlocked->atimeStart		= tmBlockedInfo.atimeStartTime;
					pSBlocked->atimeEnd			= tmBlockedInfo.atimeEndTime;
					STRNCPY_MEMSET(pSBlocked->szBlockedReasonForUser, tmBlockedInfo.szBlockedReasonForUser, SIZE_MAX_BLOCKED_ACCOUNT_REASON);		// 2007-01-10 by cmkwon
					((CPreIOCPSocket*)q.pIOCPSocket)->SendAddData(SendBuf, MSG_SIZE(MSG_PC_CONNECT_LOGIN_BLOCKED));		
					
					SAFE_DELETE(pRMsg);
					return;
				}
			}

			((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_NO_ERROR);
		}
		SAFE_DELETE(pRMsg);
		return;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2008-09-11 by cmkwon, 러시아 Innova_Rus 인증 시스템 수정 - Usp_Do_Login() 에서 인증 성공시에만 내부인증 체크를 진행하도록 수정
	//							Innova에서 Usp_Do_Login() 내에서 atum2_db_account.dbo.td_account 테이블에 AccountName, Password를 추가 하고, Password 변경시에도 Innova에서 적용해주기로 함.
	RETCODE ret;
// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 
//	//////////////////////////////////////////////////////////////////////////
//	// 2008-08-21 by dhjin, Innova BillingDB 관련처리
//	if(LANGUAGE_TYPE_RUSSIAN ==  g_pPreGlobal->GetLanguageType())
//	{
// 		SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pRMsg->AccountName, 0, NULL);
// 		SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, ((CPreIOCPSocket*)q.pIOCPSocket)->GetPeerIP(), 0, NULL);
// 		ret = SQLExecDirect(hstmt, PROCEDURE_080822_0281, SQL_NTS);
// 		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO && ret != SQL_NO_DATA)
// 		{
// 			ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"Usp_Do_Login Failed!\r\n", TRUE);
// 			SQLFreeStmt(hstmt, SQL_CLOSE);
// 			q.pIOCPSocket->SendErrorMessage(T_PC_CONNECT_LOGIN, ERR_DB_EXECUTION_FAILED);
// 			SAFE_DELETE(pRMsg);
// 			return;
// 		}		
// 		
// 		int	o_nResult = 0;
// 		SQLBindCol(hstmt, 1, SQL_C_ULONG, &(o_nResult), 0, NULL);
// 		
// 		SQLSMALLINT    nColCnts          = 0;
// 		while(TRUE)
// 		{
// 			SQLNumResultCols(hstmt, &nColCnts);
// 			if(nColCnts <= 0)
// 			{// 2008-07-25 by cmkwon, ResultCols 0 이면 적용된 RowCount 이다 
// 				ret = SQLMoreResults(hstmt);
// 				if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
// 				{
// 					break;
// 				}
// 				continue;
// 			}
// 			ret = SQLFetch(hstmt);
// 			if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
// 			{
// 				ret = SQLMoreResults(hstmt);                 // 2008-07-25 by cmkwon, 다음 Results 가 있는지를 한번더 체크한다.
// 				if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
// 				{
// 					break;
// 				}
// 				continue;
// 			}
// 		}
// 		
// 		if(FALSE == o_nResult)
// 		{
// 			((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_COMMON_LOGIN_FAILED);
// 			SQLFreeStmt(hstmt, SQL_CLOSE);
// 			SAFE_DELETE(pRMsg);
// 			return;
// 		}
//	}

	
	/*[Stored Query Definition]************************************************
	--!!!!
	-- Name:
	-- Desc:2006-06-02 by cmkwon, 추가함
	--		2006-11-15 by cmkwon, Select 검색 필드 추가(td_account테이블에 추가된 필드 - GameContinueTimeInSecondOfToday, LastGameEndDate)
	--		2007-06-28 by cmkwon, 중국 방심취관련(출생년월일 FielServer로 가져오기) - 검색 결과에 BirthYear 필드 추가
	--		// 2007-09-12 by cmkwon, 베트남 2차패스워드 구현 - atum_PreServerGetAccountInfo 프로시저 수정
	--====
	CREATE PROCEDURE dbo.atum_PreServerGetAccountInfo
		@i_accname			varchar(20)
	AS
		-- // 2007-09-12 by cmkwon, 베트남 2차패스워드 구현 - SecondaryPassword 가져오기 추가
		SELECT AccountUniqueNumber, AccountType, Password, RegisteredDate, GameContinueTimeInSecondOfToday, LastGameEndDate, BirthYear, SecondaryPassword
		FROM td_Account WITH (NOLOCK)
		WHERE AccountName = @i_accname
	GO
	**************************************************************************/

	SQLINTEGER arrCB[10] = {SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS ,SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS};	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 날짜는 이전에 로그인한 날짜로딩을 위해 하나 추가
	SQLBindParameter(hstmt, 1,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pRMsg->AccountName, 0, &arrCB[0]);
 	ret = SQLExecDirect(hstmt, PROCEDURE_080822_0265, SQL_NTS);
 	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO && ret != SQL_NO_DATA)
 	{
 		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@atum_PreServerGetAccountInfo Failed!\r\n", TRUE);
 		SQLFreeStmt(hstmt, SQL_CLOSE);
 		q.pIOCPSocket->SendErrorMessage(T_PC_CONNECT_LOGIN, ERR_DB_EXECUTION_FAILED);
 		SAFE_DELETE(pRMsg);
 		return;
 	}
	if(ret == SQL_NO_DATA)
	{// 인증 실패 (아이디가 없음)

		SQLFreeStmt(hstmt, SQL_CLOSE);
		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_DB_NO_SUCH_ACCOUNT);
		SAFE_DELETE(pRMsg);
		return;
	}

 	char szMD5String[SIZE_MAX_PASSWORD_MD5_STRING];			MEMSET_ZERO(szMD5String, SIZE_MAX_PASSWORD_MD5_STRING);
 	MD5::MD5Binary2String(pRMsg->Password, szMD5String);
	SQL_TIMESTAMP_STRUCT		tmSqlTime;		MEMSET_ZERO(&tmSqlTime, sizeof(tmSqlTime));
	SQL_TIMESTAMP_STRUCT		tmSqlTime2;		MEMSET_ZERO(&tmSqlTime2, sizeof(tmSqlTime2));
	SQL_TIMESTAMP_STRUCT		tmSqlTime3;		MEMSET_ZERO(&tmSqlTime3, sizeof(tmSqlTime3));		// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 날짜는 이전에 로그인한 날짜	

	int nBirthYear = 0;		// 2007-06-28 by cmkwon, 중국 방심취관련(출생년월일 FielServer로 가져오기) - 출생년도(중국은 출생년월일)를 가져옴
 	SQLBindCol(hstmt, 1, SQL_C_ULONG, &accInfo.AccountUniqueNumber, 0,						&arrCB[1]);
 	SQLBindCol(hstmt, 2, SQL_C_USHORT, &accInfo.AccountType, 0,								&arrCB[2]); 
	SQLBindCol(hstmt, 3, SQL_C_CHAR, accInfo.PasswordFromDB, SIZE_MAX_PASSWORD_MD5_STRING,	&arrCB[3]);
	SQLBindCol(hstmt, 4, SQL_C_TIMESTAMP, &tmSqlTime, 0,									&arrCB[4]);
 	SQLBindCol(hstmt, 5, SQL_C_LONG, &accInfo.GameContinueTimeInSecondOfToday, 0,			&arrCB[5]);		// 2006-11-15 by cmkwon
	SQLBindCol(hstmt, 6, SQL_C_TIMESTAMP, &tmSqlTime2, 0,									&arrCB[6]);		// 2006-11-15 by cmkwon
	SQLBindCol(hstmt, 7, SQL_C_LONG, &nBirthYear, 0,										&arrCB[7]);		// 2007-06-28 by cmkwon, 중국 방심취관련(출생년월일 FielServer로 가져오기)
	SQLBindCol(hstmt, 8, SQL_C_CHAR, accInfo.SecondaryPassword, SIZE_MAX_PASSWORD_MD5_STRING,	&arrCB[8]);	// 2007-09-12 by cmkwon, 베트남 2차패스워드 구현 - SecondaryPassword 가져오기 추가
	SQLBindCol(hstmt, 9, SQL_C_TIMESTAMP, &tmSqlTime3, 0,	&arrCB[9]);	// 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 날짜는 이전에 로그인한 날짜확인을 위해	
 	
 	while( SQL_NO_DATA != (ret = SQLFetch(hstmt)) );
 	SQLFreeStmt(hstmt, SQL_CLOSE);
	accInfo.AccountRegisteredDate	= tmSqlTime;
	accInfo.LastGameEndDate			= tmSqlTime2;			// 2006-11-15 by cmkwon
	accInfo.SetBirthday(nBirthYear);						// 2007-06-28 by cmkwon, 중국 방심취관련(출생년월일 FielServer로 가져오기) - 

	if(FALSE == IS_VALID_UNIQUE_NUMBER(accInfo.AccountUniqueNumber))
	{// 2006-06-02 by cmkwon, AccountUID 체크 - 인증 실패 (아이디가 없음)
		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_DB_NO_SUCH_ACCOUNT);
		SAFE_DELETE(pRMsg);
		return;
	}

	if(0 != stricmp(szMD5String, accInfo.PasswordFromDB))
	{// 2006-06-02 by cmkwon, 비번 체크
 		char szEncodedString[SIZE_MAX_PASSWORD_MD5_STRING];
 		BYTE byPass[SIZE_MAX_PASSWORD_MD5];
		MD5 md5_instance; 
 		char szTmPassword[1024];		MEMSET_ZERO(szTmPassword, 1024); 		
 		wsprintf(szTmPassword, "%s%s", MD5_PASSWORD_ADDITIONAL_STRING, accInfo.PasswordFromDB);
 		md5_instance.MD5Encode(szTmPassword, byPass);
 		MD5::MD5Binary2String(byPass, szEncodedString);
 		if (0 != stricmp(szEncodedString, szMD5String))
		{
	 		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_COMMON_LOGIN_FAILED);
			SAFE_DELETE(pRMsg);
			return;
		}
	}

	// start 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 날짜는 이전에 로그인한 날짜	
	// 비교할 타임 값 쿼리 내부에서 값을 비교 처리한다.	
	ATUM_DATE_TIME	CheckDateTime;
	CheckDateTime.SetCurrentDateTime();

	if(CheckDateTime.Year == tmSqlTime3.year) //년도도 같아야하고.
	{
		if(CheckDateTime.Month == tmSqlTime3.month) //달도 같아야 한다.
		{
			if(CheckDateTime.Day != tmSqlTime3.day) //날짜가 오늘 같으면 루틴을 처리하지 않아야한다.
			{
				SQLRETURN retEv = 0;
				SQLINTEGER tmpNum = 1;
				SQLINTEGER tmpnum1= 0;
				SQLINTEGER AccountUniqueNumber = accInfo.AccountUniqueNumber;
				SQLINTEGER	arrcb1[3] = {SQL_NTS,SQL_NTS,SQL_NTS}; 

				retEv = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG,	 SQL_INTEGER, 0,							0,	&tmpNum,				0, &arrcb1[0]); // 현재는 디폴트로 사용함
				retEv = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_ULONG,	 SQL_INTEGER, 0,							0,	&AccountUniqueNumber,	0, &arrcb1[1]);
				retEv = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_ULONG,	 SQL_INTEGER, 0,							0,	&tmpnum1,				0, &arrcb1[2]); // 처음 삽입은 무조껀 0으로 한다.
				
				ret = SQLExecDirect(hstmt, PROCEDURE_LOGINITEMEVENT_110825_0001, SQL_NTS);
				if( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
				{
					ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@atum_InsertLoginItemEvent Failed!\n", TRUE);
					SQLFreeStmt(hstmt, SQL_CLOSE);
					// return; 리턴은 하지 말아야 한다. 인증에 실패하게 된다.
				}
			}
		}
	}
	// end 2011-08-25 by shcho, 횟수별 아이템 지급기능 구현 - 날짜는 이전에 로그인한 날짜	
	
// 2008-09-11 by cmkwon, 러시아 Innova_Rus 인증 시스템 수정 - 위로 이동함. 긴존 소스는 주석 처리
// 	//////////////////////////////////////////////////////////////////////////
// 	// 2008-08-21 by dhjin, Innova BillingDB 관련처리
// 	if(LANGUAGE_TYPE_RUSSIAN ==  g_pPreGlobal->GetLanguageType())
// 	{
// 		SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pRMsg->AccountName, 0, NULL);
// 		SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, ((CPreIOCPSocket*)q.pIOCPSocket)->GetPeerIP(), 0, NULL);
// 		ret = SQLExecDirect(hstmt, (UCHAR*)"{call Usp_Do_Login(?,?)}", SQL_NTS);
//  		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO && ret != SQL_NO_DATA)
//  		{
//  			ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"Usp_Do_Login Failed!\r\n", TRUE);
//  			SQLFreeStmt(hstmt, SQL_CLOSE);
//  			q.pIOCPSocket->SendErrorMessage(T_PC_CONNECT_LOGIN, ERR_DB_EXECUTION_FAILED);
//  			SAFE_DELETE(pRMsg);
//  			return;
//  		}		
// 
// 		int	o_nResult = 0;
// 		SQLBindCol(hstmt, 1, SQL_C_ULONG, &(o_nResult), 0, NULL);
// 
// 		SQLSMALLINT    nColCnts          = 0;
// 		while(TRUE)
// 		{
// 			SQLNumResultCols(hstmt, &nColCnts);
// 			if(nColCnts <= 0)
// 			{// 2008-07-25 by cmkwon, ResultCols 0 이면 적용된 RowCount 이다 
// 				ret = SQLMoreResults(hstmt);
// 				if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
// 				{
// 					break;
// 				}
// 				continue;
// 			}
// 			ret = SQLFetch(hstmt);
// 			if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
// 			{
// 				ret = SQLMoreResults(hstmt);                 // 2008-07-25 by cmkwon, 다음 Results 가 있는지를 한번더 체크한다.
// 				if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
// 				{
// 					break;
// 				}
// 				continue;
// 			}
// 		}
// 
// 		if(FALSE == o_nResult)
// 		{
// 			((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_COMMON_LOGIN_FAILED);
//  			SQLFreeStmt(hstmt, SQL_CLOSE);
// 			SAFE_DELETE(pRMsg);
// 			return;
// 		}
// 
// 	}

 	/*[Stored Query Definition]************************************************
	--!!!!
	-- Name:
	-- Desc:2006-06-02 by cmkwon, 추가함
	--====
	CREATE PROCEDURE atum_PreServerUpdateLastLoginDate
		@i_accUID			INT
	AS
		UPDATE td_Account
			SET LastLoginDate = GetDate()
			WHERE AccountUniqueNumber = @i_accUID
	GO
 	**************************************************************************/
	SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &accInfo.AccountUniqueNumber, 0, NULL);
	ret = SQLExecDirect(hstmt, PROCEDURE_080822_0266, SQL_NTS);
	ret = SQLMoreResults(hstmt);
 	SQLFreeStmt(hstmt, SQL_CLOSE);

	((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_NO_ERROR);
	SAFE_DELETE(pRMsg);

// 2006-06-02 by cmkwon
// 	/*[Stored Query Definition]************************************************
// 	CREATE PROCEDURE atum_PreServerLogin
// 		@accname	varchar(20),
// 		@passwd		varchar(35)
// 	AS
// 		-- 마지막 로그인 시간 저장
// 		UPDATE Account
// 		SET LastLoginDate = GetDate()
// 		WHERE AccountName = @accname
// 
// 		SELECT AccountUniqueNumber, AccountType
// 		FROM td_account
// 		WHERE AccountName = @accname AND Password = @passwd
// 	GO
// 	**************************************************************************/
// 	_strlwr(pRMsg->AccountName);
// 	char szMD5String[SIZE_MAX_PASSWORD_MD5_STRING];
// 	RETCODE ret;
// 	SQLINTEGER arrCB[4] = {SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS};
// 	MD5::MD5Binary2String(pRMsg->Password, szMD5String);
// 	SQLBindParameter(hstmt, 1,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pRMsg->AccountName, 0, &arrCB[1]);
// 	SQLBindParameter(hstmt, 2,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_PASSWORD_MD5_STRING, 0, szMD5String, 0, &arrCB[2]);
// 
// 	ret = SQLExecDirect(hstmt, (UCHAR*)"{call dbo.atum_PreServerLogin(?, ?)}", SQL_NTS);
// 	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO && ret != SQL_NO_DATA)
// 	{
// 		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@QP_PreServerLogin Failed!\r\n", TRUE);
// 		SQLFreeStmt(hstmt, SQL_CLOSE);
// 		q.pIOCPSocket->SendErrorMessage(T_PC_CONNECT_LOGIN, ERR_DB_EXECUTION_FAILED);
// 		SAFE_DELETE(pRMsg);
// 		return;
// 	}
// 
// 	if (ret == SQL_NO_DATA)
// 	{// 인증 실패 (아이디가 없음)
// 
// 		SQLFreeStmt(hstmt, SQL_CLOSE);
// 		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, 0, 0, ERR_COMMON_LOGIN_FAILED);
// 		SAFE_DELETE(pRMsg);
// 		return;
// 	}
// 
// 	// 첫 번 째 '마지막 로그인 시간 저장' 부분 넘김
// 	ret = SQLMoreResults(hstmt);
// 
// 	// bind columns
// 	SQLBindCol(hstmt, 1, SQL_C_ULONG, &nAccountUniqueNumber, 0, NULL);
// 	SQLBindCol(hstmt, 2, SQL_C_USHORT, &nAccountType, 0, NULL);
// 
// 	// AccountUniqueNumber, AccountType 반환
// 	ret = SQLFetch(hstmt);
// 	SQLFreeStmt(hstmt, SQL_CLOSE);
// 
// 	// 인코딩되지 않은 경우를 대비
// 	if (ret == SQL_NO_DATA)
// 	{
// 		char szPasswordFromDB[SIZE_MAX_PASSWORD_MD5_STRING];
// 		char szEncodedString[SIZE_MAX_PASSWORD_MD5_STRING];
// 		BYTE byPass[SIZE_MAX_PASSWORD_MD5];
// 
// 		char pTmpSql[1024];
// 		_strlwr(pRMsg->AccountName);
// 		sprintf(pTmpSql, "SELECT AccountUniqueNumber, AccountType, Password \
// 							FROM td_Account	 \
// 							WHERE AccountName = \'%s\'", pRMsg->AccountName);
// 
// 		ret = SQLExecDirect(hstmt, (UCHAR*)pTmpSql, SQL_NTS);
// 
// 		if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO ) {
// 			ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@QP_PreServerLogin Failed!\r\n", TRUE);
// 			SQLFreeStmt(hstmt, SQL_CLOSE);
// 			q.pIOCPSocket->SendErrorMessage(T_PRE_DB, ERR_DB_EXECUTION_FAILED);
// 			SAFE_DELETE(pRMsg);
// 			return;
// 		}
// 
// 		SQLBindCol(hstmt, 1, SQL_C_ULONG, &nAccountUniqueNumber, 0, NULL);
// 		SQLBindCol(hstmt, 2, SQL_C_USHORT, &nAccountType, 0, NULL);
// 		SQLBindCol(hstmt, 3, SQL_C_CHAR, szPasswordFromDB, SIZE_MAX_PASSWORD_MD5_STRING, &arrCB[3]);
// 
// 		ret = SQLFetch(hstmt);
// 		SQLFreeStmt(hstmt, SQL_CLOSE);
// 
// 		MD5 md5_instance;
// 
// 		char szTmPassword[1024];			// 2006-05-22 by cmkwon, 비번에 추가 스트링 적용
// 		MEMSET_ZERO(szTmPassword, 1024);
// 		wsprintf(szTmPassword, "%s%s", MD5_PASSWORD_ADDITIONAL_STRING, szPasswordFromDB);
// 		md5_instance.MD5Encode(szTmPassword, byPass);
// 		MD5::MD5Binary2String(byPass, szEncodedString);
// 
// 		if (strcmp(szEncodedString, szMD5String) == 0)
// 		{
// 			ret = SQL_SUCCESS;
// 		}
// 		else
// 		{
// 			ret = SQL_NO_DATA;
// 		}
// 	}
// 
// 	if (ret != SQL_NO_DATA)
// 	{
// 		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, nAccountUniqueNumber, nAccountType, ERR_NO_ERROR);
// 	}
// 	else
// 	{
// 		// 인증 실패 (아이디가 없거나, 패스워드가 틀림)
// 		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, 0, 0, ERR_COMMON_LOGIN_FAILED);
// 	}
//	SAFE_DELETE(pRMsg);
}


// 2005-06-02 by cmkwon, void CPreIOCP::LoadBlockedAccounts()에서 처리
//// QT_LoadBlockedAccount
//void CAtumPreDBManager::QP_LoadBlockedAccount(DB_QUERY q, SQLHSTMT hstmt)
//{
//	// lock
//	m_pPreIOCP2->m_setBlockedAccounts.lock();
//
//	BOOL	ret;
//	char	szBlockedAccount[SIZE_MAX_ACCOUNT_NAME];
//	SDWORD	cb1;
//
//	ret = SQLExecDirect(hstmt, (UCHAR*)"SELECT * FROM td_BlockedAccounts", SQL_NTS);
//
//	cb1 = SQL_NTS;
//	SQLBindCol(hstmt, 1, SQL_C_CHAR, szBlockedAccount, SIZE_MAX_ACCOUNT_NAME, &cb1);
//
//	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
//	{
//		// unlock
//		m_pPreIOCP2->m_setBlockedAccounts.unlock();
//		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"QP_LoadBlockedAccount() Failed!\n", TRUE);
//		SQLFreeStmt(hstmt, SQL_CLOSE);
//		return;
//	}
//
//	// initialize to 0x00
//	memset(szBlockedAccount, 0x00, SIZE_MAX_ACCOUNT_NAME);
//	while ( (ret = SQLFetch(hstmt)) != SQL_NO_DATA)
//	{
//		m_pPreIOCP2->m_setBlockedAccounts.insertLock(szBlockedAccount);
//
//		// initialize to 0x00
//		memset(szBlockedAccount, 0x00, SIZE_MAX_ACCOUNT_NAME);
//	}
//
//	SQLFreeStmt(hstmt, SQL_CLOSE);
//
//	// unlock
//	m_pPreIOCP2->m_setBlockedAccounts.unlock();
//}

// QT_BlockUser
void CAtumPreDBManager::QP_BlockUser(DB_QUERY q, SQLHSTMT hstmt)
{
	SBLOCKED_ACCOUNT_INFO *pBlockedAccInfo = (SBLOCKED_ACCOUNT_INFO*)q.pQueryParam;
	/*[Stored Query Definition]************************************************
	-- 2005-06-02 by cmkwon
	-- 계정 블럭 리스트에 추가 혹은 정보 Update
	--			2007-01-10 by cmkwon, td_BlockedAccounts 테이블에 BlockedReasonForOnlyAdmin 필드 추가함
	CREATE PROCEDURE atum_Insert_BlockedAccounts
		@i_AccountName			VARCHAR(20),
		@i_BlockedType			INT,
		@i_StartDate			VARCHAR(30),
		@i_EndDate				VARCHAR(30),
		@i_AdminAccountName		VARCHAR(20),
		@i_BlockedReason		VARCHAR(200),			-- 유저가 보는 블럭 사유
		@i_BlockedReasonForOnlyAdmin	VARCHAR(200)	-- 2007-01-10 by cmkwon, 추가함 - 관리자가 보는 블럭사유
	AS	
		DECLARE @blockedTy INT
		SET @blockedTy = (SELECT BlockedType FROM td_BlockedAccounts WHERE AccountName = @i_AccountName)
		
		IF (@blockedTy IS NULL)
			BEGIN
				INSERT INTO td_BlockedAccounts
					VALUES (@i_AccountName, @i_BlockedType, @i_StartDate, @i_EndDate, @i_AdminAccountName, @i_BlockedReason, @i_BlockedReasonForOnlyAdmin)
			END
		ELSE
			BEGIN
				UPDATE td_BlockedAccounts
					SET BlockedType = @i_BlockedType, StartDate = @i_StartDate
							, EndDate = @i_EndDate, AdminAccountName = @i_AdminAccountName, BlockedReason = @i_BlockedReason, BlockedReasonForOnlyAdmin = @i_BlockedReasonForOnlyAdmin
						WHERE AccountName = @i_AccountName
			END	
	GO
	**************************************************************************/

	SQLINTEGER arrCB[8] = {SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS};
	SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pBlockedAccInfo->szBlockedAccountName, 0, &arrCB[1]);
	SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pBlockedAccInfo->enBlockedType, 0, &arrCB[2]);
	char tmpStartTimeBuf[SIZE_MAX_SQL_DATETIME_STRING];
	pBlockedAccInfo->atimeStartTime.GetSQLDateTimeString(tmpStartTimeBuf, SIZE_MAX_SQL_DATETIME_STRING);
	SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_SQL_DATETIME_STRING, 0, tmpStartTimeBuf, 0, &arrCB[3]);
	char tmpEndTimeBuf[SIZE_MAX_SQL_DATETIME_STRING];
	pBlockedAccInfo->atimeEndTime.GetSQLDateTimeString(tmpEndTimeBuf, SIZE_MAX_SQL_DATETIME_STRING);
	SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_SQL_DATETIME_STRING, 0, tmpEndTimeBuf, 0, &arrCB[4]);
	SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pBlockedAccInfo->szBlockAdminAccountName, 0, &arrCB[5]);
	SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_BLOCKED_ACCOUNT_REASON, 0, pBlockedAccInfo->szBlockedReasonForUser, 0, &arrCB[6]);
	SQLBindParameter(hstmt, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_BLOCKED_ACCOUNT_REASON, 0, pBlockedAccInfo->szBlockedReasonForOnlyAdmin, 0, &arrCB[7]);		// 2007-01-10 by cmkwon

	RETCODE ret = SQLExecDirect(hstmt, PROCEDURE_080822_0267, SQL_NTS);

	if (ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
	{
		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@QP_BlockUser() Failed!\r\n", TRUE);
		SQLFreeStmt(hstmt, SQL_CLOSE);
		SAFE_DELETE(pBlockedAccInfo);
		return;
	}
	SQLFreeStmt(hstmt, SQL_CLOSE);

	///////////////////////////////////////////////////////////////////////////////	
	// 2008-01-30 by cmkwon, 계정 블럭 로그 남기기 구현 - 로그를 추가한다.
	if(FALSE == this->LogInsertBlockUnblock(hstmt, pBlockedAccInfo, T1_FL_LOG_BLOCK_ACCOUNT))
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[Error] Insert log error!!, AccountName(%s) BlockType(%d) Period(%s~%s) AdminAccName(%s) ReasonForUser(%s) ReasonForAdmin(%s)\r\n"
			, pBlockedAccInfo->szBlockedAccountName, pBlockedAccInfo->enBlockedType, pBlockedAccInfo->atimeStartTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING))
			, pBlockedAccInfo->atimeEndTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)), pBlockedAccInfo->szBlockAdminAccountName
			, pBlockedAccInfo->szBlockedReasonForUser, pBlockedAccInfo->szBlockedReasonForOnlyAdmin);
	}

	// 2008-04-04 by cmkwon, 요 메시지는 무조건 전송
	INIT_MSG_WITH_BUFFER(MSG_PA_ADMIN_BLOCK_ACCOUNT_OK, T_PA_ADMIN_BLOCK_ACCOUNT_OK, msgBlockOK, msgBlockOKBuf);
	*msgBlockOK = *pBlockedAccInfo;
	m_pPreIOCP2->SendMessageToAdminTool(msgBlockOKBuf, MSG_SIZE(MSG_PA_ADMIN_BLOCK_ACCOUNT_OK));

	// Notify
	if (q.pIOCPSocket
		&& q.pIOCPSocket->IsUsing())
	{
		// 2008-01-31 by cmkwon, 계정 블럭/해제 명령어로 가능한 시스템 구현 - 아래와 같이 SocketType 별로 처리
		if(ST_FIELD_SERVER == q.pIOCPSocket->m_PeerSocketType)
		{
			// 2008-01-31 by cmkwon, 계정 블럭/해제 명령어로 가능한 시스템 구현 - FieldServer 로 결과 전송
			INIT_MSG_WITH_BUFFER(MSG_FP_ADMIN_BLOCKACCOUNT_OK, T_FP_ADMIN_BLOCKACCOUNT_OK, pSMsgOK, SendBuf);
			pSMsgOK->ErrCode	= ERR_NO_ERROR;
			STRNCPY_MEMSET(pSMsgOK->BlockedAccName, pBlockedAccInfo->szBlockedAccountName, SIZE_MAX_ACCOUNT_NAME);
			pSMsgOK->AdminFieldServerClientIndex	= pBlockedAccInfo->AdminFieldServerClientIndex;
			STRNCPY_MEMSET(pSMsgOK->AdminAccName, pBlockedAccInfo->szBlockAdminAccountName, SIZE_MAX_ACCOUNT_NAME);
			pSMsgOK->atimeEndTime					= pBlockedAccInfo->atimeEndTime;
			q.pIOCPSocket->SendAddData(SendBuf, MSG_SIZE(MSG_FP_ADMIN_BLOCKACCOUNT_OK));
		}
	}
	SAFE_DELETE(pBlockedAccInfo);
}

// QT_UnblockUser
void CAtumPreDBManager::QP_UnblockUser(DB_QUERY q, SQLHSTMT hstmt)
{
// 2008-01-30 by cmkwon, 계정 블럭 로그 남기기 구현 - 아래와 같이 수정
// 	char *szAccountName = (char*)q.pQueryParam;
	SBLOCKED_ACCOUNT_INFO *pBlockedAccInfo = (SBLOCKED_ACCOUNT_INFO*)q.pQueryParam;

	/*[Stored Query Definition]************************************************
	-- 계정 블럭 리스트에서 제거
	CREATE PROCEDURE atum_Delete_BlockedAccounts
		@i_AccountName			VARCHAR(20)
	AS
		DELETE FROM td_BlockedAccounts
			WHERE AccountName = @i_AccountName	
	GO
	**************************************************************************/

	SQLINTEGER cb = SQL_NTS;
	// 2008-01-30 by cmkwon, 계정 블럭 로그 남기기 구현 - 아래와 같이 수정
	//SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, szAccountName, 0, &cb);
	SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pBlockedAccInfo->szBlockedAccountName, 0, &cb);

	// 2008-01-29 by cmkwon, T_A: 계정 블럭 관련 쿼리 수정 - 사용하지 않는 코드임
	//char szQuery[512];
	//sprintf(szQuery, "DELETE FROM td_BlockedAccounts WHERE AccountName LIKE \'%s\'", szAccountName);
	RETCODE ret = SQLExecDirect(hstmt, PROCEDURE_080822_0268, SQL_NTS);

	if (ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO && ret != SQL_NO_DATA)
	{
		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@QP_UnblockUser() Failed!\r\n", TRUE);
		SQLFreeStmt(hstmt, SQL_CLOSE);
		SAFE_DELETE(pBlockedAccInfo);
		return;
	}
	SQLFreeStmt(hstmt, SQL_CLOSE);

	///////////////////////////////////////////////////////////////////////////////	
	// 2008-01-30 by cmkwon, 계정 블럭 로그 남기기 구현 - 로그를 추가한다.
	if(FALSE == this->LogInsertBlockUnblock(hstmt, pBlockedAccInfo, T1_FL_LOG_UNBLOCK_ACCOUNT))
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[Error] Insert log error!!, AccountName(%s) BlockType(%d) Period(%s~%s) AdminAccName(%s) ReasonForUser(%s) ReasonForAdmin(%s)\r\n"
			, pBlockedAccInfo->szBlockedAccountName, pBlockedAccInfo->enBlockedType, pBlockedAccInfo->atimeStartTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING))
			, pBlockedAccInfo->atimeEndTime.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)), pBlockedAccInfo->szBlockAdminAccountName
			, pBlockedAccInfo->szBlockedReasonForUser, pBlockedAccInfo->szBlockedReasonForOnlyAdmin);
	}

	// 2008-04-04 by cmkwon, 이 메시지는 무조건 전송 해야 한다.
	INIT_MSG_WITH_BUFFER(MSG_PA_ADMIN_UNBLOCK_ACCOUNT_OK, T_PA_ADMIN_UNBLOCK_ACCOUNT_OK, msgUnblockOK, msgUnblockOKBuf);
	STRNCPY_MEMSET(msgUnblockOK->AccountName, pBlockedAccInfo->szBlockedAccountName, SIZE_MAX_ACCOUNT_NAME);
	m_pPreIOCP2->SendMessageToAdminTool(msgUnblockOKBuf, MSG_SIZE(MSG_PA_ADMIN_UNBLOCK_ACCOUNT_OK));
	
	// Notify
	if (q.pIOCPSocket
		&& q.pIOCPSocket->IsUsing())
	{
		// 2008-01-31 by cmkwon, 계정 블럭/해제 명령어로 가능한 시스템 구현 - 아래와 같이 SocketType 별로 처리
		if(ST_FIELD_SERVER == q.pIOCPSocket->m_PeerSocketType)
		{
			// 2008-01-31 by cmkwon, 계정 블럭/해제 명령어로 가능한 시스템 구현 - FieldServer 로 결과 전송
			INIT_MSG_WITH_BUFFER(MSG_FP_ADMIN_UNBLOCKACCOUNT_OK, T_FP_ADMIN_UNBLOCKACCOUNT_OK, pSMsgOK, SendBuf);
			pSMsgOK->ErrCode	= ERR_NO_ERROR;
			STRNCPY_MEMSET(pSMsgOK->UnblockedAccName, pBlockedAccInfo->szBlockedAccountName, SIZE_MAX_ACCOUNT_NAME);
			pSMsgOK->AdminFieldServerClientIndex	= pBlockedAccInfo->AdminFieldServerClientIndex;
			STRNCPY_MEMSET(pSMsgOK->AdminAccName, pBlockedAccInfo->szBlockAdminAccountName, SIZE_MAX_ACCOUNT_NAME);
			q.pIOCPSocket->SendAddData(SendBuf, MSG_SIZE(MSG_FP_ADMIN_UNBLOCKACCOUNT_OK));
		}
	}
	SAFE_DELETE(pBlockedAccInfo);
}

// QT_MGameLogin
void CAtumPreDBManager::QP_MGameLogin(DB_QUERY q, SQLHSTMT hstmt)
{
	MSG_PC_CONNECT_LOGIN	*pRMsg = (MSG_PC_CONNECT_LOGIN*)q.pQueryParam;
	CAccountInfo			accInfo;
	SQLHSTMT				hstmt_ext = 0;
	ExternalAuthentication(&accInfo, pRMsg, hstmt, hstmt_ext, FALSE);
	if(FALSE == IS_VALID_UNIQUE_NUMBER(accInfo.AccountUniqueNumber))
	{
		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_COMMON_LOGIN_FAILED);
	}
	else
	{
		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, &accInfo, ERR_NO_ERROR);
	}
	
	SAFE_DELETE(pRMsg);
	return;

// 2006-06-02 by cmkwon
// 	UID32_t					nAccountUniqueNumber = INVALID_UNIQUE_NUMBER;
// 	USHORT					nAccountType = 0;
// 	int						nMGameEventType = 0;
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	// MGameEvent 처리
// 	if(MGAME_EVENT_OPEN_BETA_ATTENDANCE == g_pPreGlobal->m_enMGameEventType
// 		&& g_pPreGlobal->IsExistAccountNameForMGameEvent(pRMsg->AccountName))
// 	{
// 		nMGameEventType = g_pPreGlobal->m_enMGameEventType;
// 	}
// 
// 	RETCODE ret;
// 
// 	/*[Stored Query Definition]************************************************
// 	CREATE PROCEDURE atum_PreServerMGameLogin
// 		@i_AccountName				VARCHAR(20),
// 		@i_AccountNameForSearch		VARCHAR(64),
// 		@i_Sex						TINYINT,			-- 1: 남, 2: 여
// 		@i_BirthYear				INT,				-- 생년
// 		@i_MGameEventType			INT,
// 		@o_AccountType				SMALLINT	OUTPUT
// 	AS
// 		DECLARE @AccountUniqueNumber INT
// 		
// 		SET @AccountUniqueNumber = (
// 			SELECT AccountUniqueNumber
// 			FROM td_account
// 			WHERE AccountName LIKE @i_AccountName
// 		)
// 
// 		-- 최초 접속자는 계정 추가
// 		IF (@AccountUniqueNumber IS NULL)
// 			BEGIN
// 				INSERT INTO td_Account(AccountName, Sex, BirthYear)
// 				VALUES(@i_AccountName, @i_Sex, @i_BirthYear)
// 			END
// 
// 		-- 마지막 로그인 시간 저장
// 		UPDATE td_Account
// 		SET LastLoginDate = GetDate()
// 		WHERE AccountName LIKE @i_AccountName
// 
// 		SET @AccountUniqueNumber = (
// 			SELECT AccountUniqueNumber
// 			FROM td_account
// 			WHERE AccountName LIKE @i_AccountName
// 		)
// 		
// 		SET @o_AccountType = (
// 			SELECT AccountType
// 			FROM td_Account
// 			WHERE AccountUniqueNumber = @AccountUniqueNumber
// 		)
// 
// 		RETURN @AccountUniqueNumber
// 	GO
// 	**************************************************************************/
// 	SQLBindParameter(hstmt, 1, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &nAccountUniqueNumber, 0, NULL);
// 	SDWORD pcbNTS = SQL_NTS;
// 	_strlwr(pRMsg->AccountName);
// 	SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, pRMsg->AccountName, 0, &pcbNTS);
// 
// 	char spbuf[SIZE_MAX_SQL_PATTERN_BUFFER];
// 	SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_SQL_PATTERN_BUFFER
// 		, 0, GetSqlPattern(pRMsg->AccountName, spbuf), 0, &pcbNTS);	
// 	SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_TINYINT, 0, 0, &pRMsg->MGameSEX, 0, NULL);
// 	SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pRMsg->MGameYear, 0, NULL);
// 	SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &nMGameEventType, 0, NULL);
// 	SQLBindParameter(hstmt, 7, SQL_PARAM_OUTPUT, SQL_C_USHORT, SQL_SMALLINT, 0, 0, &nAccountType, 0, NULL);
// 
// 	ret = SQLExecDirect(hstmt, (UCHAR*)"{? = call dbo.atum_PreServerMGameLogin(?, ?, ?, ?, ?, ?)}", SQL_NTS);
// 	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO )
// 	{
// 		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@atum_PreServerMGameLogin Failed!\r\n", TRUE);
// 		SQLFreeStmt(hstmt, SQL_CLOSE);
// 		q.pIOCPSocket->SendErrorMessage(T_PC_CONNECT_LOGIN, ERR_DB_EXECUTION_FAILED);
// 		SAFE_DELETE(pRMsg);
// 		return;
// 	}
// 
// 	// Clear any result sets generated.
// 	while ( ( ret = SQLMoreResults(hstmt) ) != SQL_NO_DATA );
// 	SQLFreeStmt(hstmt, SQL_CLOSE);
// 
// 	if (FALSE == IS_VALID_UNIQUE_NUMBER(nAccountUniqueNumber))
// 	{
// 		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, nAccountUniqueNumber, nAccountType, ERR_NO_ERROR);
// 	}
// 	else
// 	{
// 		// 인증 실패 (아이디가 없거나, 패스워드가 틀림)
// 		((CPreIOCPSocket*)q.pIOCPSocket)->ResPreLogin(pRMsg, 0, 0, ERR_COMMON_LOGIN_FAILED);
// 	}
// 
// 	SAFE_DELETE(pRMsg);
}


void CAtumPreDBManager::QP_LogTotalUser(DB_QUERY q, SQLHSTMT hstmt)
{
	MSG_DB_TOTAL_USER	*pRMsg = (MSG_DB_TOTAL_USER*)q.pQueryParam;

	RETCODE ret;
	SQLINTEGER arrCB[4] = {SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS};		// 2010-11 by dhjin, 아라리오 채널링 로그인.

	/*[Stored Query Definition]************************************************
	CREATE PROCEDURE atum_log_insert_total_user
		@i_ServerGroupName			VARCHAR(20),	
		@i_MGameServerID			INT,
		@i_UserCount				INT,
		@i_nUserCountsOtherPublisherConncect				INT
	AS
		INSERT INTO atum_log_total_user
		VALUES (GetDate(), @i_ServerGroupName, @i_MGameServerID, @i_UserCount, @i_nUserCountsOtherPublisherConncect)
	GO
	**************************************************************************/
	SQLBindParameter(hstmt, 1,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_SERVER_NAME, 0,
		pRMsg->szServerGroup, 0, &arrCB[0]);
	SQLBindParameter(hstmt, 2,SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pRMsg->nMGameServerID, 0, &arrCB[1]);
	SQLBindParameter(hstmt, 3,SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pRMsg->nUserCounts, 0, &arrCB[2]);

#ifdef S_ARARIO_HSSON
	SQLBindParameter(hstmt, 4,SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0, &pRMsg->nUserCountsOtherPublisherConncect, 0, &arrCB[3]);		// 2010-11 by dhjin, 아라리오 채널링 로그인.
#endif

	ret = SQLExecDirect(hstmt, PROCEDURE_080822_0269, SQL_NTS);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@atum_log_insert_total_user Failed!\r\n", TRUE);
		SQLFreeStmt(hstmt, SQL_CLOSE);
		SAFE_DELETE(pRMsg);
		return;
	}
	SQLFreeStmt(hstmt, SQL_CLOSE);
	SAFE_DELETE(pRMsg);
}

// 2010-06-01 by shcho, GLogDB 관련 -
void CAtumPreDBManager::QP_InsertGlogAccount(DB_QUERY q, SQLHSTMT hstmt)
{// QT_InsertGlogAccount
	QPARAM_GLOG_INSERT_ACCOUNT	*pRMsg = (QPARAM_GLOG_INSERT_ACCOUNT*)q.pQueryParam;
	
	RETCODE ret;
	SQLINTEGER arrCB[4] = {SQL_NTS, SQL_NTS, SQL_NTS, SQL_NTS};

	/*[Stored Query Definition]************************************************
	ALTER PROCEDURE dbo.atum_InsertGlogAccount
		@i_AccountName				VARCHAR(20),
		@i_GamePublisher			NVARCHAR(128),		-- 게임서비스사 이름
		@i_GameServerIP				NVARCHAR(64)			-- 게임서버IP (서비스지역 표시를 위해(ex:한국,미국등등))
	AS
		--AccountUID 받아오기 퍼블리셔와 이름을 검색한다.
		DECLARE @AccountName	 	NVARCHAR(128)
		SET @AccountName = (SELECT AccountName FROM GLog.dbo.GLog_Account WITH (NOLOCK) WHERE AccountName = @i_AccountName and GamePublisher = @i_GamePublisher)
	
	  
		-- 최초 접속자는 계정 추가
		IF (@AccountName IS NULL)
		BEGIN
			--// 2010-06-01 by shcho, GLogDB 관련 - 서비스사 이름, IP는 받아와야 한다.	
			INSERT GLog.dbo.GLog_Account (AccountName, GamePublisher, GameName, GameServerIP, Birthday, Sex, RegDate ) 
			SELECT @i_AccountName, @i_GamePublisher, 'AceOnline', @i_GameServerIP,  CAST(BirthYear AS NVARCHAR(64)), Sex-1, RegisteredDate
			FROM atum2_db_account.dbo.td_account
			WHERE AccountName = @i_AccountName
		END
			  
	GO
	**************************************************************************/
	SQLBindParameter(hstmt, 1,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0,pRMsg->szAccountName, 0, &arrCB[0]);
	SQLBindParameter(hstmt, 2,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,	128, 0, g_pPreGlobal->GetGamePublisherName(), 0, &arrCB[1]);
	SQLBindParameter(hstmt, 3,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,	64,	0, g_pPreGlobal->GetPublicIPLocal(), 0, &arrCB[2]);

	ret = SQLExecDirect(hstmt, PROCEDURE_GLOG_100601_0006, SQL_NTS);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@QP_InsertGlogAccount Failed!\r\n", TRUE);
		SQLFreeStmt(hstmt, SQL_CLOSE);
		SAFE_DELETE(pRMsg);
		return;
	}
	SQLFreeStmt(hstmt, SQL_CLOSE);
	SAFE_DELETE(pRMsg);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::LogInsertBlockUnblock(SQLHSTMT hstmt, SBLOCKED_ACCOUNT_INFO *i_pBlockAccInfo, BYTE i_byLogType)
/// \brief		// 2008-01-30 by cmkwon, 계정 블럭 로그 남기기 구현 - CAtumPreDBManager::LogInsertBlockUnblock() 추가
/// \author		cmkwon
/// \date		2008-01-30 ~ 2008-01-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::LogInsertBlockUnblock(SQLHSTMT hstmt, SBLOCKED_ACCOUNT_INFO *i_pBlockAccInfo, BYTE i_byLogType)
{
	/*[Stored Query Definition]************************************************
	--------------------------------------------------------------------------------
	-- Name: atum_log_insert_block_unblock
	-- Desc: // 2008-01-30 by cmkwon, 계정 블럭 로그 남기기 구현 - 계정 블럭/수정/해제 정보 로그 추가하기
	--------------------------------------------------------------------------------
	CREATE PROCEDURE dbo.atum_log_insert_block_unblock
		@i_LogType				TINYINT,
		@i_AccountName			VARCHAR(20),
		@i_BlockedType			INT,
		@i_StartDate			VARCHAR(30),
		@i_EndDate				VARCHAR(30),
		@i_AdminAccountName		VARCHAR(20),
		@i_BlockedReason		VARCHAR(200),			-- 유저가 보는 블럭 사유
		@i_BlockedReasonForOnlyAdmin	VARCHAR(200)	-- 2007-01-10 by cmkwon, 추가함 - 관리자가 보는 블럭사유
	AS
		INSERT INTO dbo.atum_log_blockedAccount
		VALUES (@i_LogType, GetDate(), @i_AccountName, @i_BlockedType, @i_StartDate, @i_EndDate, @i_AdminAccountName, @i_BlockedReason, @i_BlockedReasonForOnlyAdmin)
	GO
	**************************************************************************/

	SQLINTEGER arrCB[9] = {SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS, SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS};
	char tmpStartTimeBuf[SIZE_MAX_SQL_DATETIME_STRING];
	char tmpEndTimeBuf[SIZE_MAX_SQL_DATETIME_STRING];
	i_pBlockAccInfo->atimeStartTime.GetSQLDateTimeString(tmpStartTimeBuf, SIZE_MAX_SQL_DATETIME_STRING);
	i_pBlockAccInfo->atimeEndTime.GetSQLDateTimeString(tmpEndTimeBuf, SIZE_MAX_SQL_DATETIME_STRING);
	SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_TINYINT, 0, 0, &i_byLogType, 0,													&arrCB[1]);
	SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_pBlockAccInfo->szBlockedAccountName, 0,		&arrCB[2]);
	SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &i_pBlockAccInfo->enBlockedType, 0,									&arrCB[3]);
	SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_SQL_DATETIME_STRING, 0, tmpStartTimeBuf, 0,						&arrCB[4]);
	SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_SQL_DATETIME_STRING, 0, tmpEndTimeBuf, 0,							&arrCB[5]);
	SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_pBlockAccInfo->szBlockAdminAccountName, 0,		&arrCB[6]);
	SQLBindParameter(hstmt, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_BLOCKED_ACCOUNT_REASON, 0, i_pBlockAccInfo->szBlockedReasonForUser, 0,		&arrCB[7]);
	SQLBindParameter(hstmt, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_BLOCKED_ACCOUNT_REASON, 0, i_pBlockAccInfo->szBlockedReasonForOnlyAdmin, 0,	&arrCB[8]);		// 2007-01-10 by cmkwon

	RETCODE ret = SQLExecDirect(hstmt, PROCEDURE_080822_0270, SQL_NTS);
	if (ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
	{
		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@atum_log_insert_block_unblock_ Failed!\r\n", TRUE);
		SQLFreeStmt(hstmt, SQL_CLOSE);
		return FALSE;
	}
	SQLFreeStmt(hstmt, SQL_CLOSE);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExternalAuthentication(CAccountInfo *o_pAccInfo, MSG_PC_CONNECT_LOGIN *i_pLogin, SQLHSTMT hstmt, SQLHSTMT hstmt_extAuth, BOOL i_bAuthenticateCheck/*=TRUE*/)
/// \brief		
///				// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 
/// \author		cmkwon
/// \date		2006-04-27 ~ 2006-04-27
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExternalAuthentication(CAccountInfo *o_pAccInfo, MSG_PC_CONNECT_LOGIN *i_pLogin, SQLHSTMT &hstmt, SQLHSTMT &hstmt_extAuth, BOOL i_bAuthenticateCheck/*=TRUE*/, UINT i_nClientIP/*=0*/)
{
	// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [언어-옵션] 추가 언어시에 외부 인증 처리 루틴에 추가

	char szJuminNum[SIZE_MAX_JUMIN_NUMBER]={NULL,};		// 2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기
	if(i_bAuthenticateCheck)
	{
		char szMD5String[SIZE_MAX_PASSWORD_MD5_STRING];
		MD5::MD5Binary2String(i_pLogin->Password, szMD5String);
		BOOL bExtAuth = FALSE;
		switch(g_pPreGlobal->GetLanguageType())
		{
		case LANGUAGE_TYPE_ENGLISH:
		case LANGUAGE_TYPE_GERMAN:		// 2008-07-04 by cmkwon, 독일어 버젼 외부인증 지원
		case LANGUAGE_TYPE_TURKISH:		// 2008-12-22 by cmkwon, 지원 서비스 추가(Gameforge4D 터키아, 불어, 이탈리아어) - 
		case LANGUAGE_TYPE_FRENCH:		// 2008-12-22 by cmkwon, 지원 서비스 추가(Gameforge4D 터키아, 불어, 이탈리아어) - 
		case LANGUAGE_TYPE_ITALIAN:		// 2008-12-22 by cmkwon, 지원 서비스 추가(Gameforge4D 터키아, 불어, 이탈리아어) - 
		case LANGUAGE_TYPE_POLISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
		case LANGUAGE_TYPE_SPANISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
			{
				// 2008-01-23 by cmkwon, S_P: Gameforge4D_Eng 외부 인증 시스템 추가 - 
				//bExtAuth = this->ExecuteExtAuth_GalaNet(&o_pAccInfo->nExtAuthAccountIDNum, i_pLogin->AccountName, szMD5String, hstmt_extAuth);
// 2008-02-11 by cmkwon, Yedang_Global_Eng 외부 인증 처리 - ExecuteExtAuth2 를 사용한다.
// #if defined(SERVICE_TYPE_ENGLISH_SERVER_1)
// 				return FALSE;		// 2008-01-23 by cmkwon, S_P: Gameforge4D_Eng 외부 인증 시스템 추가 - Yedang-Global_Eng 는 외부인증 상요하지 않음
// #endif
				// 2008-01-23 by cmkwon, S_P: Gameforge4D_Eng 외부 인증 시스템 추가 - 예당용 외부 인증 형식을 똑같이 사용한다.
				bExtAuth = this->ExecuteExtAuth2(i_pLogin->AccountName, szMD5String, i_pLogin->WebLoginAuthKey, hstmt_extAuth);
			}
			break;
		case LANGUAGE_TYPE_KOREAN:	// 2007-03-30 by cmkwon, 예당을 위해 수정함
		case LANGUAGE_TYPE_THAI:	// 2008-05-15 by cmkwon, WinnerOnline_Tha 에 외부 인증 지원 - 
		case LANGUAGE_TYPE_INDONESIA: // 2011-06-30 by shcho, 인도네시아 외부인증 지원 - 
// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 러시아 아래에 따로 추가함.
//		case LANGUAGE_TYPE_RUSSIAN:	// 2008-05-29 by cmkwon, 지원 서비스 추가(Innova_Rus 러시아어 추가) - 임시로 추가 함

// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 아래에 따로 처리함.
//		case LANGUAGE_TYPE_JAPANESE:	// 2008-12-03 by cmkwon, 지원 서비스 추가(일본 Arario_Jpn) - 임시로 추가 함
			{
				bExtAuth = this->ExecuteExtAuth2(i_pLogin->AccountName, szMD5String, i_pLogin->WebLoginAuthKey, hstmt_extAuth);
			}
			break;
		case LANGUAGE_TYPE_CHINESE:	// 2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기 - 중국 따로 처리
			{
				// 2007-07-03 by cmkwon, 중국 Yetime 비밀 번호 MD5 하지 않음 - 임시로 WebLoginAuthKey 필드 사용함
				bExtAuth = this->ExecuteExtAuthChina(szJuminNum, i_pLogin->AccountName, i_pLogin->WebLoginAuthKey, hstmt_extAuth);

				// 2007-06-27 by cmkwon, 중국 방심취 시스템 수정 - 미성년자 관련
				int nJuminLen = strlen(szJuminNum);
				if( bExtAuth
					&& (15 == nJuminLen || 18 == nJuminLen) )
				{
					char szBirthday[1024]={NULL,};
					if(15 == nJuminLen)
					{
						// 2007-06-29 by cmkwon, ex> 130429781111078, 13:성급번호, 04:시급번호, 29:현급번호, 781111:출생년월일(19XXXXXX), 078:인증번호(우수이면 남자, 기수이면 여자)
						strcpy(szBirthday, "19");
						memcpy(&szBirthday[2], &szJuminNum[6], 6);
					}
					else
					{
						// 2007-06-29 by cmkwon, ex> 222406198503051811, 22:성급번호, 24:시급번호, 06:현급번호, 19850305:출생년월일, 1811:인증번호(우수이면 남자, 기수이면 여자)
						memcpy(szBirthday, &szJuminNum[6], 8);
					}
					i_pLogin->MGameYear = atoi(szBirthday);
					o_pAccInfo->SetBirthday(i_pLogin->MGameYear);
				}
//  				// 2008-03-28 by cmkwon, 체크 시스템 로그 - 중국 방심취 관련 시스템 로그 추가, 주민번호 확인 차원
//  				g_pPreGlobal->WriteSystemLogEX(TRUE, "  [Notify] CAtumPreDBManager::ExternalAuthentication_ Acc(%s) JuminNum(%s) Birthday(%s)\r\n"
//  					, i_pLogin->AccountName, szJuminNum, o_pAccInfo->atBirthday.GetDateTimeString(STRNBUF(SIZE_MAX_SQL_DATETIME_STRING)));
			}
			break;
		case LANGUAGE_TYPE_TAIWANESE:	// 2008-10-08 by cmkwon, 대만 Netpower_Tpe 외부인증 구현 - 
			{
				bExtAuth = this->ExecuteExtAuth_Taiwanese(i_pLogin, szMD5String, hstmt_extAuth);
			}
			break;
		case LANGUAGE_TYPE_JAPANESE:	// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 왼부인증 모듈 호출
			{
				bExtAuth = this->ExecuteExtAuth_Arario(i_pLogin, szMD5String, i_pLogin->WebLoginAuthKey);
			}
			break;
		case LANGUAGE_TYPE_RUSSIAN:		// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 외부인증으로 변경
			{
				bExtAuth = this->ExecuteExtAuth_Innova(i_pLogin, i_nClientIP);
			}
			break;
		default:
			{
				bExtAuth = this->ExecuteExtAuth(i_pLogin->AccountName, szMD5String, hstmt_extAuth);
			}
		}
		
		if(FALSE == bExtAuth)
		{// 2006-04-27 by cmkwon, 외부 인증에서 실패함

			if(FALSE == IS_MASANG_IP(i_pLogin->PrivateIP))
			{// 2006-04-28 by cmkwon, 마상소프트 사내 IP가 아니면 인증 실패
				return FALSE;
			}

			// 2007-10-08 by cmkwon
			g_pPreGlobal->WriteSystemLogEX(TRUE, "[Notify] MasangIP authentication !!, AccountName(%s) WebAuthKey(%s) IP(%s)\r\n"
													, i_pLogin->AccountName, i_pLogin->WebLoginAuthKey, i_pLogin->PrivateIP);

//			char szQuery[1024];
			SDWORD pcbNTS = SQL_NTS;

			// 2008-07-02 by cmkwon, MySQL 지원 구현 - 
			//wsprintf(szQuery, "SELECT AccountUniqueNumber, AccountType, Password FROM td_Account WITH (NOLOCK) \
			//					WHERE AccountName = \'%s\'", i_pLogin->AccountName);
// 2008-08-27 by cmkwon, 날쿼리를 Procedure로 수정 - 
//			wsprintf(szQuery, QUERY_080702_0258, i_pLogin->AccountName);
			SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_pLogin->AccountName, 0, NULL);			
			RETCODE ret = SQLExecDirect(hstmt, (UCHAR*)PROCEDURE_080827_0258, SQL_NTS);
			if ( ret!=SQL_SUCCESS
				&& ret!=SQL_SUCCESS_WITH_INFO )
			{
				ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"CAtumPreDBManager::ExternalAuthentication_ Failed!\r\n", TRUE);
				SQLFreeStmt(hstmt, SQL_CLOSE);
				return FALSE;
			}
			SQLBindCol(hstmt, 1, SQL_C_ULONG, &o_pAccInfo->AccountUniqueNumber, 0, NULL);
			SQLBindCol(hstmt, 2, SQL_C_USHORT, &o_pAccInfo->AccountType, 0, NULL);
			SQLBindCol(hstmt, 3, SQL_C_CHAR, o_pAccInfo->PasswordFromDB, SIZE_MAX_PASSWORD_MD5_STRING, &pcbNTS);
			ret = SQLFetch(hstmt);
			SQLFreeStmt(hstmt, SQL_CLOSE);
			if(0 == strncmp(o_pAccInfo->PasswordFromDB, "", SIZE_MAX_PASSWORD_MD5_STRING))
			{// 2007-10-08 by cmkwon, DB 패스워드에 설정된 것이 없다 - 인증 불가
				return FALSE;
			}

			if(FALSE == IS_VALID_UNIQUE_NUMBER(o_pAccInfo->AccountUniqueNumber))
			{// 2006-04-28 by cmkwon, 계정이 없다
				return FALSE;
			}
			if(0 != strnicmp(szMD5String, o_pAccInfo->PasswordFromDB, SIZE_MAX_PASSWORD_MD5_STRING))
			{// 2006-04-28 by cmkwon, MD5 패스워드 비교

				char szEncodedString[SIZE_MAX_PASSWORD_MD5_STRING];		MEMSET_ZERO(szEncodedString, SIZE_MAX_PASSWORD_MD5_STRING);
				BYTE byPass[SIZE_MAX_PASSWORD_MD5];
				MD5 md5_instance;

				char szTmPassword[1024];			// 2006-05-22 by cmkwon, 비번에 추가 스트링 적용
				MEMSET_ZERO(szTmPassword, 1024);
				wsprintf(szTmPassword, "%s%s", MD5_PASSWORD_ADDITIONAL_STRING, o_pAccInfo->PasswordFromDB);
				md5_instance.MD5Encode(szTmPassword, byPass);
				MD5::MD5Binary2String(byPass, szEncodedString);

				if (0 != strnicmp(szEncodedString, szMD5String, SIZE_MAX_PASSWORD_MD5_STRING))
				{
					return FALSE;
				}
			}
		}
	}

	int						nMGameEventType = 0;
	///////////////////////////////////////////////////////////////////////////////
	// MGameEvent 처리
	if(MGAME_EVENT_OPEN_BETA_ATTENDANCE == g_pPreGlobal->m_enMGameEventType
		&& g_pPreGlobal->IsExistAccountNameForMGameEvent(i_pLogin->AccountName))
	{
		nMGameEventType = g_pPreGlobal->m_enMGameEventType;
	}

	/*[Stored Query Definition]************************************************
	--!!!!
	-- Name: atum_PreServerExtAuthLogin
	-- Desc: 2006-04-27 by cmkwon, 추가함
	--		   외부 DB 인증 로그인 처리 - 비번 체크는 없음, 계정이 없으면 계정 추가, AccountUniqueNumber를 리턴한다.
	--		2006-11-15 by cmkwon, Select 검색 필드 추가(td_account테이블에 추가된 필드 - GameContinueTimeInSecondOfToday, LastGameEndDate)
	--		2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기 - 주민번호 인자 추가
	--		// 2007-09-12 by cmkwon, 베트남 2차패스워드 구현 - atum_PreServerExtAuthLogin 프로시저 수정
	--====
	CREATE PROCEDURE dbo.atum_PreServerExtAuthLogin
		@i_AccountName				VARCHAR(20),
		@i_Sex						TINYINT,			-- 1: 남, 2: 여
		@i_BirthYear				INT,				-- 생년
		@i_MGameEventType			INT,
		@i_JuminNumber				VARCHAR(20)			-- 2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기 - 추가된 인자
	AS
		DECLARE @AccountUID INT
		SET @AccountUID = (SELECT AccountUniqueNumber FROM td_Account WITH (NOLOCK) WHERE AccountName = @i_AccountName)

		-- 최초 접속자는 계정 추가
		IF (@AccountUID IS NULL)
		BEGIN
			INSERT INTO td_Account(AccountName, Sex, BirthYear, MGameEventType, JuminNumber)
				VALUES(@i_AccountName, @i_Sex, @i_BirthYear, @i_MGameEventType, @i_JuminNumber)
		END
		ELSE
		BEGIN
			-- 2007-03-30 by cmkwon
			-- SQLMoreResults()의 개수를 맞추기 위해서 추가한 코드임
			UPDATE td_Account
				SET Sex = Sex
				WHERE AccountName = @i_AccountName
		END
		
		-- 마지막 로그인 시간 저장
		UPDATE td_Account
			SET LastLoginDate = GetDate()
			WHERE AccountName = @i_AccountName	
		
		-- // 2007-09-12 by cmkwon, 베트남 2차패스워드 구현 - SecondaryPassword 가져오기 추가
		SELECT AccountUniqueNumber, AccountType, Password, RegisteredDate, GameContinueTimeInSecondOfToday, LastGameEndDate, SecondaryPassword
			FROM td_Account WHERE AccountName = @i_AccountName
	GO
	**************************************************************************/
	SQLINTEGER arrCB[8] = {SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS ,SQL_NTS,SQL_NTS,SQL_NTS};
	SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_pLogin->AccountName, 0,	&arrCB[1]);
	SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_UTINYINT, SQL_TINYINT, 0, 0, &i_pLogin->MGameSEX, 0,						&arrCB[2]);
	SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &i_pLogin->MGameYear, 0,							&arrCB[3]);
	SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &nMGameEventType, 0,								&arrCB[4]);
	SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_JUMIN_NUMBER, 0, szJuminNum, 0,				&arrCB[5]);	// 2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기

	RETCODE ret = SQLExecDirect(hstmt, PROCEDURE_080822_0271, SQL_NTS);
	if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
	{
		ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@atum_PreServerExtAuthLogin Failed!\n\n", TRUE);
		SQLFreeStmt(hstmt, SQL_CLOSE);
		return FALSE;
	}

	arrCB[0]= arrCB[1]= arrCB[2]= arrCB[3]= arrCB[4]= arrCB[5]= arrCB[6]= arrCB[7]= SQL_NTS;
	char szPasswordFromDB[SIZE_MAX_PASSWORD_MD5_STRING];	MEMSET_ZERO(szPasswordFromDB, SIZE_MAX_PASSWORD_MD5_STRING);
	SQL_TIMESTAMP_STRUCT		tmSqlTime;		MEMSET_ZERO(&tmSqlTime, sizeof(tmSqlTime));
	SQL_TIMESTAMP_STRUCT		tmSqlTime2;		MEMSET_ZERO(&tmSqlTime2, sizeof(tmSqlTime2));
 	SQLBindCol(hstmt, 1, SQL_C_ULONG, &o_pAccInfo->AccountUniqueNumber, 0,						&arrCB[1]);
 	SQLBindCol(hstmt, 2, SQL_C_USHORT, &o_pAccInfo->AccountType, 0,								&arrCB[2]); 
	SQLBindCol(hstmt, 3, SQL_C_CHAR, o_pAccInfo->PasswordFromDB, SIZE_MAX_PASSWORD_MD5_STRING,	&arrCB[3]);
	SQLBindCol(hstmt, 4, SQL_C_TIMESTAMP, &tmSqlTime, 0,										&arrCB[4]);
 	SQLBindCol(hstmt, 5, SQL_C_LONG, &o_pAccInfo->GameContinueTimeInSecondOfToday, 0,			&arrCB[5]);		// 2006-11-15 by cmkwon
	SQLBindCol(hstmt, 6, SQL_C_TIMESTAMP, &tmSqlTime2, 0,										&arrCB[6]);		// 2006-11-15 by cmkwon
	SQLBindCol(hstmt, 7, SQL_C_CHAR, o_pAccInfo->SecondaryPassword, SIZE_MAX_PASSWORD_MD5_STRING,	&arrCB[7]);	// 2007-09-12 by cmkwon, 베트남 2차패스워드 구현 - SecondaryPassword 가져오기 추가

// 2008-07-24 by cmkwon, MySQL 포팅 관련(OUTPUT 제거) - 아래와 같이 수정
// 	///////////////////////////////////////////////////////////////////////////////
// 	// 2007-03-30 by cmkwon
// 	ret = SQLMoreResults(hstmt);		// 2007-03-30 by cmkwon, 없는 계정 추가 처리
// 	ret = SQLMoreResults(hstmt);		// 2007-03-30 by cmkwon, 마지막 로그인 시간 저장 처리
//
//	///////////////////////////////////////////////////////////////////////////////
//	// 2007-03-30 by cmkwon, 계정 정보 가져오기
//	ret= SQLFetch(hstmt);
//	SQLFreeStmt(hstmt, SQL_CLOSE);
//	o_pAccInfo->AccountRegisteredDate	= tmSqlTime;
//	o_pAccInfo->LastGameEndDate			= tmSqlTime2;		// 2006-11-15 by cmkwon

	///////////////////////////////////////////////////////////////////////////////
	// 2008-07-24 by cmkwon, MySQL 포팅 관련(OUTPUT 제거) -
	SQLSMALLINT    nColCnts          = 0;
	while(TRUE)
	{
		SQLNumResultCols(hstmt, &nColCnts);
		if(nColCnts <= 0)
		{// 2008-07-25 by cmkwon, ResultCols 0 이면 적용된 RowCount 이다 
			ret = SQLMoreResults(hstmt);
			if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
			{
				break;
			}
			continue;
		}
		ret = SQLFetch(hstmt);
		if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
		{
			ret = SQLMoreResults(hstmt);                 // 2008-07-25 by cmkwon, 다음 Results 가 있는지를 한번더 체크한다.
			if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
			{
				break;
			}
			continue;
		}
		o_pAccInfo->AccountRegisteredDate	= tmSqlTime;
		o_pAccInfo->LastGameEndDate			= tmSqlTime2;		// 2006-11-15 by cmkwon
	}
	SQLFreeStmt(hstmt, SQL_CLOSE);

	///////////////////////////////////////////////////////////////////////////////
	// 2007-06-27 by cmkwon, 중국 방심취 시스템 수정 - 중국만 체크, 하나의 주민번호로 처리
	if(LANGUAGE_TYPE_CHINESE == g_pPreGlobal->GetLanguageType())
	{
		int nJuminLen = strlen(szJuminNum);
		if(15 == nJuminLen
			|| 18 == nJuminLen)
		{
			/*[Stored Query Definition]************************************************
			--!!!!
			-- Name: atum_GetLastGamePlayData
			-- Desc: 2007-06-29 by cmkwon, 2007-06-27 by cmkwon, 중국 방심취 시스템 수정 - 하나의 주민번호에 계정 처리
			--		   주민번호 계정중에 최종 게임 플레이 정보를 검색한다.
			--====
			CREATE PROCEDURE dbo.atum_GetLastGamePlayData
				@i_JuminNumber				VARCHAR(20),		-- 2007-06-29 by cmkwon
			AS
				SELECT TOP 1 GameContinueTimeInSecondOfToday, LastGameEndDate 
				FROM td_Account WITH(NOLOCK)
				WHERE JuminNumber = @i_JuminNumber 
				ORDER BY LastGameEndDate DESC
			GO
			**************************************************************************/
			arrCB[0]= arrCB[1]= arrCB[2]= arrCB[3]= arrCB[4]= arrCB[5]= arrCB[6]= SQL_NTS;
			SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_JUMIN_NUMBER, 0, szJuminNum, 0,	&arrCB[1]);
			RETCODE ret = SQLExecDirect(hstmt, PROCEDURE_080822_0272, SQL_NTS);
			if ( ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO && ret!=SQL_NO_DATA)
			{
				ProcessLogMessages(SQL_HANDLE_STMT, hstmt,"@atum_GetLastGamePlayData Failed!\n\n", TRUE);
				SQLFreeStmt(hstmt, SQL_CLOSE);
				return FALSE;
			}
			arrCB[0]= arrCB[1]= arrCB[2]= arrCB[3]= arrCB[4]= arrCB[5]= arrCB[6]= SQL_NTS;
			int							nGameContinueTime = 0;
			ATUM_DATE_TIME				atLastGameEnd;
			MEMSET_ZERO(&tmSqlTime2, sizeof(tmSqlTime2));	// 2007-07-19 by cmkwon, 주민번호로 최종 접속 정보 가져오기 버그 수정
		 	SQLBindCol(hstmt, 1, SQL_C_LONG, &nGameContinueTime, 0,			&arrCB[1]);
			SQLBindCol(hstmt, 2, SQL_C_TIMESTAMP, &tmSqlTime2, 0,			&arrCB[2]);
			ret= SQLFetch(hstmt);
			SQLFreeStmt(hstmt, SQL_CLOSE);
			if(SQL_SUCCESS == ret || SQL_SUCCESS_WITH_INFO == ret)
			{// 2007-07-19 by cmkwon, 주민번호로 최종 접속 정보 가져오기 버그 수정
				atLastGameEnd = tmSqlTime2;
				if(atLastGameEnd > o_pAccInfo->LastGameEndDate)
				{
					o_pAccInfo->LastGameEndDate					= atLastGameEnd;
					o_pAccInfo->GameContinueTimeInSecondOfToday	= nGameContinueTime;
				}
			}
		}
	}


	return IS_VALID_UNIQUE_NUMBER(o_pAccInfo->AccountUniqueNumber);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExecuteExtAuth(char *i_szAccName, char *i_szPwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
/// \brief		
/// \author		cmkwon
/// \date		2006-05-17 ~ 2006-05-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuth(char *i_szAccName, char *i_szPwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
{
	/*[Stored Query Definition]************************************************
	--!!!!
	-- Name: atum_ExternalAuthentication
	-- Desc: 2006-04-27 by cmkwon, 추가 함
	--		   외부 DB 인증 프로시저 - 이것은 없어도 되지만 내부에서 테스트 하기 위해 필요한 모듈임
	--		   실제로 이 모듈은 상대 회사에서 구현해 주어야 한다.
	--====
	CREATE PROCEDURE atum_ExternalAuthentication
		@i_AccountName				VARCHAR(20),	
		@i_Password					VARCHAR(35)
	AS
		DECLARE @AccountUID INT
		
		SET @AccountUID = (SELECT AccountUniqueNumber 
								FROM td_Account
								WHERE AccountName = @i_AccountName AND Password = @i_Password)
		
		IF (@AccountUID IS NULL)
			BEGIN
					RETURN 0
			END

		RETURN 1
	GO	
	**************************************************************************/
	BOOL		bAuth = FALSE;

	SQLBindParameter(hstmt_extAuth, 1, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &bAuth, 0,								NULL);
	SQLBindParameter(hstmt_extAuth, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_szAccName, 0,		NULL);
	SQLBindParameter(hstmt_extAuth, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_PASSWORD_MD5_STRING, 0, i_szPwd, 0,	NULL);
	BOOL ret = SQLExecDirect(hstmt_extAuth, (UCHAR*)"{ ? = call atum_ExternalAuthentication(?, ?)}", SQL_NTS);
	if (ret != SQL_SUCCESS
		&& ret != SQL_SUCCESS_WITH_INFO)
	{
		if(ret != SQL_NO_DATA)
		{// 쿼리 실패
			ProcessLogMessages(SQL_HANDLE_STMT, hstmt_extAuth, "@atum_ExternalAuthentication Failed!!\r\n", TRUE);
		}
		SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
		return FALSE;
	}

	ret = SQLMoreResults(hstmt_extAuth);
	ret = SQLMoreResults(hstmt_extAuth);
	SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
	if(FALSE == bAuth)
	{
		return FALSE;
	}
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExecuteExtAuth_GalaNet(INT *o_pnExtAccountIDNum, char *i_szAccName, char *i_szPwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
/// \brief		
/// \author		cmkwon
/// \date		2006-05-22 ~ 2006-05-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuth_GalaNet(INT *o_pnExtAccountIDNum, char *i_szAccName, char *i_szPwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
{
	*o_pnExtAccountIDNum	= 0;		// 2006-05-22 by cmkwon, 초기화

	/*[Stored Query Definition]************************************************
	--!!!!
	-- Name: G_AUTHENTICATE
	-- Desc: 2006-04-27 by cmkwon, 추가 함
	--		   Galanet용 
	--		@o_ExtAccountIDNum = -1 ==> 어카운트차단상태
	--		@o_ExtAccountIDNum =  0 ==> 계정이 존재하지 안거만 비밀번호가 오류 상태임
	--		@o_ExtAccountIDNum =  그 이외의 값 ==> 인증 성공, 계정의 고유 IDNumber
	--====
	CREATE PROCEDURE G_AUTHENTICATE
		@i_AccountName			VARCHAR(20),	
		@i_Password				VARCHAR(35),
		@i_GameName				VARCHAR(10),
		@o_ExtAccountIDNum		INT				OUTPUT
	AS		
	GO	
	**************************************************************************/
	char *szExtAuthGameName  = EXT_AUTH_GAME_NAME; 
	SQLINTEGER arrCB[5] = {SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS};
	SQLBindParameter(hstmt_extAuth, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_szAccName, 0,		NULL);
	SQLBindParameter(hstmt_extAuth, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_PASSWORD_MD5_STRING, 0, i_szPwd, 0,	NULL);
	SQLBindParameter(hstmt_extAuth, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 10, 0, szExtAuthGameName, 0,					NULL);
	SQLBindParameter(hstmt_extAuth, 4, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, o_pnExtAccountIDNum, 0,					NULL);
	BOOL ret = SQLExecDirect(hstmt_extAuth, PROCEDURE_080822_0273, SQL_NTS);
	if (ret != SQL_SUCCESS
		&& ret != SQL_SUCCESS_WITH_INFO)
	{
		if(ret != SQL_NO_DATA)
		{// 쿼리 실패
			ProcessLogMessages(SQL_HANDLE_STMT, hstmt_extAuth, "@G_AUTHENTICATE Failed!!\r\n", TRUE);
		}
		SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
		return FALSE;
	}

	ret = SQLMoreResults(hstmt_extAuth);
	ret = SQLMoreResults(hstmt_extAuth);
	SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
	if(0 == *o_pnExtAccountIDNum
		|| -1 == *o_pnExtAccountIDNum)
	{
		return FALSE;
	}
	
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExecuteExtAuth2(char *i_szAccName, char *i_szPwd, char *i_szWebLoginAuthKey, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
/// \brief		
/// \author		cmkwon
/// \date		2007-03-30 ~ 2007-03-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuth2(char *i_szAccName, char *i_szPwd, char *i_szWebLoginAuthKey, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
{
	/*[Stored Query Definition]************************************************
	--!!!!
	-- Name: atum_ExternalAuthentication2
	-- Desc: 2007-03-30 by cmkwon, 추가 함
	--		   외부 DB 인증 프로시저 - 이것은 없어도 되지만 내부에서 테스트 하기 위해 필요한 모듈임
	--		   실제로 이 모듈은 상대 회사에서 구현해 주어야 한다.
	--====
	CREATE PROCEDURE atum_ExternalAuthentication2
		@o_RetCode					INT				OUTPUT,		-- 2007-03-30 by cmkwon
		@i_AccountName				VARCHAR(20),				-- 계정명
		@i_Password					VARCHAR(35),				-- 패스워드
		@i_WebLoginAuthKey			VARCHAR(20)					-- 웹인증키
	AS
		SET @o_RetCode		= 0

		DECLARE @AccountUID INT	
		SET @AccountUID = (SELECT AccountUniqueNumber FROM td_Account WITH(NOLOCK) WHERE AccountName = @i_AccountName AND Password = @i_Password)
		
		IF (@AccountUID IS NULL)
		BEGIN
			SET @o_RetCode		= 1
			RETURN
		END

		SET @o_RetCode		= 0
		RETURN
	GO
	**************************************************************************/
	int		nRetCode = 1;		// 2008-01-23 by cmkwon, 기본값을 에러 상태로 설정한다.
	SQLBindParameter(hstmt_extAuth, 1, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &nRetCode, 0,								NULL);
	SQLBindParameter(hstmt_extAuth, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_szAccName, 0,		NULL);
	SQLBindParameter(hstmt_extAuth, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_PASSWORD_MD5_STRING, 0, i_szPwd, 0,	NULL);
	SQLBindParameter(hstmt_extAuth, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_WEBLOGIN_AUTHENTICATION_KEY, 0, i_szWebLoginAuthKey, 0,		NULL);
	BOOL ret = SQLExecDirect(hstmt_extAuth, PROCEDURE_080822_0274, SQL_NTS);
	if (ret != SQL_SUCCESS
		&& ret != SQL_SUCCESS_WITH_INFO)
	{
		if(ret != SQL_NO_DATA)
		{// 쿼리 실패
			ProcessLogMessages(SQL_HANDLE_STMT, hstmt_extAuth, "@atum_ExternalAuthentication2 Failed!!\r\n", TRUE);
		}
		SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
		return FALSE;
	}

	ret = SQLMoreResults(hstmt_extAuth);
	ret = SQLMoreResults(hstmt_extAuth);
	SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
	if(0 != nRetCode)
	{// 2007-03-30 by cmkwon, 리턴값이 0이 아니면 인증 실패임
		return FALSE;
	}
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExecuteExtAuth_Argchar *i_szAccName, char *i_szPwd, char *i_szWebLoginAuthKey, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/* =EN_DBCONN_EXT_AUTH */)
/// \brief		
/// \author		// 2010-11-16 by jskim&shcho 아르헨티나 외부인증
/// \date		2010-11-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuth_Arg(char *i_szAccName, char *i_szPwd)
{
	#if defined(SERVICE_TYPE_ARGENTINA_SERVER_1)
 	BOOL RetValue = FALSE; //기본값을 에러 상태로 설정한다.
	// 2010-11-29 by shcho, 아르헨티나 외부인증 변경 SOAP 처리
	CSOAPConnect connectSOAP;
	// 상호 테스트
	g_pPreGlobal->WriteSystemLogEX(TRUE, "--------------------------------SOAP START--------------------------\r\n");
	g_pPreGlobal->WriteSystemLogEX(TRUE, "CAtumPreDBManager::ExecuteExtAuth_Arg, AccountName(%s) check start!\r\n", i_szAccName);
	
	if(TRUE != g_pPreGlobal->GetIsExtAuthUseSOAP())
	{ // 사용하지 않으면 인증 실패로 처리한다.
		return FALSE;
	}
	

	// URL과 gameID는 grobal.cfg에서 가져온 정보를 넣어야 한다. TRUE 이면 성공으로 처리한다.
	// 상호 테스트 시작시에 찍는다.
	//g_pPreGlobal->WriteSystemLogEX(
	//	TRUE, 
	//	"CAtumPreDBManager::ExecuteExtAuth_Arg SOAP STATE = URL[%s], GameID =[%d], AccountName(%s), PassWord(%s)\r\n"
	//	, g_pPreGlobal->GetExtAuthSOAPUrlString()
	//	, g_pPreGlobal->GetExtAuthSOAPGameID()
	//	, i_szAccName
	//	, i_szPwd);
	if(TRUE!=connectSOAP.SOAP_Authentication( /*URL_STR*/	connectSOAP.Char2bBSTR(g_pPreGlobal->GetExtAuthSOAPUrlString()), 
		/*GameID*/		connectSOAP.Char2bBSTR(g_pPreGlobal->GetExtAuthSOAPGameID()), 
		/*WebMethod*/	connectSOAP.Char2bBSTR("AuthenticateUser"), 
		/*Account*/ connectSOAP.Char2bBSTR(i_szAccName),
		/*Password*/	connectSOAP.Char2bBSTR(i_szPwd)))
	{ // FALSE 이면 실패
		return FALSE;
	}
	// END 2010-11-29 by shcho, 아르헨티나 외부인증 변경 SOAP 처리
	#endif
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExecuteExtAuthChina(char *o_szJuminNumber, char *i_szAccName, char *i_szPwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
/// \brief		// 2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기 - 인증함수 추가
/// \author		cmkwon
/// \date		2007-06-29 ~ 2007-06-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuthChina(char *o_szJuminNumber, char *i_szAccName, char *i_szPwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
{
	/*[Stored Query Definition]************************************************
	--!!!!
	-- Name: atum_ExternalAuthenticationChina
	-- Desc: 2007-06-29 by cmkwon, td_account 테이블에 주민번호저장하기 - 인증프로시저 추가
	--		   외부 DB 인증 프로시저 - 이것은 없어도 되지만 내부에서 테스트 하기 위해 필요한 모듈임
	--		   실제로 이 모듈은 상대 회사에서 구현해 주어야 한다.
	--		 // 2007-07-05 by cmkwon, 중국 인증 오류 수정 - output 인자를 결과 쿼리로 넘기도록 수정함
	--====
	CREATE PROCEDURE dbo.atum_ExternalAuthenticationChina
		@i_AccountName				VARCHAR(20),				-- ???
		@i_Password					VARCHAR(35)
	AS
		DECLARE @JuminNum VARCHAR(20)
		DECLARE @AccountUID INT	
		SELECT @AccountUID= UserUniqueNumber, @JuminNum= ID_Card 
		FROM member WITH(NOLOCK) 
		WHERE UserID = @i_AccountName AND Password = @i_Password
		
		IF (@AccountUID IS NULL)
		BEGIN
			SELECT 1, NULL
			RETURN
		END

		SELECT 0, @JuminNum
	GO
	**************************************************************************/
	int		nRetCode = 0;
	SQLINTEGER arrCB[4] = {SQL_NTS,SQL_NTS,SQL_NTS,SQL_NTS};
	// 2007-07-05 by cmkwon, 중국 인증 오류 수정 - Output 인자를 결과 리턴으로 변경함
	SQLBindParameter(hstmt_extAuth, 1,SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_ACCOUNT_NAME, 0, i_szAccName, 0		, &arrCB[1]);
	SQLBindParameter(hstmt_extAuth, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SIZE_MAX_PASSWORD_MD5_STRING, 0, i_szPwd, 0	, &arrCB[2]);
	BOOL ret = SQLExecDirect(hstmt_extAuth, PROCEDURE_080822_0275, SQL_NTS);
	if (ret != SQL_SUCCESS
		&& ret != SQL_SUCCESS_WITH_INFO)
	{
		if(ret != SQL_NO_DATA)
		{// 쿼리 실패
			ProcessLogMessages(SQL_HANDLE_STMT, hstmt_extAuth, "@atum_ExternalAuthenticationChina Failed!!\r\n", TRUE);
		}
		SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
		return FALSE;
	}

	// 2007-07-05 by cmkwon, 중국 인증 오류 수정 - 리턴에러코드를 결과로 받도록 수정
	SQLBindCol(hstmt_extAuth, 1, SQL_C_LONG, &nRetCode, 0,								&arrCB[1]);
	SQLBindCol(hstmt_extAuth, 2, SQL_C_CHAR, o_szJuminNumber, SIZE_MAX_JUMIN_NUMBER,	&arrCB[2]);
	ret = SQLFetch(hstmt_extAuth);
	SQLFreeStmt(hstmt_extAuth, SQL_CLOSE);
	if(0 != nRetCode)
	{// 2007-03-30 by cmkwon, 리턴값이 0이 아니면 인증 실패임
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExecuteExtAuth_Taiwanese(MSG_PC_CONNECT_LOGIN *i_pLogin, char *i_szMD5Pwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
/// \brief		// 2008-10-08 by cmkwon, 대만 Netpower_Tpe 외부인증 구현 - 
/// \author		cmkwon
/// \date		2008-10-08 ~ 2008-10-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuth_Taiwanese(MSG_PC_CONNECT_LOGIN *i_pLogin, char *i_szMD5Pwd, SQLHSTMT &hstmt_extAuth, EN_DBCONN_TYPE i_dbConnTy/*=EN_DBCONN_EXT_AUTH*/)
{
	GenericHTTPClient httpCli;	
    httpCli.InitilizePostArguments();
    httpCli.AddPostArguments("user_id", i_pLogin->AccountName);
    httpCli.AddPostArguments("user_pwd", i_szMD5Pwd);
    httpCli.AddPostArguments("ip_addr", i_pLogin->ClientIP);
    httpCli.AddPostArguments("as_code", "CB");            
    
	char szURL[1024];
	sprintf(szURL, "http://%s:%d/auth_ace.asmx/Login_Checked", g_pPreGlobal->GetExtAuthDBServerIP(), g_pPreGlobal->GetExtAuthDBServerPort());
	BOOL bRet = httpCli.Request(szURL, GenericHTTPClient::RequestPostMethod);
	if(FALSE == bRet)
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR]CAtumPreDBManager::ExecuteExtAuth_Taiwanese# call Request fail !!, URL(%s), AccountName(%s)\r\n"
			, szURL, i_pLogin->AccountName);
		return FALSE;
	}

    LPCTSTR szResult = httpCli.QueryHTTPResponse();
	if(0 >= strlen(szResult))
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR]CAtumPreDBManager::ExecuteExtAuth_Taiwanese# no response message !!, URL(%s), AccountName(%s)\r\n"
			, szURL, i_pLogin->AccountName);
		return FALSE;
	}
	int nErrCode = httpCli.LoadXMLFromQueryHTTPResponse();
	if(0 != nErrCode)
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR]CAtumPreDBManager::ExecuteExtAuth_Taiwanese# loadXML fail 1!!, URL(%s), AccountName(%s), ResponseMsg(%s), ErrCode(%d)\r\n"
			, szURL, i_pLogin->AccountName, szResult, nErrCode);
		return FALSE;
	}

	char szReturnedResult[1024];
	MEMSET_ZERO(szReturnedResult, 1024);
	if(FALSE == httpCli.GetTextFromXMLLoaderByNodeName(szReturnedResult, 1024, "//result"))
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR]CAtumPreDBManager::ExecuteExtAuth_Taiwanese# loadXML fail 2!!, URL(%s), AccountName(%s), ResponseMsg(%s)\r\n"
			, szURL, i_pLogin->AccountName, szResult);
		return FALSE;
	}
	int nReturnedResult = atoi(szReturnedResult);
	if(0 != nReturnedResult)
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR]CAtumPreDBManager::ExecuteExtAuth_Taiwanese# loadXML fail 3!!, URL(%s), AccountName(%s), Result(%d)\r\n"
			, szURL, i_pLogin->AccountName, nReturnedResult);
		return FALSE;
	}

	char szReturnedResultStr[1024];
	MEMSET_ZERO(szReturnedResultStr, 1024);
	if(FALSE == httpCli.GetTextFromXMLLoaderByNodeName(szReturnedResultStr, 1024, "//result_str"))
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR]CAtumPreDBManager::ExecuteExtAuth_Taiwanese# loadXML fail 4!!, URL(%s), AccountName(%s), ResponseMsg(%s)\r\n"
			, szURL, i_pLogin->AccountName, szResult);
		return FALSE;
	}

	char szOriAccName[SIZE_MAX_ORIGINAL_ACCOUNT_NAME];
	STRNCPY_MEMSET(szOriAccName, i_pLogin->AccountName, SIZE_MAX_ORIGINAL_ACCOUNT_NAME);

	if(FALSE == httpCli.GetParameterValue(i_pLogin->AccountName, SIZE_MAX_ACCOUNT_NAME, "user_no", szReturnedResultStr, "=|"))
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[ERROR]CAtumPreDBManager::ExecuteExtAuth_Taiwanese# loadXML fail 5!!, URL(%s), AccountName(%s), ResponseMsg(%s)\r\n"
			, szURL, i_pLogin->AccountName, szResult);
		return FALSE;
	}


	g_pPreGlobal->WriteSystemLogEX(TRUE, "[Notify] Netpower authentication success !!, FirstAccName(%s) SecAccName(%s)\r\n"
		, szOriAccName, i_pLogin->AccountName);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ExecuteExtAuth_Arario(MSG_PC_CONNECT_LOGIN *i_pLogin, char *i_szMD5Pwd, char *i_szSessionKey)
/// \brief		// 2008-12-18 by cmkwon, 일본 Arario 외부인증, 빌링 모듈 적용하기 - 
/// \author		cmkwon
/// \date		2008-12-18 ~ 2008-12-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuth_Arario(MSG_PC_CONNECT_LOGIN *i_pLogin, char *i_szMD5Pwd, char *i_szSessionKey)
{
#if defined(SERVICE_TYPE_JAPANESE_SERVER_1)

	// 2008-12-22 by cmkwon, 일본 Arario 외부인증,빌링 모듈 설정 파일(*.ini) 경로 설저하기 - 
	static BOOL bSetedIniFilePathFlag = FALSE;
	if(FALSE == bSetedIniFilePathFlag)
	{
		WCHAR wszConfigRoot[MAX_PATH];
		MEMSET_ZERO(wszConfigRoot, sizeof(WCHAR) * MAX_PATH);
		
		MultiByteToWideChar(CP_ACP, 0, CONFIG_ROOT, strlen(CONFIG_ROOT), wszConfigRoot, sizeof(WCHAR) * MAX_PATH);
		SetAuthInfoPath(wszConfigRoot);
		bSetedIniFilePathFlag		= TRUE;		// 2008-12-22 by cmkwon, 설정 한번만 처리되도록
	}

	char sessionKey[1024];		MEMSET_ZERO(sessionKey, 1024);
	char newKeyA[1024];			MEMSET_ZERO(newKeyA, 1024);		// 2008-12-18 by cmkwon, 사용하지는 않는 정보임

	STRNCPY_MEMSET(sessionKey, i_szSessionKey, 1024);
	int result = AraAuthLoginWithSesKeyB(sessionKey, newKeyA);

	if(0 != result)
	{
		g_pPreGlobal->WriteSystemLogEX(TRUE, "[Notify] CAtumPreDBManager::ExecuteExtAuth_Arario# auth fail !! AccountName(%s) IP(%s) result(%d) GetLastError(%d)\r\n", i_pLogin->AccountName, i_pLogin->ClientIP, result, GetLastError());
		return FALSE;
	}
	return TRUE;
#endif

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 
/// \author		cmkwon
/// \date		2010-04-26 ~ 2010-04-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ExecuteExtAuth_Innova(MSG_PC_CONNECT_LOGIN *i_pLogin, UINT i_nClientIP)
{
	///////////////////////////////////////////////////////////////////////////////
	// 2010-04-26 by cmkwon, 러시아 Innva 인증/빌링 시스템 변경 - 
	Err_t errCode = m_pPreIOCP2->INNBILL_ExtAuth(i_pLogin->AccountName, i_pLogin->WebLoginAuthKey, i_nClientIP);
	if(ERR_NO_ERROR != errCode)
	{		
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumPreDBManager::ProcessDinamicServerQuery(DB_QUERY *i_qQuery, CODBCStatement *i_pODBC)
/// \brief		// 2008-12-01 by cmkwon, 쿼리별로 스레드를 만들어 처리하는 시스템 구축 - 
/// \author		cmkwon
/// \date		2008-12-01 ~ 2008-12-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumPreDBManager::ProcessDinamicServerQuery(DB_QUERY *i_qQuery, CODBCStatement *i_pODBC)
{
	// 2008-12-01 by cmkwon, 쿼리별로 스레드를 만들어 처리하는 시스템 구축 - PreServer는 사용하는 쿼리가 없음
	//	switch(i_qQuery->enumQuryType)
	//	{
	//	case :
	//	}
	
	// error: no such DB query type
	g_pGlobal->WriteSystemLogEX(TRUE, "[ERROR] CAtumPreDBManager::ProcessDinamicServerQuery# no such DB Query Type !! %d(%s)\r\n", i_qQuery->enumQuryType, GetDBQueryTypeString(i_qQuery->enumQuryType));
	return FALSE;
}
