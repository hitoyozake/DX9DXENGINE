#pragma once

#include "baseobject.h"

namespace gm_obj
{
	namespace player
	{
		constexpr int LIFE_MAX = 8;
		constexpr int LIFE_DEFAULT = 3;

		class player
		{
		public:
			base::base_object obj_;

			void update();
		private:
			int life_ = LIFE_DEFAULT;
			
		};


	}


}


