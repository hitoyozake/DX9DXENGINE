#pragma once

#include "std_common.h"

namespace input
{
	constexpr int KEY_MAX = 256;
	constexpr int PAD_KEY_MAX = 16;
	class input
	{
	public:
		enum BUTTON_TYPE
		{
			E_UP,
			E_DOWN,
			E_RIGHT,
			E_LEFT,
			E_SHOT,
			E_BOMB,
			E_START,
			E_MAX
		};

		void initialize();	//‚±‚Ì’†‚É‰Šú‰»‚ğ‘‚­

		int pressed( BUTTON_TYPE key ) const;
		int released( BUTTON_TYPE key ) const;
		void update();

		bool register_key_to_button( BUTTON_TYPE button, int const key );
		bool register_padkey_to_button( BUTTON_TYPE button, int const key );

	private:
		std::array< int, BUTTON_TYPE::E_MAX > button_pressed_;
		std::array< int, BUTTON_TYPE::E_MAX > button_released_;

		std::array< int, KEY_MAX > key_;
		std::array< int, PAD_KEY_MAX > pad_key_;
		std::array< int, BUTTON_TYPE::E_MAX > pad_bt_map_;
		std::array< int, BUTTON_TYPE::E_MAX > key_bt_map_;


	};
}


