#ifndef TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_TOKEN_H
#define TOV_MEMORY_TESTS_POLICIES_BOUNDS_DUMMY_TOKEN_H

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
                    template <unsigned char TOKEN>
                    class DummyToken
                    {
                    public:
                        constexpr static size_t BOUND_SIZE = 4;
                        constexpr static unsigned char BOUND_TOKEN = TOKEN;
                        constexpr static unsigned char BOUND_SIGNATURE[BOUND_SIZE] = { BOUND_TOKEN, BOUND_TOKEN, BOUND_TOKEN, BOUND_TOKEN };

                    public:
                        void sign(void* memory)
                        {
                            memcpy(memory, BOUND_SIGNATURE, BOUND_SIZE);
                        }

                        bool checkSignature(void* memory) const
                        {
                            return memcmp(memory, BOUND_SIGNATURE, BOUND_SIZE) == 0;
                        }
                    };
                }
            }
        }
    }
}

#endif
