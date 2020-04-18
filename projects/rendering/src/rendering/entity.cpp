#include "rendering/entity.h"

#include "rendering/mesh_component.h"
#include "rendering/mesh/mesh.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    auto Entity::createMeshComponent(mesh::Mesh& mesh) -> MeshComponent&
    {
        auto& meshComponent = *create<MeshComponent>(mesh);
        mMeshComponents.push_back(meshComponent);
        return meshComponent;
    }

    TOV_NAMESPACE_END // rendering
}