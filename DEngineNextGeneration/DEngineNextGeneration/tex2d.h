#pragma once

#include <string>
#include "directx_class_def.h"

namespace tex2d
{
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


	class texture2d
	{

	};




}






