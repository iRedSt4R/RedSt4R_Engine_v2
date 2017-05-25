#include "VulkanDevice.h"

RedSt4R::API::VulkanDevice::VulkanDevice(EDeviceType deviceType, bool bUseAllGPUs)
{
	VkResult r;

	uint32_t deviceCount;
	vkEnumeratePhysicalDevices(VulkanRenderer::GetVkInstance(), &deviceCount, nullptr);
	m_PhysicalDevices.resize(deviceCount);
	vkEnumeratePhysicalDevices(VulkanRenderer::GetVkInstance(), &deviceCount, m_PhysicalDevices.data());
	RS_LOG("Number of Supported Devices: " << deviceCount);

	//------------------- Check for queue Family Index -----------------------//
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevices[0], &queueFamilyCount, nullptr);
	m_QueueFamilyProperties.resize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevices[0], &queueFamilyCount, m_QueueFamilyProperties.data());

	for (int i = 0; i < queueFamilyCount; i++)
	{
		if (m_QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			queueFamilyIndexWithGraphicsBit = i;
			RS_WARNING("Found Queue Family Index with 'VK_QUEUE_GRAPHICS_BIT' at index: " << i);
		}
	}

	float queuePriorities[]{ 1.0f };

	VkDeviceQueueCreateInfo deviceQueueInfo = {};
	deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueInfo.pNext = nullptr;
	deviceQueueInfo.flags = 0;
	deviceQueueInfo.pQueuePriorities = queuePriorities;
	deviceQueueInfo.queueFamilyIndex = queueFamilyIndexWithGraphicsBit;
	deviceQueueInfo.queueCount = 1;

	VkDeviceCreateInfo deviceinfo = {};
	deviceinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceinfo.pNext = nullptr;
	deviceinfo.queueCreateInfoCount = 1;
	deviceinfo.pQueueCreateInfos = &deviceQueueInfo;

	r = vkCreateDevice(m_PhysicalDevices[0], &deviceinfo, nullptr, &m_Device);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Vulkan Device!");
}

RedSt4R::API::VulkanDevice::~VulkanDevice()
{

}
