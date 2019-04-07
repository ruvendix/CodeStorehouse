#include <windows.h>
#include <windowsx.h> // 매크로, 메시지 크래커, 컨트롤 편의 기능 포함

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam);

void OnDestroy(HWND hWnd);

INT32 APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, INT32 cmdShow)
{
	WNDCLASSEX wcex    = { sizeof(wcex) };
	wcex.hInstance     = hInstance;
	wcex.lpszClassName = L"Base Window Program";
	wcex.lpfnWndProc   = WindowProcedure;
	wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));

	::RegisterClassEx(&wcex);

	HWND hWnd = ::CreateWindow(wcex.lpszClassName, wcex.lpszClassName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, hInstance, nullptr);

	UpdateWindow(hWnd); 
	ShowWindow(hWnd, cmdShow);
	
	MSG message;
	::ZeroMemory(&message, sizeof(message));

	while (true)
	{
		if (message.message == WM_QUIT)
		{
			break;
		}

		if (::GetMessage(&message, nullptr, 0, 0))
		{
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
	}

	return static_cast<INT32>(message.wParam);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// WM_DESTROY 메시지 크래커 적용
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnDestroy(HWND hWnd)
{
	::PostQuitMessage(EXIT_SUCCESS);
}