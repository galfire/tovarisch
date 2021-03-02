#include "test_helper.h"

#include <tov/memory/heap_area.h>

TEST_CASE("HeapArea", "[HeapArea]")
{
	const size_t sz = 1024;
	tov::memory::HeapArea area(sz);

	SECTION("getStart")
	{
		SECTION("returns a valid pointer")
		{
			CHECK(area.getStart() != nullptr);
		}
	}

	SECTION("getEnd")
	{
		SECTION("returns a valid pointer")
		{
			CHECK(area.getEnd() != nullptr);
		}

		SECTION("returns a pointer SIZE bytes after the start pointer")
		{
			void* start = area.getStart();
			void* end = area.getEnd();
			CHECK((uintptr_t)end - (uintptr_t)start == sz);
		}
	}

	SECTION("getSize")
	{
		SECTION("returns the size of the HeapArea")
		{
			CHECK(area.getSize() == sz);
		}
	}
}
