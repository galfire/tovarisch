#ifndef TOV_RENDERING_VERTEX_BUFFER_FORMAT_H
#define TOV_RENDERING_VERTEX_BUFFER_FORMAT_H

#include <tov/rendering/rendering_core.h>

#include "vertex_format.h"
#include "vertex_attribute.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class VertexBufferFormat
    {
    public:
        enum class SequenceType
        {
            // VNCVNCVNC
            INTERLEAVED,
            // VVVNNNCCC
            SEQUENTIAL
        };

        // How the attribute is used in the context of this buffer
        struct AttributeDescriptor
        {
            // The attribute semantic
            VertexAttribute::Semantic semantic;
            // The attribute index
            ushort index;
            // The attribute data type
            VertexAttribute::Type type;
            // The distance to the same semantic in the next vertex
            size_t stride;
            // The offset in bytes for this semantic in the vertex
            size_t offset;
        };

        struct Descriptor
        {
            std::vector<AttributeDescriptor> attributeDescriptors;
        };

    public:
        VertexBufferFormat(SequenceType sequenceType, VertexFormat vertexFormat);
        ~VertexBufferFormat() = default;

        auto getSequenceType() const { return mSequenceType; }
        auto getVertexFormat() const { return mVertexFormat; }

        auto getDescriptor() const -> Descriptor;

    private:
        SequenceType mSequenceType;

        VertexFormat mVertexFormat;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif