#pragma once

#include "standard_include.h"
#include "directx_include.h"

#include "boost.h"


namespace direct_x_audio
{
	class audio
	{
	private:
		struct sound_buffer
		{
			LPDIRECTSOUNDBUFFER	sound_buf_;
		};

	public:
		LPDIRECTSOUND8 sound_dev_;
		std::vector< sound_buffer > sound_buffer_;
		//load���ă|�C���^��Ԃ��A�I��?

		//�O�����J�p�B�����̃|�C���^��Ԃ�
		//auto�ł��|�C���^���邯��ǁA���낢��ƃA���Ȃ̂ł��������g��

		typedef sound_buffer * sound_buffer_ptr;
		sound_buffer_ptr buf_;//const
		sound_buffer_ptr buf() const;

		audio( const HWND hwnd );

		boost::optional< std::tuple<  WAVEFORMATEX, DWORD, std::string > > \
			open_wave( std::string const & filename ) const;
		sound_buffer_ptr load_wav( std::string const & filename );

		void play_sound( sound_buffer const & buf );



	};
}

