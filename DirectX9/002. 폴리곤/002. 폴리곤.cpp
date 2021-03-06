/*
 * <파일 설명>
 * DirectX9으로 폴리곤(Polygon)을 렌더링합니다.
 * 폴리곤은 정점(Vertex) 3개로 이루어진 다각형을 의미합니다.
 * DirectX의 기본 폴리곤은 삼각형(Triangle)입니다.
 * 우리가 눈으로 보는 모든 3D 모델은 폴리곤으로 이루어져있습니다.
 * 정점에 셰이더(Shader) 효과를 주면 다양한 표현이 가능합니다.
 * 셰이더는 나중에 알아보겠습니다.
 */

// 002. 폴리곤.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "002. 폴리곤.h"

// DirectX9 라이브러리 연결입니다.
// 여기서 코드로 넣어도 되고 프로젝트 설정의 추가 종속성에 넣어도 됩니다.
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define MAX_LOADSTRING 256

// 전역 변수:
HINSTANCE g_hInst;                          // 현재 인스턴스입니다.
HWND      g_hWnd;                           // 메인 윈도우 핸들입니다.
TCHAR     g_strCaption[MAX_LOADSTRING];     // 제목 표시줄 텍스트입니다.
TCHAR     g_strWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

const INT32 CLIENT_WIDTH  = 800;
const INT32 CLIENT_HEIGHT = 600;

LPDIRECT3D9       g_pD3DDevice9; // D3D 디바이스 객체 포인터입니다.
LPDIRECT3DDEVICE9 g_pDevice9;    // 디바이스 객체 포인터입니다. 렌더링 작업은 이걸 이용합니다.

//////////////////////////////////////////////////////////////////////////
// 매크로 함수입니다.

#define SAFE_DELETE(ptr)\
if (ptr)\
{\
    delete ptr;\
    ptr = nullptr;\
}

#define SAFE_RELEASE(ptr)\
if (ptr)\
{\
    ptr->Release();\
    ptr = nullptr;\
}

#define MSGBOX_ERR(strError) MessageBox(nullptr, _T(strError), _T("오류 안내"), MB_ICONERROR)

//////////////////////////////////////////////////////////////////////////
// 매크로 상수입니다.

// 정점 형식을 설정합니다.
// 지금은 동차 좌표를 사용하므로 D3DFVF_XYZRHW로 설정합니다.
// 3D에서는 프로그램 중앙의 좌표가 (0, 0, 0)이 되므로 이걸 기준으로 설정하게 됩니다.
// 정점 형식은 곧 정점 셰이더를 의미합니다.
// DirectX9의 기본 셰이더는 고러드(Gouraud) 셰이더입니다.
// 이번 예제에서 사용되지는 않지만 고러드 셰이더는 그라디언트(Gradiant) 효과가 있습니다.
#define D3DFVF_CUSTOM (D3DFVF_XYZRHW) 

//////////////////////////////////////////////////////////////////////////
// 구조체 선언입니다.

struct CUSTOM_VERTEX
{
	// v는 Vector의 약자입니다. 3D의 좌표는 XYZ입니다.
	// 동차 좌표(Homogeneous Coordinates)라면 XYZ에 W가 추가됩니다.
	// 이번 예제에서는 동차 좌표로 설정해보겠습니다.
	// 동차 좌표로 설정해야 클라이언트 좌표 기준으로 설정할 수 있습니다.
	D3DXVECTOR4 vPos;
	DWORD       dwColor;
};

//////////////////////////////////////////////////////////////////////////
// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM             MyRegisterClass(HINSTANCE hInstance);
BOOL             InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_    HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPTSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, g_strCaption, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY002, g_strWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (InitInstance(hInstance, nCmdShow) == FALSE)
	{
		return FALSE;
	}

	// DirectX9 초기화입니다.
	g_pD3DDevice9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DDevice9 == nullptr)
	{
		MSGBOX_ERR("D3D 디바이스 객체 생성 실패했습니다!");
		return FALSE;
	}

	D3DPRESENT_PARAMETERS presentParam;
	ZeroMemory(&presentParam, sizeof(presentParam));

	presentParam.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	presentParam.Windowed         = TRUE;
	presentParam.BackBufferFormat = D3DFMT_UNKNOWN;

	// 설정한 백 버퍼 형식으로 DirectX9 디바이스를 생성합니다.
	if (FAILED(g_pD3DDevice9->CreateDevice(	
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParam,
		&g_pDevice9)))
	{
		MSGBOX_ERR("디바이스 객체 생성 실패했습니다!");
	}

    //////////////////////////////////////////////////////////////////////////
    // 정점 설정입니다.
    // 폴리곤을 렌더링하려면 정점 정보가 3개 필요합니다.
    // DirectX는 왼손 좌표계(Left Hand Coordinate)이므로
    // 정점을 시계 방향으로 설정해야 합니다.
    // 왜냐하면 시계 방향으로 설정해야 법선 벡터의 방향이 양수가 되기 때문입니다.
    // 자세한 내용은 법선 벡터를 알아볼 때 정리하겠습니다.
    CUSTOM_VERTEX vPolygonVerticies[] = 
    {
	  { D3DXVECTOR4(150.0f,  50.0f, 0.0f, 1.0f) },
	  { D3DXVECTOR4(250.0f, 250.0f, 0.0f, 1.0f) },
	  { D3DXVECTOR4( 50.0f, 250.0f, 0.0f, 1.0f) }
    };

	// 정점 버퍼를 생성합니다.
	// DirectX9에서는 정점 버퍼에 메모리를 할당해서
	// 사용자가 원하는 정점 정보를 넣어야 합니다.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = nullptr;
	g_pDevice9->CreateVertexBuffer
	(
		sizeof(vPolygonVerticies), // 사용할 정점 버퍼의 크기입니다.
		0,                         // 0을 넣으면 됩니다.
		D3DFVF_CUSTOM,             // 정점 형식입니다.
		D3DPOOL_DEFAULT,           // 정점이 할당될 메모리 공간입니다.
		&pVertexBuffer,            // 생성된 정점 버퍼의 주소를 담을 포인터입니다.
		nullptr                    // 셰이더 핸들입니다. 지금은 nullptr로 설정합니다.
	);

	// 정점 정보를 메모리에 할당합니다.
	// 멀티쓰레드 환경에서 동작해야 하므로 메모리 영역을 잠궜다가 풀어줍니다.
	// Lock()에서 정점 정보가 등록될 주소를 등록한 뒤에 사용자가 설정한 정점 정보를
	// 복사해서 정점 버퍼에 넣습니다. 이 작업은 내부에서 알아서 처리되므로
	// Lock()을 한 뒤에 정점 정보만 제대로 복사해주면 됩니다.
	VOID* pVertexAlloc;

	pVertexBuffer->Lock
	(
		0,                         // 메모리 오프셋입니다. 0으로 설정합니다.
		sizeof(vPolygonVerticies), // 할당할 메모리 크기입니다. 정점 정보만큼 설정합니다.
		&pVertexAlloc,             // 락된 메모리의 시작 주소를 가리키는 포인터입니다.
		0                          // 플래그값인데 0으로 설정합니다.
	);

	// 락된 메모리의 시작 주소부터 사용할 정점 정보 크기만큼 복사합니다.
	CopyMemory(pVertexAlloc, vPolygonVerticies, sizeof(vPolygonVerticies));

	// 락된 메모리의 시작 주소를 풀어줍니다.
	// 그래야 다른 쓰레드에서 정점 정보가 있는 메모리에 접근할 수 있습니다.
	pVertexBuffer->Unlock();

	// Clear()는 백 버퍼를 사용자가 인자에 넘겨준 정보로 비워줍니다.
	// 3D에서는 깊이 버퍼(Depth Buffer, Z Buffer)가 존재하는데 아직은 쓸 일이 없습니다.
	// 백 버퍼를 원하는 색상으로 칠하고 싶으면 D3DCOLOR_XRGB() 매크로 함수를 이용하면 됩니다.
	g_pDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 0.0f, 0);

	// 렌더링 시작 부분입니다.
	// BeginScene() 밖에서는 렌더링되지 않습니다.
	g_pDevice9->BeginScene();

	// 디바이스의 데이터 스트림과 정점 버퍼를 연결(바인딩, Binding)시켜줍니다.
	// 데이터 스트림이라는 건 디바이스가 데이터를 다루기 위한 다리라고 생각하면 됩니다.
	// C언어를 배울 때 파일 스트림을 배웠는데 이것과 같다고 생각하면 됩니다.
	// 정점 정보를 렌더링하기 위해서는 반드시 정점 정보를 데이터 스트림에 연결시켜줘야 합니다.
	g_pDevice9->SetStreamSource
	(
		0,                    // 데이터 스트림 번호입니다. 0을 넣으면 됩니다.
		pVertexBuffer,        // 데이터 스트림과 연결될 정점 버퍼입니다.
		0,                    // 데이터 스트림 오프셋인데 0을 넣으면 됩니다.
		sizeof(CUSTOM_VERTEX) // 정점 버퍼의 개별 크기입니다. sizeof()로 정의한 정점 정보를 넣어주면 됩니다.
	);

	// 정점 형식을 설정해줍니다.
	g_pDevice9->SetFVF(D3DFVF_CUSTOM);

	// 정점을 렌더링합니다.
	// 정점을 원시적인 정보로 보기 때문에 Primitive라는 이름이 붙었습니다.
	// 형식에는 여러가지가 있는데 폴리곤은 D3DPT_TRIANGLELIST를 많이 사용합니다.
	g_pDevice9->DrawPrimitive
	(
		D3DPT_TRIANGLELIST, // 렌더링할 원시 정보 형식입니다.
		0,                  // 오프셋입니다. 0을 넣어주면 됩니다.
		1                   // 렌더링할 개수입니다. 폴리곤은 정점 3개가 필요하므로 1로 설정하면 됩니다.
	);

	// 렌더링 종료 부분입니다.
	// EndScene() 밖에서는 렌더링되지 않습니다.
	g_pDevice9->EndScene();

	// 백 버퍼와 프론트 버퍼를 교체해줍니다.
	// 백 버퍼에 렌더링을 완료했기 때문에 프론트 버퍼와 교체하면 렌더링된 모습을 볼 수 있습니다.
	g_pDevice9->Present(nullptr, nullptr, nullptr, nullptr);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	bool bDrive = true; // DirectX9 렌더링과 구분하기 위한 변수입니다.

	// 기본 메시지 루프입니다.
	while (bDrive)
	{
		// GetMessage()는 메시지큐에 메시지가 있을 때까지 대기하지만
		// PeekMessage()는 대기하지 않습니다. 게임 프로그래밍에서는
		// GetMessage()가 아니라 PeekMessage()를 사용합니다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDrive = false;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		}
	}

	// 해제는 선언된 순서의 반대로 해야 합니다.
	// 디바이스 객체를 나중에 생성했으므로 정점 버퍼부터 해제합니다.
	SAFE_RELEASE(pVertexBuffer);
	SAFE_RELEASE(g_pDevice9);
	SAFE_RELEASE(g_pD3DDevice9);

	return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY002));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = g_strWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = g_hWnd = CreateWindowW(g_strWindowClass, g_strCaption,
		WS_OVERLAPPED | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		CLIENT_WIDTH, CLIENT_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	RECT clientRect;

	GetClientRect(g_hWnd, &clientRect);

	MoveWindow(g_hWnd,
		GetSystemMetrics(SM_CXSCREEN) / 5,
		GetSystemMetrics(SM_CYSCREEN) / 5,
		CLIENT_WIDTH + (CLIENT_WIDTH - clientRect.right),
		CLIENT_HEIGHT + (CLIENT_HEIGHT - clientRect.bottom), TRUE);

	if (hWnd == nullptr)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT: // DC로 렌더링하는 게 아니므로 메시지를 따로 처리하지 않습니다.
	{
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}