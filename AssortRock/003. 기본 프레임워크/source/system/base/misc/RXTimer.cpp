/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-12 (AssortRock �������� ����)
 *
 * <���� ����>
 * �ð��� �ٷ�� Ŭ�����Դϴ�.
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

		// �и������� ����, 1000�� 1��
		m_rDeltaSeconds = ((dwCurrentFrameTime - m_dwPrevFrameTime) * 0.001f);

		m_dwPrevFrameTime = dwCurrentFrameTime;
		return m_rDeltaSeconds;
	}

	// ������ ���� �ð����� �۴ٸ� FPS�� ���� ���� ���� �ð��� ��ȯ�մϴ�.
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

		// �и������� ����, 1000�� 1��
		m_rDeltaSeconds = ((dwCurrentFrameTime - m_dwPrevFrameTime) * 0.001f);

		if (m_rDeltaSeconds < rBaseSeconds) // ������ ���� �ð����� ���� ��
		{
			// ���� ������ �ð� ���ݸ�ŭ CPU�� �޽��մϴ�.
			// �ܼ��� �������� ���ڰ� �ƴ϶� ������ �����̸� �̴ϴ�.
			// ��, ���α׷� �ӵ��� ������ �ݴϴ�.
			FLOAT32 rSleepSeconds = (rBaseSeconds - m_rDeltaSeconds) * CLOCKS_PER_SEC;
			::SleepEx(static_cast<DWORD>(rSleepSeconds), TRUE);

			// FPS�� ���� ���� ������ �ð� ������ �����մϴ�.
			// �̹� ������ ���� ������ �ð� ���ݸ�ŭ CPU�� �޽������Ƿ� ���� �ð����� �¾ƶ������ϴ�.
			m_rDeltaSeconds = rBaseSeconds;
		}

		m_dwPrevFrameTime = dwCurrentFrameTime;
		return m_rDeltaSeconds;
	}

	// ���ػ� Ÿ�̸Ӹ� �̿��� ��Ÿ������ ��� ����Դϴ�.
	// ���� �ڵ� : http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735
	FLOAT32 RXTimer::CalcHighResolutionDeltaSeconds()
	{
		// ���� ������ CPU Ŭ������ �˾Ƴ��ϴ�.
		LARGE_INTEGER highCurrentTick;
		::QueryPerformanceCounter(&highCurrentTick);

		if (m_bInit == true)
		{
			m_highPrevTick = highCurrentTick;
			m_bInit = false;
		}

		// �и������� ������ ��Ÿ�����带 ���մϴ�.
		// (���� ������ CPU Ŭ���� - ���� ������ CPU Ŭ����)�� ���ļ��� �����ָ� �˴ϴ�.
		// ����Ʈ ������ ���Դϴ�. ��, 2.352 �̷��� �Ǹ� 2.352�ʰ� �˴ϴ�.
		m_rDeltaSeconds =
			static_cast<FLOAT32>(highCurrentTick.QuadPart - m_highPrevTick.QuadPart) /
			(m_highFrequency.QuadPart);

		// �ʴ��� �������� ���� ����մϴ�.
		//FLOAT32 rDeltaMilliSec = m_rDeltaSeconds;
		//FLOAT32 rDeltaMicroSec = m_rDeltaSeconds * 0.001f;
		//RXLOG("MilliSec(%f) MicroSec(%f)", rDeltaMilliSec, rDeltaMicroSec);

		m_highPrevTick = highCurrentTick;
		return m_rDeltaSeconds;
	}

} // namespace RX end