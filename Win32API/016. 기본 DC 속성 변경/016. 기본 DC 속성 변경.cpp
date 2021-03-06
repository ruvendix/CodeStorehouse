/*
 * <파일 설명>
 * 기본 DC의 속성을 변경해보는 예제입니다.
 * 기본 DC란 운영체제가 미리 만들어놓은 DC를 말합니다.
 * GetStockObject()를 이용하면 기본 DC의 속성을 알아낼 수 있습니다.
 * 함수는 SetDCPenColor()와 SetDCBrushColor()를 사용해볼 겁니다.
 */

// 016. 기본 DC 속성 변경.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////
// 매크로 상수 입니다.
#define MAX_LOADSTRING 256
#define MAX_STRING     256

//////////////////////////////////////////////////////////////////////////
// 매크로 함수입니다.
#define ERROR_POPUP(str)             MessageBox(nullptr, _T(str), _T("오류 팝업창"), MB_ICONERROR)
#define NORMAL_POPUP(str)            MessageBox(nullptr, _T(str), _T("기본 팝업창"), MB_OK)
#define NORMAL_POPUP_USE_BUFFER(str) MessageBox(nullptr, str, _T("기본 팝업창"), MB_OK)
#define DEBUG_LOG(str)               OutputDebugString(_T(str)); OutputDebugString(_T("\n"))

#define SAFE_DELETE_ARRAY(ptr)\
if (ptr)\
{\
    delete[] ptr;\
    ptr = nullptr;\
}

//////////////////////////////////////////////////////////////////////////
// 전역 변수:
HINSTANCE g_hInst;    // 현재 인스턴스입니다.
HWND      g_hMainWnd; // 메인 윈도우의 핸들입니다.
TCHAR     g_tstrWindowCaption[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
WCHAR     g_tstrWindowClass[MAX_LOADSTRING];   // 기본 창 클래스 이름입니다.

const INT32 CLIENT_WIDTH  = 800;
const INT32 CLIENT_HEIGHT = 600;

//////////////////////////////////////////////////////////////////////////
// 함수 선언부입니다.
HRESULT          InitWindowClass(HINSTANCE hInstance);
HRESULT          InitInstance(HINSTANCE hInstance, INT32 cmdShow);
LRESULT CALLBACK WndProc(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam);

INT32 APIENTRY _tWinMain(_In_     HINSTANCE hInstance,
	                     _In_opt_ HINSTANCE hPrevInstance,
	                     _In_     LPTSTR    lpCmdLine,
	                     _In_     INT32     cmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, g_tstrWindowCaption, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY016DC, g_tstrWindowClass, MAX_LOADSTRING);

	// 윈도우 클래스를 초기화합니다.
	if (FAILED(InitWindowClass(hInstance)))
	{
		ERROR_POPUP("윈도우 클래스를 초기화하지 못했습니다!");
		return FALSE;
	}

	// 응용 프로그램을 초기화합니다.
	if (FAILED(InitInstance(hInstance, cmdShow)))
	{
		ERROR_POPUP("응용 프로그램을 초기화하지 못했습니다!");
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	// GetStockObject()에 적절한 옵션을 주면
	// 그 옵션에 해당되는 GDI 오브젝트를 가져올 수 있습니다.
	// 1회용이 아니라 한번 변경하면 계속 변경됩니다.
	// 하지만 ReleaseDC()를 하면 기본값으로 초기화됩니다.
	//
	// GetStockObject()는 운영체제가 미리 만들어놓은
	// DC를 이용하므로 DeleteObject()는 안해도 됩니다.
	// 참고로 SelectObject()의 반환값은 이전 DC의 속성값입니다.
	// 이 값을 이용하면 이전 속성값으로 복구할 수 있습니다.
	HDC hDC = GetDC(g_hMainWnd);

	HPEN hPen = static_cast<HPEN>(GetStockObject(DC_PEN));
	HPEN hOldPen = nullptr;  // 이전 펜입니다.

	hOldPen = static_cast<HPEN>(SelectObject(hDC, hPen));
	MoveToEx(hDC, 100, 100, nullptr);
	LineTo(hDC, 600, 100);
	
	// 기본 DC의 펜 속성을 변경합니다.
	SetDCPenColor(hDC, RGB(255, 0, 0));

	hOldPen = static_cast<HPEN>(SelectObject(hDC, hPen));
	MoveToEx(hDC, 100, 200, nullptr);
	LineTo(hDC, 600, 200);
	
	// 이전 펜으로 복구합니다.
	// 하지만 기본 DC의 펜 속성을 변경하면 복구되지 않습니다.
	// 기본 DC의 펜 속성을 복구하려면 DC를 해제해야 합니다.
	SelectObject(hDC, hOldPen);
	MoveToEx(hDC, 100, 300, nullptr);
	LineTo(hDC, 600, 300);

	//////////////////////////////////////////////////////////////////////////
	HBRUSH hBrush = static_cast<HBRUSH>(GetStockObject(DC_BRUSH));
	HBRUSH hOldBrush = nullptr;  // 이전 브러시입니다.

	hOldBrush = static_cast<HBRUSH>(SelectObject(hDC, hBrush));
	RECT rect1 = { 30, 30, 80, 80 };
	FillRect(hDC, &rect1, hBrush);

	// 기본 DC의 브러시 속성을 변경합니다.
	SetDCBrushColor(hDC, RGB(255, 0, 0));

	hOldBrush = static_cast<HBRUSH>(SelectObject(hDC, hBrush));
	RECT rect2 = { 630, 30, 680, 80 };
	FillRect(hDC, &rect2, hBrush); // 사각형 영역을 채워줍니다. 테두리가 없습니다.

	// 이전 브러시로 복구합니다.
	// 하지만 기본 DC의 브러시 속성을 변경하면 복구되지 않습니다.
	// 기본 DC의 브러시 속성을 복구하려면 DC를 해제해야 합니다.
	SelectObject(hDC, hOldBrush);
	RECT rect3 = { 430, 430, 480, 480 };
	FillRect(hDC, &rect3, hBrush);

	ReleaseDC(g_hMainWnd, hDC);
	//////////////////////////////////////////////////////////////////////////

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	bool bDrive = true;

	// 기본 메시지 루프입니다.
	while (bDrive)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDrive = false;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return static_cast<INT32>(msg.wParam);
}

HRESULT InitWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = nullptr;
	wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	wcex.lpszMenuName  = nullptr;
	wcex.lpszClassName = g_tstrWindowClass;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (RegisterClassEx(&wcex) == 0)
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT InitInstance(HINSTANCE hInstance, INT32 cmdShow)
{
	g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hMainWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
		g_tstrWindowClass, g_tstrWindowCaption, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CLIENT_WIDTH, CLIENT_HEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	g_hMainWnd = hMainWnd;

	if (hMainWnd == nullptr)
	{
		return E_FAIL;
	}

	ShowWindow(hMainWnd, cmdShow);
	UpdateWindow(hMainWnd);

	return S_OK;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		DEBUG_LOG("윈도우를 생성했습니다.");
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		DEBUG_LOG("윈도우를 닫았습니다.");
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		DEBUG_LOG("윈도우를 폭파시켰습니다.");
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}

	return 0;
}