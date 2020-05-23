#include <rendering/geometry/cuboid.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(geometry)

	Cuboid::Cuboid(float width, float height, float depth) noexcept
		: Geometry()
		, mWidth(width)
		, mHeight(height)
		, mDepth(depth)
	{
		this->generateVertices();
		this->generateIndicies();
	}

	void Cuboid::generateVertices()
	{
		// Scale position by width, height, and depth
		auto const positionScale = math::Vector3(mWidth, mHeight, mDepth);
		auto const UNIT = 0.5f;

		// Convert texture to normalized UV coordinates between [0, 1]
		auto const textureScale = math::Vector2(mDepth * 2 + mWidth * 2, mDepth * 2 + mHeight).reciprocal();

		auto p0 = math::Vector3(-UNIT, +UNIT, +UNIT) * positionScale;
		auto t0 = math::Vector2(mDepth, mDepth + mHeight) * textureScale;

		auto p1 = math::Vector3(-UNIT, -UNIT, +UNIT) * positionScale;
		auto t1 = math::Vector2(mDepth, mDepth) * textureScale;

		auto p2 = math::Vector3(+UNIT, +UNIT, +UNIT) * positionScale;
		auto t2 = math::Vector2(mDepth + mWidth, mDepth + mHeight) * textureScale;

		auto p3 = math::Vector3(+UNIT, -UNIT, +UNIT) * positionScale;
		auto t3 = math::Vector2(mDepth + mWidth, mDepth) * textureScale;

		auto p4 = p2;
		auto t4 = t2;
		
		auto p5 = p3;
		auto t5 = t3;

		auto p6 = math::Vector3(+UNIT, +UNIT, -UNIT) * positionScale;
		auto t6 = math::Vector2(mDepth * 2 + mWidth, mDepth + mHeight) * textureScale;

		auto p7 = math::Vector3(+UNIT, -UNIT, -UNIT) * positionScale;
		auto t7 = math::Vector2(mDepth * 2 + mWidth, mDepth) * textureScale;

		auto p8 = p6;
		auto t8 = t6;

		auto p9 = p7;
		auto t9 = t7;

		auto p10 = math::Vector3(-UNIT, +UNIT, -UNIT) * positionScale;
		auto t10 = math::Vector2(mDepth * 2 + mWidth * 2, mDepth + mHeight) * textureScale;

		auto p11 = math::Vector3(-UNIT, -UNIT, -UNIT) * positionScale;
		auto t11 = math::Vector2(mDepth * 2 + mWidth * 2, mDepth) * textureScale;

		auto p12 = p10;
		auto t12 = math::Vector2(0, mDepth + mHeight) * textureScale;

		auto p13 = p11;
		auto t13 = math::Vector2(0, mDepth) * textureScale;

		auto p14 = p0;
		auto t14 = t0;

		auto p15 = p1;
		auto t15 = t1;

		auto p16 = p10;
		auto t16 = math::Vector2(mDepth, mDepth * 2 + mHeight) * textureScale;

		auto p17 = p0;
		auto t17 = t0;

		auto p18 = p6;
		auto t18 = math::Vector2(mDepth + mWidth, mDepth * 2 + mHeight) * textureScale;

		auto p19 = p2;
		auto t19 = t2;

		auto p20 = p1;
		auto t20 = t1;

		auto p21 = p11;
		auto t21 = math::Vector2(mDepth, 0) * textureScale;

		auto p22 = p3;
		auto t22 = t3;

		auto p23 = p7;
		auto t23 = math::Vector2(mDepth + mWidth, 0) * textureScale;

		this->addPosition(p0);
		this->addPosition(p1);
		this->addPosition(p2);
		this->addPosition(p3);
		this->addPosition(p4);
		this->addPosition(p5);
		this->addPosition(p6);
		this->addPosition(p7);
		this->addPosition(p8);
		this->addPosition(p9);
		this->addPosition(p10);
		this->addPosition(p11);
		this->addPosition(p12);
		this->addPosition(p13);
		this->addPosition(p14);
		this->addPosition(p15);
		this->addPosition(p16);
		this->addPosition(p17);
		this->addPosition(p18);
		this->addPosition(p19);
		this->addPosition(p20);
		this->addPosition(p21);
		this->addPosition(p22);
		this->addPosition(p23);

		this->addTextureCoordinate(t0);
		this->addTextureCoordinate(t1);
		this->addTextureCoordinate(t2);
		this->addTextureCoordinate(t3);
		this->addTextureCoordinate(t4);
		this->addTextureCoordinate(t5);
		this->addTextureCoordinate(t6);
		this->addTextureCoordinate(t7);
		this->addTextureCoordinate(t8);
		this->addTextureCoordinate(t9);
		this->addTextureCoordinate(t10);
		this->addTextureCoordinate(t11);
		this->addTextureCoordinate(t12);
		this->addTextureCoordinate(t13);
		this->addTextureCoordinate(t14);
		this->addTextureCoordinate(t15);
		this->addTextureCoordinate(t16);
		this->addTextureCoordinate(t17);
		this->addTextureCoordinate(t18);
		this->addTextureCoordinate(t19);
		this->addTextureCoordinate(t20);
		this->addTextureCoordinate(t21);
		this->addTextureCoordinate(t22);
		this->addTextureCoordinate(t23);
	}

	void Cuboid::generateIndicies()
	{
		this->addIndices(0, 1, 2);
		this->addIndices(2, 1, 3);
		this->addIndices(4, 5, 6);
		this->addIndices(6, 5, 7);
		this->addIndices(8, 9, 10);
		this->addIndices(10, 9, 11);
		this->addIndices(12, 13, 14);
		this->addIndices(14, 13, 15);
		this->addIndices(16, 17, 18);
		this->addIndices(18, 17, 19);
		this->addIndices(20, 21, 22);
		this->addIndices(22, 21, 23);
	}

	TOV_NAMESPACE_END // geometry
	TOV_NAMESPACE_END // rendering
}
