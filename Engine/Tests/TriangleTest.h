#pragma once

#include "../API/RS_API.h"
#include "../Core/Vertex/VertexTypes.h"

using namespace RedSt4R;
using namespace API;

class TriangleTest
{
	private:
		GLFWwindow* window;

		RSRenderer* renderer;
		RSVertexShader* vs;
		RSPixelShader* ps;
		RSVertexBuffer* vb;
		RSGraphicsPipeline* graphicsPipeline;

	public:
		TriangleTest(GLFWwindow* pWindow);
		~TriangleTest();

		void Prepare();
		void Update();
		void Render();
		void End();
};