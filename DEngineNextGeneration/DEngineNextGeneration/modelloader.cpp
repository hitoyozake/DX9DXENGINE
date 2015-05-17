#include "modelloader.h"

namespace model
{
	boost::optional< i_model * > model_loader::load_model( std::string const & path ) const
	{
		LPD3DXBUFFER material_buffer, effect_buffer, adjacency_buffer;
		LPD3DXMESH mesh;
		DWORD material_num = 0;

		LPDIRECT3DDEVICE9 device = nullptr;//fix me

		auto const result_loading = D3DXLoadMeshFromX(
			path.c_str(),
			D3DXMESH_SYSTEMMEM,
			device,
			nullptr,
			std::addressof( material_buffer ),
			nullptr,
			std::addressof( material_num ),
			std::addressof( mesh )
			);

		if( result_loading != S_OK )
			return boost::none;

		if( !( mesh->GetFVF() & D3DFVF_NORMAL ) )
		{
			//–@ü‚ª–³‚¢ê‡‚Ìˆ—
		}

		auto material = std::vector< D3DXMATERIAL >( static_cast< D3DXMATERIAL * >( material_buffer->GetBufferPointer() ),
			static_cast< D3DXMATERIAL * >( material_buffer->GetBufferPointer() ) + material_num );

		std::vector< LPDIRECT3DTEXTURE9 > tex( material_num, nullptr );

		for( DWORD i = 0; i < material.size(); ++i )
		{
			if( material[ i ].pTextureFilename != nullptr )
			{
				//load texture
				D3DXCreateTextureFromFile( device, material[ i ].pTextureFilename, std::addressof( tex[ i ] ) );

			}

			material[ i ].MatD3D.Ambient = material[ i ].MatD3D.Diffuse;
		}
		material_buffer->Release();


	}

}



