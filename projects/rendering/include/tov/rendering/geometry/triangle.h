#ifndef TOV_RENDERING_GEOMETRY_TRIANGLE_H
#define TOV_RENDERING_GEOMETRY_TRIANGLE_H

#include "geometry.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(geometry)

	class Triangle
		: public Geometry
	{
	public:
		Triangle();
		~Triangle() = default;

	private:
		void generateVertices() override;
		void generateIndicies() override;
	};

	TOV_NAMESPACE_END // geometry
	TOV_NAMESPACE_END // rendering
}

#endif
