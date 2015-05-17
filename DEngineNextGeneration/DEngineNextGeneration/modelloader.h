#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>
#include <boost/optional.hpp>
#include <vector>

namespace model
{

	class i_model
	{
	public:
		virtual std::string const & name() const = 0;
		virtual std::vector< D3DXMATERIAL > material() = 0;
		virtual ~i_model();
		i_model( std::vector< LPDIRECT3DTEXTURE9 > const & t ) : tex_( t ) {}
	private:
		std::vector< LPDIRECT3DTEXTURE9 > tex_;
		LPD3DXMESH mesh_origin_;

	};

	class model : i_model
	{
	public:
		std::string const & name() const;
		std::vector< D3DXMATERIAL > material();

		~model() {}

		model( std::vector< LPDIRECT3DTEXTURE9 > const & t ) : i_model( t )
		{	

		}
	};

	class i_modelloader
	{
	public:
		virtual boost::optional< i_model * > load_model( std::string const & path ) const= 0;

	private:
	};

	class model_loader : i_modelloader
	{
	public:
		boost::optional< i_model * > load_model( std::string const & path ) const;
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
}




