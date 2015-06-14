#pragma once

/*
*debug functions API of FPS
*
*/

#include <chrono>
#include <Windows.h>
#include <algorithm>
#include <boost/chrono.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/timer.hpp>
#include <fstream>

namespace debug
{
	class time_manager
	{
	public:
		time_manager();
		double get_fps() const;	//TODO : static
		void update();
		void wait_auto();

	private:
		long calc_result_;
		std::chrono::system_clock::time_point st_;
		boost::timer timer_;
		std::chrono::system_clock::time_point start_;
		std::chrono::system_clock::time_point end_;
		double s;
		std::ofstream log;

	};


}




