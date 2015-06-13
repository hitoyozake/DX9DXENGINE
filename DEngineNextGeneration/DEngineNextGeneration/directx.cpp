#include "directx_class_def.h"
#include "directx_include.h"
#include "model.h"

namespace direct_x_settings
{
	// 定数値(マクロ)
	int const WINMODE = TRUE; // ウィンドウモードの指定（TRUE:ウィンドウモード／FALSE:フルスクリーン）
	int const SCREEN_WIDTH = 640;	// ウィンドウの幅
	int const SCREEN_HEIGHT = 480;	// ウィンドウの高さ

	//頂点フォーマット
	int long FVF_TLVERTEX = ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

	// プロトタイプ宣言
	LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );   // Windows関数
	BOOL InitApp( HINSTANCE, int );                           // ユーザー関数
	HRESULT InitDirectX( void );                                  // DirectX8初期化処理
	void ReleaseD3D( void );                                  // DirectX8開放処理

	// グローバル変数
	HWND hWnd;                              // ウィンドウハンドル
	std::string const szWinName = "Exer002";      // ウィンドウクラス用文字列
	std::string const szWinTitle = "DXEngine"; // ウィンドウクラス用文字列
	LPDIRECT3D9 gl_lpD3d = NULL;            // Direct3D8インターフェイス
	LPDIRECT3DDEVICE9 gl_lpD3ddev = NULL;   // Direct3DDevice8インターフェイス
	LPDIRECT3DTEXTURE9 gl_texture = NULL;	// テクスチャオブジェクト
	D3DPRESENT_PARAMETERS gl_d3dpp;         // ディスプレイパラメータ
	HCURSOR hCursor = LoadCursor( NULL, IDC_ARROW );
	BOOL gl_app_active = FALSE;
	BYTE gl_keyblard_table[ 256 ];	//キーボードの状態を格納

	void create_texture( std::string const & filename )
	{
		LPDIRECT3DTEXTURE9 tex;

		//画像のパレット情報
		PALETTEENTRY palette;

		if( FAILED( D3DXCreateTextureFromFileEx( gl_lpD3ddev, filename.c_str(), 0, 0, 0, 0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			D3DX_FILTER_LINEAR,
			D3DX_FILTER_LINEAR,
			D3DCOLOR_ARGB( 255, 255, 0, 0 ), //ARGB 透明色が設定されたpngはキーカラーに関係なく透過できる
			NULL,
			NULL,
			&tex
			) ) )
		{

			std::string const msg = filename + "をテクスチャとして読み込めませんでした";
			MessageBox( hWnd, msg.c_str(), \
				"ERROR", MB_OK );
			return;
		}
		else
		{
			D3DSURFACE_DESC desc;

			if( FAILED( tex->GetLevelDesc( 0, &desc ) ) )
			{
				std::string const msg = filename + "のwidthとheightを読み込めませんでした";
				MessageBox( hWnd, msg.c_str(), \
					"ERROR", MB_OK );
			}
			auto const width = desc.Width;
			auto const height = desc.Height;

			data_struct::graphic_information graph;
			graph.width_ = width;
			graph.height_ = height;
			graph.tex_ = tex;
			data_struct::texture.push_back( graph );
		}
	}

	std::array< data_struct::tlvertex, 4 > init_vertex( \
		std::pair< float, float > const & pos1, std::pair< float, float > const & pos2, int const alpha = 255 )
	{
		//0-1
		//| |
		//3-2
		std::array< data_struct::tlvertex, 4 > vertex;

		vertex[ 0 ].x_ = pos1.first;
		vertex[ 0 ].y_ = pos1.second;
		vertex[ 0 ].z_ = 0.0;
		vertex[ 0 ].rhw_ = 1.0;	//2Dを扱う時の色
		vertex[ 0 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//頂点の色
		vertex[ 0 ].tu_ = 0.0;	//テクスチャのx座標
		vertex[ 0 ].tv_ = 0.0; //テクスチャのy座標

		vertex[ 1 ].x_ = pos2.first;
		vertex[ 1 ].y_ = pos1.second;
		vertex[ 1 ].z_ = 0.0;
		vertex[ 1 ].rhw_ = 1.0;	//2Dを扱う時の色
		vertex[ 1 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//頂点の色
		vertex[ 1 ].tu_ = 1.0;	//テクスチャのx座標
		vertex[ 1 ].tv_ = 0.0; //テクスチャのy座標

		vertex[ 2 ].x_ = pos2.first;
		vertex[ 2 ].y_ = pos2.second;
		vertex[ 2 ].z_ = 0.0;
		vertex[ 2 ].rhw_ = 1.0;	//2Dを扱う時の色
		vertex[ 2 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//頂点の色
		vertex[ 2 ].tu_ = 1.0;	//テクスチャのx座標
		vertex[ 2 ].tv_ = 1.0; //テクスチャのy座標

		vertex[ 3 ].x_ = pos1.first;
		vertex[ 3 ].y_ = pos2.second;
		vertex[ 3 ].z_ = 0.0;
		vertex[ 3 ].rhw_ = 1.0;	//2Dを扱う時の色
		vertex[ 3 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//頂点の色
		vertex[ 3 ].tu_ = 0.0;	//テクスチャのx座標
		vertex[ 3 ].tv_ = 1.0; //テクスチャのy座標		 

		return std::move( vertex );
	}

	void send_vertex_to_back_buffer( data_struct::square const & data )
	{
		//テクスチャをセット -> バックバッファに転送の順でなければならない
		// -> そうしなかったら? -> テクスチャ貼ってない状態で更新して、
		//前の時のテクスチャを使うから、resetwindowの時に画像がちらつく

		gl_lpD3ddev->SetTexture( 0, data.tex_ );
		//描画するテクスチャをデバイスにセット

		gl_lpD3ddev->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, data.vertex_.data(), \
			sizeof data.vertex_[ 0 ] );
		//三角形ポリゴンをバックバッファに転送
		//第二匹数はポリゴンの数。四角形の場合は2を指定する
	}


	void draw_3d()
	{
		//3D
		for( int j = 0; j < xtex.size(); ++j )
		{
			for( int i = 0; i < xtex[ j ]->material().size(); ++i )
			{
				gl_lpD3ddev->SetFVF( xtex[ j ]->mesh()->GetFVF() );
				gl_lpD3ddev->SetMaterial( &xtex[ j ]->material()[ i ] );
				gl_lpD3ddev->SetTexture( 0, xtex[ j ]->tex()[ i ] );
				xtex[ j ]->mesh()->DrawSubset( i );
			}
		}
	}

	BOOL update_frame()
	{
		//現在のキー情報を取得
		if( !GetKeyboardState( gl_keyblard_table ) )
		{
			MessageBox( hWnd, "キー情報の取得に失敗", "ERROR", MB_OK );
			return FALSE;
		}

		/* 画面のクリア */
		gl_lpD3ddev->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 140, 140, 140, 0xFF ), 1.0f, 0 );
		//シーン開始
		gl_lpD3ddev->BeginScene();

		gl_lpD3ddev->SetFVF( FVF_TLVERTEX );
		//頂点フォーマットを設定

		for( auto const & i : data_struct::vertex )
		{
			send_vertex_to_back_buffer( i );
		}

		gl_lpD3ddev->SetVertexShader( NULL );


		draw_3d();


		//============================================================

		//::game_main::game_main();

		//============================================================
		/* シーン終了 */
		gl_lpD3ddev->EndScene();
		/* フリップ */
		gl_lpD3ddev->Present( NULL, NULL, NULL, NULL );

		return TRUE;
	}

	//ビュー・カメラの設定
	void init_view()
	{
		D3DXMATRIX d3dxmat_view;
		D3DXMatrixLookAtLH(
			&d3dxmat_view,
			&( D3DXVECTOR3( -2.0f, 0.0f, -2.0f ) ), //カメラの位置座標
			&( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ), //注視点座標
			&( D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) ) //カメラから見た上方向のベクトル
			);

		gl_lpD3ddev->SetTransform( D3DTS_VIEW, &d3dxmat_view );

		//プロジェクションの設定
		D3DXMATRIX matBaseProj;
		D3DXMatrixPerspectiveFovLH(
			&matBaseProj,
			( float )( 3.141592 / 4.0 ),	//視野角
			( float )( 640.0 / 480.0 ),	//アスペクト比
			1.0f,               //クリッピング距離（近いほう）
			1000000.0f );        //クリッピング距離（遠いほう)
		gl_lpD3ddev->SetTransform( D3DTS_PROJECTION, &matBaseProj );

		//ライトの設定
		gl_lpD3ddev->SetRenderState( D3DRS_LIGHTING, TRUE );
		D3DLIGHT9	light;
		::ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Diffuse.r = 0.9f;   light.Diffuse.g = 0.9f;   light.Diffuse.b = 0.9f;
		light.Specular.r = 0.2f;  light.Specular.g = 0.2f;  light.Specular.b = 0.2f;
		light.Ambient.r = 0.5f;   light.Ambient.g = 0.5f;   light.Ambient.b = 0.5f;
		light.Direction = D3DXVECTOR3( 0.0f, -0.5f, -0.2f );
		gl_lpD3ddev->SetLight( 0, &light );
		gl_lpD3ddev->LightEnable( 0, TRUE );
	}

	//描画の初期化を行う
	void init_render()
	{
		//gl_lpD3ddev->SetRenderState(D3DRS_ALPHAREF, 0x00000001);
		// アルファ・ブレンディングを行う
		gl_lpD3ddev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		// 透過処理を行う
		gl_lpD3ddev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		gl_lpD3ddev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );

		gl_lpD3ddev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		gl_lpD3ddev->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
		gl_lpD3ddev->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );

		//テクスチャの設定
		//透明s度の設定
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );

		init_view();
	}

	void load_texture( std::string const & filename, std::pair< float, float > const & pos )
	{
		create_texture( filename );

		//頂点データの
		auto const table = init_vertex( pos, \
			std::make_pair( pos.first + 100.0f, pos.second + 100.0f ) );
	}

	struct position
	{
		float x_ = 0.0f, y_ = 0.0f, z_ = 0.0f;
	};

	void draw_graph( position pos, data_struct::graphic_information const & gi )
	{
		//頂点データの格納
		auto table = init_vertex( std::make_pair( pos.x_, pos.y_ ), \
			std::make_pair( pos.x_ + gi.width_, \
			pos.y_ + gi.height_ ) );

		data_struct::square v;

		v.vertex_ = table;

		v.tex_ = data_struct::texture[ 1 ].tex_;
		data_struct::vertex.push_back( v );
	}


	void initialize()
	{
		init_render();

		if( auto const r = models::mdl_loader.load_model( "./saturn.x", gl_lpD3ddev ) )
		{
			xtex.push_back( reinterpret_cast< models::model * >( r.get() ) );
			try
			{
				xtex[ 0 ]->name();
			}
			catch( std::exception & e )
			{
				std::cout << e.what() << std::endl;
			}
		}

		create_texture( "sample.png" );
		create_texture( "sample2.png" );

		//頂点データの格納
		auto table = init_vertex( std::make_pair( 100.0f, 100.0f ), \
			std::make_pair( 100.0f + data_struct::texture[ 1 ].width_, \
			100.0f + data_struct::texture[ 1 ].height_ ) );

		data_struct::square v;

		v.vertex_ = table;

		v.tex_ = data_struct::texture[ 1 ].tex_;
		data_struct::vertex.push_back( v );

		//第２テクスチャ、座標登録
		table = init_vertex( std::make_pair( 90.0f, 90.0f ), \
			std::make_pair( 90.0f + +data_struct::texture[ 0 ].width_, \
			90.0f + +data_struct::texture[ 0 ].height_ ) );
		v.vertex_ = table;
		v.tex_ = data_struct::texture[ 0 ].tex_;
		data_struct::vertex.push_back( v );

	}

	BOOL InitApp( HINSTANCE hThisInst, int nWinMode )
	{
		WNDCLASSEX wc;                                   // ウィンドウクラス構造体

		// ウィンドウクラスを定義する
		wc.cbSize = sizeof( WNDCLASSEX );                  // WNDCLASSEX構造体のサイズを設定
		wc.style = NULL;                                 // ウィンドウスタイル（デフォルト）
		wc.lpfnWndProc = WinProc;                        // ウィンドウ関数
		wc.cbClsExtra = 0;                               // 通常は使わない（０にしておく）
		wc.cbWndExtra = 0;                               // 通常は使わない（０にしておく）
		wc.hInstance = hThisInst;                        // このインスタンスへのハンドル
		wc.hIcon = NULL;                                 // ラージアイコン（なし）
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );        // カーソルスタイル
		wc.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH ); // ウィンドウの背景（黒）
		wc.lpszMenuName = NULL;                          // メニュー（なし）
		wc.lpszClassName = szWinName.c_str();                    // ウィンドウクラス名
		wc.hIconSm = NULL;                               // スモールアイコン（なし）

		// ウィンドウクラスの登録
		if( !RegisterClassEx( &wc ) ) return ( FALSE );

		// ウィンドウクラスの登録ができたので、ウィンドウを生成する
		if( WINMODE )
		{
			/* ウィンドウ・モード用のウィンドウを生成 */
			hWnd = CreateWindow(
				szWinName.c_str(),              // ウィンドウクラスの名前
				szWinTitle.c_str(),             // ウィンドウタイトル
				WS_OVERLAPPEDWINDOW,    // ウィンドウスタイル
				CW_USEDEFAULT,          // ウィンドウの左角Ｘ座標
				CW_USEDEFAULT,          // ウィンドウの左角Ｙ座標
				CW_USEDEFAULT,          // ウィンドウの幅
				CW_USEDEFAULT,          // ウィンドウの高さ
				NULL,                   // 親ウィンドウ（なし）
				NULL,                   // メニュー（なし）
				hThisInst,              // このプログラムのインスタンスのハンドル
				NULL                    // 追加引数（なし）
				);

			RECT wRect, cRect;  // ウィンドウ全体の矩形、クライアント領域の矩形
			int ww, wh;         // ウィンドウ全体の幅、高さ
			int cw, ch;         // クライアント領域の幅、高さ

			// ウィンドウ全体の幅・高さを計算
			GetWindowRect( hWnd, &wRect );
			ww = wRect.right - wRect.left;
			wh = wRect.bottom - wRect.top;
			// クライアント領域の幅・高さを計算
			GetClientRect( hWnd, &cRect );
			cw = cRect.right - cRect.left;
			ch = cRect.bottom - cRect.top;
			// クライアント領域以外に必要なサイズを計算
			ww = ww - cw;
			wh = wh - ch;
			// ウィンドウ全体に必要なサイズを計算
			ww = SCREEN_WIDTH + ww;
			wh = SCREEN_HEIGHT + wh;

			// 計算した幅と高さをウィンドウに設定
			SetWindowPos( hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE );

		}
		else
		{
			/* フルスクリーン・モード用のウィンドウを生成 */
			hWnd = CreateWindow(
				szWinName.c_str(),              // ウィンドウクラスの名前
				szWinTitle.c_str(),             // ウィンドウタイトル
				WS_VISIBLE | WS_POPUP,  // ウィンドウスタイル
				0,                      // ウィンドウの左角Ｘ座標
				0,                      // ウィンドウの左角Ｙ座標
				SCREEN_WIDTH,           // ウィンドウの幅
				SCREEN_HEIGHT,          // ウィンドウの高さ
				NULL,                   // 親ウィンドウ（なし）
				NULL,                   // メニュー（なし）
				hThisInst,              // このプログラムのインスタンスのハンドル
				NULL                    // 追加引数（なし）
				);
		}

		ShowWindow( hWnd, nWinMode ); // ウィンドウを表示
		ValidateRect( hWnd, 0 );      // WM_PAINTが呼ばれないようにする
		UpdateWindow( hWnd );         // ウィンドウの更新

		return ( TRUE );              // InitApp関数の正常終了
	}

	//-----------------------------------------------------------------------------
	// 関数名　：　InitDirectX()　
	// 機能概要：　Direct Draw オブジェクトの生成
	// 戻り値　：　正常終了のとき：DD_OK、異常終了のとき：エラーコード
	//-----------------------------------------------------------------------------
	HRESULT InitDirectX( void )
	{
		D3DDISPLAYMODE  DispMode;	// ディスプレイモード
		HRESULT         hr;

		/* DirectX8オブジェクトの生成 */
		gl_lpD3d = Direct3DCreate9( D3D_SDK_VERSION );
		if( !gl_lpD3d )
		{
			// オブジェクト生成失敗
			MessageBox( hWnd, "DirectXD3D8オブジェクト生成失敗", "ERROR", MB_OK );
			return E_FAIL;
		}

		/* DirectX8のプレゼンテーションパラメータを設定 */

		// ディスプレイデータ格納構造体初期化
		ZeroMemory( &gl_d3dpp, sizeof( D3DPRESENT_PARAMETERS ) );
		// 現在のディスプレイモードデータ取得
		gl_lpD3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &DispMode );
		// バックバッファフォーマットをディスプレイと等価に
		gl_d3dpp.BackBufferFormat = DispMode.Format;
		// 横ドット幅設定
		gl_d3dpp.BackBufferWidth = SCREEN_WIDTH;
		// 縦ドット幅設定
		gl_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
		// バックバッファの数
		gl_d3dpp.BackBufferCount = 1;
		// フリップの方法（通常はこの定数でよい）
		gl_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//
		gl_d3dpp.EnableAutoDepthStencil = TRUE;
		// ステンシルフォーマット
		gl_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		// ウインドウモードの設定
		gl_d3dpp.Windowed = WINMODE;

		/* デバイスオブジェクトの生成 */

		//高性能なハードウェアデバイスの生成を試みる
		hr = gl_lpD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &gl_d3dpp, &gl_lpD3ddev );
		if( FAILED( hr ) )
		{
			//ハードウェアデバイスの生成を試みる
			hr = gl_lpD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &gl_d3dpp, &gl_lpD3ddev );
			if( FAILED( hr ) )
			{
				//ソフトウェアデバイスの生成を試みる
				hr = gl_lpD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING, &gl_d3dpp, &gl_lpD3ddev );
				if( FAILED( hr ) )
				{
					//--どのデバイスも取得できなかった
					MessageBox( hWnd, "DirectXデバイス生成失敗", "ERROR", MB_OK );
					return E_FAIL;
				}
			}
		}

		return S_OK;
	}

	//-----------------------------------------------------------------------------
	// 関数名　：　ReleaseD3D()
	// 機能概要：　DirectX8オブジェクトの開放
	//-----------------------------------------------------------------------------
	void ReleaseD3D( void )
	{
		//テクスチャの開放

		for( auto & i : data_struct::texture )
		{
			if( i.tex_ != NULL )
			{
				i.tex_->Release();
				i.tex_ = NULL;
			}
		}

		//デバイスオブジェクトの開放
		if( gl_lpD3ddev != NULL )
		{
			gl_lpD3ddev->Release();
			gl_lpD3ddev = NULL;
		}
		//DirectX8オブジェクトの開放
		if( gl_lpD3d != NULL )
		{
			gl_lpD3d->Release();
			gl_lpD3d = NULL;
		}


	}


	//ウインドウの再設定
	void reset_window()
	{
		if( gl_lpD3ddev )
		{
			//ディスプレイ・パラメータの値を使ってウインドウをリセット
			gl_lpD3ddev->Reset( &gl_d3dpp );

			//画面復帰時に描画の設定を行う
			init_render();
		}
	}


	LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		switch( message )
		{
		case WM_SIZE:	//ウインドウのサイズ変更時
			if( wParam == SIZE_MAXHIDE || wParam == SIZE_MINIMIZED )
				gl_app_active = FALSE;
			else
				gl_app_active = TRUE;
			reset_window();
			break;
		case WM_MOVE:	//ウインドウの移動時
			reset_window();
			break;
		case WM_KEYDOWN: // キーを押したとき
			switch( wParam )
			{
			case VK_ESCAPE:	//エスケープなら閉じる
				PostMessage( hWnd, WM_CLOSE, 0, 0 );
				break;
			}
			break;
		case WM_SETCURSOR: // カーソルの設定
			SetCursor( hCursor );
			break;
		case WM_DESTROY:        // 閉じるボタンをクリックした時
			PostQuitMessage( 0 ); // WM_QUITメッセージを発行
			break;
		default: // 上記以外のメッセージはWindowsへ処理を任せる
			return DefWindowProc( hWnd, message, wParam, lParam );
		}
		return 0;
	}
}



