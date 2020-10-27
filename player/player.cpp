// player.cpp : Defines the entry point for the application.
//

#include "player.h"

#include <tov/core.h>

#include <tov/math/matrix.h>
#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

#include <tov/rendering/backend.h>

#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/image.h>
#include <tov/rendering/material.h>
#include <tov/rendering/pixel_format.h>
#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering/geometry/cube.h>
#include <tov/rendering/geometry/sphere.h>

#include <tov/rendering/buffers/pixel_buffer_object.h>

#include <tov/rendering/entity.h>

#include <tov/rendering/mesh_component.h>
#include <tov/rendering/mesh/mesh.h>
#include <tov/rendering/mesh/mesh_manager.h>
#include <tov/rendering/mesh/submesh.h>
#include <tov/rendering/mesh/vertex_data_format.h>

#include <tov/rendering/texture/texture.h>

#include <tov/rendering/web/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <emscripten/emscripten.h>

using WindowPlatformSupport = tov::rendering::web::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::web::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem;

WindowPlatformSupport platformSupport;
WindowRendererSupport rendererSupport;
std::unique_ptr<RenderSystem> rs;
tov::rendering::Scene* scene_;
auto node = (tov::rendering::SceneNode*)nullptr;

//adfadfadfadfadfad

void oneIteration()
{
    auto axis = tov::math::Vector3(0.0f, 1.0f, 0.0f);
    auto angle = tov::math::Radian(0.03f);
    auto rotation = tov::math::Quaternion(angle, axis);
    node->getTransform().rotate(rotation);

    rs->renderFrame(*scene_);
    rs->swapBuffers();
}

int main()
{
    rs = std::unique_ptr<tov::rendering::RenderSystem>(
        tov::rendering::backend::createRenderSystem(platformSupport, rendererSupport)
    );

    scene_ = new tov::rendering::Scene(*rs.get());
    auto& scene = *scene_;

    auto& root = scene.getRootNode();

    auto& cameraNode = root.createChild();
    auto& camera = scene.createCamera();
    cameraNode.attachSceneObject(&camera);

    {
        auto& window = rs->createRenderWindow("#canvas1", 800, 600, false);
        auto& vp = window.createViewport(2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Black);
        camera.attachViewport(vp);
    }

    rs->initialize();

    auto bufferManager = rs->getBufferManager();

    auto colourMaterial = tov::rendering::Material();
    {
        auto pixelFormat = tov::rendering::PixelFormat(8, 8, 8, 8, 0, 0);
        auto& texture = rs->createTexture2D(16, 16, pixelFormat);

        auto size = 16u * 16u * pixelFormat.getSize();
        auto& pixelBuffer = *bufferManager->createPixelUnpackBuffer(pixelFormat, size);
        auto pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);
        texture.setPixelBufferObject(pbo);

        auto buffer = new unsigned char[size];
        for (auto i = 0u; i < size; i += 4)
        {
            buffer[i + 0] = 122;
            buffer[i + 1] = 0;
            buffer[i + 2] = 255;
            buffer[i + 3] = 255;
        }
        pbo.updatePixelData(buffer, size);
        delete[] buffer;

        texture.unpackPixelData();

        colourMaterial.setAlbedoMap(&texture);
    }

    auto textureMaterial = tov::rendering::Material();
    {
        auto image = tov::rendering::Image("./assets/skybox.png");
        auto pixelFormat = image.getPixelFormat();
        auto& texture = rs->createTexture2D(image.getWidth(), image.getHeight(), pixelFormat);

        auto size = image.getSize();
        auto& pixelBuffer = *bufferManager->createPixelUnpackBuffer(pixelFormat, size);
        auto pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);
        texture.setPixelBufferObject(pbo);

        auto data = image.data();
        pbo.updatePixelData(data, size);
        texture.unpackPixelData();

        textureMaterial.setAlbedoMap(&texture);
    }

    auto vertexDataFormat = tov::rendering::mesh::VertexDataFormat();
    {
        tov::rendering::buffers::VertexFormat vf;
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::POSITION, 0);
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::NORMAL, 1);
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::TEXTURE_COORDINATE, 2);
        tov::rendering::buffers::VertexBufferFormat vbf(
            tov::rendering::buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
            vf
        );
        vertexDataFormat.mapHandleToFormat(0, vbf);
    }

    auto& meshManager = *rs->getMeshManager();

    auto sphereMesh = meshManager.create();
    {
        auto sphere = tov::rendering::geometry::Sphere(5.0f);
        auto& submesh = sphereMesh->createSubmesh(sphere, vertexDataFormat);
        submesh.setMaterial(colourMaterial);
    }

    auto cuboidMesh = meshManager.create();
    {
        auto cuboid = tov::rendering::geometry::Cube(5.0f);
        auto& submesh = cuboidMesh->createSubmesh(cuboid, vertexDataFormat);
        submesh.setMaterial(textureMaterial);
    }

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*sphereMesh);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(0, 0, -40);
        entityNode.getTransform().setTranslation(translation);
    }

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*sphereMesh);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(5, 5, -30);
        entityNode.getTransform().setTranslation(translation);
    }

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*cuboidMesh);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(-2, 0, -15);
        entityNode.getTransform().setTranslation(translation);
        node = &entityNode;
    }

    emscripten_set_main_loop(oneIteration, 0, 1);

    return 0;
}
