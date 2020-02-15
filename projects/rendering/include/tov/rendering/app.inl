namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	template<class DEF>
	void App<DEF>::setRenderSystem(RenderSystemType* renderSystem)
	{
		mActiveRenderSystem = renderSystem;
	}

	template<class DEF>
	App<DEF>::RenderWindowType& App<DEF>::createRenderWindow(uint width, uint height, bool fullscreen)
	{
		mActiveRenderSystem->createRenderWindow(width, height, fullscreen);
	}

	TOV_NAMESPACE_END
}