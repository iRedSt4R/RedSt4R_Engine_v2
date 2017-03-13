#pragma once

#include "../Interfaces/RSVertexShader.h"
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class VulkanVertexShader : public RSVertexShader
		{
		public:


		public:
			VulkanVertexShader(char* shaderPath);
			~VulkanVertexShader();
		};
	}
}