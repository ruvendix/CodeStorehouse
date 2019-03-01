/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-11 (AssortRock �������� ����)
 *
 * <���� ����>
 * �������� ���Ǵ� ���� �Լ� �����Դϴ�.
 * �Լ� ����θ� ������, �����δ� �� ������Ʈ�� ���Խ��Ѿ� �մϴ�.
 * ����� ������Ʈ�� ���� ������ ��ġ�� �� �˴ϴ�. ��ġ�� ���� �۵��� ������� �ʽ��ϴ�.
 * ��ũ�ο� ������ ���� �ʽ��ϴ�.
 * �̸� �����ϵ� ������Ͽ� ���Ե˴ϴ�.
 *
 ====================================================================================*/
#ifndef GLOBAL_FUNCTION_H__
#define GLOBAL_FUNCTION_H__

#include "common_base.h"
#include "global_type.h"

namespace RX
{
	// ======================================================================================
	// ������Ʈ�� �������� ������ ���� �ϳ��� �۵��˴ϴ�.
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
	// �����ڵ� �����Դϴ�.
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
	// ��Ƽ����Ʈ �����Դϴ�.
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
	// ���ڿ� ������ ���� �ʴ� �Լ��Դϴ�.
	// ======================================================================================
	void ShowMouseCursor(bool bShow);

	template <typename _Ty>
	void DeleteAllHeapElement(_Ty* pContainer)
	{
		// ����, ����Ʈ �����̳� ����� �����Ҵ��� �����ϴ� �Լ��Դϴ�.
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