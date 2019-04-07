#include "RXWindowClass.h"
#include "RXWindow.h"

namespace RX
{
	
	HRESULT RXWindowClass::Init(const std::wstring& szWndClass)
	{
		WNDCLASSEX wcex    = { sizeof(wcex) };
		wcex.lpfnWndProc   = RXWindowClass::WindowProcedure;
		wcex.cbWndExtra    = sizeof(LONG_PTR); // 사용자 정의 데이터 공간할당
		wcex.hInstance     = RXGlobal::m_hMainInstance;
		wcex.hbrBackground = reinterpret_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
		wcex.lpszClassName = szWndClass.c_str();

		::RegisterClassEx(&wcex);
		
		return S_OK;
	}

	LRESULT RXWindowClass::WindowProcedure(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam)
	{
		// 핵심은 각 핸들마다 사용자 정의 데이터를 지정해서 가져오는 것!
		// 이러면 각 객체 포인터가 겹칠 일이 없음!
		RXWindow* pWindow = reinterpret_cast<RXWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

		// WM_CREATE 때 pWindow의 값이 정해집니다.
		if (message == WM_CREATE)
		{
			CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
			pWindow = reinterpret_cast<RXWindow*>(pCreateStruct->lpCreateParams);
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		}
		else
		{
			// WM_CREATE 이전에는 nullptr 고정입니다.
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