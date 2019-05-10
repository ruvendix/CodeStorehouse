// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef APP_H
#define APP_H

// RXWindow를 사용합니다.
#include "Wnd.h"

// RXWindowClass를 사용합니다.
#include "WndClass.h"

/*
	프로그램의 메인 루틴을 담당합니다.
	추상 클래스이므로 상속은 필수입니다.
*/
class RXApp
{
public:
	RXApp() = default;
	virtual ~RXApp() = default;

	virtual INT32 Run() = 0;
};

#endif