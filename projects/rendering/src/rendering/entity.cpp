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
    
    auto Entity::getDrawDataList() const -> DrawDataList
    {
        assert(mMeshComponent);

        auto& meshInstance = mMeshComponent->getMeshInstance();
        return meshInstance.getDrawDataList();
    }

    TOV_NAMESPACE_END // rendering
}
