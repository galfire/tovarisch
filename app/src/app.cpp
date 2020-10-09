#include <tov/core.h>

#include <tov/math/radian.h>
#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

#include <tov/rendering/backend.h>

#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/pixel_format.h>
#include <tov/rendering/image.h>

#include <tov/rendering/material.h>

#include <tov/rendering/pipeline/pipeline_state_descriptor.h>
#include <tov/rendering/pipeline/cull_mode.h>
#include <tov/rendering/pipeline/vertex_winding.h>

#include <tov/rendering/geometry/cube.h>
#include <tov/rendering/geometry/rectangle.h>
#include <tov/rendering/geometry/sphere.h>
#include <tov/rendering/geometry/triangle.h>

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
#include <tov/rendering/scene.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <iostream>

using WindowPlatformSupport = tov::rendering::win32::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::win32::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem;

// adfadfadf

int main(int argc, char** argv)
{
    WindowPlatformSupport platformSupport;
    WindowRendererSupport rendererSupport;

    auto rs = std::unique_ptr<RenderSystem>(
        tov::rendering::backend::createRenderSystem(platformSupport, rendererSupport)
    );

    tov::rendering::Scene scene(*rs.get());
    auto& root = scene.getRootNode();

    auto bufferManager = rs->getBufferManager();

    auto& cameraNode = root.createChild();
    auto& camera = scene.createCamera();
    cameraNode.attachSceneObject(&camera);

    {
        auto& window = rs->createRenderWindow("Window", 800, 600, false);
        auto& vp = window.createViewport(2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Black);
        camera.attachViewport(vp);
    }

    rs->initialize();

    auto colourMaterial = tov::rendering::Material();
    {
        auto pixelFormat = tov::rendering::PixelFormat(8, 8, 8, 8, 0, 0);
        auto size = 16 * 16 * pixelFormat.getSize();
        auto& pixelBuffer = *bufferManager->createPixelUnpackBuffer(pixelFormat, size);
        auto& pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);
        auto& texture = rs->createTexture2D(pbo, 16, 16, pixelFormat);

        auto buffer = new unsigned char[size];
        for (unsigned int i = 0; i < size; i += 4)
        {
            buffer[i + 0] = 122;
            buffer[i + 1] = 0;
            buffer[i + 2] = 255;
            buffer[i + 3] = 255;
        }
        pbo.updatePixelData(buffer, size);
        texture.unpackPixelData();

        colourMaterial.setAlbedoMap(&texture);
    }

    auto textureMaterial = tov::rendering::Material();
    {
        auto image = tov::rendering::Image("./assets/skybox.png");
        auto pixelFormat = image.getPixelFormat();
        auto size = image.getSize();
        auto& pixelBuffer = *bufferManager->createPixelUnpackBuffer(pixelFormat, size);
        auto& pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);
        auto& texture = rs->createTexture2D(pbo, image.getWidth(), image.getHeight(), pixelFormat);

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
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::COLOUR, 2);
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::TEXTURE_COORDINATE, 3);
        tov::rendering::buffers::VertexBufferFormat vbf(
            tov::rendering::buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
            vf
        );
        vertexDataFormat.mapHandleToFormat(0, vbf);
    }

    using MeshManager = tov::rendering::mesh::MeshManager;
    MeshManager meshManager(*bufferManager);

    auto rectangleMesh = meshManager.create();
        
    {
        auto geometry = tov::rendering::geometry::Rectangle(10.0f, 5.0f);
        auto& submesh = rectangleMesh->createSubmesh(geometry, vertexDataFormat);
        submesh.setMaterial(colourMaterial);
    }

    auto sphereMesh = meshManager.create();

    {
        auto sphere = tov::rendering::geometry::Sphere(5.0f);
        auto& submesh = sphereMesh->createSubmesh(sphere, vertexDataFormat);
        submesh.setMaterial(colourMaterial);
    }

    auto triangleMesh = meshManager.create();

    {
        auto triangle = tov::rendering::geometry::Triangle();
        auto& submesh = triangleMesh->createSubmesh(triangle, vertexDataFormat);
        submesh.setMaterial(colourMaterial);
    }

    auto cuboidMesh = meshManager.create();

    {
        auto cuboid = tov::rendering::geometry::Cube(5);
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

    //{
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*cuboidMesh);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(-2, 0, -15);
        entityNode.getTransform().setTranslation(translation);
    //}

    while(1)
    {
        /*for (unsigned int i = 0; i < sz; i += 4)
        {
            buffer[i + 0] += 1;
            buffer[i + 0] %= 255;
            buffer[i + 1] += 3;
            buffer[i + 1] %= 255;
            buffer[i + 2] += 2;
            buffer[i + 2] %= 255;
        }
        pbo.updatePixelData(buffer, sz);*/

        auto axis = tov::math::Vector3(0.0f, 1.0f, 0.0f);
        auto angle = tov::math::Radian(0.03f);
        auto rotation = tov::math::Quaternion(angle, axis);
        entityNode.getTransform().rotate(rotation);

        //texture.unpackPixelData();


#if TOV_DEBUG
        std::cout << "STARTING FRAME...\n";
#endif
        scene.queue();
        rs->renderFrame();
        rs->swapBuffers();

#if TOV_DEBUG
        std::cout << "END FRAME\n";
#endif
    }

#if TOV_COMPILER == TOV_COMPILER_MSVC
    system("PAUSE");
#endif

    return 0;
}
