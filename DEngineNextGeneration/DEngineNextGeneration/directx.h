#include "directx_class_def.h"
#include "model.h"
#include "standard_include.h"

#pragma once

namespace direct_x_settings
{

	struct vector3
	{
		float x_ = 0.0f, y_ = 0.0f, z_ = 0.0f;
	};

	typedef vector3 position;//別名


	// プロトタイプ宣言
	//prototype decleraion
	LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );   // Windows関数
	BOOL InitApp( HINSTANCE, int );                           // ユーザー関数
	HRESULT InitDirectX( void );                                  // DirectX8初期化処理
	void ReleaseD3D( void );                                  // DirectX8開放処理
	void clear_vertex_on_screen();
	int load_texture( std::string const & filename );
	BOOL update_frame();
	void initialize();
	void draw_graph( position pos, data_struct::graphic_information const & gi );

	// 定数値(マクロ)
	int const WINMODE = TRUE; // ウィンドウモードの指定（TRUE:ウィンドウモード／FALSE:フルスクリーン）
	int const SCREEN_WIDTH = 640;	// ウィンドウの幅
	int const SCREEN_HEIGHT = 480;	// ウィンドウの高さ

	//頂点フォーマット
	extern int long FVF_TLVERTEX;

	// グローバル変数
	extern HWND hWnd;                              // ウィンドウハンドル
	extern std::string const szWinName;      // ウィンドウクラス用文字列
	extern std::string const szWinTitle; // ウィンドウクラス用文字列
	extern LPDIRECT3D9 gl_lpD3d;            // Direct3D8インターフェイス
	extern LPDIRECT3DDEVICE9 gl_lpD3ddev;   // Direct3DDevice8インターフェイス
	extern LPDIRECT3DTEXTURE9 gl_texture;	// テクスチャオブジェクト
	extern D3DPRESENT_PARAMETERS gl_d3dpp;         // ディスプレイパラメータ
	extern HCURSOR hCursor;
	extern BOOL gl_app_active;
	extern BYTE gl_keyblard_table[ 256 ];	//キーボードの状態を格納



	class model_mesh
	{
	public:

	private:
		models::i_model & model_;
		LPD3DXMESH mesh_; //for drawing each object
	};

	
	extern std::vector< models::i_model * > xtex;
	extern std::vector< int > tex_index_list;

}

