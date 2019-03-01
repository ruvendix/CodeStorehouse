#include "main.h"
#include "global_instance\misc\RXCore.h"
#include "global_instance\misc\RXPerformanceProfiler.h"

INT32 APIENTRY _tWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    szCmdLine,
	INT32     cmdShow)
{
	//_CrtSetBreakAlloc(418);

	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCmdLine);
	UNREFERENCED_PARAMETER(cmdShow);

	RXCORE->OnDrive();

	return RXCORE->getMessageCode();
}