#ifndef TOV_RENDERING_GL_BUFFERS_BUFFER_H
#define TOV_RENDERING_GL_BUFFERS_BUFFER_H

#include <tov/rendering/buffers/buffer.h>

#include <tov/rendering/buffers/access_settings.h>
#include <tov/rendering/buffers/buffer_copier.h>
#include <tov/rendering/buffers/usage_settings.h>

#include <tov/rendering_gl/gl_impl.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(buffers)

	using BufferCopier = tov::rendering::buffers::BufferCopier;

	class Binder
	{
	public:
		Binder(GLuint bufferID, GLenum bufferTarget)
			: mBufferID(bufferID)
			, mBufferTarget(bufferTarget)
		{
			auto op = log_gl_op("bind buffer", mBufferTarget, mBufferID);
			glBindBuffer(mBufferTarget, mBufferID);
		}

		~Binder()
		{
			auto op = log_gl_op("unbind buffer", mBufferTarget, mBufferID);
			glBindBuffer(mBufferTarget, 0);
		}

	private:
		GLuint mBufferID;
		GLenum mBufferTarget;
	};

	template<
		rendering::buffers::UsageSettings usageSettings,
		rendering::buffers::AccessSettings accessSettings
	>
	class Buffer
		: public rendering::buffers::Buffer<BufferCopier, BufferCopier, usageSettings, accessSettings>
	{
	private:
		using AccessSettings = tov::rendering::buffers::AccessSettings;
		using UsageSettings = tov::rendering::buffers::UsageSettings;

		static GLenum getGLAccessSettings(AccessSettings accessSettings);
		static GLenum getGLUsageSettings(UsageSettings usageSettings);

	public:
		Buffer(
			rendering::buffers::BufferManager& manager,
			size_t bytes,
			GLenum bufferTarget
		);
		~Buffer();

		void discard() override;

	private:
		void map() override;
		void unmap() override;

		auto bind() { return Binder(mBufferID, mBufferTarget); }

	private:
		GLuint mBufferID;
		GLenum mBufferTarget;
		static inline GLenum sGLAccessSettings = getGLAccessSettings(accessSettings);
		static inline GLenum sGLUsageSettings = getGLUsageSettings(usageSettings);
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}

#include "buffer.inl"

#endif