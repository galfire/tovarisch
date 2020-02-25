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
		tov::rendering::buffers::BufferManager& manager,
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
	: public tov::rendering::buffers::BufferManager
{};

TEST_CASE("Buffer", "[Buffer]")
{
	int data = 42;

	SECTION("lock")
	{
		const UsageSettings usageSettings = UsageSettings::STATIC;
		const AccessSettings accessSettings = AccessSettings::READ;
		tov::rendering::buffers::BufferManager manager;
		auto buffer = DummyBuffer<usageSettings, accessSettings>(manager, sizeof(int), &data);

		SECTION("with read lock settings")
		{
			SECTION("returns a lock pointer")
			{
				void* lock = buffer.lock(LockSettings::READ);
				REQUIRE(lock != nullptr);
			}

			SECTION("returns a lock pointer populated with the buffer data")
			{
				void* lock = buffer.lock(LockSettings::READ);
				int i = *static_cast<int*>(lock);
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
		const UsageSettings usageSettings = UsageSettings::STATIC;
		const AccessSettings accessSettings = AccessSettings::WRITE;
		tov::rendering::buffers::BufferManager manager;
		auto buffer = DummyBuffer<usageSettings, accessSettings>(manager, sizeof(int), &data);

		SECTION("with write lock settings")
		{
			SECTION("writes the buffer")
			{
				void* lock = buffer.lock(LockSettings::WRITE);
				int* lockInt = static_cast<int*>(lock);
				*lockInt = 144;
				buffer.unlock();
				REQUIRE(data == 144);
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
				REQUIRE(data == 42);
			}
		}
	}
}
