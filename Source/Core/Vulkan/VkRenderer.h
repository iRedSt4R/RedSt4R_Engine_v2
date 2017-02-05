#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <vector>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "../../Debug/DebugMacros.h"
#include "VkEngine.h"

namespace RedSt4R
{
	class VkRenderer
	{
	private:
		VkEngine*			m_VkEngine			= nullptr;
		VkInstance			m_Instance			= VK_NULL_HANDLE;	
		VkDevice			m_Device			= VK_NULL_HANDLE;
		VkPhysicalDevice	m_PhysicalDevice	= VK_NULL_HANDLE;
		GLFWwindow*			m_Window			= nullptr;

		VkCommandPool		m_CommandPool		= VK_NULL_HANDLE;
		VkCommandBuffer		m_CommandBuffer		= VK_NULL_HANDLE;
		VkQueue				m_Queue				= VK_NULL_HANDLE;
		VkFence				m_Fence				= VK_NULL_HANDLE;
		VkSemaphore			m_Semaphore			= VK_NULL_HANDLE;

		VkSurfaceKHR		m_Surface			= VK_NULL_HANDLE;								
		VkSwapchainKHR		m_Swapchain			= VK_NULL_HANDLE;

		std::vector<VkImage> m_vSwapChainImage;
		std::vector<VkImageView> m_vSwapChainImageView;

		VkSurfaceCapabilitiesKHR m_SurfaceCapabilities = {};
		VkSurfaceFormatKHR  m_SurfaceFormat = {};

	public:
		VkRenderer(GLFWwindow *pWindow);
		~VkRenderer();
		
		void BeginRenderer();
		void Update();
		void Render();
		void ShutDownRenderer();

	private:
		void InitRenderer();


	};
}