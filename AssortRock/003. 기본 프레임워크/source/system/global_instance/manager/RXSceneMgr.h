/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2019-02-03
 *
 * <���� ����>
 * ���� ���� �����մϴ�.
 * ���� ���� ��ƾ�� �۵���Ű�� ���� ���� ���� �ֽ��ϴ�.
 *
 ====================================================================================*/
#ifndef RXSCENE_MANAGER_H_
#define RXSCENE_MANAGER_H_

#include "base\common\common.h"
#include "scene\RXScene.h"

enum class SCENE_TYPE : INT32
{
	CURRENT,
	NEXT,
};

namespace RX
{

	class RXScene; // ���漱���� �����ͷθ� ��� ����!
	class RXSceneMgr
	{
		PHOENIX_SINGLETON_CTOR(RXSceneMgr);

	public:
		RXSceneMgr();

		void DeleteScene();

		template <typename _Ty>
		void CreateScene()
		{
			SAFE_DELETE(m_pScene);
			m_pScene = RXNew _Ty;
			NULLCHK_HEAPALLOC(m_pScene);
		}

		// ====================================================================================
		// Getter
		// ====================================================================================
		RXScene* getCurrentScene() const noexcept
		{
			NULLCHK(m_pScene);
			return m_pScene;
		}

		// ====================================================================================
		// Setter
		// ====================================================================================
		//void setCurrentScene(RXScene* pScene)
		//{
		//	NULLCHK(pScene);
		//	m_pScene = pScene;
		//}

	private:
		RXScene* m_pScene;
		RXScene* m_pNextScene;
	};

} // namespace RX end

#endif