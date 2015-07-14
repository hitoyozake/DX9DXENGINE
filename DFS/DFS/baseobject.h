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


	//�C���^�t�F�[�X�ł͂Ȃ������ɗp����
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
		position position_;	//���W
		double speed_;	//�p���x�Ɏg�p���鑬�x
		velocity vel_;	//xy�������x
		double angle_;	//�p�x
		double r_;	//���a


	};

	class actor
	{
	public:
		int life_;
		int life_max_;

	private:
	};

}



