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

namespace RedSt4R 
{
	class VkEngine 
	{
	private:
		GLFWwindow*	m_Window;

		std::vector<VkPhysicalDevice>			vPhysicalDevices;
		std::vector<VkQueueFamilyProperties>	vQueueFamilyProperties;

		VkInstance			m_Instance	 = VK_NULL_HANDLE;
		VkDevice			m_Device	 = VK_NULL_HANDLE;
		VkSurfaceKHR		m_Surface	 = VK_NULL_HANDLE;
		VkQueue				m_Queue		 = VK_NULL_HANDLE;


		
		int queueFamilyIndexWithGB = 0;
		bool bIsDestroyed = false;

	public:
		VkEngine(GLFWwindow* a_Window);
		~VkEngine();

		void InitEngine();
		void UpdateEngine();
		void ShutdownEngine();

		FORCE_INLINE VkPhysicalDevice*	GetVkPhysicalDevices()  { return &vPhysicalDevices[0]; }
		FORCE_INLINE VkInstance			GetVkInstance()			{ return m_Instance; }
		FORCE_INLINE VkDevice			GetVkDevice()			{ return m_Device; }
		FORCE_INLINE VkSurfaceKHR		GetVkSurface()			{ return m_Surface; }
		FORCE_INLINE VkQueue			GetVkQueue()			{ return m_Queue; }

		FORCE_INLINE int GetGraphicsFamilyIndex() { return queueFamilyIndexWithGB; }
	};
}