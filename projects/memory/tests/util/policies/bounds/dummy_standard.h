#ifndef TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_STANDARD_H
#define TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_STANDARD_H

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
                    template <
                        class Front,
                        class Back
                    >
                    class DummyStandard
                    {
                    public:
                        constexpr static size_t FRONT_BOUND_SIZE = Front::BOUND_SIZE;
                        constexpr static size_t END_BOUND_SIZE = Back::BOUND_SIZE;
                        constexpr static size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;

                    public:
                        void signFront(void* memory)
                        {
                            mFront.sign(memory);
                        }

                        void signEnd(void* memory)
                        {
                            mBack.sign(memory);
                        }

                        bool checkFrontSignature(void* memory) const
                        {
                            return mFront.checkSignature(memory);
                        }

                        bool checkEndSignature(void* memory) const
                        {
                            return mBack.checkSignature(memory);
                        }

                    private:
                        Front mFront;
                        Back mBack;
                    };
                }
            }
        }
    }
}

#endif
