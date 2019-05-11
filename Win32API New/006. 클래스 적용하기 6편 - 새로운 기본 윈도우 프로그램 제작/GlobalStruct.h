// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef GLOBAL_STRUCT_H_
#define GLOBAL_STRUCT_H_

// 표준 기능을 사용합니다.
#include "Standard.h"

/*
	범용 구조체 모음입니다.
	구조체는 POD(Plain Old Data) 위주로 정의합니다.
	가끔 POD가 아닐 때도 있습니다.
*/

// 2D 좌표에서의 위치입니다. 줄여서 위치로 표기합니다.
// 비슷한 의미로는 Vector 2D가 있지만
// 수학적으로 사용하는 게 아니므로 좀 더 직관적으로 표기합니다.
struct PositionInfo
{
	INT32 x;
	INT32 y;
};

// 해상도 정보입니다.
// 해상도는 픽셀 또는 도트에 따라 의미가 변하지만
// 일반적으로는 (가로 X 세로)를 의미합니다.
struct ResolutionInfo
{
	INT32 width;
	INT32 height;
};

// 윈도우 생성 정보입니다.
// 현재는 위치와 해상도 정보만 있습니다.
struct WndCreateInfo
{
	PositionInfo   posInfo;        // 2D 좌표
	ResolutionInfo resolutionInfo; // 해상도 정보
};

#endif