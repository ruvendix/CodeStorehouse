#include "RXWindowClass.h"
#include "RXWindow.h"

namespace RX
{

	HRESULT RXWindowClass::Init(const std::wstring& szWndClass)
	{
		m_wcex               = { sizeof(m_wcex) };
		m_wcex.style         = CS_HREDRAW | CS_VREDRAW;
		m_wcex.lpfnWndProc   = RXWindowClass::WindowProcedure;
		m_wcex.cbClsExtra    = 0;
		m_wcex.cbWndExtra    = 0; //sizeof(LONG_PTR); // ����� ���� ������ �����Ҵ�
		m_wcex.hInstance     = RXGlobal::g_hMainInstance;
		m_wcex.hIcon         = nullptr;
		m_wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
		m_wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1); // GetStockBrush(GRAY_BRUSH));
		m_wcex.lpszMenuName  = nullptr;
		m_wcex.hIconSm       = m_wcex.hIcon;
		
		// ���� ������ ������ ������ϱ� ��������� �ִ´�!
		setWindowClassName(szWndClass);

		return RegisterWindowClass();
	}

	HRESULT RXWindowClass::RegisterWindowClass()
	{
		if (::RegisterClassEx(&m_wcex) == FALSE)
		{
			ERRMSGBOX(L"������ Ŭ���� ��� ����!");
			return E_FAIL;
		}

		return S_OK;
	}

	LRESULT RXWindowClass::WindowProcedure(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam)
	{
		// �ٽ��� �� �ڵ鸶�� ����� ���� �����͸� �����ؼ� �������� ��!
		// �̷��� �� ��ü �����Ͱ� ��ĥ ���� ����!
		//RXWindow* pWindow = reinterpret_cast<RXWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		RXWindow* pWindow = reinterpret_cast<RXWindow*>(::GetProp(hWnd, _T("WindowProcedure")));

		// WM_CREATE �� pWindow�� ���� �������ϴ�.
		if (message == WM_CREATE)
		{
			CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
			if (pCreateStruct == nullptr)
			{
				return ::DefWindowProc(hWnd, message, wParam, lParam);
			}

			// �θ� �����͸� �̿��ؼ� �ڽ� ��ü �����͸� �ֽ��ϴ�.
			pWindow = reinterpret_cast<RXWindow*>(pCreateStruct->lpCreateParams);
			if (pWindow == nullptr)
			{
				return ::DefWindowProc(hWnd, message, wParam, lParam);
			}

			//::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			::SetProp(hWnd, _T("WindowProcedure"), reinterpret_cast<HANDLE>(pWindow));
		}
		else
		{
			// WM_CREATE �������� nullptr �����Դϴ�.
			if (pWindow == nullptr)
			{
				return ::DefWindowProc(hWnd, message, wParam, lParam);
			}
		}

		switch (message)
		{
			HANDLE_MSG(hWnd, WM_CREATE,      pWindow->OnCreate);
			HANDLE_MSG(hWnd, WM_CLOSE,       pWindow->OnClose);
			HANDLE_MSG(hWnd, WM_DESTROY,     pWindow->OnDestroy);
			HANDLE_MSG(hWnd, WM_LBUTTONDOWN, pWindow->OnLButtonDown);
			HANDLE_MSG(hWnd, WM_RBUTTONDOWN, pWindow->OnRButtonDown);
			HANDLE_MSG(hWnd, WM_MOUSEMOVE,   pWindow->OnMouseMove);
			HANDLE_MSG(hWnd, WM_LBUTTONUP,   pWindow->OnLButtonUp);
			HANDLE_MSG(hWnd, WM_PAINT,       pWindow->OnPaint);
			HANDLE_MSG(hWnd, WM_KEYDOWN,     pWindow->OnKeyDown);
			HANDLE_MSG(hWnd, WM_COMMAND,     pWindow->OnCommand);

			// �ݵ�� ::DefWindowProc()�� ȣ��ǵ��� �ؾ� ��!
			//HANDLE_MSG(hWnd, WM_SYSKEYDOWN,  pWindow->OnSysKeyDown);
		}

		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}

} // namespace RX end