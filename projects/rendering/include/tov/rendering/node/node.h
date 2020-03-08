#ifndef TOV_RENDERING_NODE_NODE_H
#define TOV_RENDERING_NODE_NODE_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/transform.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(node)

	class Node
	{
	public:
		Node() = default;
		virtual ~Node() = default;

		auto getTransform() const -> auto const & { return mTransform; }
		auto getTransform() -> auto & { return mTransform; }

		auto getDerivedTransform() { return mTransform; }

	protected:
		Transform mTransform;
	};

	TOV_NAMESPACE_END // node
	TOV_NAMESPACE_END // rendering
};

#endif
