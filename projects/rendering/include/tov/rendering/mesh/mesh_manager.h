#ifndef TOV_RENDERING_MESH_MESH_MANAGER_H
#define TOV_RENDERING_MESH_MESH_MANAGER_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/vertex_format.h>
#include <tov/rendering/buffers/vertex_buffer_format.h>
#include "mesh.h"
#include "vertex_data_format.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    template<class DerivedBufferManagerT> class BufferManager;

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(mesh)

    template<class DerivedBufferManagerT>
    class MeshManager
    {
        using MeshT = Mesh<DerivedBufferManagerT>;

    public:
        MeshManager(buffers::BufferManagerBase& bufferManager) noexcept
            : mBufferManager(static_cast<DerivedBufferManagerT&>(bufferManager))
        {
                buffers::VertexFormat vf;
                vf.addAttribute(buffers::VertexAttribute::POSITION, 0);
                vf.addAttribute(buffers::VertexAttribute::NORMAL, 1);
                vf.addAttribute(buffers::VertexAttribute::COLOUR, 2);
                vf.addAttribute(buffers::VertexAttribute::TEXTURE_COORDINATE, 3);
                buffers::VertexBufferFormat vbf(
                    buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
                    vf
                );
                mPreferredVertexDataFormat.mapHandleToFormat(0, vbf);
        }

        ~MeshManager() noexcept = default;

        auto create()
        {
            auto mesh = MeshUPtr(
                new MeshT(*this)
            );
            mMeshList.push_back(std::move(mesh));
            auto ret = mMeshList.back().get();
            return static_cast<MeshT*>(ret);
        }

        auto getBufferManager() const -> auto & { return mBufferManager; }
        auto getPreferredVertexDataFormat() const -> auto const & { return mPreferredVertexDataFormat; }

    private:
        buffers::BufferManager<DerivedBufferManagerT>& mBufferManager;

        VertexDataFormat mPreferredVertexDataFormat;

        using MeshList = std::vector<MeshUPtr>;
        MeshList mMeshList;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
