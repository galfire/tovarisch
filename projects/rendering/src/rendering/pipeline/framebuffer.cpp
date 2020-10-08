#include <rendering/pipeline/framebuffer.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(pipeline)

	auto Framebuffer::attachTexture(texture::Texture2D const* const texture, FramebufferAttachments attachment) -> void
	{
		mNumAttachments++;
		mFrameBufferAttachments &= attachment;
		attachTextureImpl(texture, attachment);
	}

	TOV_NAMESPACE_END // rendering
	TOV_NAMESPACE_END // pipeline
}
