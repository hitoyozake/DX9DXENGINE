#pragma once

namespace game
{
	namespace scene
	{
		enum game_scene
		{
			E_TITLE,
			E_MENU,
			E_GAME,
			E_END
		};

		class scene_manager
		{
		public:
			void change_scene( game_scene scene );
		private:
			int state_;	//èÛë‘
			game_scene scene;
		};
	}
}