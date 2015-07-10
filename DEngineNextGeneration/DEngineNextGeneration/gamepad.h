#pragma once

#include "directx.h"
#include <dinput.h>


namespace input
{
	namespace joystick
	{
		extern LPDIRECTINPUT8 p_dinput;
		extern LPDIRECTINPUTDEVICE8 p_dinput_device;

		bool is_joypad_available();
		int initialize_dinput( HWND hwnd );

		constexpr int BUTTON_NUM = 32;
		constexpr int DIRECTION_NUM = 4;

		class joystick
		{
		public:
			void update();
			int initialize_dinput();
		private:
			bool direction_[ DIRECTION_NUM ];
			bool button_[ BUTTON_NUM ];
		};

	}
}



