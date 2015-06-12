#pragma once

#include "modelloader.h"

namespace models
{
	class model : public i_model
	{
	public:
		std::string const & name() const;
		std::vector< D3DMATERIAL9 > material();
		std::vector< LPDIRECT3DTEXTURE9 > tex();
		LPD3DXMESH mesh();

		bool is_ready() const;
		std::string const & debug_message();

		model( std::vector< LPDIRECT3DTEXTURE9 > const & tex, std::vector< D3DMATERIAL9 > const & m, LPD3DXMESH const & mesh );

	private:
		std::string name_ = "";
		std::vector< D3DMATERIAL9 > material_;
		std::vector< LPDIRECT3DTEXTURE9> tex_;

		LPD3DXMESH mesh_;

		bool ready_flag_;
		std::string debug_message_;

	};

	class modelloader : i_modelloader
	{
	public:
		boost::optional< i_model * > load_model( std::string const & path ) const;
	private:
	};


}


