#ifndef TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H
#define TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H

#include <tov/rendering/rendering_core.h>

#include "access_settings.h"
#include "buffer.h"
#include "index_type.h"
#include "usage_settings.h"
#include "vertex_buffer_format.h"

#include <tov/memory.h>
#include <tov/memory/memory_arena.h>
#include <tov/memory/policies/alignment/standard.h>
#include <tov/memory/policies/allocation/new_delete.h>
#include <tov/memory/policies/bounds/simple.h>
#include <tov/memory/policies/thread/single.h>

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferBase;

	class BufferManagerBase
	{
		TOV_MOVABLE_ONLY(BufferManagerBase)

	public:
		BufferManagerBase() noexcept;
		virtual ~BufferManagerBase() noexcept = default;

		auto allocateScratch(size_t size) -> void*;
		void deallocateScratch(void* ptr);
		void checkBounds(void* ptr) const;

	private:
		using MemoryArena = memory::MemoryArena<
			tov::memory::policies::allocation::NewDelete,
			tov::memory::policies::alignment::Standard,
			tov::memory::policies::thread::Single,
			tov::memory::policies::bounds::Simple
		>;

		MemoryArena mMemoryArena;
	};

	template<class DerivedBufferManagerT>
	class BufferManager
		: public BufferManagerBase
	{
	public:
		BufferManager() noexcept = default;
		virtual ~BufferManager() noexcept = default;

		template<class BufferT, class... U>
		auto create(size_t size, U&&... args)
		{
			auto buffer = BufferUPtr(
				new BufferT(*this, size, std::forward<U>(args)...)
			);
			mBuffers.push_back(std::move(buffer));
			auto ret = mBuffers.back().get();
			return static_cast<BufferT*>(ret);
		}

		template<UsageSettings usageSettings, AccessSettings accessSettings>
		auto createVertexBuffer(VertexBufferFormat format, uint numVertices)
		{
			auto vertexFormat = format.getVertexFormat();
			auto vertexSize = vertexFormat.getSize();
			size_t size = vertexSize * numVertices;
			auto buffer = static_cast<DerivedBufferManagerT*>(this)->template createVertexBufferImpl<usageSettings, accessSettings>(size);
			return buffer;
		}

		template<UsageSettings usageSettings, AccessSettings accessSettings>
		auto createIndexBuffer(uint numIndices)
		{
			auto indexType = getIndexType(numIndices);
			auto indexSize = getIndexTypeSize(indexType);
			auto size = indexSize * numIndices;
			auto buffer = static_cast<DerivedBufferManagerT*>(this)->template createIndexBufferImpl<usageSettings, accessSettings>(size);
			return buffer;
		}

	private:
		using BufferList = std::vector<BufferUPtr>;
		BufferList mBuffers;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
