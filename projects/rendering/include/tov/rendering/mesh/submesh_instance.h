#ifndef TOV_RENDERING_MESH_SUBMESH_INSTANCE_H
#define TOV_RENDERING_MESH_SUBMESH_INSTANCE_H

#include <tov/rendering/rendering_core.h>

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

    class SubmeshInstance
    {
        TOV_MOVABLE_ONLY(SubmeshInstance)

    public:
        SubmeshInstance(
            buffers::IndexBufferObject const& ibo,
            std::vector<buffers::VertexBufferObject*> vbos,
            MaterialInstance* materialInstance
        )
            : mIBO(ibo)
            , mVBOs(vbos)
            , mMaterialInstance(materialInstance)
        {}

        ~SubmeshInstance() = default;

        auto getIndexBufferObject() const -> auto const& { return mIBO; }
        auto getVertexBufferObjects() const -> auto const& { return mVBOs; }

        void setMaterialInstance(MaterialInstance* materialInstance) { mMaterialInstance = materialInstance; }
        auto getMaterialInstance() const { return mMaterialInstance; }

    private:
        buffers::IndexBufferObject const& mIBO;
        std::vector<buffers::VertexBufferObject*> mVBOs;

        MaterialInstance* mMaterialInstance;

        pipeline::ProgramInstance* mProgramInstance = nullptr;
    };

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif
