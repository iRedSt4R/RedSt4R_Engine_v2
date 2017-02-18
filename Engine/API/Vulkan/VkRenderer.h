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
			std::vector<VkPhysicalDevice>			vPhysicalDevices;
			std::vector<VkQueueFamilyProperties>	vQueueFamilyProperties;

			static int queueFamilyIndexWithGB;
			bool bIsDestroyed = false;

			VkInstance			m_Instance			= VK_NULL_HANDLE;	
			VkDevice			m_Device			= VK_NULL_HANDLE;
			VkPhysicalDevice	m_PhysicalDevice	= VK_NULL_HANDLE;
			GLFWwindow*			m_Window			= nullptr;

			VkCommandPool		m_CommandPool		= VK_NULL_HANDLE;
			VkCommandBuffer		m_CommandBuffer		= VK_NULL_HANDLE;
			CommandBuffer* m_commandbuf;

			static VkQueue				m_Queue;
			static VkFence				m_Fence;
			static VkSemaphore			m_Semaphore;

			VkSurfaceKHR		m_Surface			= VK_NULL_HANDLE;								
			VkSwapchainKHR		m_Swapchain			= VK_NULL_HANDLE;

			std::vector<VkImage> m_vSwapChainImage;
			std::vector<VkImageView> m_vSwapChainImageView;

			VkSurfaceCapabilitiesKHR m_SurfaceCapabilities = {};
			VkSurfaceFormatKHR  m_SurfaceFormat = {};

		public:
			VkRenderer(GLFWwindow *pWindow);
			~VkRenderer();
		
			void InitRenderer() override;
			void BeginRenderer() override;
			void Update() override;
			void Render() override;
			void ShutDownRenderer() override;

			__inline VkDevice GetVkDevice() { return m_Device; }

		private:


		};
	}
}