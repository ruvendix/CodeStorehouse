#include "RXWindowApp.h"

INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR szCommandLine, INT32 showType)
{
	RX::RXGlobal::m_hMainInstance = hInstance;
	RX::RXWindowApp app(L"Base Window Program", 100, 100, 1024, 768);
	return (app.Run());
}