#include "../../test_helper.h"

#include <cstring>

#include <tov/memory/policies/alignment/standard.h>

TEST_CASE("Standard", "[Standard]")
{
	struct BlockHeader
	{
		size_t alignmentSpace;
		ptrdiff_t alignmentOffset;
	};

	tov::memory::policies::alignment::Standard policy;

	SECTION("align")
	{
		SECTION("returns a pointer aligned to the specified alignment when there is enough space")
		{
			const size_t alignment = 128;
			const size_t sz = 64;
			size_t space = 256;
			void* ptr = operator new(sz);
			void* alignedPtr = policy.align(alignment, sz, ptr, space);
			CHECK((uintptr_t)alignedPtr % alignment == 0);
		}
	}

	SECTION("writeHeader")
	{
		unsigned char buffer[sizeof(BlockHeader)];
		memset(buffer, 0xCC, sizeof(BlockHeader));

		SECTION("writes a header to the buffer of the given pointer with the given alignment and offset")
		{
			void* ptr = &buffer;
			policy.writeHeader(ptr, 32, 16);

			BlockHeader header = { 32, 16 };
			unsigned char* expectedBuffer[sizeof(BlockHeader)];
			memcpy(expectedBuffer, &header, sizeof(BlockHeader));

			int compare = memcmp(expectedBuffer, buffer, sizeof(BlockHeader));
			CHECK(compare == 0);
		}


		SECTION("moves the given pointer forward by the size of the header")
		{
			void* ptr = &buffer;
			policy.writeHeader(ptr, 32, 32);
			CHECK((uintptr_t)ptr == (uintptr_t)&buffer + sizeof(BlockHeader));
		}
	}

	SECTION("readHeader")
	{
		unsigned char buffer[1024];
		memset(buffer, 0xCC, 1024);
		void* ptr = &buffer;
		policy.writeHeader(ptr, 32, 16);

		SECTION("reads the header in the buffer of the given pointer")
		{
			void* readPtr = &buffer;
			size_t alignmentSpace;
			ptrdiff_t alignmentOffset;
			policy.readHeader(readPtr, alignmentSpace, alignmentOffset);
			CHECK(alignmentSpace == 32);
			CHECK(alignmentOffset == 16);
		}

		SECTION("moves the given pointer forward by the size of the header")
		{
			void* readPtr = &buffer;
			size_t alignmentSpace;
			ptrdiff_t alignmentOffset;
			policy.readHeader(readPtr, alignmentSpace, alignmentOffset);
			CHECK((uintptr_t)readPtr == (uintptr_t)&buffer + sizeof(BlockHeader));
		}
	}
}