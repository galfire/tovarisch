#ifndef TOV_MEMORY_TESTS_POLICIES_THREAD_DUMMY_UNSAFE_H
#define TOV_MEMORY_TESTS_POLICIES_THREAD_DUMMY_UNSAFE_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            namespace policies
            {
                namespace thread
                {
                    class DummyUnsafe
                    {
                    public:
                        void enter() {};
                        void leave() {};
                    };
                }
            }
        }
    }
}

#endif
