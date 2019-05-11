// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef FONT_ANGLE_WND_H_
#define FONT_ANGLE_WND_H_

// ���� ����� ����մϴ�.
#include "Common/Common.h"

// RXWnd�� ����մϴ�.
#include "Wnd.h"

/*
	��Ʈ�� ���⸦ �����ϴ� �׽�Ʈ �������Դϴ�.
*/
class RXFontAngleWnd : public RXWnd
{
public:
	using RXWnd::RXWnd;

	RXFontAngleWnd() = default;
	virtual ~RXFontAngleWnd() = default;

	// ======================================================================
	// �޽��� �ڵ鷯�Դϴ�.
	virtual void OnPaint(HWND hWnd) override;
};

#endif