#include "model.h"

namespace model
{
	std::string const & model::name() const
	{
		return name_;
	}

	std::vector< D3DXMATERIAL > model::material()
	{
		return material_;
	}

	
}