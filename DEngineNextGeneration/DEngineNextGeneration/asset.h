#pragma once

#include <map>
#include <string>

namespace anim
{
	constexpr int DEFAULT = 0;

	class asset
	{
	public:
		int get_asset( std::string const & asset_name) const
		{
			auto const f = handle_.find( asset_name );

			if( f == handle_.cend() )
			{
				return 0;
			}
			return f->second;
		}

	private:
		std::map< std::string, int > handle_;

	};


	class anim
	{
	public:
		class frame
		{
		public:

		private:
		};

	private:

	};

	class animation_manager
	{
	public:
	private:
	};

}





