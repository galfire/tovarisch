#include <rendering/material_instance.h>

#include <rendering/material.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	MaterialInstance::MaterialInstance(
		Material& parentMaterial,
		pipeline::RasterizerStateDescriptor rasterizerStateDescriptor
	) noexcept
		: mRasterizerStateDescriptor(rasterizerStateDescriptor)
	{
		setAlbedoMap(parentMaterial.getAlbedoMap());
		setNormalMap(parentMaterial.getNormalMap());
	}

	TOV_NAMESPACE_END // rendering
}
