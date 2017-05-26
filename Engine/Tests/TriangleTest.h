#pragma once

#include "../API/RS_API.h"
#include "../Core/Vertex/VertexTypes.h"
#include "../Core/Window/Window.h"

using namespace RedSt4R;
using namespace API;

class TriangleTest
{
	private:
		Window* window;

		RSRenderer* renderer;
		RSCommandBuffer* commandBuffer;
		RSVertexBuffer* vertexBuffer;

		/*
		RSGraphicsPipeline* graphicsPipeline;

		RSVertexBuffer* vb;
		RSIndexBuffer* ib;

		RSVertexShader* vs;
		RSPixelShader* ps;

		RSTexture* texture;
		*/

	public:
		TriangleTest(Window* pWindow);
		~TriangleTest();

		void Prepare();
		void Update();
		void Render();
		void End();
};