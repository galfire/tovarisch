#ifndef TOV_RENDERING_MESH_SUBMESH_INSTANCE_H
#define TOV_RENDERING_MESH_SUBMESH_INSTANCE_H

#include <tov/rendering/rendering_core.h>

#include "draw_data.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class IndexBufferObject;
    class VertexBufferObject;

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_BEGIN(pipeline)

    class ProgramInstance;

    TOV_NAMESPACE_END // pipeline

    class MaterialInstance;

    TOV_NAMESPACE_BEGIN(mesh)
    
    class DrawDataContext;

    class SubmeshInstance
    {
        TOV_MOVABLE_ONLY(SubmeshInstance)

    public:
        SubmeshInstance(
            DrawDataContext const& drawDataContext,
            buffers::IndexBufferObject const& ibo,
            std::vector<buffers::VertexBufferObject*> vbos,
            MaterialInstance* materialInstance
        )
            : mDrawDataContext(drawDataContext)
            , mIBO(ibo)
            , mVBOs(vbos)
            , mMaterialInstance(materialInstance)
        {}

        ~SubmeshInstance() = default;

        auto getDrawDataContext() const -> auto const& { return mDrawDataContext; }
        auto getIndexBufferObject() const -> auto const& { return mIBO; }

        void setMaterialInstance(MaterialInstance* materialInstance) { mMaterialInstance = materialInstance; }
        auto getMaterialInstance() const { return mMaterialInstance; }

    private:
        DrawDataContext const& mDrawDataContext;

        buffers::IndexBufferObject const& mIBO;
        std::vector<buffers::VertexBufferObject*> mVBOs;

        MaterialInstance* mMaterialInstance;

        pipeline::ProgramInstance* mProgramInstance = nullptr;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
