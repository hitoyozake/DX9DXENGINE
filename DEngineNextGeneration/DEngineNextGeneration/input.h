#pragma once

#include <boost/signals2.hpp>
#include <boost/optional.hpp>
#include <functional>
#include <Windows.h>
#include "gamepad.h"

extern HINSTANCE hInst;

namespace input
{
	namespace bs2 = boost::signals2;

	constexpr unsigned int KEY_MAX = 256;
	constexpr unsigned int BUTTON_MAX = joystick::BUTTON_NUM + joystick::DIRECTION_NUM;

	void initialize();

	//keyboardとgamepadのボタンのマッピングをしたい．
	//マッピングしたボタンはどちらか一方を押しているだけでtrueになる

	class input
	{
	public:
		int released( int const KEY ) const; //キーが離されてからのフレーム数を返す
		int pressed( int const KEY ) const; //キーが押されてからのフレーム数
		int released_gamepad( int const KEY ) const;
		int pressed_gamepad( int const KEY ) const; //キーが押されてからのフレーム数
		void update( unsigned char table[] );

	private:
		int gl_keyboard_table[ KEY_MAX ];	//キーボードの状態を格納
		int gl_keyboard_table_r[ KEY_MAX ];	//キーボードの状態を格納 - released
		int gamepad_state_[ BUTTON_MAX ];	//gamepad状態の格納
		int gamepad_state_r[ BUTTON_MAX ];	//gamepad状態を格納 - released

	};

	//directX側の処理でキーボードの状態を毎度更新すること．ユーザサイドで更新処理を呼び出させたくない
	//ユーザサイドアクセスクラス --> directXサイドアクセスクラス

	//このクラスは後で別ファイルに移して隠蔽
	class dx_input
	{
	public:
		bool update();
		void set_signal( 
			std::function< void ( unsigned char table[] ) > const & f );
	//private:
		unsigned char keyboard_table[ KEY_MAX ];//キーボードの状態を格納
		bs2::signal< void( unsigned char table[] ) > signal_;	//inputクラスを更新
		joystick::joystick js_;
	};
}

