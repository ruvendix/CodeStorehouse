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

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam);

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
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, hInstance, nullptr);

	::UpdateWindow(hWnd); 
	::ShowWindow(hWnd, showStyle);

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

// �޽���ť���� �޽����� ������ ��, �ü���� ȣ���ϴ� �ݹ��Դϴ�.
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		// WM_DESTROY�� ������ WM_QUIT�� �����ϴ�.
		::PostQuitMessage(EXIT_SUCCESS);
		return S_OK;
	}

	// ��κ��� �޽����� �ü������ �����ϴ�.
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}