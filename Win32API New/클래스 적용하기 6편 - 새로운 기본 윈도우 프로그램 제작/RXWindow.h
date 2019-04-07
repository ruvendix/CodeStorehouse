#ifndef RX_WINDOW_H_
#define RX_WINDOW_H_

#include "common.h"

namespace RX
{

	class RXWindow
	{
	public:
		RXWindow();
		RXWindow(const std::wstring& szWndTtile);
		virtual ~RXWindow() = default;

		// ============================================================
		// �޽��� �ڵ鷯
		virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
		virtual void OnClose(HWND hWnd);
		virtual void OnDestroy(HWND hWnd);
		virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, 
			INT32 x, INT32 y, UINT keyFlags);

		// ============================================================
		// �� ���� �Լ�
		HRESULT Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight); // �ϴ��� �⺻������
		void    ChangeWindowTitle(const std::wstring& szWndTitle);

		// ============================================================
		// Getter
		std::pair<INT32, INT32> getClientWidthAndHeight() const noexcept;
		
		INT32 getClientWidth() const noexcept
		{
			return (m_rtClient.right - m_rtClient.left);
		}

		INT32 getClientHeight() const noexcept
		{
			return (m_rtClient.bottom - m_rtClient.top);
		}

		const std::wstring getWindowTitle() const noexcept
		{
			return m_szWndTitle;
		}

	protected:
		std::wstring m_szWndTitle; // ������ �̸�
		HWND         m_hWnd;       // ������ �ڵ�
		RECT         m_rtClient;   // Ŭ���̾�Ʈ ����
	};

} // namespace RX end

#endif