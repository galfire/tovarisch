#include "rendering/entity.h"

#include "rendering/component.h"
#include "rendering/mesh_component.h"

#include "rendering/mesh/mesh_instance.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    Entity::Entity() noexcept
    {}

    Entity::~Entity() noexcept
    {}

    auto Entity::createMeshComponent(mesh::Mesh& mesh) -> MeshComponent&
    {
        mMeshComponent = createComponent<MeshComponent>(mesh);
        return *mMeshComponent;
    }
    
    auto Entity::getDrawDataList() const -> DrawDataList const&
    {
        if (mMeshComponent)
        {
            auto const& meshInstance = mMeshComponent->getMeshInstance();
            auto const& drawDataList = meshInstance.getDrawDataList();
            return drawDataList;
        }
        else
        {
            // FIXME: This will cause undefined behaviour since this returns a reference
            return {};
        }
    }

    auto Entity::getDrawDataList() -> DrawDataList&
    {
        auto& meshInstance = mMeshComponent->getMeshInstance();
        auto& drawDataList = meshInstance.getDrawDataList();
        return drawDataList;
    }

    TOV_NAMESPACE_END // rendering
}
