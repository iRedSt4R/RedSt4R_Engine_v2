#include "RSRenderer.h"
#include "../Vulkan/VulkanRenderer.h"
#include "../OpenGL/OpenGLRenderer.h"

namespace RedSt4R
{
	namespace API
	{
		RSRenderer* RedSt4R::API::RSRenderer::CreateRenderer(RSDevice* pDevice, RedSt4R::Window* pWindow)
		{
			if (USE_VULKAN) return new VulkanRenderer(pDevice, pWindow);
			//if (USE_OPENGL) return new OpenGLRenderer(pWindow);
		}
	}
}