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
#include "RXPerformanceProfiler.h"

namespace RX
{

	PHOENIX_SINGLETON_INIT(RXPerformanceProfiler);

	// 비교 함수에 사용되는 클래스입니다.
	class PredSameFuncID
	{
	public:
		PredSameFuncID(INT32 funcID)
		{
			m_szFuncID = funcID;
		}

		bool operator() (const RXPerformanceProfilerInfo* pPerformanceProfilerInfo)
		{
			if (pPerformanceProfilerInfo == nullptr)
			{
				return false;
			}

			return (m_szFuncID == pPerformanceProfilerInfo->funcID);
		}

	private:
		INT32 m_szFuncID;
	};
	
	RXPerformanceProfiler::RXPerformanceProfiler()
	{
		m_vecPerformanceInfo.reserve(10);
	}

	RXPerformanceProfiler::~RXPerformanceProfiler()
	{
		Report();
		ALL_DELETE_FOR_VECTOR(m_vecPerformanceInfo);
		m_bDestroy = true;
	}

	RXPerformanceProfilerInfo* RXPerformanceProfiler::FindInfoByFuncID(INT32 funcID)
	{
		std::vector<RXPerformanceProfilerInfo*>::iterator iter;
		std::vector<RXPerformanceProfilerInfo*>::iterator iterEnd = m_vecPerformanceInfo.end();
		iter = std::find_if(m_vecPerformanceInfo.begin(), iterEnd, PredSameFuncID(funcID));

		if (iter == m_vecPerformanceInfo.end())
		{
			return nullptr;
		}

		return (*iter); // 정보를 찾은 경우입니다.
	}

	void RXPerformanceProfiler::Start(const std::string& szFuncSignautre, INT32 funcID)
	{
		RXPerformanceProfilerInfo* pPerformanceProfilerInfo = FindInfoByFuncID(funcID);
		if (pPerformanceProfilerInfo != nullptr) // 있는 정보를 활용합니다.
		{
			pPerformanceProfilerInfo->timer.StartTime();
			++(pPerformanceProfilerInfo->callCount);
		}
		else // 정보를 새로 생성합니다.
		{
			pPerformanceProfilerInfo = RXNew RXPerformanceProfilerInfo;
			pPerformanceProfilerInfo->szFuncSignature = szFuncSignautre;
			pPerformanceProfilerInfo->funcID = funcID;
			pPerformanceProfilerInfo->timer.StartTime();
			++(pPerformanceProfilerInfo->callCount);
			m_vecPerformanceInfo.push_back(pPerformanceProfilerInfo);
		}
	}

	void RXPerformanceProfiler::End(INT32 funcID)
	{
		RXPerformanceProfilerInfo* pPerformanceProfilerInfo = FindInfoByFuncID(funcID);
		if (pPerformanceProfilerInfo != nullptr) // 있는 정보를 활용합니다.
		{
			pPerformanceProfilerInfo->rTotalPerformanceTime +=
				pPerformanceProfilerInfo->timer.CalcTimeInterval();
		}
	}

	void RXPerformanceProfiler::Report()
	{
		RXLOG("=================================================================================");
		INT32 size = m_vecPerformanceInfo.size();
		for (INT32 i = 0; i < size; ++i)
		{
			if (m_vecPerformanceInfo[i] == nullptr)
			{
				continue;
			}

			RXLOG("%S 수행 능력 보고", m_vecPerformanceInfo[i]->szFuncSignature.c_str());
			RXLOG("호출 횟수      : %d", m_vecPerformanceInfo[i]->callCount);
			RXLOG("총 수행 시간   : %f초", m_vecPerformanceInfo[i]->rTotalPerformanceTime);

			// 평균 수행 시간(총 수행 시간 / 호출 횟수)
			FLOAT64 rAveragePerformanceTime =
				m_vecPerformanceInfo[i]->rTotalPerformanceTime / m_vecPerformanceInfo[i]->callCount;
			
			if (i != size - 1)
			{
				RXLOG("평균 수행 시간 : %f초\n", rAveragePerformanceTime);
			}
			else
			{
				RXLOG("평균 수행 시간 : %f초", rAveragePerformanceTime);
			}
		}
		RXLOG("=================================================================================");
	}

} // namespace RX end