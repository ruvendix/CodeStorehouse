/*
 * <파일 설명>
 * WIC 비트맵을 변환해보는 예제입니다.
 * 이미지를 변환하려면 수학을 이용해야 하는데 어떤 라이브러리든지 수학을 이용합니다.
 * 변환에는 크기, 이동, 회전이 있는데 이중에서 <회전>이 가장 어렵습니다.
 * 회전은 각도 개념이 들어가기 때문에 삼각함수는 필수로 들어갑니다.
 * 프로그래밍에서는 연산 속도로 인해 행렬 개념을 도입해서 변환 행렬을 이용합니다.
 * 하지만 변환 행렬 같은 개념을 몰라도 이미지를 회전할 수 있습니다.
 * 내부 구현을 몰라도 인터페이스를 이용하면 기능을 사용할 수 있습니다.
 */

// 020. WIC 비트맵 변환.cpp: 응용 프로그램의 진입점을 정의합니다.
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

const INT32 CLIENT_WIDTH = 800;
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
	LoadString(hInstance, IDC_MY020WIC, g_tstrWindowClass, MAX_LOADSTRING);

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
	// WIC 비트맵을 생성해서 Direct2D 비트맵으로 변환하는 과정은
	// 거의 저번과 비슷합니다만 몇 가지 수정되는 부분이 있으니 잘 봐두세요.

	// 압축된 이미지를 비트맵 형식으로 압축을 해제합니다.
	IWICBitmapDecoder* pWICBitmapDecoder = nullptr;
	if (FAILED(g_pWICImagingFactory->CreateDecoderFromFilename(L"link.png",
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

	// 클라이언트 영역과 렌더 타겟 영역에 대한 정리가 필요합니다.
	//
	// 윈도우 응용 프로그램은 프레임 + 메뉴 + 클라이언트로 이루어져있습니다.
	// 윈도우의 전체 크기는 GetWindowRect()로 알아낼 수 있으며 모니터 기준 좌표로 알려줍니다.
	// 클라이언트 영역은 GetClientRect()로 알아낼 수 있으며 프로그램 기준 좌표로 알려줍니다.
	// 따라서 모니터와 클라이언트 좌표는 차이가 있으므로 호환되게 하려면 좌표 변환이 필요합니다.
	// 원리는 모니터 원점으로부터 클라이언트 원점의 차이를 더해주는 겁니다.
	// ScreenToClient()와 ClientToScreen()이 좌표 변환을 해줍니다.
	//
	// 이제 윈도우 응용 프로그램 위에 라이브러리를 덮어 씌우게 되면 별도의 영역이 생깁니다.
	// 즉, 렌더 타겟이 클라이언트 영역으로 설정되고 그 위에 덮어 씌우는 형식입니다.
	// 오브젝트를 렌더링하는 곳은 클라이언트 영역이 맞지만 백 버퍼(Back Buffer)를 이용합니다.
	// 백 버퍼에 먼저 오브젝트를 렌더링하고 프론트 버퍼(화면)에 보여주는 방식입니다.
	// 왜 이 얘기를 하냐면 클라이언트 영역과 렌더 타겟 영역은 따로 운영되기 때문입니다.
	//
	// 클라이언트 영역은 말 그대로 윈도우 응용 프로그램의 영역을 의미하고,
	// 렌더 타겟 영역은 라이브러리가 오브젝트 렌더링을 위한 영역을 의미합니다.
	// 즉, 둘의 크기는 다를 수 있습니다. 이게 정말 중요한 내용이니까 잘 알아두세요.

	// 이미지로부터 크기를 가져옵니다.
	// GetObject()를 이용해서 BITMAP에 정보를 가져오는 것과 비슷합니다.
	UINT32 imageWidth;
	UINT32 imageHeight;
	pWICBitmapFrameDecode->GetSize(&imageWidth, &imageHeight);

	// 렌더 타겟 영역을 이미지 크기로 설정합니다.
	// 이렇게 되면 클라이언트 영역은 (800 X 600)이지만
	// 렌더 타겟 영역은 (이미지 가로 X 이미지 세로)가 됩니다.
	// 즉, 프로그램의 클라이언트 영역은 그대로지만 렌더 타겟 영역이 줄어듭니다.
	// 이렇게 되면 어떻게 될까요? 오브젝트가 확대되어서 렌더링됩니다.
	// 클라이언트 영역의 크기는 일정한데 줄어든 렌더 타겟의 영역을
	// 클라이언트 영역에 강제로 맞춰야 하기 때문에 그런 겁니다.
	g_pD2D1HwndRenderTarget->Resize(D2D1::SizeU(imageWidth, imageHeight));

	// 이미지의 크기를 D2D1 자료형으로 변환합니다.
	D2D1_RECT_F imageRect;
	ZeroMemory(&imageRect, sizeof(imageRect));
	imageRect.right = static_cast<FLOAT>(imageWidth);
	imageRect.bottom = static_cast<FLOAT>(imageHeight);

	// 이미지를 회전할 중심 좌표를 설정합니다.
	// 원래 이렇게 변환 안해도 되는데 D2D1_RECT_F를 사용하기 위해 한번 해봤습니다.
	// 원래는 static_cast<FLOAT>(imageWidth / 2.0f)로 합니다.
	D2D1_POINT_2F rotateCenterPos;
	ZeroMemory(&rotateCenterPos, sizeof(rotateCenterPos));
	rotateCenterPos.x = imageRect.right / 2.0f;
	rotateCenterPos.y = imageRect.bottom / 2.0f;

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
	// 이제는 변환된 Direct2D 비트맵을 변환해서 렌더링하면 됩니다. (라임인가 ㅋㅋ)

	//////////////////////////////////////////////////////////////////////////
	// 비트맵을 변환하는 부분입니다.
	// 렌더링 부분에는 연산 과정을 안 넣는 게 좋습니다.
	// 일반적으로는 렌더링 밖에서 연산을 하고 렌더링에서는 결과값만 이용해요.
	D2D1_RECT_F imagetRect;
	ZeroMemory(&imagetRect, sizeof(imagetRect));
	imagetRect.right = static_cast<FLOAT>(imageWidth);
	imagetRect.bottom = static_cast<FLOAT>(imageHeight);

	// 크기 행렬을 만듭니다.
	// 렌더 타겟 영역을 줄였기 때문에 적절한 크기 조절이 필요합니다.
	D2D1_MATRIX_3X2_F matScale;
	ZeroMemory(&matScale, sizeof(matScale));
	matScale = D2D1::Matrix3x2F::Scale(0.4f, 0.4f);

	// 회전 행렬을 만들기 전에 크기가 60% 줄었으므로
	// 중심 좌표도 60%만큼 줄여야 합니다.
	// 안 그러면 크기가 줄어들기 전의 좌표로 회전하게 됩니다. 이러면 망합니다.
	rotateCenterPos.x /= 2.5f;
	rotateCenterPos.y /= 2.5f;

	// 회전 행렬을 만듭니다.
	D2D1_MATRIX_3X2_F matRotate;
	ZeroMemory(&matRotate, sizeof(matRotate));
	matRotate = D2D1::Matrix3x2F::Rotation(30.0f, rotateCenterPos);

	// 이동 행렬을 만듭니다.
	D2D1_MATRIX_3X2_F matTrans;
	ZeroMemory(&matTrans, sizeof(matTrans));
	matTrans = D2D1::Matrix3x2F::Translation(250.0f, 300.0f);

	// 월드 행렬을 만듭니다.
	// 회전시킨 다음 이동해야 합니다.
	// 이게 자전이고 이 반대는 공전입니다.
	// 행렬이라 곱의 순서가 중요합니다!
	// 변환 행렬의 곱 순서는 (크기 * 자전 * 이동 * 공전 * 부모) 이렇게 됩니다.
	D2D1_MATRIX_3X2_F matWorld;
	ZeroMemory(&matWorld, sizeof(matWorld));
	matWorld = matScale * matRotate * matTrans;

	//////////////////////////////////////////////////////////////////////////
	// 렌더링 부분입니다.

	// 렌더링 시작을 알립니다.
	g_pD2D1HwndRenderTarget->BeginDraw();

	// 렌더 타겟의 배경을 설정한 색으로 지워줍니다.
	g_pD2D1HwndRenderTarget->Clear(D2D1::ColorF(0.0f, 0.8f, 0.6f, 0.5f));

	// 원본 Direct2D 비트맵을 렌더링합니다.
	g_pD2D1HwndRenderTarget->DrawBitmap(pD2D1Bitmap, &imagetRect);

	// 변환된 Direct2D 비트맵을 회전시킵니다.
	g_pD2D1HwndRenderTarget->SetTransform(matWorld);

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