#ifndef TOV_RENDERING_SCENE_OBJECT_H
#define TOV_RENDERING_SCENE_OBJECT_H

#include "rendering_core.h"

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

    private:
        void attachToSceneNode(SceneNode* sceneNode);

    protected:
        SceneNode* mParentSceneNode = nullptr;
    };

    using SceneObjectUPtr = std::unique_ptr<SceneObject>;

    TOV_NAMESPACE_END
}

#endif
