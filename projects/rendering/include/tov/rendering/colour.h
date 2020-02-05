#ifndef TOV_RENDERING_COLOUR_H
#define TOV_RENDERING_COLOUR_H

#include <tov/core.h>

#ifdef TOV_DEBUG
#include <ostream>
#endif

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Colour
	{
	public:
		explicit Colour(
			float red = 1.0f,
			float green = 1.0f,
			float blue = 1.0f,
			float alpha = 1.0f
		) noexcept
			: r(red)
			, g(green)
			, b(blue)
			, a(alpha)
		{}
		~Colour() noexcept = default;

#ifdef TOV_DEBUG
		inline friend std::ostream& operator <<
			(std::ostream& o, const Colour& colour)
		{
			o << "Colour( ";
			o << "R: " << colour.r << ", ";
			o << "G: " << colour.g << ", ";
			o << "B: " << colour.b << ", ";
			o << "A: " << colour.a;
			o << " )";
			return o;
		}
#endif

	public:
		float r, g, b, a;

	public:
		static const Colour Black;
		static const Colour White;
		static const Colour Red;
		static const Colour Green;
		static const Colour Blue;
	};

	TOV_NAMESPACE_END // rendering
}

#endif