/*
 * <파일 설명>
 * DDB를 생성하고 비트 패턴을 변경해서 프로그램에 출력해보는 예제입니다.
 * 비트맵 기초는 물론이고, 좌표에 대한 개념이 없으면 이해하기 어려운 예제입니다.
 * DDB를 직접 사용해보면 왜 DIB가 편하고 장치 독립성이 좋은지를 깨닫게 됩니다.
 */

 // 010. 비트 패턴 응용.cpp: 응용 프로그램의 진입점을 정의합니다.
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
	::LoadString(hInstance, IDC_MY010, g_tstrWindowClass, MAX_LOADSTRING);

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
	// DDB를 생성해서 비트 패턴을 변경해보고 출력해봅니다.
	// 생성된 비트맵에 사각형을 출력해볼 건데 위에서 말한 대로 기초 개념이 없으면
	// 이해하기 쉽지 않은 예제입니다. 이해가 안되면 반복해서 보는 걸 추천합니다.
	//
	HBITMAP hBitmap = CreateBitmap(300, 300, 1, 32, nullptr);

	DWORD* pBitPattern = new DWORD[300 * 300];
	GetBitmapBits(hBitmap, 300 * 300 * 32 / 8, pBitPattern);

	// 비트 패턴을 설정합니다.
	// 사각형을 그리고 내부를 채우려면 총 5가지의 과정이 필요합니다.
	// 좀 더 머리를 쓰면 더 좋은 방법도 있지만 원리를 이해하는 게 중요합니다.
	// 각 과정은 위쪽, 왼쪽, 아래쪽, 오른쪽, 채우기 이렇게 됩니다.
	// 각 과정을 함수로 만들어도 되고 하나로 합해서 만들어도 됩니다.
	// 저는 함수로 따로 만들지는 않고 한번에 작성하겠습니다.
	// 비트맵의 크기가 300 * 300이니까 (100, 100) ~ (200, 200)에 사각형을 그려볼게요.

	// 비트 패턴 위치를 옮겨다닐 포인터입니다.
	DWORD* pBitPos = nullptr;

	// 사각형의 위치는 (왼쪽 위)와 (오른쪽 아래)로 구분되는데
	// (왼쪽 위)의 좌표를 (SX, SY)라 하고
	// (오른쪽 아래)의 좌표를 (EX, EY)라 할게요.
	// Start와 End의 약자입니다.
	const INT32 SX = 100;
	const INT32 EX = 200;
	const INT32 SY = 100;
	const INT32 EY = 200;

	//////////////////////////////////////////////////////////////////////////
	// 1. 위쪽
	// 시작 위치는 SX + (SY * 300)입니다.
	// DWORD는 4바이트이므로 + 1을 할 때마다 4바이트씩 뜁니다.
	pBitPos = pBitPattern + SX + (SY * 300);
	for (INT32 i = 0; i < EX - SX; ++i)
	{
		// *(pBitPos + 1)은 *pBitPos++ 이것과 같습니다.
		// 픽셀 형식은 순서대로 Alpha, Red, Green, Blue입니다.
		*(pBitPos + i) = 0xFFFF00FF;
	}

	// 여기까지 그리면 아래처럼 됩니다.
	// ---------- 

	//////////////////////////////////////////////////////////////////////////
	// 2. 아래
	// 시작 위치는 SX + ((EY - 1) * 300)입니다.
	// SY가 3이고 EY가 6이면 높이는 6 - 3 = 3이 되지만
	// 좌표로 따지면 3, 4, 5가 되므로 끝 좌표에서 1을 빼줘야 합니다.
	// 왜 이런 경우가 생기냐면 사각형에 테두리가 존재하기 때문입니다.
	// 테두리 개념을 무시하고 좌표 자체로 높이를 설정할 수도 있습니다.
	// 그냥 만드는 사람 맘이죠 뭐 ㅋㅋㅋ
	pBitPos = pBitPattern + SX + ((EY - 1) * 300);
	for (INT32 i = 0; i < EX - SX; ++i)
	{
		// *(pBitPos + 1)은 *pBitPos++ 이것과 같습니다.
		// 픽셀 형식은 순서대로 Alpha, Red, Green, Blue입니다.
		*(pBitPos + i) = 0xFFFF00FF;
	}

	// 여기까지 그리면 아래처럼 됩니다.
	// ---------- 
	//
	//
	//
	// ----------

	//////////////////////////////////////////////////////////////////////////
	// 3. 왼쪽
	// 시작 위치는 SX + (SY * 300)입니다.
	// 위쪽과 시작 위치는 같지만 아래쪽으로 이동해야 합니다.
	// 아래쪽으로 이동하기 위해서는 Y에 300씩 더해야 합니다.
	pBitPos = pBitPattern + SX + (SY * 300);
	for (INT32 i = 0; i < EY - SY; ++i)
	{
		*(pBitPos + (i * 300)) = 0xFFFF00FF;
	}

	// 여기까지 그리면 아래처럼 됩니다.
	// ----------
	// |
	// |
	// |
	// ----------

	//////////////////////////////////////////////////////////////////////////
	// 4. 오른쪽
	// 시작 위치는 (EX - 1) + (SY * 300)입니다.
	// 아래쪽과 마찬가지로 좌표 차이는 길이입니다.
	// SX가 2이고 EX가 5이면 5 - 2 = 3이 되지만
	// 좌표로 따지면 2, 3, 4가 되므로 끝 좌표에서 1을 빼줘야 합니다.
	// 이 역시도 테두리 개념 때문에 그렇습니다.
	// 여기에 추가로 아래쪽으로 이동하기 위해서는 Y에 300씩 더해야 합니다.
	pBitPos = pBitPattern + (EX - 1) + (SY * 300);
	for (INT32 i = 0; i < EY - SY; ++i)
	{
		*(pBitPos + (i * 300)) = 0xFFFF00FF;
	}

	// 여기까지 그리면 아래처럼 됩니다.
	// ----------
	// |        |
	// |        |
	// |        |
	// ----------

	//////////////////////////////////////////////////////////////////////////
	// 5. 채우기
	// 시작 위치는 테두리를 제외한 위치가 됩니다.
	// 계산해보면 (SX + 1) + ((SY + 1) * 300)이 됩니다.
	// 하지만 아래쪽으로도 이동해야 하므로 중복 for문이 됩니다.
	for (INT32 i = 0; i < EY - SY - 2; ++i) // 테두리 제외
	{
		pBitPos = pBitPattern + (SX + 1) + ((SY + i + 1) * 300);
		
		for (INT32 j = 0; j < EX - SX - 2; ++j)
		{
			*(pBitPos + j) = 0xFF00FFFF;
		}
	}

	// 여기까지 그리면 아래처럼 됩니다.
	// ----------
	// |########|
	// |########|
	// |########|
	// ----------

	//////////////////////////////////////////////////////////////////////////
	// 이제 다 그렸으니 출력해볼게요.
	// 출력하기 전에 설정한 비트 패턴을 비트맵에 적용해야 합니다.
	// 적용된 비트 패턴은 더 이상 쓸 일이 없으므로 해제해도 됩니다.
	SetBitmapBits(hBitmap, 300 * 300 * 32 / 8, pBitPattern);
	SAFE_DELETE_ARRAY(pBitPattern);
	
	// 생성한 비트맵을 메모리 DC에 옮겨야 합니다.
	// 왜냐하면 화면 DC에서는 바로 비트맵을 출력할 수 없기 때문입니다.
	// 그 이유는 화면 DC가 출력하는 기본 정보를 유지해야 하기 때문입니다.
	// 기본 정보를 유지해야 한다는 건 장치와 직접 연결되어있따는 뜻이기도 합니다.
	// 이런 경우는 거의 비트맵이 유일한데 비트맵은 메모리 DC를 경유해서 출력해야 합니다.
	// 이 기술을 이용하면 깜빡임을 없애주는 더블 버퍼링(Double Buffering)을 구현할 수 있어요.
	// 즉, 화면 DC에 비트맵이 출력되고 있을 때 메모리 DC에서는 새로운 비트맵을 출력하는 거죠.
	HDC hMemDC = CreateCompatibleDC(GetDC(g_hMainWnd));
	SelectObject(hMemDC, hBitmap);
	DeleteObject(hBitmap); // 연결된 오브젝트는 더 이상 쓸 일이 없습니다.

	// BitBlt()은 비트맵을 출력해주는 함수입니다.
	// Bit Block Transfer의 약자인데 비트를 블록 단위로 전송해주는 함수라는 거죠.
	// 비트맵은 비트 패턴으로 이루어져있기 때문에 비트를 전송해주면 그게 곧 이미지 출력입니다.
	// DIB를 출력할 때 많이 사용하지만 DDB도 출력할 수 있습니다.
	// 내부적으로 DDB가 DIB로 변경됩니다. 즉, 장치 독립적으로 작동되는 함수입니다.
	//
	// 목적 DC, 출력할 X위치, 출력할 Y위치, 출력할 가로 크기, 출력할 세로 크기,
	// 원본 DC, 복사할 X위치, 복사할 Y위치, 전송 방식
	//
	// 이렇게 넣어주면 됩니다.
	HDC hDC = GetDC(g_hMainWnd);
	BitBlt(hDC, 100, 100, 300, 300, hMemDC, 0, 0, SRCCOPY);

	ReleaseDC(g_hMainWnd, hDC);
	ReleaseDC(g_hMainWnd, hMemDC);
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