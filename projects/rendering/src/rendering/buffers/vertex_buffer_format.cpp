#include "rendering/buffers/vertex_buffer_format.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    VertexBufferFormat::VertexBufferFormat(SequenceType sequenceType, VertexFormat vertexFormat)
        : mSequenceType(sequenceType)
        , mVertexFormat(vertexFormat)
    {
        buildDescriptor();
    }

    void VertexBufferFormat::buildDescriptor()
    {
        auto numAttributes = mVertexFormat.getAttributes().size();
        auto vertexSize = mVertexFormat.getSize();
        
        size_t offset = 0;
        auto&& attributes = mVertexFormat.getAttributes();
        for (auto&& attribute : attributes)
        {
            AttributeDescriptor attributeDescriptor;
            attributeDescriptor.semantic = attribute.getSemantic();
            attributeDescriptor.index = attribute.getIndex();
            attributeDescriptor.location = mVertexFormat.getAttributeLocation(attribute);
            attributeDescriptor.count = attribute.getCount();
            attributeDescriptor.type = attribute.getType();
            switch (mSequenceType)
            {
            case SequenceType::INTERLEAVED:
                attributeDescriptor.offset = offset;
                offset += attribute.getSize();
                attributeDescriptor.stride = vertexSize;
                break;
            case SequenceType::SEQUENTIAL:
                attributeDescriptor.offset = offset;
                offset += numAttributes * attribute.getSize();
                attributeDescriptor.stride = 0;
                break;
            default:
                break;
            }
            mDescriptor.attributeDescriptors.push_back(attributeDescriptor);
        }
    }

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}
