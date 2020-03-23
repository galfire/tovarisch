#include "buffer_manager.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(buffers)

    template<class ReaderT, class WriterT, UsageSettings usageSettings, AccessSettings accessSettings>
    void Buffer<ReaderT, WriterT, usageSettings, accessSettings>::read()
    {
        // Read the buffer into scratch
        mBufferAccessor.read(mLockOffset, mLockLength);
    }

    template<class ReaderT, class WriterT, UsageSettings usageSettings, AccessSettings accessSettings>
    void Buffer<ReaderT, WriterT, usageSettings, accessSettings>::write()
    {
        // Write scratch into the buffer
        mBufferAccessor.write(mLockOffset, mLockLength);
    }

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // rendering
}
