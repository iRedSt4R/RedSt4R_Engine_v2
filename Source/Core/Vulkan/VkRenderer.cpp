#include "VkRenderer.h"


RedSt4R::VkRenderer::VkRenderer(GLFWwindow *pWindow)
{
	m_Window = pWindow;
	m_VkEngine = new RedSt4R::VkEngine(m_Window);
	m_Device = m_VkEngine->GetVkDevice();
	m_Instance = m_VkEngine->GetVkInstance();
	m_PhysicalDevice = *(m_VkEngine->GetVkPhysicalDevices());
	vkGetDeviceQueue(m_Device, m_VkEngine->GetGraphicsFamilyIndex(), 0, &m_Queue);

	InitRenderer();
}

RedSt4R::VkRenderer::~VkRenderer()
{
	m_VkEngine->ShutdownEngine();
}

void RedSt4R::VkRenderer::InitRenderer()
{
	VkResult r;


	//------------------------- Create Win32 Surface ---------------------//
	VkWin32SurfaceCreateInfoKHR win32surfaceinfo = {};
	win32surfaceinfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	win32surfaceinfo.hwnd = glfwGetWin32Window(m_Window);
	win32surfaceinfo.hinstance = GetModuleHandle(nullptr);
	auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(m_Instance, "vkCreateWin32SurfaceKHR");

	r = CreateWin32SurfaceKHR(m_Instance, &win32surfaceinfo, nullptr, &m_Surface);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Win32Surface!");

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_PhysicalDevice, m_Surface, &m_SurfaceCapabilities);

	//------------------------- Create SwapChain -------------------------//
	std::vector<VkSurfaceFormatKHR> formats;
	uint32_t format_count = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &format_count, nullptr);
	formats.resize(format_count);
	vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &format_count, formats.data());

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
	VkCommandPoolCreateInfo cpcf = {};
	cpcf.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cpcf.pNext = nullptr;
	cpcf.queueFamilyIndex = m_VkEngine->GetGraphicsFamilyIndex();
	cpcf.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	r = vkCreateCommandPool(m_Device, &cpcf, nullptr, &m_CommandPool);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Command Pool!")
	else RS_LOG("Successfully Created Command Pool")

	VkCommandBufferAllocateInfo cbAllocateInfo = {};
	cbAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cbAllocateInfo.pNext = nullptr;
	cbAllocateInfo.commandBufferCount = 1;
	cbAllocateInfo.commandPool = m_CommandPool;
	cbAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	r = vkAllocateCommandBuffers(m_Device, &cbAllocateInfo, &m_CommandBuffer);
	if (r != VK_SUCCESS) RS_ERROR("Failed Allocating Command Buffers!");

	VkCommandBufferBeginInfo cbBeginInfo = {};
	cbBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cbBeginInfo.pNext = nullptr;

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_CommandBuffer;

	//--------------- STARTING RECORDING COMMANDS TO COMMAND BUFFERS --------------//
	vkBeginCommandBuffer(m_CommandBuffer, &cbBeginInfo);

	vkEndCommandBuffer(m_CommandBuffer);
	//---------------- ENDED RECORDING COMMANDS TO COMMAND BUFFERS --------------//

	//Submitting Command Buffers to Queue/s
	r = vkQueueSubmit(m_Queue, 1, &submitInfo, m_Fence);
	if (r != VK_SUCCESS) RS_ERROR("Failed Submitting Command Buffer To Queue!");

	vkWaitForFences(m_Device, 1, &m_Fence, VK_TRUE, UINT64_MAX);

}
void RedSt4R::VkRenderer::BeginRenderer()
{

}

void RedSt4R::VkRenderer::Update()
{

}

void RedSt4R::VkRenderer::Render()
{

}

void RedSt4R::VkRenderer::ShutDownRenderer()
{
	
}

