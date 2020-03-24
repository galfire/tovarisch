#include <iostream>

#include <array>
#include <vector>

#include <tov/core.h>
#include <tov/memory.h>

#include <tov/memory_config.h>

#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

#include <tov/rendering/render_target.h>
#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>

#include <tov/rendering/entity.h>
#include <tov/rendering/mesh_component.h>
#include <tov/rendering/mesh/mesh.h>
#include <tov/rendering/mesh/mesh_manager.h>

#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering/commands/command_bucket.h>

#include <tov/rendering/pipeline/pipeline_state_object.h>
#include <tov/rendering_gl/pipeline/shader.h>
#include <tov/rendering_gl/pipeline/program.h>

#include <tov/rendering_gl/buffers/buffer_manager.h>
#include <tov/rendering/geometry/sphere.h>

#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering/win32/window_events.h>

#include <tov/rendering/viewport.h>

#include <tov/rendering_gl/window_renderer_support.h>

#include <iostream>

using Viewport = tov::rendering::Viewport;
using WindowPlatformSupport = tov::rendering::win32::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::win32::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem;

int main(int argc, char** argv)
{
    WindowPlatformSupport platformSupport;
    WindowRendererSupport rendererSupport;

    auto rs = RenderSystem(platformSupport, rendererSupport);

    tov::rendering::Scene scene;
    tov::rendering::SceneNode node;

    auto c = *scene.createCamera();
    node.attachSceneObject(&c);

    auto& window = rs.createRenderWindow("WINDWOWWW", 640, 480, false);
    auto vp1 = window.createViewport(c, 0, 0.0f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Red);
    auto vp2 = window.createViewport(c, 1, 0.5f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Green);

    auto& window2 = rs.createRenderWindow("canvas2", 640, 180, false);
    auto vp3 = window2.createViewport(c, 2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Blue);

    auto sphere = tov::rendering::geometry::Sphere(1.0f, 4, 4);

    using BufferManager = tov::rendering::gl::buffers::BufferManager;
    BufferManager bufferManager;
    using MeshManager = tov::rendering::mesh::MeshManager<BufferManager>;
    MeshManager meshManager(bufferManager);
    auto mesh = meshManager.create();
    auto submesh = mesh->createSubmesh(sphere);
    
    auto entity = scene.createEntity();
    entity->createMeshComponent(*mesh);
    tov::rendering::SceneNode node2;
    node2.attachSceneObject(entity);

    {
        using ShaderType = tov::rendering::pipeline::ShaderType;

        tov::rendering::gl::pipeline::Shader v(ShaderType::VERTEX, "./shaders/vertex.vert.glsl");
        tov::rendering::gl::pipeline::Shader f(ShaderType::FRAGMENT, "./shaders/simple.frag.glsl");

        tov::rendering::gl::pipeline::Program p;
        p.attachShader(v);
        p.attachShader(f);
        p.link();

        tov::rendering::pipeline::PipelineStateObject pso(p, meshManager.getPreferredVertexDataFormat());



        p.use();

        p.setMatrix4("viewMatrix", c.getViewMatrix());
        p.setMatrix4("projectionMatrix", c.getProjectionMatrix());
        p.setMatrix4("modelMatrix", node2.getTransform().getHomogeneousMatrix());
    }

    while(1)
    {
        tov::math::Radian r(0.1f);
        tov::math::Vector3 axis = tov::math::Vector3::UNIT_Y;
        tov::math::Quaternion rotation(r, axis);
        node2.getTransform().rotate(rotation);
        rs.renderFrame();
    }

#if TOV_COMPILER == TOV_COMPILER_MSVC
    system("PAUSE");
#endif

    return 0;
}
