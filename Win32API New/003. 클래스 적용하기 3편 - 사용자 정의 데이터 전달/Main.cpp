// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

/*
	������ WIN32_LEAN_AND_MEAN�� ���������,
	���� ��ǻ�� ��翡���� �ǹ̰� �����Ƿ� �����մϴ�.
*/

// ��Ƽ����Ʈ, �����ڵ� ��ȯ ����� ����մϴ�.
#include <tchar.h>

// Win32 API�� ����մϴ�.
#include <windows.h>

// ��ũ��, �޽��� ũ��Ŀ, ��Ʈ�� ���� ����� ����մϴ�.
#include <windowsx.h>

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam);

// �޽��� �ڵ鷯 �����Դϴ�.
class MessageHandler
{
public:
	BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
	void OnDestroy(HWND hWnd);
};

// �̸� ���� namespace�� ���� ���Ͽ����� ����Ѵٴ� �ǹ��Դϴ�.
namespace
{
	MessageHandler gs_messageHandler;
}

// ������ ���α׷��� �������Դϴ�.
INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCommandLine, INT32 showStyle)
{
	// ======================================================================
	// ������� �ʴ� �Ű������Դϴ�.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCommandLine);

	// ======================================================================
	// ������ Ŭ������ �����ϰ� ����մϴ�.
	WNDCLASSEX wcex    = { sizeof(wcex) }; // ������ ����� �ڵ� 0���� ä�����ϴ�.
	wcex.hInstance     = hInstance;
	wcex.lpszClassName = _T("Sample"); // exe �̸����� �����մϴ�.
	wcex.lpfnWndProc   = WndProcedure; // �Լ� �̸��� �ּ��Դϴ�.
	wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));

	::RegisterClassEx(&wcex);

	// ======================================================================
	// �����츦 �����ϰ� ����ڿ��� �����ݴϴ�.
	HWND hWnd = ::CreateWindow(wcex.lpszClassName, wcex.lpszClassName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, hInstance,
		&gs_messageHandler); // ����� ���� ������ void* ������ �����Ƿ� ��� �����Ͱ� �ش�˴ϴ�.

	UpdateWindow(hWnd); 
	ShowWindow(hWnd, showStyle);

	// ======================================================================
	// �޽��� �����Դϴ�.
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

// �޽���ť���� �޽����� ������ ��, �ü���� ȣ���ϴ� �ݹ� �Լ��Դϴ�.
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam)
{
	// ======================================================================
	// ������ ����� ���� ������ �����ɴϴ�.
	MessageHandler* pMessageHandler =
		reinterpret_cast<MessageHandler*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// ======================================================================
	// WM_CREATE �������� ������ ����� ���� ������ �ֽ��ϴ�.
	// �ش� ������ ������ ��, �޸𸮿� �����صӴϴ�.
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		::SetWindowLongPtr(hWnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
		pMessageHandler = reinterpret_cast<MessageHandler*>(pCreateStruct->lpCreateParams);
	}

	// ======================================================================
	// �޽��� ũ��Ŀ ����ġ�Դϴ�.
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE,  pMessageHandler->OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, pMessageHandler->OnDestroy);
	}

	// ======================================================================
	// ��κ��� �޽����� �ü������ �����ϴ�.
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

// WM_CREATE �ڵ鷯�Դϴ�.
BOOL MessageHandler::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	return TRUE;
}

// WM_DESTROY �ڵ鷯�Դϴ�.
void MessageHandler::OnDestroy(HWND hWnd)
{
	::PostQuitMessage(EXIT_SUCCESS);
}