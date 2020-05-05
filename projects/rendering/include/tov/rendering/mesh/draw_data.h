#ifndef TOV_RENDERING_MESH_DRAW_DATA_H
#define TOV_RENDERING_MESH_DRAW_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/math/matrix.h>

#include <tov/rendering/buffers/buffer_object.h>
#include <tov/rendering/pipeline/program_instance.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData
    {
    public:
        DrawData(
            buffers::BufferObject& indexBufferObject, 
            buffers::BufferObject& vertexBufferObject,
            pipeline::ProgramInstance& programInstance
        ) noexcept
            : mIndexBufferObject(indexBufferObject)
            , mVertexBufferObject(vertexBufferObject)
            , mProgramInstance(programInstance)
        {}

        ~DrawData() noexcept = default;

        auto getIndexBufferObject() const -> auto const& { return mIndexBufferObject; }
        auto getVertexBufferObject() const -> auto const& { return mVertexBufferObject; }
        auto getProgramInstance() -> auto & { return mProgramInstance; }
        auto getProgramInstance() const -> auto const& { return mProgramInstance; }

    private:
        buffers::BufferObject& mIndexBufferObject;
        buffers::BufferObject& mVertexBufferObject;
        pipeline::ProgramInstance& mProgramInstance;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
