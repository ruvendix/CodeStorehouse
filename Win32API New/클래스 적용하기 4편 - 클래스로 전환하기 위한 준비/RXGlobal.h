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

		static HINSTANCE m_hMainInstance; // ���α׷� ���� �ν��Ͻ�
	};

} // namespace RX end

#endif