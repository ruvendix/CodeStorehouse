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
 * 매크로 이전에 포함되므로 매크로에 영향을 받지 않습니다.
 * DLL로 변경되었으므로 DLL 선언부와 구현부로 나눠집니다.
 *
 ====================================================================================*/
#include "global_function.h"
#include "global_constant.h"

// 전역 함수에서만 사용되면 전역 변수입니다.
// 절대로 프로젝트의 전역 영역과 겹치면 안 됩니다.
namespace
{
#if defined(_UNICODE) || defined(UNICODE)
	WCHAR g_szLogFile[DEFAULT_STRING_LENGTH] = L"";
#else
	CHAR  g_szLogFile[DEFAULT_STRING_LENGTH] = "";
#endif

	bool g_bInitLogFile = true;
}

namespace RX
{

	// 디버그 모드에서만 확인 가능한 로그입니다.
	// 로그는 디버그 출력창에서 확인할 수 있습니다.
	void RXDebugLogImplA(const CHAR* szText)
	{
		::OutputDebugStringA(szText);
	}

	void RXDebugLogImplW(const WCHAR* szText)
	{
		::OutputDebugStringW(szText);
	}

#if defined(_UNICODE) || defined(UNICODE)
	void RXLogImplW(PROJECT_MODE mode, bool bMessageBox, bool bFile, bool bError,
		const WCHAR* szFile, INT32 line, const WCHAR* szFunSig, const WCHAR* szFormat, ...)
	{
		WCHAR szFull[MAX_STRING_LENGTH];
		::ZeroMemory(szFull, _countof(szFull));

		if (szFile != nullptr)
		{
			_snwprintf_s(szFull, _countof(szFull), L"%s (%d) <%s> ", szFile, line, szFunSig);
		}
		else
		{
			_snwprintf_s(szFull, _countof(szFull), L"(%d) <%s> ", line, szFunSig);
		}

		WCHAR szText[DEFAULT_STRING_LENGTH];
		va_list vaList;
		va_start(vaList, szFormat);
		_vsnwprintf_s(szText, _countof(szText), szFormat, vaList);
		va_end(vaList);

		wcscat_s(szFull, szText);
		wcscat_s(szFull, L"\n");

		if (mode == PROJECT_MODE::DEBUG)
		{
			RXDebugLogImplW(szFull);
		}

		if (bMessageBox)
		{
			if (bError)
			{
				ShowErrorMessageBoxImplW(szText, szFile, line);
			}
			else
			{
				ShowMessageBoxImplW(szText);
			}
		}

		if (bFile == true)
		{
			if (g_bInitLogFile == true)
			{
				g_bInitLogFile = false;

				// 시스템 시간을 이용해서 현재 시간을 구합니다.
				// 로그 파일을 중간에 삭제할 경우 프로그램을 실행했을 때의
				// 시간으로 다시 로그 파일을 생성합니다.
				SYSTEMTIME sysTime;
				::ZeroMemory(&sysTime, sizeof(sysTime));
				WCHAR szCurTime[DEFAULT_STRING_LENGTH];
				::GetLocalTime(&sysTime);
				_snwprintf_s(szCurTime, _countof(szCurTime),
					L"%02d-%02d-%02d-%02d-%02d-%02d",
					sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour,
					sysTime.wMinute, sysTime.wSecond);

				::CreateDirectory(L"Log", nullptr);

#if defined(DEBUG) | defined(_DEBUG)
				_snwprintf_s(g_szLogFile, _countof(g_szLogFile), L"Log\\RXDebug(%s).log", szCurTime);
#else
				_snwprintf_s(g_szLogFile, _countof(g_szLogFile), L"Log\\RX(%s).log", szCurTime);
#endif
			}

			// 파일에 뭔가를 쓰려면 파일 스트림을 열고 닫아야 합니다.
			// Win32 API로도 파일 핸들로 스트림을 열고 닫습니다.
			// 단 한 줄을 쓰더라도 파일 스트림을 열고 닫아야 합니다.
			FILE* pLog = nullptr;
			_wfopen_s(&pLog, g_szLogFile, L"at");

			if (pLog != nullptr)
			{
				fwprintf(pLog, szFull);
				fclose(pLog);
			}
			else
			{
				RXDebugLogImplA("로그 누락!");
			}
		}

		if (bError)
		{
			// 디버그 모드일 때 중단점이 됩니다.
			// 디버거가 없을 때는 프로그램이 자동 종료됩니다.
			__debugbreak();
		}
	}

	void Win32LastErrorHandlerImplW(PROJECT_MODE eMode, const WCHAR* szFileName,
		INT32 line, const WCHAR* szFunSig)
	{
		DWORD errorCode = ::GetLastError();
		if (errorCode == 0)
		{
			return;
		}

		WCHAR* szText = nullptr;
		::FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), szText, 0, nullptr);

		WCHAR szErr[DEFAULT_STRING_LENGTH];
		_snwprintf_s(szErr, _countof(szErr), L"Error : %0x\nText : %s", errorCode, szText);
		ShowErrorMessageBoxImplW(szErr, szFileName, line);

		RXLogImplW(eMode, false, true, true, szFileName, line, szFunSig,
			L"Error(%0x) Text(%s)", errorCode, szText);

		LocalFree(szText);
	}
#else
	// 원칙적으로는 디버그, 릴리즈에 관계없이 파일 또는 서버에 로그를 남겨야 합니다.
	// 서식 문자열을 지원하며 "파일(라인) <함수> : 내용" 이런 형식으로 로그가 출력됩니다.
	// 참고로 디버그 모드일 때는 디버그 출력창에도 로그를 남깁니다.
	// 출력 가능한 로그의 길이는 멀티바이트 기준으로 문자 512개입니다.
	// 앞에 기본 문자열이 추가되므로 총 출력 가능한 로그의 길이는 512 + 512 = 1024입니다.
	// 메시지 박스 출력 기능도 있는데 일반 메시지 박스와 에러 메시지 박스를 지원합니다.
	void RXLogImplA(PROJECT_MODE eMode, bool bMessageBox, bool bFile, bool bError,
		const CHAR* szFile, INT32 line, const CHAR* szFunSig, const CHAR* szFormat, ...)
	{
		CHAR szFull[MAX_STRING_LENGTH];
		if (szFile != nullptr)
		{
			_snprintf_s(szFull, _countof(szFull), "%s (%d) <%s> ", szFile, line, szFunSig);
		}
		else
		{
			_snprintf_s(szFull, _countof(szFull), "(%d) <%s> ", line, szFunSig);
		}

		CHAR szText[DEFAULT_STRING_LENGTH];
		va_list vaList;
		va_start(vaList, szFormat);
		_vsnprintf_s(szText, _countof(szText), szFormat, vaList);
		va_end(vaList);

		strcat_s(szFull, szText);
		strcat_s(szFull, "\n");

		if (eMode == PROJECT_MODE::DEBUG)
		{
			RXDebugLogImplA(szFull);
		}

		if (bMessageBox)
		{
			if (bError)
			{
				ShowErrorMessageBoxImplA(szText, szFile, line);
			}
			else
			{
				ShowMessageBoxImplA(szText);
			}
		}

		// 파일이나 서버에 로그를 남기는 루틴이 오면 됩니다.
		if (bFile == true)
		{
			if (g_bInitLogFile == true)
			{
				g_bInitLogFile = false;

				// 시스템 시간을 이용해서 현재 시간을 구합니다.
				// 로그 파일을 중간에 삭제할 경우 프로그램을 실행했을 때의
				// 시간으로 다시 로그 파일을 생성합니다.
				SYSTEMTIME sysTime;
				::ZeroMemory(&sysTime, sizeof(sysTime));
				CHAR szCurTime[DEFAULT_STRING_LENGTH];
				::GetLocalTime(&sysTime);
				_snprintf_s(szCurTime, _countof(szCurTime),
					"%02d-%02d-%02d-%02d-%02d-%02d",
					sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour,
					sysTime.wMinute, sysTime.wSecond);

				::CreateDirectory("Log", nullptr);

#if defined(DEBUG) | defined(_DEBUG)
				_snprintf_s(g_szLogFile, _countof(g_szLogFile), "Log\\RXDebug(%s).log", szCurTime);
#else
				_snprintf_s(g_szLogFile, _countof(g_szLogFile), "Log\\RX(%s).log", szCurTime);
#endif
			}

			// 파일에 뭔가를 쓰려면 파일 스트림을 열고 닫아야 합니다.
			// Win32 API로도 파일 핸들로 스트림을 열고 닫습니다.
			// 단 한 줄을 쓰더라도 파일 스트림을 열고 닫아야 합니다.
			FILE* pLog = nullptr;
			fopen_s(&pLog, g_szLogFile, "at");

			if (pLog != nullptr)
			{
				fprintf(pLog, szFull);
				fclose(pLog);
			}
			else
			{
				RXDebugLogImplA("로그 누락!");
			}
		}

		if (bError)
		{
			// 디버그 모드일 때 중단점이 됩니다.
			// 디버거가 없을 때는 프로그램이 자동 종료됩니다.
			__debugbreak();
		}
	}

	// ::GetLastError()를 이용한 Win32 API 에러 핸들러입니다.
	void Win32LastErrorHandlerImplA(PROJECT_MODE eMode, const CHAR* szFileName,
		INT32 line, const CHAR* szFunSig)
	{
		DWORD errorCode = ::GetLastError();
		if (errorCode == 0)
		{
			return;
		}

		CHAR* szText = nullptr;
		::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), szText, 0, nullptr);

		CHAR szErr[DEFAULT_STRING_LENGTH];
		_snprintf_s(szErr, _countof(szErr), "Error : %0x\nText : %s", errorCode, szText);
		ShowErrorMessageBoxImplA(szErr, szFileName, line);

		RXLogImplA(eMode, false, true, true, szFileName, line, szFunSig,
			"Error(%0x) Text(%s)", errorCode, szText);

		LocalFree(szText);

		// 디버그 모드일 때 중단점이 됩니다.
		// 디버거가 없을 때는 프로그램이 자동 종료됩니다.
		__debugbreak();
	}
#endif

	// 메시지 박스를 보여주는 함수입니다.
	void ShowMessageBoxImplA(const CHAR* szText)
	{
		::MessageBoxA(::GetActiveWindow(), szText, "Caption", MB_OK);
	}

	void ShowMessageBoxImplW(const WCHAR* szText)
	{
		::MessageBoxW(::GetActiveWindow(), szText, L"Caption", MB_OK);
	}

	// 메시지 박스로 오류를 보여주는 함수입니다.
	void ShowErrorMessageBoxImplA(const CHAR* szErr, const CHAR* szFileName, INT32 line)
	{
		CHAR szText[DEFAULT_STRING_LENGTH];
		_snprintf_s(szText, _countof(szText), "%s\n%s(%d)", szErr, szFileName, line);
		::MessageBoxA(::GetActiveWindow(), szText, "Error", MB_ICONERROR);
	}

	void ShowErrorMessageBoxImplW(const WCHAR* szErr, const WCHAR* szFileName, INT32 line)
	{
		WCHAR szText[DEFAULT_STRING_LENGTH];
		_snwprintf_s(szText, _countof(szText), L"%s\n%s(%d)", szErr, szFileName, line);
		::MessageBoxW(::GetActiveWindow(), szText, L"Error", MB_ICONERROR);
	}

	// ShowCursor()는 TURE일 때 값을 누적하고 FALSE일 때 감소시킵니다.
	// 따라서 각 값을 적절히 조절해야 마우스 커서 출력 여부를 정할 수 있습니다.
	void ShowMouseCursor(bool bShow)
	{
		if (bShow == true)
		{
			while (::ShowCursor(TRUE) < 0);
		}
		else
		{
			while (::ShowCursor(FALSE) >= 0);
		}
	}

} // namespace RX end