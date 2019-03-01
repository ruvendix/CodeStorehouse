/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-02
 *
 * <파일 내용>
 * 게임 프로그램의 핵심 루틴입니다.
 *
 ====================================================================================*/
#ifndef RXCORE_H_
#define RXCORE_H_

#include "base\common\common.h"

namespace RX
{

	class RXCore : public RXBaseInterface
	{
		PHOENIX_SINGLETON_CTOR(RXCore);

	public:
		static LRESULT CALLBACK WindowProcedure(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		RXCore();

		virtual HRESULT OnInit()    override;
		virtual HRESULT OnUpdate()  override;
		virtual HRESULT OnRender()  override;
		virtual HRESULT OnRelease() override;

		HRESULT OnDrive();
		HRESULT CreateWindowClass();
		HRESULT RegisterWindowClass(const WNDCLASSEX& wcex);
		HRESULT CreateProgramWindow();

		// ====================================================================================
		// Getter
		// ====================================================================================
		HINSTANCE getProgramInstance() const noexcept
		{
			return m_hInst;
		}

		HWND getMainWindowHandle() const noexcept
		{
			return m_hMainWnd;
		}

		INT32 getMessageCode() const noexcept
		{
			return m_msgCode;
		}

		// ====================================================================================
		// Setter
		// ====================================================================================

	private:
		HINSTANCE      m_hInst;
		HWND           m_hMainWnd;
		HDC            m_hDC;
		INT32          m_msgCode;
		ResolutionInfo m_resolutionInfo;
	};

} // namespace RX end

#endif