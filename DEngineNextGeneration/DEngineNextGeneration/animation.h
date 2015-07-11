#pragma once

#include "standard_include.h"

namespace anim
{
	class anim;

	struct frame
	{
		int type = 0;
		std::string graph_asset_name;	//要求するグラフィック名
		int handle_;	//pre fetchしたptr
		int x = 0, y = 0;
		double angle = 0, scale = 0;
		int r = 0, g = 0, b = 0, a = 0;
		int time = 0;
		//per angle, per scaleなども考えられる
	};

	struct animation
	{
		std::string asset_name;
		std::vector< frame > frames;
	};

	struct animation_object
	{
		int loopcount_ = 0;
		bool used_ = false;
		int time_sum_ = 0;
		int frame_ = 0;
		bool last_frame_ = false;
		int frame_time_ = 0;

		void main();
		anim const & get_anim() const;
		void set_anim( anim * anim );

	private:
		class anim * anim_ = nullptr;
	};
}


