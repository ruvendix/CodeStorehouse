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
#include "RXVector2D.h"

namespace RX
{

	RXVector2D::RXVector2D()
	{
		rX = 0.0f;
		rY = 0.0f;
	}

	RXVector2D::RXVector2D(const RXVector2D& pos)
	{
		*this = pos;
	}

	RXVector2D::RXVector2D(const POINT& pt)
	{
		*this = pt;
	}

	RXVector2D::RXVector2D(FLOAT32 rX, FLOAT32 rY)
	{
		this->rX = rX;
		this->rY = rY;
	}

	RXVector2D::~RXVector2D()
	{

	}

	RXVector2D& RXVector2D::operator=(const RXVector2D& pos)
	{
		rX = pos.rX;
		rY = pos.rY;
		return *this;
	}

	RXVector2D& RXVector2D::operator=(const POINT& pt)
	{
		rX = static_cast<FLOAT32>(pt.x);
		rY = static_cast<FLOAT32>(pt.y);
		return *this;
	}

	RXVector2D RXVector2D::operator=(FLOAT32 rVal)
	{
		rX = rVal;
		rY = rVal;
		return *this;
	}

	RXVector2D RXVector2D::operator+(const RXVector2D& pos)
	{
		RXVector2D result;
		result.setValue(rX + pos.getX(), rY + pos.getY());
		return result;
	}

	RXVector2D RXVector2D::operator+(const POINT& pt)
	{
		RXVector2D result;
		result.setValue(rX + pt.x, rY + pt.y);
		return result;
	}

	RXVector2D RXVector2D::operator+(FLOAT32 rVal)
	{
		RXVector2D result;
		result.setValue(rX + rVal, rY + rVal);
		return result;
	}

	RXVector2D RXVector2D::operator+=(const RXVector2D& pos)
	{
		return (*this + pos);
	}

	RXVector2D RXVector2D::operator+=(const POINT& pt)
	{
		return (*this + pt);
	}

	RXVector2D RXVector2D::operator+=(FLOAT32 rVal)
	{
		return (*this + rVal);
	}

	RXVector2D RXVector2D::operator-(const RXVector2D& pos)
	{
		RXVector2D result;
		result.setValue(rX - pos.getX(), rY - pos.getY());
		return result;
	}

	RXVector2D RXVector2D::operator-(const POINT& pt)
	{
		RXVector2D result;
		result.setValue(rX - pt.x, rY - pt.y);
		return result;
	}

	RXVector2D RXVector2D::operator-(FLOAT32 rVal)
	{
		RXVector2D result;
		result.setValue(rX - rVal, rY - rVal);
		return result;
	}

	RXVector2D RXVector2D::operator-=(const RXVector2D& pos)
	{
		return (*this - pos);
	}

	RXVector2D RXVector2D::operator-=(const POINT& pt)
	{
		return (*this - pt);
	}

	RXVector2D RXVector2D::operator-=(FLOAT32 rVal)
	{
		return (*this - rVal);
	}

	RXVector2D RXVector2D::operator*(const RXVector2D& pos)
	{
		RXVector2D result;
		result.setValue(rX * pos.getX(), rY * pos.getY());
		return result;
	}

	RXVector2D RXVector2D::operator*(const POINT& pt)
	{
		RXVector2D result;
		result.setValue(rX * pt.x, rY * pt.y);
		return result;
	}

	RXVector2D RXVector2D::operator*(FLOAT32 rVal)
	{
		RXVector2D result;
		result.setValue(rX * rVal, rY * rVal);
		return result;
	}

	RXVector2D RXVector2D::operator*=(const RXVector2D& pos)
	{
		return (*this * pos);
	}

	RXVector2D RXVector2D::operator*=(const POINT& pt)
	{
		return (*this * pt);
	}

	RXVector2D RXVector2D::operator*=(FLOAT32 rVal)
	{
		return (*this * rVal);
	}

	RXVector2D RXVector2D::operator/(const RXVector2D& pos)
	{
		RXVector2D result;

		if ( (pos.getX() == 0.0f) ||
			 (pos.getY() == 0.0f) )
		{
			return result;
		}
		
		result.setValue(rX / pos.getX(), rY / pos.getY());
		return result;
	}

	RXVector2D RXVector2D::operator/(const POINT& pt)
	{
		RXVector2D result;

		if ( (pt.x == 0) ||
			 (pt.y == 0) )
		{
			return result;
		}

		result.setValue(rX / pt.x, rY / pt.y);
		return result;
	}

	RXVector2D RXVector2D::operator/(FLOAT32 rVal)
	{
		RXVector2D result;

		if (rVal == 0.0f)
		{
			return result;
		}

		result.setValue(rX / rVal, rY / rVal);
		return result;
	}

	RXVector2D RXVector2D::operator/=(const RXVector2D& pos)
	{
		return (*this / pos);
	}

	RXVector2D RXVector2D::operator/=(const POINT& pt)
	{
		return (*this / pt);
	}

	RXVector2D RXVector2D::operator/=(FLOAT32 rVal)
	{
		return (*this / rVal);
	}

	bool RXVector2D::operator==(const RXVector2D& pos)
	{
		if ( (SAME_FLOAT(rX, pos.getX()) == true) &&
			 (SAME_FLOAT(rY, pos.getY()) == true) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator==(const POINT& pt)
	{
		if ( (SAME_FLOAT(rX, pt.x) == true) &&
			 (SAME_FLOAT(rY, pt.y) == true) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator==(FLOAT32 rVal)
	{
		if ( (SAME_FLOAT(rX, rVal) == true) &&
			 (SAME_FLOAT(rY, rVal) == true) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator<(const RXVector2D& pos)
	{
		if ( (rX < pos.getX()) &&
			 (rY < pos.getY()) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator<(const POINT& pt)
	{
		if ( (rX < pt.x) &&
			 (rY < pt.y) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator<(FLOAT32 rVal)
	{
		if ( (rX < rVal) &&
			 (rY < rVal) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator>(const RXVector2D& pos)
	{
		if ( (rX > pos.getX()) &&
			 (rY > pos.getY()) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator>(const POINT& pt)
	{
		if ( (rX > pt.x) &&
			 (rY > pt.y) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator>(FLOAT32 rVal)
	{
		if ( (rX > rVal) &&
			 (rY > rVal) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator<=(const RXVector2D& pos)
	{
		if ( (*this == pos) ||
			 (*this < pos) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator<=(const POINT& pt)
	{
		if ( (*this == pt) ||
			 (*this < pt) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator<=(FLOAT32 rVal)
	{
		if ( (*this == rVal) ||
			 (*this < rVal) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator>=(const RXVector2D& pos)
	{
		if ( (*this == pos) ||
			 (*this > pos) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator>=(const POINT& pt)
	{
		if ( (*this == static_cast<FLOAT32>(pt.x)) ||
			 (*this > static_cast<FLOAT32>(pt.y)) )
		{
			return true;
		}

		return false;
	}

	bool RXVector2D::operator>=(FLOAT32 rVal)
	{
		if ( (*this == rVal) ||
			 (*this > rVal) )
		{
			return true;
		}

		return false;
	}

} // namespace RX end