/*
 * <파일 설명>
 * 비주얼 스튜디오가 자동으로 생성해주는 기본 코드입니다.
 * 기본 코드에 주석을 추가하면서 필요한 부분은 수정했습니다.
 * 리소스 때문에 직접 코드를 작성하기보다는 자동 생성 코드를 많이 이용합니다.
 */

// 004. 자동 생성 코드.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h" // 미리 컴파일된 헤더 파일입니다. 소스 파일에 첫 번째로 포함시켜야 합니다.
#include "004. 자동 생성 코드.h" // 리소스 ID를 포함한 파일입니다.

#define MAX_LOADSTRING 256

// 전역 변수:
HINSTANCE hInst;                      // 현재 인스턴스입니다.
WCHAR strCaption[MAX_LOADSTRING];     // 제목 표시줄 텍스트입니다. 프로그램의 캡션입니다.
WCHAR strWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다. 인스턴스끼리는 공유됩니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

	// TODO: 여기에 코드를 입력합니다.


	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, strCaption, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY004, strWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (InitInstance(hInstance, nCmdShow) == FALSE)
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY004));

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	// 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	// 윈도우 클래스의 크기입니다.
	wcex.cbSize = sizeof(WNDCLASSEX);

	// 윈도우 클래스의 스타일입니다.
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 프로시저(메시지 핸들러)입니다. 콜백 형식입니다.
	wcex.lpfnWndProc = WndProc;

	// 윈도우 클래스에 할당할 여분의 메모리입니다.
	wcex.cbClsExtra = 0;

	// 윈도우에 할당할 여분의 메모리입니다.
	wcex.cbWndExtra = 0;

	// 인스턴스 핸들입니다.
	wcex.hInstance = hInstance;

	// 아이콘 핸들입니다. 프로그램 왼쪽 위에 표시됩니다.
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY004));

	// 커서 핸들입니다. IDC_ARROW에 MAKEINTRESOURCE()가 설정되어있습니다.
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// 배경 브러시 핸들입니다. COLOR_BACKGROUND는 회색입니다.
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

	// 메뉴 핸들입니다.
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY004);

	// 윈도우 클래스 이름입니다.
	wcex.lpszClassName = strWindowClass;

	// 작업 표시줄에 표시되는 아이콘 핸들입니다.
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND: // 메뉴 또는 컨트롤(버튼 같은 것)을 클릭할 때 발생됩니다.
	{
		int wmId = LOWORD(wParam); // 하위 16바이트만 뽑아내는 매크로 함수입니다.

								   // 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			// 모달형(Modal, 포커스가 집중된 형식) 대화상자를 생성합니다.
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			// 윈도우를 파괴합니다. WM_DESTORY 메시지를 발생시킵니다.
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: // 클라이언트 영역(메뉴, 타이틀바 등을 제외한 영역)을 출력합니다.
	{
		PAINTSTRUCT ps; // BeginPaint()에 전달할 정보입니다.

		// 설정한 윈도우의 클라이언트 영역 DC(Device Context)를 가져옵니다.
		// DC는 운영체제가 주변장치에 독립적으로 적용하기 위한 정보입니다.
		// DC를 알아내면 GDI(Graphic Device Interface)를 이용해서
		// GDI Object(펜, 브러시, 폰트 등)를 출력할 수 있습니다.
		// 과거에는 주변장치마다 출력할 수 있는 정보를 각각 구현했다고 합니다.
		// 하지만 주변장치에 독립적인 정보가 있으면 사용자는 그 정보를 이용해서
		// 다양한 출력 작업을 할 수 있습니다. 이것은 DirectX에도 적용되는 얘기입니다.
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

		// WM_PAINT는 운영체제가 관리하는 메시지큐에 저장되는 게 아니라
		// 메시지 테이블이라는 곳에 저장됩니다. 메시지큐에 저장된 메시지들은
		// 순서대로 처리되는 게 아니라 우선순위가 정해져있어서 그 순서대로 처리됩니다.
		// WM_PAINT가 메시지 테이블로 분류되는 이유는 출력 작업 빈도수를 조절하기 위해서입니다.
		// 아무것도 하지 않는데 계속 출력할 수는 없으므로 WM_PAINT 메시지가 발생되면
		// EndPaint()에서 메시지 테이블에 저장된 WM_PAINT의 속성을 바꿔줍니다.
		// 이렇게 하면 사용자가 WM_PAINT 메시지를 요청하기 전까지는 출력 작업이 이루어지지 않습니다.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE: // 윈도우가 생성될 때 발생되는 메시지입니다.
	{
		OutputDebugString(_T("윈도우를 생성했습니다.\n"));
		break;
	}
	case WM_CLOSE: // 닫기 버튼을 눌렀을 때 발생되는 메시지입니다.
	{
		OutputDebugString(_T("윈도우를 닫았습니다.\n"));
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY: // 윈도우가 파괴될 때 발생되는 메시지입니다.
		OutputDebugString(_T("윈도우가 파괴되었습니다.\n"));
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
