#include "RSVertexShader.h"
#include "../Vulkan/VulkanVertexShader.h"

namespace RedSt4R
{
	namespace API
	{
		RSVertexShader* RSVertexShader::CreateVertexShader()
		{
			if (USE_VULKAN) return new VulkanVertexShader();
		}

	}
}