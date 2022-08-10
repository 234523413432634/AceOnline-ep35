// 2006-09-05 by cmkwon
// #include "LocalizationDefineCommon.h"
#include "Contents.h"

#ifndef _LOCALIZATION_DEFINE_COMMON_H_
#define _LOCALIZATION_DEFINE_COMMON_H_


///////////////////////////////////////////////////////////////////////////////
// 2006-09-04 by cmkwon, 언어간 다른 Define 리스트

///////////////////////////////////////////////////////////////////////////////
// 2008-01-08 by cmkwon, 언어 서비스 관련 정의를 하나로 통일함 - SERVICE_TYPE_XXX 로 통일함, Preprocessor definitions 은 사용하지 않음
// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [서비스-필수]서비스 타입(SERVICE_TYPE_XXX) 정의 하기
//  SERVICE_TYPE_KOREAN_SERVER_1		==> 한국	Masangsoft		- Kor	100
//  SERVICE_TYPE_KOREAN_SERVER_2		==>	한국	Yedang			- Kor	1000
//  SERVICE_TYPE_ENGLISH_SERVER_1		==>	캐나다	Wikigames		- Eng	2000
//  SERVICE_TYPE_ENGLISH_SERVER_2		==>	영국	Gameforge4D		- Eng	5000	
//  SERVICE_TYPE_GERMAN_SERVER_1		==>	독일	Gameforge4D		- Deu	5100	// 2008-04-11 by cmkwon, 지원 서비스 추가 - Gameforge4D 독일어 
//  SERVICE_TYPE_CHINESE_SERVER_1		==>	중국	Yetime			- Chn	3000
//  SERVICE_TYPE_VIETNAMESE_SERVER_1	==>	베트남	VTC-Intecom		- Viet	4000
//  SERVICE_TYPE_THAI_SERVER_1			==>	태국	WinnerOnline	- Tha	6000	// 2008-04-11 by cmkwon, 지원 서비스 추가 - WinnerOnline 태국어
//	SERVICE_TYPE_SINGAPORE_1			==> 영어		 WinnerOnline- Sgp	6100	// 2010-12-07 by shcho,	 지원 서비스 추가(WinnerOnline 영어) - 
//	SERVICE_TYPE_INDONESIA_SERVER_1		==> 인도네시아어 WinnerOnline- IND	6200	// 2010-01-11 by shcho,	 지원 서비스 추가(WinnerOnline 인도네시아어) - 
//  SERVICE_TYPE_RUSSIAN_SERVER_1		==>	러시아	Innova			- Rus	7000	// 2008-05-29 by cmkwon, 지원 서비스 추가(Innova_Rus 러시아어 추가) - 
//  SERVICE_TYPE_TAIWANESE_SERVER_1		==>	대만	Newpower		- Tpe	8000	// 2008-09-23 by cmkwon, 지원 서비스 추가(대만 Netpower_Tpe) - 
//  SERVICE_TYPE_JAPANESE_SERVER_1		==> 일본	Arario			- Jpn	10000	// 2008-12-03 by cmkwon, 지원 서비스 추가(일본 Arario_Jpn) - 
//  SERVICE_TYPE_TURKISH_SERVER_1		==> 터키	Gameforge4D		- Tur	5200	// 2008-12-22 by cmkwon, 지원 서비스 추가(Gameforge4D 터키아, 불어, 이탈리아어) - 
//  SERVICE_TYPE_ITALIAN_SERVER_1		==> 이탈리아어	Gameforge4D	- Ita	5400	// 2008-12-22 by cmkwon, 지원 서비스 추가(Gameforge4D 터키아, 불어, 이탈리아어) - 
//  SERVICE_TYPE_FRENCH_SERVER_1		==> 프랑스어	Gameforge4D	- Fra	5500	// 2008-12-22 by cmkwon, 지원 서비스 추가(Gameforge4D 터키아, 불어, 이탈리아어) - 
//  SERVICE_TYPE_POLISH_SERVER_1		==> 폴란드어	Gameforge4D	- Pol	5600	// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
//  SERVICE_TYPE_SPANISH_SERVER_1		==> 스페인어	Gameforge4D	- Esp	5700	// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
//	SERVICE_TYPE_ARGENTINA_SERVER_1		==> 아르헨티나	LIN			- Arg	11000	// 2010-11-01 by shcho,	 지원 서비스 추가(Gameforge4D 스페인어, 아르헨티나어) -  

// 국가 소스통합 때 추가 되어야 할 부분 순서 01

#ifdef S_CAN_SERVER_SETTING_HSSON
#define SERVICE_TYPE_ENGLISH_SERVER_1
#define SERVICE_UID_FOR_WORLD_RANKING		2000			// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 
#endif

///////////////////////////////////////////////////////////////////////////////
// 2008-05-09 by cmkwon, CodePage 정의 추가 - 
//		Korean Extended Wansung			==> 949			: Korean(Masangsoft_Kor, Yedang_Kor)
//		Latin 1							==> 1252		: English(Yedang-Global_Eng, Gameforge4D_Eng), German(Gameforge4D_Deu), French(Gameforge4D_Fra), Italian(Gameforge4D_Ita), Spanish(Gameforge4D_Esp)
//		Japanese (Shift-JIS)			==> 932			
//		Chinese (PRC)					==> 936			: Chinese(Yetime_Chn)
//		Chinese (Taiwan, Hong Kong)		==> 950			: Taiwnaese(Netpower_Tpe)
//		Viet Nam						==> 1258		: Vietnamnese(VTC-Intecom_Viet)
//		Thai							==> 874			: Thai(WinnerOnline_Tha)
//		Cyrillic, Russian (Russia)		==> 1251		: Russian(Innova_Rus)
//		Turkish							==> 1254		: Turkish(Gameforge4D_Tur)
//		Central European, Eastern European	==> 1250	: Polish(Gameforge4D_Pol)

// 국가 소스통합 때 추가 되어야 할 부분 순서 02

#ifdef S_CAN_SERVER_SETTING_HSSON
#define CODE_PAGE							1252
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-04-20 by cmkwon, Gameforge4D "/누구" 명령어 제거하기 - 
#if defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
	#define _DEFINED_GAMEFORGE4D_		// 2009-04-21 by cmkwon, 스펠링 수정함.
#endif


///////////////////////////////////////////////////////////////////////////////
// 2009-04-29 by cmkwon, 핵쉴드 사용 여부 #define 으로 처리 - 
// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [언어-옵션] 추가 언어시에 핵쉴드 사용 여부 추가
// 2009-10-06 by cmkwon, 베트남 게임 가드 X-TRAP으로 변경 - 베트남 핵쉴드에서 제외
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_KOREAN_SERVER_2) || defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_VIETNAMESE_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(_DEFINED_GAMEFORGE4D_)
// 2009-11-04 by cmkwon, 태국 게임가드 Apex로 변경 - 태국(SERVICE_TYPE_THAI_SERVER_1) 제거함.
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_KOREAN_SERVER_2) || defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(_DEFINED_GAMEFORGE4D_)
#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_KOREAN_SERVER_2) || defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(_DEFINED_GAMEFORGE4D_)

#ifdef GAMEGUARD_NOT_EXECUTE_HSSON	

#else
//	 	#define _USING_HACKSHIELD_			// 2009-04-29 by cmkwon, 핵쉴드 사용 여부 #define 으로 처리 - 핵쉴드 사용 여부 정의
#endif

	#if defined(_ATUM_FIELD_SERVER)
		#pragma comment(lib, "AntiCpXSvr.lib")
	#endif // END - #if defined(_ATUM_FIELD_SERVER)
#endif 

#ifdef S_CAN_SERVER_SETTING_HSSON
#define SIZE_MAX_INITIAL_GUILD_CAPACITY				30
#define SIZE_MAX_GUILD_CAPACITY						300
#define SIZE_MAX_ITEM_GENERAL						61
#define SIZE_MAX_ITEM_GENERAL_IN_STORE				101
#define CHARACTER_MAX_LEVEL							125
#define COUNT_IN_MEMBERSHIP_ADDED_INVENTORY			40
#define COUNT_IN_MEMBERSHIP_ADDED_STORE				50
#define COUNT_IN_MEMBERSHIP_ADDED_GUILD_CAPACITY	30
#endif

#define COUNT_IN_MEMBERSHIP_ADDED_INVENTORY			40
#define COUNT_IN_MEMBERSHIP_ADDED_STORE				50
#define COUNT_IN_MEMBERSHIP_ADDED_GUILD_CAPACITY	30

// 국가 소스통합 때 추가 되어야 할 부분 순서 04

#ifdef S_CAN_SERVER_SETTING_HSSON
#define STAT_BGEAR_ATTACK_PART						3
#define STAT_BGEAR_DEFENSE_PART						3
#define STAT_BGEAR_FUEL_PART						3
#define STAT_BGEAR_SOUL_PART						3
#define STAT_BGEAR_SHIELD_PART						3
#define STAT_BGEAR_DODGE_PART						3

#define STAT_MGEAR_ATTACK_PART						2
#define STAT_MGEAR_DEFENSE_PART						4
#define STAT_MGEAR_FUEL_PART						3
#define STAT_MGEAR_SOUL_PART						4
#define STAT_MGEAR_SHIELD_PART						3
#define STAT_MGEAR_DODGE_PART						2

#define STAT_AGEAR_ATTACK_PART						4
#define STAT_AGEAR_DEFENSE_PART						3
#define STAT_AGEAR_FUEL_PART						3
#define STAT_AGEAR_SOUL_PART						3
#define STAT_AGEAR_SHIELD_PART						4
#define STAT_AGEAR_DODGE_PART						1

#define STAT_IGEAR_ATTACK_PART						4
#define STAT_IGEAR_DEFENSE_PART						2
#define STAT_IGEAR_FUEL_PART						3
#define STAT_IGEAR_SOUL_PART						3
#define STAT_IGEAR_SHIELD_PART						2
#define STAT_IGEAR_DODGE_PART						4
#endif

///////////////////////////////////////////////////////////////////////////////
// 2006-09-15 by cmkwon, 
// Kor_Masang140	==> 121.134.114.140:9979	// 2007-01-03 by cmkwon, 마상 이전
// Kor_Yedang		==> 192.168.10.40:9979		// 2007-01-03 by cmkwon, Yedang 사설 IP
// Eng_Gala-Net		==> 상관 없음
// Viet_VTC-Intecom	==> 상관 없음
// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)

// 국가 소스통합 때 추가 되어야 할 부분 순서 05

#ifdef S_CAN_SERVER_SETTING_HSSON
#define MSBILLING_DB_SERVER_IP						"127.0.0.1"
#endif

#define MSBILLING_DB_SERVER_PORT					9979

// Kor_Masang51		==> 1
// Kor_ETRI			==> 1
// Eng_Gala-Net		==> 상관 없음
// Viet_VTC-Intecom	==> 상관 없음
#define MSBILLING_GAMEUID							1

// 2006-09-22 by dhjin
// Kor_Masang51		==> 201			// 2006-10-23 by cmkwon, 변경(101-->201)
// Kor_ETRI			==> 201			// 2006-10-23 by cmkwon, 변경(101-->201)
// Eng_Gala-Net		==> 201			// 2006-10-23 by cmkwon, 변경(101-->201)
// Viet_VTC-Intecom	==> 201			// 2006-10-23 by cmkwon, 변경(101-->201)
#define COUNT_IN_MEMBERSHIP_GUILDSTORE				201		// 2006-09-22 by dhjin, 멤버쉽 서비스시 여단 창고 카운트


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// 2007-02-13 by cmkwon

// 국가 소스통합 때 추가 되어야 할 부분 순서 06

#ifdef S_CAN_SERVER_SETTING_HSSON
#define STRMSG_S_GAMEHOMEPAGE_DOMAIN			"http://ace.subagames.com"		// 2008-08-05 by cmkwon, WikiGames_Eng 게임 정보 수정 - ,"http://www.ace-onlines.com"
#endif

///////////////////////////////////////////////////////////////////////////////
// 2006-05-22 by cmkwon, 비번 MD5로 인코딩시에 원래 비번 앞에 추가될 스트링 - 
#define MD5_PASSWORD_ADDITIONAL_STRING			""

#define EXT_AUTH_GAME_NAME						"SCO"		// 2006-05-22 by cmkwon

#ifdef S_CAN_SERVER_SETTING_HSSON
// 2008-06-05 by cmkwon, AdminTool, Monitor 접근 가능 IP를 server config file 에 설정하기 - MS140번 서버만 테스트를 위해 IP 를 틀리게(121.134.11.) 설정 함
// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP1		"127.0.0."		// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP2		"127.0.0."		// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP3		"127.0.0."		// 2008-08-05 by cmkwon, WikiGames_Eng 게임 정보 수정 - 본섭 Private IP
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP4		"127.0.0."		// 2008-08-05 by cmkwon, WikiGames_Eng 게임 정보 수정 - 본섭 Public IP
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP5		"127.0.0."		// 2008-08-05 by cmkwon, WikiGames_Eng 게임 정보 수정 - 테섭 Public IP
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP6		"127.0.0."		// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP7		"127.0.0."		// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP8		"127.0.0."		// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP9		"127.0.0."		// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP10		"127.0.0."		// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define IS_SCADMINTOOL_CONNECTABLE_IP(ip)		( 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP1,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP1)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP2,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP2)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP3,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP3)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP4,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP4)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP5,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP5)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP6,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP6)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP7,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP7)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP8,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP8)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP9,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP9)) \
												|| 0 == strncmp((ip),SCADMINTOOL_CONNECTABLE_PREFIX_IP10,strlen(SCADMINTOOL_CONNECTABLE_PREFIX_IP10)) )

///////////////////////////////////////////////////////////////////////////////
// 2006-05-02 by cmkwon, Launcher URL
#define LAUNCHER_WEB_URL						"http://ace.subagames.com/launcher.aspx"
#define TESTSERVER_LAUNCHER_WEB_URL				"http://ace.subagames.com/launcher.aspx"


///////////////////////////////////////////////////////////////////////////////
// 2007-02-13 by cmkwon
#define BILLING_DBSERVER_DATABASE_NAME			"MS_Billing"
#define BILLING_DBSERVER_USER_ID				"atum"
// Kor_Masang51		==> callweb
// Kor_Yedang		==> 2006-12-25 by cmkwon, 수정함
#define BILLING_DBSERVER_USER_PWD				"callweb"
#endif // S_CAN_SERVER_SETTING_HSSON

///////////////////////////////////////////////////////////////////////////////
// 2007-02-13 by cmkwon

// 국가 소스통합 때 추가 되어야 할 부분 순서 08

#ifdef S_CAN_SERVER_SETTING_HSSON
#define	SG_BOX_FONT_FACENAME						"Tahoma"					// 2007-02-12 by cmkwon, 글씨체
#define	SG_BOX_FONT_CHARSET							ANSI_CHARSET			// 2007-02-12 by cmkwon, 캐릭터셋
#define	SG_BOX_FONT_WEIGHT							FW_BOLD					// 2007-02-12 by cmkwon, 글씨체 두깨
#endif

// #define STR_XOR_KEY_STRING_PRE_SERVER_ADDRESS				"+-faNsf(^fP{)3>fnao??_+|23kdasf*^@`d{]s*&DS"	// 2008-04-23 by cmkwon, PreServer 주소를 IP와 도메인 둘다 지원 - 

#if defined(S_CAN_SERVER_SETTING_HSSON) && defined(S_ACCESS_INTERNAL_SERVER_HSSON)
	// 내부 서버로 ip 세팅
	// 66.207.198.252							==>	"1D1B48537E444819675E7E491C01"	 // 2010-05-26 IP변경 기존IP 208.68.90.122
	#define CHOICE_PRE_SERVER_IP_OR_DOMAIN_IN_XOR	"1A14544F7F455E066E48614A1E"	// 2014-07-30 by St0rmy changed to hamachi ip

	#define REGISTRY_BASE_PATH						"Combat-Rivals Launcher"
	#define EXE_1_FILE_NAME							"ACEonline.exe"
	#define LAUNCHER_FILE_NAME						"Launcher.atm"

	#define CLIENT_EXEUTE_FILE_NAME					"ACEonline.exe"
	#define URL_REGISTER_PAGE						"reg.asp"				// 2006-04-05 by cmkwon, 수정함

	#define WEB_START_REGISTRY_VALUE_NAME			"InstallPath"
#endif

///////////////////////////////////////////////////////////////////////////////
// 2006-12-22 by cmkwon, 게임이름 변경하면서 

// 국가 소스통합 때 추가 되어야 할 부분 순서 10
#ifdef S_CAN_SERVER_SETTING_HSSON
#define STRMSG_WINDOW_TEXT							"Combat-Rivals Launcher" // 2014-07-30 by St0rmy changed Launcher name
#define STRMSG_REG_STRING_CLIENT_VERSION			"ACEonlineVersion"
#define STRMSG_REG_STRING_REGISTRYKEY_NAME			"Wikigames"				// 2008-07-31 by cmkwon, Yedang-Global_Eng 를 Wikigames_Eng 로 변경 함 - 
#endif

///////////////////////////////////////////////////////////////////////////////
// 2007-06-27 by cmkwon, 중국 방심취 시스템 수정 - 미성년자 관련
// Kor		- 만 20세
// China	- 만 18세
#define ADULT_YEARS									20			// 2007-06-29 by cmkwon,

///////////////////////////////////////////////////////////////////////////////
// 2007-07-06 by cmkwon, SCAdminTool에서 OnlyServerAdmin관련 수정 - 계정 정보
#define SCADMINTOOL_ONLY_SERVER_ADMIN_ACCOUNT_NAME		"SC_moniter"
#define SCADMINTOOL_ONLY_SERVER_ADMIN_PASSWORD			"cowboyWkd"

///////////////////////////////////////////////////////////////////////////////
// 2007-09-05 by cmkwon, EXE_1에 로그인 서버 선택 인터페이스 수정 - 상위 URL, 우측 하단 URL
#define EXE1_URL_1										"http://notice.aceonline.com.cn/ace2.htm"
#define EXE1_URL_2										"http://notice.aceonline.com.cn/ace1.htm"


///////////////////////////////////////////////////////////////////////////////
// 2008-12-19 by cmkwon, 한국 Yedang 핵쉴드 모니터링 서버 설정 추가 - IP가 ""로 설정되면 모니터링 서버를 사용하지 않는 것임, 현재는 Masang140과 Yedang만 사용 할 것임

// 국가 소스통합 때 추가 되어야 할 부분 순서 11

#ifdef S_CAN_SERVER_SETTING_HSSON
#define GAME_GUARD_MONITORING_SERVER_IP					""
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 월드랭킹 DB 서버 정보
// 2009-06-01 by cmkwon, 월드 랭킹 시스템 테스트 기능 구현(for 테섭) - 
// 국가 소스통합 때 추가 되어야 할 부분 순서 12

#ifdef S_CAN_SERVER_SETTING_HSSON
#define WRK_DBSERVER_IP							"127.0.0.1"				// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)
#define WRK_DBSERVER_PORT						1433
#define WRK_DBSERVER_DATABASE_NAME				"atum2_db_WorldRanking"
#define WRK_DBSERVER_ID							"atum"
#define WRK_DBSERVER_PWD						"callweb"
#define WRK_DBSERVER_IP_FOR_TEST_SERVER			"127.0.0.1"				// 2009-12-28 by cmkwon, 마상회사 IP 변경 - 기존(121.134.114.)// 2009-06-01 by cmkwon, 월드 랭킹 시스템 테스트 기능 구현(for 테섭) - 
#define WRK_DBSERVER_PORT_FOR_TEST_SERVER		9979					// 2009-06-01 by cmkwon, 월드 랭킹 시스템 테스트 기능 구현(for 테섭) - 
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-03-31 by cmkwon, 세력초기화 시스템 구현 - 
#define MAX_INFLUENCE_PERCENT			53		// 최대 5% 차이까지만 세력 선택이 가능한다.

///////////////////////////////////////////////////////////////////////////////
// 2009-05-12 by cmkwon, (일본요청) 일본만 전진 기지전 주기 7일로 수정 - 전진기지전 주기 서비스별로 다르게 설정
// 국가 소스통합 때 추가 되어야 할 부분 순서 13

#ifdef S_CAN_SERVER_SETTING_HSSON
#define	OUTPOST_NEXTWARGAP				5
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-07-08 by cmkwon, 전쟁 관련 정의 위치 이동(LocalizationDefineCommon.h) - 
// 국가 소스통합 때 추가 되어야 할 부분 순서 14

#ifdef S_CAN_SERVER_SETTING_HSSON
#define	OUTPOST_WARTIME					120			// 전진기지전 진행 시간			==> 마상 10분, 나머지는 120분
#define OUTPOST_WARTIME_FOR_TESTSERVER	60			// 테섭은 전진기지전 진행 시간	==> 마상 10분, 나머지는 60분
#define PAY_MINIMUN_COUNT				10			// 모선전,전진기지전,거점전 개인 보상을 위한 최소 인원수 ==> 마상 1명, 나머지는 10명
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 
#define SIZE_MAX_ADDABLE_INVENTORY_COUNT		50		// 기본과 프리미엄을 제외한 추가로 가능한 최대 인벤 추가 개수
#define SIZE_MAX_ADDABLE_STORE_COUNT			50		// 기본과 프리미엄을 제외한 추가로 가능한 최대 창고 추가 개수

////////////////////////////////////////////////////////////////////////////////
// 컨텐츠 버젼 관리용 디파인. by hsLee. 
#define __CONTENTS_SHOW_INFINITY_DIFFICULTY_EDIT_WND__		// 인피니티 난이도 조정 UI 보이기.	2010. 07. 27. by hsLee.
////////////////////////////////////////////////////////////////////////////////


#endif // end_#ifndef _LOCALIZATION_DEFINE_COMMON_H_
