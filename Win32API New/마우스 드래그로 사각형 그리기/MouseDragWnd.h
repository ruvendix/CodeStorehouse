// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef MOUSE_DRAG_WND_H_
#define MOUSE_DRAG_WND_H_

// ���� ����� ����մϴ�.
#include "Common.h"

// RXWnd�� ����մϴ�.
#include "Wnd.h"

/*
	���� ���콺 ��ư�� Ŭ���� ���¿���
	�巡���ϸ� �簢���� �׸��� �������Դϴ�.
*/
class RXMouseDragWnd : public RXWnd
{
public:
	using RXWnd::RXWnd; // ������ �����Դϴ�.

	RXMouseDragWnd() = default;
	virtual ~RXMouseDragWnd() = default;

	// ======================================================================
	// �޽��� �ڵ鷯�Դϴ�.
	virtual void OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnPaint(HWND hWnd);

protected:
	bool m_bDrag = false; // �巡�� �����Դϴ�.
	RECT m_dragArea;      // �巡�� �����Դϴ�.
};

#endif