#include <rendering/mesh/mesh.h>

#include <rendering/buffers/index_buffer_object.h>
#include <rendering/buffers/vertex_buffer_object.h>

#include <rendering/mesh/submesh.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    Mesh::Mesh(MeshManager& manager) noexcept
        : mManager(manager)
    {}

    Mesh::~Mesh() noexcept
    {}

    auto Mesh::createSubmesh(geometry::Geometry const& geometry, VertexDataFormat const& vertexDataFormat) -> Submesh&
    {
        auto i = mSubmeshes.emplace_back(*this, geometry, vertexDataFormat);
        return mSubmeshes[i];
    }

    auto Mesh::instantiate() -> MeshInstance&
    {
        {
            auto meshInstance = std::make_unique<MeshInstance>(*this);
            mMeshInstances.push_back(std::move(meshInstance));
        }

        auto meshInstance = mMeshInstances.back().get();
        
        return *meshInstance;
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
