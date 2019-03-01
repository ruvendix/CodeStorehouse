/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-08-11 (AssortRock 전용으로 수정)
 *
 * <파일 내용>
 * 공동으로 사용되는 전역 함수 모음입니다.
 * 함수 선언부만 있으며, 구현부는 각 프로젝트에 포함시켜야 합니다.
 * 절대로 프로젝트와 전역 변수가 겹치면 안 됩니다. 겹치면 정상 작동이 보장되지 않습니다.
 * 매크로에 영향을 받지 않습니다.
 * 미리 컴파일된 헤더파일에 포함됩니다.
 *
 ====================================================================================*/
#ifndef GLOBAL_FUNCTION_H__
#define GLOBAL_FUNCTION_H__

#include "common_base.h"
#include "global_type.h"

namespace RX
{
	// ======================================================================================
	// 프로젝트의 문자집합 설정에 따라 하나만 작동됩니다.
	// ======================================================================================
#if defined(_UNICODE) || defined(UNICODE)
	void RXLogImplW(PROJECT_MODE eMode, bool bMessageBox, bool bFile, bool bError,
		const WCHAR* szFile, INT32 line, const WCHAR* szFunSig, const WCHAR* szFormat, ...);
	void Win32LastErrorHandlerImplW(PROJECT_MODE eMode, const WCHAR* szFileName,
		INT32 line, const WCHAR* szFunSig);
#else
	void RXLogImplA(PROJECT_MODE eMode, bool bMessageBox, bool bFile, bool bError,
		const CHAR* szFile, INT32 line, const CHAR* szFunSig, const CHAR* szFormat, ...);
	void Win32LastErrorHandlerImplA(PROJECT_MODE eMode, const CHAR* szFileName,
		INT32 line, const CHAR* szFunSig);
#endif

	// ======================================================================================
	// 유니코드 버전입니다.
	// ======================================================================================
	void RXDebugLogImplW(const WCHAR* szText);
	void ShowMessageBoxImplW(const WCHAR* szText);
	void ShowErrorMessageBoxImplW(const WCHAR* szErr, const WCHAR* szFileName, INT32 line);
	
	template <typename _Ty>
	const WCHAR* ConvertValueToStringImplW(WCHAR* szBuffer, _Ty value)
	{
		wcscpy_s(szBuffer, std::to_wstring(value).c_str());
		return szBuffer;
	}

	// ======================================================================================
	// 멀티바이트 버전입니다.
	// ======================================================================================
	void RXDebugLogImplA(const CHAR* szText);
	void ShowMessageBoxImplA(const CHAR* szText);
	void ShowErrorMessageBoxImplA(const CHAR* szErr, const CHAR* szFileName, INT32 line);

	template <typename _Ty>
	const WCHAR* ConvertValueToStringImplA(CHAR* szBuffer, _Ty value)
	{
		strcpy_s(szBuffer, std::to_string(value).c_str());
		return szBuffer;
	}

	// ======================================================================================
	// 문자에 영향을 받지 않는 함수입니다.
	// ======================================================================================
	void ShowMouseCursor(bool bShow);

	template <typename _Ty>
	void DeleteAllHeapElement(_Ty* pContainer)
	{
		// 벡터, 리스트 컨테이너 요소의 동적할당을 해제하는 함수입니다.
		typename _Ty::iterator iter = pContainer->begin();
		typename _Ty::iterator iterEnd = pContainer->end();
		while (iter != iterEnd)
		{
			if ((*iter) != nullptr)
			{
				delete (*iter);
				(*iter) = nullptr;
			}
			++iter;
		}
		pContainer->clear();
	}

} // namespace RX end

#endif