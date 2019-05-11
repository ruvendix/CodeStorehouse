// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

/*
	전에는 WIN32_LEAN_AND_MEAN을 사용했지만,
	요즘 컴퓨터 사양에서는 의미가 없으므로 제거합니다.
*/

// RXWndApp을 사용합니다.
#include "MyApp.h"

// RXMouseDragWnd를 사용합니다.
#include "MouseDragWnd.h"

// 윈도우 프로그램의 진입점입니다.
INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCommandLine, INT32 showStyle)
{
	// ======================================================================
	// 사용하지 않는 매개변수입니다.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCommandLine);

	// 전역공간처럼 사용할 클래스에 변수를 등록합니다.
	RXGlobal::m_hMainInstance = hInstance;

	// 프로그램의 메인 루틴을 담당할 객체를 생성합니다.
	RXMyApp myApp(_T("Sample"), 100, 100, 1024, 768);
	
	// 프로그램의 메인 윈도우를 변경합니다.
	myApp.setMainWnd(RXNew RXMouseDragWnd);

	// 프로그램의 메인 루틴을 작동시킵니다.
	return (myApp.Run());
}