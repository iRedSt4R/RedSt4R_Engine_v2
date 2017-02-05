#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include "Source/Debug/DebugMacros.h"
#include "Source/Core/Vulkan/VkEngine.h"
#include "Source/Core/Vulkan/VkRenderer.h"

RedSt4R::VkRenderer* vkRenderer;

void main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* gameWindow = glfwCreateWindow(800, 600, "RedSt4R Vulkan Engine v0.1", nullptr, nullptr);

	vkRenderer = new RedSt4R::VkRenderer(gameWindow);
	

	while (!glfwWindowShouldClose(gameWindow))
	{
		glfwPollEvents();


	}


	glfwDestroyWindow(gameWindow);
	glfwTerminate();
}