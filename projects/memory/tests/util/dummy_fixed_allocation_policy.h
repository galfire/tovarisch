#ifndef TOV_MEMORY_TESTS_DUMMY_ALLOCATION_POLICY_H
#define TOV_MEMORY_TESTS_DUMMY_ALLOCATION_POLICY_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            class DummyFixedAllocationPolicy
            {
            public:
                DummyFixedAllocationPolicy(void* start, void* end, size_t size)
                {
                    mStart = start;
                    mEnd = end;
                    mCurrent = (void*)mStart;
                    mSize = size;
                }

                void* allocate()
                {
                    void* userPtr = mCurrent;
                    mCurrent = static_cast<byte*>(mCurrent) + mSize;
                    
                    return userPtr;
                }

                void deallocate(void* ptr)
                {
                    (void)ptr;
                }

                void reset() {}

            private:
                void* mStart;
                void* mEnd;
                void* mCurrent;
                size_t mSize;
            };
        }
    }
}

#endif
