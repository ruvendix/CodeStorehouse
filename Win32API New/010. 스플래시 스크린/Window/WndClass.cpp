// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "WndClass.h"

// RXWnd�� ����մϴ�.
#include "Wnd.h"

HRESULT RXWndClass::Init(const std::wstring& szWndClass)
{
	// ======================================================================
	// ������ Ŭ������ �����մϴ�.
	::ZeroMemory(&m_wcex, sizeof(m_wcex)); // ��������̹Ƿ� ����ϰ� �ʱ�ȭ�մϴ�.
	m_wcex.cbSize        = sizeof(m_wcex);
	m_wcex.style         = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc   = RXWndClass::WndProcedure; // �Լ� �̸��� �ּ��Դϴ�.
	// m_wcex.cbClsExtra    = 0;
	// m_wcex.cbWndExtra    = 0;
	m_wcex.hInstance     = RXGlobal::m_hMainInstance;
	// m_wcex.hIcon         = nullptr;
	m_wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = reinterpret_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	// m_wcex.lpszMenuName  = nullptr;
	// m_wcex.lpszClassName = szWndClass.c_str(); // exe �̸����� �����մϴ�.
	m_wcex.hIconSm       = m_wcex.hIcon;

	// ���������� �Ҹ�ǹǷ� ��������� �����մϴ�.
	setWindowClassName(szWndClass);
	
	// ======================================================================
	// ������ Ŭ������ ����մϴ�.
	return RegisterWndClass();
}

HRESULT RXWndClass::RegisterWndClass()
{
	if (::RegisterClassEx(&m_wcex) == FALSE)
	{
		ERRMSGBOX(L"������ Ŭ���� ��� ����!");
		return E_FAIL;
	}

	return S_OK;
}

// �޽���ť���� �޽����� ������ ��, �ü���� ȣ���ϴ� �ݹ��Դϴ�.
LRESULT RXWndClass::WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ======================================================================
	// ������ ����� ���� ������ �����ɴϴ�.
	// �� ��ü���� ������ ������ �ٸ��� ������ �ڵ鰪�� �ߺ����� �ʽ��ϴ�.
	// ��, ������ ���ν��� �ϳ������� �������� �̿��� �� �ֽ��ϴ�.
	// RXWnd* pWnd = reinterpret_cast<RXWnd*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// ������ ������ �ƴ� ������ ������Ƽ�� �����մϴ�.
	RXWnd* pWnd = reinterpret_cast<RXWnd*>(::GetProp(hWnd, RXGlobal::SZ_WND_PROCEDURE_PROPERTY));

	// ======================================================================
	// WM_CREATE �������� ������ ����� ���� ������ �ֽ��ϴ�.
	// �ش� ������ ������ ��, �޸𸮿� �����صӴϴ�.
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		if (pCreateStruct == nullptr)
		{
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}

		// �θ� �����͸� �̿��ؼ� �ڽ� ��ü �����͸� �ֽ��ϴ�.
		pWnd = reinterpret_cast<RXWnd*>(pCreateStruct->lpCreateParams);
		if (pWnd == nullptr)
		{
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}

		// ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		// ������ ������ �ƴ� ������ ������Ƽ�� �����մϴ�.
		::SetProp(hWnd, RXGlobal::SZ_WND_PROCEDURE_PROPERTY, reinterpret_cast<HANDLE>(pWnd));
	}
	else
	{
		// WM_CREATE �������� nullptr �����Դϴ�.
		// �̶��� �޽����� �ü������ �����ϴ�.
		if (pWnd == nullptr)
		{
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	// ======================================================================
	// �޽��� ũ��Ŀ ����ġ�Դϴ�.
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE,      pWnd->OnCreate);
		HANDLE_MSG(hWnd, WM_CLOSE,       pWnd->OnClose);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE,   pWnd->OnMouseMove);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, pWnd->OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP,   pWnd->OnLButtonUp);
		HANDLE_MSG(hWnd, WM_PAINT,       pWnd->OnPaint);
		HANDLE_MSG(hWnd, WM_KEYDOWN,     pWnd->OnKeyDown);
		HANDLE_MSG(hWnd, WM_TIMER,       pWnd->OnTimer);
		HANDLE_MSG(hWnd, WM_DESTROY,     pWnd->OnDestroy);
	}

	// ======================================================================
	// ��κ��� �޽����� �ü������ �����ϴ�.
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}