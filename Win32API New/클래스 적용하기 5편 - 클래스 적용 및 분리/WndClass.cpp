// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "WndClass.h"

// RXWnd를 사용합니다.
#include "Wnd.h"

HRESULT RXWndClass::Init(const std::wstring& szWndClass)
{
	// ======================================================================
	// 윈도우 클래스를 정의하고 등록합니다.
	::ZeroMemory(&m_wcex, sizeof(m_wcex)); // 멤버변수이므로 깔끔하게 초기화합니다.
	m_wcex.cbSize        = sizeof(m_wcex);
	m_wcex.lpfnWndProc   = RXWndClass::WndProcedure; // 함수 이름은 주소입니다.
	m_wcex.hInstance     = RXGlobal::m_hMainInstance;
	m_wcex.hbrBackground = reinterpret_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
	m_wcex.lpszClassName = szWndClass.c_str(); // exe 이름과는 무관합니다.

	// 지역변수는 소멸되므로 멤버변수에 저장합니다.
	setWindowClassName(szWndClass);

	::RegisterClassEx(&m_wcex);
	// ======================================================================

	return S_OK;
}

// 메시지큐에서 메시지를 가져온 후, 운영체제가 호출하는 콜백입니다.
LRESULT RXWndClass::WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ======================================================================
	// 저장한 사용자 정의 정보를 가져옵니다.
	// 각 객체마다 저장한 정보는 다르고 윈도우 핸들값은 중복되지 않습니다.
	// 즉, 윈도우 프로시저 하나만으로 다형성을 이용할 수 있습니다.
	RXWnd* pWnd = reinterpret_cast<RXWnd*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
	
	// ======================================================================
	// WM_CREATE 정보에는 전달한 사용자 정의 정보가 있습니다.
	// 해당 정보를 가져온 후, 메모리에 저장해둡니다.
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		pWnd = reinterpret_cast<RXWnd*>(pCreateStruct->lpCreateParams);
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
	}
	else
	{
		// WM_CREATE 이전에는 nullptr 고정입니다.
		// 이때는 메시지를 운영체제에게 보냅니다.
		if (pWnd == nullptr)
		{
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	// ======================================================================
	// 메시지 크래커 스위치입니다.
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE,  pWnd->OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, pWnd->OnDestroy);
	}

	// ======================================================================
	// 대부분의 메시지는 운영체제에게 보냅니다.
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}