#include "RSVertexBuffer.h"
#include "../OpenGL/OpenGLVertexBuffer.h"
#include "../Vulkan/VulkanBuffer.h"

namespace RedSt4R
{
	namespace API
	{
		//RSVertexBuffer* RSVertexBuffer::CreateVertexBuffer(int size, Vertex* vertexData)
		//{
			//if (USE_VULKAN) return new VulkanVertexShader(shaderPath);
			//if (USE_OPENGL) return new OpenGLVertexBuffer(size, vertexData);
	//	}

		RSVertexBuffer* RSVertexBuffer::CreateVertexBuffer(RSDevice* pDevice, VertexColor* vertexData)
		{
			if (USE_VULKAN) return new VulkanVertexBuffer((VulkanDevice*)pDevice, vertexData);
		}

	}
}