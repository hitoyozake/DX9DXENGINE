#pragma once

#include <string>
#include "directx_class_def.h"

namespace tex2d
{
	void create_texture( std::string const & filename )
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
			return;
		}
		else
		{
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
		}
	}


	class texture2d
	{

	};




}






