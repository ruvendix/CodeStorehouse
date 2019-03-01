/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-21 (AssortRock �������� ����)
 *
 * <���� ����>
 * ���α׷��� �������� �����մϴ�.
 * �ܼ��� FPS�� �����ϴ� �� ���� FPS�� ���� �����̵� �� �� �ֽ��ϴ�.
 * �⺻ ������ �������� ������ (���� ������ + ������ ��Ű��)�Դϴ�.
 *
 ====================================================================================*/
#ifndef RXPROGRAM_FPS_MANAGER_H_
#define RXPROGRAM_FPS_MANAGER_H_

#include "base\common\common.h"
#include "base\misc\RXTimer.h"

namespace RX
{

	class RXProgramFPSMgr
	{
		PHOENIX_SINGLETON_CTOR(RXProgramFPSMgr);

	public:
		static const FLOAT32 ONE_SECOND;
		static const FLOAT32 FIXED_DELTASECONDS_60FPS;
		static const FLOAT32 FIXED_DELTASECONDS_30FPS;

	public:
		RXProgramFPSMgr();

		// ��ü �������� ������Ʈ�մϴ�.
		void UpdateFrame();

		// ====================================================================================
		// Getter
		// ====================================================================================
		FLOAT32 getTimeScale() const noexcept
		{
			return m_rTimeScale;
		}

		const RXTimer* getTimer() const noexcept
		{
			return &m_frameTimer;
		}

		// ====================================================================================
		// Setter
		// ====================================================================================
		void setTimeScale(FLOAT32 rTimeScale)
		{
			m_rTimeScale = rTimeScale;
		}

	private:
		INT32   m_frameCnt;   // ������ �����Դϴ�.
		FLOAT32   m_rFrameSec;  // ������ ���� �ð��Դϴ�.
		FLOAT32   m_rTimeScale; // Ÿ�ӽ������Դϴ�. (���� ũ�� ��������, ������ �������ϴ�)
		DWORD   m_FPS;        // �ʴ� ������ �����Դϴ�. (Frame Per Second)
		RXTimer m_frameTimer; // �������� �����ϱ� ���� Ÿ�̸��Դϴ�.
		WCHAR   m_szFPS[DEFAULT_STRING_LENGTH]; // �������� ���ڿ��� �����ϱ� ���� ���Դϴ�.
	};

} // namespace RX end

#endif