#include <tov/rendering_gl/pipeline/framebuffer.h>

#include <tov/rendering_gl/texture/texture.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(gl)
	TOV_NAMESPACE_BEGIN(pipeline)

	Framebuffer::Framebuffer(bool isDefault)
		: rendering::pipeline::Framebuffer(isDefault)
	{
		if (mIsDefault)
		{
			mFramebufferID = 0;
		}
		else
		{
			auto op = log_gl_op("generate framebuffer");
			glGenFramebuffers(1, &mFramebufferID);
		}
	}

	Framebuffer::~Framebuffer()
	{
	}

	auto Framebuffer::attachTextureImpl(
		rendering::texture::Texture2D const* const texture, 
		rendering::pipeline::FramebufferAttachments attachment
	) -> void
	{
		auto bind = FramebufferBinder(mFramebufferID);

		auto glTexture = static_cast<gl::texture::Texture2D const* const>(texture);
		auto glTextureID = glTexture->getTextureID();
		auto glAttachment = (GLenum)0;
		switch (attachment)
		{
		case rendering::pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_0:
			glAttachment = GL_COLOR_ATTACHMENT0;
			break;
		case rendering::pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_1:
			glAttachment = GL_COLOR_ATTACHMENT1;
			break;
		case rendering::pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_2:
			glAttachment = GL_COLOR_ATTACHMENT2;
			break;
		case rendering::pipeline::FramebufferAttachments::COLOUR_ATTACHMENT_3:
			glAttachment = GL_COLOR_ATTACHMENT3;
			break;
		}
		{
			auto op = log_gl_op("framebuffer texture2D", glAttachment, glTextureID);
			glFramebufferTexture2D(GL_FRAMEBUFFER, glAttachment, GL_TEXTURE_2D, glTextureID, 0);
		}
	}

	auto Framebuffer::bindImpl() const -> void
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferID);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!mIsDefault)
		{
			unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };

			auto op = log_gl_op("set draw buffers", mNumAttachments);
			glDrawBuffers(mNumAttachments, attachments);
		}
	}

	TOV_NAMESPACE_END // pipeline
	TOV_NAMESPACE_END // gl
	TOV_NAMESPACE_END // rendering
}
