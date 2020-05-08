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

#include <tov/rendering/geometry/sphere.h>
#include <tov/rendering/geometry/triangle.h>

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

    using ShaderType = tov::rendering::pipeline::ShaderType;
    tov::rendering::gl::pipeline::Shader vertexShader(ShaderType::VERTEX, "./shaders/vertex.vert.glsl");
    tov::rendering::gl::pipeline::Shader fragmentShader(ShaderType::FRAGMENT, "./shaders/simple.frag.glsl");
    vertexShader.compile();
    fragmentShader.compile();

    tov::rendering::gl::pipeline::Program program;
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);

    using Matrix4 = tov::math::Matrix4;
    auto def = tov::rendering::pipeline::ConstantDefinition<Matrix4>::DEFINITION;
    program.addConstantDefinition("modelMatrix", def);

    auto sphere = tov::rendering::geometry::Sphere(5.0f);

    using BufferManager = tov::rendering::gl::buffers::BufferManager;
    BufferManager bufferManager;

    using MeshManager = tov::rendering::mesh::MeshManager;
    MeshManager meshManager(bufferManager);
    auto mesh = meshManager.create();
    auto& submesh = mesh->createSubmesh(sphere, program);

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*mesh);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(0, 0, -40);
        entityNode.getTransform().setTranslation(translation);
    }

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        entity.createMeshComponent(*mesh);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(5, 5, -30);
        entityNode.getTransform().setTranslation(translation);
    }

	emscripten_set_main_loop(oneIteration, 0, 1);

	return 0;
}
