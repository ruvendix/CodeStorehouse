/*
 * <파일 설명>
 * 다중 인스턴스 방지 예제입니다.
 * Mutex를 이용하면 다중 인스턴스를 방지할 수 있습니다.
 * 쓰레드에 관해서 잘 몰라도 CreateMutex()를 이용하면 쉽게 구현할 수 있습니다.
 */

// 006. 다중 인스턴스 방지.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "006. 다중 인스턴스 방지.h"

#define MAX_LOADSTRING 256

// 전역 변수
HINSTANCE hInst;                       // 현재 인스턴스입니다.
TCHAR tstrTitle[MAX_LOADSTRING];       // 제목 표시줄 텍스트입니다.
TCHAR tstrWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

// 전역 상수
LPCTSTR STR_MUTEX_NAME = _T("My Mutex");    // Mutex 이름입니다.

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
	// 다중 인스턴스를 방지합니다.
	// 먼저 Mutex(Mutual Exclusion)가 존재하는지 확인합니다.
	// OpenMutex()는 접근 모드, 상속 핸들 여부, Mutex 이름의 인자를 받습니다.
	// 여기서 가장 중요한 건 Mutex 이름입니다.
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, STR_MUTEX_NAME);
	if (hMutex == nullptr)
	{
		// Mutex를 생성합니다.
		// 첫 번째 인자는 보안 형식인데 nullptr을 넣으면 알아서 설정됩니다.
		// 두 번째 인자는 초기화 소유자를 말하는데 TRUE를 넣으면 됩니다.
		// 세 번째 인자가 중요한데 여기에는 Mutex의 이름을 넣습니다.
		// 생성된 Mutex는 중복되지 않으므로 이걸 이용해서 다중 인스턴스 방지를 할 수 있습니다.
		hMutex = CreateMutex(nullptr, TRUE, STR_MUTEX_NAME);
		OutputDebugString(_T("Mutex를 생성했습니다.\n"));
	}
	else
	{
		MessageBox(nullptr, _T("중복 실행은 불가능합니다!"), _T("오류 안내"), MB_ICONERROR);
		return 0;
	}

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, tstrTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY006, tstrWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY006));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY006));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY006);
    wcex.lpszClassName  = tstrWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(tstrWindowClass, tstrTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
