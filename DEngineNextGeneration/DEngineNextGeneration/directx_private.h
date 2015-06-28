#pragma once

//.cpp�������ŌĂяo���֐��Q�D�v���g�^�C�v�錾�������Ȃ����߂Ɏg�p����t�@�C��
#include "directx_class_def.h"
#include "model.h"
#include "standard_include.h"
#include "graphic_api.h"//��ŏ���


namespace direct_x_settings
{
	// �v���g�^�C�v�錾
	//prototype decleraion
	LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );   // Windows�֐�
	void clear_vertex_on_screen();
	BOOL update_frame();
	void rotate_graph( double const radian, data_struct::square & sq );
	void zoom_graph( double const scale, data_struct::square & sq );

	

}