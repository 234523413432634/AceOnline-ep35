// 2006-09-05 by cmkwon
// #include "LocalizationDefineCommon.h"
#include "Contents.h"

#ifndef _LOCALIZATION_DEFINE_COMMON_H_
#define _LOCALIZATION_DEFINE_COMMON_H_


///////////////////////////////////////////////////////////////////////////////
// 2006-09-04 by cmkwon, �� �ٸ� Define ����Ʈ

///////////////////////////////////////////////////////////////////////////////
// 2008-01-08 by cmkwon, ��� ���� ���� ���Ǹ� �ϳ��� ������ - SERVICE_TYPE_XXX �� ������, Preprocessor definitions �� ������� ����
// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [����-�ʼ�]���� Ÿ��(SERVICE_TYPE_XXX) ���� �ϱ�
//  SERVICE_TYPE_KOREAN_SERVER_1		==> �ѱ�	Masangsoft		- Kor	100
//  SERVICE_TYPE_KOREAN_SERVER_2		==>	�ѱ�	Yedang			- Kor	1000
//  SERVICE_TYPE_ENGLISH_SERVER_1		==>	ĳ����	Wikigames		- Eng	2000
//  SERVICE_TYPE_ENGLISH_SERVER_2		==>	����	Gameforge4D		- Eng	5000	
//  SERVICE_TYPE_GERMAN_SERVER_1		==>	����	Gameforge4D		- Deu	5100	// 2008-04-11 by cmkwon, ���� ���� �߰� - Gameforge4D ���Ͼ� 
//  SERVICE_TYPE_CHINESE_SERVER_1		==>	�߱�	Yetime			- Chn	3000
//  SERVICE_TYPE_VIETNAMESE_SERVER_1	==>	��Ʈ��	VTC-Intecom		- Viet	4000
//  SERVICE_TYPE_THAI_SERVER_1			==>	�±�	WinnerOnline	- Tha	6000	// 2008-04-11 by cmkwon, ���� ���� �߰� - WinnerOnline �±���
//	SERVICE_TYPE_SINGAPORE_1			==> ����		 WinnerOnline- Sgp	6100	// 2010-12-07 by shcho,	 ���� ���� �߰�(WinnerOnline ����) - 
//	SERVICE_TYPE_INDONESIA_SERVER_1		==> �ε��׽þƾ� WinnerOnline- IND	6200	// 2010-01-11 by shcho,	 ���� ���� �߰�(WinnerOnline �ε��׽þƾ�) - 
//  SERVICE_TYPE_RUSSIAN_SERVER_1		==>	���þ�	Innova			- Rus	7000	// 2008-05-29 by cmkwon, ���� ���� �߰�(Innova_Rus ���þƾ� �߰�) - 
//  SERVICE_TYPE_TAIWANESE_SERVER_1		==>	�븸	Newpower		- Tpe	8000	// 2008-09-23 by cmkwon, ���� ���� �߰�(�븸 Netpower_Tpe) - 
//  SERVICE_TYPE_JAPANESE_SERVER_1		==> �Ϻ�	Arario			- Jpn	10000	// 2008-12-03 by cmkwon, ���� ���� �߰�(�Ϻ� Arario_Jpn) - 
//  SERVICE_TYPE_TURKISH_SERVER_1		==> ��Ű	Gameforge4D		- Tur	5200	// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - 
//  SERVICE_TYPE_ITALIAN_SERVER_1		==> ��Ż���ƾ�	Gameforge4D	- Ita	5400	// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - 
//  SERVICE_TYPE_FRENCH_SERVER_1		==> ��������	Gameforge4D	- Fra	5500	// 2008-12-22 by cmkwon, ���� ���� �߰�(Gameforge4D ��Ű��, �Ҿ�, ��Ż���ƾ�) - 
//  SERVICE_TYPE_POLISH_SERVER_1		==> �������	Gameforge4D	- Pol	5600	// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//  SERVICE_TYPE_SPANISH_SERVER_1		==> �����ξ�	Gameforge4D	- Esp	5700	// 2009-06-04 by cmkwon, ���� ���� �߰�(Gameforge4D �������, �����ξ�) - 
//	SERVICE_TYPE_ARGENTINA_SERVER_1		==> �Ƹ���Ƽ��	LIN			- Arg	11000	// 2010-11-01 by shcho,	 ���� ���� �߰�(Gameforge4D �����ξ�, �Ƹ���Ƽ����) -  

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 01

#ifdef S_CAN_SERVER_SETTING_HSSON
#define SERVICE_TYPE_ENGLISH_SERVER_1
#define SERVICE_UID_FOR_WORLD_RANKING		2000			// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - 
#endif

///////////////////////////////////////////////////////////////////////////////
// 2008-05-09 by cmkwon, CodePage ���� �߰� - 
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

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 02

#ifdef S_CAN_SERVER_SETTING_HSSON
#define CODE_PAGE							1252
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-04-20 by cmkwon, Gameforge4D "/����" ��ɾ� �����ϱ� - 
#if defined(SERVICE_TYPE_ENGLISH_SERVER_2) || defined(SERVICE_TYPE_GERMAN_SERVER_1) || defined(SERVICE_TYPE_TURKISH_SERVER_1) || defined(SERVICE_TYPE_ITALIAN_SERVER_1) || defined(SERVICE_TYPE_FRENCH_SERVER_1) || defined(SERVICE_TYPE_POLISH_SERVER_1) || defined(SERVICE_TYPE_SPANISH_SERVER_1)
	#define _DEFINED_GAMEFORGE4D_		// 2009-04-21 by cmkwon, ���縵 ������.
#endif


///////////////////////////////////////////////////////////////////////////////
// 2009-04-29 by cmkwon, �ٽ��� ��� ���� #define ���� ó�� - 
// 2008-04-25 by cmkwon, ���� ���/���� �߰��� �� �߰� �Ǿ�� �ϴ� ���� - [���-�ɼ�] �߰� ���ÿ� �ٽ��� ��� ���� �߰�
// 2009-10-06 by cmkwon, ��Ʈ�� ���� ���� X-TRAP���� ���� - ��Ʈ�� �ٽ��忡�� ����
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_KOREAN_SERVER_2) || defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_VIETNAMESE_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(_DEFINED_GAMEFORGE4D_)
// 2009-11-04 by cmkwon, �±� ���Ӱ��� Apex�� ���� - �±�(SERVICE_TYPE_THAI_SERVER_1) ������.
//#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_KOREAN_SERVER_2) || defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(SERVICE_TYPE_THAI_SERVER_1) || defined(_DEFINED_GAMEFORGE4D_)
#if defined(SERVICE_TYPE_KOREAN_SERVER_1) || defined(SERVICE_TYPE_KOREAN_SERVER_2) || defined(SERVICE_TYPE_ENGLISH_SERVER_1) || defined(_DEFINED_GAMEFORGE4D_)

#ifdef GAMEGUARD_NOT_EXECUTE_HSSON	

#else
//	 	#define _USING_HACKSHIELD_			// 2009-04-29 by cmkwon, �ٽ��� ��� ���� #define ���� ó�� - �ٽ��� ��� ���� ����
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

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 04

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
// Kor_Masang140	==> 121.134.114.140:9979	// 2007-01-03 by cmkwon, ���� ����
// Kor_Yedang		==> 192.168.10.40:9979		// 2007-01-03 by cmkwon, Yedang �缳 IP
// Eng_Gala-Net		==> ��� ����
// Viet_VTC-Intecom	==> ��� ����
// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 05

#ifdef S_CAN_SERVER_SETTING_HSSON
#define MSBILLING_DB_SERVER_IP						"127.0.0.1"
#endif

#define MSBILLING_DB_SERVER_PORT					9979

// Kor_Masang51		==> 1
// Kor_ETRI			==> 1
// Eng_Gala-Net		==> ��� ����
// Viet_VTC-Intecom	==> ��� ����
#define MSBILLING_GAMEUID							1

// 2006-09-22 by dhjin
// Kor_Masang51		==> 201			// 2006-10-23 by cmkwon, ����(101-->201)
// Kor_ETRI			==> 201			// 2006-10-23 by cmkwon, ����(101-->201)
// Eng_Gala-Net		==> 201			// 2006-10-23 by cmkwon, ����(101-->201)
// Viet_VTC-Intecom	==> 201			// 2006-10-23 by cmkwon, ����(101-->201)
#define COUNT_IN_MEMBERSHIP_GUILDSTORE				201		// 2006-09-22 by dhjin, ����� ���񽺽� ���� â�� ī��Ʈ


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// 2007-02-13 by cmkwon

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 06

#ifdef S_CAN_SERVER_SETTING_HSSON
#define STRMSG_S_GAMEHOMEPAGE_DOMAIN			"http://ace.subagames.com"		// 2008-08-05 by cmkwon, WikiGames_Eng ���� ���� ���� - ,"http://www.ace-onlines.com"
#endif

///////////////////////////////////////////////////////////////////////////////
// 2006-05-22 by cmkwon, ��� MD5�� ���ڵ��ÿ� ���� ��� �տ� �߰��� ��Ʈ�� - 
#define MD5_PASSWORD_ADDITIONAL_STRING			""

#define EXT_AUTH_GAME_NAME						"SCO"		// 2006-05-22 by cmkwon

#ifdef S_CAN_SERVER_SETTING_HSSON
// 2008-06-05 by cmkwon, AdminTool, Monitor ���� ���� IP�� server config file �� �����ϱ� - MS140�� ������ �׽�Ʈ�� ���� IP �� Ʋ����(121.134.11.) ���� ��
// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP1		"127.0.0."		// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP2		"127.0.0."		// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP3		"127.0.0."		// 2008-08-05 by cmkwon, WikiGames_Eng ���� ���� ���� - ���� Private IP
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP4		"127.0.0."		// 2008-08-05 by cmkwon, WikiGames_Eng ���� ���� ���� - ���� Public IP
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP5		"127.0.0."		// 2008-08-05 by cmkwon, WikiGames_Eng ���� ���� ���� - �׼� Public IP
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP6		"127.0.0."		// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP7		"127.0.0."		// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP8		"127.0.0."		// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP9		"127.0.0."		// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define SCADMINTOOL_CONNECTABLE_PREFIX_IP10		"127.0.0."		// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
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
// Kor_Yedang		==> 2006-12-25 by cmkwon, ������
#define BILLING_DBSERVER_USER_PWD				"callweb"
#endif // S_CAN_SERVER_SETTING_HSSON

///////////////////////////////////////////////////////////////////////////////
// 2007-02-13 by cmkwon

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 08

#ifdef S_CAN_SERVER_SETTING_HSSON
#define	SG_BOX_FONT_FACENAME						"Tahoma"					// 2007-02-12 by cmkwon, �۾�ü
#define	SG_BOX_FONT_CHARSET							ANSI_CHARSET			// 2007-02-12 by cmkwon, ĳ���ͼ�
#define	SG_BOX_FONT_WEIGHT							FW_BOLD					// 2007-02-12 by cmkwon, �۾�ü �α�
#endif

// #define STR_XOR_KEY_STRING_PRE_SERVER_ADDRESS				"+-faNsf(^fP{)3>fnao??_+|23kdasf*^@`d{]s*&DS"	// 2008-04-23 by cmkwon, PreServer �ּҸ� IP�� ������ �Ѵ� ���� - 

#if defined(S_CAN_SERVER_SETTING_HSSON) && defined(S_ACCESS_INTERNAL_SERVER_HSSON)
	// ���� ������ ip ����
	// 66.207.198.252							==>	"1D1B48537E444819675E7E491C01"	 // 2010-05-26 IP���� ����IP 208.68.90.122
	#define CHOICE_PRE_SERVER_IP_OR_DOMAIN_IN_XOR	"1A14544F7F455E066E48614A1E"	// 2014-07-30 by St0rmy changed to hamachi ip

	#define REGISTRY_BASE_PATH						"Combat-Rivals Launcher"
	#define EXE_1_FILE_NAME							"ACEonline.exe"
	#define LAUNCHER_FILE_NAME						"Launcher.atm"

	#define CLIENT_EXEUTE_FILE_NAME					"ACEonline.exe"
	#define URL_REGISTER_PAGE						"reg.asp"				// 2006-04-05 by cmkwon, ������

	#define WEB_START_REGISTRY_VALUE_NAME			"InstallPath"
#endif

///////////////////////////////////////////////////////////////////////////////
// 2006-12-22 by cmkwon, �����̸� �����ϸ鼭 

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 10
#ifdef S_CAN_SERVER_SETTING_HSSON
#define STRMSG_WINDOW_TEXT							"Combat-Rivals Launcher" // 2014-07-30 by St0rmy changed Launcher name
#define STRMSG_REG_STRING_CLIENT_VERSION			"ACEonlineVersion"
#define STRMSG_REG_STRING_REGISTRYKEY_NAME			"Wikigames"				// 2008-07-31 by cmkwon, Yedang-Global_Eng �� Wikigames_Eng �� ���� �� - 
#endif

///////////////////////////////////////////////////////////////////////////////
// 2007-06-27 by cmkwon, �߱� ����� �ý��� ���� - �̼����� ����
// Kor		- �� 20��
// China	- �� 18��
#define ADULT_YEARS									20			// 2007-06-29 by cmkwon,

///////////////////////////////////////////////////////////////////////////////
// 2007-07-06 by cmkwon, SCAdminTool���� OnlyServerAdmin���� ���� - ���� ����
#define SCADMINTOOL_ONLY_SERVER_ADMIN_ACCOUNT_NAME		"SC_moniter"
#define SCADMINTOOL_ONLY_SERVER_ADMIN_PASSWORD			"cowboyWkd"

///////////////////////////////////////////////////////////////////////////////
// 2007-09-05 by cmkwon, EXE_1�� �α��� ���� ���� �������̽� ���� - ���� URL, ���� �ϴ� URL
#define EXE1_URL_1										"http://notice.aceonline.com.cn/ace2.htm"
#define EXE1_URL_2										"http://notice.aceonline.com.cn/ace1.htm"


///////////////////////////////////////////////////////////////////////////////
// 2008-12-19 by cmkwon, �ѱ� Yedang �ٽ��� ����͸� ���� ���� �߰� - IP�� ""�� �����Ǹ� ����͸� ������ ������� �ʴ� ����, ����� Masang140�� Yedang�� ��� �� ����

// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 11

#ifdef S_CAN_SERVER_SETTING_HSSON
#define GAME_GUARD_MONITORING_SERVER_IP					""
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-02-12 by cmkwon, EP3-3 ���巩ŷ�ý��� ���� - ���巩ŷ DB ���� ����
// 2009-06-01 by cmkwon, ���� ��ŷ �ý��� �׽�Ʈ ��� ����(for �׼�) - 
// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 12

#ifdef S_CAN_SERVER_SETTING_HSSON
#define WRK_DBSERVER_IP							"127.0.0.1"				// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)
#define WRK_DBSERVER_PORT						1433
#define WRK_DBSERVER_DATABASE_NAME				"atum2_db_WorldRanking"
#define WRK_DBSERVER_ID							"atum"
#define WRK_DBSERVER_PWD						"callweb"
#define WRK_DBSERVER_IP_FOR_TEST_SERVER			"127.0.0.1"				// 2009-12-28 by cmkwon, ����ȸ�� IP ���� - ����(121.134.114.)// 2009-06-01 by cmkwon, ���� ��ŷ �ý��� �׽�Ʈ ��� ����(for �׼�) - 
#define WRK_DBSERVER_PORT_FOR_TEST_SERVER		9979					// 2009-06-01 by cmkwon, ���� ��ŷ �ý��� �׽�Ʈ ��� ����(for �׼�) - 
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - 
#define MAX_INFLUENCE_PERCENT			53		// �ִ� 5% ���̱����� ���� ������ �����Ѵ�.

///////////////////////////////////////////////////////////////////////////////
// 2009-05-12 by cmkwon, (�Ϻ���û) �Ϻ��� ���� ������ �ֱ� 7�Ϸ� ���� - ���������� �ֱ� ���񽺺��� �ٸ��� ����
// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 13

#ifdef S_CAN_SERVER_SETTING_HSSON
#define	OUTPOST_NEXTWARGAP				5
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-07-08 by cmkwon, ���� ���� ���� ��ġ �̵�(LocalizationDefineCommon.h) - 
// ���� �ҽ����� �� �߰� �Ǿ�� �� �κ� ���� 14

#ifdef S_CAN_SERVER_SETTING_HSSON
#define	OUTPOST_WARTIME					120			// ���������� ���� �ð�			==> ���� 10��, �������� 120��
#define OUTPOST_WARTIME_FOR_TESTSERVER	60			// �׼��� ���������� ���� �ð�	==> ���� 10��, �������� 60��
#define PAY_MINIMUN_COUNT				10			// ����,����������,������ ���� ������ ���� �ּ� �ο��� ==> ���� 1��, �������� 10��
#endif

///////////////////////////////////////////////////////////////////////////////
// 2009-11-02 by cmkwon, ĳ��(�κ�/â�� Ȯ��) ������ �߰� ���� - 
#define SIZE_MAX_ADDABLE_INVENTORY_COUNT		50		// �⺻�� �����̾��� ������ �߰��� ������ �ִ� �κ� �߰� ����
#define SIZE_MAX_ADDABLE_STORE_COUNT			50		// �⺻�� �����̾��� ������ �߰��� ������ �ִ� â�� �߰� ����

////////////////////////////////////////////////////////////////////////////////
// ������ ���� ������ ������. by hsLee. 
#define __CONTENTS_SHOW_INFINITY_DIFFICULTY_EDIT_WND__		// ���Ǵ�Ƽ ���̵� ���� UI ���̱�.	2010. 07. 27. by hsLee.
////////////////////////////////////////////////////////////////////////////////


#endif // end_#ifndef _LOCALIZATION_DEFINE_COMMON_H_
