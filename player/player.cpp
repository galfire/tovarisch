// player.cpp : Defines the entry point for the application.
//

#include "player.h"

#include <tov/core.h>

#include <tov/rendering/render_target.h>
#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene.h>
#include <tov/rendering/scene_node.h>

#include <tov/rendering/web/window_platform_support.h>
#include <tov/rendering_gl/window_renderer_support.h>

#include <tov/rendering_gl/pipeline/shader.h>
#include <tov/rendering_gl/pipeline/program.h>

#include <emscripten/emscripten.h>

using WindowPlatformSupport = tov::rendering::web::WindowPlatformSupport;
using WindowRendererSupport = tov::rendering::web::gl::WindowRendererSupport;
using RenderSystem = tov::rendering::RenderSystem;

WindowPlatformSupport platformSupport;
WindowRendererSupport rendererSupport;
RenderSystem rs(platformSupport, rendererSupport);

void oneIteration()
{
	rs.renderFrame();
}

int main()
{
	tov::rendering::Scene scene;
	tov::rendering::SceneNode node;

	auto& c = scene.createCamera();

	auto& window = rs.createRenderWindow("#canvas1", 640, 480, false);
	window.createViewport(c, 0, 0.0f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Red);
	window.createViewport(c, 1, 0.5f, 0.0f, 0.5f, 1.0f, tov::rendering::Colour::Green);

	auto& window2 = rs.createRenderWindow("#canvas2", 640, 180, false);
	window2.createViewport(c, 2, 0.0f, 0.0f, 1.0f, 1.0f, tov::rendering::Colour::Blue);

	{
		using ShaderType = tov::rendering::pipeline::ShaderType;

		tov::rendering::gl::pipeline::Shader v(ShaderType::VERTEX, "/shaders/vertex.vert.glsl");
		tov::rendering::gl::pipeline::Shader f(ShaderType::FRAGMENT, "/shaders/simple.frag.glsl");

		tov::rendering::gl::pipeline::Program p;
		p.attachShader(v);
		p.attachShader(f);
		p.link();
		p.use();

		p.setMatrix4("viewMatrix", c.getViewMatrix());
		p.setMatrix4("projectionMatrix", c.getProjectionMatrix());
		//p.setMatrix4("modelMatrix", node2.getTransform().getHomogeneousMatrix());
	}

	emscripten_set_main_loop(oneIteration, 0, 1);

	return 0;
}
