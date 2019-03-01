/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-07
 *
 * <파일 내용>
 * 게임 씬 안에 있는 레이어입니다.
 * 레이어는 렌더링에도 사용됩니다.
 *
 ====================================================================================*/
#include "layer.h"

namespace RX
{

	RXLayer::RXLayer()
	{
		m_ZOrder = LAYER_ZORDER::NONE;
		m_szTag  = "None";
	}

	RXLayer::RXLayer(LAYER_ZORDER layerZOrder, const std::string& szTag)
	{
		m_ZOrder = layerZOrder;
		m_szTag  = szTag;
	}

	RXLayer::~RXLayer()
	{

	}

} // namespace RX end