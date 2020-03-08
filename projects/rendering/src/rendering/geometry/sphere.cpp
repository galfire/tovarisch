#include "rendering/geometry/sphere.h"

#include <tov/math/trigonometry.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(geometry)

	Sphere::Sphere(float radius, uint sectorCount, uint stackCount)
		: Geometry()
	{
		this->set(radius, sectorCount, stackCount);
		this->generateVertices();
		this->generateIndicies();
	}

	void Sphere::set(float radius, uint sectorCount, uint stackCount)
	{
		mRadius = radius;
		mSectorCount = sectorCount;
		mStackCount = stackCount;
	}

	void Sphere::generateVertices()
	{
		float x, y, z, xy;                              // vertex position
		float nx, ny, nz;
		float lengthInv = 1.0f / mRadius;    // normal
		float s, t;                                     // texCoord

		float PI = math::PI;

		float sectorStep = 2.0f * PI / mSectorCount;
		float stackStep = PI / mStackCount;

		for (uint i = 0; i <= mStackCount; ++i)
		{
			math::Radian stackAngle = PI / 2 - i * stackStep; // starting from pi/2 to -pi/2
			xy = mRadius * math::cos(stackAngle);              // r * cos(u)
			z = mRadius * math::sin(stackAngle);               // r * sin(u)

			for (uint j = 0; j <= mSectorCount; ++j)
			{
				math::Radian sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position
				x = xy * math::cos(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * math::sin(sectorAngle);             // r * cos(u) * sin(v)
				math::Vector3 position(x, y, z);
				this->addPosition(position);

				// normalized vertex normal
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				math::Vector3 normal(nx, ny, nz);
				this->addNormal(normal);

				// vertex tex coord between [0, 1]
				s = (float)j / mSectorCount;
				t = (float)i / mStackCount;
				math::Vector2 textureCoordinate(s, t);
				this->addTextureCoordinate(textureCoordinate);
			}
		}
	}

	void Sphere::generateIndicies()
	{
		// indices
	    
		//  k1--k1+1
	    //  |  / |
	    //  | /  |
	    //  k2--k2+1

		uint k1, k2;
		for (uint i = 0; i < mStackCount; ++i)
		{
			k1 = i * (mSectorCount + 1);     // beginning of current stack
			k2 = k1 + mSectorCount + 1;      // beginning of next stack

			for (uint j = 0; j < mSectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding 1st and last stacks
				if (i != 0)
				{
					addIndices(k1, k2, k1 + 1);   // k1---k2---k1+1
				}

				if (i != (mStackCount - 1))
				{
					addIndices(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
				}
			}
		}
	}

	TOV_NAMESPACE_END // geometry
	TOV_NAMESPACE_END // rendering
}