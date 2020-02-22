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
#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering/buffers/buffer_object_manager.h>
#include <tov/rendering/buffers/vertex_buffer_format.h>
#include <tov/rendering/buffers/vertex_attribute.h>
#include <tov/rendering/buffers/vertex_format.h>
#include <tov/rendering/buffers/lock_settings.h>
#include <tov/rendering/buffers/index_type.h>

#include <tov/rendering_gl/buffers/vertex_buffer_object.h>
#include <tov/rendering_gl/buffers/index_buffer_object.h>


#include <tov/rendering/win32/window_platform_support.h>
#include <tov/rendering/win32/window_events.h>

#include <tov/rendering_gl/viewport.h>
#include <tov/rendering_gl/window_renderer_support.h>

using Viewport = tov::rendering::gl::Viewport;
using WindowPlatformSupport = tov::rendering::win32::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::win32::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem<Viewport>;

int main(int argc, char** argv)
{
	WindowPlatformSupport platformSupport;
	WindowRendererSupport rendererSupport;

	auto rs = RenderSystem(platformSupport, rendererSupport);

	tov::rendering::Scene scene;
	tov::rendering::SceneNode node;

	auto c = *scene.createCamera();
	node.attachSceneObject(&c);

	auto window = rs.createRenderWindow("WINDWOWWW", 640, 480, false);
	auto vp1 = window->createViewport(c, 0, 0.0f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Red);
	auto vp2 = window->createViewport(c, 1, 0.5f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Green);

	auto window2 = rs.createRenderWindow("canvas2", 640, 180, false);
	auto vp3 = window2->createViewport(c, 2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Blue);

	auto entity = scene.createEntity();

	tov::rendering::mesh::Mesh mesh;
	auto meshComponent = entity->createMeshComponent(mesh);

	tov::rendering::SceneNode node2;
	node2.attachSceneObject(entity);

	tov::rendering::buffers::BufferObjectManager manager;

	tov::rendering::buffers::VertexFormat vertexFormat;
	vertexFormat.addAttribute(tov::rendering::buffers::VertexAttribute::POSITION);
	vertexFormat.addAttribute(tov::rendering::buffers::VertexAttribute::NORMAL);
	vertexFormat.addAttribute(tov::rendering::buffers::VertexAttribute::TEXTURE_COORDINATE);
	std::cout << vertexFormat.getSize() << "\n";
	tov::rendering::buffers::VertexBufferFormat format(tov::rendering::buffers::VertexBufferFormat::SequenceType::SEQUENTIAL, vertexFormat);
	tov::rendering::gl::buffers::VertexBufferObject vbo(manager, format, 10);
	vbo.lock(tov::rendering::buffers::LockSettings::WRITE);
	vbo.unlock();

	int numIndices = 10;

	tov::rendering::buffers::IndexType indexType;
	if (numIndices < 2^8)
	{
		indexType = tov::rendering::buffers::IndexType::BITS_8;
	}
	else if (numIndices < 2^16)
	{
		indexType = tov::rendering::buffers::IndexType::BITS_16;
	}
	else
	{
		indexType = tov::rendering::buffers::IndexType::BITS_32;
	}
	tov::rendering::gl::buffers::IndexBufferObject ibo(manager, indexType, 10);
	ibo.lock(tov::rendering::buffers::LockSettings::WRITE);
	ibo.unlock();

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
