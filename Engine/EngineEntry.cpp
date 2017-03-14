//#include "RSIncludeVulkan.h"
#include "API/RSIncludeOpenGL.h"
#include "Config/RenderingConfig.h"
#include "Debug/DebugMacros.h"
#include "API/RS_API.h"
#include "Core/Vertex/VertexTypes.h"
#include "Tests/TriangleTest.h"

/*********************** Correct Order ! *********************/
// 1) glfwInit();											  /
// 2) Create Window                                           /
// 3) Make Context Current                                    /
// 4) glewInit();                                             /
// 5) Init Others Stuff                                       /
// 6) Loops etc...                                            /
/**************************************************************/

GLFWwindow* gameWindow;
TriangleTest* test;

void main()
{
	RedSt4R::EngineConfig::SetWindowSize(800, 600);

	glfwInit();
	if (USE_VULKAN)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		gameWindow = glfwCreateWindow(RedSt4R::EngineConfig::GetWindowWidth(), RedSt4R::EngineConfig::GetWindowHeight(), "RedSt4R Vulkan Engine v0.1", nullptr, nullptr);
	}
	else
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		gameWindow = glfwCreateWindow(RedSt4R::EngineConfig::GetWindowWidth(), RedSt4R::EngineConfig::GetWindowHeight(), "RedSt4R Vulkan Engine v0.1", nullptr, nullptr);
	}
	glfwMakeContextCurrent(gameWindow);
	glewInit();

	test = new TriangleTest(gameWindow);
	test->Prepare();

	

	while (!glfwWindowShouldClose(gameWindow))
	{
		glfwPollEvents();
		test->Update();

	}


	glfwDestroyWindow(gameWindow);
	glfwTerminate();
}