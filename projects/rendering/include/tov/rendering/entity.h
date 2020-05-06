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

    private:
        auto getDrawDataList() const -> DrawDataList const& override;

        template<class T, class... U>
        auto createComponent(U&&... args)
        {
            auto component = std::unique_ptr<T>(
                new T(std::forward<U>(args)...)
            );
            mComponents.push_back(std::move(component));
            auto ret = mComponents.back().get();
            return static_cast<T*>(ret);
        }

    private:
        using ComponentList = std::vector<std::unique_ptr<Component>>;
        ComponentList mComponents;
        MeshComponent* mMeshComponent = nullptr;
    };

    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_ENTITY_H
