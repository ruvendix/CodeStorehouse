/*
 * <파일 설명>
 * Direct2D 예제입니다.
 * Direct2D는 Windows Vista 때부터 지원하는 라이브러리입니다.
 * GDI+는 원격 시스템에서 GDI처럼 출력되는 단점이 있었는데
 * Direct2D에서는 그 단점을 보완했습니다.
 * 이름을 보면 알겠지만 DirectX를 이용합니다.
 */

// 018. Direct2D.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "resource.h"

#include <d2d1.h>               // Direct2D 헤더 파일입니다.
#pragma comment(lib, "D2D1") // GDI+ 라이브러리 링크입니다.

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

#define SAFE_RELEASE(ptr)\
if (ptr)\
{\
    ptr->Release();\
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

// Direct2D의 통합 객체 포인터입니다.
ID2D1Factory* g_pD2D1Factory;

// 윈도우 핸들을 이용해서 클라이언트 영역에 오브젝트를 렌더링할 객체 포인터입니다.
ID2D1HwndRenderTarget* g_pD2D1HwndRenderTarget;

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
	LoadString(hInstance, IDC_MY018DIRECT2D, g_tstrWindowClass, MAX_LOADSTRING);

	// Direct2D는 COM(Component Object Model)을 이용하기 때문에
	// COM을 사용할 수 있도록 초기화해줘야 합니다.
	// COM이란 바이너리 코드 수준의 인터페이스 규약을 말하는데
	// C, C++, JAVA 등에 관계 없이 인터페이스를 사용하기 위해서 등장한 기술입니다.
	
	// COM을 사용할 수 있도록 초기화합니다.
	if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
	{
		ERROR_POPUP("COM을 초기화하지 못했습니다!");
		return FALSE;
	}

	// Direct2D의 Factory 객체를 생성합니다.
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2D1Factory)))
	{
		ERROR_POPUP("Direct2D Factory 객체를 생성하지 못했습니다!");
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
	// Direct2D는 DirectX와 렌더링 과정이 비슷합니다.
	// 먼저 배경을 채우고 그 위에 오브젝트를 렌더링합니다.
	// 차이가 있다면 BeginDraw() 다음에 Clear()를 호출해야 합니다.
	// 지금은 좀 어렵겠지만 몇 번 해보면 DirectX도 쉽게 익힐 수 있을 겁니다.

	// 렌더링 시작을 알립니다.
	g_pD2D1HwndRenderTarget->BeginDraw();

	// 렌더 타겟의 배경을 설정한 색으로 지워줍니다.
	g_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(0.0f, 0.8f, 0.6f, 0.5f));

	// 브러시를 생성합니다.
	ID2D1SolidColorBrush* pSolidBrush = nullptr;
	g_pD2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.3f, 0.2f, 0.6f, 0.7f), &pSolidBrush);

	D2D1_ELLIPSE ellipse;
	ZeroMemory(&ellipse, sizeof(ellipse));

	// 원의 중심 좌표를 설정합니다.
	ellipse.point.x = 200.0f;
	ellipse.point.y = 200.0f;

	// 원의 x축 반지름 길이를 설정합니다.
	ellipse.radiusX = 100.0f;

	// 원의 y축 반지름 길이를 설정합니다.
	ellipse.radiusY = 80.0f;

	// 설정한 원을 렌더링합니다.
	g_pD2D1HwndRenderTarget->FillEllipse(ellipse, pSolidBrush); // 내부도 채웁니다.
	
	ellipse.point.x = 600.0f;
	ellipse.point.y = 200.0f;
	g_pD2D1HwndRenderTarget->DrawEllipse(ellipse, pSolidBrush); // 선만 그립니다.

	SAFE_RELEASE(pSolidBrush);

	// 렌더링 종료를 알립니다.
	g_pD2D1HwndRenderTarget->EndDraw();

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

	SAFE_RELEASE(g_pD2D1Factory);

	// COM을 해제합니다.
	CoUninitialize();

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
		RECT clientRect;
		ZeroMemory(&clientRect, sizeof(clientRect));
		GetClientRect(hWnd, &clientRect);

		// Direct2D 렌더 타겟 객체는 윈도우가 생성된 뒤에 생성해야 합니다.
		// 생성하는 과정이 조금 복잡하지만 한번 생성해놓으면 더 이상 DC를
		// 이용하지 않아도 됩니다. 생성된 객체로 렌더링하면 됩니다.
		if (FAILED(g_pD2D1Factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clientRect.right, clientRect.bottom)),
			&g_pD2D1HwndRenderTarget)))
		{
			ERROR_POPUP("Direct2D 렌더 타겟 객체를 생성하지 못했습니다!");
		}

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
		SAFE_RELEASE(g_pD2D1HwndRenderTarget); // 렌더 타겟 객체를 해제합니다.
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