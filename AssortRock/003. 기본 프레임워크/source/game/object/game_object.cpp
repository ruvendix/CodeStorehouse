/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-07
 *
 * <파일 내용>
 * 게임 오브젝트 기본형입니다.
 *
 ====================================================================================*/
#include "game_object.h"

namespace RX
{

	RXGameObject::RXGameObject()
	{
		m_szTag = "None";
	}

	RXGameObject::RXGameObject(const std::string& szTag)
	{
		m_szTag = szTag;
	}

	RXGameObject::~RXGameObject()
	{

	}

} // namespace RX end