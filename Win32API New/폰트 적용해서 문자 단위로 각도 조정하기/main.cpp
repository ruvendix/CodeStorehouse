#include "RXWindowApp.h"
#include "RXFontTestWindow.h"

INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR szCommandLine, INT32 showType)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCommandLine);
	UNREFERENCED_PARAMETER(showType);

	RX::RXGlobal::g_hMainInstance = hInstance;
	RX::RXWindowApp windowApp(L"Sample", 0, 0, 1024, 768);
	windowApp.setRXWindow(new RX::RXFontTestWindow);
	return (windowApp.Run());
} 