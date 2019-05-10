// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef MOUSE_DRAG_WND_H_
#define MOUSE_DRAG_WND_H_

// 공용 기능을 사용합니다.
#include "Common.h"

// RXWnd를 사용합니다.
#include "Wnd.h"

/*
	왼쪽 마우스 버튼을 클릭한 상태에서
	드래그하면 사각형을 그리는 윈도우입니다.
*/
class RXMouseDragWnd : public RXWnd
{
public:
	using RXWnd::RXWnd; // 생성자 위임입니다.

	RXMouseDragWnd() = default;
	virtual ~RXMouseDragWnd() = default;

	// ======================================================================
	// 메시지 핸들러입니다.
	virtual void OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnPaint(HWND hWnd);

protected:
	bool m_bDrag = false; // 드래그 여부입니다.
	RECT m_dragArea;      // 드래그 영역입니다.
};

#endif