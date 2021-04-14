#ifndef TOV_RENDERING_MESH_SUBMESH_INSTANCE_H
#define TOV_RENDERING_MESH_SUBMESH_INSTANCE_H

#include <tov/rendering/rendering_core.h>
#include <tov/rendering/buffers/index_buffer_object.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class MaterialInstance;

    TOV_NAMESPACE_BEGIN(mesh)
    
    class DrawDataContext;

    class SubmeshInstance
    {
        TOV_MOVABLE_ONLY(SubmeshInstance)

    public:
        SubmeshInstance(
            DrawDataContext const& drawDataContext,
            buffers::IndexBufferObject ibo,
            MaterialInstance* materialInstance
        )
            : mDrawDataContext(drawDataContext)
            , mIBO(ibo)
            , mMaterialInstance(materialInstance)
        {}
        ~SubmeshInstance() = default;

        auto getDrawDataContext() const -> auto const& { return mDrawDataContext; }
        auto getIndexBufferObject() const { return mIBO; }
        void setMaterialInstance(MaterialInstance* materialInstance) { mMaterialInstance = materialInstance; }
        auto getMaterialInstance() const { return mMaterialInstance; }

    private:
        DrawDataContext const& mDrawDataContext;
        buffers::IndexBufferObject mIBO;
        MaterialInstance* mMaterialInstance;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
