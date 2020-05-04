#include "rendering/camera.h"

#include "rendering/scene.h"
#include "rendering/scene_node.h"

#include "rendering/draw_context.h"

#include "rendering/mesh/draw_data.h"

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

    auto Camera::isVisible(SceneNode& node) const -> bool
    {
        return true;
    }

    void Camera::attachViewport(Viewport& viewport)
    {
        mViewports.push_back(&viewport);
    }

    void Camera::populateDrawContext(DrawContext& drawContext)
    {
        if (mViewports.size() == 0) return;

        this->buildViewMatrix();

        drawContext.setCamera(this);

        auto& root = mScene.getRootNode();
        populateDrawContext(drawContext, root);
    }

    void Camera::populateDrawContext(DrawContext& drawContext, SceneNode& node)
    {
        auto& nodes = drawContext.getSceneNodes();
        auto visible = isVisible(node);
        if (visible)
        {
            nodes.push_back(&node);

            auto& children = node.getChildren();
            for (auto&& child : children)
            {
                auto& childAsSceneNode = static_cast<SceneNode&>(*child.get());
                populateDrawContext(drawContext, childAsSceneNode);
            }
        }
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
