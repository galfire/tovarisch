#ifndef TOV_RENDERING_MESH_MESH_MANAGER_H
#define TOV_RENDERING_MESH_MESH_MANAGER_H

#include <tov/rendering/rendering_core.h>

#include "vertex_data_format.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class BufferManagerBase;

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(mesh)

    class Mesh;

    class MeshManager
    {
        TOV_MOVABLE_ONLY(MeshManager)

    public:
        MeshManager(buffers::BufferManagerBase& bufferManager) noexcept;
        ~MeshManager() noexcept;

        void initialize();

        auto create() -> Mesh*;
        auto getBufferManager() const -> auto & { return mBufferManager; }

        auto getFullscreenQuad() const -> auto& { return *mFullscreenQuad; }

    private:
        buffers::BufferManagerBase& mBufferManager;

        Mesh* mFullscreenQuad;

        using MeshList = std::vector<std::unique_ptr<Mesh>>;
        MeshList mMeshList;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
