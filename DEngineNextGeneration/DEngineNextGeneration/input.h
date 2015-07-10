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

	//keyboard��gamepad�̃{�^���̃}�b�s���O���������D
	//�}�b�s���O�����{�^���͂ǂ��炩����������Ă��邾����true�ɂȂ�

	class input
	{
	public:
		int released( int const KEY ) const; //�L�[��������Ă���̃t���[������Ԃ�
		int pressed( int const KEY ) const; //�L�[��������Ă���̃t���[����
		int released_gamepad( int const KEY ) const;
		int pressed_gamepad( int const KEY ) const; //�L�[��������Ă���̃t���[����
		void update( unsigned char table[] );

	private:
		int gl_keyboard_table[ KEY_MAX ];	//�L�[�{�[�h�̏�Ԃ��i�[
		int gl_keyboard_table_r[ KEY_MAX ];	//�L�[�{�[�h�̏�Ԃ��i�[ - released
		int gamepad_state_[ BUTTON_MAX ];	//gamepad��Ԃ̊i�[
		int gamepad_state_r[ BUTTON_MAX ];	//gamepad��Ԃ��i�[ - released

	};

	//directX���̏����ŃL�[�{�[�h�̏�Ԃ𖈓x�X�V���邱�ƁD���[�U�T�C�h�ōX�V�������Ăяo���������Ȃ�
	//���[�U�T�C�h�A�N�Z�X�N���X --> directX�T�C�h�A�N�Z�X�N���X

	//���̃N���X�͌�ŕʃt�@�C���Ɉڂ��ĉB��
	class dx_input
	{
	public:
		bool update();
		void set_signal( 
			std::function< void ( unsigned char table[] ) > const & f );
	//private:
		unsigned char keyboard_table[ KEY_MAX ];//�L�[�{�[�h�̏�Ԃ��i�[
		bs2::signal< void( unsigned char table[] ) > signal_;	//input�N���X���X�V
		joystick::joystick js_;
	};
}

