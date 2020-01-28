#ifndef TOV_RENDER_SYSTEM_COLOUR_H
#define TOV_RENDER_SYSTEM_COLOUR_H

#include <tov/core.h>

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

	public:
		float r, g, b, a;

	public:
		constexpr static Colour Black	= Colour(0.0f, 0.0f, 0.0f, 1.0f);
		constexpr static Colour White	= Colour(1.0f, 1.0f, 1.0f, 1.0f);
		constexpr static Colour Red		= Colour(1.0f, 0.0f, 0.0f, 1.0f);
		constexpr static Colour Green	= Colour(0.0f, 1.0f, 0.0f, 1.0f);
		constexpr static Colour Blue	= Colour(0.0f, 0.0f, 1.0f, 1.0f);
	};

	TOV_NAMESPACE_END // rendering
}

#endif