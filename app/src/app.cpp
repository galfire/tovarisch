#include <tov/core.h>

#include <tov/math/radian.h>
#include <tov/math/matrix.h>
#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/pixel_format.h>
#include <tov/rendering/image.h>

#include <tov/rendering/geometry/cuboid.h>
#include <tov/rendering/geometry/rectangle.h>
#include <tov/rendering/geometry/sphere.h>
#include <tov/rendering/geometry/triangle.h>

#include <tov/rendering/entity.h>
#include <tov/rendering/mesh_component.h>
#include <tov/rendering/mesh/mesh.h>
#include <tov/rendering/mesh/mesh_manager.h>

#include <tov/rendering/buffers/vertex_buffer_format.h>
#include <tov/rendering/buffers/vertex_format.h>
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

#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <iostream>

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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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

    auto rectangleMesh = meshManager.create();

    {
        auto geometry = tov::rendering::geometry::Rectangle(10.0f, 5.0f);
        rectangleMesh->createSubmesh(geometry, vertexDataFormat);
    }

    auto sphereMesh = meshManager.create();

    {
        auto sphere = tov::rendering::geometry::Sphere(5.0f);
        sphereMesh->createSubmesh(sphere, vertexDataFormat);
    }

    auto triangleMesh = meshManager.create();

    {
        auto triangle = tov::rendering::geometry::Triangle();
        triangleMesh->createSubmesh(triangle, vertexDataFormat);
    }

    auto cuboidMesh = meshManager.create();

    {
        auto cuboid = tov::rendering::geometry::Cuboid(5, 5, 5);
        cuboidMesh->createSubmesh(cuboid, vertexDataFormat);
    }

    auto image = tov::rendering::Image("./assets/skybox.png");
    auto data = image.data();
    auto size = image.getSize();

    auto pixelFormat = tov::rendering::PixelFormat(8, 8, 8, 8, 0, 0);
    auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, size);
    auto& pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);
    auto texture = tov::rendering::gl::texture::Texture2D(pbo, image.getWidth(), image.getHeight(), pixelFormat);
    
    pbo.updatePixelData(data, size);
    texture.unpackPixelData();

    /*auto buffer = new unsigned char[64 * 64 * 4];
    auto sz = texture.getSize();
    memset(buffer, 255, sz);
    for(unsigned int i = 0; i < sz; i += 4)
    {
        buffer[i + 0] = i % 255;
        buffer[i + 1] = i % 255;
        buffer[i + 2] = i % 255;
        buffer[i + 3] = i % 255;
    }
    pbo.updatePixelData(buffer, sz);*/


    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        auto& component = entity.createMeshComponent(*sphereMesh);
        auto& submesh = component.getMeshInstance().getSubmeshInstance(0);
        auto& programInstance = textureProgram.instantiate();
        programInstance.setConstant<int>("tex", 0);
        submesh.setProgramInstance(&programInstance);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(0, 0, -40);
        entityNode.getTransform().setTranslation(translation);
    }

    {
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        auto& component = entity.createMeshComponent(*sphereMesh);
        auto& submesh = component.getMeshInstance().getSubmeshInstance(0);
        auto& programInstance = colourProgram.instantiate();
        programInstance.setConstant<tov::math::Vector3>("colour", tov::math::Vector3(0.0f, 0.0f, 1.0f));
        submesh.setProgramInstance(&programInstance);
        entityNode.attachSceneObject(&entity);
        tov::math::Vector3 translation(5, 5, -30);
        entityNode.getTransform().setTranslation(translation);
    }


    //{
        auto& entityNode = root.createChild();
        auto& entity = scene.createEntity();
        auto& component = entity.createMeshComponent(*cuboidMesh);
        //auto& component = entity.createMeshComponent(*rectangleMesh);
        auto& submesh = component.getMeshInstance().getSubmeshInstance(0);
        auto& programInstance = textureProgram.instantiate();
        programInstance.setConstant<int>("tex", 0);
        submesh.setProgramInstance(&programInstance);
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
        auto angle = tov::math::Radian(0.001f);
        auto rotation = tov::math::Quaternion(angle, axis);
        entityNode.getTransform().rotate(rotation);

        //texture.unpackPixelData();
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
