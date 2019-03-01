/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-21 (AssortRock �������� ����)
 *
 * <���� ����>
 * ���α׷��� �������� �����ϴ� �Ŵ����Դϴ�.
 * �ܼ��� FPS�� �����ϴ� �� ���� FPS�� ���� �����̵� �� �� �ֽ��ϴ�.
 * �⺻ ������ �������� ������ (���� ������ + ������ ��Ű��)�Դϴ�.
 *
 ====================================================================================*/
#include "RXProgramFPSMgr.h"

const FLOAT32 RX::RXProgramFPSMgr::ONE_SECOND = 1.0f;
const FLOAT32 RX::RXProgramFPSMgr::FIXED_DELTASECONDS_60FPS = 0.0166f;
const FLOAT32 RX::RXProgramFPSMgr::FIXED_DELTASECONDS_30FPS = 0.0333f;

namespace RX
{

	PHOENIX_SINGLETON_INIT(RXProgramFPSMgr);
	RXProgramFPSMgr::RXProgramFPSMgr()
	{
		m_rFrameSec  = 0.0f;
		m_rTimeScale = 1.0f;
		m_frameCnt  = 0;
		m_FPS       = 0;
	}

	void RXProgramFPSMgr::UpdateFrame()
	{
		m_rFrameSec += m_frameTimer.CalcHighResolutionDeltaSeconds();
		++m_frameCnt;

		// 1�ʰ� �Ѿ�� ������ üũ
		if (m_rFrameSec >= ONE_SECOND)
		{
			// FPS = ������ ī��Ʈ / 1��
			// �� �� ������ ������ ���� (������ ī��Ʈ / ��� �ð�)�� �̿��մϴ�.
			m_FPS = static_cast<INT32>(m_frameCnt / m_rFrameSec);
			//RXDEBUGLOG("���� ������ ī��Ʈ %d, FPS : %d", m_frameCnt, m_FPS);
			
			m_rFrameSec -= ONE_SECOND;
			m_frameCnt = 0;
		}
	}

} // namespace RX end