#include "stdafx.h"
#include "AtumSJ.h"
#include "defineglobal.h"
#include <fstream>					// 2007-05-10 by cmkwon

#ifdef _ATUM_SERVER
#include "ODBCStatement.h"
#include "AtumDBHelper.h"
#include "GlobalGameServer.h"			// 2006-06-12 by cmkwon
#endif // _ATUM_SERVER

#define MAX_LEVEL_OR_STAT_VALUE			341		// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 기존(301)
extern const LEVEL_STAT_VALUE g_arrLevelStatValue[];
extern const LEVEL_EXPERIENCE arrLevelExperienceNew[];



setString				g_setAllLetterList;		// 2007-05-04 by cmkwon

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CParamFactor::Reset()
/// \brief		변수 초기화
/// \author		kelovon
/// \date		2004-04-10 ~ 2004-04-10
/// \warning
///////////////////////////////////////////////////////////////////////////////
void CParamFactor::Reset()
{
	MEMSET_ZERO(this, sizeof(CParamFactor));
}

CParamFactor CParamFactor::operator+(const CParamFactor &rhs) const
{
	CParamFactor ret;
	ret.Reset();

	ret.pfp_ATTACK_PART				= pfp_ATTACK_PART			+ rhs.pfp_ATTACK_PART;
	ret.pfp_DEFENSE_PART			= pfp_DEFENSE_PART			+ rhs.pfp_DEFENSE_PART;
	ret.pfp_FUEL_PART				= pfp_FUEL_PART				+ rhs.pfp_FUEL_PART;
	ret.pfp_SOUL_PART				= pfp_SOUL_PART				+ rhs.pfp_SOUL_PART;
	ret.pfp_SHIELD_PART				= pfp_SHIELD_PART			+ rhs.pfp_SHIELD_PART;
	ret.pfp_DODGE_PART				= pfp_DODGE_PART			+ rhs.pfp_DODGE_PART;
	ret.pfp_BODYCONDITION			= pfp_BODYCONDITION			+ rhs.pfp_BODYCONDITION;
	ret.pfp_ENDURANCE_01 			= pfp_ENDURANCE_01 			+ rhs.pfp_ENDURANCE_01 ;
	ret.pfp_ENDURANCE_02			= pfp_ENDURANCE_02			+ rhs.pfp_ENDURANCE_02;
	ret.pfp_CHARGING_01				= pfp_CHARGING_01			+ rhs.pfp_CHARGING_01;
	ret.pfp_CHARGING_02				= pfp_CHARGING_02			+ rhs.pfp_CHARGING_02;
	ret.pfp_PROPENSITY				= pfp_PROPENSITY			+ rhs.pfp_PROPENSITY;
	ret.pfp_HP						= pfp_HP					+ rhs.pfp_HP;
	ret.pfp_SP						= pfp_SP					+ rhs.pfp_SP;
	ret.pfp_DP						= pfp_DP					+ rhs.pfp_DP;
	ret.pfp_EP						= pfp_EP					+ rhs.pfp_EP;
	ret.pfp_SPRECOVERY				= pfp_SPRECOVERY			+ rhs.pfp_SPRECOVERY;
	ret.pfp_HPRECOVERY				= pfp_HPRECOVERY			+ rhs.pfp_HPRECOVERY;
	ret.pfm_MINATTACK_01			= pfm_MINATTACK_01			+ rhs.pfm_MINATTACK_01;
	ret.pfm_MAXATTACK_01			= pfm_MAXATTACK_01			+ rhs.pfm_MAXATTACK_01;
	ret.pfm_MINATTACK_02			= pfm_MINATTACK_02			+ rhs.pfm_MINATTACK_02;
	ret.pfm_MAXATTACK_02			= pfm_MAXATTACK_02			+ rhs.pfm_MAXATTACK_02;
	ret.pfp_ATTACKPROBABILITY_01	= pfp_ATTACKPROBABILITY_01	+ rhs.pfp_ATTACKPROBABILITY_01;
	ret.pfp_ATTACKPROBABILITY_02	= pfp_ATTACKPROBABILITY_02	+ rhs.pfp_ATTACKPROBABILITY_02;
	ret.pfp_DEFENSE_01				= pfp_DEFENSE_01			+ rhs.pfp_DEFENSE_01;
	ret.pfp_DEFENSE_02				= pfp_DEFENSE_02			+ rhs.pfp_DEFENSE_02;
	ret.pfp_DEFENSEPROBABILITY_01	= pfp_DEFENSEPROBABILITY_01	+ rhs.pfp_DEFENSEPROBABILITY_01;
	ret.pfp_DEFENSEPROBABILITY_02	= pfp_DEFENSEPROBABILITY_02	+ rhs.pfp_DEFENSEPROBABILITY_02;
	ret.pfp_SKILLPROBABILITY		= pfp_SKILLPROBABILITY		+ rhs.pfp_SKILLPROBABILITY;
	ret.pfp_FACTIONRESISTANCE		= pfp_FACTIONRESISTANCE		+ rhs.pfp_FACTIONRESISTANCE;
	ret.pfm_SPEED					= pfm_SPEED					+ rhs.pfm_SPEED;
	ret.pfp_TRANSPORT				= pfp_TRANSPORT				+ rhs.pfp_TRANSPORT;
	ret.pfp_MATERIAL				= pfp_MATERIAL				+ rhs.pfp_MATERIAL;
	ret.pfm_REATTACKTIME_01			= pfm_REATTACKTIME_01		+ rhs.pfm_REATTACKTIME_01;
	ret.pfm_REATTACKTIME_02			= pfm_REATTACKTIME_02		+ rhs.pfm_REATTACKTIME_02;
	ret.pfp_ABRASIONRATE_01			= pfp_ABRASIONRATE_01		+ rhs.pfp_ABRASIONRATE_01;
	ret.pfp_ABRASIONRATE_02			= pfp_ABRASIONRATE_02		+ rhs.pfp_ABRASIONRATE_02;
	ret.pfm_RANGE_01				= pfm_RANGE_01				+ rhs.pfm_RANGE_01;
	ret.pfm_RANGE_02				= pfm_RANGE_02				+ rhs.pfm_RANGE_02;
	ret.pfp_RANGEANGLE_01			= pfp_RANGEANGLE_01			+ rhs.pfp_RANGEANGLE_01;
	ret.pfp_RANGEANGLE_02			= pfp_RANGEANGLE_02			+ rhs.pfp_RANGEANGLE_02;
	ret.pfp_MULTITAGET				= pfp_MULTITAGET			+ rhs.pfp_MULTITAGET;
	ret.pfp_EXPLOSIONRANGE_01		= pfp_EXPLOSIONRANGE_01		+ rhs.pfp_EXPLOSIONRANGE_01;
	ret.pfp_EXPLOSIONRANGE_02		= pfp_EXPLOSIONRANGE_02		+ rhs.pfp_EXPLOSIONRANGE_02;
	ret.pfp_UNIT					= pfp_UNIT					+ rhs.pfp_UNIT;
	ret.pfp_REVISION				= pfp_REVISION				+ rhs.pfp_REVISION;
	ret.pfp_FACTIONPROBABILITY		= pfp_FACTIONPROBABILITY	+ rhs.pfp_FACTIONPROBABILITY;
	ret.pfp_SHOTNUM_01				= pfp_SHOTNUM_01			+ rhs.pfp_SHOTNUM_01;
	ret.pfp_SHOTNUM_02				= pfp_SHOTNUM_02			+ rhs.pfp_SHOTNUM_02;
	ret.pfp_MULTINUM_01				= pfp_MULTINUM_01			+ rhs.pfp_MULTINUM_01;
	ret.pfp_MULTINUM_02				= pfp_MULTINUM_02			+ rhs.pfp_MULTINUM_02;
	ret.pfp_ATTACKTIME_01			= pfp_ATTACKTIME_01			+ rhs.pfp_ATTACKTIME_01;
	ret.pfp_ATTACKTIME_02			= pfp_ATTACKTIME_02			+ rhs.pfp_ATTACKTIME_02;
	ret.pfm_TIME_01					= pfm_TIME_01				+ rhs.pfm_TIME_01;
	ret.pfm_TIME_02					= pfm_TIME_02				+ rhs.pfm_TIME_02;
	ret.pfm_WEIGHT_01				= pfm_WEIGHT_01				+ rhs.pfm_WEIGHT_01;
	ret.pfm_WEIGHT_02				= pfm_WEIGHT_02				+ rhs.pfm_WEIGHT_02;
	ret.pfp_REACTION_RANGE			= pfp_REACTION_RANGE		+ rhs.pfp_REACTION_RANGE;
	ret.pfp_REQ_MIN_LEVEL			= pfp_REQ_MIN_LEVEL			+ rhs.pfp_REQ_MIN_LEVEL;
	ret.pfp_REQ_MAX_LEVEL			= pfp_REQ_MAX_LEVEL			+ rhs.pfp_REQ_MAX_LEVEL;
	ret.pfm_SKILL_REDUCE_SHIELD_DAMAGE	= pfm_SKILL_REDUCE_SHIELD_DAMAGE	+ rhs.pfm_SKILL_REDUCE_SHIELD_DAMAGE;	
	ret.pfm_ATTACK_RANGE_01				= pfm_ATTACK_RANGE_01				+ rhs.pfm_ATTACK_RANGE_01;
	ret.pfm_ATTACK_RANGE_02				= pfm_ATTACK_RANGE_02				+ rhs.pfm_ATTACK_RANGE_02;
// 2005-12-02 by cmkwon, 주석처리	ret.pfm_SKILL_HYPERMOVING			= pfm_SKILL_HYPERMOVING				+ rhs.pfm_SKILL_HYPERMOVING;
	ret.pfm_SKILL_COLLISIONDAMAGE_DOWN	= pfm_SKILL_COLLISIONDAMAGE_DOWN	+ rhs.pfm_SKILL_COLLISIONDAMAGE_DOWN;
	ret.pfm_SKILL_SMARTSP				= pfm_SKILL_SMARTSP					+ rhs.pfm_SKILL_SMARTSP;
	ret.pfm_SKILL_REACTIONSPEED			= pfm_SKILL_REACTIONSPEED			+ rhs.pfm_SKILL_REACTIONSPEED;
	ret.pfm_SKILL_ENGINEANGLE			= pfm_SKILL_ENGINEANGLE				+ rhs.pfm_SKILL_ENGINEANGLE;
	ret.pfm_SKILL_ENGINEBOOSTERANGLE	= pfm_SKILL_ENGINEBOOSTERANGLE		+ rhs.pfm_SKILL_ENGINEBOOSTERANGLE;
	ret.pfm_DROP_EXP					= pfm_DROP_EXP						+ rhs.pfm_DROP_EXP;
	ret.pfm_DROP_SPI					= pfm_DROP_SPI						+ rhs.pfm_DROP_SPI;
	ret.pfm_DROP_ITEM					= pfm_DROP_ITEM						+ rhs.pfm_DROP_ITEM;
	ret.pfm_DROP_RAREITEM				= pfm_DROP_RAREITEM					+ rhs.pfm_DROP_RAREITEM;	// 238,2010-11-30 by shcho, 레어아이템 드랍 확률 증가 아이템 구현
	ret.pfm_HP_REPAIR_RATE_FLIGHTING	= pfm_HP_REPAIR_RATE_FLIGHTING		+ rhs.pfm_HP_REPAIR_RATE_FLIGHTING;
	ret.pfm_DP_REPAIR_RATE				= pfm_DP_REPAIR_RATE				+ rhs.pfm_DP_REPAIR_RATE;
	ret.pfm_SP_REPAIR_RATE				= pfm_SP_REPAIR_RATE				+ rhs.pfm_SP_REPAIR_RATE;

	ret.pfm_WARHEAD_SPEED				= pfm_WARHEAD_SPEED					+ rhs.pfm_WARHEAD_SPEED;		// 176, 2007-06-11 by cmkwon, 탄두의 속도
	
	// 2008-09-22 by dhjin, 신규 인첸트
	ret.pfn_ENGINE_BOOSTER_TIME_UP		= pfn_ENGINE_BOOSTER_TIME_UP		+ rhs.pfn_ENGINE_BOOSTER_TIME_UP;		// 178, // 2008-09-22 by dhjin, 부스터 시간 증가
	ret.pfn_ENGINE_MAX_SPEED_UP			= pfn_ENGINE_MAX_SPEED_UP			+ rhs.pfn_ENGINE_MAX_SPEED_UP;			// 179,	// 2008-09-22 by dhjin, 엔진 일반속도(최대) 증가
	ret.pfn_ENGINE_MIN_SPEED_UP			= pfn_ENGINE_MIN_SPEED_UP			+ rhs.pfn_ENGINE_MIN_SPEED_UP;			// 180,	// 2008-09-22 by dhjin, 엔진 일반속도(최소) 증가
	ret.pfn_ENGINE_BOOSTER_SPEED_UP		= pfn_ENGINE_BOOSTER_SPEED_UP		+ rhs.pfn_ENGINE_BOOSTER_SPEED_UP;		// 181,	// 2008-09-22 by dhjin, 엔진 부스터속도 증가
	ret.pfn_ENGINE_GROUND_SPEED_UP		= pfn_ENGINE_GROUND_SPEED_UP		+ rhs.pfn_ENGINE_GROUND_SPEED_UP;		// 182,	// 2008-09-22 by dhjin, 엔진 지상속도 증가
	ret.pfn_RADAR_OBJECT_DETECT_RANGE	= pfn_RADAR_OBJECT_DETECT_RANGE		+ rhs.pfn_RADAR_OBJECT_DETECT_RANGE;	// 183, // 2008-09-22 by dhjin, 레이더 물체 감지 반경
	ret.pfm_PIERCE_UP_01				= pfm_PIERCE_UP_01					+ rhs.pfm_PIERCE_UP_01;					// 184, // 2008-09-22 by dhjin, 기본무기 피어스율 증가 카드
	ret.pfm_PIERCE_UP_02				= pfm_PIERCE_UP_02					+ rhs.pfm_PIERCE_UP_02;					// 185, // 2008-09-22 by dhjin, 고급무기 피어스율 증가 카드
	ret.pfm_ENGINE_ANGLE_UP				= pfm_ENGINE_ANGLE_UP				+ rhs.pfm_ENGINE_ANGLE_UP;				// 186,	// 2008-09-30 by dhjin, 엔진 회전각 증가 카드
	ret.pfm_ENGINE_BOOSTERANGLE_UP		= pfm_ENGINE_BOOSTERANGLE_UP		+ rhs.pfm_ENGINE_BOOSTERANGLE_UP;		// 187,	// 2008-09-30 by dhjin, 엔진 부스터 회전각 증가 카드
	
	ret.pf_ITEM_Resistance				= pf_ITEM_Resistance				+ rhs.pf_ITEM_Resistance;				// 201, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 저항 아이템 사용 체크 
	ret.pf_ITEM_AddAttack				= pf_ITEM_AddAttack					+ rhs.pf_ITEM_AddAttack;				// 202, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 사용 체크 
	ret.pf_ITEM_ReduceDamage			= pf_ITEM_ReduceDamage				+ rhs.pf_ITEM_ReduceDamage;				// 205, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 데미지 절대값 감소 아이템 사용 체크
	ret.pf_ITEM_AddAttack_Sec			= pf_ITEM_AddAttack_Sec				+ rhs.pf_ITEM_AddAttack_Sec;			// 206, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 고급무기용(기무와 분류)
	ret.pf_ITEM_OnceResistance			= pf_ITEM_OnceResistance			+ rhs.pf_ITEM_OnceResistance;			// 207, // 2009-09-09 ~ 2010-01-19 by dhjin, 인피니티 - 한 번만 저항하고 없어지는 저항 아이템 추가
	ret.pfm_PLUS_WARPOINT_RATE			= pfm_PLUS_WARPOINT_RATE			+ rhs.pfm_PLUS_WARPOINT_RATE;			// 234, // 2010-05-18 by cmkwon, WarPoint 증가 아이템 구현(일본요청) - 
	
	ret.pf_ITEMS_MOVE_SPEED_RATE		= pf_ITEMS_MOVE_SPEED_RATE			+ rhs.pf_ITEMS_MOVE_SPEED_RATE;			// 239, // 2010-12-21 by jskim, 마을 이동 속도 증가 아이템 구현

	return ret;
}

CParamFactor& CParamFactor::operator+=(const CParamFactor &rhs)
{
	*this = *this + rhs;
	return *this;
}

CParamFactor CParamFactor::operator-(const CParamFactor &rhs) const
{
	CParamFactor ret;
	ret.Reset();

	ret.pfp_ATTACK_PART				= pfp_ATTACK_PART			- rhs.pfp_ATTACK_PART;
	ret.pfp_DEFENSE_PART			= pfp_DEFENSE_PART			- rhs.pfp_DEFENSE_PART;
	ret.pfp_FUEL_PART				= pfp_FUEL_PART				- rhs.pfp_FUEL_PART;
	ret.pfp_SOUL_PART				= pfp_SOUL_PART				- rhs.pfp_SOUL_PART;
	ret.pfp_SHIELD_PART				= pfp_SHIELD_PART			- rhs.pfp_SHIELD_PART;
	ret.pfp_DODGE_PART				= pfp_DODGE_PART				- rhs.pfp_DODGE_PART;
	ret.pfp_BODYCONDITION			= pfp_BODYCONDITION			- rhs.pfp_BODYCONDITION;
	ret.pfp_ENDURANCE_01 			= pfp_ENDURANCE_01 			- rhs.pfp_ENDURANCE_01 ;
	ret.pfp_ENDURANCE_02			= pfp_ENDURANCE_02			- rhs.pfp_ENDURANCE_02;
	ret.pfp_CHARGING_01				= pfp_CHARGING_01			- rhs.pfp_CHARGING_01;
	ret.pfp_CHARGING_02				= pfp_CHARGING_02			- rhs.pfp_CHARGING_02;
	ret.pfp_PROPENSITY				= pfp_PROPENSITY			- rhs.pfp_PROPENSITY;
	ret.pfp_HP						= pfp_HP					- rhs.pfp_HP;
	ret.pfp_SP						= pfp_SP					- rhs.pfp_SP;
	ret.pfp_DP						= pfp_DP					- rhs.pfp_DP;
	ret.pfp_EP						= pfp_EP					- rhs.pfp_EP;
	ret.pfp_SPRECOVERY				= pfp_SPRECOVERY			- rhs.pfp_SPRECOVERY;
	ret.pfp_HPRECOVERY				= pfp_HPRECOVERY			- rhs.pfp_HPRECOVERY;
	ret.pfm_MINATTACK_01			= pfm_MINATTACK_01			- rhs.pfm_MINATTACK_01;
	ret.pfm_MAXATTACK_01			= pfm_MAXATTACK_01			- rhs.pfm_MAXATTACK_01;
	ret.pfm_MINATTACK_02			= pfm_MINATTACK_02			- rhs.pfm_MINATTACK_02;
	ret.pfm_MAXATTACK_02			= pfm_MAXATTACK_02			- rhs.pfm_MAXATTACK_02;
	ret.pfp_ATTACKPROBABILITY_01	= pfp_ATTACKPROBABILITY_01	- rhs.pfp_ATTACKPROBABILITY_01;
	ret.pfp_ATTACKPROBABILITY_02	= pfp_ATTACKPROBABILITY_02	- rhs.pfp_ATTACKPROBABILITY_02;
	ret.pfp_DEFENSE_01				= pfp_DEFENSE_01			- rhs.pfp_DEFENSE_01;
	ret.pfp_DEFENSE_02				= pfp_DEFENSE_02			- rhs.pfp_DEFENSE_02;
	ret.pfp_DEFENSEPROBABILITY_01	= pfp_DEFENSEPROBABILITY_01	- rhs.pfp_DEFENSEPROBABILITY_01;
	ret.pfp_DEFENSEPROBABILITY_02	= pfp_DEFENSEPROBABILITY_02	- rhs.pfp_DEFENSEPROBABILITY_02;
	ret.pfp_SKILLPROBABILITY		= pfp_SKILLPROBABILITY		- rhs.pfp_SKILLPROBABILITY;
	ret.pfp_FACTIONRESISTANCE		= pfp_FACTIONRESISTANCE		- rhs.pfp_FACTIONRESISTANCE;
	ret.pfm_SPEED					= pfm_SPEED					- rhs.pfm_SPEED;
	ret.pfp_TRANSPORT				= pfp_TRANSPORT				- rhs.pfp_TRANSPORT;
	ret.pfp_MATERIAL				= pfp_MATERIAL				- rhs.pfp_MATERIAL;
	ret.pfm_REATTACKTIME_01			= pfm_REATTACKTIME_01		- rhs.pfm_REATTACKTIME_01;
	ret.pfm_REATTACKTIME_02			= pfm_REATTACKTIME_02		- rhs.pfm_REATTACKTIME_02;
	ret.pfp_ABRASIONRATE_01			= pfp_ABRASIONRATE_01		- rhs.pfp_ABRASIONRATE_01;
	ret.pfp_ABRASIONRATE_02			= pfp_ABRASIONRATE_02		- rhs.pfp_ABRASIONRATE_02;
	ret.pfm_RANGE_01				= pfm_RANGE_01				- rhs.pfm_RANGE_01;
	ret.pfm_RANGE_02				= pfm_RANGE_02				- rhs.pfm_RANGE_02;
	ret.pfp_RANGEANGLE_01			= pfp_RANGEANGLE_01			- rhs.pfp_RANGEANGLE_01;
	ret.pfp_RANGEANGLE_02			= pfp_RANGEANGLE_02			- rhs.pfp_RANGEANGLE_02;
	ret.pfp_MULTITAGET				= pfp_MULTITAGET			- rhs.pfp_MULTITAGET;
	ret.pfp_EXPLOSIONRANGE_01		= pfp_EXPLOSIONRANGE_01		- rhs.pfp_EXPLOSIONRANGE_01;
	ret.pfp_EXPLOSIONRANGE_02		= pfp_EXPLOSIONRANGE_02		- rhs.pfp_EXPLOSIONRANGE_02;
	ret.pfp_UNIT					= pfp_UNIT					- rhs.pfp_UNIT;
	ret.pfp_REVISION				= pfp_REVISION				- rhs.pfp_REVISION;
	ret.pfp_FACTIONPROBABILITY		= pfp_FACTIONPROBABILITY	- rhs.pfp_FACTIONPROBABILITY;
	ret.pfp_SHOTNUM_01				= pfp_SHOTNUM_01			- rhs.pfp_SHOTNUM_01;
	ret.pfp_SHOTNUM_02				= pfp_SHOTNUM_02			- rhs.pfp_SHOTNUM_02;
	ret.pfp_MULTINUM_01				= pfp_MULTINUM_01			- rhs.pfp_MULTINUM_01;
	ret.pfp_MULTINUM_02				= pfp_MULTINUM_02			- rhs.pfp_MULTINUM_02;
	ret.pfp_ATTACKTIME_01			= pfp_ATTACKTIME_01			- rhs.pfp_ATTACKTIME_01;
	ret.pfp_ATTACKTIME_02			= pfp_ATTACKTIME_02			- rhs.pfp_ATTACKTIME_02;
	ret.pfm_TIME_01					= pfm_TIME_01				- rhs.pfm_TIME_01;
	ret.pfm_TIME_02					= pfm_TIME_02				- rhs.pfm_TIME_02;
	ret.pfm_WEIGHT_01				= pfm_WEIGHT_01				- rhs.pfm_WEIGHT_01;
	ret.pfm_WEIGHT_02				= pfm_WEIGHT_02				- rhs.pfm_WEIGHT_02;
	ret.pfp_REACTION_RANGE			= pfp_REACTION_RANGE		- rhs.pfp_REACTION_RANGE;
	ret.pfp_REQ_MIN_LEVEL			= pfp_REQ_MIN_LEVEL			- rhs.pfp_REQ_MIN_LEVEL;
	ret.pfp_REQ_MAX_LEVEL			= pfp_REQ_MAX_LEVEL			- rhs.pfp_REQ_MAX_LEVEL;
	ret.pfm_SKILL_REDUCE_SHIELD_DAMAGE	= pfm_SKILL_REDUCE_SHIELD_DAMAGE	- rhs.pfm_SKILL_REDUCE_SHIELD_DAMAGE;	
	ret.pfm_ATTACK_RANGE_01				= pfm_ATTACK_RANGE_01				- rhs.pfm_ATTACK_RANGE_01;
	ret.pfm_ATTACK_RANGE_02				= pfm_ATTACK_RANGE_02				- rhs.pfm_ATTACK_RANGE_02;
// 2005-12-02 by cmkwon,	ret.pfm_SKILL_HYPERMOVING			= pfm_SKILL_HYPERMOVING				- rhs.pfm_SKILL_HYPERMOVING;
	ret.pfm_SKILL_COLLISIONDAMAGE_DOWN	= pfm_SKILL_COLLISIONDAMAGE_DOWN	- rhs.pfm_SKILL_COLLISIONDAMAGE_DOWN;
	ret.pfm_SKILL_SMARTSP				= pfm_SKILL_SMARTSP					- rhs.pfm_SKILL_SMARTSP;
	ret.pfm_SKILL_REACTIONSPEED			= pfm_SKILL_REACTIONSPEED			- rhs.pfm_SKILL_REACTIONSPEED;
	ret.pfm_SKILL_ENGINEANGLE			= pfm_SKILL_ENGINEANGLE				- rhs.pfm_SKILL_ENGINEANGLE;
	ret.pfm_SKILL_ENGINEBOOSTERANGLE	= pfm_SKILL_ENGINEBOOSTERANGLE		- rhs.pfm_SKILL_ENGINEBOOSTERANGLE;
	ret.pfm_DROP_EXP					= pfm_DROP_EXP						- rhs.pfm_DROP_EXP;
	ret.pfm_DROP_SPI					= pfm_DROP_SPI						- rhs.pfm_DROP_SPI;
	ret.pfm_DROP_ITEM					= pfm_DROP_ITEM						- rhs.pfm_DROP_ITEM;	// 238,2010-11-30 by shcho, 레어아이템 드랍 확률 증가 아이템 구현
	ret.pfm_DROP_RAREITEM				= pfm_DROP_RAREITEM					- rhs.pfm_DROP_RAREITEM;
	ret.pfm_HP_REPAIR_RATE_FLIGHTING	= pfm_HP_REPAIR_RATE_FLIGHTING		- rhs.pfm_HP_REPAIR_RATE_FLIGHTING;
	ret.pfm_DP_REPAIR_RATE				= pfm_DP_REPAIR_RATE				- rhs.pfm_DP_REPAIR_RATE;
	ret.pfm_SP_REPAIR_RATE				= pfm_SP_REPAIR_RATE				- rhs.pfm_SP_REPAIR_RATE;

	ret.pfm_WARHEAD_SPEED				= pfm_WARHEAD_SPEED					- rhs.pfm_WARHEAD_SPEED;	// 176, 2007-06-11 by cmkwon, 탄두의 속도

	// 2008-09-22 by dhjin, 신규 인첸트
	ret.pfn_ENGINE_BOOSTER_TIME_UP		= pfn_ENGINE_BOOSTER_TIME_UP		- rhs.pfn_ENGINE_BOOSTER_TIME_UP;		// 178, // 2008-09-22 by dhjin, 부스터 시간 증가
	ret.pfn_ENGINE_MAX_SPEED_UP			= pfn_ENGINE_MAX_SPEED_UP			- rhs.pfn_ENGINE_MAX_SPEED_UP;			// 179,	// 2008-09-22 by dhjin, 엔진 일반속도(최대) 증가
	ret.pfn_ENGINE_MIN_SPEED_UP			= pfn_ENGINE_MIN_SPEED_UP			- rhs.pfn_ENGINE_MIN_SPEED_UP;			// 180,	// 2008-09-22 by dhjin, 엔진 일반속도(최소) 증가
	ret.pfn_ENGINE_BOOSTER_SPEED_UP		= pfn_ENGINE_BOOSTER_SPEED_UP		- rhs.pfn_ENGINE_BOOSTER_SPEED_UP;		// 181,	// 2008-09-22 by dhjin, 엔진 부스터속도 증가
	ret.pfn_ENGINE_GROUND_SPEED_UP		= pfn_ENGINE_GROUND_SPEED_UP		- rhs.pfn_ENGINE_GROUND_SPEED_UP;		// 182,	// 2008-09-22 by dhjin, 엔진 지상속도 증가
	ret.pfn_RADAR_OBJECT_DETECT_RANGE	= pfn_RADAR_OBJECT_DETECT_RANGE		- rhs.pfn_RADAR_OBJECT_DETECT_RANGE;	// 183, // 2008-09-22 by dhjin, 레이더 물체 감지 반경
	ret.pfm_PIERCE_UP_01				= pfm_PIERCE_UP_01					- rhs.pfm_PIERCE_UP_01;					// 184, // 2008-09-22 by dhjin, 기본무기 피어스율 증가 카드
	ret.pfm_PIERCE_UP_02				= pfm_PIERCE_UP_02					- rhs.pfm_PIERCE_UP_02;					// 185, // 2008-09-22 by dhjin, 고급무기 피어스율 증가 카드
	ret.pfm_ENGINE_ANGLE_UP				= pfm_ENGINE_ANGLE_UP				- rhs.pfm_ENGINE_ANGLE_UP;				// 186,	// 2008-09-30 by dhjin, 엔진 회전각 증가 카드
	ret.pfm_ENGINE_BOOSTERANGLE_UP		= pfm_ENGINE_BOOSTERANGLE_UP		- rhs.pfm_ENGINE_BOOSTERANGLE_UP;		// 187,	// 2008-09-30 by dhjin, 엔진 부스터 회전각 증가 카드	

	ret.pf_ITEM_Resistance				= pf_ITEM_Resistance				- rhs.pf_ITEM_Resistance;				// 201, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 저항 아이템 사용 체크 
	ret.pf_ITEM_AddAttack				= pf_ITEM_AddAttack					- rhs.pf_ITEM_AddAttack;				// 202, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 사용 체크 
	ret.pf_ITEM_ReduceDamage			= pf_ITEM_ReduceDamage				- rhs.pf_ITEM_ReduceDamage;				// 205, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 데미지 절대값 감소 아이템 사용 체크
	ret.pf_ITEM_AddAttack_Sec			= pf_ITEM_AddAttack_Sec				- rhs.pf_ITEM_AddAttack_Sec;			// 206, // 2009-09-09 ~ 2010 by dhjin, 인피니티 - 절대값 타격치 아이템 고급무기용(기무와 분류)
	ret.pf_ITEM_OnceResistance			= pf_ITEM_OnceResistance			- rhs.pf_ITEM_OnceResistance;			// 207, // 2009-09-09 ~ 2010-01-19 by dhjin, 인피니티 - 한 번만 저항하고 없어지는 저항 아이템 추가
	ret.pfm_PLUS_WARPOINT_RATE			= pfm_PLUS_WARPOINT_RATE			- rhs.pfm_PLUS_WARPOINT_RATE;			// 2010-05-18 by cmkwon, WarPoint 증가 아이템 구현(일본요청) - 

	ret.pf_ITEMS_MOVE_SPEED_RATE		= pf_ITEMS_MOVE_SPEED_RATE			+ rhs.pf_ITEMS_MOVE_SPEED_RATE;			// 239, // 2010-12-21 by jskim, 마을 이동 속도 증가 아이템 구현

	return ret;
}

CParamFactor& CParamFactor::operator-=(const CParamFactor &rhs)
{
	*this = *this - rhs;
	return *this;
}

void CParamFactor::Print(BOOL i_bDbgOutOrMsg, void *i_pSocket /* = NULL */, BOOL i_bOnlyValidParam /* = TRUE */)
{
}

//LEVEL_STAT_VALUE g_arrLevelStatValue[MAX_LEVEL_OR_STAT_VALUE+1];

vectorMAP_INFO					g_vectorALL_MAP_INFO;

#ifdef _ATUM_SERVER
// 각종 수치 데이터 로딩
BOOL CAtumSJ::LoadData(CODBCStatement *i_pOdbcStmt, CLocalization *i_pLocalization)
{
	BOOL bRet = TRUE;

	// LoadAllProject에 선행해야 함!
	CAtumDBHelper::LoadMapInfo(i_pOdbcStmt, &g_vectorALL_MAP_INFO, i_pLocalization);
	return TRUE;
}

vectorMAP_INFO *CAtumSJ::GetVectPtrALL_MAP_INFO(void)
{
	return &g_vectorALL_MAP_INFO;
}
#endif // _ATUM_SERVER

const MAP_INFO* CAtumSJ::GetMapInfo(MapIndex_t i_nMapIndex)
{
	for(int i=0; i < g_vectorALL_MAP_INFO.size(); i++)
	{
		if(i_nMapIndex == g_vectorALL_MAP_INFO[i].MapIndex)
		{
			return &g_vectorALL_MAP_INFO[i];
		}
	}

	return NULL;
}

const char* CAtumSJ::GetMapName(MapIndex_t i_nMapIndex)
{
	const MAP_INFO *pMapInfo = CAtumSJ::GetMapInfo(i_nMapIndex);
	if (pMapInfo != NULL)
	{
		return pMapInfo->MapName;
	}

	return STRCMD_CS_COMMON_MAPNAME_UNKNOWN;
}

USHORT CAtumSJ::GetTransport(CHARACTER* pCharacter)
{
// 2005-09-27 by cmkwon, 무게게이즈는 장착된 아이템만 적용하도록 수정함 - 최대무게량에 레벨당 추가량을 삭제한다.
//	return (pCharacter->TotalGearStat.FuelPart * 60 + pCharacter->Level * 40 + 300);
	// 2007-05-16 by cmkwon, 300초과로 갑을 가지고 있고 적용시 최대 300이 되도록 수정
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return (min(COUNT_MAX_STAT_POINT,pCharacter->TotalGearStat.FuelPart) * 60 + 300);
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(pCharacter->Level);
	return (min(nMaxStatValue, pCharacter->TotalGearStat.FuelPart) * 60 + 300);
}

float CAtumSJ::GetSpeed(CHARACTER *pCharacter, ITEM *pItem)
{
	ASSERT_NOT_IMPLEMENTED_YET();

	return 0;
}

// 2006-10-13 by cmkwon, 리턴값 자료형 변경(float-->int)
// 2007-11-02 by cmkwon, 중량 구하는 시스템 변경 - 리턴값 자료형 변경(<--int)
float CAtumSJ::GetItemWeight(ITEM *i_pItem, int i_nCountableItemCount
							 , float i_fDesWeight/*=0.0f*/)		// 2006-01-24 by cmkwon, 중량 인챈트 수치 인자 추가
{
	float retTotalWeight = 0.0f;

	if (IS_COUNTABLE_ITEM(i_pItem->Kind))
	{
		retTotalWeight += ((float)i_nCountableItemCount) / (float)i_pItem->MinTradeQuantity * ((float)i_pItem->Weight*(1.0f + i_fDesWeight));
	}
	else
	{
		retTotalWeight += ((float)i_pItem->Weight*(1.0f + i_fDesWeight));
	}

	return retTotalWeight;

// 2007-11-02 by cmkwon, 중량 구하는 시스템 변경 - 리턴값 자료형 변경(<--int), 위와 같이 수정
//	int retTotalWeight = 0;
//
//	if (IS_COUNTABLE_ITEM(i_pItem->Kind))
//	{
//		retTotalWeight += ((float)i_nCountableItemCount) / i_pItem->MinTradeQuantity * (i_pItem->Weight*(1.0f + i_fDesWeight));
//	}
//	else
//	{
//		retTotalWeight += (i_pItem->Weight*(1.0f + i_fDesWeight));
//	}
//
//	return retTotalWeight;
}

const STATUS_NAME g_arrCharacterStatus[] =
{
	{STATUS_BEGINNER_AIRMAN,		"Beginner Airman",		STRCMD_CS_STATUS_BEGINNER_AIRMAN},
	{STATUS_3RD_CLASS_AIRMAN,		"3rd Class Airman",		STRCMD_CS_STATUS_3RD_CLASS_AIRMAN},
	{STATUS_2ND_CLASS_AIRMAN,		"2nd Class Airman",		STRCMD_CS_STATUS_2ND_CLASS_AIRMAN},
	{STATUS_1ST_CLASS_AIRMAN,		"1st Class Airman",		STRCMD_CS_STATUS_1ST_CLASS_AIRMAN},
	{STATUS_3RD_CLASS_WINGMAN,		"3rd Class Wingman",	STRCMD_CS_STATUS_3RD_CLASS_WINGMAN},
	{STATUS_2ND_CLASS_WINGMAN,		"2nd Class Wingman",	STRCMD_CS_STATUS_2ND_CLASS_WINGMAN},
	{STATUS_1ST_CLASS_WINGMAN,		"1st Class Wingman",	STRCMD_CS_STATUS_1ST_CLASS_WINGMAN},
	{STATUS_3RD_CLASS_LEADER,		"3rd Class Leader",		STRCMD_CS_STATUS_3RD_CLASS_LEADER},
	{STATUS_2ND_CLASS_LEADER,		"2nd Class Leader",		STRCMD_CS_STATUS_2ND_CLASS_LEADER},
	{STATUS_1ST_CLASS_LEADER,		"1st Class Leader",		STRCMD_CS_STATUS_1ST_CLASS_LEADER},
	{STATUS_3RD_CLASS_ACE,			"3rd Class Ace",		STRCMD_CS_STATUS_3RD_CLASS_ACE},
	{STATUS_2ND_CLASS_ACE,			"2nd Class Ace",		STRCMD_CS_STATUS_2ND_CLASS_ACE},
	{STATUS_1ST_CLASS_ACE,			"1st Class Ace",		STRCMD_CS_STATUS_1ST_CLASS_ACE},
	{STATUS_COPPER_CLASS_GENERAL,	"Copper Class General",	STRCMD_CS_STATUS_COPPER_CLASS_GENERAL},
	{STATUS_SILVER_CLASS_GENERAL,	"Silver Class General",	STRCMD_CS_STATUS_SILVER_CLASS_GENERAL},
	{STATUS_GOLD_CLASS_GENERAL,		"Gold Class General",	STRCMD_CS_STATUS_GOLD_CLASS_GENERAL},
	{STATUS_MASTER_GENERAL,			"Master General",		STRCMD_CS_STATUS_MASTER_GENERAL}
};

BYTE CAtumSJ::GetStatusByPropensity(INT i_nPropensity)
{
	if (i_nPropensity <= 100) return STATUS_BEGINNER_AIRMAN;
	else if (IS_IN_RANGE(101, i_nPropensity, 300))		return STATUS_3RD_CLASS_AIRMAN;
	else if (IS_IN_RANGE(301, i_nPropensity, 600))		return STATUS_2ND_CLASS_AIRMAN;
	else if (IS_IN_RANGE(601, i_nPropensity, 1000))		return STATUS_1ST_CLASS_AIRMAN;
	else if (IS_IN_RANGE(1001, i_nPropensity, 1500))	return STATUS_3RD_CLASS_WINGMAN;
	else if (IS_IN_RANGE(1501, i_nPropensity, 2000))	return STATUS_2ND_CLASS_WINGMAN;
	else if (IS_IN_RANGE(2001, i_nPropensity, 2500))	return STATUS_1ST_CLASS_WINGMAN;
	else if (IS_IN_RANGE(2501, i_nPropensity, 5000))	return STATUS_3RD_CLASS_LEADER;
	else if (IS_IN_RANGE(5001, i_nPropensity, 1000))	return STATUS_2ND_CLASS_LEADER;
	else if (IS_IN_RANGE(10001, i_nPropensity, 15000))	return STATUS_1ST_CLASS_LEADER;
	else if (IS_IN_RANGE(15001, i_nPropensity, 20000))	return STATUS_3RD_CLASS_ACE;
	else if (IS_IN_RANGE(20001, i_nPropensity, 25000))	return STATUS_2ND_CLASS_ACE;

	// 2005-12-27 by cmkwon, 25001 ~
	return STATUS_1ST_CLASS_ACE;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			char *  CAtumSJ::GetStatusByLevel(BYTE i_byLevel)
/// \brief		EP3 유저정보옵션 -
/// \author		dhjin
/// \date		2008-06-24 ~ 2008-06-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char * CAtumSJ::GetStatusByLevel(BYTE i_byLevel)
{
	if (IS_IN_RANGE(12, i_byLevel, 21))			return STRCMD_CS_CHARACTER_12_LEVEL_RANK;
	else if (IS_IN_RANGE(22, i_byLevel, 31))	return STRCMD_CS_CHARACTER_22_LEVEL_RANK;
	else if (IS_IN_RANGE(32, i_byLevel, 41))	return STRCMD_CS_CHARACTER_32_LEVEL_RANK;
	else if (IS_IN_RANGE(42, i_byLevel, 51))	return STRCMD_CS_CHARACTER_42_LEVEL_RANK;
	else if (IS_IN_RANGE(52, i_byLevel, 61))	return STRCMD_CS_CHARACTER_52_LEVEL_RANK;
	else if (IS_IN_RANGE(62, i_byLevel, 71))	return STRCMD_CS_CHARACTER_62_LEVEL_RANK;
	else if (IS_IN_RANGE(72, i_byLevel, 81))	return STRCMD_CS_CHARACTER_72_LEVEL_RANK;
	else if (IS_IN_RANGE(82, i_byLevel, 91))	return STRCMD_CS_CHARACTER_82_LEVEL_RANK;
// 2010-01-08 by cmkwon, 최대 레벨 상향에 따른 추가 사항(레벨별 계급) - 아래와 같이 수정 및 추가
//	else if (IS_IN_RANGE(92, i_byLevel, 100))	return STRCMD_CS_CHARACTER_92_LEVEL_RANK;
	else if (IS_IN_RANGE(92, i_byLevel, 95))	return STRCMD_CS_CHARACTER_92_LEVEL_RANK;
	else if (IS_IN_RANGE(96, i_byLevel, 99))	return STRCMD_CS_CHARACTER_96_LEVEL_RANK;
	else if (IS_IN_RANGE(100, i_byLevel, 103))	return STRCMD_CS_CHARACTER_100_LEVEL_RANK;
	else if (IS_IN_RANGE(104, i_byLevel, 107))	return STRCMD_CS_CHARACTER_104_LEVEL_RANK;
	else if (IS_IN_RANGE(108, i_byLevel, 111))	return STRCMD_CS_CHARACTER_108_LEVEL_RANK;
	else if (IS_IN_RANGE(112, i_byLevel, 115))	return STRCMD_CS_CHARACTER_112_LEVEL_RANK;
	else if (IS_IN_RANGE(116, i_byLevel, 125))	return STRCMD_CS_CHARACTER_116_LEVEL_RANK;


	// 2010-01-08 by cmkwon, 최대 레벨 상향에 따른 추가 사항(레벨별 계급) - 아래와 같이 수정
	//return FALSE;
	return STRCMD_CS_CHARACTER_XX_LEVEL_RANK;
}

const char* CAtumSJ::GetStatusNameKO(BYTE i_nStatus)
{
	if (!IS_IN_RANGE(STATUS_BEGINNER_AIRMAN, i_nStatus , STATUS_MASTER_GENERAL))
	{
		return FALSE;
	}

	return g_arrCharacterStatus[i_nStatus].StatusNameKO;
}

const char* CAtumSJ::GetStatusNameEN(BYTE i_nStatus)
{
	if (!IS_IN_RANGE(STATUS_BEGINNER_AIRMAN, i_nStatus , STATUS_MASTER_GENERAL))
	{
		return FALSE;
	}

	return g_arrCharacterStatus[i_nStatus].StatusNameEN;
}

BOOL CAtumSJ::CheckTargetErrorAngle(CHARACTER *i_pAttackCharacter,
									D3DXVECTOR3 &i_ServerAttackPosition,
									D3DXVECTOR3 &i_ServerTargetPosition,
									D3DXVECTOR3 &i_ClientTargetPosition,
									float &o_fServerDistance)
{
	D3DXVECTOR3 vFrontVel, vExpectPos;

	o_fServerDistance = D3DXVec3Length(&(i_ServerAttackPosition - i_ServerTargetPosition));

	// 타켓의 오차 각
	D3DXVec3Normalize(&vFrontVel, &(i_ClientTargetPosition - i_ServerAttackPosition));
	vExpectPos = i_ServerAttackPosition + (vFrontVel * o_fServerDistance);
	float fErrorDistance = D3DXVec3Length(&(vExpectPos - i_ServerTargetPosition));

	// A-GEAR인 경우는 검사 안 함
	if (i_pAttackCharacter != NULL && IS_AGEAR(i_pAttackCharacter->UnitKind))
	{
		return TRUE;
	}

	if (IS_IN_RANGE(0.0f, fErrorDistance, DAMAGE_KIND_ANGLE_DISTANCE))
	{
		return TRUE;
	}

	return FALSE;
}

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
float CAtumSJ::GetAttackProbabilityC(ITEM *pItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack, Stat_t i_nAttackPart, BYTE i_byLevel)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	return pItem->HitRate
			+ (bIsPrimaryAttack?pParamFactor->pfp_ATTACKPROBABILITY_01:pParamFactor->pfp_ATTACKPROBABILITY_02)
			+ CAtumSJ::GetAttackC_IncreaseProbability(i_nAttackPart, i_byLevel);
}

float CAtumSJ::GetDefenseProbabilityC(CHARACTER *pCharacter, ITEM *pDefenseItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
{// 2008-11-13 by dhjin, 클라이언트만 계산식 변경으로 차후 함수 수정시 반드시 논의 되어야 함!!

	// 2010-07-19 by dhjin, 확률 수식 변경
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
//	return (GetDefenseProbabilityC_Rate(pCharacter->TotalGearStat.DodgePart, pCharacter->Level)) * PROB256_MAX_VALUE // check: 추후에 방어 아이템(1/2형 구분 지어야 함)이 추가되면, RAND(DefenseItem.AbilityMin ~ DefenseItem.AbilityMax)로 결정
//			+ (bIsPrimaryAttack?pParamFactor->pfp_DEFENSEPROBABILITY_01:pParamFactor->pfp_DEFENSEPROBABILITY_02);
	return (GetDefenseProbabilityC_Rate(pCharacter->TotalGearStat.DodgePart, pCharacter->Level)) * PROB100_MAX_VALUE + (bIsPrimaryAttack?pParamFactor->pfp_DEFENSEPROBABILITY_01:pParamFactor->pfp_DEFENSEPROBABILITY_02);
}


/*************************************************************************************************************************************************************************************
**
**	몬스터의 공격 확률
**
**	Create Info :	??.??.??
**
**	Update Info :	// 2010. 06. 14 by hsLee 인피니티 필드 2차 난이도 조절. (몬스터 공격력 추가 수정, Pierce확률과 적중률 적용. ) - 몬스터 밸런스 관련 인자 추가, 인자의 const 화.
**
**					   (const MONSTER_INFO_EXTEND a_pMonInfoExtend = NULL)
**
**************************************************************************************************************************************************************************************/
//float CAtumSJ::GetAttackProbabilityM(MONSTER_INFO *pMonsterInfo, ITEM *pItem)
float CAtumSJ::GetAttackProbabilityM ( const MONSTER_INFO *a_pMonsterInfo, const ITEM *a_pItem , const MONSTER_INFO_EXTEND *a_pMonInfoExtend /*= NULL*/ )
{
	
	// 2010. 06. 14 by hsLee 인피니티 필드 2차 난이도 조절. (몬스터 공격력 추가 수정, Pierce확률과 적중률 적용. )
	// 2010-07-19 by dhjin, 확률 수식 변경
//	float fHitRate = (float)a_pItem->HitRate;
	float fHitRate = a_pItem->HitRate;

	float fHabitWeight = 1.0f;

	AtumTime currAtumTime;
	GetAtumTime(&currAtumTime);

	if (a_pMonsterInfo->MonsterHabit == DES_MONHABIT_DAY && !IS_IN_RANGE(0, currAtumTime.Hour, 6))
	{
		fHabitWeight = 1.1f;
	}
	else if (a_pMonsterInfo->MonsterHabit == DES_MONHABIT_NIGHT && IS_IN_RANGE(0, currAtumTime.Hour, 6))
	{
		fHabitWeight = 1.1f;
	}

	// 2010. 06. 14 by hsLee 인피니티 필드 2차 난이도 조절. (몬스터 공격력 추가 수정, Pierce확률과 적중률 적용. )
	if ( a_pMonInfoExtend )
		fHitRate *= a_pMonInfoExtend->fAtkDmgRatio;

	// 2011-11-23 shcho, 회피확률, 스탯에 따른 공격 성곡률 수정 (3번째항목, 7번째항목)
	float fRtn_Val = fHitRate * fHabitWeight + (float)a_pMonsterInfo->Level / 2.55f;
	// end 2011-11-23 shcho, 회피확률, 스탯에 따른 공격 성곡률 수정 (3번째항목, 7번째항목)

	return fRtn_Val;
	//return pItem->HitRate * fHabitWeight + pMonsterInfo->Level;
// 2005-11-08 by cmkwon, 캐릭터의 스킬레벨링을 위해서 몬스터의 공격 확률에 레벨을 더한값을 리턴한다.
//	return pItem->HitRate * fHabitWeight;
}


// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
/********************************************************************************************************************************************
**
**	몬스터의 방어 확률.
**
**	Create Info :	??. ??. ??. 
**
**	Update Info :	2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) ) - 몬스터 확장 정보 인자 추가.
**
*********************************************************************************************************************************************/
//float CAtumSJ::GetDefenseProbabilityM(MONSTER_INFO *pMonster)
float CAtumSJ :: GetDefenseProbabilityM( const MONSTER_INFO *a_pMonster , const MONSTER_INFO_EXTEND *a_pMonInfoExtend /*= NULL*/ )
{
	// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
	if ( a_pMonInfoExtend )
		return a_pMonInfoExtend->DefenseProbability;

	return a_pMonster->DefenseProbability;
	//return pMonster->DefenseProbability;
}
// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )

float CAtumSJ::GetAttackC(CHARACTER *pCharacter, ITEM *pAttackItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
	float fMinAttackFactor = (bIsPrimaryAttack?pParamFactor->pfm_MINATTACK_01:pParamFactor->pfm_MINATTACK_02)
								+ GetAttackC_IncreaseRate(pCharacter->TotalGearStat.AttackPart, pCharacter->Level);
	float fMaxAttackFactor = (bIsPrimaryAttack?pParamFactor->pfm_MAXATTACK_01:pParamFactor->pfm_MAXATTACK_02)
								+ GetAttackC_IncreaseRate(pCharacter->TotalGearStat.AttackPart, pCharacter->Level);
#ifdef _ATUM_SERVER
	if(0.3f < fMinAttackFactor - fMaxAttackFactor)
	{
		char szSysLog[1024];
		if(bIsPrimaryAttack)
		{
			sprintf(szSysLog, "[ERROR] CAtumSJ::GetAttackC_ CharInfo(%s:%d) ItemInfo(%s) pfm_MINATTACK_01(%f) pfm_MAXATTACK_01(%f)\r\n"
				, pCharacter->CharacterName, pCharacter->CharacterUniqueNumber, pAttackItem->ItemName
				, pParamFactor->pfm_MINATTACK_01, pParamFactor->pfm_MAXATTACK_01);
		}
		else
		{
			sprintf(szSysLog, "[ERROR] CAtumSJ::GetAttackC_ CharInfo(%s:%d) ItemInfo(%s) pfm_MINATTACK_02(%f) pfm_MAXATTACK_02(%f)\r\n"
				, pCharacter->CharacterName, pCharacter->CharacterUniqueNumber, pAttackItem->ItemName
				, pParamFactor->pfm_MINATTACK_02, pParamFactor->pfm_MAXATTACK_02);
		}
		g_pGlobal->WriteSystemLog(szSysLog);
		fMinAttackFactor = fMaxAttackFactor+0.3f;
	}
#endif// end_#ifdef _ATUM_SERVER
	return RANDF2(pAttackItem->AbilityMin*(1.0f+fMinAttackFactor), pAttackItem->AbilityMax*(1.0f+fMaxAttackFactor));
}

float CAtumSJ::GetMinAttackC(CHARACTER *pCharacter, ITEM *pAttackItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
{
	float fMinAttackFactor = (bIsPrimaryAttack?pParamFactor->pfm_MINATTACK_01:pParamFactor->pfm_MINATTACK_02);

	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
	return (pAttackItem->AbilityMin*(1.0f+fMinAttackFactor)) * (1.0f + GetAttackC_IncreaseRate(pCharacter->TotalGearStat.AttackPart, pCharacter->Level));
}

float CAtumSJ::GetMaxAttackC(CHARACTER *pCharacter, ITEM *pAttackItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
{
	float fMaxAttackFactor = (bIsPrimaryAttack?pParamFactor->pfm_MAXATTACK_01:pParamFactor->pfm_MAXATTACK_02);

	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
	return (pAttackItem->AbilityMax*(1.0f+fMaxAttackFactor)) * (1.0f + GetAttackC_IncreaseRate(pCharacter->TotalGearStat.AttackPart, pCharacter->Level));
}

float CAtumSJ::GetDefenseC(CHARACTER *pCharacter, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
{
	// Damage = Attack * (PROB256_MAX_VALUE - Defense) / PROB256_MAX_VALUE 로 계산하기
	// 피공격자가 캐릭터이면
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
	// 2010-07-19 by dhjin, 확률 수식 변경
//	return GetDefenseC_DecreaseRate(pCharacter->TotalGearStat.DefensePart, pCharacter->Level)*PROB256_MAX_VALUE + (bIsPrimaryAttack?pParamFactor->pfp_DEFENSE_01:pParamFactor->pfp_DEFENSE_02);
	return GetDefenseC_DecreaseRate(pCharacter->TotalGearStat.DefensePart, pCharacter->Level)*PROB100_MAX_VALUE + (bIsPrimaryAttack?pParamFactor->pfp_DEFENSE_01:pParamFactor->pfp_DEFENSE_02);
}


// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
/****************************************************************************************************************************************************************************************
**
**	몬스터의 공격력
**
**	Create Info :	??. ??. ??
**
**	Update Info :	2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) ) - 몬스터 확장 정보 인자 추가 및 기존 인자 포인터 성격수정. ( const 형 )
**
*****************************************************************************************************************************************************************************************/
//float CAtumSJ::GetAttackM(ITEM *pItem)
float CAtumSJ :: GetAttackM( const ITEM *a_pItem , const MONSTER_INFO_EXTEND *a_pMonInfoExtend /*= NULL*/ )
{
	// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
	//return RANDF2(pItem->AbilityMin, pItem->AbilityMax);

	float fRatio = 1.0f;

	if ( a_pMonInfoExtend )
		fRatio = a_pMonInfoExtend->fAtkDmgRatio;

	return RANDF2( a_pItem->AbilityMin * fRatio, a_pItem->AbilityMax * fRatio );
	// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
}
// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )


// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
/**************************************************************************************************************************************************************************************
**
**	몬스터의 최소 공격력
**
**	Create Info :	??. ??. ??
**
**	Update Info :	2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) ) - 몬스터 확장 정보 인자 추가 및 기존 인자 포인터 성격수정. ( const 형 )
**
***************************************************************************************************************************************************************************************/
//float CAtumSJ::GetMinAttackM(ITEM *pMonsterAttackItem)
float CAtumSJ :: GetMinAttackM( const ITEM *a_pMonsterAttackItem , const MONSTER_INFO_EXTEND *a_pMonInfoExtend /*= NULL*/ )
{
	// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
	//return pMonsterAttackItem->AbilityMin;

	return ( a_pMonsterAttackItem->AbilityMin * ( a_pMonInfoExtend == NULL ? 1.0f : a_pMonInfoExtend->fAtkDmgRatio ) );
	// End. 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
}
// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )


// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
/**************************************************************************************************************************************************************************************
**
**	몬스터의 최대 공격력
**
**	Create Info :	??. ??. ??
**
**	Update Info :	2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) ) - 몬스터 확장 정보 인자 추가 및 기존 인자 포인터 성격수정. ( const 형 )
**
***************************************************************************************************************************************************************************************/
//float CAtumSJ::GetMaxAttackM(ITEM *pMonsterAttackItem)
float CAtumSJ :: GetMaxAttackM( const ITEM *a_pMonsterAttackItem , const MONSTER_INFO_EXTEND *a_pMonInfoExtend /*= NULL*/ )
{
	// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
	//return pMonsterAttackItem->AbilityMax;

	return ( a_pMonsterAttackItem->AbilityMax * ( a_pMonInfoExtend == NULL ? 1.0f : a_pMonInfoExtend->fAtkDmgRatio ) );
	// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )

}
// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )


// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
/*************************************************************************************************************************************************************************************
**
**	몬스터 방어력 리턴.
**
**	Create Info :	??????
**
**	Update Info :	2009-12-24 by cmkwon, 몬스터 Defense를 인피니티서버(아레나포함)에서 고정값으로 처리 - 

					2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) ) - 몬스터 확장정보 인자 추가 및 참조 포인터들의 성격변경 ( const 처리. )
**
**************************************************************************************************************************************************************************************/
//float CAtumSJ::GetDefenseM( const MONSTER_INFO *a_pMonster, BOOL i_bIsArenaServer/*=FALSE*/ ) 
float CAtumSJ::GetDefenseM( const MONSTER_INFO *a_pMonster, BOOL i_bIsArenaServer/*=FALSE*/ , const MONSTER_INFO_EXTEND *a_pMonInfoExtend /*= NULL*/ )
{
	// 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )
	/*if ( a_pMonInfoExtend )
		Defense = a_pMonInfoExtend->Defense;

	if(i_bIsArenaServer)
	{// 2009-12-24 by cmkwon, 몬스터 Defense를 인피니티서버(아레나포함)에서 고정값으로 처리 - 
		return a_pMonster->Defense;
	}

	return RANDI(0, a_pMonster->Defense);*/

	// 2010-07-19 by dhjin, 확률 수식 변경
//	Prob256_t Defense = a_pMonster->Defense;
	float Defense = a_pMonster->Defense;

	if ( a_pMonInfoExtend )
		Defense = a_pMonInfoExtend->Defense;

	if(i_bIsArenaServer)
	{// 2009-12-24 by cmkwon, 몬스터 Defense를 인피니티서버(아레나포함)에서 고정값으로 처리 - 
		return Defense;
	}

	// 2010-07-19 by dhjin, 확률 수식 변경
//	return RANDI(0, Defense);
	return RANDF2(0, Defense);
	// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )

}
// End 2010. 05. 19 by hsLee 인피니티 필드 2차 난이도 조절. (신호처리 + 몬스터 처리(서버) )



// 2010. 06. 14 by hsLee 인피니티 필드 2차 난이도 조절. (몬스터 공격력 추가 수정, Pierce확률과 적중률 적용. )
/*****************************************************************************************************************************************************************************
**
**	몬스터의 PierceAttack확률 
**
**	Create Info :	??. ??. ??. 
**
**	Update Info :	// 2009-12-17 by cmkwon, 데미지 계산식 관련한 필드(방어력,회피,피어스,확률)에 255이상 값을 설정 가능하게 수정 - 
**
**					// 2010. 06. 14 by hsLee 인피니티 필드 2차 난이도 조절. (몬스터 공격력 추가 수정, Pierce확률과 적중률 적용. ) - 몬스터 밸런스 인자 추가, 인자의 const 화.
**
**					   (const MONSTER_INFO_EXTEND *a_pMonInfoExtend = NULL)
**
******************************************************************************************************************************************************************************/
//float CAtumSJ::GetPierceAttackProbabilityM(int i_MonsterLevel, ITEM *i_pAttItem)
float CAtumSJ::GetPierceAttackProbabilityM ( const int i_MonsterLevel, const ITEM *i_pAttItem , const MONSTER_INFO_EXTEND *a_pMonInfoExtend /*= NULL*/ )
{
	//return GetLevelStatValue(i_MonsterLevel)->Level_MonsertPierceAttackProbability + i_pAttItem->FractionResistance;

	float fRtn_Val = GetLevelStatValue(i_MonsterLevel)->Level_MonsertPierceAttackProbability + i_pAttItem->FractionResistance;

	if ( a_pMonInfoExtend )
		fRtn_Val *= a_pMonInfoExtend->fAtkDmgRatio;

	return fRtn_Val;

}
// End 2010. 06. 14 by hsLee 인피니티 필드 2차 난이도 조절. (몬스터 공격력 추가 수정, Pierce확률과 적중률 적용. )


// 캐릭터의 초당 최소 공격력
float CAtumSJ::GetMinAttackPerSecondC(CHARACTER *pCharacter, ITEM *pAttackItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
{
	float fMinAttack = GetMinAttackC(pCharacter, pAttackItem, pParamFactor, bIsPrimaryAttack);
	float fSecond = 0.0f;
	if(bIsPrimaryAttack)
	{
		fMinAttack = fMinAttack*(pAttackItem->ShotNum + pParamFactor->pfp_SHOTNUM_01)*(pAttackItem->MultiNum+pParamFactor->pfp_MULTINUM_01);
		fSecond = ( (float)(pAttackItem->ReAttacktime*(1.0f+pParamFactor->pfm_REATTACKTIME_01)) )/1000.0f;
	}
	else
	{
		fMinAttack = fMinAttack*(pAttackItem->ShotNum + pParamFactor->pfp_SHOTNUM_02)*(pAttackItem->MultiNum+pParamFactor->pfp_MULTINUM_02);
		fSecond = ( (float)(pAttackItem->ReAttacktime*(1.0f+pParamFactor->pfm_REATTACKTIME_02)) )/1000.0f;
	}

	if(fSecond <= 0.0f)
	{
		return fMinAttack;
	}
	
	return fMinAttack/fSecond;
}

// 캐릭터의 초당 최대 공격력
float CAtumSJ::GetMaxAttackPerSecondC(CHARACTER *pCharacter, ITEM *pAttackItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
{
	float fMaxAttack = GetMaxAttackC(pCharacter, pAttackItem, pParamFactor, bIsPrimaryAttack);
	float fSecond = 0.0f;
	if(bIsPrimaryAttack)
	{
		fMaxAttack = fMaxAttack*(pAttackItem->ShotNum + pParamFactor->pfp_SHOTNUM_01)*(pAttackItem->MultiNum+pParamFactor->pfp_MULTINUM_01);
		fSecond = ( (float)(pAttackItem->ReAttacktime*(1.0f+pParamFactor->pfm_REATTACKTIME_01)) )/1000.0f;
	}
	else
	{
		fMaxAttack = fMaxAttack*(pAttackItem->ShotNum + pParamFactor->pfp_SHOTNUM_02)*(pAttackItem->MultiNum+pParamFactor->pfp_MULTINUM_02);
		fSecond = ( (float)(pAttackItem->ReAttacktime*(1.0f+pParamFactor->pfm_REATTACKTIME_02)) )/1000.0f;
	}

	if(fSecond <= 0.0f)
	{
		return fMaxAttack;
	}

	return fMaxAttack/fSecond;
}


int CAtumSJ::GetTotalPrimaryShotCountPerReattackTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return (pItem->ShotNum + pParamFactor->pfp_SHOTNUM_01) * (pItem->MultiNum + pParamFactor->pfp_MULTINUM_01);
}

int CAtumSJ::GetTotalPrimaryShotNumPerReattackTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return pItem->ShotNum + pParamFactor->pfp_SHOTNUM_01;
}

int CAtumSJ::GetTotalSecondaryShotNumPerReattackTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return pItem->ShotNum + pParamFactor->pfp_SHOTNUM_02;
}

int CAtumSJ::GetTotalSecondaryShotCountPerReattackTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return (pItem->ShotNum + pParamFactor->pfp_SHOTNUM_02) * (pItem->MultiNum + pParamFactor->pfp_MULTINUM_02);
}

DWORD CAtumSJ::GetReattackTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return pItem->ReAttacktime*(1.0f+(IS_PRIMARY_WEAPON(pItem->Kind)?pParamFactor->pfm_REATTACKTIME_01:pParamFactor->pfm_REATTACKTIME_02));
}

float CAtumSJ::GetAttackRange(ITEM *pItem, CParamFactor *pParamFactor)
{
	return max(0.1f, pItem->Range*(1.0f+(IS_PRIMARY_WEAPON(pItem->Kind)?pParamFactor->pfm_RANGE_01:pParamFactor->pfm_RANGE_02)));
}

int CAtumSJ::GetSecondaryMultiNumCount(ITEM *pItem, CParamFactor *pParamFactor)
{
	return pItem->MultiNum + pParamFactor->pfp_MULTINUM_02;
}

float CAtumSJ::GetOverheatTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return (pItem->Time*(1.0f+(IS_PRIMARY_WEAPON(pItem->Kind)?pParamFactor->pfm_TIME_01:pParamFactor->pfm_TIME_02))/1000.0f);
}

float CAtumSJ::GetShotCountReattackTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return (CAtumSJ::GetReattackTime(pItem,pParamFactor)/1000.0f)/(IS_PRIMARY_WEAPON(pItem->Kind)?CAtumSJ::GetTotalPrimaryShotCountPerReattackTime(pItem,pParamFactor):1);
}

float CAtumSJ::GetShotNumReattackTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return (CAtumSJ::GetReattackTime(pItem,pParamFactor)/1000.0f)/(IS_PRIMARY_WEAPON(pItem->Kind)?CAtumSJ::GetTotalPrimaryShotNumPerReattackTime(pItem,pParamFactor):GetTotalSecondaryShotNumPerReattackTime(pItem,pParamFactor));
} 

float CAtumSJ::GetPrepareTime(ITEM *pItem, CParamFactor *pParamFactor)
{
	return (pItem->AttackTime+(IS_PRIMARY_WEAPON(pItem->Kind)?pParamFactor->pfp_ATTACKTIME_01:pParamFactor->pfp_ATTACKTIME_02))/1000.0f;
}

int CAtumSJ::GetMultiTargetNum(ITEM *pItem, CParamFactor *pParamFactor)
{
	return pItem->MultiTarget + pParamFactor->pfp_MULTITAGET;
}

float CAtumSJ::GetAttackRangeAngle(ITEM *pItem, CParamFactor *pParamFactor)
{
	return pItem->RangeAngle+(IS_PRIMARY_WEAPON(pItem->Kind)?pParamFactor->pfp_RANGEANGLE_01:pParamFactor->pfp_RANGEANGLE_02);
}

UINT CAtumSJ::GetItemSellingPriceAtShop(ITEM* pItem)
{
	return (UINT)(pItem->Price * GetItemSellingPriceRate());
}

float CAtumSJ::GetItemSellingPriceRate()
{
	return 0.2f;	// 20%
}

float CAtumSJ::GetExplosionRange(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	return ((float)i_pItem->ExplosionRange)
			+ (IS_PRIMARY_WEAPON(i_pItem->Kind)?i_pParamFactor->pfp_EXPLOSIONRANGE_01:i_pParamFactor->pfp_EXPLOSIONRANGE_02);
}

int CAtumSJ::GetCountMineAtATime(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	return GetSecondaryMultiNumCount(i_pItem, i_pParamFactor) * 3;
}

USHORT CAtumSJ::GetReactionRange(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	return i_pItem->ReactionRange + i_pParamFactor->pfp_REACTION_RANGE;
}

// 아이템의 초당 최소 공격력
float CAtumSJ::GetMinAttackPerSecond(ITEM *i_pRealItem)
{
	float fMinAttack = i_pRealItem->AbilityMin*i_pRealItem->ShotNum*i_pRealItem->MultiNum;
	float fSecond = ((float)i_pRealItem->ReAttacktime)/1000.0f;
	if(fSecond <= 0.0f)
	{
		return fMinAttack;
	}
	return fMinAttack/fSecond;
}

// 아이템의 초당 최대 공격력
float CAtumSJ::GetMaxAttackPerSecond(ITEM *i_pRealItem)
{
	float fMaxAttack = i_pRealItem->AbilityMax*i_pRealItem->ShotNum*i_pRealItem->MultiNum;
	float fSecond = ((float)i_pRealItem->ReAttacktime)/1000.0f;
	if(fSecond <= 0.0f)
	{
		return fMaxAttack;
	}
	return fMaxAttack/fSecond;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetPrimaryRadarRange(ITEM *i_pItem, CParamFactor *i_pParamFactor)
/// \brief		1형 레이더 사정 거리
/// \author		cmkwon
/// \date		2005-11-22 ~ 2005-11-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetPrimaryRadarRange(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	return i_pItem->AbilityMin * (1.0f + i_pParamFactor->pfm_ATTACK_RANGE_01);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetSecondaryRadarRange(ITEM *i_pItem, CParamFactor *i_pParamFactor)
/// \brief		2형 레이더 사정 거리
/// \author		cmkwon
/// \date		2005-11-22 ~ 2005-11-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetSecondaryRadarRange(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	return i_pItem->AbilityMax * (1.0f + i_pParamFactor->pfm_ATTACK_RANGE_02);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetCircularAngle(ITEM *i_pItem, CParamFactor *i_pParamFactor)
/// \brief		기어의 선회력, 2005-11-28 by cmkwon
/// \author		cmkwon
/// \date		2005-11-28 ~ 2005-11-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetCircularAngle(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
// 2005-12-02 by cmkwon
//	return i_pItem->SpeedPenalty * (1.0f + i_pParamFactor->pfm_SKILL_HYPERMOVING);
	return i_pItem->SpeedPenalty * (1.0f + i_pParamFactor->pfm_SKILL_REACTIONSPEED);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetEngineRangeAngle(ITEM *i_pItem, CParamFactor *i_pParamFactor)
/// \brief		// 하이퍼 무빙(선회각), 2005-12-02 by cmkwon
/// \author		cmkwon
/// \date		2005-12-02 ~ 2005-12-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetEngineRangeAngle(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	// 2008-09-22 by dhjin, 신규 인첸트, 밑과 같이 수정
//	return i_pItem->RangeAngle * (1.0f + i_pParamFactor->pfm_SKILL_ENGINEANGLE);
	return (i_pItem->RangeAngle * (1.0f + i_pParamFactor->pfm_SKILL_ENGINEANGLE) ) + i_pParamFactor->pfm_ENGINE_ANGLE_UP;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetEngineBoosterRangeAngle(ITEM *i_pItem, CParamFactor *i_pParamFactor)
/// \brief		// 하이퍼 무빙(부스터 선회각), 2005-12-02 by cmkwon
/// \author		cmkwon
/// \date		2005-12-02 ~ 2005-12-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetEngineBoosterRangeAngle(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	// 2008-09-22 by dhjin, 신규 인첸트, 밑과 같이 수정
//	return i_pItem->BoosterAngle * (1.0f + i_pParamFactor->pfm_SKILL_ENGINEBOOSTERANGLE);
	return (i_pItem->BoosterAngle * (1.0f + i_pParamFactor->pfm_SKILL_ENGINEBOOSTERANGLE) ) + i_pParamFactor->pfm_ENGINE_BOOSTERANGLE_UP;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetWarHeadSpeed(ITEM *i_pItem, CParamFactor *i_pParamFactor)
/// \brief		// 176, 2007-06-11 by cmkwon, 탄두의 속도
/// \author		cmkwon
/// \date		2007-06-19 ~ 2007-06-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetWarHeadSpeed(ITEM *i_pItem, CParamFactor *i_pParamFactor)
{
	if(FALSE == IS_SECONDARY_WEAPON(i_pItem->Kind))
	{// 2008-05-29 by cmkwon, (버그 수정)탄두 인챈트 아이템 메모리핵 걸리는 버그 수정(G0010300) - 2형 무기가 아니면 기본값을 리턴한다.
		return i_pItem->RepeatTime;
	}

	return i_pItem->RepeatTime * (1.0f + i_pParamFactor->pfm_WARHEAD_SPEED);
}

float CAtumSJ::GetMonsterDeadExpWeight(int i_nCharacterLevel, int i_nMonsterLevel)
{
	int nLevelDiff = i_nMonsterLevel - i_nCharacterLevel;
	
	if (nLevelDiff <= -11) return 0.50f;
	else if (IS_IN_RANGE(-10, nLevelDiff, -9)) return 0.60f;
//	else if (IS_IN_RANGE(-8, nLevelDiff, -7)) return 0.91f;
//	else if (IS_IN_RANGE(-6, nLevelDiff, -5)) return 0.94f;
//	else if (IS_IN_RANGE(-4, nLevelDiff, -3)) return 0.97f;
	else if (nLevelDiff == -8) return 0.70f;
	else if (nLevelDiff == -7) return 0.75f;
	else if (nLevelDiff == -6) return 0.80f;
	else if (nLevelDiff == -5) return 0.85f;
	else if (nLevelDiff == -4) return 0.90f;
	else if (nLevelDiff == -3) return 0.95f;
	else if (IS_IN_RANGE(-2, nLevelDiff, 2)) return 1.0f;
	else if (IS_IN_RANGE(3, nLevelDiff, 4)) return 1.03f;
	else if (IS_IN_RANGE(5, nLevelDiff, 6)) return 1.06f;
	else if (IS_IN_RANGE(7, nLevelDiff, 8)) return 1.09f;
	else if (nLevelDiff >= 9) return 1.12f;

	return 1.0f;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetPartyBonusExpWeight(int nPartyMemberCnts)
/// \brief		
/// \author		cmkwon
/// \date		2006-07-13 ~ 2006-07-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetPartyBonusExpWeight(int nPartyMemberCnts)
{
	switch(nPartyMemberCnts)
	{
	case 2:		return 1.03f;
	case 3:		return 1.06f;
	case 4:		return 1.09f;
	case 5:		return 1.15f;
	case 6:		return 1.30f;
	}
	return 1.0f;
}

BOOL CAtumSJ::CanPickUpDropMoney(int i_nCharacterLevel, MONSTER_INFO *i_pMonInfo)
{
	if(COMPARE_MPOPTION_BIT(i_pMonInfo->MPOption, MPOPTION_BIT_BOSS_MONSTER|MPOPTION_BIT_NAMED_MONSTER))
	{// 2005-12-16 by cmkwon, 보스몬스터/네임드몬스터 손실없음
		return TRUE;
	}
	int nLevelDiff = i_pMonInfo->Level - i_nCharacterLevel;
	Prob100_t prob;

	if (nLevelDiff <= -10) prob = 40;
	else if (nLevelDiff == -9) prob = 50;
	else if (nLevelDiff == -8) prob = 60;
	else if (nLevelDiff == -7) prob = 70;
	else if (nLevelDiff >= -6) prob = 100;

	return (RAND100() <= prob);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::CanPickUpDropItem(int i_nCharacterLevel, MONSTER_INFO *i_pMonInfo)
/// \brief		
/// \author		cmkwon
/// \date		2005-12-16 ~ 2005-12-16
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::CanPickUpDropItem(int i_nCharacterLevel, MONSTER_INFO *i_pMonInfo)
{
	if(COMPARE_MPOPTION_BIT(i_pMonInfo->MPOption, MPOPTION_BIT_BOSS_MONSTER|MPOPTION_BIT_NAMED_MONSTER))
	{// 2005-12-16 by cmkwon, 보스몬스터/네임드몬스터 손실없음
		return TRUE;
	}
	int nLevelDiff = i_pMonInfo->Level - i_nCharacterLevel;
	Prob100_t prob;

	if (nLevelDiff <= -10) prob = 30;
	else if (nLevelDiff == -9) prob = 50;
	else if (nLevelDiff == -8) prob = 70;
	else if (nLevelDiff == -7) prob = 90;
	else if (nLevelDiff >= -6) prob = 100;

	Prob100_t rValue = RAND100();

//	DBGOUT("r %d : p %d\r\n", rValue, prob);

	return (rValue <= prob);
}

BOOL CAtumSJ::CanPickUpDropRare(int i_nCharacterLevel, MONSTER_INFO *i_pMonInfo)
{
	if(COMPARE_MPOPTION_BIT(i_pMonInfo->MPOption, MPOPTION_BIT_BOSS_MONSTER|MPOPTION_BIT_NAMED_MONSTER))
	{// 2005-12-16 by cmkwon, 보스몬스터/네임드몬스터 손실없음
		return TRUE;
	}
	int nLevelDiff = i_pMonInfo->Level - i_nCharacterLevel;
	Prob100_t prob;

	if (nLevelDiff <= -10) prob = 0;
	else if (nLevelDiff == -9) prob = 0;
	else if (nLevelDiff == -8) prob = 25;
	else if (nLevelDiff == -7) prob = 50;
	else if (nLevelDiff == -6) prob = 75;
	else if (nLevelDiff == -5) prob = 100;
	else if (nLevelDiff == -4) prob = 100;
	else if (nLevelDiff >= -3) prob = 100;

	return (RAND100() <= prob);
}

const LEVEL_EXPERIENCE* CAtumSJ::GetLevelExperience(int level)
{
// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 
// 	if (level <= 0 || level > 100)
// 	{
// 		return NULL;
// 	}
	///////////////////////////////////////////////////////////////////////////////
	// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 
	level = max(1, level);
	level = min(CHARACTER_LEVEL_110, level);

	return &arrLevelExperienceNew[level];
}

const Experience_t CAtumSJ::GetInitialExperienceOfLevel(int level)
{
// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 
// 	if (level <= 0 || level > 100)
// 	{
// 		return 1.7E308;
// 	}
	///////////////////////////////////////////////////////////////////////////////
	// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 
	level = max(1, level);
	level = min(CHARACTER_LEVEL_110, level);

	return arrLevelExperienceNew[level-1].Experience;
}

const float CAtumSJ::GetPercentageOfExperience(Experience_t exp, int level)
{
	// 2010-03-11 by cmkwon, 지원레벨 110 상항 처리 빠진것 수정 - 최대지원레벨이면 무조건 0%를 리턴
	if(CHARACTER_LEVEL_110 <= level)
	{
		return 0.0f;
	}

	return (exp-GetInitialExperienceOfLevel(level))/(GetInitialExperienceOfLevel(level+1)-GetInitialExperienceOfLevel(level))*100.0f;
}

const Experience_t CAtumSJ::GetExperienceFromPercentage(float i_fPercentage, int level)
{
	return (GetInitialExperienceOfLevel(level) + i_fPercentage/100.0f*(GetInitialExperienceOfLevel(level+1)-GetInitialExperienceOfLevel(level)));
}


///////////////////////////////////////////////////////////////////////////////
// 2006-07-28 by cmkwon
// struct ITEMKIND_STRING				// 2006-07-28 by cmkwon
// {
// 	BYTE		byItemKind0;	
// 	char		*szItemKindString;		// 2006-07-28 by cmkwon, ITEMKIND_XXX --> "ITEMKIND_XXX"로 변환
// 	char		*szItemKindName;		// 2006-07-28 by cmkwon, 유저에게 보여주는 ItemKindString
// 	BOOL		bIsBazaarItemKind;		// 2006-07-28 by cmkwon, 개인 상점에서 거래 가능 ITEMKIND_XXX
// };
const ITEMKIND_STRING g_arrItemKindString[] =
{
	{ITEMKIND_AUTOMATIC					,"ITEMKIND_AUTOMATIC"				,STRCMD_CS_ITEMKIND_AUTOMATIC				,TRUE},
	{ITEMKIND_VULCAN					,"ITEMKIND_VULCAN"					,STRCMD_CS_ITEMKIND_VULCAN					,TRUE},
	{ITEMKIND_DUALIST					,"ITEMKIND_DUALIST"					,STRCMD_CS_ITEMKIND_DUALIST					,TRUE},
	{ITEMKIND_CANNON					,"ITEMKIND_CANNON"					,STRCMD_CS_ITEMKIND_CANNON					,TRUE},
	{ITEMKIND_RIFLE						,"ITEMKIND_RIFLE"					,STRCMD_CS_ITEMKIND_RIFLE					,TRUE},
	{ITEMKIND_GATLING					,"ITEMKIND_GATLING"					,STRCMD_CS_ITEMKIND_GATLING					,TRUE},
	{ITEMKIND_LAUNCHER					,"ITEMKIND_LAUNCHER"				,STRCMD_CS_ITEMKIND_LAUNCHER				,FALSE},
	{ITEMKIND_MASSDRIVE					,"ITEMKIND_MASSDRIVE"				,STRCMD_CS_ITEMKIND_MASSDRIVE				,TRUE},
	{ITEMKIND_ROCKET					,"ITEMKIND_ROCKET"					,STRCMD_CS_ITEMKIND_ROCKET					,FALSE},
	{ITEMKIND_MISSILE					,"ITEMKIND_MISSILE"					,STRCMD_CS_ITEMKIND_MISSILE					,TRUE},
	{ITEMKIND_BUNDLE					,"ITEMKIND_BUNDLE"					,STRCMD_CS_ITEMKIND_BUNDLE					,TRUE},
	{ITEMKIND_MINE						,"ITEMKIND_MINE"					,STRCMD_CS_ITEMKIND_MINE					,FALSE},
	{ITEMKIND_SHIELD					,"ITEMKIND_SHIELD"					,STRCMD_CS_ITEMKIND_SHIELD					,FALSE},
	{ITEMKIND_DUMMY						,"ITEMKIND_DUMMY"					,STRCMD_CS_ITEMKIND_DUMMY					,FALSE},
	{ITEMKIND_FIXER						,"ITEMKIND_FIXER"					,STRCMD_CS_ITEMKIND_FIXER					,FALSE},
	{ITEMKIND_DECOY						,"ITEMKIND_DECOY"					,STRCMD_CS_ITEMKIND_DECOY					,FALSE},
	{ITEMKIND_DEFENSE					,"ITEMKIND_DEFENSE"					,STRCMD_CS_ITEMKIND_DEFENSE					,TRUE},
	{ITEMKIND_SUPPORT					,"ITEMKIND_SUPPORT"					,STRCMD_CS_ITEMKIND_SUPPORT					,TRUE},
	{ITEMKIND_ENERGY					,"ITEMKIND_ENERGY"					,STRCMD_CS_ITEMKIND_ENERGY					,TRUE},
	{ITEMKIND_INGOT						,"ITEMKIND_INGOT"					,STRCMD_CS_ITEMKIND_INGOT					,TRUE},
	{ITEMKIND_CARD						,"ITEMKIND_CARD"					,STRCMD_CS_ITEMKIND_CARD					,TRUE},
	{ITEMKIND_ENCHANT					,"ITEMKIND_ENCHANT"					,STRCMD_CS_ITEMKIND_ENCHANT					,TRUE},
	{ITEMKIND_TANK						,"ITEMKIND_TANK"					,STRCMD_CS_ITEMKIND_TANK					,FALSE},
	{ITEMKIND_BULLET					,"ITEMKIND_BULLET"					,STRCMD_CS_ITEMKIND_BULLET					,FALSE},
	{ITEMKIND_QUEST						,"ITEMKIND_QUEST"					,STRCMD_CS_ITEMKIND_QUEST					,FALSE},
	{ITEMKIND_RADAR						,"ITEMKIND_RADAR"					,STRCMD_CS_ITEMKIND_RADAR					,TRUE},
	{ITEMKIND_COMPUTER					,"ITEMKIND_COMPUTER"				,STRCMD_CS_ITEMKIND_COMPUTER				,TRUE},
	{ITEMKIND_GAMBLE					,"ITEMKIND_GAMBLE"					,STRCMD_CS_ITEMKIND_GAMBLE					,TRUE},
	{ITEMKIND_PREVENTION_DELETE_ITEM	,"ITEMKIND_PREVENTION_DELETE_ITEM"	,STRCMD_CS_ITEMKIND_PREVENTION_DELETE_ITEM	,FALSE},
	{ITEMKIND_BLASTER					,"ITEMKIND_BLASTER"					,STRCMD_CS_ITEMKIND_BLASTER					,FALSE},
	{ITEMKIND_RAILGUN					,"ITEMKIND_RAILGUN"					,STRCMD_CS_ITEMKIND_RAILGUN					,FALSE},
	{ITEMKIND_ACCESSORY_UNLIMITED		,"ITEMKIND_ACCESSORY_UNLIMITED"		,STRCMD_CS_ITEMKIND_ACCESSORY_UNLIMITED		,TRUE},
	{ITEMKIND_ACCESSORY_TIMELIMIT		,"ITEMKIND_ACCESSORY_TIMELIMIT"		,STRCMD_CS_ITEMKIND_ACCESSORY_TIMELIMIT		,TRUE},
	{ITEMKIND_INFLUENCE_BUFF			,"ITEMKIND_INFLUENCE_BUFF"			,STRCMD_CS_ITEMKIND_INFLUENCE_BUFF			,FALSE},
	{ITEMKIND_INFLUENCE_GAMEEVENT		,"ITEMKIND_INFLUENCE_GAMEEVENT"		,STRCMD_CS_ITEMKIND_INFLUENCE_GAMEEVENT		,FALSE},
	{ITEMKIND_RANDOMBOX					,"ITEMKIND_RANDOMBOX"				,STRCMD_CS_ITEMKIND_RANDOMBOX				,TRUE},
	{ITEMKIND_MARK						,"ITEMKIND_MARK"					,STRCMD_CS_ITEMKIND_MARK				 	,TRUE},
	{ITEMKIND_SKILL_SUPPORT_ITEM		,"ITEMKIND_SKILL_SUPPORT_ITEM"		,STRCMD_CS_ITEMKIND_SKILL_SUPPORT_ITEM		,FALSE},
	{ITEMKIND_PET_ITEM					,"ITEMKIND_PET_ITEM"				,STRCMD_CS_ITEMKIND_PET_ITEM				,FALSE},


	{ITEMKIND_ALL_WEAPON				,"ITEMKIND_ALL_WEAPON"				,STRCMD_CS_ITEMKIND_ALL_WEAPON				,FALSE},
	{ITEMKIND_PRIMARY_WEAPON_ALL		,"ITEMKIND_PRIMARY_WEAPON_ALL"		,STRCMD_CS_ITEMKIND_PRIMARY_WEAPON_ALL		,FALSE},
	{ITEMKIND_PRIMARY_WEAPON_1			,"ITEMKIND_PRIMARY_WEAPON_1"		,STRCMD_CS_ITEMKIND_PRIMARY_WEAPON_1		,FALSE},
	{ITEMKIND_PRIMARY_WEAPON_2			,"ITEMKIND_PRIMARY_WEAPON_2"		,STRCMD_CS_ITEMKIND_PRIMARY_WEAPON_2		,FALSE},
	{ITEMKIND_SECONDARY_WEAPON_ALL		,"ITEMKIND_SECONDARY_WEAPON_ALL"	,STRCMD_CS_ITEMKIND_SECONDARY_WEAPON_ALL	,FALSE},
	{ITEMKIND_SECONDARY_WEAPON_1		,"ITEMKIND_SECONDARY_WEAPON_1"		,STRCMD_CS_ITEMKIND_SECONDARY_WEAPON_1		,FALSE},
	{ITEMKIND_SECONDARY_WEAPON_2		,"ITEMKIND_SECONDARY_WEAPON_2"		,STRCMD_CS_ITEMKIND_SECONDARY_WEAPON_2		,FALSE},
	{ITEMKIND_SKILL_ATTACK				,"ITEMKIND_SKILL_ATTACK"			,STRCMD_CS_ITEMKIND_SKILL_ATTACK			,FALSE},
	{ITEMKIND_SKILL_DEFENSE				,"ITEMKIND_SKILL_DEFENSE"			,STRCMD_CS_ITEMKIND_SKILL_DEFENSE			,FALSE},
	{ITEMKIND_SKILL_SUPPORT				,"ITEMKIND_SKILL_SUPPORT"			,STRCMD_CS_ITEMKIND_SKILL_SUPPORT			,FALSE},
	{ITEMKIND_SKILL_ATTRIBUTE			,"ITEMKIND_SKILL_ATTRIBUTE"			,STRCMD_CS_ITEMKIND_SKILL_ATTRIBUTE			,FALSE},
	{ITEMKIND_COLOR_ITEM				,"ITEMKIND_COLOR_ITEM"				,STRCMD_CS_ITEMKIND_COLOR_ITEM				,FALSE},
	{ITEMKIND_FOR_MON_PRIMARY			,"ITEMKIND_FOR_MON_PRIMARY"			,STRCMD_CS_ITEMKIND_FOR_MON_PRIMARY			,FALSE},
	{ITEMKIND_FOR_MON_GUN				,"ITEMKIND_FOR_MON_GUN"				,STRCMD_CS_ITEMKIND_FOR_MON_GUN				,FALSE},
	{ITEMKIND_FOR_MON_BEAM				,"ITEMKIND_FOR_MON_BEAM"			,STRCMD_CS_ITEMKIND_FOR_MON_BEAM			,FALSE},
	{ITEMKIND_FOR_MON_ALLATTACK			,"ITEMKIND_FOR_MON_ALLATTACK"		,STRCMD_CS_ITEMKIND_FOR_MON_ALLATTACK		,FALSE},
	{ITEMKIND_FOR_MON_SECONDARY			,"ITEMKIND_FOR_MON_SECONDARY"		,STRCMD_CS_ITEMKIND_FOR_MON_SECONDARY		,FALSE},
	{ITEMKIND_FOR_MON_ROCKET			,"ITEMKIND_FOR_MON_ROCKET"			,STRCMD_CS_ITEMKIND_FOR_MON_ROCKET			,FALSE},
	{ITEMKIND_FOR_MON_MISSILE			,"ITEMKIND_FOR_MON_MISSILE"			,STRCMD_CS_ITEMKIND_FOR_MON_MISSILE			,FALSE},
	{ITEMKIND_FOR_MON_BUNDLE			,"ITEMKIND_FOR_MON_BUNDLE"			,STRCMD_CS_ITEMKIND_FOR_MON_BUNDLE			,FALSE},
	{ITEMKIND_FOR_MON_MINE				,"ITEMKIND_FOR_MON_MINE"			,STRCMD_CS_ITEMKIND_FOR_MON_MINE			,FALSE},
	{ITEMKIND_FOR_MON_SHIELD			,"ITEMKIND_FOR_MON_SHIELD"			,STRCMD_CS_ITEMKIND_FOR_MON_SHIELD			,FALSE},
	{ITEMKIND_FOR_MON_DUMMY				,"ITEMKIND_FOR_MON_DUMMY"			,STRCMD_CS_ITEMKIND_FOR_MON_DUMMY			,FALSE},
	{ITEMKIND_FOR_MON_FIXER				,"ITEMKIND_FOR_MON_FIXER"			,STRCMD_CS_ITEMKIND_FOR_MON_FIXER			,FALSE},
	{ITEMKIND_FOR_MON_DECOY				,"ITEMKIND_FOR_MON_DECOY"			,STRCMD_CS_ITEMKIND_FOR_MON_DECOY			,FALSE},
	{ITEMKIND_FOR_MON_FIRE				,"ITEMKIND_FOR_MON_FIRE"			,STRCMD_CS_ITEMKIND_FOR_MON_FIRE			,FALSE},
	{ITEMKIND_FOR_MON_OBJBEAM			,"ITEMKIND_FOR_MON_OBJBEAM"			,STRCMD_CS_ITEMKIND_FOR_MON_OBJBEAM			,FALSE},
	{ITEMKIND_FOR_MON_STRAIGHTBOOM		,"ITEMKIND_FOR_MON_STRAIGHTBOOM"	,STRCMD_CS_ITEMKIND_FOR_MON_STRAIGHTBOOM	,FALSE},
	{ITEMKIND_ALL_ITEM					,"ITEMKIND_ALL_ITEM"				,STRCMD_CS_ITEMKIND_ALL_ITEM				,FALSE},	// 2008-06-03 by cmkwon, AdminTool, DBTool 사용시 아이템 검색시 콤보박스에서 검색 기능 추가(K0000143) - 
	{ITEMKIND_UNKNOWN					,"ITEMKIND_UNKNOWN"					,STRCMD_CS_ITEMKIND_UNKNOWN					,FALSE}
};


// 2006-07-28 by cmkwon, 함수명 변경 - GetItemKindStringKO --> GetItemKindName
const char *CAtumSJ::GetItemKindName(BYTE i_nKind)
{
	for(int i=0; g_arrItemKindString[i].byItemKind0 != ITEMKIND_UNKNOWN; i++)
	{
		if(i_nKind == g_arrItemKindString[i].byItemKind0)
		{
			return g_arrItemKindString[i].szItemKindName;
		}
	}
	return STRCMD_CS_ITEMKIND_UNKNOWN;

// 2006-07-28 by cmkwon, 위와 같이 수정함
// 	switch(i_nKind)
// 	{
// 	case ITEMKIND_AUTOMATIC:				return STRCMD_CS_ITEMKIND_AUTOMATIC;
// 	case ITEMKIND_VULCAN:					return STRCMD_CS_ITEMKIND_VULCAN;
// 	case ITEMKIND_DUALIST:					return STRCMD_CS_ITEMKIND_DUALIST;		// 2005-08-01 by hblee : GRENADE -> DUALIST 으로 변경.
// 	case ITEMKIND_CANNON:					return STRCMD_CS_ITEMKIND_CANNON;
// 	case ITEMKIND_RIFLE:					return STRCMD_CS_ITEMKIND_RIFLE;
// 	case ITEMKIND_GATLING:					return STRCMD_CS_ITEMKIND_GATLING;
// 	case ITEMKIND_LAUNCHER:					return STRCMD_CS_ITEMKIND_LAUNCHER;
// 	case ITEMKIND_MASSDRIVE:				return STRCMD_CS_ITEMKIND_MASSDRIVE;
// 	case ITEMKIND_ROCKET:					return STRCMD_CS_ITEMKIND_ROCKET;
// 	case ITEMKIND_MISSILE:					return STRCMD_CS_ITEMKIND_MISSILE;
// 	case ITEMKIND_BUNDLE:					return STRCMD_CS_ITEMKIND_BUNDLE;
// 	
// 	case ITEMKIND_MINE:						return STRCMD_CS_ITEMKIND_MINE;
// 	case ITEMKIND_SHIELD:					return STRCMD_CS_ITEMKIND_SHIELD;
// 	case ITEMKIND_DUMMY:					return STRCMD_CS_ITEMKIND_DUMMY;
// 	case ITEMKIND_FIXER:					return STRCMD_CS_ITEMKIND_FIXER;
// 	case ITEMKIND_DECOY:					return STRCMD_CS_ITEMKIND_DECOY;
// 	case ITEMKIND_DEFENSE:					return STRCMD_CS_ITEMKIND_DEFENSE;
// 	case ITEMKIND_SUPPORT:					return STRCMD_CS_ITEMKIND_SUPPORT;
// 	case ITEMKIND_ENERGY:					return STRCMD_CS_ITEMKIND_ENERGY;
// 	case ITEMKIND_INGOT:					return STRCMD_CS_ITEMKIND_INGOT;
// 	case ITEMKIND_CARD:						return STRCMD_CS_ITEMKIND_CARD;
// 	case ITEMKIND_ENCHANT:					return STRCMD_CS_ITEMKIND_ENCHANT;
// 	case ITEMKIND_TANK:						return STRCMD_CS_ITEMKIND_TANK;
// 	case ITEMKIND_BULLET:					return STRCMD_CS_ITEMKIND_BULLET;
// 	case ITEMKIND_QUEST:					return STRCMD_CS_ITEMKIND_QUEST;
// 	case ITEMKIND_RADAR:					return STRCMD_CS_ITEMKIND_RADAR;
// 	case ITEMKIND_COMPUTER:					return STRCMD_CS_ITEMKIND_COMPUTER;
// 	case ITEMKIND_GAMBLE:					return STRCMD_CS_ITEMKIND_GAMBLE;
// 	case ITEMKIND_PREVENTION_DELETE_ITEM:	return STRCMD_CS_ITEMKIND_PREVENTION_DELETE_ITEM;
// 	case ITEMKIND_BLASTER:					return STRCMD_CS_ITEMKIND_BLASTER;	// 2005-08-01 by hblee : 블래스터류 추가.
// 	case ITEMKIND_RAILGUN:					return STRCMD_CS_ITEMKIND_RAILGUN;	// 2005-08-01 by hblee : 레일건류 추가.
// 	case ITEMKIND_ACCESSORY_UNLIMITED:		return STRCMD_CS_ITEMKIND_ACCESSORY_UNLIMITED;	// 2006-03-17 by cmkwon, 사용시간이 <영원>인 액세서리 아이템
// 	case ITEMKIND_ACCESSORY_TIMELIMIT:		return STRCMD_CS_ITEMKIND_ACCESSORY_TIMELIMIT;	// 2006-03-17 by cmkwon, 사용시간에 시간 제한이 있는 액세서리 아이템
// 	case ITEMKIND_INFLUENCE_BUFF:			return STRCMD_CS_ITEMKIND_INFLUENCE_BUFF;		// 2006-04-21 by cmkwon, 세력 카드 아이템, 현재는 세력버프 아이템
// 	case ITEMKIND_INFLUENCE_GAMEEVENT:		return STRCMD_CS_ITEMKIND_INFLUENCE_GAMEEVENT;	// 2006-04-21 by cmkwon, 세력 이벤트 아이템
// 
// 	case ITEMKIND_ALL_WEAPON:				return STRCMD_CS_ITEMKIND_ALL_WEAPON;
// 	case ITEMKIND_PRIMARY_WEAPON_ALL:		return STRCMD_CS_ITEMKIND_PRIMARY_WEAPON_ALL;
// 	case ITEMKIND_PRIMARY_WEAPON_1:			return STRCMD_CS_ITEMKIND_PRIMARY_WEAPON_1;
// 	case ITEMKIND_PRIMARY_WEAPON_2:			return STRCMD_CS_ITEMKIND_PRIMARY_WEAPON_2;
// 	case ITEMKIND_SECONDARY_WEAPON_ALL:		return STRCMD_CS_ITEMKIND_SECONDARY_WEAPON_ALL;
// 	case ITEMKIND_SECONDARY_WEAPON_1:		return STRCMD_CS_ITEMKIND_SECONDARY_WEAPON_1;
// 	case ITEMKIND_SECONDARY_WEAPON_2:		return STRCMD_CS_ITEMKIND_SECONDARY_WEAPON_2;
// 	case ITEMKIND_SKILL_ATTACK:				return STRCMD_CS_ITEMKIND_SKILL_ATTACK;
// 	case ITEMKIND_SKILL_DEFENSE:			return STRCMD_CS_ITEMKIND_SKILL_DEFENSE;
// 	case ITEMKIND_SKILL_SUPPORT:			return STRCMD_CS_ITEMKIND_SKILL_SUPPORT;
// 	case ITEMKIND_SKILL_ATTRIBUTE:			return STRCMD_CS_ITEMKIND_SKILL_ATTRIBUTE;
// 
// 	case ITEMKIND_COLOR_ITEM:				return "Color Item";
// 
// 	case ITEMKIND_FOR_MON_PRIMARY:			return STRCMD_CS_ITEMKIND_FOR_MON_PRIMARY;
// 	case ITEMKIND_FOR_MON_GUN:				return STRCMD_CS_ITEMKIND_FOR_MON_GUN;
// 	case ITEMKIND_FOR_MON_BEAM:				return STRCMD_CS_ITEMKIND_FOR_MON_BEAM;
// 	case ITEMKIND_FOR_MON_ALLATTACK:		return STRCMD_CS_ITEMKIND_FOR_MON_ALLATTACK;
// 	case ITEMKIND_FOR_MON_SECONDARY:		return STRCMD_CS_ITEMKIND_FOR_MON_SECONDARY;
// 	case ITEMKIND_FOR_MON_ROCKET:			return STRCMD_CS_ITEMKIND_FOR_MON_ROCKET;
// 	case ITEMKIND_FOR_MON_MISSILE:			return STRCMD_CS_ITEMKIND_FOR_MON_MISSILE;
// 	case ITEMKIND_FOR_MON_BUNDLE:			return STRCMD_CS_ITEMKIND_FOR_MON_BUNDLE;
// 	case ITEMKIND_FOR_MON_MINE:				return STRCMD_CS_ITEMKIND_FOR_MON_MINE;
// 	case ITEMKIND_FOR_MON_SHIELD:			return STRCMD_CS_ITEMKIND_FOR_MON_SHIELD;
// 	case ITEMKIND_FOR_MON_DUMMY:			return STRCMD_CS_ITEMKIND_FOR_MON_DUMMY;
// 	case ITEMKIND_FOR_MON_FIXER:			return STRCMD_CS_ITEMKIND_FOR_MON_FIXER;
// 	case ITEMKIND_FOR_MON_DECOY:			return STRCMD_CS_ITEMKIND_FOR_MON_DECOY;
// 	case ITEMKIND_FOR_MON_FIRE:				return STRCMD_CS_ITEMKIND_FOR_MON_FIRE;
// 	case ITEMKIND_FOR_MON_OBJBEAM:			return STRCMD_CS_ITEMKIND_FOR_MON_OBJBEAM;
// 	case ITEMKIND_FOR_MON_STRAIGHTBOOM:		return STRCMD_CS_ITEMKIND_FOR_MON_STRAIGHTBOOM;
// 	}
// 	return STRCMD_CS_ITEMKIND_UNKNOWN;
}

// 2006-07-28 by cmkwon, 필요 없는 함수
// const char *CAtumSJ::GetItemKindString(BYTE i_nKind)
// {
// 	for(int i=0; g_arrItemKindString[i].byItemKind0 != ITEMKIND_UNKNOWN; i++)
// 	{
// 		if(i_nKind == g_arrItemKindString[i].byItemKind0)
// 		{
// 			return g_arrItemKindString[i].szItemKindString;
// 		}
// 	}
// 	return STRCMD_CS_ITEMKIND_UNKNOWN;
// 
// // 2006-07-28 by cmkwon, 위와 같이 수정함
// // 	switch(i_nKind)
// // 	{
// // 	case ITEMKIND_AUTOMATIC:					return "ITEMKIND_AUTOMATIC";
// // 	case ITEMKIND_VULCAN:						return "ITEMKIND_VULCAN";
// // 	case ITEMKIND_DUALIST:						return "ITEMKIND_DUALIST";		// 2005-08-01 by hblee : GRENADE -> DUALIST 으로 변경.
// // 	case ITEMKIND_CANNON:						return "ITEMKIND_CANNON";
// // 	case ITEMKIND_RIFLE:						return "ITEMKIND_RIFLE";
// // 	case ITEMKIND_GATLING:						return "ITEMKIND_GATLING";
// // 	case ITEMKIND_LAUNCHER:						return "ITEMKIND_LAUNCHER";
// // 	case ITEMKIND_MASSDRIVE:					return "ITEMKIND_MASSDRIVE";
// // 	case ITEMKIND_ROCKET:						return "ITEMKIND_ROCKET";
// // 	case ITEMKIND_MISSILE:						return "ITEMKIND_MISSILE";
// // 	case ITEMKIND_BUNDLE:						return "ITEMKIND_BUNDLE";
// // 	case ITEMKIND_MINE:							return "ITEMKIND_MINE";
// // 	case ITEMKIND_SHIELD:						return "ITEMKIND_SHIELD";
// // 	case ITEMKIND_DUMMY:						return "ITEMKIND_DUMMY";
// // 	case ITEMKIND_FIXER:						return "ITEMKIND_FIXER";
// // 	case ITEMKIND_DECOY:						return "ITEMKIND_DECOY";
// // 	case ITEMKIND_DEFENSE:						return "ITEMKIND_DEFENSE";
// // 	case ITEMKIND_SUPPORT:						return "ITEMKIND_SUPPORT";
// // 	case ITEMKIND_ENERGY:						return "ITEMKIND_ENERGY";
// // 	case ITEMKIND_INGOT:						return "ITEMKIND_INGOT";
// // 	case ITEMKIND_CARD:							return "ITEMKIND_CARD";
// // 	case ITEMKIND_ENCHANT:						return "ITEMKIND_ENCHANT";
// // 	case ITEMKIND_TANK:							return "ITEMKIND_TANK";
// // 	case ITEMKIND_BULLET:						return "ITEMKIND_BULLET";
// // 	case ITEMKIND_QUEST:						return "ITEMKIND_QUEST";
// // 	case ITEMKIND_RADAR:						return "ITEMKIND_RADAR";
// // 	case ITEMKIND_COMPUTER:						return "ITEMKIND_COMPUTER";
// // 	case ITEMKIND_GAMBLE:						return "ITEMKIND_GAMBLE";
// // 	case ITEMKIND_PREVENTION_DELETE_ITEM:		return "ITEMKIND_PREVENTION_DELETE_ITEM";
// // 	case ITEMKIND_BLASTER:						return "ITEMKIND_BLASTER";	// 2005-08-01 by hblee : 블래스터류 추가.
// // 	case ITEMKIND_RAILGUN:						return "ITEMKIND_RAILGUN";	// 2005-08-01 by hblee : 레일건류 추가.
// // 	case ITEMKIND_ACCESSORY_UNLIMITED:			return "ITEMKIND_ACCESSORY_UNLIMITED";	// 2006-03-17 by cmkwon, 사용시간이 <영원>인 액세서리 아이템
// // 	case ITEMKIND_ACCESSORY_TIMELIMIT:			return "ITEMKIND_ACCESSORY_TIMELIMIT";	// 2006-03-17 by cmkwon, 사용시간에 시간 제한이 있는 액세서리 아이템
// // 	case ITEMKIND_INFLUENCE_BUFF:				return "ITEMKIND_INFLUENCE_BUFF";	// 2006-04-21 by cmkwon
// // 	case ITEMKIND_INFLUENCE_GAMEEVENT:			return "ITEMKIND_INFLUENCE_GAMEEVENT";	// 2006-04-21 by cmkwon
// // 
// // 	case ITEMKIND_COLOR_ITEM:					return "ITEMKIND_COLOR_ITEM";	// 2005-12-06 by cmkwon
// // 	}
// //
// //	return "ITEMKIND_NA";
// }


///////////////////////////////////////////////////////////////////////////////
/// \fn			const BYTE CAtumSJ::GetItemKindByItemKindName(char *i_szItemKindName)
/// \brief		
/// \author		cmkwon
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
const BYTE CAtumSJ::GetItemKindByItemKindName(char *i_szItemKindName)
{
	for(int i=0; g_arrItemKindString[i].byItemKind0 != ITEMKIND_UNKNOWN; i++)
	{
		if(0 == stricmp(g_arrItemKindString[i].szItemKindName, i_szItemKindName))
		{
			return g_arrItemKindString[i].byItemKind0;
		}
	}
	return ITEMKIND_UNKNOWN;
}

const char *CAtumSJ::GetRaceString(USHORT i_nRace)
{
	if(RACE_ALL == i_nRace)
	{
		return STRCMD_CS_COMMON_RACE_ALL;
	}
	if(COMPARE_RACE(i_nRace, RACE_OPERATION))
	{
		return STRCMD_CS_COMMON_RACE_OPERATION;
	}
	if(COMPARE_RACE(i_nRace, RACE_GAMEMASTER))
	{
		return STRCMD_CS_COMMON_RACE_GAMEMASTER;
	}
	if(COMPARE_RACE(i_nRace, RACE_MONITOR))
	{
		return STRCMD_CS_COMMON_RACE_MONITOR;
	}
	if(COMPARE_RACE(i_nRace, RACE_DEMO))
	{
		return STRCMD_CS_COMMON_RACE_DEMO;
	}
	if(COMPARE_RACE(i_nRace, RACE_GUEST))
	{
		return STRCMD_CS_COMMON_RACE_GUEST;
	}
	if(COMPARE_RACE(i_nRace, RACE_BATTALUS))
	{
		return STRCMD_CS_COMMON_RACE_BATTALUS;
	}
	if(COMPARE_RACE(i_nRace, RACE_DECA))
	{
		return STRCMD_CS_COMMON_RACE_DECA;
	}
	if(COMPARE_RACE(i_nRace, RACE_PHILON))
	{
		return STRCMD_CS_COMMON_RACE_PHILON;
	}
	if(COMPARE_RACE(i_nRace, RACE_SHARRINE))
	{
		return STRCMD_CS_COMMON_RACE_SHARRINE;
	}
// 2006-04-20 by cmkwon
// 	if(COMPARE_RACE(i_nRace, RACE_MONSTER1))
// 	{
// 		return STRCMD_CS_COMMON_RACE_MONSTER1;
// 	}
	if(COMPARE_RACE(i_nRace, RACE_INFLUENCE_LEADER))
	{// 2006-04-20 by cmkwon
		return STRCMD_CS_COMMON_RACE_INFLUENCE_LEADER;
	}
// 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 -
//	if(COMPARE_RACE(i_nRace, RACE_INFLUENCE_SUBLEADER))
//	{// 2006-12-08 by dhjin
//		return STRCMD_CS_COMMON_RACE_INFLUENCE_SUBLEADER;
//	}
	if(COMPARE_RACE(i_nRace, RACE_INFLUENCE_SUBLEADER_1))
	{// 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 -
		return STRCMD_CS_COMMON_RACE_INFLUENCE_SUBLEADER_1;
	}
	if(COMPARE_RACE(i_nRace, RACE_INFLUENCE_SUBLEADER_2))
	{// 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 -
		return STRCMD_CS_COMMON_RACE_INFLUENCE_SUBLEADER_2;
	}

// 2006-12-08 by dhjin
//	if(COMPARE_RACE(i_nRace, RACE_MONSTER2))
//	{
//		return STRCMD_CS_COMMON_RACE_MONSTER2;
//	}

// 2007-10-06 by cmkwon, 부지도자 2명의 호칭을 다르게 설정 -
//	if(COMPARE_RACE(i_nRace, RACE_NPC))
//	{
//		return STRCMD_CS_COMMON_RACE_NPC;
//	}
	if(0 == i_nRace)
	{
		return STRCMD_CS_COMMON_RACE_NORMAL;
	}
	return STRCMD_CS_COMMON_RACE_UNKNOWN;
}

const char *CAtumSJ::GetUnitKindString(USHORT i_nUnitKind)
{
	switch(i_nUnitKind)
	{
	case UNITKIND_BT01:
	case UNITKIND_BT02:
	case UNITKIND_BT03:
	case UNITKIND_BT04:
		return STRCMD_CS_UNITKIND_BGEAR;		// 2007-03-29 by cmkwon
		break;
	case UNITKIND_DT01:
	case UNITKIND_DT02:
	case UNITKIND_DT03:
	case UNITKIND_DT04:
		return STRCMD_CS_UNITKIND_AGEAR;		// 2007-03-29 by cmkwon
		break;
	case UNITKIND_ST01:
	case UNITKIND_ST02:
	case UNITKIND_ST03:
	case UNITKIND_ST04:
		return STRCMD_CS_UNITKIND_IGEAR;		// 2007-03-29 by cmkwon
		break;
	case UNITKIND_OT01:
	case UNITKIND_OT02:
	case UNITKIND_OT03:
	case UNITKIND_OT04:
		return STRCMD_CS_UNITKIND_MGEAR;		// 2007-03-29 by cmkwon
		break;
	}

	return STRCMD_CS_UNITKIND_UNKNOWN;
}

const char *CAtumSJ::GetGLOGUnitKindString(USHORT i_nUnitKind)	   // 2010-06-01 by shcho, GLogDB 관련 -
{
	switch(i_nUnitKind)
	{
	case UNITKIND_BT01:
	case UNITKIND_BT02:
	case UNITKIND_BT03:
	case UNITKIND_BT04:
		return UNITKIND_ENG_BGEAR;	
		break;
	case UNITKIND_DT01:
	case UNITKIND_DT02:
	case UNITKIND_DT03:
	case UNITKIND_DT04:
		return UNITKIND_ENG_AGEAR;
		break;
	case UNITKIND_ST01:
	case UNITKIND_ST02:
	case UNITKIND_ST03:
	case UNITKIND_ST04:
		return UNITKIND_ENG_IGEAR;
		break;
	case UNITKIND_OT01:
	case UNITKIND_OT02:
	case UNITKIND_OT03:
	case UNITKIND_OT04:
		return UNITKIND_ENG_MGEAR;
		break;
	}
	
	return UNITKIND_ENG_UNKNOWN;
}


const GEAR_STAT_CHANGE_VALUE g_arrGearStatChangeValue[] =
{
//	{UnitKind,			1 공격, 2 방어,	3 연료, 4 정신, 5 쉴드, 6 회피
// 2006-09-11 by cmkwon, LocalizationDefineCommon.h에 정의함 나라별로 다르게 설정 가능
	{UNITKIND_BGEAR,	STAT_BGEAR_ATTACK_PART,	STAT_BGEAR_DEFENSE_PART, STAT_BGEAR_FUEL_PART, STAT_BGEAR_SOUL_PART, STAT_BGEAR_SHIELD_PART, STAT_BGEAR_DODGE_PART},		// 1
	{UNITKIND_MGEAR,	STAT_MGEAR_ATTACK_PART,	STAT_MGEAR_DEFENSE_PART, STAT_MGEAR_FUEL_PART, STAT_MGEAR_SOUL_PART, STAT_MGEAR_SHIELD_PART, STAT_MGEAR_DODGE_PART},		// 16
	{UNITKIND_AGEAR,	STAT_AGEAR_ATTACK_PART,	STAT_AGEAR_DEFENSE_PART, STAT_AGEAR_FUEL_PART, STAT_AGEAR_SOUL_PART, STAT_AGEAR_SHIELD_PART, STAT_AGEAR_DODGE_PART},		// 256
	{UNITKIND_IGEAR,	STAT_IGEAR_ATTACK_PART,	STAT_IGEAR_DEFENSE_PART, STAT_IGEAR_FUEL_PART, STAT_IGEAR_SOUL_PART, STAT_IGEAR_SHIELD_PART, STAT_IGEAR_DODGE_PART},		// 4096
	{0, 0, 0, 0, 0, 0, 0}
};

const GEAR_AUTO_STAT_VALUE_PER_LEVEL g_arrGearAutoStatValuePerLevel[] =
{
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	1,	3,	3,	3,	3,	3,	3},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	2,	6,	3,	3,	3,	6,	3},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	3,	9,	6,	3,	3,	6,	3},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	4,	12,	6,	3,	6,	6,	3},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	5,	15,	6,	3,	6,	9,	3},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	6,	18,	6,	6,	6,	9,	3},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	7,	21,	6,	6,	6,	9,	6},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	8,	24,	6,	6,	6,	12,	6},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	9,	27,	6,	6,	9,	12,	6},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	10,	30,	6,	6,	9,	12,	6},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	11,	33,	6,	6,	9,	15,	9},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	12,	36,	6,	9,	9,	15,	9},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	13,	39,	9,	9,	9,	15,	9},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	14,	42,	9,	9,	9,	18,	9},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	15,	45,	9,	9,	12,	18,	9},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	16,	48,	9,	9,	12,	18,	12},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	17,	51,	9,	9,	12,	21,	12},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	18,	54,	12,	9,	12,	21,	12},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	19,	57,	12,	12,	12,	21,	12},
	{AUTOSTAT_TYPE_BGEAR_ATTACK,	20,	60,	12,	12,	12,	24,	12},

	{AUTOSTAT_TYPE_BGEAR_MULTI,		1,	3,	3,	3,	3,	3,	3},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		2,	6,	3,	3,	3,	6,	3},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		3,	6,	6,	3,	6,	6,	3},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		4,	6,	6,	6,	6,	6,	6},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		5,	9,	6,	6,	6,	9,	6},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		6,	9,	9,	6,	9,	9,	6},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		7,	9,	9,	9,	9,	9,	9},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		8,	12,	9,	9,	9,	12,	9},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		9,	12,	12,	9,	12,	12,	9},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		10,	15,	12,	9,	12,	12,	12},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		11,	18,	12,	9,	12,	15,	12},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		12,	18,	15,	9,	15,	15,	12},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		13,	18,	15,	12,	15,	15,	15},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		14,	21,	15,	12,	15,	18,	15},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		15,	21,	18,	12,	18,	18,	15},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		16,	21,	18,	15,	18,	18,	18},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		17,	24,	18,	15,	18,	21,	18},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		18,	24,	21,	15,	21,	21,	18},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		19,	24,	21,	15,	21,	24,	21},
	{AUTOSTAT_TYPE_BGEAR_MULTI,		20,	27,	21,	15,	21,	27,	21},
	
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	1,	4,	2,	3,	3,	2,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	2,	8,	2,	3,	3,	4,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	3,	12,	2,	3,	6,	4,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	4,	20,	2,	3,	6,	4,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	5,	24,	2,	6,	6,	4,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	6,	28,	2,	6,	6,	6,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	7,	32,	2,	6,	9,	6,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	8,	40,	2,	6,	9,	6,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	9,	48,	2,	6,	9,	6,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	10,	52,	2,	6,	9,	8,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	11,	56,	2,	6,	12,	8,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	12,	64,	2,	6,	12,	8,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	13,	68,	2,	9,	12,	8,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	14,	72,	2,	9,	12,	10,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	15,	76,	2,	9,	15,	10,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	16,	84,	2,	9,	15,	10,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	17,	92,	2,	9,	15,	10,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	18,	96,	2,	9,	15,	12,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	19,	100,2,	9,	18,	12,	4},
	{AUTOSTAT_TYPE_IGEAR_ATTACK,	20,	104,2,	12,	18,	12,	4},

	{AUTOSTAT_TYPE_IGEAR_DODGE,		1,	4,	2,	3,	3,	2,	4},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		2,	4,	2,	3,	3,	4,	8},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		3,	4,	2,	3,	3,	4,	12},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		4,	4,	2,	3,	6,	4,	20},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		5,	4,	2,	6,	6,	4,	24},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		6,	4,	2,	6,	6,	6,	28},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		7,	4,	2,	6,	9,	6,	32},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		8,	4,	2,	6,	9,	6,	40},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		9,	4,	2,	6,	9,	6,	48},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		10,	4,	2,	6,	9,	8,	52},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		11,	4,	2,	6,	9,	8,	56},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		12,	4,	2,	6,	9,	8,	64},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		13,	4,	2,	9,	9,	8,	68},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		14,	4,	2,	9,	9,	10,	72},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		15,	4,	2,	9,	12,	10,	76},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		16,	4,	2,	9,	12,	10,	84},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		17,	4,	2,	9,	12,	10,	92},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		18,	4,	2,	9,	12,	12,	96},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		19,	4,	2,	9,	15,	12,	100},
	{AUTOSTAT_TYPE_IGEAR_DODGE,		20,	4,	2,	12,	15,	12,	104},

	{AUTOSTAT_TYPE_AGEAR_ATTACK,	1,	4,	3,	4,	2,	4,	1},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	2,	8,	3,	4,	2,	8,	1},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	3,	12,	3,	4,	4,	8,	1},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	4,	16,	3,	4,	4,	8,	2},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	5,	20,	3,	8,	4,	8,	2},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	6,	24,	3,	8,	4,	12,	2},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	7,	32,	3,	8,	4,	12,	2},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	8,	36,	3,	8,	4,	12,	3},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	9,	40,	3,	12,	4,	12,	3},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	10,	44,	3,	12,	4,	16,	3},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	11,	48,	3,	12,	6,	16,	3},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	12,	52,	3,	12,	6,	16,	4},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	13,	60,	3,	12,	6,	16,	4},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	14,	64,	3,	12,	6,	20,	4},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	15,	68,	3,	12,	8,	20,	4},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	16,	72,	3,	12,	8,	20,	5},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	17,	76,	3,	16,	8,	20,	5},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	18,	80,	3,	16,	8,	24,	5},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	19,	84,	3,	16,	10,	24,	5},
	{AUTOSTAT_TYPE_AGEAR_ATTACK,	20,	88,	3,	16,	10,	24,	6},

	{AUTOSTAT_TYPE_AGEAR_SHIELD,	1,	4,	3,	4,	2,	4,	1},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	2,	4,	3,	4,	2,	12,	1},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	3,	4,	3,	4,	4,	16,	1},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	4,	4,	3,	4,	4,	20,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	5,	4,	3,	8,	4,	24,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	6,	4,	3,	8,	4,	32,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	7,	4,	6,	8,	4,	36,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	8,	4,	9,	8,	4,	40,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	9,	4,	9,	12,	4,	44,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	10,	4,	9,	12,	4,	52,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	11,	4,	9,	12,	6,	56,	2},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	12,	4,	9,	12,	6,	60,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	13,	4,	9,	12,	6,	68,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	14,	4,	12,	12,	6,	72,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	15,	4,	12,	12,	8,	76,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	16,	4,	15,	12,	8,	80,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	17,	4,	15,	16,	8,	84,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	18,	4,	15,	16,	8,	92,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	19,	4,	15,	16,	10,	96,	3},
	{AUTOSTAT_TYPE_AGEAR_SHIELD,	20,	4,	15,	16,	10,	100,4},

	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	1,	2,	4,	4,	2,	3,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	2,	2,	12,	4,	2,	3,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	3,	2,	16,	4,	4,	3,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	4,	2,	20,	4,	4,	6,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	5,	2,	24,	8,	4,	6,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	6,	2,	28,	8,	6,	6,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	7,	2,	36,	8,	6,	6,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	8,	2,	40,	8,	6,	9,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	9,	2,	48,	8,	6,	9,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	10,	2,	52,	12,	6,	9,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	11,	2,	56,	12,	8,	9,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	12,	2,	60,	12,	8,	12,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	13,	2,	68,	12,	8,	12,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	14,	2,	72,	12,	10,	12,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	15,	2,	76,	16,	10,	12,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	16,	2,	80,	16,	10,	15,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	17,	2,	88,	16,	10,	15,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	18,	2,	92,	16,	12,	15,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	19,	2,	100,16,	12,	15,	3},
	{AUTOSTAT_TYPE_MGEAR_DEFENSE,	20,	2,	104,16,	12,	18,	3},

	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	1,	2,	4,	4,	2,	3,	3},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	2,	2,	8,	4,	4,	3,	3},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	3,	2,	8,	8,	6,	3,	3},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	4,	2,	8,	8,	8,	3,	6},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	5,	2,	8,	8,	8,	6,	9},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	6,	2,	12,	8,	10,	6,	9},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	7,	2,	12,	8,	12,	9,	9},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	8,	2,	12,	8,	14,	12,	9},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	9,	2,	12,	12,	16,	12,	9},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	10,	2,	16,	12,	16,	15,	9},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	11,	2,	16,	12,	18,	15,	12},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	12,	2,	16,	12,	20,	15,	15},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	13,	2,	16,	16,	22,	15,	15},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	14,	2,	20,	16,	24,	15,	15},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	15,	2,	20,	16,	24,	18,	18},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	16,	2,	20,	16,	26,	18,	21},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	17,	2,	20,	16,	28,	21,	21},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	18,	2,	20,	20,	30,	21,	21},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	19,	2,	24,	20,	32,	21,	21},
	{AUTOSTAT_TYPE_MGEAR_SUPPORT,	20,	2,	28,	20,	32,	24,	21},
	{0, 0, 0, 0, 0, 0, 0}
};

const char* CAtumSJ::GetStatString(BYTE i_nStatKind)
{
	switch(i_nStatKind)
	{
	case STAT_ATTACK_PART:		return STRCMD_CS_STAT_ATTACK_PART;
	case STAT_DEFENSE_PART:		return STRCMD_CS_STAT_DEFENSE_PART;
	case STAT_FUEL_PART:		return STRCMD_CS_STAT_FUEL_PART;
	case STAT_SOUL_PART:		return STRCMD_CS_STAT_SOUL_PART;
	case STAT_SHIELD_PART:		return STRCMD_CS_STAT_SHIELD_PART;
	case STAT_DODGE_PART:		return STRCMD_CS_STAT_DODGE_PART;
	case STAT_BONUS:			return STRCMD_CS_STAT_BONUS;
	case STAT_ALL_PART:			return STRCMD_CS_STAT_ALL_PART;
	}
	return STRCMD_CS_STAT_UNKNOWN;
}

const char *CAtumSJ::GetTimerTypeString(TimerEventType i_nTimerEventType)
{
	switch(i_nTimerEventType)
	{
	case TE_TYPE_TEST:					return "TE_TYPE_TEST";
//	case TE_TYPE_SYNC_PRI:				return "TE_TYPE_SYNC_PRI";
//	case TE_TYPE_SYNC_SEC:				return "TE_TYPE_SYNC_SEC";
//	case TE_TYPE_SYNC_SKILL:			return "TE_TYPE_SYNC_SKILL";
//	case TE_TYPE_END_SKILL:				return "TE_TYPE_END_SKILL";
	case TE_TYPE_DELETE_DUMMY:			return "TE_TYPE_DELETE_DUMMY";
	case TE_TYPE_DELETE_FIXER:			return "TE_TYPE_DELETE_FIXER";
	case TE_TYPE_DELETE_DECOY:			return "TE_TYPE_DELETE_DECOY";
	case TE_TYPE_GRADUAL_SHIELD_UP:		return "TE_TYPE_GRADUAL_SHIELD_UP";
	case TE_TYPE_RECOVER_DP:			return "TE_TYPE_RECOVER_DP";
	case TE_TYPE_RECOVER_SP:			return "TE_TYPE_RECOVER_SP";
	case TE_TYPE_GRADUAL_HP_UP:			return "TE_TYPE_GRADUAL_HP_UP";
	case TE_TYPE_GRADUAL_DP_UP:			return "TE_TYPE_GRADUAL_DP_UP";
	case TE_TYPE_GRADUAL_SP_UP:			return "TE_TYPE_GRADUAL_SP_UP";
	case TE_TYPE_GRADUAL_EP_UP:			return "TE_TYPE_GRADUAL_EP_UP";
	case TE_TYPE_REQUEST_TIMEOUT:		return "TE_TYPE_REQUEST_TIMEOUT";
	case TE_TYPE_DECREASE_SP:			return "TE_TYPE_DECREASE_SP";
	}

	return "TE_TYPE_UNKNOWN";
}

const GEAR_STAT_CHANGE_VALUE* CAtumSJ::GetGearStatChangeValueStruct(USHORT i_UnitKind)
{
	for (int i = 0; g_arrGearStatChangeValue[i].UnitKind != 0; i++)
	{
		if (IS_SAME_UNITKIND(i_UnitKind, g_arrGearStatChangeValue[i].UnitKind))
		{
			return &g_arrGearStatChangeValue[i];
		}
	}

	return NULL;
}

Stat_t CAtumSJ::GetGearStatChangeValue(USHORT i_UnitKind, BYTE i_nStatKind)
{
	for (int i = 0; g_arrGearStatChangeValue[i].UnitKind != 0; i++)
	{
		if (IS_SAME_UNITKIND(i_UnitKind, g_arrGearStatChangeValue[i].UnitKind))
		{
			switch(i_nStatKind)
			{
			case STAT_ATTACK_PART:
				return g_arrGearStatChangeValue[i].GearStat1.AttackPart;
			case STAT_DEFENSE_PART:
				return g_arrGearStatChangeValue[i].GearStat1.DefensePart;
			case STAT_FUEL_PART:
				return g_arrGearStatChangeValue[i].GearStat1.FuelPart;
			case STAT_SOUL_PART:
				return g_arrGearStatChangeValue[i].GearStat1.SoulPart;
			case STAT_SHIELD_PART:
				return g_arrGearStatChangeValue[i].GearStat1.ShieldPart;
			case STAT_DODGE_PART:
				return g_arrGearStatChangeValue[i].GearStat1.DodgePart;
			default:
				return 0;
			}
		}
	}

	return 0;
}

const LEVEL_STAT_VALUE* CAtumSJ::GetLevelStatValue(int i_nLevelOrStat)
{
	if (i_nLevelOrStat < 0)
	{
		return &g_arrLevelStatValue[0];
	}
	else if (i_nLevelOrStat > MAX_LEVEL_OR_STAT_VALUE)
	{
		return &g_arrLevelStatValue[MAX_LEVEL_OR_STAT_VALUE];
	}
	else
	{
		return &g_arrLevelStatValue[i_nLevelOrStat];
	}
}


BOOL CAtumSJ::GetGearStatBYAutoStatTypeAndLevel(GEAR_AUTO_STAT_VALUE_PER_LEVEL *o_pAutoStatValue, INT i_autoStatType, INT i_level)
{
	for(int i=0; g_arrGearAutoStatValuePerLevel[i].AutoStatType1 != 0; i++)
	{
		if(i_autoStatType == g_arrGearAutoStatValuePerLevel[i].AutoStatType1
			&& i_level == g_arrGearAutoStatValuePerLevel[i].Level)
		{
			*o_pAutoStatValue = g_arrGearAutoStatValuePerLevel[i];
			return TRUE;
		}
	}

	return FALSE;
}

char * CAtumSJ::GetAutoStatTypeString(INT i_autoStatType)
{
	switch(i_autoStatType)
	{
	case AUTOSTAT_TYPE_FREESTYLE:				return STRCMD_CS_AUTOSTAT_TYPE_FREESTYLE;
	case AUTOSTAT_TYPE_BGEAR_ATTACK:			return STRCMD_CS_AUTOSTAT_TYPE_BGEAR_ATTACK;
	case AUTOSTAT_TYPE_BGEAR_MULTI:				return STRCMD_CS_AUTOSTAT_TYPE_BGEAR_MULTI;
	case AUTOSTAT_TYPE_IGEAR_ATTACK:			return STRCMD_CS_AUTOSTAT_TYPE_IGEAR_ATTACK;
	case AUTOSTAT_TYPE_IGEAR_DODGE:				return STRCMD_CS_AUTOSTAT_TYPE_IGEAR_DODGE;
	case AUTOSTAT_TYPE_AGEAR_ATTACK:			return STRCMD_CS_AUTOSTAT_TYPE_AGEAR_ATTACK;
	case AUTOSTAT_TYPE_AGEAR_SHIELD:			return STRCMD_CS_AUTOSTAT_TYPE_AGEAR_SHIELD;
	case AUTOSTAT_TYPE_MGEAR_DEFENSE:			return STRCMD_CS_AUTOSTAT_TYPE_MGEAR_DEFENSE;
	case AUTOSTAT_TYPE_MGEAR_SUPPORT:			return STRCMD_CS_AUTOSTAT_TYPE_MGEAR_SUPPORT;
	}

	return STRCMD_CS_AUTOSTAT_TYPE_UNKNOWN;
}



/*
// 스탯(Defense)에 따른 쉴드 증가분
// 적용 방법: OnDefenseStat = stat * 증가분
*/
SHORT CAtumSJ::GetCharacterHP(BYTE i_nLevel)
{
// 2005-06-29 by cmkwon, 기레벨당 HP가 아니라 기본은 모두 600이다
//	return GetLevelStatValue(i_nLevel)->HPOfLevel;
	return 600;
}

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
SHORT CAtumSJ::GetCharacterDP(Stat_t i_nShieldPart, BYTE i_byLevel)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return GetLevelStatValue(min(COUNT_MAX_STAT_POINT, i_nShieldPart))->ShieldPart_DP;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	return GetLevelStatValue(min(nMaxStatValue, i_nShieldPart))->ShieldPart_DP;
}

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
SHORT CAtumSJ::GetCharacterSP(Stat_t i_nSoulPart, BYTE i_byLevel)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return min(COUNT_MAX_STAT_POINT, i_nSoulPart) * 8;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	return min(nMaxStatValue, i_nSoulPart) * 8;
}

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
SHORT CAtumSJ::GetCharacterEP(Stat_t i_nFuelPart, BYTE i_byLevel)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return min(COUNT_MAX_STAT_POINT, i_nFuelPart) * 10;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	return min(nMaxStatValue, i_nFuelPart) * 10;
}

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
float CAtumSJ::GetAttackC_IncreaseRate(Stat_t i_nAttackPart, BYTE i_byLevel)
{	
	// 2007-05-16 by cmkwon, 300초과로 갑을 가지고 있고 적용시 최대 300이 되도록 수정	
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return GetLevelStatValue(min(COUNT_MAX_STAT_POINT, i_nAttackPart))->AttackPart_AttackIncreaseRate;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	return GetLevelStatValue(min(nMaxStatValue, i_nAttackPart))->AttackPart_AttackIncreaseRate;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetAttackC_IncreaseProbability(Stat_t i_nAttackPart)
/// \brief		명중률 - 공격스탯에 의한 공격확률과 동일한 기능을 가지는 추가 확률
///				// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
/// \author		cmkwon
/// \date		2005-06-29 ~ 2005-06-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetAttackC_IncreaseProbability(Stat_t i_nAttackPart, BYTE i_byLevel)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return GetLevelStatValue(min(COUNT_MAX_STAT_POINT,i_nAttackPart))->AttackPart_AttackIncreaseProbability;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	return GetLevelStatValue(min(nMaxStatValue,i_nAttackPart))->AttackPart_AttackIncreaseProbability;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			float CAtumSJ::GetAttackC_PierceAttackProbability(Stat_t i_nAttackPart, ITEM *pAttackItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack)
/// \brief		// 2008-09-22 by dhjin, 신규 인첸트, PierceAttack율 - 공격스탯에 의한 방어율과 상쇄가 되는 공격 방법 중 하나
///				// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
/// \author		cmkwon
/// \date		2005-06-29 ~ 2005-06-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
float CAtumSJ::GetAttackC_PierceAttackProbability(Stat_t i_nAttackPart, ITEM *pAttackItem, CParamFactor *pParamFactor, BOOL bIsPrimaryAttack, BYTE i_byLevel)
{
	// 2008-09-22 by dhjin, 신규 인첸트, 밑과 같이 수정
//	return GetLevelStatValue(min(COUNT_MAX_STAT_POINT,i_nAttackPart))->AttackPart_PierceAttackProbability;
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//float LevelPierce = GetLevelStatValue(min(COUNT_MAX_STAT_POINT,i_nAttackPart))->AttackPart_PierceAttackProbability;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	float LevelPierce = GetLevelStatValue(min(nMaxStatValue,i_nAttackPart))->AttackPart_PierceAttackProbability;

	if(bIsPrimaryAttack)
	{
		return pAttackItem->FractionResistance + LevelPierce + (pParamFactor->pfm_PIERCE_UP_01);
	}
	else
	{
		return pAttackItem->FractionResistance + LevelPierce + (pParamFactor->pfm_PIERCE_UP_02);
	}

	return pAttackItem->FractionResistance + LevelPierce;
}

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
float CAtumSJ::GetDefenseC_DecreaseRate(Stat_t i_nDefensePart, BYTE i_byLevel)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return GetLevelStatValue(min(COUNT_MAX_STAT_POINT,i_nDefensePart))->DefensePart_DefenseDecreaseRate;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	return GetLevelStatValue(min(nMaxStatValue,i_nDefensePart))->DefensePart_DefenseDecreaseRate;
}

// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 인자추가(, BYTE i_byLevel)
float CAtumSJ::GetDefenseProbabilityC_Rate(Stat_t i_nDodgePart, BYTE i_byLevel)
{
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	//return GetLevelStatValue(min(COUNT_MAX_STAT_POINT,i_nDodgePart))->DodgePart_DefenseProbabilityRate;
	///////////////////////////////////////////////////////////////////////////////
	// 2010-02-19 by cmkwon, 100이하 레벨 최대스탯 수치 버그 수정 - 
	int nMaxStatValue = GET_MAX_STAT_POINT(i_byLevel);
	return GetLevelStatValue(min(nMaxStatValue,i_nDodgePart))->DodgePart_DefenseProbabilityRate;
}

BOOL CAtumSJ::GetRepairCost(int *o_pnCost, int *o_pnRealAmountToRepair, int i_nDesParam, int i_nRequestAmountToRepair, ITEM *i_pBulletItem/*=NULL*/)
{
	if(i_nRequestAmountToRepair <= 0)
	{
		*o_pnRealAmountToRepair	= 0;
		return TRUE;
	}
	
	int nBundleCount			= 0;
	*o_pnRealAmountToRepair		= i_nRequestAmountToRepair;
	switch(i_nDesParam)
	{
	case DES_HP:
		*o_pnCost = COST_HP_REPAIR_PER_1HP * i_nRequestAmountToRepair;
		break;
	case DES_DP:
		*o_pnCost = COST_DP_REPAIR_PER_1DP * i_nRequestAmountToRepair;
		break;
	case DES_EP:
		*o_pnCost = COST_EP_REPAIR_PER_1EP * i_nRequestAmountToRepair;
		break;
	case DES_SP:
		*o_pnCost = COST_SP_REPAIR_PER_1SP * i_nRequestAmountToRepair;
		break;
	case DES_BULLET_01:
	case DES_BULLET_02:
		nBundleCount			= i_nRequestAmountToRepair/i_pBulletItem->MinTradeQuantity;		// 묵음 카운트
		if(0 != i_nRequestAmountToRepair%i_pBulletItem->MinTradeQuantity)
		{
			nBundleCount++;		// 회복량이 MinTradeQuantity으로 나머지 연산이 0이 아이면 1을 추가한다.
		}
		*o_pnRealAmountToRepair	= nBundleCount * i_pBulletItem->MinTradeQuantity;
		*o_pnCost				= nBundleCount * i_pBulletItem->Price;
		break;
	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

enumAttackToTarget CAtumSJ::GetAttackToTarget(ClientIndex_t i_AttackIndex, MEX_TARGET_INFO &i_MexTargetInfo)
{
	return GetAttackToTarget(i_AttackIndex, i_MexTargetInfo.TargetIndex, i_MexTargetInfo.TargetItemFieldIndex);
}

enumAttackToTarget CAtumSJ::GetAttackToTarget(ClientIndex_t i_AttackIndex, ClientIndex_t i_TargetIndex, UINT i_TargetItemFieldIndex)
{
	if (i_AttackIndex == i_TargetIndex)
	{
		return ERR2ERR;
	}

	if (IS_CHARACTER_CLIENT_INDEX(i_AttackIndex))
	{
		if (IS_CHARACTER_CLIENT_INDEX(i_TargetIndex) && i_TargetItemFieldIndex == 0)
		{
			return C2C;
		}
		else if (IS_CHARACTER_CLIENT_INDEX(i_TargetIndex) && i_TargetItemFieldIndex != 0)
		{
			return C2CI;
		}
		else if (IS_MONSTER_CLIENT_INDEX(i_TargetIndex) && i_TargetItemFieldIndex == 0)
		{
			return C2M;
		}
		else if (i_TargetIndex == 0 && i_TargetItemFieldIndex != 0)
		{
			return C2I;
		}
		else if (i_TargetIndex == 0 && i_TargetItemFieldIndex == 0)
		{
			return C2NULL;
		}
		else
		{
// 2005-04-25 by cmkwon
//			ASSERT_NEVER_GET_HERE();
			return ERR2ERR;
		}
	}
	else if (IS_MONSTER_CLIENT_INDEX(i_AttackIndex))
	{
		if (IS_CHARACTER_CLIENT_INDEX(i_TargetIndex) && i_TargetItemFieldIndex == 0)
		{
			return M2C;
		}
		else if (IS_CHARACTER_CLIENT_INDEX(i_TargetIndex) && i_TargetItemFieldIndex != 0)
		{
			return M2CI;
		}
		else if (IS_MONSTER_CLIENT_INDEX(i_TargetIndex) && i_TargetItemFieldIndex == 0)
		{
// 2005-04-25 by cmkwon
//			ASSERT_NEVER_GET_HERE();

// 2009-09-09 ~ 2010 by dhjin, 인피니티 - 밑과 같이 수정
//			return ERR2ERR;
			return M2M;
		}
		else if (i_TargetIndex == 0 && i_TargetItemFieldIndex != 0)
		{
			return M2I;
		}
		else if (i_TargetIndex == 0 && i_TargetItemFieldIndex == 0)
		{
			return M2NULL;
		}
		else
		{
// 2005-04-25 by cmkwon
//			ASSERT_NEVER_GET_HERE();
			return ERR2ERR;
		}
	}
	else
	{
// 2005-04-25 by cmkwon
//		ASSERT_NEVER_GET_HERE();
		return ERR2ERR;
	}
}

BOOL CAtumSJ::IsCharacterAttacker(enumAttackToTarget i_nAttackToTarget)
{
	return IS_IN_RANGE(C2C, i_nAttackToTarget, C2NULL);
}

BOOL CAtumSJ::IsMonsterAttacker(enumAttackToTarget i_nAttackToTarget)
{
	return IS_IN_RANGE(M2C, i_nAttackToTarget, M2NULL);
}

BOOL CAtumSJ::IsCharacterTarget(enumAttackToTarget i_nAttackToTarget)
{
	return (i_nAttackToTarget == C2C
			|| i_nAttackToTarget == C2CI
			|| i_nAttackToTarget == M2C
			|| i_nAttackToTarget == M2CI);
}

BOOL CAtumSJ::IsMonsterTarget(enumAttackToTarget i_nAttackToTarget)
{
	return (i_nAttackToTarget == C2M);
}

BOOL CAtumSJ::IsItemTarget(enumAttackToTarget i_nAttackToTarget)
{
	return (i_nAttackToTarget == C2I
			|| i_nAttackToTarget == M2I);
}

BOOL CAtumSJ::CheckReqItemKind(BYTE i_nReqItemKind, BYTE i_nTargetItemKind)
{
	return COMPARE_ITEMKIND(i_nReqItemKind, i_nTargetItemKind);
}

void CAtumSJ::GetAtumTime(AtumTime *o_pAtumTime)
{
	// 시간을 전송
	time_t ltime;
	struct tm *today = NULL;
	time(&ltime);
	today = localtime(&ltime);
	// 4시간 기준으로 지난 초
	AtumTime rTime(today->tm_hour, today->tm_min);
	o_pAtumTime->SetTime((rTime*6).Hour%24, (rTime*6).Minute);
}

INT64 CAtumSJ::GetCityWarTex(INT64 i_n64ItemPrice, float i_fTexPercent)
{
	return (INT64)((i_n64ItemPrice*i_fTexPercent)/100.0f);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			INT64 CAtumSJ::GetItemTexSPI(INT64 i_n64ItemPrice, float i_fTexPercent)
/// \brief		
/// \author		cmkwon
/// \date		2006-02-08 ~ 2006-02-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT64 CAtumSJ::GetItemTexSPI(INT64 i_n64ItemPrice, float i_fTexPercent)
{
	return (INT64)((i_n64ItemPrice*i_fTexPercent)/100.0f);
}

////////////////////////////////////////////////////////////////////////////////
// 2005-07-08 by cmkwon, 캐릭터 충돌시 데미지 계산을 위한 표
//엔진 속도	데미지 (HP+SD)
//80	0.1
//90	0.1
//100	0.1
//110	0.1
//120	0.1
//130	0.1
//140	0.1
//150	0.15
//160	0.15
//170	0.15
//180	0.15
//190	0.15
//200	0.15
//210	0.2
//220	0.2
//230	0.2
//240	0.2
//250	0.2
//260	0.2
//270	0.25
//280	0.25
//290	0.25
//300	0.25
//310	0.25
//320	0.25
//330	0.3
//340	0.3
//350	0.3
//360	0.3
//370	0.3
//380	0.3
//390	0.35
//400	0.35
//410	0.35
//420	0.35
//430	0.35
//440	0.35
//450	0.4
//460	0.4
//470	0.4
//480	0.4
//490	0.4
//500	0.4
//510	0.45
//520	0.45
//530	0.45
//540	0.45
//550	0.45
//560	0.45
//570	0.5
//580	0.5
//590	0.5
//600	0.5

float CAtumSJ::GetPenaltyCollisionBYSpeed(INT i_nCurSpeed)
{
	if(i_nCurSpeed < 150){				return 0.1f;}
	else if(i_nCurSpeed < 210){			return 0.15f;}
	else if(i_nCurSpeed < 270){			return 0.2f;}
	else if(i_nCurSpeed < 330){			return 0.25f;}
	else if(i_nCurSpeed < 390){			return 0.3f;}
	else if(i_nCurSpeed < 450){			return 0.35f;}
	else if(i_nCurSpeed < 510){			return 0.4f;}
	else if(i_nCurSpeed < 570){			return 0.45f;}

	return 0.5f;
}

// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - 인자추가(MapIndex_t i_nStartCityMapIdx)
MapIndex_t CAtumSJ::GetCityMapIndexByInfluence(BYTE i_byInfluence, MapIndex_t i_nStartCityMapIdx/*=VCN_CITY_MAP_INDEX*/)
{
// 2007-05-22 by cmkwon, 일반세력도시맵(아카데미맵) 구현으로 수정됨
//	if(COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_NORMAL)
//		|| COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_VCN))
//	{
//		return VCN_CITY_MAP_INDEX;
//	}

///////////////////////////////////////////////////////////////////////////////
// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - CAtumSJ::GetCityMapIndexByInfluence#
// 	if(COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_NORMAL))
// 	{// 2007-05-21 by cmkwon, 일반군 도시맵 추가로 수정됨
// 		return NORMAL_CITY_MAP_INDEX;
// 	}
// 	else if(COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_VCN))
// 	{
// 		return VCN_CITY_MAP_INDEX;
// 	}
// 	else if(COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_ANI))
// 	{
// 		return ANI_CITY_MAP_INDEX;
// 	}
	///////////////////////////////////////////////////////////////////////////////
	// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - CAtumSJ::GetCityMapIndexByInfluence#
	if(IS_VCN_INFLUENCE_TYPE(i_byInfluence))
	{
		return VCN_CITY_MAP_INDEX;
	}
	else if(IS_ANI_INFLUENCE_TYPE(i_byInfluence))
	{
		return ANI_CITY_MAP_INDEX;
	}
	else if(IS_NORMAL_INFLUENCE_TYPE(i_byInfluence))
	{
		if(ANI_CITY_MAP_INDEX == i_nStartCityMapIdx)
		{
			return ANI_CITY_MAP_INDEX;
		}
		return VCN_CITY_MAP_INDEX;	
	}
	return VCN_CITY_MAP_INDEX;	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - CAtumSJ::GetGargenMapIndexByInfluence# 추가
/// \author		cmkwon
/// \date		2009-10-13 ~ 2009-10-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
MapIndex_t CAtumSJ::GetGargenMapIndexByInfluence(BYTE i_byInfluence, MapIndex_t i_nStartCityMapIdx/*=VCN_CITY_MAP_INDEX*/)
{
	if(IS_VCN_INFLUENCE_TYPE(i_byInfluence)
		|| IS_NORMAL_INFLUENCE_TYPE(i_byInfluence))
	{
		return 3002;
	}
	
	if(IS_ANI_INFLUENCE_TYPE(i_byInfluence))
	{
		return 3018;
	}
	return 3002;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - CAtumSJ::IsOtherInfluenceMap#, 추가

/// \author		cmkwon
/// \date		2009-10-13 ~ 2009-10-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsOtherInfluenceMap(BYTE i_byInfluence, MapIndex_t i_nStartCityMapIdx, int i_nMapInflTy)
{
	MapIndex_t nCityMapIdx = CAtumSJ::GetCityMapIndexByInfluence(i_byInfluence, i_byInfluence);

	if( (COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_VCN) && IS_MAP_INFLUENCE_ANI(i_nMapInflTy))
		|| (COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_ANI) && IS_MAP_INFLUENCE_VCN(i_nMapInflTy)))
	{
		return TRUE;
	}

	if(COMPARE_INFLUENCE(i_byInfluence, INFLUENCE_TYPE_NORMAL))
	{
		if(IS_ANI_CITY_MAP_INDEX(i_nStartCityMapIdx))
		{
			if(IS_MAP_INFLUENCE_VCN(i_nMapInflTy)
				&& IS_MAP_INFLUENCE_CITY(i_nMapInflTy))
			{
				return TRUE;
			}

			if(IS_MAP_INFLUENCE_ANI(i_nMapInflTy)
				&& FALSE == IS_MAP_INFLUENCE_CITY(i_nMapInflTy))
			{
				return TRUE;
			}
		}
		else
		{
			if(IS_MAP_INFLUENCE_ANI(i_nMapInflTy))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-10-12 by cmkwon, 프리스카 제거 방안 적용 - CAtumSJ::IsSameCharacterInfluence8MapInfluence#, 추가
/// \author		cmkwon
/// \date		2009-10-13 ~ 2009-10-13
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsSameCharacterInfluence8MapInfluence(BYTE i_byInflTy, int i_nMapInflTy)
{
	if( (IS_VCN_INFLUENCE_TYPE(i_byInflTy) && IS_MAP_INFLUENCE_VCN(i_nMapInflTy))
		|| (IS_ANI_INFLUENCE_TYPE(i_byInflTy) && IS_MAP_INFLUENCE_ANI(i_nMapInflTy)) )
	{
		return TRUE;
	}

	if(IS_NORMAL_INFLUENCE_TYPE(i_byInflTy))
	{
		if(IS_MAP_INFLUENCE_CITY(i_nMapInflTy)
			|| IS_MAP_INFLUENCE_VCN(i_nMapInflTy))
		{
			return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			D3DXVECTOR3 CAtumSJ::GetRandomXZVec3(D3DXVECTOR3 *i_pVec3Center, int i_nRandomRidiusDistance)
/// \brief		
/// \author		cmkwon
/// \date		2005-07-29 ~ 2005-07-29
/// \warning	최소값은 10이다
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 CAtumSJ::GetRandomXZVec3(D3DXVECTOR3 *i_pVec3Center, int i_nRandomRadiusDistance)
{
	i_nRandomRadiusDistance = max(10, i_nRandomRadiusDistance);

	D3DXVECTOR3 retVec3(*i_pVec3Center);
	retVec3.x += RANDI(0, 2*i_nRandomRadiusDistance) - i_nRandomRadiusDistance;
	retVec3.z += RANDI(0, 2*i_nRandomRadiusDistance) - i_nRandomRadiusDistance;	
	return retVec3;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsAlphaNum(char i_cParam)
/// \brief		알파벳 혹은 숫자 
/// \author		cmkwon
/// \date		2005-10-26 ~ 2005-10-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsAlphaNum(char i_cParam)
{
	if( (i_cParam >= '0' && i_cParam <= '9')		// '0'=48, '9'=57
		|| (i_cParam >= 'A' && i_cParam <= 'Z')		// 'A'=65, 'Z'=90
		|| (i_cParam >= 'a' && i_cParam <= 'z') )	// 'a'=97, 'z'=122
	{
		return TRUE;
	}
	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			static BOOL CAtumSJ::IsValidCharacterName(char *i_szCharName, int i_nLanguageTy)
/// \brief		
/// \author		cmkwon
/// \date		2005-10-26 ~ 2005-10-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidCharacterName(char *i_szCharName, int i_nLanguageTy)
{
	int nLen = strlen(i_szCharName);
	if(nLen < SIZE_MIN_CHARACTER_NAME
		|| nLen >= SIZE_MAXUSE_CHARACTER_NAME		// 2008-03-24 by cmkwon, 14 Bytes 까지만 유효하다.
		|| nLen >= SIZE_MAX_CHARACTER_NAME)
	{
		return FALSE;
	}

	if(0 == strnicmp(i_szCharName, "sctest", 6)		// 2006-04-06 by cmkwon, 'sctest'로 시작하는 캐릭터명은 만들 수 없다
		|| 0 == strnicmp(i_szCharName, "gm", 2))	// 2006-04-12 by cmkwon, 'gm'로 시작하는 캐릭터명은 만들 수 없다
	{// 2006-04-12 by cmkwon - 모든 서버 버전에 적용, SQL 쿼리 혹은 SCAdminTool로 만 생성 가능함
		return FALSE;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2007-01-26 by cmkwon, 언더바('_')만으로 캐릭터명이 이루어져 있는지 체크
	BOOL bIsValid = FALSE;
	for(int i=0; i < nLen; i++)
	{
		if('_' != i_szCharName[i])
		{
			bIsValid = TRUE;
			break;
		}
	}
	if(FALSE == bIsValid)
	{// 2007-01-26 by cmkwon, 캐릭터명이 '_'만으로 되어있다
		return FALSE;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2007-12-05 by cmkwon, 캐릭터명 체크시 특수문자 체크 루틴 수정 - CAtumSJ::IsValidOneByteCharacter() 로 체크
	if(FALSE == CAtumSJ::IsValidOneByteCharacter(i_szCharName, i_nLanguageTy))
	{
		// 2007-12-05 by cmkwon, 1 Byte 문자가 허용되지 않은 문자가 있다
		return FALSE;
	}

// 2007-12-05 by cmkwon, 캐릭터명 체크시 특수문자 체크 루틴 수정 - 위와 같이 CAtumSJ::IsValidOneByteCharacter() 로 처리
//	///////////////////////////////////////////////////////////////////////////////
//	// 2007-10-22 by cmkwon, 캐릭터명 체크 - 사용 불가능 문제 체크< 공백(Space, ' '), 탭(Tap), 캐리지 리턴, 라인피드)
//	for(i=0; i < nLen; i++)
//	{
//		if(strchr(STR_INVALID_CHARACTER_NAME, i_szCharName[i]))
//		{
//			return FALSE;
//		}
//	}
//
//	char szSpecialCharacterString[] = "!@#$%^&*()+|~'[];/.,<>?:\"{}\\-`=";
//	switch(i_nLanguageTy)
//	{
//	case LANGUAGE_TYPE_KOREAN:		// 한글		- 특수 문자만 체크, 언더바('_') 제외
//	case LANGUAGE_TYPE_JAPANESE:	// 일어		- 특수 문자만 체크, 언더바('_') 제외
//	case LANGUAGE_TYPE_CHINESE:		// Chinese	- 특수 문자만 체크, 언더바('_') 제외
//		{
//			if(strpbrk(i_szCharName, szSpecialCharacterString))
//			{
//				return FALSE;
//			}
//		}
//		break;
//	case LANGUAGE_TYPE_ENGLISH:		// 영어		- 1Byte씩 체크(알파벳, 숫자만 가능)
//		{
//			for(int i=0; i < nLen; i++)
//			{
//				if(FALSE == CAtumSJ::IsAlphaNum(i_szCharName[i]))		// 알파벳, 숫자 체크
//				{
//					return FALSE;
//				}
//			}
//		}
//		break;
//	case LANGUAGE_TYPE_VIETNAMESE:	// Vietnamse- 1Byte씩 체크(알파벳, 숫자, 언더바('_')만 가능)
//		{
//			for(int i=0; i < nLen; i++)
//			{
//				if(FALSE == CAtumSJ::IsAlphaNum(i_szCharName[i])		// 알파벳, 숫자 체크
//					&& '_' != i_szCharName[i])
//				{
//					return FALSE;
//				}
//			}
//		}
//		break;
//	default:
//		{
//			return FALSE;
//		}
//	}

	return IsValidAllLetter(i_szCharName, i_nLanguageTy);		// 2007-05-04 by cmkwon, 허용 문자 리스트 체크
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			static BOOL CAtumSJ::IsValidGuildName(char *i_szGuildName, int i_nLanguageTy)
/// \brief		
/// \author		cmkwon
/// \date		2005-10-26 ~ 2005-10-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidGuildName(char *i_szGuildName, int i_nLanguageTy)
{
	int nLen = strlen(i_szGuildName);
	if(nLen <= 0
		|| nLen >= SIZE_MAX_GUILD_NAME)
	{
		return FALSE;
	}

	///////////////////////////////////////////////////////////////////////////////
	// 2007-10-22 by cmkwon, 여단명 체크 - 시작, 마지막 문자로 사용 불가능 문제 체크
	if(strchr(STR_INVALID_PRE8SUFFIX_GUILD_NAME, i_szGuildName[0])
		|| strchr(STR_INVALID_PRE8SUFFIX_GUILD_NAME, i_szGuildName[nLen-1]))
	{
		return FALSE;
	}
	
	// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [언어-필수] 추가 언어의 GuildName 체크 루틴에 추가

	char szSpecialCharacterString[] = "!@#$%^&*()+|~'[];/.,<>?:\"{}\\-`=";
	switch(i_nLanguageTy)
	{
	case LANGUAGE_TYPE_KOREAN:		// 한글		- 특수 문자만 체크, 언더바('_') 제외
// 2009-01-19 by cmkwon, 일본 유효한 캐릭터명, 여단명 체크 - 아래에 시스템 구축함.
//	case LANGUAGE_TYPE_JAPANESE:	// 2008-12-03 by cmkwon, 지원 서비스 추가(일본 Arario_Jpn) - 일어		- 특수 문자만 체크, 언더바('_') 제외
	case LANGUAGE_TYPE_CHINESE:		// Chinese	- 특수 문자만 체크, 언더바('_') 제외
	case LANGUAGE_TYPE_TAIWANESE:	// 2008-09-23 by cmkwon, 지원 서비스 추가(대만 Netpower_Tpe) - // Taiwanese	- 특수 문자만 체크, 언더바('_') 제외, 
		{
			if(strpbrk(i_szGuildName, szSpecialCharacterString))
			{
				return FALSE;
			}
		}
		break;
	case LANGUAGE_TYPE_INDONESIA:
	case LANGUAGE_TYPE_ENGLISH:		// 영어		- 1Byte씩 체크(알파벳, 숫자, 언더바('_')만 가능)
	case LANGUAGE_TYPE_VIETNAMESE:	// Vietnamse- 1Byte씩 체크(알파벳, 숫자, 언더바('_')만 가능)
		{			
			for(int i=0; i < nLen; i++)
			{
				if(FALSE == CAtumSJ::IsAlphaNum(i_szGuildName[i])		// 알파벳, 숫자 체크
					&& '_' != i_szGuildName[i])
				{
					return FALSE;
				}
			}
		}
		break;
	case LANGUAGE_TYPE_RUSSIAN:		// 2008-05-29 by cmkwon, 지원 서비스 추가(Innova_Rus 러시아어 추가) - GuildName 체크, 일단 LANGUAGE_TYPE_ENGLISH 와 동일하게 처리
		{			
			for(int i=0; i < nLen; i++)
			{
				if(FALSE == CAtumSJ::IsValidRussianChar(i_szGuildName[i]))
				{
					return FALSE;
				}
			}
		}
		break;
	case LANGUAGE_TYPE_THAI:		// 2008-05-14 by cmkwon, WinnerOinke_Tha CharacterName 체크 수정 - 영문자 || 태국어 || _ 만 사용 가능, // 2008-05-02 by cmkwon, WinnerOnline_Tha 추가하기 - GuildName 체크, 일단 LANGUAGE_TYPE_ENGLISH 와 동일하게 처리
		{
			for(int i=0; i < nLen; i++)
			{
				if(IsDBCSLeadByte(i_szGuildName[i]))
				{// 2008-05-14 by cmkwon, 2 Bytes 문자는 무조건 FALSE
					return FALSE;
				}
				
				if(FALSE == CAtumSJ::IsAlphaNum(i_szGuildName[i])		// 알파벳, 숫자 체크
					&& '_' != i_szGuildName[i])
				{
					if(FALSE == CAtumSJ::IsValidThaiChar(i_szGuildName[i]))
					{
						return FALSE;
					}
				}
			}
		}
		break;
	case LANGUAGE_TYPE_GERMAN:		// 2008-07-21 by cmkwon, Gameforge4D_Deu CharacterName, GuildName 체크 수정 - , // 2008-04-25 by cmkwon, 지원 언어에 독일어 추가 - GuildName 체크, 일단 LANGUAGE_TYPE_ENGLISH 와 동일하게 처리
		{
			for(int i=0; i < nLen; i++)
			{
				if(FALSE == CAtumSJ::IsAlphaNum(i_szGuildName[i])		// 알파벳, 숫자 체크
					&& '_' != i_szGuildName[i])
				{
					if(FALSE == CAtumSJ::IsValidGermanChar(i_szGuildName[i]))
					{
						return FALSE;
					}
				}
			}
		}
		break;
	case LANGUAGE_TYPE_TURKISH:		// 2008-12-26 by cmkwon, 터키 서비스 지원 관련 추가 - 일단 체크 없음
		{

// 2009-02-10 by cmkwon, Gameforge4D (터키) 캐릭터명, 여단명 체크 - 아래와 같이 CAtumSJ::IsValidTurkishChar() 에서 체크
// 			// 2009-01-23 by cmkwon, 터키 i,I 문자 문제 처리 - 여단명에 알파벳, 숫자만 가능
// 			for(int i=0; i < nLen; i++)
// 			{
// 				if(FALSE == CAtumSJ::IsAlphaNum(i_szGuildName[i]))		// 알파벳, 숫자 체크
// 				{
// 					return FALSE;
// 				}
// 			}
			char *pCurChar = i_szGuildName;
			while(pCurChar && pCurChar < i_szGuildName + nLen)
			{
				if(FALSE == CAtumSJ::IsValidTurkishChar(*pCurChar))		// 2009-02-10 by cmkwon, Gameforge4D (터키) 캐릭터명, 여단명 체크 - 여단명 체크
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_ITALIAN:		// 2009-01-13 by cmkwon, 이탈리아 서비스 지원 관련 추가 - CAtumSJ::IsValidGuildName() 임시로 체크 없음
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-02-24 by cmkwon, Gameforge4D (이탈리아) 캐릭터명, 여단명 체크 - 
			char *pCurChar = i_szGuildName;
			while(pCurChar && pCurChar < i_szGuildName + nLen)
			{
				if(FALSE == CAtumSJ::IsValidItalianChar(*pCurChar))		// 2009-02-24 by cmkwon, Gameforge4D (이탈리아) 캐릭터명, 여단명 체크 - 여단명 체크
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_JAPANESE:	// 2009-01-19 by cmkwon, 일본 유효한 캐릭터명, 여단명 체크 - 여단명 체크
		{

			// 2009-01-21 by cmkwon, 유효한 여단명 체크시에 욕설, 금지어도 체크 추가 - 일본은 캐릭터명 체크와 동일하게
			if(0 == strnicmp(i_szGuildName, "sctest", 6)
				|| 0 == strnicmp(i_szGuildName, "gm", 2))
			{
				return FALSE;
			}

			char *pCurChar = i_szGuildName;
			while(pCurChar && pCurChar < i_szGuildName + nLen)
			{
				if(FALSE == CAtumSJ::IsValidOneByteCharForJapanese(*pCurChar))
				{
					return FALSE;
				}
				
				pCurChar = CharNext(pCurChar);		// 2007-12-05 by cmkwon, 다음 문자로 이동
			}
		}
		break;
	case LANGUAGE_TYPE_FRENCH:		// 2009-03-03 by cmkwon, 지원 서비스 추가(Gameforge4D 프랑스어 관련) - 여단명 체크, 현재는 체크 없음
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-03-12 by cmkwon, Gameforge4D (프랑스어) 캐릭터명, 여단명 체크 - 여단명 체크
			char *pCurChar = i_szGuildName;
			while(pCurChar && pCurChar < i_szGuildName + nLen)
			{
				if(FALSE == CAtumSJ::IsValidFrenchChar(*pCurChar))
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_POLISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 현재는 영어와 숫자만 가능
			// 2009-06-18 by cmkwon, Gameforge4D (폴란드) 캐릭터명, 여단명 체크 수정 - 
			char *pCurChar = i_szGuildName;
			while(pCurChar && pCurChar < i_szGuildName + nLen)
			{
				if(FALSE == CAtumSJ::IsValidPolishChar(*pCurChar))	// 2009-06-18 by cmkwon, Gameforge4D (폴란드) 캐릭터명, 여단명 체크 수정 - 
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_SPANISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 현재는 영어와 숫자만 가능
			// 2009-07-10 by cmkwon, Gameforge4D 스페인 서비스 시작 준비 - 캐릭터명, 여단명 체크 수정
			char *pCurChar = i_szGuildName;
			while(pCurChar && pCurChar < i_szGuildName + nLen)
			{
				if(FALSE == CAtumSJ::IsValidSpanishChar(*pCurChar))	// 2009-07-10 by cmkwon, Gameforge4D 스페인 서비스 시작 준비 - 캐릭터명, 여단명 체크 수정
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	return IsValidAllLetter(i_szGuildName, i_nLanguageTy);		// 2007-05-04 by cmkwon, 허용 문자 리스트 체크
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidAllLetter(char *i_szSource, int i_nLanguageTy)
/// \brief		
/// \author		cmkwon
/// \date		2007-05-04 ~ 2007-05-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidAllLetter(char *i_szSource, int i_nLanguageTy)
{
	if(g_setAllLetterList.empty())
	{// 2007-05-07 by cmkwon, 비어 있으면 무조건 참을 리턴함
		return TRUE;
	}

	// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [언어-필수] 추가 언어일때 CharacterName 에 유효한 문자 체크 루틴에 추가

	switch(i_nLanguageTy)
	{
// 2009-01-19 by cmkwon, 일본 유효한 캐릭터명, 여단명 체크 - 아래에 시스템 구축 함
//	case LANGUAGE_TYPE_JAPANESE:	// 일어		- 
	case LANGUAGE_TYPE_ENGLISH:		// 영어		- 
	case LANGUAGE_TYPE_VIETNAMESE:	// Vietnamse- 
	case LANGUAGE_TYPE_GERMAN:		// 2008-04-25 by cmkwon, 지원 언어에 독일어 추가 - CharacterName 체크, 일단 LANGUAGE_TYPE_ENGLISH 와 동일하게 처리
	case LANGUAGE_TYPE_THAI:		// 2008-05-14 by cmkwon, WinnerOinke_Tha CharacterName 체크 수정 - 여기는 체크 필요 없음, // 2008-05-02 by cmkwon, WinnerOnline_Tha 추가하기 - CharacterName 체크, 일단 LANGUAGE_TYPE_ENGLISH 와 동일하게 처리
	case LANGUAGE_TYPE_RUSSIAN:		// 2008-05-29 by cmkwon, 지원 서비스 추가(Innova_Rus 러시아어 추가) - CharacterName 체크, 일단 LANGUAGE_TYPE_ENGLISH 와 동일하게 처리
	case LANGUAGE_TYPE_TURKISH:		// 2008-12-26 by cmkwon, 터키 서비스 지원 관련 추가 - 일단 체크 없음
	case LANGUAGE_TYPE_ITALIAN:		// 2009-01-13 by cmkwon, 이탈리아 서비스 지원 관련 추가 - CAtumSJ::IsValidAllLetter() 임시로 체크 없음
	case LANGUAGE_TYPE_FRENCH:		// 2009-03-03 by cmkwon, 지원 서비스 추가(Gameforge4D 프랑스어 관련) - 캐릭터명 2byte 문자 체크, 현재는 체크 없음
	case LANGUAGE_TYPE_POLISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
	case LANGUAGE_TYPE_SPANISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
	case LANGUAGE_TYPE_INDONESIA:
		break;
	case LANGUAGE_TYPE_KOREAN:		// 한글		- 
	case LANGUAGE_TYPE_CHINESE:		// Chinese	- 
	case LANGUAGE_TYPE_TAIWANESE:	// 2008-09-23 by cmkwon, 지원 서비스 추가(대만 Netpower_Tpe) - // Taiwanese	- 
	case LANGUAGE_TYPE_JAPANESE:	// 2009-01-19 by cmkwon, 일본 유효한 캐릭터명, 여단명 체크 - 캐릭터명,여단명 체크 (2 Bytes 문자 체크)
		{
			int nLen = strlen(i_szSource);
			for(int i=0; i < nLen; i++)
			{
				if(IsDBCSLeadByte(i_szSource[i]))
				{// 2007-05-04 by cmkwon, 2Bytes 문자만 체크한다 - 영문자, 기본특수문자 제외

					char szTmp[10];
					MEMSET_ZERO(szTmp, 10);
					memcpy(szTmp, &i_szSource[i], 2);

					///////////////////////////////////////////////////////////////////////////////
					// 2007-05-04 by cmkwon, 허용문자리스트에서 찾아본다
					setString::iterator itr = g_setAllLetterList.find(szTmp);
					if(itr == g_setAllLetterList.end())
					{
						return FALSE;
					}
					i++;		// 2007-05-04 by cmkwon, 
					continue;
				}
			}
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::LoadAllLetterList(const char *i_szFilePath)
/// \brief		
/// \author		cmkwon
/// \date		2007-05-04 ~ 2007-05-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::LoadAllLetterList(const char *i_szFilePath)
{
	const int SIZE_BUFF = 1024;
	char buff[SIZE_BUFF];

	ifstream fin;
	fin.open(i_szFilePath);

	if (! fin.is_open())
	{
		return FALSE;
	}

	while(TRUE)
	{
		memset(buff, 0x00, SIZE_BUFF);
		BOOL bFlagFileEnd = fin.getline(buff, SIZE_BUFF).eof();
		if(bFlagFileEnd == TRUE && strcmp(buff, "") == 0)
		{
			break;
		}

		if (strncmp(buff, "#", 1) == 0
			|| strncmp(buff, "$", 1) == 0)
		{	// ignore blank lines
			// ignore comments
			// ignore user defined variables

			continue;
		}

		int nLen = strlen(buff);
		for(int i=0; i < nLen; i++)
		{
			if(IsDBCSLeadByte(buff[i]))
			{
				char szTmp[10];
				MEMSET_ZERO(szTmp, 10);
				memcpy(szTmp, &buff[i], 2);

				g_setAllLetterList.insert(szTmp);
				i++;
				continue;
			}
		}
	}
	fin.close();

#ifdef _ATUM_SERVER
	char szSysLog[1024];
	sprintf(szSysLog,"  [Notify] CAtumSJ::LoadAllLetterList, Total letter [%6d]counts\r\n", g_setAllLetterList.size());
	g_pGlobal->WriteSystemLogEX(TRUE, szSysLog);
#endif
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidOneByteCharacter(char *i_szSource, int i_nLanguageTy)
/// \brief		// 2007-12-05 by cmkwon, 캐릭터명 체크시 특수문자 체크 루틴 수정 - CAtumSJ::IsValidOneByteCharacter() 추가
/// \author		cmkwon
/// \date		2007-12-05 ~ 2007-12-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidOneByteCharacter(char *i_szSource, int i_nLanguageTy)
{
	// 2008-04-25 by cmkwon, 지원 언어/서비스 추가시 꼭 추가 되어야 하는 사항 - [언어-필수] 추가 언어시에 CharacterName 에 1Byte 문자 체크 루틴에 추가

	int nLen = strlen(i_szSource);
	switch(i_nLanguageTy)
	{
	case LANGUAGE_TYPE_KOREAN:		// 한글		- 특수 문자 언더바('_')만 제외
// 2008-12-09 by cmkwon, 일본 Arario 캐릭터명,여단명에 특수 문자만 제외 - 
//	case LANGUAGE_TYPE_JAPANESE:	// 2008-12-03 by cmkwon, 지원 서비스 추가(일본 Arario_Jpn) - // 일어		- 특수 문자 언더바('_')만 제외
	case LANGUAGE_TYPE_CHINESE:		// Chinese	- 특수 문자 언더바('_')만 제외
	case LANGUAGE_TYPE_TAIWANESE:	// 2008-09-23 by cmkwon, 지원 서비스 추가(대만 Netpower_Tpe) - // Taiwanese	- 특수 문자 언더바('_')만 제외
		{
			char *pCurChar = i_szSource;
			while(pCurChar && pCurChar < i_szSource + nLen)
			{
				if(FALSE == IsDBCSLeadByte(*pCurChar)			// 1 Byte 문자인지 체크
					&& FALSE == CAtumSJ::IsAlphaNum(*pCurChar)	// 영문자, 숫자가 아니다
					&& '_' != *pCurChar)						// '_' 가 아니다
				{
					return FALSE;
				}
				
				pCurChar = CharNext(pCurChar);		// 2007-12-05 by cmkwon, 다음 문자로 이동
			}
		}
		break;
	case LANGUAGE_TYPE_ENGLISH:		// 영어		- 1Byte씩 체크(알파벳, 숫자만 가능)
	case LANGUAGE_TYPE_INDONESIA:
		{
			for(int i=0; i < nLen; i++)
			{
				if(FALSE == CAtumSJ::IsAlphaNum(i_szSource[i])		// 알파벳, 숫자 체크
					&& '_' != i_szSource[i])						// 2008-08-05 by cmkwon, English 캐릭터명에 알파벳, 숫자, 언더바('_')만 가능하게 수정, 언더바 추가함.
				{
					return FALSE;
				}
			}
		}
		break;
	case LANGUAGE_TYPE_VIETNAMESE:	// Vietnamse- 1Byte씩 체크(알파벳, 숫자, 언더바('_')만 가능)
		{
			for(int i=0; i < nLen; i++)
			{
				if(FALSE == CAtumSJ::IsAlphaNum(i_szSource[i])		// 알파벳, 숫자 체크
					&& '_' != i_szSource[i])
				{
					return FALSE;
				}
			}
		}
		break;
	case LANGUAGE_TYPE_GERMAN:		// 2008-07-21 by cmkwon, Gameforge4D_Deu CharacterName, GuildName 체크 수정 - , // 2008-04-25 by cmkwon, 지원 언어에 독일어 추가 - CharacterName 체크, 일단 모두 유효하게 처리
		{
			for(int i=0; i < nLen; i++)
			{
				if(FALSE == CAtumSJ::IsAlphaNum(i_szSource[i])		// 알파벳, 숫자 체크
					&& '_' != i_szSource[i])
				{
					if(FALSE == CAtumSJ::IsValidGermanChar(i_szSource[i]))
					{
						return FALSE;
					}
				}
			}
		}
		break;
	case LANGUAGE_TYPE_THAI:		// 2008-05-14 by cmkwon, WinnerOinke_Tha CharacterName 체크 수정 - 영문자 || 태국어 || _ 만 사용 가능, // 2008-05-02 by cmkwon, WinnerOnline_Tha 추가하기 - CharacterName 체크, 일단 모두 유효하게 처리
		{
			for(int i=0; i < nLen; i++)
			{
				if(IsDBCSLeadByte(i_szSource[i]))
				{// 2008-05-14 by cmkwon, 2 Bytes 문자는 무조건 FALSE
					return FALSE;
				}

				if(FALSE == CAtumSJ::IsAlphaNum(i_szSource[i])		// 알파벳, 숫자 체크
					&& '_' != i_szSource[i])
				{
					if(FALSE == CAtumSJ::IsValidThaiChar(i_szSource[i]))
					{
						return FALSE;
					}
				}
			}
		}
		break;
	case LANGUAGE_TYPE_RUSSIAN:		// 2008-05-29 by cmkwon, 지원 서비스 추가(Innova_Rus 러시아어 추가) - CharacterName 체크, 일단 모두 유효하게 처리
		{
			for(int i=0; i < nLen; i++)
			{
				if(FALSE == CAtumSJ::IsValidRussianChar(i_szSource[i]))
				{
					return FALSE;
				}
			}
		}
		break;
	case LANGUAGE_TYPE_JAPANESE:	// 2008-12-09 by cmkwon, 일본 Arario 캐릭터명,여단명에 특수 문자만 제외 - 
		{
			// 2009-01-19 by cmkwon, 일본 유효한 캐릭터명, 여단명 체크 - 1bytest 문자 체크(영어, 숫자, 일본 반각 가다가나만 허용, '_'는 제외됨)
			char *pCurChar = i_szSource;
			while(pCurChar && pCurChar < i_szSource + nLen)
			{
				if(FALSE == CAtumSJ::IsValidOneByteCharForJapanese(*pCurChar) )
				{
					return FALSE;
				}
				
				pCurChar = CharNext(pCurChar);		// 2007-12-05 by cmkwon, 다음 문자로 이동
			}
		}
		break;
	case LANGUAGE_TYPE_TURKISH:		// 2008-12-26 by cmkwon, 터키 서비스 지원 관련 추가 - 일단 체크 없음
		{
// 2009-02-10 by cmkwon, Gameforge4D (터키) 캐릭터명, 여단명 체크 - 아래와 같이 CAtumSJ::IsValidTurkishChar() 에서 체크
// 			// 2009-01-23 by cmkwon, 터키 i,I 문자 문제 처리 - 캐릭터명 체크, 영문자, 숫자만 가능
// 			for(int i=0; i < nLen; i++)
// 			{
// 				if(FALSE == CAtumSJ::IsAlphaNum(i_szSource[i]))		// 알파벳, 숫자 체크
// 				{
// 					return FALSE;
// 				}
// 			}
			char *pCurChar = i_szSource;
			while(pCurChar && pCurChar < i_szSource + nLen)
			{
				if(FALSE == CAtumSJ::IsValidTurkishChar(*pCurChar))		// 2009-02-10 by cmkwon, Gameforge4D (터키) 캐릭터명, 여단명 체크 - 캐릭터명 체크
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_ITALIAN:		// 2009-01-13 by cmkwon, 이탈리아 서비스 지원 관련 추가 - CAtumSJ::IsValidOneByteCharacter() 임시로 체크 없음
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-02-24 by cmkwon, Gameforge4D (이탈리아) 캐릭터명, 여단명 체크 - 
			char *pCurChar = i_szSource;
			while(pCurChar && pCurChar < i_szSource + nLen)
			{
				if(FALSE == CAtumSJ::IsValidItalianChar(*pCurChar))		// 2009-02-24 by cmkwon, Gameforge4D (이탈리아) 캐릭터명, 여단명 체크 - 캐릭터명 체크
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_FRENCH:		// 2009-03-03 by cmkwon, 지원 서비스 추가(Gameforge4D 프랑스어 관련) - 캐릭터명 체크, 현재는 체크 없음
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-03-12 by cmkwon, Gameforge4D (프랑스어) 캐릭터명, 여단명 체크 - 캐릭터명 체크
			char *pCurChar = i_szSource;
			while(pCurChar && pCurChar < i_szSource + nLen)
			{
				if(FALSE == CAtumSJ::IsValidFrenchChar(*pCurChar))
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_POLISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 임시로 영어,숫자만 가능
			// 2009-06-18 by cmkwon, Gameforge4D (폴란드) 캐릭터명, 여단명 체크 수정 - 
			char *pCurChar = i_szSource;
			while(pCurChar && pCurChar < i_szSource + nLen)
			{
				if(FALSE == CAtumSJ::IsValidPolishChar(*pCurChar))	// 2009-06-18 by cmkwon, Gameforge4D (폴란드) 캐릭터명, 여단명 체크 수정 - 
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	case LANGUAGE_TYPE_SPANISH:		// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 
		{
			///////////////////////////////////////////////////////////////////////////////
			// 2009-06-04 by cmkwon, 지원 서비스 추가(Gameforge4D 폴란드어, 스페인어) - 임시로 영어,숫자만 가능
			// 2009-07-10 by cmkwon, Gameforge4D 스페인 서비스 시작 준비 - 캐릭터명, 여단명 체크 수정
			char *pCurChar = i_szSource;
			while(pCurChar && pCurChar < i_szSource + nLen)
			{
				if(FALSE == CAtumSJ::IsValidSpanishChar(*pCurChar))		// 2009-07-10 by cmkwon, Gameforge4D 스페인 서비스 시작 준비 - 캐릭터명, 여단명 체크 수정
				{
					return FALSE;
				}				
				pCurChar = CharNext(pCurChar);
			}
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidThaiChar(char i_char)
/// \brief		// 2008-05-14 by cmkwon, WinnerOinke_Tha CharacterName 체크 수정 - 
/// \author		cmkwon
/// \date		2008-05-14 ~ 2008-05-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidThaiChar(char i_char)
{
	if(0xA1 <= (BYTE)i_char && 0xAF >= (BYTE)i_char)
	{
		return TRUE;
	}
	if(0xB0 <= (BYTE)i_char && 0xBF >= (BYTE)i_char)
	{
		return TRUE;
	}
	if(0xC0 <= (BYTE)i_char && 0xCF >= (BYTE)i_char)
	{
		return TRUE;
	}
	if(0xD0 <= (BYTE)i_char && 0xDA >= (BYTE)i_char)
	{
		return TRUE;
	}
	if(0xDF == (BYTE)i_char)
	{
		return TRUE;
	}
	if(0xE0 <= (BYTE)i_char && 0xED >= (BYTE)i_char)
	{
		return TRUE;
	}
	if(0xF0 <= (BYTE)i_char && 0xFA >= (BYTE)i_char)
	{
		return TRUE;
	}

	// 0xEE, 0xEF, 0xFB 는 키보드로 입력 불가 Character 임.

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidGermanChar(char i_char)
/// \brief		// 2008-07-21 by cmkwon, Gameforge4D_Deu CharacterName, GuildName 체크 수정 - 
/// \author		cmkwon
/// \date		2008-07-21 ~ 2008-07-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidGermanChar(char i_char)
{
	if(IsAlphaNum(i_char))
	{
		return TRUE;
	}

	switch((BYTE)i_char)
	{
	case 0xC4:		//	C4	196	?	196	LATIN CAPITAL LETTER A WITH DIAERESIS
	case 0xD6:		//	D6	214	?	214	LATIN CAPITAL LETTER O WITH DIAERESIS
	case 0xDC:		//	DC	220	?	220	LATIN CAPITAL LETTER U WITH DIAERESIS
	case 0xE4:		//	E4	228	?	228	LATIN SMALL LETTER A WITH DIAERESIS
	case 0xF6:		//	F6	246	?	246	LATIN SMALL LETTER O WITH DIAERESIS
	case 0xFC:		//	FC	252	?	252	LATIN SMALL LETTER U WITH DIAERESIS
		{
			return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidRussianChar(char i_char)
/// \brief		Innova CharacterName, GuildName 체크 수정 - 
/// \author		dhjin
/// \date		2008-08-14 ~ 2008-08-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidRussianChar(char i_char)
{
	if(IsAlphaNum(i_char))
	{
		return TRUE;
	}
	
	if(0xC0 <= (BYTE)i_char && 0xFF >= (BYTE)i_char)
	{
		return TRUE;
	}

	if(0xA8 == (BYTE)i_char || 0xB8 == (BYTE)i_char)
	{
		return TRUE;
	}

	return FALSE;
}



///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidOneByteCharForJapanese(char i_char)
/// \brief		// 2009-01-19 by cmkwon, 일본 유효한 캐릭터명, 여단명 체크 - CAtumSJ::IsValidJapaneseHalfwidthChar(), 반각 가다가나 체크
/// \author		cmkwon
/// \date		2009-01-19 ~ 2009-01-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidOneByteCharForJapanese(char i_char)
{
	if(IsDBCSLeadByte(i_char))
	{
		return TRUE;	// 2 Bytes 문자는 TRUE를 리턴
	}
	
	// 영문자, 숫자 체크	
	if(CAtumSJ::IsAlphaNum(i_char))
	{
		return TRUE;
	}
		
	// HalfwidthChar
	// total 57 count
	// A6 ~ AF	==> 10
	// B1 ~ BF	==> 15 (0xB0 제외)
	// C0 ~ CF	==> 16
	// D0 ~ DF	==> 16
	if(0xB0 != (BYTE)i_char
		&& IS_IN_RANGE(0xA6, (BYTE)i_char, 0xDF))
	{
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidTurkishChar(char i_char)
/// \brief		// 2009-02-10 by cmkwon, Gameforge4D (터키) 캐릭터명, 여단명 체크 - 
/// \author		cmkwon
/// \date		2009-02-10 ~ 2009-02-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidTurkishChar(char i_char)
{
	if(IsDBCSLeadByte(i_char))
	{
		return FALSE;	// 2 Bytes 문자는 FALSE를 리턴
	}

	// 영문자, 숫자 체크	
	if(CAtumSJ::IsAlphaNum(i_char))
	{
		return TRUE;
	}

	// 2009-02-10 by cmkwon, 나머지 터키문자 체크
	switch((BYTE)i_char)
	{
	case 0xD0:		// ~G
	case 0xDD:		// I
	case 0xDE:		// S.
	case 0xF0:		// ~g
	case 0xFD:		// i
	case 0xFE:		// s.
		return TRUE;
	}
	
	return FALSE;	// 나머지는 FALSE 를 리턴
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidItalianChar(char i_char)
/// \brief		// 2009-02-24 by cmkwon, Gameforge4D (이탈리아) 캐릭터명, 여단명 체크 - 
/// \author		cmkwon
/// \date		2009-02-24 ~ 2009-02-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidItalianChar(char i_char)
{
	if(IsDBCSLeadByte(i_char))
	{
		return FALSE;	// 2 Bytes 문자는 FALSE를 리턴
	}

	// 영문자, 숫자 체크	
	if(CAtumSJ::IsAlphaNum(i_char))
	{
		return TRUE;
	}

	// 2009-02-24 by cmkwon, 나머지 이탈리아 문자
	switch((BYTE)i_char)
	{
	case 0xC0:		// 
	case 0xC8:		// 
	case 0xC9:		// 
	case 0xD2:		// 
	case 0xD9:		// 
	case 0xE0:		// 
	case 0xE8:		// 
	case 0xE9:		// 
	case 0xF2:		// 
	case 0xF9:		// 
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-03-12 by cmkwon, Gameforge4D (프랑스어) 캐릭터명, 여단명 체크 - 
/// \author		cmkwon
/// \date		2009-03-12 ~ 2009-03-12
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidFrenchChar(char i_char)
{
	if(IsDBCSLeadByte(i_char))
	{
		return FALSE;	// 2 Bytes 문자는 FALSE를 리턴
	}
	
	// 영문자, 숫자 체크	
	if(CAtumSJ::IsAlphaNum(i_char))
	{
		return TRUE;
	}
	
	// 2009-03-12 by cmkwon, 나머지 프랑스어 문자
	switch((BYTE)i_char)
	{
	case 0xC0:		// 
	case 0xC2:		// 
	case 0xC6:		// 
	case 0xC7:		// 
	case 0xC8:		// 
	case 0xC9:		// 
	case 0xCA:		// 
	case 0xCB:		// 
	case 0xCE:		// 
	case 0xCF:		// 

	case 0xD4:		// 
	case 0xD9:		// 
	case 0xDB:		// 
	case 0xDC:		// 

	case 0xE0:		// 
	case 0xE2:		// 
	case 0xE6:		// 
	case 0xE7:		// 
	case 0xE8:		// 
	case 0xE9:		// 
	case 0xEA:		// 
	case 0xEB:		// 
	case 0xEE:		// 
	case 0xEF:		// 

	case 0xF4:		// 
	case 0xF9:		// 
	case 0xFC:		// 
	case 0xFF:		// 
		return TRUE;
	}
	
	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-06-18 by cmkwon, Gameforge4D (폴란드) 캐릭터명, 여단명 체크 수정 - 
/// \author		cmkwon
/// \date		2009-06-18 ~ 2009-06-18
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidPolishChar(char i_char)
{
	if(IsDBCSLeadByte(i_char))
	{
		return FALSE;	// 2 Bytes 문자는 FALSE를 리턴
	}
	
	// 영문자, 숫자 체크	
	if(CAtumSJ::IsAlphaNum(i_char))
	{
		return TRUE;
	}
	
	// 2009-06-18 by cmkwon, 나머지 폴란드어 문자
	switch((BYTE)i_char)
	{
	case 0x8C:		// 140
	case 0x8F:		// 143
	case 0x9C:		// 156
	case 0x9F:		// 159
	case 0xA3:		// 163
	case 0xA5:		// 165
	case 0xAF:		// 175
	case 0xB3:		// 179
	case 0xB9:		// 185
	case 0xBF:		// 191
	case 0xC6:		// 198
	case 0xCA:		// 202
	case 0xD1:		// 209
	case 0xD3:		// 211
	case 0xE6:		// 230
	case 0xEA:		// 234
	case 0xF1:		// 241
	case 0xF3:		// 243
		return TRUE;
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-07-10 by cmkwon, Gameforge4D 스페인 서비스 시작 준비 - 캐릭터명, 여단명 체크 수정
/// \author		cmkwon
/// \date		2009-07-10 ~ 2009-07-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidSpanishChar(char i_char)
{
	if(IsDBCSLeadByte(i_char))
	{
		return FALSE;	// 2 Bytes 문자는 FALSE를 리턴
	}
	
	// 영문자, 숫자 체크	
	if(CAtumSJ::IsAlphaNum(i_char))
	{
		return TRUE;
	}
	
	// 2009-07-10 by cmkwon, 나머지 스페인어 문자
	switch((BYTE)i_char)
	{
	case 0xC1:		// 193
	case 0xC9:		// 201
	case 0xCD:		// 205
	case 0xD1:		// 209
	case 0xD3:		// 211
	case 0xDA:		// 218
	case 0xE1:		// 225
	case 0xE9:		// 233
	case 0xED:		// 237
	case 0xF1:		// 241
	case 0xF3:		// 243
	case 0xFA:		// 250
		return TRUE;
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			INT CAtumSJ::GetSPIPenaltyOnDead(int i_nLevel)
/// \brief		
/// \author		cmkwon
/// \date		2006-09-05 ~ 2006-09-05
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CAtumSJ::GetSPIPenaltyOnDead(int i_nLevel)
{
	// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - CAtumSJ::GetSPIPenaltyOnDead#
	if (FALSE == IS_IN_RANGE(1, i_nLevel, CHARACTER_LEVEL_110_MAX_STAT_POINT))
	{
		return 0;
	}

	return arrLevelExperienceNew[i_nLevel].PenaltySPIOnDead;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		
///				// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 인자 변경
/// \author		dhjin
/// \date		2006-09-14 ~ 2006-09-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CAtumSJ::GetMaxInventorySize(BOOL i_IsMembership, int i_nAddedCnt)
{
	if (FALSE == i_IsMembership)
	{
		return SIZE_MAX_ITEM_GENERAL + i_nAddedCnt;		// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 
	}

	return SIZE_MAX_ITEM_GENERAL + COUNT_IN_MEMBERSHIP_ADDED_INVENTORY + i_nAddedCnt;	// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 인자 변경
/// \author		dhjin
/// \date		2006-09-14 ~ 2006-09-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CAtumSJ::GetMaxStoreSize(BOOL i_IsMembership, int i_nAddedCnt)
{
	if (FALSE == i_IsMembership)
	{
		return SIZE_MAX_ITEM_GENERAL_IN_STORE + i_nAddedCnt;	// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 
	}

	return SIZE_MAX_ITEM_GENERAL_IN_STORE + COUNT_IN_MEMBERSHIP_ADDED_STORE + i_nAddedCnt;	// 2009-11-02 by cmkwon, 캐쉬(인벤/창고 확장) 아이템 추가 구현 - 
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			INT CAtumSJ::GetMaxGuildSize(INT i_nGuildMemberCapacity, BOOL i_IsMembership)
/// \brief		
/// \author		dhjin
/// \date		2006-09-14 ~ 2006-09-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CAtumSJ::GetMaxGuildSize(INT i_nGuildMemberCapacity, BOOL i_IsMembership)
{
	if (i_IsMembership)
	{
		if(SIZE_MAX_GUILD_CAPACITY >= i_nGuildMemberCapacity+COUNT_IN_MEMBERSHIP_ADDED_GUILD_CAPACITY)
		{
			return i_nGuildMemberCapacity+COUNT_IN_MEMBERSHIP_ADDED_GUILD_CAPACITY;
		}

		return SIZE_MAX_GUILD_CAPACITY;
	}

	// 2008-08-12 by dhjin, 버그로 i_nGuildMemberCapacity를 리턴한다. // 2008-05-27 by dhjin, EP3 여단 수정 사항 - 여단원 증가 캐쉬 아이템
//	return SIZE_MAX_INITIAL_GUILD_CAPACITY;
//	return SIZE_MAX_GUILD_CAPACITY;
	return i_nGuildMemberCapacity;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			char * CAtumSJ::GetJamboreePreAddCharacterString(int i_nNumber)
/// \brief		
/// \author		cmkwon
/// \date		2007-04-10 ~ 2007-04-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
char * CAtumSJ::GetJamboreePreAddCharacterString(int i_nNumber)
{
	switch(i_nNumber)
	{
	case 1:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_1;
	case 2:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_2;
	case 3:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_3;
	case 4:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_4;
	case 5:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_5;
	case 6:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_6;
	case 7:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_7;
	case 8:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_8;
	case 9:		return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_9;
	case 10:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_10;
	case 11:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_11;
	case 12:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_12;
	case 13:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_13;
	case 14:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_14;
	case 15:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_15;
	case 16:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_16;
	case 17:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_17;
	case 18:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_18;
	case 19:	return STRCMD_CS_JAMBOREE_PREADD_CHARACTER_NAME_19;
	}

	return "Un_";
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CAtumSJ::IsValidPiotFace(BYTE i_byPilotFace)
/// \brief		// 2007-11-21 by cmkwon, PilotFace 변경 카드 구현 - 
/// \author		cmkwon
/// \date		2007-11-21 ~ 2007-11-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidPiotFace(BYTE i_byPilotFace)
{
	switch(i_byPilotFace)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:			// 2008-05-30 by dhjin, 신규 케릭터 추가
	case 100:
	case 101:
	case 102:
	case 103:
	case 104:
	case 105:		// 2008-05-30 by dhjin, 신규 케릭터 추가
		{
			return TRUE;
		}
	}

	return FALSE;
}




///////////////////////////////////////////////////////////////////////////////
/// \fn			INT CAtumSJ::GetTimeSecondByItemKind8ItemAttribute(ITEM *i_pItemInfo)
/// \brief		// 2008-11-26 by cmkwon, 사용 후 시간(절대시간) 제한 아이템 구현 - 
///				// 2009-10-22 by cmkwon, 시간 제한형류 아이템 시스템 정리 - CAtumSJ::GetTimeSecondByItemKind8ItemAttribute#, 수정
/// \author		cmkwon
/// \date		2008-11-26 ~ 2008-11-26
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CAtumSJ::GetTimeSecondByItemKind8ItemAttribute(ITEM *i_pItemInfo, TIME_TERM_t i_enTimeTermTy/*=TIME_TERM_USING_ITEM*/)
{
// 2009-10-22 by cmkwon, 시간 제한형류 아이템 시스템 정리 - 아래와 같이 수정
// 	switch(i_pItemInfo->Kind)
// 	{
// 	case ITEMKIND_AUTOMATIC:
// 	case ITEMKIND_VULCAN:
// 	case ITEMKIND_DUALIST:
// 	case ITEMKIND_CANNON:
// 	case ITEMKIND_RIFLE:
// 	case ITEMKIND_GATLING:
// 	case ITEMKIND_LAUNCHER:
// 	case ITEMKIND_MASSDRIVE:
// 	case ITEMKIND_SUPPORT:
// 	case ITEMKIND_ENERGY:
// 	case ITEMKIND_ACCESSORY_TIMELIMIT:
// 	case ITEMKIND_INFLUENCE_GAMEEVENT:
// 	case ITEMKIND_SKILL_SUPPORT_ITEM:
// 	case ITEMKIND_SKILL_ATTACK:
// 	case ITEMKIND_SKILL_DEFENSE:
// 	case ITEMKIND_SKILL_SUPPORT:
// 	case ITEMKIND_SKILL_ATTRIBUTE:
// 	case ITEMKIND_FOR_MON_MISSILE:
// 		{
// 			return i_pItemInfo->Time/1000;
// 		}
// 		break;
// 	case ITEMKIND_CARD:
// 		{
// 			if(COMPARE_BIT_FLAG(i_pItemInfo->ItemAttribute, ITEM_ATTR_DELETED_TIME_LIMITE_AFTER_USED))
// 			{
// 				return i_pItemInfo->Time;	// Second(초) 단위로 설정되어 있음
// 			}
// 
// 			if(COMPARE_BIT_FLAG(i_pItemInfo->ItemAttribute, ITEM_ATTR_CASH_ITEM_PREMIUM_CARD))
// 			{
// 				return i_pItemInfo->Time * 24 * 60 * 60;	// 일(Day) 단위로 설정되어 있음
// 			}
// 
// 			return i_pItemInfo->Time/1000;	// 나머지는 밀리세컨드(ms) 단위로 설정
// 		}
// 		break;
// 	}
// 
// 	return i_pItemInfo->Time;
	// 2010-11-09 by dhjin - 베트남 죽는 버그 요청 찾기 위해 일단 로그 남기기.
	if(NULL == i_pItemInfo)
	{
		return 0;
	}

#ifdef _ATUM_CLIENT
	
#else
	char szSysLog[1024];
	sprintf(szSysLog,"  [Notify] CAtumSJ::GetTimeSecondByItemKind8ItemAttribute,IN \r\n");
	g_pGlobal->WriteSystemLogEX(TRUE, szSysLog);
	char szSysLog1[1024];
	sprintf(szSysLog1,"  [Notify] CAtumSJ::GetTimeSecondByItemKind8ItemAttribute,Itemnum [%6d]\r\n", i_pItemInfo->ItemNum);
	g_pGlobal->WriteSystemLogEX(TRUE, szSysLog1);
#endif

	///////////////////////////////////////////////////////////////////////////////
	// 2009-10-22 by cmkwon, 시간 제한형류 아이템 시스템 정리 - 
	switch(i_enTimeTermTy)
	{
	case TIME_TERM_USING_ITEM:
		{
			if(ITEMKIND_ACCESSORY_TIMELIMIT == i_pItemInfo->Kind)
			{
				return i_pItemInfo->Time/1000;		// 밀리세컨드(ms) 단위
			}

			if(COMPARE_BIT_FLAG(i_pItemInfo->ItemAttribute, ITEM_ATTR_TIME_LIMITE))
			{
				return i_pItemInfo->Time/1000;		// 밀리세컨드(ms) 단위
			}
			else if(COMPARE_BIT_FLAG(i_pItemInfo->ItemAttribute, ITEM_ATTR_DELETED_TIME_LIMITE_AFTER_USED))
			{
				return i_pItemInfo->Time;			// 세컨드(s) 단위
			}
			return i_pItemInfo->Time;
		}
		break;
	case TIME_TERM_DELETE_ITEM:
		{
			if(COMPARE_BIT_FLAG(i_pItemInfo->ItemAttribute, ITEM_ATTR_DELETED_TIME_LIMITE))
			{
				return i_pItemInfo->Endurance * 3600;	// 시간으로 설정되어 있음
			}
		}
		break;
	case TIME_TERM_PREMIUM:
		{
			if(COMPARE_BIT_FLAG(i_pItemInfo->ItemAttribute, ITEM_ATTR_CASH_ITEM_PREMIUM_CARD))
			{
				return i_pItemInfo->Time * 86400;		// Day로 설정되어 있음
			}
		}
		break;
	case TIME_TERM_EVENT:
		{
			if(ITEMKIND_INFLUENCE_GAMEEVENT == i_pItemInfo->Kind)
			{
				return i_pItemInfo->Time/1000;
			}			
		}
		break;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-10-22 by cmkwon, 시간 제한형류 아이템 시스템 정리 - CAtumSJ::GetTimeMinuteByItemKind8ItemAttribute#, 추가
/// \author		cmkwon
/// \date		2009-10-22 ~ 2009-10-22
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CAtumSJ::GetTimeMinuteByItemKind8ItemAttribute(ITEM *i_pItemInfo, TIME_TERM_t i_enTimeTermTy/*=TIME_TERM_USING_ITEM*/)
{
	int nSecond = CAtumSJ::GetTimeSecondByItemKind8ItemAttribute(i_pItemInfo, i_enTimeTermTy);
	if(0 >= nSecond)
	{
		return 0;
	}
	return nSecond/60;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 
/// \author		cmkwon
/// \date		2009-02-24 ~ 2009-02-24
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsAlphaNum(char *i_szString)
{
	int nLen = strlen(i_szString);
	for(int i=0; i < nLen; i++)
	{
		if(FALSE == CAtumSJ::IsAlphaNum(i_szString[i]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-02-12 by cmkwon, EP3-3 월드랭킹시스템 구현 - 
/// \author		cmkwon
/// \date		2009-02-19 ~ 2009-02-19
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidNickName(char *i_szNickName)
{
	int nLen = strlen(i_szNickName);
	if(FALSE == IS_IN_RANGE(SIZE_MIN_CHARACTER_NAME, nLen, SIZE_MAXUSE_CHARACTER_NAME-1))
	{
		return FALSE;
	}

	return CAtumSJ::IsAlphaNum(i_szNickName);
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2009-08-03 by cmkwon, EP3-4 편대 대형 스킬 구현 - 해당 편대 대형별 적용 될 스킬아이템번호를 리턴한다.
///				// 2009-09-30 by cmkwon, 편대 대형별 스킬 ItemNum 변경 - 
/// \author		cmkwon
/// \date		2009-08-17 ~ 2009-08-17
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
INT CAtumSJ::FindPartyFormationSkillNum(BYTE i_byFormationTy)
{
	switch(i_byFormationTy)
	{
	case FLIGHT_FORM_2_COLUMN:				return 7813151;		// 이렬 종대
	case FLIGHT_FORM_2_LINE:				return 7813091;		// 이렬 횡대
	case FLIGHT_FORM_TRIANGLE:				return 7813101;		// 삼각 편대
	case FLIGHT_FORM_INVERTED_TRIANGLE:		return 7813161;		// 역삼각 편대
	case FLIGHT_FORM_BELL:					return 7813111;		// 종 형태
	case FLIGHT_FORM_INVERTED_BELL:			return 7813131;		// 역종 형태
	case FLIGHT_FORM_X:						return 7813171;		// X자 형태
	case FLIGHT_FORM_STAR:					return 7813141;		// 별 형태
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2010-01-14 by cmkwon, 월드랭킹시스템 버그 수정(서비스삭제,서버그룹삭제) - 
/// \author		cmkwon
/// \date		2010-01-14 ~ 2010-01-14
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CAtumSJ::IsValidWRankingServiceName(char *i_szServiceName)
{
	int nLen = strlen(i_szServiceName);
	if(FALSE == IS_IN_RANGE(SIZE_MIN_CHARACTER_NAME, nLen, SIZE_MAX_SERVICE_NAME-1))
	{
		return FALSE;
	}

	for(int i=0; i < nLen; i++)
	{
		if(FALSE == CAtumSJ::IsAlphaNum(i_szServiceName[i])
			&& '-' != i_szServiceName[i]
			&& '_' != i_szServiceName[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 
/// \author		cmkwon
/// \date		2010-04-21 ~ 2010-04-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumSJ::GetLuckyMachineSlotCount(int i_machineKind)
{
	switch(i_machineKind)
	{
	case LUCKY_MACHINE_KIND_HAPPY_MACHINE:			return 1;
	case LUCKY_MACHINE_KIND_WEAPON_MACHINE:			return 3;
	case LUCKY_MACHINE_KIND_ARMOR_MACHINE:			return 3;
	}

	return MaxPayLuckyMachineItem;		// 최대 필요 개수 리턴
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - 
///				// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - (빠진부분추가) - 
/// \author		cmkwon
/// \date		2010-04-21 ~ 2010-04-21
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CAtumSJ::GetRareItemInfoList(vectRARE_ITEM_INFOPtrList *o_pValidRareList, BOOL i_bIsPrefix, mapRARE_ITEM_INFOPtrList *i_pRareItemInfoList, ITEM *i_pTargetItemInfo, ITEM *i_pRareItemInfo)
{
	if(NULL == i_pTargetItemInfo || NULL == i_pRareItemInfo)
	{
		return 0;
	}

	int nReqUseTypeMask	= (FALSE == COMPARE_BIT_FLAG(i_pRareItemInfo->ItemAttribute, ITEM_ATTR_SUPER_GAMBLE_ITEM)) ? RARE_ITEM_USE_TYPE_GAMBLE : RARE_ITEM_USE_TYPE_SUPERGAMBLE; 
	int nReqMinLevel	= min(CHARACTER_MAX_LEVEL, i_pTargetItemInfo->ReqMinLevel);
	mapRARE_ITEM_INFOPtrList::iterator itr(i_pRareItemInfoList->begin());
	for(; itr != i_pRareItemInfoList->end(); itr++)
	{
		RARE_ITEM_INFO *pRareItemInfo = itr->second;
		if(0 >= pRareItemInfo->Probability
			|| (FALSE != i_bIsPrefix && FALSE == IS_RARE_PREFIX(pRareItemInfo->CodeNum))
			|| (FALSE == i_bIsPrefix && FALSE == IS_RARE_SUFFIX(pRareItemInfo->CodeNum))
			|| FALSE == IS_IN_RANGE(pRareItemInfo->ReqMinLevel, nReqMinLevel, pRareItemInfo->ReqMaxLevel)
			|| FALSE == COMPARE_ITEMKIND(pRareItemInfo->ReqItemKind, i_pTargetItemInfo->Kind)
			|| FALSE == COMPARE_BIT_FLAG(pRareItemInfo->ReqUseType, nReqUseTypeMask))		// 2010-04-20 by cmkwon, 신규 러키 머신 구현 - (빠진부분추가) - 
		{
			continue;
		}

		o_pValidRareList->push_back(pRareItemInfo);
	}

	return o_pValidRareList->size();
}

const char *CAtumSJ::GetInfluenceTypeString(BYTE i_byInfluenceTy)
{
	if(INFLUENCE_TYPE_ALL_MASK ==  i_byInfluenceTy)
	{// 모든 세력
		// 2007-10-30 by cmkwon, 세력별 해피아워 이벤트 구현 - 정의 함
		//return "All Influence User";
		return STRCMD_CS_INFLUENCE_TYPE_ALL_MASK;
	}
	if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_NORMAL))
	{// 바이제니유  시티 일반군
		return STRCMD_CS_INFLUENCE_TYPE_NORMAL;
	}
	if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_VCN))
	{// 바이제니유  시티 정규군
		return STRCMD_CS_INFLUENCE_TYPE_VCN;
	}	
	if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_ANI))
	{// 알링턴 시티 반란군
		return STRCMD_CS_INFLUENCE_TYPE_ANI;
	}
	if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_RRP))
	{// 바탈러스 연방군
		return STRCMD_CS_INFLUENCE_TYPE_RRP;
	}
	return "Unknown Influence";
}
// 2010-06-01 by shcho, GLogDB 관련 -
const char *CAtumSJ::GetInfluenceTypeGLogString(BYTE i_byInfluenceTy)
{
	if(INFLUENCE_TYPE_ALL_MASK ==  i_byInfluenceTy)
	{// 모든 세력
		// 2007-10-30 by cmkwon, 세력별 해피아워 이벤트 구현 - 정의 함
		//return "All Influence User";
		return INFLUENCE_TYPE_ENG_ALL_MASK;
	}
	if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_NORMAL))
	{// 바이제니유  시티 일반군
		return INFLUENCE_TYPE_ENG_NORMAL;
	}
	if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_VCN))
	{// 바이제니유  시티 정규군
		return INFLUENCE_TYPE_ENG_VCN;
	}	
	if(COMPARE_INFLUENCE(i_byInfluenceTy, INFLUENCE_TYPE_ANI))
	{// 알링턴 시티 반란군
		return INFLUENCE_TYPE_ENG_ANI;
	}
	return "Unknown Influence";
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		아이템 툴에서 사용하기 위한 함수
/// \author		cmkwon
/// \date		2005-07-08 ~ 2005-07-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
const char *CAtumSJ::GetPositionString(BYTE i_byPosition)
{
	switch(i_byPosition)
	{
	case POS_PROW:				return STRCMD_CS_POS_PROW;
	case POS_PROWIN:			return STRCMD_CS_POS_PROWIN;
	case POS_PROWOUT:			return STRCMD_CS_POS_PROWOUT;
	case POS_WINGIN:			return STRCMD_CS_POS_WINGIN;			// 2006-07-20 by cmkwon, 이펙트 아이템 (중앙 위쪽)
	case POS_WINGOUT:			return STRCMD_CS_POS_WINGOUT;
	case POS_CENTER:			return STRCMD_CS_POS_CENTER;
	case POS_REAR:				return STRCMD_CS_POS_REAR;

	// 2010-06-15 by shcho&hslee 펫시스템 - 선언 변경.
	//case POS_ATTACHMENT:		return STRCMD_CS_POS_ATTACHMENT;		// 2006-03-30 by cmkwon, 무제한 악세사리 - 부착물
	case POS_ACCESSORY_UNLIMITED :	return STRCMD_CS_POS_ACCESSORY_UNLIMITED;		// 2006-03-30 by cmkwon, 무제한 악세사리 - 부착물

	// 2010-06-15 by shcho&hslee 펫시스템 - 선언 변경.
	//case POS_PET:				return STRCMD_CS_POS_PET;				// 2006-03-30 by cmkwon, 시간제한 악세사리
	case POS_ACCESSORY_TIME_LIMIT :	return STRCMD_CS_POS_ACCESSORY_TIME_LIMIT;				// 2006-03-30 by cmkwon, 시간제한 악세사리

	// 2010-06-15 by shcho&hslee 펫시스템
	case POS_PET :				return STRCMD_CS_POS_PET;

	case POS_INVALID_POSITION:	return STRCMD_CS_POS_INVALID_POSITION;
	}

	return STRCMD_CS_POS_ITEMWINDOW_OFFSET;		// POS_ITEMWINDOW_OFFSET 이번호 부터는 인벤토리에 위치
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			
/// \brief		아이템 툴에서 사용하기 위한 함수
/// \author		cmkwon
/// \date		2005-07-08 ~ 2005-07-08
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
const char *CAtumSJ::GetReqUnitKindString(USHORT i_usUnitKindMask)
{
	switch(i_usUnitKindMask)
	{
	case UNITKIND_BGEAR_MASK:			return STRCMD_CS_UNITKIND_BGEAR_ALL;		// 2007-03-29 by cmkwon
	case UNITKIND_MGEAR_MASK:			return STRCMD_CS_UNITKIND_MGEAR_ALL;		// 2007-03-29 by cmkwon
	case UNITKIND_AGEAR_MASK:			return STRCMD_CS_UNITKIND_AGEAR_ALL;		// 2007-03-29 by cmkwon
	case UNITKIND_IGEAR_MASK:			return STRCMD_CS_UNITKIND_IGEAR_ALL;		// 2007-03-29 by cmkwon
	case UNITKIND_ALL_MASK:				return STRCMD_CS_UNITKIND_GEAR_ALL;			// 2007-03-29 by cmkwon
// 2005-07-08 by cmkwon, 지금은 필요 없음
//	case UNITKIND_BGEAR:				return "B-Gear";
//	case UNITKIND_MGEAR:				return "M-Gear";
//	case UNITKIND_AGEAR:				return "A-Gear";
//	case UNITKIND_IGEAR:				return "I-Gear";
	}
	return "Unknown Gear";
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			const char *CAtumSJ::GetGuildRankString(BYTE i_byGuildRank)
/// \brief		
/// \author		cmkwon
/// \date		2006-03-07 ~ 2006-03-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
const char *CAtumSJ::GetGuildRankString(BYTE i_byGuildRank)
{
	switch(i_byGuildRank)
	{
	case GUILD_RANK_PRIVATE_NULL:		return STRCMD_CS_GUILD_RANK_PRIVATE_NULL;	// 무소속 대대원
	case GUILD_RANK_COMMANDER:			return STRCMD_CS_GUILD_RANK_COMMANDER;		// 비행여단장, 길드장
	case GUILD_RANK_SUBCOMMANDER:		return STRCMD_CS_GUILD_RANK_SUBCOMMANDER;	// 부여단장				// 2008-05-20 by dhjin, EP3 - 여단 수정 사항
	case GUILD_RANK_SQUAD_LEADER_1:		return STRCMD_CS_GUILD_RANK_SQUAD_LEADER_1;	// 제 1 비행대대장
	case GUILD_RANK_PRIVATE_1:			return STRCMD_CS_GUILD_RANK_PRIVATE_1;		// 제 1 비행대대원
	case GUILD_RANK_SQUAD_LEADER_2:		return STRCMD_CS_GUILD_RANK_SQUAD_LEADER_2;	// 제 2 비행대대장
	case GUILD_RANK_PRIVATE_2:			return STRCMD_CS_GUILD_RANK_PRIVATE_2;		// 제 2 비행대대원
	case GUILD_RANK_SQUAD_LEADER_3:		return STRCMD_CS_GUILD_RANK_SQUAD_LEADER_3;	// 제 3 비행대대장
	case GUILD_RANK_PRIVATE_3:			return STRCMD_CS_GUILD_RANK_PRIVATE_3;		// 제 3 비행대대원
	case GUILD_RANK_SQUAD_LEADER_4:		return STRCMD_CS_GUILD_RANK_SQUAD_LEADER_4;	// 제 4 비행대대장
	case GUILD_RANK_PRIVATE_4:			return STRCMD_CS_GUILD_RANK_PRIVATE_4;		// 제 4 비행대대원
	case GUILD_RANK_SQUAD_LEADER_5:		return STRCMD_CS_GUILD_RANK_SQUAD_LEADER_5;	// 제 5 비행대대장
	case GUILD_RANK_PRIVATE_5:			return STRCMD_CS_GUILD_RANK_PRIVATE_5;		// 제 5 비행대대원
	}
	return "Unknown Guild Rank";
}

// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 110레벨까지 값 설정
// 레벨 & 경험치 관련
//		// 2006-02-28 by cmkwon, ExprerienceLossOnDeath 수치 변경
// struct LEVEL_EXPERIENCE {
// 	INT				Level;						// 레벨
// 	Experience_t	ExperienceIncreament;		// (해당 레벨의 최고 경험치) - (해당 레벨-1의 최고 경험치), 정확하지 않으므로 사용 불가!
// 	Experience_t	Experience;					// (해당 레벨-1)의 초기 경험치
// 	Experience_t	ExperienceLossOnDeath;		// 죽었을 때 경험치 감소량
//	INT				PenaltySPIOnDead;			// 2006-09-05 by cmkwon, 캐릭터가 죽을 때 떨어지는 레벨별 SPI Count
// };
const LEVEL_EXPERIENCE arrLevelExperienceNew[] = {
	{0		,0				,0				,0			,0},
	{1		,91				,91				,0			,0},
	{2		,141			,232			,0			,0},
	{3		,221			,453			,0			,0},
	{4		,391			,844			,0			,0},
	{5		,711			,1555			,0			,0},
	{6		,1241			,2796			,0			,0},
	{7		,2041			,4837			,0			,0},
	{8		,3171			,8008			,0			,0},
	{9		,4691			,12699			,0			,0},
	{10		,6661			,19360			,666		,836},
	{11		,9141			,28501			,904		,938},
	{12		,12191			,40692			,1194		,1044},
	{13		,15871			,56563			,1539		,1154},
	{14		,20241			,76804			,1943		,1267},
	{15		,25361			,102165			,2409		,1385},
	{16		,31291			,133456			,2941		,1507},
	{17		,38091			,171547			,3542		,1633},
	{18		,45821			,217368			,4215		,1764},
	{19		,54541			,271909			,4963		,1899},
	{20		,64311			,336220			,5787		,2039},
	{21		,75191			,411411			,6691		,2184},
	{22		,87241			,498652			,7677		,2334},
	{23		,100521			,599173			,8745		,2489},
	{24		,115091			,714264			,9897		,2649},
	{25		,131011			,845275			,11135		,2814},
	{26		,148341			,993616			,12460		,2985},
	{27		,167141			,1160757		,13872		,3162},
	{28		,187471			,1348228		,15372		,3345},
	{29		,209391			,1557619		,16960		,3534},
	{30		,232961			,1790580		,18636		,3729},
	{31		,258241			,2048821		,20401		,3930},
	{32		,285291			,2334112		,22252		,4138},
	{33		,314171			,2648283		,24191		,4353},
	{34		,344941			,2993224		,26215		,4574},
	{35		,377661			,3370885		,28324		,4803},
	{36		,412391			,3783276		,30516		,5039},
	{37		,449191			,4232467		,32790		,5283},
	{38		,488121			,4720588		,35144		,5534},
	{39		,529241			,5249829		,37576		,5793},
	{40		,572611			,5822440		,40082		,6061},
	{41		,618291			,6440731		,42662		,6337},
	{42		,666341			,7107072		,45311		,6621},
	{43		,716821			,7823893		,48027		,6914},
	{44		,769791			,8593684		,50806		,7217},
	{45		,825311			,9418995		,53645		,7528},
	{46		,883441			,10302436		,56540		,7849},
	{47		,944241			,11246677		,59487		,8180},
	{48		,1007771		,12254448		,62481		,8522},
	{49		,1074091		,13328539		,65519		,8873},
	{50		,1143261		,14471800		,68595		,9235},
	{51		,1215341		,15687141		,71705		,9608},
	{52		,1290391		,16977532		,74842		,9993},
	{53		,1368471		,18346003		,78002		,10389},
	{54		,1449641		,19795644		,81179		,10796},
	{55		,1533961		,21329605		,84367		,11216},
	{56		,1621491		,22951096		,87560		,11649},
	{57		,1712291		,24663387		,90751		,12094},
	{58		,1806421		,26469808		,93933		,12552},
	{59		,1903941		,28373749		,97100		,13024},
	{60		,2004911		,30378660		,100245		,13510},
	{61		,2405893		,32784553		,117888		,14010},
	{62		,2887071		,35671624		,138579		,14524},
	{63		,3464485		,39136109		,162830		,15053},
	{64		,4157382		,43293491		,191239		,15598},
	{65		,4988858		,48282349		,224498		,16159},
	{66		,5986629		,54268978		,263411		,16736},
	{67		,7183954		,61452932		,308910		,17329},
	{68		,8620744		,70073676		,362071		,17939},
	{69		,10344892		,80418568		,424140		,18567},
	{70		,12413870		,92832438		,496554		,19213},
	{71		,14896644		,107729082		,580969		,19877},
	{72		,17875972		,125605054		,679286		,20560},
	{73		,21451166		,147056220		,793693		,21263},
	{74		,25741399		,172797619		,926690		,21985},
	{75		,30889678		,203687297		,1081138	,22728},
	{76		,37067613		,240754910		,1260298	,23492},
	{77		,44481135		,285236045		,1467877	,24277},
	{78		,53377362		,338613407		,1708075	,25084},
	{79		,64052834		,402666241		,1985637	,25914},
	{80		,76863400		,479529641		,2305902	,26767},
	{81		,92236080		,571765721		,2674846	,27643},
	{82		,110683296		,682449017		,3099132	,28544},
	{83		,132819955		,815268972		,3586138	,29470},
	{84		,159383946		,974652918		,4143982	,30422},
	{85		,191260735		,1165913653		,4781518	,31400},
	{86		,229512882		,1395426535		,5508309	,32404},
	{87		,275415458		,1670841993		,6334555	,33437},
	{88		,330498549		,2001340542		,7270968	,34498},
	{89		,396598258		,2397938800		,8328563	,35587},
	{90		,475917909		,2873856709		,9518358	,36707},
	{91		,571101490		,3444958199		,10850928	,37857},
	{92		,685321788		,4130279987		,12335792	,39039},
	{93		,822386145		,4952666132		,13980564	,40252},
	{94		,986863374		,5939529506		,15789813	,41499},
	{95		,1184236048		,7123765554		,17763540	,42779},
	{96		,1421083257		,8544848811		,19895165	,44094},
	{97		,1705299908		,10250148719	,22168898	,45445},
	{98		,2046359889		,12296508608	,24556318	,46831},
	{99		,2455631866		,14752140474	,27011950	,48255},
	{100	,2946758239		,17698898713	,29467582	,49718},
	{101	,2946758239		,20645656952	,29467582	,49718},
	{102	,2946758239		,23592415191	,29467582	,49718},
	{103	,2946758239		,26539173430	,29467582	,49718},
	{104	,2946758239		,29485931669	,29467582	,49718},
	{105	,2946758239		,32432689908	,29467582	,49718},
	{106	,2946758239		,35379448147	,29467582	,49718},
	{107	,2946758239		,38326206386	,29467582	,49718},
	{108	,2946758239		,41272964625	,29467582	,49718},
	{109	,2946758239		,44219722864	,29467582	,49718},
	{110	,2946758239		,47166481103	,29467582	,49718},
	{111 	,3830785710  	,50997266813 	,38307857 	,646334},
	{112 	,3830785710  	,54828052523 	,38307857 	,646334},
	{113 	,3830785710  	,58658838233 	,38307857 	,646334},
	{114 	,3830785710  	,62489623943 	,38307857 	,646334},
	{115 	,3830785710  	,66320409653 	,38307857 	,646334},
	{116	,4980021423  	,71300431076 	,49800214 	,840234},
	{117	,4980021423  	,76280452499 	,49800214 	,840234},
	{118	,4980021423  	,81260473922 	,49800214 	,840234},
	{119	,4980021423  	,86240495345 	,49800214 	,840234},
	{120 	,6474027849  	,92714523194 	,64740278 	,1092304},
	{121 	,6474027849  	,99188551043 	,64740278 	,1092304},
	{122 	,6474027849  	,105662578892 	,64740278 	,1092304},
	{123 	,6474027849  	,112136606741 	,64740278 	,1092304},
	{124 	,8474027849  	,122136606741 	,64740278 	,1092304},
	{125 	,8474027849  	,132136606741 	,64740278 	,1092304}
};

// 2009-12-29 by cmkwon, 캐릭터 최대 레벨 상향(110으로) - 스탯 341까지 값설정, 몬스터 플러스 피어스 110레벨까지 설정
// Level 혹은 Stat에 대한 각종 값
//struct LEVEL_STAT_VALUE
//{
//	INT		LevelOrStat;
//	double	AttackPart_AttackIncreaseRate;			// 공격 스탯에 의한 attack 증가율, @GetAttackC()
//	double	AttackPart_AttackIncreaseProbability;	// 명중률 - 공격스탯에 의한 공격확률과 동일한 기능을 가지는 추가 확률
//	INT		AttackPart_PierceAttackProbability;		// 피어스율(256확률) - 상대방 방어율에서 이 값을 차감한것이 실제 상대방 방어율이 된다.
//	double	DefensePart_DefenseDecreaseRate;		// 방어 스탯에 의한 defense 감소분, @GetDefenseC()
//	double	ShieldPart_DP;							// ShieldPart에 대한 Shield(DP)값
//	double	DodgePart_DefenseProbabilityRate;		// 회피 스탯에 의한 방어확률의 비율, @GetDefenseProbabilityC()
//	INT		HPOfLevel;								// Level에 대한 HP
//	INT		Level_MonsertPierceAttackProbability;	// MonsterLevel에 대한 몬스터 PierceAttack확률
//};
// 2007-05-21 by cmkwon, ShieldPart에 해당하는 Shield량 수치 기존보다 3배 크게함

// 확률 수식 변경 관련 - 피어스확률 값 수정. (4번째 항목.)	2010. 10. 06. by hsLee.
// 2011-11-23 shcho, 회피확률, 스탯에 따른 공격 성곡률 수정 (3번째항목, 7번째항목)
const LEVEL_STAT_VALUE g_arrLevelStatValue[] = {
	{0		,0.0000 	,0.0000 	,0		,0.0000 	,0.0000 	,0.0000 	,0	 	,0},
	{1		,0.0227500 	,0.1471		,1.57  	,0.0098 	,60.0000 	,0.0050 	,10		,0.39},
	{2		,0.0250250 	,0.1618		,1.57  	,0.0130 	,79.9800 	,0.0067 	,20		,0.78},
	{3		,0.0273000 	,0.1765		,1.57  	,0.0163 	,99.9600 	,0.0083 	,30		,1.17},
	{4		,0.0295750 	,0.1912		,1.97  	,0.0195 	,120.0000 	,0.0100 	,40		,1.56},
	{5		,0.0318500 	,0.2059		,1.97  	,0.0227 	,139.9800 	,0.0117 	,50		,1.96},
	{6		,0.0341250 	,0.2206		,2.36  	,0.0258 	,159.9600 	,0.0133 	,61		,2.35},
	{7		,0.0364000 	,0.2353		,2.36  	,0.0290 	,180.0000 	,0.0150 	,72		,2.74},
	{8		,0.0386750 	,0.2500		,2.36  	,0.0321 	,199.9800 	,0.0167 	,83		,3.13},
	{9		,0.0409500 	,0.2647		,2.75  	,0.0352 	,219.9600 	,0.0183 	,94		,3.52},
	{10		,0.0432250 	,0.2794		,2.75  	,0.0383 	,240.0000 	,0.0200 	,105		,3.92},
	{11		,0.0455000 	,0.2941		,2.75  	,0.0414 	,259.9800 	,0.0217 	,117		,4.31},
	{12		,0.0477750 	,0.3088		,3.14  	,0.0444 	,279.9600 	,0.0233 	,129		,4.70},
	{13		,0.0500500 	,0.3235		,3.14  	,0.0475 	,300.0000 	,0.0250 	,141		,5.09},
	{14		,0.0523250 	,0.3382		,3.53  	,0.0505 	,321.9780 	,0.0267 	,153		,5.49},
	{15		,0.0546000 	,0.3529		,3.53  	,0.0535 	,343.9560 	,0.0283 	,166		,5.88},
	{16		,0.0568750 	,0.3676		,3.53  	,0.0565 	,366.0000 	,0.0300 	,179		,6.27},
	{17		,0.0591500 	,0.3824		,3.93  	,0.0594 	,387.9780 	,0.0317 	,192 		,6.66},
	{18		,0.0614250 	,0.3971		,3.93  	,0.0624 	,409.9560 	,0.0333 	,205 		,7.05},
	{19		,0.0637000 	,0.4118		,3.93  	,0.0653 	,432.0000 	,0.0350 	,218		,7.45},
	{20		,0.0659750 	,0.4265		,4.32  	,0.0680 	,453.9780 	,0.0367 	,232		,7.84},
	{21		,0.0682500 	,0.4412		,4.32  	,0.0708 	,475.9560 	,0.0383 	,246		,8.23},
	{22		,0.0705250 	,0.4559		,4.71  	,0.0735 	,498.0000 	,0.0400 	,260		,8.62},
	{23		,0.0728000 	,0.4706		,4.71  	,0.0764 	,519.9780 	,0.0417 	,274		,9.01},
	{24		,0.0750750 	,0.4853		,4.71  	,0.0793 	,541.9560 	,0.0433 	,288		,9.41},
	{25		,0.0773500 	,0.5000		,5.10  	,0.0822 	,564.0000 	,0.0450 	,303		,9.80},
	{26		,0.0796250 	,0.5147		,5.10  	,0.0850 	,585.9780 	,0.0467 	,318		,10.19},
	{27		,0.0819000 	,0.5294		,5.10  	,0.0877 	,607.9560 	,0.0483 	,333		,10.58},
	{28		,0.0841750 	,0.5441		,5.50  	,0.0905 	,630.0000 	,0.0500 	,348		,10.98},
	{29		,0.0864500 	,0.5588		,5.50  	,0.0933 	,653.9760 	,0.0517 	,363		,11.37},
	{30		,0.0887250 	,0.5735		,5.50  	,0.0962 	,677.9520 	,0.0533 	,379		,11.76},
	{31		,0.0910000 	,0.5882		,5.89  	,0.0990 	,702.0000 	,0.0550 	,395		,12.15},
	{32		,0.0932750 	,0.6029		,5.89  	,0.1017 	,725.9760 	,0.0567 	,411		,12.54},
	{33		,0.0955500 	,0.6176		,6.28  	,0.1043 	,749.9520 	,0.0583 	,427		,12.94},
	{34		,0.0978250 	,0.6324		,6.28  	,0.1070 	,774.0000 	,0.0600 	,443		,13.33},
	{35		,0.1001000 	,0.6471		,6.28  	,0.1097 	,797.9760 	,0.0617 	,460		,13.72},
	{36		,0.1023750 	,0.6618		,6.67  	,0.1123 	,821.9520 	,0.0633 	,477		,14.11},
	{37		,0.1046500 	,0.6765		,6.67  	,0.1150 	,846.0000 	,0.0650 	,494		,14.50},
	{38		,0.1069250 	,0.6912		,6.67  	,0.1175 	,869.9760 	,0.0667 	,511		,14.90},
	{39		,0.1092000 	,0.7059		,7.06  	,0.1200 	,893.9520 	,0.0683 	,528		,15.29},
	{40		,0.1114750 	,0.7206		,7.06  	,0.1225 	,918.0000 	,0.0700 	,546		,15.68},
	{41		,0.1137500 	,0.7353		,7.46  	,0.1250 	,943.9740 	,0.0717 	,564		,16.07},
	{42		,0.1160250 	,0.7500		,7.46  	,0.1275 	,969.9480 	,0.0733 	,582		,16.47},
	{43		,0.1183000 	,0.7647		,7.46  	,0.1300 	,996.0000 	,0.0750 	,600		,16.86},
	{44		,0.1205750 	,0.7794		,7.85  	,0.1325 	,1021.9740 	,0.0767 	,618		,17.25},
	{45		,0.1228500 	,0.7941		,7.85  	,0.1350 	,1047.9480 	,0.0783 	,637		,18.03},
	{46		,0.1251250 	,0.8088		,7.85  	,0.1375 	,1074.0000 	,0.0800 	,656		,18.43},
	{47		,0.1274000 	,0.8235		,8.24  	,0.1400 	,1099.9740 	,0.0817 	,675		,18.82},
	{48		,0.1296750 	,0.8382		,8.24  	,0.1425 	,1125.9480 	,0.0833 	,694		,19.21},
	{49		,0.1319500 	,0.8529		,8.63  	,0.1450 	,1152.0000 	,0.0850 	,713		,19.60},
	{50		,0.1342250 	,0.8676		,8.63  	,0.1475 	,1177.9740 	,0.0867 	,733 		,20.00},
	{51		,0.1365000 	,0.8824		,8.63  	,0.1500 	,1203.9480 	,0.0883 	,753 		,20.39},
	{52		,0.1387750 	,0.8971		,9.02  	,0.1525 	,1230.0000 	,0.0900 	,773		,20.78},
	{53		,0.1410500 	,0.9118		,9.02  	,0.1549 	,1255.9740 	,0.0917 	,793		,21.17},
	{54		,0.1433250 	,0.9265		,9.02  	,0.1573 	,1281.9480 	,0.0933 	,813		,21.56},
	{55		,0.1456000 	,0.9412		,9.42  	,0.1597 	,1308.0000 	,0.0950 	,834		,21.96},
	{56		,0.1478750 	,0.9559		,9.42  	,0.1620 	,1335.9720 	,0.0967 	,855		,22.35},
	{57		,0.1501500 	,0.9706		,9.42  	,0.1643 	,1363.9440 	,0.0983 	,876		,22.74},
	{58		,0.1524250 	,0.9853	,9.81  	,0.1667 	,1392.0000		,0.1000 	,897		,23.13},
	{59		,0.1547000 	,1.0000	,9.81  	,0.1689 	,1419.9720		,0.1017 	,918		,23.52},
	{60		,0.1569750 	,1.0147	,10.20 	,0.1712 	,1447.9440		,0.1033 	,940		,23.92},
	{61		,0.1592500 	,1.0294	,10.20 	,0.1735 	,1476.0000		,0.1050 	,962		,24.31},
	{62		,0.1615250 	,1.0441	,10.20 	,0.1757 	,1503.9720		,0.1067 	,984		,24.70},
	{63		,0.1638000 	,1.0588	,10.59 	,0.1780 	,1531.9440		,0.1083 	,1006		,25.09},
	{64		,0.1660750 	,1.0735	,10.59 	,0.1803 	,1560.0000		,0.1100 	,1028		,25.49},
	{65		,0.1683500 	,1.0882	,10.59 	,0.1825 	,1587.9720		,0.1117 	,1051		,25.88},
	{66		,0.1706250 	,1.1029	,10.99 	,0.1847 	,1615.9440		,0.1133 	,1074		,26.27},
	{67		,0.1729000 	,1.1176	,10.99 	,0.1870 	,1644.0000		,0.1150 	,1097		,26.66},
	{68		,0.1751750 	,1.1324	,11.38 	,0.1891 	,1671.9720		,0.1167 	,1120		,27.05},
	{69		,0.1774500 	,1.1471	,11.38 	,0.1912 	,1699.9440		,0.1183 	,1143		,27.45},
	{70		,0.1797250 	,1.1618	,11.38 	,0.1934 	,1728.0000		,0.1200 	,1167		,27.84},
	{71		,0.1820000 	,1.1765	,11.77 	,0.1955 	,1757.9700		,0.1217 	,1191		,28.23},
	{72		,0.1842750 	,1.1912	,11.77 	,0.1976 	,1787.9400		,0.1233 	,1215		,28.62},
	{73		,0.1865500 	,1.2059	,11.77 	,0.1998 	,1818.0000		,0.1250 	,1239		,29.01},
	{74		,0.1888250 	,1.2206	,12.16 	,0.2019 	,1847.9700		,0.1267 	,1263		,29.41},
	{75		,0.1911000 	,1.2353	,12.16 	,0.2040 	,1877.9400		,0.1283 	,1288		,29.80},
	{76		,0.1933750 	,1.2500	,12.55 	,0.2062 	,1908.0000		,0.1300 	,1313		,30.19},
	{77		,0.1956500 	,1.2647	,12.55 	,0.2083 	,1937.9700		,0.1317 	,1338		,30.58},
	{78		,0.1979250 	,1.2794	,12.55 	,0.2104 	,1967.9400		,0.1333 	,1363		,30.98},
	{79		,0.2002000 	,1.2941	,12.95 	,0.2126 	,1998.0000		,0.1350 	,1388		,31.37},
	{80		,0.2024750 	,1.3088	,12.95 	,0.2145 	,2027.9700		,0.1367 	,1414		,31.76},
	{81		,0.2047500 	,1.3235	,12.95 	,0.2165 	,2057.9400		,0.1383 	,1440		,32.15},
	{82		,0.2070250 	,1.3382	,13.34 	,0.2186 	,2088.0000		,0.1400 	,1466		,32.54},
	{83		,0.2093000 	,1.3529	,13.34 	,0.2205 	,2117.9700		,0.1417 	,1492		,32.94},
	{84		,0.2115750 	,1.3676	,13.73 	,0.2225 	,2147.9400		,0.1433 	,1518		,33.33},
	{85		,0.2138500 	,1.3824	,13.73 	,0.2246 	,2178.0000		,0.1450 	,1545		,33.72},
	{86		,0.2161250 	,1.3971	,13.73 	,0.2265 	,2209.9680		,0.1467 	,1572		,34.11},
	{87		,0.2184000 	,1.4118	,14.12 	,0.2285 	,2241.9360		,0.1483 	,1599		,34.50},
	{88		,0.2206750 	,1.4265	,14.12 	,0.2306 	,2274.0000		,0.1500 	,1626		,34.90},
	{89		,0.2229500 	,1.4412	,14.12 	,0.2325 	,2305.9680		,0.1517 	,1653		,35.29},
	{90		,0.2252250 	,1.4559	,14.51 	,0.2345 	,2337.9360		,0.1533 	,1681		,35.68},
	{91		,0.2275000 	,1.4706	,14.51 	,0.2366 	,2370.0000		,0.1550 	,1709		,36.07},
	{92		,0.2297750 	,1.4853	,14.51 	,0.2385 	,2401.9680		,0.1567 	,1737		,36.47},
	{93		,0.2320500 	,1.5000	,14.91 	,0.2404 	,2433.9360		,0.1583 	,1765		,36.86},
	{94		,0.2343250 	,1.5147	,14.91 	,0.2424 	,2466.0000		,0.1600 	,1793		,37.25},
	{95		,0.2366000 	,1.5294	,15.30 	,0.2442 	,2497.9680		,0.1617 	,1822		,37.64},
	{96		,0.2388750 	,1.5441	,15.30 	,0.2460 	,2529.9360		,0.1633 	,1851		,38.03},
	{97		,0.2411500 	,1.5588	,15.30 	,0.2479 	,2562.0000		,0.1650 	,1880		,38.43},
	{98		,0.2434250 	,1.5735	,15.69 	,0.2498 	,2593.9680		,0.1667 	,1909		,38.82},
	{99		,0.2457000 	,1.5882	,15.69 	,0.2517 	,2625.9360		,0.1683 	,1938		,39.21},
	{100	,0.2479750 	,1.6029	,15.69 	,0.2537 	,2658.0000 		,0.1700 	,1967		,39.60},
	{101	,0.2502500 	,1.6176	,16.08 	,0.2555 	,2691.9660 		,0.1717 	,1967		,40.00},
	{102	,0.2525250 	,1.6324	,16.08 	,0.2573 	,2725.9320 		,0.1733 	,1967		,40.39},
	{103	,0.2548000 	,1.6471	,16.48 	,0.2592 	,2760.0000 		,0.1750 	,1967		,40.78},
	{104	,0.2570750 	,1.6618	,16.48 	,0.2610 	,2793.9660 		,0.1767 	,1967		,41.17},
	{105	,0.2593500 	,1.6765	,16.48 	,0.2628 	,2827.9320 		,0.1783 	,1967		,41.56},
	{106	,0.2616250 	,1.6912	,16.87 	,0.2647 	,2862.0000 		,0.1800 	,1967		,41.96},
	{107	,0.2639000 	,1.7059	,16.87 	,0.2664 	,2895.9660 		,0.1817 	,1967		,42.35},
	{108	,0.2661750 	,1.7206	,16.87 	,0.2682 	,2929.9320 		,0.1833 	,1967		,42.74},
	{109	,0.2684500 	,1.7353	,17.26 	,0.2700 	,2964.0000 		,0.1850 	,1967		,43.13},
	{110	,0.2707250 	,1.7500	,17.26 	,0.2717 	,2997.9660 		,0.1867 	,1967		,43.52},
	{111	,0.2730000 	,1.7647	,17.65 	,0.2735 	,3031.9200  	,0.1883 	,1967		,43.52},
	{112	,0.2752750 	,1.7794	,17.65 	,0.2753 	,3066.0000  	,0.1900 	,1967		,43.52},
	{113	,0.2775500 	,1.7941	,17.65 	,0.2770 	,3099.9600  	,0.1917 	,1967		,43.52},
	{114	,0.2798250 	,1.8088	,18.04 	,0.2788 	,3133.9200  	,0.1933 	,1967		,43.52},
	{115	,0.2821000 	,1.8235	,18.04 	,0.2806 	,3168.0000  	,0.1950 	,1967		,43.52},
	{116	,0.2843750 	,1.8382	,18.04 	,0.2822 	,3203.9400  	,0.1967 	,1967		,43.52},
	{117	,0.2866500 	,1.8529	,18.44 	,0.2839 	,3239.9100  	,0.1983 	,1967		,43.52},
	{118	,0.2889250 	,1.8676	,18.44 	,0.2857 	,3276.0000  	,0.2000 	,1967		,43.52},
	{119	,0.2912000 	,1.8824	,18.83 	,0.2872 	,3311.9400  	,0.2017 	,1967		,43.52},
	{120	,0.2934750 	,1.8971	,18.83 	,0.2888 	,3347.9100  	,0.2033 	,1967		,43.52},
	{121	,0.2957500 	,1.9118	,18.83 	,0.2905 	,3384.0000  	,0.2050 	,1967		,43.52},
	{122	,0.2980250 	,1.9265	,19.22 	,0.2921 	,3419.9400  	,0.2067 	,1967		,43.52},
	{123	,0.3003000 	,1.9412	,19.22 	,0.2938 	,3455.9100  	,0.2083 	,1967		,43.52},
	{124	,0.3025750 	,1.9559	,19.22 	,0.2956 	,3492.0000  	,0.2100 	,1967		,43.52},
	{125	,0.3048500 	,1.9706	,19.61 	,0.2972 	,3527.9400  	,0.2117 	,1967		,43.52},
	{126	,0.3071250 	,1.9853	,19.61 	,0.2989 	,3563.9100  	,0.2133 	,1967		,43.52},
	{127	,0.3094000 	,2.0000	,19.61 	,0.3007 	,3600.0000  	,0.2150 	,1967		,43.52},
	{128	,0.3116750 	,2.0147	,20.00 	,0.3022 	,3635.9400  	,0.2167 	,1967		,43.52},
	{129	,0.3139500 	,2.0294	,20.00 	,0.3038 	,3671.9100  	,0.2183 	,1967		,43.52},
	{130	,0.3162250 	,2.0441	,20.40 	,0.3055 	,3708.0000  	,0.2200 	,1967		,43.52},
	{131	,0.3185000 	,2.0588	,20.40 	,0.3070 	,3745.9500  	,0.2217 	,1967		,43.52},
	{132	,0.3207750 	,2.0735	,20.40 	,0.3086 	,3783.9000  	,0.2233 	,1967		,43.52},
	{133	,0.3230500 	,2.0882	,20.79 	,0.3103 	,3822.0000  	,0.2250 	,1967		,43.52},
	{134	,0.3253250 	,2.1029	,20.79 	,0.3118 	,3859.9500  	,0.2267 	,1967		,43.52},
	{135	,0.3276000 	,2.1176	,20.79 	,0.3134 	,3897.9000  	,0.2283 	,1967		,43.52},
	{136	,0.3298750 	,2.1324	,21.18 	,0.3151 	,3936.0000  	,0.2300 	,1967		,43.52},
	{137	,0.3321500 	,2.1471	,21.18 	,0.3166 	,3973.9500  	,0.2317 	,1967		,43.52},
	{138	,0.3344250 	,2.1618	,21.57 	,0.3181 	,4011.9000  	,0.2333 	,1967		,43.52},
	{139	,0.3367000 	,2.1765	,21.57 	,0.3197 	,4050.0000  	,0.2350 	,1967		,43.52},
	{140	,0.3389750 	,2.1912	,21.57 	,0.3212 	,4087.9500  	,0.2367 	,1967		,43.52},
	{141	,0.3412500 	,2.2059	,21.97 	,0.3227 	,4125.9000  	,0.2383 	,1967		,43.52},
	{142	,0.3435250 	,2.2206	,21.97 	,0.3243 	,4164.0000  	,0.2400 	,1967		,43.52},
	{143	,0.3458000 	,2.2353	,21.97 	,0.3258 	,4201.9500  	,0.2417 	,1967		,43.52},
	{144	,0.3480750 	,2.2500	,22.36 	,0.3273 	,4239.9000  	,0.2433 	,1967		,43.52},
	{145	,0.3503500 	,2.2647	,22.36 	,0.3289 	,4278.0000  	,0.2450 	,1967		,43.52},
	{146	,0.3526250 	,2.2794	,22.75 	,0.3303 	,4317.9600  	,0.2467 	,1967		,43.52},
	{147	,0.3549000 	,2.2941	,22.75 	,0.3318 	,4357.9200  	,0.2483 	,1967		,43.52},
	{148	,0.3571750 	,2.3088	,22.75 	,0.3333 	,4398.0000  	,0.2500 	,1967		,43.52},
	{149	,0.3594500 	,2.3235	,23.14 	,0.3347 	,4437.9600  	,0.2517 	,1967		,43.52},
	{150	,0.3617250 	,2.3382	,23.14 	,0.3362 	,4477.9200  	,0.2533 	,1967		,43.52},
	{151	,0.3640000 	,2.3529	,23.14 	,0.3377 	,4518.0000  	,0.2550 	,1967		,43.52},
	{152	,0.3662750 	,2.3676	,23.53 	,0.3391 	,4557.9600  	,0.2567 	,1967		,43.52},
	{153	,0.3685500 	,2.3824	,23.53 	,0.3406 	,4597.9200  	,0.2583 	,1967		,43.52},
	{154	,0.3708250 	,2.3971	,23.93 	,0.3421 	,4638.0000  	,0.2600 	,1967		,43.52},
	{155	,0.3731000 	,2.4118	,23.93 	,0.3434 	,4677.9600  	,0.2617 	,1967		,43.52},
	{156	,0.3753750 	,2.4265	,23.93 	,0.3448 	,4717.9200  	,0.2633 	,1967		,43.52},
	{157	,0.3776500 	,2.4412	,24.32 	,0.3463 	,4758.0000  	,0.2650 	,1967		,43.52},
	{158	,0.3799250 	,2.4559	,24.32 	,0.3476 	,4797.9600  	,0.2667 	,1967		,43.52},
	{159	,0.3822000 	,2.4706	,24.32 	,0.3490 	,4837.9200  	,0.2683 	,1967		,43.52},
	{160	,0.3844750 	,2.4853	,24.71 	,0.3505 	,4878.0000  	,0.2700 	,1967		,43.52},
	{161	,0.3867500 	,2.5000	,24.71 	,0.3518 	,4919.9400  	,0.2717 	,1967		,43.52},
	{162	,0.3890250 	,2.5147	,24.71 	,0.3532 	,4961.9100  	,0.2733 	,1967		,43.52},
	{163	,0.3913000 	,2.5294	,25.10 	,0.3547 	,5004.0000  	,0.2750 	,1967		,43.52},
	{164	,0.3935750 	,2.5441	,25.10 	,0.3560 	,5045.9400  	,0.2767 	,1967		,43.52},
	{165	,0.3958500 	,2.5588	,25.50 	,0.3574 	,5087.9100  	,0.2783 	,1967		,43.52},
	{166	,0.3981250 	,2.5735	,25.50 	,0.3589 	,5130.0000  	,0.2800 	,1967		,43.52},
	{167	,0.4004000 	,2.5882	,25.50 	,0.3602 	,5171.9400  	,0.2817 	,1967		,43.52},
	{168	,0.4026750 	,2.6029	,25.89 	,0.3616 	,5213.9100  	,0.2833 	,1967		,43.52},
	{169	,0.4049500 	,2.6176	,25.89 	,0.3631 	,5256.0000  	,0.2850 	,1967		,43.52},
	{170	,0.4072250 	,2.6324	,25.89 	,0.3644 	,5297.9400  	,0.2867 	,1967		,43.52},
	{171	,0.4095000 	,2.6471	,26.28 	,0.3657 	,5339.9100  	,0.2883 	,1967		,43.52},
	{172	,0.4117750 	,2.6618	,26.28 	,0.3671 	,5382.0000  	,0.2900 	,1967		,43.52},
	{173	,0.4140500 	,2.6765	,26.67 	,0.3684 	,5423.9400  	,0.2917 	,1967		,43.52},
	{174	,0.4163250 	,2.6912	,26.67 	,0.3697 	,5465.9100  	,0.2933 	,1967		,43.52},
	{175	,0.4186000 	,2.7059	,26.67 	,0.3711 	,5508.0000  	,0.2950 	,1967		,43.52},
	{176	,0.4208750 	,2.7206	,27.06 	,0.3723 	,5551.9500  	,0.2967 	,1967		,43.52},
	{177	,0.4231500 	,2.7353	,27.06 	,0.3736 	,5595.9000  	,0.2983 	,1967		,43.52},
	{178	,0.4254250 	,2.7500	,27.06 	,0.3749 	,5640.0000  	,0.3000 	,1967		,43.52},
	{179	,0.4277000 	,2.7647	,27.46 	,0.3761 	,5683.9500  	,0.3017 	,1967		,43.52},
	{180	,0.4299750 	,2.7794	,27.46 	,0.3774 	,5727.9000  	,0.3033 	,1967		,43.52},
	{181	,0.4322500 	,2.7941	,27.85 	,0.3787 	,5772.0000  	,0.3050 	,1967		,43.52},
	{182	,0.4345250 	,2.8088	,27.85 	,0.3799 	,5815.9500  	,0.3067 	,1967		,43.52},
	{183	,0.4368000 	,2.8235	,27.85 	,0.3812 	,5859.9000  	,0.3083 	,1967		,43.52},
	{184	,0.4390750 	,2.8382	,28.24 	,0.3825 	,5904.0000  	,0.3100 	,1967		,43.52},
	{185	,0.4413500 	,2.8529	,28.24 	,0.3837 	,5947.9500  	,0.3117 	,1967		,43.52},
	{186	,0.4436250 	,2.8676	,28.24 	,0.3850 	,5991.9000  	,0.3133 	,1967		,43.52},
	{187	,0.4459000 	,2.8824	,28.63 	,0.3863 	,6036.0000  	,0.3150 	,1967		,43.52},
	{188	,0.4481750 	,2.8971	,28.63 	,0.3875 	,6079.9500  	,0.3167 	,1967		,43.52},
	{189	,0.4504500 	,2.9118	,28.63 	,0.3888 	,6123.9000  	,0.3183 	,1967		,43.52},
	{190	,0.4527250 	,2.9265	,29.02 	,0.3901 	,6168.0000  	,0.3200 	,1967		,43.52},
	{191	,0.4550000 	,2.9412	,29.02 	,0.3913 	,6213.9300  	,0.3217 	,1967		,43.52},
	{192	,0.4572750 	,2.9559	,29.42 	,0.3926 	,6259.8900  	,0.3233 	,1967		,43.52},
	{193	,0.4595500 	,2.9706	,29.42 	,0.3939 	,6306.0000  	,0.3250 	,1967		,43.52},
	{194	,0.4618250 	,2.9853	,29.42 	,0.3950 	,6351.9300  	,0.3267 	,1967		,43.52},
	{195	,0.4641000 	,3.0000	,29.81 	,0.3962 	,6397.8900  	,0.3283 	,1967		,43.52},
	{196	,0.4663750 	,3.0147	,29.81 	,0.3974 	,6444.0000  	,0.3300 	,1967		,43.52},
	{197	,0.4686500 	,3.0294	,29.81 	,0.3985 	,6489.9300  	,0.3317 	,1967		,43.52},
	{198	,0.4709250 	,3.0441	,30.20 	,0.3997 	,6535.8900  	,0.3333 	,1967		,43.52},
	{199	,0.4732000 	,3.0588	,30.20 	,0.4009 	,6582.0000  	,0.3350 	,1967		,43.52},
	{200	,0.4754750 	,3.0735	,30.59 	,0.4020 	,6627.9300  	,0.3367 	,1967		,43.52},
	{201	,0.4777500 	,3.0882	,30.59 	,0.4032 	,6673.8900  	,0.3383 	,1967		,43.52},
	{202	,0.4800250 	,3.1029	,30.59 	,0.4044 	,6720.0000  	,0.3400 	,1967		,43.52},
	{203	,0.4823000 	,3.1176	,30.99 	,0.4055 	,6765.9300  	,0.3417 	,1967		,43.52},
	{204	,0.4845750 	,3.1324	,30.99 	,0.4067 	,6811.8900  	,0.3433 	,1967		,43.52},
	{205	,0.4868500 	,3.1471	,30.99 	,0.4079 	,6858.0000  	,0.3450 	,1967		,43.52},
	{206	,0.4891250 	,3.1618	,31.38 	,0.4090 	,6905.9400  	,0.3467 	,1967		,43.52},
	{207	,0.4914000 	,3.1765	,31.38 	,0.4102 	,6953.8800  	,0.3483 	,1967		,43.52},
	{208	,0.4936750 	,3.1912	,31.77 	,0.4114 	,7002.0000  	,0.3500 	,1967		,43.52},
	{209	,0.4959500 	,3.2059	,31.77 	,0.4125 	,7049.9400  	,0.3517 	,1967		,43.52},
	{210	,0.4982250 	,3.2206	,31.77 	,0.4137 	,7097.8800  	,0.3533 	,1967		,43.52},
	{211	,0.5005000 	,3.2353	,32.16 	,0.4149 	,7146.0000  	,0.3550 	,1967		,43.52},
	{212	,0.5027750 	,3.2500	,32.16 	,0.4160 	,7193.9400  	,0.3567 	,1967		,43.52},
	{213	,0.5050500 	,3.2647	,32.16 	,0.4172 	,7241.8800  	,0.3583 	,1967		,43.52},
	{214	,0.5073250 	,3.2794	,32.55 	,0.4184 	,7290.0000  	,0.3600 	,1967		,43.52},
	{215	,0.5096000 	,3.2941	,32.55 	,0.4195 	,7337.9400  	,0.3617 	,1967		,43.52},
	{216	,0.5118750 	,3.3088	,32.95 	,0.4207 	,7385.8800  	,0.3633 	,1967		,43.52},
	{217	,0.5141500 	,3.3235	,32.95 	,0.4219 	,7434.0000  	,0.3650 	,1967		,43.52},
	{218	,0.5164250 	,3.3382	,32.95 	,0.4229 	,7481.9400  	,0.3667 	,1967		,43.52},
	{219	,0.5187000 	,3.3529	,33.34 	,0.4240 	,7529.8800  	,0.3683 	,1967		,43.52},
	{220	,0.5209750 	,3.3676	,33.34 	,0.4252 	,7578.0000  	,0.3700 	,1967		,43.52},
	{221	,0.5232500 	,3.3824	,33.34 	,0.4262 	,7627.9500  	,0.3717 	,1967		,43.52},
	{222	,0.5255250 	,3.3971	,33.73 	,0.4273 	,7677.9000  	,0.3733 	,1967		,43.52},
	{223	,0.5278000 	,3.4118	,33.73 	,0.4285 	,7728.0000  	,0.3750 	,1967		,43.52},
	{224	,0.5300750 	,3.4265	,33.73 	,0.4295 	,7777.9500  	,0.3767 	,1967		,43.52},
	{225	,0.5323500 	,3.4412	,34.12 	,0.4306 	,7827.9000  	,0.3783 	,1967		,43.52},
	{226	,0.5346250 	,3.4559	,34.12 	,0.4318 	,7878.0000  	,0.3800 	,1967		,43.52},
	{227	,0.5369000 	,3.4706	,34.51 	,0.4328 	,7927.9500  	,0.3817 	,1967		,43.52},
	{228	,0.5391750 	,3.4853	,34.51 	,0.4338 	,7977.9000  	,0.3833 	,1967		,43.52},
	{229	,0.5414500 	,3.5000	,34.51 	,0.4349 	,8028.0000  	,0.3850 	,1967		,43.52},
	{230	,0.5437250 	,3.5147	,34.91 	,0.4359 	,8077.9500  	,0.3867 	,1967		,43.52},
	{231	,0.5460000 	,3.5294	,34.91 	,0.4370 	,8127.9000  	,0.3883 	,1967		,43.52},
	{232	,0.5482750 	,3.5441	,34.91 	,0.4381 	,8178.0000  	,0.3900 	,1967		,43.52},
	{233	,0.5505500 	,3.5588	,35.30 	,0.4391 	,8227.9500  	,0.3917 	,1967		,43.52},
	{234	,0.5528250 	,3.5735	,35.30 	,0.4401 	,8277.9000  	,0.3933 	,1967		,43.52},
	{235	,0.5551000 	,3.5882	,35.69 	,0.4412 	,8328.0000  	,0.3950 	,1967		,43.52},
	{236	,0.5573750 	,3.6029	,35.69 	,0.4422 	,8379.9300  	,0.3967 	,1967		,43.52},
	{237	,0.5596500 	,3.6176	,35.69 	,0.4433 	,8431.8900  	,0.3983 	,1967		,43.52},
	{238	,0.5619250 	,3.6324	,36.08 	,0.4444 	,8484.0000  	,0.4000 	,1967		,43.52},
	{239	,0.5642000 	,3.6471	,36.08 	,0.4454 	,8535.9300  	,0.4017 	,1967		,43.52},
	{240	,0.5664750 	,3.6618	,36.08 	,0.4464 	,8587.8900  	,0.4033 	,1967		,43.52},
	{241	,0.5687500 	,3.6765	,36.48 	,0.4475 	,8640.0000  	,0.4050 	,1967		,43.52},
	{242	,0.5710250 	,3.6912	,36.48 	,0.4485 	,8691.9300  	,0.4067 	,1967		,43.52},
	{243	,0.5733000 	,3.7059	,36.87 	,0.4495 	,8743.8900  	,0.4083 	,1967		,43.52},
	{244	,0.5755750 	,3.7206	,36.87 	,0.4505 	,8796.0000  	,0.4100 	,1967		,43.52},
	{245	,0.5778500 	,3.7353	,36.87 	,0.4515 	,8847.9300  	,0.4117 	,1967		,43.52},
	{246	,0.5801250 	,3.7500	,37.26 	,0.4525 	,8899.8900  	,0.4133 	,1967		,43.52},
	{247	,0.5824000 	,3.7647	,37.26 	,0.4535 	,8952.0000  	,0.4150 	,1967		,43.52},
	{248	,0.5846750 	,3.7794	,37.26 	,0.4545 	,9003.9300  	,0.4167 	,1967		,43.52},
	{249	,0.5869500 	,3.7941	,37.65 	,0.4555 	,9055.8900  	,0.4183 	,1967		,43.52},
	{250	,0.5892250 	,3.8088	,37.65 	,0.4565 	,9108.0000  	,0.4200 	,1967		,43.52},
	{251	,0.5915000 	,3.8235	,38.04 	,0.4574 	,9161.9400  	,0.4217 	,1967		,43.52},
	{252	,0.5937750 	,3.8382	,38.04 	,0.4584 	,9215.8800  	,0.4233 	,1967		,43.52},
	{253	,0.5960500 	,3.8529	,38.04 	,0.4593 	,9270.0000  	,0.4250 	,1967		,43.52},
	{254	,0.5983250 	,3.8676	,38.44 	,0.4602 	,9323.9400  	,0.4267 	,1967		,43.52},
	{255	,0.6006000 	,3.8824	,38.44 	,0.4612 	,9377.8800  	,0.4283 	,1967		,43.52},
	{256	,0.6028750 	,3.8971	,38.44 	,0.4621 	,9432.0000  	,0.4300 	,1967		,43.52},
	{257	,0.6051500 	,3.9118	,38.83 	,0.4630 	,9485.9400  	,0.4317 	,1967		,43.52},
	{258	,0.6074250 	,3.9265 ,38.83 	,0.4640 	,9539.8800  	,0.4333 	,1967		,43.52},
	{259	,0.6097000 	,3.9412 ,38.83 	,0.4649 	,9594.0000  	,0.4350 	,1967		,43.52},
	{260	,0.6119750 	,3.9559 ,39.22 	,0.4658 	,9647.9400  	,0.4367 	,1967		,43.52},
	{261	,0.6142500 	,3.9706 ,39.22 	,0.4668 	,9701.8800  	,0.4383 	,1967		,43.52},
	{262	,0.6165250 	,3.9853 ,39.61 	,0.4677 	,9756.0000  	,0.4400 	,1967		,43.52},
	{263	,0.6188000 	,4.0000 ,39.61 	,0.4686 	,9809.9400  	,0.4417 	,1967		,43.52},
	{264	,0.6210750 	,4.0147 ,39.61 	,0.4696 	,9863.8800  	,0.4433 	,1967		,43.52},
	{265	,0.6233500 	,4.0294 ,40.00 	,0.4705 	,9918.0000  	,0.4450 	,1967		,43.52},
	{266	,0.6256250 	,4.0441 ,40.00 	,0.4714 	,9973.9200  	,0.4467 	,1967		,43.52},
	{267	,0.6279000 	,4.0588 ,40.00 	,0.4724 	,10029.8700 	,0.4483 	,1967		,43.52},
	{268	,0.6301750 	,4.0735 ,40.40 	,0.4733 	,10086.0000 	,0.4500 	,1967		,43.52},
	{269	,0.6324500 	,4.0882 ,40.40 	,0.4742 	,10141.9200 	,0.4517 	,1967		,43.52},
	{270	,0.6347250 	,4.1029 ,40.79 	,0.4752 	,10197.8700 	,0.4533 	,1967		,43.52},
	{271	,0.6370000 	,4.1176 ,40.79 	,0.4761 	,10254.0000 	,0.4550 	,1967		,43.52},
	{272	,0.6392750 	,4.1324 ,40.79 	,0.4770 	,10309.9200 	,0.4567 	,1967		,43.52},
	{273	,0.6415500 	,4.1471 ,41.18 	,0.4780 	,10365.8700 	,0.4583 	,1967		,43.52},
	{274	,0.6438250 	,4.1618 ,41.18 	,0.4789 	,10422.0000 	,0.4600 	,1967		,43.52},
	{275	,0.6461000 	,4.1765 ,41.18 	,0.4798 	,10477.9200 	,0.4617 	,1967		,43.52},
	{276	,0.6483750 	,4.1912 ,41.57 	,0.4808 	,10533.8700 	,0.4633 	,1967		,43.52},
	{277	,0.6506500 	,4.2059 ,41.57 	,0.4817 	,10590.0000 	,0.4650 	,1967		,43.52},
	{278	,0.6529250 	,4.2206 ,41.97 	,0.4826 	,10645.9200 	,0.4667 	,1967		,43.52},
	{279	,0.6552000 	,4.2353 ,41.97 	,0.4836 	,10701.8700 	,0.4683 	,1967		,43.52},
	{280	,0.6574750 	,4.2500 ,41.97 	,0.4845 	,10758.0000 	,0.4700 	,1967		,43.52},
	{281	,0.6597500 	,4.2647 ,42.36 	,0.4853 	,10815.9300 	,0.4717 	,1967		,43.52},
	{282	,0.6620250 	,4.2794 ,42.36 	,0.4862 	,10873.8600 	,0.4733 	,1967		,43.52},
	{283	,0.6643000 	,4.2941 ,42.36 	,0.4871 	,10932.0000 	,0.4750 	,1967		,43.52},
	{284	,0.6665750 	,4.3088 ,42.75 	,0.4879 	,10989.9300 	,0.4767 	,1967		,43.52},
	{285	,0.6688500 	,4.3235 ,42.75 	,0.4887 	,11047.8600 	,0.4783 	,1967		,43.52},
	{286	,0.6711250 	,4.3382 ,43.14 	,0.4896 	,11106.0000 	,0.4800 	,1967		,43.52},
	{287	,0.6734000 	,4.3529 ,43.14 	,0.4904 	,11163.9300 	,0.4817 	,1967		,43.52},
	{288	,0.6756750 	,4.3676 ,43.14 	,0.4913 	,11221.8600 	,0.4833 	,1967		,43.52},
	{289	,0.6779500 	,4.3824 ,43.53 	,0.4922 	,11280.0000 	,0.4850 	,1967		,43.52},
	{290	,0.6802250 	,4.3971 ,43.53 	,0.4930 	,11337.9300 	,0.4867 	,1967		,43.52},
	{291	,0.6825000 	,4.4118 ,43.53 	,0.4938 	,11395.8600 	,0.4883 	,1967		,43.52},
	{292	,0.6847750 	,4.4265 ,43.93 	,0.4947 	,11454.0000 	,0.4900 	,1967		,43.52},
	{293	,0.6870500 	,4.4412 ,43.93 	,0.4955 	,11511.9300 	,0.4917 	,1967		,43.52},
	{294	,0.6893250 	,4.4559 ,43.93 	,0.4964 	,11569.8600 	,0.4933 	,1967		,43.52},
	{295	,0.6916000 	,4.4706 ,44.32 	,0.4973 	,11628.0000 	,0.4950 	,1967		,43.52},
	{296	,0.6938750 	,4.4853 ,44.32 	,0.4981 	,11685.9300 	,0.4967 	,1967		,43.52},
	{297	,0.6961500 	,4.5000 ,44.71 	,0.4989 	,11743.8600 	,0.4983 	,1967		,43.52},
	{298	,0.6984250 	,4.5147 ,44.71 	,0.4998 	,11802.0000 	,0.5000 	,1967		,43.52},
	{299	,0.7007000 	,4.5294 ,44.71 	,0.5006 	,11859.9300 	,0.5017 	,1967		,43.52},
	{300	,0.7029750 	,4.5441 ,45.10 	,0.5015 	,11917.8600 	,0.5033 	,1967		,43.52},
	{301	,0.7052500 	,4.5588 ,45.10 	,0.5024 	,11976.0000 	,0.5050 	,1967		,43.52},
	{302	,0.7075250 	,4.5735 ,45.10 	,0.5067 	,12034.1400 	,0.5067 	,1967		,43.52},
	{303	,0.7098000 	,4.5882 ,45.10 	,0.5083 	,12092.0700 	,0.5083 	,1967		,43.52},
	{304	,0.7120750 	,4.6029 ,45.50 	,0.5100 	,12150.0000 	,0.5100 	,1967		,43.52},
	{305	,0.7143500 	,4.6176 ,45.50 	,0.5117 	,12208.1400 	,0.5117 	,1967		,43.52},
	{306	,0.7166250 	,4.6324 ,45.50 	,0.5133 	,12266.0700 	,0.5133 	,1967		,43.52},
	{307	,0.7189000 	,4.6471 ,45.89 	,0.5150 	,12324.0000 	,0.5150 	,1967		,43.52},
	{308	,0.7211750 	,4.6618 ,45.89 	,0.5167 	,12382.1400 	,0.5167 	,1967		,43.52},
	{309	,0.7234500 	,4.6765 ,46.28 	,0.5183 	,12440.0700 	,0.5183 	,1967		,43.52},
	{310	,0.7257250 	,4.6912 ,46.28 	,0.5200 	,12498.0000 	,0.5200 	,1967		,43.52},
	{311	,0.7280000 	,4.7059 ,46.28 	,0.5217 	,12556.1400 	,0.5217 	,1967		,43.52},
	{312	,0.7302750 	,4.7206 ,46.67 	,0.5233 	,12614.0700 	,0.5233 	,1967		,43.52},
	{313	,0.7325500 	,4.7353 ,46.67 	,0.5250 	,12672.0000 	,0.5250 	,1967		,43.52},
	{314	,0.7348250 	,4.7500 ,46.67 	,0.5267 	,12730.1400 	,0.5267 	,1967		,43.52},
	{315	,0.7371000 	,4.7647 ,47.06 	,0.5283 	,12788.0700 	,0.5283 	,1967		,43.52},
	{316	,0.7393750 	,4.7794 ,47.06 	,0.5300 	,12846.0000 	,0.5300 	,1967		,43.52},
	{317	,0.7416500 	,4.7941 ,47.06 	,0.5317 	,12904.1400 	,0.5317 	,1967		,43.52},
	{318	,0.7439250 	,4.8088 ,47.46 	,0.5333 	,12962.0700 	,0.5333 	,1967		,43.52},
	{319	,0.7462000 	,4.8235 ,47.46 	,0.5350 	,13020.0000 	,0.5350 	,1967		,43.52},
	{320	,0.7484750 	,4.8382 ,47.85 	,0.5367 	,13078.1400 	,0.5367 	,1967		,43.52},
	{321	,0.7507500 	,4.8529 ,47.85 	,0.5383 	,13136.0700 	,0.5383 	,1967		,43.52},
	{322	,0.7530250 	,4.8676 ,47.85 	,0.5400 	,13194.0000 	,0.5400 	,1967		,43.52},
	{323	,0.7553000 	,4.8824 ,48.24 	,0.5417 	,13252.1400 	,0.5417 	,1967		,43.52},
	{324	,0.7575750 	,4.8971 ,48.24 	,0.5434 	,13310.0700 	,0.5434 	,1967		,43.52},
	{325	,0.7598500 	,4.9118 ,48.24 	,0.5450 	,13368.0000 	,0.5450 	,1967		,43.52},
	{326	,0.7621250 	,4.9265 ,48.63 	,0.5467 	,13426.1400 	,0.5467 	,1967		,43.52},
	{327	,0.7644000 	,4.9412 ,48.63 	,0.5484 	,13484.0700 	,0.5484 	,1967		,43.52},
	{328	,0.7666750 	,4.9559 ,49.02 	,0.5500 	,13542.0000 	,0.5500 	,1967		,43.52},
	{329	,0.7689500 	,4.9706 ,49.02 	,0.5517 	,13600.1400 	,0.5517 	,1967		,43.52},
	{330	,0.7712250 	,4.9853 ,49.02 	,0.5534 	,13658.0700 	,0.5534 	,1967		,43.52},
	{331	,0.7735000 	,5.0000 ,49.42 	,0.5550 	,13716.0000 	,0.5550 	,1967		,43.52},
	{332	,0.7757750 	,5.0147 ,49.42 	,0.5567 	,13774.1400 	,0.5567 	,1967		,43.52},
	{333	,0.7780500 	,5.0294 ,49.42 	,0.5584 	,13832.0700 	,0.5584 	,1967		,43.52},
	{334	,0.7803250 	,5.0441 ,49.81 	,0.5600 	,13890.0000 	,0.5600 	,1967		,43.52},
	{335	,0.7826000 	,5.0588 ,49.81 	,0.5617 	,13948.1400 	,0.5617 	,1967		,43.52},
	{336	,0.7848750 	,5.0735 ,49.81 	,0.5634 	,14006.0700 	,0.5634 	,1967		,43.52},
	{337	,0.7871500 	,5.0882 ,50.20 	,0.5650 	,14064.0000 	,0.5650 	,1967		,43.52},
	{338	,0.7894250 	,5.1029 ,50.20 	,0.5667 	,14122.1400 	,0.5667 	,1967		,43.52},
	{339	,0.7917000 	,5.1176 ,50.59 	,0.5684 	,14180.0700 	,0.5684 	,1967		,43.52},
	{340	,0.7939750 	,5.1324 ,50.59 	,0.5700 	,14238.0000 	,0.5700 	,1967		,43.52},
	{341	,0.7939750 	,5.1324 ,50.59 	,0.5700 	,14238.0000 	,0.5700 	,1967		,43.52}
};
