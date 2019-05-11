// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef WND_CLASS_H
#define WND_CLASS_H

// 공용 기능을 사용합니다.
#include "Common/Common.h"

/*
	윈도우 클래스 생성 및 관리용입니다.
*/
class RXWndClass
{
public:
	RXWndClass() = default;
	virtual ~RXWndClass() = default;

	HRESULT Init(const std::wstring& szWndClass);
	HRESULT RegisterWndClass();

	// ============================================================
	// Setter
	void setWindowClassName(const std::wstring& szWndClass)
	{
		m_szWndClass = szWndClass;
		m_wcex.lpszClassName = m_szWndClass.c_str();
	}

private:
	// RXWndClass 전용으로써, 외부에 공개하지 않습니다.
	static LRESULT CALLBACK WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WNDCLASSEX   m_wcex;       // 윈도우 클래스 정보입니다.
	std::wstring m_szWndClass; // 윈도우 클래스 이름입니다.
};

#endif