#include "global.h"


namespace game_main
{
	namespace global
	{
		//入力
		input::input input;
		input::dx_input dx_input; //後でうまく隠蔽化したい

		asset::anim_loader anim_loader;
		asset::graph_loader graph_loader;
		asset::asset_pool asset_pool;


	}
}