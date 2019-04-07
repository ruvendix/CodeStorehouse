#ifndef RX_WINDOW_H_
#define RX_WINDOW_H_

#include "common.h"

namespace RX
{

	class RXWindow
	{
	public:
		RXWindow(const std::wstring& szWndTtile);
		virtual ~RXWindow() = default;

		// ============================================================
		// 메시지 핸들러
		virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct) { return TRUE; }
		virtual void OnDestroy(HWND hWnd);

		// ============================================================
		// 그 외의 함수
		HRESULT Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight); // 일단은 기본형으로
		void         ChangeWindowTitle(const std::wstring& szWndTitle);

		// ============================================================
		// Getter
		const std::wstring getWindowTitle() const noexcept
		{
			return m_szWndTitle;
		}

	protected:
		std::wstring m_szWndTitle; // 윈도우 이름
		HWND         m_hWnd;       // 윈도우 핸들
	};

} // namespace RX end

#endif