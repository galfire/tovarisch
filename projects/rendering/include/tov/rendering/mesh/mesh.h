#ifndef TOV_RENDERING_MESH_MESH_H
#define TOV_RENDERING_MESH_MESH_H

#include <tov/rendering/rendering_core.h>

#include "submesh.h"
#include <tov/rendering/geometry/geometry.h>

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	template<class DerivedBufferManagerT> class MeshManager;

	class MeshBase
	{
		TOV_MOVABLE_ONLY(MeshBase)

	public:
		MeshBase() noexcept = default;
		virtual ~MeshBase() noexcept = default;
	};

	template<class DerivedBufferManagerT>
	class Mesh
		: public MeshBase
	{
	public:
		Mesh(MeshManager<DerivedBufferManagerT>& manager) noexcept
			: mManager(manager)
		{}

		~Mesh() noexcept = default;

		auto getManager() const -> auto const & { return mManager; }

		//auto createSubmesh(uint numVertices, uint numIndices)
		//{
		//	auto submesh = SubmeshUPtr(
		//		new Submesh(*this, numVertices, numIndices)
		//	);
		//	mSubmeshes.push_back(std::move(submesh));
		//	auto ret = mSubmeshes.back().get();
		//	return ret;
		//}

		auto createSubmesh(const tov::rendering::geometry::Geometry& geometry)
		{
			auto submesh = SubmeshUPtr(
				new Submesh(*this, geometry)
			);
			mSubmeshes.push_back(std::move(submesh));
			auto ret = mSubmeshes.back().get();
			return ret;
		}

	private:
		MeshManager<DerivedBufferManagerT>& mManager;

		using SubmeshList = std::vector<SubmeshUPtr>;
		SubmeshList mSubmeshes;
	};

	using MeshUPtr = std::unique_ptr<MeshBase>;

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_MESH_H
