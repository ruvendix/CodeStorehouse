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
#include "RXScene.h"

namespace
{
	bool PredLayerZOrder(RX::RXLayer* pFirst, RX::RXLayer* pSecond)
	{
		// first �������� true�� ���ǿ� �°� ���ĵ�, �� ���� ��������
		return (pFirst->getZOrder() < pSecond->getZOrder());
	}
}

namespace RX
{

	RXScene::RXScene()
	{

	}

	RXScene::~RXScene()
	{

	}

	HRESULT RXScene::OnInit()
	{		
		MSGBOX("Test");

		// ���̾� 2�� ����
		InsertLayer(LAYER_ZORDER::UI, "UI");
		InsertLayer(LAYER_ZORDER::OBJECT, "Object");

		return S_OK;
	}

	HRESULT RXScene::OnUpdate()
	{
		return S_OK;
	}

	HRESULT RXScene::OnRender()
	{
		return S_OK;
	}

	HRESULT RXScene::OnRelease()
	{
		DeleteAllHeapElement(&m_listLayer);
		return S_OK;
	}

	void RXScene::InsertLayer(LAYER_ZORDER layerZOrder, const std::string& szTag)
	{
		RXLayer* pLayer = RXNew RXLayer(layerZOrder, szTag);
		NULLCHK_HEAPALLOC(pLayer);

		m_listLayer.push_back(pLayer);

		if (m_listLayer.size() >= 2)
		{
			m_listLayer.sort(PredLayerZOrder);
		}
	}

} // namespace RX end