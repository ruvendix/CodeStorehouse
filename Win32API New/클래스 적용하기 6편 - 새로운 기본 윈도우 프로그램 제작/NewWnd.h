// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef NEW_WINDOW_H_
#define NEW_WINDOW_H_

// RXWindow를 사용합니다.
#include "Wnd.h"

/*
	테스트 윈도우입니다.
*/
class RXNewWnd : public RXWnd
{
public:
	using RXWnd::RXWnd; // 생성자 위임입니다.

	virtual ~RXNewWnd() = default;

	// ======================================================================
	// 메시지 핸들러입니다.
	virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags) override;
};

#endif