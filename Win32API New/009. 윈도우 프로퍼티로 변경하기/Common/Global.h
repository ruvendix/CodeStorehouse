// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef GLOBAL_H_
#define GLOBAL_H_

// 표준 기능을 사용합니다.
#include "Standard.h"

// 범용 구조체를 사용합니다.
#include "GlobalStruct.h"

/*
	전역공간처럼 사용합니다.
	생성자와 소멸자를 제외한 모든 멤버함수와 멤버변수는 static입니다.
*/
class RXGlobal final
{
public:
	RXGlobal() = default;
	~RXGlobal() = default;

	// ======================================================================
	// 함수 목록입니다.

	// 길이와 높이를 전달하면 클라이언트 영역 기준으로 윈도우 영역을 재조정합니다.
	// 예를 들어 길이에 1024를 전달하고 높이에 768을 전달하면
	// 클라이언트 영역은 (1024 * 768)이 됩니다.
	static void AdjustClientArea(HWND hWnd, INT32 width, INT32 height);

	// ======================================================================
	// 변수 목록입니다.
	static HINSTANCE m_hMainInstance; // 프로그램 메인 인스턴스입니다.
	
	// ======================================================================
	// 상수 목록입니다.
	static const TCHAR* SZ_WND_PROCEDURE_PROPERTY;
};

#endif