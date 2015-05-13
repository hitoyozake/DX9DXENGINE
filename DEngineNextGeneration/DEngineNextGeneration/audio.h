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
		//loadしてポインタを返す、的な?

		//外部公開用。こいつのポインタを返す
		//autoでもポインタ取れるけれど、いろいろとアレなのでこっちを使う

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

