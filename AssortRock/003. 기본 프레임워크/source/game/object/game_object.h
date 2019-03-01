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
#ifndef RXGAME_OBJECT_H__
#define RXGAME_OBJECT_H__

#include "base\common\common.h"

namespace RX
{

	class RXGameObject
	{
	public:
		RXGameObject();
		RXGameObject(const std::string& szTag);
		virtual ~RXGameObject();

		// ====================================================================================
		// Getter
		// ====================================================================================
		std::string getTag() const noexcept
		{
			return m_szTag;
		}

		// ====================================================================================
		// Setter
		// ====================================================================================
		void setTag(const std::string& szTag)
		{
			m_szTag = szTag;
		}

	private:
		std::string m_szTag;
	};

} // namespace RX end

#endif