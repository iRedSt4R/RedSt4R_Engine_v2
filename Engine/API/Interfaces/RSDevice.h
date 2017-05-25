#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Debug/DebugMacros.h"


enum class EDeviceType
{
	BestGPU, FirstGPU
};

namespace RedSt4R
{
	namespace API
	{
		class RSDevice
		{
		public:
			static RSDevice* CreateDevice(EDeviceType deviceType, bool bUseAllGPUs);
		};
	}
}