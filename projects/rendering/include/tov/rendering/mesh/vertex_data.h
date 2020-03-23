#ifndef TOV_RENDERING_MESH_VERTEX_DATA_H
#define TOV_RENDERING_MESH_VERTEX_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/usage_settings.h>
#include <tov/rendering/buffers/buffer_object.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>

#include "vertex_data_format.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	// Container for vertex buffer objects
	// A submesh can be composed of multiple VBOs, where different VBOs contain different vertex attributes.
	// For example, one VBO can contain POSITION data, while another VBO contains NORMAL data.
	class VertexData
	{
		TOV_MOVABLE_ONLY(VertexData)

		using AccessSettings = buffers::AccessSettings;
		using UsageSettings = buffers::UsageSettings;
		using VBOHandle = byte;
		using BufferObjectUPtr = buffers::BufferObjectUPtr;
		using HandleToVBOMap = std::unordered_map<VBOHandle, BufferObjectUPtr>;

	public:
		template<class BufferManagerT>
		VertexData(
			BufferManagerT& bufferManager,
			VertexDataFormat format,
			uint numVertices
		) noexcept
			: mFormat(format)
		{
			auto handles = mFormat.getHandles();
			for (auto&& handle : handles)
			{
				auto bufferFormat = mFormat.getVertexBufferFormatForHandle(handle);
				auto buffer = bufferManager.template createVertexBuffer<UsageSettings::STATIC, AccessSettings::WRITE>(bufferFormat, numVertices);
				auto bufferObject = BufferObjectUPtr(
					new tov::rendering::buffers::VertexBufferObject(*buffer, bufferFormat)
				);
				mHandleToVBOMap[handle] = std::move(bufferObject);
			}
		}

		~VertexData() noexcept = default;

		auto getBufferObjectForHandle(VBOHandle handle) const -> auto&
		{
			auto vbo = mHandleToVBOMap.at(handle).get();
			return *static_cast<buffers::VertexBufferObject*>(vbo);
		}

		auto getFormat() const -> auto&
		{
			return mFormat;
		}

	private:
		VertexDataFormat mFormat;
		HandleToVBOMap mHandleToVBOMap;
	};

	using VertexDataUPtr = std::unique_ptr<VertexData>;

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif
