#include "RSQueue.h"
#include "../Vulkan/VulkanQueue.h"

namespace RedSt4R
{
	namespace API
	{
		RSQueue* RedSt4R::API::RSQueue::CreateQueue()
		{
			if (USE_VULKAN) return new VulkanQueue();
		}
	}
}