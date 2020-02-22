#ifndef TOV_RENDERING_BUFFERS_VERTEX_FORMAT_H
#define TOV_RENDERING_BUFFERS_VERTEX_FORMAT_H

#include <tov/rendering/rendering_core.h>

#include "vertex_attribute.h"

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	class VertexFormat
	{
	public:
		void addAttribute(VertexAttribute attribute);
		size_t getSize() const { return mSize; }

	private:
		using VertexAttributeList = std::vector<VertexAttribute>;

		// TODO: 
		// The list of attributes should be unique for each semantic.
		// A semantic should not exist more than once in this list.
		VertexAttributeList mAttributes;
		size_t mSize;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
