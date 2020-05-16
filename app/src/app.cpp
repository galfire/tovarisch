#include <iostream>

#include <tov/core.h>

#include <tov/math/matrix.h>
#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/pixel_format.h>

#include <tov/rendering/geometry/sphere.h>

#include <tov/rendering/entity.h>
#include <tov/rendering/mesh/mesh.h>
#include <tov/rendering/mesh/mesh_manager.h>

#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering_gl/pipeline/shader.h>
#include <tov/rendering_gl/pipeline/program.h>
#include <tov/rendering_gl/buffers/buffer_manager.h>

#include <tov/rendering_gl/texture/texture.h>

#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

using WindowPlatformSupport = tov::rendering::win32::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::win32::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem;

// adfadf

int main(int argc, char** argv)
{
    WindowPlatformSupport platformSupport;
    WindowRendererSupport rendererSupport;

    auto rs = RenderSystem(platformSupport, rendererSupport);

    tov::rendering::Scene scene(rs);
    auto& root = scene.getRootNode();

    auto& cameraNode = root.createChild();
    auto& camera = scene.createCamera();
    cameraNode.attachSceneObject(&camera);

    {
        auto& window = rs.createRenderWindow("Window", 800, 600, false);
        auto& vp = window.createViewport(2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Black);
        camera.attachViewport(vp);
    }

    auto fl = tov::rendering::pipeline::ConstantDefinition<float>::DEFINITION;
    auto integer = tov::rendering::pipeline::ConstantDefinition<int>::DEFINITION;
    using Vector3 = tov::math::Vector3;
    using Matrix4 = tov::math::Matrix4;
    auto mat4 = tov::rendering::pipeline::ConstantDefinition<Matrix4>::DEFINITION;
    auto vec3 = tov::rendering::pipeline::ConstantDefinition<Vector3>::DEFINITION;

    using ShaderType = tov::rendering::pipeline::ShaderType;
    tov::rendering::gl::pipeline::Shader vertexShader(ShaderType::VERTEX, "./shaders/vertex.vert.glsl");
    tov::rendering::gl::pipeline::Shader colourShader(ShaderType::FRAGMENT, "./shaders/colour.frag.glsl");
    tov::rendering::gl::pipeline::Shader textureShader(ShaderType::FRAGMENT, "./shaders/texture.frag.glsl");
    vertexShader.compile();
    colourShader.compile();
    textureShader.compile();

    tov::rendering::gl::pipeline::Program colourProgram;
    colourProgram.attachShader(vertexShader);
    colourProgram.attachShader(colourShader);
    colourProgram.link();
    colourProgram.addConstantDefinition("modelMatrix", mat4);
    colourProgram.addConstantDefinition("viewMatrix", mat4);
    colourProgram.addConstantDefinition("projectionMatrix", mat4);
    colourProgram.addConstantDefinition("colour", vec3);
    colourProgram.buildLocationMap();

    tov::rendering::gl::pipeline::Program textureProgram;
    textureProgram.attachShader(vertexShader);
    textureProgram.attachShader(textureShader);
    textureProgram.link();
    textureProgram.addConstantDefinition("modelMatrix", mat4);
    textureProgram.addConstantDefinition("viewMatrix", mat4);
    textureProgram.addConstantDefinition("projectionMatrix", mat4);
    textureProgram.addConstantDefinition("texture", integer);
    textureProgram.buildLocationMap();

    using BufferManager = tov::rendering::gl::buffers::BufferManager;
    BufferManager bufferManager;
    using MeshManager = tov::rendering::mesh::MeshManager;
    MeshManager meshManager(bufferManager);

    auto sphere = tov::rendering::geometry::Sphere(5.0f);
    auto mesh = meshManager.create();
    auto& submesh = mesh->createSubmesh(sphere, textureProgram);

    auto pixelFormat = tov::rendering::PixelFormat(8, 8, 8, 8, 0, 0);
    auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, 64 * 64);
    auto& pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);
    auto texture = tov::rendering::gl::texture::Texture2D(pbo, 64, 64, pixelFormat);
    
    auto buffer = new unsigned char[64 * 64 * 4];
    auto sz = texture.getSize();
    memset(buffer, 255, sz);
    for(unsigned int i = 0; i < sz; i += 4)
    {
        buffer[i + 0] = i % 255;
        buffer[i + 1] = i % 255;
        buffer[i + 2] = i % 255;
        buffer[i + 3] = i % 255;
    }
    pbo.updatePixelData(buffer, sz);

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*mesh);
        auto& drawDataList = entity.getDrawDataList();
        for (auto&& drawData : drawDataList)
        {
            auto& programInstance = drawData.getProgramInstance();
            //programInstance.setConstant<tov::math::Vector3>("colour", tov::math::Vector3(1.0f, 0.0f, 1.0f));
        }
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(0, 0, -40);
        entityNode.getTransform().setTranslation(translation);
    }

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*mesh);
        auto& drawDataList = entity.getDrawDataList();
        for (auto&& drawData : drawDataList)
        {
            auto& programInstance = drawData.getProgramInstance();
            //programInstance.setConstant<tov::math::Vector3>("colour", tov::math::Vector3(0.0f, 0.0f, 1.0f));
        }
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(5, 5, -30);
        entityNode.getTransform().setTranslation(translation);
    }

    while(1)
    {
        for (unsigned int i = 0; i < sz; i += 4)
        {
            buffer[i + 0] += 1;
            buffer[i + 0] %= 255;
            buffer[i + 1] += 3;
            buffer[i + 1] %= 255;
            buffer[i + 2] += 2;
            buffer[i + 2] %= 255;
        }
        pbo.updatePixelData(buffer, sz);

        texture.unpackPixelData();
        auto textureBind = texture.bind();

#if TOV_DEBUG
        std::cout << "STARTING FRAME...\n";
#endif
        rs.swapBuffers();
        scene.queue();
        rs.renderFrame();

#if TOV_DEBUG
        std::cout << "END FRAME\n";
#endif
    }

#if TOV_COMPILER == TOV_COMPILER_MSVC
    system("PAUSE");
#endif

    return 0;
}
