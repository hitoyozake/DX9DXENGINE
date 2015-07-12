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
			//graph‚Ì‰Šú‰»
			if( auto graphlist = game_main::global::graph_loader.load( GRAPHLIST_FILENAME ) )
			{
				//map‚ª•Ô‹p‚³‚ê‚é
				game_main::global::asset_pool.set_graph_map( graphlist.get() );
			}

			//anim‚Ì‰Šú‰»
			if( auto animlist = game_main::global::anim_loader.load( ANIMLIST_FILENAME, game_main::global::asset_pool.get_graph_map() ) )
			{
				game_main::global::asset_pool.set_anim_map( animlist.get() );
			}
			return true;
		}
	}
}