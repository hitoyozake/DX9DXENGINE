#pragma once

#include "boost.h"
#include "animation.h"
#include "directx_include.h"
#include "standard_include.h"

#include <map>
#include <string>

namespace asset
{
	class graph_loader
	{
	public:
		//assetname - handle ‚Ìmap‚ð•Ô‚·
		boost::optional< std::map< std::string, int > > load( std::string const & animlist_filename );
		
	private:
		boost::optional< std::vector< std::string > > load_anim( std::string const & animlist_filename );
		std::vector< std::string > parse( std::string const & str ) const;
	};

	class anim_loader
	{
	public:
		//assetname - handle ‚Ìmap‚ð•Ô‚·
		boost::optional< std::map< std::string, anim::animation > > anim_loader::load( std::string const & animlist_filename, std::map< std::string, int > const & graph_map );
	private:
		std::vector< std::string > parse( std::string const & str ) const;
		boost::optional< std::vector< std::string > > load_anim( std::string const & animlist_filename );
		void register_anim( std::vector< std::string > const & parsed_strs, std::map< std::string, anim::animation > & map, std::map< std::string, int > const & graph_map );
	};


	class asset_pool
	{
	public:
		std::map< std::string, int > const & get_graph_map()
		{
			return std::ref( graph_map_ );
		}

		std::map< std::string, int > const & get_anim_map()
		{
			return std::ref( anim_map_ );
		}

		void set_graph_map( std::map< std::string, int > const & graph_map )
		{
			graph_map_ = graph_map;
		}

		void set_anim_map( std::map< std::string, anim::animation > const & anim_map )
		{
			for( auto const & it : anim_map )
			{
				anim_strage_.push_back( it.second );

				//index‚ðƒnƒ“ƒhƒ‹‚Æ‚µ‚Ä“o˜^
				anim_map_[ it.first ] = anim_strage_.size() - 1;
			}
		}

	private:
		std::map< std::string, int > graph_map_;
		std::map< std::string, int > anim_map_;
		std::vector< anim::animation > anim_strage_;
	};



}





