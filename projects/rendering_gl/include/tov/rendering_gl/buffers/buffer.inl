namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(buffers)

    template<
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
    GLenum Buffer<usageSettings, accessSettings>::getGLUsageSettings()
    {
        GLenum usage = 0;
        if ((usageSettings & UsageSettings::STATIC) == UsageSettings::STATIC)
        {
            usage = GL_STATIC_DRAW;
        }
        else if ((usageSettings & UsageSettings::DYNAMIC) == UsageSettings::DYNAMIC)
        {
            usage = GL_DYNAMIC_DRAW;
        }
        else if ((usageSettings & UsageSettings::STREAM) == UsageSettings::STREAM)
        {
            usage = GL_STREAM_DRAW;
        }
        return usage;
    }

    template<
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

    template<
        UsageSettings usageSettings,
        AccessSettings accessSettings
    >
    void Buffer<usageSettings, accessSettings>::discard()
    {
        auto b = bind();
        auto op = log_gl_op("buffer data", mBufferTarget, mBytes, sGLUsageSettings);
        glBufferData(this->mBufferTarget, this->mBytes, nullptr, sGLUsageSettings);
    }

    TOV_NAMESPACE_END // buffers
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}
