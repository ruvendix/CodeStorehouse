/*
 * <파일 설명>
 * DirectX9 초기화 프로그램입니다.
 * DirectX9 프로그래밍은 이렇게 시작됩니다.
 */

// 001. 초기화.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "001. 초기화.h"

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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, g_strCaption, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY001, g_strWindowClass, MAX_LOADSTRING);
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

	// 백 버퍼(Back Buffer) 정보 초기화입니다.
	// 백 버퍼는 자연스러운 렌더링을 위해 미리 렌더링되는 공간을 뜻합니다.
	// 화면에 보이는 버퍼는 프론트 버퍼(Front Buffer)라고 합니다.
	// 백 버퍼와 프론트 버퍼는 서로 연결되어있는데 이것을 스왑 체인(Swap Chain)이라고 합니다.
	// 렌더링되는 버퍼에는 서페이스(Surface)가 존재하는데 이걸 응용하면
	// 텍스처(Texture) 같은 곳에도 렌더링할 수 있습니다.
	// 이때는 렌더 타겟(Render Target이 텍스처가 됩니다.
	// 정리하면 기본 렌더 타켓은 백 버퍼라고 할 수 있습니다.
	D3DPRESENT_PARAMETERS presentParam;
	ZeroMemory(&presentParam, sizeof(presentParam));

	// 버퍼를 교체할 때의 효과를 설정합니다.
	// D3DSWAPEFFECT_DISCARD가 예제로 사용되는데
	// 이것은 프론트 버퍼가 화면상에 출력되고 있을 때
	// 백 버퍼의 변경이 일어나도 신경 쓰지 않겠다는 겁니다.
	// 하지만 비디오 메모리(그래픽 카드의 메모리)가 많이 필요한
	// 오버헤드(Overhead, 비용)가 있습니다.
	// 다른 건 D3DSWAPEFFECT_FLIP, D3DSWAPEFFECT_COPY가 있습니다.
	presentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	
	// 윈도우 모드(창 모드) 여부입니다.
	presentParam.Windowed = TRUE;

	// 백 버퍼 형식입니다.
	// 윈도우 모드(창 모드)에서는 D3DFMT_UNKNOWN으로 설정하고
	// 전체 화면 모드일 때는 원하는 형식을 설정합니다.
	// 형식에는 D3DFMT_A8B8G8R8 같은 것들이 있습니다.
	presentParam.BackBufferFormat = D3DFMT_UNKNOWN;

	// 설정한 백 버퍼 형식으로 DirectX9 디바이스를 생성합니다.
	if (FAILED(g_pD3DDevice9->CreateDevice(
               // 어댑터 설정입니다. 기본은 1개입니다.	
               D3DADAPTER_DEFAULT,
               
               // 디바이스 타입입니다.
               // HAL(Hard Abstraction Layer)은 그래픽 장치에 관계없이
               // 그래픽 카드의 기능을 이용하는 걸 뜻합니다.
               D3DDEVTYPE_HAL,
                      
               // 디바이스와 연결될 윈도우 핸들입니다.
               g_hWnd,
               
               // 디바이스의 정점 처리 방식을 설정합니다.
               // 소프트웨어 처리 방식보다 하드웨어 처리 방식을 많이 사용합니다.
               // 예제에서는 소프트웨어 처리 방식으로 설정합니다.
               D3DCREATE_SOFTWARE_VERTEXPROCESSING,
               
               // 설정한 백 버퍼 형식을 전달합니다.
               &presentParam,
               
               // 생성할 디바이스의 주소를 저장할 포인터입니다.
               // 포인터가 가리키는 주소를 변경해야 하므로 더블 포인터로 설정해야 합니다.
               &g_pDevice9)))
	{
		MSGBOX_ERR("디바이스 객체 생성 실패했습니다!");
	}

	// Present()는 백 버퍼와 프론트 버퍼를 바꿔줍니다.
	// 따라서 백 버퍼가 프론트 버퍼로 설정됩니다.
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
	// 디바이스 객체를 나중에 생성했으므로 디바이스 객체부터 해제합니다.
	SAFE_RELEASE(g_pDevice9);
	SAFE_RELEASE(g_pD3DDevice9);

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY001));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = g_strWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   // 클라이언트 크기를 기준으로 전체 윈도우 크기를 재설정합니다.
   // 좌표가 아니라 크기를 넘겨주므로 0부터 시작하면 1을 빼야 합니다.
   // 만약에 1을 빼지 않는다면 800 X 600이 아니라 801 X 601로 설정됩니다.
   // 하지만 윈도우 스타일 적용에 제한이 있으므로 MoveWinodw()를 사용해야 합니다.
   // MoveWindow()는 좌표를 이용해서 전체 영역을 설정해줍니다.
   //
   // AdjustWindowRect(&clientRect, WS_OVERLAPPED | WS_SYSMENU, FALSE);

   HWND hWnd = g_hWnd = CreateWindowW(g_strWindowClass, g_strCaption,
	   WS_OVERLAPPED | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
	   CLIENT_WIDTH, CLIENT_HEIGHT, nullptr, nullptr, hInstance, nullptr); 

   RECT clientRect;

   // 윈도우 핸들의 클라이언트 영역을 좌표로 알려줍니다.
   // 항상 왼쪽 위 좌표는 (0, 0)입니다.
   // 실제 모니터의 좌표와는 차이가 있으므로 주의해야 합니다.
   // ScreenToClinet() 또는 ClientToScreen()을 이용해서 좌표 변환을 합니다.
   GetClientRect(g_hWnd, &clientRect);

   // 좌표를 이용해서 윈도우의 전체 영역을 재설정해줍니다.
   // 좌표 이동과 크기 변경 두 가지 기능이 있습니다.
   // 원하는 크기의 클라이언트 영역을 적용하려면
   // 가로는 (가로 + (가로 - 클라이언트 영역))
   // 세로는 (세로 + (세로 - 클라이언트 영역)) 이렇게 해야 합니다.
   // 왜냐하면 현재 설정된 클라이언트 영역에서 원하는 클라이언트 영역과의
   // 차이를 구한 뒤 윈도우 전체 영역에 더해주면 전체 윈도우 영역이 커지면서
   // 클라이언트 영역도 새로 설정되기 때문입니다.
   // 이 방법은 윈도우 스타일에 제약을 받지 않습니다.
   MoveWindow
   (
	   g_hWnd,
	   GetSystemMetrics(SM_CXSCREEN) / 5, // 가로는 5분의 1 지점으로 설정합니다.
	   GetSystemMetrics(SM_CYSCREEN) / 5, // 세로는 5분의 1 지점으로 설정합니다.
	   CLIENT_WIDTH + (CLIENT_WIDTH - clientRect.right),
	   CLIENT_HEIGHT + (CLIENT_HEIGHT - clientRect.bottom),
	   TRUE
   );

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