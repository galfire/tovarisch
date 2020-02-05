#include "rendering/colour.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	const Colour Colour::Black = Colour(0.0f, 0.0f, 0.0f, 1.0f);
	const Colour Colour::White = Colour(1.0f, 1.0f, 1.0f, 1.0f);
	const Colour Colour::Red = Colour(1.0f, 0.0f, 0.0f, 1.0f);
	const Colour Colour::Green = Colour(0.0f, 1.0f, 0.0f, 1.0f);
	const Colour Colour::Blue = Colour(0.0f, 0.0f, 1.0f, 1.0f);

	TOV_NAMESPACE_END // rendering
}