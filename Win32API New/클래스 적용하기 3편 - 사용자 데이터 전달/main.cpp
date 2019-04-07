#include <windows.h>
#include <windowsx.h> // 매크로, 메시지 크래커, 컨트롤 편의 기능 포함

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam);

class MessageHandler
{
public:
	BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
	void OnDestroy(HWND hWnd);
};

MessageHandler g_messageHandler;

INT32 APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, INT32 cmdShow)
{
	WNDCLASSEX wcex    = { sizeof(wcex) };
	wcex.hInstance     = hInstance;
	wcex.lpszClassName = L"Base Window Program";
	wcex.lpfnWndProc   = WindowProcedure;
	wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
	
	// 사용자 정의 데이터를 위한 공간입니다.
	// 일반적으로는 사용하지 않으므로 0으로 초기화하지만
	// 기본 윈도우 프로그램의 클래스화를 위해서는 필요하므로 4바이트만큼 할당합니다.
	wcex.cbWndExtra = sizeof(LONG_PTR);

	::RegisterClassEx(&wcex);

	HWND hWnd = ::CreateWindow(wcex.lpszClassName, wcex.lpszClassName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, hInstance,
		&g_messageHandler); // void*를 받으므로 모든 포인터를 넣을 수 있습니다.

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
	MessageHandler* pMessageHandler =
		reinterpret_cast<MessageHandler*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// WM_CREATE 공용 처리는 예외입니다.
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		::SetWindowLongPtr(hWnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
		pMessageHandler = reinterpret_cast<MessageHandler*>(pCreateStruct->lpCreateParams);
	}

	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE,  pMessageHandler->OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, pMessageHandler->OnDestroy);
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL MessageHandler::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	return TRUE;
}

void MessageHandler::OnDestroy(HWND hWnd)
{
	::PostQuitMessage(EXIT_SUCCESS);
}