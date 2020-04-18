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
            // The attribute index (TEX1, TEX2, etc.)
            ushort index;
            // The attribute location (the location index in the vertex)
            ushort location;
            // The number of components
            ushort count;
            // The attribute data type
            VertexAttribute::Type type;
            // The distance to the same semantic in the next vertex
            size_t stride;
            // The offset in bytes for this semantic in the vertex
            size_t offset;

#ifdef TOV_DEBUG
            inline friend std::ostream& operator << (std::ostream& o, const AttributeDescriptor& ad)
            {
                o << "Semantic: " << ad.semantic << ", ";
                o << "Index: " << ad.index << ", ";
                o << "Type: " << ad.type << ", ";
                o << "Stride: " << ad.stride << ", ";
                o << "Offset: " << ad.offset;
                return o;
            }
#endif
        };

        struct Descriptor
        {
            std::vector<AttributeDescriptor> attributeDescriptors;

#ifdef TOV_DEBUG
            inline friend std::ostream& operator <<
                (std::ostream& o, const Descriptor& desc)
            {
                for (auto&& ad : desc.attributeDescriptors)
                {
                    o << ad << "\n";
                }
                return o;
            }
#endif
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
