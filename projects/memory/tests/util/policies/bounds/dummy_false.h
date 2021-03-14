#ifndef TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_FALSE_H
#define TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_FALSE_H

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
                    class DummyFalse
                    {
                    public:
                        constexpr static size_t FRONT_BOUND_SIZE = 0;
                        constexpr static size_t END_BOUND_SIZE = 0;
                        constexpr static size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;

                    public:
                        void signFront(void* memory) {}
                        void signEnd(void* memory) {}

                        bool checkFrontSignature(void* memory) const
                        {
                            return false;
                        }

                        bool checkEndSignature(void* memory) const
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
