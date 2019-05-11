// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "Wnd.h"

RXWnd::RXWnd()
{
	m_szWndTitle = _T("RXWnd");
	m_hWnd = nullptr;
	
	::SetRect(&m_clientArea, 0, 0, 0, 0);
}

RXWnd::RXWnd(const std::wstring& szWndTitle)
{
	m_szWndTitle = szWndTitle;
	m_hWnd = nullptr;

	::SetRect(&m_clientArea, 0, 0, 1024, 768);
}

// WM_CREATE 핸들러입니다.
BOOL RXWnd::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	m_hWnd = hWnd;
	return TRUE; // 메시지 크래커로 인해 반드시 TRUE를 반환해야 합니다.
}

// WM_DESTROY 핸들러입니다.
void RXWnd::OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
{
	MSGBOX(_T("(RXWnd) 마우스 왼쪽 버튼 클릭!"));
}

// WM_DESTROY 핸들러입니다.
void RXWnd::OnDestroy(HWND hWnd)
{
	// WM_DESTROY를 받으면 WM_QUIT을 보냅니다.
	::PostQuitMessage(EXIT_SUCCESS);
}

// 윈도우 생성 기본형입니다.
HRESULT RXWnd::Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwStyle)
{
	// ======================================================================
	// 윈도우를 생성하고 사용자에게 보여줍니다.
	m_hWnd = ::CreateWindow(m_szWndTitle.c_str(), m_szWndTitle.c_str(),
		dwStyle, x, y, clientWidth, clientHeight,
		HWND_DESKTOP, nullptr, RXGlobal::m_hMainInstance, this);

	if (m_hWnd == nullptr)
	{
		ERRMSGBOX(L"윈도우 생성 실패!");
		return E_FAIL;
	}

	// 클라이언트 영역 기준으로 윈도우 영역을 재조정합니다.
	RXGlobal::AdjustClientArea(m_hWnd, clientWidth, clientHeight);
	
	// 윈도우 핸들값을 얻었으므로 클라이언트 영역 갱신이 가능합니다.
	::GetClientRect(m_hWnd, &m_clientArea);

	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hWnd);
	// ======================================================================

	return S_OK;
}

// 윈도우 생성 정보를 인자로 받고,
// 윈도우 스타일을 WS_OVERLAPPEDWINDOW로 고정합니다.
HRESULT RXWnd::Create(const WndCreateInfo& wndCreateInfo)
{
	return Create(wndCreateInfo.posInfo.x, wndCreateInfo.posInfo.y,
		wndCreateInfo.resolutionInfo.width, wndCreateInfo.resolutionInfo.height, WS_OVERLAPPEDWINDOW);
}