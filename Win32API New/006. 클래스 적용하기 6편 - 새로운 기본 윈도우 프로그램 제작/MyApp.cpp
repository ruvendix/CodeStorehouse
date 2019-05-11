// ==================================================================================== =
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "MyApp.h"

RXMyApp::RXMyApp()
{
	m_pWndClass = RXNew RXWndClass;
	m_pWnd      = RXNew RXWnd;

	::ZeroMemory(&m_wndCreateInfo, sizeof(m_wndCreateInfo));
}

RXMyApp::RXMyApp(const std::wstring& szTitle, INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight)
{
	m_pWndClass = RXNew RXWndClass;
	m_pWnd      = RXNew RXWnd(szTitle);

	m_wndCreateInfo.posInfo.x = x;
	m_wndCreateInfo.posInfo.y = y;

	m_wndCreateInfo.resolutionInfo.width  = clientWidth;
	m_wndCreateInfo.resolutionInfo.height = clientHeight;
}

RXMyApp::~RXMyApp()
{
	SAFE_DELETE(m_pWnd);
	SAFE_DELETE(m_pWndClass);
}

// 윈도우 클래스를 초기화합니다.
HRESULT RXMyApp::InitWndClass()
{
	if (FAILED(m_pWndClass->Init(m_pWnd->getWndTitle())))
	{
		return E_FAIL;
	}

	return S_OK;
}

// 프로그램의 메인 루틴입니다.
INT32 RXMyApp::Run()
{
	// =====================================================================================
	// 동적할당 메모리 릭을 잡기 위한 설정입니다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 메모리 릭이 발생하면 몇 번째 할당에서 발생했는지 조사합니다.
	// _CrtSetBreakAlloc(100);

	// =====================================================================================
	// 윈도우 클래스 및 윈도우를 초기화합니다.
	if (FAILED(InitWndClass()))
	{
		return 0;
	}

	if (FAILED(m_pWnd->Create(m_wndCreateInfo)))
	{
		return 0;
	}

	// ======================================================================
	// 메시지 루프입니다.
	MSG message;
	::ZeroMemory(&message, sizeof(message));

	bool bRun = true;
	while (bRun == true)
	{
		if (message.message == WM_QUIT)
		{
			bRun = false;
		}

		if (::PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) != FALSE)
		{
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
	}
	// ======================================================================

	return (message.wParam);
}