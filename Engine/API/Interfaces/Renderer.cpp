#include "Renderer.h"
#include "../Vulkan/VkRenderer.h"

namespace RedSt4R
{
	namespace API
	{
		Renderer * RedSt4R::API::Renderer::CreateRenderer(GLFWwindow * pWindow)
		{
			if(USE_VULKAN) return new VkRenderer(pWindow);
		}
	}
}