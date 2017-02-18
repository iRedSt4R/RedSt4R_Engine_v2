#include "VkRenderer.h"

VkResult r;

int RedSt4R::API::VkRenderer::queueFamilyIndexWithGB = 0;

RedSt4R::API::VkRenderer::VkRenderer(GLFWwindow *pWindow)
{
	m_Window = pWindow;
}

RedSt4R::API::VkRenderer::~VkRenderer()
{
	
}

void RedSt4R::API::VkRenderer::InitRenderer()
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

	//---------------------- Check For Supported GPUs ------------------------//
	uint32_t deviceCount;
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
	vPhysicalDevices.resize(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, vPhysicalDevices.data());
	RS_LOG("Number of Supported Devices: " << deviceCount);

	//------------------- Check for queue Family Index -----------------------//
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
	VkBase::device = m_Device;

	vkGetDeviceQueue(m_Device, queueFamilyIndexWithGB, 0, &m_Queue);

	//------------------------- Create Win32 Surface ---------------------//
	VkWin32SurfaceCreateInfoKHR win32surfaceinfo = {};
	win32surfaceinfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	win32surfaceinfo.hwnd = glfwGetWin32Window(m_Window);
	win32surfaceinfo.hinstance = GetModuleHandle(nullptr);
	auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(m_Instance, "vkCreateWin32SurfaceKHR");

	r = CreateWin32SurfaceKHR(m_Instance, &win32surfaceinfo, nullptr, &m_Surface);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Win32Surface!");

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vPhysicalDevices[0], m_Surface, &m_SurfaceCapabilities);

	//------------------------- Create SwapChain -------------------------//
	std::vector<VkSurfaceFormatKHR> formats;
	uint32_t format_count = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevices[0], m_Surface, &format_count, nullptr);
	formats.resize(format_count);
	vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevices[0], m_Surface, &format_count, formats.data());

	if (formats[0].format == VK_FORMAT_UNDEFINED) 
	{
		m_SurfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
		m_SurfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	}
	else 
	{
		m_SurfaceFormat = formats[0];
	}

	uint32_t swapChainImages = 2;

	VkSwapchainCreateInfoKHR scCreateInfo = {};
	scCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	scCreateInfo.surface = m_Surface;
	scCreateInfo.minImageCount = swapChainImages; //swapChainImages Buffering
	scCreateInfo.imageFormat = m_SurfaceFormat.format;
	scCreateInfo.imageColorSpace = m_SurfaceFormat.colorSpace;
	scCreateInfo.imageExtent.width = 800;
	scCreateInfo.imageExtent.height = 600;
	scCreateInfo.imageArrayLayers = 1;
	scCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	scCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	scCreateInfo.queueFamilyIndexCount = 0;
	scCreateInfo.pQueueFamilyIndices = nullptr;
	scCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	scCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	scCreateInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	scCreateInfo.clipped = VK_TRUE;
	scCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	
	r = vkCreateSwapchainKHR(m_Device, &scCreateInfo, nullptr, &m_Swapchain);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating SwapChain!");

	//--------------------------- Swap Chain Images --------------------------//
	m_vSwapChainImage.resize(swapChainImages);
	m_vSwapChainImageView.resize(swapChainImages);

	r = vkGetSwapchainImagesKHR(m_Device, m_Swapchain, &swapChainImages, m_vSwapChainImage.data());
	if (r != VK_SUCCESS) RS_ERROR("Failed Getting SwapChain Images!");

	for (uint32_t i = 0; i < swapChainImages; ++i)
	{
		VkImageViewCreateInfo ivCreateInfo = {};
		ivCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ivCreateInfo.image = m_vSwapChainImage[i];
		ivCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		ivCreateInfo.format = m_SurfaceFormat.format;
		ivCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		ivCreateInfo.subresourceRange.baseMipLevel = 0;
		ivCreateInfo.subresourceRange.levelCount = 1;
		ivCreateInfo.subresourceRange.baseArrayLayer = 0;
		ivCreateInfo.subresourceRange.layerCount = 1;

		vkCreateImageView(m_Device, &ivCreateInfo, nullptr, &m_vSwapChainImageView[i]);
		if (r != VK_SUCCESS) RS_ERROR("Failed Creating ImageView From SwapChain Images!");
	}


	//--------------------------- Create Fence -----------------------------//
	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	vkCreateFence(m_Device, &fenceCreateInfo, nullptr, &m_Fence);

	//Create Semaphore
	VkSemaphoreCreateInfo sCreateInfo = {};
	sCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(m_Device, &sCreateInfo, nullptr, &m_Semaphore);


	//---------------------- Command Pool and Buffers -----------------------//
	m_commandbuf = CommandBuffer::CreateCommandBuffer(1);

	
}
void RedSt4R::API::VkRenderer::BeginRenderer()
{

}

void RedSt4R::API::VkRenderer::Update()
{

}

void RedSt4R::API::VkRenderer::Render()
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_CommandBuffer;

	//--------------- STARTING RECORDING COMMANDS TO COMMAND BUFFERS --------------//
	m_commandbuf->Begin();

	m_commandbuf->End();
	//---------------- ENDED RECORDING COMMANDS TO COMMAND BUFFERS --------------//

	//Submitting Command Buffers to Queue/s
	r = vkQueueSubmit(m_Queue, 1, &submitInfo, m_Fence);
	if (r != VK_SUCCESS) RS_ERROR("Failed Submitting Command Buffer To Queue!");

	vkWaitForFences(m_Device, 1, &m_Fence, VK_TRUE, UINT64_MAX);

}

void RedSt4R::API::VkRenderer::ShutDownRenderer()
{
	
}

