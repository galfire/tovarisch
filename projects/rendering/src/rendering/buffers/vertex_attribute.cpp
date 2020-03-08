#include "rendering/buffers/vertex_attribute.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	const VertexAttribute VertexAttribute::POSITION(Semantic::POSITION, Type::FLOAT, 3);
	const VertexAttribute VertexAttribute::NORMAL(Semantic::NORMAL, Type::FLOAT, 3);
	const VertexAttribute VertexAttribute::COLOUR(Semantic::COLOUR, Type::UBYTE, 4);
	const VertexAttribute VertexAttribute::TEXTURE_COORDINATE(Semantic::TEXTURE_COORDINATE, Type::FLOAT, 2);

	VertexAttribute::VertexAttribute(Semantic semantic, Type type, ushort count) noexcept
		: mSemantic(semantic)
		, mType(type)
		, mCount(count)
	{}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}