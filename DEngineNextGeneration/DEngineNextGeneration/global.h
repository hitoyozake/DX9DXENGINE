#pragma once

#include "input.h"
#include "asset.h"
#include "animation.h"

namespace game_main
{
	namespace global
	{
		extern input::input input;
		//externéŒ¾‚È‚Ç
		extern input::dx_input dx_input; //Œã‚Å‚¤‚Ü‚­‰B•Á‰»‚µ‚½‚¢
		
		extern asset::anim_loader anim_loader;
		extern asset::graph_loader graph_loader;
		extern asset::asset_pool asset_pool;
	}


}