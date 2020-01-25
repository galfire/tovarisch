#include <catch2/catch.hpp>

#include <cstring>

#include <tov/memory/policies/bounds/none.h>

TEST_CASE("None", "[None]")
{
	const size_t sz = 1024;
	char buffer[sz];
	memset(buffer, 0xFF, sz);

	tov::memory::policies::bounds::None policy;

	SECTION("signFront")
	{
		SECTION("does nothing")
		{
			char original[sz];
			memset(original, 0xFF, sz);

			policy.signFront(buffer);

			int compare = memcmp(original, buffer, sz);
			REQUIRE(compare == 0);
		}
	}

	SECTION("signEnd")
	{
		SECTION("does nothing")
		{
			char original[sz];
			memset(original, 0xFF, sz);

			policy.signEnd(buffer);

			int compare = memcmp(original, buffer, sz);
			REQUIRE(compare == 0);
		}
	}
	
	SECTION("checkFrontSignature")
	{
		SECTION("returns true for signed memory")
		{
			policy.signFront(buffer);
			REQUIRE(policy.checkFrontSignature(buffer));
		}

		SECTION("returns true for unsigned memory")
		{
			REQUIRE(policy.checkFrontSignature(buffer));
		}
	}

	SECTION("checkEndSignature")
	{
		SECTION("returns true for signed memory")
		{
			policy.signEnd(buffer);
			REQUIRE(policy.checkEndSignature(buffer));
		}

		SECTION("returns true for unsigned memory")
		{
			REQUIRE(policy.checkEndSignature(buffer));
		}
	}
}
