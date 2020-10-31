#include "rendering/view_frustum.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    void ViewFrustumView::buildViewMatrix(Transform& transform) noexcept
    {
        mViewMatrix = transform.getHomogeneousMatrix();
    }

    TOV_NAMESPACE_END // rendering
}
