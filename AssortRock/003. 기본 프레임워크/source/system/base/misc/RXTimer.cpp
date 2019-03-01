/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-08-12 (AssortRock 전용으로 수정)
 *
 * <파일 내용>
 * 시간을 다루는 클래스입니다.
 *
 ====================================================================================*/
#include "RXTimer.h"

namespace RX
{

	LARGE_INTEGER RXTimer::m_highFrequency;

	RXTimer::RXTimer()
	{
		m_bInit = true;
	}

	void RXTimer::InitFrequency()
	{
		::QueryPerformanceFrequency(&m_highFrequency);
	}

	void RXTimer::StartTime()
	{
		m_dwPrevFrameTime = ::timeGetTime();
	}

	void RXTimer::StartHighResolutionTime()
	{
		::QueryPerformanceCounter(&m_highPrevTick);
	}

	FLOAT32 RXTimer::CalcTimeInterval()
	{
		DWORD dwEndTime = ::timeGetTime();
		FLOAT32 rTimeInterval = ((dwEndTime - m_dwPrevFrameTime) * 0.001f);
		return rTimeInterval;
	}

	FLOAT64 RXTimer::CalcHighResolutionTimeInterval()
	{
		LARGE_INTEGER endTime;
		::QueryPerformanceCounter(&endTime);
		FLOAT64 rTimeInterval =
			(endTime.QuadPart - m_highPrevTick.QuadPart) / static_cast<FLOAT64>(m_highFrequency.QuadPart);
		return rTimeInterval;
	}

	FLOAT32 RXTimer::CalcDeltaSeconds()
	{
		DWORD dwCurrentFrameTime = ::timeGetTime();

		if (m_bInit == true)
		{
			m_dwPrevFrameTime = dwCurrentFrameTime;
			m_bInit = false;
		}

		// 밀리세컨드 단위, 1000이 1초
		m_rDeltaSeconds = ((dwCurrentFrameTime - m_dwPrevFrameTime) * 0.001f);

		m_dwPrevFrameTime = dwCurrentFrameTime;
		return m_rDeltaSeconds;
	}

	// 프레임 간격 시간보다 작다면 FPS에 따른 고정 간격 시간을 반환합니다.
	FLOAT32 RXTimer::CalcFixedDeltaSecondsByFPS(FPS_TYPE fpsType)
	{
		FLOAT32 rBaseSeconds = 0.0f;
		(fpsType == FPS_TYPE::SIXTY) ?
			(rBaseSeconds = FIXED_DELTASECONDS_60FPS) : (rBaseSeconds = FIXED_DELTASECONDS_30FPS);

		DWORD dwCurrentFrameTime = ::timeGetTime();

		if (m_bInit == true)
		{
			m_dwPrevFrameTime = dwCurrentFrameTime;
			m_bInit = false;
		}

		// 밀리세컨드 단위, 1000이 1초
		m_rDeltaSeconds = ((dwCurrentFrameTime - m_dwPrevFrameTime) * 0.001f);

		if (m_rDeltaSeconds < rBaseSeconds) // 프레임 간격 시간보다 작을 때
		{
			// 남은 프레임 시간 간격만큼 CPU를 휴식합니다.
			// 단순히 보여지는 숫자가 아니라 실제로 딜레이를 겁니다.
			// 즉, 프로그램 속도에 영향을 줍니다.
			FLOAT32 rSleepSeconds = (rBaseSeconds - m_rDeltaSeconds) * CLOCKS_PER_SEC;
			::SleepEx(static_cast<DWORD>(rSleepSeconds), TRUE);

			// FPS에 따른 고정 프레임 시간 간격을 대입합니다.
			// 이미 위에서 남은 프레임 시간 간격만큼 CPU가 휴식했으므로 실제 시간과도 맞아떨어집니다.
			m_rDeltaSeconds = rBaseSeconds;
		}

		m_dwPrevFrameTime = dwCurrentFrameTime;
		return m_rDeltaSeconds;
	}

	// 고해상도 타이머를 이용한 델타세컨드 계산 방법입니다.
	// 참고 코드 : http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735
	FLOAT32 RXTimer::CalcHighResolutionDeltaSeconds()
	{
		// 현재 시점의 CPU 클럭수를 알아냅니다.
		LARGE_INTEGER highCurrentTick;
		::QueryPerformanceCounter(&highCurrentTick);

		if (m_bInit == true)
		{
			m_highPrevTick = highCurrentTick;
			m_bInit = false;
		}

		// 밀리세컨드 단위로 델타세컨드를 구합니다.
		// (현재 시점의 CPU 클럭수 - 이전 시점의 CPU 클럭수)에 주파수를 나눠주면 됩니다.
		// 디폴트 단위는 초입니다. 즉, 2.352 이렇게 되면 2.352초가 됩니다.
		m_rDeltaSeconds =
			static_cast<FLOAT32>(highCurrentTick.QuadPart - m_highPrevTick.QuadPart) /
			(m_highFrequency.QuadPart);

		// 초단위 기준으로 값을 출력합니다.
		//FLOAT32 rDeltaMilliSec = m_rDeltaSeconds;
		//FLOAT32 rDeltaMicroSec = m_rDeltaSeconds * 0.001f;
		//RXLOG("MilliSec(%f) MicroSec(%f)", rDeltaMilliSec, rDeltaMicroSec);

		m_highPrevTick = highCurrentTick;
		return m_rDeltaSeconds;
	}

} // namespace RX end