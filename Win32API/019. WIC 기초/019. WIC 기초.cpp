/*
 * <파일 설명>
 * WIC(Windows Imaging Component) 기초 예제입니다.
 * WIC는 이미지를 변환 및 저장할 수 있는 윈도우 응용체제의 컴포넌트입니다.
 * Direct2D는 WIC를 사용할 수 있는데 주로 이미지를 다룰 때 사용합니다.
 * 코드 자체가 좀 복잡한데 외우는 게 아니라 사용 방법만 보면 됩니다.
 */

// 019. WIC 기초.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "resource.h"

#include <d2d1.h>            // Direct2D 헤더 파일입니다.
#pragma comment(lib, "D2D1") // GDI+ 라이브러리 링크입니다.

#include <wincodec.h> // WIC 헤더 파일입니다.

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

// WIC의 통합 객체 포인터입니다.
IWICImagingFactory* g_pWICImagingFactory;

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
	LoadString(hInstance, IDC_MY019WIC, g_tstrWindowClass, MAX_LOADSTRING);

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

	// WIC의 Factory 객체를 생성합니다.
	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pWICImagingFactory))))
	{
		ERROR_POPUP("WIC Factory 객체를 생성하지 못했습니다!");
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
	// Direct2D와 WIC png 이미지를 출력해볼 겁니다.
	// 저번 예제와 중복되는 부분이 있으므로 잘 봐두세요.
	// 사용 방법을 외우는 게 아니라 대충 어떻게 사용되는지만 알면 됩니다.

	// 압축된 이미지를 비트맵 형식으로 압축을 해제합니다.
	IWICBitmapDecoder* pWICBitmapDecoder = nullptr;
	if (FAILED(g_pWICImagingFactory->CreateDecoderFromFilename(L"dark_souls3.png",
		nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pWICBitmapDecoder)))
	{
		ERROR_POPUP("이미지를 불러오지 못했습니다!");
		return FALSE;
	}

	// 사용할 이미지를 선택합니다.
	// 일반적으로 이미지 파일에는 하나의 이미지만 들어있지만
	// 이미지 파일 안에 여러 개의 이미지가 들어있는 경우도 있습니다.
	// 예제에서는 첫 번째 이미지를 선택합니다.
	IWICBitmapFrameDecode* pWICBitmapFrameDecode = nullptr;
	if (FAILED(pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrameDecode)))
	{
		ERROR_POPUP("이미지를 선택하지 못했습니다!");
		return FALSE;
	}

	// WIC를 Direct2D에서 사용 가능하도록 변환해줍니다.
	// WIC 형식의 렌더 타겟이 있으면 바로 사용 가능하지만
	// 지금은 Direct2D 렌더 타겟을 이용해볼게요.
	IWICFormatConverter* pWICFormatConverter = nullptr; // 변환 객체 포인터 생성
	if (FAILED(g_pWICImagingFactory->CreateFormatConverter(&pWICFormatConverter)))
	{
		ERROR_POPUP("변환 객체를 생성하지 못했습니다!");
		return FALSE;
	}
	
	if (FAILED(pWICFormatConverter->Initialize(pWICBitmapFrameDecode,
		GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, nullptr, 0.0f,
		WICBitmapPaletteTypeCustom)))
	{
		ERROR_POPUP("변환 객체를 초기화하지 못했습니다!");
		return FALSE;
	}

	// Direct2D와 연결시켜줍니다.
	ID2D1Bitmap* pD2D1Bitmap = nullptr;
	if (FAILED(g_pD2D1HwndRenderTarget->CreateBitmapFromWicBitmap(pWICFormatConverter,
		nullptr, &pD2D1Bitmap)))
	{
		ERROR_POPUP("WIC 비트맵 객체를 Direct2D 비트맵 객체로 변환하지 못했습니다!");
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	// 여기까지가 WIC 비트맵을 생성해서 Direct2D 비트맵으로 변환하는 과정입니다.
	// 이제는 변환된 Direct2D 비트맵을 렌더링하면 됩니다.
	RECT clientRect;
	ZeroMemory(&clientRect, sizeof(clientRect));
	GetClientRect(g_hMainWnd, &clientRect);

	D2D1_RECT_F imagetRect;
	ZeroMemory(&imagetRect, sizeof(imagetRect));

	// 렌더링할 이미지 영역을 클라이언트 영역으로 설정합니다.
	imagetRect.right  = static_cast<FLOAT>(clientRect.right);
	imagetRect.bottom = static_cast<FLOAT>(clientRect.bottom);

	// 렌더링 시작을 알립니다.
	g_pD2D1HwndRenderTarget->BeginDraw();

	// 렌더 타겟의 배경을 설정한 색으로 지워줍니다.
	g_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(0.0f, 0.8f, 0.6f, 0.5f));

	// 변환된 Direct2D 비트맵을 렌더링합니다.
	g_pD2D1HwndRenderTarget->DrawBitmap(pD2D1Bitmap, &imagetRect);

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

	// 사용한 지역 객체를 해제합니다.
	SAFE_RELEASE(pD2D1Bitmap);
	SAFE_RELEASE(pWICFormatConverter);
	SAFE_RELEASE(pWICBitmapFrameDecode);
	SAFE_RELEASE(pWICBitmapDecoder);

	// 사용한 전역 객체를 해제합니다.
	SAFE_RELEASE(g_pWICImagingFactory);
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