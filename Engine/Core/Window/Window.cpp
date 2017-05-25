#include "Window.h"

GLFWwindow* RedSt4R::Window::m_Window;

RedSt4R::Window::Window(float windowWidth, float windowHeight, char* windowName, bool bFullScreen)
	:m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_WindowName(windowName)
{
	RedSt4R::EngineConfig::SetWindowSize(m_WindowWidth, m_WindowHeight);

	glfwInit();
	if (USE_VULKAN)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_Window = glfwCreateWindow(windowWidth, windowHeight, "RedSt4R Engine 2 [Vulkan]", nullptr, nullptr);
	}
	else if(USE_OPENGL)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_Window = glfwCreateWindow(windowHeight, windowHeight, "RedSt4R Engine 2 [OpenGL]", nullptr, nullptr);
	}
	else
	{

	}

	glfwMakeContextCurrent(m_Window);
	glewInit();
}

RedSt4R::Window::~Window()
{

}

bool RedSt4R::Window::ShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

void RedSt4R::Window::Clear()
{

}

void RedSt4R::Window::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void RedSt4R::Window::Close()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void RedSt4R::Window::CreateVulkanSurface(VkInstance pInstance, VkDevice pDevice, VkPhysicalDevice pPhysicalDevice)
{
	VkResult r;

	VkWin32SurfaceCreateInfoKHR win32surfaceinfo = {};
	win32surfaceinfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	win32surfaceinfo.hwnd = glfwGetWin32Window(m_Window);
	win32surfaceinfo.hinstance = GetModuleHandle(nullptr);
	auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(pInstance, "vkCreateWin32SurfaceKHR");

	r = CreateWin32SurfaceKHR(pInstance, &win32surfaceinfo, nullptr, &m_VulkanSurface);
	if (r != VK_SUCCESS) RS_ERROR("Failed Creating Win32Surface!");

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pPhysicalDevice, m_VulkanSurface, &m_VulkanSurfaceCapabilities);

	//------------------------- Create SwapChain -------------------------//
	std::vector<VkSurfaceFormatKHR> formats;
	uint32_t format_count = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(pPhysicalDevice, m_VulkanSurface, &format_count, nullptr);
	formats.resize(format_count);
	vkGetPhysicalDeviceSurfaceFormatsKHR(pPhysicalDevice, m_VulkanSurface, &format_count, formats.data());

	if (formats[0].format == VK_FORMAT_UNDEFINED)
	{
		m_VulaknSurfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
		m_VulaknSurfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	}
	else
	{
		m_VulaknSurfaceFormat = formats[0];
	}
}
