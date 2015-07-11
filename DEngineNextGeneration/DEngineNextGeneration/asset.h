#pragma once

#include "boost.h"
#include "directx_include.h"
#include "standard_include.h"

#include <map>
#include <string>

namespace anim
{
	class graph_loader
	{
	public:
		boost::optional< std::vector< std::string > > load_anim( std::string const & animlist_filename );
		void register_anim( std::vector< std::string > const & strs, std::map< std::string, int > & map );

	private:
		std::vector< std::string > parse( std::string const & str ) const;
	};


	class asset_pool
	{
	public:
	private:
	};



}





