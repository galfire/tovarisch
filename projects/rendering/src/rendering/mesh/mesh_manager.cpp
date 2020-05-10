#include <rendering/mesh/mesh_manager.h>

#include <rendering/buffers/vertex_buffer_format.h>
#include <rendering/buffers/vertex_format.h>

#include <rendering/mesh/mesh.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    MeshManager::MeshManager(buffers::BufferManagerBase& bufferManager) noexcept
        : mBufferManager(bufferManager)
    {
        buffers::VertexFormat vf;
        vf.addAttribute(buffers::VertexAttribute::POSITION, 0);
        vf.addAttribute(buffers::VertexAttribute::NORMAL, 1);
        //vf.addAttribute(buffers::VertexAttribute::COLOUR, 2);
        vf.addAttribute(buffers::VertexAttribute::TEXTURE_COORDINATE, 3);
        buffers::VertexBufferFormat vbf(
            buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
            vf
        );
        mPreferredVertexDataFormat.mapHandleToFormat(0, vbf);
    }

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
