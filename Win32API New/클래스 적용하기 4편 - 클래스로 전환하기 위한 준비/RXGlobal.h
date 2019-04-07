#ifndef RX_GLOBAL_H_
#define RX_GLOBAL_H_

#include "common.h"

namespace RX
{

	class RXGlobal
	{
	public:
		RXGlobal()  = default;
		~RXGlobal() = default;

		static HINSTANCE m_hMainInstance; // 프로그램 메인 인스턴스
	};

} // namespace RX end

#endif