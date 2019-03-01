/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2019-02-07
 *
 * <파일 내용>
 * 2D 좌표입니다.
 * 점과 벡터 둘 다 포함되는 개념입니다.
 *
 ====================================================================================*/
#ifndef RXVECTOR2D_H_
#define RXVECTOR2D_H_

#include "base\common\common.h"

namespace RX
{

	class RXVector2D
	{
	public:
		RXVector2D();
		RXVector2D(const RXVector2D& pos);
		explicit RXVector2D(const POINT& pt);
		RXVector2D(FLOAT32 rX, FLOAT32 rY);
		~RXVector2D();

		// ====================================================================================
		// Getter
		// ====================================================================================
		RXVector2D getValue() const noexcept
		{
			return *this;
		}

		FLOAT32 getX() const noexcept
		{
			return rX;
		}

		FLOAT32 getY() const noexcept
		{
			return rY;
		}

		// ====================================================================================
		// Setter
		// ====================================================================================
		void setValue(const RXVector2D& pos)
		{
			*this = pos;
		}

		void setValue(const POINT& pt)
		{
			*this = pt;
		}

		void setValue(FLOAT32 rX, FLOAT32 rY)
		{
			this->rX = rX;
			this->rY = rY;
		}

		// ====================================================================================
		// Operator
		// ====================================================================================
		RXVector2D& operator=(const RXVector2D& pos);
		RXVector2D& operator=(const POINT& pt);
		RXVector2D  operator=(FLOAT32 rVal);

		RXVector2D  operator+(const RXVector2D& pos);
		RXVector2D  operator+(const POINT& pt);
		RXVector2D  operator+(FLOAT32 rVal);

		RXVector2D  operator+=(const RXVector2D& pos);
		RXVector2D  operator+=(const POINT& pt);
		RXVector2D  operator+=(FLOAT32 rVal);
				    
		RXVector2D  operator-(const RXVector2D& pos);
		RXVector2D  operator-(const POINT& pt);
		RXVector2D  operator-(FLOAT32 rVal);

		RXVector2D  operator-=(const RXVector2D& pos);
		RXVector2D  operator-=(const POINT& pt);
		RXVector2D  operator-=(FLOAT32 rVal);
				    
		RXVector2D  operator*(const RXVector2D& pos);
		RXVector2D  operator*(const POINT& pt);
		RXVector2D  operator*(FLOAT32 rVal);

		RXVector2D  operator*=(const RXVector2D& pos);
		RXVector2D  operator*=(const POINT& pt);
		RXVector2D  operator*=(FLOAT32 rVal);
				    
		RXVector2D  operator/(const RXVector2D& pos);
		RXVector2D  operator/(const POINT& pt);
		RXVector2D  operator/(FLOAT32 rVal);

		RXVector2D  operator/=(const RXVector2D& pos);
		RXVector2D  operator/=(const POINT& pt);
		RXVector2D  operator/=(FLOAT32 rVal);

		bool operator==(const RXVector2D& pos);
		bool operator==(const POINT& pt);
		bool operator==(FLOAT32 rVal);

		bool operator<(const RXVector2D& pos);
		bool operator<(const POINT& pt);
		bool operator<(FLOAT32 rVal);

		bool operator>(const RXVector2D& pos);
		bool operator>(const POINT& pt);
		bool operator>(FLOAT32 rVal);

		bool operator<=(const RXVector2D& pos);
		bool operator<=(const POINT& pt);
		bool operator<=(FLOAT32 rVal);

		bool operator>=(const RXVector2D& pos);
		bool operator>=(const POINT& pt);
		bool operator>=(FLOAT32 rVal);

	private:
		FLOAT32 rX;
		FLOAT32 rY;
	};

} // namespace RX end

#endif