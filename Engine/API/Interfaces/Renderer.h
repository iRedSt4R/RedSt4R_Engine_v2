#pragma once
#include "../../RSIncludeVulkan.h"

namespace RedSt4R
{
	namespace API
	{
		class Renderer
		{
		public:
			virtual void InitRenderer() = 0; 
			virtual void BeginRenderer() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
			virtual void ShutDownRenderer() = 0;

			static Renderer* CreateRenderer(GLFWwindow* pWindow);
		};
	}
}