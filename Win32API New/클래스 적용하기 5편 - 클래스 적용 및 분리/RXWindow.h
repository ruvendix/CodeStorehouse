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
		// �޽��� �ڵ鷯
		virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct) { return TRUE; }
		virtual void OnDestroy(HWND hWnd);

		// ============================================================
		// �� ���� �Լ�
		HRESULT Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight); // �ϴ��� �⺻������
		void         ChangeWindowTitle(const std::wstring& szWndTitle);

		// ============================================================
		// Getter
		const std::wstring getWindowTitle() const noexcept
		{
			return m_szWndTitle;
		}

	protected:
		std::wstring m_szWndTitle; // ������ �̸�
		HWND         m_hWnd;       // ������ �ڵ�
	};

} // namespace RX end

#endif