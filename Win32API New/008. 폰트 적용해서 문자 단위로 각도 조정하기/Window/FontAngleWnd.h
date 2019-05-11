// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef FONT_ANGLE_WND_H_
#define FONT_ANGLE_WND_H_

// 공용 기능을 사용합니다.
#include "Common/Common.h"

// RXWnd를 사용합니다.
#include "Wnd.h"

/*
	폰트에 기울기를 적용하는 테스트 윈도우입니다.
*/
class RXFontAngleWnd : public RXWnd
{
public:
	using RXWnd::RXWnd;

	RXFontAngleWnd() = default;
	virtual ~RXFontAngleWnd() = default;

	// ======================================================================
	// 메시지 핸들러입니다.
	virtual void OnPaint(HWND hWnd) override;
};

#endif