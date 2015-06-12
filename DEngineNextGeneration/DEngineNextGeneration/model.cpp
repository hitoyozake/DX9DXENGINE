#include "model.h"

namespace models
{
	std::string const & model::name() const
	{
		return name_;
	}
	
	model::model( std::vector< LPDIRECT3DTEXTURE9 > const & tex, std::vector< D3DMATERIAL9 > const & m, LPD3DXMESH const & mesh )
		: tex_(tex), material_(m), mesh_( mesh )
	{
	}

	LPD3DXMESH model::mesh()
	{
		return mesh_;
	}


	std::vector< D3DMATERIAL9 > model::material()
	{
		return material_;
	}
	
	std::vector< LPDIRECT3DTEXTURE9 > model::tex()
	{
		return tex_;
	}

	
}