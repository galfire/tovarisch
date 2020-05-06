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
    public:
        MeshManager(buffers::BufferManagerBase& bufferManager) noexcept;
        ~MeshManager() noexcept;

        auto create() -> Mesh*;
        auto getBufferManager() const -> auto & { return mBufferManager; }
        auto getPreferredVertexDataFormat() const -> auto const& { return mPreferredVertexDataFormat; }

    private:
        buffers::BufferManagerBase& mBufferManager;

        VertexDataFormat mPreferredVertexDataFormat;

        using MeshList = std::vector<std::unique_ptr<Mesh>>;
        MeshList mMeshList;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
