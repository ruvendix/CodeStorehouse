// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef GLOBAL_H_
#define GLOBAL_H_

// ǥ�� ����� ����մϴ�.
#include "Standard.h"

// ���� ����ü�� ����մϴ�.
#include "GlobalStruct.h"

/*
	��������ó�� ����մϴ�.
	�����ڿ� �Ҹ��ڸ� ������ ��� ����Լ��� ��������� static�Դϴ�.
*/
class RXGlobal final
{
public:
	RXGlobal() = default;
	~RXGlobal() = default;

	// ======================================================================
	// �Լ� ����Դϴ�.
	static void         AdjustClientArea(HWND hWnd, INT32 width, INT32 height);
	static void         DrawBimapExcludeColorKey(HDC hDC, HBITMAP hBitmap, INT32 x, INT32 y,
		                                         COLORREF colorKey, bool bCenter);
	static POINT        CalcCenterPosByScreen(INT32 width, INT32 height);
	static POINT        CalcCenterPosByScreen(WndCreateInfo* pWndCreateInfo);
	static std::wstring MakeFormatString(const WCHAR* szFormat, ...);

	// ======================================================================
	// ���� ����Դϴ�.
	static HINSTANCE m_hMainInstance;  // ���α׷� ���� �ν��Ͻ��Դϴ�.
	static bool      m_bRunMainWnd;    // ���α׷� ���� ������ �۵� �����Դϴ�.

	// ======================================================================
	// ��� ����Դϴ�.
	static const TCHAR* SZ_WND_PROCEDURE_PROPERTY;
	static const TCHAR* SZ_NULL;

	// ������ �����Դϴ�.
	static const INT32  WINDOW_COLOR_WHITE = RGB(255, 255, 255);
	static const INT32  WINDOW_COLOR_RED   = RGB(255, 0, 0);
	static const INT32  WINDOW_COLOR_GREEN = RGB(0, 255, 0);
	static const INT32  WINDOW_COLOR_BLUE  = RGB(0, 0, 255);
};

#endif