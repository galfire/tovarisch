#ifndef TOV_MEMORY_TESTS_POLICIES_ALIGNMENT_DUMMY_STANDARD_H
#define TOV_MEMORY_TESTS_POLICIES_ALIGNMENT_DUMMY_STANDARD_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            namespace policies
            {
                namespace alignment
                {
                    class DummyStandard
                    {
                    public:
                        inline size_t determineAlignmentSpace(size_t alignment)
                        {
                            return alignment - 1;
                        }

                        inline void* align(size_t alignment, size_t size, void*& ptr, size_t& space)
                        {
                            return std::align(alignment, size, ptr, space);
                        }
                    };
                }
            }
        }
    }
}

#endif
