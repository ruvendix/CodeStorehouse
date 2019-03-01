/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-10-21 (AssortRock 전용으로 수정)
 *
 * <파일 내용>
 * 프로그램의 프레임을 관리하는 매니저입니다.
 * 단순히 FPS를 측정하는 것 말고도 FPS에 따른 딜레이도 줄 수 있습니다.
 * 기본 설정은 수직동기 기준의 (가변 프레임 + 프레임 스키핑)입니다.
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

		// 1초가 넘어가면 프레임 체크
		if (m_rFrameSec >= ONE_SECOND)
		{
			// FPS = 프레임 카운트 / 1초
			// 좀 더 정밀한 측정을 위해 (프레임 카운트 / 경과 시간)을 이용합니다.
			m_FPS = static_cast<INT32>(m_frameCnt / m_rFrameSec);
			//RXDEBUGLOG("현재 프레임 카운트 %d, FPS : %d", m_frameCnt, m_FPS);
			
			m_rFrameSec -= ONE_SECOND;
			m_frameCnt = 0;
		}
	}

} // namespace RX end