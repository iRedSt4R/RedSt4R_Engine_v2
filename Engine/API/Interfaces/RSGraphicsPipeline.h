#pragma once
#include "../../Debug/DebugMacros.h"
#include "../RS_API.h"

namespace RedSt4R
{
	namespace API
	{
		class RSGraphicsPipeline
		{
		public:
			RSVertexShader* vertexShader;
			RSPixelShader* pixelShader;
			RSCommandBuffer* commandBuffer;

		public:
			static RSGraphicsPipeline* CreateGraphicsPipeline(float flags);
		};
	}
}