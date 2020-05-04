#include <rendering/mesh/mesh.h>

#include <rendering/mesh/submesh.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    Mesh::Mesh(MeshManager& manager) noexcept
        : mManager(manager)
        , mDrawDataList({})
    {}

    void Mesh::addDrawData(DrawData drawData)
    {
        mDrawDataList.push_back(drawData);
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
