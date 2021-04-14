#ifndef TOV_RENDERING_BUFFERS_VERTEX_FORMAT_H
#define TOV_RENDERING_BUFFERS_VERTEX_FORMAT_H

#include <tov/rendering/rendering_core.h>

#include "vertex_attribute.h"

#include <unordered_map>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class VertexFormat
    {
    private:
        using VertexAttributeToLocationMap = std::unordered_map<VertexAttribute, ushort, VertexAttribute::Hash, VertexAttribute::EqualTo>;

    public:
        void addAttribute(VertexAttribute attribute, ushort location);

        // The size of the vertex in bytes
        auto getSize() const { return mSize; }

        auto getAttributes() const { return std::span{ mAttributes }; }

        auto getAttributeLocation(VertexAttribute attribute) const { return mAttributeToLocationMap.at(attribute); }

    private:
        std::vector<VertexAttribute> mAttributes;
        VertexAttributeToLocationMap mAttributeToLocationMap;
        size_t mSize = 0;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
