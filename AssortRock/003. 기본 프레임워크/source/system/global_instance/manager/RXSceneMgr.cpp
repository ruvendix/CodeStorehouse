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
#include "RXSceneMgr.h"

namespace RX
{

	PHOENIX_SINGLETON_INIT(RXSceneMgr);
	RXSceneMgr::RXSceneMgr()
	{
		m_pScene     = nullptr;
		m_pNextScene = nullptr;
	}

	void RXSceneMgr::DeleteScene()
	{
		SAFE_DELETE(m_pScene);
		SAFE_DELETE(m_pNextScene);
	}

} // namespace RX end