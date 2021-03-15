#ifndef TOV_RENDERING_ENTITY_H
#define TOV_RENDERING_ENTITY_H

#include "rendering_core.h"

#include "scene_object.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class Component;
    class MeshComponent;

    TOV_NAMESPACE_BEGIN(mesh)

    class Mesh;

    TOV_NAMESPACE_END //mesh

    class Entity
        : public SceneObject
    {
        TOV_MOVABLE_ONLY(Entity)

    public:
        Entity() noexcept;
        ~Entity() noexcept;

        auto createMeshComponent(mesh::Mesh& mesh) -> MeshComponent&;
        auto getDrawDataList() const -> DrawDataList const& override;

    private:
        template<class T, class... U>
        auto createComponent(U&&... args)
        {
            {
                auto component = std::make_unique<T>(std::forward<U>(args)...);
                mComponents.push_back(std::move(component));
            }

            auto component = mComponents.back().get();
            return static_cast<T*>(component);
        }

    private:
        using ComponentList = std::vector<std::unique_ptr<Component>>;
        ComponentList mComponents;
        MeshComponent* mMeshComponent = nullptr;
    };

    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_ENTITY_H
