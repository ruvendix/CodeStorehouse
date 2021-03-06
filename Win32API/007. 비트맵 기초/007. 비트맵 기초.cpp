/*
 * <파일 설명>
 * 비트맵(Bitamp) 기초 예제입니다.
 * 비트맵이란 비트들이 나열된 모습이 지도 같다고 해서 붙은 이름입니다. (진짜 그렇게 보임)
 * 비트들이 나열된 형식을 비트 패턴(Bit Pattern)이라고 하는데 별로 중요한 건 아닙니다.
 * 중요한 건 DDB(Device Dependant Bitmap)와 DIB(Device Independant Bitmap)입니다.
 * DDB는 그래픽 카드에 종속적이므로 출력할 수 있는 형식이 정해져있고 그에 따라 처리해야 합니다.
 * 하지만 DIB는 그래픽 카드에 관계 없이 출력할 수 있습니다. 즉, 내부적으로 변환 작업을 합니다.
 * 변환 작업으로 인해 DIB는 DDB보다 처리 속도가 느리지만 편리한 건 DIB가 최고입니다.
 */

// 007. 비트맵 기초.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////
// 매크로 상수 입니다.
#define MAX_LOADSTRING 256
#define MAX_STRING     256

//////////////////////////////////////////////////////////////////////////
// 매크로 함수입니다.
#define ERROR_POPUP(str)  MessageBox(nullptr, _T(str), _T("오류 팝업창"), MB_ICONERROR)
#define NORMAL_POPUP(str) MessageBox(nullptr, str, _T("기본 팝업창"), MB_OK)
#define DEBUG_LOG(str)   OutputDebugString(_T(str)); OutputDebugString(_T("\n"))

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
    ::LoadString(hInstance, IDC_MY007, g_tstrWindowClass, MAX_LOADSTRING);
	
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
	// 비트맵 기초 예제입니다.
	//
	// 1. 픽셀(Pixel)의 개념을 이해합니다.
	//    픽셀은 여러 형식이 있는데 과거에는
	//    8비트, 16비트(하이 컬러), 24비트(트루 컬러)를 많이 사용했습니다.
	//    요즘은 알파 채널(Alpha Channel)이 포함된 32비트를 많이 사용합니다.
	//
	// 32비트입니다. 순서대로 A, R, G, B입니다.
	// 포인터로도 접근할 수 있는데 비주얼 스튜디오 2017에서는 기본으로 막는 것 같습니다.
	// 그래서 시프트 연산자를 이용했습니다.
	DWORD dw32BitPixel = 0xFF112233;

	TCHAR tstrBuffer[MAX_STRING];
	_snwprintf_s(tstrBuffer, _countof(tstrBuffer), L"알파값 : %03u", static_cast<BYTE>(dw32BitPixel >> 24));
	NORMAL_POPUP(tstrBuffer);

	_snwprintf_s(tstrBuffer, _countof(tstrBuffer), L"빨강값 : %03d", static_cast<BYTE>(dw32BitPixel >> 16));
	NORMAL_POPUP(tstrBuffer);

	_snwprintf_s(tstrBuffer, _countof(tstrBuffer), L"초록값 : %03d", static_cast<BYTE>(dw32BitPixel >> 8));
	NORMAL_POPUP(tstrBuffer);

	_snwprintf_s(tstrBuffer, _countof(tstrBuffer), L"파랑값 : %03d", static_cast<BYTE>(dw32BitPixel));
	NORMAL_POPUP(tstrBuffer);

	//////////////////////////////////////////////////////////////////////////
	// 2. 비트맵 생성하기
	//
	// 비트맵은 이미지 파일만 존재하는 게 아니라 메모리에도 만들 수 있습니다.
	// 비트맵을 만들 때는 CreateBitmap()을 이용합니다.
	// CreateBitmap()은 DDB를 만드는 함수입니다.
	//
	// DDB를 좀 더 편하게 만들기 위해 현재 DC가 지원하는 픽셀 형식을 알아냅니다.
	HDC hDC = GetDC(g_hMainWnd);
	INT32 pixelFormat = GetDeviceCaps(hDC, BITSPIXEL);
	ReleaseDC(g_hMainWnd, hDC); // 사용한 DC는 해제해줍니다.
	
	// 비트 패턴을 할당합니다.
	// 일반적으로 이미지 파일은 가로와 세로가 4배수입니다.
	DWORD* pBitPattern = new DWORD[32 * 32];
	
	for (INT32 i = 0; i < 32; ++i)
	{
		for (INT32 j = 0; j < 32; ++j)
		{
			pBitPattern[i * 32 + j] = 0xFF112233;
		}
	}

	// CreateBimap()의 매개변수는 다음과 같습니다.
	// 가로, 세로, 플레인 수(1로 설정), 픽셀 형식, 비트 패턴
	HBITMAP hBitMap = CreateBitmap(32, 32, 1, 32, pBitPattern);

	BITMAP bitmap;
	GetObject(hBitMap, sizeof(bitmap), &bitmap);
	_snwprintf_s(tstrBuffer, _countof(tstrBuffer),
		L"비트맵 가로 : %d | 비트맵 세로 : %d", bitmap.bmWidth, bitmap.bmHeight);
	NORMAL_POPUP(tstrBuffer);

	delete[] pBitPattern;
	DeleteObject(hBitMap); // 생성한 오브젝트를 파괴합니다.

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

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY007));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = g_tstrWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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