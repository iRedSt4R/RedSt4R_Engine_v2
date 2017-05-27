#pragma once
#include "../Interfaces/RSCommandBuffer.h"
#include "../../RSIncludeVulkan.h"

namespace RedSt4R
{
	namespace API
	{
		class VulkanCommandBuffer : public RSCommandBuffer
		{
		public:
			VkCommandPool m_CommandPool = VK_NULL_HANDLE;
			VkCommandBuffer	m_CommandBuffer;
			VkCommandBufferBeginInfo cbBeginInfo = {};
			VkSubmitInfo submitInfo = {};


			virtual void rsCmdBindVertexBuffers(RSVertexBuffer* pVertexBuffers, uint32_t firstBinding, uint32_t bindingCount, int offsets) override;
			virtual void rsCmdBindPipeline(RSGraphicsPipeline* pGraphicsPipeline, EPipelineBindPoint bindPoint) override;


			virtual void rsCmdBeginRenderPass(RSGraphicsPipeline* pGraphicsPipeline, uint32_t frameBufferIndex) override;


			virtual void rsCmdDraw(uint32_t vertexCount, uint32_t firstVertex) override;

		public:
			VulkanCommandBuffer(float flags);
			~VulkanCommandBuffer();

			virtual void Begin() override;
			virtual void End() override;
			virtual void SubmitToQueue(void* pQueue) override;
			virtual void Reset() override;

			//__inline static VulkanCommandBuffer* GetVulkanCommandBuffer
			__inline VkCommandBuffer GetVkCommandBuffer() { return m_CommandBuffer; }
		};

	}
}