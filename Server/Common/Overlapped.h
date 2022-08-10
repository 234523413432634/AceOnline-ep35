///////////////////////////////////////////////////////////////////////////////
//  Overlapped.h : 
//  
//  Date	: 2004-03-17 by cmkwon
///////////////////////////////////////////////////////////////////////////////

#ifndef _OVERLAPPED_H_
#define _OVERLAPPED_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SocketHeader.h"


///////////////////////////////////////////////////////////////////////////////
// COverlapped 객체를 delete 하기 위한 define
#define SAFE_DELETE_COverlapped(pOver)	\
	{									\
		if(NULL != pOver				\
			&& pOver->GetOverlappedType() == COverlapped::EN_OVERLAPPED_TYPE_DYNAMIC)	\
		{								\
			delete (pOver);				\
			(pOver) = NULL;				\
		}								\
	}


class COverlapped;				// 2008-03-13 by cmkwon, 대규모 전쟁시 클라이언트 팅기는거 수정 - 
struct SSendedOverlappedInfo	// 2008-03-13 by cmkwon, 대규모 전쟁시 클라이언트 팅기는거 수정 - 
{
	COverlapped		*pOverlapped;
	BYTE			*pbyData;
	int				nSendedSize;
};
typedef vector<SSendedOverlappedInfo>		vectSSendedOverlappedInfo;	// 2008-03-13 by cmkwon, 대규모 전쟁시 클라이언트 팅기는거 수정 - 

class COverlapped : public OVERLAPPED
{
public:
	typedef enum
	{
		EN_OPERATION_MODE_READ		= 0,
		EN_OPERATION_MODE_WRITE		= 1
	} ENOperationMode;
	typedef enum
	{
		EN_OVERLAPPED_TYPE_STATIC	= 2,
		EN_OVERLAPPED_TYPE_DYNAMIC	= 3
	} ENOverlappedType;
public:	
	COverlapped(ENOperationMode i_enOperationMode, 
		ENOverlappedType i_enOverlappedType, BOOL Encoding = FALSE);
	~COverlapped();

	///////////////////////////////////////////////////////////////////////////
	// Property
	BYTE GetOperationMode(void){				return m_enOperationMode;};
	BYTE GetOverlappedType(void){				return m_enOverlappedType;};
	WSABUF * GetWSABUFPtr(void){				return &m_WSABUF;};
	sockaddr_in * Getsocketaddr_inPtr(void){	return &m_socketaddr_in;};
	int GetSizesocketaddr_in(void){				return m_nSizesocketaddr_in;};
	int * GetSizesocketaddr_inPtr(void){		return &m_nSizesocketaddr_in;};

	// Operations
	// 2008-03-13 by cmkwon, 대규모 전쟁시 클라이언트 팅기는거 수정 - 인자추가(SSendedOverlappedInfo *o_pSendedOverInfo)
	BOOL AddData(SSendedOverlappedInfo *o_pSendedOverInfo, BYTE* pData, int nSize);					// COverlapped 클래스의 내부 버퍼에 데이타를 추가한다.
	int GetDataSize(void);									// COverlapped 클래스의 내부 버퍼에 추가된 데이타의 사이즈를 리턴
	void ResetOverlapped(void);								// COverlapped 클래스를 초기화 한다.
	void EncodePacket(BYTE seq);							// m_bEncodingFlag 가 TRUE이고 m_bEncodedFlag 가 FALSE일때 Encoding을 한다.
	void SetSequenceNumber(BYTE seq);						// m_bEncodingFlag 가 FALSE일때 Sequence Number 를 설정한다.
	BYTE GetSequenceNumber();								// m_bEncodingFlag 가 TRUE이고 m_bEncodedFlag 가 TRUE일때 패킷에 설정된 Sequence Number
															// m_bEncodingFlag 가 FALSE일때 패킷에 설정된 Sequence Number
	BOOL IsPacketEncoded();									// 패킷이 Encoding 되었는지의 여부를 리턴

	///////////////////////////////////////////////////////////////////////////
	// new, delete 를 오버라이딩한다.
	void * operator new(size_t size);
	void operator delete(void* p);
	
private:	
	BYTE				m_enOperationMode;					// Read Or Write Mode 변수
	BYTE				m_enOverlappedType;					// Overlapped 객체의 Static or Dynamic Type 변수
	BYTE				m_bEncodingFlag;					// COverlapped 가 Encoding 을 위한 것인지의 Flag
	BYTE				m_bEncodedFlag;						// COverlapped 가 Encoding 되었는지의 Flag
	WSABUF				m_WSABUF;							// ReadFile and WriteFile 인자	
	char				lpBuff[SIZE_MAX_SOCKET_BUFFER];		// Data Buffer
	sockaddr_in			m_socketaddr_in;					// UDP 지원을 위한 변수(샹대방 주소를 설정)
	int					m_nSizesocketaddr_in;				// UDP 지원을 위한 변수(socketaddr 사이즈)

	///////////////////////////////////////////////////////////////////////////
	// static 멤버 변수
	static char*		pXOR_ENCODE_BYTES;	
};
#endif // _OVERLAPPED_H_endif
