#ifndef RX_WINDOW_H_
#define RX_WINDOW_H_

#include "RXCommon.h"

namespace RX
{

	class RXWindow
	{
	public:
		RXWindow();
		RXWindow(const std::wstring& szWndTitle);
		virtual ~RXWindow() = default;

		// ============================================================
		// �޽��� �ڵ鷯
		virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
		virtual void OnClose(HWND hWnd);
		virtual void OnDestroy(HWND hWnd);
		virtual void OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
		virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags);
		virtual void OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
		virtual void OnRButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags);
		virtual void OnPaint(HWND hWnd);
		virtual void OnKeyDown(HWND hWnd, UINT vKey, BOOL bDown, INT32 repeat, UINT flags);
		virtual void OnSysKeyDown(HWND hWnd, UINT vk, BOOL bDown, INT32 repeat, UINT flags);
		virtual void OnCommand(HWND hWnd, INT32 id, HWND hControlWnd, UINT codeNotify);

		// ============================================================
		// ���� �Լ�
		HRESULT CreateRXWindow(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight); // �⺻��

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

		// ============================================================
		// Setter
		void setTitle(const std::wstring& szTitle)
		{
			m_szWndTitle = szTitle;
		}

		void setTitleBarTitle(const std::wstring& szTitle)
		{
			m_szWndTitle = szTitle;
			::SetWindowText(m_hWnd, szTitle.c_str());
		}

		void setClientRect(RECT rtClient)
		{
			m_rtClient = rtClient;
		}

	protected:
		std::wstring           m_szWndTitle;  // ������ �̸�
		HWND                   m_hWnd;        // ������ �ڵ�
		RECT                   m_rtClient;    // Ŭ���̾�Ʈ ����
		std::vector<RXWindow*> m_vecChildWnd; // �ڽ� ������ ���

		// �Լ� ���ø� => �Ļ� Ŭ������ �����Ƿ�...
	public:
		template <typename _Ty>
		_Ty* CreateChildRXWindow(const std::wstring& szChildClassName,
			INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwAdditionalStyle)
		{
			_Ty* pChildRXWnd = RXNew _Ty;
			pChildRXWnd->setTitle(szChildClassName); // ������ Ŭ���� �̸��� �� Ÿ��Ʋ

			DWORD dwChildStyle = WS_CHILD | WS_VISIBLE | dwAdditionalStyle;
			HWND hChildWnd = ::CreateWindow(szChildClassName.c_str(), szChildClassName.c_str(),
				dwChildStyle, x, y, clientWidth, clientHeight,
				m_hWnd, nullptr, RXGlobal::g_hMainInstance, pChildRXWnd);

			if (hChildWnd == nullptr)
			{
				ERRMSGBOX(L"�ڽ� ������ ���� ����!");
				return nullptr;
			}

			::UpdateWindow(hChildWnd);

			RECT rtClient;
			::GetClientRect(hChildWnd, &rtClient);
			pChildRXWnd->setClientRect(rtClient);

			return pChildRXWnd;
		}
	};

} // namespace RX end

#endif