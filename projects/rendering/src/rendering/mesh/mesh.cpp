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
        auto submesh = std::unique_ptr<Submesh>(
            new Submesh(*this, geometry, vertexDataFormat)
        );
        mSubmeshes.push_back(std::move(submesh));
        auto ret = mSubmeshes.back().get();
        return *ret;
    }

    auto Mesh::instantiate() const -> MeshInstance
    {
        auto meshInstance = MeshInstance();

        for (auto&& submesh : mSubmeshes)
        {
            auto submeshInstance = submesh->instantiate();
            meshInstance.addSubmeshInstance(submeshInstance);
        }
        
        return meshInstance;
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
