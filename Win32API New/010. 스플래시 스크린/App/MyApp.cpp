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

	m_szMainWndClassName = RXGlobal::SZ_NULL;
}

RXMyApp::RXMyApp(const std::wstring& szTitle, INT32 clientWidth, INT32 clientHeight)
	: RXMyApp(szTitle, 0, 0, clientWidth, clientHeight)
{

}

RXMyApp::RXMyApp(const std::wstring& szTitle, INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight)
{
	m_pWndClass = RXNew RXWndClass;
	m_pWnd      = RXNew RXWnd(szTitle);

	m_wndCreateInfo.posInfo.x = x;
	m_wndCreateInfo.posInfo.y = y;

	m_wndCreateInfo.resolutionInfo.width  = clientWidth;
	m_wndCreateInfo.resolutionInfo.height = clientHeight;

	m_szMainWndClassName = szTitle;
}

RXMyApp::~RXMyApp()
{
	SAFE_DELETE(m_pWnd);
	SAFE_DELETE(m_pWndClass);
}

// 윈도우 클래스를 초기화합니다.
HRESULT RXMyApp::InitWndClass()
{
	// =====================================================================================
	// 윈도우 타이틀이 있으면 해당 이름으로 윈도우 클래스를 생성하고,
	// 윈도우 타이틀이 없으면 메인 윈도우 클래스 이름으로 생성합니다.
	std::wstring szWndTitle = m_pWnd->getWndTitle();
	if (szWndTitle.length() == 0)
	{
		m_pWnd->setTitleBarTitle(m_szMainWndClassName);
		if (FAILED(m_pWndClass->Init(m_szMainWndClassName)))
		{
			return E_FAIL;
		}
	}
	else
	{
		if (FAILED(m_pWndClass->Init(szWndTitle)))
		{
			return E_FAIL;
		}
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

	// 스플래시 윈도우는 메뉴, 경계선 등이 없어야 하니까 WS_POPUP으로 생성합니다.
	if (FAILED(m_pWnd->Create(m_wndCreateInfo, WS_POPUP)))
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
		// WM_QUIT를 받으면 스플래시 윈도우인지 메인 윈도우인지 판단합니다.
		if (message.message == WM_QUIT)
		{
			// 스플래시 윈도우가 파괴된 경우이므로 메인 윈도우를 생성합니다.
			if (RXGlobal::m_bRunMainWindow == false)
			{
				setMainWnd(RXNew RXWnd);
				m_pWnd->setTitleBarTitle(m_szMainWndClassName);

				RXGlobal::CalcCenterPosByScreen(&m_wndCreateInfo);
				if (FAILED(m_pWnd->Create(m_wndCreateInfo)))
				{
					return EXIT_FAILURE;
				}

				RXGlobal::m_bRunMainWindow = true;
			}
			// 메인 윈도우가 파괴된 경우이므로 메시지 루프를 탈출합니다.
			else
			{
				bRun = false;
			}
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