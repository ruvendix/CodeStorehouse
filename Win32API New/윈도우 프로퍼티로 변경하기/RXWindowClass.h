#ifndef RX_WINDOW_CLASS_H
#define RX_WINDOW_CLASS_H

#include "RXCommon.h"

namespace RX
{

	class RXWindowClass
	{
	public:
		RXWindowClass()          = default;
		virtual ~RXWindowClass() = default;

		virtual HRESULT Init(const std::wstring& szWndClass);

		HRESULT RegisterWindowClass();

		// ============================================================
		// Getter
		const std::wstring getWindowClassName() const noexcept
		{
			return m_wcex.lpszClassName;
		}

		// ============================================================
		// Setter
		void setWindowClassName(const std::wstring& szWndClass)
		{
			m_szWndClass = szWndClass;
			m_wcex.lpszClassName = m_szWndClass.c_str();
		}

		void setBackgroundBrush(HBRUSH hBrush)
		{
			m_wcex.hbrBackground = hBrush;
		}

		void setMouseCursor(HCURSOR hCursor)
		{
			m_wcex.hCursor = hCursor;
		}

	private:
		static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message,
			WPARAM wParam, LPARAM lParam);

		WNDCLASSEX   m_wcex;
		std::wstring m_szWndClass;
	};

} // namespace RX end

#endif