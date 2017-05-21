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
		/*
		RSGraphicsPipeline* graphicsPipeline;

		RSVertexBuffer* vb;
		RSIndexBuffer* ib;

		RSVertexShader* vs;
		RSPixelShader* ps;

		RSTexture* texture;
		*/

	public:
		TriangleTest(GLFWwindow* pWindow);
		~TriangleTest();

		void Prepare();
		void Update();
		void Render();
		void End();
};