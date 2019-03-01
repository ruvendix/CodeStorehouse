/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-03
 *
 * <파일 내용>
 * 게임 씬을 관리합니다.
 * 현재 씬의 루틴을 작동시키고 다음 씬을 갖고 있습니다.
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

	class RXScene; // 전방선언은 포인터로만 사용 가능!
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