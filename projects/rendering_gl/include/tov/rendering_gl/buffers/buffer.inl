namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	GLenum Buffer<usageSettings, accessSettings>::getGLAccessSettings()
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
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	Buffer<usageSettings, accessSettings>::Buffer(
		rendering::buffers::BufferManagerBase& manager,
		size_t bytes,
		GLenum bufferTarget
	) 
		: rendering::buffers::Buffer<NullReader, BufferWriter, usageSettings, accessSettings>(
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
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	Buffer<usageSettings, accessSettings>::~Buffer()
	{
		auto op = log_gl_op("delete buffer");
		glDeleteBuffers(1, &(this->mBufferID));
	}

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	void Buffer<usageSettings, accessSettings>::discard()
	{
		auto b = bind();
		auto op = log_gl_op("discard buffer");
		glBufferData(this->mBufferTarget, this->mBytes, nullptr, sGLUsageSettings);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // buffers
}
