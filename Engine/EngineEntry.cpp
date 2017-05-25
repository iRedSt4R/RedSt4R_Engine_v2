//#include "RSIncludeVulkan.h"
#include "API/RSIncludeOpenGL.h"
#include "Config/RenderingConfig.h"
#include "Debug/DebugMacros.h"
#include "API/RS_API.h"
#include "Core/Vertex/VertexTypes.h"
#include "Tests/TriangleTest.h"
#include "Core/Window/Window.h"

/*********************** Correct Order ! *********************/
// 1) glfwInit();											  /
// 2) Create Window                                           /
// 3) Make Context Current                                    /
// 4) glewInit();                                             /
// 5) Init Others Stuff                                       /
// 6) Loops etc...                                            /
/**************************************************************/


TriangleTest* test;
RedSt4R::Window* window;

void main()
{
	window = new RedSt4R::Window(1100, 500, "sdfds");
	test = new TriangleTest(window);
	test->Prepare();

	

	while (!window->ShouldClose())
	{
		window->Clear();
		test->Update();
		window->Update();

	}
	
	window->Close();
}