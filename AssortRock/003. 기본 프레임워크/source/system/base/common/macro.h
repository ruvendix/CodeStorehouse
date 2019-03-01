/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-08-07 (AssortRock 전용으로 수정)
 *
 * <파일 내용>
 * 공동으로 사용되는 매크로 모음입니다.
 * 전역 함수에 영향을 받습니다.
 *
 ====================================================================================*/
#ifndef MACRO_H__
#define MACRO_H__

#include "global_function.h"


// ====================================================================================
// 비트 관련 매크로입니다.
// ====================================================================================
#define ON_BIT(data, value)  (data |= value)
#define OFF_BIT(data, value) (data &= ~value)
#define IS_BIT(data, value)  ((data & value) != 0)
#define TOGGLE_BIT(data, value)\
if (IS_BIT(data, value))\
{\
	OFF_BIT(data, value);\
}\
else\
{\
	ON_BIT(data, value);\
}

// ====================================================================================
// 동적 할당, Release, LostDevice, ResetDevice 관련 매크로입니다.
// 동적 할당 영역은 _NORMAL_BLOCK으로 설정합니다.
// ====================================================================================
#if defined(DEBUG) | defined(_DEBUG)
#define RXNew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define RXNew new
#endif

#if defined(DEBUG) | defined(_DEBUG)
#define RXMalloc(size) _malloc_dbg(size, _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define RXMalloc(size) malloc(size)
#endif

#define SAFE_DELETE(ptr)\
if (ptr != nullptr)\
{\
	delete ptr;\
	ptr = nullptr;\
}

#define SAFE_DELTE_ARR(ptr)\
if (ptr != nullptr)\
{\
	delete[] ptr;\
	ptr = nullptr;\
}

#define SAFE_RELEASE(ptr)\
if (ptr != nullptr)\
{\
    ptr->Release();\
    ptr = nullptr;\
}

// vector의 요소가 동적할당되었을 때 전부 해제합니다.
// 요소가 포인터 형식이 아니면 컴파일 실패됩니다.
#define ALL_DELETE_FOR_VECTOR(vec)\
INT32 size = vec.size();\
for (INT32 i = 0; i < size; ++i)\
{\
	SAFE_DELETE(vec[i]);\
}

// ====================================================================================
// 메시지 박스 관련 매크로입니다.
// ====================================================================================
#if defined(_UNICODE) || defined(UNICODE)
#define WIDEN(x)       L##x
#define WIDEN2(x)      WIDEN(x)
#define __TFILE__      WIDEN2(__FILE__)
#define __TFUNCTION__  WIDEN2(__FUNCTION__)
#define __TFUNCSIG__   WIDEN2(__FUNCSIG__)
#else
#define __TFILE__      __FILE__
#define __TFUNCTION__  __FUNCTION__
#define __TFUNCSIG__   __FUNCSIG__
#endif

// WCHAR 전용입니다.
#define __WFILE__     WIDEN2(__FILE__)
#define __WFUNCTION__ WIDEN2(__FUNCTION__)
#define __WFUNCSIG__  WIDEN2(__FUNCSIG__)

// 메시지 박스만 출력합니다.
// 프로젝트 모드에 상관없이 무조건 알려줘야 할 때 사용합니다.
#if defined(_UNICODE) || defined(UNICODE)
#define MSGBOX(szText)      RX::ShowMessageBoxImplW(L##szText)
#else					         
#define MSGBOX(szText)      RX::ShowMessageBoxImplA(szText)
#endif


// ====================================================================================
// 널포인터 체크 관련 매크로입니다.
// ====================================================================================
#define NULLCHK(ptr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is nullptr!");\
}

#define NULLCHK_RETURN(ptr, szErr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is nullptr!");\
	RXERRLOG_RETURN(szErr);\
}

#define NULLCHK_RETURN_NOCOMENT(ptr)\
if (ptr == nullptr)\
{\
    RXERRLOG_RETURN(#ptr " is nullptr!");\
}

#define NULLCHK_RETURN_FALSE(ptr)\
if (ptr == nullptr)\
{\
	RXERRLOG_RETURN_FALSE(#ptr " is nullptr!");\
    return false;\
}

#define NULLCHK_RETURN_EFAIL(ptr, szErr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is nullptr!");\
	RXERRLOG_RETURN_EFAIL(szErr);\
}

#define NULLCHK_RETURN_EFAIL_NOCOMENT(ptr)\
if (ptr == nullptr)\
{\
    RXERRLOG_RETURN_EFAIL(#ptr " is nullptr!");\
}

#define NULLCHK_HEAPALLOC(ptr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is failed in heap allocation!");\
}

#define NULL_RETURN(ptr)\
if (ptr == nullptr)\
{\
    return;\
}

#define NULL_RETURN_OK(ptr)\
if (ptr == nullptr)\
{\
    return S_OK;\
}

// 가변인자가 지원되지 않는 매크로 함수입니다.
#define RXERRLOG_RETURN(szErr)       RXERRLOG(szErr); return
#define RXERRLOG_RETURN_FALSE(szErr) RXERRLOG(szErr); return false
#define RXERRLOG_RETURN_EFAIL(szErr) RXERRLOG(szErr); return E_FAIL


// ====================================================================================
// 스트링 관련 매크로입니다.
// ====================================================================================
#if defined(_UNICODE) || defined(UNICODE)
	#define SZ_NULL L""
#else
	#define SZ_NULL ""	
#endif


// ====================================================================================
// 에러 핸들러 관련 매크로입니다.
// ====================================================================================

// 디버그 모드만 작동, 릴리즈 모드는 X
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXDEBUGLOG(szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::DEBUG, false, false, false,\
			nullptr, __LINE__, __TFUNCSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXDEBUGLOG(szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::DEBUG, false, false, false,\
			nullptr, __LINE__, __TFUNCSIG__, szFormat, __VA_ARGS__)
	#endif
#else
	#define RXDEBUGLOG __noop
#endif

// 서식 문자열 지원, 디버그 모드에서는 디버그 출력창에도 출력
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXLOG(szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::DEBUG, false, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXLOG(szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::DEBUG, false, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, szFormat, __VA_ARGS__)
	#endif
#else
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXLOG(szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::RELEASE, false, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXLOG(szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::RELEASE, false, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, szFormat, __VA_ARGS__)
	#endif
#endif

// RXLOG()에 메시지 박스 기능이 추가된 함수입니다.
#if defined(DEBUG) || defined(_DEBUG)
#if defined(_UNICODE) || defined(UNICODE)
#define RXMSGBOXLOG(szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::DEBUG, true, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, L##szFormat, __VA_ARGS__)
#else
#define RXMSGBOXLOG(szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::DEBUG, true, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, szFormat, __VA_ARGS__)
#endif
#else
#if defined(_UNICODE) || defined(UNICODE)
#define RXMSGBOXLOG(szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::RELEASE, true, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, L##szFormat, __VA_ARGS__)
#else
#define RXMSGBOXLOG(szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::RELEASE, true, true, false,\
			nullptr, __LINE__, __TFUNCSIG__, szFormat, __VA_ARGS__)
#endif
#endif

// 서식 문자열 지원, 디버그 모드에서는 디버그 출력창에도 출력
// 메시지 박스 출력 지원, 에러 메시지 박스만 지원합니다.
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXERRLOG(szFormat, ...) RX::RXLogImplW(PROJECT_MODE::DEBUG, true, true, true,\
		nullptr, __LINE__, __TFUNCSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXERRLOG(szFormat, ...) RX::RXLogImplA(PROJECT_MODE::DEBUG, true, true, true,\
		nullptr, __LINE__, __TFUNCSIG__, szFormat, __VA_ARGS__)
	#endif
#else
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXERRLOG(szFormat, ...) RX::RXLogImplW(PROJECT_MODE::RELEASE, true, true, true,\
		nullptr, __LINE__, __TFUNCSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXERRLOG(szFormat, ...) RX::RXLogImplA(PROJECT_MODE::RELEASE, true, true, true,\
		nullptr, __LINE__, __TFUNCSIG__, szFormat, __VA_ARGS__)
	#endif
#endif

// CHAR 전용입니다.
#define RXLOG_CHAR(bMessageBox, szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::DEBUG, bMessageBox, true, false,\
			nullptr, __LINE__, __FUNCSIG__, szFormat, __VA_ARGS__)

#define RXERRLOG_CHAR(szFormat, ...) RX::RXLogImplA(PROJECT_MODE::DEBUG, true, true, true,\
		nullptr, __LINE__, __FUNCSIG__, szFormat, __VA_ARGS__)

// WCHAR 전용입니다.
#define RXLOG_WCHAR(bMessageBox, szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::DEBUG, bMessageBox, true, false,\
			nullptr, __LINE__, __WFUNCSIG__, L##szFormat, __VA_ARGS__)

#define RXERRLOG_WCHAR(szFormat, ...) RX::RXLogImplW(PROJECT_MODE::DEBUG, true, true, true,\
		nullptr, __LINE__, __WFUNCSIG__, L##szFormat, __VA_ARGS__)

// 파일, 라인, 에러 이름, 에러 내용
// GetLastError()를 이용한 Win32 API의 에러 핸들러입니다.
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplW(PROJECT_MODE::DEBUG,\
				nullptr, __LINE__, __TFUNSIG__);
	#else
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplW(PROJECT_MODE::DEBUG,\
				nullptr, __LINE__, __TFUNSIG__);
#endif
#else
	#if defined(_UNICODE) || defined(UNICODE)
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplA(PROJECT_MODE::RELEASE,\
				nullptr, __LINE__, __TFUNSIG__);
	#else
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplA(PROJECT_MODE::RELEASE,\
				nullptr, __LINE__, __TFUNSIG__);
	#endif
#endif


// ====================================================================================
// 그 외의 매크로입니다.
// ====================================================================================

// 플래그값을 문자열로 변경시키는 매크로입니다.
#define CONVERT_FLAG_TO_STRING(flag) _T(#flag)

// ====================================================================================
// 피닉스 싱글톤입니다.
// 죽었다가 다시 부활한다는 의미로 피닉스라고 합니다...
//
// 중간에 new(m_pInst) classType은 Replacement New입니다.
// 메모리를 새로 할당하지 않고 생성자만 호출합니다.
//
// 생성자와 소멸자는 시점으로 인해 고정입니다.
// 따라서 생성 작업은 Init(), 해제 작업은 Release() 같은 함수를 만들어야 합니다.
#define PHOENIX_SINGLETON(classType)\
public:\
	static classType* Instance()\
	{\
		if (m_bDestroy == true)\
		{\
			Create();\
			new(m_pInst) classType;\
			std::atexit(Destroy);\
			m_bDestroy = true;\
		}\
		if (m_pInst == nullptr)\
		{\
			Create();\
		}\
		return m_pInst;\
	}\
private:\
	classType() = default;\
	classType(const classType& rhs)  = delete;\
	classType(const classType&& rhs) = delete;\
	~classType()\
	{\
		m_bDestroy = true;\
	}\
	classType& operator=(const classType& rhs)  = delete;\
	classType& operator=(const classType&& rhs) = delete;\
	static void Create()\
	{\
		static classType inst;\
		m_pInst = &inst;\
	}\
	static void Destroy()\
	{\
		m_pInst->~classType();\
	}\
	static bool m_bDestroy;\
	static classType* m_pInst;

// 피닉스 싱글톤의 생성자 재정의가 가능한 매크로 함수입니다.
#define PHOENIX_SINGLETON_CTOR(classType)\
public:\
	static classType* Instance()\
	{\
		if (m_bDestroy == true)\
		{\
			Create();\
			new(m_pInst) classType;\
			std::atexit(Destroy);\
			m_bDestroy = true;\
		}\
		if (m_pInst == nullptr)\
		{\
			Create();\
		}\
		return m_pInst;\
	}\
private:\
	classType(const classType& rhs)  = delete;\
	classType(const classType&& rhs) = delete;\
	~classType()\
	{\
		m_bDestroy = true;\
	}\
	classType& operator=(const classType& rhs)  = delete;\
	classType& operator=(const classType&& rhs) = delete;\
	static void Create()\
	{\
		static classType inst;\
		m_pInst = &inst;\
	}\
	static void Destroy()\
	{\
		m_pInst->~classType();\
	}\
	static bool m_bDestroy;\
	static classType* m_pInst;

// 피닉스 싱글톤의 생성자 및 소멸자 재정의가 가능한 매크로 함수입니다.
// 소멸자를 재정의할 때 m_bDestroy는 필수로 처리해줘야 합니다.
#define PHOENIX_SINGLETON_FULL(classType)\
public:\
	static classType* Instance()\
	{\
		if (m_bDestroy == true)\
		{\
			Create();\
			new(m_pInst) classType;\
			std::atexit(Destroy);\
			m_bDestroy = true;\
		}\
		if (m_pInst == nullptr)\
		{\
			Create();\
		}\
		return m_pInst;\
	}\
private:\
	classType(const classType& rhs)  = delete;\
	classType(const classType&& rhs) = delete;\
	classType& operator=(const classType& rhs)  = delete;\
	classType& operator=(const classType&& rhs) = delete;\
	static void Create()\
	{\
		static classType inst;\
		m_pInst = &inst;\
	}\
	static void Destroy()\
	{\
		m_pInst->~classType();\
	}\
	static bool m_bDestroy;\
	static classType* m_pInst;

// 피닉스 싱글톤의 멤버변수 초기화 매크로 함수입니다.
#define PHOENIX_SINGLETON_INIT(classType)\
	classType* classType::m_pInst = nullptr;\
	bool classType::m_bDestroy = false;


// ====================================================================================
// 전역 인스턴스 관련 매크로 모음입니다.
// ====================================================================================
#define SINGLETON(classType) classType::Instance()

#define RXCORE                 SINGLETON(RX::RXCore)
#define RXFPSMGR               SINGLETON(RX::RXProgramFPSMgr)
#define RXSCENEMGR             SINGLETON(RX::RXSceneMgr)
#define RXPERFORMANCE_PROFILER SINGLETON(RX::RXPerformanceProfiler)

#define MAININST RXCORE->getProgramInstance()
#define MAINWND  RXCORE->getProgramInstanceHandle()

// 퍼포먼스 프로파일러의 시작과 끝은 한 세트입니다.
#define PERFORMANCE_PROFILER_START()\
INT32 funcID = __COUNTER__;\
RXPERFORMANCE_PROFILER->Start(__FUNCSIG__, funcID)
#define PERFORMANCE_PROFILER_END() RXPERFORMANCE_PROFILER->End(funcID)

// ====================================================================================
// 수학 관련 매크로 모음입니다.
// ====================================================================================
#define SAME_FLOAT(v1, v2) (std::abs(v1 - v2) <= FLT_EPSILON)

#endif