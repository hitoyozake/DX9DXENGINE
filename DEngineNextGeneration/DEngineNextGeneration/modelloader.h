#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <boost/optional.hpp>
#include <vector>

namespace models
{

	class i_model
	{
	public:
		virtual std::string const & name() const
		{
			return "aa";
		}
		virtual std::vector< D3DMATERIAL9 > material() = 0;
		virtual std::vector< LPDIRECT3DTEXTURE9 > tex() = 0;
		virtual LPD3DXMESH mesh() = 0;
		virtual ~i_model();
		i_model();
	private:
		LPD3DXMESH mesh_origin_;
	};

	
	class i_modelloader
	{
	public:
		virtual boost::optional< i_model * > load_model( std::string const & path, LPDIRECT3DDEVICE9 const device ) const = 0;

	private:
	};

	class model_loader : i_modelloader
	{
	public:
		boost::optional< i_model * > load_model( std::string const & path, LPDIRECT3DDEVICE9 const device ) const;
	private:
	};

	class i_model_object
	{
	public:
		virtual std::vector< ID3DXMesh > mesh() = 0;
		virtual D3DXVECTOR4 position() const = 0;
	private:
	};

	class model_object : i_model_object
	{
	public:
		
	private:
	};

	static model_loader mdl_loader;
}




