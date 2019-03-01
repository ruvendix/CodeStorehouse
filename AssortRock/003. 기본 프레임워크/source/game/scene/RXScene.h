/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-03
 *
 * <파일 내용>
 * 게임 씬의 기본형입니다.
 * 상속 받아서 다른 씬을 구현하면 됩니다.
 *
 ====================================================================================*/
#ifndef RXSCENE_H__
#define RXSCENE_H__

#include "base\common\common.h"
#include "layer\layer.h"

namespace RX
{

	class RXScene : public RXBaseInterface
	{
	public:
		RXScene();
		virtual ~RXScene();

		virtual HRESULT OnInit()    override;
		virtual HRESULT OnUpdate()  override;
		virtual HRESULT OnRender()  override;
		virtual HRESULT OnRelease() override;

		// 씬에 레이어를 삽입합니다.
		// 레이어가 2개 이상 존재하면 오름차순으로 정렬합니다.
		void InsertLayer(LAYER_ZORDER layerZOrder, const std::string& szTag);

		// ====================================================================================
		// Getter
		// ====================================================================================
		RXLayer* getFrontLayer() const noexcept
		{
			return m_listLayer.front();
		}

		RXLayer* getEndLayer() const noexcept
		{
			return m_listLayer.back();
		}

	private:
		std::list<RXLayer*> m_listLayer;
	};

} // namespace RX end

#endif