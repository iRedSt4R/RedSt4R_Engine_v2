#include "RSCommandBuffer.h"
#include "../Vulkan/VulkanCommandBuffer.h"

namespace RedSt4R
{
	namespace API
	{
		RSCommandBuffer* RedSt4R::API::RSCommandBuffer::CreateCommandBuffer(float flags)
		{
			if(USE_VULKAN) return new VulkanCommandBuffer(flags);
		}
	}
}