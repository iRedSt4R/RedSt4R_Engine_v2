#include "VulkanRenderer.h"
#include "VkBase.h"

using namespace RedSt4R;

VkResult r;

int RedSt4R::API::VulkanRenderer::queueFamilyIndexWithGB = 0;
VkDevice RedSt4R::API::VulkanRenderer::m_Device = VK_NULL_HANDLE;
VkQueue RedSt4R::API::VulkanRenderer::m_Queue = VK_NULL_HANDLE;
VkFence RedSt4R::API::VulkanRenderer::m_Fence = VK_NULL_HANDLE;
VkSemaphore RedSt4R::API::VulkanRenderer::m_Semaphore = VK_NULL_HANDLE;

RedSt4R::API::VulkanRenderer::VulkanRenderer(GLFWwindow *pWindow)
{
	m_Window = Window::GetGLFWWindow();
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

	VkSwapchainCreateInfoKHR scCreateInfo = {};
	scCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	scCreateInfo.surface = m_Surface;
	scCreateInfo.minImageCount = swapChainImages; //swapChainImages Buffering
	scCreateInfo.imageFormat = m_SurfaceFormat.format;
	scCreateInfo.imageColorSpace = m_SurfaceFormat.colorSpace;
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

	//----------------------- Create Render Pass -----------------------//
	// TODO: Add Depth/Stencil

	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = m_SurfaceFormat.format;
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

	r = vkCreateRenderPass(m_Device, &renderPassInfo, nullptr, &m_RenderPass);
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
		framecf.width = 800;
		framecf.height = 600;
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

	rect2D.offset.x = 0;
	rect2D.offset.y = 0;
	rect2D.extent.height = 600;
	rect2D.extent.width = 800;

	clearValue.color.float32[0] = 0.2f;
	clearValue.color.float32[1] = 0.2f;
	clearValue.color.float32[2] = 0.2f;
	clearValue.color.float32[3] = 0.2f;

	//---------------------- Command Pool and Buffers -----------------------//
	m_commandbuf = RSCommandBuffer::CreateCommandBuffer(1);

	//---------------------- Creating Test Shader ----------------------------//
	testShader = RSShader::CreateShader("Shaders/vert.spv", "Shaders/frag.spv");

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)EngineConfig::GetWindowWidth();
	viewport.height = (float)EngineConfig::GetWindowHeight();
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &rect2D;

	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	rasterizer.depthBiasClamp = 0.0f; // Optional
	rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f; // Optional
	multisampling.pSampleMask = nullptr; // Optional
	multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	multisampling.alphaToOneEnable = VK_FALSE; // Optional

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f; // Optional
	colorBlending.blendConstants[1] = 0.0f; // Optional
	colorBlending.blendConstants[2] = 0.0f; // Optional
	colorBlending.blendConstants[3] = 0.0f; // Optional

	VkDynamicState dynamicStates[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};

	VkPipelineDynamicStateCreateInfo dynamicState = {};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = 2;
	dynamicState.pDynamicStates = dynamicStates;

	VkPipelineLayout pipelineLayout;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = 0; // Optional

	if (vkCreatePipelineLayout(m_Device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = ((VulkanShader*)testShader)->shaderStages.data();
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr; // Optional
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = nullptr; // Optional
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = m_RenderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	auto r = vkCreateGraphicsPipelines(m_Device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_Pipeline);
	if (r != VK_SUCCESS) RS_ERROR("FAILED CREATING GRAPHICS PIPELINE!!!!!!!");
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
	renderPassBeginInfo.renderPass = m_RenderPass;
	renderPassBeginInfo.framebuffer = m_vFrameBuffer[currentBackBufferIndex];
	renderPassBeginInfo.renderArea = rect2D;
	renderPassBeginInfo.clearValueCount = 1;
	renderPassBeginInfo.pClearValues = &clearValue;

	m_commandbuf->Begin();
	vkCmdBeginRenderPass(((VulkanCommandBuffer*)m_commandbuf)->GetVkCommandBuffer(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(((VulkanCommandBuffer*)m_commandbuf)->m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline);
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

