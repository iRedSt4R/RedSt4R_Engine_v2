#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class RSShader
		{
		public:

			static RSShader* CreateShader(char* vertexShaderPath, char* pixelShaderPath);
		};
	}
}