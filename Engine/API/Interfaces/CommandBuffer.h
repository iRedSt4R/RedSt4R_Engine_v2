#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class CommandBuffer
		{
		public:
			virtual void Begin() = 0;
			virtual void End() = 0;
			virtual void Reset() = 0;

			static CommandBuffer* CreateCommandBuffer(float flags);
		};
	}
}