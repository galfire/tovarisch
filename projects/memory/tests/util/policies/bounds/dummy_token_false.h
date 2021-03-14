#ifndef TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_TOKEN_TRUE_H
#define TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_TOKEN_TRUE_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            namespace policies
            {
                namespace bounds
                {
                    class DummyTokenFalse
                    {
                    public:
                        constexpr static size_t BOUND_SIZE = 0;

                    public:
                        void sign(void* memory) {}
                        bool checkSignature(void* memory) const
                        {
                            return false;
                        }
                    };
                }
            }
        }
    }
}

#endif
