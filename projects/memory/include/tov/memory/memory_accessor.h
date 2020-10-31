#ifndef TOV_MEMORY_MEMORY_ACCESSOR_H
#define TOV_MEMORY_MEMORY_ACCESSOR_H

#include <tov/core.h>

#include <cstring>

namespace tov
{
    TOV_NAMESPACE_BEGIN(memory)

    template<class T>
    class MemoryWriter
    {
    public:
        inline void write(void* __restrict buffer, T* __restrict memory) const
        {
            T* start = static_cast<T*>(buffer);
            memcpy(start, memory, sizeof(T));
        }
    };

    template<class T>
    class MemoryReader
    {
    public:
        inline void read(void* __restrict buffer, T& out) const
        {
            out = *static_cast<T*>(buffer);
        }
    };

    template<class T>
    class MemoryAccessor
    {
    public:
        inline void write(void* __restrict buffer, T* __restrict memory) const
        {
            mWriter.write(buffer, memory);
        }

        inline void read(void* __restrict buffer, T& out) const
        {
            mReader.read(buffer, out);
        }

    private:
        MemoryWriter<T> mWriter;
        MemoryReader<T> mReader;
    };

    TOV_NAMESPACE_END // memory
}

#endif
