#ifndef TOV_RENDERING_GEOMETRY_CUBOID_H
#define TOV_RENDERING_GEOMETRY_CUBOID_H

#include "geometry.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(geometry)

	class Cuboid
		: public Geometry
	{
	public:
		Cuboid(float width, float height, float depth) noexcept;
		virtual ~Cuboid() = default;

	private:
		void generateVertices();
		void generateIndicies();

	private:
		float mWidth;
		float mHeight;
		float mDepth;
	};

	TOV_NAMESPACE_END // geometry
	TOV_NAMESPACE_END // rendering
}

#endif
