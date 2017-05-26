#include "VulkanRenderer.h"
#include "VkBase.h"

VertexColor vertices[] = { // Top Right
	VertexColor(0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f),  // Bottom Right
	VertexColor(0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f),  // Bottom Left
	VertexColor(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f)   // Top Left 
};

using namespace RedSt4R;

VkResult r;

int RedSt4R::API::VulkanRenderer::queueFamilyIndexWithGB = 0;
VkDevice RedSt4R::API::VulkanRenderer::m_Device = VK_NULL_HANDLE;
VkInstance RedSt4R::API::VulkanRenderer::m_Instance = VK_NULL_HANDLE;
VkQueue RedSt4R::API::VulkanRenderer::m_Queue = VK_NULL_HANDLE;
VkFence RedSt4R::API::VulkanRenderer::m_Fence = VK_NULL_HANDLE;
VkSemaphore RedSt4R::API::VulkanRenderer::m_Semaphore = VK_NULL_HANDLE;
VkSurfaceFormatKHR RedSt4R::API::VulkanRenderer::m_SurfaceFormat = {};

RedSt4R::API::VulkanRenderer::VulkanRenderer(RedSt4R::Window* pWindow)
	:window(pWindow)
{
	m_Window = pWindow->GetGLFWWindow();
}

RedSt4R::API::VulkanRenderer::~VulkanRenderer()
{
	
}

void RedSt4R::API::VulkanRenderer::InitRenderer()
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
	device = new VulkanDevice(EDeviceType::BestGPU, false);
	m_Device = device->GetVkDevice();
	vPhysicalDevices = device->GetVkPhysicalDevices();

	vkGetDeviceQueue(m_Device, queueFamilyIndexWithGB, 0, &m_Queue);

	//------------------------- Create Win32 Surface ---------------------//

	window->CreateVulkanSurface(m_Instance, m_Device, vPhysicalDevices[0]);
	
	VkSwapchainCreateInfoKHR scCreateInfo = {};
	scCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	scCreateInfo.surface = window->GetVkSurface();
	scCreateInfo.minImageCount = swapChainImages; //swapChainImages Buffering
	scCreateInfo.imageFormat = window->GetVkSurfaceFormat().format;
	scCreateInfo.imageColorSpace = window->GetVkSurfaceFormat().colorSpace;
	scCreateInfo.imageExtent.width = EngineConfig::GetWindowWidth();
	scCreateInfo.imageExtent.height = EngineConfig::GetWindowHeight();
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
		ivCreateInfo.format = window->GetVkSurfaceFormat().format;
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

	vertexBuffer = new VulkanVertexBuffer(device, vertices);

	//----------------------- Create Render Pass -----------------------//
	// TODO: Add Depth/Stencil

	rect2D.offset.x = 0;
	rect2D.offset.y = 0;
	rect2D.extent.height = EngineConfig::GetWindowHeight();
	rect2D.extent.width = EngineConfig::GetWindowWidth();

	clearValue.color.float32[0] = 0.2f;
	clearValue.color.float32[1] = 0.2f;
	clearValue.color.float32[2] = 0.2f;
	clearValue.color.float32[3] = 0.2f;

	//---------------------- Command Pool and Buffers -----------------------//
	m_commandbuf = RSCommandBuffer::CreateCommandBuffer(1);

	//---------------------- Creating Test Shader ----------------------------//
	testShader = RSShader::CreateShader("Shaders/vert.spv", "Shaders/frag.spv");

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)EngineConfig::GetWindowWidth();
	viewport.height = (float)EngineConfig::GetWindowHeight();
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	RS_DESC_GRAPHICSPIPELINE gpDesc;
	gpDesc.clearValue = clearValue;
	gpDesc.device = m_Device;
	gpDesc.rect2D = rect2D;
	gpDesc.surfaceFormat = window->GetVkSurfaceFormat();
	gpDesc.viewport = viewport;
	gpDesc.vertexBuffer = vertexBuffer;


	
	graphicsPip = RSGraphicsPipeline::CreateGraphicsPipeline(testShader, &gpDesc);

	m_vFrameBuffer.resize(swapChainImages);
	for (uint32_t i = 0; i < swapChainImages; ++i)
	{
		VkFramebufferCreateInfo framecf = {};
		framecf.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framecf.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framecf.renderPass = ((VulkanGraphicsPipeline*)graphicsPip)->GetVkRenderPass();
		framecf.attachmentCount = 1;
		framecf.pAttachments = &m_vSwapChainImageView[i];
		framecf.width = EngineConfig::GetWindowWidth();
		framecf.height = EngineConfig::GetWindowHeight();
		framecf.layers = 1;
		r = vkCreateFramebuffer(m_Device, &framecf, nullptr, &m_vFrameBuffer[i]);
		if (r != VK_SUCCESS) RS_ERROR("Failed Creating FrameBuffer!");
	}

	//--------------------------- Create Fence -----------------------------//
	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	vkCreateFence(m_Device, &fenceCreateInfo, nullptr, &m_Fence);
	vkCreateFence(m_Device, &fenceCreateInfo, nullptr, &m_FenceForSwapChain);

	//Create Semaphore
	VkSemaphoreCreateInfo sCreateInfo = {};
	sCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(m_Device, &sCreateInfo, nullptr, &m_Semaphore);

}
void RedSt4R::API::VulkanRenderer::BeginRenderer()
{
	vkAcquireNextImageKHR(m_Device, m_Swapchain, UINT64_MAX, 0, m_FenceForSwapChain, &currentBackBufferIndex);
	vkWaitForFences(m_Device, 1, &m_FenceForSwapChain, VK_TRUE, UINT64_MAX);
	vkResetFences(m_Device, 1, &m_FenceForSwapChain);
	vkQueueWaitIdle(m_Queue);
}

void RedSt4R::API::VulkanRenderer::Update()
{

}

void RedSt4R::API::VulkanRenderer::Render()
{
	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.renderPass = ((VulkanGraphicsPipeline*)graphicsPip)->GetVkRenderPass();
	renderPassBeginInfo.framebuffer = m_vFrameBuffer[currentBackBufferIndex];
	renderPassBeginInfo.renderArea = rect2D;
	renderPassBeginInfo.clearValueCount = 1;
	renderPassBeginInfo.pClearValues = &clearValue;

	VkDeviceSize offsets[] = { 0 };

	m_commandbuf->Begin();
	vkCmdBeginRenderPass(((VulkanCommandBuffer*)m_commandbuf)->GetVkCommandBuffer(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(((VulkanCommandBuffer*)m_commandbuf)->m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, ((VulkanGraphicsPipeline*)graphicsPip)->GetVkPipeline());
	vkCmdBindVertexBuffers(((VulkanCommandBuffer*)m_commandbuf)->m_CommandBuffer, 0, 1, vertexBuffer->GetVkBuffer(), offsets);
	vkCmdDraw(((VulkanCommandBuffer*)m_commandbuf)->m_CommandBuffer, 3, 1, 0, 0);
	m_commandbuf->End();
	
	m_commandbuf->SubmitToQueue(m_Queue);

	vkWaitForFences(m_Device, 1, &m_Fence, VK_TRUE, UINT64_MAX);

}

void RedSt4R::API::VulkanRenderer::EndRenderer()
{
	VkResult res = VkResult::VK_RESULT_MAX_ENUM;

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 0;
	presentInfo.pWaitSemaphores = nullptr;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &m_Swapchain;
	presentInfo.pImageIndices = &currentBackBufferIndex;


	vkQueuePresentKHR(m_Queue, &presentInfo);
}

void RedSt4R::API::VulkanRenderer::ShutDownRenderer()
{
	
}

