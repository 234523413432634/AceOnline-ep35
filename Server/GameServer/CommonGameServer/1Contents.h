#pragma once

//----------------------------------------------------------------------------------------------------------//
// 국가별 define                                                                                            //
//----------------------------------------------------------------------------------------------------------//
// _DEBUG
// TEST140
// YEDANG_KOR
// WIKIGAMES_ENG
// YETIME_CHN
// INTECOM_VIET
// GAMEFORGE4D_ENG
// GAMEFORGE4D_DEU
// GAMEFORGE4D_TURKISH
// GAMEFORGE4D_ITALIAN
// GAMEFORGE4D_FRANCE
// GAMEFORGE4D_POL
// GAMEFORGE4D_ESP
// WINNERONLINE_THA
// WINNERONLINE_SGP
// WINNERONLINE_IDN
// INNOVA_RUS
// NETPOWER_TPE
// ARARIO_JPN
// LIN_ARG
//
//----------------------------------------------------------------------------------------------------------//
// define 사용 규약                                                                                         //
//----------------------------------------------------------------------------------------------------------//
//
// 1. 국가별 define 사용해서 묶을 때는 위의 순서 대로 묶고, 공백 역시 정확하게 삽입
// ex1> #if defined(TEST140) || defined(YEDANG_KOR) ( o ) 딩동댕!
// ex2> #if defined(TEST140) ||defined(YEDANG_KOR)  ( x ) 땡!
// ex3> #if defined(YEDANG_KOR) || defined(TEST140) ( x ) 땡!
//
// 2. 전처리기 사용 시 #ifndef 사용을 불허 (대신 #else를 사용)
// ex1> #ifndef TEST140 ( x ) 땡!
//
// 3. define을 분류 할 때 다른 국가에서 사용 가능성이 농후 할 경우 아래로 분리하고, 아닐 경우 위쪽에 분리
//
// 4. define을 생성 시 국가별 특성을 가질 경우 앞쪽에 국가 이니셜 삽입
//
// 5. define을 생성 시 자신의 이니셜을 끝에 삽입
//
// 6. define을 생성 시 서버, 클라에 따라서 C나 S를 삽입, 둘다 사용 할 경우 SC로 삽입
//
// 7. 동일한 define을 절대 2번 선언하지 말 것
//
// 8. 빌드 선택 시 "Win32 Debug"는 폐기된 빌드이며, 기본으로 "Win32 D_Test140" 사용
//
// 9. 국가별 define(ex> TEST140, YEDANG_KOR)은 절대 이 헤더파일(Contents.h) 이외에는 쓰지 말 것
//
//----------------------------------------------------------------------------------------------------------//
// 국가별로 차별화를 두고 다시는 변화하지 않을 작업                                                         //
//----------------------------------------------------------------------------------------------------------//

#if defined(_DEBUG) || defined(TEST140)
#define CUSTOM_OPTIMIZER_HSSON					// ini 파일 읽어서 게임에 적용
#define MULTI_LOADER_HSSON						// 클라이언트를 여러개 띄울 수 있도록 수정
#define GAMEGUARD_NOT_EXECUTE_HSSON				// 게임 가드 실행 안함
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define KOR_INPUT_LANGUAGE_HSSON				// 입력 언어 변환
#define KOR_HANGEUL_START_HSSON					// 한글 모드로 시작
#define KOR_CASHSHOP_INTERFACE_HSSON			// 캐쉬샵 인터페이스
#define KOR_GAME_RATINGS_HSSON					// 게임 등급물 위원회 아이콘 추가
#define KOR_CHARACTER_INTERFACE_POS_HSSON		// 언어에 따라 위치 수정
#endif

#if defined(YEDANG_KOR)
#define KOR_YEDANG_WEB_LAUNCHER_HSSON			// 예당 웹런쳐
#endif

#if defined(_DEBUG)
#define _ATUM_DEVELOP							// 서버용) 서버소스상 디버깅일 때 활성화 해줘야 함
#endif

#if defined(INNOVA_RUS)
#define _USING_INNOVA_FROST_					// 서버용) 러시아의 경우 게임가드로 포레스트 사용
#endif

#if defined(TEST140)
#define S_140_SERVER_SETTING_HSSON				// 접속할 서버, 파일명 등 국가별 세팅
#endif

#if defined(YEDANG_KOR)
#define S_KOR_SERVER_SETTING_HSSON				// 접속할 서버, 파일명 등 국가별 세팅
#define YEDANG_RELEASE							// 핵쉴드, 몇가지 기능 한국만 수행
#endif

#if defined(ARARIO_JPN)
#define S_JPN_SERVER_SETTING_HSSON				// 접속할 서버, 파일명 등 국가별 세팅
#endif

#if defined(WIKIGAMES_ENG)
#define S_CAN_SERVER_SETTING_HSSON				// 접속할 서버, 파일명 등 국가별 세팅
#endif

#if defined(INNOVA_RUS)
#define S_RUS_SERVER_SETTING_HSSON				// 접속할 서버, 파일명 등 국가별 세팅
#endif

#if defined(INTECOM_VIET)
#define S_VIE_SERVER_SETTING_HSSON				// 접속할 서버, 파일명 등 국가별 세팅
#endif

#if defined(TEST140)
//#define _DEBUG_MAPSETTING						// 키로 색상 바꾸기
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN)
#define S_ARARIO_HSSON							// 아라리오 채널링
#endif

#if defined(ARARIO_JPN)
#define LANGUAGE_JAPAN							// 일본에 기존에 사용하던 디파인
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
/*
#include "Str_KOR/StringDefineCommon.h"
#include "Str_KOR/StringDefineServer.h"
#include "Str_KOR/StringDefineClient.h"
*/
#include "../../../Common/Str_CAN/StringDefineCommon.h"
#include "../../../Common/Str_CAN/StringDefineServer.h"
#include "../../../Common/Str_CAN/StringDefineClient.h"
#endif

#if defined(ARARIO_JPN)
#include "Str_JPN/StringDefineCommon.h"
#include "Str_JPN/StringDefineServer.h"
#include "Str_JPN/StringDefineClient.h"
#endif

#if defined(WIKIGAMES_ENG)
#include "../../../Common/Str_CAN/StringDefineCommon.h"
#include "../../../Common/Str_CAN/StringDefineServer.h"
#include "../../../Common/Str_CAN/StringDefineClient.h"
#endif

#if defined(INNOVA_RUS)
#include "Str_RUS/StringDefineCommon.h"
#include "Str_RUS/StringDefineServer.h"
#include "Str_RUS/StringDefineClient.h"
#endif

#if defined(INTECOM_VIET)
#include "Str_VIE/StringDefineCommon.h"
#include "Str_VIE/StringDefineServer.h"
#include "Str_VIE/StringDefineClient.h"
#endif



//----------------------------------------------------------------------------------------------------------//
// 국가별로 차별화를 두지만 컨텐츠 레벨(진도) 또는 요구(특성)에 따라서 변화 될 작업                         //
//----------------------------------------------------------------------------------------------------------//
#if defined(INTECOM_VIET) || defined(LIN_ARG)
#define ONLY_FULL_WINDOW_HSSON					// 무조건 전체화면으로 게임 진행, 알트 + 탭하면 팅구기
#endif

#if defined(TEST140) || defined(YEDANG_KOR) 
#define GUILD_WAREHOUSE_ACCESS_HSSON			// 멤버쉽이 아니더라도 여단창고 이용가능
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define NEW_CASHSHOP_INTERFACE_HSSON			// 신규 캐쉬샵 작업
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define KOR_CASHSHOP_REFILL_WEB_HSSON			// 캐쉬샵 충전 웹페이지 추가
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define WAREHOUSE_SHARES_HSSON					// 캐릭터 간에 창고를 공유 할 수 있음
#endif

#if defined(TEST140)
#define SC_GROWING_PARTNER_HSKIM_JHAHN			// 캐릭터 정보 창에서 파트너UI 활성화
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN) || defined(WIKIGAMES_ENG) || defined(INTECOM_VIET) || defined(INNOVA_RUS)
#define S_INFINITY3_HSKIM						// 인피니티 3차 적용 (서버)
#define INFI_QUEST_JSKIM					    // 인피니티 퀘스트
#define MULTI_TARGET_JSKIM						// 멀티타켓
#define S_AUTHENTICATION_SERVER_HSKIM			// 인증 서버 적용 (서버)
#define SC_SECURITY_COMMAND_HSKIM				// 비밀키 적용 (클라 서버) [선행조건 (인증 서버 적용)]
//#define C_SECURITY_COMMAND_JHAHN				// 비밀키 클라이언트 확인 - 절대 주석 풀지 마세요
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(WIKIGAMES_ENG) || defined(YETIME_CHN) || defined(INTECOM_VIET) || defined(GAMEFORGE4D_ENG) || defined(GAMEFORGE4D_DEU) || defined(GAMEFORGE4D_TURKISH) || defined(GAMEFORGE4D_ITALIAN) || defined(GAMEFORGE4D_FRANCE) || defined(GAMEFORGE4D_POL) || defined(GAMEFORGE4D_ESP) || defined(WINNERONLINE_THA) || defined(WINNERONLINE_SGP) || defined(WINNERONLINE_IDN) || defined(INNOVA_RUS) || defined(NETPOWER_TPE) || defined(ARARIO_JPN) || defined(LIN_ARG)
#define S_ACCESS_INTERNAL_SERVER_HSSON		// 접속하는 IP를 내부 테스트 서버로 설정
#endif

#if defined(TEST140)
#define SC_DARK_CRASH_HSSON						// 클라이언트 크래쉬 날때 서버로 클라 정보 전송
#endif

#if defined(TEST140)
#define SC_DARK_CRASH_FILE_OUTPUT_HSSON			// 클라이언트 크래쉬 날때 클라 정보를 txt파일로 남길지 여부
#endif

#if defined(TEST140)
#define S_GLOG_HSSON						    // GLog 기능
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN) || defined(WIKIGAMES_ENG) || defined(INTECOM_VIET) || defined(INNOVA_RUS)
#define S_LOGIN_ITEM_EVENT_SHCHO			    // 로그인시 아이템 증정
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN) || defined(INTECOM_VIET)
#define S_AUTO_UPDATE_VERSION_BY_PRESVR_HSSON	// 자동 업데이트 버전
#endif

#if defined(INTECOM_VIET) || defined(INNOVA_RUS)
#define S_ARENA_NOT_INFO						// 아레나에서는 할 수 없게 함
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define SC_SHUT_DOWNMIN_SHCHO					// 셧다운제(만 16세 미만 접속 제한)
#endif
#if defined(INTECOM_VIET)
#define S_MANAGER_ADMIN_HSSON					// 게임 마스터도 계정 블럭/언블럭 시킬 수 있도록 수정
#endif



