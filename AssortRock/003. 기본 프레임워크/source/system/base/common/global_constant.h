/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-08-07 (AssortRock 전용으로 수정)
 *
 * <파일 내용>
 * 공동으로 사용되는 전역 상수 모음입니다.
 * 미리 컴파일된 헤더파일에 포함됩니다.
 *
 ====================================================================================*/
#ifndef GLOBAL_CONSTANT_H__
#define GLOBAL_CONSTANT_H__

#include "global_type.h"

const INT32 DEFAULT_STRING_LENGTH = 512;
const INT32 MAX_STRING_LENGTH     = 1024;
const INT32 MAX_FILE_NAME         = 256;

const FLOAT32 FIXED_DELTASECONDS_60FPS = 0.0166f;
const FLOAT32 FIXED_DELTASECONDS_30FPS = 0.0333f;

#endif