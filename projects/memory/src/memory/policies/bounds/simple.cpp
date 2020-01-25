#include <cstring>

#include "memory/policies/bounds/simple.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)
	TOV_NAMESPACE_BEGIN(policies)
	TOV_NAMESPACE_BEGIN(bounds)

	constexpr byte Simple::FRONT_BOUND_SIGNATURE[FRONT_BOUND_SIZE];
	constexpr byte Simple::END_BOUND_SIGNATURE[END_BOUND_SIZE];

	void Simple::signFront(void* memory)
	{
		memcpy(memory, FRONT_BOUND_SIGNATURE, FRONT_BOUND_SIZE);
	}

	void Simple::signEnd(void* memory)
	{
		memcpy(memory, END_BOUND_SIGNATURE, END_BOUND_SIZE);
	}

	bool Simple::checkFrontSignature(void* memory) const
	{
		if (memcmp(memory, FRONT_BOUND_SIGNATURE, FRONT_BOUND_SIZE) != 0)
			return false;
		return true;
	}

	bool Simple::checkEndSignature(void* memory) const
	{
		if (memcmp(memory, END_BOUND_SIGNATURE, END_BOUND_SIZE) != 0)
			return false;
		return true;
	}

	TOV_NAMESPACE_END // bounds
	TOV_NAMESPACE_END // policies
	TOV_NAMESPACE_END // mebmory
}