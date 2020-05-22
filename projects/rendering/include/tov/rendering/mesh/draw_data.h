#ifndef TOV_RENDERING_MESH_DRAW_DATA_H
#define TOV_RENDERING_MESH_DRAW_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/math/matrix.h>

#include <tov/rendering/buffers/index_buffer_object.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>
#include <tov/rendering/pipeline/program_instance.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    class DrawData
    {
    public:
        DrawData(
            buffers::IndexBufferObject const& indexBufferObject, 
            std::vector<buffers::VertexBufferObject*> const& vertexBufferObjects,
            pipeline::ProgramInstance const& programInstance
        ) noexcept
            : mIndexBufferObject(indexBufferObject)
            , mVertexBufferObjects(vertexBufferObjects)
            , mProgramInstance(programInstance)
        {}

        ~DrawData() noexcept = default;

        auto getIndexBufferObject() const -> auto const& { return mIndexBufferObject; }
        auto getVertexBufferObjects() const -> auto const& { return mVertexBufferObjects; }
        auto getProgramInstance() -> auto & { return mProgramInstance; }
        auto getProgramInstance() const -> auto const& { return mProgramInstance; }

    private:
        buffers::IndexBufferObject const& mIndexBufferObject;
        std::vector<buffers::VertexBufferObject*> const& mVertexBufferObjects;
        pipeline::ProgramInstance const& mProgramInstance;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
