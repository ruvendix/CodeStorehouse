#ifndef COMMON_H_
#define COMMON_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <tchar.h>

#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

#include <string>
#include <vector>
#include <unordered_map>

#define ERRMSGBOX(szError)\
	(::MessageBox(::GetDesktopWindow(), szError, L"¿À·ù", MB_OK))

#include "RXGlobal.h"

#endif