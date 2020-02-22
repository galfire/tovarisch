#ifndef TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H
#define TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H

#include <tov/rendering/rendering_core.h>

#include "buffer_object.h"

#include <tov/memory.h>
#include <tov/memory/memory_arena.h>
#include <tov/memory/policies/alignment/standard.h>
#include <tov/memory/policies/allocation/new_delete.h>
#include <tov/memory/policies/bounds/none.h>
#include <tov/memory/policies/thread/single.h>

#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	class BufferObjectManager
	{
		TOV_MOVABLE_ONLY(BufferObjectManager)

	public:
		BufferObjectManager() noexcept;;
		virtual ~BufferObjectManager() noexcept = default;

		void* allocateScratch(size_t size);
		void deallocateScratch(void* ptr);

		template<class BufferObjectT, class... U>
		BufferObjectT* create(U&&... args)
		{
			auto bufferObject = BufferObjectUPtr(
				new BufferObjectT(*this, std::forward<U>(args)...)
			);
			mBufferObjects.push_back(std::move(bufferObject));
			auto ret = mBufferObjects.back().get();
			return static_cast<BufferObjectT*>(ret);
		}

	private:
		using BufferObjectList = std::vector<BufferObjectUPtr>;
		BufferObjectList mBufferObjects;

		using MemoryArena = memory::MemoryArena<
			tov::memory::policies::allocation::NewDelete,
			tov::memory::policies::alignment::Standard,
			tov::memory::policies::thread::Single,
			tov::memory::policies::bounds::None
		>;

		MemoryArena mMemoryArena;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif