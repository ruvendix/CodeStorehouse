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
const TCHAR* RXGlobal::SZ_WND_PROCEDURE_PROPERTY = _T("WndProcedure");

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