#ifndef TOV_RENDERING_SCENE_SKYBOX_H
#define TOV_RENDERING_SCENE_SKYBOX_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    class RenderSystem;

    TOV_NAMESPACE_BEGIN(mesh)
    class DrawData;
    class MeshInstance;
    TOV_NAMESPACE_END // mesh

    TOV_NAMESPACE_BEGIN(texture)
    class Texture;
    TOV_NAMESPACE_END // texture

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(scene)

    class Skybox
    {
        TOV_MOVABLE_ONLY(Skybox)

    public:
        Skybox(RenderSystem& renderSystem, texture::Texture* texture) noexcept;
        ~Skybox() noexcept;

        /*void setTexture(texture::Texture* texture) { mTexture = texture; }
        auto getTexture() const { return mTexture; }*/

        auto getDrawData() const -> mesh::DrawData const& { return *mDrawData.get(); }

    private:
        std::unique_ptr<mesh::DrawData> mDrawData;
        mesh::MeshInstance* mCubeInstance = nullptr;

        //texture::Texture* mTexture = nullptr;


    };

    TOV_NAMESPACE_END // scene
    TOV_NAMESPACE_END // rendering
}

#endif
