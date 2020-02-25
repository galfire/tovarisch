#ifndef TOV_RENDERING_MESH_VERTEX_DATA_H
#define TOV_RENDERING_MESH_VERTEX_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/vertex_attribute.h>
#include <tov/rendering/buffers/vertex_buffer_format.h>

#include <unordered_map>
#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	//class BufferObjectBase; 
	
	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_BEGIN(mesh)

	// Container for vertex buffer objects
	// A submesh can be composed of multiple VBOs, where different VBOs contain different vertex attributes.
	// For example, one VBO can contain POSITION data, while another VBO contains NORMAL data.

	class VertexData
	{
		TOV_MOVABLE_ONLY(VertexData)

		/*using VertexAttribute = rendering::buffers::VertexAttribute;
		using BufferObjectBase = rendering::buffers::BufferObjectBase;
		using VertexBufferFormat = rendering::buffers::VertexBufferFormat;

		using AttributeToVBOMap = std::unordered_map<VertexAttribute, BufferObjectBase*>;
		using AttributeToVBOFormatMap = std::unordered_map<VertexAttribute, VertexBufferFormat>;
		using VBOList = std::vector<BufferObjectBase*>;*/

	public:
		VertexData() noexcept = default;
		~VertexData() noexcept = default;

	private:
		/*AttributeToVBOMap mAttributeToVBOMap;
		AttributeToVBOMap mAttributeToVBOFormatMap;
		VBOList mVBOList;*/
	};

	using VertexDataUPtr = std::unique_ptr<VertexData>;

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif
