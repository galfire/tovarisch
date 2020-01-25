#ifndef TOV_MEMORY_TESTS_DUMMY_ALLOCATION_POLICY_H
#define TOV_MEMORY_TESTS_DUMMY_ALLOCATION_POLICY_H

namespace tov
{
	namespace test
	{
		namespace memory
		{
			class DummyAllocationPolicy
			{
			public:
				void* allocate(size_t sz)
				{
					void* ptr = operator new(sizeof(size_t) + sz);
					*static_cast<size_t*>(ptr) = sz;
					return static_cast<unsigned char*>(ptr) + sizeof(size_t);
				}

				void deallocate(void* ptr)
				{
					void* originalPtr = static_cast<unsigned char*>(ptr) - sizeof(size_t);
					operator delete(originalPtr);
				}

				size_t getAllocationSize(void* ptr) const
				{
					unsigned char* asByte = static_cast<unsigned char*>(ptr);
					asByte -= sizeof(size_t);
					size_t sz = *reinterpret_cast<size_t*>(asByte);
					return sz;
				}

				void reset() {}
			};

		}
	}
}

#endif