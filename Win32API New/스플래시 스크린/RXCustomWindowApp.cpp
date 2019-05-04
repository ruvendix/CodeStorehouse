#include "../resource.h"

#include "RXCustomWindowApp.h"
#include "RXWindowTestWindow.h"

namespace RX
{

	static HBRUSH g_hBrushTable[3];

	// ���߿� ��Ʈ�� ���̺�� �����ؾ��ҵ�, ������ �׳� �ϵ��ڵ�
	HRESULT RXCustomWindowApp::InitWindowClass()
	{
		// =========================================================
		// ���� ������ Ŭ���� ���
		// ���� ������ Ŭ������ �̸��� ���� �����쿡�� ������ݴϴ�.
		RXStringVector& stringVector = RXGlobal::g_windowClassStringVector;
		stringVector.AddString(_T("Sample"));

		if (FAILED(m_pWindowClass->Init(stringVector.FindString(_T("Sample")))))
		{
			return E_FAIL;
		}

		m_pWindow->setTitleBarTitle(_T("Sample"));
		// ============================================================

		// ============================================================
		// �ڽ� ������ Ŭ���� ���
		stringVector.AddString(_T("Child"));
		m_pWindowClass->setWindowClassName(stringVector.FindString(_T("Child")));
		m_pWindowClass->setBackgroundBrush(GetStockBrush(GRAY_BRUSH));
		m_pWindowClass->setMouseCursor(::LoadCursor(RXGlobal::g_hMainInstance,
			MAKEINTRESOURCE(IDC_STARCRAFT2_CURSOR)));
		m_pWindowClass->RegisterWindowClass();
		// ============================================================

		// ���� ���ϵ� Ŭ����
		stringVector.AddString(_T("ChildLeft"));
		m_pWindowClass->setWindowClassName(stringVector.FindString(_T("ChildLeft")));
		m_pWindowClass->setBackgroundBrush(g_hBrushTable[0]);
		m_pWindowClass->RegisterWindowClass();

		// ���� ���ϵ� Ŭ����
		stringVector.AddString(_T("ChildTop"));
		m_pWindowClass->setWindowClassName(stringVector.FindString(_T("ChildTop")));
		m_pWindowClass->setBackgroundBrush(g_hBrushTable[1]);
		m_pWindowClass->RegisterWindowClass();

		// �Ʒ��� ���ϵ� Ŭ����
		stringVector.AddString(_T("ChildBottom"));
		m_pWindowClass->setWindowClassName(stringVector.FindString(_T("ChildBottom")));
		m_pWindowClass->setBackgroundBrush(g_hBrushTable[2]);
		m_pWindowClass->RegisterWindowClass();

		return S_OK;
	}

	INT32 RXCustomWindowApp::Run()
	{
		g_hBrushTable[0] = ::CreateSolidBrush(RGB(255, 0, 0));
		g_hBrushTable[1] = ::CreateSolidBrush(RGB(0, 255, 0));
		g_hBrushTable[2] = ::CreateSolidBrush(RGB(0, 0, 255));

		if (FAILED(InitWindowClass()))
		{
			return EXIT_FAILURE;
		}

		if (FAILED(m_pWindow->CreateRXWindow(
			m_windowInfo[APP_WINDOW_INFO::POSITION].first,
			m_windowInfo[APP_WINDOW_INFO::POSITION].second,
			m_windowInfo[APP_WINDOW_INFO::AREA].first,
			m_windowInfo[APP_WINDOW_INFO::AREA].second, WS_POPUP | WS_VISIBLE)))
		{
			return EXIT_FAILURE;
		}

		MSG message = { nullptr };

		bool bRun = true;
		while (bRun == true)
		{
			if (message.message == WM_QUIT)
			{
				if (RXGlobal::g_bRunMainWindow == true)
				{
					setMainRXWindow(RXNew RX::RXWindowTestWindow);

					RXStringVector& stringVector = RXGlobal::g_windowClassStringVector;
					m_pWindow->setTitleBarTitle(stringVector.FindString(_T("Sample")));

					if (FAILED(m_pWindow->CreateRXWindow(
						m_windowInfo[APP_WINDOW_INFO::POSITION].first,
						m_windowInfo[APP_WINDOW_INFO::POSITION].second,
						m_windowInfo[APP_WINDOW_INFO::AREA].first,
						m_windowInfo[APP_WINDOW_INFO::AREA].second)))
					{
						return EXIT_FAILURE;
					}
				}
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

		SAFE_DLETE_BRUSH(g_hBrushTable[0]);
		SAFE_DLETE_BRUSH(g_hBrushTable[1]);
		SAFE_DLETE_BRUSH(g_hBrushTable[2]);

		return (message.wParam);
	}

} // namespace RX end