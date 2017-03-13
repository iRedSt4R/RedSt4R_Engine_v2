#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"

namespace RedSt4R
{
	namespace API
	{
		class RSCommandBuffer
		{
		public:
			virtual void Begin() = 0;
			virtual void End() = 0;
			virtual void SubmitToQueue(void* pQueue) = 0;
			virtual void Reset() = 0;

			static RSCommandBuffer* CreateCommandBuffer(float flags);
		};
	}
}