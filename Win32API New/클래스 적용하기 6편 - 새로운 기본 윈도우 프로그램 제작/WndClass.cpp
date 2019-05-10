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
	// ������ Ŭ������ �����ϰ� ����մϴ�.
	::ZeroMemory(&m_wcex, sizeof(m_wcex)); // ��������̹Ƿ� ����ϰ� �ʱ�ȭ�մϴ�.
	m_wcex.cbSize        = sizeof(m_wcex);
	m_wcex.style         = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc   = RXWndClass::WndProcedure; // �Լ� �̸��� �ּ��Դϴ�.
	// m_wcex.cbClsExtra    = 0;
	// m_wcex.cbWndExtra    = 0;
	m_wcex.hInstance     = RXGlobal::m_hMainInstance;
	// m_wcex.hIcon         = nullptr;
	m_wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = reinterpret_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
	// m_wcex.lpszMenuName  = nullptr;
	// m_wcex.lpszClassName = szWndClass.c_str(); // exe �̸����� �����մϴ�.
	m_wcex.hIconSm       = m_wcex.hIcon;

	// ���������� �Ҹ�ǹǷ� ��������� �����մϴ�.
	setWindowClassName(szWndClass);

	if (::RegisterClassEx(&m_wcex) == 0)
	{
		ERRMSGBOX(_T("������ Ŭ���� ��� ����!"));
		return E_FAIL;
	}
	// ======================================================================

	return S_OK;
}

// �޽���ť���� �޽����� ������ ��, �ü���� ȣ���ϴ� �ݹ��Դϴ�.
LRESULT RXWndClass::WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ======================================================================
	// ������ ����� ���� ������ �����ɴϴ�.
	// �� ��ü���� ������ ������ �ٸ��� ������ �ڵ鰪�� �ߺ����� �ʽ��ϴ�.
	// ��, ������ ���ν��� �ϳ������� �������� �̿��� �� �ֽ��ϴ�.
	RXWnd* pWnd = reinterpret_cast<RXWnd*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

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

		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
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
		HANDLE_MSG(hWnd, WM_DESTROY,     pWnd->OnDestroy);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, pWnd->OnLButtonDown);
	}

	// ======================================================================
	// ��κ��� �޽����� �ü������ �����ϴ�.
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}