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

RedSt4R::API::VulkanRenderer::VulkanRenderer(RedSt4R::Window* pWindow)
	:window(pWindow)
{
	//m_Window = pWindow->GetGLFWWindow();
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
	//vPhysicalDevices = device->GetVkPhysicalDevices();

	vkGetDeviceQueue(device->GetVkDevice(), queueFamilyIndexWithGB, 0, &m_Queue);

	//------------------------- Create Win32 Surface ---------------------//

	window->CreateVulkanSurface(m_Instance, device->GetVkDevice(), device->GetVkPhysicalDevices()[0]);
	
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
	
	r = vkCreateSwapchainKHR(device->GetVkDevice(), &scCreateInfo, nullptr, &m_Swapchain);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating SwapChain!");

	//--------------------------- Swap Chain Images --------------------------//
	m_vSwapChainImage.resize(swapChainImages);
	m_vSwapChainImageView.resize(swapChainImages);

	r = vkGetSwapchainImagesKHR(device->GetVkDevice(), m_Swapchain, &swapChainImages, m_vSwapChainImage.data());
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

		vkCreateImageView(device->GetVkDevice(), &ivCreateInfo, nullptr, &m_vSwapChainImageView[i]);
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
	m_commandbuf = new VulkanCommandBuffer(1);
	m_commandBuf2 = new VulkanCommandBuffer(1);

	//---------------------- Creating Test Shader ----------------------------//
	testShader = RSShader::CreateShader("Shaders/vert.spv", "Shaders/frag.spv");

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)EngineConfig::GetWindowWidth();
	viewport.height = (float)EngineConfig::GetWindowHeight();
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = window->GetVkSurfaceFormat().format;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	auto r = vkCreateRenderPass(device->GetVkDevice(), &renderPassInfo, nullptr, &m_RenderPass);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating RenderPass!");

	m_vFrameBuffer.resize(swapChainImages);
	for (uint32_t i = 0; i < swapChainImages; ++i)
	{
		VkFramebufferCreateInfo framecf = {};
		framecf.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framecf.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framecf.renderPass = m_RenderPass;
		framecf.attachmentCount = 1;
		framecf.pAttachments = &m_vSwapChainImageView[i];
		framecf.width = EngineConfig::GetWindowWidth();
		framecf.height = EngineConfig::GetWindowHeight();
		framecf.layers = 1;
		r = vkCreateFramebuffer(device->GetVkDevice(), &framecf, nullptr, &m_vFrameBuffer[i]);
		if (r != VK_SUCCESS) RS_ERROR("Failed Creating FrameBuffer!");
	}

	RS_DESC_GRAPHICSPIPELINE gpDesc;
	gpDesc.clearValue = clearValue;
	gpDesc.device = device->GetVkDevice();
	gpDesc.rect2D = rect2D;
	gpDesc.surfaceFormat = window->GetVkSurfaceFormat();
	gpDesc.viewport = viewport;
	gpDesc.vertexBuffer = vertexBuffer;
	gpDesc.frameBuffer = m_vFrameBuffer.data();
	gpDesc.renderPass = m_RenderPass;

	graphicsPip = new VulkanGraphicsPipeline(testShader, &gpDesc);

	//--------------------------- Create Fence -----------------------------//
	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	vkCreateFence(device->GetVkDevice(), &fenceCreateInfo, nullptr, &m_Fence);
	vkCreateFence(device->GetVkDevice(), &fenceCreateInfo, nullptr, &m_FenceForSwapChain);

	//Create Semaphore
	VkSemaphoreCreateInfo sCreateInfo = {};
	sCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(device->GetVkDevice(), &sCreateInfo, nullptr, &m_Semaphore);

	m_commandbuf->Begin();
	m_commandbuf->rsCmdBeginRenderPass(graphicsPip, 0);
	m_commandbuf->rsCmdBindPipeline(graphicsPip, EPipelineBindPoint::Graphics);
	m_commandbuf->rsCmdBindVertexBuffers(vertexBuffer, 0, 1, 0);
	m_commandbuf->rsCmdDraw(3, 0);
	m_commandbuf->End();

	m_commandBuf2->Begin();
	m_commandBuf2->rsCmdBeginRenderPass(graphicsPip, 1);
	m_commandBuf2->rsCmdBindPipeline(graphicsPip, EPipelineBindPoint::Graphics);
	m_commandBuf2->rsCmdBindVertexBuffers(vertexBuffer, 0, 1, 0);
	m_commandBuf2->rsCmdDraw(3, 0);
	m_commandBuf2->End();


}
void RedSt4R::API::VulkanRenderer::BeginRenderer()
{
	vkAcquireNextImageKHR(device->GetVkDevice(), m_Swapchain, UINT64_MAX, 0, m_FenceForSwapChain, &currentBackBufferIndex);
	vkWaitForFences(device->GetVkDevice(), 1, &m_FenceForSwapChain, VK_TRUE, UINT64_MAX);
	vkResetFences(device->GetVkDevice(), 1, &m_FenceForSwapChain);
	vkQueueWaitIdle(m_Queue);
}

void RedSt4R::API::VulkanRenderer::Update()
{

}

void RedSt4R::API::VulkanRenderer::Render()
{
	
	if (currentBackBufferIndex == 0)
	{
		m_commandbuf->SubmitToQueue(m_Queue);
		vkWaitForFences(device->GetVkDevice(), 1, &m_Fence, VK_TRUE, UINT64_MAX);
	}
	else
	{
		m_commandBuf2->SubmitToQueue(m_Queue);
		vkWaitForFences(device->GetVkDevice(), 1, &m_Fence, VK_TRUE, UINT64_MAX);
	}
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

