#pragma once

#include "standard_include.h"

namespace anim
{
	struct frame
	{
		int type = 0;
		std::string graph_asset_name;	//要求するグラフィック名
		int x = 0, y = 0;
		double angle = 0, scale = 0;
		int r = 0, g = 0, b = 0, a = 0, time = 0;
		//per angle, per scaleなども考えられる
	};

	struct anim
	{
		std::string asset_name;
		std::vector< frame > frames;
	};

	struct animation_object
	{
		int loopcount_ = 0;
		bool used_ = false;
		int x = 0;
		int time_ = 0;
		int frame_ = 0;
		bool last_frame_ = false;
		int frame_time_ = 0;
		class anim * anim_ = nullptr;

		void main();
	};
}


