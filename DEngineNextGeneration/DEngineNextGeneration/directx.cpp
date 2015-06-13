#include "directx_class_def.h"
#include "directx_include.h"
#include "model.h"
#include "directx.h"

namespace direct_x_settings
{
	
	std::vector< int > tex_index_list;

	
	//���_�t�H�[�}�b�g
	int long FVF_TLVERTEX = ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

	// �O���[�o���ϐ�
	HWND hWnd;                              // �E�B���h�E�n���h��
	std::string const szWinName = "Exer002";      // �E�B���h�E�N���X�p������
	std::string const szWinTitle = "DXEngine"; // �E�B���h�E�N���X�p������
	LPDIRECT3D9 gl_lpD3d = NULL;            // Direct3D8�C���^�[�t�F�C�X
	LPDIRECT3DDEVICE9 gl_lpD3ddev = NULL;   // Direct3DDevice8�C���^�[�t�F�C�X
	LPDIRECT3DTEXTURE9 gl_texture = NULL;	// �e�N�X�`���I�u�W�F�N�g
	D3DPRESENT_PARAMETERS gl_d3dpp;         // �f�B�X�v���C�p�����[�^
	HCURSOR hCursor = LoadCursor( NULL, IDC_ARROW );
	BOOL gl_app_active = FALSE;
	BYTE gl_keyblard_table[ 256 ];	//�L�[�{�[�h�̏�Ԃ��i�[
	void clear_vertex_on_screen();
	LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

	//���[�h�ɐ��������ꍇ�̓O���t�B�b�N�n���h����Ԃ�(index)
	int load_texture( std::string const & filename )
	{
		LPDIRECT3DTEXTURE9 tex;

		//�摜�̃p���b�g���
		PALETTEENTRY palette;

		if( FAILED( D3DXCreateTextureFromFileEx( gl_lpD3ddev, filename.c_str(), 0, 0, 0, 0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			D3DX_FILTER_LINEAR,
			D3DX_FILTER_LINEAR,
			D3DCOLOR_ARGB( 255, 255, 0, 0 ), //ARGB �����F���ݒ肳�ꂽpng�̓L�[�J���[�Ɋ֌W�Ȃ����߂ł���
			NULL,
			NULL,
			&tex
			) ) )
		{

			std::string const msg = filename + "���e�N�X�`���Ƃ��ēǂݍ��߂܂���ł���";
			MessageBox( hWnd, msg.c_str(), \
				"ERROR", MB_OK );
			return -1;
		}
		
		D3DSURFACE_DESC desc;

		if( FAILED( tex->GetLevelDesc( 0, &desc ) ) )
		{
			std::string const msg = filename + "��width��height��ǂݍ��߂܂���ł���";
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

		//return index
		return data_struct::texture.size() - 1;

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
		vertex[ 0 ].rhw_ = 1.0;	//2D���������̐F
		vertex[ 0 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//���_�̐F
		vertex[ 0 ].tu_ = 0.0;	//�e�N�X�`����x���W
		vertex[ 0 ].tv_ = 0.0; //�e�N�X�`����y���W

		vertex[ 1 ].x_ = pos2.first;
		vertex[ 1 ].y_ = pos1.second;
		vertex[ 1 ].z_ = 0.0;
		vertex[ 1 ].rhw_ = 1.0;	//2D���������̐F
		vertex[ 1 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//���_�̐F
		vertex[ 1 ].tu_ = 1.0;	//�e�N�X�`����x���W
		vertex[ 1 ].tv_ = 0.0; //�e�N�X�`����y���W

		vertex[ 2 ].x_ = pos2.first;
		vertex[ 2 ].y_ = pos2.second;
		vertex[ 2 ].z_ = 0.0;
		vertex[ 2 ].rhw_ = 1.0;	//2D���������̐F
		vertex[ 2 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//���_�̐F
		vertex[ 2 ].tu_ = 1.0;	//�e�N�X�`����x���W
		vertex[ 2 ].tv_ = 1.0; //�e�N�X�`����y���W

		vertex[ 3 ].x_ = pos1.first;
		vertex[ 3 ].y_ = pos2.second;
		vertex[ 3 ].z_ = 0.0;
		vertex[ 3 ].rhw_ = 1.0;	//2D���������̐F
		vertex[ 3 ].color_ = D3DCOLOR_RGBA( 255, 255, 255, alpha );	//���_�̐F
		vertex[ 3 ].tu_ = 0.0;	//�e�N�X�`����x���W
		vertex[ 3 ].tv_ = 1.0; //�e�N�X�`����y���W		 

		return std::move( vertex );
	}

	void send_vertex_to_back_buffer( data_struct::square const & data )
	{
		//�e�N�X�`�����Z�b�g -> �o�b�N�o�b�t�@�ɓ]���̏��łȂ���΂Ȃ�Ȃ�
		// -> �������Ȃ�������? -> �e�N�X�`���\���ĂȂ���ԂōX�V���āA
		//�O�̎��̃e�N�X�`�����g������Aresetwindow�̎��ɉ摜�������

		gl_lpD3ddev->SetTexture( 0, data.tex_ );
		//�`�悷��e�N�X�`�����f�o�C�X�ɃZ�b�g

		gl_lpD3ddev->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, data.vertex_.data(), \
			sizeof data.vertex_[ 0 ] );
		//�O�p�`�|���S�����o�b�N�o�b�t�@�ɓ]��
		//���C���̓|���S���̐��B�l�p�`�̏ꍇ��2���w�肷��
	}


	void draw_3d()
	{
		//3D
		/*for( int j = 0; j < xtex.size(); ++j )
		{
			for( int i = 0; i < xtex[ j ]->material().size(); ++i )
			{
				gl_lpD3ddev->SetFVF( xtex[ j ]->mesh()->GetFVF() );
				gl_lpD3ddev->SetMaterial( &xtex[ j ]->material()[ i ] );
				gl_lpD3ddev->SetTexture( 0, xtex[ j ]->tex()[ i ] );
				xtex[ j ]->mesh()->DrawSubset( i );
			}
		}*/
	}

	BOOL update_frame()
	{
		//���݂̃L�[�����擾
		if( !GetKeyboardState( gl_keyblard_table ) )
		{
			MessageBox( hWnd, "�L�[���̎擾�Ɏ��s", "ERROR", MB_OK );
			return FALSE;
		}

		/* ��ʂ̃N���A */
		gl_lpD3ddev->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 140, 140, 140, 0xFF ), 1.0f, 0 );
		//�V�[���J�n
		gl_lpD3ddev->BeginScene();

		gl_lpD3ddev->SetFVF( FVF_TLVERTEX );
		//���_�t�H�[�}�b�g��ݒ�

		static float x = 0.0f;

		x += 1.0f;
		for( auto const & index : tex_index_list )
		{
			position p;
			p.x_ = 320.0f;
			p.y_ += x;
			draw_graph( p, data_struct::texture[ index ] );
		}

		for( auto const & i : data_struct::vertex )
		{
			send_vertex_to_back_buffer( i );
		}

		//�`��̃N���A
		clear_vertex_on_screen();

		gl_lpD3ddev->SetVertexShader( NULL );


		draw_3d();


		//============================================================

		//::game_main::game_main();

		//============================================================
		/* �V�[���I�� */
		gl_lpD3ddev->EndScene();
		/* �t���b�v */
		gl_lpD3ddev->Present( NULL, NULL, NULL, NULL );

		return TRUE;
	}

	//�r���[�E�J�����̐ݒ�
	void init_view()
	{
		D3DXMATRIX d3dxmat_view;
		D3DXMatrixLookAtLH(
			&d3dxmat_view,
			&( D3DXVECTOR3( -2.0f, 0.0f, -2.0f ) ), //�J�����̈ʒu���W
			&( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ), //�����_���W
			&( D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) ) //�J�������猩��������̃x�N�g��
			);

		gl_lpD3ddev->SetTransform( D3DTS_VIEW, &d3dxmat_view );

		//�v���W�F�N�V�����̐ݒ�
		D3DXMATRIX matBaseProj;
		D3DXMatrixPerspectiveFovLH(
			&matBaseProj,
			( float )( 3.141592 / 4.0 ),	//����p
			( float )( 640.0 / 480.0 ),	//�A�X�y�N�g��
			1.0f,               //�N���b�s���O�����i�߂��ق��j
			1000000.0f );        //�N���b�s���O�����i�����ق�)
		gl_lpD3ddev->SetTransform( D3DTS_PROJECTION, &matBaseProj );

		//���C�g�̐ݒ�
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

	//�`��̏��������s��
	void init_render()
	{
		//gl_lpD3ddev->SetRenderState(D3DRS_ALPHAREF, 0x00000001);
		// �A���t�@�E�u�����f�B���O���s��
		gl_lpD3ddev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		// ���ߏ������s��
		gl_lpD3ddev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		gl_lpD3ddev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );

		gl_lpD3ddev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		gl_lpD3ddev->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
		gl_lpD3ddev->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );

		//�e�N�X�`���̐ݒ�
		//����s�x�̐ݒ�
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		gl_lpD3ddev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );

		init_view();
	}


	
	//���W�ɉ摜��\��
	void draw_graph( position pos, data_struct::graphic_information const & gi )
	{
		//���_�f�[�^�̊i�[
		auto table = init_vertex( std::make_pair( pos.x_, pos.y_ ), \
			std::make_pair( pos.x_ + gi.width_, \
			pos.y_ + gi.height_ ) );

		data_struct::square v;

		v.vertex_ = table;

		v.tex_ = gi.tex_;
		data_struct::vertex.push_back( v );
	}

	//�`��pvector�̃N���A
	void clear_vertex_on_screen()
	{
		data_struct::vertex.clear();
	}


	void initialize()
	{
		init_render();

		/*if( auto const r = models::mdl_loader.load_model( "./saturn.x", gl_lpD3ddev ) )
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
		}*/

		auto index = load_texture( "sample.png" );

		//test code
		if( index != -1 )
			tex_index_list.push_back( index );

		index = load_texture( "sample2.png" );

		if( index != -1 )
			tex_index_list.push_back( index );

	}

	BOOL InitApp( HINSTANCE hThisInst, int nWinMode )
	{
		WNDCLASSEX wc;                                   // �E�B���h�E�N���X�\����

		// �E�B���h�E�N���X���`����
		wc.cbSize = sizeof( WNDCLASSEX );                  // WNDCLASSEX�\���̂̃T�C�Y��ݒ�
		wc.style = NULL;                                 // �E�B���h�E�X�^�C���i�f�t�H���g�j
		wc.lpfnWndProc = direct_x_settings::WinProc;                        // �E�B���h�E�֐�
		wc.cbClsExtra = 0;                               // �ʏ�͎g��Ȃ��i�O�ɂ��Ă����j
		wc.cbWndExtra = 0;                               // �ʏ�͎g��Ȃ��i�O�ɂ��Ă����j
		wc.hInstance = hThisInst;                        // ���̃C���X�^���X�ւ̃n���h��
		wc.hIcon = NULL;                                 // ���[�W�A�C�R���i�Ȃ��j
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );        // �J�[�\���X�^�C��
		wc.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH ); // �E�B���h�E�̔w�i�i���j
		wc.lpszMenuName = NULL;                          // ���j���[�i�Ȃ��j
		wc.lpszClassName = szWinName.c_str();                    // �E�B���h�E�N���X��
		wc.hIconSm = NULL;                               // �X���[���A�C�R���i�Ȃ��j

		// �E�B���h�E�N���X�̓o�^
		if( !RegisterClassEx( &wc ) ) return ( FALSE );

		// �E�B���h�E�N���X�̓o�^���ł����̂ŁA�E�B���h�E�𐶐�����
		if( WINMODE )
		{
			/* �E�B���h�E�E���[�h�p�̃E�B���h�E�𐶐� */
			hWnd = CreateWindow(
				szWinName.c_str(),              // �E�B���h�E�N���X�̖��O
				szWinTitle.c_str(),             // �E�B���h�E�^�C�g��
				WS_OVERLAPPEDWINDOW,    // �E�B���h�E�X�^�C��
				CW_USEDEFAULT,          // �E�B���h�E�̍��p�w���W
				CW_USEDEFAULT,          // �E�B���h�E�̍��p�x���W
				CW_USEDEFAULT,          // �E�B���h�E�̕�
				CW_USEDEFAULT,          // �E�B���h�E�̍���
				NULL,                   // �e�E�B���h�E�i�Ȃ��j
				NULL,                   // ���j���[�i�Ȃ��j
				hThisInst,              // ���̃v���O�����̃C���X�^���X�̃n���h��
				NULL                    // �ǉ������i�Ȃ��j
				);

			RECT wRect, cRect;  // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
			int ww, wh;         // �E�B���h�E�S�̂̕��A����
			int cw, ch;         // �N���C�A���g�̈�̕��A����

			// �E�B���h�E�S�̂̕��E�������v�Z
			GetWindowRect( hWnd, &wRect );
			ww = wRect.right - wRect.left;
			wh = wRect.bottom - wRect.top;
			// �N���C�A���g�̈�̕��E�������v�Z
			GetClientRect( hWnd, &cRect );
			cw = cRect.right - cRect.left;
			ch = cRect.bottom - cRect.top;
			// �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
			ww = ww - cw;
			wh = wh - ch;
			// �E�B���h�E�S�̂ɕK�v�ȃT�C�Y���v�Z
			ww = SCREEN_WIDTH + ww;
			wh = SCREEN_HEIGHT + wh;

			// �v�Z�������ƍ������E�B���h�E�ɐݒ�
			SetWindowPos( hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE );

		}
		else
		{
			/* �t���X�N���[���E���[�h�p�̃E�B���h�E�𐶐� */
			hWnd = CreateWindow(
				szWinName.c_str(),              // �E�B���h�E�N���X�̖��O
				szWinTitle.c_str(),             // �E�B���h�E�^�C�g��
				WS_VISIBLE | WS_POPUP,  // �E�B���h�E�X�^�C��
				0,                      // �E�B���h�E�̍��p�w���W
				0,                      // �E�B���h�E�̍��p�x���W
				SCREEN_WIDTH,           // �E�B���h�E�̕�
				SCREEN_HEIGHT,          // �E�B���h�E�̍���
				NULL,                   // �e�E�B���h�E�i�Ȃ��j
				NULL,                   // ���j���[�i�Ȃ��j
				hThisInst,              // ���̃v���O�����̃C���X�^���X�̃n���h��
				NULL                    // �ǉ������i�Ȃ��j
				);
		}

		ShowWindow( hWnd, nWinMode ); // �E�B���h�E��\��
		ValidateRect( hWnd, 0 );      // WM_PAINT���Ă΂�Ȃ��悤�ɂ���
		UpdateWindow( hWnd );         // �E�B���h�E�̍X�V

		return ( TRUE );              // InitApp�֐��̐���I��
	}

	//-----------------------------------------------------------------------------
	// �֐����@�F�@InitDirectX()�@
	// �@�\�T�v�F�@Direct Draw �I�u�W�F�N�g�̐���
	// �߂�l�@�F�@����I���̂Ƃ��FDD_OK�A�ُ�I���̂Ƃ��F�G���[�R�[�h
	//-----------------------------------------------------------------------------
	HRESULT InitDirectX( void )
	{
		D3DDISPLAYMODE  DispMode;	// �f�B�X�v���C���[�h
		HRESULT         hr;

		/* DirectX8�I�u�W�F�N�g�̐��� */
		gl_lpD3d = Direct3DCreate9( D3D_SDK_VERSION );
		if( !gl_lpD3d )
		{
			// �I�u�W�F�N�g�������s
			MessageBox( hWnd, "DirectXD3D8�I�u�W�F�N�g�������s", "ERROR", MB_OK );
			return E_FAIL;
		}

		/* DirectX8�̃v���[���e�[�V�����p�����[�^��ݒ� */

		// �f�B�X�v���C�f�[�^�i�[�\���̏�����
		ZeroMemory( &gl_d3dpp, sizeof( D3DPRESENT_PARAMETERS ) );
		// ���݂̃f�B�X�v���C���[�h�f�[�^�擾
		gl_lpD3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &DispMode );
		// �o�b�N�o�b�t�@�t�H�[�}�b�g���f�B�X�v���C�Ɠ�����
		gl_d3dpp.BackBufferFormat = DispMode.Format;
		// ���h�b�g���ݒ�
		gl_d3dpp.BackBufferWidth = SCREEN_WIDTH;
		// �c�h�b�g���ݒ�
		gl_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
		// �o�b�N�o�b�t�@�̐�
		gl_d3dpp.BackBufferCount = 1;
		// �t���b�v�̕��@�i�ʏ�͂��̒萔�ł悢�j
		gl_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//
		gl_d3dpp.EnableAutoDepthStencil = TRUE;
		// �X�e���V���t�H�[�}�b�g
		gl_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		// �E�C���h�E���[�h�̐ݒ�
		gl_d3dpp.Windowed = WINMODE;

		/* �f�o�C�X�I�u�W�F�N�g�̐��� */

		//�����\�ȃn�[�h�E�F�A�f�o�C�X�̐��������݂�
		hr = gl_lpD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &gl_d3dpp, &gl_lpD3ddev );
		if( FAILED( hr ) )
		{
			//�n�[�h�E�F�A�f�o�C�X�̐��������݂�
			hr = gl_lpD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &gl_d3dpp, &gl_lpD3ddev );
			if( FAILED( hr ) )
			{
				//�\�t�g�E�F�A�f�o�C�X�̐��������݂�
				hr = gl_lpD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING, &gl_d3dpp, &gl_lpD3ddev );
				if( FAILED( hr ) )
				{
					//--�ǂ̃f�o�C�X���擾�ł��Ȃ�����
					MessageBox( hWnd, "DirectX�f�o�C�X�������s", "ERROR", MB_OK );
					return E_FAIL;
				}
			}
		}

		return S_OK;
	}

	//-----------------------------------------------------------------------------
	// �֐����@�F�@ReleaseD3D()
	// �@�\�T�v�F�@DirectX8�I�u�W�F�N�g�̊J��
	//-----------------------------------------------------------------------------
	void ReleaseD3D( void )
	{
		//�e�N�X�`���̊J��

		for( auto & i : data_struct::texture )
		{
			if( i.tex_ != NULL )
			{
				i.tex_->Release();
				i.tex_ = NULL;
			}
		}

		//�f�o�C�X�I�u�W�F�N�g�̊J��
		if( gl_lpD3ddev != NULL )
		{
			gl_lpD3ddev->Release();
			gl_lpD3ddev = NULL;
		}
		//DirectX8�I�u�W�F�N�g�̊J��
		if( gl_lpD3d != NULL )
		{
			gl_lpD3d->Release();
			gl_lpD3d = NULL;
		}


	}


	//�E�C���h�E�̍Đݒ�
	void reset_window()
	{
		if( gl_lpD3ddev )
		{
			//�f�B�X�v���C�E�p�����[�^�̒l���g���ăE�C���h�E�����Z�b�g
			gl_lpD3ddev->Reset( &gl_d3dpp );

			//��ʕ��A���ɕ`��̐ݒ���s��
			init_render();
		}
	}


	LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		switch( message )
		{
		case WM_SIZE:	//�E�C���h�E�̃T�C�Y�ύX��
			if( wParam == SIZE_MAXHIDE || wParam == SIZE_MINIMIZED )
				gl_app_active = FALSE;
			else
				gl_app_active = TRUE;
			reset_window();
			break;
		case WM_MOVE:	//�E�C���h�E�̈ړ���
			reset_window();
			break;
		case WM_KEYDOWN: // �L�[���������Ƃ�
			switch( wParam )
			{
			case VK_ESCAPE:	//�G�X�P�[�v�Ȃ����
				PostMessage( hWnd, WM_CLOSE, 0, 0 );
				break;
			}
			break;
		case WM_SETCURSOR: // �J�[�\���̐ݒ�
			SetCursor( hCursor );
			break;
		case WM_DESTROY:        // ����{�^�����N���b�N������
			PostQuitMessage( 0 ); // WM_QUIT���b�Z�[�W�𔭍s
			break;
		default: // ��L�ȊO�̃��b�Z�[�W��Windows�֏�����C����
			return DefWindowProc( hWnd, message, wParam, lParam );
		}
		return 0;
	}
}



