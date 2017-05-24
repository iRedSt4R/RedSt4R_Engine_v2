#pragma once

#include "../Interfaces/RSGraphicsPipeline.h"
//#include "../Interfaces/RSRenderer.h"
//#include "../RS_API.h"
#include "VulkanShader.h"

class VulkanShader;

namespace RedSt4R
{
	namespace API
	{
		class VulkanGraphicsPipeline : public RSGraphicsPipeline
		{
		private:
			VkPipeline m_Pipeline;
			VkRect2D m_Rect2D;
			VkRenderPass m_RenderPass;
			VkPipelineLayout m_PipelineLayout;

			VulkanShader* m_Shader;

		public:
			VulkanGraphicsPipeline(RSShader* shader, RS_DESC_GRAPHICSPIPELINE* gpDesc);
			~VulkanGraphicsPipeline();

			__inline VkPipeline GetVkPipeline() { return m_Pipeline; }
			__inline VkRenderPass GetVkRenderPass() { return m_RenderPass; }

		};
	}
}

