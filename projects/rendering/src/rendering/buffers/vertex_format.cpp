#include "rendering/buffers/vertex_format.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    void VertexFormat::addAttribute(VertexAttribute attribute, ushort location)
    {
        mAttributes.push_back(attribute);
        mAttributeToLocationMap[attribute] = location;
        mSize += attribute.getSize();
    }

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}
