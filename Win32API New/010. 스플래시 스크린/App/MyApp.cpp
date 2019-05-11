// ==================================================================================== =
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

// ������ Ŭ������ �ʱ�ȭ�մϴ�.
HRESULT RXMyApp::InitWndClass()
{
	// =====================================================================================
	// ������ Ÿ��Ʋ�� ������ �ش� �̸����� ������ Ŭ������ �����ϰ�,
	// ������ Ÿ��Ʋ�� ������ ���� ������ Ŭ���� �̸����� �����մϴ�.
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

// ���α׷��� ���� ��ƾ�Դϴ�.
INT32 RXMyApp::Run()
{
	// =====================================================================================
	// �����Ҵ� �޸� ���� ��� ���� �����Դϴ�.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �޸� ���� �߻��ϸ� �� ��° �Ҵ翡�� �߻��ߴ��� �����մϴ�.
	// _CrtSetBreakAlloc(100);

	// =====================================================================================
	// ������ Ŭ���� �� �����츦 �ʱ�ȭ�մϴ�.
	if (FAILED(InitWndClass()))
	{
		return 0;
	}

	// ���÷��� ������� �޴�, ��輱 ���� ����� �ϴϱ� WS_POPUP���� �����մϴ�.
	if (FAILED(m_pWnd->Create(m_wndCreateInfo, WS_POPUP)))
	{
		return 0;
	}

	// ======================================================================
	// �޽��� �����Դϴ�.
	MSG message;
	::ZeroMemory(&message, sizeof(message));

	bool bRun = true;
	while (bRun == true)
	{
		// WM_QUIT�� ������ ���÷��� ���������� ���� ���������� �Ǵ��մϴ�.
		if (message.message == WM_QUIT)
		{
			// ���÷��� �����찡 �ı��� ����̹Ƿ� ���� �����츦 �����մϴ�.
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
			// ���� �����찡 �ı��� ����̹Ƿ� �޽��� ������ Ż���մϴ�.
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