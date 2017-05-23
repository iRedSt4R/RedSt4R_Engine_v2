#pragma once
//#include "../RS_API.h"
#include "RSCommandBuffer.h"

namespace RedSt4R
{
	namespace API
	{
		class RSQueue
		{
		public:
			virtual void SumbitCommandBuffer(RSCommandBuffer* cmdBuffer) = 0;

			static RSQueue* CreateQueue();
		};
	}
}