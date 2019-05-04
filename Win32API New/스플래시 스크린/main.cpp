#include "RXCustomWindowApp.h"
#include "RXFontTestWindow.h"
#include "RXControlTestWindow.h"
#include "RXWindowTestWindow.h"
#include "RXPopupWindow.h"
#include "RXLayeredWindow.h"

INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR szCommandLine, INT32 showType)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCommandLine);
	UNREFERENCED_PARAMETER(showType);

	RX::RXGlobal::g_hMainInstance = hInstance;
	RX::RXCustomWindowApp customWindowApp(0, 0, 1024, 768);
	customWindowApp.setMainRXWindow(RXNew RX::RXLayeredWindow);
	return (customWindowApp.Run());
}