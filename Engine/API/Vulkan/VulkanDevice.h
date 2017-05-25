#pragma once
#include "../Interfaces/RSDevice.h"
#include "../../RSIncludeVulkan.h"
#include "VulkanRenderer.h"
#include <vector>

namespace RedSt4R
{
	namespace API
	{
		class VulkanDevice : public RSDevice
		{
		private:
			VkDevice m_Device;
			std::vector<VkPhysicalDevice> m_PhysicalDevices;
			std::vector<VkQueueFamilyProperties>	m_QueueFamilyProperties;
			int queueFamilyIndexWithGraphicsBit;

		public:
			VulkanDevice(EDeviceType deviceType, bool bUseAllGPUs);
			~VulkanDevice();

			__inline VkDevice GetVkDevice() { return m_Device; }
			__inline std::vector<VkPhysicalDevice> GetVkPhysicalDevices() { return m_PhysicalDevices; }

		};
	}
}