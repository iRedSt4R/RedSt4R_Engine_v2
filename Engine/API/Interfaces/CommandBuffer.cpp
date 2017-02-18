#include "CommandBuffer.h"
#include "../Vulkan/VulkanCommandBuffer.h"

namespace RedSt4R
{
	namespace API
	{
		CommandBuffer* RedSt4R::API::CommandBuffer::CreateCommandBuffer(float flags)
		{
			if(USE_VULKAN) return new VulkanCommandBuffer(flags);
		}
	}
}