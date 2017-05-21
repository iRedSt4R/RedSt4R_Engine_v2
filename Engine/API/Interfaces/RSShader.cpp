#include "RSShader.h"
#include "../Vulkan/VulkanShader.h"

namespace RedSt4R
{
	namespace API
	{
		RSShader* RSShader::CreateShader(char* vertexShaderPath, char* pixelShaderPath)
		{
			if(USE_VULKAN) return new VulkanShader(vertexShaderPath, pixelShaderPath);
		}

	}
}