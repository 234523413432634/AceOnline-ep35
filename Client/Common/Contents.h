#pragma once

#define S_CAN_SERVER_SETTING_HSSON					// 접속할 서버, 파일명 등 국가별 세팅

#if defined(_DEBUG)
#define CUSTOM_OPTIMIZER_HSSON						// ini 파일 읽어서 게임에 적용
#define MULTI_LOADER_HSSON							// 클라이언트를 여러개 띄울 수 있도록 수정
#define GAMEGUARD_NOT_EXECUTE_HSSON					// 게임 가드 실행 안함
#define _ATUM_DEVELOP								// 서버용) 서버소스상 디버깅일 때 활성화 해줘야 함
#endif

#if defined(_KOR)
#define KOR_YEDANG_WEB_LAUNCHER_HSSON				// 예당 웹런쳐
#define YEDANG_RELEASE								// 핵쉴드, 몇가지 기능 한국만 수행
#define S_ARARIO_HSSON								// used to strtok email to get first token as username
#define KOR_INPUT_LANGUAGE_HSSON					// 입력 언어 변환
#define KOR_HANGEUL_START_HSSON						// 한글 모드로 시작
#define KOR_CASHSHOP_INTERFACE_HSSON				// 캐쉬샵 인터페이스
#define KOR_GAME_RATINGS_HSSON						// 게임 등급물 위원회 아이콘 추가
#define KOR_CHARACTER_INTERFACE_POS_HSSON			// 언어에 따라 위치 수정
#include "../../../Common/Str_KOR/StringDefineCommon.h"
#include "../../../Common/Str_KOR/StringDefineServer.h"
#include "../../../Common/Str_KOR/StringDefineClient.h"
#endif

#if defined(_JPN)
#define LANGUAGE_JAPAN								// 일본에 기존에 사용하던 디파인
#define S_ARARIO_HSSON								// 아라리오 채널링
#include "../../../Common/Str_JPN/StringDefineCommon.h"
#include "../../../Common/Str_JPN/StringDefineServer.h"
#include "../../../Common/Str_JPN/StringDefineClient.h"
#endif

#if defined(_ENG)
#include "../../../Common/Str_CAN/StringDefineCommon.h"
#include "../../../Common/Str_CAN/StringDefineServer.h"
#include "../../../Common/Str_CAN/StringDefineClient.h"
#endif

#if defined(_RUS)
#include "../../../Common/Str_RUS/StringDefineCommon.h"
#include "../../../Common/Str_RUS/StringDefineServer.h"
#include "../../../Common/Str_RUS/StringDefineClient.h"
#endif

#if defined(_VIE)
#include "../../../Common/Str_VIE/StringDefineCommon.h"
#include "../../../Common/Str_VIE/StringDefineServer.h"
#include "../../../Common/Str_VIE/StringDefineClient.h"
#endif

//----------------------------------------------------------------------------------------------------------//
// 국가별로 차별화를 두지만 컨텐츠 레벨(진도) 또는 요구(특성)에 따라서 변화 될 작업                         //
//----------------------------------------------------------------------------------------------------------//

#if defined(WIKIGAMES_ENG)
#define S_INFINITY3_HSKIM							// Enable IF3
#define INFI_QUEST_JSKIM							// Enable IF3 Quests
#define MULTI_TARGET_JSKIM							// Monster multi target (Enable load from OMI.tex by client)
#define NEW_CASHSHOP_INTERFACE_HSSON				// ItemShop:: enables GIFT button
#define S_ACCESS_INTERNAL_SERVER_HSSON				// Connect to test server (TESTSERVER_LAUNCHER_WEB_URL in launcher and other IP in LocalizationDefineCommon.h)
#define S_LOGIN_ITEM_EVENT_SHCHO					// Item event server sided (not used)
#define KOR_CASHSHOP_REFILL_WEB_HSSON				// ItemShop:: Show refill button if defined YEDANG_RELEASE ItemShop will be disabled
#define WAREHOUSE_SHARES_HSSON						// allow shared wh between characters on the same account (tabs in wh)
#define GUILD_WAREHOUSE_ACCESS_HSSON				// allow using guild wh
//#define S_AUTHENTICATION_SERVER_HSKIM				// Enable Auth Server (preserver will require auth server validation to start)
//#define _DEBUG_MAPSETTING							// 키로 색상 바꾸기
//#define SC_SECURITY_COMMAND_HSKIM					// Enable masang command to take down server (lol)
//#define C_SECURITY_COMMAND_JHAHN					// Client sided security command
//#define ONLY_FULL_WINDOW_HSSON					// possible to play only full screen
//#define SC_GROWING_PARTNER_HSKIM_JHAHN			// allow PET leveling?
//#define SC_DARK_CRASH_HSSON						// Dark crash feature
//#define SC_DARK_CRASH_FILE_OUTPUT_HSSON			// Dark crash output file generation feature
//#define S_AUTO_UPDATE_VERSION_BY_PRESVR_HSSON		// Load version info from HTTP server instead of version.ver from config (requires proper .ver files on update server)
//#define S_GLOG_HSSON								// GLog on off
//#define S_ARENA_NOT_INFO							// disable checking if ArenaInfo.State is not equal to ARENA_STATE_NONE
//#define SC_SHUT_DOWNMIN_SHCHO						// "Players under the age of 16 cannot play from 12 A.M. to 6 A.M. by the regulation of the juvenile protection."
//#define S_MANAGER_ADMIN_HSSON						// partially disable functionality of Admin Tool for users with 256 account type (GM)
#endif

#if defined(_ATUM_CLIENT)
#define _WIREFRAME
#define _NOCLIP
#define _DRAW_EVENTS
#define _DISABLE_BSTOP_AUTOHORIZONT
#define _INSTANT_LAUNCH
#define _NO_FADE
#endif



