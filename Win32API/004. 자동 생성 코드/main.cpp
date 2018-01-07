/*
 * <���� ����>
 * ���־� ��Ʃ����� �ڵ����� �������ִ� �⺻ �ڵ��Դϴ�.
 * �⺻ �ڵ忡 �ּ��� �߰��ϸ鼭 �ʿ��� �κ��� �����߽��ϴ�.
 * ���ҽ� ������ ���� �ڵ带 �ۼ��ϱ⺸�ٴ� �ڵ� ���� �ڵ带 ���� �̿��մϴ�.
 */

// 004. �ڵ� ���� �ڵ�.cpp: ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h" // �̸� �����ϵ� ��� �����Դϴ�. �ҽ� ���Ͽ� ù ��°�� ���Խ��Ѿ� �մϴ�.
#include "004. �ڵ� ���� �ڵ�.h" // ���ҽ� ID�� ������ �����Դϴ�.

#define MAX_LOADSTRING 256

// ���� ����:
HINSTANCE hInst;                      // ���� �ν��Ͻ��Դϴ�.
WCHAR strCaption[MAX_LOADSTRING];     // ���� ǥ���� �ؽ�Ʈ�Դϴ�. ���α׷��� ĸ���Դϴ�.
WCHAR strWindowClass[MAX_LOADSTRING]; // �⺻ â Ŭ���� �̸��Դϴ�. �ν��Ͻ������� �����˴ϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.


	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, strCaption, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY004, strWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (InitInstance(hInstance, nCmdShow) == FALSE)
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY004));

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (TranslateAccelerator(msg.hwnd, hAccelTable, &msg) == FALSE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return static_cast<int>(msg.wParam);
}

//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	// ������ Ŭ������ ũ���Դϴ�.
	wcex.cbSize = sizeof(WNDCLASSEX);

	// ������ Ŭ������ ��Ÿ���Դϴ�.
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// ������ ���ν���(�޽��� �ڵ鷯)�Դϴ�. �ݹ� �����Դϴ�.
	wcex.lpfnWndProc = WndProc;

	// ������ Ŭ������ �Ҵ��� ������ �޸��Դϴ�.
	wcex.cbClsExtra = 0;

	// �����쿡 �Ҵ��� ������ �޸��Դϴ�.
	wcex.cbWndExtra = 0;

	// �ν��Ͻ� �ڵ��Դϴ�.
	wcex.hInstance = hInstance;

	// ������ �ڵ��Դϴ�. ���α׷� ���� ���� ǥ�õ˴ϴ�.
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY004));

	// Ŀ�� �ڵ��Դϴ�. IDC_ARROW�� MAKEINTRESOURCE()�� �����Ǿ��ֽ��ϴ�.
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// ��� �귯�� �ڵ��Դϴ�. COLOR_BACKGROUND�� ȸ���Դϴ�.
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

	// �޴� �ڵ��Դϴ�.
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY004);

	// ������ Ŭ���� �̸��Դϴ�.
	wcex.lpszClassName = strWindowClass;

	// �۾� ǥ���ٿ� ǥ�õǴ� ������ �ڵ��Դϴ�.
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	HWND hWnd = CreateWindowW(strWindowClass, strCaption, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 1, 800, 0, nullptr, nullptr, hInstance, nullptr);

	if (hWnd == nullptr)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND: // �޴� �Ǵ� ��Ʈ��(��ư ���� ��)�� Ŭ���� �� �߻��˴ϴ�.
	{
		int wmId = LOWORD(wParam); // ���� 16����Ʈ�� �̾Ƴ��� ��ũ�� �Լ��Դϴ�.

								   // �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_ABOUT:
			// �����(Modal, ��Ŀ���� ���ߵ� ����) ��ȭ���ڸ� �����մϴ�.
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			// �����츦 �ı��մϴ�. WM_DESTORY �޽����� �߻���ŵ�ϴ�.
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: // Ŭ���̾�Ʈ ����(�޴�, Ÿ��Ʋ�� ���� ������ ����)�� ����մϴ�.
	{
		PAINTSTRUCT ps; // BeginPaint()�� ������ �����Դϴ�.

		// ������ �������� Ŭ���̾�Ʈ ���� DC(Device Context)�� �����ɴϴ�.
		// DC�� �ü���� �ֺ���ġ�� ���������� �����ϱ� ���� �����Դϴ�.
		// DC�� �˾Ƴ��� GDI(Graphic Device Interface)�� �̿��ؼ�
		// GDI Object(��, �귯��, ��Ʈ ��)�� ����� �� �ֽ��ϴ�.
		// ���ſ��� �ֺ���ġ���� ����� �� �ִ� ������ ���� �����ߴٰ� �մϴ�.
		// ������ �ֺ���ġ�� �������� ������ ������ ����ڴ� �� ������ �̿��ؼ�
		// �پ��� ��� �۾��� �� �� �ֽ��ϴ�. �̰��� DirectX���� ����Ǵ� ����Դϴ�.
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

		// WM_PAINT�� �ü���� �����ϴ� �޽���ť�� ����Ǵ� �� �ƴ϶�
		// �޽��� ���̺��̶�� ���� ����˴ϴ�. �޽���ť�� ����� �޽�������
		// ������� ó���Ǵ� �� �ƴ϶� �켱������ �������־ �� ������� ó���˴ϴ�.
		// WM_PAINT�� �޽��� ���̺�� �з��Ǵ� ������ ��� �۾� �󵵼��� �����ϱ� ���ؼ��Դϴ�.
		// �ƹ��͵� ���� �ʴµ� ��� ����� ���� �����Ƿ� WM_PAINT �޽����� �߻��Ǹ�
		// EndPaint()���� �޽��� ���̺� ����� WM_PAINT�� �Ӽ��� �ٲ��ݴϴ�.
		// �̷��� �ϸ� ����ڰ� WM_PAINT �޽����� ��û�ϱ� �������� ��� �۾��� �̷������ �ʽ��ϴ�.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE: // �����찡 ������ �� �߻��Ǵ� �޽����Դϴ�.
	{
		OutputDebugString(_T("�����츦 �����߽��ϴ�.\n"));
		break;
	}
	case WM_CLOSE: // �ݱ� ��ư�� ������ �� �߻��Ǵ� �޽����Դϴ�.
	{
		OutputDebugString(_T("�����츦 �ݾҽ��ϴ�.\n"));
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY: // �����찡 �ı��� �� �߻��Ǵ� �޽����Դϴ�.
		OutputDebugString(_T("�����찡 �ı��Ǿ����ϴ�.\n"));
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
