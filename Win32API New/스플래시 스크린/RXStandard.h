#ifndef RX_STANDARD_H_
#define RX_STANDARD_H_

#include <crtdbg.h>
#include <tchar.h>

#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>
#include <CommCtrl.h>

#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
#include <unordered_map>

#define RXNew new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define MSGBOX(szText) (::MessageBox(::GetDesktopWindow(), szText, L"Ä¸¼Ç", MB_OK))

#define ERRMSGBOX(szError)\
	(::MessageBox(::GetDesktopWindow(), szError, L"¿À·ù", MB_OK))

#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

#define SAFE_DLETE_BRUSH(hBrush)\
	if (hBrush != nullptr)\
	{\
		::DeleteBrush(hBrush);\
		hBrush = nullptr;\
	}

const INT32 MAX_STRING_LENGTH = 512;
const INT32 WS_GAME_DEFAULT   = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME) | WS_VISIBLE;

const INT32 WINDOW_COLOR_WHITE = RGB(255, 255, 255);
const INT32 WINDOW_COLOR_RED   = RGB(255,   0,   0);
const INT32 WINDOW_COLOR_GREEN = RGB(  0, 255,   0);
const INT32 WINDOW_COLOR_BLUE  = RGB(  0,   0, 255);

#pragma comment(lib, "winmm.lib")

#endif