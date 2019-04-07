#include "RXWindowClass.h"
#include "RXWindow.h"

namespace RX
{
	HRESULT RXWindowClass::Init(const std::wstring& szWndClass)
	{
		WNDCLASSEX wcex    = { sizeof(wcex) };
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = RXWindowClass::WindowProcedure;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = sizeof(LONG_PTR); // ����� ���� ������ �����Ҵ�
		wcex.hInstance     = RXGlobal::m_hMainInstance;
		wcex.hIcon         = nullptr;
		wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = reinterpret_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
		wcex.lpszMenuName  = nullptr;
		wcex.lpszClassName = szWndClass.c_str();
		wcex.hIconSm       = wcex.hIcon;

		if (::RegisterClassEx(&wcex) == 0)
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
		RXWindow* pWindow =
			reinterpret_cast<RXWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

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

			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
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
		}

		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}

} // namespace RX end