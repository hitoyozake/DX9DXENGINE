#include "animation.h"

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include "module.h"

#include <map>

namespace anim
{
	using module::lexical_cast;

	class anim_loader
	{
	public:
		boost::optional< std::vector< std::string > > load_anim( std::string const & animlist_filename );
		void register_anim( std::vector< std::string > const & strs, std::map< std::string, animation > & map );
	private:
		std::vector< std::string > parse( std::string const & str ) const;
	};


	void anim_loader::register_anim( std::vector< std::string > const & strs, std::map< std::string, animation > & map )
	{
		if( strs.size() == 0 )
			return;

		animation anim;
		anim.asset_name = strs[ 0 ];

		for( int i = 1; i < strs.size(); ++i )
		{
			auto const parsed = parse( strs[ i ] );

			frame f;

			enum anim_format
			{
				assetname,
				type,
				x,
				y,
				time,
				r,
				g,
				b,
				a,
				scale,
				angle
			};

			f.x = lexical_cast< int >( parsed[ anim_format::x ] );
			f.y = lexical_cast< int >( parsed[ anim_format::y ] );
			f.r = lexical_cast< int >( parsed[ anim_format::r ] );
			f.g = lexical_cast< int >( parsed[ anim_format::g ] );
			f.b = lexical_cast< int >( parsed[ anim_format::b ] );
			f.a = lexical_cast< int >( parsed[ anim_format::a ] );
			f.angle = lexical_cast< double >( parsed[ anim_format::angle ] );
			f.scale = lexical_cast< double >( parsed[ anim_format::scale ] );
			f.time = lexical_cast< double >( parsed[ anim_format::time ] );
			f.type = lexical_cast< int >( parsed[ anim_format::type ] );
			f.graph_asset_name = parsed[ anim_format::assetname ];

			//prefetchÇÇ±Ç±Ç≈çœÇ‹ÇπÇΩÇ¢ÅDÇ™ÅCédéñÇµâﬂÇ¨Ç©?

			anim.frames.push_back( f );
		}
	}

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

			if( tmp[ 0 ] != '#' && tmp != "" )
				contents.push_back( tmp );
		}

		return boost::optional< std::vector< std::string > >( contents );
	}



}
