#include "../test_helper.h"

#include <tov/rendering/buffers/buffer_object.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/buffer_object_manager.h>
#include <tov/rendering/buffers/buffer_reader.h>
#include <tov/rendering/buffers/buffer_writer.h>
#include <tov/rendering/buffers/usage_settings.h>

class DummyReader
	: public tov::rendering::buffers::BufferReader<DummyReader>
{
public:
	DummyReader(void* dataPtr)
		: mDataPtr(dataPtr)
	{}

	void readImpl(size_t offset, size_t length, void* pDest)
	{
		int* pDestInt = static_cast<int*>(pDest);
		*pDestInt = *static_cast<int*>(mDataPtr);
	}

private:
	void* mDataPtr = nullptr;
};

class DummyWriter
	: public tov::rendering::buffers::BufferWriter<DummyWriter>
{
public:
	DummyWriter(void* dataPtr)
		: mDataPtr(dataPtr)
	{}

	void writeImpl(size_t offset, size_t length, void* pSrc)
	{
		int* pSrcInt = static_cast<int*>(pSrc);
		*static_cast<int*>(mDataPtr) = *pSrcInt;
	}

private:
	void* mDataPtr = nullptr;
};

using tov::rendering::buffers::AccessSettings;
using tov::rendering::buffers::LockSettings;
using tov::rendering::buffers::UsageSettings;

template<UsageSettings usageSettings, AccessSettings accessSettings>
class DummyBufferObject
	: public tov::rendering::buffers::BufferObject<DummyReader, DummyWriter, usageSettings, accessSettings>
{
public:
	DummyBufferObject(
		tov::rendering::buffers::BufferObjectManager& manager,
		size_t bytes,
		int* dataPtr
	)
		: tov::rendering::buffers::BufferObject<DummyReader, DummyWriter, usageSettings, accessSettings>(manager, bytes, dataPtr)
	{}
};

TEST_CASE("BufferObject", "[BufferObject]")
{
	
	int data = 42;

	const UsageSettings usageSettings = UsageSettings::STATIC;
	const AccessSettings accessSettings = AccessSettings::READ | AccessSettings::WRITE;
	tov::rendering::buffers::BufferObjectManager manager;
	auto bufferObject = DummyBufferObject<usageSettings, accessSettings>(manager, sizeof(int), &data);

	SECTION("lock")
	{
		SECTION("with read lock settings")
		{
			SECTION("returns a lock pointer")
			{
				void* lock = bufferObject.lock(LockSettings::READ);
				REQUIRE(lock != nullptr);
			}

			SECTION("returns a lock pointer populated with the buffer data")
			{
				void* buffer = bufferObject.lock(LockSettings::READ);
				int i = *static_cast<int*>(buffer);
				REQUIRE(i == 42);
			}
		}

		SECTION("with no-read lock settings")
		{
			SECTION("returns a lock pointer")
			{
				void* lock = bufferObject.lock(LockSettings::NO_READ);
				REQUIRE(lock != nullptr);
			}

			SECTION("returns a lock pointer without reading the buffer data")
			{
				void* buffer = bufferObject.lock(LockSettings::NO_READ);
				int i = *static_cast<int*>(buffer);
				REQUIRE(i != 42);
			}
		}
	}

	SECTION("unlock")
	{
		SECTION("with write lock settings")
		{
			SECTION("writes the buffer")
			{
				void* lock = bufferObject.lock(LockSettings::WRITE);
				int* lockInt = static_cast<int*>(lock);
				*lockInt = 144;
				bufferObject.unlock();
				REQUIRE(data == 144);
			}
		}

		SECTION("with no-write lock settings")
		{
			SECTION("does not write the buffer")
			{
				void* lock = bufferObject.lock(LockSettings::NO_WRITE);
				int* lockInt = static_cast<int*>(lock);
				*lockInt = 144;
				bufferObject.unlock();
				REQUIRE(data == 42);
			}
		}
	}
}
