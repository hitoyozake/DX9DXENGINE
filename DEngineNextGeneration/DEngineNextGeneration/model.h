#pragma once

#include "modelloader.h"

namespace model
{
	class model : i_model
	{
	public:
		std::string const & name() const;
		std::vector< D3DXMATERIAL > material();
		bool is_ready() const;
		std::string const & debug_message();
	private:
		std::string name_ = false;
		std::vector< D3DXMATERIAL > material_;
		std::vector< LPDIRECT3DTEXTURE9> tex_;

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


