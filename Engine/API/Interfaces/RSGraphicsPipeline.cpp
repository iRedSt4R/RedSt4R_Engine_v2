#include "RSGraphicsPipeline.h"
#include "../Vulkan/VulkanGraphicsPipeline.h"

namespace RedSt4R
{
	namespace API
	{
		RSGraphicsPipeline* RedSt4R::API::RSGraphicsPipeline::CreateGraphicsPipeline(RSShader* shader, RS_DESC_GRAPHICSPIPELINE* gpDesc)
		{
			//TODO: if (USE_OPENGL) return new OpenGLGraphicsPipeline(rsVB, rsVS, rsPS, rsIB);
			if (USE_VULKAN) return new VulkanGraphicsPipeline(shader, gpDesc);
		}
	}
}
