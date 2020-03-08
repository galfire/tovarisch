#ifndef TOV_RENDERING_MESH_VERTEX_DATA_FORMAT_H
#define TOV_RENDERING_MESH_VERTEX_DATA_FORMAT_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/vertex_attribute.h>
#include <tov/rendering/buffers/vertex_buffer_format.h>

#include <unordered_map>
#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	class VertexDataFormat
	{
		using VertexAttribute = rendering::buffers::VertexAttribute;
		using VertexBufferFormat = rendering::buffers::VertexBufferFormat;
		using VertexAttributeList = std::vector<VertexAttribute>;

		using VBOHandle = byte;
		using HandleList = std::vector<VBOHandle>;
		using AttributeToHandleMap = std::unordered_map<VertexAttribute, VBOHandle, VertexAttribute::Hash, VertexAttribute::EqualTo>;
		using HandleToFormatMap = std::unordered_map<VBOHandle, VertexBufferFormat>;

	public:
		VertexDataFormat() noexcept {}
		~VertexDataFormat() noexcept {}

		auto getHandles() const -> auto const &
		{
			return mHandles;
		}

		auto getAttributes() const -> auto const &
		{
			return mAttributes;
		}

		auto getHandleForAttribute(VertexAttribute attribute) const
		{
			auto handle = mAttributeToHandleMap.at(attribute);
			return handle;
		}

		auto getVertexBufferFormatForHandle(VBOHandle handle) const
		{
			auto format = mHandleToFormatMap.at(handle);
			return format;
		}

		auto getVertexBufferFormatForAttribute(VertexAttribute attribute) const
		{
			auto handle = getHandleForAttribute(attribute);
			auto format = getVertexBufferFormatForHandle(handle);
			return format;
		}

		void mapHandleToFormat(VBOHandle handle, VertexBufferFormat vbf)
		{
			if (!mHandleToFormatMap.contains(handle))
			{
				mHandles.push_back(handle);
				mHandleToFormatMap[handle] = vbf;
				auto attributes = vbf.getVertexFormat().getAttributes();
				for (auto&& attribute : attributes)
				{
					mAttributeToHandleMap[attribute] = handle;
					mAttributes.push_back(attribute);
				}
			}
		}

	private:
		HandleList mHandles;
		VertexAttributeList mAttributes;
		AttributeToHandleMap mAttributeToHandleMap;
		HandleToFormatMap mHandleToFormatMap;
	};

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif
