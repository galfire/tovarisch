#include "test_helper.h"

#include <tov/memory/policies/bounds/token.h>

TEST_CASE("Token", "[None]")
{
	const size_t sz = 1024;
	char buffer[sz];
	memset(buffer, 0xFF, sz);

	tov::memory::policies::bounds::Token<'c'> policy;

	SECTION("sign")
	{
		SECTION("writes the front bound signature at the given pointer")
		{
			policy.sign(buffer);

			const unsigned char expectedSignature[] = { 'c', 'c', 'c', 'c' };
			const size_t signatureSize = 4;

			int compare = memcmp(expectedSignature, buffer, signatureSize);
			CHECK(compare == 0);
		}
	}

	SECTION("checkSignature")
	{
		SECTION("returns true for signed memory")
		{
			policy.sign(buffer);
			CHECK(policy.checkSignature(buffer));
		}

		SECTION("returns false for unsigned memory")
		{
			CHECK_FALSE(policy.checkSignature(buffer));
		}
	}
}
