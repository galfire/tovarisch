#include "rendering/mesh/mesh.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	Submesh* Mesh::createSubmesh()
	{
		auto submesh = SubmeshUPtr(
			new Submesh()
		);
		mSubmeshes.push_back(std::move(submesh));
		auto ret = mSubmeshes.back().get();
		return ret;
	}

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}