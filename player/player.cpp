// player.cpp : Defines the entry point for the application.
//

#include "player.h"

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
#include <tov/rendering/mesh_component.h>
#include <tov/rendering/mesh/mesh.h>
#include <tov/rendering/mesh/mesh_manager.h>
#include <tov/rendering/mesh/vertex_data_format.h>

#include <tov/rendering/buffers/pixel_buffer_object.h>

#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering_gl/pipeline/shader.h>
#include <tov/rendering_gl/pipeline/program.h>
#include <tov/rendering_gl/buffers/buffer_manager.h>
#include <tov/rendering_gl/texture/texture.h>

#include <tov/rendering/web/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <emscripten/emscripten.h>

using WindowPlatformSupport = tov::rendering::web::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::web::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem;

WindowPlatformSupport platformSupport;
WindowRendererSupport rendererSupport;
RenderSystem rs(platformSupport, rendererSupport);
tov::rendering::Scene scene(rs);

//adfadf

void oneIteration()
{
    rs.swapBuffers();

    scene.queue();

    rs.renderFrame();
}

int main()
{
    auto& root = scene.getRootNode();

    auto& cameraNode = root.createChild();
    auto& camera = scene.createCamera();
    cameraNode.attachSceneObject(&camera);

    {
        auto& window = rs.createRenderWindow("#canvas1", 800, 600, false);
        auto& vp = window.createViewport(2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Black);
        camera.attachViewport(vp);
    }

    using CType = tov::rendering::pipeline::ConstantType;

    auto fl = tov::rendering::pipeline::ConstantDefinition<CType::FLOAT, float>::DEFINITION;
    auto integer = tov::rendering::pipeline::ConstantDefinition<CType::INT, int>::DEFINITION;
    using Vector3 = tov::math::Vector3;
    using Matrix4 = tov::math::Matrix4;
    auto mat4 = tov::rendering::pipeline::ConstantDefinition<CType::MATRIX_4, Matrix4>::DEFINITION;
    auto vec3 = tov::rendering::pipeline::ConstantDefinition<CType::VECTOR_3, Vector3>::DEFINITION;
    auto tex2D = tov::rendering::pipeline::ConstantDefinition<CType::TEXTURE_2D, int>::DEFINITION;

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
    textureProgram.addConstantDefinition("tex", integer);
    textureProgram.buildLocationMap();

    using BufferManager = tov::rendering::gl::buffers::BufferManager;
    BufferManager bufferManager;
    using MeshManager = tov::rendering::mesh::MeshManager;
    MeshManager meshManager(bufferManager);

    auto vertexDataFormat = tov::rendering::mesh::VertexDataFormat();

    {
        tov::rendering::buffers::VertexFormat vf;
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::POSITION, 0);
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::NORMAL, 1);
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::COLOUR, 2);
        tov::rendering::buffers::VertexBufferFormat vbf(
            tov::rendering::buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
            vf
        );
        vertexDataFormat.mapHandleToFormat(0, vbf);
    }
    {
        tov::rendering::buffers::VertexFormat vf;
        vf.addAttribute(tov::rendering::buffers::VertexAttribute::TEXTURE_COORDINATE, 3);
        tov::rendering::buffers::VertexBufferFormat vbf(
            tov::rendering::buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
            vf
        );
        vertexDataFormat.mapHandleToFormat(1, vbf);
    }


    auto mesh = meshManager.create();

    {
        auto sphere = tov::rendering::geometry::Sphere(5.0f);
        mesh->createSubmesh(sphere, vertexDataFormat);
    }

    auto pixelFormat = tov::rendering::PixelFormat(8, 8, 8, 8, 0, 0);
    auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, 64 * 64);
    auto pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);
    auto texture = tov::rendering::gl::texture::Texture2D(pbo, 64, 64, pixelFormat);

    auto buffer = new unsigned char[64 * 64 * 4];
    auto sz = texture.getSize();
    memset(buffer, 255, sz);
    pbo.updatePixelData(buffer, sz);
    texture.unpackPixelData();
    auto bind = texture.bind();

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        auto& component = entity.createMeshComponent(*mesh);
        auto& submesh = component.getMeshInstance().getSubmeshInstance(0);
        auto& programInstance = textureProgram.instantiate();
        programInstance.setConstant<int>("tex", 0);
        //auto& programInstance = colourProgram.instantiate();
        //programInstance.setConstant<tov::math::Vector3>("colour", tov::math::Vector3(1.0f, 0.0f, 1.0f));
        submesh.setProgramInstance(&programInstance);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(0, 0, -40);
        entityNode.getTransform().setTranslation(translation);
    }

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        auto& component = entity.createMeshComponent(*mesh);
        auto& submesh = component.getMeshInstance().getSubmeshInstance(0);
        //auto& programInstance = textureProgram.instantiate();
        auto& programInstance = colourProgram.instantiate();
        programInstance.setConstant<tov::math::Vector3>("colour", tov::math::Vector3(0.0f, 0.0f, 1.0f));
        submesh.setProgramInstance(&programInstance);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(5, 5, -30);
        entityNode.getTransform().setTranslation(translation);
    }

    emscripten_set_main_loop(oneIteration, 0, 1);

    return 0;
}
