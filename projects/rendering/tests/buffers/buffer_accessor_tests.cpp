#include "../test_helper.h"

#include <tov/rendering/buffers/buffer_accessor.h>

#include <tov/rendering/buffers/buffer_reader.h>
#include <tov/rendering/buffers/buffer_writer.h>
#include <tov/rendering/buffers/lock_settings.h>
#include <tov/rendering/buffers/access_settings.h>

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


TEST_CASE("BufferAccessor", "[BufferAccessor]")
{
	using tov::rendering::buffers::AccessSettings;
	using tov::rendering::buffers::LockSettings;

	int data = 42;
	int scratch = 0;

	size_t sz = sizeof(int);

	SECTION("with write access settings")
	{
		constexpr AccessSettings U = AccessSettings::WRITE;
		tov::rendering::buffers::BufferAccessor<DummyReader, DummyWriter, U> u(static_cast<void*>(&data));
		// Read data into scratch, no read
		u.read(0, sz, &scratch);
		REQUIRE(scratch == 0);
		// Write scratch into data
		scratch = 144;
		u.write(0, sz, &scratch);
		REQUIRE(data == 144);
	}

	SECTION("with read access settings")
	{
		constexpr AccessSettings U = AccessSettings::READ;
		tov::rendering::buffers::BufferAccessor<DummyReader, DummyWriter, U> u(static_cast<void*>(&data));
		// Read data into scratch
		u.read(0, sz, &scratch);
		REQUIRE(scratch == 42);
		// Write scratch into data, no write
		scratch = 144;
		u.write(0, sz, &scratch);
		REQUIRE(data == 42);
	}

	SECTION("with read and write access settings")
	{
		constexpr AccessSettings U = AccessSettings::WRITE | AccessSettings::READ;
		tov::rendering::buffers::BufferAccessor<DummyReader, DummyWriter, U> u(static_cast<void*>(&data));
		// Read data into scratch
		u.read(0, sz, &scratch);
		REQUIRE(scratch == 42);
		// Write scratch into data
		scratch = 144;
		u.write(0, sz, &scratch);
		REQUIRE(data == 144);
	}
}
