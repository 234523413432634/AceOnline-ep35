#pragma once

#define S_CAN_SERVER_SETTING_HSSON					// Á¢¼ÓÇÒ ¼­¹ö, ÆÄÀÏ¸í µî ±¹°¡º° ¼¼ÆÃ

#if defined(_DEBUG)
#define CUSTOM_OPTIMIZER_HSSON						// ini ÆÄÀÏ ÀÐ¾î¼­ °ÔÀÓ¿¡ Àû¿ë
#define MULTI_LOADER_HSSON							// Å¬¶óÀÌ¾ðÆ®¸¦ ¿©·¯°³ ¶ç¿ï ¼ö ÀÖµµ·Ï ¼öÁ¤
#define GAMEGUARD_NOT_EXECUTE_HSSON					// °ÔÀÓ °¡µå ½ÇÇà ¾ÈÇÔ
#define _ATUM_DEVELOP								// ¼­¹ö¿ë) ¼­¹ö¼Ò½º»ó µð¹ö±ëÀÏ ¶§ È°¼ºÈ­ ÇØÁà¾ß ÇÔ
#endif

#if defined(_KOR)
#define KOR_YEDANG_WEB_LAUNCHER_HSSON				// ¿¹´ç À¥·±ÃÄ
#define YEDANG_RELEASE								// ÇÙ½¯µå, ¸î°¡Áö ±â´É ÇÑ±¹¸¸ ¼öÇà
#define S_ARARIO_HSSON								// used to strtok email to get first token as username
#define KOR_INPUT_LANGUAGE_HSSON					// ÀÔ·Â ¾ð¾î º¯È¯
#define KOR_HANGEUL_START_HSSON						// ÇÑ±Û ¸ðµå·Î ½ÃÀÛ
#define KOR_CASHSHOP_INTERFACE_HSSON				// Ä³½¬¼¥ ÀÎÅÍÆäÀÌ½º
#define KOR_GAME_RATINGS_HSSON						// °ÔÀÓ µî±Þ¹° À§¿øÈ¸ ¾ÆÀÌÄÜ Ãß°¡
#define KOR_CHARACTER_INTERFACE_POS_HSSON			// ¾ð¾î¿¡ µû¶ó À§Ä¡ ¼öÁ¤
#include "../../../Common/Str_KOR/StringDefineCommon.h"
#include "../../../Common/Str_KOR/StringDefineServer.h"
#include "../../../Common/Str_KOR/StringDefineClient.h"
#endif

#if defined(_JPN)
#define LANGUAGE_JAPAN								// ÀÏº»¿¡ ±âÁ¸¿¡ »ç¿ëÇÏ´ø µðÆÄÀÎ
#define S_ARARIO_HSSON								// ¾Æ¶ó¸®¿À Ã¤³Î¸µ
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
// ±¹°¡º°·Î Â÷º°È­¸¦ µÎÁö¸¸ ÄÁÅÙÃ÷ ·¹º§(Áøµµ) ¶Ç´Â ¿ä±¸(Æ¯¼º)¿¡ µû¶ó¼­ º¯È­ µÉ ÀÛ¾÷                         //
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
//#define _DEBUG_MAPSETTING							// Å°·Î »ö»ó ¹Ù²Ù±â
//#define SC_SECURITY_COMMAND_HSKIM					// Enable masang command to take down server (lol)
//#define C_SECURITY_COMMAND_JHAHN					// Client sided security command
//#define ONLY_FULL_WINDOW_HSSON					// possible to play only full screen
//#define SC_GROWING_PARTNER_HSKIM_JHAHN			// allow PET leveling­
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



