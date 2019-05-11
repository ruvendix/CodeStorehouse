// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef NEW_WINDOW_H_
#define NEW_WINDOW_H_

// RXWindow�� ����մϴ�.
#include "Wnd.h"

/*
	�׽�Ʈ �������Դϴ�.
*/
class RXNewWnd : public RXWnd
{
public:
	using RXWnd::RXWnd; // ������ �����Դϴ�.

	virtual ~RXNewWnd() = default;

	// ======================================================================
	// �޽��� �ڵ鷯�Դϴ�.
	virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags) override;
};

#endif