#include "RSRenderer.h"
#include "../Vulkan/VulkanRenderer.h"
#include "../OpenGL/OpenGLRenderer.h"

namespace RedSt4R
{
	namespace API
	{
		RSRenderer* RedSt4R::API::RSRenderer::CreateRenderer(Window* pWindow)
		{
			if (USE_VULKAN) return new VulkanRenderer(pWindow);
			//if (USE_OPENGL) return new OpenGLRenderer(pWindow);
		}
	}
}