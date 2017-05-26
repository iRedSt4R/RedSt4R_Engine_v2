#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"
//#include "../RS_API.h"


namespace RedSt4R
{
	namespace API
	{
		enum class EPipelineBindPoint
		{
			Graphics, Compute
		};

		class RSCommandBuffer
		{
		public:
			virtual void Begin() = 0;
			virtual void End() = 0;
			virtual void SubmitToQueue(void* pQueue) = 0;
			virtual void Reset() = 0;

			//virtual void rsCmdBindVertexBuffers(RSVertexBuffer* pVertexBuffers, uint32_t firstBinding, uint32_t bindingCount, int offsets) = 0;
			//virtual void rsCmdBindPipeline(RSGraphicsPipeline* pGraphicsPipeline, EPipelineBindPoint) = 0;

			static RSCommandBuffer* CreateCommandBuffer(float flags);
		};
	}
}