#include "VkEngine.h"

VkResult r;

void CheckVk(VkResult a_Result, char* a_FailedMessage)
{
	if (a_Result != VK_SUCCESS)
	{
		RS_ERROR(a_FailedMessage)
	}
}

void CheckVk(VkResult a_Result, char* a_FailedMessage, char* a_SuccessMessage)
{
	if (a_Result != VK_SUCCESS)
	{
		RS_ERROR(a_FailedMessage)
	}
	else
	{
		RS_LOG(a_SuccessMessage)
	}
}

RedSt4R::VkEngine::VkEngine(GLFWwindow* pWindow)
{
	m_Window = pWindow;
	InitEngine();
}

void RedSt4R::VkEngine::InitEngine()
{
	//------------------------- Application and Instance ----------------------------//
	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName = "RedSt4R Engine";
	applicationInfo.apiVersion = VK_API_VERSION_1_0;
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	instanceCreateInfo.enabledLayerCount = 0;
	instanceCreateInfo.ppEnabledLayerNames = nullptr;

	uint32_t count;
	const char** extensions = glfwGetRequiredInstanceExtensions(&count);
	instanceCreateInfo.enabledExtensionCount = count;
	instanceCreateInfo.ppEnabledExtensionNames = extensions;

	r = vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance);
	if (r != VK_SUCCESS) RS_ERROR("Failed creating Vulkan Instance!");

	//------------------------- Win32 Surface ----------------------------//
	VkWin32SurfaceCreateInfoKHR win32surfaceinfo = {};
	win32surfaceinfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	win32surfaceinfo.hwnd = glfwGetWin32Window(m_Window);
	win32surfaceinfo.hinstance = GetModuleHandle(nullptr);
	auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(m_Instance, "vkCreateWin32SurfaceKHR");

	//CheckVk(CreateWin32SurfaceKHR(m_Instance, &win32surfaceinfo, nullptr, &m_Surface), "Failed Creating Windows Surface!", "Successfully Created Windows Surface!");
	r = CreateWin32SurfaceKHR(m_Instance, &win32surfaceinfo, nullptr, &m_Surface);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Win32Surface!");

	//------------- Check For Supported GPUs -----------------//
	uint32_t deviceCount;
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
	vPhysicalDevices.resize(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, vPhysicalDevices.data());
	RS_LOG("Number of Supported Devices: "<< deviceCount);

	//------------ Check for queue Family Index --------------//
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevices[0], &queueFamilyCount, nullptr);
	vQueueFamilyProperties.resize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevices[0], &queueFamilyCount, vQueueFamilyProperties.data());

	for (int i = 0; i < queueFamilyCount; i++)
	{
		if (vQueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			queueFamilyIndexWithGB = i;
			RS_WARNING("Found Queue Family Index with 'VK_QUEUE_GRAPHICS_BIT' at index: " << i);
		}
	}

	float queuePriorities[]{ 1.0f };

	VkDeviceQueueCreateInfo deviceQueueInfo = {};
	deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueInfo.pNext = nullptr;
	deviceQueueInfo.flags = 0;
	deviceQueueInfo.pQueuePriorities = queuePriorities;
	deviceQueueInfo.queueFamilyIndex = queueFamilyIndexWithGB;
	deviceQueueInfo.queueCount = 1;

	VkDeviceCreateInfo deviceinfo = {};
	deviceinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceinfo.pNext = nullptr;
	deviceinfo.queueCreateInfoCount = 1;
	deviceinfo.pQueueCreateInfos = &deviceQueueInfo;

	r = vkCreateDevice(vPhysicalDevices[0], &deviceinfo, nullptr, &m_Device);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Vulkan Device!");



	//--------------------------- SWAP CHAIN ----------------------------------//
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(vPhysicalDevices[0], m_Surface, &presentModeCount, nullptr);
}

void RedSt4R::VkEngine::UpdateEngine()
{

}

void RedSt4R::VkEngine::ShutdownEngine()
{
	if (!bIsDestroyed)
	{
		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		vkDestroyDevice(m_Device, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}

	bIsDestroyed = true;
}

RedSt4R::VkEngine::~VkEngine()
{
	if(!bIsDestroyed) ShutdownEngine();
}
