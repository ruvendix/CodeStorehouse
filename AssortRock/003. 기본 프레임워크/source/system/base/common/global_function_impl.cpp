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
 * ��ũ�� ������ ���ԵǹǷ� ��ũ�ο� ������ ���� �ʽ��ϴ�.
 * DLL�� ����Ǿ����Ƿ� DLL ����ο� �����η� �������ϴ�.
 *
 ====================================================================================*/
#include "global_function.h"
#include "global_constant.h"

// ���� �Լ������� ���Ǹ� ���� �����Դϴ�.
// ����� ������Ʈ�� ���� ������ ��ġ�� �� �˴ϴ�.
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

	// ����� ��忡���� Ȯ�� ������ �α��Դϴ�.
	// �α״� ����� ���â���� Ȯ���� �� �ֽ��ϴ�.
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

				// �ý��� �ð��� �̿��ؼ� ���� �ð��� ���մϴ�.
				// �α� ������ �߰��� ������ ��� ���α׷��� �������� ����
				// �ð����� �ٽ� �α� ������ �����մϴ�.
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

			// ���Ͽ� ������ ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
			// Win32 API�ε� ���� �ڵ�� ��Ʈ���� ���� �ݽ��ϴ�.
			// �� �� ���� ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
			FILE* pLog = nullptr;
			_wfopen_s(&pLog, g_szLogFile, L"at");

			if (pLog != nullptr)
			{
				fwprintf(pLog, szFull);
				fclose(pLog);
			}
			else
			{
				RXDebugLogImplA("�α� ����!");
			}
		}

		if (bError)
		{
			// ����� ����� �� �ߴ����� �˴ϴ�.
			// ����Ű� ���� ���� ���α׷��� �ڵ� ����˴ϴ�.
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
	// ��Ģ�����δ� �����, ����� ������� ���� �Ǵ� ������ �α׸� ���ܾ� �մϴ�.
	// ���� ���ڿ��� �����ϸ� "����(����) <�Լ�> : ����" �̷� �������� �αװ� ��µ˴ϴ�.
	// ����� ����� ����� ���� ����� ���â���� �α׸� ����ϴ�.
	// ��� ������ �α��� ���̴� ��Ƽ����Ʈ �������� ���� 512���Դϴ�.
	// �տ� �⺻ ���ڿ��� �߰��ǹǷ� �� ��� ������ �α��� ���̴� 512 + 512 = 1024�Դϴ�.
	// �޽��� �ڽ� ��� ��ɵ� �ִµ� �Ϲ� �޽��� �ڽ��� ���� �޽��� �ڽ��� �����մϴ�.
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

		// �����̳� ������ �α׸� ����� ��ƾ�� ���� �˴ϴ�.
		if (bFile == true)
		{
			if (g_bInitLogFile == true)
			{
				g_bInitLogFile = false;

				// �ý��� �ð��� �̿��ؼ� ���� �ð��� ���մϴ�.
				// �α� ������ �߰��� ������ ��� ���α׷��� �������� ����
				// �ð����� �ٽ� �α� ������ �����մϴ�.
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

			// ���Ͽ� ������ ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
			// Win32 API�ε� ���� �ڵ�� ��Ʈ���� ���� �ݽ��ϴ�.
			// �� �� ���� ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
			FILE* pLog = nullptr;
			fopen_s(&pLog, g_szLogFile, "at");

			if (pLog != nullptr)
			{
				fprintf(pLog, szFull);
				fclose(pLog);
			}
			else
			{
				RXDebugLogImplA("�α� ����!");
			}
		}

		if (bError)
		{
			// ����� ����� �� �ߴ����� �˴ϴ�.
			// ����Ű� ���� ���� ���α׷��� �ڵ� ����˴ϴ�.
			__debugbreak();
		}
	}

	// ::GetLastError()�� �̿��� Win32 API ���� �ڵ鷯�Դϴ�.
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

		// ����� ����� �� �ߴ����� �˴ϴ�.
		// ����Ű� ���� ���� ���α׷��� �ڵ� ����˴ϴ�.
		__debugbreak();
	}
#endif

	// �޽��� �ڽ��� �����ִ� �Լ��Դϴ�.
	void ShowMessageBoxImplA(const CHAR* szText)
	{
		::MessageBoxA(::GetActiveWindow(), szText, "Caption", MB_OK);
	}

	void ShowMessageBoxImplW(const WCHAR* szText)
	{
		::MessageBoxW(::GetActiveWindow(), szText, L"Caption", MB_OK);
	}

	// �޽��� �ڽ��� ������ �����ִ� �Լ��Դϴ�.
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

	// ShowCursor()�� TURE�� �� ���� �����ϰ� FALSE�� �� ���ҽ�ŵ�ϴ�.
	// ���� �� ���� ������ �����ؾ� ���콺 Ŀ�� ��� ���θ� ���� �� �ֽ��ϴ�.
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