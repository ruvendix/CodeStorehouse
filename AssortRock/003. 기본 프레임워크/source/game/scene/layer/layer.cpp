/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2019-02-07
 *
 * <���� ����>
 * ���� �� �ȿ� �ִ� ���̾��Դϴ�.
 * ���̾�� ���������� ���˴ϴ�.
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