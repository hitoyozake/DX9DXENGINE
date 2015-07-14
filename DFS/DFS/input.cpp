#include "input.h"
#include "std_common.h"

namespace input
{
	void input::initialize()
	{
		std::fill( this->key_bt_map_.begin(), this->key_bt_map_.end(), 0 );
		std::fill( this->pad_bt_map_.begin(), this->pad_bt_map_.end(), 0 );

		register_key_to_button( BUTTON_TYPE::E_UP, KEY_INPUT_UP );
		register_key_to_button( BUTTON_TYPE::E_DOWN, KEY_INPUT_DOWN );
		register_key_to_button( BUTTON_TYPE::E_RIGHT, KEY_INPUT_RIGHT );
		register_key_to_button( BUTTON_TYPE::E_LEFT, KEY_INPUT_LEFT );

	}


	int input::pressed( BUTTON_TYPE key ) const
	{
		if( key >= BUTTON_TYPE::E_MAX )
		{
			throw std::exception( "error, key is invalid" );
		}
		return button_pressed_[ static_cast< int >( key ) ];

	}
	int input::released( BUTTON_TYPE key ) const
	{
		if( key >= BUTTON_TYPE::E_MAX )
		{
			throw std::exception( "error, key is invalid" );
		}
		return button_released_[ static_cast< int >( key ) ];
	}

	void input::update()
	{
		std::array< char, KEY_MAX > all_keys;
		GetHitKeyStateAll( all_keys.data() );

		int const pad_input = GetJoypadInputState( DX_INPUT_PAD1 );

		int mul = 1;

		for( int i = 0; i < PAD_KEY_MAX; ++i )
		{
			if( pad_input & mul )
			{
				++pad_key_[ i ];
			}
			else
			{
				pad_key_[ i ] = 0;

			}
			mul *= 2;
		}

		for( std::size_t i = 0; i < BUTTON_TYPE::E_MAX; ++i )
		{
			if( all_keys[ key_bt_map_[ i ] ] == 1 || pad_key_[ pad_bt_map_[ i ] ] == 1 )
			{
				++button_pressed_[ i ];
				button_released_[ i ] = 0;
			}
			else
			{
				button_pressed_[ i ] = 0;
				++button_released_[ i ];
			}
		}
	}


	bool input::register_key_to_button( BUTTON_TYPE button, int const key )
	{
		if( button >= BUTTON_TYPE::E_MAX )
			return false;

		bool find = false;

		for( auto & i : key_bt_map_ )
		{
			if( i == key )
			{
				find = true;
				std::swap( key_bt_map_[ button ], i );
				break;
			}
		}

		//使っていないキーだったら単純に登録
		if( find == false )
		{
			key_bt_map_[ button ] = key;
		}

		return true;
	}
	bool input::register_padkey_to_button( BUTTON_TYPE button, int const key )
	{
		if( button >= BUTTON_TYPE::E_MAX )
			return false;

		bool find = false;

		for( auto & i : pad_bt_map_ )
		{
			if( i == key )
			{
				find = true;
				std::swap( pad_bt_map_[ button ], i );
				break;
			}
		}

		//使っていないキーだったら単純に登録
		if( find == false )
		{
			pad_bt_map_[ button ] = key;
		}

		return true;
	}

}


