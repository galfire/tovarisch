#ifndef TOV_RENDERING_MESH_INDEX_DATA_H
#define TOV_RENDERING_MESH_INDEX_DATA_H

#include <tov/rendering/rendering_core.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/usage_settings.h>
#include <tov/rendering/buffers/buffer_object.h>
#include <tov/rendering/buffers/index_buffer_object.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	class IndexData
	{
		TOV_MOVABLE_ONLY(IndexData)

		using AccessSettings = tov::rendering::buffers::AccessSettings;
		using UsageSettings = tov::rendering::buffers::UsageSettings;
		using BufferObjectUPtr = rendering::buffers::BufferObjectUPtr;

	public:
		template<class BufferManagerT>
		IndexData(
			BufferManagerT& bufferManager,
			uint numIndices
		) noexcept
		{
			auto buffer = bufferManager.createIndexBuffer<UsageSettings::STATIC, AccessSettings::WRITE>(numIndices);
			auto bufferObject = BufferObjectUPtr(
				new tov::rendering::buffers::IndexBufferObject(*buffer)
			);
			mIndexBufferObject = std::move(bufferObject);
		}

		~IndexData() noexcept = default;

		auto getBufferObject() const -> auto&
		{
			auto ibo = mIndexBufferObject.get();
			return *static_cast<tov::rendering::buffers::IndexBufferObject*>(ibo);
		}

	private:
		BufferObjectUPtr mIndexBufferObject;
	};

	using IndexDataUPtr = std::unique_ptr<IndexData>;

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif
