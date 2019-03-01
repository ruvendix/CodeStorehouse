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