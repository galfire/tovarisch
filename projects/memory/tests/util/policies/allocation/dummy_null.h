#ifndef TOV_MEMORY_TESTS_POLICIES_ALLOCATION_DUMMY_NULL_H
#define TOV_MEMORY_TESTS_POLICIES_ALLOCATION_DUMMY_NULL_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            namespace policies
            {
                namespace allocation
                {
                    class DummyNull
                    {
                    public:
                        DummyNull() {}
                        DummyNull(void* start, void* end) {}
                        DummyNull(void* start, void* end, size_t size) {};

                        void* allocate()
                        {
                            return nullptr;
                        }

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
    }
}

#endif
