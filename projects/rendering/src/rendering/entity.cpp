#include "rendering/entity.h"

#include "rendering/mesh_component.h"
#include "rendering/mesh/mesh.h"
#include "rendering/mesh/mesh_instance.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

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
            return {};
        }
    }


    TOV_NAMESPACE_END // rendering
}