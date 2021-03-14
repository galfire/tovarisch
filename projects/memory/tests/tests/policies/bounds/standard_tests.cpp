#include "test_helper.h"

#include <tov/memory/policies/bounds/standard.h>
#include <tov/memory/policies/bounds/token.h>

namespace
{
	template <tov::byte TOKEN>
	using Token = tov::memory::policies::bounds::Token<TOKEN>;

	template <class Front, class Back>
	using Policy = tov::memory::policies::bounds::Standard<Front, Back>;
}

TEST_CASE("Standard", "[None]")
{
	const size_t sz = 1024;
	char buffer[sz];
	memset(buffer, 0xFF, sz);

	Policy<Token<'a'>, Token<'z'>> policy;

	SECTION("signFront")
	{
		SECTION("writes the front bound signature at the given pointer")
		{
			policy.signFront(buffer);

			const unsigned char expectedSignature[] = "aaaa";
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

			const unsigned char expectedSignature[] = "zzzz";
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
