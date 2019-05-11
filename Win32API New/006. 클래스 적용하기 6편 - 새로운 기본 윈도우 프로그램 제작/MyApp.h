// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef MY_APP_H
#define MY_APP_H

// RXApp을 사용합니다.
#include "App.h"

// RXNewWnd를 사용합니다.
#include "NewWnd.h"

/*
	메인 루틴을 담당합니다.
*/
class RXMyApp : public RXApp
{
public:
	RXMyApp();
	RXMyApp(const std::wstring& szTitle, INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight);
	virtual ~RXMyApp();
	
	virtual HRESULT InitWndClass();
	virtual INT32   Run() override;

private:
	RXWndClass*   m_pWndClass;     // 윈도우 클래스입니다.
	RXWnd*        m_pWnd;          // 윈도우입니다.
	WndCreateInfo m_wndCreateInfo; // 윈도우 생성 정보입니다.
};

#endif