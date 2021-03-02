#include "test_helper.h"

#include <tov/memory/memory_accessor.h>

TEST_CASE("MemoryAcessor", "[MemoryAccessor]")
{
	tov::memory::MemoryAccessor<int> accessor;

	char buffer[sizeof(int)];
	memset(&buffer, 0xFF, sizeof(int));

	SECTION("write")
	{
		SECTION("writes the given memory to the buffer")
		{
			int i = 42;
			accessor.write(&buffer, &i);
			int compare = memcmp(&i, buffer, sizeof(int));
			CHECK(compare == 0);
		}
	}

	SECTION("read")
	{
		int i = 42;
		accessor.write(&buffer, &i);

		SECTION("reads the buffer and writes the memory to the out location")
		{
			int out;
			accessor.read(&buffer, out);
			CHECK(out == 42);
		}
	}
}
