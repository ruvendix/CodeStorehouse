#ifndef RX_WINDOW_CLASS_H
#define RX_WINDOW_CLASS_H

#include "common.h"

namespace RX
{

	class RXWindowClass
	{
	public:
		HRESULT Init(const std::wstring& szWndClass);

	private:
		static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message,
			WPARAM wParam, LPARAM lParam);
	};

} // namespace RX end

#endif