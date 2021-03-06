/*
 * <파일 설명>
 * 타이머 예제입니다.
 * WIN32 API에서 시간 관련 함수가 몇 가지 있는데 여기에서는 타이머만 사용합니다.
 * 타이머는 주기적으로 일정한 시간 간격이 되면 함수를 호출합니다. 즉, 콜백입니다.
 */

// 012. 타이머.cpp: 응용 프로그램의 진입점을 정의합니다.
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

INT32 g_firstValue;
INT32 g_secondValue;

//////////////////////////////////////////////////////////////////////////
// 함수 선언부입니다.
HRESULT          InitWindowClass(HINSTANCE hInstance);
HRESULT          InitInstance(HINSTANCE hInstance, INT32 cmdShow);
LRESULT CALLBACK WndProc(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void CALLBACK    TimeProc(HWND hMainWnd, UINT msg, UINT_PTR, DWORD);

INT32 APIENTRY _tWinMain(_In_     HINSTANCE hInstance,
	                     _In_opt_ HINSTANCE hPrevInstance,
	                     _In_     LPTSTR    lpCmdLine,
	                     _In_     INT32     cmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	::LoadString(hInstance, IDS_APP_TITLE, g_tstrWindowCaption, MAX_LOADSTRING);
	::LoadString(hInstance, IDC_MY012, g_tstrWindowClass, MAX_LOADSTRING);

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
	// 타이머는 콜백을 이용하기 때문에 아래 부분도 잘 봐둬야 합니다.
	// 4번째 인자에 nullptr을 넣으면 윈도우 프로시저에서 WM_TIMER가 발생합니다.
	// 이 메시지를 처리해도 되지만 일반적으로는 콜백을 사용합니다.
	SetTimer(g_hMainWnd, 1, 1000, TimeProc);
	SetTimer(g_hMainWnd, 2, 3000, TimeProc);

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

	// 타이머를 제거합니다.
	KillTimer(g_hMainWnd, 1);
	KillTimer(g_hMainWnd, 2);

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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);

		TCHAR tstrBuffer[MAX_STRING];
		_snwprintf_s(tstrBuffer, _countof(tstrBuffer),
			L"첫 번째 값 : %d | 두 번째 값 : %d", g_firstValue, g_secondValue);
		TextOut(hDC, 200, 200, tstrBuffer, _tcslen(tstrBuffer));

		EndPaint(hWnd, &ps);
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

// 타이머가 주기적으로 호출하는 함수입니다.
// 인자는 순서대로 윈도우 핸들, 메시지, 타이머 아이디, 프로그램을 실행한 뒤의 경과 시간입니다.
void CALLBACK TimeProc(HWND hMainWnd, UINT msg, UINT_PTR timerID, DWORD dwElapsedTime)
{
	switch (timerID)
	{
        case 1:
        {
			++g_firstValue;
            break;
        }
        case 2:
        {
			++g_secondValue;
            break;
        }
	}

	// 현재 출력된 클라이언트 영역을 무효 영역으로 설정합니다.
	// 출력된 영역이 무효화되었으므로 다시 출력해야 합니다.
	// 이때 WM_PAINT 메시지가 발생하므로 출력을 갱신할 수 있습니다.
	// 반대 함수는 ValidateRect()가 있습니다.
	InvalidateRect(hMainWnd, nullptr, TRUE);
}