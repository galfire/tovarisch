#include <tov/core.h>

#include <tov/math/radian.h>
#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

#include <tov/rendering/backend.h>

#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/image.h>
#include <tov/rendering/material.h>
#include <tov/rendering/pixel_format.h>

#include <tov/rendering/geometry/cube.h>
#include <tov/rendering/geometry/sphere.h>

#include <tov/rendering/entity.h>
#include <tov/rendering/mesh_component.h>
#include <tov/rendering/mesh/mesh.h>
#include <tov/rendering/mesh/mesh_manager.h>
#include <tov/rendering/mesh/submesh.h>

#include <tov/rendering/buffers/vertex_buffer_format.h>
#include <tov/rendering/buffers/vertex_format.h>
#include <tov/rendering/mesh/vertex_data_format.h>

#include <tov/rendering/texture/texture.h>

#include <tov/rendering/buffers/pixel_buffer_object.h>

#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering/scene/scene.h>
#include <tov/rendering/scene/skybox.h>

#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <iostream>
#include <chrono>

using WindowPlatformSupport = tov::rendering::win32::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::win32::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem;

// adfadfadfadfadf

int main(int argc, char** argv)
{
    WindowPlatformSupport platformSupport;
    WindowRendererSupport rendererSupport;

    auto rs = std::unique_ptr<RenderSystem>(
        tov::rendering::backend::createRenderSystem(platformSupport, rendererSupport)
    );

    tov::rendering::scene::Scene scene(*rs.get());
    auto& camera = scene.createCamera();
    camera.setNearDistance(0.1f);
    //camera.setFieldOfView(tov::math::PI / 6.0f);

    {
        auto& window = rs->createRenderWindow("Window", 800, 600, false);
        auto& vp = window.createViewport(2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Black);
        camera.attachViewport(vp);
    }

    auto& root = scene.getRootNode();
    auto& cameraNode = root.createChild();
    cameraNode.attachSceneObject(&camera);

    rs->initialize();

    auto& meshManager = *rs->getMeshManager();
    auto& bufferManager = *rs->getBufferManager();

    auto texture = (tov::rendering::texture::Texture*)nullptr;
    {
        auto image = tov::rendering::Image("./assets/equi_bar.jpg");
        auto pixelFormat = image.getPixelFormat();
        texture = &rs->createTexture2D(image.getWidth(), image.getHeight(), pixelFormat);

        auto size = image.getSize();
        auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, size);
        auto& pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);

        auto data = image.data();
        pbo.updatePixelData(data, size);
        texture->unpackPixelData(pbo);
    }

    auto skybox = tov::rendering::scene::Skybox(*rs.get(), texture);
    scene.setSkybox(&skybox);

    auto colourMaterial = tov::rendering::Material();
    {
        auto pixelFormat = tov::rendering::PixelFormat(8, 8, 8, 8, 0, 0);
        auto& texture = rs->createTexture2D(16, 16, pixelFormat);

        auto size = 16u * 16u * pixelFormat.getSize();
        auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, size);
        auto& pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);

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

        texture.unpackPixelData(pbo);

        colourMaterial.setAlbedoMap(&texture);
    }

    auto textureMaterial = tov::rendering::Material();
    {
        auto image = tov::rendering::Image("./assets/skybox.png");
        auto pixelFormat = image.getPixelFormat();
        auto& texture = rs->createTexture2D(image.getWidth(), image.getHeight(), pixelFormat);
        
        auto size = image.getSize();
        auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, size);
        auto& pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);

        auto data = image.data();
        pbo.updatePixelData(data, size);
        texture.unpackPixelData(pbo);

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

    auto node = (tov::rendering::SceneNode*)nullptr;
    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*cuboidMesh);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(-2, 0, -15);
        entityNode.getTransform().setTranslation(translation);
        node = &entityNode;
    }

    using namespace std::chrono_literals;

    constexpr auto timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto accumulator(0ns);
    auto currentTime = clock::now();

    while(1)
    {
        auto now = clock::now();
        auto deltaTime = now - currentTime;
        //std::cout << deltaTime.count() << "\n";
        currentTime = now;

        accumulator += deltaTime;

        while (accumulator >= timestep)
        {
            accumulator -= timestep;

            //previous_state = current_state;
            //update(&current_state); // update at a fixed rate each time
        }

        auto alpha = (float)accumulator.count() / std::chrono::duration_cast<std::chrono::nanoseconds>(timestep).count();

        {
            auto axis = tov::math::Vector3(0.0f, 1.0f, 0.0f);
            auto angle = tov::math::Radian(0.01f) * alpha;
            auto rotation = tov::math::Quaternion(angle, axis);
            node->getTransform().rotate(rotation);
        }

        /*{
            auto axis = tov::math::Vector3(0.0f, 1.0f, 0.0f);
            auto angle = tov::math::Radian(0.001f) * alpha;
            auto rotation = tov::math::Quaternion(angle, axis);
            cameraNode.getTransform().rotate(rotation);
        }*/


#if TOV_DEBUG
        //std::cout << "STARTING FRAME...\n";
#endif
        rs->renderFrame(scene);
        rs->swapBuffers();

#if TOV_DEBUG
        //std::cout << "END FRAME\n";
#endif
    }

#if TOV_COMPILER == TOV_COMPILER_MSVC
    system("PAUSE");
#endif

    return 0;
}
