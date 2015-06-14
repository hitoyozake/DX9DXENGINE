#pragma once

#include "standard_include.h"

namespace graphic_api
{
	//ユーザにはdirectXのコードを見せずに
	//APIを提供する

	//user -> this api -> call directx_settings_api -> directX api
	void draw_graph( int graph_handle, double x, double y );
	void draw_graph( int graph_handle, double x, double y, double rotation_radian, double scale = 1.0 );

	double angle_to_radian( double angle );
	double radian_to_angle( double const radian );

	/*
	画像の読み込みを行う
	Return : 画像のハンドル．失敗時は-1
	*/
	int load_graph( std::string const & filename );
}

