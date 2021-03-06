/*
 * <파일 설명>
 * 펜 예제입니다.
 * 펜은 DC의 속성값 중 하나입니다.
 * 펜 자체는 GDI 오브젝트로 분류됩니다.
 */

// 013. 펜.cpp: 응용 프로그램의 진입점을 정의합니다.
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
	::LoadString(hInstance, IDS_APP_TITLE, g_tstrWindowCaption, MAX_LOADSTRING);
	::LoadString(hInstance, IDC_MY013, g_tstrWindowClass, MAX_LOADSTRING);

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
	// 펜 예제입니다.
	// 펜을 여러 개 만들고 스타일을 설정해서 어떻게 되는지 알아봅니다.
	HDC hDC = GetDC(g_hMainWnd);

	// 기본 펜입니다. 기본 색은 검정색입니다.
	HPEN hPen = static_cast<HPEN>(GetCurrentObject(hDC, OBJ_PEN));
	
	POINT pos2D = { 100, 100 };
	MoveToEx(hDC, pos2D.x, pos2D.y, nullptr); // 좌표에 점을 찍습니다.
	LineTo(hDC, pos2D.x + 300, pos2D.y); // 선을 그립니다.

	// 기본 펜의 색상은 검정색이라서 현재 배경에서는 잘 안 보입니다.
	// 펜의 색상 변경과 동시에 다양한 펜 스타일을 알아볼게요.

	//////////////////////////////////////////////////////////////////////////

	// 펜의 굵기가 너무 굵으면 일부 스타일은 기본 형식처럼 출력됩니다.
	INT32 penStyleTable[5] =
	{
		PS_SOLID,
		PS_DASH,
		PS_DOT,
		PS_DASHDOT,
		PS_DASHDOTDOT
	};

	// DC의 배경 모드를 투명하게 변경합니다.
	// 점선 펜의 경우 뒷 배경이 보이면 안되니까요.
	SetBkMode(hDC, TRANSPARENT);

	for (INT32 i = 0; i < 5; ++i)
	{
		hPen = CreatePen(penStyleTable[i], 1, RGB(255, 255, 255));
		SelectObject(hDC, hPen);
		MoveToEx(hDC, pos2D.x, pos2D.y + (30 * i), nullptr);
		LineTo(hDC, pos2D.x + 300, pos2D.y + (30 * i));
	}
	DeleteObject(hPen);

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