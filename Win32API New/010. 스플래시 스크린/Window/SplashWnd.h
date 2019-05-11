// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef SPLASH_WND_H_
#define SPLASH_WND_H_

// 공용 기능을 사용합니다.
#include "Common/Common.h"

// RXWnd를 사용합니다.
#include "Wnd.h"

class RXSplashWnd : public RXWnd
{
public:
	using RXWnd::RXWnd;

	RXSplashWnd() = default;
	virtual ~RXSplashWnd() = default;

	// ======================================================================
	// 메시지 핸들러입니다.
	virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct) override;
	virtual void OnPaint(HWND hWnd) override;
	virtual void OnDestroy(HWND hWnd) override;
	virtual void OnTimer(HWND hWnd, UINT id) override;

private:
	HBITMAP m_hBitmap = nullptr; // 스플래시 윈도우로 사용할 비트맵 핸들입니다.
};

#endif