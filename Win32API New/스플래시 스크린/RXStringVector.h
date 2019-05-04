#ifndef RX_STRING_VECTOR_H_
#define RX_STRING_VECTOR_H_

#include "RXStandard.h"

namespace RX
{

	class RXStringVector
	{
	public:
		RXStringVector();
		~RXStringVector();

		void                AddString(const std::wstring& sz);
		void                DeleteString(const std::wstring& sz);
		const std::wstring& FindString(const std::wstring& sz);

	private:
		std::vector<std::wstring> m_vecString;
	};

} // namespace RX end

#endif