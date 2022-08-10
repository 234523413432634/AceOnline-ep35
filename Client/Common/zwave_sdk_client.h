//7A7A7A584023252521217E6667766D65696C3200580000000000020001000000B791AC415815010070110100591501009A010000004039C5EFC9C9010000003EC1E8CA017176785A5E24242421217E7A766D657473724200
#pragma once

#ifndef BOOL
typedef int BOOL;
#endif

#define ZSOPT_USESYSGUARD			0x0001
#define ZSOPT_SHOWSPLASH			0x0002
#define ZSOPT_SHOWTRAY				0x0004

#define ZSOPT_SPLASH_CENTER			0x0100
#define ZSOPT_SPLASH_TOP_LEFT		0x0200
#define ZSOPT_SPLASH_TOP_RIGHT		0x0300
#define ZSOPT_SPLASH_BOTTOM_LEFT	0x0400
#define ZSOPT_SPLASH_BOTTOM_RIGHT	0x0500

#ifndef ZWAVE_ERROR_CODE
#define ZWAVE_STATUS_INVALID_HANDLE				0xE0190001
#define ZWAVE_STATUS_CODE_NOT_FOUND				0xE0190002
#define ZWAVE_STATUS_NOT_INITIALIZED			0xE0190003
#define ZWAVE_STATUS_UNICODE_CONVERSION_FAIL	0xE0190004
#define ZWAVE_STATUS_INVALID_PARAMETER			0xE0190005
#define ZWAVE_STATUS_INVALID_DATABASE			0xE0190006
#define ZWAVE_STATUS_INSUFFICIENT_RESOURCE		0xE0190007
#define ZWAVE_STATUS_UNHANDLED_EXCEPTION		0xE0190008
#define ZWAVE_STATUS_STATE_MISMATCH				0xE0190009
#define ZWAVE_STATUS_INVALID_DLL				0xE0190010
#define ZWAVE_STATUS_INVALID_OPERATION			0xE0190011
#define ZWAVE_STATUS_INVALID_PACKET				0xE0190012
#endif

typedef char *PACKETDATA;
typedef const char *CPACKETDATA;

BOOL ZCWAVE_Init();
BOOL ZCWAVE_Cleanup();
BOOL ZCWAVE_Probe(CPACKETDATA szPack, PACKETDATA szReturn, SIZE_T nSize);
HANDLE ZCWAVE_CreateCodeBox();
BOOL ZCWAVE_CloseCodeBox(HANDLE h);
BOOL ZCWAVE_ProbeCodeBox(HANDLE h, CPACKETDATA data, PACKETDATA buf, SIZE_T size);
BOOL ZCWAVE_SysEnter(LPCTSTR path, DWORD opt);
BOOL ZCWAVE_SysExit();

#if defined(_ATUM_CLIENT)
FORCEINLINE
unsigned long
InterlockedExchangefA(
_Inout_ _Interlocked_operand_ unsigned long volatile *Target,
_In_ unsigned long Value
)
{
	return (unsigned long)_InterlockedExchange((volatile long*)Target, (long)Value);
}

FORCEINLINE
unsigned long
InterlockedCompareExchangefA(
_Inout_ _Interlocked_operand_ unsigned long volatile *Destination,
_In_ unsigned long Exchange,
_In_ unsigned long Comperand
)
{
	return (unsigned long)_InterlockedCompareExchange((volatile long*)Destination, (long)Exchange, (long)Comperand);
}
#endif