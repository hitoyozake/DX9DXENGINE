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

	typedef vector3 position;//�ʖ�


	// �v���g�^�C�v�錾
	//prototype decleraion
	LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );   // Windows�֐�
	BOOL InitApp( HINSTANCE, int );                           // ���[�U�[�֐�
	HRESULT InitDirectX( void );                                  // DirectX8����������
	void ReleaseD3D( void );                                  // DirectX8�J������
	void clear_vertex_on_screen();
	int load_texture( std::string const & filename );
	BOOL update_frame();
	void initialize();
	void draw_graph( position pos, data_struct::graphic_information const & gi );

	// �萔�l(�}�N��)
	int const WINMODE = TRUE; // �E�B���h�E���[�h�̎w��iTRUE:�E�B���h�E���[�h�^FALSE:�t���X�N���[���j
	int const SCREEN_WIDTH = 640;	// �E�B���h�E�̕�
	int const SCREEN_HEIGHT = 480;	// �E�B���h�E�̍���

	//���_�t�H�[�}�b�g
	extern int long FVF_TLVERTEX;

	// �O���[�o���ϐ�
	extern HWND hWnd;                              // �E�B���h�E�n���h��
	extern std::string const szWinName;      // �E�B���h�E�N���X�p������
	extern std::string const szWinTitle; // �E�B���h�E�N���X�p������
	extern LPDIRECT3D9 gl_lpD3d;            // Direct3D8�C���^�[�t�F�C�X
	extern LPDIRECT3DDEVICE9 gl_lpD3ddev;   // Direct3DDevice8�C���^�[�t�F�C�X
	extern LPDIRECT3DTEXTURE9 gl_texture;	// �e�N�X�`���I�u�W�F�N�g
	extern D3DPRESENT_PARAMETERS gl_d3dpp;         // �f�B�X�v���C�p�����[�^
	extern HCURSOR hCursor;
	extern BOOL gl_app_active;
	extern BYTE gl_keyblard_table[ 256 ];	//�L�[�{�[�h�̏�Ԃ��i�[



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

