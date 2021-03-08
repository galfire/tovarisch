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
                    return operator new(sz);
                }

                void deallocate(void* ptr)
                {
                    operator delete(ptr);
                }

                void reset() {}
            };

        }
    }
}

#endif
