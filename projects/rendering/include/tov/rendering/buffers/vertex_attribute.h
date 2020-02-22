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
		enum class Semantic
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

		enum class Type
		{
			FLOAT,
			INT,
			UINT,
			SHORT,
			USHORT,
			BYTE,
			UBYTE
		};

		VertexAttribute(Semantic semantic, Type type, ushort count) noexcept;
		~VertexAttribute() noexcept = default;

		size_t getSize() const { return mSize; }

	private:
		static constexpr size_t getTypeSize(Type type);

	private:
		const Semantic mSemantic;
		const Type mType;
		const ushort mCount;
		const size_t mSize;

	public:
		static const VertexAttribute POSITION;
		static const VertexAttribute NORMAL;
		static const VertexAttribute COLOUR;
		static const VertexAttribute TEXTURE_COORDINATE;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif