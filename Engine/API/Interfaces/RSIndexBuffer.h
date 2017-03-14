#pragma once
#include "../../Debug/DebugMacros.h"
#include "../../Config/RenderingConfig.h"


namespace RedSt4R
{
	namespace API
	{
		class RSIndexBuffer
		{
		public:
			static RSIndexBuffer* CreateIndexBuffer(int size, uint32_t* indexData);
		};
	}
}