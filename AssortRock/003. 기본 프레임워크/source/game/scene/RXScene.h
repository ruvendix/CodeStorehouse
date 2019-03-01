/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2019-02-03
 *
 * <���� ����>
 * ���� ���� �⺻���Դϴ�.
 * ��� �޾Ƽ� �ٸ� ���� �����ϸ� �˴ϴ�.
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

		// ���� ���̾ �����մϴ�.
		// ���̾ 2�� �̻� �����ϸ� ������������ �����մϴ�.
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