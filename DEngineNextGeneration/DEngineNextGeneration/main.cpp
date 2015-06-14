#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <boost/format.hpp>

#include "game_main.h"
#include "standard_include.h"
#include "directx_class_def.h"
#include "audio.h"
#include "modelloader.h"
#include "model.h"
#include "fps.h"

#include "directx.h"

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

	// DirectX9�̏�����
	hr = InitDirectX();
	if( FAILED( hr ) ) return ( FALSE );

	//������
	direct_x_settings::initialize();

	direct_x_audio::audio aud( hWnd );
	auto const test_wav = aud.load_wav( "test.wav" );

	bool test = false;

	debug::time_manager time_manager;
	static unsigned int counter = 0;

	// ���b�Z�[�W���[�v
	// Windows�́uWM_QUIT�v���b�Z�[�W���󂯂�ƋU(0)��߂�
	while( true ) 
	{
		auto const fpsstr = boost::format( "%0.3f fps" ) % time_manager.get_fps();
		
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
			//aud.play_sound( test_wav.buf_ );	
			if( ++counter % 10 == 0 )
				SetWindowText( hWnd, static_cast< LPCSTR >( fpsstr.str().c_str() ) );
			//�Q�[���̃��C������
			if( FAILED( update_frame() ) )
				break;
			time_manager.wait_auto();
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
