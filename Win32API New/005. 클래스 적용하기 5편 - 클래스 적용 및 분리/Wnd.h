// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef WND_H_
#define WND_H_

// 공용 기능을 사용합니다.
#include "Common.h"

/*
	윈도우 생성 및 관리용입니다.
*/
class RXWnd
{
public:
	RXWnd(const std::wstring& szWndTtile);
	virtual ~RXWnd() = default;

	// ======================================================================
	// 메시지 핸들러입니다.
	virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
	virtual void OnDestroy(HWND hWnd);

	// ======================================================================
	// 윈도우 생성입니다.
	HRESULT Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwStyle); // 기본형입니다.

protected:
	std::wstring m_szWndTitle; // 윈도우 이름입니다.
	HWND         m_hWnd;       // 윈도우 핸들입니다.
};

#endif