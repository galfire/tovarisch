#include "rendering/buffers/vertex_attribute.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	const VertexAttribute VertexAttribute::POSITION(Semantic::POSITION, Type::FLOAT, 3, 0);
	const VertexAttribute VertexAttribute::NORMAL(Semantic::NORMAL, Type::FLOAT, 3, 0);
	const VertexAttribute VertexAttribute::COLOUR(Semantic::COLOUR, Type::UBYTE, 4, 0);
	const VertexAttribute VertexAttribute::TEXTURE_COORDINATE(Semantic::TEXTURE_COORDINATE, Type::FLOAT, 2, 0);

	constexpr VertexAttribute::VertexAttribute(Semantic semantic, Type type, ushort count, ushort index) noexcept
		: mSemantic(semantic)
		, mType(type)
		, mCount(count)
		, mIndex(index)
	{}

	constexpr VertexAttribute va(VertexAttribute::Semantic::POSITION, VertexAttribute::Type::FLOAT, 3, 0);

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}