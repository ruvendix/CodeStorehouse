#include <windows.h>
#include "common.h"

INT32 APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, INT32 cmdShow)
{
	// 전역처럼 사용할 클래스에 변수를 등록합니다.
	RX::RXGlobal::m_hMainInstance = hInstance;
	
	return 0;
}