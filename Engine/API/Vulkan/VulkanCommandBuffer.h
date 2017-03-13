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