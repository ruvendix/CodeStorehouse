/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2019-02-07
 *
 * <���� ����>
 * ���� ������Ʈ �⺻���Դϴ�.
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