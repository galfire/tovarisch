#ifndef TOV_RENDERING_TRANSFORM_H
#define TOV_RENDERING_TRANSFORM_H

#include "rendering_core.h"

#include <tov/math/quaternion.h>
#include <tov/math/vector.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Transform
	{
	public:
		Transform() noexcept;
		Transform(
			const math::Vector3& translation,
			const math::Quaternion& rotation,
			const math::Vector3& scale
		) noexcept;

		auto operator = (const Transform& other) -> Transform&;

		auto operator == (const Transform& other) const -> bool;
		auto operator != (const Transform& other) const -> bool;

		void translate(const math::Vector3& translation);
		void setTranslation(const math::Vector3& translation);
		auto getTranslation() const -> const math::Vector3&;
		auto getTranslation() -> math::Vector3&;

		void rotate(const math::Quaternion& rotation);
		void setRotation(const math::Quaternion& rotation);
		auto getRotationQuaternion() const -> const math::Quaternion&;
		auto getRotationQuaternion() -> math::Quaternion&;

		void scale(const math::Vector3& scale);
		void setScale(const math::Vector3& scale);
		auto getScale() const -> const math::Vector3&;
		auto getScale() -> math::Vector3&;

		auto getRotationMatrix() const -> math::Matrix3;
		auto getScaleMatrix() const -> math::Matrix3;
		auto getHomogeneousMatrix() const -> math::Matrix4;

	private:
		math::Vector3 mTranslation;
		math::Quaternion mRotation;
		math::Vector3 mScale;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
