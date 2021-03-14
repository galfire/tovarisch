#ifndef TOV_MEMORY_TESTS_POLICIES_ALLOCATION_DUMMY_FIXED_H
#define TOV_MEMORY_TESTS_POLICIES_ALLOCATION_DUMMY_FIXED_H

namespace tov
{
    namespace test
    {
        namespace memory
        {
            namespace policies
            {
                namespace allocation
                {
                    class DummyFixed
                    {
                    public:
                        DummyFixed(void* start, void* end, size_t size)
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
    }
}

#endif
