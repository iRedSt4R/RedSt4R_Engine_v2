#pragma once
#include "../Interfaces/RSQueue.h"
#include "../../RSIncludeVulkan.h"

namespace RedSt4R
{
	namespace API
	{
		class VulkanQueue : public RSQueue
		{
		public:
			VkQueue m_Queue = VK_NULL_HANDLE;
			


		public:
			VulkanQueue();
			~VulkanQueue();

			virtual void SumbitCommandBuffer(RSCommandBuffer* cmdBuffer) override;

			//__inline static VulkanCommandBuffer* GetVulkanCommandBuffer
			__inline VkQueue GetVkQueue() { return m_Queue; }
		};

	}
}