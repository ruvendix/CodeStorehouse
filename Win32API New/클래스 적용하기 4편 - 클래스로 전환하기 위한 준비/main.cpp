#include <windows.h>
#include "common.h"

INT32 APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, INT32 cmdShow)
{
	// ����ó�� ����� Ŭ������ ������ ����մϴ�.
	RX::RXGlobal::m_hMainInstance = hInstance;
	
	return 0;
}