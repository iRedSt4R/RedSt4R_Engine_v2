#pragma once

#include "../../API/RSIncludeOpenGL.h"
#include "../../RSIncludeVulkan.h"
#include "../../Config/RenderingConfig.h"
#include "../../Debug/DebugMacros.h"
#include <vector>


namespace RedSt4R
{
	//namespace API{ class VulkanRenderer; }

	class Window
	{
	private:
		int m_WindowWidth, m_WindowHeight;
		char* m_WindowName;

		static GLFWwindow* m_Window;

		//Vulkan Surface
		VkSurfaceKHR m_VulkanSurface;
		VkSurfaceCapabilitiesKHR m_VulkanSurfaceCapabilities = {};
		VkSurfaceFormatKHR  m_VulaknSurfaceFormat;


	public:
		Window(float windowWidth, float windowHeight, char* windowName, bool bFullScreen = false);
		~Window();

		bool ShouldClose();
		void Clear();
		void Update();
		void Close();

		void CreateVulkanSurface(VkInstance pInstance, VkDevice pDevice, VkPhysicalDevice pPhysicalDevice);

	public:
		__inline static GLFWwindow* GetGLFWWindow() { return m_Window; }
		__inline VkSurfaceKHR GetVkSurface() { return m_VulkanSurface; }
		__inline VkSurfaceFormatKHR GetVkSurfaceFormat() { return m_VulaknSurfaceFormat; }
	};
}