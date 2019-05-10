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

// 매크로, 메시지 크래커, 컨트롤 편의 기능을 사용합니다.
#include <windowsx.h>

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam);

// 메시지 핸들러 모음입니다.
class MessageHandler
{
public:
	BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
	void OnDestroy(HWND hWnd);
};

// 이름 없는 namespace는 현재 파일에서만 사용한다는 의미입니다.
namespace
{
	MessageHandler gs_messageHandler;
}

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
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, hInstance,
		&gs_messageHandler); // 사용자 정의 정보는 void* 형식을 받으므로 모든 포인터가 해당됩니다.

	UpdateWindow(hWnd); 
	ShowWindow(hWnd, showStyle);

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

// 메시지큐에서 메시지를 가져온 후, 운영체제가 호출하는 콜백 함수입니다.
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam)
{
	// ======================================================================
	// 저장한 사용자 정의 정보를 가져옵니다.
	MessageHandler* pMessageHandler =
		reinterpret_cast<MessageHandler*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// ======================================================================
	// WM_CREATE 정보에는 전달한 사용자 정의 정보가 있습니다.
	// 해당 정보를 가져온 후, 메모리에 저장해둡니다.
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		::SetWindowLongPtr(hWnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
		pMessageHandler = reinterpret_cast<MessageHandler*>(pCreateStruct->lpCreateParams);
	}

	// ======================================================================
	// 메시지 크래커 스위치입니다.
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE,  pMessageHandler->OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, pMessageHandler->OnDestroy);
	}

	// ======================================================================
	// 대부분의 메시지는 운영체제에게 보냅니다.
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

// WM_CREATE 핸들러입니다.
BOOL MessageHandler::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	return TRUE;
}

// WM_DESTROY 핸들러입니다.
void MessageHandler::OnDestroy(HWND hWnd)
{
	::PostQuitMessage(EXIT_SUCCESS);
}