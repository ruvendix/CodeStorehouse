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
#include "RXPerformanceProfiler.h"

namespace RX
{

	PHOENIX_SINGLETON_INIT(RXPerformanceProfiler);

	// �� �Լ��� ���Ǵ� Ŭ�����Դϴ�.
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

		return (*iter); // ������ ã�� ����Դϴ�.
	}

	void RXPerformanceProfiler::Start(const std::string& szFuncSignautre, INT32 funcID)
	{
		RXPerformanceProfilerInfo* pPerformanceProfilerInfo = FindInfoByFuncID(funcID);
		if (pPerformanceProfilerInfo != nullptr) // �ִ� ������ Ȱ���մϴ�.
		{
			pPerformanceProfilerInfo->timer.StartTime();
			++(pPerformanceProfilerInfo->callCount);
		}
		else // ������ ���� �����մϴ�.
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
		if (pPerformanceProfilerInfo != nullptr) // �ִ� ������ Ȱ���մϴ�.
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

			RXLOG("%S ���� �ɷ� ����", m_vecPerformanceInfo[i]->szFuncSignature.c_str());
			RXLOG("ȣ�� Ƚ��      : %d", m_vecPerformanceInfo[i]->callCount);
			RXLOG("�� ���� �ð�   : %f��", m_vecPerformanceInfo[i]->rTotalPerformanceTime);

			// ��� ���� �ð�(�� ���� �ð� / ȣ�� Ƚ��)
			FLOAT64 rAveragePerformanceTime =
				m_vecPerformanceInfo[i]->rTotalPerformanceTime / m_vecPerformanceInfo[i]->callCount;
			
			if (i != size - 1)
			{
				RXLOG("��� ���� �ð� : %f��\n", rAveragePerformanceTime);
			}
			else
			{
				RXLOG("��� ���� �ð� : %f��", rAveragePerformanceTime);
			}
		}
		RXLOG("=================================================================================");
	}

} // namespace RX end