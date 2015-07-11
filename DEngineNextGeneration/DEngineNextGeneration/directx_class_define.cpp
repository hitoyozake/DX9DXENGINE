#include "directx_class_def.h"
#include "standard_include.h"

namespace direct_x_settings
{
	namespace data_struct
	{
		std::vector< square > vertex;
		std::vector< graphic_information > texture;

		class texture_manager
		{
		public:
			graphic_information const & get( int const handle ) const
			{
				return texture_[ handle ];
			}
		private:
			std::vector< graphic_information > texture_;

		};
	}
}