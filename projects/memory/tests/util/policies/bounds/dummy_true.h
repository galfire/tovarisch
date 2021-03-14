#ifndef TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_TRUE_H
#define TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_TRUE_H

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
                    class DummyTrue
                    {
                    public:
                        void signFront(void* memory) {}
                        void signEnd(void* memory) {}

                        bool checkFrontSignature(void* memory) const
                        {
                            return true;
                        }

                        bool checkEndSignature(void* memory) const
                        {
                            return true
                        }
                    };
                }
            }
        }
    }
}

#endif
