#include "RSGraphicsPipeline.h"
#include "../OpenGL/OpenGLGraphicsPipeline.h"

namespace RedSt4R
{
	namespace API
	{
		RSGraphicsPipeline* RedSt4R::API::RSGraphicsPipeline::CreateGraphicsPipeline(RSVertexBuffer* rsVB, RSVertexShader* rsVS, RSPixelShader* rsPS, RSIndexBuffer* rsIB)
		{
			if (USE_OPENGL) return new OpenGLGraphicsPipeline(rsVB, rsVS, rsPS, rsIB);
		}
	}
}
