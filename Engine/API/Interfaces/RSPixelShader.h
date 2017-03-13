#pragma once
#include "../../Config/RenderingConfig.h"
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class RSPixelShader
		{
		public:
			static RSPixelShader* CreatePixelShader(char* shaderPath);
		};
	}
}
