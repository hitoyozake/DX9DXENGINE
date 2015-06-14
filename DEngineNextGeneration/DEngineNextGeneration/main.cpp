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
	MSG msg;		// メッセージ構造体変数
	HRESULT hr;

	//表示するウィンドウの定義、登録、表示
	if( !InitApp( hThisInst, nWinMode ) ) return ( FALSE );

	// DirectX9の初期化
	hr = InitDirectX();
	if( FAILED( hr ) ) return ( FALSE );

	//初期化
	direct_x_settings::initialize();

	direct_x_audio::audio aud( hWnd );
	auto const test_wav = aud.load_wav( "test.wav" );

	bool test = false;

	debug::time_manager time_manager;
	static unsigned int counter = 0;

	// メッセージループ
	// Windowsは「WM_QUIT」メッセージを受けると偽(0)を戻す
	while( true ) 
	{
		auto const fpsstr = boost::format( "%0.3f fps" ) % time_manager.get_fps();
		
		//メッセージがあるかどうか
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( !GetMessage( &msg, NULL, 0, 0 ) )
				break;
			TranslateMessage( &msg ); // キーボード利用を可能にする
			DispatchMessage( &msg );  // 制御をWindowsに戻す
		}
		else if( gl_app_active )
		{
			//aud.play_sound( test_wav.buf_ );	
			if( ++counter % 10 == 0 )
				SetWindowText( hWnd, static_cast< LPCSTR >( fpsstr.str().c_str() ) );
			//ゲームのメイン処理
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

	// DirectX8オブジェクトの削除
	ReleaseD3D();

	return msg.wParam;
}
