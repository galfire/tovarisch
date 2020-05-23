#ifndef TOV_RENDERING_RECTANGLE_H
#define TOV_RENDERING_RECTANGLE_H

#include "geometry.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(geometry)

	class Rectangle
		: public Geometry
	{
	public:
		Rectangle(float width, float height) noexcept;
		~Rectangle() = default;

	private:
		float mWidth;
		float mHeight;
	};

	TOV_NAMESPACE_END // geometry
	TOV_NAMESPACE_END // rendering
}

#endif
