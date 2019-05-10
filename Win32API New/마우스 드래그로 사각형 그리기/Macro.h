// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef MACRO_H_
#define MACRO_H_

// 기본 메시지 박스입니다.
#define MSGBOX(szContents) (::MessageBox(::GetDesktopWindow(), szContents, L"메시지 박스", MB_OK))

// 오류 메시지 박스입니다.
#define ERRMSGBOX(szError) (::MessageBox(::GetDesktopWindow(), szError, L"오류", MB_OK))

// 공용체의 멤버값을 size_t로 변환합니다.
#define NUM(enumValue)           static_cast<size_t>(enumValue)

// 정수값을 공용체의 멤버값으로 변환합니다.
#define ENUM(enumType, intValue) static_cast<enumType>(intValue)

// 디버그 모드에서 메모리 릭을 잡는 보조입니다.
#define RXNew new(_NORMAL_BLOCK, __FILE__, __LINE__)

// 동적할당된 포인터를 해제하고 nullptr로 만듭니다.
#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

#endif