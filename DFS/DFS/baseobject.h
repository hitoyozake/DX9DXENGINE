#pragma once


#include "std_common.h"

namespace base
{
	struct position
	{
		double x = 0, y = 0, z = 0;
	};

	struct velocity
	{
		double x = 0, y = 0;
	};


	//インタフェースではなく合成に用いる
	class base_object
	{
	public:
		int type() const;
		int time() const;
		double x() const;
		double y() const;
		position const & pos();
		velocity const & vel() const;
		double angle() const;
		double speed() const;
		double angular_vel() const;
		double vel_x() const;
		double vel_y() const;
		position const & pos() const;
		void draw();
		void move();
	private:
		int type_;
		int time_;
		position position_;	//座標
		double speed_;	//角速度に使用する速度
		velocity vel_;	//xy成分速度
		double angle_;	//角度
		double r_;	//半径


	};

	class actor
	{
	public:
		int life_;
		int life_max_;

	private:
	};

}



