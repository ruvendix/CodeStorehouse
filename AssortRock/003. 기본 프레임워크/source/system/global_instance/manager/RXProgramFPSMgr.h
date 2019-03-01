/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-10-21 (AssortRock 전용으로 수정)
 *
 * <파일 내용>
 * 프로그램의 프레임을 관리합니다.
 * 단순히 FPS를 측정하는 것 말고도 FPS에 따른 딜레이도 줄 수 있습니다.
 * 기본 설정은 수직동기 기준의 (가변 프레임 + 프레임 스키핑)입니다.
 *
 ====================================================================================*/
#ifndef RXPROGRAM_FPS_MANAGER_H_
#define RXPROGRAM_FPS_MANAGER_H_

#include "base\common\common.h"
#include "base\misc\RXTimer.h"

namespace RX
{

	class RXProgramFPSMgr
	{
		PHOENIX_SINGLETON_CTOR(RXProgramFPSMgr);

	public:
		static const FLOAT32 ONE_SECOND;
		static const FLOAT32 FIXED_DELTASECONDS_60FPS;
		static const FLOAT32 FIXED_DELTASECONDS_30FPS;

	public:
		RXProgramFPSMgr();

		// 전체 프레임을 업데이트합니다.
		void UpdateFrame();

		// ====================================================================================
		// Getter
		// ====================================================================================
		FLOAT32 getTimeScale() const noexcept
		{
			return m_rTimeScale;
		}

		const RXTimer* getTimer() const noexcept
		{
			return &m_frameTimer;
		}

		// ====================================================================================
		// Setter
		// ====================================================================================
		void setTimeScale(FLOAT32 rTimeScale)
		{
			m_rTimeScale = rTimeScale;
		}

	private:
		INT32   m_frameCnt;   // 프레임 개수입니다.
		FLOAT32   m_rFrameSec;  // 프레임 누적 시간입니다.
		FLOAT32   m_rTimeScale; // 타임스케일입니다. (값이 크면 빨라지고, 작으면 느려집니다)
		DWORD   m_FPS;        // 초당 프레임 개수입니다. (Frame Per Second)
		RXTimer m_frameTimer; // 프레임을 측정하기 위한 타이머입니다.
		WCHAR   m_szFPS[DEFAULT_STRING_LENGTH]; // 프레임을 문자열로 저장하기 위한 것입니다.
	};

} // namespace RX end

#endif