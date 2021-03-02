#include "test_helper.h"

#include <tov/memory/policies/bounds/simple.h>

TEST_CASE("Simple", "[None]")
{
	const size_t sz = 1024;
	char buffer[sz];
	memset(buffer, 0xFF, sz);

	tov::memory::policies::bounds::Simple policy;

	SECTION("signFront")
	{
		SECTION("writes the front bound signature at the given pointer")
		{
			policy.signFront(buffer);

			const unsigned char expectedSignature[4] = { 0xAF, 0xAF, 0xAF, 0xAF };
			const size_t signatureSize = 4;

			int compare = memcmp(expectedSignature, buffer, signatureSize);
			CHECK(compare == 0);
		}
	}

	SECTION("signEnd")
	{
		SECTION("writes the end bound signature at the given pointer")
		{
			policy.signEnd(buffer);

			const unsigned char expectedSignature[4] = { 0xFC, 0xFC, 0xFC, 0xFC };
			const size_t signatureSize = 4;

			int compare = memcmp(expectedSignature, buffer, signatureSize);
			CHECK(compare == 0);
		}
	}

	SECTION("checkFrontSignature")
	{
		SECTION("returns true for signed memory")
		{
			policy.signFront(buffer);
			CHECK(policy.checkFrontSignature(buffer));
		}

		SECTION("returns false for unsigned memory")
		{
			CHECK_FALSE(policy.checkFrontSignature(buffer));
		}
	}

	SECTION("checkEndSignature")
	{
		SECTION("returns true for signed memory")
		{
			policy.signEnd(buffer);
			CHECK(policy.checkEndSignature(buffer));
		}

		SECTION("returns false for unsigned memory")
		{
			CHECK_FALSE(policy.checkEndSignature(buffer));
		}
	}
}
