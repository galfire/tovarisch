#ifndef TOV_RENDERING_DRAW_CONTEXT_H
#define TOV_RENDERING_DRAW_CONTEXT_H

#include <tov/rendering/rendering_core.h>

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Camera;
    class SceneNode;

    class DrawContext
    {
    public:
        DrawContext() = default;
        ~DrawContext() = default;

        void setCamera(Camera* camera) { mCamera = camera; }
        auto getCamera() const { return mCamera; }

        auto getSceneNodes() -> auto& { return mSceneNodes; }

    private:
        Camera* mCamera = nullptr;
        std::vector<SceneNode*> mSceneNodes;
    };

    TOV_NAMESPACE_END // rendering
}

#endif
