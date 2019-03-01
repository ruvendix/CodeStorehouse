/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-02
 *
 * <파일 내용>
 * main.cpp의 헤더파일입니다.
 * 프로젝트에 한번만 포함됩니다.
 *
 ====================================================================================*/
#ifndef MAIN_H_
#define MAIN_H_

#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC // 디버그 할당을 사용하겠다는 선언
#define RXNew new(_NORMAL_BLOCK, __FILE__, __LINE__) // 덤프를 좀 더 쉽게 보기 위한 것
#endif

#endif