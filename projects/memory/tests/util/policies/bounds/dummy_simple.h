#ifndef TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_SIMPLE_H
#define TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_SIMPLE_H

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
                    class DummySimple
                    {
                    public:
                        constexpr static size_t FRONT_BOUND_SIZE = 4;
                        constexpr static size_t END_BOUND_SIZE = 4;
                        constexpr static size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;

                        constexpr static byte FRONT_BOUND_TOKEN = 'a';
                        constexpr static byte END_BOUND_TOKEN = 'z';

                        constexpr static byte FRONT_BOUND_SIGNATURE[FRONT_BOUND_SIZE] = { FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN };
                        constexpr static byte END_BOUND_SIGNATURE[END_BOUND_SIZE] = { END_BOUND_TOKEN, END_BOUND_TOKEN, END_BOUND_TOKEN, END_BOUND_TOKEN };


                    public:
                        void signFront(void* memory)
                        {
                            memcpy(memory, FRONT_BOUND_SIGNATURE, FRONT_BOUND_SIZE);
                        }
                        void signEnd(void* memory)
                        {
                            memcpy(memory, END_BOUND_SIGNATURE, END_BOUND_SIZE);
                        }

                        bool checkFrontSignature(void* memory) const
                        {
                            return memcmp(memory, FRONT_BOUND_SIGNATURE, FRONT_BOUND_SIZE) == 0;
                        }

                        bool checkEndSignature(void* memory) const
                        {
                            return memcmp(memory, END_BOUND_SIGNATURE, END_BOUND_SIZE) == 0;
                        }
                    };
                }
            }
        }
    }
}

#endif
