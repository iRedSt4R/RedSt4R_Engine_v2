#include "Window.h"

GLFWwindow* RedSt4R::Window::m_Window;

RedSt4R::Window::Window(float windowWidth, float windowHeight, char* windowName, bool bFullScreen)
	:m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_WindowName(windowName)
{
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
