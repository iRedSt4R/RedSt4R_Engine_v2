#include "RSDevice.h"
#include "../Vulkan/VulkanDevice.h"

namespace RedSt4R
{
	namespace API
	{
		RSDevice* RedSt4R::API::RSDevice::CreateDevice(EDeviceType deviceType, bool bUseAllGPUs)
		{
			if (USE_VULKAN) return new VulkanDevice(deviceType, bUseAllGPUs);
			//return nullptr;
		}
	}
}