#include "input.h"
#include "directx_include.h"
#include "global.h"

#include <boost/bind.hpp>
#include "gamepad.h"

namespace input
{
	void initialize()
	{
		auto f = boost::bind( & input::update, std::addressof( game_main::global::input ), _1 );
		game_main::global::dx_input.set_signal(	f );

		joystick::initialize_dinput( direct_x_settings::hWnd );
	}

	bool dx_input::update()
	{
		constexpr unsigned char PRESSED = 0x80;
		
		//ゲームパッドのチェック

		if( GetKeyboardState( keyboard_table ) )
		{
			//キーボードのチェック
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

			js_.update();

			//game_main::global::input.update( keyboard_table );
			signal_( keyboard_table );

			return true;
		}
		else
			return false;
	}

	void dx_input::set_signal( std::function< void ( unsigned char table[] ) > const & f )
	{
		signal_.connect( f );
	}


	int input::released( int const KEY ) const
	{
		//TODO enum classに変更
		if( KEY < 0 || KEY >= KEY_MAX )
		{
			return -1;
		}

		return gl_keyboard_table_r[ KEY ];
	}

	int input::pressed( int const KEY ) const
	{
		//TODO enum classに変更
		if( KEY < 0 || KEY >= KEY_MAX )
		{
			return -1;	//return 0でも可?
		}

		return gl_keyboard_table[ KEY ];
	}

	int input::pressed_gamepad( int const KEY ) const
	{
		return this->gamepad_state[ KEY ];
	}

	int input::pressed_gamepad( int const KEY ) const
	{
		return this->gamepad_state[ KEY ];
	}



	void input::update( unsigned char table[] )
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