// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "Global.h"

// static 멤버변수 및 멤버상수 초기화 방법입니다.
// 정의는 필수지만 초기화값은 설정해주지 않아도 됩니다.
HINSTANCE    RXGlobal::m_hMainInstance           = nullptr;
bool         RXGlobal::m_bRunMainWnd          = false;
const TCHAR* RXGlobal::SZ_WND_PROCEDURE_PROPERTY = _T("WndProcedure");
const TCHAR* RXGlobal::SZ_NULL                   = _T("");

// 길이와 높이를 전달하면 클라이언트 영역 기준으로 윈도우 영역을 재조정합니다.
// 예를 들어 길이에 1024를 전달하고 높이에 768을 전달하면
// 클라이언트 영역은 (1024 * 768)이 됩니다.
void RXGlobal::AdjustClientArea(HWND hWnd, INT32 width, INT32 height)
{
	// ======================================================================
	// 현재 적용된 윈도우 스타일을 조사합니다.
	DWORD dwStyle   = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	DWORD dwStyleEx = ::GetWindowLongPtr(hWnd, GWL_EXSTYLE);
	BOOL  bMenu     = (::GetMenu(hWnd) != nullptr);

	// ======================================================================
	// 스크롤바 길이를 조사합니다.
	RECT clientArea = { 0, 0, width, height };

	if (dwStyle & WS_HSCROLL)
	{
		clientArea.right += ::GetSystemMetrics(SM_CXHSCROLL);
	}

	if (dwStyle & WS_HSCROLL)
	{
		clientArea.bottom += ::GetSystemMetrics(SM_CXVSCROLL);
	}

	// ======================================================================
	// 클라이언트 영역 기준으로 윈도우 영역을 재조정합니다.
	::AdjustWindowRectEx(&clientArea, dwStyle, bMenu, dwStyleEx);

	// 이미 윈도우가 생성된 이후이므로 재조정된 크기를 적용합니다.
	::SetWindowPos(hWnd, nullptr, 0, 0, clientArea.right - clientArea.left,
		clientArea.bottom - clientArea.top, SWP_NOMOVE | SWP_NOZORDER);
}

// 컬러키 부분을 제외시키고 비트맵을 그립니다.
void RXGlobal::DrawBimapExcludeColorKey(HDC hDC, HBITMAP hBitmap,
	INT32 x, INT32 y, COLORREF colorKey, bool bCenter)
{
	// ======================================================================
	// 메모리 DC를 생성해서 그릴 비트맵과 연결시켜줍니다.
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hOldBitmap = SelectBitmap(hMemDC, hBitmap);

	// ======================================================================
	// 비트맵 정보를 이용해서 비트맵을 그릴 위치를 설정합니다.
	BITMAP bitmapInfo;
	::GetObject(hBitmap, sizeof(bitmapInfo), &bitmapInfo);

	// bCenter에 따라 비트맵을 그릴 위치를 조정합니다.
	POINT drawPos;
	if (bCenter == true)
	{
		drawPos.x = (x / 2) - (bitmapInfo.bmWidth / 2);
		drawPos.y = (y / 2) - (bitmapInfo.bmHeight / 2);
	}
	else
	{
		drawPos.x = x;
		drawPos.y = y;
	}

	// ======================================================================
	// GdiTransparentBlt()은 TransparentBlt()과 동일하지만 별도의 라이브러리 연결이 필요 없습니다.
	::GdiTransparentBlt(hDC, drawPos.x, drawPos.y, bitmapInfo.bmWidth, bitmapInfo.bmHeight,
		hMemDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, colorKey);

	// ======================================================================
	// 메모리 DC에 이전 비트맵을 적용하고, 메모리 DC를 제거합니다.
	// 딱히 의미는 없지만 이전 정보를 복구해야 한다는 원칙을 따릅니다.
	SelectBitmap(hMemDC, hOldBitmap);
	::DeleteDC(hMemDC);
}

// 모니터 가운데로 프로그램을 배치할 위치를 구합니다.
POINT RXGlobal::CalcCenterPosByScreen(INT32 width, INT32 height)
{
	POINT centerPos;
	centerPos.x = (::GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
	centerPos.y = (::GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);
	return centerPos;
}

// WndCreateInfo의 ResolutionInfo 정보로 중앙 위치를 구합니다.
// 구한 위치는 POINT로도 반환하지만 WndCreateInfo의 PositionInfo에도 적용합니다.
// 표준 라이브러리에도 이런 유형의 함수들이 있습니다.
POINT RXGlobal::CalcCenterPosByScreen(WndCreateInfo* pWndCreateInfo)
{
	if (pWndCreateInfo == nullptr)
	{
		return POINT();
	}

	POINT centerPos = CalcCenterPosByScreen(pWndCreateInfo->resolutionInfo.width,
		pWndCreateInfo->resolutionInfo.height);
	pWndCreateInfo->posInfo.x = centerPos.x;
	pWndCreateInfo->posInfo.y = centerPos.y;
	return centerPos;
}

// Create은 생성 정보를 이용해서 처음부터 만들 때 사용하고
// Make는 전달된 정보들을 조합해서 만들 때 사용합니다. (사실 별로 차이는 없음...)
// printf()처럼 사용하면 std::wstring 자료형으로 문자열을 만듭니다.
std::wstring RXGlobal::MakeFormatString(const WCHAR* szFormat, ...)
{
	// ======================================================================
	// 가변 인자 매크로를 이용해서 각 인자들을 구분합니다.
	va_list va = nullptr;
	va_start(va, szFormat); // 가변 인자의 시작을 알립니다.

	// 서식 문자열의 길이를 구합니다.
	// 동적할당을 위해 종료 문자를 포함해야 합니다.
	INT32 strLength = _vscwprintf(szFormat, va) + 1;

	// 가변 인자로 문자열을 조합하려면 메모리 버퍼가 필요합니다.
	// std::string은 메모리 버퍼가 가변적이라 사용할 수 없습니다.
	// 참고로 단순하게 바이트 단위로 동적할당할 때는 std::malloc()을 사용합니다.
	WCHAR* szBuffer = nullptr;
	szBuffer = reinterpret_cast<WCHAR*>(std::malloc(strLength * sizeof(WCHAR)));
	::ZeroMemory(szBuffer, (strLength * sizeof(WCHAR)));

	// 동적할당된 메모리 버퍼에 서식 문자열과 가변 인자들을 조합해서 하나의 문자열로 만듭니다.
	vswprintf_s(szBuffer, strLength, szFormat, va);
	va_end(va); // 가변 인자의 종료를 알립니다.

	// ======================================================================
	// 동적할당된 메모리 버퍼를 해제하고 완성된 문자열을 std::wstring에 복사합니다.
	std::wstring szResult = szBuffer;
	free(szBuffer);

	return szResult;
}