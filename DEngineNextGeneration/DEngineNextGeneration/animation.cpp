#include "animation.h"

#include <boost/optional.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>


namespace anim
{

	class anim_loader
	{
	public:
		boost::optional< std::vector< std::string > > load_anim( std::string const & animlist_filename );
		void register_anim( std::vector< std::vector< std::string > > const & anims );
	private:
		std::vector< std::string > parse( std::string const & str ) const;
	};

	std::vector< std::string > anim_loader::parse( std::string const & str ) const
	{
		std::vector< std::string > result;

		boost::split( result, str, boost::is_any_of( "," ) );

		return result;
	}

	boost::optional< std::vector< std::string > > anim_loader::load_anim( std::string const & animlist_filename )
	{
		std::ifstream animlist( animlist_filename );

		if( ! animlist )
		{
			return boost::none;
		}

		std::vector< std::string > contents;

		while( !animlist.eof() )
		{
			std::string tmp;
			std::getline( animlist, tmp );

			if( tmp[ 0 ] != '#' )
				contents.push_back( tmp );
		}

		return boost::optional< std::vector< std::string > >( contents );
	}



}
