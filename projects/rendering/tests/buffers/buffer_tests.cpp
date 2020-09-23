#include "../test_helper.h"
#include "buffer_test_helper.h"

#include <tov/rendering/buffers/buffer.h>
#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/buffer_copier.h>
#include <tov/rendering/buffers/buffer_manager.h>
#include <tov/rendering/buffers/usage_settings.h>

using tov::rendering::buffers::AccessSettings;
using tov::rendering::buffers::BufferCopier;
using tov::rendering::buffers::LockSettings;
using tov::rendering::buffers::UsageSettings;

template<UsageSettings usageSettings, AccessSettings accessSettings>
class DummyBuffer
    : public tov::rendering::buffers::Buffer<BufferCopier, BufferCopier, usageSettings, accessSettings>
{
public:
    DummyBuffer(
        tov::rendering::buffers::BufferManagerBase& manager,
        size_t bytes,
        void* buffer
    )
        : tov::rendering::buffers::Buffer<BufferCopier, BufferCopier, usageSettings, accessSettings>(manager, bytes)
        , mTestBuffer(buffer)
    {}

    void map() override
    {
        this->mBuffer = mTestBuffer;
    }

    void unmap() override
    {
        this->mBuffer = nullptr;
    }

private:
    void* mTestBuffer;
};

class DummyBufferManager
    : public tov::rendering::buffers::BufferManager<DummyBufferManager>
{
public:
    tov::rendering::buffers::BufferBase* createConstantBufferImpl(size_t size) { return nullptr; }
    tov::rendering::buffers::BufferBase* createIndexBufferImpl(size_t size) { return nullptr; }
    tov::rendering::buffers::BufferBase* createPixelUnpackBufferImpl(size_t size) { return nullptr; }
    tov::rendering::buffers::BufferBase* createVertexBufferImpl(size_t size) { return nullptr; }
};

TEST_CASE("Buffer", "[Buffer]")
{
    DummyBufferManager manager;

    SECTION("lock")
    {
        int* bufferStore = new int(42);

        const UsageSettings usageSettings = UsageSettings::STATIC;
        const AccessSettings accessSettings = AccessSettings::READ;
        auto buffer = DummyBuffer<usageSettings, accessSettings>(manager, sizeof(int), bufferStore);

        SECTION("with read lock settings")
        {
            SECTION("returns a lock pointer")
            {
                auto lock = buffer.lock(LockSettings::READ);
                REQUIRE(lock != nullptr);
            }

            SECTION("returns a lock pointer populated with the buffer data")
            {
                auto lock = buffer.lock(LockSettings::READ);
                auto i = *static_cast<int*>(lock);
                REQUIRE(i == 42);
                buffer.unlock();
            }
        }

        SECTION("with no-read lock settings")
        {
            SECTION("returns a lock pointer")
            {
                void* lock = buffer.lock(LockSettings::NO_READ);
                REQUIRE(lock != nullptr);
            }

            SECTION("returns a lock pointer without reading the buffer data")
            {
                void* lock = buffer.lock(LockSettings::NO_READ);
                int i = *static_cast<int*>(lock);
                REQUIRE(i != 42);
            }
        }
    }

    SECTION("unlock")
    {
        int* bufferStore = new int(42);

        const UsageSettings usageSettings = UsageSettings::STATIC;
        const AccessSettings accessSettings = AccessSettings::WRITE;
        auto buffer = DummyBuffer<usageSettings, accessSettings>(manager, sizeof(int), bufferStore);

        SECTION("with write lock settings")
        {
            SECTION("writes the buffer")
            {
                void* lock = buffer.lock(LockSettings::WRITE);
                int* lockInt = static_cast<int*>(lock);
                *lockInt = 144;
                buffer.unlock();
                REQUIRE(*bufferStore == 144);
            }
        }

        SECTION("with no-write lock settings")
        {
            SECTION("does not write the buffer")
            {
                void* lock = buffer.lock(LockSettings::NO_WRITE);
                int* lockInt = static_cast<int*>(lock);
                *lockInt = 144;
                buffer.unlock();
                REQUIRE(*bufferStore == 42);
            }
        }
    }

    SECTION("when locking with offset and length")
    {
        char bufferStore[8];

        const UsageSettings usageSettings = UsageSettings::STATIC;
        const AccessSettings accessSettings = AccessSettings::WRITE;
        auto buffer = DummyBuffer<usageSettings, accessSettings>(manager, sizeof(bufferStore), bufferStore);

        SECTION("writes the designated section of the buffer")
        {
            {
                void* lock = buffer.lock(0, 4, LockSettings::WRITE);
                memset(lock, '1', 4);
                buffer.unlock();
            }

            {
                void* lock = buffer.lock(4, 4, LockSettings::WRITE);
                memset(lock, '2', 4);
                buffer.unlock();
            }

            char expectedBufferStore[8]= { '1', '1', '1', '1', '2', '2', '2', '2' };
            REQUIRE(memcmp(bufferStore, expectedBufferStore, sizeof(bufferStore)) == 0);
        }
    }
}

TEST_CASE("Multiple buffers", "[Buffer]")
{
    DummyBufferManager manager;

    SECTION("can map to the same buffer store")
    {
        char bufferStore[8];

        const UsageSettings usageSettings = UsageSettings::STATIC;
        const AccessSettings accessSettings = AccessSettings::WRITE;

        {
            auto buffer = DummyBuffer<usageSettings, accessSettings>(manager, sizeof(bufferStore), bufferStore);
            void* lock = buffer.lock(0, 4, LockSettings::WRITE);
            memset(lock, '1', 4);
            buffer.unlock();
        }

        {
            auto buffer = DummyBuffer<usageSettings, accessSettings>(manager, sizeof(bufferStore), bufferStore);
            void* lock = buffer.lock(4, 4, LockSettings::WRITE);
            memset(lock, '2', 4);
            buffer.unlock();
        }

        char expectedBufferStore[8] = { '1', '1', '1', '1', '2', '2', '2', '2' };
        REQUIRE(memcmp(bufferStore, expectedBufferStore, sizeof(bufferStore)) == 0);
    }
}
