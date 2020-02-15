#ifndef TOV_RENDERING_APP_H
#define TOV_RENDERING_APP_H

#include "rendering_core.h"

#include "render_system.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class Viewport> class RenderWindow;

	template<class DEF>
	class App
	{
		TOV_MOVABLE_ONLY(App)

		using ViewportType = typename DEF::ViewportType;
		using RenderSystemType = RenderSystem<ViewportType>;
		using RenderWindowType = RenderWindow<ViewportType>;

	public:
		App() noexcept = default;
		~App() noexcept = default;

		void setRenderSystem(RenderSystemType* renderSystem);
		
		RenderWindowType& createRenderWindow(uint width, uint height, bool fullscreen)

		void renderFrame();

	private:
		RenderSystemType* mActiveRenderSystem = nullptr;
		RenderWindowType* mMainRenderWindow = nullptr;
	};

	TOV_NAMESPACE_END // rendering
}

#include "app.inl"

#endif