#ifndef TOV_RENDERING_BUFFERS_VERTEX_ATTRIBUTE_H
#define TOV_RENDERING_BUFFERS_VERTEX_ATTRIBUTE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    class VertexAttribute
    {
    public:
        enum class Semantic : byte
        {
            // Position vector, 3 floats
            POSITION,

            // Normal vector, 3 floats 
            NORMAL,

            // Colour value, 4 unsigned bytes
            COLOUR,

            // Texture coordinate vector, 2 floats
            TEXTURE_COORDINATE,
        };

#if TOV_DEBUG
        inline friend std::ostream& operator << (std::ostream& o, const Semantic& semantic)
        {
            switch (semantic)
            {
            case Semantic::POSITION:            o << "POSITION"; break;
            case Semantic::NORMAL:              o << "NORMAL"; break;
            case Semantic::COLOUR:              o << "COLOUR"; break;
            case Semantic::TEXTURE_COORDINATE:  o << "TEXTURE COORDINATE"; break;
            default:                            o << "UNKNOWN (" << (byte)semantic << ")"; break;
            }
            return o;
        }
#endif

        enum class Type : byte
        {
            FLOAT,
            INT,
            UINT,
            SHORT,
            USHORT,
            BYTE,
            UBYTE
        };

#if TOV_DEBUG
        inline friend std::ostream& operator << (std::ostream& o, const Type& type)
        {
            switch (type)
            {
            case Type::FLOAT:   o << "FLOAT"; break;
            case Type::INT:     o << "INT"; break;
            case Type::UINT:    o << "UINT"; break;
            case Type::SHORT:   o << "SHORT"; break;
            case Type::USHORT:  o << "USHORT"; break;
            case Type::BYTE:    o << "BYTE"; break;
            case Type::UBYTE:   o << "UBYTE"; break;
            default:            o << "UNKNOWN (" << (byte)type << ")"; break;
            }
            return o;
        }
#endif

    private:
        static constexpr auto getTypeSize(Type type)
        {
            switch (type)
            {
            case Type::FLOAT:
                return sizeof(float);
            case Type::INT:
                return sizeof(int);
            case Type::UINT:
                return sizeof(unsigned int);
            case Type::SHORT:
                return sizeof(short);
            case Type::USHORT:
                return sizeof(unsigned short);
            case Type::BYTE:
                return sizeof(byte);
            case Type::UBYTE:
                return sizeof(byte);
            default:
                return static_cast<size_t>(0u);
            }
        }

    public:
        constexpr VertexAttribute(Semantic semantic, Type type, ushort count, ushort index) noexcept;
        ~VertexAttribute() noexcept = default;

        auto operator = (const VertexAttribute& rhs) -> auto &
        {
            mSemantic = rhs.mSemantic;
            mType = rhs.mType;
            mCount = rhs.mCount;
            return *this;
        }

        auto getSemantic() const { return mSemantic; }
        auto getType() const { return mType; }
        auto getCount() const { return mCount; }
        auto getSize() const { return getTypeSize(mType) * mCount; }
        auto getIndex() const { return mIndex; }

    private:
        Semantic mSemantic;
        Type mType;
        ushort mCount;
        ushort mIndex;

    public:
        static const VertexAttribute POSITION;
        static const VertexAttribute NORMAL;
        static const VertexAttribute COLOUR;
        static const VertexAttribute TEXTURE_COORDINATE;

    public:
        struct Hash
        {
            auto operator () (const VertexAttribute& vertexAttribute) const
            {
                size_t hash = 0;
                hash |= static_cast<size_t>(vertexAttribute.getSemantic()) << (0);
                hash |= static_cast<size_t>(vertexAttribute.getType())     << (0 + 8 * sizeof(VertexAttribute::Semantic));
                hash |= static_cast<size_t>(vertexAttribute.getCount())    << (0 + 8 * sizeof(VertexAttribute::Semantic) + 8 * sizeof(VertexAttribute::Type));
                return hash;
            }
        };

        struct EqualTo
        {
            auto operator () (const VertexAttribute& lhs, const VertexAttribute& rhs) const
            {
                return
                    lhs.getSemantic() == rhs.getSemantic() &&
                    lhs.getType() == rhs.getType() &&
                    lhs.getCount() == rhs.getCount();
            }
        };
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
