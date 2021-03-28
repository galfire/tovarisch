namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(buffers)

    template <
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
    Buffer<usageSettings, accessSettings>::Buffer(
        base::BufferManagerBase& manager,
        size_t bytes,
        GLenum bufferTarget
    ) 
        : base::Buffer<NullReader, BufferWriter, usageSettings, accessSettings>(
            manager,
            bytes,
            mBufferID,
            mBufferTarget
        )
        , mBufferTarget(bufferTarget)
    {
        {
            auto op = log_gl_op("generate buffer");
            glGenBuffers(1, &(this->mBufferID));
        }
        discard();
    }

    template<
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
    Buffer<usageSettings, accessSettings>::~Buffer()
    {
        auto op = log_gl_op("delete buffer");
        glDeleteBuffers(1, &(this->mBufferID));
    }

    template <
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
    void Buffer<usageSettings, accessSettings>::bind() const
    {
        auto op = log_gl_op("bind buffer", mBufferTarget, mBufferID);
        glBindBuffer(mBufferTarget, mBufferID);
    }

    template <
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
    void Buffer<usageSettings, accessSettings>::unbind() const
    {
        auto op = log_gl_op("unbind buffer", mBufferTarget, mBufferID);
        glBindBuffer(mBufferTarget, 0);
    }

    template <
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
        void Buffer<usageSettings, accessSettings>::discard()
    {
        auto bind = binder();
        auto op = log_gl_op("buffer data", this->mBufferTarget, this->mBytes, sGLUsageSettings);
        glBufferData(this->mBufferTarget, this->mBytes, nullptr, sGLUsageSettings);
    }

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}
