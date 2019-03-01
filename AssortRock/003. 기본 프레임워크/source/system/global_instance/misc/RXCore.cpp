/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2019-02-02
 *
 * <���� ����>
 * ���� ���α׷��� �ٽ� ��ƾ�Դϴ�.
 *
 ====================================================================================*/
#include "RXCore.h"
#include "global_instance\manager\RXProgramFPSMgr.h"
#include "global_instance\manager\RXSceneMgr.h"

namespace
{
	const LPCTSTR g_szCore = _T("Framework");
}

namespace RX
{
	PHOENIX_SINGLETON_INIT(RXCore);

	LRESULT RXCore::WindowProcedure(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CREATE:
		{
			RXLOG("���α׷� ������ ����!");
			break;
		}
		case WM_CLOSE:
		{
			RXLOG("���α׷� �ݱ� ��ư Ŭ��!");
			::DestroyWindow(hMainWnd);
			break;
		}
		case WM_DESTROY:
		{
			RXLOG("���α׷� ����!");
			::PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
			{
				RXLOG("ESC �Է�!");
				::DestroyWindow(hMainWnd);
				break;
			}
			}

			break;
		}
		case WM_SYSCOMMAND:
		{
			// ���� 4��Ʈ�� ���������� ����ϴ� ���̹Ƿ� ������ ��!
			if (SC_KEYMENU == (wParam & 0xFFF0))
			{
				RXLOG("ALT + Enter");
			}
		}
		}

		return ::DefWindowProc(hMainWnd, msg, wParam, lParam);
	}

	RXCore::RXCore()
	{
		m_hInst    = nullptr;
		m_hMainWnd = nullptr;
		m_hDC      = nullptr;
		m_msgCode  = 0;

		m_resolutionInfo.width  = 1024;
		m_resolutionInfo.height = 768;
	}

	HRESULT RXCore::OnInit()
	{
		// ������ �����Դϴ�.
		// �ý��� �������� �����ϴ�.
		_wsetlocale(LC_ALL, L""); // nullptr�� �ƴ϶� L""�� ����!

		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		RXFPSMGR->UpdateFrame();

		m_hInst = ::GetModuleHandle(nullptr);
		NULLCHK_RETURN_EFAIL_NOCOMENT(m_hInst);

		if (FAILED(CreateWindowClass()))
		{
			RXERRLOG("������ Ŭ���� ���� ����!");
			return E_FAIL;
		}

		if (FAILED(CreateProgramWindow()))
		{
			RXERRLOG("���α׷� ������ ���� ����!");
			return E_FAIL;
		}

		RXSCENEMGR->CreateScene<RXScene>();
		if (FAILED(RXSCENEMGR->getCurrentScene()->OnInit()))
		{
			RXERRLOG("���� �� �ʱ�ȭ ����!");
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXCore::OnUpdate()
	{
		RXFPSMGR->UpdateFrame();

		if (FAILED(RXSCENEMGR->getCurrentScene()->OnUpdate()))
		{
			RXERRLOG("���� �� ������Ʈ ����!");
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXCore::OnRender()
	{
		if (FAILED(RXSCENEMGR->getCurrentScene()->OnRender()))
		{
			RXERRLOG("���� �� ������ ����!");
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXCore::OnRelease()
	{
		if (FAILED(RXSCENEMGR->getCurrentScene()->OnRelease()))
		{
			RXERRLOG("���� �� ���� ����!");
			return E_FAIL;
		}

		RXSCENEMGR->DeleteScene();
		::ReleaseDC(m_hMainWnd, m_hDC);
		return S_OK;
	}

	HRESULT RXCore::OnDrive()
	{
		// =====================================================================================
		// ���α׷� ���� ��ƾ
		// =====================================================================================
		if (FAILED(OnInit()))
		{
			RXERRLOG("���α׷� �ʱ�ȭ ����!");
			return E_FAIL;
		}

		// =====================================================================================
		// �޽��� ����
		// =====================================================================================
		MSG msg;
		::ZeroMemory(&msg, sizeof(msg));

		bool bDrive = true;
		while (bDrive != false)
		{
			if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					bDrive = false;
					m_msgCode = msg.wParam;
				}

				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				// ���� ������ �� �ڸ�
				// ������ �޽��� ó���� ���� �κ��� ����Ÿ���̶�� ��
				if (FAILED(OnUpdate()))
				{
					RXERRLOG("���α׷� ������Ʈ ����!");
					return E_FAIL;
				}

				if (FAILED(OnRender()))
				{
					RXERRLOG("���α׷� ������ ����!");
					return E_FAIL;
				}
			}
		}

		// =====================================================================================
		// ���α׷� ���� ��ƾ
		// =====================================================================================
		if (FAILED(OnRelease()))
		{
			RXERRLOG("���α׷� ���� ����!");
			return E_FAIL;
		}

		return S_OK;
	}

	// MAKEINTRESOURCE(100) => 16������ ��ȯ�Ǿ 0x00000064�� ����
	HRESULT RXCore::CreateWindowClass()
	{
		WNDCLASSEX wcex;
		::ZeroMemory(&wcex, sizeof(wcex));

		wcex.cbSize        = sizeof(wcex);
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = RXCore::WindowProcedure;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = m_hInst;
		wcex.hIcon         = ::LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_RUVENDIX_ICO));
		wcex.hCursor       = ::LoadCursor(m_hInst, MAKEINTRESOURCE(IDC_GAME));
		wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(LTGRAY_BRUSH));
		wcex.lpszMenuName  = nullptr;
		wcex.lpszClassName = g_szCore;
		wcex.hIconSm       = wcex.hIcon;

		if (FAILED(RegisterWindowClass(wcex)))
		{
			return E_FAIL;
		}		

		return S_OK;
	}

	HRESULT RXCore::RegisterWindowClass(const WNDCLASSEX& wcex)
	{
		if (::RegisterClassEx(&wcex) == 0)
		{
			RXERRLOG("������ Ŭ���� ��� ����!");
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXCore::CreateProgramWindow()
	{
		m_hMainWnd = ::CreateWindow(g_szCore, g_szCore, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			::GetDesktopWindow(), nullptr, m_hInst, nullptr);
		NULLCHK_RETURN_EFAIL_NOCOMENT(m_hMainWnd);

		m_hDC = ::GetDC(m_hMainWnd);
		NULLCHK_RETURN_EFAIL(m_hDC, "HDC �������� ����!");

		RECT rtWindow = { 0, 0, m_resolutionInfo.width , m_resolutionInfo.height };
		::AdjustWindowRect(&rtWindow, WS_OVERLAPPEDWINDOW, false);

		INT32 screenWidth  = ::GetSystemMetrics(SM_CXSCREEN);
		INT32 screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

		INT32 clientWidth  = rtWindow.right - rtWindow.left;
		INT32 clientHeight = rtWindow.bottom - rtWindow.top;

		// SWP_NOMOVE   => x, y ����
		// SWP_NOZORDER => hWndInsertAfter ����
		::SetWindowPos(m_hMainWnd, HWND_TOPMOST, (screenWidth - clientWidth) / 2,
			(screenHeight - clientHeight) / 2, clientWidth, clientHeight, SWP_NOZORDER);

		::UpdateWindow(m_hMainWnd);
		::ShowWindow(m_hMainWnd, SW_NORMAL);

		return S_OK;
	}

} // namespace RX end