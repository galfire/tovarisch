#ifndef TOV_RENDERING_CAMERA_H
#define TOV_RENDERING_CAMERA_H

#include "rendering_core.h"

#include "scene_object.h"

#include <tov/math/radian.h>
#include "transform.h"
#include "view_frustum.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class DrawContext;
    class Scene;
    class SceneNode;
    class Viewport;

    class Camera
        : public SceneObject
    {
    public:
        Camera(Scene& scene) noexcept;

        void setNearDistance(float nearDistance);
        void setFarDistance(float farDistance);
        void setAspectRatio(float aspectRatio);
        void setFieldOfView(math::Radian fieldOfView);

        void populateDrawContext(DrawContext& drawContext);
        void populateDrawContext(DrawContext& drawContext, SceneNode& node);

        auto isVisible(SceneNode&) const -> bool;

        auto getProjectionMatrix() const { return mViewFrustum.getProjectionMatrix(); }
        auto getViewMatrix() const { return mViewFrustum.getViewMatrix(); }

        void attachViewport(Viewport& viewport);
        auto getViewports() const -> auto & { return mViewports; }

    private:
        auto getDrawDataList() const -> DrawDataList const& { return mDrawDataList; }

        void buildProjectionMatrix(void);
        void buildViewMatrix(void);

    private:
        Scene& mScene;
        Transform mCachedTransform;
        ViewFrustum<ProjectionType::PERSPECTIVE> mViewFrustum;

        DrawDataList mDrawDataList;

        std::vector<Viewport*> mViewports;
    };

    TOV_NAMESPACE_END
}

#endif