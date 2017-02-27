#pragma once
#include "../../RSIncludeVulkan.h"
#include <vector>
#include "../../Debug/DebugMacros.h"
#include "../RS_API.h"

namespace RedSt4R
{
	namespace API
	{
		class VkRenderer : public Renderer
		{
		public:
			GLFWwindow*			m_Window			= nullptr;

			std::vector<VkPhysicalDevice>			vPhysicalDevices;
			std::vector<VkQueueFamilyProperties>	vQueueFamilyProperties;

			CommandBuffer* m_commandbuf;

			static int queueFamilyIndexWithGB;
			uint32_t currentBackBufferIndex = UINT32_MAX;
			VkFence	m_FenceForSwapChain = VK_NULL_HANDLE;

			static VkDevice		m_Device;
			VkPhysicalDevice	m_PhysicalDevice	= VK_NULL_HANDLE;
			bool bIsDestroyed = false;


			VkInstance					m_Instance	= VK_NULL_HANDLE;	
			static VkQueue				m_Queue;
			static VkFence				m_Fence;
			static VkSemaphore			m_Semaphore;

			VkSurfaceKHR		m_Surface			= VK_NULL_HANDLE;								
			VkSwapchainKHR		m_Swapchain			= VK_NULL_HANDLE;
			VkRenderPass		m_RenderPass		= VK_NULL_HANDLE;
			uint32_t swapChainImages = EngineConfig::GetSwapChainImageCout();

			std::vector<VkImage> m_vSwapChainImage;
			std::vector<VkImageView> m_vSwapChainImageView;
			std::vector<VkFramebuffer> m_vFrameBuffer;

			VkSurfaceCapabilitiesKHR m_SurfaceCapabilities = {};
			VkSurfaceFormatKHR  m_SurfaceFormat = {};

			VkRect2D rect2D;
			VkClearValue clearValue;

		public:
			VkRenderer(GLFWwindow *pWindow);
			~VkRenderer();
		
			void InitRenderer() override;
			void BeginRenderer() override;
			void Update() override;
			void Render() override;
			void EndRenderer() override;
			void ShutDownRenderer() override;

			__inline VkDevice GetVkDevice() { return m_Device; }

		private:



		};
	}
}