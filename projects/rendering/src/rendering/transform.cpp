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

	auto Transform::operator = (const Transform& other) -> Transform&
	{
		mTranslation = other.mTranslation;
		mRotation = other.mRotation;
		mScale = other.mScale;
		return *this;
	}

	auto Transform::operator == (const Transform& other) const -> bool
	{
		return
			mTranslation == other.mTranslation &&
			mRotation == other.mRotation &&
			mScale == other.mScale;
	}

	auto Transform::operator != (const Transform& other) const -> bool
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

	auto Transform::getTranslation() const -> const math::Vector3&
	{
		return mTranslation;
	}

	auto Transform::getTranslation() -> math::Vector3&
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

	auto Transform::getRotationQuaternion() const -> const math::Quaternion&
	{
		return mRotation;
	}

	auto Transform::getRotationQuaternion() -> math::Quaternion&
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

	auto Transform::getScale() const -> const math::Vector3&
	{
		return mScale;
	}

	auto Transform::getScale() -> math::Vector3&
	{
		return mScale;
	}

	auto Transform::getRotationMatrix() const -> math::Matrix3
	{
		return mRotation.toRotationMatrix();
	}

	auto Transform::getScaleMatrix() const -> math::Matrix3
	{
		auto s = math::Matrix3::IDENTITY;
		s[0][0] = mScale.x;
		s[1][1] = mScale.y;
		s[2][2] = mScale.z;

		return s;
	}

	auto Transform::getHomogeneousMatrix() const -> math::Matrix4
	{
		auto m = math::Matrix4::IDENTITY;

		// Set translation
		m[0][3] = mTranslation.x;
		m[1][3] = mTranslation.y;
		m[2][3] = mTranslation.z;

		auto scaleRotationMatrix = getRotationMatrix();
		
		if (mScale != math::Vector3::UNIT_SCALE)
		{
			auto scaleMatrix = getScaleMatrix();
			scaleRotationMatrix *= scaleMatrix;
		}

		memcpy(&m[0], &scaleRotationMatrix[0], 3 * sizeof(float));
		memcpy(&m[1], &scaleRotationMatrix[1], 3 * sizeof(float));
		memcpy(&m[2], &scaleRotationMatrix[2], 3 * sizeof(float));

		return m;
	}

	TOV_NAMESPACE_END
}
