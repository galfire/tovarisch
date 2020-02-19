#include "rendering/transform.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	Transform::Transform() noexcept
		: mTranslation(math::Vector3::ZERO)
		, mRotation(math::Quaternion::IDENTITY)
		, mScale(math::Vector3::UNIT_SCALE)
	{}

	Transform::Transform(
		const math::Vector3& translation,
		const math::Quaternion& rotation,
		const math::Vector3& scale
	) noexcept
		: mTranslation(translation)
		, mRotation(rotation)
		, mScale(scale)
	{}

	Transform& Transform::operator = (const Transform& other)
	{
		mTranslation = other.mTranslation;
		mRotation = other.mRotation;
		mScale = other.mScale;
		return *this;
	}

	bool Transform::operator == (const Transform& other) const
	{
		return
			mTranslation == other.mTranslation &&
			mRotation == other.mRotation &&
			mScale == other.mScale;
	}

	bool Transform::operator != (const Transform& other) const
	{
		return !(*this == other);
	}

	void Transform::translate(const math::Vector3& translation)
	{
		mTranslation += translation;
	}

	void Transform::setTranslation(const math::Vector3& translation)
	{
		mTranslation = translation;
	}

	const math::Vector3& Transform::getTranslation() const
	{
		return mTranslation;
	}

	math::Vector3& Transform::getTranslation()
	{
		return mTranslation;
	}

	void Transform::rotate(const math::Quaternion& rotation)
	{
		mRotation *= rotation;
	}

	void Transform::setRotation(const math::Quaternion& rotation)
	{
		mRotation = rotation;
	}

	const math::Quaternion& Transform::getRotationQuaternion() const
	{
		return mRotation;
	}

	math::Quaternion& Transform::getRotationQuaternion()
	{
		return mRotation;
	}

	void Transform::scale(const math::Vector3& scale)
	{
		mScale *= scale;
	}

	void Transform::setScale(const math::Vector3& scale)
	{
		mScale = scale;
	}

	const math::Vector3& Transform::getScale() const
	{
		return mScale;
	}

	math::Vector3& Transform::getScale()
	{
		return mScale;
	}

	math::Matrix3 Transform::getRotationMatrix() const
	{
		return mRotation.toRotationMatrix();
	}

	math::Matrix3 Transform::getScaleMatrix() const
	{
		math::Matrix3 s = math::Matrix3::IDENTITY;
		s[0][0] = mScale.x;
		s[1][1] = mScale.y;
		s[2][2] = mScale.z;

		return s;
	}

	math::Matrix4 Transform::getHomogeneousMatrix() const
	{
		math::Matrix4 m = math::Matrix4::IDENTITY;

		// Set translation
		m[0][3] = mTranslation.x;
		m[1][3] = mTranslation.x;
		m[2][3] = mTranslation.x;

		math::Matrix3 scaleRotationMatrix = getRotationMatrix();
		
		if (mScale != math::Vector3::UNIT_SCALE)
		{
			math::Matrix3 scaleMatrix = getScaleMatrix();
			scaleRotationMatrix *= scaleMatrix;
		}

		memcpy(&m[0], &scaleRotationMatrix[0], 3 * sizeof(float));
		memcpy(&m[1], &scaleRotationMatrix[1], 3 * sizeof(float));
		memcpy(&m[2], &scaleRotationMatrix[2], 3 * sizeof(float));

		return m;
	}

	TOV_NAMESPACE_END
}
