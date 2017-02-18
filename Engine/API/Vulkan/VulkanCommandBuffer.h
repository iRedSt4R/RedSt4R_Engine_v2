#pragma once
#include "../Interfaces/CommandBuffer.h"
#include "../../RSIncludeVulkan.h"

namespace RedSt4R
{
	namespace API
	{
		class VulkanCommandBuffer : public CommandBuffer
		{
		public:
			VkCommandPool		m_CommandPool = VK_NULL_HANDLE;
			VkCommandBuffer		m_CommandBuffer = VK_NULL_HANDLE;
			VkCommandBufferBeginInfo cbBeginInfo = {};
			VkSubmitInfo submitInfo = {};



		public:
			VulkanCommandBuffer(float flags);
			~VulkanCommandBuffer();

			virtual void Begin() override;
			virtual void End() override;
			virtual void SubmitToQueue(void* pQueue) override;
			virtual void Reset() override;
		};

	}
}