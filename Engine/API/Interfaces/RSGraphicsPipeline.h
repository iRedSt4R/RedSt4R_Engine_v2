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
			virtual void SetVertexBuffer(RSVertexBuffer* rsVB) = 0;
			virtual void SetVertexShader(RSVertexShader* rsVS) = 0;
			virtual void SetPixelShader(RSPixelShader* rsPS) = 0;
			virtual void Execute() = 0;

		public:
			static RSGraphicsPipeline* CreateGraphicsPipeline(RSVertexBuffer* rsVB, RSVertexShader* rsVS, RSPixelShader* rsPS, RSIndexBuffer* rsIB);
		};
	}
}