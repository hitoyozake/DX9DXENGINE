#include "baseobject.h"


namespace base
{
	int base_object::type() const
	{
		return type_;
	}

	double base_object::x() const
	{
		return position_.x;
	}

	double base_object::y() const
	{
		return position_.y;
	}

	position const & base_object::pos() const
	{
		return position_;
	}

	velocity const & base_object::vel() const
	{
		return vel_;
	}

}