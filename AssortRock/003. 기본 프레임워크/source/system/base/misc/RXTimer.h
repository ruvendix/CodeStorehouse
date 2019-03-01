/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-12 (AssortRock �������� ����)
 *
 * <���� ����>
 * �ð��� �ٷ�� Ŭ�����Դϴ�.
 * �ð� ������ ª�� ��ŸŸ�ӵ� ���� �� �ְ�
 * �ð� ������ �� �����ս�Ÿ�ӵ� ���� �� �ֽ��ϴ�.
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

		// ���ػ� Ÿ�̸��� ���ļ��� ��´�.
		// ���ļ��� �ʴ� �������� ���ϰ� ������ Hz(�츣��)�Դϴ�.
		// ���� ��� 60Hz�� �ʴ� 60�� �����Ѵٴ� ���Դϴ�.
		// �ֱ�� 1����Ŭ(Cycle)�� �ɸ��� �ð��� ���մϴ�.
		// ����Ŭ�� ���� �� ���� �ǹ��մϴ�. ���� �ֱ�� = (1 / ���ļ�)�Դϴ�.
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
			return m_rDeltaSeconds; // �̸� ����ص� ��ŸŸ��
		}

	private:
		bool    m_bInit;           // Ÿ�̸� ù �۵� �����Դϴ�.
		FLOAT32 m_rDeltaSeconds;   // ������ ���� �ð� �����Դϴ�. ������ ���Դϴ�.
		DWORD   m_dwPrevFrameTime; // ���� ������ �ð��Դϴ�. ���� �������� ������� �ʽ��ϴ�.

		// ���ػ� Ÿ�̸��Դϴ�. LARGE_INTEGER�� 8����Ʈ �ڷ����Դϴ�.
		// ���ػ� Ÿ�̸��� ���ļ�(�ʴ� ������)�� CPU�� Ŭ������ �̿��մϴ�.
		// ���ļ��� ���� ������ �и��Ǿ��ֽ��ϴ�.
		LARGE_INTEGER m_highPrevTick; // ���� �����ӿ��� CPU�� Ŭ����, ���� �������� ������� �ʽ��ϴ�.
		static LARGE_INTEGER m_highFrequency; // CPU�� ���ļ�
	};

} // namespace RX end
	
#endif