#ifndef TOV_RENDERING_SCENE_OBJECT_H
#define TOV_RENDERING_SCENE_OBJECT_H

#include "rendering_core.h"

#include "mesh/draw_data.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class SceneNode;

    class SceneObject
    {
        friend class SceneNode;

    public:
        SceneObject() = default;
        virtual ~SceneObject() = default;

        auto getParentSceneNode() const { return mParentSceneNode; }

        using DrawDataList = std::span<const mesh::DrawData>;
        virtual auto getDrawDataList() const -> DrawDataList TOV_ABSTRACT;

    private:
        void attachToSceneNode(SceneNode* sceneNode);

    protected:
        SceneNode* mParentSceneNode = nullptr;
    };

    TOV_NAMESPACE_END
}

#endif
