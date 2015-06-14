#include "graphic_api.h"
#include "directx.h"
#include "mathdef.h"
#include "standard_include.h"

namespace graphic_api
{
	void draw_graph( int graph_handle, double x, double y )
	{
		direct_x_settings::position pos;
		
		pos.x_ = x;
		pos.y_ = y;

		direct_x_settings::draw_graph( pos, 0.0, 1.0,
			direct_x_settings::data_struct::texture[ 
			graph_handle
			] );
	}

	void draw_graph( int const graph_handle, double const x, double const y, double const angle, double const scale )
	{
		direct_x_settings::position pos;

		pos.x_ = x;
		pos.y_ = y;

		direct_x_settings::draw_graph( pos, angle, scale + 1,
			direct_x_settings::data_struct::texture[
				graph_handle
			] );
	}

	double angle_to_radian( double const angle )
	{
		return mathdef::radian * angle;
	}

	double radian_to_angle( double const radian )
	{
		return radian / mathdef::radian;
	}


	/*
	画像の読み込みを行う
	Return : 画像のハンドル．失敗時は-1
	*/
	int load_graph( std::string const & filename )
	{
		//ただの転送(今のところは)
		return direct_x_settings::load_texture( filename );
	}
	
}