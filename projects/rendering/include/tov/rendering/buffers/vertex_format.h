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
    private:
        using VertexAttributeList = std::vector<VertexAttribute>;

    public:
        void addAttribute(VertexAttribute attribute);
        auto getSize() const { return mSize; }

        auto getAttributes() const -> auto const & { return mAttributes; }

    private:

        // TODO:
        // The list of attributes should be unique for each semantic.
        // A semantic should not exist more than once in this list.
        VertexAttributeList mAttributes;
        size_t mSize = 0;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
