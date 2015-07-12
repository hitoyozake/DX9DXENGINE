#pragma once

#include "boost.h"
#include "standard_include.h"

namespace module
{
	template< class T >
	T lexical_cast( std::string const & t )
	{
		std::string tmp = t;
		boost::replace_all( tmp, " ", "" );
		return boost::lexical_cast< T >( tmp );
	}
}




