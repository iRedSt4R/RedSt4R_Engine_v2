#pragma once
#include "../../Debug/DebugMacros.h"
#include "RS_API_DESC.h"
#include "RSShader.h"

namespace RedSt4R
{
	namespace API
	{	
		class RSGraphicsPipeline
		{

		public:
			static RSGraphicsPipeline* CreateGraphicsPipeline(RSShader* shader, RS_DESC_GRAPHICSPIPELINE* gpDesc);
		};
	}
}