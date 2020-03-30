#include "rendering/camera.h"

#include "rendering/scene_node.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Camera::Camera(Scene& scene) noexcept
        : mScene(scene)
        , mCachedTransform()
        , mViewFrustum()
    {}

    void Camera::setNearDistance(float nearDistance)
    {
        mViewFrustum.setNearDistance(nearDistance);
        buildProjectionMatrix();
    }

    void Camera::setFarDistance(float farDistance)
    {
        mViewFrustum.setFarDistance(farDistance);
        buildProjectionMatrix();
    }

    void Camera::setAspectRatio(float aspectRatio)
    {
        mViewFrustum.setAspectRatio(aspectRatio);
        buildProjectionMatrix();
    }

    void Camera::setFieldOfView(math::Radian fieldOfView)
    {
        mViewFrustum.setFieldOfViewY(fieldOfView);
        buildProjectionMatrix();
    }

    void Camera::render()
    {
        this->buildViewMatrix();
    }

    void Camera::buildProjectionMatrix()
    {
        mViewFrustum.buildProjectionMatrix();
    }

    void Camera::buildViewMatrix()
    {
        if (mParentSceneNode &&
            mCachedTransform != mParentSceneNode->getDerivedTransform())
        {
            mCachedTransform = mParentSceneNode->getDerivedTransform();
            mViewFrustum.buildViewMatrix(mCachedTransform);
        }
    }

    TOV_NAMESPACE_END
}
