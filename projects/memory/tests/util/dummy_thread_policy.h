#ifndef TOV_MEMORY_TESTS_DUMMY_THREAD_POLICY_H
#define TOV_MEMORY_TESTS_DUMMY_THREAD_POLICY_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            class DummyThreadPolicy
            {
            public:
                void enter() {};
                void leave() {};
            };
        }
    }
}

#endif
