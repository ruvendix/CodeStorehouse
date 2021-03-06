/*
 * <파일 설명>
 * Windows XP부터 지원하는 GDI+ 예제입니다.
 * GDI+는 GDI를 보완해서 나온 기술입니다.
 * GDI+는 좀 더 고사양의 그래픽 카드에 대응할 수 있습니다.
 */																	  

// 017. GDI+.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "resource.h"

#include <gdiplus.h>            // GDI+ 헤더 파일입니다.
#pragma comment(lib, "gdiplus") // GDI+ 라이브러리 링크입니다.

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

#define SAFE_DELETE(ptr)\
if (ptr)\
{\
    delete ptr;\
    ptr = nullptr;\
}

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
	LoadString(hInstance, IDC_MY017GDI, g_tstrWindowClass, MAX_LOADSTRING);

	// ULONG_PTR은 32비트와 64비트에 따라 자료형이 변합니다.
	// 32비트에서는 DWORD(unsigned long)로 동작하고,
	// 64비트에서는 unsigned __int64로 동작합니다.
	ULONG_PTR GDIplusToken;

	// GDI+를 초기화할 때 사용되는 정보입니다.
	// GDI+는 Gdiplus라는 네임 스페이스를 사용합니다.
	Gdiplus::GdiplusStartupInput GDIplusInitInfo;

	// GDI+를 초기화합니다.
	// 그래픽 카드가 GDI+를 지원해야 사용할 수 있습니다.
	if (Gdiplus::GdiplusStartup(&GDIplusToken,
		&GDIplusInitInfo, nullptr) != Gdiplus::Ok)
	{
		ERROR_POPUP("GDI+를 초기화하지 못했습니다!");
		return FALSE;
	}

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
	// GDI+를 사용하기 위해서는 GDI+ 전용 그래픽 객체가 필요합니다.
	// GDI+를 이용해서 일반선과 Anti Aliasing(안티 에일리어싱, 계단현상 방지)이
	// 적용된 선을 그려볼게요. GDI+에서는 Alpha값도 설정 가능합니다.
	HDC hDC = GetDC(g_hMainWnd);
	Gdiplus::Graphics* pGDIgraphics =
		new Gdiplus::Graphics(hDC); // DC와 윈도우 핸들 둘 다 가능합니다.
	
	Gdiplus::Color color(128, 255, 0, 0);
	Gdiplus::Pen* pPen = new Gdiplus::Pen(color, 3.0f);

	// 일반선을 그립니다.
	pGDIgraphics->SetSmoothingMode(Gdiplus::SmoothingModeInvalid);
	pGDIgraphics->DrawLine(pPen, 100, 100, 600, 200);

	// Anti Aliasing이 적용된 선을 그립니다.
	pGDIgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	pGDIgraphics->DrawLine(pPen, 100, 300, 600, 400);
	
	SAFE_DELETE(pPen);
	SAFE_DELETE(pGDIgraphics);
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

	// GDI+를 해제합니다.
	Gdiplus::GdiplusShutdown(GDIplusToken);

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