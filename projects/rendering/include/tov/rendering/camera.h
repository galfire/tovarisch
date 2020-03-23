#ifndef TOV_RENDERING_CAMERA_H
#define TOV_RENDERING_CAMERA_H

#include "rendering_core.h"

#include <tov/math/radian.h>

#include "scene_object.h"

#include "transform.h"
#include "view_frustum.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Camera
        : public SceneObject
    {
    public:
        Camera() noexcept;

        void setNearDistance(float nearDistance);
        void setFarDistance(float farDistance);
        void setAspectRatio(float aspectRatio);
        void setFieldOfView(math::Radian fieldOfView);

        void renderScene();

        auto getProjectionMatrix() const { return mViewFrustum.getProjectionMatrix(); }
        auto getViewMatrix() const { return mViewFrustum.getViewMatrix(); }

    private:
        void buildProjectionMatrix(void);
        void buildViewMatrix(void);

    private:
        Transform mCachedTransform;
        ViewFrustum<ProjectionType::PERSPECTIVE> mViewFrustum;
    };

    TOV_NAMESPACE_END
}

#endif