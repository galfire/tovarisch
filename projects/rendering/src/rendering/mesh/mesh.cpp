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
        {
            //mSubmeshes2.emplace_back(*this, geometry, vertexDataFormat);
            //auto submesh = &mSubmeshes2.back();
            //return *submesh;
        }

        {
            auto submesh = std::make_unique<Submesh>(*this, geometry, vertexDataFormat);
            mSubmeshes.push_back(std::move(submesh));
        }

        auto submesh = mSubmeshes.back().get();
        mSubmeshes_.push_back(submesh);
        return *submesh;
    }

    auto Mesh::instantiate() -> MeshInstance&
    {
        {
            auto meshInstance = std::make_unique<MeshInstance>(*this);
            mMeshInstances.push_back(std::move(meshInstance));
        }

        auto meshInstance = mMeshInstances.back().get();

        /*for (auto&& submesh : mSubmeshes)
        {
            auto& submeshInstance = submesh->instantiate();
            meshInstance->addSubmeshInstance(submeshInstance);
        }*/
        
        return *meshInstance;
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
