#ifndef TOV_RENDERING_VIEW_FRUSTUM_H
#define TOV_RENDERING_VIEW_FRUSTUM_H

#include "rendering_core.h"

#include <tov/math/matrix.h>
#include <tov/math/radian.h>

#include "transform.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class ViewFrustumView
	{
	public:
		void buildViewMatrix(const Transform& transform) noexcept;

		auto getViewMatrix() const { return mViewMatrix; }

	private:
		math::Matrix4 mViewMatrix = math::Matrix4::ZERO;
	};

	enum class ProjectionType
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	template<ProjectionType Projection>
	class ViewFrustumProjection
	{
	private:
		struct ProjectionParameters
		{
			float left;
			float right;
			float bottom;
			float top;
		};

	public:
		void setNearDistance(float nearDistance) noexcept { mNearDistance = nearDistance; }
		void setFarDistance(float farDistance) noexcept { mFarDistance = farDistance; }
		void setAspectRatio(float aspectRatio) noexcept { mAspectRatio = aspectRatio; }
		void setFieldOfViewY(math::Radian fovy) noexcept { mFieldOfViewY = fovy; }

		inline void buildProjectionMatrix() noexcept;

		auto getProjectionMatrix() const { return mProjectionMatrix; }

	private:
		inline ProjectionParameters calculateProjectionParameters() noexcept;

	private:
		float mNearDistance = 1.0f;
		float mFarDistance = 3000.0f;
		float mAspectRatio = 4.0f / 3;
		math::Radian mFieldOfViewY = math::Radian(math::PI / 6);
		math::Matrix4 mProjectionMatrix = math::Matrix4::ZERO;
	};

	template<ProjectionType Projection>
	class ViewFrustum
		: public ViewFrustumView
		, public ViewFrustumProjection<Projection>
	{};

	TOV_NAMESPACE_END // rendering
}

#include "view_frustum.inl"

#endif