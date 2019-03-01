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
#ifndef RXLAYER_H__
#define RXLAYER_H__

#include "base\common\common.h"

enum class LAYER_ZORDER : INT32
{
	NONE = 0,
	OBJECT,
	HUD,
	UI, // UI�� �������Դϴ�.
	END,
};

namespace RX
{

	class RXLayer
	{
	public:
		RXLayer();
		RXLayer(LAYER_ZORDER layerZOrder, const std::string& szTag);
		virtual ~RXLayer();

		// ====================================================================================
		// Getter
		// ====================================================================================
		LAYER_ZORDER getZOrder() const noexcept
		{
			return m_ZOrder;
		}

		std::string getTag() const noexcept
		{
			return m_szTag;
		}

		// ====================================================================================
		// Setter
		// ====================================================================================
		void setZOrder(LAYER_ZORDER layerZOrder)
		{
			m_ZOrder = layerZOrder;
		}

		void setTag(const std::string& szTag)
		{
			m_szTag = szTag;
		}

	private:
		LAYER_ZORDER  m_ZOrder;
		std::string m_szTag;
	};

} // namespace RX end

#endif