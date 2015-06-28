#include "input.h"
#include "directx_include.h"

namespace input
{
	bool dx_input::update()
	{
		if( !GetKeyboardState( keyboard_table ) )
		{
			return true;
		}
		else
			return false;
	}

	void set_signal( void( *fp )( void ) )
	{

	}





}