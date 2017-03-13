#include "RSVertexBuffer.h"
#include "../OpenGL/OpenGLVertexBuffer.h"

namespace RedSt4R
{
	namespace API
	{
		RSVertexBuffer* RSVertexBuffer::CreateVertexBuffer(int size, glm::vec3* vertexData)
		{
			//if (USE_VULKAN) return new VulkanVertexShader(shaderPath);
			if (USE_OPENGL) return new OpenGLVertexBuffer(size, vertexData);
		}

	}
}