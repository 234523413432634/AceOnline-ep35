#pragma once

//----------------------------------------------------------------------------------------------------------//
// ������ define                                                                                            //
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
// define ��� �Ծ�                                                                                         //
//----------------------------------------------------------------------------------------------------------//
//
// 1. ������ define ����ؼ� ���� ���� ���� ���� ��� ����, ���� ���� ��Ȯ�ϰ� ����
// ex1> #if defined(TEST140) || defined(YEDANG_KOR) ( o ) ������!
// ex2> #if defined(TEST140) ||defined(YEDANG_KOR)  ( x ) ��!
// ex3> #if defined(YEDANG_KOR) || defined(TEST140) ( x ) ��!
//
// 2. ��ó���� ��� �� #ifndef ����� ���� (��� #else�� ���)
// ex1> #ifndef TEST140 ( x ) ��!
//
// 3. define�� �з� �� �� �ٸ� �������� ��� ���ɼ��� ���� �� ��� �Ʒ��� �и��ϰ�, �ƴ� ��� ���ʿ� �и�
//
// 4. define�� ���� �� ������ Ư���� ���� ��� ���ʿ� ���� �̴ϼ� ����
//
// 5. define�� ���� �� �ڽ��� �̴ϼ��� ���� ����
//
// 6. define�� ���� �� ����, Ŭ�� ���� C�� S�� ����, �Ѵ� ��� �� ��� SC�� ����
//
// 7. ������ define�� ���� 2�� �������� �� ��
//
// 8. ���� ���� �� "Win32 Debug"�� ���� �����̸�, �⺻���� "Win32 D_Test140" ���
//
// 9. ������ define(ex> TEST140, YEDANG_KOR)�� ���� �� �������(Contents.h) �̿ܿ��� ���� �� ��
//
//----------------------------------------------------------------------------------------------------------//
// �������� ����ȭ�� �ΰ� �ٽô� ��ȭ���� ���� �۾�                                                         //
//----------------------------------------------------------------------------------------------------------//

#if defined(_DEBUG) || defined(TEST140)
#define CUSTOM_OPTIMIZER_HSSON					// ini ���� �о ���ӿ� ����
#define MULTI_LOADER_HSSON						// Ŭ���̾�Ʈ�� ������ ��� �� �ֵ��� ����
#define GAMEGUARD_NOT_EXECUTE_HSSON				// ���� ���� ���� ����
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define KOR_INPUT_LANGUAGE_HSSON				// �Է� ��� ��ȯ
#define KOR_HANGEUL_START_HSSON					// �ѱ� ���� ����
#define KOR_CASHSHOP_INTERFACE_HSSON			// ĳ���� �������̽�
#define KOR_GAME_RATINGS_HSSON					// ���� ��޹� ����ȸ ������ �߰�
#define KOR_CHARACTER_INTERFACE_POS_HSSON		// �� ���� ��ġ ����
#endif

#if defined(YEDANG_KOR)
#define KOR_YEDANG_WEB_LAUNCHER_HSSON			// ���� ������
#endif

#if defined(_DEBUG)
#define _ATUM_DEVELOP							// ������) �����ҽ��� ������� �� Ȱ��ȭ ����� ��
#endif

#if defined(INNOVA_RUS)
#define _USING_INNOVA_FROST_					// ������) ���þ��� ��� ���Ӱ���� ������Ʈ ���
#endif

#if defined(TEST140)
#define S_140_SERVER_SETTING_HSSON				// ������ ����, ���ϸ� �� ������ ����
#endif

#if defined(YEDANG_KOR)
#define S_KOR_SERVER_SETTING_HSSON				// ������ ����, ���ϸ� �� ������ ����
#define YEDANG_RELEASE							// �ٽ���, ��� ��� �ѱ��� ����
#endif

#if defined(ARARIO_JPN)
#define S_JPN_SERVER_SETTING_HSSON				// ������ ����, ���ϸ� �� ������ ����
#endif

#if defined(WIKIGAMES_ENG)
#define S_CAN_SERVER_SETTING_HSSON				// ������ ����, ���ϸ� �� ������ ����
#endif

#if defined(INNOVA_RUS)
#define S_RUS_SERVER_SETTING_HSSON				// ������ ����, ���ϸ� �� ������ ����
#endif

#if defined(INTECOM_VIET)
#define S_VIE_SERVER_SETTING_HSSON				// ������ ����, ���ϸ� �� ������ ����
#endif

#if defined(TEST140)
//#define _DEBUG_MAPSETTING						// Ű�� ���� �ٲٱ�
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN)
#define S_ARARIO_HSSON							// �ƶ󸮿� ä�θ�
#endif

#if defined(ARARIO_JPN)
#define LANGUAGE_JAPAN							// �Ϻ��� ������ ����ϴ� ������
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
// �������� ����ȭ�� ������ ������ ����(����) �Ǵ� �䱸(Ư��)�� ���� ��ȭ �� �۾�                         //
//----------------------------------------------------------------------------------------------------------//
#if defined(INTECOM_VIET) || defined(LIN_ARG)
#define ONLY_FULL_WINDOW_HSSON					// ������ ��üȭ������ ���� ����, ��Ʈ + ���ϸ� �ñ���
#endif

#if defined(TEST140) || defined(YEDANG_KOR) 
#define GUILD_WAREHOUSE_ACCESS_HSSON			// ������� �ƴϴ��� ����â�� �̿밡��
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define NEW_CASHSHOP_INTERFACE_HSSON			// �ű� ĳ���� �۾�
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define KOR_CASHSHOP_REFILL_WEB_HSSON			// ĳ���� ���� �������� �߰�
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define WAREHOUSE_SHARES_HSSON					// ĳ���� ���� â�� ���� �� �� ����
#endif

#if defined(TEST140)
#define SC_GROWING_PARTNER_HSKIM_JHAHN			// ĳ���� ���� â���� ��Ʈ��UI Ȱ��ȭ
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN) || defined(WIKIGAMES_ENG) || defined(INTECOM_VIET) || defined(INNOVA_RUS)
#define S_INFINITY3_HSKIM						// ���Ǵ�Ƽ 3�� ���� (����)
#define INFI_QUEST_JSKIM					    // ���Ǵ�Ƽ ����Ʈ
#define MULTI_TARGET_JSKIM						// ��ƼŸ��
#define S_AUTHENTICATION_SERVER_HSKIM			// ���� ���� ���� (����)
#define SC_SECURITY_COMMAND_HSKIM				// ���Ű ���� (Ŭ�� ����) [�������� (���� ���� ����)]
//#define C_SECURITY_COMMAND_JHAHN				// ���Ű Ŭ���̾�Ʈ Ȯ�� - ���� �ּ� Ǯ�� ������
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(WIKIGAMES_ENG) || defined(YETIME_CHN) || defined(INTECOM_VIET) || defined(GAMEFORGE4D_ENG) || defined(GAMEFORGE4D_DEU) || defined(GAMEFORGE4D_TURKISH) || defined(GAMEFORGE4D_ITALIAN) || defined(GAMEFORGE4D_FRANCE) || defined(GAMEFORGE4D_POL) || defined(GAMEFORGE4D_ESP) || defined(WINNERONLINE_THA) || defined(WINNERONLINE_SGP) || defined(WINNERONLINE_IDN) || defined(INNOVA_RUS) || defined(NETPOWER_TPE) || defined(ARARIO_JPN) || defined(LIN_ARG)
#define S_ACCESS_INTERNAL_SERVER_HSSON		// �����ϴ� IP�� ���� �׽�Ʈ ������ ����
#endif

#if defined(TEST140)
#define SC_DARK_CRASH_HSSON						// Ŭ���̾�Ʈ ũ���� ���� ������ Ŭ�� ���� ����
#endif

#if defined(TEST140)
#define SC_DARK_CRASH_FILE_OUTPUT_HSSON			// Ŭ���̾�Ʈ ũ���� ���� Ŭ�� ������ txt���Ϸ� ������ ����
#endif

#if defined(TEST140)
#define S_GLOG_HSSON						    // GLog ���
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN) || defined(WIKIGAMES_ENG) || defined(INTECOM_VIET) || defined(INNOVA_RUS)
#define S_LOGIN_ITEM_EVENT_SHCHO			    // �α��ν� ������ ����
#endif

#if defined(TEST140) || defined(YEDANG_KOR) || defined(ARARIO_JPN) || defined(INTECOM_VIET)
#define S_AUTO_UPDATE_VERSION_BY_PRESVR_HSSON	// �ڵ� ������Ʈ ����
#endif

#if defined(INTECOM_VIET) || defined(INNOVA_RUS)
#define S_ARENA_NOT_INFO						// �Ʒ��������� �� �� ���� ��
#endif

#if defined(TEST140) || defined(YEDANG_KOR)
#define SC_SHUT_DOWNMIN_SHCHO					// �˴ٿ���(�� 16�� �̸� ���� ����)
#endif
#if defined(INTECOM_VIET)
#define S_MANAGER_ADMIN_HSSON					// ���� �����͵� ���� ��/��� ��ų �� �ֵ��� ����
#endif



