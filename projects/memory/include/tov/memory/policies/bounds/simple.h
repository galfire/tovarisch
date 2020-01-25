#ifndef TOV_MEMORY_POLICIES_BOUNDS_SIMPLE_H
#define TOV_MEMORY_POLICIES_BOUNDS_SIMPLE_H

#include <tov/core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)
	TOV_NAMESPACE_BEGIN(policies)
	TOV_NAMESPACE_BEGIN(bounds)

	class Simple
	{
	public:
		// Number of bytes in the start bound guard
		constexpr static size_t FRONT_BOUND_SIZE = 4;
		// Number of bytes in the end bound guard
		constexpr static size_t END_BOUND_SIZE = 4;

		constexpr static size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;

		constexpr static byte FRONT_BOUND_TOKEN = 0xAF;
		constexpr static byte END_BOUND_TOKEN = 0xFC;

		constexpr static byte FRONT_BOUND_SIGNATURE[FRONT_BOUND_SIZE] = { FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN };
		constexpr static byte END_BOUND_SIGNATURE[END_BOUND_SIZE] = { END_BOUND_TOKEN, END_BOUND_TOKEN, END_BOUND_TOKEN, END_BOUND_TOKEN };

	public:
		void signFront(void* memory);
		void signEnd(void* memory);

		bool checkFrontSignature(void* memory) const;
		bool checkEndSignature(void* memory) const;
	};

	TOV_NAMESPACE_END // bounds
	TOV_NAMESPACE_END // policies
	TOV_NAMESPACE_END // memory
}

#endif