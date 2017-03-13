#include "RSVertexShader.h"
#include "../OpenGL/OpenGLVertexShader.h"

namespace RedSt4R
{
	namespace API
	{
		RSVertexShader* RSVertexShader::CreateVertexShader(char* shaderPath)
		{
			//if (USE_VULKAN) return new VulkanVertexShader(shaderPath);
			if (USE_OPENGL) return new OpenGLVertexShader(shaderPath);
		}

	}
}