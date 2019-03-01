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
#ifndef RXLAYER_H__
#define RXLAYER_H__

#include "base\common\common.h"

enum class LAYER_ZORDER : INT32
{
	NONE = 0,
	OBJECT,
	HUD,
	UI, // UI가 마지막입니다.
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