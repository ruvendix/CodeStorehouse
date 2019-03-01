/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-02
 *
 * <파일 내용>
 * 게임 프로그램의 핵심 루틴입니다.
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
			RXLOG("프로그램 윈도우 생성!");
			break;
		}
		case WM_CLOSE:
		{
			RXLOG("프로그램 닫기 버튼 클릭!");
			::DestroyWindow(hMainWnd);
			break;
		}
		case WM_DESTROY:
		{
			RXLOG("프로그램 종료!");
			::PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
			{
				RXLOG("ESC 입력!");
				::DestroyWindow(hMainWnd);
				break;
			}
			}

			break;
		}
		case WM_SYSCOMMAND:
		{
			// 하위 4비트는 내부적으로 사용하는 값이므로 날려야 함!
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
		// 로케일 세팅입니다.
		// 시스템 로케일을 따릅니다.
		_wsetlocale(LC_ALL, L""); // nullptr이 아니라 L""로 설정!

		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		RXFPSMGR->UpdateFrame();

		m_hInst = ::GetModuleHandle(nullptr);
		NULLCHK_RETURN_EFAIL_NOCOMENT(m_hInst);

		if (FAILED(CreateWindowClass()))
		{
			RXERRLOG("윈도우 클래스 생성 실패!");
			return E_FAIL;
		}

		if (FAILED(CreateProgramWindow()))
		{
			RXERRLOG("프로그램 윈도우 생성 실패!");
			return E_FAIL;
		}

		RXSCENEMGR->CreateScene<RXScene>();
		if (FAILED(RXSCENEMGR->getCurrentScene()->OnInit()))
		{
			RXERRLOG("게임 씬 초기화 실패!");
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXCore::OnUpdate()
	{
		RXFPSMGR->UpdateFrame();

		if (FAILED(RXSCENEMGR->getCurrentScene()->OnUpdate()))
		{
			RXERRLOG("게임 씬 업데이트 실패!");
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXCore::OnRender()
	{
		if (FAILED(RXSCENEMGR->getCurrentScene()->OnRender()))
		{
			RXERRLOG("게임 씬 렌더링 실패!");
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXCore::OnRelease()
	{
		if (FAILED(RXSCENEMGR->getCurrentScene()->OnRelease()))
		{
			RXERRLOG("게임 씬 해제 실패!");
			return E_FAIL;
		}

		RXSCENEMGR->DeleteScene();
		::ReleaseDC(m_hMainWnd, m_hDC);
		return S_OK;
	}

	HRESULT RXCore::OnDrive()
	{
		// =====================================================================================
		// 프로그램 시작 루틴
		// =====================================================================================
		if (FAILED(OnInit()))
		{
			RXERRLOG("프로그램 초기화 실패!");
			return E_FAIL;
		}

		// =====================================================================================
		// 메시지 루프
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
				// 게임 로직이 올 자리
				// 윈도우 메시지 처리가 없는 부분을 데드타임이라고 함
				if (FAILED(OnUpdate()))
				{
					RXERRLOG("프로그램 업데이트 실패!");
					return E_FAIL;
				}

				if (FAILED(OnRender()))
				{
					RXERRLOG("프로그램 렌더링 실패!");
					return E_FAIL;
				}
			}
		}

		// =====================================================================================
		// 프로그램 종료 루틴
		// =====================================================================================
		if (FAILED(OnRelease()))
		{
			RXERRLOG("프로그램 종료 실패!");
			return E_FAIL;
		}

		return S_OK;
	}

	// MAKEINTRESOURCE(100) => 16진수로 변환되어서 0x00000064로 변함
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
			RXERRLOG("윈도우 클래스 등록 실패!");
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
		NULLCHK_RETURN_EFAIL(m_hDC, "HDC 가져오기 실패!");

		RECT rtWindow = { 0, 0, m_resolutionInfo.width , m_resolutionInfo.height };
		::AdjustWindowRect(&rtWindow, WS_OVERLAPPEDWINDOW, false);

		INT32 screenWidth  = ::GetSystemMetrics(SM_CXSCREEN);
		INT32 screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

		INT32 clientWidth  = rtWindow.right - rtWindow.left;
		INT32 clientHeight = rtWindow.bottom - rtWindow.top;

		// SWP_NOMOVE   => x, y 무시
		// SWP_NOZORDER => hWndInsertAfter 무시
		::SetWindowPos(m_hMainWnd, HWND_TOPMOST, (screenWidth - clientWidth) / 2,
			(screenHeight - clientHeight) / 2, clientWidth, clientHeight, SWP_NOZORDER);

		::UpdateWindow(m_hMainWnd);
		::ShowWindow(m_hMainWnd, SW_NORMAL);

		return S_OK;
	}

} // namespace RX end