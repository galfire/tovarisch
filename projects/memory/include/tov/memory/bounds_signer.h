#ifndef TOV_MEMORY_BOUNDS_SIGNER_H
#define TOV_MEMORY_BOUNDS_SIGNER_H

#include <tov/core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(memory)

	template<typename BoundsPolicy>
	class BoundsSigner
	{
	public:
		inline void signFront(void*& memory)
		{
			mBoundsPolicy.signFront(memory);

			union
			{
				void** raw;
				tov::byte** byte;
			};

			raw = &memory;
			*byte += BoundsPolicy::FRONT_BOUND_SIZE;
		}

		inline void signEnd(void*& memory)
		{
			mBoundsPolicy.signEnd(memory);
			
			union
			{
				void** raw;
				tov::byte** byte;
			};

			raw = &memory;
			*byte += BoundsPolicy::END_BOUND_SIZE;
		}

	private:
		BoundsPolicy mBoundsPolicy;
	};

	TOV_NAMESPACE_END // memory
}

#endif