#ifndef TOV_RENDERING_MESH_SUBMESH_H
#define TOV_RENDERING_MESH_SUBMESH_H

#include <tov/rendering/rendering_core.h>

#include "index_data.h"
#include "vertex_data.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	class Submesh
	{
		TOV_MOVABLE_ONLY(Submesh)

	public:
		Submesh() = default;
		~Submesh() = default;

	private:
		IndexDataUPtr mIndexData;
		VertexDataUPtr mVertexData;
	};

	using SubmeshUPtr = std::unique_ptr<Submesh>;

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_SUBMESH_H
