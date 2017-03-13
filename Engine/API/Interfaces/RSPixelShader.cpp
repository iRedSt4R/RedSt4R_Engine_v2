#include "RSPixelShader.h"
#include "../OpenGL/OpenGLPixelShader.h"

namespace RedSt4R
{
	namespace API
	{
		RSPixelShader* RedSt4R::API::RSPixelShader::CreatePixelShader(char* shaderPath)
		{
			//if (USE_VULKAN) return new VulkanCommandBuffer(shaderPath);
			if (USE_OPENGL) return new OpenGLPixelShader(shaderPath);
		}
	}
}
