#ifndef TOV_RENDERING_COMPONENT_H
#define TOV_RENDERING_COMPONENT_H

#include "rendering_core.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class Component
	{
		TOV_MOVABLE_ONLY(Component)

	public:
		Component() = default;
		virtual ~Component() = default;
	};

	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_COMPONENT_H
