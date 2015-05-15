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
	private:
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
	};
}




