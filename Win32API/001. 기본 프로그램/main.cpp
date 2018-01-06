/*
 * <파일 설명>
 * Win32API 기본 프로그램입니다.
 * 개념에 혼란을 줄 수 있는 부분이 있어서 필요한 부분만 작성했습니다.
 * 기본 프로그램에 Win32API의 다양한 기능들을 추가하면 훌륭한 윈도우 프로그램을 만들 수 있습니다.
 * 자동 생성 코드가 존재하기 때문에 굳이 이렇게 처음부터 작성할 필요는 없습니다.
 * 그냥 개념 이해를 위해 한번 정도만 작성하면 충분하다고 생각합니다.
 * 참고로 Win32API는 멀티바이트, 유니코드 양쪽을 지원합니다. 
 */

#include <windows.h> // Win32API를 이용하기 위한 기본 헤더 파일입니다.

LPCSTR lpStrClassName      = "Win32API Basic Window Class";
LPCSTR lpStrMainWindowName = "Win32API Basic Main Window";

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT32 Message, WPARAM wParam, LPARAM lParam);

// 윈도우 프로그래밍에서는 C, C++에서 사용한 main()이 아니라 winMain()을 작성합니다.
// Win32API에서는 정수 자료형을 효율적으로 사용하기 위해 바이트로 구분합니다.
// 실수 자료형은 일관성을 지키기 위해 FLOAT, DOUBLE 이렇게 대문자로 표기합니다.
//
// APIENTRY는 Win32API의 기본 호출 규약인 __stdcall을 의미합니다.
// __stdcall은 인자를 <-(오른쪽) 순서로 매개변수에 전달하고, 스택 프레임을 호출된 함수에서 정리합니다.
// C, C++에서 사용했던 함수(printf(), fopen() 등)들은 함수 호출 규약이 __cdecl입니다.
//
// H로 시작되면 핸들(Handle)을 의미하는데 핸들은 운영체제가 할당해주는 자원의 정수값입니다.
// 직접 자원에 접근할 수는 없지만 핸들을 이용하면 간접적으로 자원에 접근할 수 있습니다.
// 인스턴스(Instance)는 운영체제에 등록된 프로그램을 말합니다. 같은 프로그램이면 인스턴스가 같습니다.
// 하지만 프로세스(Process, 메모리에 활성화된 프로그램)는 PID(Process Identification)로 판단하기 때문에
// 같은 프로그램도 다르다고 구분합니다.
INT32 APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT32 cmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance); // 안 쓰는 매개변수를 표시합니다.

	//////////////////////////////////////////////////////////////////////////
	// 윈도우 클래스(Window Class)를 생성합니다.
	// 여기서 말하는 클래스는 객체지향(C++, C#, JAVA 등)의 클래스가 아닙니다.
	// 멀티프로그래밍(Multiprogramming)을 위해 자원(Resource)을 공유하기 위한 구조체입니다.
	// Class에는 "종류"라는 뜻도 있는데 이 뜻으로 사용되었습니다.
	// 게임에서 전사 클래스, 마법사 클래스 이렇게 표현하기도 하는데 이것과 같은 뜻입니다.
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc)); // 내부적으로 memset(&wc, 0, sizeof(wc))입니다.

	//wc.cbSize        = sizeof(wc);    // 윈도우 클래스의 크기
	wc.hInstance     = hInstance;       // 운영체제에 등록할 인스턴스
	wc.lpszClassName = lpStrClassName;  // 윈도우 클래스 이름
	wc.lpfnWndProc   = WindowProcedure; // 메시지를 처리할 윈도우 프로시저, 위에서 따로 설명

	// 초기화가 끝난 윈도우 클래스를 운영체제에 등록합니다.
	// 다른 윈도우를 만들고 싶으면 등록한 윈도우 클래스를 재활용하면 됩니다.
	// 새로 만들 필요 없이 wcex의 정보를 재설정해서 등록해주면 됩니다.
	RegisterClass(&wc);

	//////////////////////////////////////////////////////////////////////////
	// 윈도우를 생성합니다.
	// 인자는 순서대로 다음과 같습니다.
	// 윈도우 클래스 이름 | 윈도우 이름 | 윈도우 스타일 | 생성할 x 좌표 | 생성할 y 좌표
	// 가로 길이 | 세로 길이 | 부모 윈도우 | 메뉴 | 인스턴스 | 전달할 정보
	//
	// 마지막 인자는 윈도우 프로시저의 lParam으로 전달되는 정보입니다.
	// CreateWindow()는 WM_CREATE 메시지가 발생시키는데 이때 윈도우 프로시저에서
	// CREATESTRUCT로 lParam을 전달 받을 수 있습니다.
	// 여기서는 개념에 혼란을 줄 수 있다고 판단해서 해당 내용은 제외시킵니다.
	//
	// WS_OVERLAPPEDWINDOW는 Win32API 프로그램의 기본 윈도우 스타일입니다.
	// CW_USEDEFAULT는 Win32API 프로그램의 기본값입니다.
	HWND hWnd = CreateWindow(lpStrClassName, lpStrMainWindowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

	// 생성한 윈도우를 갱신합니다.
	UpdateWindow(hWnd); 

	// 갱신한 윈도우를 보여줍니다. winMain()의 cmdShow가 사용됩니다.
	// cmdShow의 기본값은 SW_NORMAL입니다.
	ShowWindow(hWnd, cmdShow);
	
	//////////////////////////////////////////////////////////////////////////
	// 메시지를 처리할 메시지 루프를 작성합니다.
	// 프로그램에서 발생한 메시지들은 운영체제가 관리하는 메시지 큐에 저장되어서
	// 우선순위에 따라 각 메시지가 처리됩니다. 일부 메시지는 메시지 테이블이라는 곳에 저장됩니다.
	// 우선순위는 메시지 큐 > 메시지 테이블입니다. 메시지 테이블에 저장되는 대표적인 메시지는 WM_PAINT입니다.
	MSG message;
	ZeroMemory(&message, sizeof(message));

	while (true)
	{
		if (message.message == WM_QUIT) // 종료 메시지를 받으면 메시지 루프를 탈출합니다.
		{
			break;
		}

		if (GetMessage(&message, nullptr, 0, 0))
		{
			DispatchMessage(&message);
		}
	}

	return static_cast<INT32>(message.message);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT32 Message, WPARAM wParam, LPARAM lParam)
{
   // switch ~ case 내부에서 지역변수를 사용하려면
   //
   // case 1:
   // {
   //     INT32 num;
   //     break;
   // }
   //
   // 이렇게 묶어야 합니다. 안 묶으면 컴파일 오류가 발생할 수 있습니다.
	switch (Message)
	{
		case WM_CLOSE:
		{
			INT32 a = 100;
			PostQuitMessage(0); // 0은 WinMain()에 전달할 값입니다.
			return 0;
		}
	}

	// 기본적으로 처리되어야 할 메시지는 아래에 있는 함수에게 맡깁니다.
	// DefWindowProc은 Default Window Procedure의 약자입니다.
	return DefWindowProc(hWnd, Message, wParam, lParam);
}