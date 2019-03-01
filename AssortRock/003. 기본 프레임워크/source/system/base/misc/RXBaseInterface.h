/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-02
 *
 * <파일 내용>
 * OnInit, OnUpdate, OnRender, OnRelease가 있습니다.
 * 필요하면 계속 추가될 수 있습니다.
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

		// 아래에 있는 함수들은 오버라이딩 필수입니다.
		virtual HRESULT OnInit()    = 0;
		virtual HRESULT OnUpdate()  = 0;
		virtual HRESULT OnRender()  = 0;
		virtual HRESULT OnRelease() = 0;
	};

} // namespace RX end

#endif