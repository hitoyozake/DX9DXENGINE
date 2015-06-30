#include "input.h"
#include "directx_include.h"
#include "global.h"

namespace input
{
	bool dx_input::update()
	{
		constexpr unsigned char PRESSED = 0x80;
		
		if( GetKeyboardState( keyboard_table ) )
		{
			for( std::size_t i = 0; i < KEY_MAX; ++i )
			{
				if( keyboard_table[ i ] & PRESSED )
				{
					keyboard_table[ i ] = 1;
				}
				else
				{
					keyboard_table[ i ] = 0;
				}
			}
			game_main::global::input.copy( keyboard_table );
			signal_();

			return true;
		}
		else
			return false;
	}

	void dx_input::set_signal( void( *fp )( void ) )
	{
		signal_.connect( fp );
	}

	int input::released( int const KEY ) const
	{
		//TODO enum class�ɕύX
		if( KEY < 0 || KEY >= KEY_MAX )
		{
			return -1;
		}

		return gl_keyboard_table_r[ KEY ];
	}

	int input::pressed( int const KEY ) const
	{
		//TODO enum class�ɕύX
		if( KEY < 0 || KEY >= KEY_MAX )
		{
			return -1;
		}

		return gl_keyboard_table[ KEY ];
	}

	void input::copy( unsigned char table[] )
	{
		for( std::size_t i = 0; i < KEY_MAX; ++i )
		{
			if( table[ i ] > 0 )
			{
				++gl_keyboard_table[ i ];
				gl_keyboard_table_r[ i ] = 0;
			}
			else
			{
				++gl_keyboard_table_r[ i ];
				gl_keyboard_table[ i ] = 0;
			}
		}
	}




}