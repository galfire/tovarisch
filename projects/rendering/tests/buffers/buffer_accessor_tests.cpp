#include "../test_helper.h"
#include "buffer_test_helper.h"

#include <tov/rendering/buffers/buffer_accessor.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/buffer_copier.h>
#include <tov/rendering/buffers/lock_settings.h>

using tov::rendering::buffers::AccessSettings;
using tov::rendering::buffers::BufferCopier;
using tov::rendering::buffers::LockSettings;

TEST_CASE("BufferAccessor", "[BufferAccessor]")
{
	void* data = new int(42);
	void* scratch = new int(0);

	size_t sz = sizeof(int);

	SECTION("with write access settings")
	{
		constexpr AccessSettings U = AccessSettings::WRITE;
		tov::rendering::buffers::BufferAccessor<BufferCopier, BufferCopier, U> u(data, scratch);
		// Read data into scratch, no read
		u.read(0, sz);
		REQUIRE(*(int*)scratch == 0);
		// Write scratch into data
		*(int*)scratch = 144;
		u.write(0, sz);
		REQUIRE(*(int*)data == 144);
	}

	SECTION("with read access settings")
	{
		constexpr AccessSettings U = AccessSettings::READ;
		tov::rendering::buffers::BufferAccessor<BufferCopier, BufferCopier, U> u(data, scratch);
		// Read data into scratch
		u.read(0, sz);
		REQUIRE(*(int*)scratch == 42);
		// Write scratch into data, no write
		*(int*)scratch = 144;
		u.write(0, sz);
		REQUIRE(*(int*)data == 42);
	}

	SECTION("with read and write access settings")
	{
		constexpr AccessSettings U = AccessSettings::WRITE | AccessSettings::READ;
		tov::rendering::buffers::BufferAccessor<BufferCopier, BufferCopier, U> u(data, scratch);
		// Read data into scratch
		u.read(0, sz);
		REQUIRE(*(int*)scratch == 42);
		// Write scratch into data
		*(int*)scratch = 144;
		u.write(0, sz);
		REQUIRE(*(int*)data == 144);
	}
}
