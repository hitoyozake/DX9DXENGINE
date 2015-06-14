#pragma once

#include "standard_include.h"

namespace graphic_api
{
	//���[�U�ɂ�directX�̃R�[�h����������
	//API��񋟂���

	//user -> this api -> call directx_settings_api -> directX api
	void draw_graph( int graph_handle, double x, double y );
	void draw_graph( int graph_handle, double x, double y, double rotation_radian, double scale = 1.0 );

	double angle_to_radian( double angle );
	double radian_to_angle( double const radian );

	/*
	�摜�̓ǂݍ��݂��s��
	Return : �摜�̃n���h���D���s����-1
	*/
	int load_graph( std::string const & filename );
}

