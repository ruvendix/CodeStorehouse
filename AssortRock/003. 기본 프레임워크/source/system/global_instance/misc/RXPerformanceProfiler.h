/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2019-03-01
 *
 * <���� ����>
 * �Լ��� ���� �ɷ��� �����մϴ�.
 * ���� �Լ��� ���� �ɷ��� ���ÿ� ������ �� �ֽ��ϴ�.
 *
 ====================================================================================*/
#ifndef RXPERFORMANCE_PROFILER_H_
#define RXPERFORMANCE_PROFILER_H_

#include "base\common\common.h"
#include "base\misc\RXTimer.h"

namespace RX
{

	// �����ս� �������Ϸ� ����
	struct RXPerformanceProfilerInfo
	{
		// ����ü�� ���� �⺻ �ʱ�ȭ�� �־�θ� ����� �� ���մϴ�.
		RXPerformanceProfilerInfo()
		{
			rTotalPerformanceTime = 0.0f;
			callCount = 0;
		}

		std::string szFuncSignature;       // �����Ǵ� �Լ��� �̸��� ����
		RXTimer     timer;                 // Ÿ�̸�
		FLOAT64     rTotalPerformanceTime; // �� ���� �ð�
		INT32       callCount;             // ȣ�� Ƚ��
		INT32       funcID;                // �����Ǵ� �Լ��� �ĺ��� ���� ID (__COUNTER__ Ȱ��)
	};

	class RXPerformanceProfiler
	{
		PHOENIX_SINGLETON_FULL(RXPerformanceProfiler);

	public:
		RXPerformanceProfiler();
		~RXPerformanceProfiler();

		// �Լ��� ID�� �̿��ؼ� ������ �ִ� �������� ã�ƺ��� ������ ������ ���� �����մϴ�.
		// __COUNTER__�� �����ϵǴ� ���� �������� ���� �ű�
		void Start(const std::string& szFuncSignature, INT32 funcID);

		// ���⼭�� �̹� ���� ������ �� �� �����ϴ�!
		// Start()���� ������ �����ϱ��!
		void End(INT32 funcID);

		// ��� �Լ��� ���� ����� �����մϴ�.
		// ���� ȣ������ �ʴ´ٸ� �Ҹ��ڿ��� �ڵ� ȣ��˴ϴ�.
		void Report();

	private:
		// �Լ��� ID�� ������ ã���ϴ�.
		RXPerformanceProfilerInfo* FindInfoByFuncID(INT32 funcID);

		std::vector<RXPerformanceProfilerInfo*> m_vecPerformanceInfo;
	};

} // namespace RX end

#endif