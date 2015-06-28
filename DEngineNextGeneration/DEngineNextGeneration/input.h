#pragma once

#include <boost/signals2.hpp>

namespace input
{
	namespace bs2 = boost::signals2;

	constexpr unsigned int KEY_MAX = 256;



	class input
	{
	public:
		unsigned int released( int const KEY ) const; //�L�[��������Ă���̃t���[������Ԃ�
		unsigned int pressed( int const KEY ) const; //�L�[��������Ă���̃t���[����

	private:
		unsigned int gl_keyboard_table[ KEY_MAX ] = {};	//�L�[�{�[�h�̏�Ԃ��i�[
		
	};

	//directX���̏����ŃL�[�{�[�h�̏�Ԃ𖈓x�X�V���邱�ƁD���[�U�T�C�h�ōX�V�������Ăяo���������Ȃ�
	//���[�U�T�C�h�A�N�Z�X�N���X --> directX�T�C�h�A�N�Z�X�N���X

	//���̃N���X�͌�ŕʃt�@�C���Ɉڂ��ĉB��
	class dx_input
	{
	public:
		bool update();
		void set_signal( void( *fp )( void ) );
	private:
		unsigned char keyboard_table[ KEY_MAX ] = {};//�L�[�{�[�h�̏�Ԃ��i�[
		bs2::signal< void() > signal_;	//input�N���X���X�V
	};
}

