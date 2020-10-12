#include <rendering/mesh/mesh_manager.h>

#include <rendering/mesh/mesh.h>
#include <rendering/mesh/vertex_data_format.h>
#include <rendering/geometry/rectangle.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    MeshManager::MeshManager(buffers::BufferManagerBase& bufferManager) noexcept
        : mBufferManager(bufferManager)
    {}

    MeshManager::~MeshManager() noexcept
    {}

    void MeshManager::initialize()
    {
        auto vertexDataFormat = VertexDataFormat();
        {
            buffers::VertexFormat vf;
            vf.addAttribute(buffers::VertexAttribute::POSITION, 0);
            vf.addAttribute(buffers::VertexAttribute::TEXTURE_COORDINATE, 1);
            buffers::VertexBufferFormat vbf(
                buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
                vf
            );
            vertexDataFormat.mapHandleToFormat(0, vbf);
        }

        mFullscreenQuad = create();
        {
            auto geometry = geometry::Rectangle(2.0f, 2.0f); // [ -1, +1 ], [ -1, +1 ]
            mFullscreenQuad->createSubmesh(geometry, vertexDataFormat);
        }
    }

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
