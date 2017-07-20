#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Core/Window/Window.h"
#include "RSCommandBuffer.h"
#include "RSDevice.h"

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
			virtual void Render(RSCommandBuffer* pRSCmd1, RSCommandBuffer* pRSCmd2) = 0;
			virtual void EndRenderer() = 0;
			virtual void ShutDownRenderer() = 0;

			static RSRenderer* CreateRenderer(RSDevice* pDevice, RedSt4R::Window* pWindow);
		};
	}
}