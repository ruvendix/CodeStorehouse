/*
 * <파일 설명>
 * 비트맵 파일을 출력해보는 예제입니다.
 * DIB를 사용하므로 픽셀 형식은 따지지 않아도 됩니다.
 * 비트맵 파일을 출력할 줄 알면 좀 더 다양한 프로그래밍을 할 수 있습니다.
 */

// 011. 비트맵 파일 출력.cpp: 응용 프로그램의 진입점을 정의합니다.
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
	::LoadString(hInstance, IDC_MY011, g_tstrWindowClass, MAX_LOADSTRING);

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
	// 비트맵 파일을 읽어서 클라이언트 영역에 출력합니다.
	// DIB를 출력할 것이므로 생각보다는 어렵지 않습니다.
	// DC에 대한 개념과 비트맵 기초 개념만 있으면 쉽게 이해할 수 있습니다.
	// 이미지 파일 경로는 프로젝트 경로를 기준으로 합니다.
	// LoadImage()는 보통 이렇게 사용되므로 자세한 사항은 MSDN을 참고해주세요.
	HBITMAP hBitmap =
		static_cast<HBITMAP>(LoadImage(hInstance, _T("dark_souls3.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	
	HDC hDC    = GetDC(g_hMainWnd);
	HDC hMemDC = CreateCompatibleDC(hDC);

	SelectObject(hMemDC, hBitmap);
	DeleteObject(hBitmap);

	BITMAP bitmap;
	GetObject(hBitmap, sizeof(bitmap), &bitmap);

	BitBlt(hDC, 100, 100, bitmap.bmWidth,
		bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);

	ReleaseDC(g_hMainWnd, hDC);
	DeleteDC(hMemDC);
	
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