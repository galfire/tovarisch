#ifndef TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H
#define TOV_RENDERING_BUFFERS_BUFFER_OBJECT_MANAGER_H

#include <tov/rendering/rendering_core.h>

#include "access_settings.h"
#include "buffer.h"
#include "index_type.h"
#include "usage_settings.h"
#include "vertex_buffer_format.h"

#include <tov/memory.h>
#include <tov/memory_config.h>

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

        virtual BufferBase* createIndexBuffer(uint numIndices) TOV_ABSTRACT;
        virtual BufferBase* createVertexBuffer(VertexBufferFormat format, uint numVertices) TOV_ABSTRACT;

    private:
        memory::ArenaNewDelete mMemoryArena;
    };

    template<class DerivedBufferManagerT>
    class BufferManager
        : public BufferManagerBase
    {
    public:
        BufferManager() noexcept = default;
        virtual ~BufferManager() noexcept = default;

        BufferBase* createVertexBuffer(VertexBufferFormat format, uint numVertices) override
        {
            auto vertexFormat = format.getVertexFormat();
            auto vertexSize = vertexFormat.getSize();
            auto size = vertexSize * numVertices;
            auto buffer = static_cast<DerivedBufferManagerT*>(this)->createVertexBufferImpl(size);
            return buffer;
        }

        BufferBase* createIndexBuffer(uint numIndices) override
        {
            auto indexType = getIndexType(numIndices);
            auto indexSize = getIndexTypeSize(indexType);
            auto size = indexSize * numIndices;
            auto buffer = static_cast<DerivedBufferManagerT*>(this)->createIndexBufferImpl(size);
            return buffer;
        }

    protected:
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

    private:
        using BufferList = std::vector<BufferUPtr>;
        BufferList mBuffers;
    };

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}

#endif
