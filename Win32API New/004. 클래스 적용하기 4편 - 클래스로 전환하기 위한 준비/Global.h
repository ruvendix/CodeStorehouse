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

/*
	전역공간처럼 사용합니다.
	생성자와 소멸자를 제외한 모든 멤버함수와 멤버변수는 static입니다.
*/
class RXGlobal final
{
public:
	RXGlobal() = default;
	~RXGlobal() = default;

	static HINSTANCE m_hMainInstance; // 프로그램 메인 인스턴스입니다.
};

#endif