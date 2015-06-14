#include "fps.h"
#include <chrono>
#include <algorithm>

namespace debug
{
	double fps_ = 0;

	time_manager::time_manager():start_( std::chrono::system_clock::now() ), end_( std::chrono::system_clock::now() ), log( "fps.txt" )
	{
		calc_result_ = std::chrono::duration_cast< std::chrono::milliseconds >( end_ - start_ ).count();
	}

	long long get_now()
	{
		auto const a = std::chrono::system_clock::now() - std::chrono::system_clock::now();

		return std::chrono::duration_cast< std::chrono::milliseconds >( a ).count();
	}

	void time_manager::update()
	{
		//do something
	}

	double time_manager::get_fps() const
	{
		return ( 16 * 60 ) / static_cast< double >( ( std::max< long long > )( calc_result_, 1 ) );
	}

	void time_manager::wait_auto()
	{
		calc_result_ = static_cast< long >( ( std::chrono::high_resolution_clock::now() - st_ ).count() / 10000.0 );

		auto const fps_calc = 16 - calc_result_;

		if( fps_calc > 0 )
		{
			Sleep( fps_calc );
			log << fps_calc << std::endl;

		}

		calc_result_ = static_cast< long >( ( std::chrono::high_resolution_clock::now() - st_ ).count() / 10000.0 );
		st_ = std::chrono::high_resolution_clock::now();

	}

	static double fps()
	{
		return fps_;
	}
}





