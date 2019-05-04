#ifndef RX_GLOBAL_H_
#define RX_GLOBAL_H_

#include "RXStandard.h"
#include "RXStringVector.h"

namespace RX
{

	namespace RXGlobal
	{

		// Create은 부가 정보를 곁들여서 아예 처음부터 만드는 것
		// Make는 전달된 정보들을 잘 섞어서 만드는 것
		// 그게 그거이긴 함...
		std::wstring MakeFormatString(const WCHAR* szFormat, ...);
		
		// 선분 하나를 긋는 헬퍼
		// 이 함수를 호출한 다음 LineTo()를 계속 호출하면 선이 이어짐
		void DrawLineSegment(HDC hDC, INT32 startX, INT32 startY, INT32 endX, INT32 endY);

		// 자식 윈도우의 좌표를 부모 윈도우의 클라이언트 영역 좌표로 변환
		RECT ConvertChildToParentClientRect(HWND hChildWnd);

		// Rectangle()을 좀 더 쉽게 사용하기 위해
		void DrawRect(HDC hDC, const RECT& rt);

		// 원하는 클라이언트 영역으로 전체 영역을 변경해줌
		void AdjustClientRect(HWND hWnd, INT32 width, INT32 height);

		// 투명 부분으로 설정한 컬러키 부분을 제외시키고 그려주는 비트맵
		void DrawBimapExcludeColorKey(HDC hDC, HBITMAP hBitmap,
			INT32 x, INT32 y, COLORREF colorKey, bool bCenter);

		// 프로그램을 모니터 가운데로 위치시켜줄 위치를 알려줌
		POINT CalcCenterPosByScreen(INT32 width, INT32 height);

		// 외부에서 사용하는 전역변수는 extern 표시 필수!
		extern HINSTANCE      g_hMainInstance;           // 프로그램 메인 인스턴스
		extern RXStringVector g_windowClassStringVector; // 윈도우 클래스 이름 모음
		extern bool           g_bRunMainWindow;          // 프로그램 메인 윈도우 작동 여부

		// ==========================================================
		// 템플릿 함수
		template <typename _Ty>
		void SafeDeleteVector(_Ty* pVec)
		{
			if (pVec == nullptr)
			{
				return;
			}

			// ========================================================================
			// 벡터는 이렇게 삭제하는 게 더 편함
			INT32 size = pVec->size();
			for (INT32 i = 0; i < size; ++i)
			{
				SAFE_DELETE((*pVec)[i]);
			}
			// ========================================================================

			// ========================================================================
			// 이건 이터레이터를 사용한 방식
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
			pChildRXWnd->setTitle(szChildClassName); // 윈도우 클래스 이름이 곧 타이틀

			DWORD dwChildStyle = WS_CHILD | WS_VISIBLE | dwAdditionalStyle;
			HWND hChildWnd = ::CreateWindow(szChildClassName.c_str(), szChildClassName.c_str(),
				dwChildStyle, x, y, clientWidth, clientHeight,
				hParentWnd, nullptr, RXGlobal::g_hMainInstance, pChildRXWnd);

			if (hChildWnd == nullptr)
			{
				ERRMSGBOX(L"자식 윈도우 생성 실패!");
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