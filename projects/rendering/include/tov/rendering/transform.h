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

		Transform& operator = (const Transform& other);

		bool operator == (const Transform& other) const;
		bool operator != (const Transform& other) const;

		void translate(const math::Vector3& translation);
		void setTranslation(const math::Vector3& translation);
		const math::Vector3& getTranslation() const;
		math::Vector3& getTranslation();

		void rotate(const math::Quaternion& rotation);
		void setRotation(const math::Quaternion& rotation);
		const math::Quaternion& getRotationQuaternion() const;
		math::Quaternion& getRotationQuaternion();

		void scale(const math::Vector3& scale);
		void setScale(const math::Vector3& scale);
		const math::Vector3& getScale() const;
		math::Vector3& getScale();

		math::Matrix3 getRotationMatrix() const;
		math::Matrix3 getScaleMatrix() const;
		math::Matrix4 getHomogeneousMatrix() const;

	private:
		math::Vector3 mTranslation;
		math::Quaternion mRotation;
		math::Vector3 mScale;
	};

	TOV_NAMESPACE_END // rendering
}

#endif
