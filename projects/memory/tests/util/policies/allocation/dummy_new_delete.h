#ifndef TOV_MEMORY_TESTS_POLICIES_ALLOCATION_DUMMY_NEW_DELETE_H
#define TOV_MEMORY_TESTS_POLICIES_ALLOCATION_DUMMY_NEW_DELETE_H

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
                    class DummyNewDelete
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
    }
}

#endif
