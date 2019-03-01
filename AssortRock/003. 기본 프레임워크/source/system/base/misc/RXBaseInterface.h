/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2019-02-02
 *
 * <���� ����>
 * OnInit, OnUpdate, OnRender, OnRelease�� �ֽ��ϴ�.
 * �ʿ��ϸ� ��� �߰��� �� �ֽ��ϴ�.
 *
 ====================================================================================*/
#ifndef RXBASE_INTERFACE_H_
#define RXBASE_INTERFACE_H_

#include "..\common\common.h"

namespace RX
{

	class RXBaseInterface
	{
	public:
		RXBaseInterface()  = default;
		~RXBaseInterface() = default;

		// �Ʒ��� �ִ� �Լ����� �������̵� �ʼ��Դϴ�.
		virtual HRESULT OnInit()    = 0;
		virtual HRESULT OnUpdate()  = 0;
		virtual HRESULT OnRender()  = 0;
		virtual HRESULT OnRelease() = 0;
	};

} // namespace RX end

#endif