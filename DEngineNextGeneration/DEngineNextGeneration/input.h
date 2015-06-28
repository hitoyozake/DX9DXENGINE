#pragma once

#include <boost/signals2.hpp>

namespace input
{
	namespace bs2 = boost::signals2;

	constexpr unsigned int KEY_MAX = 256;



	class input
	{
	public:
		unsigned int released( int const KEY ) const; //キーが離されてからのフレーム数を返す
		unsigned int pressed( int const KEY ) const; //キーが押されてからのフレーム数

	private:
		unsigned int gl_keyboard_table[ KEY_MAX ] = {};	//キーボードの状態を格納
		
	};

	//directX側の処理でキーボードの状態を毎度更新すること．ユーザサイドで更新処理を呼び出させたくない
	//ユーザサイドアクセスクラス --> directXサイドアクセスクラス

	//このクラスは後で別ファイルに移して隠蔽
	class dx_input
	{
	public:
		bool update();
		void set_signal( void( *fp )( void ) );
	private:
		unsigned char keyboard_table[ KEY_MAX ] = {};//キーボードの状態を格納
		bs2::signal< void() > signal_;	//inputクラスを更新
	};
}

