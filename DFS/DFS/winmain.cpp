
#include "std_common.h"
#include "scene.h"
#include "global.h"

#pragma comment( lib, "libboost_chrono-vc120-mt-gd-1_56.lib" )
#pragma comment( lib, "libboost_system-vc120-mt-gd-1_56.lib" )

int Key[ 256 ];

int GetHitKeyStateAll_2( int GetHitKeyStateAll_InputKey[] )
{
	char GetHitKeyStateAll_Key[ 256 ];
	GetHitKeyStateAll( GetHitKeyStateAll_Key );
	for( int i = 0; i<256; i++ )
	{
		if( GetHitKeyStateAll_Key[ i ] == 1 ) GetHitKeyStateAll_InputKey[ i ]++;
		else                            GetHitKeyStateAll_InputKey[ i ] = 0;
	}
	return 0;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	SetWindowText( "Fantasy Shooting" );

	ChangeWindowMode( TRUE );//�E�B���h�E���[�h
	
	using game::scene::scene_manager;
	scene_manager scene_mgr;
	
	if( DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK ) != 0 ) return -1;//�������Ɨ���ʉ�

	
	int graph = LoadGraph( "./asset/sample.png" );
	int x = 320, y = 240;

	//�L�[�{�[�h�Ȃǂ̏�����
	global::padkey.initialize();

	while( ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll_2( Key ) == 0 && Key[ KEY_INPUT_ESCAPE ] == 0 )
	{
		//�L�[�{�[�h�̍s�i
		global::padkey.update();

		if( global::padkey.pressed( global::padkey.E_UP ) )
		{
			--y;
		}
		if( global::padkey.pressed( global::padkey.E_DOWN ) )
		{
			++y;
		}
		if( global::padkey.pressed( global::padkey.E_RIGHT ) )
		{
			++x;
		}
		if( global::padkey.pressed( global::padkey.E_LEFT ) )
		{
			--x;
		}


		DrawGraph( x, y, graph, TRUE );
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}