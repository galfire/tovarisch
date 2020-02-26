#ifndef TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H
#define TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H

#include <tov/rendering/rendering_core.h>

#include "buffer.h"
#include "index_type.h"
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

	class BufferManager
	{
		TOV_MOVABLE_ONLY(BufferManager)

	public:
		BufferManager() noexcept;;
		virtual ~BufferManager() noexcept = default;

		void* allocateScratch(size_t size);
		void deallocateScratch(void* ptr);
		void checkBounds(void* ptr) const;

		template<class BufferT, class... U>
		BufferT* create(size_t size, U&&... args)
		{
			auto buffer = BufferUPtr(
				new BufferT(*this, size, std::forward<U>(args)...)
			);
			mBuffers.push_back(std::move(buffer));
			auto ret = mBuffers.back().get();
			return static_cast<BufferT*>(ret);
		}

	private:
		using BufferList = std::vector<BufferUPtr>;
		BufferList mBuffers;

		using MemoryArena = memory::MemoryArena<
			tov::memory::policies::allocation::NewDelete,
			tov::memory::policies::alignment::Standard,
			tov::memory::policies::thread::Single,
			tov::memory::policies::bounds::Simple
		>;

		MemoryArena mMemoryArena;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
