#ifndef TOV_MEMORY_TESTS_DUMMY_NULL_ALLOCATION_POLICY_H
#define TOV_MEMORY_TESTS_DUMMY_NULL_ALLOCATION_POLICY_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            class DummyNullAllocationPolicy
            {
            public:
                void* allocate(size_t sz)
                {
                    return nullptr;
                }

                void deallocate(void* ptr)
                {
                }

                void reset() {}
            };
        }
    }
}

#endif
