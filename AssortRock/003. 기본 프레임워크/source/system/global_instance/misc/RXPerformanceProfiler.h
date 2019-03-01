/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-03-01
 *
 * <파일 내용>
 * 함수의 수행 능력을 측정합니다.
 * 여러 함수의 수행 능력을 동시에 측정할 수 있습니다.
 *
 ====================================================================================*/
#ifndef RXPERFORMANCE_PROFILER_H_
#define RXPERFORMANCE_PROFILER_H_

#include "base\common\common.h"
#include "base\misc\RXTimer.h"

namespace RX
{

	// 퍼포먼스 프로파일러 정보
	struct RXPerformanceProfilerInfo
	{
		// 구조체도 변수 기본 초기화를 넣어두면 사용할 때 편합니다.
		RXPerformanceProfilerInfo()
		{
			rTotalPerformanceTime = 0.0f;
			callCount = 0;
		}

		std::string szFuncSignature;       // 측정되는 함수의 이름과 형식
		RXTimer     timer;                 // 타이머
		FLOAT64     rTotalPerformanceTime; // 총 수행 시간
		INT32       callCount;             // 호출 횟수
		INT32       funcID;                // 측정되는 함수의 식별을 위한 ID (__COUNTER__ 활용)
	};

	class RXPerformanceProfiler
	{
		PHOENIX_SINGLETON_FULL(RXPerformanceProfiler);

	public:
		RXPerformanceProfiler();
		~RXPerformanceProfiler();

		// 함수의 ID를 이용해서 기존에 있는 정보인지 찾아보고 없으면 정보를 새로 생성합니다.
		// __COUNTER__는 컴파일되는 라인 기준으로 값을 매김
		void Start(const std::string& szFuncSignature, INT32 funcID);

		// 여기서는 이미 없는 정보가 올 수 없습니다!
		// Start()에서 무조건 넣으니까요!
		void End(INT32 funcID);

		// 모든 함수의 측정 결과를 보고합니다.
		// 따로 호출하지 않는다면 소멸자에서 자동 호출됩니다.
		void Report();

	private:
		// 함수의 ID로 정보를 찾습니다.
		RXPerformanceProfilerInfo* FindInfoByFuncID(INT32 funcID);

		std::vector<RXPerformanceProfilerInfo*> m_vecPerformanceInfo;
	};

} // namespace RX end

#endif