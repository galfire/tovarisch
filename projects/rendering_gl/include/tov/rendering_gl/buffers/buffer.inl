namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	GLenum Buffer<usageSettings, accessSettings>::getGLAccessSettings(Buffer::AccessSettings accessSettings)
	{
		GLenum access = 0;
		if ((accessSettings & AccessSettings::READ) == AccessSettings::READ)
		{
			access |= GL_MAP_READ_BIT;
		}
		else if ((accessSettings & AccessSettings::WRITE) == AccessSettings::WRITE)
		{
			access |= GL_MAP_WRITE_BIT;
		}
		return access;
	}

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	GLenum Buffer<usageSettings, accessSettings>::getGLUsageSettings(Buffer::UsageSettings usageSettings)
	{
		if ((usageSettings & UsageSettings::STATIC) == UsageSettings::STATIC)
		{
			return GL_STATIC_DRAW;
		}
		else if ((usageSettings & UsageSettings::DYNAMIC) == UsageSettings::DYNAMIC)
		{
			return GL_DYNAMIC_DRAW;
		}
		else if ((usageSettings & UsageSettings::STREAM) == UsageSettings::STREAM)
		{
			return GL_STREAM_DRAW;
		}
	}

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	Buffer<usageSettings, accessSettings>::Buffer(
		rendering::buffers::BufferManager& manager,
		size_t bytes,
		GLenum bufferTarget
	)
		: mBufferTarget(bufferTarget)
		, rendering::buffers::Buffer<BufferCopier, BufferCopier, usageSettings, accessSettings>(
			manager,
			bytes
		)
	{
		auto op = log_gl_op("generate buffer");
		glGenBuffers(1, &mBufferID);
	}

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	Buffer<usageSettings, accessSettings>::~Buffer()
	{
		auto op = log_gl_op("delete buffer");
		glDeleteBuffers(1, &mBufferID);
	}

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	void Buffer<usageSettings, accessSettings>::map()
	{
		auto b = bind();
		auto op = log_gl_op("map buffer", mBufferTarget, mBufferID);
		mBuffer = glMapBufferRange(mBufferTarget, mLockOffset, mLockLength, sGLAccessSettings);
	}

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	void Buffer<usageSettings, accessSettings>::unmap()
	{
		auto b = bind();
		auto op = log_gl_op("unmap buffer", mBufferTarget, mBufferID);
		glUnmapBuffer(mBufferTarget);
		mBuffer = nullptr;
	}

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	void Buffer<usageSettings, accessSettings>::discard()
	{
		auto b = bind();
		auto op = log_gl_op("discard buffer", mBufferTarget, mBufferID);
		glBufferData(mBufferTarget, mBytes, nullptr, sGLUsageSettings);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // buffers
}
