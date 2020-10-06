#include <rendering/material_instance.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	MaterialInstance::MaterialInstance(
		pipeline::ProgramInstance& programInstance,
		pipeline::RasterizerStateDescriptor rasterizerStateDescriptor
	) noexcept
		: mProgramInstance(programInstance)
		, mRasterizerStateDescriptor(rasterizerStateDescriptor)
	{
	}

	TOV_NAMESPACE_END // rendering
}
