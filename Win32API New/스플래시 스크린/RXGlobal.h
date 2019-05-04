#ifndef RX_GLOBAL_H_
#define RX_GLOBAL_H_

#include "RXStandard.h"
#include "RXStringVector.h"

namespace RX
{

	namespace RXGlobal
	{

		// Create�� �ΰ� ������ ��鿩�� �ƿ� ó������ ����� ��
		// Make�� ���޵� �������� �� ��� ����� ��
		// �װ� �װ��̱� ��...
		std::wstring MakeFormatString(const WCHAR* szFormat, ...);
		
		// ���� �ϳ��� �ߴ� ����
		// �� �Լ��� ȣ���� ���� LineTo()�� ��� ȣ���ϸ� ���� �̾���
		void DrawLineSegment(HDC hDC, INT32 startX, INT32 startY, INT32 endX, INT32 endY);

		// �ڽ� �������� ��ǥ�� �θ� �������� Ŭ���̾�Ʈ ���� ��ǥ�� ��ȯ
		RECT ConvertChildToParentClientRect(HWND hChildWnd);

		// Rectangle()�� �� �� ���� ����ϱ� ����
		void DrawRect(HDC hDC, const RECT& rt);

		// ���ϴ� Ŭ���̾�Ʈ �������� ��ü ������ ��������
		void AdjustClientRect(HWND hWnd, INT32 width, INT32 height);

		// ���� �κ����� ������ �÷�Ű �κ��� ���ܽ�Ű�� �׷��ִ� ��Ʈ��
		void DrawBimapExcludeColorKey(HDC hDC, HBITMAP hBitmap,
			INT32 x, INT32 y, COLORREF colorKey, bool bCenter);

		// ���α׷��� ����� ����� ��ġ������ ��ġ�� �˷���
		POINT CalcCenterPosByScreen(INT32 width, INT32 height);

		// �ܺο��� ����ϴ� ���������� extern ǥ�� �ʼ�!
		extern HINSTANCE      g_hMainInstance;           // ���α׷� ���� �ν��Ͻ�
		extern RXStringVector g_windowClassStringVector; // ������ Ŭ���� �̸� ����
		extern bool           g_bRunMainWindow;          // ���α׷� ���� ������ �۵� ����

		// ==========================================================
		// ���ø� �Լ�
		template <typename _Ty>
		void SafeDeleteVector(_Ty* pVec)
		{
			if (pVec == nullptr)
			{
				return;
			}

			// ========================================================================
			// ���ʹ� �̷��� �����ϴ� �� �� ����
			INT32 size = pVec->size();
			for (INT32 i = 0; i < size; ++i)
			{
				SAFE_DELETE((*pVec)[i]);
			}
			// ========================================================================

			// ========================================================================
			// �̰� ���ͷ����͸� ����� ���
			//typename _Ty::iterator iterBegin = pVec->begin();
			//typename _Ty::iterator iterEnd   = pVec->end();

			//for (typename _Ty::iterator iter = iterBegin; iter != iterEnd; ++iter)
			//{
			//	SAFE_DELETE(*iter);
			//}
			// ========================================================================
		}

		template <typename _Ty>
		_Ty* CreateChildRXWindow(HWND hParentWnd, const std::wstring& szChildClassName,
			INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwAdditionalStyle)
		{
			_Ty* pChildRXWnd = RXNew _Ty;
			pChildRXWnd->setTitle(szChildClassName); // ������ Ŭ���� �̸��� �� Ÿ��Ʋ

			DWORD dwChildStyle = WS_CHILD | WS_VISIBLE | dwAdditionalStyle;
			HWND hChildWnd = ::CreateWindow(szChildClassName.c_str(), szChildClassName.c_str(),
				dwChildStyle, x, y, clientWidth, clientHeight,
				hParentWnd, nullptr, RXGlobal::g_hMainInstance, pChildRXWnd);

			if (hChildWnd == nullptr)
			{
				ERRMSGBOX(L"�ڽ� ������ ���� ����!");
				return nullptr;
			}

			pChildRXWnd->setWindowHandle(hChildWnd);
			::UpdateWindow(hChildWnd);

			RECT rtClient;
			::GetClientRect(hChildWnd, &rtClient);
			pChildRXWnd->setClientRect(rtClient);

			return pChildRXWnd;
		}

	}; // namespace RXGlobal end

} // namespace RX end

#endif