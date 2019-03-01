/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-08-12 (AssortRock 전용으로 수정)
 *
 * <파일 내용>
 * 시간을 다루는 클래스입니다.
 * 시간 간격이 짧은 델타타임도 구할 수 있고
 * 시간 간격이 긴 퍼포먼스타임도 구할 수 있습니다.
 *
 ====================================================================================*/
#ifndef RXTIMER_H_
#define RXTIMER_H_

#include "base\common\common.h"

namespace RX
{

	class RXTimer
	{
	public:
		RXTimer();
		~RXTimer() = default;

		// 고해상도 타이머의 주파수를 얻는다.
		// 주파수는 초당 진동수를 말하고 단위는 Hz(헤르츠)입니다.
		// 예를 들어 60Hz면 초당 60번 진동한다는 뜻입니다.
		// 주기는 1사이클(Cycle)에 걸리는 시간을 말합니다.
		// 사이클은 진동 한 번을 의미합니다. 따라서 주기는 = (1 / 주파수)입니다.
		static void InitFrequency();

		void StartTime();
		void StartHighResolutionTime();

		FLOAT32 CalcTimeInterval();
		FLOAT64 CalcHighResolutionTimeInterval();
		FLOAT32 CalcDeltaSeconds();
		FLOAT32 CalcFixedDeltaSecondsByFPS(FPS_TYPE fpsType);
		FLOAT32 CalcHighResolutionDeltaSeconds();

		// ====================================================================================
		// Getter
		FLOAT32 getDeltaSeconds() const noexcept
		{
			return m_rDeltaSeconds; // 미리 계산해둔 델타타임
		}

	private:
		bool    m_bInit;           // 타이머 첫 작동 여부입니다.
		FLOAT32 m_rDeltaSeconds;   // 프레임 간의 시간 차이입니다. 단위는 초입니다.
		DWORD   m_dwPrevFrameTime; // 이전 프레임 시간입니다. 현재 프레임은 고려하지 않습니다.

		// 고해상도 타이머입니다. LARGE_INTEGER는 8바이트 자료형입니다.
		// 고해상도 타이머의 주파수(초당 진동수)와 CPU의 클럭수를 이용합니다.
		// 주파수는 정적 변수로 분리되어있습니다.
		LARGE_INTEGER m_highPrevTick; // 이전 프레임에서 CPU의 클럭수, 현재 프레임은 고려하지 않습니다.
		static LARGE_INTEGER m_highFrequency; // CPU의 주파수
	};

} // namespace RX end
	
#endif