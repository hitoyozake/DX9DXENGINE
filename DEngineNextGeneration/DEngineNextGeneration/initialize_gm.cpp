#include "initialize.h"
#include "global.h"

namespace game_main
{
	namespace initialize
	{
		std::string const GRAPHLIST_FILENAME = "./asset/graphlist.as";
		std::string const ANIMLIST_FILENAME = "./asset/animlist.as";

		bool initialize()
		{
			//graphの初期化
			if( auto graphlist = game_main::global::graph_loader.load( GRAPHLIST_FILENAME ) )
			{
				//mapが返却される
				game_main::global::asset_pool.set_graph_map( graphlist.get() );
			}

			//animの初期化
			if( auto animlist = game_main::global::anim_loader.load( ANIMLIST_FILENAME, game_main::global::asset_pool.get_graph_map() ) )
			{
				game_main::global::asset_pool.set_anim_map( animlist.get() );
			}
			return true;
		}
	}
}