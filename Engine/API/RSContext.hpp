#pragma once
#include "RS_API.h"
#include "../Core/Window/Window.h"

//template <class T>
//void RSAPI_CAST()

namespace RedSt4R
{
	namespace API
	{
		class RS_RTCT
		{
		private:
			static RSRenderer* m_Renderer;
			static Window* activeWindow;

		public:
			FORCE_INLINE Window* GetActiveWindow() { return activeWindow; }
			FORCE_INLINE RSRenderer* GetRenderer() { return m_Renderer; }
		};

		RedSt4R::API::RSRenderer* RS_RTCT::m_Renderer;
		RedSt4R::API::Window* RS_RTCT::activeWindow;

	}
}

