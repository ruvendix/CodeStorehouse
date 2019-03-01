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
#include "RXScene.h"

namespace
{
	bool PredLayerZOrder(RX::RXLayer* pFirst, RX::RXLayer* pSecond)
	{
		// first 기준으로 true면 조건에 맞게 정렬됨, 이 경우는 오름차순
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

		// 레이어 2개 생성
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