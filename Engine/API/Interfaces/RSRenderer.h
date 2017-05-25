#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Core/Window/Window.h"

namespace RedSt4R
{

	namespace API
	{
		class RSRenderer
		{
		public:
			virtual void InitRenderer() = 0; 
			virtual void BeginRenderer() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
			virtual void EndRenderer() = 0;
			virtual void ShutDownRenderer() = 0;

			static RSRenderer* CreateRenderer(RedSt4R::Window* pWindow);
		};
	}
}