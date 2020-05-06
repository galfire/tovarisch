#include <rendering/mesh/mesh.h>

#include <rendering/mesh/submesh.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    Mesh::Mesh(MeshManager& manager) noexcept
        : mManager(manager)
        , mDrawDataList({})
    {}

    Mesh::~Mesh() noexcept
    {}

    void Mesh::addDrawData(DrawData drawData)
    {
        mDrawDataList.push_back(drawData);
    }

    auto Mesh::createSubmesh(geometry::Geometry const& geometry, pipeline::Program& program) -> Submesh&
    {
        auto submesh = std::unique_ptr<Submesh>(
            new Submesh(*this, geometry, program)
        );
        mSubmeshes.push_back(std::move(submesh));
        auto ret = mSubmeshes.back().get();
        return *ret;
    }

    auto Mesh::instantiate() const -> MeshInstance
    {
        return MeshInstance(mDrawDataList);
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
