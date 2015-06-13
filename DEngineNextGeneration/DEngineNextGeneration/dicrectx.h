#include "directx_class_def.h"
#include "model.h"

#pragma once

namespace direct_x_settings
{
	

	class model_mesh
	{
	public:

	private:
		models::i_model & model_;
		LPD3DXMESH mesh_; //for drawing each object
	};

	std::vector< models::i_model * > xtex;
	
}

