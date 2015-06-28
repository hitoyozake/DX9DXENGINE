#pragma once

//.cpp内だけで呼び出す関数群．プロトタイプ宣言をおこなうために使用するファイル
#include "directx_class_def.h"
#include "model.h"
#include "standard_include.h"
#include "graphic_api.h"//後で消す


namespace direct_x_settings
{
	// プロトタイプ宣言
	//prototype decleraion
	LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );   // Windows関数
	void clear_vertex_on_screen();
	BOOL update_frame();
	void rotate_graph( double const radian, data_struct::square & sq );
	void zoom_graph( double const scale, data_struct::square & sq );

	

}