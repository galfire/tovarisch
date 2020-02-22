#include "rendering/buffers/vertex_attribute.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	const VertexAttribute VertexAttribute::POSITION(Semantic::POSITION, Type::FLOAT, 3);
	const VertexAttribute VertexAttribute::NORMAL(Semantic::NORMAL, Type::FLOAT, 3);
	const VertexAttribute VertexAttribute::COLOUR(Semantic::NORMAL, Type::UBYTE, 4);
	const VertexAttribute VertexAttribute::TEXTURE_COORDINATE(Semantic::TEXTURE_COORDINATE, Type::FLOAT, 2);

	constexpr size_t VertexAttribute::getTypeSize(Type type)
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
			return 0;
		}
	}

	VertexAttribute::VertexAttribute(Semantic semantic, Type type, ushort count) noexcept
		: mSemantic(semantic)
		, mType(type)
		, mCount(count)
		, mSize(getTypeSize(type) * count)
	{
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}