// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#ifndef WIN32API_STDAFX_H_
#define WIN32API_STDAFX_H_

#include "targetver.h"

// 거의 사용되지 않는 내용은 windows.h에서 제외합니다.
#ifdef WIN32_LEAN_AND_MEAN
    #include <windows.h> // Windows 헤더 파일
#else
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h> // Windows 헤더 파일
    #undef  WIN32_LEAN_AND_MEAN
#endif

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <string>

#endif