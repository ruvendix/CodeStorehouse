// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef SPLASH_WND_H_
#define SPLASH_WND_H_

// ���� ����� ����մϴ�.
#include "Common/Common.h"

// RXWnd�� ����մϴ�.
#include "Wnd.h"

class RXSplashWnd : public RXWnd
{
public:
	using RXWnd::RXWnd;

	RXSplashWnd() = default;
	virtual ~RXSplashWnd() = default;

	// ======================================================================
	// �޽��� �ڵ鷯�Դϴ�.
	virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct) override;
	virtual void OnPaint(HWND hWnd) override;
	virtual void OnDestroy(HWND hWnd) override;
	virtual void OnTimer(HWND hWnd, UINT id) override;

private:
	HBITMAP m_hBitmap = nullptr; // ���÷��� ������� ����� ��Ʈ�� �ڵ��Դϴ�.
};

#endif