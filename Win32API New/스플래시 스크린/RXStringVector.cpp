#include "RXStringVector.h"

namespace RX
{	

	// 비교 함수에 사용되는 클래스입니다.
	class PredSameFuncString
	{
	public:
		PredSameFuncString(const std::wstring& sz)
		{
			m_sz = sz;
		}

		bool operator() (const std::wstring& sz)
		{
			return (m_sz == sz);
		}

	private:
		std::wstring m_sz;
	};

	RXStringVector::RXStringVector()
	{
		m_vecString.reserve(10);
	}

	RXStringVector::~RXStringVector()
	{

	}

	void RXStringVector::AddString(const std::wstring& sz)
	{
		m_vecString.push_back(sz);
	}

	void RXStringVector::DeleteString(const std::wstring& sz)
	{
		std::vector<std::wstring>::iterator iter =
			std::find_if(m_vecString.begin(), m_vecString.end(), PredSameFuncString(sz));
		m_vecString.erase(iter);
	}

	const std::wstring& RXStringVector::FindString(const std::wstring& sz)
	{
		std::vector<std::wstring>::iterator iter =
			std::find_if(m_vecString.begin(), m_vecString.end(), PredSameFuncString(sz));
		return (*iter);
	}

} // namespace RX end