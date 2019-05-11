// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

/*
	전에는 WIN32_LEAN_AND_MEAN을 사용했지만,
	요즘 컴퓨터 사양에서는 의미가 없으므로 제거합니다.
*/

// 멀티바이트, 유니코드 전환 기능을 사용합니다.
#include <tchar.h>

// Win32 API를 사용합니다.
#include <windows.h>

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam);

// 윈도우 프로그램의 진입점입니다.
INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCommandLine, INT32 showStyle)
{
	// ======================================================================
	// 사용하지 않는 매개변수입니다.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCommandLine);

	// ======================================================================
	// 윈도우 클래스를 정의하고 등록합니다.
	WNDCLASSEX wcex    = { sizeof(wcex) }; // 나머지 멤버는 자동 0으로 채워집니다.
	wcex.hInstance     = hInstance;
	wcex.lpszClassName = _T("Sample"); // exe 이름과는 무관합니다.
	wcex.lpfnWndProc   = WndProcedure; // 함수 이름은 주소입니다.
	wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));

	::RegisterClassEx(&wcex);

	// ======================================================================
	// 윈도우를 생성하고 사용자에게 보여줍니다.
	HWND hWnd = ::CreateWindow(wcex.lpszClassName, wcex.lpszClassName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, hInstance, nullptr);

	::UpdateWindow(hWnd); 
	::ShowWindow(hWnd, showStyle);

	// ======================================================================
	// 메시지 루프입니다.
	MSG message;
	::ZeroMemory(&message, sizeof(message));

	while (::GetMessage(&message, nullptr, 0, 0) == TRUE)
	{
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}
	// ======================================================================

	return static_cast<INT32>(message.wParam);
}

// 메시지큐에서 메시지를 가져온 후, 운영체제가 호출하는 콜백입니다.
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		// WM_DESTROY를 받으면 WM_QUIT을 보냅니다.
		::PostQuitMessage(EXIT_SUCCESS);
		return S_OK;
	}

	// 대부분의 메시지는 운영체제에게 보냅니다.
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}