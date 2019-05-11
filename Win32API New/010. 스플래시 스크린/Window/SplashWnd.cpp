// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "SplashWnd.h"

namespace
{
	const INT32 RANDOM_SPLASH_COUNT = 6;
	const INT32 SPLASH_TIMER_ID = 1;
}

// WM_CREATE 핸들러입니다.
BOOL RXSplashWnd::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	if (pCreateStruct == nullptr)
	{
		return FALSE;
	}

	// ======================================================================
	// 스플래시 윈도우로 사용할 비트맵을 랜덤하게 고릅니다.
	// RANDOM_SPLASH_COUNT와 실제 비트맵 파일 개수는 일치해야 정상 작동됩니다.
	// 비트맵을 고르면 비트맵 메모리에 로딩해서 비트맵 핸들값을 얻습니다.
	std::srand(::timeGetTime());
	std::wstring szFilePath =
		RXGlobal::MakeFormatString(_T("resource\\splash_%d.bmp"), std::rand() % RANDOM_SPLASH_COUNT);
	m_hBitmap = static_cast<HBITMAP>(::LoadImage(RXGlobal::m_hMainInstance,
		szFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));

	if (m_hBitmap == nullptr)
	{
		ERRMSGBOX(_T("비트맵 로딩 실패!"));
		return FALSE;
	}

	// ======================================================================
	// 스플래시 윈도우를 설정합니다.
	// 윈도우 스타일은 WS_EXLAYERED로 설정해야 하는데
	// 설정한 다음에는 반드시 SetLayeredWindowAttributes() 또는 UpdateLayeredWindow()를
	// 바로 호출해야 정상 작동이 보장됩니다!
	//
	// 추가적으로 스플래시 스크린은 무조건 보여야 하므로 WS_EX_TOPMOST로 설정하고,
	// 작업 표시줄과 알트탭 목록에서 숨기야 하므로 WS_EX_TOOLWINDOW를 설정합니다.
	::SetWindowLongPtr(hWnd, GWL_EXSTYLE, ::GetWindowLongPtr(hWnd, GWL_EXSTYLE) |
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);

	// 컬러키를 제외하고 그리려면 LWA_COLORKEY 플래그를 설정합니다.
	::SetLayeredWindowAttributes(hWnd, RXGlobal::WINDOW_COLOR_WHITE, 0, LWA_COLORKEY);

	// ======================================================================
	// 윈도우 위치를 화면 가운데로 조정합니다.
	POINT centerPos = RXGlobal::CalcCenterPosByScreen(pCreateStruct->cx, pCreateStruct->cy);
	::SetWindowPos(hWnd, HWND_TOPMOST, centerPos.x, centerPos.y, 0, 0, SWP_NOSIZE);

	// ======================================================================
	// 스플래시 윈도우가 보여질 시간을 설정합니다.
	// 타이머를 이용하면 간단하게 처리할 수 있습니다.
	::SetTimer(hWnd, SPLASH_TIMER_ID, 3000, nullptr);
	// ======================================================================

	return TRUE;
}

// WM_PAINT 핸들러입니다.
void RXSplashWnd::OnPaint(HWND hWnd)
{
	// 반드시 DC를 BeginPaint()로 생성해야 합니다.
	// 그렇지 않으면 WM_PAINT는 삭제되지 않습니다.
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ======================================================================
	// 스플래시 윈도우에 사용할 비트맵을 그립니다.
	RXGlobal::DrawBimapExcludeColorKey(hDC, m_hBitmap,
		getClientWidth(), getClientHeight(), RXGlobal::WINDOW_COLOR_WHITE, true);
	// ======================================================================

	// BeginPaint()로 시작했으면 EndPaint()로 끝내야 합니다.
	EndPaint(hWnd, &ps);
}

// WM_DESTROY 핸들러입니다.
void RXSplashWnd::OnDestroy(HWND hWnd)
{
	::KillTimer(hWnd, SPLASH_TIMER_ID);
	DeleteBitmap(m_hBitmap);
	RXWnd::OnDestroy(hWnd);
}

// WM_TIMER 핸들러입니다.
void RXSplashWnd::OnTimer(HWND hWnd, UINT id)
{
	// 타이머가 이벤트를 받으면 메인 윈도우를 활성화시킵니다.
	if (id == SPLASH_TIMER_ID)
	{
		::SendMessage(hWnd, WM_CLOSE, 0, 0); // 안전하게 종료하는 방법입니다.
	}
}