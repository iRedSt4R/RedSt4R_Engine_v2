#pragma once
#include "../../RSIncludeVulkan.h"
#include <vector>
#include "../../Debug/DebugMacros.h"
#include "VulkanCommandBuffer.h"
#include "../../Core/Window/Window.h"
#include "VulkanShader.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanDevice.h"
#include "../Interfaces/RSRenderer.h"
#include "VulkanBuffer.h"

namespace RedSt4R
{
	namespace API
	{
		class VulkanDevice;
		class VulkanVertexBuffer;
		class VulkanGraphicsPipeline;

		class VulkanRenderer : public RSRenderer
		{
		public:
			Window* window;

			VulkanCommandBuffer* m_commandbuf;
			VulkanCommandBuffer* m_commandBuf2;

			VulkanShader* testShader;
			VulkanGraphicsPipeline* graphicsPip;
			VulkanDevice* device;
			VulkanVertexBuffer* vertexBuffer;

			static int queueFamilyIndexWithGB;
			uint32_t currentBackBufferIndex = UINT32_MAX;
			VkFence	m_FenceForSwapChain = VK_NULL_HANDLE;

			static VkDevice				m_Device;
			static VkInstance			m_Instance;	
			static VkQueue				m_Queue;
			static VkFence				m_Fence;
			static VkSemaphore			m_Semaphore;
						
			VkSwapchainKHR		m_Swapchain			= VK_NULL_HANDLE;
			VkRenderPass		m_RenderPass		= VK_NULL_HANDLE;
			uint32_t swapChainImages = EngineConfig::GetSwapChainImageCout();

			std::vector<VkImage> m_vSwapChainImage;
			std::vector<VkImageView> m_vSwapChainImageView;
			std::vector<VkFramebuffer> m_vFrameBuffer;

			VkRect2D rect2D;
			VkClearValue clearValue;
			
		public:
			VulkanRenderer(RedSt4R::Window* pWindow);
			~VulkanRenderer();
		
			void InitRenderer() override;
			void BeginRenderer() override;
			void Update() override;
			void Render() override;
			void EndRenderer() override;
			void ShutDownRenderer() override;

			__inline VkDevice GetVkDevice() { return m_Device; }
			__inline static VkInstance GetVkInstance() { return m_Instance; }
		};
	}
}