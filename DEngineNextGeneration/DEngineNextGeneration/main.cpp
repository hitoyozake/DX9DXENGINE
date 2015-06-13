#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9tex.h>

#include "game_main.h"
#include "standard_include.h"
#include "directx_class_def.h"
#include "audio.h"
#include "modelloader.h"
#include "model.h"


std::vector< D3DMATERIAL9 > mtral;
std::vector< LPDIRECT3DTEXTURE9 > xtex_;
std::vector< models::i_model * > xtex;


DWORD material_num = 0;
LPD3DXMESH mesh;


int WINAPI WinMain( HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode )
{
	using namespace direct_x_settings;
	MSG msg;		// ���b�Z�[�W�\���̕ϐ�
	HRESULT hr;

	//�\������E�B���h�E�̒�`�A�o�^�A�\��
	if( !InitApp( hThisInst, nWinMode ) ) return ( FALSE );

	// DirectX8�̏�����
	hr = InitDirectX();
	if( FAILED( hr ) ) return ( FALSE );

	//������
	initialize();

	direct_x_audio::audio aud( hWnd );
	auto const test_wav = aud.load_wav( "test.wav" );

	bool test = false;
	// ���b�Z�[�W���[�v
	// Windows�́uWM_QUIT�v���b�Z�[�W���󂯂�ƋU(0)��߂�
	while( true ) {

		//���b�Z�[�W�����邩�ǂ���
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( !GetMessage( &msg, NULL, 0, 0 ) )
				break;
			TranslateMessage( &msg ); // �L�[�{�[�h���p���\�ɂ���
			DispatchMessage( &msg );  // �����Windows�ɖ߂�
		}
		else if( gl_app_active )
		{
			if( test == false )
			{
				//aud.play_sound( test_wav.buf_ );
				test = true;
			}

			//�Q�[���̃��C������
			if( FAILED( update_frame() ) )
				break;
			Sleep( 1 );
		}
		else
		{
			WaitMessage();
		}
	}

	// DirectX8�I�u�W�F�N�g�̍폜
	ReleaseD3D();

	return msg.wParam;
}
