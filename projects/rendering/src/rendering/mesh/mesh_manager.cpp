#include <rendering/mesh/mesh_manager.h>

#include <rendering/mesh/mesh.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    MeshManager::MeshManager(buffers::BufferManagerBase& bufferManager) noexcept
        : mBufferManager(bufferManager)
    {}

    MeshManager::~MeshManager() noexcept
    {}

    auto MeshManager::create() -> Mesh*
    {
        auto mesh = std::unique_ptr<Mesh>(
            new Mesh(*this)
        );
        mMeshList.push_back(std::move(mesh));
        auto ret = mMeshList.back().get();
        return static_cast<Mesh*>(ret);
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
