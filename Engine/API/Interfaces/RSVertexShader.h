#pragma once
#include "../../Config/RenderingConfig.h"
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class RSVertexShader
		{
		public:
			virtual void Bleh() = 0;

			static RSVertexShader* CreateVertexShader();
		};
	}
}