#include "RSVertexBuffer.h"
#include "../OpenGL/OpenGLVertexBuffer.h"
#include "../../Core/Vertex/VertexTypes.h"

namespace RedSt4R
{
	namespace API
	{
		RSVertexBuffer* RSVertexBuffer::CreateVertexBuffer(int size, VertexBase* vertexData)
		{
			//if (USE_VULKAN) return new VulkanVertexShader(shaderPath);
			if (USE_OPENGL) return new OpenGLVertexBuffer(size, vertexData);
		}

	}
}